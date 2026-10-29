# verify-ui の報告（グループ lookup、2026-10-29）

ui の直し（#57・#59・#60）を、書いた担当とは別の目で確かめた。作業ツリーは /home/yuuki/projects/kyopro2/kyopro-atlas-wt/lookup（feat/lookup）。ファイルは直していない（この報告だけを書いた）。git は読むだけ。

**注意（同じ作業ツリーの別の担当）**：検証の途中（11:00 ごろ）から、別の担当（#52 の search と見られる）が同じ作業ツリーで docs の別名・`schema/page.schema.json`・`tools/check_pages.py` を書き換え、`tools/check_search.mjs` を足している。ビルドと検査は 10:48 の状態で行った。この時点の変更は ui の分だけだった（`git status` と更新時刻で確かめた）。ui が直したファイルは、どれも 10:37 より後に変わっていない。11:10 に `gen_site.py --check` を流し直すと「生成物が古い：14 ファイル」になるが、原因は後から入った別名の変更で、ui の変更ではない。2 つの担当の変更をまとめた後に、メインが gen_site を流し直す必要がある。

## 結論

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #57 似た手法の使い分けへの戻り道 | 合格。完了の条件は 2 つとも満たす | 1（軽い。コードのコメントの位置） |
| #59 知識マップの操作 | 合格。完了の条件は 3 つとも満たす | 0 |
| #60 逆引き辞典と用語の索引の絞り込み | 直しが要る。完了の条件（390px・「最大公約数」「K 番目」）は満たす | 1（言い換えが活用形の語で効かず、件数の行が誤った案内を出す） |

## #57 似た手法の使い分けへの戻り道

### 完了の条件 1：表に載る手法のページすべてに、該当する節へのリンクがあるか

ビルドした HTML から自前のスクリプトで数えた（gen_site の対応を使わず、method-comparison の h2 ごとに表の中の `<a>` を集め、graph.json の url でページに戻した）。

- 表に載るのは 105 ページ（ページと節の組 112）。欠けは glossary の 1 組だけ。glossary は「比べる観点」の表にある横断ページで、手法のページではないので、除いてよい（担当の判断どおり）。手法のページ 104 は、112 組のうち 111 組のすべてで、ページ下部の欄に該当する節へのリンクがある。
- 表の外（段落・箇条書き）のリンクも数えた。欠けは「比べる観点」（計算量の見積もり）・横断ページ（glossary・stress-testing）・はじめに（how-to-use。参考の節）だけで、どれも設計どおり除いたもの。
- 欄が出るページは 120（1 節 108・2 節 11・3 節 1）。欄のリンク先はどれも method-comparison に実在する h2 である。対応のない行き先はない。

### 完了の条件 2：Union-Find の拡張を問われ方から選べる表

- method-comparison#connectivity の表は 9 行で、Issue に挙げた 9 項目（成分の情報・差の制約・2 色・削除だけ・追加と削除が混ざる・直前の取り消し・過去の時刻の連結・次の空き・しきい値ごと）にそろう。
- 13 のリンクの anchor は、どれも行き先のページに実在する見出しである（union-find-applications#data-on-root・#next-pointer・#multiple-uf、weighted-union-find#consistency・#generalization、bipartite-graph#union-find、union-find-connectivity#reverse-deletion・#threshold、offline-dynamic-connectivity#time-segment-tree、rollback-union-find#with-dfs、partially-persistent-union-find#what-it-does・#alternatives、merge-process-tree#bottleneck）。
- 各行の中身を行き先の節の本文と照らした。
  - 差の制約の式 $x_v - x_u = w$ と「各頂点が親との差を持つ」は weighted-union-find#consistency と同じ向きである。
  - 2 色は、頂点を 2 倍にする方法と XOR の重み付きの 2 通りがある（bipartite-graph#union-find・weighted-union-find#generalization）。
  - ロールバックは経路圧縮をしない（rollback-union-find#no-path-compression）。
  - 部分永続は先読みなしに答え、先読みできれば並列二分探索で代わりになる（#alternatives）。
  - しきい値の順は先にクエリを読む方法で、先読みできなければ併合過程の木の LCA で答える（merge-process-tree#bottleneck は「質問を先読みしなくても」と書く）。
  - 表の後の「しきい値ごとに Union-Find を持つ」は union-find-applications#multiple-uf と合う。
  - 事実の誤りは見つからなかった。
- 390px で表は横にはみ出さず（scrollWidth 390）、KaTeX のエラーは 0。

### 壊れていないか

