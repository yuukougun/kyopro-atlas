# counting-labeled-graphs の検証（b3）

- 対象：docs/comb/counting-labeled-graphs.md、snippets/counting-labeled-graphs/{connected-count,subset-connected,farthest-layers}.{cpp,yaml}、docs/img/counting-labeled-graphs/{component-of-1,bfs-layers}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py counting-labeled-graphs`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視。720px の PNG は道具の高さの見積もり（SVG に width がないので固有幅 480 で計算し、Chrome は全幅に広げる）のせいで下が切れるので、全体は 360px の PNG で確かめた（図の問題ではない）
- atcoder.jp・codeforces.com は開いていない。読んだのは参考の drken の 3 記事だけ（付録 B のドメイン）

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page counting-labeled-graphs`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/counting-labeled-graphs`：connected-count 3 case・farthest-layers 6 case・subset-connected 6 case すべて一致
- サニタイザ（`-fsanitize=address,undefined`）：connected-count（N = 20）、farthest-layers（n = 2・3、mod 7）、subset-connected（3 頂点 2 辺）で異常なし。最大の大きさ：farthest-layers は n = 500・mod 999999937 で 0.15 秒、subset-connected は N = 17・M = 60 で 0.10 秒
- 数値（Python で計算）：c(1..7) = 1, 1, 4, 38, 728, 26704, 1866256（本文の値と一致）。$n = 3$ の全列挙の表と $c(3)$ の計算。誤った式（残りを $c$ で掛ける）を再帰で使うと 1, 1, 5, 41（落とし穴と確認問題 1 の 5・41 と一致）。逆向きの式 $a(n)$ で $h = c$ とすると $n \le 7$ で $a(n) = g(n)$。距離の層の DP（$R = n - 1$、$\mathrm{dp}[0][1] = 1$）の $\sum_j \mathrm{dp}[R][j]$ が $n \le 7$ で $c(n)$ と一致（層の DP の正しさ）。$3^{17} = 129140163 \approx 1.3 \times 10^8$。$500 \cdot 499 / 2 = 124750$
- 頂点集合の DP：式・計算の順・$e(S)$ の求め方・`(rest - 1) & rest` から始める理由・回数が $3^N$ の半分ほど（$\sum_S 2^{\lvert S \rvert - 1}$）。正しい
- 例題 ABC281 G：台帳（確認済み、diff 2304）と label・要約が一致。drken の記事で 3 ≤ N ≤ 500・10^8 ≤ M ≤ 10^9（素数とは限らない）、O(N^3)、パスカルの三角形を確かめた。記事は頂点 N から逆向きに層を作るが、本文の前向きの形もコード片の全探索（n ≤ 6）と一致し、食い違いはない
- 練習 ABC180 F：drken の記事で、自己ループなし・多重辺あり・M ≤ N ≤ 300・mod 10^9+7、最小の未使用の頂点を含む成分を選ぶ係数 $\binom{N-n-1}{k-1}$、パスは $k!/2$（$k = 1$ は 1）、サイクルは $(k-1)!/2$（$k = 2$ は 1）、$f(L) - f(L-1)$ を確かめた。方針の DP を Python で書き、N ≤ 5・全 M・全 L で多重辺の全列挙と一致（執筆者の未解決の点 1「頂点は区別する」も、全列挙が番号付きで数えて一致したので正しい）
- 力試し ABC213 G：drken の記事で単純グラフ・N ≤ 17・mod 998244353、$f(S) = 2^{e(S)} - \sum f(T) 2^{e(S \setminus T)}$（$v \in T \subsetneq S$）、答え $\sum_{S \ni 0, k} f(S) 2^{e(V \setminus S)}$、$O(3^N)$ を確かめた。記事は 0-indexed の k = 1..N−1 で、本文の 1-indexed の k と同じ
- 参考の 3 つの URL：題名は記事の h1 どおり、内容も書かれたとおり
- 本文は自分の例（n = 6 の図、n = 3・4 の値）で、記事の文・例の写しはない（F8）
- 図：component-of-1 は T = {1, 3, 4}（辺 1–3・3–4 で連結）、残り {2, 5, 6}、C(5, 2) で代替テキストと一致。bfs-layers は各層の頂点が前の層と 1 本以上結ばれ、2 層離れた辺がなく、代替テキストと一致。白背景・viewBox・font-family="sans-serif"・相対パス。360px でも文字は読める

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2 | #by-size の「応用の型」2 つ目 | 「連結な二部グラフや連結な森も同じ形である。全体を数えてから、頂点 1 の成分で分けて引く」は 2 つとも成り立たない。森は「全体」が先に分からず、連結なもの（木、$n^{n-2}$）から逆向きの式 $a(n)$ で森を組み立てる向きである。二部グラフは「二部グラフの全体」を直接は数えられず、2 色に塗ったグラフ $b(n) = \sum_k \binom{n}{k} 2^{k(n-k)}$ を全体にし、連結な塗ったグラフを引き出してから 2 で割る（連結な二部グラフの塗り方はちょうど 2 通り）という手順が要る。このまま読むと読者は二部グラフの全体を数えようとして止まる | Python で $b(n)$ から引いて 2 で割ると 1, 1, 3, 19, 195, 3031（n = 1..6、連結な二部グラフの数の既知の列）。森は $c$ の代わりに $n^{n-2}$ を $h(k)$ に入れる向き | 「連結な森（木からなる）は逆向き：$h(k) = k^{k-2}$（[Prüfer 列](../comb/cayley-pruefer.md)）を入れて $a(n)$ で組み立てる。連結な二部グラフは、2 色に塗ったグラフの全体 $\sum_k \binom{n}{k} 2^{k(n-k)}$ から連結な塗ったグラフを引き出し、2 で割る（連結なら塗り方は 2 通り）」のように、それぞれの向きと手順を書く |
| 2 | 直すとよい | clarity U4 | #bfs-layers の DP の式の後 | 一般の節で、DP を回し終えた後の答え（連結なグラフ全体なら $R = N - 1$ で $\sum_j \mathrm{dp}[R][j]$）が書かれていない。$R$ も「層に配る頂点の数」とだけあり、ふつうは $N - 1$ であることが例題まで出てこない | 本文。$\sum_j \mathrm{dp}[N-1][j] = c(N)$ は Python で $n \le 7$ を確かめた | 「頂点 1 以外のすべてを配るなら $R = N - 1$ で、$\sum_j \mathrm{dp}[R][j]$ が連結なグラフの数 $c(N)$ になる（どの頂点も頂点 1 から届くので）」を 1 文足す。小さい検算（$N = 4$ で 38）を添えるとなおよい |
| 3 | 直すとよい | clarity U3 | #subset-dp の「応用の型」2 つ目 | 「$S$ の中の端子をすべて対にする方法の数なら $f(S)$ は階乗で数えられ」の「端子」が定義されず、何を対にするのか（各頂点に何個の端子があるのか）分からない。読者はどんな問題の形かを思い浮かべられない | 本文 | 「各頂点に決まった数の端点があり、$S$ の中の端点を 2 つずつ組にして辺にする方法なら、端点が $2m$ 個のとき $f(S) = (2m - 1)!! = (2m)!/(2^m m!)$」のように、何を数えるかと式を書く。書けないなら箇条ごと外す |
| 4 | 直すとよい | figure G5 | bfs-layers.svg の頂点 7 | 頂点 7 だけ赤い太い枠だが、凡例にも代替テキストにも意味の説明がない（例題 ABC281 G の「最も遠い頂点」を示すつもりと読めるが、この節の図としては根拠がない） | 360px の PNG を目視。SVG の `stroke="#b03030" stroke-width="3"` | ほかの頂点と同じ色にするか、凡例に「最後の層」などの説明を 1 行足す |
| 5 | 直すとよい | clarity U6 | #by-size の 1 段落目「[連結の節](#component-of-1)の式」 | リンクの文字「連結の節」がどの節か分かりにくい（「連結」で始まる節は #complement で、リンク先は #component-of-1） | 本文と見出し | 「[頂点 1 の成分で分類する節](#component-of-1)の式」とする |
| 6 | 直すとよい | clarity U9 | #component-of-1 の最後の段落・落とし穴 1 つ目・確認問題 1 つ目 | 「残りを $c$ で掛けると成分がちょうど 2 つのものしか引かれない」が 3 か所で同じ言い方でくり返され、落とし穴と確認問題は同じ値 41 まで出す。確認問題の答えが落とし穴に書いてある | 本文 | #component-of-1 の段落は理由だけにして、落とし穴は「$n = 4$ で値がずれる（確認問題）」と短くし、値 41 は確認問題の答えにだけ置く |
| 7 | 直すとよい | fact F5 | 練習問題の節 | 練習が 1 問で、手引き §10 の目安（練習 2〜6）を下回る（執筆者の未解決の点 3） | 手引き §10 | メインが判断する。執筆者の候補 abc389_g（距離の層＋偶奇＋辺の数）は難しく、力試しの方が合う |
| 8 | 直すとよい | fact F7 | #comparison の表と #bfs-layers ほか | 執筆者の未解決の点 4 のリンク：cayley-pruefer と zeta-mobius-subset はいま stage: draft で、節へ張り替えられる（cayley-pruefer#cayley、zeta-mobius-subset の節は exp・log を直接扱う anchor がないのでページのままでよい）。matrix-tree-theorem は stub のまま。また #subset-dp の「$S$ の最小の頂点を代表」は [subset-enumeration-dp#fix-minimum](../dp/subset-enumeration-dp.md#fix-minimum) にリンクできる | 各ページの front matter（stage・sections） | メインが張り替える（手引き §14-23）。fix-minimum へのリンクは任意 |

## 執筆者の未解決の点について

- abc180_f の頂点は区別する：正しい（上の「確かめたこと」の全列挙と一致）
- ABC281 G を前向きの層で書いた：正しく、記事の逆向きの形と同じ数を数える（全探索 n ≤ 6、本文の層の DP で $n \le 7$ の $c(n)$ も一致）
- 練習が 1 問：指摘 7
- stub へのリンク：指摘 8

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc180_f | summary（本体と alternatives の 2 つ） | 自己ループのない（多重辺は許す）N 頂点 M 辺の無向グラフで、各連結成分がパスかサイクルで、最大の連結成分の頂点数がちょうど L のものの数を求める。 | 執筆者の提案に賛成。台帳の「単純無向グラフ」は誤り（drken の記事：多重辺あり、大きさ 2 のサイクルは二重辺）。本文の行はすでに直っている |
| abc180_f・abc213_g | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2020/10/21/145700、https://drken1215.hatenablog.com/entry/2021/08/12/132500 で問いと制約を確かめた |

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 7）。直すべきは指摘 1（応用の型の 1 行の誤り）だけで、式・コード片・例題の解き方・図はすべて確かめて正しかった。
