# policy-page の報告（グループ policy-draft・Issue #2）

担当：policy-page。作業ツリー：kyopro-atlas-wt/policy-draft（ブランチ docs/policy-draft）。2026-10-29。

## 結果の一言

Issue #2 の「やること」の 5 項目を、新しいページ `docs/start/ai-and-sources.md`（下書き。stage は draft）に書いた。トップページと「この教材の使い方」の目的と範囲の節に、1 行ずつリンクを足した。記録から確かめられない点は本文に `<!-- 作者が確かめる：… -->` を 9 か所残した（下の表）。公開（マージ）は作者の確認待ちなので、Issue としては一部（partial）である。

## 直したファイル

| ファイル | 行 | 内容 |
| --- | --- | --- |
| docs/start/ai-and-sources.md（新規、158 行） | 全体 | 方針のページ。id `ai-and-sources`、title「出典と AI 利用の方針」、type guide、field start、order 40、kind [案内]、level null、complexity null、stage draft、updated 2026-10-29。sections は ai-writing・no-copying・citations・noai・contact の 5 つ。末尾に定型の `## 参考 {#references}` |
| docs/index.md | 8 | info「制作中」の下（`## 入口` の前）に 1 行：「本文は AI（Claude）で書いている。書き方と確かめ方、出典の扱いは[出典と AI 利用の方針](start/ai-and-sources.md)にある。」gen:begin〜gen:end には触れていない |
| docs/start/how-to-use.md | 59、31 | 「この教材の目的と範囲」の節の末尾に 1 行：「本文は AI（Claude）で書いている。誰がどう書いて確かめたか、他者の記事をどう参考にしたかは[出典と AI 利用の方針](ai-and-sources.md)にある。」front matter の updated を 2026-10-29 に（stage は reviewed のまま） |

front matter は schema/page.schema.json と既存の start のページ（how-to-use・notation・atcoder-system）にそろえた。frequency は guide なので書いていない（ほかの start のページと同じ）。

## Issue の 5 項目と節の対応

| Issue の項目 | 節（anchor） | 書いたこと |
| --- | --- | --- |
| 本文は AI を使って執筆し、作者が確認していること | AI で書いていることと確かめ方（ai-writing）、要点の「今の段階」 | AI（Claude。手元の Claude Code）が本文・図・コード片・サイトの仕組みを作ったこと。作者が決めたこと（目的・読者・範囲と 3 つの約束、設計の確認）。確かめ方の 3 段（別の担当の 4 観点の検証、機械の検査、2 巡の全体の検証）。段階 4 つの意味。2026-10-29 の時点で、このページのほかの 353 ページはすべて「検証済み」で「完成」はまだないこと。作者がすべてを確かめたものではないこと |
| 他者の記事は参考にしているが、文章・図・コードは転載していないこと | 他者の記事を転載しない（no-copying） | 文章・図・コード・問題文ごとの扱い。条件のある資料（USACO Guide・cp-algorithms と OI Wiki・問題文を引用している解説）の使い方。同梱しているソフトウェア（ACL・KaTeX・Cytoscape.js・cytoscape-dagre）とそのライセンス |
| 参考にした資料は各ページの「参考」欄に記載していること | 参考にした資料の示し方（citations） | 参考の 1 行の形、例題・練習の解説も入れること、ACL の document_ja、学ぶための資料の節、用語集と用語の索引を除く全ページにあること、問題の裏付けの URL は台帳に残すこと、atcoder.jp・codeforces.com の URL と公式の解説は入れないこと |
| AI の利用を断る指定（noai など）があるサイトは資料にしていないこと | AI の利用を断るサイトを資料にしない（noai） | 確かめる 2 か所（robots の meta タグと X-Robots-Tag）と check_noai.py、規約で断るサイト、書き手ごとに違うサービス、付録 B の記録。AtCoder・Codeforces の指定と、題名・difficulty・問いの確かめ方。claude.ai の解説でも開かせないこと |
| 掲載内容に問題があれば連絡してほしいこと（Issue の案内）と、連絡を受けたときの対応 | 掲載内容についての連絡と対応（contact） | 受け口は https://github.com/yuukougun/kyopro-atlas/issues 。連絡してほしい場合 4 つ、書いてほしいこと、アカウントが要ること。対応の手順 5 つ（下書き。作者が確かめる） |

