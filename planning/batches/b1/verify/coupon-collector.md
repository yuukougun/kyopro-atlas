# coupon-collector の検証（工程8b・バッチ b1）

- 対象：docs/comb/coupon-collector.md、snippets/coupon-collector/expected.{cpp,yaml}・expected-mod.{cpp,yaml}、docs/img/coupon-collector/stages.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page coupon-collector`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/coupon-collector`：2 片・期待と違う 0
- `npx textlint docs/comb/coupon-collector.md`：エラー 0・警告 2（33 行・166 行の文の長さ。執筆者の報告と同じ）
- 数値の手計算：$6H_6 = 6 \cdot 49/20 = 14.7$、$N = 4$ で $1 + 4/3 + 2 + 4 = 25/3$、最後の段階の割合 $4/(25/3) = 0.48$（「約半分」で正しい）、$10^5 H_{10^5} \approx 1.209 \times 10^6$、確認問題 $1 + 1.2 + 1.5 = 3.7$、$N = 2$ の直接計算 $\sum_{t \ge 2} t (1/2)^{t-1} = 4 - 1 = 3$、mod の期待出力 $25 \cdot 3^{-1} \equiv 332748126$。すべて一致
- 執筆者が導いた主張を小さなプログラムで確かめた（Python の Fraction で厳密に計算）
  - 持っている種類の集合を状態にした期待値 DP（自己ループを移項）で、$N = 1..6$ の等確率の $E[T] = N H_N$ と、$K$ 種類そろうまでの $\sum_{k=0}^{K-1} N/(N-k)$ を全 $K$ で照合し、すべて一致。サイコロで 3 種類なら 37/10 = 3.7
  - 確率が違う場合の min-max 包除：$p = (1/2, 1/3, 1/6)$ で $\sum_{S \ne \emptyset} (-1)^{|S|+1} / \sum_{i \in S} p_i = 73/10$ が集合の DP の 73/10 と一致
  - ABC194 D の式 $\sum_{i=1}^{N-1} N/i$ は段階 1 から足す形で本文の説明と合う（ikatakos の解説の「幾何分布を利用する解法」と同じ方針）
- 図：chrome-headless-shell 146 で SVG を等倍（560×256）と、幅 390px の画面（2 倍密度）で画像にした（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-coupon-collector/full.png・narrow.png）。和文も表示され、文字の重なり・はみ出しはない。背景は白で塗られている。箱の幅は 52 × 期待値で、値・ラベルは本文と一致
- 出典：ikatakos の ABC194 のメモ（D - Journey の「幾何分布を利用する解法」「DP解法」の節がある）、drken の ABC078 C / ARC085 C の記事（題名一致。100ms・1900ms・提出 1 回の時間 × 回数の期待値）、E869120 の prob3-4-4.cpp（$\sum_{i=N}^{1} N/i$ の実装）を開き、参考の記載どおりであることを確かめた。atcoder.jp・codeforces.com は開いていない。本文の文の並び・例（サイコロ・コイン・$N = 4$ の図）は出典と別で、近すぎる箇所はない

## 指摘

### 1｜直すべき｜事実・記法（F7）・分かりやすさ（U3）｜要点の「計算量」と front matter の complexity

- **問題**：「mod 998244353 で答えるなら、逆元の計算を含めて $O(N \log p)$」の $p$ は法の意味だが、同じ要点の 1 行上とページ全体で $p$ は成功確率である。読者は「確率の log」と読んで意味が取れない（$p < 1$ なら $\log p < 0$）
- **根拠**：要点の「何ができるか」「計算量」と #geometric の定義。ほかのページ（rational-mod・binomial-precompute）は $p$ を法としているが、このページでは記号が衝突する
- **直し方**：要点と complexity を「$O(N \log \mathrm{mod})$」または「（法を $P$ として）$O(N \log P)$」「$N$ 回の逆元で $O(N \log 998244353)$」のように、確率の $p$ と別の記号にする

### 2｜直すべき｜図（G3）｜stages.svg の文字の大きさ

- **問題**：viewBox の幅 560 に対し、スマホの表示幅（約 358px）では縮尺 0.64 になり、本文の文字（font-size 14）が約 9.0px、見出し（15）が約 9.6px になる
- **根拠**：幅 390px の画面で画像にして確認した（narrow.png）。prefix-sum・complexity-estimation の検証と同じ基準（スマホで 10px 以上）に届かない
- **直し方**：font-size を 16 以上（見出しは 17）に上げる。左のラベルの列（x = 0〜100）は 2 行に折ってあるので、文字を大きくしても横幅 560 のままで収まる見込み。または左の列を詰めて viewBox を 520 前後にする

### 3｜直すとよい｜リンク（F7）｜#geometric・#next-steps の expected-value-dp へのリンク

