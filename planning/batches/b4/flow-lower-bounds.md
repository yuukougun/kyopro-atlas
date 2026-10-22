# flow-lower-bounds の報告（b4）

- 書いたファイル：docs/graph/flow-lower-bounds.md、snippets/flow-lower-bounds/usage.{cpp,yaml}、docs/img/flow-lower-bounds/transform.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 期待と違う0、textlint エラー0・警告6（要点の「何ができるか」の 1 文目は summary のまま、図の代替テキストの長さ、数式を含む文の助詞の重なり）
- 図：transform.svg を render_svg.py で 360・720 の幅にして目で確かめた
- コード片：下限付きの s-t 最大流の関数を ACL の mf_graph で書き、小さいランダムなグラフ 3000 個で各辺の流量を全通り試した答えと assert で照合した

## 使った出典

- https://kmjp.hatenablog.jp/entry/2023/01/22/0900 ：例題の方針（台帳の evidence）
- https://qiita.com/recuraki/items/9620eb026a33972df626 ：例題のモデル化（2 のマスの s 側・t 側の辺に下限 1）。qiita.com は付録 B にあり、check_noai でも指定なし
- https://snuke.hatenablog.com/entry/2016/07/10/043918 ：下限付き最大流の作り方。**新しいドメイン**：snuke.hatenablog.com は check_noai で noai・noimageai の指定なし（2026-10-22）
- https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.hpp ：判定・最大・最小の流量の求め方
- https://cp-algorithms.com/graph/flow_with_demands.html ：構成の確認だけ（文章と図は使っていない）
- https://raw.githubusercontent.com/yosupo06/library-checker-problems/master/graph/min_cost_b_flow/task.md ：Library Checker の Minimum Cost b-flow の定義の確認（judge.yosupo.jp の問題ページは JS で描かれ本文を読めなかったため）

## 台帳への提案

- abc285_g｜evidence｜https://qiita.com/recuraki/items/9620eb026a33972df626 を足す（2 つ目の裏付け。§15-6）
- abc285_g｜checked｜2026-10-22

## 用語集への提案

- 循環流｜circulation｜始点・終点を持たず、すべての頂点で入る量と出る量が等しい流れ。s-t 流は、t から s へ容量の大きい辺を足すと循環流として扱える。
- 下限付きの辺（最小流量制約）｜lower-bound｜流量に「L 以上 R 以下」の範囲が付いた辺。流量を L + g と置くと容量 R − L の普通の辺に直せる。（ページがあるので用語集に要るかはメインの判断）

## 手引きへの提案

- §5 graph に「下限付きの流れの最大化で、t→s の大きな辺を残したまま flow(s, t) を呼ぶと、その辺の逆辺を通ってすでに流れた量も返るので、返り値がそのまま合計の流量になる」を足すかどうか（ACL で書くときの取り違えやすい点。持ち主は flow-lower-bounds#super-vertex）

## 問題の補充の候補

- 確かめた範囲では ABC で下限付きフローを直接使う問題は abc285_g のほかに見つからなかった（研究ノートでも ABC の例は 1 問）。候補の探索は ap.py の範囲では行っていない（第三者の解説で「最小流量」「下限付き」を名指しする ABC の記事は abc285_g だけだった）
- 練習として Library Checker の Minimum Cost b-flow（https://judge.yosupo.jp/problem/min_cost_b_flow）を「練習問題 > Library Checker」に置いた（§15-5）。負のコストを含むので ACL だけでは通らない旨を本文に書いた

## 未解決の点

- Minimum Cost b-flow は下限付きの最小費用流で、このページの範囲（最大流）より広い。練習に置くのが重すぎるなら外すか、参考だけに移す
- 流量が負にしかなれない入力（下限で t から s へ流れが強制される場合）は、ページの作り方では「流せない」になる。自作の要点に注記したが、Luzhiled's Library の min_flow は負の流量も返す仕様で、扱いが違う
- 動く図は作っていない（catalog の visual は null）

## 検証の指摘への対応（2026-10-22）

- 指摘 1〜7 はすべて直した。採らなかったものはない
    - 1：complexity・要点から容量 1 の行を外し、$O(F(N + M))$ を上限として書いた。例題の最後の箇条は「$D$ は 2 のマスの数に等しく $HW$ 以下」から $O((HW)^2)$ の上限だけを書き、「速い」は消した
    - 2：負のコストは「先に上限まで流したことにして逆向きの正のコストの辺に置き換える」に直した。Minimum Cost b-flow は残し、要約を問いだけにして、通らない理由を「流量と双対変数の出力・64 bit を超える答え」に直した
    - 3：図の注記を「u は L だけ多く出した（L 多く受け取り T へ）」に、代替テキストも同じ向きに直した（360px で収まることを確認）
    - 4：#super-vertex の 1 文目に $d(v)$ の定義を添え、#pre-flow の最後の段落から $S$・$T$ の前出しを外した
    - 5：最小の流量を $X - Y$ の式で書き、負になりうることを足した
    - 6：`int` の最大値は「ほかの容量の合計に足りないことがある」と避ける理由を明示した
    - 7：usage.yaml に $t \to s$ 向きの下限だけがある case（-1）を足した
- 手引きへの提案（§5 graph）に、「下限付きの最小費用流で、負のコストの辺も先に流したことにして非負に直せる」も添える候補とする（メインの判断）
