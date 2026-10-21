# difference-sequence の報告（b3）

- 書いたファイル：docs/basics/difference-sequence.md、snippets/difference-sequence/{min-ops,level}.{cpp,yaml}、docs/img/difference-sequence/range-to-points.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（5 節とも見出しにした）
- 定型の節：落とし穴・上位の手法へのつながり・例題・練習問題・確認問題・使い分け・参考
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 本・期待と違う 0）、textlint（エラー 0・警告 16。半開区間の `[l, r)` による括弧の対応・数式を含む文の長さ・読点の数、要点の囲みの signs 由来の「に」の重複）
- 図：range-to-points.svg を render_svg.py で 360px・720px の PNG にして目で確かめた
- 動く図：作っていない（visual は priority 2・static）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc459_f | summary | 整数列で、隣り合う 2 項の左を 1 減らし右を 1 増やす操作を繰り返し、列を狭義単調増加にする最小の操作回数を求める。 | 解答コード https://github.com/wangsenyuan/algorithm-practice/blob/main/src/atcoders/abc/abc400/abc450/abc459/f/solution.go 、https://github.com/yaohaoyou/yhy/blob/main/Blog/Trick.md |
| abc459_f | evidence | 上の 2 件を足す（ikatakos.com は 2026-10-21 に 503 で読めなかった） | — |
| abc459_f | approach | 隣り合う 2 項の ∓1 は累積和の 1 点の操作。A_i − i で広義単調に直し、ブロックを併合して均す（スタックで O(N)） | 同上 |
| abc454_f | summary | 0 以上 M 未満の整数の列で、区間の各要素に 1 を足して M で割った余りにする操作により、列を回文にする最小の回数を求める。 | https://github.com/FisherGoGo/ACM/blob/main/%E5%81%9A%E9%A2%98%E7%AC%94%E8%AE%B0/%E5%A5%BD%E9%A2%98/ABC454F_Make_it_Palindrome_2.md |
| abc454_f | evidence | 上の URL を足す（ikatakos.com は 503） | — |
| abc466_e | alternatives（difference-sequence）の summary | 主の summary と同じ「表と裏に数が書かれたカードの列で、区間の裏返しを K 回以下行った後の、上を向いた数の和の最大値を求める。」 | https://qiita.com/comet725/items/d9928d9fdb242140f987 |

- 本文の例題の行は、台帳の summary（「（執筆時に確かめる）」と「操作の内容は執筆時に確かめる」）を自分の要約で置き換えて書いた（手引き §14-15・16）。台帳を直したら fix_problems で同じ文になる
- abc459_f の要約の「複数のテストケース」は行の長さのため外した

## 用語集への提案

- なし（広義単調増加 `non-decreasing` は既存の語にリンクした）

## 手引きへの提案

- 差分列の定義をページごとに揃えたい。imos#adjacent-difference は内側の $d_1, \dots, d_{N-1}$、このページは両端の外を 0 とした $d_0, \dots, d_N$（長さ $N + 1$）で書いた。後者は「接頭辞・接尾辞の操作も 2 点の操作」になり、最小回数の式が端の場合分けなしで書ける。basics の書き方（§5）に「最小回数・可否の問題では差分列を両端の外まで $N + 1$ 個取る」を足す案

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc116_c（Grand Garden、diff 542） | 高さ 0 の花の列に区間の水やり（+1）を繰り返し、目標の高さにする最小回数。答えは隣接差の正の部分の和（最小回数の節の 1 つ目の型の最小の例） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc116-c.html |

- 練習が 2 問（目安 2〜6 の下限）。abc116_c は基礎の帯なので、練習の先頭の易しい 1 問として置く案。黄の帯の練習はほかに見つけられなかった

## 未解決の点

- ABC459 F の問題文の細部（操作の途中で値が負になってよいか、答えが存在しない場合の扱い）は第三者の資料から確かめきれなかった。本文は「回数は $\sum (S_k - S'_k)$、$S'_k \le S_k$ が必要」と、解答コードと一致する範囲だけを書いた。小さい場合（N ≤ 4、値 0〜3）は、累積和の全探索と snippets/difference-sequence/level.cpp の答えが一致することを確かめた
- ABC459 F の「ブロックを併合する」正しさは、本文では証明の筋（均した列が各接頭辞の和の上限に届くこと）だけを書いた。併合が要る理由の厳密な証明は書いていない
- ABC454 F の式（小さい方から (h+1)−k 個の和）は、N ≤ 5・M ≤ 4 のすべての入力で BFS と一致することを確かめた
- ikatakos.com（台帳の evidence）は 2026-10-21 の時点で 503 を返し、読めなかった
- w.atwiki.jp/sport_programming は check_noai で noai の指定はなかったが、Cloudflare の確認で本文を取得できず、使っていない
- 新しく noai を確かめたドメイン：w.atwiki.jp（指定なし。使っていない）。github.com・qiita.com・drken1215.hatenablog.com・oraclesqlpuzzle.ninja-web.net・imoz.jp は既知か確認済み（imoz.jp は付録 B にないが check_noai で指定なし）

## 使用量の目安

- 道具の呼び出し 約 60 回、Web 取得・検索 約 15 回

## 検証の指摘への対応（b3 の直し）

- 指摘 1〜6・8 は直した（8 は文字を 14px に上げ、左の注記を図の下の 1 行へ移し、その行の「変わるのは d_1 と d_4 だけ」は短くした）
- 指摘 7 は ABC466 E の方針をこのページの視点（端を含めた XOR の差分列と、0 でない点が 2K 個以下の対応）で書き直した。abc116_c を練習に足す案は、台帳に abc116_c がなく共有ファイルを書けないので採らず、提案として残す（上の「問題の補充の候補」）
- 台帳への提案：検証役の確かめにより abc459_f・abc454_f の checked に 2026-10-21 を入れる。abc459_f の approach は「累積和の 1 点の操作に直し、B_i = A_i − i のブロックを併合して均す」に直す
