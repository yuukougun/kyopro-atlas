# b5 検証：divisors-and-multiples

- 対象：docs/patterns/divisors-and-multiples.md、docs/img/divisors-and-multiples/multiple-hops.svg（snippets はなし。本文の ```text の擬似コード 1 つだけ）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：図は `python3 tools/render_svg.py divisors-and-multiples --scale 2` で 360px・720px の PNG にして目で確かめた（白の背景つきなのでダークでも読める）。コード片がないので code.md の C1〜C8 は対象なし（擬似コードは C4 のとおり ```text）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page divisors-and-multiples`：エラー 0・警告 0
- リンク先の anchor：本文の `../` で始まるリンク（divisor-enum#enumerate・#candidates・#count-and-sum・#pitfalls、divisor-count-bound#table・#divisor-dp・#enumerate-hcn、harmonic-sum#collect-multiples・#vs-sieve、prime-factorization#procedure・#which-method・#per-prime、spf-sieve#many-numbers・#build-and-factor・#linear-sieve、euler-phi#formula、multiplicative-function#prefix-sums、divisor-inclusion-exclusion#order・#gcd-sum、mobius-function#gcd-one・#vs-divisor-ie、zeta-mobius-divisor#per-prime・#gcd-lcm-convolution・#inverse、prime-exponent-vector#squarefree-kernel・#huge-lcm、stars-and-bars#applications、gcd-lcm#euclid・#lcm-overflow・#prefix-suffix-gcd・#many-numbers、gcd-properties#difference-gcd・#range-gcd・#step-mod、floor-quotient-enum#block-end・#vs-others、integer-division#cpp-vs-math、glossary#coprime、start/notation.md）をスクリプトで照らし、すべてある
- 数値（作業用の場所の Python）：高度合成数の候補の DFS で max d(N) は N ≤ 10^9 で 1344、10^12 で 6720、10^18 で 103680（一致）。Σ_{d≤10^6} ⌊10^6/d⌋ = 13,970,034 ≈ 1.4×10^7、M = 12 の Σ⌊12/d⌋ = 35、Σ_{n≤10^6} √n ≈ 6.7×10^8、1344² ≈ 1.8×10^6、46340² = 2,147,395,600 ≤ 2^31−1 < 46341²（「N ≥ 46340² であふれる」は正確）、2·3·…·31 ≈ 2.0×10^11 ≤ 10^12 < ×37 で異なる素因数 11 種類以下、2^39 < 10^12 < 2^40 で指数 39 以下、d(12) = 6・σ(12) = 28、2×10^5 個 × 1000 回 = 2×10^8：すべて一致
- gcd がちょうど g の式 f(g) = C(c[g],2) − f(2g) − …（大きい順）を、ランダムな列（値 ≤ 30、12 個）で全組の gcd の数え上げと比べて一致
- 定理・性質：約数の対、√N を超える素因数は高々 1 つ、d・σ の公式、gcd(a+x, b+x) = gcd(a+x, b−a)、区間 gcd の値は O(log A) 種類、mod N で A ずつ進むと周期 N/gcd(A,N)、⌊N/i⌋ の値は 2√N 種類以下で区間の右端 ⌊N/q⌋、核が等しい ⇔ 積が平方数、積が N の長さ K の列は素数ごとの C(e+K−1, K−1) の積、GCD 畳み込みは倍数の向き・LCM は約数の向き、f(1) = Σ μ(d)F(d)：どれも正しく、条件（正の整数・0 の別扱い）も書かれている
- 計算量：要点・front matter の complexity・本文が一致（約数列挙と 1 個の分解 O(√N)、倍数たどり O(M log M)、最小素因数の篩 O(M log log M) の前計算＋1 個 O(log M)）。spf-sieve の要点とも一致
- 問題：ABC180 C は drken 氏の記事で「N ≤ 10^12 の約数をすべて小さい順に出力」と確かめ、要約・方針（√N まで、平方数の重複、ソート）と一致。典型90 075 は ebisuke 氏の記事で「魔法 1 回で今あるすべてのボールを同時に叩き、合成数は ab = x（a, b ≥ 2）の 2 個に分かれる、2 ≤ N ≤ 10^12」と確かめ、要約と一致。E869120 氏の sol/075.cpp（素因数を重複込みで数え、2^i ≥ 個数 となる最小の i）と方針が一致。要約に手法名・解き方は入っていない。台帳の typical90_bw の summary は「（執筆時に確かめる）」のままなので、執筆者の台帳への提案（summary と checked 2026-10-22）をメインが反映する必要がある。abc180_c・typical90_bw の checked 2026-10-22 の提案に賛成
- 参考の URL：drken1215.hatenablog.com・zenn.dev・github.com は付録 B にある。ebisuke33.hatenablog.com は付録 B になく、`tools/check_noai.py` で noai・noimageai の指定なしを確かめた（zenn・drken も同じく指定なし）。題名はどれも書かれたとおり。drken 氏の記事は √N までの列挙と i·i = N の重複に触れ、samekard 氏の記事は √N を超える素因数が高々 1 つの理由を場合分けで述べる（書かれたとおり）。ebisuke 氏の記事は指摘 1
- 出典に近すぎないか（F8）：本文の例（M = 12 の図、N = 12 の d・σ、N = 36 の重複）と文の並びは参考の記事と別で、近すぎない
- 執筆者の未解決の点：(1) 表の「代表の問題」をこのページの 2 問だけにしたのは見本（bracket-sequence）と手引き §5 の pattern の決まり（表には label を文字で書き、リンクは表の後の囲み）に合い、patterns の練習 0〜3 の目安にも収まる。(2) 落とし穴の「積が平方数の問題では 0 を核の計算に入れない」は #products の本文（0 は別に数える）と prime-exponent-vector#squarefree-kernel と食い違わない
- 図：値（各行の回数 12・6・4・3・2・2・6、合計 35、144）が本文・代替テキストと一致。360px で文字は約 11.7px で読め、重なり・はみ出しなし。viewBox 400×330 と width・height が同じ比、白の背景、font-family sans-serif、色だけでなく点の大小でも区別。catalog の visual は priority 2 で静的な図で足りる

## 指摘

### 1. 直すべき｜事実（F9）｜#references の ebisuke 氏の記事の説明

- **問題**：説明が「典型90 075 の、回数が ⌈log₂ k⌉ になる理由」だが、記事は√x までの試し割りで素因数を数え、2 の累乗が個数以上になる最小の指数をコードで出すだけで、その回数になる理由は述べていない。参考の説明が資料の中身と合わない。執筆者の台帳への提案（evidence の追加）もこの記事を根拠にしている
- **根拠**：https://ebisuke33.hatenablog.com/entry/typical90-3 の 075 の項（問題の設定・制約・解法の手順・コードはあるが、理由の説明はない）
- **直し方**：説明を「典型90 075 の問題の設定（魔法 1 回ですべてのボールを同時に叩く）と、素因数の個数から回数を出す解答」とする。回数の理由は本文の練習の方針（ボールの数は 1 回で高々 2 倍）に執筆者が自分で書いており、それで足りる

### 2. 直すとよい｜図（G5）・分かりやすさ（U3）｜#properties の図と直後の段落の「跳ぶ回数」

- **問題**：図の右の「回数」・代替テキストの「1 ずつ跳んで 12 回」・本文の「跳ぶ回数が少なくなる」は、どれも訪れる倍数の個数 ⌊M/d⌋ を指すが、図の弧（跳ぶ回数）は 11・5・3・2・1・1・0 本で、弧を数える読者は合計が 35 にならず止まる（d = 7〜12 は 0 回跳んで「1 回」）
- **根拠**：SVG の path の数と、図の「回数」の列の比較
- **直し方**：「回数」を「訪れる数」か「処理する回数」にし、本文も「行ごとに処理する倍数の個数 ⌊M/d⌋」とする。代替テキストも「1 から 12 まで 12 個の倍数を訪れる」のように言い換える

### 3. 直すとよい｜事実（F6）・分かりやすさ（U3）｜#divisor-functions の「線形篩なら d・φ・μ の表を O(M) で作れる」

- **問題**：リンク先の spf-sieve#linear-sieve が示すのは φ と μ だけで、d の作り方（最小素因数の指数を別に持つ）はない。読者がリンク先で d の表の作り方を探しても見つからない
- **根拠**：docs/math/spf-sieve.md の #linear-sieve（節の題「φ・μ の表を同時に作る」、本文も φ・μ の式だけ）
- **直し方**：「線形篩なら φ・μ の表を O(M) で作れる（d も最小素因数の指数を持てば同様）」とするか、d を外す

### 4. 直すとよい｜手引き（§14-11）・分かりやすさ（U6）｜#properties の末尾の確認問題

- **問題**：確認問題が題材の性質の節の中にある。手引き §14-11 は `## 確認問題 {#quiz}` にまとめるとする（§5 の「要所に置き」との揺れがあり、既存のページにも節の中に置いたものが多いので、直すべきとまではしない）
- **根拠**：planning/style-guide.md §14-11
- **直し方**：練習問題の囲みの後か参考の前に `## 確認問題 {#quiz}` を立てて移す（sections には載せない）。今の位置のままにするならメインの判断で可

### 5. 直すとよい｜分かりやすさ（U3）｜#harmonic の見出し「1〜N の各数…」と本文の M

- **問題**：見出しは N、本文と表と冒頭の記法の約束は「値の上限は M」。断片で読む（U6）と N と M が同じものか迷う。執筆者も未解決の点に挙げている
- **根拠**：本文 55 行目の記法の約束（N は 1 つの数、M はすべての数を扱うときの上限）
- **直し方**：sections の title と見出しを「1〜M の各数の約数・倍数を集める」に変える（anchor は harmonic のまま。title の変更はメインの判断）

## 総合の判定

小さな直しで可。直すべき 1（参考の ebisuke 氏の記事の説明が中身と合わない）、直すとよい 4。数値・定理・計算量・リンク・問題の要約と方針はすべて確かめて一致し、図も正しく読める。台帳の typical90_bw の summary は「（執筆時に確かめる）」のままなので、執筆者の提案の反映を忘れないこと。
