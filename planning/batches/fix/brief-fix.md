# 直す担当への共通の指示（工程11）

kyopro-atlas（AtCoder で黄色を目指す人のための、辞書として引く競プロの教材。Material for MkDocs → GitHub Pages）の Issue を直す。リポジトリは /home/yuuki/projects/kyopro2/kyopro-atlas、サイトは https://yuukougun.github.io/kyopro-atlas/ 。今日は 2026-10-29。

## 最初に読むもの

- 担当の Issue の本文：`gh issue view <番号>`（読むだけ。Issue にコメント・編集・クローズをしない）
- CLAUDE.md の「守ること」と「並列で書くときの規則」
- 本文を直すなら planning/style-guide.md（執筆の手引き）の関係する節。用語の正規形は付録 A、記法は §6、図は §8、コード片は §9、問題の載せ方は §10

## 守ること

- **直してよいのは、頼まれたファイルだけ**である。ほかの担当が同じ作業ツリーで同時に別のファイルを直しているので、担当外のファイルを書き換えない。git は読むだけ（status・diff・log・show）にし、checkout・restore・stash・reset・commit・push をしない
- `tools/gen_site.py` を `--check` なしで動かさない。`nav.yml`・`docs/lists/`・`docs/index/`・`docs/<分野>/index.md`・`docs/llms.txt`・`overrides/assets/data/graph.json` などの生成物を手で直さない。生成物を変えたいときは、元（ページの front matter か gen_site.py）を直すよう頼まれていなければ、報告に「提案」として書く
- front matter で直してよいのは、頼まれた項目と `updated` だけである。本文を直したページは `updated: 2026-10-29` にする（`stage` は変えない）
- 用語集・prh.yml・早見表・使い分け（guide/method-comparison）・catalog・台帳 data/problems.yaml・手引き（planning/style-guide.md）を変えたいときは、報告に「提案」として書く（メインがまとめて反映する）。頼まれたときだけ直す
- 動く図（`overrides/assets/js/viz/`・`tests/viz/`）は頼まれたときだけ作る。共通の部品 `overrides/assets/js/viz.js` と `overrides/assets/css/kp.css` は、頼まれていなければ変えずに提案にする
- 本文は だ・である調。atcoder.jp・codeforces.com を開かない（WebFetch・curl・ブラウザのどれでも）。問題の実在・題名・difficulty は `python3 tools/ap.py show <ID>` で確かめ、記憶だけで問題番号を書かない
- `mkdocs build`・`mkdocs serve` は動かさない（site/ を上書きし、ほかの担当とぶつかる）。見た目を確かめるなら、公開中のサイトか、作業用フォルダへのビルド `uv run mkdocs build -q -d <作業用フォルダ>/site` を使う

## 直したあとに確かめること（書き換えない検査）

- `python3 tools/check_pages.py --page <id>`（ページごと）。エラー 0 にする
- 問題の行を触ったら `python3 tools/fix_problems.py --check --page <id>`
- コード片を触ったら `python3 tools/check_snippets.py snippets/<id>`
- 図を触ったら `python3 tools/check_svg.py --page <id>`。見た目は `python3 tools/render_svg.py <id> --out <作業用フォルダ>` で PNG にして確かめる
- 表記は `npx textlint <直したファイル>`（エラー 0 にする。既存の警告が出たら報告に書く）

## 報告

- 詳しい報告を `planning/batches/fix/<バッチ>/<担当の名前>.md` に書く：Issue ごとに、直したファイルと行、直した内容、確かめたこと、残った点・提案
- 最終の返答は短くする（300 字以内）：Issue ごとの完了／一部／未着手、検査の結果、報告のファイルの場所、メインに判断してほしい点
