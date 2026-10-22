# tree-path の問題の補充（b6・工程9）

- ページ：docs/tree/tree-path.md（レベル 青）。今の練習は abc133_f（diff 2330）の 1 問。例題は abc152_f、力試しは abc298_h
- 探したところ：
    - (1) b1・b3・b5 の summary/candidates.md と b2 の報告 planning/batches/b2/tree-path.md。b3 と b2 に abc014_4・abc267_f・typical90_ai（どれも持ち主は lca）が挙がっている。b1 は abc298_h（既に力試し）だけ、b5 には tree-path の記載なし
    - (2) data/problems.yaml で pages に tree-path を持つ問題は abc152_f・abc133_f・abc298_h の 3 問で、どれも本文にある。本文にない問題はない
    - (3) `python3 tools/ap.py search` で題名に Path・Tree・Paths・Road・Median・Cross を含む diff 1100〜2500 の問題を一覧にし、パスの判定の式が効きそうなものを第三者の解説で確かめた。arc142_c を新たに見つけた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- このセッションでは Web 検索の上限に達し、検索が使えなかった。解説は付録 B のブログの記事内検索（はてなブログの /search）と URL の規則から探したので、探し方は狭い。候補はもっとあるかもしれない
- 候補 1 問を足すと練習は合わせて 2 問になる（目安の下限）

## 候補

### arc142_c（新規。台帳になし）

- 問題ID：arc142_c
- 題名：C. Tree Queries
- difficulty：1347（水）
- 役割：practice（ページの帯（青）より下だが、「点 x がパス上にあるか」の式そのものを使う入門の練習として置く。帯の外なので、メインの判断で外してもよい）
- 要約：形の分からない木で、2 頂点の距離を尋ねる質問を繰り返して、頂点 1 と頂点 2 の距離を当てるインタラクティブの問題である。
- 方針の要点：1・2 以外の各頂点 x について d(1,x) と d(2,x) を尋ねると、x がパス 1–2 の上にあるとき和が d(1,2) になり外れると大きくなるので和の最小が答えになるが、パス上にほかの頂点がない（d(1,2)=1）ときと区別が付かない場合（最小の和が 3 になる場合）だけ、和が最小の 2 頂点の距離を 1 回尋ねて分ける。
- 裏付け：
    - https://merom686.hatenablog.com/entry/2022/06/20/000753 （C の節。「最短経路上にある頂点からの距離の和が求める距離になる」こと、(N−2)×2 回の質問、距離 1 の場合の区別に和が最小の 2 頂点の距離を尋ねることを確かめた。merom686.hatenablog.com は付録 B にある）
    - 2 つ目は見つけられなかった（kmjp・drken1215・kanpurin・merom686 のはてなの記事内検索、ikatakos の ARC142 のページ（D だけ）、kazun-kyopro の URL の規則を試した）
- 台帳への追加の提案：pages に {id: tree-path, role: practice}、anchor は on-path。summary・approach は上の要約・方針の要点を使う

## 検討して足さなかったもの

- abc267_f（Exactly K Steps、diff 1939）：既に lca の例題と tree-diameter の練習。kazun-kyopro の解説（https://kazun-kyopro.hatenablog.com/entry/ABC/267/F）は直径の端点を根にして K 個上の祖先を求める解き方で、パスの K 番目の頂点（上ってから下る分解）を使っていない。一般の根で解くなら kth-on-path の練習にもなるが、3 ページ目に重ねる利点は小さい
- typical90_ai（Preserve Connectivity）：既に auxiliary-tree の例題と lca の練習。DFS 順で隣り合う 2 点の距離の和の半分で、合流点の考えの一般化ではあるが、このページの判定の式を使う問題ではない
- abc014_4（閉路）：lca の例題。閉路の長さ＝距離＋1 で、距離の式だけで済み、パスの判定・分解を使わない
- abc148_f（Playing Tag on Tree、diff 1457）：tree-distance の練習。2 点からの BFS で済み、LCA を使わない
