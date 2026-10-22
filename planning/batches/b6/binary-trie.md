# binary-trie の問題の補充（b6・工程9）

- ページ：docs/ds/binary-trie.md（レベル 青）。今の練習は abc425_g（diff 2205）の 1 問、例題は abc281_f・abc308_g。力試しの節はない
- 探したところ：(1) b1・b5 の summary/candidates.md には binary-trie の補充の候補なし。b3 の summary/candidates.md と b2 の報告 planning/batches/b2/binary-trie.md の「問題の補充の候補」に arc122_d（力試しの案）。(2) data/problems.yaml で pages に binary-trie を持つのは abc281_f・abc308_g・abc425_g の 3 問だけで、どれも本文にある。approach に Binary Trie と書かれているが pages に binary-trie がない問題として abc451_g（xor-basis の alternatives）を見つけた。(3) `ap.py search xor` の一覧と台帳の approach から arc033_3・abc403_g を拾い、第三者の解説で確かめた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 使ったドメイン（drken1215.hatenablog.com・kmjp.hatenablog.jp・ikatakos.com）はどれも付録 B にある。新しく noai を確かめたドメインはない
- 練習の候補 2 問を足すと練習は合わせて 3 問になる。ほかに力試しの候補が 2 問ある

## 候補

### arc033_3（台帳にあり、pages に binary-trie なし）

- 問題ID：arc033_3
- 題名：C. データ構造
- difficulty：1641（参考値・experimental。青）
- 役割：practice
- 要約：数の集合に値を追加するクエリと、小さい方から x 番目の値を出力してそれを集合から取り除くクエリを処理する（値・クエリ数とも 2×10^5 以下）。
- 方針の要点：各ノードに部分木の個数を持つ Binary Trie に値を入れ、#kth-and-global-xor の降り方（x = 0）で K 番目の葉を探し、その値を削除する。1 回 O(B) である。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2020/02/29/035900 （制約 Q, X ≤ 2×10^5 と、各ノードに個数を持つ Binary Trie で「左の子の個数と K を比べて降りる」K 番目の取得と削除の解を確かめた）
- 台帳への追加の提案：pages に {id: binary-trie, role: practice}。今は kth-element の例題・balanced-bst の練習で、BIT 上の二分探索が主の解。このページでは「BIT 上の二分探索と同じ降り方を Binary Trie で書く」練習になる

### abc403_g（台帳にあり、pages に binary-trie なし）

- 問題ID：abc403_g
- 題名：G. Odd Position Sum Query
- difficulty：2028（黄）
- 役割：practice（帯の上端 1999 をわずかに超えるだけで、手法が #xor-min-max の「部分木ごとの値を持ち上げる」型そのものなので練習に置く。帯を厳しく見るなら challenge）
- 要約：空の多重集合に値を 1 つずつ追加し、そのたびに昇順に並べたときの奇数番目の要素の和を答える。追加する値は前の答えから決まるので先読みできない。
- 方針の要点：値域 [0, 2^30) の Binary Trie（必要なノードだけ作る値域のセグメント木と同じ形）の各ノードに（個数, 奇数番目の和, 偶数番目の和）を持たせ、左の子の個数が奇数なら右の子の 2 つの和を入れ替えて合成し、追加のたびに葉から根へ作り直す。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0427_abc403 （先読みできないので座標圧縮できず、[0, 2^30) 程度の値域で必要なところだけ作るセグメント木にし、ノードに個数・奇数番目の和・偶数番目の和を持たせ、左の個数の偶奇で右を入れ替える合成を確かめた。解説の題名は Binary Trie ではなく「動的セグ木」）
    - https://kmjp.hatenablog.jp/entry/2025/04/28/1030 （問いの確認。想定解は動的セグ木と書かれ、kmjp 氏自身は平方分割で解いている）
- 台帳への追加の提案：pages に {id: binary-trie, role: practice}。今は segment-tree-on-values の challenge・sqrt-decomposition の practice。本文では「値域の動的セグメント木と同じ」と一言添えるとよい

