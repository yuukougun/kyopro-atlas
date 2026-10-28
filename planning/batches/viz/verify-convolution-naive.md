# 検証：動く図 convolution-naive

対象：`overrides/assets/js/viz/convolution-naive.js`・`tests/viz/convolution-naive.test.mjs`・置き場 `docs/math/convolution-ntt.md`（sum-pairs の節。74 行に 1 文を足した）。工程11・バッチ f1・Issue #51 の 4 つの図のうちの 1 つで、作った担当は f1-viz-conv（報告 `planning/batches/viz/convolution-naive.md`）。観点は `planning/checklists/figure.md`（G1〜G7）と `code.md`（試験と本文との一致）、手引き §8、interfaces.md §7。検証役は verify-f1-viz1。

**結論：合格。直すべき指摘は 0 件、直すとよい指摘が 2 件。** 状態の列と描画は、図に描かれたものを読み直す独立の確かめ（1231 通りの config）で不一致 0、本文の例の 7 状態は手計算と一致する。ブラウザでは幅 390・1280 のライト・ダークのすべてで図が出て、操作と instant navigation も働く。Issue #51 の完了の条件のうち、このページで「図を表示できなかった」が出ないことを満たす。

## 確かめたこと

| 項目 | 結果 |
| --- | --- |
| 試験 | `node --test "tests/viz/*.test.mjs"`：213 件すべて通る（convolution-naive は 8 件） |
| G1 本文の例（手計算） | a = (1, 2, 3)、b = (4, 5, 6)。c_0 = 1 × 4 = 4、c_1 = 1 × 5 + 2 × 4 = 13、c_2 = 1 × 6 + 2 × 5 + 3 × 4 = 28、c_3 = 2 × 6 + 3 × 5 = 27、c_4 = 3 × 6 = 18（和 90 = 6 × 15）。7 状態（start・ずらし幅 0〜4・done）の caption の組・式・値がこれと一致し、本文 78 行の「5 + 8 = 13」「6 + 10 + 12 = 28」「c_3 = 27、c_4 = 18」「N + M − 1 通り」「O(NM)」とも一致する |
| G1 独立の確かめ | 作業用の `conv_check.mjs`。render の出力（偽の h）から、a・b・積・c の段のマスの文字と添字の文字を位置で読み直し、states の中身に頼らずに次を確かめた：b が反転して並ぶ（左から j = M − 1, …, 0）、上下に同じ x のマスの組がちょうど i + j = k の組、b_0 の真下に c_k、重なったマスだけ塗り、積のマスの値が a_i b_j、c の段は k まで値・残りは点線の空のマス、いまの c_k だけ is-answer、和の式の文字、caption の式、「左にはみ出し」「右端より右」の言い方が図の位置と合う、done の c と掛け算の回数、マスと文字が viewBox に収まる。許すすべての (N, M)（30 通り）× 乱数 40 通り＋9 だけの config と本文の例、計 1231 通りで不一致 0 |
| 試験の強さ | 状態は「位置から作った組 = 定義の組」「どの組も 1 回だけ掛ける」「c_k と途中の c が定義どおり」を許すすべての大きさで見ていて十分である。render の試験には穴がある（指摘 2） |
| 足した文（74 行） | 「ずらし幅が $k$ のとき $b_j$ は $a_{k-j}$ の真下に来るので、重なるのは $i + j = k$ の組だけである。」図は b_0 を列 k に、b_j を列 k − j に置くので一致する。78 行の「ずらし幅 0 では $a_0$ と $b_0$ だけが重なり」とも合う。KaTeX で $a_{k-j}$ が描かれることを撮って確かめた |
| 不正な config | 試験の 17 通りに加え、ブラウザで列の数が 11 になる config（a = (1, 2, 3)、b の長さ 5）に差し替えた写しで「図を表示できなかった：a の長さ N と b の長さ M は N + 2M − 2 ≤ 10 にする（…長い方を a にするとよい）」と出て、console.error にも出る |
| `check_pages.py --page convolution-ntt` | エラー 0・警告 0 |
| `npx textlint docs/math/convolution-ntt.md` | エラー 0・警告 19。HEAD の版（`git show HEAD:… \| npx textlint --stdin`）と同じ 19 件（行も同じ）で、74 行には出ない。caption は 7 つの config の全状態を書き出して textlint にかけ、警告は組 (1, 2, 3) の半角のコンマを数える max-comma の 10 件だけ（本文では数式の中なので出ない） |
| `gen_site.py --check` | llms.txt・graph.json・start/how-to-use.md が古い（updated を 2026-10-29 にしたことによる版の変化。作り直しはメイン） |
| ビルド | `uv run mkdocs build -d <作業用フォルダ>/site`（-q なし）。WARNING・ERROR 0 |
| 書き方（G6・手引き §8・interfaces §7） | binary-search と同じ登録の形（factory、module.exports と KPViz.register、"use strict"、ES5）。`states` は DOM を使わず、入力を書き換えない。`validate` を states・viewBox・render の入口で呼ぶ。viewBox は a・b の長さだけで決まる。色は `.kp-v-*` の class と、z-algorithm と同じく Material の CSS 変数を使う inline の style だけ（色の直書き 0）。caption の添字は fenwick-tree と同じ `a_0` の形。div は `<div class="kp-viz" data-viz="…" data-config='…'></div>` の形 |
| G7 | catalog の visual（dynamic・priority 1「片方を反転して少しずつずらしながら重なりの積を足す素朴な畳み込みのステップ送り」）を満たす。図の前（74 行）と後（78 行）に要点があり、JS がなくても通じる。直前の静的な図 anti-diagonal.svg（積の表を斜めに足す）とは見せ方が違い、重複しない |

