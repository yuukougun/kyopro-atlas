# exponent-mod の検証（工程8b・b1）

- 対象：docs/math/exponent-mod.md、snippets/exponent-mod/{tower-prime,tower-general}.{cpp,yaml}、docs/img/exponent-mod/powers-mod-7.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page exponent-mod`（エラー 0・警告 0）、`python3 tools/fix_problems.py --check --page exponent-mod`（直すべき行 0）、`python3 tools/check_snippets.py snippets/exponent-mod`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/math/exponent-mod.md`（0 errors・11 warnings。数式を含む文の長さ・読点などで、§13.8 により残してよい）
- front matter：HEAD の版と比べ、執筆者が変えたのは complexity・stage・updated だけ。sections の 4 つの title と本文の見出しが一致する。complexity・要点の計算量・本文（「一般の法」の節の終わり）の 3 か所が一致する
- コード片（作業用の場所 v-exponent-mod/、`-fsanitize=address,undefined` 付き）
    - tower_mod（一般の法）：底 0〜5・高さ 1〜4 で本当の値が求まる塔すべてと法 1〜59 の 81908 通り、さらに底 $10^{18}$ までの高さ 2・3 の塔と法（素数・2 冪・$10^9$・小さい素数の積・乱数）の 2 万通りを、Python の多倍長の直接計算（$0^0 = 1$）と比べてすべて一致。サニタイザの報告なし
    - tower_mod_prime：$p = 2, 3, 5, 7, 11, 13$ で底 $0 \sim 3p - 1$・$b \le 7$・$c \le 4$ の全組と、$p = 998244353, 10^9 + 7$ で底が $p$ の倍数・指数が $p - 1$ の倍数になる組を含む 5000 通りを `pow(a, b**c, p)` と比べてすべて一致。$p = 2$ では `pow_mod(b, c, 1) = 0` になるが、底が奇数なので答え 1 で正しい
    - cases（tower-prime 8 件・tower-general 9 件）の期待出力は上の直接計算と一致。$0^0$・底が $p$ の倍数で指数 0・法 1・底 $10^{18}$ の境界を含む。`main` の assert も中身を確かめている
    - 中間値：cap の掛け算は $v < 2^{31}$、底 $\le 2^{31}$ で積 $< 2^{62}$。指数 $\varphi(m) + (\cdot) < 2 \times 10^9$ は `long long`。`pow_mod` の `int m` に $m \le 10^9$ が収まる
    - 書き方：bits・using namespace std・マクロと型の別名なし・`'\n'`。再帰ラムダは `auto&& self` の形（DFS ではないが手引きの形に合う）。取り込みは core の範囲だけ
- 事実
    - ACL v1.6 の document_ja/math.md：`ll pow_mod(ll x, ll n, int m)`、制約 $0 \le n$・$1 \le m$、$O(\log n)$。third_party の実装で `safe_mod(x, m)` により負の $x$ も扱え、$m = 1$ なら 0、$m \ge 2$ で `pow_mod(0, 0, m) = 1`。modint の `x.pow(ll n)` は $0 \le n$。「ACL では」の囲みと一致
    - $998244352 = 2^{23} \times 7 \times 17$（$2^{23} \times 119$）。本文の数値例（法 7 の 3 と 2 の累乗の列、$2^{10} \equiv 2$、$3^{10^{18}} \equiv 4 \pmod 7$ と誤りの $3$、$2^9 \equiv 8 \pmod{12}$、$2^4 \equiv 4$、$2^{100} \equiv 4 \pmod{12}$）はすべて手で計算し直して正しい
    - 一般化の証明：$\varphi$ の乗法性から $\varphi(p^e) \mid \varphi(m)$、$\varphi(p^e) = p^{e-1}(p-1) \ge 2^{e-1} \ge e$。主張と証明は正しく、上の総当たりとも合う。「素因数の指数の最大値以上で足りる」「$\log_2 m$ 以上」も正しい（執筆者の未解決の点 2：2 通りの書き方は矛盾せず、このままでよい）
    - 止まる理由（$m \ge 3$ で $\varphi(m)$ は偶数、偶数 $m$ で $\varphi(m) \le m/2$）と、$\sqrt{m_j}$ の和が等比級数で $O(\sqrt m)$ になることは正しい
    - Library Checker の Tetration Mod（GitHub の task.md を取得）：$0^0 = 1$、$0 \le A, B \le 10^9$、$1 \le M \le 10^9$、$T \le 1000$。本文・参考の記述と一致（$A \uparrow\uparrow 0 = 1$ は task.md には書かれていないが、本文は「と定める」と自分の約束として書いているのでよい）
