---
id: modint
title: modint
aliases: [static_modint, dynamic_modint, mint, modint998244353, modint1000000007]
type: technique
field: math
chapter: mod の計算
order: 60
level: 基礎
kind: [整数論, 実装・C++]
prerequisites: [mod-inverse]
related: [acl-reading#modint, mod-arithmetic, library-design]
summary: 四則演算のたびに自動で余りを取る型で、mod 付きの数え上げを素直に書ける。法が固定なら static_modint、入力で決まるなら dynamic_modint を使い、値は val() で取り出す。
complexity: 加減乗 O(1)、割り算・inv() O(log m)、pow(n) O(log n)
signs:
  - {type: phrase, text: 法 M（素数とは限らない）が入力で与えられ、その余りで数え上げの答えを出力する}
acl: [static_modint, dynamic_modint]
verify: []
frequency: A
frequency_evidence: 数え上げ・確率を mod で答える問題で常に使う道具（ページ単体の最近の出現は数えにくいので手で A にした）
sections:
  - {title: 何が自動になるか（加減乗除と負の数の正規化）, anchor: what-is-automatic}
  - {title: static_modint と dynamic_modint（set_mod）の使い分け, anchor: static-dynamic}
  - {title: val() で取り出す・大小比較や「0 になったか」で元の値は分からない, anchor: pitfalls}
  - {title: 割り算の条件（法が素数でなければ互いに素が必要）, anchor: division}
  - {title: 上位の手法での使われ方（階乗の表・畳み込み・行列・期待値）, anchor: connections}
  - {title: 自作するときの設計（加減の条件分岐・64bit の掛け算・pow と inv・入出力）, anchor: self-made}
  - {title: ACL の中身（Barrett 還元・raw）, anchor: acl-internals}
stage: draft
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：四則演算のたびに自動で余りを取る型で、mod 付きの数え上げを素直に書ける。法が固定なら static_modint、入力で決まるなら dynamic_modint を使い、値は `val()` で取り出す。
    - **いつ使うか**：法 M（素数とは限らない）が入力で与えられ、その余りで数え上げの答えを出力する。答えを 998244353 などで割った余りで出力する問題全般でも使う。
    - **計算量**：足し算・引き算・掛け算は $O(1)$、割り算と `inv()` は $O(\log m)$、`pow(n)` は $O(\log n)$
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)

<!-- textlint-disable -->
別名：static_modint・dynamic_modint・mint・modint998244353・modint1000000007
<!-- textlint-enable -->

modint は、法 $m$ で割った余り（$0$ 以上 $m$ 未満の値）だけを持ち、演算のたびに自動で余りを取り直す型である。式を普通の整数と同じ形で書けるので、余りの取り忘れや負の数の直し忘れがなくなる。ただし、型が直してくれるのは「modint どうしの演算」だけで、その手前の整数の計算や、余りから元の値を推し量ることは助けてくれない。このページはその境目を中心に書く。