### ブラウザ（G2〜G4）

chrome-headless-shell 146.0.7680.76 を CDP で動かした（Node v24.22.1、deviceScaleFactor 2、日本語は /mnt/c/Windows/Fonts を足した fonts.conf）。幅 390（mobile とタッチの emulation）と 1280、それぞれ prefers-color-scheme の light・dark（body の data-md-color-scheme が default・slate になることを確かめた）。

- 4 通りとも、図が 1 つ取り付き、`.kp-viz__error` 0、`.katex-error` 0、JS の例外・console.error 0（出たのは api.github.com の 403 だけで、リポジトリの表示部品のもの）。横のはみ出しなし（scrollWidth = clientWidth）
- 「次へ」をマウスのクリックで押して 1/7 → 7/7。各状態で caption が `states` の caption と一致し、カウンタが進み、最後で「次へ」「最後へ」が無効になる。「前へ」で 6/7、「最初へ」で 1/7（「最初へ」「前へ」が無効）、「最後へ」で 7/7
- キーボード（図にフォーカス）：Home → → End ← Home で 1・2・3・7・6・1。Space で自動再生が始まり、もう一度で止まる
- 自動再生：1× で 1.45 秒後に 2/7。4× に替えると最後まで進んで止まり、ボタンが「自動再生」に戻る
- スワイプ（幅 390、タッチ）：左へで 2/7、右へで 1/7
- instant navigation：本文のリンク（FFT・NTT の仕組み）で fft-ntt へ移り、history.back で戻ると、図は 1 つ・操作の列も 1 つで 1/7 から始まり、「次へ」で 2/7 になる。進む・戻るをもう 1 回しても同じ。window に置いた印が残り、performance.timeOrigin も変わらないことで、読み込みし直しでなく instant navigation で移ったことを確かめた（「記録」の注意を参照）
- 寸法：viewBox 328 × 280。幅 390 で SVG は 337 × 288（倍率 1.03。16px の字が 16.4px、12px が 12.3px、下付きの 10px が 10.3px）、幅 1280 で max-height 22em に当たり高さ 352px（倍率 1.26）。どの状態でも、SVG の全要素の getBBox が viewBox に収まる。ボタンは 44 × 44
- 目で見たこと（全状態を撮った）：重なった列の a と b が塗られて「×」でつながり、真下の積の段に積、c の段のいまの c_k が濃い塗りで b_0 の真下に来る。添字 i・j が色付きの太字になる。ダークでも、塗り・薄い枠・点線の空のマス・濃い塗りの白い字が見分けられる。done では b の段が最後の位置に薄く残り、c がそろう
- config を差し替えた写し（作業用のサイトだけ）：列の数が上限の 10（a = (1, 2)、b = (3, 4, 5, 6, 7)）と 9 が 4 個どうし（ダーク）は幅 390 で倍率 0.75（12px の字が 9px、下付きが 7.5px）。「324」もマスに収まる。1 個どうしは 3 状態で「右へずらす →」が出ない

## 指摘

