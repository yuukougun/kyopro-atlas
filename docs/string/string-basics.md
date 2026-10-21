---
id: string-basics
title: 文字列の基本操作と辞書順
aliases: [辞書順, 文字列の比較, 文字の一斉置換, 文字列の回転, 連結して辞書順最小, lexicographical order]
type: technique
field: string
chapter: 文字列の基本
order: 10
level: 基礎
kind: [文字列]
prerequisites: [sorting-techniques]
related: [lexicographic-greedy, run-length-encoding, subsequence-matching, z-algorithm#cyclic-shift, exchange-argument, subsequence-and-substring, bracket-sequence, parsing, cpp-string-api]
summary: 辞書順の最小・回転・文字の一斉置換を問う文字列の問題を、定義に沿った全探索と比較で解く。辞書順は最初に異なる位置の文字で決まり、片方が尽きたら短い方が小さい。
complexity: null
signs:
  - {type: phrase, text: 条件を満たす文字列のうち辞書順で最小（最大）のものを出力する}
  - {type: phrase, text: 文字を一斉に別の文字へ置き換える操作を繰り返して一致させられるか}
  - {type: phrase, text: 先頭の文字を末尾に移す（回転する）操作を何回か行う}
  - {type: constraint, text: '|S| ≤ 5000 程度で、回転や置き方を全部試せる'}
acl: []
verify: []
frequency: A
frequency_evidence: recent 0・前提として 13 ページに届く（直接 7）・古い ABC 4 問
sections:
  - {title: '辞書順の定義と std::string の比較（接頭辞は短い方が小さい）', anchor: lexicographic-order}
  - {title: 部分文字列（連続）と部分列（連続でなくてよい）の違い, anchor: substring-vs-subsequence}
  - {title: 文字の一斉置換：両方向の対応が一意か（全単射）, anchor: character-mapping}
  - {title: 連結して辞書順最小：長さが違えば a+b < b+a で比べる, anchor: concat-order}
  - {title: 回転（巡回シフト）の入口：回転回数の全探索と A+A, anchor: rotation}
  - {title: 計算量の落とし穴（substr・+・find は長さに比例する）, anchor: cost-pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：辞書順の最小・回転・文字の一斉置換を問う文字列の問題を、定義に沿った全探索と比較で解く。辞書順は最初に異なる位置の文字で決まり、片方が尽きたら短い方が小さい。
    - **いつ使うか**：
        - 条件を満たす文字列のうち辞書順で最小（最大）のものを出力する
        - 文字を一斉に別の文字へ置き換える操作を繰り返して一致させられるか
        - 先頭の文字を末尾に移す（回転する）操作を何回か行う
        - |S| ≤ 5000 程度で、回転や置き方を全部試せる
    - **計算量**：（執筆時に書く）
    - **前提**：[ソートで考える](../basics/sorting-techniques.md)
