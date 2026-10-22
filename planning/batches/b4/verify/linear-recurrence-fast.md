# b4 検証：linear-recurrence-fast

- 対象：docs/math/linear-recurrence-fast.md、snippets/linear-recurrence-fast/recurrence.{cpp,yaml}（図はなし。catalog の visual は null）
- 観点：fact.md・code.md・clarity.md・figure.md（図がないので figure.md は対象外）
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0

## 実行して確かめたこと

- `python3 tools/check_pages.py --page linear-recurrence-fast`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/linear-recurrence-fast`：7 case 一致
- コード片を `-fsanitize=address,undefined` つきでコンパイルし、d ≤ 120 のランダムな 60 件（n に 0・1・d−1・d・2d・10^18 までの乱数、係数と初項に 0 を含む）で動かした：assert（Bostan-Mori・素朴なきたまさ法・直接の計算・Berlekamp-Massey で見つけ直した漸化式の一致）がすべて通り、サニタイザの報告もなし
- `berlekamp_massey` を、連立一次方程式（法 998244353 の掃き出し）で求めた「与えた項をすべて満たす最短の長さ」と比べた：長さ 0〜10 の列 20 万件（0 が多い列・先頭に 0 が続く列・漸化式から作った列・でたらめな列を混ぜた）で、返す長さが最短と一致し、返す係数が全項を満たす。長さが伸びるときだけ prev を更新する条件 `i - cur.size() > shift - prev.size()` は「新しい長さ i − shift + |prev| が今の長さより大きい」と同値で、正しい
- `bostan_mori` を、deg P < deg Q・Q(0) ≠ 1 を含む一般の P/Q で冪級数の割り算と比べた：2 万件一致。p が空のとき 0 を返す処理も正しい（d = 0 の漸化式で使われる）
- ABC300 Ex の方針（bit が 0 なら偶数側、1 なら偶数側と奇数側の和）：K ≤ 5・N ≤ 200 の 300 件で、m AND N = m の a_m の和の愚直な計算と一致
- 計算の主張：$L(x^i \Phi) = 0$ からの $a_N = L(x^N \bmod \Phi)$、フィボナッチの例 $x^3 \equiv 2x + 1$・$a_3 = 2$、$V(x) = Q(x)Q(-x)$ が偶関数、$\deg V_e = K$・$\deg U_e, \deg U_o < K$（$\deg U \le 2K - 1$ から）、$N = 0$ で $P(0)/Q(0) = a_0$、Cayley-Hamilton から $A^i v$ の成分が $\Phi$ の係数の漸化式を満たすこと、2K 項で最短の漸化式が定まること：どれも正しい
- 計算量：要点・complexity・本文（きたまさ法 $O(K^2 \log N)$、Bostan-Mori $O(K \log K \log N)$、素朴な掛け算で $O(K^2 \log N)$、Berlekamp-Massey $O(M^2)$）が一致。TDPC の $2 \times 10^6 \times 30 = 6 \times 10^7$ も合う
- Fiduccia との比較：ryuhe1 氏の Qiita（本人の解説）に Fiduccia $3\mathsf{M}(d)\lceil\log(N+1)\rceil$、Bostan-Mori $2\mathsf{M}(d)\lceil\log(N+1)\rceil$ とあり「約 2/3」は正しい（下の指摘 5 は出典の書き方だけ）。同じ記事に、TDPC のような $\Gamma(x) = x^d - \sum x^n$ では Fiduccia の方が速くなりうるとあり、本文の「きたまさ法でも同じ計算量」と矛盾しない
- ACL：document_ja/convolution.md（v1.6）で、`convolution` の要件（m は素数、$2^c \mid m - 1$ かつ $\lvert a \rvert + \lvert b \rvert - 1 \le 2^c$）、計算量 $O(n \log n + \log m)$、空配列なら空を返すこと。`vector<modint998244353>` の左辺値を渡す使い方も通る
- Library Checker：library-checker-problems の task.md・info.toml（raw.githubusercontent.com）で、kth_term は $d \le 10^5$・$k \le 10^{18}$、find_linear_recurrence は $N \le 10^4$、consecutive_terms は $d \le 10^5$・$k \le 10^{18}$・$M \le 5 \times 10^5$、法はどれも 998244353。題名も本文と一致
- 問題：`python3 tools/ap.py show` で tdpc_fibonacci（T. フィボナッチ・diff なし）、abc436_g（G. Linear Inequation・diff 2164）、abc300_h（Ex. Fibonacci: Revisited・diff 3209）。label・diff が本文と合う
- 問題の内容：drken 氏の 2 記事（数式の画像の引数を読んだ）で、TDPC は $F_1 = \dots = F_K = 1$、$2 \le K \le 1000$、$1 \le N \le 10^9$、法 $10^9+7$。ABC300 Ex は $a_0 = \dots = a_{K-1} = 1$、$1 \le K \le 5 \times 10^4$、$0 \le N \le 10^{18}$、m AND N = m の和、法 998244353。本文・執筆者の台帳の提案と一致。kmjp 氏の記事も問いが同じ。ABC436 G は ikatakos 氏の解法の節（問題文の節は読んでいない）で $[y^M] \frac{1}{(1-y)\prod(1-y^{A_i})}$、分母の次数は約 $10^4$、Bostan-Mori で $O(d \log d \log M)$。rui_er 氏は DP＋Berlekamp-Massey＋Bostan-Mori で $O(D^2 + D \log D \log M)$。本文の方針・別解と一致
- 参考の URL：10 件すべて 200 で、題名・著者が本文と一致。arxiv.org は付録 B にないので `tools/check_noai.py` で確かめた（noai・noimageai の指定なし）。atcoder.jp の URL は問題の囲みの中だけ
- F8：drken 氏の TDPC の記事も 0-indexed に直して Bostan-Mori を使うが、本文の言い回しと式の並べ方は別物で、近すぎない
- front matter：変えたのは complexity・stage・updated だけ。要点と summary は食い違わない。別名の行に aliases 5 つがそろう
- 執筆者の未解決の点：(1) consecutive_terms の「多項式の逆元と組み合わせる工夫が要る」は、Bostan-Mori の変形で $a_k, \dots, a_{k+d-1}$ を求めてから、その $d$ 項と $Q$ で作った分子 $P'$ について $P'/Q$ を冪級数の逆元で $M$ 項展開する方法に当たり、発展の概要として誤りではない。(2) fps-basics へのページのリンクは、相手の節ができたら張り替えればよい。(3) 例題の並び（diff なしの TDPC を先）は妥当

## 指摘

### 1. 直すべき｜事実（F2）・記法（F7）｜#implementation の箇条書き「$P$ を $K$ 項で切る」

- **問題**：「$A(x) Q(x)$ を切らずに使うと、$P/Q$ が元の数列にならない」は、本文の記号のままでは誤り。#bostan-mori で $A(x) = \sum_{i \ge 0} a_i x^i$（無限の級数）と定義しているので、$A(x) Q(x)$ は切らなくても次数 $K$ 未満の多項式で、ちょうど $P(x)$ に等しい。切らないと困るのは、最初の $K$ 項だけの多項式 $a_0 + \dots + a_{K-1} x^{K-1}$ と $Q$ の積（次数 $2K - 1$ まで）である
- **根拠**：#bostan-mori の「$A(x) Q(x)$ の $x^n$（$n \ge K$）の係数は 0」から、$A(x)Q(x)$ には次数 $K$ 以上の項がない。後半の文「切るのは最初の $K$ 項と $Q$ の積の、次数 $K$ 以上の部分」とも食い違う
- **直し方**：「最初の $K$ 項の多項式 $a_0 + \dots + a_{K-1} x^{K-1}$ と $Q$ の積を切らずに使うと、次数 $K$ 以上に余分な項が残り、$P/Q$ が元の数列にならない」のように、何と何の積かを本文の記号で言い直す

### 2. 直すとよい｜事実（F4）｜#implementation の「ACL では」と箇条書き「法が 998244353 でないとき」

- **問題**：「ACL の `convolution` はそのままでは使えない」は言い過ぎ。`convolution<m>` は NTT に向く素数なら 998244353 以外でも使える（ACL のドキュメントの要件は「m は素数、$2^c \mid m - 1$ かつ $\lvert a \rvert + \lvert b \rvert - 1 \le 2^c$」）。使えないのは $10^9 + 7$ のように $m - 1$ が 2 で多く割れない法である。囲みの「mod 998244353 の」も、既定の値であることが分からない
- **根拠**：~/lib/ac-library-master/document_ja/convolution.md の (1)(2) の宣言と要件
- **直し方**：囲みを「既定は mod 998244353（テンプレート引数で NTT に向くほかの素数も指定できる）」とし、箇条書きの見出しを「法が NTT に向かないとき（$10^9 + 7$ など）」にする

### 3. 直すとよい｜具体例（F3）・読みやすさ（U9）｜#vs-matrix 第 1 段落

- **問題**：「$K = 100$ なら $10^6 \times 60$」は $\log N \approx 60$（$N \le 10^{18}$）、「$K = 1000$ では $10^9 \times 30$」は $\log N \approx 30$（$N \le 10^9$）で、同じ文の中で $N$ の想定が変わっている。「$10^9 \times 30$ を超えて」も何を超えるのかが読み取りにくい
- **根拠**：$\log_2 10^{18} \approx 60$、$\log_2 10^9 \approx 30$
- **直し方**：$N \le 10^{18}$ にそろえ、「$K = 1000$ なら $10^9 \times 60$ 回ほどになり間に合わない」とする

### 4. 直すとよい｜飛躍（U3）｜#implementation の箇条書き「Berlekamp-Massey の項数」

- **問題**：「誤った漸化式でも assert は通る」の「assert」がどれを指すか分からない（コード片の assert か、読者が自分で書く確かめか）。読者には「与えた項に合っているかの確かめは、項が足りないと誤った漸化式でも通ってしまう」という要点が伝わりにくい
- **根拠**：本文の取り込み範囲（bostan-mori・berlekamp-massey）には assert がない。コード片の main の assert は完全なプログラムを開かないと見えない
- **直し方**：「見積もった項数の 2 倍より少ないと、返った漸化式が与えた項にすべて合っていても、その先で外れることがある。確かめるときは与えた項より先の値で比べる」のようにまとめる

### 5. 直すとよい｜出典（F9）｜#bostan-mori の「Bostan と Mori の論文によると、掛け算の回数は Fiduccia の方法のおよそ 3 分の 2」

- **問題**：arXiv の要旨は「Fiduccia と定数倍を除いて同じ計算量で、より速い」とだけ言い、3 分の 2 の数字は出典に挙げた ryuhe1 氏の Qiita（$3\mathsf{M}(d)$ 対 $2\mathsf{M}(d)$）で確かめられる。本文の書き方では、読者が論文の要旨を開いても数字が見つからない
- **根拠**：https://arxiv.org/abs/2008.08822 の Abstract、https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a の冒頭と「Fiduccia のアルゴリズムと Bostan–Mori のアルゴリズム」の節（論文の本文の PDF は手元に読む道具がなく確かめていない）
- **直し方**：「考案者の解説（ryuhe1 氏の Qiita）によると」とするか、論文と並べて挙げる

### 6. 直すとよい｜分かりやすさ（U2）・問題（F5）｜#abc436_g の方針と解法の詳細

- **問題**：方針と解法の詳細で、分母の次数 $D = 1 + \sum A_i$ がどれくらいの大きさかが書かれていないので、読者は $O(D \log D \log M)$ や別解の $O(D^2)$ が間に合うかを判断できない。台帳の summary も「M は非常に大きい」だけで、$N$・$A_i$ の上限がない
- **根拠**：ikatakos 氏の解法の節に「分母の次数は、制約より高々 $O(N \max(A)) \simeq 10^4$」、rui_er 氏に「$D = \sum A_i \le NA \le 10^4$」とある
- **直し方**：方針に「分母の次数は制約から $10^4$ 程度」と一言足す。台帳の summary に $N$・$A_i$・$M$ の上限を入れるなら、解説で制約の数値を確かめてからメインが反映する（提案）

## 台帳への提案

- tdpc_fibonacci・abc300_h・abc436_g の `checked` に 2026-10-22 を入れてよい（上の問題の内容の項で問いを確かめた）。abc300_h の summary は執筆者の提案のとおりでよい（drken 氏の記事の問題概要と一致）

## 総合の判定

小さな直しで可（直すべき 1 件・直すとよい 5 件）。コード片はランダムな比較とサニタイザで問題がなく、計算量・定理・Library Checker の制約・問題の内容は資料と一致する。指摘 1 は 1 文の言い直しで直る。