## 事実と、確かめた記録

| 本文の記述 | 確かめた記録 |
| --- | --- |
| 制作は手元の Claude（Claude Code）で、執筆の担当を立てて並行して書いた | requirements.md §2（ローカルの Claude CLI）、progress.md 8b（ページごとの執筆 → 検証 → 直し、並列） |
| 図・コード片・サイトの仕組みも AI が作った | progress.md 工程6（S1〜S5 の担当）・8b・viz |
| 作者が目的・読者・範囲と約束を決めた | requirements.md §1・§3・§8 の注意点、decisions.md 2026-10-21（AtCoder を AI で読まない） |
| 設計は AI の案を作者が確かめてから進めた | progress.md 工程5（ユーザーの承認）、design.md §10.1 |
| 別の担当が 4 観点（事実・コード・図・分かりやすさ）で検証、書いた担当に検証させない | progress.md 8b、design.md §10.2、planning/checklists/（fact・code・figure・clarity） |
| 機械の検査（台帳と照らす・GCC 15.2 でコンパイル・実行・textlint）、push のたびに GitHub Actions | design.md §8.6、.github/workflows/check.yml（push と pull_request、gcc:15.2.0 のコンテナ） |
| 全体の検証 2 巡（1 巡目 5 観点の洗い出しと直し、2 巡目は残り）、別の担当の検証、全ページを検証済みに | progress.md 工程10 |
| 段階 4 つの名前 | tools/gen_site.py の STAGE_JA（準備中・本文あり・未検証・検証済み・完成） |
| 完成は作者が目を通してよいとしたページ | progress.md「次にやること」5、README.md |
| 2026-10-29 の時点で 353 ページが reviewed、done は 0 | `grep '^stage:'` で数えた（作業ツリーとメインのどちらも reviewed 353） |
| 段階は今は「準備中」のときだけ帯で出る | overrides/main.html 102〜105 行、Issue #9 の背景 |
| 文章の近さを検証役が並べて読んで確かめる（例の数値・図の形を含む） | planning/checklists/fact.md F8 |
| 図はこの教材の SVG・Mermaid・動く図だけで、ほかのサイトの画像はない | docs の外部画像のリンク 0 件、docs/img の 414 枚はすべて SVG、Mermaid 10 か所、動く図の div 28 か所（数えた） |
| 問題文と入出力例を載せない、コード片の入力に入出力例を使わない | requirements.md §6、style-guide §2.5・§9、checklists/code.md C2 |
| USACO Guide の規約（書面の許可のない使用・複製・再配布の禁止）と構成の参考だけ | research/00-curriculum.md の冒頭と §7.5、design.md §6.7、style-guide §11。規約の文は usaco.guide/general/using-this-guide を WebFetch で確かめた（h1 は「Using This Guide」、本文に "No part of this site may be used, reproduced, redistributed, commercialized, or sold without prior written permission."） |
| cp-algorithms・OI Wiki は文章と図を使わない。考え方や計算量の確認と、学ぶための資料 | style-guide §11、docs の参考の行（cp-algorithms 31 か所・OI Wiki 23 か所の「文章と図は使っていない」「学ぶための資料」） |
| 問題文を引用した解説は問題文の部分を読まない | research/00 §7.5、style-guide §11・§15-6 |
| 同梱のソフトウェアとライセンス | third_party/ac-library/LICENSE（CC0）、overrides/assets/vendor/SOURCES.txt と各 LICENSE（MIT） |
| 参考の 1 行の形、例題の解説も入れる、ACL は document_ja、atcoder.jp・codeforces.com の URL を入れない | style-guide §11、§16-1（学ぶための資料） |
| 参考の節は用語集と用語の索引を除く全ページにある | 数えた（353 ページ中 351。ないのは guide/glossary と guide/term-index） |
| 問題の裏付けの URL は台帳に問題ごとにある、未確認は載せない | data/problems.yaml の evidence・status、design.md §5.4・§11 |
| 参考に atcoder.jp・codeforces.com の URL も公式の解説もない | 数えた（参考の節に atcoder.jp・codeforces.com の URL 0 件、editorial へのリンク 0 件。atcoder.jp へのリンクはすべて /tasks/ の問題リンク） |
| noai を確かめる 2 か所（robots の meta・クローラの名前の meta、X-Robots-Tag） | tools/check_noai.py |
| 書き手ごとに確かめるサービス、付録 B に日付つきで記録 | style-guide 付録 B |
| 資料にしたドメインはすべて付録 B にある | docs の参考などのリンクのホスト 112 個を付録 B と照らした（atcoder.jp の問題リンクを除いて、すべて付録 B にある。trap.jp は付録 B では記事の確認が未了だった → 下の「確かめたこと」） |
| AtCoder の問題・解説ページと Codeforces の noai・noimageai | decisions.md 2026-10-21 |
| claude.ai の解説でも 2 つのサイトを開かせない | claude/project-instructions.md の 3 |
| 直した内容は commit の履歴に残り、誰でも見られる | decisions.md（リポジトリは public） |

