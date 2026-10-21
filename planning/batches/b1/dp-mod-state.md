# dp-mod-state の報告と提案（工程8b・b1）

- 書いたファイル：docs/dp/dp-mod-state.md、snippets/dp-mod-state/{max-multiple,average-count,game-remainder}.{cpp,yaml}、docs/img/dp-mod-state/fold.svg
- front matter で変えたもの：complexity・stage（draft）・updated（節は足していない）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 3 件とも一致、textlint エラー0・警告3（数式を含む文の長さ 3 件。折りたたみ内の箇条書きと確認問題の題。誤検出として残した）
- 使った出典：kazun（abc281_d・abc262_d）、ebisuke33（abc220_d）、drken（abc135_d・arc060_a）、ikatakos（abc195_e、解説の部分だけ）。新しく noai を確かめたドメイン：ebisuke33.hatenablog.com（指定なし）
- 図：visual は priority 3 なので静的な SVG（和の数直線を M = 4 ごとに折り返して列を状態にまとめる図）で代えた。動く図は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc195_e | pages の dp-mod-state の役割 | practice のまま（変更なし）。本文の節 game-by-remainder で型として参照し、snippet は一般化（法 m）した形にした | — |
| abc195_e | checked | 欠けている（他の項目は `checked: null`）。項目をそろえる | — |

## 用語集への提案

- なし（「状態」は既存の `state` にリンクした）

## 手引きへの提案

- 例題・練習の解法を snippet で一般化して載せるとき（法 m を入力にする等）、練習問題の答えそのものになる場合の扱い（練習の方針は折りたたむが、本文の節のコードで解ける）を決めておくとよい。本ページでは game-by-remainder のコードが abc195_e の解法とほぼ同じ
- §5 dp の「初期値」に、積の条件では空の積が 1（余り 1 mod M）であることを足してもよい

## 問題の補充の候補

catalog の problems_note のとおり、abc319 以降で余りを状態にする DP が主役の問題は見つけられなかった（水のページに abc319 以降が 1 問以上という目安を満たせていない）。

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc244_e（diff 1125） | 長さ K の歩道で頂点 X を通る回数が偶数のものの数。偶奇（2 で割った余り）を状態に持つ（research/02 §5.3 の候補）。練習に向く | https://kazun-kyopro.hatenablog.com/entry/ABC/244/E （未読。台帳に入れる前に確かめる） |
| typical90_e（★7） | 使える数字が決まった N 桁（N ≤ 10^18）の数で B の倍数の個数。余りの DP を桁数の倍化で速くする。台帳では matrix-power の力試しにある。力試しか related の参照に向く | https://drken1215.hatenablog.com/entry/2021/10/08/231200 （台帳の evidence） |

## 未解決の点

- abc262_d の答えの法（998244353 か）は evidence の解説から確かめられなかったので、本文では「問題の指定の法」と書いた
- arc060_a の x_i の上限は解説の要約から確かめられなかったので、本文では和の範囲を式（[-NA, N·max x]）で書き、数値を出していない
- frequency は B（recent 0）のままで、abc319 以降の根拠がない点は catalog の level_evidence のとおり
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 6 回（ほかに curl で記事の題名を 6 件）
