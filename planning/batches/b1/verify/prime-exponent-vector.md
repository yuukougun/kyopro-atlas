# prime-exponent-vector の検証（工程8b・b1）

- 対象：docs/math/prime-exponent-vector.md、snippets/prime-exponent-vector/（square-pairs・lcm-mod の 2 組）、docs/img/prime-exponent-vector/exponent-bars.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/prime-exponent-vector.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page prime-exponent-vector`（エラー 0・警告 0）、`python3 tools/check_snippets.py -v snippets/prime-exponent-vector`（2 片・4 case と 5 case が一致）、`npx textlint`（0 errors・8 warnings。186・206・207 行の問題の要約と方針の文の長さ、助詞の重複。§13.8 の範囲で、直さなくてよい）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- コード片：2 つとも `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で警告なし、cases の入力で実行してサニタイザの報告なし。cases の期待出力を Python の素朴な方法（全組の積を `isqrt` で判定、`lcm` を順に取って mod）で別に計算し、すべて一致（2 8 0 18 3 → 7、1 4 9 7 → 3、200000 199999 50000 → 1、0 0 → 1、999983 1000000 → 982993007、5 個の素数 → 134248596）。中間値：lcm-mod の `res * (p % MOD)` は 10^18 未満、square-pairs の核は値以下で long long に収まる。取り込みの範囲は関数だけで、本文の手順 1〜3（核・個数・二項係数、0 は別に足す）と変数がそろう
- 本文の数値・主張を Python で確かめた：
    - 確認問題 $2^4 3^3 5$ の約数のうち平方数は 6 個、$360 \times 84 = 30240$、gcd 12・lcm 2520、$a \times b = 2^5 3^3 5 \cdot 7$（図と本文で一致）
    - 奇数倍の個数 $\lfloor(\lfloor M/L\rfloor+1)/2\rfloor$ と「$v_2$ がそろわなければ 0」を、$a_i \le 12$・長さ 1〜3・$M \le 300$ の乱択 2000 回で全探索と比べて一致
    - ABC254 D の方針 $\sum_i \lfloor\sqrt{N/\mathrm{core}(i)}\rfloor$ を $N < 80$ で全探索と比べて一致（$i = j$ を含む順序付きの組）
    - $10^{11}$ 以下の 7-smooth 数は 10688 個（「約 1 万個」は正しい。執筆者の数とも一致）
    - 試し割りの回数：$\sqrt{2\times10^5} \times 2\times10^5 \approx 8.9\times10^7$（本文どおり）、$\sqrt{10^9}\times 2\times10^5 \approx 6.3\times10^9$（指摘 2）
    - 定理：積・gcd・lcm・割り切り・平方数・$k$ 乗数の表、$ab$ が平方数 $\iff \mathrm{core}(a)=\mathrm{core}(b)$、立方数の相手の正規形が $(3-e) \bmod 3$ でただ 1 つ、XOR が 0 になる空でない選び方 $2^{N-r}-1$、奇数倍 $\iff a \mid x$ かつ $v_2(x)=v_2(a)$ は、どれも成り立つ（反例なし）
- 台帳の evidence を読んだ（drken1215.hatenablog.com は付録 B）：
    - ABC150 D（2020/01/12）：$a_i$ は 2 以上の偶数、2 の指数がそろうときだけ存在し、lcm の奇数倍を $(M/L+1)/2$ で数える。本文の方針・式と一致（執筆者の未解決の点 3 つ目は確認済み）
    - ABC300 G（2023/05/02）：$N \le 10^{16}$、$P \le 100$。素数を 2 組に分けて列挙・ソートし、尺取りで数える。本文の「尺取りか二分探索」は正しい。台帳の alternatives の approach を「二分探索」から合わせる提案（執筆者の提案）に賛成
    - AGC003 D（2018/09/29）：$N \le 10^5$、$s_i \le 10^{10}$。2500 以下の素数で試し割りし、残りは 1・$P$・$P^2$・$PQ$ の 4 通り。本文の方針と一致（執筆者の未解決の点 2 つ目は確認済み。書き方は指摘 5）
- 図：puppeteer の chrome-headless-shell 146 で、幅 900px と幅 390px（暗い背景の上）に画像にして目で確かめた。和文のフォントがこの環境になく和文は豆腐になったが、配置・はみ出し・重なりはない。背景は白で塗られ、`viewBox` があり、文字はテキストのまま（`font-family="sans-serif"`）。lcm は赤の実線、gcd は緑の破線で、色に加えて線の種類で区別している。棒の高さ（2：3・2、3：2・1、5：1・0、7：0・1）と下の 3 行の式は本文と一致。代替テキストも図の中身を文章で言えている。catalog の visual（priority 2、static）の text を満たす
- 参照先：xor-basis・gaussian-elimination・mod-arithmetic#no-compare・meet-in-the-middle・hashing-for-sets・integer-root・spf-sieve・mod-inverse・gcd-lcm・start/notation はどれもある。用語集の `#squarefree` はまだないが、手引き §13.5 のとおり提案済み（執筆者の用語集の提案に賛成）

## 指摘

### 1｜直すべき｜fact（F2）・clarity（U4）｜#single-prime の「指数をそろえる操作」の段落