- **問題**：執筆者は expected-value-dp が stub だとしてページへのリンクにとどめたが、今は draft で `self-loop` の節（「自己ループの移項」）がある
- **根拠**：docs/comb/expected-value-dp.md の sections（anchor: self-loop、stage: draft。同じバッチで書かれている）
- **直し方**：#geometric の「期待値 DP の自己ループの移項と同じもの」と #next-steps の「段階が戻る・飛ぶ」のリンクを `../comb/expected-value-dp.md#self-loop` にする。メインがバッチの終わりに、expected-value-dp の確定後にまとめて直してもよい。inclusion-exclusion（#min-max）と expectation-tail-sum（#waiting-time）はまだ stub なので、執筆者の判断どおりページへのリンクのままでよい

### 4｜直すとよい｜事実（F2）｜#next-steps の min-max 包除の「N が大きくても計算できる」

- **問題**：「部分集合を確率の和ごとにまとめて数えれば、$N$ が大きくても計算できる」は条件が抜けている。確率の和の取りうる値が少ない（各 $p_i$ が整数の重み $w_i / W$ で、$W$ が小さい）ときに限る。一般の実数の確率では和の種類が $2^N$ 通りになりうる
- **根拠**：まとめて数えるには「和の値ごとの、符号付きの部分集合の数」を DP で求める必要があり、その DP の状態数は和の取りうる値の数（重みの合計 $W$）に比例する
- **直し方**：「確率が $w_i / W$（$W$ が小さい整数）の形なら、部分集合を重みの和ごとに DP でまとめて数えられ、$N$ が大きくても計算できる」のように条件を書く

### 5｜直すとよい｜分かりやすさ（U3）・前提（F6）｜#staged の線形性

- **問題**：ページの中心の #staged は期待値の線形性に頼っているが、prerequisites は probability-basics だけで、linearity-of-expectation（order 350）はこのページ（330）より後にある。probability-basics の線形性の記述は「つながり」の 1 行だけで、読者は「独立でない $T_k$ の和でも期待値を足してよい」を知らない可能性がある
- **根拠**：front matter の prerequisites・order、probability-basics の #next-steps
- **直し方**：#staged の 3 つ目の項目に「$E[X + Y] = E[X] + E[Y]$ は $X, Y$ が独立でなくても成り立つ」を 1 文で書く（リンクは今のまま）。または prerequisites に linearity-of-expectation を足す（order との兼ね合いはメインの判断）

### 6｜直すとよい｜リンク（F7）｜導入の「記法と用語の約束」へのリンク

- **問題**：「$H_N = 1 + 1/2 + \dots + 1/N$ を調和数と呼ぶ（記法と用語の約束）」と、調和数の文の後にリンクがあるが、start/notation.md には $H_N$・調和数の定義はない。確率・期待値の記法の節（`#probability`）があるだけである
- **根拠**：docs/start/notation.md の sections（anchor: probability）。$H_N$・調和数は grep で見つからない
- **直し方**：リンクを「期待値を $E[X]$、確率を $P(A)$ と書く（[記法と用語の約束](../start/notation.md#probability)）。」の文の末尾へ移す

### 7｜直すとよい｜分かりやすさ（U5）｜#failures の表の 3 行目

- **問題**：「問われ方」の列に「最初から成功していれば 0 回」、「期待値」の列に「状態ごとに分ける」とあり、ほかの 2 行（問われ方 → 数える量 → 式）と形がそろわない。表の後の文を読まないと何を言っているか分からない
- **根拠**：表と直後の段落
- **直し方**：表は 2 行にし、3 行目の内容は表の後の段落（最初の状態ですでに終わっている場合は場合分けする）だけで述べる。具体例（「すでに条件を満たしていれば 0 回」の問題の形）を 1 つ添えるとなおよい

### 8｜直すとよい｜分かりやすさ（U5）｜#staged の応用の型「段階ごとに確率の形が違う」

- **問題**：例の「当たりの数が段階ごとに決まるくじ」が抽象的で、どんな $p_k$ になるのかが読み取れない
- **根拠**：応用の型の 3 つ目
- **直し方**：式の形が見える例にする。たとえば「$N$ 枚のカードのうち $k$ 枚目まで裏返した段階で、まだ表の $N - k$ 枚から当たりを引く確率が $(N-k)/N$ でなく $(N-k)/M$ の形になる」や、ABC194 D のように「今いる頂点以外から選ぶ」なら $p_k = (N-k)/(N-1)$ になる、など

## 執筆者の未解決の点について

- inclusion-exclusion・expectation-tail-sum：まだ stub なので、ページへのリンクのままでよい（同意）
- expected-value-dp：draft になっている。指摘 3 のとおり `#self-loop` へ直せる
- harmonic-sum へのリンク：harmonic-sum が扱う $\sum N/i = O(N \log N)$ はこのページの $N H_N$ と同じ和なので、「同じ和」としてのリンクは妥当。残してよい
- 台帳の arc085_a の summary の短縮の提案：textlint の警告（166 行）の原因として妥当

## 総合の判定

小さな直しで可（直すべき 2・直すとよい 6）。事実・数値・コード片・出典に誤りはない。直すべきは計算量の記号の衝突（1）と図の文字の大きさ（2）で、どちらも数か所の書き換えで済む。
