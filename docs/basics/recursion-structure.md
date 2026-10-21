---
id: recursion-structure
title: 再帰的な構造
aliases: [フラクタル, 自己相似, 再帰関数, レベル N の構造, recursive structure, fractal]
type: technique
field: basics
chapter: 再帰と分割統治
order: 310
level: 基礎
kind: [ダブリング・分割統治]
prerequisites: []
related: [divide-and-conquer, recursive-enumeration, memoized-recursion, cpp-lambda#recursive-lambda]
summary: レベル N のものがレベル N − 1 のものの組合せで定義される構造の K 番目を、各レベルの長さを前計算して再帰でたどって求める。長さが指数的に増えるので、必要な深さは log K 程度で済む。
complexity: null
signs:
  - {type: phrase, text: レベル N のものがレベル N − 1 のものを並べて作られる}
  - {type: phrase, text: 長さが 2 倍・3 倍で増える構造の K 番目}
  - {type: phrase, text: フラクタル図形を描く}
  - {type: constraint, text: レベルは 50 程度まででも、全体の長さが 10^15 を超える}
acl: []
frequency: B
frequency_evidence: recent 1（abc476_g）・前提として 6 ページに届く（直接 2）・古い ABC 3 問
sections:
  - {title: 長さを前計算して K 番目を再帰で探す, anchor: kth-by-length}
  - {title: 再帰で描く, anchor: draw}
  - {title: 必要な深さは log K（長さの上限で打ち切る）, anchor: depth}
  - {title: 再帰の深さとスタック, anchor: stack}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：レベル N のものがレベル N − 1 のものの組合せで定義される構造の K 番目を、各レベルの長さを前計算して再帰でたどって求める。長さが指数的に増えるので、必要な深さは log K 程度で済む。
    - **いつ使うか**：
        - レベル N のものがレベル N − 1 のものを並べて作られる
        - 長さが 2 倍・3 倍で増える構造の K 番目
        - フラクタル図形を描く
        - レベルは 50 程度まででも、全体の長さが 10^15 を超える
    - **計算量**：（執筆時に書く）
    - **前提**：なし
