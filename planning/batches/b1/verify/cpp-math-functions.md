# cpp-math-functions の検証（工程8b・バッチ b1）

- 対象：docs/cpp/cpp-math-functions.md、snippets/cpp-math-functions/ の 16 組、docs/img/cpp-math-functions/{bit-count,division}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page cpp-math-functions -v`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-math-functions`：16 片・コンパイル 32 回・期待と違う 0
- `npx textlint docs/cpp/cpp-math-functions.md`：エラー 0・警告 0
- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- `.venv/bin/mkdocs build -d <一時置き場>/site`（ほかのページの anchor の警告だけで、このページの警告はなし）。出力の HTML を grep で確かめた
- compile-error の 4 片を g++-15 で個別にコンパイルし、エラーの文面が本文の理由と一致することを確かめた：bitset-ng は `the value of 'n' is not usable in a constant expression`、popcount-int-ng は `no matching function for call to 'popcount(int&)'`、clamp-ng は `no matching function for call to 'clamp(long long int&, int, long long int&)'`、gcd-ng は `no matching function for call to '__gcd(int, long long int)'`
- 本文の主張を小さなプログラムで確かめた（g++-13・g++-15、`-std=gnu++23 -O2`）：`lcm(100003, 100019)`（int）= 1412265465、`-D_GLIBCXX_ASSERTIONS` で `Assertion '!__overflow' failed`、`__gcd(12, -18)` = −6、`bit_ceil(4294967295u)` = 1、`midpoint(-3, 0)` = −2・`midpoint(0, -3)` = −1・`midpoint(2147483647, 2147483645)` = 2147483646、`RAND_MAX` = 2147483647、`__builtin_ctz(0)` = 32、`__builtin_popcount((1LL << 40) + 1)` = 1 で `-Wall -Wextra` の警告なし（`-Wconversion` を足すと警告が出る）、`(long long)pow(3, 35)` = 50031545098999704、`(long long)sqrt(10^18 − 1)` = 10^9、M_PI は `-std=c++23` でも通る、`random_shuffle` は `-Wdeprecated-declarations` の警告
- libstdc++ の `std::lcm` が先に割ること：/usr/include/c++/15/numeric の 205 行 `__r = __m2 / __gcd(...)`、209 行 `return __r * __n2` で確かめた
- sqrtl の境界：0 以上 2^64 未満の乱数 2×10^7 個と、r² − 1・r²・r² + 2r（r は 2^32 未満の多数の値）で `(unsigned long long)sqrtl(x)` が正しい床になるかを `unsigned __int128` で確かめ、誤りは 0 件（指摘 3）
- 出典：cppreference（lcm・midpoint・bit_ceil・uniform_int_distribution とその構築子・RAND_MAX）、cpprefjp（clamp・numbers・bit）、GCC の Bit Operation Builtins を curl で取得し、題名と該当の文を確かめた（lcm の「表せないと未定義」、clamp の事前条件、uniform_int_distribution の閉区間と構築子の「a > b なら未定義」、ctz・clz の「0 なら未定義」）。どれも付録 B のドメイン
- 図：chrome-headless-shell 146（puppeteer のもの）で SVG を幅 1280px（2 倍）と幅 358px（2 倍密度）で画像にした（一時置き場の bit-count-full.png・bit-count-narrow.png・division-full.png・division-narrow.png）。この環境には日本語のフォントがなく和文は豆腐になったので、和文の字幅は確かめていない。背景は白で塗られており、ダークモードでも白地の図として読める

## 指摘

### 1｜直すべき｜分かりやすさ・記法（F7・U6）｜#bit-functions の見出し、参考の 2 行

- **問題**：見出し `## <bit> の関数：…` の `<bit>` が HTML の生のタグとして出力され、ブラウザでは消える。本文の見出しは「 の関数：popcount・…」になり、目次（右の nav）でも「の関数：popcount・…」と先頭が欠ける。参考の `[cpprefjp「<numbers>」]`・`[cpprefjp「<bit>」]` も同じで、リンクの文字が「cpprefjp「」」になる
- **根拠**：mkdocs build の出力 site/cpp/cpp-math-functions/index.html に `<h2 id="bit-functions"><bit> の関数：…` と、`<a href="https://cpprefjp.github.io/reference/numbers.html">cpprefjp「<numbers>」</a>`・`…bit.html">cpprefjp「<bit>」</a>` がそのまま入っている。目次の `md-nav__link` の中身は「の関数：popcount・…」だった。本文の `` `<bit>` `` のようにバッククォートで囲んだ箇所は `&lt;bit&gt;` になっていて問題ない
- **直し方**：見出しと front matter の sections の title を `` `<bit>` の関数：… `` にする（バッククォートを含む見出しは cpp-integer-overflow・cpp-macros-template-file に前例がある。title を変えるのでメインの了承が要る。anchor は変えない）。参考の 2 行は `` cpprefjp「`<numbers>`」 ``・`` cpprefjp「`<bit>`」 `` にする。front matter の complexity の `<bit>`・`bitset<N>` も、gen_site の出力先（一覧・llms.txt）で Markdown として扱われるならバッククォートで囲むとよい

