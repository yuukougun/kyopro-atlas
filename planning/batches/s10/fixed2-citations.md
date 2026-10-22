# s10 2巡目：出典の題名のそろえ（§17-10）

decisions.md・§17-10・fixed2-shared.md に従った。commit はしていない。gen_site.py は実行していない。atcoder.jp・codeforces.com は開いていない。

## 洗い出し

- 洗い出しのときの 124 件、fixed2-shared の時点の 35 件は、分野の担当が並行してそろえていたので、作業を始めた時点の check_pages の警告は 2 件だった
- check_pages の警告は参考・学ぶための資料の節で、各行の**最初の**リンクだけを見る。そこで全ページの本文と出典の行の外部リンク `[題名](URL)` をすべて集め（AtCoder の問題のリンクは除く）、URL ごとに題名を比べた（スクリプト：scratchpad/s10b/cite/collect.py）。URL の末尾の `/`・`#…`・http と https の違いを除いて比べるスクリプト（norm.py）も流した
- 残っている違いは、どれもそろえなくてよいものだった
  - 学ぶための資料の節の「X 氏の記事[「題名」](URL)」と、参考の節の「[X「題名」](URL)」：題名は同じで、著者をリンクの外に書く形の違いだけ（stern-brocot・fft-ntt・multiplicative-function）
  - Library Checker の問題へのリンク：練習・ライブラリの節の問題名（例 `Shortest Path`）と参考の `Library Checker「Shortest Path」`、library-design の検証の表の問題の id（`shortest_path`）。問題名と id の列であって出典の題名ではない
  - 本文の文の中のリンクの文字（min-cut の「ACL の appendix」、problem-sets の「judge.yosupo.jp」）

## 直したもの（題名は記事の h1・title を check_noai と同じ取り方で確かめた。2026-10-22）

| URL | そろえた題名 | 直したページ |
| --- | --- | --- |
| github.com/yosupo06/library-checker-problems/tree/master/convolution | yosupo06「library-checker-problems/convolution」（サイトのほかの library-checker-problems の書き方に合わせた） | math/fft-ntt（参考） |
| ikatakos.com/…/2026/0912_abc475 | ikatakos「AtCoder Beginner Contest 475 E,F,G問題メモ」（h1） | math/divisor-count-bound（参考） |
| cpprefjp.github.io/reference/string/basic_string/contains.html | cpprefjp「std::basic_string::contains」（title・h1 に std:: がある） | cpp/cpp-string-api（参考。check_pages は行の 2 つ目のリンクを見ないので警告に出ていなかった） |
| ikatakos.com/…/2026/0627_abc464（#f_-_random_vault_heist つき） | ikatakos「第七回日本最強プログラマー学生選手権～Advance～ -予選- （AtCoder Beginner Contest 464）F,G問題メモ」（h1。meet-in-the-middle・alien-dp と同じ） | comb/probability-symmetry（参考。「ikatakos の競プロ Wiki「ABC464」」から） |
| judge.yosupo.jp/problem/persistent_unionfind | Persistent Unionfind（library-checker-problems の info.toml の title） | ds/partially-persistent-union-find L118（本文の「Persistent UnionFind」） |

## fixed2-shared の差し替えと外し

- doi.org（union-find-applications）・suzukiapple.tumblr.com（sqrt-decomposition）・trap.jp post/1594（hashing-for-sets）：どれもページの担当がすでに反映していた（grep で docs に残っていないことを確かめた）
- trap.jp の残り 4 か所（cpp-environment L304、cpp-macros-template-file L315・L316、static-top-tree L185）：decisions.md は「証明書の検証を外して取得し、noai の指定がなければ残す」だが、fixed2-shared のとおり検証を外した取得はできていない。メインの判断待ちなので変えていない

## 確かめたこと

- `python3 tools/check_pages.py`：エラー 0、警告 0（「同じ URL の出典の題名が違う」も 0）
- collect.py：上の「そろえなくてよいもの」のほかに題名の違いはない
- `npx textlint`（直した 5 ページ）：エラー 0（警告 36 は前からのもの）
- 図・コード片・anchor・id・URL は変えていない

## 残したもの

- check_pages の警告は行の最初のリンクだけを見る。「- [A](u1)・[B](u2)」の 2 つ目も集めると、cpp-string-api のような違いも拾える（道具の改め。メインの判断）
- trap.jp の判断