- 問題：`python3 tools/ap.py show` で abc228_e（E. Integer Sequence Fair・diff 1579）・abc222_g（G. 222・diff 2242）が台帳・本文と一致。役割（例題 1・練習 1）も台帳どおり。evidence の kazun の解説 2 件を読み、ABC228 E の制約（$N, K, M \le 10^{18}$）・方針（$P - 1$ で割る、$M$ が $P$ の倍数なら $K^N \ge 1$ なので 0、$O(\log N + \log P)$）、ABC222 G の言い換え（$L = 9K$ または $9K/2$、$\gcd(10, L) = 1$ でなければ答えなし、$\varphi(L)$ の約数を小さい順に試す）が本文と一致。台帳の `checked` に 2026-10-21 を入れてよい（abc228_e・abc222_g）
- 参考の URL：drken の Qiita・kazun（228E・222G）を開いて題名・内容が書かれたとおり。ACL・library-checker-problems は GitHub の実物で確かめた。どれも付録 B のドメイン。drken の記事の例（法 7 の掛け算表、法 19 の 3・4 の累乗、$3^{100}$）と本文の例（法 7 の周期の円、$2^{10}$、$3^{10^{18}}$）は別で、証明の筋は教科書どおりの並べ替えで文は違う。近すぎる箇所はない
- 図 powers-mod-7.svg：Windows の Chrome（headless=new、2 倍密度）で画像にして目で見た。値（3：1→3→2→6→4→5、2：1→2→4）・指数のラベル・矢印の向きは本文と代替テキストに一致。背景は白、`viewBox` あり、文字はテキストのまま、点線で「戻る」矢印を区別、はみ出しなし。上付きの表示に崩れがある（指摘 1）
- リンク先：mod-pow・mod-inverse・multiplicative-order・euler-phi・crt・miller-rabin・cpp-integer-overflow・start/notation への相対リンクで、check_pages の警告なし。用語集の `#coprime` はまだない（執筆者の提案どおり足す）
- 執筆者の未解決の点：(1) tower-general は配列で受け取る形のままでよい（本文は Tetration Mod には「上の段だけを扱う形にする」と書いており、そこは指摘 2 で言い方を直す）。自作ライブラリの形はメインが決める。(2) 上のとおり正しい。(3) mod-pow の練習にある ABC228 E から base-multiple へリンクする件は、mod-pow 側の話なのでメインに任せる

## 指摘

### 1｜直すとよい｜図（G5）｜powers-mod-7.svg の 1 の上のラベル「3⁰, 3⁶」「2⁰, 2³」

- **問題**：上付きの後の空の `<tspan dy="6"></tspan>` で基線を戻そうとしているが、文字のない tspan の dy は Chrome で適用されない。そのため「, 3」が上付きの高さのまま描かれ、2 つ目の指数「6」「3」はさらに 6px 上に出て、階段状に崩れる
- **根拠**：Chrome（headless）で画像にして確かめた（作業用の場所 v-exponent-mod/shot.png）。1 つだけの上付き（3¹ など）は後ろに文字がないので崩れない
- **直し方**：基線を戻す dy を次の文字を含む tspan に付ける（例：`3<tspan dy="-6" font-size="10">0</tspan><tspan dy="6">, 3</tspan><tspan dy="-6" font-size="10">6</tspan>`）か、2 つのラベルを別の `<text>` に分ける

### 2｜直すとよい｜fact（F2）・clarity（U3）｜#euler-theorem の最後の段落「塔を配列に展開せず上の O(log m) 段だけを扱えばよい」

