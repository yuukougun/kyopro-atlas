# verify-policy-page の報告（グループ policy-draft・Issue #2）

検証：policy-page の直し（docs/start/ai-and-sources.md〈新規〉・docs/index.md・docs/start/how-to-use.md）。作業ツリー kyopro-atlas-wt/policy-draft（ブランチ docs/policy-draft）。2026-10-29。ファイルは直していない（この報告だけを書いた）。

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #2 出典と AI 利用の方針 | 直しが要る | 4（必須 2・軽微 2） |

- 「やること」の 5 項目はすべて節になっている（ai-writing・no-copying・citations・noai・contact）。トップページと「この教材の使い方」からのリンクもある。「公開」はグループの方針（draft の pull request で、マージしない）どおりまだで、完了の条件は一部（Refs #2）
- 作者が確かめていないことの扱いはよい。「完成」のページがまだないこと、作者がすべてを確かめたものではないことを本文に書き、記録にない判断（3 つ目の約束・USACO Guide・対応の手順・受け口など）は `<!-- 作者が確かめる -->` に残している
- ただし、制作の事実として断定した文のうち 2 か所が、リポジトリの記録と食い違う（下の 1・2）

## 直しが要る点

### 1. 【必須】atcoder.jp・codeforces.com を「開かず、資料にもしていない」は記録と食い違う

- ファイル・行：docs/start/ai-and-sources.md 121（「そのため、制作では atcoder.jp（サブドメインを含む）と codeforces.com のページを AI で開かず、資料にもしていない」）、106（「atcoder.jp と codeforces.com のページは参考に入れない」）
- 理由：記録では、決まりを作る前と、指定を確かめるときに開いている。決まりの後も、AtCoder の公式の言語の一覧を元にした記述が本文と参考にある
  - planning/decisions.md 22〜28（2026-10-21「質問の前に確認した事実」）：AtCoder の問題・解説ページの meta、robots.txt と利用規約、img.atcoder.jp の言語一覧を確かめた記録。C++ の環境（GCC 15.2 のオプション）もここで記録した
  - docs/cpp/cpp-environment.md 307（参考の節）：「AtCoder の GCC 版のオプションの一覧…は、AtCoder の公式の言語の一覧（2025-10 の言語アップデートの時点）による」。atcoder.jp のサブドメインのページを資料にしたと、公開中のページ自身が書いている
  - planning/research/00-curriculum.md 136：codeforces.com の noai は「2026-10-21 に https://codeforces.com/edu/courses で確認」（AI が 1 ページを開いて見つけた）
