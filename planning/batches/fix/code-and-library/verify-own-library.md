# verify-own-library：own-library の直しの検証（工程11 グループ code-and-library・Issue #53・#64）

作業ツリー：`kyopro-atlas-wt/code-and-library`（ブランチ feat/code-and-library、HEAD da9b5c2、commit 前の差分）。日付：2026-10-29。対象は own-library の担当が直したファイル（overrides/main.html・kp.css、docs の ds 10 ページと guide/library-design、snippets の 14 ファイル）と報告 own-library.md。同じ作業ツリーのほかの担当（code-links・graph-code）の変更は対象にしていない。ファイルは直していない（この報告だけを書いた）。atcoder.jp・codeforces.com は開いていない。

## まとめ

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #53 | 直しが要る | 2（dynamic-dp で Library Checker の節と末尾の行が重なる。library-design の「末尾の自作の確認にも出る」が発展の概要に当てはまらない） |
| #64 | 直しが要る | 4（BIT の `(n)` のコンストラクタがない違いが書かれていない。`min_left<f>(r)` の形がない違いが抜けている。再帰の `max_right` を「SegTree に足す」と書いている。提案 1 の文面と開いて置く 5 ページが合わない） |

完了の条件の大筋は満たしている。verify を持つ 84 ページすべてで、表示された HTML に verify の各問題へのリンクがある（スクリプトで数えた）。自作の節を持つ 10 ページから library-design の #interface・#verify へリンクがある。足したコード片は check_snippets（28 片・期待と違う 0）とサニタイザを通り、ACL v1.6 と乱数で突き合わせて一致した。直しが要るのは、ACL との違いの書き漏れ 2 つと、文の誤り・食い違い 4 つである。どれも文かコード片の数行で直せる。

## 直しが要る点

### 1. #64 自作の BIT に ACL の `fenwick_tree(n)` に当たるコンストラクタがないことが書かれていない

- ファイル：`docs/ds/fenwick-tree.md` 119 行目（自作するときの囲みの最初の段落）、`docs/guide/library-design.md` 90 行目（#acl-names の BIT の行）、`snippets/fenwick-tree/own-bit.cpp` 11 行目
- 理由：ACL v1.6 の `fenwick_tree` の公開されたコンストラクタは `fenwick_tree<T> fw(int n)`（全要素 0）だけである（document_ja/fenwicktree.md、fenwicktree.hpp）。自作の `BIT` は `explicit BIT(const vector<long long>& a)` しか持たない。囲みは「`add(p, x)`・`sum(l, r)` の名前と意味は ACL と同じ」「ACL にないものは 3 つある（配列から線形時間で作るコンストラクタ…）」と書き、表は「配列からの $O(N)$ の構築…を足した」と書く。これでは ACL の上に足したように読める。実際には ACL の `(n)` の形がなく、ACL と同じ書き方の `BIT fw(n);` は「no matching function for call to 'BIT::BIT(int&)'」でコンパイルできない（g++-15 で確かめた）。Issue の完了の条件「ACL と違う名前・返り値のすべてに違いが書かれている」に足りない
- 直し方の案：(a) コード片に `explicit BIT(int n) : n(n), t(n + 1, 0) {}  // 全要素 0（ACL の fenwick_tree(n) と同じ）` を足し、囲みを「コンストラクタは ACL と同じ `BIT(n)`（全要素 0）に、初期値の配列から線形時間で作るものを足した」とする。セグメント木で `SegTree()`・`SegTree(int n)` をそろえたのと同じ扱いになる。または (b) 囲みと表に「ACL の `fenwick_tree(n)` に当たるコンストラクタはなく、全要素 0 なら `BIT bit(vector<long long>(n))` で作る」と書く

### 2. #64 自作のセグメント木に `min_left<f>(r)` の形もないことが抜けている（表の「ほかは同じ」が誤り）

