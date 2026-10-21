# binary-search の検証（工程8b・b1）

- 対象：docs/basics/binary-search.md、snippets/binary-search/{meguru,count,triangles}.{cpp,yaml}、docs/img/binary-search/bounds.svg、埋め込みの動く図（overrides/assets/js/viz/binary-search.js。既存の見本で、今回は書かれていない）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page binary-search -v`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page binary-search --check`（直すべき行 0）、`python3 tools/check_snippets.py snippets/binary-search`（3 片・コンパイル 3 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/basics/binary-search.md`（0 errors・4 warnings。59・97 行の max-comma、196 行の sentence-length と no-unmatched-pair。どれも数式・代替テキストの数の列・半開区間 $[j + 1, N)$ の誤検出で、§13.8 により残してよい）、`node --test tests/viz/binary-search.test.mjs`（6 件すべて通る）
- front matter：`git diff` で、変わったのは complexity・stage と要点以降の本文だけ。complexity・要点の計算量・本文（74 行）が一致する
- コード片：3 片とも `-fsanitize=address,undefined` 付きで cases を動かし、報告なし。meguru は lower_bound と assert で比べ、cases に空・1 要素・全部偽・全部真・負の値を含む。count の cases の期待出力を手で数え直した（列 1 3 3 5 5 5 8 は図と同じ）。triangles の cases（2 2 2 2 → 4、1〜5 → 3）も手で正しい。書き方（bits・using namespace std・マクロなし・`'\n'`・ラムダは判定の関数）は §9 に合う。取り込みの範囲（core・query）は要点だけ
- 自分で導いた主張を小さなプログラムで確かめた（作業用の場所 v-binary-search/t.cpp、サニタイザ付き）
    - めぐる式で真の側が左（「$a_i \le x$ を満たす最後」「$a_i < x$ を満たす最後」= lower_bound − 1）を、スニペットと同じ `ng + (ok - ng) / 2` で 2 万組の乱数と比べた。mid は常に両端の間（両端を除く）にあり、答えも一致
    - 表の「閉区間 $[l, r]$ に入る個数 = upper_bound(r) − lower_bound(l)」、降順の列に `greater<>()` を渡した lower_bound が「$x$ 以下の最初の位置」：一致
    - 判定の回数：幅 $2 \times 10^5$ で最悪 18 回、$10^{18}$ で 60 回（本文と一致）
    - 三角形の数え方（2 本を固定して lower_bound）を全組の素朴な数え上げと 3000 組比べて一致。$C(2000, 3) = 1{,}331{,}334{,}000 \approx 1.3 \times 10^9$
    - ABC119 D の方針（最初の行き先は左右の最寄りの 4 か所、その先は残りの種類の左右の最寄り）を、全組と両方の順の素朴な最小と 3000 組比べて一致
    - `while (lo < hi)` の書き方で lo $= -1$、hi $= 0$：`(-1) / 2` は 0 で mid $=$ hi、真のとき区間が縮まない（本文どおり）
    - あふれの閾値：`int` の上限 2147483647、`long long` の上限 9223372036854775807（指摘 2・3）
- 事実の出典：cppreference の lower_bound（「ランダムアクセスでないイテレータでは、イテレータを進める回数は距離に比例する。set などのメンバの lower_bound を使うべき」）と cpprefjp の lower_bound（比較は最大 $\log_2(\mathit{last} - \mathit{first}) + O(1)$ 回、set には専用のメンバ関数を使う）で、156 行の主張を確かめた。`std::midpoint` は cppreference・cpprefjp とも C++20・`<numeric>`、整数で和が奇数なら第 1 引数の側へ丸め、あふれない。`ok + (ng - ok) / 2` も ok 側へ丸めるので「同じ働き」は成り立つ（執筆者の未解決の点 3 は解決）。`partition_point` の返り値、`ranges::lower_bound` が C++20 であることも一致
- 参考の URL：7 件とも開き、題名と著者が書かれたとおり（drken の Qiita 1 件・はてなブログ 6 件）。どれも付録 B のドメイン。本文の文・例は出典と並びも数値も違い、近すぎる箇所はない（めぐる式の例の列も記事と別）
- 問題：7 問（例題 1・練習 4・力試し 1、提案の abc299_d）とも `python3 tools/ap.py show` で題名・diff が台帳・本文と一致し、台帳で確認済み。役割と数は catalog・台帳と一致。evidence（drken の記事）を読み、方針はすべて食い違いがない。ABC205 D は記事でも $A$ は単調増加で、$C_i = A_i - i - 1$（0-indexed）の上で lower_bound する。ABC302 D の「upper_bound の 1 つ手前が $a - D$ 以上なら候補」、ABC321 D の「$P - a$ 以上の最初の位置で分けて累積和と $P \times$ 個数」、ARC084 C の「中段を固定、上段は lower_bound、下段は $N -$ upper_bound」も記事と一致。台帳の `checked` に 2026-10-21 を入れてよい（abc143_d・abc302_d・abc205_d・abc321_d・arc084_a・abc119_d）
- 図 bounds.svg：Windows の Chrome（headless=new）で、等倍（560×250、2 倍密度）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（作業用の場所 v-binary-search/full.png・narrow.png）。値（1 3 3 5 5 5 8、x = 5、lower_bound 3・upper_bound 6、3 個・3 個・6 個）は本文・代替テキスト・count の cases と一致。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、色に加えて破線（5 未満）と実線で区別。はみ出しはない。矢印の向きに誤りがある（指摘 5）
- 動く図：data-config（列 2 3 3 5 7 7 7 9、target 7）で `states` を出すと、mid が 3 → 5 → 4、答え 4 で、本文 65〜68 行の文章と一致。catalog の visual（dynamic・priority 1、ok 側と ng 側のステップ送り）を満たす。JS の mid は $\lfloor (\mathrm{ng} + \mathrm{ok}) / 2 \rfloor$、コード片は `ng + (ok - ng) / 2` だが、この向き（ng < ok）では同じ値になる
- リンク先：interactive・kth-value は stub（§13.4 によりよい）、ほかは draft。glossary#sentinel はある
- 執筆者の未解決の点：(1) frequency_evidence の abc476_d・abc480_d・abc480_e は ap.py では実在する（D. Automat 860・D. Concatenation of Prefixes 864・E. Product-Bounded Arithmetic Sequences 1355）が台帳にない。front matter は執筆者の担当外で、本文にも載せていないので、このページの指摘にはしない（メインが台帳に足すか frequency_evidence を見直すか決める）。(2) 図は上のとおり確かめた。(3) midpoint と set の lower_bound は上のとおり確かめた

## 指摘

### 1｜直すべき｜手引き（§13.1・§13.2）｜front matter の sections と #pitfalls の見出し（27 行・150 行）

- **問題**：「落とし穴」は定型の節なので sections に載せず、見出しを `## 落とし穴 {#pitfalls}` にする決まり（§13.1。上の各節より優先）だが、sections に `anchor: pitfalls` の行があり、見出しが「落とし穴（(ok + ng) / 2 のあふれ・負の数の丸め・set に std::lower_bound）」と長い。執筆者も「手引きへの提案」で迷った点として挙げている
- **根拠**：style-guide §13.1・§13.2（sections の変更は執筆者が行ってよい）。kmp・z-algorithm の検証の「使い分け」の指摘と同じ型
- **直し方**：sections から pitfalls の行を消し、見出しを `## 落とし穴 {#pitfalls}` にする（anchor は同じなのでリンクは壊れない）。かっこの中の 3 項目は節の中の太字の小見出しにすでにある

