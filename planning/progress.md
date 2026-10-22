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
| 7 | 試作 | 完了（2026-10-21） | 試作9ページ（下の表） |
| 8 | 本制作 | 完了（2026-10-22。8a 骨格・8b 本文。全 353 ページが draft） | [batches/b1/STATE.md](batches/b1/STATE.md) |
| 9 | スキル作成 | 完了（2026-10-22） | .claude/skills/record-problem・claude/（解説の手順 v1） |
| 10 | 全体の検証 | 進行中（洗い出しと直し：batches/s10/） | [batches/s10/](batches/s10/)（audit-*.md・fixed-*.md・left-*.md） |

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
- 残り：用語の索引の漢字の読み（五十音順にするか。工程10 の残り）。~~docs/index/*.md に search: exclude を足す~~ 済み（gen_site.py が front matter に入れる）

## 工程7：試作

9ページの骨格を make_skeleton で作り、執筆担当9本が並列で本文を書いている（2026-10-21 開始）。書き終えたら、別の担当が検証（事実・コード・分かりやすさ・図）し、直す。各担当の使用量（トークン・時間）を記録して、全体の見込みを出す（T21）。

| ページ | 種類 | 執筆 | 検証 |
| --- | --- | --- | --- |
| basics/binary-search-answer | 基礎 | 完了 | 完了 |
| dp/bit-dp | 水・DP | 完了 | 完了 |
| ds/lazy-segment-tree | 水・データ構造・動く図 | 完了 | 完了 |
| comb/linearity-of-expectation | 水・数学 | 完了 | 完了 |
| graph/extended-dijkstra | 水（青の節）・グラフ | 完了 | 完了 |
| cpp/cpp-views-basics | C++ | 完了 | 完了 |
| tree/hld | 発展の概要 | 完了 | 完了 |
| patterns/bracket-sequence | 題材別 | 完了 | 完了 |
| math/floor-sum | 黄・数学 | 完了 | 完了 |

## 試作の結果

- 9ページを執筆→検証（別の担当）→直しの流れで仕上げた。検証で事実の誤りが各ページに1〜4件見つかり、すべて直した。詳細と使用量は [batches/pilot.md](batches/pilot.md)、検証の報告は batches/pilot-verify/
- 試作をサイトで確かめるため、工程8a の骨格（準備中の343ページ）を作り、公開した（ユーザーの選択）
- 全体の見込み：1ページあたり約35〜45万トークン、残り約340ページで約1.2〜1.5億トークン・作業時間は合計約20時間
- 手引きに §13「試作で決めたこと」を足した。用語集に13語

## 本制作の進め方（8b。記録）

- 1ページずつ「執筆 → 検証（別のエージェント、checklists の4観点）→ 直し」を、終わったページから次へ進める流れ（ワークフローの pipeline）で並列に回す。同時に動かすのは最大20（1本のワークフローは16まで。20にするには2本に分ける）
- 執筆者に渡すもの：手引き・見本（基礎は basics/binary-search-answer、水以上は ds/lazy-segment-tree、C++ は cpp/cpp-views-basics）・interfaces・catalog の項目・台帳。共有ファイルへの提案は `planning/batches/<バッチ>/<id>.md` に書かせる
- 1ページあたり約13分・約32万トークン（試しの計測）
- 止めるときはページの段階を `batches/<バッチ>/STATE.md` に残し、途中で止まったページは骨格に戻すか、その段階をやり直す

## 次にやること

1. ~~ユーザーに試作を見てもらい、見本の2枚を決める~~ 完了（見本は basics/binary-search-answer と ds/lazy-segment-tree。C++ は cpp/cpp-views-basics）
2. ~~9b：claude.ai の実機確認~~ 完了（2026-10-21）：新しい Projects で、索引からのページ・節の URL、atcoder.jp を開かない、開催中のコンテストを断る、ファイルを変更しない、記録用まとめ、のすべてをユーザーが確認した
3. 工程8b（本文）：完了（2026-10-22。全 353 ページが draft。b1 基礎・水 173、b2 青 46、b3 黄 35、b4 発展の概要 50、b5 横断 33）。動く図は置き場のあった19個すべてを作成・検証・直し（batches/viz/）。残りと次の順：
   1. ~~b2・b3 の提案の反映~~ 完了（2026-10-22。台帳・用語集117語・手引き §15。方針は batches/b3/decisions.md）
   2. ~~節へのリンクの張り替え~~ 完了（2026-10-22。324か所。相手がまだ stub だったものは 2 回目の張り替えで済み）
   3. ~~発展の概要50ページ（b4）と横断ページ33（b5）~~ 完了（2026-10-22。全353ページが draft）。b4・b5 の提案の反映（手引き §16、batches/b5/decisions.md）と2回目のリンクの張り替え（326か所）も完了
   4. ~~問題の補充~~ 完了（2026-10-22。練習0〜1問の52ページに116行、新しい問題51。batches/b6/）。9c（解説手順の確定）も完了（2026-10-22。claude/ の v1。ユーザーが Project instructions を貼り直す）。残りは下の「工程10：全体の検証」へ移した
   - 並列の進め方：ワークフローの args はページの front matter から機械的に作り、expect（件数）を渡す。commit は動いている担当と混ざらないよう、別の作業ツリー（git worktree）でその分だけを生成・検査してから行うか、すべて止めてから行う。ビルドの確認は `mkdocs build --strict` に -q を付けない

## 工程10：全体の検証

- 洗い出し（2026-10-22）：観点ごとの監査を batches/s10/audit-*.md に置いた（事実・図・関係・共有ファイル・構造）。各観点の「## shared」は共有ファイルの直し、分野ごとの見出しはページの直し
- 直し：共有ファイルの分は batches/s10/fixed-shared.md、直せず判断の要るものは batches/s10/left-*.md
- 残り（洗い出し以前からのもの）：
  - §14〜§16 へのそろえ直し（発展の概要の #library・#resources の節、確認問題の置き場所、箇条書きの句点など。audit-structure.md の ## shared）
  - batches/b5/decisions.md の最後の 2 行（張り替えの残り 6 か所・§16-7 の言い回し）
  - 用語の索引の漢字の読み（五十音順にするか。tools/README.md にも記録）
  - b6 の abc411_e（題名に角かっこ）：道具の正規表現を直し、expectation-tail-sum の練習に載せた（2026-10-22、s10）

## ユーザーにお願いしていること

- ~~`sudo apt install libnspr4 libnss3 libasound2`~~ 済み（2026-10-22 に ldconfig で 3 つとも見つかり、render_svg.py が PNG を作れることを確かめた）
