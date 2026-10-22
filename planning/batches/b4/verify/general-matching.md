# b4 検証：general-matching

- 対象：docs/graph/general-matching.md、snippets/general-matching/{bitdp,tutte-rank}.{cpp,yaml}、docs/img/general-matching/{blossom,contracted}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px の PNG にして目で確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page general-matching`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/general-matching`：コード片 2・期待と違う 0
- `npx textlint docs/graph/general-matching.md`：エラー 0・警告 10（執筆者の報告と同じ。文の長さ・数式を含む文など）
- 両方のコード片を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイル（警告なし）。$N \le 9$ のランダムなグラフ 400 通り（辺の密度 0.2・0.5・0.8）で、辺の部分集合の全探索による最大マッチングと tutte-rank・bitdp（重み 1）の出力を比べ、すべて一致。サニタイザの報告なし
- 例題の言い換え（複製・重み 0／1・最小重み完全マッチング）を、$N \le 5$・$A_i \le 3$ のランダム 400 通りで、辺の部分集合の全探索と比べてすべて一致（-1 の場合を含む）。同じ辺を 2 回使わないこと（重み 0 の 2 本に替えると 2 減る）の議論も正しい
- 奇閉路の例を手で確かめた：辺 r-a・a-b（組）・b-c・c-d（組）・d-r・c-t、r と t が空き。r-d-c-t は 組でない・組・組でない で増加路。花を戻すとき、出口 c へ底 r から組の辺で着く周り r→d→c（長さ 2）を選ぶのが正しく、r→a→b→c（長さ 3、組でない辺で着く）は c-t と続かない
- 擬似コード（外／内、別の木の外で増加路、同じ木の外で花、内は無視）は標準の Edmonds の探索と合う
- Berge の定理：bipartite-matching の #alternating-path の証明（対称差が交互の路と閉路に分かれる）は二部性を使っておらず、本文の主張は正しい
- Tutte 行列：階数＝最大マッチングの 2 倍（Lovász）、乱数を入れると階数は下がる向きにしか間違えない（特殊化で小行列式が 0 になるだけ）、0 でない小行列式は次数 $\le N$ の多項式なので Schwartz-Zippel で外れる確率は $N/(p-1)$ 以下（本文の $N/p$ との差は無視できる）。$N=500$ で約 $5 \times 10^{-7}$ で「$10^{-6}$ ほど」は妥当。行列が交代行列なので階数は偶数で、`rank / 2` は正しい
- bitDP：状態 $2^N$・遷移 $N$ で $O(2^N N)$、`__builtin_ctz(~s)` は $s < 2^n - 1$ で常に $n$ 未満のビットを返す。$n=1$ でも正しい。本文の状態・遷移・計算順序・初期値と答えとコードが一致
- Wikipedia「Blossom algorithm」：花＝「2k+1 本の辺のうちちょうど k 本が M に入る閉路」、全体 $O(|E||V|^2)$、Micali-Vazirani $O(|E|\sqrt{|V|})$。本文と一致
- Wikipedia「Maximum weight matching」：Gabow の $O(V^3)$、$w'(e) = C - w(e)$ で最大の本数の中で最小重みに直す方法（十分条件 $C > 2\sum \lvert w(e) \rvert$）。本文と一致（後の指摘 3 を参照）
- Wikipedia「Tutte matrix」：定義（$i<j$ で $x_{ij}$、$A_{ji} = -x_{ij}$）と、行列式が 0 でない ⟺ 完全マッチングがある。Lovász の階数の話は Wikipedia にはない（Harvey の論文に拠るのは妥当）
- arXiv cs/0601026：Nicholas J. A. Harvey「Algebraic Structures and Algorithms for Matching and Matroid Problems (Preliminary Version)」。著者・題名は合う
- ei1333 Gabow Edmonds：「一般グラフの最大マッチングを、Gabow の Edmonds' Algorithm によって求める」、計算量 $O(VE \log V)$、verify は yosupo-general-matching。本文と一致
- Library Checker の task.md：general_matching は単純グラフ・$1 \le N \le 500$・$0 \le M \le N(N-1)/2$。general_weighted_matching は同じに加えて $1 \le w_i \le 10^6$、出力はマッチング（完全とは限らない）。本文と一致（言い回しは指摘 6）
- 例題：`python3 tools/ap.py show abc412_g` → G. Degree Harmony・diff 3402。kmjp 氏の記事：「N 点 M 辺の単純無向グラフ…全域部分グラフのうち、点 i の次数は A[i] 以下であり、かつ A[i] と偶奇が一致する…辺数の最小値」、S=ΣA が奇数なら -1、複製した S 点のグラフで同じ元の頂点の点どうしは重み 0、元の辺のある頂点の点どうしは重み 1、行列 E の重み 1 の成分に Y を掛けて行列式を Y=0..S で求めラグランジュ補間、最初の 0 でない係数の添字の半分が答え、多項式が恒等的に 0 なら -1。本文の要約・方針・解法の詳細の記述（-1 の場合を除く。指摘 1）と合う。台帳の summary の提案も記事と合う
- 図：blossom.svg は 5 頂点の閉路・組の辺（太い青）・組でない辺（細い灰）・増加路（橙の破線）が本文と一致し、色と線の太さ・破線の両方で区別できる。contracted.svg も本文と一致。どちらも幅 380 で 360px でも文字が読める。文字はテキストのまま、置き場所と相対パスも正しい。catalog の visual は対象外（静的な図 2 枚で十分）
- front matter：変えたのは complexity・stage・updated と sections の 2 節の追加（報告どおり）。要点の計算量と complexity は一致

