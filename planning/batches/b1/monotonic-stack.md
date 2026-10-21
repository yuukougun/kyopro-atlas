# monotonic-stack の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/monotonic-stack.md、snippets/monotonic-stack/{prev-greater,sum-of-min,sliding-min,cartesian-tree}.{cpp,yaml}、docs/img/monotonic-stack/{procedure,histogram}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。§13.2 に従い、sections の title を見出しに合わせて短くした（anchor と level は変えていない）
  - procedure：「単調スタックの手順と保つ性質」（かっこ書きを外した）
  - contribution：「i が最小（最大）になる区間の数と寄与の数え上げ」（本文は最小値の和を主に書いたので最小を先にした）
  - sliding-window-minimum：「スライド最小値（単調 deque）」
  - dp-transition：「DP の遷移の高速化に使う」
  - choosing：「使い分け」（anchor は choosing のまま。§13.1 の定型の `comparison` とは違う anchor になる）
  - cartesian-tree：「Cartesian tree（最大値で区間を割る再帰を O(N) で作る）」
  - swag：「SWAG：スタック 2 本で作る総積つきキュー」
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 件すべて一致）、textlint（エラー 0・警告 13）
  - 残した警告：要点の囲みの入れ子の箇条書き（数式を含む）の sentence-length、数式の中の列や区間 $(L_i, R_i)$・$[0, 2)$ による max-comma と no-unmatched-pair、図の代替テキストの数の列。どれも規則の誤検出
- 図：静的な SVG 2 枚（catalog の visual は priority 3 なので動く図は作らず、置き場の div も置いていない）。描画して目で見る道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認を検証役に頼みたい
- 使った出典：drken のはてなブログ 6 本（abc372_d・abc359_e・agc005_b・donuts_2015_3・arc189_d・abc311_g）、zenn（abc352_d）、note.com の hip_crow3665 の記事（abc435_f）、GitHub の E869120/kyopro-tessoku の answer_A60.cpp（raw で読んだ）、ikatakos の ABC407 の記録（候補の裏付けにだけ使い、本文には使っていない）。題名は title 要素で確かめた
- 新しく noai を確かめたもの：note.com/hip_crow3665/n/ne7a656317cea（check_noai で指定なし。記事中に AI の利用や複製を断る記述もなかった）。付録 B の note.com の「確かめた記事」に足してほしい

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc189_c | pages | monotonic-stack に role: practice を足す（ヒストグラムの最大長方形の最も易しい形。interval の練習はそのまま） | https://note.com/rikimarublack/n/n3074b0955e95（台帳の evidence） |

ほかの使った 9 問の summary と approach は、evidence の解説と食い違いがなかった。補足：

- abc359_e の approach「左で最も近い高い板」は正しい（本文も「手前で初めて高い仕切り」で書いた）。WebFetch の要約が一度「低い」と言ったが、入出力例の値で計算し直して「高い」で合うことを確かめた
- arc189_d の monotonic-stack 側の alternatives の summary「各スライムから始めて、隣の小さいスライムを吸収し続けたときの最終的な大きさ」は、本文の行が主の summary（「到達できる最大の大きさを全員分」）で出ている。alternatives の summary は使われていないようなので、そろえるかはメインに任せる

## 用語集への提案

- ならし計算量｜amortized-complexity｜1 回ごとの上限ではなく、操作の列全体の合計を操作の回数で割って見積もる計算量。単調スタックでは「各添字は 1 回積まれ高々 1 回降ろされる」ので、1 回の処理で多く降ろしても合計は $O(N)$ に収まる（本文で 2 か所、この anchor へリンクした）

## 手引きへの提案

- §13.1 の定型の「使い分け」は anchor が `comparison` だが、骨格の sections に `anchor: choosing` の使い分けがあるページがある（このページと lazy-segment-tree）。既存の anchor を変えないので `## 使い分け {#choosing}` にした。定型を `comparison` にそろえるなら、sections から外すか転送を決めてほしい
- 水の technique の目安にある「必要になる場面」「アイデアとなぜ正しいか」「計算量」は、このページでは最初の中身の節 procedure の中に小見出し（保つ性質・各操作の手順・なぜ O(N) か）としてまとめた。sections に載せる節を増やさずに目安を満たす形として、ほかのページでも使えると思う

## 問題の補充の候補

- abc407_f（F. Sums of Sliding Window Maximum、diff 1740、ap.py で実在を確認、台帳になし）：長さ N の列について、窓の幅 k = 1..N ごとに、幅 k のすべての窓の最大値の和を求める。各要素が最大になる範囲（左右で初めて大きい位置。同じ値は片側 ≤）を求め、窓の幅ごとの個数が台形になるので 2 階の差分で足す。範囲は単調スタックでも set でも求まる。contribution の節の練習（青）に向く。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0524_abc407 （ikatakos は set で範囲を求めている。単調スタックで書けることは同じ範囲を求めるだけなので自明だが、第三者の記述は未確認）
- abc379_f（F. Buildings 2、diff 1659、ap.py で実在を確認、台帳になし）：research/05-ds では確度 medium（解法の細部は未確認）。見えるビルの数の応用（右から単調スタックを作りながらクエリをオフラインで処理し、スタックの上を二分探索）。第三者の解説での裏付けがまだないので、使うなら解説を探してほしい
- abc334_f（F. Christmas Present 2、diff 1813、ap.py で実在を確認）：research/02-dp で dp-sliding-window の候補（確度 low・裏付け未取得）。直前 K 個の最小値で決まる DP の遷移の例題として dp-transition の節に欲しい。本文では問題 ID を出さず、型だけを書いた

## 未解決の点

- SWAG の deque 版（片方が空になったら残りを半分ずつ分け直すとならし O(1)）は、研究メモと一般的な知識に基づく。第三者の資料での確認を検証役に頼みたい（本文では 1 文だけ）
- abc372_d で同じ高さのビルがあり得るかは確かめきれなかった（drken の記事の例は同じ値を含み、コードは真に低いものだけを降ろしている）。本文は「同じ高さは隠さない定義なので真に低いものだけを降ろす」と書いた。定義の細部（「より高い建物がない」）は drken の記事の要約に基づく
- frequency_evidence の abc480_g は台帳で inline-dp の力試し（summary が「（執筆時に確かめる）」）で、このページには載せていない
- research で挙がっていた awesam・kuuso1（Qiita）、drken「Cartesian Tree の O(N) 構築」、motsu-xe「SWAG」は今回読んでいないので、参考に入れていない
- 使用量の目安：道具の呼び出し 40 回ほど、Web 取得 12 回