## 本文に残した「作者が確かめる」（9 か所）

| 行 | 内容 |
| --- | --- |
| 26 | ページ全体が下書きであること。公開する前にコメントをすべて確かめて消す |
| 33 | 公開する日に「完成」のページの数を確かめ、要点の「今の段階」と ai-writing の節の数字を直す |
| 51 | 3 つの約束を「作者が決めた」と書いてよいか（1・2 は requirements.md、3 は作者の決定として記録にあるのは AtCoder だけで、ほかのサイトへの広げ方は CLAUDE.md と調査の手引き §3 の 8） |
| 70 | #9 で段階と更新日を表示したら、表示の場所を書き足し、段階の一覧を how-to-use へのリンクに替えるか |
| 83 | 「他者のコードを写さない」は手引きに明記がない（文章は §2.6・§11、例と図の形は F8）。コードの行を方針として書いてよいか |
| 91 | USACO Guide の規約は「使用（used）」も禁じている。構成の参考にしたことをこのまま書いてよいか |
| 119 | robots.txt の AI 向けのクローラの拒否を「断る指定」に含めるか（今は check_noai.py の --robots で表示するだけで、判定に入れていない） |
| 136 | GitHub のアカウントがない人や、公開の Issue に書きにくい連絡の受け口を用意するか（#10 とそろえる） |
| 148 | 対応の手順は記録にない下書き。返事と直しの目安の期限、急ぐ申し出のときにページを先に取り下げるか、Issue を閉じる時期 |

## 流した検査

- `python3 tools/check_pages.py -v --page ai-and-sources --page how-to-use --page docs/index.md`：エラー 0・警告 0。全ページ（`python3 tools/check_pages.py`）もエラー 0・警告 0（354 ページ、draft 1・reviewed 353）
- `npx textlint docs/start/ai-and-sources.md docs/start/how-to-use.md docs/index.md`：エラー 0。新しいページは警告 0。how-to-use の警告 4 件（138・191・219・359 行）と index.md の警告 1 件（3 行）は、元からあるもの（HEAD の版で同じ 4 件・1 件が出ることを確かめた。行は 2 行ずれる）
- `python3 tools/gen_site.py --check`：生成物が古い 9 ファイル（nav.yml、docs/start/index.md、docs/lists/index.md、docs/lists/kind-guide.md、docs/llms.txt、docs/index/start.md、overrides/assets/data/graph.json、docs/guide/term-index.md、docs/start/how-to-use.md の生成ブロック）。新しいページを足したので想定どおり。生成はメインに任せる
- `uv run --frozen mkdocs build -q -d <作業用フォルダ>/site`：成功（strict ではない。nav に載っていないので strict だと omitted_files の警告になる）。HTML で、要点の囲み・見出しの id 6 つ・相対リンク（how-to-use の #claude・#stub・#problems・#ai-rule-version）を確かめ、コメントが表示されないことを確かめた。ヘッドレスの Chrome で幅 1000px と 400px を撮って目で確かめた（崩れなし。meta タグのインラインコードも 400px で折り返す）
- `python3 tools/check_noai.py https://trap.jp/post/1224/ https://trap.jp/post/2589/ https://trap.jp/post/2861/`：3 本とも HTTP 200 で取得でき、robots の meta と X-Robots-Tag に noai・noimageai がない（2026-10-29）。progress.md の残りの件の情報としてメインに渡す（下の提案 4）

