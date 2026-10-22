---
title: データ構造の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# データ構造の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## STL コンテナの使い分け（stl-containers） {#stl-containers}

- id：`stl-containers`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/stl-containers/
- 別名：STL、STL containers、標準ライブラリのコンテナ、コンテナの計算量
- 種類：データ構造、実装・C++
- サイン：
    - 言い回し：要素の追加・削除と、検索・最小値の取り出しのクエリが混ざる
    - 式の形：j − i = A_i + A_j のように、i だけの式と j だけの式が等しい組 (i, j) を数える
    - 制約：N, Q ≤ 2×10^5 で、追加・削除・検索のクエリが来る
- 節：
    - `stl-containers#complexity-table` 操作とコンテナの計算量の早見表：https://yuukougun.github.io/kyopro-atlas/ds/stl-containers/#complexity-table
    - `stl-containers#counting-map` map で数えながら走査する（→ 累積和と連想配列で区間を数える）：https://yuukougun.github.io/kyopro-atlas/ds/stl-containers/#counting-map

## set・multiset・map の応用（ordered-set） {#ordered-set}

- id：`ordered-set`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/
- 別名：順序付き集合、ordered set、set::lower_bound、前後の要素、番兵、パレート境界
- 種類：データ構造
- 前提：`stl-containers`
- サイン：
    - 言い回し：x 以上で最小の値・最も近い値を、追加・削除しながら何度も答える
    - 言い回し：まだ使われていない最小の値（mex）を更新のたびに答える
    - 言い回し：同じ行・同じ列で次にある壁や家を見つけて壊す
    - 制約：値が 10^9 まであり、配列の添字にできない
- 節：
    - `ordered-set#neighbors` 前後の要素（lower_bound とその 1 つ前。番兵で端の場合分けを消す）：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/#neighbors
    - `ordered-set#near-kth` K 番目付近（イテレータを K 歩動かす。K が小さいときだけ）：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/#near-kth
    - `ordered-set#mex` まだ出ていない値の set で mex を管理する（→ 題材別の mex）：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/#mex
    - `ordered-set#rows-and-columns` 行ごと・列ごとの set（グリッドで次の壁を探し、両方から消す）（水）：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/#rows-and-columns
    - `ordered-set#pareto` パレート境界を map で持つ（支配される点を消す。ならし O(log N)）（水）：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/#pareto
    - `ordered-set#adjacent-pairs` ソート順で隣り合う組の集合（2 番目に大きい値の寄与。最小 XOR の組は Binary Trie のページ）（青）：https://yuukougun.github.io/kyopro-atlas/ds/ordered-set/#adjacent-pairs

## 優先度付きキュー（priority-queue） {#priority-queue}

- id：`priority-queue`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/
- 別名：priority_queue、ヒープ、heap、二分ヒープ、binary heap、削除できるヒープ、遅延削除、erasable heap
- 種類：データ構造、貪欲
- 前提：`stl-containers`
- サイン：
    - 言い回し：毎回いちばん大きい（小さい）ものを取り出し、新しい候補を入れる
    - 言い回し：接頭辞ごとに K 番目に大きい値を答える
    - 言い回し：グループ間の移動のたびに、各グループの最大値のうちの最小値を答える
    - 制約：追加と取り出しが合わせて 2×10^5 回程度
- 節：
    - `priority-queue#what-it-does` 何ができるか（push・top・pop。最小を取り出す向きと pair の比較順。書き方は C++ 章）：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/#what-it-does
    - `priority-queue#binary-heap` 二分ヒープの仕組み（保つ性質「親 ≤ 子」・push で上げる・pop で下げる・heapify は O(N)）：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/#binary-heap
    - `priority-queue#patterns` 使い方の型（ソートと組む貪欲・上位 K 個の列挙・大きさ K のヒープで接頭辞の K 番目）：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/#patterns
    - `priority-queue#with-offset` 全体への加算と組む（入れるときに引き、出すときに足す）：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/#with-offset
    - `priority-queue#lazy-deletion` 削除できるヒープ（遅延削除：削除予定のヒープの top と一致したら両方から捨てる）：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/#lazy-deletion
    - `priority-queue#vs-multiset` priority_queue と multiset の使い分け（任意の削除・両端・前後の要素が要るなら multiset）：https://yuukougun.github.io/kyopro-atlas/ds/priority-queue/#vs-multiset

## 上位 K 個の和と中央値の管理（top-k-multiset） {#top-k-multiset}

- id：`top-k-multiset`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/
- 別名：2 つの multiset、2 つのヒープ、two heaps、下位 K 個の和、動的な中央値、running median、Priority Sum Structure
- 種類：データ構造
- 前提：`ordered-set`、`priority-queue`
- サイン：
    - 言い回し：1 点を更新するたびに、大きい方から K 個の和を答える
    - 言い回し：幅 M の窓をずらしながら、小さい方から K 個の和を答える
    - 言い回し：数を追加しながら中央値（|x − a_i| の和を最小にする x）を答える
    - 制約：Q ≤ 2×10^5 で、更新のたびに上位 K 個の和や中央値を答える
- 節：
    - `top-k-multiset#two-sets` 2 つに分けて持つ（L＝小さい K 個、R＝残り。L の和を持つ）：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/#two-sets
    - `top-k-multiset#invariants` 保つ性質（L の個数が K・L の最大 ≤ R の最小）と、境界の 1 個を移して回復する手順：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/#invariants
    - `top-k-multiset#erase-update` 削除・更新（どちらにあるかを見て消してから回復する）：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/#erase-update
    - `top-k-multiset#median` 中央値を保つ（個数の差を 1 以内に。削除がなければヒープ 2 本）と Σ|x − a_i| の更新：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/#median
    - `top-k-multiset#by-index` 値を添字にした BIT・セグメント木で書く方法（→ 値を添字にする BIT・セグメント木）：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/#by-index
    - `top-k-multiset#absolute-sum-function` |x − a| + b を足していく関数の最小値（中央値の更新の応用。Slope Trick の入口）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/top-k-multiset/#absolute-sum-function

## 区間を set で管理する（interval-set） {#interval-set}

- id：`interval-set`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/
- 別名：IntervalSet、RangeSet、ODT、Chtholly Tree、珂朵莉树、互いに素な区間の集合
- 種類：データ構造
- 前提：`ordered-set`
- サイン：
    - 言い回し：区間を塗るたびに、塗られたマスの数や色ごとのマスの数を答える
    - 言い回し：同じ色でつながった区間をまとめて塗り替える
    - 言い回し：点 x が覆われているか・x を含む区間はどこか
    - 制約：座標が 10^9 まで（配列の添字にできない）
- 節：
    - `interval-set#representation` 持ち方（左端をキーにした map・両端の番兵の区間）：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/#representation
    - `interval-set#find` x を含む区間の検索（upper_bound の 1 つ前）：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/#find
    - `interval-set#split` split(x)（区間の分割）を先に書き、代入・削除はその組み合わせで書く：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/#split
    - `interval-set#amortized` なぜならしで速いか（新しくできる区間は O(1) 個、消える区間は一度だけ）と、走査だけの操作が混ざると崩れる理由：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/#amortized
    - `interval-set#applications` 応用（mex・塗り分け・和集合の長さ・値ごとの合計の差分更新）：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/#applications
    - `interval-set#valued-intervals` 値つきの区間の分割・統合（黄）：https://yuukougun.github.io/kyopro-atlas/ds/interval-set/#valued-intervals

