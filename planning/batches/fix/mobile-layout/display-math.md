# display-math の報告（工程11 グループ mobile-layout・Issue #55 の数式の部分）

作業ツリー：`kyopro-atlas-wt/mobile-layout`（ブランチ fix/mobile-layout）。担当は #55 のうち math・comb の別行の数式（`$$…$$`）だけで、表・kp.css・手引き §8 はほかの担当（tables など）の範囲。commit はしていない。gen_site は流していない。日付：2026-10-29。

## まとめ

| Issue | 状態 | 一言 |
| --- | --- | --- |
| #55 | 一部（数式の部分は完了） | 幅 390px で画面幅を超える別行の数式を、math・comb の 93 ページで 119 本 → 0 本にした（調査と同じ判定。実際に横に送れるかの判定では 137 本 → 0 本）。日本語の文を `\text` で入れた長い式（判定 B で 40 本）は、定義の文を地の文に出すか縦に積み、すべて収めた。表・続きの手がかり（影）・手引き §8 はこの担当の外 |

- 直したのは 58 ページ（math 24・comb 34）の 137 本の式。どのページも front matter は `updated: 2026-10-29` だけを変えた（stage は reviewed のまま）
- 直し方の内訳：並べた式・長い等式を `aligned`・`gathered` で縦に積んだもの 114 本（うち 1 本は例示の中間の項も省いた）、定義や注記の文を地の文に出したもの 20 本（そのうち 7 本は定義だけの式で、別行の数式ごと地の文にした）、例示の中間の項を省いて 1 行に収めたもの 3 本。計 137 本。どれも式の意味は変えていない
- 検査：check_pages（58 ページ、エラー 0・警告 0。インラインの `\text` の検査を含む）、textlint（エラー 0。警告は 819 → 855 で、増えたのはすべて `$$…$$` の中の sentence-length。下の「確かめたこと」）

## 計測

調査のスクリプト（`agents/a5/measure.mjs`）を土台にした `measure.mjs` で、作業用フォルダへビルドしたサイト（`uv run mkdocs build -q -d <作業用フォルダ>/site-…`）を `python3 -m http.server` で配って、ヘッドレスの Chrome（幅 390px・モバイルの表示）で math・comb の全 93 ページ（分野の入口 2 ページを含む。調査と同じ）を測った。数式は KaTeX が描き終え（`katex-init.js` が付ける `data-kp-rendered` がすべての数式に付く）、フォントを読み終えてから測る（調査のスクリプトは読み込みの 1.5 秒後に測っていて、ほかの Chrome と同時に動かしたときに描く前のページを測ることがあったので、待つ処理を足した。表の数はこの形で測り直したもので、93 ページとも描き終えてから測れている）。

判定は 2 つにした。

- **A（調査と同じ）**：KaTeX の式の幅 > `div.arithmatex` の clientWidth + 1
- **B（実際に横に送れるか）**：`div.arithmatex` の scrollWidth > clientWidth + 1。スマホの幅では Material が式（`.katex-display`）に左右 0.8rem（16px）の余白を付けるので、式の幅が「入れ物 − 32px」を超えると横に送れる。本文では 358px、囲み（details・admonition）の中では 324px が上限になる（後述の kp.css の変更の後）。A は式の幅が 359〜391px のものを数えないので、B の方が本数が多い

| | ページ | 本数（A） | 本数（B） | うち `\text` の日本語を含む（B） |
| --- | --- | --- | --- | --- |
| 直す前 | 54（A）・58（B） | 119 | 137 | 40 |
| 直した後 | 0 | 0 | 0 | 0 |

- 「`\text` の日本語を含む」は、`\text{…}` の中にかな・漢字がある式を数えた（判定 A では 30 本）。調査の 33 本とは数え方が少し違う（調査の数え方は残っていない）が、どちらにしても直した後は 0 本である
- 折りたたみ（`???`）を閉じたままでも開いても同じ本数だった（閉じた details の中も Chrome が幅を計算する）。直した後も両方で 0 本
- KaTeX のエラー（赤字）は前後とも 0。インラインの数式で行からはみ出すものも前後とも 0、ページ全体の横ずれも前後とも 0
- 直した後の別行の数式は 293 → 286 本（定義だけの式 7 本を地の文にした）
- 計測の途中で、同じ作業ツリーの tables の担当が kp.css を変えた（狭い画面で囲みの中の `div.arithmatex` の左右の負のマージンを 0.8rem → 0.6rem にした。囲みの中の式の上限が 332px → 324px に狭まる）。直す前の数は元の kp.css で測った値で、今の kp.css に差し替えて測り直しても 119・137 本で変わらない。直した後の数は今の kp.css で測った（囲みの中の 1 本がこの変更で 2px はみ出したので、もう 1 段積んだ。comb/counting-basics#coloring の証明）
- 参考（Issue の基準の外）：幅 375px・360px でも測った。下の「残った点」に数を書く

