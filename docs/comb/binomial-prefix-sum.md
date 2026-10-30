---
id: binomial-prefix-sum
title: 二項係数の部分和
aliases: [二項係数の累積和, 'Σ_{k≤K} C(n,k)']
type: overview
field: comb
chapter: 二項係数の系統
order: 140
level: 発展
kind: [数え上げ]
prerequisites: [binomial-precompute]
related: [binomial-identities, inclusion-exclusion, mo-algorithm]
summary: 二項係数の部分和 S(n,K)（k ≤ K の C(n,k) の和）を、S(n+1,K) = 2S(n,K) − C(n,K) などの式で (n, K) を 1 ずつ動かしながら更新する。部分和を大量に使う包除の計算で役に立つ。
complexity: 前計算 O(N)、(n, K) を 1 動かす更新 O(1)、Q 個の (n, K) を Mo の順に処理して O(N√Q + Q log Q)
signs:
  - {type: shape, text: '答えの式に k ≤ K の C(n,k) の和が、多くの (n, K) について現れる'}
acl: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 1 問
sections:
  - {title: 何ができるか, anchor: what}
  - {title: n と K を 1 ずつ動かす更新式, anchor: update}
  - {title: Mo のように動かす順番を工夫する, anchor: order}
  - {title: 包除と組み合わせる例, anchor: with-inclusion-exclusion}
  - {title: 自作するときの要点, anchor: library}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：二項係数の部分和 $S(n, K) = \sum_{k \le K} \binom{n}{k}$ を、$S(n+1, K) = 2S(n, K) - \binom{n}{K}$ などの式で $(n, K)$ を 1 ずつ動かしながら $O(1)$ で更新する。部分和を大量に使う包除の計算で役に立つ。
    - **いつ使うか**：答えの式に $\sum_{k \le K} \binom{n}{k}$ の形の和が、多くの $(n, K)$ について現れる。
    - **計算量**：階乗の前計算 $O(N)$ の後、$(n, K)$ を 1 動かす更新が $O(1)$。$K$ を固定して $n = 0, 1, \dots, N$ のすべてなら合わせて $O(N)$、ばらばらの $Q$ 個の $(n, K)$ なら Mo's algorithm の順に並べて $O(N \sqrt{Q} + Q \log Q)$（$n, K \le N$）
    - **前提**：[二項係数の前計算](../comb/binomial-precompute.md)

<!-- textlint-disable -->
別名：二項係数の累積和・Σ_{k≤K} C(n,k)
<!-- textlint-enable -->

二項係数の部分和は、パスカルの三角形の 1 行の先頭から $K$ 番目までの和である。$\sum_{k=0}^{n} \binom{n}{k} = 2^n$ のような閉じた式はないので、1 つずつ足すと 1 個あたり $O(K)$ かかる。隣の $(n, K)$ との関係を使えば 1 歩 $O(1)$ で移れるので、必要な $(n, K)$ を順にたどって求める。

