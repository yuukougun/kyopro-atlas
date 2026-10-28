# graph-ds の直しの検証（バッチ minor-content）

- 検証した担当：graph-ds（報告は [graph-ds.md](graph-ds.md)）。担当の Issue：#21・#22・#23・#24・#26・#27・#28・#29・#30・#19（#19 は segment-tree-on-values の分だけ。alien-dp・cht は別の担当）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content、未 commit の差分を `git diff` で読んだ）。ファイルは直していない（この報告だけを書いた）
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/verify-graph-ds
- 結論：**10 件とも合格。直しが要る点は 0 件**。メインの反映が要る点（台帳の提案・生成物・frequency）は下の「メインに伝える点」に書いた

## Issue ごとの判定

| Issue | 判定 | 確かめたこと |
| --- | --- | --- |
| #21 なもりグラフの章 | 合格 | chapter が「基本と探索」、order が 75（cycle-detection 70 と bipartite-graph 80 の間）。id・URL・sections・related（functional-graph）・#directed-version は変わらない。`gen_site.py --check --diff` で nav.yml・docs/graph/index.md・一覧・llms.txt・graph.json・ロードマップ（水の 41 → 35 番）が意図どおりに変わることを見た（作り直しはメインの仕事） |
| #22 lowlink のブロックカット木の節 | 合格 | 節が #vs-scc の後・落とし穴の前にあり、中身と anchor は同じ。front matter の sections の順と本文の順が一致した。節の冒頭「ここまでの関節点の条件を前提にする」は新しい位置でも通じる。練習の「[ブロックカット木の節](#block-cut-tree)」も届く |
| #23 重心分解のリンク先 | 合格 | `../tree/tree-traversal.md#bfs-order` になった。tree-traversal に `{#bfs-order}` の見出しと sections がある。リンクの文字は tree-centroid・leaf-first と同じ |
| #24 SCC の推移性の重複 | 合格 | 反射律・対称律・推移律が 1 文にまとまり、推移性は 1 回だけになった。「推移律」の語はサイトのほかのページ・用語集（半順序）と同じ |
| #26 Union-Find の merge の返り値 | 合格 | third_party/ac-library の `dsu::merge` は `int`（`leader` を返し、もともと同じなら `x == y` の `x`）で、document_ja/dsu.md の「連結だった場合はその代表元、非連結だった場合は新たな代表元」と合う。third_party と ~/lib/ac-library-master の atcoder/ は同じ中身（diff で確認）。ACL の囲みの 2 段落目（`if (d.merge(a, b))` は代表元が 0 かを見るだけ、先に `same`）は正しく、境界の節の acl-cycle.cpp は実際に `same` で調べてから `merge` している。#size-and-edges の書き分け（ACL は返り値、自作は `find(a)`）も own-dsu.cpp の `bool merge` と合う。使い分けの行き止まりは offline-dynamic-connectivity と rollback-union-find#offline-dynamic-connectivity（anchor あり）へつながった |
| #27 BIT の閉区間 | 合格 | 6 か所とも半開区間になった。fenwick-tree 146 行目の `sum(0, A_i + 1)` と、すぐ下の count-by-value.cpp の `cnt.sum(0, id + 1)` は同じ形（値をそのまま添字にした形と、圧縮した番号 id の形）。159 行目は $[0, \mathrm{id})$ と $[0, \mathrm{id} + 1)$ がそろった。kth-element の「$[0, r)$ の和が $k$ 未満で $[0, r + 1)$ の和が $k$ 以上」は ACL の max_right の約束（`r = n` か `g(op(a[l..r])) = false`）と合う。segment-tree-on-values 124 行目も $f = [c \le K]$ の max_right と合う |
| #28 遅延セグメント木の max_right | 合格 | third_party/ac-library の lazysegtree.hpp に `template <class G> int max_right(int l, G g)`・`int min_left(int r, G g)` があり、`seg.max_right(l, f)`・`seg.min_left(r, f)` の形で呼べる（`<g>` の形は `bool (*g)(S)` の関数ポインタだけ）。同じ囲みの `apply(l, r, f)` の `f`（作用）と取り違えないよう 1 文で断ってあり、segment-tree-binary-search#what-it-does の ACL の囲み（要件 $f(e())$ が真・副作用がない、`lazy_segtree` にも同じ約束）へリンクしている。docs と snippets に `max_right<`・`min_left<` の形はもう残っていない |
| #29 見慣れないデータ構造の節の並び | 合格 | #elsewhere が最初の節になり、sections の並びも elsewhere → table → meldable-heap。anchor と中身は同じ。要点の「使い方」の順（#elsewhere → #table）と節の並びが合う。#table の「[次の節](#meldable-heap)」も次の節を指す |
| #30 練習 2 問の移動 | 合格 | 台帳の abc309_f・abc283_f の pages が segment-tree-on-values の practice になり（差分は 2 行だけ）、本文の行・方針・参考が移った。`fix_problems.py --check --page segment-tree-monoids --page segment-tree-on-values` は直すべき行 0・直せない行 0・台帳にあって本文にない 0。全ページの `fix_problems.py --check` も 0。練習の並びは易しい順（1283・1562・1619・1771、1666・2052）。補った abc467_f は台帳で確認済み・ap.py で 2052 を確かめた。要約を足す型（括弧列の (合計, 最小接頭和) の min を max に替えた結合）で、このページの主題に当たる |
| #19 segment-tree-on-values の前提 | 合格（この担当の分） | prerequisites と要点の前提が [fenwick-tree, segment-tree, coordinate-compression] で一致し、リンクの文字はほかのページの前提（euler-tour・kth-element など）と同じ「BIT（Fenwick Tree）」。fenwick-tree は同じ分野で order 150 < 200、レベルは水どうしで、check_pages の警告は出ない。ビルドしたページ下部の「前提」にも BIT が出る。alien-dp・cht の分はこの検証の外 |

