# b4 検証：matrix-tree-theorem

- 対象：docs/graph/matrix-tree-theorem.md、snippets/matrix-tree-theorem/count.{cpp,yaml}、docs/img/matrix-tree-theorem/example-graph.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px の PNG にして確かめた（白の背景つき）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page matrix-tree-theorem`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/matrix-tree-theorem`：11 case 一致
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library`：警告なし。`T`（乱数グラフで全列挙と比べる assert）が ok。`E 2 4`（0→1 を 2 本、1→0 を 2 本）は 2。`E 3 0`（辺が 0 本）は `edges[0]` で落ちる（指摘 3）
- `npx textlint`：エラー 0・警告 3（執筆者の報告と同じ）
- 本文の例：頂点 1 を除いた 3×3 の行列式を第 1 行で展開し直した：$2\cdot(3\cdot2-1) - (-1)\cdot\det\begin{pmatrix}-1&-1\\0&2\end{pmatrix} = 10 - 2 = 8$。本文の式どおり。全列挙（破線なし 4・破線あり $\binom42-2=4$）も正しく、コード片の case `U 4 5 … → 8` とも一致
- 図：頂点 1〜4 の位置・四角形の 4 本と破線の 1-3・各頂点の次数（1 と 3 が 3、2 と 4 が 2）が本文・代替テキストと一致。360px で文字が読め、重なり・はみ出しなし。線の種類（実線・破線）で区別していて色に頼らない。catalog の visual は対象外とみた
- 証明の筋：$L = BB^{\mathsf T}$、Cauchy-Binet、全域木なら小行列式 $\pm1$（r 以外の葉がある）・そうでなければ 0。正しい
- 有向の版：根から出る木は $D_{\text{in}} - A$、根へ向かう木は $D_{\text{out}} - A$ から根の行と列を除く。正しい（コード片の全列挙の assert でも一致）。3 頂点の有向閉路でどの根でも 1、も正しい
- BEST 定理：英語版 Wikipedia の主張（$\mathrm{ec}(G) = t_w \prod_v (\deg(v)-1)!$、$t_w$ は w へ向かう木の数、連結な Eulerian なグラフで w によらない）と一致。入次数＝出次数なら $D_{\text{in}} - A = D_{\text{out}} - A$ なので、根へ向かう木と根から出る木の数が等しいという本文の主張も正しい。自己ループを $(\deg^+ - 1)!$ にだけ数える扱いは、コード片の全列挙（自己ループを含む乱数グラフ）で確かめられている
- 言い換え 2 つ（s→t のオイラー路＝辺 t→s を足して 1 本目に固定、始点 s 固定の閉路＝$\mathrm{ec}\cdot\deg^+(s)$）は正しい
- #subset-dp：最小の頂点を含む成分で分ける漸化式、$t(\{v\}) = 1$、計算量 $O(2^N N^3)$ と $O(3^N)$ は正しい
- 計算量：要点・front matter の complexity・本文 #library が一致
- Library Checker：GitHub の task.md・info.toml で確かめた。counting_spanning_tree_undirected・directed は $1 \le N \le 500$、$0 \le M \le 5\times10^5$、単純とは限らない。counting_eulerian_circuits は $1 \le N \le 500$、$1 \le M \le 2\times10^5$、$e_0 = 0$ に固定した数（＝巡回シフトを同一視）。matrix_det は $1 \le N \le 500$・mod 998244353。本文と一致。potato167 氏の記事の制約の書き方の違い（執筆者の未解決の点）は、本文が info.toml に従っているので問題ない
- 例題：`python3 tools/ap.py show abc336_g` → G. 16 Integers・diff 3138。kmjp 氏の記事（台帳の evidence）の要約（長さ N+3 の 0/1 列、4 文字の窓の値の出現回数が X と一致する列を数える）と、方針（3 ビットの 8 頂点、窓 abcd を abc→bcd の辺 X 本、始点と終点の 64 通り、補助の辺で閉路にして BEST 定理、最後に $X_i!$ で割る）が本文と合う。窓 i の辺が $\lfloor i/2 \rfloor \to i \bmod 8$ になるのも正しい。N の上限は記事に書かれていない（kmjp 氏の階乗の表は 2×10^6 程度）ので、本文の「階乗は N まで前計算する」で足りる
- 参考の URL：Wikipedia の 2 ページ（主張の確認に使った）、potato167 氏の記事（題名・著者・BEST 定理の実装・多重辺の階乗の割り算・ABC336 G を含む問題一覧を確認）、kmjp 氏の記事（題名と内容を確認）、GitHub の library-checker-problems。どれも書かれたとおり。atcoder.jp の URL は例題の囲みの問題リンクだけ
- front matter：変えたのは complexity・stage・updated と sections の library・resources の追加（報告どおり）。要点の「何ができるか」と summary が食い違わない。別名の行に aliases がすべてある

## 指摘

### 1. 直すべき｜事実（F2）｜#best-theorem の最後の段落「辺を区別しない（同じ種類の辺が c 本ある）ときは、区別して数えた後で、種類ごとに c! で割る」

- **問題**：主語が限られていないので、直前の $\mathrm{ec}(G)$（巡回シフトを同一視した閉路の数）にも使えるように読めるが、$\mathrm{ec}(G)$ を $\prod c!$ で割るのは誤りで、整数にならないこともある。割ってよいのは、始点を決めた「辺の並び（列）」を数えたもの（始点と終点が決まったオイラー路、始点だけ決まった閉路 $\mathrm{ec}\cdot\deg^+(s)$）である。巡回の数は、同じ種類の辺を入れ替える置換が巡回シフトと重なる場合があるため、単純に割れない
- **根拠**：反例：2 頂点で 0→1 を 2 本（種類 a）、1→0 を 2 本（種類 b）。辺を区別した $\mathrm{ec}(G) = t_w \cdot 1! \cdot 1! = 2$（コード片 `E 2 4` の出力も 2）。辺を区別しない閉路は abab の 1 つだけだが、$2 / (2!\cdot2!) = 1/2$ になる。一方、始点 0 を決めた列の数は $\mathrm{ec}\cdot\deg^+(0) = 4$、$4/(2!\,2!) = 1$ で正しい。例題 ABC336 G は列を数えるので、例題の解法は正しい
- **直し方**：「辺を区別しない（同じ種類の辺が $c$ 本ある）ときは、始点を決めた列の数（上の 2 つの言い換え）を区別して数えた後で、種類ごとに $c!$ で割る。巡回シフトを同一視した $\mathrm{ec}(G)$ そのものは、こうして割ってはいけない」のように、使える対象を限る

### 2. 直すとよい｜分かりやすさ（U3）｜#best-theorem「なぜこの形になるかの筋」

- **問題**：「1 本目の辺を固定して閉路をたどり、$w$ 以外の各頂点から最後に出ていく辺を集めると」の $w$ が、1 本目の辺の始点であることが書かれていない。直前の式では $w$ は「ある頂点」なので、読者は任意の $w$ で成り立つ対応だと読み、後の「$w$ では 1 本目の辺が決まっていて」で初めて $w$ が始点だと気付く
- **根拠**：対応が全単射になるのは、$w$ を 1 本目の辺の始点に取ったときだけである（最後に $w$ に戻るので $w$ から最後に出る辺は木に入れない）
- **直し方**：「$w$ から出る辺を 1 本目に固定して閉路をたどり、$w$ 以外の各頂点から最後に出ていく辺を集めると」とする

### 3. 直すとよい｜コード（C8）｜snippets/matrix-tree-theorem/count.cpp `count_eulerian_circuits`（取り込み best の中）の `int root = edges[0].first;`

- **問題**：辺が 0 本のとき `edges[0]` が範囲外になり、未定義動作で落ちる。Library Checker の counting_eulerian_circuits は $M \ge 1$ なので提出では起きないが、本文は「次数と連結性を確かめ、辺のない頂点を除いてから使う」とだけ書いていて、空のグラフの扱いが読者に分からない。例題 ABC336 G のように補助の辺の有無で呼び分けて自作に流用すると踏みうる
- **根拠**：`printf 'E 3 0\n' | ./a`（サニタイザつき）で `reference binding to null pointer` の後に SEGV
- **直し方**：先頭に `if (edges.empty()) return 1;`（空の列を閉路 1 つとみなす）か `return 0;` を、どちらの約束かのコメントつきで足す。あるいは関数の前のコメントに「辺は 1 本以上」と前提を書く

### 4. 直すとよい｜分かりやすさ（U6）｜#directed の最後の段落

- **問題**：根へ向かう木について「対角に出次数を置く」とだけあり、非対角を同じ $-(u \to v \text{ の辺の本数})$ のままでよいのかが書かれていない。向きを取り違えやすいとこの段落自身が注意しているので、非対角まで明示したほうが迷わない
- **根拠**：根へ向かう木の行列は $D_{\text{out}} - A$（非対角は根から出る木と同じ）で、検証役は本文から非対角を読み取れず、自分で導いて確かめた
- **直し方**：「対角に出次数を置き、非対角は同じく $-(u \to v$ の辺の本数$)$ とする」と 1 句足す

## 台帳への提案（検証役から）

- abc336_g：執筆者の summary の提案は kmjp 氏の記事と合う。`checked: 2026-10-22` を入れてよい。evidence への potato167 氏の記事の追加も、記事の問題一覧に ABC336 G があるので妥当

## 執筆者の未解決の点について

- abc253_h の 2 つ目の裏付け：未取得のまま。台帳に入れるのはメインの判断（本文は ID を出していないので、このページの検証の範囲では問題なし）
- abc336_g の N の上限：本文は上限に頼る書き方をしていないので、このままでよい
- Library Checker の制約：info.toml で $N \le 500$・$M \le 2\times10^5$ を確かめた。本文は正しい
- determinant が stub・euler-path などからのリンクの張り替え：メインの作業。本文側に直すものはない

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 3）。指摘 1 は 1 段落の書き直しで済む。
