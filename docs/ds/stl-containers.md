---
id: stl-containers
title: STL コンテナの使い分け
aliases: [STL, STL containers, 標準ライブラリのコンテナ, コンテナの計算量]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 10
level: 基礎
kind: [データ構造, 実装・C++]
prerequisites: []
related: [ordered-set, priority-queue, stack-techniques, prefix-sum-counting, cpp-container-idioms]
summary: どの操作を速くしたいかで vector・deque・set・map・priority_queue・unordered_map を選ぶ。multiset の erase(x) は同じ値を全部消し、map の [] は要素を作る。
complexity: set・map の追加・削除・検索・lower_bound は O(log N)、priority_queue の追加・取り出しは O(log N)、vector の末尾への追加はならし O(1)、unordered_map は平均 O(1)（最悪 O(N)）
signs:
  - {type: phrase, text: 要素の追加・削除と、検索・最小値の取り出しのクエリが混ざる}
  - {type: shape, text: 'j − i = A_i + A_j のように、i だけの式と j だけの式が等しい組 (i, j) を数える'}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で、追加・削除・検索のクエリが来る'}
acl: []
verify: [associative_array]
frequency: A
frequency_evidence: recent 0・前提として 72 ページに届く（直接 5）・古い ABC 2 問
sections:
  - {title: 操作とコンテナの計算量の早見表, anchor: complexity-table}
  - {title: map で数えながら走査する（→ 累積和と連想配列で区間を数える）, anchor: counting-map}
stage: reviewed
updated: 2026-10-22
---

!!! abstract "要点"
    - **何ができるか**：どの操作を速くしたいかで vector・deque・set・map・priority_queue・unordered_map を選ぶ。multiset の `erase(x)` は同じ値を全部消し、map の `[]` は要素を作る。
    - **いつ使うか**：
        - 要素の追加・削除と、検索・最小値の取り出しのクエリが混ざる。
        - $j - i = A_i + A_j$ のように、$i$ だけの式と $j$ だけの式が等しい組 $(i, j)$ を数える。
        - $N, Q \le 2 \times 10^5$ で、追加・削除・検索のクエリが来る。
    - **計算量**：set・map の追加・削除・検索・`lower_bound` は $O(\log N)$、priority_queue の追加・取り出しは $O(\log N)$、vector の末尾への追加はならし $O(1)$、unordered_map は平均 $O(1)$（衝突を狙った入力では最悪 $O(N)$）。
    - **前提**：なし

<!-- textlint-disable -->
別名：STL・STL containers・標準ライブラリのコンテナ・コンテナの計算量
<!-- textlint-enable -->

STL コンテナの使い分けは、クエリで何度も行う操作を書き出し、その操作が速いコンテナを選ぶことである。どのコンテナも何かを速くする代わりに別の何かを遅くしているので、速くしたい操作が決まれば選択肢はほぼ 1 つに決まる。基本の使い方は知っているものとして、選び方・数えながらの走査・よくある事故に絞る。

## 操作とコンテナの計算量の早見表 {#complexity-table}

コンテナを選ぶときは、次の表で「速い操作」の列に自分の欲しい操作があるものを探す。$N$ は要素数である。

| コンテナ | 速い操作 | 遅い・できない操作 |
| --- | --- | --- |
| `vector` | 添字アクセス $O(1)$、末尾の追加・削除 ならし $O(1)$ | 途中・先頭への挿入と削除 $O(N)$、値の検索 $O(N)$ |
| `deque` | 添字アクセス $O(1)$、両端の追加・削除 $O(1)$ | 途中への挿入と削除 $O(N)$ |
| `stack`・`queue` | 端の追加・削除・参照 $O(1)$ | 端以外は見られない |
| `priority_queue` | 追加・最大の取り出し $O(\log N)$、最大を見る $O(1)$ | 任意の要素の削除・検索、値の書き換え |
| `set`・`multiset` | 追加・削除・検索・`lower_bound` $O(\log N)$、最小・最大 $O(1)$、小さい順の走査 | K 番目の取得、`multiset` の `erase(x)`・`count(x)` は $O(\log N + x \text{ の個数})$ |
| `map` | キーで追加・削除・検索・`lower_bound` $O(\log N)$、キーの小さい順の走査 | K 番目の取得 |
| `unordered_set`・`unordered_map` | 追加・削除・検索 平均 $O(1)$ | 順序がない（`lower_bound`・最小がない）、最悪 $O(N)$ |

