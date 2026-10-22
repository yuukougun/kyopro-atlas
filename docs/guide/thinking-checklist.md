---
id: thinking-checklist
title: 詰まったときの発想リスト
aliases: [考察の引き出し, 考察の手順, 発想の型, 方針が立たないとき, 考察の型の一覧, 典型考察, 考察テクニック]
type: guide
field: guide
chapter: コンテストと考察
order: 100
level: null
kind: [案内, 考察]
prerequisites: []
related: [symmetry-pigeonhole-casework, reformulation, fix-variable, contribution, complement, invariant, parity, reverse-thinking, construction, binary-search-answer, bitwise-independence, periodicity, greedy-basics, game-basics, stl-containers, stress-testing#experiment, reverse-index-constraints, reverse-index-signs, contest-strategy#switching]
summary: 方針が立たないときに、問題の形から試す考察の型を引き、上から順に問いを当てられる。各型は考察の章と手法のページへつなぐ入口で、型の説明の本体はそちらにある。
complexity: null
signs: []
acl: []
sections:
  - {title: 使い方, anchor: how-to-use}
  - {title: 総和を求める, anchor: shape-sum}
  - {title: 個数を数える, anchor: shape-count}
  - {title: 操作できるか・最小回数, anchor: shape-operation}
  - {title: 最大・最小, anchor: shape-optimize}
  - {title: 1 つ作る（構築）, anchor: shape-construct}
  - {title: ほかの型の行き先, anchor: other-types}
  - {title: 誤読を疑う, anchor: q-misreading}
  - {title: 制約から計算量を逆算する, anchor: q-constraints}
  - {title: 小さいケースを試す, anchor: q-small-cases}
  - {title: 言い換えの問い, anchor: q-rephrase}
  - {title: 変わらないものを探す, anchor: q-invariants}
  - {title: 仮定を足して外す, anchor: q-assumptions}
  - {title: 有名な手法を当てはめる, anchor: q-known-methods}
  - {title: 一度離れる, anchor: q-step-away}
  - {title: 問題集の考察の型との対応, anchor: book-mapping}
stage: draft
updated: 2026-10-22
---

!!! abstract "要点"
    - **何のページか**：方針が立たないときに、問題の形から試す考察の型を引き、上から順に問いを当てられる。各型は考察の章と手法のページへつなぐ入口で、型の説明の本体はそちらにある。
    - **いつ引くか**：
        - 問題文を読んで、全探索より速い方法が浮かばない。
        - 手法の名前は知っているが、この問題のどこに使うのかが見えない。
        - 方針を立てたが、小さい例で答えが合わない。
    - **使い方**：まず問われているものの形（総和・個数・操作・最大最小・構築）の表から試す型を選ぶ。表で決まらなければ、[誤読を疑う](#q-misreading)から順に問いを当てる。
    - **前提**：なし。制約から計算量を見積もる方法は[計算量の見積もり](../basics/complexity-estimation.md)にある。

<!-- textlint-disable -->
別名：考察の引き出し・考察の手順・発想の型・方針が立たないとき・考察の型の一覧・典型考察・考察テクニック
<!-- textlint-enable -->

詰まったときの発想リストは、方針が立たない問題に当てる問いを、問題の形ごとの表と、順にたどる問いの列の 2 つにまとめたものである。どの行も、型の説明は考察の章（[言い換えの典型](../thinking/reformulation.md)・[主客転倒・寄与](../thinking/contribution.md)など）と手法のページに任せ、ここでは「この形ならこの型を試す」という対応と、そのページへのリンクだけを置く。問題文の言い回しから手法を探すときは[逆引き辞典（言い回しから）](reverse-index-signs.md)、混同しやすい手法から 1 つを選ぶときは[似た手法の使い分け](method-comparison.md)を使う。

## 使い方 {#how-to-use}

発想リストは 2 段で使う。1 段目は**問われているものの形**から試す型を選ぶ表で、2 段目は形で決まらないときに**上から順に当てる問い**である。

1. **問われているものの形を決める**：出力するものを、総和・条件を満たすものの個数・操作の可否や最小回数・最大値や最小値・条件を満たすもの 1 つのどれかに分ける。どれにも当たらなければ[ほかの型の行き先](#other-types)を見る。
2. **形の表から型を試す**：表の左の列から問題に近い行を探し、行の問いを自分の問題に当ててみる。答えが「はい」なら、リンク先のページで条件と手順を確かめる。
3. **表で決まらなければ問いを順にたどる**：[誤読を疑う](#q-misreading)から[一度離れる](#q-step-away)まで、8 つの問いを上から当てる。前の問いほど確かめる手間が少なく、飛ばして後で気づいたときの損が大きいので、この順に並べた。

1 つの問題が複数の形を持つこともあり（「操作の最小回数の総和」など）、そのときは両方の表を試す。

表で選んだ型が外れたら、同じ表の別の行を試し、それでも進まなければ問いの列に移る。問いの列は、コンテスト中に回す順として[詰まったとき](contest-strategy.md#when-stuck)にも短く載せてある。

## 総和を求める {#shape-sum}

全ペア・全区間・全部分集合のような「すべての対象についての和」は、対象を 1 つずつ列挙すると $O(N^2)$ 以上になる。多くの場合、要素の側から「この要素は何回数えられるか」を数えれば線形に近い時間で済む。

| 問題の形 | 試す問い | ページ |
| --- | --- | --- |
| 全ペア・全区間についての和 | 各要素は何個の対象に数えられるか？ | [数える対象を入れ替える](../thinking/contribution.md#swap-roles) |
| 全ペアの差の絶対値の和 | ソートすれば絶対値の符号が決まるか？ | [ソートで符号を決める](../thinking/contribution.md#sort-signs) |
| 各数の桁の和・約数の個数の和 | 各桁・各約数は何回現れるか？ | [各桁・各約数の寄与](../thinking/contribution.md#digits-divisors) |
| 全区間の最大値・最小値の和 | 各要素が最大になる区間はいくつか？ | [各要素が最大・最小になる回数](../thinking/contribution.md#max-min-count) |
| 全ペアの XOR の和 | bit ごとに 0 と 1 の個数で数えられるか？ | [bit ごとの寄与](../basics/bitwise-independence.md#per-bit-contribution) |
| 添字の小さい順の組の積の和 | 全体の和の 2 乗から対角を引いて半分にできるか？ | [対称性で計算を半分にする](../thinking/symmetry-pigeonhole-casework.md#symmetry) |
| 二重の Σ の和 | 和の順序を入れ替えると内側が式で閉じるか？ | [和の順序の入れ替え](../math/sigma-manipulation.md#swap-order) |
| 期待値・すべての場合の総和 | 指示確率変数の和に分けられるか？ | [期待値の線形性](../comb/linearity-of-expectation.md#linearity) |

表の行は、どれも「対象 × 要素の表を、行ごとではなく列ごとに足す」という同じ発想の変形である。和を mod で求めるときは、要素ごとの回数が大きくなるので掛ける前に余りを取る。

## 個数を数える {#shape-count}

条件を満たすものの個数は、条件をそのまま数えにくいときに、数えやすい別の集合に言い換える。数えにくいときは、補集合・一部の固定・累積和の余りのような、数えやすい集合への言い換えを試す。

| 問題の形 | 試す問い | ページ |
| --- | --- | --- |
| 「少なくとも 1 つ」「〜でない」 | 全体から補集合を引けば易しいか？ | [全体 − 補集合](../thinking/complement.md#whole-minus-complement) |
| 条件が 2〜3 個重なる | 包除で重なりを足し戻せるか？ | [2〜3 条件の包除](../thinking/complement.md#two-conditions) |
| 3 つ組・2 つ組を数える | 真ん中を固定すると左右が独立になるか？ | [真ん中を固定する](../thinking/fix-variable.md#fix-middle) |
| 区間の和が $K$・$M$ の倍数 | 累積和の差（余りが等しい組）に直せるか？ | [累積和と連想配列で区間を数える](../basics/prefix-sum-counting.md#same-remainder) |
| 「ちょうど $K$」を数える | 「$K$ 以下」から「$K-1$ 以下」を引けるか？ | [「ちょうど」を「以下」の差で数える](../comb/counting-mindset.md#exactly-vs-at-most) |
| 数える対象が複雑 | 1 対 1 に対応する易しい対象があるか？ | [対応づけ](../comb/counting-bijection.md#bijection) |
| 並べ方・選び方を数える | 決まった順に並ぶ $k$ 個は、全体の $1/k!$ として数えられるか？ | [順序を固定して数える](../comb/counting-fix-order.md#relative-order) |
| 式が立たない | 先頭から決めていく DP の状態は何か？ | [DP の 4 つの要素](../dp/dp-basics.md#four-parts) |

式を立てたら、小さい $N$ の全探索の値と比べてから使う（[小さいケースの全探索で式を検算する](../comb/counting-mindset.md#verify-small)）。数え上げ全体の手順は[数え上げの考え方](../comb/counting-mindset.md#procedure)にある。

## 操作できるか・最小回数 {#shape-operation}

「操作を繰り返して目標の状態にできるか」「最小で何回か」という問題は、操作そのものを追うと状態が爆発する。操作で**変わらない量**からは可否の必要条件が、**必ず減る量**からは操作が必ず止まることと回数の上界が、1 回で減る幅に上限がある量からは回数の下界が手に入る。

| 問題の形 | 試す問い | ページ |
| --- | --- | --- |
| 目標の状態にできるか | 操作で変わらない量（和の余り・偶奇・XOR）は何か？ | [不変量で必要条件を見つける](../thinking/invariant.md#necessary-and-sufficient) |
| ちょうど $K$ 回の操作 | $K$ と目標までの差の偶奇がそろうか？ | [ちょうど K 回なら偶奇がそろう](../thinking/parity.md#exactly-k) |
| 操作は必ず終わるか・回数の上限 | 1 回ごとに必ず減る量はあるか？ | [単調量で操作回数を抑える](../thinking/invariant.md#monovariant) |
| 操作の順序が自由 | 順序によらないなら、都合のよい順に並べ替えられるか？ | [都合のよい順で考える](../thinking/invariant.md#order-independence) |
| 操作の結果から元を復元する | 最後の操作を特定して取り除けるか？ | [最後の操作を特定して逆再生する](../thinking/reverse-thinking.md#undo-last) |
| 辺・要素を削除していく | 逆順に見て追加にできるか？ | [削除を逆順の追加にする](../thinking/reverse-thinking.md#delete-to-add) |
| 区間に一律に足す・隣を入れ替える | 差分列・転倒数に言い換えられるか？ | [操作の言い換え](../thinking/reformulation.md#operations) |
| 任意の 2 つを入れ替える最小回数 | 置換の巡回の個数で決まるか？ | [置換の巡回分解](../comb/permutation-cycles.md#min-swaps) |
| $10^{18}$ 回のような巨大な回数 | 状態が有限で、周期に入るか？ | [尾と周期](../basics/periodicity.md#rho) |
| 状態の数が少ない | 状態を頂点、操作を辺にして BFS できるか？ | [何を頂点にするか](../graph/graph-modeling.md#what-to-vertex) |

[不変量](../guide/glossary.md#invariant)から出るのは必要条件だけである。十分であることは、実際に目標を作る手順を示して確かめる（[構築問題の考え方](../thinking/construction.md#necessary-conditions)）。

## 最大・最小 {#shape-optimize}

最大値・最小値を求める問題は、「答えを $x$ にできるか」という判定に直すか、答えの上界を示してそれを達成する例を作るかの 2 通りで攻めることが多い。どちらでも決まらなければ、貪欲法か DP で直接求める。

| 問題の形 | 試す問い | ページ |
| --- | --- | --- |
| 最大値の最小化・最小値の最大化 | 「答えを $x$ にできるか」は $x$ について単調か？ | [最大値の最小化・最小値の最大化](../basics/binary-search-answer.md#minimax) |
| 答えの見当が付く | 「答え ≤ U」を示し、U を達成する例を作れるか？ | [上界・下界を示して達成する例を作る](../thinking/construction.md#bound-and-construct) |
| その場でよいものを選び続けたい | 最適解を貪欲の選び方に近づけても悪くならないか？ | [正当性の示し方](../basics/greedy-basics.md#proof) |
| 並べる順序で値が変わる | 隣り合う 2 つを入れ替えたときの差で比較が決まるか？ | [隣接交換で比較を導く](../basics/exchange-argument.md#adjacent-swap) |
| 2 つ以上の量を同時に最適化 | 片方（最大値など）を固定すると残りが易しくなるか？ | [最大値を固定して残りを最適化する](../thinking/fix-variable.md#fix-maximum) |
| XOR などの bit 演算の最大 | 上の bit から順に決められるか？ | [上の bit から決める貪欲](../basics/bitwise-independence.md#top-down) |
| 平均・比の最大 | 「平均 ≥ x」を「Σ(a − x) ≥ 0」に直せるか？ | [平均・中央値の最大化](../basics/fractional-binary-search.md#average) |
| 辞書順で最小のもの | 先頭から 1 文字ずつ、残りが作れる範囲で最小を選べるか？ | [辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md#why-front) |
| 貪欲が怪しい | 小さいケースの全探索と比べて反例が出ないか？ | [反例の探し方](../basics/greedy-basics.md#counterexamples) |

貪欲法は正しさを確かめずに書くと WA になりやすい。反例が出たら DP に切り替える（[貪欲が失敗する例と DP への切り替え](../basics/greedy-basics.md#when-greedy-fails)）。

## 1 つ作る（構築） {#shape-construct}

条件を満たすものを 1 つ出力する問題（構築問題）では、答えが 1 つに決まらないので、自分で規則を決めて作る。手で作れる小さいケースから始め、作れない場合の条件を先に挙げる。

| 問題の形 | 試す問い | ページ |
| --- | --- | --- |
| 規則が見えない | $N = 1, 2, 3, 4$ で手で作ると規則が見えるか？ | [小さい N で作って規則を一般化する](../thinking/construction.md#small-cases) |
| 作れないときは -1 を出力 | 作れるための必要条件は何か？ それは十分か？ | [必要条件を先に挙げる](../thinking/construction.md#necessary-conditions) |
| 最大の個数・最大の値で作る | 上界を示し、ちょうど達成する並べ方を作れるか？ | [上界・下界を示して達成する例を作る](../thinking/construction.md#bound-and-construct) |
| 条件を満たすグラフを作る | DFS 木・BFS 木の性質を使えるか？ | [DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md#dfs-tree) |
| 距離・次数の情報から木を作る | 最も近い頂点どうしを辺で結べるか？ | [木の構築・復元](../tree/tree-construction.md#from-distances) |
| 作った答えが正しいか不安 | 出力を検査するプログラムを書けるか？ | [出力を検査するプログラムで確かめる](../thinking/construction.md#checker) |

ABC でよく出る構築の型（手順を出力する・数列を作る・グラフを作る）は[ABC の構築の型](../thinking/construction.md#abc-patterns)にまとめてある。

## ほかの型の行き先 {#other-types}

5 つの形に当てはまらない問題や、形とは別の手がかりがある問題の行き先をまとめる。

| 手がかり | 試す問い | ページ |
| --- | --- | --- |
| 2 人が交互に手を打つゲーム | 終局から勝ち負けを DP で埋められるか？ | [必勝・必敗の定義](../comb/game-basics.md#win-lose) |
| ゲームの状態が大きすぎる | 総手数の偶奇や真似をする戦略で決まらないか？ | [真似戦略・ペアリング戦略](../comb/game-basics.md#mirror-strategy) |
| K 番目に小さい値 | 「x 以下が K 個以上か」を数えて二分探索できるか？ | [K 番目の値](../basics/kth-value.md#why-count) |
| 確率を求める | 対称性で、どれも同じ確率にならないか？ | [対称性で確率を求める](../comb/probability-symmetry.md#symmetry) |
| x 座標と y 座標・各 bit | 独立に分けて別々に解けるか？ | [独立に分解する](../thinking/reformulation.md#independence) |
| 値の種類が少ない・余りが少ない | 鳩の巣原理で、必ず一致が起きる回数を抑えられるか？ | [鳩の巣原理](../thinking/symmetry-pigeonhole-casework.md#pigeonhole) |
| 端の場合や大小関係で振る舞いが変わる | 場合を分けると、それぞれが易しくなるか？ | [場合分け](../thinking/symmetry-pigeonhole-casework.md#casework) |
| 関係・移動・依存が書かれている | 何を頂点と辺にすればグラフの問題になるか？ | [グラフへの帰着](../graph/graph-modeling.md#what-to-edge) |
| 追加・削除・検索のクエリ | どの操作を速くしたいか、どのコンテナが合うか？ | [操作とコンテナの計算量の早見表](../ds/stl-containers.md#complexity-table) |
| 何を全探索するかで迷う | いくつか決めれば残りが計算で決まらないか？ | [何を全探索するか](../basics/brute-force.md#what-to-enumerate) |

問題文の特定の言い回し（「部分列」「mex」「区間」など）から引くときは、題材ごとのページ（[区間](../patterns/interval.md)・[順列と置換](../patterns/permutation.md)など）と[逆引き辞典（言い回しから）](reverse-index-signs.md#by-phrase)の方が早い。

## 誤読を疑う {#q-misreading}

方針が立たない原因は、思うより多く問題の読み違いにある。誤読は確かめる手間が小さい。気づかずに進むと考察の時間がすべて無駄になるので、問いの列の最初に置く。問題文を読み直し、次の点を自分の言葉で書き出す。

- **大きさ**：$N$ の上限はいくつか。値の上限と個数の上限を取り違えていないか。
- **構造**：グラフは木か、一般のグラフか。辺に向きはあるか。連結である保証はあるか。
- **向き**：求めるのは最大か最小か。等号を含む「以上」と含まない「より大きい」のどちらか。
- **数**：「ちょうど $K$」か「$K$ 以下」か。同じ値が重複しうるか。
- **連続性**：選ぶのは連続した部分（部分文字列・区間）か、飛び飛びでよい部分列か（[部分文字列と部分列](../string/string-basics.md#substring-vs-subsequence)）。
- **出力**：mod を取るか。答えがないときに何を出力するか。複数テストケースか。

最後に、入力例の 1 つを自分の解釈で手計算し、出力例と一致するかを確かめる。一致しなければ、解釈のどこかが違っている。

## 制約から計算量を逆算する {#q-constraints}

制約の最大値を計算量の式に入れ、C++ で 1 秒に $10^8$ 回前後に収まる式を探すと、想定される解法の計算量が見える。たとえば $N \le 2 \times 10^5$ なら $O(N \log N)$・$O(N \sqrt{N})$ 程度まで、$N \le 20$ なら $O(2^N N)$ が候補になり、手法の候補が絞れる。表は[制約 → 許される計算量 → 疑う手法の表](../basics/complexity-estimation.md#constraint-table)にある。

制約については、次の問いを当てる。

- **最大値を入れたか**：$N$ と $Q$ のように制約が 2 つあれば、両方の最大値を同時に入れたか。
- **不自然に小さい変数はないか**：$N$ は大きいのに $K \le 10$ や値が $10^6$ 以下のように、1 つだけ小さい変数があれば、そこを全探索するか状態に持つ合図である。
- **答えの候補は少なくないか**：$N$ ではなく答えの候補や値の種類で全探索すると、速く済むことがある（[候補の数で見積もる](../basics/complexity-estimation.md#count-candidates)）。
- **複数テストケースの合計は抑えられているか**：$\sum N$ の上限があれば、合計で見積もる（[複数テストケースは合計で見積もる](../basics/complexity-estimation.md#multiple-testcases)）。

ただし、制約に縛られすぎない。制約が緩くても想定より速い解法が素直なことはあるし、ならし計算量で見積もると間に合う解法もある（[ならし計算量](../basics/complexity-estimation.md#amortized)）。制約の帯ごとのページの一覧は[逆引き辞典（制約・計算量から）](reverse-index-constraints.md#pages-by-constraint)にある。

## 小さいケースを試す {#q-small-cases}

$N = 1, 2, 3$ や極端な入力（全部同じ値・単調な列・パス状の木）で、答えを手で出してみる。手を動かすと、答えが入力のどの量で決まるかが見えることが多い。手で追い切れなければ、[愚直解](../guide/glossary.md#naive-solution)を書いて小さい $N$ の答えを全部出し、表にして規則を探す（[実験で規則を予想する](stress-testing.md#experiment)）。

- **規則は見えるか**：答えの列を並べ、差・比・偶奇・周期を見る。数列なら OEIS で検索すると、名前の付いた数列のことがある。
- **図にしたか**：数直線・グリッド・グラフ・折れ線に描くと、言葉では見えない構造が見える。
- **規則は正しいか**：小さいケースで見つけた規則は予想にすぎない。なぜ成り立つかを示すか、もう少し大きい $N$ でも全探索と一致することを確かめる（[必要条件と十分条件](../math/proof-patterns.md#necessary-sufficient)）。

貪欲法や式の検算にも同じ道具を使う（[反例の探し方](../basics/greedy-basics.md#counterexamples)・[小さいケースの全探索で式を検算する](../comb/counting-mindset.md#verify-small)）。

## 言い換えの問い {#q-rephrase}

問題をそのまま解けないときは、同じ答えになる別の問題に書き直す。言い換えの型は次の問いにまとめられる。言い換えの具体例の一覧は[言い換えの一覧表](../thinking/reformulation.md#table)にある。

| 問い | 言い換えの例 | ページ |
| --- | --- | --- |
| 答えを決め打ちすると、判定は易しいか？ | 最小値の最大化 → 「全部 $x$ 以上にできるか」 | [判定の単調性を確かめる](../basics/binary-search-answer.md#monotonicity) |
| 後ろから見ると、選択肢が 1 つに決まるか？ | 後ろの値から順に決める | [後ろから決めると一意になる](../thinking/reverse-thinking.md#decide-from-back) |
| 1 つを固定すると、残りが易しくなるか？ | 3 つ組 → 真ん中を固定して左右の積 | [一部を固定して数える](../thinking/fix-variable.md#fix-middle) |
| 要素の側から数えられるか？ | 全区間の和 → 各要素が含まれる区間の数 | [主客転倒・寄与](../thinking/contribution.md#swap-roles) |
| 補集合の方が数えやすいか？ | 「少なくとも 1 つ」→ 全体 − 「1 つもない」 | [余事象](../thinking/complement.md#whole-minus-complement) |
| 添字と値を混ぜた式を分けられるか？ | $A_j - A_i = j - i$ → $A_j - j = A_i - i$ | [i と j を分離する](../thinking/reformulation.md#separate-indices) |
| 独立な部分に分けられるか？ | x と y・bit ごと・連結成分ごと | [独立に分解する](../thinking/reformulation.md#independence) |
| 操作を点の操作に直せるか？ | 区間への一律の加算 → 差分列の 2 点の変更 | [操作の言い換え](../thinking/reformulation.md#operations) |
| 対称性で半分にできるか？ | $N \le M$ に入れ替える | [対称性で場合を減らす](../thinking/symmetry-pigeonhole-casework.md#symmetry-cases) |
| グラフにすると、知っている問題になるか？ | 移動・依存・同じであるという関係を辺にする | [グラフへの帰着](../graph/graph-modeling.md#what-to-vertex) |

言い換えた後は、元の問題と答えが一致するかを小さいケースで確かめる。条件を 1 つ落とした言い換え（必要条件だけを満たすもの）になっていることがある。

## 変わらないものを探す {#q-invariants}

操作や移動を繰り返す問題では、何が変わらないか、何が必ず一方向に変わるかを探す。見つかった量は、目標に届かない理由（必要条件）か、操作回数の上限・下限になる。

- **和・余り・XOR は変わらないか**：1 回の操作で和や XOR がどう変わるかを式で書く。変わらないなら、初めと目標で値が違えば不可能である（[不変量で必要条件を見つける](../thinking/invariant.md#necessary-and-sufficient)）。
- **偶奇は変わらないか**：1 歩ごとに座標の和の偶奇が入れ替わる、操作ごとに個数の偶奇が変わる、のような形を探す（[1 歩ごとに偶奇が入れ替わる](../thinking/parity.md#alternating)）。グリッドなら市松模様の色を塗る（[市松模様の偶奇](../thinking/parity.md#checkerboard)）。
- **gcd は変わらないか**：引き算や互除法に似た操作なら、gcd が保たれることが多い（[操作で gcd が変わらない](../math/proof-patterns.md#gcd-invariant)）。
- **必ず減る量はあるか**：境界の数・転倒数・総和のように、0 以上の整数のまま 1 回ごとに必ず 1 以上減る量があれば、操作は有限回で終わり、回数の上限も出る（[単調量で操作回数を抑える](../thinking/invariant.md#monovariant)）。
- **状態は有限か**：状態の種類が有限なら、いつか同じ状態に戻って周期に入る（[尾と周期](../basics/periodicity.md#rho)）。

不変量は必要条件しか与えないので、十分であることは構築で示す。

## 仮定を足して外す {#q-assumptions}

一般の場合が難しいときは、問題を易しくする仮定を自分で足して解き、その解き方を手がかりに仮定を外していく。

- **どんな仮定なら解けるか**：値がすべて異なる、$N$ が偶数、値が 0 と 1 だけ、木がパス（一直線）、操作が 1 回だけ、など。仮定を足した問題が解けたら、仮定を外して何が壊れるかを調べる。壊れる部分だけを別に扱えば、元の問題も解けることがある。
- **必要条件を並べると十分にならないか**：答えが「はい」になるのに明らかに必要な条件を、思いつく限り並べる。並べた条件を全部満たすどの入力でも実際に作れると示せたら、その条件の組は必要十分条件である（[必要条件を先に挙げる](../thinking/construction.md#necessary-conditions)）。ここで[必要条件](../guide/glossary.md#necessary-condition)は、答えが「はい」なら必ず成り立つ条件をいう。
- **端の場合を分けたか**：$N = 1$、すべて同じ値、$K = 0$ のような場合を先に分けると、残りの一般の場合に強い仮定が置ける（[場合分け](../thinking/symmetry-pigeonhole-casework.md#casework)）。

## 有名な手法を当てはめる {#q-known-methods}

ここまでの問いで決まらなければ、知っている手法を 1 つずつ当てはめてみる。問題のどの量をどの手法に載せるかを、手法の側から考える逆向きの探し方である。当てはめる順は、軽いものからでよい。

1. **全探索**：何を全探索すれば残りが決まるか。通り数は制約に収まるか（[全探索の設計](../basics/brute-force.md#what-to-enumerate)）。
2. **二分探索**：答えや境界を決め打ちすると判定が易しくならないか（[答えで二分探索](../basics/binary-search-answer.md#monotonicity)）。
3. **累積和・尺取り法**：区間の量を何度も求めていないか（[累積和](../basics/prefix-sum.md)・[尺取り法](../basics/two-pointers.md)）。
4. **貪欲法**：その場でよいものを選んで、正しさを示せるか（[貪欲法の考え方と正当性](../basics/greedy-basics.md#proof)）。
5. **DP**：先頭から決めていくとき、先の選び方を決めるのに何を覚えておけば足りるか（[DP の基本](../dp/dp-basics.md#four-parts)）。
6. **グラフ**：頂点と辺に直すと、最短路・連結性・二部グラフの問題にならないか（[グラフへの帰着](../graph/graph-modeling.md#what-to-vertex)）。
7. **データ構造**：同じ集計を何度も繰り返していないか。区間の集約や順序つきの集合で速くならないか（[STL コンテナの使い分け](../ds/stl-containers.md#complexity-table)・[セグメント木](../ds/segment-tree.md#what-it-does)）。

候補が 2 つ以上浮かんだら[似た手法の使い分け](method-comparison.md)で選ぶ。手法の名前と計算量を一覧で見るなら[早見表](cheatsheet.md)を使う。

## 一度離れる {#q-step-away}

同じ考えを回し続けて進まなくなったら、一度その問題から離れる。考えが 1 つの方針に固まっていると、別の見方に気づきにくいからである。

- **コンテスト中なら**：別の問題を読み、時間をおいて戻る。戻ったときは、それまでに分かったこと（必要条件・小さいケースの答え・試して外れた方針）を紙に書き出してから再開する。見切りの時刻の決め方は[取り組む問題の選び方と切り替え](contest-strategy.md#switching)にある。
- **練習なら**：決めた時間を過ぎたら解説を読む。読む前に、どこまで分かってどこで詰まったかを 1 文で書いておくと、解説のどの部分が自分に足りなかったかがはっきりする（[解説を見るまでの時間](practice-method.md#when-to-read)）。
- **終わった後に**：解けなかった原因を「誤読・知識不足・考察不足・実装の誤り・時間不足」のどれかに分け、どの条件から型を連想できたはずかを記録する（[記録の付け方](practice-method.md#records)）。同じ型で考察不足が続くなら、その型の行から考察の章のページを読み直す。

## 問題集の考察の型との対応 {#book-mapping}

問題集の考察の章で学んだ型を、このサイトのページへ対応づける。対応は節の題名と例題の解答のコード、各ページが扱う範囲から決めた。本の節の中身と完全に一致するとは限らない。

『競技プログラミングの鉄則』（鉄則本）6 章「考察テクニック」の各節は次のページに当たる。

| 本の節 | このサイトのページ |
| --- | --- |
| 6.1 偶奇を考える | [偶奇に着目する](../thinking/parity.md) |
| 6.2 足された回数を考える | [主客転倒・寄与](../thinking/contribution.md) |
| 6.3 上限値を考える | [上界・下界を示して達成する例を作る](../thinking/construction.md#bound-and-construct) |
| 6.4 一手先を考える | [区間スケジューリング](../basics/interval-scheduling.md#why-right-end)・[貪欲法の考え方と正当性](../basics/greedy-basics.md) |
| 6.5 個数を考える | [map で数えながら走査する](../ds/stl-containers.md#counting-map)・[二項係数](../comb/binomial-coefficient.md#meanings)（値ごとの個数を数えてから組を数える） |
| 6.6 後ろから考える | [後ろから・逆順に考える](../thinking/reverse-thinking.md) |
| 6.7 固定して全探索 | [一部を固定して数える](../thinking/fix-variable.md) |
| 6.8 問題を言い換える | [言い換えの典型](../thinking/reformulation.md) |
| 6.9 データの持ち方を工夫する | [反転フラグ](../ds/global-offset.md#flip-flag) |
| 6.10 不変量に着目する | [不変量・単調に変わる量](../thinking/invariant.md) |

『問題解決のための「アルゴリズム×数学」が基礎からしっかり身につく本』5 章「問題解決のための数学的考察」の各節は次のページに当たる。

| 本の節 | このサイトのページ |
| --- | --- |
| 5.2 規則性を考える | [周期性の検出](../basics/periodicity.md)・[小さいケースを試す](#q-small-cases) |
| 5.3 偶奇に着目する | [偶奇に着目する](../thinking/parity.md) |
| 5.4 集合を上手く扱う | [余事象](../thinking/complement.md)・[包除原理](../comb/inclusion-exclusion.md) |
| 5.5 ギリギリを考える | [候補の数で見積もる](../basics/complexity-estimation.md#count-candidates)（推定。最適解のある境界に候補を絞る） |
| 5.6 小問題に分解する | [独立に分解する](../thinking/reformulation.md#independence) |
| 5.7 足された回数を考える | [主客転倒・寄与](../thinking/contribution.md) |
| 5.8 上界を考える | [上界・下界を示して達成する例を作る](../thinking/construction.md#bound-and-construct) |
| 5.9 次の手だけを考える〜貪欲法〜 | [貪欲法の考え方と正当性](../basics/greedy-basics.md) |

## 参考 {#references}

- [マイナビ出版『競技プログラミングの鉄則』](https://book.mynavi.jp/ec/products/detail/id=131288)：6 章の節の題名（対応表）
- [kumonosu「問題解決のための「アルゴリズム×数学」が基礎からしっかり身につく本」の目次](https://kumonosu.cloudsquare.jp/program/table-of-contents/post-6047/)：5 章の節の題名（対応表）
- [E869120/kyopro-tessoku（GitHub）](https://github.com/E869120/kyopro-tessoku)：6 章の例題 A36〜A45 の解答のコード（対応表）
- [E869120/math-algorithm-book（GitHub）](https://github.com/E869120/math-algorithm-book)：5 章の節末問題の解答のコード（対応表）
- [Motsu_xe「解法キーアイデア集」](https://motsu-xe.hatenablog.com/entry/2019/12/17/173222)：問いの列の構成（誤読・制約・実験・仮定を足す・必要条件・別の問題を解く）
- [kmyk「競技プログラミングの問題の解き方、そのマニュアル」](https://kmyk.github.io/blog/blog/2016/06/21/how-to-solve-problems-in-competitive-programming/)：有名な手法を順に当てはめる考え方、解けなかった原因の切り分け
- [アルゴリズムロジック「競技プログラミングで解法を思いつくための典型的な考え方」](https://algo-logic.info/how-to-think-cp/)：問題の形（操作・数え上げ・構築・最大最小）ごとの考え方の分け方