## 指摘

### 1. 直すべき｜事実（F5）・分かりやすさ（U4）｜#abc412_g の解法の詳細

- **問題**：-1 になるのが「$X$ が奇数のとき」だけのように読める。$X$ が偶数でも完全マッチングがなければ答えは -1 である（例：$N=2$、$A = (1, 1)$、辺なし。$X = 2$ だが 2 つの複製をつなぐ辺がない）。また、最後の「最小重みがそのまま答え」には、逆向き（条件を満たす辺の選び方から同じ重みの完全マッチングが作れる）の説明がない。読者がこの通りに書くと、完全マッチングがない入力で答えを誤る
- **根拠**：kmjp 氏の記事は、多項式が恒等的に 0（完全マッチングがない）のときも -1 を出力している。全探索との比較で、$X$ 偶数で -1 になる入力が実際に出た
- **直し方**：1 つ目の項目を「$X$ が奇数なら -1」のままにし、最後の項目の前に次の 2 文を足す。「逆に、条件を満たす辺の選び方があれば、各頂点 $i$ で選んだ辺に $i$ の複製を 1 つずつ割り当て、残りの $A_i - d_i$ 個（偶数）を 2 個ずつ組めば、重みが辺の数に等しい完全マッチングになる。」「完全マッチングがなければ（$X$ が偶数でも）答えは -1 である。」

### 2. 直すとよい｜分かりやすさ（U1）・事実（F10）｜要点の「何ができるか」「いつ使うか」（front matter の summary・signs）と、要点の計算量・#bitdp

- **問題**：要点の「何ができるか」と「いつ使うか」は「$N \le 16$ 程度なら bitDP」、要点の計算量と #bitdp は「$N \le 20$ 程度」で、同じページの中で目安が食い違う。本文の $O(2^N N)$ なら $N = 20$ で約 $2 \times 10^7$ で、20 の方が正しい目安である
- **根拠**：summary・signs は catalog（graph.yaml）の書き出しのまま（$N \le 16$）。本文の計算量は執筆者が導いたもので、コードで確かめた
- **直し方**：執筆者の報告に「summary と signs の $N \le 16$ を $N \le 20$ にする」提案を足し、メインが front matter と要点をそろえる（執筆者は summary・signs を直接変えない）

### 3. 直すとよい｜事実（F2）｜#edmonds の最後の段落（「十分大きな定数 − 重み」）

- **問題**：「十分大きな定数」の大きさが示されておらず、完全マッチングがない場合にどうなるかにも触れていない。また、定数を大きく取ると重みが大きくなり、Library Checker 向けのライブラリ（重み $\le 10^6$ を前提にした int の実装）ではあふれうる
- **根拠**：本数 $k$ のマッチングの重みは $[kC - kW, kC]$（$W$ は重みの最大）なので、$C > (N/2) W$ なら本数の多い方が必ず勝つ。Wikipedia「Maximum weight matching」は十分条件 $C > 2\sum \lvert w(e) \rvert$ を挙げ、得られるのは「最大の本数の中で重みが最小のマッチング」と書いている
- **直し方**：「（$C > (N/2) \max w$ なら足りる）」を添え、「得られたマッチングが完全でなければ、完全マッチングはない」を 1 文足す。重みの型（long long）にも一言触れるとよい

