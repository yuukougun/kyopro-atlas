# stack-techniques の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/stack-techniques.md、snippets/stack-techniques/{cancel,run-length,undo,chords}.{cpp,yaml}、docs/img/stack-techniques/bracket-stack.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 単調スタック・永続データ構造・01-BFS へのつながり, anchor: next-steps}` を足した（基礎の構成の「上位の手法とのつながり」。stl-containers の next-steps にならった）。既存の anchor は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（4 件すべて一致）、fix_problems --check --page stack-techniques（直すべき行 0）、textlint（エラー 0・警告 1）
  - 残した警告：204 行の sentence-length（「練習の方針」の折りたたみの中の箇条書きがまとめて 1 文として数えられる誤検出。列 10161 を指している）
  - fix_problems --check（全体）は終了コード 1：string/kmp.md の 6 行（abc304_f ほか）が ID だけの行のまま。このページとは無関係で、触っていない
- 動く図：作っていない（catalog の visual は priority 2・static）。静的な SVG で「(()()) を読むときのスタックの中身」を描いた。描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた
- 使った出典：drken のはてなブログ 7 本（abc328_d・abc240_d・abc307_d・arc108_b・abc243_d・abc338_e・arc076_c の方針）、qiita の masa2796（ABC428 C、状態を積んで取り消す）、kazun-kyopro.hatenablog.com（ABC237 D、逆順に deque の両端へ足す）。どれも付録 B のドメインで、新しく noai を確かめたドメインはない
- 自分で確かめた事実：空の `deque<int>` を 10^6 個作ると最大常駐が約 660MB、空の `vector<int>` 10^6 個は約 27MB（手元の g++-15 -O2、/usr/bin/time の %M）。落とし穴に書いた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc428_c | 新規（確認済み）・pages | stack-techniques に role: practice。summary「括弧の文字を末尾に足す・末尾を消すクエリのたびに、文字列が正しい括弧列かを答える。」approach「各時点の（残高, 接頭辞の残高の最小値）を積み、削除は pop で 1 つ前の状態に戻す」。diff 483（ap.py で確認） | https://qiita.com/masa2796/items/486bd7caa8fa49e0442e |
| abc237_d | 新規（確認済み）・pages | stack-techniques に role: practice。summary「(0) から始め、i を i − 1 の左か右に挿入することを繰り返した後の列を求める。」approach「逆順に処理すると挿入先が両端だけになり、deque の先頭か末尾に足す」。diff 544（ap.py で確認） | https://kazun-kyopro.hatenablog.com/entry/ABC/237/D |
| abc283_d | 新規（確認済み）・pages | stack-techniques に role: practice。summary「括弧と英小文字の列に従って箱に文字を出し入れするとき、同じ文字が箱に 2 つ入ることがないかを判定する。」approach「開き括弧と箱に入れた文字を積み、閉じ括弧で開き括弧まで降ろしながら箱から出す」。diff 453（ap.py で確認） | https://drken1215.hatenablog.com/entry/2024/11/01/130905 |

- 使った問題（abc328_d・abc240_d・abc307_d・arc108_b・abc243_d・abc338_e・arc076_c）の summary と approach は、evidence の解説と食い違いがなかった
- arc076_c の approach は「両端が周上にある組だけ」を残すと書いており、解説（片方でも内部にある組は無視してよい）と一致する

## 用語集への提案

- ならし計算量｜amortized｜操作 1 回の計算量は場合により大きくても、操作の列全体で平均すると小さく抑えられるときの、その平均の計算量。スタックで各要素が 1 回積まれ高々 1 回降ろされる処理などが典型（本文ではリンクしていない。必要なら next-steps のロールバックの行の「ならし計算量」からリンクする）

## 手引きへの提案

- 基礎の technique の「上位の手法とのつながり」を定型の見出しにするなら、anchor を `next-steps` にそろえてはどうか（stl-containers と本ページが next-steps、binary-search は comparison にまとめていて揃っていない）

## 問題の補充の候補

- abc428_c（C. Brackets Stack Query、diff 483）：括弧の末尾への追加・削除のたびに正しい括弧列かを答える。undo の節の型（状態を積む）の練習。裏付け：https://qiita.com/masa2796/items/486bd7caa8fa49e0442e 。本文ではいま問題 ID を出さず、型とコード片（undo.cpp）だけを書いた
- abc237_d（D. LR insertion、diff 544）：直前の要素の左右に挿入する操作の結果。deque の節の「逆順に処理して両端に足す」の練習。裏付け：https://kazun-kyopro.hatenablog.com/entry/ABC/237/D 。本文では型だけを書いた
- abc283_d（D. Scope、diff 453）：括弧の対応と、閉じたときに中身を戻す。brackets の節の練習。裏付け：https://drken1215.hatenablog.com/entry/2024/11/01/130905
- 「真ん中への挿入は deque 2 本」の型の AtCoder の問題は見つけていない（research でも未発見）

## 未解決の点

- abc454_d（frequency_evidence の recent）は台帳で bracket-sequence の練習で、problem-sets.md では stack-techniques#cancel に結び付いている。このページには載せていない。cancel の節の練習にも足すかはメインで決めてほしい
- bfs が stack-techniques を前提にしているが、このページのキューの説明は deque の節の 1 文（末尾に入れて先頭から出す）だけにした。基礎のページは短くする方針を優先した
- 図 bracket-stack.svg の表示の確認を検証役に頼みたい
- 「libstdc++ の deque は空でも領域を確保する」は実測（約 660 バイト／個）に基づく。内部の仕組み（map と 1 つのノード 512 バイトの確保）は記憶なので、本文には書かなかった