## 全体への操作を変数で持つ（global-offset） {#global-offset}

- id：`global-offset`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/global-offset/
- 別名：global offset、オフセット、全体加算、反転フラグ、回転量、全体に反映させる値を別に持つ
- 種類：データ構造、クエリ処理の工夫
- 前提：`stl-containers`
- サイン：
    - 言い回し：全要素に x を足す・全体に代入する操作がクエリに混ざる
    - 言い回し：列全体を反転してから先頭・末尾に追加する
    - 言い回し：配列を回転してから i 番目を参照する
    - 制約：Q ≤ 2×10^5 で、全体への操作を毎回 O(N) で行うと間に合わない
- 節：
    - `global-offset#offset` オフセット（入れるときに引き、出すときに足す）：https://yuukougun.github.io/kyopro-atlas/ds/global-offset/#offset
    - `global-offset#flip-flag` 反転フラグ（追加する側や添字の読み方を入れ替え、最後に向きを直す）：https://yuukougun.github.io/kyopro-atlas/ds/global-offset/#flip-flag
    - `global-offset#assign-all` 全体代入と個別の差分（代入のたびに差分の map を空にする。ならし）：https://yuukougun.github.io/kyopro-atlas/ds/global-offset/#assign-all
    - `global-offset#rotation` 回転は先頭位置の添字で表す：https://yuukougun.github.io/kyopro-atlas/ds/global-offset/#rotation
    - `global-offset#to-lazy-segment-tree` 遅延セグメント木とのつながり（全体への操作を区間への操作に広げる）（水）：https://yuukougun.github.io/kyopro-atlas/ds/global-offset/#to-lazy-segment-tree

## 配列で作る連結リスト（linked-list） {#linked-list}

- id：`linked-list`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/linked-list/
- 別名：連結リスト、双方向リスト、linked list、doubly linked list、prev・next の配列
- 種類：データ構造
- 前提：`stl-containers`
- サイン：
    - 言い回し：値 x の直後に y を挿入・値 x を削除する操作を繰り返し、最後の列を出力する
    - 言い回し：カードの山を別のカードの上へ付け替える
    - 言い回し：列車の連結・切り離し
- 節：
    - `linked-list#arrays` prev・next の配列と番兵（先頭・末尾）：https://yuukougun.github.io/kyopro-atlas/ds/linked-list/#arrays
    - `linked-list#operations` 挿入・削除・付け替えの手順：https://yuukougun.github.io/kyopro-atlas/ds/linked-list/#operations
    - `linked-list#output` 最後に先頭からたどって出力する：https://yuukougun.github.io/kyopro-atlas/ds/linked-list/#output

## スタック・キュー・deque の使いどころ（stack-techniques） {#stack-techniques}

- id：`stack-techniques`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/
- 別名：stack、queue、括弧の対応、打ち消し、操作の取り消し
- 種類：データ構造
- 前提：`stl-containers`
- サイン：
    - 言い回し：括弧の対応を取る・対応する括弧ごと消す
    - 言い回し：特定の並びが現れたら取り除く操作を繰り返した結果
    - 言い回し：直前の操作を取り消す（Undo）
    - 言い回し：円周上の弦どうしが交差するか
- 節：
    - `stack-techniques#brackets` 括弧の対応（開き括弧の位置を積む）と括弧列の残高（→ 題材別の括弧列）：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/#brackets
    - `stack-techniques#cancel` 直前と打ち消し合うものを消す（末尾を見て pop）：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/#cancel
    - `stack-techniques#run-length` ランレングスを積む（(値, 個数) の組）：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/#run-length
    - `stack-techniques#undo` 直前の操作を取り消す（変更前の値を積んで戻す。任意の版へ戻るなら永続データ構造）：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/#undo
    - `stack-techniques#deque` deque（両端への追加・真ん中への挿入は deque 2 本）：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/#deque
    - `stack-techniques#chords` 円を切り開いて弦の交差判定に帰着する（水）：https://yuukougun.github.io/kyopro-atlas/ds/stack-techniques/#chords

## 単調スタックとスライド最小値（monotonic-stack） {#monotonic-stack}

- id：`monotonic-stack`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/
- 別名：monotonic stack、単調 stack、ヒストグラム内最大長方形、sliding window minimum、単調 deque、単調キュー、SWAG、Sliding Window Aggregation、Cartesian Tree、デカルト木
- 種類：データ構造、尺取り・スライド窓
- 前提：`stack-techniques`
- サイン：
    - 言い回し：左（右）で初めて自分より大きい（小さい）要素の位置
    - 言い回し：各ビルから見えるビルの数・すべての区間の最小値の和
    - 言い回し：長さ K のすべての区間の最小値（最大値）
    - 式の形：dp[i] = min(dp[i−K..i−1]) + c のように、直前 K 個の最小値で決まる遷移
    - 制約：N ≤ 2×10^5 で、各要素から左右を見ていくと O(N^2) になる
- 節：
    - `monotonic-stack#procedure` 単調スタックの手順と保つ性質：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#procedure
    - `monotonic-stack#histogram` ヒストグラムの最大長方形：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#histogram
    - `monotonic-stack#contribution` i が最小（最大）になる区間の数と寄与の数え上げ：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#contribution
    - `monotonic-stack#visible` 見えるビルの数・水位のシミュレーション：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#visible
    - `monotonic-stack#sliding-window-minimum` スライド最小値（単調 deque）：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#sliding-window-minimum
    - `monotonic-stack#dp-transition` DP の遷移の高速化に使う：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#dp-transition
    - `monotonic-stack#cartesian-tree` Cartesian tree（最大値で区間を割る再帰を O(N) で作る）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#cartesian-tree
    - `monotonic-stack#swag` SWAG：スタック 2 本で作る総積つきキュー（発展）：https://yuukougun.github.io/kyopro-atlas/ds/monotonic-stack/#swag

## Union-Find（union-find） {#union-find}

- id：`union-find`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/union-find/
- 別名：UF、DSU、Disjoint Set Union、disjoint set、素集合データ構造、経路圧縮、union by size
- 種類：データ構造、連結性・全域木
- 前提：`graph-basics`
- ACL：`dsu`
- サイン：
    - 言い回し：辺を追加していきながら、2 頂点が同じグループか・グループの大きさを答える
    - 言い回し：グループを合併する操作と、グループについての質問が交互に来る
    - 言い回し：連結成分の個数・最大の連結成分の大きさ
    - 制約：N, Q ≤ 2×10^5 で辺の追加と質問が混ざる
