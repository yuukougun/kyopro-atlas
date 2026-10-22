# generating-function-counting（母関数の考え方）の報告

- 書いたファイル：docs/comb/generating-function-counting.md、snippets/generating-function-counting/bounded.{cpp,yaml}（図は描いていない。catalog の visual が null のため）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は title を 1 つ変え、並びを本文の順に入れ替えた（anchor は変えていない。下の「手引きへの提案」1）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 12。数式を含む文の長さ・数式の中の読点と助詞の重なりで、§13-8 の誤検出として残した）
- 使った出典：
  - https://drken1215.hatenablog.com/entry/2023/05/28/010200（ABC303 Ex の立式と計算量）
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0314_abc449（ABC449 G。解法の節だけ）
  - https://kmjp.hatenablog.jp/entry/2026/03/14/0900（ABC449 G の数え方の確認）
  - https://kmjp.hatenablog.jp/entry/2024/12/21/0930（ABC385 G の挿入 DP と因子の積）
  - https://drken1215.hatenablog.com/entry/2023/09/25/070100（ABC321 F）
  - https://qiita.com/hotman78/items/f0e6d2265badd84d429a（学ぶための資料：FPS の演算と計算量）
  - https://nyaannyaan.github.io/library/fps/formal-power-series.hpp（学ぶための資料：実装）
  - https://github.com/yosupo06/library-checker-problems（Library Checker の問題名と内容。sharp_p_subset_sum・partition_function・product_of_polynomial_sequence の task.md を読んだ）
  - 新しく noai を確かめたドメインはない（どれも付録 B にある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc449_g | summary | 1 桁から M 桁までのレピュニット（1 だけが並ぶ数）を重複を許して N 個選んで足すとき、和として現れる整数の種類数を求める。 | ikatakos（上の URL）・kmjp https://kmjp.hatenablog.jp/entry/2026/03/14/0900 |
| abc449_g | evidence | kmjp の URL を足す（2 つ目の裏付け） | 同上 |
| abc449_g | checked | 2026-10-22 | 2 つの解説で問いと解き方を確かめた |
| abc449_g | approach | 10 の冪の和に直し、各桁 9 以下の代表の個数の母関数 (1−x^10)^(M−1)/(1−x)^M の、x^N・x^(N−9)・… の係数の和から ⌊N/9⌋ を引く | 同上 |
| abc385_g | checked | 2026-10-22 | kmjp の解説で挿入 DP と因子の積を確かめた |

- abc449_g について：kmjp の記事は「合計して N になる表現」と書く箇所があるが、ikatakos・kmjp とも解き方（個数の合計 T ≤ N・T ≡ N mod 9・⌊N/9⌋ を引く）は N を選ぶ個数とした場合のものなので、N は個数とした

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 母関数 | generating-function | 数列 a_0, a_1, … を係数に並べた冪級数 Σ a_n x^n。積が畳み込み（独立な選択の組合せ）にあたる |
| 上昇階乗 | rising-factorial | x(x+1)…(x+n−1) のこと。係数は第 1 種スターリング数 |

（本文ではどちらもリンクせず、本文で定義した）

## 手引きへの提案

1. 骨格の sections に anchor `examples` の中身の節（「例：Prüfer 列と多項式の累乗、上昇階乗」）があり、定型の `## 例題 {#examples}`（§13-1）と anchor がぶつかった。anchor を変えずに title を「例題：Prüfer 列と累乗、上限つきの桁の和」に変えて例題の節として使い、定型の見出しは置かなかった。上昇階乗の話は dp-as-polynomial の節へ移した。sections に定型の anchor（examples・practice・quiz など）を持つ骨格がほかにないか、catalog と骨格で確かめるとよい
2. 発展の概要（§4）の「学ぶための資料」は、hld と同じく `## 学ぶための資料 {#resources}` を sections に載せない定型の節として置いた。§13-1 の定型の一覧に足すとよい
3. 発展の概要に確認問題を置くときも `## 確認問題 {#quiz}` にまとめた（§14-11）

## 問題の補充の候補

- 足りているので新しい候補は探していない（例題 2・練習 2）

## 未解決の点

- 例題 ABC449 G の制約（N・M の上限）は確かめていない。本文では「M が大きくても隣の項との比で求められる」とだけ書いた（ikatakos によると M は 10^9 まで）
- cayley-pruefer の発展の節の計算量（FPS の累乗 O(N log N)、繰り返し二乗法と畳み込み O(N log^2 N)、分割統治 O(N log^2 N)）とこのページの値は一致している。fps-basics が draft になったら、演算の表の計算量（逆元・log・exp・累乗 O(K log K)、多くの因子の積 O(K log^2 K)）を照らしてほしい
- fps-basics・stirling-first・online-convolution は stub なので、ページへのリンクだけにした（§14-23）。fps-basics が draft になったら to-fps の節から節へのリンクに張り替える
- maspy 氏のサイト（maspy.com）は現在、別の内容（工事中の表示）になっていて、FPS の解説を資料に使えなかった
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 約 14 回

## 検証の指摘への対応（verify/generating-function-counting.md）

- 1（直すべき）：本文の挿入 DP の段落から ABC385 G と因子 $x^{-1} + (n-1) + x$ の文を消した
- 2（直すべき）：Library Checker の Stirling Number of the First Kind を「下降階乗の係数（符号付き）。絶対値が上昇階乗の係数」に直した
- 3：「おおむね difficulty 2400 以上」をやめ、「主に後半の G・Ex（このページの例題は difficulty 2501 と 2631）」にした
- 4：挿入 DP の段落に、大きい値から入れること・状態が左から見える個数であること・左端の 1 か所だけで増えることを足した（問題名は出さない）
- 5：ABC449 G の解法の詳細に $O(N \log N)$ と $M$ の現れ方を足した。未解決の点の「制約を確かめていない」は検証役が ikatakos の記録で $N \le 10^5$・$M \le 10^9$ と確かめたので解決
- 6：ACL の囲みの計算量を $O(n \log n + \log \mathrm{mod})$（法を固定すれば $O(n \log n)$）にした
- 7：要点から「上限つきの選び方は … 二項係数で求まり」の一文を削って summary にそろえた（summary への提案はしない）
- 採らなかった指摘：なし