- ファイル：`docs/ds/segment-tree.md` 163 行目、`docs/guide/library-design.md` 92 行目
- 理由：ACL v1.6 の `segtree` には `max_right<f>(l)` と `min_left<f>(r)` の両方がある（segtree.hpp、document_ja/segtree.md の min_left の (1)）。自作の `SegTree` はどちらも持たないが、囲みは `max_right<f>(l)` だけを挙げ、表は「`max_right<f>(l)` の形がない。ほかは同じ」と書く。`seg.min_left<f>(r)` は自作ではコンパイルできない（g++-15 で確かめた）
- 直し方の案：囲みを「ACL にある `max_right<f>(l)`・`min_left<f>(r)` の形（判定の関数をテンプレートの引数で渡す書き方）はない」に、表を「`max_right<f>(l)`・`min_left<f>(r)` の形がない。ほかは同じ」にする

### 3. #64 再帰の `max_right` を「SegTree に足すメンバ関数」と書いているが、SegTree にはもう `max_right` がある

- ファイル：`docs/ds/segment-tree-binary-search.md` 128 行目（自作するときの囲みの最初の段落）
- 理由：今回の直しで、セグメント木のページの `SegTree` に非再帰の `max_right(l, f)` が入った。囲みは「`SegTree` に足すメンバ関数として書いた」と書き、続けて非再帰の `max_right` が `SegTree` に入っていることも書く。書いてあるとおりに足すと、同じ形のメンバ関数が 2 つになり「cannot be overloaded」でコンパイルできない（segment-tree/own.cpp の core に own-max-right.cpp の core を足して、g++-15 で確かめた）
- 直し方の案：「[セグメント木の自作](…)の `SegTree` の `max_right` を、再帰で書いた版である。名前が同じなので、使うときは非再帰の `max_right` と置き換える。」のように、足すのではなく置き換えると書く

### 4. #53 発展の概要 dynamic-dp で、Library Checker の節と末尾の「自作の確認」の行が重なる

- ファイル：`docs/dp/dynamic-dp.md` 147 行目（`## ライブラリでの検証 {#library}` の箇条書き）
- 理由：テンプレートは、発展の概要では本文に `judge.yosupo.jp/problem/<名前>"` のリンクがある問題を末尾の行に出さない。dynamic-dp の #library は verify の `point_set_range_composite` を「**Point Set Range Composite**（`point_set_range_composite`）」と名前だけで書いていて、リンクがない（参考の行は GitHub の library-checker-problems へのリンク）。そのため末尾に「自作の確認：Library Checker の point_set_range_composite（確かめ方）」が出て、同じ問題が #library と末尾の 2 か所に並ぶ（幅 390px で撮って確かめた）。発展の概要 31 ページのうち、重なるのはこの 1 ページだけである。Issue の「名前だけの問題名を judge.yosupo.jp へのリンクにする」がまだ当たっていない箇所でもある
- 直し方の案：147 行目の名前を `[Point Set Range Composite](https://judge.yosupo.jp/problem/point_set_range_composite)` のリンクにし、`updated` を 2026-10-29 にする。これで末尾の行は出なくなる（リンクは本文に残る）。148 行目の `point_set_tree_path_composite_sum_fixed_root` も同じ形にそろえてよい。あわせて提案 2 に「発展の概要の #library の問題名は judge.yosupo.jp へのリンクにする（テンプレートはリンクを見て重複を省く）」を足す

### 5. #53 library-design の「各ページの末尾の自作の確認にも出る」が、発展の概要に当てはまらない

- ファイル：`docs/guide/library-design.md` 83 行目（#acl-names の表の前の段落）と 173 行目（#verify の手順 1）
- 理由：テンプレートは発展の概要では本文にリンクのある問題を出さないので、verify を持つ発展の概要 31 ページのうち 30 ページには「自作の確認」の行がない。83 行目の直後の表の「ロールバックできる Union-Find」の行（`dynamic_graph_vertex_add_component_sum`）もその 1 つで、rollback-union-find の末尾に行はなく、問題は練習問題の「Library Checker」の小見出しにある。173 行目の手順 1 が指す #verify-table の 84 ページのうち 30 ページも同じである
- 直し方の案：両方の文に「（発展の概要では、本文の Library Checker の節にある）」を足す

