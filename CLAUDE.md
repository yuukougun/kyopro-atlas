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
- 事実（問題番号・計算量・定理）は確かめてから書く。他者の文章は転載せず、参考にした資料は出典に残す
- 本文は だ・である調
- メインのセッションは設計と一貫性の管理に専念し、調査・執筆・検証はサブエージェントに分担させる。検証は書いた本人にさせない
- commit はまとまった単位で、意図が分かるメッセージで行う。push まで行ってよい
- `notes/`（学習記録）と `.cache/` は git の追跡外
