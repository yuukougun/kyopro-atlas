---
id: lcs
title: 最長共通部分列と編集距離
aliases: [LCS, Longest Common Subsequence, レーベンシュタイン距離, Edit Distance, Levenshtein Distance, 最長共通部分文字列, DP の DP]
type: technique
field: dp
chapter: 列の DP
order: 180
level: 水
kind: [DP, 文字列]
prerequisites: [dp-basics]
related: [dp-reconstruction, subsequence-dp, interval-dp, palindrome, counting-dedup, bit-dp, subsequence-and-substring#longest]
summary: 2 つの文字列の最長共通部分列の長さを、末尾どうしが一致するかで分ける 2 次元の DP で O(NM) で求める。同じ表で挿入・削除・置換のコストを取れば編集距離になる。
complexity: null
signs:
  - {type: constraint, text: '2 つの列・文字列で N, M ≤ 3000〜5000'}
  - {type: phrase, text: 共通の部分列の最長・共通部分列の組の数}
  - {type: phrase, text: 挿入・削除・置換で一致させる最小回数}
  - {type: phrase, text: ある値（2 つの文字列の最長共通部分列の長さなど）がちょうど k になる文字列の数}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 表の意味と遷移（一致する末尾を使って損をしない理由）, anchor: recurrence}
  - {title: 復元（右下から逆にたどる）, anchor: restore}
  - {title: 編集距離（挿入・削除・置換の 3 方向のコスト）, anchor: edit-distance}
  - {title: 部分列と部分文字列の違い（最長共通部分文字列）, anchor: substring}
  - {title: 共通部分列の組の数（包除で重複を引く・2 次元の累積和）, anchor: count-pairs, level: 青}
  - {title: 最長回文部分列（S と反転の LCS）, anchor: palindromic-subsequence}
  - {title: LCS の値ごとに数える：DP の DP（内側の DP の 1 行を外側の状態にする）, anchor: dp-of-dp, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：2 つの文字列の最長共通部分列の長さを、末尾どうしが一致するかで分ける 2 次元の DP で O(NM) で求める。同じ表で挿入・削除・置換のコストを取れば編集距離になる。
    - **いつ使うか**：
        - 2 つの列・文字列で N, M ≤ 3000〜5000
        - 共通の部分列の最長・共通部分列の組の数
        - 挿入・削除・置換で一致させる最小回数
        - ある値（2 つの文字列の最長共通部分列の長さなど）がちょうど k になる文字列の数
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
