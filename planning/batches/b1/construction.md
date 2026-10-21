# construction の報告（工程8b・バッチ b1）

- 書いたファイル：docs/thinking/construction.md、snippets/construction/small-cases.{cpp,yaml}・checker.{cpp,yaml}、docs/img/construction/zigzag.svg・modsum-bound.svg
- front matter で変えたもの：complexity・stage（draft）・updated（今日と同じ値のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 2 組・期待と違う 0。textlint エラー 0、警告 3（33 行は要点の囲み全体を 1 文と数える誤検出で見本と同じ。123 行と 245 行は数式 `(2, 3, 4, 5, 1)`・`(a, b), (c, d)` の中のカンマを数える誤検出）
- 使った出典：drken1215.hatenablog.com の 6 記事（例題 2・練習 3・力試し 1 の問いと方針。記事の題名は実物の title で確かめた）。新しいドメインはない
- 図：静的な SVG 2 枚（visual は priority 2・static）。手元に描画の道具がなく、座標を計算して書いただけなので、検証役に表示の確認を頼みたい

## 台帳への提案

- なし（使った 6 問はすべて台帳で確認済み、役割も台帳のとおり）

## 用語集への提案

- 必要条件・十分条件｜necessary-condition｜「答えが存在するなら必ず成り立つ条件」が必要条件、「成り立てば必ず答えが作れる条件」が十分条件。構築問題では、必要条件を挙げ、それを満たす場合をすべて作り方で覆うことで十分性を示す。（本文の導入で `../guide/glossary.md#necessary-condition` にリンクした）
- 候補（メインの判断で）：チェッカー｜checker｜答えが複数ありうる問題で、出力が条件を満たすかを確かめるプログラム。stress-testing のページに置くなら用語集は不要

## 手引きへの提案

- thinking のページで本文の表に問題の label を文字で書いてよいか（pattern の規則にはあるが thinking にはない）。abc-patterns の節の表に「ABC350 C」などを文字で書き、リンクは練習・力試しの囲みにだけ置いた。check_pages は通る

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc474_d（D. Outweigh、diff 389、ap.py で実在を確認）：A_x > B_x となる位置 x があるかで可否が決まり、あればその位置だけを非常に大きい値にした数列を作る（重み付きの比較の条件を満たす数列の構築）。裏付け：https://qiita.com/comet725/items/3772fa3312c73be086e3 。ただしこの記事は解答コードが中心で問題の条件が十分に読み取れず、ikatakos 氏の abc474 の記録には D の節がなかった。問いの裏付けをもう 1 件取ってから練習に足すのがよい（最近の ABC の基礎の構築として価値が高い）
- abc282_f（F. Union of Two Sets、diff 1734、ap.py で確認）：区間をあらかじめ選んでおき、どのクエリ区間も選んだ 2 つの和集合で表す。2 冪の長さの区間を用意する（Sparse Table の考え方）。裏付け：https://drken1215.hatenablog.com/entry/2022/12/29/112939（research/01 §5 の表。今回は記事を開いていない）。インタラクティブ寄りなので力試しの候補
- abc146_d（D. Coloring Edges on Tree、diff 1192、ap.py で確認）：木の辺を、同じ頂点に接する辺が違う色になるよう最少の色数で塗る。最大次数が下界で、DFS で達成する（上界・下界と達成の型）。research/01 §4.L が bound-and-construct の候補に挙げている。裏付けの解説はまだ確かめていない。本文の確認問題「木の辺の塗り分け」は問題 ID を出さずにこの型を扱った

## 未解決の点

- related の thinking-checklist#shape-construct・stress-testing・invariant・graph-construction・tree-construction はまだ stub なので、本文ではページへのリンクだけにし、stub のページの節へはリンクしていない（parity#checkerboard・bit-operations#xor-properties は draft で見出しを確かめた）
- abc-patterns（水）の節の追加の前提として graph-basics を書いた。front matter の prerequisites は空のまま（ページ全体の前提ではないため）
- frequency_evidence に挙がる abc453_f・abc454_e・abc474_g・abc474_d は本文で扱っていない（abc454_e・abc474_g は parity の練習・力試し、abc453_f は木の重心の構築で発展寄り）。abc454_e のグリッドの型は parity#checkerboard へのリンクで触れた
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 8 回（うち 1 回は D の節がなく使わなかった）、記事の題名の確認に curl 1 回

## 検証の指摘への対応（2026-10-21）

- 直した：指摘 1（確認問題の答えを「接する辺の数 = 次数 ≤ D」で言い直し、根の場合も含めた）、指摘 2（129 行の不変量へのリンクを外して文字だけに）、指摘 3（「条件を疑う必要はない」を弱め、作り方がすべての場合を覆うかの確認を足した）、指摘 4（ABC126 F に $M \ge 2$ と組の数 $2^{M-1}$ が偶数であることを明記）、指摘 5（ARC115 C で最も長い列 $1, 2, 4, \dots$ と下界 $\lfloor \log_2 N \rfloor + 1$、素因数の個数が $\log_2 N$ 以下であることを明記）、指摘 6（目標と切り上げ $\lceil (\text{初めの量} - \text{目標}) / c \rceil$ を明記）、指摘 7（small-cases.yaml に入力 8 の case を追加）、指摘 8（見出しを「回数の上限を 1 回だけ越える」に）、指摘 9（modsum-bound.svg の $P_i$ を tspan の下付きに、下の説明文を 14px の 2 行にして高さを 330 に。zigzag.svg の説明文も 14px に）
- 回答の任意の点：abc-patterns の表の「ABC131 E」を `[ABC131 E](#abc131_e)` にした
- ほかに：textlint の max-comma の警告が 232 行（ABC350 C の練習の方針）に出たので、「$i = 1$ から $N - 1$ まで順に」などに言い換えたが、警告は残った（数式の直後の「。」で文が切れず、項目全体を 1 文と数えている模様。どの文も読点は 3 個以下）
- 採らなかった指摘：なし
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 片・期待と違う 0、textlint エラー 0（警告 4 件：33・123・245 行の既知の誤検出と、上の 232 行）
- 図は直した後の表示を目で確かめていない（描画の道具がない）。メインか検証役に、下付きの添字と 2 行の説明文の見え方の確認を頼みたい
- 共有ファイルへの提案の追加：なし