- 節：
    - `union-find#what-it-does` 何ができるか（併合と判定。分割・削除はできない）：https://yuukougun.github.io/kyopro-atlas/ds/union-find/#what-it-does
    - `union-find#invariants` 保つ性質（各グループは根付き木で、根が代表元。par は根なら −(大きさ)）：https://yuukougun.github.io/kyopro-atlas/ds/union-find/#invariants
    - `union-find#operations` 各操作の手順（find は根までたどって経路圧縮、merge は根どうしを小さい方から大きい方へつなぐ）：https://yuukougun.github.io/kyopro-atlas/ds/union-find/#operations
    - `union-find#complexity` なぜ速いか（union by size だけで深さ log N、経路圧縮と合わせてならし O(α(N))）：https://yuukougun.github.io/kyopro-atlas/ds/union-find/#complexity
    - `union-find#boundaries` 境界（同じグループどうしの併合・自己ループと多重辺・成分数・大きさの積のあふれ）：https://yuukougun.github.io/kyopro-atlas/ds/union-find/#boundaries
    - `union-find#size-and-edges` 根に大きさ・辺数を持たせる（ほかの情報を持たせる型は Union-Find の応用）：https://yuukougun.github.io/kyopro-atlas/ds/union-find/#size-and-edges

## Union-Find の応用（union-find-applications） {#union-find-applications}

- id：`union-find-applications`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/
- 別名：UF に情報を持たせる、併合時の寄与、成分ごとの集約、次の空きへ飛ぶ Union-Find、次の要素へのポインタ、区間を塗る UF
- 種類：データ構造、連結性・全域木
- 前提：`union-find`
- ACL：`dsu`
- サイン：
    - 言い回し：全頂点対について、パス上の最大の辺の重みの総和
    - 言い回し：いくつかの区間の和が分かっているとき、全体の和が決まるか
    - 言い回し：成分の中で K 番目に大きい番号・成分の中のクラス c の人数
    - 言い回し：右にある最初の空き位置に書き込む
- 節：
    - `union-find-applications#data-on-root` 根に成分の情報を持たせる：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/#data-on-root
    - `union-find-applications#count-on-merge` 併合の瞬間に寄与を数える：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/#count-on-merge
    - `union-find-applications#modeling` 何を頂点にするかの言い換え：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/#modeling
    - `union-find-applications#next-pointer` 次の空きへ飛ぶ Union-Find：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/#next-pointer
    - `union-find-applications#vs-graph` グラフの章との分担：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/#vs-graph
    - `union-find-applications#multiple-uf` しきい値ごと・関係ごとに Union-Find を持つ（青）：https://yuukougun.github.io/kyopro-atlas/ds/union-find-applications/#multiple-uf

## 重み付き Union-Find（weighted-union-find） {#weighted-union-find}

- id：`weighted-union-find`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/
- 別名：weighted union-find、ポテンシャル付き Union-Find、重み付き UF、偶奇の Union-Find、二部グラフの Union-Find、頂点倍化の Union-Find、差分の矛盾判定
- 種類：データ構造、連結性・全域木
- 前提：`union-find`
- サイン：
    - 言い回し：x_R − x_L = D の形の情報が順に与えられ、矛盾しないかを判定する
    - 言い回し：相対的な位置・差だけが分かっている
    - 言い回し：正直者と嘘つき・2 色に塗り分けられるか
    - 制約：情報と質問が交互に Q ≤ 2×10^5 回来る
- 節：
    - `weighted-union-find#idea` 必要になる場面とアイデア：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#idea
    - `weighted-union-find#invariants` 保つ性質（各頂点は親との差を持つ）：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#invariants
    - `weighted-union-find#operations` 各操作の手順（find・merge・差の取得）：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#operations
    - `weighted-union-find#boundaries` 境界（根の差は 0・同じ成分の merge・値の範囲）：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#boundaries
    - `weighted-union-find#consistency` 矛盾の判定と差の取得：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#consistency
    - `weighted-union-find#complexity` 計算量とその根拠：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#complexity
    - `weighted-union-find#generalization` 一般化（XOR で偶奇・二部グラフ、頂点を 2 倍にする）：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#generalization
    - `weighted-union-find#applications` 応用の型：https://yuukougun.github.io/kyopro-atlas/ds/weighted-union-find/#applications

## 部分永続 Union-Find（partially-persistent-union-find） {#partially-persistent-union-find}

- id：`partially-persistent-union-find`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/partially-persistent-union-find/
- 別名：部分永続 UF、時刻つき Union-Find、partially persistent union-find
- 種類：データ構造、連結性・全域木
- 前提：`union-find`、`binary-search`
- サイン：
    - 言い回し：最初の t 本の辺だけを使ったときに連結か・成分の大きさは
    - 言い回し：x と y が初めて同じ集合になるのは何回目の操作か
- 節：
    - `partially-persistent-union-find#what-it-does` 何ができるか（過去の時刻での find）：https://yuukougun.github.io/kyopro-atlas/ds/partially-persistent-union-find/#what-it-does
    - `partially-persistent-union-find#no-path-compression` なぜ経路圧縮をしないのか：https://yuukougun.github.io/kyopro-atlas/ds/partially-persistent-union-find/#no-path-compression
    - `partially-persistent-union-find#binary-search-time` 時刻の二分探索で「初めて連結になる時刻」を求める：https://yuukougun.github.io/kyopro-atlas/ds/partially-persistent-union-find/#binary-search-time
    - `partially-persistent-union-find#alternatives` 代わりの手（並列二分探索・併合過程の木（Kruskal 再構築木））：https://yuukougun.github.io/kyopro-atlas/ds/partially-persistent-union-find/#alternatives

## ロールバックできる Union-Find（rollback-union-find） {#rollback-union-find}

- id：`rollback-union-find`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/rollback-union-find/
- 別名：ロールバック UF、Undo つき Union-Find、undoable union-find、rollback union-find
- 種類：データ構造、連結性・全域木
- 前提：`union-find`
- サイン：
    - 言い回し：木の根から各頂点へのパスごとに、パス上の要素どうしのつながりを答える
    - 言い回し：辺の追加と削除が混ざり、そのたびに 2 頂点が連結かを答える
- 節：
    - `rollback-union-find#what-it-does` 何ができるか（後入れ先出しの取り消し）：https://yuukougun.github.io/kyopro-atlas/ds/rollback-union-find/#what-it-does
    - `rollback-union-find#no-path-compression` なぜ経路圧縮をしないのか（戻すコストとならしの保証が崩れること）：https://yuukougun.github.io/kyopro-atlas/ds/rollback-union-find/#no-path-compression
    - `rollback-union-find#with-dfs` 木の DFS と組む（入るとき併合・出るとき取り消し）：https://yuukougun.github.io/kyopro-atlas/ds/rollback-union-find/#with-dfs
    - `rollback-union-find#offline-dynamic-connectivity` オフライン動的連結性の部品（時間軸のセグメント木に辺を載せる → グラフの章）：https://yuukougun.github.io/kyopro-atlas/ds/rollback-union-find/#offline-dynamic-connectivity

## BIT（Fenwick Tree）（fenwick-tree） {#fenwick-tree}

