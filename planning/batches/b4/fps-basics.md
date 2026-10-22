# fps-basics（形式的冪級数と多項式の演算）の報告

- 書いたファイル：docs/math/fps-basics.md、snippets/fps-basics/newton.{cpp,yaml}（図は描いていない。catalog の visual が null のため）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に中身の節「式の形から使う演算を選ぶ」（anchor signs）を先頭に足した（§4 の overview の「サイン」にあたる。既存の anchor は変えていない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 18。数式を含む文の長さ・数式の中の助詞の重なり・参考の題名の「「」の連続で、§13-8・§14-25 の誤検出として残した）
- 使った出典（新しく noai を確かめたドメインはない。どれも付録 B にある）：
  - https://drken1215.hatenablog.com/entry/2023/09/03/161400（例題 ABC318 Ex の問い・包除原理・閉路の大きさの DP）
  - https://qiita.com/hotman78/items/f0e6d2265badd84d429a（各演算の計算量と定数項の条件）
  - https://nyaannyaan.github.io/library/fps/formal-power-series.hpp・https://nyaannyaan.github.io/library/fps/multipoint-evaluation.hpp（実装・多点評価の積の木）
  - https://drken1215.hatenablog.com/entry/2023/09/08/003100（Taylor shift の式）
  - https://drken1215.hatenablog.com/entry/2022/03/29/190000・2023/05/28/010200・2023/09/25/070100（練習 3 問）
  - https://github.com/yosupo06/library-checker-problems/tree/master/polynomial（問題名の一覧、inv・log・exp・pow・sqrt・division・taylor_shift・multipoint の task.md と pow の info.toml の M_MAX = 10^18）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc318_h | summary | 1〜N の順列 P・Q で辺 i → P_i（重み Q_i）を張ったグラフの閉路をなくすために消す辺の重みの和を最小化する問題について、辺を番号の小さい順に見る貪欲法と大きい順に見る貪欲法がどちらも誤る (P, Q) の組の数を 998244353 で割った余りで求める。 | drken の解説（上の URL） |
| abc318_h | approach | 包除原理で「どちらかの貪欲法が正しい」組を引き、正しい組の数を閉路ごとの確率 1/t の指数型母関数 exp(Σ x^t/t^2) の係数で求める（分割統治の畳み込みで DP を速くしてもよい） | drken の解説と手元の全探索（N ≤ 5 で答え 0・0・4・172・6828 が式と一致） |
| abc318_h | checked | 2026-10-22 | 同上 |

- abc318_h の裏付けは drken の 1 つだけである（§15-6 は 2 つ以上が目標）。kmjp の 2023-09-03 前後の記事と ikatakos の abc318 のページ（Ex の項は未作成）には解説がなかった。代わりに、本文の exp の式を手元の Python の全探索（N ≤ 5）で確かめた
- abc321_f の title の末尾に空白がある（'#(subset sum = K) with Add and Erase '）。label に影響するなら削るとよい

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 指数型母関数 | exponential-generating-function | 数列 c_n を Σ c_n x^n / n! の形に並べた冪級数。ラベル付きの部品の集まりを数えるとき、部品の母関数の exp が集まりの母関数になる |
| ニュートン法（冪級数） | newton-method-fps | 先頭 m 項が正しい近似から、先頭 2m 項が正しい近似を作る反復。逆元・exp・平方根を O(N log N) で求めるのに使う |

（本文ではどちらもリンクせず、本文で定義した。generating-function-counting の提案の「母関数」が用語集に入れば、このページからもリンクできる）

## 手引きへの提案

1. 発展の概要で「サイン」を節にするとき、骨格の sections にない中身の節を足すことになった（signs）。overview の骨格に「式の形から選ぶ」節を標準で置くか、要点の囲みのサインで済ませてよいかを §4 に書くとよい
2. generating-function-counting の提案 2 と同じく、`## 学ぶための資料 {#resources}` を sections に載せない定型の節として置いた

## 問題の補充の候補

- 例題 1・練習 3 で数は足りているので、新しい候補は台帳に足さなくてよい。ただし練習の 3 問はどれも FPS の演算を要しない（ABC245 D・ABC321 F は O(NM)・O(K) の足し引き）か、例題が別ページにある（ABC303 Ex）。FPS の演算をそのまま使う練習を足すなら、次の 2 問が候補（どちらも台帳になく、裏付けはタグだけなので、第三者の解説で確かめてから足す）
  - abc289_h（Ex. Trio）：多項式の逆元を使う発展問題（research/06 §5.7、裏付け https://nyaannyaan.github.io/docs/problems/editorials/ のタグだけ）
  - abc345_g（G. Sugoroku 5）：ニュートン法・ラグランジュの反転公式を使う発展問題（同上）
- abc462_g（Completely Wrong、2232、台帳では inclusion-exclusion の力試し）は「FPS で項をまとめる」と approach にあるので、fps-basics の練習にも載せられる（ikatakos・kmjp の解説で FPS の演算が何かを確かめてから）

## 未解決の点

- 本文の「ABC では主に difficulty 2200 以上の G・Ex で現れる」は、台帳の abc462_g (2232)・abc303_h (2501)・abc318_h (2785) と catalog の level_evidence からの見当である
- 例題 ABC318 Ex の exp による解き方は drken の記事にはない（記事は「公式解説は FPS」と触れるだけで、本文は分割統治の畳み込み）。式は自分で導き、N ≤ 5 の全探索で確かめた。検証役に式の導出（閉路ごとに確率 1/t で独立になる点）を見てほしい
- コード片の exp は反復ごとに log を呼ぶ簡単な形で、計算量は O(N log N) だが定数倍が重い。Library Checker の N = 5×10^5 で間に合うかは試していない（本文には「厳しいときは資料の書き方に替える」と書いた）
- 計算量の照らし合わせ：generating-function-counting の表（逆元・log・exp・累乗 O(K log K)、繰り返し二乗法 O(K log K log N)、多くの因子の積 O(K log^2 K)）と cayley-pruefer#with-polynomials（累乗 O(N log N)、繰り返し二乗法と畳み込み O(N log^2 N)）は、このページの値と一致している。generating-function-counting の to-fps の節と stirling-first・cayley-pruefer からのリンクは、節へのリンク（#operations・#polynomial-ops）に張り替えられる
- lagrange-interpolation・online-convolution は stub なので、ページへのリンクだけにした（§14-23）
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 約 9 回

## 検証の指摘への対応（2026-10-22）

- 1〜8 はすべて直した。7 は表の累乗を $O(N \log N)$ にそろえ、$a_d^M$ の $O(\log M)$ は「累乗で $a_0 = 0$」の注意に書いた
- 採らなかった指摘はない
- 台帳の提案：abc318_h の checked に 2026-10-22 を入れてよい（検証役の答え）
