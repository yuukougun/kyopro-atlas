# connected-components の検証（工程8b・b1）

- 対象：docs/graph/connected-components.md、snippets/connected-components/{bfs-tally,acl-dsu}.{cpp,yaml}、docs/img/connected-components/components.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page connected-components`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/connected-components`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/graph/connected-components.md`（0 errors・3 warnings。no-doubled-joshi。174 行の「でも」は台帳の abc157_d の summary 由来で、執筆者の台帳への提案で消える。ほかの 2 つは読みに支障がない）
- コード片：2 片とも `-fsanitize=address,undefined -I third_party/ac-library` でコンパイルし、乱数の小さなグラフ 400 組（自己ループ・多重辺を含む、N ≤ 8・M ≤ 10）で素朴な Union-Find の集計（成分の数・最大の頂点数・木・なもり・それ以外の数）と比べて全部一致、サニタイザの報告なし（作業用の場所 v-connected-components/t.py）。cases の期待出力（図の例 13 頂点 12 辺 → `4 4 2 1 1` など）は手でも正しい。cases に 1 頂点・辺なし・自己ループ・多重辺がある。書き方（bits・using namespace std・マクロなし・`'\n'`・0-indexed）は §9 に合う。本文の記号 comp・c・vcnt・ecnt とコードの変数名がそろう。取り込みは core だけ
- ACL：document_ja/dsu.md で、コンストラクタ $O(n)$、merge・same・leader・size はならし $O(\alpha(n))$、groups は $O(n)$。「ACL では」の囲みと一致。merge の戻り値は代表元（int）で、併合したかどうかは返さない（指摘 2）
- 計算量：front matter の complexity・要点・表・本文の根拠（各頂点に 1 回番号、各辺は両端から 1 回ずつ）が一致
- 自分で導いた主張の確かめ
    - $E - (V - 1)$ による 3 分類（全域木＋残りの辺）：正しい。確認問題の 4 頂点の閉路＋対角線は $E = V + 1$ で単純閉路が 3 つ（三角形 2 つと外周）。正しい
    - 森で $C = N - M$、一般に $M - (N - C)$ が閉路をなくすのに取り除く辺の最小本数（巡回数）：正しい。確認問題（10 頂点 7 辺、閉路なし → 3、閉路がちょうど 1 つ → 4）も正しい
    - 次数の和の半分と自己ループ（片方だけ push すると 1/2）：正しい
    - abc131_f の型（各成分が完全二部グラフになり、最後の点の数は $\sum X_c Y_c$）：5×5 の格子の点の集合 300 組で、操作を閉包までくり返した点の数と一致。証明の折りたたみ（道 $x_0 y_1 x_2 y_3$ の 3 隅から $x_0$–$y_3$ を足して道を縮める）も正しい
- 問題：例題 abc177_d、練習 abc292_d・abc157_d、力試し abc131_f は台帳で確認済み。label・diff（732・579・1208・1937）は台帳と一致し、役割と数は catalog と一致。方針は台帳の evidence と食い違わない（abc177_d：最大の成分の大きさ。abc292_d：kazun の記事で制約 $1 \le u_j \le v_j \le N$、成分ごとに頂点数と辺数）。台帳の `checked` に 2026-10-21 を入れてよい（abc177_d・abc131_f。abc157_d は指摘 3 の点を確かめてから）
- 参考の URL：kazun（abc292_d）と drken（abc157_d）を開き、題名・内容が書かれたとおり。どちらも付録 B のドメイン（hatenablog）。本文の文・例は記事と並びも例も違い、近すぎる箇所はない
- 図 components.svg：ヘッドレスのブラウザがこの環境になく（playwright・chromium・cairosvg なし）、画像にはしていない。SVG の座標を読んで確かめた。頂点番号と辺（1-2・2-3・2-4、5-6-7 の三角形と 7-8、孤立点 9、10-11-12-13 の四角形と対角線 10-12）は bfs-tally の 1 つ目の case と一致し、太線（幅 4・赤）が閉路の辺に正しく付く。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、色に加えて線の太さで区別。ラベルの文字幅は枠に収まる（「孤立点（木）」約 90px／枠 100px で最も狭い）。代替テキストは要点を言う。catalog の visual は static・priority 2 で、「3 通りで同じ成分が得られる様子」は描いていないが、priority 2 なので許容
- 用語集の anchor（isolated-vertex・multi-edge・self-loop・forest・complete-bipartite-graph・super-vertex）は docs/guide/glossary.md にまだない。§13.5 により提案で書いてよく、執筆者の報告に 6 語の提案がある。メインが用語集に足さないまま `mkdocs build --strict` すると落ちる（申し送り）
- 執筆者の未解決の点
    1. abc292_d の多重辺：kazun の記事にも明記はない（辺の集合の書き方だけ）。本文は自己ループだけに触れ、辺は入力の 1 本ずつ数える方針なので、多重辺があっても方針は正しい。直す必要はない
    2. values-as-vertices が力試し abc131_f の考え方をそのまま説明している点：この節は catalog の sections（level 青）と signs が求める中身で、問題名も出していない。力試しの方針がこの節を参照する作りは手引きに反しない。このままでよい
    3. `../ds/union-find.md#practice` の参照：union-find.md の練習に abc206_d（値の一括置換）がある。参照は正しい