### 2｜直すべき｜fact（F2）｜#pitfalls の「(ok + ng) / 2 のあふれ」（152 行）

- **問題**：(a)「`int` で ok と ng がどちらも $10^9$ を超えると、和が上限を超える」は誤り。どちらも $1.05 \times 10^9$ なら和は $2.1 \times 10^9 < 2147483647$ であふれない。(b)「`long long` でも、答えで二分探索して $10^{18}$ 付近を探すと同じことが起きる」も誤り。$10^{18}$ 付近の 2 つの和は約 $2 \times 10^{18}$ で、上限の約 $9.2 \times 10^{18}$ に届かない。あふれるのは片方を $4.6 \times 10^{18}$ 以上（`LLONG_MAX` や $5 \times 10^{18}$ の番兵）に置いたとき。(c)「`ok + (ng - ok) / 2` と書けばあふれない」は、ok と ng の符号が違って差が上限を超えるとき（例：$-5 \times 10^{18}$ と $5 \times 10^{18}$）には成り立たない（`std::midpoint` はこの場合もあふれない）
- **根拠**：`INT_MAX` = 2147483647、`LLONG_MAX` = 9223372036854775807（t.cpp で出力）。cppreference の midpoint「No overflow occurs」
- **直し方**：「`int` で ok と ng の和が約 $2.1 \times 10^9$ を超えると（どちらも $1.1 \times 10^9$ 程度なら）あふれる。`long long` でも、ng を $5 \times 10^{18}$ や `LLONG_MAX` のような大きな番兵にすると同じことが起きる」とする。`ok + (ng - ok) / 2` には「差が型に収まる範囲で」と添え、「`std::midpoint(ok, ng)`（C++20）はその場合もあふれず、ok 側へ丸める」とする

