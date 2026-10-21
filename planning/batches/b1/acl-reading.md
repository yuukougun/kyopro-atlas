# acl-reading の報告（工程8b・バッチ b1）

- 書いたファイル：docs/cpp/acl-reading.md、snippets/acl-reading/（20 組。conventions・explicit-ng・explicit-ok・components・groups・groups-ng・modint・modint-cout-ng・modint-println-ng・modint-val・modint-sort-ng・modint-sort-ok・segtree-args・segtree-lambda・segtree-lambda-cxx17-ng・capturing-ng・capturing-ok・max-right・lazy-args・template-arg-ng）、docs/img/acl-reading/template-args.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を見出しに合わせて短くした（anchor・level は変えていない）。template-arg-errors の title の例を `op must work as S(S, S)` から `mapping must work as S(F, S)` に変えた（本文の実例に合わせた）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 20 組・37 回のコンパイルで期待と違う 0。textlint エラー 0、警告 1（193 行。結合法則の数式の中のカンマを max-comma が数える誤検出）
- 使った出典：ACL v1.6 の document_ja（手元 ~/lib/ac-library-master と GitHub）、github.com/atcoder/ac-library/releases（v1.5 の関数の形の拡張・v1.6 の val()）、gcc.gnu.org/projects/cxx-status.html（P2718 は GCC 15）、en.cppreference.com の Range-based for loop と Template parameters。新しいドメインはない

## 台帳への提案

- なし。catalog の problems_note のとおり、C++ のページには問題を置かなかった（本文の確認問題 6 問で確かめる）

## 用語集への提案

- なし（結合法則 `associativity`・単位元 `identity-element` は既存の anchor にリンクした）
- 候補（メインの判断で）：作用｜action｜遅延セグメント木で、区間の各要素に施す更新。ACL の lazy_segtree では型 F・mapping・composition・id で表す

## 手引きへの提案

- §9 のコード片の規則に一言足すとよい：`ranges::sort(v, {}, &mint::val)` のようにメンバ関数のポインタを射影に渡すと、g++-13・g++-15 の `-O2 -Wall` で `-Warray-bounds` の誤警告が出た（ACL の modint で確認）。射影はラムダ `[](mint x) { return x.val(); }` にする
- 実行時に落ちることを示すコード片（groups-ng のように版によって Segmentation fault になるもの）は、check_snippets の expect で「落ちる」を表せない。今回は安全な環境（g++-15・gnu++23）の run だけを設定し、落ちる環境の結果は本文に手で書いた。必要なら expect: crash（または sanitizer 付きの実行で失敗を期待する形）の追加を検討してほしい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- なし（C++ のページは問題を置かない方針）

## 未解決の点

- cpp_std・gcc_min は null のままにした。ページの中心が 1 つの版に決まらない（ACL 自体は C++17 の `auto` テンプレート引数、ラムダを直接渡すのは C++20、groups の節は C++23・GCC 15）ため、catalog の規則に従った
- 「ACL v1.4 以前は関数の名前しか受け取らない」は、v1.5 のリリースノート（#160 で受け取る関数の形が広がった）と v1.5 以降のソースからの判断で、v1.4 のソースは手元にないので直接は確かめていない
- 図 template-args.svg は手元に SVG の描画の道具がなく、表示を目で確かめていない（座標を手で調べただけ）。検証役に表示の確認を頼みたい
- 本文で節へリンクした cpp-initialization#explicit・cpp-range-for#temporary-range は、front matter は draft だが、確認した時点では本文に見出しがまだなかった（並行して執筆中と思われる）。anchor は相手の sections にあるので check_pages は通る
- 部品の一覧の表の「手法のページ」のリンク先（union-find・fenwick-tree・scc・two-sat・max-flow・min-cost-flow・convolution-ntt・z-algorithm）はまだ stub なので、ページへのリンクだけにして節へはリンクしていない
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 5 回（うち 1 回は 404 で、その出典は使わなかった）
