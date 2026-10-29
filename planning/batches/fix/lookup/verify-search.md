# verify-search の報告（グループ lookup・Issue #52、2026-10-29）

search の直し（#52 サイト内検索）を、書いた担当とは別の目で確かめた。作業ツリーは /home/yuuki/projects/kyopro2/kyopro-atlas-wt/lookup（feat/lookup）。ファイルは直していない（この報告だけを書いた）。git は読むだけにした。

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/lookup/verify-search（ビルド・検索の結果の JSON・画面写真・検証用のスクリプト `js/`）

## 結論

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #52 サイト内検索 | 合格。完了の条件は 2 つとも満たす | 0（任意の改善が 2 つ。メインに判断してほしい副作用が 3 つあり、そのうち「ビット + 別の語」の検索は担当の報告にない） |

## 確かめ方

ビルドは 3 つ作った。どれも `mkdocs build --strict` が警告なしで通った。

- before：HEAD（af7ee6c）を `git archive` で取り出したもの
- after：before に、この担当が直した 38 ページと、term-index の front matter の 1 行（`search: {exclude: true}`）だけを重ねたもの。ほかの担当の変更は含めない
- wt：作業ツリーをそのままビルドしたもの。ui の担当の変更を含む

検索の順位は 2 通りの方法で測った。

- 担当の `tools/check_search.mjs`：Material の検索の worker を node の vm で動かす
- 自前のヘッドレスの Chrome のスクリプト（`js/chrome-search.mjs`）：検索欄に語を入れて結果を読む。前の語の結果を読まないよう、語ごとに欄を空にして結果が消えるのを待ち、2 回続けて同じ結果になってから読む

wt で 100 語（調査の 45 語と、下の試しの 55 語）を引くと、上位 10 件と件数が 2 つの方法で全部一致した。check_search.mjs は、実際のブラウザと同じ並びを出すとみてよい。

## 1. 完了の条件 1：19 語で、目的のページが 3 位以内に出るか

満たす。19 語すべてが 3 位以内で、そのうち 14 語が 1 位である（`--within 1` で 14 / 19）。

| 語 | 目的のページ | before | after | wt | wt（Chrome） | wt の上位 3 件 |
| --- | --- | --- | --- | --- | --- | --- |
| BIT | fenwick-tree | 11 | 3 | 3 | 3 | bitset-speedup・bit-dp・fenwick-tree |
| UF | union-find | 9 | 1 | 1 | 1 | union-find・partially-persistent-union-find・offline-dynamic-connectivity |
| 全方位木DP | rerooting | 15 | 1 | 1 | 1 | rerooting・tree-dp・cpp-range-for |
| 全方位木 DP | rerooting | 15 | 1 | 1 | 1 | rerooting・tree-dp・cpp-range-for |
| ビットDP | bit-dp | 101 | 2 | 2 | 2 | bitset-speedup・bit-dp・cpp-math-functions |
| ビット DP | bit-dp | 101 | 2 | 2 | 2 | bitset-speedup・bit-dp・cpp-math-functions |
| フェニック木 | fenwick-tree | 114 | 1 | 1 | 1 | fenwick-tree・matrix-tree-theorem・segment-tree-binary-search |
| 01BFS | zero-one-bfs | なし | 1 | 1 | 1 | zero-one-bfs・glossary |
| にぶたん | binary-search | なし | 1 | 1 | 1 | binary-search・glossary |
| グランディ | grundy-number | なし | 1 | 1 | 1 | grundy-number・glossary |
| セグ木 | segment-tree | 5 | 2 | 2 | 2 | segment-tree-binary-search・segment-tree・lis |
| Union-Find | union-find | 6 | 1 | 1 | 1 | union-find・weighted-union-find・rollback-union-find |
| DSU | union-find | 5 | 1 | 1 | 1 | union-find・cpp-initialization・acl-reading |
| Mo | mo-algorithm | 3 | 1 | 1 | 1 | mo-algorithm・project-selection・monge |
| CHT | cht | 3 | 1 | 1 | 1 | cht・convex-hull・dp-speedup-overview |
| 累積和 | prefix-sum | 3 | 1 | 1 | 1 | prefix-sum・prefix-sum-2d・tree-distance |
| 最小全域木 | minimum-spanning-tree | 2 | 1 | 1 | 1 | minimum-spanning-tree・spanning-tree-advanced・kind-connectivity |
| LIS | lis | 2 | 2 | 2 | 2 | operation-sequence・lis・subsequence-and-substring |
| いもす | imos | 2 | 1 | 1 | 1 | imos・dp-prefix-sum・tree-imos |

