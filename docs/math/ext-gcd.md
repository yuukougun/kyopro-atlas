---
id: ext-gcd
title: 拡張ユークリッドの互除法と一次合同式
aliases: [拡張 Euclid, extended Euclidean algorithm, extgcd, ベズーの等式, Bézout's identity, ax+by=c, 一次不定方程式, linear congruence]
type: technique
field: math
chapter: GCD と合同式
order: 210
level: 水
kind: [整数論]
prerequisites: [gcd-lcm]
related: [mod-inverse, crt]
summary: 互除法の途中経過から ax + by = gcd(a, b) の整数解を求める。ax + by = c は gcd | c のときだけ解をもち、一次合同式 ax ≡ b (mod m) や法が素数でないときの逆元もこれで解く。
complexity: null
signs:
  - {type: phrase, text: ax + by = c を満たす整数の組}
  - {type: phrase, text: 円周上を K ずつ進んで、何回目で初めて特定の位置に着くか}
  - {type: phrase, text: A の倍数を足して、B で割った余りを C にできるか}
  - {type: phrase, text: 法 M が素数とは限らない一次方程式 a x ≡ b (mod M)}
  - {type: constraint, text: 法 M ≤ 10^9 が素数とは限らず、a^(M−2) で逆元を作れない}
acl: [inv_mod]
verify: []
frequency: B
frequency_evidence: recent 1（abc459_g）・前提として 1 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: 互除法の各段で、余りを a と b の整数係数の組み合わせとして持ち続ける, anchor: procedure}
  - {title: ax + by = c の解の存在条件と一般解 x = x0 + k·b/g, anchor: general-solution}
  - {title: 最小の非負解への調整と、係数のあふれの見積もり, anchor: min-solution}
  - {title: 一次合同式 ax ≡ b (mod m) と、gcd で割ること, anchor: linear-congruence}
  - {title: ACL では（inv_mod の内部の inv_gcd。拡張ユークリッドそのものは公開 API にない）, anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：互除法の途中経過から ax + by = gcd(a, b) の整数解を求める。ax + by = c は gcd | c のときだけ解をもち、一次合同式 ax ≡ b (mod m) や法が素数でないときの逆元もこれで解く。
    - **いつ使うか**：
        - ax + by = c を満たす整数の組
        - 円周上を K ずつ進んで、何回目で初めて特定の位置に着くか
        - A の倍数を足して、B で割った余りを C にできるか
        - 法 M が素数とは限らない一次方程式 a x ≡ b (mod M)
        - 法 M ≤ 10^9 が素数とは限らず、a^(M−2) で逆元を作れない
    - **計算量**：（執筆時に書く）
    - **前提**：[GCD・LCM とユークリッドの互除法](../math/gcd-lcm.md)
