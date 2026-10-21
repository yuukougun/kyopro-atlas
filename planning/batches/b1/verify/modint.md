# modint の検証（工程8b・b1）

- 対象：docs/math/modint.md、snippets/modint/（conversion・dynamic・self-made の 3 組）。図はなし（catalog の visual は null で、figure.md の観点は該当なし）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/modint.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page modint`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/modint`（3 片・コンパイル 3 回・期待と違う 0）、`npx textlint docs/math/modint.md`（0 errors・7 warnings。要点の計算量の行・練習の要約・折りたたみの長い行の助詞の重複と文の長さで、執筆者の報告どおり）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- ACL v1.6 のドキュメント（document_ja/modint.md）とソース（modint.hpp・internal_math.hpp）と照らした：
    - set_mod の制約 $1 \le m \le 2 \times 10^9 + 1000$、`modint` は `dynamic_modint<-1>` の別名、複数の法は `dynamic_modint<0>`・`dynamic_modint<1>`、`modint998244353` は `static_modint<998244353>` の別名、raw に法以上を入れたときは未定義（ドキュメント 231 行）
    - dynamic_modint の既定の法は 998244353（modint.hpp 250 行 `bt(998244353)`）
    - static_modint の inv は `internal::is_prime<m>` で分岐し、素数なら `assert(_v)` の後に `pow(umod() - 2)`、そうでなければ `inv_gcd` と `assert(eg.first == 1)`。dynamic_modint はいつも `inv_gcd`
    - Barrett 還元：`im = (unsigned long long)(-1) / m + 1`（$= \lceil 2^{64}/m \rceil$）、`x = (z * im) >> 64` は商か商 + 1（ソースのコメント [2]）、`z < y` なら $m$ を足し戻す。本文の説明と一致
    - 計算量：要点・front matter の complexity・ドキュメント（inv と割り算 $O(\log \mathrm{mod})$、pow $O(\log n)$）は一致
- 自分で動かして確かめた（作業用の場所 v-modint/t.cpp、g++-15 `-std=gnu++23 -O2`）：
    - `set_mod` なしの `modint::mod()` は 998244353
    - 確認問題 1：$a = b = c = 10^{18}$ で `(mint(a) + b) * c` と `mint(a + b) * c` はどちらも 866082298 で、`__int128` で計算した値と一致
    - `set_mod(1)` の後の `modint(12345).val()` は 0
    - 法 $10^9$ で `modint(10) / 3` は 666666670（3 倍すると 10）、`modint(10) / 4` は `Assertion 'eg.first == 1' failed.` で止まる（確認問題 3 の答えどおり）
    - `mint z = 998244354` の `z.val()` は 1（元の値は偶数）。指摘 1 の根拠
- 練習の方針：ABC357 D の「$d \le 19$ で $10^d - 1$ は 998244353 の倍数にならない」を Python で $d = 1 \sim 19$ について計算し、倍数になるものはなかった（執筆者の未解決の点 2 つ目は確認済み）。式 $N \cdot \frac{r^N - 1}{r - 1}$ は drken の記事の方針と合う。ABC281 G は drken の記事（evidence）で、法 $M$ を入力から読み二項係数をパスカルの三角形で作ること、層ごとの DP であることを確かめた
- 参考の URL：noshi91・drken 2 本は `tools/check_noai.py` で指定なし、題名は本文のとおり。atcoder.jp・codeforces.com の URL は参考に入っていない（練習の問題リンクは囲みの中で、check_pages が通る）
- リンク先の節：rational-mod#no-compare・binomial-precompute#composite-mod・acl-reading#modint はある
- コード片：3 つとも手引き §9 の書き方（`bits/stdc++.h`・`using namespace std;`・`'\n'`、マクロなし。`using mint = …` は §9 で許されている形、`atcoder::modint` は執筆者が手引きへの提案に挙げた）。self-made の加減は $M < 2^{31}$ で $v + w < 2^{32}$、掛け算は 64bit で $< 2^{62}$ で、あふれない。self-made の main は ACL と比べる `assert` を持ち、負の値・0・法と等しい値・$10^{18}$ を cases に含む（本文 #self-made の最後の段落どおり）
- 出典に近すぎないか（F8）：self-made のコードは noshi91 の記事と同じ趣旨（法をテンプレート引数にする・加減は条件分岐）だが、型・関数の分け方・コメントは別で、ありふれた形の範囲。本文の文章も記事の言い回しではない

## 指摘

### 1｜直すべき｜fact（F2）｜#pitfalls の「`val()` を元の値として使う」の段落（本文 87 行付近）

