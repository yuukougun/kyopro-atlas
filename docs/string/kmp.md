---
id: kmp
title: KMP 法と文字列の周期
aliases: [KMP, MP 法, Knuth-Morris-Pratt, 失敗関数, prefix function, π 配列, border, 最小周期, 繰り返し単位]
type: technique
field: string
chapter: 線形時間の照合と回文
order: 70
level: 青
kind: [文字列]
prerequisites: [string-basics]
related: [z-algorithm, aho-corasick, string-automaton-dp, rolling-hash, divisor-enum, mobius-function, suffix-automaton]
summary: π[i]（先頭 i+1 文字の、接頭辞でも接尾辞でもある最長の真の部分の長さ）を O(N) で求める。π をたどると全 border と最小周期が分かり、照合に失敗したときのずらし方や照合オートマトンの遷移にも使える。
complexity: π の構築 O(N)（ならし）、パターン照合 O(N + M)、照合オートマトンの表 O(σM)
signs:
  - {type: phrase, text: 接頭辞と接尾辞が一致する最長の長さ}
  - {type: phrase, text: 最小周期・何かの繰り返しで書けるか}
  - {type: phrase, text: N の約数 M を周期に持つ文字列（表）を数える}
  - {type: phrase, text: 文字が 1 つずつ来るたびに、パターンが現れたかを判定する}
  - {type: constraint, text: '|S| ≤ 10^6 で、すべての接頭辞について周期や一致する長さを問う'}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 6 問
sections:
  - {title: 失敗関数 π（border）の定義と添字の流儀, anchor: failure-function}
  - {title: なぜ O(N) か：照合長は 1 文字で高々 1 増え、ループで減る回数も合計 N 以下, anchor: linear-time}
  - {title: パターン照合：失敗したら π の値までずらす, anchor: matching}
  - {title: MP と KMP の違い（競プロでは MP を KMP と呼ぶことが多い）, anchor: mp-vs-kmp}
  - {title: border の連鎖と全 border の列挙, anchor: border-chain}
  - {title: 周期と繰り返し：最小周期と、繰り返しで書ける条件（弱周期定理）, anchor: string-period}
  - {title: N の約数の周期を数える：約数ごとに数えて包除（メビウス）, anchor: count-periodic}
  - {title: 照合オートマトン（状態×文字 → 次の状態）を表に埋める, anchor: automaton}
stage: draft
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：$\pi[i]$（先頭 $i + 1$ 文字の、接頭辞でも接尾辞でもある最長の真の部分の長さ）を $O(N)$ で求める。$\pi$ をたどると全 border と最小周期が分かり、照合に失敗したときのずらし方や照合オートマトンの遷移にも使える。
    - **いつ使うか**：
        - 接頭辞と接尾辞が一致する最長の長さ
        - 最小周期・何かの繰り返しで書けるか
        - $N$ の約数 $M$ を周期に持つ文字列（表）を数える
        - 文字が 1 つずつ来るたびに、パターンが現れたかを判定する
        - $\lvert S \rvert \le 10^6$ で、すべての接頭辞について周期や一致する長さを問う
    - **計算量**：$\pi$ の構築は全体で $O(N)$（ならし。1 文字あたりは最悪 $O(N)$）。長さ $M$ のパターンの長さ $N$ の本文での全出現は $O(N + M)$。照合オートマトンの表は文字の種類数を $\sigma$ として $O(\sigma M)$
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)

<!-- textlint-disable -->
別名：KMP・MP 法・Knuth-Morris-Pratt・失敗関数・prefix function・π 配列・border・最小周期・繰り返し単位
<!-- textlint-enable -->

KMP 法は、文字列の各接頭辞について「接頭辞でも接尾辞でもある最長の部分」の長さ $\pi$ を、すでに求めた値を使い回して線形時間で求める手法である。$\pi$ は、照合に失敗したときに、ずらした後も一致が分かっている長さ（どこから比べ直すか）を表す。$\pi$ をたどれば、文字列の周期や繰り返しの単位も分かる。ACL にはないので自分で書くが、中心は 10 行ほどである。

## 失敗関数 π（border）の定義と添字の流儀 {#failure-function}

