# convex-hull の報告（b3 執筆）

- 書いたファイル：docs/geometry/convex-hull.md、snippets/convex-hull/{hull,max-slope,inside}.{cpp,yaml}、docs/img/convex-hull/{andrew,max-slope,fan}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections の lattice-points の title を短くした（「格子点：線分上は gcd(|dx|, |dy|)+1、多角形は Pick の定理」。§14-12 の 60 字の目安。anchor は変えていない）
- 構成：technique（黄）。要点 → 7 つの中身の節（各節の末尾に応用の型）→ 落とし穴 → 例題 3 → 練習 2（方針は折りたたみ）→ 力試し 1 → 確認問題（節の中に 1、quiz に 4）→ 使い分け → 参考。acl: [] なので ACL の囲みはない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 21（数式を含む文の長さ・読点の数、半開区間の角括弧、図の代替テキストの長さ。§13-8・§14-25 の誤検出として残した）
- コード片の確かめ方：hull.cpp は 0〜5 の格子の乱択 3000 件で、素朴な凸包・辺の上の点の列挙・格子点の全数え上げと一致を確かめた（一直線上の点を残す版で、右端の縦の辺の点を 2 回拾う誤りをこの試験で見つけて直した）。max-slope.cpp は乱択 2000 件で全区間の平均の最大（分数）と一致。inside.cpp は乱択 1500 件で、境界の判定と角度の総和による内外と一致
- 図：andrew.svg（catalog の visual は priority 2・dynamic のステップ送り。動く図は作らず、途中の 1 ステップと完成形の静的な図で代えた。必要なら後で動く図にする）、max-slope.svg・fan.svg（研究ノートの「図」にある接線と扇形の図）。render_svg.py で 360px・560px・720px の PNG にして目で確かめた
- 使った出典：E869120 の GitHub（typical90 041 の problem-txt と sol/041-03.cpp。問いと制約、答え i + b − N）、kmjp（abc341_g・abc296_g・abc251_g・abc202_f）、merom686（abc296_g）、drken（agc021_b）、en.wikipedia（Convex hull algorithms・Point in polygon）、ja.wikipedia（ピックの定理）。新しいドメインはない（kmjp.hatenablog.jp は付録 B にあり、check_noai.py でも指定なしを確かめた）
- ikatakos.com は作業中ずっと 503 で読めなかった。台帳の evidence が ikatakos の abc341_g・abc251_g・abc202_f は、kmjp の記事で問いと方針を確かめた

## 台帳への提案

- typical90_ao｜summary｜格子点にある N 本の杭をすべて囲む周の最も短い塀を作り、塀の上と内側にある格子点のうち、まだ杭のない点の数を求める。｜https://github.com/E869120/kyopro_educational_90/blob/main/problem-txt/041.txt（問題文の txt と sol/041-03.cpp で確かめた）
- typical90_ao｜checked｜2026-10-21｜同上
- abc341_g｜evidence に追加｜https://kmjp.hatenablog.jp/entry/2024/02/17/0900（ikatakos が 503 のため。累積和の点と、右から凸包の隣をたどる方針を確かめた）｜checked 2026-10-21
- abc296_g｜evidence に追加｜https://kmjp.hatenablog.jp/entry/2023/04/01/0900（内部・外部・境界を答える問いと、上下の鎖で二分探索する別解）｜checked 2026-10-21
- abc251_g｜evidence に追加｜https://kmjp.hatenablog.jp/entry/2022/05/14/0900（辺ごとに最も厳しい平行移動を前計算し、1 点を N 本の辺で判定する O(N(M+Q))）｜checked 2026-10-21
- abc202_f｜evidence に追加｜https://kmjp.hatenablog.jp/entry/2021/05/24/0900（凸包の面積が整数になる部分集合を数える。三角形の内部の点の 2 の冪を掛ける DP）｜checked 2026-10-21
- agc021_b｜checked｜2026-10-21｜drken の記事で、凸包の頂点だけが正の確率を持ち、外角 / 2π になることを確かめた

## 用語集への提案

