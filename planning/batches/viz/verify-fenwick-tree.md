# 動く図 fenwick-tree の検証

対象：`overrides/assets/js/viz/fenwick-tree.js`・`tests/viz/fenwick-tree.test.mjs`・`docs/ds/fenwick-tree.md`（#invariants に足した 85 行目の段落と 87 行目の div）。報告 `planning/batches/viz/fenwick-tree.md`。観点は `planning/checklists/figure.md`（G1〜G7）と `code.md`（JS に当てはまる範囲）。

## 結論

直すべき指摘は 0 件、直すとよい指摘は 3 件。状態の列は手法として正しく（sum は最下位の 1 を消しながら箱を右から取り、add は a_i を含む箱を短い順にちょうど 1 回ずつ直す）、本文の例の値（初期の t = 3, 4, 4, 9, 5, 14, 2, 31、sum(7) = t[7] + t[6] + t[4] = 2 + 14 + 9 = 25、add(3, +2) が t[3]・t[4]・t[8] を直して 16 で止まる）・静的な図 boxes.svg の代替テキスト・#operations の擬似コードと食い違わない。ブラウザで図が描かれ、ステップ送りで進むことを目で確かめた。

## 確かめたこと

- `node --test tests/viz/fenwick-tree.test.mjs`：7 件すべて通る
- 別に書いた突き合わせ（作業用の場所 `scratchpad/vfen/chk.cjs`・`chk2.cjs`。リポジトリには置いていない）：試験とは別の乱数（Park–Miller）と別の作り方で参照を作った。t は本文の「線形時間の構築」（t[i] = a_i から始め、t[i + lowbit(i)] に足し込む）で作り、sum は `i & (i − 1)` で最下位の 1 を消して進め、add は定義から「a_i を含む箱」を全部列挙して短い順に直す。N 1〜12、操作 1〜4 個、a・x は −99〜99 の 30000 通りと、値を同じ符号の 80〜99・x を 50〜99 に寄せて 999 を超えやすくした 30000 通り（うち 655 通りが Error）。全ステップの `phase`・`opIndex`・`i`・`s`・`current`・`visited`・`coveredFrom`・`a`・`t` が一致し、「途中の |t| か |s| が 999 を超える」ときにだけ Error になることも一致した。caption の「で s = …。」と「旧 → 新」の数が状態の値と一致し、全ステップで `render` を偽の `h` で呼んで座標・文字に NaN・undefined・Infinity が出ないことも確かめた
- caption：本文の例の 11 状態、`{a: [−4], ops: [sum(0), add(1, −9), sum(1)]}`、`{a: 1〜12, ops: [sum(12), add(12, +1)]}` を全部読んだ。1 ステップに変化は 1 つずつ（sum は s と箱 1 つ、add は箱 1 つ）で、caption と描かれた値・上の行（「sum(7)　i = 4　s = 25」など）がそろう。2 進数の桁数は N に合わせ、止まる値 16 だけが 5 桁（10000）になるのは正しい
- 誤った config：試験の 23 通りに加え、config が文字列・配列、`a: "123"`・`a: {length: 2}`・`ops: {}`・`i: "1"`・`i` なし・`i: Infinity`・`x: "1"`・`x: Infinity`・`x: 1e300`・`a: [NaN]`・操作が配列・`x: −0` がすべて Error になる（余分なキーは無視する。見本と同じ扱い）。ブラウザでも add の i を 0 にしたページで「図を表示できなかった：add の i は 1 ≤ i ≤ 8 の整数にする（1-indexed。i = 0 の add は止まらない）」が出て、SVG とボタンは出ない
- `python3 tools/check_pages.py`：エラー 7 件・警告 0 件。エラーはすべて math/gaussian-elimination.md などの用語集の anchor で、fenwick-tree には出ない
- `npx textlint docs/ds/fenwick-tree.md`：エラー 0・警告 18。80〜99 行目には出ない（足した 85 行目に警告なし）
- ブラウザ：`uv run mkdocs build -d <scratchpad>/site-fenwick-tree`（-q なし。警告は gaussian-elimination の anchor 5 件だけ）を `python3 -m http.server` で配り、`~/.cache/puppeteer` の chrome-headless-shell 146（日本語は font_env と同じ fontconfig で `/mnt/c/Windows/Fonts` を足す）を CDP で動かした。幅 800（ライト）・360（ライト）・360（ダーク `slate`）で、11 状態すべてを「次へ」で送って撮った（`scratchpad/vfen/shots/`）。カウンタ 1/11〜11/11 と caption が進み、太枠・点線・三角の印が caption のとおりに動き、最後で「次へ」「最後へ」が無効になる。キーボードの End で 11/11、Home で 1/11。JS の例外・console.error は 0（誤った config のページの console.error だけ）。幅 360 で `document.documentElement.scrollWidth` は 360（はみ出しなし）、SVG は 306.8px（viewBox 344×282、約 0.89 倍）、ボタンは 44×44。N = 12 の config も幅 360 で読めた（約 0.61 倍）
- 色だけに頼らないか：今の箱は太い枠、通った箱は点線の枠、今の i は添字・2 進数の太字と三角の印、add の a_i は太枠。sum で覆い終えた a の塗りと枠の色は色だけだが、点線の箱と caption の「a_1〜a_7 を重なりなく覆う」で分かるので問題にしない。ダークでも枠・文字が読める
- 本文との一致：85 行目の段落（列 3・1・4・1・5・9・2・6、sum(7) が 2 + 14 + 9 = 25、add(3, +2) が t[3]・t[4]・t[8] に 2 を足す）は図の動きと一致する。init の caption「t[i] は区間 (i − lowbit(i), i] の和、すなわち a の i で終わる長さ lowbit(i) の区間の和」は 74 行目の性質と同じ。sum の「最下位の 1 が消える」、add の「最下位の 1 の桁で繰り上がる」は 107・109 行目と同じ。添字はこの節の 1-indexed にそろっている
- catalog の visual（ds.yaml、priority 2「添字を 2 進数で並べ、各箱が覆う区間を横棒で描き、add と sum で通る箱が順に光るステップ送り」）を満たす

