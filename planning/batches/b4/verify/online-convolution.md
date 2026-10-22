# b4 検証：online-convolution

- 対象：docs/math/online-convolution.md、snippets/online-convolution/product.{cpp,yaml}・online.{cpp,yaml}、docs/img/online-convolution/cdq-order.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py online-convolution --scale 2` で 360px・720px の PNG にして目で確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page online-convolution`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/online-convolution`：online 4 case・product 4 case が一致
- 2 つのコード片を `-fsanitize=address,undefined` つきでコンパイル・実行：警告・異常なし（中の n = 0〜300 の愚直な方法との比較も通る）
- textlint：エラー 0・警告 15（文の長さ・読点の数・助詞の重なり。執筆者の報告どおり）
- online.cpp：`gg(g.begin(), g.begin() + (r - l))` は $r - l \le n + 1 = $ `g.size()` なので範囲内。$c[k - l]$ は $k - j \ge 1$ の寄与だけで、$g[0]$ が効かないことも本文どおり。本文の手順 1〜4・保つ性質・半開区間・変数名とコードが一致する
- ACL：`third_party/ac-library/atcoder/convolution.hpp` の 226・238 行に `if (std::min(n, m) <= 60) return convolution_naive(...)`。囲みの「片方の長さが 60 以下なら素朴な方法」は正しい（document_ja には書かれていないが、前提のページ convolution-ntt の #acl にソースでの確認として書かれており、そこへリンクしている）。計算量 $O(n \log n)$ は document_ja/convolution.md と一致
- 積の分割統治の計算量：1 段の畳み込みの長さの合計が $O(D)$、深さ $\lceil \log_2 N \rceil$ で $O(D \log D \log N)$。優先度付きキュー（ハフマンの順）も、ハフマン木の重み付きの深さが $D(H + 1)$（$H \le \log_2 N$）で抑えられるので同じ計算量。正しい（ただし指摘 2）
- オンライン畳み込みの正しさと計算量の説明：「$j$ と $k$ を初めて分ける区間がただ 1 つ」「同じ深さの区間の長さの合計が $N + 1$」ともに正しい
- 逆元・exp の係数の式：$fg = 1$ から $g_n = -f_0^{-1} \sum_{j=1}^{n} f_j g_{n-j}$、$g' = f'g$ の $x^{n-1}$ の係数から $n g_n = \sum_{k=1}^{n} k f_k g_{n-k}$。どちらも正しい
- Library Checker：library-checker-problems の polynomial 以下に online・relaxed を名に含む問題はない（`gh api .../git/trees/master?recursive=1` で検索）。「オンライン畳み込みそのものの問題はない」は正しい。product_of_polynomial_sequence の info.toml は N_MAX = 500000・D_MAX = 500000、task.md は $0 \le d_i$（定数の多項式も来る）
- 問題：`python3 tools/ap.py show` で abc352_g（G. Socks 3・diff 2413）、abc213_h（H. Stroll・diff 2806）、abc281_h（Ex. Alchemy・diff 3180）。本文の label と diff が合う
- ABC352 G：drken 氏の記事（$N \le 3 \times 10^5$、$2 \le A_i \le 3000$、$P$ = 係数 / $\binom{S}{k}$、$\binom{S}{k}$ を $\times (S - k)/(k + 1)$ で進める、$O(N \log^2 N)$）と kmjp 氏の記事（FIFO のキューで先頭の 2 つを掛けて末尾に戻す）で、本文の方針と解法の詳細が一致する。$S \le 9 \times 10^8 < p$ なので逆元も取れる
- ABC213 H：drken 氏の記事（$N \le 10$、$T \le 4 \times 10^4$、素朴に $O(MT^2)$、区間 $[l, r)$ で辺ごとに `dp[u][l..m)` と `p[e][0..r-l)` を畳み込む、$[0, T+1)$ で呼ぶ、$O(MT\log^2 T)$）と kmjp 氏の記事で、本文と一致する
- ABC281 Ex：drken 氏の記事で、規則（レベル $n$ 未満の $n$ 個、レベル 2 以上は各レベル 1 個まで、種類が互いに違う）・レベル 1 の多項式が $\sum_k \binom{A}{k} x^k$、レベル $i$ の因子が $1 + \mathrm{dp}[i] x$・公式解説はオンラインの分割統治 FFT・記事は平方分割、を確かめた。練習の要約と方針は正しい。要約は手法名を含まない
- Nyaan's Library：題名「Relaxed Convolution」、`get(x, y)` は $a_q = x, b_q = y$ を渡して $c_q$ を返す。Verified with に yosupo の exp・inv（と convolution）がある。本文の説明と一致する
- 参考の URL 8 件：上の 6 件を取得して題名・内容が本文の説明と合う。GitHub の 2 件も存在する。atcoder.jp・codeforces.com の URL は問題の囲みの中だけ
- 図：$[0, 8)$ を 3 段に分け、各段の左（実線）・右（破線）・矢印が本文の手順と合う。360px で文字は約 10px で読める。viewBox と width・height の比が同じ。catalog の visual は null なので静的な図だけで G7 の違反ではない
- 執筆者の未解決の点：
    1. frequency_evidence の abc462_g：kmjp 氏の記事（台帳の evidence）を読んだ。色ごとの多項式をキューに入れ、先頭の 2 つを掛けて戻す処理で積を求め、包除の和を取っている。このページの「多数の多項式の積」をそのまま使うので、frequency_evidence は妥当
    2. summary の「次数の小さいものから2つずつ掛けて」：指摘 5
    3. fps-basics へ anchor なしのリンク：問題ない

## 指摘

### 1. 直すべき｜事実（F2）・分かりやすさ（U4）｜#online「自作するときの要点」の 4 つ目（$g$ 自身も $\mathrm{dp}$ で決まるとき）

- **問題**：「区間を 2 の冪にそろえると、$l > 0$ の区間では $r - l \le l$ なので必要な項は確定しているが、$l = 0$ の区間だけ扱いを分ける必要がある」は、$l = 0$ の区間だけを変えればよいと読める。実際には、$l = 0$ の区間で足せない項を、$l > 0$ の区間で受け持つ（左半分の値を両側の因子として 2 回足す）必要があり、$l = 0$ だけを変えると答えが合わない
- **根拠**：$\mathrm{dp}[1] = 1$、$\mathrm{dp}[i] = \sum_{j=1}^{i-1} \mathrm{dp}[j] \, \mathrm{dp}[i-j]$（カタラン数がずれたもの）で、$N + 1 = 16$ の 2 の冪の区間で試した（scratchpad の relaxed.py）。$l = 0$ の区間では両方の添字が $m$ 未満の組だけを足し、$l > 0$ はそのままにすると `1, 1, 1, 3, 5, 9, 17, …` となり、正しい `1, 1, 2, 5, 14, 42, 132, …` と合わない。$l > 0$ の区間で $\mathrm{dp}[l, m) * \mathrm{dp}[0, r-l)$ を 2 倍して足すと全部一致した。$l = 0$ の区間で足せない項 $\mathrm{dp}[j]\,\mathrm{dp}[k-j]$（$j < m \le k - j$）は、$j$ と $k - j$ を入れ替えた形でしか後の区間に現れないためである
- **直し方**：「$l = 0$ の区間では左半分どうしだけを畳み込み、$l > 0$ の区間では左半分を $\mathrm{dp}$ 側と $g$ 側の両方に使う（同じ畳み込みを 2 倍して足す）。$l > 0$ なら $r - l \le l$ なので、相手側の項は確定している」のように、両方の区間の扱いを書く。詳細を資料に任せるなら「$l = 0$ の区間と $l > 0$ の区間で足し方を変える必要がある」とし、「だけ」をやめる

### 2. 直すとよい｜事実（F1）｜#product-of-many「因子の次数がばらばらでも、…$O(D \log D \log N)$」と要点・complexity

- **問題**：次数 0 の因子（定数）があると $D < N$ になりうるが、再帰の節は $N$ 個あり、各段の畳み込みの長さの合計は $D + N$ 程度になる。$O(D \log D \log N)$ は $D \ge N$（1 次以上の因子だけ）のときの式で、条件が書かれていない
- **根拠**：本文が確かめ先に挙げる Product of Polynomial Sequence は task.md で $0 \le d_i$、info.toml で N_MAX = D_MAX = 500000。定数の多項式が来る
- **直し方**：「各因子の次数が 1 以上なら」と条件を添えるか、$O((N + D) \log (N + D) \log N)$ と書く。complexity・要点も同じ言い方にそろえる（front matter の complexity は執筆者が変えてよい項目）

### 3. 直すとよい｜事実（F3）｜#quiz の 2 問目の答え

- **問題**：「$N = 2 \times 10^5$ なら $2 \times 10^{10}$ 回ほど」。ACL の素朴な方法は長さ $n$ と $m$ で $nm$ 回の掛け算なので、$i$ 回目は長さ $i + 1$ と 2 で約 $2i$ 回、合計は約 $N^2 = 4 \times 10^{10}$ 回になる
- **根拠**：`convolution_naive` は $n \times m$ の二重ループ。$\sum_{i=1}^{N} 2i \approx N^2$
- **直し方**：「$4 \times 10^{10}$ 回ほど」にするか、「$10^{10}$ を超え」と桁だけ言う

### 4. 直すとよい｜図（G5）・分かりやすさ（U3）｜cdq-order.svg の右の箱のラベル

- **問題**：破線の箱（寄与を受け取る右半分）の中に「右へ足す」と書かれており、箱そのものが「さらに右へ足す」側に読める。凡例（破線の箱：寄与を受け取る右半分）と言い方がずれる
- **根拠**：360px の PNG で、段 1・段 2 の右の箱に「右へ足す」、左の箱に「左（確定）」と並ぶ
- **直し方**：右の箱のラベルを「受け取る」か「右（寄与を足される）」にする

### 5. 直すとよい｜分かりやすさ（U1）・F10｜front matter の summary（提案としてメインへ）

- **問題**：summary の「次数の小さいものから2つずつ掛けて」と、要点の「隣どうし 2 つずつ畳み込む分割統治」、本文の主の説明（添字で半分に分ける）が少しずれる。執筆者の未解決の点 2 のとおり
- **根拠**：本文 #product-of-many は添字の分割を主にし、優先度付きキューを別の書き方として挙げる。どちらも計算量は同じ
- **直し方**：summary を「多数の多項式の積を、半分ずつに分けて（または次数の小さいものから）2 つずつ掛けて O(N log² N) で求める。…」にする提案をメインに上げる（summary は執筆者が変えない項目なので、メインがバッチの終わりに反映）

## 台帳への提案（検証で確かめたもの）

- abc213_h：checked に 2026-10-22（drken 氏・kmjp 氏の記事で問いと方針を確かめた）。evidence に kmjp 氏の記事を足す執筆者の提案に賛成
- abc281_h：執筆者の summary・approach の提案は drken 氏の記事と一致する。checked に 2026-10-22
- abc352_g：evidence に kmjp 氏の記事を足す執筆者の提案に賛成
- abc462_g：approach に「色ごとの多項式の積を分割統治（キュー）で求め」を足し、pages に online-convolution（関連）を足すかはメインの判断（frequency_evidence の根拠になっているため）

## 総合の判定

小さな直しで可。直すべき 1（指摘 1：両側オンラインで $l = 0$ の区間「だけ」扱いを分ける、という説明の誤り）、直すとよい 4。
