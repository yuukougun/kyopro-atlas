# kyopro-atlas

AtCoder で黄色（2000）を目指す学習者向けの、辞書として引く教材サイト（Material for MkDocs → GitHub Pages）。

- 要件：[planning/requirements.md](planning/requirements.md)
- 決定事項：[planning/decisions.md](planning/decisions.md)（要件で決めていなかった点。新しい日付の記録が優先）
- 進捗と次にやること：[planning/progress.md](planning/progress.md)

## 作業を再開するとき

1. `planning/progress.md` を読み、今の工程と次にやることを確かめる
2. 工程3以降は設計書（`planning/design.md`）に従う

## 守ること

- **atcoder.jp とそのサブドメインの問題ページ・解説ページを AI で開かない**（noai 指定）。問題の実在・タイトル・difficulty は `python3 tools/ap.py` で確かめる。記憶だけで問題番号を書かない
- codeforces.com も noai 指定があるので開かない。ほかのサイトも、AI の利用を断る指定があれば資料にしない
- 事実（問題番号・計算量・定理）は確かめてから書く。他者の文章は転載せず、参考にした資料は出典に残す
- 本文は だ・である調
- メインのセッションは設計と一貫性の管理に専念し、調査・執筆・検証はサブエージェントに分担させる。検証は書いた本人にさせない
- commit はまとまった単位で、意図が分かるメッセージで行う。push まで行ってよい
- `notes/`（学習記録）と `.cache/` は git の追跡外

## 並列で書くときの規則（design-review T9・T10）

- 執筆のサブエージェントが書いてよいのは、担当のページ（`docs/<field>/<id>.md`）と `snippets/<id>/` だけ。用語集・prh.yml・早見表・使い分け・catalog・問題の台帳への追加は、報告に「提案」として書かせ、メインがバッチの終わりにまとめて反映する
- `tools/gen_site.py` の実行と commit・push はメインのセッションだけが行う
- 骨格（工程8a）以降は、各ページの front matter と問題の台帳 `data/problems.yaml` が正。catalog は凍結し、執筆の指示としてだけ使う。ページの id と URL は変えない（変えるときは転送と localStorage の鍵の読み替えを用意し、ユーザーに知らせる）
