---
id: gcd-properties
title: GCD の性質
aliases: [差の gcd, 区間 gcd, gcd の変化は log 回, gcd と周期]
type: technique
field: math
chapter: GCD と合同式
order: 220
level: 青
kind: [整数論, 区間クエリ]
prerequisites: [gcd-lcm]
related: [sparse-table, segment-tree, minimum-spanning-tree, convex-hull#lattice-points]
summary: 全体に同じ数を足したときの gcd を隣接差の gcd に直し、左端を固定した区間 gcd が O(log A) 種類しかないことで区間 gcd を速く求める。mod N で A ずつ進むと gcd(A, N) の倍数だけを回ることも使う。
complexity: null
signs:
  - {type: phrase, text: A_i + B_j の矩形・全体に x を足したときの gcd}
  - {type: phrase, text: 区間の gcd を多数答える}
  - {type: phrase, text: mod N で A ずつ進む操作で全ての点に行けるか}
  - {type: constraint, text: 'N, Q ≤ 2×10^5 で区間 gcd のクエリ'}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: '差の gcd：gcd(a + x, b + x) = gcd(a + x, b − a)', anchor: difference-gcd}
  - {title: 区間 gcd はセグメント木・Sparse Table に載る（左端を固定すると値は O(log A) 種類）, anchor: range-gcd}
  - {title: 'mod N で A ずつ進むと gcd(A, N) の倍数だけを回る（周期と連結性）', anchor: step-mod}
  - {title: '線分上の格子点は gcd(|dx|, |dy|) + 1 個', anchor: lattice-on-segment}
  - {title: 'ax + by（x, y ≥ 0）で表せない最大の数 ab − a − b', anchor: frobenius}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：全体に同じ数を足したときの gcd を隣接差の gcd に直し、左端を固定した区間 gcd が O(log A) 種類しかないことで区間 gcd を速く求める。mod N で A ずつ進むと gcd(A, N) の倍数だけを回ることも使う。
    - **いつ使うか**：
        - A_i + B_j の矩形・全体に x を足したときの gcd
        - 区間の gcd を多数答える
        - mod N で A ずつ進む操作で全ての点に行けるか
        - N, Q ≤ 2×10^5 で区間 gcd のクエリ
    - **計算量**：（執筆時に書く）
    - **前提**：[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)
