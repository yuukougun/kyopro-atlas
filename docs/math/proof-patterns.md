---
id: proof-patterns
title: 整数の証明の型
aliases: [整数問題の証明, 並べ替え論法, 余りの鳩の巣, gcd が不変, mod での矛盾]
type: thinking
field: math
chapter: GCD と合同式
order: 250
level: 基礎
kind: [考察, 整数論]
prerequisites: [gcd-lcm]
related: [notation, invariant, symmetry-pigeonhole-casework, parity, stress-testing, gcd-properties]
summary: 実験で見つけた整数の規則が正しいかを、定番の筋道で確かめる。操作で gcd が変わらない、a, 2a, … が余りを並べ替える、余りの鳩の巣、mod での矛盾などを使う。
complexity: null
signs:
  - {type: phrase, text: 操作を好きなだけ繰り返したとき、最後に残る値や作れる値を答える}
  - {type: phrase, text: 大きい方から小さい方を引く・余りに置き換える操作を繰り返す}
  - {type: phrase, text: 区間の幅が法 m 以上なら答えが決まる（余りは m 種類しかない）}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 操作で gcd が変わらない（互除法の不変量）, anchor: gcd-invariant}
  - {title: 互いに割り切り合うことで等号を示す, anchor: mutual-divisibility}
  - {title: '並べ替え論法（a, 2a, …, (p−1)a が余りの並べ替えになる）', anchor: rearrangement}
  - {title: 余りの鳩の巣（m+1 個のうち2つは同じ余り）, anchor: pigeonhole-remainder}
  - {title: mod での矛盾で「できない」を示す, anchor: contradiction-mod}
  - {title: 必要条件と十分条件（実験の結果を信じてよいか）, anchor: necessary-sufficient}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：実験で見つけた整数の規則が正しいかを、定番の筋道で確かめる。操作で gcd が変わらない、a, 2a, … が余りを並べ替える、余りの鳩の巣、mod での矛盾などを使う。
    - **いつ使うか**：
        - 操作を好きなだけ繰り返したとき、最後に残る値や作れる値を答える
        - 大きい方から小さい方を引く・余りに置き換える操作を繰り返す
        - 区間の幅が法 m 以上なら答えが決まる（余りは m 種類しかない）
    - **計算量**：（執筆時に書く）
    - **前提**：[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)