- 代表の 65 語（`node tools/check_search.mjs`）は、before 38 / 65、after 65 / 65、wt 65 / 65 だった。担当の報告 §4.1・§4.2 と同じである
- ビット DP の 2 位は、1 位の bitset-speedup とほぼ同点である。3 位以内には確実に入る（3 位は cpp-math-functions。担当の測りでは 54% 下）

## 2. 完了の条件 2：検索の索引の大きさを測り直し、記録してあるか

満たす。測った値は担当の報告 §4.4 と一致した。記録は報告 §4.4 にある。

| | search_index.json | gzip（Python -6） | 項目 |
| --- | --- | --- | --- |
| before | 17,591,802 バイト | 3,488,882 | 5695 |
| after | 17,349,657 バイト | 3,449,181 | 5652 |
| wt | 17,358,107 バイト | 3,450,845 | 5652 |

## 3. 足した別名（aliases と本文の別名の行）

- **出典**：33 語（26 ページ）のどれも、用語集の略称の項（`#abbreviations`：にぶたん・全方位）か、表記の対応表（`#canonical-forms`。「別の書き方」「直す表記」）にある。どれも、目的のページの手法を指す正しい呼び方である。
  - スパニングツリーは表では全域木の別名である。全域木を定義するのは最小全域木のページだけで、このページにはもとから「最大全域木」の別名もある。
  - デックは deque の読みで、スタック・キュー・deque のページに当たる。
- **重なり**：33 語は、どれもほかのページの題名や別名と重ならない。1 語は 1 ページだけに当たる。
- **本文の別名の行**：全 355 ページで、「別名：」の行は aliases を「・」でつないだものと一字一句同じである（自前のスクリプトで確かめた）。`check_pages.py` は全ページでエラー 0・警告 0、直した 39 ページ（`--page`、`-v`）でも 0・0 である
- **updated**：別名の行を変えた 26 ページは、どれも `updated: 2026-10-29` である（5 ページが 10-22 から変わり、ほかはもとから 10-29）。tags・search だけを足した 12 ページ（bit-full-search・bitwise-independence・cpp-math-functions・mo-algorithm は 10-22 のまま）は変えていない。手引き §2.1 に合う
- **生成物**：after の写しで `gen_site.py --check --diff` を流した（書かない）。古くなるのは 14 ファイルで、差分は次の 3 つだけである。tags・search は生成物に出ない。メインが gen_site を流せばよい。
  - 詳細索引の「別名」の行
  - 用語の索引の新しい行（「にぶたん → 二分探索」「スパニングツリー → 最小全域木」など）
  - 版の文字列

## 4. front matter の新しい項目（schema と check_pages）

- `schema/page.schema.json`：トップは `additionalProperties: false` なので、`tags` を足すことが要る。足した `tags` は「重複のない、空でない文字列の配列」で、14 ページすべてで schema が通る
- 書き換えた写し（作業用フォルダの `neg/`）に `--root` で当て、次のとおり出ることを確かめた
  - エラー：`search.boost` 0 と -1、`tags: Mo`（文字列）と `tags: [UF, UF]`（重複）が schema、題名にも別名にもない tags（cht に「凸包」）
  - 警告：`search.boost` 3、xor から「ビット」の tags を外したもの、「フェニック」を含む別名を segment-tree に足したもの
- `python -m unittest discover -s tests/tools`：70 件 OK。作業ツリーの `git status` は前後で変わらない

## 5. 関係のない語への影響

### 5.1 調査の 45 語（before と after の上位 6 件を比べた）

- **崩れていない**：調査で 1 位だった 26 語は、after でも wt でも全部 1 位のままである
- 上位 6 件が変わった語は、どれも目的のページより下の入れ替わりだけだった
  - fenwick-tree（boost 1.8）が入ったもの：座圧 3 位、二分探索 5 位、bit全探索 6 位
  - そのほかのページが入ったもの：セグ木で lis 3 位（lis の boost 1.1。lis には「セグメント木版」の節がある）、尺取りで prefix-sum 5 位、遅延セグ木で segment-tree 6 位
  - 用語の索引が外れて上位 6 件から消えた語：nCr・フェニック・ロリハ・CHT・なもり・Grundy・ワーシャルフロイド
- 目的のページの順位が下がった語はない

