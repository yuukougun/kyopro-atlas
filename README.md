# kyopro-atlas

AtCoder で黄色（レート 2000）を目指す人のための、**辞書として引く**競技プログラミングの教材です。ABC で解けなかった問題をきっかけに、必要な手法のページを引いて読む使い方を想定しています。

- サイト：https://yuukougun.github.io/kyopro-atlas/
- 状態：全ページに本文があり、Issue の対応を進めています。執筆・別の担当の検証・Issue の対応が一通り終わったら「完成」にします（作者がすべての記述を確かめたという意味ではありません）

## 教材の使い方

- **引く**：検索、用語の索引、逆引き辞典（制約や問題の言い回しから手法を探す）、題材別のページ（括弧列・順列・XOR など）から目的のページを探します
- **順に学ぶ**：色別ロードマップと知識マップで、レベル（基礎・水・青・黄・発展）と前提の順にたどれます
- **ページの読み方**：冒頭の「要点」だけで何ができて、いつ使うかが分かります。続きに理由・処理の流れ・例題（解法は折りたたみ）・練習問題があります
- **進捗**：練習問題の「解いた」、ページ上部の「理解した」、あとで読む「勉強したいリスト」は、ブラウザの中（localStorage）だけに保存されます。端末をまたぐときは「この教材の使い方」のページから、ファイルへの書き出し・読み込みをしてください

## 解けなかった問題を claude.ai で解説してもらう

claude.ai/code の **Projects** で、このリポジトリを読みながら解説してもらえます。

1. [Claude GitHub App](https://github.com/apps/claude) をこのリポジトリに入れる
2. claude.ai/code のサイドバーの「Projects」で新しいプロジェクトを作り、Context にこのリポジトリを追加する
3. 歯車 → Memory → Project instructions に、[`claude/project-instructions.md`](claude/project-instructions.md) の枠の中を貼る
4. 1つのスレッドで1問を扱い、問題をスクリーンショットか要約で伝え、考えたこと・詰まったところと「ヒントだけ／解説まで」を伝える（頼み方の例はサイトの「この教材の使い方」の [claude.ai での解説の頼み方](https://yuukougun.github.io/kyopro-atlas/start/how-to-use/#claude)）

解説には根拠にした教材のページ・節の URL、解けなかった原因の一言、参照した索引の版が付きます。指示の版は v1（2026-10-22）で、`claude/project-instructions.md` の版が上がったら貼り直してください。

開催中のコンテスト（ABC・ARC・AGC・ADT・AWC）の問題には使えません（AtCoder生成AI対策ルール）。Claude は atcoder.jp と codeforces.com のページを開かず、リポジトリのファイルも変更しません。

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
| `LICENSE`・`LICENSE-docs` | ライセンスの文書（`LICENSE` は MIT、`LICENSE-docs` は `docs/` の本文と図の CC BY 4.0。下の「ライセンス」） |

## 手元でサイトを見る

サイトを見るだけなら [uv](https://docs.astral.sh/uv/) だけが要ります（Node.js は表記の検査 textlint にだけ使います）。

```bash
uv sync --locked
uv run mkdocs serve        # http://127.0.0.1:8000/kyopro-atlas/
```

検査は `python3 tools/check_pages.py`、`python3 tools/check_snippets.py`、`npm ci && npm run lint:text` で行います。

## ライセンス

- 教材の本文と図（`docs/` のページと図）は [CC BY 4.0](LICENSE-docs)（クリエイティブ・コモンズ 表示 4.0 国際）です。出典（kyopro-atlas、作者 yuukougun、ページの題名と URL）と CC BY 4.0 へのリンクを示し、手を加えたときはその旨を書けば、複製・改変・再配布ができ、営利の目的にも使えます
- コード（`snippets/` のプログラムとページに載るコード片、`tools/`・`tests/`、`overrides/` のテンプレート・CSS・JavaScript など）と、そのほかのファイルは [MIT License](LICENSE) です
- 同梱している外部のものは、それぞれのライセンスに従います。`third_party/ac-library/`（AtCoder Library）は CC0 1.0 です。`overrides/assets/vendor/` の KaTeX・Cytoscape.js・cytoscape-dagre は MIT License で、KaTeX のフォントは SIL Open Font License 1.1 です。ライセンスの文書は同じディレクトリに置いています（KaTeX のフォントは、フォントのファイルの中にライセンスの表示があります）

問題の題名、参考に挙げた資料の題名、制作の記録に引用した文など、ページやファイルに出る他者のものは、これらのライセンスの対象ではありません。考え方はサイトの[出典と AI 利用の方針](https://yuukougun.github.io/kyopro-atlas/start/ai-and-sources/#license)にあります。
