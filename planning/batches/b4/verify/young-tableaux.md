# young-tableaux の検証（b4）

- 対象：docs/comb/young-tableaux.md、snippets/young-tableaux/hook.{cpp,yaml}、docs/img/young-tableaux/hook-lengths.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-22

## 確かめたこと

- `python3 tools/check_pages.py --page young-tableaux`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/young-tableaux`：期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）。手でも `-std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルし、警告・サニタイザの報告なし。入力 `3 / 4 3 1` の出力は 70 で本文と一致
- `python3 tools/ap.py show abc378_g`：G. Everlasting LIDS、diff 3051。台帳・囲みの label・diff と一致
- 本文の数値を手で計算し直した：(4,3,1) のフック長 6,4,3,1 / 4,2,1 / 1、積 576、8!/576 = 70。(2,1) は 2、(3,3) は 720/144 = 5 = C_3。3×3 はフック長の積 8640、9!/8640 = 42、42² = 1764。20! ≈ 2.43×10^18 < 2^63−1 < 21!。p(30) = 5604・p(50) = 204226 は partition-number の #size と一致
- 例題の条件と解法を Python の全探索（一時置き場の g.py）で確かめた：A, B ≥ 2、AB ≤ 9 の 6 通りで、「末尾に n + 0.5 を足して LIS・LDS がともに保たれる n が存在する」順列の数（2・10・10・70・70・504）が、「r 行目の A 列目 > r+1 行目の A−1 列目」の条件を DP（置く位置が A 列目のとき、下の行がすでに A−1 個あることを要求）で数えた P の数 × Q のフック長公式の値と一致した。量化を「すべての値」と読むと、最大より大きい値で LIS が増えるので答えは常に 0 になり、執筆者の「ある値」の判断は妥当
- 追い出しの経路は右下の空き (B, A) で終わるときだけ両方の長さが保たれる（足せる角は (1, A+1)・(B+1, 1)・(B, A) の 3 つ）。1 行目では P[1][A−1] < x < P[1][A] を満たす x = P[1][A−1] + 0.5 が必ずとれるので、条件は P だけのものになる。本文の記述と合う
- 状態数：B×A に収まる形の数は C(A+B, B)。AB ≤ 120 の範囲で最大は約 65 万（A=10, B=12）で、遷移 B 本を掛けても間に合う
- en.wikipedia の Robinson–Schensted correspondence：逆順で P が転置されること、LDS が 1 列目の長さであること、Greene の定理（「高々 k 本の増加部分列の和集合の最大の大きさ = λ1 + … + λk」）を確かめた。Hook length formula：Greene-Nijenhuis-Wilf のフックウォークの確率的証明、全単射の証明、カタラン数への言及がある
- 参考の 4 つの外部 URL（en.wikipedia 2 件・kmjp・ikatakos）は 200 を返す。ikatakos の G の解法の節は RS 対応・(f^λ)² の説明で、本文の例（形 (4,3,1)・(3,3)・3×3）と例は別のもの。文の並びも近くない（F8）
- 本文中のリンク先 anchor（partition-number #enumeration・#size、reflection-principle #catalan、lis #binary-search、binomial-precompute）はすべて存在する
- 図：`python3 tools/render_svg.py` で 360px・720px の PNG にして目で確かめた。文字の重なり・はみ出しなし。値は本文と一致、白の背景あり、viewBox と width・height の比が同じ、幅 300。代替テキストで値とフックの範囲が分かる
- 執筆者の未解決の点：(1) 「ある値」の量化は上の全探索で妥当と確認。(2) 逆順で転置されることと Erdős-Szekeres の説明は wikipedia と形の議論で正しい。(3) 対合の数を書かなかったことは問題なし

## 指摘

### 1. 直すとよい｜clarity（U3）・fact（F7）｜#hook-length の「自作するときの要点」の 1 つ目

