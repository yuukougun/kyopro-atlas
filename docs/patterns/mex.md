---
id: mex
title: mex
aliases: [minimum excluded, 含まれない最小の非負整数, まだ出ていない最小の値]
type: pattern
field: patterns
order: 50
level: null
kind: [案内, データ構造, 考察]
prerequisites: []
related: [ordered-set, segment-tree-binary-search, interval-set, fix-variable, contribution, two-pointers, lazy-segment-tree, grundy-number, construction]
summary: 集合に含まれない最小の非負整数 mex を求める・更新する・総和を取る問題で、問われ方から使う手法を引ける。「N 要素の mex は N 以下」「mex ≥ k+1 ⇔ 0〜k をすべて含む」の 2 つの性質から考える。
complexity: null
signs:
  - {type: phrase, text: 含まれない最小の非負整数（mex）を答える}
  - {type: phrase, text: 1 点を書き換えるたびに数列の mex を答える}
  - {type: phrase, text: 長さ M の全区間の mex の最小値}
  - {type: phrase, text: 全区間・全パスの mex の総和}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: 更新のたびに mex を答える → 出現回数 0 の値の set・セグメント木上の二分探索, anchor: online-mex}
  - {title: 値が区間でまとめて入る → 区間を set で管理（interval-set）, anchor: interval-values}
  - {title: 区間・窓の mex の最小値・最大値 → 値を固定して出現位置の間隔を見る（fix-variable）, anchor: window-mex}
  - {title: 全区間・全パスの mex の総和 → mex が k+1 以上の数を足す主客転倒, anchor: sum-of-mex}
  - {title: ゲームの局面の値 → Grundy 数（grundy-number）, anchor: grundy}
  - {title: mex を指定した値にする構築 → 0〜k−1 を入れて k を入れない（construction）, anchor: construction}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：集合に含まれない最小の非負整数 mex を求める・更新する・総和を取る問題で、問われ方から使う手法を引ける。「N 要素の mex は N 以下」「mex ≥ k+1 ⇔ 0〜k をすべて含む」の 2 つの性質から考える。
    - **いつ使うか**：
        - 含まれない最小の非負整数（mex）を答える
        - 1 点を書き換えるたびに数列の mex を答える
        - 長さ M の全区間の mex の最小値
        - 全区間・全パスの mex の総和
    - **使い方**：（執筆時に書く）
