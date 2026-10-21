# kyopro-atlas

AtCoder で黄色（レート 2000）を目指す人のための、**辞書として引く**競技プログラミングの教材です。ABC で解けなかった問題をきっかけに、必要な手法のページを引いて読む使い方を想定しています。

- サイト：https://yuukougun.github.io/kyopro-atlas/
- 状態：制作中。本文があるのは一部のページで、ほかは「準備中」の印が付いた枠です

## 教材の使い方

- **引く**：検索、用語の索引、逆引き辞典（制約や問題の言い回しから手法を探す）、題材別のページ（括弧列・順列・XOR など）から目的のページを探します
- **順に学ぶ**：色別ロードマップと知識マップで、レベル（基礎・水・青・黄・発展）と前提の順にたどれます
- **ページの読み方**：冒頭の「要点」だけで何ができて、いつ使うかが分かります。続きに理由・処理の流れ・例題（解法は折りたたみ）・練習問題があります
- **進捗**：練習問題の「解いた」と、ページ上部の「理解した」のチェックは、ブラウザの中（localStorage）だけに保存されます。端末をまたぐときは「この教材の使い方」のページから書き出し・読み込みをしてください

## 解けなかった問題を claude.ai で解説してもらう

claude.ai/code の **Projects** で、このリポジトリを読みながら解説してもらえます。

1. [Claude GitHub App](https://github.com/apps/claude) をこのリポジトリに入れる
2. claude.ai/code のサイドバーの「Projects」で新しいプロジェクトを作り、Context にこのリポジトリを追加する
3. 歯車 → Memory → Project instructions に、[`claude/project-instructions.md`](claude/project-instructions.md) の枠の中を貼る
4. 問題はスクリーンショットか要約で伝え、考えたことと「ヒントだけ／解説まで」を伝える

開催中のコンテストの問題には使えません（AtCoder生成AI対策ルール）。Claude は atcoder.jp のページを開きません。

## 学習の記録を残す

解説の最後に「記録用まとめを出して」と頼み、出たコードブロックを手元の Claude Code（このフォルダで `claude` を起動）に `/record-problem` に続けて貼ると、`notes/<問題ID>.md` に1問1ファイルで記録されます。`notes/` は GitHub に上がりません。

## リポジトリの中身

| 場所 | 中身 |
| --- | --- |
| `docs/` | 教材の本文（Markdown）と、生成した索引・一覧 |
| `snippets/` | 本文に取り込むコード片（完全なプログラムと検査の設定） |
| `data/` | 問題の台帳（裏付けの記録）と、最近の ABC の分類 |
| `claude/` | claude.ai での解説の手順と、記録用まとめの形式 |
| `tools/` | 骨格・索引の生成と、各種の検査（使い方は `tools/README.md`） |
| `overrides/` | サイトのテンプレート・CSS・JS |
| `planning/` | 要件・決定事項・調査・設計・進捗（制作の記録） |

## 手元でサイトを見る

[uv](https://docs.astral.sh/uv/) と Node.js が要ります。

```bash
uv sync --locked
uv run mkdocs serve        # http://127.0.0.1:8000/kyopro-atlas/
```

検査は `python3 tools/check_pages.py`、`python3 tools/check_snippets.py`、`npm ci && npm run lint:text` で行います。
