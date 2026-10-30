---
id: z-algorithm
title: Z-algorithm
aliases: [Z 法, Z 配列, Z function, 拡張 KMP, z_algorithm, 各位置からの最長共通接頭辞, 巡回シフト, A+A の技, Z アルゴリズム]
type: technique
field: string
chapter: 線形時間の照合と回文
order: 60
level: 水
kind: [文字列]
prerequisites: [string-basics]
related: [kmp, rolling-hash, suffix-array, palindrome#manacher, dp-sequence-partition, bit-dp, method-comparison#strings]
summary: Z 配列 z[i]（S と S[i:] の最長共通接頭辞の長さ）を O(N) で求める。P＋区切り＋T の Z 配列でパターンの全出現を決定的に見つけられ、回転の検索や周期の判定にも使える。
complexity: O(N)（N は文字列の長さ。P＋区切り＋T なら O(|P| + |T|)）
signs:
  - {type: phrase, text: 各位置から、文字列の先頭と何文字一致するか}
  - {type: phrase, text: A を何回回転すると B になるか（円環状の文字列の一致）}
  - {type: phrase, text: T を S の接頭辞の連結で表す最小の個数}
  - {type: phrase, text: パターンの全出現位置}
  - {type: constraint, text: '|S|, |T| ≤ 10^6 で、ずらし方ごとに比べる O(|S||T|) が間に合わない'}
acl: [z_algorithm]
verify: [zalgorithm]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: Z 配列の定義と、P＋区切り＋T によるパターン検索, anchor: pattern-search}
  - {title: なぜ O(N) か：Z-box の内側は値をコピーでき、比較のたびに右端が進む, anchor: linear-time}
  - {title: ACL の z_algorithm（先頭の値が n になる流儀・区切りの −1）, anchor: acl}
  - {title: 巡回シフト：A+A の中で B を探す（回転 N 回を二重に数えない）, anchor: cyclic-shift}
  - {title: 周期の判定：p が周期であることと Z 配列の値の関係, anchor: period}
  - {title: 反転と連結する：後ろからの一致と回文の接尾辞, anchor: reverse}
  - {title: S＋区切り＋T で各位置から S の接頭辞が何文字続くか（DP の材料）, anchor: prefix-extension, level: 黄}
stage: done
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：文字列 $S$ の各位置 $i$ について、$S$ と $S[i, N)$ の最長共通接頭辞の長さ $z[i]$ を、すべての $i$ についてまとめて $O(N)$ で求める。パターン $P$・区切り・本文 $T$ をつないだ列の Z 配列を使えば、$P$ の全出現を決定的に（衝突の心配なく）見つけられる。回転の検索や周期の判定にも使える。
    - **いつ使うか**：
        - 各位置から、文字列の先頭と何文字一致するか
        - A を何回回転すると B になるか（円環状の文字列の一致）
        - T を S の接頭辞の連結で表す最小の個数
        - パターンの全出現位置
        - $\lvert S \rvert, \lvert T \rvert \le 10^6$ で、ずらし方ごとに比べる $O(\lvert S \rvert \lvert T \rvert)$ が間に合わない
    - **計算量**：長さ $N$ の列に対して $O(N)$（ならしではなく 1 回の呼び出し全体の上限）。$P$＋区切り＋$T$ なら $O(\lvert P \rvert + \lvert T \rvert)$
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)

<!-- textlint-disable -->
別名：Z 法・Z 配列・Z function・拡張 KMP・z_algorithm・各位置からの最長共通接頭辞・巡回シフト・A+A の技・Z アルゴリズム
<!-- textlint-enable -->

Z-algorithm は、文字列の各位置から「先頭と何文字一致するか」を、すでに分かった一致を使い回して線形時間で求める手法である。ACL に `z_algorithm` があるので、パターン検索・回転の一致・周期の判定の多くは、うまくつないだ列の Z 配列を 1 回作るだけで済む。

## Z 配列の定義と、P＋区切り＋T によるパターン検索 {#pattern-search}

