# b5 報告：method-comparison（似た手法の使い分け）

- 書いたファイル：docs/guide/method-comparison.md（snippets・図の画像はなし。図は Mermaid のフローチャート 1 つ）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。textlint エラー 0・警告 3（確認問題の折りたたみ 2 か所と参考の 1 行で、折りたたみの中の文がつながって数えられた文の長さの誤検出）。自前のリンク検査で、相対リンクの全 anchor が相手のページにあり、stub のページ（reverse-index-signs・reverse-index-constraints・stress-testing・dp-speedup-overview・kth-and-median・subsequence-and-substring）へはページへのリンクだけにしたことを確かめた
- 構成：hub の形（節ごとに「状況 → 使う手法 → 計算量またはページ」の表と、組の見分け方の短い説明）。中身は各ページの節へリンクした。表の数値・計算量は各ページの front matter の complexity と使い分けの節にそろえた
- 使った出典：cp-algorithms「0-1 BFS」（計算量と BFS との使い分けを確かめただけ。文章は使っていない）、drken「k 番目の値を高速に取り出せるデータ構造のまとめ」（Qiita）、ACL document_ja（手元の v1.6）。新しく noai を確かめたドメインはない（どれも付録 B にある）

## 台帳への提案

- なし（guide は問題を持たない。catalog の problems も空）

## 用語集への提案

- なし。使った用語集の anchor（offline・forced-online・triangle-inequality・shortest-path-tree・inverse-element・idempotent・associativity・coprime）はどれもある

## 手引きへの提案

- §4 に type guide の構成の目安がない。method-comparison は hub の形（表とリンクが本体）で書いた。「guide の比較のページは hub に準じ、節ごとに『状況 → 使う手法 → 計算量 → ページ』の表と、組の見分け方を 2〜4 文」と足すとよい
- 使い分けの表で、手法のページへのリンクを「使う手法」の列に入れるか「ページ」の列に分けるかが節によって違う（計算量の列を置いた節は手法の列にリンクを入れた）。列を 4 つまでに抑えるためで、統一するなら手引きで決めてほしい
- 各ページの `## 使い分け` から「全体の比べ方は似た手法の使い分けにある」とページへリンクしている箇所（warshall-floyd・zero-one-bfs）は、本ページが draft になったので節へ張り替えられる：warshall-floyd:296 → `method-comparison.md#shortest-path`、zero-one-bfs:269 → `method-comparison.md#shortest-path`

## 問題の補充の候補

- なし（guide は問題を載せない）。最短路木と最小全域木の違いは、既存の例題の小見出し（shortest-path-dag#abc252_e・minimum-spanning-tree#abc218_e）へのリンクで示した

## 未解決の点

- フローチャートは Mermaid（CDN 読み込み）で書いた。図の前後に分かれ道を文章でも書いたので、読み込めなくても内容は通じる。catalog の visual は priority 2 の static なので SVG にはしていない。SVG が要るなら後で描く
- フローチャートは「全点対か → DAG か → 負の辺 → 重みが等しいか → 0 と 1 か」の順にした。research の判断の順序（重み → 始点 → 制約 → 状態 → 辺の削減）と並びが違うが、本文の「判断の順序」の箇条書きは research の順のままにし、図は分かれ道の数を減らすために全点対を先に置いた
- 「数の扱い」に二項係数の計算方法の表を足した（catalog の指示にはないが、research/07 §6.2 の使い分けにあり、binomial-precompute の節がそろっているため）。不要なら外す
- ベルマンフォード法の制約の目安を「$N$ と $M$ が数千まで」と書いた（research/03 の「N, M ≤ 数千」に合わせた）。$NM \le 10^7$ 程度という数値は書いていない

## 検証の指摘への対応（verify/method-comparison.md）

- 1〜4（直すべき）：すべて直した。最短路 DAG に「重みがすべて正なら」の条件、判断の順序の一文を「負の辺がないと決まった後は、重みが等しい・0 と 1・非負の順に前提が弱く遅い手法」に、文字列の表はワイルドカードとハミング距離（$O(\sigma (N + M) \log (N + M))$）の 2 行に分け、BIT の最小値は「値が小さくなる更新だけのとき」に限った
- 5：図の前の文を「1〜2 段に DAG かどうかを加えて分かれ道にすると」に言い換え、図が扱う範囲（制約・状態・辺の数・時刻は 3〜6 段で見る）を 1 文足した
- 6：分かれ道と葉のラベルを短くした（「全点対か」「N ≤ 400 程度か」「DAG か」「重みが等しいか」「0 と 1 だけか」「始点ごとに下の手法」）。形（flowchart TD）は変えていない
- 7・8：指摘どおり直した（「始点から届く負閉路を経由して届く頂点」、2-SAT は割り当ても求められる）
- 10：逆元の用語集リンクを観点の表（62 行）に移し、区間の集約の節はリンクなしにした
- 9：担当ページの中なので自分で張り替えた（reverse-index-signs#by-phrase・reverse-index-constraints#constraint-table・segment-tree-graph#cover・kth-and-median#overview・stress-testing#procedure・dp-speedup-overview#shape-to-tool・subsequence-and-substring#overview）。warshall-floyd・zero-one-bfs から本ページの `#shortest-path` への張り替えは他のページなので、上の手引きへの提案のとおりメインに任せる
- 採らなかったもの：なし