### 6. #64 提案 1（自作するときの決まりの案）の文面と、開いて置く 5 ページの形が合わない

- ファイル：`planning/batches/fix/code-and-library/own-library.md` 103・106 行目（提案 1 の「開くか折りたたむか」「最後の文」）。対応するページは `docs/ds/kth-element.md` 130 行目、`docs/ds/sparse-table.md` 120〜122 行目、`docs/ds/merge-sort-tree.md` 85 行目、`docs/ds/rollback-union-find.md` 63・69・71 行目
- 理由：報告は「ds の 10 ページをこの案にそろえた」とし、Issue の完了の条件も「決まりどおり」である。しかし開いて置くページは、案の次の 2 点と食い違う。メインが案をそのまま手引きに入れると、この 5 ページは手引きに合わないことになる
  - 「最後の文：試験で確かめたことを 1〜2 文で書き、名前の約束…で結ぶ」：kth-element・sparse-table・merge-sort-tree は、リンクの文をコードの前の段落の末尾に置き、試験の文がない。rollback-union-find も試験の文がない
  - 「コードの直前の段落に『ACL にはないので自作する』と書く」：sparse-table はその段落（120 行目）とコードの間に「C++ では次のように書く。…」（122 行目）がある。rollback-union-find は ACL では取り消せないことをコードの後（69 行目）に書いている
- 直し方の案：案の方を実態に合わせるのが手軽である。たとえば「最後の文」を折りたたみのときの決まりとし、「開いて置くときは、ACL にないこと・ACL の名前との対応・名前の約束へのリンクを、コードの前の段落にまとめてよい。試験の文は任意」を足す。ページの方を案にそろえるなら、上の 4 ページの文を動かし、試験の文を足す

## 確かめたこと

### #53：verify の問題へのリンク（スクリプトで数えた）

作業用フォルダにビルドし（`uv run mkdocs build -q -d <作業用フォルダ>/site`）、独自のスクリプト（作業用フォルダの `count_verify.py`。担当のものは使っていない）で、docs のすべての Markdown の front matter の verify と、表示された HTML を突き合わせた。

- verify を持つページは 84。84 ページすべてで、verify の各問題について `href="https://judge.yosupo.jp/problem/<名前>"` が HTML にある（欠け 0）
- 「自作の確認」の行が出るのは 54 ページ、出ないのは 30 ページ。出ない 30 ページはすべて発展の概要で、verify の問題がすべて本文にリンクされている。行に出る問題の並びは、54 ページすべてでテンプレートの決まり（発展の概要は本文にリンクのある問題を除く、ほかは全部）どおりだった。行のある 54 ページすべてに「確かめ方」（`../../guide/library-design/#verify`）がある
- verify の問題名は 136 種類。library-checker-problems の categories.toml（raw.githubusercontent.com）にない 6 個（aho_corasick・minimum_enclosing_circle・minimum_steiner_tree・range_add_range_min・static_range_sum_with_upper_bound・sum_of_multiplicative_function）も、同じリポジトリの木（GitHub の API）に `<分野>/<名前>/info.toml` があった。136 個すべてが実在の問題で、行のリンクは切れない
- 自作の節を持つ 10 ページ（segment-tree・lazy-segment-tree・fenwick-tree・kth-element・union-find・weighted-union-find・rollback-union-find・segment-tree-binary-search・sparse-table・merge-sort-tree）は、どれも本文に library-design の #interface と #verify へのリンクがある（表示された HTML で数えた）。library-design に `acl-names`・`interface`・`verify` の id がある

### #53：発展の概要と Library Checker の節の重なり

