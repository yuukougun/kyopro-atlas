# mo-algorithm の報告（b2）

- 書いたファイル：docs/ds/mo-algorithm.md、snippets/mo-algorithm/mo-basic.{cpp,yaml}、snippets/mo-algorithm/mo-inversions.{cpp,yaml}、snippets/mo-algorithm/mo-tree.{cpp,yaml}、docs/img/mo-algorithm/query-order.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（catalog の choosing は骨格の段階で外れており、定型の `## 使い分け {#comparison}` にした）
- 構成：level 青・type technique なので §4 の technique（水・青・黄）に従った。必要になる場面・処理の流れ・計算量は what-it-does・ordering・implementation で兼ねた（§14-5）。acl は空なので ACL の囲みはない。黄の節（two-prefixes・mo-on-tree）と発展の節（variants）は、最初に追加の前提を書いた
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0（3 本。どれも起動時に小さな乱数の入力で素朴な数え方と比べる assert を持つ）、textlint エラー 0・警告 37（大半は数式の半開区間 $[l, r)$ の括弧の対応、数式を含む文の長さ・読点、図の代替テキストの長さ。誤検出として残した）
- 図：query-order.svg（visual priority 2 の静的な図。クエリを点 (l, r) に置き、N = 16・B = 4 の帯ごとに r を往復する道筋を「伸ばしてから縮める」の順の直角の折れ線で描いた）。render_svg.py で 360px・720px を目で確かめた。動く図は作っていない（priority 2 なので div も置いていない）

## 使った出典

- https://ei1333.hateblo.jp/entry/2017/09/11/211011（ei1333「Mo's algorithm」）：使える条件、ブロックの数 √Q と O(N√Q) の数え方、伸ばしてから縮める順、奇数ブロックの逆順、木上の Mo・時間付き Mo（ブロック n^(2/3)、O(n^(5/3))）の概要
- https://snuke.hatenablog.com/entry/2016/07/01/000000（snuke「Mo's algorithm とその上位互換の話」）：ブロックの大きさ N/√Q の改善、ロールバックで追加だけにする方法
- https://kmjp.hatenablog.jp/entry/2023/03/12/0900：例題 abc293_g（Mo、C(c, 2) の差分）
- https://kazun-kyopro.hatenablog.com/entry/ABC/242/G：例題 abc242_g（答え Σ floor(cnt/2)、N ≤ 10^5、Q ≤ 10^6、O(N√Q)）
- https://kmjp.hatenablog.jp/entry/2026/09/27/0930：練習 abc477_g（入りと出の列、LCA を一時的に足す、「個数が f 以上の値の数」の配列）
- https://kmjp.hatenablog.jp/entry/2024/12/14/0900：練習 abc384_g（(X, Y) の Mo、値で座圧した個数と和の BIT を A 側・B 側に 2 本ずつ）
- https://kmjp.hatenablog.jp/entry/2025/05/10/0900：力試し abc405_g（多項係数、値の平方分割でブロックごとに個数の和と 1/c! の積、伸縮 O(1)・取得 O(√N)）
- https://www.cnblogs.com/CR-J/p/19684169：補充の候補 abc448_f の確認だけ（本文には使っていない）
- 新しく noai を確かめたドメイン：ei1333.hateblo.jp・snuke.hatenablog.com（どちらも check_noai で noai・noimageai の指定なし。付録 B への追加を提案する）。take44444.github.io も確かめたが（指定なし）、読んでいない

## 台帳への提案

- なし（使った 5 問の summary・difficulty・役割は台帳のとおり。本文の行は fix_problems の検査で一致）

## 用語集への提案

- なし（リンクした half-open-interval・offline は既存）

## front matter・catalog への提案

- aliases の「クエリ平方分割」を外す：クエリ平方分割は「√Q 個のクエリごとに構造を作り直す」別の手法で、sqrt-decomposition#query-buckets（catalog の 05-ds §4.D の 3 番）が持ち主である。Mo's algorithm の別名として引くと誤った節に着く。term-index の「クエリ平方分割 → Mo's algorithm」も sqrt-decomposition へ向けるとよい
- aliases に「ロールバック Mo」を足す（variants の節で扱っている。時間付き Mo は既にある）

## 手引きへの提案

