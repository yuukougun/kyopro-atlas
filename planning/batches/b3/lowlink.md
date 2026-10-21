# lowlink の報告（b3）

- 書いたファイル：docs/graph/lowlink.md、snippets/lowlink/{lowlink,two-edge}.{cpp,yaml}、docs/img/lowlink/dfs-tree.svg、docs/img/lowlink/bridge-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（6 節とも見出しと title が同じ）
- 構成：level 黄・type technique なので §4 の technique（水・青・黄）。必要になる場面・処理の流れ・計算量は ord-low の節で兼ねた（§14-5）。応用の型は conditions と two-edge-connected の末尾（§14-7）。発展の節 block-cut-tree は見本の lazy-segment-tree にならい、使い分けの後・参考の前に置いた。acl: [] なので ACL の囲みはない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0（2 本）、textlint エラー 0・警告 5（数式の中の読点による max-comma 4 件と、別行の数式の文の長さ 1 件。§13-8 の誤検出として残した）
- コード片の確かめ：lowlink.cpp は、橋の判定と「頂点を除いたときに分かれる個数 pieces[v]」を、辺・頂点を 1 つずつ除いて成分を数える素朴な方法と main の assert で比べる。two-edge.cpp は「同じ成分 ⇔ どの辺を 1 本除いても同じ連結成分に残る」と「橋の数 = 成分の数 − 連結成分の数（森）」を assert で比べる。手元で多重辺・自己ループ・非連結を含む乱択の 500 ケースずつを流し、どちらも一致した
- 落とし穴「後退辺で low[to] を使う」は、lowlink.cpp の該当行を low[to] に替えた版で、本文の例（三角形 2 つが頂点 1 を共有）が頂点の assert で落ち、橋の判定は落ちないことを確かめた（版は snippets に置いていない）
- 図：dfs-tree.svg（DFS 木に ord と low、後退辺は破線の矢印、橋は太線と「橋」の字、関節点は二重丸）と bridge-tree.svg（同じグラフで成分を点線の枠で囲み、縮約した A-B-C の木）。visual は priority 2 の static なので静的な図にした。render_svg.py で 360px・720px を目で確かめた。動く図の置き場は置いていない

## 使った出典

- https://ei1333.github.io/luzhiled/snippets/graph/lowlink.html：ord と low の定義、橋・関節点の条件
- https://ei1333.github.io/luzhiled/snippets/graph/two-edge-connected-components.html：成分の番号付けと縮約。ARC039 D で検証されていること（下の補充の候補の裏付け）
- https://algo-logic.info/articulation-points/：根と根以外で条件が違う理由
- https://blog.hamayanhamayan.com/entry/2016/10/18/123552：橋・関節点の問題の一覧（ARC039 D が「二重辺連結成分分解と橋」の節にあること）
- https://blog.hamayanhamayan.com/entry/2017/10/15/002234：例題 abc075_c（橋の本数、Union-Find の全探索）
- https://amentorimaru.hatenablog.com/entry/2025/04/11/210228：abc334_g を関節点で解く方針（ord(u) ≤ low(v) の子ごとに成分が 1 増え、根は子の数 − 1）
- https://www.cnblogs.com/codwarm/p/18463129：abc375_g を、dis1[x] + c + disn[y] = dis1[n] の辺だけの部分グラフの橋で解く方針
- 新しく noai を確かめたドメイン：algo-logic.info（X-Robots-Tag なし、meta robots は max-image-preview:large のみ）、amentorimaru.hatenablog.com（同じく指定なし）。www.cnblogs.com は付録 B にあるが記事も確かめた（指定なし）
- algo-logic.info/bridge-lowlink/ も noai を確かめたが本文の参考には使っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc075_c | checked | 2026-10-21 | evidence の hamayan の記事で、問い（取り除くと非連結になる辺の数）と全探索の方針を確かめた |
| abc375_g | pages に追加 | {id: lowlink, role: practice}（または example） | 最短路に乗る辺だけの部分グラフの橋が答えになる。https://www.cnblogs.com/codwarm/p/18463129 。evidence にこの URL を足す。approach に「最短路に乗る辺の部分グラフで橋を求めてもよい」を足す |
| abc334_g | pages に追加 | {id: lowlink, role: practice}（または example） | 各マスを除いたときの成分の増分を関節点の条件で数える。https://amentorimaru.hatenablog.com/entry/2025/04/11/210228 。evidence にこの URL を足す |

- 本文では両問を問題の囲みに入れず、応用の型と練習問題の節で label の一部と持ち主のページ（shortest-path-dag#challenge・offline-dynamic-connectivity）へのリンクで触れた。台帳に lowlink の役割が付いたら、練習問題の囲みに移せる（黄のページの例題の目安「難しい F と易しい G」に合うので、例題にしてもよい）
- catalog の problems_note「lowlink が想定の解法だと確かめられた ABC の問題がなく」は、上の 2 件の第三者の解説で「lowlink で解ける」ことは裏付けられた。公式の想定解かどうかは確かめていない（atcoder.jp を開かないため）

## 用語集への提案

