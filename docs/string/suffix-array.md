---
id: suffix-array
title: Suffix Array と LCP 配列
aliases: [接尾辞配列, SA, LCP 配列, SA-IS, Kasai 法, suffix_array, lcp_array, 異なる部分文字列の数]
type: technique
field: string
chapter: 接尾辞の構造
order: 120
level: 黄
kind: [文字列, データ構造]
prerequisites: [string-basics, binary-search]
related: [sparse-table, monotonic-stack, rolling-hash, trie, z-algorithm, suffix-automaton, run-length-encoding]
summary: 全接尾辞を辞書順に並べた添字の列（SA）と隣どうしの最長共通接頭辞（LCP 配列）を作る。異なる部分文字列の数・任意の 2 接尾辞の LCP・パターンの出現回数が求まり、ACL の suffix_array・lcp_array で使える。
complexity: null
signs:
  - {type: phrase, text: 異なる部分文字列の個数}
  - {type: phrase, text: 全接尾辞どうしの LCP の和}
  - {type: phrase, text: 回転したものどうしの辞書順の大小を数える}
  - {type: phrase, text: 部分文字列を辞書順に並べたときの K 番目}
  - {type: constraint, text: '|S| ≤ 5×10^5 程度で全部分文字列を扱う'}
acl: [suffix_array, lcp_array]
verify: [suffixarray, number_of_substrings]
frequency: B
frequency_evidence: recent 1（abc452_g）・前提として 1 ページに届く（直接 1）・古い ABC 4 問
sections:
  - {title: SA と LCP 配列の定義（ACL の suffix_array・lcp_array。lcp の長さは n−1）, anchor: definition}
  - {title: 異なる部分文字列の数 = N(N+1)/2 − Σlcp, anchor: distinct-substrings}
  - {title: 任意の 2 接尾辞の LCP は LCP 配列の区間最小（Sparse Table）, anchor: lcp-rmq}
  - {title: パターンの出現回数：SA 上の二分探索で範囲を求める, anchor: pattern-count}
  - {title: 全ペアの LCP の和：LCP 配列の上の単調スタック, anchor: lcp-sum}
  - {title: 複数の文字列を連結するときの区切り（vector<int> と大きな値）, anchor: concat-separator}
  - {title: 回転どうしの比較：S+S+T+T の SA, anchor: rotations}
  - {title: 部分文字列の辞書順 K 番目, anchor: kth-substring, level: 発展}
  - {title: 自作するなら：ダブリング O(N log^2 N) → O(N log N) → SA-IS, anchor: build-your-own}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：全接尾辞を辞書順に並べた添字の列（SA）と隣どうしの最長共通接頭辞（LCP 配列）を作る。異なる部分文字列の数・任意の 2 接尾辞の LCP・パターンの出現回数が求まり、ACL の suffix_array・lcp_array で使える。
    - **いつ使うか**：
        - 異なる部分文字列の個数
        - 全接尾辞どうしの LCP の和
        - 回転したものどうしの辞書順の大小を数える
        - 部分文字列を辞書順に並べたときの K 番目
        - |S| ≤ 5×10^5 程度で全部分文字列を扱う
    - **計算量**：（執筆時に書く）
    - **前提**：[文字列の基本操作と辞書順](../string/string-basics.md)、[二分探索](../basics/binary-search.md)
