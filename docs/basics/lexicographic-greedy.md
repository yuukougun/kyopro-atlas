---
id: lexicographic-greedy
title: 辞書順最小を前から決める貪欲
aliases: [辞書順最小, lexicographically smallest, 辞書順 K 番目, 先頭から貪欲に決める]
type: technique
field: basics
chapter: 貪欲
order: 280
level: 基礎
kind: [貪欲, 文字列]
prerequisites: [greedy-basics]
related: [subsequence-matching#lexicographically-smallest, string-basics, topological-sort#lexicographic, binomial-coefficient#kth, dp-reconstruction#dp-kth-lexicographic, exchange-argument]
summary: 条件を満たすもののうち辞書順最小を、先頭から 1 つずつ「小さい候補から試し、残りで条件を満たせるならその候補に確定」で作る。残りで実現できるかの判定を速く正しく行うことが問題の本体になる。
complexity: null
signs:
  - {type: phrase, text: 辞書順最小（最大）の文字列・列を出力する（なければ −1）}
  - {type: phrase, text: 条件を満たす中で最も小さいもの}
  - {type: phrase, text: 辞書順で K 番目}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 先頭から決める理由（辞書順の性質）, anchor: why-front}
  - {title: 残りで実現できるかの判定（次の出現位置の表・個数の数え上げ）, anchor: feasibility}
  - {title: 順序の制約は入次数 0 を小さい順に（トポロジカルソート）, anchor: topological}
  - {title: 辞書順 K 番目（先頭ごとの個数と K を比べる）, anchor: kth}
  - {title: 判定が重い型, anchor: heavy-check, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：条件を満たすもののうち辞書順最小を、先頭から 1 つずつ「小さい候補から試し、残りで条件を満たせるならその候補に確定」で作る。残りで実現できるかの判定を速く正しく行うことが問題の本体になる。
    - **いつ使うか**：
        - 辞書順最小（最大）の文字列・列を出力する（なければ −1）
        - 条件を満たす中で最も小さいもの
        - 辞書順で K 番目
    - **計算量**：（執筆時に書く）
    - **前提**：[貪欲法の考え方と正当性](../basics/greedy-basics.md)
