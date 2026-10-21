# fractional-binary-search（平均・中央値の最大化）執筆の報告と提案

- 書いたファイル：docs/basics/fractional-binary-search.md、snippets/fractional-binary-search/average-subarray.{cpp,yaml}・median-subarray.{cpp,yaml}、docs/img/fractional-binary-search/lines.svg・median.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件とも期待どおり。別に 400 件の乱択で全探索と照合済み）、textlint（エラー 0、警告 15。数式を含む文の長さ・`[l, r)` の括弧の対応・`$(4, 1)$` の読点など規則の誤検出と、「割り算も個数も」の助詞の重なり）
- 図：静的な SVG 2 枚（visual は priority 2）。描画の確認はできていない（手元に SVG を画像にする道具がない）ので、検証役に見た目の確認を頼みたい。生成スクリプトは一時置き場の gen_svg.py

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc469_e | summary | o と x からなる文字列で、o を K 個以上含む連続した区間を選ぶとき、区間に占める o の割合の最大値を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0801_abc469 （解説の部分。問題文の題材の言い回しは確かめていないので、文面は検証で調整してよい） |
| abc469_e | approach | o を 1・x を 0 にして平均の最大化に帰着し、答え a を二分探索して、a を引いた累積和と「o を K 個以上含む左端」の範囲の最小値で判定する | 同上 |
| abc203_d | approach（補足） | 中央値は大きい方から ⌊K²/2⌋+1 番目。「x 以下の個数 ≥ K² − ⌊K²/2⌋」で判定する | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc203-d.html （コードから読んだ） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 中央値 | median | 値を小さい順に並べたときの真ん中の値である。個数 m が偶数のときは中央の 2 つのどちらを取るか（小さい方から ⌈m/2⌉ 番目か ⌊m/2⌋+1 番目か）を問題ごとに定める。 |
| 分数計画 | fractional-programming | (Σa)/(Σb) の形の比を最大（最小）にする問題。答え x を決めて Σ(a − x·b) の符号を判定する二分探索や Dinkelbach 法で解く。（任意。別名の行にだけ出るので、なくてもよい） |

本文の `../guide/glossary.md#median` は提案した anchor で書いた。

## 手引きへの提案

- §8 の SVG：作業環境に SVG を画像にする道具（rsvg-convert・cairosvg・playwright など）がなく、執筆者が見た目を確かめられない。用意するか、「見た目の確認は検証役が行う」と明記してほしい
- ikatakos 氏の記録は「問題文を引用した節を読まない」とあるが、WebFetch では節を選んで読めない。今回は要約の指示で「問題文の引用部分は除く」と頼んだ。この取り方でよいかを決めてほしい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 水のページに abc319 以降の問題が abc469_e と abc324_f の 2 問ある（abc324_f は 2023-10 で 7 問体制）ので、手引き §10 の目安は満たしている。今回は新しい候補を探していない
- 練習に平均の易しい形（連続部分列の平均で長さの下限つき）が台帳にない。ABC の候補が見つかれば補いたい（未調査）

## 未解決の点

- arc101_b（ARC101 D）の区間の中央値の定義（偶数長で大きい方か小さい方か）と、全区間の個数に対する必要数を第三者の解説で確かめきれなかった（drken 氏の記事は本文とコードで「以上／以下」「≥／>」が食い違う）。そのため本文と方針では定義に依存する不等号を書かず、「問題文から読む」とした
- abc469_e の題材（o と x が何を表すか）は確かめていない。要約は文字列の形で書いた
- abc236_e の中央値の定義（偶数個は小さい方）は oraclesqlpuzzle のコードの判定（X 以上が N/2+1 個以上）から読んだ。本文の練習の方針は「偶数個は小さい方を取る定義なので和が正」と書いた
- Dinkelbach 法の「反復は二分探索より少なく済むことが多い」は一般的な理解として書いた（OI Wiki は収束速度を述べていない）
- 使い分けの「値を更新しながら中央値を保つ」は top-k-sum などのページがまだ決まっていないのでリンクしていない

## 使った出典

- ikatakos（ABC469 D,E,F,G 問題メモ）、oraclesqlpuzzle（ABC203 D・ABC294 F・ABC236 E）、drken（ABC324 F・ABC034 D・ARC101 D・ARC026 D）、OI Wiki「分数规划」（構成の参考のみ）。どれも付録 B のドメインで、新しいドメインはない

## 使用量の目安

- 道具の呼び出し約 30 回、Web 取得 12 回（WebFetch 10・検索 1・題名の取得 1 回で 8 URL）

## 検証の指摘への対応（2026-10-21）

- 1〜9 はすべて直した。1 は置き換えた値を $d_i$、選んだ集合を $T$ にした（累積和の $S$ は前提のページに合わせて残した）。9 は C のラベルを直線の左下（x ≈ 0.1、縦軸の近く）へ移した
- 10（台帳）は共有ファイルなので直さず、提案として次に書く

### 台帳への提案（検証の指摘 10）

- `data/problems.yaml` の abc469_e・arc026_4・abc236_e の `checked` に 2026-10-21 を入れる（検証役が evidence で方針を確かめた）
