# balanced-bst の報告（b4）

- 書いたファイル：docs/ds/balanced-bst.md、snippets/balanced-bst/implicit-treap.{cpp,yaml}、docs/img/balanced-bst/treap.svg・split.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `library`（自作するときの要点と Library Checker）を足し、treap の後に置いた。pbds の title を 60 字以内に短くした（「pb_ds の tree（order_of_key・find_by_order。重複は値と通し番号の組にする）」。anchor は変えていない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直す行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 8：要点の囲みの長い文、`$[l, r)$` の括弧の誤検出、数式を含む長い文、表の読点）
- 図：SVG 2 枚（幅 380）。render_svg.py で 360px・720px を目で確かめた。動く図は作っていない（catalog の visual は null）
- 使った出典：qiita.com/hamamu/items/570e7c36bf73913cbeb8（学ぶための資料）、ei1333.github.io/library/（structure/bbst の一覧）、gcc.gnu.org の Policy-Based Data Structures、github.com/yosupo06/library-checker-problems の data_structure（range_reverse_range_sum・dynamic_sequence_range_affine_range_sum・ordered_set の task.md）、en.wikipedia.org の Treap、練習の裏付けに kyo-pro.hatenablog.com（ABC241 D）・qiita.com/recuraki（ABC241 D の pb_ds 解）・drken1215.hatenablog.com（ARC033 C）。新しく check_noai で確かめたドメイン：yuulis.hatenablog.com（noai・noimageai の指定なし。候補の確認に読んだだけで本文には使っていない）

## 台帳への提案

- abc241_d：pages の balanced-bst の alternatives の evidence に https://qiita.com/recuraki/items/993d08d87084fec671ae（pb_ds の tree による解）がすでに台帳の evidence にあるので変更なし。ただし alternatives の summary に「K ≤ 5」がなく、本文の練習の方針では K ≤ 5 を使った（主の summary の値）。alternatives の summary も主の summary にそろえることを提案する
- arc033_3：evidence に、平衡二分探索木・pb_ds でも解けることを述べた資料として drken の Qiita「k 番目の値を高速に取り出せるデータ構造のまとめ」（https://qiita.com/drken/items/1b7e6e459c24a83bb7fd 。kth-element の参考に既出）を足すことを提案する（evidence が 1 つだけなので §15-6 の 2 つ以上に近づける）

## 用語集への提案

- 通りがけ順｜in-order｜二分木の頂点を「左の部分木 → 自分 → 右の部分木」の順に並べる順序。二分探索木では値の小さい順になる（本文では短く定義し、リンクしていない）
- 期待計算量｜expected-complexity｜乱数を使うアルゴリズムで、入力ごとに乱数についての時間の期待値を取ったもの。どの入力でも成り立つ点で、入力の分布を仮定する平均計算量と違う（本文は「期待 O(log N)」と書き、ならし計算量との違いを本文で述べた）

## 手引きへの提案

- §9 の「std の名前と同じ関数名を作らない」の例に `merge`（`std::merge`）を足すとよい。treap・マージテク・Union-Find の自作で出やすい。コード片では `join` と名付けた

## 問題の補充の候補

- abc392_f（ABC392 F. Insert、diff 1395、台帳では確認済み）：空の列に i を先頭から P_i 番目の位置へ挿入していった後の列を求める。位置で指定した挿入そのものなので、implicit treap で split と merge を N 回行えば素直に解ける（逆順の処理と BIT の方が軽い）。balanced-bst の練習（alternatives として）を提案する。問いの裏付け：https://yuulis.hatenablog.com/entry/ABC-392-F（逆順の処理とセグメント木の解）。treap で解くことを述べた第三者の解説は見つけられなかったので、追加するならメインの判断でよい
- ABC で treap が必須の問題は、research と同じく見つからなかった

## 未解決の点

- 例題は catalog のとおり 0 問
- 学ぶための資料に日本語の treap の入門として iwiwi 氏のスライド「プログラミングコンテストでのデータ構造」（SlideShare）が有名だが、slideshare のドメインを確かめておらず、平衡二分木の章があるかも確かめていないので載せなかった
- 練習 ABC241 D の K ≤ 5 は台帳の主の summary に従った（読んだ 2 つの解説はどちらも K の上限を書いていなかった）
- 使用量の目安：道具の呼び出し 45 回ほど、Web 取得 12 回ほど

## 検証の指摘への対応

- 直すとよい 6 件をすべて採った（採らなかったものはない）
  1. #treap を「親の優先度は子の優先度以上」にそろえ、形が 1 通りに決まるのは優先度がすべて異なるときと書き、等しい組はまれで深さの評価にほとんど影響しないと添えた。コード片の Node の注釈も「親は子以上」にした
  2. split は 1 本の経路、merge は $a$ の右端と $b$ の左端の経路で、時間は深さ（merge は 2 つの深さの和）に比例すると直し、split 後の木にも深さの評価が使えると添えた
  3. ops の取り込みを外し、表への参照と関数名だけにした。node の区間は pull と push だけに絞り（Node の各フィールドは本文で 1 文で説明）、core は残した。snippets の ops の目印は残してある（本文からは使っていない）
  4. 性質の 3 つ目に「集約値には反映済み」と書き、push の位置に「反転の保留は子の入れ替えも push まで遅らせる約束」と書いた。非可換な演算の項に、逆向きの集約値を持つときは保留を付けた時点で自分の 2 つの集約値を入れ替え、push では子の入れ替えと保留の受け渡しだけをする、と約束を書いた
  5. complexity を「split・merge … 区間の総積」にそろえ、導入を「期待 $O(\log N)$」にした
  6. treap.svg・split.svg の D のラベルを辺の上側（y = 56・68）へ、treap.svg の B のラベルを左側へ移した。render_svg.py の 720px で重なりがないことを確かめた
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直す行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 8）
- 台帳への提案は上のとおりで変更なし。検証役の提案（abc241_d・arc033_3 の checked に 2026-10-22 を入れる。K ≤ 5 は未確認）もメインの判断に任せる
