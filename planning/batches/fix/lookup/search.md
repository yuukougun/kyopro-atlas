# search の報告（グループ lookup・Issue #52）

- 担当の Issue：#52（サイト内検索で、略称や題名から目的のページが上位に出るようにする）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/lookup（ブランチ feat/lookup）。git は読むだけで、commit などはしていない。同じ作業ツリーでほかの担当が `mkdocs.yml`・`overrides/`・`tools/gen_site.py`・`docs/guide/term-index.md` の本文などを直しているので、それらには触れていない
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/lookup/search（ビルドしたサイト・試算のスクリプト・結果の JSON・画面写真）
- 直したファイル（作業ツリーからの相対パス）
  - ページの front matter（aliases・tags・search.boost）と本文の別名の行：下の §3 の 38 ページ（§3.1〜§3.3 の表のページ）
  - `docs/guide/term-index.md`：front matter に `search: {exclude: true}` の 1 行だけ（本文と `updated` はほかの担当の変更）
  - `schema/page.schema.json`：`tags` を足し、`search` の説明を足した
  - `tools/check_pages.py`：tags と search.boost の検査（`check_search_meta`・`check_tag_groups`）と冒頭の説明
  - `tools/check_search.mjs`（新規）：検索の上位を確かめるスクリプト
- front matter：別名の行（本文）を変えた 26 ページの `updated` を 2026-10-29 にした（もとから 2026-10-29 のページもある）。tags・search だけを足した 12 ページは front matter だけの変更なので `updated` を変えていない（手引き §2.1）。stage は変えていない

## まとめ

| Issue | 状態 | 一言 |
| --- | --- | --- |
| #52 | 完了（提案あり） | 19 語すべてで目的のページが 3 位以内（14 語が 1 位）。用語集の略称・直す表記から別名を 33 語足し、検索語 8 つを tags（14 ページ）、族の元のページなど 7 つに search.boost、用語の索引を検索から外した。索引は 17,591,802 → 17,349,657 バイト（測り直した値は §4.4）。一覧（lists/）を外すのは gen_site.py の提案。確かめる道具 `tools/check_search.mjs` を足した |

## 1. Material for MkDocs 9.7.7 の検索で効くもの（確かめたこと）

`.venv` の mkdocs-material 9.7.7 のコード（`material/plugins/search/plugin.py`）と、検索の worker（`search.2c215733.min.js`。source map に入っている TypeScript）を読んで確かめた。

- **索引の作り方（Python 側）**：ページの HTML を見出し（h1〜h6 で id のあるもの）ごとの節に分け、節ごとに 1 項目（location・title・text）を作る。本文に h1 を書かないので、ページの先頭の項目の title は front matter の `title`、ほかの項目の title は各見出しの文字である
  - front matter の `search: {exclude: true}`：ページを丸ごと索引に入れない
  - front matter の `search: {boost: N}`：ページの**全部の節**の項目に boost を付ける
  - front matter の `tags`（リストのとき）：ページの全部の節の項目に tags を付ける。tags プラグインは使っていないので、ページの上には出ない（`partials/tags.html` は tags プラグインが作る変数があるときだけ描く。ビルドした union-find のページに `md-tag` がないことを確かめた）。**検索の結果には印（`md-tag`）として出る**（§3.2 の画面写真）
  - 重み（fields）の既定：title 1000、text 1、tags 1,000,000（`on_config`）。mkdocs.yml の `plugins.search.fields` で変えられる
  - 索引は `json.dumps` の既定（ensure_ascii）で書くので、日本語は 1 字 6 バイト（`\uXXXX`）になる
