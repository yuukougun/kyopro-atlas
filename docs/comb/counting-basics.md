---
id: counting-basics
title: 和・積の法則と順列・組合せ
aliases: [和の法則, 積の法則, 円順列, 重複順列, nPr, 塗り分けの数, rule of product]
type: technique
field: comb
chapter: 数え上げの基礎
order: 10
level: 基礎
kind: [数え上げ]
prerequisites: []
related: [binomial-coefficient, counting-mindset, counting-fix-order, twelvefold-way, mod-pow, dp-state-design]
summary: 排反な場合分けは足し、独立な段階の選択は掛けて数える。積の法則は前の段階で何を選んでも次の選択肢の数が同じときだけ使え、円環の塗り分けでは最後の要素の選択肢の数が変わる。
complexity: null
signs:
  - {type: phrase, text: 隣り合うもの（距離 2 以内のもの）が異なるように塗り分ける方法の数}
  - {type: phrase, text: 円形に並べる・円環で最後と最初も隣り合う}
  - {type: constraint, text: N ≤ 10^18 で、答えが段階ごとの選択肢の数の積になる}
  - {type: shape, text: 答えが K(K−1)^(N−1) のような累乗の積の形になる}
acl: []
frequency: A
frequency_evidence: recent 0・前提として 40 ページに届く（直接 2）・古い ABC 2 問
sections:
  - {title: 和の法則と積の法則（積の法則が使える条件）, anchor: sum-and-product}
  - {title: 順列・組合せ・重複順列・円順列, anchor: permutations}
  - {title: 一列の塗り分けと円環の塗り分け, anchor: coloring}
  - {title: 決める順番を変えて積の法則を使えるようにする, anchor: order-of-choice}
  - {title: 写像 12 相の「玉も箱も区別する」マス（k^n と順列）, anchor: twelvefold-cells}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：排反な場合分けは足し、独立な段階の選択は掛けて数える。積の法則は前の段階で何を選んでも次の選択肢の数が同じときだけ使え、円環の塗り分けでは最後の要素の選択肢の数が変わる。
    - **いつ使うか**：
        - 隣り合うもの（距離 2 以内のもの）が異なるように塗り分ける方法の数
        - 円形に並べる・円環で最後と最初も隣り合う
        - N ≤ 10^18 で、答えが段階ごとの選択肢の数の積になる
        - 答えが K(K−1)^(N−1) のような累乗の積の形になる
    - **計算量**：（執筆時に書く）
    - **前提**：なし