長さ $N$ の文字列 $S$（0-indexed）の Z 配列は、$z[i]$ ＝「$S$ と $S[i, N)$ の[最長共通接頭辞](../guide/glossary.md#lcp)の長さ」で決まる長さ $N$ の配列である。$z[0]$ は $S$ 自身との比較なので $N$ になる（ACL の流儀。[ACL の節](#acl)）。

たとえば $S = \texttt{aabxaab}$ の Z 配列は $(7, 1, 0, 0, 3, 1, 0)$ である。$z[4] = 3$ は、$S[4, 7) = \texttt{aab}$ が先頭の $\texttt{aab}$ と一致し、文字列の終わりで止まることを表す。$z[1] = 1$ は、$S[1, 7) = \texttt{abxaab}$ と $S$ が最初の $\texttt{a}$ だけ一致し、次の文字（$\texttt{b}$ と $\texttt{a}$）で食い違うことを表す。

**パターン検索**。長さ $m$ のパターン $P$ が長さ $n$ の本文 $T$ のどこに現れるかを、ずらし方ごとに比べると $O(nm)$ かかる。$n, m$ が $10^5$ を超えると間に合わない。そこで $P$ と $T$ の間に、どちらにも現れない区切り $\#$ を挟んだ列 $V = P + \# + T$ の Z 配列を作る。$T$ の位置 $j$ は $V$ の位置 $m + 1 + j$ にあたり、次が成り立つ。

$$
z[m + 1 + j] = m \iff T[j, j + m) = P
$$

区切りは $V$ に 1 回しか現れないので、$V$ の接頭辞との一致は区切りの位置（$V[m]$）に届いたところで必ず止まる。だから $T$ 側の位置の $z$ は $m$ を超えず、ちょうど $m$ になるのは $P$ 全体と一致したときだけである。全体の計算量は $O(n + m)$ で、[ローリングハッシュ](../string/rolling-hash.md)と違って衝突による誤判定がない。

```cpp
--8<-- "z-algorithm/find-all.cpp:core"
```

完全なプログラム：[`find-all.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/z-algorithm/find-all.cpp)（GitHub）
{ .kp-code-src }

## なぜ O(N) か：Z-box の内側は値をコピーでき、比較のたびに右端が進む {#linear-time}

$z[i]$ を位置ごとに先頭から比べ直すと、$S = \texttt{aa}\dots\texttt{a}$ のような入力で合計 $O(N^2)$ になる。Z-algorithm は、すでに見つけた一致区間を使って比較を省く。

$1 \le i' < i$ の位置のうち、一致区間 $[i', i' + z[i'])$ の右端が最も右にあるものを $[l, r)$ とし、Z-box と呼ぶ（そのような区間がまだなければ $l = r = 0$ とする）。$i' = 0$ を含めないのは、$z[0] = N$ とすると箱がいつも $[0, N)$ になってしまうからである。Z-box は $S[l, r) = S[0, r - l)$ を満たす。よって $l \le i < r$ なら、$S[i, r)$ は接頭辞の側の $S[i - l, r - l)$ と同じ文字列である。その位置の値 $z[i - l]$ はもう分かっている。$z[i]$ は次の 3 通りで決まる。

1. **$i \ge r$**：使える情報がないので、$S[0]$ と $S[i]$ から 1 文字ずつ比べる
2. **$i < r$ かつ $z[i - l] < r - i$**：$z[i] = z[i - l]$ がそのまま答えになり、比べなくてよい
3. **$i < r$ かつ $z[i - l] \ge r - i$**：少なくとも $r - i$ 文字は一致すると分かる。箱の外の $S[r]$ と $S[r - i]$ から比べ始める

2 が正しいのは、食い違いが箱の内側で起きるからである。$k = z[i - l]$ とすると $S[i - l + k] \ne S[k]$ で、$i - l + k < r - l$ なので、箱の中の対応する位置の文字 $S[i + k]$ も $S[i - l + k]$ と同じである。よって $S[i + k] \ne S[k]$ となり、$z[i]$ はちょうど $k$ になる。3 では、箱の外の文字は接頭辞の側と同じとは限らないので、そこから先は比べるしかない。

![S = aabaabaac で Z-box は \[3, 8)。i = 4 では対応する位置 1 の z[1] = 1 が r − i = 4 より小さいので z[4] = 1 を写す。i = 6 では z[3] = 5 が r − i = 2 以上なので、箱の外の S[8] と S[2] から比べて z[6] = 2 になる](../img/z-algorithm/z-box.svg)

次の図は、同じ処理を $i = 1$ から 1 位置ずつ送って見せる。上の段が $S$ で、上の括弧が Z-box、中の段は $S$ の先頭を位置 $i$ にそろえて並べたもの、下の段が決まった $z$ である。箱の内側から写した部分は破線のマス、実際に比べたマスは一致なら塗り、食い違いなら斜線で示し、写すときは対応する位置 $i - l$ から $i$ へ矢印を引く。比べずに写す場合（2）は、箱の内側の対応から分かる食い違いの位置を点線の枠と「≠」で示す。箱を取り替えるステップでは、新しい Z-box を一番上に破線の括弧で描く。

<div class="kp-viz" data-viz="z-algorithm" data-config='{"s": "aabaabaac"}'></div>

成功した比較は全体で $N$ 回を超えない。理由は次のとおりである。

- 2 の場合は比較をしない（実装では最初の 1 回が必ず失敗する）
- 1 と 3 の場合、成功する比較が読む位置は、それまでの $r$ 以上である。$z[i]$ が決まると右端は $r = i + z[i]$ に進むので、成功した比較 1 回につき $r$ は少なくとも 1 進む
- $r$ は減らず $N$ を超えないので、成功した比較は合計 $N$ 回以下。失敗した比較は各位置で高々 1 回

よって全体は $O(N)$ である。各位置での手間は一定ではないが、合計に上限があるので 1 回の呼び出しで $O(N)$ が保証される。自分で書くと次のようになる（ACL と同じく $z[0] = N$ にする）。

```cpp
--8<-- "z-algorithm/own-z.cpp:core"
```

完全なプログラム：[`own-z.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/z-algorithm/own-z.cpp)（GitHub）
{ .kp-code-src }

??? question "確認問題：r − i で頭打ちにする理由"
    $i < r$ のとき、初期値を `min(r - i, z[i - l])` にしている。`min` を取らずに `z[i - l]` から比べ始めると何が起きるか。

    ??? success "答え"
        $z[i - l] > r - i$ のとき、箱の外の文字まで一致すると決めつけることになり、$z[i]$ が大きすぎる値になりうる。箱の外は接頭辞の側と同じとは限らない。たとえば $S = \texttt{aabaabaac}$ の $i = 6$ では $z[3] = 5$ だが、本当の $z[6]$ は 2 である。

## ACL の z_algorithm（先頭の値が n になる流儀・区切りの −1） {#acl}

ACL の `z_algorithm` は文字列と整数の列の両方に使える。区切りを挟むときは `vector<int>` にしておくと安全である。

!!! info "ACL では"
    `vector<int> z = atcoder::z_algorithm(s);`（`s` は `string`、または `vector<T>` で `T` は `int`・`unsigned int`・`long long`・`unsigned long long`）。長さ $N$ の配列を返し、$z[i]$ は `s` と `s[i, N)` の LCP の長さ。$O(N)$、$0 \le N \le 10^8$。

**$z[0] = N$ の流儀**。ACL は $z[0]$ に $N$ を入れる。解説によっては $z[0] = 0$ とする書き方もあるので、ほかのコードと混ぜるときは境界に注意する。周期を探すループを $p = 1$ から始める、検索では区切りより後ろの位置だけを見る、のように $z[0]$ を読まない書き方にしておけば、どちらの流儀でも同じ結果になる。

**区切りは −1 にする**。`string` のまま `p + "#" + t` とつなぐと、入力に `#` が含まれうる問題では誤る。文字を `int` に直した `vector<int>` を作り、区切りを $-1$ にすれば、ASCII の文字（0〜127）とは必ず違う。整数の列を検索するときも同じで、値が 0 以上なら $-1$、負の値もありうるなら値の範囲の外の数を区切りにする。ACL の `string` 版も内部で `vector<int>` に写してから計算するので、自分で `vector<int>` を作っても遅くならない。

## 巡回シフト：A+A の中で B を探す（回転 N 回を二重に数えない） {#cyclic-shift}

長さ $N$ の文字列 $A$ を $k$ 回転したもの（先頭の文字を末尾へ移す操作を $k$ 回）は $A[k, N) + A[0, k)$ で、これは $A + A$ の長さ $N$ の窓 $(A + A)[k, k + N)$ と同じである（[文字列の基本操作の回転の節](../string/string-basics.md#rotation)）。よって「$A$ を何回回転すると $B$ になるか」は、$A + A$ の中での $B$ の出現位置を探す問題になる。

$V = B + \# + A + A$ の Z 配列を作り、$k = 0, 1, \dots, N - 1$ の順に $z[N + 1 + k] = N$ となる最初の $k$ を答える。どの $k$ でも成り立たなければ、$B$ は $A$ の回転ではない。

```cpp
--8<-- "z-algorithm/rotation.cpp:core"
```

完全なプログラム：[`rotation.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/z-algorithm/rotation.cpp)（GitHub）
{ .kp-code-src }

$A + A$ の位置 $N$ から始まる窓は $A$ 自身で、0 回転と同じである。「$B$ に一致する回転は何通りか」を数えるときに $k = N$ まで見ると、0 回転を二重に数える。見る範囲を $0 \le k < N$ に限るか、$A + A$ の最後の 1 文字を落とした長さ $2N - 1$ の列を使う。

回転どうしの辞書順の比較は、Z 配列ではなく [Suffix Array の回転の節](../string/suffix-array.md#rotations)の方法を使う。

## 周期の判定：p が周期であることと Z 配列の値の関係 {#period}

$1 \le p \le N$ について、すべての $0 \le i < N - p$ で $S[i] = S[i + p]$ が成り立つとき、$p$ を $S$ の[周期](../guide/glossary.md#period)という。この条件は「$S[p, N)$ と $S[0, N - p)$ が等しい」と同じなので、$p < N$ なら次が成り立つ。

$$
p \text{ が周期} \iff z[p] = N - p
$$

$p = N$ はいつでも周期である。Z 配列を 1 回作れば、すべての $p$ を $O(N)$ でまとめて判定でき、最小の周期は条件を満たす最小の $p$ になる。$z[p] = N - p$ は「長さ $N - p$ の接尾辞が接頭辞と一致する」ことでもあり、この一致する部分を [border](../guide/glossary.md#border) と呼ぶ。border を長い順にたどる使い方は [KMP 法](../string/kmp.md)で扱う。

```cpp
--8<-- "z-algorithm/period.cpp:core"
```

完全なプログラム：[`period.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/z-algorithm/period.cpp)（GitHub）
{ .kp-code-src }

周期と「繰り返し」は違う。$S = \texttt{abcab}$ は周期 3 を持つが、長さ 3 の文字列の繰り返しではない。$S$ が長さ $p$ の文字列の繰り返しであるのは、$p$ が周期で、かつ $p \mid N$ のときである。さらに、最小の周期 $p_0$ が $N$ を割り切らなければ、$S$ は $N$ より短いどの文字列の繰り返しでもない。

??? note "証明：最小の周期が N を割り切らなければ、繰り返しにならない"
    $S$ が長さ $q$（$q < N$、$q \mid N$）の文字列の繰り返しだとすると、$q$ は周期で $q \le N / 2$ である。最小の周期 $p_0$ は $p_0 \le q$ を満たすので $p_0 + q \le N$ になる。ここで「周期 $a < b$ が $a + b \le N$ を満たせば $b - a$ も周期である」ことが使える（$i + b < N$ なら $S[i] = S[i + b] = S[i + b - a]$、そうでなければ $i \ge N - b \ge a$ なので $S[i] = S[i - a] = S[i + b - a]$）。$a = p_0$、$b = q$ から始めて、互除法と同じように大きい方を差に置き換えていく（和は減るので条件は保たれる）と、$\gcd(p_0, q)$ も周期になる（Fine-Wilf の定理の弱い形）。よって $p_0$ の最小性から $\gcd(p_0, q) = p_0$、すなわち $p_0 \mid q$ となり、$p_0 \mid N$ が従う。対偶を取れば主張が得られる。

## 反転と連結する：後ろからの一致と回文の接尾辞 {#reverse}

Z 配列は「先頭との一致」しか測らないが、$S$ を反転した $R$（$R[k] = S[N - 1 - k]$）と組み合わせると、後ろからの一致や回文も測れる。

**後ろからの一致**。$R$ の Z 配列 $z_R$ について、$1 \le i \le N$ について、$z_R[N - i]$ は「$S[0, i)$ と $S$ の最長共通接尾辞の長さ」になる（$i = 0$ なら左側は空で、長さは 0 とする）。$R[N - i, N)$ は $S[0, i)$ を反転したものだからである。$S$ の Z 配列 $z_S$ と合わせると、区切り位置 $i$ ごとに次の 2 つが $O(1)$ で分かる。

- 右側 $S[i, N)$ の先頭が、$S$ の接頭辞と何文字一致するか：$z_S[i]$
- 左側 $S[0, i)$ の末尾が、$S$ の接尾辞と何文字一致するか：$z_R[N - i]$

文字列を決まった形のいくつかの部分に分けて数える問題で、両端の一致の長さを調べるのに使う。

**回文の接尾辞**。$V = R + \# + S$ の Z 配列で、$S$ の位置 $j$（$V$ の位置 $N + 1 + j$）の値は $R$ と $S[j, N)$ の LCP である。

$$
z[N + 1 + j] = N - j \iff S[j, N) \text{ は回文}
$$

左辺は $S[j, N) = R[0, N - j)$ を意味する。$R[0, N - j)$ は $S[j, N)$ を反転したものなので、これは $S[j, N)$ が反転しても変わらないことと同じである。条件を満たす最小の $j$ が最長の回文の接尾辞を与える。回文の中心ごとの半径まで要るなら [回文のページ](../string/palindrome.md#manacher)の Manacher を使う。

## S＋区切り＋T で各位置から S の接頭辞が何文字続くか（DP の材料） {#prefix-extension}

この節は [区間分割 DP](../dp/dp-sequence-partition.md) を前提にする。$V = S + \# + T$ の Z 配列から、$T$ の各位置で次の値が読める。

$$
\mathrm{len}[j] = z[\lvert S \rvert + 1 + j] = T[j] \text{ から始めて } S \text{ の接頭辞が何文字続くか}
$$

接頭辞の接頭辞はまた接頭辞なので、$1 \le k \le \mathrm{len}[j]$ のどの $k$ でも $T[j, j + k)$ は $S$ の接頭辞である。この性質は「$T$ を $S$ の接頭辞（空でない）の連結に分ける」型の DP の遷移そのものになる。

- 状態：$\mathrm{dp}[j]$ ＝ $T[0, j)$ を $S$ の接頭辞の連結に分けるときの最小の個数（分けられなければ $\infty$）
- 遷移：$\mathrm{dp}[j + k] \leftarrow \mathrm{dp}[j] + 1$（$1 \le k \le \mathrm{len}[j]$）
- 初期値と答え：$\mathrm{dp}[0] = 0$、答えは $\mathrm{dp}[\lvert T \rvert]$

遷移を素直に配ると $O(\lvert T \rvert \lvert S \rvert)$ かかる。ここで、$\mathrm{dp}$ が $j$ について減らないことが使える。$T[0, x)$ を $c$ 個に分けた方法があるとする。$y < x$ なら、$y$ をまたぐピース $[a, b)$（$a < y \le b$）を $[a, y)$ に切り詰め、それより後ろのピースを捨てる。切り詰めたピースは空でない接頭辞のままなので、$T[0, y)$ も $c$ 個以下に分けられる。

よって個数 $c$ 以下で届く位置は区間 $[0, \mathrm{reach}_c]$ になる。次の式で区間を広げていけば、答えは $O(\lvert S \rvert + \lvert T \rvert)$ で求まる（幅優先探索の段を広げるのと同じ要領）。

$$
\mathrm{reach}_{c+1} = \max_{j \le \mathrm{reach}_c} (j + \mathrm{len}[j])
$$

```cpp
--8<-- "z-algorithm/prefix-concat.cpp:core"
```

完全なプログラム：[`prefix-concat.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/z-algorithm/prefix-concat.cpp)（GitHub）
{ .kp-code-src }

同じつなぎ方で、2 つの文字列の重なりも測れる。$V = b + \# + a$ の Z 配列を作る。$a$ の位置 $j$ の値が $\lvert a \rvert - j$ なら、$a$ の接尾辞 $a[j, \lvert a \rvert)$ は $b$ の接頭辞と一致する。そのような $j$ のうち $\lvert a \rvert - j$ の最大が、$a$ の後ろに $b$ を重ねてつなぐときの重なりである。また、値が $\lvert b \rvert$ 以上の位置があれば $b$ は $a$ に含まれる。複数の文字列をすべて含む最短の文字列は、この重なりを前計算して [bitDP](../dp/bit-dp.md) で並べ順を決める。

## 落とし穴 {#pitfalls}

**区切りが文字と重なる**。`p + "#" + t` は、入力に `#` が現れると区切りの役をしない。$z$ が区切りをまたいで伸び、$T$ 側の値が $\lvert P \rvert$ を超えたり、誤った一致を報告したりする。`vector<int>` にして区切りを $-1$ にする（[ACL の節](#acl)）。

**区切りを入れ忘れる**。$P + T$ とそのままつなぐと、$T$ 側の $z$ が $T$ の中まで伸びる。検索だけなら $z \ge \lvert P \rvert$ で判定すれば正しく動くが、区切りがある前提で $z = \lvert P \rvert$ と判定すると出現を取りこぼす。$\mathrm{len}[j]$ や重なりの長さは $\lvert S \rvert$ を超えた誤った値になる。

**$z[0]$ の流儀の違い**。ACL は $z[0] = N$、ほかの解説のコードは $z[0] = 0$ のことがある。最大値を取るループに $i = 0$ を含めると、流儀によって答えが変わる。

**回転を二重に数える**。$A + A$ の中で $B$ の出現を数えるとき、開始位置 $N$ は 0 回転と同じである（[巡回シフトの節](#cyclic-shift)）。

**接尾辞ごとに Z を作り直す**。開始位置 $i$ ごとに $S[i, N)$ の Z 配列を作ると、2 つの位置の LCP がすべて分かる代わりに $O(N^2)$ かかる。$N \le 5000$ なら間に合うが、$N = 2 \times 10^5$ では間に合わない。任意の 2 か所の LCP を多数問うなら、[Suffix Array](../string/suffix-array.md#lcp-rmq) かローリングハッシュを使う。

**連結した文字列を何度も作る**。`b + a + a` のような連結をループの中で毎回作ると、そのつど長さに比例する時間がかかる。つないだ列は 1 回だけ作り、添字の対応（$T$ の位置 $j$ は $\lvert P \rvert + 1 + j$）で読む。

## 例題 {#examples}

### ABC430 E. Shift String {#abc430_e}

<div class="kp-problems" data-role="example" markdown>

- [ABC430 E. Shift String](https://atcoder.jp/contests/abc430/tasks/abc430_e)（diff 1109）：A を何回回転すると B に一致するかを求める。

</div>

回転は $A + A$ の長さ $N$ の窓なので、$A + A$ の中で $B$ が最初に現れる位置が答えになる。$\lvert A \rvert$ が最大 $10^6$ で、ずらし方ごとに比べる $O(N^2)$ は間に合わない。$B + \# + A + A$ の Z 配列で線形時間に探す（[巡回シフトの節](#cyclic-shift)）。

??? note "解法の詳細"
    - $V = B + (-1) + A + A$ を `vector<int>` で作り、`z_algorithm` を呼ぶ。
    - $k = 0, 1, \dots, N - 1$ の順に $z[N + 1 + k] = N$ を調べ、最初に成り立つ $k$ を出力する。どれでも成り立たなければ $-1$ を出力する。
    - テストケースが複数あるが、長さの総和に上限があるので、ケースごとに $O(N)$ で全体も線形である。
    - コードは[巡回シフトの節](#cyclic-shift)のものと同じ形である。

### ABC284 F. ABCBAC {#abc284_f}

<div class="kp-problems" data-role="example" markdown>

- [ABC284 F. ABCBAC](https://atcoder.jp/contests/abc284/tasks/abc284_f)（diff 1575）：T が「S の先頭 i 文字＋S の反転＋S の残り」の形になる S と i を求める。

</div>

$S$ を $L = S[0, i)$ と $Q' = S[i, N)$ に分けると、$T = L + \mathrm{rev}(Q') + \mathrm{rev}(L) + Q'$ である。前半 $X = T[0, N)$ と、後半を反転した $Y = \mathrm{rev}(T[N, 2N))$ を作る。$Q = \mathrm{rev}(Q')$ とおくと、$X = L + Q$、$Y = Q + L$ になる。すなわち $Y$ は $X$ を $i$ 回転したものであり、回転の検索に帰着する。

??? note "解法の詳細"
    - $X = T[0, N)$、$Y = \mathrm{rev}(T[N, 2N))$ を作る。
    - $Y + (-1) + X + X$ の Z 配列を作り、$0 \le i \le N$ で $z[N + 1 + i] = N$ となる $i$ を探す。ここでは $i = 0$ と $i = N$ は別の答えとして扱ってよい（出力する $i$ が違う）。
    - 見つかれば $S = X[0, i) + \mathrm{rev}(X[i, N))$ と $i$ を出力し、なければ $-1$ を出力する。全体で $O(N)$。
    - $Y$ が $X$ の回転かを直接確かめる代わりに、区切り位置ごとに 2 か所の一致をローリングハッシュで $O(1)$ ずつ比べてもよい。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC398 F. ABCBA](https://atcoder.jp/contests/abc398/tasks/abc398_f)（diff 1033）：S の後ろに文字を足して作れる最短の回文を求める。
- [ABC141 E. Who Says a Pun?](https://atcoder.jp/contests/abc141/tasks/abc141_e)（diff 1459）：重ならずに 2 回以上現れる部分文字列の最大の長さを求める（N ≤ 5000）。

</div>

??? note "練習の方針"
    - **ABC398 F**：最長の回文の接尾辞 $S[j, N)$ を見つけ、その前の $S[0, j)$ を反転して後ろに足す。$\mathrm{rev}(S) + \# + S$ の Z 配列で、$z = N - j$ となる最小の $j$ を探す（[反転と連結する節](#reverse)）
    - **ABC141 E**：開始位置 $i$ ごとに $S[i, N)$ の Z 配列を作ると、$z[d]$ は位置 $i$ と $i + d$ から始まる一致の長さである。重ならないためには長さが $d$ 以下でなければならないので、$\min(z[d], d)$ の最大を取る。全体で $O(N^2)$

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [ABC257 G. Prefix Concatenation](https://atcoder.jp/contests/abc257/tasks/abc257_g)（diff 2078）：T を S の接頭辞の連結に分けるときの最小の個数を求める。
- [ABC343 G. Compress Strings](https://atcoder.jp/contests/abc343/tasks/abc343_g)（diff 2114）：N 個（≤ 20）の文字列をすべて連続部分文字列として含む文字列の長さの最小を求める。
- [ARC055 C. ABCAC](https://atcoder.jp/contests/arc055/tasks/arc055_c)（diff 2392・参考値）：S を A+B+C+A+C の形に分ける方法の数を求める。

</div>

??? note "力試しの方針"
    - **ABC257 G**：$S + \# + T$ の Z 配列で $\mathrm{len}[j]$ を求め、届く範囲を段ごとに広げる（[接頭辞の伸びの節](#prefix-extension)）
    - **ABC343 G**：ほかの文字列に含まれる文字列を先に除き、順序付きの組ごとに重なりの長さを Z で求める。最後に置いた文字列を状態に持つ bitDP で、並べ順を決める
    - **ARC055 C**：$\lvert ABC \rvert = i$ を全探索する（$\lvert B \rvert = 2i - N \ge 1$）。右側 $S[i, N) = A + C$ について、$A$ は $S$ の接頭辞なので $\lvert A \rvert \le z_S[i]$、$C$ は $S[0, i)$ の接尾辞でもあるので $\lvert C \rvert \le z_R[N - i]$ になる。$A$・$C$ が空でないことと合わせて、$\lvert A \rvert$ の取りうる範囲の長さを足す（[反転と連結する節](#reverse)）

## 確認問題 {#quiz}

??? question "確認問題：Z 配列を書く"
    $S = \texttt{abaab}$ の Z 配列を（ACL の流儀で）書け。

    ??? success "答え"
        $(5, 0, 1, 2, 0)$。$z[2]$ は $\texttt{aab}$ と $\texttt{abaab}$ が 1 文字だけ一致する。$z[3]$ は $\texttt{ab}$ が先頭の $\texttt{ab}$ と一致して文字列の終わりで止まる。

??? question "確認問題：周期の判定"
    $S = \texttt{abcabca}$（$N = 7$）の最小の周期はいくつか。$S$ は長さ 7 より短い文字列の繰り返しか。

    ??? success "答え"
        $z[3] = 4 = 7 - 3$ なので最小の周期は 3 である（$z[1] = z[2] = 0$）。3 は 7 を割り切らないので、$S$ は長さ 7 より短いどの文字列の繰り返しでもない。

??? question "確認問題：区切りの役目"
    $P = \texttt{aa}$、$T = \texttt{aaa}$ を区切りなしで $\texttt{aaaaa}$ とつないで Z 配列を作った。$T$ の位置 0 にあたる値はいくつか。区切りを入れるとどうなるか。

    ??? success "答え"
        区切りなしでは位置 2 の値で、$z[2] = 3$ になり $\lvert P \rvert = 2$ を超える。$T$ の中まで一致が伸びたためである。$\texttt{aa\#aaa}$ にすると位置 3 の値は 2 になり、ちょうど $\lvert P \rvert$ で止まる。

## 使い分け {#comparison}

| 手法 | 1 回で分かること | 向いている場面 |
| --- | --- | --- |
| Z-algorithm | 各位置から先頭と何文字一致するか | ACL にあり決定的。区切りでつないで検索・周期・接頭辞の伸び |
| [KMP 法](../string/kmp.md) | 各位置で終わる最長の border | 文字が 1 つずつ来る照合、border の連鎖、照合のオートマトン |
| [ローリングハッシュ](../string/rolling-hash.md) | 任意の 2 つの部分文字列が等しいか | 任意の 2 か所の比較、二分探索と組み合わせた LCP。衝突は確率で抑える |
| [Suffix Array](../string/suffix-array.md) | すべての接尾辞の辞書順 | 辞書順・異なる部分文字列の数・任意の 2 接尾辞の LCP |

パターン検索・回転の一致・周期の判定なら、まず Z で考えるとよい。ACL にあるので実装の誤りが入りにくく、ハッシュのような衝突もない。比べたい 2 か所が先頭に固定されていない問題では、ハッシュか Suffix Array に移る。

## 参考 {#references}

- [AtCoder Library「String」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/string.md)：`z_algorithm` の宣言・制約・計算量
- [ikatakos「AtCoder Beginner Contest 430 E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1101_abc430)：例題の方針（A+A の中で B を探す）と制約（解説の部分だけを参照）
- [ikatakos「AtCoder Beginner Contest 284 E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/0107_abc284)：例題の制約と、前半と後半の反転を作り、Z 配列で区切り位置ごとの一致を判定する方法（解説の部分だけを参照）。回転への帰着は本文で導いた
- [ikatakos「ユニークビジョンプログラミングコンテスト2025 春（AtCoder Beginner Contest 398）F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0322_abc398)：練習の方針（最長の回文の接尾辞を求めて前を反転して足す）（解説の部分だけを参照）
- [drken「AtCoder ABC 141 E - Who Says a Pun? (1D, 水色, 500 点)」](https://drken1215.hatenablog.com/entry/2019/09/16/014600)：練習の方針（接尾辞ごとの Z と $\min(z, d)$）
- [ikatakos「AtCoder Beginner Contest 257 G 問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0625_abc257)：力試しの方針と、届く範囲を広げる貪欲（解説の部分だけを参照）
- [kmjp「AtCoder ABC #343 : G - Compress Strings」](https://kmjp.hatenablog.jp/entry/2024/03/02/0930)：力試しの方針（含まれる文字列の除去と、Z による重なりの計算）
- [drken「AtCoder ARC 055 C - ABCAC」](https://drken1215.hatenablog.com/entry/2023/08/07/004451)：力試しの方針（S と反転の Z 配列による数え方）
