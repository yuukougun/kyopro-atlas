---
id: greedy-priority-queue
title: 優先度付きキューを使う貪欲
aliases: [priority_queue で貪欲, ヒープで貪欲, 締め切り付きスケジューリング, 後悔付き貪欲, 小さい順に K 個を列挙, K-best enumeration]
type: technique
field: basics
chapter: 貪欲
order: 260
level: 水
kind: [貪欲, データ構造]
prerequisites: [greedy-basics, priority-queue]
related: [interval-scheduling, reverse-thinking, top-k-multiset, slope-trick, alien-dp#undoable-greedy, kth-value]
summary: 締め切りのある仕事の選び方や、毎回最大（最小）を取り出す操作の繰り返しを、候補を優先度付きキューに入れて O(N log N) で処理する。小さい順に K 個を列挙するときは、取り出したものから次の候補を作って入れる。
complexity: null
signs:
  - {type: phrase, text: 日が進むと選択肢が増え、各日に 1 つ選ぶ}
  - {type: phrase, text: 締め切りまでに何個できるか・報酬の最大}
  - {type: phrase, text: 毎回いちばん大きい（小さい）ものを取り出して更新する}
  - {type: phrase, text: 組合せの和の小さい方から K 番目（K が小さい）}
  - {type: constraint, text: K ≤ 2×10^5 程度で、小さい順に K 個取り出せば足りる}
  - {type: shape, text: 一度選んだものを、後でよいものが来たら入れ替えたい}
acl: []
frequency: B
frequency_evidence: recent 1（abc464_g）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: 毎回最大を取り出す（同じ値はまとめる）, anchor: take-max}
  - {title: 後ろの日から決める（使えるようになった候補をキューに入れる）, anchor: from-last-day}
  - {title: 時刻順に入れて締め切りの早いものから処理する（時刻は次のイベントまで飛ばす）, anchor: earliest-deadline}
  - {title: 最大値を固定して上位 K 個を保つ, anchor: fix-max-keep-k}
  - {title: 小さい順に K 個を列挙する（取り出したら次の候補を入れる）, anchor: k-best}
  - {title: 選んだものを後から入れ替える（後悔付き貪欲。一般形は Alien DP のページ）, anchor: regret}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：締め切りのある仕事の選び方や、毎回最大（最小）を取り出す操作の繰り返しを、候補を優先度付きキューに入れて O(N log N) で処理する。小さい順に K 個を列挙するときは、取り出したものから次の候補を作って入れる。
    - **いつ使うか**：
        - 日が進むと選択肢が増え、各日に 1 つ選ぶ
        - 締め切りまでに何個できるか・報酬の最大
        - 毎回いちばん大きい（小さい）ものを取り出して更新する
        - 組合せの和の小さい方から K 番目（K が小さい）
        - K ≤ 2×10^5 程度で、小さい順に K 個取り出せば足りる
        - 一度選んだものを、後でよいものが来たら入れ替えたい
    - **計算量**：（執筆時に書く）
    - **前提**：[貪欲法の考え方と正当性](../basics/greedy-basics.md)、[優先度付きキュー](../ds/priority-queue.md)