### 4. 直すとよい｜分かりやすさ（U3）｜#odd-cycles の第 3 段落の最後の文

- **問題**：打ち切られたのは d（「次に r→d と進んでも d は調べ済みとして打ち切られる」）なのに、原因の文は c の着き方を述べていて、読者はどちらの印が問題なのか迷う。d には 1 回目に組の辺（c→d）で着き、2 回目は組でない辺（r→d）で着こうとしていて、偶奇の違う着き方を同じ印で打ち切ったのが原因である
- **根拠**：本文の例を手でたどると、2 回目に打ち切られるのは d で、その先で c に組の辺（d→c）で着く場合が調べられない
- **直し方**：「d には 1 回目は組の辺（c→d）で着いたが、今回は組でない辺（r→d）で着いている。偶奇の違う着き方を同じ印で打ち切ったため、その先で c に組の辺で着く場合（d→c→t）を調べられなかった」のように、d と c の両方を名指しする

### 5. 直すとよい｜事実（F7）｜#tutte-matrix の 3 つ目の箇条書き

- **問題**：「行列式が 0 でないかを見れば足りる（Tutte の定理）」の「Tutte の定理」は、ふつう Tutte の完全マッチングの条件（$G - S$ の奇数個の連結成分の数が $\lvert S \rvert$ 以下）を指し、読者が別の定理と取り違えうる
- **根拠**：Wikipedia「Tutte matrix」は、行列式（Pfaffian の 2 乗）が多項式として 0 でない ⟺ 完全マッチングがある、として Tutte (1947) を引いているが「Tutte の定理」とは呼んでいない
- **直し方**：「（Tutte, 1947）」とするか、「行列式が多項式として 0 でないことと、完全マッチングがあることが同値なので」と理由を書く

### 6. 直すとよい｜分かりやすさ（U9）｜#library の最後の段落

- **問題**：「どちらも $N \le 500$ で、重みは 1 以上 $10^6$ 以下である」は、重みのない general_matching にも重みがあるように読める。また、どちらも単純グラフ（自己ループなし）である点は、tutte-rank のコード片（自己ループがあると対角に $-x$ が残り交代行列でなくなる）を試すときに効く
- **根拠**：library-checker-problems の task.md（graph/general_matching・graph/general_weighted_matching）
- **直し方**：「どちらも単純グラフで $N \le 500$、General Weighted Matching の重みは 1 以上 $10^6$ 以下である」とする

### 7. 直すとよい｜事実（F9）｜#references の Harvey の行

- **問題**：題名に「(Preliminary Version)」が抜けている
- **根拠**：arXiv cs/0601026 の題名は「Algebraic Structures and Algorithms for Matching and Matroid Problems (Preliminary Version)」
- **直し方**：題名に「(Preliminary Version)」を足す（#resources の箇条も同様）

## 執筆者の未解決の点について

- abc412_g の evidence が kmjp 氏の 1 つだけの件：検証でも追加の第三者の解説は探していない。ただし言い換えの正しさは全探索との比較で確かめたので、本文の方針・解法の詳細（指摘 1 を直した後）は正しい。§15-6 の目標（2 つ以上）に届かないことはメインの判断に任せる
- $1 - N/p$ の確率：Schwartz-Zippel から導けることを確かめた（厳密には 0 を除く $p-1$ 通りから選ぶので $N/(p-1)$。mt19937 の剰余の偏りを入れても $1.2$ 倍程度で、本文の「$10^{-6}$ ほど」は変わらない）。直さなくてよい
- Gabow の改良版の作り（縮約したグラフを作り直さない）：ei1333 氏のページの記述は「Gabow の Edmonds' Algorithm」と計算量だけで、作りの説明はない。本文は一般的な説明として妥当で、誤りはない
- bipartite-matching・konig-theorem からの節へのリンクの張り替えはメインの作業

## 台帳への提案

- abc412_g：執筆者の summary の提案は kmjp 氏の記事の問題の要約と合う。`checked: 2026-10-22` を入れてよい

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 6）。直すべきは例題の解法の詳細の -1 の場合の書き落としだけで、本文の仕組み・計算量・コード片・図は正しい。