ABC での出題は少なく、例題の [ABC235 G](#abc235_g)（diff 2462）が代表である。更新式は短いので、式の形と導き方を覚えておけば足りる。

## 何ができるか {#what}

このページの記法：$S(n, K) = \sum_{k=0}^{K} \binom{n}{k}$ とし、$K < 0$ なら $S(n, K) = 0$ とする。$k > n$ の $\binom{n}{k}$ は 0 とみなすので、$K \ge n$ なら $S(n, K) = 2^n$ である（記法の全体は[記法と用語の約束](../start/notation.md)）。

$\binom{n}{k}$ は[二項係数の前計算](../comb/binomial-precompute.md)で 1 個 $O(1)$ になるが、その和 $S(n, K)$ は 1 個求めるのに $O(K)$ かかる。$S(n, K)$ が数個なら足すだけでよい。困るのは、包除の和の各項に別々の $(n, K)$ の部分和が現れ、項が $10^5$〜$10^6$ 個あるときである。全部を足し直すと $O(N^2)$ になる。

ここで次の 2 つが効く。

- 状態 $(n, K)$ から $(n \pm 1, K)$・$(n, K \pm 1)$ へは、二項係数 1 個の計算で移れる（[更新式](#update)）。
- 必要な $(n, K)$ を、移動の合計が少なくなる順にたどる。$K$ が一定で $n$ だけ変わるなら $n$ の順に、2 つともばらばらなら Mo's algorithm の順にする（[動かす順番](#order)）。

サインは「立てた式に $\sum_{k \le K} \binom{n}{k}$ が出て、その $(n, K)$ が多い」ことである。典型は、上限つきの選び方（各グループから $K$ 個以下を選ぶ）を、条件を破る対象の集合で包除するときに出る（[包除と組み合わせる例](#with-inclusion-exclusion)）。

## n と K を 1 ずつ動かす更新式 {#update}

$K$ を動かす式は、和の項を 1 つ足し引きするだけである。

$$
\begin{aligned}
S(n, K+1) &= S(n, K) + \binom{n}{K+1}, \\
S(n, K-1) &= S(n, K) - \binom{n}{K}
\end{aligned}
$$

$n$ を動かす式は、パスカルの三角形の関係 $\binom{n+1}{k} = \binom{n}{k} + \binom{n}{k-1}$ を $k = 0, \dots, K$ で足して得る。

$$
\begin{aligned}
S(n+1, K) &= S(n, K) + S(n, K-1) \\
&= 2S(n, K) - \binom{n}{K}
\end{aligned}
$$

行 $n$ の各項は、下の行の真下と右下の 2 か所へ足し込まれる。和を $k \le K$ で切ると、右端の $\binom{n}{K}$ だけは右下（$k = K+1$）への寄与が範囲の外に出る。だから「2 倍して $\binom{n}{K}$ を引く」になる。

例で確かめる。$S(4, 2) = 1 + 4 + 6 = 11$ で、$S(5, 2) = 1 + 5 + 10 = 16$ である。式では $2 \cdot 11 - \binom{4}{2} = 22 - 6 = 16$ となり一致する。

$n$ を減らす向きは、この式を解いて $S(n-1, K) = \bigl(S(n, K) + \binom{n-1}{K}\bigr) / 2$ とする。mod 998244353 のような奇素数の法では、2 で割る代わりに 2 の逆元を掛ければよい。

式は $K < 0$・$K \ge n$ でもそのまま成り立つ。$K > n$ では $\binom{n}{K} = 0$ なので $S(n+1, K) = 2^{n+1}$、$K = n$ では $\binom{n}{K} = 1$ なので $S(n+1, K) = 2^{n+1} - 1$ になる。範囲外の二項係数を 0 として返す関数を使えば、場合分けはいらない。

## Mo のように動かす順番を工夫する {#order}

必要な $(n, K)$ の並び方で、たどり方を選ぶ。

- **$K$ が一定（または種類が少ない）で $n$ が $0, 1, \dots, N$**：$S(0, K) = 1$（$K \ge 0$）から $n$ を 1 ずつ増やす。$K$ 1 つあたり $O(N)$ である。包除の和ではたいていこの形になる。
- **$n$ が一定で $K$ がいろいろ**：行 $n$ の二項係数を並べた[累積和](../basics/prefix-sum.md)を作れば、どの $K$ も $O(1)$ で引ける。
- **$(n, K)$ がどちらもばらばらで $Q$ 個**：[Mo's algorithm](../ds/mo-algorithm.md#two-prefixes) の区間 $(l, r)$ の代わりに $(n, K)$ を状態として並べる。$n$ をブロックの大きさ $N / \sqrt{Q}$ で分け、ブロックの中は $K$ の順にする。移動の総回数は $O(N \sqrt{Q})$ で、1 歩が $O(1)$ なので全体は $O(N \sqrt{Q} + Q \log Q)$ になる。クエリをすべて先に読む[オフライン](../guide/glossary.md#offline)の処理である。

Mo の順で処理するときは、$n$ を減らす向きも使うので、2 の逆元が要る。クエリに $K = -1$ があれば $K$ を減らす向きでそこまで行くので、$S(n, -1) = 0$ を扱えるようにしておく。

## 包除と組み合わせる例 {#with-inclusion-exclusion}

この節は[包除原理](../comb/inclusion-exclusion.md)を前提にする。

典型は「$N$ 個のグループのどれも空にしない」数え方である。いくつかの種類の対象を、各種類ごとに「どのグループへ入れるか（1 グループに 1 個まで、合計は種類ごとの上限 $K$ 個以下）」だけで区別して配る。同じ種類の対象は区別しないので、ある種類を $m$ 個のグループへ配る方法は入れるグループの選び方で決まり、$S(m, K)$ 通りである。種類が $t$ 個（上限 $K_1, \dots, K_t$）で種類ごとに独立なら、空のグループがない数は、空にすると決めた $k$ 個のグループで包除して

$$
\sum_{k=0}^{N} (-1)^k \binom{N}{k} \prod_{i=1}^{t} S(N-k, K_i)
$$

になる。この和には、上限 $K_i$ を固定した $S(m, K_i)$（$m = 0, 1, \dots, N$）が全部現れる。$K$ が固定で $n$ が 1 ずつ動く形なので、$n$ を増やす更新式で $m$ の順に $O(N)$ で表を作れる。$t$ が定数なら全体も $O(N)$ である（$t = 3$ の場合が[例題 ABC235 G](#abc235_g)）。

この形のサインは「各グループへ入れる数の上限」と「どれも空にしない（少なくとも 1 つ）」の組み合わせである。条件を破る側（空のグループ）を選ぶと、残りのグループでは上限つきの自由な選び方になり、そこに部分和が出る。

## 自作するときの要点 {#library}

ACL に二項係数の部分和はない。自作するときは、状態 $(n, K)$ と値 $s = S(n, K)$ の組を持ち、4 方向の移動を関数にする。保つ性質は「常に $s = S(n, K)$」で、初期状態は $(0, 0)$、$s = 1$ である。コードの `k` が本文の $K$ にあたる。

```cpp
--8<-- "binomial-prefix-sum/mover.cpp:core"
```

完全なプログラム：[`mover.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/binomial-prefix-sum/mover.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }

- $K$ を増やすときは先に $K$ を進めてから $\binom{n}{K}$ を足し、減らすときは先に $\binom{n}{K}$ を引いてから $K$ を戻す。$n$ を動かす式では、増やすときは動かす前の $n$、減らすときは動かした後の $n$ の二項係数を使う。順番を取り違えると 1 つずれた項を足し引きする。
- 二項係数の表は、たどる範囲の最大の $n$ まで作る。範囲外の $(n, k)$ で 0 を返す関数にしておく（[表の大きさと範囲外の 0](../comb/binomial-precompute.md#table-size)）。
- 区間の Mo と違って、$(n, K)$ には通ってはいけない状態がない（$K > n$ や $K = -1$ でも式が成り立つ）ので、4 方向はどの順に動かしてもよい。$K$ は目標の値より小さくならないので、クエリに $K = -1$ がなければ $S(n, -1)$ も通らない。

完全なプログラム（[`snippets/binomial-prefix-sum/mover.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/binomial-prefix-sum/mover.cpp)）は、クエリを Mo の順に並べて処理し、`n_max` が 60 以下のときは各答えを愚直な和と `assert` で比べる。

Library Checker には二項係数の部分和そのものの問題はない。二項係数の部分は Binomial Coefficient (Prime Mod) で確かめられる。部分和は、小さい $n$ で愚直に足した値と比べるのが確実である。

## 学ぶための資料 {#resources}

- [ikatakos「HHKB Programming Contest 2022（AtCoder Beginner Contest 235）F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0115_abc235)の G 問題の節：パスカルの三角形で値が下の行へ 2 回ずつ足し込まれることから、$n$ を 1 増やす式を導いている。
- [kmjp「AtCoder ABC #235 : G - Gardens」](https://kmjp.hatenablog.jp/entry/2022/01/17/0900)：包除の式と、部分和の表を $n$ の順に埋めるコード。
- 2 つの座標を Mo の順に動かす考え方は [Mo's algorithm の 2 つの接頭辞の節](../ds/mo-algorithm.md#two-prefixes)にまとめた。

## 例題 {#examples}

### ABC235 G. Gardens {#abc235_g}

<div class="kp-problems" data-role="example" markdown>

- [ABC235 G. Gardens](https://atcoder.jp/contests/abc235/tasks/abc235_g)（diff 2462）：N 個の庭に 3 種類の苗（それぞれ A 本・B 本・C 本まで）を、1 つの庭に同じ種類は 1 本までとして植える方法のうち、どの庭にも 1 本以上植えるものの数を求める。

</div>

方針：空の庭の集合で包除する。空にする庭を $k$ 個決めると、残りの $N - k$ 個の庭では種類ごとに独立に植えてよい。種類ごとの方法の数は植える庭の選び方で、$S(N-k, A)$ などになる。$S(m, A)$・$S(m, B)$・$S(m, C)$ を $m = 0, \dots, N$ について $n$ を増やす更新式で求めれば、全体が $O(N)$ になる。

??? note "解法の詳細"
    - 同じ種類の苗は区別しないので、ある種類を $m$ 個の庭に植える方法は「植える庭の集合」で決まる。苗を区別すると数え方が変わり、部分和にならない。
    - 答えの式で $k$ 個の庭を空にすると決めた数え方は、「少なくともその $k$ 個が空」の数になっている。
    - $S(m+1, A) = 2S(m, A) - \binom{m}{A}$ で、$m < A$ の間は $\binom{m}{A} = 0$ なので値は $2^m$ のまま進む。
    - 階乗の表は $N$ まで作る。$N$ が大きいので $O(N)$ の解法が要る。$S$ を毎回足し直すと $O(N \cdot \max(A, B, C))$ で間に合わない。

## 参考 {#references}

- [ikatakos「HHKB Programming Contest 2022（AtCoder Beginner Contest 235）F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0115_abc235)：学ぶための資料。$n$ を 1 増やす更新式の導き方と、例題 ABC235 G の包除の式（解法の節だけを読んだ）
- [kmjp「AtCoder ABC #235 : G - Gardens」](https://kmjp.hatenablog.jp/entry/2022/01/17/0900)：例題 ABC235 G の方針と、部分和の表を $n$ の順に埋める実装
- [yosupo「Library Checker の問題（enumerative_combinatorics）」](https://github.com/yosupo06/library-checker-problems/tree/master/enumerative_combinatorics)：二項係数の部分和の問題がないことと、二項係数の検証に使う問題の確認
