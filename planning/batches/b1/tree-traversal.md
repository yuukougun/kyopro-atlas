# tree-traversal（根付き木と走査順）の報告

- 書いたファイル：docs/tree/tree-traversal.md、snippets/tree-traversal/{dfs-order,bfs-order,parent-index}.{cpp,yaml}、docs/img/tree-traversal/orders.svg
- front matter で変えたもの：complexity（`O(N)（DFS・BFS・番号順のどれでも、各頂点と各辺を定数回ずつ見る）`）・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 0）
- 使った出典（どれも付録 B のドメイン。新しく noai を確かめたドメインはない）
  - drken ABC213 D（例題の方針）、gotoki_no_joe ABC270（練習の方針）、drken ABC333 D、ZOI_dayo ABC309、drken ABC146 D、kmjp ABC133 E（各問題の方針）

## 台帳への提案

- なし。使った 6 問（abc213_d・abc270_c・abc333_d・abc309_e・abc146_d・abc133_e）は確認済みで、summary は evidence の解説で問いを確かめた内容と合っていた
- 補足：abc270_c の evidence（gotoki_no_joe）は Haskell の解説で、グラフが木であることや制約は書いていない。問いと方針（親を記録してたどる）の裏付けには足りるが、木であることを明記した解説（例：drken・ikatakos の ABC270 の記事）を evidence に足すとよい（未確認なので URL は書かない）

## 用語集への提案

- なし（用語集へのリンクは使っていない）
- 候補として検討した語：「行きがけ番号」｜`preorder-index`｜DFS で頂点に入った順に 0 から振った番号 $\mathrm{in}[v]$。$v$ の部分木は区間 $[\mathrm{in}[v], \mathrm{in}[v] + \mathrm{sz}[v])$ に並ぶ。euler-tour の $\mathrm{in}[v]$ と同じ意味なので、用語集に足すかはメインに任せる

## 手引きへの提案

- §8 の SVG：代替テキストに木の形とすべての順を書くと textlint の文の長さ（120 字）を超えやすい。「代替テキストは要点だけにし、細部は直後の表や本文に書く」と一言あるとよい（今回は親の一覧を図の直後の表に回した）

## 他のページへの提案（メインの判断用）

- cpp-environment#stack-depth の節の題名は「-O2 でも深さ 2×10^5 で落ちうる」としている。手元（ulimit -s 8192、g++-15 -std=gnu++23 -O2）で、snippets/tree-traversal/dfs-order.cpp の再帰ラムダの DFS は、パス状の木の **N = 10^5** でも Segmentation fault になった（N = 2×10^5・10^6 も同じ。g++ 11 の -O0・-O2 でも 2×10^5 で落ちた）。BFS 順の版（bfs-order.cpp）は N = 10^6 でも通った。執筆時の参考に
- catalog の visual（dynamic・priority 2）は作っていない。静的な SVG（orders.svg：木と、行きがけ順・帰りがけ順・BFS 順の 3 行、頂点 2 の部分木の区間を強調）で代えた。動く図を作るなら次の仕様を提案する
  - `<div class="kp-viz" data-viz="tree-traversal" data-config='{"n":7,"edges":[[1,2],[1,3],[2,4],[2,5],[3,6],[5,7]],"root":1}'></div>`
  - ステップごとに、DFS のスタック（再帰の途中の頂点）・行きがけ順の列・帰りがけ順の列・各頂点の sz を表示する。BFS 順に切り替えると、キュー（配列 order と読み位置 i）と深さを表示し、最後に逆から読んで sz を集める様子を見せる
  - 置き場所は「行きがけ順と帰りがけ順（子から親へ集約する）」の 3 つの性質の直後

## 問題の補充の候補

- なし（例題 1・練習 4・力試し 1 で目安を満たしている）

## 未解決の点

- AtCoder のスタックの上限の具体的な値は書いていない（「大きく、再帰のままで通ることが多い」とだけ書いた。dfs のページと同じ書き方。値は cpp-environment の担当で確かめる）
- cpp-environment は stub なので、#stack-depth ではなくページへリンクした（§7 の規則どおり）。draft になったら節へのリンクに直してよい
- 図の代替テキストは親の一覧を「表のとおり」として直後の表に任せている

## 使用量の目安

- 道具の呼び出し 約 35 回、Web 取得 6 回（WebFetch）＋題名の確認 6 件（curl）

## 検証の指摘への対応（verify/tree-traversal.md）

- 指摘 1（直すべき）：`#to-tree-dp` の文を「子から集めるときは帰りがけ順か BFS 順の逆、親から配るときは行きがけ順か BFS 順」に直した
- 指摘 2（直すべき）：参考の gotoki_no_joe の「参考にした点」を記事の中身（問いと、親を引数で渡して戻らない DFS でパスを探す別の解き方）に合わせた。本文の方針（親を記録して Y からたどる）の裏付けになる解説は未確認なので、URL は足していない
- 指摘 3：落とし穴「深さの基準を取り違える」を、差は基準によらないこと・深さの値そのものを使うとずれること・「y 世代先まで」は差が y 以下で端を含むことに書き換えた
- 指摘 4：採ったが形を変えた。式の形 $[1, 5)$ を本文に書くと textlint の no-unmatched-pair が警告を出したので、「$\mathrm{in} = 1$・$\mathrm{sz} = 4$ なので、行きがけ番号が 1 以上 5 未満（番号 1〜4 の 4 個）」と半開区間の意味を言葉で書いた
- 指摘 5：ABC309 E の方針に、保険がなければ自分の分を −1、根は親の分を −1 とすることを足した
- 指摘 6：dfs-order.cpp の検査を、各頂点の区間が親の区間の内側にあることを 1 段ずつ確かめる形（$O(N)$）に変えた。check_snippets は通る
- 指摘 7：取り込みの直後の段落の頭に「`in`・`pre`・`post` は次の節で扱う行きがけ番号・行きがけ順・帰りがけ順の記録である」と足した
- 採らなかった指摘：なし

### 台帳への提案（検証を受けて）

- abc213_d・abc333_d・abc309_e・abc146_d・abc133_e に `checked: 2026-10-21` を入れる（検証役が evidence で問いと方針を確かめた）
- abc270_c は、親を記録してたどる方針と木であることを書いた解説を確かめて evidence に足してから `checked` を入れる。それまで参考の記事は「問いと別の解き方」としてだけ挙げている
