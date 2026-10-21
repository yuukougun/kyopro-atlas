# segment-tree-on-values の報告と提案

- 書いたファイル：docs/ds/segment-tree-on-values.md、snippets/segment-tree-on-values/{count-sum,top-k,dynamic-odd-sum}.{cpp,yaml}、docs/img/segment-tree-on-values/count-sum-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を見出しに合わせて短くした（dp-on-values・top-k-sum・dynamic-segment-tree。anchor と level は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 3 本とも一致、textlint エラー 0（警告 23。半開区間 `[l, r)` の括弧の対応、数式を含む文の長さ・読点の数、「に」の重なりなどの誤検出）
- 図：visual は priority 2 の static なので SVG 1 枚（ヒストグラムと（個数, 和）のセグメント木、K = 2 の境界）。動く図は作っていない
- 使った出典：ACL document_ja（segtree・fenwicktree）、programming-hiroba.com（abc339_e）、drken（abc281_e・abl_d）、qiita gotoki_no_joe（abc276_f）、kmjp（abc403_g・abc287_g）、Library Checker の問題文（raw.githubusercontent.com の yosupo06/library-checker-problems。github.com 系で付録 B の範囲）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc339_e | evidence | 2 つ目の drken（abl_d の記事）は abc339_e の解説ではないので外すか、abl_d だけに残す | https://drken1215.hatenablog.com/entry/2020/09/27/080300 は ABL D の記事 |
| abc281_e | title | 末尾の空白を除いて `Least Elements`（fix_problems の label は空白なしで出ている） | — |
| abc403_g | approach | 「値域の動的セグ木に（個数, 奇数番目の和, 偶数番目の和）…」の evidence（kmjp）は想定解が動的セグ木と書くだけで、ノードの中身は書いていない。中身は本文で自分で導いた。中身まで書いた第三者の解説があれば evidence に足したい | https://kmjp.hatenablog.jp/entry/2025/04/28/1030 |
| abc287_g | role の並び | 変更なし（力試しで、易しい順に abc403_g（2028）→ abc287_g（2180）と並べた） | — |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| オンライン強制 | forced-online | 前のクエリの答えを使って次のクエリの入力を復号させる形式。クエリを先読みできないので、座標圧縮やクエリの並べ替えなどオフラインの手法が使えない |
| 動的セグメント木 | （用語集でなく本ページの #dynamic-segment-tree へ） | 用語の索引に別名「動的セグ木」として載っていればよい |

## 手引きへの提案

- §5 ds の「保つ性質・各操作の手順・境界」の 3 つの小見出しは、BIT・セグメント木そのものでない「使い方のページ」（このページなど）では、最初の節の下に置けば足りた。そう明記するとよい
- 「ACL では」の囲みに見出しを付けるか（定型の見出しの一覧にない）が分からなかった。今回は見出しを付けず、最初の節の末尾に置いた。定型の見出し `## ACL では {#acl}` を §13 に足すか、見出しなしと決めてほしい

## 問題の補充の候補

- 足りている（例題 2・練習 2・力試し 2。abc319 以降は abc339_e・abc403_g）。練習を増やすなら、値を添字にした（個数, 和）や区間 max の DP の水の ABC（abc319 以降）を探す余地がある。今回は ap.py での探索はしていない

## 未解決の点

- abc339_e の値の上限（$5 \times 10^5$）は第三者のコードの定数から読んだだけで、本文には「値の上限が小さい」としか書いていない
- 動的セグメント木のメモリの見積もり（$Q = 2 \times 10^5$ で約 200 MB）は、このページのコード片のノードの大きさでの概算。abc403_g の Q の上限は確かめていない（本文では Q の値を問題に結び付けていない）
- Library Checker の point_set_range_composite_large_array の N の上限は、問題文がパラメータ（N_MAX）で書かれていて確かめきれなかった。本文では「長さの大きい列」とだけ書いた
- related の top-k-multiset（draft）の #by-index から本ページへのリンクがある。本ページからは top-k-multiset のページへリンクした（節は指していない）
