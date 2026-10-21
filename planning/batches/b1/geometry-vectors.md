# geometry-vectors の報告（工程8b・b1）

- 書いたファイル：docs/geometry/geometry-vectors.md、snippets/geometry-vectors/ccw.{cpp,yaml}、snippets/geometry-vectors/polygon.{cpp,yaml}、docs/img/geometry-vectors/cross-sign.svg・shoelace.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 偏角ソート・凸包・累積和へのつながり, anchor: next-steps}` を足した（手引き §4 の基礎の構成「上位の手法とのつながり」）
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 期待と違う 0／textlint エラー 0（警告 23 は数式を含む文の長さ・読点、助詞「か」「に」の重複などで、意味を損なわないので残した）／fix_problems --check は本ページに直す行なし（geometry/rotation-transform.md に 8 行あるが、別の担当のページ）
- 動く図：catalog の visual は static・priority 2 なので、静的な SVG 2 枚で代えた（動く図の div は置いていない）
- 使った出典：drken（abc181_c・abc361_b・abc016_4・abc250_f・abc373_g）、merom686（abc224_c・abc266_c）、ikatakos（abc472_f。解法の部分だけ）、en.cppreference.com（std::complex の要素の型）。どれも付録 B のドメインで、新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc472_f | approach | 重心＝Σ(p_i+p_{i+1})·cross(p_i,p_{i+1}) / (3Σcross)。辺ごとの 3 種類の値を 2 周分の累積和にし、閉じる辺を足して各クエリ O(1) | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0822_abc472 |
| abc373_g | approach | 交差する 2 本をつなぎ替えると三角不等式で長さの和が真に減るので、長さの和が最小の完全マッチング（最小費用流）に交差はない | https://drken1215.hatenablog.com/entry/2024/09/29/034410 |
| abc016_4 | note | 線分が多角形の頂点を通らないことが制約で保証される（端点で接する場合を考えなくてよい） | https://drken1215.hatenablog.com/entry/2023/06/08/041900 |

summary はどれも表記の規則に合っていたので、直しの提案はない。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 外積 | cross-product | 2 次元のベクトル a, b に対する a_x b_y − a_y b_x。正なら b は a の左（反時計回りの側）、0 なら同じ直線上。絶対値は a と b が作る平行四辺形の面積。詳しくは geometry-vectors#cross-and-dot |
| 内積 | dot-product | a_x b_x + a_y b_y。正なら a と b のなす角は鋭角、0 なら直角、負なら鈍角 |
| ccw | ccw | 3 点 p, q, r について cross(q − p, r − p) の符号。p → q → r が左に曲がれば正、右なら負、一直線上なら 0。geometry-vectors#ccw |
| 符号付き面積 | signed-area | 頂点の並びの向きで符号を付けた面積。反時計回りを正とし、多角形の座標の公式（靴紐公式）は符号付き面積の 2 倍を与える |

## 手引きへの提案

- §5 geometry に「外積の値どうしを掛けない（ccw の符号にしてから掛ける）」を足すとよい。交差判定のオーバーフローは見落としやすく、幾何のページの多くで共通する
- 早見表の「外積の値の大きさ」（research 08 §6.3）の 8×10^18 は、各積の上界から足した見積もりである。|x|, |y| ≤ 10^9 の正方形の中の 3 点なら、実際の最大は三角形の面積の上限から 4×10^18 である。早見表に入れるときは「見積もり」と明記するか、両方を書くとよい（本文は見積もりとして書いた）

## 問題の補充の候補

確認済みの問題で、例題 1・練習 4・力試し 3 がそろっているので、補充は必須ではない。基礎の練習に abc319 以降の問題がない（abc361_b だけ）ので、余力があれば ap.py と第三者の解説で abc319 以降の外積・ccw の易しい問題を探すとよい（今回は探していない）。

## 未解決の点

- abc181_c・abc224_c の座標の範囲は、解説の抜粋では確かめられなかった。本文では制約の数値を書かず、「`long long` で読めば制約の大きさを気にしなくてよい」とだけ書いた
- abc266_c の解説（merom686）は符号の向きをサンプルで決めたとしていて、入力が反時計回りかは書いていない。本文の練習の方針は「符号の向き（反時計回りの入力なら正）を小さな例で確かめてから書く」と条件付きにした
- SVG は描画して目で確かめられなかった（rsvg-convert などがない）。座標は計算で合わせたが、検証役に表示の確認を頼みたい
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 約 12 回

## 検証の指摘への対応（planning/batches/b1/verify/geometry-vectors.md）

- 指摘 1〜7 はすべて直した（1：45 度回転の主張を「見積もりは 4 倍で保証がなくなる。45 度回転は実際には −2 倍で収まるが途中の積が 9×10^18 でぎりぎり」に／2：shoelace.svg の viewBox を 0 0 600 340 に広げた／3：表の 2 行目を見積もりの 3.2×10^19 にそろえ、実際の最大 4×10^18 を表の下に 1 文足した／4：原点が外のときと内のときを分けた／5：累積和のあふれと #overflow へのリンクを足した／6：ABC266 C を「すべて正か、すべて負」に／7：N ≤ 100 と組の数 161700 を書いた）。採らなかったものはない
- 検査：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 期待と違う 0／textlint エラー 0（警告 25）

### 台帳への提案（追加）

- 検証役の確認に基づき、`checked` に 2026-10-21 を入れる：abc181_c・abc361_b・abc224_c・abc266_c・abc016_4・abc250_f
- abc181_c の note に「N ≤ 100」（根拠：drken の解説。本文の例題の方針で使った）
