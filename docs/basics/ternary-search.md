---
id: ternary-search
title: 三分探索
aliases: [三分法, 黄金分割探索, 凸関数の極値, 凸関数, 離散凸, 増分が単調, ternary search]
type: technique
field: basics
chapter: 凸と三分探索
order: 220
level: 水
kind: [二分探索]
prerequisites: [binary-search-answer]
related: [median-absolute, circle-geometry#geometry-optimization, slope-trick, greedy-priority-queue]
summary: 下に凸（谷が 1 つ）な関数の最小値を、2 点の値を比べて外側を捨てながら求める。整数なら f(x+1) − f(x) の符号で二分探索するほうが安全で、凸性は「凸関数の和・最大は凸」で確かめる。
complexity: null
signs:
  - {type: phrase, text: 時刻や位置を 1 つ選んで、時間やコストを最小化する（谷形）}
  - {type: phrase, text: 答えを実数で出力し、誤差が許される}
  - {type: shape, text: 1 つ増やすごとの増分が単調に増える}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 実数版（反復回数の目安）と整数版（残りを全部調べる）, anchor: real-and-integer}
  - {title: 差分の符号で二分探索する方法, anchor: difference-sign}
  - {title: 凸性の確かめ方（凸関数の和・最大は凸、|x − a| と x^2 は凸）, anchor: convexity}
  - {title: 平らな部分がある関数での失敗, anchor: flat-pitfall}
  - {title: 黄金分割探索, anchor: golden-section}
  - {title: 増分が単調なら 1 単位ずつ貪欲に配る, anchor: marginal-greedy, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：下に凸（谷が 1 つ）な関数の最小値を、2 点の値を比べて外側を捨てながら求める。整数なら f(x+1) − f(x) の符号で二分探索するほうが安全で、凸性は「凸関数の和・最大は凸」で確かめる。
    - **いつ使うか**：
        - 時刻や位置を 1 つ選んで、時間やコストを最小化する（谷形）
        - 答えを実数で出力し、誤差が許される
        - 1 つ増やすごとの増分が単調に増える
    - **計算量**：（執筆時に書く）
    - **前提**：[答えで二分探索](../basics/binary-search-answer.md)
