# bell-number の報告（b2）

- 書いたファイル：docs/comb/bell-number.md、snippets/bell-number/stirling.{cpp,yaml}（範囲 core・bell）、snippets/bell-number/partition-xor.{cpp,yaml}（範囲 core）、docs/img/bell-number/stirling-table.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections[0] の title を引用符で囲んだ（カンマを含むため。手引き §14-13。文字は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致、textlint エラー 0・警告 12（数式を含む文の読点・長さ、図の代替テキストの長さ、「も」「に」「か」の重複の誤検出に近いもの）。SVG は render_svg.py の 360px・720px で目視した
- 使った出典：drken「写像12相を総整理」（漸化式）、yuulis.hatenablog.com の ABC390 D（check_noai で noai なしを確認。はてなブログの新しい書き手）、oraclesqlpuzzle の ABC390 D、drken の ABC310 D。atcoder.jp・codeforces.com は開いていない
- 数値（B_0〜B_30、S(n,k)、3^n、S(12,5) = 1379400 が S(12,·) の最大、Σ_{i<12} B_i = 820988）は Python で計算して確かめた

## 台帳への提案

- abc390_d・abc310_d：変更なし（本文の行は台帳と一致）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 集合の分割 | set-partition | 集合を、空でなく互いに共通部分のない部分集合（組）の集まりに分けること。組の並びと組の中の順番は区別しない。$n$ 個の集合の分割の数がベル数である |
| 全射 | surjection | 写像 $f: X \to Y$ で、$Y$ のどの要素にも $X$ のどれかの要素が写るもの。「$k$ 色をどれも 1 回以上使う塗り方」は $n$ 個から $k$ 色への全射で、その数は $k! \, S(n,k)$ |

（本文ではリンクを張らずに語だけを書いた。用語集に足したら最初の出現（導入の「集合の分割」、recurrence の節の「全射」）にリンクを張れる）

- 付録 A に「第 2 種スターリング数」「第 1 種スターリング数」を「スターリング数」と並べて足すとよい（ページの題名に使っているため）

## 手引きへの提案

- §14-13 の「title にカンマを含むときは引用符」は骨格の生成にも適用するとよい（骨格の sections[0] の title が `S(n,k)` のカンマで YAML の別項目に割れ、check_pages の schema エラーになっていた）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

練習が 1 問なので、vs-subset-dp の節の対比（B_N では間に合わず 3^N の DP にする）の練習として、台帳で確認済みの次の 2 問を bell-number の practice に足すことを提案する。

- dp_u（EDPC U. Grouping）：N 羽（N ≤ 16）のうさぎをグループに分け、同じグループの組の得点の和を最大化する。B_16 ≈ 1.0×10^10 で全列挙できず、部分集合の DP（3^16）にする対比になる。裏付け：https://qiita.com/Series_205/items/7d2c57b45179006d0bc6（台帳の evidence）
- typical90_as（典型90 045. Simple Grouping（★6））：N 点を K 個のグループに分け、グループ内の距離の最大の最大を最小化する。組の数つきの部分集合の DP（O(K·3^N)）の対比。裏付け：https://github.com/E869120/kyopro_educational_90/blob/main/editorial/045.jpg（台帳の evidence）

S(n,k) や B_n の値そのものを mod で問う ABC の問題は見つけられなかった（研究ノートの記述どおり、全射は包除原理の問題として出る）。

## 未解決の点

- frequency C のページで練習が 1 問しかない（上の補充が採られれば 3 問）
- related の `inclusion-exclusion#surjection` は相手が stub なので、本文ではページへのリンクだけにした。相手が draft になったら recurrence の節の包除の式の行を `#surjection` へ張り替える
- recursive-enumeration の #pruning の節がこのページの #size へリンクしたがっていた（b1 handoff 1.2）。#size は本文にあるので張り替えてよい。complexity-estimation:138 のページへのリンクも #size に張り替えられる
- 図は visual priority 3（静的）なので SVG 1 枚で済ませた。B_n の増え方は本文の表で示した

## 検証の指摘への対応（b2 verify）

- 1（図の矢印）：直した。×1・×3 のラベルを元のセル（S(4,2)・S(4,3)）に直接置き、凡例を「×1：…　×3：…」に変えて線種への依存をなくした。2 本とも実線にし、矢じりは 25 のセルの上端（y=261）で止めた。render_svg の 360px・720px で目視
- 2（法の条件）：直した。「$k!$ の逆元が要るので、法は $k!$ と互いに素（$k$ より大きい素数なら満たす）」
- 3（T! 回ずつ）：直した。「どの組も空でない割り当てに限っても同じ分け方を T! 回ずつ数える」
- 4（N = 13 の目安）：直した。N = 13 の行を足した（B_13 ≈ 2.8×10^7、葉 1 つ O(1) が必須）
- 5（練習が 1 問）：採らなかった（執筆者は書けない）。台帳の dp_u・typical90_as の pages に bell-number（role: practice）を足す必要があり、共有ファイルなのでメインの判断に回す。提案は上の「問題の補充の候補」のとおり。採るなら本文の practice に 2 行と「練習の方針」を足す
- 6（#surjection）：直した。recurrence の節の包除原理のリンクを `../comb/inclusion-exclusion.md#surjection` に張り替えた（相手の見出しに {#surjection} があることを確かめた）。使い分けの節のリンクはページ全体のままにした
- 7（reserve の定数）：直した。同じ行に「// N <= 12 なら葉は B_12 = 4213597 個以下」を足した
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致、textlint エラー 0（警告 12）