このページでは法を $m$（素数なら $p$）と書き、ACL の型を `mint` と略す（`using mint = atcoder::modint998244353;`）。記法は[記法と用語の約束](../start/notation.md)にそろえる。ACL の書き方の基本（`.val()` で出力する・`<` がない・v1.6 で `val()` は `int`）は [ACL の読み方](../cpp/acl-reading.md#modint)にある。

## 何が自動になるか（加減乗除と負の数の正規化） {#what-is-automatic}

modint が自動でするのは次の 3 つである。どれも「値は常に $0$ 以上 $m$ 未満」という[不変条件](../guide/glossary.md#invariant)を保つための処理である。

- **整数から作るときの正規化**：`mint(x)` は $x \bmod m$ を $0$ 以上に直して持つ。$x$ が負でも、$10^{18}$ のような大きな `long long` でもよい
- **加減乗の後の正規化**：足し算・引き算は、結果が範囲を出たら $m$ を引く・足すだけで直す。掛け算は 64bit で掛けてから余りを取る。引き算の後に負になる心配がない（[mod の計算の基本](../math/mod-arithmetic.md)の処理を型が肩代わりする）
- **割り算**：`a / b` は $b$ の逆元を掛ける。使える条件は[割り算の条件](#division)の節にある

自動にならないのは、modint になる前の整数の計算である。`mint x = a * b;` は、`a * b` を `long long` のまま計算してから mint に直す。$a, b$ が $10^{18}$ 近くならその時点であふれる（符号付き整数のあふれは未定義動作）。`mint bad = 1 / 2;` も、`int` の割り算で 0 になってから mint に直るので 0 になる。

```cpp
--8<-- "modint/conversion.cpp:core"
```

避け方は「片方を先に mint にする」ことである。`mint(a) * b` は左が mint なので、`b` も mint に直ってから掛け算が行われる。読み込んだ値を、最初から mint の変数や `vector<mint>` へ入れてしまうのも確実である。

??? question "確認問題：どれが正しい？"
    `long long` の $a, b, c$（どれも $0$ 以上 $10^{18}$ 以下）について、$(a + b) \times c \bmod 998244353$ を求めたい。次のうち正しく求まるのはどれか。

    1. `mint((a + b) * c)`
    2. `(mint(a) + b) * c`
    3. `mint(a + b) * c`

    ??? success "答え"
        2 と 3 である。1 は `(a + b) * c` を `long long` で計算するのであふれる。3 の `a + b` は $2 \times 10^{18}$ 以下で `long long`（約 $9.2 \times 10^{18}$ まで）に収まるので正しい。ただし 3 は和が収まるかを毎回考える必要があるので、2 のように最初に mint にする方が安全である。

## static_modint と dynamic_modint（set_mod）の使い分け {#static-dynamic}

ACL の modint には、法をコンパイル時に決める static_modint と、実行時に決める dynamic_modint の 2 種類がある。

| 型 | 法の決まり方 | 使う場面 |
| --- | --- | --- |
| `modint998244353`・`modint1000000007` | 型に書かれた定数 | 問題文に法が書かれている（ほとんどの問題） |
| `static_modint<M>` | テンプレート引数の定数 | ほかの定数の法（例：`static_modint<1000000009>`） |
| `modint`（`dynamic_modint<-1>`） | `modint::set_mod(m)` | 法が入力で与えられる |

法が定数なら static_modint を使う。法が入力で与えられる問題では、法は実行するまで分からないので static_modint は使えず、`modint` を使う。`set_mod` は読み込んだ直後、mint の値を 1 つも作らないうちに呼ぶ。

```cpp
--8<-- "modint/dynamic.cpp:core"
```

- **set_mod を忘れても動いてしまう**：`modint` の既定の法は 998244353 なので、`set_mod` を書き忘れてもコンパイルと実行は通り、答えだけが違う。入出力例の法がたまたま 998244353 だと気づけない
- **set_mod の前に作った値**：`set_mod` より前に作った mint（グローバルの `vector<mint>` を整数で初期化したものなど）は、古い法の余りのまま残る。表は `set_mod` の後で作る
- **法の範囲**：$1 \le m \le 2 \times 10^9 + 1000$。$m = 1$ ならすべての値が 0 になる
- **法を 2 種類使う**：`modint` の法は型に 1 つだけなので、2 つの法を同時に使うなら `dynamic_modint<0>` と `dynamic_modint<1>` のように番号の違う型を使う

static_modint は法が定数なので、コンパイラが「定数で割った余り」を掛け算とシフトに置き換えられ、速くなる。dynamic_modint は代わりに [Barrett 還元](#acl-internals)で速くしているが、法が定数のときは static_modint を使うのが基本である。

## val() で取り出す・大小比較や「0 になったか」で元の値は分からない {#pitfalls}

mint が持っているのは余りだけで、元の整数の情報は失われている。このことから来るバグが modint の落とし穴の大半である。

**`x == 0` で「1 つもない」とは言えない**。数え上げの答えが mint で 0 でも、元の個数が $998244353$ の倍数だった可能性がある。「方法がなければ $-1$ を出力」という問題では、個数を mint で数えて 0 かどうかを見るのではなく、到達できるかを `bool` の表で別に持つ。1 つの表で済ませたいなら、DP の値を「mint の個数」と「1 つ以上あるか」の組にする。

**大小比較・最大値は余りでは取れない**。mint に `<` がないのは、余りの大小が元の値の大小と関係しないからである（$998244353$ の余りは 0 で、$998244352$ より小さく見える）。最大値を求める DP や、どちらの選び方が得かの比較は、`long long`・`double` などの元の値で行い、答えの出力にだけ mint を使う。確率や期待値で最適な戦略を選ぶ場合も同じである（[有理数を mod で表す](../comb/rational-mod.md#no-compare)）。

**`val()` を元の値として使う**。`x.val()` は $0$ 以上 $m$ 未満の余りである。配列の添字や個数の比較にそのまま使うと、元の値と違うので誤る。`val()` を使うのは出力と、余りそのものに意味がある計算（別の法での計算へ値を渡すなど）だけにする。法が奇数なら `val()` の偶奇と元の値の偶奇も関係しない（`mint(998244354).val()` は 1 だが、元の値は偶数）。元の値の偶奇のような性質が要るなら、`bool` や `long long` で別に持つ。

**掛けた数で割って戻せるとは限らない**。`x *= 6;` の後に `x /= 3;` で戻すのは、割る数が法と互いに素なら正しい。しかし $p$ を掛けてから $p$ で割るように、割る数が法 $p$ の倍数だと、掛けた時点で値が 0 になり戻せない。$\binom{n}{k}$ を $n! / (k!(n-k)!)$ で求めるのも、$n \ge p$ なら分母が 0 になる。整数になる式でも途中の値は余りなので、割れるかを mint の値から判断せず、[割り算の条件](#division)を満たすかを式の側で確かめる。

??? question "確認問題：「−1 を出力」の判定"
    グリッドの左上から右下への経路の数を mint の DP で数え、`dp[h - 1][w - 1] == 0` なら「到達できない」として $-1$ を出力した。どんな場合に誤るか。

    ??? success "答え"
        経路が存在して、その数がちょうど $998244353$ の倍数のとき、mint の値が 0 になり $-1$ を出力してしまう。到達できるかは `bool` の DP か BFS で別に判定する。

## 割り算の条件（法が素数でなければ互いに素が必要） {#division}

`a / b` が意味を持つのは $b$ の逆元があるとき、すなわち $\gcd(b, m) = 1$ のときだけである（[逆元と mod での割り算](../math/mod-inverse.md)）。ACL はこの条件を `assert` で調べ、満たさないと止まる。AtCoder では実行時エラー（RE）になる。

- **法が素数 $p$**：$b$ が $p$ の倍数（mint として 0）でなければ割れる。static_modint は法が素数かをコンパイル時に判定し、素数ならフェルマーの小定理で $b^{p-2}$ を逆元にする
- **法が素数でない**：$\gcd(b, m) = 1$ のときだけ割れる。たとえば法 $10^9$ では、2 や 5 で割れない。逆元は[拡張ユークリッドの互除法](../math/ext-gcd.md)で求められる（ACL の dynamic_modint はいつもこちらを使う）

法が入力で与えられ、素数とは限らない問題では、割り算を使わない式に直すのが基本である。二項係数は「階乗の逆元」の代わりにパスカルの三角形 $\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$ で作れば、足し算だけで済む（[法が素数でないとき](../comb/binomial-precompute.md#composite-mod)）。

法が素数でも、割る数が $p$ の倍数になる場合は別に扱う。等比数列の和 $\frac{r^n - 1}{r - 1}$ は、$r \equiv 1 \pmod p$ だと分母が 0 になる。このときは和が $n$ 項の $1$ の和、すなわち $n \bmod p$ になる。割る前に「分母が mint で 0 にならないか」を考える習慣を付けるとよい。

??? question "確認問題：割れる？"
    法が $10^9$（素数でない）の `modint` で、`mint(10) / 3` と `mint(10) / 4` はそれぞれどうなるか。

    ??? success "答え"
        $\gcd(3, 10^9) = 1$ なので `mint(10) / 3` は計算でき、$3x \equiv 10 \pmod{10^9}$ を満たす $x$ になる。$\gcd(4, 10^9) = 4$ なので `mint(10) / 4` は逆元がなく、`assert` で止まる。

## 上位の手法での使われ方（階乗の表・畳み込み・行列・期待値） {#connections}

modint は、mod の値を扱う上位の手法の部品として使われる。どれも「普通の整数と同じ形で書ける」ことが効く。

- **階乗とその逆元の表**：`vector<mint> fact(n + 1), ifact(n + 1);` を作り、$\binom{n}{k}$ を $O(1)$ で求める（[二項係数の前計算](../comb/binomial-precompute.md)）。法は素数 $p$ で、$n < p$ でなければならない（$n \ge p$ なら $n!$ が 0 になり逆元がない）
- **DP の値**：数え上げの DP の表を `vector<mint>` にすれば、遷移の足し算・掛け算で余りを書かずに済む。表は 0 で埋まった状態から始まる
- **畳み込み**：ACL の `convolution` は `vector<static_modint<m>>` を受け取れる（[畳み込み](../math/convolution-ntt.md)）。法は NTT に向く素数でなければならない
- **行列累乗**：行列の要素を mint にすれば、整数の行列と同じコードで $\bmod m$ の行列累乗になる（[行列累乗](../math/matrix-power.md)）
- **確率・期待値**：答えが有理数 $P/Q$ のとき、途中の計算をすべて mint で行えば、最後に $P \times Q^{-1}$ が自然に得られる（[有理数を mod で表す](../comb/rational-mod.md)）

## 自作するときの設計（加減の条件分岐・64bit の掛け算・pow と inv・入出力） {#self-made}

自作するときは、値 $v$ を常に $0 \le v < m$ に保つことを不変条件にし、各演算をその上で組み立てる（ライブラリ全体の作り方は[自作ライブラリの設計](../guide/library-design.md)）。次は法をテンプレート引数で固定した最小の形である（$m < 2^{31}$ を仮定）。

```cpp
--8<-- "modint/self-made.cpp:core"
```

- **足し算・引き算は条件分岐**：$0 \le v, w < m$ なら $v + w < 2m$ なので、$m$ 以上なら 1 回引くだけでよい。`%` より速い。引き算は $v + (m - w)$ として同じ形にすると、符号なし整数のまま負にならない
- **掛け算は 64bit**：$v \times w < m^2 < 2^{62}$ なので、`unsigned long long` に直してから掛けて余りを取る。32bit のまま掛けるとあふれる。法が $2^{32}$ を超えるなら `__int128` が要る
- **コンストラクタで負の数を直す**：C++ の `%` は、負の数を割ると 0 以下の余りを返す（`-7 % 3` は `-1`）ので、`x %= m` の後に負なら $m$ を足す
- **pow と inv**：`pow` は[繰り返し二乗法](../math/mod-pow.md)で $O(\log n)$。`inv` を $v^{m-2}$ にすると法が素数のときだけ正しく、素数でない法も使うなら拡張ユークリッドで書く
- **入出力**：`operator<<` と `operator>>` を定義すると `cout << x` と `cin >> x` が書ける。ACL の modint にはないので、自作するなら入れておくと便利である
- **法をテンプレート引数にする**：法がコンパイル時の定数になるので `%` が速くなる。実行時に法が決まる版は、法を `static` 変数に持つ別の型として作る

確かめるときは、ACL の modint と同じ演算をして結果が一致するかを、負の数・0・法と等しい値・$10^{18}$ 近い値で比べる。上のコード片は、そうした比較の `assert` を `main` に持つ。

## ACL の中身（Barrett 還元・raw） {#acl-internals}

ACL の modint の実装には、自作の参考になる工夫が 2 つある。

**Barrett 還元**。dynamic_modint の法は実行時に決まるので、`z % m` をコンパイラが速い形に置き換えられない。そこで `set_mod` のときに $\mathrm{im} = \lceil 2^{64} / m \rceil$ を前計算しておく。積 $z = v \times w$ に対し、$\lfloor z \cdot \mathrm{im} / 2^{64} \rfloor$ は商 $\lfloor z / m \rfloor$ に等しいか 1 大きいだけになる。だから $z$ からこの数の $m$ 倍を引き、引きすぎていたら $m$ を足し戻せば余りが求まる。128bit の掛け算 1 回と 64bit の掛け算 1 回で、割り算を使わずに済む。

**raw**。`mint::raw(x)` は余りを取らずに $x$ をそのまま入れる。$0 \le x < m$ が分かっているときに余りの計算を省くための関数で、範囲外の値を入れたときの動作は未定義である。ふつうは `mint(x)` で十分で、ループの中で何度も作るときの定数倍の高速化にだけ使う。

ほかに、static_modint の `inv` は法が素数かどうかで方法を変える。素数の判定はコンパイル時に行われ（`internal::is_prime`）、素数なら $v^{m-2}$、そうでなければ拡張ユークリッドの互除法を使う。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC357 D. 88888888](https://atcoder.jp/contests/abc357/tasks/abc357_d)（diff 970）：正の整数 N を N 回並べてできる整数を 998244353 で割った余りを求める（N ≤ 10^18）。
- [ABC281 G. Farthest City](https://atcoder.jp/contests/abc281/tasks/abc281_g)（diff 2304）：頂点 1 から頂点 N への距離が他のどの頂点への距離よりも真に大きい、N 頂点の連結な単純無向グラフの数を、入力の M（素数とは限らない）で割った余りで求める。

</div>

??? note "練習の方針"
    - **ABC357 D**：$N$ の桁数を $d$、$r = 10^d$ とすると、答えは $N(1 + r + \dots + r^{N-1}) = N \cdot \frac{r^N - 1}{r - 1}$ である。`mint r = mint(10).pow(d);` とし、`((r.pow(N) - 1) / (r - 1) * mint(N)).val()` を出力する。$N$ は $10^{18}$ まであるので、`mint(N)` にしてから掛ける（`long long` どうしで先に掛けない）。$d \le 19$ の範囲で $10^d - 1$ は 998244353 の倍数にならないので、この割り算はいつも使える
    - **ABC281 G**：法 $M$ が入力なので `modint` を使い、読み込んだ直後に `set_mod(M)` を呼ぶ。頂点 1 からの距離の層ごとに頂点数を決める DP で、層の間・層の中の辺の張り方の数を掛けていく。$M$ が素数とは限らないので割り算は使わず、二項係数はパスカルの三角形で作る。全体で $O(N^3)$

## 参考 {#references}

- [AtCoder Library「Modint」（document_ja/modint.md）](https://github.com/atcoder/ac-library/blob/master/document_ja/modint.md)：型の種類・set_mod の制約・割り算と inv の条件と計算量・raw・複数の法
- [AtCoder Library「modint.hpp」・「internal_math.hpp」](https://github.com/atcoder/ac-library/tree/master/atcoder)：負の数の正規化・既定の法 998244353・inv の分岐・Barrett 還元の実装（v1.6 のソースを手元で確認）
- [noshi91「modint 構造体を使ってみませんか？ (C++)」](https://noshi91.hatenablog.com/entry/2019/03/31/174006)：自作の設計（加減の条件分岐・法をテンプレート引数にする理由・実行時の法の版）
- [drken「AtCoder ABC 357 D - 88888888 (1Q, 緑色, 350 点)」](https://drken1215.hatenablog.com/entry/2024/06/10/000051)：練習の方針（等比数列の和を modint の pow と割り算で求める）
- [drken「AtCoder ABC 281 G - Farthest City (黄色, 600 点)」](https://drken1215.hatenablog.com/entry/2022/12/13/173300)：練習の方針（層ごとの DP、法が入力で二項係数をパスカルの三角形で作る）
