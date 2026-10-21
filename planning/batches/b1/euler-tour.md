# euler-tour の報告（工程8b・バッチ b1）

- 書いたファイル：docs/tree/euler-tour.md、snippets/euler-tour/（subtree-sum・depth-count・root-path の 3 組の .cpp と .yaml）、docs/img/euler-tour/subtree-interval.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（7 節すべてを見出しにした）。level は front matter の「青」のままにした（指示文の「水」とは食い違う。未解決の点を参照）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 3 組で期待と違う 0。textlint エラー 0、警告 11（要点の囲みの数式を含む文の長さ、`[\mathrm{in}[v], \mathrm{out}[v])` の半開区間の括弧を no-unmatched-pair が数える誤検出、確認問題の折りたたみの題名の行に数える文の長さ、台帳の summary をそのまま使った abc240_e の行の長さ）
- 使った出典：merom686 の ABC406、qiita.com の bfs 氏の ABC406 まとめ・2yuu 氏の ABC202 E、hamayan の ABC202 E、kmjp の ABC294 G・ABC337 G、Kazun の ABC240 E、ACL の document_ja（fenwicktree）。新しいドメインはない（すべて付録 B）。本文の末尾で judge.yosupo.jp の vertex_add_subtree_sum へリンクした（ページは開いていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc406_f | summary | 最初はどの頂点の重みも 1 の木で、頂点の重みへの加算と、指定した辺で木を 2 つに分けたときの両側の重みの和の差の絶対値の質問に答える。 | https://qiita.com/bfs/items/8d3f7bf6c8e90b073086 ・ https://merom686.hatenablog.com/entry/2025/05/18/151742 |
| abc337_g | summary | 頂点 1〜N の木の各頂点 u について、u と v を結ぶパス上に w があり w > v となる組 (v, w) の数を求める。 | https://kmjp.hatenablog.jp/entry/2024/01/20/1000 |
| abc202_e | evidence | https://qiita.com/2yuu/items/898b95864905dcbc8e7d を足す（台帳の approach「深さごとの列と二分探索」の裏付け。いまの evidence の hamayan 氏の記事は深さの順の平面走査と BIT の別解で、二分探索は書いていない） | https://qiita.com/2yuu/items/898b95864905dcbc8e7d |
| abc406_f | evidence | https://qiita.com/bfs/items/8d3f7bf6c8e90b073086 を足す（merom686 氏の記事には操作の中身が書かれていない） | 同左 |
| abc239_e・abc240_e・abc294_g・abc202_e | summary | 末尾に「。」を足す（ほかの問題と表記をそろえる。本文の行は「。」付きで書いた） | — |
| abc239_e | evidence | `https://kazun-kyopro.hatenablog.com/entry/ABC/NNN/X` は雛形の URL が残っているので外す | — |

- 例題の並び：abc406_f（1470）→ abc202_e（1638）→ abc294_g（1702）の易しい順にした。役割は catalog のとおり（abc202_e が representative）

## 用語集への提案

- なし。半開区間 `half-open-interval`・オフライン `offline` の既存の anchor にリンクした（`offline` は用語集の本文にまだ見出しがない。ほかのページもリンクしているので、未作成なら足してほしい：オフライン｜offline｜クエリを先にすべて読み、答える順を並べ替えてから処理すること）

## 手引きへの提案

- §6 の木の記法に $\mathrm{ord}[t]$（位置 $t$ にいる頂点。$\mathrm{ord}[\mathrm{in}[v]] = v$）を足すとよい。HL 分解やオイラーツアーの列から頂点へ戻すときに使う
- §6 に「$\mathrm{out}[v]$ は次に振る番号（部分木は半開区間 $[\mathrm{in}[v], \mathrm{out}[v])$）」と流儀を明記するとよい。閉区間の流儀と混ざるのが典型のバグで、HL 分解のページは $[\mathrm{in}[v], \mathrm{in}[v] + \mathrm{sz}[v])$ と書いている（どちらも同じ区間）

## 動く図の仕様（priority 1。JS は未作成）

