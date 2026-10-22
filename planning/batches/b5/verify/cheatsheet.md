# 検証：cheatsheet（早見表）

- 対象：docs/guide/cheatsheet.md（stage: draft、2026-10-22）
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証役：執筆者とは別のエージェント

## 確かめたこと（要約）

- `python3 tools/check_pages.py --page cheatsheet`：エラー 0・警告 0
- 本文の相対リンク（全件）：すべてファイルが実在し、`#anchor` 付きのものは相手のページに `{#anchor}` か sections の anchor があり、stub のページへの節リンクはない（手元のスクリプトで確かめた）
- 数値の再計算（scratchpad の n.py・s.cpp、Python 3 と g++ -O2）：
    - $N = 2 \times 10^5$ の $N\log N \approx 3.52\times10^6$・$N\log^2 N \approx 6.20\times10^7$・$N\sqrt N \approx 8.94\times10^7$
    - 型の境目：$12!$／$20!$、$\binom{33}{16}=1166803110$／$\binom{66}{33}\approx7.22\times10^{18}$、$F_{46}=1836311903$／$F_{92}\approx7.54\times10^{18}$、$2^{53}$・$2^{127}$
    - 2 と 3 の累乗、$\log_2$ の 4 値、ベル数 $B_{10},B_{12},B_{13}$、$\binom{30}{15},\binom{40}{20},\binom{100}{5}$、カタラン数 $C_{10},C_{15},C_{20}$、分割数 $p(10),p(30),p(50),p(100)$
    - $\lfloor N/i\rfloor$ の値の個数（$10^6$ で 1999、$10^{12}$ で 1999999）、$\sum_{d\le 10^6}\lfloor 10^6/d\rfloor = 13970034$
    - メモリ：1024 MiB に `int` 268435456 個・`long long` 134217728 個、$5000^2$ の `long long` は 190.7 MiB
    - 互除法の最大回数（隣り合うフィボナッチ数の組で 42・85）
    - $998244353 = 119\cdot2^{23}+1$、3 が原始根（$p-1$ の素因数 2・7・17 で確かめた）、$2^{-1}=499122177$、$10^9+6 = 2\times500000003$（500000003 は素数）、$(p-1)^2\approx9.96\times10^{17}$、`0x3f3f3f3f`$=1061109567$ でその 2 倍は `int` に収まる
    - 篩（$10^9$ まで、6.6 秒）：$\pi(10^5)=9592$、$\pi(2\times10^5)=17984$、$\pi(10^6)=78498$、$\pi(10^7)=664579$、$\pi(10^8)=5761455$、$\pi(10^9)=50847534$、$10^9$ 以下で始まる隣り合う素数の差の最大は 282（436273009 から）
    - 外積の上界 $2\cdot(2\times10^9)^2 = 8\times10^{18}$、正方形 $[-10^9,10^9]^2$ 内の三角形の面積の最大は正方形の半分なので外積の最大は $4\times10^{18}$
    - `<bit>` の表（`unsigned` の 12 と 0）は値をすべて手で照合
- ACL の計算量：~/lib/ac-library-master/document_ja/ の dsu・fenwicktree・segtree（get・all_prod は $O(1)$）・lazysegtree・scc・twosat・maxflow（$O(n^2m)$、容量 1 で $O((n+m)\sqrt m)$、$O(F(n+m))$）・mincostflow・convolution・string（suffix_array の文字列版・lcp_array・z_algorithm は $O(n)$）・math（pow_mod $O(\log n)$、inv_mod・floor_sum $O(\log m)$、crt $O(n\log\mathrm{lcm})$）・modint と照らし、すべて一致。オラクルが定数時間という仮定の注記もある
- 約数の個数（240・1344・6720・103680）、異なる素因数の個数（primorial で 9 個・15 個）、互除法の回数は divisor-count-bound・gcd-lcm のページと一致
- 参考の URL 4 件：すべて 200 で、題名が書かれたとおり（drken の 2 記事、cppreference「Fundamental types」、ACL の document_ja）。ドメインは付録 B にある。atcoder.jp・codeforces.com の URL はない
- 図・snippets はない（figure.md・code.md は該当なし）。表の中のインラインのコードは C++ の書き方として正しい（`x >> i & 1` の優先順位、`x & 1 == 0` の読まれ方、`min({a, 3LL, b})` の型、`long long INF = 1e18;` など）
- 表の列は最大 4 で、だ・である調。要点・別名の行・導入の順も手引きどおり

## 指摘

### 1．直すべき：N ≤ 20 の行の O(3^N)

