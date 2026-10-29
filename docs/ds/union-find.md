---
id: union-find
title: Union-Find
aliases: [UF, DSU, Disjoint Set Union, disjoint set, 素集合データ構造, 経路圧縮, union by size]
type: technique
field: ds
chapter: Union-Find
order: 100
level: 基礎
kind: [データ構造, 連結性・全域木]
prerequisites: [graph-basics]
related: [connected-components, union-find-connectivity, minimum-spanning-tree, union-find-applications, weighted-union-find, small-to-large, acl-reading#components]
summary: 要素を互いに素なグループに分けて持ち、2 つのグループの併合と「同じグループか」の判定を、union by size と経路圧縮でならし O(α(N)) で行う。グループの大きさや個数も数えられる。
complexity: 構築 O(N)、併合・判定・大きさの取得はならし O(α(N))（union by size だけなら 1 回ごとに最悪 O(log N)）
signs:
  - {type: phrase, text: 辺を追加していきながら、2 頂点が同じグループか・グループの大きさを答える}
  - {type: phrase, text: グループを合併する操作と、グループについての質問が交互に来る}
  - {type: phrase, text: 連結成分の個数・最大の連結成分の大きさ}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で辺の追加と質問が混ざる'}
acl: [dsu]
verify: [unionfind]
frequency: A
frequency_evidence: recent 1（abc451_e）・前提として 18 ページに届く（直接 9）・古い ABC 5 問
sections:
  - {title: 何ができるか（併合と判定。分割・削除はできない）, anchor: what-it-does}
  - {title: 保つ性質（各グループは根付き木で、根が代表元。par は根なら −(大きさ)）, anchor: invariants}
  - {title: 各操作の手順（find は根までたどって経路圧縮、merge は根どうしを小さい方から大きい方へつなぐ）, anchor: operations}
  - {title: なぜ速いか（union by size だけで深さ log N、経路圧縮と合わせてならし O(α(N))）, anchor: complexity}
  - {title: 境界（同じグループどうしの併合・自己ループと多重辺・成分数・大きさの積のあふれ）, anchor: boundaries}
  - {title: 根に大きさ・辺数を持たせる（ほかの情報を持たせる型は Union-Find の応用）, anchor: size-and-edges}
stage: reviewed
updated: 2026-10-29
---

!!! abstract "要点"
    - **何ができるか**：要素を互いに素なグループに分けて持ち、2 つのグループの併合と「同じグループか」の判定を、union by size と経路圧縮でならし $O(\alpha(N))$ で行う。グループの大きさや個数も数えられる。
    - **いつ使うか**：
        - 辺を追加していきながら、2 頂点が同じグループか・グループの大きさを答える
        - グループを合併する操作と、グループについての質問が交互に来る
        - 連結成分の個数・最大の連結成分の大きさ
        - $N, Q \le 2 \times 10^5$ で辺の追加と質問が混ざる
    - **計算量**：構築 $O(N)$、併合・判定・大きさの取得はならし $O(\alpha(N))$。$\alpha$ は逆アッカーマン関数で、実用上は 4 以下の定数と見てよい。union by size だけなら 1 回ごとに最悪 $O(\log N)$
    - **前提**：[グラフの表現と用語](../graph/graph-basics.md)

<!-- textlint-disable -->
別名：UF・DSU・Disjoint Set Union・disjoint set・素集合データ構造・経路圧縮・union by size
<!-- textlint-enable -->

Union-Find は、グループを根付き木で表し、根を代表として比べることで「2 つのグループをまとめる」と「同じグループか」を速く処理するデータ構造である。無向グラフに辺を 1 本ずつ足しながら、連結かどうかや連結成分の大きさを答えるのが典型的な使い方になる。

## 何ができるか（併合と判定。分割・削除はできない） {#what-it-does}

Union-Find は、要素 $0, 1, \dots, N-1$（0-indexed）を、どの 2 つも共通の要素を持たないグループに分けて持つ。最初はどの要素も 1 つだけのグループにいる。行える操作は次のとおりである。

- **併合** $\mathrm{merge}(a, b)$：$a$ のグループと $b$ のグループを 1 つにまとめる
- **判定** $\mathrm{same}(a, b)$：$a$ と $b$ が同じグループかを答える
- **大きさ** $\mathrm{size}(a)$：$a$ のグループの要素数を答える

無向グラフで言えば、併合は辺 $(a, b)$ を足すこと、判定は 2 頂点が連結かを問うことにあたる。辺を足すたびに BFS で調べ直すと 1 回 $O(N + M)$ かかり、$Q = 2 \times 10^5$ 回の質問には間に合わない。Union-Find なら全体でほぼ $O(N + Q)$ で済む。

できないのは、グループを分けることと、要素や辺を取り除くことである。一度まとめたグループは元に戻せない。削除が来る問題の扱いは[使い分け](#comparison)の節で述べる。

## 保つ性質（各グループは根付き木で、根が代表元。par は根なら −(大きさ)） {#invariants}

Union-Find は、各グループを 1 本の根付き木として持つ。木の根をそのグループの[代表元](../guide/glossary.md#representative)と呼び、「同じグループか」は「根が同じか」で判定する。木の形は何でもよく、子から親への矢印だけを持てば足りる。

実装では、長さ $N$ の配列 $\mathrm{par}$ 1 本で次の性質を保つ。

- $\mathrm{par}[v] \ge 0$ なら、$v$ は根ではなく、$\mathrm{par}[v]$ が $v$ の親である
- $\mathrm{par}[v] < 0$ なら、$v$ は根で、$-\mathrm{par}[v]$ がそのグループの要素数である
- 親をたどると、どの要素からも有限回で自分のグループの根に着く（閉路はない）

最初はすべて $\mathrm{par}[v] = -1$（大きさ 1 の根）である。大きさは根にだけ持ち、根以外の要素は親の番号しか持たない点が大事である。大きさを別の配列 $\mathrm{sz}$ に持つ書き方でも、正しいのは根の値だけである。根でなくなった要素の $\mathrm{sz}$ は併合のあとで直されないので、大きさは必ず $\mathrm{find}$ で根を求めてから読む。

## 各操作の手順（find は根までたどって経路圧縮、merge は根どうしを小さい方から大きい方へつなぐ） {#operations}

すべての操作は、要素の根を求める $\mathrm{find}(v)$ を土台にする。

```text
find(v):
    par[v] < 0 なら v を返す（v は根）
    r = find(par[v])
    par[v] = r            # 経路圧縮：根に直接つなぎ直す
    r を返す

merge(a, b):
    x = find(a), y = find(b)
    x == y なら何もしない（もう同じグループ）
    -par[x] < -par[y] なら x と y を入れ替える（x を大きい方にする）
    par[x] += par[y]      # 大きさを足す（どちらも負の数）
    par[y] = x            # 小さい方の根を大きい方の根の下へ
```

$\mathrm{same}(a, b)$ は $\mathrm{find}(a) = \mathrm{find}(b)$ かで答える。$\mathrm{size}(a)$ は $-\mathrm{par}[\mathrm{find}(a)]$ である。次の図は、8 要素を併合したあとに $\mathrm{find}(7)$ を呼んだときの、経路圧縮の前と後である。

![上は根 0 の木で、7 から根まで 7 → 6 → 4 → 0 と 3 回たどる。下は find(7) のあとで、たどった 6 と 7 が根 0 を直接指す。par は [−8, 0, 0, 2, 0, 4, 0, 0] になる](../img/union-find/path-compression.svg)

$\mathrm{find}(7)$ は 7 → 6 → 4 → 0 とたどって根 0 を見つける。帰りがけに、通った 7 と 6 の親を根 0 に書き換える（4 はもともと根の子）。次に 7 や 6 の根を求めるときは、1 回たどるだけで済む。

下の動く図では、同じ 8 要素で併合を 1 回ずつ進める。根どうしがつながるたびに、下に入る根の $\mathrm{par}$ は親の番号に、残る根の $\mathrm{par}$ は新しい $-(\text{大きさ})$ に変わる。最後の $\mathrm{find}(7)$ で深さが縮むことも確かめられる。この順では、併合する 2 つの木がいつも同じ大きさになる。

<div class="kp-viz" data-viz="union-find" data-config='{"n": 8, "ops": [{"type": "merge", "a": 0, "b": 1}, {"type": "merge", "a": 2, "b": 3}, {"type": "merge", "a": 0, "b": 2}, {"type": "merge", "a": 4, "b": 5}, {"type": "merge", "a": 6, "b": 7}, {"type": "merge", "a": 4, "b": 6}, {"type": "merge", "a": 0, "b": 4}, {"type": "find", "x": 7}]}'></div>

大きさの同じ木どうしを併合するときは、どちらを根にしてもよい（図では $a$ 側の根を残している）。最後の併合の直前は、0 の木も 4 の木も大きさ 4 で深さ 2 である。併合すると深さは 3 になり、$\mathrm{find}(7)$ の経路圧縮で 7 と 6 が根の直下に上がる。

大きさの違う木をつなぐ様子は、次の図で確かめられる。6 要素で大きさ 4 の木を作り、そこへ大きさ 1 の木を 2 回つなぐ。$\mathrm{merge}(4, 3)$ では $b$ 側の根 0 の方が大きいので入れ替え、小さい方の根 4 を根 0 の下に入れる（その前の $\mathrm{find}(3)$ で経路圧縮も起きる）。

<div class="kp-viz" data-viz="union-find" data-config='{"n": 6, "ops": [{"type": "merge", "a": 0, "b": 1}, {"type": "merge", "a": 2, "b": 3}, {"type": "merge", "a": 0, "b": 2}, {"type": "merge", "a": 4, "b": 3}, {"type": "merge", "a": 5, "b": 1}]}'></div>

小さい方の根を大きい方の根の下に入れると、深さが 1 増えるのは小さい方の木の要素だけで、大きい方の木の要素の深さは変わらない。だから木全体の深さは増えにくい（[次の節](#complexity)）。

??? note "自作するとき：`UnionFind`（ACL の `dsu` に当たる）"
    `merge`・`same`・`size` の名前と 0-indexed の添字は、ACL の `dsu` にそろえた。ACL と違うのは次の 3 つである。

    - 根を求める関数は、本文の手順に合わせて `find` とした（ACL では `leader`）。
    - `merge` は併合したかどうかを `bool` で返す（ACL は新しい代表元を返す）。成分の数や閉路を作る辺を数えるときに使える。新しい根は、併合のあとで `find(a)` を呼んで求める。
    - 全グループの一覧の `groups()` と、添字の範囲を確かめる `assert` は省いた。

    ```cpp
    --8<-- "union-find/own-dsu.cpp:core"
    ```

    完全なプログラム：[`own-dsu.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/union-find/own-dsu.cpp)（GitHub）
    { .kp-code-src }

    試験では、併合に成功した回数から数えたグループの数と、根（$\mathrm{par}[v] < 0$ の要素）の数が一致することを確かめている。[練習問題](#practice)の PRACTICE2 A と、Library Checker の [Unionfind](https://judge.yosupo.jp/problem/unionfind) が確認に使える。名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。

!!! info "ACL では"
    `atcoder::dsu d(n);`。`d.merge(a, b)`（併合したあとの代表元を返す。もともと同じなら、その代表元）・`d.same(a, b)`・`d.leader(a)`・`d.size(a)` はどれもならし $O(\alpha(n))$、`d.groups()` は全グループの要素の一覧を $O(n)$ で返す（並び順は決まっていない）。中身は union by size と経路圧縮で、根に −(大きさ) を持つ。添字は 0-indexed。

    `d.merge` の返り値は自作の `merge`（併合したら `true`）と意味が違い、`if (d.merge(a, b))` は代表元が 0 かどうかを見るだけで、併合できたかの判定にならない。併合できたかは、先に `d.same(a, b)` で調べる（[境界の節](#boundaries)のコード）。

## なぜ速いか（union by size だけで深さ log N、経路圧縮と合わせてならし O(α(N))） {#complexity}

$\mathrm{find}$ の手間は、たどる深さで決まる。工夫なしにつなぐと、$0 \leftarrow 1 \leftarrow 2 \leftarrow \dots$ のような 1 本の鎖ができ、$\mathrm{find}$ が 1 回 $O(N)$ になる。2 つの工夫がこれを防ぐ。

**union by size**（小さい方を大きい方の下へつなぐ）だけで、どの木の深さも $\log_2 N$ 以下になる。ある要素 $v$ の深さが 1 増えるのは、$v$ を含む木が、それ以上の大きさの木の根の下へつながるときだけである。このとき $v$ を含む木の大きさは 2 倍以上になる。木の大きさは $N$ を超えないので、大きさの倍増は $\log_2 N$ 回までしか起きない。だから $\mathrm{find}$ の手間は 1 回ごとに最悪 $O(\log N)$ である。木の高さ（ランク）で比べる union by rank でも、同じ上限が成り立つ。

**経路圧縮**は、$\mathrm{find}$ でたどった要素をすべて根の直下に移す。これだけでも[ならし計算量](../guide/glossary.md#amortized-complexity)は $O(\log N)$ になる。両方を使うと、1 回あたりのならし計算量は $O(\alpha(N))$ になる（Tarjan による）。$\alpha$ は増え方が極めて遅い関数で、$N$ が $10^{80}$ 程度でも 4 以下である。

ならし計算量なので、1 回の $\mathrm{find}$ が $O(\log N)$ かかることはある。それでも $Q$ 回の操作の合計は $O(N + Q \, \alpha(N))$ に収まる。競技プログラミングでは、両方を入れておけば 1 回ほぼ定数と見てよい。

??? question "確認問題：工夫を片方だけにすると"
    (1) 経路圧縮だけを入れ、併合では大きさを見ずに `par[find(b)] = find(a)` とつないだ。答えは正しいか。速さはどうか。
    (2) 経路圧縮を入れず、union by size だけにした。$N = 2 \times 10^5$、$Q = 2 \times 10^5$ で間に合うか。

    ??? success "答え"
        (1) 答えは正しい。つなぎ方はどの根を代表にするかを変えるだけで、「同じ木にいるか」は変わらない。速さはならし $O(\log N)$ になり、間に合うことが多い。ただし一時的に深い鎖ができうるので、再帰の `find` が深くなる。
        (2) 間に合う。深さが $\log_2 N \approx 18$ 以下なので、1 回 $O(\log N)$、全体で約 $4 \times 10^6$ 回の手間である。経路圧縮を入れない形は、操作を取り消す [ロールバックできる Union-Find](../ds/rollback-union-find.md#no-path-compression) で使う。

## 境界（同じグループどうしの併合・自己ループと多重辺・成分数・大きさの積のあふれ） {#boundaries}

- **同じグループどうしの併合**：$\mathrm{find}(a) = \mathrm{find}(b)$ なら何もしない。ここで大きさを足すと、自分の大きさを 2 倍に数えてしまう。また $\mathrm{par}[y] = x$ で $x = y$ だと根が自分を指し、$\mathrm{par}$ の負の値（大きさ）が消える。以後の $\mathrm{find}(x)$ は自分を親としてたどり続けて止まらない（再帰ならスタックがあふれる）
- **自己ループと多重辺**：辺 $(v, v)$ や 2 本目の $(a, b)$ は、どちらも「すでに同じグループ」の併合になる。連結性は変わらないが、辺の本数を数える問題では数え漏らさないようにする（[次の節](#size-and-edges)）
- **連結成分の数**：最初は $N$ 個で、併合が成功するごとに 1 減る。だから「$N$ − 併合に成功した回数」である。辺の本数 $M$ を引くと、同じグループどうしの併合まで数えて誤る。最後にまとめて求めるなら、$\mathrm{par}[v] < 0$ の $v$（根）を数えてもよい
- **閉路を作る辺の数**：辺を順に見て、両端がすでに同じグループだった辺の数である。連結成分の数を $C$ とすると、これは $M - (N - C)$ に等しい
- **大きさの積のあふれ**：併合すると、$\mathrm{size}(a) \times \mathrm{size}(b)$ 組が新しく連結になる。この積は $N = 2 \times 10^5$ で最大 $10^{10}$ に達し、`int` では表せない。積と合計は `long long` で計算する。`d.size(a) * d.size(b)` は `int` どうしの積なので、足す前の掛け算であふれる。`(long long)d.size(a) * d.size(b)` のように、掛ける前に片方を `long long` へ変える（[整数のオーバーフロー](../cpp/cpp-integer-overflow.md)）

次のコードは ACL の `dsu` で、閉路を作る辺の数と連結成分の数を同時に数える。入力の頂点番号は 1-indexed なので、読んだらすぐに 1 を引く。

```cpp
--8<-- "union-find/acl-cycle.cpp:core"
```

完全なプログラム：[`acl-cycle.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/union-find/acl-cycle.cpp)（GitHub）
{ .kp-code-src }

## 根に大きさ・辺数を持たせる（ほかの情報を持たせる型は Union-Find の応用） {#size-and-edges}

グループごとの情報は、大きさと同じく根にだけ持ち、併合のときに合成する。大きさの次によく使うのは辺の本数で、連結成分が木か（辺数 ＝ 頂点数 − 1）、閉路をちょうど 1 つ持つか（辺数 ＝ 頂点数）を見分けられる。

辺数を $\mathrm{edges}$ という配列で根に持つなら、辺 $(a, b)$ を足すたびに次のようにする。

```text
x = find(a), y = find(b)
x == y なら edges[x] += 1        # 自己ループ・多重辺もここで数える
そうでなければ x と y を併合し、新しい根 r について
    edges[r] = edges[x] + edges[y] + 1
```

併合のあとで新しい根がどちらになるかは、大きさの比べ方で決まる。古い根の変数のまま書き込むと、根でない要素に書いて情報が消える。新しい根を受け取ってから書く。ACL では `merge` の返り値が新しい根である。自作の `merge`（[各操作の手順](#operations)のコード）は併合できたかの `bool` を返すので、併合のあとで $\mathrm{find}(a)$ を呼んで新しい根を求める。

辺の追加と質問が交互に来ないなら、もっと簡単に書ける。各辺の片方の端に 1 を数えておき、全部の併合が終わってから、各頂点の数を $\mathrm{find}(v)$ に足し込めばよい。併合の途中で根が変わっても関係がない。

最小値・和・上位 $K$ 個・値ごとの個数のように、ほかの情報を根に持たせる型や、併合の瞬間に組の数を数える型は [Union-Find の応用](../ds/union-find-applications.md)で扱う。

## 落とし穴 {#pitfalls}

**根を求めずにつなぐ**。`par[b] = a` のように要素どうしを直接つなぐと、$b$ が根でないとき、$b$ は元の木から切り離される。$b$ の元の仲間とのつながりが消え、答えが変わる。必ず $\mathrm{find}$ で根を求め、根どうしをつなぐ。

**親の値で同じグループかを比べる**。`par[a] == par[b]` は判定にならない。経路圧縮はたどった要素しか書き換えないので、同じグループの要素でも親は違いうる。図の $\mathrm{find}(7)$ のあとでも、3 の親は 2 で、5 の親は 4 である。比べるのは常に $\mathrm{find}(a)$ と $\mathrm{find}(b)$ である。グループごとに集計するときも、$\mathrm{par}[v]$ ではなく $\mathrm{find}(v)$ を添字にする。

**`groups()` を何度も呼ぶ**。ACL の `groups()` は呼ぶたびに $O(N)$ かかる。質問ごとに呼ぶと全体で $O(NQ)$ になる。成分の数は併合の成功回数から、最大の大きさは併合のたびに更新して持つ。

**1-indexed のまま使う**。問題の頂点番号は 1 から始まる。`dsu d(n)` に $N$ をそのまま渡すと、頂点 $N$ が範囲の外になる。ACL では assert で止まり、自作では配列の外を読む。読んだ直後に 1 を引くか、大きさ $N + 1$ で作って 0 番を使わない。

## 使い分け {#comparison}

- **グラフが最初から全部与えられる**：連結成分を 1 回求めるだけなら、[BFS](../graph/bfs.md)・[DFS](../graph/dfs.md)・Union-Find のどれでもよい（[連結成分](../graph/connected-components.md)）。Union-Find は隣接リストを作らずに済むので短く書ける
- **辺の追加と質問が交互に来る**：Union-Find を使う。BFS で毎回調べ直すと間に合わない
- **距離や経路そのものが要る**：Union-Find は連結かどうかしか分からない。BFS などの探索を使う
- **辺や頂点の削除がある**：削除の順序が最初に全部分かる（オフライン）なら、操作を逆順に見て「追加」に直すことで Union-Find を使える（[Union-Find で連結性を扱う](../graph/union-find-connectivity.md)）。追加と削除が入り混じるなら、発展の[辺の追加と削除が混ざる連結性](../graph/offline-dynamic-connectivity.md)の方法を使う（これも先読みが前提で、部品は[ロールバックできる Union-Find](../ds/rollback-union-find.md#offline-dynamic-connectivity)）
- **有向グラフ**：Union-Find は向きを無視した連結しか扱えない。互いに行き来できるかは[強連結成分分解](../graph/scc.md)を使う

??? question "確認問題：削除のクエリ"
    $N$ 頂点 $M$ 辺のグラフから辺を 1 本ずつ取り除き、取り除くたびに連結成分の数を答える。Union-Find で解けるか。

    ??? success "答え"
        Union-Find は分割ができないので、そのままでは解けない。ただし取り除く順序が最初に全部分かるので、最後の状態（取り除かれない辺だけのグラフ）から始め、逆順に辺を足していけば Union-Find で解ける。答えは逆順に記録し、最後に反転して出力する。

## 上位の手法へのつながり {#next-steps}

- **根に情報を持たせる・併合で数える**：成分ごとの最小値や上位 $K$ 個を持つ型、辺を重みの順に足して組の数を数える型（[Union-Find の応用](../ds/union-find-applications.md)）
- **差を持たせる**：親との差 $\mathrm{diff}[v]$ を持たせると、「$x_b - x_a = w$」という条件の矛盾を判定できる（[重み付き Union-Find](../ds/weighted-union-find.md)）。頂点を 2 倍にして二部グラフを判定する型もある（[二部グラフ判定](../graph/bipartite-graph.md)）
- **最小全域木**：辺を重みの小さい順に見て、両端が別のグループなら採用する（クラスカル法、[最小全域木](../graph/minimum-spanning-tree.md)）。採用の判定がそのまま Union-Find の判定である
- **小さい方を大きい方へ**：union by size の「小さい方が動くたびに大きさが 2 倍以上になる」という議論は、集合を丸ごと移すときにも使える（[マージテク](../tree/small-to-large.md)）
- **履歴を残す**：経路圧縮をやめて union by size だけにすると、操作の取り消しや過去の時点の判定ができる（[ロールバックできる Union-Find](../ds/rollback-union-find.md#no-path-compression)・[部分永続 Union-Find](../ds/partially-persistent-union-find.md#no-path-compression)）

## 例題 {#examples}

### ABC288 C. Don’t be cycle {#abc288_c}

<div class="kp-problems" data-role="example" markdown>

- [ABC288 C. Don’t be cycle](https://atcoder.jp/contests/abc288/tasks/abc288_c)（diff 436）：単純無向グラフから辺を取り除いて閉路をなくすとき、取り除く辺の最小本数を求める。

</div>

辺を 1 本ずつ足していき、両端がすでに同じグループならその辺は閉路を作る。そういう辺だけを取り除けば、残りは閉路のない森になる。連結成分の数を $C$ とすると、残せる森の辺は $N - C$ 本までである。だから取り除く本数は $M - (N - C)$ より少なくできず、この方法はちょうどその本数を取り除く。

??? note "解法の詳細"
    - 辺を入力の順に見る。$\mathrm{same}(u, v)$ なら数え、そうでなければ $\mathrm{merge}(u, v)$ する。数えた本数が答えである。
    - 答えは $M - (N - C)$ とも書ける。どの順に辺を見ても、残す辺は全域森になるので本数は同じである。
    - 全体で $O(N + M \, \alpha(N))$。コードは[境界](#boundaries)の節の ACL の例と同じ形である。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [ABC292 D. Unicyclic Components](https://atcoder.jp/contests/abc292/tasks/abc292_d)（diff 579）：すべての連結成分で頂点数と辺数が等しいかを判定する。
- [ABC177 D. Friends](https://atcoder.jp/contests/abc177/tasks/abc177_d)（diff 732）：友達関係から、どのグループにも友達どうしがいないように分けるときの最小のグループ数を求める。
- [ABC206 D. KAIBUNsyo](https://atcoder.jp/contests/abc206/tasks/abc206_d)（diff 879）：値を別の値に一括で置き換える操作で、数列を回文にする最小回数を求める。
- [ABC157 D. Friend Suggestions](https://atcoder.jp/contests/abc157/tasks/abc157_d)（diff 1208）：各人について、同じ成分にいて友達でもブロック相手でもない人の数を答える。
- [典型90 012. Red Painting（★4）](https://atcoder.jp/contests/typical90/tasks/typical90_l)（diff —）：マスを赤く塗るクエリと、2 マスが赤いマスだけで行き来できるかのクエリを処理する。
- [PRACTICE2 A. Disjoint Set Union](https://atcoder.jp/contests/practice2/tasks/practice2_a)（diff —）：辺の追加と、2 頂点が連結かの判定のクエリを処理する。

</div>

??? note "練習の方針"
    - **ABC292 D**：根に頂点数と辺数を持たせ、全部の成分で等しいかを見る。自己ループと多重辺も 1 本と数える。併合が終わってから各頂点の辺数を根に足し込んでもよい
    - **ABC177 D**：問題文から、友達の友達も友達になる。だから同じ連結成分の人は全員が互いに友達で、別々のグループに入れる必要がある。逆に最大の成分の大きさだけグループがあれば足りるので、それが答えである
    - **ABC206 D**：値を頂点にし、対称な位置の値 $A_i$ と $A_{N-1-i}$ をつなぐ。大きさ $K$ の成分をそろえるには $K - 1$ 回が要り、それで足りる。併合に成功した回数がそのまま答えである
    - **ABC157 D**：友達関係で併合し、人 $i$ の答えは「成分の大きさ − 1 − 同じ成分にいる友達とブロック相手の数」である。友達は必ず同じ成分にいるので次数を引き、ブロック相手は同じ成分のときだけ引く
    - **典型90 012**：マス $(r, c)$ を $rW + c$ の番号にする（0-indexed）。塗るたびに上下左右の赤いマスと併合する。判定では、まず 2 マスとも赤いかを確かめてから $\mathrm{same}$ を見る
    - **PRACTICE2 A**：ACL の `dsu` か自作の Union-Find をそのまま使う。自作の動作確認に使える

## 参考 {#references}

- [AtCoder Library「DSU」（document_ja）](https://github.com/atcoder/ac-library/blob/master/document_ja/dsu.md)：ACL の `dsu` の操作・計算量・制約
- [けんちょん「AtCoder ACL Practice Contest A - Disjoint Set Union」](https://drken1215.hatenablog.com/entry/2022/12/14/212330)：計算量 $O(\alpha(N))$ と $\alpha$ の大きさ、自作の Union-Find の書き方
- [kyo-pro「ABC288C - Don’t be cycle」](https://kyo-pro.hatenablog.com/entry/2023/02/04/224004)：例題の方針（同じ成分を結ぶ辺を数える）
- [kyo-pro「ABC292D - Unicyclic Components」](https://kyo-pro.hatenablog.com/entry/ABC292D)：練習の方針（根に頂点数と辺数を持たせ、辺数は併合のあとで根に足し込む）
- [けんちょん「AtCoder ABC 177 D - Friends」](https://drken1215.hatenablog.com/entry/2020/10/10/023200)：練習の方針（最大の連結成分の大きさが答えになる理由）
- [drken「AtCoder ABC 206 D - KAIBUNsyo (2Q, 緑色, 400 点)」](https://drken1215.hatenablog.com/entry/2021/06/26/165800)：練習の方針（値を頂点にし、併合の成功回数を数える）
- [けんちょん「AtCoder ABC 157 D - Friend Suggestions」](https://drken1215.hatenablog.com/entry/2020/03/02/022900)：練習の方針（成分の大きさから自分・友達・ブロック相手を引く）
- [E869120「競プロ典型 90 問 012 の解答例」](https://github.com/E869120/kyopro_educational_90/blob/main/sol/012.cpp)：練習の方針（マスの番号付けと、両方赤かの確認）