### 5.2 全ページの題名と別名（`--sweep`）

before と after の両方で流した。担当の報告 §4.3 の数と、1 位でなくなった 20 語・3 位から外れた 6 語の一覧が、そのまま再現した。

- 題名：354 語。1 位 321、3 位以内 346
- 別名：2264 語。1 位 985、3 位以内 1422
- 1 位でなくなった語は、どれも 2 位である。3 位から外れた語は 4 位（5 語）と 6 位（多項式の逆元）である
- 目的のページが 3 位以上下がった別名は 14 語ある。直す前に 3 位以内だったのは多項式の逆元（3 位 → 6 位）だけで、ほかの 13 語は直す前から 19 位より下だった

### 5.3 担当の報告にない副作用：「ビット」と別の語を並べた検索

「ビット」の tags は 8 ページに付いていて、重みは題名の 1000 倍である。このため、「ビット」と別の手法の名前を空白で並べて引くと、8 ページが必ず上位 8 件を占める。目的のページは 9 位より下に落ちる。1 語だけで引くときは変わらない。

| 語 | 目的のページ | before | after |
| --- | --- | --- | --- |
| ビット 高速ゼータ変換 | zeta-mobius-subset | 1 | 9 |
| ビット 線形基底 | xor-basis | 1 | 9 |
| ビット 桁DP | digit-dp | 1 | 9 |
| ビット 主客転倒 | contribution | 1 | 9 |
| ビット XOR 基底 | xor-basis | 2 | 9 |
| ビット 最小全域木 | minimum-spanning-tree | 2 | 9 |
| ビット 半分全列挙 | meet-in-the-middle | 3 | 10 |
| ビット 包除 | inclusion-exclusion | 4 | 9 |
| ビット 部分集合 | subset-enumeration-dp | 6 | 12 |
| 高速ゼータ変換・部分集合の列挙・XOR 基底（1 語） | 各ページ | 1 | 1 |

- 1 ページだけに付けた tags の副作用は小さい。tags のページが 1 位になるだけで、目的のページは 2〜3 位に残る（UF 最小全域木 2 → 2、UF 連結成分 4 → 5、Mo 平方分割 2 → 3、全方位 木の直径 2 → 2）
- 担当の報告 §3.2 には「tags の語の前方一致に当たる検索では、tags のあるページがほかのどのページより上に来る」とある。仕組みとしては合っている。ただし、8 ページに付けた「ビット」では、目的のページが最初の画面から消えるところまでは書いていない
- tags の重み（mkdocs.yml の `plugins.search.fields.tags.boost`）を下げる案も試した。after の索引の重みだけを書き換えて測った
  - 2000：65 / 65 を保つ。高速ゼータ変換は 1 位、主客転倒は 2 位に戻るが、ほかの 7 語は 7〜12 位のままである
  - 5000：65 / 65 を保つが、高速ゼータ変換が 3 位に戻るだけである
  - 20000 以上：今と同じである
- この副作用は、8 ページに同じ tags を付ける作り方そのものから来る。重みを変えても消えない。直すには「ビット」の tags を外すしかない。外すと、ビット DP・ビットDP は 101 位に戻り、完了の条件を満たさない。どちらを取るかはメインの判断である（担当の §9「tags を使ってよいか」に足す材料）

### 5.4 2 字の「全…」の語（「全方位」の tags）

検索は「全*」で引かれるので、「全方位」の tags が当たる。担当の報告のとおりである。

- 全体・全部・全射・全単射・全順序・全区間・全通り・全確率・全クエリ：1 位が bit-full-search から rerooting に変わった。どちらも目的のページではなく、直す前から崩れていた
- 全期待値：expected-value-dp が 1 位 → 2 位
- 全探索・全列挙・全域木・全点対最短路・全頂点・全探索の設計：変わらないか、良くなった

### 5.5 用語の索引を検索から外したこと

用語の索引のページは、自分の題名と別名で引いても出なくなる。担当の報告 §5 に書いてあるとおりである。

| 語 | before | after |
| --- | --- | --- |
| 用語の索引 | 用語の索引が 1 位 | 出ない（1 位は用語集。要点から用語の索引へのリンクがある） |
| 索引 | 用語の索引が 1 位 | 出ない（1 位は問題番号の索引） |
| 五十音順 | 用語の索引が 1 位 | 出ない |
| 別名の索引 | 用語の索引が 1 位 | 出ない |

