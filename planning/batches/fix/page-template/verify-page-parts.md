# page-parts の検証の報告（#9・#10・#54・#56）

直した担当（page-parts）とは別の目で、`overrides/main.html`・`overrides/assets/css/kp.css`・`docs/start/how-to-use.md`・`.github/ISSUE_TEMPLATE/page-error.yml`・`planning/interfaces.md` の差分と、報告 `page-parts.md` を確かめた。ファイルは直していない（この報告だけを書いた）。git は読むだけにした。担当の検証用のスクリプトは使わず、照合のスクリプトは別に書いた。

作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/page-template/verify-page-parts`（以下 `<V>`）。

- ビルド：`<V>/site`（いまの作業ツリー）、`<V>/site-base`（4 ファイルを HEAD に戻したコピー `<V>/base-tree` から）、`<V>/site-var`（段階などを変えたコピー `<V>/var-tree` から。§2）、Zensical 0.0.71 の出力 `<V>/ztree/site`・`<V>/zbase/site`・`<V>/zvar/site`
- スクリプト：`<V>/check_site.py`（front matter と HTML の照合）、`<V>/diff_base.py`（新しい部品を除いて元のビルドと比べる）、`<V>/nav_test.mjs`（instant navigation）、`<V>/shots.mjs`・`<V>/shots_var.mjs`（画像）
- 画像：`<V>/shots/`・`<V>/shots-var/`

## 結論

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #9 段階と更新日の表示 | 合格 | 0 |
| #10 誤りの報告の入口 | 合格 | 0 |
| #54 上の帯の節の印 | 合格 | 0 |
| #56 関連の表示 | 直しが要る（軽微） | 1（使い方のページの「関連」の説明。§5） |

テンプレートの動きには直しの要る点がなかった。直しが要るのは、使い方のページの 1 文だけである。

## 1. Issue の完了の条件

| Issue | 完了の条件 | 結果 |
| --- | --- | --- |
| #9 | どのページでも、段階と更新日が見える | 満たす。id のある 353 ページすべてで、最後の行の段階の表示名と `<time datetime>` が front matter と一致した。id のない 67 ページ（ホーム・分野の入口・一覧など）は front matter に stage・updated がないので出ない |
| #9 | 「この教材の使い方」に段階の意味が書かれている | 満たす。`#stub` に 4 段階の表がある |
| #10 | どのページからも 1 回のクリックで報告を始められ、題名と URL が入る | 満たす（GitHub 上の動作はマージ後。§3）。420 ページすべて（404 を除く）に報告のリンクがあり、`parse_qs` で分解した template・title・page-title・page-url・page-updated が front matter（title のないホームは nav の題名「ホーム」）と canonical の URL に一致した |
| #10 | 「この教材の使い方」に報告の仕方が書かれている | 満たす。`#report` の節がある |
| #54 | 198 節の見出しと目次にレベルのバッジが出る | 満たす。見出しの印 198（すべて h2）、目次の印 396（右の目次 198・ナビゲーションの中の目次 198）。印の色と文字は sections の level と一致し、印のない節に余計な印はない。198 節はすべてページのレベルより上の帯である |
| #54 | 390px で、どの節が「青の節」か分かる | 満たす。本文の見出しの後ろとドロワーの目次に「青」「水」の印が出る（`shots/bsa-390-light-h2-dp.png`・`bsa-390-dark-drawer.png`） |
| #56 | related のページや節が、ページの下から 1 回のクリックで開ける | 満たす。related 1,955 件すべてについて、ページの下（前提・次に読む・関連）に同じ行き先（節は anchor まで）へのリンクがある。関連の欄に出るのは 1,695 件（節 210 件）、前提・次に読むと重なって外れたのは 260 件。リンク先のページと anchor はすべて実在した |
| #56 | 「この教材の使い方」に「関連」の欄の説明がある | 満たす（ただし 1 文に直しが要る。§5） |

「やること」のうち、手引きの決め事（#9 の updated の規則、#54 の節の頭の 1 文）、design.md の改め（#56）、#2 の方針のページとの案内のそろえ（#10）は、担当の報告の提案 4・5・2・3・9 になっている。担当が直してよいファイルの外なので、提案にしたのは規則どおりである。

## 2. 特に見ること

### 段階と、部品の出方

作業ツリーのコピー（`<V>/var-tree`）で 6 ページの front matter を変えてビルドし（`<V>/site-var`）、HTML と画像（`shots-var/`）で確かめた。