### 2｜直すべき｜図（G5）｜division.svg、−4 の目盛り

- **問題**：破線の矢印（floor の向き）の矢じりが、目盛りのラベル「−4」の「−」の上に重なり、「−4」が「4」のように見える。この図でいちばん大事な値である
- **根拠**：等倍と幅 358px の画像で確認した。下の弧 `M145 128 Q132.5 165 119 128` が y = 128〜146 を通り、目盛りのラベル（y = 142 が基線）の帯と同じ高さにある。矢じりの先は (119, 128) で、「−4」のラベルは x = 120 を中心にしている
- **直し方**：下の弧を目盛りのラベルより下に回す（例えば始点・終点を y = 150 付近にして、点と目盛りへは短い縦線でつなぐ）か、上の弧と同じく数直線の上に描いて線種だけで区別する。あわせて、2 つの赤い点に「−3.5」「3.5」のラベルを付けると、代替テキストと図が対応する

### 3｜直すとよい｜事実（F2）｜#pow-sqrt の「sqrtl」の行

- **問題**：「ただし $2^{64}$ 近くまで常に正しいとは限らない」とあるが、AtCoder・手元の x86-64 の GCC では、0 以上 $2^{64}$ 未満のすべての整数で `(unsigned long long)sqrtl(x)` が正しい床になる。執筆者も具体例は確かめていないと報告している。読者は「x86-64 でも誤る例がある」と受け取る
- **根拠**：(a) 計算：long double は仮数部 64 bit なので $x < 2^{64}$ は正確に表せる。$x = r^2 - 1$（$r < 2^{32}$）の平方根は $r$ より $\frac{1}{2r} > 2^{-33}$ 以上小さく、$[2^{31}, 2^{32})$ の数の間隔の半分 $2^{-33}$ より大きく離れるので、正しく丸めれば $r$ 未満になる（x87 の fsqrt は正しく丸める）。(b) 乱数 2×10^7 個と境界の値（r² − 1・r²・r² + 2r）で誤り 0 件
- **直し方**：「x86-64 の GCC（AtCoder）では $2^{64}$ 未満で正しい床が出るが、long double が double と同じ処理系（MSVC など）では `sqrt` と同じく誤る。どの環境でも同じコードで正しくするには補正を書く」のように、補正を勧める理由を移植性と `sqrt` を使う場合に置き換える。言い切りに自信が持てないなら、この 1 文を消して「補正の仕方は integer-root のページ」だけにしてもよい

### 4｜直すとよい｜事実（F2）｜#gcd-lcm の落とし穴 1

- **問題**：`int` 同士の `lcm` があふれる例で「本当の値が入らない」「1412265465 と出た」と書くが、規格ではこれは未定義動作である。読者は「値がずれるだけ」と受け取りうる
- **根拠**：cppreference「std::lcm」：「The behavior is undefined if |m|, |n|, or the least common multiple of |m| and |n| is not representable as a value of type std::common_type_t<M, N>」（参考に挙げた URL）
- **直し方**：「結果がその型で表せないときは未定義動作で、手元では … と出た」とし、[未定義動作](../cpp/cpp-undefined-behavior.md) へリンクする

### 5｜直すとよい｜事実（F2）｜#gcd-lcm の「素朴に書くと」

- **問題**：「ユークリッドの互除法 `b == 0 ? a : gcd(b, a % b)` と同じである」とあるが、負の数では同じでない。素朴な互除法は `gcd(12, -18)` で −6 を返し、`std::gcd` は 6 を返す。同じ節で「負の数は絶対値で計算する」と書いているのと食い違う
- **根拠**：手元で素朴な再帰が `(12, -18)` → −6、`(-12, 18)` → 6、`std::gcd(12, -18)` → 6
- **直し方**：「0 以上の引数では、ユークリッドの互除法 … と同じである」とする。落とし穴 3 の `__gcd` が負の値を返す理由（中身が素朴な互除法）とも結び付く

### 6｜直すとよい｜記法（F7）｜#integer-division の表、3 行目

