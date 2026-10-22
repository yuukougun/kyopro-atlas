# b5 提案：patterns/grid

- 書いたファイル：docs/patterns/grid.md、docs/img/grid/checkerboard.svg（snippets は置いていない。pattern のページなので疑似コードもなく、取り込むコード片がない）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を properties の次に足した（見本 bracket-sequence と同じ形）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0（警告 16 は助詞の重複・数式を含む文の長さ・図の代替テキストの長さの誤検出）。図は render_svg で 360・720 の幅を目視した
- 使った出典：qiita.com（comet725 の 2 記事）、scrapbox.io/konan-compro（ABC464・ABC472 の記録。check_noai で noai・noimageai の指定なしを確かめた。付録 B の scrapbox.io の確かめたプロジェクトに konan-compro を足してほしい）。ikatakos.com の ABC464・ABC472 の記録は E・D の解法の節がなく使えなかった

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
|---|---|---|---|
| abc472_d | summary | 爆弾のマスがあるグリッドで、爆弾のマスを通らずに上下左右に K 回以内動いて、爆弾が 1 つもない行と列の交わるマスへ行けるマスの数を求める。 | https://qiita.com/comet725/items/630641329b8edc669f8f |
| abc472_d | evidence に追加 | https://scrapbox.io/konan-compro/ABC472_%EF%BC%882026%2F08%2F22%EF%BC%89 | （D の節で、爆弾のない行・列のマスを始点にした多始点 BFS と K = 0 の注意） |
| abc472_d | checked | 2026-10-22 | |
| abc464_e | summary | はじめはすべて同じ文字のグリッドに、左上の角から指定のマスまでの長方形を指定の文字で塗る操作を順に行った後の、各マスの文字を求める。 | https://qiita.com/comet725/items/94922f79d708c74ca829 |
| abc464_e | approach | 操作の番号を長方形の右下の角に書き、右下から左上へ max で伝えて各マスに最後に効く操作を求める（2 次元の累積 max） | 同上 |
| abc464_e | evidence に追加 | https://scrapbox.io/konan-compro/ABC464_%EF%BC%882026%2F06%2F27%EF%BC%89 | （E の節で、(r, c) に番号を書き左・上へ chmax で広げる方針） |
| abc464_e | checked | 2026-10-22 | |

- abc464_e の approach の「後ろから伝播させる 2 次元のいもす法の変形」は、実際は和ではなく max の累積（包除の引き算がない）なので、上のように直すとよい。problem-sets.md は abc464_e を imos#imos-2d に振っているが、本文の行き先は grid#rectangles か prefix-sum-2d の方が合う（problem-sets の生成の元を確かめてほしい）

## front matter・catalog への提案

- related に konig-theorem・connected-components・union-find-connectivity・dijkstra・minimax・construction を足す（本文の節からリンクしている。とくに #tiling の最大独立集合は konig-theorem#make-bipartite、#states のゲームは minimax#states が持ち主）
- related の sweep-line-2d は本文で使った（#rectangles）。inclusion-exclusion-dp・operation-sequence も使った。外すものはない
- sections の rows-cols の title は catalog では手法の id（manhattan-chebyshev, coordinate-compression）が付いていたが、骨格の title にはない。そのままにした
- operation-sequence が draft になったら、#rows-cols の行や列の塗り替えのリンクを operation-sequence#overwrite に張り替える（いまは stub なのでページへのリンク）

## 用語集への提案

- 語：市松模様｜anchor：checkerboard｜定義：グリッドのマス (i, j) を i + j の偶奇で 2 色に塗った模様。上下左右に隣り合うマスは必ず違う色になるので、4 近傍のグリッドは二部グラフになる。
- 語：4 近傍・8 近傍｜anchor：neighborhood｜定義：マスの上下左右の 4 マスを 4 近傍、それに斜めの 4 マスを足したものを 8 近傍という。8 近傍はチェビシェフ距離が 1 のマスである。
（本文では用語集にない語なのでリンクしていない）

## 手引きへの提案

- §6 の記法に「グリッドのマスは (i, j)＝i 行目・j 列目（0-indexed、i は下へ増える）、移動量の配列は di・dj。問題文の (x, y) は読み込みで (i, j) に直す」を足す（b1 handoff §3 の grid-graph の提案と同じ。grid・grid-graph・rotation-transform は i・j、manhattan-chebyshev の盤面の節は r・c を使っていて揺れがある）
- pattern のページの sections に overview（一覧の表）を足すのを §4 の pattern の構成に明記する（骨格の catalog には overview がないページがある）

## 問題の補充の候補

- 表の各行の代表は行き先のページの問題を label の文字で書いた（ABC007 C・ABC176 D・ABC339 D・ABC325 C・EDPC H・ABC331 D・ABC213 C・ABC454 E・ABC178 E・ABC322 D・ABC204 F）。どれも台帳で確認済みで、別のページに載っている
- 練習は catalog の 2 問だけにした（patterns は 0〜3）。追加の候補は探していない（2 問で各節の代表が足りているため）

## 未解決の点

- abc472_d の問いの細部（爆弾のマスを通れないこと、移動回数を「安全なマスから」「安全なマスへ」のどちらで数えるか）は、2 つの解説の実装と記述から読み取った。上下左右の移動は可逆なのでどちらの向きでも数は同じだが、問題文で確かめていない
- abc464_e の「はじめはすべて同じ文字」は Qiita の実装（操作なしを 'A' とする）と scrapbox の記述（A が残っている）から読み取った。初期の文字が入力で与えられるかは確かめていない（要約では文字を書かずに済ませた）
- #tiling の「プロファイル DP の状態数は短い辺の長さ w に対して 2^w 程度」は broken-profile-dp の 1 マスずつの形に基づく目安で、状態の圧縮（#compress）で減る場合がある

## 検証の指摘への対応（2026-10-22）

- 指摘 1（#rectangles の最大値の累積）：直した。$(0, 0)$ を左上の角とする長方形に限ること、任意の長方形には使えないこと、右下から伝える向き（ABC464 E）を書き分けた
- 指摘 2（表の ABC325 C）：直した。「つながったまとまりの数」の行のページにグリッドグラフを足した
- 指摘 3（表の代表の問題にリンクがない）：採らなかった。例題を持ち主のページだけに置く規則と両立させるため、今の形（行き先のページの問題を label の文字で書き、リンクは行き先の囲みにある）のままにした。手引き §4 に「pattern の表の代表の問題は、行き先のページの問題を label で書いてよい（リンクは行き先のページの囲みにある）」と足すことを提案する。見本の形に寄せるかはメインの判断に任せる
- 指摘 4（行と列を 1 つずつ選ぶ）：直した。$M$・$R_r$・$C_c$ を定義し、$O(M)$ 回で済む理由まで書いた
- 指摘 5（ちょうど K 歩）：直した。「動けるマスが隣に 1 つでもあれば」の条件と往復の説明を足し、節の最初の文を「主に必要条件として使う」にした
