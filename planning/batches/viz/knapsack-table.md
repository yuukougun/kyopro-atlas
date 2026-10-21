# 動く図 knapsack-table（0-1 ナップサックの表）

## 作ったもの

- `overrides/assets/js/viz/knapsack-table.js`：0-1 ナップサックの表 dp[i][j] を 1 行ずつ、1 マスずつ埋める動く図。見本（binary-search・lazy-segment-tree）と同じ形で、`states(config)` は DOM を使わない純粋な関数、`render(svg, state, config, h)` が描く。`viewBox` は W と品物の数だけで決まり、ステップによらない
- `tests/viz/knapsack-table.test.mjs`：試験 7 件
- `docs/dp/knapsack-01.md`：図の前の文に「max を取った側の矢印を太線で示し、最後に答えのマスから表を逆にたどる。」を足した。div の config は変えていない。図の後の文（最後の行 0, 2, 3, 5, 6, 7、答え dp[3][5] = 7、品物 0 と品物 2、各行は減らない）は図の最後の状態と一致する

## config

`{"W": 5, "items": [{"w": 2, "v": 3}, {"w": 1, "v": 2}, {"w": 3, "v": 4}], "mode": "at-most"}`（本文と同じ）

- `W`：1〜10 の整数。`items`：1〜6 個の `{"w": 1〜10 の整数, "v": 0〜99 の整数}`。`mode`：`"at-most"`（既定。初期値すべて 0、答え dp[N][W]）か `"exact"`（dp[0][0] = 0、ほかは −∞、答えは最後の行の最大）
- 誤りは見本と同じく Error を投げ、viz.js が「図を表示できなかった：…」と出す（`w: 0` で表示を確かめた）
- 状態の表の −∞ は null で持つ（JSON にしても失われないように）。マスと caption では「−∞」と書く（執筆者の仕様の「−」ではなく、本文の表の書き方に合わせた）

## ステップ（本文の例で 20 状態。一般に N × (W + 1) + 2）

1. init：行 0 だけを埋める。caption は「以下」の定義ですべて 0 にする理由（ちょうどのときは dp[0][0] = 0、ほかは −∞ にする理由）
2. マスごとに 1 状態：いまのマスを太い枠、読む 2 つのマスを強調し、選ばない遷移（真上から真下）と選ぶ遷移（w_i 左から斜め、中ほどに「+v」）を矢印で描く。max を取った側は太い実線と塗ったマス、取らなかった側は細い破線と灰色のマス。同じ値ならどちらも太線。j < w_i のマスは真下の矢印だけ。caption は `dp[2][3] = max(dp[1][3], dp[1][2] + 2) = max(3, 3 + 2) = 5 である。品物 1 を選ぶ方（斜めの矢印）が大きい。` の形で、行の最初のマスでは「行 2 では品物 1（重さ 1・価値 2）を選ぶかを決める。」を前に付ける。図の下にも短い式を出す
3. done：答えのマスを塗り、答えのマスから表を逆にたどった道（同じ値なら選ばない側）を太線で示す。caption は最後の行・答え・選んだ品物（「品物 0 と品物 2 を選ぶ」）と、本文と同じ「各行は左から右へ減らない」の理由

色だけに頼らないよう、行の左に「dp[1]：品物 0」「重さ 2・価値 3」と文字で書き、まだ埋めていないマスは点線の枠、いまのマスは太い枠、選んだ遷移は太い実線、選ばなかった遷移は細い破線にした。色は kp.css の既存の class（kp-v-cell・kp-v-text・kp-v-ptr・kp-v-mark）だけで付け、CSS は足していない。

## 確かめたこと

