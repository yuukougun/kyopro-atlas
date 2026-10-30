---
title: 幾何の詳細索引
type: generated
search:
  exclude: true
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 幾何の詳細索引

分野の全ページの id・URL・別名・サイン・種類・前提・使い分け・節。全分野の1行の一覧と索引の版は https://yuukougun.github.io/kyopro-atlas/llms.txt にある。

## ベクトルと外積（geometry-vectors） {#geometry-vectors}

- id：`geometry-vectors`　レベル：基礎　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/
- 別名：外積、内積、cross product、ccw、向き判定、符号付き面積、多角形の面積、靴紐公式、shoelace formula、線分の交差判定、点と直線の距離、3 次元の基本、直方体の共通部分
- 種類：幾何
- サイン：
    - 言い回し：3 点が一直線上にあるか・三角形ができるか
    - 言い回し：左に曲がるか右に曲がるか・四角形が凸か
    - 言い回し：頂点が順に与えられた多角形の面積
    - 言い回し：2 本の線分が交わるか・多角形を線分で切って分かれる個数
    - 言い回し：直方体どうしの共通部分の体積
    - 制約：座標が整数で |x|, |y| ≤ 10^9（外積は long long にぎりぎり収まる）
    - 式の形：(x2 − x1)(y3 − y1) − (y2 − y1)(x3 − x1) の符号で場合を分ける
- 節：
    - `geometry-vectors#cross-and-dot` 外積と内積の意味（符号と大きさ）：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#cross-and-dot
    - `geometry-vectors#ccw` ccw：3 点の回り方・一直線上の判定・凸性の判定：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#ccw
    - `geometry-vectors#overflow` オーバーフローの見積もり（座標 10^9 で外積は 8×10^18、さらに足すなら \_\_int128）：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#overflow
    - `geometry-vectors#polygon-area` 三角形・多角形の面積：座標の公式（面積の 2 倍を整数のまま扱う）（水）：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#polygon-area
    - `geometry-vectors#segment-intersection` 線分の交差判定（端点で接する・同一直線上の場合）と点と直線の距離（水）：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#segment-intersection
    - `geometry-vectors#3d-geometry` 3 次元の基本：軸に平行な直方体の共通部分は軸ごとの区間の積：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#3d-geometry
    - `geometry-vectors#point-representation` 点の表し方：整数の構造体と std::complex：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-vectors/#point-representation

## 誤差の扱いと整数での処理（geometry-precision） {#geometry-precision}

- id：`geometry-precision`　レベル：水　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/
- 別名：浮動小数点の誤差、floating-point error、EPS、整数化、桁落ち、直線の正規化、方向ベクトルの約分、ax+by+c=0
- 種類：幾何、整数論
- 前提：`geometry-vectors`、`gcd-lcm`
- 使い分け：`method-comparison#numbers`
- サイン：
    - 言い回し：座標や値が小数第 k 位まで与えられる
    - 言い回し：ちょうど境界上か・整数になるかを判定する
    - 言い回し：K 点以上を通る直線の数・平行な辺の組（台形）の数
    - 言い回し：絶対誤差または相対誤差 10&#94;-6〜10&#94;-9 まで許される
    - 制約：座標が 10^9 規模の整数で、傾きや角度を比べる
- 節：
    - `geometry-precision#double-precision` double の精度の目安（仮数 53 ビット・値 10^9 で絶対誤差 10^-7 程度）と桁落ち：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#double-precision
    - `geometry-precision#scale-to-integer` 小数の入力を 10^k 倍して整数にする（文字列で読んで整数にする）：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#scale-to-integer
    - `geometry-precision#integer-comparison` 比較は外積・内積・距離の 2 乗で（sqrt・atan2・除算を避ける）：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#integer-comparison
    - `geometry-precision#line-normalization` 方向・直線の正規化：gcd で約分し、(1, −1) と (−1, 1) を同じにする符号の決め方：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#line-normalization
    - `geometry-precision#double-coordinates` 中点を整数にするために座標を 2 倍する：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#double-coordinates
    - `geometry-precision#eps` 実数が避けられないとき：long double と、値の大きさに合わせた EPS：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#eps
    - `geometry-precision#output-and-binary-search` 出力の桁数と、実数の二分探索の打ち切り：https://yuukougun.github.io/kyopro-atlas/geometry/geometry-precision/#output-and-binary-search

