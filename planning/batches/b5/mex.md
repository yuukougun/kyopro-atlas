# b5 提案：mex（docs/patterns/mex.md）

- 書いたファイル：docs/patterns/mex.md、snippets/mex/window-min.{cpp,yaml}、docs/img/mex/number-line.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を題材の性質の次に足した（見本 bracket-sequence と同じ形）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 10：図の代替テキストの長さ、数式の中の読点・角括弧の誤検出、表の行）
- 図：number-line.svg を render_svg.py で 360px・720px にして目で確かめた（3 段：mex 3 → 書き換えで 6 へ飛ぶ → 0 に戻る）。catalog の visual（static・priority 2）を静的な SVG で満たした
- 使った出典：ikatakos ABC194・ABC438、hamayan ABC194 E、drken ABC330 E（いずれも付録 B のドメイン）。新しく noai を確かめたドメインはない

## 台帳への提案

- abc194_e｜checked｜2026-10-22｜ikatakos（値を固定して間隔を見る）と hamayan（答えの二分探索＋窓）の 2 つで問いと解法を確かめた
- abc438_f｜checked｜2026-10-22｜ikatakos の解法部分で、頂点番号の mex・主客転倒・両端の更新と打ち切りを確かめた（evidence は 1 件なので、2 件目を足せるとよい）
- abc438_f｜evidence の 1 件目｜`https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/` は一覧のページなので外してよい（abc194_e も同じ）

## 用語集への提案

- mex｜mex｜非負整数の集合に含まれない最小の非負整数。空集合の mex は 0 で、N 個の要素からなる集合の mex は N 以下である。（題材別のページ patterns/mex へのリンクを添える。grundy-number#definition でも定義している）

## 手引きへの提案

- §5 または付録に「mex の印の配列は大きさ N + 1（答えが N になりうる）、N より大きい値は読み飛ばす」を持ち主 patterns/mex#pitfalls として置く（grundy-number#pitfalls・interval-set・ordered-set でも同じ注意が出る）
- pattern の表の「代表の問題」に、ほかのページに載る問題（ABC330 E・ABC470 G・ABC368 F）を label の文字で書き、表の後にそのページの #practice・#challenge・例題の anchor へリンクした。catalog の problems_note（本文から参照する）に従ったもので、この書き方でよいか決めてほしい

## 問題の補充の候補

- abc272_e（E. Add and Mex、diff 1434）：各回の操作の後の数列の mex を答える。mex ≤ N なので [0, N] に入る値だけを列挙し、調和級数で O(N log N) に抑える。→ 題材の性質（値の上限）の練習。裏付け：https://kyo-pro.hatenablog.com/entry/ABC272E 、https://qiita.com/MoroeTachibana-oh/items/2128746896925fbaac5c
- abc290_c（C. Max MEX、diff 225）：数列から K 個を選んだときの mex の最大値。答えは min(K, mex(A))。→ 構築の節の「要素の数」の必要条件の例（基礎なので練習の易しい側）。裏付け：https://programming-hiroba.com/abc290-c/ 、https://aruma256.dev/blog/2023/03/09/abc290-c.html（aruma256.dev は未確認のドメイン。check_noai で確かめてから使う）
- abc308_e（E. MEX、diff 1042）：文字列 MEX の位置の 3 つ組について mex の総和（真ん中を固定する）。→ fix-variable と組み合わせる型。第三者の解説はまだ読んでいない（候補のみ）
- arc216_b（B. Range Mex Sum、diff 1935）：題名から区間の mex の総和の型と思われるが、解説は未確認（候補のみ）

## 未解決の点

- window-mex の節の「長さ M の窓の mex の最大値」（答えで二分探索＋窓の種類数）と「区間の mex のクエリの先読み」（last のセグメント木の二分探索）は、台帳に確認済みの問題がない。自分で確かめた一般的な方法として書いた
- 全区間の mex の総和の O(N log N) は lazy-segment-tree-patterns#reformulate の説明にリンクしただけで、このページでは詳しく書いていない（ABC470 G の持ち主はそちら）
- glossary に mex の項目がないので、本文の「mex」には用語集のリンクを張っていない

## 検証の指摘への対応（verify/mex.md）

- 直すべき 0・直すとよい 4。4 件ともすべて採った（採らなかったものはない）
    1. #overview の表の 2 行目の代表を「—」にした。#interval-values の最後の文を「値ごとの個数と合わせて持てば同じ形で解ける（個数 0→1 で長さ 1 の区間を加え、1→0 で取り除く）」とし、ordered-set#practice の ABC330 E の別解として示した
    2. #sum-of-mex の全区間の項目に「値 k を加えると最小の右端は今の値と L 以降の k の最初の出現の max になり、今の値が L について単調なので区間の一部への代入になる」を足した
    3. #online-mex の囲みを「m は要素の数（初めの N 個と加えた Q 個）を超えないので、全体で N + Q 回しか増えず」に直した
    4. #interval-values の計算量を「ならし O(log K)（K を持っている区間の数とする）」にした
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 10、直す前と同じ種類）
- 台帳への提案は検証の結果と一致（abc194_e・abc438_f を checked、evidence の一覧のページを外す）。上の「台帳への提案」のとおり
