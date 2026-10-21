# lowlink の検証（b3）

- 対象：docs/graph/lowlink.md、snippets/lowlink/{lowlink,two-edge}.{cpp,yaml}、docs/img/lowlink/{dfs-tree,bridge-tree}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py lowlink`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目で確かめた
- atcoder.jp・codeforces.com は開いていない。試しのコードは scratchpad（v-lowlink/bf.py）に置き、リポジトリには置いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page lowlink`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page lowlink`：直すべき行 0
- `python3 tools/check_snippets.py -v snippets/lowlink`：2 本・10 case すべて一致。lowlink.cpp・two-edge.cpp とも、main の assert が素朴な方法（辺・頂点を 1 つずつ除いて成分を数える）と比べている。cases は 1 頂点・本文の図・多重辺・パス・星形と自己ループと孤立点・閉路を含む
- front matter：執筆者が変えたのは complexity・stage だけ（git diff）。complexity と要点の計算量が一致。別名の行に aliases がすべてある
- 本文の主張を Python で乱択（N ≤ 7、M ≤ 10、多重辺・自己ループ・非連結を含む 5000 例）で確かめた（v-lowlink/bf.py）：
    - 辺の番号で親を除く実装の橋・関節点は全探索と一致
    - 落とし穴「後退辺で low[to] を使う」：橋の判定は 5000 例すべて一致、関節点は 50 例で誤る（本文の「橋の判定は変わらないが、関節点を見落とす」のとおり）。本文の例（三角形 {0,1,2} と {1,3,4}、0→1→2→3→4）も手で追って頂点 1 を見落とすことを確かめた
    - 多重辺の節「親を頂点で除くと橋を誤るが、関節点は誤らない」：自己ループを除いたグラフで、頂点で除く実装の関節点はすべて一致、橋は 1423 例で誤る
    - vs-scc の「Tarjan と同じスタックで low[v] = ord[v] なら v までを取り出すと二重辺連結成分が求まる」：「どの辺を 1 本除いても同じ成分に残る」と全例一致
    - block-cut-tree の求め方（木の辺と祖先へ向かう後退辺を積み、low[c] ≥ ord[p] で辺 {p,c} まで取り出す。根でも同じ）：各辺がちょうど 1 つのブロックに入り、頂点を 1 つ除いて分かれる辺の組と別のブロックになることが全例一致
    - 応用の型「すべての最短路が通る辺 ⇔ 最短路に乗る辺の部分グラフの橋」：重み 1〜3 の乱択 3000 例で、辺を除いてダイクストラし直した結果と一致
- 理論の確認：low[c] が ord[c] か ord[p] 以下のどちらかになること（後退辺は祖先と子孫だけを結ぶため）、pieces（根は s_v、根以外は s_v + 1、孤立点は 0）、根の判定、二重辺連結成分の縮約が森になること、ARC039 D 型（「同じ橋を 2 回渡らない」なら B の成分が A–C の木の道に乗るか）は正しい
- 図 dfs-tree：ord 0〜6、low 0・0・0・3・3・3・6、橋 1-3 と 5-6、関節点 1・3・5 を手で計算し直して一致。後退辺の矢印の向き（2→0、5→3）、凡例、文字の重なり・はみ出しなし。360px でも読める
- 図 bridge-tree：成分 A・B・C と橋 1-3・5-6、縮約した A-B-C が本文と一致。白背景（rect fill #ffffff）・viewBox・font-family="sans-serif"・相対パス。代替テキストに値がある
- 問題：`tools/ap.py show` で abc075_c（C. Bridge、diff 1067）・abc334_g（diff 2242）・abc375_g（diff 2014）が実在し、本文の表記と一致。例題の要約に手法名なし
- ABC334 G・ABC375 G の方針：amentorimaru の記事（ord・low で子ごとに判定、根は子の数で）と codwarm の記事（dis(1,x) + c + dis(y,n) = dis(1,n) の辺の部分グラフで Tarjan 法の橋）で、本文の応用の型の方針と食い違いなし
- 参考の URL：ei1333・algo-logic・hamayan（2 件）・amentorimaru・codwarm を `tools/check_noai.py` で確かめ、どれも noai の指定なし。題名と内容は書かれたとおり
- Library Checker：yosupo06/library-checker-problems の task.md で、two_edge_connected_components は「単純とは限らない」（自己ループも制約で除かれていない）、biconnected_components は「単純とは限らないが自己ループはない」を確かめた。本文の「多重辺を含むので」は正しい
- コード：手引き §9 の DFS の形（`auto dfs = [&](auto&& self, int v, int pe) -> void`）、`'\n'`、マクロなし。本文の擬似コードと変数名（k・ord・low・pe・to）がそろう
- F8：図の例（三角形 2 つを橋でつなぎ尾を付けたグラフ）と本文の文は参考の記事の写しではない

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact F2 / clarity U3 | ord-low の擬似コード、else の行の注釈「後退辺（または子孫から見た同じ辺の裏側）」 | else に来るのは「子孫の側から見た後退辺」と「祖先の側から見た同じ後退辺」の 2 つで、裏側は祖先から見たものである。「子孫から見た裏側」は逆で、直後の段落（「祖先の側から見ると、行き先は子孫なので…」）とも食い違って読める | 擬似コードの分岐を追うと、ord[to] > ord[v] で else に来るのは v が祖先のとき | 「後退辺（祖先の側から見た同じ辺も来るが、min に影響しない）」のようにする |
| 2 | 直すとよい | fact F2 / clarity U2 | conditions の応用の型「すべての最短路に含まれる辺」の理由の文 | 「その辺を除いても 1 と N がつながるなら、その辺を通らない最短路が残るから」は、部分グラフの中の道が最短路とは限らない（無向なので辺を逆向きにたどれる）ので、そのままでは理由にならない。主張自体は正しい（乱択で確かめた） | 正しい理由：e = {u, v}（dist₁[u] < dist₁[v]）がすべての最短路に乗るなら、ほかの最短路の辺は両端とも dist₁ が dist₁[u] 以下か dist₁[v] 以上なので、e を除くと dist₁ の小さい側と大きい側を結ぶ辺がなくなる | 「すべての最短路が e = {u, v} を通るなら、ほかの最短路の辺は u より手前か v より先にしかなく、e を除くと 1 の側と N の側が切れる」と言い換える。あるいは理由を shortest-path-dag#challenge に任せて 1 文で済ませる |
| 3 | 直すとよい | fact F2 | 確認問題「橋の両端は関節点か」の答え「次数が 2 以上なら関節点である」 | 本文のコードは自己ループを許すが、u が橋 {u, v} と自己ループだけを持つと次数は 3 でも関節点でない。条件は次数ではなく「v のほかに隣の頂点がある」 | u–v の橋に u の自己ループを足したグラフで、u を除いても残りは v だけで連結 | 「u に v 以外の隣の頂点があれば関節点である」とし、図の頂点 6 の説明もそれに合わせる（単純グラフなら次数と同じと添えてもよい） |
| 4 | 直すとよい | fact F5 | block-cut-tree の「辺のない孤立点を 1 点だけのブロックとして数えるかは、問題の定義に合わせる」（執筆者の未解決の点 3） | Library Checker の Biconnected Components では、孤立点も 1 頂点の成分として出力する。本文はその直後に同じ問題で確かめるよう書いているので、ここで答えを示すと読者が迷わない | library-checker-problems の graph/biconnected_components/sol/correct.cpp（`// single vertex component` で孤立点を 1 点の成分にして出力）。example_02 は孤立点 3 つを含む | 「Library Checker の Biconnected Components では孤立点も 1 点の成分として出力する」と書き足す |