外さずに `search: {boost: 0.3}` で下げる案も試した。この値では自分の題名でも上位 3 件に入らないので、間を取る案にはならない。外すか残すかの二択で、判断はメインに任せる（担当の §9）。

## 6. 表示（幅 390px・ダークとライト）

作業用フォルダで http を立て、wt のビルドを Chrome で撮った。画面写真は作業用フォルダの次のファイルにある。

- 検索の結果：`shot-search-uf-dark.png`・`shot-search-bitdp-dark.png`・`shot-search-grundy-light.png` など
- ページ：`shot-page-uf-dark.png`・`shot-page-bs-light.png` など

- 検索の結果の 1 件目の下に、tags の印（UF・DSU、ビット、グランディ）が出る。当たった語には印が付く。ダークモードでも読める。tags のある節は全部当たるので、「このページ内にあと N 件」の数は増える（害はない）
- ページの上には tags の印が出ない。union-find・bit-dp・xor・fenwick-tree の HTML に `md-tag` はない。overrides にも tags を描くところはない
- union-find と binary-search のページは、幅 390px で横にはみ出さない（scrollWidth 390）。別名の行の終わりに、足した語が出る
- Zensical については、担当の 0.0.71 のビルド（担当の作業用フォルダの zen-src）を見た。union-find のページに `md-tags`（UF・DSU）が出ており、報告 §6 のとおりである。CI の zensical.yml も 0.0.71 で、担当のビルドのログは「No issues found」

## 7. ほかの検査

- `npx textlint`（直した 38 ページ）：エラーは 0。警告は 662 件で、直す前の写しと同じである（行番号のずれを除いて、規則と文が一致する）
- `tools/check_search.mjs` は、報告と使い方のとおりに動いた
  - 終了コードは、合格 0・不合格 1（before）・読めない 2（`--site` の誤り、知らない引数）
  - `--base`（http）と `--site` は同じ結果になる。`--compare`・`--within`・`--json` も使える
- `tools/check_pages.py` の冒頭の説明と、schema の説明は、実際の検査と合っている

## 直しが要る点

なし。

## 任意の改善（直さなくても合格）

1. **tools/check_pages.py 1542 行・1559 行**：`tags` が配列でないとき（例：`tags: ビット`）に、文字列を 1 字ずつ回してしまう。schema のエラーのほかに、「題名か別名に「ッ」を含むが tags にない」のような誤った警告が数百件出る。写しで `tags: Mo` にすると 451 件出た。
   - 直し方の案：両方の関数で、`p.get("tags")` が list のときだけ回す
   - 既存の aliases の検査も同じ書き方なので、必須ではない
2. **schema/page.schema.json 51 行**：search の説明は「同じ語を題名に持つページの族で元のページ（セグメント木・Union-Find など）を上に出すときだけ使い」と書く。実際の使い方とは少し違う。
   - fenwick-tree（BIT と bitset・bitDP）と lis（LIS と linked-list）は、前方一致で当たる別の語に勝つための boost である
   - 直し方の案：「同じ語（前方一致で当たる語を含む）を題名に持つページの族で」とすると、使い方と合う

## メインに判断してほしい点（担当の報告 §9 に足す材料）

1. **「ビット」の tags（§5.3）**
   - 残す場合：ビット DP は 101 位 → 2 位になる。代わりに、「ビット」と別の手法の名前を並べた検索では、その手法のページが 9 位より下に落ちる
   - 外す場合：完了の条件のうち 2 語（ビット DP・ビットDP）を満たさない
   - tags の重みを下げても、ほとんど直らない
2. **用語の索引を外したこと（§5.5）**：自分の題名・別名でも出なくなる。boost を下げる中間の案は効かないので、外すか残すかの二択である
3. **「全方位」の tags（§5.4）**：担当の報告のとおりである。全期待値・全期待値の公式で、expected-value-dp が 2 位に下がる

## 範囲外の気づき（この担当の直しではない）

- **docs/guide/term-index.md 67 行**の「別名にだけあって本文に出てこない語は、検索では見つからない」は正しくない（直す前からある本文で、作業ツリーでは ui の担当が本文を直している）
  - 別名は必ず冒頭の別名の行に出る（check_pages の検査）。その行は検索の索引に入る。今回足した「にぶたん」「バイナリサーチ」などは、別名の行だけで 1 位に出る
  - 同じ段落の「ひらがなの専門語（いもす法など）」の例も、#52 の後はいもすが 1 位なので当たらなくなった
  - メインがまとめるときに、言い回しを直すとよい
