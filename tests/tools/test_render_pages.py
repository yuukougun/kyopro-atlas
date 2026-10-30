"""描いたページの崩れを数える道具（tools/render_pages.py。#61）の試験。
python3 -m unittest discover -s tests/tools
WebSocket・ページの一覧と絞り込み・配り方・まとめ方は Chrome なしで確かめる。Chrome（render_svg.py と同じ探し方）が
あれば、崩れを仕込んだ小さなサイトを実際に描いて、種類ごとに見つかることも確かめる（ないときは飛ばす。数秒かかる）。
道具は CI に入れない（手元で流す）ので、描く試験も CI（環境変数 CI がある）では飛ばす。"""
import http.client
import json
import os
import re
import socket
import struct
import subprocess
import sys
import tempfile
import threading
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import render_pages as rp  # noqa: E402
import render_svg  # noqa: E402

CHROME = None if os.environ.get("CI") else render_svg.find_chrome(None)


def server_frame(opcode: int, payload: bytes, fin: bool = True) -> bytes:
    """Chrome の側から送るフレーム（マスクしない）。"""
    n = len(payload)
    head = bytearray([(0x80 if fin else 0) | opcode])
    if n < 126:
        head.append(n)
    elif n < 1 << 16:
        head.append(126)
        head += struct.pack(">H", n)
    else:
        head.append(127)
        head += struct.pack(">Q", n)
    return bytes(head) + payload


def read_client_frame(sock: socket.socket) -> tuple[int, bytes]:
    """client（render_pages）が送ったフレームを読む。(opcode, 外したマスクの中身)。"""
    def take(n):
        b = b""
        while len(b) < n:
            b += sock.recv(n - len(b))
        return b
    b0, b1 = take(2)
    assert b1 & 0x80, "client のフレームはマスクする"
    n = b1 & 0x7F
    if n == 126:
        n = struct.unpack(">H", take(2))[0]
    elif n == 127:
        n = struct.unpack(">Q", take(8))[0]
    mask = take(4)
    return b0 & 0x0F, rp._xor(take(n), mask)


def bare_ws(sock: socket.socket) -> rp.WebSocket:
    """手順（handshake）を済ませた形の WebSocket。"""
    ws = rp.WebSocket.__new__(rp.WebSocket)
    ws.sock, ws.buf, ws.parts = sock, bytearray(), []
    return ws


