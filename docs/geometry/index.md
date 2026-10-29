---
title: 幾何
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 幾何

ベクトルと外積、誤差、凸包、偏角ソート、45 度回転など。8 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[数の扱い](../guide/method-comparison.md#numbers)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

- [ベクトルと外積](geometry-vectors.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：外積 a.x·b.y − a.y·b.x の符号で向き（左・右・一直線上）が、絶対値で平行四辺形の面積が分かる。
- [誤差の扱いと整数での処理](geometry-precision.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：幾何の計算をできるだけ整数で行い、誤差による判定の誤りを防ぐ。
- [偏角ソート](argument-sort.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：点を原点から見た角度の順に並べる。
- [回転・平行移動・アフィン変換](rotation-transform.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：点の回転・反転・平行移動を式で計算し、操作列を何回か行った後の位置を求める。
- [マンハッタン距離と 45 度回転](manhattan-chebyshev.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：u = x+y、v = x−y と座標を変える（45 度回転）と、マンハッタン距離はチェビシェフ距離 max(|Δu|, |Δv|) になる。
- [円と幾何の最適化](circle-geometry.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：2 円の位置関係は、中心間の距離と半径の和・差を 2 乗して整数のまま判定できる。
- [凸包と凸多角形](convex-hull.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：点を x 座標でソートし、スタックの末尾が凹む間は取り除くことで、全点を囲む最小の凸多角形（凸包）を O(N log N) で作る。
- [発展の幾何](advanced-geometry.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：動的な凸包・回転キャリパー（最遠点対）・最近点対・半平面交差・ミンコフスキー和で、点集合と凸図形の最大・最小・共通部分を O(N log N) 前後で求める。