| ページと変えたこと | 結果 |
| --- | --- |
| basics/binary-search-answer を stub にし、本文を要点の囲みだけにした | 上に「準備中」の帯。最後の行に「準備中」（`--kp-stub-color`。ライト rgb(166,92,0)・ダーク rgb(255,183,77)）。節へ移るリンクは上にも下にも出ない。見出しと目次の印は見出しがないので 0 |
| graph/dijkstra を draft | 「下書き」が stub と同じ色で出る |
| ds/segment-tree を done | 「完成」がリンクの色で出る |
| misc/parsing の updated を消し、題名を `A&B #1 + C++ "q" <x> 100% ?=&y` にした | 更新日の項目が消え、報告の URL から page-updated が消える。題名は `&`→%26・`#`→%23・`+`→%2B・`"`→%22・`<`→%3C・`%`→%25・`?`→%3F・`=`→%3D と符号化され、分解すると元の題名に戻る |
| patterns/grid の related を空にした（レベルなし・前提なし・次に読むなし） | ページの下の `nav.kp-links` 自体が出ず、最後の行（段階・更新日・報告）だけが出る |
| patterns/interval の related を 26 件にした | 関連は 20 件で止まり、「ほか 6 件は知識マップで見る」（`?focus=interval`）が出る |

いまのデータでの出方：

- reviewed（353 ページすべて）：「検証済み」がリンクの色で、`how-to-use/#stub` へのリンクになる
- level のないページ（guide 19・pattern 10・hub 4・cpp 1 の 34 ページ）：「理解した」と節へ移るリンクは出ず、関連と最後の行は出る（`shots/guide-390-dark-bottom.png`）
- related が 0 件のページはいまはない。basics/bit-full-search は related の 4 件がすべて次に読むに出ているので、関連の欄が出ない（空の見出しは出ない）
- related が最多の patterns/interval（20 件）：1280px で 2 段、390px で 1 段。横のはみ出しなし（`interval-1280-bottom.png`・`interval-390-light-bottom.png`）
- 上の帯が 3 つある basics/fractional-binary-search：1280px で 1 行、390px で 2 行（`fbs-390-head.png`・`fbs-1280-head.png`）

### basics/binary-search-answer（sections に上位の節）

- 見出し：`#dp-check` に「青」、`#real-number` に「水」が headerlink の直前に入る。目次も同じ（`bsa-1280-dp.png`・`bsa-1280-dark-dp.png`）
- 「理解した」：基礎・水の節・青の節。水の欄の横の↓は `#real-number`、青は `#dp-check` を指す。本文では青の節が水の節より前にあるが、それぞれの帯の最初の節へ移るので正しい。同じ帯の節が 2 つ以上ある 31 の帯でも、front matter の最初の節が本文でも最初の節だった
- 390px のタッチの端末で↓は 44×44px。上の「理解した」は 2 行になる（担当の判断 3 のとおり。`bsa-390-light-head.png`）

### instant navigation（`nav_test.mjs`）

`<V>/srv/kyopro-atlas` をビルドへのリンクにして `python3 -m http.server` で配り、Chrome に `kyopro.test:80` をそのポートへ向けさせて、公開と同じ `/kyopro-atlas/` の下で開いた（Material は sitemap の URL の protocol と hostname だけを合わせ、port は合わせないため）。

| 手順 | 結果 |
| --- | --- |
| basics/binary-search で印を置き、本文の binary-search-answer へのリンクを押す | 印が残った（同じ文書のまま入れ替わった）。見出しの印 2、右の目次の印 2、ナビゲーションの中の目次の印 2、↓ 2・↑ 2、関連 2 件。段階・更新日と、報告の title・page-title・page-url・page-updated が移った先のページのものになった |
| ↓（水の節） | `#real-number` の見出しが上から 68px（ヘッダー 48px の下）に来た |
| ↑（ページの下の青の節） | `#dp-check` が上から 68px に来た |
| 上の「青の節」に印を付ける | 下の欄にも印が付き、localStorage に `understood.binary-search-answer.青` が入った |
| guide/method-comparison へ移る | 印 0・↓↑ 0・関連 13 件。報告の題名と URL が method-comparison のものになった |
| 戻る（history.back） | binary-search-answer に戻り、印・↓↑・報告が戻った。チェックの状態も残った |
| patterns/interval へ移る | 関連 20 件、最後の行も interval のもの |

