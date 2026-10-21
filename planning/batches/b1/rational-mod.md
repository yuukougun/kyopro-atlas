# rational-mod の報告と提案（工程8b・b1）

- 書いたファイル：docs/comb/rational-mod.md、snippets/rational-mod/{dice-sum,percent,reconstruct}.{cpp,yaml}、docs/img/rational-mod/two-routes.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（6 節すべて見出しに anchor を付けた）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 7）
  - 残した警告：sentence-length 5 件（数式を含む文。52 行・206 行・214 行・220 行・221 行・233 行付近）、no-unmatched-pair 1 件（折りたたみの中の半開区間 $[t, t + T_1)$）、max-ten 1 件（参考の題名の中の読点）。どれも数式・題名による誤検出
- 動く図：catalog の visual は null。静的な SVG（分数で足してから mod に移す道と、先に移してから足す道が同じ値に着く図）を 1 枚置いた
- ACL の囲み：見出しを立てず、「途中の計算をすべて mod で行う」の節の終わりに置いた（定型の見出しに ACL がないため）
- 使った出典：drken のはてなブログ 3 本（abc323_e・abc280_e・abc300_e）、programming-hiroba（abc326_e）、ACL の document_ja/modint.md（手元の ~/lib/ac-library-master と third_party のソースで inv の assert を確認）。題名は各ページの h1 で確かめた。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc326_e | evidence | `https://programming-hiroba.com/`（サイトのトップ）を外し、`https://programming-hiroba.com/abc326-e/` だけにする | 記事そのものが裏付け |
| abc326_e | summary | N 面のサイコロを、出た目が今の値以下になるまで振り続け、今の値より大きい目が出るたびにその目に対応する給料を受け取るとき、給料の合計の期待値を mod 998244353 で求める。 | https://programming-hiroba.com/abc326-e/（「前に出た目以下になるまで振る」・出た目の給料の和）。いまの「サイコロを振って給料が決まる過程で」は問いが分からない |

ほかの使った問題（abc323_e・abc280_e・abc300_e）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- 有理数復元｜rational-reconstruction｜mod p の値 R から、R ≡ a × q^(−1) となる分子・分母の小さい分数 a/q を探すこと。|a|, q ≤ B で 2B² < p なら答えはただ 1 つ。検算に使う（本文ではリンクしていない。付けるなら rational-mod#reconstruct へ）

## 手引きへの提案

- §4 の technique の構成に「ACL では」があるが、§13.1 の定型の見出しに ACL の見出し（anchor）がない。今回は節の中に囲みだけを置いた。定型の見出しにするなら `## ACL では {#acl}` を足してほしい
- §5 comb の「mod の値は大小比較できないことに触れる」は、このページに詳しく書いた（#no-compare）。ほかの comb のページからは、rational-mod が draft になったので節へのリンクで済ませられる

## 問題の補充の候補

- 足りている（例題 1・練習 3、うち abc319 以降が 2 問：abc323_e・abc326_e）ので探していない
- #no-compare（比較は実数で、答えは mod で）の練習が台帳にない。optimal-strategy-expectation の担当が問題を探すときに、比較が要り答えを mod で出す ABC の問題があれば、このページの力試しにも足したい

## 未解決の点

- 「分母が 0 になる」節の「$N$ が $10^{18}$ まで動いて $N = 998244353$ になる」は一般論の例で、実際にこれで落ちる ABC の問題は確かめていない
- 「ACL の modint は `cout <<` に直接渡せない」は ACL v1.6 のソースに operator<< がないことによる（third_party/ac-library/atcoder/modint.hpp で確認）
- 例題の詳細の答えの範囲（$\max(0, X - T_1 + 1) \le t \le X$）は drken の解説の条件 $t + T_1 \ge X + 1$ から書いた

## 使用量の目安

- 道具の呼び出し 約 25 回、Web 取得 8 回（drken 3 本×2、programming-hiroba 2 回）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜5・7：すべて直した。指摘 7 は小さい文字を 15〜16 に上げ、縦の矢印のラベルを 1 行（a × b^(−1)・5 × 6^(−1)）にし、下の注記は「p = 998244353」だけに縮めた（「どちらの道でも同じ値」は本文と代替テキストにある）
- 指摘 2：percent.cpp は表の確率を `r` とし、`assert(r.val() != 0); mint e = 1 / r;` にした。cases は変わらず一致
- 指摘 6：台帳の直しなので、上の「台帳への提案」（abc326_e の summary と evidence）のとおりメインに頼む。あわせて abc326_e の `checked` に 2026-10-21 を入れる提案を足す
- 採らなかったもの：なし
