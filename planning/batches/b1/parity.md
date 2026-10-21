# parity（偶奇に着目する）の報告と提案

- 書いたファイル：docs/thinking/parity.md、docs/img/parity/checkerboard-walk.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated
- 検査：check_pages --page parity（エラー 0・警告 0）、fix_problems --check（直す行 0）、textlint（エラー 0、警告 9。囲みの中のリンク名・台帳の summary・要点の入れ子のリストによる文長などの誤検出）
- 使った出典：hamayan（arc089_a）、drken（abc126_e）、Reputeless/tenkei_90 と E869120/kyopro_educational_90 の sol/024.cpp（github.com）、ikatakos の abc454・abc474 の記録（解法の節だけ）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_x | evidence | https://github.com/E869120/kyopro_educational_90/blob/main/sol/024.cpp を追加（Reputeless のページはキーワードだけで、判定の中身は公式の解答で確かめた） | 同 URL |
| arc089_a・typical90_x | checked | 2026-10-21（evidence で問いと方針を確かめた） | 各 evidence |
| abc126_e | approach | 「条件でつながった成分ごとに 1 枚見ればよい（Union-Find）」のままでよい | drken |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 市松模様 | checkerboard | グリッドのマス (i, j) を i + j の偶奇で 2 色に塗り分けたもの。隣り合うマスは必ず色が違うので、1 マスずつ動く道筋は 2 色を交互に踏む。 |
| 必要条件 | necessary-condition | 「できるなら必ず成り立つ」条件。満たさなければできないと言えるが、満たしてもできるとは限らない（十分性は構築などで別に示す）。 |

（本文では用語集へのリンクは張っていない。足したらメインの判断でリンクしてよい）

## 手引きへの提案

- thinking のページで「方針も折りたたむ」とき、例題の小見出しの下の折りたたみの題を `??? note "方針"` にした。手引き §10 は「解法の詳細」の題だけを示すので、thinking では `"方針"` を使うと明記するとそろう
- 偶奇の条件は「否定にしか使えない」点を確認問題で強調した。thinking の各ページで「必要条件 → 構築で十分性」の流れを共通の書き方にしてよいかもしれない（proof-patterns#necessary-sufficient が書かれたらリンクする）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付け |
| --- | --- | --- | --- |
| abc125_d | 隣り合う 2 つの符号を同時に反転する操作をくり返したときの総和の最大。負の数の個数の偶奇が変わらないことから決まる（台帳では invariant の例題。parity では練習として） | 練習 | https://drken1215.hatenablog.com/entry/2019/04/27/224100 |
| abc136_d | L/R に従って子どもが 10^100 回動いた後の人数。RL の境界ごとに、境界までの距離の偶奇で 2 か所に振り分ける（research 01 の表では「塊の長さの偶奇で振り分ける」）（台帳では run-length-encoding の練習。[exactly-k] の「回数が非常に大きいときは偶奇」の例） | 練習 | https://drken1215.hatenablog.com/entry/2020/12/29/190100 |

- abc319 以降で基礎〜水の偶奇の問題は見つけていない（catalog の level_evidence と同じ）。abc460_d（距離の偶奇、bfs の力試し）は bfs に置いたままでよい

## 未解決の点

- 骨格の related の game-basics#move-parity は game-basics が stub なので、本文では節ではなくページ（../comb/game-basics.md）にリンクした。game-basics が draft になったら #move-parity に直せる
- 本文で ../comb/permutation-parity.md・../basics/periodicity.md・../ds/union-find.md・../graph/bfs.md・../thinking/construction.md にリンクした（related にない）。related に permutation-parity を足すか検討を
- abc474_g の「K の偶奇の条件」は ikatakos 氏の記録でも証明が示されていないので、本文は「偶奇にも条件があり、実験で推測する」とだけ書き、具体的な条件は書いていない
- SVG は手元に描画の道具がなく、XML の妥当性だけ確かめた。見た目は検証役に確かめてほしい
- 使用量の目安：道具の呼び出し約 25 回、Web 取得 6 回

## 検証の指摘への対応（2026-10-21）

- 直すとよい 1〜6 はすべて直した（1：$\lvert a \rvert \equiv a$ の 1 段を足した／2：最後の区間の終点を丸の縁 (114, 232) にした／3：リンクを game-basics#move-parity にした／4：参考の題名を記事のとおりにした／5：図の前に「格子点をマスと見ると」の 1 文を足した／6：complexity を「1 回あたりならし」にした）。採らなかった指摘はない
- 未解決の点の 1 つ目（game-basics へのリンク）は 3 で解消した
