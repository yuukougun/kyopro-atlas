---
id: modint
title: modint
aliases: [static_modint, dynamic_modint, mint, modint998244353, modint1000000007]
type: technique
field: math
chapter: mod の計算
order: 60
level: 基礎
kind: [整数論, 実装・C++]
prerequisites: [mod-inverse]
related: [acl-reading#modint, mod-arithmetic, library-design]
summary: 四則演算のたびに自動で余りを取る型で、mod 付きの数え上げを素直に書ける。法が固定なら static_modint、入力で決まるなら dynamic_modint を使い、値は val() で取り出す。
complexity: null
signs:
  - {type: phrase, text: 法 M（素数とは限らない）が入力で与えられ、その余りで数え上げの答えを出力する}
acl: [static_modint, dynamic_modint]
verify: []
frequency: A
frequency_evidence: 数え上げ・確率を mod で答える問題で常に使う道具（ページ単体の最近の出現は数えにくいので手で A にした）
sections:
  - {title: 何が自動になるか（加減乗除と負の数の正規化）, anchor: what-is-automatic}
  - {title: static_modint と dynamic_modint（set_mod）の使い分け, anchor: static-dynamic}
  - {title: val() で取り出す・大小比較や「0 になったか」で元の値は分からない, anchor: pitfalls}
  - {title: 割り算の条件（法が素数でなければ互いに素が必要）, anchor: division}
  - {title: 自作するときの設計（加減の条件分岐・64bit の掛け算・pow と inv・入出力）, anchor: self-made}
  - {title: ACL の中身（Barrett 還元・raw）, anchor: acl-internals}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：四則演算のたびに自動で余りを取る型で、mod 付きの数え上げを素直に書ける。法が固定なら static_modint、入力で決まるなら dynamic_modint を使い、値は val() で取り出す。
    - **いつ使うか**：法 M（素数とは限らない）が入力で与えられ、その余りで数え上げの答えを出力する
    - **計算量**：（執筆時に書く）
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)
