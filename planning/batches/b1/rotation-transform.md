# rotation-transform の報告と提案（工程8b・b1）

- 書いたファイル：docs/geometry/rotation-transform.md、snippets/rotation-transform/{affine-compose,grid-rotate,congruence}.{cpp,yaml}、docs/img/rotation-transform/{affine-compose,grid-rotation}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 件とも期待どおり、textlint エラー 0（警告 25 は数式を含む文の読点・長さ、数式内の括弧、「に」の重複などの誤検出か軽微なもの）
- 図：catalog の visual は static・priority 2 なので SVG の静的な図 2 枚にした（動く図は作っていない）。手元に SVG の描画の道具がなく、目視の確認はしていない（XML として読めることだけ確かめた）。検証で表示を確かめてほしい
- 使った出典：merom686（abc259_b・abc298_b・abc292_f）、oraclesqlpuzzle（abc189_e）、drken（abc168_c・abc144_d・abc207_d）、ikatakos（abc197_d、解説の部分だけ）。新しく noai を確かめたドメインはない（zenn.dev は付録 B にあり、記事 os515/atcoder-abc375-c も check_noai で指定なしを確認）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc298_b | approach | 「回転を 0〜3 回施した盤面のそれぞれで条件を調べる（節 grid-rotation）」。今の「回転の添字の式で 4 通り試す」でもよいが、evidence の記事に添字の式はないので、式は本文の節で示した | https://merom686.hatenablog.com/entry/2023/04/16/020333 |
| abc292_f | approach | 「頂点を長方形の角に置き、傾き θ を 0〜30 度で動かして、右の壁と天井の制約が等しくなる θ を二分探索する」。evidence の記事は 15 度を境にする観察で、作者も確信がないと書いているので、本文の方針は自分で式を立てて書いた（s cos θ ≤ B、s sin(θ+60°) ≤ A、A ≤ B）。検証で確かめてほしい | https://merom686.hatenablog.com/entry/2023/03/04/234139 |
| abc189_e | evidence | ikatakos の記事は読んでいない（oraclesqlpuzzle で確かめた）。変更は不要 | — |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| アフィン変換 | affine-transformation | 点 (x, y) を (ax + by + e, cx + dy + f) に移す変換。回転・反転・拡大と平行移動の組合せで、(x, y, 1) に 3×3 行列を掛ける形で書ける。合成は行列の積になる |

（本文では用語集へのリンクを張っていない。geometry の他ページや matrix-power から引くなら足すとよい）

## 手引きへの提案

- §5 geometry に「90 度の倍数の回転は三角関数を使わず整数の式で書く」「盤面（行が下向き）では回転の見かけの向きが点の座標と逆になる」を足すと、grid 系のページ（brute-force#move-board など）とそろう
- SVG を目視で確かめる道具（rsvg-convert や cairosvg）が執筆の環境にない。検証役が描画を確かめる手順を checklists に入れるか、道具を入れてほしい

## 問題の補充の候補

catalog の problems_note のとおり abc319 以降の問題がない。見つけた候補：

| 問題 ID | 題名・diff | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- | --- |
| abc375_c | C. Spiral Rotation（diff 972） | N×N の盤面で、外側から k 層目のマスを k 回ずつ時計回りに 90 度回した後の盤面を求める。層の番号 min(i+1, j+1, N−i, N−j) を 4 で割った余りの回数だけ (i, j) → (j, N−1−i) を施す。盤面を毎回作り直すと O(N^3) で間に合わない | 練習（節 grid-rotation） | https://zenn.dev/os515/articles/atcoder-abc375-c |
| abc404_b | B. Grid Rotation（diff 181） | 盤面の回転と塗り替えで別の盤面に一致させる問題と思われる（題名からの推測）。第三者の解説を見つけられず未確認 | 練習の候補（未確認） | なし |

- 水の帯で abc319 以降の、回転・アフィン変換が本体の問題は見つからなかった（ap.py の題名検索で Rotat・Spin・Flip・Mirror・Grid などを見た範囲）。abc336_f（Rotation Puzzle、2018）は部分の 180 度回転の操作列を半分全列挙で探す問題で、本体は meet-in-the-middle のため候補にしていない（解説は読んでいない）

## 未解決の点

- abc298_b の問題文の回転の定義（どちら回りか）は、evidence の記事に式がなく確かめていない。本文の練習の方針では「回転を 0〜3 回」とだけ書き、向きに依存しない書き方にした
- 合同判定の節（黄）の「偏角と距離の列の巡回シフトで照合する方法」は、drken の記事の解法 2・3 を要約したもの。リンク先のページ（z-algorithm など）は付けていない
- 参考の Competitive Programmer's Handbook（cses.fi）は research の出典にあるが、付録 B にないドメインで今回は読んでいないので、参考から外した

## 検証の指摘への対応（2026-10-21）

- 1〜8 はすべて直した。1：affine-compose.cpp の `using Mat`・congruence.cpp の `using P` を外して型を書き下した（長くなる関数の宣言は改行し、op_matrix は `return {{{…}}};` にした）。2：97 行を `cos(acos(-1.0) / 2)` にそろえた。3：導入に $M$・$Q$ を添えた。4：`atan2` の値域を「$-\pi$ から $\pi$ の範囲」にした。5：斉次性の 1 文を足した。6：巡回シフトの方法を、偏角の順（同じ偏角なら長さの順）に（長さの 2 乗・次の点との内積・外積）の組の列を作り、Z algorithm で照合する形に書き直し、`../string/z-algorithm.md` へリンクした（check_pages でリンク切れなし）。7：grid-rotation.svg の viewBox の高さを 300 に、説明の文を y = 284 に下げ、矢印の終点を x = 340 にして「i ↓」から離した。8：カンマ演算子を波かっこの 2 文にした
- 採らなかったもの：なし
- 手引きへの提案（追加）：matrix-power と同じく、型の別名をやめると `array<array<long long, 3>, 3>` が宣言ごとに並ぶ。§9 の例外に「行列・点の型の別名」を足すかはメインで判断してほしい
