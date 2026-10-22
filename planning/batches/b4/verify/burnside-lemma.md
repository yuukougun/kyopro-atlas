# burnside-lemma の検証（b4）

- 対象：docs/comb/burnside-lemma.md、snippets/burnside-lemma/necklace.{cpp,yaml}・cube.{cpp,yaml}（図はなし。catalog の visual は null）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、ACL は third_party/ac-library

## 実行した検査

- `python3 tools/check_pages.py --page burnside-lemma`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/burnside-lemma`：コード片 2・期待と違う 0
- `python3 tools/fix_problems.py --check --page burnside-lemma`：直すべき行 0
- `npx textlint docs/comb/burnside-lemma.md`：エラー 0・警告 11（数式・漸化式を含む文の長さと読点、助詞「で」の重複。折りたたみの中の箇条書きが多く、誤検出として妥当）
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で necklace.cpp・cube.cpp をコンパイルして実行：警告・サニタイザの報告なし。`6 4` → `700 430`、`1000000000 3` → `122038410 376068165`、cube に `3` → 型の一覧と `57`
- 一時置き場の chk.py（Python、コード片とは独立に書いた）：
    - $(1/n)\sum_{d \mid n}\varphi(d)k^{n/d}$ と裏返しを含む式を mod 998244353 で計算し、n = 10^9・k = 3 で `122038410 376068165` と一致（cases 4 つ目の期待はプログラムの写しではないことを確認）
    - ABC428 G の形の小さな例（美しさ {2, 2, 3, 4, 6}、U = 60）で、回転の最小表現による全列挙・本文の「最短周期で分類する」式（G(l, m) = F(l, m) − Σ G(e, m^{e/l}) と Σ G(e, x^{e/l})/e）・本文の Burnside の式（Σ_s F(gcd(l, s), x^{g/l}) / l）の 3 つが x = 2..60 のすべてで一致

## 確かめた事実（問題なし）

- 補題の式と証明：(g, x) の組の 2 通りの数え方、「x を y に移す操作は Stab(x) の操作の後に h を施す形にちょうど 1 通りずつ書ける」（h^{-1}g ∈ Stab(x) で存在、h の打ち消しで一意）、軌道と固定部分群の大きさの関係。循環・逆向きの議論はない
- 4 個・2 色の例 (16 + 2 + 4 + 2)/4 = 6 と、列挙した 6 種類：正しい。16/4 = 4 と合わない説明も正しい
- s 個ずらす回転の巡回が長さ n/gcd(n, s) で gcd(n, s) 個、gcd(n, s) = n/d となる s が φ(d) 個（euler-phi#divisor-sum の記述と一致。0 ≤ s < n と 1..n の違いは s = 0 ↔ n で同じ）
- n = 6・k = 4：(4096 + 64 + 32 + 8)/6 = 700。裏返しを含めて (4200 + 3·4^4 + 3·4^3)/12 = 430。n 奇数の軸の巡回 (n+1)/2 個、n 偶数の軸 n/2 + 1 個・n/2 個：正しい
- 赤 2・青 2 の輪：(6 + 0 + 2 + 0)/4 = 2。正しい
- 最短周期の例 f(1) = 2、f(2) = 2、f(4) = 12 → 6。確認問題の 51：両方の方法で正しい。§5 comb の「約数の値から引くときは小さい順」に合う
- 立方体の 5 つの型と個数（1・6・3・8・6）、巡回の長さ：cube.cpp の生成（2 つの 90 度回転の向きのコメントも面の番号と一致）と kmjp 氏の記事の型分けで確認。k = 2 で 10、k = 3 で (729 + 243 + 324 + 72)/24 = 57
- ABC198 F の方程式 5 本と母関数 $x^6/((1-x)^2(1-x^4))$：kmjp 氏の記事（型分けと方程式、24 の逆元、行列累乗）と一致。母関数は x/(1−x)・x/(1−x)・x^4/(1−x^4) の積で正しい
- ABC428 G：kmjp 氏の記事（B[i] ≥ 2 で長さが O(log U)、F・G の定義、G = F − Σ_{d≥2} G(m^{1/d}, l/d)、逆元で l で割る）と ikatakos 氏の記録の解法の節（最短周期で分類、回転を考えない個数が O(U log² U)）で確認。本文の e = l/d の書き方は同じ式。「美しさが 2 以上」（未解決の点 2）は kmjp 氏の記事の B[i] ≥ 2 で裏付けられる。全体 O(U log² U) も F の DP（長さ log U 段 × 調和級数 U log U）から妥当
- 計算量：要点・front matter の complexity・本文が一致。素因数分解 O(√n)、約数ごとの累乗 O(D log n)。divisors_with_phi の約数の生成は O(D) で、本文と矛盾しない
- 「p = 998244353 と n < p なら問題にならない」と、#library の「|G| が法の倍数でないことを確かめる」：条件つきで正しい。necklace.cpp のコメントにも書かれている
- n ≤ 10^18 で divisors_with_phi の途中の値（d·pk·p ≤ n、ph·pk·(p−1) = φ(…) ≤ n）は long long に収まる
- 例題 2 問：`tools/ap.py show` で abc428_g（G. Necklace、diff 2472）・abc198_f（F. Cube、diff 2769）。台帳はどちらも確認済み・role example・pages は本ページだけ。label・URL・diff は本文と一致
- 参考の URL：ja.wikipedia・cp-algorithms（題名 "Burnside's lemma / Pólya enumeration theorem"）・library-checker-problems の number_theory が 200 を返す。kmjp の 2 記事は該当問題の記事。scrapbox.io/pctsnote は `tools/check_noai.py` で noai・noimageai の指定なし（執筆者の結果と一致）で、内容は補題の定義・小さな例・ABC198 F の回転の扱いと 2x + 2y + 2z = S の母関数
- 出典の文章に近すぎないか（F8）：kmjp・pctsnote と並べて読んだ。本文の例（4 個 2 色、n = 6・k = 4、赤 2 青 2、5 個 3 色）は資料の例と別で、言い回しも別
- コード片（C1〜C8）：§9 の書き方（bits/stdc++.h、マクロ・型の別名なし、`'\n'`、ACL の modint）に合う。取り込みの印 core・bracelet と本文が一致（by-period の範囲は本文に取り込まれていないが、§13-9 の範囲で問題なし）。cases に n = 1 と大きい n があり、main の assert で n ≤ 8・k ≤ 3 を全列挙と比べている。本文の「3 つの関数を比べて確かめている」と一致
- front matter：執筆者が変えたのは complexity・stage・updated と sections の library の追加だけ（catalog と比べた）。summary・signs と要点が一致。別名の行に aliases がすべてある
- リンク先の節（counting-dedup#divide・#representative、euler-phi#divisor-sum、divisor-inclusion-exclusion#period、miller-rabin、glossary#fixed-point・#double-counting・#period）は存在し、内容も本文の言及と合う（指摘 1 の 1 か所を除く）

## 指摘

### 1. 直すべき｜事実（F7・リンク）｜#necklace「色の個数が決まっている」の段落の「（[円環の塗り分け](../comb/counting-basics.md#coloring)の例と同じ）」

- 問題：counting-basics#coloring（一列の塗り分けと円環の塗り分け）は「隣り合うものが違う色」の数え方の節で、赤 2 個・青 2 個を輪に並べる例はない。読者がリンクをたどっても「同じ例」が見つからない
- 根拠：docs/comb/counting-basics.md を読んだ。赤 2・青 2 の円形の例（6/4 が整数にならず答えは 2）は 91 行目、節 `## 順列・組合せ・重複順列・円順列 {#permutations}`（72 行目から）の落とし穴の箇条にある。#coloring（95 行目から）には回転の同一視も赤・青の例もない
- 直し方：`（[円順列の落とし穴](../comb/counting-basics.md#permutations)の例と同じ）` のように、リンク先を #permutations にしてリンクの文字も合わせる

