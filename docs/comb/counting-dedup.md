---
id: counting-dedup
title: 重複の除き方
aliases: [ダブルカウントを防ぐ, 重複を除く, 代表元, 正規形, 最左マッチ, 最小添字規則]
type: technique
field: comb
chapter: 数え方の考え方
order: 100
level: 青
kind: [数え上げ, DP, 考察]
prerequisites: [counting-mindset, dp-state-design]
related: [counting-bijection, multinomial-coefficient, burnside-lemma, recursive-enumeration, subsequence-dp, inclusion-exclusion, lcs, subset-enumeration-dp]
summary: 同じ対象を何度も数えてしまうとき、どれもちょうど c 回ずつなら c で割り、重複度がばらばらなら代表元を 1 つ決めて代表元だけを数える。数え上げ DP では、最も左を取る・最小番号から決めるなどで作り方を 1 通りにする。
complexity: null
signs:
  - {type: phrase, text: 異なる〜の個数（種類数）}
  - {type: phrase, text: 操作で作れる文字列（列）の種類数}
  - {type: phrase, text: S を部分列として含む文字列の個数}
  - {type: phrase, text: 区別しないグループに分ける方法の数}
  - {type: shape, text: 作り方（遷移の列）を数える式で、同じ対象が複数回数えられてしまう}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 5 問
sections:
  - {title: 重複度が一定なら割る（同じものを含む順列・円順列）, anchor: divide}
  - {title: 重複度が一定でないなら代表元を決める, anchor: representative}
  - {title: 部分列として含む文字列は最も左の埋め込みで数える, anchor: leftmost}
  - {title: グループ分けは未使用の最小番号から決める, anchor: min-index}
  - {title: DP の中で代表を決める（直前と違う・最初に〜で場合分け・包除で重なりを引く）, anchor: in-dp}
  - {title: 落とし穴：グループの順序を区別して K! 倍に数える, anchor: pitfall-order}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：同じ対象を何度も数えてしまうとき、どれもちょうど c 回ずつなら c で割り、重複度がばらばらなら代表元を 1 つ決めて代表元だけを数える。数え上げ DP では、最も左を取る・最小番号から決めるなどで作り方を 1 通りにする。
    - **いつ使うか**：
        - 異なる〜の個数（種類数）
        - 操作で作れる文字列（列）の種類数
        - S を部分列として含む文字列の個数
        - 区別しないグループに分ける方法の数
        - 作り方（遷移の列）を数える式で、同じ対象が複数回数えられてしまう
    - **計算量**：（執筆時に書く）
    - **前提**：[数え上げの考え方](../comb/counting-mindset.md)、[DP の状態の設計](../dp/dp-state-design.md)