- id：`fenwick-tree`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/
- 別名：Binary Indexed Tree、フェニック木、fenwick_tree
- 種類：データ構造、区間クエリ
- 前提：`prefix-sum`、`bit-operations`
- ACL：`fenwick_tree`
- サイン：
    - 言い回し：一点の値の更新と区間の和の質問が交互に来る
    - 言い回し：i より前にある x 以下の要素の個数
    - 式の形：Σ_{j&lt;i} [A_j ≤ A_i] のように、前にある要素のうち条件を満たすものの個数・和を i ごとに足す
    - 制約：N, Q ≤ 2×10^5 で更新があり、累積和を毎回作り直すと間に合わない
- 節：
    - `fenwick-tree#what-it-does` 何ができるか（一点加算・接頭辞の和と逆元）：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#what-it-does
    - `fenwick-tree#invariants` 保つ性質（添字 i は、i で終わる長さ lowbit(i) の区間の和を持つ）：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#invariants
    - `fenwick-tree#operations` 各操作の手順（add は上へ、sum は下へ。線形時間の構築）：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#operations
    - `fenwick-tree#boundaries` 境界（添字の変換・i = 0・符号なし整数）：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#boundaries
    - `fenwick-tree#count-by-value` 値を添字にして数える（座標圧縮と組む）：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#count-by-value
    - `fenwick-tree#variants` 変種（差分の BIT・BIT 2 本・2 次元 BIT・接頭辞の max）：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#variants
    - `fenwick-tree#binary-search` BIT 上の二分探索：https://yuukougun.github.io/kyopro-atlas/ds/fenwick-tree/#binary-search

## 転倒数（inversion-number） {#inversion-number}

- id：`inversion-number`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/inversion-number/
- 別名：inversion、inversion number、inversion count、反転数、バブルソートの交換回数、隣接 swap の最小回数
- 種類：データ構造、数え上げ
- 前提：`fenwick-tree`、`coordinate-compression`
- ACL：`fenwick_tree`
- サイン：
    - 言い回し：隣り合う要素の交換でソートする最小回数・バブルソートの交換回数
    - 言い回し：i < j かつ A_i > A_j を満たす組の数
    - 言い回し：巡回シフトや、全体に加算して mod を取った各列の転倒数
    - 制約：N ≤ 2×10^5 で、答えが約 2×10^10 まで大きくなる
- 節：
    - `inversion-number#count-with-bit` BIT で数える手順（値を座標圧縮し、左から自分より大きい既出の個数を足す）：https://yuukougun.github.io/kyopro-atlas/ds/inversion-number/#count-with-bit
    - `inversion-number#adjacent-swaps` なぜ隣接 swap の最小回数か（1 回の隣接 swap で転倒数はちょうど 1 増減する）：https://yuukougun.github.io/kyopro-atlas/ds/inversion-number/#adjacent-swaps
    - `inversion-number#reformulation` 言い換え（P を Q に並べ替える回数＝Q での位置に置き換えた列の転倒数、累積和の大小の組）：https://yuukougun.github.io/kyopro-atlas/ds/inversion-number/#reformulation
    - `inversion-number#incremental` 差分で更新する（先頭を末尾へ回す・全体に足して mod を取る・色ごとの転倒数を引く）：https://yuukougun.github.io/kyopro-atlas/ds/inversion-number/#incremental
    - `inversion-number#sliding-window` 窓を伸縮しながら転倒数を増減する（尺取り・期待値と組む）（青）：https://yuukougun.github.io/kyopro-atlas/ds/inversion-number/#sliding-window

## K 番目の値を求めるデータ構造（kth-element） {#kth-element}

- id：`kth-element`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/kth-element/
- 別名：BIT 上の二分探索、Fenwick tree binary search、order statistics、順序統計量、空きの K 番目
- 種類：データ構造、二分探索
- 前提：`fenwick-tree`、`ordered-set`
- ACL：`fenwick_tree`
- サイン：
    - 言い回し：数の追加・削除と、K 番目に小さい値の質問
    - 言い回し：空いている場所のうち K 番目に置く・指定した位置への挿入を繰り返した最終的な列
    - 言い回し：x 以下の要素の個数（順位）
- 節：
    - `kth-element#bit-binary-search` BIT 上の二分探索の手順（値が 0 以上であることが前提）：https://yuukougun.github.io/kyopro-atlas/ds/kth-element/#bit-binary-search
    - `kth-element#reverse-insertion` 挿入を逆順に処理して「空きの P 番目」に置く：https://yuukougun.github.io/kyopro-atlas/ds/kth-element/#reverse-insertion
    - `kth-element#vs-kth-value` 答えの二分探索で K 番目を数える方法との違い：https://yuukougun.github.io/kyopro-atlas/ds/kth-element/#vs-kth-value

## セグメント木（segment-tree） {#segment-tree}

- id：`segment-tree`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/
- 別名：セグ木、segtree、Segment Tree、RMQ、非再帰セグ木、区間最小値、文字の集合を持つセグ木
- 種類：データ構造、区間クエリ
- 前提：`prefix-sum`
- ACL：`segtree`
- サイン：
    - 言い回し：配列の値を書き換えながら、区間の最小値（最大値・gcd）を何度も答える
    - 言い回し：1 文字の更新と、区間に現れる文字の種類数
    - 制約：N, Q ≤ 2×10&#94;5〜5×10&#94;5 で、一点の更新と区間の質問が交互に来る
- 節：
    - `segment-tree#what-it-does` 何ができるか（一点更新・区間取得）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#what-it-does
    - `segment-tree#complexity` なぜ O(log N) か（各段で高々 2 個のノード）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#complexity
    - `segment-tree#invariants` 保つ性質：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#invariants
    - `segment-tree#operations` 各操作の手順：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#operations
    - `segment-tree#boundaries` 境界（半開区間・空区間・単位元）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#boundaries
    - `segment-tree#recursive-vs-iterative` 再帰型と非再帰型：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#recursive-vs-iterative
    - `segment-tree#string-queries` 文字列へのクエリ（文字の集合をビットで持つ）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#string-queries
    - `segment-tree#dp` DP の配列を載せる：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree/#dp

## セグメント木上の二分探索（segment-tree-binary-search） {#segment-tree-binary-search}

- id：`segment-tree-binary-search`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/
- 別名：セグ木上の二分探索、セグ木の二分探索、binary search on segment tree、max_right、min_left
- 種類：データ構造、二分探索、区間クエリ
- 前提：`segment-tree`、`binary-search`
- ACL：`segtree`、`lazy_segtree`
- サイン：
    - 言い回し：位置 i 以降で初めて値が x 以上になる位置
    - 言い回し：空いている場所のうち K 番目
    - 言い回し：各 l について、条件を満たす最長の区間
    - 制約：N, Q ≤ 2×10^5 で、更新のたびに条件を満たす最初の位置を答える
