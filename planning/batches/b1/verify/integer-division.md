# integer-division の検証（工程8b・b1）

- 対象：docs/math/integer-division.md、snippets/integer-division/（division・multiples・overflow・double-ng の 4 組）、docs/img/integer-division/floor-ceil.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/integer-division.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page integer-division`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/integer-division`（4 片・コンパイル 4 回・期待と違う 0）、`npx textlint docs/math/integer-division.md`（0 errors・22 warnings。執筆者の報告のとおり、重なった助詞と文の長さ）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- 4 片を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で作り直し、cases の入力で動かした。警告なし・サニタイザの報告なし。cases の期待出力は手で計算し直して一致（multiples の $[-10, -1]$ の 3 の倍数 3 個・$-7$ 以上で 3 で割って 2 余る最小は $-7$、overflow の `4 6 10` で積 240・lcm 60、$10^9 \times (10^9 + 1)$ が上限を超えることなど）。なお division.cpp の main は $a = $ `LLONG_MIN` を入れると検査の式 `a - r` があふれるが、cases にない入力で、取り込み範囲（core）の外なので指摘にしない
- 自分で導かれた主張を、作業用の場所の chk.py で無作為に確かめた（$\lvert a \rvert \le 60$、$1 \le \lvert b \rvert \le 9$ で 20 万回）：
    - floor_div・ceil_div が数学の floor・ceil と一致（$b$ が負の場合も含む）
    - 閉区間の個数 $\lfloor R/K \rfloor - \lfloor (L-1)/K \rfloor$、半開区間の個数 $\lceil r/K \rceil - \lceil l/K \rceil$ が素朴に数えた値と一致（$L$ が 0 や負でも）
    - $x + ((r - x) \bmod m)$ が $x$ 以上で余り $r$ の最小、$x - ((x - r) \bmod m)$ が $x$ 以下で余り $r$ の最大
    - $b > 0$ なら $ab \le L \iff a \le \lfloor L/b \rfloor$ が $a$・$L$ が負でも成り立つ（floor_div を使った場合）
    - `(a + b - 1) / b` と `(a - 1) / b + 1` は、本文の範囲（$a > -b$・$a \ge 1$）では常に正しい。ただし範囲の外でも割り切れる場合などに正しい値を返すので、「だけ」は言い過ぎ（指摘 1）
- 手で確かめた：$-7 \div 3$（数学で $-3$ 余り $2$、C++ で $-2$ と $-1$）、確認問題の答え（$[0, 10]$ の 3 の倍数 4 個、$-6$ と $9$、`a > L / b` の 2 例）、表の誤る例（$b = 2$・$a = -8$ で $-3$、$a = 0$ で $1$）、例題の $-13 \to -2$・$-20 \to -2$
- 事実：`double` の仮数部 53 bit と $2^{53} \approx 9.007 \times 10^{15}$、$10^{18}$ 付近（$2^{59}$ と $2^{60}$ の間）の `double` の間隔 $2^7 = 128$、$10^{18}$ が 128 の倍数なので $10^{18} - 1$ が $10^{18}$ に丸められること（double-ng の実行でも 1 ずれる）、`__int128` の上限 $2^{127} - 1 \approx 1.7 \times 10^{38}$、`LLONG_MIN / -1` があふれること、C++ の `/` が 0 の向きに切り捨て `(a/b)*b + a%b == a` であること（en.cppreference.com の Arithmetic operators）は正しい
- 計算量：要点・front matter の complexity・本文（どれも $O(1)$、lcm は gcd の $O(\log \min(a, b))$）は一致
- 参照先の節：cpp-math-functions#integer-division、cpp-integer-overflow の #signed-overflow-ub・#int-product・#overflow-check・#int128、periodicity#periodic-patterns は見出しがある。#int128 の節は入出力を扱っていない（指摘 4）
- 問題：`python3 tools/ap.py` は問題 ID を直接取らない（`show` などの下位コマンド）が、check_pages が台帳との一致を見てエラー 0。参考の URL を取得して確かめた：nagi0724（題名一致。割り切れず負なら 1 引く場合分け）、fjnkt98（題名一致。負なら符号を反転して切り上げる別の書き方だが、例題の裏付けとして食い違いはない）、E869120 038.cpp（`C = A / gcd`・`B <= 10^18 / C` で事前に判定、超えたら Large。本文の方針と一致）、zenn asamichiruko（題名「ABC 432 C 問題の解き方と説明」、大きい飴の個数の合計の最大値、共通部分の最大を選ぶ）、drken の abc432_c（下記）
- 執筆者の未解決の点：
    - **abc432_c の問いの向き**：drken の記事は問題概要で「最小値」と書くが、解法の本文も AC コードも最大の $P$ を選んで総和を出しており、概要の書き誤りと見られる。zenn asamichiruko は最大値。AC のコードが最大を出すので、本文の「最大値」でよい。また本文の方針「$P$ は $Y \min A_i$」は、drken の「$Y \min A_i$ 以下で $D$ で割って $r$ 余る最大」と同じ値になる（$Y \equiv X \pmod{Y - X}$ なので $Y \min A_i$ 自体が余り $r$ を持つ）ことを確かめた。台帳への提案（summary・approach・evidence の追加）に賛成。checked に 2026-10-21 を入れる提案も添える
    - **X・Y を「値」とぼかした点**：drken は単価（円）、zenn は重さ。「値」でも問いは分かるが、指摘 6
    - **図の表示**：Windows 側の Chrome をヘッドレスで動かし（`--headless=new --screenshot`、幅 1280px、ライト）、SVG を画像にして目で見た。文字の重なり・はみ出しはない。背景は白で塗られ、`viewBox` あり、文字はテキストのまま（`font-family="sans-serif"`）。値（$-7$ の floor $-9$・ceil $-6$・余り 2、$7$ の floor $6$・ceil $9$・余り 1）は本文・代替テキストと一致。気になった点は指摘 5