- **検索（worker）**：lunr.js の BM25 で、`b(0)`（本文の長さで割らない）。項目の boost は、その項目の全部のフィールドの点に掛かる。検索語の後ろに `*` を付けて前方一致で引く（「BIT」は「bit*」で、bitset・bitdp・bit_width にも当たる）。lunr の点の後で、ページの先頭の項目には (1 + (1 + 当たった語の割合)²)、節の項目には (1 + 割合²) を掛け、ページごとにまとめて、いちばん点の高い項目の順にページを並べる。表示はこの順の 1 ページ 1 件である
- **日本語の扱い**：mkdocs.yml の separator で区切った後、索引の側だけ、カナ・かな・漢字の塊を TinySegmenter で分ける。検索語の漢字の続きは、索引にある語で前から区切り直す（`segment()`）が、**続きの最後の 1 字が必ず落ちる**（`for (let j = i + 1; j < query.length; j++)` で最後の字を含む切れ目を見ない）。「累積和」は「累積*」、「区間篩」は「区間*」、2 字の語（「区間」「一覧」「全体」）は 1 字目だけ（「区*」）で引かれる。1 字の漢字はそのまま
- **別名（aliases）**は本文の別名の行（text、重み 1）に入るだけで、題名（1000）に語を持つほかのページにはまず勝てない（Issue の指摘のとおり）

検索の結果を確かめる道具は、この worker を node の vm でそのまま動かす（§3.6）。ヘッドレスの Chrome で検索欄に語を入れた結果（調査の a7 の search.mjs を手元の http に向けたもの）と、直す前のビルドで 45 語の上位 6 件と件数が完全に一致した（作業用フォルダの chrome-before.txt と node-before.txt）。

## 2. 19 語が上に出なかった理由

| 理由 | 語 |
| --- | --- |
| 同じ語を題名に持つ族の中の僅差（0.01〜0.06%）や、題名の珍しい語（「木上」など）が勝つ | Union-Find・いもす・最小全域木・セグ木・累積和（題名「累積和」は 1 語、「2 次元累積和」は「累積」「和」の 2 語に分かれ、珍しい「累積」の方が点が高い） |
| 前方一致で、ほかのページの題名の珍しい語が勝つ | BIT（bitset・bitDP・bit_width）、Mo（典型90 の「Get More Money」・Monge）、LIS（「linked-list,」。ASCII のコンマが区切りにない） |
| 別名が本文にしかなく、ほかのページの題名（見出し）に同じ語がある | UF・DSU（cpp の節の題名の dsu・DSU on Tree）・CHT（凸包・DP の高速化の節の題名）・フェニック木（「木」が題名に当たる）・ビット DP（「ビット」「DP」が題名に当たる） |
| 別名がどのページにもない（用語集だけに当たる） | 01BFS・にぶたん・グランディ |
| TinySegmenter の分け方の食い違い | 全方位木 DP（題名は「全方」「位木」に分かれ、検索語は索引にある「全方位」で区切られて「全方位*」になる） |

## 3. 直したこと

### 3.1 別名を足した（33 語・26 ページ）

用語集の略称の項（`guide/glossary#abbreviations`）と、表記の正規形と別名の対応表（`#canonical-forms`）の「別の書き方」「直す表記」のうち、検索に打たれそうな語（略称・カタカナ読み・よくある書き方）を、各ページの aliases と別名の行の末尾に足した。送り仮名・中黒だけの揺れ（繰返し二乗法・ワーシャル・フロイド法など）と、ページのない語（最短経路・0-origin など）は足していない。表のほかの語はもとから別名にある。

| ページ | 足した別名 |
| --- | --- |
| basics/binary-search | にぶたん・バイナリサーチ・2 分探索 |
| comb/grundy-number | グランディ数 |
| graph/zero-one-bfs | 01BFS |
| dp/rerooting | 全方位 |
| dp/bit-dp | bit DP |
| ds/union-find | ユニオンファインド |
| basics/ternary-search | 3 分探索 |
| basics/two-pointers | 尺とり法・シャクトリ法 |
| dp/dp-basics | もらう DP |
| graph/warshall-floyd | フロイドワーシャル法 |
| graph/bipartite-graph | 2 部グラフ・二分グラフ |
| graph/minimum-spanning-tree | スパニングツリー |
| graph/min-cost-flow | 最小費用フロー |
| tree/lca | 最低共通祖先 |
| ds/segment-tree | セグメントツリー・セグツリー |
| ds/priority-queue | プライオリティキュー・優先順位付きキュー |
| ds/stack-techniques | デック |
| misc/bitset-speedup | ビットセット |
| math/sieve-eratosthenes | エラトステネスのふるい |
| math/fps-basics | 形式的べき級数 |
| comb/inclusion-exclusion | 包含除外原理・包除の原理 |
| string/z-algorithm | Z アルゴリズム |
| string/suffix-array | サフィックスアレイ |
| string/palindrome | マナカー |
| string/aho-corasick | エイホコラシック法 |
| guide/library-design | ライブラリチェッカー |