- 節：
    - `segment-tree-binary-search#what-it-does` 何ができるか（max_right・min_left）と f の条件：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/#what-it-does
    - `segment-tree-binary-search#complexity` なぜ O(log N) か（登る段階と降りる段階）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/#complexity
    - `segment-tree-binary-search#predicate-patterns` 条件の書き方の型（初めて x 以上・和が w 以下・mex）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/#predicate-patterns
    - `segment-tree-binary-search#kth-one` 和が K に達する位置（K 番目の 1・空きの K 番目）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/#kth-one
    - `segment-tree-binary-search#boundaries` 境界（l = N・返り値が N・f(e()) が偽になる条件・1-indexed）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/#boundaries
    - `segment-tree-binary-search#on-lazy-segment-tree` 遅延セグメント木の上の二分探索（単調な列への区間作用）（青）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-binary-search/#on-lazy-segment-tree

## 値を添字にする BIT・セグメント木（segment-tree-on-values） {#segment-tree-on-values}

- id：`segment-tree-on-values`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-on-values/
- 別名：値域セグ木、権値線段樹、値を添字にするセグ木、動的セグ木、dynamic segment tree、sparse segment tree
- 種類：データ構造、区間クエリ、ソート・座標圧縮
- 前提：`segment-tree`、`coordinate-compression`
- ACL：`segtree`、`fenwick_tree`
- サイン：
    - 言い回し：隣り合う要素の差が D 以下の部分列の最長
    - 言い回し：値を追加しながら、上位 K 個の和・ソートしたときの奇数番目の和を答える
    - 言い回し：前の答えを使って次のクエリが復号され、先読みができない
    - 式の形：dp[v] = max(dp[v − D..v + D]) + 1 のように、値の範囲から最大を取る遷移
    - 制約：値が 10^9 まで、N, Q ≤ 2×10^5
- 節：
    - `segment-tree-on-values#index-by-value` 値を添字にする（個数・和を載せる）と座標圧縮：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-on-values/#index-by-value
    - `segment-tree-on-values#dp-on-values` DP の値を値の添字で持つ：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-on-values/#dp-on-values
    - `segment-tree-on-values#top-k-sum` 上位 K 個の和（境界はセグメント木上の二分探索で探す）（青）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-on-values/#top-k-sum
    - `segment-tree-on-values#odd-position-sum` 左の個数の偶奇で右の読み方が変わる量（ソート後の奇数番目の和）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-on-values/#odd-position-sum
    - `segment-tree-on-values#dynamic-segment-tree` 動的セグメント木（必要なノードだけ作る）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-on-values/#dynamic-segment-tree

## 遅延セグメント木（lazy-segment-tree） {#lazy-segment-tree}

- id：`lazy-segment-tree`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/
- 別名：遅延セグ木、Lazy Segment Tree、lazy segtree、遅延評価セグメント木、遅延伝搬、区間作用・区間取得、双対セグ木、Dual Segment Tree
- 種類：データ構造、区間クエリ
- 前提：`segment-tree`
- ACL：`lazy_segtree`
- サイン：
    - 言い回し：区間に一律に加算・代入・アフィン変換・反転し、区間の和・最小値・最大値を答える
    - 言い回し：区間に一律に加算・代入し、一点の値だけを答える
    - 制約：N, Q ≤ 2×10^5 で、区間の更新と区間の取得が交互に来る
- 節：
    - `lazy-segment-tree#what-it-does` 何ができるか（区間作用・区間取得）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#what-it-does
    - `lazy-segment-tree#idea` 保留を持たせるアイデアとなぜ正しいか：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#idea
    - `lazy-segment-tree#complexity` 計算量とその根拠：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#complexity
    - `lazy-segment-tree#acl-standard` ACL の lazy_segtree で標準の型を呼ぶ：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#acl-standard
    - `lazy-segment-tree#size-in-node` 区間の長さを S に持たせる（区間和）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#size-in-node
    - `lazy-segment-tree#acl-conventions` ACL の約束（mapping・composition・id）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#acl-conventions
    - `lazy-segment-tree#boundaries` 境界（葉の長さ・e()・代入の番兵・INF・mod）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#boundaries
    - `lazy-segment-tree#dual-segment-tree` 双対セグメント木（区間作用・一点取得）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#dual-segment-tree
    - `lazy-segment-tree#invariants` 保つ性質と push の手順（自作するとき）（青）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree/#invariants

## セグメント木に何を載せるか（segment-tree-monoids） {#segment-tree-monoids}

- id：`segment-tree-monoids`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-monoids/
- 別名：モノイドの設計、monoid design、抽象化セグ木、second best、行列を載せるセグ木
- 種類：データ構造、区間クエリ
- 前提：`segment-tree`
- ACL：`segtree`
- サイン：
    - 言い回し：1 点の更新と、区間が正しい括弧列か・回文かの判定
    - 言い回し：区間で 2 番目に大きい値（の個数）
    - 言い回し：区間の最大部分配列和・区間で最長の連続する 1
    - 式の形：区間 [l, r) の答えが、各位置の一次関数や小さな行列を順に合成したもので書ける
- 節：
    - `segment-tree-monoids#design-steps` 設計の手順（答えに要る情報を足し、結合法則と単位元を確かめる）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-monoids/#design-steps
    - `segment-tree-monoids#pattern-table` 型の表（和・min/max・gcd・最小値と個数・括弧列・最大部分配列和など）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-monoids/#pattern-table
    - `segment-tree-monoids#non-commutative` 非可換なモノイド（一次関数の合成・ハッシュの連結。積む順序）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-monoids/#non-commutative
    - `segment-tree-monoids#matrix` 行列を載せる（(min,+)・(max,+) の半環も）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-monoids/#matrix

## 遅延セグメント木の載せ方の型（lazy-segment-tree-patterns） {#lazy-segment-tree-patterns}

- id：`lazy-segment-tree-patterns`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/
- 別名：遅延セグ木のチートシート、S と F の設計、区間加算区間最小、区間代入区間和、Range Affine Range Sum、区間反転
- 種類：データ構造、区間クエリ、考察
- 前提：`lazy-segment-tree`、`segment-tree-monoids`
- ACL：`lazy_segtree`
- サイン：
    - 言い回し：区間をソートする操作を繰り返す
    - 言い回し：2 つの数列への区間加算と、区間の Σ A_i B_i
    - 言い回し：0/1 列の区間反転と、区間で 1 が連続する最大の長さ
    - 言い回し：一列に並ぶ人を順に動かす総移動量
- 節：
    - `lazy-segment-tree-patterns#design-steps` 設計の手順と載せられる条件（S はモノイド・F は恒等写像を含み合成で閉じる・f(x·y) = f(x)·f(y)）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#design-steps
    - `lazy-segment-tree-patterns#pattern-table` 型の表（S・op・e・F・mapping・composition・id）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#pattern-table
    - `lazy-segment-tree-patterns#assign-sentinel` 区間代入の「なし」の番兵と composition の向き：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#assign-sentinel
    - `lazy-segment-tree-patterns#flip` 0/1 反転・転倒数・最長の連続（0 と 1 の情報を入れ替える）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#flip
    - `lazy-segment-tree-patterns#arithmetic-add` 等差数列の加算・2 列の積の和（添字の和や Σa・Σb を S に足す）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#arithmetic-add
    - `lazy-segment-tree-patterns#not-applicable` 載らない作用（区間 chmin と区間和・区間の割り算・区間の並べ替え）と逃げ道：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#not-applicable
    - `lazy-segment-tree-patterns#reformulate` 言い換えてから載せる（しきい値で 0/1 にする・X_i − i・寄与）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/lazy-segment-tree-patterns/#reformulate