### 3｜直すべき｜fact（F2）・code（C3）｜#lower-bound の番兵の値の段落（117 行）と count.cpp の `INF = 4e18`

- **問題**：「$4 \times 10^{18}$ を番兵にして $x$ との差を取ると、`long long` の上限を超えることがある」は誤り。番兵どうしの差でも $8 \times 10^{18}$ で上限（約 $9.2 \times 10^{18}$）に収まり、$\lvert x \rvert \le 10^{18}$ 程度なら $x$ との差も $5 \times 10^{18}$ で収まる。あふれるのは距離を 2 つ以上足したとき（ABC119 D のように「$x$ から番兵まで ＋ 番兵から次まで」で $4 \times 10^{18} + 8 \times 10^{18}$）。また直前に取り込むコード片が `INF = 4e18` を使っており、「4e18 はあふれることがある」と読めて、コード片が誤りの例に見える
- **根拠**：$8 \times 10^{18} < 9223372036854775807 < 1.2 \times 10^{19}$（t.cpp で確かめた）
- **直し方**：「このコード片の $4 \times 10^{18}$ は、差を 1 回取るだけなら収まる。距離を 2 つ以上足し合わせるなら（力試しの ABC119 D など）、番兵どうしの距離も足されるので $10^{18}$ 程度にとどめる」とする。コード片の値を `1e18` にそろえてもよい（cases の出力は変わらない）

### 4｜直すべき｜fact（F2）｜#interactive の「範囲の個数を聞ける場合」（171 行）

- **問題**：「『個数が $m$ 未満（印のない行が含まれる）』は $m$ について単調」は、各行に印が高々 1 つという条件がないと成り立たない。1 行目に印が 2 つ・2 行目に印がないと、$m = 2$ で個数 2 は $m$ 未満でないのに印のない行がある。条件が成り立てば、$c(m) - m$ は $m$ を 1 増やすと増えない（$c(m+1) - c(m) \in \{0, 1\}$）ので単調になる。あわせて $[1, m]$ は閉区間だが断りがない（§6）
- **根拠**：上の反例。$c(m+1) - (m+1) \le c(m) - m$ の計算
- **直し方**：「各行に印が高々 1 つで、閉区間 $[1, m]$（1-indexed の行）にある印の個数を聞けるなら、『個数が $m$ 未満』は…」と条件を足し、単調になる理由（$m$ を 1 増やしても個数は高々 1 しか増えない）を一言添える

### 5｜直すべき｜figure（G5）｜bounds.svg の矢印の向き

- **問題**：2 本の矢印の先が下（列の境目）ではなく左を向いて描かれる。marker の三角形 `M0,0 L8,0 L4,8 z` は下向きに描いてあるが、`orient="auto-start-reverse"` で線の向き（下向き＝90 度）にさらに回されるため、左向きになる。黒い大きな三角が lower_bound の線の左に、upper_bound では「（5 より大きい最初）」の文字の左下に重なって見え、「どの境目を指すか」が読み取りにくい。矢印の色も線の色（青・茶）と違う黒（#333）
- **根拠**：Chrome（headless=new）で等倍と幅 358px に描いた画像（v-binary-search/full.png・narrow.png）で、どちらも三角が左を向く
- **直し方**：marker を `orient="auto"` のまま右向きの三角 `M0,0 L8,4 L0,8 z`、`refX="8" refY="4"` にする（線の向きに回って下を向き、先が線の端に来る）。色は `fill="context-stroke"` か線ごとに marker を分けて青・茶にする。upper_bound の線（y = 72〜86）は短いので、ラベルを少し上げて矢印と文字が重ならないようにする