足した 33 語のうち 26 語は目的のページが 3 位以内（20 語が 1 位）。数字や漢字の 1 字目で引かれる 2 分探索（43 位）・3 分探索（22 位）・2 部グラフ（21 位）・最小費用フロー（11 位）・最低共通祖先（6 位）・包含除外原理（4 位）・もらう DP（4 位）は上に出ないが、用語の索引に載る（gen_site のあと）ので残した。直す前は「ユニオンファインド」「バイナリサーチ」「セグメントツリー」「プライオリティキュー」「ビットセット」「サフィックスアレイ」「マナカー」「スパニングツリー」は用語集にしか当たらなかった。

### 3.2 tags（検索語）を足した（14 ページ）

aliases（本文の重み）では、題名や見出しに同じ語を持つページに勝てない語だけを、front matter の `tags` にした。Material の search プラグインが読む front matter の設定で、プラグインは増やしていない。

| ページ | tags | 直した語 |
| --- | --- | --- |
| ds/union-find | UF・DSU | UF 9 位 → 1 位、DSU 5 位 → 1 位 |
| ds/fenwick-tree | フェニック | フェニック木 114 位 → 1 位 |
| dp/cht | CHT | CHT 3 位 → 1 位 |
| ds/mo-algorithm | Mo | Mo 3 位 → 1 位 |
| dp/rerooting | 全方位 | 全方位木 DP・全方位木DP 15 位 → 1 位 |
| comb/grundy-number | グランディ | グランディ数 33 位 → 1 位 |
| dp/bit-dp と、題名か別名に「ビット」を含む 7 ページ（basics/bit-full-search・basics/bit-operations・basics/bitwise-independence・cpp/cpp-math-functions・ds/binary-trie・misc/bitset-speedup・patterns/xor） | ビット | ビット DP・ビットDP 101 位 → 2 位 |

tags は題名の 1000 倍の重みなので、tags の語の前方一致に当たる検索では、tags のあるページがほかのどのページより上に来る。そのため次の規則で選んだ（schema の説明に書き、check_pages で検査する）。

- 題名か aliases に含まれる語だけを書く（tags の語は別名の行に必ず出る）
- 木・DP・Tree のように多くの題名に出る語は書かない（「フェニック木」でなく「フェニック」。「ビット DP」は「dp」がほかの DP の題名をすべて押しのけるので書かない）
- 漢字で始まる語はなるべく避ける。2 字の漢字の語は 1 字目だけで引かれる（§1）ので、「全方位」は「全体の…」「全クエリ…」の検索にも当たる。全方位木 DP は題名の分かれ方のせいでほかに直す方法がないので、例外として残した（下の 1 位でなくなった語を参照）
- 題名か別名の一部の語（ビット・フェニック・グランディ）は、その語を題名か別名に含むページのすべてに付ける。片方だけに付けると、もう片方の別名の検索で順位を奪う（ビットを bitDP だけに付けると、ビット全探索・ビット Trie・「数・ビット・乱数の関数」で 1 位を奪った）。付けたページの間の順位は、tags がないときと同じになる
- 別名そのもの（UF・DSU・CHT・Mo・全方位）は、そのページだけに付けてよい。ほかのページの別名の「ロールバック UF」「重み付き UF」「DSU on Tree」は Union-Find が 1 位、それぞれのページが 2 位になる
- tags を付けたページに search.boost を付けると、tags の点（題名の 1000 倍）にも掛かり、tags の語を含む検索のすべてで 1 位になる。同じ tags を持つページの族には boost を付けない（Union-Find の boost 1.05 は、UF・DSU を族のほかのページに付けていないので問題にならない）

検索の結果の見え方（作業用フォルダの shot-uf.png・shot-bitdp.png）：結果の 1 件目の下に「UF」「DSU」の印が出て、当たった語に色が付く。同じページのほかの節は「このページ内にあと N 件」にたたまれる。

### 3.3 search.boost を足した（7 ページ）

