---
title: その他の技法の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# その他の技法の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。stub（準備中）のページは要約と前提しかなく、節の見出しもまだない。

## インタラクティブ問題（interactive） {#interactive}

- id：`interactive`　レベル：基礎　段階：draft　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/misc/interactive/
- 別名：対話型、インタラクティブ、ジャッジとの対話、質問回数、インタラクティブの二分探索、interactive problem
- 種類：二分探索、実装・C++
- 前提：`binary-search`
- サイン：
    - 言い回し：問題文に「インタラクティブ」「質問は Q 回まで」とある
    - 言い回し：質問の答えが入力として返ってくる・入出力例が対話の形
    - 制約：質問回数の上限が 20 回など log2 N 程度
- 節：
    - `interactive#format` 形式と C++ の作法（出力のたびに flush・cin.tie(nullptr) を書いたとき）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#format
    - `interactive#query-budget` 回数の上限から方針を逆算する（情報量の下界）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#query-budget
    - `interactive#binary-search` 二分探索で候補を半分ずつ減らす：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#binary-search
    - `interactive#binary-encoding` 2 進表記で質問を設計する：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#binary-encoding
    - `interactive#explore-graph` 未知のグラフを探索する（DFS の行きと帰り）（水）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#explore-graph
    - `interactive#equations-crt` 連立方程式・中国剰余定理で特定する（青）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#equations-crt
    - `interactive#output-structure-first` 先に構造を出力してから答える（青）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#output-structure-first
    - `interactive#adaptive-judge` 適応的ジャッジ（最悪の場合の回数で考える）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#adaptive-judge
    - `interactive#local-testing` 手元でのテスト（ジャッジ役のプログラムとパイプでつなぐ）：https://yuukougun.github.io/kyopro-atlas/misc/interactive/#local-testing

## 乱択アルゴリズム（randomized） {#randomized}

- id：`randomized`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/misc/randomized/
- 別名：乱択、ランダム化、モンテカルロ法、ラスベガス法、過半数、Boyer-Moore の投票、Color Coding、randomized algorithm
- 種類：ハッシュ・乱択
- 前提：`probability-basics`
- サイン：
    - 言い回し：半数を超える要素が条件を満たす（過半数）
    - 制約：K ≤ 10 程度の少数の要素を選ぶ条件で、要素の種類が多い
    - 式の形：決定的な方法は重いが、確率的に正しければ十分に速い
    - 式の形：固定の mod・係数のハッシュが、作為的な入力で衝突させられる
- 節：
    - `randomized#monte-carlo-las-vegas` モンテカルロ法とラスベガス法：https://yuukougun.github.io/kyopro-atlas/misc/randomized/#monte-carlo-las-vegas
    - `randomized#failure-probability` 失敗確率の見積もりと試行回数（(1 − p)^k）：https://yuukougun.github.io/kyopro-atlas/misc/randomized/#failure-probability
    - `randomized#majority` 過半数の扱い（ランダムな 2 つを選ぶ・Boyer-Moore の投票）：https://yuukougun.github.io/kyopro-atlas/misc/randomized/#majority
    - `randomized#color-coding` Color Coding（黄）：https://yuukougun.github.io/kyopro-atlas/misc/randomized/#color-coding
    - `randomized#cpp-random` C++ の乱数（mt19937_64・時間計測）：https://yuukougun.github.io/kyopro-atlas/misc/randomized/#cpp-random
    - `randomized#heuristics` 焼きなましなどのヒューリスティックは ABC の範囲外（AHC）：https://yuukougun.github.io/kyopro-atlas/misc/randomized/#heuristics

## bitset による高速化（bitset-speedup） {#bitset-speedup}

- id：`bitset-speedup`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/
- 別名：bitset、ビット並列、ワード並列、1/64 倍、bitset で部分和、推移閉包、到達可能性クエリ、bitset speedup
- 種類：ビット演算、計算量、DP
- 前提：`bit-operations`、`complexity-estimation`
- サイン：
    - 制約：N ≤ 2000〜5000 程度で、O(N^3) や O(N^2 M) が少し間に合わない
    - 言い回し：部分和として作れる値か（和の上限が 10&#94;5〜10&#94;6）
    - 言い回し：2 頂点の共通の隣接頂点・三角形の数
    - 言い回し：偶奇（XOR）だけ分かればよい
    - 言い回し：u から v へ到達できるかのクエリが大量にある
    - 制約：N が 5×10^4 程度で N^2/64 の計算が間に合う
- 節：
    - `bitset-speedup#word-parallel` ワード並列の考え方と計算量の目安（N^3/64）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#word-parallel
    - `bitset-speedup#common-neighbors` 共通の隣接頂点・三角形の数（行の AND と popcount）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#common-neighbors
    - `bitset-speedup#parity-xor` 偶奇だけの集計（XOR）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#parity-xor
    - `bitset-speedup#subset-sum-shift` 部分和 DP のシフト OR（黄）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#subset-sum-shift
    - `bitset-speedup#reachability` DAG の到達可能性（逆トポロジカル順に OR、閉路は SCC で縮約）（黄）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#reachability
    - `bitset-speedup#memory-batching` メモリの見積もりと 64 個ずつのクエリの処理（黄）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#memory-batching
    - `bitset-speedup#cpp` C++ の作法（大きさはコンパイル時の定数・大きな bitset をスタックに置かない）：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#cpp
    - `bitset-speedup#vs-bit-dp` bitDP との違い：https://yuukougun.github.io/kyopro-atlas/misc/bitset-speedup/#vs-bit-dp

## 構文解析（parsing） {#parsing}

- id：`parsing`　レベル：青　段階：stub　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/misc/parsing/
- 別名：再帰下降構文解析、パーサ、BNF、式の評価、逆ポーランド記法、recursive descent parsing
- 種類：文字列
- 前提：`recursion-structure`
- サイン：
    - 言い回し：数式の文字列が与えられ、値を求める
    - 言い回し：\+ と \* と括弧の優先順位がある
    - 言い回し：式として正しい部分文字列
    - 言い回し：入れ子の構造を持つ文字列
    - 制約：式の長さが 2×10^5 程度で、括弧の入れ子が深くなりうる
- 節：
    - `parsing#bnf` BNF と規則ごとの関数（読み取り位置を参照で共有する）：https://yuukougun.github.io/kyopro-atlas/misc/parsing/#bnf
    - `parsing#why-it-works` 優先順位と括弧が正しく読める理由（構文木と呼び出しの木）：https://yuukougun.github.io/kyopro-atlas/misc/parsing/#why-it-works
    - `parsing#edge-cases` 単項マイナス・空白などの例外：https://yuukougun.github.io/kyopro-atlas/misc/parsing/#edge-cases
    - `parsing#grammar-dp` 文法に沿った DP：https://yuukougun.github.io/kyopro-atlas/misc/parsing/#grammar-dp
    - `parsing#substring-sum` 式の部分文字列の総和（発展）：https://yuukougun.github.io/kyopro-atlas/misc/parsing/#substring-sum
    - `parsing#deep-nesting` 深い入れ子と再帰の深さ：https://yuukougun.github.io/kyopro-atlas/misc/parsing/#deep-nesting
