#!/usr/bin/env python3
"""URL を取得して、robots の meta と X-Robots-Tag に noai・noimageai（AI の利用を断る指定）があるかを出す
（design-review T20、設計書 §6.7）。新しいドメインを資料にする前に実行し、結果を style-guide のドメインの記録に足す。

使い方:
  python3 tools/check_noai.py URL [URL ...]       各 URL を取得して、noai・noimageai の有無を出す
  python3 tools/check_noai.py --robots URL ...    加えて robots.txt の AI 向けのクローラ（GPTBot・ClaudeBot など）への指定も出す
  python3 tools/check_noai.py --json URL ...      結果を JSON で出す
atcoder.jp・codeforces.com（とそのサブドメイン）は取得せず「既知の noai」と出す（AI で開かない。CLAUDE.md）。
転送（リダイレクト）の先がこれらのドメインなら、転送をたどらない。
終了コード: 0＝どの URL にも noai・noimageai がない、1＝ある URL がある（既知の noai を含む）、
           2＝取得できない URL がある（noai のある URL がなければ）

見るもの:
  X-Robots-Tag  レスポンスのヘッダー（「googlebot: noai」のようにクローラを指定したものも数え、そのクローラを添える）
  meta          <meta name="robots" content="…"> と、クローラの名前の meta（googlebot・gptbot・ccbot・claudebot など）
  参考          tdm-reservation（EU の TDM のオプトアウト。ヘッダーと meta）。noai の判定には入れない
標準ライブラリだけで動く。取得は1つの URL に1回（--robots のときは robots.txt も1回）。
"""
from __future__ import annotations

import argparse
import html.parser
import json
import re
import sys
import urllib.error
import urllib.parse
import urllib.request

USER_AGENT = "kyopro-atlas-noai-check (+https://github.com/yuukougun/kyopro-atlas)"
KNOWN_NOAI = {
    "atcoder.jp": "問題・解説ページに <meta name=\"robots\" content=\"noai, noimageai\">（decisions.md 2026-10-21）",
    "codeforces.com": "ページに <meta name=\"robots\" content=\"noai\"> と noimageai（decisions.md 2026-10-21）",
}
FLAGS = ("noai", "noimageai")
BOT_METAS = {"robots", "googlebot", "google-extended", "bingbot", "gptbot", "chatgpt-user", "ccbot", "claudebot",
             "claude-web", "anthropic-ai", "perplexitybot", "applebot-extended", "bytespider"}
AI_AGENTS = ["GPTBot", "ChatGPT-User", "ClaudeBot", "Claude-Web", "anthropic-ai", "Google-Extended", "CCBot",
             "PerplexityBot", "Applebot-Extended", "Bytespider"]
MAX_BYTES = 3 * 1024 * 1024


def known_noai(url: str) -> str | None:
    host = (urllib.parse.urlsplit(url).hostname or "").lower().rstrip(".")
    for d, note in KNOWN_NOAI.items():
        if host == d or host.endswith("." + d):
            return f"{d}：{note}"
    return None


class NoKnownRedirect(urllib.request.HTTPRedirectHandler):
    def redirect_request(self, req, fp, code, msg, headers, newurl):  # noqa: ANN001
        if known_noai(newurl):
            raise urllib.error.URLError(f"既知の noai のドメインへの転送なので、たどらない: {newurl}")
        return super().redirect_request(req, fp, code, msg, headers, newurl)


OPENER = urllib.request.build_opener(NoKnownRedirect)


class MetaParser(html.parser.HTMLParser):
    def __init__(self) -> None:
        super().__init__(convert_charrefs=True)
        self.metas: list[tuple[str, str]] = []

    def handle_starttag(self, tag, attrs):  # noqa: ANN001
        if tag.lower() != "meta":
            return
        a = {k.lower(): (v or "") for k, v in attrs}
        name = (a.get("name") or a.get("http-equiv") or "").strip().lower()
        if name in BOT_METAS or name in ("tdm-reservation", "tdm-policy", "x-robots-tag"):
            self.metas.append((name, a.get("content", "").strip()))


def tokens(value: str) -> tuple[str | None, set[str]]:
    """「googlebot: noai, noimageai」→ ("googlebot", {"noai", "noimageai"})。"""
    bot = None
    m = re.match(r"\s*([A-Za-z0-9_-]+)\s*:\s*(.*)$", value)
    if m and m.group(1).lower() not in ("noai", "noimageai", "noindex", "nofollow", "none", "all"):
        bot, value = m.group(1), m.group(2)
    return bot, {t.strip().lower() for t in re.split(r"[,\s]+", value) if t.strip()}


def fetch(url: str) -> tuple[int, str, dict[str, list[str]], bytes]:
    req = urllib.request.Request(url, headers={"User-Agent": USER_AGENT, "Accept": "text/html,*/*;q=0.5"})
    try:
        res = OPENER.open(req, timeout=20)
    except urllib.error.HTTPError as e:      # 404 などでもヘッダーと本文は読む
        res = e
    with res:
        body = res.read(MAX_BYTES)
        headers: dict[str, list[str]] = {}
        for k, v in res.headers.items():
            headers.setdefault(k.lower(), []).append(v)
        return res.status if hasattr(res, "status") else res.code, res.geturl(), headers, body


def decode(body: bytes, headers: dict[str, list[str]]) -> str:
    ctype = ";".join(headers.get("content-type", []))
    m = re.search(r"charset=([\w-]+)", ctype, re.I) or re.search(rb"<meta[^>]+charset=[\"']?([\w-]+)", body[:4096], re.I)
    enc = m.group(1) if m else "utf-8"
    enc = enc.decode("ascii", "replace") if isinstance(enc, bytes) else enc
    try:
        return body.decode(enc, errors="replace")
    except LookupError:
        return body.decode("utf-8", errors="replace")


