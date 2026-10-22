# b5 提案：knowledge-map（知識マップ）

- 書いたファイル：docs/guide/knowledge-map.md、docs/img/knowledge-map/reading.svg（地図の読み方の静的な図。render_svg で 360px・720px を目視）
- front matter で変えたもの：stage（draft）・updated（2026-10-22）。complexity は計算量のない案内のページなので null のまま
- 検査：check_pages（エラー0・警告0）、fix_problems --check（直す行0）、textlint（エラー0・警告0）。コード片なし
- 書き方の根拠：overrides/assets/js/map.js・progress.js・overrides/main.html の実装（表示の切り替え・URL の引数・次の候補の条件・深さの自動の絞り込み 80 ページ・related の添え方）と、design.md §8.4・§9.1、design-review T2・T15、interfaces §5〜§7
- 全体の図の節の Mermaid は、2026-10-22 の graph.json から数えた分野をまたぐ前提の本数（5 本以上の組）。本文に日付と「ページを足すと変わる」を添えた
- 出典：js.cytoscape.org（check_noai で noai の指定なしを確認。付録 B への追加を提案）、github.com/cytoscape/cytoscape.js-dagre

## 台帳への提案

- なし（hub ではなく guide で、catalog の problems も空）

## 用語集への提案

- なし（「前提」「次の候補」は本文で定義した。用語集に入れるなら：次の候補｜next-candidate｜レベルを持つ未理解のページのうち、レベルを持つ直接の前提をすべて「理解した」にしたもの。知識マップで光る枠で示す）

## 手引きへの提案

- 付録 B に js.cytoscape.org を足す（noai・noimageai の指定なし、robots="all"。2026-10-22）
- 横断のページで地図・集計の数（分野をまたぐ前提の本数など）を本文に書くときは、日付と「データから数えた値」を添える（§15-11 の手元で数えた値に準じる）

## 問題の補充の候補

- なし（このページは問題を載せない）

## 未解決の点

- 全体の図の Mermaid の本数は、ページの前提を直すと古くなる。gen_site.py の生成ブロック（例：`field-edges`）にするか、メインが定期的に数え直すかを決めてほしい
- 次の候補の判定は直接の前提だけを見る（map.js の isCandidate）。summary の「前提をすべて理解した」は直接の前提の意味で、本文ではそう明記した。祖先すべてを条件にしたいなら map.js の変更になる
- 「答えで二分探索 +水青」の印の例は、sections の level（水・青）から作った表示で、ラベルの「+水青」は区切りなしに連結される（map.js の upperLevels の join("")）。読みにくければ「+水・青」にする変更を検討してよい
- 本文に `?field=`・`?focus=`・`?view=all` の URL の引数を書いた。map.js の引数の名前を変えるときは本文も直す

## 検証の指摘への対応（2026-10-22）

- 指摘 1〜10 はすべて直した（図の光る枠を藍色 `#3f51b5` にし凡例に「光る枠は藍色」、説明の出る位置を「地図の下」、初めの表示を表示ごとに書き分け、全体の図は上から下と明記し Mermaid を `flowchart TB`、「→ 分野名」の点も破線の枠と添えた、焦点の表示の読み始めをレベルを持つ点に限定、確認問題 3 を焦点の表示の塗り・光る枠を当てる問いに替えた、要点を「直接の前提をすべて理解した」に、図のラベルを実際の題名に（bit 演算は 2 行）、ロードマップへのリンクを `#progress`・`#reading-order` へ）。採らなかった指摘はない
- 提案（メインへ）：summary の「前提をすべて理解した次の候補」を「直接の前提をすべて理解した次の候補」にする。map.js 417 行の凡例の文言も同じ言い換えにするとよい