- 文章の近さ（F8）：参考の記事の例（$X = -13$ などの数値）と同じ数値・言い回しの段落は見当たらない

## 指摘

### 1｜直すべき｜fact（F2）｜#ceil-formula の 2 段落目の最後「C++ の `/` がこの floor と一致するのは、割られる数 $a + b - 1$ が 0 以上のときだけである。」と、#pitfalls の「`(a + b - 1) / b` は $a \le -b$ で…誤る」

- **問題**：「だけ」が誤り。割られる数が負でも、割り切れるときは C++ の `/` と floor は一致する。そのため `(a + b - 1) / b` は $a \le -b$ でも正しい値を返すことがあり（$b = 1$ なら常に正しい）、落とし穴の「$a \le -b$ で誤る」も「必ず誤る」と読める。同じく `(a - 1) / b + 1` も $a \le 0$ で正しいことがある（$a = -1$・$b = 2$ で $0$）
- **根拠**：反例。$a = -5$・$b = 3$ で $a + b - 1 = -3$、C++ の `-3 / 3` は $-1$ で $\lceil -5/3 \rceil = -1$ と一致する。chk.py で、$a > -b$ の外で正しい値を返す組が 160 組あった（$b = 1$ の全部と、$a + b - 1$ が $b$ で割り切れる組）
- **直し方**：「C++ の `/` は、割られる数が 0 以上なら floor と一致する。負だと、割り切れないときに floor より 1 大きくなる」に直す。表の見出しは「必ず正しい範囲」とし、落とし穴は「$a \le -b$ で誤ることがある」「$a = 0$ などで誤る」とする

### 2｜直すとよい｜clarity（U3）・fact（F2）｜#count-multiples の 1 段落目

- **問題**：「$R$ 以下の倍数の個数」から「$L - 1$ 以下の倍数の個数」を引く、と述べた直後に「0 や負の倍数も数えるとき」と続く。負の倍数まで数えると「$R$ 以下の倍数」は無限個なので、個数の引き算としては読めない。本文はその後で「$j$ の範囲の長さ」に言い換えているが、2 つの説明のつながりが分かりにくい
- **根拠**：$K = 3$ なら $3$ 以下の 3 の倍数は $3, 0, -3, -6, \dots$ と無限にある
- **直し方**：「$Kj \in [L, R]$ となる整数 $j$ は $\lceil L/K \rceil \le j \le \lfloor R/K \rfloor$ で、$\lceil L/K \rceil = \lfloor (L-1)/K \rfloor + 1$ なので個数は…」のように $j$ の範囲から直接導くか、「$L, R \ge 0$ なら $R$ 以下の 0 以上の倍数の個数…、負を含めても $j$ の範囲の長さとして同じ式になる」と順を立てる

### 3｜直すとよい｜clarity（U4）・fact（F2）｜#overflow の最後の段落「$b < 0$ なら両辺を $-1$ 倍して $b > 0$ の形に直してから使う」

