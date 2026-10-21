---
id: global-offset
title: 全体への操作を変数で持つ
aliases: [global offset, オフセット, 全体加算, 反転フラグ, 回転量, 全体に反映させる値を別に持つ]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 60
level: 基礎
kind: [データ構造, クエリ処理の工夫]
prerequisites: [stl-containers]
related: [lazy-segment-tree, priority-queue, stack-techniques, periodicity, complexity-estimation]
summary: 「全要素に x を足す」「全体を反転する」「全体を回転する」を、要素を書き換えずにオフセット・反転フラグ・先頭位置の変数で表す。入れるときに引き、取り出すときに足すのが基本になる。
complexity: null
signs:
  - {type: phrase, text: 全要素に x を足す・全体に代入する操作がクエリに混ざる}
  - {type: phrase, text: 列全体を反転してから先頭・末尾に追加する}
  - {type: phrase, text: 配列を回転してから i 番目を参照する}
  - {type: constraint, text: Q ≤ 2×10^5 で、全体への操作を毎回 O(N) で行うと間に合わない}
acl: []
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 5 問
sections:
  - {title: オフセット（入れるときに引き、出すときに足す）, anchor: offset}
  - {title: 反転フラグ（追加する側や添字の読み方を入れ替え、最後に向きを直す）, anchor: flip-flag}
  - {title: 全体代入と個別の差分（代入のたびに差分の map を空にする。ならし）, anchor: assign-all}
  - {title: 回転は先頭位置の添字で表す, anchor: rotation}
  - {title: 落とし穴（反転中の先頭と末尾の取り違え・向きの直し忘れ・オフセットのあふれ）, anchor: pitfalls}
  - {title: 遅延セグメント木とのつながり（全体への操作を区間への操作に広げる）, anchor: to-lazy-segment-tree, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：「全要素に x を足す」「全体を反転する」「全体を回転する」を、要素を書き換えずにオフセット・反転フラグ・先頭位置の変数で表す。入れるときに引き、取り出すときに足すのが基本になる。
    - **いつ使うか**：
        - 全要素に x を足す・全体に代入する操作がクエリに混ざる
        - 列全体を反転してから先頭・末尾に追加する
        - 配列を回転してから i 番目を参照する
        - Q ≤ 2×10^5 で、全体への操作を毎回 O(N) で行うと間に合わない
    - **計算量**：（執筆時に書く）
    - **前提**：[STL コンテナの使い分け](../ds/stl-containers.md)
