# palindrome の報告と提案（工程8b・b1）

- 書いたファイル：docs/string/palindrome.md、snippets/palindrome/expand-center.{cpp,yaml}、snippets/palindrome/manacher.{cpp,yaml}、docs/img/palindrome/symmetric-pairs.svg、docs/img/palindrome/manacher-mirror.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages --page palindrome（エラー 0・警告 0）、fix_problems --check（palindrome の行に指摘なし。ほかのページ geometry/rotation-transform.md に 8 行の指摘があるが担当外）、check_snippets snippets/palindrome（2 件とも一致。manacher.cpp は N ≤ 200 で全区間を素朴な判定と assert で照合）、textlint（エラー 0、警告 22。数式 `[l, r)` の括弧の対の誤検出、数式を含む文の長さ、要点の「中心から伸ばす・両端から作る」の「から」の重複など）
- 動く図：作っていない（visual は priority 3。静的な SVG 2 枚で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc468_d | checked | 2026-10-21 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0725_abc468 （長さ ≤ 10^4、中心から伸ばし不一致 1 組まで）、https://qiita.com/comet725/items/72f8f924a4bfdb9e13cd |
| abc398_f | checked | 2026-10-21 | ikatakos 0322_abc398（Manacher・ハッシュ、\|S\| ≤ 5×10^5） |
| abc206_d | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2021/06/26/165800 |
| abc359_d | checked | 2026-10-21 | https://merom686.hatenablog.com/entry/2024/06/23/014345 |
| abc290_e | checked | 2026-10-21 | ikatakos 0219_abc290（min(左から何番目, 右から何番目) の寄与） |
| abc363_f | checked | 2026-10-21 | https://merom686.hatenablog.com/entry/2024/07/21/020359 |
| abc394_e | unverified_in | 削除してよい（内容は ikatakos 0222_abc394 で確認済み） | ikatakos 0222_abc394 |

## 用語集への提案

なし（用語集へのリンクは使っていない）。

## 手引きへの提案

- 担当の指示に「レベル 基礎」とあったが、ページの front matter は level: 水（catalog も 水）。front matter が正なので、technique（水）の構成（必要になる場面は各節の冒頭に含め、落とし穴・例題・練習・力試し・確認問題・使い分けを置く）で書いた。指示の生成側のレベルの取り違えがないか確かめてほしい
- sections に `comparison` の anchor を持つページでは、§13.1 の定型の「## 使い分け {#comparison}」と anchor が重なる。sections の title をそのまま見出しにした（「回文判定の道具の使い分け（…）」）。この扱いでよいか、§13 に一言あるとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| code_festival_2017_qualc_c（Inserting 'x'、diff 975） | 文字列の好きな位置に x を挿入して回文にする最小の回数（できなければ −1）。両端から 2 つの添字を寄せる貪欲 | 練習（外側から組み立てる・両端から作るの基礎の型） | https://drken1215.hatenablog.com/entry/2020/02/19/093100 |
| abc363_d（Palindromic Number、diff 975） | N 番目に小さい回文数。桁数ごとの個数を数え、前半の桁で決まることを使う（内容は記憶による。第三者の解説で未確認） | 練習の候補（裏付けを取ってから） | 未取得（ikatakos 0720_abc363 には D の節がない） |
| abc175_f（Making Palindrome、diff 2512） | 文字列を左右に置いて回文を作る最小コスト。左右の余りを状態にした最短路 | 力試し（発展帯なので載せるかは判断を任せる） | https://drken1215.hatenablog.com/entry/2020/08/16/032500 （調査レポート §5 にある） |

## 未解決の点

- ABC394 E の「到達できない組」の出力の値は解説で確かめていないので、本文では「指定に従う」と書いた
- ABC363 F の N の上限は解説に明記がなく、本文には書いていない（「約数の個数は高々 6720」は merom 氏の記事による値だが本文には入れていない）
- ABC197 F の方針は、kmjp 氏の解説（中心から外へ伸ばす）と、本文の主な説明（(1, N) から内側へ BFS して出会い方の偶奇で答える）の 2 通りを書いた。どちらも正しいが、検証の際に確かめてほしい
- 回文木へのリンクは suffix-automaton が stub なので、節（#palindromic-tree）ではなくページへ張った。draft 以降になったら節へのリンクに直せる
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 12 回

## 検証の指摘への対応（planning/batches/b1/verify/palindrome.md）

- 指摘 1（直すべき）：sections から comparison を消し、見出しを `## 使い分け {#comparison}` にして、確認問題の後・参考の前へ移した
- 指摘 2（直すべき）：manacher-mirror.svg と代替テキストの「c = 9」「c = 11」を「位置 j = 9」「位置 j = 11」にし、行の見出し「c」を「位置」にした
- 指摘 3：#manacher の冒頭を「区切りを挟んだ $T$ の $2N + 1$ 個の位置（両端の空の回文の中心 2 個を含む）」にした
- 指摘 4：「任意の区間の判定を決定的に済ませたいなら Manacher、接頭辞・接尾辞だけなら Z でもよい」の趣旨に直した
- 指摘 5：区間 DP の式に「閉区間 $[l, r]$ について」を添えた
- 指摘 6：merom686「ABC363」の出典の説明を、記事の内容（中の回文の数と外側の反転の組が N の約数で 0 を含まないこと、積の途中のあふれ）に直した
- 指摘 7：abc394_e の解法の詳細を「最後まで未到達の組は $-1$ を出す」にした
- 指摘 8：2 枚の図の位置の数字を 14 に上げ、manacher-mirror の「r」を破線の上端の上へ動かし、弧の下の空いた帯を詰めて viewBox の高さを 345 → 292 にした
- 採らなかった指摘：なし

### 提案（メインが反映する）

- 台帳 data/problems.yaml：abc394_e の unverified_in を消す（検証役が evidence で「到達できない組は $-1$」を確認済み）。abc197_f に checked: 2026-10-21 を足す（検証役が kmjp の記事で確認）。既出の checked の提案（abc468_d・abc398_f・abc206_d・abc359_d・abc290_e・abc363_f）も検証役の確認と合う
- 手引き §13：「sections に comparison が残っていたら消す」の一言を足すかはメインの判断に任せる
- 参考：`python3 tools/fix_problems.py --check` は graph/warshall-floyd.md の 5 行（裸の問題 id）を直すべき行として報告する。本ページとは無関係
