# own-library の報告（code-and-library：#53・#64）

- 担当：#53（自作の確認用の問題を各ページから開けるようにする）・#64（自作の示し方と名前を ACL との対応が分かる形にそろえる）
- 作業ツリー：`../kyopro-atlas-wt/code-and-library`（feat/code-and-library）。2026-10-29
- 前の実行が 5 時間の上限で止まった後の再開だが、作業ツリーにこの担当の変更は残っていなかったので、最初から行った

## まとめ

| Issue | 状態 | 一言 |
| --- | --- | --- |
| #53 | 完了（担当分） | テンプレートがページ下部に「自作の確認：Library Checker の …（確かめ方）」の行を出す。verify を持つ 84 ページすべてで、表示された HTML に verify の問題へのリンクがある。自作の節を持つ ds の 10 ページから library-design の #interface・#verify へリンクした。グラフ・木の名前だけの問題名は graph-code の担当 |
| #64 | 完了（担当分） | 「自作するとき」の決まりの案を提案に書き、ds の 10 ページをそろえた。ACL と違う名前・返り値を各ページに書き、library-design に対応表（#acl-names）を置いた。遅延セグメント木の自作を汎用にし、自作のセグメント木に `all_prod`・`max_right`・`min_left` を足した。手引きへの反映はメイン |

## #53：確認用の問題の表示

### 直したもの

- `overrides/main.html`
    - 75・87 行：nav を見るループで library-design の URL を `ns.lib_url` に取る
    - 237〜245 行：front matter の `verify` から出す問題の一覧 `vf_ns.items` を作る。**type が overview のページだけ**、本文の HTML に `judge.yosupo.jp/problem/<名前>"` があればその問題を出さない（発展の概要は本文の #library に Library Checker の対応を書く決まり。§13-10・§16-4）。ほかの種類のページは、本文にリンクがあってもすべて出す
    - 249 行：ページ下部の nav を出す条件に `vf_ns.items` を足す
    - 301〜303 行：関連の欄の後・知識マップのリンクの前に 1 行を出す。`<p class="kp-links__verify"><span class="kp-links__verify-label">自作の確認</span>：Library Checker の <a href="https://judge.yosupo.jp/problem/…">問題名</a>、…（<a href="…/guide/library-design/#verify">確かめ方</a>）</p>`
    - 冒頭のコメントに部品の一覧を足した。メソッドの呼び出しは使っていない（`in`・`~`・`urlencode`・`loop.first` だけ）
- `overrides/assets/css/kp.css`（末尾に追記だけ）：`.kp-links__verify`（行の全幅・余白）、`.kp-links__verify-label`（太字）、`.kp-links__verify a { overflow-wrap: anywhere; }`（問題名は長い 1 語なので、狭い画面では途中で折り返す）
- 自作の節を持つ ds のページから library-design へのリンク：segment-tree・lazy-segment-tree・fenwick-tree・kth-element・union-find・weighted-union-find・rollback-union-find・segment-tree-binary-search・sparse-table・merge-sort-tree の 10 ページに、「名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。」を置いた（#64 の「自作するとき」の囲みかコードの前の段落の中）
- `docs/guide/library-design.md` 173 行：動作確認の手順の 1 に「同じ問題は、手法のページの末尾の「自作の確認」の行にも出る」を足した

### 確かめたこと

- 作業用フォルダへのビルド（`uv run mkdocs build -q -d <作業用フォルダ>/site`）で、verify を持つ 84 ページすべてについて、表示された HTML に verify の各問題へのリンク（`judge.yosupo.jp/problem/<名前>"`）があることをスクリプトで確かめた。行が出るのは 54 ページ、出ないのは 30 ページで、出ないのはすべて発展の概要で、verify の問題がすべて本文にリンクされているもの（cht・rollback-union-find・hld など）
- hld・general-matching などは graph-code の担当が本文にリンクを足したので、重ねて出ていない（作業ツリーを共有しているため、そちらの変更が入った状態でビルドした）
- 見た目：ヘッドレスの Chrome で、幅 1280 のライトとダーク、幅 375（問題が 5 つの math/gaussian-elimination）を撮って確かめた。幅 375 でも長い問題名が折り返し、横にはみ出さない。手元の Chrome に日本語のフォントがないので和文は豆腐になるが、配置は確かめられた

### 残った点

- テンプレートの説明（how-to-use・interfaces.md §7）は提案に書いた
- 技術のページでは、本文に同じ問題のリンクがあっても行を出す（dijkstra・euler-path などの地の文、complement-graph-bfs・floor-sum・lowlink の練習の Library Checker）。ページの末尾のいつもの場所に並ぶ方を優先した。重なりを避けるなら「すべての種類で、本文にリンクのある問題を出さない」に変えられる（1 行の変更）。判断してほしい点の 2

## #64：自作の示し方と名前

### 決まりの案

