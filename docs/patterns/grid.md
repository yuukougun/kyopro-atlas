---
id: grid
title: グリッド
aliases: [マス目, 盤面, H×W, 二次元配列, grid]
type: pattern
field: patterns
order: 90
level: null
kind: [案内, グラフ探索, DP]
prerequisites: []
related: [grid-graph, bfs, zero-one-bfs, extended-dijkstra, union-find, dp-grid, lattice-paths, inclusion-exclusion-dp, prefix-sum-2d, imos, sweep-line-2d, manhattan-chebyshev, coordinate-compression, parity, rotation-transform, brute-force, bipartite-matching, broken-profile-dp, operation-sequence]
summary: H×W のマス目が出てくる問題で、問われ方から使う手法を引ける。マスを頂点とする最短路、右・下に進む DP、長方形の累積和、行と列の独立、市松模様の偶奇、45 度回転、盤面の回転へつなぐ。
complexity: null
signs:
  - {type: phrase, text: H×W のマス目で、スタートからゴールへの最小の移動回数}
  - {type: phrase, text: 右か下にだけ進む経路の数・経路上の値の最大}
  - {type: phrase, text: 長方形の範囲の和・黒マスの個数を多数答える}
  - {type: phrase, text: 1×2 のタイル（ドミノ）を敷き詰める・置く}
  - {type: phrase, text: 盤面を 90 度回転・反転させて一致させる}
  - {type: phrase, text: 斜めに動く駒・マンハッタン距離・ひし形の範囲}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: '最小の移動回数 → グリッドの BFS・01-BFS（grid-graph, bfs, zero-one-bfs）', anchor: shortest}
  - {title: 向き・残り回数などの状態がある・盤面全体が状態 → 状態を頂点にする（extended-dijkstra）, anchor: states}
  - {title: 連結成分・塗りつぶし → DFS・BFS・Union-Find（union-find）, anchor: components}
  - {title: '右か下にだけ進む → グリッドの DP・格子路（dp-grid, lattice-paths）', anchor: right-down}
  - {title: '長方形の和・長方形への加算 → 2 次元累積和・2 次元いもす法（prefix-sum-2d, imos）', anchor: rectangles}
  - {title: 行と列を選ぶ・行と列への操作 → 行と列を独立に考える・別々に座標圧縮, anchor: rows-cols}
  - {title: 到達・敷き詰めの可否 → 市松模様の偶奇（parity）, anchor: checkerboard}
  - {title: 斜めの移動・マンハッタン距離・ひし形の範囲 → 45 度回転・斜めの座標（manhattan-chebyshev）, anchor: diagonal}
  - {title: '盤面の回転・反転・平行移動 → 添字の対応の式・全部試す（rotation-transform, brute-force）', anchor: rotation}
  - {title: ドミノの配置・隣り合わないマスの選び方 → 二部マッチング・プロファイル DP, anchor: tiling}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：H×W のマス目が出てくる問題で、問われ方から使う手法を引ける。マスを頂点とする最短路、右・下に進む DP、長方形の累積和、行と列の独立、市松模様の偶奇、45 度回転、盤面の回転へつなぐ。
    - **いつ使うか**：
        - H×W のマス目で、スタートからゴールへの最小の移動回数
        - 右か下にだけ進む経路の数・経路上の値の最大
        - 長方形の範囲の和・黒マスの個数を多数答える
        - 1×2 のタイル（ドミノ）を敷き詰める・置く
        - 盤面を 90 度回転・反転させて一致させる
        - 斜めに動く駒・マンハッタン距離・ひし形の範囲
    - **使い方**：（執筆時に書く）