- 問題：前の節で分割を $\lambda_1, \lambda_2, \dots$（1-indexed）と定義しているのに、ここの式 $h(i, j) = (\lambda_i - 1 - j) + (\lambda'_j - 1 - i) + 1$ は「0-indexed」で $\lambda_i$ が 1 行目を $\lambda_0$ と読む前提になっている。読者は $\lambda_1$ を 1 行目と覚えたまま読むので、1 つずれる
- 根拠：#what の定義 $\lambda = (\lambda_1 \ge \dots)$ と、コード片の `lambda[i]`（0-indexed）
- 直し方：1-indexed のまま $h(i, j) = (\lambda_i - j) + (\lambda'_j - i) + 1$ と書くか、「行・列を 0 から数え、$\lambda_i$ も 0 行目から数えるとき」と添える

### 2. 直すとよい｜clarity（U3）｜#hook-length の冒頭のフック長の定義

- 問題：「その箱の右にある箱の数と下にある箱の数」は、右下の領域全体と読む余地がある。図を見れば分かるが、断片で読んだとき（U6）に誤読しうる
- 直し方：「同じ行で右にある箱の数と、同じ列で下にある箱の数」とする

### 3. 直すとよい｜clarity（U2）｜#abc378_g の解法の詳細の 1 つ目

- 問題：「追い出されるのは各行の末尾の値でなければならず」に理由がない。また、1 行目に入れる値がいつでも選べる（条件が P だけになる）ことが書かれていない。代わりに「手元の全探索により確かめた」が理由の位置にある
- 根拠：追い出しの経路は行が下がるごとに同じ列か左へ動くので、最後に B 行目の A 列目に着くには、どの行でも A 列目を通るしかない。1 行目は P[1][A−1] と P[1][A] の間の値（n + 0.5 の形）が必ずとれる
- 直し方：上の 2 文を足し、全探索の一文は「手元の全探索でも確かめた」と補助の位置に下げる（手引き §15-11 の書き方に合わせる）

### 4. 直すとよい｜clarity（U4）｜#abc378_g の解法の詳細の 2 つ目

- 問題：「置く行の長さが上の行の長さを超えない遷移だけを許し」は、置く前の長さか置いた後の長さかが曖昧。また「追加の大小関係を破る置き方」を状態だけで判定できる理由（A 列目に置くとき、下の行がすでに A−1 個あるか）が書かれていない
- 根拠：上の検証の DP は「置く前に上の行が真に長い」「A 列目に置くときは下の行の長さが A−1」で 6 通りすべて一致した
- 直し方：「置いた後も上の行より長くならない」とし、「r 行目の A 列目に置くのは、r+1 行目がすでに A−1 個そろっているときだけ」と 1 文足す

### 5. 直すとよい｜fact（F2）｜導入の「ABC での出題は difficulty 3000 前後の G 問題の 1 度だけである」

- 問題：全数を確かめた主張になっているが、根拠は研究メモと執筆者の探索だけで、言い過ぎになりうる
- 直し方：「このサイトで確かめた ABC の出題は〜の 1 問だけ」のように範囲を付ける

### 6. 直すとよい｜clarity（U6）｜#partitions の最後の段落

- 問題：「上で触れた順列の逆順に対応する」が別の節（#robinson-schensted）を指し、節を 1 つだけ読むと何のことか分からない
- 直し方：「順列を逆順にすると RS 対応の $P$ が転置される（[RS 対応](#robinson-schensted)）ので、分割の転置は順列の逆順に対応する」とする

### 7. 直すとよい｜fact（F2）｜#robinson-schensted の Greene の定理

- 問題：「$k$ 本の増加部分列の和集合」は、wikipedia の述べ方「高々 $k$ 本」と少し違う（N < k のときなどにずれる）
- 根拠：en.wikipedia の Robinson–Schensted correspondence（"the union of at most k increasing subsequences"）
- 直し方：「高々 $k$ 本」とする

## 台帳への提案について

- abc378_g の summary・approach・evidence の提案は、本文と上の全探索に合うので賛成する。問題文は検証役も読んでいないので、`checked` を入れるかはメインに任せる（ikatakos の記事の問題文の節は使わない）

## 総合の判定

小さな直しで可（直すべき 0 件、直すとよい 7 件）。事実・数値・コード片・図に誤りは見つからなかった。
