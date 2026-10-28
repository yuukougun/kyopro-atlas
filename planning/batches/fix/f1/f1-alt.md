# f1-alt：Issue #50 の本文側（図の代替テキストの対にならない `[`）

担当：#50 のうち、27 ページ 28 か所の代替テキストを直すところ。検査を足す作業（f1-tools）と手引きの更新（メイン）は担当外。

## 直したもの

- 直し方：代替テキストの中の対にならない `[` を `\[` にした。対応はスタックで調べ、対にならない `[` だけをエスケープした。`L[1]`・`dp[j]`・`S[4]`・`z[1]` のように対になる括弧は変えていない。エスケープしたのは全部で 77 個で、どれも半開区間の `[` である。代替テキストの文言はほかに変えていない
- front matter：27 ページの `updated` を 2026-10-22 から 2026-10-29 にした。`stage` などほかの項目は変えていない
- 差分の確認：HEAD と行ごとに比べた。変わったのは `updated` の 27 行と代替テキストの 28 行だけである。新しい行から `[` の前の逆斜線を除くと、元の行と一致する

| ファイル | updated の行 | 図の行 | 図 | `\[` の数 |
| --- | --- | --- | --- | --- |
| docs/basics/imos.md | 35 | 66 | img/imos/imos-1d.svg | 2 |
| docs/basics/imos.md | 35 | 173 | img/imos/imos-2d.svg | 2 |
| docs/basics/difference-sequence.md | 30 | 61 | img/difference-sequence/range-to-points.svg | 1 |
| docs/basics/divide-and-conquer.md | 31 | 132 | img/divide-and-conquer/range-knapsack.svg | 3 |
| docs/basics/event-sort.md | 30 | 56 | img/event-sort/timeline.svg | 3 |
| docs/basics/interval-scheduling.md | 29 | 64 | img/interval-scheduling/greedy.svg | 8 |
| docs/basics/periodicity.md | 31 | 121 | img/periodicity/period-count.svg | 1 |
| docs/ds/segment-tree.md | 33 | 91 | img/segment-tree/prod-nodes.svg | 5 |
| docs/ds/segment-tree-binary-search.md | 32 | 101 | img/segment-tree-binary-search/climb-descend.svg | 5 |
| docs/ds/sqrt-decomposition.md | 30 | 59 | img/sqrt-decomposition/buckets.svg | 1 |
| docs/ds/sweep-line-2d.md | 32 | 101 | img/sweep-line-2d/rectangle-prefix.svg | 4 |
| docs/ds/interval-set.md | 32 | 92 | img/interval-set/assign.svg | 8 |
| docs/ds/offline-queries.md | 33 | 83 | img/offline-queries/distinct-count-sweep.svg | 2 |
| docs/ds/persistent-data-structures.md | 30 | 90 | img/persistent-data-structures/path-copying.svg | 2 |
| docs/dp/interval-dp.md | 31 | 65 | img/interval-dp/split.svg | 1 |
| docs/dp/interval-dp-advanced.md | 29 | 67 | img/interval-dp-advanced/preorder-split.svg | 4 |
| docs/dp/dp-sequence-partition.md | 29 | 66 | img/dp-sequence-partition/last-block.svg | 5 |
| docs/dp/dp-speedup-overview.md | 25 | 72 | img/dp-speedup-overview/read-ranges.svg | 2 |
| docs/tree/euler-tour.md | 34 | 80 | img/euler-tour/subtree-interval.svg | 1 |
| docs/tree/hld.md | 30 | 76 | img/hld/decomposition.svg | 3 |
| docs/tree/merge-process-tree.md | 29 | 59 | img/merge-process-tree/merge-tree.svg | 1 |
| docs/tree/tree-imos.md | 29 | 61 | img/tree-imos/marks-and-sweep.svg | 1 |
| docs/string/rolling-hash.md | 33 | 74 | img/rolling-hash/prefix-hash.svg | 1 |
| docs/string/hashing-for-sets.md | 32 | 97 | img/hashing-for-sets/prefix-sum-hash.svg | 2 |
| docs/string/z-algorithm.md | 34 | 84 | img/z-algorithm/z-box.svg | 1 |
| docs/graph/offline-dynamic-connectivity.md | 26 | 51 | img/offline-dynamic-connectivity/time-segment-tree.svg | 4 |
| docs/patterns/interval.md | 41 | 73 | img/interval/subarrays-as-points.svg | 1 |
| docs/start/notation.md | 31 | 61 | img/notation/half-open.svg | 3 |

## 確かめたこと

