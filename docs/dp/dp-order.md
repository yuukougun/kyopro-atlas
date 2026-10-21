---
id: dp-order
title: DP の計算順序
aliases: [計算順序, ループの順番, 後ろから DP, 逆順 DP]
type: technique
field: dp
chapter: DP の考え方
order: 40
level: 水
kind: [DP]
prerequisites: [dp-basics]
related: [dp-dag, memoized-recursion, interval-dp, bit-dp, dp-reconstruction, reverse-thinking#decide-from-back, expected-value-dp#order, game-basics#win-lose]
summary: dp[x] を計算する時点で、依存する値がすべて確定している順に状態を回す。添字の昇順に限らず、後ろから・値の順・区間の長さ順・集合の包含順などを依存の向きから選ぶ。
complexity: null
signs:
  - {type: phrase, text: 値の小さい（大きい）方へしか移れない}
  - {type: phrase, text: ゴールに着いたら終わり・残り回数が 0 になったら終わり（終わりの値が分かっている）}
  - {type: shape, text: 'dp[i] が dp[j]（j > i）から決まる（i 番目以降で最適に行動したときの値）'}
acl: []
frequency: B
frequency_evidence: recent 0・前提として 11 ページに届く（直接 3）・古い ABC 6 問
sections:
  - {title: 依存グラフと計算順序の原則（閉路があれば DP にならない）, anchor: dependency}
  - {title: 典型の順序（添字・逆順・値の順・区間の長さ順・集合の昇順・木の帰りがけ順）, anchor: typical-orders}
  - {title: 後ろから解くサイン（終わりの値が分かっている・辞書順最小の復元）, anchor: backward}
  - {title: 期待値 DP・ゲーム DP の計算順序（確率・期待値・ゲームの章へ）, anchor: expectation-and-games}
  - {title: 落とし穴：2 重ループの内外の順・逆順の境界・配る形で未確定の値を配る, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：dp[x] を計算する時点で、依存する値がすべて確定している順に状態を回す。添字の昇順に限らず、後ろから・値の順・区間の長さ順・集合の包含順などを依存の向きから選ぶ。
    - **いつ使うか**：
        - 値の小さい（大きい）方へしか移れない
        - ゴールに着いたら終わり・残り回数が 0 になったら終わり（終わりの値が分かっている）
        - dp[i] が dp[j]（j > i）から決まる（i 番目以降で最適に行動したときの値）
    - **計算量**：（執筆時に書く）
    - **前提**：[DP の基本](../dp/dp-basics.md)
