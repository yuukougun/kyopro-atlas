---
id: ordered-set
title: set・multiset・map の応用
aliases: [順序付き集合, ordered set, 'set::lower_bound', 前後の要素, 番兵, パレート境界]
type: technique
field: ds
chapter: 標準コンテナの応用
order: 20
level: 基礎
kind: [データ構造]
prerequisites: [stl-containers]
related: [interval-set, kth-element, priority-queue, top-k-multiset, binary-trie, mex, hashing-for-sets, binary-search, cpp-container-idioms#iterators]
summary: set・multiset・map の lower_bound で「x 以上の最小」「x 未満の最大」を O(log N) で求め、要素の追加・削除と組み合わせる。番兵で端の場合分けを消し、mex や同じ行・列の次の要素も同じ形で求める。
complexity: null
signs:
  - {type: phrase, text: x 以上で最小の値・最も近い値を、追加・削除しながら何度も答える}
  - {type: phrase, text: まだ使われていない最小の値（mex）を更新のたびに答える}
  - {type: phrase, text: 同じ行・同じ列で次にある壁や家を見つけて壊す}
  - {type: constraint, text: 値が 10^9 まであり、配列の添字にできない}
acl: []
verify: [predecessor_problem, double_ended_priority_queue]
frequency: A
frequency_evidence: recent 2（abc466_f・abc475_e）・前提として 8 ページに届く（直接 6）・古い ABC 8 問
sections:
  - {title: 前後の要素（lower_bound とその 1 つ前。番兵で端の場合分けを消す）, anchor: neighbors}
  - {title: K 番目付近（イテレータを K 歩動かす。K が小さいときだけ）, anchor: near-kth}
  - {title: まだ出ていない値の set で mex を管理する（→ 題材別の mex）, anchor: mex}
  - {title: 行ごと・列ごとの set（グリッドで次の壁を探し、両方から消す）, anchor: rows-and-columns, level: 水}
  - {title: パレート境界を map で持つ（支配される点を消す。ならし O(log N)）, anchor: pareto, level: 水}
  - {title: ソート順で隣り合う組の集合（2 番目に大きい値の寄与。最小 XOR の組は Binary Trie のページ）, anchor: adjacent-pairs, level: 青}
  - {title: 落とし穴（multiset の erase・end と begin の前の参照・イテレータの無効化）, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：set・multiset・map の lower_bound で「x 以上の最小」「x 未満の最大」を O(log N) で求め、要素の追加・削除と組み合わせる。番兵で端の場合分けを消し、mex や同じ行・列の次の要素も同じ形で求める。
    - **いつ使うか**：
        - x 以上で最小の値・最も近い値を、追加・削除しながら何度も答える
        - まだ使われていない最小の値（mex）を更新のたびに答える
        - 同じ行・同じ列で次にある壁や家を見つけて壊す
        - 値が 10^9 まであり、配列の添字にできない
    - **計算量**：（執筆時に書く）
    - **前提**：[STL コンテナの使い分け](../ds/stl-containers.md)
