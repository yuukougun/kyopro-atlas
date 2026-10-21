# memoized-recursion の報告（工程8b・バッチ b1）

- 書いたファイル：docs/dp/memoized-recursion.md、snippets/memoized-recursion/floor-memo.{cpp,yaml}・dag-memo.{cpp,yaml}、docs/img/memoized-recursion/call-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の 4 つ目の title を「落とし穴：深い再帰・閉路・自己ループ」に短くし（anchor pitfalls は同じ）、基礎の構成の目安に合わせて「上位の手法とのつながり」（anchor next-steps）を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 10 は数式を含む文の長さ・数式の中の括弧・助詞の重複の誤検出と、台帳の summary の行）
- 図：catalog の visual は priority 2（static）なので、呼び出しの木を静的な SVG にした（f(12)、f(k) = f(⌊k/2⌋) + f(⌊k/3⌋)、メモに当たった呼び出しを灰色の点線で示す）。動く図は作っていない
- 使った出典：qiita.com/drken（03c7db44ccd27820ea0d・dc53c683d6de8aeacf5a）、programming-hiroba.com（abc340-c・abc275-d）、drken1215.hatenablog.com（abc357_e・abc300_e）、torus711.hatenablog.com（abc380_f）。どれも付録 B にあるドメインで、新しく noai を確かめたドメインはない
- 数の裏付け（手元の Python で計算）：f(k) = f(⌊k/2⌋)+f(⌊k/3⌋) で N = 10^18 の現れる値 1012 個・メモなしの呼び出し 448825916312037 回、f(12) の呼び出し 23 回（メモありで 13 回）、⌊x/2⌋・⌈x/2⌉ で N = 10^17 の現れる値 95 個、10^18 以下の 2^a3^b5^c の約数の個数の最大 2700

## 台帳への提案

- abc357_e｜summary｜末尾に「。」を足す（「…組 (u, v) の数を求める。」）｜表記の規則（台帳のほかの summary と同じ形）。本文の行は catalog の memoized-recursion 用の要約（alternatives の文）を使った
- abc340_c｜approach｜「f(x) = x + f(⌊x/2⌋) + f(⌈x/2⌉)。現れる値は各段に 2 個で、N = 10^17 でも 95 個なので map でメモ化する」に補ってもよい｜https://programming-hiroba.com/abc340-c/
- abc380_f｜summary（alternatives の game-basics 用）｜「（ルールの詳細は執筆時に確かめる）」を外し、「先手 N 枚・後手 M 枚の手札と場の L 枚（合わせて 12 枚以下）を使い、手札を 1 枚場に出してそれより小さい場のカードを 1 枚まで手札に戻すゲームで、動けなくなった方が負けとして勝者を求める。」などに｜https://torus711.hatenablog.com/entry/2024/11/17/144754
- abc380_f｜checked・abc340_c・abc275_d・abc300_e・dp_g の checked｜2026-10-21（evidence の解説で問いを確かめた）

## 用語集への提案

- トップダウン DP｜top-down-dp｜漸化式を再帰関数で書き、初めの状態から必要な状態を呼んで値を求める DP の書き方。計算済みの値を覚えるものをメモ化再帰と呼ぶ。for 文で表を埋めるボトムアップと対になる（本文ではリンクしていない。term-index 用）
- 未計算の印｜（用語集でなく、本文で十分。提案しない）

## 手引きへの提案

- §5 dp に「メモ化再帰で書く例は、未計算の印を答えと別に持つ（-1 が答えになりうるか確かめる）」を一言足すとよい。expected-value-dp・game-basics の本文でも同じ注意が書かれていて、各ページで繰り返している
- 基礎の technique の構成の目安に「上位の手法とのつながり」があるが、§13.1 の定型の節の一覧にない。anchor を next-steps に固定するか（binary-search-answer も next-steps を sections に載せている）、定型として sections から外すかを決めるとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

台帳への追加はしていない。ap.py での確認はしていない（研究ノート 02-dp.md の候補をそのまま挙げる）ので、追加の前に ap.py と解説で確かめてほしい。

- abc037_d｜グリッドで隣の値が大きいマスへだけ進む経路の総数を求める（値の大小が DAG を作り、計算順序が添字の順でない）｜https://qiita.com/drken/items/03c7db44ccd27820ea0d（研究ノート 02-dp.md §5.3。difficulty は参考値 1377）
- abc184_d・abc201_d｜研究ノート §3 の level_evidence に「計算順が自明でない・メモ化が楽」の例として名前だけある。題材は未確認

## 未解決の点

- AtCoder のスタックの上限：本文では値を書かず、「手元の既定（8 MiB が多い）」と「提出先の上限が分からないとき」とだけ書き、cpp-environment#stack-depth（stub）と recursion-structure#stack へ回した。cpp-environment が draft になったら #stack-depth へのリンクに替えるとよい（いまは stub なのでページへのリンクにした）
- related の cpp-lambda#recursive-lambda も stub なので、本文はページへのリンク（../cpp/cpp-lambda.md）にした
- 確認問題「2・3・5 で割る場合の個数」の答えは「およそ 10^4 通り以下」と見積もりだけを書いた（正確な個数は数えていない）
- 例題の答えの大きさは手元の Python で確かめた（N = 10^17 で 5655884811924144128。long long に収まる）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 6 回

## 検証の指摘への対応

- 直した：指摘 1（⌊N/k⌋ の遷移の総数 O(N^{3/4})、N = 10^12 は間に合わない、#block-end へつなぐ）・2（手札に書かれた数の合計）・3（a ≤ 59・b ≤ 37、1178 通り）・4（59・37・25、10917 通り・7254 個）・6（f(0) = 0 と n ≤ 10^17 を本文に）・7（調べなかった手の先は計算されない）
- 指摘 5：(b) を採り、練習の方針の ABC275 D に「本文の図の漸化式そのもので、手で書いて確かめる問題」と明記した。図の題材は catalog の visual の指示どおりなので変えていない。練習から外すかどうかはメインの判断に任せる
- 未解決の点の cpp-lambda へのリンク：cpp-lambda が draft で anchor があるので、本文を `../cpp/cpp-lambda.md#self-argument` にした（related の cpp-lambda#recursive-lambda はそのまま）
- 採らなかったもの：なし
