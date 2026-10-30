---
id: ai-and-sources
title: 出典と AI 利用の方針
aliases: [AI の利用, 生成 AI, 出典, 参考文献, 転載, noai, 著作権, ライセンス, 問い合わせ, 連絡先]
type: guide
field: start
order: 40
level: null
kind: [案内]
prerequisites: []
related: [how-to-use#stub, how-to-use#report, how-to-use#problems, how-to-use#claude, how-to-use#ai-rule-version, atcoder-system#ai-rules]
summary: この教材の本文を AI（Claude）が書き、別の AI の担当と機械の検査で確かめている流れと、段階「完成」の意味がわかる。他者の記事を転載しない約束、出典の示し方、AI の利用を断るサイトの扱い、ライセンス、連絡先も示す。
complexity: null
signs: []
acl: []
sections:
  - {title: AI で書いていることと確かめ方, anchor: ai-writing}
  - {title: 他者の記事を転載しない, anchor: no-copying}
  - {title: 参考にした資料の示し方, anchor: citations}
  - {title: AI の利用を断るサイトを資料にしない, anchor: noai}
  - {title: 教材のライセンス, anchor: license}
  - {title: 掲載内容についての連絡と対応, anchor: contact}
stage: reviewed
updated: 2026-10-30
---

!!! abstract "要点"
    - **何のページか**：この教材の本文を AI（Claude）が書き、別の AI の担当と機械の検査で確かめている流れと、段階「完成」の意味がわかる。他者の記事を転載しない約束、出典の示し方、AI の利用を断るサイトの扱い、ライセンス、連絡先も示す。
    - **使い方**：教材の文章がどう書かれて確かめられたか、他者の記事をどう参考にしたかを知りたいときに引く。教材の文章・図・コードを使いたいときは[教材のライセンス](#license)を、掲載内容に問題を見つけたときは[掲載内容についての連絡と対応](#contact)を読む。
    - **作者の役割**：作者は目的・読者・範囲と制作の約束を決め、設計を確かめ、公開してよいかを判断している。すべての記述を作者が確かめたわけではない。

<!-- textlint-disable -->
別名：AI の利用・生成 AI・出典・参考文献・転載・noai・著作権・ライセンス・問い合わせ・連絡先
<!-- textlint-enable -->

出典と AI 利用の方針は、この教材を誰がどのように書いて確かめ、何を資料にし、資料をどう示しているかの説明である。教材を使うときのライセンスと、参考にされた記事の著者や読者が問題に気づいたときの連絡先も示す。読者が claude.ai に解説を頼むときの約束は、[claude.ai での解説の頼み方](how-to-use.md#claude)にある。

## AI で書いていることと確かめ方 {#ai-writing}

この教材の本文は、作者の指示のもとで AI（Anthropic の Claude）が書いている。制作には手元で動かす Claude Code を使い、ページを分けて執筆の担当を立て、並行して書かせた。図・コード片と、索引や一覧を作るサイトの仕組みも、同じように AI が作った。

作者は、教材の目的・読者・範囲と、次の制作の約束を決めた。

- 事実（問題番号・計算量・定理など）は、確かめてから書く。
- 他者の文章を転載せず、参考にした資料を出典として残す。
- AI の利用を断る指定のあるサイトを資料にしない。

ページの分け方・レベル・構成などの設計は、AI がまとめた案を作者が確かめてから進めた。

書いたページは、次の 4 段で確かめている。

1. **別の担当による検証**：書いた担当とは別の AI の担当が、事実・コード・図・分かりやすさの 4 つの観点で読み、指摘を直した。書いた担当には、自分のページを検証させない。
2. **機械の検査**：問題の番号・題名・difficulty を、AtCoder Problems の公開データから作った問題の台帳と照らす。コード片は完全なプログラムにして GCC 15.2 でコンパイル・実行し、期待どおりに動くかを確かめる。表記は textlint で検査する。これらの検査は、変更を push するたびに GitHub Actions でも動く。すべてのコード片のコンパイルと外部のリンクの確認は、週に 1 回動く。
3. **全体の検証**：全ページを書き終えた後（2026-10-22）、全体の検証を 2 巡行った。1 巡目は構成・ページどうしの関係・事実・図・共有のファイルの 5 つの観点で全ページの問題点を洗い出して直し、2 巡目は残った点を直した。どちらも直した結果を別の担当が検証し、その時点の全ページの段階を「検証済み」にした。
4. **Issue の対応**：その後に見つけた点と、読者から寄せられた要望を GitHub の Issue にまとめて直す。直した結果は、別の担当が検証する。

各ページの最後の行には、ページの段階と更新日が出る。本文を書いたページの段階は、次のように進む（準備中を含む 4 つの段階の一覧は[ページの段階と「準備中」の帯](how-to-use.md#stub)）。

- **下書き**：AI の担当が書き、まだ検証していない。
- **検証済み**：別の担当が検証し、指摘を直した。
- **完成**：執筆・別の担当の検証・Issue の対応を一通り終え、作者が公開してよいとした。作者がすべての記述を確かめたわけではない。

「完成」のページも、本文は AI が書き、AI の担当と機械の検査で確かめたものである。検証をすり抜けた誤りが残ることもある。誤りに気づいたら、[掲載内容についての連絡と対応](#contact)の方法で知らせてほしい。

## 他者の記事を転載しない {#no-copying}

この教材は、競技プログラミングの解説記事やライブラリの文書などを参考にして書いている。他者の文章・図・コードは転載しない。資料は内容を理解し、事実を確かめるために読み、この教材の言葉・図・コードで書き直す。

- **文章**：自分の言葉で書く。検証の担当は、参考にした資料と本文を並べて読み、文の並び・言い回し・例（数値や図の形）がそのままになっていないかを確かめる。
- **図**：この教材のために作った SVG の図・Mermaid の図・動く図（ステップ送りの図）だけを載せている。ほかのサイトの画像は載せていない。
- **コード**：本文のコード片は、この教材のために書いた完全なプログラム（リポジトリの [`snippets/`](https://github.com/yuukougun/kyopro-atlas/tree/main/snippets)）から取り込んでいる。資料のコードは写さない。
- **問題文**：AtCoder の問題文と入出力例は載せない。問題は、リンクと、問いだけを自分の言葉にした要約で示す（[問題の表示](how-to-use.md#problems)）。コード片を確かめる入力にも、問題の入出力例は使わない。

ライセンスや規約で使い方に条件のある資料は、条件に合わせて使い方を狭めている。

- **CC BY-SA の資料**：cp-algorithms（CC BY-SA 4.0）と OI Wiki（CC BY-SA 4.0 と SATA）は、文章と図を使わず、考え方や計算量を確かめるために読んだ。さらに学ぶための資料として挙げることもある。
- **問題文を引用している解説**：第三者の解説やコンテストの記録のうち、問題文（英訳を含む）を引用して載せているものは、問題文の部分を読まず、解法の部分だけを参照する。

## 参考にした資料の示し方 {#citations}

各ページの末尾には「参考」の節があり、そのページで参考にした資料を 1 行に 1 件ずつ並べている。1 行には、著者・題名・URL と、その資料のどこを参考にしたかを書く。

- 例題・練習問題の方針を確かめるために読んだ解説も、参考に入れる。
- ACL の使い方は、GitHub にある ACL の公式の文書（document_ja）を参考に挙げる。
- 発展の概要のページでは、さらに学ぶための資料を「学ぶための資料」の節にも並べる。
- 参考の節は、トップページ・分野の入口・用語集・索引・一覧・勉強したいリストを除くページにある。

問題（例題・練習・力試し）について、何を問い、どう解けるかは、解説で確かめた。使った解説の多くは、第三者の書いたものである。典型90問・鉄則本・アルゴリズムと数学・ACL Practice では、出題者が GitHub に公開している資料（解説・解答例。典型90問では問題文も）も参考にし、それだけで確かめた問題もある。確かめた資料の URL は、リポジトリの[問題の台帳](https://github.com/yuukougun/kyopro-atlas/blob/main/data/problems.yaml)に、問題ごとの記録として残している。裏付けの取れない問題は載せない。

参考には、atcoder.jp と codeforces.com の URL を入れない（[AI の利用を断るサイトを資料にしない](#noai)）。atcoder.jp にある AtCoder の解説ページも、資料にしていない。典型90問では、出題者が GitHub に公開している解説が公式の解説にあたり、参考にも挙げている。問題の行のリンクは atcoder.jp の問題ページを指すが、これは読者が問題を開くためのものである。

## AI の利用を断るサイトを資料にしない {#noai}

Web のサイトには、AI による利用を断る指定を置いているものがある。この教材は、そうしたサイトを資料にしない。

資料にするドメインは、使う前に、次の 2 か所に noai・noimageai の指定がないことを確かめる。確かめるプログラムは、リポジトリの [tools/check_noai.py](https://github.com/yuukougun/kyopro-atlas/blob/main/tools/check_noai.py) である。

- ページの HTML にある robots の meta タグ（`<meta name="robots" content="noai">` の形。クローラの名前を指定したものも含む）
- HTTP の応答の X-Robots-Tag ヘッダー

利用規約などで AI の利用を断っていると分かったサイトも、資料にしない。はてなブログ・Scrapbox・note のように書き手ごとに設定や条件の違うサービスは、書き手・プロジェクト・記事ごとに確かめる。確かめたドメインは、確かめた日とともに[執筆の手引き](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/style-guide.md)の付録 B に記録している。

AtCoder の問題ページと解説ページには noai と noimageai の指定があり、Codeforces のページにも同じ指定がある。どちらも制作の始め（2026-10-21）に確かめた。そのため、制作では AtCoder の問題ページと解説ページ（atcoder.jp とそのサブドメイン）と、codeforces.com のページを AI で開かない。問題の題名と difficulty は AtCoder Problems の公開データで確かめ、問いと解き方は第三者や出題者が公開している解説などで確かめる（[参考にした資料の示し方](#citations)）。AtCoder の言語の一覧（img.atcoder.jp の静的ファイル）には noai の指定がないことも、同じ日に確かめた。

読者が claude.ai に解説を頼むときも、Claude にこの 2 つのサイトを開かせない約束にしている（[claude.ai での解説の頼み方](how-to-use.md#claude)）。開催中のコンテストの問題に使わない約束は、[AtCoder生成AI対策ルールの版](how-to-use.md#ai-rule-version)にある。

## 教材のライセンス {#license}

この教材の本文・図・コードは、条件を守れば誰でも使えるライセンスで公開している。

- **本文と図**：[CC BY 4.0](https://creativecommons.org/licenses/by/4.0/deed.ja)（クリエイティブ・コモンズ 表示 4.0 国際）である。下の段落の表示をすれば、複製・再配布・改変ができ、営利の目的にも使える。
- **コード**：MIT ライセンスである。ページに載るコード片と、その元の完全なプログラム、サイトを作るプログラム（索引や一覧を作るスクリプト・テンプレート・動く図の JavaScript など）が対象である。
- **同梱している外部のもの**：それぞれのライセンスに従う。コード片が呼び出す AtCoder Library（ACL）は CC0 である。サイトの表示に使う KaTeX・Cytoscape.js・cytoscape-dagre は MIT ライセンスで、KaTeX のフォントは SIL Open Font License 1.1 である。ライセンスの文書はリポジトリの同じディレクトリに置いている（KaTeX のフォントは、フォントのファイルの中にライセンスの表示がある）。

本文や図を使うときは、出典として kyopro-atlas（作者 yuukougun）とページの題名・URL を示し、CC BY 4.0 へのリンクを添え、手を加えたときはその旨を書く。ライセンスの文書は、リポジトリの [LICENSE-docs](https://github.com/yuukougun/kyopro-atlas/blob/main/LICENSE-docs)（本文と図。法的な全文は[リーガル・コード](https://creativecommons.org/licenses/by/4.0/legalcode.ja)）と [LICENSE](https://github.com/yuukougun/kyopro-atlas/blob/main/LICENSE)（コード）にある。どのファイルがどちらにあたるかは、LICENSE-docs と [README](https://github.com/yuukougun/kyopro-atlas/blob/main/README.md) のライセンスの節に書いてある。問題の題名や参考に挙げた資料の題名など、ページに出る他者のものは、このライセンスの対象ではない。

## 掲載内容についての連絡と対応 {#contact}

掲載内容に問題があれば、GitHub の [kyopro-atlas の Issue](https://github.com/yuukougun/kyopro-atlas/issues) で知らせてほしい。連絡の受け口は GitHub の Issue だけで、Issue を立てるには GitHub のアカウントが要る。各ページの最後の行の「このページの誤りを報告する」から開くと、ページの題名・URL・更新日が入った画面になる（[誤りの報告](how-to-use.md#report)）。

たとえば次のような場合である。

- 自分の記事の文章・図・コードが、この教材に写されている、または近すぎると感じたとき
- 参考の行の著者・題名・URL が違うとき、または自分の記事を参考に挙げないでほしいとき
- AI の利用を断っているサイトが資料になっているとき
- 事実の誤り（計算量・定理・問題の内容など）や、分かりにくいところに気づいたとき

知らせるときは、ページの URL（節が分かれば節の名前も）と、何が問題か、どうしてほしいかを書いてほしい。参考にされた記事の著者であれば、その記事の URL も添えてほしい。Issue は公開され、誰でも読める。

連絡を受けたら、内容を確かめ、誤りや問題があれば直す。直した内容はリポジトリの commit の履歴に残り、誰でも見られる。

## 参考 {#references}

- [kyopro-atlas「AtCoder黄色到達教材 要件定義」](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/requirements.md)：教材の目的と、事実を確かめる・文章を転載しない・出典を残す約束
- [kyopro-atlas「決定事項の記録」](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/decisions.md)：AtCoder と Codeforces の noai の指定、AtCoder のページを AI で読まない決定、教材のライセンスと段階「完成」の意味
- [kyopro-atlas「執筆の手引き」](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/style-guide.md)：Web と出典の決まり（§2.6・§11）と、確かめたドメインの記録（付録 B）
- [kyopro-atlas「事実の検証のチェックリスト」](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/checklists/fact.md)：出典の文章に近すぎないかの確かめ方（F8）と、参考の URL の確かめ方（F9）
- [kyopro-atlas「check_noai.py」](https://github.com/yuukougun/kyopro-atlas/blob/main/tools/check_noai.py)：noai・noimageai の指定の確かめ方
- [kyopro-atlas「進捗と残り作業」](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/progress.md)：執筆・検証の流れと、全体の検証の 2 巡
- [kyopro-atlas「工程11：Issue の対応（2026-10-29〜）」](https://github.com/yuukougun/kyopro-atlas/blob/main/planning/batches/fix/README.md)：Issue を直し、直した結果を別の担当が検証する流れ
- [Creative Commons「表示 4.0 国際」](https://creativecommons.org/licenses/by/4.0/deed.ja)：CC BY 4.0 で許される使い方と、出典の表示の条件