- verify を持つ発展の概要は 31 ページ。30 ページは verify の問題がすべて本文（#library か練習問題の Library Checker の小見出し）にリンクされていて、末尾の行は出ない。重なりはない
- 残る dynamic-dp だけが重なる（直しが要る点 4）
- 技術のページでは、本文にリンクのある問題も行に出る。重なるのは次の 26 ページで、担当が「判断してほしい点 2」でメインに回している。このうち segment-tree・fenwick-tree・union-find の 3 ページは、今回の自作の囲みで足したリンクと行が重なる（担当の提案の「触れるならリンクにする」どおりなので、直しは要らない）
  - zeta-mobius-subset・binary-trie・fenwick-tree・mo-algorithm・persistent-data-structures・segment-tree-on-values・segment-tree・sparse-table・sqrt-decomposition・sweep-line-2d・union-find・circle-geometry・complement-graph-bfs・degree-sqrt・dijkstra・euler-path・lowlink・min-cost-flow・minimum-spanning-tree・exponent-mod・floor-sum・multiplicative-order・centroid-decomposition・euler-tour・lca・tree-diameter

### #53：テンプレートと CSS

- 行は関連の欄の後・知識マップのリンクの前に出て、`grid-column: 1 / -1` で全幅になる。nav を出す条件に `vf_ns.items` が足されているので、verify だけを持つページでも出る。メソッドの呼び出しはなく（`in`・`~`・`urlencode`・`loop.first`）、front matter の文字列は `| e` を通している
- 見た目（ヘッドレスの Chrome、作業用フォルダの http.server 経由、日本語のフォントあり）：幅 390px のライト・ダーク（fenwick-tree）、幅 390px で問題が 5 つ（math/gaussian-elimination）、幅 1280px のダーク（gaussian-elimination）、dynamic-dp の #library と末尾を撮った。長い問題名は途中で折り返し、横にはみ出さない。幅 390px でページの scrollWidth が clientWidth を超えないこと（library-design・fenwick-tree・gaussian-elimination・lazy-segment-tree・segment-tree・union-find）も測った
- library-design #acl-names の表（5 列）は、幅 390px では表だけが横にスクロールし、ページははみ出さない

### #64：自作の節の置き方（提案 1 の案と照らした）

| ページ | ACL の囲み | 置き方 | 案との照合 |
| --- | --- | --- | --- |
| segment-tree | あり | #operations の終わりの折りたたみ「自作するとき：`SegTree`（ACL の `segtree` に当たる）」 | 合う（違いの書き漏れは直しが要る点 2） |
| lazy-segment-tree | あり | 青の節 #invariants の終わりの折りたたみ | 合う |
| fenwick-tree | あり | #operations の終わりの折りたたみ | 合う（違いの書き漏れは直しが要る点 1） |
| kth-element | あり（BIT では書けない操作） | #bit-binary-search の各操作の手順の後に開いて置く | 置き場所・開き方は合う。最後の文は直しが要る点 6 |
| union-find | あり | #operations の折りたたみ（後ろに ACL の囲み） | 合う |
| weighted-union-find | なし | #operations の終わりに開いて置く | 合う |
| rollback-union-find | なし（発展の概要） | #library に開いて置く | 置き場所は合う。文の位置は直しが要る点 6 |
| segment-tree-binary-search | あり | #complexity の「再帰で書くとき」の終わりの折りたたみ | 置き方は合う。文は直しが要る点 3 |
| sparse-table | なし | #build の各操作の手順の後に開いて置く | 置き場所・開き方は合う。文の位置は直しが要る点 6 |
| merge-sort-tree（Issue の一覧の外） | なし | #build の構築の手順の後に開いて置く | 開き方は合う。最後の文は直しが要る点 6 |

- 折りたたみの題のバッククォートは `<summary>` の中で `<code>` になり、囲みの中のコードの取り込みも `<details>` の中に入っている（lazy-segment-tree・union-find・segment-tree を開いて撮った）

### #64：ACL v1.6 との照合（third_party/ac-library と ~/lib/ac-library-master/document_ja）

