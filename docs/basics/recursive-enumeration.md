---
id: recursive-enumeration
title: 再帰による全列挙
aliases: [DFS による全列挙, バックトラック, 枝刈り, 組分けの全列挙, グループ分けの全列挙, 集合分割の全列挙, backtracking]
type: technique
field: basics
chapter: 全探索
order: 60
level: 水
kind: [全探索]
prerequisites: [bit-full-search]
related: [bit-dp, memoized-recursion, brute-force, bell-number#size, cpp-lambda#recursive-lambda]
summary: 部分的に決めた状態から 1 つずつ決めていく再帰で、条件を満たす数・組分け・敷き詰めを全部列挙する。組分けは「まだ組のない最小番号の人から決める」と同じ分け方を二度数えない。
complexity: null
signs:
  - {type: phrase, text: 条件を満たす数・列を小さい順にすべて作る}
  - {type: constraint, text: N ≤ 10〜12 人を組・グループに分ける（ベル数 B12 ≈ 4.2×10^6）}
  - {type: constraint, text: 2N ≤ 16 人を 2 人組に分ける（(2N−1)!! 通り）}
  - {type: phrase, text: タイルの敷き詰め・パズルを途中で打ち切りながら試す}
acl: []
frequency: A
frequency_evidence: recent 2（abc473_d・abc475_d）・前提として 2 ページに届く（直接 1）・古い ABC 6 問
sections:
  - {title: 生成型（桁を 1 つずつ足す）, anchor: generate}
  - {title: 組分け型（最小番号から決めて重複を防ぐ）, anchor: partition}
  - {title: ペア分け型, anchor: pairing}
  - {title: 敷き詰め型（左上の空きマスから置く）, anchor: tiling}
  - {title: 枝刈りと計算量の見積もり（葉の数 × 1 本あたり）, anchor: pruning}
  - {title: 状態を戻し忘れない（バックトラック）, anchor: backtrack}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：部分的に決めた状態から 1 つずつ決めていく再帰で、条件を満たす数・組分け・敷き詰めを全部列挙する。組分けは「まだ組のない最小番号の人から決める」と同じ分け方を二度数えない。
    - **いつ使うか**：
        - 条件を満たす数・列を小さい順にすべて作る
        - N ≤ 10〜12 人を組・グループに分ける（ベル数 B12 ≈ 4.2×10^6）
        - 2N ≤ 16 人を 2 人組に分ける（(2N−1)!! 通り）
        - タイルの敷き詰め・パズルを途中で打ち切りながら試す
    - **計算量**：（執筆時に書く）
    - **前提**：[bit 全探索と順列全探索](../basics/bit-full-search.md)
