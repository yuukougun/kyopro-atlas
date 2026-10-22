# steiner-subtree の問題の補充（工程9・b6）

ページ：docs/tree/steiner-subtree.md（レベル 基礎）。例題は abc368_d、練習・力試しは 0 問。

## 確かめた候補（2問、どちらも力試し）

### typical90_ai
- 題名：035. Preserve Connectivity（★7）
- difficulty：なし（ap.py で実在を確認。典型 90 問のため diff が付かない。★7 は青〜黄の目安）
- 役割：challenge
- 要約：木と多数のクエリが与えられ、各クエリで指定された頂点をすべてつなぐのに必要な辺の数の最小値を答える問題である。
- 方針の要点：指定頂点を行きがけ順に並べ、隣り合う 2 点（最後と最初も）の距離を LCA で求めて足し、2 で割る（このページの「上位の手法へのつながり」の 1 つ目そのもの）。
- 裏付け：
  - https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp（行きがけ順に並べて depth[v] − depth[lca(v, 次)] を足す実装を読んで確かめた）
- 注：台帳では auxiliary-tree の example・lca の practice。このページでは力試しとして pages に足す提案（1 クエリなら本文の O(N) で解けるが、クエリが多いので次の段への橋渡しになる）。b1 の報告にも同じ提案があった

### abc149_f
- 題名：F. Surrounded Nodes
- difficulty：2208（黄、ap.py で確認）
- 役割：challenge
- 要約：木の各頂点を確率 1/2 で黒に塗り、黒い頂点をすべて含む最小の部分木に含まれる白い頂点の数の期待値を求める問題である。
- 方針の要点：頂点 v が答えの木に入るのは v を除いた成分のうち 2 つ以上に黒があるとき（辺で見れば両側に黒があるとき、本文の 1 ≤ c[v] ≤ K−1 の条件）なので、各頂点・各辺について確率を求め期待値の線形性で足す。
- 裏付け：
  - https://kmjp.hatenablog.jp/entry/2019/12/30/0930（「v を取り除いた成分の 2 つ以上に黒がある」で判定し、成分の大きさから確率を出す方針を確かめた）
  - 本教材 docs/tree/tree-edge-contribution.md の力試しの方針（辺が入る確率 (1 − 2^{-s})(1 − 2^{-(N−s)}) の和による別解）
- 注：台帳では tree-edge-contribution・linearity-of-expectation の challenge。このページの challenge として pages に足す提案

## 練習（practice）の候補

基礎の帯（〜1199）に入る練習向きの問題は見つからなかった。無理に足していない。

- ap.py で題名を Steiner・Subtree・Visit・Collect・Delivery・Necessary・Prun・Keep・Connect などで探した。Steiner で出るのは abc368_d（例題）と abc395_g（2561、一般のグラフのシュタイナー木で、steiner-tree のページの範囲）だけだった
- GitHub のコード検索（"Steiner"・"minimal subtree"）でも、基礎〜水の帯で該当する AtCoder の問題は出なかった
- これまでの候補（b1・b3・b5 の candidates.md と b1 の報告）にあったのは typical90_ai だけ。台帳でこのページを pages に持つのは abc368_d（例題）だけ
- この回は WebSearch の上限に達していて、検索エンジンでの日本語の解説探しはできなかった。工程10で再度探す余地がある

## 見送った候補

- arc097_d（F. Monochrome Cat、diff 2948、ap.py で確認）：最初に「条件を満たした葉を削り続ける」処理を使うが、本題は残った木の上の別の考察で、帯から大きく離れる。第三者の解説を開いて確かめられていないので載せない
- abc369_g（G. As far as possible、diff 2055）：指定頂点と根を結ぶ部分木の辺の数 ×2 が答えになるが、本題は長いパスを貪欲に選ぶ部分で、台帳では tree-diameter の challenge。このページには合わないので載せない
- abc395_g（Minimum Steiner Tree 2、diff 2561）：一般のグラフのシュタイナー木（steiner-tree のページ）
