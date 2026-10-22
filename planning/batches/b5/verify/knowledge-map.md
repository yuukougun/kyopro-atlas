# b5 検証：knowledge-map（知識マップ）

- 検証したもの：docs/guide/knowledge-map.md、docs/img/knowledge-map/reading.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 照らした実装：overrides/assets/js/map.js、overrides/assets/js/progress.js、overrides/main.html、overrides/assets/css/kp.css、mkdocs.yml の palette、overrides/assets/data/graph.json（2026-10-22）
- 実行したもの
  - `python3 tools/check_pages.py --page knowledge-map`：エラー 0・警告 0
  - `python3 tools/check_noai.py https://js.cytoscape.org/`：noai・noimageai の指定なし（robots="all"）
  - `python3 tools/render_svg.py knowledge-map --scale 2`：幅 360px・720px を目視。文字の重なり・はみ出しはない
  - graph.json と全ページの front matter を Python で突き合わせた：353 ページで prerequisites・level の食い違いなし。前提のグラフに閉路なし
  - 分野をまたぐ前提を graph.json から数え直した：5 本以上の組は 11 組で、Mermaid の本数（basics→ds 15、dp→comb 9、basics→dp 8、ds→graph 8、math→comb 7、basics→tree 6、ds→tree 6、basics→string 6、graph→tree 5、basics→comb 5、basics→geometry 5）とすべて一致
- コード片：なし（code.md の観点は該当なし）
- 確かめて正しかった主な点：segment-tree の前提は prefix-sum だけ、fenwick-tree は prefix-sum と bit-operations、bit-operations と prefix-sum は前提なし（図と確認問題 1 の筋は正しい）。binary-search-answer は基礎で水・青の節を持ち、ラベルは `+水青`（upperLevels は LEVELS の順に並べ、join("")）。次の候補の条件（isCandidate）、80 ページで深さを絞る（MAX_DESCENDANTS・autoDepth）、`?field=`・`?focus=`・`&depth=`・`?view=all`、既定の分野 basics、15 分野、レベルを持たないページだけの分野が はじめに・横断ページ・題材別 の 3 つ、全体の図の数の出し方、1 本の辺を薄く描く、related の囲み（点線の枠・矢印のない破線）、「解除」、ほかのタブの変更の反映（storage イベント→kp:progress）、各ページの下のリンク（次に読むが 9 件以上で「ほか N ページは知識マップで見る」、近いレベルを優先して 8 件）、チェック欄の並び（main.html）、レベル別の一覧の最後の表「下のレベルのページの中の水の節」、ロードマップの列の並び

## 指摘

### 1（直すべき）図｜G5・F3｜reading.svg

- **問題**：図は「地図の一部を写したもの」（本文 49 行）と述べるが、光る枠を橙（`#ffb74d`）の下地で描いている。実際の地図の光る枠は `underlay-color: P.accent`（map.js 319 行）で、サイトの accent は indigo（mkdocs.yml 48・55 行）なので藍色に光る。しかも橙は発展のレベルの色（kp.css `--kp-lv-hatten: #ff8000`、本文 53 行「発展は橙」）で、図を見た読者が「橙＝発展」「光る＝橙」を取り違えうる
- **根拠**：map.js の `node.cand` のスタイル、kp.css の凡例 `.kp-sw--glow`（`--md-accent-fg-color`）、mkdocs.yml の `accent: indigo`
- **直し方**：下地の色を Material の indigo（例 `#3f51b5`、fill-opacity 0.35〜0.45 程度）に変える。あわせて図の下の凡例の行に「光る枠は藍色」などと添えると、レベルの色と混ざらない

### 2（直すべき）事実｜F2（実装の記述）｜#how-to-read 59 行

- **問題**：「マウスを乗せるか長押しすると、点の下に題名・レベル・分野・要約が出て」とあるが、説明の囲み（`.kp-map__info`）は地図の canvas の下、凡例の上に置かれる段落で、点の位置には出ない（map.js 422 行 `root.append(toolbar, status, canvas, info, legend)`、kp.css 485 行に位置の指定なし）。スマホで地図が大きいとき、読者は点の近くを探して見つけられない
- **直し方**：「地図の下に題名・レベル・分野・要約が出て」にする

### 3（直すべき）事実｜F2（実装の記述）｜#how-to-read 63 行

- **問題**：「地図が画面より大きいときは、文字が読める倍率で前提の側（左端）から表示する」は分野ごとの表示だけの動きである。焦点の表示では選んだページを画面の中央に置き（map.js 618〜619 行 `cy.center(cy.getElementById(state.focus))`）、全体の図はいつも全部を収める（614 行）
- **直し方**：「分野ごとの表示では左端（前提の側）から、焦点の表示では選んだページを中央にして表示する。全体の図はいつも全体を収める」のように表示ごとに書き分ける

### 4（直すとよい）事実｜F2｜導入 39 行・#overview

