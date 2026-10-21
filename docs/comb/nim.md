---
id: nim
title: Nim と XOR
aliases: [ニム, ニム和, 石取りゲーム, 上限つき Nim, 逆形 Nim, Bouton の定理, misère Nim]
type: technique
field: comb
chapter: ゲーム
order: 460
level: 水
kind: [ゲーム, ビット演算]
prerequisites: [game-basics, bit-operations]
related: [grundy-number, xor-basis, hadamard-transform, partizan-games]
summary: 山から 1 個以上取り合い最後の石を取った方が勝つゲームは、全山の個数の XOR が 0 なら後手必勝、そうでなければ先手必勝である。XOR が 0 の局面からは必ず 0 でなくなり、0 でない局面からは 0 にできる。
complexity: null
signs:
  - {type: phrase, text: いくつかの山から石を取り合い、最後に取った人が勝ち}
  - {type: phrase, text: 1 回に取れる個数に上限（範囲）がある}
  - {type: phrase, text: 先手が勝てるように最初の配置を変えられるか}
acl: []
frequency: C
frequency_evidence: recent 0・前提として 2 ページに届く（直接 1）・古い ABC 2 問
sections:
  - {title: Bouton の定理と証明の筋, anchor: bouton}
  - {title: 勝つための手（XOR を 0 にする山の選び方）, anchor: winning-move}
  - {title: 上限つき（x mod (k+1)）・範囲つきの変種, anchor: bounded, level: 青}
  - {title: 先手と後手で取れる数が違うとき, anchor: asymmetric, level: 青}
  - {title: 逆形 Nim（最後に取った方が負け）, anchor: misere, level: 発展}
  - {title: 必勝局面の数え上げ（XOR 畳み込み）, anchor: counting, level: 発展}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：山から 1 個以上取り合い最後の石を取った方が勝つゲームは、全山の個数の XOR が 0 なら後手必勝、そうでなければ先手必勝である。XOR が 0 の局面からは必ず 0 でなくなり、0 でない局面からは 0 にできる。
    - **いつ使うか**：
        - いくつかの山から石を取り合い、最後に取った人が勝ち
        - 1 回に取れる個数に上限（範囲）がある
        - 先手が勝てるように最初の配置を変えられるか
    - **計算量**：（執筆時に書く）
    - **前提**：[ゲームの基本と勝敗の DP](../comb/game-basics.md)、[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
