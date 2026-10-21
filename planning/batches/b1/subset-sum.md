# subset-sum の報告と提案

- 書いたファイル：docs/dp/subset-sum.md、snippets/subset-sum/count.{cpp,yaml}、docs/img/subset-sum/shift-or.svg（静的な図。catalog の visual は priority 2・static なので動く図は置かない）
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（pitfalls は骨格の title のまま見出しにした。dp-basics と同じ扱い）
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 0／check_snippets 期待と違う 0／textlint エラー 0・警告 5（34・36 行は要点の囲みの summary と signs の文（骨格のまま）、59・132 行は「に」の重複で引用の語句を含む、63 行は図の代替テキストの読点）
- 使った出典：drken（TDPC A）、ikatakos（ABC204・216・169。解説の部分だけ）、Kazun（ABC274 D）、hamayan（ABC222 E）。どれも付録 B のドメインで、新しいドメインはない

## 台帳への提案

- なし（使った 6 問はすべて確認済みで、summary も表記の規則に合っている）
- 参考：abc222_e の evidence のうち hamayan の解説は ±D_i の DP を直接書く方法で、(K + ΣD)/2 の部分和への言い換えは本文の側で導いた（数学的に同値）

## 用語集への提案

- なし（リンクしたのは既存の state だけ）

## 手引きへの提案

- 基礎のページで、骨格の sections に「落とし穴：…」が title 付きで入っている場合の扱い（§13-1 の定型の「## 落とし穴 {#pitfalls}」にするか、title に合わせるか）を決めてほしい。今回は dp-basics にならって title と同じ見出しにした

## 問題の補充の候補

- 追加は不要と判断した（例題 1・練習 5）。力試しの候補は abc221_g（diff 2914、45 度回転して 2 つの ± の部分和に分け bitset で判定・復元、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/1002_abc221 ）だが、基礎のページには難しすぎるので bitset-speedup の側で扱うのがよい

## 未解決の点

- TDPC A で 0 点（1 問も解かない）を種類に数えることは、drken の記事のコードが j = 0 から数えていることで確かめた（記事の本文には 1 からと読める記述がある）。問題文そのものは開いていない
- 図 shift-or.svg は描画して目で確かめる手段がなかった（XML としての妥当性だけ確かめた）。幅 632 に対して最下行の文が右端近くまで届くので、表示で確かめてほしい
- 「平均をちょうど A にする」の言い換えは arc060_a（dp-mod-state の練習）と同じ型だが、本文では問題 ID を出さず型だけ書いた