全文は提案の 1。要点は次のとおりで、ds の 10 ページをこの案にそろえた。

- **置き場所**：処理の流れ（保つ性質・各操作の手順）の節の終わり、擬似コードの後。上の帯の自作の節があればその節
- **開くか折りたたむか**：ACL に同じ部品がある（「ACL では」の囲みがある）なら `??? note "自作するとき：`型名`（ACL の `名前` に当たる）"` で閉じる。ACL にない部品・ACL の部品では書けない操作は開いて置き、コードの直前の段落に「ACL にはないので自作する」と書く
- **ACL との対応**：囲みの最初の段落（開いて置くならコードの直前の段落）に、そろえた名前と、そろえていない名前・返り値を書く。違いは library-design#acl-names の表にもまとめる
- **最後の文**：試験で確かめたことと、library-design の #interface・#verify へのリンク

グラフのページで ACL に同じ部品があるもの（max-flow・scc・min-cost-flow）は、すでに折りたたみに入れている（題が「C++ の実装例（…）」）。案はこの多数派に合わせ、題を「自作するとき：…」にそろえるものである。

### 直したページ（本文）

| ページ | 置き方 | 書いた違い |
| --- | --- | --- |
| segment-tree（162〜169 行） | #operations の折りたたみ（題を改めた） | 名前・配置・`assert` の前提は ACL と同じ。`max_right<f>(l)` の形はない。手順は segment-tree-binary-search#complexity へ。Point Set Range Composite をリンクにした |
| lazy-segment-tree（352〜359 行） | 青の節 #invariants の終わりの折りたたみ | 7 つの部品・名前は ACL と同じ。区間の操作が再帰で、`max_right`・`min_left`・一点への `apply(p, f)` がない。`max_right` を足す手順（再帰の search で子を探す前に push）。区間加算・区間最小値の部品の対応 |
| fenwick-tree（118〜125 行） | #operations の折りたたみ（開いていたのを閉じた） | `add`・`sum(l, r)` は ACL と同じ。線形時間の構築・`sum(r)`・`lower_bound(w)` を足した。kth-element では同じ探索を `kth(k)` と呼ぶ。中身は `long long`（ACL は符号なし）。`assert` を省いた |
| kth-element（130 行） | 開いたまま（ACL の BIT では書けない操作） | ACL にないので BIT ごと自作。`sum(r)` は ACL の `sum(0, r)`。`kth(k)` は BIT の `lower_bound(w)` と同じ探索で返り値も同じ |
| union-find（112〜123 行） | #operations の折りたたみ（開いていたのを閉じた） | 根を求める関数が `find`（ACL は `leader`）。`merge` は `bool`（ACL は新しい代表元）。`groups()` と `assert` を省いた。Unionfind をリンクにした |
| weighted-union-find（119〜125 行） | 開いたまま（ACL にない） | 名前は Union-Find の自作にそろえた（`find`・`same`）。`merge(u, v, w)` は矛盾しなければ `true` |
| rollback-union-find（63・71 行） | #library に開いたまま（ACL にない） | 名前は `dsu` にそろえ、取り消しの 3 つを足した。本文の find はコードの `leader`。`leader` は経路圧縮をしない。`merge` は `bool` |
| segment-tree-binary-search（121〜134 行） | 「再帰で書くとき」のコードを折りたたみに入れた | 約束は ACL の `max_right(l, f)` と同じ。非再帰の `max_right`・`min_left` はセグメント木の `SegTree` にある |
| sparse-table（114〜122 行） | 開いたまま（ACL にない） | 取得の名前を `segtree` の `prod(l, r)` にそろえた（擬似コードの `query` も `prod` に）。空の区間は渡せない |
| merge-sort-tree（85 行） | 開いたまま（ACL にない） | ACL にないので自作。区間は 0-indexed の半開区間、`count_sum_le(l, r, x)` |

- `docs/guide/library-design.md` 79〜99 行：「名前」の項から表へリンクし、`### この教材の自作と ACL の名前 {#acl-names}` を #interface の中に置いた。列は「部品｜ACL｜この教材の自作｜ACL との違い｜確認の問題」の 5 つで、8 行（Union-Find・重み付き・ロールバック・BIT・K 番目の値（BIT）・セグメント木・遅延セグメント木・Sparse Table）。表の後に find と leader・merge の返り値・assert の 3 つの注意を置いた。front matter の sections は変えていない（### の小見出しにした）
- 本文を直したページの `updated` を 2026-10-29 にした（lazy-segment-tree・weighted-union-find・rollback-union-find・sparse-table・merge-sort-tree・library-design。ほかはすでに 2026-10-29）

### 直したコード片