- `node --test tests/viz/knapsack-table.test.mjs`：7 件すべて通る。本文の config で最後の行が [0, 2, 3, 5, 6, 7]、答え dp[3][5] = 7、選んだ品物 [0, 2]、各行が減らない、dp[2][3] の caption が執筆者の報告の例の式と一致。全探索（最初の i 個の部分集合をすべて試す）と、各状態の埋めたマスの値が一致：乱数の 400 通り × 以下・ちょうど。逆にたどった選び方が答えの値（ちょうどでは重さも）を実現する。端の場合（どの品物も入らない、W ちょうどに詰められない、同じ値の tie、上限いっぱいの W = 10・6 個、mode の省略）、ちょうどの定義で −∞ の caption（`max(−∞, −∞ + 3) = −∞`）、caption が句点で終わる、入力を書き換えない、誤った config 16 通りで Error、viewBox の大きさ
- `python3 tools/check_pages.py`：エラー 1 件は `ds/lazy-segment-tree-patterns.md` のリンク切れ（別のページ）で、knapsack-01 には 0 件。警告 0
- `npx textlint docs/dp/knapsack-01.md`：エラー 0。警告 17 件はすべて以前からのもの（足した 64 行には出ていない）
- ブラウザ：`uv run mkdocs build -d <scratchpad>/site-knapsack-table`（-q なし）でビルドし、`python3 -m http.server 8831` で出して、chrome-headless-shell を CDP で操作（日本語は render_svg.py の font_env と同じく Windows のフォントを足した fonts.conf）。幅 900px・360px（ライト）と 900px（ダーク）で、「次へ」のクリックで 1/20 → 20/20 と状態が進み、表・矢印・caption・カウンタが変わることをスクリーンショットで目で確かめた。360px でも数字・行の名前・「+3」が読め、横にはみ出さない（scrollWidth = 360）。config を替えた写し（ちょうどの定義、W = 8・品物 5 個、誤りの w = 0）も表示を確かめた
- 撮った画像：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/kt-shot/`（900-*・360-*・900-dark-*・ex/・big/・err/・final/）

## 未解決の点

- 執筆者の仕様の後半（1 次元の配列を大きい方から・小さい方から更新する 2 本を並べる）は作っていない。同じ例が静的な図 rolling-direction.svg にあり、置き場の div も meaning の節の 1 つだけなので、表を埋める図に絞った。動く図にするなら別の名前（例：knapsack-rolling）で rolling の節に置くのがよい（メインの判断）
- ちょうどの定義で両方が −∞ のマスは tie として両方の矢印を太線にしている（caption は「どちらもまだ作れない重さである」）。本文では mode = exact を使っていない
- W = 10 では幅 360px で文字が約 8px まで縮む。本文の W = 5 では問題ない。スマホで読むには W ≤ 8 ぐらいにとどめる
- 1 マス 1 ステップなので本文の例で 20 ステップある。長いと感じるなら、j < w_i のマス（真上を下ろすだけ）をまとめる手がある

## 検証の指摘への対応（verify-knapsack-table.md）

直すべきは 0 件。直すとよい 3 件のうち 1・2 を直し、3 は採らなかった。

- 1（何も選ばないときの done の caption）：直した。`picked` が空のときは「太線は答えのマスから表を逆にたどった道で、どの段も真下なので品物を選ばない。」にし、斜めの段に触れない。試験に `{W: 2, items: [{w: 1, v: 0}]}` の done の caption を足した
- 2（ちょうどで keep・take がどちらも −∞ のマス）：直した。choice を `"none"` にし、両方の矢印を細い破線、両方の読み元を灰色で描く（render は keep・tie・only のときだけ選ばない側を、take・tie のときだけ選ぶ側を太線にするので、none は両方とも細くなる）。caption は「どちらもまだ作れない重さなので、どちらの矢印も取らない。」。試験に、ちょうど・W = 3・(2,3) の dp[1][3] が none になること、tie のマスは keep が −∞ でないことを足した。前の「未解決の点」の 2 つ目はこれで解消
- 3（catalog の visual の後半、1 次元配列の更新の向き）：採らなかった。書いてよい範囲（この図と置き場の div の前後）を超え、別の名前の図を rolling の節に置くかはメインの判断である。要点は静的な図 rolling-direction.svg が同じ例で示している
- 確かめたこと：`node --test tests/viz/knapsack-table.test.mjs` 7 件通る（`tests/viz/*.test.mjs` 全体で 74 件通る）。`python3 tools/check_pages.py` はエラー 0（警告 2 件は misc/bitset-speedup の別名で、このページではない）。`npx textlint docs/dp/knapsack-01.md` はエラー 0・警告 17（以前と同じ。本文は変えていない）。`uv run mkdocs build -d <scratchpad>/site-knapsack-table`（-q なし）でビルドし、chrome-headless-shell で本文の config を 900px で 1/20 → 2/20 → 11/20 → 20/20、360px で 20/20 と「次へ」で進むことを確かめた。config を替えた写し（ちょうど・W = 3・(2,3) の dp[1][3]、W = 2・(5,9) の done）で、none のマスが両方細い破線・灰色になること、何も選ばない done の caption を目で確かめた。画像は `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/kfix/`
