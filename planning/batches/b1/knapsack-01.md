# knapsack-01 の報告（工程8b・バッチ b1）

- 書いたファイル：docs/dp/knapsack-01.md、snippets/knapsack-01/（zero-one・unbounded-count・bounded-binary の各 .cpp と .yaml）、docs/img/knapsack-01/rolling-direction.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の 1 つ目の title を `dp[i][w] の意味…` から `dp[i][j] の意味…` に変えた（本文の添字を j にそろえたため。anchor は meaning のまま）。節 `上位の手法とのつながり`（anchor next-steps、level はページと同じ）を足した
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 3 組で期待と違う 0。textlint エラー 0、警告 14（台帳から作る問題の行・参考の行の文の長さと助詞の重なり、数式の中のカンマを数える max-comma など。本文の直せるものは直した）
- 使った出典：kyopro-friends.hatenablog.com（EDPC D の制約と表）、qiita.com/drken（以下・ちょうどの初期値、価値の DP の答え）、programming-hiroba.com（abc286_d・abc344_d・abc317_d）、ikatakos.com（abc153_e・abc373_f、解説の部分だけ）、qiita.com/sano192（abc219_d）、oraclesqlpuzzle.ninja-web.net（abc032_d）。問題の補充の候補のために drken1215.hatenablog.com（arc073_b）と kazun-kyopro.hatenablog.com（abc289_d）を読んだ。新しいドメインはない
- 動く図：priority 1 の置き場の div だけを「dp[i][j] の意味」の節に置いた（下記）

## 動く図の仕様（knapsack-table）

- 置き場：`<div class="kp-viz" data-viz="knapsack-table" data-config='{"W": 5, "items": [{"w": 2, "v": 3}, {"w": 1, "v": 2}, {"w": 3, "v": 4}], "mode": "at-most"}'></div>`
- 内容：品物 × 重さの表（行 0〜N、列 0〜W）を 1 行ずつ、1 マスずつ埋める。選ばない遷移は真上のマスから真下への矢印、選ぶ遷移は w_i 左の前の行のマスから斜めの矢印。max を取った側を強調する。caption に式の値（例：`dp[2][3] = max(dp[1][3], dp[1][2] + 2) = 5`）
- 後半（または mode の切り替え）：1 次元の配列を大きい方から・小さい方から更新する 2 本を並べ、同じ段で書き換えた値を読む矢印を別の色・線種で示す（静的な図 rolling-direction.svg と同じ例：品物 1 個、重さ 2・価値 3、W = 6）
- config の mode は at-most（以下）と exact（ちょうど。初期値 −∞ を「−」で表示）を想定。本文の例の最後の行は 0, 2, 3, 5, 6, 7、答え dp[3][5] = 7

## 台帳への提案

- abc032_d｜evidence｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc032-d.html を足す｜今の evidence（drken の Qiita）は類題の一覧に名前があるだけで、3 種類の制約での切り替えを裏付けていない。oraclesqlpuzzle のコードで N ≤ 30 は半分全列挙、重さ ≤ 1000 は重さの DP、それ以外は価値の DP の 3 分岐を確かめた
- dp_d・abc286_d・abc344_d・abc317_d・abc153_e・abc219_d・abc032_d・abc373_f｜checked｜2026-10-21｜各 evidence の解説で問いと方針を確かめた
- abc373_f｜approach｜「k 個目の増分 v − (2k − 1) が減るので、重さの余りごとに分けると最適な遷移元が単調になる（Monotone Minima で O(NW log W)）」に補う｜ikatakos の解説

## 用語集への提案

- なし（状態 `state` は既存の anchor にリンクした）

## 手引きへの提案

