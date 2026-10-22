# dynamic-dp の報告（b4・執筆）

- 書いたファイル：docs/dp/dynamic-dp.md、snippets/dynamic-dp/usage.{cpp,yaml}、docs/img/dynamic-dp/segment-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 定型でない見出し：`## 学ぶための資料 {#resources}`（hld と同じ。sections には載せていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 6：要点の囲みの文の長さ、半開区間の `[` の対、`と` の重複（単位行列の成分の列挙）、数式の行の長さ。いずれも誤検出か列挙のため残した）
- 図：segment-tree.svg（幅 400）を render_svg.py で 360px・720px にして目で確かめた。visual は static・priority 3 なので動く図は作らない
- 行列の向き：segment-tree-monoids にそろえ、横ベクトル・(p, q) 成分は p → q・op(a, b) = ab にした。縦ベクトルの書き方（matrix-power）との関係と、そのときの op は本文の節 order-and-identity に書いた。木の節だけは、HL 分解の番号（浅い方が小さい）と積の順をそろえるために縦ベクトルで書き、その理由を本文に書いた

## 使った出典

- kmjp.hatenablog.jp（例題の 3×3 の状態と遷移）、ikatakos.com（例題の 4×4 の状態。解法の節だけ）
- github.com/yosupo06/library-checker-problems（point_set_range_composite・point_set_tree_path_composite_sum_fixed_root の task.md。judge.yosupo.jp は SPA で本文が取れなかった）
- oi-wiki.org「动态 DP」（構成の確認だけ。例題が洛谷 P4719（木の最大重み独立集合）であることを確かめた。文章・図は使っていない）
- ACL のヘッダ third_party/ac-library/atcoder/segtree.hpp（prod が e() から掛け始めること、all_prod が d[1] を返すこと、size が bit_ceil(n) であること）
- 新しく noai を確かめたドメインはない（どれも付録 B にある）

## 台帳への提案

- abc246_h｜checked｜2026-10-22｜evidence の 2 本（kmjp・ikatakos）で問いと解法を確かめた。checked が null のまま
- abc246_h｜evidence｜変更なし（2 本で §15-6 を満たす）

## 用語集への提案

- なし（独立集合 independent-set・結合法則 associativity は既存の語にリンクした）

## 手引きへの提案

- 行列をセグメント木に載せるページの向き（横ベクトル・(p, q) は p → q・op(a, b) = ab）を §6 の記法に足すとよい。b3 handoff §3 の「どちらかにそろえる」の答えとして、segment-tree-monoids と dynamic-dp は横ベクトルにした。matrix-power は縦ベクトルのまま（累乗では向きが答えに影響しないため）で、どちらのページも互いの書き方と op の向きを本文で明記している
- 木の上の動的 DP のように「値が深い方から浅い方へ流れ、HL 分解の番号は浅い方が小さい」場面では、縦ベクトルの方が番号の順に積が並ぶ。static-top-tree を書くときに、この節（dynamic-dp#on-trees）と書き方をそろえるよう申し送りたい

## 問題の補充の候補

- 確認済みの例題 abc246_h だけで、発展の例題の目安（0〜2）は満たす。追加の候補は探したが、ABC で 1 点更新つきの列の動的 DP が想定解の問題は catalog の problems_note のとおり見つからなかった（研究資料 02-dp・05-ds の範囲。ap.py での新しい探索はしていない）
- 木の版は static-top-tree の例題 abc351_g（研究資料 04-tree §4.31）が近い。dynamic-dp に練習として足すかは、static-top-tree の執筆とあわせてメインで判断してほしい（台帳の status は未確認）

## 未解決の点

- static-top-tree は stub なので、本文の Static Top Tree の説明（「パスの圧縮」と「部分木の併合」で高さ O(log N) に組み直し、更新を O(log N) 回の合成で済ませる）は研究資料 04-tree §4.31 と一般的な理解に基づく。static-top-tree を書くときに食い違いがないか確かめてほしい
- 確認問題の「op を ba にしても例題の答えは変わらない」は、部分列の種類数が文字列の反転で変わらないことによる（? を含めても反転の全単射で成り立つ）。検証で確かめてほしい
- メモリの見積もり（N = 2×10^5、S = 10 の long long で約 420 MB）は 2 × 262144 ノード × 800 バイトの計算値

## 検証の指摘への対応（2026-10-22）

- 指摘 1〜7 をすべて直した（採らなかったものはない）
- 指摘 1 の front matter の signs（執筆者は直せない）：メインへの提案｜dynamic-dp｜signs の 2 つ目の text を `'列の区間 [l, r) だけで DP をしたときの答えを、クエリごとに求める'` にする（要点・本文の半開区間とそろえる。手引き §6）
- 指摘 4 は「積の定数倍」の箇条から mod のあふれの注意を分け、別の箇条「mod の掛け算のあふれ」にした
