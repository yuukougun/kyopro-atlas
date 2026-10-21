# argument-sort の報告（工程8b・バッチ b1）

- 書いたファイル：docs/geometry/argument-sort.md、snippets/argument-sort/{sort-points,range-sum,half-window,atan2-limit}.{cpp,yaml}、docs/img/argument-sort/half-planes.svg
- front matter で変えたもの：complexity（`並べ替え O(N log N)（比較 1 回 O(1)、整数だけで誤差なし）。並べた後、角度の範囲の点の数・重みの和は前計算 O(N)、クエリごとに O(log N)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 片・期待と違う 0）、textlint（エラー 0・警告 26。数式を含む文の長さ、数式の中の `[0, 2\pi)`・`(-\pi, \pi]` を括弧の対応の誤りと見るもの、数式の中の読点で、いずれも誤検出）
- コード片 sort-points・range-sum・half-window は、Python の素朴な実装とランダムな 500 ケース（座標 ±5 以下、同じ方向・原点・x 軸上を含む）で突き合わせた（一時置き場で実施）
- 図：静的な SVG（前半・後半の半平面と境界の所属、点の偏角の順位）。描画の道具が手元になく、見た目は目で確かめていない。検証役に描画の確認を頼みたい
- 動く図：catalog の visual は priority 2 なので作らず、置き場の div も置いていない（静的な SVG で代えた）。作るなら仕様は「原点のまわりで半直線を正の x 軸から反時計回りに回し、通過した点に順位を付ける。前半と後半を色と線種で分け、同じ方向の点は同時に順位が付く」

## 使った出典

- drken「Yosupo Library Checker - Sort Points by Argument」：半平面の比較・原点・atan2 の懸念（Library Checker の順序は (−π, π]、原点は偏角 0）
- ikatakos ABC442 のメモ（解説の部分）：例題 ABC442 E の方針。atan2 を使わない理由、時計回りの並び、2 周分の累積和
- E869120 sol/009.cpp：典型90 009 の方針（反対方向の lower_bound と候補 2 つ、O(N^2 log N)）
- merom686「ABC225」：ABC225 E の方針（外積で比べる、右端の順の貪欲）
- ikatakos ABC139 のメモ（解説の部分）：ABC139 F の方針（半平面に入るベクトルが連続、2 周分）
- drken ABC207 D：重心を N 倍で整数に、偏角の順に並べて（長さの 2 乗・内積・外積）の列の巡回シフトで照合
- kmjp「AtCoder ABC #479 (オムロンプログラミングコンテスト2026) : G - Tuning」：ABC479 G の問いと方針。ikatakos ABC479 のメモ（解説の部分）で方針を確かめた
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

- abc479_g｜summary｜整数の組 (A_i, B_i) に有理数 (C_i, D_i) を足して、どの i でも比 (A_i + C_i) : (B_i + D_i) が等しくなるようにするとき、|C_i| + |D_i| の総和の最小値を求める。｜https://kmjp.hatenablog.jp/entry/2026/10/14/0900
- abc479_g｜approach｜「点 (A_i, B_i) を原点を通る直線に乗せる問題に言い換え、片方の成分だけを動かすとして傾きの順に並べ、重み付き中央値を累積和で探す」｜同上と https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/1011_abc479
- abc479_g｜evidence｜kmjp の URL を足す（ikatakos のページは問題文を引用した節があるため、問いの確認は kmjp で行った）
- abc442_e・typical90_i・abc225_e・abc139_f・abc207_d・abc479_g｜checked｜2026-10-21｜各 evidence で問いと方針を確かめた
- abc442_e｜evidence｜usaco.guide の 6 件のうち /plat/geo-pri 以外（hashing・hashmaps・bitsets・interactive・random）はこの問題と無関係に見える。research の資料一覧から機械的に写ったものと思われるので外すとよい
- abc139_f｜evidence｜Nyaan・ei1333 のライブラリのトップは問題の裏付けにならない（maspy の max_norm_sum が例に挙げているという research の記述は残してよい）。ikatakos だけでよい
- abc207_d｜approach｜「重心を原点に移し（座標を N 倍して整数に）、偏角の順に並べた点の列を（長さの 2 乗・内積・外積）で符号化して巡回シフトで照合する」に具体化してもよい｜https://drken1215.hatenablog.com/entry/2023/07/25/143000

## 用語集への提案

- 偏角｜argument｜原点から点（ベクトル）への向きを、正の x 軸から反時計回りに測った角度。範囲を [0, 2π) とするか (−π, π]（atan2 と同じ）とするかを決めて使う。原点には偏角がない
- 狭義の弱順序（strict-weak-ordering）は cpp-comparators の節へリンクした。用語集に足すなら同じ節へ転送するとよい

## 手引きへの提案

- §5 geometry に「偏角や角度の比較は、180 度未満の範囲に分けてから外積で比べる（外積の符号は 180 度未満でしか大小を表さない）」を 1 行足すと、convex-hull・circle-geometry など偏角を使うページで書き方がそろう
- geometry の各ページで使う比較関数の名前（`cross`・`half`・`arg_less`）と、偏角の範囲の既定（[0, 2π)、正の x 軸から反時計回り）をそろえる約束があるとよい。このページは [0, 2π) を既定にし、(−π, π] への変え方を表で示した

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

catalog の数（例題 2・練習 2・力試し 2）で足りている。水のページなので abc319 以降の水の問題が例題か練習にあると良いが、abc442_e（1355）が例題にある。次は節に合う候補（第三者の解説での裏付けは research 08 のもの）。

- abc296_g（G. Polygon and Points、2241。ap.py で実在と difficulty を確かめた）：凸多角形に対する多数の点の内外判定。内部の点から見た頂点の偏角で辺を二分探索する。research 08 §5 に例題として載る（point-in-polygon との境界）｜https://merom686.hatenablog.com/entry/2023/04/01/235440
- Library Checker の sort_points_by_argument は verify に入っている。本文では Library Checker の順序の違い（(−π, π]・原点は 0）に触れた

## 未解決の点

- 典型90 009 の制約（N の上限）を第三者の資料で確かめられなかった（E869120 の解答コードに制約のコメントがない）。本文では「$O(N^2 \log N)$」とだけ書き、N の上限は書いていない
- ABC225 E の図形の正確な形（端点の座標）と、端だけ接する場合を重なりとみなすかは、merom686 の記事に書かれていなかった。本文では「両端の点の方向で決まる区間」「端の扱いは問題の定義に合わせる」とだけ書いた
- ABC442 E のクエリの両端（A_j・B_j）がモンスターの番号か方向そのものかは、ikatakos の解法の記述（正規化して位置を求める）から方向として扱えることだけを確かめた。本文は「方向 A から時計回りに方向 B まで」と書いた
- ABC479 G の「片方の成分だけを動かせばよい」は kmjp 氏の記事で「筆者の考え」として書かれている主張で、証明は確かめていない。力試しの方針には言い換えの筋だけを書いた
- 「座標が 10^4 程度までなら atan2 で順序は崩れにくい」は、偏角の差の下限 1/(2C^2) と double の間隔からの見積もりで、atan2 の実装の誤差（数 ulp）を含めても十分な余裕がある、という判断である。厳密な保証ではないので、本文でも「崩れにくい」とした
- geometry-vectors・geometry-precision・convex-hull・rotation-transform は stub なので、ページへのリンクだけにした（節へのリンクはしていない）

## 検証の指摘への対応（verify/argument-sort.md）

- 指摘 1〜8 はすべて直した（図の注記の位置、ABC207 D の同じ方向の順、ABC139 F の長さ 0 の扱いを議論の前へ、atan2 の見積もりを下限と余裕の大きさの書き方へ（目安を 10^6 に）、Library Checker の順と原点の位置、ABC479 G の片方の成分だけを動かす理由と A_i = 0 の点、maspy の URL、θ の定義）。採らなかったものはない
- 台帳への提案（再掲）：abc479_g の summary を本文の要約に、6 問の checked を 2026-10-21 に（検証役も同意）
