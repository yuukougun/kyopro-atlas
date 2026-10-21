# min-cost-flow の報告（b3）

- 書いたファイル：docs/graph/min-cost-flow.md、snippets/min-cost-flow/slope.{cpp,yaml}、snippets/min-cost-flow/primal-dual.{cpp,yaml}、docs/img/min-cost-flow/residual.svg・slope.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の acl の title を「ACL の mcf_graph（flow と slope）」に変えた（anchor はそのまま。b1 の A4 に従い囲みを中心にしつつ、topological-sort・scc と同じく中身のある見出しにした）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 本・8 case 一致）、textlint（エラー 0、警告 19。助詞「に」の重複・数式を含む文の長さ・図の代替テキスト・`[l, r)` の括弧の対応の誤検出）。SVG 2 枚は render_svg.py で 360px・720px を目視した
- 使った出典：ACL の document_ja/mincostflow.md（手元の ~/lib/ac-library-master）、ACL の test/example/mincostflow_practice.cpp（手元）、kmjp の abc247_g・abc407_g・abc421_g・abc231_h の記事（付録 B のドメイン）。新しいドメインはない
- 図：visual は priority 2（static）なので、静的な SVG 2 枚（残余グラフの 2 段階・流量ごとの最小コストの折れ線）で代えた。動く図の div は置いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc421_g | summary | 数列と区間の候補が与えられ、候補の区間を選んでその中の全要素に 1 を足す操作をくり返すとき、数列を広義単調増加にするための最小の操作回数を求める（できるかどうかも判定する）。 | https://kmjp.hatenablog.jp/entry/2025/08/30/1000 （差分 D_i = A_{i+1} − A_i をすべて 0 以上にする、と書かれている） |
| abc421_g・abc407_g・abc247_g・abc231_h | checked | 2026-10-21 | 上の kmjp の各記事で問いと方針を確かめた |
| abc421_g | title | 末尾の空白（'Increase to make it Increasing '）は ap.py の値のままか確かめる。fix_problems が作った label には空白が入っていない | — |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 残余グラフ | residual-graph | フローを流した後に、各辺の「まだ流せる量」の順向きの辺と「押し戻せる量」の逆向きの辺を並べたグラフ。最小費用流では逆向きの辺のコストを元の符号を反転したものにする。（本文では max-flow へのリンクで済ませたので、用語集に入れるなら max-flow と共有） |
| 逐次最短路法 | successive-shortest-path | 残余グラフのコストの最短路に流すことをくり返して最小費用流を求める方法。primal-dual 法とも呼ぶ。（ページの節 #successive-shortest-path があるので用語集は不要かもしれない） |

## 手引きへの提案

- §5 graph の「フローは中身よりモデル化を主役に」に、最小費用流の「定数 − 利得」で非負に直すときは「どの 1 単位の流れも定数を足した辺をちょうど 1 回通る層に置く」ことを書くよう足すとよい（燃やす埋める・二部マッチングのページでも同じ言い回しにそろえられる）
- b1 A4（ACL は見出しを立てない）と、sections に anchor: acl がある骨格（max-flow・min-cost-flow）が食い違う。今回は topological-sort・scc にならって中身のある見出し＋囲みにした。max-flow の執筆者にも同じ扱いを伝えるとよい

## 問題の補充の候補

- abc214_h（H. Collecting、diff 3138）：SCC で縮約した DAG の上で K 人の経路を決め、「最初に通った人だけが回収する」を頂点の分割とコストで表す最小費用流。発展の力試し向き。裏付け：https://kmjp.hatenablog.jp/entry/2021/08/16/0930 （research/03-graph §5.2 の表。今回は読んでいない）
- abc224_h（H. Security Camera 2、diff 2887）：LP の双対で読み替えて最小費用流にする。発展向き。裏付け：https://kmjp.hatenablog.jp/entry/2021/10/26/0930 （同上、今回は読んでいない）
- 割当問題の節（発展）の例題は、research でも ABC で必須の問題が見つかっていない。abc373_g は geometry-vectors の力試しにあり、「最小重み完全マッチングには交差がない」という性質の問題なので、本ページの練習に足すなら役割を相談したい
- 練習が 2 問なので、黄の目安（2〜6）の下限。abc319 以降で、重み付き二部マッチング・slope を使う ABC G を ap.py と第三者の解説で探す余地がある（今回は探していない）

## 未解決の点

- abc247_g の制約（大学・得意分野の種類数）は kmjp のコードの配列の大きさ（150）からの推測しかないので、本文には書いていない
- abc421_g の「できない場合」の出力の形（-1 など）は確かめていないので、要約は「できるかどうかも判定する」にとどめた
- abc231_h の方針は kmjp の「流量を 1 ずつ増やし、高い辺を通った分を引いた値の最小をとる」に従った。高い辺を通る回数が流量から一意に決まる理由（f − H と f − W）は本文では細かく書いていない
- Library Checker の assignment の制約（N の上限）は task.md の値が埋め込みの変数で読めなかった。本文では N の上限を書いていない
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 5 回（kmjp 4・Library Checker の GitHub 1）

## 検証の指摘への対応（b3 の直し）

- 1（確認問題の置き場）：「K ごとの答え」を #quiz の「逆辺のコスト」の後へ移した。
- 2（下限を安い辺と高い辺で表す型）：(a) モデル化の節に、高い辺のコスト L をほかのコストの総和より大きくとると安い辺がすべて使われ、高い辺を通る回数が流量から決まるので、流量ごとに引く量を変えればよい理由と、nonnegative-cost の規則との違いを足した。(b) ABC231 H の方針を「slope を 1 回呼び、各 f ≥ max(H, W) で cost − L·((f − H) + (f − W)) の最小をとる」に直した。
- 3（ABC407 G の非負化）：両方の層に B を足し g(F) − 2BF の最小をとる 1 文を足した。
- 4（slope の区間の傾き）：「同じ長さが続いた分はまとめられる」を入れた。
- 5（証明の届かない頂点）：証明の 2 つ目に、届く頂点だけを考えることと、後の段落で上限付きの距離を扱う旨を足した。
- 6（重み付き二部マッチングの本数が自由な場合）：nonnegative-cost の 2 つの直し方を指す 1 文を足した。
- 7（箇条書きの句点）：本文の箇条書き（要点の囲みと参考は除く）の行末に「。」を足した。ほかの draft のページの揺れはメインの判断に任せる。
- 8（residual.svg の文字の大きさ）：左右の 2 枚を上下に並べ（viewBox 310×580）、辺の数字と頂点の文字を 17px に上げた。代替テキストの「左・右」を「上・下」に直した。360px と 720px を render_svg.py で目視した。
- 採らなかった指摘：なし。
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0 行）、check_snippets（2 本一致）、textlint（エラー 0、警告 19）。
