---
id: base-conversion
title: N 進法
aliases: [基数変換, base conversion, b 進法, n 進数, −2 進法, 26 進, Horner 法]
type: technique
field: math
chapter: floor と商
order: 270
level: 基礎
kind: [整数論]
prerequisites: [integer-division]
related: [bit-operations, binary-search-answer, floor-quotient-enum]
summary: N を b で割った余りを並べて b 進表記にし、Horner 法で数に戻す。負の基数（−2 進）や 1 始まりの 26 進（a..z, aa..）、基数を変数とみた二分探索といった変形にも使う。
complexity: null
signs:
  - {type: phrase, text: b 進法・−2 進法で表す}
  - {type: phrase, text: 'a, b, …, z, aa, ab, … と続く名前の n 番目'}
  - {type: phrase, text: 文字列を n 進数とみた値が M 以下になる n を数える}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: b 進表記への変換と Horner 法による復元（0 の扱い）, anchor: convert}
  - {title: 1 始まりの 26 進（1 を引いてから割る）, anchor: bijective-26}
  - {title: 負の基数（余りを 0 以上に直してから割る）, anchor: negative-base, level: 水}
  - {title: 基数の二分探索とオーバーフロー（1 桁の場合分け）, anchor: base-binary-search, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：N を b で割った余りを並べて b 進表記にし、Horner 法で数に戻す。負の基数（−2 進）や 1 始まりの 26 進（a..z, aa..）、基数を変数とみた二分探索といった変形にも使う。
    - **いつ使うか**：
        - b 進法・−2 進法で表す
        - a, b, …, z, aa, ab, … と続く名前の n 番目
        - 文字列を n 進数とみた値が M 以下になる n を数える
    - **計算量**：（執筆時に書く）
    - **前提**：[整数の割り算と余り](../math/integer-division.md)
