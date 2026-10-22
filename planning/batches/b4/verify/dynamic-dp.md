# b4 検証：dynamic-dp

- 対象：docs/dp/dynamic-dp.md、snippets/dynamic-dp/usage.{cpp,yaml}、docs/img/dynamic-dp/segment-tree.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px の PNG にして確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page dynamic-dp`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/dynamic-dp`：期待と違う 0（4 case）
- `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library`：警告なし。ランダムな 300 通り（$N \le 10$、0・1・? の列と 1〜5 回の書き換え）をサニタイザつきで動かし、コード片の中の全探索 `brute` の assert がすべて通った
- 確認問題の主張（`op(a, b)` を $ba$ にしても例題の答えはすべて一致する）：コード片の `op` の引数を入れ替えたものを同じ 300 通りで動かし、全探索の assert が通り、出力も元と一致した。反転で部分列の種類数が変わらない（? の置き換えも反転で 1 対 1 に移る）ので正しい。一次関数 $f_0 = 2x+1$、$f_1 = 3x$ の合成は $6x+3$ と $6x+1$ で、向きの誤りが見える
- 単位行列の注意（0 で埋めた `e()` は、`all_prod` だけを使い $N$ が 2 のべきなら答えに出ない）：`e()` を零行列に替えた版で、$N$ が 2 のべきの 106 通りはすべて正しい答え、それ以外の 194 通りはすべて誤った答えになった。本文のとおり。ACL のヘッダでも `size = bit_ceil(n)`、`all_prod` は `d[1]` を返し、`prod` は `sml = e()`・`smr = e()` から掛け始める
- メモリの見積もり：$\mathrm{bit\_ceil}(2 \times 10^5) = 262144$、ノード $524288$ 個 × 800 バイト ＝ 約 419 MB。本文の「約 5.2 × 10^5 個」「約 420 MB」と一致
- 例題の行列：$(x_0, x_1, 1)$ の横ベクトルで、0 を読むと $x_0 \leftarrow x_0 + x_1 + 1$（0 列目が $(1,1,1)^\top$）、他は恒等。$T_0$・$T_1$・$T_?$ の 3 つとも手で照らして正しい。答えが積の添字 2 の行の 0・1 列の和になるのも正しい
- 木の節：(max,+) の行列 $\begin{pmatrix} g_0 & g_0 \\ g_1 & -\infty \end{pmatrix}$ の積が $f_0(v) = g_0 + \max(f_0(h), f_1(h))$、$f_1(v) = g_1 + f_0(h)$ になること、葉の行列に $(0, -\infty)^\top$ を掛けると $(0, a_v)$ になることを手で確かめた。さらに Python で、ランダムな木（500 通り、$N \le 12$、負の重みも含む）で重い子を先に訪れる DFS の番号を振り、各重いパスの行列を番号の順に掛けて $(0, -\infty)^\top$ に掛けた値が、素朴な木 DP の根の値と一致することを確かめた（重いパスが番号の連続した区間になることも assert した）
- 計算量：要点・front matter の complexity・本文（#what-it-does の $O(S^3 (N + Q \log N))$、#on-trees の $O(S^3 \log^2 N)$）が一致。ACL の document_ja/segtree.md の「オラクル内部の計算量が $O(f(n))$ ならすべて $O(f(n))$ 倍」とも合う
- 例題：`python3 tools/ap.py show abc246_h` → Ex. 01? Queries・diff 2677。台帳の summary と囲みの要約が一致。kmjp 氏の記事（題名「AtCoder ABC #246 : Ex - 01? Queries」）は末尾が 0・1 の数と定数 1 の 3×3 の行列をセグメント木に載せる解法で、本文の方針と同じ。ikatakos 氏の記録（Ex の解法の部分だけ読んだ）は 4 状態（oo・ox・xo・xx）の 4×4 の行列で、積の左右の順に注意する旨がある。#resources の「3×3 と 4×4 の別の状態の取り方」は正しい。台帳の abc246_h の `checked` に 2026-10-22 を入れる執筆者の提案に同意する
- Library Checker：point_set_range_composite の task.md は「$f_p$ を $cx + d$ に差し替え」「$f_{r-1}(\cdots f_l(x))$ を答える」で、本文の要約と $(x, 1) \begin{pmatrix} c & 0 \\ d & 1 \end{pmatrix} = (cx + d, 1)$ の向きは正しい。point_set_tree_path_composite_sum_fixed_root は指摘 3 を参照
- 参考の URL：OI Wiki「动态 DP」（200、HL 分解の重いパスごとの行列のセグメント木、(max,+) の積、洛谷 P4719 の最大重み独立集合）、kmjp・ikatakos（上記）、GitHub の library-checker-problems の 2 つの task.md、ACL の document_ja。atcoder.jp の URL は例題の囲みの問題リンクだけ。本文の文章が出典の言い回しに近い箇所は見当たらない（F8）
- リンクの anchor：matrix-power#write-as-matrix・#fast-power・#semiring、segment-tree-monoids#matrix・#non-commutative、subsequence-dp#leftmost、glossary#associativity・#independent-set はすべて存在し、相手のページは draft 以降
- Static Top Tree の記述（未解決の点 1）：「パスの圧縮（compress）と部分木の併合（rake）の 2 種類の操作で高さ $O(\log N)$ の木に組み直し、1 点更新を $O(\log N)$ 回の合成で済ませる」「行列にしなくてよい」は一般的な説明と合う。static-top-tree の本文と食い違わないかは、そのページの検証で併せて見るとよい
- 図：segment-tree.svg（viewBox 400×260、width・height が同じ比、白の背景、文字はテキスト）。360px でも下付きの添字まで読め、重なり・はみ出しはない。書き換えた葉 T₂ から根までの 2 つのノードが破線の枠と太い辺・「求め直す」のラベルで示され、色だけに頼っていない。代替テキストと本文の「根までの $O(\log N)$ 個のノードを掛け直す」と一致。catalog の visual は static・priority 3 なので静的な図でよい
- front matter：変えたのは complexity・stage・updated（報告どおり）。要点の「何ができるか」と summary は同じ文

