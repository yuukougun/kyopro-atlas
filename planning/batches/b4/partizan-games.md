# partizan-games の報告（b4）

- 書いたファイル：docs/comb/partizan-games.md、snippets/partizan-games/surreal.{cpp,yaml}、docs/img/partizan-games/hackenbush-sum.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 1：32 行の要点の囲みの文の長さ。囲みの入れ子の箇条書きを 1 文と数える誤検出）
- 図：hackenbush-sum.svg を render_svg.py で PNG にして目で確かめた（実線＝左、破線＝右で、色だけに頼らない）
- コード片：Hackenbush の茎の値を分母 2^20 の整数で求め、和の符号の勝者が総当たり（左先・右先の両方）と一致することを assert で確かめる
- 新しく noai を確かめたドメイン：hitonanode.github.io（指定なし）。www.ivis.co.jp は証明書の検証に失敗して確かめられず、使っていない

## 台帳への提案

- abc229_h｜summary｜N 行 N 列の盤に先手の駒と後手の駒があり、自分の駒を 1 つ上の空きマスへ進めるか相手の駒を 1 つ取り除く手を交互に打つとき、どちらが勝つかを判定する。｜https://kmjp.hatenablog.jp/entry/2021/12/01/0930
- abc229_h｜evidence に追加｜https://hitonanode.github.io/cplib-cpp/number/dyadic_rational.hpp.html（ABC229 H を値で評価できる非不偏ゲームの適用例として挙げている）
- abc229_h｜checked｜2026-10-22

## 用語集への提案

- 非不偏ゲーム｜partizan-game｜2 人が交互に手を打つゲームで、同じ局面でも手番によって打てる手が違うもの。打てなくなった方が負けの規則なら、局面に数を割り当てて独立な部分の和の勝敗を判定できることがある。
- 超現実数｜surreal-number｜ゲームの局面の値として使う数。競プロで現れるのは分母が 2 の累乗の分数で、左右の行き先の値の間にある最も単純な数として後ろ向きに決まる。
- （本文では用語集にない語として「左・右」「最も単純な数」「和」を本文中で定義した。リンクは張っていない）

## 手引きへの提案

- §5 comb に「非不偏ゲームの値を double で持たず、分母を固定した整数で持つ。$\max L \ge \min R$ の局面は数にならないので assert で確かめる」を足すと、ゲームの他ページ（nim#asymmetric・game-basics#turn）からの参照に使える。
- nim#asymmetric・grundy-number#limitations から本ページへのリンクは、draft になったので節（#why-not-grundy・#tempo）へ張り替えられる。

## 問題の補充の候補

- 確認済みの 2 問（例題 1・練習 1）で発展の概要の目安を満たすので、補充は必須ではない。
- 候補（未確認。ap.py で実在と difficulty を確かめ、第三者の解説で裏付けてから）：tkppc6-1 の P「Game on Colored Tree」（赤青 Hackenbush の木の値を求める）。hitonanode 氏のページ（https://hitonanode.github.io/cplib-cpp/number/dyadic_rational.hpp.html）で問題名と内容が挙がっている。ap.py で contest id と問題 ID を確かめていないので台帳には書いていない。

## 未解決の点

- 本文の「値の分母の指数は、その局面から続けられる手数の最大より小さい」は、組合せゲーム理論の一般的な事実（m/2^d（d ≥ 1）の誕生日は d + 1 以上で、局面の値の誕生日は局面の木の深さ以下）から書いた。資料の該当箇所での確認はしていない。検証役に確かめてほしい。
- 「Grundy 数が 0 でない不偏な部分の値は、どんな正の数より小さく、どんな負の数より大きい」と、$S + *g$ の勝敗の条件は、kmjp 氏の ABC265 Ex の記事の条件（S > 0、または S = 0 かつ G ≠ 0 で先手勝ち）と一致することだけを資料で確かめた。
- 練習の方針の「アダマール変換」は hadamard-transform のページへリンクしたいが、field と状態を確かめていないのでリンクしていない。メインの判断でリンクを足してほしい。
- 学ぶための資料の教科書『Lessons in Play』の邦訳名は大学のシラバスの検索結果（syllabus.s.isct.ac.jp）で見たもので、書誌は直接確かめていない。参考の一覧には入れていない。
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 5 回・検索 6 回。

## 検証の指摘への対応

- 1（直すべき・分母の指数）：「手番を問わず続けて打てる手の数の最大、つまり局面の木の深さ」に直し、Hackenbush の列なら辺の本数で見積もれると添えた。
- 2（直すべき・#tempo の最後の段落）：一般的な形にとどめ、向かい合う駒・背中合わせの駒の対応と練習問題への言及は本文から外した（練習の方針の折りたたみに既にある）。
- 3（直すとよい）：「この問題の制約では 2^6 ほど」に直した。
- 4（直すとよい・邦訳名）：書誌を出版社・国立国会図書館で確かめられなかったので、邦訳名を外し、原題と著者（Albert・Nowakowski・Wolfe）だけにした。
- 5（直すとよい）：「$A$、$A + B$、$A + A + B$ の値は」と明示した。
- 6（直すとよい・リンク）：hadamard-transform は draft で #power がこの使い方に合うので、練習の方針に `../math/hadamard-transform.md#power` を張った。メインの判断で外してよい。
- 採らなかった指摘：なし。
