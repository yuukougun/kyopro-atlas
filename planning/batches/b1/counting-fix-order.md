# counting-fix-order の報告（工程8b）

- 書いたファイル：docs/comb/counting-fix-order.md、snippets/counting-fix-order/{bfs-coloring,tree-order}.{cpp,yaml}、docs/img/counting-fix-order/{relative-order,bfs-coloring}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（定型の節は §13-1 の見出しで置いた。使い分けは節 vs-dp が担うので「## 使い分け」は置いていない）
- 検査の結果：
  - check_pages --page counting-fix-order：エラー 0・警告 0
  - fix_problems --page で 3 行を台帳から作り、--check は直すべき行 0
  - check_snippets snippets/counting-fix-order：コード片 2・期待と違う 0（どちらも n が小さいとき全探索と assert で突き合わせる）
  - textlint：エラー 0。警告 7（要点の囲みの入れ子の箇条を 1 文と数える誤検出、図の代替テキストの助詞、数式の読点、「重複も漏れも」の慣用の「も」、「に」の重なり 3 か所）
- 使った出典（どれも付録 B のドメイン。新しいドメインなし）：
  - https://drken1215.hatenablog.com/entry/2019/07/08/002700 ：例題 abc133_e の問い・根の子とそれ以外の子の選択肢
  - https://kmjp.hatenablog.jp/entry/2019/07/07/1000 ：abc133_e を DFS 順に塗る方針（DFS 順でも成り立つことの裏付け）
  - https://drken1215.hatenablog.com/entry/2020/01/12/224100 ：abc151_e の問い（この記事は隣り合う差の寄与で数える別の方針）
  - https://kmjp.hatenablog.jp/entry/2020/03/28/1030 ：abc160_f の問いと、多項係数を合わせる全方位木 DP
  - https://qiita.com/AKpirion/items/21b1aead96fec77d67ef ：abc209_c（台帳にない。本文では問題 ID を出さず型だけ書いた）
  - N!/Π sz の式と、根を移すときの ans[v] = ans[u]·sz[v]/(N − sz[v]) は自分で導き、snippets の全探索（n ≤ 8）で確かめた

## 台帳への提案

- abc160_f：evidence の 1 件目 https://kanpurin.hatenablog.com/entry/2020/04/07/182948 は「典型問題メモ」の目次で、この問題の解法の記述がない。裏付けにならないので外すか、解説の記事に差し替える
- abc151_e：evidence の drken の記事は「隣り合う差 × またぐ選び方の数」で解いており、alternatives の counting-fix-order 用の approach（各要素が最大・最小になる数を二項係数で数える）とは方針が違う。どちらでも解けるので内容は正しいが、approach の裏付けを足すなら別の解説を探す
- 新規 abc209_c（下の「問題の補充の候補」）

## 用語集への提案

- 半順序｜partial-order｜要素の間の「先・後」の関係で、すべての組が比べられるとは限らないもの。数え上げでは「A は B より先」という制約の集まりを指す（vs-dp の節で `../guide/glossary.md#partial-order` へリンクした）

## 手引きへの提案

- §4 technique の目安の「使い分け」について、sections に使い分けの節（このページの vs-dp）があるときは定型の `## 使い分け {#comparison}` を置かなくてよい、と明記するとよい

## 問題の補充の候補

- abc209_c（C. Not Equal、diff 285）：各 i について 1 以上 C_i 以下の整数を、すべて異なるように選ぶ方法の数。上限の小さい順に決めると選択肢が C_i − i 個で一定になり積の法則が使える（本文の bfs-order の節の最初の例）。裏付け https://qiita.com/AKpirion/items/21b1aead96fec77d67ef 。diff が低いので practice の先頭（易しい順）に置く想定
- abc319 以降の問題は見つからなかった（Web 検索 3 回）。水のページなので 1 問以上ほしいが、「n!/k!」「親が子より先」の型は ABC では近年少ない

## 未解決の点

- 動く図は作っていない（catalog の visual は static・priority 3）。静的な SVG 2 枚で代えた。SVG を画像にして見る道具が手元になく、文字の重なりは座標の計算でしか確かめていない（検証役が描画で確かめてほしい）
- 研究メモの「DFS 順では成り立たないことがある」は、abc133_e の型では誤り（行きがけ順でも成り立つ）。本文では「どの頂点も親より後に塗る順番なら成り立ち、親より先に子孫を塗ると壊れる」と書き、パスの反例を載せた
- vs-dp の節の「向きが混ざると木 DP で部分木の中での順位を状態に持つ」は一般論で、具体の問題で裏付けていない
- frequency は B のまま（recent 0）

## 検証の指摘への対応（2026-10-21）

- 1（直すべき・#sort-and-fix の同じ値）：直した。「より小さい値から」なら漏れ、「以下の（自分以外の）値から」なら重複する、と分けて書いた
- 2（挿入 DP の計算量）：直した。状態 N × N と、累積和で遷移をまとめて O(N^2) と書いた
- 3（「親が子より後」）：直した。番号 i を N + 1 − i に付け替える 1 対 1 対応で説明した
- 4（上限付きの添字）：直した。並べ替えた後の C_0 ≤ C_1 ≤ … と明記した
- 5・6（図）：直した。bfs-coloring.svg は幅 600 にし、凡例と答えの式を木の下へ移して 17px に、頂点 2 の「K−1」を円の左上へ移した。relative-order.svg は小さい文字を 15px にし、「残す」「× B が先」を x = 160・365・570 へ寄せて枠に収めた
- 7（半順序のリンク）：本文は変えず、上の「用語集への提案」をメインが反映する前提とした。反映しない場合はリンクを外してほしい
- 8（リンクの文字）：前の 3 つを題名に合わせた。「寄与」は文中の語として使っているのでそのままにした
- 9（tree-order.cpp の BFS の行）：core を波かっこで書き、「根 0 の親は -1 なので、根へ戻る辺は to != 0 で除く」とコメントを足した。brute 側は確かめ用なのでそのまま

## 台帳への提案（追記）

- 検証役の提案どおり、abc133_e・abc151_e・abc209_c の checked に 2026-10-21 を入れてよい。abc209_c を practice に足すときは、要約に解き方（並べ替え）を入れない