## 指摘

### 1. 直すべき｜記法（F7）｜要点の囲み「いつ使うか」の 2 つ目（36 行目）と front matter の signs の 2 つ目

- **問題**：「列の区間 [l, r] だけで DP をしたときの答え」が閉区間の書き方で、「閉区間」と明記していない。本文（#what-it-does・#order-and-identity）は半開区間 $[l, r)$ で書いていて、要点と本文で区間の書き方が食い違う
- **根拠**：手引き §6「区間は半開区間 $[l, r)$ を基本にし、閉区間は『閉区間 $[l, r]$』と明記する」
- **直し方**：要点の文を「列の区間 $[l, r)$ だけで DP をしたときの答えを、クエリごとに求める」にする（意味は変わらないので signs と食い違わない）。signs の text も同じく `[l, r)` にするよう、報告でメインに提案する（front matter の signs は執筆者が直せないため）

### 2. 直すとよい｜分かりやすさ（U3）｜#on-trees の「木では値が深い方から浅い方へ流れる」の段落

- **問題**：#order-and-identity では「縦ベクトルで書くなら `op(a, b)` を $ba$ にする」と書いたのに、この節は縦ベクトルにしたうえで積が番号の順に並ぶと言う。`op` を $ab$ のままにするのか $ba$ にするのかが明記されておらず、前の節を読んだ読者は「縦ベクトルなら ba」と取り違えうる（向きが逆になるのは、木では値が番号の大きい方から小さい方へ流れるため）
- **根拠**：検証の Python では、重いパスの行列を番号の順（浅い方から）に左から掛けたときに正しい値になった。つまり `op(a, b)` は $a \otimes b$ のまま
- **直し方**：段落の終わりに「値が番号の大きい方から小さい方へ流れるので、縦ベクトルでも `op(a, b)` は $a \otimes b$ のままでよい（#order-and-identity の $ba$ は、値が番号の小さい方から流れる列の場合）」の 1 文を足す

### 3. 直すとよい｜事実（F5）｜#verify の Point Set Tree Path Composite Sum (Fixed Root) の行（147 行目）