## Sparse Table（sparse-table） {#sparse-table}

- id：`sparse-table`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/sparse-table/
- 別名：スパーステーブル、ST 表、静的 RMQ、Disjoint Sparse Table
- 種類：データ構造、区間クエリ、ダブリング・分割統治
- 前提：`doubling`
- サイン：
    - 言い回し：配列が変わらず、区間の最小値・最大値・gcd を非常に多く聞かれる
    - 制約：クエリが 10^6 級で、1 回 O(1) で答えたい
- 節：
    - `sparse-table#what-it-does` 何ができるか（静的・冪等な演算なら O(1)）：https://yuukougun.github.io/kyopro-atlas/ds/sparse-table/#what-it-does
    - `sparse-table#idempotent` なぜ重なってよいか（冪等）と k = ⌊log₂ L⌋：https://yuukougun.github.io/kyopro-atlas/ds/sparse-table/#idempotent
    - `sparse-table#build` 作り方（長さが 2 のべきの区間の表と log の表）：https://yuukougun.github.io/kyopro-atlas/ds/sparse-table/#build
    - `sparse-table#disjoint-sparse-table` 冪等でない演算（2 べきに分けて O(log N)、Disjoint Sparse Table）（発展）：https://yuukougun.github.io/kyopro-atlas/ds/sparse-table/#disjoint-sparse-table

## Segment Tree Beats（segment-tree-beats） {#segment-tree-beats}

- id：`segment-tree-beats`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-beats/
- 別名：beats、Ji Driver Segment Tree、吉司机线段树、区間 chmin 区間和、区間 chmin・chmax
- 種類：データ構造、区間クエリ
- 前提：`lazy-segment-tree`
- サイン：
    - 言い回し：区間 chmin・chmax と区間和を同時に答える
    - 言い回し：区間の各要素を x で割る（切り捨て）操作と区間和
- 節：
    - `segment-tree-beats#what-it-does` 何ができるか（遅延セグメント木に載らない更新）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-beats/#what-it-does
    - `segment-tree-beats#node-data` ノードに持つもの（最大値・真に 2 番目の最大値・最大値の個数・和）と 3 つの場合：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-beats/#node-data
    - `segment-tree-beats#complexity` 計算量（chmin と和だけならならし O((N+Q) log N)、区間加算が混ざると log^2）：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-beats/#complexity
    - `segment-tree-beats#shrinking-values` 値が潰れる操作（割り算・mod・平方根）と、区間を set で管理する別解：https://yuukougun.github.io/kyopro-atlas/ds/segment-tree-beats/#shrinking-values

## クエリの先読み（offline-queries） {#offline-queries}

- id：`offline-queries`　レベル：水　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/
- 別名：オフライン処理、offline queries、クエリ先読み、クエリのソート、区間の種類数、Range Set Query、オンライン強制
- 種類：クエリ処理の工夫、データ構造
- 前提：`fenwick-tree`、`sorting-techniques`
- ACL：`fenwick_tree`
- サイン：
    - 言い回し：区間 [l, r] に含まれる値の種類数を多数のクエリで答える
    - 言い回し：重み w 以下の辺だけを使ったときの連結・X 以下の要素の和をクエリごとに答える
    - 言い回し：クエリどうしが独立で、順番を入れ替えても答えが変わらない
    - 制約：値が 10^9 まで、N, Q ≤ 2×10^5 で、クエリにも新しい値が現れる
- 節：
    - `offline-queries#idea` 考え方（並べ替えて処理し、元の順に戻して出力する）：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#idea
    - `offline-queries#distinct-count` 右端でソートして BIT（区間の種類数：各値の最後の出現位置にだけ 1 を立てる）：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#distinct-count
    - `offline-queries#threshold` しきい値でソート（重み w 以下の辺だけで連結か・X 以下の要素の和）：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#threshold
    - `offline-queries#reverse-time` 時間を逆にする（削除を追加に → グラフの章の Union-Find と連結性）：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#reverse-time
    - `offline-queries#difference-of-times` 答えを 2 時点の差に分ける：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#difference-of-times
    - `offline-queries#compress` 先に全部読んで座標圧縮する：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#compress
    - `offline-queries#online` オンライン強制の見分け方と、そのときの構造（永続・マージソート木・動的セグメント木）：https://yuukougun.github.io/kyopro-atlas/ds/offline-queries/#online

## 平面走査（sweep-line-2d） {#sweep-line-2d}

- id：`sweep-line-2d`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/
- 別名：sweep line、plane sweep、走査線、スイープライン、2 次元クエリ、矩形内の点の数、長方形クエリ
- 種類：クエリ処理の工夫、区間クエリ、ソート・座標圧縮
- 前提：`event-sort`、`offline-queries`、`lazy-segment-tree`
- ACL：`fenwick_tree`、`lazy_segtree`
- サイン：
    - 言い回し：長方形の中にある点の数・和を多数のクエリで答える
    - 言い回し：区間 [p, q] に完全に含まれる区間の数
    - 言い回し：幅 W・高さ D の枠に入る点の最大数
    - 制約：座標が 10^9 まで・点とクエリが 2×10^5 個（2 次元累積和の表は作れない）
- 節：
    - `sweep-line-2d#idea` 考え方（一方の座標で並べ、もう一方をデータ構造で持つ）：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/#idea
    - `sweep-line-2d#rectangle-count` 支配点の数え上げと長方形内の点の数：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/#rectangle-count
    - `sweep-line-2d#intervals-as-points` 区間を 2 次元の点と見る（区間に含まれる区間の数）：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/#intervals-as-points
    - `sweep-line-2d#window-max` 固定幅の窓を動かして区間加算・区間最大（遅延セグメント木）：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/#window-max
    - `sweep-line-2d#boundaries` 同じ座標での処理順・閉区間と半開区間・座標圧縮：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/#boundaries
    - `sweep-line-2d#union-area` 長方形の和集合の面積（区間加算・最小値とその個数）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/sweep-line-2d/#union-area

## Mo's algorithm（mo-algorithm） {#mo-algorithm}

- id：`mo-algorithm`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/
- 別名：Mo、Mo 法、クエリ平方分割、木上の Mo、Mo on tree、時間付き Mo
- 種類：クエリ処理の工夫、区間クエリ
- 前提：`offline-queries`
- サイン：
    - 言い回し：静的な列で、区間ごとの同じ値の組の数・出現回数が条件を満たす値の種類数
    - 言い回し：木のパス上の値の頻度を多数のクエリで答える
    - 制約：N, Q ≈ 2×10^5 で、制限時間が長めにとってある
