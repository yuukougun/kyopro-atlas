# tree-isomorphism の報告と提案（b4）

- 書いたファイル：docs/tree/tree-isomorphism.md、snippets/tree-isomorphism/ahu.{cpp,yaml}、snippets/tree-isomorphism/unrooted-hash.{cpp,yaml}、docs/img/tree-isomorphism/ahu-names.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件とも一致）、textlint（エラー 0、警告 2）
  - 残した警告：要点の「いつ使うか」の名詞句の列挙（§15-2 で句点なし）が 1 文と数えられた文の長さ、図の代替テキストの文の長さ（§14-25）
  - unrooted-hash.cpp は、7 頂点以下の乱数の木 400 組で順列の全探索と答えが一致することを手元で確かめた（一時置き場の t.py）
  - 図は render_svg.py で 360px・720px の PNG にして目で確かめた
- 使った出典：OI Wiki の tree-hash・tree-ahu（構成と事実の確認だけ。文章と図は使っていない）、arXiv 2309.14441 の要旨（AHU 法が線形時間）、Nyaan・ei1333 のライブラリ、library-checker-problems の task.md と info.toml（N ≤ 5×10^5、制限 5 秒、一直線のテストあり）、CSES 1700・1701 の問題ページ
- 新しく noai を確かめたドメイン：arxiv.org（arxiv.org/abs/2309.14441）・cses.fi（task/1700・1701）。どちらも noai・noimageai の指定なし

## 台帳への提案

- なし（このページで使った台帳の問題はない。例題は 0 問）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 同型（根付き木） | rooted-tree-isomorphism | 2 つの根付き木で、根を根に写し、親子の関係を保つ頂点の 1 対 1 の対応があることである。子の並び順は区別しない。既存の graph-isomorphism の項に 1 文足す形でもよい |
| 木の高さ（頂点の高さ） | height | 頂点 $v$ から、$v$ の部分木で最も深い葉までの辺の数である。葉の高さは 0 である。深さ（根からの距離）とは向きが逆である |

## 手引きへの提案

- §5 tree に「木の同型・木のハッシュで、子の名前は整列した列（多重集合）として扱い、名前の表は比べる木すべてで共有する。根のない木は中心（または重心）を根にし、2 個なら両方を試すか辺に仮の頂点を足す（持ち主は tree-isomorphism#unrooted）」を足すかどうか。tree-centroid#one-or-two の記述とそろえた
- 付録 A の木に「高さ」を足すか（深さと区別するため）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| agc024_d（D. Isomorphism Freak、diff 2307） | 木に頂点と辺を足してよいとき、同じ色の頂点を根にした部分木がすべて同型になる塗り方の色の数の最小と、そのときの葉の数の最小を求める | 練習か力試し。中心（頂点か辺）を根にして深さごとにそろえる考え方で、同型の判定やハッシュそのものは使わない。このページの #unrooted の「中心を根にする」の応用として置けるが、tree-diameter#center の力試しの方が合うかもしれない | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2018/0520_agc024 （解法の節だけを読んだ）。2 つ目の裏付けは見つからなかった |

- tupc2022_m（M. Fractal Tree Isomorphism、diff なし）も ap.py で見つかったが、第三者の解説を確かめていない
- ap.py で "Isomorph"・"Hash"・"Shape" を検索したが、ABC で木の同型やハッシュを本質的に使う問題は見つからなかった（abc232_c・abc371_c は小さい一般グラフの全探索で、small-graph-brute-force の担当）

## 未解決の点

- 木のハッシュの誤る確率の「1 組あたり N/p 以下」は、高さごとの乱数と積の設計に Schwartz-Zippel の補題を当てた自分の議論で、出典は Nyaan のライブラリの実装（確率の議論は書かれていない）と一般の補題である。証明の筋は折りたたみに書いた。検証役に確かめてほしい
- Library Checker の分類を全部の組で見積もった「3×10^-2 程度」は粗い上限（組の数 × N/p）である
- frequency_evidence の「古い ABC 1 問」がどの問題かは分からなかった（catalog には書かれていない）
- 練習の見出しに「CSES」の小見出しを立てた。§15-5 は Library Checker だけを定めているので、ほかのジャッジを同じ形で置いてよいか決めてほしい

## 検証の指摘への対応

- 指摘 1〜8 はすべて直した（1：折りたたみの証明を法 $p$ の多項式に置き換え、葉は定数 1 と断った。2：OI Wiki の紹介と参考の行を「整数の写像」と「乱数の XOR は任意の工夫」に直した。3：図の前に名前を振る順と、値に意味がないことを足した。4：「両方を試す」に逆の向きを足した。5：complexity・要点・#tree-hash の計算量を、値の計算と種類数の集計に分けた。6：unrooted-hash.cpp のカンマ演算子を波かっこに直した。7：確認問題の 2 問目を「直径の端点を根にしないのはなぜか」に替えた。8：同型を用語集へ、更新の話題を Static Top Tree へつないだ）
- 採らなかった指摘：なし
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件とも一致）、textlint（エラー 0、警告 2 は前と同じ 32 行・57 行の文の長さ）

### メインへの提案（検証の未解決の点から）

- front matter の frequency_evidence「古い ABC 1 問」を「recent 0・前提として届くページなし・ABC で本質的に使う問題なし」に直すかどうか（本文と research 04-tree §4.29 に合わせる。執筆者は変えられない）
- 手引き §15-5 を「Library Checker・CSES などのジャッジ」に広げるかどうか
- 用語集の graph-isomorphism の項に「根付き木では根を根に写し、子の並び順は区別しない」の 1 文を足す（上の用語集の提案と同じ。本文の導入からこの項へリンクを張った）
