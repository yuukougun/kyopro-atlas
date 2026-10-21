# max-flow（最大流）の執筆の報告と提案

- 書いたファイル：docs/graph/max-flow.md、snippets/max-flow/{usage,own-dinic,vertex-split}.{cpp,yaml}、docs/img/max-flow/reverse-edge.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は、`acl` の title を「ACL では（mf_graph の囲み）」から見出しと同じ「ACL の mf_graph で書く」に直し、本文の順（residual → algorithms → acl → modeling → undirected-vertex-capacity）に並べ替えた。anchor は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 3 本・期待と違う 0／textlint エラー 0・警告 16（数式を含む文の長さ、数式の前後や箇条書きの中の助詞「に」「は」の重なりの誤検出）
- 図：SVG 1 枚（逆辺が要る例の 3 段：元のグラフ・1 流した後の残余グラフ・最終の流れ）を render_svg.py で 360px・720px の PNG にして目で確かめた
- 動く図（visual priority 1）：置き場の div だけ置いた。仕様は下の「動く図の仕様」
- 使った出典：ACL の document_ja（maxflow.md・appendix.md）と test/example/maxflow_practice.cpp、kmjp（abc205_f・abc318_g・abc241_g）、E869120 の GitHub（鉄則本 answer_A68.cpp）。新しいドメインはない
- 申し送り（b1 handoff §1）：acl-reading:114 の行は `#acl`、grid-graph:122 の行（ドミノの配置 → 最大流）は `#modeling` へ張り替えられる

## 動く図の仕様（max-flow-residual）

- div：`<div class="kp-viz" data-viz="max-flow-residual" data-config='{"n": 4, "labels": ["s", "a", "b", "t"], "edges": [[0, 1, 1], [0, 2, 1], [1, 2, 1], [1, 3, 1], [2, 3, 1]], "s": 0, "t": 3, "paths": [[0, 1, 2, 3], [0, 2, 1, 3]]}'></div>`
- 状態：最初は元のグラフ（各辺に残りの容量、逆辺は容量 0 で薄く）。各ステップで `paths` の 1 本を強調し、その道の最小の容量 d を示してから流す。流した後は順辺の容量が d 減り、逆辺の容量が d 増える。逆辺を通るステップでは、元の辺の流量が減る（押し戻す）ことを caption で言う。最後に s から届く頂点を塗り、増加路がないこと（最小カット）を示す
- `paths` を渡さずに、BFS で増加路を自動で探す版にしてもよい（その場合は 1 本目に s→a→b→t を選ぶよう、辺の順で決まる DFS にする必要がある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| tessoku_book_bp | summary | 容量付きの有向グラフで、頂点 1 から頂点 N へ流せる量の最大を求める。 | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap09/answer_A68.cpp（入力の辺をそのまま足して 1 から N へ流す） |
| tessoku_book_bp | evidence | 上の answer_A68.cpp の URL に絞る（今はフォルダの URL） | 同上 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 残余グラフ | residual-graph | 流れを決めたグラフで、各辺 u→v（容量 c、流量 f）を、残りの容量 c−f の順辺 u→v と、押し戻せる量 f の逆辺 v→u に置き換えたもの。最大流は残余グラフで s から t への道がなくなるまで流す |
| 増加路 | augmenting-path | 残余グラフで、容量が正の辺だけを通る s から t への道。道の上の容量の最小値だけ流量を増やせる |

（本文では用語集へリンクしていない。「残余グラフ」「増加路」は本文の最初の節で定義している）

## 手引きへの提案

- §14-4（ACL は見出しを立てず囲みにする）と、骨格の sections に `ACL では（… の囲み） {#acl}` が残っているページの扱いが食い違う。今回は ACL の使い方そのもの（割り当ての読み出し・上限・続けて流す・min_cut）に中身があるので、中身の節「ACL の mf_graph で書く {#acl}」にして囲みを中に置いた。ほかのフローのページ（min-cost-flow など）も同じ形の sections なら、同じ扱いでよいかを決めてほしい
- §5 graph の「フローは中身より、どんなグラフを作るかを主役にする」に、「作ったグラフで、解 → 流れ、整数の流れ → 解 の両向きが言えることを書く」を足すとよい（今回の modeling の節の冒頭の 2 条件）

## 問題の補充の候補

例題 2・練習 2・力試し 1 で目安を満たすので、必須の補充はない。abc319 以降の問題が 1 問もないので、余力があれば次を確かめる（ap.py で実在と difficulty は確かめた。第三者の解説での裏付けはまだしていない）：

- abc437_g（G. Colorful Christmas Tree、diff 2806）：research/03-graph の §4.G の表で「最大流」に分類されている。力試しの候補だが、difficulty が発展の帯なので、裏付けの後に flow 系の発展のページに回すかを決める。裏付けの URL は未調査（kmjp の ABC437 の記事を探すとよい）
- abc401_g（G. Push Simultaneously、diff 2022）：答えで二分探索して完全マッチングを判定する問題で、research では二部マッチングに分類されている。max-flow の練習にするより bipartite-matching の例題の方が合う

## 未解決の点

- 例題 abc205_f の制約（H, W, N の上限）は evidence の kmjp の記事に書いていない。本文では制約の値を書かず、頂点数・辺数を式で書いた
- 例題 practice2_d の制約も、evidence（ACL のコード）からは分からないので書いていない。解法の詳細の計算量は「マスの数 V」で書いた
- Dinic 法の容量 1 の場合の計算量 O((N+M)√M) は ACL のドキュメントの記載をそのまま使い、証明は書いていない（1 回分が O(N+M) になることと BFS の回数が O(√M) になることを本文で一言だけ述べた）

## 検証の指摘への対応（2026-10-21）

- 1〜6：すべて本文に反映した（流量の定義を「出る量 − 入る量」に、流量が小さいときの例外と ABC318 G の計算量、assert、無限大の書き分け、ABC241 G の辺、落とし穴の最後の項の書き直し）
- 2 の front matter の signs（「頂点数が数百〜数千…」）は catalog 由来なので変えていない。メインへの提案：signs に「流量が定数と分かるなら頂点数が多くても使える」を足すか検討してほしい
- 7（#acl の見出し）：採らなかった。手引き §14-4 との食い違いはメインの判断事項（上の「手引きへの提案」と同じ）。認めない場合は #acl の中身を #algorithms の末尾の囲みに移し、anchor `acl` を残す
- 8（動く図 max-flow-residual）：執筆者の範囲外（JS は頼まれたときだけ）。メインへの申し送り：JS と試験の作成を頼んでほしい。仕様は上の「動く図の仕様」をそのまま使える
- 台帳：検証役の確認により、tessoku_book_bp の `checked` に 2026-10-21 を入れてよい（提案）
