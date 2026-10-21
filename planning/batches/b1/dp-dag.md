# dp-dag（DAG 上の DP）の執筆報告と提案

- 書いたファイル：docs/dp/dp-dag.md、snippets/dp-dag/longest-and-count.{cpp,yaml}、docs/img/dp-dag/table-as-dag.svg
- front matter で変えたもの：complexity（O(N+M)…）・stage（draft）・updated（2026-10-21、元から同じ）。sections に「上位の手法とのつながり」（anchor: connections、level はページと同じ基礎）を足した（手引き §4 の基礎の構成「上位の手法とのつながり」に合わせるため）
- 検査：check_pages --page dp-dag（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets snippets/dp-dag（1 本・6 case 一致）、textlint（エラー 0、警告 3：数式を含む文の長さ）
- 図：visual は priority 2 の static なので、SVG（列の DP とグリッドの DP を DAG として並べた図）で作った。動く図は作っていない
- 使った出典（どれも付録 B のドメイン。新しいドメインはない）：qiita.com/drken/items/03c7db44ccd27820ea0d、drken1215.hatenablog.com/entry/2023/06/10/150200、qiita.com/mhiro216/items/9b185e066bfd6eae7db8、kmjp.hatenablog.jp/entry/2019/09/01/1000、torus711.hatenablog.com/entry/2024/01/07/215719、qiita.com/uniTM/items/2d7a99ccd449c5140c4f（補充の候補の確認）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc139_e | evidence | https://qiita.com/mhiro216/items/9b185e066bfd6eae7db8 を足す | 今の evidence（kmjp）は前日に変わった選手だけを調べる貪欲で解いており、台帳の approach「試合を頂点、順序の制約を辺…閉路があれば不可能」は書かれていない。mhiro216 の記事が試合を頂点にした DAG の最長路と閉路の判定（−1）を説明している |
| abc335_e | approach | 同じ値の隣接頂点を（SCC か Union-Find で）まとめてから、トポロジカル順に DP する | torus711 の記事は値の順ではなく、SCC のトポロジカル順で DP している。「値の小さい順」でも正しいが、裏付けの記事と合わせる |
| dp_g・abc211_d・abc139_e・abc335_e | checked | 2026-10-21 | 各 evidence（abc139_e は上の追加分）で問いと方針を確かめた |

- abc211_d の主の summary「無向グラフで、都市 1 から都市 N への最短経路の本数を求める」は用語の正規形（最短路）と句点・mod の書き方が alternatives と違う。dp-dag では alternatives の summary を使った

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| DAG | dag | 閉路のない有向グラフ（Directed Acyclic Graph）。頂点を、すべての辺が前から後ろへ向くように一列に並べられる（トポロジカル順）。（ほかのページもすでにこの anchor にリンクしている） |

## front matter・prh への提案

- signs の「有向グラフの最長の経路の長さ・経路の本数・最短経路の本数」は prh で「最短経路 → 最短路」に当たる。本文の要点では「最短路」にした。front matter（と catalog 由来の signs）も「最短路の本数」に直すとよい

## 手引きへの提案

- §4 の基礎の構成「上位の手法とのつながり」は sections の定型の節（§13-1）に入っていない。定型の見出しと anchor（例：`## 上位の手法とのつながり {#connections}`）を決めると、ページ間でそろう

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc232_d | 壁のあるグリッドを左上から右か下へだけ進むとき、通れるマスの数の最大を求める（グリッドが DAG で、行ごとに左から見る順がトポロジカル順） | 練習（diff 539 で最も易しい。level_evidence にも挙がっている） | https://qiita.com/uniTM/items/2d7a99ccd449c5140c4f |
| abc037_d | グリッドで隣へ値が増える向きにだけ進む経路の総数（値の昇順がトポロジカル順） | 練習（diff 1377 参考値。台帳にはまだない。memoized-recursion の候補にも挙がっている） | https://qiita.com/drken/items/03c7db44ccd27820ea0d（類題として挙げている。解法は本文では未確認） |

- 基礎のページだが、練習が水（1528・1540）に寄っている。abc232_d を足すと易しい順の入口ができる
- abc319 以降の問題は abc335_e だけ。最近の ABC の DAG 上の DP の問題は見つけていない

## 未解決の点

- SVG は描画の道具がなく目で確かめていない。文字幅は見積もりで 720 の幅に収めた。検証で描画を確かめてほしい
- 「同じ頂点を 2 回通らない最長路は一般のグラフでは効率よく解けないとされる」は NP 困難の事実を言い換えたもので、出典は付けていない（一般的な事実として書いた）
- 「頂点数が 20 程度までなら bitDP」は計算量 O(2^N N^2) からの見積もりで、問題による
- 最短路の本数の節は shortest-path-dag の count-paths と重なる。dp-dag は「距離の順が DAG の順」の見方と BFS・ダイクストラ法での配り方に絞り、詳しくは shortest-path-dag へ送った。shortest-path-dag の執筆者と分担を合わせてほしい
- related の bitset-speedup#reachability・scc#dp-on-dag の先のページはまだ stub なので、本文ではページへのリンクだけにした（手引き §7）。draft になったら節へのリンクに直すとよい

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜8 はすべて直した。採らなかった指摘はない
  - 1：図を縦に積み、viewBox を 440×436 にした（幅 358px で font-size 14 が約 11.4px）。破線の弧は出る点を +7、着く点を −7 ずらした。幅 358px・2 倍密度で描画して重なり・はみ出しがないことを確かめた
  - 2：参考の 2 件の題名を記事のとおりにし、drken の ABC211 D の「参考にした点」を BFS の更新の 2 つの場合にした
  - 3：Union-Find でまとめてよいのは同じ値の辺が両向きに通れるときだけと書き、片向きなら強連結成分分解（同じ値の片向きの辺は残るが DAG にはなる）と書いた
  - 4：ダイクストラ法で古い要素を飛ばさないと本数が 2 重に増えることを 1 文足した
  - 5：scc#dp-on-dag・shortest-path-dag#count-paths・shortest-path-dag#build・fractional-binary-search#dp-check へ節のリンクにした
  - 6：#with-cycles の SCC の項目に前提の断りを足した
  - 7：計算量の言い換えを「状態数 ＋ 遷移の総数」に直した
  - 8：スタックの目安を memoized-recursion に合わせ（ulimit -s unlimited、深さ 10^6 超や上限が不明なら書き直す）、cpp-environment#stack-depth へリンクした
- 「未解決の点」の最後の項目（scc・bitset-speedup が stub）は誤りだった。scc は draft で節へリンクした。bitset-speedup はページへのリンクのまま
- 台帳への提案（変わらず）：abc139_e の evidence に mhiro216 を足す・abc335_e の approach を「同じ値の隣接頂点を SCC か Union-Find でまとめてから、トポロジカル順に DP する」に直す・dp_g・abc211_d・abc139_e・abc335_e の checked に 2026-10-21。用語集の #dag の追加と、signs の「最短経路の本数」→「最短路の本数」もメインで反映してほしい