- segtree：自作の `SegTree` のコンストラクタ 3 つ・`set`・`get`・`prod`・`all_prod`・`max_right(l, f)`・`min_left(r, f)` と前提の `assert` は ACL と同じ。ACL のドキュメントの `op` の型は `S op(S a, S b)` なので、自作がテンプレートの引数を関数のポインタで受けることは違いに数えなくてよい（`const S&` を受ける関数は ACL の実装では通り、自作では通らないが、ドキュメントの約束の外である）。`min_left<f>(r)` の書き漏れは直しが要る点 2
- lazy_segtree：7 つの部品・コンストラクタ 3 つ・`set`・`get`・`prod`・`all_prod`・`apply(l, r, f)` は同じ。`apply(p, f)`・`max_right`・`min_left` がないことは囲みと表にある
- fenwick_tree：`add`・`sum(l, r)` は同じ。中身が `long long` のままであること、`sum(r)`・`lower_bound(w)` を足したこと、`assert` を省いたことは書いてある。コンストラクタの書き漏れは直しが要る点 1
- dsu：`find` と `leader`、`merge` の返り値（`bool` と代表元）、`groups` がないことは、union-find の囲み・表・表の後の注意にある。`if (uf.merge(a, b))` が ACL では代表元が 0 でないかを見るだけになる、という注意も正しい
- weighted-union-find・rollback-union-find・sparse-table・kth-element・merge-sort-tree の、ACL にないことと名前の対応の説明は、コード片と合っていた。kth-element の `kth(k)` と fenwick-tree の `lower_bound(w)` は、長さ 0〜19 の乱数の列で 1,000,000 回比べて返り値がすべて同じだった（本文の「返り値も同じ 0-indexed の位置」は正しい）

### #64：コード片

- `python3 tools/check_snippets.py -v snippets/{segment-tree,lazy-segment-tree,segment-tree-binary-search,sparse-table,fenwick-tree,kth-element,union-find,weighted-union-find,rollback-union-find,merge-sort-tree,library-design}`：28 片・コンパイル 28 回・期待と違う 0
- 直した 10 ファイル（segment-tree/own・lazy-segment-tree/own・segment-tree-binary-search/own-max-right・sparse-table の 2 つ・fenwick-tree/own-bit・kth-element の 2 つ・weighted-union-find の 2 つ）を `-fsanitize=address,undefined -fno-sanitize-recover=all` で cases どおりに動かし、報告なし・出力一致
- ACL との突き合わせ（作業用フォルダ。core の範囲を切り出して使った）
  - 自作の `SegTree` と `atcoder::segtree`：可換でない演算（mod 7 の 2×2 行列の積）、長さ 0〜39、乱数の更新・取得・`all_prod`・`get` と、単調でない判定の関数での `max_right`・`min_left`。144,752 回の比較ですべて一致。`SegTree()`・`SegTree(5)` も確かめた
  - 自作の `LazySegTree` と `atcoder::lazy_segtree`：作用が可換でないアフィン、値に左端・右端を持たせて演算も可換でなくした型で、乱数の作用・取得・`set`・`get`・`all_prod`。96,617 回の比較ですべて一致
  - 再帰の `max_right`（own-max-right.cpp）と ACL の `max_right`：上の行列の積と単調でない判定の関数で、150,000 回すべて一致
- 試験が誤りを見つけるか（わざと壊して cases を流した）
  - lazy-segment-tree/own.cpp：`all_apply` の合成の向きを逆にする・`set` の前の push を消す・`get` の前の push を消す → どれも 3 case とも assert で落ちる。本文の「この試験で見つかる」は正しい。`prod` で左右の子を結ぶ順を逆にしても落ちない（試験の 2 つの型は、値の演算が min と和で可換なため）。本文はこれを主張していないので直しは要らない（下の参考 2）
  - segment-tree/own.cpp：`min_left`・`max_right` の掛ける向きを逆にする → 3 case とも落ちる。`prod` の左右を逆にする → 1 つ目の case で落ちる
- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0

### ほかの箇所への影響

