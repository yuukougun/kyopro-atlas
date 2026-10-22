# alien-dp の報告と提案（b4）

- 書いたファイル：docs/dp/alien-dp.md、snippets/alien-dp/nonadjacent.{cpp,yaml}、docs/img/alien-dp/tangent.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と確かめ方, anchor: library}` を足した（§13-10 の「自作するときの要点と Library Checker の対応」の置き場）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 0、check_snippets 一致（6 case と、main の中で乱数 2000 列を素朴な DP と比べる assert）、textlint エラー0・警告14（数式を含む文の長さ・図の代替テキストの読点・助詞の重複の誤検出）
- 図：tangent.svg を render_svg.py で 360px・720px にして目で確かめた（ラベルと線の重なりを直した）。visual は priority 3（static）なので動く図の置き場は置いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc355_g | summary | 1 から N の位置から K 個を選び、重みに比例する確率で決まる位置と、選んだ中で最も近い位置との距離の期待値を最小にする。 | https://kmjp.hatenablog.jp/entry/2024/06/05/0900 （kmjp 氏の解説の問題の読み取り。出力の形（期待値の何倍か）は確かめていないので、本文は「期待値を最小にする」にとどめた） |
| abc218_h | evidence | 追加：https://kmjp.hatenablog.jp/entry/2021/09/12/0930 （赤を隣り合わせない形への言い換えと、順序付き集合による貪欲） | evidence を2つ以上にする（§15-6）。既存の kanpurin 氏の一覧は Alien DP の項に abc218_h を載せている |
| abc464_g | evidence | 追加の候補なし。ikatakos 氏の記録の解法の節で、隣り合わない選択（コストの和の最小）と取り消し付きの貪欲を確かめた。記事は「1 つの x なら凸性から Alien DP も使えるが、多くの x が要るので向かない」と書いている | — |
| abc464_g | approach | 「隣り合わない k 個を選ぶ和の最大」は記事では「コスト C_i の和の最小」（最小化の向き）。approach を「隣り合わない x 個を選ぶコストの和の最小を、すべての x について求める」に直すとよい | ikatakos 氏の記録 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 凹関数（上に凸） | concave-function | グラフ上の 2 点を結ぶ線分が、その区間でグラフより上にこない関数である。整数の上の関数なら、差 $f(x+1) - f(x)$ が広義単調減少であることと同じで、$-f$ が凸関数であることと同じである。 |
| Lagrange 緩和 | lagrangian-relaxation | 制約（個数がちょうど K など）を外し、破った量に比例する罰金を目的関数に加えた問題を解く方法である。罰金の係数を調整して元の問題の答えを得る。競技プログラミングでは Alien DP の別名として使われる。 |

本文では「上に凸」を使わず「$-f$ が凸関数」「得が広義単調減少」で書いた（用語集にリンクできる語だけを使うため）。

## 手引きへの提案

- §5 dp に「Alien DP で同点の個数があるときは、罰金つきの問題で個数の少ない方を選ぶと決め、cnt(λ) ≤ K となる最小の整数 λ で g(λ) + λK を答える（返った個数ではなく K を掛ける）。値しか返せない罰金つきの問題では、h(λ) = g(λ) + λK を整数の三分探索で最小にする」を足す案。持ち主は alien-dp#binary-search-lambda
- 発展の概要に「自作するときの要点」の節を足すときの anchor を `library` にそろえる案（hld も `library`）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc305_h（Ex. Shojin、diff 3344、ap.py で確認） | 問題の列を連続する区間（日）に分けるコストの最小を、日数の制約を罰金に置き換えて求める（research/02 §5.1 の記述。問いは未確認）。発展なので力試しの候補。台帳に項目がない | https://kanpurin.hatenablog.com/entry/2020/04/07/182948 （Alien DP の項の一覧に ABC305 H がある）。解法の第三者の解説は未確認なので、追加するなら kmjp 氏の 2023-06 の記事などで問いと解き方を確かめる必要がある |

本文では abc305_h に触れていない（§13-6）。

## 未解決の点

- abc218_h の例題の方針のうち「R ≤ N − R なら赤を隣り合わせない置き方に最適解がある」は kmjp 氏の記事の主張に従った。Alien DP で直接（直前の色を状態に持つ DP で）解く解き方は、kanpurin 氏の一覧が Alien DP の項に載せていることと、言い換え後の問題がコード片の問題と同じ形であることで裏付けた。公式の解説は開いていない
- abc355_g の「区間のコストが Monge になる」は kmjp 氏の解説が証明なしに使っている（本文は「Monge になる」と書いた）。第三者の証明は確かめていない
- with-monge の節の「Monge な区間分割では f(K) が凸」は noshi91 氏の記事の補題（Monge グラフの d-辺最短路長の凸性）に従った。区間分割は 0 から N へのパスで辺の数が区間の数に当たる対応なので同じである
- 取り消し付きの貪欲の正しさは「詳しい証明は資料に任せる」とした。学ぶための資料に、この貪欲の証明を日本語で書いた資料（はてなブログなど）を見つけられなかった。見つかれば資料に足すとよい
- Library Checker に Alien DP そのものの問題はない（GitHub の library-checker-problems の問題の一覧で convex・monge・edge などを検索して確かめた）
- 新しく noai を確かめたドメイン：soi.ch（https://soi.ch/wiki/alien-optimization/。noai の指定なし。ページに利用条件の記載は見当たらない）。noshi91.github.io は付録 B にある（記事は CC BY 4.0）
- 使用量の目安：道具の呼び出し 約45回、Web 取得 7回（検索 4回）

## 検証の指摘への対応（b4 verify）

- 直すとよい 8 件をすべて直した（1 同点の決まりの理由を 2 文に分けて差の不等式で説明、2「限られる」を見た範囲の事実に、3 Monge の不等式を $a < b < c < d$ に、4 コード片の二分探索の不変条件のコメント、5「小さくなる」を「大きくならない（広義単調減少）」に、6 soi.ch の注記、7 LARSCH に monge#smawk-larsch へのリンク、8 ABC355 G の方針に番兵と端の区間を追記）。採らなかったものはない
- 検査：check_pages エラー0・警告0、fix_problems --check 0、check_snippets 一致、textlint エラー0（警告15、長い文と助詞の重複の誤検出）
- 台帳への提案（検証役から）：abc218_h・abc355_g・abc464_g の `checked` を 2026-10-22 にする