計測に使ったもの（作業用フォルダ `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/mobile-layout/display-math/`）：`measure.mjs`（計測）・`run-measure.sh`（配信と全ページの計測）・`summarize.py`（数える）・`locate.py`（はみ出す式を Markdown の行に対応づける）・`texw.mjs`（候補の TeX の幅を、サイトと同じ CSS の中で測る。本文・囲みの中を選べる）・`patch.py`（書き換えの指定を当てる）・`spec-*.txt`（137 本の書き換えの指定）・`shots.mjs`（切り出しのスクリーンショット）。表の数の元の JSON は `f-before-open.json`（元の kp.css）・`f-before-newcss-open.json`（今の kp.css）・`f-after-open.json`・`f-after-closed.json`、幅を変えたものは `f-*-375.json`・`f-*-360.json`。

## 直し方の約束（全ページで同じにした）

- **並べた式**（`\qquad` や `,\quad` で横に並べた別々の式）は `\begin{aligned}` で `=`・`\equiv` の位置にそろえて縦に積む。左辺の形がそろわないものは `gathered`（中央そろえ）。元の式の読点（`,`）は行末に残した
- **長い等式の鎖** `A = B = C` は `A &= B \\ &= C`。左辺が長く 1 行目に収まらないときは、左辺だけを 1 行目に置き、`&= …` を 2 行目から左端にそろえる（`&A \\ &= B \\ &= C`）
- **同値・ならば の鎖** は `& P \\ \iff & Q`（`\Longrightarrow` も同じ）で、記号を左に出して式の頭をそろえる
- **1 つの長い和・積** は、項の切れ目で折り、続きの行を `&\quad + …`・`&\quad \cdot …` と字下げする
- **条件の添え書き** `\qquad (n \ge 1,\ k \ge 1)` は、収まらなければ次の行に置く（`gathered` なら中央、`aligned` なら式の頭の位置）
- **日本語の定義・説明の文**（`X = \text{…の数}`、`(\text{…})` の注記）は地の文に出し、「…を $X$ とする」の形にした。式に残すのは記号の式だけにした。地の文のインラインの数式には `\text` を入れていない
- 短いラベル（`\text{確定した部分}`・`K \text{ 回}`・`\text{非負整数解}`・`P(\text{$i$ が起きる})` など）は、式の一部なので残し、式を積んで収めた
- 例示の中間の項は、省いても式の値と読み方が変わらないものだけ省いた（4 本。下の表）

## 直したファイル

58 ページ。どのページも front matter の `updated` を 2026-10-29 にした（22 ページは 2026-10-22 から変え、36 ページは今日の別の直しですでに 2026-10-29 だった）。表の「行」は直した後のファイルで、その式（または地の文）の始まりの行。px は直す前の式の幅（判定 B の対象。上限は本文 358px・囲みの中 324px）。

