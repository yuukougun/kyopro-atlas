# 決定事項の記録

要件定義書（[requirements.md](requirements.md)）で決めていなかった点を、ユーザーへの質問と回答で決めた記録。新しい決定は日付を付けて追記する。設計書と食い違う場合は、新しい日付の記録を優先する。

## 2026-10-21 最初の質問への回答

| 項目 | 決定 | 補足 |
| --- | --- | --- |
| 緑以下の基礎知識 | レベル「基礎」を追加し、短めの個別ページを作る | 初歩からの説明は省き、応用の型・落とし穴・上位の手法とのつながりに絞る。逆引き辞典や知識マップで行き止まりを作らないため |
| レベルの基準 | その知識が主に必要になる問題の difficulty 帯 | 基礎：〜1199／水：1200〜1599／青：1600〜1999／黄：2000〜2399／発展：2400〜。difficulty は AtCoder Problems の推定値 |
| 黄色より上（橙 diff 以上） | 「発展」として概要だけの短いページにする | 何ができるか・どんな問題で使うか・ライブラリでの使い方 |
| 進捗・確認の仕組み | 次の3つを入れる：確認問題（折りたたみ）、練習問題の「解いた」チェック、ページの「理解した」チェック | 保存先は localStorage のみ。解いた数はロードマップに、理解度は知識マップの色分けに表示する |
| ACL の扱い | ユーザーは将来、自作ライブラリを作る（ACL にあるものも作り直す）。それまでは ACL も使えるようにする | 各ページは「自分で実装できる粒度の処理の流れ」と「ACL での対応（名前と最低限の使い方）の囲み」を持つ。加えて、自作ライブラリの設計と動作確認（Library Checker など）の横断ページを作る |
| 文体 | だ・である調 | |
| 本制作の順序 | 骨格 → 基礎・水 → 青 → 黄 | 骨格＝全ページの枠（タイトル・メタデータ・数行の要約）、逆引き辞典、知識マップ。発展の概要ページの扱いは設計で決める |
| 優先する分野 | 特になし | 設計で決めた順に進める |
| サイト生成 | Material for MkDocs をバージョン固定で使う | タグ一覧・索引ファイル・知識マップなどの生成は MkDocs に依存しない独立スクリプトで行い、将来 Zensical へ移りやすくする |
| AtCoder のページ | AI では読まない（noai 指定を尊重する） | 問題の実在・タイトル・difficulty は AtCoder Problems の公開データで確認する。要約は知識と第三者の解説記事から短く書き、裏付けが取れない問題は採用しない |
| commit と push | まとまった単位で commit し、push まで任せる | 調査レポートの段階から。GitHub Pages（GitHub Actions でデプロイ）の設定も任せる |
| コード片の検証環境 | ユーザーが `sudo apt install g++-15` を実行する | PPA `ubuntu-toolchain-r/test` に Ubuntu 22.04 向けの GCC 15.2.0 がある。AtCoder の GCC と同じ版 |

## 2026-10-21 質問の前に確認した事実

- **リポジトリ**：GitHub `yuukougun/kyopro-atlas`（public、作成時は空）。公開 URL は `https://yuukougun.github.io/kyopro-atlas/` になる見込み
- **AtCoder の AI 関連の指定**：問題ページと解説ページに `<meta name="robots" content="noai, noimageai">` がある。robots.txt（AI 学習用の Google-Extended と Applebot-Extended は全面拒否）と利用規約には、AI による閲覧を禁じる記述はない。言語一覧（img.atcoder.jp の静的ファイル）には noai 指定がない
- **AtCoder生成AI対策ルール（20261014版）**：ABC・ARC・AGC の開催中は、問題文やその要約を生成 AI に入力して解法やコードを出力させることを禁止している。過去問の練習には適用されない。したがって、claude.ai での解説はコンテスト終了後の問題にだけ使う
- **AtCoder の C++ 環境**（2025-10 の言語アップデート）：C++23 (GCC 15.2.0) と C++23 (Clang 21.1.0)。GCC 版のおもなオプションは `-std=gnu++23 -O2 -Wall -Wextra -march=native -fmodules -ftrivial-auto-var-init=zero -DATCODER -DONLINE_JUDGE -lstdc++exp`。ac-library 1.6・Boost 1.88.0・GMP 6.3.0・Eigen 3.4.0・abseil などが使える。2026-06 に GCC 版から `-flto=auto` が削除された
- **手元の環境**：g++-13（13.4.0、`-std=c++23`）、ACL は `~/lib/ac-library-master`（ドキュメントは `document_ja/`）、VS Code と cph（バンドル機能を足したフォーク版）。Python 3.10、uv、Node.js 24、gh が使える
- **Material for MkDocs**：2025-11 から保守モード（9.7.0 で新機能の追加は終了。重大なバグとセキュリティの修正は少なくとも12か月）。後継の Zensical は alpha（0.0.71、2026-10-16）で、`mkdocs.yml` を読めるがプラグインへの対応は一部
- **AtCoder Problems の API**：非公式。アクセスの間隔は1秒以上空ける。静的な JSON（`problems.json`、`problem-models.json` など）を一度取得し、キャッシュして使う（`tools/ap.py`）
