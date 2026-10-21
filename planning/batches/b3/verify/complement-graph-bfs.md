# complement-graph-bfs の検証（b3）

- 対象：docs/graph/complement-graph-bfs.md、snippets/complement-graph-bfs/{complement-bfs,components}.{cpp,yaml}、docs/img/complement-graph-bfs/take-unvisited.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py --out <scratchpad> docs/img/complement-graph-bfs/take-unvisited.svg`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目で確かめた
- atcoder.jp・codeforces.com は開いていない。試しのコードは scratchpad（v-complement-graph-bfs/t.py・big.txt）に置き、リポジトリには置いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page complement-graph-bfs`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page complement-graph-bfs`：直すべき行 0
- `python3 tools/check_snippets.py snippets/complement-graph-bfs`：2 本とも期待どおり（期待と違う 0）
- 2 本を `-fsanitize=address,undefined` 付きでコンパイルし、ランダムな単純グラフ 600 例（N ≤ 12、M は 0〜N(N−1)/2）で、隣接行列で補グラフを作る素朴な BFS（距離・最短路の本数 mod 998244353）と素朴な連結成分と照合した。すべて一致し、サニタイザの報告なし
- 同じ 600 例で、配列版の走査の「残す」回数が M 以下・「取り出す」回数が N − 1 以下であることを確かめた（本文の上限 2M より強く成り立つ。指摘 2）
- N = 2×10^5・M ≈ 2×10^5（頂点 1 の次数がほぼ N の星形）の入力で complement-bfs.cpp は 0.06 秒
- 例（N = 6、取り除く辺 1-2・1-3・2-4・2-5、始点 1）：距離 1:0・4,5,6:1・2,3:2、走査で残すのは u=1 で 2・3、u=4 で 2、u=5 で 2（計 4）、取り出すのは 5 回。本数 cnt[3] = 3（1→4→3・1→5→3・1→6→3）、cnt[2] = 3 − 1 − 1 = 1（1→6→2 のみ）を手で確かめた。snippet の case「6 4」の出力 `0 2 2 1 1 1`／`1 1 3 1 1 1` とも一致。確認問題 3 の誤り方 cnt[3] = 2 も正しい
- 「隣の値の最大」の応用（執筆者の未解決 3）：値の大きい順の列を先頭から見て、見送るのは v 自身か G での v の隣だけなので、見送りは deg_G(v) + 1 回以下で、全体 O(N + M)（並べ替えを除く）。正しい。G に多重辺があっても見送る頂点の種類は変わらないので、この応用は多重辺で壊れない（和の方は壊れる。落とし穴の 5 つ目と同じ）
- 落とし穴：`for (int w : rest)` の中の `rest.erase(w)` は消した要素のイテレータを進めるので未定義動作、`it = rest.erase(it)` が正しい直し方。印の消し忘れで「残す」が誤って増える説明も正しい
- 計算量の 3 か所（front matter の complexity・要点・#complexity の表）は一致。ならしであることも本文に書かれている
- ABC319 G：`tools/ap.py show abc319_g` で題名「G. Counting Shortest Paths」・diff 2185 が本文と台帳に一致。要約に手法名なし。kmjp の記事（2023-09-09）で、問題が「N 頂点の完全グラフから M 辺取り除いたグラフで 1 から N への最短経路の数」であること、mod 998244353、届かなければ −1、層ごとに「前の層の dp の和から通れない辺の分を引く」方針を確かめた。記事のコードは隣接を set で持つ（重複は自然に消える）
- 執筆者の未解決 1（ABC319 G の制約）：kmjp の記事に制約の記載はなく、本検証でも確かめられなかった。本文は数を書かず条件付きの落とし穴にしているので、このままでよい
- 執筆者の未解決 2（Library Checker の制約）：library-checker-problems の info.toml で N_MIN = 1・N_MAX = 500000・M_MIN = 0・M_MAX = 500000、task.md で「与えられるグラフは単純」・入力 0-indexed・出力形式（K のあと各成分の l と頂点）を確かめた。本文は数を書いていないので問題なし。components.cpp の case「0 0」は N_MIN の外だが、空のグラフで動くことの確かめとして害はない
- リンク先：graph-basics#terms（補グラフの定義あり）・bfs#why-shortest・shortest-path-dag#count-paths・thinking/complement・ordered-set#pitfalls・ordered-set#rows-and-columns・glossary#amortized-complexity・ds/linked-list はどれも存在する
- 参考の URL：kmjp.hatenablog.jp・github.com・judge.yosupo.jp は付録 B にある。kmjp の題名「AtCoder ABC #319 : G - Counting Shortest Paths」は一致。github の task.md は HTTP 200 で内容も書かれたとおり（題名は指摘 1）
- F8：本文の例（N = 6 の 4 辺）・文は kmjp の記事と別。記事の方針は層 S(n) を総当たりする形で、本文の「未訪問の集合を走査する」BFS とは書き方が違い、写しではない
- コード：`bits/stdc++.h`・`using namespace std;`、マクロなし、`'\n'`、ACL は modint の別名だけ。本文の記号（rest・keep・dist・mark・u・w）とコードの変数名が一致。取り込みは core・count・core で印の名前も合う。dist は int、本数は modint で、引き算で負にならない
- 図：白背景・viewBox あり・font-family="sans-serif"・相対パス。補グラフの辺（1-4・1-5・1-6・4-3・5-3・6-3・6-2）、同じ層の辺（4-5・5-6・4-6・2-3）、元の辺の破線（1-2・1-3・2-4・2-5）が正しく、補グラフ全体の 11 本と元の 4 本で 15 = 6·5/2 本。下段の走査表・残した辺のラベル・「残した回数 4・取り出した回数 5」も本文と一致。破線と色の両方で区別しており色覚の違いでも読める。代替テキストに値がある。catalog の visual は static・priority 3 で、この静的な図で足りる

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact（F9） | #take-unvisited の 85 行目（応用の型：補グラフの連結成分）と #references の 194 行目 | Library Checker の問題名を「Connected Components of the Complement Graph」と書いているが、実際の題名は「Connected Components of Complement Graph」（the なし）。 | library-checker-problems の graph/connected_components_of_complement_graph/info.toml の `title = 'Connected Components of Complement Graph'` | 2 か所とも「Connected Components of Complement Graph」にする |
| 2 | 直すとよい | fact（F1）・clarity（U2） | #complexity の「残す回数」の項（96 行目）と確認問題 2 の答え（183 行目） | 「1 本の辺 u-w が『残す』に使われるのは u を取り出したときと w を取り出したときの高々 2 回」「全体で 2M 以下」は上限として正しいが、実際は高々 1 回である。u を取り出して w を残したなら、後で w を取り出すときに u はもう rest にいない。そのため直後の「図の例でも、残した回数は 4 回（元の辺の数）」と、本文の上限 2M が合わず、読者は「なぜ 2M ではなく M なのか」で引っかかる | ランダムな 600 例で「残す」回数 ≤ M を確かめた。理屈は上のとおり | 「1 本の辺 u-w が『残す』に使われるのは、先に取り出された方の端点を取り出したときの 1 回だけである（もう一方を取り出すときには、先の端点はもう rest にない）。だから全体で M 回以下である」とする。確認問題 2 の答えも「次数以下で、全頂点で足すと 2M 以下」に一言「（辺ごとに見れば 1 回なので、実際は M 以下）」を足すか、今のまま次数の上限の問いとして残す |
| 3 | 直すとよい | clarity（U4） | #take-unvisited の擬似コード（69〜77 行目） | `rest = keep` で使う keep を、各反復の初めに空にすることが書かれていない。コード片には `vector<int> keep;` があるが、擬似コードだけで実装すると keep を外に置いたまま溜め続ける誤りを招く | コード片 core の `vector<int> keep;` の位置 | 「u を取り出す」の次に「keep = 空」を足す |
| 4 | 直すとよい | fact（F1） | 要点・front matter の complexity・#complexity の表と 110 行目 | set 版の計算量 O((N + M) log N) は上限として正しいが、set で log がかかるのは消す（N − 1 回）ときだけで、残す頂点はイテレータを進めるだけ（ならし O(1)）なので、印の配列で隣接を見るなら O(N log N + M) である。また「set<pair<int,int>> で引く書き方も…評価は同じ」の「同じ」が、何と同じ計算量になるのか（O((N + M) log M) 程度）が読み取りにくい | 走査 1 回あたりの手間を数え直した | 書き換えるなら表を O(N log N + M) にし、110 行目を「…走査 1 回ごとに O(log M) かかり、全体で O((N + M) log M) になる」とする。ただし今の書き方も誤りではないので、front matter と要点はそのままでもよい |
| 5 | 直すとよい | figure（G3） | take-unvisited.svg（360px） | 幅 360px では凡例（「補グラフの辺」「同じ層の辺」「元の辺（通れない）」）と、残した辺のラベル（1-2・1-3・2-4・2-5）が小さく、判読がぎりぎり。重なり・はみ出しはない。執筆者も報告で認めており、同じ内容が図の後の文章にあるので致命的ではない | render_svg.py の 360px の PNG を目視 | 凡例と辺ラベルの font-size を 1〜2 段上げる（viewBox 640 幅で 13〜14 程度） |

## 台帳への提案

- abc319_g の `checked` に 2026-10-21 を入れる（tools/ap.py で題名・diff、kmjp の記事で問題の内容・mod・−1 の出力を確かめた。制約の数は未確認）

## 総合の判定

小さな直しで可。直すべき 1 件（Library Checker の題名の the）、直すとよい 4 件。正しさ（BFS・本数の式・連結成分・計算量の上限）はプログラムと手計算で確かめて問題なし。
