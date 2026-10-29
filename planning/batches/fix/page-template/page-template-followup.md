# page-template-followup の報告（検証の推奨 4 点、2026-10-29）

担当：page-parts の検証の報告 `verify-page-parts.md` §6 の推奨 4 点（メインの判断で直す）。
作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/page-template（feat/page-template）。git は読むだけ（status・diff）にし、commit などはしていない。
作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/page-template-followup`（以下 `<W>`）。直す前の 3 ファイルの写しは `<W>/before-src/`。

## 結論

| 推奨 | 直したところ | 結果 |
| --- | --- | --- |
| 1 「その節へ移る」を「その帯の最初の節へ移る」に | `docs/start/how-to-use.md` 281 行目 | 完了 |
| 2 「理解した」のチェック欄の説明を作りのとおりに | `planning/interfaces.md` 148 行目 | 完了 |
| 3 related の `id#anchor` の相手が stub ならページへのリンクに | `overrides/main.html` 103〜120 行目（あわせて `planning/interfaces.md` 68・150 行目） | 完了 |
| 4 目次の印に `aria-hidden="true"` | `overrides/main.html` 28〜30・38 行目 | 完了 |

直したのは上の 3 ファイルだけである。ほかのページの出力は、目次の印に aria-hidden が付いたこと以外は 1 文字も変わっていない（下の「確かめたこと」）。

## 1. how-to-use の「その節へ移る」

- `docs/start/how-to-use.md` 281 行目（#progress の「理解した」）：「欄の横の矢印を押すとその節へ移る。」を「欄の横の矢印を押すとその帯の最初の節へ移る。」にした。189 行目（#page-anatomy）の「その帯の最初の節へ移る」と同じ言い方である
- front matter は変えていない（`updated: 2026-10-29`、`stage: reviewed` のまま）

## 2. interfaces.md の「理解した」のチェック欄

- `planning/interfaces.md` 148 行目（§7 の「理解した」のチェック）を次にした
  - 前：「上の帯のチェック欄（`label.kp-check`）は `span.kp-understood__item` で包み、横にその帯の最初の節へ移るリンク（…）を置く」
  - 後：「チェック欄（`label.kp-check`）はどれも（ページのレベルの欄も）`span.kp-understood__item` で包む。上の帯の節の欄（「青の節」など）にだけ、横にその帯の最初の節（sections の順）へ移るリンク（`a.kp-check__jump`。矢印は CSS で、上では↓・下では↑）を置く。準備中のページは本文に節の見出しがないので置かない」
- 作りとの照合：`main.html` の 157 行目で、`lv_ns.levels` のすべての欄（ページのレベルを含む）を `span.kp-understood__item` で包む。リンクは `secs`（ページのレベルの欄では空）があり、最初の節に anchor があり、`m.stage != "stub"` のときだけ置く（162 行目）。最初の節は front matter の sections の順で選ぶ（`secs | first`）。矢印は `kp.css` の `a.kp-check__jump::before`（↓）と `.kp-links a.kp-check__jump::before`（↑）

## 3. 関連の `id#anchor` の相手が stub のとき

- `overrides/main.html` 114〜120 行目：related の `id#anchor` の相手の `meta.stage` が `stub` なら、anchor と節の題を落とし、ページへのリンク（印はページの level）にした。stub でない相手の節へのリンクは前と同じである
- 重ねない規則：前と同じく、前提と出した次に読む（8 件）に出たページは関連に出さない。今回、関連に出したページも「出した」に入れた（118 行目）。stub の相手の節が 2 つ以上あるとき（`X#a`・`X#b`）や、ページと節が両方あるとき（`X`・`X#a`）に、同じページへのリンクが 2 行出ないようにするためである。stub でない相手の節は、前と同じく、ページが出ていても出す
- いまの related には、同じ行の重なり・同じページのページと節・同じページの節 2 つ以上のどれもない（0 件。`<W>/rel_stats.py`）。stub のページもないので、いまの出力は変わらない
- コメント（103〜105 行目）を直した。Python のメソッドの呼び出しは使っていない（Zensical の約束。下で Zensical でも確かめた）
- 約束の文書も作りにそろえた（直してよい 3 ファイルの中）：`planning/interfaces.md` 68 行目（§2 の related）に「相手が stub の間は、節ではなくページへリンクする」、150 行目（§7 の前提・次に読む・関連）に「相手のページが stub なら、本文に節の見出しがないので、節ではなくページへのリンクにする（印はページの level）。前提・出した次に読む・関連にすでに出たページは、関連に重ねて出さない（節への関連は出す）」
- この規則は、how-to-use の #stub（265 行目）「そのページへのリンクは節ではなくページ全体を指し、本文が書けると節へのリンクに張り替える」と、`tools/gen_site.py`（30・352 行目。節へのリンクは draft 以降だけ）と合う。関連の欄は stage を見て出すので、stub が draft になると自動で節へのリンクに戻る

