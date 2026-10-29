---
id: dp-prefix-sum
title: 累積和・いもす法による DP の高速化
aliases: [累積和 DP, いもす法 DP, 累積和で遷移をまとめる]
type: technique
field: dp
chapter: DP の考え方
order: 90
level: 水
kind: [DP, 累積和・差分]
prerequisites: [dp-basics, imos]
related: [dp-segment-tree, inline-dp, prefix-sum-2d, dp-sequence-partition, insertion-dp, dp-grid, dp-speedup-overview]
summary: 遷移元が連続した範囲の和になる DP を、前の段の累積和で 1 回 O(1) にする。遷移先が範囲なら、いもす法で差分に書いておき後で累積する。
complexity: 遷移 1 回 O(1)、累積和の作成は段ごとに O(段の幅)。全体は状態数に比例する（例：O(NK)）
signs:
  - {type: phrase, text: 各人に 0〜a_i 個を配る方法の数（上限つきの配り方）}
  - {type: constraint, text: N ≤ 100、K ≤ 10^5 程度で、O(NK) は通るが O(NK^2) は通らない}
  - {type: shape, text: 'dp[i] = Σ_{j=i−R}^{i−L} dp[j] のように、遷移元が連続した範囲の和'}
  - {type: shape, text: 'dp[i] から i+L〜i+R の範囲へ同じ値を配る'}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 6 ページに届く（直接 3）・古い ABC 7 問
sections:
  - {title: 貰う形と累積和・配る形といもす法, anchor: pull-and-push}
  - {title: 同じ段の累積和（上限つきの配り方）, anchor: same-row}
  - {title: 区間の和集合・方向ごとの累積（縦・横・斜め）, anchor: directional}
  - {title: 遷移元が接頭辞なら累積 min・累積 max でもよい, anchor: prefix-min}
  - {title: 余りごとの累積, anchor: by-remainder, level: 青}
  - {title: 2 次元の累積, anchor: two-dimensional, level: 青}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：遷移元が連続した範囲の和になる DP を、前の段の累積和で 1 回 $O(1)$ にする。遷移先が範囲なら、いもす法で差分に書いておき後で累積する。
    - **いつ使うか**：
        - 各人に 0〜$a_i$ 個を配る方法の数（上限つきの配り方）。
        - $N \le 100$、$K \le 10^5$ 程度で、$O(NK)$ は通るが $O(NK^2)$ は通らない。
        - $\mathrm{dp}[i] = \sum_{j=i-R}^{i-L} \mathrm{dp}[j]$ のように、遷移元が連続した範囲の和。
        - $\mathrm{dp}[i]$ から $i+L$〜$i+R$ の範囲へ同じ値を配る。
    - **計算量**：遷移 1 回が $O(1)$ になり、全体は状態数に比例する（上限つきの配り方なら $O(NK)$）。累積和の作成は段ごとに段の幅の時間で、状態数を超えない。
    - **前提**：[DP の基本](../dp/dp-basics.md)、[いもす法](../basics/imos.md)

<!-- textlint-disable -->
別名：累積和 DP・いもす法 DP・累積和で遷移をまとめる
<!-- textlint-enable -->

累積和・いもす法による DP の高速化は、遷移の式の右辺が「連続した範囲の和」になっているときに、その和を[累積和](../basics/prefix-sum.md)の 2 つの値の差で取る方法である。配る側から見て遷移先が連続した範囲なら、[いもす法](../basics/imos.md)で始点と終点の次に印を付け、後でまとめて累積する。どちらも、素直に書くと計算量の次数が 1 つ多い DP を、状態数と同じ次数に下げる。

## 貰う形と累積和・配る形といもす法 {#pull-and-push}

マス $0$ から歩幅 $L$〜$R$ で右へ進み、マス $i$ に着く方法の数を $\mathrm{dp}[i]$ とする（0-indexed、$1 \le L \le R$）。最後の 1 歩で場合分けすると、遷移は次の式になる。

$$
\mathrm{dp}[0] = 1, \qquad \mathrm{dp}[i] = \sum_{j = i - R}^{i - L} \mathrm{dp}[j] \quad (\text{添字が負の項は } 0)
$$

この式のまま和を取ると、1 マスに $R - L + 1$ 回の足し算がかかり、全体で $O(N(R - L))$ になる。$N$ と $R - L$ がどちらも $2 \times 10^5$ なら $4 \times 10^{10}$ 回で間に合わない。

