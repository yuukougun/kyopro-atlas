---
id: palindrome
title: 回文の扱いと Manacher
aliases: [回文, palindrome, 回文判定, Manacher's algorithm, 回文半径, 中心から伸ばす, 両端から作る]
type: technique
field: string
chapter: 線形時間の照合と回文
order: 80
level: 水
kind: [文字列]
prerequisites: [string-basics]
related: [bfs, extended-dijkstra#two-ends, union-find, dp-state-design, contribution, rolling-hash, z-algorithm, suffix-automaton#palindromic-tree]
summary: 回文の問題を、対称な位置の組を見る・中心から伸ばす・両端から作るの 3 つの見方で小さな状態に落とす。各中心の最長回文の半径は Manacher で O(N) で求まる。
complexity: null
signs:
  - {type: phrase, text: 回文にするための最小の操作回数（書き換え・一斉置換）}
  - {type: phrase, text: 回文になる部分文字列の個数}
  - {type: phrase, text: グラフの歩道の文字列が回文になる最短の長さ}
  - {type: phrase, text: 長さ K の回文を部分文字列に含まないように埋める方法の数}
  - {type: constraint, text: N ≤ 10^6 で、すべての中心（区間）について回文かを問う}
acl: []
verify: [enumerate_palindromes]
frequency: B
frequency_evidence: recent 1（abc468_d）・前提として届くページなし・古い ABC 7 問
sections:
  - {title: 対称な位置の組を見る（Union-Find でまとめる・組ごとの寄与を数える）, anchor: symmetric-pairs}
  - {title: 中心から伸ばす O(N^2)（奇数長と偶数長の中心）, anchor: expand-center}
  - {title: 直前 K−1 文字を状態にした DP（長さ K の回文を作らない）, anchor: avoid-k-palindrome}
  - {title: グラフ上の回文：頂点の組を状態にして両端から BFS（出会う位置の偶奇）, anchor: palindrome-path}
  - {title: 外側から組み立てる（回文の式・約数）, anchor: build-outside-in, level: 青}
  - {title: Manacher：各中心の最長回文半径を O(N) で（Z と同じく内側をコピーする）, anchor: manacher, level: 青}
  - {title: 回文判定の道具の使い分け（Manacher・ハッシュ・Z・回文木）, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：回文の問題を、対称な位置の組を見る・中心から伸ばす・両端から作るの 3 つの見方で小さな状態に落とす。各中心の最長回文の半径は Manacher で O(N) で求まる。
    - **いつ使うか**：
        - 回文にするための最小の操作回数（書き換え・一斉置換）
        - 回文になる部分文字列の個数
        - グラフの歩道の文字列が回文になる最短の長さ
        - 長さ K の回文を部分文字列に含まないように埋める方法の数
        - N ≤ 10^6 で、すべての中心（区間）について回文かを問う
    - **計算量**：（執筆時に書く）
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)
