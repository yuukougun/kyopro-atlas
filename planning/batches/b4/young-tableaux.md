# young-tableaux の報告と提案（b4）

- 書いたファイル：docs/comb/young-tableaux.md、snippets/young-tableaux/hook.{cpp,yaml}、docs/img/young-tableaux/hook-lengths.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 14：数式を含む文の長さ・助詞の重なりの誤検出。数式の多い文と例題の要約の行）
- 図：hook-lengths.svg（形 (4, 3, 1) のフック長と 1 つのフックの網かけ）を render_svg.py で画像にして目で確かめた
- 定型以外の見出し：`## ライブラリでの使い方 {#library}`・`## 学ぶための資料 {#resources}`（overview の構成。hld と同じく sections に載せていない）
- 使った出典：en.wikipedia.org（Hook length formula・Robinson–Schensted correspondence）、ja.wikipedia.org（ヤング図形）、github.com（library-checker-problems の問題一覧）、kmjp.hatenablog.jp、ikatakos.com（解法の節だけ）。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc378_g | summary | 長さ AB − 1 の順列のうち、LIS の長さが A、LDS の長さが B であり、末尾に値を 1 つ付け加えて両方の長さを保てるものの数を、素数で割った余りとして求める。 | ikatakos の解法の節（末尾に加える n+0.5 は「ある n」として扱われる）。kmjp の記事の要約は「どんな値を加えても」と書くが、最大より大きい値を加えると LIS は必ず増えるので「ある値」と読むのが正しい |
| abc378_g | approach | Robinson-Schensted 対応で形を長方形から 1 箱欠けた形に決め、Q をフック長公式で、追加の大小関係が付く P を形を状態にした DP で数えて掛ける | 同上の 2 件 |
| abc378_g | evidence | ikatakos の記事を足す：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1102_abc378 | evidence を 2 件にする（§15-6） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| Young 図形 | young-diagram | 整数の分割 λ1 ≥ λ2 ≥ … を、i 行目に λi 個の箱を左詰めで並べた図形。行と列を入れ替えると、転置した分割の図形になる。 |
| 標準タブロー | standard-young-tableau | Young 図形の箱に 1〜N を 1 つずつ書き込み、どの行も左から右へ、どの列も上から下へ増加するようにしたもの。 |
| フック長 | hook-length | Young 図形の箱について、その箱の右にある箱の数と下にある箱の数に 1 を足した値。 |

本文では用語集にリンクしていない（§15-1）。

## 手引きへの提案

- §4 の overview の構成の「ライブラリでの使い方」「学ぶための資料」に、定型の見出しと anchor（`{#library}`・`{#resources}`）を §13-1 の一覧に足すとよい。hld はすでに `{#resources}` を使っており、ページごとに揺れないようにしたい
- 付録 A に「標準タブロー」「フック長」「Young 図形」「Robinson-Schensted 対応（RS 対応）」を足す案。ja.wikipedia は「ヤング盤・標準盤」と書くが、本文は catalog の aliases に合わせて「標準タブロー」を正規形にした

## 問題の補充の候補

- 確認済みの例題（abc378_g）で 1 問はそろっているので、補充は急がない。ABC で Young 図形・フック長公式そのものを使う問題はほかに見つけていない（研究メモ 07-math-comb §7.5 も「abc378_g のみ」）
- Library Checker にフック長公式や RS 対応の問題はない（library-checker-problems の一覧で確かめた）。近い問題として longest_increasing_subsequence と partition_function を本文で挙げた

## 未解決の点

- abc378_g の問題文は読んでいない。条件の「末尾に値を付け加える」の量化（ある値か、すべての値か）は ikatakos の解法の節と、手元の全探索（A, B ≥ 2、AB ≤ 9 で「ある値」の解釈の答えが P の数 × Q の数に一致）から「ある値」と判断した。制約（AB ≤ 120）は ikatakos の解法の節の記述で、本文には数値を書いていない
- 本文の Schensted の定理・Greene の定理・逆順で転置されることは en.wikipedia の記事で確かめた。逆順の性質と Erdős-Szekeres の定理の説明はコード片では試していない（RS の LIS・LDS と (f^λ)^2 の個数、Σ(f^λ)^2 = N! は N ≤ 7 で assert している）
- 「対合の数 = Σ f^λ」は確かめきれなかったので書いていない
- 動く図は catalog の visual が null なので作っていない

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 9 回（検索 2 回を含む）

## 検証の指摘への対応（2026-10-22）

- 指摘 1〜7（いずれも「直すとよい」）をすべて直した。採らなかったものはない
  - 1：フック長の式を 1-indexed の $h(i, j) = (\lambda_i - j) + (\lambda'_j - i) + 1$ にした（コード片は 0-indexed のままで、本文の式とは独立）
  - 2：フック長の定義を「同じ行で右」「同じ列で下」と明記した
  - 3・4：解法の詳細に、追い出しの経路が A 列目を通るしかない理由、1 行目の値がいつでも選べること、DP の遷移の条件（置いた後も上の行より長くならない、A 列目に置くのは下の行に A−1 個そろっているときだけ）を足し、全探索は補助の位置に下げた
  - 5：「このサイトで確かめた範囲では」と範囲を付けた
  - 6：#partitions の最後の段落を、RS 対応の節へのリンク付きで自己完結にした
  - 7：Greene の定理を「高々 $k$ 本」にした
- 用語集への提案の「フック長」の定義も、指摘 2 に合わせて次のように改める：「Young 図形の箱について、同じ行でその箱より右にある箱の数と、同じ列でその箱より下にある箱の数に 1 を足した値。」