- 観点：事実（F3）
- 場所：#complexity-and-constraints の最初の表、2 行目（49 行）
- 問題：「$N \le 15$〜$20$｜$O(2^N N)$、$O(3^N)$」と並べているため、$N = 20$ で $O(3^N)$ が許されると読める。$3^{20} \approx 3.5 \times 10^9$ で間に合わない。行き先の complexity-estimation の表には「（$3^N$ は $N \le 15$ 程度まで）」の条件があるが、早見表で落ちている。同じページの #magnitudes では「$N = 16$ 程度までなら軽い」と書いており、ページの中でも食い違う
- 根拠：$3^{20} = 3486784401$（計算）。docs/basics/complexity-estimation.md 60 行
- 直し方：「$O(2^N N)$、$O(3^N)$（$3^N$ は $N \le 15$〜$16$ 程度まで）」のように条件を足す

### 2．直すとよい：`<bit>` の行の GCC の版

- 観点：事実（F2）
- 場所：#cpp の版の表、1 行目（357 行）
- 問題：「`<bit>`（`popcount` など）｜C++20｜9〜」とある。`popcount`・`countl_zero` などは GCC 9 からあるが、同じページの #bit-tricks で使う `bit_width`・`bit_ceil`・`bit_floor`・`has_single_bit` は GCC 9 では `log2p1`・`ceil2`・`floor2`・`ispow2` という名前で、今の名前になったのは GCC 10（P1956R1）である。表を見て GCC 9 で `bit_ceil` を書くと通らない
- 根拠：libstdc++ の C++20 の対応状況（P1956R1 は GCC 10）。執筆者の未解決の点にある「version-matrix と照らし合わせる」の一部
- 直し方：「9〜（`bit_width`・`bit_ceil`・`bit_floor` は 10〜）」と書くか、行の GCC を 10〜 にする。実害は小さい（読者の手元は g++-13）

### 3．直すとよい：2 つの `contains` が区別しにくい

- 観点：分かりやすさ（U9）
- 場所：#cpp の版の表、1 行目と 4 行目（357・360 行）
- 問題：1 行目の `contains`（`set`・`map` のメンバ関数、C++20）と 4 行目の「`ranges::fold_left`・`contains`」（`ranges::contains`、C++23）が同じ名前で並び、どちらが C++23 か迷う
- 直し方：1 行目を「`set`・`map` の `contains`」、4 行目を「`ranges::fold_left`・`ranges::contains`」と書く

### 4．直すとよい：負の数の % の言い過ぎ

- 観点：事実（F2）
- 場所：#mod の表、「負の数の余り」の行（256 行）
- 問題：「C++ の `%` は負の数に負の値を返す」は、割り切れるとき（`-6 % 3 == 0`）には成り立たない
- 直し方：「割られる数が負なら、余りは 0 か負の値になる」とする

### 5．直すとよい：表の列の中身のずれ

- 観点：分かりやすさ（U9）
- 場所：#stl の「見た目より遅い書き方」の表（211・214・215 行）と「コンテナ」の表（201・202 行）
- 問題：「計算量」の列に、`multiset` の `erase(x)`（すべて消す）・`m[k]`（要素を作る）・`endl`（毎回書き出す）の振る舞いが入り、列の名前と中身が合わない。また「遅い操作」の列の「任意の要素の削除」（`priority_queue`）・「K 番目の取得」（`set`）は遅いのではなく、操作そのものがない（イテレータを進めれば $O(N)$）
- 直し方：表の見出しを「計算量・振る舞い」にするか、2 つ目の表の名前を「見た目と違う書き方」にする。「遅い操作」には「（操作がない）」「（`next` で $O(N)$）」のように添える

### 6．直すとよい：切り上げの式の「だけ」

- 観点：事実（F2）
- 場所：#formulas の「整数」の表、切り上げの行（307 行）
- 問題：「$a + b - 1 \ge 0$ のときだけ正しい」の「だけ」は言い過ぎで、$b = 1$ のときなど $a + b - 1 < 0$ でも正しい場合がある。行き先の integer-division のページは「正しいのは … のとき」（十分条件）と書いている
- 直し方：「$a + b - 1 \ge 0$ なら正しい（負だと誤ることがある）」とする

## 執筆者の未解決の点について

- C++ の版の表：GCC の版を照らした結果、`<bit>` の行（指摘 2）のほかは一致した（`std::format` 13、`views::enumerate`・`zip`・`chunk` 13、`ranges::fold_left`・`ranges::contains`・static な `operator()` 13、`print`・deducing this・`ranges::to` 14、P2718 の寿命の延長と `from_range`・`insert_range`・`append_range` 15）。version-matrix への張り替えはメインの判断でよい
- 素数の差：$10^9$ までの 282 は篩で確かめた。$10^{18}$ までの値を載せない判断は妥当
- 調和級数：$\sum_{d \le 10^6} \lfloor 10^6/d \rfloor = 13970034 \approx 1.4 \times 10^7$ を確かめた。早見表の書き方で正しい

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 5）。
