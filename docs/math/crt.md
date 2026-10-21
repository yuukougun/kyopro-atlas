---
id: crt
title: 中国剰余定理
aliases: [CRT, Chinese remainder theorem, 中国の剰余定理, Garner, 連立合同式]
type: technique
field: math
chapter: GCD と合同式
order: 230
level: 青
kind: [整数論]
prerequisites: [ext-gcd]
related: [divisor-count-bound, fft-ntt, gcd-lcm]
summary: 複数の合同式 x ≡ r_i (mod m_i) を同時に満たす x を、拡張ユークリッドで2式ずつ合わせて mod lcm でただ1つに求める。解があるのは r1 ≡ r2 (mod gcd(m1, m2)) のときだけである。
complexity: null
signs:
  - {type: phrase, text: 周期の違う複数の条件が同時に成り立つ最初の時刻}
  - {type: phrase, text: x を m_i で割った余り r_i が複数与えられる}
  - {type: phrase, text: 法が素数でない数え上げを素因数ごとに分けて最後に戻す}
acl: [crt]
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 2式の CRT は一次不定方程式を1回解くこと, anchor: two-equations}
  - {title: 法が互いに素でないときの解の存在条件, anchor: non-coprime}
  - {title: 多数の式を順に合わせる・lcm のあふれ, anchor: many-equations}
  - {title: Garner のアルゴリズム（巨大な解を mod で求める）, anchor: garner, level: 黄}
  - {title: 'ACL の crt（解がなければ (0, 0)）', anchor: acl}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：複数の合同式 x ≡ r_i (mod m_i) を同時に満たす x を、拡張ユークリッドで2式ずつ合わせて mod lcm でただ1つに求める。解があるのは r1 ≡ r2 (mod gcd(m1, m2)) のときだけである。
    - **いつ使うか**：
        - 周期の違う複数の条件が同時に成り立つ最初の時刻
        - x を m_i で割った余り r_i が複数与えられる
        - 法が素数でない数え上げを素因数ごとに分けて最後に戻す
    - **計算量**：（執筆時に書く）
    - **前提**：[拡張ユークリッドの互除法と一次合同式](../math/ext-gcd.md)
