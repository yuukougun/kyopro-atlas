---
id: gaussian-elimination
title: 掃き出し法
aliases: [ガウスの消去法, Gaussian elimination, Gauss-Jordan, 連立一次方程式, ランク, ライツアウト, mod 2 の連立方程式]
type: technique
field: math
chapter: 行列と線形代数
order: 330
level: 青
kind: [線形代数・行列]
prerequisites: [mod-inverse]
related: [xor-basis, determinant, bit-full-search, bitset-speedup, lagrange-interpolation, expectation-linear-equations]
summary: 行基本変形で行列を階段形にし、連立一次方程式の解なし・一意・無数を判定してランクを O(n³) で求める。mod 2 では XOR で消去して bitset で速くでき、解の個数は 2^(変数の数 − ランク) になる。
complexity: null
signs:
  - {type: phrase, text: スイッチを押すと複数のランプが反転する・偶奇の条件が N 個ある}
  - {type: phrase, text: 条件を満たす押し方の数を mod で答える}
  - {type: phrase, text: 各頂点に書いた値の、隣接する頂点の XOR が 0 になるように決める}
  - {type: constraint, text: 変数・式の数が数百〜2000 程度で O(n³) や O(n³/64)}
  - {type: shape, text: 変数の一次式（mod 2 なら XOR）＝定数 の式が複数立つ}
acl: []
verify: [system_of_linear_equations, system_of_linear_equations_mod_2, matrix_rank, matrix_rank_mod_2, inverse_matrix]
frequency: B
frequency_evidence: recent 0・前提として 3 ページに届く（直接 1）・古い ABC 3 問
sections:
  - {title: 行基本変形と階段形、解なし（0 = 1）・一意・無数の判定, anchor: row-reduction}
  - {title: mod p の掃き出し（ピボットで割る＝逆元）, anchor: mod-p}
  - {title: mod 2 の掃き出しは XOR、bitset で速くする, anchor: mod-2}
  - {title: ランクと解の個数 p^(n − rank), anchor: rank}
  - {title: 実数の掃き出し（部分ピボット選択と誤差）, anchor: real}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：行基本変形で行列を階段形にし、連立一次方程式の解なし・一意・無数を判定してランクを O(n³) で求める。mod 2 では XOR で消去して bitset で速くでき、解の個数は 2^(変数の数 − ランク) になる。
    - **いつ使うか**：
        - スイッチを押すと複数のランプが反転する・偶奇の条件が N 個ある
        - 条件を満たす押し方の数を mod で答える
        - 各頂点に書いた値の、隣接する頂点の XOR が 0 になるように決める
        - 変数・式の数が数百〜2000 程度で O(n³) や O(n³/64)
        - 変数の一次式（mod 2 なら XOR）＝定数 の式が複数立つ
    - **計算量**：（執筆時に書く）
    - **前提**：[逆元と mod での割り算](../math/mod-inverse.md)
