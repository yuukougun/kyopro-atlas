# tree-dp-square の検証（b3）

- 対象：docs/dp/tree-dp-square.md、snippets/tree-dp-square/{tree-knapsack,components}.{cpp,yaml}、docs/img/tree-dp-square/pairs-at-lca.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py tree-dp-square`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない。試しのコードは scratchpad（v-tree-dp-square/ の cap.cpp・gen.py・arc171c.py）に置き、リポジトリには置いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page tree-dp-square`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page tree-dp-square`：直すべき行 0。textlint：エラー 0・警告 11（文の長さ・助詞の重なり。執筆者の報告どおり）
- `python3 tools/check_snippets.py -v snippets/tree-dp-square`：2 本・11 case すべて一致
- 2 本を `-fsanitize=address,undefined` 付きでコンパイルし、ランダムな木（N ≤ 12、tree-knapsack は K = 1〜N と負の重みも）300 例ずつで動かした。中の全探索の assert がすべて通り、サニタイザの報告なし。tree-knapsack の添字は i ≤ min(s, K)、j ≤ min(t, K − i) で nxt の長さ min(s + t, K) + 1 を超えない
- why-n2 の組の議論：Python で木の帰りがけ順のマージを再現し、300 本の木（ランダム・一直線・星形・毛虫、N ≤ 3000）で Σ s·t = N(N−1)/2 がちょうど成り立つことを確かめた。(s+1)(t+1) ≤ 4st（s, t ≥ 1）、LCA が v であること、u = ℓ の場合の扱い、星形の確認問題（仕事 2(k+1) の和）も正しい
- cap-k の O(NK)：同じ 300 本・ランダムな K で Σ min(s,K)·min(t,K) ≤ 2NK がすべて成り立った。証明の 3 通り（大と大は N/K 回以下、大と小は小の側の頂点ごとに K、小と小は相手が 2K 未満）を読み、穴は見つからなかった。打ち切りの条件（添字が減らない）と、成分の数の i + j − 1 ≥ max(i, j)（i, j ≥ 1）も正しい
- 確認問題の数値：N = 5000 で (N+1)^2 × (N−1) ≈ 1.25×10^11、N = 10^5・K = 300 で NK = 3×10^7・(N−1)K^2 ≈ 9×10^9、`dp[5000][5001]` の long long で約 200 MB。どれも正しい
- 落とし穴「サイズをマージの前に足す」：一直線の木で Σ t^2 = O(N^3) になる説明は正しい
- 成分の数の DP：表の 4 通り、初期値 (1,0)・(0,1)、答えの読み方は jikei の記事の 2 配列・遷移（両方使うと 1 減る）と一致。components.cpp の cases（N = 4 の星形 11・3・1・0 など）は中の全探索の assert で確かめられている
- ARC171 C の方針「辺の集合ごとに Π d! を足す」：N ≤ 7 のランダムな木 200 本で、辺を 1 回ずつ使う交換の列をすべて試す全探索と一致（v-tree-dp-square/arc171c.py）。Luogu の記事（f_{u,i}・g_{u,0/1}、i! と (i+1)!、N ≤ 3000、mod 998244353）とも合う。練習の要約は Luogu の題意の要約と同じ意味で、手法名なし
- ABC207 F：kmjp の記事の 3 状態（警備されていない・高橋君がいる・隣に警備される）と添字 x + y + 1 の 2 つの遷移を確かめた。本文の「個数をいつ数えるか」の 3 行と合う
- ARC130 D：kmjp の記事の f(v, n)・対称性 f(v,n) = g(v, S(v) − n)・累積和 DS と、本文の方針が合う。要約「隣接する頂点すべてより大きいか小さい」は記事の「パス a-b-c で P[b] が最小か最大」と同値（b の隣に b より小さいものと大きいものがあれば、その 2 つを両端にしたパスが反する）
- TDPC P：sigma425 の記事の「j 本書いてて、i から下に k 本（0,1,2）」と本文の方針が合う
- 問題 5 件：`tools/ap.py show` で題名と diff（abc287_f 2034・arc171_c 2244・abc207_f 2398・tdpc_eel なし・arc130_d 2437）が本文と一致。役割は catalog どおり
- 参考の 8 つの URL：`tools/check_noai.py` ですべて指定なし。題名・内容は書かれたとおり（merom686 は「完全グラフの辺と対応させる」計算量の説明に触れる、kanpurin の「2乗の木DP」に ABC207 F・ARC130 D・ABC287 F）。F8：本文の例（図の 8 頂点の木、重みの和の最大のナップサック）は記事の写しではない
- リンク先：tree-dp#vertex-states・tree-dp#postorder・tree/lca・tree/small-to-large・knapsack-01・subset-sum はどれも存在し、相手は draft
- コード：bits/stdc++.h と using namespace std、マクロなし、`'\n'`、DFS は `auto&& self` の形で戻り値の型を明記、ACL は modint の別名だけ（手引きの例外どおり）。mint の積は ACL の modint で、long long の max は NEG = LLONG_MIN/4 で足してもあふれない（|a| が常識的な範囲なら）
- 図：catalog の visual（static・priority 2・頂点の組と LCA）を、A × B の表で満たしている。値（s = 5、t = 3、15 組、(a, e) の LCA が v）は本文の文と合う。白背景・viewBox・font-family="sans-serif"・相対パス。720px で重なり・はみ出しなし。代替テキストに s・t・組の数・LCA がある

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | code C8・fact F2 | 落とし穴「配列を最初から長さ N + 1 で確保する」の最後の 2 文（「子の配列は戻り値で受け取るか、マージ後に `dp[c] = {};` で捨てる。`clear()` は容量を解放しないことがある」） | この段落の dp は `vector<vector<long long>>` なので、`dp[c]` は `vector<long long>`。`v = {}` は initializer_list の代入が選ばれ、要素を消すだけで容量を解放しない（clear と同じ）。読者がこの通りに書くとメモリは減らない。components.cpp の `dp[c] = {};` が効くのは、要素が `std::array<vector<mint>, 2>`（集成体）で、空の配列からのムーブ代入になるからで、本文の文脈とは型が違う。また `clear()` は容量を変えない（「ことがある」ではない） | v-tree-dp-square/cap.cpp（g++-15 -O2）：長さ 1000 の `vector<long long>` に `= {}` で capacity 1000 のまま、`clear()` も 1000、`array<vector<long long>,2>` に `= {}` で 0、`= vector<long long>()` と `vector<long long>().swap(v)` で 0 | 「マージ後に `dp[c] = vector<long long>();`（または `vector<long long>().swap(dp[c]);`）で捨てる。`dp[c] = {};` や `clear()` は容量を解放しない」とする。components.cpp の `dp[c] = {};` は動くのでそのままでよいが、読者が型を替えて写すと効かなくなるので、`dp[c] = array<vector<mint>, 2>();` と型を書く形にすると安全 |
| 2 | 直すとよい | clarity U9・code C3 | 落とし穴「両方を選ぶ遷移で添字が −1 になる」の最後の文 | 「ループで −1 を読むと範囲外になる」とあるが、components.cpp で i = j = 0 のとき起きるのは `nxt[1][i + j - 1]` への書き込みである。読み合わせで「どこを読むのか」と迷う | components.cpp 42 行目 | 「i = j = 0 のときに添字 −1 へ書き込み、範囲外になる」とする |
| 3 | 直すとよい | clarity U7 | 練習の方針「ABC207 F」 | 「見張られていない子は、親に見張りを置いたときにだけ +1 する」は正しいが、もう 1 つの +1（見張られていない v が、見張りを置いた子とマージしたとき）が抜けていて、方針だけを読むと遷移を落とす。本文 state-and-count の 2 つ目の行には両方ある | kmjp の記事のコード：`to[x+y+1][2] += from[x][2]*dp[e][y][0]` と `to[x+y+1][1] += from[x][0]*dp[e][y][2]` の 2 つ | 「見張られていない頂点は、隣（親か子）に見張りを置くと分かったマージで +1 する」とする |
| 4 | 直すとよい | figure G3 | pairs-at-lca.svg（幅 360px） | 720 × 340 の横長の図が 360px で半分に縮み、文字が 7px 相当になる。表の見出しと下の 3 行の説明は読めるがかなり小さい | render_svg.py の 360px の PNG を目視 | font-size を 16〜18 に上げるか、右の表を木の下に置く縦長の配置（viewBox を 420 × 560 程度）にする。代替テキストと本文で意味は通るので急がない |
| 5 | 直すとよい | fact F5 | 練習の要約「TDPC P. うなぎ」（台帳の summary と同じ） | 「互いに共有しない K 本のパス」は何を共有しないか（頂点か辺か）が抜けている。方針の「下へ伸びる本数 0〜2」は頂点を共有しない形を前提にしている。パスの長さの下限と制約も確かめられていない（執筆者の未解決の点と同じ。こちらでも atcoder.jp 以外の資料で問題文を確かめられなかった） | sigma425 の記事は状態だけで問いを書いていない | 問題文を確かめられる第三者の資料が見つかれば、台帳の summary を「互いに頂点を共有しない K 本のパス」の形にし、checked を埋める。見つかるまでは本文はこのままでよい |

## 執筆者の未解決の点について

- TDPC P の制約・パスの条件：こちらでも確かめられなかった（指摘 5）。方針に計算量の数値を書かない判断でよい
- cap-k の「N ≤ 10^5 の木から K ≤ 100 個選ぶ」：型の例として書かれており、特定の問題を指していないので問題ない。台帳にこの型の確認済みの問題は探していない
- arc171_c の 2 つの主張（辺の集合が違えば結果も違う・各頂点の辺の順だけが結果を決める）：全探索で Π d! の和と一致したので、主張は正しい（日本語の記事がなくても事実として問題ない）

## 台帳への提案

- 執筆者の提案（abc287_f の evidence に jikei の記事、arc171_c の summary・evidence に Luogu の記事、arc130_d の evidence を kmjp の記事に差し替え、arc171_c の approach の直し）に同意。どれも記事で確かめた
- abc287_f・arc171_c・abc207_f・arc130_d：checked に 2026-10-21（各記事で問いと方針を確かめた）。tdpc_eel は空のまま
- arc171_c の台帳の summary は今「（執筆時に確かめる）」なので、本文の要約で埋める（反映が要る）

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 4）。直すべきの 1 件は落とし穴の 1〜2 文の差し替えで直る