## 直しが要る点

なし。

## メインに伝える点（直しは要らない）

1. **#30 の台帳の提案（メインの反映待ち）**：segment-tree-monoids の練習の abc467_f の行は、台帳の pages にまだ segment-tree-monoids がない（台帳は exchange-argument の力試しだけ）。fix_problems・check_pages は「本文にあって台帳の pages にない」組を見ないので、今は検査が通る。担当の提案 1（`{id: segment-tree-monoids, role: practice}` を足す）を入れた台帳の写しを作業用フォルダに作って試し、`fix_problems.py --check --ledger <写し>`（3 ページ）と `check_pages.py --ledger <写し>` がどちらも 0 件であることを確かめた。台帳が正なので、gen_site の前にこの提案を反映する
2. **#30 の abc467_f の役割**：練習でも力試しでもよい。力試しに移すと練習が ABC331 F の 1 問になり、目安の 2〜6 を下回る。Issue の指定（練習に補う）にも合うので、練習のままでよいと考える
3. **ABC467 F の方針の確かめ**：B の降順が最適であることと、（A の和, 自分までの A の和 + B の最大）を $(s_x + s_y, \max(m_x, s_x + m_y))$ で結び、空の葉を $(0, -\infty)$、同じ B を 1 つの葉にまとめる計算が正しいことを、台帳の summary のモデル（1 通ずつ書いて送り、送ってから B 後に返信）で全順列と照らした（3000 件。スクリプトは作業用フォルダの scripts/abc467f_check.py。リポジトリには置いていない）。exchange-argument の力試しの方針とも食い違わない
4. **#21 の order 75**：order は D18 で 10 刻みにしたが、schema の説明は「骨格では 10 刻み」で、間に入れる余地として使ったものと読める。10 の倍数でない order はサイトでこれだけだが、検査はなく、ほかのページの order を動かさずに済む。namori-graph の `updated` は本文を変えていないが、変えてよい項目の範囲なので判断はメインに任せる
5. **#19 の related**：segment-tree-on-values の related から fenwick-tree を外したのは、check_pages の「前提と related の重複」の警告を避けるためで、妥当と考える（fenwick-tree 側の related には segment-tree-on-values が残り、segment-tree と同じ形）
6. **frequency**：`frequency.py --check` で fenwick-tree（前提として 13 → 16 ページ）・segment-tree-monoids（古い ABC 5 → 3 問）・segment-tree-on-values（5 → 7 問）の差分が出る。台帳の提案を反映した後に `--write` を流す（担当の提案 2 のとおり。abc467_f を足すと segment-tree-monoids の recent の数も変わりうる）
7. **ABC467 F の行の要約**：台帳の summary のままなので「A_j」「B_j」が素の文字で出る（ABC283 F の「|P_i − P_j|」と同じ）。問題の行の書き方は #68 で方針を決めるので、ここでは直さない
8. **#27 の範囲の外の閉区間**：担当の報告のとおり、fenwick-tree 82・244・300 行目、segment-tree-on-values 199 行目、sweep-line-2d の問題文の区間などに「閉区間」と断らない閉区間が残る。Issue が挙げた箇所ではないので、#77（表記）でまとめて扱うのがよい
9. **マージ**：メインの作業ツリーには docs/ds/sweep-line-2d.md の未 commit の変更（`updated` を同じ 2026-10-29 にし、101 行目の代替テキストの `[` をエスケープ）がある。この担当の変更は同じ値の `updated` と 85 行目なので、食い違いは出ない

