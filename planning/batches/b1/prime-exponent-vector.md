# prime-exponent-vector の報告（工程8b・b1）

- 書いたファイル：docs/math/prime-exponent-vector.md、snippets/prime-exponent-vector/square-pairs.{cpp,yaml}、snippets/prime-exponent-vector/lcm-mod.{cpp,yaml}、docs/img/prime-exponent-vector/exponent-bars.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: XOR 基底・集合のハッシュ・半分全列挙へのつながり, anchor: next-steps}`（level はページと同じ基礎）を足した
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 期待と違う 0（2 片）／fix_problems --check で本ページの直すべき行 0（harmonic-sum.md の 7 行が出るが、別の執筆者の担当）／textlint エラー 0、警告 8（問題の行の長さ、数式を含む文の長さ、助詞の重複の誤検出に近いもの）
- 図：静的な SVG を 1 枚（catalog の visual の priority 2：360 と 84 の指数の棒、lcm は高い方・gcd は低い方）。手元に SVG の描画の道具がなく、目視の確認はしていない（座標は計算で配置）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc150_d | summary | 「全ての k で」→「すべての k で」（prh の規則。本文は直した） | style-guide §7 |
| abc300_g | alternatives（prime-exponent-vector）の summary | 「素因数が全て P 以下」→「素因数がすべて P 以下」（本文は直した）。approach は「二分探索」より「尺取りか二分探索」が evidence に合う（drken の記事は尺取り） | https://drken1215.hatenablog.com/entry/2023/05/02/234200 |
| agc003_d | summary | 「どの2つを」→「どの 2 つを」（本文は直した） | style-guide §7 |
| typical90_y | approach / evidence | evidence（作問者の解答コード）は桁の多重集合を非増加順に列挙する方法で、2^a 3^b 5^c 7^d の列挙ではない。approach を「桁の積の候補（桁の多重集合、または 2^a 3^b 5^c 7^d の形）を全て列挙して確かめる」とするか、7-smooth 数の列挙を説明する第三者の解説を evidence に足す。10^11 以下の 7-smooth 数は 10688 個（手元で計算） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/025.cpp |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| squarefree（平方因子を含まない） | squarefree | 1 より大きい平方数で割り切れない正の整数のことである。素因数分解したとき、どの素数の指数も 1 以下になる。1 も含める |

（本文の「核」はページ内で定義した呼び方で、用語集には足さなくてよい）

## 手引きへの提案

- 台帳の summary が prh・空白の規則に反すると textlint がエラーにするため、§13.7（本文だけ直さず提案する）と §13.8（エラー 0）が両立しない。fix_problems は要約を書き換えないので、本文を直して提案に書いた。どちらを優先するかを手引きに書くとよい

## 問題の補充の候補

- 確認済みの問題で例題 1・練習 3・力試し 3 がそろうので、補充は必須ではない
- 候補（未確認、台帳は書いていない）：「指数をそろえる操作」の型（2 で割る・3 で割るなどの操作で全要素を等しくする）は練習に問題がない。ap.py と第三者の解説で ABC から探す価値がある。本文では型だけを書いた

## 未解決の点

- 単一の素数の節の「指数をそろえる操作」の段落は、裏付けた問題がない一般論として書いた。問題が見つからなければ短くしてよい
- 力試し AGC003 D の「√[3]{10^10} 程度までの素数で割った後の残りが 1・p・p²・pq」は drken の記事（2500 までの素数で試し割り）に基づく
- ABC150 D の数え方 ⌊(⌊M/L⌋ + 1)/2⌋ は drken の記事による（L = lcm(a_k/2)）
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 7 回（drken の記事 6、GitHub 1。どれも付録 B のドメイン）

## 検証の指摘への対応（工程8b・b1）

- 指摘 1（直すべき）：「指数をそろえる操作」の段落に、そろえる先の基準（割るだけなら最小、掛けるだけなら最大、両方向なら中央値）を書いた
- 指摘 2〜5（直すとよい）：すべて採った。2 は「約 6×10^9 回」に、3 は complexity を値の上限 M の記号にそろえ、4 は図の目盛り・棒の数値・p のラベル・下の 3 行を font-size 16 に上げ、5 は「√[3]{10^10} ≈ 2154 以上（たとえば 2500）」と、相手の正規形が 10^10 を超えるなら無条件に選べることを足した
- 台帳への提案：検証の「台帳への提案」（abc150_d・abc300_g・agc003_d の checked を 2026-10-21 に、abc300_g の approach、typical90_y の approach）に賛成する
