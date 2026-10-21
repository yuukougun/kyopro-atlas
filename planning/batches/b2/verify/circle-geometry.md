# circle-geometry の検証（b2）

- 対象：docs/geometry/circle-geometry.md、snippets/circle-geometry/{relation,connect,lattice,enclose}.{cpp,yaml}、docs/img/circle-geometry/{two-circles,enclose-candidates}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py circle-geometry`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない。ikatakos.com は今回も 503 で読めなかった

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page circle-geometry`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/circle-geometry`：connect 5・enclose 8・lattice 10・relation 3 case すべて一致
- enclose：`-fsanitize=address,undefined` を付けて、候補の全列挙と Welzl を 3300 組で比べた（座標 ±3・±10^9・一直線上・重なる点ばかり、半径 10^9−1 の円周上の 40 点）。食い違い 0、サニタイザの報告なし。Welzl は N = 2×10^5（座標 10^9 規模）で 0.02 秒。執筆者の未解決の点（10^9 規模での EPS）は、この範囲では問題なし
- lattice：小数の桁数 0〜4・負の座標・半径 0〜9 の 300 例で、Python の Fraction による全探索と一致（サニタイザ付き）
- 外心の式：$2u \cdot b = \lvert b \rvert^2$、$2u \cdot c = \lvert c \rvert^2$ をクラメルの公式で解いた形と一致。外積は座標 10^9 で最大 $8 \times 10^{18}$ で `long long` に収まる
- 2 円の交点の式（$a = (d^2 + r_1^2 - r_2^2) / 2d$）・表の 5 通り・$D \le 8 \times 10^{18}$・$50^4/6 \approx 10^6$（$\binom{50}{3} \cdot 50 = 980000$）・$(2 \cdot 10^5)^2 = 4 \times 10^{10}$・ABC259 D の $\binom{3002}{2} \approx 4.5 \times 10^6$：正しい
- 最小包含円の証明：$T$ がどの開いた半平面にも入らない ⇔ $o$ が $T$ の凸包に入る。カラテオドリの定理で 3 点以下に絞れ、辺の上なら直径。論理は通っている（半径 0 の退化だけ指摘 3）
- 入れ子の三分探索（$g(x) = \min_y F$ は同時に凸なら凸）、変わり目の区間で積が単調か上に凸、確認問題 1〜3 の数値（$D = 1, 4, 16$／積 5・9・5）：正しい
- 「関数名の衝突」の囲み：`int relation(...)` を作って呼ぶと g++-15 -std=gnu++23 で `reference to 'relation' is ambiguous`、-std=gnu++17 では通る。本文どおり
- ACL の囲み：dsu の merge・same・size はドキュメント（document_ja/dsu.md）でならし $O(\alpha(n))$。一致
- 例題・練習・力試し 7 問：`tools/ap.py show` で題名・diff が本文と一致。台帳はすべて確認済み
- ABC259 D（執筆者の未解決の点 1）：はまやん氏の記事は配列 3010 と「int だとあふれるので long long」、検索結果の要約が $1 \le N \le 3000$、座標 $\pm 10^9$、$1 \le r \le 10^9$ を示す。本文の「3000 程度」「10^9 規模」と食い違いなし。kyo-pro 氏の記事で $(r_i - r_j)^2 \le D \le (r_i + r_j)^2$ の判定も確かめた
- ABC292 F（執筆者の未解決の点 2）：三角形が長方形に入るかは向きを決めると外接長方形の幅と高さだけで決まるので、向き $\varphi$ を細かく全部試す Python の全探索（厳密な上限）と、本文の方針（1 頂点を角、$0^\circ \le \theta \le 30^\circ$、横 $W / \cos\theta$ と縦 $H / \sin(\theta + 60^\circ)$ の交点を二分探索、$2H/\sqrt3 \le W$ なら $\theta = 0$）を 15 組（1×1、1000×1、1000×999、乱数）で比べ、相対 $10^{-5}$ 以内で一致した。方針は正しい（理由の 1 文を足す案は指摘 4）
- ABC181 F：drken 氏の記事で壁 $y = \pm 100$、$N \le 100$、$\lvert x_i \rvert, \lvert y_i \rvert < 100$、$0 < r \le 100$、壁までの重み $100 - y_i$・$y_i + 100$、最初につながる辺の半分が答え、を確かめた。本文と一致
- ABC157 F：drken 氏の記事で $K \le N \le 60$、時間は $c_i \times$ 距離、時刻の二分探索、候補は中心と 2 円の交点、1 回 $O(N^3)$ を確かめた。本文と一致
- Library Checker：GitHub の task.md で「各点が最小包含円の周上にあるかを 0/1 の文字列で答える」「入力は整数・すべての点は異なる」を確かめた。本文の囲みどおり
- 参考の URL：ドメインはすべて付録 B（hatenablog の各氏・blog.hamayanhamayan.com・judge.yosupo.jp）。読んだもの（hamayan・kyo-pro・merom686 の ABC292・drken の ABC181・ABC157）は題名・内容が書かれたとおり
- リンク先の anchor（integer-root#sqrt-correction、geometry-precision#integer-comparison・#scale-to-integer、ternary-search#convexity・#flat-pitfall、binary-search-answer#real-number、union-find-connectivity#binary-search、glossary#cross-product）はすべて存在する
- 図：two-circles の 5 つの配置（離れる d=85>65、外接 d=65、交わる d=42 と交点 (111.6, 285±23.2)、内接 d=20=45−25 と接点 335、内包 d=10<27）と、enclose-candidates の鈍角（3 点目は中心から 33.5<70、頂点の角は鈍角）・鋭角（3 点とも中心から 70.4、3 つの角はすべて鋭角）は座標の計算どおり。白背景・viewBox・font-family="sans-serif"・相対パス。360px でも文字が読め、重なりなし。代替テキストで要点が分かる

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact F7・clarity U3 | lattice-points-in-circle の「整数の平方根」の箇条書き | 「$r^2 \le m < (r + 1)^2$ になるまで補正する」の $r$ が、同じ節で円の半径に使っている $r$ と同じ文字。直前の段落では平方根を $w = \lfloor \sqrt m \rfloor$ と呼んでいる | 本文 95 行目と 109 行目 | 「$w^2 \le m < (w + 1)^2$ になるまで補正する」にする |
| 2 | 直すとよい | clarity U3 | geometry-optimization の「時刻を決めると円の共通部分の判定になる」 | $c_i$ がこの節で定義されないまま「半径 $T / c_i$ の円」が出てくる。何の問題の話かは力試しの節まで読まないと分からず、断片で読むと通じない | 本文 200 行目。$c_i$ の説明は 327 行目の力試しの方針だけ | 「点 $i$ までの距離に係数 $c_i$ を掛けた時間がかかるとき、時刻 $T$ までに…」のように、$c_i$ の意味を同じ文で添える |
| 3 | 直すとよい | fact F2 | min-enclosing-circle の「必ず次のどちらか」と証明、circumcenter の「すべての点が同じ位置なら…（中点の候補で出る）」 | $N = 1$ では 2 点も 3 点もなく、どちらの候補にも当たらない（中点の候補もない）。証明も $r = 0$ のときは「距離を $r$ より小さくできる」が成り立たない。コード（`best` の初期値を `far2(p, p[0])` にしている）は正しく扱っている | 本文 130・178 行目、enclose.cpp 33 行目のコメント「N = 1 なら 0」 | 130 行目の直後に「（点が 1 つか、すべて同じ位置なら半径 0）」を足し、178 行目は「答えは半径 0 である（$N = 1$ でも出るよう、最初の答えを点 1 つの円にしておく）」とする |
| 4 | 直すとよい | clarity U2 | practice の「練習の方針」の ABC292 F | 「1 頂点を左下の角に置き、$0^\circ \le \theta \le 30^\circ$ でよい」理由が書かれていない（執筆者の未解決の点 2）。方針自体は全探索と一致した | 上の「確かめたこと」の数値実験。理由：三角形の外接長方形の 4 辺には頂点が触れ、頂点は 3 つなので 1 頂点は外接長方形の角にある。2 辺の向きが $\theta$ と $\theta + 60^\circ$ で両方とも第 1 象限に入るのが $0 \le \theta \le 30^\circ$ | 「三角形が入るかは外接長方形が入るかで決まり、外接長方形の角には三角形の頂点があるので、1 頂点を角に置いてよい」を 1 文足す |
| 5 | 直すとよい | code C3 | relation.cpp 17 行目と 6 行目のコメント | 「5：一致」「中心も半径も同じなら一致」とあるが、半径 0 の同じ 2 点（本文の「点を半径 0 の円とみなす」使い方で始点と終点が同じとき）は 15 行目の `d2 == s2` に先に当たって 1（外接）を返す。`touches` の結果は正しい | `printf "2\n3 4 0 3 4 0\n0 0 0 1 0 0\n" \| ./rel` → `external 1` | 17 行目の判定を先に置く（`if (d2 == 0 && r1 == r2) return 5;` を最初に）か、コメントに「半径 0 どうしは外接として返す」と書く。cases に半径 0 の同じ 2 点を足す |
| 6 | 直すとよい | code C3・clarity U4 | enclose.cpp 56 行目（welzl の取り込みの範囲） | `r2 * (1 + 1e-12L) + 1e-12L` の幅に説明がない。読者は「なぜ足すのか・なぜこの値か」で止まる（Library Checker の囲みで EPS が結果を左右すると書いているので、なおさら） | コードを読んで。座標 10^9 規模の 3300 例で全列挙と一致したので値は妥当 | 同じ行に「// 誤差で周上の点を外と判定しないよう、相対と絶対の小さな幅を足す」とコメントを足す |

## 執筆者の未解決の点について

- ABC259 D の制約：はまやん氏の記事（配列 3010・long long の注意）と検索結果の要約で確かめた。本文のぼかした書き方のままでよい
- ABC292 F の $0^\circ$〜$30^\circ$：数値実験で正しい。理由の 1 文を足す案は指摘 4
- ABC191 D・ABC157 F の ikatakos：今回も 503。ABC157 F は drken 氏の記事で確かめた
- Library Checker の問題の形：GitHub の task.md で確かめた。本文どおり
- Welzl の EPS（座標 10^9 規模）：3300 例で一致。コメントの案は指摘 6

## 台帳への提案

- abc157_f：checked を 2026-10-21 に（drken 氏の記事で問いと方針を確かめた。執筆者の提案と同じ）
- abc292_f：checked を 2026-10-21 に（merom686 氏の記事で 1 頂点を角に置き角度を二分探索する方針を確かめ、全探索で正しさを確かめた）。alternatives の approach を執筆者の提案のとおり二分探索の形にするのに賛成
- abc259_d：evidence に https://blog.hamayanhamayan.com/entry/2022/07/09/224142 を足す案に賛成
- abc191_d：summary に「（周上を含む）」を足す案に賛成（本文の囲みはすでにその形）

## 総合の判定

小さな直しで可。直すべき指摘は 0、直すとよい指摘は 6（記号の重なり・$c_i$ の定義・$N = 1$ の退化・ABC292 F の理由・コードのコメント 2 つ）。
