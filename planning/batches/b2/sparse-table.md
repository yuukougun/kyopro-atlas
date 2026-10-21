# sparse-table の報告（b2 執筆）

- 書いたファイル：docs/ds/sparse-table.md、snippets/sparse-table/{sparse-table,disjoint}.{cpp,yaml}、docs/img/sparse-table/cover.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（両コード片は素朴な計算と assert で比べ、乱数 300 ケースでも通した）、textlint エラー 0・警告 31（数式を含む文の長さ・読点の数・数式の角括弧の誤検出が中心）
- 図：cover.svg を render_svg.py で 360px・720px の PNG にして目で確かめた
- 動く図：catalog の visual は priority 2・static なので、静的な SVG で代えた（動く図の置き場は作っていない）
- 使った出典：drken の abc282_f の記事（制約 N ≤ 4000・区間 50000 個まで）、Kazun の abc254_f の記事（隣接差の gcd・Disjoint Sparse Table）、cp-algorithms（冪等の要件・段が外側の持ち方・DST の存在。文章と図は使っていない）、Library Checker Static RMQ、cppreference の bit_width。新しいドメインはない

## 台帳への提案

- abc254_f｜pages に `{id: sparse-table, role: practice}` を足す｜列が変わらない区間 gcd を Sparse Table（冪等）で引く型の代表。本文では問題 ID を出さず「区間の gcd」の型として書いた｜https://kazun-kyopro.hatenablog.com/entry/ABC/254/F
- abc282_f｜checked が null｜evidence の記事が abc282_f のものであることと、制約（N ≤ 4000、出力できる区間は 50000 個まで）を確かめた。checked を 2026-10-21 にしてよい｜https://drken1215.hatenablog.com/entry/2022/12/29/112939

## 用語集への提案

- 冪等｜idempotent｜演算 · がすべての x で x · x = x を満たすこと。min・max・gcd・AND・OR は冪等で、和・XOR は冪等でない。Sparse Table で重なった 2 区間を結んでよい理由になる
  - check_pages が未登録の anchor をエラーにするので、本文の「冪等」（what-it-does の箇条書き）はリンクなしにした。用語集に足したら `[冪等](../guide/glossary.md#idempotent)` に張り替える

## 手引きへの提案

- §13-5 は「用語集へのリンクはまだなくても書いてよい」とするが、check_pages は未登録の anchor をエラーにする。どちらかにそろえたい（警告に下げる、または手引きを「提案だけにしてリンクは張らない」に直す）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc254_f（Rectangle GCD、diff 1764、台帳で確認済み）：(i, j) 成分が A_i + B_j の行列の部分長方形の gcd を多数答える。隣接差の区間 gcd に直し、更新がないので Sparse Table で引ける｜https://kazun-kyopro.hatenablog.com/entry/ABC/254/F（練習に推す）
- そのほかは見つからなかった。catalog の problems_note のとおり、abc319 以降で Sparse Table が要る問題は今回も探し当てられていない。LCA（オイラーツアー＋RMQ）・LCP の区間最小の問題は各ページの持ち物なので、ここには足していない

## 未解決の点

- 練習問題の節がない（台帳で sparse-table に付いた練習がない）。abc254_f を足したら `## 練習問題 {#practice}` を作る
- abc282_f のクエリ数の上限は記事の要約でしか確かめていないので、本文には書いていない
- 冪等の説明で「左の区間を先に結べば交換法則は要らない」と書いた（(A·B)·(B·C) = A·(B·B)·C の組み替え）。証明は本文にあるが、検証役に確かめてほしい
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 4 回（WebSearch 1 回を含む）

## 検証の指摘への対応（b2）

- 直すべき 1（区間の gcd の型）：直した
- 直すとよい 2〜8：すべて採って直した（3 は「コードは半開区間で受け取る」ことも添えて、本文の閉区間の説明の $l = r$ と混同しないようにした）
- 採らなかったもの：なし
- 台帳への提案（検証役と同じ）：abc282_f・abc254_f の `checked` に 2026-10-21。abc254_f の pages に `{id: sparse-table, role: practice}` を足す。用語集に「冪等」を足したら what-it-does の「冪等」をリンクにする
- 道具への備考：render_svg.py の 720px の PNG で図の下が切れる（検証役の備考）
