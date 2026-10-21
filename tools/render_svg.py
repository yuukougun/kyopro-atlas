#!/usr/bin/env python3
"""図の SVG（docs/img/<page-id>/*.svg）を、手元のヘッドレスの Chrome で PNG にして目で確かめる（決定 b1 D4）。

本文の画像は本文の幅に合わせて縮むので、狭い幅（既定 360px＝スマートフォン）と通常の幅（既定 720px）の2枚を出す。
各幅では、SVG を <img style="max-width:100%"> で置いた（サイトと同じ縮み方の）ページを撮る。

使い方:
  python3 tools/render_svg.py tree-diameter                ページの id（docs/img/<id>/ のすべての SVG）
  python3 tools/render_svg.py docs/img/bfs/layers.svg      SVG のファイル・フォルダ（くり返し可）
  python3 tools/render_svg.py bfs --out /tmp/png           出力先（既定は新しい一時ディレクトリ。最後に場所を出す）
  python3 tools/render_svg.py bfs --width 360 --width 1000 幅（px。くり返し・カンマ区切り可。既定 360,720）
  python3 tools/render_svg.py bfs --scale 2                画素の倍率（既定 1。細部を見るなら 2）
  python3 tools/render_svg.py bfs --bg '#1e2129'           周りの色（既定 白。ダークモードの背景で縁を見るとき）
  python3 tools/render_svg.py bfs --chrome PATH            Chrome の場所（既定は ~/.cache/puppeteer/ の chrome-headless-shell、
                                                           なければ chrome、環境変数 CHROME）
出力: <out>/<page-id>/<name>-<幅>.png。終了コード: 撮れないものがあれば 1
日本語のフォントが fontconfig にないと文字が豆腐（□）になる。WSL で /mnt/c/Windows/Fonts があればそこを足して撮る。
どちらもなければ注意を出す（fonts-noto-cjk などを入れる）。
Chrome がないときは `npx @puppeteer/browsers install chrome-headless-shell@stable --path ~/.cache/puppeteer` で取れる。
"""
from __future__ import annotations

import argparse
import html
import os
import re
import shutil
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IMG = ROOT / "docs" / "img"
PAD = 8          # 周りの余白（px）
INSTALL_HINT = ("ヘッドレスの Chrome が見つからない。次のどれかで用意する:\n"
                "  npx @puppeteer/browsers install chrome-headless-shell@stable --path ~/.cache/puppeteer\n"
                "  npx puppeteer browsers install chrome-headless-shell\n"
                "または --chrome か環境変数 CHROME で場所を渡す")


def find_chrome(given: str | None) -> Path | None:
    for c in (given, os.environ.get("CHROME")):
        if c:
            p = Path(c).expanduser()
            if p.is_file() and os.access(p, os.X_OK):
                return p
            w = shutil.which(c)
            return Path(w) if w else None
    cache = Path.home() / ".cache" / "puppeteer"
    for pattern in ("chrome-headless-shell/*/*/chrome-headless-shell", "chrome/*/*/chrome"):
        found = sorted((p for p in cache.glob(pattern) if p.is_file() and os.access(p, os.X_OK)),
                       key=lambda p: [int(x) if x.isdigit() else 0 for x in re.split(r"[.-]", p.parent.parent.name)])
        if found:
            return found[-1]                       # 新しい版
    for name in ("chrome-headless-shell", "google-chrome", "chromium", "chromium-browser"):
        w = shutil.which(name)
        if w:
            return Path(w)
    return None


WIN_FONTS = Path("/mnt/c/Windows/Fonts")
FC_CACHE = Path.home() / ".cache" / "kyopro-atlas-fontconfig"   # Windows のフォントの索引（2回目から速い）


def font_env(work: Path) -> tuple[dict[str, str] | None, str | None]:
    """日本語のフォントがなければ、WSL の Windows のフォントを足した fontconfig の設定を作る。(環境, 注意) を返す。"""
    try:
        r = subprocess.run(["fc-list", ":lang=ja"], capture_output=True, text=True, timeout=30)
        if r.stdout.strip():
            return None, None
    except (OSError, subprocess.TimeoutExpired):
        pass
    if WIN_FONTS.is_dir():
        conf = work / "fonts.conf"
        conf.write_text(
            "<?xml version='1.0'?><!DOCTYPE fontconfig SYSTEM 'fonts.dtd'><fontconfig>"
            "<include ignore_missing='yes'>/etc/fonts/fonts.conf</include>"
            f"<dir>{html.escape(str(WIN_FONTS))}</dir><cachedir>{html.escape(str(FC_CACHE))}</cachedir>"
            "</fontconfig>", encoding="utf-8")
        return {**os.environ, "FONTCONFIG_FILE": str(conf)}, f"日本語のフォントがないので {WIN_FONTS} を足して撮る"
    return None, "注意: 日本語のフォントが見つからない。日本語は豆腐（□）になる（fonts-noto-cjk などを入れる）"


def _num(v: str | None) -> float | None:
    m = re.match(r"\s*([0-9.]+)\s*(px)?\s*$", v or "")
    return float(m.group(1)) if m else None


