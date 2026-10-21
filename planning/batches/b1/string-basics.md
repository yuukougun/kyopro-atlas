# string-basics の報告と提案（工程8b・b1）

- 書いたファイル：docs/string/string-basics.md、snippets/string-basics/{concat-order,char-mapping,min-rotation}.{cpp,yaml}、docs/img/string-basics/{compare,rotation-window}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 9）
  - 残した警告：要点の囲みの「何ができるか」の no-doubled-joshi（骨格の summary をそのまま使った文）、導入の max-comma と no-unmatched-pair（数式 $S[0], S[1], \dots$ と半開区間 $S[l, r)$ の誤検出）、例の列挙「`abca` も `xyzx` も」と「文字 $c$ を一斉に $d$ に」の no-doubled-joshi（自然な言い回しなので残した）、計算量の落とし穴と練習の方針の sentence-length と no-unmatched-pair（数式 $S[i, i + m)$・$S[i] \to T[i]$ を含む文）
- 図：静的な SVG 2 枚（辞書順の比較・A+A の窓）。catalog の visual は priority 2 で static なので、動く図は作っていない。SVG は XML として読めることだけを確かめた（手元に描画の道具がなく、見た目は未確認）
- 使った出典：drken のはてなブログ 4 本（abc042_b・abc286_c・abc076_c・arc097_a）、ikatakos の ABC110 の記録（解説の部分だけ）。題名は各ページの title 要素（ikatakos は h1）で確かめた。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc110_c | summary | 2 種類の文字を選んで一斉に入れ替える操作を繰り返して、S を T にできるかを判定する。 | 操作は片道の置き換えではなく入れ替え（ikatakos の記録の解説部分。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2018/0923_abc110）。片道の置き換えなら出どころの一意性は要らず答えが変わるので、要約で区別したい |

ほかの使った問題（abc042_b・abc286_c・abc076_c・arc097_a）の summary と approach は、evidence の解説と食い違いがなかった。abc042_b の approach の「長さが違えば a+b < b+a の比較が要る」は解説には書かれていない（解説は長さが違うと誤る例だけを示す）が、本文の節 concat-order で証明を付けて扱った。

## catalog・front matter への提案

- signs の「文字を一斉に別の文字へ置き換える操作を繰り返して一致させられるか」は、abc110_c の操作（入れ替え）とずれる。「2 種類の文字を一斉に入れ替える操作を繰り返して一致させられるか」に直すか、置き換えと入れ替えの両方を含む言い方にしてほしい（本文の節 character-mapping は両方に触れている）
- related の `z-algorithm#cyclic-shift` は、z-algorithm がまだ stub なので本文では節ではなくページへリンクした。z-algorithm が draft になったら節 rotation の「A+A の中で B を探す」から `../string/z-algorithm.md#cyclic-shift` へのリンクに直すとよい

## 用語集への提案

- 全単射｜bijection｜2 つの集合の要素を、もれも重なりもなく 1 対 1 に対応させる写像。文字の置換では「S の同じ文字は T でも同じ文字に、T の同じ文字は S でも同じ文字から」となる対応を指す（本文で `../guide/glossary.md#bijection` にリンク済み）

## 手引きへの提案

- §7 の付録 A に「巡回シフト（回転）」を足してはどうか。本文では「回転（巡回シフト）」を見出しに使い、本文中は「回転」で統一した
- 基礎の technique の「上位の手法とのつながり」は、binary-search の報告と同じく `## 使い分け {#comparison}` にまとめた。定型の見出しにするなら anchor を決めてほしい

## 問題の補充の候補

- 確認済みの問題で例題 1・練習 4 がそろったので、新しい候補は探していない
- frequency_evidence が recent 0 なので、abc319 以降の B〜C から回転・辞書順の比較・文字の対応を問う問題を足せるとよい。今回は ap.py での探索まではしていない

## 未解決の点

- SVG の見た目（文字の重なり・はみ出し）を描画して確かめていない。座標の計算では viewBox 内に収まる
- 片道の置き換え（文字 c をすべて d にする）の条件は、本文では「出どころの一意性は要らず、巡回をほどく空いた文字が問題になる」とだけ書き、正確な必要十分条件は書いていない（裏付けの資料を読んでいないため）
- 節 rotation の「辞書順で最小の回転は A+A の Suffix Array で全探索より速く求まる」は一般的な事実として書いた。Lyndon 分解・Booth の方法には触れていない

## 検証の指摘への対応（2026-10-21）

- 直すべき 1（`ans = ans + c` の TLE）：例を $N = 10^6$（コピーの合計 約 $5 \times 10^{11}$ 文字）にし、$2 \times 10^5$ では間に合うこともあると書き添えた
- 直すとよい 2〜11：すべて採った。2 は境目を $10^4$ に、3 は「各組の処理が $O(1)$ なら」と $O(N^3)$ の注意を足した。4 は例を `c`・`ca`（`cca` と `cac`）に替え、concat-order.yaml に同じ入力を足した。6 は表の `string_view` を cpp-string-api#string-view へのリンクにし「寿命に注意」を添えた。8 は節 rotation で $A$（長さ $N$）・文字列 $B$ を定義した。11 は compare.svg の説明と凡例を 14px にし、右の説明を x=360 に寄せ、太枠の上端を 3px 下げた（y=43・233、高さ 108）
- 採らなかったもの：なし
- 台帳・用語集への新しい提案はない（検証の「台帳・catalog への提案」は上の提案と同じ）
