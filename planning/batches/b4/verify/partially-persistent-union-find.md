# partially-persistent-union-find の検証（b4）

対象：docs/ds/partially-persistent-union-find.md、snippets/partially-persistent-union-find/（usage.cpp・usage.yaml）、docs/img/partially-persistent-union-find/find-at-time.svg。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page partially-persistent-union-find`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/partially-persistent-union-find`：コンパイル 1 回・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- usage.cpp を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイル：警告なし。yaml の 1 件目と 3 件目を流して期待どおり（self_check の 300 回の assert も通る）。サニタイザの異常なし
- yaml の cases を手で確かめた：図の例（1-2・3-4・1-3・4-5）で、初めて同じになる時刻は (1,2)=1、(2,4)=3、(1,5)=4、(3,3)=0、時刻 2 の大きさはどれも 2。2 件目（1-2・2-1・2-3）の (1,3)=3、size(1,1)=2、size(3,1)=1。正しい
- 作業用の場所で総当たりと照らした（リポジトリには置かない）：$N \le 60$・併合 $\le 120$ 回の乱択 2000 件で、`first_same`（二分探索）と `first_same_climb`（登る方法）の両方が、併合を順に再現した素朴な「初めて同じ集合になった操作の番号」と全組で一致。あわせて今の森の深さが常に $\lfloor \log_2 N \rfloor$ 以下（観測した最大は 4）。サニタイザの異常なし
- `npx textlint`：エラー 0・警告 2（33 行付近の要点の文の長さ、105 行の骨格の見出しの二重かっこ。どちらも front matter 由来で、手引き §13-8 の範囲）
- front matter：git diff で、執筆者が変えたのは complexity・stage・updated だけ。要点の計算量と complexity は一致。別名の行に aliases がすべてあり、最初の `##` より前にある。要点の「何ができるか」は summary と同じ
- 主張の確認：
    - 根へ向かう道で tm が真に増えること（つないだ時刻には親は根なので、親が根でなくなるのはそれより後）、時刻 $t$ の森が今の森から $t$ より後の辺を切ったものになること、find の条件 `tm[x] <= t` と「併合の前に時刻を 1 進める」約束の対応：正しい
    - 経路圧縮で壊れる例：圧縮後 par[4]=1・tm[4]=2 のままなので、find(4, 2) は 1 で止まる。本文どおり
    - union by size だけで深さ $\log_2 N$ 以下、最悪 $O(\log N)$（ならしでない）：noshi91 の記事（union by size のみで $O(\log N)$）・前提の union-find#complexity と一致。上の乱択でも確かめた
    - size(x, t) の `upper_bound(make_pair(t, INF))` の 1 つ前：履歴は時刻の昇順で、初めに (0, 1) があるので prev は常に有効
    - 登る方法の正しさ（未解決の点 2）：2 本の道の合流点 $w$ までの辺の時刻の最大が答え、という本文の論法は正しい（$w$ より下の辺が 1 本でも欠ければ、その側の根は $w$ より下で、もう一方の根と違う）。tm の小さい側を登ると、$w$ に先に着いた側は tm[w] が下の側より大きいので待つことになり、必ず $w$ で出会う。上の乱択でも一致
    - 完全永続を永続配列で 1 回 $O(\log^2 N)$：noshi91 の記事と一致
    - 並列二分探索の $O((N + M + Q) \log M)$ 回の操作：各段で初期化 $N$・併合 $M$・判定 $Q$ を $\log M$ 段。正しい
    - Stamp Rally の判定の単調性（別の成分の大きさの和は、合わさる瞬間に合わさった成分の大きさに等しく、その後は増えるだけ）：正しい
- ACL：`acl: []` で、本文の「ACL には部分永続 Union-Find はない」は document_ja の一覧（dsu のみ）と一致
- Library Checker の Persistent UnionFind：`gh api` で library-checker-problems の data_structure/persistent_unionfind/task.md を読んだ。クエリ 0 は $G_{k_i}$ に辺を足した版を $G_i$ とする、クエリ 1 は $G_{k_i}$ での連結判定で、過去の版から枝分かれする完全永続の問題である。本文の「このデータ構造では解けない」「版の木の DFS と取り消しで解ける」は正しい
- 問題の内容：
    - code_thanks_festival_2017_h：drken の記事（台帳の evidence）で、$N$ 個の集合に $M$ 回の併合、$Q$ 個のクエリで 2 要素が何回目の操作の後に初めて同じグループになるか、最後まで別なら −1、$2 \le N \le 10^5$・$0 \le M, 1 \le Q \le 10^5$ を確かめた。記事の解法も根でなくなった時刻・大きさの履歴・十分大きい時刻で別なら −1・時刻の二分探索で、本文の方針と一致。$N \ge 2$ だが同じ 2 要素のクエリが来ても `first_same` は 0 を返して落ちない。方針の計算量は制約に合う。ap.py で diff なし（本文の「diff —」と一致）
    - agc002_d：drken の記事で、番号 $i$ 以下の辺だけを使い、x と y から合わせて z 頂点を訪れる最小の $i$ を問うこと、解法に部分永続 Union-Find（時刻の二分探索・時刻での大きさ）と並列二分探索の 2 つがあることを確かめた。本文の方針と一致。ap.py で diff 2514