コンソールのエラーと例外は 0 件だった。部品はすべて HTML に書かれ、Material が入れ替える `[data-md-component=container]`（本文と左右の目次を含む）の中にあるので、JS で付け直さなくても正しく出る。なお、instant navigation の後は Material が相対の href を絶対の URL に書き換える（`#real-number` → `http://…/binary-search-answer/#real-number`）。同じページの中への移動なので、動きは変わらない。

### 報告のリンクの符号化

- Jinja2 の `urlencode`（`/` だけを残す）で、題名の `+`（C++ の 6 ページ）は %2B、`'`（Mo's algorithm）は %27、空白は %20 になる。`+` が空白に化けることはない
- `href` は `| e` で `&` が `&amp;` になり、HTML の属性として正しい。HTML を戻した URL の文字は英数字と `%-_.~/:?=&` だけである
- 題名は front matter の title を使うので、nav_title のある 3 ページでも長い題名が入る（cpp-integer-overflow は「整数のオーバーフローと __int128」）。title のないホームは nav の題名「ホーム」が入る
- page-url は 420 ページすべてで `<link rel="canonical">` と一致した
- ひな形は SchemaStore の `github-issue-forms.json`（担当の取った `page-parts/dl-schema/` のファイル）に対して、自分の検査で 0 件のエラー。id・label の重複なし、id は英数字と `-` だけ、選択肢の重複なし。リポジトリは public・Issue は有効・既定のブランチは main（`gh repo view`）で、`validations.required` も効く。例に使った `abc340_e` は `tools/ap.py show` で実在を確かめた

### Zensical の約束

- `main.html` に Python のメソッドの呼び出し（`.xxx(`）はない。使っているフィルターは e・first・join・length・list・map・replace・safe・selectattr・string・url・urlencode で、`super()`・`namespace()` は関数である
- Zensical 0.0.71（`uvx --offline`。`.cache` を空のフォルダにしたコピーで実行）で `zensical build --strict` が「No issues found」。その出力に `check_site.py` を当てても指摘 0（見出しの印 198・目次の印 198×2・↓↑ 156×2・関連 1,695・報告 420・段階と更新日 353）。変えたコピーの Zensical の出力でも、特殊な題名の符号化・stub・draft・done・関連の上限が MkDocs と同じに出た
- 担当の「元の main.html は Zensical で同じ帯の節が 2 つ以上あると『理解した』のチェック欄が重なる」も確かめた：元のテンプレートを Zensical でビルドすると acl-reading の input が 12 個（MkDocs では 4 個）、直した後は 4 個

## 3. 別の箇所が壊れていないか

| 検査 | 結果 |
| --- | --- |
| `mkdocs build --strict`（作業ツリー、出力は `<V>/site-strict`） | 成功、警告なし |
| 元のビルドとの比較（`diff_base.py`。印・↓↑・包みの span・関連の欄・最後の行を除いて 421 ファイルを比べた） | 違うのは 29 ファイルだけ：how-to-use（本文を直したため）、404.html（別の担当の 404.html）、関連だけが出るようになった 27 ページの空の `nav.kp-links`（関連の欄を除いた残り）。ほかの HTML は 1 文字も変わっていない。「理解した」の input も全ページで元と同じ |
| 検索の索引 `search_index.json` | 変わったのは how-to-use の 5 項目（#levels・#page-anatomy・#stub・#report・#progress）だけ。印・最後の行は索引に入らない |
| `python3 tools/check_pages.py --page how-to-use`・全ページ | どちらもエラー 0・警告 0 |
| `npx textlint docs/start/how-to-use.md` | エラー 0。警告 4 は直す前のファイルと同じ 4 件（行がずれただけ） |
| `python3 tools/gen_site.py --check` | 4 ファイルが古い（llms.txt・index/start.md・graph.json・how-to-use の版の生成ブロック）。how-to-use の節と updated を変えたためで、担当の提案 1 のとおりメインが流す |
| progress.js | `input[data-kp-understood]` と `closest(".kp-check")` だけを使うので、span で包んでも動く（instant navigation の手順で確かめた） |
| 390px の横のはみ出し | binary-search-answer・patterns/interval・how-to-use・変えた 5 ページで、ライトとダークとも scrollWidth = 390 |
| 見た目（390px のタッチのライト・ダーク、1280px のライト・ダーク） | 上の帯・見出し・ドロワーの目次・右の目次・ページの下・最後の行・how-to-use の #stub の表と #report・ホームの最後の行。崩れなし |

## 4. 直したファイルの中身

