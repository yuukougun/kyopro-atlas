# union-find の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/union-find.md、snippets/union-find/{own-dsu,acl-cycle}.{cpp,yaml}、docs/img/union-find/path-compression.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 上位の手法へのつながり, anchor: next-steps}` を足した（基礎の目安の「上位の手法とのつながり」の置き場）。既存の節の title・anchor は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件すべて一致）、textlint（エラー 0・警告 4）
  - 残した警告：39 行の sentence-length（要点の囲みの「いつ使うか」の入れ子の箇条書きを 1 文と数える誤検出。見本のページと同じ）、98 行の max-comma（図の代替テキストの中の配列 par の数の列）、223 行・224 行の no-doubled-joshi（abc206_d・abc157_d の要約。台帳の summary から作る行なので本文では直さず、下の台帳への提案に書いた）
- 動く図：JS は書いていない。置き場の div を「各操作の手順」の節に置いた（図の前後の文章も書いた）。仕様は下の「動く図の仕様」
- 使った出典：ACL の document_ja/dsu.md と third_party/ac-library/atcoder/dsu.hpp（v1.6）、けんちょんのはてなブログ 4 本（practice2_a・abc177_d・abc206_d・abc157_d）、kyo-pro のはてなブログ 2 本（abc288_c・abc292_d）、E869120 の典型 90 問の解答例 012（GitHub）。候補探しで oraclesqlpuzzle（abc350_d）を読んだ。どれも付録 B のドメインで、新しく noai を確かめたドメインはない
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 10 回（うち 404 が 2 回）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc206_d | alternatives（union-find）の summary | 「値を別の値に一括で置き換える操作を繰り返し、数列を回文にするための最小の回数を求める。」（「で」の重なりを解く） | https://drken1215.hatenablog.com/entry/2021/06/26/165800 |
| abc157_d | alternatives（union-find）の summary | 「各人について、同じ成分にいて、友達とブロック相手のどちらでもない人の数を答える。」（「でも」の重なりを解く） | https://drken1215.hatenablog.com/entry/2020/03/02/022900 |
| abc288_c・abc292_d・abc177_d・practice2_a・typical90_l | — | 変更なし。summary・approach は evidence の解説と食い違いがなかった | 各 evidence |

- abc292_d の approach（「根に頂点数と辺数を持たせる」）は、kyo-pro の解説ではすべての併合のあとで各頂点の辺数を根に足し込む形である。どちらでも解けるので台帳は変えなくてよいが、本文の方針には両方を書いた

## 用語集への提案

- 代表元｜representative｜Union-Find などで、グループを代表する 1 つの要素。Union-Find では木の根で、2 要素が同じグループかを代表元が同じかで判定する（本文の「保つ性質」の節からリンク済み）
- ならし計算量｜amortized-complexity｜操作を何回も続けたときの合計の計算量を回数で割ったもの。1 回だけなら重いこともあるが、合計では上限に収まる。Union-Find・vector の push_back・尺取り法などで使う（本文の「なぜ速いか」の節からリンク済み。計算量の用語の節に置くとよい）

## 手引きへの提案

- 基礎の technique の目安（§4）の「上位の手法とのつながり」は、定型の見出し（§13.1）にない。binary-search の執筆者も同じ点を挙げている。今回は sections に `next-steps` を足して中身の節として扱った（binary-search-answer の `next-steps` と同じ anchor）。定型の見出しにするなら `## 上位の手法へのつながり {#next-steps}` を §13.1 に足すのがよいと考える
- sections に `choosing`（使い分け）がある骨格では、定型の `## 使い分け {#comparison}` と重なる。今回は sections の choosing だけを置き、comparison は置いていない。どちらにそろえるか決めてほしい

## 動く図の仕様（priority 1、名前 union-find）

