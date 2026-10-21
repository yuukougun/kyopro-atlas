---
id: kmp
title: KMP 法と文字列の周期
aliases: [KMP, MP 法, Knuth-Morris-Pratt, 失敗関数, prefix function, π 配列, border, 最小周期, 繰り返し単位]
type: technique
field: string
chapter: 線形時間の照合と回文
order: 70
level: 青
kind: [文字列]
prerequisites: [string-basics]
related: [z-algorithm, aho-corasick, string-automaton-dp, rolling-hash, divisor-enum, mobius-function, suffix-automaton]
summary: π[i]（先頭 i+1 文字の、接頭辞でも接尾辞でもある最長の真の部分の長さ）を O(N) で求める。π をたどると全 border と最小周期が分かり、照合に失敗したときのずらし方や照合オートマトンの遷移にも使える。
complexity: null
signs:
  - {type: phrase, text: 接頭辞と接尾辞が一致する最長の長さ}
  - {type: phrase, text: 最小周期・何かの繰り返しで書けるか}
  - {type: phrase, text: N の約数 M を周期に持つ文字列（表）を数える}
  - {type: phrase, text: 文字が 1 つずつ来るたびに、パターンが現れたかを判定する}
  - {type: constraint, text: '|S| ≤ 10^6 で、すべての接頭辞について周期や一致する長さを問う'}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 6 問
sections:
  - {title: '失敗関数 π（border）の定義と添字の流儀（π[0] を 0 にするか −1 にするか）', anchor: failure-function}
  - {title: なぜ O(N) か：照合長は 1 文字で高々 1 増え、ループで減る回数も合計 N 以下, anchor: linear-time}
  - {title: パターン照合：失敗したら π の値までずらす, anchor: matching}
  - {title: MP と KMP の違い（競プロでは MP を KMP と呼ぶことが多い）, anchor: mp-vs-kmp}
  - {title: border の連鎖と全 border の列挙, anchor: border-chain}
  - {title: '周期と繰り返し：最小周期 N − π[N−1]、N を割り切るときだけ繰り返しで書ける（弱周期定理）', anchor: string-period}
  - {title: N の約数の周期を数える：約数ごとに数えて包除（メビウス）, anchor: count-periodic}
  - {title: 照合オートマトン（状態×文字 → 次の状態）を表に埋める, anchor: automaton}
  - {title: Z との使い分け（ACL に KMP はなく、周期は z_algorithm でも判定できる）, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：π[i]（先頭 i+1 文字の、接頭辞でも接尾辞でもある最長の真の部分の長さ）を O(N) で求める。π をたどると全 border と最小周期が分かり、照合に失敗したときのずらし方や照合オートマトンの遷移にも使える。
    - **いつ使うか**：
        - 接頭辞と接尾辞が一致する最長の長さ
        - 最小周期・何かの繰り返しで書けるか
        - N の約数 M を周期に持つ文字列（表）を数える
        - 文字が 1 つずつ来るたびに、パターンが現れたかを判定する
        - |S| ≤ 10^6 で、すべての接頭辞について周期や一致する長さを問う
    - **計算量**：（執筆時に書く）
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)
