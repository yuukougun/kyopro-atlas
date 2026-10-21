# digit-and-mod の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/digit-and-mod.md、snippets/digit-and-mod/substring-multiple.{cpp,yaml}、docs/img/digit-and-mod/suffix-pairs.svg
- front matter で変えたもの：complexity・stage（draft）・updated（節は足していない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（期待と違う 0）、textlint（エラー 0。警告 26 は数式中の半開区間 `[l, r)` の括弧・数式を含む文の長さと読点の数・「が」「に」の重複 2 件で、規則の誤検出か読みやすさに影響しないもの）
- 使った出典：drken1215.hatenablog.com（abc164_d・abc158_e・abc182_c・abc181_d・arc084_b）、qiita.com/comet725（abc460_e）、ikatakos.com（abc460_e、解説の部分だけ）。新しく noai を確かめたドメインはない（torus711.hatenablog.com は付録 B にあり、下の候補の裏付けに検索結果だけを見た）
- 静的な図：catalog の visual（priority 2）の「接尾辞の余りと同じ余りの位置を線で結ぶ図」を SVG で作った。動く図は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc460_e | summary（本体と alternatives の digit-and-mod・counting-mindset） | N 以下の正の整数の組 (x, y) のうち、x の後ろに y を 10 進で連結した数が、M を法として x + y と合同になるものの個数を求める。 | https://qiita.com/comet725/items/7ac6436793b6e5d1ee4f ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460 |
| abc460_e | approach（digit-and-mod） | y の桁数 d を固定すると条件は x(10^d − 1) ≡ 0 (mod M) になり y が消える。x は M / gcd(10^d − 1, M) の倍数の個数、y は d 桁の数の個数で、積を d について足す | 同上 |
| abc460_e | 備考 | 答えは 998244353 で割った余り、テストケースは複数。本文の要約には入れていない（問いの核だけにした） | 同上 |
| abc181_d | summary | 「数字列 S（1〜9 の数字だけ）の桁を…」と、0 を含まないことを足すとよい（方針の「0 を含む倍数を除く」の根拠になる） | https://drken1215.hatenablog.com/entry/2020/11/02/023700 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 互いに素 | coprime | 2 つの整数 a, b の最大公約数が 1 であること。a と m が互いに素なら、a を掛けても割っても m で割り切れるかは変わらず、a の mod m での逆元がある |

（本文では `../guide/glossary.md#coprime` にリンクした）

## 手引きへの提案

- §6 の記法に「部分文字列を整数とみた値」の書き方がない。本文では $\mathrm{val}(S[l, r))$ と書き、冒頭の記法の行で定義した。数字列を扱う他のページ（prefix-sum-counting の後ろからの累積など）とそろえるなら、手引きに足すとよい
- 数の連結は $\mathrm{concat}(x, y)$、桁数は $d(y)$ と書いた。同じ記号を geometric-series-mod などでも使うなら手引きにそろえるとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc353_d（D. Another Sigma Problem、diff 844） | 数列の i < j のすべての組について、A_i の後ろに A_j を連結した数の総和を 998244353 で割った余りを求める。数の連結の節の「ペアの連結の総和」の型そのもの（本文では問題 ID を出さず型だけ書いた）。練習の候補。diff が基礎の帯なので、練習の最初に置く | https://torus711.hatenablog.com/entry/2024/05/12/202925 （検索結果の要約で、A_j の桁数 d ごとに A_i·10^d が寄与することを確認。本文はまだ読んでいない） |

- abc319 以降の問題は abc460_e が 1 問ある（水の練習）。例題の abc164_d は古いので、接尾辞の余りの型で abc319 以降の問題があれば例題か練習に足したいが、今回は見つけていない

## 未解決の点

- abc460_e の制約（N・M の上限）は第三者の解説から推定した（N は 19 桁程度まで扱う）。本文では「N ≤ 10^18 なら」と条件付きで書き、制約の数値は書いていない
- P が 2・5 を約数に持つ一般の合成数（P = 2^a 5^b Q）の数え方は、自分で導いた方法を短く書いた（第三者の資料では確かめていない）。長さ k 以上の部分文字列が 2^a 5^b で割り切れるかは最後の k 桁で決まること、Q の部分は接尾辞の余りが等しいことで決まることから組み合わせた。検証役に確かめてほしい。どの台帳の問題もこの場合を問わないので、不要なら節から外してよい
- 一般の 7・13 の判定（1001 = 7 × 11 × 13 を使う 3 桁ごとの交互和）は載せていない
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 6 回（WebFetch 4・検索 1・タイトル取得の curl）
