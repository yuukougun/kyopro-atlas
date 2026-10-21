---
id: probability-symmetry
title: 対称性で確率を求める
aliases: [どれも同じ確率, ランダムな順列に置き換える, 2 状態に縮める]
type: technique
field: comb
chapter: 確率・期待値
order: 360
level: 水
kind: [確率・期待値, 考察]
prerequisites: [probability-basics]
related: [symmetry-pigeonhole-casework#symmetry, linearity-of-expectation, probability-dp, counting-fix-order]
summary: 入れ替えても問題が変わらない対象は、どれも同じ確率を持つ。残りから一様に選んでいく過程は一様ランダムな順列を先頭から見る過程と同じなので、状態を特別な 1 つとその他に縮めたり、ペアの大小を確率 1/2 としたりできる。
complexity: null
signs:
  - {type: phrase, text: 一様ランダムにシャッフルする}
  - {type: phrase, text: ランダムに 2 つを選んで入れ替える操作を K 回行う}
  - {type: phrase, text: 残りから一様ランダムに 1 つずつ選ぶ}
  - {type: phrase, text: ランダムな順列での順位・転倒の期待値}
acl: []
frequency: A
frequency_evidence: recent 2（abc464_f・abc473_g）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 入れ替えで移り合う事象は同じ確率, anchor: symmetry}
  - {title: 特別な 1 つとその他に縮める（2 状態）, anchor: two-states}
  - {title: 残りから一様に選ぶ = ランダムな順列, anchor: random-permutation}
  - {title: ペアの大小は確率 1/2, anchor: pairs}
  - {title: 対称でない要素（初期位置・特別な要素）に注意する, anchor: asymmetric}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：入れ替えても問題が変わらない対象は、どれも同じ確率を持つ。残りから一様に選んでいく過程は一様ランダムな順列を先頭から見る過程と同じなので、状態を特別な 1 つとその他に縮めたり、ペアの大小を確率 1/2 としたりできる。
    - **いつ使うか**：
        - 一様ランダムにシャッフルする
        - ランダムに 2 つを選んで入れ替える操作を K 回行う
        - 残りから一様ランダムに 1 つずつ選ぶ
        - ランダムな順列での順位・転倒の期待値
    - **計算量**：（執筆時に書く）
    - **前提**：[確率の基本](../comb/probability-basics.md)
