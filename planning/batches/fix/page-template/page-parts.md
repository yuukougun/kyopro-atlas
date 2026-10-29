# page-parts の報告（グループ page-template、2026-10-29）

担当の Issue：#9（段階と更新日）・#10（誤りの報告の入口）・#54（上の帯の節の印）・#56（関連の表示）。
作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/page-template（feat/page-template）。git は読むだけで、commit などはしていない。

## 直したファイル

| ファイル | 変更 |
| --- | --- |
| `overrides/main.html` | `site_nav` ブロックを足した（目次の印）。`content` ブロックに、見出しの印・節へ移るリンク・関連の欄・最後の行（段階・更新日・報告）を足した。冒頭のコメントを改めた（+159／−20 行） |
| `overrides/assets/css/kp.css` | 末尾に追記だけ（529 行目〜、+111 行。既存の規則は 1 行も変えていない） |
| `docs/start/how-to-use.md` | 本文（#levels・#page-anatomy・#stub・#progress を直し、#report の節を足した）、front matter の sections に `{title: 誤りの報告, anchor: report}`、`updated: 2026-10-29`（stage は変えていない） |
| `.github/ISSUE_TEMPLATE/page-error.yml` | 新規。Issue forms のひな形 |
| `planning/interfaces.md` | 版の行、§2 に 3 項目（related・sections の level・stage と updated の表示）、§7 の表（「理解した」の行を改め、「節のレベルの印」「前提・次に読む・関連」「段階・更新日・誤りの報告」の行） |

新しい JS は作っていない。印もリンクも HTML に書く作りにしたので、`mkdocs.yml` の `extra_javascript` を足す必要もない（`mkdocs.yml` は触っていない）。

## #9 段階と更新日 — 完了

- `main.html` 295 行目〜：ページの最後の行（`div.kp-page-info`）に「段階 検証済み」「更新日 2026-10-22」を出す。表示名は stub＝準備中、draft＝下書き、reviewed＝検証済み、done＝完成。段階の文字は「この教材の使い方」の `#stub` へのリンクにした。更新日は `<time datetime>` にした。stub の「準備中」の帯（上）は変えていない。
- 置き場所はページの下にした。上の帯は 390px で既に 2〜3 行あり、これ以上足すと題名が下がる。#10 の報告のリンクと同じ行にまとめられる（Issue #10 の本文もまとめてよいとしている）。
- `kp.css` 589 行目〜：`.kp-page-info`・`.kp-stage`（準備中・下書きは `--kp-stub-color`、検証済み・完成はリンクの色）。
- `how-to-use.md` の `#stub`（250 行目〜）に、4 つの段階の意味の表と、「検証済みでも誤りは残りうるので報告する」「更新日は中身を最後に直した日」を足した。既存の 2 段落はそのまま残した。
- 確かめたこと：353 ページすべてで、表示の段階と更新日が front matter と一致する（作業用フォルダの `verify_site.py`）。stub・draft・done は、作業用フォルダのコピーで 3 ページの stage を変えてビルドし、表示名・色・stub の帯を画像で確かめた（stub のページには節へ移るリンクを出さないことも）。
- 残り：`updated` を書き換える場合の規則は手引きの変更なので、提案 5 にした。

## #10 誤りの報告の入口 — 完了（GitHub 上の動作はマージ後に 1 回確かめる）

- 受け口は GitHub の Issue だけにした（ほかの受け口は作らない）。ひな形は Issue forms の `.github/ISSUE_TEMPLATE/page-error.yml`。項目は、ページの題名（`page-title`、必須）・URL（`page-url`）・更新日（`page-updated`）・種類（`kind`、選択、必須）・場所（`where`）・内容（`what`、必須）。冒頭の説明に「Issue は公開される。問題文や解説の文章は写さず、問題 ID で示す」と書いた。
- `main.html` 329 行目〜：どのページにも（id のないホーム・分野の入口・一覧の 67 ページにも）、最後の行に「このページの誤りを報告する」を出す。行き先は
  `https://github.com/yuukougun/kyopro-atlas/issues/new?template=page-error.yml&title=誤りの報告：<題名>&page-title=<題名>&page-url=<URL>&page-updated=<updated>`
  （値はすべて `urlencode`、属性は `| e`）。form の項目の id が URL の引数の名前になる（GitHub Docs「Syntax for GitHub's form schema」の id の説明）。新しいタブで開く（`target="_blank" rel="noopener"`。instant navigation も横取りしない）。
