# kth-element の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/kth-element.md、snippets/kth-element/bit-kth.{cpp,yaml}、snippets/kth-element/reverse-insert.{cpp,yaml}、docs/img/kth-element/bit-binary-search.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を見出しに合わせて短くした（anchor と level は変えていない）
  - comparison：「方法の比較（どの方法で K 番目を求めるか）」
  - bit-binary-search：「BIT 上の二分探索の手順（値が 0 以上であることが前提）」
  - reverse-insertion：かぎ括弧を残してそのまま
  - vs-kth-value：「答えの二分探索で K 番目を数える方法との違い」
- 構成の判断：sections の anchor `comparison` は定型の「使い分け」の anchor と同じなので、別の「使い分け」見出しは立てず、方法の比較の節を使い分けとして本文の前半に置いた。sections に載せない中身の節として `## 必要になる場面 {#motivation}` を置いた
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 2 件とも一致。textlint エラー 0（警告 31 は数式の中の括弧・数式を含む文の長さ・囲みの中の行の誤検出）。fix_problems --check はこのページの行は 0 件（ほかのページ offline-queries の 6 行が残っている）
- 図：静的な SVG を 1 枚（visual は priority 2・static）。SVG を画像にする道具が手元になく、見た目は確かめていない（XML として正しいことと、文字が枠に収まる幅は計算で確かめた）。検証役に表示の確認を頼みたい

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc241_d | alternatives（pages: kth-element）の summary | 「数の追加と「x 以下で大きい方から K 番目」「x 以上で小さい方から K 番目」の質問を処理する（K ≤ 5）。」（k を K に。prh の K 番目の規則に合わせる。ordered-set の行は既に K） | 本文の行は手で K に直した。fix_problems が作り直すと k に戻る |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| オフライン | offline | クエリをすべて先に読んでから答える処理の仕方。先読みした値で座標圧縮したり、クエリの順序を並べ替えたりできる。反対に、1 つ答えてから次のクエリが決まるものをオンラインと言う |
| lowbit | lowbit | 正の整数 i を割り切る最大の 2 べき。2 進数で i の最下位の 1 だけを残した値で、C++ では `i & -i` で求まる。BIT の t[i] が受け持つ区間の長さになる |

（本文では用語集へのリンクは半開区間だけで、上の 2 語はまだリンクしていない。足したらリンクしてよい）

## 手引きへの提案

- sections の anchor が定型の anchor（comparison など）と重なるときの扱いを決めてほしい。今回は sections の節を使い分けとして使い、定型の見出しを立てなかった
- 台帳の summary に問題文の変数としての小文字 k があり、prh が「k 番目 → K 番目」でエラーにする。本文だけ直すと fix_problems で戻るので、台帳の summary は K に統一するか、prh の規則を緩めるかを決めてほしい

## 問題の補充の候補

catalog の problems_note のとおり、水の帯で手法をそのまま使う ABC の例題（abc319 以降）がない。ap.py の題名検索（K-th・Kth・Insert・Query など）と Web 検索で探したが、BIT 上の二分探索が主役の abc319 以降の問題は見つからなかった。

| 問題 ID | 何を問うか | 裏付けの URL | 備考 |
| --- | --- | --- | --- |
| abc364_d（diff 1136） | 数直線上の点 B_j ごとに、点の集合 A のうち k_j 番目に近い点までの距離を答える | https://junkobayashi.hatenablog.com/entry/2024/07/28/030800（noai の指定なしを確かめた） | 集合は固定で、距離の答えの二分探索と lower_bound で数える型。このページより kth-value（または vs-kth-value の対比の練習）向き。基礎の帯 |

メインで、abc319 以降の「追加・削除と K 番目」「空きの K 番目」の問題を第三者の解説から探す必要がある。

## 未解決の点

- abc392_f の制約（N の上限）は確かめていない。本文では具体的な値を書かず「数十万だと間に合わない」とした
- arc033_3 で「x 番目が必ず存在する」保証は解説から確かめていない（解法の詳細では存在する前提で書いた。drken の Qiita のコードも存在を前提にしている）
- 外側の二分探索の計算量の目安（Q log^2 N ≈ 6×10^7）は Q = 2×10^5、N = 2×10^5 での計算値

## 使った出典

- https://qiita.com/drken/items/1b7e6e459c24a83bb7fd：方法の比較・arc033_3 の制約（Q, X ≤ 2×10^5）
- https://drken1215.hatenablog.com/entry/2020/02/29/035900：arc033_3 の問い
- https://drken1215.hatenablog.com/entry/2022/12/14/185200：abc281_e の BIT（個数と和）と BIT 上の二分探索、(値, 添字) で座圧してタイを潰さない点
- https://kyo-pro.hatenablog.com/entry/ABC241D-cpp：abc241_d の multiset の方法
- https://yuulis.hatenablog.com/entry/ABC-392-F：abc392_f の逆順の処理と max_right（新しく noai を確かめたドメイン：yuulis.hatenablog.com、指定なし）
- ~/lib/ac-library-master/document_ja/segtree.md・fenwicktree.md、third_party/ac-library/atcoder/fenwicktree.hpp（data が private であること）
- 新しく noai を確かめたドメイン：yuulis.hatenablog.com・junkobayashi.hatenablog.com（どちらも指定なし。付録 B への追加を提案）

## 使用量の目安

- 道具の呼び出し 約 35 回、Web 取得 5 ページ＋検索 1 回

## 検証の指摘への対応（2026-10-21）

- 直したもの：指摘 1（歩幅は 2 べきでなければならない理由を lowbit で書き直し、N 以上の 2 べきから始めても正しいことを添えた。導入の段落にも「step が 2 べき」を足した）・2（飛び越える側だけに直し、確認問題 3 へつないだ）・3・4（試す前は幅 2·step、試した後は幅 step と書き分けた）・5（「①〜④」の印に変え、「答え 7」を下の段へ移し、下の 4 行は本文の箇条書きと重なるので外して縦を 445→395 に縮め、小さい文字を 12→13px にした）・7（bit_floor を cpp-math-functions#bit-functions へリンク）・8・9（数の上限を M と置いて O(Q log M) に。x 番目は存在する前提と断った）
- 採らなかったもの：指摘 6 は位置を変えていない。sections の anchor が comparison で、比較の節が最初に引かれる内容なので今の位置のままがよいと考える。「ACL では」も BIT 上の二分探索の中で書けないことと max_right の代わりを並べるのが読みやすいので節の中に残した。メインの判断を求める
- abc392_f の N の上限（5×10^5）は検証役が確かめたが、本文の「数十万だと間に合わない」は正しいのでそのままにした

### 提案（共有ファイル）

- 手引き §13.1 に「catalog の sections の anchor が定型の anchor（comparison など）と重なるときは sections を優先し、中身の節として置く」と足す（検証の指摘 6）
- 台帳：arc033_3 に `checked: 2026-10-21`（drken の Qiita で Q, X ≤ 2×10^5。存在の保証は未確認）、abc392_f に `checked: 2026-10-21`（Yuulis の記事で N ≤ 5×10^5・1 ≤ P_i ≤ i）
- 台帳：abc241_d の kth-element の summary の k を K に直す（前の報告のとおり）