- ビルド：`uv run mkdocs build -q -d <作業用フォルダ>/site` で作業用フォルダへビルドした（出たのは Material の告知だけ）
- 突き合わせ（作業用フォルダの verify_build.py）：420 ページで、docs/ の図の参照 414 か所に対し、HTML の `<img>`（`img/` を指すもの）が 414 ある。ページごとの数の不一致はない。alt の文言（Markdown の `\X` を X に戻したもの）と src の行き先も全件一致した。本文（pre・code の外）に「![」の文字は残っていない
- 対照：27 ページを HEAD に戻したコピーを同じ設定でビルドすると、`<img>` は 386 で、27 ページで数が合わず、同じ 27 ページに「![」が文字で残る（Issue の数と同じ）。突き合わせで崩れを捉えられることを確かめた
- リポジトリの .venv の Python-Markdown 3.11.2 で、`\[` と対になる `L[1]` などが混ざった代替テキストも `<img alt="…[1, 7)… L[1] …">` になることを確かめた
- `python3 tools/check_pages.py --page <id>`：27 ページともエラー 0・警告 0。f1-tools の代替テキストの検査は、作業を終えた時点で tools/check_pages.py に入っていなかった（tools/ に差分なし）ので、その検査では確かめていない。代わりに、同じ見方のスクリプト find_alt.py（alt の `[ ]` の対応を調べる。`\[`・`\]` は数えない）で調べ、docs/ の 414 か所すべてで括弧が対になっていた（直す前は 28 か所が対にならなかった）
- `npx textlint`（担当の 27 ファイル）：エラー 0、警告 657。HEAD の 682 件と比べると、no-unmatched-pair が 26 件消え、no-doubled-joshi が 1 件増えた。増えたのは ds/segment-tree-binary-search.md:101 の代替テキストで、「…[4, 8) は 28 で偽になり、降りて [4, 6) は 20 で偽、[4, 5) は 11 で真なので…」の「は」の重なりである。直す前は記法が崩れて文が切れていたため出ていなかった。文言を変えない指示なので残した。ほかの警告は前からあるもの
- `python3 tools/gen_site.py --check`：docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md が変わると出る。変わるのは版と「updated の最大」（2026-10-22 から 2026-10-29）だけなので、メインが gen_site.py を流せば消える
- 図（SVG）は触っていないので、check_svg・render_svg は動かしていない

## 調べて分かったこと

- 対にならない `]`（左が開いた区間 `(l, r]`）でも同じように崩れ、`\]` にすれば直る。閉区間 `[l, r]` は括弧が対になるので崩れない
- リンクの文字でも同じ崩れが起きる（`[区間 [l, r) の和](x.md)` は `[区間 <a href="x.md">l, r) の和</a>` になる）。docs/ の本文（フェンス・コード・数式の外）で括弧が対にならない行を調べた（scan_brackets.py、24 行）。リンクや画像の文字の中にあるのは今回の 28 か所だけだった。残りは表の別のセルにあるもの・admonition の題・意図したエスケープ（`dp\[i][j]`）・gen_site.py が作る分野の入口の要約で、崩れていない
- 代替テキストに `$…$` を書くと、alt に `\(…\)` がそのまま残る。いま数式を代替テキストに使っている図はない
- textlint の ja-technical-writing/no-unmatched-pair は、HEAD で 28 か所のうち 26 か所に警告を出していた。ただし dp-sequence-partition:66 と hashing-for-sets:97 を見逃し、数式の中の半開区間にも警告を出す。警告で埋もれもするので、代わりの検査にはならない

## 提案

### 手引き §8（SVG の項の次に足す）

> - 代替テキストとリンクの文字に区間を書くときは、対にならない括弧を逆斜線でエスケープする：`\[l, r)`・`(l, r\]`（例 `![区間 \[1, 5) に +1](../img/imos/imos-1d.svg)`）。`[` か `]` が対にならないと Python-Markdown は画像やリンクとして読まず、図は出ずに「![…」の文字とリンクになる（#50）。`dp[i]` や閉区間 `[l, r]` のように対になる括弧はそのままでよい。代替テキストに数式（`$…$`）は使わない（alt に `\(…\)` が残る）

### 手引き §6（任意）

- 「区間は半開区間 $[l, r)$ を基本にし」の行に、「数式の外（図の代替テキスト・リンクの文字）に書くときは §8 のとおりエスケープする」と一言足す

### 検査（f1-tools・検証役へ）

- f1-tools の check_pages の検査が入ったら、この 27 ページで通ることを検証役が確かめるとよい
- ビルドの後の突き合わせ（数・alt・src・本文の「![」）には、作業用フォルダの verify_build.py をそのまま使える。引数はリポジトリとビルドしたフォルダ

## 残った点

- ds/segment-tree-binary-search.md:101 の no-doubled-joshi（警告）。消すには代替テキストの文言を変える必要があるので、直すかどうかはメインが決める
- f1-tools の検査が入った後の check_pages では、まだ確かめていない

## 作業用フォルダのもの

/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/f1-alt/ に次を置いた。

- find_alt.py：alt の括弧の対応
- fix_alt.py：直したスクリプト
- verify_build.py：ビルドの突き合わせ
- scan_brackets.py：本文の括弧
- site/：ビルドしたもの
- old/：HEAD に戻したコピーとそのビルド

## 使用量の目安

道具の呼び出しは約 35 回、Web 取得は 0 回。ビルドは 2 回（各 15 秒ほど）。
