---
id: dp-mod-state
title: 余り・個数を状態に持つ DP
aliases: [余りを状態に, mod DP, 倍数の数え上げ, 平均が整数]
type: technique
field: dp
chapter: DP の考え方
order: 60
level: 水
kind: [DP, 整数論]
prerequisites: [dp-state-design, mod-arithmetic]
related: [digit-dp, subset-sum, knapsack-01, dp-sequence-partition, game-basics#state-design]
summary: 「和が M の倍数」「平均が整数」のような条件は、和そのものではなく M で割った余りを状態に持てば数えられる。平均は選ぶ個数を外側で固定するか、各値から平均を引いて和 0 に直す。
complexity: null
signs:
  - {type: phrase, text: 和（積）が M の倍数になる選び方の数}
  - {type: phrase, text: 平均が整数になる・平均がちょうど A になる選び方の数}
  - {type: phrase, text: '''?'' を埋めた数を M で割った余りが r になるものの数'}
  - {type: constraint, text: M ≤ 1000 程度、N ≤ 100 程度}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 余りを状態にしてよい理由（足し算・掛け算と mod が両立する）, anchor: why-remainder}
  - {title: 個数も状態に持つ（K 個選んで和が D の倍数）, anchor: with-count}
  - {title: 平均の扱い（個数を外側で固定する・平均を引いて和 0 にする）, anchor: average}
  - {title: 後ろから余りごとの勝敗を決めるゲーム, anchor: game-by-remainder, level: 青}
  - {title: 落とし穴：C++ の % が負になる・状態の mod と答えの mod の混同, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：「和が M の倍数」「平均が整数」のような条件は、和そのものではなく M で割った余りを状態に持てば数えられる。平均は選ぶ個数を外側で固定するか、各値から平均を引いて和 0 に直す。
    - **いつ使うか**：
        - 和（積）が M の倍数になる選び方の数
        - 平均が整数になる・平均がちょうど A になる選び方の数
        - '?' を埋めた数を M で割った余りが r になるものの数
        - M ≤ 1000 程度、N ≤ 100 程度
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の状態の設計](../dp/dp-state-design.md)、[mod の計算の基本](../math/mod-arithmetic.md)