- 木上の Mo の記法：euler-tour#mo-on-tree の $\mathrm{ST}$・$\mathrm{EN}$（入りと出の両方を記録した列での位置）に本文をそろえた。§6 の木の記法には $\mathrm{in}$・$\mathrm{out}$ しかないので、長さ 2N の列の位置の記法として $\mathrm{ST}(v)$・$\mathrm{EN}(v)$ を §6 に足すとよい

## 問題の補充の候補

- abc448_f（ABC448 F. Authentic Traveling Salesman Problem、diff 1719、ap.py で確認）：平面上の点をすべて 1 回ずつ巡る閉路で、隣り合う点のマンハッタン距離の和が上限（解説によれば 10^10）以下になるものを出力する。x 座標で点を √N 個ずつのブロックに分け、ブロックごとに y の昇順・降順を交互に並べる（Mo の並べ方そのもの）。裏付け：https://www.cnblogs.com/CR-J/p/19684169 （解法とコード。制約と上限の導出は書かれていない）、https://www.cnblogs.com/rickylin/p/19687650/ABC448 （検索結果で見ただけ。未読）。abc319 以降の青で、ordering の節の「並べ方だけを使う」練習になる。上限の値と N の制約は別の解説で確かめてから台帳に入れたい
- 基本形の abc319 以降の問題は見つからなかった（catalog の level_evidence のとおり、最近の Mo はどれも拡張と組む G）

## 節へ張り替えるリンク（handoff の mo-algorithm の 6 か所）

- inversion-number:134（区間ごとの転倒数）→ `mo-algorithm#implementation`（左右で変化が違うときの 4 つの関数と BIT のコード片がある）
- offline-queries:267（オフライン BIT と Mo の使い分け）→ `mo-algorithm#what-it-does`
- hashing-for-sets:111（区間の集合を扱う方法の 1 つ）→ `mo-algorithm#what-it-does`
- hashing-for-sets:261（O(N√Q) の見積もり）→ `mo-algorithm#ordering`
- euler-tour:188・euler-tour:319 → `mo-algorithm#mo-on-tree`（euler-tour:195 の「2 回現れた頂点を打ち消す実装は、Mo のページの木上の Mo の節で扱う」も同じ節へリンクにできる）

## 未解決の点

- abc293_g の制約（N・Q・A_i の上限）は、kmjp の記事に書かれておらず確かめられなかった。本文では制約の数値を書かず、答えの大きさを「10^15 程度」とだけ書いた（同じ値が 2×10^5 個のときの C(n, 3) から）
- abc477_g の区間の取り方：kmjp の記事は「S の入りと T の入りの間で奇数回現れる頂点＋LCA」と読める説明だった。本文は euler-tour のページにそろえて「祖先なら [ST(u), ST(v)]、そうでなければ [EN(u), ST(v)] と LCA」と書き、mo-tree.cpp で素朴な数え方と 200 個の乱数の木で一致を確かめた
- 時間付き Mo の「N = 10^5 程度が限度」は、N^(5/3) ≈ 2×10^8 からの見当で、出典にはない
- 「std::function に入れると遅くなりやすい」は一般的な知識による注意で、このページでは計測していない
- abc242_g の B = √N と B = N/√Q の回数の比較（3.5×10^8 と 2×10^8）は、本文の式 N²/B + QB から自分で計算した値である

## 検証の指摘への対応（verify/mo-algorithm.md）

- 1・2・3・4・5・8・9：指摘の直し方のとおり本文を直した（4 は ordering の tip と abc242_g の解法の詳細の両方に「上限の見積もり」を添えた）
- 7：図の道筋を太く（3.5px）し、点の番号を 13px・円を半径 11 にした。ブロックの見出しを円と重ならないよう上へずらした。render_svg の 360px で確かめた
- 6：採らず、提案にした。summary と要点の「何ができるか」は食い違わせない規則なので、要点だけ直さず両方まとめてメインに委ねる

## summary の提案（指摘 6）

- front matter の summary と要点の「何ができるか」の「区間の種類数のように左右を合成できない量」を「区間の同じ値の組の数のように左右を合成できない量」に替える。区間の種類数は同じページの確認問題・使い分けで先読みと BIT の方が速いとしており、冒頭で引いた読者が種類数に Mo を選びかねない。メインが summary を直すとき、要点の行も同じ文に直す
