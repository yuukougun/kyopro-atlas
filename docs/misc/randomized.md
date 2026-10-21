---
id: randomized
title: 乱択アルゴリズム
aliases: [乱択, ランダム化, モンテカルロ法, ラスベガス法, 過半数, Boyer-Moore の投票, Color Coding, randomized algorithm]
type: technique
field: misc
order: 20
level: 青
kind: [ハッシュ・乱択]
prerequisites: [probability-basics]
related: [hash-safety#what-to-randomize, hashing-for-sets, rolling-hash, cpp-math-functions#random, circle-geometry#min-enclosing-circle, bit-dp]
summary: 乱数を使って、一定の確率で誤るが速い方法（モンテカルロ法）や、常に正しいが時間が確率的な方法（ラスベガス法）を作る。成功確率 p の試行を k 回繰り返すと失敗確率は (1 − p)^k になるので、回数を見積もって決める。
complexity: null
signs:
  - {type: phrase, text: 半数を超える要素が条件を満たす（過半数）}
  - {type: constraint, text: K ≤ 10 程度の少数の要素を選ぶ条件で、要素の種類が多い}
  - {type: shape, text: 決定的な方法は重いが、確率的に正しければ十分に速い}
  - {type: shape, text: 固定の mod・係数のハッシュが、作為的な入力で衝突させられる}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: モンテカルロ法とラスベガス法, anchor: monte-carlo-las-vegas}
  - {title: 失敗確率の見積もりと試行回数（(1 − p)^k）, anchor: failure-probability}
  - {title: 過半数の扱い（ランダムな 2 つを選ぶ・Boyer-Moore の投票）, anchor: majority}
  - {title: Color Coding, anchor: color-coding, level: 黄}
  - {title: C++ の乱数（mt19937_64・時間計測）, anchor: cpp-random}
  - {title: 焼きなましなどのヒューリスティックは ABC の範囲外（AHC）, anchor: heuristics}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：乱数を使って、一定の確率で誤るが速い方法（モンテカルロ法）や、常に正しいが時間が確率的な方法（ラスベガス法）を作る。成功確率 p の試行を k 回繰り返すと失敗確率は (1 − p)^k になるので、回数を見積もって決める。
    - **いつ使うか**：
        - 半数を超える要素が条件を満たす（過半数）
        - K ≤ 10 程度の少数の要素を選ぶ条件で、要素の種類が多い
        - 決定的な方法は重いが、確率的に正しければ十分に速い
        - 固定の mod・係数のハッシュが、作為的な入力で衝突させられる
    - **計算量**：（執筆時に書く）
    - **前提**：[確率の基本](../comb/probability-basics.md)
