---
title: 考察の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 考察の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## 言い換えの典型（reformulation） {#reformulation}

- id：`reformulation`　レベル：水　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/reformulation/
- 別名：言い換え、式変形、条件の言い換え、独立に分解、x と y を分ける、変数変換、reformulation
- 種類：考察
- サイン：
    - 言い回し：条件が複雑で直接は数えにくい・判定しにくい
    - 言い回し：x 方向と y 方向・bit ごと・連結成分ごとに結果が独立に決まる
    - 式の形：式を変形すると i の項と j の項に分離できる
- 節：
    - `reformulation#table` 言い換えの一覧表（元の条件 → 言い換え → 使う手法のページ）：https://yuukougun.github.io/kyopro-atlas/thinking/reformulation/#table
    - `reformulation#separate-indices` i と j を分離する（a_i − i などの変数変換）：https://yuukougun.github.io/kyopro-atlas/thinking/reformulation/#separate-indices
    - `reformulation#independence` 独立に分解する（x と y・bit ごと・連結成分ごと）：https://yuukougun.github.io/kyopro-atlas/thinking/reformulation/#independence
    - `reformulation#operations` 操作の言い換え（区間操作を差分列で・隣接 swap を転倒数で）：https://yuukougun.github.io/kyopro-atlas/thinking/reformulation/#operations
    - `reformulation#then-data-structure` 言い換えてからデータ構造に載せる（青）：https://yuukougun.github.io/kyopro-atlas/thinking/reformulation/#then-data-structure

## 一部を固定して数える（fix-variable） {#fix-variable}

- id：`fix-variable`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/fix-variable/
- 別名：決め打ち、固定して全探索、真ん中を固定、片方を固定、最大値を固定、fix one variable
- 種類：考察、全探索
- 前提：`brute-force`
- サイン：
    - 言い回し：3 つ組 (i < j < k) を数える
    - 言い回し：2 つの値の組で、片方を決めればもう片方の条件が単純になる
    - 言い回し：最大値（最小値）を決めて残りを最適化する
    - 制約：N ≤ 2×10^5 で 3 つ組は N^3 通りあり、全部は試せない
- 節：
    - `fix-variable#fix-middle` 真ん中を固定して左右を独立に数える：https://yuukougun.github.io/kyopro-atlas/thinking/fix-variable/#fix-middle
    - `fix-variable#fix-parts` 角・余り・平方因子を除いた部分を固定する：https://yuukougun.github.io/kyopro-atlas/thinking/fix-variable/#fix-parts
    - `fix-variable#fix-maximum` 最大値を固定して残りを最適化する：https://yuukougun.github.io/kyopro-atlas/thinking/fix-variable/#fix-maximum
    - `fix-variable#speed-up` 固定したあとを速くする（二分探索・累積和・連想配列）：https://yuukougun.github.io/kyopro-atlas/thinking/fix-variable/#speed-up

## 主客転倒・寄与（contribution） {#contribution}

- id：`contribution`　レベル：水　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/contribution/
- 別名：主客転倒、寄与、貢献度、contribution technique、足された回数、各要素が何回数えられるか
- 種類：考察、数え上げ
- サイン：
    - 言い回し：すべての組・区間・部分集合についての総和
    - 言い回し：各要素が答えに何回足されるか
    - 言い回し：全区間の最小値（2 番目に大きい値）の和
    - 制約：N ≤ 2×10^5 で、組・区間は N^2 個あり列挙できない
- 節：
    - `contribution#swap-roles` 数える対象を入れ替える（表の行と列。式の規則は Σ の変形のページ）：https://yuukougun.github.io/kyopro-atlas/thinking/contribution/#swap-roles
    - `contribution#sort-signs` ソートで符号を決める（全ペアの差）：https://yuukougun.github.io/kyopro-atlas/thinking/contribution/#sort-signs
    - `contribution#digits-divisors` 各桁・各約数の寄与：https://yuukougun.github.io/kyopro-atlas/thinking/contribution/#digits-divisors
    - `contribution#max-min-count` 各要素が最大・最小になる回数（同じ値の扱い）：https://yuukougun.github.io/kyopro-atlas/thinking/contribution/#max-min-count
    - `contribution#counting` 数え上げ・期待値での使い方（数え上げの章へ）：https://yuukougun.github.io/kyopro-atlas/thinking/contribution/#counting