- **問題**：「等しければ指数の差の合計が操作回数になる」は、何との差かが書かれておらず、操作の種類によっては誤りになる。割るだけ（÷2）なら各素数の指数を全要素の最小にそろえ、掛けるだけ（×3）なら最大にそろえるので、差の基準が違う。×2 と ÷2 の両方ができるなら最小の回数は中央値との差 $\sum |e_i - \mathrm{med}|$ で、「差の合計」を最小や最大との差と読むと答えが大きくなる。執筆者が未解決とした段落で、裏付けの問題もない
- **根拠**：例 $v_2$ が 0・2・4 の 3 要素で ×2 と ÷2 ができるとき、最小との差の合計は 6、最大との差の合計も 6 だが、中央値 2 にそろえれば 4 回で済む。割るだけなら最小の 0 にそろえて 6 回、掛けるだけなら最大の 4 にそろえて 6 回で、基準を言わないと決まらない
- **直し方**：「等しければ、素数ごとにそろえる先の指数を決め、その差の合計が操作回数になる。割るだけならそろえる先は全要素の最小、掛けるだけなら最大である」と基準を書く（両方向の操作は触れないか、「両方できるなら中央値」と足す）。問題が見つからないなら、執筆者の案どおり「操作で変わらない部分が全要素で等しくなければ不可能」までに短くしてもよい

### 2｜直すとよい｜fact（F3）｜#pitfalls「素因数分解が間に合わない」

- **問題**：「$A \le 10^9$ で同じ $N$ だと $10^{10}$ 回近く」は、計算すると $\sqrt{10^9} \times 2\times10^5 \approx 6.3\times10^9$ で、$10^{10}$ に「近い」とは言いにくい。結論（間に合わない）は正しい
- **根拠**：上の計算
- **直し方**：「約 $6 \times 10^9$ 回になり間に合わない」にする

### 3｜直すとよい｜fact（F1）・clarity（U3）｜front matter の complexity と要点の「計算量」

- **問題**：front matter は篩の前計算を $O(A \log\log A)$（$A$ は 1 個の値）と書き、要点は値の上限 $M$ で $O(M \log\log M)$ と書く。意味は同じだが記号が違い、front matter の方は「1 個の値で篩を作る」ように読める。前提の spf-sieve は「V は値の上限」と断っている
- **根拠**：docs/math/spf-sieve.md の complexity「前計算 O(V log log V)（V は値の上限…）」
- **直し方**：complexity を「指数・核の計算は 1 個 O(√A)。値の上限 M までの最小素因数の篩なら、前計算 O(M log log M) の後 1 個 O(log A)」のように要点とそろえる

### 4｜直すとよい｜figure（G3）｜exponent-bars.svg

- **問題**：viewBox の幅 600 に対して目盛りと棒の数値が font-size 12、本文の 3 行が 14 なので、幅 390px の画面（コンテンツ幅 約 358px）では約 7〜8px と 8〜9px になり、小さくて読みにくい（画像にして確かめた）
- **根拠**：幅 390px での描画を目で確かめた。等倍（幅 600px 以上）では問題ない
- **直し方**：棒の数値と p のラベルを 16 前後、下の 3 行を 16〜18 に上げる。下の 3 行は本文にも同じ式があるので、図から外して高さを詰めてもよい

### 5｜直すとよい｜clarity（U4）・fact（F2）｜#challenge の AGC003 D の方針

- **問題**：「$\sqrt[3]{10^{10}}$ 程度までの素数で割った後の残りが $1$・$p$・$p^2$・$pq$ のどれか」は正しいが、(a)「程度」がどちら向きに丸めてよいかが分からない（$\sqrt[3]{10^{10}} \approx 2154$ で、これ以上まで割れば足りる。evidence は 2500 まで）、(b) 残りが $p$・$pq$ のとき相手の正規形は $p^2$・$p^2q^2$ で $10^{10}$ を超えうるので、そのときは相手がいない（long long でもあふれうる）点に触れていない。力試しの方針なので必須ではない
- **根拠**：$2154^3 \approx 9.99\times10^9 < 10^{10} < 2155^3$。drken の記事（evidence）は 2500 以下の素数で割り、相手が値の上限を超える場合を分けている
- **直し方**：「$\sqrt[3]{10^{10}} \approx 2154$ 以上（たとえば 2500）までの素数で割る」とし、「相手の正規形が $10^{10}$ を超えるなら相手はいないので、その数は無条件に選べる」を 1 文足す

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc150_d・abc300_g・agc003_d | checked | 2026-10-21 | 上の evidence を読み、制約・方針が本文と合うことを確かめた |
| abc300_g | alternatives（prime-exponent-vector）の approach | 執筆者の提案どおり「尺取りか二分探索」に | drken の記事は尺取り |
| typical90_y | approach | 執筆者の提案に賛成（本文の方針は 7-smooth の列挙と桁の多重集合の両方を書いていて正しい） | 10^11 以下の 7-smooth 数 10688 個を手元で計算 |

## 総合の判定

**小さな直しで可**。直すべき 1（指数をそろえる操作の段落の基準）、直すとよい 4。事実・コード・図の大部分は確かめたとおり正しい。
