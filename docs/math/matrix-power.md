---
id: matrix-power
title: 行列累乗
aliases: [行列の累乗, matrix exponentiation, 行列累乗 DP, 遷移行列, 隣接行列の累乗, min-plus 行列, '(max,+) 行列', 半環の行列]
type: technique
field: math
chapter: 行列と線形代数
order: 320
level: 青
kind: [線形代数・行列, DP, ダブリング・分割統治]
prerequisites: [mod-pow, dp-state-design]
related: [doubling, geometric-series-mod, linear-recurrence-fast, segment-tree-monoids#matrix, warshall-floyd, string-automaton-dp, broken-profile-dp, dp-speedup-overview, dynamic-dp]
summary: 状態が毎回同じ線形の遷移 v' = Av で変わるとき、K 回後の A^K v を行列の繰り返し二乗法で O(n³ log K) で求める。DP の遷移や、足し算と掛け算を min と + に替えた行列にも使える。
complexity: null
signs:
  - {type: constraint, text: 状態数 n ≤ 100 程度で、繰り返しの回数 K が 10^9〜10^18}
  - {type: phrase, text: 漸化式の第 N 項（N ≤ 10^18）}
  - {type: phrase, text: グラフでちょうど K 歩の経路の数・K 本の辺を使う最短路}
  - {type: phrase, text: 長さ 10^18 の文字列のうち、禁止された部分文字列を含まないものの数}
  - {type: phrase, text: 幅の小さい盤を長く伸ばしたときの敷き詰め方の数}
  - {type: shape, text: 'dp[t+1] の各成分が dp[t] の成分の線形結合で、係数が t によらない'}
acl: []
verify: [matrix_product, pow_of_matrix]
frequency: A
frequency_evidence: recent 3（abc456_f・abc458_f・abc469_g）・前提として 3 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: 漸化式・状態の遷移を行列で書く（定数項を状態に入れる）, anchor: write-as-matrix}
  - {title: 行列の積と繰り返し二乗法（積の向き・単位行列・n³ log K の見積もり・mod の掛け算のあふれ）, anchor: fast-power}
  - {title: 隣接行列の K 乗と長さ K の経路の数, anchor: adjacency-power}
  - {title: DP の遷移を行列にする（照合の状態・末尾の数文字・グリッドの境界の状態）, anchor: dp-transition}
  - {title: '(min,+)・(max,+) などの半環の行列と単位元・零元', anchor: semiring}
  - {title: 累乗でなく合成として使う（アフィン変換の積）, anchor: composition}
  - {title: ダブリングで遷移を合成する（行列にすると大きすぎるとき・桁を倍々に伸ばす）, anchor: doubling-transition, level: 黄}
  - {title: プロファイル DP の遷移行列と状態数の見積もり, anchor: profile-dp, level: 黄}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：状態が毎回同じ線形の遷移 v' = Av で変わるとき、K 回後の A^K v を行列の繰り返し二乗法で O(n³ log K) で求める。DP の遷移や、足し算と掛け算を min と + に替えた行列にも使える。
    - **いつ使うか**：
        - 状態数 n ≤ 100 程度で、繰り返しの回数 K が 10&#94;9〜10&#94;18
        - 漸化式の第 N 項（N ≤ 10^18）
        - グラフでちょうど K 歩の経路の数・K 本の辺を使う最短路
        - 長さ 10^18 の文字列のうち、禁止された部分文字列を含まないものの数
        - 幅の小さい盤を長く伸ばしたときの敷き詰め方の数
        - dp[t+1] の各成分が dp[t] の成分の線形結合で、係数が t によらない
    - **計算量**：（執筆時に書く）
    - **前提**：[繰り返し二乗法](../math/mod-pow.md)、[DP の状態の設計](../dp/dp-state-design.md)
