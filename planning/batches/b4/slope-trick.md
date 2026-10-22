# slope-trick の報告（b4・執筆）

- 書いたファイル：docs/dp/slope-trick.md、snippets/slope-trick/usage.{cpp,yaml}、docs/img/slope-trick/breakpoints.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作ライブラリでの扱い, anchor: library}` を足した（hld の発展の概要と同じ形）。「学ぶための資料」は hld と同じく `## 学ぶための資料 {#resources}` の見出しだけで sections に載せていない
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 14。数式を含む文の長さ・表の行・助詞の重なりの誤検出）
- 新しいドメイン：hitonanode.github.io を check_noai.py で確かめた（noai・noimageai の指定なし）。付録 B への追加を提案する
- 図：breakpoints.svg を render_svg.py で 360px・720px にして目で確かめた（ラベルの重なりを直した）。visual は priority 3 なので動く図は置かず、静的な図で代えた
- コード片：表の操作をそのまま書いた構造体。乱数の操作の列（|x − a|・片側の折れ線・定数・左右の累積 min・区間の min）を、範囲 [−300, 300] の配列で計算した値と比べている（最小値と [−40, 40] の各点の値）。本文の main は「広義単調増加にする最小コスト」
- 手元の確かめ：ARC123 D の練習の方針（R を空にする → max(0, A_i − A_{i−1}) だけ平行移動 → |x| と |x − A_i| を足す）を、長さ 5 以下・値 −5〜5 の乱数 3000 件で全探索と比べて一致を確かめた（本文の方針は自分で導いたもの。evidence の maspy は問題名の列挙だけ）

## 台帳への提案

- abc217_h｜evidence｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0904_abc217 を足す（解法の節で Slope Trick・初期位置を 0 の多数で表す・時刻差で左右をずらすことを確認）
- arc123_d｜evidence｜https://kmjp.hatenablog.jp/entry/2021/09/16/0930 を足す（貪欲に B・C を作ってからずらす解き方。Slope Trick の解き方の裏付けではない）。今の evidence の maspy (2) は問題名を挙げるだけで解法がない。Slope Trick での解き方は手元の全探索との比較で確かめた（上記）
- arc123_d｜approach｜「B_i = x の DP で、R を空にする・max(0, A_i − A_{i−1}) の平行移動・|x| と |x − A_i| の加算を行う（貪欲に作って中央値で調整する解き方もある）」に具体化
- abc127_f｜evidence｜drken・maspy (2) で確認済み。変更なし

## 用語集への提案

- 区分線形｜piecewise-linear｜いくつかの点で折れる直線のつながりでできた関数。折れる点（傾きが変わる点）の位置と傾きの変化で関数全体が決まる（本文では定義を書き、リンクしていない）

## 手引きへの提案

- 発展の概要に「自作ライブラリでの扱い {#library}」を中身の節として足し、「学ぶための資料 {#resources}」を定型の見出しにする形が hld と slope-trick で 2 例になった。§13-1 の定型の見出しに `## 学ぶための資料 {#resources}` を加えるか決めてほしい
- Library Checker に対応する問題がない手法では「Library Checker に直接の問題はない（日付）」と書き、愚直な方法との乱数の比較と AtCoder の問題で確かめる、と書いてよいかを §13-10 に明記するとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

いずれも裏付けは maspy「slope trick (2) 問題編」の 1 つだけ（§15-6 の 2 つ以上に届かない）。ABC で Slope Trick が必須の問題は abc217_h 以外に見つけていない。

- arc070_c（ARC070 E. NarrowRectangles、diff 3365）：横に並ぶ長方形を左右に動かして全体をつなげる最小コスト。区間の min（左右で違う量ずらす）と |x − l_i| の加算 — https://maspypy.com/slope-trick-2-%e5%95%8f%e9%a1%8c%e7%b7%a8 （research/02-dp にも挙がっている）。力試しの候補
- dwango2016qual_e（DWANGO2016-PRELIMS E. 花火、diff 3144 参考値）：時刻順の目標位置に対し、単調な列を選んで距離の和を最小にする。累積 min と |x − p_i| の加算 — 同上
- utpc2012_12（UTPC2012 L. じょうしょうツリー、diff なし）：木の頂点の値を変えて単調にする最小コスト。木の上のマージ（節 on-trees の型） — 同上。on-trees の節は今は問題 ID を出さず型だけを書いた

## 未解決の点

- front matter の frequency_evidence の「recent 1（abc458_g）」は、台帳では abc458_g が monge の練習（(max,+) 畳み込みと答えの二分探索）で、slope-trick の問題ではない。frequency の根拠を確かめてほしい（変えていない）
- 例題 ABC217 H のダメージの向き（入力のどの値がどちら側か）は、kmjp の記事でも文と式で向きが食い違うと要約されたので、本文では向きと入力の値の対応を書かなかった
- KUPC2015 の WAAAAAAAAAAAAALL（maspy (2) の問題）は、ap.py で kupc2015_h が別の題（Bit Count）だったので、問題 ID を確かめられていない
- related の greedy-priority-queue#regret からは Slope Trick のページへリンクがあるが、本文では後悔付き貪欲との関係の主張を裏付けられなかったので書いていない

## 検証の指摘への対応

- 指摘 1〜5：本文を直した（導入の「Ex」→「H（ABC217 H）」と根拠の範囲、2 つのヒープの節で $a_i$ が 2 つ加わること、ライブラリの節で性質が保たれる理由、#breakpoints の L・R の定義、#on-trees の $N$ ＝頂点数の断り）
- 指摘 6（frequency_evidence の abc458_g）：front matter の frequency の欄はメインの判断に任せるので変えていない。提案：abc458_g が Slope Trick で解ける裏付けがなければ recent から外し、frequency を再判定する