### 2. 直すとよい｜分かりやすさ（U3・U6）｜#why-not-divide の 2 段落目「軌道の大きさが $\lvert G \rvert / \lvert \mathrm{Stab}(x) \rvert$ なので」

- 問題：$\mathrm{Stab}(x)$ は #what の折りたたんだ証明の中でだけ定義されている。証明を開かない読者や、この節だけを読む claude.ai には記号の意味が分からない
- 直し方：「$x$ を変えない操作の集合を $\mathrm{Stab}(x)$ とすると、軌道の大きさは $\lvert G \rvert / \lvert \mathrm{Stab}(x) \rvert$ である（#what の証明）」のように、節の中で一言定義する

### 3. 直すとよい｜分かりやすさ（U3）・事実（F2）｜#necklace「色の個数が決まっている」の段落の最後の文「一般に、長さ $L$ の巡回が $c$ 個なら、各色の個数が $L$ の倍数のときだけ多項係数の分だけあり、そうでなければ 0 である」

- 問題：「多項係数の分だけ」がどの多項係数か書かれていない（$\binom{n}{a_1, \dots}$ と読み違えうる）。また「長さ $L$ の巡回が $c$ 個」とすべて同じ長さの場合に限ることが、裏返し（長さ 1 と 2 が混じる）の直後なので読み取りにくい
- 直し方：「回転では巡回の長さがすべて同じ $L$ になる。色 $i$ を $a_i$ 個使うとき、すべての $a_i$ が $L$ の倍数なら、$c$ 個の巡回に色を割り当てる $\frac{c!}{\prod_i (a_i/L)!}$ 通り（多項係数）で、そうでなければ 0 である」のように式で書く。赤 2 青 2 の 2 個ずらす回転で $2!/(1!\,1!) = 2$ と確かめられる

