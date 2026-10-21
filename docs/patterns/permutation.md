---
id: permutation
title: 順列と置換
aliases: [permutation, 置換, 1〜N の順列]
type: pattern
field: patterns
order: 30
level: null
kind: [案内, 数え上げ, 考察]
prerequisites: []
related: [permutation-cycles, construction, inversion-number, permutation-parity, functional-graph, doubling, insertion-dp, inclusion-exclusion, binomial-coefficient, bit-full-search, lis]
summary: 1〜N の順列が与えられる問題で、問われ方から使う手法を引ける。i → P_i の矢印のサイクル、swap の回数と偶奇、置換の繰り返し、順列の数え上げ、辞書順の問われ方に分ける。
complexity: null
signs:
  - {type: phrase, text: '(1, 2, …, N) の順列 P が与えられる'}
  - {type: phrase, text: 任意の 2 要素の swap を繰り返してソートする最小回数}
  - {type: phrase, text: 隣り合う 2 要素の swap でソートする最小回数}
  - {type: phrase, text: ちょうど K 回の swap（10^100 回など）で作れる列}
  - {type: phrase, text: 置換を K 回（K ≤ 10^18）適用した結果}
  - {type: phrase, text: 条件を満たす順列の個数}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: '任意の swap でソートする最小回数・手順 → 置換の巡回分解（permutation-cycles, construction）', anchor: any-swap}
  - {title: 隣接 swap でソートする最小回数 → 転倒数（inversion-number）, anchor: adjacent-swap}
  - {title: ちょうど K 回の swap で作れるか → 置換の偶奇（permutation-parity）, anchor: swap-parity}
  - {title: '置換を K 回適用した結果 → サイクルごとの周期・ダブリング（functional-graph, doubling）', anchor: repeat}
  - {title: 位置と値の両方から引く操作 → 逆置換を同時に持つ, anchor: inverse}
  - {title: '条件を満たす順列の数 → 挿入 DP・撹乱順列（insertion-dp, inclusion-exclusion）', anchor: counting}
  - {title: '辞書順で何番目・K 番目の順列 → 残りの並べ方の数・順列全探索（binomial-coefficient, bit-full-search）', anchor: lexicographic}
  - {title: 増加部分列・いくつの増加部分列に分けるか → LIS（lis）, anchor: increasing}
  - {title: 落とし穴, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：1〜N の順列が与えられる問題で、問われ方から使う手法を引ける。i → P_i の矢印のサイクル、swap の回数と偶奇、置換の繰り返し、順列の数え上げ、辞書順の問われ方に分ける。
    - **いつ使うか**：
        - (1, 2, …, N) の順列 P が与えられる
        - 任意の 2 要素の swap を繰り返してソートする最小回数
        - 隣り合う 2 要素の swap でソートする最小回数
        - ちょうど K 回の swap（10^100 回など）で作れる列
        - 置換を K 回（K ≤ 10^18）適用した結果
        - 条件を満たす順列の個数
    - **使い方**：（執筆時に書く）
