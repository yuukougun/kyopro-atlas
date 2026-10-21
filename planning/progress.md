# 進捗と残り作業

セッションが途切れても続きから再開できるように、工程ごとの状態と次にやることを記録する。作業の区切りごとに更新する。

## 工程（requirements.md §8「進め方」）

| # | 工程 | 状態 | 成果物 |
| --- | --- | --- | --- |
| 1 | 質問 | 完了（2026-10-21） | [decisions.md](decisions.md) |
| 2 | 調査 | 完了（2026-10-21） | [research/](research/)（手引きは [research/README.md](research/README.md)） |
| 3 | 設計 | 初版完了（2026-10-21） | [design.md](design.md)・[catalog/](catalog/) |
| 4 | 設計の見直し | 完了（2026-10-21） | planning/review/（見直し3本）・[design-review.md](design-review.md)（対応）・設計書第2版・目次第2版 |
| 5 | 決定の提示 | 完了（2026-10-21） | ユーザーの承認（decisions.md の「工程5での確認」） |
| 6 | 土台作り | 完了（2026-10-21） | [interfaces.md](interfaces.md)・公開 https://yuukougun.github.io/kyopro-atlas/ |
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

## 工程6：土台作り

部品どうしの約束を [interfaces.md](interfaces.md) に決め、5つの担当が並列で作っている（2026-10-21 開始）。

| 担当 | 作るもの | 状態 |
| --- | --- | --- |
| S1 サイト | mkdocs.yml、overrides/main.html、overrides/assets（CSS・progress.js・map.js・viz.js・同梱ライブラリ）、仮のホームと知識マップの置き場 | 完了 |
| S2 道具 | schema/page.schema.json、tools/make_skeleton.py・gen_site.py・check_pages.py・fix_problems.py・check_snippets.py・check_noai.py、tools/README.md | 完了 |
| S3 CI と環境 | pyproject.toml・uv.lock、package.json・textlint、third_party/ac-library（v1.6）、.github/workflows | 完了 |
| S4 執筆の手引き | planning/style-guide.md、planning/checklists/、prh.yml | 完了 |
| S5 記録用スキル（9a） | .claude/skills/record-problem/SKILL.md、claude/record-format.md | 完了 |

## 工程6の結果

- commit 7086af6 を push。deploy・check・zensical の3つのワークフローが成功し、サイトが https://yuukougun.github.io/kyopro-atlas/ で公開された
- CI のコンテナ（gcc:15.2.0）で、同梱の ACL v1.6 を使うコード片（snippets/_ci-smoke）がコンパイル・実行まで通った（T11）
- 353ページの骨格（一時置き場）で、check_pages エラー0、mkdocs build --strict 成功、ブラウザ確認86項目すべて通過（ライト・ダーク・スマホ幅）。知識マップの表示は約0.2秒（CPU 1/4 で約1.1秒）
- Zensical の正式な評価（T4）は 0.1.0（2026-11-05 予定）が出てから行う。それまでは CI の試験ビルドで見る
- 残り：用語の索引の漢字の読み（五十音順にするか）、docs/index/*.md に search: exclude を足す（S1 の提案）

## 次にやること

1. 工程7（試作）：性質の違うページを書く（設計書 §10.1 の候補＋黄の手法ページ1つ）。執筆→検証→修正の流れを試し、ページの種類ごとの使用量を測る（T21）
2. 9b：試作のページと仮の索引で claude.ai の実機確認
3. 試作をユーザーに見てもらい、設計と手引きを直す

## ユーザーにお願いしていること

- なし（g++-15 は 2026-10-21 に導入済み。VS Code の設定と `~/pch` も更新済み）
