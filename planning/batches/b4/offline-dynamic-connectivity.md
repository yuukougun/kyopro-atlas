# offline-dynamic-connectivity（b4・発展の概要）の報告

- 書いたファイル：docs/graph/offline-dynamic-connectivity.md、snippets/offline-dynamic-connectivity/usage.{cpp,yaml}、docs/img/offline-dynamic-connectivity/time-segment-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 構成：要点 → 別名 → 導入 → time-segment-tree（区間の載せ方と、葉から根の経路で時刻の辺がちょうどそろう理由・図）→ dfs-rollback（DFS の擬似コード、後入れ先出しで取り消せる理由、経路圧縮をしない理由、計算量の根拠、コード片 2 つ、自作の要点、頂点の値の加算の扱い、オンライン強制では使えないこと）→ 使い分け → 例題 abc334_g → 練習（Library Checker のみ）→ 参考
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 21：区間の記法 `[l, r)` の括弧の対応・数式やリンクを含む文の長さ・折りたたみの中の文・要点の囲みの summary 由来の文の助詞の重なりなど、誤検出か summary に合わせたもの）
- コード片の確かめ：check_snippets の 5 ケースに加え、一時置き場で素朴な再計算と 300 件の乱数比較をして一致した（頂点数 1〜6、クエリ 0〜15）
- 図：render_svg で 360px・720px の PNG にして目で確かめた
- 使った出典：kmjp（例題の解法。マスが緑である区間を載せる形）、amentorimaru（例題の関節点による別解。新しいドメイン amentorimaru.hatenablog.com を check_noai で確かめ、noai・noimageai の指定なし）、cp-algorithms「Deleting from a data structure in O(T(n) log n)」（一般の枠組みと動的連結性の実装があることの確認。文章と図は使っていない）、Library Checker の問題文は GitHub の library-checker-problems の graph/dynamic_graph_vertex_add_component_sum/task.md で確かめた（judge.yosupo.jp のページは JS で描かれ、本文を取れなかった）

## 台帳への提案

- なし（abc334_g の summary・evidence はそのままで本文と合う）

## 用語集への提案

- 時間軸のセグメント木｜time-segment-tree｜時刻を葉とするセグメント木で、各要素が存在する時刻の区間をそれを覆う O(log Q) 個のノードに載せたもの。葉から根までのノードに載った要素が、その時刻に存在する要素とちょうど一致する。（本文では用語集にリンクしていない。足すなら本ページの #time-segment-tree を指してもよい）

## front matter・catalog への提案

- verify に `dynamic_graph_vertex_add_component_sum` を足す（rollback-union-find は既に持つ。本ページは練習の Library Checker に同じ問題を置いた）

## 手引きへの提案

- 頂点や要素が「ない」時刻が 1 点だけのとき（例題の型）、辺を両端の欠ける時刻で 3 区間に分ければ、辺だけを載せる汎用のコード片がそのまま使える。概要のページでも、汎用のコード片 1 つと、問題ごとの載せ方の言い換えで済ませる形がよかった

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 探していない。発展の概要の例題の目安（0〜2）を abc334_g の 1 問で満たしている。練習は Library Checker の 1 問だけ

## 未解決の点

- rollback-union-find#offline-dynamic-connectivity は、頂点の値の加算を「葉で v から根までの経路のすべての sum に足す」形で書き、「根だけに足すと取り消しで x が元の根に残る」としている。本ページは別の方法として「加算を時刻 [t, Q) に存在する操作としてセグ木に載せ、入るときに根の合計に足し、出るときに引く」と書いた（後入れ先出しで取り消すので正しい。本ページからはあちらの節へリンクした）。あちらの「根だけに足すと」の記述は、葉で取り消さずに足す場合の話であり、本ページの方法と矛盾しないが、読者が食い違いと受け取らないか検証役に見てほしい
- 例題の制約（H・W の上限）と答えの法は問題ページを開けないので書いていない。全体の計算量はマスの数 G で O(G log^2 G) とだけ書いた
- lowlink.md の例題への言及（「関節点で切り離される部分木を数えても解ける」）と本ページの別解の記述はそろっている

## 検証の指摘への対応

- 指摘 1〜4 はすべて直した（参考の題名と著者を h1・ブログの表示名に、加算の段落に根の合計の持ち方・取り消しの順・rollback-union-find の節との関係を追記、図の葉 1 を「1 に e」（font-size 11）に、マスを載せる書き方が軽いことを追記）。採らなかったものはない
- 提案：lowlink.md の参考のあめんばーど氏の記事の題名は「G - Christmas Color Grid 2 / …」で、h1 の「【AtCoder】」が抜けている。本ページは h1 どおりにしたので、統一するならメインで lowlink.md 側をそろえてほしい