## 執筆者の未解決の点について

1. abc075_c の制約：台帳の evidence（e869120 の Qiita・hamayan の記事）はどちらも制約を書いておらず、N ≤ 50・M の上限・単純であることは確かめられなかった（hamayan のコードの配列は 101）。本文は台帳の summary と同じ「N ≤ 50 の連結な無向グラフ」で、全探索が間に合うという主張は N ≤ 50 なら M が何であっても成り立つ。本文の直しは要らないが、台帳の summary の N ≤ 50 を確かめる資料はメインで探してほしい
2. abc375_g・abc334_g を囲みに入れない扱い：台帳の役割が別ページなので今の書き方でよい。台帳の提案に同意する（role は practice が妥当。例題は持ち主のページだけにある規則のため）
3. 指摘 4。Library Checker は孤立点を 1 点の成分として数える
4. メンガーの定理：名前だけで本文の理解に支障はない。そのままでよい
5. handoff の張り替え先の対応：各リンク先の anchor（ord-low・conditions・multi-edges・two-edge-connected・vs-scc）はページに存在する

## 台帳への提案

- abc075_c：checked は、制約を確かめる資料が見つかるまで入れない（上の 1）。内容（橋の本数を数える、全探索で解ける）は hamayan の記事で確かめた
- abc334_g・abc375_g：pages に {id: lowlink, role: practice} を足し、evidence に amentorimaru・codwarm の記事を足す執筆者の提案に同意

## 総合の判定

小さな直しで可（直すべき 0・直すとよい 4）。どれも 1〜2 文の差し替えで直る