## 余事象（complement） {#complement}

- id：`complement`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/complement/
- 別名：補集合、全体から引く、少なくとも 1 つ、2 条件の包除、complementary counting
- 種類：考察、数え上げ
- サイン：
    - 言い回し：〜でないもの・少なくとも 1 つ含むもの
    - 言い回し：すべて異なる・条件を 1 つでも満たす
    - 言い回し：A でも B でもないものの個数
    - 式の形：直接数えると場合分けが多いが、条件を満たさない側は数えやすい
- 節：
    - `complement#whole-minus-complement` 全体 − 補集合：https://yuukougun.github.io/kyopro-atlas/thinking/complement/#whole-minus-complement
    - `complement#two-conditions` 2〜3 条件の包除（重なりを足し戻す）：https://yuukougun.github.io/kyopro-atlas/thinking/complement/#two-conditions
    - `complement#mod-and-empty` mod の引き算と空集合の扱い：https://yuukougun.github.io/kyopro-atlas/thinking/complement/#mod-and-empty

## 偶奇に着目する（parity） {#parity}

- id：`parity`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/parity/
- 別名：パリティ、偶奇性、mod 2、市松模様、チェッカーボード、parity
- 種類：考察
- サイン：
    - 言い回し：ちょうど K 回の操作・±1 の移動
    - 言い回し：和が偶数という条件
    - 言い回し：グリッドを 1 マスずつ動く操作の可否
    - 言い回し：チェス盤の塗り分け・ドミノの敷き詰め
- 節：
    - `parity#alternating` 1 歩ごとに偶奇が入れ替わる：https://yuukougun.github.io/kyopro-atlas/thinking/parity/#alternating
    - `parity#exactly-k` ちょうど K 回なら偶奇がそろうことが必要：https://yuukougun.github.io/kyopro-atlas/thinking/parity/#exactly-k
    - `parity#components` 偶奇の条件でつながった成分（Union-Find）：https://yuukougun.github.io/kyopro-atlas/thinking/parity/#components
    - `parity#checkerboard` 市松模様の偶奇（青）：https://yuukougun.github.io/kyopro-atlas/thinking/parity/#checkerboard
    - `parity#bipartite-game` 二部グラフ・ゲームとのつながり：https://yuukougun.github.io/kyopro-atlas/thinking/parity/#bipartite-game

## 不変量・単調に変わる量（invariant） {#invariant}

- id：`invariant`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/invariant/
- 別名：モノバリアント、保存量、単調量、操作の順序によらない、invariant、monovariant
- 種類：考察
- サイン：
    - 言い回し：操作を好きな回数・好きな順に行える
    - 言い回し：目標の状態に到達できるか・最終状態の最大値
    - 言い回し：操作の前後で変わらない量（和・偶奇・余り）がありそう
- 節：
    - `invariant#necessary-and-sufficient` 不変量で必要条件を見つけ、構築で十分性を示す：https://yuukougun.github.io/kyopro-atlas/thinking/invariant/#necessary-and-sufficient
    - `invariant#monovariant` 単調量（必ず減る量）で回数の上界を得る：https://yuukougun.github.io/kyopro-atlas/thinking/invariant/#monovariant
    - `invariant#order-independence` 操作の順序によらないなら都合のよい順で考える：https://yuukougun.github.io/kyopro-atlas/thinking/invariant/#order-independence
    - `invariant#independent-parts` 独立な部分に分ける（奇数部分ごと）：https://yuukougun.github.io/kyopro-atlas/thinking/invariant/#independent-parts

## 後ろから・逆順に考える（reverse-thinking） {#reverse-thinking}

- id：`reverse-thinking`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/reverse-thinking/
- 別名：逆から考える、操作を逆再生、クエリを逆順に処理、削除を追加に、work backwards
- 種類：考察、クエリ処理の工夫
- サイン：
    - 言い回し：辺・要素の削除のクエリ
    - 言い回し：操作列を復元する・操作の結果から元を求める
    - 式の形：後ろから決めると選択肢が 1 つに決まる
