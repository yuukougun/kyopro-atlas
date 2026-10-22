# b4 検証：rollback-union-find

- 対象：docs/ds/rollback-union-find.md、snippets/rollback-union-find/version-tree.{cpp,yaml}、docs/img/rollback-union-find/dfs-history.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px の PNG にして確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page rollback-union-find`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/rollback-union-find`：4 case 一致
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined`：警告なし。1 つ目の case をサニタイザつきで実行し、期待どおり `1 0 1 0`、異常なし（末尾の snapshot・rollback の assert も通る）
- `npx textlint`：エラー 0・警告 12（執筆者の報告と同じ。文の長さ・助詞の重なり・代替テキスト・参考の行）
- front matter：`git diff` で、変わったのは complexity・stage・updated だけ。summary と要点の「何ができるか」は同じ文。complexity と要点の計算量が一致
- 計算量：union by size だけで高さ $\le \log_2 N$、find 最悪 $O(\log N)$、undo は 2 件の書き戻しで $O(1)$、オフライン動的連結性は辺 1 本が $O(\log Q)$ ノード × 併合 $O(\log N)$ で $O(Q \log Q \log N)$。どれも正しい。Nyaan 氏のライブラリのページの計算量（unite・find・same が $O(\log n)$）とも合う
- 例題 abc302_h：`python3 tools/ap.py show abc302_h` → Ex. Ball Collector・diff 2407。台帳の役割は rollback-union-find が example、root-path-dfs が challenge で、本文の囲みと一致。drken 氏の記事（evidence）の題名は「AtCoder ABC 302 Ex - Ball Collector (橙色, 625 点)」で参考の題名と一致
- 「成分の種類数の最大は $\min(\text{頂点数}, \text{辺数})$」：Python で、頂点 1〜5・辺 1〜6（自己ループ・多重辺を含む）のランダムなグラフ 3000 通りについて、全辺の向きの全列挙と比べてすべて一致
- オフライン動的連結性の頂点加算の工夫（各頂点に Union-Find の木で下の合計を持たせ、併合で足し、取り消しで引き、加算は v から根までの経路に足す）：Python で、時間軸のセグメント木＋この工夫と、愚直な連結成分の和を、N≤6・Q≤20 のランダムなクエリ 3000 通りで比べ、すべて一致（ただし指摘 1 の扱いが要る）
- Library Checker の問題文（library-checker-problems の task.md）：persistent_unionfind は `t k u v`、$G_{-1}$ は辺なし、$-1 \le k_i < i$、$k_i = -1$ か $t_{k_i} = 0$。コード片の入力の読み方と一致。dynamic_graph_vertex_add_component_sum は `0 u v`（追加）・`1 u v`（削除）・`2 v x`（加算）・`3 v`（成分の和）で、本文の要約と一致
- 参考の URL：drken（題名一致）、ikatakos（「トヨタ自動車プログラミングコンテスト2023#2(AtCoder Beginner Contest 302) G,Ex問題メモ」、Ex の節あり）、cp-algorithms（題名一致）、OI Wiki「线段树与离线询问」（題名一致）、ei1333 の union-find-undo.hpp（undo・snapshot・rollback あり）、Nyaan「RollbackつきUnion Find」（題名一致、persistent_unionfind での検証あり）。atcoder.jp の URL は例題の囲みの問題リンクだけ
- root-path-dfs#no-path-compression との食い違い：記録 2 件・経路圧縮すると戻しても分かれない・union by size で $O(\log N)$ の 3 点とも一致（記号 $s, r, w$ も確認問題とそろっている）
- 図：木（1 の子が 2・3）と 4 時点のスタック（e1／e1+e2／e1 と点線の e2／e1+e3）が代替テキスト・本文と一致。幅 400 で 360px でも文字が読める。catalog の visual は static・priority 2 で、「DFS の行き（併合）と帰り（取り消し）で履歴のスタックが伸び縮みする様子」を満たす

## 指摘

### 1. 直すべき｜事実（F2）・分かりやすさ（U4）｜#what-it-does の「境界」と #offline-dynamic-connectivity の頂点加算の工夫

- **問題**：「境界」では、同じグループどうしの merge でも記録を 2 件積み「戻しても害はない」とし、呼び出し側は merge の結果を見ずに undo できると勧めている。一方、オフライン動的連結性の節では、取り消しを $\mathrm{sum}[a] \mathrel{-}= \mathrm{sum}[b]$ の引き算で行う。この 2 つを本文どおりに組むと、同じ成分どうしの merge（$a = b$）を取り消すときに $\mathrm{sum}[a] \mathrel{-}= \mathrm{sum}[a]$ となり、成分の合計が 0 に消える。「害はない」は par を書き戻す場合にだけ正しい
- **根拠**：検証の Python（時間軸のセグメント木＋本文の工夫）で、$a = b$ の記録の取り消しでも引き算をするようにすると、ランダムな 3000 通りのうち 192 通りで愚直な解と食い違った。$a = b$ のときは引き算をしないようにすると 3000 通りすべて一致した。オフライン動的連結性では閉路を作る辺（同じ成分どうしの併合）がふつうに現れる
- **直し方**：頂点加算の工夫の段落に「同じ成分どうしの併合（$a = b$）の記録を取り消すときは、合計を引かない」を 1 文足す。あわせて「境界」の「戻しても害はない」を「par を書き戻すだけなら害はない（引き算で戻す値は別。[オフライン動的連結性](#offline-dynamic-connectivity)）」のように限定する

### 2. 直すとよい｜分かりやすさ（U3）・事実（F2）｜#abc302_h の解法の詳細「成分ごとの値」

- **問題**：「閉路を一方向に回るように向け、残りの辺を閉路から遠ざかる向きに向ければ」は、閉路が 2 つ以上ある成分（$e > s$）では、残りの辺の中に「閉路から遠ざかる向き」が決まらないもの（別の閉路を作る辺）が出て、読者が迷う。結論の $\min(s, e)$ は正しい（検証の全列挙で一致）
- **根拠**：例えば 3 頂点に 4 本の辺がある成分では、閉路 1 つと全域木の辺のほかに 1 本余り、その向きは本文の説明から決まらない
- **直し方**：「閉路を 1 つ選んで一方向に回るように向け、閉路の外の頂点へは、その頂点を作った全域木の辺を閉路から遠ざかる向きに向ける。残った辺の向きは何でもよい」のように書く

### 3. 直すとよい｜事実（F9）・分かりやすさ（U4）｜#what-it-does の末尾「公開されているライブラリ（ei1333 氏・Nyaan 氏のもの）を使う」と参考の ei1333 の行

- **問題**：本文の snapshot は「今の併合の回数を返し、rollback(s) でその時点まで戻す」だが、ei1333 氏の `UnionFindUndo` の `snapshot()` は記録をすべて捨てて今を基準にし、`rollback()` は引数なしで記録が空になるまで戻す（最後の snapshot の時点へ戻る）。同じ名前で意味が違うので、本文の説明のつもりでライブラリを使うと取り違える
- **根拠**：https://ei1333.github.io/library/structure/union-find/union-find-undo.hpp のコード（`snapshot() { while (history.size()) history.pop(); }`、`rollback() { while (history.size()) undo(); }`）
- **直し方**：参考の ei1333 の行か本文に「snapshot は記録を捨てて今の時点を基準にし、rollback は引数なしでその時点まで戻す形」と添える

### 4. 直すとよい｜分かりやすさ（U7）｜#practice の Library Checker の 2 行

- **問題**：練習の要約が解き方を書いている（「版を頂点にした木を作り、DFS で入るとき併合・出るとき取り消す」「下の合計を持たせ、取り消しを引き算で行う工夫を足す」）。本文でも両方の解き方を折りたたみの外で書いている。Library Checker はデータ構造の検証用の問題なので許される余地はあるが、clarity の U7 の「要約に解き方が書いてある」に当たる
- **根拠**：clarity.md U7。他のページの Library Checker の行（two-sat・spanning-tree-advanced など）は問いだけを書いている
- **直し方**：練習の 2 行は問いだけにし、解き方への言及は「本文の [木の DFS と組む](#with-dfs) のコード片がそのまま使える」程度に留める。メインが「Library Checker の練習は本文の節を指してよい」と決めるならこのままでよい

### 5. 直すとよい｜分かりやすさ（U3・U8）｜#no-path-compression 第 2 段落「圧縮された頂点が古い根を直接指したまま残り」と確認問題 1

- **問題**：「古い根」が、取り消しで根に戻る $s$ のことか、併合先の $r$ のことか読み取りにくい（実際は併合先の $r$ を指したまま残る）。また確認問題 1 は、この段落の主張に具体例を足しただけで、ほぼ本文の写しになっている
- **根拠**：clarity.md U3（指すものの曖昧さ）・U8（本文の文をそのまま問う）
- **直し方**：本文を「圧縮された頂点が併合先の根を直接指したまま残り」とする。確認問題 1 は、たとえば「経路圧縮の書き換えもすべて記録すれば正しく戻せるのに、なぜ使わないのか」（記録が増える・ならしが崩れる）など、条件を変えて考えさせる問いにすると本文の写しにならない

### 6. 直すとよい｜図（G5）｜dfs-history.svg の左上の題

- **問題**：題の文字が「木（頂点 v で辺 e_v を併合）」と、アンダースコアの文字のまま出る。本文と代替テキスト以外では $e_v$ と書いているので、図だけ記法が違う
- **根拠**：360px・720px の PNG で目視
- **直し方**：`e<tspan baseline-shift="sub" font-size="9">v</tspan>` のように下付きにするか、「頂点 v に入るとき辺 e_v」の代わりに「頂点 v で辺 ev を併合（e1・e2・e3）」のように書く

## 未解決の点への意見

- offline-dynamic-connectivity との持ち主：頂点加算の工夫（下の合計・経路への加算・引き算での取り消し・指摘 1 の $a = b$ の扱い）は「取り消しと値の更新を両立させる Union-Find の作り方」なので、このページを持ち主にし、offline-dynamic-connectivity は手順の詳しい説明を持ってこちらへリンクするのが自然と考える。申し送りに指摘 1 の注意を入れてほしい
- front matter の `verify: [dynamic_graph_vertex_add_component_sum]`（catalog 由来で執筆者は変えていない）は、コード片が確かめているのは persistent_unionfind の形なので、メインの判断で `persistent_unionfind` を足すか入れ替えることを提案する
- 台帳の提案（abc302_h の evidence に ikatakos 氏の記事を足す）：ページの Ex の節があることを確かめた。足してよい。台帳の abc302_h の `checked` は 2026-10-21 のままでよい（問題の内容は今回の確認とも合う）

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 5）
