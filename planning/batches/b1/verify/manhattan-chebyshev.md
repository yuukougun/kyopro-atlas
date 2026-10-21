# manhattan-chebyshev の検証（工程8b・b1）

- 対象：docs/geometry/manhattan-chebyshev.md、snippets/manhattan-chebyshev/{farthest-pair,chebyshev-sum,diamond-count,segtree-farthest}.{cpp,yaml}、docs/img/manhattan-chebyshev/{rotate,diagonal}.svg（動く図はない）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査
    - `python3 tools/check_pages.py --page manhattan-chebyshev -v`：エラー 0・警告 0
    - `python3 tools/fix_problems.py --page manhattan-chebyshev --check`：直すべき行 0
    - `python3 tools/check_snippets.py snippets/manhattan-chebyshev`：4 片・コンパイル 4 回・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
    - `npx textlint`：0 errors・29 warnings（執筆者の報告どおり。文の長さと数式の中の括弧・読点）
- front matter：骨格（75cd131）との差分は complexity・stage だけ。sections・id・題名・別名は変わっていない。別名の行は aliases とすべて一致
- コード片
    - 4 片とも `-fsanitize=address,undefined -Wall -Wextra` 付きで cases を動かし、出力一致・報告なし
    - 乱数の入力で 300 回ずつ動かし、各片の main の中の素朴な計算との assert がすべて通った（diamond-count は H, W ≤ 7・D ≤ 15、segtree-farthest は座標 ±10^9 で更新と問い合わせを混ぜた 20 回、chebyshev-sum・farthest-pair は座標 ±10^6 で N ≤ 50）
    - 取り込みの範囲（core）は要点の数行で、本文の記号（u, v, s, w, 半開区間）とそろう。書き方は §9 どおり（bits・using namespace std・マクロなし・'\n'）
    - segtree の使い方（`segtree<S, op, e> seg(n)`、`set`、`prod(l, r)` は半開で `l == r` なら `e()`、計算量 O(log n)）を ~/lib/ac-library-master/document_ja/segtree.md と照らして一致
- 自分で導いた主張を小さなプログラムで確かめた（作業用の場所 v-manhattan-chebyshev/t.cpp、サニタイザ付き）
    - $\lvert a \rvert + \lvert b \rvert = \max(\lvert a + b \rvert, \lvert a - b \rvert)$ と $2\max(\lvert a \rvert, \lvert b \rvert) = \lvert a + b \rvert + \lvert a - b \rvert$：$\lvert a \rvert, \lvert b \rvert \le 20$ の乱数 10 万組で成立
    - 斜め 4 方向の駒の BFS：$x + y$ の偶奇が違えば届かず、同じなら手数 $= \max(\lvert \Delta x \rvert, \lvert \Delta y \rvert)$（確認問題 2・#parity-after-rotation と一致）
    - 斜めの線の長さの式（$\max(0, s - (W-1)) \le r \le \min(H-1, s)$）：$H, W \le 6$ の全部で一致
    - 時刻と位置：$\lvert p_2 - p_1 \rvert \le t_2 - t_1$ ⇔ $(t - p, t + p)$ の両成分が減らない：乱数 10 万組で一致
    - `INT_MAX` = 2147483647（指摘 1）。ビショップの到達：1 × W・H × 1 の盤面で同じ色に届かないマスがある（指摘 4）
    - 確認問題 1（(1,0) と (3,3) の距離 5）、図の 13 個（ひし形 1+4+8、正方形の偶奇がそろう点 9+4）：手計算で正しい
- 出典（参考の URL 12 件）：ACL の segtree は手元のドキュメントで確かめ、残り 11 件を開いた。題名と著者は書かれたとおり、ドメインはすべて付録 B にある。本文の方針はどれも出典と食い違わない
    - drken ABC178 E（$x+y$・$x-y$ の幅）、drken ABC265 F（$(j, k)$ の DP、斜めの累積和、$O(ND^2)$、N ≤ 100・D ≤ 1000）、drken ABC330 F（一辺の二分探索、軸ごとに独立）
    - merom686 ABC366（x と y の独立、候補は約 4×10^6）、testcampus（zenn）ABC366（候補をすべて計算してソートと upper_bound、候補は −2×10^6〜2×10^6）、merom686 ABC351（偶奇で分け、半分の和と差をソートして累積和）
    - ikatakos ABC184 C（3 手以下。2 手の条件は同色・距離 6 以下・$\lvert \Delta r \pm \Delta c \rvert \le 3$）、ABC210 D（右下と左下に固定、累積の最小、自分自身を避ける、左右反転）、ABC377 F（4 種類の線、重複をまとめて交点で戻す。コードは偶奇が違う斜めの組を飛ばす）、ABC437 F（`2 L R x y` で 1-indexed の閉区間、4 つの最大・最小をセグ木）、ABC476 F（行の差の項と四隅からの DP、O(N^2)。45 度回転は使わない）
    - 本文の文・例は出典と並びも数値も違い、近すぎる箇所はない