## 偏角ソート（argument-sort） {#argument-sort}

- id：`argument-sort`　レベル：水　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/
- 別名：偏角、角度でソート、argument sort、atan2、方向の順に並べる、回転する光線
- 種類：幾何、ソート・座標圧縮
- 前提：`geometry-vectors`、`sorting-techniques`
- サイン：
    - 言い回し：原点から見た方向の順に並べる
    - 言い回し：回転する光線（レーザー）に当たる点の数
    - 言い回し：∠ABC の最大
    - 言い回し：ベクトルをいくつか選んで和の長さを最大にする
    - 制約：座標が 10^9 規模の整数で、角度の大小や一致を正確に比べる
- 節：
    - `argument-sort#half-plane-compare` 半平面に分けて外積で比べる（全周を外積だけで比べると推移律が壊れる理由）：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#half-plane-compare
    - `argument-sort#atan2` atan2 の手軽さと限界：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#atan2
    - `argument-sort#edge-cases` 原点・同じ方向の点・半平面の境界（x 軸の正と負）の扱い：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#edge-cases
    - `argument-sort#range-count` 並べた後に：角度の範囲の点の数（累積和）：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#range-count
    - `argument-sort#wrap-around` 一周を扱う：配列を 2 周分にして尺取り（青）：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#wrap-around
    - `argument-sort#opposite-direction` 反対方向に最も近い点の二分探索（青）：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#opposite-direction
    - `argument-sort#angular-intervals` 角度の区間のスケジューリング・連続する範囲だけを試す最適化（青）：https://yuukougun.github.io/kyopro-atlas/geometry/argument-sort/#angular-intervals

## 回転・平行移動・アフィン変換（rotation-transform） {#rotation-transform}

- id：`rotation-transform`　レベル：水　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/
- 別名：回転行列、rotation matrix、座標の回転、affine transformation、合同変換、複素数で回転、グリッドの回転、90 度回転、転置、三角関数、ラジアン、余弦定理
- 種類：幾何、線形代数・行列
- 前提：`geometry-vectors`
- サイン：
    - 言い回し：点を θ 度回転した位置
    - 言い回し：回転・反転・平行移動の操作を順に行った後の位置のクエリ
    - 言い回し：回転と平行移動で 2 つの点集合が重なるか
    - 言い回し：盤面を 90 度回転して一致させる
    - 制約：操作が M ≤ 2×10^5 回、各クエリは途中の時点での点の位置
- 節：
    - `rotation-transform#rotation-formula` 回転の式と、中心まわりの回転（中心を原点に移す・回す・戻す）：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#rotation-formula
    - `rotation-transform#rotate-90` 90 度回転・反転を整数のまま書く：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#rotate-90
    - `rotation-transform#affine` アフィン変換：(x, y, 1) と 3×3 行列・掛ける順序（後の操作を左から掛ける）：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#affine
    - `rotation-transform#prefix-composition` 操作列の累積とクエリ：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#prefix-composition
    - `rotation-transform#grid-rotation` グリッドの回転・転置・反転の添字（(i, j) → (j, N−1−i)）：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#grid-rotation
    - `rotation-transform#trig-angle` 三角関数と角度の基本（度とラジアン・π は acos(−1)・余弦定理）：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#trig-angle
    - `rotation-transform#congruence` 点集合の合同判定：重心をそろえて照合する（黄）：https://yuukougun.github.io/kyopro-atlas/geometry/rotation-transform/#congruence

## マンハッタン距離と 45 度回転（manhattan-chebyshev） {#manhattan-chebyshev}