class WebSocketTest(unittest.TestCase):
    def test_xor_roundtrip(self):
        mask = b"\x01\x80\xff\x7e"
        for n in (0, 1, 3, 4, 5, 1000):
            data = bytes((i * 37) % 256 for i in range(n))
            self.assertEqual(rp._xor(rp._xor(data, mask), mask), data)
        self.assertEqual(rp._xor(b"\x00\x00\x00\x00\x00", mask), b"\x01\x80\xff\x7e\x01")

    def test_encode_lengths(self):
        for n, extra in ((5, 0), (125, 0), (126, 2), (65535, 2), (65536, 8), (70000, 8)):
            payload = os.urandom(n)
            f = rp.encode_frame(0x1, payload, b"abcd")
            self.assertEqual(f[0], 0x81)
            self.assertTrue(f[1] & 0x80)
            self.assertEqual(f[1] & 0x7F, n if extra == 0 else (126 if extra == 2 else 127))
            self.assertEqual(f[2 + extra:6 + extra], b"abcd")
            self.assertEqual(rp._xor(f[6 + extra:], b"abcd"), payload)

    def test_recv_fragments_ping_and_close(self):
        a, b = socket.socketpair()
        try:
            ws = bare_ws(a)
            big = "x" * 70000
            b.sendall(server_frame(0x1, "こんにちは".encode()) +
                      server_frame(0x1, b"ab", fin=False) + server_frame(0x9, b"p") + server_frame(0x0, b"cd") +
                      server_frame(0x1, big.encode()) + server_frame(0x8, b""))
            self.assertEqual(ws.recv(2), "こんにちは")
            self.assertEqual(ws.recv(2), "abcd")
            self.assertEqual(read_client_frame(b), (0xA, b"p"))        # ping には pong を返す
            self.assertEqual(ws.recv(2), big)
            with self.assertRaises(ConnectionError):
                ws.recv(2)
        finally:
            a.close()
            b.close()

    def test_timeout_keeps_stream(self):
        a, b = socket.socketpair()
        try:
            ws = bare_ws(a)
            b.sendall(server_frame(0x1, b"0123456789")[:1])            # フレームの頭の 1 バイトだけ
            with self.assertRaises(TimeoutError):
                ws.recv(0.05)
            b.sendall(server_frame(0x1, b"0123456789")[1:])
            self.assertEqual(ws.recv(2), "0123456789")
        finally:
            a.close()
            b.close()

    def serve_once(self, reply: bytes) -> tuple[int, list[bytes]]:
        srv = socket.socket()
        srv.bind(("127.0.0.1", 0))
        srv.listen(1)
        got: list[bytes] = []

        def run():
            c, _ = srv.accept()
            req = b""
            while b"\r\n\r\n" not in req:
                req += c.recv(4096)
            got.append(req)
            c.sendall(reply)
            threading.Event().wait(0.5)
            c.close()
            srv.close()
        threading.Thread(target=run, daemon=True).start()
        return srv.getsockname()[1], got

    def test_handshake_and_leftover(self):
        port, got = self.serve_once(b"HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n\r\n"
                                    + server_frame(0x1, b'{"id": 1}'))
        ws = rp.WebSocket(f"ws://127.0.0.1:{port}/devtools/page/X")
        self.assertEqual(ws.recv(2), '{"id": 1}')                       # 応答の頭と同じ塊で来たフレーム
        req = got[0].decode()
        self.assertTrue(req.startswith("GET /devtools/page/X HTTP/1.1\r\n"))
        self.assertIn("Upgrade: websocket", req)
        self.assertIn("Sec-WebSocket-Version: 13", req)
        ws.sock.close()

    def test_handshake_refused(self):
        port, _ = self.serve_once(b"HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n")
        with self.assertRaises(ConnectionError):
            rp.WebSocket(f"ws://127.0.0.1:{port}/x")


def write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


class SiteTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        t = Path(self.tmp.name)
        self.site, self.docs = t / "site", t / "docs"
        for p in ("", "graph/", "graph/bfs/", "index/graph/", "lists/kind-dp/", "assets/vendor/x/", "search/"):
            write(self.site / p / "index.html", f"<p>{p or 'top'}</p>")
        write(self.site / "404.html", "<p>404</p>")
        write(self.site / "img" / "a.svg", "<svg xmlns='http://www.w3.org/2000/svg'/>")
        locs = "".join(f"<url><loc>https://example.com/kp/{p}</loc></url>" for p in ("", "graph/", "graph/bfs/"))
        write(self.site / "sitemap.xml", f'<?xml version="1.0"?><urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">{locs}</urlset>')
        for p in ("index.md", "graph/index.md", "graph/bfs.md"):
            write(self.docs / p, "x")

    def tearDown(self):
        self.tmp.cleanup()

    def test_list_pages(self):
        pages = rp.list_pages(self.site, self.docs)
        self.assertEqual(sorted(p.path for p in pages),
                         sorted(["", "graph/", "graph/bfs/", "index/graph/", "lists/kind-dp/", "404.html"]))
        src = {p.path: p.source for p in pages}
        self.assertEqual(src[""], "docs/index.md")
        self.assertEqual(src["graph/"], "docs/graph/index.md")
        self.assertEqual(src["graph/bfs/"], "docs/graph/bfs.md")
        self.assertIsNone(src["lists/kind-dp/"])
        self.assertEqual([p.label for p in pages if p.path == ""], ["/（トップ）"])

    def test_select(self):
        pages = rp.list_pages(self.site, self.docs)

        def sel(ps=(), fs=()):
            return [p.path for p in rp.select_pages(pages, list(ps), list(fs))]
        self.assertEqual(len(sel()), 6)
        self.assertEqual(sel(["bfs"]), ["graph/bfs/"])                       # id
        self.assertEqual(sel(["graph/bfs"]), ["graph/bfs/"])                 # URL のパス
        self.assertEqual(sel(["docs/graph/bfs.md"]), ["graph/bfs/"])         # 元の Markdown
        self.assertEqual(sel(["graph"]), ["graph/"])                         # パスに合うものを id より先に
        self.assertEqual(sel(["index"]), [""])
        self.assertEqual(sel(["kind-dp", "404.html"]), ["lists/kind-dp/", "404.html"])
        self.assertEqual(sel(fs=["graph"]), ["graph/", "graph/bfs/"])
        self.assertEqual(sel(["kind-dp"], ["graph"]), ["graph/", "graph/bfs/", "lists/kind-dp/"])
        with self.assertRaises(SystemExit):
            sel(["nope"])
        with self.assertRaises(SystemExit):
            sel(fs=["nope"])

    def test_prefix(self):
        self.assertEqual(rp.site_prefix(self.site), "/kp/")
        (self.site / "sitemap.xml").unlink()
        self.assertEqual(rp.site_prefix(self.site), "/")

    def test_serve(self):
        server, base = rp.serve(self.site, "/kp/")
        try:
            self.assertTrue(base.endswith("/kp/"))
            port = server.server_address[1]

            def get(path):
                c = http.client.HTTPConnection("127.0.0.1", port, timeout=5)
                c.request("GET", path)
                r = c.getresponse()
                body = r.read()
                c.close()
                return r.status, r.getheader("Location"), r.getheader("Content-Type"), body
            self.assertEqual(get("/kp/graph/bfs/")[::3], (200, b"<p>graph/bfs/</p>"))
            status, loc, _, _ = get("/kp/graph/bfs")
            self.assertEqual((status, loc), (301, "/kp/graph/bfs/"))
            self.assertEqual(get("/kp/img/a.svg")[2], "image/svg+xml")
            self.assertEqual(get("/graph/bfs/")[0], 404)                     # パスの外
            self.assertEqual(get("/kp/none.png")[0], 404)
        finally:
            server.shutdown()
            server.server_close()


