# notation の報告と提案（b5）

- 書いたファイル：docs/start/notation.md、snippets/notation/conventions.{cpp,yaml}、docs/img/notation/half-open.svg・mod-clock.svg
- front matter で変えたもの：stage（draft）・updated（2026-10-22）。complexity は guide なので null のまま（ほかの guide のページと同じ）。sections は変えていない（13 節の anchor をすべて見出しに付けた）。定型の節 `#quiz`・`#references` を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 1 件とも期待どおり、textlint エラー 0（警告 19：多くは数式 $[l, r)$ の括弧の対の誤検出と、数式・リンクを含む文の読点の数、図の代替テキストの文の長さ）。図は render_svg.py で 360px・720px の PNG にして目で確かめた
- 構成：guide。要点（何のページか・使い方・約束の優先順位）→ 13 節（記号の意味だけを書き、使い方は draft のページの節へリンク）→ 確認問題 3（catalog の 2x ≡ 4 (mod 6)、1-indexed の閉区間の変換、(−7) mod 3 と `-7 % 3`）→ 参考。生成ブロックはない（--list-blocks に notation はない）
- 問題：載せていない（catalog の problems が空）
- 使った出典：en.cppreference.com（Arithmetic operators：整数の / は 0 の向きに切り捨て）、ja.wikipedia.org（整数の合同：一次合同式の一意な解の条件）、en.wikipedia.org（Iverson bracket）。新しいドメインはない
- 記法をそろえるために grep で数えた本文の使われ方：`\bmod` 94 ファイル・`\pmod` 41（`\mod` は 0）、`\operatorname{lcm}` 14（ほかの書き方 0）、`\binom` 93、`\mathrm{dist}` 25、`\mathrm{dep}` 18、`\mathrm{par}` 28、`\mathrm{sz}` 13、`\mathrm{lca}` 12、`\oplus` 42、`\text{ AND }` 13、`\lvert S \rvert` 37、`\deg` 8、`u \to v` 36、`\setminus` 17・`\overline{S}` 2。本文はこの多い方にそろえた

## 記法の提案のまとめ（b1 handoff §3・b2b3 handoff §3）

本文に入れたもの：

| 提案 | 入れた節 |
| --- | --- |
| パスカルの三角形の表 $\mathrm{C}[n][k]$（binomial-coefficient） | math（ページごとに定める数論の記号） |
| AND・OR は数式で `\text{ AND }`、コードの話でバッククォートの `&`（bit-operations） | sets-bits |
| 擬似コードの `\|x\|` と本文の $\lvert \cdot \rvert$（bitwise-independence） | math（名前の付いた量・表・擬似コード） |
| $\mathrm{val}$ の立体（digit-and-mod）。concat・$d(y)$ はページの冒頭の定義に任せた | math |
| $\mathrm{ord}[t]$（$\mathrm{ord}[\mathrm{in}[v]] = v$）と $\mathrm{out}[v]$ の半開区間（euler-tour） | tree |
| グリッドの (i, j) は i 行目・j 列目、di・dj（grid-graph） | indexing |
| 値の上限の文字（harmonic-sum） | numbers（下の「未解決の点」1） |
| 反転した文字列 $S^R$（lcs） | string |
| 状態ベクトルの向き（matrix-power・segment-tree-monoids） | math（行列とベクトルの向き。下の「未解決の点」2） |
| 余事象 $\overline{A}$・条件付き確率 $P(A \mid B)$（probability-basics） | probability |
| Iverson の記法 $[P]$（sigma-manipulation・mobius-function ほか 4 ページ） | math（和と積・条件の記号） |
| 量の単位（「40 MB」の空白、メモリ制限は MiB）（spf-sieve） | numbers |
| 木上の Mo の $\mathrm{ST}(v)$・$\mathrm{EN}(v)$（mo-algorithm） | tree |
| 分散 $V[X]$（expectation-of-square） | probability |
| 失敗リンクの記号 fail[v] と link(v)（string-automaton-dp） | string（どちらも同じものと書いただけ。下の「未解決の点」3） |
| 一般の二項演算の記号 ∘（subset-enumeration-dp） | math |

入れなかったもの：

