#!/usr/bin/env python3
"""AtCoder Problems の公開データで、問題の実在・タイトル・difficulty を確認する。

AtCoder 本体（atcoder.jp）のページは取得しない。問題ページと解説ページには
noai 指定があるため、問題の情報は AtCoder Problems（非公式 API）の静的 JSON から得る。

使い方:
  python3 tools/ap.py fetch [--force]          データを取得してキャッシュする（.cache/ 以下）
  python3 tools/ap.py show ID [ID ...]         問題の情報を表示する。見つからない ID があれば終了コード 1
  python3 tools/ap.py search 語 [--prefix abc] [--min 1200] [--max 1599] [--limit 50]
  python3 tools/ap.py contest CONTEST_ID       コンテストの問題一覧
  show / search / contest は --json で JSON を出力する

difficulty は AtCoder Problems の表示と同じ補正をかけた値（400 未満を正の値に写したもの）。
レベルは planning/decisions.md の定義（基礎 〜1199／水／青／黄／発展 2400〜）。
"""
from __future__ import annotations

import argparse
import datetime
import gzip
import json
import math
import sys
import time
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CACHE = ROOT / ".cache" / "atcoder-problems"
BASE = "https://kenkoooo.com/atcoder/resources/"
RESOURCES = {
    "problems": "problems.json",
    "models": "problem-models.json",
    "contests": "contests.json",
    "contest_problem": "contest-problem.json",
}
USER_AGENT = "kyopro-atlas (+https://github.com/yuukougun/kyopro-atlas)"
INTERVAL_SEC = 1.5  # API の利用方針：アクセスの間隔は1秒以上空ける

COLORS = [(400, "灰"), (800, "茶"), (1200, "緑"), (1600, "水"), (2000, "青"), (2400, "黄"), (2800, "橙")]
LEVELS = [(1200, "基礎"), (1600, "水"), (2000, "青"), (2400, "黄")]
JST = datetime.timezone(datetime.timedelta(hours=9))


def clip(d: float) -> int:
    """AtCoder Problems の表示と同じ補正。"""
    return round(d if d >= 400 else 400 / math.exp(1.0 - d / 400))


def band(d: int, table: list[tuple[int, str]], top: str) -> str:
    for upper, name in table:
        if d < upper:
            return name
    return top


def fetch(force: bool) -> None:
    CACHE.mkdir(parents=True, exist_ok=True)
    fetched = False
    for name in RESOURCES.values():
        path = CACHE / name
        if path.exists() and not force:
            print(f"skip  {name}（キャッシュあり。更新するときは --force）")
            continue
        if fetched:
            time.sleep(INTERVAL_SEC)
        req = urllib.request.Request(BASE + name, headers={"User-Agent": USER_AGENT, "Accept-Encoding": "gzip"})
        with urllib.request.urlopen(req, timeout=180) as res:
            body = res.read()
            if res.headers.get("Content-Encoding") == "gzip":
                body = gzip.decompress(body)
        json.loads(body)  # 壊れたデータを保存しない
        path.write_bytes(body)
        fetched = True
        print(f"saved {name}（{len(body):,} bytes）")
    if fetched:
        (CACHE / "fetched_at.txt").write_text(datetime.datetime.now(JST).isoformat(timespec="seconds") + "\n")


