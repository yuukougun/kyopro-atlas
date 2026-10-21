---
id: greedy-basics
title: 貪欲法の考え方と正当性
aliases: [グリーディ, Greedy, 貪欲, 交換しても悪化しない, マトロイド]
type: technique
field: basics
chapter: 貪欲
order: 240
level: 基礎
kind: [貪欲]
prerequisites: [sorting-techniques]
related: [exchange-argument, interval-scheduling, dp-basics, stress-testing, minimum-spanning-tree]
summary: その場で最もよいものを選び続ける方針が正しいことを、交換論法（最適解を貪欲解に近づけても悪くならない）や帰納法で確かめてから使う。怪しいときは小さいケースの全探索と比べる。
complexity: null
signs:
  - {type: phrase, text: 強いもの・安いものから順に使う}
  - {type: phrase, text: 1 回ごとに最大（最小）のものを選ぶ操作を繰り返す}
  - {type: shape, text: その場で一番よいものを選んでも後悔しない（入れ替えても悪くならない）}
acl: []
frequency: A
frequency_evidence: recent 5（abc454_f・abc459_d・abc468_f・abc471_f・abc473_e）・前提として 9 ページに届く（直接 5）・古い ABC 2 問
sections:
  - {title: 正当性の示し方（交換論法・帰納法・常に先行している・マトロイド）, anchor: proof}
  - {title: 基準を決めて強い順に使う, anchor: strongest-first}
  - {title: 同じ値をまとめて処理する, anchor: batch-same-values}
  - {title: 反例の探し方（小さいケースの全探索と比べる）, anchor: counterexamples}
  - {title: 貪欲が失敗する例と DP への切り替え, anchor: when-greedy-fails}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：その場で最もよいものを選び続ける方針が正しいことを、交換論法（最適解を貪欲解に近づけても悪くならない）や帰納法で確かめてから使う。怪しいときは小さいケースの全探索と比べる。
    - **いつ使うか**：
        - 強いもの・安いものから順に使う
        - 1 回ごとに最大（最小）のものを選ぶ操作を繰り返す
        - その場で一番よいものを選んでも後悔しない（入れ替えても悪くならない）
    - **計算量**：（執筆時に書く）
    - **前提**：[ソートで考える](../basics/sorting-techniques.md)
