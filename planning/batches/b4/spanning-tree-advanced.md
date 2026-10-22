# spanning-tree-advanced の報告（b4）

- 書いたファイル：docs/graph/spanning-tree-advanced.md、snippets/spanning-tree-advanced/boruvka.{cpp,yaml}、snippets/spanning-tree-advanced/manhattan-mst.{cpp,yaml}、docs/img/spanning-tree-advanced/octants.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 2 本とも期待どおり（どちらも乱数の入力で素朴な方法と比べる assert を含む）／textlint エラー 0・警告 2（38 行目は要点の囲みの summary の文の長さ、78 行目は数式 $d(p, q)$ の中の読点の誤検出）
- 図：octants.svg を render_svg.py で 360px・720px の PNG にして目で確かめた。動く図はない（catalog の visual は null）
- 使った出典：参考の節のとおり。新しいドメインはない（en.wikipedia.org・cp-algorithms.com・ei1333.github.io・drken1215.hatenablog.com・github.com・judge.yosupo.jp はどれも付録 B にある）

## 台帳への提案

- keyence2019_e（KEYENCE 2019 E. Connecting Cities、diff 2623、確認済み）の pages に `{id: spanning-tree-advanced, role: example}` を足す（例題の持ち主をこのページにするか、centroid-decomposition の力試しのまま、こちらは practice にするかはメインが決める）。本文の Borůvka 法の節は、この問題と同じ重み $D \lvert i - j \rvert + A_i + A_j$ の完全グラフを問題 ID なしの型として扱い、snippets/spanning-tree-advanced/boruvka.cpp がその解き方（成分の異なる上位 2 件）を実装している。足したら、Borůvka 法の節の型の説明を例題へのリンクに張り替えられる
  - 裏付け：https://drken1215.hatenablog.com/entry/2019/01/15/081500 （辺の重みの形と分割統治の解法。Borůvka 法でも解けるという言及のみで手順はない）。2 つ目の裏付けは見つけていない
- 台帳の approach の追記の案：「…候補 O(N log N) 本でクラスカル法。Borůvka 法で、各段に左右の走査で成分の異なる上位 2 件を持っても O(N log N)」

## 用語集への提案

- なし（カット・縮約・全域木は用語集にあり、リンクした）
- 候補（足すかどうかはメインの判断）：有向全域木｜arborescence｜根 $r$ からすべての頂点へ有向路で届き、根以外の各頂点に入る辺がちょうど 1 本ある辺の集合。本文では最小有向全域木の節の 1 文目で定義した

## 手引きへの提案

- 発展の概要で ABC の問題が 1 問もないときの `## 練習問題 {#practice}` の書き方（「ABC で必須になる問題は確認できなかった」の 1 文＋ Library Checker の小見出しだけ）を §15-5 の例として書いておくと、ほかの発展のページとそろう

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| keyence2019_e | 番号の差と両端の値で重みが決まる完全グラフの最小全域木（Borůvka 法・候補の辺を絞るクラスカル法） | https://drken1215.hatenablog.com/entry/2019/01/15/081500 |
| cf17_final_j | 木の上の距離と頂点の値で重みが決まる完全グラフの最小全域木（Borůvka 法か重心分解。diff 3822 で難しすぎる） | 上と同じ drken の記事に Tree MST も Borůvka 法で解けるという言及がある（問題そのものの解説は読んでいない。裏付けとしては弱い） |

Manhattan MST・最小有向全域木・第 2 最小全域木を問う AtCoder の問題は見つけられなかった（ap.py の題名検索では手がかりにならない）。

## 未解決の点

- Library Checker の Minimum Spanning Tree・Manhattan MST・Directed MST の URL は、GitHub の library-checker-problems のディレクトリ名（graph/minimum_spanning_tree・geo/manhattanmst・graph/directedmst）から作った。judge.yosupo.jp のページそのものは開いていない
- 第 2 最小全域木を問う Library Checker の問題はない（graph・geo のディレクトリの一覧で確認）
- 最小有向全域木の「閉路の辺を 1 本だけ外して残りを使う最適な木がある」は証明を書かず、資料（Wikipedia・ei1333）に任せた
- related に bottleneck-path・functional-graph・lca を足す案（本文でリンクしている）。front matter の変更なので提案にとどめる

## 使用量の目安

- 道具の呼び出し 45 回ほど、Web 取得 14 回（検索 2 回を含む）

## 検証の指摘への対応（直し）

- 指摘 1（Borůvka 法の同じ重み）：直した。まとめて採るときは閉路を作りうる、Union-Find で確かめるなら比べ方を決めなくても重みの和は正しい、比べ方を決めると選んだ辺が森になる、と書き分けた
- 指摘 2（併合可能なヒープ）：本文のリンクの語を「併合可能なヒープ」にそろえた。anchor の `#meldable-heap` は付けなかった：advanced-ds-catalog は stage が stub で、check_pages が節へのリンクを許さない（draft 以降になったら `#meldable-heap` に張り替える）。front matter の complexity と要点の「併合できるヒープ」は変えていない
- 指摘 3（根が決まっていないとき）：直した。$L$ を「元の辺の重みの絶対値の和より大きい値」にし、$2L$ 未満なら結果から $L$ を引いたものが答えで、$L$ の辺の先が根になることを足した
- 指摘 4（閉路の検出）：直した。「根以外の各頂点」とし、根に自分への辺を足す（または根で止まる）ことを足した。「縮約後の自己ループを捨てる」の項目を要点に足した
- 指摘 5（図）：直した。左下寄りに x・y の向きの矢印を足し、$x+y$ 一定の破線を太くした（2.5）。破線はもともと塗った領域の端から端まで（斜めの境目から水平の境目まで）引いてあるので長さは変えていない。360px の PNG で確かめた

## 追加の提案（直しから）

- front matter の complexity と要点の「併合できるヒープ」を、advanced-ds-catalog の見出しに合わせて「併合可能なヒープ」にそろえる（メインの判断）
- advanced-ds-catalog が draft 以降になったら、本文の「併合可能なヒープ」のリンクを `../ds/advanced-ds-catalog.md#meldable-heap` に張り替える
