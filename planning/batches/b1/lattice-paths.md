# lattice-paths の報告と提案（工程8b・b1）

- 書いたファイル：docs/comb/lattice-paths.md、snippets/lattice-paths/{knight,forbidden}.{cpp,yaml}、docs/img/lattice-paths/{basic,forbidden}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 鏡像法・包除 DP・LGV 補題へのつながり, anchor: next-steps}` を足した（基礎の目安の「上位の手法とのつながり」。level はページと同じ基礎）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件・全ケース一致。期待値は Python の全探索 DP と math.comb で別に計算した）、textlint（エラー 0・警告 4）
  - 残した警告：35 行の no-doubled-joshi（要点の 1 文目。front matter の summary と同じ文にしたため）、62 行と 96 行の no-doubled-joshi（「重複も漏れもない」の慣用句）、119 行の max-comma（数式 $i = 0, \dots, n$ の中の読点）
- 動く図：作っていない。catalog の visual は priority 3（静的な図で代えてよい）なので、静的な SVG 2 枚（各点の経路数の表と 1 つの経路、禁止領域と境目を越える行）で代えた
- 使った出典：drken のはてなブログ 5 本（abc145_d・arc058_b・abc154_f・abc011_4・agc001_e）、kmjp のブログ（abc240_g）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc154_f | summary | 「最短経路」を「最短路」に（textlint の prh が「最短経路 => 最短路」をエラーにする）。本文の行は先に「最短路」に直したので、台帳も合わせてほしい（fix_problems --check は summary の差を見ていないようで、0 件のままだった） | prh.yml |

ほかの使った問題（abc145_d・arc058_b・abc011_4・agc001_e・abc240_g）の summary と approach は、evidence の解説と食い違いがなかった。

## front matter・catalog への提案

- summary と signs の 1 つ目の「最短経路」が prh の正規形「最短路」と食い違う。本文の要点は「最短路」にした（文の残りは summary と同じ）。summary と signs も「最短路」に直すと要点と完全に一致する。aliases の「グリッドの最短経路の数」は別名なのでそのままでよい

## 用語集への提案

- なし（「全単射」は counting-bijection へ、「縦の和」は binomial-identities#hockey-stick へリンクした）

## 手引きへの提案

- 基礎の technique の目安の「上位の手法とのつながり」は定型の見出しにない。今回は binary-search-answer にならって sections に `next-steps` として足した。定型の見出し（例：`## 上位の手法とのつながり {#next-steps}`）にするなら §13.1 に足してほしい
- prh の「最短経路 => 最短路」は、summary や台帳の summary から機械的に作る行（要点・問題の行）に当たる。骨格の生成時か台帳の作成時に prh をかける手順があるとよい

## 問題の補充の候補

- abc034_c（C. 経路、diff 1440 参考値。ap.py で確認）：H×W のグリッドの左上から右下へ、右と下だけで進む経路の数を法 10^9+7 で求める。障害物のない基本形そのもので、ABC145 D の前の練習として易しい側に置ける。裏付け：https://qiita.com/2yuu/items/35617e56e1794d33c22b 、https://qiita.com/tiaki73/items/43f222d75da0e6a66426
- abc319 以降の格子路の問題は見つけていない（frequency_evidence も recent 0）

## 未解決の点

- 図 2 枚は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認（とくに forbidden.svg の「h=0」などのラベルが格子の線と重なって読みにくくないか）を検証役に頼みたい
- agc001_e は difficulty がないので、力試しの中で abc240_g（2462）より前に置いた（解説の題名では 1400 点の問題）
- ABC011 D の練習の方針の「double で 4^N で割りながら計算する」は、drken の解説の long double のパスカルの三角形とは別の書き方で、精度の根拠を本文では書いていない。方針の範囲として足りるかを検証役に見てほしい

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：#move-counts の箇条を「1 通りとは限らない。平面なら自由に選べる回数（3 種類なら 1 つ、4 種類なら 2 つ）でループ」に直した
- 指摘 2：#forbidden-region に「この節ではマスを (行, 列) = (r, c) の 0-indexed で表す」の 1 文を足した
- 指摘 3：#sum-of-paths と力試しの方針の「1 を置く」を「各始点の位置に 1 を足す（同じ始点が複数あればその個数）」に、範囲を「座標の絶対値が M 以下なら (2M+1)^2 の格子の DP で O(N + M^2)」に直した
- 指摘 4：ABC011 D の方針を「パスカルの三角形の各段を 2 で割って C(n,k)/2^n の表を作り、確率どうしを掛ける。45 度回転なら 2 つの積」と具体化した
- 指摘 5：forbidden.svg のラベルを点線の右（x = 146、左揃え）・各行の上寄りで経路の線と重ならない位置に移し、14px に上げた。右の説明を図の下に回し、viewBox を 380×540 にした（幅 390px の画面で倍率約 0.94）
- 指摘 6：#basic の段落を二項係数のページ #meanings へのリンクで縮めた。basic.svg は点の図をやめ、3 行 4 列のマスに経路の数を書く図（下 2 回・右 3 回、C(5, 2) = 10、経路 RRDRD）に描き直し、落とし穴「マスの数と移動の回数」とつなげた。説明は図の下に置き viewBox は 300×350。確認問題（点 (3, 2)）は点の座標のままで本文の式と合う
- 指摘 7：#forbidden-region に「角のすぐ上のマス (H-A-1, B-1) を通るかで分けられない理由」、#independent-axes に「n = 2 で原点に戻る方法（4 通り）」の確認問題を足した。角の点はマスの経路では曖昧なので、検証の案の「角の点」をマスに言い換えた
- 指摘 8：落とし穴を「(H+1) 行 (W+1) 列のグリッドの答えになる」に直した
- 採らなかった指摘：なし
- 図 2 枚は描き直し・配置の変更の後、ブラウザで描画しての確認はしていない（XML として読めることと座標だけ確かめた）。再検証で見てほしい

### 台帳への提案（検証の指摘から）

- arc058_b の approach「境界を越える列で分類」を「禁止領域の右の境目を越える行で分類し」に（本文の向きに合わせる）
- 6 問（abc145_d・abc154_f・abc011_4・arc058_b・agc001_e・abc240_g）の checked に 2026-10-21（検証役が evidence で確認済み）
