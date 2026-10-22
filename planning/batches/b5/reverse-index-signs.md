# reverse-index-signs の報告と提案（b5）

- 書いたファイル：docs/guide/reverse-index-signs.md（生成ブロック signs-phrase・signs-shape の外側だけ。中は変えていない）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）。complexity は案内のページなので null のまま
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0・警告1（確認問題 3 の題に数式を含むための文の長さの誤検出）。コード片・図は作っていない（visual は null）。Mermaid の流れ図を 1 つ置いた
- 問題：catalog の problems が空で、hub の目安（0〜3）の範囲なので載せていない

## 書いた構成

- 引き方と注意：3 つの向き（言い回し・式の形・題材と状況）、ページ内検索の勧め、流れ図、サインは保証でないこと、引く前の誤読の確認、表の列（レベル・準備中）の読み方
- 言い回しから引く：5 つの群の中身（gen_site.py の PHRASE_GROUPS に合わせた）と、生成ブロック
- 立てた式の形から引く：貰う形に直して右辺を見る、DP は dp-speedup-overview#shape-to-tool へ。生成ブロック
- 1 つのサインに複数の手法が当たるとき：K 番目・最小値の最大化・実数の出力・削除のクエリ・締め切り・最短距離・区間のクエリ・10^18 回の繰り返し・期待値・XOR の 10 の小見出し（anchor は kth・maximize-minimum・real-answer・deletion・deadline・shortest・range-query・huge-repeat・expectation・xor）。各「見分ける点 → 手法 → ページ」の表
- 題材から引く：patterns の 10 ページと twelvefold-way・graph-modeling の表
- 状況から引く：制約・名前・方針・迷い・遅い DP・提出の失敗・解説が読めないなどから案内のページへの表
- 確認問題 3 つ、参考 3 件

## 台帳への提案

なし（問題を載せていない）。

## 用語集への提案

- サイン｜sign｜手法を疑うきっかけになる、問題文の言い回し・求めるものの形・制約の形・立てた式の形。本教材では各ページの要点の「いつ使うか」に置き、逆引き辞典の表の行になる。

（本文ではリンクせず、引き方と注意の節の冒頭で定義した。足したら、その最初の「サイン」にリンクを張れる）

## 手引きへの提案

- 生成の表が古い：signs-shape の表で dp-speedup-overview が「（準備中）」のままになっている（今は draft）。gen_site.py の実行で直るはず
- stub のページへのリンクが多い：reverse-index-constraints・term-index・thinking-checklist・method-comparison・stress-testing・cheatsheet・cpp-reverse-index・advanced-ds-catalog・graph-modeling と patterns の 9 ページ（bracket-sequence 以外）へはページへのリンクにした。相手が draft になったら、次の節へ張り替えられる
  - patterns の各ページ → `#overview`（bracket-sequence の形にそろうなら）
  - method-comparison → 該当の比較の節（最短路・区間のクエリの組）
  - reverse-index-constraints → 帯の節
- 見分け方の節の扱い：言い回しの行を生成している以上、見分け方の表（手書き）とページの signs がずれうる。ページの signs を直すときに、この節の表も見直す決まりを §15 に置くとよい

## 問題の補充の候補

なし（hub の目安の範囲で、載せる必要がない）。

## 未解決の点

- 確認問題 1 の答えで示した行「一点の値の更新と区間の和の質問が交互に来る」（fenwick-tree の signs）と、確認問題 3 の行「遷移のコストが i と j の積の項を 1 つだけ含む」（cht の signs）は、生成の表の文言に頼っている。signs の文を変えたら確認問題も直す必要がある
- 群の説明は gen_site.py の PHRASE_GROUPS（kind の 1 つ目で分ける）に合わせた。PHRASE_GROUPS を変えたら、言い回しから引くの節の箇条書きも直す
- 「頂点数が数百で全点対ならワーシャルフロイド法」は、本文のページ（warshall-floyd）の記述に合わせた目安で、数値を断定していない

## 使った出典

- Motsu_xe「解法キーアイデア集」（motsu-xe.hatenablog.com）：誤読の例。check_noai で noai の指定がないことを確かめた（付録 B にない）
- algo-logic「競技プログラミングで解法を思いつくための典型的な考え方」（algo-logic.info）：題材・言い回しごとの束ね方。check_noai で確かめた（付録 B にない）
- chokudai「競技プログラミングの強みと「典型力」について」（chokudai.hatenablog.com）：典型の組合せと、解いた後に要素を言葉にする習慣。check_noai で確かめた（付録 B は chokudai.github.io だけ）
- kmyk.github.io（research の出典）も check_noai で指定なしを確かめたが、本文では使っていない
- 本文の見分け方の表は、各ページの本文（使い分け・該当の節）を読んで合わせた

## 使用量の目安

道具の呼び出し 約35回、Web 取得 3 回（curl）＋ check_noai 4 回。

## 検証の指摘への対応（b5）

- 直した：1（ナップサックの行を「選び方の数」に絞り、価値の最大の行を足して #not-undoable へ）・2（総和と最大化・最小化を 2 行に分け #top-down へ）・3（見出しを「最大値の最小化」に広げ、導入と 4 行目を山形・谷形の両方に）・4（Nim に限定し、制限つきは Grundy 数の XOR の行を足した）・5（いもす法の行に「区間への加算」、Union-Find の行に「削除だけ・先に全部読める」）・6（「値が 1 程度でも桁が足りず WA になりうる」）・7（誤読の列挙を並べ替え、自前の例「異なる」の値と添字・操作の回数の上限と下限・1 始まりを足した。chokudai の言い回しは言い直した。参考の注記も合わせた）・8b（「kind の 1 つ目」を消した）・9（検索の例を「K 番目」に）
- 8a：要点の文は直した。summary は執筆者が変えられないので下の提案にする
- 10：メインの gen_site.py の実行（執筆者の作業ではない）
- 採らなかったもの：なし
- textlint の警告 1（確認問題 3 の答えの文の長さ、数式による §13-8 の誤検出）は残る

## 指摘への対応から出た提案

- summary（front matter）を要点に合わせ「問題文の言い回しや求めるもの、立てた式の形から、疑う手法とページを引ける。同じ言い回しに複数の手法が当たるときの見分け方も添える。」に直す（指摘 8a）
- cpp/cpp-io.md#float-output の「大きな値は」も、有効数字 6 桁では値が 1 程度でも相対誤差が 10^-6 を超えうるので、持ち主に直しを頼む（指摘 6）
- gen_site.py を実行し、signs-shape の dp-speedup-overview の「（準備中）」を消す（指摘 10）
