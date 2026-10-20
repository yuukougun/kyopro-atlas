# 進捗と残り作業

セッションが途切れても続きから再開できるように、工程ごとの状態と次にやることを記録する。作業の区切りごとに更新する。

## 工程（requirements.md §8「進め方」）

| # | 工程 | 状態 | 成果物 |
| --- | --- | --- | --- |
| 1 | 質問 | 完了（2026-10-21） | [decisions.md](decisions.md) |
| 2 | 調査 | 完了（2026-10-21） | [research/](research/)（手引きは [research/README.md](research/README.md)） |
| 3 | 設計 | 初版完了（2026-10-21） | [design.md](design.md)・[catalog/](catalog/) |
| 4 | 設計の見直し | 完了（2026-10-21） | planning/review/（見直し3本）・[design-review.md](design-review.md)（対応）・設計書第2版・目次第2版 |
| 5 | 決定の提示 | 進行中 | ユーザーの確認 |
| 6 | 土台作り | 未着手 | |
| 7 | 試作 | 未着手 | |
| 8 | 本制作 | 未着手 | |
| 9 | スキル作成 | 未着手 | |
| 10 | 全体の検証 | 未着手 | |

## 工程2：調査

分野ごとにサブエージェントを1つずつ並列で動かす。担当と成果物は [research/README.md](research/README.md) §6。

全11本が完了。項目は延べ598（分野をまたぐ重複30を含む）、例題・練習問題の候補は延べ1650件。全問題IDが AtCoder Problems のデータに実在し、difficulty の記載も一致することを機械的に確かめた。

調査中に分かった制約：
- Web 検索の共有の枠が途中で尽き、各担当は既知のサイト（個人ブログのアーカイブ、cp-algorithms、USACO Guide、OI Wiki など）を直接読んで補った。裏付けの取れない問題は各レポートで「未確認」に分けてある
- codeforces.com にも noai 指定があり、資料にしていない

## 工程3：設計

- 設計書 [design.md](design.md) の初版を書いた（2026-10-21）。分野をまたぐ重複と境界、レベルで迷った項目の決定を含む
- 目次（catalog）は分野のまとまりごとに9本のサブエージェント（A〜I）が下書き中。規則は [catalog/README.md](catalog/README.md)、検証は `python3 tools/check_catalog.py`

9本とも完了（2026-10-21）。目次の初版は15分野・367ページ。`tools/check_catalog.py` でエラー0・警告0・未処理の調査の key 0。章の区切り（コメント）を `chapter` の項目に変換した。各ファイルの `open_issues` に担当が決めきれなかった点がある。

## 工程4：設計の見直し（完了）

- 見直し3本（planning/review/）の指摘76件と照合112項目への対応を [design-review.md](design-review.md) に決め、設計書を第2版にした
- 目次（catalog）を第2版の形式に直した：353ページ（基礎100・水79・青52・黄37・発展51・レベルなし34）。統合で消えた id 21・新しい id 7・レベルの変更23（hub への変更4を含む）。`tools/check_catalog.py`（第2版）でエラー0、警告35（すべて「根拠の問題が帯の外」で、理由を level_evidence に記載）
- 問題の台帳 `data/problems.yaml`：1178問すべて裏付けを確認済み（`tools/build_ledger.py --check` で食い違い0）。**台帳は手で status・summary・note を直したので、`build_ledger.py` で作り直さない**（`--check` だけ使う）
- 最近の ABC のデータ `data/recent-abc.yaml`（abc451〜480 の D〜G 120問中118問を手法のページに対応）から frequency を付け直した（A 76・B 153・C 72。modint を A、interval-scheduling・median-absolute を B に手で直した）
- 執筆時に扱う残り：abc461_e・abc466_d（行・列ごとに最後の操作を持つ）と abc472_f（多角形の重心）に対応する節がない。abc465_g は手法が未確認。z-algorithm・rolling-hash・mo-algorithm・binary-trie・lis・euler-tour・tree-edge-contribution など、最近の根拠が帯と少しずれるページは level_evidence に理由を書いて帯を据え置いた

## 次にやること

1. 工程5：決定の一覧（設計書 §12）と、ユーザーに確かめる点（design-review §6）を示して確認を得る
2. 確認を得たら工程6（土台作り）。最初に CI のコンテナで snippets を1本通す、記録用スキル（9a）を作る

## ユーザーにお願いしていること

- なし（g++-15 は 2026-10-21 に導入済み。VS Code の設定と `~/pch` も更新済み）
