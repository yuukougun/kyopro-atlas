# two-pointers の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/two-pointers.md、snippets/two-pointers/at-most-k-kinds.{cpp,yaml}、snippets/two-pointers/at-least-k-sum.{cpp,yaml}、docs/img/two-pointers/window-staircase.svg
- front matter で変えたもの：complexity（`O(N)（区間への出し入れが O(1) のとき。両端とも合計 N 回しか動かない）`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 21。数式の中の `[l, r)` を括弧の対応の誤りと見るもの、数式を含む文の長さ、数式の中の読点の数で、いずれも誤検出）
- コード片は Python の全探索とランダムな 400 ケースで突き合わせた（一時置き場で実施）
- 図：静的な SVG（各 l に対する区間 [l, r(l)) を帯で並べた階段の図）。SVG を描画する道具が手元になく、見た目は目で確かめていない。検証役に描画の確認を頼みたい
- 動く図（catalog の visual は priority 1）は作っていない。置き場の div を「単調性の見抜き方」の節に置いた：`<div class="kp-viz" data-viz="two-pointers" data-config='{"array": [1, 2, 1, 3, 1, 1, 2], "K": 4, "mode": "at-most"}'></div>`
  - 図の仕様：列の上に区間 [l, r) の窓を描き、1 ステップごとに「r を 1 つ伸ばす（和が K 以下のまま）」か「伸ばせないので l を 1 つ進める」を行う。各ステップの caption に l・r・和と、どちらを動かしたかを書く。下に各 l に対する r(l) の単調な折れ線（3, 3, 4, 5, 7, 7, 7）を、l を進めた時点で 1 点ずつ足す。mode は将来 "at-least"（和が K 以上の型）を足す余地として置いた

## 使った出典

- drken（qiita）「しゃくとり法 (尺取り法) の解説と、それを用いる問題のまとめ」：2 つの型、空区間の扱い、二分探索との関係
- drken（hatenablog）ABC130 D・ABC326 C・ARC022 B・ABC153 F・ABC098 D（ARC098 D）：例題・練習・力試しの問いと方針
- oraclesqlpuzzle ABC032-C：0 の場合分けと積の尺取り
- E869120 典型90 sol/034.cpp（github raw）：個数と種類数の持ち方の確認
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

- abc130_d｜checked｜2026-10-21｜https://drken1215.hatenablog.com/entry/2019/06/17/004300 で問いと方針を確かめた
- abc326_c｜checked｜2026-10-21｜approach を「左端を点に合わせてよいので、ソートして各点から長さ M の範囲の右端を尺取り（または lower_bound）で求める」に具体化してもよい｜https://drken1215.hatenablog.com/entry/2023/11/11/204912
- typical90_ah・abc032_c・arc022_2・abc153_f・arc098_b｜checked｜2026-10-21｜各 evidence で問いと方針を確かめた
- abc153_f｜approach｜「まだ倒れていない最も左のモンスターを左端に含むように爆弾を置く貪欲。効果の切れる座標と回数をキューで管理する（またはいもす法）」に具体化してもよい｜https://drken1215.hatenablog.com/entry/2020/01/26/234000

## 用語集への提案

- 空区間｜empty-interval｜左端と右端が等しい区間 $[l, l)$。要素を 1 つも含まない。尺取り法・累積和で、区間の長さが 0 になる場合の扱いに注意が要る（本文ではリンクしていない。必要ならメインで判断）
- 半開区間（half-open-interval）は既存の anchor にリンクした

## 手引きへの提案

- §5 basics の「尺取り法は右端を進めても左端が戻らない理由」は、実際には「左端を進めても右端が戻らない理由」が本文の主役になる（単調なのは各 l に対する r(l)）。表現を直すとよい
- コード片で「部分区間も満たす型は右端の for、より大きい区間も満たす型は左端の for」と書き分けた。ほかのページ（kth-value・meet-in-the-middle など）で尺取りを使うときに書き方をそろえるなら、このページを参照するよう手引きに一言あるとよい

## 問題の補充の候補

catalog の数（例題 1・練習 4・力試し 2）で足りているので必須ではない。次は節の内容に合う候補（ap.py で実在と difficulty を確かめていない。research 01 に載っているもの）。

- abc172_c（Tsundoku、930）：累積和と尺取り（片方を増やすともう片方が減る 2 つの列の尺取り）。台帳では prefix-sum の練習。二分探索との関係の節の練習にも合う｜https://blog.hamayanhamayan.com/entry/2020/06/27/230511
- abc124_d（Handstand、1138）：ランレングスの塊の列で固定個数の窓を尺取り。台帳では run-length-encoding の例題。本文の「使い分け」で型だけ触れた｜https://drken1215.hatenablog.com/entry/2019/04/14/222900
- abc319 以降の尺取りの問題（frequency_evidence の abc452_f・abc461_d・abc470_g など）は台帳に未登録。水のページではないので必須ではないが、近年の例として練習に 1 問あると良い（第三者の解説での裏付けはまだしていない）

## 未解決の点

- abc130_d の制約（$a_i$ の範囲、$K$ の上限）は evidence のページで確かめきれなかった（取得した範囲に N の制約しか見えなかった）。本文は「正の整数列」（台帳の summary）と「和と答えは long long」だけを書き、K の上限は書いていない
- abc032_c の制約は evidence のページの数式が読めず、$K, s_i \le 10^9$ は推定。落とし穴の節の「$K \le 10^9$・$a_i \le 10^9$ なら」は条件付きの一般論として書き、問題の制約としては書いていない
- 「負の値で和が K 以上を数える」の BIT による方法は、本文で一般論として 1 行だけ触れた。BIT のページへのリンクは付けていない（id を確かめていないため）。メインで `../ds/fenwick-tree.md` などに当てるとよい
- monotonic-stack は stub なので、手引き §7 によりページへのリンクだけにした。draft になったら `#sliding-window-minimum` を付けてほしい

## 検証の指摘への対応（2026-10-21）

- 1・2・3・4・5・7・8・9：本文を直した（1 はコード片のコメントも「区間 [l, r]（a[r] を入れた後）」に）
- 6：担当ページの 2 か所のリンクを `../ds/monotonic-stack.md#sliding-window-minimum` にした（front matter の related はすでに anchor 付き）
- 10：図の目盛りの font-size を 13 から 15 に上げ、ラベルを「添字」から「境界」にし、代替テキストに「上の数字は区間の端の位置」と足した
- 11：採らなかった（執筆者の担当外）。提案：メインが `overrides/assets/js/viz/two-pointers.js` と `tests/viz/` を報告の仕様（各 l の r(l) = 3, 3, 4, 5, 7, 7, 7）で作るか、それまで kp-viz の div と直後の段落（「動く図では…」）を外す