- `snippets/segment-tree/own.cpp`：汎用の `SegTree` に、ACL と同じ `SegTree()`・`explicit SegTree(int n)`、`all_prod`、ACL と同じ非再帰の手順の `max_right(l, f)`・`min_left(r, f)` と、ACL と同じ前提の `assert` を足した。試験に乱数の確かめを足した（長さ 0〜12。和で「和が w 以下」、可換でない「区間が昇順か」のモノイドで max_right・min_left を素朴な方法と比べる。`all_prod` と `SegTree(n)` も）。cases はそのまま
- `snippets/lazy-segment-tree/own.cpp`・`own.yaml`（新規）：`own-add-min.cpp`・`own-add-min.yaml`（区間加算・区間最小値の専用）を**消して**置き換えた。ACL と同じ 7 つの部品を受け取る `LazySegTree`（区間の操作は本文の擬似コードどおり再帰）で、`set`・`get`・`prod`・`all_prod`・`apply(l, r, f)` と `assert` を持つ。main は前と同じ入出力（cases は前の yaml と同じ）で、乱数の試験は区間加算・区間最小値と区間アフィン・区間和（作用が可換でない）の 2 つで、作用・取得・set・get・all_prod を素朴な方法と比べる。commit では消したファイルも含める
- `snippets/segment-tree-binary-search/own-max-right.cpp`：再帰の `max_right` を部品（`S`・`op`・`e`）を受け取る形にし、`assert(0 <= l && l <= n && f(e()))` を足した。cases はそのまま
- `snippets/sparse-table/sparse-table.cpp`・`disjoint.cpp`：`query` を `prod`、型名を `SparseTable`・`DisjointSparseTable` にし、コンストラクタに `explicit` を付けた
- `explicit` を足した：`fenwick-tree/own-bit.cpp`（BIT）・`kth-element/bit-kth.cpp`・`reverse-insert.cpp`（Fenwick）・`weighted-union-find/weighted-union-find.cpp`・`parity.cpp`（library-design#interface の 2）

### 確かめたこと

- `python3 tools/check_snippets.py`（segment-tree・lazy-segment-tree・segment-tree-binary-search・sparse-table・fenwick-tree・kth-element・union-find・weighted-union-find・rollback-union-find・merge-sort-tree・library-design）：28 片・期待と違う 0
- segment-tree/own.cpp と lazy-segment-tree/own.cpp を `-fsanitize=address,undefined` でも動かし、報告なし
- 試験が誤りを見つけるかを、わざと壊して確かめた（作業用フォルダで）：`min_left` で掛ける向きを逆にする → 「区間が昇順か」の試験が落ちる。`all_apply` の合成の向きを逆にする → 区間アフィン・区間和の試験が落ちる。`set` の前の push を消す → 区間加算・区間最小値の試験が落ちる。本文の「この試験で見つかる」はこの結果による
- ACL v1.6（`third_party/ac-library/atcoder/segtree.hpp`・`lazysegtree.hpp`・`~/lib/ac-library-master/document_ja/dsu.md`）と名前・前提・返り値を照らした。セグメント木の `op`・`e` は、ACL（`auto`）も自作（関数のポインタ）もキャプチャのないラムダを渡せることを g++-15 で確かめたので、違いには書いていない
- Library Checker の問題の題（Unionfind・Point Add Range Sum・Point Set Range Composite）は library-checker-problems の `data_structure/<名前>/info.toml` で確かめた
- ビルドした HTML で、折りたたみの題のバッククォートがコードになること、囲みの中のコードの取り込みが崩れないことを確かめた（lazy-segment-tree・union-find を撮った）

## 検査の結果

- `python3 tools/check_pages.py`（全 353 ページ）：エラー 0・警告 0
- `python3 tools/check_snippets.py`：28 片・期待と違う 0
- `npx textlint`（直した 11 ページ）：エラー 0。直した行に出る警告は segment-tree-binary-search の 2 つだけで、どちらも前からあるもの（123 行の `$[k_l, k_r)$` の括弧の誤検出と、125 行の読点 4 つの文。この文は「足す」を「掛ける」に変えただけ）。折りたたみの中の 2 段落目からは textlint が見ないので、文の長さ・助詞の重なり・空白は自分で確かめ、長い文は分けた
- `python3 tools/gen_site.py --check`：llms.txt・graph.json・how-to-use.md が古いと出る。作業ツリーのほかの担当の変更と合わせた結果で、メインが作り直す
- `python3 tools/fix_code_links.py --check --stat`（直した 11 ページ）：直せないところ 0。メインが流すと、折りたたみの中のコードの下にも「完全なプログラム」の行が入る（字下げは道具が合わせる）

## 提案（メインに頼む共有ファイルの変更）

### 1. 手引き §4 の「ACL では」の段落の後に足す（#64）

（検証の指摘 6 への対応で改めた。開いて置く 5 ページの形に合わせ、置き場所・ACL との対応・試験とリンクの項を、折りたたむときと開いて置くときに分けた。改めた点は末尾の「検証の指摘への対応」にある）