class ChangedTest(unittest.TestCase):
    """--changed：変わったファイルから描き直すページを選ぶ（changed_pages）と、git の差分の取り方（git_changed）。"""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        t = Path(self.tmp.name)
        self.site, self.docs = t / "site", t / "docs"
        md = {
            "index.md": "ホーム",
            "graph/index.md": "分野の入口",
            "graph/bfs.md": '<div class="kp-viz" data-viz="bfs-layers"></div>\n![図](../img/bfs/layers.svg)\n',
            "graph/dijkstra.md": '--8<-- "bfs/grid.cpp:core"\n<div class="kp-viz" data-viz="dijkstra"></div>\n',
            "guide/knowledge-map.md": '<div id="kp-map"></div>',
            "guide/roadmap.md": '<div class="kp-roadmap-stats"></div>',
            "guide/search.md": '<div class="kp-filter"></div>',
            "lists/kind-dp.md": "生成した一覧",
        }
        for p, text in md.items():
            write(self.docs / p, text)
            stem = p[:-3]
            stem = "" if stem == "index" else stem.removesuffix("/index") + "/"
            write(self.site / stem / "index.html", "<p>x</p>")
        write(self.site / "404.html", "<p>404</p>")
        self.pages = rp.list_pages(self.site, self.docs)

    def tearDown(self):
        self.tmp.cleanup()

    def pick(self, *files):
        return rp.changed_pages(list(files), self.pages, self.docs)

    def test_pages(self):
        self.assertEqual(self.pick("docs/graph/bfs.md"), (["graph/bfs/"], []))
        self.assertEqual(self.pick("docs/graph/index.md", "docs/lists/kind-dp.md"), (["graph/", "lists/kind-dp/"], []))
        self.assertEqual(self.pick("docs/graph/gone.md"), ([], []))                      # 消したページ
        self.assertEqual(self.pick("snippets/bfs/grid.cpp"), (["graph/bfs/", "graph/dijkstra/"], []))   # id と本文の --8<--
        self.assertEqual(self.pick("snippets/dijkstra/main.yaml"), (["graph/dijkstra/"], []))
        self.assertEqual(self.pick("docs/img/bfs/layers.svg"), (["graph/bfs/"], []))
        self.assertEqual(self.pick("overrides/assets/js/viz/dijkstra.js"), (["graph/dijkstra/"], []))
        self.assertEqual(self.pick("overrides/assets/js/map.js"), (["guide/knowledge-map/"], []))
        self.assertEqual(self.pick("overrides/assets/js/filter.js"), (["guide/knowledge-map/", "guide/search/"], []))
        self.assertEqual(self.pick("overrides/assets/data/graph.json"), (["guide/knowledge-map/", "guide/roadmap/"], []))
        self.assertEqual(self.pick("overrides/404.html"), (["404.html"], []))

    def test_ignored(self):
        self.assertEqual(self.pick("tools/check_pages.py", "tests/viz/dijkstra.test.mjs", "data/problems.yaml",
                                   "planning/progress.md", "docs/llms.txt", "snippets/README.md"), ([], []))

    def test_shared(self):
        everything = [p.path for p in self.pages]
        for f in ("mkdocs.yml", "nav.yml", "uv.lock", "overrides/main.html", "overrides/assets/css/kp.css",
                  "overrides/assets/js/viz.js", "overrides/assets/js/katex-init.js",
                  "overrides/assets/vendor/katex-0.16.47/katex.min.js", "docs/robots.txt"):
            self.assertEqual(self.pick("docs/graph/bfs.md", f), (everything, [f]), f)

    def test_git(self):
        top = Path(self.tmp.name) / "repo"
        top.mkdir()

        def git(*a):
            subprocess.run(["git", "-C", str(top), *a], check=True, capture_output=True)
        git("init", "-q", "-b", "main")
        git("config", "user.email", "t@example.com")
        git("config", "user.name", "t")
        for p in ("docs/a.md", "docs/b.md", "docs/c.md", "docs/e.md"):
            write(top / p, "x")
        git("add", ".")
        git("commit", "-q", "-m", "1")
        git("checkout", "-q", "-b", "topic")
        write(top / "docs/a.md", "y")                                   # コミットした変更
        git("commit", "-q", "-am", "2")
        git("checkout", "-q", "main")
        write(top / "docs/e.md", "main だけの変更")                       # 分かれ目より後の main の変更は入れない
        git("commit", "-q", "-am", "3")
        git("checkout", "-q", "topic")
        write(top / "docs/b.md", "z")                                   # コミットしていない変更
        write(top / "docs/new.md", "n")                                 # 追跡していないファイル
        git("mv", "docs/c.md", "docs/d.md")                             # 名前を変えたものは両方
        files, mb = rp.git_changed(top, "main")
        self.assertEqual(files, ["docs/a.md", "docs/b.md", "docs/c.md", "docs/d.md", "docs/new.md"])
        self.assertEqual(len(mb), 9)
        with self.assertRaises(SystemExit):
            rp.git_changed(top, "no-such-ref")


