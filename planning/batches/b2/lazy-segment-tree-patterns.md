# lazy-segment-tree-patterns の報告（b2）

- 書いたファイル：docs/ds/lazy-segment-tree-patterns.md、snippets/lazy-segment-tree-patterns/{assign-add,flip-run,arith-add,two-seq}.{cpp,yaml}（どれも範囲 core。素朴な計算と assert で照合する）、docs/img/lazy-segment-tree-patterns/run-merge.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 本とも一致、textlint エラー 0・警告 15（数式を含む文の長さ・読点、半開区間 `[l, r)` の括弧の対応、要点の囲みの長い行。どれも規則の誤検出）。4 本のコード片は手元でランダムな入力 300 通りずつを流し、素朴な計算との assert が通ることも確かめた。SVG は render_svg.py の 720px で目視した
- 使った出典：drken（abc357_f・abc322_f・practice2_l）、merom686（abc332_f・abc371_f）、kmjp（abc237_g・abc265_g・abc470_g）、ACL の document_ja。新しいドメインはない。atcoder.jp・codeforces.com は開いていない
- 動く図は作っていない（visual は static・priority 2 で、型の表を Markdown の表にした。最長の連続のつなぎ方だけ SVG にした）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc470_g | summary | 非負整数の列のすべての連続部分列について、mex の総和を求める。 | https://kmjp.hatenablog.jp/entry/2026/08/13/0930 |
| abc470_g | approach | mex を「0〜m をすべて含む区間の数」の m についての和に言い換え、左端ごとの最小の右端（左端について単調）を、二分探索と区間代入・区間和で更新する（Segment Tree Beats の区間 chmax・区間和でもよい） | 同上（kmjp は Beats で解いている。単調性から区間代入に落とせることは本文で自分で示した） |
| abc470_g | evidence | kmjp の URL を足す（ikatakos のページは執筆の時点で 503 で読めなかった） | 同上 |
| abc371_f | evidence | https://merom686.hatenablog.com/entry/2024/09/15/021105 を足す（ikatakos は 503 で読めなかった） | merom686 は X_i − i の言い換えと、区間代入・最小・最大・和を持つ値を書いている |

- 本文の行は fix_problems が台帳から作れる形で書いた。abc470_g の行は上の要約で書いてある（台帳の summary が「（執筆時に確かめる）」のため。手引き §14-16）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 作用 | action | 列の要素の値を変える操作を、値から値への関数とみたもの。遅延セグメント木では「x を足す」「x にする」「0 と 1 を入れ替える」などの作用を区間にまとめて施し、2 つの作用を続けたもの（合成）も 1 つの作用として持つ |

（本文ではリンクを張っていない。足したら導入か design-steps の最初の「作用」にリンクできる）

## 手引きへの提案

- sections の title が長いページ（このページの design-steps は 56 字で、見出しとしては読みにくい）では、§14-12 の「長い title は anchor を変えずに短くしてよい」を骨格の段階で当てるとよい。案：design-steps の title を「設計の手順と載せられる 3 つの条件」にする（本文で条件を列挙しているので、括弧の中は要らない）。今回は title を変えていない

## 他のページへの申し送り

- handoff §1 の行（相手が draft になったので張り替えられる）：
  - inversion-number:135「0/1 の列の区間反転と区間の転倒数」→ `lazy-segment-tree-patterns.md#flip`
  - lazy-segment-tree:155「型の一覧は…にまとめる」→ `#pattern-table`
  - lazy-segment-tree:302「値と作用を自分で設計する」→ `#design-steps`
- segment-tree-monoids（前提。stub）と同じ anchor（design-steps・pattern-table）を持つ。向こうは一点更新のモノイド、こちらは作用の側の設計なので、向こうが書かれたら design-steps の手順 1〜3 を向こうの節へのリンクに置き換えられるかを検証役が見るとよい
- 本文から stub のページ（segment-tree-beats・sqrt-decomposition・sweep-line-2d・difference-sequence・mex・segment-tree-monoids）へは anchor なしでリンクした

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

数は足りている（例題 2・練習 4・力試し 2。abc319 以降が 5 問）。補うなら次の 1 問。

- abc455_f（ABC455 F. Merge Slimes 2、diff 1549、台帳で確認済み。lazy-segment-tree の練習）：区間加算のたびに、区間の値の相異なる 2 要素の積の和を mod で答える。arithmetic-add の節の「応用の型」（積の和に要る量を S に足す）の練習に当たる。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0425_abc455（lazy-segment-tree の参考と同じ。今回は 503 で読み直せなかった）

## 未解決の点

- ikatakos.com が執筆の時点で 503 を返し、台帳の evidence（abc371_f・abc470_g）を読めなかった。代わりに merom686（abc371_f）と kmjp（abc470_g）で確かめた。abc371_f の「右へ押すと k から始まる連続した範囲が g に揃う」「移動量は区間和の変化」は merom686 の記述と自分の導出で、abc470_g の「単調なので chmax を区間代入にできる」は自分の導出である（kmjp は Beats）。検証役に確かめてほしい
- abc332_f の答えが mod で求めるものかは、merom686 の記事に書いていなかったので本文で触れていない
- abc322_f の制約（N ≤ 5×10^5、Q ≤ 10^5）と閉区間・1-indexed の入力は drken の記事で確かめた
- 型の表の「区間代入・一次関数の合成」（verify の range_set_range_composite）は、mapping で h^len を繰り返し二乗法で作る O(log² N) の方法を書いた。h^len を前計算して O(log N) にする書き方もあるが、触れていない

## 検証の指摘への対応（b2）

- 直したもの：1（しきい値の二分探索で求まるのは位置 p の値・K 番目の値と書き直し、判定の計算量を足した）・2（確認問題 3 は「どちらも載らない」を先に書き、反例 (1, 2, 3) を添えた）・3（要点と complexity を「定数倍がおよそ K 倍」に）・4（2 回の累積和は取得が更新の後に来るとき、交互ならフェニック木、と条件を足した）・5（閉区間と明記）・6（表の補足と abc265_g の方針に「異なる値の対 6 つでもよい」を足した）・7（composition を「なしなら g、ほかは f と『なし』」に）・8（acl-standard と size-in-node の 2 つへリンク）・9（手順 1〜3 を 2 つに縮め、S の設計は segment-tree-monoids#design-steps と同じと書いた。手順は 4 つになった）・10（本文と確認問題 4 の $a$ を $\mathit{add}$ にそろえ、コードに合わせた）
- 採らなかったもの：なし
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 本一致、textlint エラー 0・警告 18（数式を含む文の長さ・読点・半開区間の括弧。誤検出）
- 台帳への提案（検証役の提案に賛成）：abc357_f・abc322_f・practice2_l・abc237_g・abc371_f・abc470_g・abc265_g の `checked` に 2026-10-21 を入れる（abc332_f は mod の有無が未確認のため保留）。abc371_f・abc470_g の evidence の追加は上の「台帳への提案」のとおり