### 4. 直すとよい｜事実（F2）・分かりやすさ（U4）｜例題 ABC198 F の解法の詳細の 4 点目「回さない型は $\binom{S-1}{5}$ のように閉じた式でも書けるが、$S$ が法より大きいと二項係数の前計算は使えない」

- 問題：前計算の表が使えないのは正しいが、$\binom{S-1}{5}$ は 5 個の積 $(S-1)(S-2)\cdots(S-5)$ に $120$ の逆元を掛ければ $S$ が法より大きくても求まる。「閉じた式は使えない」と読めて、漸化式（行列累乗）しか方法がないと誤解させる
- 直し方：「回さない型は $\binom{S-1}{5}$ で、5 個の積に $5!$ の逆元を掛ければ $S$ が大きくても求まる（前計算の表は使えない）。型ごとに閉じた式を作るより、すべての型を同じ漸化式の方法で求める方が場合分けが減る」のようにする

### 5. 直すとよい｜事実（F9・手引き §14-24）｜参考の kmjp（ABC428 G）と ikatakos の題名

- 問題：ブログの題名は記事の h1 にそろえる決まりだが、2 件が短縮されている
- 根拠：kmjp の記事の title は「AtCoder ABC #428 (Promotion of AtCoderJobs) : G - Necklace」。ikatakos の記録の題名は「AtCoder Beginner Contest 428（Promotion of AtCoderJobs）D,E,F,G問題メモ」
- 直し方：それぞれ「AtCoder ABC #428 (Promotion of AtCoderJobs) : G - Necklace」「AtCoder Beginner Contest 428（Promotion of AtCoderJobs）D,E,F,G問題メモ」にする

### 6. 直すとよい｜分かりやすさ（U8・手引き §14-11）｜#by-period の中の確認問題

- 問題：手引き §14-11 は確認問題を `## 確認問題 {#quiz}` にまとめるとしているが、節の中に置いている（ほかのページにも同じ置き方は多く、害は小さい）。また問いが「2 つの方法で求めよ」で、どちらも本文の例と同じ手順の当てはめになっている（U8 の「本文の主張を別の場合に当てる・条件を外す」としては弱い）
- 直し方：`## 確認問題 {#quiz}` を落とし穴の前に立てて移す。余裕があれば「6 個の玉を 2 色で塗る（回転のみ）とき、$2^6/6$ が整数にならない理由と答え 14」や「裏返しも同一視すると 5 個 3 色は何通りか（39）」のように、条件を変えた問いを 1 つ足す

## 図

図はなし。catalog の visual は null（キーがない）なので G7 の不足もない。figure.md の G1〜G6 は対象なし。

## 執筆者の未解決の点について

- 1（ABC198 F の S の上限）：kmjp 氏の記事にも数値はない。本文は「S が大きい」とだけ書いており、このままでよい
- 2（ABC428 G の美しさが 2 以上）：kmjp 氏の記事の「B[i] ≥ 2 より長さは O(log U)」で裏付けられた
- 3（euler-phi の「バーンサイドの補題」の表記）：題名にそろえる直しに賛成（メインが判断）
- 4（ほかのページのリンクの張り替え）：counting-basics:91 の張り替え先は #necklace の「色の個数が決まっている」の段落が合う。指摘 1 と組にして、両方向の参照をそろえるとよい

## 台帳への提案（執筆者の提案の確認）

- abc428_g の summary の直し：kmjp 氏の記事の問題概要（無限個の宝石、回転は同一視・反転は区別、f(2), …, f(U)）と一致。賛成
- abc428_g の evidence に ikatakos を足す：G の解法の節がこの問題のものであることを確認した。賛成
- abc198_f の evidence に pctsnote を足す：ABC198 F の回転の扱いと 2x + 2y + 2z = S の母関数が書かれていることを確認した。賛成
- abc428_g・abc198_f の `checked` に 2026-10-22 を入れる

## 総合の判定

小さな直しで可。直すべき 1 件（指摘 1：リンク先の節の誤り）、直すとよい 5 件。数式・具体例・コード片・例題の方針はすべて確かめられ、事実の誤りはない。
