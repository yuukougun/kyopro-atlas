# advanced-geometry の報告（b4）

- 書いたファイル：docs/geometry/advanced-geometry.md、snippets/advanced-geometry/calipers.{cpp,yaml}、snippets/advanced-geometry/minkowski.{cpp,yaml}、docs/img/advanced-geometry/minkowski.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない（7 節すべてに見出しと anchor を付けた）。定型の節として resources・examples・practice・references を置いた
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 件とも期待どおり、textlint エラー 0（警告 14 は数式を含む文の長さ・読点の数、数式の中の括弧、折りたたみの中の文の助詞の誤検出）
- 図：minkowski.svg（幅 400）を render_svg.py で 360・720 幅の PNG にして目で確かめた
- 使った出典：kmjp の ABC478 G・ABC244 Ex の記事、ikatakos の ABC244 の記録（Ex の節だけ）、cp-algorithms の 5 記事（ミンコフスキー和・最近点対・半平面交差・ドロネー・交わる線分）、OI Wiki「旋转卡壳」、en.wikipedia「Bentley–Ottmann algorithm」、Library Checker の問題リポジトリ（geo/closest_pair・furthest_pair の制約）。新しいドメインはない（すべて付録 B にある）

## 台帳への提案

- abc478_g：evidence が kmjp の 1 件だけ。第三者の解説を検索したが見つからなかった（§15-6 の目標の 2 件に届かない）。見つかれば足してほしい
- abc478_g：approach の「（research/00 §5.2 の分類による。節 minkowski-sum）」は kmjp の記事で確かめたので、「番号で分割統治し、左の点の凸包と右の点の凸包のミンコフスキー和で、またぐ組の内分点の凸包を作る（節 minkowski-sum）」に改めてよい
- abc244_h：approach に「時刻のセグメント木に凸包を持たせる別解（kmjp）」を足してよい（ikatakos は点の追加で凸包を保つ方法、kmjp はセグメント木の方法）

## 用語集への提案

- 対蹠点｜antipodal-pair｜凸多角形を平行な 2 本の直線で挟んだとき、それぞれの直線に触れる 2 つの頂点の組。最遠点対は対蹠点の組の中にある
- ミンコフスキー和｜minkowski-sum｜2 つの点の集合 A・B から 1 つずつ選んだ点の和の集合 {a + b}。凸多角形どうしの和は、辺を偏角の順に合わせた凸多角形になる（ページがあるので用語集に入れず、ページの節へリンクするだけでもよい）

## 手引きへの提案

- geometry の注意に足す案：凸多角形の辺のベクトルを外積の符号で比べてマージするとき（ミンコフスキー和）は、どちらの列も最も下（同じ高さなら最も左）の頂点から始める。そうすると比べる 2 本の向きの差が 180 度未満に収まる（§5 geometry の偏角の比較の注意の具体例）
- 回転キャリパーは一直線上の点を除いた凸包で行う（辺上の点を残すと外積の等しい頂点が続き、ポインタの進め方が崩れる）。convex-hull#degenerate の不等号の向きと関係する

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc460_f（F. Farthest Pair Query、diff 1987、ap.py で実在を確認）：題名から最遠点対のクエリと思われるが、第三者の解説を見つけられず、問いも手法も確かめていない（ユークリッド距離か、マンハッタン距離で 45 度回転を使うのかも不明）。裏付けが見つかれば、ここか manhattan-chebyshev の練習の候補
- math_and_algorithm_af（アルゴ数学 034. Nearest Points、diff なし）：題名から最近点対と思われるが未確認。制約が小さく全組で解けるなら、このページには合わない
- ABC で最近点対・回転キャリパー・半平面交差を直接使う問題は ap.py の題名検索（Closest・Farthest・Nearest・Hull・Polygon）では見つからなかった

## 未解決の点

- 例題 ABC478 G の計算量 $O(N \log^2 N)$ は、kmjp の記事に書かれておらず、各段のミンコフスキー和の頂点の合計が $O(N)$ であることから自分で見積もった値である（本文は「程度」と書いた）
- 本文の解法の詳細では、各段の和の頂点を集めて最後に 1 回だけ凸包を作る形にした（kmjp は各段で左・右・和の 3 つの凸包を合わせる形）。どちらも同じ答えになる
- 半平面交差を整数で判定するときの「係数の 3 次の積」は、座標 $10^9$ で `__int128` に収まるかを本文で断定していない（「`__int128` を使うか浮動小数点で」とした）
- 動的な凸包の「`std::set` の各頂点に次の辺の傾きを持たせて lower_bound」は一般に知られた作り方（直線の側の LineContainer と同じ）として書いたが、出典の記事（ikatakos）は x をキーにした添字付きの集合で二分探索している
- 練習の Library Checker に Line Add Get Min（cht の検証問題）を双対として載せた。重複が気になるなら外してよい

## 検証の指摘への対応（2026-10-22）

- 直すべき 1・2、直すとよい 3〜9 はすべて本文で直した。未解決 1 に合わせて解法の詳細の「程度」も外した
- 直すとよい 10（別名「円の反転」が本文にない）：aliases は執筆者が変えられないため、本文は変えず下の提案にした。別名の行も aliases と一致させる必要があるので残している

### 共有ファイルへの提案（検証の指摘から）

- front matter の aliases と別名の行から「円の反転」を外す（本文に扱いがない）。扱うなら circle-geometry など円を扱うページの aliases へ移す
- docs/ds/sweep-line-2d.md に「軸に平行な線分の交点を数える」節を足す（水平な線分の両端を +1・-1 のイベントにし、垂直な線分の y の区間の和を BIT で取る）。足したら本文 #segment-intersections のリンクをその節へ張り替える
- 台帳：abc478_g・abc244_h に `checked: 2026-10-22` を入れてよい（検証役が第三者の記事で方針を確かめた）