````markdown
**自作するとき**（工程11、#64）：ページの題の部品を自作した実装（ライブラリに入れる形の struct）は、「ACL では」の囲みと対にして次のように置く。節の中の変種（双対セグメント木・BIT 2 本・偶奇の Union-Find など）や使い方の例には当てない。

- **置き場所**：処理の流れ（保つ性質・構築・各操作の手順）を書いた節の中で、手順の擬似コード（ないなら手順の説明）の後に置く。境界の小見出しの前でも後でもよい。上の帯の自作の節（lazy-segment-tree#invariants など）があれば、その節の終わりに置く。発展の概要では `#library` の節に置く
- **開くか折りたたむか**：ACL に同じ部品があり「ACL では」の囲みを置くページは、`??? note "自作するとき：`型名`（ACL の `名前` に当たる）"` の折りたたみに入れる。ACL にない部品と、ACL の部品では書けない操作（BIT 上の二分探索など）は折りたたまずに置く
- **ACL との対応**：折りたたむときは、最初の段落に、ACL にそろえた名前と、そろえていない名前・返り値・引数を書く（「根を求める関数は `find`（ACL では `leader`）」「`merge` は `bool` を返す（ACL は新しい代表元）」）。開いて置くときは、コードより前の段落（同じ節の中。コードの直前でなくてよい）に、ACL にないので自作すること（ACL の部品では書けない操作なら、書けない理由）と、どの ACL の名前・約束にそろえたか（Sparse Table の `prod`）、そろえていない名前・返り値を書く。違いは [library-design の対応表](../guide/library-design.md#acl-names)にもまとめる（行を足すのは提案）
- **名前**：メンバ関数の名前・引数の順・0-indexed・半開区間は ACL にそろえる。コンストラクタは、ACL のドキュメントの各部品の「コンストラクタ」の項にある形（`dsu(n)`・`fenwick_tree(n)`・`segtree(n)`・`segtree(v)` など）を持たせ、足したもの（配列から作る `BIT(a)` など）は違いに書く。そろえないのは本文の手順や図と同じ名前にしたいとき（Union-Find の `find`）だけにし、違いを書く。同じ部品を別のページでも自作するなら、名前をそろえるか違いを書く（`lower_bound(w)` と `kth(k)`）
- **試験とリンク**：折りたたむときは、コードの後の段落に、試験で確かめたこと（素朴な方法との照合・乱数）を 1〜2 文で書き、「名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。」で結ぶ。開いて置くときは、この「名前の約束は…」の文をコードの前の段落の末尾か、コードの後の段落の末尾に置く。試験の文は任意である。確認用の問題（front matter の verify）はテンプレートがページの末尾に出すので、並べ直さなくてよい（触れるなら judge.yosupo.jp へのリンクにする）

折りたたむときの例（union-find#operations）：

```markdown
??? note "自作するとき：`UnionFind`（ACL の `dsu` に当たる）"
    `merge`・`same`・`size` の名前と 0-indexed の添字は、ACL の `dsu` にそろえた。ACL と違うのは次の 3 つである。

    - 根を求める関数は、本文の手順に合わせて `find` とした（ACL では `leader`）。
    - …

    ```cpp
    --8<-- "union-find/own-dsu.cpp:core"
    ```

    試験では、…。名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。
```

開いて置くときの例（sparse-table#build）：

~~~markdown
ACL には Sparse Table がないので自作する。取得の関数の名前と引数は、ACL の `segtree` の `prod(l, r)`（0-indexed・半開区間）にそろえた。ただし ACL の `prod` と違い、空の区間（$l = r$）は渡せない。名前の約束は[インターフェースの決め方](../guide/library-design.md#interface)、確かめ方は[動作確認の手順](../guide/library-design.md#verify)にある。

```cpp
--8<-- "sparse-table/sparse-table.cpp:core"
```
~~~
````

- 今の 10 ページとの照合：折りたたむ 5 ページ（segment-tree・lazy-segment-tree・fenwick-tree・union-find・segment-tree-binary-search）は、最初の段落に ACL との対応、コードの後に試験の文とリンクがある。開いて置く 5 ページ（kth-element・weighted-union-find・rollback-union-find・sparse-table・merge-sort-tree）は、コードより前の段落に ACL にないことと名前の対応がある（rollback-union-find は検証の指摘 6 で文を動かした）。リンクは kth-element・sparse-table・merge-sort-tree がコードの前、weighted-union-find・rollback-union-find がコードの後にある。試験の文は weighted-union-find（「乱数の試験つき」）だけにある
- 題の型名・ACL の名前はバッククォートで書く。折りたたみの題のバッククォートはコードとして出る（cpp-integer-overflow で確認）。バッククォートの外に `UnionFind` と書くと prh が「Union-Find」に直せと言う

### 2. 手引き §15-5（Library Checker の練習）に足す（#53）

- 「front matter の verify の問題は、テンプレートがページの末尾の「自作の確認」の行に出す。技術のページで練習問題に「Library Checker」の小見出しを立てるのは、verify にない問題を足すときか、問題ごとに説明を添えたいときだけでよい。発展の概要は本文の #library に Library Checker の対応を書き（§13-10・§16-4）、テンプレートは本文にリンクのある問題を重ねて出さない。発展の概要の #library に書く問題名は judge.yosupo.jp へのリンクにする（テンプレートはリンクを見て重なりを省くので、名前だけだと末尾の行にも出て 2 か所に並ぶ。dp/dynamic-dp の #library がその形で残っている）」（検証の指摘 4 への対応で最後の文を足した）

### 3. how-to-use（#page-anatomy。ほかの担当が直しているので文案だけ）

- 5 の「ページの下」を「前提・次に読む・関連の 3 つの欄と、**自作の確認の行**、知識マップでこのページの前後を見るリンクがある。…」にする
- 3 つの欄の箇条書きの後に段落を足す：「欄の下の「自作の確認」の行には、そのページの手法を自作したときに確かめられる Library Checker（judge.yosupo.jp）の問題が並ぶ。問題名を押すと問題文へ、「確かめ方」を押すと[自作ライブラリの設計と動作確認](../guide/library-design.md#verify)の手順へ移る。発展の概要のページでは、本文にリンクのある問題（ライブラリの節や練習問題の「Library Checker」など）は重ねて出さない。」
- 224 行（「ACL では」の囲みの説明）の後に足す：「ACL に同じ部品があれば、自作のコードは「自作するとき」の折りたたみに入れ、ACL と違う名前・返り値を最初に書いてある（違いの一覧は[自作ライブラリの設計と動作確認](../guide/library-design.md#acl-names)）。」

### 4. interfaces.md

- §7 の表に行を足す：「自作の確認｜テンプレートが front matter の `verify`（Library Checker の問題名）から、ページ下部の関連の欄の後に `p.kp-links__verify` の 1 行（「自作の確認：Library Checker の <問題名>、…（確かめ方）」）を出す。問題名は `https://judge.yosupo.jp/problem/<名前>`、「確かめ方」は library-design の #verify へのリンク。type が overview のページでは、本文の HTML に `judge.yosupo.jp/problem/<名前>"` がある問題を出さない（本文の #library に書く決まりのため）」
- §2 の front matter の例の `verify:` の注記に「ページ下部の「自作の確認」に出る（§7）」を足す

### 5. design.md

- 技術のページの構成の一覧（401 行の「8. ACL では」）の後に「自作するとき（ACL にある部品は折りたたみ。ACL との名前・返り値の違い。手引き §4）」を足す
- 153 行・319 行の verify（D14）の説明に「ページ下部の自作の確認と、library-design の対応表に出る」を足す

### 6. decisions.md（2026-10-29 工程11 の表）

- 「自作の示し方（#64）｜ACL にある部品の自作は「自作するとき」の折りたたみ、ACL にない部品は開いて置く。名前は ACL にそろえ、そろえない名前（Union-Find の find）と返り値（merge の bool）は違いを書く。Sparse Table の取得は query から prod に改め、遅延セグメント木の自作は部品を受け取る汎用の形にした｜判断してほしい点の 1 の結論を書く」
- 「確認用の問題の表示（#53）｜テンプレートがページ下部に「自作の確認」の行を出す。発展の概要は本文にリンクのある問題を出さない」

### 7. ほかの分野のページ（ほかの担当・後のバッチ）

- 案を採るなら、グラフの自作の折りたたみの題を「自作するとき：…」にそろえ、最初の段落に ACL との対応を書く：graph/max-flow「C++ の実装例（Dinic 法を自分で書く）」（ACL の `mf_graph`）、graph/scc「C++ の実装例（Kosaraju 法）」（`scc_graph`）、graph/min-cost-flow「自作するときのコード（…）」（`mcf_graph`）。graph/euler-path の「C++ の実装例（有向グラフ）」は ACL にない部品なので、案では開いて置く（長いので閉じたままにするなら、案に「長いものは閉じてよい」を足す）
- math/modint#self-made・graph/two-sat・文字列（z-algorithm・suffix-array）など、ACL にある部品の自作を持つページも同じ形にし、library-design#acl-names の表に行を足す

### 8. 検査（任意）

- check_pages に、ds・graph・math のページで「`acl` があり、自作の struct のコード片を取り込むなら、`??? note "自作するとき：` の囲みの中にある」を警告として足せる。今回の 10 ページは満たしている

### 9. commit のときの注意

- `snippets/lazy-segment-tree/own-add-min.{cpp,yaml}` を消し、`own.{cpp,yaml}` を足した。`git add -A` で消したファイルも含める
- 本文の `updated` を変えたので、`tools/gen_site.py` で graph.json・llms.txt を作り直す
- `tools/fix_code_links.py` を流すと、この 11 ページのコードの下にもリンクの行が入る

## メインに判断してほしい点

1. **Union-Find の find と merge の返り値**：自作は `find` と `bool` の `merge` のまま残し、違いを書いた（decisions の #26 のとおりコードは変えていない）。union-find の本文の手順・sections の題・図の代替テキスト・動く図（union-find.js の操作名 find）が find を使うので、そろえるとそれらも直すことになる。library-design#acl-names では「ライブラリにするなら leader にそろえる」と勧めた。ACL にそろえる（`leader` と代表元を返す `merge`）なら、union-find・weighted-union-find の本文・コード片・図を直す別の作業になる
2. **自作の確認の行の重なり**：発展の概要だけ、本文にリンクのある問題を出さない。技術のページは本文にリンクがあっても出す（地の文や練習の Library Checker と重なるのは dijkstra・euler-path・lowlink・min-cost-flow・complement-graph-bfs・floor-sum など約 10 ページ）。すべての種類で重ねない形にもできる（`m.type == "overview" and` を外すだけ）
3. **ACL にない部品の自作を開くか**：案では開いて置く（今の weighted-union-find・rollback-union-find・sparse-table・kth-element・merge-sort-tree の形）。グラフの euler-path のように長いものを閉じてよいかを決めてほしい（提案の 7）
4. **library-design#acl-names を sections に載せるか**：front matter を変えないよう `###` の小見出しにした。ほかのページの related や詳細索引から節として引けるようにするなら、`##` の節にして sections に足す

## 使った資料

- ACL v1.6：`third_party/ac-library/atcoder/segtree.hpp`・`lazysegtree.hpp`（名前・前提の assert・max_right・min_left の手順）、`~/lib/ac-library-master/document_ja/dsu.md`（merge の返り値）
- library-checker-problems（raw.githubusercontent.com）：`categories.toml`、`data_structure/{unionfind,point_add_range_sum,point_set_range_composite}/info.toml` の題。どちらも付録 B のドメイン
- 新しいドメインは使っていない。atcoder.jp・codeforces.com は開いていない

## 検証の指摘への対応（2026-10-29）

verify-own-library.md の「直しが要る点」6 つへの対応である。5 つを直した。4（dp/dynamic-dp.md）は担当外のファイルなので直さず、メインに回す。指摘に誤りはなかった（1・2・3 のコンパイルエラーは g++-15 で再現した）。ただし 1 の「ACL の公開コンストラクタは `fenwick_tree(n)` だけ」は不正確で、`fenwicktree.hpp` には引数なしの `fenwick_tree()` もある（ACL の appendix.md の「デフォルトコンストラクタ」の項のとおり、どの構造体にもある）。そこで自作の BIT には両方を足した。

| 指摘 | 状態 | 直したファイルと行 | 直した内容 |
| --- | --- | --- | --- |
| 1 BIT の `(n)` のコンストラクタ（#64） | 直した | `snippets/fenwick-tree/own-bit.cpp` 2・12・13・50〜55 行、`docs/ds/fenwick-tree.md` 119・125 行、`docs/guide/library-design.md` 90 行 | コード片に ACL と同じ `BIT() : BIT(0) {}` と `explicit BIT(int n) : n(n), t(n + 1, 0) {}`（全要素 0）を足した。囲みは「コンストラクタ `BIT()`・`BIT(n)`（全要素 0）と、`add(p, x)`・`sum(l, r)` の名前と意味は ACL と同じ」「ACL にないものは…線形時間で作るコンストラクタ `BIT(a)`…」にした。表は「コンストラクタ `BIT()`・`BIT(n)` は ACL と同じ。配列から $O(N)$ で作る `BIT(a)`・…を足した」にした。main で、線形時間の構築と `BIT(n)` から `add` を $N$ 回呼んだものの中の配列が一致することと、`BIT()` が長さ 0 になることを `assert` で確かめ、囲みの試験の文に 1 文足した（cases はそのまま） |
| 2 `min_left<f>(r)` の形（#64） | 直した | `docs/ds/segment-tree.md` 163 行、`docs/guide/library-design.md` 92 行 | 囲みを「判定の関数は `max_right(l, f)`・`min_left(r, f)` の引数で渡す。ACL にある `max_right<f>(l)`・`min_left<f>(r)` の形…はない」に、表を「`max_right<f>(l)`・`min_left<f>(r)` の形がない。ほかは同じ」にした。ACL v1.6 の `segtree` の公開メンバ（コンストラクタ 3 つ・`set`・`get`・`prod`・`all_prod`・2 つの形の `max_right`・`min_left`）と照らし、「ほかは同じ」が正しいことを確かめた |
| 3 再帰の `max_right` を「足す」（#64） | 直した | `docs/ds/segment-tree-binary-search.md` 128 行 | 「`SegTree` は ACL と同じ非再帰の手順の `max_right`・`min_left` を持つ。次はその `max_right` を再帰で書いた版である。…`SegTree` で使うときは、非再帰の `max_right` を、この `search` と `max_right` の 2 つで置き換える。両方の `max_right` を残すと、同じ形のメンバ関数が 2 つになってコンパイルできない」にした |
| 4 dynamic-dp の重なり（#53） | 直していない（担当外） | `docs/dp/dynamic-dp.md` 147・148 行（直してよいファイルにない） | メインに回す（下の「メインに判断してほしい点」の 1）。提案 2 に「発展の概要の #library に書く問題名は judge.yosupo.jp へのリンクにする」を足した。テンプレートで `<code>` の問題名も重なりとみなす手は採らなかった（dynamic-dp では本文にリンクがないので、末尾の行を消すと judge.yosupo.jp へのリンクがページから消え、#53 の完了の条件を満たさなくなる） |
| 5 library-design の「末尾にも出る」（#53） | 直した | `docs/guide/library-design.md` 83・173 行 | 両方の文に「（発展の概要では、本文のライブラリの節や練習問題の「Library Checker」などにある）」を足した。指摘の文案「本文の Library Checker の節」は、verify を持つ発展の概要 31 ページを数えると、リンクの置き場所が #library（21 か所）・練習問題の「Library Checker」（38 か所）・中身の節（tree-ratio-greedy の #merge-with-heap）に分かれるので、「や…など」の形にした |
| 6 提案 1 と開いて置くページ（#64） | 直した | この報告の提案 1、`docs/ds/rollback-union-find.md` 63・69 行 | 案を実態に合わせた（下の「提案 1 の改め方」）。rollback-union-find は、ACL の `dsu` では取り消せないことをコードの前の段落の頭に移し（「…取り消しには使えない。そこで自作する。次のコードは…」）、コードの後の段落を「自作のほかに、公開されているライブラリ（…）も使える。」にした。ほかの 4 ページ（kth-element・sparse-table・merge-sort-tree・weighted-union-find）は改めた案に合うので、変えていない |

### 提案 1 の改め方

- **置き場所**：「処理の流れ（保つ性質・各操作の手順）を書いた節の終わり」を「処理の流れ（保つ性質・構築・各操作の手順）を書いた節の中で、手順の擬似コード（ないなら手順の説明）の後。境界の小見出しの前でも後でもよい」にした。発展の概要は `#library` に置くと足した（検証の参考 4 の「境界の小見出しより前でよい」も入れた）。merge-sort-tree のコードは #build の「構築の手順」の後で、#query の擬似コードより前にあるが、この書き方なら合う
- **開くか折りたたむか**：開いて置くときの「コードの直前の段落に『ACL にはないので自作する』」を、次の ACL との対応の項へ移した
- **ACL との対応**：折りたたむときと開いて置くときに分けた。開いて置くときは「コードより前の段落（同じ節の中。コードの直前でなくてよい）」に、ACL にないので自作すること（書けない操作なら理由）・そろえた ACL の名前と約束・そろえていない名前と返り値を書く。sparse-table の 120 行と 124 行のコードの間の「C++ では次のように書く。…」（122 行）は、これで決まりの内になる
- **名前**：コンストラクタの文を足した。ACL のドキュメントの各部品の「コンストラクタ」の項にある形を持たせ、足したものは違いに書く（指摘 1 の再発を防ぐため）。引数なしのコンストラクタは決まりに入れていない（下の「メインに判断してほしい点」の 2）
- **最後の文 → 試験とリンク**：試験の文は折りたたむときの決まりにし、開いて置くときは任意にした。「名前の約束は…」の文は、開いて置くときはコードの前の段落の末尾か、コードの後の段落の末尾に置く
- 開いて置くときの例（sparse-table#build の形）を足した。案の後の箇条書きに、今の 10 ページとの照合を書いた

### 確かめたこと

- 再現：`BIT fw(n);`（直す前）は「no matching function for call to 'BIT::BIT(int&)'」、`SegTree` に再帰の `max_right` を足すと「cannot be overloaded」、`seg.min_left<f>(r)` は「no matching function」で、どれも g++-15 で再現した
- 指摘 1：`python3 tools/check_snippets.py snippets/fenwick-tree`（4 片・期待と違う 0）。`-fsanitize=address,undefined -fno-sanitize-recover=all` で cases の 3 つを動かし、報告なし・出力一致。線形時間の構築の親の添字を `j <= n` から `j < n` に壊すと、足した `assert(bit.t == slow.t)` で落ちる。`BIT fw(n);`・グローバルの `BIT g;` に `g = BIT(n);` と代入する書き方が通り、`BIT fw = 5;` は explicit のためエラーになる（library-design#interface の 2 のとおり）
- 指摘 3：セグメント木の `SegTree` の非再帰の `max_right` を、segment-tree-binary-search の再帰の `search`・`max_right` で置き換えたものを作り、和のセグメント木（長さ 0〜13、3,000 回）で `max_right` と、残した非再帰の `min_left` を素朴な方法と比べた。44,486 回すべて一致し、サニタイザの報告もない
- `python3 tools/check_pages.py --page <id>`（fenwick-tree・segment-tree・segment-tree-binary-search・rollback-union-find・library-design）：どれもエラー 0・警告 0。全ページもエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`（上の ds の 4 ページ）：直すべき行 0
- `python3 tools/check_snippets.py`（segment-tree・lazy-segment-tree・segment-tree-binary-search・sparse-table・fenwick-tree・kth-element・union-find・weighted-union-find・rollback-union-find・merge-sort-tree・library-design）：28 片・期待と違う 0
- `npx textlint`（直した 5 ファイル）：エラー 0。警告の数と中身は直す前と同じ（fenwick-tree 22・segment-tree 23・segment-tree-binary-search 34・library-design 4・rollback-union-find 6。どれも前からある文）。textlint が見ない折りたたみの 2 段落目以降は、字下げを外した写しを textlint にかけた。segment-tree-binary-search の囲みの「で」の重なりが 1 つ出たので文を分け、出なくなった
- `python3 tools/fix_code_links.py --check --stat`（直した 5 ページ）：直せないところ 0（コードの下の行の追加 17 は、メインが流すときに入る分）
- `python3 tools/gen_site.py --check`：llms.txt・graph.json・how-to-use.md が古い（前と同じ。メインが作り直す）
- 作業用フォルダへのビルド（`uv run mkdocs build -q -d <作業用フォルダ>/site`）：表示された HTML で、BIT の折りたたみの中のコードに 2 つのコンストラクタがあること、5 か所の新しい文が出ることを確かめた。検証の担当の数え方（count_verify.py）で、verify を持つ 84 ページすべてに問題へのリンクがあり、行が出るのは 54 ページ・出ないのは 30 ページで、前と変わらない。ヘッドレスの Chrome で幅 390px の library-design（#acl-names の表）・fenwick-tree と segment-tree-binary-search の折りたたみを開いた所・rollback-union-find の #library を撮り、5 ページとも横にはみ出さないことを測った
- `updated`：直した 5 ページはどれもすでに 2026-10-29

### メインに判断してほしい点（この対応で増えたもの）

1. **dp/dynamic-dp.md の #library（指摘 4）**：担当外なので直していない。147 行の「**Point Set Range Composite**（`point_set_range_composite`）」を `[Point Set Range Composite](https://judge.yosupo.jp/problem/point_set_range_composite)` にし、`updated: 2026-10-29` にすると、末尾の「自作の確認」の行が消えて重なりがなくなる（judge.yosupo.jp へのリンクは本文に残るので、#53 の完了の条件も満たす）。148 行の `point_set_tree_path_composite_sum_fixed_root` も同じ形にそろえてよい（verify にはないので末尾の行には関係しない）。origin/main（03e0c36）では dynamic-dp の #resources と使い分けが変わっているが、#library の 147・148 行は変わっていない。なお、この対応で直した 5 ファイルのうち fenwick-tree・segment-tree・segment-tree-binary-search・rollback-union-find は origin/main でも変わっているが、問題の行（「diff —」→「diff なし」）と資料の節だけで、この対応の行とは重ならない
2. **自作の Union-Find の引数なしのコンストラクタ**：ACL の `dsu` には `dsu()` があり（dsu.hpp、appendix.md の「デフォルトコンストラクタ」）、library-design#interface の 2 も引数なしのコンストラクタを勧めている。自作の `UnionFind`（`snippets/union-find/own-dsu.cpp`）にはこれがなく、`UnionFind uf;` はコンパイルできない。union-find の囲みは「ACL と違うのは次の 3 つ」と書いているので、厳密には 4 つ目の違いになる。検証の指摘になく、このブランチで触っていないコード片なので直していない。直すなら、コード片に `UnionFind() {}` を足す（BIT と同じ扱い）か、囲みと library-design の表に「引数なしのコンストラクタはない」と書く
3. 最初の報告の「メインに判断してほしい点」の 1〜4 は、そのまま残る

### 使ったもの

- 作業用フォルダ：`/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-and-library/fixup-own-library`（ビルドしたサイト・再現と置き換えの C++・発展の概要のリンクの置き場所を数えた scan_overview.py・スクリーンショット）。http.server（ポート 43911）は使い終えて止めた
- ACL v1.6：`third_party/ac-library/atcoder/{fenwicktree,segtree,dsu,lazysegtree}.hpp`、`~/lib/ac-library-master/document_ja/{fenwicktree,dsu,appendix}.md`
- 新しいドメインは使っていない。atcoder.jp・codeforces.com は開いていない