同じ語を題名に持つページの族で、元のページを上に出すためだけに使った。boost はページの全部の節の点に掛かるので、族のほかのページの別名の検索では 1 位を譲ることがある（§4.3）。値は、目的の順位にすぐ下のページと 5〜13% の差が付く最小に近いものにした（僅差のままだと、ほかのページの本文を少し直しただけで順位が入れ替わる）。

| ページ | boost | 直した語 | すぐ下のページとの差（直した後） |
| --- | --- | --- | --- |
| ds/segment-tree | 1.1 | セグ木 5 位 → 2 位、題名「セグメント木」7 位 → 2 位 | 6%（1 位の「セグメント木上の二分探索」は題名の珍しい語「木上」で 1.66 倍。1 位にするには 1.83 が要り、族のほかのページの別名をいくつも奪う） |
| ds/fenwick-tree | 1.8 | BIT 11 位 → 3 位 | 13%（1.6 では 4 位の cpp-math-functions と 0.3% 差だった。上の bitset・bitDP は題名の珍しい語 bitset・bitdp に前方一致で当たる。1 位にするには 2.02 が要る） |
| dp/lis | 1.1 | LIS 2 位 → 2 位（3 位・4 位と 0.06%・0.13% 差だったのを 10% 差に） | 10%（1 位は「linked-list,」の題名。ASCII のコンマが区切りにないため） |
| ds/union-find | 1.05 | Union-Find 6 位 → 1 位 | 5% |
| basics/imos | 1.05 | いもす 2 位 → 1 位 | 5% |
| basics/prefix-sum | 1.3 | 累積和 3 位 → 1 位 | 5% |
| graph/minimum-spanning-tree | 1.05 | 最小全域木 2 位 → 1 位 | 5% |

fenwick-tree を 1.6 → 1.8、lis に 1.1 を足したときの、題名・別名の全部の検索への影響は、別名の 1 位の出入りが 1 対 1（upper_bound が二分探索から LIS のページへ）だけだった。

### 3.4 用語の索引を検索から外した

`docs/guide/term-index.md` の front matter に `search: {exclude: true}` を足した（§5）。

### 3.5 schema と check_pages

- `schema/page.schema.json`：`tags`（文字列の配列、重複なし）を足し、§3.2 の規則と Zensical での扱いを説明に書いた。`search` の説明に boost・exclude の使い方を足した
- `tools/check_pages.py`
  - エラー：tags の語が題名にも aliases にも含まれない（`tags が題名・別名にない`）、search.boost が 0 以下
  - 警告：search.boost が 2 より大きい、題名か別名の一部の語の tags（ビットなど）を、その語を題名か別名に含むほかのページが持たない（`tags の語を含むのに tags にない`。別名そのものの tags は見ない）
  - 作業用フォルダの写し（neg/）に、題名にない tags・boost 0・boost 3・xor の tags を外したものを作り、エラー 2 件・警告 4 件（xor の 1 件と、凸包の 2 件・boost 3 の 1 件）が出ることを確かめた

### 3.6 tools/check_search.mjs（新規）

ビルドしたサイトの `search/search_index.json` と Material の検索の worker（言語のファイルも）を http か フォルダから読み、node の vm の中でそのまま動かして、検索欄に語を入れたときと同じページの並びを出す。node 20 以上だけで動く（ブラウザ・npm のパッケージは要らない）。

```sh
uv run mkdocs build -q -d <作業用フォルダ>/site
python3 -m http.server -d <作業用フォルダ>/site 8000 &
node tools/check_search.mjs                         # 代表の 65 語（#52 の 19 語を含む）で目的のページが 3 位以内か。入らなければ終了コード 1
node tools/check_search.mjs --sweep -v              # 全ページの題名と別名でも引き、3 位以内にないものを出す（数分）
node tools/check_search.mjs --json after.json --compare before.json   # 直す前の結果と比べる
node tools/check_search.mjs --site site セグ木 'BIT=fenwick-tree'      # http なしで、語ごとの上位
```

代表の語は、#52 の 19 語・調査で 1 位だった 26 語・§3.1 で足した別名のうち上位に出る 20 語。索引の大きさ（バイトと gzip の目安）も出す。

## 4. 結果（直す前と後）

