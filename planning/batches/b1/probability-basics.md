# probability-basics の報告（工程8b）

- 書いたファイル：docs/comb/probability-basics.md、snippets/probability-basics/first-move.{cpp,yaml}、docs/img/probability-basics/two-dice.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「確率 DP・期待値 DP・期待値の線形性へのつながり」（anchor: next-steps）を足した（基礎のページの「上位の手法とのつながり」）
- 検査の結果：
  - check_pages --page probability-basics：エラー 0・警告 0
  - fix_problems --check：直すべき行 0
  - check_snippets snippets/probability-basics：コード片 1・期待と違う 0（cases は自作。問題の入出力例は使っていない）
  - textlint：エラー 0。警告 7（図の代替テキストの長さ、「(表, 表)・…」の組の読点、数式を含む文の長さ、かぎかっこ内の引用文や「〜に…に」の助詞の重複の検出。どれも読みやすさを確かめて残した）
- 使った出典（どれも付録 B のドメイン。新しいドメインなし）：
  - https://drken1215.hatenablog.com/entry/2019/05/19/224500_2 ：例題 abc126_c の方針（最初の目で場合分け、O(N log K)）
  - https://drken1215.hatenablog.com/entry/2021/03/02/190700 ：練習 abc193_d の方針（81 通り、順番を区別して数える、同じ数字は c(c−1)）
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0620_abc463 ：abc463_f の問いの確認（解説の部分だけ。本文には使っていない）
- 数値の確認：1 − (5/6)^4 = 671/1296、13/52 × 12/51 = 1/17、P(和 7 | 少なくとも一方が 3) = 2/11、2 回の最大値の期待値 161/36、E[X^2] = 91/6 は手計算で確かめた

## 台帳への提案

- abc126_c・abc193_d：summary・difficulty は台帳のままで問題なし
- catalog の problems_note のとおり練習が 1 問しかない。下の「問題の補充の候補」を参照

## 用語集への提案

- 同様に確からしい｜equally-likely｜起こりうる結果を根元事象に分けたとき、どれも同じ確率で起きること。このとき確率は場合の数の比になる（本文ではリンクしていない。用語集に足すなら確率の基本の #ratio へも誘導できる）
- 排反｜mutually-exclusive｜2 つの事象が同時には起きないこと。確率を足してよい条件。独立とは別の性質（本文ではリンクしていない）

## 手引きへの提案

- §6 の記法に、余事象 `$\overline{A}$`・条件付き確率 `$P(A \mid B)$` を足すとよい（本文の記法の行でそう書いた）
- §13-8 の「誤検出なら残してよい」の例に、図の代替テキストの文の長さ（120 字超）を足すとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc463_f（F. Senshuraku、diff 2127）：最後の試合の勝敗がランダムに決まった後、最多勝の選手から一様に優勝者を選ぶとき、各選手の優勝確率を mod 998244353 で求める。自分の試合の勝敗で条件付けし、同率の人数の分布（二項分布）と 1/k の和で全確率の公式を使う。裏付け https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0620_abc463 。frequency_evidence と problem-sets で #conditional に結び付けられているので、力試し（challenge）として足すのがよい。ただし基礎のページの力試しとしては重いので、role は main の判断に任せる
- math_and_algorithm_w（アルゴ数学 023. Dice Expectation、diff なし）：題名からは期待値の定義の練習に見えるが、第三者の解説を検索で見つけられず、問いを確かめていない（候補止まり）
- past202209_c（C. Biased Dice、diff なし）：題名からは確率の基本の練習に見えるが、問いを確かめていない（候補止まり）
- 基礎の練習として abc 茶〜緑の確率の問題（場合の数の比・余事象）を 1〜2 問足したいが、ap.py の題名検索（Dice・Coin・Probab）では確かな候補が見つからなかった。研究ノート 07 §2.3 の表でも茶〜緑帯の純粋な確率の問題は abc126_c・abc193_d だけ

## 未解決の点

- 動く図は作っていない（catalog の visual は null）。静的な SVG（2 個のサイコロの 6 × 6 の表。和 7 を塗り、1 回目が 3 の行を破線で囲む）を 1 枚置いた。SVG を描画して見た目は確かめていない（手元に描画の道具がない）。文字の位置は viewBox 640 × 400 の中に収まるように計算した
- ほかのページの節へのリンクは、draft の linearity-of-expectation の #sum-vs-expectation と #nonlinear だけ。stub のページ（complement・rational-mod・expected-value-dp・probability-dp・coupon-collector・inclusion-exclusion・cpp-io）へはページだけにリンクした
- 本文の「全確率の公式」の具体例（1〜N のサイコロとコイン）は例題 abc126_c と同じ型で、例題の小見出しへリンクした
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 3 回（WebFetch）、Web 検索 2 回、題名の確認に curl 2 回
