# tree-bipartite の報告と提案

- 書いたファイル：docs/tree/tree-bipartite.md、snippets/tree-bipartite/coloring.{cpp,yaml}、docs/img/tree-bipartite/depth-parity.svg
- front matter で変えたもの：complexity（`塗り分け O(N)、2 点の距離の偶奇は 1 回 O(1)`）・stage（draft）・updated（2026-10-21）。sections に `{title: 上位の手法とのつながり, anchor: next-steps}` を足した（基礎の構成の目安に合わせた）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（1 件、期待と一致。プログラムは各クエリを素朴な BFS の距離と、N ≤ 200 では距離が奇数の組の総数を全探索と assert で照合する）、textlint（エラー 0・警告 4。図の代替テキストの文の長さ、「が」「に」の重複の誤検出。173 行目は台帳の summary 由来）
- 図：catalog の visual は priority 2 の static なので、静的な SVG 1 枚（深さの偶奇で塗った 8 頂点の木。奇数の距離のパスを破線、偶数を太線で示し、色の違う組 16・足せる辺 9 を下に書いた）で代えた。描画の道具がなく、目視の確認はしていない（XML として正しいことだけ確かめた）。動く図を後で作るなら、同じ木（辺 0-1・0-2・1-3・1-4・2-5・3-6・5-7）で 2 点を選ぶと深さの和と距離が出る形にすると本文の数値と合う
- 使った出典：hamayan（abc209_d の問いと、偶奇で出会う場所が決まること）、E869120 の 026.cpp（多い方の色から N/2 個）、drken（abc126_d の重みの偶奇で塗る）、gotoki_no_joe（abc398_e の足せる辺と手番の選び方）。どれも付録 B のドメイン。新しく noai を確かめたドメインはない

## 台帳への提案

- abc209_d｜summary｜末尾に「。」を足す｜表記の規則（ほかの行は句点で終わる）
- typical90_z｜summary｜末尾に「。」を足す｜同上
- abc126_d｜summary｜末尾に「。」を足す｜同上
- abc398_e：pages の tree-bipartite に alternatives の summary（「先手と後手のどちらで勝つかを選んで対戦する」）があるが、fix_problems は本体の summary で行を作らなかった（「（fix_problems で埋める）」のまま残った）。本文には本体の summary を手で書いた。alternatives を使う設計なら fix_problems の対応を、使わないなら alternatives の削除を検討してほしい

## 用語集への提案

- 独立集合｜independent-set｜グラフの頂点の集まりで、どの 2 つも辺で結ばれていないもの。木や二部グラフでは片方の色の頂点がそのまま独立集合になる（本文で `../guide/glossary.md#independent-set` にリンク済み）
- 頂点被覆｜vertex-cover｜すべての辺について、両端の少なくとも一方を含む頂点の集まり（本文では語を使わず言い換えた。König の定理のページで要るなら）

## 手引きへの提案

- なし

## 問題の補充の候補

- abc437_g（G. Colorful Christmas Tree、diff 2806）｜木が二部グラフであることを使い、色で頂点を左右に分けて最大流で解く｜https://kmjp.hatenablog.jp/entry/2025/12/20/0930 （調査 04-tree §5.1 にあり、台帳での状態は確かめていない。帯が高すぎるので、置くなら上位の手法とのつながりの参照か、二部マッチング・最大流のページの力試し）
- 基礎のページなので例題 1・練習 2・力試し 1 で足りると判断し、新しい候補は探していない

## 未解決の点

- abc398_e の力試しの方針で「足せる組を最初に列挙して集合で持つ」と書いたが、N の制約は確かめていない（atcoder.jp を開けないため）。gotoki_no_joe の記事は候補の辺を列挙して小さい順に足す実装なので、列挙できる大きさであることは裏付けがある
- 「少ない方の色の頂点だけで全頂点に自分か隣が届く（N ≥ 2）」「一方の色だけで全辺の端点を押さえる」は自分で示した事実で、資料の裏付けはない（証明は本文の 1 文で足りる程度）

## 検証の指摘への対応（verify/tree-bipartite.md）

- 指摘 1（直すべき）：#majority-color の冒頭に「この節と次の節の表の 3 行目は深さの偶奇で塗ったときの話」と条件を足し、#cross-pairs の 1 段落目にも、重みの塗り方では 1・2 行目だけが成り立つことを書いた
- 指摘 2（直すべき・台帳）：メインへの提案。data/problems.yaml の abc398_e の evidence から https://kmjp.hatenablog.jp/entry/2025/03/25/0930 （ABC398 G の記事）を外し、https://www.cnblogs.com/Melville/p/18787412 か https://junkobayashi.hatenablog.com/entry/2025/03/23/224334 （N ≤ 100 の記述あり）を足す。あわせて abc209_d・typical90_z・abc126_d の checked に 2026-10-21 を入れる（検証役の提案）
- 指摘 3：#cross-pairs の 1 段落目で $a$・$b$ を定義し直し、参照先を [距離の偶奇](#distance-parity) に直した
- 指摘 4：「歩道」を「ウォーク（頂点の繰り返しを許す道。graph-basics#terms へのリンク）」にした。prh.yml への提案：サイト全体で「歩道」→「ウォーク」にそろえる（thinking/parity.md 137 行目などに「歩道」が残る）
- 指摘 5：図の黒の節点と節点の枠を #333333 にした（白い番号の文字はそのまま）
- 採らなかったもの：なし
