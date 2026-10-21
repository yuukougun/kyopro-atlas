# 動く図 floor-quotient-enum の検証

対象：`overrides/assets/js/viz/floor-quotient-enum.js`・`tests/viz/floor-quotient-enum.test.mjs`・`docs/math/floor-quotient-enum.md`（#why-sqrt に足した 1 段落と div）。報告 `planning/batches/viz/floor-quotient-enum.md`。観点は `planning/checklists/figure.md`（G1〜G7）と `code.md`（JS に当てはまる範囲。C++ のコード片は今回の対象外）。

## 結論

直すべき指摘は 0 件、直すとよい指摘は 2 件。状態の列は手法（l ← 1、q = ⌊N/l⌋、r = ⌊N/q⌋、l ← r + 1）として正しく、本文の例（N = 20 の 8 区間・和 66、確認問題の N = 10 の 5 区間）・静的な図 staircase.svg・本文の記法（閉区間 [l, r]、s = ⌊√N⌋、1-indexed）と食い違わない。ブラウザで図が描かれ、ステップ送りで状態が進むことを目で確かめた。

## 確かめたこと

- `node --test tests/viz/floor-quotient-enum.test.mjs`：7 件すべて通る。試験は全探索の区間・和との一致、r の式、l ≤ √N の区間の幅 1、l > √N の区間の q² < N、区間の数 2s / 2s − 1 を N = 1〜30 のすべてで見ており、状態の数だけを見る試験ではない
- 別に書いた突き合わせ（作業用の場所 `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/vfqe/chk.cjs`。リポジトリには置いていない）：N = 1〜30 で、試験とは別の方法で答えを作って比べた。和は「1〜N の各数の約数の個数の和」を二重ループで数えた値（本文 #why-sqrt の主張）と一致し、区間の数は ⌊N/i⌋ の値の集合の大きさと一致した。各区間について、[l, r] のすべての i で ⌊N/i⌋ = q、r + 1 では値が変わること（r が最大）を確かめた。caption は正規表現で数を取り出し、l・q・r・足す量・和・次の左端がすべて状態と一致すること、「幅 1」「√N より小さい」の言い分けが l² ≤ N で切り替わり、それぞれ実際に幅 1・q² < N であること、done の caption の「左に k 個」が s と一致し、区間の数が ⌊N/s⌋ = s のときだけ 2s − 1 になることを確かめた。すべて一致（不一致 0）
- caption：本文の例の 10 状態を全部読んだ。1 ステップに変化は 1 つ（区間を 1 つ足す）で、caption と描かれた太枠・三角・下の行の和がそろう。[7, 10] の caption「(10 − 7 + 1) × 2 = 8 を足して 56」は本文 #block-end の「l = 7 なら q = 2、r = 10」と同じ
- 誤った config：試験の 9 通りに加え、`undefined`・`{}`・`{n: -1}`・`{n: true}`・`[]`・`"x"`・`{n: [20]}` がすべて Error になる。ブラウザでも `{"n": 0}`・`{"n": "20"}` のページで「図を表示できなかった：n は 1〜30 の整数にする」と出て、SVG は描かれない（console.error は viz.js が出す 1 行だけ）
- `python3 tools/check_pages.py`：エラー 0・警告 0
- `npx textlint docs/math/floor-quotient-enum.md`：エラー 0・警告 20。足した 59 行目には警告がない（警告は前からある行だけ）
- ブラウザ：`uv run mkdocs build -d /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/site-floor-quotient-enum`（警告は Material の告知だけ）を `python3 -m http.server` で配り、`~/.cache/puppeteer` の chrome-headless-shell 146.0.7680.76（日本語は font_env と同じ fontconfig で `/mnt/c/Windows/Fonts` を足す）を CDP で動かした（`vfqe/shot.mjs`）。幅 360（ライト・ダーク `slate`）と 800（ライト）で「次へ」を押して撮った。カウンタ 1/10〜10/10、caption、太枠（`.is-focus` は block の状態で 4〜7 個の要素、start と done で 0）、l・r の三角、下の行「足した区間 k 個、和 = …」が進み、最後で「次へ」「最後へ」が無効になる。キーボードの End で 10/10、← で 9/10。JS の例外・console.error は 0。幅 360 でも 800 でも `scrollWidth` は画面の幅以内（はみ出しなし）。ビルド結果のコピーで config を `{"n": 30}`・`{"n": 1}`・`{"n": 16}` に替えたページも撮り、N = 30 で添字が間引かれて重ならないこと、N = 1 で右の区別の文字が出ないこと、N = 16 で「√N = 4」と出ることを確かめた（撮った画像は `vfqe/shots/`）
- 色だけに頼らないか：まだ足していない棒は点線の枠、足し終えた棒は実線と塗り、いまの区間は太枠・太字の値・l と r の三角と文字で区別している。ダークでも塗りと点線が見分けられる
- 狭い幅：viewBox は N = 20 で 374×316、N = 30 で 364×316、N = 1 で 300×316 で、ステップによらない。幅 360 で棒の値と添字が読める（添字は約 10px）
- G7：catalog（`math.yaml` の floor-quotient-enum）の visual は dynamic・priority 1 で「階段グラフで、同じ高さの段を 1 つの区間として順にたどるステップ送り」。図はこれを満たす。図の前の案内の段落と後の本文で、JS が動かなくても意味が通る
- 本文との一致：足した段落の「8 段を足し終えると和は 66 になる」は done の状態と同じ。図の上の「1 個ずつ」「商 < √N」は静的な図の代替テキスト（「線より左は 1 個ずつ、右は商が 4 以下」）・本文の箇条書き（i > √N の側は ⌊N/i⌋ < √N）と同じ内容

## 指摘

| 番号 | 重さ | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | `floor-quotient-enum.js` 74 行目（start の caption） | 「右（i > √N）は値が √N 未満しかない」は「値が √N 未満の数しかない」とも読め、日本語として落ち着かない。言いたいのは「右の値はどれも √N 未満」 | 本文の例の 1 状態目（幅 360 の `vfqe/shots/w360-s1.png`） | 「右（i > √N）の値はどれも √N 未満である。」に替える（試験の caption の照合に影響しないことを確かめる） |
| 2 | 直すとよい | `floor-quotient-enum.js` 73〜74 行目（start の caption） | N = 1 では i > √N の棒がなく、図も右の区別の文字（「商 < √N」）を出さないのに、caption は「右（i > √N）は値が √N 未満しかない」と右側を説明する | config `{"n": 1}` の 1 状態目（`vfqe/shots/n1-s1.png`）。本文の config には出ない | `s < n` のときだけ右側の文を付ける（render の 170 行目と同じ条件）。N = 1 は「左（i ≤ √N）の 1 本だけである。」などにする |

## 気づいたこと（指摘にしない）

- 図は #why-sqrt にあり、右端の式 r = ⌊N/⌊N/l⌋⌋ は次の #block-end で導く。案内の段落で「右端 r の求め方は次の節で説明する」とリンクしているので、読む順で困ることはないと判断した。図を #block-end に移すかは作者の報告どおりメインの判断に任せる
- 幅 1 の段の 2 桁の値（「10」「20」）が棒の幅よりわずかに広い件（作者の未解決）は、撮った画像で隣の値と重ならず読めることを確かめた
- 作業用の `scratchpad/v/` はほかの検証役と共有されていたので、この検証で書いた `chk.cjs`・`shot.mjs` は `scratchpad/vfqe/` に写した（`v/` の同名のファイルは上書きしてしまった）。ポート 8731 は別のサーバが使っていたので 8797 で配った
