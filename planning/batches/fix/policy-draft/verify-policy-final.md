# verify-policy-final の報告（グループ policy-draft・Issue #2）

検証：policy-final の直し（docs/start/ai-and-sources.md・LICENSE〈新規〉・LICENSE-docs〈新規〉・README.md・mkdocs.yml・.github/ISSUE_TEMPLATE/page-error.yml・docs/start/how-to-use.md・planning/decisions.md）。作業ツリー kyopro-atlas-wt/policy-draft（ブランチ docs/policy-draft、未 commit）。2026-10-29。ファイルは直していない（この報告だけを書いた）。

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #2 出典と AI 利用の方針 | 直しが要る | 9（必須 5・軽微 4。うち 6 つは共有のファイルで、メインの反映が要る） |

- ユーザーの決定はページに入っている：連絡を受けたときの対応は「内容を確かめ、誤りや問題があれば直す」の 1 文だけ（130 行）、受け口は GitHub の Issue だけ（119 行）、3 つの約束は「作者が決めた」（42〜46 行）、ライセンスは本文と図が CC BY 4.0・コードが MIT（107〜115 行）、「完成」は一通りの作業を終えたもの（61 行）
- 「作者が確かめる」のコメントは 0（ソースとビルドした HTML の両方で確かめた）。作者がすべてを確かめたように読める文は、方針のページにはない（30・61 行で打ち消している）
- LICENSE は MIT の全文で、GitHub の `gh api licenses/mit` のひな形と、末尾の空行 1 つを除いて一字一句同じ。CC BY 4.0 の名前（クリエイティブ・コモンズ 表示 4.0 国際 パブリック・ライセンス）と URL（deed.ja・legalcode.ja）、表示の条件（クレジット・ライセンスへのリンク・変更の明示、営利も可）は creativecommons.org の 2 ページと合う
- how-to-use #stub の段階の説明（表と下の段落）と方針のページの 57〜61 行は一致する。表示名も main.html の STAGE_NAME（下書き・検証済み・完成）と同じ
- トップページ（docs/index.md 10 行）と「この教材の使い方」（how-to-use 61・274・290 行）からのリンクはある。完了の条件の「公開」はメインのマージ待ち
- ただし、方針のページの記述が制作の記録と食い違う点（下の 1）、方針のページと食い違う読者向けの文が残っている点（2〜4）、外部のもののライセンスの誤り（5）がある

## 直しが要る点

### 1. 【必須・メインの判断】問題文の写しを読んだ記録があり、方針のページの 77 行（と 103 行）と食い違う

- ファイル・行：docs/start/ai-and-sources.md 77（「第三者の解説やコンテストの記録のうち、問題文（英訳を含む）を引用して載せているものは、問題文の部分を読まず、解法の部分だけを参照する」）、103（「問いと解き方は第三者や出題者が公開している解説などで確かめる」）
- 理由：制作の記録では、AtCoder の問題文の写しを読んで問題の細部を確かめたことが何度もある。方針のページの字面（noai の指定のあるサイトを開かない）には反しないが、読者は「AtCoder の問題文は写しも含めて読んでいない」と受け取る。リポジトリは public なので、記録は誰でも読める
  - 洛谷（Luogu）の AtCoder の問題ページ（`/problem/AT_…`。記録自身が「洛谷の写し」「問題の訳」と呼ぶ）で制約や問いの細部を確かめた：abc214_f・abc230_f・abc299_f（planning/batches/b3/subsequence-dp.md 8・14）、abc251_g・abc202_f・abc296_g・abc341_g（b3/verify/convex-hull.md 20・46・50・60）、abc401_g・abc320_g（b3/verify/bipartite-matching.md 23・24、b3/bipartite-matching.md 69）、abc261_h・abc209_e（b3/verify/game-retrograde-analysis.md 23・24・37）。どれもページに載る問題である。台帳 data/problems.yaml 5363 行では、abc214_f の evidence に https://www.luogu.com.cn/problem/AT_abc214_f が入っている（ほか b5/verify/problem-sets.md 47 の atc002_c は台帳にない候補）
  - ikatakos 氏の記録の問題文の節（AtCoder の問題文の引用）を、検証役が要約を確かめるために読み（b1/verify/hashing-for-sets.md 14・30）、その内容で abc455_g の summary を直した（b1/hashing-for-sets.md 65）。手引き §11 の「問題文を引用した節を読まない・使わない」にも反する。問題文の節が誤って取得・表示された、または目に入ったという記録も 4 つある（b1/imos.md 8、b4/stirling-first.md 18、b5/interval.md 32 は本文に使っていないと書き、b1/verify/knapsack-01.md 22 は「検証にだけ使った」と書く）
  - 一方で b2/verify/graph-construction.md 6 は「問題文の写しのミラーも開いていない」と書いており、写しを避ける考えはあった