- id：`manhattan-chebyshev`　レベル：水　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/
- 別名：45 度回転、マンハッタン距離、Manhattan distance、チェビシェフ距離、Chebyshev distance、L1 距離、L∞ 距離、u=x+y, v=x−y、絶対値を外す、斜めの番号
- 種類：幾何、考察
- 前提：`sorting-techniques`、`prefix-sum`
- ACL：`segtree`
- サイン：
    - 言い回し：マンハッタン距離が最大の 2 点・ある点から最も遠い点
    - 言い回し：マンハッタン距離の和の最小・全ペアの距離の総和
    - 言い回し：斜め移動（キングの移動）だけでの距離・斜めにしか動けない駒
    - 言い回し：ひし形の範囲（|x|+|y| ≤ D）にある点の数
    - 制約：N ≤ 2×10^5 点の全ペアのマンハッタン距離の和や最大を問い、全組 O(N^2) が間に合わない
    - 式の形：|x_i − x_j| + |y_i − y_j| や max(|x_i − x_j|, |y_i − y_j|) の最大・和が式に出る
- 節：
    - `manhattan-chebyshev#rotate-45` 45 度回転：|Δx|+|Δy| = max(|Δu|, |Δv|) になる理由：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#rotate-45
    - `manhattan-chebyshev#farthest-pair` 最遠点対：x+y と x−y の最大・最小（点の更新はセグ木）：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#farthest-pair
    - `manhattan-chebyshev#axis-independence` x と y を独立に扱う：距離の和は軸ごと・中央値・寄与：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#axis-independence
    - `manhattan-chebyshev#remove-abs` 絶対値の外し方：向きを固定して場合分けし、盤面を反転してもう一度：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#remove-abs
    - `manhattan-chebyshev#diagonal-coordinates` 盤面の斜め：r+c・r−c で斜めの線に番号を付ける（色の偶奇は parity）：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#diagonal-coordinates
    - `manhattan-chebyshev#parity-after-rotation` 回転後の偶奇：u と v の偶奇がそろう点だけが元の格子点（チェビシェフ → マンハッタンで 1/2 が出る）（青）：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#parity-after-rotation
    - `manhattan-chebyshev#diamond-range` ひし形の範囲を正方形にして 2 次元累積和（黄）：https://yuukougun.github.io/kyopro-atlas/geometry/manhattan-chebyshev/#diamond-range

## 円と幾何の最適化（circle-geometry） {#circle-geometry}

- id：`circle-geometry`　レベル：青　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/
- 別名：円の交差判定、2 円の位置関係、外接円、円と格子点、最小包含円、smallest enclosing circle、Welzl、半径の二分探索、三分探索で幾何、候補点の列挙
- 種類：幾何、二分探索
- 前提：`geometry-precision`、`binary-search-answer`
- ACL：`dsu`
- サイン：
    - 言い回し：円周を伝って移動できるか・円どうしが交わるか
    - 言い回し：すべての点を含む最小の円
    - 言い回し：障害物を避けて通れる円の最大の半径
    - 言い回し：円の内部にある格子点の数
    - 制約：N ≤ 50 程度の点で、実数の位置や半径を最適化する
- 節：
    - `circle-geometry#two-circles` 2 円の位置関係（離れる・外接・交わる・内接・内包）を 2 乗した整数で判定：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#two-circles
    - `circle-geometry#lattice-points-in-circle` 円と格子点：y ごとに x の範囲を整数で求める：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#lattice-points-in-circle
    - `circle-geometry#connectivity` 円のつながりを Union-Find で：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#connectivity
    - `circle-geometry#min-enclosing-circle` 最小包含円：候補は 2 点を直径とする円か 3 点の外接円（Welzl の乱択も）：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#min-enclosing-circle
    - `circle-geometry#circumcenter` 外心の計算と退化（3 点が一直線上）：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#circumcenter
    - `circle-geometry#geometry-optimization` 幾何の最適化の選び方：候補の列挙・答えの二分探索（半径・時刻）・三分探索：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#geometry-optimization
    - `circle-geometry#ternary-search-caveats` 三分探索の注意：凸性の確認・入れ子の三分探索・式の変わり目の時刻を列挙する方法（黄）：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#ternary-search-caveats
    - `circle-geometry#no-heuristics` 山登り・焼きなましに頼らない（ABC の幾何の最適化は凸性や候補の列挙で解ける）：https://yuukougun.github.io/kyopro-atlas/geometry/circle-geometry/#no-heuristics