## 検査の結果

- `python3 tools/check_pages.py --page <id>`：12 ページすべてエラー 0・警告 0。全ページ（353）でもエラー 0・警告 0
- `python3 tools/fix_problems.py --check`：2 ページ・全ページとも直すべき行 0・直せない行 0・台帳にあって本文にない 0
- `npx textlint`（12 ファイル）：エラー 0・警告 207（HEAD の版は 194）。増えたのは、数式の中の半開区間の `[` に対の `]` がない（no-unmatched-pair）7 件と、それで文の区切りがずれた長い文・LaTeX の文字数による長い文（scc 51 行目など）で、手引き §13-8 の誤検出である。textlint が見ない union-find の ACL の囲みの 2 段落目は、取り出して textlint にかけてエラー・警告 0
- `python3 tools/gen_site.py --check --diff`（書かない）：nav.yml・docs/graph/index.md・docs/lists/・docs/index/・llms.txt・graph.json・逆引き・ロードマップに意図どおりの差分（ほかの担当の分を含む）。作業ツリーは変わっていない
- ビルド：`uv run mkdocs build -q -d <作業用フォルダ>/site` と `--strict` のビルドが通った（作業ツリーは変わっていない）
- 表示：作業用フォルダで `python3 -m http.server`（ポート 43183。使い終えて止めた）を立て、ヘッドレスの Chrome で 12 ページの描画後の DOM を出し、KaTeX のエラー 0・描かれていない数式 0 を確かめた。幅 390px のライトとダークで、union-find の ACL の囲み（2 段落とも囲みの中）・#size-and-edges・使い分け、lowlink の #vs-scc → #block-cut-tree → 落とし穴、advanced-ds-catalog の冒頭（#elsewhere の表）、fenwick-tree の #count-by-value、kth-element の ACL の囲み、sweep-line-2d の #rectangle-count、segment-tree-on-values の要点・練習・方針、segment-tree-monoids の練習・方針、lazy-segment-tree-patterns の ACL の囲み、scc の #condensation、centroid-decomposition の落とし穴を撮って見た（作業用フォルダの shots/）。崩れはない
- コード片・図・動く図は変わっていないので、check_snippets・check_svg・tests/viz は流していない

## 使った資料

- AtCoder Library v1.6：third_party/ac-library/atcoder/dsu.hpp・lazysegtree.hpp、~/lib/ac-library-master/document_ja/dsu.md・lazysegtree.md
- `python3 tools/ap.py show`：abc467_f（2052）・abc309_f（1619）・abc283_f（1771）・abc331_f（1666）
- Web は開いていない（atcoder.jp・codeforces.com も開いていない）
