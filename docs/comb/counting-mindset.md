---
id: counting-mindset
title: 数え上げの考え方
aliases: [数え上げの基本方針, ちょうど 1 回数える, ちょうど＝以下の差, 式で数えるか DP で数えるか]
type: technique
field: comb
chapter: 数え方の考え方
order: 70
level: 水
kind: [数え上げ, 考察]
prerequisites: [binomial-coefficient]
related: [complement, contribution, stress-testing#experiment, counting-fix-order, inclusion-exclusion, divisor-inclusion-exclusion, linearity-of-expectation, dp-basics]
summary: 数え上げを、対象の確定 → 数えやすい言い換え → 排反な場合の和と独立な段階の積 → 重複と漏れの確認 → 小さいケースでの検算の順に解く。「ちょうど」は「以下」の差で、全通りの総和は寄与で数える。
complexity: null
signs:
  - {type: phrase, text: 最大値（最小値）がちょうど K になるものの個数}
  - {type: phrase, text: すべての選び方についての〜の総和}
  - {type: shape, text: 答えが「K 以下」の個数の差 f(K) − f(K−1) で書ける}
acl: []
frequency: A
frequency_evidence: recent 3（abc456_g・abc457_f・abc471_e）・前提として 14 ページに届く（直接 7）・古い ABC 7 問
sections:
  - {title: 数え上げの手順と「ちょうど 1 回」, anchor: procedure}
  - {title: 式で数えるか DP で数えるか, anchor: formula-or-dp}
  - {title: 「ちょうど」を「以下」の差で数える, anchor: exactly-vs-at-most}
  - {title: 二項係数と組み合わせた寄与（残りの選び方を掛ける）, anchor: contribution-with-binomial, level: 青}
  - {title: 小さいケースの全探索で式を検算する, anchor: verify-small}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：数え上げを、対象の確定 → 数えやすい言い換え → 排反な場合の和と独立な段階の積 → 重複と漏れの確認 → 小さいケースでの検算の順に解く。「ちょうど」は「以下」の差で、全通りの総和は寄与で数える。
    - **いつ使うか**：
        - 最大値（最小値）がちょうど K になるものの個数
        - すべての選び方についての〜の総和
        - 答えが「K 以下」の個数の差 f(K) − f(K−1) で書ける
    - **計算量**：（執筆時に書く）
    - **前提**：[二項係数の意味と性質](../comb/binomial-coefficient.md)
