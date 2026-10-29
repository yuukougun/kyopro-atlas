# 検証する担当への共通の指示（工程11）

ほかの担当が Issue を直した結果を、書いた本人とは別の目で確かめる。リポジトリは /home/yuuki/projects/kyopro2/kyopro-atlas、サイトは https://yuukougun.github.io/kyopro-atlas/ （公開中のサイトはまだ直す前の状態）。

## 確かめること

1. Issue の本文（`gh issue view <番号>`。読むだけ）の「完了の条件」「直したあとの状態」を満たしているか
2. 直した箇所が planning/checklists/ の観点（fact・clarity・code・figure のうち関係するもの）と planning/style-guide.md に合っているか。事実（計算量・定義・コード）が正しいか
3. 直したことで、別の箇所が壊れていないか（リンク・anchor・表・数式・図・生成物への影響）
4. 書き換えない検査が通るか：`python3 tools/check_pages.py --page <id>`、必要に応じて `fix_problems.py --check`・`check_snippets.py`・`check_svg.py`・`npx textlint <ファイル>`・`node --test "tests/viz/*.test.mjs"`
5. 表示が要るものは、作業用フォルダへビルドして（`uv run mkdocs build -d <作業用フォルダ>/site`）、ヘッドレスの Chrome で幅 390px とダークモードで撮って見る。リポジトリの site/ には書かない。ビルドしたサイトは `file://` で開かず、作業用フォルダで `python3 -m http.server <ポート> --directory <作業用フォルダ>` を立て、`http://127.0.0.1:<ポート>/site/…` で開く（`file://` では KaTeX などの JS が動かず、数式のエラーを見落とす）。ほかの担当とポートがぶつからないよう、10000〜60000 から選び、使い終えたら止める

差分は `git diff -- <ファイル>` で見る。何を直したかは担当の報告（`planning/batches/fix/<バッチ>/<担当>.md`）にある。

## 守ること

- ファイルを直さない。指摘は報告に書く（直すのは書いた担当）。git は読むだけ
- atcoder.jp・codeforces.com を開かない。第三者のサイトにある問題文の写しや訳（洛谷の問題ページ、記録に引用された問題文の節）も読まない（手引き §2.6）。問題の情報は `python3 tools/ap.py show <ID>` で確かめる

## スクリーンショット

```sh
CH=/home/yuuki/.cache/puppeteer/chrome-headless-shell/linux-146.0.7680.76/chrome-headless-shell-linux64/chrome-headless-shell
# 日本語のフォント：/mnt/c/Windows/Fonts を足した fonts.conf を作業用フォルダに作り、FONTCONFIG_FILE で渡す
FONTCONFIG_FILE=<作業用フォルダ>/fonts.conf timeout 60 $CH --headless --disable-gpu --no-sandbox --hide-scrollbars --no-first-run \
  --window-size=390,3000 --virtual-time-budget=8000 --screenshot=<作業用フォルダ>/名前.png 'file:///…/index.html または http://…'
# ダークモードは --blink-settings=preferredColorScheme=0 を足す
```

fonts.conf の中身：`<?xml version="1.0"?><!DOCTYPE fontconfig SYSTEM "fonts.dtd"><fontconfig><include ignore_missing='yes'>/etc/fonts/fonts.conf</include><dir>/mnt/c/Windows/Fonts</dir></fontconfig>`

## 報告

- 詳しい報告を `planning/batches/fix/<バッチ>/verify-<担当>.md` に書く：Issue ごとに「合格／直しが要る」、直しが要る点（ファイル・行・理由・直し方の案）
- 最終の返答は短くする（300 字以内）：Issue ごとの合否と、直しが要る点の数、報告のファイルの場所