- 直し方の案（どちらにするかはメインが決める。ユーザーに確かめるのがよい）
  - (a) 開示する：#no-copying の 77 行の後か #noai の 103 行の後に、例「制作の途中では、問題の制約や問いの細部を、洛谷にある AtCoder の問題の写し（訳）で確かめたことがある（11 問。台帳と制作の記録にある）。ikatakos 氏の記録の問題文の節を読んで、問題の要約を確かめたこともある（1 問）。どちらも問題文の表現は本文に使っていない。」を足す。今後どうするか（写しや訳も読まないことにするか）も 1 文で書く
  - (b) 直して決まりにする：12 問（洛谷の 11 問と abc455_g）の細部を解説だけで確かめ直し、台帳の abc214_f の evidence から洛谷の問題ページを外し、手引き §15-6 に「問題文の写し・訳（洛谷の AT_ の問題ページなど）も読まない」を足す。方針のページ 77 行は「問題文の写しや訳も読まない」と広げる。過去に読んだことは (a) と同じく 1 文で書く
- 補足：how-to-use 261 行の「問いと解き方を第三者の解説で確かめている」も、この点で事実と合わない（下の 4）

### 2. 【必須・メイン】トップページが「作者が目を通したページから完成にする」のまま

- ファイル・行：docs/index.md 8（info「制作中」：「作者が目を通したページから順に完成にしていく。」）
- 理由：decisions.md 80 行（今回足した「段階「完成」の意味」）と方針のページ 61 行・how-to-use 272〜274 行と食い違い、作者が全ページに目を通すように読める。トップページは方針のページへリンクする入口（Issue の完了の条件）なので、同じ日に公開されると読者の目に食い違いがそのまま入る。policy-final の提案 1 と同じ
- 直し方の案：「執筆・検証・Issue の対応が一通り終わったら、ページを完成にする（段階の意味は[ページの段階](start/how-to-use.md#stub)）。」のように改める。「全ページに本文があり、全体の検証を済ませた」は、後から足した draft の 3 ページ（problem-index・study-list・patterns/circular）があるので、合わせて見直すとよい

### 3. 【必須】README の「状態」が古い

- ファイル・行：README.md 6（「全 353 ページを書き終え…作者が目を通したページから「完成」にしていきます」）
- 理由：2 と同じ食い違い（decisions.md 80 行が README を改めると書いている）。ページ数も今は 357（reviewed 354・draft 3）。README は今回ライセンスの節を足したファイルで、GitHub のリポジトリの入口に出る。policy-final の提案 1 と同じ
- 直し方の案：例「状態：全ページに本文があり、Issue の対応を進めています。執筆・別の担当の検証・Issue の対応が一通り終わったら、ページを「完成」にします（作者がすべての記述を確かめたという意味ではありません）」。ページ数は書かないか、gen_site の数に合わせる

### 4. 【必須】how-to-use が「問いと解き方を第三者の解説で確かめている」のまま

- ファイル・行：docs/start/how-to-use.md 261
- 理由：方針のページ 88 行は「典型90問・鉄則本・アルゴリズムと数学・ACL Practice では、出題者が GitHub に公開している資料も参考にし、それだけで確かめた問題もある」と書く。台帳でも出題者の資料だけで確かめた問題がある（前の検証の 2）。同じ日に公開される 2 つのページが食い違う。1 の写しの件もある。policy-final の提案 5 と同じ
- 直し方の案：「問いと解き方を、第三者や出題者が公開している解説・解答例で確かめている（[出典と AI 利用の方針](ai-and-sources.md#citations)）」。1 で (a) を選ぶなら「解説など」にそろえる

### 5. 【必須】KaTeX のフォントは MIT ではなく SIL Open Font License 1.1

- ファイル・行：docs/start/ai-and-sources.md 113、README.md 59、LICENSE-docs 17、planning/decisions.md 79（どれも「KaTeX・Cytoscape.js・cytoscape-dagre は MIT」「ライセンスの文書を同じディレクトリに置いている」）
- 理由：同梱している overrides/assets/vendor/katex-0.16.47/fonts/ の woff2 20 個は、フォントの中の name テーブル（ID 13 ライセンスの説明・ID 14 URL）に「This Font Software is licensed under the SIL Open Font License, Version 1.1.」「with Reserved Font Name KaTeX_Main」など（著作権者 Design Science, Inc.・Khan Academy）と書いている（fontTools で読んで確かめた。20 個とも同じ）。ディレクトリにある LICENSE は katex の npm の tarball の MIT だけで、OFL の文書はリポジトリのどこにもない（SOURCES.txt も「katex-0.16.47/ (MIT)」）。外部のものの扱いの記述として誤りになる
- 直し方の案：4 か所を「KaTeX は MIT ライセンス（フォントは SIL Open Font License 1.1）」にする。「どれも、ライセンスの文書を…同じディレクトリに置いている」を保つなら、メインが OFL 1.1 の文書を katex-0.16.47/ に足して SOURCES.txt に出所を書く（取得元のドメインは先に check_noai.py で確かめる）。足さないなら、その文を「フォントのライセンスはフォントのファイルの中に書かれている」のように直す

### 6. 【軽微】README のライセンスの節が CC BY 4.0 の条件を一部しか書いていない

- ファイル・行：README.md 57（「出典（kyopro-atlas とページの URL）を示せば、複製・改変・再配布ができ…」）
- 理由：方針のページ 115 行と LICENSE-docs 21〜22 行は、表示の条件を「kyopro-atlas・作者 yuukougun・ページの題名と URL、CC BY 4.0 へのリンク、手を加えたときはその旨」としている。README は作者・題名・ライセンスへのリンク・変更の明示が抜け、出典だけで足りるように読める（コモンズ証の条件も「適切なクレジット・ライセンスへのリンク・変更の明示」）
- 直し方の案：「出典（kyopro-atlas、作者 yuukougun、ページの題名と URL）と CC BY 4.0 へのリンクを示し、手を加えたときはその旨を書けば、複製・改変・再配布ができ…」にそろえる

### 7. 【軽微・メイン】付録 B に creativecommons.org（と kenkoooo.com）がない

- ファイル・行：planning/style-guide.md 付録 B（454〜行）。方針のページ 101 行は「確かめたドメインは…付録 B に記録している」と書き、141 行の参考と 111・115 行のリンクで creativecommons.org を使う
- 理由：手引き §11 の手順どおり、policy-final は check_noai.py の結果を報告に書き、付録 B への追加を提案した（提案 4）。反映されるまで、101 行の文がこのページ自身で成り立たない。この検証でも 2026-10-29 に check_noai.py で deed.ja・legalcode.ja とも HTTP 200・noai・noimageai なしを確かめた。AtCoder Problems（kenkoooo.com）も、方針のページ 53・103 行が「公開データで確かめる」と書く資料だが付録 B にない（前の検証 verify-policy-page.md の確認が 2026-10-29）
- 直し方の案：メインが付録 B の「そのほか」に `creativecommons.org（2026-10-29）`・`kenkoooo.com（AtCoder Problems の公開データ。2026-10-29）` を足す

### 8. 【軽微・メイン】decisions.md の #2 の行が古く、ユーザーの決定の一部が記録にない

- ファイル・行：planning/decisions.md 67（「公開（マージ）はユーザーが事実を確かめてから」）
- 理由：同じ 2026-10-29 の表の 80 行（「一通りの作業が終わったら、全ページを完成にしてよい」）と食い違う。方針のページを仕上げて公開することにしたのに、記録が「ユーザーが確かめてから」のままである。今回のユーザーの決定のうち、連絡を受けたときの対応は細かく決めない・受け口は GitHub の Issue だけ・3 つの約束は作者が決めた、は decisions.md にない（policy-final の報告にだけある）。policy-final の提案 2 と同じ
- 直し方の案：67 行の補足を「下書きを draft の pull request で見せた。2026-10-29 にユーザーが方針を決め（連絡を受けたときの対応は細かく決めない、受け口は GitHub の Issue だけ、3 つの約束は作者が決めたと書く、ほかはメインに任せる）、仕上げて公開する」のように改めるか、1 行足す。1 の結論もここに残す

### 9. 【軽微・メイン】progress.md が「done はユーザーが目を通してから」のまま

- ファイル・行：planning/progress.md 106（次にやること 5「ユーザーがページに目を通し、よければ stage を done にする」）、114（「done はユーザーが目を通してから付ける」）
- 理由：decisions.md 80 行と食い違う。方針のページ 139 行の参考が progress.md を「執筆・検証の流れ」として挙げているので、参考をたどった読者が反対のことを読む。policy-final の提案 1 と同じ
- 直し方の案：106 行を「Issue の対応が一通り終わったら、全ページの stage を done にする（decisions.md 2026-10-29「段階「完成」の意味」）」に、114 行の後半を同じ意味に改める

## 確かめたこと（問題のなかったもの）

- Issue #2 の「やること」の 5 項目は、それぞれ節になっている（ai-writing・no-copying・citations・noai・contact）。ライセンスの節（license）を足した。要点・別名の行・導入・sections の 6 つの anchor・related は整っている
- 記録との照合（1 以外は合う）
  - 4 段の確かめ方：checklists の 4 観点、.github/workflows/check.yml（push と pull_request で check_pages・textlint・変わったコード片を gcc:15.2.0 で）、snippets-weekly.yml（すべてのコード片、毎週日曜）、links.yml（外部リンク、毎週月曜）、progress.md 工程10 の 2 巡と 5 観点（構成・関係・事実・図・共有ファイル）と日付 2026-10-22、Issue #1 は作者以外のアカウント（Haruki07-crew）の要望
  - 段階の表示：overrides/main.html 338〜387（id を持つページの最後の行に段階と更新日、段階は how-to-use#stub へのリンク、報告のリンクに題名・URL・更新日）。ビルドした方針のページでも「段階 検証済み・更新日 2026-10-29・このページの誤りを報告する」が出る
  - 図：docs の画像の参照 370 はすべて SVG、外部の画像・img タグ 0、外部の画像を埋めた SVG 0、Mermaid 10、動く図 28
  - コード：docs の ```` ```cpp ```` 1149 個はすべて snippets/ からの取り込み（base_path は snippets）。直接書いたのは ```` ```bash ```` 3 個（コマンド）と ```` ```text ```` 142 個（擬似コードなど）で、手引き §2.7 のとおり
  - 参考の節のないページ：stage を持つ 357 ページのうち glossary・problem-index・study-list・term-index の 4 つと、front matter のない 67 ファイル（トップと分野の入口 16・詳細索引 15・一覧 36）。88 行の記述と合う
  - 参考に atcoder.jp・codeforces.com（サブドメインを含む）の URL は 0。atcoder.jp へのリンクはすべて /tasks/ の問題リンク
  - 出題者の資料：台帳でページに載る典型90 67 問・鉄則本 11 問・アルゴ数学 4 問・ACL Practice 12 問の evidence に、出題者の GitHub の資料（github.com/E869120/kyopro_educational_90・kyopro-tessoku・math-algorithm-book、github.com/atcoder/ac-library）がある。問題文の evidence は typical90_bc・bg・bk・bt の 4 問（problem/・problem-txt/）
  - noai：tools/check_noai.py は robots の meta（クローラの名前の meta を含む）と X-Robots-Tag を見て、robots.txt は --robots で表示するだけで判定に入れない。101・96〜99 行と合う。AtCoder・Codeforces の指定と日付は decisions.md 25・26 と合う
- ライセンス：LICENSE（MIT の全文）、LICENSE-docs の対象（docs/ で追跡しているのは .md 424・.svg 415・llms.txt 1 だけで、図はすべて docs/img/ にある）と対象外の振り分けに隙間はない。third_party/ac-library/LICENSE は CC0 1.0、Cytoscape.js・cytoscape-dagre（内蔵の dagre・graphlib を含む）は MIT（KaTeX のフォントだけが 5）。mkdocs.yml の copyright は YAML として正しく、ビルドした footer に `© 2026 yuukougun ・ 本文と図は CC BY 4.0、コードは MIT ライセンス（ライセンスの説明）` がリンクつきで出る
- Issue のひな形：page-error.yml は YAML として読め、キーは name・description・title・labels・body。ラベル「誤りの報告」はリポジトリにある（`gh label list`、#D93F0B）。main.html 339〜340 行の「labels を付けない」は URL の引数の話で、ひな形の labels とは別である
- 作者の役割：48 行の「設計は…作者が確かめてから進めた」は progress.md 工程5（ユーザーの承認）・decisions.md 33〜42 と合う。docs の中で「作者が」「目を通」を含む文は、2 の docs/index.md 8 行と、gen_site が古い summary から作った生成物（docs/start/index.md 17・docs/lists/kind-guide.md 19・docs/llms.txt 35。gen_site を流せば直る）だけ
- 表示：作業用フォルダにビルドし、http.server（127.0.0.1:47213。使い終えて止めた）経由でヘッドレスの Chrome で幅 390px のライトとダークで方針のページの全体、how-to-use の #stub（ダーク）と #report（ライト）を撮って見た。要点・番号つきの 4 段・段階の箇条書き・meta タグのインラインコード・ライセンスの節・参考・関連・最後の行・footer まで崩れはない

## 書き換えない検査

- `python3 tools/check_pages.py -v --page ai-and-sources`・`--page how-to-use`：どちらもエラー 0・警告 0。全体：357 ページ、エラー 0・警告 0
- `npx textlint docs/start/ai-and-sources.md`：0 件。`docs/start/how-to-use.md`：警告 4（144・197・237・417 行。どれも今回変えていない行で、policy-final の報告と同じ）。`docs/index.md`：警告 1（3 行。変えていない）
- `python3 tools/fix_code_links.py --check --stat --page ai-and-sources`・`--page how-to-use`：直すところ 0
- `python3 tools/gen_site.py --check`：生成物が古い 7 ファイル（docs/start/index.md・docs/lists/kind-guide.md・docs/llms.txt・docs/index/start.md・overrides/assets/data/graph.json・docs/guide/term-index.md・docs/start/how-to-use.md）。summary・aliases・sections・stage を変えたので想定どおり。メインが流す
- `uv run --frozen mkdocs build --strict -d <作業用フォルダ>/site`：成功・WARNING なし（作業ツリーの git status はビルドの前後で同じ）。ビルドした HTML で h2 の id 7 つ、「作者が確かめる」のコメント 0、方針のページの中のリンク（#ai-writing など 7 つの anchor、how-to-use の #stub・#report・#problems・#claude・#ai-rule-version、atcoder-system#ai-rules）がすべて解決することを確かめた。トップページ → start/ai-and-sources/、how-to-use → ../ai-and-sources/・#ai-writing・#contact もある
- `python3 tools/render_pages.py <作業用フォルダ>/site --page ai-and-sources --page how-to-use --page docs/index.md --width 360,390`：エラー 0。警告 2 は how-to-use#levels の表（幅 402px。変えていない節で #55 の範囲）

## メインへの補足（直しの必須ではない）

1. **開かないページの範囲**：方針のページ 103 行は CLAUDE.md に合わせて「AtCoder の問題ページと解説ページ（atcoder.jp とそのサブドメイン）」と書くが、手引き §2.6・付録 B の末尾・research/README.md §3 の 1・claude/project-instructions.md 3 は atcoder.jp（サブドメインを含む）全体を開かないとしている。誤りではない（狭い方の文は正しい）が、執筆と調査の実際に合わせて「atcoder.jp（サブドメインを含む）のページを開かない」と書く手もある。そうするなら、同じ段落の img.atcoder.jp の 1 文は「制作の始めに読んだ」形にする
2. **Scrapbox**：101 行の「Scrapbox」は 2024 年に Cosense へ名前が変わっている（ドメインは scrapbox.io のまま）。付録 B が scrapbox.io と書いているので今のままでも通じるが、「Scrapbox（Cosense）」としてもよい
3. **チェックリスト F9**：「よくある失敗」の「AtCoder の公式解説を参考に入れる」は、典型90 の出題者の GitHub の解説（方針のページ 90 行で公式の解説として参考に挙げてよいとしたもの）と紛れる。「atcoder.jp にある公式解説」と書くとよい
4. **docs/start/atcoder-system.md 34**：「atcoder.jp のページは開いていないので」は、decisions.md 25（2026-10-21 に問題・解説ページの meta、robots.txt・利用規約、言語の一覧を確かめた）と字面で食い違う。#2 の範囲外なので、#3 の軽微な修正に回すとよい（例「制作では atcoder.jp のページを開かないので」）
5. **policy-final の提案**：提案 3（ひな形の種類に出典の申し出を足す）、6（手引き §2.6・§10・§11・§15-6）、7（gen_site.py の STAGE_JA の draft を「下書き」に。docs/llms.txt 9 行にも「本文あり・未検証」が出ている）、8（start の説明）、9（how-to-use の related）は、どれも妥当と考える。1 で (b) を選ぶなら、提案 6 の §15-6 に写し・訳の扱いを足す
6. **policy-final の「メインに判断してほしい点」**：1（docs/ 以外をまとめて MIT）は対象に隙間がなく、方針のページの書き方とも合う。ただし planning/ の調査の記録などには他者の文の引用（USACO Guide の規約の 1 文など）があるので、LICENSE-docs の「対象でないもの」の 3 つ目を「ページやファイルに出る他者のもの（引用・名前・題名）」に広げるとより正確になる。2（robots.txt の 1 文）は check_noai.py の動きと decisions.md 25 に合う。3（copyright の絶対 URL）はビルドで確かめた
7. **この検証で行った git の操作**：メインのリポジトリで `git fetch -q origin` を 1 回流した（参考の行が指すファイルが origin/main にあるかを見るため。remote-tracking の参照が更新されるだけで、作業ツリーとブランチは変えていない）。指示の「git は読むだけ」から外れたので書いておく。結果：planning/batches/fix/README.md など参考の 8 ファイルは origin/main にあり、LICENSE・LICENSE-docs はまだない（マージで入る）

## 使った出典

- creativecommons.org：https://creativecommons.org/licenses/by/4.0/deed.ja と https://creativecommons.org/licenses/by/4.0/legalcode.ja（check_noai.py で 1 回ずつ、curl で 1 回ずつ。題名・h1・正式名・表示の条件を確かめた。文は写していない）
- GitHub の license API（`gh api licenses/mit`。MIT のひな形）
- PyPI（fonttools・brotli を作業用フォルダの一時的な環境に入れ、KaTeX の woff2 の name テーブルを読んだ）
- ほかはリポジトリの記録（CLAUDE.md、planning/decisions.md・progress.md・style-guide.md・checklists/fact.md・code.md・research/README.md・batches/fix/README.md・brief-*.md・b1〜b5 と s10 の報告、data/problems.yaml、tools/check_noai.py・check_pages.py・ap.py・gen_site.py・render_pages.py、overrides/main.html・assets/vendor/SOURCES.txt と各 LICENSE、third_party/ac-library/LICENSE、.github/、claude/project-instructions.md）と、Issue #1・#2 の本文・ラベルの一覧（読んだだけ）
- atcoder.jp・codeforces.com は開いていない。洛谷・ikatakos.com・web.archive.org も開いていない（1 は記録だけで確かめた）

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/policy-final/verify-policy-final（ビルド・写真・CC のページの写し・MIT のひな形・フォントを読むスクリプト）。リポジトリの site/ と docs/ には一時ファイルを作っていない。