class CollectTest(unittest.TestCase):
    LIGHT, DARK = rp.Variant(390, "light"), rp.Variant(390, "dark")

    def test_merge_and_notes(self):
        err = {"h": "x", "where": "", "text": "\\frac{", "msg": "Expected 'EOF'"}
        page_a, page_b = rp.SitePage("a/", "docs/a.md"), rp.SitePage("b/")
        results = {
            "a/": [(self.LIGHT, {"items": {"katex-error": [dict(err)]}, "console": ["console.error: boom"],
                                 "scheme": "default", "counts": {"math": 3}}),
                   (self.DARK, {"items": {"katex-error": [dict(err)], "wide-math": [
                       {"h": "", "where": "折りたたみの中", "tex": "a+b", "width": 500, "box": 390, "hidden": 126}]},
                       "console": [], "scheme": "default", "counts": {"math": 3}})],
            "b/": [(self.LIGHT, {"failed": "TimeoutError: Chrome の答えが来ない"})],
        }
        findings, notes = rp.collect([page_a, page_b], results)
        kinds = [f.kind for f in findings]
        self.assertEqual(kinds, ["katex-error", "load-failed", "wide-math", "js-error"])   # KINDS の順
        k = findings[0]
        self.assertEqual(k.variants, ["390 ライト", "390 ダーク"])
        self.assertEqual(k.line(), "a/#x（docs/a.md）: \\frac{ — Expected 'EOF'［390 ライト・390 ダーク］")
        self.assertEqual(findings[2].line(),
                         "a/（docs/a.md）: 幅 500px・右の 126px が隠れる（入れ物 390px）: a+b（折りたたみの中）［390 ダーク］")
        self.assertEqual(len(notes), 1)                                      # ダークなのに default
        self.assertIn("slate", notes[0])
        s = rp.summarize(findings)
        self.assertEqual((s["katex-error"]["findings"], s["katex-error"]["pages"]), (1, 1))
        self.assertEqual(s["load-failed"]["severity"], "error")
        self.assertEqual(s["wide-math"]["severity"], "warning")
        self.assertEqual(rp.totals(results), {"math": 3})                    # 最初の回の数だけを足す

    def test_same_text_in_one_run(self):
        # 同じ回の中の、文が同じ別の要素（見出しの行と幅が同じ表が 2 つ）はまとめない。ほかの回とは同じ番目どうしでまとめる。
        # px の数が文に入るので、幅の違う回とはまとまらない
        table = {"h": "overview", "where": "", "head": "a | b | c | d", "width": 402, "box": 374, "hidden": 28, "cols": 4}
        narrow = dict(table, box=344, hidden=58)
        results = {"p/": [(self.LIGHT, {"items": {"wide-table": [dict(table), dict(table)]}}),
                          (self.DARK, {"items": {"wide-table": [dict(table), dict(table)]}}),
                          (rp.Variant(360, "light"), {"items": {"wide-table": [dict(narrow), dict(narrow)]}})]}
        findings, _ = rp.collect([rp.SitePage("p/", "docs/p.md")], results)
        self.assertEqual([f.variants for f in findings],
                         [["390 ライト", "390 ダーク"], ["390 ライト", "390 ダーク"], ["360 ライト"], ["360 ライト"]])
        self.assertEqual(findings[0].line(), findings[1].line())
        s = rp.summarize(findings)
        self.assertEqual((s["wide-table"]["findings"], s["wide-table"]["pages"]), (4, 1))

    def test_console_errors(self):
        base = "http://127.0.0.1:5555/kp/"
        events = [
            {"method": "Runtime.exceptionThrown", "params": {"exceptionDetails": {
                "text": "Uncaught", "url": base + "assets/js/x.js", "lineNumber": 4,
                "exception": {"description": "Error: boom\n    at f (x.js:5)"}}}},
            {"method": "Runtime.consoleAPICalled", "params": {"type": "error", "args": [{"type": "string", "value": "kyopro-atlas: x"}]}},
            {"method": "Runtime.consoleAPICalled", "params": {"type": "log", "args": [{"type": "string", "value": "ok"}]}},
            {"method": "Log.entryAdded", "params": {"entry": {"level": "error", "url": base + "img/a.svg",
                                                               "text": "Failed to load resource: 404"}}},
            {"method": "Log.entryAdded", "params": {"entry": {"level": "error", "url": base + "img/a.svg",
                                                               "text": "Failed to load resource: 404"}}},
            {"method": "Log.entryAdded", "params": {"entry": {"level": "error", "url": "https://api.github.com/repos/x",
                                                               "text": "Failed to load resource: 403"}}},
            {"method": "Log.entryAdded", "params": {"entry": {"level": "warning", "text": "deprecated"}}},
        ]
        self.assertEqual(rp.console_errors(events, base), [
            "例外: Error: boom（/assets/js/x.js:5）",
            "console.error: kyopro-atlas: x",
            "Failed to load resource: 404（/img/a.svg）",
        ])


