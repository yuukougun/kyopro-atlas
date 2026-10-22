# rollback-union-find の提案（b4）

- 書いたファイル：docs/ds/rollback-union-find.md、snippets/rollback-union-find/version-tree.{cpp,yaml}、docs/img/rollback-union-find/dfs-history.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。節は足していない
- 検査：check_pages（エラー・警告 0）、fix_problems --check（0）、check_snippets（4 case 一致）、textlint（エラー 0、警告 12：数式を含む文の長さ・図の代替テキスト・参考の行・数式内の角括弧の誤検出・助詞の重なり）
- 図：render_svg.py で 360px・720px を目で確かめた
- 新しく noai を確かめたドメイン：devgenjin77.hatenablog.com（指定なし。ただし abc302_h の解説はなかったので使っていない）

## 台帳への提案

- abc302_h｜evidence｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/0520_abc302 を足す（解法の節で、値を頂点・ボールの組を辺にし成分ごとに min(頂点数, 辺数)、経路圧縮なしのロールバック UF を DFS で使うことを確かめた）

## 用語集への提案

- なし（rollback・offline・amortized-complexity は既存の語にリンクした）

## 手引きへの提案

- ds の節：取り消しの間に値を加える問題（オフライン動的連結性の頂点加算など）では、根の合計を「元の値を書き戻す」方式で戻すと加えた値が消える。Union-Find の木の各頂点に下の合計を持たせ、加算は v から根までの経路すべてに足し、取り消しは引き算にする（根だけに足すと、取り消しで分かれた側から x が抜けない）。持ち主は rollback-union-find#offline-dynamic-connectivity。offline-dynamic-connectivity を書く人への申し送りにもしてほしい

## 問題の補充の候補

- ABC で取り消せる Union-Find が要る問題は abc302_h のほかに見つからなかった（drken 氏の「undoつきUnion-Find」カテゴリーも ABC は abc302_h だけで、残りは Codeforces）。研究メモのとおり、abc334_g（diff 2242）は kmjp 氏がオフライン動的連結性で解いているとあり、offline-dynamic-connectivity の例題の候補（このページでは使わなかった。裏付けの URL は研究メモ 03-graph §4.D に記載なし、要確認）
- 本文では Library Checker の Persistent Unionfind と Dynamic Graph Vertex Add Component Sum を練習（§15-5 の小見出し）に置いた

## 未解決の点

- offline-dynamic-connectivity（stub）とは手順の要点（区間を求める・セグメント木に載せる・DFS で併合と取り消し・O(Q log Q log N)）が重なる。向こうを書くときに、詳しい手順と頂点加算の工夫の持ち主をどちらにするか決めてほしい（今はこのページに頂点加算の工夫を書いた）
- root-path-dfs#no-path-compression とは、記録 2 件・経路圧縮すると戻しても分かれない・union by size で O(log N) の 3 点で食い違わないことを確かめた
- 公式の解説（atcoder.jp）は開いていない

## 検証の指摘への対応

- 1（直すべき）：直した。「境界」を「par を書き戻すだけなら害はない。引き算で戻す値は別」に限定し、頂点加算の段落に「同じ成分どうしの併合（a = b）の記録を取り消すときは引かない」を足した
- 2〜6（直すとよい）：すべて直した。5 の確認問題 1 は、検証の例（経路圧縮をすべて記録すればよいのでは）が本文第 2 段落の写しに近くなるので採らず、「undo で b の par だけを戻し a の大きさを戻さないとどうなるか」（same は正しいが size が狂い、union by size の高さの保証が崩れる）に替えた。3 は本文の末尾（ライブラリを使う文の直後）に違いを添えた。6 は図の題を tspan の下付きにし、360px で確かめた

## 追加の提案（検証を受けて）

- front matter の verify：コード片が確かめているのは persistent_unionfind の形なので、`verify: [persistent_unionfind, dynamic_graph_vertex_add_component_sum]` にするかはメインの判断に任せる（catalog 由来のため変えていない）
- 手引き・offline-dynamic-connectivity への申し送り：頂点加算の工夫で、同じ成分どうしの併合（a = b）の記録を取り消すときは sum を引かない（引くと成分の合計が 0 に消える）。上の「手引きへの提案」に加えてほしい
