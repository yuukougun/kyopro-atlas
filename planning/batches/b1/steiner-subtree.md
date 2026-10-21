# steiner-subtree の報告（工程8b・バッチ b1）

- 書いたファイル：docs/tree/steiner-subtree.md、snippets/steiner-subtree/（root-dfs・prune の 2 組の .cpp と .yaml）、docs/img/steiner-subtree/root-at-terminal.svg
- front matter で変えたもの：complexity（`O(N)（指定頂点の集合 1 つにつき）`）・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 上位の手法とのつながり, anchor: next-steps}` を足した（基礎の technique の目安の「上位の手法とのつながり」。ほかのページからリンクする単位になる）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 2 組で期待と違う 0。textlint エラー 0、警告 3（78・79 行は箇条の太字の見出しと本文を 1 文と数える「は」の重複の誤検出、136 行は参考の Qiita 記事の題名に含まれる読点）
- 使った出典：qiita.com の mattsunkun 氏の ABC368 解説（例題の問いと方針）、github.com の E869120 kyopro_educational_90 の sol/035-04.cpp（クエリ版の距離の和の半分）。新しいドメインはない（どちらも付録 B）
- 図：catalog の visual は static・priority 2 なので、静的な SVG 1 枚にした（動く図は作っていない）

## 台帳への提案

- なし（abc368_d の summary・approach・evidence は解説と一致した）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| NP 困難 | np-hard | 多項式時間で解ける方法が知られていない（見つかれば多くの難しい問題がまとめて解ける）種類の問題。競技プログラミングでは、入力のどこかが小さい（指定頂点が 10 個前後など）ことを使って指数時間で解く。 |

- 本文の vs-graph の節で `../guide/glossary.md#np-hard` にリンクした

## 手引きへの提案

- なし

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| typical90_ai | 木と多数のクエリで、各クエリの指定頂点をすべてつなぐのに必要な辺の数の最小値を答える（指定頂点を行きがけ順に並べ、隣り合う 2 点と最後・最初の距離の和の半分） | このページの力試し（台帳では auxiliary-tree の例題。例題は 1 ページだけなので、ここでは力試しに） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp |

- ap.py で題名を「Steiner」「Connectivity」「Visit」「Necessary」などで探したが、基礎の形の ABC の問題は abc368_d のほかに見つからなかった。catalog の problems_note のとおり練習は空のままにした

## 未解決の点

- related の `auxiliary-tree#steiner-queries` について：auxiliary-tree はまだ骨格（stub）なので、本文では節ではなくページへリンクした。auxiliary-tree が draft になったら、上位の手法とのつながりの節のリンクを `#steiner-queries` に直すとよい。同じく leaf-first（stub）は `#peel-leaves`、steiner-tree（stub）は `#on-tree` へのリンクがふさわしい
- tree-edge-contribution（stub）へのリンクは、辺の条件 $1 \le c[v] \le K - 1$ が辺ごとの寄与の数え方の簡単な例であるという意味で置いた。そのページの内容と合うかは、そのページの執筆時に確かめてほしい
- 例題の制約（N の上限）は第三者の解説に書かれていなかったので、本文に書いていない

## 検証の指摘への対応（verify/steiner-subtree.md）

- 指摘 1・2（直すべき）：落とし穴の「$K = 1$」を「1 を足し忘れて 0 を出す」誤りに書き直し、「再帰が深すぎる」を前提のページと同じ事実（手元の Linux の既定 8 MiB でパス状の $N = 2 \times 10^5$ は落ちる）に合わせた
- 指摘 3：要点で「$v$ の部分木（$v$ とその子孫）」と断り、root-at-terminal の冒頭で「答えの木」と呼び分けると断った。prune-leaves・next-steps の答えの側も「答えの木」に直した。ページの題名・aliases・例題の問いの言い換えは id と検索に関わるので「部分木」のまま
- 指摘 4：リンクはそのまま。用語集の提案の定義を次のように改める（メインが反映しない場合はリンクを外してほしい）：「NP 困難：多項式時間で解く方法が知られておらず、見つかれば NP に属するすべての問題が多項式時間で解けることになる種類の問題。競技プログラミングでは、入力のどこかが小さい（指定頂点が 10 個前後など）ことを使って指数時間で解く。」
- 指摘 5・6：next-steps の 2 つ目の箇条を「行きがけ順で隣り合う 2 点の LCA」「全体で $O(\sum K \log N)$ 程度」に直した
- 指摘 7：leaf-first を `#peel-leaves`、tree-edge-contribution を `#edge-pairs` に直した。auxiliary-tree・steiner-tree は stub のためページへのリンクのまま
- 指摘 8：図の凡例を「c = 部分木の中の」に揃え、「（根が指定頂点のとき）」の行を足した
- 採らなかったもの：なし
- 台帳への提案（検証役から）：abc368_d に `checked: 2026-10-21` を入れる
