---
id: invariant
title: 不変量・単調に変わる量
aliases: [モノバリアント, 保存量, 単調量, 操作の順序によらない, invariant, monovariant]
type: thinking
field: thinking
order: 60
level: 基礎
kind: [考察]
prerequisites: []
related: [parity, reverse-thinking, proof-patterns#necessary-sufficient, game-basics#move-parity, run-length-encoding, difference-sequence]
summary: 操作で変わらない量（和の余り・個数の偶奇・XOR）を見つけて必要条件を得て、十分性は構築で示す。操作で必ず減る量（単調量）は操作回数の上界や停止性の証明に使う。
complexity: null
signs:
  - {type: phrase, text: 操作を好きな回数・好きな順に行える}
  - {type: phrase, text: 目標の状態に到達できるか・最終状態の最大値}
  - {type: phrase, text: 操作の前後で変わらない量（和・偶奇・余り）がありそう}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 不変量で必要条件を見つけ、構築で十分性を示す, anchor: necessary-and-sufficient}
  - {title: 単調量（必ず減る量）で回数の上界を得る, anchor: monovariant}
  - {title: 操作の順序によらないなら都合のよい順で考える, anchor: order-independence}
  - {title: 独立な部分に分ける（奇数部分ごと）, anchor: independent-parts}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：操作で変わらない量（和の余り・個数の偶奇・XOR）を見つけて必要条件を得て、十分性は構築で示す。操作で必ず減る量（単調量）は操作回数の上界や停止性の証明に使う。
    - **いつ使うか**：
        - 操作を好きな回数・好きな順に行える
        - 目標の状態に到達できるか・最終状態の最大値
        - 操作の前後で変わらない量（和・偶奇・余り）がありそう
    - **計算量**：（執筆時に書く）
    - **前提**：なし