- 図：`python3 tools/render_svg.py` で 360px・720px の PNG にして目で確かめた。辺の時刻（2-1:1、4-3:2、3-1:3、5-1:4）は本文の併合の順と union by size（同じ大きさなら先の側が根）と一致し、find(4, 2) で登る辺（赤の太線）、時刻 3 以上の辺（破線）、「時刻 2 の根は 3（大きさ 2）」も本文・代替テキストと一致。viewBox 400×260 と width・height が同じ比、白背景、sans-serif のテキスト、色と線の種類（太線・実線・破線）の併用でよい。360px でも文字は約 0.9 倍で読める。catalog の visual（priority 2・static「各辺につながった時刻を書いた木で、時刻 t の find が t 以下の辺だけを登る様子」）を満たす
- 参考の URL：drken の 2 記事・noshi91 の記事は check_noai.py で noai の指定なし。題名・内容は参考の行の説明どおり。本文の例（5 頂点の森）・言い回しは記事と別で、F8 の問題はない

### 執筆者の未解決の点について

- 例題の出力（最後まで別のとき）：drken の記事で −1 と確かめた。本文で「問題の指定」とだけ書くのは問題文の転載を避ける書き方としてよい。コード片の `first_same` も −1 を返すので、そのまま使える
- 登る方法の正しさ：上のとおり、論法の確認と $N \le 60$ の乱択 2000 件で正しいと確かめた。第三者の資料は要らない
- rollback-union-find・merge-process-tree・parallel-binary-search へのリンク：3 つとも今は draft（b4 で執筆中）。ページへのリンクのまま残し、メインの張り替え（commit 64f6f66 と同じ作業）に任せてよい（指摘 4）

## 指摘

1. **直すとよい**｜U8・F2｜#quiz の 2 つ目の答え「初めて同じ集合になる時刻を二分探索すると、答えが 1 大きくなる」｜条件を `tm[x] < t` にすると same(x, y, t) は「時刻 $t - 1$ の状態」を返すので、普通は 1 大きくなるが、例外が 2 つある。$x = y$ なら時刻 0 で真のまま 0 を返す。最後の併合（時刻 now）で初めて同じになった組は、`first_same` の最初の確かめ `same(x, y, now)` が偽になり −1 を返す（「最後まで同じにならない」と誤る）。「答えが 1 大きくなる」と言い切ると、読者はずれ方を一様と思い込む｜`find` の条件を `<` に替えると、same(x, y, t) は「最初の $t - 1$ 回の後」と同じになる（$t \ge 1$）。usage.cpp の first_same の先頭の判定は時刻 now で行う｜答えを「多くの組で答えが 1 大きくなり、最後の併合で初めてつながった組は『最後まで別』と誤る」のように、ずれ方を 2 つに分けて書く（$x = y$ の場合には触れなくてよい）

2. **直すとよい**｜U6｜#no-path-compression の 1 段落目（「図の例で今の時刻の find(4) を経路圧縮すると」）と #quiz の 1 つ目の答え（「図の森で」）｜図と例は #what-it-does にあり、節を 1 つだけ取り出して読むと、「4 の親が 1 に変わる」「時刻 3 にならないとつながらない 1」の意味が分からない（4 が時刻 2 に 3 の下へ、3 が時刻 3 に 1 の下へつながったことが節の中にない）｜clarity.md U6｜「#what-it-does の図の例（4 は時刻 2 に 3 の下へ、3 は時刻 3 に 1 の下へつながっている）で」のように、例の要点を括弧で一言補う。#binary-search-time で使う $\mathrm{tm}$ にも、初出で「（$v$ が根でなくなった時刻）」と一言添えるとよい

3. **直すとよい**｜U3｜#binary-search-time の 2 段落目「ng を $-1$ にする」｜$-1$ にする理由が書かれておらず、読者は「時刻 0 は何もしていない状態なのだから ng = 0 でよいのでは」と迷う。$x = y$ のときは時刻 0 が答えになるので、0 を ng にはできない｜usage.cpp の 3 件目・4 件目の cases（`3 3`・`1 1` で答え 0）｜「時刻 0 でも $x = y$ なら同じ集合なので、ng は判定しない番兵の $-1$ にする」と理由を 1 文足す

4. **直すとよい**｜F7（リンク）｜#alternatives の並列二分探索・併合過程の木・Undo 可能 Union-Find のリンク、本文冒頭の related に当たるリンク｜3 つのページは今は draft になっている（docs/ds/parallel-binary-search.md・docs/tree/merge-process-tree.md・docs/ds/rollback-union-find.md の stage）。節へのリンクにできる｜各ページの front matter の stage｜メインがバッチの終わりに節へのリンクへ張り替える（執筆者が直す必要はない）

5. **直すとよい**｜G5｜find-at-time.svg の凡例「時刻 2 以下の辺」｜時刻 2 の辺（4-3）は赤の太線で描かれているので、実線の灰色は 2-1 の 1 本だけになる。凡例の「時刻 2 以下の辺」と見比べると、4-3 が実線でないことに一瞬迷う｜render_svg.py の 360px・720px の PNG｜凡例を「時刻 2 以下の辺（登らないもの）」とするか、赤の凡例を「find(4, 2) で登る辺（時刻 2 以下）」にして、赤も時刻 2 以下であることを示す

## 総合の判定

そのまま（直すべき 0 件）。計算量・tm が道の上で真に増える性質・経路圧縮で壊れる例・登る方法の正しさ・例題と練習の方針は、資料と総当たりで正しいことを確かめた。直すとよい 5 件は、確認問題の言い切り・断片で読んだときの補い・番兵の理由・リンクの張り替え・凡例の言葉で、どれも小さい。

## 台帳への提案（検証役から）

- code_thanks_festival_2017_h の checked に 2026-10-22 を入れる（drken の記事で問い・−1 の出力・制約・解法を確認）。2 つ目の evidence は、執筆者と同じく今回も見つけていない
- agc002_d の checked に 2026-10-22 を入れる（drken の記事で問いと部分永続 Union-Find・並列二分探索の 2 つの解法を確認）
