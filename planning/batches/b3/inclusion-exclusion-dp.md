# inclusion-exclusion-dp（包除 DP）の報告と提案

- 書いたファイル：docs/comb/inclusion-exclusion-dp.md、snippets/inclusion-exclusion-dp/{first-obstacle,ban-permutation,equal-blocks}.{cpp,yaml}、docs/img/inclusion-exclusion-dp/first-obstacle.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 3 件とも期待どおり（brute force の assert つき）／textlint エラー 0・警告 11（数式を含む文の長さ・数式の中の読点や括弧の誤検出、「に」の重複 2 件は言い換えると不自然になるので残した）
- 図：first-obstacle.svg（visual priority 2・static）を render_svg で PNG にして目で確かめた。動く図の div は置いていない
- 使った出典：drken（dp_y・arc115_e・arc101_c）、kmjp（abc309_g・abc214_g）、tibrella（abc309_g）。新しく noai を確かめたドメイン：blog.tibrella.space（check_noai で指定なし。記事は GNU FDL 1.3 と明記。方針の参考だけで文章は使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc309_g | evidence | `https://kanpurin.hatenablog.com/entry/2020/04/07/182948` を外し、`https://blog.tibrella.space/post/abc309g-solution/` を足す | kanpurin の記事は典型の索引で ABC309 G の解説ではない。kmjp の記事は包除を使わない直接の bitDP（位置と値の未確定を持つ）で、inclusion-exclusion-dp の approach（違反の位置を選ぶ包除）の裏付けは tibrella の記事だけ |
| abc309_g | approach の補足 | 今の approach のままでよい。insertion-dp 側の alternatives の approach「包除で違反する位置を選び…」は insertion-dp の方針として不自然（kmjp の解き方は包除なしで、未確定の個数と窓の bit を持つ DP）。insertion-dp 側は「位置と値の両方で、まだ相手が決まっていない個数と近くの bit を持つ DP」にするのがよい | https://kmjp.hatenablog.jp/entry/2023/07/08/1000 |

## 用語集への提案

なし（本文は用語集へのリンクを使っていない）。

## 手引きへの提案

- comb の書き方（§5）に「包除の和を DP にするときは、符号は値に掛けて運び、偶奇を状態に持たない書き方にそろえる（|S| ごとに別の係数が掛かる場合だけ個数を状態に持つ）」を足すと、tree-dp・insertion-dp など関連ページの書き方がそろう

## 問題の補充の候補

ABC の黄で、この手法が想定解の問題は見つけられなかった。発展の帯の候補だけ挙げる。

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc236_h（Ex. Distinct Multiples、diff 2898） | 各 i で D_i の倍数かつ M 以下の正整数を選び、すべて異なる列の数を数える。等しいと指定した組の集合で包除し、連結成分ごとの係数を bitDP でまとめる | challenge | https://kmjp.hatenablog.jp/entry/2022/01/24/1100 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0123_abc236 （どちらも検索結果の要約までで、本文は未読） |
| agc005_d（D. ~K Perm Counting、diff 2943） | すべての i で \|P_i − i\| ≠ K となる順列の数。違反のマスを鎖に分けてルークの置き方を DP で数え、(N−k)! を掛けて包除する | challenge（count-violations の型） | https://ei1333.github.io/luzhiled/snippets/memo/inclusion-exclusion.html （検索結果の要約まで、本文は未読） |

## 未解決の点

- abc309_g の N の上限を確かめていない（kmjp のコードの配列の大きさから 100 程度と推定）。本文では N の上限を書かず、「N = 100 なら約 5×10^7 回」と仮定の形で書いた
- frequency_evidence に「古い ABC 2 問」とあるが、ABC で直近にこの手法が想定解の問題は見つからなかった（problems_note どおり練習は arc115_e の 1 問）
- related に lattice-paths・dp-grid・counting-dedup から張られている「inclusion-exclusion-dp」へのリンクは、このページが draft になったので `#first-obstacle` に張り替えられる（b1 handoff の dp-grid:74・292、lattice-paths:112・176、b2 の counting-dedup:132）
- 本文から insertion-dp・tree-dp-square（どちらも stub）へページへのリンクを張った。monotonic-stack#dp-transition・knapsack-01・divisor-inclusion-exclusion・modint へもリンクしたが related にはない（related に足すかはメインの判断）

## 検証の指摘への対応（b3）

- 直した：1（落とし穴を「階乗の式を負の添字で使う」誤りに書き直し）、2（「少なくとも k 個」をやめ、指定して数えた和であることと戻す式 $e_t$ を添えた）、3（a：スタックの積み方と和の保ち方、b：$\mathrm{dp}[v][1] = 1$ の初期値）、4（$M$ を定義）、5（a：2 種類の移動の例、b：述語を足した）、6（練習・力試しの方針の 3 行に句点）
- 採らなかった：6 のうち #comparison の箇条書きの句点は、ほかのページの使い分けと書き方をそろえるためメインの判断に任せる（285 行は 5b の直しで述語を足したので句点が付いた）

### 提案（共有ファイル、検証の指摘から）

- 台帳 `data/problems.yaml` の abc309_g の evidence を kanpurin の 2020/04/07 の記事（ABC309 より前）から tibrella の記事に差し替える。insertion-dp 側の alternatives の approach を「包除なし」の書き方に直す（kmjp のコードは包除を使わない）
- 本ページの 5 問の checked に 2026-10-21 を入れる
- frequency_evidence の「古い ABC 2 問」の文言をメインで確かめる