| ファイル | 本数 | 節（anchor）・行・直す前の幅 |
| --- | --- | --- |
| `docs/math/base-conversion.md` | 2 | convert（53 行・415px）、bijective-26（88 行・483px） |
| `docs/math/convolution-ntt.md` | 1 | split-by-bit（209 行・539px） |
| `docs/math/crt.md` | 3 | two-equations（65 行・490px）、garner（143 行・570px）、garner（153 行・558px） |
| `docs/math/digit-and-mod.md` | 2 | suffix-remainder（101 行・397px）、suffix-remainder（110 行・428px） |
| `docs/math/divisor-enum.md` | 1 | count-and-sum（103 行・496px） |
| `docs/math/euler-phi.md` | 1 | formula（57 行・361px） |
| `docs/math/fft-ntt.md` | 1 | butterfly（71 行・572px） |
| `docs/math/floor-sum.md` | 7 | reduce（75 行・537px）、swap-axes（95 行・647px）、swap-axes（105 行・646px）、mod-to-floor（165 行・488px）、mod-to-floor（176 行・429px）、abc443_g（238 行・373px）、quiz（278 行・651px） |
| `docs/math/gcd-lcm.md` | 1 | prefix-suffix-gcd（116 行・441px） |
| `docs/math/gcd-properties.md` | 3 | difference-gcd（63 行・546px）、difference-gcd（74 行・576px）、difference-gcd（83 行・614px） |
| `docs/math/geometric-series-mod.md` | 2 | matrix（117 行・510px）、repeated-digits（140 行・597px） |
| `docs/math/hadamard-transform.md` | 1 | transform（59 行・450px） |
| `docs/math/harmonic-sum.md` | 3 | why-n-log-n（61 行・413px）、collect-multiples（113 行・440px）、quotient-ranges（170 行・676px） |
| `docs/math/integer-root.md` | 1 | compare-sqrt（127 行・523px） |
| `docs/math/linear-recurrence-fast.md` | 1 | bostan-mori（96 行・364px） |
| `docs/math/matrix-power.md` | 2 | composition（215 行・627px）、doubling-transition（238 行・373px） |
| `docs/math/miller-rabin.md` | 1 | miller-rabin（68 行・592px） |
| `docs/math/mod-arithmetic.md` | 1 | why-mod（58 行・497px） |
| `docs/math/mod-inverse.md` | 1 | inverse-table（119 行・452px） |
| `docs/math/multiplicative-function.md` | 2 | dirichlet（65 行・584px）、prime-counting（93 行・486px） |
| `docs/math/multiplicative-order.md` | 1 | bsgs-details（180 行・448px） |
| `docs/math/sigma-manipulation.md` | 5 | linearity（55 行・422px）、linearity（64 行・394px）、linearity（73 行・578px）、group-by-value（136 行・402px）、formulas（162 行・559px） |
| `docs/math/stern-brocot.md` | 2 | continued-fraction（70 行・420px）、best-approximation（97 行・756px） |
| `docs/math/xor-basis.md` | 1 | xor-walk（154 行・430px） |
| `docs/comb/bell-number.md` | 1 | recurrence（56 行・494px） |
| `docs/comb/binomial-coefficient.md` | 1 | pascal（69 行・418px） |
| `docs/comb/binomial-identities.md` | 2 | parity-sum（84 行・385px）、power-sums（188 行・516px） |
| `docs/comb/binomial-precompute.md` | 4 | fact-ifact（68 行・379px）、composite-mod（127 行・457px）、lucas（163 行・376px）、parity-pyramid（186 行・634px） |
| `docs/comb/binomial-prefix-sum.md` | 2 | update（61 行・592px）、update（70 行・476px） |
| `docs/comb/burnside-lemma.md` | 1 | cube（129 行・447px） |
| `docs/comb/cayley-pruefer.md` | 6 | degree-sequence（86 行・746px）、degree-sequence（110 行・454px）、sum-over-degrees（122 行・557px）、sum-over-degrees（134 行・638px）、sum-over-degrees（144 行・389px）、with-polynomials（166 行・693px） |
| `docs/comb/counting-basics.md` | 2 | coloring（112 行・499px）、coloring（124 行・674px） |
| `docs/comb/counting-dedup.md` | 1 | min-index（114 行・492px） |
| `docs/comb/counting-fix-order.md` | 1 | tree-order（138 行・391px） |
| `docs/comb/counting-labeled-graphs.md` | 5 | complement（54 行・380px）、component-of-1（83 行・442px）、by-size（106 行・392px）、bfs-layers（164 行・414px）、exactly-l（179 行・764px） |
| `docs/comb/counting-mindset.md` | 2 | exactly-vs-at-most（103 行・408px）、contribution-with-binomial（127 行・522px） |
| `docs/comb/coupon-collector.md` | 3 | geometric（55 行・495px）、geometric（64 行・480px）、staged（103 行・485px） |
| `docs/comb/divisor-inclusion-exclusion.md` | 1 | partition（67 行・430px） |
| `docs/comb/expectation-linear-equations.md` | 2 | cycle（100 行・423px）、geometric-series（130 行・459px） |
| `docs/comb/expectation-of-square.md` | 6 | difference（52 行・564px）、pairs（87 行・483px）、pairs（106 行・410px）、variance（179 行・524px）、variance（189 行・439px）、abc450_g（231 行・376px） |
| `docs/comb/expectation-tail-sum.md` | 5 | kth-value（93 行・389px）、waiting-time（116 行・464px）、waiting-time（127 行・397px）、continuous（150 行・398px）、exactly-vs-at-least（163 行・493px） |
| `docs/comb/expected-value-dp.md` | 4 | total-expectation（58 行・413px）、total-expectation（66 行・490px）、total-expectation（77 行・519px）、self-loop（156 行・610px） |
| `docs/comb/generating-function-counting.md` | 2 | coefficients（55 行・376px）、formulas（91 行・489px） |
| `docs/comb/grundy-number.md` | 3 | definition（58 行・385px）、sum（100 行・376px）、dp（143 行・368px） |
| `docs/comb/inclusion-exclusion-dp.md` | 7 | first-obstacle（82 行・595px）、first-obstacle（86 行・414px）、count-violations（122 行・665px）、count-violations（134 行・838px）、equal-blocks（153 行・391px）、tree（179 行・876px）、tree（183 行・657px） |
| `docs/comb/inclusion-exclusion.md` | 3 | general（55 行・769px）、general（61 行・387px）、symmetric（124 行・620px） |
| `docs/comb/lgv-lemma.md` | 1 | what（47 行・719px） |
| `docs/comb/linearity-of-expectation.md` | 4 | linearity（57 行・391px）、linearity（68 行・718px）、pairs（166 行・371px）、sum-vs-expectation（189 行・394px） |
| `docs/comb/minimax.md` | 2 | negamax（52 行・674px）、negamax（56 行・363px） |
| `docs/comb/mobius-function.md` | 6 | definition（60 行・476px）、inversion（89 行・394px）、inversion（98 行・581px）、inversion（112 行・400px）、gcd-one（136 行・682px）、gcd-one（150 行・627px） |
| `docs/comb/partition-number.md` | 2 | recurrence（64 行・438px）、partition-dp（194 行・532px） |
| `docs/comb/probability-dp.md` | 3 | forward（72 行・470px）、by-time（123 行・376px）、random-walk（158 行・613px） |
| `docs/comb/rational-mod.md` | 1 | why（69 行・767px） |
| `docs/comb/reflection-principle.md` | 1 | two-sided（192 行・381px） |
| `docs/comb/stars-and-bars.md` | 1 | stars-bars（61 行・396px） |
| `docs/comb/stirling-first.md` | 3 | what（64 行・451px）、recurrence（88 行・500px）、recurrence（104 行・380px） |
| `docs/comb/twelvefold-way.md` | 2 | surjection（130 行・521px）、surjection（141 行・669px） |
| `docs/comb/zeta-mobius-subset.md` | 1 | or-and-convolution（154 行・523px） |