class KatexColorTest(unittest.TestCase):
    def test_error_color(self):
        # 赤字の命令は KaTeX の errorColor の既定（#cc0000）で見つける。katex-init.js か同梱の KaTeX が変えたら
        # render_pages.KATEX_ERROR_COLOR も変える
        init = (ROOT / "overrides/assets/js/katex-init.js").read_text(encoding="utf-8")
        self.assertNotIn("errorColor", init)
        self.assertIn("throwOnError: false", init)
        katex = sorted((ROOT / "overrides/assets/vendor").glob("katex-*/katex.min.js"))
        self.assertTrue(katex)
        for k in katex:
            m = re.search(r'errorColor:\{[^}]*?default:"(#[0-9A-Fa-f]{3,6})"', k.read_text(encoding="utf-8"))
            self.assertIsNotNone(m, k)
            self.assertEqual(m.group(1).lower(), "#cc0000", k)
        self.assertEqual(rp.KATEX_ERROR_COLOR, "rgb(204, 0, 0)")


# 崩れを仕込んだページ。Material と KaTeX は使わず、描いた後の形（data-kp-rendered・.katex-html > .base・
# .md-typeset__scrollwrap・.kp-viz）を手で書く。配色は prefers-color-scheme から Material と同じ属性を付け、Material と同じく
# prefers-color-scheme が替わったら付け直す（render_pages は同じ幅のほかの配色を、読み込み直さずに調べる）
HEAD = """<!doctype html><html lang="ja"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<style>
body { margin: 0; font: 16px sans-serif; } .md-content { padding: 0 16px; }
div.arithmatex { overflow: auto; } .md-typeset__scrollwrap { overflow-x: auto; }
.katex-display { display: block; } .base { display: inline-block; white-space: nowrap; }
</style>
<script>const kpDark = matchMedia("(prefers-color-scheme: dark)");
const kpScheme = () => document.body.setAttribute("data-md-color-scheme", kpDark.matches ? "slate" : "default");
document.addEventListener("DOMContentLoaded", kpScheme);
kpDark.addEventListener("change", () => setTimeout(kpScheme, 100));</script>
</head><body><div class="md-content"><article>
"""
TAIL = "</article></div></body></html>\n"
WIDE = '<div class="arithmatex" data-kp-rendered="1"><span class="katex-display"><span class="katex"><span class="katex-html">' \
       '<span class="base" style="width:{w}px">{t}</span></span></span></span></div>'
# 描けたインラインの数式（annotation に TeX）。KaTeX は throwOnError: false のとき、描けない命令の名前だけを
# errorColor（#cc0000）で描く（.katex-error にならない。KaTeX 0.16.47 が \abs{x} を描いた形）
INLINE = '<span class="arithmatex" data-kp-rendered="1"><span class="katex"><span class="katex-mathml"><math><semantics>' \
         '<mrow></mrow><annotation encoding="application/x-tex">{tex}</annotation></semantics></math></span>' \
         '<span class="katex-html" aria-hidden="true"><span class="base">{html}</span></span></span></span>'
