# grid-graph の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/grid-graph.md、snippets/grid-graph/{grid-bfs,components-8,obstacle-dual}.{cpp,yaml}、docs/img/grid-graph/{flatten,obstacle-dual}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（見出しの文字は title と同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 2）
  - 残した警告：図の代替テキスト 2 か所の sentence-length（代替テキストは 1 文で図の要点を言うため長い）
  - obstacle-dual.cpp は、H, W ≤ 5 のランダムな 1500 ケースで grid-bfs.cpp（4 近傍の BFS）と答えが一致することを確かめた
- 図：静的な SVG 2 枚（visual は priority 2。対応表・dx・dy・市松模様を flatten.svg 1 枚にまとめ、障害物の鎖を obstacle-dual.svg に描いた）。描画の道具がなく、XML として読めることと座標・文字幅の見積もりだけを確かめた。表示の確認（文字のはみ出し）を検証役に頼みたい
- 使った出典：drken（abc325_c）、Lanly の cnblogs（abc351_d）、hamayan（abc088_d）、motoya0118 の Qiita（typical90_l）、kmjp（abc413_g）。どれも台帳の evidence で、付録 B のドメイン。新しく noai を確かめたドメインはない
- 本文のリンク先はどれも stub なので、節へのリンクはせず、ページへのリンクだけにした

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| （なし） | | | |

使った 5 問の summary・approach は evidence の解説と食い違いがなかった。補足：

- abc413_g：kmjp の記事は H = 1 または W = 1 を例外として場合分けしているが、「左端か下端」「右端か上端」の判定は H = 1 でも式を変えずに正しい（本文の obstacle-dual.cpp で H = 1・W = 1 のケースを確かめた）
- abc325_c：drken の記事で H, W ≤ 1000 を確かめ、例題の方針に書いた

## 用語集への提案

- タイムスタンプの印｜timestamp-visited｜探索のたびに訪問済みの配列を消し直す代わりに、訪問した探索の番号を書き込み、「今の番号と同じなら訪問済み」と判定する書き方。消し直しの $O(\text{配列の長さ})$ を省ける（本文の boundary-cells で使った。リンクはしていない。採用なら本文から張る）

## 手引きへの提案

- 骨格の section の題名が dx・dy だが、本文とコードでは行と列の取り違えを避けて di・dj と書き、本文で「よく dx・dy と書く」と断った。グリッドのページ（patterns/grid・dp-grid・bfs など）で添字の文字をそろえたいので、§6 の記法に「グリッドは (i, j)＝i 行目・j 列目、移動の配列は di・dj」を足すか決めてほしい

## 問題の補充の候補

どれも台帳に確認済みで別のページに載っている問題。このページへの追加は役割の追加になる。

- abc151_d（D. Maze Master、diff 959）：迷路の 2 マス間の最短距離の最大値を求める。H, W ≤ 20 なので全マスから BFS する。本文の neighbors の確認問題と同じ型。現在 bfs の練習。裏付け：https://blog.hamayanhamayan.com/entry/2020/01/12/225950 （research/03-graph の表。今回は読んでいない）
- abc407_g（G. Domino Covering SUM、diff 2190）：ドミノの配置を市松模様の二部グラフにして最小費用流で解く。checkerboard の節の力試しに向く（現在 min-cost-flow の練習）。裏付け：https://kmjp.hatenablog.jp/entry/2025/05/27/0900 （research/03-graph の表。今回は読んでいない）
- abc193_f（F. Zebraness、diff 2475）：市松模様で片側の色を反転して最小カットにする。checkerboard の節の「燃やす埋める」の 1 文の実例。発展の難しさなので本文で型として触れるだけでもよい（現在 project-selection の練習）。裏付け：https://kmjp.hatenablog.jp/entry/2021/02/27/1000
- 止まるマス（boundary-cells）の節は abc351_d が練習にあるだけで、ABC の新しい回（abc400 以降）の例がない。research の §5.3 の未確認の候補から探す価値がある

## 未解決の点

- obstacle-dual の逆向き（行けないなら鎖がある）の証明は、本文では筋だけを折りたたみに書いた（到達集合の外周をたどる議論。Hex の定理と同じ形）。第三者の資料での確認はしていない。kmjp の記事は結論だけを述べている
- 「AtCoder のスタックは大きいが、手元では落ちることがある」は research/03-graph の dfs のメモに基づく。具体的な上限の値は書いていない
- frequency_evidence の abc453_d（extended-dijkstra の練習）・abc460_d（bfs の力試し）はこのページに載せていない
- 使用量の目安：道具の呼び出し 35 回ほど、Web 取得 5 回

## 検証の指摘への対応（verify/grid-graph.md）

- 1（直すべき・歩数の偶奇）：直した。「同じマスを何度通ってもよいなら」を前に置き、往復は「経路の途中の辺」とし、$s = t$ で 1 歩も動けないときは $K = 0$ でしか着けない例外を足した
- 2（flatten.svg の差の書き方）：直した。右の図の見出しの下に「番号の差で隣を書くのは番兵で囲んだときだけ（そのとき W を W + 2 に読み替える）」を置き、代替テキストにも同じ一言を足した
- 3（小さい文字）：直した。flatten.svg は差の図を表の下に移して縦長（viewBox 440×660）にし、文字を 14px 以上にした。obstacle-dual.svg の 13px の説明文 3 行を 14px にした。手元に描画の道具がないので、表示の目視は次の検証で確かめてほしい
- 4（市松模様の用語）：(a)(b) は提案どおり直した。(c) は後半の 1 文を消し、「片方の色のマスだけ値の 0 と 1 の意味を入れ替えると、燃やす埋める（最小カット）で扱える形になることがある」と具体化した。abc193_f は台帳の役割の追加になるので、本文には入れず「問題の補充の候補」のままにした
- 5（逆向きの証明の筋）：直した。外周を左上の角から時計回りにたどり、左端か下端に初めて着く所と、その直前の上端か右端の所の間の障害物の列を取る、と区間を決める文を足した
- 6（タイムスタンプの印）：本文は直していない（指摘も不要としている）。用語集の採否はメインの判断に任せる

## 台帳への提案（検証から）

- abc325_c・abc351_d・abc088_d・typical90_l・abc413_g の `checked` に 2026-10-21 を入れる（検証役が evidence の記事で問いと方針を確かめた。問題文そのものは開いていない）
