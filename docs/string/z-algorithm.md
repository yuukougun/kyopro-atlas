---
id: z-algorithm
title: Z-algorithm
aliases: [Z 法, Z 配列, Z function, 拡張 KMP, z_algorithm, 各位置からの最長共通接頭辞, 巡回シフト, A+A の技]
type: technique
field: string
chapter: 線形時間の照合と回文
order: 60
level: 水
kind: [文字列]
prerequisites: [string-basics]
related: [kmp, rolling-hash, suffix-array, palindrome#manacher, dp-sequence-partition, bit-dp, method-comparison#strings]
summary: Z 配列 z[i]（S と S[i:] の最長共通接頭辞の長さ）を O(N) で求める。P＋区切り＋T の Z 配列でパターンの全出現を決定的に見つけられ、回転の検索や周期の判定にも使える。
complexity: null
signs:
  - {type: phrase, text: 各位置から、文字列の先頭と何文字一致するか}
  - {type: phrase, text: A を何回回転すると B になるか（円環状の文字列の一致）}
  - {type: phrase, text: T を S の接頭辞の連結で表す最小の個数}
  - {type: phrase, text: パターンの全出現位置}
  - {type: constraint, text: '|S|, |T| ≤ 10^6 で、ずらし方ごとに比べる O(|S||T|) が間に合わない'}
acl: [z_algorithm]
verify: [zalgorithm]
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: Z 配列の定義と、P＋区切り＋T によるパターン検索, anchor: pattern-search}
  - {title: なぜ O(N) か：Z-box の内側は値をコピーでき、比較のたびに右端が進む, anchor: linear-time}
  - {title: 'ACL の z_algorithm（z[0] = n の流儀・vector<int> にして区切りに −1）', anchor: acl}
  - {title: 巡回シフト：A+A の中で B を探す（回転 N 回を二重に数えない）, anchor: cyclic-shift}
  - {title: '周期の判定：p が周期 ⇔ z[p] = N − p', anchor: period}
  - {title: S＋区切り＋T で各位置から S の接頭辞が何文字続くか（DP の材料）, anchor: prefix-extension, level: 黄}
  - {title: Z・KMP・ハッシュの使い分け, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：Z 配列 z[i]（S と S[i:] の最長共通接頭辞の長さ）を O(N) で求める。P＋区切り＋T の Z 配列でパターンの全出現を決定的に見つけられ、回転の検索や周期の判定にも使える。
    - **いつ使うか**：
        - 各位置から、文字列の先頭と何文字一致するか
        - A を何回回転すると B になるか（円環状の文字列の一致）
        - T を S の接頭辞の連結で表す最小の個数
        - パターンの全出現位置
        - |S|, |T| ≤ 10^6 で、ずらし方ごとに比べる O(|S||T|) が間に合わない
    - **計算量**：（執筆時に書く）
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)