def robots_txt(url: str) -> dict:
    parts = urllib.parse.urlsplit(url)
    rurl = f"{parts.scheme}://{parts.netloc}/robots.txt"
    try:
        status, _, headers, body = fetch(rurl)
    except Exception as e:  # noqa: BLE001
        return {"url": rurl, "error": str(e)}
    if status >= 400:
        return {"url": rurl, "status": status, "agents": {}}
    groups: list[tuple[list[str], list[str]]] = []
    agents: list[str] = []
    rules: list[str] = []
    for raw in decode(body, headers).splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line or ":" not in line:
            continue
        k, v = (x.strip() for x in line.split(":", 1))
        if k.lower() == "user-agent":
            if rules:
                groups.append((agents, rules))
                agents, rules = [], []
            agents.append(v)
        elif k.lower() in ("disallow", "allow") and agents:
            rules.append(f"{k.capitalize()}: {v}")
    if agents:
        groups.append((agents, rules))
    out = {}
    for name in AI_AGENTS + ["*"]:
        hit = [r for ags, rs in groups if any(a.lower() == name.lower() for a in ags) for r in rs]
        if hit:
            out[name] = hit
    return {"url": rurl, "status": status, "agents": out}


def check(url: str, with_robots: bool) -> dict:
    r: dict = {"url": url}
    note = known_noai(url)
    if note:
        r.update(known=note, noai=True, flags=list(FLAGS))
        return r
    try:
        status, final, headers, body = fetch(url)
    except Exception as e:  # noqa: BLE001
        reason = str(getattr(e, "reason", e))
        if reason.startswith("既知の noai"):
            target = reason.rsplit(": ", 1)[-1]
            r.update(known=f"{known_noai(target)}（{target} へ転送される）", noai=True, flags=list(FLAGS))
        else:
            r.update(error=reason, noai=None)
        return r
    r.update(status=status, final_url=final)
    found: list[str] = []
    xrt = headers.get("x-robots-tag", [])
    for v in xrt:
        bot, toks = tokens(v)
        found += [f"{f}（X-Robots-Tag{'・' + bot if bot else ''}）" for f in FLAGS if f in toks]
    p = MetaParser()
    try:
        p.feed(decode(body, headers))
    except Exception:  # noqa: BLE001  壊れた HTML でも、読めたところまでで判定する
        pass
    for name, content in p.metas:
        if name in BOT_METAS or name == "x-robots-tag":
            bot, toks = tokens(content)
            found += [f"{f}（meta {name}{'・' + bot if bot else ''}）" for f in FLAGS if f in toks]
    r.update(x_robots_tag=xrt, metas=[{"name": n, "content": c} for n, c in p.metas],
             tdm=[f"header: {v}" for v in headers.get("tdm-reservation", [])] + [f"meta {n}: {c}" for n, c in p.metas if n.startswith("tdm")],
             found=found, noai=bool(found))
    if with_robots:
        r["robots_txt"] = robots_txt(final or url)
    return r


def show(r: dict) -> None:
    print(r["url"])
    if r.get("known"):
        print(f"  既知の noai（取得しない）: {r['known']}")
        print("  判定: noai あり（資料にしない・AI で開かない）")
        return
    if r.get("error"):
        print(f"  取得できない: {r['error']}")
        return
    final = f"（転送後 {r['final_url']}）" if r.get("final_url") and r["final_url"] != r["url"] else ""
    print(f"  取得: HTTP {r['status']}{final}")
    print(f"  X-Robots-Tag: {'、'.join(r['x_robots_tag']) or 'なし'}")
    metas = [f"{m['name']}=\"{m['content']}\"" for m in r["metas"] if not m["name"].startswith("tdm")]
    print(f"  meta: {'、'.join(metas) or 'なし（robots・クローラの名前の meta がない）'}")
    if r["tdm"]:
        print(f"  参考（TDM のオプトアウト）: {'、'.join(r['tdm'])}")
    if "robots_txt" in r:
        rt = r["robots_txt"]
        if rt.get("error"):
            print(f"  robots.txt: 取得できない（{rt['error']}）")
        elif rt.get("status", 200) >= 400:
            print(f"  robots.txt: HTTP {rt['status']}（ない）")
        else:
            ai = {k: v for k, v in rt["agents"].items() if k != "*"}
            print("  robots.txt の AI 向けの指定: " + ("なし" if not ai else "；".join(f"{k}: {', '.join(v)}" for k, v in ai.items())))
            if "*" in rt["agents"]:
                print("  robots.txt の * への指定: " + ", ".join(rt["agents"]["*"][:6]) + ("…" if len(rt["agents"]["*"]) > 6 else ""))
    print("  判定: " + ("noai あり: " + "、".join(r["found"]) + "（資料にしない）" if r["noai"] else "noai・noimageai の指定はない"))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("urls", nargs="+", help="確かめる URL")
    parser.add_argument("--robots", action="store_true", help="robots.txt の AI 向けのクローラへの指定も出す")
    parser.add_argument("--json", action="store_true", help="結果を JSON で出す")
    args = parser.parse_args()
    results = []
    for url in args.urls:
        if not re.match(r"https?://", url):
            url = "https://" + url
        results.append(check(url, args.robots))
    if args.json:
        print(json.dumps(results, ensure_ascii=False, indent=1))
    else:
        for r in results:
            show(r)
    if any(r.get("noai") for r in results):
        sys.exit(1)
    if any(r.get("error") for r in results):
        sys.exit(2)


if __name__ == "__main__":
    main()