- 凸包｜convex-hull｜平面上の点をすべて含む最小の凸多角形。頂点になるのは外側の点だけである。（本文では用語集へリンクしていない。ページそのものがあるので、索引用に要るときだけ）
- 上側凸包・下側凸包｜upper-hull｜凸包の周を x 座標が最小の点から最大の点まで、上を通る部分と下を通る部分に分けたもの。（本文の #andrew で定義した。cht のページが同じ語を使うなら用語集に置くとよい）

## 手引きへの提案

- §5 geometry に「凸多角形は頂点を反時計回り・一直線に並ぶ 3 頂点なしで持つ（`<= 0` の凸包で作り直す）と約束すると、内外判定・面積・Pick の定理の書き方がそろう」を 1 行足すとよい
- render_svg.py：viewBox だけで width のない SVG は、Chrome が img を max-width いっぱいに広げるのに、ウインドウの高さは固有の幅で計算するため、720px の PNG で下が切れる（今回の 3 枚とも）。360px の PNG は全体が写る。width・height を SVG に付けるか、道具の高さの計算を直すとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- math_and_algorithm_bu（アルゴ数学 098. Polygon and Point、diff なし、ap.py で実在を確認。台帳になし）：題名から一般の多角形の内外判定（交差数）の練習の候補。第三者の解説を見つけられず、問いは未確認（E869120/math-algorithm-book の editorial の md には 098 の節が見つからなかった）。確かめられれば point-in-polygon の節の練習に推す
- abc211_f（Rectilinear Polygons、diff 2350、ap.py で確認）：軸に平行な多角形と多数の点の内外（含む多角形の数）を数える問題と思われるが、解説は未確認。交差数の偶奇を平面走査で数える型なので、この節の力試しの候補
- abc319 以降で凸包が鍵の ABC は abc478_g（advanced-geometry の例題）だけで、ap.py の題名検索（Convex・Hull・Polygon）でもほかに見つからなかった

## 未解決の点

- abc341_g・abc296_g の制約（N・Q・A_i・座標の範囲）は、読めた第三者の記事に書かれておらず確かめられなかった。本文の例題には制約の数値を書いていない（max-slope の節の「$\lvert a_i \rvert \le 10^6$、$N \le 2 \times 10^5$ なら」は仮定の例として書いた）。abc296_g の頂点の向き（反時計回りで与えられるか）も未確認なので、本文は「反時計回りに並べ」とだけ書いた
- catalog の visual（priority 2・dynamic）は静的な図で代えた。動く図にするなら、config は点の列（例 `{"points": [[0,2],[1,0],[2,2],[3,1],[4,4],[5,0],[6,2],[7,3]]}`）で、下側→上側のスタックの積み・除きを 1 ステップずつ caption 付きで出す仕様を想定する
- cht は stub なので、双対の節からはページへのリンクだけにした。cht が draft になったら、双対の節へのリンク（cht から convex-hull#cht-duality）と、cht 側の該当節へのリンクを張り合わせるとよい
- argument-sort の参考の行（Graham scan への言及）と、gcd-properties の「多角形の格子点」・floor-sum の表の行・geometry-precision の abc296_g の方針は、convex-hull へのページのリンクのまま。`#lattice-points`・`#point-in-convex-polygon`・`#andrew` へ張り替えられる

## 検証の指摘への対応（b3）

- 指摘 1〜6：本文と andrew.svg を直した（図の (a) の除く辺は灰色の点線にし、凡例は「(b) 下側・(b) 上側」とした）
- 指摘 7：3 枚の SVG に viewBox と同じ width・height を足した。サイト全体のそろえ方はメインの判断に任せる
- 指摘 8：台帳の summary の直しなので、提案として下に書く（本文の要約は fix_problems で反映される）

### 台帳への提案（指摘 8）

- abc251_g｜summary｜M 通りに平行移動した凸多角形のすべての内部または境界の上にあるかを、多数の点について判定する。
- abc202_f｜summary｜3 点以上の点の部分集合のうち、それらを囲む最小の凸多角形の面積の 2 倍が偶数になるものの数を求める。