途中で、how-to-use.md と index.md の元の版の textlint の警告を比べるため、作業ツリーの docs/ に一時ファイル 2 つ（docs/start/.orig-how-to-use.tmp.md・docs/.orig-index.tmp.md）を作り、検査の直後に消した。git status に残っていないことを確かめた。

## 提案（共有のファイル。メインが反映する）

1. **tools/gen_site.py の分野の説明**（57 行）：start の説明「この教材の使い方、記法と用語の約束、AtCoder の仕組み」に「出典と AI 利用の方針」を足す。docs/start/index.md と how-to-use の fields の表（はじめに 3 → 4 ページ）に出る。design.md §2.1 の表も同じ文
2. **gen_site.py の実行**：nav・一覧・llms.txt・用語の索引・graph.json・index/start.md・how-to-use の生成ブロックを作り直す（draft の pull request で見せるなら、nav に出るよう生成してから見せる）
3. **手引き §2.6・§11 とチェックリスト**：作者がコードの行（本文 83 行のコメント）を方針として認めたら、style-guide §2.6 に「他者のコードを写さない」を足し、checklists/fact.md の F8 か code.md に「コード片が資料のコードに近すぎないか」の確かめ方を足す
4. **付録 B と progress.md**：trap.jp の記事 3 本（post/1224・2589・2861。cpp-environment・cpp-macros-template-file・static-top-tree の参考）を 2026-10-29 に check_noai.py で確かめ、HTTP 200 で noai・noimageai がなかったことを付録 B に記録し、progress.md の「残り」から外す
5. **how-to-use の related**：`ai-and-sources` を足す（front matter。今回は頼まれた updated だけを変えた）
6. **今の段階の自動化（任意）**：gen_site の `stage-summary` ブロック（制作状況の表）を方針のページに置くと、「完成」の数が自動で合う。ただし今の表は 6 列で手引き §8 の「列は 4〜5 まで」を超えるので、合計だけの短い形を足すなどが要る
7. **#10 との関係**：#10 で各ページの「誤りを報告する」リンクと Issue のテンプレートを作るときに、方針のページの #contact と案内をそろえる。#9 で段階を表示したら、方針のページの段階の説明を how-to-use#stub へのリンクにするか決める
8. **docs/index.md の重なり**：#4（info「制作中」の文の直し）と #7（入口）も docs/index.md を直す。足した 1 行の置き場所は、マージのときに合わせて見直す

## メインに判断してほしい点

