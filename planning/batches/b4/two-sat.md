# two-sat の報告（b4）

- 書いたファイル：docs/graph/two-sat.md、snippets/two-sat/usage.{cpp,yaml}・at-most-one.{cpp,yaml}、docs/img/two-sat/implication.svg・unsat.svg
- front matter で変えたもの：complexity（`O(N + M)（変数 N 個・節 M 個）`）・stage（draft）・updated（2026-10-22）。sections に `when-to-use`（使える形と使えない形）を先頭に足し、`acl` の title を「ACL の two_sat と自作するときの要点」に変えた（anchor は同じ）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0、警告 5：数式を含む文の長さと要点の囲みの長い 1 文）。SVG 2 枚は render_svg で 360px・720px を目視した
- 使った出典：kmjp の ABC210 F・ABC277 Ex の記事（例題・練習の方針）、ACL の twosat.hpp・document_ja/twosat.md・twosat_practice.cpp、英語版 Wikipedia「2-satisfiability」、ei1333.github.io（Luzhiled's Library）、Library Checker の問題定義（GitHub）。新しいドメインはない（どれも付録 B にある）

## 台帳への提案

- practice2_h・abc210_f・abc277_h の evidence が 1 つずつしかない（§15-6 の目標は 2 つ以上）。追加の候補：
  - practice2_h｜evidence｜https://github.com/atcoder/ac-library/blob/master/document_ja/twosat.md を足す（使用例として同じ問題を載せている）
  - abc210_f・abc277_h は今回 2 つ目を探していない（未解決の点）
- 表記・事実の誤りは見つからなかった

## 用語集への提案

- リテラル｜literal｜真偽の変数か、その否定（$x$ や $\lnot x$）。SAT の節を組み立てる単位
- 節｜clause｜リテラルを OR でつないだ条件。2-SAT では 2 つのリテラルの OR
- 含意グラフ｜implication-graph｜リテラルを頂点とし、節 $a \lor b$ を辺 $\lnot a \to b$・$\lnot b \to a$ にした有向グラフ。辺 $u \to v$ は「$u$ が真なら $v$ も真」を表す

（本文ではリンクを張らず、リテラル・含意グラフを導入の段落と implication の節で定義した。足したら最初の出現にリンクを張れる）

## 手引きへの提案

- §5 graph に「2-SAT の復元は『トポロジカル順で後ろの成分にある方を真』。Tarjan 法は成分を逆トポロジカル順に見つけるので、自作では番号の向きを確かめる」を足すとよい（持ち主は two-sat#acl）
- 付録 A のグラフに「リテラル・節・含意グラフ」を足す案（研究ノート 03-graph の用語の一覧にはすでにある）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 今回は探していない。例題 2 問（practice2_h・abc210_f）と練習 1 問（abc277_h）で発展の目安（例題 0〜2）は満たす

## 未解決の点

- abc210_f・abc277_h の evidence を 2 つ目まで集めていない
- 骨格の sections の title「ACL では（two_sat の囲み）」を、自作の要点と Library Checker を含めるために変えた。ほかのページから #acl へのリンクの文言に影響があれば直してほしい（anchor は変えていない）
- 本文で触れた「1 つの数の異なる素因数は 10^7 以下なら 8 種類以下」は 2·3·5·7·11·13·17·19 = 9699690 から手で確かめた値。ABC210 F の制約は本文に書いていない
- 申し送り（handoff-b2b3 §1.2）：project-selection から two-sat へのページへのリンクは、two-sat が draft になったので節へ張り替えられる（候補：#when-to-use）。b1 の §2 の重なり（acl-reading:113・bipartite-graph:172・scc:189・scc:268）は、two-sat 側を短くして scc#acl・scc#algorithms・bipartite-graph へリンクした

## 検証の指摘への対応（verify/two-sat.md）

- 指摘 1（直すべき）：ABC277 Ex の下限を「$X_a < k$ なら $X_b \ge L - k + 1$」に直した
- 指摘 2：早見表の前に、ACL の列は $a$・$b$ を「$x_i$・$x_j$ が真」としたときの書き方で、否定のリテラルならその側の `true`・`false` を入れ替える、と足した
- 指摘 3：Library Checker の変数が 1 始まりであること（$k$ を $x_{k-1}$ に読み替える）と、出力の形（`s SATISFIABLE` と、`v` に続く $\pm i$ の列を 0 で終える行）を足した
- 指摘 4：(a) 使えない理由を「そのままでは 2-SAT の形にならない。一般の 3-SAT は NP 困難」に、(b) 燃やす埋めるは「コストの形が型に合えば」と条件を添えた
- 指摘 5：acl の title の変更はメインの判断に任せる（anchor は同じ。採るのが妥当と考える）
- 指摘 6：implication の第 3 段落を、復元が直接使うのは節ごとの 2 本の辺である、と書き直した。#acl の「辺は必ず 2 本」の理由も「背理法が成り立たない」に合わせた
- 指摘 7（採らなかった）：背理法と「高々 1 つ」の議論はどちらも数行で、モデル化の正しさを読者が確かめる助けになる。検証も「今のままでもよい」としているので、折りたたまずに残した
