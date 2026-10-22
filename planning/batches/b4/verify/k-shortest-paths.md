# b4 検証：k-shortest-paths

- 対象：docs/graph/k-shortest-paths.md、snippets/k-shortest-paths/k-times.{cpp,yaml}（図はなし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。試しのコードは scratchpad（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-k-shortest-paths/）に置き、リポジトリには置いていない

## 実行して確かめたこと

- `python3 tools/check_pages.py --page k-shortest-paths`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/k-shortest-paths`：k-times.cpp 6 case 一致
- k-times.cpp を `-fsanitize=address,undefined` つきでコンパイル・実行：警告・異常なし（中の乱択の比較 200 個も通る）。本文の小さい例（0→1 重み 2、1→0 重み 1）の入力で 2, 5, 8, 11 が出て、本文のヒープの取り出し順 (0,0)・(2,1)・(3,0)・(5,1) とも合う
- 取り込み部分を、**重み 0 の辺・重み 0 の閉路・自己ループ・多重辺を含む**乱択のグラフ 20000 個で、長さごとのウォークの数を数える DP（同じ長さの中は重み 0 の辺で不動点まで回し、K で飽和させる）と比べた：すべて一致。執筆者の main の試験は重み 1 以上だけなので、重み 0 の場合の正しさはこれで補った
- 本文の「異なる長さだけを数えるなら、v で直前に取り出した値と同じ値の取り出しを捨てる」も同じ 20000 個で、到達できる (頂点, 長さ) の集合から求めた異なる長さの列と比べた：すべて一致
- 正しさの説明（接頭辞の議論）：$v$ への $j$ 番目のウォークの直前の $u$ へのウォークより真に短いものが $j$ 個あれば、$v$ への $j$ 番目より真に短いものが $j$ 個できて矛盾する。正しい。計算量：各頂点の取り出しが $K$ 回までなので追加は $K \sum \deg = KM$ 回以内。正しい
- Library Checker：library-checker-problems の task.md・info.toml を読んだ。単純とは限らない有向グラフ、同じ長さでも別のウォーク、ない分は -1、$N, M, K \le 3 \times 10^5$、$0 \le c \le 10^7$、制限 5 秒。本文の要約と一致（$M \ge 1$ だが、コード片の case の $M = 0$ は自作の入力なので問題ない）
- ei1333 のライブラリ：k-shortest-walk.hpp は `vector<T> k_shortest_walk(const Graph<T>& g, int s, int t, int k)`、計算量 $O((V + E) \log V + K \log K)$、Eppstein（hotman78 の記事を参照）。k-shortest-path.hpp は `vector<pair<T, vector<int>>> k_shortest_path(...)`（長さと辺番号の列）、$O(KV(E + V) \log V)$、「verify が甘いため合っているかかなり不安」の注記。本文と一致。木の辺を「ダイクストラ法の親（`dist.from`）かつ等式を満たす最初の 1 本」で選び、残りを寄り道として push している。本文の自作の要点 2 つと合う
- Wikipedia「Yen's algorithm」：非負の重み、1971 年、計算量 $O(KN(M + N \log N))$（ダイクストラの呼び出しは $Kl$ 回、$l$ は spur path の長さで最悪 $N$）。「K shortest path routing」：ループを許す変種は Eppstein（1998）、ループなしは Yen。本文・参考の説明と一致
- 参考の URL：7 件すべて開けて、題名が本文と一致（hotman78・nariaki3551 の Qiita の題名を `<title>` で照合）。ドメインはすべて付録 B。atcoder.jp・codeforces.com の URL はない
- F8：hotman78 の記事本文と Eppstein の 4 段を並べて読んだ。記事は永続 leftist heap の実装とポテンシャルの式変形が中心で、本文の言い回し・例（2 頂点の閉路）は別物。近すぎない
- 前提とリンク：glossary の path-walk・shortest-path-tree・potential、dijkstra.md#potential、persistent-data-structures.md#path-copying はいずれも存在する（check_pages も通る）
- front matter：変えたのは complexity・stage・updated と sections の yen-eppstein の title（anchor は不変）。title の変更は手引き §15-2 で執筆者が行ってよいもの。complexity と要点の計算量は一致
- 図：catalog（planning/catalog/graph.yaml）の visual は null。図がないことは G7 の違反ではない。小さい例は文章で 1 回動かしてあり、図がなくても通じる
- 執筆者の未解決の点：
  1. Eppstein の $O((N + M) \log (N + M) + K \log K)$ は資料の $O((V + E) \log V + K \log K)$ を含む上界で正しい（単純グラフなら $\log M \le 2 \log N$ で同じ。多重辺で $M$ が大きい場合も成り立つ）。記憶 $O(M \log M)$ も、各寄り道の辺を永続ヒープに 1 本ずつ push すると 1 回 $O(\log M)$ 個の節点を作るので正しい上界
  2. 「$KM$ が $10^7$ 程度まで」は、追加 $10^7$ 回 × $\log$ で $2 \times 10^8$ 程度なので妥当。「Yen は $N, M$ が数千、$K$ が数十まで」は計算量と合わない（指摘 1）
  3. 原論文を開いていない点は、Wikipedia の出典つきの記述で年と計算量が確かめられるので問題ない

## 指摘

### 1. 直すべき｜事実（F1・F3）｜#yen-eppstein の Yen の段落の末尾と、#comparison の表の Yen の行

- **問題**：「$N, M$ が数千、$K$ が数十までが目安」は、本文が書いた計算量 $O(KN(N + M) \log N)$ から見積もると大きすぎる
- **根拠**：$K = 30$、$N = M = 3000$ を入れると $30 \cdot 3000 \cdot 6000 \cdot \log_2 3000 \approx 6 \times 10^9$ になり、数秒では終わらない。目安が成り立つのは、逸れる点の数（$k - 1$ 本目のパスの長さ）が $N$ よりずっと小さいときだけである（Wikipedia もダイクストラの呼び出しを $Kl$ 回、$l$ はパスの長さで最悪 $N$ と書く）
- **直し方**：たとえば「1 本ごとのダイクストラ法の回数はパスの頂点数で、最悪 $N$ 回。最悪の見積もりでは $KN(N + M)$ が $10^8$ 程度まで（$N, M$ が数百、$K$ が数十）が目安で、パスが短ければもっと大きくても間に合う」とし、表の「向く大きさ」も「$N, M$ が数百、$K$ が数十まで（パスが短ければもっと）」にそろえる

### 2. 直すとよい｜分かりやすさ（U1）・F10｜front matter の summary・signs

- **問題**：要点・本文は「ウォーク」に直したが、summary と signs に「歩道」が残り、手引き §15-22・付録 A（歩道は使わない）に反する。一覧のページ（lists/level-advanced.md・graph/index.md・lists/kind-shortest-path.md）にも summary の「歩道」がそのまま出る
- **根拠**：front matter の summary「歩道なら…歩道の列挙は Eppstein」、signs「K 番目に短い経路・歩道の長さ」
- **直し方**：執筆者の報告の「手引き・front matter・catalog への提案」の案どおり、メインが summary と signs を「ウォーク」に直す（執筆者は front matter を直せないので、ページの直しではなくメインの反映）

### 3. 直すとよい｜分かりやすさ（U8）｜#quiz の 1 問目

- **問題**：「ふつうのダイクストラ法の読み飛ばしの条件を残すとどうなるか」は、#k-times の要点「距離の配列で枝刈りしない」の 1 文をほぼそのまま問うていて、答えも本文の写しになる
- **根拠**：本文「2 番目以降の値がすべて捨てられる。読み飛ばしの条件は『$v$ をすでに $K$ 回取り出したか』に置き換える」と、答え「2 番目以降の値はすべて読み飛ばされ…『$v$ をすでに $K$ 回取り出したか』に置き換え」が同じ
- **直し方**：本文の主張を別の場合に当てる問いに替える。たとえば「異なる長さだけを数える版で、$v$ で直前と同じ値の取り出しを捨てるとき、その組から辺を伸ばさなくても答えが変わらないのはなぜか」（答え：同じ長さのウォークに辺を足すと、すでに伸ばしたものと同じ長さしか作らないため）や、「$t$ だけ $K$ 回で止め、ほかの頂点の取り出し回数を制限しないとどうなるか（正しいが遅くなる。閉路があると追加が止まらないこともある）」

### 4. 直すとよい｜分かりやすさ（U3）｜#quiz の 2 問目の答え

- **問題**：「最短より $2w$ だけ長いウォークができる」の $w$ が定義されていない
- **根拠**：問い・答えのどこにも $w$ が出てこない。断片で読むと何の重みか分からない
- **直し方**：「最短路の上（または途中の頂点に付いた）の重み $w$ の辺を 1 往復するだけで、最短より $2w$ 長いウォークができる」とする。辺が 1 本 $s - t$ だけのグラフ（単純パスは 1 本だが、2 回取り出す方法は $3w$ を 2 番目に出す）を例に添えると具体的になる

### 5. 直すとよい｜分かりやすさ（U4）・事実（F2）｜#yen-eppstein の Eppstein の「木の辺は 1 頂点に 1 本だけ」

- **問題**：多重辺（同じ $u \to v$ が 2 本、ともに $d(u) = w + d(v)$）があると、木の辺を「頂点の組」や「行き先が親であること」だけで見分けた実装は、2 本とも木の辺として飛ばしてしまう。本文は「1 本だけ」とは書くが、見分け方（辺の番号か、最初の 1 本だけを飛ばす印）が書かれていない
- **根拠**：ei1333 の実装は `used` の印で、親へ向かい等式を満たす辺のうち最初の 1 本だけを飛ばしている。Library Checker は多重辺を含む
- **直し方**：要点の 1 つ目に「多重辺があるので、木の辺は辺の番号で 1 本に決める（親へ向かう辺のうち最初の 1 本だけを飛ばし、2 本目からは費用 0 の寄り道にする）」と一言足す

## 総合の判定

小さな直しで可。直すべき指摘は 1 件（Yen の目安の大きさ）。ほかの事実（3 つの計算量、正しさの説明、Library Checker の制約、ei1333 の関数、参考の題名）とコード片は確かめた範囲で正しい。