1. 連絡を受けたときの対応の具体（返事と直しの目安の期限、急ぐ申し出のときに先に取り下げるか、Issue を閉じる時期）。本文は下書きの手順だけを書いた
2. GitHub のアカウントがない人や、公開の Issue に書きにくい連絡の受け口を用意するか（#10 の「報告の受け口」と合わせて決める）
3. robots.txt での AI 向けのクローラの拒否を「AI の利用を断る指定」に含めるか（今の判定は meta と X-Robots-Tag と規約だけ）
4. 「他者のコードを写さない」を方針として書いてよいか（記録には文章と例・図の形の決まりしかない）
5. USACO Guide の規約は「使用」も書面の許可なしには禁じている。構成の参考にしたことの書き方（このページと how-to-use の参考）
6. 3 つの約束をすべて「作者が決めた」と書いてよいか（noai の決定として記録にあるのは AtCoder だけ）
7. 公開のページから planning/・tools/・data/ のファイル（GitHub の blob の URL）へリンクしてよいか。参考の 6 行と本文の 3 か所がそうである
8. 教材そのもののライセンス（リポジトリに LICENSE がない）を、このページか別の場所で示すか。Issue #2 の範囲の外なので書いていない
9. 新しいページの stage は draft にした。検証の後で reviewed にするか、作者が確かめた時点で done にするかはメインが決める
10. AtCoder Problems のデータ（tools/ap.py が kenkoooo.com/atcoder/resources/ から取る JSON）は付録 B にない。記事ではなくデータなので扱いを決めておくとよい（本文では「AtCoder Problems の公開データ」とだけ書き、リンクはしていない）

## 使った出典

- usaco.guide/general/using-this-guide（付録 B にあるドメイン。WebFetch で 1 回。題名と規約の文を確かめた）
- trap.jp の記事 3 本（check_noai.py で 1 回ずつ。資料としては読んでいない）
- ほかはすべてリポジトリの記録（README.md、CLAUDE.md、planning/requirements.md・decisions.md・progress.md・design.md・style-guide.md・checklists/・research/README.md・research/00-curriculum.md、tools/check_noai.py・gen_site.py・ap.py、data/problems.yaml、overrides/main.html・assets/vendor/SOURCES.txt、third_party/ac-library/LICENSE、.github/workflows/）と、Issue #2・#3・#7・#9・#10 の本文（読んだだけ）

## 使用量の目安

道具の呼び出し約 75 回、Web 取得 1 回（WebFetch）、check_noai による取得 3 回、サイトのビルド 2 回（各 16 秒ほど）、所要時間は 1 時間ほど。

## 検証の指摘への対応（2026-10-29、fixup-policy-page）

verify-policy-page の指摘 4 件（必須 2・軽微 2）をすべて直した。直したのは docs/start/ai-and-sources.md だけで、docs/index.md と docs/start/how-to-use.md には触れていない。front matter は変えていない（stage は draft、updated は 2026-10-29 のまま）。行は直した後の番号である。

### 直したこと

