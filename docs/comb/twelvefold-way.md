---
id: twelvefold-way
title: 写像 12 相
aliases: [玉と箱, 玉と箱の数え上げ, 区別する・しない, twelvefold way]
type: hub
field: comb
chapter: 数え上げの基礎
order: 60
level: null
kind: [案内, 数え上げ]
prerequisites: [stars-and-bars]
related: [counting-basics, multinomial-coefficient, bell-number, partition-number, inclusion-exclusion#surjection, counting-dedup]
summary: n 個の玉を k 個の箱に入れる方法を、玉・箱の区別の有無と各箱の個数の制限で 12 通りに分け、各マスの式と行き先のページを引く。箱を区別しないとき k! で割れるのは、どの箱も空でない場合だけである。
complexity: null
signs:
  - {type: phrase, text: 区別しない箱（グループ）に分ける方法の数}
  - {type: phrase, text: 玉（人・数）を箱（グループ・色）に配る方法の数}
  - {type: phrase, text: どの箱にも 1 個以上入れる・空の箱を許す}
acl: []
sections:
  - {title: 12 マスの表と各マスの行き先, anchor: table}
  - {title: 箱を区別しないと k! で割れない理由（空の箱）, anchor: why-not-divide}
  - {title: 全射のマス：二項係数の系統と包除の系統の合流, anchor: surjection}
  - {title: 問題文から区別の有無と制限を読み取る, anchor: reading}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：n 個の玉を k 個の箱に入れる方法を、玉・箱の区別の有無と各箱の個数の制限で 12 通りに分け、各マスの式と行き先のページを引く。箱を区別しないとき k! で割れるのは、どの箱も空でない場合だけである。
    - **いつ使うか**：
        - 区別しない箱（グループ）に分ける方法の数
        - 玉（人・数）を箱（グループ・色）に配る方法の数
        - どの箱にも 1 個以上入れる・空の箱を許す
    - **使い方**：（執筆時に書く）
    - **前提**：[重複組合せ](../comb/stars-and-bars.md)
