# determinant（行列式）の報告と提案

- 書いたファイル：docs/math/determinant.md、snippets/determinant/mod-p.{cpp,yaml}、snippets/determinant/arbitrary-mod.{cpp,yaml}（図はなし。visual が null のため）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 計算量と自作するときの要点, anchor: library}` を足した（lgv-lemma と同じ形）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 6（数式を含む文の長さ・読点の数、`$[0, m)$` の半開区間による括弧の対の誤検出、「に」の重複 1 件は数式の中）
- 使った出典：ja.wikipedia.org「行列式」（定義・性質・O(n^3)）、oi-wiki.org「高斯消元」（行列式の節、文章は使っていない）、nyaannyaan.github.io「Determinant (arbitrary mod)」（互除法の掃き出しの手順）、github.com の library-checker-problems（3 問の制約。N_MAX・M_MAX は info.toml の params で確認）、kmjp.hatenablog.jp の ABC253 Ex の記事（下の候補の裏付け）。新しく noai を確かめたドメインはない（どれも付録 B にある）

## 台帳への提案

- なし（このページの例題・練習は catalog どおり 0 問。本文に問題の囲みはない）

## 用語集への提案

- 行列式｜determinant｜正方行列 $A$ に対し、各行から列が重ならないように 1 つずつ成分を選んだ積に置換の符号を付けて、すべての選び方で足した値。行の交換で符号が変わり、ある行の定数倍を別の行に足しても変わらない。
- ラプラシアン行列｜laplacian-matrix｜グラフの各頂点の次数を対角に、頂点 $u$・$v$ を結ぶ辺の本数の $-1$ 倍を $(u, v)$ 成分に置いた行列。行列木定理で使う。（matrix-tree-theorem の執筆者と定義をそろえてほしい）

## 手引きへの提案

- §5 math に「行列式の掃き出しではピボットの行を割らない（割るなら値を掛け戻す）。素数でない法は互除法の掃き出し（持ち主は determinant#modulus）」を足すとよい。lgv-lemma・matrix-tree-theorem が determinant#modulus と determinant#library へリンクできる
- lgv-lemma の本文は「法が素数でないときは…行列式のページで扱う」と determinant へページ単位でリンクしている。determinant が draft になったので `../math/determinant.md#modulus` に張り替えられる（メインの作業）

## 問題の補充の候補

- abc253_h（Ex. We Love Forest、diff 2758）：候補の辺から K 本を選んで森になる確率。頂点の部分集合ごとに行列木定理（ラプラシアン行列の余因子の行列式、mod 998244353）で全域木の数を求め、部分集合の DP で森を数える。裏付け：https://kmjp.hatenablog.jp/entry/2022/05/28/1030 。持ち主は matrix-tree-theorem（例題か練習）で、determinant では本文の参照にとどめるのがよい。裏付けは 1 つなので、もう 1 つ探してから台帳に入れてほしい
- abc184_a（A. Determinant、diff 6）は 2×2 の公式を計算するだけで、発展のページの問題には合わない（載せない）

## 未解決の点

- 互除法の掃き出しの計算量 $O(N^3 + N^2 \log m)$ は、ピボットが各行との最大公約数に置き換わって対数が打ち消し合う、という自分の議論による。第三者の資料で同じ式を明記したものは見つけられなかった（Nyaan 氏のページは計算量を書いていない）。検証役に議論の確認を頼みたい
- Library Checker の任意 mod の問題で、実際に N = 0 の試験があるかは確かめていない（制約が $0 \le N$ であることだけ確認し、本文もその書き方にした）
- 「学ぶための資料」に日本語の競プロ向けの解説記事（互除法の掃き出し）を入れられなかった。良い記事があれば差し替えたい

## 検証の指摘への対応

- 指摘 1〜5 はすべて直した（確認問題 1 の誤った一文、LGV 補題の「符号付き」、ACL の modint では assert で止まること、ラプラシアン行列の自己ループと多重辺、計算量の式）
- 用語集への提案の「ラプラシアン行列」は、定義に「次数は自己ループを除く。多重辺は本数をそのまま数える」を足してほしい（matrix-tree-theorem#laplacian とそろえるため）