## 4. 目次の印の aria-hidden

- `overrides/main.html` 38 行目：目次（右の目次と、狭い画面でナビゲーションの中に出る目次）の印の `span` に `aria-hidden="true"` を足した。28〜30 行目のコメントに理由（HTML では題の前にあり CSS の order で後ろに見せるので、読み上げで題の前に来ないようにする。帯は本文の見出しの印で読み上げられる）を書いた
- 本文の見出しの印（229 行目）には付けていない（帯を読み上げる側として残す）

## 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `.venv/bin/mkdocs build --strict -q -d <W>/site` | 成功（警告なし。出たのは Material の MkDocs 2.0 についての案内だけ） |
| 直す前のビルド（`<W>/site-before`）との全ファイルの比較（`<W>/diff_builds.py`。目次の印の aria-hidden だけを外して比べる） | ファイルの増減なし。違いは 2 ファイルだけ：how-to-use の 1 文と、検索の索引の `start/how-to-use/#progress` の 1 項目。目次の印は前 396（右の目次 198・ナビゲーションの中の目次 198）→ 後 396 で、すべてに aria-hidden がある（ないもの 0）。見出しの印 198 には aria-hidden がない。関連の欄・「理解した」・最後の行は全ページで前と同じ |
| basics/binary-search-answer の目次の印（`<W>/bsa_parts.py`） | 4 個（`#dp-check` の「青」・`#real-number` の「水」が右の目次とナビゲーションの中の目次に 1 つずつ）。href・題・印の文字・class・title は前と同じで、aria-hidden だけが増えた |
| basics/binary-search-answer の関連の欄 | 前と同じ 2 件（「貪欲法の考え方と正当性」基礎、「DP の基本」基礎） |
| 見た目（ヘッドレスの Chrome。`<W>/cdp.mjs` は page-parts の担当のスクリプトの写しに、読み上げの名前を取る手順を足したもの。`<W>/jobs-bsa.json`） | 1280px のライト・ダークの右の目次と関連の欄、390px のタッチのドロワーの目次と関連の欄の 6 枚が、前のビルドと画素まで同じ（`<W>/shots-before/`・`<W>/shots-after/`）。印は前と同じく題の後ろに出る。aria-hidden を対象にする CSS は Material にも kp.css にもない |
| 読み上げの名前（CDP の Accessibility.getPartialAXTree） | 右の目次（1280px）とドロワーの目次（390px）のリンクの名前が、前「青 判定を DP で作る（決め打ちごとに初期化し直す）」→ 後「判定を DP で作る（決め打ちごとに初期化し直す）」（水の節も同じ）。本文の見出しは前も後も「判定を DP で作る（…） 青 ¶」で、帯が読まれる |
| stub の相手への関連（写し `<W>/var-tree` で 4 ページを stub にし、2 ページの related に行を足して、元のテンプレート `<W>/site-var-before` と直したテンプレート `<W>/site-var-after` でビルド） | `<W>/check_stub_related.py` で、元の関連の欄から規則で作った期待と、直した出力を 353 ページで照らして NG 0。関連の欄が変わったのは、stub の相手の節を挙げていた 11 ページだけで、stub のページの節へのリンクは残っていない |
| 　場合 A（前後の関係なし）：comb/minimax の `binary-search-answer#dp-check` | 前「答えで二分探索 › 判定を DP で作る（…）」青・`#dp-check` 付き → 後「答えで二分探索」基礎（ページの level）・ページへ |
| 　場合 B（相手が次に読むに出ている）：dp/dp-order の `expected-value-dp#order`、basics/divide-and-conquer の `monge#monotone-minima` | どちらも関連から外れた（期待値 DP・Monge は次に読むから開ける）。dp-order の `game-basics#win-lose`（stub でない）は前と同じに残る |
| 　場合 C（節 2 つとページ）：basics/periodicity に `…#pigeonhole`・`…#symmetry`・ページの順で書いた | 最初の位置に「対称性・鳩の巣原理・場合分け」のページへのリンクが 1 行だけ出る |
| 　場合 C'（ページが先、節が後）：comb/game-basics | ページへのリンクが 1 行だけ出る |
| 　場合 D（stub でないページとその節）：comb/minimax に `tree-dp`・`tree-dp#postorder` | 前も後も 2 行（ページと「木 DP › 帰りがけ順に…」）が出る |
| Zensical 0.0.71（`cd <W>/var-tree && uvx --offline zensical@0.0.71 build --strict`。直したテンプレート） | 「No issues found」。353 ページの前提・次に読む・関連の欄が MkDocs の出力（`<W>/site-var-after`）と同じで、stub の相手の節へのリンクは 0。目次の印 396 すべてに aria-hidden、見出しの印 198 にはなし（出力は確かめた後に消した。`<W>/zensical.log`） |
| `python3 tools/check_pages.py`（全ページ）・`--page how-to-use` | どちらもエラー 0・警告 0（終了コード 0） |
| `npx textlint docs/start/how-to-use.md` | エラー 0。警告 4 は直す前と同じ 4 件（137・190 行の助詞「か」、224 行の [ の対、385 行の文の長さ）。281 行目に指摘なし |
| `npx textlint planning/interfaces.md`（参考。CI の textlint は docs/ だけが対象） | 直す前も後も同じ 20 件（エラー 17・警告 3。3・25・30・74・85〜87・93・135・175 行目）。直した 68・148・150 行目に指摘なし |
| `python3 tools/gen_site.py --check` | 古いのは前と同じ 4 ファイル（`docs/llms.txt`・`docs/index/start.md`・`overrides/assets/data/graph.json`・how-to-use の版の生成ブロック）。この直しで増えたものはない |

## 残った点・提案

1. （page-parts の提案 1 のまま）`python3 tools/gen_site.py` を流す。この直しで生成物は増えていない
2. page-parts の提案 2（design.md §8.4 に関連の表示を足す）を反映するときは、「`id#anchor` の相手が stub の間は、節ではなくページへのリンクにする」も添えると、interfaces.md §2・§7 とそろう
3. 検証の報告の推奨 3 の別案（check_pages に「related の `id#anchor` の相手が stub」の警告を足す）は、テンプレートが自分でページへのリンクにするので要らないと考える
4. 参考：作業中に `git status` で `planning/design.md`・`planning/style-guide.md` の変更が増えた（ほかの担当の作業）。触れていない

## 作業用フォルダに残したもの（`<W>`）

- `site`（直した後）・`site-before`（直す前）：作業ツリーのビルド。`before-src/`：直す前の 3 ファイル
- `diff_builds.py <前の site> <後の site>`：全ファイルを比べる（目次の印の aria-hidden だけを外す）
- `bsa_parts.py <前の site> <後の site> <ページの相対パス>`：1 ページの目次の印と関連の欄を並べる
- `cdp.mjs`・`fonts.conf`・`jobs-bsa.json`・`jobs-ax390.json`・`run-before.json`・`run-after.json`・`shots-before/`・`shots-after/`：撮影と読み上げの名前（`FONTCONFIG_FILE=<W>/fonts.conf node cdp.mjs <site> <出力> <jobs>`）
- `var-tree/`（stub の試しの写し。main.html は直したもの）・`site-var-before`・`site-var-after`・`check_stub_related.py <ツリー> <元の site> <直した site>`・`zensical.log`
- `rel_stats.py`・`sec_rel.py`・`sec_rel.txt`：related の重なりと、節への related の一覧
