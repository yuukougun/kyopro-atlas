# kth-value の検証（b2）

- 対象：docs/basics/kth-value.md、snippets/kth-value/pair-product.{cpp,yaml}・top-m-sum.{cpp,yaml}、docs/img/kth-value/count-staircase.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page kth-value`：エラー 0・警告 0
- `python3 tools/fix_problems.py --check --page kth-value`：直すべき行 0
- `python3 tools/check_snippets.py snippets/kth-value`：2 本・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `npx textlint docs/basics/kth-value.md`：エラー 0・警告 6（数式の中のカンマと文の長さ、折りたたみの中。誤検出として残してよい）
- サニタイザ：両方を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、乱数の小さな入力 600 組ずつ（値の範囲 ±3・±10・±10^9、負と 0 を含む）を全列挙と比べた。食い違い 0、サニタイザの報告 0
- 速さ：pair-product を N = 2×10^5、|a_i| ≤ 10^9 の乱数で 0.36 秒
- abc341_d の上限 2KP：N, M < 60（N ≠ M）、K ≤ 30 の全部で「K 番目 ≤ 2KP」を全列挙で確かめた（反例なし）。本文の場合分けの議論も正しい
- 本文の数値：図の count(x)（0, 1, 3, 3, 4, 6, 6）、確認問題 3 つ（{3,3,3,8} の K = 2、{9,7,7,7,2} の M = 2 で 30 と 16、符号の表の a = (-3,-1,0,2,5)・x = -2）、log2(2×10^18) ≈ 60.8 → 約 61 回、N = 2×10^5 で組が約 2×10^10・順序付きで 4×10^10。すべて正しい
- why-count の 2 つの理由、「未満」で数えたときの「x 未満の個数 < K となる最大の x」、0 始まりで「≥ K+1」、大きい方から K 番目の言い換え、上位 M 個の和で「c < M」となる理由を、定義から確かめた。正しい
- リンク：binary-search#lower-bound・binary-search-answer#monotonicity・integer-division#floor-ceil・cpp-integer-overflow#overflow-check・greedy-priority-queue#k-best・kth-element#vs-kth-value・fractional-binary-search#ratio は、どれも draft で anchor がある。wavelet-matrix は stub で、anchor なしのリンク（§14-23 どおり）
- 問題：ap.py で abc341_d（829）・abc155_d（1845）・abc205_d（713）・arc037_c（1824、参考値）・abc149_e（1905）・abc364_d（1136）を確かめた。label・diff・要約は台帳と一致
- evidence（すべて付録 B のドメイン。題名は h1 と一致）
  - oraclesqlpuzzle abc341-d：題は「ABC340-D Only one of two」で中身は abc341_d、式 `x/A + x/B - 2(x/LCM)`。制約は記事にない（未解決 2 のとおり）
  - drken abc155_d：2 ≤ N ≤ 2×10^5、|A_i| ≤ 10^9、符号で場合分け、(S − T)/2。本文と一致
  - drken arc037_c：N ≤ 30000、K ≤ N^2、1 ≤ a_i, b_j ≤ 10^9。本文の「値はすべて正」「ok = 10^18 でよい」と一致
  - drken abc205_d：A は単調増加、前計算 C_i = A_i − i（1 始まり）。本文と一致
  - hamayan abc149_e：M 番目の値の二分探索、`(M − getCount(ok+1)) * ok + getSum(ok+1)`。本文の top-m-sum と同じ形
  - 追加で読んだ kmjp「AtCoder ABC #149 : E - Handshake」（https://kmjp.hatenablog.jp/entry/2019/12/30/0900 、付録 B）：x = y を許し、x と y が逆順のものは別の組とみなす、と書かれている（未解決 1 の答え。下の指摘 2）
- 図：`python3 tools/render_svg.py kth-value`（360px・720px）と `--width 1000 --scale 2` で PNG にして目で見た。白い背景・viewBox・テキストのまま・ハッチと「可／不可」の文字で色だけに頼らない。文字の重なり・はみ出しなし。360px でも数字が読める。値は本文・代替テキストと一致。catalog（patterns.yaml の visual：「x 以下の個数」の階段で高さ K を初めて超える x）の意図を満たす
  - 備考（ページの問題ではない）：render_svg.py の 720px の PNG は高さ 378px で切れ、最下段の矢印と「可の最小 x = 2 が答え」が写らなかった（360px では写る）。撮影の画面の高さが足りないとみられる。道具の側の問題としてメインに伝える
- 執筆者の未解決の点
  1. abc149_e の組の数え方 → kmjp の記事で「同じ人を含む順序付きの組（N^2 通り）」と確かめた。台帳の summary の提案は正しい（指摘 2）
  2. abc341_d の制約 → 確かめられる資料は見つけていない（oraclesqlpuzzle には制約がない）。本文が制約の数値を書かず、上限 2KP を N ≠ M だけから導いた点は正しい（指摘 4 で一言の追加を勧める）
  3. 「約 61 回」→ V ≈ 2×10^18 の値として正しい。ほかのページの「約 60 回」（10^18）と食い違いではない。直さなくてよい

## 指摘

### 1. 直すべき｜事実（F2）｜落とし穴「負の数の割り算」（123 行）

- 問題：「C++ の `/` は 0 の向きに切り捨てるので、$x < 0$ で `x / a[i]` は $\lfloor x / a_i \rfloor$ と一致しないことがある」と、ずれる条件を $x < 0$ に限っている。実際には $x$ と $a_i$ の符号が違い、割り切れないときにずれる。このページの主題は負の $a_i$ を含む積なので、$x > 0$・$a_i < 0$ の場合こそ起きる
- 根拠：$x = 5$、$a_i = -2$ で `5 / -2` は $-2$、$\lfloor 5 / (-2) \rfloor = \lfloor -2.5 \rfloor = -3$。$x < 0$ でも $a_i < 0$ なら（例 $-5 / -2$ は 2、$\lfloor 2.5 \rfloor = 2$）一致する
- 直し方：「$x$ と $a_i$ の符号が違い、割り切れないとき（例：`5 / -2` は $-2$ だが $\lfloor -2.5 \rfloor = -3$）、`x / a[i]` は $\lfloor x / a_i \rfloor$ と一致しない」のように条件を直す

### 2. 直すとよい｜事実・分かりやすさ（F5・U7）｜力試しの方針 ABC149 E（185 行）、参考

- 問題：組の数え方を「問題文で確かめる」と読者に任せ、どちらとも書いていない。方針が「何を数えるか」を決めないので、読者は top-m-sum のコードをそのまま当ててよいか判断できない
- 根拠：kmjp の解説（付録 B のドメイン）に、x = y を許し、逆順を別の組とみなすとある。hamayan の解説のコードも i = j を含む順序付きの組を数える。2 つの独立した解説が一致する
- 直し方：方針に「組は同じ人を含む順序付きの N^2 通りなので、[上位 M 個の和](#top-m-sum)のコードで b = a とした形になる」と書く。参考に kmjp の記事を足し、台帳の evidence に kmjp の URL を足す提案を報告に入れる（summary の直しの提案はこのままでよい）

### 3. 直すとよい｜事実（F2・F7）｜落とし穴「個数と積のオーバーフロー」（125 行）

- 問題：「値が $10^{18}$ 近くまでの列どうしの積は `long long` にも収まらない」は、あふれる境目を大きく見誤らせる。`long long` の上限は約 $9.2 \times 10^{18}$ なので、絶対値が約 $3 \times 10^9$ を超える値どうしでもうあふれうる
- 根拠：$(3.1 \times 10^9)^2 \approx 9.6 \times 10^{18} > 2^{63} - 1$
- 直し方：「値の絶対値が約 $3 \times 10^9$ を超えると、積は `long long` にも収まらない」とする

### 4. 直すとよい｜分かりやすさ（U4）｜例題 ABC341 D の解法の詳細（144 行）

- 問題：ok の番兵を $2KP$ にすると書くが、それが `long long` に収まるかに触れていない。読者は自分の制約で確かめる必要があることに気づきにくい
- 根拠：本文は制約の数値を書いていない（執筆者の未解決 2）。上限の議論そのものは全列挙で確かめた（反例なし）
- 直し方：「制約の範囲で $2KP$ が `long long` に収まることを確かめる（約 61 回という回数もこの大きさからである）」の 1 文を足す。制約の数値は、資料で確かめられるまで書かない

### 5. 直すとよい｜コード（C3）｜snippets/kth-value/top-m-sum.cpp 111〜112 行

- 問題：本文は「$t$ より大きい値の個数 $c$」と書くが、コードの変数名は `above` で、本文の記号と対応が取りにくい
- 根拠：本文 top-m-sum の節「その個数 $c$ は $M$ 未満」「答えは … $+ (M - c) \times t$」
- 直し方：`long long c = count_ge(t + 1);  // t より大きい値の個数（m 未満）` とし、出力を `sum_ge(t + 1) + (m - c) * t` にする（count_ge の中の局所変数 `c` は `cnt` などに変える）

### 6. 直すとよい｜分かりやすさ（U3）｜数え方の型の確認問題（93 行）

- 問題：「並べ済みの」はあまり使わない言い方で、$a_0$ が 0-indexed であることも断りがない（本文はそれまで $a_i$ の添字の始まりを言っていない）
- 直し方：「ソート済みの $a = (a_0, \dots, a_4) = (-3, -1, 0, 2, 5)$（0-indexed）」のように書く

## 台帳への提案（検証役から）

- abc341_d・abc155_d・abc205_d・arc037_c・abc149_e の `checked` に 2026-10-21 を入れる（evidence で問いと解き方を確かめた）
- abc149_e の evidence に https://kmjp.hatenablog.jp/entry/2019/12/30/0900 を足す（組の数え方の裏付け）
- 執筆者の abc364_d の追加の提案：ap.py で実在・題名・diff 1136 を確かめた（解説の中身は読んでいない）

## 総合の判定

小さな直しで可。直すべき 1 件（落とし穴の割り算のずれる条件）、直すとよい 5 件。コード片は全列挙との比較とサニタイザで誤りなし、図・数値・問題の対応も正しい。
