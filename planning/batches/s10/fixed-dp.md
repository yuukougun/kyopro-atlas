# 工程10 直し：dp・misc（直した数と残したもの）

対象：planning/batches/s10/audit-*.md の「## dp」「## misc」の項目。

**直した数 56・一部を残した数 4・残した数 1**。残したものの詳細は [left-dp.md](left-dp.md)。

## 事実・表記（audit-facts）4 件

- bit-dp：L157・L158 の「歩道」を「ウォーク」にした
- bit-dp：見出しと sections の title を「ほかの探索と組み合わせる（BFS・ワーシャルフロイド法で距離を前計算してから）」にした（anchor `with-shortest-paths` は同じ）
- digit-dp：太字の見出し語を「閉区間 $[L, R]$ の下限」にした。digit-dp-advanced：確認問題を「両方を閉区間 $[L, R]$ から選ぶ」にした
- misc/interactive：L159 を「閉区間 $[L, R]$ を…」、L260 を「聞ける閉区間 $[l, r]$」にした

## 図（audit-figure）37 件（SVG 46 枚）

すべての図を 360px の画面で文字が 9px 以上になるようにし、width・height を viewBox と同じ値で付けた。`python3 tools/render_svg.py --width 360` で撮って、文字の重なりと切れを目で確かめた。図の値・並び・意味は変えていない。

- 作り直し（幅 400 以下に詰め、横に並んでいた注記・凡例・表を下へ回す）：bit-dp/subset-order、dp-basics/push-pull、dp-segment-tree/split-abs、dp-sequence-partition/last-block、dp-state-design/bracket・merge、interval-dp/table・split、tree-dp/independent-set・reroot-difference、digit-dp-advanced/multiple-numbers・carry、dp-dimension-reduction/swap-tables、dp-mod-state/fold、dp-phase/phases、dp-prefix-sum/pull-prefix、insertion-dp/relative-rank-table・hakone-matching、knapsack-01/rolling-direction、memoized-recursion/call-tree、misc の interactive/halving、bitset-speedup/word-and・shift-or、randomized/failure-probability
- パネルを縦に並べ直した：tree-dp-square/pairs-at-lca（木と表を上下に。代替テキストの「左は・右は」を「上は・下は」に直した）、rerooting/what-changes（2 つの根を上下に、矢印を縦に）、dp-order/six-orders（6 枚を 1 列に。left-dp.md に判断を残した）
- 文字を大きくするか余白を詰めた：dp-grid/square（説明を表の下へ）、knapsack-undo/add-remove（16 にし、はみ出す説明を左へ）、lcs/table、subset-enumeration-dp/three-states、subsequence-dp/leftmost-dag（viewBox の左右の余白を詰めた）、subset-sum/shift-or（同じ）、misc の parsing/call-tree、randomized/boyer-moore
- width・height だけ足した：broken-profile-dp/profile・transitions、dp-dag/table-as-dag、dp-grid/order、dp-reconstruction/kth-counts・trace-back、dp-segment-tree/values-steps、inline-dp/row-diff、interval-dp-advanced/preorder-split

## つながり（audit-relations）4 件

- dp-dag：with-cycles の SCC の項目から「前提にする」をやめ、縮約の結果だけを書いて「この縮約（強連結成分分解）は水の内容であり、手順は scc#dp-on-dag にある」と送る形にした
- subset-enumeration-dp：sections の vs-zeta に `level: 黄` を付け、節の書き出しを「この節は黄の内容である。前提として高速ゼータ変換を使う。」にした
- interval-dp L141・knapsack-01 L215・subset-sum L110：リンクの文字を「並べ替えてから DP する」にした
- knapsack-undo L219 を「DP の状態の削減」、digit-dp L219・digit-dp-advanced L297 を「照合オートマトン上の DP」にした

## 台帳と本文（audit-shared）5 件・一部 1 件・残した 1 件

本文の問題の行は `python3 tools/fix_problems.py --page …` で label・URL・diff を埋め、`--check` で 0 件を確かめた。方針は台帳の approach と evidence の記事の解き方に合わせた。

- dp-state-design：練習に ABC147 E（差そのものを状態に足す可否の DP）を足した
- rerooting：`## 力試し {#challenge}` を作り、ABC223 G（各方向の部分木の最大マッチングを全方位木 DP で求める）を足した
- dp-basics：練習に ABC242 C（末尾の数字を状態にする）を足した
- subset-enumeration-dp：練習に ABC332 E（分散を 2 乗の和の最小に直し、袋ごとに部分集合を列挙）を足した。参考の記事が出典になる
- insertion-dp：練習に EXAWIZARDS2019 D（小さい順に挿入し、先頭に置いたときだけ効く）を足した
- 一部：dp-prefix-sum は abc183_e（方向ごとの累積和）を足した。abc130_e は練習が 7 問になるので足さず、台帳から外す案を left-dp.md に書いた
- 残した：slope-trick の abc458_g は §16-17 の判断待ち

## 構成（audit-structure）6 件・一部 3 件

- dp-speedup-overview：hub なので complexity を null にした（要点の囲みの「計算量」は残した）
- dp-basics・subset-sum・misc/interactive：`## 上位の手法へのつながり {#next-steps}` を足した（dp-basics と subset-sum は確認問題の前、interactive は例題の前）。リンク先の anchor はすべてあるのを確かめた
- misc/bitset-speedup L124・misc/parsing L237〜239：箇条書きの文の行に句点を付けてそろえた
- 一部：cht・dynamic-dp・monge は見出しと sections の title を「ライブラリでの検証」に縮めた。anchor の `verify` → `library` は決まり（anchor を変えない）に当たるので left-dp.md に残した

## 検査

- `python3 tools/check_pages.py`：エラー 0・警告 0
- `npm run lint:text`：エラー 1（`docs/ds/partially-persistent-union-find.md:122`、担当の外。left-dp.md に記録）。dp・misc の変えたページはエラー 0。変えた行の警告のうち、自分で足した文の長さ・助詞の重なりは直した
- `python3 tools/fix_problems.py --check --page …`（6 ページ）：直すべき行 0
- コード片は変えていないので check_snippets は回していない