- ビルドの前（HEAD を `git archive` で取り出してビルド）と後で、全 422 ページの下部の欄を比べた。前提・次に読む・知識マップのリンクに差はない。関連の差は 6 ページ（dijkstra・bellman-ford・warshall-floyd・zero-one-bfs・z-algorithm・rolling-hash）で、method-comparison のリンクが外れただけ（担当の報告どおり）。
- 本文（article）が変わったのは想定どおりの 21 ページだけだった：直した 5 ページ、詳細索引 15、how-to-use の版の行。ほかのページの違いは、末尾の `filter.js` の script の 1 行だけ。
- 見た目は、graph/dijkstra（1280px）・dp/dp-dag（1280px ダーク）・ds/union-find（390px ダーク）で確かめた。欄は「次に読む」と「関連」の間に出て、横のはみ出しはない。

### 直しが要る点

1. **tools/gen_site.py 139〜146 行（軽い）**：もとは `FIELD_COMPARISONS` の直前にあったコメント「# 分野の入口の「使い分け」：guide/method-comparison の節（anchor）。その分野のページへのリンクが多い節を選んだ…」と `FIELD_COMPARISONS` の間に、新しい `COMPARISON_PAGE`・`COMPARISON_SKIP_SECTIONS`・`COMPARISON_SKIP_FIELDS` が挟まった。このためコメントが `COMPARISON_PAGE = "method-comparison"` の説明に読める。
   - 直し方の案：新しい 3 つの定数とそのコメントを、「# 分野の入口の「使い分け」」のコメントより前へ移し、コメントを `FIELD_COMPARISONS` の直前に戻す。
   - ついでの案（任意）：752 行 `self.by_id.get("method-comparison")` も `COMPARISON_PAGE` にそろえる。

### メインへの申し送り（担当の直しではない）

- 担当の提案 1（how-to-use #page-anatomy の「前提・次に読む・関連の 3 つの欄」）は反映が要る。今のままでは、120 ページに出る「似た手法の使い分け」の欄が、ページの構成の説明から抜ける。
- claude/explain.md 31 行は、詳細索引の中身を「別名・サイン・前提・節の anchor」と書く。詳細索引に「使い分け」の行が増えたので、解説役に使わせるなら 1 語足すとよい（任意）。

## #59 知識マップの操作

### 完了の条件 1：Issue の語で目的のページが選ばれるか

ビルドした地図で `findPages`（「ページ」欄の照合）を呼んで確かめた。欄に値を入れて change を起こす操作でも、同じページが中心になる。

| 語 | 選ばれたページ（2 番目以降はほかの候補） |
| --- | --- |
| セグ木 | segment-tree, dp-segment-tree, segment-tree-graph |
| UF | union-find, union-find-applications, weighted-union-find |
| LIS | lis, linked-list, graph-basics |
| CHT | cht（Convex Hull Trick と Li Chao Tree） |
| 桁DP | digit-dp, digit-dp-advanced |
| Mo | mo-algorithm, parity, dp-mod-state, monge |
| ハッシュ | rolling-hash, hash-safety, hashing-for-sets, tree-isomorphism |

- Issue の語はすべて目的のページになる（前は「該当なし」か、Monge・木の同型判定に飛んでいた）。
- ほかに試した約 75 語も、ほとんど目的のページになった（BIT・遅延セグ木・だいくすとら・ＵＮＩＯＮ－ＦＩＮＤ・DSU・01BFS・全方位木DP・座圧・2SAT・強連結成分分解・Segment Tree・lazy-segment-tree など）。
- 参考（直しは要らない。規則どおりの結果で、別名の付け方の問題。#52 で別名を見直すときの材料）：
  - 「gcd」は cpp-math-functions（別名 gcd に完全一致）が先で、gcd-lcm は 2 番目になる。
  - 「マッチング」は dilworth-path-cover（別名「マッチングの双対」の前方一致）が、bipartite-matching（部分一致）より先に来る。
  - 「mod」は parity（別名「mod 2」）が先で、mod-arithmetic は上位 4 件に入らない。
  - 「セグメントツリー」「ネットワークフロー」「にぶたん」「グランディ」は当たらない。どれも当たるページを示す別名がない。

### 完了の条件 2：390px で点を長押しすると、説明が画面の中に出るか

390×844 でタッチを有効にし、地図の見え方を 5 通りにして点を 1.1 秒長押しした（ライトとダークの両方）。どの場合も、説明は画面の中（ヘッダーの下から 844px まで）に出た。長押しした点は画面に残り、説明に隠れなかった。