## 指摘

| 番号 | 重さ | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | `fenwick-tree.js` 27 行目（`MAX_ABS_T`）と `validate`、312・322 行目（値の文字） | 検証は「絶対値 999 以下」しか見ないので、幅 1 列の枠（奇数の t[i] と a の行。幅 36・34）に 4 文字の値（−100〜−495）が入り、文字が枠の線にかかる。コメントの「箱の枠に収まる桁数」が成り立たない | `{"a": [−99 を 12 個], "ops": [add(9, −99) を 4 回]}` を幅 360 で描くと、最後の状態で a_9 と t[9] の「−495」が枠の左右の線に重なる（`scratchpad/vfen/shots/wide-20.png`）。この config は Error にならない。本文の config は影響を受けない | `validate` で、a の各値と奇数の i の t[i]（幅 1 の枠に描く値）が −99〜999 に収まるかも確かめ、外れたら Error（「幅 1 の枠に描く a と t の値は −99〜999 にする」など）を投げ、試験にその 1 件を足す。または `render` で、幅 1 の枠で文字列が 4 文字以上のときだけ `font-size` を小さくする |
| 2 | 直すとよい | `fenwick-tree.js` 184 行目（sum の start の caption） | i = 1 で「a_1 + … + a_1 を求める」、i = 2 で「a_1 + … + a_2 を求める」と出る。項が 1〜2 個のときの「…」は不自然 | `{a: [−4], ops: [..., {type: "sum", i: 1}]}` の 7 状態目。本文の例（sum(7)）では出ない | i = 1 は「a_1 を求める」、i = 2 は「a_1 + a_2 を求める」、i ≥ 3 は今のまま、と分ける |
| 3 | 直すとよい | `fenwick-tree.js` 233〜234 行目（add の end の caption） | 直した箱が 1 つのとき「a_12 を含む箱は t[12] の 1 つで、すべて 1 回ずつ直した。」と出る。1 つに「すべて」「1 回ずつ」は合わない | `{a: 1〜12, ops: [..., {type: "add", i: 12, x: 1}]}` の 8 状態目、`add(1, −9)`（N = 1）の 6 状態目 | `visited.length === 1` のときは「a_12 を含む箱は t[12] だけで、それを直した。」にする |

## 気づいたこと（指摘にしない）

- add の start の状態では、a の行はすでに足した後の値（a_3 = 6）で、t はまだ足す前（t[3] = 4）である。caption が「a_3 に 2 を足す（a_3 = 6）。a_3 を含む箱をすべて直すため…」と書いているので読み違えは起きにくい。BIT の実装は a を持たず t だけを直すので、a の行は「論理上の列」とみなせばよい
- caption の添字は「a_3」「a_1〜a_7」と下線で書いている（本文は $a_3$）。ほかの動く図は `a[i]`・`D[i]` の形だが、このページでは t[i] と区別するために下付きの形にしたものと読める。本文と記号の意味は同じなので問題にしない
- config が文字列のときの Error が「data-config がない」になるが、two-pointers・lazy-segment-tree と同じ文面なので問題にしない
- 作業用の場所の `scratchpad/site-fenwick-tree/ds/` に、確かめのために `fwbad/`・`fw12/`・`fwwide/` のページを足した（ビルド済みのサイトの写しで、リポジトリには影響しない）
