---
id: dp-speedup-overview
title: DP の高速化の選び方
aliases: [DP の高速化, DP 高速化, DP 最適化, DP Optimization, 遷移の高速化]
type: hub
field: dp
chapter: DP の高速化
order: 310
level: null
kind: [DP, 案内]
prerequisites: [dp-basics]
related: [dp-prefix-sum, dp-segment-tree, inline-dp, dp-dimension-reduction, bitset-speedup#subset-sum-shift, online-convolution#dp-as-polynomial, fps-basics, matrix-power#dp-transition, cht, monge, alien-dp, slope-trick]
summary: 素直な DP が間に合わないとき、貰う形の式の右辺の形（区間の和・区間の最小・多項式の積・同じ線形の遷移の繰り返し・一次関数の最小など）から速くする道具を選ぶ。
complexity: null
signs:
  - {type: shape, text: 素直に書いた DP の遷移が状態 1 つあたり O(N) かかり、全体で O(N^2) になる}
acl: []
sections:
  - {title: 状態を減らすか、遷移を速くするか, anchor: two-directions}
  - {title: 貰う形の式を書き、右辺の形を見る, anchor: read-the-recurrence}
  - {title: 早見表：遷移の形から道具を選ぶ, anchor: shape-to-tool}
  - {title: 多項式の積・同じ線形の遷移の繰り返し（畳み込み・行列累乗へ）, anchor: algebraic-tools}
  - {title: 凸性を使う高速化（CHT・Monge・Alien DP・Slope Trick）の使いどころ, anchor: convexity}
stage: draft
updated: 2026-10-22
---

!!! abstract "要点"
    - **何のページか**：素直な DP が間に合わないとき、貰う形の式の右辺の形（区間の和・区間の最小・多項式の積・同じ線形の遷移の繰り返し・一次関数の最小など）から速くする道具を選ぶ。
    - **いつ使うか**：素直に書いた DP の遷移が状態 1 つあたり $O(N)$ かかり、全体で $O(N^2)$ になる。
    - **使い方**：まず貰う形の式を書く。右辺の集約（和・min・OR）と遷移元の範囲の動き方を[早見表](#shape-to-tool)で探し、行のページの節へ進む。
    - **計算量**：全体は状態数 × 遷移 1 回の手間。遷移 1 回の手間は、累積和が $O(1)$、セグメント木が $O(\log N)$、スライド最小値がならし $O(1)$。状態数 $n$・ステップ数 $T$ の行列累乗は $O(n^3 \log T)$
    - **前提**：[DP の基本](../dp/dp-basics.md)

<!-- textlint-disable -->
別名：DP の高速化・DP 高速化・DP 最適化・DP Optimization・遷移の高速化
<!-- textlint-enable -->

DP の高速化の選び方は、間に合わない DP を前にして、どのページの道具を使えばよいかを引くための案内である。道具の中身は各ページに任せ、ここでは「式のどこを見れば道具が決まるか」と、その対応の表をまとめる。

## 状態を減らすか、遷移を速くするか {#two-directions}

DP の計算量は「状態数 × 遷移 1 回の手間」である（[状態](../guide/glossary.md#state)・[遷移](../guide/glossary.md#transition)の数え方は [DP の基本](../dp/dp-basics.md#four-parts)）。だから速くする道は 2 つしかない。状態の数を減らすか、1 つの状態の値を求める手間を減らすかである。

| 何が多いか | 見るところ | 道具 | ページ |
| --- | --- | --- | --- |
| 状態数（表が大きすぎる） | 添字の範囲は答えに効く分だけで足りるか | 上限で打ち切る | [状態の削減](../dp/dp-dimension-reduction.md#cap) |
| 状態数（添字の範囲が $10^9$ など） | 値と添字を入れ替えられるか | 値と添字の入れ替え | [状態の削減](../dp/dp-dimension-reduction.md#dp-swap-key-value) |
| 状態数（何を持つか自体が多い） | 将来に効く要約だけを持っているか | 状態の設計の見直し | [状態の設計](../dp/dp-state-design.md#state-count) |
| 遷移 1 回の手間（1 つの値に $O(N)$ 個の遷移元） | 貰う形の式の右辺の形 | 累積和・セグメント木・CHT など | [次の節](#read-the-recurrence)と[早見表](#shape-to-tool) |

たとえば $N = 2 \times 10^5$ 個の状態がそれぞれ直前 $K = 2 \times 10^5$ 個から値を集めると、$NK = 4 \times 10^{10}$ 回で間に合わない（1 秒に $10^8$ 回の目安は[計算量の見積もり](../basics/complexity-estimation.md#how-to-estimate)）。状態数 $N$ は減らせないことが多いので、遷移の $K$ を $1$ や $\log N$ に縮める道を探す。逆に、ナップサックの重さの上限が $10^9$ のように表そのものが作れないときは、遷移を速くしても意味がなく、状態の側を直す（[EDPC E](../dp/dp-dimension-reduction.md#dp_e)）。

2 つの道は組み合わさることも多い。状態を減らした後の遷移を、さらに道具で速くする問題もある（[力試し](#challenge)の典型90 090 は、状態を減らしてから線形漸化式の高速化を使う）。

## 貰う形の式を書き、右辺の形を見る {#read-the-recurrence}

道具を選ぶ前に、まず貰う形の式を 1 本書く。貰う形とは、$\mathrm{dp}[i]$ を左辺に置き、右辺に遷移元 $j$ からの値を集める書き方である（配る形との関係は [DP の基本](../dp/dp-basics.md#dp-push-pull)）。

$$
\mathrm{dp}[i] = \bigoplus_{j \in R(i)} f(\mathrm{dp}[j], i, j)
$$

この式で見るのは次の 3 つである。

1. **集約 $\bigoplus$ の種類**：和か、min・max か、OR（可否）か。和は引き算で戻せるので累積和が使えるが、min・max は戻せない
2. **遷移元の範囲 $R(i)$ の動き方**：接頭辞 $[0, i)$ か、両端が戻らずに右へ動く窓か、任意の区間か、「値が小さいもの」のように値で決まる集合か
3. **項 $f$ の形**：$\mathrm{dp}[j]$ に $i$ だけの量を足すだけか、$i$ と $j$ の積の項があるか、係数が差 $i - j$ だけで決まるか、遷移の仕方がどの $i$ でも同じか

次の図は、範囲 $R(i)$ の 3 つの典型を並べたものである。上の 2 つは集約の種類で道具が分かれる。3 つ目は位置が飛び飛びなので、値を添字にした木を使う。

![① 接頭辞 [0, i) から読むなら、和は累積和、min・max は累積 min・max で足りる。② 幅 3 の窓 [i−3, i) が右へ動くだけなら、和は累積和、min・max はスライド最小値。③ A[j] < A[i] を満たす j のように位置が飛び飛びなら、値を添字にしたセグメント木を使う](../img/dp-speedup-overview/read-ranges.svg)

同じ「足場を跳んで進む」DP でも、右辺の形が変わると道具が変わる。足場 $0, 1, \dots, N-1$ を左から進み、足場 $i$ に来る直前の足場を $j$ とする。

| 右辺 | 形 | 道具 |
| --- | --- | --- |
| $\sum_{j = i-K}^{i-1} \mathrm{dp}[j]$（行き方の数） | 連続区間の和 | [累積和](../dp/dp-prefix-sum.md#pull-and-push) |
| $\min_{i-K \le j < i} \mathrm{dp}[j] + c_i$ | 右へ動く窓の min | [スライド最小値](../dp/dp-segment-tree.md#dp-sliding-window) |
| $\min_{j < i,\ h_j < h_i} \mathrm{dp}[j] + c_i$ | 値で決まる集合の min | [値を添字にしたセグメント木](../dp/dp-segment-tree.md#values-on-segment-tree) |
| $\min_{j < i} \mathrm{dp}[j] + (h_i - h_j)^2$ | 積 $h_i h_j$ の項が 1 つ | [CHT](../dp/cht.md#lines) |
| $\sum_{j < i} \mathrm{dp}[j]\, g[i - j]$ | 係数が差 $i - j$ だけで決まる | [畳み込み](../math/online-convolution.md#dp-as-polynomial) |
| $\sum_{s = 1}^{K} \mathrm{dp}[i - s]$ で $N \le 10^{18}$、$K$ が小さい | 同じ線形の遷移の繰り返し | [行列累乗](../math/matrix-power.md#dp-transition) |

配る形で書いた DP は、配る先が連続区間ならいもす法で累積和と同じことができる（[配る形といもす法](../dp/dp-prefix-sum.md#pull-and-push)）。それ以外の形は、いったん貰う形に書き直してから右辺を見る方が道具を当てやすい。

## 早見表：遷移の形から道具を選ぶ {#shape-to-tool}

貰う形の式の右辺から行を探し、ページの節へ進む。おおむね上の行ほど易しく、ABC でよく出る。例題の列は、そのページに例題・練習として載せた問題である。

| 右辺の形（遷移元の範囲・項） | 道具 | ページ | 例題 |
| --- | --- | --- | --- |
| 連続区間の和 | 累積和（配る形ならいもす法） | [DP と累積和](../dp/dp-prefix-sum.md#pull-and-push) | [EDPC M](../dp/dp-prefix-sum.md#dp_m)・[ABC179 D](../dp/dp-prefix-sum.md#abc179_d) |
| 接頭辞（$j < i$ すべて）の min・max | 累積 min・max | [DP と累積和](../dp/dp-prefix-sum.md#prefix-min) | — |
| 右へ動くだけの窓の min・max | スライド最小値（単調 deque） | [セグメント木・スライド最小値](../dp/dp-segment-tree.md#dp-sliding-window) | — |
| 手前で初めて自分より大きい位置の 1 点 | 単調スタック | [単調スタック](../ds/monotonic-stack.md#dp-transition) | [ABC359 E](../ds/monotonic-stack.md#abc359_e) |
| 任意の区間・値の範囲の min・max・和 | セグメント木・BIT（値なら座標圧縮） | [セグメント木・スライド最小値](../dp/dp-segment-tree.md#values-on-segment-tree) | [EDPC Q](../dp/dp-segment-tree.md#dp_q)・[典型90 037](../dp/dp-segment-tree.md#typical90_ak) |
| コストが $\lvert x_i - x_j \rvert$ の一次式 | 左右に分けて 2 本のセグメント木 | [セグメント木・スライド最小値](../dp/dp-segment-tree.md#split-abs) | [ABC353 G](../dp/dp-segment-tree.md#abc353_g) |
| 前の段がほぼそのまま写り、一部だけ変わる・範囲に一律に足す | インライン DP（遅延セグメント木） | [インライン DP](../dp/inline-dp.md#diff-per-row) | [ABC271 E](../dp/inline-dp.md#abc271_e)・[EDPC W](../dp/inline-dp.md#dp_w) |
| 可否（bool）で、和の値を添字にした表 | bitset のシフト OR | [bitset による高速化](../misc/bitset-speedup.md#subset-sum-shift) | [AGC020 C](../misc/bitset-speedup.md#practice) |
| 係数が差 $i - j$ だけで決まる和・多項式の積 | 畳み込み・分割統治 FFT・FPS | [分割統治 FFT](../math/online-convolution.md#dp-as-polynomial) | [ABC213 H](../math/online-convolution.md#abc213_h) |
| 毎回同じ線形の遷移を巨大な回数くり返す | 行列累乗・ダブリング・線形漸化式の高速化 | [行列累乗](../math/matrix-power.md#dp-transition) | [EDPC R](../math/matrix-power.md#dp_r)・[ABC305 G](../math/matrix-power.md#abc305_g) |
| $\min_j (\mathrm{dp}[j] + a_j x_i + b_j)$ | CHT・Li Chao Tree | [CHT](../dp/cht.md#lines) | [EDPC Z](../dp/cht.md#dp_z) |
| $\min_j (\mathrm{dp}_{k-1}[j] + c(j, i))$ で $c$ が Monge（前の段が確定している） | monotone minima | [Monge](../dp/monge.md#monotone-minima) | [ABC348 G](../dp/monge.md#abc348_g) |
| $\min_j (\mathrm{dp}[j] + c(j, i))$ で $c$ が Monge（段のない形） | LARSCH・左半分を先に確定させる分割統治 | [Monge](../dp/monge.md#smawk-larsch) | — |
| 区間 DP $\mathrm{dp}[l][r] = \min_m (\mathrm{dp}[l][m] + \mathrm{dp}[m][r]) + w(l, r)$ で $w$ が Monge かつ区間を広げても減らない | Knuth-Yao | [Monge](../dp/monge.md#knuth-yao) | — |
| ちょうど $K$ 個選び、最適値が $K$ について凸 | Alien DP | [Alien DP](../dp/alien-dp.md#penalty) | [ABC218 H](../dp/alien-dp.md#abc218_h) |
| $\mathrm{dp}[x]$ が $x$ の凸な折れ線で、$\lvert x - a \rvert$ を足す・累積 min を取る | Slope Trick | [Slope Trick](../dp/slope-trick.md#breakpoints) | [ABC217 H](../dp/slope-trick.md#abc217_h) |
| 1 点を書き換えるたびに DP の答えを聞く | 遷移の行列をセグメント木に載せる | [動的 DP](../dp/dynamic-dp.md#what-it-does) | [ABC246 Ex](../dp/dynamic-dp.md#abc246_h) |

表の読み方には 3 つの注意がある。

- **1 つの式に複数の行が当たる**：区間の min は、窓が単調ならスライド最小値、そうでなくてもセグメント木で書ける。セグメント木は和・min・max のどの行の代わりにもなる。$\log$ が付いても間に合うなら、迷わずセグメント木でよい（使い分けの詳細は[セグメント木・累積和・スライド最小値の使い分け](../dp/dp-segment-tree.md#which-tool)）
- **前の段が確定しているか**：累積和とスライド最小値は、読む値が読む前に決まっていることを前提にする。同じ段の値を書きながら任意の範囲を読むなら、セグメント木か BIT にする
- **CHT から下は発展**：CHT から Slope Trick までは、式を変形して凸性や Monge 性を確かめる手間がかかる。使いどころは[凸性を使う高速化](#convexity)にまとめた。最後の動的 DP は、遷移を行列に書き直す手間がかかる

## 多項式の積・同じ線形の遷移の繰り返し（畳み込み・行列累乗へ） {#algebraic-tools}

右辺が和で、各項が「前の値 × 係数」の線形な形なら、DP を多項式や行列の計算とみて速くできる。分かれ目は、係数が何で決まるかと、段の数がどれだけ大きいかである。

| 式の形 | 規模の目安 | 道具 | ページ |
| --- | --- | --- | --- |
| $\mathrm{dp}[i] = \sum_{j<i} \mathrm{dp}[j]\, g[i - j]$（係数が差だけで決まる） | $N \le 2 \times 10^5$ 程度 | FPS の逆元・オンライン畳み込み | [DP の遷移を多項式の積とみる](../math/online-convolution.md#dp-as-polynomial) |
| 段ごとに決まった多項式を掛ける（「値 $v$ を使う・使わない」の $(1 + x^v)$ など） | 段も次数も $10^5$ 程度 | 畳み込み（NTT）を分割統治で | [多数の多項式の積](../math/online-convolution.md#product-of-many)・[畳み込み](../math/convolution-ntt.md#sum-pairs) |
| $\mathrm{dp}[t+1] = A\, \mathrm{dp}[t]$（どの段でも同じ遷移） | 段 $T \le 10^{18}$、状態 $n$ が 100 程度まで | 行列累乗 $O(n^3 \log T)$ | [DP の遷移を行列にする](../math/matrix-power.md#dp-transition) |
| 同じ遷移だが、行列にすると大きすぎる | $n^3$ が重いとき | 遷移の形を使ったダブリング | [ダブリングで遷移を合成する](../math/matrix-power.md#doubling-transition) |
| 1 本の $K$ 項の線形漸化式 | $K$ が数千〜$10^5$、$N \le 10^{18}$ | きたまさ法・Bostan-Mori | [線形漸化式の高速化](../math/linear-recurrence-fast.md#vs-matrix) |

**畳み込みに乗る条件**は、係数が添字の差 $i - j$ だけで決まることである。たとえば「歩幅 $s$ で跳ぶ方法が $g[s]$ 通り」のとき、$\mathrm{dp}[i] = \sum_{j<i} \mathrm{dp}[j]\, g[i-j]$ になる。素朴には $O(N^2)$ だが、多項式で $P = \mathrm{dp}[0] / (1 - G)$ と書けるので、FPS の逆元で $O(N \log N)$ になる（式の導き方は[分割統治 FFT のページ](../math/online-convolution.md#dp-as-polynomial)）。係数が $i$ や $j$ そのものにもよるなら、畳み込みには乗らない。

**行列累乗に乗る条件**は、遷移の仕方が段 $t$ によらないことと、状態が少ないことである。歩幅が $1$〜$K$ の跳び方の数で $N \le 10^{18}$ なら、直前 $K$ 個の値を状態にした $K \times K$ の行列の $N$ 乗になる。見積もりは $n^3 \log T$ で、$n = 100$、$T = 10^{18}$ なら $10^6 \times 60 = 6 \times 10^7$ 回で間に合う。$n = 500$ では $7.5 \times 10^9$ 回になり、間に合わない。$\min$ と $+$ の行列でも結合法則が成り立つので、最短路のような最適化の DP にも同じことができる（[半環の行列](../math/matrix-power.md#semiring)）。

段を進めるのではなく列の 1 点を書き換えるたびに答えを求め直すなら、各位置の遷移の行列をセグメント木に載せる（[動的 DP](../dp/dynamic-dp.md#matrix-on-segment-tree)）。

## 凸性を使う高速化（CHT・Monge・Alien DP・Slope Trick）の使いどころ {#convexity}

ここに並ぶ 4 つの手法は、どれも発展のページである。ABC では難しい G や Ex でまれに出る程度なので、黄を目指す段階では「式がこの形なら名前を思い出せる」ことを目標にし、ライブラリを用意して使う。どれも式の変形で形を確かめてから使う。

| 確かめる形 | 確かめ方 | 道具 | ページ |
| --- | --- | --- | --- |
| コストを展開すると $i$ だけの項・$j$ だけの項と、積の項 1 つに分かれる | $(h_i - h_j)^2 = h_i^2 - 2h_i h_j + h_j^2$ のように展開する | CHT・Li Chao Tree | [CHT](../dp/cht.md#lines) |
| 区間のコスト $c(l, r)$ が、交差する 2 区間の和 ≤ 外側と内側の和を満たす | 定義の不等式を確かめるか、小さい入力で全探索して確かめる | monotone minima・LARSCH・Knuth-Yao | [Monge 性の定義と確かめ方](../dp/monge.md#definition) |
| 「ちょうど $K$ 個」の最適値 $f(K)$ が $K$ について凸 | $f(K+1) - f(K)$ が単調になるかを小さい入力で確かめる | Alien DP | [罰金で個数の制約を外す](../dp/alien-dp.md#penalty) |
| $\mathrm{dp}[x]$ を $x$ の関数とみると凸な折れ線で、遷移が折れ線の足し算・累積 min | 足す関数が凸か（$\lvert x - a \rvert$ など）を見る | Slope Trick | [凸関数を傾きの変わる点で表す](../dp/slope-trick.md#breakpoints) |

凸性は「たぶん凸」で使うと、誤った答えを静かに返す。小さい入力で素朴な DP の値を全部出し、差が単調に並ぶかを確かめてから使うのが安全である（[凸関数](../guide/glossary.md#convex-function)の定義は用語集）。ABC の制約では、Monge 性があっても $O(N^2)$ や $O(N^3)$ のまま通ることも多い。まず素朴な計算量で間に合うかを見積もり、間に合わないときだけこれらを持ち出す。

凸性の中でも「ちょうど $K$ 個」の形は、Monge な区間分割と Alien DP を組み合わせることがある（[Monge な区間分割と組み合わせる](../dp/alien-dp.md#with-monge)）。個数ごとの最適値の列どうしを合成するなら、上に凸な列どうしの (max,+) 畳み込み（下に凸なら (min,+) 畳み込み）が使える（[凸な列どうしの合成](../dp/monge.md#convex-max-plus-convolution)）。

## 落とし穴 {#pitfalls}

- **式を書かずに道具から考える**：問題文に「区間」とあるだけでセグメント木を書き始めると、見落としが起きる。遷移元が接頭辞なら累積 min で足りるし、そもそも範囲でないこともある。CHT も、コストに $i$ と $j$ の積の項がなければ使えない。先に貰う形の式を 1 本書き、[右辺の 3 つの点](#read-the-recurrence)を確かめる。
- **min・max を累積の差で求める**：和は $S_r - S_l$ で区間の和に戻せるが、min は戻せない。$A = (1, 5, 3)$ の区間 $[1, 3)$ の min は 3 である。一方、累積 min は $1, 1, 1$ で、どう組み合わせても 3 は出てこない。累積 min が使えるのは範囲が接頭辞のときだけである。それ以外はスライド最小値かセグメント木にする（[累積 min・max](../dp/dp-prefix-sum.md#prefix-min)）。
- **範囲の端を切り詰め忘れる**：窓 $[i - K, i)$ は $i < K$ で負の添字に出る。下端を $\max(0, i - K)$ に切り詰める。範囲が空になる $i$ の値も、最小化なら $+\infty$、数え上げなら 0 と決めておく。mod の下で累積和の差が負になる落とし穴は [DP と累積和の落とし穴](../dp/dp-prefix-sum.md#pitfalls)にある。
- **行列累乗の $n^3$ を忘れる**：段の数が巨大だと行列累乗を思い浮かべるが、計算量は状態数 $n$ の 3 乗に効く。$n = 500$ で $T = 10^{18}$ なら約 $7.5 \times 10^9$ 回で間に合わない。状態を減らすか、漸化式が 1 本なら[線形漸化式の高速化](../math/linear-recurrence-fast.md#vs-matrix)を使う。

## 確認問題 {#quiz}

??? question "確認問題：直前 K 個の最小値"
    $\mathrm{dp}[i] = \min_{i-K \le j < i} \mathrm{dp}[j] + c_i$ を、$N, K \le 2 \times 10^5$ で求めたい。素朴な計算量と、何で速くするかを答えよ。

    ??? success "答え"
        素朴には $O(NK)$ で、最大 $4 \times 10^{10}$ 回になる。遷移元の窓 $[i-K, i)$ は $i$ とともに右へ動くだけなので、スライド最小値で全体 $O(N)$ になる（[スライド最小値による遷移](../dp/dp-segment-tree.md#dp-sliding-window)）。セグメント木で 1 回 $O(\log N)$、全体 $O(N \log N)$ にしても間に合う。min は引き算で戻せないので、累積和の考え方は使えない。

??? question "確認問題：2 乗のコスト"
    $\mathrm{dp}[i] = \min_{j < i} \bigl(\mathrm{dp}[j] + (x_i - x_j)^2\bigr)$ を、$N \le 2 \times 10^5$ で求めたい。どの道具が使えるか。式をどう変形するか。

    ??? success "答え"
        展開すると $\mathrm{dp}[j] + x_j^2 - 2x_i x_j + x_i^2$ で、$x_i^2$ は $j$ によらない。$j$ ごとに傾き $a_j = -2x_j$、切片 $b_j = \mathrm{dp}[j] + x_j^2$ の直線を作れば、$\mathrm{dp}[i] = \min_j (a_j x_i + b_j) + x_i^2$ で、直線の最小値を問う形になる。CHT が使える（[遷移を直線の最小値に変形する](../dp/cht.md#lines)）。

??? question "確認問題：巨大な段数"
    1 回に $1$〜$K$ 段進める階段で、$N$ 段目に着く方法の数を求めたい。$N \le 10^{18}$、$K \le 50$ のとき、何を状態にして、どの道具を使うか。

    ??? success "答え"
        $\mathrm{dp}[i] = \sum_{s=1}^{K} \mathrm{dp}[i-s]$ は、どの $i$ でも同じ線形の遷移である。直前 $K$ 個の値 $(\mathrm{dp}[i-1], \dots, \mathrm{dp}[i-K])$ を状態にすると、1 段進める操作が $K \times K$ の行列になる。行列累乗で $O(K^3 \log N)$、$50^3 \times 60 = 7.5 \times 10^6$ 回で求まる（[DP の遷移を行列にする](../math/matrix-power.md#dp-transition)）。

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [典型90 090. Tenkei90's Last Problem（★7）](https://atcoder.jp/contests/typical90/tasks/typical90_cl)（diff —）：長さ N の 0 以上の整数の列のうち、どの区間でも（区間の最小値）×（区間の長さ）が K 以下になるものの個数を、998244353 で割った余りで求める。

</div>

??? note "方針"
    小課題を順に解くと、高速化の道具を段階的に使うことになる。列の値を棒の高さとみると、条件は「棒の下にできるどの長方形も面積が $K$ 以下」と言い換えられる。

    - 高さの大きい順に「区間の値がすべて $h$ 以上である数え方」を求める区間 DP を作る。区間の位置をずらしても条件は変わらないので、区間の端を状態から外し、（高さ $h$, 長さ $m$）だけを状態に持てばよい。$h \cdot m \le K$ の組だけを考えればよい。
    - 高さ $h$ を固定すると、長さについての値の列が線形漸化式を満たす。$h = 0$ の段では長さ $N$（$10^9$ まで）の項が要るので、行列累乗では状態が多すぎ、[線形漸化式の高速化](../math/linear-recurrence-fast.md#vs-matrix)（きたまさ法・Bostan-Mori）を使う。

## 参考 {#references}

- [E869120「競プロ典型 90 問」090 の解説（editorial/090-01〜05.jpg）](https://github.com/E869120/kyopro_educational_90/blob/main/editorial/090-01.jpg)：力試しの典型90 090 の問いと、小課題ごとの道具（区間 DP・状態の削減・線形漸化式の高速化）の流れ
