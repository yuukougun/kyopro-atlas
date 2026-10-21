---
id: dp-state-design
title: DP の状態の設計
aliases: [状態設計, DP の状態, 直前を状態に持つ, 末尾の数文字を状態に持つ, 環状 DP, 円環 DP, 括弧列の DP]
type: technique
field: dp
chapter: DP の考え方
order: 50
level: 水
kind: [DP]
prerequisites: [dp-basics]
related: [dp-dimension-reduction, dp-mod-state, dp-phase, bit-dp, bracket-sequence#counting, string-automaton-dp, palindrome#avoid-k-palindrome, counting-dedup#in-dp, binary-search-answer#dp-check]
summary: 過去の選び方そのものではなく、将来の選び方と評価に影響する要約（直前の値・個数・末尾の数文字・開き括弧の数など）だけを状態に持つ。要約が同じ状態は同一視しても答えが変わらない。
complexity: null
signs:
  - {type: phrase, text: 隣り合う〜が異なる・同じことを連続して〜しない}
  - {type: phrase, text: 直前の選択でコストが変わる・モードが切り替わる}
  - {type: phrase, text: 長さ K の回文・特定の短い文字列を部分文字列に含まない文字列の数}
  - {type: phrase, text: 円形に並んでいる（最後と最初も隣り合う）}
  - {type: phrase, text: '''('' と '')'' と ''?'' の列から正しい括弧列を作る方法の数'}
  - {type: constraint, text: 制約の一部だけが小さい（K ≤ 5、末尾の K ≤ 10 文字、文字の種類 26）}
acl: []
frequency: A
frequency_evidence: recent 4（abc456_d・abc457_f・abc462_f・abc464_d）・前提として 20 ページに届く（直接 9）・古い ABC 10 問
sections:
  - {title: 将来に効く要約だけを持てば合流できる理由, anchor: why-summary-works}
  - {title: 典型の要約（直前の値・on/off・偶奇・個数・上限で打ち切った値）, anchor: typical-summaries}
  - {title: 末尾の数文字を状態にする（禁止された並び・回文を避ける）, anchor: last-characters}
  - {title: 括弧列の DP（開き括弧の残り数を状態にする）, anchor: bracket-dp}
  - {title: 環状の列（1 か所で切り、最初の状態を固定して DP を回す）, anchor: dp-cyclic}
  - {title: 状態数の見積もり（(P+1)^K・2^K・末尾の数文字の組の数）, anchor: state-count}
  - {title: 落とし穴：最適値だけを持って状態を潰しすぎる, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：過去の選び方そのものではなく、将来の選び方と評価に影響する要約（直前の値・個数・末尾の数文字・開き括弧の数など）だけを状態に持つ。要約が同じ状態は同一視しても答えが変わらない。
    - **いつ使うか**：
        - 隣り合う〜が異なる・同じことを連続して〜しない
        - 直前の選択でコストが変わる・モードが切り替わる
        - 長さ K の回文・特定の短い文字列を部分文字列に含まない文字列の数
        - 円形に並んでいる（最後と最初も隣り合う）
        - '(' と ')' と '?' の列から正しい括弧列を作る方法の数
        - 制約の一部だけが小さい（K ≤ 5、末尾の K ≤ 10 文字、文字の種類 26）
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