- 節：
    - `mo-algorithm#what-it-does` 何ができるか（1 要素の出入りで答えを差分更新できる量）：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/#what-it-does
    - `mo-algorithm#ordering` クエリの並べ方と計算量（ブロックの大きさ N/√Q、伸縮の総回数 O(N√Q)）：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/#ordering
    - `mo-algorithm#implementation` 実装の要点（伸ばしてから縮める・奇数ブロックで r を逆順・取得を重くしてよい（値の平方分割））：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/#implementation
    - `mo-algorithm#two-prefixes` 2 つの接頭辞の長さ (X, Y) を区間と見る（黄）：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/#two-prefixes
    - `mo-algorithm#mo-on-tree` 木上の Mo（入りと出の両方を記録した列で、パスを区間にする。LCA を別に足す）（黄）：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/#mo-on-tree
    - `mo-algorithm#variants` 時間付き Mo・ロールバック Mo（発展）：https://yuukougun.github.io/kyopro-atlas/ds/mo-algorithm/#variants

## 平方分割（sqrt-decomposition） {#sqrt-decomposition}

- id：`sqrt-decomposition`　レベル：黄　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/sqrt-decomposition/
- 別名：sqrt decomposition、バケット法、bucket method、根号で場合分け、heavy/light、クエリの平方分割
- 種類：クエリ処理の工夫、データ構造、計算量
- 前提：`segment-tree`
- サイン：
    - 言い回し：次数の合計が 2M・各色の個数の合計が N のように、合計だけが抑えられている
    - 言い回し：位置 i から A_i ずつ先へ跳ぶ・配る
    - 言い回し：区間加算と、区間内の x 以上の要素の個数
    - 制約：制限時間が長めで、O(N√N) ≈ 10^8 なら間に合う
- 節：
    - `sqrt-decomposition#buckets` 配列のバケット分割（丸ごと入るブロックはタグ、端は要素ごと）：https://yuukougun.github.io/kyopro-atlas/ds/sqrt-decomposition/#buckets
    - `sqrt-decomposition#heavy-light` 根号で場合分け（合計が抑えられた量の大小で分ける）：https://yuukougun.github.io/kyopro-atlas/ds/sqrt-decomposition/#heavy-light
    - `sqrt-decomposition#query-buckets` クエリの平方分割（√Q 個ごとに作り直し、未反映の分は愚直に補正する）：https://yuukougun.github.io/kyopro-atlas/ds/sqrt-decomposition/#query-buckets
    - `sqrt-decomposition#implementation` 実装の要点（ブロック番号・同じブロックの場合・タグの押し下げ・B の選び方）：https://yuukougun.github.io/kyopro-atlas/ds/sqrt-decomposition/#implementation

## 並列二分探索（parallel-binary-search） {#parallel-binary-search}

- id：`parallel-binary-search`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/parallel-binary-search/
- 別名：parallel binary search、整体二分、全クエリの二分探索を同時に進める
- 種類：クエリ処理の工夫、二分探索
- 前提：`binary-search-answer`、`offline-queries`
- サイン：
    - 言い回し：多数のクエリが、それぞれ何回目の操作で条件を満たすようになるかを問う
    - 言い回し：最初の t 回の操作の後に条件を満たす最小の t を、クエリごとに答える
- 節：
    - `parallel-binary-search#what-it-does` 何ができるか（オフラインで全クエリの二分探索を一斉に進める）：https://yuukougun.github.io/kyopro-atlas/ds/parallel-binary-search/#what-it-does
    - `parallel-binary-search#procedure` 手順（各段で mid の順にクエリを並べ、過程を 1 回流して判定する）と計算量：https://yuukougun.github.io/kyopro-atlas/ds/parallel-binary-search/#procedure
    - `parallel-binary-search#with-union-find` Union-Find と組む例（最初の t 本の辺で条件を満たすか）：https://yuukougun.github.io/kyopro-atlas/ds/parallel-binary-search/#with-union-find
    - `parallel-binary-search#alternatives` 代わりの手（部分永続 Union-Find・併合過程の木）：https://yuukougun.github.io/kyopro-atlas/ds/parallel-binary-search/#alternatives

## CDQ 分割統治（cdq-divide-and-conquer） {#cdq-divide-and-conquer}

- id：`cdq-divide-and-conquer`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/cdq-divide-and-conquer/
- 別名：CDQ divide and conquer、時系列の分割統治、オフラインの分割統治、3 次元の支配点の数え上げ
- 種類：クエリ処理の工夫、ダブリング・分割統治
- 前提：`divide-and-conquer`、`fenwick-tree`
- サイン：
    - 言い回し：3 つの値すべての大小関係を満たす組を数える
    - 言い回し：点の追加と長方形の質問が混ざるが、オフラインでよい
- 節：
    - `cdq-divide-and-conquer#what-it-does` 何ができるか（時系列の分割統治で 1 次元を消す）：https://yuukougun.github.io/kyopro-atlas/ds/cdq-divide-and-conquer/#what-it-does
    - `cdq-divide-and-conquer#procedure` 手順（左の更新 → 右のクエリを平面走査で処理する）と計算量 O(N log^2 N)：https://yuukougun.github.io/kyopro-atlas/ds/cdq-divide-and-conquer/#procedure
    - `cdq-divide-and-conquer#library` 自作するときの要点と Library Checker：https://yuukougun.github.io/kyopro-atlas/ds/cdq-divide-and-conquer/#library
    - `cdq-divide-and-conquer#alternatives` 代わりの手（座標が小さいなら 2 次元 BIT、更新がなければ平面走査）：https://yuukougun.github.io/kyopro-atlas/ds/cdq-divide-and-conquer/#alternatives

## 永続データ構造（persistent-data-structures） {#persistent-data-structures}

- id：`persistent-data-structures`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/persistent-data-structures/
- 別名：persistent data structure、永続、版の木、永続スタック、永続セグ木、経路コピー、path copying、操作の巻き戻し
- 種類：データ構造、クエリ処理の工夫
- 前提：`segment-tree`、`stack-techniques`
- サイン：
    - 言い回し：状態を保存し、あとで読み込んで続きの操作をする
    - 言い回し：配列を丸ごとコピーする操作と、1 点更新・区間和が混ざる
    - 言い回し：時刻 t の時点での区間の値の分布
- 節：
    - `persistent-data-structures#version-tree` 版の木（追加は子を作る・削除は親へ戻る・保存は頂点を覚える）：https://yuukougun.github.io/kyopro-atlas/ds/persistent-data-structures/#version-tree
    - `persistent-data-structures#path-copying` 経路コピー（1 回の更新で O(log N) 個のノードを新しく作る。丸ごとのコピーは根の指し替え）：https://yuukougun.github.io/kyopro-atlas/ds/persistent-data-structures/#path-copying
    - `persistent-data-structures#partial-vs-full` 部分永続と完全永続：https://yuukougun.github.io/kyopro-atlas/ds/persistent-data-structures/#partial-vs-full
    - `persistent-data-structures#offline-version-tree` 操作の版を木にしてオフラインで処理する（版の木の DFS と取り消し）：https://yuukougun.github.io/kyopro-atlas/ds/persistent-data-structures/#offline-version-tree
    - `persistent-data-structures#prefix-versions` 接頭辞ごとの版で区間の K 番目・x 以下の個数をオンラインで求める（発展）：https://yuukougun.github.io/kyopro-atlas/ds/persistent-data-structures/#prefix-versions