## 指摘

### 1｜直すべき｜手引き（§13.1）｜front matter の sections と #pitfalls の見出し（25 行・125 行付近）

- **問題**：「落とし穴」は定型の節で、sections に載せず見出しを `## 落とし穴 {#pitfalls}` にする決まり（§13.1。上の各節より優先）だが、sections に `anchor: pitfalls` の行があり、見出しが「落とし穴（孤立点・多重辺・自己ループ・再帰の深さ）」になっている。執筆者も「手引きへの提案」で迷った点として挙げている
- **根拠**：style-guide §13.1。binary-search の検証の指摘 1 と同じ型（ほかにも bit-full-search・bit-operations などに同じ形があるので、メインが一括で決めるとよい）
- **直し方**：sections から pitfalls の行を消し、見出しを `## 落とし穴 {#pitfalls}` にする（anchor は同じなのでリンクは壊れない）。4 項目は節の中の太字の書き出しにすでにある。メインが「catalog が中身の節として持つ pitfalls は sections に残してよい」と決めるなら、この指摘は不要

### 2｜直すとよい｜fact（F4）・clarity（U4）｜#pitfalls の「Union-Find なら、成分の数は『N − 併合に成功した回数』」

- **問題**：ACL の `merge` は代表元を返し、併合したかどうかを返さない。読者が ACL でこの数え方をそのまま書こうとすると、「成功」の判定のしかたが分からない
- **根拠**：document_ja/dsu.md の merge（`int d.merge(int a, int b)`、戻り値は代表元）
- **直し方**：「（ACL なら `if (!d.same(a, b))` で数えてから merge する。最後に `d.groups().size()` でもよい）」と添える

### 3｜直すとよい｜fact（F5）｜練習の方針の ABC157 D「友達は必ず同じ成分にいるので次数をそのまま引き」

- **問題**：次数をそのまま引いてよいのは、友達の組が重複せず、同じ組が友達とブロックの両方に現れない制約があるときだけである。本文にその条件がなく、evidence の drken の記事も条件に触れず、友達とブロック相手を set に入れて重複を除く書き方をしている。検証役は問題文を開けないので、制約を確かめられなかった
- **根拠**：drken「AtCoder ABC 157 D - Friend Suggestions」（答え = `uf.size(i) - dame[i].size() - 1`、dame は同じ成分の友達・ブロック相手の set）
- **直し方**：制約を確かめられたら「制約で友達の組は重複せず、ブロックの組とも重ならないので」と理由を添える。確かめられなければ「友達と、同じ成分のブロック相手を合わせた人数（重複を除く）を引く」と書く

### 4｜直すとよい｜clarity（U9）・fact（F2）｜#three-methods の表と本文の言い過ぎ

- **問題**：(a) 表の DFS・BFS の行「距離や探索の順序も要る」は、距離が分かるのは BFS だけ（DFS では最短距離にならない）。(b)「辺の追加と質問が交互に来るなら Union-Find しか間に合わない」の「しか」は言い過ぎで、理由（毎回探索し直すと $O(Q(N + M))$）もない
- **根拠**：DFS の訪問順は最短距離を与えない（bfs.md・dfs.md の内容）
- **直し方**：(a)「距離（BFS）や探索の順序も要る」。(b)「質問のたびに探索し直すと $O(Q(N + M))$ かかるので、Union-Find を使う」

### 5｜直すとよい｜figure（G5）｜components.svg の枠の線の種類

- **問題**：4 つの成分の枠が実線・破線・実線・点線とばらばらで、凡例がない。読者は線の種類に意味（木となもりの区別など）があると読みかねない
- **根拠**：SVG の `stroke-dasharray`（なもりの枠 `8 4`、右端の枠 `2 4`、ほかはなし）。凡例は「太い線：閉路に含まれる辺」だけ
- **直し方**：枠をすべて実線にそろえるか、意味を持たせるなら凡例に書く

## 総合の判定

小さな直しで可。直すべき 1（§13.1 の pitfalls の扱い。メインの一括の判断しだいで不要）、直すとよい 4。事実・コード・図の値に誤りは見つからなかった。