- 置いた div：`<div class="kp-viz" data-viz="union-find" data-config='{"n": 8, "ops": [{"type": "merge", "a": 0, "b": 1}, {"type": "merge", "a": 2, "b": 3}, {"type": "merge", "a": 0, "b": 2}, {"type": "merge", "a": 4, "b": 5}, {"type": "merge", "a": 6, "b": 7}, {"type": "merge", "a": 4, "b": 6}, {"type": "merge", "a": 0, "b": 4}, {"type": "find", "x": 7}]}'></div>`
- 状態：森（各要素の par）と、配列 par の表示（根は −(大きさ)）。merge は「a の根を求める → b の根を求める → 大きさを比べる → 小さい方の根を大きい方の根の下へ」を 1〜2 ステップに分け、大きさが同じなら a 側の根を残す（ACL と同じ）。find は根までたどる道を 1 段ずつ強調し、帰りがけに親を根へ書き換える
- 最後の状態は静的な図 path-compression.svg の右側と一致する（par = [−8, 0, 0, 2, 0, 4, 0, 0]）。merge の途中の find でも経路圧縮が起きるが、この ops では深さ 2 以下の要素しかたどらないので形は変わらない（0 と 4 の併合では 0・4 は根）
- caption の例：「find(7)：7 → 6 → 4 → 0 と 3 回たどって根 0 を見つけた」「7 と 6 の親を根 0 に書き換えた（経路圧縮）」

## 問題の補充の候補

- abc350_d（D. New Friends、diff 773、ap.py で実在と difficulty を確認。台帳になし）：友達の友達と友達になる操作を繰り返したとき、新しく増える友達の組の数の最大を求める。各連結成分で「頂点数 s の完全グラフの辺数 s(s−1)/2 − 今ある辺数」を足す。根に頂点数と辺数を持たせる型と、積の `long long` の練習になる。練習（practice）での追加を提案する。裏付け：https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc350-d.html
- abc319 以降の問題は、基礎のページの要件でないため探していない（frequency_evidence の recent の abc451_e は台帳で tree-construction の例題で、Union-Find は道具として使うだけなので載せていない）

## 未解決の点

- 図 path-compression.svg は描画して目で確かめる道具（rsvg-convert・cairosvg）がなく、XML として読めることと座標の計算だけを確かめた。文字のはみ出しや矢印の重なりの確認を検証役に頼みたい
- 「経路圧縮だけでならし O(log N)」「両方でならし O(α(N))（Tarjan）」「α(N) は 10^80 程度でも 4 以下」は、research/05-ds の記述（cp-algorithms を参照）と drken の practice2_a の記事に基づく。原論文では確かめていない
- 確認問題 (1) の答えで「経路圧縮だけだと一時的に深い鎖ができうる」と書いた。これは大きさを見ずにつなぐ例（鎖を作る併合の順）からの推論で、資料での裏付けはない

## 検証の指摘への対応（verify/union-find.md）

- 1〜6・8：本文・図・コード片を直した。4 は図の文字を 16〜18 に上げ（viewBox の高さを 450 に）、5 は赤の marker を 3.5 にして矢じりを黒と同じ大きさにした
- 7：コード片のコメントと ACL の囲みは「大きさ」にそろえた。front matter の sections の title（「parent は根なら −(サイズ)」「サイズの積のあふれ」「根にサイズ・辺数を持たせる」）と、それに合わせた本文の見出しは執筆者の担当外なので残した。下の提案を参照

## 提案（検証の指摘から）

- sections の title の用語：本文に合わせ、invariants を「保つ性質（各グループは根付き木で、根が代表元。par は根なら −(大きさ)）」、boundaries の「サイズの積のあふれ」を「大きさの積のあふれ」、size-and-edges を「根に大きさ・辺数を持たせる（…）」にそろえることを提案する（本文の見出しも同時に直す）
- 台帳の abc177_d の alternatives（union-find 向け）の summary に「友達の友達も友達とみなすとき、」を足すことを提案する（主の summary にはある）