- **問題**：不等式 $ab \le L$ の両辺を $-1$ 倍すると $a(-b) \ge -L$ と不等号が逆向きになり、本文の $\le$ の形には戻らない。何を $-1$ 倍するのかが読み取れない
- **根拠**：$ab = (-a)(-b)$ なので、$a$ と $b$ の符号を両方反転すれば $(-a)(-b) \le L$（$-b > 0$）となり本文の形に入る。ただし $a$ か $b$ が `LLONG_MIN` だと反転があふれる
- **直し方**：「$b < 0$ なら $ab = (-a)(-b)$ と書き直し、$-a \le \lfloor L/(-b) \rfloor$ で判定する」とする。あるいは「積が負になりうる場合は `__int128` で掛けて比べるのが簡単」と逃げ方を示す

### 4｜直すとよい｜fact（F7）｜#overflow の「__int128 に逃げる」の項目「入出力ができないなどの注意は [__int128](../cpp/cpp-integer-overflow.md#int128) にある」

- **問題**：#int128 の節は値の範囲・積の書き方・リテラルがないことを扱い、入出力は別の節 #int128-io（`__int128 の入出力：cout << も cin >> もできない…`）にある
- **直し方**：リンク先を `../cpp/cpp-integer-overflow.md#int128-io` にするか、「注意は [__int128](…#int128) と [__int128 の入出力](…#int128-io) にある」と 2 つ挙げる

### 5｜直すとよい｜figure（G5・G3）｜floor-ceil.svg

- **問題**：
    - 線の種類の約束がそろっていない。左（$a = -7$）は「floor（実線）」「ceil・C++ の /（破線）」と書き、線の種類が意味を持つように見えるが、右（$a = 7$）は ceil も floor・C++ の / も実線で、注記もない。読者は「破線＝C++ の /」なのか「破線＝ceil」なのか迷う
    - 灰色の点線の補助線（x = 110 と x = 530、y = 58〜94）が、「floor（実線）：−9、q = −3」と「floor・C++ の /：6、q = 2」の文字の行を縦に横切る（画像で見ると細く薄いので読めなくはない）
    - viewBox の幅 640 に対し下の q のラベルは 11px なので、幅 390px の画面では約 7px になり読みにくい
- **確かめた結果**：Windows 側の Chrome をヘッドレスで動かし、幅 1280px・ライトで画像にして目で見た（作業用の場所の shot.png）。ダークでも背景が白で塗られているので読める
- **直し方**：「C++ の / が返す側」を破線で示す、と約束を 1 つに決め、右の「floor・C++ の /」の矢印を実線と破線の重ね（または注記「C++ の / も同じ」）にし、左右とも注記の「（実線）（破線）」をその約束に合わせる。補助線は文字の行の手前（y ≤ 76 と y ≥ 96）で切る。q のラベルは 12〜13px に上げる

### 6｜直すとよい｜fact（F5）｜#practice の ABC432 C の行「2 種類の飴（値 X と Y、X < Y）」

- **問題**：「値」が値段なのか重さなのか分からず、「全員の合計」が何の合計かも読み取りにくい
- **根拠**：drken の記事は単価（円）、zenn asamichiruko は重さとして扱っている。どちらでも「1 個あたりの量 X と Y の合計をそろえる」という構造は同じ
- **直し方**：「1 個あたりの重さが X と Y（X < Y）の 2 種類の飴を…全員の重さの合計をそろえるとき」のように量を明示する（台帳の summary の提案もそろえる）。問題文を確かめられないので、メインのセッションで向き（重さか値段か）を決めてよい

## 台帳への提案（検証役から）

- abc432_c：執筆者の提案（summary・approach・evidence に zenn asamichiruko を足す）に賛成し、checked を 2026-10-21 にする。問いの向き（最大値）は drken の解法と AC コード、zenn の記事で確かめた
- abc239_b・typical90_al：参考の記事で例題・方針を確かめたので、checked を 2026-10-21 にしてよい

## 総合の判定

**小さな直しで可**。直すべき 1 件（切り上げの式が使える条件の「だけ」の言い過ぎ）、直すとよい 5 件。コード片 4 組はコンパイル・実行・サニタイザとも問題なく、本文の主張（floor_div・ceil_div・safe_mod、区間の倍数の個数、余りをそろえる最小の数、割り算によるあふれの判定、double の誤差）は計算と無作為の確かめで正しかった。
