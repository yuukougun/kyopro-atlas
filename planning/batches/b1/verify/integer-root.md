# 検証：integer-root（整数の平方根・K 乗根と累乗数）

- 対象：`docs/math/integer-root.md`、`snippets/integer-root/`（isqrt・kth-root・perfect-powers・sqrt-ng の .cpp と .yaml）、`docs/img/integer-root/correction.svg`
- 観点：planning/checklists/ の fact・code・clarity・figure
- 日付：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page integer-root`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/integer-root`：4 本・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `python3 tools/fix_problems.py --page integer-root --check`：直すべき行 0
- `npx textlint docs/math/integer-root.md`：エラー 0・警告 4（max-comma 2・sentence-length 2。執筆者の報告どおりで、数式の中の読点と数式を含む長い文）
- 4 本を `-fsanitize=address,undefined` 付きでコンパイルし、cases と境界（`isqrt(LLONG_MAX)`・`kth_root(LLONG_MAX, 1)`・`kth_root(LLONG_MAX, 64)`・`count_perfect_powers(LLONG_MAX)`）を実行：サニタイザの報告なし。`count_perfect_powers(2^63−1) = 3039102893` を Python のメビウス関数による数え方（$1 - \sum_k \mu(k)(\lfloor N^{1/k} \rfloor - 1)$）と比べて一致。$N = 99$ で 12 も一致
- 本文の数値と主張：
    - `(long long)sqrt((double)(r^2-1))` が初めて $r$ になるのは $r = 67108865$（$n \approx 4.5 \times 10^{15}$）：sqrt-ng.cpp の assert で確認
    - $\lfloor \sqrt{2^{63}-1} \rfloor = 3037000499$（Python の `math.isqrt`）、$3037000500^2 > 2^{63}-1$
    - kth_root の判定ループ：$a \ge 2$ なら $a^{i+1} > N$ となる最初の $i \le 62$ で `x > n / a` が真になって返るので、63 回までで止まる。ng $= 3037000500$ で $K \ge 2$ の答えを必ず超える。二分探索の回数 $\lceil \log_2 3037000500 \rceil = 32$
    - perfect-powers のループ条件 `a <= n / a / a` は $a^3 \le N$ と同値（$\lfloor \lfloor N/a \rfloor / a \rfloor = \lfloor N/a^2 \rfloor$）
    - $N = 99$ の例（平方数 9 個、指数 3 以上の列挙 $8, 16, 27, 32, 64, 81$、残り $8, 27, 32$、合計 12）、$2^6 = 4^3 = 8^2$、$2^{15} = 8^5 = 32^3$：手で確認
    - ABC400 C の 2 つの数え方（$\lfloor\sqrt{\lfloor N/2 \rfloor}\rfloor + \lfloor\sqrt{\lfloor N/4 \rfloor}\rfloor$ と、$b$ を奇数に限る和 $\sum_a \lfloor (M+1)/2 \rfloor$）を $N \le 3000$ で、$(a, b)$ を全部作って set で数える素朴な方法と比べ、すべて一致
    - ABC243 G の式 $S_X = \sum_{\alpha=1}^{\lfloor X^{1/4} \rfloor} (\lfloor \sqrt{X} \rfloor - \alpha^2 + 1) S_\alpha$：$S_X = \sum_{y \le \lfloor\sqrt X\rfloor} \sum_{\alpha \le \lfloor\sqrt y\rfloor} S_\alpha$ の和の順を入れ替えると得られ、正しい。$(9 \times 10^{18})^{1/4} \approx 54772.3$
    - compare-sqrt の式変形と「$\sqrt{x} < k \iff x < k^2$」「$\lfloor \sqrt{x} \rfloor \ge k \iff x \ge k^2$」：正しい。$4ab \le 4 \times 10^{18} < 2^{63}$ で収まる
