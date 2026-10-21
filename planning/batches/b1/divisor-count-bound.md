# divisor-count-bound（約数の個数の上界と高度合成数）の執筆の報告

- 書いたファイル：docs/math/divisor-count-bound.md、snippets/divisor-count-bound/divisor-dp.{cpp,yaml}、snippets/divisor-count-bound/hcn.{cpp,yaml}、docs/img/divisor-count-bound/dfs-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の pitfalls の title を「落とし穴（約数の個数を √N と見積もる・10^18 の約数の列挙に O(√N) かかる）」に直した（anchor はそのまま。見出しと title をそろえるため。手引き §13.2）
- 検査の結果：check_pages --page divisor-count-bound はエラー・警告とも 0。check_snippets は 2 本とも期待どおり。textlint はエラー 0、警告 12（数式を含む文の長さ・読点の数、数式をはさんだ「は」「で」の重なりで、誤検出として残した）。fix_problems --check はこのページの直すべき行 0（math/harmonic-sum.md に 7 行あるが、別の担当のページなので触っていない）
- 表の数値（d(n) の最大・達成する最小の数・ω(n) の最大）は、snippets の hcn.cpp と同じ方法の Python で 10^3〜10^18 について計算し直し、research/06 §6.3 の表と一致することを確かめた。10^10 の 2304（6983776800）は ikatakos 氏の abc461_f の記録の値とも一致
- 図：visual は priority 2（static）。表は Markdown の表にし、DFS の木を SVG（N = 60）にした。描画の道具が手元になく、見た目は目で確かめていない
- 使った出典：drken1215（arc167_b・acl1_b・カテゴリ「数量が小さいことの活用：約数の個数」）、github.com（E869120 の典型90 085 の解答例）、ikatakos.com（abc461_f・abc475_g の解法の部分だけ）。新しいドメインはなし（drken1215 のカテゴリページを check_noai で確かめ、指定なし）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc461_f | summary | 相異なる正の整数からなり、総積が N になる数列すべてについて要素の総和を足し合わせ、998244353 で割った余りを求める（N ≤ 10^10）。 | 今は「（執筆時に確かめる）」。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0606_abc461 （解法の部分）。本文の行はこの値で書いた |
| abc461_f | approach | N の約数を品物にし、積の番号と長さを状態にしたナップサック風の DP。集合で数えて最後に長さの階乗を掛ける | 同上。research の分類の注記を外す |
| arc167_b | summary | A^B の正の約数をすべて掛けた積が A で何回割り切れるかを、998244353 で割った余りで求める（A ≤ 10^12、B ≤ 10^18）。 | 「全て」が prh のエラー（すべて）。本文の行は「すべて」で書いた。制約は https://drken1215.hatenablog.com/entry/2024/01/31/220502 |
| arc167_b | approach | 約数の積は M^{d(M)/2}。指数 B·Π(B e_i + 1) の半分を、偶奇を mod の前の値で判定して求める | 同上 |
| abc475_g | approach | 指数が単調に減る形の候補を列挙し、D の倍数になる枝は素数を替えるか捨てる。素数ごとの指数に上限を設けて候補を絞る | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0912_abc475 （解法の部分）。制約 N, D ≤ 10^18、T ≤ 10 も summary に足すとよい |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 高度合成数 | highly-composite-number | 自分より小さいどの正の整数よりも約数の個数が多い正の整数（1, 2, 4, 6, 12, 24, 36, …）。N 以下で約数の個数が最大になる数は、N 以下で最大の高度合成数である |

- 本文では高度合成数をページ内で定義しているので、用語集はなくてもよい。term-index にはすでに別名で載っている

## 手引きへの提案

- 骨格の sections に落とし穴の節が anchor `pitfalls` で入っているページでは、§13.1 の定型の見出し「## 落とし穴 {#pitfalls}」と、§13.2 の「見出しと title を同じにする」がぶつかる。ほかのページ（binary-search など）にならって「落とし穴（…）」の title にしてそろえたが、どちらにするかを手引きに書いておくとよい

## 問題の補充の候補

- **abc300_e**（E. Dice Product 3、diff 1354、台帳で確認済み）：サイコロの目を掛けていき積がちょうど N になる確率。現れる値が N の約数（2・3・5 の積）に限られ、メモの大きさが d(N) で抑えられる。divisor-dp の節の「メモ化再帰でも同じ」の練習に向く。裏付け：https://drken1215.hatenablog.com/entry/2023/05/03/212600 （drken の「数量が小さいことの活用：約数の個数」カテゴリ）
- **abc212_g**（G. Power Pair、diff 2150、台帳で確認済み）：P − 1 の約数ごとに φ(d) を求めて数える（P ≤ 10^12）。約数ごとに重い処理をしても間に合う型の力試しに向く。裏付け：https://drken1215.hatenablog.com/entry/2021/08/01/163600
- **abc335_g**（G. Discrete Logarithm Problems、diff 2614、台帳で確認済み）：P − 1 の約数を使って位数を求める。発展なので候補にとどめる。裏付け：https://drken1215.hatenablog.com/entry/2024/01/07/220400
- abc319 以降の水（E 相当）でこのページの例題になる ABC は見つからなかった。例題は catalog どおり arc167_b のままにした。arc167_b は「約数の個数の上界」よりも「約数の個数の公式と偶奇」の問題なので、上界の見積もりそのものが鍵の例題としては typical90_cg の方が近い。例題と練習の入れ替えを検討してほしい（typical90_cg は difficulty がない）

## 未解決の点

- dfs-tree.svg の見た目（文字の重なり）を描画して確かめていない
- 「約数の個数はおおよそ ∛N 程度」は経験則として書いた（表の値で、10^9 以下では ∛N の数倍まで、10^12 以上では ∛N 未満であることを確かめた）。定理ではないことが伝わる書き方にしたつもりだが、検証で見てほしい
- abc475_g の方針は ikatakos 氏の記録の要約にとどめた（指数の上限の根拠は記録でも一部「未証明」とされている）。本文では上限の具体的な値を書いていない
- divisor-enum・crt は同じバッチで draft になっており、`divisor-enum#count-and-sum`・`crt#applications`・`crt#acl1_b` にリンクした。anchor が変わったら直す