| 場面 | 説明の位置（上端〜下端の px） |
| --- | --- |
| 地図が画面いっぱい・下の点 | 70〜284（地図の上の端） |
| 地図が画面いっぱい・上の点 | 403〜641（地図の下の端） |
| 地図の上だけが見える・画面の下の点 | 598〜836（ページを送って見せる） |
| 地図の下だけが見える・画面の上の点 | 56〜294（ページを送って見せる） |
| 地図の下だけが見える・画面の下の点 | 56〜270 |

- 地図の空いた所を押すと閉じる。点を短く押しても固定され、ページは移らない（アドレスは ?field=basics のまま）。
- ダブルタップすると、instant navigation でそのページへ移る。

### 完了の条件 3：1280px で ?focus=lazy-segment-tree の関連の囲みが切れないか

- 倍率は 0.956 になる。関連の囲み（「関連」の文字を含む）は地図 686×628 の中の [262, 243]〜[467, 526] に収まり、6 つの点もすべて入る。画像でも、囲みは選んだページの真下に出て、切れていない（ライトとダーク）。
- related を持つ全 355 ページで焦点の表示を描き直し、選んだページと関連の囲み（中の点を含む）が地図の中に収まるかを、1280px と 390px の両方で確かめた。外れはどちらも 0 だった。

### そのほかの動き

- PC（1280px）の動き：
  - 点に乗せると仮の説明が出て、「点を押すと、この説明を固定する」と添えられる。押すと固定し、別の点に乗せても替わらない。
  - 説明の「この点を中心に表示」で ?focus=dfs になる。Esc で閉じる。
  - 点の上から地図の外へ一気に出ると、仮の説明は消える。点から説明へ 0.4 秒ほどで移れば、説明は消えない。
  - 「ハッシュ」のほかの候補はボタンで 4 件出て、押すとそのページが中心になる。「にぶたん」では当たらないことと、探し方の案内が出る。
- instant navigation：Material は sitemap.xml の URL（https://yuukougun.github.io/kyopro-atlas/…）のホスト名だけを差し替えて照らすので、ポートの違う手元のサーバーでは働かない。そこで、作業用フォルダのビルドのコピーで sitemap.xml の URL を手元のものに書き換えて試した。window に置いた印が残ること（読み込み直していないこと）を確かめた。
  - ds/union-find の「ほか 1 ページは知識マップで見る」から地図が ?focus=union-find で出る。
  - 「桁DP」で digit-dp が中心になる。点のダブルクリックで、そのページへ instant navigation で移る。
  - 戻ると ?focus=digit-dp の地図に戻る。コンソールのエラーはない。

## #60 逆引き辞典と用語の索引の絞り込み

### 完了の条件：390px で開いてすぐ見える位置に欄があり、「最大公約数」「K 番目」で該当する行だけが残るか

390×844（タッチ、ライトとダーク）で確かめた。

| ページ | 欄の上端〜下端（画面の高さ 844） |
| --- | --- |
| 逆引き辞典（言い回しから） | 298〜342px |
| 逆引き辞典（制約・計算量から） | 298〜342px |
| 用語の索引 | 257〜301px |

- 3 ページとも横のはみ出しはない（scrollWidth 390）。
- 照合は filter.js とは別に書いた正規化（NFKC・小文字・カタカナ → ひらがな・区切りの記号を除く）で行い、見えている行と比べた。
  - 「最大公約数」：17 行が残る。17 行とも gcd か最大公約数を含み、含む行で隠れたものは 0 である。件数の行に「言い換え：「最大公約数」を「gcd」に置き換えた形でも探した。」と出る。
  - 「K 番目」：35 行が残る。34 行は「K 番目」をそのまま含む。残る 1 行は「値を追加しながら、上位 K 個の和・ソートしたときの奇数番目の和を答える」で、K と「番目」を別々に含む。上位 K 個の和は K 番目の値と同じ道具（値を添字にする BIT）で解くので、外れとまでは言えない。担当の判断（特別な規則を入れない）でよいと考える。
- そのほか：
  - 「gcd」→ 17 行、「スワップ」→ 20 行。
  - 制約のページで「グリッド」→ 8 行、「10^5」→ 80 行（KaTeX の注釈の文字に当たる）。
  - 用語の索引で「セグ木」→ 59 語、「最大公約数」→ 20 語、「だいくすとら」→ 11 語。
  - どれも、当たる単位と見えている単位が一致した。
- JS を止めると欄は空の div のままで、1,008 行がすべて見える。
- instant navigation（上と同じ方法）：
  - 欄は使い分けのページから移った先でも付き、要点の前に移る。
  - 目次で隠れた節（#by-situation）を押すと、絞り込みが解けて節へ移る。残っている節（#by-phrase）を押すと、?filter=gcd のまま移る。
  - 用語の索引へ移って「dsu」→ 3 語。戻る・進むで ?filter= の絞り込みが元に戻る。
  - コンソールのエラーはない。