def svg_size(path: Path) -> tuple[float, float]:
    """SVG の固有の大きさ（width・height、なければ viewBox）。"""
    root = ET.parse(path).getroot()
    w, h = _num(root.get("width")), _num(root.get("height"))
    vb = root.get("viewBox")
    if vb:
        parts = [float(x) for x in re.split(r"[\s,]+", vb.strip())]
        if len(parts) == 4 and parts[2] > 0 and parts[3] > 0:
            if w and not h:
                h = w * parts[3] / parts[2]
            elif h and not w:
                w = h * parts[2] / parts[3]
            elif not w and not h:
                w, h = parts[2], parts[3]
    if not (w and h):
        raise ValueError("width・height か viewBox が読めない")
    return w, h


def collect(targets: list[str]) -> list[Path]:
    out: list[Path] = []
    for t in targets:
        p = Path(t).expanduser()
        if not p.exists() and (IMG / t).is_dir():
            p = IMG / t
        if p.is_dir():
            out += sorted(p.rglob("*.svg"))
        elif p.is_file() and p.suffix == ".svg":
            out.append(p)
        else:
            sys.exit(f"{t} がない（ページの id・SVG のファイル・フォルダ）")
    return [p.resolve() for p in dict.fromkeys(out)]


def render(chrome: Path, svg: Path, width: int, scale: float, bg: str, out_png: Path, work: Path,
           env: dict[str, str] | None = None) -> str | None:
    """撮れなければ理由を返す。"""
    try:
        sw, sh = svg_size(svg)
    except (ET.ParseError, ValueError) as e:
        return f"SVG が読めない: {e}"
    shown_w = min(sw, width - 2 * PAD)             # max-width:100% で縮む
    height = int(round(shown_w * sh / sw)) + 2 * PAD
    page = work / f"{out_png.stem}.html"
    page.write_text(
        "<!doctype html><meta charset='utf-8'>"
        f"<style>html,body{{margin:0;background:{html.escape(bg)}}}body{{padding:{PAD}px}}"
        "img{display:block;max-width:100%;height:auto}</style>"
        f"<img src='{svg.as_uri()}'>", encoding="utf-8")
    cmd = [str(chrome), "--headless", "--disable-gpu", "--no-sandbox", "--hide-scrollbars", "--no-first-run",
           "--allow-file-access-from-files", f"--force-device-scale-factor={scale:g}",
           f"--window-size={width},{height}", f"--screenshot={out_png}", page.as_uri()]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=60, env=env)
    except subprocess.TimeoutExpired:
        return "Chrome が 60 秒で終わらない"
    if r.returncode != 0 or not out_png.is_file():
        tail = [x for x in r.stderr.strip().split("\n") if x][-3:]
        return f"Chrome が失敗した（終了コード {r.returncode}）" + ("\n      " + "\n      ".join(tail) if tail else "")
    return None


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("targets", nargs="+", help="ページの id・SVG のファイル・フォルダ")
    parser.add_argument("--out", type=Path, help="出力先（既定は新しい一時ディレクトリ）")
    parser.add_argument("--width", action="append", default=[], help="幅（px。くり返し・カンマ区切り可。既定 360,720）")
    parser.add_argument("--scale", type=float, default=1.0, help="画素の倍率（既定 1）")
    parser.add_argument("--bg", default="#ffffff", help="周りの色（既定 #ffffff）")
    parser.add_argument("--chrome", help="Chrome の実行ファイル")
    args = parser.parse_args()

    try:
        widths = [int(x) for v in (args.width or ["360,720"]) for x in v.split(",") if x.strip()]
    except ValueError:
        sys.exit("--width は整数（px）")
    if not widths or min(widths) <= 2 * PAD:
        sys.exit(f"--width は {2 * PAD + 1} 以上")
    svgs = collect(args.targets)
    if not svgs:
        sys.exit("SVG がない")
    chrome = find_chrome(args.chrome)
    if chrome is None:
        sys.exit(INSTALL_HINT)
    out = (args.out.expanduser() if args.out else Path(tempfile.mkdtemp(prefix="kp-svg-"))).resolve()
    out.mkdir(parents=True, exist_ok=True)

    bad = 0
    with tempfile.TemporaryDirectory(prefix="kp-svg-html-") as tmp:
        env, note = font_env(Path(tmp))
        if note:
            print(note)
        for svg in svgs:
            sub = svg.parent.name if svg.parent != IMG else "_"
            (out / sub).mkdir(exist_ok=True)
            for w in widths:
                png = out / sub / f"{svg.stem}-{w}.png"
                err = render(chrome, svg, w, args.scale, args.bg, png, Path(tmp), env)
                rel = svg.relative_to(ROOT) if ROOT in svg.parents else svg
                if err:
                    bad += 1
                    print(f"NG  {rel}（幅 {w}）: {err}")
                else:
                    print(f"OK  {rel}（幅 {w}）→ {png}")
    print(f"\nSVG {len(svgs)}・PNG {len(svgs) * len(widths) - bad}・失敗 {bad}（Chrome {chrome}）\n出力先: {out}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