- **問題**：表の見出しが「数学の $\lfloor a / b \rfloor$ と $a \bmod b$」で、`7 % -2` の行に $a \bmod b = -1$ と書いている。リンク先の [整数の割り算と余り](../math/integer-division.md) は「$a \bmod m$ は 0 以上 $m$ 未満の余り」と定義しており（54 行）、法が負のときの $\bmod$ はその定義の外である。床関数に合わせた余り $a - b\lfloor a/b \rfloor$ のことなら、そう書かないと読者は「mod は −1 になることがある」と取り違える
- **根拠**：docs/math/integer-division.md 54 行。$7 - (-2) \cdot \lfloor 7/(-2) \rfloor = 7 - 8 = -1$
- **直し方**：表の見出しの 3 列目を「数学の $\lfloor a / b \rfloor$ と $a - b \lfloor a / b \rfloor$」にするか、3 行目の余りを「—」にして「除数が負の場合は競プロではまれ」と添える

### 7｜直すとよい｜記法（F7）｜#pow-sqrt の 1 段落目のリンク

- **問題**：「[浮動小数点数の型](../cpp/cpp-types-literals.md)」がページの先頭に飛ぶ。cpp-types-literals は draft で、`floating-point` の節（「double が整数を正確に表せるのは 2^53 まで、x86-64 の long double は仮数部 64bit」）がある
- **根拠**：docs/cpp/cpp-types-literals.md の sections と 193 行
- **直し方**：`../cpp/cpp-types-literals.md#floating-point` にする。sqrtl の行の「仮数部 64 bit」にも同じリンクを付けてよい

### 8｜直すとよい｜事実（F2・F9）｜#random の落とし穴 1

- **問題**：「32767 の処理系もある」は執筆者の記憶に基づき、出典がない
- **根拠**：cppreference「RAND_MAX」（https://en.cppreference.com/cpp/numeric/random/RAND_MAX）に「This value is implementation dependent. It's guaranteed that this value is at least 32767」とある。手元の GCC（glibc）で 2147483647 は確かめた
- **直し方**：「規格は 32767 以上とだけ決めていて（手元の GCC では $2^{31} - 1$）」と書き換え、参考に cppreference「RAND_MAX」を足す。MSVC の名を出すなら Microsoft のドキュメントを出典にする

### 9｜直すとよい｜事実（F2）｜#bit-tricks の `x & -x` の行

- **問題**：「`x` が符号なしなら `1u << countr_zero(x)` とも書ける」は、$x = 0$ では `countr_zero` が 32 になり `1u << 32` が未定義動作になる。`unsigned long long` の `x` では `1u` が 32 bit なので、33 桁目より上の 1 で誤る
- **根拠**：シフト量が型の桁数以上なら未定義動作（同じページの bit_ceil の落とし穴と同じ理由）
- **直し方**：「`x` が 0 でない `unsigned` なら `1u << countr_zero(x)`（`unsigned long long` なら `1ULL << …`）とも書ける」とする

### 10｜直すとよい｜分かりやすさ（U3）｜#bit-tricks の落とし穴

- **問題**：「`for (int s = m; s > 0; …)` は空集合 0 を処理しない。止める条件を書かないと、0 の次に $m$ に戻って回り続ける」の 2 文目は、1 文目の for（止める条件 `s > 0` がある）とは別の書き方の話で、何の「止める条件」かが読み取りにくい
- **根拠**：1 回目に読んだとき、2 文目が `s > 0` を外した場合の話だと気付くまでに引っかかった。`(0 - 1) & m = m` なので戻ることは正しい
- **直し方**：「`s > 0` を条件にすると空集合 0 を処理しない。条件を外すと、`(0 - 1) & m` が $m$ に戻って回り続ける。0 を処理してから `break` する形（上のコード）にする」とする

### 11｜直すとよい｜図（G3）｜bit-count.svg・division.svg

- **問題**：(a) どちらも viewBox の幅が 640 で font-size 13 なので、スマホの幅（表示 358px）では本文の文字が約 7.3px、bit-count の桁の番号（font-size 11）は約 6.2px になり、読むのがつらい。(b) division.svg の「C++ の -7 / 2 は −3」は ASCII のハイフン、ほかのラベルは「−」で、そろっていない。(c) bit-count.svg の「countr_zero = 2」のラベルは、破線の括弧から 40px 下・左に離れていて、線でつながっていない（「破線」と文字で補っているので読めはする）
- **根拠**：幅 358px の画像（一時置き場の bit-count-narrow.png・division-narrow.png）。bit-count の 2 進の 32 マスと括弧・popcount の引き出し線は重なりがなく、値（28・4・2・2、桁の番号 31・3・2・1・0）は本文の表と一致した
- **直し方**：(a) division.svg は数直線の範囲を −5〜5 から −5〜4 程度に縮めて viewBox を 480 前後にするか font-size を 16 にする。bit-count.svg は 32 マスの横幅が要るので、桁の番号と説明のラベルの font-size を上げ、図の下の空き（y = 180〜200）を詰める程度でよい。(b) 「C++ の −7 / 2 は −3」にそろえる（コードとしての `-7 / 2` を示したいなら等幅の書体にする）。(c) countr_zero のラベルを括弧の直下（y = 152 付近、右寄せ）に移し、popcount のラベルをその下にする