### 地の文を変えたところ（検証で読んでほしい）

式から文を出した 20 本と、式の形を変えたために周りの文を合わせたところ。どれも元の式と同じことを言うように書いた。

| ファイル | 節 | 変えた内容 |
| --- | --- | --- |
| `docs/math/geometric-series-mod.md` | matrix | 2 つの行列の式を縦に積んだので、直後の「右の式は」を「2 つ目の式は」にした |
| `docs/math/harmonic-sum.md` | quotient-ranges | 「値が閉区間 $[qx, (q + 1)x - 1]$ にあり $x$ より大きい要素の個数を $n_q$ とすると、次の式になる。」を足し、式を $\sum_{q \ge 1} q \times n_q$ にした |
| `docs/math/xor-basis.md` | xor-walk | 別行の式（$d(u) \oplus d(v) \oplus$（閉路の値をいくつか XOR したもの））を外し、「ありうる値は、$d(u) \oplus d(v)$ に閉路の値をいくつか XOR したものである。」にした（ページの中で $c$・$c_e$ は別の意味に使われているので記号は足さなかった） |
| `docs/comb/cayley-pruefer.md` | degree-sequence | `cases` の式を「すべての $v$ で $d_v \ge 1$ かつ $\sum_v d_v = 2N - 2$ なら $\frac{(N-2)!}{\prod_v (d_v - 1)!}$ で、それ以外なら 0 である」にした |
| `docs/comb/cayley-pruefer.md` | degree-sequence（応用の型） | 「よって、頂点 $v$ の次数が $k$ の木の数は次のとおりである。」を足し、式を右辺だけにした |
| `docs/comb/cayley-pruefer.md` | sum-over-degrees | 「足す辺の選び方の数は次の式になる」にし、式を右辺だけにした |
| `docs/comb/counting-labeled-graphs.md` | complement | 別行の式（$c(n) = g(n) -$（非連結な $n$ 頂点のグラフの数））を外し、「$c(n)$ を、$g(n)$ から非連結な $n$ 頂点のグラフの数を引いて求める。」にした。続く文の「この式が」を「この引き算が」、「右辺に出てくる $c(k)$」を「引く数を求めるのに使う $c(k)$」にした |
| `docs/comb/counting-labeled-graphs.md` | exactly-l | 「どの成分も大きさ $x$ 以下のものの数を $F(x)$ とすると、最大がちょうど $L$ のものの数は次の式になる。」を足し、式を $F(L) - F(L - 1)$ にした |
| `docs/comb/counting-mindset.md` | exactly-vs-at-most | 「最大値がちょうど $k$ の列の数は次の式になる」にし、式を $k^N - (k-1)^N$ にした |
| `docs/comb/expected-value-dp.md` | total-expectation | 「1 手目で $t$ へ移ったという事象を $A_t$ とすると」を足し、条件を $E[X_s \mid A_t]$ にした（ページの中で $A_t$ はほかに使われていない） |
| `docs/comb/grundy-number.md` | definition | 定義の文に「（行き先）」を足し、式の条件を「$w$ は $v$ の行き先」にした（「行き先」はこのページで 1 手で移れる局面を指す語として、すぐ後から何度も使われている） |
| `docs/comb/inclusion-exclusion-dp.md` | first-obstacle | 定義だけの式を外し、「障害物ごとに、始点から障害物 $i$ まで、ほかの障害物を通らずに行く経路の数を $\mathrm{dp}[i]$ として求める。」にした |
| `docs/comb/inclusion-exclusion-dp.md` | count-violations | 「行と列が重ならない $k$ 個の禁止のマスの選び方の数を $r_k$ とする。」を前に足し、式から注記を外した |
| `docs/comb/inclusion-exclusion-dp.md` | count-violations（状態） | 定義だけの式を外し、「…選び方の数を $\mathrm{dp}[j][\mathrm{mask}]$ とする。」の段落にした |
| `docs/comb/inclusion-exclusion-dp.md` | tree | 定義だけの式を外し、「…符号付きの重みの和を $\mathrm{dp}[v][s]$ とする。」の段落にした |
| `docs/comb/inclusion-exclusion.md` | general | 式の後ろの注記を、式の後の文「$N(S)$ は $S$ の条件をすべて破るものの個数で、$S$ の外の条件は破っても破らなくてもよい。」にした |
| `docs/comb/inclusion-exclusion.md` | symmetric | 「$\lvert S \rvert = k$ のときの $N(S)$ を $f(k)$ とすると、次のようになる。」を足し、式から注記を外した |
| `docs/comb/lgv-lemma.md` | what | 「置換 $\sigma$ ごとに、$P_i$ が $a_i$ から $b_{\sigma(i)}$ への経路で、どの 2 本も頂点を共有しない組 $(P_1, \dots, P_k)$ の数を $n(\sigma)$ とすると、次が成り立つ。」にし、式を $\det M = \sum_{\sigma} \operatorname{sgn}(\sigma) \cdot n(\sigma)$ にした（$n(\sigma)$ はこのページでほかに使われていない） |
| `docs/comb/minimax.md` | negamax | 定義だけの式を外し、「局面 $s$ で手番の人が、以後に得る（自分の得点 − 相手の得点）の最大値を $f(s)$ とする。」にした |
| `docs/comb/mobius-function.md` | gcd-one | 「$d$ の倍数である $A_i$ の個数を $C(d)$ とすると、次のようになる。」を足し、式から注記を外した |
| `docs/comb/probability-dp.md` | by-time | 定義だけの式を外し、「時刻 $t$ にちょうど曲が切り替わる確率を $\mathrm{dp}[t]$ と置く。」にした |