- 偏角の範囲の既定 [0, 2π) と比較関数の名前（argument-sort）：幾何の章の中だけの約束なので、記法のページに置かず argument-sort に任せた。幾何のページが増えたら「幾何の記法」の節を足す案
- 差分列の添字の範囲（difference-sequence）：手引き §5 basics で $d_0, \dots, d_N$ の $N + 1$ 個と決まっている。記法のページには置かなかった
- 互換と swap の表記（permutation-parity）：置換のページ群の中でそろえる話で、記法の約束の対象外とした
- `__int128` の mulmod の置き場：手引き §15-12 で mod-pow に決まっている

## 台帳への提案

- なし（このページに載せる問題はない）

## 用語集への提案

- なし。Iverson の記法はこのページの #math に定義を置いた。用語集の「指示確率変数」（#indicator）とは、本文の probability の節で関係を 1 文で書いた

## 手引きへの提案

- §6 に足す案：「log の底は書かないが、回数の見積もりでは底 2 で数える」「2 文字以上の名前は `\mathrm`（dp だけでなく cnt・val・dist なども）」「表の値は角括弧 $\mathrm{dist}[v]$、式で決まる値は丸括弧 $\mathrm{lca}(u, v)$」「popcount は `\operatorname{popcount}`」「具体的な文字列は本文で `abc`、数式の中で `\texttt{abc}`」「量の単位は数と単位の間に空白、メモリ制限は MiB」
- §6 の「木」の行に $\mathrm{ord}[t]$ と $\mathrm{ST}(v)$・$\mathrm{EN}(v)$ を、「確率」の行に $P(A \mid B)$・$\overline{A}$・$V[X]$ を、「整数」の行に Iverson の記法 $[P]$ と $[x^n] f$ を足す案
- そろえ直しの候補：docs/basics/bit-operations.md の 39・140・196 行が `\mathrm{popcount}`、hadamard-transform・invariant は `\operatorname{popcount}`。後者が多いので bit-operations を `\operatorname` に直す案（記法のページは `\operatorname` にした）

## 問題の補充の候補

- 探していない。guide のページで、catalog の problems も空のため

## 未解決の点

1. **値の上限の文字**：手引き §6 は $M$ を辺数にしているが、harmonic-sum と divisors-and-multiples は値の上限を $M$ と書いている。記法のページでは「値の上限には決まった文字を当てず、ページの冒頭で定める（辺の出てこないページでは $M$ を使うこともある）」と今の状態に合わせて書いた。$V$ などに決めてそろえ直すかはメインが決める
2. **行列の向き**：matrix-power は縦ベクトル（$v' = Av$）、segment-tree-monoids は横ベクトル（$v \leftarrow vT$、`op(a, b) = ab`）で、どちらも理由がある。記法のページでは両方を書き「各ページの冒頭で示す」とした。dynamic-dp を書くときにどちらにそろえるかは未決のまま
3. **失敗リンクの記号**：string-automaton-dp は $\mathrm{fail}[v]$（頂点）、aho-corasick は $\mathrm{link}(v)$（節点）。記法のページでは同じものと書くだけにした。どちらかにそろえるかはメインが決める
4. **σ の重なり**：文字の種類の数 $\sigma$ と約数の和 $\sigma(n)$ が同じ文字。ページの冒頭の定義に従うと書いた
5. 「AtCoder の GCC 15.2（`-std=gnu++23`）」は cpp-environment の本文と手引き §9 によった（atcoder.jp は開いていない）
6. 使用量の目安：道具の呼び出し約 45 回、Web 取得 6 回（Wikipedia 3・cppreference 2 と存在確認）

## 検証の指摘への対応

- 指摘 1（直すべき）：$10^9 + 7$ の余りの積を「最大で $(10^9 + 6)^2 \approx 1.0 \times 10^{18}$ で、`long long` の上限 $9.2 \times 10^{18}$ に収まる」に直した
- 指摘 2：確認問題 2 を、累積和 $S_0 = 0$、$S_{i+1} = S_i + a_i$ で「$l$ 番目から $r$ 番目まで」の和を問う形に変えた（答え $S_r - S_{l-1}$、理由に $[l - 1, r)$）
- 指摘 3：確認問題 1 のヒントを「#congruence-division の条件で確かめる」にし、$x = 5$ を落とす話は答えに移した
- 指摘 4：接頭辞・接尾辞の空文字列と $S$ 自身になる場合を分けて書いた
- 指摘 5：gcd の行を「$\gcd(0, a) = a$（$a \ge 0$）」にした
- 採らなかった指摘：なし
- 再検査：check_pages エラー 0・警告 0、fix_problems 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 23：数式の括弧の対の誤検出が増えた分）