- 問題：11 問とも `python3 tools/ap.py show` で題名・diff が本文と一致（abc330_f の題名の 2 つの空白も ap.py の値どおり）。役割は台帳と一致
- 図：Windows の Chrome（headless=new、2 倍密度）で、等倍（rotate 628×354）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（v-manhattan-chebyshev/wrotate.png・wnarrow.png）。日本語の文字のはみ出し・重なりはない。背景は白で塗られ、ダークでも読める。値はどちらも本文・代替テキストと一致（rotate：左右とも 13 個、× は偶奇の違う点。diagonal：W = 5 で r − c + 4、r + c = 4 と r − c + 4 = 3 の斜め）
- リンク先：アンカー（median-absolute#separate-axes、dp-grid#flip-direction、parity#checkerboard、lis#dilworth、prefix-sum-2d#formula、dp-prefix-sum#directional）はすべてある。convex-hull・spanning-tree-advanced は stub（§13.4 によりよい）
- 執筆者の未解決の点
    - (1) ABC366 E の制約：第三者の解説 2 件とも N・D の上限を書いていない。testcampus は候補を −2×10^6〜2×10^6 とする。本文が数を書かず「候補の数を R とする」にとどめたのは妥当（指摘 7 で R の大きさを添える案）
    - (2) ABC437 F の区間：ikatakos のメモで「`2 L R x y`、1 ≤ L ≤ R ≤ N の閉区間（コードでは `prod(l - 1, r)`）」と確かめた。本文の方針は区間の与え方に触れておらず、誤りはない。台帳の summary に区間を足す執筆者の提案は正しい
    - (3) ikatakos の ABC457 のページ：題名は「Polaris.AI プログラミングコンテスト 2026（AtCoder Beginner Contest 457）E,F問題メモ」で、本文の参考の題名と一致。中身には G（Catch All Apples）の節もあり、$(T - X, T + X)$ への変換、x でソート（同じ x は y の昇順）、y の列の最長の狭義減少部分列を Dilworth で、と書かれている。題名と中身のずれは元のページのもので、本文の書き方（題名をそのまま、内容は G の解説）でよい
    - (4) ABC476 F：ikatakos のメモは「行の差の項（行ごとの前後の累積和と 2 階の累積和）と、残りの成分を四隅からの DP」で O(N^2)。本文の方針（縦の差・横の差の成分に分け、行ごとの前計算と四隅からの累積和）と同じ粒度で一致する
    - (5) related の reformulation へのリンクなし：related は front matter の一覧で、本文のリンクは必須でないのでよい
- メインへの申し送り（台帳）：abc476_f・abc457_g の summary が台帳では「（執筆時に確かめる）」のまま（執筆者の提案のとおり埋める。abc457_g は lis のページの要約と文が違うので、どちらかにそろえる）。abc457_g の evidence に `https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/`（一覧のページ）が入っている。11 問の checked に 2026-10-21 を入れてよい（上の出典で問いと方針を確かめた）

## 指摘

### 1｜直すべき｜fact（F2）｜#farthest-pair の 99 行と #pitfalls の 207 行「x + y は 2×10^9 まで動き、int に収まらない」

- **問題**：座標の絶対値が $10^9$ 以下なら $u = x + y$ は $[-2 \times 10^9, 2 \times 10^9]$ で、`int`（上限 2147483647）に収まる。収まらないのは差 $\max u - \min u$（最大 $4 \times 10^9$）と、距離 $\lvert u - u_0 \rvert$ のほうである。結論（`long long` で持つ）は正しいが、理由が誤っている
- **根拠**：`INT_MAX` = 2147483647 > 2×10^9（t.cpp で出力）
- **直し方**：99 行は「座標が $10^9$ までなら $u$ は $\pm 2 \times 10^9$ で `int` の上限（約 $2.1 \times 10^9$）にほとんど余裕がなく、差 $\max u - \min u$ は $4 \times 10^9$ まで動いて `int` に収まらない。変換した値から `long long` で持つ」とする。207 行も同じく「$x + y$ は $\pm 2 \times 10^9$、その差は $4 \times 10^9$ まで動き…」とする

### 2｜直すべき｜fact（F3）｜#parity-after-rotation の 181 行「その半分のマスは空のままになる」

- **問題**：$(H + W - 1)^2$ の配列のうち元のマスに対応するのは $HW$ 個で、空のマスは半分ではなく半分より多い。偶奇の違う半分に加えて、回転後のひし形（元の長方形の像）の外の隅も空になる。$H = W = 4$ では 49 マス中 16 マスしか使わず、33 マス（約 2/3）が空。$H = W$ が大きいと約 3/4、$H = 1$ では $W^2$ 中 $W$ 個しか使わない
- **根拠**：$S = H + W - 1$、使うマスは $HW$。$H = W = n$ で $HW / S^2 = n^2 / (2n - 1)^2 \to 1/4$
- **直し方**：「その半分以上のマスは空のままになる（偶奇の違うマスと、元の盤面の像の外の隅。$H = W$ なら約 3/4）」とする