直す前は HEAD（af7ee6c）を `git archive` で作業用フォルダに写してビルドしたもの、直した後は、その写しにこの担当が直した 39 のページ（§3 の 38 ページと用語の索引）だけを重ねてビルドしたもの（ほかの担当の変更を入れない）。作業ツリーをそのままビルドしたもの（ほかの担当の変更を含む。索引 17,358,107 バイト）でも、代表の 65 語がすべて合格した。どれも `mkdocs build --strict` が通った。結果は作業用フォルダの before.json・after2.json（`--json`）と after2-report.txt（`--sweep -v --compare` の出力）にある。

### 4.1 #52 の 19 語

| 語 | 目的のページ | 直す前 | 直した後 | 直した後の上位 3 件 |
| --- | --- | --- | --- | --- |
| BIT | fenwick-tree | 11 位 | 3 位 | bitset-speedup・bit-dp・fenwick-tree |
| UF | union-find | 9 位 | 1 位 | |
| 全方位木DP | rerooting | 15 位 | 1 位 | |
| 全方位木 DP | rerooting | 15 位 | 1 位 | |
| ビットDP | bit-dp | 101 位 | 2 位 | bitset-speedup・bit-dp・cpp-math-functions |
| ビット DP | bit-dp | 101 位 | 2 位 | 同上 |
| フェニック木 | fenwick-tree | 114 位 | 1 位 | |
| 01BFS | zero-one-bfs | なし | 1 位 | |
| にぶたん | binary-search | なし | 1 位 | |
| グランディ | grundy-number | なし | 1 位 | |
| セグ木 | segment-tree | 5 位 | 2 位 | segment-tree-binary-search・segment-tree・segment-tree-on-values |
| Union-Find | union-find | 6 位 | 1 位 | |
| DSU | union-find | 5 位 | 1 位 | |
| Mo | mo-algorithm | 3 位 | 1 位 | |
| CHT | cht | 3 位 | 1 位 | |
| 累積和 | prefix-sum | 3 位 | 1 位 | |
| 最小全域木 | minimum-spanning-tree | 2 位 | 1 位 | |
| LIS | lis | 2 位 | 2 位 | operation-sequence・lis・subsequence-and-substring |
| いもす | imos | 2 位 | 1 位 | |

ビット DP は、ビットの族の中で bitset-speedup（別名に「ビットセット」「ビット並列」があり、本文に DP もある）と 0.0002% 差の 2 位で、3 位とは 54% 離れている。2 位・3 位の語（BIT・ビット DP・セグ木・LIS）は、どれも 3 位以内に 6% 以上の差で入っている（§3.3）。

### 4.2 代表の語（65 語）

直す前 38 / 65 → 直した後 65 / 65 が 3 位以内。調査で 1 位だった 26 語はすべて 1 位のまま。

### 4.3 全ページの題名と別名（--sweep）

| | 直す前 | 直した後 |
| --- | --- | --- |
| 題名 | 355 語、1 位 318、3 位以内 344 | 354 語（用語の索引を外した）、1 位 321、3 位以内 346 |
| 別名 | 2236 語、1 位 972、3 位以内 1391 | 2264 語（足した 33 語を含み、用語の索引の 5 語を除く）、1 位 985、3 位以内 1422 |

両方にある語で比べると、題名は 1 位になった 5（いもす法・累積和・全方位木 DP・Union-Find・最小全域木）・1 位でなくなった 1、3 位以内に入った 3（セグメント木 7 位 → 2 位など）・落ちた 0。別名は 1 位になった 16・1 位でなくなった 20、3 位以内に入った 14・落ちた 6。1 位でなくなった語はすべて 2 位で、理由は次のとおり。