| 指摘 | 行 | 直した内容 |
| --- | --- | --- |
| 1【必須】atcoder.jp・codeforces.com を「開かず、資料にもしていない」 | 123・125・127・108 | 123：「制作の始め（2026-10-21）にこれらの指定を確かめてからは、…AI で開いていない」と時点を限った。125：例外の段落を足した（AtCoder のコンパイラとオプションの記述は AtCoder の公式の言語の一覧による。一覧は img.atcoder.jp にあり、制作の始めに noai がないことを確かめて読んだ。[AtCoder と手元の C++ 環境の参考](../cpp/cpp-environment.md#references) へのリンク）。127：「作者が確かめる」のコメント（下）。108：「参考には、atcoder.jp と codeforces.com の URL を入れない」に直し、例外は #noai で述べると書いた |
| 2【必須】「公式の解説も参考にしていない」「第三者の解説で確かめた」 | 104・106・108・123 | 104：「解説で確かめた。使った解説の多くは、第三者の書いたものである。典型90問・鉄則本・アルゴリズムと数学・ACL Practice では、出題者が GitHub に公開している解説や解答例も使い、それだけで確かめた問題もある」。108：「atcoder.jp にある AtCoder の公式の解説も、資料にしていない。ただし、出題者が GitHub に公開している解説や解答例（上の問題集のもの）は資料にし、参考にも挙げている。典型90問では、この出題者の解説が公式の解説にあたる」。123：「問いと解き方は第三者や出題者が公開している解説や解答例で確かめた（#citations へのリンク）」。106：「作者が確かめる」のコメント（下） |
| 3【軽微】OI Wiki の SATA | 88 | 「ライセンスは、cp-algorithms が CC BY-SA 4.0、OI Wiki が CC BY-SA 4.0 と SATA である」（research/00-curriculum.md 12・136 の記録どおり） |
| 4【軽微】「すべてのページにある」 | 102 | 「参考の節は、各分野のページのうち、用語集と用語の索引を除くすべてにある。トップページと、自動で作るページ（分野の入口・一覧・詳細索引）にはない」 |

### 指摘の案から変えた点と理由

- **「atcoder.jp の解説ページは開いていない」→「資料にしていない」**：decisions.md 25 では、決まりを作る前に解説ページの meta を確かめている（開いている）。「開いていない」は #noai の段落で時点を限って書いた
- **「作者」→「出題者」**：このページの「作者」は教材の作者を指す（「作者が決めた」「作者が目を通した」）ので、問題の作者は「出題者」にした
- **「GitHub や Qiita」→「GitHub」**：台帳で、典型90問・鉄則本・アルゴリズムと数学の evidence にある出題者（E869120 氏）の資料は、すべて github.com と raw.githubusercontent.com にある。qiita.com/e869120 の記事は ABC・ARC の 9 問（abc007_3 など）の evidence にあるだけで、出題者の資料ではない
- **「アルゴ数学」→「アルゴリズムと数学」**：guide/problem-sets の呼び方（別名）にそろえた
- **ACL Practice を足した**：台帳で practice2_d・e・g・h の evidence は、ACL のリポジトリの使用例（github.com/atcoder/ac-library の test/example/*_practice.cpp。AtCoder 自身の解答のプログラム）だけである。参考でも max-flow・min-cost-flow・scc・two-sat が挙げている。指摘と同じ種類の食い違いなので、同じ文で直した
- **「（公式の解説）」**：「典型90問では、この出題者の解説が公式の解説にあたる」と書いた。リポジトリの README（raw.githubusercontent.com で 1 回読んだ）で、出題者の企画の問題解説を置くリポジトリだと確かめた。AtCoder の側で公式とされているかは、atcoder.jp を開かないので確かめていない（degree-sqrt 185・240 の「公式の解説」の呼び方にそろえた。下の判断 3）
- **例外を「1 つ」と数えなかった**：20261014 版のルールの中身をどこで読んだかが記録にない。atcoder.jp で読んでいれば例外が増えるので、「例外として」とだけ書いた

### 足した「作者が確かめる」（2 か所。全部で 11 か所）

| 行 | 内容 |
| --- | --- |
| 106 | 出題者の資料は、解説と解答例のほかに問題文も使っている。台帳の typical90_bc・bg・bk・bt の evidence に出題者のリポジトリの問題文（problem/・problem-txt/）があり、参考でも complexity-estimation 239・242（055・072 の問題の画像で制約）と hash-safety 316（047 の「問題文も参照」）が挙げる。104 行の文と 89 行（問題文を載せている解説）に書き足すかを、手引き §15-6 に出題者のリポジトリが入るかと合わせて決める（verify の「メインへの補足 1」と同じ件） |
| 127 | 例外の記録（decisions.md の 2026-10-21「質問の前に確認した事実」で、決まりの前に問題・解説ページの meta、robots.txt と利用規約、言語の一覧を確かめたこと。Codeforces は調査 00 が codeforces.com/edu/courses で確かめたこと）と、記録にない 2 点。(1) decisions.md の GCC 版のオプションの一覧を言語の一覧から読んだか（b5 の cpp-environment の担当が確かめられず、提案に回した点。決着の記録がない）。(2) 20261014 版のルールの中身をどこで読んだか |

### 確かめたこと

- 台帳 data/problems.yaml を数え直した：ページに載る典型90問 67 問中 55・鉄則本 11 問中 10・アルゴリズムと数学 4 問中 4 の evidence に出題者の資料があり、出題者のものだけは 35・10・3（計 48）。検証の数と一致する。ACL Practice は 12 問中 4 問が ACL の使用例だけ
- docs のリンク：github.com/E869120 へリンクするファイルは 66（典型90 のリポジトリ 54・kyopro-tessoku 10・math-algorithm-book 6。重なりあり）。atcoder.jp へのリンクは /tasks/ の問題リンクだけで、codeforces.com・slideshare へのリンクは 0。evidence のホストにも atcoder.jp・codeforces.com はない
- 参考の節：stage を持つ 354 ページ中 352 にある（ないのは glossary・term-index）。stage のない 67 ファイル（docs/lists 35・docs/index 15・index.md 17〈トップページと分野の入口〉）にはない
- 「制作の始め（2026-10-21）」：progress.md の工程 1（質問）が 2026-10-21。決まりの後に atcoder.jp・codeforces.com を開いた記録はない（b1 などの検証の報告、b5 の reverse-index-constraints・contest-strategy は「開いていない」と書く）
- 出典の扱いは手引き §2.6・§11・§14-17（典型90 の jpg は同じリポジトリの解答コードで確かめてよい）と付録 B に照らした

### 検査（書き換えない検査）

- `python3 tools/check_pages.py -v --page ai-and-sources --page how-to-use --page docs/index.md`：エラー 0・警告 0。全ページもエラー 0・警告 0（354 ページ、draft 1・reviewed 353）
- `npx textlint docs/start/ai-and-sources.md docs/start/how-to-use.md docs/index.md`：エラー 0。新しいページは警告 0。警告 5（how-to-use 138・191・219・359、index 3）は元からあるもので、変更していない行
- `python3 tools/gen_site.py --check`：生成物が古い 9 ファイル（前と同じ。新しいページの分で、メインが gen_site を流す）
- `uv run --frozen mkdocs build -q -d <作業用フォルダ>/site`：成功。HTML で、新しいリンク（../../cpp/cpp-environment/#references・#citations・#noai）が解決し、節の id 6 つがあり、コメントが表示されないことを確かめた

### 提案（共有のファイル。メインが反映する）

1. **how-to-use.md 243**：「問いと解き方を第三者の解説で確かめている」を、このページの 104 行にそろえる（例：「第三者の解説か、出題者が公開している解説や解答例で確かめている」）
2. **手引き §11 と §10**：§11 の「cp-algorithms・OI Wiki（CC BY-SA）」を「cp-algorithms（CC BY-SA 4.0）・OI Wiki（CC BY-SA 4.0 と SATA）」にする。§10 の「問いと解き方は第三者の解説で裏付け」に、出題者の資料（典型90 などの GitHub の解説・解答コード、ACL の使用例）を使ってよいことを足す（§14-17 の運用に合わせる）
3. **付録 B**：img.atcoder.jp を「言語の一覧だけ。2026-10-21 に noai がないことを確かめた」と記録する。このページの 117 行の「確かめたドメインは付録 B に記録している」と合う
4. **atcoder-system.md 34**：20261014 版のルールを atcoder.jp で読んでいたと分かったら、「atcoder.jp のページは開いていない」も同じように時点を限る

### メインに判断してほしい点

1. 例外の書き方（127 行のコメント）：decisions.md のオプションの一覧を言語の一覧から読んだか、20261014 版のルールの中身をどこで読んだか。分かれば、例外の段落を確定する
2. 出題者のリポジトリの問題文（106 行のコメント）：手引き §15-6 の「問題文を読まない」に入るか。入らないなら 104 行か 89 行に「典型90問は出題者の問題文で制約を確かめたページがある」と書き、入るなら complexity-estimation と hash-safety の参考を見直す
3. 典型90問の GitHub の解説を「公式の解説にあたる」と書いてよいか（README と degree-sqrt の呼び方による。atcoder.jp では確かめていない）

### 使った出典

- https://raw.githubusercontent.com/E869120/kyopro_educational_90/main/README.md（付録 B のドメイン。1 回。リポジトリの中身の説明だけを読み、問題文のファイルは開いていない）
- ほかはリポジトリの記録（planning/decisions.md・progress.md・style-guide.md・research/00-curriculum.md・batches/b5/、data/problems.yaml、docs の各ページ）と Issue #2 の本文（読んだだけ）
