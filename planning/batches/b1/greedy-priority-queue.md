# greedy-priority-queue の報告と提案（工程8b・b1）

- 書いたファイル：docs/basics/greedy-priority-queue.md、snippets/greedy-priority-queue/from-last-day.{cpp,yaml}、snippets/greedy-priority-queue/k-best.{cpp,yaml}、docs/img/greedy-priority-queue/from-last-day.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件、期待と違う 0）、textlint（エラー 0、警告 18。要点の囲みの長い文・数式を含む文の長さと読点・「が」「に」の重なりなど。残したものは誤検出か、言い換えると読みにくくなるもの）
- 図：catalog の visual は static・priority 2 なので、静的な SVG を 1 枚作った（後ろの日から進めてヒープに入れ、最大を取り出す 3 段の表）。画像に描き出して見た目を確かめる道具（rsvg-convert など）が手元になく、座標は手で決めたので、メインかレビューで表示を確かめてほしい
- 使った出典：drken（abc137_d・abc325_d・abc141_d・abc297_e）、oraclesqlpuzzle（abc376_e・abc249_f）、ikatakos（abc250 の記録。解法の部分だけを読んだ）。どれも付録 B のドメインなので、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc325_d | summary | 「各商品に印字できる時刻の範囲が決まっていて、印字した後は 1 単位時間あけないと次を印字できないとき、印字できる商品の最大数を求める。」（今の「1 秒に 1 個ずつ」は単位があいまい。drken の記事にも単位がない） | https://drken1215.hatenablog.com/entry/2023/10/22/184800 |
| abc297_e | note | 金額は空の選び方（0）を数えず、正の金額だけで K 番目を数える（drken の記事の文は「0 を最初に入れる」だが、コードは 0 を入れない。本文の練習の方針は 0 に触れない書き方にした） | https://drken1215.hatenablog.com/entry/2025/02/07/012850 |
| abc376_e | note | テストケースが複数ある形（oraclesqlpuzzle のコードから読んだ）。本文の練習の方針で「毎回作り直す」と書いた | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc376-e.html |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 後悔付き貪欲 | regret-greedy | 候補をとりあえず選んでおき、後でよりよい候補が来たら、選んだものの中で最も悪いものと入れ替える（取り消す）貪欲法。選んだものをヒープで持つ。取り消し付きの貪欲とも言う |

用語集へのリンクは本文に入れていない（ページの節 #regret で定義しているので、用語集からこの節へリンクする形がよい）。

## 手引きへの提案

- §4 の「technique（基礎）」と「technique（水・青・黄）」の構成は、field が basics で level が水のページにどちらを使うかが読み取りにくい。今回は指示に従い、基礎の構成（応用の型・落とし穴・つながり）に寄せ、技法ごとの節に「なぜ正しいか」を入れた。basics の水のページの構成を 1 行で決めておくとよい
- 静的な SVG の見た目を確かめる道具（rsvg-convert か cairosvg）を手元の環境に入れるか、tools に描き出しの手順を置くとよい

## 問題の補充の候補

catalog の練習は 3 問で、力試しがない。後悔付き貪欲の節（#regret）と時刻を飛ばす節に問題がない。どれも `python3 tools/ap.py show` で実在と difficulty を確かめた。

| 問題 ID | diff | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- | --- |
| abc216_e | 1084 | 乗るたびに楽しさが 1 減るアトラクションに合計 K 回まで乗るときの、楽しさの合計の最大値（同じ値をまとめて処理する。#take-max） | 練習（台帳では greedy-basics の練習。こちらにも足す） | https://blog.hamayanhamayan.com/entry/2021/08/29/231101（台帳の evidence） |
| abc249_f | 1786 | 代入と加算の操作の列から K 個まで無視できるとき、最後の値の最大（後ろから見て、最後に残す代入を固定し、無視する負の加算の小さい K 個をヒープで保つ。#fix-max-keep-k の応用） | 力試し | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc249-f.html |
| abc214_e | 1835 | 各ボールを区間 [L, R] の中の別々の箱に入れられるかの判定（時刻順に入れて締め切りの早いものから処理し、時刻を飛ばす。#earliest-deadline） | 力試し（台帳では priority-queue の練習。こちらにも足す） | 台帳の evidence（scrapbox.io/procon-kirokuyou の記事）。今回は開いていないので、使うなら検証役が読むこと |
| abc250_g | 2219 | 各日に株を 1 株買う・売る・何もしないのどれかを選ぶときの利益の最大（価格を 2 回入れて売りを取り消す後悔付き貪欲。#regret） | 力試し（黄なので、alien-dp の練習に回す案もある） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0508_abc250（記録の筆者は「正当性は未証明」と書いている） |