- **問題**：「`val()` を使うのは出力と、余りそのものに意味がある計算（$\bmod 2$ の偶奇を別に求めるなど）だけにする」は、括弧の例が「余りそのものに意味がある計算」の例として読め、「`x.val() % 2` で偶奇が分かる」と取れる。しかし法が奇数なら `val()` の偶奇と元の値の偶奇は関係しない。この段落が戒めている誤りそのものを、正しい使い方の例として挙げている
- **根拠**：`mint z = 998244354;` の `z.val()` は 1（元の値 998244354 は偶数）。作業用の場所で実行して確かめた
- **直し方**：括弧を外すか、正しい例に替える。例：「`val()` を使うのは出力と、余りそのものに意味がある計算（別の法での計算へ値を渡すなど）だけにする。元の値の偶奇のような性質は `val()` からは分からないので、必要なら `bool` や `long long` で別に持つ」

### 2｜直すとよい｜clarity（U2・U3）｜#pitfalls の「掛けてから割り算で戻す」の段落

- **問題**：見出しの太字（掛けてから割り算で戻す）と中身（「割り切れるか」「何で割ったか」を mint の値から判断できない）が結び付きにくく、どんなコードを書くと何が起きるのかが分からない。ほかの 3 つの段落は「こう書くとこう誤る」が具体的なのに、この段落だけ抽象的である
- **直し方**：具体的な誤りの形を 1 つ書く。例：「`mint x = 1; x *= 6; … x /= 3;` のように、掛けた数で割って元に戻すのは、割る数が法と互いに素なら正しい。ただし割る数が $p$ の倍数（$p$ を掛けて $p$ で割るなど）だと、掛けた時点で 0 になり戻せない。$\binom{n}{k}$ を $n!/(k!(n-k)!)$ で求めるのも、$n \ge p$ なら分母が 0 になる」とし、[割り算の条件](#division)へつなぐ。見出しも「掛けた数で割って戻せるとは限らない」などにする

### 3｜直すとよい｜fact（F2）｜#connections の「階乗とその逆元の表」の項

- **問題**：「法は素数でなければならない」だけだと、素数なら常に表が使えると読める。$\mathrm{fact}[i]$ の逆元が要るので、$n < p$ も条件になる（$n \ge p$ なら $n!$ が $p$ の倍数で 0）。#division の最後の段落「割る前に分母が 0 にならないか」とも合わせたい
- **直し方**：「法は素数 $p$ で、$n < p$ でなければならない（$n \ge p$ なら $n!$ が 0 になり逆元がない）」にする。詳しくは二項係数の前計算のページへのリンクで足りる

### 4｜直すとよい｜clarity（U3）｜練習の方針の ABC357 D

- **問題**：「`(r.pow(N) - 1) / (r - 1) * N` を出力する。$N$ は `mint(N)` にしてから掛ける」と書くが、示した式は `* N` で `mint(N)` を書いていない。左が mint なので実際には `N` も mint に直ってから掛かる（#what-is-automatic の説明どおり）が、本文の式と注意が食い違って見える
- **直し方**：式を `(r.pow(N) - 1) / (r - 1) * mint(N)` にするか、注意を「左が mint なので `N` も mint に直ってから掛かる（`N * N` のように `long long` どうしで先に掛けない）」にする。あわせて `.val()` で出力することを添えるとよい

### 5｜直すとよい｜fact（F2）｜#self-made の「コンストラクタで負の数を直す」の項

- **問題**：「C++ の `%` は負の数に負の余りを返す」は、割り切れるとき 0 を返すので「負の数に 0 以下の余りを返す」が正確
- **直し方**：「C++ の `%` は、負の数を割ると 0 以下の余りを返す（$-7 \bmod 3$ は $-1$）ので、`x %= m` の後に負なら $m$ を足す」にする

## 執筆者の未解決の点への答え

- 「static_modint は % が掛け算とシフトに置き換わって速い」：定数での剰余をコンパイラが掛け算とシフトに置き換えるのは一般的な最適化で、static_modint の掛け算は `z % umod()`（umod は constexpr）なので当てはまる。本文は「置き換えられ、速くなる」と定性的に書くだけなので、実測なしでよい
- 「$d \le 19$ で $10^d - 1$ は 998244353 の倍数にならない」：確かめた（倍数になる $d$ はない）
- acl-reading#modint との重なり：本文はリンクで済ませ、「余りから元の値は分からない」側に絞っていて問題ない
- 台帳の abc281_g の alternatives（pages: modint）の summary の「入力の P」：drken の記事でも法は $M$ として読んでおり、提案どおり主の summary にそろえるのがよい。台帳の abc357_d・abc281_g の `checked` に 2026-10-21 を入れてよい（evidence の記事で問題の内容を確かめた）

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 4）。
