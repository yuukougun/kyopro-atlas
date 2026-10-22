# online-convolution の報告（b4）

- 書いたファイル：docs/math/online-convolution.md、snippets/online-convolution/product.{cpp,yaml}、snippets/online-convolution/online.{cpp,yaml}、docs/img/online-convolution/cdq-order.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 足した定型でない見出し：`## 学ぶための資料 {#resources}`（stirling-first などの発展の概要にそろえた。sections には載せていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（2 本）、textlint エラー 0・警告 15（数式を含む文の長さ、`[l, r)` の半開区間の括弧の対応、数式を含む文の助詞の重なりの誤検出）
- 図：cdq-order.svg（幅 400）を render_svg.py で 360・720 の幅に描いて目で確かめた。catalog の visual は null なので動く図の置き場は作っていない
- 使った出典：drken1215.hatenablog.com（ABC213 H・ABC352 G・ABC281 Ex の記事）、kmjp.hatenablog.jp（ABC213 H・ABC352 G）、nyaannyaan.github.io（Relaxed Convolution）、github.com（library-checker-problems の task.md・info.toml、NyaanNyaan/library のファイル一覧）、judge.yosupo.jp（問題ページの存在だけを確かめた）。新しく noai を確かめたドメインはない（すべて付録 B にある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc281_h | summary | レベル 1 の宝石が A 種類あり、種類の違う宝石を合成して上のレベルの宝石を作れるとき、作れるレベル N の宝石の種類数を求める。 | https://drken1215.hatenablog.com/entry/2023/01/07/162412 |
| abc281_h | approach | 因子が前のレベルの答えで決まる多項式の積の係数を、オンラインの分割統治 FFT（公式）か、直近の因子をためて一定個数ごとに畳み込む平方分割で求める | 同上 |
| abc352_g | evidence | https://kmjp.hatenablog.jp/entry/2024/05/05/0900 を追加（キューで 2 つずつ掛ける積の分割統治） | 同左 |
| abc213_h | evidence | https://kmjp.hatenablog.jp/entry/2021/08/15/0930 を追加（時間の軸の分割統治と NTT） | 同左 |
| abc213_h | checked | 2026-10-22 | 上の 2 つの記事 |

- abc281_h の summary は、合成の細かい規則（材料の個数とレベルの関係）を書いていない。drken 氏の記事の言い換えでは「レベル n の宝石はレベル n 未満の種類の違う n 個から作り、レベル 2 以上は各レベル 1 個まで」だが、問題文で確かめられないので要約は粗くした
- abc281_h の第 2 の裏付けは見つけられていない（kmjp 氏の記事の URL を当てられなかった）

## 用語集への提案

- relaxed convolution（両側オンラインの畳み込み）｜relaxed-convolution｜畳み込む 2 つの列のどちらも、前の項の結果を見てから次の項が決まる畳み込み。$c_i$ を $a_0, \dots, a_i$ と $b_0, \dots, b_i$ が分かった時点で返す。（本文ではリンクせず短く説明した）

## 手引きへの提案

- 発展の概要で「Library Checker に手法そのものの問題がない」ときに、FPS の問題（Inv・Exp）を漸化式に直して確かめる、と書いてよいかの方針があるとよい（今回はそう書いた）

## 問題の補充の候補

- abc357_g（G. Stair-like Grid、diff 3159）：catalog の problems_note のとおり、手法の分類（Nyaan の解説一覧）でしか確かめていない。問いと解き方の第三者の解説は今回読んでいないので、追加は提案しない
- 例題 2・練習 1 で発展の概要の目安（例題 0〜2）に収まっているので、新しい候補は探していない

## 未解決の点

- front matter の frequency_evidence に「recent 1（abc462_g）」とあるが、台帳の abc462_g は inclusion-exclusion の力試しで、解き方は「FPS で項をまとめる」になっている。このページの手法（積の分割統治）を使うかは確かめていない
- summary・要点の「次数の小さいものから2つずつ掛けて」は、本文では「添字で半分に分ける分割統治、または優先度付きキューで次数の小さい 2 つを掛ける」の 2 通りとして書いた。どちらも同じ計算量になる
- fps-basics は draft だが本文の見出しがまだないので、anchor なしでリンクした
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 約 13 回

## 検証の指摘への対応

- 指摘 1（直すべき）：#online の自作の要点 4 つ目を、$l = 0$ の区間と $l > 0$ の区間の両方の足し方（$l > 0$ では同じ畳み込みを 2 倍して足す）を書く形に直した
- 指摘 2：計算量を $O((N + D) \log (N + D) \log N)$ とし、本文に「各因子の次数が 1 以上なら $O(D \log D \log N)$」を添えた。要点・complexity もそろえた
- 指摘 3：小テスト 2 問目の答えを $4 \times 10^{10}$ 回ほどに直した
- 指摘 4：図 cdq-order.svg の右の箱のラベルを「右へ足す」から「受け取る」にした
- 指摘 5：summary は執筆者が変えない項目なので、提案としてメインに上げる（下）

## summary の提案（検証の指摘 5）

- 現：多数の多項式の積を次数の小さいものから2つずつ掛けて O(N log² N) で求める。…
- 案：多数の多項式の積を、半分ずつに分けて（または次数の小さいものから）2つずつ掛けて O(N log² N) で求める。dp[i] が dp[0..i−1] と既知の列の畳み込みで決まるときは、左半分を確定させてから右半分へ寄与を足す分割統治で求める。
