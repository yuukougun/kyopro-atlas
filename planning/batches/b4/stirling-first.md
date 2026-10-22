# stirling-first の報告と提案（b4）

- 書いたファイル：docs/comb/stirling-first.md、snippets/stirling-first/rising.{cpp,yaml}（表の漸化式・上昇階乗の分割統治。全列挙で巡回の個数・左から見える位置の個数の両方と照合）、snippets/stirling-first/buildings.{cpp,yaml}（例題 ABC385 G の式を N ≤ 7 の全列挙と照合）。図はなし（visual: null。表と式で足りると判断）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない。定型でない節 `## 学ぶための資料 {#resources}` を hld に合わせて置いた（sections には載せていない）
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、check_snippets 2 本とも通過、textlint エラー0・警告11（数式の中の読点による max-comma、数式を含む文の長さ、「重複も漏れもない」の助詞の重なり。誤検出または慣用として残した）
- 使った出典：kmjp（abc385_g・abc247_h）、ikatakos（abc385・abc247 の解法の節）、Nyaan's Library（fps-famous-series）、Library Checker の task.md（GitHub）、ACL document_ja。新しいドメインはなし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc247_h | summary | N 人の服の色の列が与えられ、2 人を選んで位置を入れ替える操作をちょうど K 回行った後の人の並びのうち、服の色の列が初めと同じになるものの数を求める。 | https://kmjp.hatenablog.jp/entry/2022/04/10/1100 |
| abc247_h | evidence に追加 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0410_abc247 | 解法の節で、最小 swap 回数を巡回の個数に直し第 1 種スターリング数の行を色ごとに畳み込むことを確認 |
| abc385_g | evidence に追加 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1221_abc385 | 解法の節で、大きい順の挿入と (x^-1 + i + x) の積を確認 |

本文の行は abc247_h を `- abc247_h：自分の要約` で書き、fix_problems が label を埋めた。

注：ikatakos の abc385 のページは、節を切り出すスクリプトの誤りで問題文の節も一度表示された。本文の要約と方針には使っていない（要約は台帳の値のまま、方針は kmjp と解法の節による）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 上昇階乗 | rising-factorial | $x(x+1)\cdots(x+n-1)$ のこと。$x^{\overline{n}}$ と書く。展開した係数が第 1 種スターリング数になる。下降階乗 $x(x-1)\cdots(x-n+1)$ と対になる |
| 左から見える位置（left-to-right maximum） | left-to-right-maximum | 列の位置 $i$ で、$A_i$ がそれより左のどの値よりも大きいもの。記録（record）とも言う。順列でその個数がちょうど $k$ のものは $c(n,k)$ 個 |

（本文ではリンクを張らず、本文の中で定義した）

## 手引きへの提案

- §4 の overview の構成に「学ぶための資料」があるが、定型の見出しと anchor が §13-1 にない。hld が `## 学ぶための資料 {#resources}` を使っているので、定型の節として §13-1 に足すとよい
- comb の注意に「符号なし c(n,k) と符号付き s(n,k) = (−1)^(n−k) c(n,k)。Library Checker は符号付き」を足すとよい（第 1 種を扱う fps-basics・generating-function-counting でも同じ誤りが起きうる）

## 問題の補充の候補

- なし（例題 1・練習 1 で発展の目安 0〜2 に収まる）。Library Checker の 3 問を §15-5 の形ではなく fps 節の中の箇条書きで置いた（練習問題の見出しの下に移すべきならメインの判断に従う）

## 未解決の点

- 例題の解法の詳細に書いた「答え = Σ_j c(N−1, j)·binom(j, (j+K)/2)」の閉じた形は、参考の 2 記事（どちらも y+y^{-1}+i の積を直接畳み込む）とは別の書き方で、全列挙（N ≤ 7）で確かめた自前の導出である
- Taylor shift による倍化 O(N log N) と、列 c(n,K) の指数型母関数 (−log(1−x))^K / K! は、Nyaan's Library の実装（Stirling1st・Stirling1stRow）で確かめた。速さの比較はしていない
- Small p, Large n の解き方は書かず、資料に任せた
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 約 12 回（curl・検索 1 回）

## 検証の指摘への対応（b4 直し）

指摘 1〜6 はすべて採った。採らなかったものはない。

- 1：要点の計算量に列 $c(n, K)$ の FPS の累乗 $O(N \log N)$ を足した
- 2：#vs-second-kind の一致の条件を「$k \ge n - 1$（と $k = 0$）」と (n, k) で書いた
- 3：#records の応用の型を「最大の値の $xy$ と $i = 1, \dots, n-1$ の $(x + y + i - 1)$ の積」とし、$i$ の意味と隙間の内訳を書いた
- 4：練習の方針の色ごとの人数を $a_1, a_2, \dots$ に替えた
- 5：#what の輪の説明に「裏返しは区別する」を足した
- 6：ほかのページ（cht など）にそろえ、Library Checker の 3 問を練習問題の節の小見出し「Library Checker」へ移した。fps 節と学ぶための資料の節には練習問題の節へのリンクを残した

textlint の警告は 13 件（エラー 0）。増えた分は数式を含む文の max-comma などで、残した。
