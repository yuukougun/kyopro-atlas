---
id: brute-force
title: 全探索の設計
aliases: [全列挙, 工夫した全探索, 総当たり, 何を全探索するか, 候補が少ない, 盤面の全探索, ポリオミノ, brute force]
type: technique
field: basics
chapter: 全探索
order: 40
level: 基礎
kind: [全探索]
prerequisites: [complexity-estimation]
related: [bit-full-search, fix-variable, small-graph-brute-force, divisor-count-bound]
summary: 何を全探索するかを選び直して通り数を減らす。いくつか決めれば残りが計算で決まる、答えの候補の側を試す、小さい次元だけを試して残りを速く求める、などの型がある。
complexity: null
signs:
  - {type: phrase, text: 変数が 2〜3 個で、いくつか決めれば残りが計算で決まる}
  - {type: phrase, text: 答えの候補（暗証番号・中心の座標など）が N によらず少ない}
  - {type: constraint, text: 一方の次元だけ極端に小さい（H ≤ 8 など）}
  - {type: constraint, text: K ≤ 10^12 で約数を扱う（約数の個数は最大 6720）}
  - {type: phrase, text: 小さい盤面を回転・平行移動して重ねる・敷き詰める}
acl: []
frequency: A
frequency_evidence: recent 5（abc451_d・abc469_d・abc474_e・abc476_d・abc480_e）・前提として 71 ページに届く（直接 3）・古い ABC 5 問
sections:
  - {title: 何を全探索するか（2 つ決めて 3 つ目を計算する）, anchor: what-to-enumerate}
  - {title: 決めてから整合性を確かめる, anchor: decide-then-check}
  - {title: 候補が少ないことに気づく（答えの側・小さい次元・約数の個数・log 回の収束）, anchor: small-candidates}
  - {title: 片側を全探索して残りを速く求める（貪欲・二分探索・累積和）, anchor: half-enumeration}
  - {title: 盤面を動かして全部試す（回転・平行移動）, anchor: move-board, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：何を全探索するかを選び直して通り数を減らす。いくつか決めれば残りが計算で決まる、答えの候補の側を試す、小さい次元だけを試して残りを速く求める、などの型がある。
    - **いつ使うか**：
        - 変数が 2〜3 個で、いくつか決めれば残りが計算で決まる
        - 答えの候補（暗証番号・中心の座標など）が N によらず少ない
        - 一方の次元だけ極端に小さい（H ≤ 8 など）
        - K ≤ 10^12 で約数を扱う（約数の個数は最大 6720）
        - 小さい盤面を回転・平行移動して重ねる・敷き詰める
    - **計算量**：（執筆時に書く）
    - **前提**：[計算量の見積もり](../basics/complexity-estimation.md)