### 6｜直すとよい｜clarity（U3）・fact（F2）｜#pitfalls の「番兵の位置で判定する」（160 行）

- **問題**：前半は「列の外の番兵で check を呼ぶと配列の外を読む」、後半は「条件が番兵で本当に成り立つかをループの前に確かめる。『答えがなければ −1』の問題では真の側の端が本当に真かを先に判定する」で、2 つの別の話が混ざる。列の外の番兵（ok $= N$）は約束で真とみなすものなので「本当に真か」を確かめる対象ではなく、確かめが要るのは ok を実在の候補（答えの上限など）に置いたとき。読者は「ok $= N$ で check を呼ぶな」と「ok が真かを先に判定せよ」が矛盾するように読む
- **根拠**：54 行（番兵の位置では check を呼ばない）と 160 行後半の食い違い
- **直し方**：「列の外に置いた番兵では check を呼ばない。ok を列の中や答えの候補の上限など実在の位置に置くときは、そこで本当に真かをループの前に確かめる（答えで二分探索の『答えがなければ −1』など）」と 2 つに分けて書く

### 7｜直すとよい｜code（C2）｜count.cpp・triangles.cpp の main

- **問題**：§9 は「main と assert を持つ完全なもの」とするが、2 片とも assert がなく、期待出力は cases の手計算だけで支えている。meguru は lower_bound と assert で比べている
- **根拠**：style-guide §9、code.md C2「assert で中身を確かめていない」
- **直し方**：count は lt・le・left・right を素朴な線形走査と、triangles は小さい $N$ で 3 重ループの数え上げと assert で比べる（t.cpp の比べ方と同じ）

### 8｜直すとよい｜clarity（U6）｜#interactive の「めぐる式の判定」（168・170 行）

- **問題**：節だけを取り出すと「めぐる式」「ok・ng」「番兵の位置を質問しない」（173 行）が何を指すか分からない。170 行の「両端の値が分かっている列」で、両端が列の中の実在の位置（質問しなくても値が分かる位置）である点が、列の外の番兵との違いとして伝わりにくい
- **根拠**：clarity.md U6
- **直し方**：最初の文で「[めぐる式](#meguru)（check(ok) は真・check(ng) は偽を保って間を縮める書き方）」とリンクと一言を添え、170 行に「先頭と末尾は質問しなくても値が分かるので、番兵として使える」と足す

### 9｜直すとよい｜clarity（U9）｜#lower-bound の「左右の最寄り」（107 行）

- **問題**：「その 1 つ手前の要素（$x$ 未満で最小の差）」は「最小の差」が何の差か分かりにくく、コード片のコメント「x 未満で最大」とも言い方が違う
- **根拠**：count.cpp の query の範囲のコメント
- **直し方**：「その 1 つ手前の要素（$x$ 未満で最大）」とする

### 10｜直すとよい｜fact（F2）｜導入（47 行）と #meguru の最初（51 行）

- **問題**：(a)「O(N^2) を O(N log N) にする使い方が最も多い」は数えた根拠がない。(b)「偽から真へ 1 回だけ変わる」は、すべて真・すべて偽の場合（76 行で扱う）を除くように読める
- **根拠**：本文 76 行（すべて真・すべて偽も同じループで扱う）
- **直し方**：(a)「よく出る」程度にする。(b)「高々 1 回だけ変わる（列の外の番兵まで含めれば、ちょうど 1 回）」とする

## 提案への意見（メイン向け）

- 台帳の abc299_d に binary-search の practice を足す提案：問いと型は本文 170 行と合い、diff 684 も基礎のページに合う。ただし interactive の例題なので、本文の練習に足すなら #interactive に置く形がよい
- 用語集「単調性（monotonicity）」の提案は妥当。足すなら 51 行の最初の「単調」からリンクする

## 総合の判定

小さな直しで可。直すべき 5（sections と見出し、あふれの閾値 2 か所、インタラクティブの単調性の条件、図の矢印）、直すとよい 5。どれも数行の文と SVG の marker の直しで済み、構成・コード片・問題・動く図は正しい。
