---
id: union-find-applications
title: Union-Find の応用
aliases: [UF に情報を持たせる, 併合時の寄与, 成分ごとの集約, 次の空きへ飛ぶ Union-Find, 次の要素へのポインタ, 区間を塗る UF]
type: technique
field: ds
chapter: Union-Find
order: 110
level: 水
kind: [データ構造, 連結性・全域木]
prerequisites: [union-find]
related: [union-find-connectivity, minimum-spanning-tree, small-to-large, merge-process-tree, interval-set, contribution, tree-edge-contribution]
summary: Union-Find の根に成分の情報（サイズ・辺数・上位 K 個・値ごとの個数）を持たせ、併合のときに合成する。辺を重みの順に足して組の数を数える型、区間の和を辺に言い換える型、次の空きへ飛ぶ型がある。
complexity: null
signs:
  - {type: phrase, text: 全頂点対について、パス上の最大の辺の重みの総和}
  - {type: phrase, text: いくつかの区間の和が分かっているとき、全体の和が決まるか}
  - {type: phrase, text: 成分の中で K 番目に大きい番号・成分の中のクラス c の人数}
  - {type: phrase, text: 右にある最初の空き位置に書き込む}
acl: [dsu]
verify: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 9 問
sections:
  - {title: 根に成分の情報を持たせる（根にだけ持ち、併合で合成する。上位 K 個や値ごとの map は小さい方を大きい方へ）, anchor: data-on-root}
  - {title: 併合の瞬間に寄与を数える（辺を重みの昇順に足し、2 つの成分のサイズの積だけ組が決まる）, anchor: count-on-merge}
  - {title: 何を頂点にするかの言い換え（累積和の添字・x 座標と y 座標の二部グラフ・値を頂点に）, anchor: modeling}
  - {title: 次の空きへ飛ぶ Union-Find（区間を一度ずつ塗る。set の lower_bound で代用できる）, anchor: next-pointer}
  - {title: グラフの章との分担（根に情報を持たせる型は Union-Find の応用、削除を逆順の追加にする・しきい値で辺を絞る・Kruskal 法はグラフの章）, anchor: vs-graph}
  - {title: 閾値ごと・関係ごとに Union-Find を持つ（重みごとの Union-Find・2 つの Union-Find の根の組）, anchor: multiple-uf, level: 青}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：Union-Find の根に成分の情報（サイズ・辺数・上位 K 個・値ごとの個数）を持たせ、併合のときに合成する。辺を重みの順に足して組の数を数える型、区間の和を辺に言い換える型、次の空きへ飛ぶ型がある。
    - **いつ使うか**：
        - 全頂点対について、パス上の最大の辺の重みの総和
        - いくつかの区間の和が分かっているとき、全体の和が決まるか
        - 成分の中で K 番目に大きい番号・成分の中のクラス c の人数
        - 右にある最初の空き位置に書き込む
    - **計算量**：（執筆時に書く）
    - **前提**：[Union-Find](../ds/union-find.md)
