---
id: sparse-table
title: Sparse Table
aliases: [スパーステーブル, ST 表, 静的 RMQ, Disjoint Sparse Table]
type: technique
field: ds
chapter: 区間クエリ
order: 240
level: 青
kind: [データ構造, 区間クエリ, ダブリング・分割統治]
prerequisites: [doubling]
related: [segment-tree, lca, prefix-sum, suffix-array, divide-and-conquer]
summary: 更新のない列で、冪等な演算（min・max・gcd・and・or）の区間クエリに、前処理 O(N log N)・質問 O(1) で答える。長さ 2^k の区間の答えを持ち、質問は重なってよい 2 つの区間で覆う。
complexity: 前処理 O(N log N)（メモリも同じ）、冪等な演算の取得 O(1)。冪等でない演算は取得 O(log N)、Disjoint Sparse Table なら前処理 O(N log N)・取得 O(1)。更新はできない
signs:
  - {type: phrase, text: 配列が変わらず、区間の最小値・最大値・gcd を非常に多く聞かれる}
  - {type: constraint, text: クエリが 10^6 級で、1 回 O(1) で答えたい}
acl: []
verify: [staticrmq]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 何ができるか（静的・冪等な演算なら O(1)）, anchor: what-it-does}
  - {title: なぜ重なってよいか（冪等）と k = ⌊log₂ L⌋, anchor: idempotent}
  - {title: 作り方（長さが 2 のべきの区間の表と log の表）, anchor: build}
  - {title: 冪等でない演算（2 べきに分けて O(log N)、Disjoint Sparse Table）, anchor: disjoint-sparse-table, level: 発展}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：更新のない列で、[冪等](../guide/glossary.md#idempotent)な演算（min・max・gcd・AND・OR）の区間クエリに、前処理 $O(N \log N)$・取得 $O(1)$ で答える。長さ $2^k$ の区間の答えを表に持ち、問われた区間を重なってよい 2 つの区間で覆う。
    - **いつ使うか**：
        - 配列が変わらず、区間の最小値・最大値・gcd を非常に多く聞かれる。
        - クエリが $10^6$ 級で、1 回 $O(1)$ で答えたい。
    - **計算量**：前処理 $O(N \log N)$（メモリも $O(N \log N)$）、冪等な演算の取得 $O(1)$。冪等でない演算は取得 $O(\log N)$、Disjoint Sparse Table なら前処理 $O(N \log N)$・取得 $O(1)$。更新はできない。
    - **前提**：[ダブリング](../basics/doubling.md)

<!-- textlint-disable -->
別名：スパーステーブル・ST 表・静的 RMQ・Disjoint Sparse Table
<!-- textlint-enable -->

Sparse Table は、各位置から始まる長さ $1, 2, 4, 8, \dots$ の区間の答えを表に前計算しておき、区間の最小値などを表の 2 か所を見るだけで答えるデータ構造である。表の作り方は、添字を 1 つずつ進める遷移の[ダブリング](../basics/doubling.md#aggregates)そのものである。列が変わらないことと、演算が「同じものを 2 回使っても結果が変わらない」ことを使って、取得を $O(1)$ にしている。

## 何ができるか（静的・冪等な演算なら O(1)） {#what-it-does}

Sparse Table は、長さ $N$ の列 $a_0, \dots, a_{N-1}$（0-indexed）が最後まで変わらないとき、[半開区間](../guide/glossary.md#half-open-interval) $[l, r)$（$l < r$）について $a_l \cdot a_{l+1} \cdot \dots \cdot a_{r-1}$ を $O(1)$ で返す。演算 $\cdot$ には次の 2 つが要る。

- [結合法則](../guide/glossary.md#associativity)：$(x \cdot y) \cdot z = x \cdot (y \cdot z)$
- 冪等：どの $x$ でも $x \cdot x = x$

min・max・gcd・AND・OR はどちらも満たす。和・積・XOR は冪等でない（$x + x \ne x$、$x \oplus x = 0$）ので、そのままでは使えない。和なら[累積和](../basics/prefix-sum.md)で足り、引き算できない演算は[冪等でない演算](#disjoint-sparse-table)の方法を使う。

[セグメント木](../ds/segment-tree.md)でも区間の最小値は 1 回 $O(\log N)$ で求まるので、ABC で Sparse Table が必須になることはまれである。差が出るのは、区間の取得をほかの処理の内側で何度も呼ぶときである。たとえば区間の最小値を外側から二分探索で呼ぶと、セグメント木なら $O(\log^2 N)$（木を降りる `max_right` を使えば $O(\log N)$）、Sparse Table なら $O(\log N)$ になる。$N \log N$ 回の取得を呼ぶ処理でも、1 回 $O(1)$ なら全体が $O(N \log N)$ に収まる。

ほかの手法の部品として使う型が多い。

- **LCA**：木を DFS で回り、頂点に着くたびその頂点を記録した長さ $2N - 1$ の列を作る。2 頂点の位置の間で最も浅い頂点が LCA なので、深さの区間最小で求まる（[LCA](../tree/lca.md#comparison)）
- **LCP**：[Suffix Array](../string/suffix-array.md#lcp-rmq) では、2 つの接尾辞の最長共通接頭辞の長さが LCP 配列の区間最小になる
- **区間の gcd**：$\gcd(x_1, \dots, x_k) = \gcd(x_1, x_2 - x_1, \dots, x_k - x_{k-1})$ を使うと、各項に同じ値を足した列の gcd や、$(i, j)$ 成分が $A_i + B_j$ の行列の長方形の gcd は、隣り合う項の差の区間 gcd に直る（[gcd の性質](../math/gcd-properties.md)）。列が変わらなければ Sparse Table で引ける
- **最大値の位置**：値と添字の組 $(a_i, i)$ を辞書順の max で結べば、区間の最大値の位置が求まる。組の max も冪等である。最大値の位置で区間を左右に分ける[分割統治](../basics/divide-and-conquer.md#split-at-max)で、分ける位置を $O(1)$ で引ける
- **区間の集合を設計する**：[ABC282 F](#abc282_f) のように、「どの区間も用意した 2 つの区間の和集合で表せる」集合を作らせる問題では、Sparse Table が持つ区間の集合がそのまま答えになる

## なぜ重なってよいか（冪等）と k = ⌊log₂ L⌋ {#idempotent}

Sparse Table の表 $\mathrm{st}[k][i]$ は、区間 $[i, i + 2^k)$ の演算の結果である。長さ $L = r - l$ の区間 $[l, r)$ を問われたら、$2^k \le L$ を満たす最大の $k$、すなわち $k = \lfloor \log_2 L \rfloor$ をとる。そして左端から伸ばした $[l, l + 2^k)$ と、右端から伸ばした $[r - 2^k, r)$ の 2 つの答えを結ぶ。

$$
a_l \cdot \dots \cdot a_{r-1} = \mathrm{st}[k][l] \cdot \mathrm{st}[k][r - 2^k]
$$

次の図は、列 $(5, 3, 7, 9, 6, 4, 8, 1)$ で区間 $[1, 7)$ の最小値を求める例である。$L = 6$ なので $k = 2$ になり、長さ 4 の区間 $[1, 5)$ と $[3, 7)$ を使う。2 つは $[3, 5)$ で重なる。

![列 5 3 7 9 6 4 8 1 の区間 1 から 7 の最小値を、長さ 4 の区間 1 から 5（最小値 3）と 3 から 7（最小値 4）の 2 つで覆い、min(3, 4) = 3 と求める。下は k = 0 から 3 の表で、st[2][1] = 3 と st[2][3] = 4 を読む](../img/sparse-table/cover.svg)

図の要点を文章で書くと次のとおりである。

- 表の $k = 2$ の段の $\mathrm{st}[2][1] = \min(3, 7, 9, 6) = 3$ と、$\mathrm{st}[2][3] = \min(9, 6, 4, 8) = 4$ を読む
- 答えは $\min(3, 4) = 3$ で、区間 $[1, 7)$ の最小値と一致する。重なりの $9$ と $6$ は 2 回使われるが、min は同じ値を 2 回使っても結果が変わらない

**2 つの区間で過不足なく覆える理由**：$k$ の決め方から $2^k \le L < 2^{k+1}$ である。$2^k \le L$ なので、2 つの区間はどちらも $[l, r)$ の中に収まる。$L < 2^{k+1}$ なので $l + 2^k > r - 2^k$ となり、2 つの区間の間にすき間はない。よって 2 つの和集合は $[l, r)$ にちょうど一致する。

**重なっても答えが変わらない理由**：重なりの部分の結果を $B$ とし、区間を左から「左だけの部分 $A$」「重なり $B$」「右だけの部分 $C$」に分ける。左の区間の結果は $A \cdot B$、右の区間の結果は $B \cdot C$ である。結合法則で $(A \cdot B) \cdot (B \cdot C) = A \cdot (B \cdot B) \cdot C$ と組み替え、冪等から $B \cdot B = B$ なので $A \cdot B \cdot C$ になる。$L = 2^k$ で 2 つの区間が一致し、$A$ や $C$ が空になるときは、その部分を式から除けばよく、$B \cdot B = B$ だけで済む。左の区間を先に結べば、交換法則は要らない。

和では $B + B \ne B$ なので、重なりを 2 回数えてしまう。和は冪等でないので、重なった 2 区間では求まらない。

$k = \lfloor \log_2 L \rfloor$ は、整数のまま求める。次の 3 つのどれでもよい。

- 前計算の表：$\mathrm{lg}[1] = 0$、$\mathrm{lg}[L] = \mathrm{lg}[\lfloor L / 2 \rfloor] + 1$（$L \ge 2$）を $O(N)$ で作る
- C++20 の `std::bit_width`（`<bit>`）：`bit_width((unsigned)L) - 1`
- GCC の組み込み関数：`__lg(L)`

## 作り方（長さが 2 のべきの区間の表と log の表） {#build}

自分でライブラリを書くときの約束を、保つ性質・各操作の手順・境界に分けて示す。

### 保つ性質

- $\mathrm{st}[k][i]$：区間 $[i, i + 2^k)$ の結果。$k = 0, 1, \dots, \lfloor \log_2 N \rfloor$ で、$i$ は $i + 2^k \le N$ を満たす範囲だけ持つ
- $\mathrm{st}[0][i] = a_i$
- $\mathrm{lg}[L] = \lfloor \log_2 L \rfloor$（$1 \le L \le N$）

### 各操作の手順

長さ $2^k$ の区間 $[i, i + 2^k)$ は、長さ $2^{k-1}$ の 2 つの区間 $[i, i + 2^{k-1})$ と $[i + 2^{k-1}, i + 2^k)$ にちょうど分かれる。よって段 $k$ は段 $k - 1$ から作れる。重なりのない分け方なので、作るときには冪等は要らない。

```text
build(a):                          # N = |a|
    lg[1] ← 0; L = 2..N について lg[L] ← lg[L / 2] + 1
    st[0][i] ← a[i]
    k = 1, 2, …, lg[N] について:
        i + 2^k ≤ N のすべての i について:
            st[k][i] ← op(st[k-1][i], st[k-1][i + 2^(k-1)])

prod(l, r):                        # 0 ≤ l < r ≤ N
    k ← lg[r - l]
    return op(st[k][l], st[k][r - 2^k])
```

ACL には Sparse Table がないので自作する。取得の関数の名前と引数は、ACL の `segtree` の `prod(l, r)`（0-indexed・半開区間）にそろえた。ただし ACL の `prod` と違い、空の区間（$l = r$）は渡せない（この節の境界の項）。名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。

C++ では次のように書く。演算を関数で渡し、min と gcd の表を同じ形で作れるようにした。

```cpp
--8<-- "sparse-table/sparse-table.cpp:core"
```

**計算量**：段は $\lfloor \log_2 N \rfloor + 1$ 個で、各段は $N$ 個以下の値を $O(1)$ ずつで作る。よって前処理は時間・メモリとも $O(N \log N)$ である。取得は表を 2 か所読んで 1 回結ぶだけなので $O(1)$ になる。演算そのものに時間がかかるときは、その分を掛ける。gcd は 1 回 $O(\log \max a)$ なので、取得も $O(\log \max a)$ になる。

### 境界

- **空の区間**：$l = r$ では $\mathrm{lg}[0]$ が定まらない。表は単位元を使わないので、空の区間に返す値は呼び出す側で決める（min なら $+\infty$ など）
- **右の区間の始点**：$r - 2^k$ である。閉区間 $[L, R]$ で考えると $R - 2^k + 1$ になり、1 ずれやすい。問題文の閉区間（1-indexed）$[L, R]$ は、半開区間 $[L - 1, R)$ に直してから渡す
- **段の数**：$\lfloor \log_2 N \rfloor + 1$ 段である。$N = 1$ なら段 0 だけになる。$N$ が 2 のべきでなくても、表の外を読むことはない（$r - 2^k \ge l \ge 0$、$l + 2^k \le r \le N$）
- **表の向き**：$\mathrm{st}[k][i]$ の順（段が外側）に持つ。作るときの内側のループが $i$ を順に進むので、メモリを連続して読める

## 落とし穴 {#pitfalls}

- **和や XOR に使う**：重なりを 2 回数えるので答えが合わない。冪等でない演算は、引き算できるなら累積和、できないなら[冪等でない演算](#disjoint-sparse-table)の方法にする
- **log を浮動小数点で求める**：`(int)log2(L)` は浮動小数点の丸めを通る。整数の表か `bit_width` を使えば、誤差を考えなくてよい
- **メモリの見積もり**：$N = 5 \times 10^5$ で `long long` の表を持つと、19 段でおよそ $9 \times 10^6$ 個、約 72 MB になる。`int` で足りる値なら `int` にする。[セグメント木](../ds/segment-tree.md)のメモリは $O(N)$ なので、メモリが厳しい問題ではそちらにする
- **更新がある**：1 か所の値が変わると、その位置を含む区間がすべての段で変わる。作り直しは $O(N \log N)$ なので、更新が来る問題ではセグメント木を使う
- **組の比較**：最大値の位置を求めるとき、同じ値が複数あると、どの位置が返るかは比較の決め方で変わる。「最も左」が欲しければ、値が等しいときは添字の小さい方を返す比較にする

## 冪等でない演算（2 べきに分けて O(log N)、Disjoint Sparse Table） {#disjoint-sparse-table}

この節は、ここまでの表の作り方と、[分割統治](../basics/divide-and-conquer.md#range-knapsack)の「中点をまたぐ区間を中点からの累積で扱う」考え方を前提にする。

和・積・XOR・行列の積のように冪等でない演算でも、同じ表で $O(\log N)$ なら求まる。区間の長さ $L$ を 2 進数で表し、左端から上位の bit の長さ $2^k$ の順に跳ぶ。跳んだ区間は互いに重ならないので、冪等は要らず、結合法則だけで足りる。左から順に結べば、交換法則も要らない。これは[ダブリング](../basics/doubling.md)の $K$ 回の移動と同じ手順である。

取得を $O(1)$ にしたいときは、Disjoint Sparse Table を使う。結合法則を満たす演算なら何でも載せられ、前処理は $O(N \log N)$ である。

### Disjoint Sparse Table の表

段 $h = 1, 2, \dots$ ごとに、列を長さ $2^h$ の塊に区切る。各塊の中点 $m$（塊の先頭 $+ 2^{h-1}$）について、次の累積を持つ。

- 塊の左半分の $i$ では、$t[h][i] = a_i \cdot a_{i+1} \cdot \dots \cdot a_{m-1}$（$i$ から中点の手前まで）
- 塊の右半分の $i$ では、$t[h][i] = a_m \cdot a_{m+1} \cdot \dots \cdot a_i$（中点から $i$ まで）

閉区間 $[l, r]$（$l < r$）を問われたら、$l$ と $r$ の 2 進表記が異なる最上位の bit を見る。その bit を最下位を 0 番目として $h - 1$ 番目（すなわち $h$ = `bit_width(l ^ r)`）とすると、それより上の bit は等しいので、$l$ と $r$ は段 $h$ の同じ塊に入る。その bit は $l$ で 0、$r$ で 1 なので、$l$ は塊の左半分、$r$ は右半分に入る。よって答えは $t[h][l] \cdot t[h][r]$ の 1 回の演算で求まる。2 つの部分は中点で分かれていて重ならない。

$N = 8$ で $l = 1$、$r = 6$ なら、$1 = 001_{(2)}$、$6 = 110_{(2)}$ で、$l \oplus r = 111_{(2)}$ なので $h = 3$ になる。塊は $[0, 8)$、中点は 4 で、$t[3][1] = a_1 \cdot a_2 \cdot a_3$ と $t[3][6] = a_4 \cdot a_5 \cdot a_6$ を結ぶ。$l = 4$、$r = 5$ なら $l \oplus r = 1$ で $h = 1$、塊は $[4, 6)$ で、$t[1][4] = a_4$ と $t[1][5] = a_5$ を結ぶ。$l = r$ のときは $a_l$ をそのまま返す。

各段で各位置の値を 1 回ずつ作るので、前処理は $O(N \log N)$、取得は $O(1)$ である。半開区間 $[l, r)$ で受け取るなら、$r - 1$ を閉区間の右端にする。区間の和で確かめた実装を次に示す。コードは半開区間 $[l, r)$ で受け取り、`e` は空の区間（$l = r$）に返す値にだけ使う。空の区間を聞かないなら単位元は要らない。

```cpp
--8<-- "sparse-table/disjoint.cpp:core"
```

和なら累積和で足りるので、Disjoint Sparse Table が役に立つのは、引き算できない演算を変わらない列の上で何度も聞かれるときである。素数でない法での区間の積や、行列・一次関数の合成などが当たる。クエリを先にすべて読めるなら、分割統治で中点をまたぐクエリをまとめて処理する方法もある。

## 例題 {#examples}

### ABC282 F. Union of Two Sets {#abc282_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC282 F. Union of Two Sets](https://atcoder.jp/contests/abc282/tasks/abc282_f)（diff 1734）：区間の集合を自分で用意し、質問された区間を用意した 2 つの区間の和集合で表す（対話問題）。

</div>

区間の集合を自分で出力しておき、後から来る区間を、出力した区間 2 つの和集合でちょうど表す[対話](../misc/interactive.md)の問題である。Sparse Table が持つ区間、すなわち各始点 $l$ から始まる長さ $2^k$ の区間をすべて出力すればよい。問われた区間は、[なぜ重なってよいか](#idempotent)と同じく、左端から伸ばした区間と右端から伸ばした区間の 2 つで覆える。和集合は同じ要素を 2 回含んでも変わらないので、重なりは問題にならない。

??? note "解法の詳細"
    $N \le 4000$、出力できる区間は $50000$ 個まで、問いは $10^5$ 個までである。1-indexed の閉区間で、$0 \le k \le 11$ と $1 \le l \le N - 2^k + 1$ のすべての組について区間 $[l, l + 2^k - 1]$ を出力し、組 $(k, l)$ に通し番号を付けておく。$2^{11} = 2048 \le 4000 < 2^{12}$ なので段は 12 個である。区間の数は $\sum_{k=0}^{11} (N - 2^k + 1) = 12 \cdot 4001 - (2^{12} - 1) = 43917$ 個で、上限に収まる。

    問い $[L, R]$ が来たら、$k = \lfloor \log_2 (R - L + 1) \rfloor$ をとり、組 $(k, L)$ と $(k, R - 2^k + 1)$ の番号を答える。前計算は $O(N \log N)$、1 問 $O(1)$ である。出力のたびに flush する（[対話の作法](../misc/interactive.md#format)）。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC125 C. GCD on Blackboard](https://atcoder.jp/contests/abc125/tasks/abc125_c)（diff 1197）：N 個の整数のうち 1 つを好きな整数に書き換えたとき、全体の最大公約数としてありうる最大値を求める。
- [ABC254 F. Rectangle GCD](https://atcoder.jp/contests/abc254/tasks/abc254_f)（diff 1764）：(i, j) 成分が A_i + B_j の N×N の表について、指定された長方形の中の値すべての最大公約数を、多数のクエリに答える。

</div>

??? note "練習の方針"
    - **ABC125 C**：書き換える要素 $i$ を全探索すると、答えは $i$ を除いた gcd である。それは区間 $[0, i)$ と $[i+1, N)$ の 2 つの区間 gcd の gcd なので、Sparse Table で各 $i$ を $O(1)$ 回の gcd で求める。左右からの累積 gcd の方が簡単で、実装の確かめとして解く
    - **ABC254 F**：gcd は隣り合う項の差に置き換えても変わらないので、長方形の gcd は左上の値と、$A$・$B$ の隣接差の区間 gcd 2 つとの gcd になる。差の列は変わらないので、Sparse Table で区間 gcd を引く（gcd は冪等なので普通の Sparse Table でよい）

## 確認問題 {#quiz}

??? question "確認問題：区間の和に、重なった 2 つの区間を使えないのはなぜか"
    重なりの要素を 2 回足してしまうからである。たとえば $a = (1, 2, 3)$ の $[0, 3)$ は、$k = 1$ で $[0, 2)$ と $[1, 3)$ を使う。和は $3 + 5 = 8$ になり、正しい値 $6$ より重なりの $a_1 = 2$ の分だけ大きい。min なら $\min(1, 2) = 1$ で、重なりがあっても正しい。

??? question "確認問題：N = 10^6 のとき、表の段はいくつ要るか"
    $2^{19} = 524288 \le 10^6 < 2^{20} = 1048576$ なので $\lfloor \log_2 10^6 \rfloor = 19$ で、段 $0$ から $19$ までの 20 段である。

??? question "確認問題：区間の最小値の位置（複数あれば最も左）を O(1) で答えるには、何を表に持てばよいか"
    値と添字の組 $(a_i, i)$ を持ち、辞書順の小さい方を返す演算で結ぶ。値が小さい方を選び、値が等しければ添字の小さい方を選ぶ。この演算は結合法則を満たし、同じ組を 2 回結んでも同じ組が返るので冪等である。よって重なった 2 区間で引ける。

??? question "確認問題：Disjoint Sparse Table で、N = 8 の閉区間 [2, 5] はどの段の何を結ぶか"
    $2 = 010_{(2)}$、$5 = 101_{(2)}$ で、$2 \oplus 5 = 111_{(2)}$ なので段 $h = 3$ である。塊は $[0, 8)$、中点は 4 で、$t[3][2] = a_2 \cdot a_3$ と $t[3][5] = a_4 \cdot a_5$ を結ぶ。

## 使い分け {#comparison}

| 状況 | 使う手法 |
| --- | --- |
| 更新がなく、区間の和（引き算できる演算） | [累積和](../basics/prefix-sum.md) |
| 更新がなく、区間の min・max・gcd を非常に多く聞く | Sparse Table（取得 $O(1)$） |
| 一点の更新がある | [セグメント木](../ds/segment-tree.md)（取得 $O(\log N)$） |
| 左右の端がどちらも単調に動く（尺取り・幅が一定の窓） | [スライド最小値](../ds/monotonic-stack.md)（全体 $O(N)$） |
| 更新がなく、引き算できない演算で $O(1)$ が欲しい | [Disjoint Sparse Table](#disjoint-sparse-table) |
| 区間の AND・OR | Sparse Table か、[bit ごとの 1 の個数の累積和](../basics/bitwise-independence.md) |

## 参考 {#references}

- [drken「AtCoder ABC 282 F - Union of Two Sets (2D, 青色, 600 点)」](https://drken1215.hatenablog.com/entry/2022/12/29/112939)：例題 abc282_f の制約と、長さが倍々に伸びる区間を全始点に用意する方針（記事は長さ $2^k - 1$ の区間を用い、2 のべきでもよいと述べる）
- [Kazun「AtCoder Beginner Contest 254 F問題 Rectangle GCD」](https://kazun-kyopro.hatenablog.com/entry/ABC/254/F)：隣り合う項の差の gcd に直して区間 gcd にする型と、Disjoint Sparse Table での取得
- [cp-algorithms「Sparse Table」](https://cp-algorithms.com/data_structures/sparse-table.html)：冪等な演算に限って取得が $O(1)$ になること・表を段が外側の順に持つとメモリを連続して読めること・Disjoint Sparse Table の存在（文章と図は使っていない）
- [Library Checker「Static RMQ」](https://judge.yosupo.jp/problem/staticrmq)：区間最小の検証用の問題
- [cppreference「std::bit_width」](https://en.cppreference.com/cpp/numeric/bit_width)：`bit_width` が C++20 の `<bit>` にあること
- [hamayan「GCD on Blackboard [AtCoder Beginner Contest 125 C]」](https://blog.hamayanhamayan.com/entry/2019/04/28/085936)：練習 ABC125 C の Sparse Table による区間 gcd と累積 gcd
