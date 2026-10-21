---
id: operation-sequence
title: 操作列とクエリ
aliases: [クエリの列, 操作の列, 逆順処理, シミュレーション]
type: pattern
field: patterns
order: 100
level: null
kind: [案内, クエリ処理の工夫, データ構造]
prerequisites: []
related: [global-offset, linked-list, stack-techniques, interval-set, union-find-applications, reverse-thinking, union-find-connectivity, offline-queries, mo-algorithm, event-sort, segment-tree, lazy-segment-tree, sqrt-decomposition, persistent-data-structures, root-path-dfs, rollback-union-find, periodicity, doubling]
summary: 操作やクエリが Q 個続く問題で、問われ方から処理の仕方を引ける。全体の操作を変数で持つ、後ろから見る、削除を逆順の追加にする、先読みして並べ替える、過去の版に戻る、周期で打ち切る、などの型に分ける。
complexity: null
signs:
  - {type: phrase, text: 辺や頂点を 1 つずつ削除するたびに、連結成分の数を答える}
  - {type: phrase, text: 全体に加算する・全体を反転する操作が混ざる}
  - {type: phrase, text: 過去の状態に戻す・ある時点の状態をコピーする}
  - {type: phrase, text: 行や列・区間を塗り替える操作の後の最終状態}
  - {type: phrase, text: 同じ操作を 10^18 回繰り返した後の状態}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: 全体への加算・反転・回転 → 全体の操作を変数で持つ（global-offset）, anchor: global-ops}
  - {title: '列の途中への挿入・削除・付け替え → 配列で持つ連結リスト・deque（linked-list, stack-techniques）', anchor: insert-delete}
  - {title: '区間を塗る・同じ値の区間をつなぐ → 区間を set で管理・次の空きへ飛ぶ Union-Find（interval-set, union-find-applications）', anchor: paint}
  - {title: 後の操作が前の操作を上書きする → 後ろから見る（reverse-thinking）, anchor: overwrite}
  - {title: 削除が難しい → 逆順にして追加にする（union-find-connectivity）, anchor: reverse-deletion}
  - {title: '先読みしてよい → 並べ替えてまとめて処理・Mo・イベントにして走査（offline-queries, mo-algorithm, event-sort）', anchor: offline}
  - {title: '更新と質問が交互で区間を扱う → セグメント木・遅延セグメント木・平方分割（segment-tree, lazy-segment-tree, sqrt-decomposition）', anchor: online}
  - {title: '過去の版に戻る・版をコピーする → 版の木・永続データ構造（persistent-data-structures, root-path-dfs, rollback-union-find）', anchor: versions}
  - {title: '同じ操作を非常に多く繰り返す → 周期で打ち切る・操作の合成をダブリング（periodicity, doubling）', anchor: repeat}
  - {title: 落とし穴, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：操作やクエリが Q 個続く問題で、問われ方から処理の仕方を引ける。全体の操作を変数で持つ、後ろから見る、削除を逆順の追加にする、先読みして並べ替える、過去の版に戻る、周期で打ち切る、などの型に分ける。
    - **いつ使うか**：
        - 辺や頂点を 1 つずつ削除するたびに、連結成分の数を答える
        - 全体に加算する・全体を反転する操作が混ざる
        - 過去の状態に戻す・ある時点の状態をコピーする
        - 行や列・区間を塗り替える操作の後の最終状態
        - 同じ操作を 10^18 回繰り返した後の状態
    - **使い方**：（執筆時に書く）