### 直しが要る点

1. **overrides/assets/js/filter.js 31・37 行（SYNONYMS）。関係：docs/guide/reverse-index-signs.md 49 行**
   - 何が起きるか：言い換えは、語に含まれる組の語を、文字列のまま置き換えて作る。このため、活用した形で打つと、意味のない形しかできない。
     - 「取り除く」→「削除く」になる。逆引き辞典（言い回しから）で 5 行しか残らず、削除の行は出ない（「削除」なら 36 行）。
     - 「入れ替える」→「swapる」「交換る」になる。2 行しか残らない（「入れ替え」なら 20 行）。
   - それでも件数の行は「言い換え：「取り除」を「削除」に置き換えた形でも探した。」と出す。削除でも探したように読める。
   - reverse-index-signs.md 49 行は「「削除」と「取り除く」のような少数の言い換えは、欄が両方の語で探す」と書く。「取り除く」と打つ人には、この説明が成り立たない。
   - 直し方の案：組に活用形を足す（`["削除", "取り除く", "取り除"]`・`["swap", "スワップ", "入れ替える", "入れ替え", "交換"]`）。
     - メモリの上で試したところ、「取り除く」で「削除」、「入れ替える」で「swap」「交換」も探すようになった。
     - ただし、このままでは件数の行に「「取り除」を「取り除く」」のような置き換えまで並ぶ。そこで `synonyms()` で、語に含まれる組の語が複数あれば、最も長い語だけを置き換える。
     - 別の案：組の語の後ろに、語の終わりまでひらがなだけが続く場合（送り仮名）は、言い換えの語だけの形も足す。
   - どちらにしても、置き換えた形が意味をなさないときは、件数の行に出さない。
   - 直した後に「取り除く」「入れ替える」「削除」「スワップ」の件数を数え直す。

### 推奨（直さなくても完了の条件は満たす）

- reverse-index-signs.md 49 行「それでも同じ意味を別の言葉で書いた行は残るので」：同じ段落で「残る」を「絞り込んで表示に残る」の意味で使っている。そのため、「（表示に）残る」とも読める。「それでも、同じ意味を別の言葉で書いた行は当たらないことがあるので」のようにするとよい。
- 欄の例の語（placeholder「例：最大公約数・K 番目」）は、制約のページでも同じである。制約のページでは「最大公約数」→ 2 行、「K 番目」→ 1 行しか当たらず、本文の案内（「グリッド」「クエリ」「10^5」）と合わない。ページごとに例を変えるとよい（目印の div に data 属性で渡すなど）。

## 検査

| 検査 | 結果 |
| --- | --- |
| `python3 tools/gen_site.py --check` | 10:46 は「生成物は最新」。11:10 は 14 ファイルが古い（後から別の担当が別名を変えたため。上の注意） |
| `python3 tools/check_pages.py`（全ページ） | エラー 0・警告 0（10:46） |
| `check_pages.py --page`（method-comparison・knowledge-map・reverse-index-signs・reverse-index-constraints・term-index・how-to-use） | どれもエラー 0・警告 0。term-index と how-to-use は一度 NameError（`check_search_meta`）で止まった。別の担当が check_pages.py を書き換えている途中だったためで、後で流し直すと 0 件だった |
| `python3 -m unittest discover -s tests/tools` | 70 件 OK（skip 2）。ComparisonTest 4 件を含む（10:46 と 11:10 の 2 回） |
| `npx textlint`（直した 5 ページ） | エラー 0。警告 9 は、HEAD のファイルでも同じ 9 件（元からある） |
| `.venv/bin/mkdocs build --strict -d <作業用フォルダ>/site` | 成功（WARNING なし） |
| `node --check`（map.js・filter.js） | 通る |
| ヘッドレスの Chrome（390px タッチ・1280px・ダーク・JS なし・instant navigation） | 上の各節のとおり。コンソールのエラーなし（GitHub の API の 403 は手元の環境によるもので、直しとは関係ない） |

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/lookup/verify-ui

- `scripts/`：check_compare.py・diff_links.py・count_rows.py・cdp.mjs・t_*.mjs
- `shots/`：filter-*・hold-390-*・focus-lazy-*・links-*・mc-uf-table-390 など
- `site/`：直した後のビルド。`site-base/`：HEAD のビルド。`site-inst/`：sitemap.xml を手元の URL にしたコピー

サーバー（ポート 43217）と Chrome は止めた。