- **問題**：(a) 再帰は底 $a_0$（いちばん外側、塔の下）から始まって $O(\log m)$ 段で法が 1 になるので、扱うのは塔の「下の（外側の）」段である。「上の」では向きが逆に読める。(b) 高さを切り詰めるとき、底 $A = 0$ では $0 \uparrow\uparrow B$ が $B$ の偶奇で 1・0 と交互になり（$0^0 = 1$ の約束）、$A = 1$ は常に 1 なので、単に $\min(B, L)$ 段に縮めると $A = 0$ で偶奇が変わって誤る。頭打ちの値も、縮めた塔の上端では本当の値と違うので、$A \ge 2$ でも縮め方に条件が要る
- **根拠**：コード片の solve の再帰の向き（$i = 0$ から $i + 1$ へ）。$0 \uparrow\uparrow 2 = 0^0 = 1$、$0 \uparrow\uparrow 3 = 0^1 = 0$
- **直し方**：「塔の下（外側）から $O(\log m)$ 段だけを扱えばよい」に直し、「$A = 0$ は $B$ の偶奇で 1 か 0、$A = 1$ は 1 と先に分け、$A \ge 2$ なら高さを $\min(B, \text{十分大きな段数})$ に縮めても頭打ちの値が上限に達したままなので答えは変わらない」と 1〜2 文添える

### 3｜直すとよい｜clarity（U4）｜#euler-theorem の「境目の判定」と tower-general の cap の計算

- **問題**：本文は「底が 2 以上なら頭打ちの値は 31 回以内の掛け算で決まる」とだけ書き、コードにある底 0・1 の場合（$1^e = 1$、$0^0 = 1$、$e \ge 1$ なら $0^e = 0$）の説明がない。本文だけで実装すると、底 0・1 で 31 回の打ち切りが効かず指数の回数だけ回る（指数が頭打ちの $2^{31}$ なら約 21 億回）書き方になりうる
- **根拠**：コード片の `if (a[i] <= 1)` の分岐が本文のどこにも対応しない（code.md C3）
- **直し方**：「底が 0 か 1 なら、頭打ちの値は指数が 0 かどうかだけで決まる（底 1 は 1、底 0 は指数 0 なら 1・それ以外 0）」を「境目の判定」の項に 1 文足す

### 4｜直すとよい｜fact（F7）｜冒頭の記法の行「$0^0 = 1$ とする（記法と用語の約束）」

- **問題**：リンク先の docs/start/notation.md（stub）には $0^0$ の約束がなく、約束の出どころがリンク先にあるように読める
- **根拠**：`grep "0\^" docs/start/notation.md` で該当なし
- **直し方**：記法の行の約束はこのページのものとして書き（「このページでは $0^0 = 1$ とする（Library Checker の Tetration Mod と同じ）」）、notation.md へのリンクは文の終わりに別に置く。または notation.md に $0^0 = 1$ の約束を足すことをメインに提案する

### 5｜直すとよい｜fact（F5）・clarity（U7）｜例題の囲みの要約（ABC228 E）

- **問題**：要約に「（M^(K^N)）」と答えの式が入っている。答えの式を立てるのはこの問題の解き方の最初の一歩で、要約は問いだけにする決まり（§2.5）に照らすと言い過ぎ。本文の方針の 1 文目と重なる
- **根拠**：style-guide §2.5、clarity.md U7。要約は台帳の summary（mod-pow 側の alternatives も同じ文）から作られている
- **直し方**：本文だけ直さず（§13.7）、台帳の summary から「（M^(K^N)）」を外すことをメインに提案する

## 総合の判定

小さな直しで可（直すべき 0・直すとよい 5）。定理・証明・数値例・2 つのコード片（総当たり 10 万通り超で一致）・ACL の記述・問題の内容はすべて正しい。直すとよいのは、図の上付きの崩れ、累乗の塔の高さを縮めるときの向きと底 0・1 の扱いの説明、$0^0$ の約束の出どころ、例題の要約の 5 件。
