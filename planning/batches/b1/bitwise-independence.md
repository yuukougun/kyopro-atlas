# bitwise-independence の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/bitwise-independence.md、snippets/bitwise-independence/pair-xor-sum.{cpp,yaml}、docs/img/bitwise-independence/bit-count-table.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（1 片・期待と違う 0）、textlint（エラー 0・警告 19。数式を含む文の長さ、`$$` の数式ブロック内の読点と括弧、助詞の重複の誤検出に近いもの）
- 図：catalog の visual（static・priority 2）の「2 進表記を縦に並べ、bit ごとの 0・1 の個数から寄与を足す図」を SVG にした（a = 3, 5, 6）。描画ツールが手元になく、目視の確認はしていない（座標は単純な格子）
- コード片：pair-xor-sum.cpp に 2 つの取り込み範囲（core：全ペアの XOR の和、range：長さ 2 以上の全区間の XOR の和）。小さい入力では素朴な計算と assert で照合する

## 使った出典

- drken「AtCoder ABC 147 D - Xor Sum 4 (1Q, 水色, 400 点)」https://drken1215.hatenablog.com/entry/2020/04/25/032000：例題の問い（N ≤ 3×10^5・A_i < 2^60・mod 10^9+7）と方針
- ikatakos「AtCoder Beginner Contest 147 C～F問題メモ」：題名だけ確認（台帳の evidence。本文の参考に入れた）
- oraclesqlpuzzle「ABC365-E Xor Sigma Problem」：区間を bit ごとに数える方針（制約はページに書かれていなかった）
- drken ABC117 D・ABC129 E・ABC281 F の記事：上限 K と食い違う bit での場合分け／和 = XOR の言い換えと L 以下の数え方／上位ビットで分ける再帰（N ≤ 1.5×10^5、A_i < 2^30）
- 補充の候補の確認に検索結果だけを見た：zenn.dev/testcampus、qiita.com（rute_not_route・u2dayo）。どれも付録 B のドメイン
- 新しく noai を確かめたドメイン：なし

## 台帳への提案

- なし（使った 5 問はどれも確認済みで、summary も本文の書き方と合っている）
- 参考：abc281_f は台帳の summary（「x を選んで、全要素と x の XOR の最大値を最小にする」）をそのまま使った。alternatives の bitwise-independence 向けの summary（max(a_i xor x)）は本文の行には使われていない

## 用語集への提案

- なし（本文では用語集へリンクしていない。「累積 XOR」は累積和のページへのリンクで足りると判断した）

## 手引きへの提案

- 擬似コード（```text）の中の `|one|` などは textlint の対象外だが、本文の数式の表記（$\lvert \cdot \rvert$）とずれる。擬似コードの記法をそろえる規則があるとよい
- prh.yml：「上位ビット」と「上の bit」が混在しやすい（sections の title が両方を使う）。正規形を付録 A の「bit ごと」に合わせて「上位 bit」にそろえるかどうかを決めてほしい。本文は sections の title に合わせて両方を使った

## 問題の補充の候補

- abc347_d（D. Popcount and XOR、diff 1041、ap.py で確認）｜popcount(X) = a、popcount(Y) = b、X xor Y = C となる 60 bit 以内の (X, Y) を 1 つ作る（なければ -1）｜C の bit が 1 の位置は X・Y の一方だけ、0 の位置は両方か両方でないかと bit ごとに決まるので、個数と偶奇で可否を判定して割り振る。abc319 以降の問題なので練習に向く（易しい側）｜https://zenn.dev/testcampus/articles/089f7b56e3745c 、https://qiita.com/hyouchun/items/0c2a8b3bc4f281b34e24
- abc238_d（D. AND and SUM、diff 921、ap.py で確認）｜x AND y = a かつ x + y = s となる非負整数の組があるかを判定する｜a + b = (a xor b) + 2(a and b) を使い、s − 2a ≥ 0 かつ (s − 2a) AND a = 0 で判定する。節 addition の練習（易しい）。bit-operations の xor-properties の練習でもよい｜https://qiita.com/rute_not_route/items/5d586f9f28b605d8233f 、https://qiita.com/u2dayo/items/12ac3e1834ededba1824
- arc092_b（ABC091 D. Two Sequences、diff 2207、ap.py で確認）｜2 つの数列のすべての組の和の XOR を求める｜bit k ごとに mod 2^(k+1) の余りをソートし、和が [2^k, 2^(k+1)) か [3·2^k, 2^(k+2)) に入る組の数の偶奇を二分探索で数える。節 addition の「下の bit をまとめて見る」の力試し（黄なので力試しの上限）｜第三者の解説の URL は未確認（drken の記事があると思うが、URL を確かめていない）

## 未解決の点

- 節 addition の「区間の和と XOR が等しい区間を数える問題」は arc098_b（two-pointers の力試し）を念頭に置いたが、本文では問題 ID を出さず尺取り法のページへリンクした
- 力試しの abc281_f は binary-trie の例題なので、ここでは力試しのまま（catalog どおり）。split-by-top-bit の節と binary-trie#implicit の説明が重なる。binary-trie を書くときは、こちらの節へリンクして重複を減らすとよい
- 節 top-down の「2 つ選んだ AND の最大値」は型の説明だけで、台帳に対応する問題がない
- 確認問題（部分集合の XOR の総和 = OR × 2^(N−1)、上限つき貪欲の反例 a = (4, 0, 0)・K = 4）は手計算で確かめた
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 7 回・検索 2 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜8 はすべて採った。採らなかったものはない
  - 1・2：コード片の区間の和は「a[i] < 2^30 かつ n ≤ 10^5」のときだけ計算し（(10^5+1)^2/4 × 2^30 ≈ 2.7×10^18）、素朴な照合もその条件の下でだけ行う。`small` の判定は 1 回にまとめた。n = 10^5・値 < 2^30 と、値が 60 bit 近い入力でサニタイザの出力なしを確かめた。落とし穴「個数 × 個数 × 2^k のあふれ」に区間版の見積もり（N = 2×10^5・B = 30 で約 1.1×10^19）を足した
  - 3：X < K になる理由の 1 文、候補を比べる擬似コード、a = (4, 0, 0)・K = 4 の例を足した
  - 4：「XOR してから足すのは分けてよい」を箇条の外（繰り上がりの段落の後）へ移した
  - 5：図の行ラベルを「寄与」にした
  - 6：リンクを bit-operations.md#xor-properties にした
  - 7：range-xor の最終段落と落とし穴を、AND・OR についての否定に絞った
  - 8：2 つの長い文を分けた
- 台帳への提案（検証役から引き継ぐ）：abc117_d の approach を「K と初めて食い違う bit で場合分けし、下の bit は多数決で決める（桁 DP でも解ける）」に直す。abc147_d・abc117_d・abc129_e・abc281_f の checked に 2026-10-21 を入れる
