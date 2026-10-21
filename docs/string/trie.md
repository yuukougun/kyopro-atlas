---
id: trie
title: Trie
aliases: [トライ木, 接頭辞木, prefix tree, 全ペアの LCP の和]
type: technique
field: string
chapter: Trie と照合オートマトン
order: 90
level: 水
kind: [文字列, データ構造]
prerequisites: [string-basics, dfs]
related: [binary-trie, aho-corasick, suffix-array, sorting-techniques, contribution, linearity-of-expectation]
summary: 文字列の集合を、共通の接頭辞を共有する木に入れる。各節点に通過数を持てば、全ペアの最長共通接頭辞の和や、ある接頭辞を持つ文字列の数が、長さの総和に比例する時間で求まる。
complexity: null
signs:
  - {type: phrase, text: 全ペアの最長共通接頭辞（LCP）の長さの和}
  - {type: phrase, text: 各文字列について、ほかの文字列との LCP の最大}
  - {type: phrase, text: ある文字列を接頭辞に持つ文字列の数（追加・削除あり）}
  - {type: phrase, text: 数列（文字列）の集合を辞書順にたどる}
  - {type: constraint, text: 文字列の個数が多く、長さの総和が 5×10^5 程度まで}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として 2 ページに届く（直接 2）・古い ABC 6 問
sections:
  - {title: 節点・挿入・検索（子を配列で持つか map で持つか・節点数の上限）, anchor: basic-operations}
  - {title: 通過数と終端の印の区別, anchor: counts}
  - {title: '全ペアの LCP の和：節点ごとに C(通過数, 2) を足す（主客転倒）', anchor: lcp-sum}
  - {title: ソートして隣どうしの LCP を見る代用, anchor: sort-alternative}
  - {title: Trie 上の DFS と、節点に値を持つ DP, anchor: dp-on-trie, level: 青}
  - {title: Trie 上の確率・期待値, anchor: expectation-on-trie, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：文字列の集合を、共通の接頭辞を共有する木に入れる。各節点に通過数を持てば、全ペアの最長共通接頭辞の和や、ある接頭辞を持つ文字列の数が、長さの総和に比例する時間で求まる。
    - **いつ使うか**：
        - 全ペアの最長共通接頭辞（LCP）の長さの和
        - 各文字列について、ほかの文字列との LCP の最大
        - ある文字列を接頭辞に持つ文字列の数（追加・削除あり）
        - 数列（文字列）の集合を辞書順にたどる
        - 文字列の個数が多く、長さの総和が 5×10^5 程度まで
    - **計算量**：（執筆時に書く）
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)、[深さ優先探索（DFS）](../graph/dfs.md)
