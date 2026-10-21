---
id: bitset-speedup
title: bitset による高速化
aliases: [bitset, ビット並列, ワード並列, 1/64 倍, bitset で部分和, 推移閉包, 到達可能性クエリ, bitset speedup]
type: technique
field: misc
order: 30
level: 青
kind: [ビット演算, 計算量, DP]
prerequisites: [bit-operations, complexity-estimation]
related: [subset-sum, topological-sort, scc#condensation, cpp-math-functions#bitset, gaussian-elimination#mod-2, xor-basis, bit-dp]
summary: bool を 64 個ずつ 1 語に詰め、AND・OR・XOR・シフトを語単位で行って計算量をおよそ 1/64 にする。部分和 DP のシフト OR、共通の隣接頂点・三角形の数え上げ、偶奇の集計、DAG の到達可能性に使う。
complexity: null
signs:
  - {type: constraint, text: N ≤ 2000〜5000 程度で、O(N^3) や O(N^2 M) が少し間に合わない}
  - {type: phrase, text: 部分和として作れる値か（和の上限が 10^5〜10^6）}
  - {type: phrase, text: 2 頂点の共通の隣接頂点・三角形の数}
  - {type: phrase, text: 偶奇（XOR）だけ分かればよい}
  - {type: phrase, text: u から v へ到達できるかのクエリが大量にある}
  - {type: constraint, text: N が 5×10^4 程度で N^2/64 の計算が間に合う}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 6 問
sections:
  - {title: ワード並列の考え方と計算量の目安（N^3/64）, anchor: word-parallel}
  - {title: 共通の隣接頂点・三角形の数（行の AND と popcount）, anchor: common-neighbors}
  - {title: 偶奇だけの集計（XOR）, anchor: parity-xor}
  - {title: 部分和 DP のシフト OR, anchor: subset-sum-shift, level: 黄}
  - {title: DAG の到達可能性（逆トポロジカル順に OR、閉路は SCC で縮約）, anchor: reachability, level: 黄}
  - {title: メモリの見積もりと 64 個ずつのクエリの処理, anchor: memory-batching, level: 黄}
  - {title: C++ の作法（大きさはコンパイル時の定数・大きな bitset をスタックに置かない）, anchor: cpp}
  - {title: bitDP との違い, anchor: vs-bit-dp}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：bool を 64 個ずつ 1 語に詰め、AND・OR・XOR・シフトを語単位で行って計算量をおよそ 1/64 にする。部分和 DP のシフト OR、共通の隣接頂点・三角形の数え上げ、偶奇の集計、DAG の到達可能性に使う。
    - **いつ使うか**：
        - N ≤ 2000〜5000 程度で、O(N^3) や O(N^2 M) が少し間に合わない
        - 部分和として作れる値か（和の上限が 10&#94;5〜10&#94;6）
        - 2 頂点の共通の隣接頂点・三角形の数
        - 偶奇（XOR）だけ分かればよい
        - u から v へ到達できるかのクエリが大量にある
        - N が 5×10^4 程度で N^2/64 の計算が間に合う
    - **計算量**：（執筆時に書く）
    - **前提**：[bit 演算の基本と XOR の性質](../basics/bit-operations.md)、[計算量の見積もり](../basics/complexity-estimation.md)