- 直し方の案：決まりを作った時点からの話にし、例外を書く。例：「制作の始め（2026-10-21）にこれらの指定を確かめてからは、atcoder.jp（サブドメインを含む）と codeforces.com のページを AI で開いていない。例外として、AtCoder の C++ の環境（コンパイラとオプション）は、そのときに読んだ AtCoder の公式の言語の一覧（img.atcoder.jp。noai の指定はない）によっている（[C++ の環境](../cpp/cpp-environment.md#references)の参考）」。106 行は「URL は参考に入れない」とするか、同じ例外を添える。言い方を作者に決めてもらうなら、`<!-- 作者が確かめる -->` に上の記録を書く（本文は断定しない）
- 補足：AtCoder生成AI対策ルールの 20261014 版の中身（decisions.md 27）は、どこで読んだかが記録にない。atcoder.jp で読んだのなら同じ例外になるので、作者に確かめるコメントに入れるとよい

### 2. 【必須】「AtCoder の公式の解説も参考にしていない」「第三者の解説で確かめた」は、典型90・鉄則本・アルゴ数学で記録と食い違う

- ファイル・行：docs/start/ai-and-sources.md 106（「AtCoder の公式の解説も参考にしていない」）、104・121（「何を問い、どう解けるかは、第三者の解説で確かめた」「問いと解き方は第三者の解説で確かめた」）
- 理由：
  - 典型90 の公式の解説は、作者の E869120 氏が GitHub に置いた解説である。docs/graph/degree-sqrt.md 240 は E869120「kyopro_educational_90」の解説の画像を参考に挙げて「公式の解説の組み方」と書き、185 でも「公式の解説は逆向きの組み方をしている」と書く。github.com/E869120 にリンクする docs のファイルは 66 ある
  - 台帳 data/problems.yaml で、ページに載る問題のうち典型90 は 67 問中 55 問、鉄則本は 11 問中 10 問、アルゴ数学は 4 問中 4 問の evidence に、問題の作者（E869120 氏）の解説・解答例がある。そのうち 48 問（典型90 35・鉄則本 10・アルゴ数学 3）は evidence が作者のものだけで、「第三者の解説」で確かめたとは言えない
- 直し方の案：106 行は「atcoder.jp の解説ページ（AtCoder の公式の解説）は開いていない。典型90 は、作者が GitHub に公開している解説（公式の解説）を参考に挙げたページがある」とする。104・121 行は「第三者の解説（典型90・鉄則本・アルゴ数学は、作者が GitHub や Qiita に公開している解説も）で確かめた」とする
- メインへ：docs/start/how-to-use.md 243 の「問いと解き方を第三者の解説で確かめている」（元からある文）も同じなので、この直しにそろえるとよい

### 3. 【軽微】OI Wiki のライセンスが記録より狭い

- ファイル・行：docs/start/ai-and-sources.md 88（「cp-algorithms と OI Wiki（CC BY-SA）」）
- 理由：planning/research/00-curriculum.md 12・136 は「OI Wiki（CC BY-SA 4.0＋SATA）・cp-algorithms（CC BY-SA 4.0）」と記録している。ライセンスの条件を示す箇所なので、SATA を落とすと事実として足りない（手引き §11 の「（CC BY-SA）」に合わせた書き方だが、記録の詳しい方が正しい）
- 直し方の案：「cp-algorithms（CC BY-SA 4.0）と OI Wiki（CC BY-SA 4.0 と SATA）」。手引き §11 の表記も合わせるよう提案に足す

### 4. 【軽微】「参考の節は…すべてのページにある」がトップページや自動で作るページに当たらない

- ファイル・行：docs/start/ai-and-sources.md 102
- 理由：参考の節は、stage を持つ 354 ページのうち glossary・term-index 以外のすべてにある（数えて確かめた）。一方、トップページ（docs/index.md）、分野の入口（docs/<field>/index.md）、一覧（docs/lists/）、詳細索引（docs/index/）の 67 ファイルには参考の節がない。読者から見るとトップページや分野の入口もページなので、「すべてのページ」は言い過ぎになる
- 直し方の案：「参考の節は、用語集と用語の索引を除くすべての解説のページにある（トップページと、自動で作る分野の入口・一覧のページにはない）」

## 確かめたこと（問題のなかったもの）

- 記録との照合：requirements.md §2・§6・§8、decisions.md、progress.md（工程5・6・8b・10）、design.md §5.4・§6.5〜6.7・§8.6・§10・§12、style-guide §2.5〜2.7・§9・§11・§15-6・§16-1・付録 B、checklists/fact.md F8・F9・code.md C2、claude/project-instructions.md 3、tools/check_noai.py、tools/gen_site.py の STAGE_JA、overrides/main.html 102（stub のときだけ帯）、.github/workflows/check.yml（push と pull_request で check_pages・textlint・変わったコード片を gcc:15.2.0 で）、vendor/SOURCES.txt と各 LICENSE、third_party/ac-library/LICENSE（CC0）。1・2 以外の事実の記述は記録と合う
- 数：stage は reviewed 353・draft 1（このページ）・done 0。問題の行 1585 はすべて atcoder.jp の問題リンク（参考に atcoder.jp・codeforces.com の URL は 0）。docs のリンクのホスト 113 個は、自分のサイト以外すべて付録 B にある。図は docs/img の 414 枚がすべて SVG（外部の画像・`<image>` なし）、Mermaid 10、動く図 28。ページに載る問題 1251 問はすべて確認済みで evidence がある。参考の節は 351/353 ページ（+ このページ）。学ぶための資料の節は overview 51 ページすべて
- 第三者の確認（2026-10-29、check_noai.py）：trap.jp の post/1224・2589・2861 は HTTP 200 で noai・noimageai なし（policy-page の提案 4 と同じ結果）。AtCoder Problems（https://kenkoooo.com/atcoder/）も HTTP 200 で指定なし、robots.txt は 404（メインの判断 10 の材料。付録 B に足すとよい）

## 書き換えない検査

- `python3 tools/check_pages.py -v --page ai-and-sources --page how-to-use --page docs/index.md`：エラー 0・警告 0。全ページ：エラー 0・警告 0（354 ページ、draft 1・reviewed 353）
- `npx textlint docs/start/ai-and-sources.md docs/start/how-to-use.md docs/index.md`：エラー 0。警告 5（how-to-use 138・191・219・359、index 3）はどれも変更していない行で、元からあるもの。新しいページは 0
- `python3 tools/gen_site.py --check`：生成物が古い 9 ファイル（nav.yml・docs/start/index.md・lists・llms.txt・index/start.md・graph.json・term-index・how-to-use の生成ブロック）。新しいページを足したので想定どおり（メインが gen_site を流す）
- `uv run --frozen mkdocs build -d <作業用フォルダ>/site`：成功。警告は nav に載っていないこと（start/ai-and-sources.md）だけ
- 表示：作業用フォルダで http.server を立て、ヘッドレスの Chrome で幅 390px のライトとダークを撮った。要点・箇条書き・meta タグのインラインコードの折り返し・参考の節まで崩れなし。コメントは表示されない。トップページの追加の 1 行もダークで確かめた。リンク（index → start/ai-and-sources/、how-to-use → ../ai-and-sources/、#ai-writing など 6 つの anchor、how-to-use の #problems・#stub・#claude・#ai-rule-version）は解決する。幅 390px では長い h2 の「¶」が次の行に回って見出しの下が空くが、Material の既定の動きで、ほかのページも同じ

## メインへの補足（直しの必須ではない）

1. docs/string/hash-safety.md 316 の参考に「（1 枚目と問題文も参照）」とある（E869120 氏の典型90 のリポジトリ）。手引き §15-6 は個人の解説リポジトリの問題文を読まない決まりで、方針のページ 89 行は「問題文の部分を読まず、解法の部分だけを参照した」と過去の事実として書く。作者のリポジトリの問題文が §15-6 に入るかを決め、入るなら hash-safety の参考を見直すか、89 行を「読まない約束にしている」の形にする
2. 生成した HTML には `<!-- 作者が確かめる：… -->` のコメントがそのまま入る（表示はされない）。draft の pull request でマージしないので構わないが、公開の前に消す（26 行の指示どおり）。リポジトリが public なので、draft の pull request の差分ではコメントも誰でも読める
3. policy-page の報告の「editorial へのリンク 0 件」は atcoder.jp の解説のことで、github.com/E869120/…/editorial へのリンクは多数ある（上の 2）
