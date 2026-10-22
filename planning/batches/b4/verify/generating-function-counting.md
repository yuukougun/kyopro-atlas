# generating-function-counting（母関数の考え方）の検証

- 検証した版：作業ツリーの docs/comb/generating-function-counting.md（stage: draft、updated 2026-10-22）、snippets/generating-function-counting/bounded.{cpp,yaml}
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0

## 実行した確かめ

- `python3 tools/check_pages.py --page generating-function-counting`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/generating-function-counting`：10 case 一致
- `g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library bounded.cpp`：警告なし。`0 3 0`→1、`3 2 3`→7、`2 0 0`→1、`3 1 2`→3、`1 0 5`→0、`3 2 100`→0、`100000 0 5`→0、`200000 9 200000`→44809982。サニタイザの報告なし。閉じた式と繰り返し二乗法が assert で一致
- ABC449 G の解法の詳細（代表・x^N, x^(N−9), … の係数の和 − ⌊N/9⌋）を、全探索（N 個のレピュニットの和の種類数）と比べるプログラムで N = 1..22・M = 1..5 のすべてで一致を確かめた（一時置き場の g449.py）
- 小さな式の手計算：硬貨の例 (1+x+x²)(1+x²)、N=3・c=2・K=3 の 10−3=7、確認問題 2 問の答え、DP の表 3 行の回す向き、ABC303 Ex の (N−2)!·[x^(N−2)]F^N、ABC385 G の因子 x^(−1)+(n−1)+x（n=1..N−1）と y=x+x^(−1) での上昇階乗 y(y+1)…(y+N−2)：どれも正しい
- ACL：document_ja/convolution.md と照らした（宣言・modint の列を渡せること・n=|a|+|b|）
- 出典：ikatakos の ABC449 の記録（G の節）を読み、制約 N ≤ 10^5・M ≤ 10^9、N は選ぶ個数、解き方（代表・母関数・⌊N/9⌋ を引く・O(N log N)）が本文と一致することを確かめた。Library Checker の stirling_number_of_the_first_kind の task.md を gh api で読んだ（下の 2）
- 図：catalog（planning/catalog/comb.yaml）の visual は null、ページに図はない。figure.md の観点は対象なし

## 指摘

### 1（直すべき）分かりやすさ U7：本文が練習問題の解き方を折りたたみの外で書いている

- 場所：`#dp-as-polynomial` の「挿入 DP と上昇階乗」の段落の最後の文
- 問題：「左右の両方から見える数を扱うと、因子が $x^{-1} + (n - 1) + x$ の形になる（練習の [ABC385 G](#practice)）」は、練習 ABC385 G の解き方の核（差の母関数の因子）をそのまま書いている。clarity.md U7 の「本文が練習の問題を指して、その解き方を折りたたみの外で書いてしまう」に当たる
- 根拠：clarity.md U7。同じ因子は「練習の方針」の折りたたみの中にもあるので、本文から消しても情報は失われない
- 直し方：この文を消す。残すなら問題名を出さず「見える数の差を扱う問題では、因子に $x^{-1}$ が入る」程度にとどめる

### 2（直すべき）事実 F2：Library Checker の第 1 種スターリング数の問題は「上昇階乗の係数」ではない

- 場所：`#to-fps` の Library Checker の一覧の最後の行「Stirling Number of the First Kind：上昇階乗の係数」
- 問題：この問題が求めるのは符号付きの $s(N, k)$ で、下降階乗 $x(x-1)\cdots(x-N+1)$ の係数である。上昇階乗の係数（符号なし）を出す実装はそのままでは通らない
- 根拠：library-checker-problems の enumerative_combinatorics/stirling_number_of_the_first_kind/task.md（「符号付き第 1 種スターリング数 s(n,k) を x(x−1)⋯(x−(n−1)) = Σ s(n,k) x^k を満たす係数として定義」）
- 直し方：「Stirling Number of the First Kind：下降階乗 $x(x-1)\cdots(x-N+1)$ の係数（符号付き）。絶対値が上昇階乗の係数」に直す

### 3（直すとよい）事実 F2：導入の「おおむね difficulty 2400 以上の G・Ex」に根拠がない

- 場所：導入の 2 段落目
- 問題：執筆者の見立てで、台帳や出典で確かめた主張ではない（例題・練習の 4 問のうち ABC321 F は diff 1645 で、母関数の見方の練習として載っている）。数値を言い切ると事実の主張に見える
- 直し方：「このページの例題は difficulty 2500 前後の G・Ex で、」のように確かめられる事実に寄せるか、数値を外して「ABC では後半の G・Ex で多い」程度にする

### 4（直すとよい）分かりやすさ U3：挿入 DP の段落で、入れる順と「状態」が書かれていない

- 場所：`#dp-as-polynomial` の「挿入 DP と上昇階乗」
- 問題：「状態を 1 増やす重み 1」「状態を変えない重み n − 1」が、何を入れる DP で状態が何かを言わないまま、左から見える位置の個数に結び付けられる。レート 1000 の読者は「なぜ左から見える数になるのか」で止まる
- 直し方：「大きい値から順に入れ、状態を左から見える個数とする。n 番目に入れる値は n か所に置け、左端の 1 か所だけで見える個数が 1 増える」の 1 文を足す（ABC385 G の名は出さない。指摘 1 と両立する）

### 5（直すとよい）分かりやすさ U2：例題 ABC449 G の解法の詳細に計算量がない

- 場所：`#abc449_g` の「解法の詳細」の最後の項目
- 問題：「2 つの列を畳み込んで、要る係数を足す」で終わり、なぜ間に合うかがない。執筆者の未解決の点（制約）も残っている
- 根拠：ikatakos の記録によると制約は $N \le 10^5$・$M \le 10^9$。分子・分母の列を $N$ 次まで求めて畳み込むので $O(N \log N)$
- 直し方：「どちらも $N$ 次まで求めればよいので、畳み込みを含めて $O(N \log N)$ である（$M$ は二項係数の比の計算にだけ現れる）」を足す。本文の「M が大きくても」はこれで根拠が付く

### 6（直すとよい）事実 F1・F4：ACL の convolution の計算量の書き写し

- 場所：`#to-fps` の「ACL では」の囲み
- 問題：ドキュメントの計算量は $O(n \log n + \log \mathrm{mod})$。998244353 固定なら差はないが、ACL の値として書くならそろえる
- 根拠：~/lib/ac-library-master/document_ja/convolution.md
- 直し方：「$O(n \log n + \log \mathrm{mod})$（法を固定すれば $O(n \log n)$）」とする

### 7（直すとよい）分かりやすさ U1・事実 F10：要点の「何ができるか」と summary の違い

- 場所：要点の囲みと front matter の summary
- 問題：要点に「上限つきの選び方は … 閉じた式の係数として二項係数で求まり」が足されたが、summary にはない。食い違いではないが、U1 の「要点と summary が言っていることが違う」に近い
- 直し方：要点のこの一文を削ってそろえるか、summary への追加をメインへの提案として報告に書く（front matter の summary は執筆者が変えない）

## 執筆者の未解決の点について

- ABC449 G の制約：ikatakos の記録で $N \le 10^5$・$M \le 10^9$ と確かめた。本文の方針はこれに合う（指摘 5 で計算量を足す提案）
- 台帳 abc449_g の summary は「（執筆時に確かめる）」のまま。執筆者の提案の summary（ページの囲みと同じ文）は ikatakos の記録の問いと一致するので、そのまま反映してよい。checked に 2026-10-22 を入れる提案にも同意する
- FPS の演算の計算量（逆元・log・exp・累乗 $O(K \log K)$、多くの因子の積 $O(K \log^2 K)$）は一般に知られた値どおりで、cayley-pruefer の値とも一致している

## 総合の判定

小さな直しで可（直すべき 2・直すとよい 5）。数式・例題の解法・コード片は確かめた範囲で正しい。直すべきは、本文から練習 ABC385 G の因子を外すこと（1）と、Library Checker の第 1 種スターリング数の説明を符号付き・下降階乗に直すこと（2）の 2 つである。