## マージソート木（merge-sort-tree） {#merge-sort-tree}

- id：`merge-sort-tree`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/merge-sort-tree/
- 別名：Merge Sort Tree、マージソートツリー、領域木、Range Tree
- 種類：データ構造、区間クエリ
- 前提：`segment-tree`、`binary-search`
- サイン：
    - 言い回し：区間内で X 以下の要素の個数・和を多数のクエリで答える
    - 言い回し：前の答えで次のクエリが決まる（オンライン強制）
- 節：
    - `merge-sort-tree#idea` 必要になる場面とアイデア：https://yuukougun.github.io/kyopro-atlas/ds/merge-sort-tree/#idea
    - `merge-sort-tree#build` 作り方（子の列をマージする）とメモリ O(N log N)：https://yuukougun.github.io/kyopro-atlas/ds/merge-sort-tree/#build
    - `merge-sort-tree#query` クエリの手順（O(log N) 個のノードで二分探索）と累積和で和も：https://yuukougun.github.io/kyopro-atlas/ds/merge-sort-tree/#query
    - `merge-sort-tree#bit-per-level` 各段に BIT を持たせる（先読みと組む）（発展）：https://yuukougun.github.io/kyopro-atlas/ds/merge-sort-tree/#bit-per-level

## Wavelet Matrix（wavelet-matrix） {#wavelet-matrix}

- id：`wavelet-matrix`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/wavelet-matrix/
- 別名：ウェーブレット行列、Wavelet Tree、区間の K 番目
- 種類：データ構造、区間クエリ、ビット演算
- 前提：`merge-sort-tree`、`bit-operations`
- サイン：
    - 言い回し：区間の K 番目に小さい値をオンラインで答える
    - 言い回し：長方形（添字の範囲 × 値の範囲）の中の点の数
- 節：
    - `wavelet-matrix#what-it-does` 何ができるか（区間の K 番目・x 未満の個数・和）：https://yuukougun.github.io/kyopro-atlas/ds/wavelet-matrix/#what-it-does
    - `wavelet-matrix#build` 段の作り方（上位ビットから安定に振り分ける）：https://yuukougun.github.io/kyopro-atlas/ds/wavelet-matrix/#build
    - `wavelet-matrix#usage` ライブラリでの使い方と、マージソート木・永続セグメント木との比較：https://yuukougun.github.io/kyopro-atlas/ds/wavelet-matrix/#usage

## Binary Trie（binary-trie） {#binary-trie}

- id：`binary-trie`　レベル：青　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/ds/binary-trie/
- 別名：二分トライ、2 進 Trie、ビット Trie、XOR Trie、XOR の最小化
- 種類：データ構造、ビット演算
- 前提：`trie`、`bit-operations`
- サイン：
    - 言い回し：x を選んで XOR の最大値を最小にする・集合の中で x との XOR が最小の要素
    - 言い回し：追加・削除のたびに、任意の 2 要素の XOR の最小値を答える
    - 言い回し：全体に XOR をかけてから K 番目に小さい値
    - 制約：A_i < 2^30 で、追加・削除・質問が合わせて 2×10^5 回程度
- 節：
    - `binary-trie#build` 作り方（上位 bit からたどる二分木・ノードに個数）：https://yuukougun.github.io/kyopro-atlas/ds/binary-trie/#build
    - `binary-trie#xor-min-max` XOR の最小・最大（同じ側を優先して降りる）：https://yuukougun.github.io/kyopro-atlas/ds/binary-trie/#xor-min-max
    - `binary-trie#kth-and-global-xor` K 番目と全体への XOR（bit ごとの反転フラグ）：https://yuukougun.github.io/kyopro-atlas/ds/binary-trie/#kth-and-global-xor
    - `binary-trie#implicit` 明示的に作らない Binary Trie（上位 bit で分ける再帰）：https://yuukougun.github.io/kyopro-atlas/ds/binary-trie/#implicit

## 平衡二分探索木と pb_ds の tree（balanced-bst） {#balanced-bst}

- id：`balanced-bst`　レベル：発展　段階：draft　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/ds/balanced-bst/
- 別名：平衡二分木、balanced binary search tree、treap、implicit treap、RBST、splay、pb_ds tree、order statistics tree
- 種類：データ構造
- 前提：`ordered-set`
- サイン：
    - 言い回し：列の途中（位置で指定）への挿入・削除と、区間の反転
    - 言い回し：K 番目の値と、値の順位の両方をオンラインで答える
- 節：
    - `balanced-bst#what-it-does` 何ができるか（位置で分割・結合する列の構造）：https://yuukougun.github.io/kyopro-atlas/ds/balanced-bst/#what-it-does
    - `balanced-bst#treap` treap の split・merge と、深さが期待 O(log N) になる理由：https://yuukougun.github.io/kyopro-atlas/ds/balanced-bst/#treap
    - `balanced-bst#library` 自作するときの要点と Library Checker：https://yuukougun.github.io/kyopro-atlas/ds/balanced-bst/#library
    - `balanced-bst#pbds` pb_ds の tree（order_of_key・find_by_order。重複は値と通し番号の組にする）：https://yuukougun.github.io/kyopro-atlas/ds/balanced-bst/#pbds
    - `balanced-bst#alternatives` 代わりの手（BIT 上の二分探索・連結リスト・逆順の処理と BIT）：https://yuukougun.github.io/kyopro-atlas/ds/balanced-bst/#alternatives

## 見慣れないデータ構造の名前と用途（advanced-ds-catalog） {#advanced-ds-catalog}

- id：`advanced-ds-catalog`　レベル：—　段階：stub　type：hub
- URL：https://yuukougun.github.io/kyopro-atlas/ds/advanced-ds-catalog/
- 別名：セグ木マージ、segment tree merging、2 次元セグ木、2 次元 BIT、K-D tree、併合可能なヒープ、meldable heap、skew heap、leftist heap、Fast Set、Fractional Cascading、析合木、Kinetic Segment Tree
- 種類：案内、データ構造
- 節：
    - `advanced-ds-catalog#table` 名前・何ができるか・代わりになる手の表：https://yuukougun.github.io/kyopro-atlas/ds/advanced-ds-catalog/#table
    - `advanced-ds-catalog#meldable-heap` 併合可能なヒープ（skew heap・leftist heap・ランダム化ヒープ。マージテクで足りることが多い）：https://yuukougun.github.io/kyopro-atlas/ds/advanced-ds-catalog/#meldable-heap
    - `advanced-ds-catalog#elsewhere` ほかのページにあるもの（木の動的な構造は木の章、CDQ 分割統治・時間付き Mo・Li Chao Tree は各ページ）：https://yuukougun.github.io/kyopro-atlas/ds/advanced-ds-catalog/#elsewhere