## 凸包と凸多角形（convex-hull） {#convex-hull}

- id：`convex-hull`　レベル：黄　段階：done　type：technique
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/
- 別名：凸包、convex hull、Andrew のアルゴリズム、monotone chain、Graham scan、上側凸包、下側凸包、点の内外判定、凸多角形の内外判定、交差数判定、Pick の定理、多角形の格子点、線分上の格子点
- 種類：幾何
- 前提：`geometry-vectors`、`binary-search`、`gcd-lcm`
- サイン：
    - 言い回し：すべての点を囲む最小の凸多角形
    - 言い回し：外側にある点だけが効く
    - 言い回し：区間の平均・傾き・比の最大
    - 言い回し：多数の点が凸多角形の内部・境界・外部のどこにあるか
    - 言い回し：多角形の内部にある格子点の数
    - 式の形：(S_j − S_i)/(j − i) の最大（2 点を結ぶ傾きの最大）
- 節：
    - `convex-hull#andrew` Andrew 法（monotone chain）：下側と上側を作る：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#andrew
    - `convex-hull#degenerate` 一直線上の点・重複点・全点が一直線上のときの扱い（外積の不等号の向き）：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#degenerate
    - `convex-hull#max-slope` 比・平均の最大は上側凸包の接線（累積和の点）：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#max-slope
    - `convex-hull#cht-duality` 凸包と CHT の双対（点 (a, b) と直線 y = ax+b）：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#cht-duality
    - `convex-hull#point-in-convex-polygon` 凸多角形の内外判定：扇形に分けて二分探索（O(log N)）：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#point-in-convex-polygon
    - `convex-hull#point-in-polygon` 一般の多角形の内外判定（交差数の偶奇）：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#point-in-polygon
    - `convex-hull#lattice-points` 格子点：線分上は gcd(|dx|, |dy|)+1、多角形は Pick の定理：https://yuukougun.github.io/kyopro-atlas/geometry/convex-hull/#lattice-points

## 発展の幾何（advanced-geometry） {#advanced-geometry}

- id：`advanced-geometry`　レベル：発展　段階：done　type：overview
- URL：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/
- 別名：回転キャリパー、rotating calipers、最遠点対、最近点対、closest pair、半平面交差、動的凸包、ミンコフスキー和、Minkowski sum、ボロノイ図、ドロネー三角形分割、円の反転
- 種類：幾何
- 前提：`convex-hull`
- サイン：
    - 言い回し：最も遠い 2 点（凸包上の対蹠点）
    - 言い回し：最も近い 2 点（N ≤ 2×10^5）
    - 言い回し：点の追加と ax+by の最大のクエリ
    - 言い回し：2 つの凸な点集合の和の凸包
    - 言い回し：半平面の共通部分
- 節：
    - `advanced-geometry#dynamic-hull` 動的な凸包（点の追加と ax+by の最大）：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#dynamic-hull
    - `advanced-geometry#rotating-calipers` 回転キャリパー（凸包上の最遠点対）：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#rotating-calipers
    - `advanced-geometry#closest-pair` 最近点対（分割統治・平面走査で O(N log N)）：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#closest-pair
    - `advanced-geometry#half-plane-intersection` 半平面交差：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#half-plane-intersection
    - `advanced-geometry#minkowski-sum` ミンコフスキー和（凸包の和）：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#minkowski-sum
    - `advanced-geometry#voronoi` ボロノイ図・ドロネー三角形分割：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#voronoi
    - `advanced-geometry#segment-intersections` 線分の交点の列挙（Bentley-Ottmann）：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#segment-intersections
    - `advanced-geometry#library` 自作するときの要点と Library Checker：https://yuukougun.github.io/kyopro-atlas/geometry/advanced-geometry/#library
