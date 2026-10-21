---
id: dp-reconstruction
title: DP の復元
aliases: [DP 復元, 選び方の出力, DP テーブルからの復元, 辞書順最小の復元]
type: technique
field: dp
chapter: DP の考え方
order: 80
level: 水
kind: [DP]
prerequisites: [dp-basics]
related: [dp-order, lcs, bfs#path-restoration, lexicographic-greedy#kth, binomial-coefficient#kth, subsequence-dp]
summary: 最適値だけでなく選び方そのものを出力するとき、完成した表を終端から逆にたどって最適な遷移を復元する。辞書順最小は後ろからの DP と前からの貪欲で、辞書順 K 番目は個数を数えて先頭から決める。
complexity: null
signs:
  - {type: phrase, text: 選び方（経路・操作列）を 1 つ出力せよ}
  - {type: phrase, text: 条件を満たすものが複数あれば辞書順最小のものを出力せよ}
  - {type: phrase, text: 辞書順で K 番目のものを出力せよ（K は 10^18 程度）}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 表を残して終端から逆にたどる・遷移元を記録しておく, anchor: trace-back}
  - {title: 最適な遷移が複数あるときの選び方, anchor: ties}
  - {title: 辞書順最小の復元（後ろからの DP と前からの貪欲）, anchor: lexicographic-min}
  - {title: 辞書順 K 番目を数え上げで決める（個数が K を超えたら打ち切る）, anchor: dp-kth-lexicographic}
  - {title: 落とし穴：使い回した表では辿れない・辿った順の逆転・数え上げの溢れ, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：最適値だけでなく選び方そのものを出力するとき、完成した表を終端から逆にたどって最適な遷移を復元する。辞書順最小は後ろからの DP と前からの貪欲で、辞書順 K 番目は個数を数えて先頭から決める。
    - **いつ使うか**：
        - 選び方（経路・操作列）を 1 つ出力せよ
        - 条件を満たすものが複数あれば辞書順最小のものを出力せよ
        - 辞書順で K 番目のものを出力せよ（K は 10^18 程度）
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
