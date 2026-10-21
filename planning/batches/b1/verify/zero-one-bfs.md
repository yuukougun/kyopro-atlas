# zero-one-bfs の検証（工程8b・b1）

- 対象：docs/graph/zero-one-bfs.md、snippets/zero-one-bfs/（graph・turns の 2 組）、docs/img/zero-one-bfs/example-graph.svg、置き場の div（`data-viz="zero-one-bfs"`）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/zero-one-bfs.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page zero-one-bfs`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/zero-one-bfs`（2 片・コンパイル 2 回・期待と違う 0）、`npx textlint docs/graph/zero-one-bfs.md`（0 errors・3 warnings。報告のとおり 92・162・163 行の数式の中の読点で、誤検出）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- front matter：catalog と比べ、変わったのは complexity・stage・updated と、sections に足した 2 節（procedure・cost-modeling）と並びだけ（手引き §2.1 の範囲）。要点の計算量と complexity は一致。別名の行に aliases の 2 つがある
- 問題：`python3 tools/ap.py show` で 5 問の題名・diff を確かめた（abc176_d 1248・arc005_3 1503（参考値）・typical90_aq なし・abc213_e 1423・abc246_e 1476）。label・URL・diff は台帳と一致し、要約に手法名はない。補充の候補 abc400_d（1026）も実在する
- 例題の方針と evidence：
  - abc176_d：oraclesqlpuzzle のコードで、4 近傍は追加コストなし・5×5 のワープはコスト +1・届かなければ -1 を確かめた。本文の方針と一致（台帳の evidence に足す提案に賛成）
  - arc005_3：drken の記事で、壁マスへ入る辺の重みを 1・通路へは 0 とし、最短路長が 2 以下なら YES、ダイクストラ法でも十分 AC と確かめた。本文と一致
  - typical90_aq：E869120 の sol/043.cpp で、始点の 4 つの向きを距離 0 で deque に入れ、ゴールの 4 つの向きの最小を答えると確かめた。本文と一致
  - abc213_e：hamayan の記事で、隣への移動はコスト 0、パンチで行けるのは 5×5 から「マンハッタン距離が 4 の場合」（＝四隅）を除いたマスと確かめた。本文と一致
  - abc246_e：hamayan の記事は「直前に進んだ向き」を状態に持つダイクストラ法で、最初の 1 手にもコストが付く形。本文の「始点の距離を 1 にするか、答えに 1 を足す」と同じ答えになる。盤面の上限は記事に書かれておらず、配列の大きさ 1510 から読めるだけ（指摘 5）
- 本文の主張の検証（作業用の場所で）：
  - graph.cpp を ASan・UBSan 付きで、頂点 1〜8・辺 0〜20 の乱数のグラフ 1500 個についてダイクストラ法と比べ、不一致 0
  - turns.cpp を ASan・UBSan 付きで、1〜6 × 1〜6 の乱数の迷路 1500 個について、独立な方法（直進できるだけ進む移動を 1 手とする BFS で線分の数を求め、1 を引く）と比べ、不一致 0
  - 01-BFS を Python で書き、乱数のグラフ 20000 個で「各頂点の push は高々 2 回」「読み飛ばしの後に辺を調べるのは各頂点 1 回」「取り出す距離は広義単調増加」「deque の中の距離は 2 種類以下」を assert で確かめた（最大 push 2・最大走査 1・違反 0）。計算量の証明（折りたたみ）と 126 行の「読み飛ばしなしでも正しい」も正しい
  - deque の例の表（82〜90 行）を手で追い直し、各行の deque の中身と最終の距離（0,1,0,0,1）が一致。graph.yaml の 1 つ目の case とも一致
  - 確認問題「初めて見つけたら確定」の例（$s \to a$ 1・$s \to b$ 0・$b \to a$ 0）は、辺を見る順によらず $a$ が 1 になる。正しい
  - `<=` で更新すると重み 0 の閉路（$u \leftrightarrow v$ が重み 0）で無限ループになることを確かめた
  - 向きの確認問題（U ターンの辺を張らなければ重み 2）、重み 2 を末尾に入れると単調が崩れる例、辺を割る対処：どれも正しい。U ターンを重み 1 で張る turns.cpp も、U ターンが最適解に要らないので「曲がる回数の最小」の答えは変わらない（上の比較で確認）
  - 9×10^6 個の `int` で約 36 MB：正しい