### arc122_d（b2・b3 の候補。台帳になし）

- 問題ID：arc122_d
- 題名：D. XOR Game
- difficulty：2331（黄）
- 役割：challenge
- 要約：2N 個の整数を 2 人が 1 つずつ交互に取って N 組を作り、組ごとの XOR の最大値を先手は大きく、後手は小さくしたいとき、最適に行動した結果の値を求める。
- 方針の要点：上位 bit で集合を 2 つに分け、両側が偶数個なら両側で再帰した値の最大、奇数個なら 2 つの集合をまたぐ組の XOR の最小（片方を Binary Trie に入れ、もう片方の各要素について XOR の最小を引く）が答えになる。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2021/06/13/0930 （後手は相手の取った数に組む相手を前もって決めておけること、偶奇での場合分け、奇数のとき片方の集合で Binary Trie を作ってもう片方の各要素の XOR の最小を求めることを確かめた）
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0612_arc122 （同じ場合分け。2 つの集合をまたぐ XOR の最小は木を作らずに bit ごとに分ける再帰で求めていて、#implicit の形に当たる。公式の解説は Trie を作ると書かれている）
- 台帳への追加の提案：pages に {id: binary-trie, role: challenge}（bitwise-independence の #split-by-top-bit にも合う可能性があるが、そちらは確かめていない）

### abc451_g（台帳にあり、pages に binary-trie なし）

- 問題ID：abc451_g
- 題名：G. Minimum XOR Walk
- difficulty：2221（黄）
- 役割：challenge（帯から離れ、XOR 基底との組み合わせが要るため）
- 要約：辺に重みのある連結な無向グラフで、2 頂点を結ぶウォークの重み（通った辺の重みの XOR）の最小値が K 以下になる頂点の組の数を求める。
- 方針の要点：全域木で根からの XOR D(v) を求め、木に入らない辺が作る閉路の値で XOR 基底を作って各 D(v) を最小化したあと、XOR が K 以下の組を Binary Trie で数える（#kth-and-global-xor の応用の型「a ⊕ x < y の個数」を K + 1 で使う）。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2026/03/28/0930 （全域木・閉路の値の XOR 基底・各値の最小化の後、値を 1 つずつ入れる前に「入っている値との XOR が K+1 未満の個数」を Binary Trie で数える解を確かめた）
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0328_abc451 （同じ帰着。組の数え上げは木を作らず、K の bit が 1 なら同じ側の組をすべて数えて違う側の組で再帰、0 なら同じ側の組で再帰する分け方で、#implicit の形に当たる）
- 台帳への追加の提案：pages に {id: binary-trie, role: challenge}。前提に xor-basis が要るので、本文では related の [XOR 基底] へのリンクを添える

## 除いたもの

- abc281_f・abc308_g（例題）・abc425_g（練習）：本文に既にある
- abc241_d（Sequence Query、diff 1177）：Binary Trie でも解けるが、K ≤ 5 なので multiset のイテレータを動かすのが主の解で、帯からも離れる
- abc234_d（Prefix K-th Max、diff 503）：K が固定で priority_queue で済み、帯から離れすぎる
- そのほか `ap.py search xor`（1300〜2500）の問題（abc126_f・abc141_f・abc283_g・agc045_a など）は XOR 基底・構成・bit ごとの独立が主の解で、Binary Trie の問題とは確かめられなかったので候補にしない

## 本文に足すときのメモ

- 練習の並びは易しい順に arc033_3（1641）→ abc403_g（2028）→ abc425_g（2205）。arc033_3 は K 番目の降り方、abc403_g は部分木ごとの値を持ち上げる型、abc425_g は明示的に作らない形の練習で、節の 3 つの型が 1 問ずつそろう
- 力試しの節（`## 力試し {#challenge}`）を新しく作り、abc451_g（2221）→ arc122_d（2331）の順に置く