### 12｜直すとよい｜分かりやすさ（U9）｜見出しの長さ（執筆者の手引きへの提案に同意）

- **問題**：#builtins の見出しは 100 字を超え、#integer-division・#pow-sqrt も 80 字前後ある。目次（右の nav）では折り返して数行になる
- **根拠**：手引き §13.2（見出しと title を同じにする）による。執筆者も手引きへの提案で挙げている
- **直し方**：メインの判断に任せる。短くするなら、括弧の中（「ctz・clz・__lg に 0 を渡すと未定義…」など）を節の 1 文目に移す

### 13｜直すとよい（任意）｜事実（F2）｜#random の落とし穴 2（執筆者の未解決の点 2）

- **問題**：「種を固定すると毎回同じ列になる」は、エンジン（`mt19937_64`）の列については規格で決まっていて正しい。一方、`uniform_int_distribution`・`shuffle` の結果は分布の計算方法が規格で決まっていないので、同じ種でも標準ライブラリ（libstdc++ と MSVC など）が違えば変わりうる。手元で再現した失敗を別の環境で再現できない原因になる
- **根拠**：規格 [rand.predef] は `mt19937_64` の 10000 回目の値（9981545732273789042）を定めているが、[rand.dist] は分布の計算方法を定めていない（記憶による。cppreference の各分布のページにも計算方法の記述はない）
- **直し方**：書くなら落とし穴 2 に「同じ種で同じ列になるのはエンジンの値で、分布を通した値は標準ライブラリが違うと変わりうる」と 1 文足す。書かなくても誤りではないので任意

## 執筆者の未解決の点への回答

- 図の文字の重なり：bit-count.svg は重なりなし。division.svg は破線の矢じりが「−4」に重なる（指摘 2）
- 分布の計算方法：指摘 13（任意）
- RAND_MAX が 32767 の処理系：cppreference で「32767 以上」と確かめられる。書き方を指摘 8 のとおりにすると記憶に頼らずに済む
- `__builtin_ctz(0)` が 32：手元でも 32、`__lg(0)` は −1 だった。本文の「たまたま」の書き方でよい
- sqrtl：x86-64 の GCC では $2^{64}$ 未満で常に正しかった（指摘 3）

## そのほか確かめて問題がなかった点

- 要点の計算量・front matter の complexity・本文が一致（F1）。front matter は complexity・stage・updated と sections の gcd-lcm の title だけが変わっていて、title の変更は報告に理由がある（F10）。cpp_std・gcc_min が null なのは、版の違う機能を並べるページで、ほかの cpp のページにも前例がある
- 表の値（x = 12 と x = 0 の popcount・countr_zero・countl_zero・bit_width・bit_ceil・bit_floor）は bit-functions の cases と一致。組み込み関数の表の「0 を渡したとき」は GCC のドキュメントと一致（`__lg` は libstdc++ で `__builtin_clz` を使うので未定義）
- $3^{35} = 50031545098999707$、double の間隔は $2^{55}$ 以上 $2^{56}$ 未満で 8 なので近い表せる値は …704（「近くの偶数」は正しいが「8 の倍数」の方が正確。直さなくてよい）
- `(a + b - 1) / b` の反例（$a = -8$, $b = 2$ で −3、正しくは −4）、`midpoint` の丸めと二分探索の停止の議論、`clamp` の型と $lo > hi$ の事前条件（cpprefjp「事前条件 low の値は high の値より大きくなってはならない」）、`bitset` の `_Find_first` が 1 がないとき $N$ を返すこととコードの `s <= MAXS`（= `s < N`）、$10^8 / 8$ バイト ≈ 12 MB、`b.test(i)` の例外
- コード片は手引き §9 に沿う（`bits/stdc++.h`・`using namespace std;`、マクロ・型の別名なし、`'\n'`）。chrono の `elapsed_ms` のラムダは手引きの例（比較関数・DFS・判定の関数）の外だが、経過時間を返す小さな関数で読みやすさを損なわないので指摘しない
- 確認問題 4 問は本文から答えられ、理由も書かれている（U8）

## 総合の判定

小さな直しで可。直すべき 2 件（`<bit>` の見出しと参考のリンクの文字が消える、division.svg の矢じりが「−4」に重なる）、直すとよい 11 件。事実の誤りに当たるものはなく、直すとよいのうち 3・4・5・6・9 は事実の言い方を正確にするもの。