### 例示の中間の項を省いたもの（4 本）

| ファイル | 節 | 前 → 後 |
| --- | --- | --- |
| `docs/math/euler-phi.md` | formula | $n (1 - 1/p_1)(1 - 1/p_2) \cdots (1 - 1/p_r)$ → $n (1 - 1/p_1) \cdots (1 - 1/p_r)$（361px で 3px だけはみ出していた） |
| `docs/math/gcd-properties.md` | difference-gcd | $\gcd(a_0, a_1 - a_0, a_2 - a_1, \dots, a_{k-1} - a_{k-2})$ の $a_2 - a_1$ を省いた（2 行に積んでも右辺だけで 358px を超えるため） |
| `docs/comb/grundy-number.md` | sum | $g(v_1, v_2, \dots, v_N) = g(v_1) \oplus g(v_2) \oplus \dots$ の $v_2$ の項を省いた |
| `docs/comb/stirling-first.md` | recurrence | $x(x+1)(x+2)\cdots(x+n-1)$ → $x(x+1)\cdots(x+n-1)$（同じページの倍化の節もこの形） |

そのほか形を変えたもの：comb/expected-value-dp#self-loop の分数は、分子を `aligned` で 3 行にした（分数の形はそのまま。610px → 296px）。comb/mobius-function#definition の $\mu(1), \dots, \mu(12)$ の値の並びは、6 個ずつ 2 行にした。comb/counting-dedup#min-index の和の添字の条件は `\substack` で 2 段にした。

## 確かめたこと