vector の末尾への追加が「ならし $O(1)$」なのは、容量が足りなくなると約 2 倍（libstdc++ の場合）の領域を取り直して全体を写すからである。写す回数の合計は $N + N/2 + N/4 + \dots < 2N$ なので、1 回あたりは定数で済む。ただし再確保の瞬間には、それまでのイテレータと参照がすべて無効になる（[落とし穴](#pitfalls)）。

set・map は平衡二分探索木（libstdc++ では赤黒木）で、木の高さが常に $O(\log N)$ に保たれる。追加・削除・検索は根から 1 本の道をたどるだけなので $O(\log N)$ になる。中身の仕組みは[平衡二分探索木](../ds/balanced-bst.md)にある。

表にない `list`（位置が分かっていれば挿入・削除 $O(1)$）は競技プログラミングではほとんど使わない。前後の要素をつなぎ替える操作は、配列で前後の添字を持つ方が速く書ける（[配列で作る連結リスト](../ds/linked-list.md)）。

## 使い分け {#comparison}

選ぶ手順は「クエリで繰り返す操作を全部書き出す → そのすべてが速いコンテナを表から探す」である。よく出る組み合わせは次のとおりである。

| 繰り返す操作 | 選ぶもの | 理由 |
| --- | --- | --- |
| 最大（最小）の取り出しと追加だけ | `priority_queue` | 定数倍が軽い。最小は `priority_queue<int, vector<int>, greater<int>>`（[落とし穴](#pitfalls)） |
| 追加・削除と最小・最大の両方 | `multiset` | ヒープは任意の要素を消せない |
| 追加・削除と「$x$ 以上で最小」 | `set`・`multiset` | メンバの `lower_bound` が $O(\log N)$ |
| 値ごとの個数・名前ごとの値 | `map`（キーの範囲が狭ければ配列） | キーが大きい・文字列でも使える |
| 先頭と末尾の両方から出し入れ | `deque` | `vector` の先頭への挿入は $O(N)$ |

選ぶときの考え方は 3 つある。

- **できる操作が多いほど遅い**：`priority_queue` でできることは `multiset` でもできるが、`multiset` は木の節点を 1 つずつ確保するので定数倍が数倍から 10 倍ほど重い。最大の取り出しと追加だけなら `priority_queue` を使う。逆に、任意の要素の削除が要るのに `priority_queue` を選ぶと、遅延削除という工夫が要る（[優先度付きキュー](../ds/priority-queue.md)）
- **値の範囲が狭ければ配列**：値が $10^6$ 以下の整数なら、`map<int, int>` より `vector<int> cnt(V)` の方が速く、$O(1)$ で数えられる。値が $10^9$ まであるなら map を使うか、先に[座標圧縮](../basics/coordinate-compression.md)して配列にする
- **標準にない操作は別のデータ構造へ**：「小さい方から K 番目」「$x$ 未満の要素の個数」は set では速く求まらない（イテレータを K 歩進めると $O(K)$）。[K 番目の値を求めるデータ構造](../ds/kth-element.md)の BIT や pb_ds を使う

??? question "確認問題：set で x 未満の最大の要素"
    `set<int> s` で、$x$ 未満で最大の要素を $O(\log N)$ で得るにはどう書くか。そのような要素がないときはどう判定するか。

    ??? success "答え"
        `auto it = s.lower_bound(x);` で $x$ 以上の最小の要素を指し、その 1 つ前 `prev(it)` が $x$ 未満の最大である。`it == s.begin()` なら $x$ 未満の要素はないので、`prev` を取る前に判定する（`begin()` に `prev` を使うこと自体が未定義動作）。

## map で数えながら走査する（→ 累積和と連想配列で区間を数える） {#counting-map}

「条件を満たす組 $(i, j)$（$i < j$）の個数」を素朴に数えると $O(N^2)$ かかる。条件を「$i$ で決まる値 $=$ $j$ で決まる値」の形に変形できれば、左から走査しながら $O(N \log N)$ で数えられる。

例として $A_j - A_i = j - i$ を満たす組を数える。移項すると $A_i - i = A_j - j$ になり、左辺は $i$ だけ、右辺は $j$ だけで決まる。そこで $j$ を左から動かし、これまでに見た $i$ について $A_i - i$ の値ごとの個数を map に記録しておく。$j$ での答えへの寄与は、記録の中で値が $A_j - j$ のものの個数である。

```cpp
--8<-- "stl-containers/count-pairs.cpp:core"
```

- **調べてから記録する**：$j$ 自身を先に記録すると、$i = j$ の組まで数える。検索を先にすれば、記録にあるのは常に $j$ より前の添字だけになる
- **符号付きで大きめの型**：$A_j - j$ は負にもなるので、キーは符号付きにする。組の数は最大 $N(N-1)/2 \approx 2 \times 10^{10}$ なので、答えを `long long` で持つ
- **検索に `[]` を使わない**：`cnt[key]` で検索すると、ない値の要素が作られて map が膨らむ。答えは変わらないが、メモリと時間を余計に使う

区間の和の条件も、累積和 $S$ を使うと「$S_l = S_r - K$」のように $l$ だけの式と $r$ だけの式に分かれるので、同じ走査で数えられる。$S_0$ を最初に記録しておくことや余りの扱いなど、区間に固有の注意は[累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#equal-k)にまとめてある。

## 落とし穴 {#pitfalls}

**multiset の `erase(x)` は等しい要素を全部消す**。`ms.erase(5)` は 5 を 1 個ではなく全部消し、消した個数を返す。1 個だけ消すなら、`find` で得たイテレータを渡す。`find` が `end()` を返したまま `erase` すると未定義動作なので、先に確かめる（[1 個だけ消す書き方](../cpp/cpp-container-idioms.md#multiset-erase-one)）。また `count(x)` は $x$ の個数に比例する時間がかかる。同じ値が大量にあるときに毎回呼ぶと遅いので、有無だけなら `contains(x)`（C++20）を使う。

```cpp
--8<-- "stl-containers/multiset-erase.cpp:core"
```

**set に `std::lower_bound` を使うと $O(N)$**。`std::lower_bound(s.begin(), s.end(), x)` は比較こそ $O(\log N)$ 回だが、set のイテレータは 1 歩ずつしか進めないので、中点へ移動するだけで $O(N)$ かかる。正しい結果が返るので気づきにくく、TLE で初めて分かる。set・map ではメンバの `s.lower_bound(x)` を使う（[メンバの lower_bound](../cpp/cpp-container-idioms.md#member-lower-bound)）。

**map の `[]` は要素を作る**。`if (mp[x] > 0)` と書くだけで、$x$ がなければ値 0 の要素が作られる。要素数 `mp.size()` で「異なる値の個数」を数えていると、調べただけの値まで数えてしまう。存在を調べるだけなら `mp.contains(x)`（C++20）か `mp.find(x) != mp.end()` を使う（[map の []](../cpp/cpp-container-idioms.md#map-subscript)）。

**空のコンテナの `size() - 1`**。`size()` は符号なしの整数を返すので、空のときの `v.size() - 1` は $-1$ ではなく約 $1.8 \times 10^{19}$ になる。`for (int i = 0; i < v.size() - 1; i++)` は、空の `v` で範囲の外を読み続ける。`i + 1 < v.size()` と書くか、`(int)v.size() - 1` のように符号付きに直してから引く。

**イテレータの無効化**。vector に `push_back` すると、再確保のたびにそれまでのイテレータ・参照・ポインタがすべて無効になる。範囲 for で `v` を回しながら同じ `v` に `push_back` するのは未定義動作である。set・map では消した要素を指すイテレータだけが無効になるので、走査しながら消すときは `it = s.erase(it)` で次へ進む（[無効化の規則](../cpp/cpp-container-idioms.md#invalidation)）。

**priority_queue は最大を取り出す**。既定の `priority_queue<int>` は `top()` が最大である。最小が欲しいときは `priority_queue<int, vector<int>, greater<int>>` にする。符号を反転して入れる方法もあるが、取り出すときに戻し忘れやすい。

**unordered_map が遅くなる**。ハッシュ値が同じ箱に集まるような入力を作られると、1 回の操作が $O(N)$ まで遅くなる。AtCoder ではまれだが、入力を参加者が作れるコンテストでは狙われる。順序が要らず、map では間に合わないときだけ使い、そのときは乱数を混ぜたハッシュを渡す（[ハッシュの衝突と安全な設計](../string/hash-safety.md#unordered-map)）。迷ったら map を使えばよい。

??? question "確認問題：multiset から 1 個だけ消す"
    `multiset<int> ms` に 3 が 4 個入っている。3 を 2 個だけ消したい。`ms.erase(3)` を 2 回呼ぶと何が起きるか。正しくはどう書くか。

    ??? success "答え"
        1 回目の `ms.erase(3)` で 3 が 4 個とも消え、2 回目は何も消さずに 0 を返す。1 個ずつ消すには `auto it = ms.find(3); if (it != ms.end()) ms.erase(it);` を 2 回行う。

## 上位の手法へのつながり {#next-steps}

この使い分けは、上位の手法の部品になる。

- **前後の要素・mex**：set の `lower_bound` とその 1 つ前で「最も近い値」を求め、追加・削除と組み合わせる（[set・multiset・map の応用](../ds/ordered-set.md)）
- **ヒープの貪欲と遅延削除**：ソートとヒープを組む貪欲、上位 K 個の列挙、消したい値を別のヒープに入れて後で捨てる遅延削除（[優先度付きキュー](../ds/priority-queue.md)）
- **2 つの multiset**：上位 K 個とそれ以外に分けて持ち、境界の 1 個を入れ替えながら和や中央値を保つ（[上位 K 個の和と中央値の管理](../ds/top-k-multiset.md)）
- **全体への操作**：全要素に一律に足す量をコンテナの外の変数で持ち、入れるときに引いて出すときに足す（[全体への操作を変数で持つ](../ds/global-offset.md)）
- **スタック・キュー・deque**：括弧の対応・打ち消し・両端からの処理（[スタック・キュー・deque の使いどころ](../ds/stack-techniques.md)）

## 例題 {#examples}

### ABC253 C. Max - Min Query {#abc253_c}

<div class="kp-problems" data-role="example" markdown>

- [ABC253 C. Max - Min Query](https://atcoder.jp/contests/abc253/tasks/abc253_c)（diff 518）：多重集合への追加・個数を指定した削除と、最大値 − 最小値の出力を繰り返す。

</div>

繰り返す操作は「追加」「値 $x$ を指定した個数だけ削除」「最大と最小を見る」の 3 つである。任意の値の削除と、最大・最小の両方が要るので、表から `multiset` を選ぶ。`erase(x)` は $x$ を全部消してしまうので、イテレータで 1 個ずつ消す。

??? note "解法の詳細"
    - 追加は `ms.insert(x)`。削除は「`find(x)` が `end()` でない間、そのイテレータを `erase` する」を最大 $c$ 回繰り返す（[落とし穴](#pitfalls)のコード）。出力は `*ms.rbegin() - *ms.begin()`。
    - 指定された個数が大きくても、消せるのは入っている個数までである。消した要素はどれも過去に 1 回ずつ追加されたものなので、削除の回数は全体で追加の回数を超えない。クエリ数を $Q$ として全体で $O(Q \log Q)$ になる。
    - 別の書き方：`map<int, int>` で値ごとの個数を持ち、個数を $\min(c, \text{個数})$ だけ減らして 0 になったらキーを消す。最大と最小は `rbegin()->first`・`begin()->first` で得られ、削除は 1 回 $O(\log Q)$ で済む。
    - ヒープを最大用・最小用の 2 本持ち、個数の表で消えた値を後から捨てる遅延削除でも解ける（[優先度付きキュー](../ds/priority-queue.md)）。

## 練習問題 {#practice}

<div class="kp-problems" data-role="practice" markdown>

- [鉄則本 A54. Map](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bb)（diff —）：名前ごとの点数の登録と参照のクエリを処理する。
- [鉄則本 A55. Set](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bc)（diff —）：整数の追加・削除と「x 以上で最小の値」のクエリを処理する。
- [ABC166 E. This Message Will Self-Destruct in 5s](https://atcoder.jp/contests/abc166/tasks/abc166_e)（diff 1062）：j − i = A_i + A_j を満たす組 (i, j) の数を求める。

</div>

??? note "練習の方針"
    - **鉄則本 A54**：キーが文字列なので `map<string, int>` で名前から点数を引く。登録は代入で上書きする
    - **鉄則本 A55**：`set<int>` の `insert`・`erase` と、メンバの `lower_bound`。`end()` が返れば該当する値がない
    - **ABC166 E**：$i + A_i = j - A_j$ と $i$ だけの式と $j$ だけの式に分け、[map で数えながら走査する](#counting-map)。$A_i \ge 1$ なので $i \ge j$ の組は条件を満たさず、先に全部の $i$ を記録してから数えても同じになる

## 参考 {#references}

- [kyo-pro「ABC253C - Max - Min Query」](https://kyo-pro.hatenablog.com/entry/ABC253C)：例題の multiset での 1 個ずつの削除と、map・ヒープによる別解
- [drken「AtCoder ABC 166 E - This Message Will Self-Destruct in 5s (1Q, 緑色, 500 点)」](https://drken1215.hatenablog.com/entry/2024/11/23/172436)：練習の方針（式を i 側と j 側に分けて map で数える）
- [E869120「kyopro-tessoku」の第 8 章のコード](https://github.com/E869120/kyopro-tessoku/tree/main/codes/cpp/chap08)：練習の方針（A54 の map、A55 の set）
- [cpprefjp「std::multiset::erase」](https://cpprefjp.github.io/reference/set/multiset/erase.html)：キーを渡した erase が等しい要素を全部消し、個数を返すこと
- [cpprefjp「multiset::count」](https://cpprefjp.github.io/reference/set/multiset/count.html)：count が対数時間と等しい要素の個数に比例する時間かかること
- [cppreference「std::lower_bound」](https://en.cppreference.com/w/cpp/algorithm/lower_bound)：ランダムアクセスでないイテレータでは比較が対数回でも移動が線形になり、set・map ではメンバを使うべきこと