| 番号 | 図とステップ | 項目 | 内容 | 確かめた結果 | 直し方の案 | 重さ |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | `convolution-naive.js` 107 行。ずらし幅 k ≥ N + 1 の caption（本文の例では 6/7 の k = 4） | G1・C3 | k ≥ N の caption はどれも「下の段を右へ 1 つずらし、b_0 は a の右端より右に出た。」で、k ≥ N + 1 では b_0 はすでに前の段で出ているのに「出た」をくり返す。どの b_j が右に出たかも言わない（k = 0 では「b_1 と b_2 は a の左にはみ出している」と言うのと釣り合わない） | 本文の例で 5/7（k = 3）と 6/7（k = 4）の書き出しが同じ文になる。誤りではないが、6/7 では b_0 と b_1 が右に出ている | k ≥ N では右に出た b_j（j = 0〜k − N）を restOfB と同じ形で言う。k = N は今のまま「b_0 は a の右端より右に出た。」、k > N は「b_0 と b_1 は a の右端より右に出ている。」（3 個以上は「b_0〜b_{k−N}」）。試験の 125 行・173 行は k = N の場合なので変えずに通る。k > N の言い方を確かめる assert を足す | 推奨 |
| 2 | `convolution-naive.test.mjs` 242〜306 行（render の試験） | G1（試験） | render の試験は「塗りのマスが上下でそろう」「× の数」「積のマスの x」「b の段の右端と c_k の列」を見るが、b の段のマスに書く値と添字 j を確かめない。積の値も 279 行の `texts.some(e => e.text === 積)` で、図のどこかにその数があるかしか見ない。図の要の「b を反転して置く」が試験で守られていない | 作業用の写し（`mut/`）で render の 228 行を `var t = s.shift - (M - 1) + j;`（b を反転せずに並べる）に変えると、8 件の試験がすべて通る（図では b_0 が a_0 の下に来ず、重なる組も違う）。同じ写しを `conv_check.mjs` にかけると、最初の状態から「b が反転していない」「重なる組が違う」で落ちる。今の JS は正しい | step の各状態で、a_i の真下の b のマスの文字が b[k − i]、その下の添字の文字が k − i であること、積のマス（a_i の列）の文字が a_i × b_{k−i} であることを、位置で引いて確かめる assert を足す（start では b_j の文字が列 −j にあることも） | 推奨 |

## 作者の「未解決の点」への判断

- start と k = 0 で b の位置が同じこと：start は置き方と添字の読み方の説明、k = 0 は最初の重なりと積で、役割が違うのでこのままでよい
- done で b の段を最後の位置に薄く残すこと：「ずらし幅はここまで」の位置が見えるので、残す方がよい
- 値を 0〜9 の整数に限ること：今の置き場では足りる

## 気づいたが指摘にしないこと

- caption の長さが状態ごとに違うので、操作の列の高さが動く（図の枠の高さが幅 390 で 512〜584px、1280 で 480〜528px）。指で「次へ」を続けて押すとボタンの位置がずれる。viz.js・kp.css の共通の作り（caption の min-height 3.2em）によるもので、ほかの図も同じなので、この図の指摘にしない（メインへの提案：caption の高さを全状態の最大にそろえるなど）
- 列の数が上限に近い config では、幅 390 で下付きが 7.5px になる（作者の報告どおり）。本文の config は倍率 1.03 で問題ない
- caption の組 (1, 2, 3) の半角のコンマが textlint の max-comma に数えられる。caption は本文ではないので問題にしない

## 記録

- 確かめた環境：chrome-headless-shell 146.0.7680.76、Node v24.22.1、幅 390（mobile・タッチ）と 1280、ライトとダーク、deviceScaleFactor 2
- 作業用のファイル：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-f1-viz1/`（`conv_check.mjs` が独立の確かめ、`cdp.mjs`・`drive.mjs` がブラウザの操作で `conv-report.json` がその結果、`shots/conv-*.png` が撮った画像、`mut/` が指摘 2 の写し、`alt.mjs` が config の差し替え）。ビルドしたサイトと http サーバーは使い終えて消した・止めた
- **instant navigation の確かめ方の注意**（メインと、ほかの検証役へ）：brief-verify.md のとおり `python3 -m http.server` で作業用のビルドを `/site/` の下に配ると、本文のリンクは instant navigation にならず、ふつうのページの読み込みになる。Material 9.7.7 は sitemap.xml の URL のプロトコルとホスト名だけを今のページに合わせ（バンドルの `fi(e,t){return e.protocol=t.protocol,e.hostname=t.hostname,e}`）、ポートとパス（`/kyopro-atlas/`）は変えないので、`http://127.0.0.1:<ポート>/site/…` のリンクは sitemap にないとみなされるためである。読み込みし直しでも図は 1 つで 1/7 から出るので、それを見ただけでは instant navigation を確かめたことにならない。今回は作業用のビルドの写しの sitemap.xml の URL を `http://127.0.0.1:<ポート>/site2/` に置き換えて確かめた（window に置いた印が残り、performance.timeOrigin が変わらないことで判定。`/site/` のままでは印が消え、Network に Document の読み込みが出る）。作者の報告には sitemap の置き換えがないので、作者の instant navigation の確かめは読み込みし直しだったと考えられる（今回の確かめで、instant navigation でも問題ないことは分かった）。brief-verify.md の手順にこの置き換えを足すとよい