- **計測**：上の「計測」のとおり。390px で、判定 A・B とも、折りたたみを閉じても開いても 0 本
- **見た目**：幅 390px・2 倍の切り出しで、crt（同値の鎖・Garner の 3 行）・integer-root・geometric-series-mod（行列の 2 行）・matrix-power（ラベル付きの行列）・expected-value-dp（$A_t$ の式・分子を積んだ分数）・binomial-precompute（同値の鎖）・inclusion-exclusion-dp（和の途中の改行・`+=` の 2 行）・counting-dedup（`\substack`）・mobius-function（2 行の値の並び・ならばの鎖）・counting-basics（囲みの中の 4 行）・lgv-lemma（$n(\sigma)$ の地の文と式）・grundy-number（行き先の式）・floor-sum（条件を 3 行目に置いた式・囲みの中の 3 行）を目で見て、そろえ・字下げ・行間が崩れていないことを確かめた（`shots/`）。囲みの中の式でも囲みの枠の線は切れていない
- **check_pages**：`python3 tools/check_pages.py --page <58 ページの id>` でエラー 0・警告 0（直す前も 0・0）。`--field math`・`--field comb` でも 0・0
- **textlint**：`npx textlint <58 ファイル>` でエラー 0。警告は 819 → 855（+36）。内訳は sentence-length が +37、max-comma が −1（lgv-lemma）。増えた sentence-length はすべて `$$…$$` の中の行で、地の文の警告の数はどのページも変わっていない。textlint の Markdown の読み方は数式を知らず、`$$…$$` を 1 つの文として長さを数えるので、`aligned`・`\\`・`&` を足すと 120 字を超える（直す前のページにもこの種の警告がある）。基準は直す前の 58 ファイルを `git show HEAD:` で作業用フォルダに出して同じ設定で流した
- **ビルド**：`uv run mkdocs build -q -d <作業用フォルダ>/site-after` が通る（`mkdocs build`・`serve` は動かしていない）
- **front matter**：58 ページとも、HEAD との差は `updated` の行だけであることを機械で確かめた
- **gen_site**：`python3 tools/gen_site.py --check` は「生成物が古い：3 ファイル」（`docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/start/how-to-use.md`）を出す。版（入力の front matter などのハッシュ）が `updated` の変更で変わるためで（同じ作業ツリーのほかの担当の変更も入る）、生成物は手で直していない。メインが gen_site を流せば消える

## 残った点・提案

### 残った点

- **375px・360px（Issue の基準の外）**：判定 B で、幅 375px（本文の式の上限 343px）は 147 本（61 ページ）→ 15 本（14 ページ）、幅 360px（上限 328px）は 161 本（67 ページ）→ 43 本（32 ページ）。375px の 15 本のうち 5 本はこの担当が積み直した式（390px の上限 358px の近くまで使っている。gcd-properties#difference-gcd 357px・probability-dp#forward 356px・generating-function-counting#formulas 353px など）、10 本は 390px では収まっていて触っていない式。360px の 43 本は、積み直した式 19 本・触っていない式 24 本。ほかに、インラインの数式で行からはみ出すものが 375px で 1 か所（comb/partition-number#abc404_f の `\max_{\text{押し方}}` の式）、360px で 2 か所（それと comb/counting-fix-order#sort-and-fix の集合の並び）ある。どれも直す前からあり、この担当の範囲（別行の数式・390px）の外なので触っていない
- 囲みの中の式の上限は kp.css の囲みの余白に左右される（tables の担当の変更で 332px → 324px になった）。kp.css がこの後また変わるなら、`run-measure.sh` で測り直すとよい
- textlint の sentence-length の警告が、別行の数式の中で 37 件増えた（エラーではない）

### 提案（メインに頼む共有ファイルの変更）

1. **手引き §6（記法）に別行の数式の幅の約束を足す**（#55 の §8 の追記は別の担当の範囲なので、数式の書き方だけ）：「別行の数式は幅 390px に収める（本文で式の幅 358px まで、囲みの中で 324px まで）。並べた式は `aligned`（`=` でそろえる）か `gathered` で縦に積み、長い等式は `A &= B \\ &= C`、同値の鎖は `& P \\ \iff & Q` の形で折る。日本語の定義や注記は式に入れず、地の文で「…を $X$ とする」と書く。短いラベル（`\text{非負整数解}` など）は式に残してよい」
2. **textlint で別行の数式を検査から外す**：`.textlintrc.json` に `textlint-filter-rule-allowlist` を入れ、`"allow": ["/\\$\\$[\\s\\S]*?\\$\\$/m"]` のように `$$…$$` の範囲の指摘を消す（package.json の devDependencies にも足す）。今は数式を `aligned` で積むほど sentence-length の警告が増え、地の文の本当の警告が埋もれる
3. **描画の検査（#61、render-check のグループ）に別行の数式の幅を入れる**：今回の `measure.mjs` の判定 B（`div.arithmatex` の scrollWidth > clientWidth + 1）を 390px で全ページに流せば、新しく書いた式のはみ出しを CI で見つけられる。今回の 137 本は math・comb だけで、ほかの分野は測っていない

## メインに判断してほしい点

- 375px・360px でも収めるか（Issue と指示の基準は 390px なので、この担当では 390px で止めた）
- 地の文に新しい記号を入れたところ（harmonic-sum の $n_q$、expected-value-dp の $A_t$、lgv-lemma の $n(\sigma)$）と、例示の中間の項を省いた 4 本（euler-phi・gcd-properties・grundy-number・stirling-first）をこのままにしてよいか