class Data:
    def __init__(self) -> None:
        missing = [n for n in RESOURCES.values() if not (CACHE / n).exists()]
        if missing:
            sys.exit("キャッシュがない。先に `python3 tools/ap.py fetch` を実行する（不足: " + ", ".join(missing) + "）")
        load = lambda key: json.loads((CACHE / RESOURCES[key]).read_text(encoding="utf-8"))
        self.problems = {p["id"]: p for p in load("problems")}
        self.models = load("models")
        self.contests = {c["id"]: c for c in load("contests")}
        self.pairs = load("contest_problem")
        self.placements: dict[str, dict[str, str]] = {}  # 問題ID → {コンテストID: 問題の記号}
        for pr in self.pairs:
            self.placements.setdefault(pr["problem_id"], {})[pr["contest_id"]] = pr["problem_index"]

    def origin(self, pid: str) -> str:
        """問題が最初に出たコンテスト。

        problems.json の contest_id は、過去問を再利用した最新のコンテスト
        （AtCoder Daily Training など）を指すことがあるので使わない。
        """
        placed = self.placements.get(pid, {})
        prefix = pid.rsplit("_", 1)[0]
        if prefix in placed:
            return prefix
        if placed:
            return min(placed, key=lambda c: (self.contests.get(c, {}).get("start_epoch_second", 1 << 62), c))
        return self.problems[pid]["contest_id"]

    def info(self, pid: str, cid: str | None = None) -> dict | None:
        p = self.problems.get(pid)
        if p is None:
            return None
        cid = cid or self.origin(pid)
        raw = (self.models.get(pid) or {}).get("difficulty")
        d = clip(raw) if raw is not None else None
        start = self.contests.get(cid, {}).get("start_epoch_second")
        index = self.placements.get(pid, {}).get(cid, p.get("problem_index"))
        return {
            "id": pid,
            "contest_id": cid,
            "index": index,
            "name": p.get("name"),
            # problems.json の title は再利用先のコンテストでの記号が付くことがあるので作り直す
            "title": f"{index}. {p.get('name')}",
            "url": f"https://atcoder.jp/contests/{cid}/tasks/{pid}",
            "difficulty": d,
            "experimental": (self.models.get(pid) or {}).get("is_experimental"),
            "color": band(d, COLORS, "赤") if d is not None else None,
            "level": band(d, LEVELS, "発展") if d is not None else None,
            "date": datetime.datetime.fromtimestamp(start, JST).date().isoformat() if start else None,
        }


def line(x: dict) -> str:
    if x["difficulty"] is None:
        diff = "diff=なし"
    else:
        exp = "（参考値）" if x["experimental"] else ""
        diff = f"diff={x['difficulty']}{exp} {x['color']}/{x['level']}"
    return f"OK  {x['id']}\t{x['title']}\t{diff}\t{x['date']}\t{x['url']}"


def output(items: list[dict], as_json: bool) -> None:
    if as_json:
        print(json.dumps(items, ensure_ascii=False, indent=1))
    else:
        for x in items:
            print(line(x))


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    f = sub.add_parser("fetch")
    f.add_argument("--force", action="store_true")
    s = sub.add_parser("show")
    s.add_argument("ids", nargs="+")
    s.add_argument("--json", action="store_true")
    q = sub.add_parser("search")
    q.add_argument("word")
    q.add_argument("--prefix", default="", help="コンテストIDの接頭辞（abc, arc, typical90 など）")
    q.add_argument("--min", type=int)
    q.add_argument("--max", type=int)
    q.add_argument("--limit", type=int, default=50)
    q.add_argument("--json", action="store_true")
    c = sub.add_parser("contest")
    c.add_argument("contest_id")
    c.add_argument("--json", action="store_true")
    args = ap.parse_args()

    if args.cmd == "fetch":
        fetch(args.force)
        return
    data = Data()
    if args.cmd == "show":
        found, ng = [], []
        for pid in args.ids:
            x = data.info(pid)
            (found if x else ng).append(x or pid)
        output(found, args.json)
        for pid in ng:
            print(f"NG  {pid}\t見つからない", file=sys.stderr)
        sys.exit(1 if ng else 0)
    if args.cmd == "search":
        word = args.word.lower()
        hits = []
        for pid, p in data.problems.items():
            text = f"{p.get('name', '')} {p.get('title', '')}".lower()
            if word not in text:
                continue
            x = data.info(pid)
            if not x["contest_id"].startswith(args.prefix):
                continue
            d = x["difficulty"]
            if args.min is not None and (d is None or d < args.min):
                continue
            if args.max is not None and (d is None or d > args.max):
                continue
            hits.append(x)
        hits.sort(key=lambda x: (x["date"] or "", x["id"]))
        output(hits[: args.limit], args.json)
        if len(hits) > args.limit:
            print(f"…ほか {len(hits) - args.limit} 件（--limit で増やせる）", file=sys.stderr)
        return
    if args.cmd == "contest":
        ids = [pr["problem_id"] for pr in data.pairs if pr["contest_id"] == args.contest_id]
        items = [x for x in (data.info(i, args.contest_id) for i in ids) if x]
        items.sort(key=lambda x: (len(x["index"] or ""), x["index"] or ""))
        if not items:
            sys.exit(f"コンテスト {args.contest_id} の問題が見つからない")
        output(items, args.json)


if __name__ == "__main__":
    main()
