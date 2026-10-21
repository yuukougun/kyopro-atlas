# interval-dp-advanced（黄・technique）の報告

- 書いたファイル：docs/dp/interval-dp-advanced.md、snippets/interval-dp-advanced/{preorder-trees,visited-range}.{cpp,yaml}、docs/img/interval-dp-advanced/preorder-split.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致（両方とも main で全探索と比べる assert つき）、textlint エラー 0・警告 21（数式を含む文の長さ・`[l, r)` の括弧の対応・図の代替テキストの誤検出）
- 図：preorder-split.svg を render_svg.py で 360px・720px にして目で確かめた。visual は priority 3（静的）なので動く図は置いていない
- 使った出典：kmjp（ABC252 G・ABC292 G）、drken（ABC206 F）、www.cnblogs.com の Jijidawang「ABC266 ~ 273 题解」（ABC273 F）、kanpurin（一覧）。新しく noai を確かめたドメイン：fkgtinfo.com・algo-logic.info（指定なし。ただし本文には使っていない）、blog.csdn.net（HTTP 521 で取得できず判定できない。使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc273_f | evidence | https://www.cnblogs.com/CDOI-24374/p/16792927.html を足す（今の kanpurin の記事は問題名の一覧だけで解き方がない。誤りではないので残したまま足す） | 記事中の ABC273 F の節（訪れた区間の両端と今いる端の DP、Θ(n²)） |
| abc292_g | evidence | https://kmjp.hatenablog.jp/entry/2023/03/04/0900 を足す（kanpurin の一覧は問題名だけで解き方がない。誤りではないので残したまま足す） | kmjp の記事（区間・桁・数字を状態にしたメモ化再帰、O(M N^3)） |
| abc252_g | checked | 済み。tree-construction の力試しの方針（f と g、兄弟の番号の条件）と本文は食い違わない | kmjp |
| abc206_f | checked | 2026-10-21 | drken |
| abc273_f | checked | 2026-10-21 | cnblogs と検証役の全探索（b3 verify） |
| abc292_g | checked | 2026-10-21 | kmjp と検証役の全探索（b3 verify） |

## 用語集への提案

- なし（行きがけ順・半開区間はリンク済みの語・ページを使った）

## 手引きへの提案

- 区間 DP の応用のページは sections の 4 節が練習問題の解き方そのもの（ABC206 F・ABC273 F・ABC292 G）になっている（b1 handoff §2.1「練習の答えが本文で見えてしまう」と同じ形）。本文は一般の形で書き、ABC273 F は到着時刻の和の問題で代わりにコードを示したが、ABC292 G の節は問題の形のまま書いた。ABC292 G を例題に上げる（例題 2 問になる）か、練習のままにするかをメインが決める

## 問題の補充の候補

- 今回は ap.py と第三者の解説で新しい候補を探していない（確認済みの 4 問で節がすべて埋まったため）。研究ノートの発展 abc261_g（2803）・abc262_g（3114）は黄のページの範囲を超えるので載せていない

## 未解決の点

- ABC273 F の第三者の解説（cnblogs）は遷移を「自明」として省いている。本文の練習の方針（壁へ範囲を広げるときに対応するハンマーが範囲の中にあるかを調べる・行けなければ -1）は、状態の定義から筆者が組み立てたもの。検証役に確かめてほしい。cnblogs の要約では出発点が「位置 1」と読めたが、本文は台帳の summary どおり「原点」とした
- ABC292 G の制約 N, M ≤ 40 は kmjp のコードの配列の大きさからの推定。本文では「40 程度」とぼかした
- 本文の「到着時刻の和は待っている数で先払いする」型と「帰りがけ順・BFS 順」「括弧列と森」の応用の型は、特定の問題に依らない一般の事実として書いた（コード片は全探索と照合済み）
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得・検索 約 15 回

## 検証の指摘への対応（b3 verify）

- 指摘 1（練習の解き方が本文で見える）：(b) で直した。#digits-and-ranges の冒頭から「練習の ABC292 G」の名指しを外して一般の形だけにし、#visited-range の ABC273 F の言及も問題名を外した一般の例（「ある点を通るには別の点で何かを拾っておく必要がある」）にした。問題との対応は練習の方針の折りたたみにだけ残す。(a)（ABC292 G を例題に上げる）は台帳の役割の変更なのでメインの判断に残す
- 指摘 2（提案の根拠の誤り）：上の「台帳への提案」の根拠を「kanpurin の一覧は問題名だけで解き方がない」に直した。abc273_f・abc292_g の checked も足した
- 指摘 3：「根を $P_0$ に固定した木は $N^{N-2}$ 通りある」とし、ケイリーの公式へリンクした
- 指摘 4・5：コード片のコメントを直し、出発点の位置を `o`（本文も $o$）に変えた
- 指摘 6：99 行・134 行・133 行の文を短くした
- 指摘 7：図を描き直した（viewBox 460×240、文字 15px 以上、題と最下段の注記を省き、右の木を詰めた）。render_svg.py の 360px で目で確かめた
- 指摘 8：#visited-range と落とし穴に、$N = 5000$ で表が約 400MB になることと、長さごとに 2 段だけ持てばよいことを足した
- 採らなかったもの：なし
