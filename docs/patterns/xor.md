---
id: xor
title: XOR
aliases: [排他的論理和, ビットごとの排他的論理和, exclusive or]
type: pattern
field: patterns
order: 70
level: null
kind: [案内, ビット演算, 線形代数・行列]
prerequisites: [bit-operations]
related: [bitwise-independence, prefix-sum, fenwick-tree, tree-distance, binary-trie, xor-basis, digit-dp, two-pointers, meet-in-the-middle, nim, grundy-number, hashing-for-sets, hadamard-transform]
summary: XOR が出てくる問題で、問われ方から使う手法を引ける。桁ごとに独立で、同じ値どうしで打ち消し合う、という 2 つの性質から、桁ごとの数え上げ・累積 XOR・XOR 基底・Binary Trie・Nim・集合のハッシュへつなぐ。
complexity: null
signs:
  - {type: phrase, text: すべての組・すべての区間の XOR の総和}
  - {type: phrase, text: x を選んで XOR の最大値・最小値を求める}
  - {type: phrase, text: いくつか選んだ XOR で作れる値・作れる値の個数・K 番目}
  - {type: phrase, text: 区間の XOR・木のパスの XOR・経路の XOR}
  - {type: phrase, text: 石を取り合うゲームで、山の石の数の XOR}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: 全ペア・全区間の XOR の和 → 桁ごとに 0 と 1 の個数を数える（bitwise-independence）, anchor: sum-of-xor}
  - {title: '区間の XOR → 累積 XOR、更新があれば BIT（prefix-sum, fenwick-tree）', anchor: range-xor}
  - {title: 木の 2 点間のパスの XOR → 根からの XOR どうしの XOR（tree-distance）, anchor: tree-path}
  - {title: x を選んで XOR の最大・最小、2 要素の XOR の最小 → 上位ビットから決める・Binary Trie, anchor: choose-x}
  - {title: 選んだ XOR で作れる値・最大値・K 番目 → XOR 基底（xor-basis）, anchor: basis}
  - {title: グラフの経路の XOR の最小 → 閉路の XOR を基底にする（xor-basis）, anchor: path-xor}
  - {title: XOR が絡む条件を満たす数の個数 → 桁 DP（digit-dp）, anchor: digit-dp}
  - {title: XOR と和が等しい区間の数 → 尺取り法（two-pointers）, anchor: xor-equals-sum}
  - {title: 小さいグリッドの経路の XOR → 半分全列挙（meet-in-the-middle）, anchor: meet-in-the-middle}
  - {title: '石取りゲーム → Nim・Grundy 数（nim, grundy-number）', anchor: games}
  - {title: 2 つの集合が一致するか → 乱数の XOR によるハッシュ（hashing-for-sets）, anchor: set-hash}
  - {title: 添字の XOR で畳み込む → アダマール変換（hadamard-transform）, anchor: xor-convolution}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：XOR が出てくる問題で、問われ方から使う手法を引ける。桁ごとに独立で、同じ値どうしで打ち消し合う、という 2 つの性質から、桁ごとの数え上げ・累積 XOR・XOR 基底・Binary Trie・Nim・集合のハッシュへつなぐ。
    - **いつ使うか**：
        - すべての組・すべての区間の XOR の総和
        - x を選んで XOR の最大値・最小値を求める
        - いくつか選んだ XOR で作れる値・作れる値の個数・K 番目
        - 区間の XOR・木のパスの XOR・経路の XOR
        - 石を取り合うゲームで、山の石の数の XOR
    - **使い方**：（執筆時に書く）
    - **前提**：[bit 演算の基本と XOR の性質](../basics/bit-operations.md)
