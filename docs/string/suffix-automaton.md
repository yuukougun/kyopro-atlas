---
id: suffix-automaton
title: Suffix Automaton と発展の文字列アルゴリズム
nav_title: Suffix Automaton など
aliases: [SAM, 接尾辞オートマトン, DAWG, 回文木, eertree, Palindromic Tree, Lyndon 分解, Duval, 最小回転, Run の列挙, Main-Lorentz, 逆 Manacher, 逆 Z]
type: overview
field: string
chapter: 接尾辞の構造
order: 130
level: 発展
kind: [文字列]
prerequisites: [suffix-array]
related: [palindrome, z-algorithm, kmp, trie]
summary: Suffix Automaton は全部分文字列を状態数 2N−1 以下の DFA で表し、文字を足しながら異なる部分文字列の数を答える。回文木・Lyndon 分解なども、ABC では SA・Z・Manacher で代えられることが多い。
complexity: null
signs:
  - {type: phrase, text: 文字を 1 つずつ追加しながら、異なる部分文字列の数を答える}
  - {type: phrase, text: 2 つの文字列の最長共通部分文字列}
  - {type: phrase, text: 異なる回文の部分文字列の種類数と、それぞれの出現回数}
  - {type: phrase, text: 辞書順最小の巡回シフト}
  - {type: phrase, text: Z 配列（回文半径）が与えられ、それを満たす文字列を作る}
acl: []
verify: [eertree, lyndon_factorization, runenumerate]
frequency: B
frequency_evidence: recent 1（abc452_g）・前提として届くページなし・古い ABC 0 問
sections:
  - {title: Suffix Automaton（状態数 2N−1 以下・遷移数 3N−4 以下。文字の追加に強い）, anchor: suffix-automaton}
  - {title: 回文木（eertree）, anchor: palindromic-tree}
  - {title: Lyndon 分解（Duval）と最小回転, anchor: lyndon-factorization}
  - {title: Run の列挙（Main-Lorentz）, anchor: run-enumeration}
  - {title: 文字列アルゴリズムの逆問題（逆 Manacher・逆 Z）, anchor: inverse-string-problems}
  - {title: そのほかの名前（2 次元ローリングハッシュ・Suffix Tree・Boyer-Moore の検索）, anchor: others}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：Suffix Automaton は全部分文字列を状態数 2N−1 以下の DFA で表し、文字を足しながら異なる部分文字列の数を答える。回文木・Lyndon 分解なども、ABC では SA・Z・Manacher で代えられることが多い。
    - **いつ使うか**：
        - 文字を 1 つずつ追加しながら、異なる部分文字列の数を答える
        - 2 つの文字列の最長共通部分文字列
        - 異なる回文の部分文字列の種類数と、それぞれの出現回数
        - 辞書順最小の巡回シフト
        - Z 配列（回文半径）が与えられ、それを満たす文字列を作る
    - **計算量**：（執筆時に書く）
    - **前提**：[Suffix Array と LCP 配列](../string/suffix-array.md)