- §5 の dp か §13 に「1 次元化の判断の基準」を一言：in-place で書けるかは「同じ段で書き換えた値を同じ段で読むか」で決まり、グループから 1 つ選ぶ遷移は 1 本の配列では書けない。執筆の途中で「上限で打ち切る遷移も 1 本では書けない」と誤って書きかけたが、大きい方から配れば遷移先は遷移元以上なので正しく計算できる（検証役にも、この点を確かめてもらいたい）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- arc073_b（D. Simple Knapsack、diff 1477）｜重さが w_1〜w_1 + 3 の 4 種類しかない 0-1 ナップサック。重さごとに価値の降順の累積和を作り、何個取るかを全探索（O(N^4)）。「計算量で解法を切り替える」節の 4 行目（重さの種類が少ない）の代表。練習（水の節）向き｜https://drken1215.hatenablog.com/entry/2024/10/19/042434
- abc289_d（D. Step Up Robot、diff 551）｜決まった歩幅を何度でも使い、罠の段を避けてちょうど X 段に着けるかの可否 DP。個数制限なしの易しい練習｜https://kazun-kyopro.hatenablog.com/entry/ABC/289/D
- abc054_d（D. Mixing Experiment、diff 1655）｜2 種の薬品の量を状態にした費用の最小（2 次元のナップサック）。調査レポート 02 §5.1 の候補。今回は解説を読んでいない｜https://drken1215.hatenablog.com/entry/2019/02/15/205900

## 未解決の点

- 図 rolling-direction.svg は手元に SVG の描画の道具がなく、表示を目で確かめていない（座標を計算しただけ）。検証役に表示の確認を頼みたい
- 本文で触れた dp-basics・subset-sum・dp-dimension-reduction・dp-reconstruction・knapsack-undo・exchange-argument-dp・tree-dp-square・divide-and-conquer・monotonic-stack は stub なので、ページへのリンクだけにした（meet-in-the-middle#vs-knapsack は draft なので節へリンクした）。divide-and-conquer#range-knapsack も節が書かれたら節へのリンクに直せる
- 個数制限付きの節の「余りごとのスライド最小値」の式は自分で導いて書いた（cp-algorithms は CC BY-SA のため読んでいない）。検証役に式の確認を頼みたい
- abc373_f の方針は ikatakos の解説の Monotone Minima による解法だけを確かめた。公式の解法（重さごとに優先度付きキューで増分を選ぶ方法）は確かめていないので書いていない
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 11 回（ほかに題名の確認のための curl）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜9 はすべて直した（1：$\pm\infty$ とあふれの説明を書き直し、2：グループを $j$ 外側の 1 本で書く形を本文・確認問題・落とし穴に追記、3：$S$ を定義、4：「減らない」、5：$\mathrm{dp}'$ の定義・$\max(0, q - b_i)$・窓の最大の一言、6：bounded-binary の `b`・`rest`・`k`・`c` を `long long` に、7：$NW \le 10^8$ の目安と $N \cdot W_1 \cdot W_2$、8：打ち切りを 1 本の配列で配る向き、9：部分木のサイズで抑える条件）
- 採らなかったもの：なし（指摘 10 はメインの作業なので下の提案へ）

### 提案（メインへ）

- **front matter の signs**（共有の要点にも出る）：`N ≤ 100〜5000、W ≤ 10^4〜10^5（O(NW) が通る）` は $N = 5000$・$W = 10^5$ も通ると読めるので、`NW ≤ 10^7〜10^8（O(NW) が通る）` などへの変更を提案する（指摘 7）
- **動く図 knapsack-table**：`overrides/assets/js/viz/knapsack-table.js` と試験の作成の依頼。仕様は先の報告のとおり（本文の例 W = 5、最後の行 0, 2, 3, 5, 6, 7 と config は一致を検証済み）（指摘 10）
- **執筆者の手引きへの提案の訂正**：先に書いた「グループから 1 つ選ぶ遷移は 1 本の配列では書けない」は誤り。「グループの品物を 1 つずつ配列全体に反映すると混ざる。$j$ を外側（大きい方から）、品物を内側にすれば 1 本でも書ける」と直して扱ってほしい（指摘 2）
- **台帳**（検証役が確かめた分）：dp_d の evidence に https://kyopro-friends.hatenablog.com/entry/2019/01/12/230931 を追加／abc373_f checked 2026-10-21（ikatakos の解説で問いと方針を確認）／abc344_d checked 2026-10-21（プロひろの解説で確認）／abc032_d の evidence 追加は先の提案のとおり