## 検証の指摘への対応

担当：fixup-display-math（この担当の続き）。日付：2026-10-29。検証の報告 `verify-display-math.md` の「直しが要る点」の 2 点を、どちらも検証の案のとおりに直した。変えたのは 2 ページの 2 行だけである。2 ページとも front matter の `updated` はすでに 2026-10-29 で（stage は reviewed のまま）、front matter は変えていない。commit はしていない。gen_site は `--check` だけを流した。検証の「気づいた点（直さなくてよい）」の 2 点（crt#garner の `\dots`、miller-rabin・mod-arithmetic の `\pmod`）は触っていない。

| 指摘 | 状態 | ファイル・行 | 前 → 後 |
| --- | --- | --- | --- |
| 1. counting-dedup#min-index：和の添字の 2 行が重なり、⊆ が ⊂ に見える | 直した | `docs/comb/counting-dedup.md` 116 行 | `\substack{v \in Y \subseteq X \\ Y \text{ がグループにできる}}` → `\substack{v \in Y \subseteq X \\[0.3em] Y \text{ がグループにできる}}`。行の区切りに 0.3em の空きを足しただけで、式のほかの字は変えていない |
| 2. expectation-of-square#variance：「右の形」が縦に積んだ後の並びと合わない | 直した | `docs/comb/expectation-of-square.md` 196 行 | 「右の形は分子が整数なので」→「2 行目の形は分子が整数なので」 |

### 案の選び方

- **1 は検証の案 1（行の間を空ける）にした**。案 2（条件「グループにできる」を地の文に出し、式を `\sum_{v \in Y \subseteq X}` だけにする）では、式だけを読むと $v \in Y \subseteq X$ を満たすすべての $Y$ を足すように読め、和の範囲が地の文の言葉に頼る。この条件は和の範囲を決める式の一部で、上の約束の「短いラベルは式の一部なので残し、積んで収める」に当たるので、式に残した
  - 行の間の指定（`\\[1ex]`・`\\[2ex]`）は cayley-pruefer・geometric-series-mod・matrix-power・linear-recurrence-fast ですでに使っている。`katex-init.js` は外側の `\[ … \]` だけを外すので、`\\[0.3em]` もそのまま KaTeX に届く
- **2 は「2 行目の形」にした**（検証の第 1 案）。geometric-series-mod で使った「2 つ目の式」は別々の 2 本の式を指す言い方で、ここは 1 本の等式を 2 行に積んだものなので、行で指した。`aligned` の行の並びは画面の幅によらず同じなので、行で指してもずれない

### 見た目

幅 390px のモバイル表示で、ライトとダーク、2 倍・4 倍・8 倍で撮った（`zoom.mjs`）。

- **counting-dedup**
  - 直す前は、⊆ の下の横棒が「プ」の上の横画につながり、1 行目が「v∈Y⊂X」と読めた（検証の報告と同じ）。直した後は 2 行が離れ、⊆ の横棒が見える。`aligned` の 2 行（和の行と $\mathrm{dp}[\varnothing] = 1$ の行）のそろえは変わらない
  - 墨の空きを `gap.py` で測った（substack の箱の横の範囲で、墨のある画素の行の帯を数える）。直す前は 2 行の墨が 1 つの帯につながっていた（空き 0。どの倍率でも、ライトとダークでも同じ）。直した後は、1 行目の下端（⊆ の横棒）と 2 行目の上端の間に 4.5 CSS px 空いた（4 倍で 18 画素、8 倍で 37 画素。ライトとダークで同じ）
  - 式の入れ物は clientWidth 390・scrollWidth 390 で、横に送れない（390px に収まる）。KaTeX のエラーは 0
- **expectation-of-square**：式は `aligned` の 2 行で描かれ、分子が整数の形 $\frac{N \sum_i x_i^2 - (\sum_i x_i)^2}{N^2}$ が 2 行目にあることを確かめた。1 行目の分数 $\frac{1}{N}$ と取り違えない

### 計測

display-math の `measure.mjs`（土台は調査の `agents/a5/measure.mjs`）を写し、作業用フォルダへビルドしたサイトを `python3 -m http.server` で配って、math・comb の 93 ページを幅 390px で測った。判定 A・B は上の「計測」と同じである。

| ビルド | 別行の数式 | 判定 A（調査と同じ） | 判定 B（横に送れる） | KaTeX のエラー |
| --- | --- | --- | --- | --- |
| HEAD（最初の直しの前。上の「計測」と検証の値） | 293 | 119 本（54 ページ） | 137 本（58 ページ） | 0 |
| この直しの前（作業ツリー） | 286 | 0 本 | 0 本 | 0 |
| この直しの後（作業ツリー） | 286 | 0 本 | 0 本 | 0 |

