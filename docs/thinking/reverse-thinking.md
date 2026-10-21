---
id: reverse-thinking
title: 後ろから・逆順に考える
aliases: [逆から考える, 操作を逆再生, クエリを逆順に処理, 削除を追加に, work backwards]
type: thinking
field: thinking
order: 70
level: 基礎
kind: [考察, クエリ処理の工夫]
prerequisites: []
related: [union-find-connectivity#reverse-deletion, offline-queries#reverse-time, greedy-priority-queue#from-last-day, invariant]
summary: 後ろから決めると選択肢が一意になる、最後の操作が特定できれば逆再生で取り除ける、削除を逆にすると追加になる、など時間の向きを逆にして考える。
complexity: null
signs:
  - {type: phrase, text: 辺・要素の削除のクエリ}
  - {type: phrase, text: 操作列を復元する・操作の結果から元を求める}
  - {type: shape, text: 後ろから決めると選択肢が 1 つに決まる}
acl: []
frequency: A
frequency_evidence: recent 2（abc466_f・abc477_d）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 後ろから決めると一意になる, anchor: decide-from-back}
  - {title: 最後の操作を特定して逆再生する, anchor: undo-last}
  - {title: 締め切りを後ろから見る, anchor: deadlines}
  - {title: 削除を逆順の追加にする（Union-Find はグラフの章）, anchor: delete-to-add, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：後ろから決めると選択肢が一意になる、最後の操作が特定できれば逆再生で取り除ける、削除を逆にすると追加になる、など時間の向きを逆にして考える。
    - **いつ使うか**：
        - 辺・要素の削除のクエリ
        - 操作列を復元する・操作の結果から元を求める
        - 後ろから決めると選択肢が 1 つに決まる
    - **計算量**：（執筆時に書く）
    - **前提**：なし