- 節：
    - `reverse-thinking#decide-from-back` 後ろから決めると一意になる：https://yuukougun.github.io/kyopro-atlas/thinking/reverse-thinking/#decide-from-back
    - `reverse-thinking#undo-last` 最後の操作を特定して逆再生する：https://yuukougun.github.io/kyopro-atlas/thinking/reverse-thinking/#undo-last
    - `reverse-thinking#deadlines` 締め切りを後ろから見る：https://yuukougun.github.io/kyopro-atlas/thinking/reverse-thinking/#deadlines
    - `reverse-thinking#delete-to-add` 削除を逆順の追加にする（Union-Find はグラフの章）（水）：https://yuukougun.github.io/kyopro-atlas/thinking/reverse-thinking/#delete-to-add

## 構築問題の考え方（construction） {#construction}

- id：`construction`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/construction/
- 別名：構築、constructive、1 つ出力せよ、上界と下界、必要条件と十分性、constructive algorithms
- 種類：考察
- サイン：
    - 言い回し：条件を満たすものを 1 つ出力せよ（存在しなければ −1）
    - 言い回し：操作手順を出力せよ（回数の上限が与えられている）
    - 言い回し：最大値を求めるが、答えに自然な上限がありそう
- 節：
    - `construction#small-cases` 小さい N で作って規則を一般化する：https://yuukougun.github.io/kyopro-atlas/thinking/construction/#small-cases
    - `construction#necessary-conditions` 必要条件を先に挙げる：https://yuukougun.github.io/kyopro-atlas/thinking/construction/#necessary-conditions
    - `construction#bound-and-construct` 上界・下界を示して達成する例を作る：https://yuukougun.github.io/kyopro-atlas/thinking/construction/#bound-and-construct
    - `construction#checker` 出力を検査するプログラムで確かめる：https://yuukougun.github.io/kyopro-atlas/thinking/construction/#checker
    - `construction#abc-patterns` ABC の構築の型（手順・数列・グラフ）（水）：https://yuukougun.github.io/kyopro-atlas/thinking/construction/#abc-patterns

## 対称性・鳩の巣原理・場合分け（symmetry-pigeonhole-casework） {#symmetry-pigeonhole-casework}

- id：`symmetry-pigeonhole-casework`　レベル：基礎　段階：stub　type：thinking
- URL：https://yuukougun.github.io/kyopro-atlas/thinking/symmetry-pigeonhole-casework/
- 別名：対称性、鳩の巣原理、部屋割り論法、場合分け、pigeonhole principle、端の場合を分ける
- 種類：考察
- サイン：
    - 言い回し：i < j の組の和など、i と j を入れ替えても同じ形の式
    - 言い回し：自分以外の全員の XOR（和）が与えられる
    - 制約：余りや状態が M 種類しかなく、M + 1 個以上の候補がある
    - 言い回し：N = 1 や N が小さいときだけ答えの形が違う
- 節：
    - `symmetry-pigeonhole-casework#symmetry` 対称性で計算を半分にする（i < j の和・全体の XOR から 1 つ除く）：https://yuukougun.github.io/kyopro-atlas/thinking/symmetry-pigeonhole-casework/#symmetry
    - `symmetry-pigeonhole-casework#symmetry-cases` 対称性で場合を減らす（N ≤ M に入れ替える）：https://yuukougun.github.io/kyopro-atlas/thinking/symmetry-pigeonhole-casework/#symmetry-cases
    - `symmetry-pigeonhole-casework#pigeonhole` 鳩の巣原理（必ず一致が起きる・探索の打ち切り回数）（水）：https://yuukougun.github.io/kyopro-atlas/thinking/symmetry-pigeonhole-casework/#pigeonhole
    - `symmetry-pigeonhole-casework#casework` 場合分け（端の場合・大小関係・操作の順序によらないこと）：https://yuukougun.github.io/kyopro-atlas/thinking/symmetry-pigeonhole-casework/#casework
