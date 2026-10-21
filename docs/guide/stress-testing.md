---
id: stress-testing
title: ストレステストと実験
aliases: [ランダムテスト, 愚直解との比較, 実験, OEIS, 撃墜ケース探し]
type: guide
field: guide
chapter: コンテストと考察
order: 120
level: null
kind: [案内, 実装・C++]
prerequisites: []
related: [debugging-checklist, thinking-checklist#q-small-cases, counting-mindset, interactive, cpp-math-functions#random]
summary: WA の原因が見つからないときに、愚直解と本解を小さいランダムな入力で比べて反例を探せる。小さいケースの全探索で表を作り、規則を予想する実験の手順も示す。
complexity: null
signs: []
acl: []
sections:
  - {title: ストレステストの手順, anchor: procedure}
  - {title: 書き方の形, anchor: setups}
  - {title: 生成器のコツ, anchor: generators}
  - {title: 注意, anchor: caveats}
  - {title: 実験で規則を予想する, anchor: experiment}
  - {title: インタラクティブ問題を手元で試す, anchor: interactive}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：WA の原因が見つからないときに、愚直解と本解を小さいランダムな入力で比べて反例を探せる。小さいケースの全探索で表を作り、規則を予想する実験の手順も示す。
    - **使い方**：（執筆時に書く）
