# divisor-enum の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/math/divisor-enum.md、snippets/divisor-enum/divisors.{cpp,yaml}（core の範囲は prime と divisors の 2 つ）、docs/img/divisor-enum/pairs.svg（静的な図。visual は priority 2・static なので動く図は置かない）
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（pitfalls は骨格の title のまま見出しにした。ほかの執筆者と同じ扱い）
- 検査の結果：check_pages --page divisor-enum はエラー 0・警告 0。fix_problems --check はこのページで直す行 0（全体の 5 行は math/sieve-eratosthenes.md で、別の執筆者のページ）。check_snippets は期待と違う 0。textlint はエラー 0・警告 10（数式を含む文の長さ・読点の数、要点の「何ができるか」の「に」の重なり（summary の文のまま）、問題の行と出典の行の長さ。誤検出として残した）
- 使った事実の確かめ方：10^9 以下で始まる隣り合う素数の差の最大 282（436273009 の後）は篩を書いて計算した。`(long long)sqrt(10^16 − 1)` が 10^8 を返すこと、46340² = 2147395600、3037000499² < 2^63 − 1 < 3037000500²、d(735134400) = 1344、σ(36) = 91 は Python で確かめた。約数の個数の最大（10^9 で 1344、10^12 で 6720）は research/06 §6.3 の表による

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc112_d | summary | 「全ての要素の」→「すべての要素の」（prh のエラー。本文の行は手で直した） | 手引き §7（ひらがなで書く語） |
| diverta2019_d | summary | 「全て求め」→「すべて求め」（同上） | 手引き §7 |

- fix_problems が作る diverta2019_d の label は「DIVERTA2019 D. DivRem Number」になる（contest id を大文字にする規則）。読みやすさのため、interfaces.md §3 の表示名に diverta2019 → 「diverta 2019」などを足すかはメインで決めてほしい（今回は規則どおり DIVERTA2019 にした）

## 用語集への提案

- なし（用語集へのリンクは使っていない）

## 手引きへの提案

- 骨格の sections に `anchor: pitfalls` が長い title で入っている件（§13.1 との食い違い）は、ほかの執筆者の報告と同じ。今回も §13.2 に従い title と見出しを一致させた
- 台帳の summary の「全て」が本文の行で prh のエラーになる。台帳の summary を一括で textlint にかけるとよい（ext-gcd の報告と同じ論点）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc180_c | N の約数をすべて小さい順に出力する（√N までのループで i と N/i を集めてソート）。台帳では確認済みで divisors-and-multiples の練習 | 練習（diff 142。列挙とソートの最初の 1 問） | https://drken1215.hatenablog.com/entry/2020/10/21/194700 （台帳の evidence） |
| typical90_cg | a ≤ b ≤ c、abc = K（K ≤ 10^12）の組の数。約数の組を全部試す。台帳では確認済みで divisor-count-bound の練習 | 練習（本文の「積が N になる組」の 3 数の型の代表） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/085.cpp （台帳の evidence） |
| abc420_g | n² + n + X が平方数となる整数 n をすべて求める（4X − 1 を 2 数の積に分ける約数の列挙） | 練習（diff 1427、abc319 以降） | research/06 §5.3 では usaco.guide の練習問題の一覧でだけ確認（状態はタグ）。第三者の解説では未確認で、台帳に入れる前に確かめが要る |

## 未解決の点

- 例題・練習の問いは drken 氏の記事 5 件で確かめた。diverta2019_d の「和を出力」は記事の解法（(N − r)/r を足し合わせる）から判断した
- 落とし穴の「$2^{52}$ 程度を超えると」は、$m^2 - 1$ の形で `(long long)sqrt` がずれ始める最小の $m$ が $2^{26} + 1$ 付近（$N \approx 4.5 \times 10^{15}$）であることを Python の double で確かめた。$N = 10^{16} - 1$ で `(long long)sqrt(n)` が $10^8$ を返すことは g++ でも実行して確かめた
- 図 pairs.svg は SVG を画像にする道具がなく、座標の計算だけで配置を確かめた（文字と線の重なりがないかは検証役に目で見てほしい）
- related の divisors-and-multiples#enumerate と brute-force へは本文でリンクしていない（使い分けの節に入る場面がなかった）

## 使った出典

- drken「AtCoder ABC 112 D - Partition (2Q, 緑色, 400 点)」https://drken1215.hatenablog.com/entry/2018/11/06/120600
- drken「AtCoder ABC 149 C - Next Prime (5Q, 灰色, 300 点)」https://drken1215.hatenablog.com/entry/2020/01/02/112800
- drken「AtCoder ABC 057 C - Digits in Multiplication (4Q, 緑色, 300 点)」https://drken1215.hatenablog.com/entry/2019/09/16/221500
- drken「diverta 2019 D - DivRem Number (2Q, 緑色, 500 点)」https://drken1215.hatenablog.com/entry/2019/05/12/004500
- drken「AtCoder ABC 161 F - Division or Substraction (1D, 水色, 600 点)」https://drken1215.hatenablog.com/entry/2020/04/04/224500
- planning/research/06-math-nt.md §4.3・§5.3・§6.2・§6.3
- 新しく noai を確かめたドメイン：なし（すべて付録 B の drken1215.hatenablog.com）

## 使用量の目安

- 道具の呼び出し 約 30 回、Web 取得 5 回（＋題名の確認に curl 5 回）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜7 はすべて採った（直すべき 1 件・直すとよい 6 件）。採らなかったものはない
    - 指摘 3：要点の計算量を $O(d(N) \log d(N))$ に直し、front matter の complexity も `O(d(N) log d(N))（d(N) は約数の個数）` に直した（complexity は執筆者が直してよい項目）
    - 指摘 4：「篩で計算して確かめた」を消し、「（$436273009$ と次の素数の差）」だけにした
    - 指摘 5：pairs.svg の √36 = 6 の点線を 6 の枠の中央（x = 520）に移し、枠の背面に置いた
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 期待と違う 0、textlint エラー 0（警告 10 は直す前と同じ種類）

### 提案（メイン向け、検証の提案の再掲）

- 台帳：abc112_d・abc149_c・abc057_c・diverta2019_d・abc161_f の `checked` に 2026-10-21。abc112_d・diverta2019_d の summary の「全て」→「すべて」
