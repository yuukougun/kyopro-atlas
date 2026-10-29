# policy-final の報告（グループ policy-draft・Issue #2）

担当：policy-final。作業ツリー：kyopro-atlas-wt/policy-draft（ブランチ docs/policy-draft）。2026-10-29。前の報告は [policy-page.md](policy-page.md)（下書きと、検証の指摘への直し）と [verify-policy-page.md](verify-policy-page.md)。

## 結果の一言

#2 の下書き（draft の pull request #79）を、ユーザーとメインの決定に従って仕上げた。方針のページの「作者が確かめる」のコメント 11 か所をすべて解消して消し、ライセンスの節を足し、stage を reviewed にした。教材のライセンス（本文と図は CC BY 4.0、コードは MIT）を LICENSE・LICENSE-docs・README・mkdocs.yml の copyright に示した。how-to-use の #stub の「完成」の意味を改め、#report から方針のページへリンクした。Issue のひな形に「誤りの報告」のラベルを付け、decisions.md に 2 行を足した。残るのはメインの作業（gen_site・マージ・公開）である。

## 直したファイル

| ファイル | 行 | 内容 |
| --- | --- | --- |
| docs/start/ai-and-sources.md | 全体（141 行） | 下の「方針のページの直し」 |
| LICENSE（新規） | 1〜21 | MIT。Copyright (c) 2026 yuukougun。文は GitHub の license API（`gh api licenses/mit`）のひな形のまま。許諾と無保証の文が overrides/assets/vendor/katex-0.16.47/LICENSE（MIT）と一字一句同じことを diff で確かめた |
| LICENSE-docs（新規） | 1〜29 | CC BY 4.0 の告知：対象（docs/ のページと図）、対象でないもの（コードとそのほかのファイルは MIT、同梱の外部のものは各自のライセンス、ページに出る他者の名前・題名）、使うときの表示、コモンズ証と[リーガル・コード](https://creativecommons.org/licenses/by/4.0/legalcode.ja)へのリンク、英語の 3 行 |
| README.md | 55〜63 | 末尾に「## ライセンス」の節。README のほかの節に合わせて です・ます調 |
| mkdocs.yml | 16 | copyright の 1 行：`© 2026 yuukougun ・ 本文と図は CC BY 4.0、コードは MIT ライセンス（ライセンスの説明）`。「ライセンスの説明」は方針のページの #license へのリンク |
| .github/ISSUE_TEMPLATE/page-error.yml | 9 | `labels: ["誤りの報告"]` |
| docs/start/how-to-use.md | 272・274・290 | #stub の表の「完成」の行と、表の下の段落。#report の末尾に、方針のページ（#contact）へのリンクの 1 文。front matter は変えていない（updated は 2026-10-29、stage は reviewed のまま） |
| planning/decisions.md | 79・80 | 2026-10-29 の表に「教材のライセンス（#2）」と「段階「完成」の意味（#2）」の 2 行 |

## 方針のページの直し

### front matter

- stage：draft → reviewed（指示のとおり）。updated は 2026-10-29 のまま
- summary：「作者が目を通したページから「完成」にしていく流れ」を「別の AI の担当と機械の検査で確かめている流れと、段階「完成」の意味」にし、示すものに「ライセンス」を足した（2 文・113 字）。要点の「何のページか」も同じ文
- sections：`license`（教材のライセンス）を `contact` の前に足した。ほかの anchor は変えていない
- aliases：「ライセンス」を足した（別名の行にも足した）
- related：how-to-use#report を足し、近い順に how-to-use#stub を先頭にした

### 本文

| 節 | 直したこと |
| --- | --- |
| 要点 | 「今の段階」（2026-10-29 の数）を外し、「作者の役割」にした：目的・読者・範囲と制作の約束を決め、設計を確かめ、公開してよいかを判断している。すべての記述を作者が確かめたわけではない。「使い方」に #license を足した |
| 導入 | 示すものにライセンスを足した |
| ai-writing | 確かめ方を 4 段にし、4 段目「Issue の対応」を足した。機械の検査に週 1 回の全コード片のコンパイルと外部リンクの確認を足した。段階は、各ページの最後の行に出ること（#9）と、下書き・検証済み・完成の意味を書き、4 つの一覧は how-to-use#stub へのリンクにした。完成は「執筆・別の担当の検証・Issue の対応を一通り終え、作者が公開してよいとした。作者がすべての記述を確かめたわけではない」。日付つきのページ数は外した |
| no-copying | 「他者の文章・図・コードは転載しない」と書き、コードの行に「資料のコードは写さない」を足した。USACO Guide の行を外し、条件のある資料は「CC BY-SA の資料」（cp-algorithms・OI Wiki）と「問題文を引用している解説」（決まりの形「読まず…参照する」に改めた）の 2 行にした。同梱のソフトウェアの段落は license の節へ移した |
| citations | 参考の節のないページを、数え直した結果で「トップページ・分野の入口・用語集・索引・一覧・勉強したいリスト」にした。出題者の資料を「解説・解答例。典型90問では問題文も」にし、台帳に残すのを「確かめた資料の URL」にした。典型90 の出題者の解説を公式の解説と書いた |
| noai | 確かめる 2 か所（meta・X-Robots-Tag）と利用規約を書き、robots.txt は判定に入れていないと 1 文で書いた。AtCoder・Codeforces の段落を記録にある事実だけにした（下の表の 127 行） |
| license（新規） | 本文と図は CC BY 4.0（コモンズ証へのリンク）、コードは MIT（ページのコード片・元のプログラム・サイトを作るプログラム）、同梱の外部のもの（ACL は CC0、KaTeX・Cytoscape.js・cytoscape-dagre は MIT）は各自のライセンス。使うときの表示（kyopro-atlas・作者 yuukougun・ページの題名と URL、CC BY 4.0 へのリンク、手を加えた旨）、LICENSE-docs・リーガル・コード・LICENSE・README へのリンク、他者の名前や題名は対象外 |
| contact | 受け口は GitHub の Issue だけでアカウントが要ること、各ページの「このページの誤りを報告する」と how-to-use#report への案内。対応の手順 5 つを「連絡を受けたら、内容を確かめ、誤りや問題があれば直す」の 1 文にした |
| 参考 | USACO Guide の行を外した。decisions.md の行の説明にライセンスと「完成」の意味を足した。工程11 の README（Issue を直して別の担当が検証する流れ）と、Creative Commons の「表示 4.0 国際」（コモンズ証）の行を足した |

### 解消した「作者が確かめる」のコメント（11 か所。すべて消した）

行は直す前の番号である。

| 行 | 内容 | 解消のしかた |
| --- | --- | --- |
| 26 | ページ全体が下書き | 消した（stage は reviewed） |
| 33 | 公開する日に「完成」の数を直す | 日付つきのページ数を本文から外し、時がたっても変わらない文（作者の役割・各段階の意味）にした |
| 51 | 3 つの約束を「作者が決めた」と書いてよいか | ユーザーの決定 (3)。文はそのまま |
| 70 | #9 の段階の表示 | #9 で各ページの最後の行に段階と更新日が出る（overrides/main.html の kp-page-info。段階は how-to-use#stub へのリンク）ので、そう書いた。段階の名前は表示（main.html の STAGE_NAME）と how-to-use#stub にそろえて「下書き」にした（前は gen_site.py の STAGE_JA の「本文あり・未検証」） |
| 83 | 「他者のコードを写さない」 | メインの決定。「他者の文章・図・コードは転載しない」 |
| 91 | USACO Guide | メインの決定。行と参考を外した |
| 106 | 出題者の問題文 | メインの決定。台帳で出題者の問題文が evidence にあるのは典型90の 4 問（typical90_bc・bg・bk・bt）だけなので、「典型90問では問題文も」と限った |
| 121 | robots.txt | メインの決定。判定に入れていないと明記した（下の判断 2） |
| 127 | AtCoder の例外 | メインの決定。書いたのは記録にある事実だけである：問題・解説ページに noai・noimageai がある、Codeforces にも同じ指定がある（どちらも 2026-10-21 に確かめた。decisions.md 25・26、research/00 136）、問題・解説ページ（atcoder.jp とそのサブドメイン）と codeforces.com を AI で開かない（CLAUDE.md）、言語の一覧（img.atcoder.jp の静的ファイル）に noai がないことを同じ日に確かめた（decisions.md 25）。オプションの一覧をどこから読んだか、20261014 版のルールをどこで読んだかは書いていない。cpp-environment の参考へのリンクも外した |
| 142 | GitHub 以外の受け口 | ユーザーの決定 (2)。受け口は GitHub の Issue だけ |
| 154 | 対応の手順・期限 | ユーザーの決定 (1)。手順と期限を書かず、「内容を確かめ、誤りや問題があれば直す」にした |

## 今回足した・変えた記述の裏付け

| 記述 | 確かめた記録 |
| --- | --- |
| 3 つの約束は作者が決めた | ユーザーの決定 (3)（このバッチの指示） |
| 4 段目「Issue の対応」（見つけた点と読者からの要望を Issue にまとめて直し、別の担当が検証する） | decisions.md 2026-10-29（Issue #4〜#77 を調査で作り、メインが直す）、batches/fix/README.md（直す → 別の担当が検証）。Issue #1 は作者以外のアカウントの要望で、decisions.md で対象に入れた（`gh issue list` で確かめた） |
| 全コード片のコンパイルと外部リンクの確認は週 1 回 | .github/workflows/snippets-weekly.yml・links.yml の schedule |
| 段階は各ページの最後の行に出る | overrides/main.html 336〜（STAGE_NAME・kp-page-info・#stub へのリンク）。ビルドした方針のページでも「段階 検証済み・更新日 2026-10-29・このページの誤りを報告する」が出る |
| 「完成」の意味 | ユーザーの決定 (5) |
| 参考の節のないページ | stage を持つ 357 ページのうち glossary・problem-index・term-index・study-list の 4 つ（数えた）と、生成するページ（トップ・分野の入口・一覧・詳細索引） |
| 出題者の資料 | 台帳：典型90 は載る 67 問中 55 問に出題者の evidence（出題者のものだけが 35 問）、鉄則本 11 中 10（10）、アルゴリズムと数学 4 中 4（3）、ACL Practice 12 中 4（4。ACL の使用例）。問題文は typical90_bc・bg・bk・bt の 4 問 |
| 参考に atcoder.jp・codeforces.com の URL がない | 参考の節を数え直して 0 |
| 図はこの教材のものだけ | docs の画像の参照 370 はすべて SVG、外部の画像・img タグは 0。docs/img の 415 枚はすべて SVG。Mermaid 10、動く図 28 |
| ページのコード片は snippets/ から取り込んだもの（だから MIT と書ける） | docs の ```` ```cpp ```` 1149 個はすべて取り込み（`--8<--`）だけで、直接書いた C++ は 0（数えた。手引き §2.7 の決まりとも合う） |
| 同梱の外部のもののライセンス | third_party/ac-library/LICENSE（CC0 1.0 Universal）、overrides/assets/vendor/SOURCES.txt と各 LICENSE（KaTeX・Cytoscape.js・cytoscape-dagre と内蔵の dagre・graphlib。どれも MIT の許諾文） |
| CC BY 4.0 の正式名と条件 | creativecommons.org の deed.ja（h1「表示 4.0 国際」。クレジットの表示・ライセンスへのリンク・変更の明示が条件で、営利目的も可）と legalcode.ja（「クリエイティブ・コモンズ 表示 4.0 国際 パブリック・ライセンス」）。どちらも 2026-10-29 に check_noai.py で HTTP 200・noai なし。文は写さず、自分の言葉にした |
| footer の copyright にリンクが効く | Material 9.7.7 の partials/copyright.html は `config.copyright` をそのまま出す。ビルドした HTML で `&copy;` とリンクがエスケープされずに出ることを確かめた |
| ラベル | `gh label list` で「誤りの報告」がある（#D93F0B）。ひな形の `labels` は、出した人の権限によらず Issue に付く（main.html 339〜340 の「付けない」は URL の引数の話で、別のもの） |

## 流した検査

- `python3 tools/check_pages.py -v --page ai-and-sources`：エラー 0・警告 0
- `python3 tools/check_pages.py -v --page how-to-use`：エラー 0・警告 0
- `python3 tools/check_pages.py`（全体）：357 ページ、エラー 0・警告 0（draft 3・reviewed 354）
- `npx textlint docs/start/ai-and-sources.md`：0 件（途中で 1 文が 121 字の警告が出たので 2 文に分けた）
- `npx textlint docs/start/how-to-use.md`：エラー 0・警告 4（144・197・237・417 行）。HEAD の版を作業用フォルダに写して同じ設定で流すと同じ 4 件（417 行は 2 行ずれて 415 行）で、どれも変えていない行
- `python3 tools/fix_code_links.py --check --stat --page ai-and-sources`：直すところ 0（`snippets/` は how-to-use と同じリンクにした）
- `python3 tools/gen_site.py --check`：生成物が古い 7 ファイル（docs/start/index.md・docs/lists/kind-guide.md・docs/llms.txt・docs/index/start.md・overrides/assets/data/graph.json・docs/guide/term-index.md・docs/start/how-to-use.md の版のブロック）。summary・aliases・sections・stage を変えたので想定どおり。メインが流す
- YAML：mkdocs.yml（copyright の値）と page-error.yml（キーの並びと `labels: ['誤りの報告']`）を読み直した
- `uv run --frozen mkdocs build -d <作業用フォルダ>/site` と `--strict`：どちらも成功・警告なし。HTML で h2 の id 7 つ（ai-writing・no-copying・citations・noai・license・contact・references）、コメントが残っていないこと、footer、how-to-use から ai-and-sources/#ai-writing・#contact へのリンクを確かめた
- `python3 tools/render_pages.py <作業用フォルダ>/site --page ai-and-sources --page how-to-use --width 360,390`（ライト・ダーク）：エラー 0。警告 2 は how-to-use#levels の表（幅 402px。変えていない節で、#55 の範囲）
- 目で確かめた：方針のページを幅 390px のライトとダークで節ごとに撮った（render_pages の CDP の部品を使う小さなスクリプト。作業用フォルダの shoot.py）。横ずれなし（scrollWidth 390）、要点・箇条書き・関連・最後の行・footer の copyright まで崩れなし。how-to-use の #stub の表と #report も撮った

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/policy-final/policy-final（ビルド・写真・CC のページの写し・MIT のひな形）。リポジトリの site/ と docs/ には一時ファイルを作っていない。

## 提案（共有のファイル。メインが反映する）

1. **「完成」の意味のそろえ直し**（決定 (5) と食い違う記述で、直してよいファイルの外）
   - docs/index.md 8 行（info「制作中」）：「作者が目を通したページから順に完成にしていく。」→ 例「執筆・検証・Issue の対応を一通り終えたら、全ページを完成にする。」
   - README.md 6 行（状態）：同じ食い違い。「全 353 ページ」も今は 357
   - planning/progress.md 106 行（次にやること 5「ユーザーがページに目を通し、よければ stage を done にする」）と 114 行（「done はユーザーが目を通してから付ける」）
2. **decisions.md の #2 の行（67 行）**：「公開はユーザーが事実を確かめてから」のままである。残りの決定（連絡を受けたときの対応は細かく決めない、受け口は GitHub の Issue だけ、3 つの約束は作者が決めた、robots.txt は判定に入れない、USACO Guide は挙げない、出題者の資料も参考にした、典型90 の出題者の解説は公式の解説）を 1 行にまとめて足すか、67 行の補足を書き換える（今回は頼まれた 2 行だけを足した）
3. **page-error.yml の種類**：出典についての申し出（記事が写されている・参考の行の誤り・参考から外してほしい・AI の利用を断るサイト）に合う選択肢がなく、「その他」を選ぶことになる。dropdown に「出典・転載・AI の利用についての申し出」を足し、冒頭の markdown に方針のページ #contact へのリンクを足すとよい（今回は labels だけを変えた）
4. **付録 B**：creativecommons.org を足す（2026-10-29 に check_noai.py で deed.ja・legalcode.ja とも HTTP 200・noai なし。方針のページの参考とリンクで使う）。前の報告の提案（img.atcoder.jp の記録）と、検証の補足（kenkoooo.com の AtCoder Problems）も未反映
5. **how-to-use.md 261 行**：「問いと解き方を第三者の解説で確かめている」を方針のページ #citations にそろえる（例「第三者や出題者が公開している解説・解答例で確かめている」）。前の報告の提案 1 と同じ
6. **手引き**：§2.6 に「他者のコードを写さない」（方針として書いたので）、§11 の OI Wiki を「CC BY-SA 4.0 と SATA」に、§10・§15-6 に出題者の資料（典型90 などの GitHub の解説・解答例・問題文、ACL の使用例）を使ってよいことを足す。前の報告の提案 2・3 と同じ
7. **tools/gen_site.py の STAGE_JA**（93 行）：draft が「本文あり・未検証」で、ページの表示（main.html の STAGE_NAME）と how-to-use#stub の「下書き」と違う。今は stage-summary のブロックを置いたページがないので見えないが、そろえるとよい
8. **gen_site.py の start の説明**（64 行）：「この教材の使い方、記法と用語の約束、AtCoder の仕組み」に「出典と AI 利用の方針」を足す（前の報告の提案 1）
9. **how-to-use の related**：ai-and-sources を足す（前の報告の提案 5）
10. **README の「リポジトリの中身」の表**：LICENSE・LICENSE-docs の行を足すか（任意）

## メインに判断してほしい点

1. **本文と図のほかのファイルのライセンス**：LICENSE-docs と README では docs/ だけを CC BY 4.0 にし、それ以外（snippets/・tools/・tests/・overrides/ に加えて planning/・claude/・data/・設定のファイル・README）をまとめて MIT にした。対象に隙間がなく、GitHub もリポジトリを MIT と表示する。planning/ などの文書も CC BY 4.0 にしたいなら、LICENSE-docs の「対象」「対象でないもの」、README の 2 つ目の項目、decisions.md 79 行を直す
2. **robots.txt の 1 文**：方針のページ 101 行に「robots.txt でのクローラの拒否は、この判定に入れていない」と明記した。理由は記録にないので書いていない。触れずに済ませるなら、この 1 文を消すだけでよい
3. **copyright のリンク**：方針のページの #license へ絶対 URL でリンクした。footer はどのページにも同じ文字のまま出るので、相対のパスではページの深さによって切れる。手元の mkdocs serve では公開中のサイトへ移る
4. **4 段目の「読者から寄せられた要望」**：Issue #1（作者以外のアカウント）を指す。名前は出していない

## 使った出典

- creativecommons.org：https://creativecommons.org/licenses/by/4.0/deed.ja と https://creativecommons.org/licenses/by/4.0/legalcode.ja（check_noai.py で 1 回ずつ、curl で 1 回ずつ。題名・正式名・条件を確かめた）
- GitHub の license API（`gh api licenses/mit`。MIT のひな形）
- ほかはリポジトリの記録（CLAUDE.md、planning/decisions.md・progress.md・requirements.md・style-guide.md・checklists/fact.md・code.md・research/00-curriculum.md・research/README.md・batches/fix/README.md・brief-fix.md・前の 2 つの報告、tools/check_noai.py・gen_site.py・fix_code_links.py・render_pages.py・render_svg.py・textlint_targets.py、data/problems.yaml、overrides/main.html・assets/vendor/SOURCES.txt と各 LICENSE、third_party/ac-library/LICENSE、.github/workflows/、schema/page.schema.json、Material の partials/copyright.html）と、Issue #2 の本文・Issue の一覧・ラベルの一覧（読んだだけ）
- atcoder.jp・codeforces.com は開いていない

## 使用量の目安

道具の呼び出し約 75 回、Web の取得 4 回（check_noai 2・curl 2）と GitHub API 1 回、ビルド 2 回（各 15 秒ほど）、描画の確かめ 3 回、所要時間は 1 時間ほど。

## 検証の指摘への対応（2026-10-29）

検証の報告は [verify-policy-final.md](verify-policy-final.md)（指摘 9：必須 5・軽微 4）。直してよいファイルの範囲（方針のページ、LICENSE・LICENSE-docs、README のライセンスの節、mkdocs.yml の copyright、page-error.yml の labels、how-to-use の #stub と #report のリンク、decisions.md の 2026-10-29 の表への行の追加）の中で直し、範囲の外のものは文の案を「提案」に書いた。行の番号は直した後のもの。

### 指摘ごとの対応

| 指摘 | 対応 | ファイルと行 |
| --- | --- | --- |
| 1 必須・メイン：問題文の写し・訳を読んだ記録 | 一部。開示の段落を足した（直し方の (a) と (b) のどちらでも要る部分）。今後の扱い（写し・訳も読まないか）は書いていない（メインに判断してほしい点 1） | docs/start/ai-and-sources.md 90 |
| 2 必須：トップページの「作者が目を通したページから」 | 直していない（docs/index.md は担当外）。文の案は提案 1 | — |
| 3 必須：README の「状態」 | 直していない（README で直してよいのはライセンスの節だけ）。提案 2 | — |
| 4 必須：how-to-use 261「第三者の解説で確かめている」 | 直していない（how-to-use で直してよいのは #stub と #report のリンクだけで、261 行は #problems）。提案 3 | — |
| 5 必須：KaTeX のフォントは SIL OFL 1.1 | 直した（4 か所） | ai-and-sources.md 115、README.md 59、LICENSE-docs 16〜19、decisions.md 79 |
| 6 軽微：README の CC BY 4.0 の表示の条件 | 直した | README.md 57 |
| 7 軽微・メイン：付録 B に creativecommons.org・kenkoooo.com | 直していない（手引き）。提案 4 | — |
| 8 軽微・メイン：decisions.md の #2 の行が古い | 2026-10-29 の表に 1 行を足した（67 行は変えていない） | decisions.md 81 |
| 9 軽微・メイン：progress.md の「done はユーザーが目を通してから」 | 直していない（担当外）。提案 5 | — |

### 1. 問題文の写し・訳（開示の段落）

検証の挙げた記録を読み直し、ほかの記録も `luogu`・`洛谷`・`AT_`・`問題文の節` などで探した。

- 洛谷（Luogu）の問題ページ（`/problem/AT_…`。記録は「問題の訳」「写し」「問題文と制約」と呼ぶ）で問いや制約を確かめた問題：検証の 11 問（abc214_f・abc230_f・abc299_f〈b3/subsequence-dp.md 8、b3/verify/subsequence-dp.md 19・47・48〉、abc251_g・abc202_f・abc296_g・abc341_g〈b3/verify/convex-hull.md 20・60〉、abc401_g・abc320_g〈b3/verify/bipartite-matching.md 23・24〉、abc261_h・abc209_e〈b3/verify/game-retrograde-analysis.md 23・24〉）に加えて、abc466_f（b6/floor-sum.md 28。floor-sum の候補から外すとき）と atc002_c（b5/verify/problem-sets.md 47。台帳にない候補）の計 13 問。b1/segmented-sieve.md 7 も「制約の確認のために見た」とあるが、問題ページか記事かは書いていない。abc230_f・abc299_f は問い自体も洛谷で確かめている（台帳の evidence は kanpurin の分類の記事だけ）
- コンテストの記録（ikatakos 氏）の問題文の節：要約を確かめるために読んだのは abc455_g と abc424_f（b1/verify/hashing-for-sets.md 14・30）、目に入って検証に使ったのが abc373_f（b1/verify/knapsack-01.md 22）。b1/verify/binomial-coefficient.md 20 の abc202_d（「1 ≤ A, B ≤ 30 も読めた」）はどの節かが分からない。誤って取得・表示されたのは b1/imos.md 8（abc466）・b4/stirling-first.md 18（abc385）・b5/interval.md 32（abc457_e）・b4/verify/steiner-tree.md 21（WebFetch の要約が制約の節の値を返した）で、どれも本文に使っていないと書いている
- 調査の段階（research/03-graph.md 57・142）では、洛谷の問題ページから利用者が付けたタグだけを取り出して集計し、「問題文の翻訳は読んでいない」と書いている。問いや制約を確かめたものではないので、ページには書いていない

ページには、#citations の「何を問い、どう解けるかは、解説で確かめた」の段落（88 行）の次に、次の段落を足した。#noai の 105 行（「問いと解き方は…解説などで確かめる」）はすでに #citations へリンクしているので、どちらから読んでもこの段落に届く。#no-copying の扱い（77 行）から外れたことは、段落の中から #no-copying へリンクして書いた。

> 解説のほかに、第三者のサイトにある AtCoder の問題文の写しや訳を読んだ問題もある。洛谷（Luogu）の問題ページでは、十数問の問いや制約を確かめた。コンテストの記録に引用された問題文の節も、要約を確かめるために読んだことや、誤って目にしたことがある（他者の記事を転載しないの節に書いた扱いから外れる）。どれも、問題文の表現は本文に使っていない。どの問題かは、リポジトリの planning/batches/ にある執筆と検証の報告に残っている。

- 数は「十数問」とした（はっきり書いてあるのが 13 問で、segmented-sieve の 1 件が分からないため）。ikatakos 氏の記録の分は、読んだものと誤って目にしたものの境が記録によってあいまいなので、数を書いていない
- 「問題文の表現は本文に使っていない」は、各記録の書き方（imos・binomial-coefficient・stirling-first・interval は表現を使っていないと書く。洛谷の分は中国語の訳から制約や条件を拾っただけ）による。元の問題文と並べて確かめてはいない（開かないため）
- 「第三者のサイトにある」を付けたのは、典型90 の作者が GitHub に公開している問題文（88 行で参考にしたと書いたもの）と分けるため
- 今後の扱いを書いていないのは、(a)（写し・訳で制約を確かめることを認める）と (b)（写し・訳も読まない）が方針の選択で、どちらにも理由があるため（メインに判断してほしい点 1）

### 5. KaTeX のフォントのライセンス

作業用フォルダの一時的な環境（fonttools 4.68.0・brotli）で、overrides/assets/vendor/katex-0.16.47/fonts/ の woff2 20 個の name テーブルを読んだ。20 個とも ID 13 に「This Font Software is licensed under the SIL Open Font License, Version 1.1.」と著作権者（Design Science, Inc.・Khan Academy）、Reserved Font Name（KaTeX_Main など 12 種）、ID 14 に http://scripts.sil.org/OFL がある。リポジトリに OFL の文書はなく（`grep -rn "OFL\|Open Font"` で 0）、katex-0.16.47/LICENSE は MIT だけである。検証の指摘のとおりだった。

OFL の文書を足すのは vendor の中で担当外なので、「ライセンスの文書は同じディレクトリに置いている」を保ったまま、フォントについて「フォントのファイルの中にライセンスの表示がある」と括弧で足した。

- ai-and-sources.md 115：「…ACL は CC0 である。サイトの表示に使う KaTeX・Cytoscape.js・cytoscape-dagre は MIT ライセンスで、KaTeX のフォントは SIL Open Font License 1.1 である。ライセンスの文書はリポジトリの同じディレクトリに置いている（KaTeX のフォントは、フォントのファイルの中にライセンスの表示がある）。」（1 文が 136 字の警告が出たので 2 文に分けた）
- README.md 59・LICENSE-docs 16〜19：同じ内容（README は です・ます調）
- decisions.md 79：同梱の外部のものの括弧に「KaTeX のフォントは SIL Open Font License 1.1」を足した

### 6. README の表示の条件

README.md 57 を「出典（kyopro-atlas、作者 yuukougun、ページの題名と URL）と CC BY 4.0 へのリンクを示し、手を加えたときはその旨を書けば、複製・改変・再配布ができ、営利の目的にも使えます」にした。同じ読み違いを避けるため、方針のページ 113 行の「出典を示せば」も「下の段落の表示をすれば」にした（すぐ下の 117 行が条件を並べる）。

### 8. decisions.md の行

2026-10-29 の表の末尾（81 行）に「出典と AI 利用の方針のページの仕上げ（#2）」を足した。決定の欄はユーザーの答え（連絡を受けたときの対応は細かく決めない〈急ぎの申し出は少なく、対応できる期間も決まっていないため〉、GitHub のアカウントがない人はこのサイトを見ないと考えて GitHub 以外の受け口は作らない、3 つの約束は作者が決めたと書いてよい、ほかの内容はメインに任せ、ラベルなどリポジトリの設定もメインが変えてよい）で、補足の欄はメインの決定（robots.txt・転載・USACO Guide・出題者の資料・典型90 の公式の解説・AtCoder のページの書き方）と、「仕上げたページは stage: reviewed で公開する（上の #2 の行の、公開はユーザーが事実を確かめてから、に代わる）」、写し・訳の開示を書いた。67 行は変えていない（表の行の追加だけを頼まれているため）。公開の 1 文はメインの判断として書いたので、違えば直してほしい（メインに判断してほしい点 2）。

### 検証の補足のうち、ついでに直したもの

- 補足 6（他者のものの範囲）：LICENSE-docs 20〜21 を「ページやファイルに出る他者のもの（問題の題名、参考に挙げた資料の題名、制作の記録に引用した文など）。この告知と LICENSE のどちらの対象でもない」に、README.md 61 を同じ意味に広げた。planning/ などの MIT のファイルにも、他者の文の引用（調査の記録の規約の 1 文など）があるため。方針のページ 117 行（ページに出る他者のもの）はページの話なので変えていない

### 確かめたこと（直した後）

- `python3 tools/check_pages.py -v --page ai-and-sources`・`--page how-to-use`：どちらもエラー 0・警告 0。全体（`python3 tools/check_pages.py`）もエラー 0・警告 0（357 ページ。reviewed 354・draft 3）
- `npx textlint docs/start/ai-and-sources.md`：0 件。`docs/start/how-to-use.md`：警告 4（144・197・237・417 行。今回は変えていないファイルで、前と同じ）。README.md は textlint の対象（tools/textlint_targets.py。docs/ だけ）の外で、です・ます調の誤りが出るのは前からである。ライセンスの節（55〜61 行）には、それ以外の誤り・警告はない（59 行の文の長さの警告は文を分けて消した）
- `python3 tools/fix_code_links.py --check --stat --page ai-and-sources`：直すところ 0
- `python3 tools/gen_site.py --check`：生成物が古い 7 ファイル（前の報告と同じ。今回は front matter を変えていない）。メインが流す
- `uv run --frozen mkdocs build --strict -d <作業用フォルダ>/site`：成功・WARNING なし（作業ツリーの git status はビルドの前後で同じ）。ビルドした方針のページで、h2 の id 7 つ、足した段落、#no-copying と GitHub の planning/batches へのリンク、ライセンスの 2 項目の文、「作者が確かめる」のコメント 0 を確かめた
- `python3 tools/render_pages.py <作業用フォルダ>/site --page ai-and-sources --width 360,390`：エラー 0・警告 0

### メインに判断してほしい点（この回）

1. **問題文の写し・訳の今後の扱い**（指摘 1）。開示の段落は書いたので、ページは今のままでも記録と食い違わない。決めたら次のどちらかを段落の末尾に足す
   - (b) 読まない（勧める）：「今後は、第三者のサイトにある問題文の写しや訳も読まない。」。あわせて手引き §15-6 に「問題文の写し・訳（洛谷の `/problem/AT_…` など）も読まない」を足し、brief の執筆・検証の指示にも書く。台帳 abc214_f の evidence の https://www.luogu.com.cn/problem/AT_abc214_f は外してよい（記録は planning/batches/ に残るので、ページの段落はそのままで合う）。13 問を解説だけで確かめ直すかは任意（解説に制約のない問題は、ユーザーに確かめてもらうか、本文を「…なら」の仮定の形にする）。勧める理由：77 行の扱い（引用された問題文を読まない）の理由は写し・訳にもそのまま当たる。多くの担当は「問題文を読まない規則」で動いていた（b1/nim.md 29、s10/left-shared.md 29、b2/verify/graph-construction.md 6 は写しのミラーも開いていない）。claude/explain.md 9 も検索結果から AtCoder のページを読まないとしている
   - (a) 認める：「解説に書かれていない制約に限り、今後も写しや訳で確かめることがある。」。手引き §15-6 にも同じ扱いを書く。理由：abc401_g の座標が 10^18 まであることは洛谷で分かり、long long があふれる誤りを直せた（b3/verify/bipartite-matching.md 23・39）
2. **decisions.md 81 行の公開の 1 文**：「仕上げたページは stage: reviewed で公開する（上の #2 の行の、公開はユーザーが事実を確かめてから、に代わる）」をメインの判断として書いた。ユーザーは「ほかの内容はメインに任せる」「一通り終わったら完成にしてよい」と答えたが、公開の条件をはっきり変えたわけではない。違うなら直すか、ユーザーに確かめてほしい
3. **KaTeX のフォントの OFL の文書**：OFL 1.1 は、フォントを配るときに著作権の表示とライセンスを添えることを求める。フォントの name テーブルには著作権と「OFL 1.1 で許諾する」旨と URL があるが、全文ではない。overrides/assets/vendor/katex-0.16.47/ に OFL 1.1 の全文（例 OFL.txt。取得元は先に check_noai.py で確かめる。KaTeX の GitHub のフォントのリポジトリか SIL のサイト）を足し、SOURCES.txt の「katex-0.16.47/ (MIT)」に出所とフォントのライセンスを書くとよい。足したら、ai-and-sources.md 115・README.md 59・LICENSE-docs 19 の括弧書き（フォントのファイルの中にライセンスの表示がある）は消してよい

### 提案（この回。直してよいファイルの外）

1. **docs/index.md 8**（指摘 2・必須）：「このサイトは制作中である。全ページに本文があり、Issue の対応を進めている。執筆・別の担当の検証・Issue の対応が一通り終わったら、ページを完成にする（段階の意味は[ページの段階と「準備中」の帯](start/how-to-use.md#stub)）。」。今は draft が 3 ページ（guide/study-list・guide/problem-index・patterns/circular）あるので、「全体の検証を済ませた」は外した
2. **README.md 6**（指摘 3・必須）：「- 状態：全ページに本文があり、Issue の対応を進めています。執筆・別の担当の検証・Issue の対応が一通り終わったら「完成」にします（作者がすべての記述を確かめたという意味ではありません）」。ページ数は書かない（gen_site の数は 357）
3. **docs/start/how-to-use.md 261**（指摘 4・必須）：「載せた問題は、どれも実在と題名・difficulty を AtCoder Problems の公開データで確かめ、問いと解き方を第三者や出題者が公開している解説などで確かめている（[出典と AI 利用の方針](ai-and-sources.md#citations)）。各行の先頭には「解いた」のチェック欄が付く（[進捗の記録](#progress)）。」。指摘 1 で開示したので「解説など」にした。本文を直すので updated は 2026-10-29 のまま
4. **手引きの付録 B**（指摘 7）：「そのほか」に `creativecommons.org（2026-10-29）` と `kenkoooo.com（AtCoder Problems の公開データ。tools/ap.py が取る。2026-10-29）` を足す。前の報告の提案（img.atcoder.jp の記録）も未反映
5. **planning/progress.md 106・114**（指摘 9）：106 行を「5. Issue の対応が一通り終わったら、全ページの stage を done にする（decisions.md 2026-10-29「段階「完成」の意味」）。直したい点はメインが手引きと照らして直す」に、114 行の後半を「done は Issue の対応が一通り終わってから付ける（同じ行）」にする
6. **overrides/assets/vendor/SOURCES.txt**：「katex-0.16.47/ (MIT)」を「katex-0.16.47/ (MIT。fonts/ の woff2 は SIL Open Font License 1.1)」にする（判断してほしい点 3 と同じ件）
7. 前の報告の提案 3・6〜10 と、検証の補足 1〜4（開かないページの範囲、Scrapbox の名前、チェックリスト F9 の書き方、atcoder-system.md 34）は、この回では触れていない。Scrapbox が Cosense に名前を変えたことは、この回では確かめていないので書いていない

### 使った出典（この回）

- リポジトリの記録（verify-policy-final.md と、そこに挙がった b1〜b6・s10 の報告、research/03-graph.md、style-guide.md §2.5・§2.6・§11・§15・付録 B、decisions.md、progress.md、claude/explain.md、data/problems.yaml、overrides/assets/vendor/ の SOURCES.txt と各 LICENSE、third_party/ac-library/LICENSE）
- PyPI（fonttools・brotli を作業用フォルダの一時的な環境に入れ、フォントの name テーブルを読んだ）。GitHub は `gh issue view 2`・`gh pr view 79` を読んだだけ
- Web のページの取得はしていない。atcoder.jp・codeforces.com・洛谷・ikatakos.com は開いていない（指摘 1 は記録だけで確かめた）

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/policy-final/fixup-policy-final（ビルド、フォントを読むスクリプトと結果 font-names.txt、一時的な環境）。リポジトリの site/ と docs/ には一時ファイルを作っていない。

使用量の目安：道具の呼び出し約 60 回、Web の取得 0 回（PyPI からの導入 1 回）、ビルド 1 回（20 秒ほど）、描画の確かめ 1 回、所要時間は 50 分ほど。
