---
id: run-length-encoding
title: ランレングス圧縮
aliases: [連長圧縮, RLE, 塊ごとに考える, run-length encoding]
type: technique
field: basics
chapter: 尺取り法とランレングス圧縮
order: 180
level: 基礎
kind: [文字列, 考察]
prerequisites: []
related: [two-pointers, string-basics, invariant, difference-sequence]
summary: 同じ値（文字）の連続を（値, 長さ）の組にして、塊の単位で考える。多くの操作は塊の内部では一様で境界でだけ変化するので、境界の数や塊の列の尺取りで考えられる。
complexity: null
signs:
  - {type: phrase, text: 同じ文字・値が続く部分}
  - {type: phrase, text: 区間を反転して 1 の連続を最長にする}
  - {type: phrase, text: 操作で塊（境界）の数がいくつ減るか}
  - {type: phrase, text: ランレングス形式で与えられる入力}
acl: []
frequency: B
frequency_evidence: recent 1（abc452_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 塊への分け方（最後の塊を忘れない・番兵の塊）, anchor: split}
  - {title: 境界の数で操作を数える, anchor: count-boundaries}
  - {title: 塊の列で尺取りする, anchor: two-pointers-on-runs}
  - {title: 塊ごとに偶奇で振り分ける, anchor: parity-per-run}
  - {title: ランレングスのまま処理する, anchor: keep-compressed, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：同じ値（文字）の連続を（値, 長さ）の組にして、塊の単位で考える。多くの操作は塊の内部では一様で境界でだけ変化するので、境界の数や塊の列の尺取りで考えられる。
    - **いつ使うか**：
        - 同じ文字・値が続く部分
        - 区間を反転して 1 の連続を最長にする
        - 操作で塊（境界）の数がいくつ減るか
        - ランレングス形式で与えられる入力
    - **計算量**：（執筆時に書く）
    - **前提**：なし
