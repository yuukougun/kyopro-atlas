# argument-sort の検証（工程8b・b1）

- 対象：docs/geometry/argument-sort.md、snippets/argument-sort/{sort-points,range-sum,half-window,atan2-limit}.{cpp,yaml}、docs/img/argument-sort/half-planes.svg（動く図はない。catalog の visual は priority 2）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page argument-sort`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/argument-sort`（4 片・コンパイル 4 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/geometry/argument-sort.md`（0 errors・26 warnings。数式の中の `[0, 2\pi)`・`(-\pi, \pi]` を括弧の対応の誤りとみるもの、数式・コードを含む文の長さと読点の数で、§13.8 により残してよい）
- front matter：骨格（57d1492 の親）との差は complexity・stage と要点以降の本文だけ。complexity・要点の計算量・本文（range-count の節）が一致する。sections の見出しの文字は title と一致し、定型の節（例題・練習問題・力試し・確認問題・使い分け・落とし穴・参考）は §13.1 の見出しと anchor で、sections に載っていない
- コード片：4 片とも `-fsanitize=address,undefined` 付きでコンパイルし、cases と乱択の入力で報告なし。作業用の場所 v-argument-sort/brute.py で、座標 ±1・±2・±5 の乱択 300 件（原点・同じ方向・x 軸上を含む）を素朴な方法と比べ、sort-points（stable_sort の順を含む）・range-sum（u と v が同じ方向・一周をまたぐ場合を含む）・half-window がすべて一致した。atan2-limit は `same` と `-1` を出す。書き方（bits・using namespace std・マクロと型の別名なし・`'\n'`・ラムダは比較関数だけ）は §9 に合う。取り込みの範囲は要点だけで、本文の手順（lower_bound・upper_bound・半開区間）と変数がそろう
- 自分で導かれた主張を小さなプログラムで確かめた（作業用の場所 v-argument-sort/）
    - 本文の具体例の外積：61〜65 行（1・2・1）、90 行（1）、99 行（−1）、134 行・270 行・276 行の値は手計算で正しい
    - 表の「$(-\pi, \pi]$ のときの前半・後半」：座標 ±4 の乱択 2000 件で atan2 の順と一致（maspy の angle_sort.hpp・drken の記事の分け方とも同じ）
    - 原点を含む三角形の数 $\binom{N}{3} - \sum \binom{k_i}{2}$（どの 2 点も原点と一直線上にない）：全組の数え上げと 300 件一致
    - 反対方向の lower_bound とその 1 つ前の 2 候補で最大のなす角が取れること：全候補と 500 件一致
    - ABC139 F の「2 周分の列の連続した範囲（長さ $N$ 以下）を全部試せば最適」：全部分集合と 300 件一致
    - atan2 の順が崩れる座標の大きさ（a2.cpp）：外積が 1 の第 1・第 3 象限の組をおよそ 12 万組ずつ作り、`atan2` の大小を調べた。$C = 10^4, 10^6, 10^7$ では崩れ 0、$C = 10^8$ で約 3 万、$10^9$ で約 22 万が崩れた（指摘 4）
    - オーバーフローの見積もり（$2 \times 10^{18}$・$8 \times 10^{18}$ と `long long` の上限）は正しい
- 事実の出典
    - Library Checker の Sort Points by Argument（GitHub の library-checker-problems の task.md）：順は atan2 の $(-\pi, \pi]$（負の $x$ 軸の始まりから反時計回り）、原点の偏角は 0、同じ偏角の点の順は任意。本文の「原点の偏角を 0 と決めている」は正しい（指摘 5）
    - drken の記事：分け方（正の $x$ 軸を下の半平面の組に入れる）・原点を自分の組にする・atan2 の懸念は本文・参考の記述と一致。本文の例の数値は記事になく、近すぎる箇所はない
    - maspy の geo/angle_sort.hpp：下の半平面と正の $x$ 軸を 1 つの組、原点、上の半平面と負の $x$ 軸の順。参考の記述と一致（指摘 7）
- 問題：6 問とも `python3 tools/ap.py show` で題名・diff（1355・なし・1678・2034・2074・2386）が台帳・本文と一致。役割と数（例題 2・練習 2・力試し 2）は台帳と一致。evidence を読んで方針を確かめた
    - ABC442 E（ikatakos の解説の部分）：クエリの両端はモンスターの番号で、その方向から時計回りに回る。同じ方向なら回らない。座標は $10^9$ 規模で atan2 では誤る。本文の方針・range-count の手順（同じ方向なら 3 の場合）と一致
    - 典型90 009（E869120 sol/009.cpp）：各 $B$ で角度を並べ、反対方向を lower_bound して位置とその 1 つ前の 2 候補、$O(N^2 \log N)$。点の配列は 2009 要素で、$N$ は 2000 程度までと読める
    - ABC225 E（merom686）：第 1 象限の図形を区間にし、外積で比べ、右端の順の貪欲。端だけ接する場合の扱いは記事にない（本文は問題の定義に合わせると書いており、それでよい）
    - ABC139 F（ikatakos の解説の部分）：最適な集合は和との内積の符号で決まる半平面で、偏角の列の連続した範囲。本文と一致
    - ABC207 D（drken）：座標を $N$ 倍して重心を整数に、重心と同じ点を除く、偏角の順に並べ、（長さの 2 乗・次の点との内積・外積）の列を巡回シフトで照合する。偏角が等しい点は長さの 2 乗で順を決めている（指摘 2）
    - ABC479 G（kmjp）：問い（有理数の $C_i, D_i$ を足して比をそろえ、$\sum (\lvert C_i \rvert + \lvert D_i \rvert)$ を最小にする）は本文の要約と一致。$A_i < 0$ なら $(A_i, B_i)$ の符号を反転、$A_i = 0$ の点は並べる対象から外して費用だけ数える（指摘 6）
    - 台帳の `checked` に 2026-10-21 を入れてよい：abc442_e・typical90_i・abc225_e・abc139_f・abc207_d・abc479_g。abc479_g の summary は「（執筆時に確かめる）」のままなので、執筆者の提案どおり本文の要約を台帳に入れる
- 参考の URL：9 件とも付録 B のドメイン（hatenablog・ikatakos.com・github.com・kmjp.hatenablog.jp）。drken 2 件・merom686・kmjp・ikatakos 3 件・E869120・maspy を開き、題名と内容が書かれたとおり。ikatakos は解説の部分だけを読んだ
- 図 half-planes.svg：Windows の Chrome（headless=new）で、等倍（520×420、2 倍密度）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（作業用の場所 v-argument-sort/full.png・narrow.png）。点の座標（40px が 1）と順位 1〜7（(1, 2) と (2, 4) が同じ 3）は偏角と一致し、代替テキスト・本文と合う。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、正の $x$ 軸は実線・負の $x$ 軸は破線で色以外でも区別できる。文字の重なりがある（指摘 1）
- リンク先：cpp-comparators#strict-weak-ordering・#less-equal-pitfall、prefix-sum#circular、binary-search#lower-bound、interval-scheduling#why-right-end はどれも draft で anchor がある。convex-hull は stub（ページへのリンクだけでよい）。geometry-vectors・geometry-precision・rotation-transform は今は draft になっている
- 執筆者の未解決の点
    1. 典型90 009 の $N$：解答コードの配列の大きさから 2000 程度と読める。本文は $N$ を書いていないので直す必要はない
    2. ABC225 E の端の扱い：記事にもない。本文の書き方でよい
    3. ABC442 E の両端：モンスターの番号（ikatakos）。「方向 A」と書いても方針は変わらないので直す必要はない
    4. ABC479 G の「片方の成分だけを動かせばよい」：成り立つ。原点を通る直線 $ax + by = 0$ に点 $(A, B)$ を動かす費用は、$a c + b d = -(aA + bB)$ の下で $\lvert c \rvert + \lvert d \rvert$ を最小にするので $\lvert aA + bB \rvert / \max(\lvert a \rvert, \lvert b \rvert)$ で、係数の絶対値が大きい方の成分だけを動かすと達成される。どちらの成分かは直線だけで決まり、点によらない。だから最適解では全点が同じ成分だけを動かし、2 つの場合の小さい方が答えになる（指摘 6）
    5. atan2 で崩れにくい座標の大きさ：上の実験のとおり（指摘 4）
    6. stub のページ：上のとおり

## 指摘

### 1｜直すべき｜figure（G5・G3）｜docs/img/argument-sort/half-planes.svg の正の x 軸の注記

- **問題**：「正の x 軸（実線）は前半」（x=470 右寄せ・y=205）が、点 1 の座標の注記「(4, 0)」（x=426・y=203）と点 1 の円の上端に重なり、画像では「（実線）(4, 0)は前半」のように読めない。幅 358px に縮めた画像でも同じ
- **根拠**：v-argument-sort/full.png・narrow.png（headless Chrome で描画）
- **直し方**：注記を軸の下側（例：y=240、点 1 の円より下）へ移すか、「(4, 0)」を円の下（y=245 付近）へ移す。あわせて「(2, 4)」が前半の塗りの上端（y=40）にかかっているので、点 (2, 4) の注記を円の右（x=348・y=60）へ下げるとよい

### 2｜直すべき｜fact（F5・F2）｜#challenge の「力試しの方針」ABC207 D（261 行）

- **問題**：「各点集合を偏角の順に並べ、隣り合う点の組から（長さの 2 乗・内積・外積）の列を作る」には、同じ方向で長さの違う点の並べ方がない。`arg_less` では同じ方向の点が等しいので、並びが入力の順で決まり、合同な 2 つの集合でも列が食い違って「No」と誤る（例：$\{(1, 0), (2, 0), (0, 1)\}$ と、同じ点を別の順で入力したもの）。参考にした drken の記事も偏角が等しいときは長さの 2 乗で順を決めている
- **根拠**：drken「AtCoder ABC 207 D - Congruence Points」の並べ方（偏角が主、長さの 2 乗が従）。本文 118 行の「arg_less はこの 2 点を等しいとして扱う」
- **直し方**：「偏角の順に並べ（同じ方向なら原点に近い順）」と添える

### 3｜直すとよい｜fact（F2）・clarity（U3）｜#angular-intervals の ABC139 F の議論（190 行）

- **問題**：「選んでいないベクトル $v$ が $s \cdot v \ge 0$ を満たすなら $\lvert s + v \rvert^2$ は $\lvert s \rvert^2$ より大きい」は $v \ne 0$ のときだけ正しい（$v = 0$ なら等しい）。長さ 0 のベクトルを除くことは 192 行に後から出てくる
- **根拠**：$\lvert s + v \rvert^2 - \lvert s \rvert^2 = 2 s \cdot v + \lvert v \rvert^2$
- **直し方**：議論の前に「長さ 0 のベクトルは和を変えないので除いておく」を置くか、「長さ 0 でない $v$」と書く。192 行の同じ文は消してよい

### 4｜直すとよい｜fact（F2）｜#atan2 の「座標が $10^4$ 程度までなら」（108 行）と確認問題「atan2 で足りるか」

- **問題**：(a)「十分大きいとき、つまり座標が $10^4$ 程度までなら」の「つまり」が式から出ない。$1 / (2C^2)$ が `double` の間隔 $10^{-16}$ と並ぶのは $C \approx 7 \times 10^7$ で、$10^4$ では $5 \times 10^{-9}$ と 7 桁の余裕がある。(b)「$1 / (2C^2)$ 程度まで小さくなりうる」の理由として挙げた「外積は絶対値 1 以上、長さは $\sqrt{2} C$ 以下」は下限の理由で、「小さくなりうる」の理由ではない
- **根拠**：v-argument-sort/a2.cpp。外積が 1 の組で `atan2` の大小を調べると、$C = 10^6, 10^7$ でも崩れ 0、$10^8$ で崩れ始める
- **直し方**：「異なる 2 方向の偏角の差は $1 / (2C^2)$ 以上である（外積は 0 でなければ…だから）。座標が $10^6$ 程度までなら、これは `double` の間隔の 1000 倍以上あり、`atan2` で並べても順序は崩れない。$10^9$ では間隔より小さくなる」のように、下限であることと余裕の大きさを書く。安全側に $10^4$ を残すなら「余裕を見て」と添える

### 5｜直すとよい｜fact（F2）・clarity（U4）｜#edge-cases の Library Checker の記述（116 行）

- **問題**：Library Checker の Sort Points by Argument は原点だけでなく順そのものが $(-\pi, \pi]$（負の $x$ 軸の直後から反時計回り）で、原点は偏角 0 の位置（負の偏角の点と正の $x$ 軸の点の間）に入る。本文は原点のことだけを書き、このページの既定（$[0, 2\pi)$、原点は先頭）のコード片ではそのまま通らないことが読み取れない。front matter の verify にこの問題が入っているので、自作ライブラリにする読者が迷う
- **根拠**：library-checker-problems の geo/sort_points_by_argument/task.md、drken の記事（原点を独立した組にして負の偏角の組と正の偏角の組の間に置く）
- **直し方**：「Library Checker の Sort Points by Argument は順が $(-\pi, \pi]$ で、原点の偏角を 0 とする（下の表の 1 行目の分け方にし、原点の組を前半と後半の間に置く）」とする

### 6｜直すとよい｜fact（F5）・clarity（U2）｜#challenge の「力試しの方針」ABC479 G（262 行）

- **問題**：(a)「片方の成分だけを動かすとして」の理由がなく、読者は「両方動かす方がよい場合は？」で止まる。(b)「$A_i$ を正にそろえて」は $A_i = 0$ の点にはできない。kmjp の解法は $A_i = 0$ の点を並べる対象から外し、費用だけを足している
- **根拠**：上の「未解決の点 4」の議論（原点を通る直線への $L_1$ の距離は、係数の大きい方の成分だけを動かして達成され、その成分は直線だけで決まる）。kmjp の記事の $A_i = 0$ の扱い
- **直し方**：「直線を決めると、どの点も同じ側の成分だけを動かすのが最も安い（直線への $L_1$ の距離は軸に平行な移動で達成される）」を 1 文足し、「$A_i = 0$ の点は傾きを持たないので並べずに費用 $\lvert B_i \rvert$ の項として足す（傾き $t$ に対し $\lvert B_i - t A_i \rvert = \lvert B_i \rvert$）」と添える

### 7｜直すとよい｜fact（F9）｜#references の maspy（294 行）

- **問題**：URL がライブラリのトップで、比較の流儀がどのファイルにあるか分からない
- **根拠**：比較は geo/angle_sort.hpp の `lower_or_upper`・`angle_comp_3` にある
- **直し方**：URL を `https://github.com/maspypy/library/blob/main/geo/angle_sort.hpp` にし、題名を「maspypy「library geo/angle_sort.hpp」」とする

### 8｜直すとよい｜clarity（U3）｜#half-plane-compare の $\theta$ の定義（59 行）

- **問題**：「偏角の差を $\theta = \theta_b - \theta_a$ とすると…$\theta$ が $(0, \pi)$ なら正、$(\pi, 2\pi)$ なら負」は、$\theta$ が負になる場合（$\theta_b < \theta_a$）を述べていない。直前の文の「$a$ から反時計回りに測った $b$ までの角度」とつながりにくい
- **根拠**：$\theta_a, \theta_b \in [0, 2\pi)$ なら差は $(-2\pi, 2\pi)$
- **直し方**：「$a$ から反時計回りに測った $b$ までの角度を $\theta$（$0 \le \theta < 2\pi$）とすると」と定義する。$\sin$ は周期 $2\pi$ なので以降の文はそのまま通る

## 総合の判定

小さな直しで可。直すべき指摘は 2 件（図の文字の重なり、ABC207 D の方針の同じ方向の並べ方）、直すとよい指摘は 6 件。本文の主張・具体例・コード片は素朴な方法との突き合わせですべて正しかった。
