---
id: mod-arithmetic
title: mod の計算の基本
aliases: [剰余演算, 余りを取る, 合同式の計算, modular arithmetic, mod 998244353, mod 1e9+7]
type: technique
field: math
chapter: mod の計算
order: 30
level: 基礎
kind: [整数論]
prerequisites: [integer-division]
related: [modint, mod-inverse, notation, dp-mod-state]
summary: 答えを m で割った余りで求めるとき、足し算・引き算・掛け算は途中で何度余りを取ってもよい。割り算と大小比較はそのままではできず、負の数とあふれにも注意が要る。
complexity: null
signs:
  - {type: phrase, text: 引き算を含む式の値を、0 以上 m 未満の余りで出力する}
  - {type: constraint, text: 10^9 程度の値の積を何度も取り、余りを取らないと 64bit に収まらない}
acl: []
verify: []
frequency: A
frequency_evidence: recent 0・前提として 39 ページに届く（直接 6）・古い ABC 2 問
sections:
  - {title: 途中で余りを取ってよい理由（合同式の性質）, anchor: why-mod}
  - {title: 引き算の後の負の数を 0 以上に直す, anchor: negative}
  - {title: 掛け算のあふれ（両方を mod に収めてから 64bit で掛ける）, anchor: overflow}
  - {title: 割り算はそのままではできない（→ 逆元）, anchor: division}
  - {title: mod を取った値で大小比較・最大値を考えてはいけない, anchor: no-compare}
  - {title: なぜ 998244353 か（素数で、NTT に向く形）, anchor: why-998244353}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：答えを m で割った余りで求めるとき、足し算・引き算・掛け算は途中で何度余りを取ってもよい。割り算と大小比較はそのままではできず、負の数とあふれにも注意が要る。
    - **いつ使うか**：
        - 引き算を含む式の値を、0 以上 m 未満の余りで出力する
        - 10^9 程度の値の積を何度も取り、余りを取らないと 64bit に収まらない
    - **計算量**：（執筆時に書く）
    - **前提**：[整数の割り算と余り](../math/integer-division.md)
