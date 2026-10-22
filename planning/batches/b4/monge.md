# b4 monge（Monge 性による DP の高速化）の報告と提案

- 書いたファイル：docs/dp/monge.md、snippets/monge/convolution.{cpp,yaml}、docs/img/monge/monotone-minima.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（期待と違う0）、textlint（エラー0、警告19。数式を含む文の長さ・数式の中の読点と角括弧の誤検出、並列の「からだけ」「も」）。SVG は render_svg で 360px・720px を目視した
- 使った出典：
  - https://speakerdeck.com/tatyam_prime/monge-noshou-yin-shu （新しいドメイン speakerdeck.com。check_noai で noai・noimageai の指定なしを確認）：定義・確かめ方・各アルゴリズムの計算量
  - https://noshi91.hatenablog.com/entry/2023/02/18/005856 （付録 B の noshi91.hatenablog.com）：簡易版 LARSCH
  - https://github.com/yosupo06/library-checker-problems/tree/master/convolution ：min_plus_convolution_convex_arbitrary・convex_convex の存在と凸の定義
  - kmjp 氏の abc348_g・abc383_g・abc355_g の記事、ikatakos 氏の abc458 の記事（G の解法の節だけ）
- 動く図は作っていない（visual は priority 3 なので静的な SVG 1 枚で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc458_g | summary | 日ごとの収入と費用が決まっている中で、最終的に脱出できる子どもの人数の最大を求める。（本文の行はこの仮の要約。問題文は読めないので、問いの細部はメインで確かめてほしい） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0516_abc458 （解法の節：答えの人数で二分探索し、日ごとの収入・残っている人数に比例する費用・脱出の費用で残量を DP） |
| abc458_g | approach | 答えの人数で二分探索し、脱出した人数についての残量の最大を上に凸な折れ線で持つ。脱出の遷移は 1 次の列との (max,+) 畳み込みで、傾きの列（Slope Trick に近い持ち方）でならし O(N) に判定する | 同上 |
| abc458_g | pages | slope-trick にも練習として載せる候補（解き方の中心は折れ線の傾きの管理） | 同上 |
| abc348_g | evidence | 2 つ目の裏付けが見つからなかった（第三者のブログを検索したが該当なし）。kmjp 氏の 1 件のまま | — |
| abc348_g | approach | 「B の昇順に並べ、分割統治で上に凸な列（A の和）と任意の列を (max,+) 畳み込みで合成する（monotone minima）」に。今の「凹な列のマージ」だけだと、g の側が凸でなく monotone minima を使う点が抜ける | https://kmjp.hatenablog.jp/entry/2024/04/08/0930 |
| abc383_g | approach | 「始点を K 以上離して選ぶ問題にし、両端の使えない個数ごとに上に凸な列を持って、分割統治で差分のマージにより合成する」 | https://kmjp.hatenablog.jp/entry/2024/12/13/0930 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| (min,+) 畳み込み | min-plus-convolution | 列 a, b から c_k = min_{i+j=k}(a_i + b_j) を作る演算。ふつうの畳み込みの積を和に、和を最小に置き換えたもの。最大を取るものは (max,+) 畳み込みと呼ぶ |
| Monge | monge | 行列 A が、行 i1 < i2 と列 j1 < j2 のどれでも A[i1][j1] + A[i2][j2] ≤ A[i1][j2] + A[i2][j1] を満たす性質。各行の最小値の位置が単調になる（本文は monge#definition） |
| 上に凸 | concave | 隣との差が広義単調に減る列・関数。最大化の「k 個選ぶ」問題の答えでよく現れる（凸関数 #convex-function の項に併記でもよい） |

## 手引きへの提案

- §6 の記法に (min,+)・(max,+) の書き方（全角の括弧に入れず半角の `(min,+)`）を足すとよい。aliases の `'(max,+) 畳み込み'` と本文の表記をそろえた
- 付録 A の DP の語に「monotone minima」「(min,+) 畳み込み」を足す候補（本文で英字のまま使った）
- 付録 B に speakerdeck.com を足す候補（スライドごとに書き手が違うので、確かめたのは tatyam_prime の「Monge の手引書」だけ）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc355_g | N 個の位置から K 個を選び、重み付きで決まる値との最小の距離の期待値（の分子）を最小にする。区間のコストが Monge なので monotone minima と Alien DP を組み合わせる。今は alien-dp の練習なので、monge にも練習として載せる候補 | https://kmjp.hatenablog.jp/entry/2024/06/05/0900 |
| codequeen2023_final_e | 列をいくつかの区間に区切り、各区間の最大 − 最小の和を最大にする。区間のコストが Monge（最大化の向き）で LARSCH により O(N log N) と記事にあるが、記事の主な解法は Monge を使わない O(N) の DP なので、練習にするなら「別解」扱い | https://drken1215.hatenablog.com/entry/2023/09/04/214120 |
| arc067_d | 焼肉店を巡る区間の選び方で、最適な左端の単調性を使う（research/02 の候補）。裏付けが USACO Guide だけで、問いを第三者の解説で確かめていない | （未確認） |

## 未解決の点

- abc458_g の要約は解法の節から読み取った仮のもの。問題文を読めないので、問いの細部（人数の最大を求めるのか、など）はメインか検証役が別の解説で確かめてほしい
- Knuth-Yao・SMAWK・LARSCH を使う確認済みの ABC は見つかっていない（research/02 と同じ）。本文では「必須の問題は見つかっていない」と書いた
- 「Monge なコストで k 個の区間に分ける最小値は k について凸」は tatyam 氏の資料の Alien DP の節に基づく。本文では証明を載せていない
- monotone minima で「同じ値のときに残す側をそろえる」の扱い：最も左を残す前提で証明したことを書いた。左右を混ぜても値は正しいかもしれないが、確かめていない
- snippets の core は (min,+) の向き（Library Checker に合わせた）。例題は (max,+) なので、符号の反転で使うと本文に書いた

## 検証の指摘への対応

- 指摘 1〜5 はすべて直した。採らなかった指摘はない
- 指摘 3：要点の「いつ使うか」の 1 行目は front matter の signs と同じ文言なので $c(a, c)$ のまま残し、#definition・#knuth-yao の本文だけ $l_1 \le l_2 \le r_1 \le r_2$ に替えた。#definition に要点の式との対応を 1 文で書いた
- 指摘 5：$K$ の上限は確かめていないので、数値は書かず「$K$ は小さいので」とした。上限はメインで確かめてほしい
- 未解決の点 4（同じ値のときの扱い）は検証役の指摘 2 で解決したので、証明の折りたたみに後半として加えた

## 台帳への提案（検証の後の追加）

- abc458_g の approach の「ならし O(N)」は、検証役によれば記事では単に O(N)。ならしの書き方のままでよい（stack の pop がならし）
