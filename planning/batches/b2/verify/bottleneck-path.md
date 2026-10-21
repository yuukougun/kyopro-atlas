# bottleneck-path の検証（b2）

- 対象：docs/graph/bottleneck-path.md、snippets/bottleneck-path/{pair,many-queries,matching}.{cpp,yaml}、docs/img/bottleneck-path/{graph,reconstruction-tree}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py bottleneck-path`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page bottleneck-path`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/bottleneck-path`：pair 5 case・many-queries 4 case・matching 5 case すべて一致
- `npx textlint docs/graph/bottleneck-path.md`：エラー 0・警告 3（文の長さ。要点の囲み・図の代替テキスト・折りたたみの中。§13-8・§14-25 の範囲）
- 乱択の比較（作業場所で実行）：3 本を `-fsanitize=address,undefined` 付きでコンパイルし、n ≤ 7・m ≤ 10、重みの範囲 3・10・10^9 の乱択 400 ケースずつを流した。pair は Python の素朴な方法（しきい値ごとの連結判定）と全一致。many-queries と matching は main の assert（素朴な方法・B の並べ方の全探索）がすべて通り、サニタイザの報告もなし。s = t・非連結・同じ重みの辺・多重辺を含む
- many-queries の速さ：N = 2×10^5 のパス状のグラフと Q = 2×10^5 の質問（端点の片方を 0 に固定）で 0.03 秒
- many-queries の正しさの議論（2 つの写しが端点の成分の一覧に必ずあること、短い方だけを見て見つかること、答えの出た写しを読み飛ばすこと）と計算量の議論（一覧の長さで入れ替えても、頂点数の小さい成分の写しに数えれば O(Q log N)）：正しい
- カット性質の議論（why-mst）・判定の単調性・同じ重みの辺・非連結（最小全域森）・最小全域木が複数あるときの確認問題：正しい
- 図の例：b(1, 4) = 5、経路 1-3-4 は 6、1-2-5-4 は 7。併合の順 2・3・4・5 と併合過程の木の形、LCA(1, 4) = 根（重み 5）。本文・2 枚の図・代替テキスト・コード片の cases（0-indexed で同じグラフ）がそろっている
- ABC383 E の貪欲の最適性の証明（しきい値ごとの上限 Σ min(a_c, b_c) にすべての x で等しい）：正しい
- 確認問題：ダイクストラ法の緩和を max にする方法、和の最短路の反例（10 と 6・6）：正しい
- 例題・練習：`tools/ap.py show` で abc383_e（diff 1616）・abc181_f（2009）・abc394_g（2031）が実在し、label・diff・要約が台帳と一致。catalog の役割（example 1・practice 2）とも一致
- abc383_e：Lanly の記事で、f の定義・B の並べ替え・併合のたびに成分の A と B の残りの数から組を作る方針を確かめた
- abc394_g：kmjp の記事で、答えの式（h < min なら Y + Z − 2h、そうでなければ |Y − Z|、同じ建物は |Y − Z|）と、高い順に併合してクエリの集合を小さい方から移す方針を確かめた。本文の「min(Y, Z) ≤ h なら |Y − Z|」と同じ
- abc181_f：drken の記事で、N ≤ 100、壁は y = ±100、釘・上下の壁の N + 2 頂点、距離の順に併合して上下がつながった距離の半分が答え、O(N^2 log N) を確かめた。記事は壁どうしの辺を張らないが、N ≥ 1 で通路の中に釘があるので、壁どうしの辺（200）を足しても答えは変わらない
- ACL の囲み：document_ja/dsu.md と照らし、merge の戻り値（代表元）・same・size・ならし O(α(n)) は正しい
- 参考の 4 つの URL：どれも付録 B のドメイン（www.cnblogs.com・drken1215.hatenablog.com・kmjp.hatenablog.jp・github.com）で、内容は書かれたとおり
- リンク先の anchor：minimum-spanning-tree の kruskal-prim・why-correct・quiz・maximum、union-find-connectivity の binary-search・threshold、binary-search-answer の minimax、union-find-applications の abc214_d、small-to-large の relabel-smaller、lca の path-aggregate・farthest-ancestor、glossary の cut がすべてある。stub の merge-process-tree・parallel-binary-search・partially-persistent-union-find は anchor なしのリンクで §14-23 どおり
- 図：白背景・viewBox あり・font-family="sans-serif"・相対パス。360px でも数字・ラベルは読める。catalog の visual（static・priority 2、再構築木で LCA の重みが答えになることを示す）を満たす

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F1・F10 | front matter の `complexity` と要点の「計算量」 | Q 組のオフラインの計算量が、front matter は `O(M log M + Q log N)`、要点と本文 many-queries の節は $O(M \log M + Q \log N \cdot \alpha(N))$ で食い違う | F1「3 か所が一致しているか」、F10 のよくある失敗「complexity と要点の計算量が違う」 | front matter を `Q 組はオフラインで O(M log M + Q log N α(N))` にそろえる（または要点と本文から α を落としてそろえる） |
| 2 | 直すとよい | code C3・clarity U4 | 例題 ABC383 E の解法の詳細と matching.cpp の 12〜15 行 | コードは最初に「同じ頂点の A と B を重み 0 で組にする」が、本文の方針・解法の詳細にこの処理の説明がない。読者は取り込んだコードのこのループで止まる（執筆者の未解決の点 1：A_i ≠ B_j の保証を確かめられなかったための処理） | コードと本文を 1 行ずつ対応させて | 解法の詳細の最初に「同じ頂点にある A と B は、重み 0 で先に組にしておく（成分が 1 頂点のときの min(a, b) 組にあたる）」と 1 文足す |
| 3 | 直すとよい | clarity U3・U9 | 例題 ABC383 E（方針と解法の詳細） | 記号 x・y が 3 通りに使われる。方針では f(x, y) の頂点、解法の詳細の 1 段落目では残っている A と B の数、証明の段落ではしきい値 x。1 段落目の文は 133 字で条件も多い | 本文 166・169・175 行 | 残りの数を $p, q$（または $c_A, c_B$）に変え、1 段落目を「併合後の残りの数を求める」「min 組を作って足す」の 2 文に分ける |
| 4 | 直すとよい | fact F4・clarity U4 | kruskal-order の「ACL では」の囲み | 囲みは merge・same・size を説明するが、many-queries.cpp と matching.cpp が使う `d.leader(a)` がない。逆に size はページのコードで使わない | document_ja/dsu.md の leader（代表元を返す、ならし O(α(n))） | 「`d.leader(a)` は a の成分の代表元を返す」を足す（size は残しても外してもよい） |
| 5 | 直すとよい | fact F7 | why-mst の「カットを渡る辺」 | 用語集の cut の項は「カットを横切る辺」と呼ぶ。リンク先と言い方が違う | docs/guide/glossary.md 225 行 | 「カットを横切る辺」にそろえる |
| 6 | 直すとよい | fact F7 | 見出しと sections の title「Kruskal の順に成分を併合しながら答える」 | 手引き §14-22 と付録 A の表記はクラスカル法で、本文もクラスカル法を使う。見出しだけ「Kruskal」になっている（「Kruskal 再構築木」は別名なのでよい） | 手引き §14-22 | 見出しと title を「クラスカル法の順に成分を併合しながら答える」にする（anchor は変えない。§13-2） |
| 7 | 直すとよい | fact F9 | 参考の 1 行目「~Lanly~」 | ほかのページ（functional-graph・extended-dijkstra・small-graph-brute-force）は同じ著者を「Lanly」と書いている。ページの間で表記が違う | grep の結果 | 「Lanly」にそろえる |
| 8 | 直すとよい | 書き方（§14-25） | 応用の型（98〜102 行）・many-queries の 2 つの方法（128〜129 行）・reconstruction-tree の箇条書き（143〜144 行）・落とし穴・練習の方針・使い分け | 箇条書きの各行が句点で終わっていない。§14-25「箇条書きの各行は句点で終える」に合わない（要点の囲みは手引きの見本どおりでよい）。ほかの b2 の検証（divisor-inclusion-exclusion の 9）と同じ指摘 | 手引き §14-25 | 文の形の行の末尾に句点を足す |

## 執筆者の未解決の点について

1. abc383_e の A_i ≠ B_j と制約：evidence の Lanly の記事にも制約の記述はなく、確かめられなかった。matching.cpp は保証がなくても正しい（乱択 400 ケースで全探索と一致、同じ頂点の A・B を含む）。本文の説明の欠けは指摘 2
2. minimum-spanning-tree の 214・288 行と union-find-connectivity の 159 行の張り替え：#why-mst と #kruskal-order はどちらもあり、張り替えてよい（メインの作業）
3. stub への anchor なしリンク：§14-23 どおりで問題なし
4. merge-process-tree との重なり：reconstruction-tree の節は作り方・LCA の重み・行ける範囲の区間の要点だけで、証明とコードを持たない。持ち主は merge-process-tree（catalog/guide.yaml の kruskal-reconstruction-tree の記録とも合う）でよく、このページは今の概要のままでよいと考える。決めるのはメイン
5. 練習 2 問が diff 2000 超：数は目安（2〜6）を満たす。青のページの練習としては難しめなので、執筆者の提案の abc214_d（diff 1341、台帳で確認済み）を practice に足すかはメインが決める

## 台帳への提案

- abc383_e：checked を 2026-10-21 に（Lanly の記事で問いと方針を確かめた。今は null）
- abc181_f・abc394_g：evidence で問いと方針を確かめた。checked はすでに 2026-10-21

## 総合の判定

小さな直しで可。直すべき 1 件（front matter の計算量の食い違い）・直すとよい 7 件。定理・数値・コード・図に誤りは見つからなかった。