- `python3 tools/check_pages.py --page <id> -v`（直した 11 ページと dynamic-dp）：どれもエラー 0・警告 0。全ページ（`check_pages.py`）もエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`（ds の 10 ページ）：直すべき行 0
- `uv run mkdocs build --strict`（作業用フォルダへ）：警告なしで通った
- `python3 tools/gen_site.py --check --diff`：llms.txt・graph.json・how-to-use.md の版の文字列（ハッシュ）だけが変わる。メインが作り直す
- `uv run python -m unittest discover -s tests/tools`：68 件すべて通った
- `npx textlint`（直した 11 ページ）：エラー 0。直した行に出る警告は segment-tree-binary-search の 123・125 行目の 2 つだけで、どちらも前からある文（担当の報告どおり）。textlint が見ない囲みの 2 段落目以降は、足した行の文の長さを数え、100 字を超える文がないことを確かめた
- 消したコード片 `lazy-segment-tree/own-add-min.{cpp,yaml}` を参照するのは、planning の過去の記録（pilot-verify）と担当の報告だけで、docs・snippets・tools には残っていない。sparse-table の旧名 `sparse_table`・`query` を参照するページもない（math/gcd-properties の `gcd_table::query` は別の部品）
- 直したコード片を取り込むのは、それぞれのページだけである。本文を直したページと、取り込むコード片が変わったページの `updated` は、すべて 2026-10-29 になっている

## 直さなくてよいが、伝えておくこと（参考）

1. **技術のページの重なり**（担当の判断してほしい点 2）：上の 26 ページで、本文のリンクと末尾の行に同じ問題が出る。今の形（末尾のいつもの場所に必ず並ぶ）で困ることはない。メインが決める
2. **遅延セグメント木の試験**：値の演算が可換でない型を 1 つ足すと（たとえば値に左端・右端を持たせる）、`prod` で子を結ぶ順の誤りも見つかる。本文の「境界」の 3 つ目（演算が可換でないときは左の子を先に結ぶ）の確かめになる
3. **merge-sort-tree**：コードが #build（構築の手順）にあり、`count_sum_le` の手順（#query）より前に出る。Issue の一覧の外で、前からの位置である。コンストラクタに `explicit` がない（ほかの自作には今回付けた）
4. **提案 1 の「節の終わり」**：kth-element・sparse-table は「### 各操作の手順」の後・「### 境界」の前に、lazy-segment-tree は上の帯の節の終わり（「### 境界（自作で増えるもの）」の後）に置いている。どちらも案の 2 つの文に合うが、手引きに入れるときは「各操作の手順の擬似コードの後（境界の小見出しより前でよい）」と書くと迷わない
5. **重み付き Union-Find の確認の問題**：`unionfind_with_potential` は mod 998244353 の問題で、自作の `WeightedUnionFind`（`long long` の差を等号で比べる）はそのままでは使えず、差を mod の加算にして使う（本文の #generalization にある）。library-design の表に「差を mod 998244353 にして使う」と添えると親切である
6. **segment-tree-binary-search の言葉**：「再帰で書くとき」は「掛ける」にしたが、同じ節の上の手順（和の図の説明）は「足す」のままである。和の例の説明なので誤りではない
7. **library-design の表の幅**：5 列で、幅 390px では「ACL との違い」の列が狭く、型名が途中で折れる。手引きの目安（列は 4〜5 まで）の内なので、そのままでよい

## 使ったもの

- 作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-and-library/verify-own-library`（ビルドしたサイト・count_verify.py・突き合わせと壊した版の C++・スクリーンショット）。http.server（ポート 43817）は使い終えて止めた
- ACL v1.6：`third_party/ac-library/atcoder/{segtree,lazysegtree,fenwicktree,dsu}.hpp`、`~/lib/ac-library-master/document_ja/{segtree,fenwicktree,dsu}.md`
- library-checker-problems（付録 B の raw.githubusercontent.com・github.com）：`categories.toml`、リポジトリの木（`gh api`）、`data_structure/unionfind_with_potential/task.md`
