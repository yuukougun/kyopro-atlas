# insertion-dp の報告と提案（b3）

- 書いたファイル：docs/dp/insertion-dp.md、snippets/insertion-dp/{relative-rank,ascents,hakone}.{cpp,yaml}、docs/img/insertion-dp/{relative-rank-table,hakone-matching}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 本とも期待どおり）、textlint（エラー 0、警告 16。数式を含む文の長さと助詞の重なりの誤検出）
- コード片は scratchpad の Python の全探索（N ≤ 7）で全条件・全 K を突き合わせた。TDPC O の遷移（塊の数 g・切る組 k の二項係数）と連結成分 DP の遷移（条件なしで N! になること）も全探索で確かめた
- 図：2 枚とも render_svg.py で 360px・720px を目で確かめた。visual は dynamic・priority 3 なので、静的な図（相対順位の表・位置と値の線）で代えた。動く図の div は置いていない
- 使った出典：qiita.com（Series_205、EDPC T）、kmjp.hatenablog.jp（ABC209 F・ABC282 G・ABC468 G）、drken1215.hatenablog.com（ABC134 F・ABC267 G・exawizards2019_d、カテゴリ「挿入DP」「箱根駅伝DP」）、kanpurin.hatenablog.com（分類と名前の由来）、sigma425.hatenablog.com（TDPC O）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc209_f | evidence | https://kmjp.hatenablog.jp/entry/2021/07/10/0900 を足す（今の kanpurin の記事は問題の一覧で、解説ではない） | 同 URL |
| abc282_g | evidence | https://kmjp.hatenablog.jp/entry/2022/12/18/0900 を足す（同上） | 同 URL |
| abc468_g | approach | 値の小さい順に置き、1〜a を含む最短の区間の長さを状態にする。区間の中の空きに置くか外に伸ばすかで遷移し、o の位置で区切って掛ける | https://kmjp.hatenablog.jp/entry/2026/07/25/0930 |
| abc468_g | evidence | 上の kmjp の URL を足す（ikatakos.com は執筆時に 503 で読めなかった） | 同 URL |
| abc209_f・abc134_f・abc282_g・abc267_g・dp_t・tdpc_string・abc309_g | checked | 2026-10-21（evidence で問いと方針を確かめた） | 各 evidence |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 相対順位 | relative-rank | 列の一部（先頭 i 個など）だけを見たとき、ある要素がその中で何番目に小さいか。値そのものでなく大小関係だけを表す |
| 極大・極小（列の） | local-extremum | 列の要素のうち、両隣（あるものだけ）より大きいものを極大、小さいものを極小という |

本文では相対順位を用語集へリンクしていない（提案が通ればメインがリンクを足す）。

## 手引きへの提案

- なし

## 問題の補充の候補

- exawizards2019_d（D. Modulo Operations、diff 2075）：N 個の数を好きな順に使って x を x mod y で置き換えるとき、N! 通りの順番すべての最終値の和。小さい順に要素を挿入し、新しい要素は先頭に置いたときだけ効く（それ以外の i か所は前の段と同じ）ので dp[i+1][x] = dp[i][x mod s] + i·dp[i][x]。値の順に挿入する見方の練習（水〜黄の易しい側）に使える。裏付け：https://drken1215.hatenablog.com/entry/2019/04/01/201600
- abc266_g（Yet Another RGB Sequence、diff 2045、台帳にあり・multinomial-coefficient の練習）：drken 氏の「挿入DP」カテゴリに入っている。insertion-dp の練習に重ねて載せるかはメインの判断に任せる。裏付け：https://drken1215.hatenablog.com/entry/2023/05/04/185000

## 未解決の点

- abc267_g の台帳の summary「数列の並べ替えのうち…」は、同じ値の要素を区別して数えるのか（添字の順列）、異なる数列として数えるのかが読み取れない。drken 氏のコードは最後に割らず、同じ値を区別する形の係数になっている。問題文を確かめられないので、本文の方針は「真に小さい数 m で係数が決まる」までにとどめた。メインで台帳の summary の言い方を確かめてほしい
- abc468_g の方針は kmjp 氏の記事だけで確かめた（ikatakos 氏の記録は 503）。状態の意味（最短の区間の長さ）は記事のコードの読み取りなので、検証役に別の解説でも確かめてほしい
- 連結成分 DP の節は ABC の例題がない（研究の記録どおり）。USACO Guide は構成の参考だけなので、出典に入れていない
- mathenachia の「DP の俗称」（https://www.mathenachia.blog/dp/）は 404 だったので参考から外した（研究の記録の URL が古い可能性）
- frequency_evidence の abc473_g は台帳では probability-symmetry の練習で、このページには載らない（catalog の problems にもない）。本文では触れていない

## 検証の指摘への対応

- 指摘 1（直すべき）：落とし穴の最後の 2 文を「前の d（隙間 t）で足しても後の d'（隙間 t+1）で足しても、両端の隙間の寄与が 0 なので答えは同じ。どちらかに決めて混ぜない」に替えた
- 指摘 2（直すべき）：ABC468 G の方針を「区間の外の左右どちらかに置いて伸ばす（伸びた後の長さは任意、間の空きは後の値で埋まる）」「区切りの途中では区間がちょうど埋まった状態を使わない」に直した
- 指摘 3（直すとよい）：本文の要約は台帳の summary と揃える必要があるので、本文は変えていない。下の台帳への提案に回した
- 指摘 4（直すとよい）：hakone.cpp のループ変数と注釈を t にし、本文に「コードでは段 t の添字を捨て、dp[d][s] を 1 段ずつ作り直す」と 1 文足した
- 指摘 5（直すとよい）：問題名「箱根駅伝」を確かめられないので、本文を「AOJ 2439 に由来する」と問題番号だけの形にした
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0）

## 台帳への提案（検証の後の追加）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc267_g | summary | 長さ N の数列 A の並べ替え N! 通り（同じ値の要素も区別する）のうち、A_i < A_{i+1} となる i がちょうど K 個あるものの個数を求める。（本文の要約も合わせて直す） | drken の ABC267 G の記事、検証の全探索 |
| abc468_g | approach | 上の提案の「外に伸ばす」を「区間の外に伸ばす（伸びた後の長さは今より長いどれでもよい）」とする | kmjp の ABC468 G の記事 |