- tags の UF・DSU（Union-Find が 1 位になる）：ロールバック UF・重み付き UF・DSU on Tree
- tags の全方位（「全…」の 2 字の語が「全*」で引かれる）：題名「全体への操作を変数で持つ」、別名「全期待値の公式」。3 位 → 4 位：全確率の公式・全クエリの二分探索を同時に進める
- boost：fenwick-tree 1.8（double・balanced binary search tree・DFS tree・Virtual Tree。本文や題名の「Tree」などで並んでいたもの）、union-find 1.05（逆順 Union-Find・Union-Find の併合の過程を表す木。3 位 → 4 位：代表元・自己ループ）、minimum-spanning-tree 1.05（最小有向全域木・directed MST）、prefix-sum 1.3（二次元累積和。正規形の「2 次元累積和」は 1 位のまま）、lis 1.1（upper_bound）
- 用語の索引を外したことで idf が変わり、0.1% ほどの僅差が入れ替わったもの（tags と boost なしで用語の索引だけを外した試算でも同じ語が入れ替わった）：セグ木 DP・環状 DP・heap・erasable heap・連結して辞書順最小・木の性質。3 位 → 4 位：range-based for、3 位 → 6 位：多項式の逆元

両方にある別名 2231 語では、1 位は 969 → 965 と少し減るが、3 位以内は 1388 → 1396 に増えた（1 位になったのは UF・DSU・フェニック木・CHT・Mo・MST・ビット並列など 16 語）。題名 354 語では 1 位 317 → 321、3 位以内 343 → 346。1 位を譲った語はすべて 2 位なので、検索の結果の 1 画面目からは消えていない。

### 4.4 索引の大きさ

| | search_index.json | gzip（-6） | 項目 |
| --- | --- | --- | --- |
| 直す前 | 17,591,802 バイト | 3,488,882 | 5695 |
| 直した後 | 17,349,657 バイト（-1.4%） | 3,449,181 | 5652 |
| ＋一覧（kind-*・level-*）を外す（提案 1） | 16,761,773 バイト（-4.7%） | 3,333,030（-4.5%） | 5382 |
| ＋索引を UTF-8 で書く（提案 3） | 10,082,427 バイト（-42.7%） | 2,872,776（-17.7%） | 5382 |

用語の索引を外して約 25 万バイト減り、tags で約 6,500 バイト増えた。大半は各ページの本文（コードを含む）で、ページを外すだけでは大きくは減らない。GitHub Pages は gzip で配るので、回線で運ぶのは約 3.4 MB である。gzip の値は Python の gzip（-6）で測った（check_search.mjs が出す gzip の目安は node の zlib なので 2% ほど小さく出る）。提案 1・3 の行は、直した後の索引から項目を除き、プラグインと同じ形で書き直して測った試算である。

## 5. 一覧（lists/）と用語の索引を検索から外すか

直す前の全ページの題名・別名の検索（2591 語）で数えた。

| | 上位 3 件に出た語 | そのうち目的のページより上 | 目的のページが 3 位以内にないとき、代わりに上位 3 件に出た語 | 大きさ |
| --- | --- | --- | --- | --- |
| 一覧（lists/kind-*・level-*） | 71 | 37 | 32 | 約 59 万バイト（3.4%） |
| 用語の索引 | 256 | 4 | 3 | 約 25 万バイト（1.4%） |

- **一覧（lists/）は外す**（提案 1）。目的のページより上に出ることが多く（「ビット演算」は一覧が 1 位で、bit 演算のページは 3 位）、要約の 1 文はページ自身にもある。一覧はナビの「一覧」と分野の入口・ページの上の帯から 1 クリックで開ける。ただし一覧の入口（`lists/index.md`、「一覧」）は外さない。「一覧」「種類別」と打って入口を探す使い方が残るため。lists/ の front matter は gen_site.py が作るので、この担当は直していない
- **用語の索引は外した**。別名の検索の 1 割で上位 3 件の 1 枠を使うのに、目的のページが見つからないときの代わりになったのは 3 語だけだった（用語の索引の項目は節なので、別名の行を持つページ自身より下に来る）。外すと「用語の索引」「索引」と打っても用語の索引のページが出なくなり、用語集（1 位。末尾から用語の索引へのリンクがある）と問題番号の索引が出る。用語の索引はホームの「解けなかった問題から引く」・使い方・ナビの「辞書として引く」から開け、ページ自体が「サイト内検索の結果に左右されない入口」（要点）なので、検索から外しても役目は変わらない。戻すときは front matter の 1 行を消す
- docs/index/（Claude 用の詳細索引）はもとから外してある

## 6. Zensical での扱い

