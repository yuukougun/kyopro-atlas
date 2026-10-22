# static-top-tree の報告（b4・執筆）

- 書いたファイル：docs/tree/static-top-tree.md、snippets/static-top-tree/stt.{cpp,yaml}、docs/img/static-top-tree/tree.svg・stt.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と検証, anchor: library}` を足した（hld の library と同じ扱い）
- 定型でない見出し：`## 学ぶための資料 {#resources}`（hld・dynamic-dp と同じ。sections には載せていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 3：要点の囲みの文の長さ、別行の数式を含む文の長さ、参考の Library Checker の行の長さ。どれも数式・URL 名の誤検出として残した）
- 図：tree.svg（幅 300）・stt.svg（幅 400）を render_svg.py で 360px・720px にして目で確かめた。stt.svg の形は、コード片の組み立てを実際に動かして得た節点の親子（圧縮(0, 圧縮(1, 圧縮(2, 3)))、0 の下に 4・6 の併合）をそのまま描いた。visual は null なので動く図はない
- コード片：Static Top Tree の組み立て（build）と、ABC351 G と同じハッシュの DP（dp）。self_test で乱数の木 300 個 × 30 更新を愚直な方法と比べ、パス・星（N = 2^17）で高さが 4·17+4 以下を assert で確かめている。手元で測った高さは N = 2^17 でパス 18・星 21・完全二分木 49・乱数の木 46・毛虫 19（本文には書いていない）
- dynamic-dp の申し送り（向きをそろえる）：HL 分解の節で、一次関数の合成を番号の順（浅い方が左）に並べ、dynamic-dp#on-trees と同じ向きだと明記した。dynamic-dp の Static Top Tree の説明（圧縮と併合で高さ O(log N)、更新は O(log N) 回の合成）は本文と食い違わない

## 使った出典

- nyaannyaan.github.io（解説一覧：ABC351G に Static top tree、ABC311H に重軽再帰 DP のタグ。リンク先は atcoder.jp なので開いていない）
- ikatakos.com（ABC351 G の解法の節だけ：問い、HL 分解で O(N + Q log^2 N)、0 の個数を別に持つ工夫、公式解説が Static Top Tree で O(N + Q log N)）
- zenn.dev/blue_jam（5 つの操作、節点の数 O(N)、rake に交換法則が要ること）
- trap.jp（noya2「式変形で導出する Static Top Tree」：HL 分解の式からの導出、ABC351G が一次関数）
- maspypy.com（Point Set Tree Path Composite Sum：部品に持たせる値、根を変える版）
- ei1333.github.io（Static Top Tree DP のインタフェースと計算量）
- hitonanode.github.io（実装の参考としてだけ挙げた）
- www.luogu.com.cn（KK_lang の記事：ABC311 Ex の手法と O(N^{log2 3} X)）、www.cnblogs.com（Scarab の記事：ABC311 Ex の問いが頂点ごと・共通の X であること）、www.cnblogs.com/hikkio（問いの確認の補助）
- github.com/yosupo06/library-checker-problems（2 問の task.md）
- 新しく noai を確かめたドメイン（check_noai.py で指定なし）：trap.jp、hitonanode.github.io、ei1333.hateblo.jp（読んではいない）

## 台帳への提案

- abc351_g｜summary｜根付き木で、葉のハッシュは頂点の値 $A_v$、ほかの頂点のハッシュは $A_v$ に子のハッシュの積を足したものとする。$A_v$ を 1 つ書き換えるたびに、根のハッシュを 998244353 で割った余りを答える。｜ikatakos の解法の節、trap.jp
- abc351_g｜evidence｜既存の nyaannyaan に https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0427_abc351 と https://trap.jp/post/2861/ を足す（nyaannyaan のページはタグだけで、解説の本体は atcoder.jp）
- abc351_g｜checked｜2026-10-22
- abc311_h｜summary｜美しさ・重さ・2 色のどちらかを持つ頂点の根付き木で、頂点ごとに部分木から頂点を取り除いて親子の色がすべて異なる木を作る。残した頂点の重さの和が $X$ 以下での美しさの和の最大値を求める（取り除いた頂点の子は残った最も近い祖先につなぎ直す）。｜luogu・cnblogs の 2 本
- abc311_h｜evidence｜https://www.luogu.com.cn/article/1s1aiccu と https://www.cnblogs.com/Scarab/p/19057649 を足す
- abc311_h｜checked｜2026-10-22