- 問題：5 件（abc400_c・abc193_c・abc361_f・abc243_g と提案の panasonic2020_c）を `tools/ap.py show` で確認。題名・diff は本文と一致。台帳との一致は check_pages で 0 件
- 参考の 6 件を curl で取得し、題名と著者を確かめた（題名の書き方の小さな違いは指摘 6）。drken 氏の ABC361 F の記事は、素数の指数ごとの包除原理と、`sqrtl`・`cbrt`・`pow` で近い値を求めて `while (power(res + 1, K) <= N) ++res` で補正する K 乗根を載せており、本文の参考の説明と合う。`tools/check_noai.py` で at274.hatenablog.com・yuulis.hatenablog.com に noai の指定がないことを確認
- 図：ヘッドレスの Chrome（puppeteer の chrome-headless-shell 146）で SVG を 640×300（2 倍）と幅 390px で画像にした。日本語のフォントが WSL に入っていないので、Windows の NotoSansJP を一時的な fontconfig で読ませて描いた。文字の重なり・はみ出しはない。背景は白、`viewBox` あり、文字はテキスト。値とラベルは本文・コードと一致（補正の順：減らす→増やす）。指摘 2 の 1 点だけ
- 執筆者の未解決の点：
    - 図の表示：上のとおり描いて確かめた。重なりはない。右側の 2 行の順が逆（指摘 2）
    - 「Apple Silicon の macOS では long double が double と同じ 64 bit」：Apple の一次資料「Writing ARM64 code for Apple platforms」（https://developer.apple.com/documentation/xcode/writing-arm64-code-for-apple-platforms 。JSON 版 `developer.apple.com/tutorials/data/documentation/xcode/writing-arm64-code-for-apple-platforms.json` を取得）に「long double は … double 型と同じになる（which makes it identical to the double type）」とあり、正しい。出典は参考に足すとよい（指摘 4）
    - 「pow(n, 1.0/k) のずれは 1 より大きいこともあると考える」：乱数の $N < 2^{63}$・$2 \le K \le 61$ を 300 万組と、$a^K$ と $a^K - 1$（$a \le 3 \times 10^6$）で試したところ、ずれは最大 1 だった。本文は「保証がないのでループで直す」という安全側の書き方で、誤りではない。指摘にしない

## 指摘

1. 重さ：直すべき／観点：fact（F2・F3）／場所：#perfect-powers、コード片の後の段落「平方数の判定には、前の節の正確な `isqrt` を使う。ここを `sqrt` にすると、大きな平方数を「平方数でない」と判定して二重に数える。」
   - 問題：結果を言い切っているが、このコード片の範囲では起きない。
   - 根拠：指数 3 以上の累乗数で $2^{63}-1$ 以下のもの（重複を含めて 2161146 個）をすべて作り、`isqrt` による判定と `s = (long long)sqrt((double)x); s * s == x`（積は `__int128`）の判定を比べた。食い違いは 0 件だった（平方数を「でない」とする誤りも、その逆も 0）。`double s = sqrt(x); s == floor(s)` の書き方でも $10^{18}$ 以下で 0 件。累乗数が平方数のすぐ近くに来るのは小さい値だけなので、誤差が出ない。試したコードは一時置き場の `t.cpp`・`t2.cpp`
   - 直し方：「ここを `sqrt` にすると二重に数える」と言い切るのをやめる。たとえば「平方数の判定も、前の節の正確な `isqrt` で行う。この範囲の累乗数では `sqrt` でもたまたま誤らないが、それを確かめるより `isqrt` を使う方が安全である」とする。または、判定で起きることを書かずに「浮動小数点数の判定に頼らない」とだけ書く

2. 重さ：直すべき／観点：figure（G5）／場所：correction.svg の右上の注記（`y=186` と `y=200` の 2 行、x=560）
   - 問題：上の行が「(r+1)² > N で減らす」、下の行が「推定が r+1 なら」になっていて、上から読むと「(r+1)² > N で減らす／推定が r+1 なら」と順序が逆になる。左側の注記（「推定が r−1 なら r² ≤ N で増やす」）と並べると読み違えやすい
   - 根拠：ヘッドレスの Chrome で描いた画像で確認した
   - 直し方：2 つの `<text>` の y を入れ替える（「推定が r+1 なら」を y=186、「(r+1)² > N で減らす」を y=200）