[Zensical の検索の設定](https://zensical.org/docs/setup/search/)と[front matter](https://zensical.org/docs/authoring/frontmatter/)の説明（zensical.org。`tools/check_noai.py --robots` で noai・noimageai の指定がなく robots.txt もないことを確かめた）、パッケージの README（PyPI の 0.0.71 の METADATA。検索の記述はない）と `zensical/config.py`、uv のキャッシュにある 0.0.71 で作業用フォルダの写しをビルドした結果（`zen-src/`）で確かめた。

- `search.exclude`：効く（ページを索引から外す。写しで lists/kind-bit の項目が 0 になった）。`data-search-exclude` で節やブロックも外せる
- `search.boost`：**効かない**。説明になく、0.0.71 の本体に boost の文字列がなく、写しで union-find に付けた boost が索引（`search.json`）に出なかった
- `tags`：索引の項目に入るが、検索の worker では**絞り込みの印**として使い、点には入れない（重みは title 3・text 1・path 2）。さらに、tags プラグインを設定していなくても**ページの下に印（`md-tags`）として出る**（写しの union-find のページに「UF」「DSU」が出た）。front matter の `hide: [tags]` で隠せる（Zensical の `partials/tags.html`）
- mkdocs.yml の `plugins.search` は `separator` だけを読み、`lang`・`pipeline`・`fields` は読み捨てる（`_PLUGIN_UNSUPPORTED_OPTIONS`）。日本語は TinySegmenter でなく、ブラウザの `Intl.Segmenter`（言語は `theme.language`）で語に分ける（0.0.71 の worker）ので、§1 の分け方の食い違いや最後の 1 字が落ちる問題は起きない見込み
- 重みが title 3：text 1 なので、Zensical では別名の行（本文）が題名に対して今より強く効く。移るときは代表の語の順位を測り直す（check_search.mjs は Material の worker 専用なので、Zensical の worker 用に書き直しが要る）
- まとめ：Zensical に移ると、boost と tags の重みは失われ、tags は各ページの下の印になる。移るときに tags を消すか、14 ページに `hide: [tags]` を足す

## 7. 検査

- `python3 tools/check_pages.py --page <直した 39 ページ> -v`：エラー 0・警告 0。全ページ（`python3 tools/check_pages.py`）もエラー 0・警告 0
- `python3 -m unittest discover -s tests/tools`：70 件 OK（skip 2）
- `npx textlint <直した 38 ページ>`：エラー 0。警告 662 件はすべて前からのもの（37 ページは直す前の写しの同じファイルでも 643 件、lis は front matter だけの変更で 19 件）。足した別名は textlint-disable の中。用語の索引は本文がほかの担当の変更なので数えていない
- `mkdocs build --strict`（作業用フォルダへ。直した後の写しと、作業ツリーそのもの）：どちらも警告なしで通った
- `python3 tools/gen_site.py --check`：生成物が 14 ファイル古い（別名を足したので用語の索引・docs/index/・llms.txt・graph.json が変わる。ほかの担当の変更の分も含む）。メインが gen_site を流す
- `node tools/check_search.mjs`：直す前 38 / 65（#52 の語 6 / 19）→ 直した後 65 / 65（19 / 19）。作業ツリーのビルド（`--site`）でも 65 / 65。`--sweep` は直す前と後の両方で流した（§4.3）
- tags の印の見え方：直した後のビルドを Chrome で開き、「UF」（幅 1280）と「ビット DP」（幅 390）の検索の結果を撮った（shot-uf.png・shot-bitdp.png）
- check_search.mjs の照合：直す前のビルドで、ヘッドレスの Chrome で検索欄に入れた 45 語の上位 6 件と件数が一致した

## 8. 提案（メインに頼む共有ファイルの変更）

1. **一覧を検索から外す**（`tools/gen_site.py`）：`level_list()`・`kind_list()` の `self.front(...)` に `search_exclude=True` を渡す（`lists/index.md` の `self.front("一覧")` はそのまま）。試験（tests/tools/test_gen_site.py）に「kind-*・level-* の front matter に search.exclude がある」を足す。索引は約 59 万バイト減る
2. **check_search.mjs を手引きと CI に**：`tools/README.md` の表に「`check_search.mjs`｜ビルドしたサイトで、代表の語の検索の上位と索引の大きさを確かめる（node。http か --site）｜なし（--json）」を足す。deploy.yml の `mkdocs build --strict` の後に `node tools/check_search.mjs --site site` を、失敗しても止めない手順（continue-on-error）で足すと、別名や boost の変更で代表の語が落ちたときに気づける
3. **索引を UTF-8 で書く hook**（mkdocs.yml の `hooks:` と hooks/ の小さな Python）：on_post_build で `site/search/search_index.json` を読み、`json.dumps(..., ensure_ascii=False, separators=(",", ":"))` で書き直す。17.3 MB → 10.4 MB、gzip で約 14% 減る。worker は fetch して JSON.parse するので読み方は変わらない（hooks は mkdocs.yml の冒頭の方針で使ってよいもの。Zensical は自分の search.json を UTF-8 で作るので関係しない）
4. **手引き（planning/style-guide.md §2.1）と interfaces.md §2** に tags の規則を書く：「front matter の `tags` は検索語。題名か別名に含まれる語だけを書き、木・DP のように多くの題名に出る語と漢字で始まる語は避ける。題名か別名の一部の語は、その語を題名か別名に含むページのすべてに付ける。別名そのもの（略称）はそのページだけでよい。`search.boost` は族の元のページだけに 2 以下で付け、tags を付けた族には付けない。変えたら `node tools/check_search.mjs` で代表の語を確かめる」
5. **区切り（mkdocs.yml の separator）に ASCII のコンマなどを足す**のは見送った方がよい：``,;!?"'`<>={}|&\`` と `\.(?!\d)` を足して直す前の索引で試算すると、LIS が 1 位になるが（「linked-list,」が消える）、別名の 1 位の出入りは 22 対 26、題名は 2 対 1 でほぼ変わらない。LIS は lis の boost 1.1 で足りている
6. 用語集の略称の項（`guide/glossary#abbreviations`）の「全方位（全方位木 DP）」などの略称は、本文では使わない語なので、別名に足した語（にぶたん・グランディ数・01BFS・ユニオンファインド など）を表に足すかは、用語集の持ち主の判断（今は表にある語だけを別名にした）
7. **（大きな変更。今回は入れていない）別名を題名なみの重みにする**：hook（on_page_markdown）で各ページの aliases を `page.meta["tags"]` に写し、mkdocs.yml の `plugins.search.fields` で tags の重みを 1,000,000 から題名なみに下げる。直す前の索引で試算すると（作業用フォルダの sim.mjs）、別名で引いたときの 1 位は 972 → 1573（tags 500）・1707（tags 1000）語に増えるが、題名で引いたときの 1 位は 318 → 313・293 語に減り、調査で 1 位だった 26 語のうち 3 語が 1 位でなくなる（重みを下げずに全部の別名を tags にすると、題名の 1 位が 191 語まで崩れる）。hook は Zensical では動かないので、Zensical の印の問題（§6）は起きない。代わりに検索の結果に全部の別名が印として並ぶので、kp.css で `.md-search-result .md-tags` を隠すことになる。入れるなら、この担当の tags と boost を外して測り直す

## 9. メインに判断してほしい点

- **tags を使ってよいか**：Material の search プラグインが読む front matter で、プラグインは増やしていない。代わりに Zensical では印としてページの下に出る（§6）。使わないと、UF・DSU・フェニック木・ビット DP・ビットDP の 5 語は 3 位以内に入らない（目的のページは本文でしか当たらず、題名の 1000 倍の差を boost では越えられない）。全方位木 DP・全方位木DP は boost 1.3 で 2 位になるが、3 位と 0.25% 差で崩れやすい。戻すときは 14 ページの `tags:` の行を消し、schema・check_pages の tags の部分を外す
- **全方位の tags**：「全体の…」「全クエリ…」のように「全」で始まる 2 字の語を含む検索で、全方位木 DP が 1 位に来る。題名「全体への操作を変数で持つ」が 2 位になる。外すと全方位木 DP は 15 位に戻る（boost 1.3 でも 2 位だが、3 位と 0.25% 差で崩れやすい）
- **用語の索引を検索から外したこと**（§5）。外さない方がよければ front matter の 1 行を消す
