# median-absolute の報告（工程 8b）

- 書いたファイル：docs/basics/median-absolute.md、snippets/median-absolute/median-sum.{cpp,yaml}、snippets/median-absolute/window-cost.{cpp,yaml}、docs/img/median-absolute/slope.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「中央値の更新・slope trick・三分探索へのつながり（next-steps）」を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0、textlint エラー 0（警告 7：数式を含む文の長さと助詞の重複の誤検出）
- 使った出典：drken（arc100_a・abc330_f・nikkei2019_final_c の記事）、github.com/Reputeless/tenkei_90/blob/main/070.md（check_noai で指定なしを確認。github.com は付録 B にある）
- 図：静的な SVG 1 枚（数直線の点と傾きの折れ線）。描画の道具が手元になく、座標の計算で配置を確かめただけなので、検証で目視してほしい
- 事実の確認：中央値で最小になること、外側から組にした差の和の公式、区間 [x, x + l] への距離の和の最小（組の公式と 2N 点の中央値の両方）を Python の全探索で確かめた（ランダム 3000 回）

## 台帳への提案

- なし（arc100_a・typical90_br・abc330_f の summary はそのまま使えた）
- abc330_f の title「Minimize Bounding  Square」は空白が 2 つある。AtCoder Problems の値どおりなら直さなくてよいが、label に二重の空白がそのまま出る点を確かめてほしい

## 用語集への提案

- 中央値｜median｜ソートした列の真ん中の値。偶数個のときは中央の 2 つのどちらか（問題ごとに定義を確かめる）。Σ|x − a_i| を最小にする
- 重み付き中央値｜weighted-median｜重みの累積が全体の半分以上になる最初の点。Σ w_i |x − a_i| を最小にする

## 手引きへの提案

- なし

## 問題の補充の候補

- nikkei2019_final_c（全国統一プログラミング王決定戦本選 C. Come Together、diff なし）：グリッドの全マスのコマから K 個を除き、残りを 1 マスに集める上下左右の移動回数の最小を求める。行と列に分け、各座標のコマの数を重みにした重み付き中央値を取る。練習に向く（even-count の重み付き中央値と separate-axes の両方を使う）。裏付け：https://drken1215.hatenablog.com/entry/2019/02/18/173100

## 未解決の点

- abc330_f の座標の範囲は第三者の解説の読んだ範囲に書かれていなかったので、本文ではオーバーフローの見積もりを「点の数 × 座標の幅」と書いた
- with-binary-search の「外側から組にする」判定（g(l) = Σ max(0, a_{N−1−i} − a_i − l)）は解説の方法（2N 点の中央値）と別の書き方で、全探索で確かめたもの。出典はない
- related の manhattan-chebyshev#axis-independence・top-k-multiset#median は相手が stub なので、本文からは節でなくページへリンクした

## 検証の指摘への対応（2026-10-21）

- 1〜8 はすべて直した（1：差だけではあふれないと訂正、2：「a_i が整数なら」を追加、3：導入を 0-indexed の a_0..a_{N-1} にし証明にも明記、4：入れ子の理由を 1 文追加、5：top-k-multiset#median と manhattan-chebyshev#axis-independence へ節リンク、6：\text 内の x を数式に、7：図の文字を 14px にし a_i を「点 a」に、8：閉区間と明記）
- 採らなかったもの：なし
- 台帳への提案（検証から）：arc100_a・typical90_br・abc330_f に checked: 2026-10-21 を入れてよい