- 執筆者の未解決の点：
  - SVG の表示：指摘 1
  - 「Dial の方法」：英語版 Wikipedia の Bucket queue（`tools/check_noai.py` で指定なしを確認）で、Dial (1969) の最短路のアルゴリズムであること、優先度が幅 $c + 1$ の範囲に収まるので余りで添字を付けて使い回せることを確かめた。本文の「キューは $C + 1$ 個を使い回せば足りる」は正しい。ただし出典がない（指摘 3）
  - ABC246 E の上限：本文（171 行）は一般論の例として $H = W = 1500$ を使うだけで、問題の制約とは書いていない。本文は直さなくてよい。参考の説明だけ直す（指摘 5）
  - typical90_aq の位置：diff がないので易しい順は決められない。★4 で、ほかの 2 問（1423・1476）より前に置くのは妥当
- 出典（F8・F9）：参考の 6 件の URL を開き、題名（ARMERIA「01-BFSのちょっと丁寧な解説」、けんちょん「AtCoder ARC 005 C - 器物損壊！高橋君 (試験管水色)」、oraclesqlpuzzle「ABC176-D Wizard in Maze」、GitHub の sol/043.cpp、hamayan の 2 件）が書かれたとおりと確かめた。ARMERIA の記事と本文を並べて読んだが、本文は構成（表・不変条件の箇条・例のグラフ・証明）が違い、例も別で、近すぎない
- リンク先：bfs・dijkstra・grid-graph・method-comparison・modular-shortest-path（stub）・extended-dijkstra（`#parity-mod-direction` の見出しあり）はどれもある
- 図：Windows の Chrome（headless=new）で example-graph.svg を等倍（600×330）と、幅 390px の画面に幅 358px で（2 倍密度、暗い背景の上に）画像にして目で確かめた。背景は白で塗られ、`viewBox` があり、文字はテキストのまま。重み 0 は青い実線、重み 1 は灰色の破線で、色だけでなく線の種類で分けている。辺 6 本・重み・最終の距離は div の config・本文の表と一致する。ただし重なりがある（指摘 1）
- 動く図：catalog の visual は `{kind: dynamic, priority: 1}` だが、`overrides/assets/js/viz/` に zero-one-bfs.js はない（指摘 2）

## 指摘

### 1｜直すべき｜figure（G5・G3）｜example-graph.svg

- **問題**：辺 1→4（青い実線、(241.1, 233.7) → (497.0, 156.9)）が、頂点 2 の下の「dist = 0」（y = 192）の上を横切り、文字に線が重なって読みにくい。さらに同じ線が辺 2→4 の重みのラベル「1」の白い四角（x 435〜455、y 153〜173）にかかって途切れ、「1」が青い実線のすぐ上に乗って見える。辺 1→4 のラベル「0」はその下にあるので、頂点 4 の手前では「1」と「0」のどちらがどの辺の重みか取り違えやすい。2 本の矢じりも頂点 4 の左側で重なっている。執筆者が報告で表示の確認を頼んだ点
- **根拠**：上の 2 枚の画像（等倍・幅 358px）で、「dist = 0」に線が重なり、「1」のラベルが実線と破線の間に挟まって見えた。座標の計算でも、x = 370 での辺 1→4 の y は約 195 で、ラベルの文字（y = 192 を基線とする 14px の文字）と重なる
- **直し方**：辺 1→4 が頂点 2 の周りを通らない配置にする。たとえば頂点 4 を (520, 240) に下げて 1→4 を水平に、2→4 を右下へ向かう斜めにする（このとき頂点 4 の距離は下ではなく右か上に書く）。または頂点 2 の距離を上（y ≈ 115 の右寄り）に書き、2→4 のラベルを破線の上側（y ≈ 135）に置く。直したら等倍と幅 358px で描画して、線と文字・ラベルどうしが重ならないことを確かめる

### 2｜直すとよい｜figure（G7）・clarity（U6）｜#deque-invariant の 94〜96 行（動く図の置き場）

