# graph-basics の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/graph-basics.md、snippets/graph-basics/build.{cpp,yaml}、docs/img/graph-basics/representations.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない。sections に載せない小見出し `### 隣接リストに持たせる情報 {#adjacency-extras}` を representations の下に足した
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（1 件・4 ケース一致）、textlint（エラー 0・警告 7）
  - 残した警告：35 行（要点の計算量の「で」の重なり。言い換えると並びが崩れる）、48 行（図の代替テキストの読点）、64 行（「メモリにも時間にも」の並列）、120・121 行（数式の中の数の列の読点）、150 行（折りたたみの中の答えの文の長さの誤検出）、169 行（`g[a]` に $b$、`g[b]` に $a$ の並列）
- 動く図：作っていない。catalog の visual は static・priority 2 なので、静的な SVG（同じグラフを図・隣接リスト・隣接行列・辺リストで並べ、辺 {1, 2} の現れる場所を太い橙の枠と太字で示す）にした
- 使った出典：E869120 の GitHub（typical90 078 の解答例。数える条件が「小さい隣がちょうど 1 個」であることを確認）、drken のはてなブログ（abc284_c。題名は title 要素で確認）、ACL の internal_csr.hpp（手元の ~/lib/ac-library-master で、scc と mincostflow の内部で使われていることを確認）。候補探しで qiita.com（sano192）と www.cnblogs.com（Lanly）を読んだ。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_bz | summary | 各頂点について、隣接する頂点のうち自分より番号の小さいものがちょうど 1 個である頂点の個数を求める（いまの「条件を満たす」はあいまい。問いだけなので手法名は入れていない） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/078.cpp |

abc284_c の summary と approach は evidence の解説と食い違いがなかった。

## 用語集への提案

本文で定義したので、用語集からこのページの節へ向ける形を提案する（本文から用語集へのリンクは張っていない）。

- 次数｜degree｜頂点につながる辺の本数。有向グラフでは入次数と出次数に分ける。全頂点の和は 2M（graph-basics#handshake）
- 単純グラフ｜simple-graph｜多重辺も自己ループもないグラフ（graph-basics#terms）
- パス・ウォーク｜path-walk｜辺をたどる頂点の列のうち、頂点の繰り返しを許さないものがパス（単純パス）、許すものがウォーク（graph-basics#terms）
- 補グラフ｜complement-graph｜完全グラフから元の辺を取り除いたグラフ。元のグラフで辺がない組を結ぶ（graph-basics#terms）
- CSR｜csr｜全辺を始点の順に 1 本の配列に並べ、各頂点の区間の始まりを別の配列に持つグラフの表現。ACL の内部で使われる（graph-basics#adjacency-extras）

## 手引きへの提案

- 基礎の technique の目安「上位の手法とのつながり」は、このページでは表現の表（使う手法の列）と握手補題の節の箇条書き（探索の計算量・オイラー路・次数による平方分割）に入れ、独立の節を作らなかった。定型の見出しにするなら anchor を決めてほしい（binary-search の報告と同じ指摘）
- §13.2 に従い、見出しを sections の title と同じにしたので、用語と落とし穴の見出しがかっこ書きつきで長い。落とし穴は §13.1 で定型の `## 落とし穴 {#pitfalls}` とされており、sections から外すか決めてほしい

## 問題の補充の候補

練習が 1 問なので、表現そのものを問う問題を 2 つ挙げる（どちらも ap.py で実在と題名・difficulty を確認、台帳には書いていない）。

- abc276_b（B. Adjacency List、diff 143）：都市と道路の組から、各都市につながる都市の個数と番号を昇順に出力する。辺リストから隣接リストを両方向に作り、ソートする。裏付け：https://qiita.com/sano192/items/298c551f0e63c9c93260
- abc343_b（B. Adjacency Matrix、diff 53）：N×N の 0/1 の隣接行列から、各頂点につながる頂点の番号を昇順に出力する。行ごとに 1 の列を拾う（隣接行列 → 隣接リストの変換）。裏付け：https://www.cnblogs.com/Lanly/p/18058486
- どちらも灰色の B 問題で易しい。役割は practice を想定（並びは abc343_b → abc276_b → abc284_c）

## 未解決の点

- 図 representations.svg は描画して目で確かめる道具がなく（rsvg・cairosvg なし）、XML として読めることと座標の計算だけを確かめた。凡例の文字列が右端（900）にはみ出さないかを含め、表示の確認を検証役に頼みたい
- 「ACL の CSR は vector の中に vector を持つより速い」は一般的な理解（メモリが連続でキャッシュに乗りやすい）に基づくもので、計測はしていない
- 確認問題の (3, 3, 1, 1) が単純グラフで作れないことは自分で確かめた（次数 3 の 2 頂点がほかの 3 頂点すべてとつながるので、次数 1 の頂点の次数が 2 になる）
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 約 12 回