## 未解決の点

- #regret の節の「株の売買」の貪欲は、正しさの証明を本文に書いていない（「この型ごとに要る」「Alien DP のページへ」とした）。alien-dp の #undoable-greedy が書かれたら、そちらへ節のリンクに直す（今は alien-dp と slope-trick が stub なので、ページへのリンクだけにした）
- #regret の節の前から解く版（締め切りの順に入れ、入りきらなければ最小を捨てる）の正しさは、本文では一言の理由だけにした。厳密には「間に合う集合はマトロイドになる」ことから従う。証明を折りたたみで足すかは検証役の判断に任せる
- 本文の #take-max で、同じ値をまとめる型を問題 ID なしで書いた（abc216_e が台帳でこのページにないため）。補充が通れば練習に足し、本文から節へ結ぶ
- related の top-k-multiset・priority-queue・interval-scheduling・kth-value・reverse-thinking は stub なので、節ではなくページへリンクした

## 検証の指摘への対応（2026-10-21）

- 直すべき 1〜3：すべて直した（#take-max の余りの値を $v - q$ にし、最後の種類は $v' = 0$ まで下げると書いた。例も「$K$ 回まで」にした。#fix-max-keep-k に $A$・$B$ が非負の条件、評価を $i \ge K - 1$ から始めること、同じ $A$ の値があるときの $i^\ast$ の取り方を書いた。#k-best と落とし穴は「入れた組を set で覚える」にした）
- 直すとよい 4〜11：すべて採った
    - 4：日 $d$ より後は貪欲と同じ最適解をとる前提と、$d' < d$ を書いた
    - 5：「凸なら貪欲で求まる」の文を消し、「凸になる問題の一般的な扱いは Alien DP・Slope Trick のページ」とつないだ
    - 6：折りたたみ「最も安い 1 つを捨ててよい理由」を足した。検証役の案の交換（$z$ を任意の $w$ に替える）はそのままでは条件が崩れうる（$\ell_w < \ell_z$ のとき、間の $t$ で個数が 1 増える）ので、「見た仕事のうち最適解に入るものはヒープにある」を保つ形にし、間の $t$ でも $t + 1$ 個以下に収まる理由まで書いた
    - 7：手順の後に終わりの条件を書いた
    - 8：「候補も値も途中で変わらないなら」にした
    - 9：最初に各値段を入れること、0 を入れると 1 つずれるので問題文で確かめることを書いた
    - 10：図の viewBox を 560 幅にし、文字を 16（補足は 14）に上げた。題の行を 2 行に分け、「← 先頭を取り出す」と最下行の説明は外して、各行の下に「先頭の 3 を選び、2 は次の日へ持ち越す」などとまとめた。値・代替テキストは変えていない
    - 11：確認問題の反例を $m = 3$、$(1, 9), (1, 8), (3, 1)$（前から 17、正しくは 18）に替えた

### 台帳への提案（追加）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc137_d・abc325_d・abc297_e | checked | 2026-10-21（検証役が evidence の記事で例題・練習の方針を確かめた） | 検証の報告 planning/batches/b1/verify/greedy-priority-queue.md |
| abc325_d | note | 時刻の上限（本文の「10^18 程度」）は evidence の記事からは確かめられていない。本文は long long で持つ安全側の書き方 | 同上 |
| abc376_e | note | 値が正であること（本文 #fix-max-keep-k の非負の条件）は oraclesqlpuzzle の記事には書かれていない。もう 1 つの evidence の記事で確かめる | 同上 |
