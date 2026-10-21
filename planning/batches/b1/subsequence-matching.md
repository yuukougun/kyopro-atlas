# subsequence-matching の報告と提案（工程8b・b1）

- 書いたファイル：docs/string/subsequence-matching.md、snippets/subsequence-matching/{next-table,repeated}.{cpp,yaml}、docs/img/subsequence-matching/next-table.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（2 件すべて一致）、textlint（エラー 0・警告 20）、fix_problems --check（このページは 0。ほかのページ string/hashing-for-sets.md:223 の abc424_f に label の二重空白が 1 件あり。担当外なので触っていない）
  - 残した警告：半開区間 $S[0, i)$・$S[i, N)$・$S[l, e)$ を括弧の対と誤検出する no-unmatched-pair、数式を含む文の sentence-length、図の代替テキストの数の列の max-comma、数式の中の「から」の no-doubled-joshi など。どれも数式か代替テキストによる誤検出
- repeated.cpp は Python の素朴な実装と、ランダムな 400 ケース（N ≤ 5、|S| ≤ 5、|T| ≤ 4、文字 abc）で答えが一致することを確かめた
- 図：catalog の visual は static・priority 2 なので、静的な SVG（S = abcab の nxt の表と T = bab で引いた欄）にした。動く図は作っていない
- 使った出典：merom686（ABC452・ABC346 の記録）、comet725（Qiita、ABC452 D の DP 解）、drken（abc324_e・typical90_f・arc081_c）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc452_d | evidence の順 | merom686 を先にする（comet725 の記事は照合位置を状態にした DP の解で、次の出現位置の表の方針は書かれていない）。値を変える必要はない | https://merom686.hatenablog.com/entry/2026/04/05/005148 |

ほかの使った問題（abc324_e・typical90_f・abc346_f・arc081_c）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- なし（番兵は既存の sentinel にリンクした）。部分列・部分文字列の語は string-basics の節にリンクしたので、用語集には足さなくてよいと考える

## 手引きへの提案

- 基礎の technique の「上位の手法とのつながり」は定型の見出しがないので、binary-search と同じく `## 使い分け {#comparison}` にまとめた。定型にするなら anchor を決めてほしい（binary-search の報告と同じ提案）

## 問題の補充の候補

- なし。例題 1・練習 3・力試し 1 で目安を満たす。repeated-string（青）と lexicographically-smallest（水）にもそれぞれ練習が 1 問ある

## 未解決の点

- abc452_d の制約（|S|・|T| の上限）は第三者の記録に数値がなく、「T が短い」とだけ確かめた。本文では具体的な上限を書かず、計算量 O(26N + N|T|) だけを書いた
- next-table.svg は描画して目で確かめる道具がなく、XML として読めることと表の値（Python で計算）だけを確かめた。文字のはみ出しがないか、表示の確認を検証役に頼みたい
- 「N = 10^6・σ = 26 の int の表は約 100 MB」「vector<vector<int>> は行ごとに確保して遅い」は計算と一般的な知識による

## 検証の指摘への対応（直し）

- 指摘 1〜5（直すとよい）はすべて直した。1：#repeated-string の冒頭で「この節では N は繰り返しの回数、S の長さは |S|」と断り、練習の方針にも添えた。2：q' の条件に「T[j-1] を拾った位置より右」を足し、範囲を [q'+1, N) にした。3：match_end に始める位置 p（既定 0）を引数で足し、本文を `match_end(nxt, t, p)` に合わせた（T が空なら p-1 を返す）。main と cases は変えていない。4：図の向きと番兵の行の対応を書いた。5：O(σN^2) を O(N^2) にした
- 採らなかったもの：指摘 3 の「始点を変えた cases を足す」は、main の入力形式を変える必要があるので見送った（乱数比較は p = 0 の経路で済んでいる）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 22。増えた 2 件は半開区間 [q'+1, N) の no-unmatched-pair と数式を含む文の長さで、誤検出）
