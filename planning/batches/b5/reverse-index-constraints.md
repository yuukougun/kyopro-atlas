# reverse-index-constraints の報告（b5）

- 書いたファイル：docs/guide/reverse-index-constraints.md、snippets/reverse-index-constraints/ops-benchmark.{cpp,yaml}、docs/img/reverse-index-constraints/max-n-per-class.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 生成ブロック signs-constraint：中身は変えず、ブロックごと「制約の帯ごとの候補のページ」の見出しの下へ移した（骨格では要点の直後にあった）。gen_site.py は実行していない
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 期待と違う 0、textlint エラー 0・警告 5（助詞の重複 4 と、表の行の長さ 1。表の行と、言い換えると不自然になる箇所なので残した）
- 図：max-n-per-class.svg（幅 400）を render_svg.py で 360px・720px にして目で確かめた
- 問題：catalog の problems が空で、guide は問題を持たないので載せていない
- 新しく noai を確かめたドメイン：algo-logic.info・motsu-xe.hatenablog.com・note.com/irinote（どれも指定なし。note.com の irinote の記事は資料として読んでいないので出典に入れていない）

## 台帳への提案

- なし（このページは問題を持たない）

## 用語集への提案

- なし（本文で用語集へのリンクは張っていない）

## 手引きへの提案

- 「1 秒あたりの演算回数」の手元の実測（ops-per-second の表）を、ほかのページで定数倍を書くときの共通の値として付録に置くとよい。測定：g++-15（15.2）・`-std=gnu++23 -O2`、Intel Core i7-13700・WSL2。依存のある掛け算と足し算 10^8 回 0.08 秒、32 MiB の配列を順に読む 10^8 回 0.03 秒、同じ配列を乱数の位置で読む 10^8 回 0.44〜0.51 秒、set の挿入と lower_bound 各 10^6 回 0.34 秒（3 回ずつ測った）。読む位置が直前に読んだ値で決まる（依存のある）乱数の読み出しは 10^8 回で約 7 秒だった（本文には載せていない）
- §5 basics の「計算量の目安の数値は complexity-estimation の値にそろえる」に、reverse-index-constraints#magnitudes も同じ値（log₂(2×10^5) ≈ 17.6、N log N ≈ 3.5×10^6、N log² N ≈ 6.2×10^7、N√N ≈ 8.9×10^7）だと添えるとよい

## front matter・catalog への提案

- 生成ブロックの位置：骨格では signs-constraint のブロックが要点の直後に置かれていた。gen_site の骨格の生成で、ブロックを sections の pages-by-constraint の位置に置くようにするとよい（今回は手で移した）
- related に method-comparison（使い分け）と cpp-container-idioms#member-lower-bound を足すとよい（本文の「見た目より遅い」から参照している）

## 生成ブロックについて気づいた点（gen_site・各ページの signs への提案）

- 「上限が 10 以下」の帯に complexity-estimation の「N ≤ 8 / 20 / 40 / … / 10^18 のような制約の大きさ」が入っている。帯に分けられないので「数の上限で分けられないもの」へ回すのが自然（最初の数で分けているように見える）
- 「上限が 10^12 以下」の帯に、状態数 10^6〜10^7（extended-dijkstra）、NW ≤ 10^7〜10^8（knapsack-01）、O(N√N) ≈ 10^8（sqrt-decomposition）、−10^9 ≤ A_i（prefix-sum-counting）、W ≤ 10^9（dp-dimension-reduction）などが入っており、帯の意味（N の上限）とずれている。サインの最大の数で分けているためと思われる。N（列の長さ・回数）の上限の数で分けるか、値の上限のサインは「数の上限で分けられないもの」へ回す規則にするとよい
- 「上限が 500 以下」の帯の matrix-power（状態数 ≤ 100、K が 10^9〜10^18）も同じで、10^18 の帯の方が引かれやすい
- 「上限が 2×10^5 前後」の multiplicative-order（法 P が 10^9、√P ≈ 3×10^4）も同じ

## 問題の補充の候補

- なし（guide は問題を持たない）

## 未解決の点

- AtCoder の C++ の環境（C++23 (GCC 15.2.0)・`-O2 -march=native` など）は planning/decisions.md の記録に従って書いた。一次資料（言語一覧）は img.atcoder.jp にあり、atcoder.jp のサブドメインなので開いておらず、出典にも入れていない。cpp-environment のページが書かれたら、そちらへの節リンクに張り替える（今は stub なのでページへのリンク）
- 手元の実測は AtCoder の判定機と CPU が違う。AtCoder のコードテストで同じコード片を測れば判定機での値が分かるが、AI では行っていない。ユーザーが測る場合は ops-benchmark.cpp に n = 100000000 を与えればよい
- 「ABC の多くは実行時間制限 2 秒」は確かめられなかったので書いていない（制限は問題文で確かめると書いた）
- cheatsheet#complexity-and-constraints（related にある）は stub なので本文からはリンクしていない。cheatsheet を書くときは、1 秒の目安と N = 2×10^5 の量をこのページと同じ値にそろえ、相互にリンクする

## 検証の指摘への対応

- 直した：1（確認問題の `set` の操作を約 6×10^6 回に直し、木の中の比較の回数と分けた）、2（キャッシュに収まらない大きさという条件を足した）、3（濃い棒と破線の棒をそれぞれ説明）、4（何の回数かを明示）、5（題と問いを「表から秒数を見積もる」に寄せた）、6（帯の分け方の規則を gen_site の実装どおりに書いた）、7（取り込みの範囲の先頭に `timed` の説明のコメントを 1 行足した）、8（周期性の検出に「状態の種類が少ないとき」を添えた）、9（このページを「N ≤ 15〜16 程度」にした）、10（`-march=native` を付けていないことと、付けても同じことを添えた）
- 採らなかったもの：なし
- 提案（共有ファイル）：complexity-estimation の constraint-table の「3^N は N ≤ 15 程度」は、このページの「15〜16 程度」と矛盾しない範囲だが、2 ページでそろえるなら complexity-estimation 側も「15〜16 程度」にするとよい（担当外なので書いていない）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 期待と違う 0、textlint エラー 0・警告 5（前と同じ）
