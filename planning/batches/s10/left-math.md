# 工程10 math の直しで残したもの

math の直し担当が直せなかった・判断の要る項目。書いてよい範囲（docs/math・snippets・docs/img の math のページ）の外にあるもの、またはメインの判断が要るもの。

## ほかの分野のページに要る直し（audit-facts の math の項目に含まれていたもの）

- docs/graph/time-dependent-dijkstra.md・L212：$\mathrm{lcm}$ を `\operatorname{lcm}` に直す（notation §6）。math 側の docs/math/spf-sieve.md・L200 は直した
- docs/guide/method-comparison.md・L429：閉区間 $[L, R]$ の断りを足す（「区間篩と同じく閉区間」など）。math 側の mod-inverse・spf-sieve は直した

## メインの判断が要るもの

- docs/math/linear-recurrence-fast.md・L134（audit-structure）：ライブラリの節の anchor が `implementation`。§16-2 では `library` にそろえるが、この直しの決まりは「anchor は変えない」なので変えていない。外からのリンクは docs/index/math.md（生成物）だけで、localStorage の鍵は anchor を使わない（progress.js はページ×レベルと問題 ID だけ）。変えるなら見出しの `{#implementation}` を `{#library}` に、front matter の sections の anchor も `library` にして、gen_site.py で索引を作り直す
- docs/math/modint.md（audit-structure）：基礎の technique に定型の next-steps がない。中身の節「上位の手法での使われ方 {#connections}」が同じ役をしている。現状でよいか、定型の節に改めるかを決める
- docs/math/mod-pow.md（audit-structure）：同じく next-steps がない。中身の節「繰り返し二乗法を部品にする手法 {#building-block}」（sections にある）が同じ役をしている。modint と同じ扱いにする
- docs/math/floor-sum.md（audit-structure）：黄の technique なのに練習問題の節がない（例題 2・力試し 1）。足すには台帳 data/problems.yaml への追加が要るので、問題の補充の観点に回す

## メインへの知らせ（直したことに伴うもの）

- docs/math/sigma-manipulation.md の節 `formulas` の見出しを「よく使う和の公式と、異なる 2 つの積の和を和の 2 乗で表す式」に変えた（anchor はそのまま）。docs/guide/problem-sets.md の L117・L180 は古い見出しの文字を載せている。gen_site.py の生成物なら作り直しで直る
- 図を 2 枚に分けたので、画像のファイルが変わった。消したもの：exponent-mod/powers-mod-7.svg・integer-division/floor-ceil.svg・multiplicative-order/powers-mod7.svg・gaussian-elimination/steps.svg・mod-arithmetic/clock.svg・mod-inverse/mult-table.svg・sigma-manipulation/swap-grid.svg。足したもの：上の各フォルダの 2 枚（詳しくは fixed-math.md）。commit のときに消したものと足したものの両方を入れる
- style-guide 付録 B に fairy-lettuce.hatenadiary.com を足す（xor-basis の参考に使った。2026-10-22 の check_noai で noai・noimageai の指定はない）
