# stern-brocot の報告（b4）

- 書いたファイル：docs/math/stern-brocot.md、snippets/stern-brocot/approx.{cpp,yaml}、docs/img/stern-brocot/tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と Library Checker, anchor: library}` を足した（§13-10 の「自作するときの要点と Library Checker の対応」の置き場）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 4（要点の囲みの文の長さ、数式を含む文の読点・助詞の重複の誤検出）
- 図：tree.svg（上から 4 段、1/1 から 3/5 への道 L・R・L を太線）。render_svg で 360px・720px を目で確かめた。visual は null なので動く図の置き場は作っていない
- 使った出典：cp-algorithms（Stern-Brocot tree and Farey sequences）、Library Checker の 2 問（judge.yosupo.jp と GitHub の task.md・info.toml で制約を確認）、Nyaan's Library、kmjp（例題）、kanpurin（典型問題メモ）。新しいドメインはない（すべて付録 B にある）
- コード片の確かめ：分子・分母 ≤ 30、x, y ≤ 60 の無作為な 3000 件を Python の全探索（fractions）と照合し、すべて一致

## 台帳への提案

- abc333_g｜evidence｜kanpurin「競技プログラミング　典型問題メモ」https://kanpurin.hatenablog.com/entry/2020/04/07/182948 を足す（Stern-Brocot 木の節に ABC333 G が挙がっている。§15-6 の 2 つ以上の目標のため。ただし解法の詳細はなく分類の裏付けだけ）

## 用語集への提案

- 中間数｜mediant｜2 つの分数 a/b と c/d に対し、分子どうし・分母どうしを足した分数 (a+c)/(b+d)。値はもとの 2 つの間にある。Stern-Brocot 木と Farey 数列はこれを挟んで作る。
- 連分数｜continued-fraction｜分数を a0 + 1/(a1 + 1/(a2 + …)) の形に表したもの。各項 a_i は分子と分母に互除法を行ったときの商の列になる。

## 手引きへの提案

- 付録 A の整数論・代数に「Stern-Brocot 木・連分数・中間数・Farey 数列・最良有理近似」を足す（ページの題名は「Stern-Brocot 木と連分数」。gcd-lcm の 166 行目のリンクの文字は「Stern–Brocot 木」とエンダッシュになっているので、§7 の ASCII のハイフンにそろえる直しも併せて提案する。gcd-lcm は担当外なので直していない）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- joisc2008_fraction（fraction. 分数 (Fraction)、diff なし）：ap.py で実在を確かめた。Farey 数列（分母が N 以下の既約分数の列）の列挙に関わる問題と思われるが、第三者の解説が見つからず、問いを確かめられていない。裏付けなし（未確認のまま。練習にするなら解説を探す）
- arc192_d（D. Fraction Line、diff 2722）：題名だけで分数を扱うと分かる。内容は未確認で、Stern-Brocot 木と関係があるかも分からない（候補として挙げるだけ）

## 未解決の点

- 例題の制約（N の上限・r の桁数）は atcoder.jp を開けないので確かめていない。本文では「たとえば y = 10^18、N = 10^10 なら」と仮の値として書き、例題の節では具体的な上限を書いていない。近さが等しいときの扱いも「問題の指定に従う」とした（kmjp 氏のコードは小さい方を出す）
- 「判定だけで二分探索するときの判定の回数 O(log N)」は cp-algorithms の O(log(p+q)) の主張に拠った（自分では証明を書いていない）
- 作業中に front matter を書き換えるスクリプトの誤りで担当ページを一度空にしたが、git の HEAD の骨格から作り直した（ほかのファイルには触れていない）

## 検証の指摘への対応（2026-10-22）

- 直したもの：1（`i128` の別名を消し `__int128` と書いた）、2（Farey 数列の両端を $0/1$ と $1/1$ に）、3（「1 回ずつ現れる」の理由に $p \ge a + c$・$q \ge b + d$ を書いた）、4（LCA の取り方）、5（コード片のコメントを本文の記号に）、6（「128bit」を「128 bit」に。complexity・節の題名・見出し）、7（近さが等しいとき、参考にした解答は小さい方の $L$ を出すことを添えた）
- 採らなかったもの：なし

## 提案（検証の指摘から）

- サイト全体で「128bit」と「128 bit」が揺れている（検証役の数えで 10 対 9）。prh.yml か手引きで「128 bit」（数字と単位の間に空白）にそろえることを提案する
- abc333_g：検証役が kmjp 氏の記事で問いと解き方を確かめたので、台帳に `checked: 2026-10-22` を入れてよい（evidence への kanpurin 氏の記事の追加の提案も併せて）
