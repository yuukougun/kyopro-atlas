#!/usr/bin/env python3
"""図の SVG（docs/img/**/*.svg）の大きさと文字の大きさを機械的に調べる（手引き §8・§15-8。工程10 の洗い出し s10）。

使い方:
  python3 tools/check_svg.py                    全部の図を調べ、警告を出す
  python3 tools/check_svg.py --page union-find  そのページの図（docs/img/<id>/）だけ（くり返し・カンマ区切り可）
  python3 tools/check_svg.py docs/img/x/a.svg   その図だけ
  python3 tools/check_svg.py --strict           警告があれば終了コード 1（既定は 0。読めない SVG だけ 1）

見るもの（どれも警告）:
  width・height がない        §8「viewBox と、それと同じ比の width・height を付ける」
  width:height が viewBox と違う
  幅が 450 を超える           §15-8「幅 400 程度まで」の目安から大きく外れる
  文字が小さい                スマホの本文の幅（328px）で表示したときに 9px 未満になる文字
                              （倍率 = min(width, 328) / viewBox の幅、文字 = font-size × 倍率。上付き・下付きの tspan は除く）
標準ライブラリだけで動く。
"""
from __future__ import annotations

import argparse
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IMG = ROOT / "docs" / "img"
AVAIL = 328.0       # スマホ（360px）で本文に使える幅
MIN_TEXT = 9.0      # 表示したときの文字の大きさの下限（px）
MAX_WIDTH = 450.0   # §15-8 の目安（400 程度）から大きく外れる幅
NS = "{http://www.w3.org/2000/svg}"


def num(s: str | None) -> float | None:
    if s is None:
        return None
    m = re.match(r"\s*([0-9.]+)\s*(px)?\s*$", s)
    return float(m.group(1)) if m else None


def font_size(el: ET.Element, parent: float) -> float:
    v = el.get("font-size")
    m = re.search(r"font-size\s*:\s*([^;]+)", el.get("style") or "")
    if m:
        v = m.group(1)
    if v is None:
        return parent
    v = v.strip()
    try:
        if v.endswith("em"):
            return parent * float(v[:-2])
        if v.endswith("%"):
            return parent * float(v[:-1]) / 100
    except ValueError:
        return parent
    n = num(v)
    return n if n else parent


def texts(el: ET.Element, fs: float, scale: float, out: list[tuple[float, str]]) -> None:
    fs = font_size(el, fs)
    m = re.search(r"scale\(\s*([0-9.]+)", el.get("transform") or "")
    if m:
        scale *= float(m.group(1))
    tag = el.tag.replace(NS, "")
    if tag in ("text", "tspan"):
        own = (el.text or "").strip()
        fsa = el.get("font-size") or ""
        sub = tag == "tspan" and (el.get("baseline-shift") or fsa.endswith("em"))
        if own and not sub:
            out.append((fs * scale, own[:30]))
    for c in el:
        texts(c, fs, scale, out)


def check(path: Path) -> tuple[list[str], str | None]:
    """(警告の一覧, 読めないときの理由)。"""
    try:
        root = ET.parse(path).getroot()
    except ET.ParseError as e:
        return [], f"SVG として読めない: {e}"
    warns = []
    vb = root.get("viewBox")
    w, h = num(root.get("width")), num(root.get("height"))
    vbw = vbh = None
    if vb:
        try:
            a = [float(x) for x in re.split(r"[ ,]+", vb.strip())]
            vbw, vbh = a[2], a[3]
        except (ValueError, IndexError):
            warns.append(f"viewBox が読めない: {vb}")
    else:
        warns.append("viewBox がない")
    if root.get("width") is None or root.get("height") is None:
        warns.append("width・height がない（viewBox と同じ比で付ける。§8）")
    elif w and h and vbw and vbh and abs(w / h - vbw / vbh) > 0.01 * vbw / vbh:
        warns.append(f"width:height（{w:g}:{h:g}）が viewBox（{vbw:g}:{vbh:g}）と比が違う")
    width = w or vbw
    if width and width > MAX_WIDTH:
        warns.append(f"幅 {width:g} が §15-8 の目安（400 程度）を超える")
    base = vbw or w
    if base:
        shown = min(w, AVAIL) if w else AVAIL
        sc = shown / base
        out: list[tuple[float, str]] = []
        texts(root, 16.0, 1.0, out)
        small = [(f * sc, t) for f, t in out if f * sc < MIN_TEXT]
        if small:
            mn = min(e for e, _ in small)
            ex = "・".join(t for _, t in small[:3])
            warns.append(f"幅 {AVAIL:g}px で {MIN_TEXT:g}px 未満の文字が {len(small)} 個（最小 {mn:.1f}px。例：{ex}）")
    return warns, None


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("files", nargs="*", type=Path, help="調べる SVG（なければ docs/img の全部）")
    parser.add_argument("--page", action="append", default=[], help="そのページの図だけ（id。くり返し・カンマ区切り可）")
    parser.add_argument("--strict", action="store_true", help="警告があれば終了コード 1")
    args = parser.parse_args()

    if args.files:
        targets = [p.resolve() for p in args.files]
    else:
        ids = [x.strip() for v in args.page for x in v.split(",") if x.strip()]
        dirs = [IMG / i for i in ids] if ids else [IMG]
        targets = sorted(p for d in dirs for p in d.rglob("*.svg"))
    n_warn = n_files = 0
    errors = []
    for p in targets:
        warns, err = check(p)
        rel = p.relative_to(ROOT) if p.is_relative_to(ROOT) else p
        if err:
            errors.append(f"{rel}: {err}")
            continue
        if warns:
            n_files += 1
            n_warn += len(warns)
            for w in warns:
                print(f"警告: {rel}: {w}")
    for e in errors:
        print("エラー: " + e)
    print(f"\n図 {len(targets)} 枚・警告 {n_warn} 件（{n_files} 枚）・エラー {len(errors)} 件")
    sys.exit(1 if errors or (args.strict and n_warn) else 0)


if __name__ == "__main__":
    main()