$S$ 自身より短い文字列で、$S$ の[接頭辞](../string/string-basics.md)かつ接尾辞であるものを $S$ の [border](../guide/glossary.md#border) という。空の文字列はいつでも border である。たとえば $S = \texttt{abacaba}$ の border は $\texttt{aba}$・$\texttt{a}$・空の 3 つである。

長さ $N$ の文字列 $S$（0-indexed）の失敗関数 $\pi$ は、$\pi[i]$ ＝「$S[0, i + 1)$ の最長の border の長さ」で決まる長さ $N$ の配列である。長さ 1 の文字列の border は空だけなので、$\pi[0] = 0$ になる。

| $i$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| $S[i]$ | a | b | a | c | a | b | a |
| $\pi[i]$ | 0 | 0 | 1 | 0 | 1 | 2 | 3 |

$\pi[6] = 3$ は、$S[0, 7) = \texttt{abacaba}$ の先頭 3 文字と末尾 3 文字がどちらも $\texttt{aba}$ で、4 文字以上では一致しないことを表す。

**作り方**。$\pi[i]$ を、$\pi[i - 1]$ から求める。長さ $k \ge 1$ の $S[0, i + 1)$ の border から最後の文字を除くと、$S[0, i)$ の border（空でもよい）になる。よって $\pi[i]$ の候補は「$S[0, i)$ の border の長さ $j$ で、$S[j] = S[i]$ を満たすもの」に 1 を足したものだけである。$S[0, i)$ の border を長い順に $j = \pi[i - 1], \pi[j - 1], \dots$ とたどり、最初に $S[j] = S[i]$ となったところで $\pi[i] = j + 1$ とする。$j = 0$ まで来ても一致しなければ $\pi[i] = 0$ である。border を長い順にこの形でたどり尽くせる理由は [border の連鎖の節](#border-chain)で示す。

```cpp
--8<-- "kmp/prefix-function.cpp:core"
```

**添字の流儀**。解説によって配列の持ち方が 2 通りある。

- **$\pi[0] = 0$ の流儀**（このページ）：長さ $N$ の配列で、$\pi[i]$ は $S[0, i + 1)$ の最長の border の長さ。ループは `j > 0` の間だけたどる
- **$A[0] = -1$ の流儀**（MP 法の解説に多い）：長さ $N + 1$ の配列で、$A[i]$ は $S[0, i)$ の最長の border の長さ。$A[0] = -1$ は番兵である。ループは `j >= 0` の間たどり、抜けた後で $j$ を 1 増やす

2 つは $A[i + 1] = \pi[i]$ で対応する。どちらで書いても計算量は同じだが、混ぜると添字が 1 ずれる。他人のコードを写すときは、配列の長さと $[0]$ の値で流儀を確かめる。

## なぜ O(N) か：照合長は 1 文字で高々 1 増え、ループで減る回数も合計 N 以下 {#linear-time}

$\pi$ の作り方は二重ループに見えるが、全体で $O(N)$ である。各 $i$ で何回たどるかは一定でないので、合計で数える（[ならし計算量](../basics/complexity-estimation.md#amortized)）。

ループの中の変数 $j$ に注目する。$i$ の処理を始めるときは $j = \pi[i - 1]$ で、終えるときは $j = \pi[i]$ である。

- `while` を 1 回回るたびに、$j$ は $\pi[j - 1] < j$ に変わるので 1 以上減る
- `if` で $j$ が増えるのは、1 つの $i$ につき高々 1 で、全体で $N - 1$ 以下
- $j$ は 0 未満にならない

減った量の合計は増えた量の合計を超えないので、`while` を回る回数は全体で $N - 1$ 以下である。よって比較は全体で $O(N)$ 回になる。

ただし、1 つの $i$ だけを見ると多く回ることがある。$S = \texttt{aaaa}\dots\texttt{ab}$ の最後の $\texttt{b}$ では、$j$ が $N - 2, N - 3, \dots, 0$ と 1 ずつ減り、`while` を $N - 2$ 回回る（比較は $N - 1$ 回）。「直前の状態に戻してやり直す」使い方では、この偏りのせいで $O(N)$ が崩れる（[落とし穴](#pitfalls)）。

## パターン照合：失敗したら π の値までずらす {#matching}

長さ $M$ のパターン $P$ が、長さ $N$ の本文 $T$ のどこに現れるかを求める。ずらし方ごとに比べ直すと $O(NM)$ かかり、$N, M$ が $10^5$ を超えると間に合わない。KMP 法は $T$ を左から 1 文字ずつ読み、「$T$ のいま読んだ所までの末尾が、$P$ の先頭何文字と一致しているか」を表す $j$ だけを持って進む。

次の文字 $T[i]$ が $P[j]$ と一致すれば $j$ を 1 増やす。一致しなければ、$P$ をずらして $T$ の末尾と一致する $P$ の接頭辞のうち、次に長いものに移る。一致していた $P[0, j)$ の接尾辞で $P$ の接頭辞でもあるものは $P[0, j)$ の border なので、次に長いものは長さ $\pi[j - 1]$ である。ずらした後の先頭 $\pi[j - 1]$ 文字は一致すると分かっているので、比べ直さない。

![本文 abababc でパターン ababc を照合する。先頭に合わせると P[4] = c と T[4] = a で失敗する。一致していた abab の最長の border は ab（π[3] = 2）なので、P を 2 文字ずらし、先頭の ab は比べ直さずに P[2] と T[4] から比べると、位置 2 からの出現が見つかる](../img/kmp/shift.svg)

図の例では、$P = \texttt{ababc}$ の $\pi$ は $(0, 0, 1, 2, 0)$ である。$j = 4$ で失敗したので $j = \pi[3] = 2$ とし、$P[2] = \texttt{a}$ と $T[4] = \texttt{a}$ から比べ直す。$j$ が $M$ になったら、位置 $i - M + 1$ からの出現である。続く出現を探すため $j = \pi[M - 1]$ に戻す。こうすれば重なった出現も見逃さない。たとえば $\texttt{aaaa}$ の中の $\texttt{aa}$ は 3 か所とも見つかる。

```cpp
--8<-- "kmp/match.cpp:core"
```

計算量は $\pi$ の構築と同じ議論で、$j$ が増えるのは $T$ の 1 文字につき高々 1 回なので $O(N)$、$\pi$ の構築と合わせて $O(N + M)$ である。$T$ を先まで知らなくても、文字が来るたびにその場で判定できる。

**区切りでつなぐ書き方**。$P + \# + T$（$\#$ はどちらにも現れない文字）の $\pi$ を作り、$T$ 側の位置で $\pi = M$ となる所を出現とみなしてもよい。区切りがあるので border は $M$ を超えない。照合の関数を別に書かなくて済むが、区切りの文字の選び方は [Z-algorithm](../string/z-algorithm.md#acl) と同じ注意が要る。上の照合の関数は区切りが要らないので、整数の列の検索（[ABC150 F](#abc150_f)）にもそのまま使える。

## MP と KMP の違い（競プロでは MP を KMP と呼ぶことが多い） {#mp-vs-kmp}

ここまでの方法は、正確には MP 法（Morris-Pratt）である。失敗したら、一致していた部分の最長の border へ移る。KMP 法（Knuth-Morris-Pratt）は、移った先で次に比べる文字が、いま失敗した文字と同じ場合を飛ばす改良である。

状態 $j$ で $P[j]$ との比較に失敗したとする。$k = \pi[j - 1]$ に移ったとき $P[k] = P[j]$ なら、本文の同じ文字と比べてもまた失敗すると分かっている。KMP 法はこれを前計算で飛ばす。失敗したときの移り先を $f[j]$ とし、$P[k] = P[j]$ なら $f[j] = f[k]$、そうでなければ $f[j] = k$ とする（$j = 0$ で失敗したら、本文の次の文字へ進む）。

違いが出るのは 1 文字あたりの最悪の手間である。$P = \texttt{aaa}\dots\texttt{ab}$（$\texttt{a}$ が $M - 1$ 個）を本文 $\texttt{aaa}\dots\texttt{ac}$ に当てると、$\texttt{c}$ の 1 文字で MP 法は状態を $M - 1, M - 2, \dots, 0$ とたどる。KMP 法は、$\texttt{a}$ を待つ状態どうしの移動を飛ばすので、数回で状態 0 に着く。一般に、KMP 法では 1 文字あたりの比較の回数が、黄金比 $\varphi$ を底とする $\log_\varphi M$ 程度に抑えられる。

全体の計算量はどちらも $O(N + M)$ で変わらない。競プロでは MP 法の配列 $\pi$ を「KMP」と呼ぶことが多く、$\pi$ は border・周期・オートマトンにそのまま使えるので、MP 法を覚えれば足りる。1 文字あたりの手間を $O(1)$ にしたいときは、KMP 法ではなく[照合オートマトン](#automaton)の表を作る。

## border の連鎖と全 border の列挙 {#border-chain}

$S$ の border は、最長の border の長さ $\pi[N - 1]$ から始めて $b \leftarrow \pi[b - 1]$ を 0 になるまでくり返すと、長い順にすべて得られる。これを border の連鎖という。

![S = aabaabaa の border は長い順に aabaa（π[7] = 5）、aa（π[4] = 2）、a（π[1] = 1）。各段で接頭辞と接尾辞が同じ文字列になっていて、次の段は前の段の border の最長の border である](../img/kmp/border-chain.svg)

**なぜすべて得られるか**。$S$ の最長の border を $B$（長さ $b$）とし、$C$ を $B$ より短い $S$ の border とする。$C$ は $S$ の接頭辞なので $B$ の接頭辞でもあり、$S$ の接尾辞なので $B$ の接尾辞でもある。よって $C$ は $B$ の border である。逆に $B$ の border は $S$ の border でもある。したがって「$S$ の border のうち $B$ より短いもの」は「$B = S[0, b)$ の border」とちょうど一致し、その最長は $\pi[b - 1]$ である。これをくり返せばよい。同じ議論で、$S[0, i + 1)$ の border はどれも $\pi[i]$ からの連鎖に現れる。[作り方](#failure-function)でたどった候補が漏れないのはこのためである。

**各接頭辞が何回現れるか**。$S$ の長さ $k$ の接頭辞が位置 $i$ で終わる所に現れることは、$k = i + 1$ であるか、$k$ が $S[0, i + 1)$ の border の長さであることと同じである。そこで各 $i$ について、最長の border $\pi[i]$ に 1 を数え、連鎖に沿って短い border へ受け渡す。長い $k$ から順に `cnt[pi[k - 1]] += cnt[k]` とすれば、連鎖をたどり直さずに $O(N)$ で済む。

```cpp
--8<-- "kmp/borders.cpp:core"
```

受け渡しは $k$ の大きい順に行う。$\pi[k - 1] < k$ なので、`cnt[k]` は自分より長い接頭辞からの受け渡しがすべて済んでから読まれる。

## 周期と繰り返し：最小周期と、繰り返しで書ける条件（弱周期定理） {#string-period}

$1 \le p \le N$ について、すべての $0 \le i < N - p$ で $S[i] = S[i + p]$ が成り立つとき、$p$ を $S$ の[周期](../guide/glossary.md#period)という。この条件は「$S[0, N - p)$ と $S[p, N)$ が等しい」と同じで、長さ $N - p$ の border があることと同じである。

$$
p \text{ が周期} \iff N - p \text{ が border の長さ}
$$

よって最小の周期は最長の border から決まり、$N - \pi[N - 1]$ である。周期の全体は、border の連鎖の各長さ $b$ について $N - b$ を集めたものになる（空の border に当たる $N$ も含む）。

**周期と繰り返しは違う**。$S$ が長さ $p$ の文字列の $N / p$ 回の繰り返しで書けるのは、$p$ が周期で、かつ $p \mid N$ のときである。$S = \texttt{abcabcab}$ は $\pi[7] = 5$ なので最小の周期は 3 だが、3 は 8 を割り切らない。次の性質により、最小の周期が $N$ を割り切らなければ、$S$ は自分より短いどの文字列の繰り返しでもない。

```cpp
--8<-- "kmp/prefix-function.cpp:period"
```

> **弱周期定理**：$p$ と $q$ がどちらも $S$ の周期で $p + q \le N$ なら、$\gcd(p, q)$ も $S$ の周期である。

??? note "証明"
    $p > q$ として、$p - q$ が周期であることを示せばよい。後はユークリッドの互除法と同じく、大きい方から小さい方を引くことをくり返す。和は減っていくので $p + q \le N$ の仮定は保たれ、最後に $\gcd(p, q)$ が残る。

    $0 \le i < N - (p - q)$ について $S[i] = S[i + p - q]$ を示す。

    - $i + p < N$ のとき：周期 $p$ より $S[i] = S[i + p]$。$(i + p - q) + q = i + p < N$ なので、周期 $q$ より $S[i + p - q] = S[i + p]$
    - $i + p \ge N$ のとき：$i \ge N - p \ge q$ なので、周期 $q$ より $S[i] = S[i - q]$。$(i - q) + p < N$ なので、周期 $p$ より $S[i - q] = S[i - q + p]$

    どちらでも $S[i] = S[i + p - q]$ が成り立つ。

**最小の周期が $N$ を割り切らなければ繰り返しで書けない理由**。$S$ が長さ $q$（$q < N$、$q \mid N$）の文字列の繰り返しだとすると、$q$ は周期で $q \le N / 2$ である。最小の周期 $d$ は $d \le q$ なので $d + q \le N$ となり、弱周期定理から $\gcd(d, q)$ も周期になる。$d$ の最小性から $\gcd(d, q) = d$、すなわち $d \mid q$ で、$d \mid N$ が従う。

**繰り返しの単位は一意**。$d \mid N$ なら $S$ は $U = S[0, d)$ の $N / d$ 回の繰り返しで、$U$ 自身はもう短い文字列の繰り返しで書けない（書けたら $S$ にもっと短い周期がある）。このような $U$ を $S$ の繰り返しの単位、繰り返しで書けない文字列を原始的な文字列と呼ぶ。2 つの文字列が「同じ単位の繰り返しか」は、単位どうしを比べれば判定できる（[ABC312 Ex](#challenge)）。

**すべての接頭辞について**。$\pi$ は各接頭辞の最長の border なので、$S[0, i + 1)$ の最小の周期は $i + 1 - \pi[i]$ で、すべての $i$ について $O(N)$ でまとめて分かる。接尾辞についても知りたいときは、$S$ を反転した文字列の $\pi$ を作る。

## N の約数の周期を数える：約数ごとに数えて包除（メビウス） {#count-periodic}

この節は[約数の列挙](../math/divisor-enum.md)と[約数包除](../comb/divisor-inclusion-exclusion.md)を前提にする。「$N$ 未満の $N$ の約数 $d$ のどれかを周期に持つ文字列（条件付き）は何通りか」を数える。

1 つの約数 $d$ を周期に持つ文字列の数 $F(d)$ は数えやすい。$d \mid N$ なら、周期 $d$ を持つことは「添字を $d$ で割った余りが同じ位置の文字がすべて等しい」ことと同じである。よって余りごとに独立に文字を決めればよい。困るのは、複数の約数を周期に持つ文字列を重ねて数えてしまうことである。$N = 12$ なら $\texttt{aaa}\dots\texttt{a}$ は周期 1・2・3・4・6 をすべて持つ。

重なりは、弱周期定理で整理できる。$N$ 未満の $N$ の約数 $p, q$ は $N / 2$ 以下なので $p + q \le N$ を満たし、どちらも周期なら $\gcd(p, q)$ も周期である。$\gcd(p, q)$ も $N$ の約数である。したがって、文字列ごとに「周期になる $N$ の約数」の最小のもの $d_0$ がただ 1 つ決まり、ほかはすべて $d_0$ の倍数になる。そこで次のように分ける。

- $f(d)$ ＝「周期になる $N$ の約数のうち最小のものが $d$」である文字列の数
- $F(d) = \sum_{e \mid d} f(e)$（周期 $d$ を持つ文字列は、最小の $d_0$ が $d$ の約数のどれかになる）

$d$ の小さい順に $f(d) = F(d) - \sum_{e \mid d,\ e < d} f(e)$ と求める。答えは、$N$ 未満の約数 $d$ についての $f(d)$ の和である。約数の個数を $D$ とすると、$F$ の計算に $O(ND)$、引き算に $O(D^2)$ かかる。$N \le 10^6$ なら $D \le 240$ なので十分に速い。

[メビウス関数](../comb/mobius-function.md) $\mu$ を使うと、$f(N) = \sum_{d \mid N} \mu(N / d) F(d)$ と書ける。答えは $F(N) - f(N)$ なので、1 本の式にまとめると次のようになる。どちらの書き方でも結果は同じである。

$$
\text{答え} = -\sum_{d \mid N,\ d < N} \mu(N / d) \, F(d)
$$

## 照合オートマトン（状態×文字 → 次の状態）を表に埋める {#automaton}

[パターン照合](#matching)の状態 $j$（$0 \le j \le M$）は、本文の次の 1 文字だけで次の状態が決まる。そこで、状態 $j$ で文字 $c$ を読んだ後の状態 $\mathrm{nxt}[j][c]$ を、すべての $j, c$ について表にしておく。これを照合オートマトン（KMP オートマトン）という。

表は $j$ の小さい順に埋められる。

- $j < M$ かつ $P[j] = c$ なら、一致が伸びて $\mathrm{nxt}[j][c] = j + 1$
- そうでなく $j = 0$ なら $\mathrm{nxt}[0][c] = 0$
- それ以外は、失敗して状態 $\pi[j - 1]$ に移ってから $c$ を読むのと同じなので、$\mathrm{nxt}[j][c] = \mathrm{nxt}[\pi[j - 1]][c]$

$\pi[j - 1] < j$ なので、3 つ目で写す行はもう埋まっている。状態 $M$（$P$ 全体と一致した直後）も 3 つ目の規則で埋まる。文字の種類数を $\sigma$ とすると、表の大きさと作る手間はどちらも $O(\sigma M)$ である。

```cpp
--8<-- "kmp/automaton.cpp:core"
```

表があると、1 文字あたりの手間がならしでなく常に $O(1)$ になる。これが効くのは次の 2 つの場面である。

- **DP の状態にする**：「長さ $L$ の文字列で $P$ を含まないものの数」は、$\mathrm{dp}[j]$ ＝ いまの照合の状態が $j$ の文字列の数として、表の遷移で配れば $O(L \sigma M)$ で求まる。状態 $M$ に入る遷移を捨てればよい。$L$ が巨大なら遷移を行列にして累乗する（[照合オートマトン上の DP](../string/string-automaton-dp.md)）
- **状態を戻しながら読む**：木の上の DFS で根からの文字列を照合し、帰るときに状態を戻す場合などは、ならしの議論が使えない。表を引けば各辺 $O(1)$ で済む

```cpp
--8<-- "kmp/automaton.cpp:dp"
```

パターンが複数あるときは、パターンを [Trie](../string/trie.md) にまとめ、$\pi$ の代わりに失敗リンクを張る。これが [Aho-Corasick 法](../string/aho-corasick.md)で、表の埋め方は同じ考え方である。

## 落とし穴 {#pitfalls}

**添字の流儀を混ぜる**。$\pi[0] = 0$ の流儀では最小の周期は `n - pi[n - 1]`、$A[0] = -1$ の流儀では `n - A[n]` である。片方の流儀の配列にもう片方の式を使うと 1 ずれる。`while` の条件も、前者は `j > 0`、後者は `j >= 0` で、取り違えると配列の外の参照か誤った値になる。

**全体が一致した後に $j$ を戻さない**。照合で $j = M$ になった後、そのまま次の文字を読むと `p[m]` を参照して配列の外に出る。出現を記録したら $j = \pi[M - 1]$ に戻す。$j = 0$ に戻すと、$\texttt{aa}$ を $\texttt{aaa}$ から探すときの 2 つ目のような、重なった出現を見逃す。

**最小の周期が $N$ を割り切るかを確かめ忘れる**。「繰り返しで書けるか」を問われて、最小の周期 $p = N - \pi[N - 1]$ を求めただけで答えると誤る。$p \mid N$ でなければ、$S$ は自分より短いどの文字列の繰り返しでもない。

**周期はすべて最小の周期の倍数だと思い込む**。$S = \texttt{aabaa}$ の周期は 3・4・5 で、4 は最小の周期 3 の倍数ではない。最小の周期 $d$ の倍数になると言えるのは、$N - d$ 以下の周期（弱周期定理が使える範囲）だけである。$N$ 未満の $N$ の約数である周期は $N / 2$ 以下なので、これに含まれる。$N$ 自身はいつも周期だが、$d$ の倍数とは限らない。

**状態を戻しながら $\pi$ でたどる**。1 文字あたりの手間は最悪 $O(M)$ なので、DFS で戻りながら照合したり、同じ状態から何度もやり直したりすると $O(NM)$ になりうる。この場合は[照合オートマトン](#automaton)の表を引く。

!!! info "ACL では"
    ACL に KMP 法はない。`atcoder::z_algorithm(s)` で代用できる（$O(N)$）。$1 \le p < N$ について「$p$ が周期 ⇔ $z[p] = N - p$」で、これは長さ $N - p$ の border の有無と同じである（[Z-algorithm の周期の節](../string/z-algorithm.md#period)）。

## 例題 {#examples}

### ABC304 F. Shift Table {#abc304_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC304 F. Shift Table](https://atcoder.jp/contests/abc304/tasks/abc304_f)（diff 1619）：N の約数 M を周期に持つという条件を満たすシフト表の数を求める。

</div>

$N$ 日のシフト表は $N$ 文字の文字列で、各日は「必ず働く」か「働くかどうかを自由に選べる」かが入力から決まっている。$N$ 未満の $N$ の約数のどれかを周期に持つ表を数える。周期 $d$ を持つ表の数 $F(d)$ は余りごとに数えられるので、[N の約数の周期を数える節](#count-periodic)の包除で重なりを除く。

??? note "解法の詳細"
    - 周期 $d$（$d \mid N$）を持つ表では、添字を $d$ で割った余りが同じ日の値がすべて等しい。余り $r$ の日の中に「必ず働く」日が 1 つでもあれば、その余りの日はすべて働く（1 通り）。1 つもなければ、働くか休むかの 2 通りである。よって $F(d) = 2^{(\text{必ず働く日を含まない余りの数})}$ で、1 つの $d$ につき $O(N)$ で求まる。
    - $d$ の小さい順に $f(d) = F(d) - \sum_{e \mid d,\ e < d} f(e)$ を求め、$N$ 未満の約数 $d$ の $f(d)$ を足す。mod 998244353 で計算する。
    - $N \le 10^5$ で約数は高々 128 個なので、全体で $O(N D)$ である。
    - メビウス関数を篩で作り、$-\sum_{d \mid N,\ d < N} \mu(N / d) F(d)$ を直接計算してもよい。

### ABC150 F. Xor Shift {#abc150_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC150 F. Xor Shift](https://atcoder.jp/contests/abc150/tasks/abc150_f)（diff 2281）：b が、a の巡回シフトの各要素を x で XOR したものになる (k, x) をすべて求める。

</div>

シフト量 $k$ を決めると、$x$ は $a_k \oplus b_0$ に決まる。$x$ を消すために隣どうしの XOR を取ると、すべての要素を同じ $x$ で XOR しても $p \oplus q$ は変わらないので、問題は「差分の列 $b'$ が、差分の列 $a'$ の巡回シフトのどれと一致するか」になる。$a'$ を 2 周つないだ列の中で $b'$ の出現をすべて求めればよい。

??? note "解法の詳細"
    - 0-indexed で $a'_i = a_i \oplus a_{(i + 1) \bmod N}$、$b'_i = b_i \oplus b_{(i + 1) \bmod N}$ とする。
    - $a'$ を 2 周つないだ列（長さ $2N - 1$ まででよい）の中で、$b'$ が位置 $k$（$0 \le k < N$）から現れるかを、[パターン照合](#matching)の関数を整数の列に書き換えて求める。区切りが要らないので、値の範囲を気にしなくてよい。
    - $k$ で一致したら $x = a_k \oplus b_0$ である。$b_0 = a_k \oplus x$ から始めて、差分が等しいので $b_i = a_{(i + k) \bmod N} \oplus x$ が順に成り立つ。逆に条件を満たす $(k, x)$ では差分が一致するので、漏れもない。
    - $k$ の小さい順に出力する。全体で $O(N)$。Z-algorithm（区切りを値の範囲の外にする）やローリングハッシュでも解ける。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC430 E. Shift String](https://atcoder.jp/contests/abc430/tasks/abc430_e)（diff 1109）：A を何回回転すると B に一致するかを求める。
- [ABC135 F. Strings of Eternity](https://atcoder.jp/contests/abc135/tasks/abc135_f)（diff 2388）：t を繰り返した文字列が、s を繰り返した文字列に含まれる最大の回数を求める。

</div>

??? note "練習の方針"
    - **ABC430 E**：回転は $A + A$ の長さ $N$ の窓なので、$A + A$ の中での $B$ の最初の出現位置を[パターン照合](#matching)で求める。Z-algorithm での解き方は [Z-algorithm の巡回シフトの節](../string/z-algorithm.md#cyclic-shift)にある。
    - **ABC135 F**：$s$ を $\lvert s \rvert + \lvert t \rvert$ 文字以上になるまで繰り返した列で $t$ を照合し、$s$ の各位置 $i$（$0 \le i < \lvert s \rvert$）から $t$ が始まるかを求める。始まる位置 $i$ ごとに、$i$ から $(i + \lvert t \rvert) \bmod \lvert s \rvert$ へ辺を張る。各頂点から出る辺は高々 1 本なので、最長の道の辺の数が答えで、閉路があれば無限（$-1$）である。

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [ABC312 Ex. snukesnuke](https://atcoder.jp/contests/abc312/tasks/abc312_h)（diff 2477）：N 人が順に希望の文字列を名乗り、それまでの名前と重なるときは希望の文字列を最小の回数だけ繰り返したものを名乗るとき、各人の繰り返しの回数を求める。
- [ARC060 F. Best Representation](https://atcoder.jp/contests/arc060/tasks/arc060_d)（diff 2804）：文字列を、周期を持たない文字列に分割するときの最小の個数と、その分け方の数を求める。

</div>

??? note "力試しの方針"
    - **ABC312 Ex**：各 $S_i$ を最小の周期から繰り返しの単位 $U$ と回数 $r_i$（$S_i = U^{r_i}$）に直すと、単位が違う名前は重ならない。単位ごとに「使った回数の集合」と、$r$ ごとの「前回どこまで調べたか」を持ち、$r_i$ の倍数を順に調べて空いている最初の回数を取る。調べた位置は戻らないので、調べ直しが起きない。
    - **ARC060 F**：原始的な文字列への分割を数える。$S$ が原始的なら答えは 1 個・1 通り、すべて同じ文字なら $N$ 個・1 通りである。それ以外は 2 個にでき、分け方は「$S[0, i)$ と $S[i, N)$ がどちらも原始的」な $i$ の数になる。接頭辞 $S[0, i)$ は、$p = i - \pi[i - 1]$ が $p = i$ であるか $i$ を割り切らないとき原始的である。接尾辞は反転した $S$ の $\pi$ で同じように判定でき、全体で $O(N)$ になる。

## 確認問題 {#quiz}

??? question "確認問題：π を書く"
    $S = \texttt{aabaaab}$ の $\pi$ を書け。

    ??? success "答え"
        $(0, 1, 0, 1, 2, 2, 3)$。$\pi[5]$ では、$\pi[4] = 2$ の border $\texttt{aa}$ に $S[5] = \texttt{a}$ を足そうとすると $S[2] = \texttt{b}$ と食い違う。次に長い border の長さ $\pi[1] = 1$ に移ると $S[1] = \texttt{a}$ と一致するので $\pi[5] = 2$ になる。$\pi[6]$ は $\texttt{aa}$ に $\texttt{b}$ を足した $\texttt{aab}$ で 3 である。

??? question "確認問題：最小の周期と繰り返し"
    $S = \texttt{abaababaab}$（$N = 10$）の $\pi[9]$ は 5 である。最小の周期はいくつか。$S$ は 10 文字より短い文字列の繰り返しで書けるか。

    ??? success "答え"
        最小の周期は $10 - 5 = 5$ で、5 は 10 を割り切るので $S = (\texttt{abaab})^2$ と書ける。$\texttt{abaab}$ 自身は最小の周期 3 が 5 を割り切らないので、これ以上短い単位はない。

??? question "確認問題：照合で全体が一致した後"
    照合で $j = M$ になった後、$j = \pi[M - 1]$ ではなく $j = 0$ に戻すと、$P = \texttt{aba}$・$T = \texttt{ababa}$ の答えはどうなるか。

    ??? success "答え"
        位置 0 の出現を見つけた後、$j = 0$ から $T[3] = \texttt{b}$ を読むので、位置 2 から始まる出現 $\texttt{aba}$ を見逃し、出現は 1 か所だけになる。$j = \pi[2] = 1$ に戻せば、$T[2] = \texttt{a}$ を接頭辞 $\texttt{a}$ として残したまま続けられ、2 か所とも見つかる。

??? question "確認問題：ならし計算量が崩れる場面"
    根付き木の各辺に文字が書かれていて、根から各頂点への文字列が $P$ で終わるかを DFS で調べる。$\pi$ でたどる照合を、帰るときに状態を戻しながら使うと遅くなりうるのはなぜか。

    ??? success "答え"
        $O(N)$ の根拠は「$j$ が減る量の合計は増えた量の合計以下」だが、状態を戻すと、減らした後で同じ大きい $j$ に何度も戻れる。たとえば $j = M - 1$ の頂点に、失敗して長くたどる子が多数つくと、子ごとに $O(M)$ かかる。照合オートマトンの表を引けば、各辺 $O(1)$ で済む。

## 使い分け {#comparison}

KMP 法と [Z-algorithm](../string/z-algorithm.md) は、どちらも「先頭との一致」を線形時間で求める。見る向きが違う。

| 手法 | 位置 $i$ について分かること | 向いている場面 |
| --- | --- | --- |
| Z-algorithm | $i$ から始まる部分と先頭の最長一致 | 区切りでつないだ検索・周期の判定。ACL にある |
| KMP 法 | $i$ で終わる部分と先頭の最長一致（$\pi$） | border の連鎖・文字が 1 つずつ来る照合・オートマトン |
| [ローリングハッシュ](../string/rolling-hash.md) | 任意の 2 か所が等しいか | 先頭に固定されない比較。衝突は確率で抑える |
| [Aho-Corasick 法](../string/aho-corasick.md) | 複数のパターンのどれと一致しているか | 複数パターンの照合・DP |

パターンを 1 つ探すだけなら、ACL にある Z で足りる。KMP 法を自分で書くのは、border を長い順にたどるとき、すべての接頭辞の最小の周期を使うとき、本文が 1 文字ずつ来るとき、照合の状態を DP に載せるときである。

## 参考 {#references}

- [snuke「文字列の頭良い感じの線形アルゴリズムたち」](https://snuke.hatenablog.com/entry/2014/12/01/235807)：MP 法の配列の定義（$A[0] = -1$ の流儀）と、全体で線形になる理由
- [cp-algorithms「Prefix function. Knuth–Morris–Pratt algorithm」](https://cp-algorithms.com/string/prefix-function.html)：$\pi[0] = 0$ の流儀と、各接頭辞の出現回数・オートマトンの応用（構成の参考。文章と図は使っていない）
- [Wikipedia「Knuth–Morris–Pratt algorithm」](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)：KMP 法の 1 文字あたりの比較の回数が黄金比を底とする対数で抑えられること
- [AtCoder Library「String」（document_ja/string.md）](https://github.com/atcoder/ac-library/blob/master/document_ja/string.md)：string の機能の一覧（KMP 法がないこと）と `z_algorithm` の仕様・計算量
- [drken「AtCoder ABC 304 F - Shift Table」](https://drken1215.hatenablog.com/entry/2023/06/07/153403)：例題 abc304_f の約数ごとの数え方とメビウス関数による包除
- [drken「AtCoder ABC 150 F - Xor Shift」](https://drken1215.hatenablog.com/entry/2020/01/12/115800)：例題 abc150_f の差分の列への言い換えと、2 周つないだ列での照合
- [ikatakos「AtCoder Beginner Contest 430」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1101_abc430)：練習 abc430_e の方針（解法の部分だけ）
- [ikatakos「AtCoder Beginner Contest 135」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2019/0727_abc135)：練習 abc135_f の出現位置からの遷移と閉路の判定（解法の部分だけ）
- [kmjp「AtCoder ABC #312 Ex - snukesnuke」](https://kmjp.hatenablog.jp/entry/2023/07/30/0930)：力試し abc312_h の問いと、繰り返しの単位ごとに使った回数を管理する方針
- [merom686「ABC312」](https://merom686.hatenablog.com/entry/2023/07/30/020536)：力試し abc312_h の方針（最小の繰り返し単位への分解と、調べた位置の記録）
- [drken「AtCoder ARC 060 F - 最良表現」](https://drken1215.hatenablog.com/entry/2018/09/07/190100)：力試し arc060_d の答えが 1・2・N に分かれることと、接頭辞・接尾辞の周期の判定