- **問題**：導入は「前提の側を左、次に読む側を右に置く」を 3 通りの表示すべての話として書くが、全体の図は上から下へ配置する（map.js 35 行 `LAYOUT_FIELDS` の `rankDir: "TB"`）。ページの Mermaid は左から右（`flowchart LR`）なので、実物の全体の図と向きが違って見える
- **直し方**：#overview に「全体の図は前提の分野を上、受ける分野を下に置く」と 1 文足す（導入の文は「ページの点を描く表示では」と限定する）。Mermaid も `flowchart TB` にすると実物に近い

### 5（直すとよい）分かりやすさ｜U3｜#how-to-read 56 行・#by-field 72 行

- **問題**：点の約束で「破線の枠：ほかの分野のページ」とするが、「→ 分野名」の点も破線の枠（primary の色）で描かれる（map.js 313 行 `node.next`）。同じ破線で 2 種類の点があることが本文から分からない
- **直し方**：72 行の「→ 分野名」の点の説明に「これも破線の枠（テーマの色）で、中に『N ページ』と出る」と添える

### 6（直すとよい）分かりやすさ・事実｜U3・F2｜#focus 128 行

- **問題**：「塗られていない点のうち最も左にあるものから読めば、前提を飛ばさずに進める」。レベルを持たないページは塗られないので、祖先にあると「最も左の塗られていない点」になり続ける。現に cpp-undefined-behavior（基礎）の前提に cpp-environment（レベルなし）がある（graph.json で該当は 1 件）。主張そのものは、dagre の段で前提が必ず左にあるので、レベルを持つ点に限れば成り立つ
- **直し方**：「塗られていない点のうち、レベルを持つ（枠に色のある）ものの最も左から読めば」とする

### 7（直すとよい）分かりやすさ｜U8｜#quiz の 3 問目

- **問題**：「関連（related）のページが地図の辺にならないのはなぜか」の答えは、61 行の本文をほぼ写せば済む。U8 の「本文の 1 文を写せば済む問い」に当たる
- **直し方**：本文の主張を別の場面に当てる問いに替える。例：「BIT と bit 演算の基本は理解したが累積和にチェックを付けていない。焦点の表示で BIT を選ぶと、何が塗られ、何が光るか」（答え：bit 演算の基本と BIT が塗られ、累積和は前提のない基礎のページなので光る。BIT は理解済みなので光らない）。あるいは「前提の前提を飛ばしてチェックを付けると、次の候補はどう見えるか」（141 行の場合）

### 8（直すとよい）分かりやすさ｜U1｜要点 30 行

- **問題**：要点の「前提をすべて理解した次の候補」は summary の写しで、本文（135・141 行）の「直接の前提だけを見る」と読み違えやすい（祖先すべてと読める）。summary は執筆者が変えられないが、要点の文は書き直してよい（手引き §2.2）
- **直し方**：要点は「直接の前提をすべて理解した次の候補」とし、summary の同じ言い換えをメインへの提案に書く（地図の凡例の文言 map.js 417 行も同じ）

### 9（直すとよい）図｜G5｜reading.svg のラベル

- **問題**：図の点のラベルは「BIT」「bit 演算の基本」だが、地図に実際に出る題名は「BIT（Fenwick Tree）」「bit 演算の基本と XOR の性質」である（pageNode は nav_title か title を使い、両ページとも nav_title は null）。本文は「地図の一部を写したもの」と言うので、地図で同じ点を探す読者が戸惑いうる
- **直し方**：ラベルを実際の題名にする（幅 150 に収まらなければ 2 行にする）か、本文 49 行を「地図の一部を簡単にしたもの（題名は略した）」にする

### 10（直すとよい）リンク｜F7（§15-23）｜#progress 143 行・#as-table 152 行

- **問題**：ロードマップは draft で節があるのに、ページへのリンクになっている。指す先は「解いた数・理解した数」と「色ごとのページの列」の節である
- **直し方**：143 行は `roadmap.md#progress`、152 行は `roadmap.md#reading-order` にする

## 執筆者の未解決の点について

- **Mermaid の本数が古くなる**：本数は 2026-10-22 の graph.json と一致した（上の実行結果）。日付と「ページを足すと変わる」が本文にあるので、今の書き方で誤りではない。生成ブロックにするかはメインの判断（生成にするなら gen_site.py に分野をまたぐ辺の集計を足すだけで済む）
- **次の候補は直接の前提だけを見る**：本文 135・141 行の書き方は実装と一致し、前提の前提を飛ばした場合の注意もある。指摘 8 で要点の言い方だけ直すことを勧める
- **「+水青」の区切り**：本文は実装どおりに書いている。表示を「+水・青」にするなら map.js と本文 57 行を一緒に直す（ページの指摘ではない）
- **URL の引数**：本文の引数の名前と既定の動きは map.js（parseQuery・writeQuery・start）と一致した

## 総合の判定

小さな直しで可（直すべき 3 件：図の光る枠の色、説明の出る位置、地図が大きいときの初めの表示の書き分け。いずれも数行の修正）