- **問題**：「根からの合成の総和を問う」はあいまいで、根から下へ合成するようにも読める。実際は、各頂点 $y$ の値 $a_y$ に、$y$ から根へ向かう路の辺の一次関数を $y$ に近い方から順に施した値を、すべての $y$ について足したものを問う
- **根拠**：library-checker-problems の tree/point_set_tree_path_composite_sum_fixed_root/task.md
- **直し方**：「そのたびに、各頂点の値に、その頂点から根までの辺の関数を頂点に近い方から順に施した値の総和を問う」にする

### 4. 直すとよい｜分かりやすさ（U9）｜#matrix-on-segment-tree の「積の定数倍」の箇条（90 行目）

- **問題**：「mod を取る掛け算は 1 回ごとに mod を取る」は定数倍を速くする工夫の箇条の中にあるが、中身はあふれを防ぐための正しさの注意で、速くはならない（むしろ遅くなる）。言い回しも「mod を取る」が重なって読みにくい
- **根拠**：リンク先の matrix-power#fast-power の見出しも「mod の掛け算のあふれ」で、あふれの話である
- **直し方**：「mod の下の掛け算は、1 回ごとに余りを取ってあふれを防ぐ（[行列累乗の積の節](../math/matrix-power.md#fast-power)）。modint を使えば自動で行われる」のように、あふれの注意として書き分ける。速さの工夫として書くなら「`unsigned long long` に数回分ためてから余りを取る」の形にする

### 5. 直すとよい｜コード（C3）｜snippets/dynamic-dp/usage.cpp 84 行目

- **問題**：コメント「t の 2 行目が (x0, x1, 1) になる」は、本文の「3 行目（添字 2 の行）」と食い違って見える（0-indexed の 2 行目のつもりだが、日本語の「2 行目」は 1 から数えると読まれる）。この行は query の取り込み範囲に入っていて本文に出る
- **根拠**：本文 #abc246_h の「全体の積 $P$ の 3 行目（添字 2 の行）」
- **直し方**：「t の添字 2 の行が (x0, x1, 1) になる」にする

### 6. 直すとよい｜分かりやすさ（U3）・記法（F7）｜#what-it-does の「遷移がその位置だけで決まる」の箇条（63 行目）

- **問題**：「[部分列 DP](../dp/subsequence-dp.md) の貰う形の式」がページ全体へのリンクで、どの式かを探す必要がある。subsequence-dp では「貰う形」の式 $f[i+1] = 2 f[i] - f[l]$ が節 #next-table-dp にある
- **根拠**：docs/dp/subsequence-dp.md 102〜114 行目（「値の種類が多い列（貰う形）」）と、同ページの「[貰う形](#next-table-dp)」のリンク
- **直し方**：リンクを `../dp/subsequence-dp.md#next-table-dp` にし、「直前の出現位置 $l$ の値を引く $f[i+1] = 2 f[i] - f[l]$」と式を添える

### 7. 直すとよい｜事実（F1）｜「ACL では」の囲み（84 行目）と complexity の「全体の答え O(1)」

- **問題**：「`seg.all_prod()` は $O(1)$ で呼ぶ」の後の「計算量はそれぞれ $S^3$ 倍になる」は、`all_prod` にも当たるように読める。`all_prod` は `op` を呼ばず根の値を返すだけで、行列を値で返すので写しに $O(S^2)$ かかる（$S^3$ 倍ではない）。誤りというほどではないが、「それぞれ」の範囲があいまい
- **根拠**：third_party/ac-library/atcoder/segtree.hpp の `S all_prod() const { return d[1]; }`
- **直し方**：「`set`・`prod` の計算量は $S^3$ 倍の $O(S^3 \log N)$ になる。`all_prod` は根の行列を返すだけである」とする

## 総合の判定

小さな直しで可。直すべき 1 件（要点の閉区間の書き方）、直すとよい 6 件。事実・計算量・コード・図はすべて確かめて正しく、執筆者の未解決の点（確認問題の反転の主張、メモリの見積もり、Static Top Tree の説明）はいずれも正しいことを確かめた。