- 題名は front matter の `title` を使う。nav_title のある 3 ページでは `page.title` が短い名前になるため。URL は `page.canonical_url`（公開の URL）。
- `labels` などの引数は付けない。GitHub Docs「Creating an issue」に、引数の権限がない人が開くと 404 になるとある。form の `labels` も付けていない（合うラベルがない。提案 8）。
- `how-to-use.md` に「誤りの報告 {#report}」の節（267 行目〜）を足し、#stub・#page-anatomy から案内した。#2 の方針のページへのリンクは張っていない。
- 確かめたこと：
  - form を SchemaStore の `github-issue-forms.json`（作業用フォルダの `dl-schema/` に取った）で検査し、エラー 0、id の重複なし。
  - 353 ページの報告の URL を `parse_qs` で分解し、template・title・page-title・page-url・page-updated が front matter と一致する。id のない 67 ページにもリンクがある（404 だけは別の担当の `overrides/404.html` が content を上書きするので出ない）。
- 残り：ひな形は既定のブランチにないと使えないので、マージ後に 1 ページの報告のリンクを開き、題名と 3 つの項目が入ることを確かめる（提案 11）。GitHub Docs では Issue forms は public preview である。

## #54 上の帯の節の印 — 完了（節の頭の 1 文の書き方は提案）

- 見出し：`main.html` 220 行目〜。本文の HTML の `<a class="headerlink" href="#<anchor>"` の前に `<span class="kp-mini kp-lv-<色> kp-sec-lv" title="青の節（difficulty 1600〜1999）">青</span>` を入れる（文字列の置き換え。toc の permalink が前提）。
- 目次：`main.html` 29 行目〜の `site_nav` ブロック。`super()` の HTML の `<a href="#<anchor>" class="md-nav__link">` の直後に同じ印を入れ、CSS の `order` で題の後ろに出す。右の目次と、狭い画面でナビゲーションの中に出る目次の両方に付く。目次の部分テンプレート（toc-item.html）は上書きしていない。
- JS を使わず HTML に書くので、instant navigation で入れ替わったページにもそのまま出る（`document$` で付け直す処理が要らない）。検索の索引は本文の HTML から作られるので、印は入らない（`search_index.json` で確かめた。変わったのは how-to-use の 4 項目と #report だけ）。
- 「理解した」：上の帯の節のチェック欄（`label.kp-check`、そのまま）を `span.kp-understood__item` で包み、横にその帯の最初の節へ移るリンク `a.kp-check__jump` を置いた（158 行目。上では↓、下では↑。`aria-label`「青の節へ移る」、`title` に節の題）。準備中のページには出さない。同じ帯の節が 2 つ以上ある 31 の帯では最初の節へ移り、ほかの節は見出しと目次の印で見つける。
- 既存の不具合も直した（129 行目〜）：Zensical でだけ、同じ帯の節が 2 つ以上あると「理解した」のチェック欄が重なって出ていた（acl-reading の水の節は 5 つで、チェック欄が 5 回出る）。`for … if … lv not in lv_ns.levels` が、MiniJinja では先に全部を選ぶため。元の main.html を Zensical でビルドして、重なりが元からあることを確かめてから直した。MkDocs の出力の「理解した」の input は、全 420 ページで元のビルドと同じ。
- `kp.css` 529 行目〜：見出しの印（0.6em）、目次の印（`.md-typeset` の外なので `kp-mini` の形を書いた）、節へ移るリンク（2em の丸。指の端末では 44px）。
- 確かめたこと（数。完了の条件）：site/ の HTML で、198 節の見出しの印 198、目次の印 396（198 × 2 か所）、節へ移るリンクは 156 の帯 × 上と下。Zensical 0.0.71 の出力でも同じ数。
- 確かめたこと（動き）：ヘッドレスの Chrome（CDP）で、basics/binary-search から instant navigation で binary-search-answer へ移った（window に置いた値が残るので、同じ文書のまま）。移った後に見出しの印 2・目次の印 4・節へ移るリンク 4 があり、↓ を押すと `#dp-check` の見出しがヘッダーの下（上から 68px）に来る。↑（下の欄）で `#real-number` へも移る。「青の節」を押すとチェックが付き、下のチェック欄と localStorage も変わる（progress.js はそのまま動く）。
- 390px：本文の見出しと、ナビゲーションの中の目次に印が出る（画像 `bsa-390-drawer.png`）。3 つのチェック欄があるページでは、上の帯の「理解した」が 2 行になる（判断 3）。

## #56 関連の表示 — 完了（design.md の改めは提案）

- `main.html` 66〜124 行目・269 行目〜：ページの下の欄に「関連」を足した。
  - 並び：front matter に書いた順。レベル順にすると、題材別のページで話題ごとのまとまりが崩れる（例：patterns/interval は累積和 → 尺取り → … → 平面走査の順に並んでいる）。
  - 上限：20 件。今の最大（patterns/interval）が 20 件なので、いまの related はすべて 1 回のクリックで開ける。超えた分は「ほか N 件は知識マップで見る」（知識マップの焦点の表示には関連の囲みが出る）。
  - `id#anchor` は「ページの題名 › 節の題」で節へのリンクにする。節の題は相手の sections の title、レベルの印は節の level（なければページの level）。
  - 前提と、出した次に読む（8 件）にあるページは、関連に重ねて出さない（節への関連は出す）。related のうち 263 件（129 ページ）が次に読むのページと重なり、そのうち次に読むに出る 260 件を関連から外した（1,955 件 → 1,695 件。判断 4）。
- `kp.css` 580 行目〜：関連の欄は行の全幅を使い、幅に応じて段に分ける（`column-width: 15em`）。1280px では 2 段、390px では 1 段。
- `how-to-use.md` の「ページの構成と読み方」（185 行目〜）に、ページの下の前提・次に読む・関連の 3 つの欄の説明を足した。
- `interfaces.md` §2・§7 を改めた。design.md は提案 2・3。
- 確かめたこと：353 ページで、関連の件数・行き先（anchor を含む）・題・レベルの印が、front matter から計算した期待と一致する（1,695 件、うち節 210 件）。

## 共通の確認

| 検査 | 結果 |
| --- | --- |
| `.venv/bin/mkdocs build --strict -q -d <作業用フォルダ>/site2` | 成功（警告なし） |
| `.venv/bin/mkdocs build -q -d <作業用フォルダ>/site` | 成功。ビルドの時間は元と同じくらい（15.1 秒 → 15.5 秒） |
| Zensical 0.0.71（`uvx --offline`、作業用フォルダのコピーで `zensical build --strict`） | 成功（No issues found）。HTML の照合も指摘 0 |
| `python3 tools/check_pages.py --page how-to-use`・全ページ | どちらもエラー 0・警告 0 |
| `npx textlint docs/start/how-to-use.md` | エラー 0。警告 4 は直す前からある 4 件と同じ（137・190 行の助詞「か」、224 行の [ の対、385 行の文の長さ） |
| `python3 tools/gen_site.py --check` | 4 ファイルが古い：`docs/llms.txt`・`docs/index/start.md`・`overrides/assets/data/graph.json`・how-to-use の版の生成ブロック。how-to-use の節（report）と updated を変えたため。メインが流す（提案 1） |
| 見た目（ヘッドレスの Chrome、390px のタッチ・1280px・ダーク） | binary-search-answer（上の帯・見出し・目次・ナビゲーションの中の目次・下）、patterns/interval（関連 20 件）、thinking/contribution（節への関連）、how-to-use、一覧のページ、ホーム。390px で横にはみ出さない（scrollWidth = 390） |

作業用フォルダ（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/page-template/page-parts）に、検証に使えるものを残した。

- `verify_site.py <作業ツリー> <site>`：ビルドした HTML を front matter と照らす（見出しと目次の印、節へ移るリンク、関連、段階・更新日・報告の URL）
- `cdp.mjs <site> <出力> <jobs.json>`：site を `/kyopro-atlas/` の下で配り、ヘッドレスの Chrome で撮る・調べる。Material は sitemap の URL の port を合わせないので、`kyopro.test:80` をこの server へ向けて instant navigation を試せるようにした。日本語のフォントは `fonts.conf`（Windows のフォントを足す。`tools/render_svg.py` と同じ方法）を `FONTCONFIG_FILE` で渡す
- `shots/`：撮った画像。`jobs*.json`：撮り方

## 提案（共有のファイル）

1. `python3 tools/gen_site.py` を流す（上の 4 ファイル）。
2. design.md §8.4「前提・次に読む」の項に足す：「関連（related）も出す。front matter の順に 20 件まで、`id#anchor` は節の題を添えて節へ。前提・次に読むに出たページは重ねない。超えた分は知識マップの焦点の表示へ」。「バッジ」の項に足す：「上位の帯の節の見出しと目次にレベルの印を付ける。段階（stage）と更新日（updated）と誤りの報告のリンクをページの最後の行に出す」。
3. design.md §3.2 の表の「前提」の行の使い道を「知識マップ、次に読む・関連の欄、ロードマップの順序」にする。§3.3 の related のコメントを「あると良い関連。節は id#anchor。ページの下の『関連』に書いた順で出る」にする。
4. style-guide §2.3：「見出しに色の印は付けない」を「見出しに色の印を手で書かない（level のある節の見出しと目次には、テンプレートが印を付ける）」にする。同じ項の「上位の帯の節は、最初に追加の前提をリンクで示す」を、#54 の「節の頭の 1 文」として次の形にそろえる案：「上位の帯の節は、見出しの直後に 1 文で追加の前提を示す（例：この節は [遅延セグメント木](…) を前提にする）。帯の名前は見出しの印で分かるので、『この節は青の内容である』とは書かない」。そろえる作業は本文の直しなので、content-consistency などのバッチで。
5. style-guide に `updated` の規則を足す案（#9）：「読者に見える中身（本文・問題の行・図・取り込むコード片）を直したら、その日にする（誤字の直しも含む）。front matter だけの変更と、gen_site.py が書き換える生成ブロックだけの変更では変えない」。how-to-use は「更新日は、そのページの中身を最後に直した日である」と書いたので、これと合う。
6. style-guide（front matter の節）に足す案：「related は近いものから書く（ページの下の『関連』にこの順で 20 件まで出る）」。
7. 任意：`tools/check_pages.py` に「related が 20 件を超える」警告を足す（超えた分はページの下に出ず、知識マップでしか見えない）。
8. GitHub にラベル（例：「誤りの報告」）を作り、`page-error.yml` に `labels: [誤りの報告]` を足す（ない名前は無視されるので、ラベルを作ってから）。
9. #2（出典と AI 利用の方針）のページは、報告の仕方を書き直さず、「この教材の使い方」の [誤りの報告](../start/how-to-use.md#report) へリンクして案内をそろえる。
10. 任意：README の「状態」の行に「各ページの最後の行に段階と更新日を出している」と足す。
11. マージ後に、公開のサイトで 1 ページの「このページの誤りを報告する」を開き、form の題名・ページの題名・URL・更新日が入ることを確かめる（form は既定のブランチにないと使えないので、マージの前には試せない）。

## 判断してほしい点

1. 段階と更新日はページの下（最後の行）に置いた。上の帯に置くほうがよければ移せる。
2. how-to-use の「検証済み」の説明は「書いた担当とは別の担当が、事実・コード・図・説明の分かりやすさを確かめ、見つかった誤りを直した」とした。検証したのが AI のサブエージェントであることを書くかは、#2 の方針に合わせて決めてほしい。
3. 390px では、上の帯の節のチェック欄の横の ↓（44px の丸）のため、3 つのチェック欄があるページで「理解した」が 2 行になる（元は 1 行）。このままでよいか。
4. 関連で、次に読むに出たページは重ねて出さない（260 件を外した）。重ねても出すほうがよいか。
5. 範囲の外で気づいた既存の点：nav_title のある 3 ページ（cpp-integer-overflow・cpp-structured-bindings・suffix-automaton）で、ページの h1 が短い名前（nav_title）になっている。MkDocs が nav の題名を page.title にし、Material の content.html が h1 に page.title を使うため（Zensical も同じ）。直すかどうか（触れていない）。

## 検証の指摘への対応（2026-10-29）

検証の報告 `verify-page-parts.md` の「直しが要る点」1 件を直した。作業用フォルダは `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/page-template/fixup-page-parts`（以下 `<F>`）。git は読むだけにした。

### 指摘 1（#56）：「関連」の説明の「前提の関係はないが」— 直した

- 判断：指摘は正しい。front matter で数えると、related のうち相手がこのページを前提にしているもの（次に読むの関係）はページ 263 件・節 11 件あり、相手がこのページの前提であるもの（前提の関係）は 0 件だった。ビルドした HTML（`<F>/site`）で関連の欄の 1,695 行を調べると、次に読むの関係がある行は 14 行（ページ 3：bit-operations → xor-basis、dp-basics → dp-speedup-overview、tree-traversal → euler-tour。節 11：dp-order → expected-value-dp#order・game-basics#win-lose など）で、検証の報告の数と一致した（`<F>/related_rel.py`）。
- 直したところ：`docs/start/how-to-use.md` 199 行目（#page-anatomy の「ページの下の 3 つの欄」の箇条書き）の最初の文
  - 前：「**関連**：前提の関係はないが、あわせて読むとよいページと節。」
  - 後：「**関連**：前提・次に読むとは別に、書き手があわせて読むとよいとしたページと節。」
  - 後ろの 3 文（本文でリンクしていないものも入る／書き手が並べた順に 20 件まで／前提・次に読むに出たページは重ねて出さない）はそのまま
- 新しい文が、関連の欄に出る行のすべてに合うこと：関連の欄の行はどれも related（書き手が挙げたもの）から出て、前提・次に読むは prerequisites から出る別の欄である。新しい文は前提の関係の有無を言わないので、14 行にも当たる。最後の文「前提・次に読むに出たページは重ねて出さない」は出たページだけを外すという意味なので、次に読むの 9 件目以降の 3 ページと節 11 件が関連に残ることと矛盾しない。
- 同じ言い過ぎがほかにないこと：担当のファイル（main.html・kp.css・how-to-use.md・interfaces.md・page-error.yml）に「前提の関係はない」のような言い方はほかにない（interfaces.md §2・§7 は並び・件数・重ねない規則だけを書いている）。design.md の「前提と related に同じページを置かない」（D12）は自分の前提との重なりの話で、数えた結果（0 件）とも新しい文とも合う。
- front matter：`updated` は最初の直しで 2026-10-29 にしてあるので変えていない。`stage` は reviewed のまま。

### 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --page how-to-use`・全ページ | どちらもエラー 0・警告 0 |
| `npx textlint docs/start/how-to-use.md` | エラー 0。警告 4 は直す前と同じ 4 件（137・190 行の助詞「か」、224 行の [ の対、385 行の文の長さ）。HEAD の版にも同じ 4 件がある（行は 136・189・217・357） |
| `.venv/bin/mkdocs build -q -d <F>/site` | 成功（14.5 秒） |
| `.venv/bin/mkdocs build --strict -q -d <F>/site2` | 成功（終了コード 0。出たのは Material の MkDocs 2.0 についての案内だけ） |
| ビルドの HTML | 両方のビルドの how-to-use に新しい文があり、「前提の関係はないが」は 0 件 |
| 見た目（`<F>/cdp.mjs`。最初の担当のスクリプトの写し） | how-to-use の 3 つの欄の箇条書きを、1280px のライト・ダークと 390px のタッチのライト・ダークで撮った（`<F>/shots/howto-1280-cols.png`・`howto-1280-dark-cols.png`・`howto-390-cols.png`・`howto-390-dark-cols.png`）。崩れなし。4 つとも scrollWidth が画面の幅と同じで、横にはみ出さない |
| `python3 tools/gen_site.py --check` | 古いのは最初の直しと同じ 4 ファイル（`docs/llms.txt`・`docs/index/start.md`・`overrides/assets/data/graph.json`・how-to-use の版の生成ブロック）。この直しで増えたものはない。提案 1 のままメインが流す |

### 検証の報告の推奨（§6）について

§6 の 4 点は「直さなくてよい」とされ、今回の直す点に入っていないので、直していない。直すかどうかはメインが判断する（直すなら、どれも担当のファイルの中で済む）。

1. `how-to-use.md` 281 行目（#progress）の「欄の横の矢印を押すとその節へ移る」を「その帯の最初の節へ移る」にそろえる（189 行目と同じ言い方）
2. `planning/interfaces.md` 148 行目を「チェック欄はどれも `span.kp-understood__item` で包み、上の帯の節の欄には横に…」と、作りのとおりに書く
3. `overrides/main.html` 115〜121 行目：related の `id#anchor` の相手が stub なら、anchor と節の題を落としてページへのリンクにする（または check_pages に警告を足す）。いまは stub のページがないので起きない
4. `overrides/main.html` 35〜37 行目：目次の印に `aria-hidden="true"` を付け、読み上げの順を見た目にそろえる

### 作業用フォルダに残したもの

- `<F>/related_rel.py <作業ツリー> <site>`：関連の欄の行のうち、前提・次に読むの関係がある行を数える
- `<F>/jobs-howto.json`：撮り方。`<F>/shots/`：撮った画像
- `<F>/how-to-use.HEAD.md`：textlint の比べに使った HEAD の版