- **問題**：catalog の visual は priority 1 の動く図だが、zero-one-bfs.js がなく、いまのページでは div の場所に何も出ない。96 行の「動く図では、…を示す」は、JS ができるまで読者には存在しない図の説明になる。なお図の前後の文章（静的な図と手順を追う表）だけで要点は通じるので、JS がなくても意味は分かる
- **根拠**：`overrides/assets/js/viz/` には binary-search.js・lazy-segment-tree.js だけ
- **直し方**：メインが zero-one-bfs.js と tests/viz/zero-one-bfs.test.mjs の作成を頼む（仕様は執筆者の報告のとおりでよい。頂点の配置は指摘 1 で直した後の SVG に合わせる）。本文は直さなくてよい

### 3｜直すとよい｜fact（F9）｜#weights-012 の 185 行と #references

- **問題**：「Dial の方法」「キューは $C + 1$ 個を使い回せば足りる」は記憶に基づき、参考に出典がない（手引き §2.6「参考にした資料はページ末尾の参考に残す」）
- **根拠**：英語版 Wikipedia「Bucket queue」の「Dial's algorithm for shortest paths」と、余りで添字を付ける最適化の段落で、名前（Robert B. Dial, 1969）と $c + 1$ の幅を確かめた。内容は正しい
- **直し方**：参考に「[Wikipedia（英語）「Bucket queue」](https://en.wikipedia.org/wiki/Bucket_queue)：距離ごとのキュー（Dial の方法）と、$C + 1$ 個を使い回せる理由」を足す。en.wikipedia.org は付録 B にないが `tools/check_noai.py` で指定なしを確かめた（付録 B への追加はメインへの提案）

### 4｜直すとよい｜fact（F7）｜#direction-state の 158 行

- **問題**：リンクの文字が「拡張ダイクストラ法」だが、リンク先の題名は「状態を頂点にする」で、aliases にあるのも「拡張ダイクストラ」（法なし）。読者が飛んだ先で題名が違い、正規形とも合わない
- **直し方**：「（状態を頂点にする考え方は[状態を頂点にする](../graph/extended-dijkstra.md#parity-mod-direction)の「偶奇・mod・向きを持つ」）」のように、リンク先の題名か節の見出しを文字にする

### 5｜直すとよい｜fact（F9）｜#references の hamayan「Bishop 2」の行（278 行）

- **問題**：説明に「と盤面の大きさ」とあるが、記事に制約の記述はなく、コードの配列の大きさ（1510）から推測できるだけ。本文も ABC246 E の上限を述べていない
- **直し方**：「練習の方針（向きを状態に持つ）」だけにする

### 6｜直すとよい｜fact（F3）｜#必要になる場面 の 52 行

- **問題**：「1 マスから出る辺が 25 本」は、例題 ABC176 D（歩く 4 本＋ワープ 24 本＝28 本、212 行）とも ABC213 E（4＋20＝24 本）とも合わない。「といった規模」とあるので誤りとまでは言えないが、212 行と並べると数が揃わない
- **直し方**：「1 マスから出る辺が 20〜30 本」か「1 マスから 5×5 の範囲へ辺が出る」とする

### 7｜直すとよい｜code（C3）｜snippets/zero-one-bfs/turns.cpp の 12〜30 行

- **問題**：変数名の意味が本文と graph.cpp とでずれる。turns.cpp の `s` は状態の番号だが、本文と graph.cpp の `s` は始点。`nd` は turns.cpp では新しい向き、graph.cpp では新しい距離。`w` は turns.cpp では盤面の幅、graph.cpp では辺の重み。同じページの 2 つのコード片を続けて読むと取り違えやすい
- **直し方**：turns.cpp の `s` を `st`（状態）に、`nd` を `e`（向きを変えた先）などに変える。`w` は本文の $W$ に合わせて残してよい

## 台帳への提案

- abc176_d：evidence に https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc176-d.html を足す（執筆者の提案に賛成。コードで方針を確かめた）
- abc176_d・arc005_3・typical90_aq・abc213_e・abc246_e：summary と approach を上の資料で確かめたので、`checked: '2026-10-21'` を入れる
- 補充の候補 abc400_d（diff 1026）：ap.py で実在を確認。方針は確かめていない

## 総合の判定

小さな直しで可。直すべき 1 件（図の線とラベルの重なり）、直すとよい 6 件。本文の事実・計算量・証明・コード片・例の表はどれも確かめた範囲で正しい。
