---
id: integer-division
title: 整数の割り算と余り
aliases: [floor_div, floor division, 切り捨て除算, 切り上げ, 負の数の割り算, 負の数の余り, オーバーフロー判定, 割り算で比較]
type: technique
field: math
chapter: 式と整数の基本
order: 20
level: 基礎
kind: [整数論]
prerequisites: []
related: [notation, mod-arithmetic, integer-root, cpp-math-functions, cpp-integer-overflow#overflow-check]
summary: 負の数を含む割り算・余り・切り上げや区間の倍数の個数を、C++ の / と % の切り捨ての向きに注意して正しく求める。積があふれるかどうかも、掛ける前に割り算で判定する。
complexity: null
signs:
  - {type: constraint, text: 入力に負の数（|X| ≤ 10^18 など）があり、割り算・余り・切り上げを使う}
  - {type: constraint, text: 積・lcm・累乗が 10^18 を超えうる（long long の上限は約 9.2×10^18）}
  - {type: phrase, text: x 以上で、m で割って r 余る最小の数}
  - {type: phrase, text: '[L, R] にある K の倍数の個数'}
  - {type: phrase, text: 一定の間隔で発車する・周期的に起こる出来事の、ある時刻以降で最初のもの}
acl: []
verify: []
frequency: A
frequency_evidence: recent 1（abc460_e）・前提として 67 ページに届く（直接 6）・古い ABC 6 問
sections:
  - {title: C++ の / と % と、数学の floor・mod の違い, anchor: cpp-vs-math}
  - {title: 負の数でも正しい floor_div・ceil_div・safe_mod, anchor: floor-ceil}
  - {title: 切り上げ ⌈a/b⌉ = ⌊(a+b−1)/b⌋ が使える条件, anchor: ceil-formula}
  - {title: '区間 [L, R] の K の倍数の個数と、x 以上で m で割って r 余る最小の数', anchor: count-multiples}
  - {title: あふれる前に割り算で判定する（a > L / b）と __int128 への逃げ方, anchor: overflow}
  - {title: double で割らない（10^18 付近の誤差）, anchor: no-double}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：負の数を含む割り算・余り・切り上げや区間の倍数の個数を、C++ の / と % の切り捨ての向きに注意して正しく求める。積があふれるかどうかも、掛ける前に割り算で判定する。
    - **いつ使うか**：
        - 入力に負の数（|X| ≤ 10^18 など）があり、割り算・余り・切り上げを使う
        - 積・lcm・累乗が 10^18 を超えうる（long long の上限は約 9.2×10^18）
        - x 以上で、m で割って r 余る最小の数
        - [L, R] にある K の倍数の個数
        - 一定の間隔で発車する・周期的に起こる出来事の、ある時刻以降で最初のもの
    - **計算量**：（執筆時に書く）
    - **前提**：なし
