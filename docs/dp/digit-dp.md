---
id: digit-dp
title: 桁 DP
aliases: [Digit DP, smaller フラグ, 未満フラグ, leading zero]
type: technique
field: dp
chapter: 状態の形で分かれる DP
order: 250
level: 水
kind: [DP, 数え上げ]
prerequisites: [dp-state-design, mod-arithmetic]
related: [digit-dp-advanced, dp-mod-state, bitwise-independence#top-down, string-automaton-dp]
summary: N 以下の整数のうち条件を満たすものの個数や総和を、上の桁から決め、それまでの桁が N と一致しているかのフラグと問題の情報を状態にして求める。計算量は桁数に比例する。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^18、または N が 10^4 桁の文字列}
  - {type: phrase, text: N 以下で条件を満たす整数の個数・総和}
  - {type: phrase, text: 各桁の和・0 でない桁の数}
  - {type: phrase, text: K 以下の X について、XOR や AND の条件を満たすものを数える・最大化する}
acl: []
frequency: A
frequency_evidence: recent 2（abc465_e・abc466_g）・前提として 1 ページに届く（直接 1）・古い ABC 6 問
sections:
  - {title: N と一致しているかのフラグ（一致したままの道は 1 本だけ）, anchor: tight-flag}
  - {title: 問題の情報を状態に足す（桁和の余り・個数）, anchor: extra-state}
  - {title: leading zero を区別するとき, anchor: leading-zero}
  - {title: 2 進の桁 DP（XOR・AND）, anchor: binary}
  - {title: 割る数を全探索して桁 DP を繰り返す, anchor: fix-divisor}
  - {title: 落とし穴：N 自身を含むか・0 を数えるか, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N 以下の整数のうち条件を満たすものの個数や総和を、上の桁から決め、それまでの桁が N と一致しているかのフラグと問題の情報を状態にして求める。計算量は桁数に比例する。
    - **いつ使うか**：
        - N ≤ 10^18、または N が 10^4 桁の文字列
        - N 以下で条件を満たす整数の個数・総和
        - 各桁の和・0 でない桁の数
        - K 以下の X について、XOR や AND の条件を満たすものを数える・最大化する
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の状態の設計](../dp/dp-state-design.md)、[mod の計算の基本](../math/mod-arithmetic.md)