RED_ABS = '<span class="mord text" style="color:#cc0000;"><span class="mord" style="color:#cc0000;">\\abs</span></span>' \
          '<span class="mord"><span class="mord mathnormal">x</span></span>'
TABLE = '<div class="md-typeset__scrollwrap"><div class="md-typeset__table"><table><tr><th>列 1</th><th>列 2</th></tr>' \
        '<tr><td><div style="width:700px">x</div></td><td>y</td></tr></table></div></div>'
OK_PAGE = HEAD + """<h2 id="a">よいページ</h2><p>本文。<code>$x$</code> と <code>\\text</code> はコードの中なのでよい。</p>
<p>色を付けた数式 """ + INLINE.format(tex="\\color{red}{x}", html='<span class="mord" style="color:red;">x</span>') + \
    """ と、数式の外の <span style="color:#cc0000">赤い字</span> は KaTeX のエラーでない。</p>
""" + WIDE.format(w=200, t="fits") + """
<div class="md-typeset__scrollwrap"><div class="md-typeset__table"><table><tr><th>a</th><th>b</th></tr></table></div></div>
<img src="../img/ok.svg" alt="よい図">
""" + TAIL
BAD_PAGE = HEAD + """<h2 id="math">数式</h2>
<p><span class="arithmatex" data-kp-rendered="1"><span class="katex-error" title="ParseError: KaTeX parse error: Expected 'EOF', got '}'">\\frac{</span></span></p>
<p>絶対値 """ + INLINE.format(tex="\\abs{x}", html=RED_ABS) + """ と書いた</p>
<p><span class="arithmatex">\\(x\\)</span></p>
<p>たとえば $S = $ ab のとき</p>
""" + WIDE.format(w=800, t="wide") + """
<h2 id="wide">はみ出し</h2>
<p>abc <span id="long" style="display:inline-block;width:600px">long</span></p>
""" + TABLE + TABLE + """
<details><summary>開く</summary>""" + WIDE.format(w=900, t="hidden") + """</details>
<h2 id="viz">図</h2>
<div class="kp-viz" data-viz="nope"><p class="kp-viz__error">図を表示できなかった：図のスクリプトを読み込めない：nope</p></div>
<div class="kp-viz" data-viz="steps" id="steps"><svg class="kp-viz__svg"></svg><p class="kp-viz__caption"></p></div>
<div class="kp-viz" data-viz="never"></div>
<img src="../img/missing.svg" alt="ない図">
<img src="../img/gap.svg" alt="帯のある図">
<pre class="mermaid"><code>graph LR; a--&gt;b</code></pre>
<script>
const v = document.getElementById("steps"), cap = v.querySelector(".kp-viz__caption");
v.kpViz = { states: [1, 2, 3], go: (i) => { cap.textContent = i === 2 ? "図を描けなかった：bad" : "ステップ " + i; } };
console.error("boom");
</script>
""" + TAIL
SVG = '<svg xmlns="http://www.w3.org/2000/svg" width="40" height="20" viewBox="0 0 40 20">' \
      '<rect x="0" y="0" width="40" height="{h}" fill="#ffffff"/><text x="2" y="12" font-size="10">a</text></svg>'


