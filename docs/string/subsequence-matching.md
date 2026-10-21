---
id: subsequence-matching
title: 部分列の判定と次の出現位置の表
aliases: [部分列判定, 次の出現位置, nxt 配列, 部分列オートマトン, 序列自動機, 部分列として含むか, subsequence automaton]
type: technique
field: string
chapter: 文字列の基本
order: 20
level: 基礎
kind: [文字列]
prerequisites: [string-basics, binary-search]
related: [subsequence-dp, lexicographic-greedy, lcs, dp-reconstruction, subsequence-and-substring]
summary: T が S の部分列かを、S を左から見て T の文字をできるだけ早く拾う貪欲で判定する。各位置から各文字が次に現れる位置の表を作れば、多数の判定や辞書順最小の部分列も速く求まる。
complexity: null
signs:
  - {type: phrase, text: T を部分列として含むか（連続でなくてよい）}
  - {type: phrase, text: 長さ K の部分列のうち辞書順で最小のもの}
  - {type: phrase, text: S の部分列として現れない最短の文字列}
  - {type: phrase, text: S を何回も繰り返した文字列の部分列として入るか}
  - {type: constraint, text: '|S| ≤ 10^5〜10^6、文字は英小文字で 26×(N+1) の表が持てる'}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc452_d）・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 貪欲な照合：できるだけ左で拾うのが最善な理由, anchor: greedy-matching}
  - {title: '次の出現位置の表 nxt[i][c]（後ろから作る・番兵 N）', anchor: next-occurrence}
  - {title: 文字ごとの位置のリストと lower_bound による代用, anchor: position-lists}
  - {title: 辞書順最小の部分列（残りで足りる範囲の最小の文字を選ぶ）, anchor: lexicographically-smallest, level: 水}
  - {title: 繰り返した文字列の部分列（文字ごとの累積個数で位置を飛ばす）, anchor: repeated-string, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：T が S の部分列かを、S を左から見て T の文字をできるだけ早く拾う貪欲で判定する。各位置から各文字が次に現れる位置の表を作れば、多数の判定や辞書順最小の部分列も速く求まる。
    - **いつ使うか**：
        - T を部分列として含むか（連続でなくてよい）
        - 長さ K の部分列のうち辞書順で最小のもの
        - S の部分列として現れない最短の文字列
        - S を何回も繰り返した文字列の部分列として入るか
        - |S| ≤ 10&#94;5〜10&#94;6、文字は英小文字で 26×(N+1) の表が持てる
    - **計算量**：（執筆時に書く）
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)、[二分探索](../basics/binary-search.md)
