# b5 提案：dp-speedup-overview（DP の高速化の選び方、hub）

- 書いたファイル：docs/dp/dp-speedup-overview.md、docs/img/dp-speedup-overview/read-ranges.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない（catalog にある pitfalls は §14-1 に従い定型の `## 落とし穴 {#pitfalls}` で置いた）
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0（警告15：数式・リンクの角括弧の誤検出、表の行・折りたたみ内の文の長さ、要点の計算量の列挙の「が」の重複）
- 図：read-ranges.svg（幅 400、3 段：接頭辞・右へ動く窓・値で決まる飛び飛びの集合）。render_svg.py で 360px・720px を目視
- 使った出典：E869120 典型90 090 の解説画像（github.com、付録 B にある）。新しいドメインなし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_cl | summary | 長さ N の 0 以上の整数の列のうち、どの区間でも（区間の最小値）×（区間の長さ）が K 以下になるものの個数を、998244353 で割った余りで求める。 | https://github.com/E869120/kyopro_educational_90/blob/main/editorial/090-02.jpg （条件）・090-01.jpg（mod）・090-05.jpg（N ≤ 10^9, K ≤ 10^5） |
| typical90_cl | approach | 高さの大きい順の区間 DP を（高さ, 長さ）の状態に減らし、高さごとの線形漸化式を高速きたまさ法・Bostan-Mori で解く | 同上 090-03〜05.jpg |
| typical90_cl | evidence | 090-03.jpg〜090-05.jpg を足す（解法の本体は P3〜P5） | 同上 |

## 用語集への提案

なし（state・transition・convex-function は既存の項目にリンクした）。

## 手引きへの提案

- §4 の hub の構成に「何から引くか → 道具 → ページ → 例題」の表で、例題の列は相手のページの例題の小見出し（`../dp/cht.md#dp_z` など）か `#practice` へリンクする形を、hub の書き方の例として足すとよい（このページはその形で書いた。問題の囲みの外に atcoder.jp へのリンクは置いていない）
- dp-basics・dp-prefix-sum・dp-segment-tree はこのページを「DP の高速化の全体像」、matrix-power は「DP の高速化の一覧」とリンクの文字で呼んでいる。題名「DP の高速化の選び方」にそろえるかはメインの判断（リンク先は有効）

## 問題の補充の候補

hub の目安（0〜3 問）に収まるので、補充は要らない。表の例題の列はすべて相手のページに載った問題で足りた。

## 未解決の点

- 早見表の「右へ動くだけの窓の min・max」の行は、dp-segment-tree#dp-sliding-window に例題の小見出しがないので例題の列を「—」にした。monotonic-stack#dp-transition の擬似コードが同じ形なので、そちらにも例題がつけば埋められる
- 典型90 090 の第三者の解説は公式の解説画像 1 本だけで確かめた（解答コードは GitHub の API の回数制限で一覧を取れなかった）。§15-6 の「2 つ以上」は満たしていない
- 確認問題の「1〜K 段進める階段」の行列累乗の見積もり（50^3 × 60 = 7.5×10^6）、本文の n = 100・500 の見積もりは手で計算した値

## 検証の指摘への対応

- 1（直すべき）：早見表の Monge の行を 3 行に分けた（前の段が確定した形 → monotone minima・#monotone-minima、段のない形 → LARSCH・分割統治・#smawk-larsch、区間 DP → Knuth-Yao・#knuth-yao）。#convexity の表の道具も「monotone minima・LARSCH・Knuth-Yao」にした
- 2：「上に凸な列どうしの (max,+) 畳み込み（下に凸なら (min,+) 畳み込み）」に直した
- 3：read-ranges.svg の ①・② の行のラベルを「j」にした
- 4：「表の読み方」の 1 つ目の項目の文を 2 つに切った
- 5：動的 DP の行を表の最後へ移し、導入を「おおむね上の行ほど易しく」、注意を「CHT から下は発展」（動的 DP は遷移を行列に書き直す手間がかかる、と 1 文足した）にした
- 採らなかった指摘：なし
- 台帳への追加の提案：typical90_cl の `checked` に 2026-10-22 を入れる（検証役が解説画像 P1〜P5 で問い・制約・方針を確かめた）
