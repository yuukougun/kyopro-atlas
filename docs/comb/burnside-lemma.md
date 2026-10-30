---
id: burnside-lemma
title: Burnside の補題
aliases: [Pólya の数え上げ定理, ネックレス, 数珠順列, 回転で同一視して数える, Burnside's lemma]
type: overview
field: comb
chapter: 数え方の考え方
order: 110
level: 発展
kind: [数え上げ]
prerequisites: [counting-dedup]
related: [divisor-inclusion-exclusion, euler-phi, gcd-lcm]
summary: 回転・反転などで同一視したときの異なるものの数を、各操作で動かないものの数の平均として求める。重複度が対象ごとに違って単純に割れないときに使い、回転だけの数珠は d | n の φ(d) k^(n/d) の和を n で割った値になる。
complexity: 数珠（回転のみ）は素因数分解 O(√n) と約数ごとの累乗 O(D log n)（D は n の約数の個数）。一般には操作の型ごとに動かないものを 1 回ずつ数える
signs:
  - {type: phrase, text: 回転（反転）して一致するものは同じとみなす}
  - {type: phrase, text: 数珠・ネックレスの塗り方の数}
  - {type: phrase, text: 立方体の面の塗り方（書き込み方）の数}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 何ができるか（同一視したものの数 = 動かないものの数の平均）, anchor: what}
  - {title: なぜ単純に操作の数で割れないか, anchor: why-not-divide}
  - {title: 数珠（回転のみ）の式, anchor: necklace}
  - {title: 最短周期で分類して割る方法（約数包除の形）, anchor: by-period}
  - {title: 立方体の 24 通りの回転, anchor: cube}
  - {title: 自作するときの要点と検証, anchor: library}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：回転・裏返しなどで同一視したときの異なるものの数を、各操作で動かないものの数の平均として求める。重複度が対象ごとに違って単純に割れないときに使い、回転だけの数珠は $\frac{1}{n} \sum_{d \mid n} \varphi(d) k^{n/d}$ になる。
    - **いつ使うか**：
        - 回転（反転）して一致するものは同じとみなす。
        - 数珠・ネックレスの塗り方の数。
        - 立方体の面の塗り方（書き込み方）の数。
    - **計算量**：数珠（回転のみ）は $n$ の素因数分解 $O(\sqrt{n})$ と約数ごとの累乗 $O(D \log n)$（$D$ は $n$ の約数の個数）。一般には、操作を型で分け、型ごとに動かないものを 1 回ずつ数える
    - **前提**：[重複の除き方](../comb/counting-dedup.md)

<!-- textlint-disable -->
別名：Pólya の数え上げ定理・ネックレス・数珠順列・回転で同一視して数える・Burnside's lemma
<!-- textlint-enable -->

Burnside の補題は、「回して重なるものは同じ」とみなしたときの種類の数を、操作ごとに「その操作で変わらないもの」を数えて平均する形に言い換える定理である。同一視した後の対象を直接数える代わりに、同一視する前の対象を操作ごとに数えればよくなる。ABC では difficulty 2400 以上で現れる程度だが、式の形を知っていれば数珠・立方体の問題は機械的に立式できる。

## 何ができるか（同一視したものの数 = 動かないものの数の平均） {#what}

数える対象の集合を $X$（たとえば長さ $n$ の色の列 $k^n$ 通り）、同一視に使う操作の集合を $G$（たとえば $0, 1, \dots, n-1$ 個ずらす回転）とする。$G$ は「どの 2 つの操作を続けても $G$ の操作になり、何もしない操作を含み、どの操作にも元に戻す操作が $G$ の中にある」ものとする。回転だけ・回転と裏返し・立方体の回転は、どれもこれを満たす。

$x$ に $G$ の操作を施して得られるものをすべて集めた集合を、$x$ の**軌道**と呼ぶ。同一視した後の 1 種類が 1 つの軌道にあたる。Burnside の補題は次の等式である。

$$
(\text{軌道の数}) = \frac{1}{\lvert G \rvert} \sum_{g \in G} \lvert \mathrm{Fix}(g) \rvert
$$