- 置き場：`<div class="kp-viz" data-viz="euler-tour" data-config='{"n": 7, "parents": [-1, 6, 0, 2, 5, 0, 2], "select": [2, 5, 6, 0]}'></div>`（in-out の節。静的な図 subtree-interval.svg と同じ木）
- 上に根付き木（子は番号の小さい順に回る）、下に行きがけ順の列（各マスに頂点番号、下に位置）を並べる
- 状態の列：最初の数ステップで DFS の進行（入るたびに in を振り、出るときに out を記録）を見せ、続けて select の各頂点について、その部分木の頂点と列の区間 [in, out) を同時に強調する。caption 例：「頂点 2 の部分木は区間 [1, 5)。番号 1〜4 は頂点 2 に入ってから出るまでに振られた」
- 色だけで区別しない（強調は太線と塗り。区間の上に括弧と [in, out) の文字）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc187_e（diff 1358、台帳では tree-imos の例題）：辺の片側の頂点すべてに加算するクエリの後の各頂点の値。euler-tour の練習に足すと、補集合の 2 区間への加算を BIT で行う解き方と、いもす法でよい場面の対比になる。裏付け：https://qiita.com/recuraki/items/dd85ed26718c851582b6 （題名に「オイラーツアー+区間和のアプローチ」。本文は読んでいない。検証時に確かめてほしい）
- abc319 以降で青の帯（1600〜1999）の例題は見つけられなかった（catalog の level_evidence の open_issues のとおり）。検索を 1 回しただけなので、続けて探す余地はある

## 未解決の点

- **level の食い違い**：指示文は「レベル 水」だが、骨格の front matter と catalog は「青」（level_evidence：abc202_e 1638・abc294_g 1702）。front matter が正という規則に従い青のままにした。節の書き方は青のページとして書いた
- abc406_f と abc202_e・abc294_g の制約（N, Q の上限）は第三者の解説に書かれておらず、本文では制約の数値を書かなかった（計算量の式だけ）
- abc337_g の方針は kmjp 氏の記事の要約（隣接する各方向の小さいラベルの数を部分木または補集合へ加算）を自分の言葉で組み立て直した。kmjp 氏は「ラベルの大きい順に処理」と書いているように読めたが、本文はラベルの小さい順に BIT へ足す形で書いた（どちらでも数えられる）。検証で確かめてほしい
- 図 subtree-interval.svg は手元に SVG の描画の道具がなく、表示を目で確かめていない（座標を計算で決めただけ）
- 節へのリンク：mo-algorithm（stub）の mo-on-tree 節、lca（stub）の comparison 節、tree-traversal（stub）の recursion-depth 節へはページへのリンクだけにした。draft になったら節へのリンクに直すとよい
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 8 回、Web 検索 3 回

## 検証の指摘への対応（2026-10-21）

- 1（直すべき・木上の Mo）：区間の取り方（祖先なら閉区間 $[\mathrm{ST}(u), \mathrm{ST}(v)]$、そうでなければ $[\mathrm{EN}(u), \mathrm{ST}(v)]$）を書き、「ちょうど 1 回」から LCA を外した。続く段落は「打ち消す実装は Mo のページ」に縮めた
- 2（直すべき・ABC337 G）：0-indexed に統一し「$w$ − $w$ の部分木の中の個数」に直した。囲みの summary（台帳の文）は「頂点 1〜N」のままだが、大小の比較は読み替えで変わらない
- 3：一般論（重みの上限 × $(N - 1)$ を見積もり、`int` を超えるなら `long long`）にした。abc294_g の重みの上限は確かめられていない
- 4：動く図の説明を仕様（DFS の進行のあと頂点 2・5・6・0 を順に強調）に合わせた
- 5：root-path.cpp の取り込みの中、`dist` の直前に lca のコメントを足した
- 6：LCA を (c) の列の最小で求める段落を #meanings の (c) の説明へ移した
- 7：`lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);` と計算量を書いた
- 8：入力は親の配列のままにし、subtree-sum.cpp の DFS の直前に「子だけの隣接リストなので親を渡さない（無向なら int p を足す）」のコメントを足した。depth-count・root-path は同じ形なので、最初に出る 1 か所だけにした
- 9：in/out のラベルと位置の数字を 16px にし、viewBox を 490 幅（x 60〜550）に詰めた。頂点 0 のラベルは辺との隙間を取るため 9px 上げた。目での確かめはまだ（描画の道具がない）

## 台帳への提案（検証を受けて追加）

- abc406_f・abc202_e・abc294_g・abc240_e・abc337_g に `checked: 2026-10-21`（検証役が evidence で確かめた）
