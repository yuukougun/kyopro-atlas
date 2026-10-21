# lis の報告（工程8b・バッチ b1）

- 書いたファイル：docs/dp/lis.md、snippets/lis/（lis・restore・weighted の 3 組）、docs/img/lis/dilworth.svg
- front matter で変えたもの：complexity・stage（draft）。updated は既に今日の日付だった。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 3 組で期待と違う 0。textlint エラー 0、警告 17（数式の中のカンマを max-comma が数えるもの、表の行・別名の行・図の代替テキストの長さ、問題の summary の助詞の重なりなど）
- 使った出典：drken（abc134_e・abc354_f・abc006_4・abc360_g）、kmjp（abc165_f）、E869120 の GitHub の sol/060.cpp（typical90_bh。台帳の evidence の editorial/060.jpg は画像で読めないため、同じリポジトリの解答例で確かめた）、ikatakos（abc457_g・abc476_g・abc468_f。解法の節だけ）、sigma425（tdpc_target）、ACL の document_ja/segtree.md。新しく noai を確かめたドメイン：scrapbox.io（下の候補の abc038_d 用。指定なし。本文には使っていない）
- 動く図：本文に `<div class="kp-viz" data-viz="lis" data-config='{"array": [3, 1, 4, 1, 5, 9, 2, 6], "strict": true}'></div>` を置き、図の前後に同じ内容の表と文章を書いた。図の仕様の案：各ステップで「入れる値・lower_bound（strict が false なら upper_bound）で決まる位置 k・置換か追加か・入れた後の L・a_i で終わる最長 k + 1」を caption に出す。L の置き換わる箱を強調し、下段に素朴な O(N^2) の dp[i] の表を並べて、同じ値が出ることを対比する。catalog の visual の後半（減少列の各点が別々の増加列に入る図）は静的な SVG（dilworth.svg）で代えた

## 台帳への提案

- abc457_g｜summary｜数直線上の決まった時刻・位置に落ちるリンゴを、速さが 1 以下のロボットですべて受け取るとき、ロボットの台数の最小を求める。｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0509_abc457（ロボットの初期位置の条件は確かめきれていない）
- abc476_g｜summary｜区間 [L, R] の各整数の popcount を順に並べた列を、狭義増加の部分列に分けるときの、部分列の個数の最小を求める。｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0919_abc476（複数のテストケースがあるらしい）
- abc476_g の summary に「[L, R]」があると textlint の no-unmatched-pair が警告を出すので、「L 以上 R 以下の各整数」と書く方がよいかもしれない
- typical90_bh｜evidence｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/060.cpp を足す（editorial/060.jpg は画像で、文章として確かめられない）
- tdpc_target｜evidence｜sigma425 の記事は「ただの LIS」と書くだけで、円を区間に直す手順・狭義広義・接する場合は書かれていない。mathenachia.blog/dp/ も題名を挙げるだけ。円の入れ子の不等号を確かめられる第三者の解説を足したい（本文の方針は「問題の定義に合わせてそろえる」とぼかした）

## 用語集への提案

- なし（状態 `state` は既存の anchor にリンクした）

## 手引きへの提案

- 台帳の evidence が画像（典型90 の editorial の jpg）だと WebFetch で中身を確かめられない。同じリポジトリの sol/NNN.cpp を evidence に足すか、代わりに使ってよいと手引きに書くとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc038_d（D. プレゼント、diff 1804 参考値）：箱を幅と高さがともに狭義に大きい箱へ入れていくとき、入れ子にできる箱の個数の最大を求める。節 nesting の代表（幅の昇順・同じ幅は高さの降順に並べて高さの狭義 LIS）。https://scrapbox.io/wafuwafualgorithm/ABC038_D_-_%E3%83%97%E3%83%AC%E3%82%BC%E3%83%B3%E3%83%88（noai の指定なしを確認済み）。tdpc_target より易しく、入れ子の練習に向く
- abc468_f（F. Chmax、diff 1693）：2 つの変数に値を順に入れていき、入れる先の値より大きいと得点が入るとき、得点の最大を求める。前から最大値を更新する要素の個数と、それを除いた列の LIS の和になる（LIS の発展）。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0725_abc468。frequency_evidence に名前があるのに catalog の problems にないので、練習に足す案（abc319 以降の水〜青の問題で、ページの水の根拠にもなりうる）
- abc369_f（F. Gather Coins、diff 1618、台帳で確認済み・dp-reconstruction と dp-grid の練習）：節 restore の練習として lis にも載せる案（コインの位置で LIS 型の DP をし、直前を記録して経路を復元する）。https://torus711.hatenablog.com/entry/2024/09/01/181216。本文では問題 ID を出さず型だけに触れた

## 未解決の点

- tdpc_target の「内側」が接する場合を含むかを第三者の解説で確かめられなかった。力試しの方針と節 nesting では不等号を問題文で確かめるよう書いた
- 節 variants の 1 か所変更の LIS（abc360_g）は、drken の解説が「書き換え先を直前の要素 + 1 に限ってよい」形で解いている。本文では f・g と「k − j ≥ 2 かつ a_k − a_j ≥ 2」の組をセグメント木で取る形で説明した（同じ結果になることは自分で確かめたが、検証役に見てほしい）
- 「すべての LIS に必ず含まれる」判定（含まれうる要素の中で f[i] の値が唯一）は出典なしで自分の議論から書いた。検証役に確かめてほしい
- dilworth.svg は手元に SVG の描画の道具がなく、表示を目で確かめていない（座標を手で計算し、XML として読めることだけ確かめた）
- 練習が 6 問・力試しが 2 問で、練習の dp_q は dp-segment-tree の例題でもある。dp_q の difficulty がないので、易しい順の位置は見当で先頭に置いた
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 約 14 回（検索 4 回を含む）
