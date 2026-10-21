# subset-enumeration-dp の報告（b2）

- 書いたファイル：docs/dp/subset-enumeration-dp.md、snippets/subset-enumeration-dp/{grouping,partition-count,k-groups}.{cpp,yaml}、docs/img/subset-enumeration-dp/three-states.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 19。問題の行・数式を含む文の長さ・助詞の重なりの誤検出が主）
- 図：three-states.svg を render_svg.py で 360px・720px にして目で確かめた（visual は static・priority 2 なので動く図は作っていない）
- 使った出典：Series_205（Qiita, EDPC U）・drken（ABC187 F・ABC310 D・ABC321 G）・E869120 の GitHub（典型90 045 の sol/045.cpp）・rareshana（Qiita, ABC332 E）。どれも付録 B のドメイン。新しいドメインはない

## 台帳への提案

- abc310_d｜pages の subset-enumeration-dp の approach｜「仲の悪い組を含まない集合を前計算し、ちょうど j 個のチームに分ける方法の数を最小の要素を含むチームから数える（N ≤ 10 なので全列挙でも解ける）」｜drken の記事は全列挙だけを書き、本文中に 3^N の解き方の記述はない（タグだけ）。3^N の方針は本ページの自前の説明である
- typical90_as｜evidence に追加｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/045.cpp ｜jpg の解説の代わりに解答コードで状態と遷移を確かめた（手引き §14-17）
- dp_u・abc187_f・typical90_as・abc321_g｜checked｜2026-10-21｜evidence で問いと方針を確かめた
- abc187_f｜evidence｜usaco.guide の 3 件は構成の参考だけのドメインなので、問題の裏付けからは外してよい

## 用語集への提案

- 部分集合の部分集合（submask）｜submask｜集合 S の部分集合 T のこと。bit で表すと S の 1 の桁だけからなる整数で、T ← (T − 1) AND S で大きい順に列挙できる
- クリーク｜clique｜グラフの頂点の集合で、どの 2 頂点の間にも辺があるもの（本文の例題 ABC187 F で使った。用語集にすでにあればリンクを足したい）

## 手引きへの提案

- §6 の記法で XOR を ⊕ と決めているので、「問題に合わせた二項演算」を一般に書くときの記号（本ページでは ∘ を使った）を決めておくとよい

## 問題の補充の候補

- abc332_e（E. Lucky bag、diff 1883、ap.py で確認）｜N ≤ 15 個の品物を D 個の袋に分け（空の袋も許す）、袋の重さの分散を最小にする｜状態を「入れた品物の集合と袋の数」にし、部分集合を 1 袋にまとめる遷移。空の袋にも値（平均との差の 2 乗）があるので初期値に注意する｜https://qiita.com/rareshana/items/76af4e8d8dcbedfc8714 ・ https://qiita.com/navel_tos/items/7d4db517b8a0c3d4d21b ｜役割は practice を提案（abc319 以降の青で、本文の「グループの数を状態に足す」の「空のグループにも値がある」の型そのもの。本文では問題 ID を出さずに型だけを書いた）

## 未解決の点

- 典型90 045 の制約（N の上限）は解答コードから読めず、本文には書いていない。「2 乗のまま比べてよい」は大小比較の話として書いた
- vs-zeta で触れた「部分集合の畳み込みで O(2^N N^2)」は一般的な事実として書き、出典は付けていない。zeta-mobius-subset か発展のページに持ち主の節ができたら、そこへのリンクに替えたい
- abc321_g の方針で counting-labeled-graphs（stub）へページのリンクを置いた。相手が draft になったら #component-of-1 か #complement へ張り替える（メインの控え）
- chromatic-number（stub）へページのリンクを 2 か所置いた。相手の節 chromatic-number ができたら張り替える
- 申し送り §1 の bit-operations:146・178 のリンクは、本ページの #why-3n（146 行）と #submask-loop（178 行）へ張り替えられる
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 7 回（検索 1 回を含む）

## 検証の指摘への対応（直し）

- 指摘 1〜7 をすべて採った（採らなかったものはない）。図 three-states.svg のラベルは g から T に、partition-count.yaml の cases は n = 0〜10 のすべてにした
- 共有ファイルへの提案：検証の「台帳への提案」（dp_u・abc187_f・typical90_as・abc321_g を checked、typical90_as の evidence に sol/045.cpp を足す）に同意する。部分集合の畳み込みの持ち主の節ができたら、#vs-zeta の記述からリンクを張る
