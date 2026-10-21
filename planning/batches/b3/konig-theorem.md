# konig-theorem の報告（b3）

- 書いたファイル：docs/graph/konig-theorem.md、snippets/konig-theorem/cover.{cpp,yaml}、snippets/konig-theorem/lp-double.{cpp,yaml}、docs/img/konig-theorem/cover-and-matching.svg
- front matter で変えたもの：complexity（`最大流 O((N + M)√(N + M))、被覆の復元 O(N + M)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages 警告 0、fix_problems --check 0、check_snippets 2 本とも一致、textlint エラー 0・警告 11（front matter の行の長さ、数式の中の集合の読点 `$\{4, a, b\}$`・`$[0, 1)$` の括弧、台帳から作る問題の行、表の行、例題の段落の「に」。どれも誤検出か、問題の行の台帳の要約による）
- 図：cover-and-matching.svg を render_svg.py で 360px・720px にして目で確かめた。catalog の visual は priority 2・static なので、動く図の置き場は作っていない
- 使った出典：ACL document_ja/maxflow.md（手元の v1.6）、en.wikipedia.org の Kőnig's theorem (graph theory)・Edge cover・Vertex cover（raw で取得）、kmjp 氏の abc274_g・abc445_g・abc461_g の記事。新しく noai を確かめたドメインはない。ikatakos.com（abc461_g の evidence）はメンテナンス中で読めなかった

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc445_g | alternatives[konig-theorem].summary と summary | N×N の盤面の置けないマスを避けて、縦横に (±A, ±B) か (±B, ±A) だけ動く駒を、どの 2 つも互いに 1 手で届かないように最も多く置く置き方を 1 つ求める。 | https://kmjp.hatenablog.jp/entry/2026/02/14/1030 |
| abc274_g | checked | 2026-10-21 | https://kmjp.hatenablog.jp/entry/2022/10/22/0900（問いと解法を確かめた） |
| abc445_g | checked | 2026-10-21 | 同上の kmjp 氏の記事 |

本文の abc445_g の行は `- abc445_g：要約` で書き、fix_problems で label を埋めた。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| マッチング | matching | 端点を共有しない辺の集まり。二部グラフの最大マッチングは最大流で求まる |
| 頂点被覆 | vertex-cover | どの辺も、少なくとも一方の端点が入っている頂点の集まり。補集合は独立集合になる |
| 辺被覆 | edge-cover | どの頂点も、少なくとも 1 本の辺の端点になっている辺の集まり。辺を持たない頂点があると作れない |
| LP 緩和 | lp-relaxation | 0 か 1 を取る変数の条件を、0 以上 1 以下の実数に緩めた問題。最大値は元の問題の最大値以上になる |

本文ではこれらの語をページの中で定義したので、用語集へのリンクは張っていない（独立集合だけ glossary#independent-set へ張った）。用語集に足すなら、ほかのページ（bipartite-matching・min-cut など）から張る先になる。

## 手引きへの提案

- 付録 A の「グラフ」に、最大独立集合・最小頂点被覆・最小辺被覆・マッチング・交互路・残余グラフを足すとよい（フロー・マッチングの章で表記がそろう）

## 問題の補充の候補

- 練習は 2 問（abc445_g・abc461_g）で目安の下限を満たすので、今回は探していない。黄の例題が 1 問（abc274_g）なので、易しめの例題（ABC の F・典型90 の二部グラフの最大独立集合など）があれば足したい。候補を探すときは、ap.py と第三者の解説で問いを確かめる必要がある

## 未解決の点

- abc461_g：孤立点（辺を持たない頂点）の値に上限があるかを確かめられなかった（問題文は開けず、ikatakos 氏の記録はメンテナンス中）。kmjp 氏の解答は孤立点に 2026（両方の写しが独立集合に入る）を割り当てる式 `(2N − ν) × 1013` なので、値に 2026 以下の上限があるか、孤立点がない制約だと考えられる。本文の方針では孤立点に触れていない
- abc274_g：制約（盤面の大きさ）は確かめていないので、本文の計算量は空きマスの数 K で書いた
- 「被覆の復元」の節は、ACL の min_cut の返す集合が最大流の取り方によらない（残余グラフで s から届く集合は一意）ことに頼っている。snippets の期待値もこれに依存する。本文では一意性に触れていない
- 相手のページへの張り替え：bipartite-graph:170 と tree-bipartite:142 から konig-theorem へページへのリンクがある。節へ張り替えるなら、bipartite-graph:170 は #theorem、tree-bipartite:142 は #theorem が合う
- 本文から stub のページ（bipartite-matching・min-cut・general-matching・chromatic-number・dilworth-path-cover・project-selection）へは anchor なしでリンクした。chromatic-number が draft になったら #independent-set、min-cut は #restore、bipartite-matching は #reduction へ張り替えられる

## 検証の指摘への対応（2026-10-21）

- 1（直すべき）：表の「成り立つ範囲」を「二部グラフならいつも（一般には $\tau \ge \nu$ で、等しいとは限らない）」に、#make-bipartite を「定理が保証されない」に、#general-graph の冒頭を「保証されるのは二部グラフだけで、$\tau > \nu$ になりうる」に直した。あわせて同じ節の「崩れるのは」を「崩れうるのは」にした
- 2：本文に「残る左の頂点は 4 だけなので、合わせて 3 本が上限」を足し、図の注記も「1・2・3 からは a・b への 2 本だけ、4 から 1 本で、マッチングは 3 本が上限」（2 行）にした
- 3：#lp-half-integrality の最後の段落に、値は 0 以上・辺を持つ頂点では上限 $c$ が辺の条件から出ること・辺を持たない頂点は上限 $c$ が別にあるときに限ること、を足した。abc461_g の制約（孤立点の有無・値の上限）は今回も確かめられていない
- 4：要点の括弧に「最小辺被覆は辺を持たない頂点がないとき」を足した
- 5：「最小カットにならない」を「最小カットになるとは限らない」にした
- 6：図を 420×600 の縦長にし、凡例と式をグラフの下へ移して文字を 18（注記 16）にした。render_svg.py の 360px で読めることを確かめた
- 7：「数が正の整数なら」と前置きした
- 採らなかったもの：なし。textlint の警告 12 件はどれも元からの形（集合の中のカンマ・台帳から作る行・長い証明の文）で、エラーは 0

## 提案（検証の後）

- 台帳：abc461_g の note に「孤立点の値の上限（または孤立点がない制約）を、問題文が読める第三者の記録で確かめる」を残す。確かめられたら本文の方針に 1 文（孤立点は 2026 を置く、など）を足す
- 台帳：abc274_g・abc445_g の `checked` に 2026-10-21 を入れる（検証役も同意）