$\mathrm{Fix}(g)$ は $X$ のうち、操作 $g$ を施しても変わらないもの（$g$ の[固定点](../guide/glossary.md#fixed-point)）の集合である。

4 個の玉の輪を 2 色（白・黒）で塗り、回転で重なるものを同じとみなす例で確かめる。

- 回さない：16 通りすべてが変わらない
- 1 個ずらす・3 個ずらす：全部が同じ色の 2 通りだけが変わらない
- 2 個ずらす：向かい合う玉が同じ色なら変わらないので、$2^2 = 4$ 通り

平均は $(16 + 2 + 4 + 2) / 4 = 6$ である。実際に列挙すると、白 4・白 3 黒 1・白 2 黒 2（同じ色が隣り合う）・白 2 黒 2（交互）・白 1 黒 3・黒 4 の 6 種類になる。

??? note "証明（組を 2 通りに数える）"
    $g \cdot x = x$ を満たす組 $(g, x)$ の数を[2 通りに数える](../guide/glossary.md#double-counting)。$g$ ごとに数えると $\sum_g \lvert \mathrm{Fix}(g) \rvert$ である。$x$ ごとに数えると、$x$ を変えない操作の集合 $\mathrm{Stab}(x)$ の大きさの和 $\sum_x \lvert \mathrm{Stab}(x) \rvert$ になる。

    $x$ を $y$ に移す操作のどれか 1 つを $h$ とすると、$x$ を $y$ に移す操作はすべて「$\mathrm{Stab}(x)$ の操作を施してから $h$」の形にちょうど 1 通りずつ書ける。よって軌道の各要素へ移す操作は $\lvert \mathrm{Stab}(x) \rvert$ 個ずつあり、$\lvert G \rvert = (\text{軌道の大きさ}) \times \lvert \mathrm{Stab}(x) \rvert$ が成り立つ。1 つの軌道の要素について $\lvert \mathrm{Stab}(x) \rvert$ を足すと $\lvert G \rvert$ になるので、全体の和は $\lvert G \rvert \times (\text{軌道の数})$ である。両辺を $\lvert G \rvert$ で割れば補題が出る。

## なぜ単純に操作の数で割れないか {#why-not-divide}

軌道の大きさがすべて $\lvert G \rvert$ なら、$\lvert X \rvert / \lvert G \rvert$ で済む（[重複度が一定なら割る](../comb/counting-dedup.md#divide)）。しかし自分自身に重なる対象があると、軌道が小さくなる。4 個の玉の例では、白黒が交互の塗り方は 2 個ずらすと元に戻るので、軌道は 2 個しかない。全部が同じ色なら軌道は 1 個である。$16 / 4 = 4$ は答えの 6 と合わない。

Burnside の補題は、この「小さな軌道」を、それを変えない操作の分だけ多く数えて補う。$x$ を変えない操作の集合を $\mathrm{Stab}(x)$ とすると、軌道の大きさは $\lvert G \rvert / \lvert \mathrm{Stab}(x) \rvert$ である（[証明](#what)を参照）。したがって、変わらない操作の多い対象ほど軌道が小さく、和の中で多く数えられて、ちょうど釣り合う。

代表元を 1 つ決める方法（[重複度が一定でないなら代表元を決める](../comb/counting-dedup.md#representative)）は、「辞書順で最小の回転」のような代表の条件を数えやすく書けるときに使える。数珠や立方体では代表の条件が数えにくいので、Burnside の補題で操作の側から数える方が楽である。

## 数珠（回転のみ）の式 {#necklace}

$n$ 個の玉の輪を $k$ 色で塗り、回転で重なるものを同じとみなす。$s$ 個ずらす回転は、玉の位置を長さ $n / \gcd(n, s)$ の巡回 $\gcd(n, s)$ 個に分ける（[置換の巡回分解](../comb/permutation-cycles.md)）。この回転で変わらないのは、各巡回の玉がすべて同じ色の塗り方なので、$\lvert \mathrm{Fix} \rvert = k^{\gcd(n, s)}$ である。

$0 \le s < n$ のうち $\gcd(n, s) = n / d$ となる $s$ は $\varphi(d)$ 個ある（[オイラーの φ 関数](../math/euler-phi.md#divisor-sum)）。同じ $\gcd$ の回転をまとめると、次の式になる。

$$
\frac{1}{n} \sum_{s=0}^{n-1} k^{\gcd(n, s)} = \frac{1}{n} \sum_{d \mid n} \varphi(d)\, k^{n/d}
$$

$n = 6$、$k = 4$ なら $(4^6 + 1 \cdot 4^3 + 2 \cdot 4^2 + 2 \cdot 4) / 6 = 4200 / 6 = 700$ である。$4^6 / 6$ が整数にならないのに、和は必ず $n$ で割り切れる。

**裏返しも同じとみなす**ときは、$n$ 個の回転に $n$ 個の裏返しを加えた $2n$ 個の操作で平均する。裏返しで変わらない塗り方の数は、軸の通り方で決まる。

- $n$ が奇数：軸はどれも玉 1 個を通り、巡回は $(n + 1)/2$ 個なので $k^{(n+1)/2}$ 通りが $n$ 本
- $n$ が偶数：玉 2 個を通る軸が $n/2$ 本（$k^{n/2 + 1}$ 通り）、玉を通らない軸が $n/2$ 本（$k^{n/2}$ 通り）

**色の個数が決まっている**ときも、巡回ごとに同じ色という考え方は変わらない。赤 2 個・青 2 個を 4 個の輪に並べると、回さない操作では $\binom{4}{2} = 6$ 通り、2 個ずらす回転（長さ 2 の巡回が 2 個）ではどちらの巡回を赤にするかの 2 通り、1 個・3 個ずらす回転（長さ 4 の巡回が 1 個）では 0 通りである。平均 $(6 + 0 + 2 + 0) / 4 = 2$ が答えになる（[円順列の落とし穴](../comb/counting-basics.md#permutations)の例と同じ）。

一般に、回転では巡回の長さがすべて同じ $L$ になる（巡回は $c = n/L$ 個）。色 $i$ を $a_i$ 個使うとき、すべての $a_i$ が $L$ の倍数なら、変わらない並べ方は $c$ 個の巡回に色を割り当てる多項係数 $\frac{c!}{\prod_i (a_i/L)!}$ 通りで、そうでなければ 0 通りである。上の 2 個ずらす回転なら $2!/(1!\,1!) = 2$ になる。

答えを素数 $p$ で割った余りで求めるときは、最後の $1/n$ を[逆元](../math/mod-inverse.md)で掛ける。$n$ が $p$ の倍数だと逆元がない。$p = 998244353$ と $n < p$ の組なら問題にならない。

## 最短周期で分類して割る方法（約数包除の形） {#by-period}

Burnside の補題を使わず、列の[周期](../guide/glossary.md#period)で分けて割る方法もある。長さ $n$ の列のうち、$n$ の約数である最短の周期がちょうど $d$ のものの数を $f(d)$ とする。

- 最短周期が $d$ の列は、回すとちょうど $d$ 種類の列になる（$d$ 個ずらすと元に戻り、それより少ないずらし方では戻らない）
- よって最短周期が $d$ の列からなる輪は $f(d)/d$ 種類で、答えは $\sum_{d \mid n} f(d) / d$ である

$f(d)$ は、周期 $d$ を持つ列の数 $k^d$ から、$d$ の真の約数 $e$ の $f(e)$ を小さい順に引いて求める（[約数包除の周期の数え上げ](../comb/divisor-inclusion-exclusion.md#period)）。$n = 4$、$k = 2$ なら $f(1) = 2$、$f(2) = 4 - 2 = 2$、$f(4) = 16 - 2 - 2 = 12$ で、答えは $2/1 + 2/2 + 12/4 = 6$ になり、Burnside の補題と一致する。

この方法は、軌道ごとに重複度がそろうように分類してから割る、という[重複の除き方](../comb/counting-dedup.md)の基本の考え方をそのまま使う。$f(d)$ の数え方が問題の条件（積・和の制約など）で変わるときや、列の長さが 1 つに決まっていないときに立式しやすい。[例題の ABC428 G](#abc428_g) はこの形で解ける。

## 立方体の 24 通りの回転 {#cube}

立方体を回す操作（裏返しは含まない）は 24 通りある。立方体の面の塗り方・書き込み方を数えるときは、6 面の位置を回転がどう入れ替えるかの巡回の型で 5 つに分ける。

| 回転の種類 | 個数 | 6 面の巡回の長さ |
| --- | --- | --- |
| 回さない | 1 | 1・1・1・1・1・1 |
| 向かい合う面の中心を通る軸で 90 度・270 度 | 6 | 1・1・4 |
| 向かい合う面の中心を通る軸で 180 度 | 3 | 1・1・2・2 |
| 向かい合う頂点を通る軸で 120 度・240 度 | 8 | 3・3 |
| 向かい合う辺の中点を通る軸で 180 度 | 6 | 2・2・2 |

個数の合計は 24 で、巡回の型ごとの個数はコード片 [`snippets/burnside-lemma/cube.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/burnside-lemma/cube.cpp) で 90 度回転 2 つから 24 通りを生成して確かめた。$k$ 色で面を塗るなら、巡回ごとに 1 色なので

$$
\begin{aligned}
&\frac{k^6 + 6k^3 + 3k^4 + 8k^2 + 6k^3}{24} \\
&= \frac{k^6 + 3k^4 + 12k^3 + 8k^2}{24}
\end{aligned}
$$

で、$k = 2$ なら 10 通り、$k = 3$ なら 57 通りになる（同じコード片で全列挙と比べた）。

面に数を書いて合計を決める問題では、巡回の長さが重みになる。長さ $L$ の巡回の面にはすべて同じ数 $x$ が入るので、合計への寄与は $L x$ である。たとえば 90 度の回転なら、変わらない書き方の数は $a + b + 4c = S$ の解の数になる（[例題の ABC198 F](#abc198_f)）。

## 自作するときの要点と検証 {#library}

ACL に Burnside の補題に当たる関数はない。自作するときの要点は次のとおりである。

- 操作を 1 つずつ回さず、巡回の型が同じ操作をまとめて「型ごとの $\lvert \mathrm{Fix} \rvert$ × 個数」で足す。数珠では型が $n$ の約数ごとに決まるので、約数の列挙で済む
- $\lvert \mathrm{Fix}(g) \rvert$ は「$g$ の各巡回の上で同じ値」という条件で数える。巡回の長さが重み（個数の倍数条件や和の係数）として現れる
- 最後に $\lvert G \rvert$ で割る。mod なら逆元を掛け、$\lvert G \rvert$ が法の倍数でないことを確かめる
- 回転だけか、裏返しも含むかを最初に決める（裏返しを含むと $\lvert G \rvert$ が 2 倍になる）

数珠の式の中心は次のとおりである。$n$ を素因数分解して約数 $d$ と $\varphi(d)$ を同時に作る（[約数列挙](../math/divisor-enum.md)・[素因数分解](../math/prime-factorization.md)）。

```cpp
--8<-- "burnside-lemma/necklace.cpp:core"
```

完全なプログラム：[`necklace.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/burnside-lemma/necklace.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

裏返しも同じとみなす版は、回転の和に裏返しの和を足して $2n$ で割る。

```cpp
--8<-- "burnside-lemma/necklace.cpp:bracelet"
```

完全なプログラム：[`necklace.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/burnside-lemma/necklace.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

コード片では、最短周期で分類する版（`necklace_by_period`）も持ち、$n \le 8$、$k \le 3$ で全列挙（回した列のうち辞書順で最小のものだけを数える）と 3 つの関数を比べて確かめている。

Library Checker に Burnside の補題をそのまま問う問題はない。小さい場合を全列挙と比べて確かめるのが確実である。$n$ が $10^{18}$ 程度まで大きいときは素因数分解が試し割りでは間に合わないので、その部分を Library Checker の Factorize で確かめた方法（[大きな数の素因数分解](../math/miller-rabin.md#pollard-rho)）に替える。

## 落とし穴 {#pitfalls}

- **裏返しを含めるか**：ネックレスを裏返せるかどうかで答えが変わる。$n = 6$、$k = 4$ では回転だけなら 700 通り、裏返しも含めると 430 通りである。立方体は回転だけ（鏡に映した形は別）が普通である
- **$\lvert G \rvert$ で割るのは最後**：操作ごとに $\lvert \mathrm{Fix}(g) \rvert / \lvert G \rvert$ を足すと、mod でない計算では端数が出る。和を取ってから割る
- **変わらないものの数え方**：「回しても同じ」は「各巡回の上で値が等しい」ことで、「全体が同じ色」ではない。2 個ずらす回転では、交互に塗った輪も変わらない

## 学ぶための資料 {#resources}

- [Wikipedia「バーンサイドの補題」](https://ja.wikipedia.org/wiki/%E3%83%90%E3%83%BC%E3%83%B3%E3%82%B5%E3%82%A4%E3%83%89%E3%81%AE%E8%A3%9C%E9%A1%8C)（日本語）：補題の正確な形と、軌道と固定点の言葉づかい
- [pctsnote「バーンサイドの補題」](https://scrapbox.io/pctsnote/%E3%83%90%E3%83%BC%E3%83%B3%E3%82%B5%E3%82%A4%E3%83%89%E3%81%AE%E8%A3%9C%E9%A1%8C)（Scrapbox）：小さな例での確かめと、ABC198 F で立方体の回転を 5 つの型に分ける考え方
- [cp-algorithms「Burnside's lemma / Pólya enumeration theorem」](https://cp-algorithms.com/combinatorics/burnside.html)（英語）：証明と、ネックレスの式・色の数を変数にした Pólya の数え上げ定理への一般化

## 例題 {#examples}

### ABC428 G. Necklace {#abc428_g}

<div class="kp-problems" data-role="example" markdown>

- [ABC428 G. Necklace](https://atcoder.jp/contests/abc428/tasks/abc428_g)（diff 2472）：美しさの決まった何種類かの宝石を何個でも使って輪のネックレスを作るとき、美しさの積が x になるもの（回転で一致するものは同じ、裏返しは区別）の数を、2 以上 U 以下の各 x について求める。

</div>

方針：輪の長さは決まっていない。ただし美しさが 2 以上なので、積が $U$ 以下の列の長さは $\log_2 U$ 程度に収まる。長さ $l$・積 $m$ の列の数 $F(l, m)$ を DP で求め、[最短周期で分類する方法](#by-period)で「最短周期がちょうど $l$ の列」の数 $G(l, m)$ に直して $l$ で割る。

??? note "解法の詳細"
    - $F(l, m)$：長さ $l$ の列で美しさの積が $m$ のものの数。長さを 1 ずつ伸ばす DP にする。積の倍数を回るので、1 段あたり調和級数の和の時間で済む
    - 長さ $l$ で最短周期が $e$ の列は、最短周期 $e$ の列（積 $r$）を $l/e$ 回繰り返したものである。全体の積は $r^{l/e}$ になる。よって $G(l, m) = F(l, m) - \sum_{e \mid l,\ e < l} G(e, m^{e/l})$（$m$ が $l/e$ 乗数のときだけ引く）
    - 長さ $l$・積 $x$ の輪は、最短周期 $e$ ごとに $G(e, x^{e/l}) / e$ 種類ある。これを $l$ と $e$ について足すと $x$ の答えになる
    - Burnside の補題で書いても同じ式になる。長さ $l$ の列を $s$ 個ずらして変わらないのは、長さ $g = \gcd(l, s)$ の列を繰り返したもので、その数は $F(g, x^{g/l})$ である
    - 全体で $O(U \log^2 U)$ 程度

### ABC198 F. Cube {#abc198_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC198 F. Cube](https://atcoder.jp/contests/abc198/tasks/abc198_f)（diff 2769）：立方体の 6 面に正の整数を書き、合計が S になる書き方の数を、回転で一致するものを同じとみなして求める。

</div>

方針：[立方体の 24 通りの回転](#cube)を 5 つの型に分け、型ごとに「回しても変わらない書き方」を数えて平均する。変わらない書き方は、各巡回の面に同じ数を書くものなので、巡回の長さを係数にした一次方程式の正の整数解の数になる。

??? note "解法の詳細"
    - 型ごとの方程式と個数：回さない $a + b + c + d + e + f = S$（1 個）、面の軸で 90 度 $a + b + 4c = S$（6 個）、面の軸で 180 度 $a + b + 2c + 2d = S$（3 個）、頂点の軸 $3a + 3b = S$（8 個）、辺の軸 $2a + 2b + 2c = S$（6 個）
    - 答えは、個数を重みにした解の数の和を 24 で割ったもの。mod では 24 の逆元を掛ける
    - 解の数は母関数の係数で、たとえば $a + b + 4c = S$ の正の整数解の数は $\frac{x^6}{(1-x)^2 (1-x^4)}$ の $x^S$ の係数である（各変数が $\frac{x^L}{1 - x^L}$）。$S$ が大きいので、分母から決まる線形漸化式の第 $S$ 項として、[行列累乗](../math/matrix-power.md)か [線形漸化式の高速な計算](../math/linear-recurrence-fast.md)で求める
    - 回さない型は $\binom{S-1}{5}$ で、5 個の積 $(S-1)(S-2)\cdots(S-5)$ に $5!$ の逆元を掛ければ $S$ が大きくても求まる（前計算の表は使えない）。型ごとに閉じた式を作るより、すべての型を同じ漸化式の方法で求める方が場合分けが減る

## 確認問題 {#quiz}

??? question "確認問題：5 個の玉の輪を 3 色で塗る方法（回転で同一視）を、2 つの方法で求めよ"
    Burnside の補題：$5$ は素数なので、回さない操作が $3^5 = 243$ 通り、残りの 4 個の回転がそれぞれ全部同じ色の 3 通りで、$(243 + 4 \cdot 3)/5 = 51$ 通り。

    最短周期で分類：$f(1) = 3$、$f(5) = 243 - 3 = 240$ で、$3/1 + 240/5 = 3 + 48 = 51$ 通り。

??? question "確認問題：6 個の玉の輪を 2 色で塗る方法（回転で同一視）は何通りか。$2^6 / 6$ では求まらない理由も答えよ"
    $2^6 / 6$ は整数にならない。白黒が交互の塗り方などは自分自身に重なり、軌道の大きさが 6 より小さいからである。Burnside の補題では、$\gcd(6, s)$ が 6・1・2・3・2・1 なので $(2^6 + 2 + 2^2 + 2^3 + 2^2 + 2)/6 = 84/6 = 14$ 通り。

??? question "確認問題：5 個の玉の輪を 3 色で塗る方法を、裏返しも同一視して求めよ"
    回転の和は上の問いの $243 + 4 \cdot 3 = 255$。$5$ は奇数なので、裏返し 5 本はどれも巡回が $3$ 個で $3^3 = 27$ 通りずつ。$(255 + 5 \cdot 27)/10 = 39$ 通り。

## 参考 {#references}

- [Wikipedia「バーンサイドの補題」](https://ja.wikipedia.org/wiki/%E3%83%90%E3%83%BC%E3%83%B3%E3%82%B5%E3%82%A4%E3%83%89%E3%81%AE%E8%A3%9C%E9%A1%8C)：学ぶための資料。補題の形と用語
- [pctsnote「バーンサイドの補題」](https://scrapbox.io/pctsnote/%E3%83%90%E3%83%BC%E3%83%B3%E3%82%B5%E3%82%A4%E3%83%89%E3%81%AE%E8%A3%9C%E9%A1%8C)：学ぶための資料。例題 ABC198 F で立方体の回転を型に分ける考え方
- [cp-algorithms「Burnside's lemma / Pólya enumeration theorem」](https://cp-algorithms.com/combinatorics/burnside.html)：学ぶための資料。証明とネックレスの式の確認（文章・図は使っていない）
- [yosupo「Library Checker の問題（number_theory）」](https://github.com/yosupo06/library-checker-problems/tree/master/number_theory)：Burnside の補題をそのまま問う問題がないことと、Factorize の確認
- [kmjp「AtCoder ABC #428 (Promotion of AtCoderJobs) : G - Necklace」](https://kmjp.hatenablog.jp/entry/2025/10/18/0900)：例題 ABC428 G の方針（最短周期で分けて割る）
- [ikatakos「AtCoder Beginner Contest 428（Promotion of AtCoderJobs）D,E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1018_abc428)：例題 ABC428 G の方針と計算量（解法の節だけを読んだ）
- [kmjp「AtCoder ABC #198 : F - Cube」](https://kmjp.hatenablog.jp/entry/2021/04/11/0900)：例題 ABC198 F の 5 つの型と方程式、行列累乗による解の数の計算
