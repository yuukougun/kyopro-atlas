# segment-tree の報告（工程8b・バッチ b1）

- 書いたファイル：docs/ds/segment-tree.md、snippets/segment-tree/（usage・own・char-set の 3 組）、docs/img/segment-tree/prod-nodes.svg・set-path.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を見出しに合わせて短くした（anchor・level は変えていない。9 節とも同じ anchor）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check --page segment-tree 直すべき行 0（全体の --check は ds/kth-element.md:202 の label の末尾の空白 1 行で終了コード 1。担当外なので直していない）。check_snippets 3 組・期待と違う 0。textlint エラー 0、警告 21（数式の中の `[l, r)` の括弧の対応・数式の中の読点・数式を含む文の長さの誤検出だけ）
- 使った出典：ACL v1.6 の document_ja/segtree.md と atcoder/segtree.hpp（手元）、programming-hiroba.com（abc341_e）、merom686・drken1215 のはてなブログ（abc157_e）、qiita.com の aruru88・Konini64（abc476_e）・recuraki（abc285_f）、ikatakos.com（abc461_e。解法の部分だけ）。新しいドメインはない
- 動く図：priority 1 なので、§「なぜ O(log N) か」に置き場の div（`data-viz="segment-tree"`、config は `{"array": [5, 3, 7, 2, 6, 4, 8, 1], "op": "min", "ops": [{"type": "prod", "l": 1, "r": 7}, {"type": "set", "p": 5, "x": 0}, {"type": "prod", "l": 1, "r": 7}]}`）と、前後の文章だけを書いた。JS は作っていない。仕様の案：完全二分木の各ノードに区間と値を書く。prod は非再帰の手順どおり l・r を葉から 1 段ずつ上げ、使うノードを光らせて sL・sR の値を caption に出す。set は葉から根までの経路を順に作り直す。静的な図 prod-nodes.svg・set-path.svg と同じ列・同じ操作にそろえた

## 台帳への提案

- abc476_e｜summary｜数列の区間を指定するたびに、その区間の最小値と最大値の位置を入れ替え、すべての操作の後の数列を求める。｜https://qiita.com/aruru88/items/ca31e5a1e6f9a753cf33・https://qiita.com/Konini64/items/c53dbd8331ce8358f858（本文の行はこの文で書いた）
- abc476_e｜approach｜最小値用と最大値用のセグメント木に（値, 位置）の組を載せ、入れ替えは 2 点の更新にする｜同上
- abc461_e｜summary｜白いマス目の行を黒く塗る操作と列を白く塗る操作のたびに、黒いマスの数を答える。｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0606_abc461（本文の行はこの文で書いた）
- abc461_e｜approach｜同じ行・列への操作は最後のものだけを有効とし、時刻を添字にした有効な操作の数の区間和で寄与の差分を数える｜同上
- abc157_e｜evidence の補足｜drken 氏の記事は set・BIT 26 本の解法で、ビット集合の OR のセグメント木は merom686 氏の記事にある（evidence は両方あるので変更は不要。approach の「26 ビットで持ち OR」は merom686 氏の記事が裏付け）

## 用語集への提案

- なし（半開区間 `half-open-interval`・単位元 `identity-element`・結合法則 `associativity`・モノイド `monoid` は既存の anchor にリンクした）

## 手引きへの提案

- 骨格の sections に「使い分け（choosing）」が中身の節として載っているページ（このページ・lazy-segment-tree）と、§13.1 の定型の `## 使い分け {#comparison}` が併存している。このページは front matter の anchor（choosing）を変えずに使った。どちらにそろえるかを決めておくとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 今回は探していない。例題 2・練習 5 で目安を満たし、abc319 以降の ABC も練習に 2 問（abc476_e・abc461_e）ある
- 力試しが 0 問なので、余力があれば青の帯の一点更新・区間取得の応用（research/05 §5 の segment-tree-monoids の候補 abc309_f・abc223_f など）を、monoids のページと重ならない形で 1 問足すとよい（未確認。役割の判断はメインに任せる）

## 未解決の点

- abc476_e の問題文の詳細（数列が順列か、値に重複があるか、制約）は、第三者の記事のどちらにも書かれておらず確かめられなかった。summary は「数列」と書き、方針は（値, 位置）の組にして値の重複があっても動く形にした
- abc341_e・abc157_e の制約の上限は本文に書いていない（記事で確かめられた範囲だけを書いた）
- 図の SVG は手元に描画の道具がなく、表示を目で確かめていない（座標を手で調べ、XML として読めることだけ確かめた）。検証役に表示の確認を頼みたい
- 本文で節へリンクしたのは acl-reading#segtree-args と rolling-hash#hash-segment-tree（どちらも draft で見出しがある）。fenwick-tree・sparse-table・segment-tree-monoids・segment-tree-binary-search・dp-segment-tree・segment-tree-on-values・complete-binary-tree はまだ stub なので、ページへのリンクだけにした
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 8 回（WebFetch 7 回・題名の確認の curl 1 回）
