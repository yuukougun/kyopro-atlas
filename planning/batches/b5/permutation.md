# permutation（順列と置換）の報告と提案

- 書いたファイル：docs/patterns/permutation.md、snippets/permutation/inverse.{cpp,yaml}、snippets/permutation/rank.{cpp,yaml}、docs/img/permutation/arrows.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `overview`（問われ方と手法の一覧。見本の bracket-sequence に合わせた）を足した。`repeat` の title の「サイクルごとの周期」を「巡回ごとの周期」に直した（§7「置換は巡回と言う」）。anchor は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも期待どおり、textlint エラー 0（警告 16。数式の中の読点による読点の数・文の長さ、数式を挟んだ助詞の重複の誤検出）
- 図：arrows.svg（幅 400）を render_svg.py で 360px・720px の PNG にして目で確かめた。visual は priority 2 の静的な図なので、動く図の置き場は作っていない
- 使った出典：qiita.com/comet725（ABC470 D）、drken1215.hatenablog.com（ABC150 C）。どちらも付録 B にあるドメイン。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
|---|---|---|---|
| abc470_d | summary | 順列に対して、2 か所の値の入れ替えと、列を逆置換に置き換える操作を順に行った後の列を求める。 | https://qiita.com/comet725/items/5b5dd4fa2d26f8b73f9a （本文の行はこの要約で書いた） |
| abc470_d | approach | 位置 → 値と値 → 位置（逆置換）の 2 つの配列を同時に持ち、入れ替えでは両方を書き換え、逆置換への置き換えでは 2 つの配列の役目を入れ替える（どの操作も O(1)） | 同上 |
| abc470_d | evidence | 2 つ目の裏付けが見つかっていない（ikatakos 氏の ABC470 の記録は E〜G だけで D がない）。§15-6 の 2 つ以上の目標に届かない | — |

## 用語集への提案

| 語 | anchor | 定義 |
|---|---|---|
| 逆置換 | inverse-permutation | 順列 $P$ に対し、値 $v$ のある位置を $Q_v$ とした順列 $Q$（$Q_{P_i} = i$）である。$i \to P_i$ の矢印の向きを逆にしたもので、巡回の分け方と長さは $P$ と同じになる。 |
| 恒等置換 | identity-permutation | すべての $i$ で $P_i = i$ となる置換、すなわちソート済みの列である。どの置換と合成しても相手を変えない。付録 A に正規形はあるが用語集に項目がない。 |

本文ではどちらもリンクを張らず、本文で定義した。用語集に入ったら、題材の性質の節の最初の出現にリンクを張れる。

## front matter・catalog への提案

- summary の「i → P_i の矢印のサイクル」を「i → P_i の矢印でできる巡回」に直す（§7「置換は巡回と言う」。要点の囲みは「巡回」で書いた）。index/patterns・lists/kind-counting の文も gen_site で追従する
- catalog の lexicographic の title にある「（binomial-coefficient, bit-full-search）」は front matter で落ちている。front matter が正なので本文は front matter の title に合わせた（変更は不要と考える）

## 手引きへの提案

- pattern の構成（§4）に「問われ方と手法の一覧 `{#overview}` を sections に載せる」と書き足すとよい。見本の bracket-sequence は持つが、骨格の permutation には無かった
- 定型の節ではない「節の中の小さな表」（数え上げの条件の形 → 手法 → ページ）を pattern のページで使ってよいかを明記するとよい（本文では counting の節で使った）

## 問題の補充の候補

- なし（練習 2 問で patterns の目安 0〜3 に入る。例題は 0 問で目安 0〜1 に入る）
- 余力があれば辞書順の行の練習に ABC276 C. Previous Permutation（diff 389、ap.py で実在を確認）が合いそうだが、第三者の解説で問いと解き方をまだ確かめていない

## 未解決の点

- 表の「代表の問題」の列には、このページの囲みにない問題（ABC436 E・ABC350 C・ABC190 F・ABC470 F・ABC377 E・ABC367 E・EDPC T・ABC134 E）の label を文字だけで書いた（catalog の problems_note に従った）。行き先のページでの役割は台帳で確かめた（abc350_c は construction の練習、abc377_e は permutation-cycles などの練習、abc367_e は doubling の練習）
- 逆置換の節の「値 1〜k の位置が連続しているか」の型は問題 ID を出していない（台帳に該当する問題を探していない）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 3 回（うち 1 回は D の記載がなく不採用）

## 検証の指摘への対応（2026-10-22）

- 直すべき 2 件（指摘 1・2）と直すとよい 7 件（指摘 3〜9）をすべて直した。採らなかった指摘はない
  - 指摘 2：多項係数は draft の [multinomial-coefficient#meaning](../../../docs/comb/multinomial-coefficient.md) へリンクした
  - 指摘 6：Dilworth の定理のリンクは同じ文の前にあるので、置き換えた文では ABC134 E がこの形だと示すだけにした
  - 指摘 8：コードの配列名は変えず、本文に「コードでは $Q$ を `pos` と書く」と添えた
  - 指摘 9：tspan で下付きにし、render_svg.py の 720px の PNG で確かめた
- 直した後の検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 16）

## 検証を受けての追加の提案（共有ファイル・ほかのページ）

- comb/permutation-parity.md#exactly-k（125 行付近）の「『最小回数以下か』と『偶奇が合うか』の両方を確かめる」は向きが逆で、「最小回数以上か」が正しい（検証の指摘 1 の参考）。そのページの直しとして扱ってほしい
- 台帳 abc470_d の `checked` に 2026-10-22 を入れる（検証役が qiita.com/comet725 の記事で問いと解法を確かめた）。2 つ目の裏付けは引き続き目標