- 後退辺｜back-edge｜無向グラフの DFS で、DFS 木に入らなかった辺である。必ず祖先と子孫を結ぶ（有向グラフの DFS では、ほかに前進辺・横断辺がある）。閉路の検出や lowlink で使う。（本文は太字で定義し、リンクは張っていない。check_pages が未定義の anchor をエラーにするため）
- 縮約｜contraction｜グラフの頂点の集まりを 1 つの頂点にまとめ、集まりの中の辺を消し、外へ出る辺を残す操作である。強連結成分や二重辺連結成分を縮約すると DAG や木になる。
- 二重辺連結成分｜two-edge-connected-component｜橋をすべて除いたときの連結成分である。同じ成分の 2 頂点は、どの辺を 1 本除いてもつながったままである。（ページがあるので用語集に置くなら lowlink#two-edge-connected へのリンクだけでもよい）

## 手引きへの提案

- §13-5「用語集へのリンクはまだなくても書いてよい」と、check_pages が用語集にない anchor をエラーにすることが食い違う。どちらかにそろえるとよい（今回は太字にして提案に回した）
- 練習問題を Library Checker で補うページ（problems_note に書いてあるもの）での書き方の決まりがない。今回は「## 練習問題 {#practice}」の中に judge.yosupo.jp へのふつうのリンクの箇条書きを置いた（問題の囲みは atcoder.jp だけの書式なので使っていない）。この形でよいか決めてほしい

## 問題の補充の候補

- abc375_g（ABC375 G. Road Blocked 2、diff 2014）：各道路を通行止めにしたとき 1 から N への最短距離が変わるか。最短路に乗る辺の部分グラフの橋。台帳で確認済み（shortest-path-dag の力試し）。裏付け https://www.cnblogs.com/codwarm/p/18463129
- abc334_g（ABC334 G. Christmas Color Grid 2、diff 2242）：緑のマスを 1 つ一様に選んで赤にしたときの緑の連結成分の数の期待値。関節点で切り離される部分木を数える。台帳で確認済み（offline-dynamic-connectivity の例題）。裏付け https://amentorimaru.hatenablog.com/entry/2025/04/11/210228
- arc039_d（ARC039 D. 旅行会社高橋君、diff 2550 参考値）：A から B を経て C へ、同じ橋を 2 回通らずに行けるか。二重辺連結成分で縮約した木の上で、B の成分が A と C の成分を結ぶ道に乗るかを LCA の距離で判定する。台帳にない。裏付け https://ei1333.github.io/luzhiled/snippets/graph/two-edge-connected-components.html （この問題で verify）と https://blog.hamayanhamayan.com/entry/2016/10/18/123552 （一覧の「二重辺連結成分分解と橋」の節）。力試し向き。本文の two-edge-connected の応用の型で、問題 ID を出さずに型だけ書いた
- 見つけたが難しすぎる・裏付けを読んでいない候補：tenka1_2015_qualA_d（D. ハシポン、diff 2559 参考値）、arc045_d（D. みんな仲良し高橋君、diff 3039 参考値）、arc062_d（F. Painting Graphs with AtCoDeer、diff 3175）。どれも hamayan の一覧にあるだけで、解説は読んでいない

## 未解決の点

1. abc075_c の制約（M の上限、多重辺・自己ループがないこと）は確かめていない。本文では「N ≤ 50 と小さい」とだけ書いた
2. abc375_g・abc334_g が lowlink のページの問題の囲みにない（台帳の役割が別ページのため）。台帳の提案が通ったら、練習問題の節の文章を囲みに置き換える必要がある
3. block-cut-tree の節の「孤立点を 1 点だけのブロックとして数えるかは問題の定義に合わせる」は、Library Checker の biconnected_components の出力の定義を確かめていない
4. メンガーの定理（辺の版）は名前だけ出して証明していない。用語集かリンク先が要るかはメインの判断に任せる
5. handoff §1 の 8 か所（cycle-detection:161・dfs:129・graph-basics:81・namori-graph:189・scc:115・scc:199・scc:267・shortest-path-dag:187）は、それぞれ次へ張り替えられる：cycle-detection:161・namori-graph:189・shortest-path-dag:187 → #conditions、dfs:129 → #ord-low、graph-basics:81 → #multi-edges、scc:115・scc:267 → #vs-scc、scc:199 → #two-edge-connected（あるいはページのまま）

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 7 回、検索 3 回

## 検証の指摘への対応（b3 verify）

- 指摘 1〜4（直すとよい）はすべて採った：擬似コードの else の注釈を「祖先の側から見た同じ辺も来る」に、最短路の応用の型の理由を「ほかの最短路の辺は u より手前か v より先にしかない」に、確認問題の条件を「v のほかに隣の頂点があるか」（単純グラフなら次数 2 以上と同じ）に直し、block-cut-tree に Library Checker は孤立点を 1 点の成分として出力することを書き足した
- 採らなかった指摘：なし
- 台帳への提案（abc075_c の制約の資料、abc334_g・abc375_g の pages と evidence）は検証の記録のとおりで、メインに任せる
