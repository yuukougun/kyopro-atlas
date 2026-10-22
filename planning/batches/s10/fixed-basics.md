# 工程10 直し：basics・thinking（直した数と残したもの）

対象：planning/batches/s10/audit-*.md の「## basics」「## thinking」の項目。

**直した数 66・残した数 2**（直さなくてよい 1 件は別に数える）。残したものの詳細は [left-basics.md](left-basics.md)。

## 事実・表記（audit-facts）10 件

- complexity-estimation：$3^N$ の上限を「$N \le 15$〜$16$ 程度まで」にし、演算回数を $3^{16} \approx 4.3 \times 10^7$ にした
- bit-operations：`1 << 31` のかっこ内を「C++20 から規格で値が決まった。C++14・C++17 では処理系定義で、GCC では同じ値になる。どの版でも警告は出ない」にした（style-guide §5 の決まりどおり）
- kth-value：「0 始まり」を「0 番目から数える」、「1 始まり」を「1-indexed」にした
- bitwise-independence：本文・見出し・sections の title・complexity の「上位ビット」を「上位 bit」にした（anchor `split-by-top-bit` は変えていない）。summary は提案に回した
- bit-operations：見出しと sections の title の「最下位ビット」を「最下位 bit」にした（anchor `popcount` は同じ）
- difference-sequence：「フェニック木」を「BIT」にした
- divide-and-conquer：要点の「区間 $[L, R]$」を「閉区間 $[L, R]$」にした
- median-absolute：「slope trick」を「Slope Trick」にした
- thinking/parity：「歩道」を「ウォーク」にした
- thinking/symmetry-pigeonhole-casework：「閉区間 $[L, R]$」にし、「4-サイクルの検出」を「長さ 4 の閉路の検出」にした

## 図（audit-figure）37 件

すべての図を 360px の画面で文字が 9px 以上になるようにし、width・height を viewBox と同じ値で付けた。`python3 tools/render_svg.py --width 360` で撮って、文字の重なりと切れを目で確かめた。

- 作り直し（幅 400 以下に詰め、横に並んでいた注記・凡例・表を下へ回す）：binary-search-answer/greedy-check・staircase、binary-search/bounds、bitwise-independence/bit-count-table、coordinate-compression/mapping・intervals、difference-sequence/range-to-points、event-sort/timeline（時間軸と処理の表を縦に並べた）、fractional-binary-search/lines・median、imos/imos-1d、interval-scheduling/greedy（「飛ばす」は × と凡例の 1 行にした）、kth-value/count-staircase、median-absolute/slope、meet-in-the-middle/combine、prefix-sum-counting/pairs、recursion-structure/burger-kth、run-length-encoding/runs、ternary-search/shrink（2 つの場合を縦に並べた）・difference-sign・flat-pitfall、thinking/parity/checkerboard-walk、thinking/reverse-thinking/reverse-deletion（4 つの時刻を縦に並べ、右に削除・左に追加の矢印）、thinking/symmetry-pigeonhole-casework/pair-table・pigeonhole-boxes
- 文字だけ大きくした：bit-operations/ops-table、doubling/table-jump、greedy-basics/exchange、greedy-priority-queue/from-last-day（見出しの「新しく入れる b」を「入れる b」に縮めた）、imos/imos-2d、lexicographic-greedy/smallest-subsequence、sorting-techniques/matching、two-pointers/window-staircase、thinking/construction/zigzag・modsum-bound
- width・height だけ足した：bit-operations/submask-steps、brute-force/fix-two、complexity-estimation/operation-counts、divide-and-conquer/range-knapsack・recursion-tree、periodicity/period-count・rho、prefix-sum/half-open、thinking/fix-variable/fix-middle

図の内容（値・並び・意味）は変えていないので、代替テキストはそのまま正しい。

## つながり（audit-relations）3 件

- exchange-argument の落とし穴：`<=` と `double` の害を分けて書き直した（`<=` は狭義の弱順序を壊して実行時に落ちうる、`double` の比は違う比が同じ値に丸められて順を取り違え誤答になる）
- imos#adjacent-difference：ここの $d$ が内側の隣接差 $d_1, \dots, d_{N-1}$ であることと、両端の外を 0 とみなして $d_0, d_N$ まで取れば端の区間も 2 点の操作になること（difference-sequence#to-point-operations へのリンク）を足した
- thinking/parity：「重み付き Union-Find」のリンクを `../ds/weighted-union-find.md#generalization`（XOR で偶奇を持つ節）にし、related に weighted-union-find を足した

## 台帳と本文（audit-shared）4 件直した・2 件残した・1 件は直さなくてよい

- 直した：binary-search の練習に abc299_d（質問で二分探索する節と interactive の例題へリンク）、kth-value の練習に abc364_d（距離を答えで二分探索）、prefix-sum の練習に typical90_bx（#circular の型）、bit-full-search の練習に abc197_c（区切りの位置を bit に対応させる）を足した。行の書式は台帳の label・diff・summary どおり（check_pages で台帳と一致）
- 残した：difference-sequence の abc116_c（台帳から外すのが自然）、exchange-argument の abc467_f（問いの確認と台帳の summary が要る）
- 直さなくてよい：thinking/fix-variable の abc458_e（未確認の note どおり）

## 構成（audit-structure）12 件

- `## 上位の手法へのつながり {#next-steps}` を 11 ページに足した（落とし穴の後・問題の前。sections には載せない）：binary-search、bit-full-search、complexity-estimation、coordinate-compression、imos、interval-scheduling、lexicographic-greedy、periodicity、prefix-sum、run-length-encoding、two-pointers。リンク先はすべて実在する節で、リンクの文字は相手の題名にそろえた
- bitwise-independence の要点：1 文目を「全ペア・全区間の XOR・AND・OR の集計を、bit ごとに 0 と 1 の個数を数えて $O(N^2)$ から $O(NB)$ にする」にし、性質は 2 文目へ回した

## 検査

- `python3 tools/check_pages.py`：basics・thinking のページのエラー 0。全体ではエラー 1 件（math/integer-division の図がない。担当外で、left-basics.md に記録）
- `npx textlint docs/basics/*.md docs/thinking/*.md`：エラー 0（run-length-encoding に出た prh の「接尾辞配列」は Suffix Array に直した）
- コード片は変えていない（`python3 tools/check_snippets.py --changed` は他の分野の変更 1 件だけを試し、期待と違う 0）
- 図は上の自作の計測（audit と同じ計算：倍率 = min(width, 328) / viewBox の幅）で、basics・thinking の SVG 55 枚すべてで 9px 未満の文字が 0、width のない図が 0