@unittest.skipUnless(CHROME, "Chrome がない（render_svg.py の探し方。環境変数 CHROME）か、CI で走らせている")
class ChromeTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory()
        t = Path(cls.tmp.name)
        site = t / "site"
        write(site / "index.html", HEAD + "<h1 id='top'>トップ</h1>" + TAIL)
        write(site / "ok" / "index.html", OK_PAGE)
        write(site / "bad" / "index.html", BAD_PAGE)
        write(site / "img" / "ok.svg", SVG.format(h=20))
        write(site / "img" / "gap.svg", SVG.format(h=13))                # 下の 7px が透ける
        locs = "".join(f"<url><loc>https://example.com/demo/{p}</loc></url>" for p in ("", "ok/", "bad/"))
        write(site / "sitemap.xml", f'<?xml version="1.0"?><urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">{locs}</urlset>')
        cls.pages = rp.list_pages(site)
        variants = [rp.Variant(390, "light"), rp.Variant(390, "dark")]
        with mock.patch.object(rp, "WAIT_MS", 500), mock.patch.object(rp, "WAIT_MERMAID_MS", 500):
            cls.results = rp.run(site, cls.pages, variants, CHROME, 2, 20.0, t, None)
        cls.findings, cls.notes = rp.collect(cls.pages, cls.results)

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def of(self, page: str, kind: str) -> list[rp.Finding]:
        return [f for f in self.findings if f.page.path == page and f.kind == kind]

    def test_clean_pages(self):
        self.assertEqual([f.line() for f in self.findings if f.page.path in ("", "ok/")], [])
        self.assertEqual(self.notes, [])
        for v, res in self.results["ok/"]:
            self.assertEqual(res["scheme"], rp.SCHEME_ATTR[v.scheme])         # 配色が切り替わる
            self.assertEqual((res["vw"], res["sw"]), (390, 390))
            self.assertEqual(res["counts"]["img"], 1)

    def test_every_kind_on_bad_page(self):
        found = {f.kind for f in self.findings if f.page.path == "bad/"}
        self.assertEqual(found, set(rp.KINDS) - {"load-failed"})
        for f in self.findings:
            if f.page.path == "bad/":
                self.assertEqual(f.variants, ["390 ライト", "390 ダーク"], f.line())

    def test_details(self):
        ke = sorted(self.of("bad/", "katex-error"), key=lambda f: f.data["text"])
        self.assertEqual([(f.heading, f.data["text"]) for f in ke], [("math", "\\abs{x}"), ("math", "\\frac{")])
        self.assertEqual(ke[0].data["red"], ["\\abs"])                     # 赤字の命令（.katex-error にならない）
        self.assertIn("赤字の命令 \\abs", ke[0].detail)
        self.assertIn("Expected 'EOF'", ke[1].data["msg"])
        (mu,) = self.of("bad/", "math-unrendered")
        self.assertFalse(mu.data["katex"])
        (lm,) = self.of("bad/", "leaked-markup")
        self.assertEqual(lm.data["mark"], "$")
        wide = sorted(self.of("bad/", "wide-math"), key=lambda f: f.data["width"])
        self.assertEqual([(f.data["width"], f.where) for f in wide], [(800, ""), (900, "折りたたみの中")])
        (po,) = self.of("bad/", "page-overflow")
        self.assertIn("#long", po.data["what"])
        self.assertGreater(po.data["over"], 200)
        wt = self.of("bad/", "wide-table")                                  # 見出しの行と幅が同じ表が 2 つ。まとめない
        self.assertEqual([(f.heading, f.data["cols"], f.data["head"]) for f in wt], [("wide", 2, "列 1 | 列 2")] * 2)
        self.assertEqual(wt[0].line(), wt[1].line())
        errs = sorted((f.data["viz"], f.data.get("step")) for f in self.of("bad/", "viz-error"))
        self.assertEqual(errs, [("nope", None), ("steps", 3)])
        (vu,) = self.of("bad/", "viz-unrendered")
        self.assertEqual(vu.data["viz"], "never")
        (ib,) = self.of("bad/", "img-broken")
        self.assertEqual(ib.data["src"], "../img/missing.svg")
        (it,) = self.of("bad/", "img-transparent")
        self.assertEqual((it.data["src"], it.data["sides"]), ("../img/gap.svg", {"下": 7}))
        js = [f.detail for f in self.of("bad/", "js-error")]
        self.assertIn("console.error: boom", js)
        self.assertTrue(any("/img/missing.svg" in x and "127.0.0.1" not in x for x in js), js)


if __name__ == "__main__":
    unittest.main()