- `how-to-use.md`：だ・である調。#page-anatomy・#levels・#stub・#report・#progress の記述は、§2 で確かめたテンプレートの動き（8 件・20 件の上限、重ねない規則、節の形、矢印、段階の表示名と色、報告の手順）と合う。2 列の表は 390px でも収まる
- `page-error.yml`：冒頭の注記（labels はない名前が無視される、項目の id が引数の名前）は GitHub Docs の Issue forms の説明と合う
- `interfaces.md`：§2 の 3 項目と §7 の表は、テンプレートの作りと合う（§6 に言い回しの推奨が 1 つある）
- `kp.css`：末尾への追記だけで、既存の規則は変わっていない。使っている変数（`--kp-c`・`--kp-cf`・`--kp-stub-color`）は両方の配色にある

## 5. 直しが要る点

### 1. 「関連」の説明の「前提の関係はないが」が、出ている関連の一部に当たらない（#56）

- 場所：`docs/start/how-to-use.md` 199 行目「**関連**：前提の関係はないが、あわせて読むとよいページと節。」
- 理由：related には、相手がこのページを前提にしている（＝次に読むの関係がある）ページや節も書かれている（263 件と節 11 件）。テンプレートは、次に読むに出た 8 件までのページだけを関連から外すので、関連の欄には次に読むの関係のある行が 14 件残る。ページ 3 件（basics/bit-operations → xor-basis、dp/dp-basics → dp-speedup-overview、tree/tree-traversal → euler-tour。どれも次に読むの 9 件目以降）と、節 11 件（dp/dp-order → expected-value-dp#order・game-basics#win-lose、string/string-basics → z-algorithm#cyclic-shift など）である。dp-order のページでは、次に読むの「期待値 DP」と、関連の「期待値 DP › 計算順序とメモ化再帰」が並ぶ。「前提の関係はない」は、この 14 件では事実と違う（事実の検証の F2「言い過ぎ」）
- 直し方の案：「**関連**：前提・次に読むとは別に、書き手があわせて読むとよいとしたページと節。」のように、前提の関係の有無を言わない形にする（後ろの文はそのままでよい）

## 6. 直さなくてよいが、直すとよくなる点（推奨）

1. `how-to-use.md` 281 行目（#progress）「欄の横の矢印を押すとその節へ移る」：同じ帯の節が 2 つ以上ある 31 の帯では、最初の節へ移る。189 行目（#page-anatomy）と同じく「その帯の最初の節へ移る」にそろえると誤解がない
2. `planning/interfaces.md` 148 行目「上の帯のチェック欄（`label.kp-check`）は `span.kp-understood__item` で包み」：実際はページのレベルの欄も含めてすべての欄を包み、リンクを置くのは上の帯の節の欄だけである。「チェック欄はどれも `span.kp-understood__item` で包み、上の帯の節の欄には横に…」とすると作りのとおりになる
3. `overrides/main.html` 115〜121 行目（関連の節へのリンク）：相手のページが stub のときも `#anchor` 付きの節へのリンクと「› 節の題」を出す。stub のページには見出しがないので、節へは移らない。手引き §7（「ほかのページの節へは、そのページが draft 以降のときだけリンクする」）・§14-23 と、check_pages の「準備中のページの節へのリンク」のエラーは本文のリンクにしか効かない（related の検査は相手の sections に anchor があるかだけを見る）ので、関連では見逃される。いまは stub のページがないので起きないが、本文より先に骨組みを公開するとき（how-to-use #stub）に起きうる。`q.meta.stage == "stub"` なら anchor と節の題を落としてページへのリンクにするか、check_pages に related の `id#anchor` の相手が stub なら警告を足す
4. `overrides/main.html` 35〜37 行目（目次の印）：印を `<a …class="md-nav__link">` の直後に入れ、CSS の order で後ろに見せているので、読み上げでは「青 判定を DP で作る…」と印が題の前に来る。見た目の順と読み上げの順をそろえるなら、目次の印には `aria-hidden="true"` を付ける（帯は本文の見出しの印で読み上げられる）。軽い点である

## 7. 担当の「判断してほしい点」について（メインへの参考）

- 判断 3（390px で「理解した」が 2 行）：確かめたとおり 2 行になる。3 帯ある fractional-binary-search も 2 行で収まり、はみ出しはない
- 判断 4（次に読むに出たページを関連に重ねない）：重ねない規則で 260 件が外れても、すべて次に読む・前提から 1 回のクリックで開ける。§5 の 14 件は、この規則の外（次に読むの 9 件目以降と節）として関連に残る
- 判断 5（nav_title のある 3 ページの h1）：報告のリンクの題名は front matter の title なので、この点の影響を受けない