- 折りたたみを開いても閉じても同じ数だった。93 ページとも、数式を描き終えてから測れた。インラインの数式のはみ出しと、ページ全体の横ずれも、前後とも 0 だった
- 2 つのビルドの kp.css は同じ版（今の作業ツリーの kp.css）である

### 書き換えない検査

- **check_pages**：`python3 tools/check_pages.py --page counting-dedup`・`--page expectation-of-square` は、どちらもエラー 0・警告 0（インラインの `\text` の検査を含む）
- **textlint**：`npx textlint docs/comb/counting-dedup.md docs/comb/expectation-of-square.md` はエラー 0・警告 15。直す前の 2 ファイル（作業用フォルダに写して 2 つの直しを戻したもの）も、同じ設定で警告 15 で、規則ごとの数も同じだった
  - 違うのは counting-dedup 114 行の `$$…$$` の sentence-length の字数（175 → 182。`[0.3em]` の分）だけで、件数は変わらない
  - 直した 196 行には、前からの no-unmatched-pair が 1 件ある。同じ文の `$[l, r)$`（半開区間）の括弧への誤検出なので、直していない
- **ビルド**：`uv run mkdocs build -q -d <作業用フォルダ>/site-after` は警告なしで通った（出たのは MkDocs 2.0 の案内だけ）。`mkdocs build`・`serve` は動かしていない
- **差分**：直す前に 2 ファイルの sha1 を控えた。直した後のファイルから 2 つの直しを戻すと控えと一致するので、この担当の変更はこの 2 行だけである
- **gen_site**：`python3 tools/gen_site.py --check` は、前と同じ 3 ファイル（`docs/llms.txt`・`overrides/assets/data/graph.json`・`docs/start/how-to-use.md`）を古いと出す。最初の直しなどの `updated` の変更によるもので、この直しは front matter を変えていないので増えていない

### 気づいた点（担当の外。直していない）

- **docs/dp の 2 本の `\substack` にも同じ重なりがある**。2 行目に和文を入れた `\substack` は、math・comb の外に 2 本ある。どちらも HEAD からある式で、このバッチの変更ではない。幅 390px・4 倍と 8 倍で撮ると、1 行目の ≤ の横棒が 2 行目の和文に届く
  - `docs/dp/dp-sequence-partition.md` 58 行（`\substack{0 \le j < i \\ [j, i) \text{ が条件を満たす}}`）：2 行の墨が 1 つの帯につながる（空き 0）。≤ の横棒が「条」の上の横画につながり、$j$ の下端も「件」に重なる
  - `docs/dp/interval-dp-advanced.md` 62 行（`\substack{l < m \le r \\ m = r \text{ または } P_l < P_m}`）：2 行の墨の間が 0.75 CSS px しかなく、≤ の横棒が 2 行目に接して見える。この和は $m = r$ を含むので、≤ が < に見えると範囲を読み違える
  - 直すなら、どちらも行の区切りを `\\[0.3em]` にすれば足りるはずである。docs/dp はこの担当の外なので、メインの判断に回す（画像は作業用フォルダの `shots/other-*.png`）
- **手引きへの提案**：上の提案 1（手引き §6 に別行の数式の幅の約束を足す）に、「`\substack` で和文の行を積むときは、行の区切りを `\\[0.3em]` にする。KaTeX は和文の字を M の高さとして行を詰めるので、和文の上端が上の行の字に届く」を足すとよい

### 作ったもの（作業用フォルダ）

`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/mobile-layout/fixup-display-math/`

- `scripts/measure.mjs`・`scripts/run-measure.sh`・`scripts/summarize.py`：計測（display-math のものを写し、Chrome のプロファイルの置き場だけを変えた）
- `scripts/zoom.mjs`：1 本の式を TeX の一部で探し、高い倍率で撮る（検証の `zoom.mjs` が土台。横に送れる式は substack が見えるところまで送る）。`scripts/gap.py`：substack の 2 行の墨の空きを測る。`scripts/shots.sh`：直した 2 本をまとめて撮る
- 計測の結果：`before-open-390.json`・`before-closed-390.json`・`after-open-390.json`・`after-closed-390.json`
- 画像：`shots/before-*.png`・`shots/after-*.png`（counting-dedup はライト・ダークの 2・4・8 倍、expectation-of-square はライト・ダークの 2 倍）、`shots/other-*.png`（docs/dp の 2 本）
- textlint の結果：`tl-before.json`・`tl-after.json`（直す前の 2 ファイルの写しは `tl-before/`）
- ビルド：`site-before/`（この直しの前）・`site-after/`（後）
