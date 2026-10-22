# divisors-and-multiples の報告と提案（b5）

- 書いたファイル：docs/patterns/divisors-and-multiples.md、docs/img/divisors-and-multiples/multiple-hops.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を題材の性質の後に足した（見本 bracket-sequence と同じ一覧の節）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0、textlint エラー0（警告10：数式を含む文の長さ、助詞「に」の重複の誤検出など）
- 図：multiple-hops.svg（visual priority 2 の静的な図。M = 12 で各 d から d ずつ跳ぶ弧、行ごとの回数、合計 35）。render_svg で 360px・720px を目で確かめた
- 使った出典：drken1215（ABC180 C）、github E869120 sol/075.cpp、ebisuke33.hatenablog.com（新しく check_noai で確認：noai・noimageai の指定なし）、zenn.dev/samekard_dev（典型90 075）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
|---|---|---|---|
| typical90_bw | summary | 整数 N が書かれたボールがあり、1 回の魔法で、素数でないボールをすべて同時に、積が元の数になる 2 以上の 2 つの整数のボールに分ける。すべてのボールが素数になるまでの最小の回数を求める。 | https://ebisuke33.hatenablog.com/entry/typical90-3 、https://github.com/E869120/kyopro_educational_90/blob/main/sol/075.cpp |
| typical90_bw | evidence（追加） | https://ebisuke33.hatenablog.com/entry/typical90-3 、https://zenn.dev/samekard_dev/articles/417f487b654394 | 同左 |
| abc180_c | checked | 2026-10-22（drken の記事で問いと解法を確かめた） | https://drken1215.hatenablog.com/entry/2020/10/21/194700 |
| typical90_bw | checked | 2026-10-22 | 同上 |

## 用語集への提案

- 乗法的関数｜multiplicative-function はページの id と同じなので語の項目は不要かもしれない。用語集に置くなら：乗法的関数｜multiplicative｜互いに素な a, b について f(ab) = f(a) f(b) が成り立つ整数の関数。約数の個数 d、約数の和 σ、オイラーの φ 関数、メビウス関数 μ がその例である。（本文ではリンクせず括弧で定義した）
- 核（平方因子を除いた核）｜squarefree-kernel｜n の素因数分解で指数が奇数の素数だけを掛けた数。ab が平方数であることは、a と b の核が等しいことと同じ。（prime-exponent-vector で「核」と呼んでいる。用語集の squarefree の項に一言足す形でもよい）

## 手引きへの提案

- pattern のページで、題材の性質に「1 つの大きな数か、1〜M のすべての数か」のように N と M の 2 つの文字を使い分けた。整数論の案内では「1 つの数 N、値の上限 M」（harmonic-sum の M に合わせた）を記法の提案として start/notation に載せてはどうか
- 骨格の section の title「1〜N の各数の約数・倍数を集める」は N のままにした（anchor・title を変えないため）。本文の中では値の上限を M と書いている。title を「1〜M の…」に変えるかはメインの判断に任せる

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 一覧の表で代表の問題が「—」の行が多い（gcd がちょうど g・倍数を回す・積が平方数など）。patterns は練習 0〜3 の目安なので補充は必須ではない。各行の代表は、リンク先の手法のページの例題・練習にすでにある（harmonic-sum・divisor-inclusion-exclusion・prime-exponent-vector など）ので、新しい問題は探していない。必要なら、表の「代表の問題」列に他ページの例題を label で書いてよいか（bracket-sequence は「このページに載せたものだけ」とした）の決まりがあると補充しやすい

## 未解決の点

- 表の「代表の問題」は見本に合わせてこのページの 2 問だけを書いた
- 落とし穴の「積が平方数の問題では 0 を核の計算に入れない」は prime-exponent-vector#squarefree-kernel の見出し（0 の扱い）に合わせた要約で、持ち主はそのページ

## 検証の指摘への対応

- 指摘 1（直すべき）：直した。ebisuke 氏の記事の説明を「典型90 075 の問題の設定（魔法 1 回ですべてのボールを同時に叩く）と、素因数の個数から回数を出す解答」にした。台帳への提案の evidence にこの記事を挙げるのは、問題の設定の裏付けとしてであり、回数の理由の裏付けではない
- 指摘 2：直した。図の右の列の見出しを「個数」、下の 2 行を「1 個ずつ」「35 個」にし、代替テキストと本文も「訪れる倍数の個数 ⌊M/d⌋」に言い換えた。図の前に「右の数は、その行で訪れる倍数の個数である」を足した
- 指摘 3：直した。「線形篩なら φ・μ の表を O(M) で作れる。d も、最小素因数の指数を別に持てば同じように作れる」とした
- 指摘 4：直した。確認問題を `## 確認問題 {#quiz}`（参考の前）に移した（sections には載せていない）
- 指摘 5：直した。sections の title と見出しを「1〜M の各数の約数・倍数を集める → 倍数を回す調和級数（harmonic-sum）」にした（anchor は harmonic のまま）。docs/index/patterns.md の題は gen_site で作り直されるので、メインの再生成で追随する。「手引きへの提案」の 2 つ目（title を N のままにした件）はこれで不要になった
- 採らなかったもの：なし