**貰う形と累積和**。右辺は $\mathrm{dp}$ の連続した範囲、閉区間 $[i - R, i - L]$ の和である。$S[k] = \mathrm{dp}[0] + \dots + \mathrm{dp}[k - 1]$（$S[0] = 0$）を持てば、[半開区間](../guide/glossary.md#half-open-interval) $[l, r)$ の和は $S[r] - S[l]$ なので、閉区間 $[i - R, i - L]$ は半開区間 $[i - R, i - L + 1)$ に直して次のように 1 回で取れる。

$$
\mathrm{dp}[i] = S[i - L + 1] - S[\max(0, i - R)]
$$

次の図は $L = 2$、$R = 4$ で $\mathrm{dp}[7]$ を求める様子である。$S[k]$ は「境界 $k$ より左の和」なので、dp の各マスの境目の下に並べると、区間の和が両端の境目の値の差になることが見える。

![歩幅 2〜4 で dp[7] を求める図。dp は 1, 0, 1, 1, 2, 2, 4 と並び、遷移元の dp[3]〜dp[5] の和 5 は、その下に並べた累積和の S[6] = 7 から S[3] = 2 を引いた値に等しい](../img/dp-prefix-sum/pull-prefix.svg)

図の要点は、遷移元の区間がどれだけ長くても、読むのは $S$ の 2 か所だけということである。

この DP は $\mathrm{dp}$ と $S$ を同時に伸ばしていく。マス $i$ の値を求めるときに要るのは $S[i - L + 1]$ までで、$L \ge 1$ なら $S[i]$ までに収まる。だから次の順で回せば、使う値はすべて計算済みになる。

1. $\mathrm{dp}[i]$ を $S$ の差で求める（$i = 0$ は初期値の 1）
2. $S[i + 1] = S[i] + \mathrm{dp}[i]$ で累積和を 1 つ伸ばす

```cpp
--8<-- "dp-prefix-sum/pull.cpp:core"
```

完全なプログラム：[`pull.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/dp-prefix-sum/pull.cpp)（GitHub）
{ .kp-code-src }

**配る形といもす法**。同じ DP を配る形で書くと、確定した $\mathrm{dp}[i]$ を閉区間 $[i + L, i + R]$ のすべてのマスへ足すことになる。これも 1 回に $R - L + 1$ 回かかる。範囲への同じ値の足し込みは、差分の配列 $D$（コードの `diff`）に「$D[i + L] \mathrel{+}= \mathrm{dp}[i]$、$D[i + R + 1] \mathrel{-}= \mathrm{dp}[i]$」と 2 か所書けば済む。$D$ を左から累積した値（コードの `cur`）が、そのマスに配られた合計である。

配る先はいつも自分より右なので、マス $i$ に配られる値は、$i$ を見る時点ですべて書き込み済みである。したがって、累積を最後にまとめて取る必要はない。左から進みながら $D[i]$ を足し込んだ値が、そのまま $\mathrm{dp}[i]$ になる。

```cpp
--8<-- "dp-prefix-sum/push.cpp:core"
```

完全なプログラム：[`push.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/dp-prefix-sum/push.cpp)（GitHub）
{ .kp-code-src }

**なぜ正しいか**。どちらの形も、素直な DP と同じ値を足している。累積和は「区間の和」を、差分は「区間への同じ値の足し込み」を、それぞれ端の 2 か所の操作で表しただけで、足し合わせる項の集合は変わらない。素直な DP が正しければ、高速化した DP も正しい。

**計算量**。各マスで $S$ を 2 か所読む（または $D$ に 2 か所書く）だけなので、1 マス $O(1)$、全体で $O(N)$ になる。一般に、遷移元（遷移先）が $c$ 個の区間に分かれるなら、1 つの状態あたり $O(c)$ である。

| 遷移の形 | 道具 | 1 回の操作 |
| --- | --- | --- |
| 遷移元が連続した範囲（貰う形） | 前の値の累積和 $S$ | $S[r] - S[l]$ を読む |
| 遷移先が連続した範囲（配る形） | 差分 $D$（いもす法） | 始点に $+v$、終点の次に $-v$ |

??? question "確認問題：いもす法の累積はいつ取るか"
    配る形のいもす法で、差分 $D$ を左から累積するのは「すべての $i$ を配り終えてから」でなければならないか。

    ??? success "答え"
        この DP ではその必要はない。マス $j$ への書き込みはすべて $j$ より左のマスから来るので、左から進んで $j$ に着いた時点で $D[0] + \dots + D[j]$ は確定している。逆に、遷移先が自分より左にもある（向きが混ざる）なら、途中で読んだ累積は未確定なので、段を分けて配り終えてから累積する。

## 同じ段の累積和（上限つきの配り方） {#same-row}

$N$ 人に $K$ 個の飴を、$i$ 番目の人には 0〜$a_i$ 個ずつ、余さず配る方法の数を数える。「$\mathrm{dp}[i][j]$ ＝ 先頭 $i$ 人に合計 $j$ 個を配る方法の数」とし、$i$ 番目の人（0-indexed）に $c$ 個配ると考える。

$$
\mathrm{dp}[0][0] = 1, \qquad \mathrm{dp}[i + 1][j] = \sum_{c = 0}^{\min(a_i, j)} \mathrm{dp}[i][j - c] = \sum_{k = \max(0, j - a_i)}^{j} \mathrm{dp}[i][k]
$$

答えは $\mathrm{dp}[N][K]$ である。状態は $(N + 1)(K + 1)$ 個で、各遷移が最大 $K + 1$ 項の和なので、素直に書くと $O(NK^2)$ になる。$N = 100$、$K = 10^5$ なら $10^{12}$ 回で間に合わない。

右辺は、1 つ前の段 $\mathrm{dp}[i][\cdot]$ の中の、$j$ 方向に連続した範囲の和である。そこで段ごとに、その段の中で $j$ 方向の累積和 $S_i[k] = \mathrm{dp}[i][0] + \dots + \mathrm{dp}[i][k - 1]$ を作る。

$$
\mathrm{dp}[i + 1][j] = S_i[j + 1] - S_i[\max(0, j - a_i)]
$$

段ごとの手順は次のとおりで、1 段に $O(K)$、全体で $O(NK)$ になる。

1. 前の段 $\mathrm{dp}[i][\cdot]$ から $S_i$ を $0$〜$K + 1$ まで作り切る
2. 各 $j$ について、新しい段の値を $S_i$ の差で求める

手順 1 を先に終えておけば、手順 2 で同じ配列 $\mathrm{dp}$ を上書きしてよい。新しい値は $S_i$ からしか読まず、古い $\mathrm{dp}$ はもう読まないからである。

```cpp
--8<-- "dp-prefix-sum/candies.cpp:core"
```

完全なプログラム：[`candies.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/dp-prefix-sum/candies.cpp)（GitHub）
{ .kp-code-src }

例として $a = (1, 2, 3)$、$K = 4$ なら、段は $\mathrm{dp}[1] = (1, 1, 0, 0, 0)$、$\mathrm{dp}[2] = (1, 2, 2, 1, 0)$ と進む。最後は $\mathrm{dp}[3][4] = \mathrm{dp}[2][1] + \dots + \mathrm{dp}[2][4] = 2 + 2 + 1 + 0 = 5$ で、$S_2 = (0, 1, 3, 5, 6, 6)$ から $S_2[5] - S_2[1] = 5$ と同じ値が出る。

順列の数え上げで相対順位を状態にする DP（[挿入 DP](../dp/insertion-dp.md#prefix-sum)）も、遷移元が前の段の $j$ 方向の連続した範囲の和になる点で、上限つきの配り方と同じ形である。

**1 次元で同じ配列から貰うなら、累積和の代わりに 1 つの変数でもよい**。$\mathrm{dp}[v]$ が同じ配列の直前の範囲の和になる DP では、範囲の和を 1 つの変数で持ち、$v$ を 1 つ進めるたびに更新してもよい。

- 窓が一定の幅なら（「各桁が 1〜9 で桁の和が $K$」の直前 9 項など）、新しく入る項を足して出ていく項を引く
- 遷移元が接頭辞なら（「各項が 3 以上の数列」の $[0, v - 3]$ など）、出ていく項はなく、入る項を足すだけでよい

隣り合う式の差を取って $\mathrm{dp}[v] = \mathrm{dp}[v - 1] + (\text{入る項}) - (\text{出る項})$ と書き直すのも同じことである。区間の端が状態ごとに不規則に動くなら、累積和の方が書き間違えにくい。

## 区間の和集合・方向ごとの累積（縦・横・斜め） {#directional}

遷移元が 1 つの区間でなくても、いくつかの連続した範囲に分かれるなら、範囲ごとに累積和の差を取って足せばよい。

- **区間の和集合**：歩幅の集合が $K$ 個の重ならない区間 $[l_t, r_t]$ の和集合なら、$\mathrm{dp}[i]$ は区間ごとの差 $S[i - l_t + 1] - S[\max(0, i - r_t)]$ の合計で、1 マス $O(K)$ になる（[例題の ABC179 D](#abc179_d)）。区間が重なると、重なった歩幅を 2 回数えてしまう
- **補集合の範囲**：「隣り合う項の差の絶対値が $K$ 以上」のように、遷移元が「ある範囲の外側」なら、前の段の全体の和から内側の範囲の和を引く。外側は左右 2 つの区間になるので、2 つの差を足しても同じである
- **方向ごとの累積**：グリッドで「右・下・右下のどれかへ、壁の手前まで何マスでも進める」とき、マス $(i, j)$ の遷移元は、左・上・左上の各方向に壁まで続く線分である。方向ごとに別の累積を持ち、たとえば横方向は $X[i][j] = X[i][j - 1] + \mathrm{dp}[i][j - 1]$ とし、壁のマスでは 0 に戻す。$\mathrm{dp}[i][j]$ は 3 方向の累積の和で、1 マス $O(1)$ になる（[グリッド DP](../dp/dp-grid.md)）

方向ごとの累積で壁のマスを 0 に戻すのは、累積を「差を取る」代わりに「途中で打ち切る」ことで区間の左端を表しているからである。左端が壁で決まるので、差を取る必要がない。

斜めの方向も同じように扱える。2 次元の表の遷移元が斜めの線分になるなら、その向きに沿った累積和を作り、線分の両端の差で取る。$a - b$ が一定の向きなら $T[a][b] = T[a - 1][b - 1] + \mathrm{dp}[a][b]$、$a + b$ が一定の向きなら $U[a][b] = U[a - 1][b + 1] + \mathrm{dp}[a][b]$ である。遷移元が向きの違う何本かの線分に分かれるなら、向きごとに累積を作って足す（[力試しの ABC265 F](#challenge)）。

## 遷移元が接頭辞なら累積 min・累積 max でもよい {#prefix-min}

最適化の DP で $\mathrm{dp}[i + 1][j] = c_j + \min_{k \ge j} \mathrm{dp}[i][k]$ のように、遷移元が前の段の接尾辞（または接頭辞）全体なら、前の段の後ろからの累積 min を作れば 1 回 $O(1)$ で取れる。

$$
M[k] = \min(\mathrm{dp}[i][k], M[k + 1]), \qquad \mathrm{dp}[i + 1][j] = c_j + M[j]
$$

たとえばグリッドの各行を「左から $j$ マスを白、残りを黒」にそろえ、下の行ほど白が少なくなるようにする最小の塗り替え数なら、「$\mathrm{dp}[i][j]$ ＝ $i$ 行目の白を $j$ 個にしたときの、そこまでの最小コスト」とする。上の行の白の個数 $k$ は $k \ge j$ を満たせばよいので、遷移元は接尾辞になる。

min と max に使えるのは、範囲が端から始まるときだけである。和は $S[r] - S[l]$ のように引き算で途中から始まる範囲も取れるが、min には引き算がない。$\min(\mathrm{dp}[l..r))$ を 2 つの累積 min から作ることはできないので、任意の範囲の min なら[セグメント木](../dp/dp-segment-tree.md#values-on-segment-tree)を、範囲が一方向に動くなら[スライド最小値](../dp/dp-segment-tree.md#dp-sliding-window)を使う。

??? question "確認問題：累積 min で取れない範囲"
    $\mathrm{dp}[i] = c_i + \min_{i - K \le j < i} \mathrm{dp}[j]$ を累積 min だけで $O(1)$ にできるか。

    ??? success "答え"
        できない。範囲 $[i - K, i)$ は左端も動くので接頭辞ではなく、累積 min $\min(\mathrm{dp}[0..i))$ から $[0, i - K)$ の分を取り除く方法がない。範囲は右へ単調に動くので、スライド最小値（両端キュー）で 1 回ならし $O(1)$、セグメント木なら $O(\log N)$ で取る（[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md#dp-sliding-window)）。

## 余りごとの累積 {#by-remainder}

遷移元が添字の連続した範囲ではなく、「ある値の余りが等しい添字」の集まりになる DP では、余りごとに別々の累積を持つ。

**余りが一致する遷移元**。数列を区間に区切り、$k$ 番目の区間の和が $k$ で割り切れるようにする数え上げを考える。$A$ の累積和を $P$ とし、「$\mathrm{dp}[i][k]$ ＝ 先頭 $i$ 項を $k$ 個の区間に区切る方法の数」とする。最後の区間を $(t, i]$ とすると、条件は $P_i - P_t \equiv 0 \pmod{k}$、すなわち $P_t \equiv P_i \pmod{k}$ である。

$$
\mathrm{dp}[i][k] = \sum_{t < i,\ P_t \equiv P_i \ (\mathrm{mod}\ k)} \mathrm{dp}[t][k - 1]
$$

そこで $\mathrm{acc}[k][r]$ ＝「これまでの $t$ で $P_t \bmod k = r$ のものについての $\mathrm{dp}[t][k - 1]$ の和」を持つ。$\mathrm{dp}[i][k] = \mathrm{acc}[k][P_i \bmod k]$ と $O(1)$ で読み、$i$ の値がそろったら各 $k$ について $\mathrm{acc}[k][P_i \bmod k] \mathrel{+}= \mathrm{dp}[i][k - 1]$ と足し込む。区切りの数 $k$ は最大 $N$ で、余りは $k$ 通りある。したがって $\mathrm{acc}$ の大きさと全体の時間はどちらも $O(N^2)$ である。この節の内容は[区間分割 DP](../dp/dp-sequence-partition.md) と合わせて読むとよい。

**一定の歩幅で飛ぶ遷移元**。$\mathrm{dp}[i] = \sum_{t \ge 1} \mathrm{dp}[i - t \cdot d]$ のように、遷移元が $d$ 飛びに並ぶなら、$d$ 飛びの累積 $C[i] = \mathrm{dp}[i] + C[i - d]$ を作る。$C$ は $i \bmod d$ ごとに独立した累積和である。上限 $u$ 回までなら $C[i - d] - C[i - (u + 1)d]$ のように差で取れる。個数制限付きのナップサックの数え上げ（前の段から重さ $w$ の品物を 0〜$u$ 個足す遷移）も、前の段の $w$ 飛びの累積を作れば同じように $O(\text{状態数})$ になる。

どちらも「足し込むときと読むときで、同じ余りの箱を使う」ことが正しさの要点である。読む前に今の $i$ 自身を箱に入れてしまうと、長さ 0 の区間を数えるなどの誤りになる。

## 2 次元の累積 {#two-dimensional}

この節は [2 次元累積和](../basics/prefix-sum-2d.md)を前提にする。遷移元が「左上の長方形全体」になる DP は、表そのものの 2 次元累積和で 1 回 $O(1)$ にする。

$$
\mathrm{dp}[i][j] = \sum_{i' < i,\ j' < j} \mathrm{dp}[i'][j']
$$

2 つの列 $X$・$Y$ から、取り出す位置の組を変えて同じ値の列になる部分列の組を数える問題が典型である。「$\mathrm{dp}[i][j]$ ＝ 最後に $X_i$ と $Y_j$ を対応させた組の数」とすると、直前の対応は $i' < i$ かつ $j' < j$ の任意の位置なので、遷移元は左上の長方形になる。$W[i][j]$ を $\mathrm{dp}$ の左上 $[0, i) \times [0, j)$ の和として

$$
W[i + 1][j + 1] = W[i][j + 1] + W[i + 1][j] - W[i][j] + \mathrm{dp}[i][j]
$$

で表と同時に伸ばせば、$\mathrm{dp}[i][j] = [X_i = Y_j] \cdot (1 + W[i][j])$ と読める（1 は空の列から始める分。$X_i \ne Y_j$ の位置は対応させられないので 0）。$X$ の長さを $N$、$Y$ の長さを $M$ とすると、答えは空の組を足した $1 + W[N][M]$ で、状態 $O(NM)$ に対して全体も $O(NM)$ になる。

遷移先が長方形になる配る形なら、2 次元のいもす法（四隅に $\pm v$、横と縦に累積）を使う（[2 次元いもす法](../basics/imos.md#imos-2d)）。

## 落とし穴 {#pitfalls}

**累積和を更新しながら同じ段で使う**。上限つきの配り方で、$\mathrm{dp}$ を上書きしながら「$S$ も同時に作る」と、$S$ に新しい段の値が混ざる。前の段の累積和は、新しい段を書き始める前に作り切る。1 次元で同じ配列から貰う DP（[貰う形と累積和](#pull-and-push)）では逆に、$\mathrm{dp}[i]$ を求めてから $S[i + 1]$ を伸ばす。$S[i + 1]$ を先に伸ばそうとすると、まだ 0 の $\mathrm{dp}[i]$ を足してしまう。

**区間の端のずれ**。閉区間 $[l, r]$ の和は $S[r + 1] - S[l]$ である。$S[r] - S[l]$ と書くと右端の項が抜け、$S[r + 1] - S[l - 1]$ と書くと 1 つ多い。式を半開区間 $[l, r + 1)$ に直してから $S$ の添字に写すと間違えにくい。端が配列の外に出るときは、左端を $\max(0, \cdot)$、右端を $\min(\text{幅}, \cdot)$ で切り詰め、切り詰めた後に左端 $\ge$ 右端なら空区間として 0 にする。

**範囲の幅が 0 や負になる特別な値**。「差の絶対値が $K$ 以上」で $K = 0$ なら、引くべき内側の範囲 $[j - K + 1, j + K - 1]$ が空になる。そのまま式に入れると左端が右端より大きい区間になり、差が負の値になって答えが壊れる。空区間の判定を入れるか、$K = 0$ を別に扱う。

**mod の差が負になる**。$S[r] - S[l]$ は、どちらも余りを取った値なので、本当の和が正でも負になりうる。C++ の `%` は、割られる数が負なら 0 以下の余りを返す（符号は割られる数に従う）ので、`(s[r] - s[l] + MOD) % MOD` のように法を足してから余りを取る。ACL の modint なら引き算の結果は自動で 0 以上になる。最小値・最大値の比較と違い、mod の値どうしは大小を比べても意味がないことにも注意する。

**いもす法の終点の次が配列の外**。配る先の終点 $i + R$ が配列の最後なら、$-v$ を書く位置 $i + R + 1$ は配列の外になる。差分の配列を 1 つ長く取って[番兵](../guide/glossary.md#sentinel)にするか、終点の次が外なら書かない。

## 例題 {#examples}

### ABC179 D. Leaping Tak {#abc179_d}

<div class="kp-problems" data-role="example" markdown>

- [ABC179 D. Leaping Tak](https://atcoder.jp/contests/abc179/tasks/abc179_d)（diff 1251）：いくつかの区間の和集合に含まれる歩幅で、マス 1 からマス N まで進む方法の数を求める。

</div>

最後の 1 歩で場合分けすると、マス $i$ の遷移元は「$i$ から各区間の歩幅を引いた範囲」になり、区間ごとに連続した範囲である。歩幅の候補をすべて試すと $O(N^2)$ だが、区間の数は高々 10 個なので、区間ごとに累積和の差を取れば $O(NK)$ で済む。

??? note "解法の詳細"
    - 0-indexed でマス $0$ から $N - 1$ へ進むとし、「$\mathrm{dp}[i]$ ＝ マス $i$ に着く方法の数」、$\mathrm{dp}[0] = 1$ とする。答えは $\mathrm{dp}[N - 1]$
    - 区間 $[l_t, r_t]$ からの寄与は、遷移元が閉区間 $[i - r_t, i - l_t]$ なので $S[i - l_t + 1] - S[\max(0, i - r_t)]$。左端が右端以上なら 0
    - $i$ の小さい順に、$\mathrm{dp}[i]$ を求めてから $S[i + 1]$ を伸ばす。区間は重ならないので、寄与をそのまま足してよい
    - 差を取るたびに法を足してから余りを取る。コードは[貰う形と累積和](#pull-and-push)のものと同じ形で、配る形のいもす法でも解ける

### EDPC M. Candies {#dp_m}

<div class="kp-problems" data-role="example" markdown>

- [EDPC M. Candies](https://atcoder.jp/contests/dp/tasks/dp_m)（diff なし）：N 人の子どもに K 個の飴を、i 番目の子には 0〜a_i 個ずつ、余さず配る方法の数を求める。

</div>

$i$ 番目の子に配る個数で場合分けすると、遷移元は前の段の連続した範囲になる。$N \le 100$、$K \le 10^5$ なので、$O(NK^2)$ は間に合わず $O(NK)$ にしたい。前の段の累積和を作れば、各遷移が 2 つの値の差になる。

??? note "解法の詳細"
    - 「$\mathrm{dp}[i][j]$ ＝ 先頭 $i$ 人に合計 $j$ 個を配る方法の数」、$\mathrm{dp}[0][0] = 1$。答えは $\mathrm{dp}[N][K]$
    - 遷移は $\mathrm{dp}[i + 1][j] = S_i[j + 1] - S_i[\max(0, j - a_i)]$（$S_i$ は前の段の累積和）
    - 段ごとに、先に $S_i$ を作り切ってから新しい段を書く。こうすれば 1 本の配列を上書きしてよい
    - 法は $10^9 + 7$。差には法を足してから余りを取る。コードは[同じ段の累積和](#same-row)のもの

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC178 D. Redistribution](https://atcoder.jp/contests/abc178/tasks/abc178_d)（diff 875）：各項が 3 以上の整数で、総和が S になる数列の個数を求める。
- [ABC253 E. Distance Sequence](https://atcoder.jp/contests/abc253/tasks/abc253_e)（diff 1073）：長さ N・各項が 1〜M で、隣り合う項の差の絶対値が K 以上の数列の個数を求める。
- [ABC183 E. Queen on Grid](https://atcoder.jp/contests/abc183/tasks/abc183_e)（diff 1288）：壁のあるグリッドで、右・下・右下のどれかへ壁の手前まで何マスでも進めるとき、左上から右下へ行く方法の数を求める。
- [典型90 042. Multiple of 9（★4）](https://atcoder.jp/contests/typical90/tasks/typical90_ap)（diff なし）：各桁が 1〜9 で桁の和が K になる正の整数のうち、9 の倍数の個数を求める。
- [ABC442 F. Diagonal Separation 2](https://atcoder.jp/contests/abc442/tasks/abc442_f)（diff 1295）：グリッドのマスを塗り替えて、各行の左側に並ぶ白の個数が下の行ほど減る形にするときの、塗り替えの最小数を求める。
- [TDPC F. 準急](https://atcoder.jp/contests/tdpc/tasks/tdpc_semiexp)（diff なし）：1 番目と N 番目の駅には止まり、K 駅以上連続しては止まらない停車駅の選び方の数を求める。
- [ABC207 E. Mod i](https://atcoder.jp/contests/abc207/tasks/abc207_e)（diff 1820）：数列をいくつかの区間に区切り、K 番目の区間の和が K で割り切れるようにする方法の数を求める。

</div>

??? note "練習の方針"
    - **ABC178 D**：「$\mathrm{dp}[v]$ ＝ 総和が $v$ の数列の数」、$\mathrm{dp}[0] = 1$。最後の項で場合分けすると遷移元は $[0, v - 3]$ の接頭辞なので、$v \ge 3$ で $\mathrm{dp}[v] = S[v - 2]$、$v = 1, 2$ は 0。隣の式との差を取って $\mathrm{dp}[v] = \mathrm{dp}[v - 1] + \mathrm{dp}[v - 3]$ としてもよい
    - **ABC253 E**：「$\mathrm{dp}[i][j]$ ＝ 長さ $i$ で最後が $j$」。遷移元は前の段の、$j$ から $K$ 以上離れた値で、内側の範囲の外の 2 区間である。前の段の全体から内側の範囲の和を引く。$K = 0$ では内側が空になるので別に扱う
    - **ABC183 E**：遷移元はそのマスから左・上・左上へ壁に当たるまでの 3 本の線分である。「$X[i][j]$ ＝ 行の左から $(i, j)$ までの $\mathrm{dp}$ の和（壁で 0 に戻す）」を持つ。列・斜めの同じ和 $Y$・$Z$ も持てば、$\mathrm{dp}[i][j] = X[i][j-1] + Y[i-1][j] + Z[i-1][j-1]$ で $O(1)$ になる。全体 $O(HW)$
    - **典型90 042**：9 の倍数は桁の和が 9 の倍数なので、$K$ が 9 の倍数でなければ 0。「$\mathrm{dp}[s]$ ＝ 桁の和が $s$ の数の個数」は最後の桁で場合分けして直前 9 項の和になり、窓の和か累積和で $O(K)$
    - **ABC442 F**：「$\mathrm{dp}[i][j]$ ＝ $i$ 行目の白を左から $j$ 個にしたときの最小の塗り替え数」。行の中のコストは左右からの累積和で全 $j$ を $O(N)$ で求め、上の行は $k \ge j$ の最小なので後ろからの累積 min で取る。全体 $O(N^2)$
    - **TDPC F**：最後に通過した駅で場合分けすると、遷移元は直前の一定の幅の窓になり、窓の和を累積和で取れる。止まる・止まらないの 2 通りから「直前がすべて停車した場合」を引く $\mathrm{dp}[i + 1] = 2\,\mathrm{dp}[i] - \mathrm{dp}[i - K]$ の形に整理してもよい。最後の駅に止まる条件は余事象で処理する
    - **ABC207 E**：区切った区間の数 $k$ を状態に足し、条件 $P_t \equiv P_i \pmod{k}$ を余りごとの箱 $\mathrm{acc}[k][r]$ で取る（[余りごとの累積](#by-remainder)）。全体 $O(N^2)$

## 力試し {#challenge}

<div class="kp-problems" data-role="challenge" markdown>

- [ABC265 F. Manhattan Cafe](https://atcoder.jp/contests/abc265/tasks/abc265_f)（diff 2290）：N 次元の格子点で、与えられた 2 点からのマンハッタン距離がともに D 以下の点の個数を求める。

</div>

??? note "力試しの方針"
    - **ABC265 F**：座標ごとに 2 点の座標の差だけが効くように平行移動・反転し、「$\mathrm{dp}[i][a][b]$ ＝ $i$ 座標目まで決めて、2 点からの距離の和がそれぞれ $a$・$b$ になる数」とする。2 点の座標の差を $\delta$ とすると、新しい座標の値を 2 点の間に取れば $(a, b)$ の増え方は $(x, \delta - x)$ で $a + b$ 一定の向きに、外側に取れば $(x, x + \delta)$・$(x + \delta, x)$ で 2 本の対角線の向きに動く。遷移元は向きの違う斜めの線分 3 本になるので、向きごとに累積和を作って差で取ると、$O(ND^3)$ が $O(ND^2)$ になる

## 確認問題 {#quiz}

??? question "確認問題：どの形なら累積和で速くなるか"
    次の遷移のうち、累積和（または累積 min）で 1 回 $O(1)$ にできるものはどれか。

    1. $\mathrm{dp}[i][j] = \sum_{k \le j} \mathrm{dp}[i - 1][k] \cdot w_k$
    2. $\mathrm{dp}[i][j] = \max_{j - 3 \le k \le j + 3} \mathrm{dp}[i - 1][k]$
    3. $\mathrm{dp}[i][j] = \sum_{k \ne j} \mathrm{dp}[i - 1][k]$

    ??? success "答え"
        1 と 3 はできる。1 は $\mathrm{dp}[i - 1][k] \cdot w_k$ を 1 つの列と見て累積和を取ればよい（$w_k$ は $k$ だけで決まるので前に計算できる）。3 は全体の和から $\mathrm{dp}[i - 1][j]$ を引けばよい。2 は和ではなく max で、範囲が接頭辞でも接尾辞でもないので累積 max では取れない。幅が 7 と小さければそのまま 7 項を見ればよく、幅が大きければスライド最小値（最大値）かセグメント木を使う。

## 使い分け {#comparison}

- 遷移元・遷移先が連続した範囲の**和**なら累積和・いもす法、端から始まる範囲の **min・max** なら累積 min・max を使う
- 任意の範囲の min・max、または値の更新と範囲の取得が入り混じるなら[セグメント木・スライド最小値による DP の高速化](../dp/dp-segment-tree.md)を使う
- 前の段をほぼそのまま写し、一部の範囲にだけ一律に足すなら、表を作り直さない[インライン DP](../dp/inline-dp.md) を考える
- どの道具を選ぶかは、貰う形の式を書いて右辺の形を見て決める（[DP の高速化の全体像](../dp/dp-speedup-overview.md#read-the-recurrence)）

## 参考 {#references}

- [Series_205「Educational DP Contest (EDPC) K ~ O 問題 解説」](https://qiita.com/Series_205/items/618b6ad1a22e7401a606)：例題 EDPC M の状態・遷移と、前の段の累積和・負の mod の処理
- [drken「AtCoder ABC 179 D - Leaping Tak (1Q, 水色, 400 点)」](https://drken1215.hatenablog.com/entry/2020/09/20/081800)：例題 ABC179 D の区間ごとの累積和の差
- [drken「AtCoder ABC 178 D - Redistribution (2Q, 緑色, 400 点)」](https://drken1215.hatenablog.com/entry/2020/10/11/211000)：練習の方針（接頭辞の和と、差を取った漸化式）
- [Kazun「AtCoder Beginner Contest 253 E問題 Distance Sequence」](https://kazun-kyopro.hatenablog.com/entry/ABC/253/E)：練習の方針（全体から内側の範囲を引くことと $K = 0$ の扱い）
- [E869120「kyopro_educational_90 042 の解説（画像）」](https://github.com/E869120/kyopro_educational_90/blob/main/editorial/042.jpg)：練習の方針（9 の倍数と桁の和、直前 9 項の和）
- [ikatakos「JPRSプログラミングコンテスト2026#1（AtCoder Beginner Contest 442）E,F,G問題メモ」](https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0124_abc442)：練習の方針（後ろからの累積 min による遷移。解説の部分だけを参照）
- [sigma425「Typical DP Contest (TDPC)」](https://sigma425.hatenablog.com/entry/2016/08/02/214547)：練習の方針（準急の漸化式と余事象）
- [drken「AtCoder ABC 207 E - Mod i (2D, 青色, 500 点)」](https://drken1215.hatenablog.com/entry/2024/05/21/013749)：余りごとの累積の持ち方
- [drken「AtCoder ABC 265 F - Manhattan Cafe (黄色, 500 点)」](https://drken1215.hatenablog.com/entry/2023/07/15/021500)：力試しの方針（斜め方向の累積和）
- [drken「AtCoder ABC 130 E - Common Subsequence (1D, 青色, 500 点)」](https://drken1215.hatenablog.com/entry/2019/06/21/230200)：2 次元の累積で遷移をまとめる型
- [drken「AtCoder ABC 183 E - Queen on Grid (1Q, 水色, 500 点)」](https://drken1215.hatenablog.com/entry/2020/11/16/204900)：方向ごとの累積の型
