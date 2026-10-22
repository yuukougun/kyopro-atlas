# general-matching の報告と提案

- 書いたファイル：docs/graph/general-matching.md、snippets/general-matching/{bitdp,tutte-rank}.{cpp,yaml}、docs/img/general-matching/{blossom,contracted}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `tutte-matrix`（大きさだけなら乱択（Tutte 行列の階数））と `library`（自作するときの要点と確かめ方）を足した（level はページと同じ）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0、textlint エラー 0（警告 10 は文の長さ・数式を含む文・図の代替テキストの読点・助詞「で」の重複）。図は render_svg で目視した
- 使った出典：en.wikipedia.org（Blossom algorithm・Maximum weight matching・Tutte matrix）、arxiv.org/abs/cs/0601026（Harvey）、ei1333.github.io（Gabow Edmonds）、github.com（library-checker-problems の task.md）、kmjp.hatenablog.jp（例題）
- 新しく noai を確かめたドメイン：arxiv.org（指定なし、2026-10-22）、www.kurims.kyoto-u.ac.jp（指定なし。PDF の文字を取り出せず、資料には使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc412_g | summary | 単純な無向グラフと各頂点の値 A_i が与えられ、各頂点の次数が A_i 以下で A_i と偶奇が等しくなるように辺を選ぶとき、選ぶ辺の数の最小を求める（できなければ -1）。 | https://kmjp.hatenablog.jp/entry/2025/06/29/0930 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 花（blossom） | blossom | マッチングに対して、長さ 2k+1 で組の辺を k 本含む閉路。Edmonds のアルゴリズムはこれを 1 頂点に縮約して増加路を探す。 |
| 交互路 | alternating-path | 組の辺と組でない辺が交互に並ぶ路。両端が空いている交互路が増加路である。（用語集に「増加路」はあるが「交互路」がない。付録 A に正規形としてある） |

## 手引きへの提案

- 発展の概要のページで「学ぶための資料」を `## 学ぶための資料 {#resources}` の定型の節にするなら §13-1 に足すとよい（alien-dp と同じ見出しにそろえた。sections には載せていない）

## 問題の補充の候補

- ABC で一般グラフのマッチングを使う問題は abc412_g 以外に見つけられなかった（第三者の解説の検索で、ABC412 G 以外に候補が出なかった）。bitDP で解けるマッチングは bit-dp の EDPC O など既存の例題がある

## 未解決の点

- abc412_g の裏付けは kmjp 氏の解説 1 つだけ（§15-6 の目標は 2 つ以上）。ikatakos 氏の ABC412 の記録には G の節がなく、ほかの第三者の解説は見つからなかった。制約（ΣA_i の上限）は解説の本文になく、本文には書いていない
- 乱数を入れた Tutte 行列で階数が保たれる確率 1 − N/p 以上は、Schwartz-Zippel の補題からの一般的な導き（出典の本文では確かめきれていない）。Harvey の論文では「階数が最大マッチングの 2 倍（Lovász）」の部分だけを確かめた
- Gabow の改良版の内部の作り（縮約したグラフを作り直さない）は一般的な説明で、ei1333 氏の実装の中身は読んでいない
- bipartite-matching・konig-theorem からこのページへのリンクは、draft になったので節（#odd-cycles など）へ張り替えられる（handoff-b2b3 の申し送り）

## 検証の指摘への対応（2026-10-22）

- 指摘 1（直すべき）・3〜7：直した。3 は $C > (N/2) \max w$・完全でない場合・long long を足した。5 は「Tutte の定理」をやめ、同値であることを理由として書いて（Tutte, 1947）とした
- 指摘 2：summary・signs は執筆者が変えないので、下の提案にした（要点の「何ができるか」「いつ使うか」も front matter からそろえてほしい）

### front matter への提案（指摘 2）

| 項目 | 今の値 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| summary | …N ≤ 16 程度なら bitDP で足りる。 | …N ≤ 20 程度なら bitDP で足りる。 | 本文の O(2^N N) は N=20 で約 2×10^7。要点の計算量・#bitdp と食い違う |
| signs（constraint） | N ≤ 16 程度の一般グラフでペアを作る | N ≤ 20 程度の一般グラフでペアを作る | 同上 |

### 台帳への提案（追加）

- abc412_g：検証で summary が kmjp 氏の記事と合うと確かめられたので `checked: 2026-10-22` を入れてよい