## 用語集への提案

- なし（重い辺 heavy-edge・重いパス heavy-path・結合法則・交換法則・逆元は既存の語にリンクした）。Static Top Tree の「パスの部品（Path cluster）」「束の部品（Point cluster）」はこのページだけの語なので本文で定義した

## 手引きへの提案

- 発展の概要で、AtCoder の公式解説が主な資料のとき（ABC351 G の Static Top Tree）は、「学ぶための資料」に名前だけ書き、リンクしない書き方にした。この扱いでよいか決めてほしい
- Static Top Tree の 5 つの操作の日本語名を「頂点・辺を付ける・併合（rake）・頂点を付ける・圧縮（compress）」にした。付録 A に足すなら「圧縮（compress）・併合（rake）」

## 問題の補充の候補

- 確認済みの abc351_g（例題）・abc311_h（練習）で発展の目安は満たすので、新しい探索はしていない
- abc311_h は重軽再帰 DP（値の更新のない静的な木 DP）の問題で、このページの本題（更新のたびの木 DP）とは別の手法である。本文では「重い子を特別に扱う別の技法」として節の最後に置き、練習の方針で違いを書いた。tree-dp-square（二乗の木 DP）か、ナップサック型の木 DP のページの力試しへ移す方が合うかもしれない

## 未解決の点

- aliases の「重軽再帰 DP」は abc311_h の手法名で、Static Top Tree や動的木 DP の別名ではない。別名のままだと検索で誤解を招くので、aliases から外すか、本文の短い説明（heavy-path-dp の節の最後）への誘導として残すかを決めてほしい
- complexity の構築 O(N log N) はコード片の素朴な分け方（列を毎回走査して重みの半分で分ける）での見積もりである。工夫すれば O(N) で組める（maspy 氏の記事は yosupo 氏のスタックを使う方法に触れている）が、本文では確かめていないので書いていない
- 高さ O(log N) の説明は「列ごとの深さ log2(W/w) が打ち消し合う」直感で書き、厳密な証明は資料に任せた。資料で証明を確かめたわけではない（公式解説は読んでいない）
- 「ABC351 G の公式解説は、ABC の想定解として Static Top Tree を初めて正面から扱った」は、検索で見た第三者の記述（noya2 氏の記事の周辺）に基づく。検証で確かめてほしい
- Point Set Tree Path Composite Sum (Fixed Root) の「パスの部品に合成した一次関数・値の和・頂点数を持たせる」は maspy 氏の記事の要約に基づく助言で、自分で通したわけではない

## 検証の指摘への対応（b4 verify）

- 1〜9・11：すべて直した。11 はコード片の `HashDP::set` を `update`、`StaticTopTree::merge` を `build_balanced` に改名した
- 6：本文の平衡の段落に「コード片の組み立ては O(N log N)、工夫すれば O(N)（Luzhiled's Library は構築 O(n)）」を足し、complexity と要点を「構築 O(N log N)（工夫すれば O(N)）」にした
- 10：build の取り込みを build_balanced・compress・rake・add_edge・add_vertex の部分（約 35 行）に絞り、enum・メンバ・コンストラクタ・add は snippets に残した。本文で `add(k, l, r, t)` の意味を 1 文で説明した。dp の取り込み（約 36 行）は 5 つの操作の表と対応する本体なので残した
- 採らなかったもの：なし

## 台帳への提案（差し替え）

- abc311_h｜summary｜上の提案を次の文に差し替える：美しさ・重さ・2 色のどちらかを持つ頂点の根付き木で、頂点 $v$ ごとに、$v$ の部分木から $v$ 以外の頂点を取り除いて親子の色がすべて異なる木を作る。残した頂点の重さの和が $X$ 以下での美しさの和の最大値を求める（取り除いた頂点の子は残った最も近い祖先につなぎ直す）。
- abc351_g・abc311_h の checked 2026-10-22 は検証でも確かめ済み

## メインに決めてほしい点（変わらず）

- abc311_h をこのページの練習から tree-dp-square などへ移すか。移すなら aliases の「重軽再帰 DP」と #heavy-path-dp の最後の段落も移し先へ移す
