---
id: cdq-divide-and-conquer
title: CDQ 分割統治
aliases: [CDQ divide and conquer, 時系列の分割統治, オフラインの分割統治, 3 次元の支配点の数え上げ]
type: overview
field: ds
chapter: クエリ処理の工夫
order: 310
level: 発展
kind: [クエリ処理の工夫, ダブリング・分割統治]
prerequisites: [divide-and-conquer, fenwick-tree]
related: [sweep-line-2d, parallel-binary-search, offline-queries]
summary: 3 次元の支配点の数え上げや、点の追加つきの長方形クエリを、オフラインで O(N log^2 N) で解く。更新とクエリの列を時刻で半分に分け、左の更新が右のクエリに与える影響だけを BIT で処理する。
complexity: null
signs:
  - {type: phrase, text: 3 つの値すべての大小関係を満たす組を数える}
  - {type: phrase, text: 点の追加と長方形の質問が混ざるが、オフラインでよい}
acl: []
verify: [point_add_rectangle_sum]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: 何ができるか（時系列の分割統治で 1 次元を消す）, anchor: what-it-does}
  - {title: 手順（左の更新 → 右のクエリを平面走査で処理する）と計算量 O(N log^2 N), anchor: procedure}
  - {title: 代わりの手（座標が小さいなら 2 次元 BIT、更新がなければ平面走査）, anchor: alternatives}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：3 次元の支配点の数え上げや、点の追加つきの長方形クエリを、オフラインで O(N log^2 N) で解く。更新とクエリの列を時刻で半分に分け、左の更新が右のクエリに与える影響だけを BIT で処理する。
    - **いつ使うか**：
        - 3 つの値すべての大小関係を満たす組を数える
        - 点の追加と長方形の質問が混ざるが、オフラインでよい
    - **計算量**：（執筆時に書く）
    - **前提**：[分割統治](../basics/divide-and-conquer.md)、[BIT（Fenwick Tree）](../ds/fenwick-tree.md)