### 3｜直すとよい｜fact（F2）・clarity（U3）｜#parity-after-rotation の 183 行と力試しの方針（331 行）の「増加列」「最長減少部分列」

- **問題**：ABC457 G では $T - X$ が同じで $T + X$ が違う点が出るので、どちらが広義・狭義かで答えが変わる。183 行は「[最長増加部分列](../dp/lis.md#dilworth)の問題に帰着」、331 行は「増加列への最小分割数は最長減少部分列の長さ」とだけ書き、広義と狭義の区別とソートの同順位の扱いがない。lis のページ #dilworth は「狭義増加 ↔ 広義減少、広義増加 ↔ 狭義減少」と書き分けており、そちらとそろえたい。183 行の「最長増加部分列の問題に帰着」も、実際に求めるのは減少列の最長なので読者が取り違えやすい
- **根拠**：lis.md #dilworth の定理の文。ikatakos の ABC457 のメモ（(x, y) の組でソートし、y の列の最長の狭義減少部分列を求める）
- **直し方**：183 行を「行ける順に並ぶ点の列は両方の座標が減らない列になり、必要な列の数は[Dilworth の定理](../dp/lis.md#dilworth)で減少列の最長に帰着する」とする。331 行を「$(T - X, T + X)$ の組で昇順にソートすると、1 台が取る列はもう一方の座標の広義増加列になり、広義増加列への最小分割数は最長の狭義減少部分列の長さに等しい」とする

### 4｜直すとよい｜fact（F2）｜#diagonal-coordinates の 167 行「色が同じマスへは何手かで必ず行け」

- **問題**：$H = 1$ か $W = 1$ の盤面ではビショップは動けず、同じ色のマスにも行けない（1 × 3 の (0,0) と (0,2)）。$H, W \ge 2$ なら成り立つ
- **根拠**：t.cpp の BFS で、$H, W \le 5$ のうち 1 × W・H × 1 だけで同色の未到達マスが出た
- **直し方**：「$H, W \ge 2$ の盤面（または無限の盤面）では、色が同じマスへは何手かで必ず行け…」とする

### 5｜直すとよい｜fact（F1・F10）｜front matter の complexity（13 行）と要点の計算量（46 行）

- **問題**：要点には「点の更新つきの最遠点はセグメント木で 1 回 $O(\log N)$」があるが、front matter の complexity にない。チェックリスト F1 は 3 か所の一致を求める
- **直し方**：complexity に「点の更新つきの最遠点はセグ木で 1 回 O(log N)」を足す

### 6｜直すとよい｜clarity（U6）｜#farthest-pair の 113 行「コードは[ACL では](#acl)の囲みにある」

- **問題**：segtree-farthest のコードは `!!! info "ACL では"` の囲みの外（222〜226 行、`## ACL では` の節の本文）にある。囲みを開いても見つからない。見出しと囲みが同じ「ACL では」で二重になっている点は、執筆者が手引きへの提案で決定を求めている
- **直し方**：「コードは[ACL では](#acl)の節にある」とする。囲みと節の扱いはメインの決定に合わせる

### 7｜直すとよい｜clarity（U4）｜例題 ABC366 E の解法の詳細（280〜282 行）

- **問題**：計算量が $O(N \log N + R \log R)$ で終わり、$R$ がどのくらいかが分からず、全部の候補を並べてよいのか読者が判断できない。出典（testcampus）は候補を $-2 \times 10^6$〜$2 \times 10^6$、merom686 は約 $4 \times 10^6$ 個としている
- **直し方**：「候補の数 $R$ は座標の範囲の幅に $2D$ を足した程度で、この問題では数百万に収まる」のように、具体的な制約に頼らない大きさの目安を一言添える（制約の数は確かめられていないので書かない）

### 8｜直すとよい｜figure（G5）｜rotate.svg の右の図の目盛り「-2」「2」

- **問題**：右の図の目盛りの文字（x = 428 と 564）が正方形の縦の辺の真上にあり、青い線が「-2」「2」を貫いて読みにくい（左の図はひし形の頂点の下なので重ならない）
- **根拠**：Windows の Chrome で等倍と幅 358px に描いた画像（v-manhattan-chebyshev/wrotate.png・wnarrow.png）
- **直し方**：右の図の目盛りの文字を辺から少しずらす（「-2」は `text-anchor="end"` で x = 424、「2」は `text-anchor="start"` で x = 568 など）か、白い縁取り（`paint-order="stroke"`・`stroke="#fff"`）を付ける

## 総合の判定

小さな直しで可（直すべき 2・直すとよい 6）。直すべき 2 件はどちらも 1 文の書き換えで済む（int の範囲の理由、回転後の配列の空のマスの割合）。コード片 4 つは乱数の突き合わせとサニタイザで問題がなく、図 2 枚も値・描画とも正しい。出典 11 件と方針の食い違いはない。