3. 重さ：直すとよい／観点：code（C3）・clarity（U3）／場所：snippets/integer-root/perfect-powers.cpp の core（`vector<long long> odd;`）
   - 問題：「平方数でない数」を入れる配列の名前が `odd` で、「奇数」と読める。本文は「平方数でないもの」と書いており、変数名とずれる
   - 直し方：`non_square` か `others` にする（コメントはそのまま）

4. 重さ：直すとよい／観点：fact（F9）／場所：#sqrt-correction「補正はやめない」の項と #references
   - 問題：「Apple Silicon の macOS では long double が double と同じ 64 bit」は正しいが、出典がない（執筆者は記憶に基づくと報告）
   - 根拠：Apple「Writing ARM64 code for Apple platforms」に「long double は double 型と同じ」とある
   - 直し方：参考に「Apple「Writing ARM64 code for Apple platforms」：Apple Silicon の macOS では long double が double と同じであること」を足す（developer.apple.com は付録 B にあるか、`tools/check_noai.py` で確かめてから）

5. 重さ：直すとよい／観点：fact（F2）・clarity（U4）／場所：#compare-sqrt「$c - a - b \le 0$ なら、左辺は正なので成り立たない」
   - 問題：$a, b$ が正であるという条件が書かれていないので、「左辺は正」が言えない（$a = 0$ なら左辺は 0）。結論（成り立たない）は $a$ や $b$ が 0 でも正しい
   - 直し方：「$a, b, c$ を正の整数とする」と先に置くか、「左辺は 0 以上なので（$c - a - b < 0$ なら明らか、$= 0$ でも $0 < 0$ は偽）」のように書く。前者が短い

6. 重さ：直すとよい／観点：fact（F9）／場所：#references
   - 問題：記事の題名の書き方が実物と少し違う。torus711 氏の記事は「AtCoder Beginner Contest 400, C : 2^a b^2」、kazun 氏の記事は「AtCoder Beginner Contest 243 G問題 Sqrt」
   - 直し方：実物の題名に合わせる（ほかのページの書き方の慣例が「略した題名」でよいなら直さなくてよい）

7. 重さ：直すとよい／観点：fact（F2）／場所：#sqrt-correction「r が大きいとこの差が double の刻みより小さくなり、r に丸められる」
   - 問題：最も近い値への丸めで $r$ になるのは、差 $\frac{1}{2r}$ が刻みの「半分」より小さくなったときである。$r = 2^{26} + 1$ では刻みは $2^{-26}$、差は約 $2^{-27}$ で、ちょうど半分の境目にあたる
   - 直し方：「double の刻みの半分より小さくなり」とする

8. 重さ：直すとよい（メインへの連絡）／観点：fact（F7）／場所：#perfect-powers の `[累乗数](../guide/glossary.md#perfect-power)`
   - 問題：用語集に `perfect-power` の anchor はまだない（執筆者の提案）。check_pages は通っているが、提案を採らないとリンク先の anchor がない
   - 直し方：メインが用語集の提案を反映する。採らないなら本文のリンクを外す

## 指摘にしなかったこと

- 「毎回の `sqrt` の呼び出しも遅い」（落とし穴）：GCC は `-fno-math-errno` なしでは `sqrt` をループの外へ出せないことがあり、大きくは外れていない
- 練習の方針（ABC193 C・ABC361 F）、力試しの方針（ABC243 G）：計算量は制約に合い、解き方の要点は折りたたみの中にある。要約に手法名は入っていない
- 執筆者の台帳への提案（abc361_f の evidence が包除原理であること）：上の drken 氏の記事の確認と合う。本文は両方の方法を書いており問題ない

## 総合の判定

小さな直しで可（直すべき 2 件：累乗数の節の `sqrt` による二重計上の言い切り、図の右上の 2 行の順）
