# euler-phi（黄・technique）の報告と提案

- 書いたファイル：docs/math/euler-phi.md、snippets/euler-phi/phi.{cpp,yaml}（範囲 single・sieve）、snippets/euler-phi/power-pair.{cpp,yaml}（範囲 core）、docs/img/euler-phi/coprime-to-12.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を 3 つ直した（anchor はそのまま）
  - sieve：「全て」→「すべて」（§7 のひらがなの語）
  - euler-theorem：「…指数の mod への応用」→「…位数・指数の mod への応用」（節で位数が φ の約数になることを主に書いたため）
  - divisor-sum：`Σ_{d|n} φ(d) = n と「位数が d の元は φ(d) 個」` → 「約数についての φ の和が n になることと、位数が d の元が φ(d) 個あること」（見出しに `{` `}` `|` を書くと attr_list と表の記号に紛れるため言葉にした）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致、textlint エラー 0（警告 12 はすべて数式を含む文の長さと数式の中の読点）
- 図：coprime-to-12.svg（catalog の visual priority 2 の静的な図）。render_svg.py で 360・720 の幅を目で確かめた。動く図は作っていない
- 使った出典：drken の Qiita 3 本（付録 B）、drken1215.hatenablog.com（abc212_g）、kazun-kyopro.hatenablog.com（abc222_g）、kmjp.hatenablog.jp（arc185_e の候補の確認）。新しいドメインはない

## 台帳への提案

- abc212_g｜summary｜「…ものの個数を 998244353 で割った余りを求める（P ≤ 10^12）。」と、余りで答えることを足す｜https://drken1215.hatenablog.com/entry/2021/08/01/163600 （本文では例題の囲みの後に「答えは 998244353 で割った余りを出力する」と補った）
- abc162_e｜pages に {id: euler-phi, role: practice} を足す｜gcd = Σ_{d | gcd} φ(d) から、答えは Σ_d φ(d) ⌊K/d⌋^N の 1 本の和になる。本ページの divisor-sum の節の「gcd を約数の和に分ける」の練習。例題は divisor-inclusion-exclusion のままでよい。φ の式は divisor-inclusion-exclusion の gcd-sum の節の tip にも書かれている（裏付けは恒等式そのもの。台帳の evidence は https://kmjp.hatenablog.jp/entry/2020/04/12/1000）
- arc185_e（新規、diff 2185 黄）｜本ページの力試し｜下の「問題の補充の候補」

## 用語集への提案

- 位数｜multiplicative-order｜整数 $a$ と法 $n$ が互いに素なとき、$a^k \equiv 1 \pmod{n}$ となる最小の正の整数 $k$。$a^m \equiv 1$ となる $m$ はちょうど位数の倍数で、位数は $\varphi(n)$ の約数である。（ページ multiplicative-order があるので、用語集に置かずページへのリンクで足りるならそれでよい）
- 既約分数｜reduced-fraction｜分子と分母が互いに素な分数。分母が $d$ で $0$ より大きく $1$ 以下の既約分数は $\varphi(d)$ 個ある。（本文ではリンクしていない。必要なら）

## 手引きへの提案

- §2.3 または §14-12：見出しと sections の title に `{` `}` `|`（数式の添字の `Σ_{d|n}` など）を書かない、を足すとよい。attr_list の `{#anchor}` と紛れるおそれがある。catalog の title にこの形が残っているページがほかにもあるかもしれない

## 問題の補充の候補

| 問題 ID | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- |
| arc185_e（ARC185 E. Adjacent GCD、diff 2185） | 列の各接頭辞について、空でない部分列すべての「隣り合う要素の gcd の和」の総和を求める | gcd(a, b) = Σ_{d \| a, d \| b} φ(d) に分け、d ごとに「d の倍数の要素の 2^i の和」を持って更新する。本ページの力試し（divisor-sum の節） | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 （φ で書いた方針と、約数包除でも解けること） |
| abc162_e（台帳にあり） | 1..K の長さ N の列すべての gcd の総和 | Σ_d φ(d) ⌊K/d⌋^N | 上の台帳への提案 |

- b2 の zeta-mobius-divisor の報告でも arc185_e が「mobius-function・euler-phi の練習」として挙がっている。役割はメインが決める
- 確かめたが入れなかった：abc335_g（Discrete Logarithm Problems、diff 2614 発展）は位数を P − 1 の約数から求める問題で、multiplicative-order の側の問題（第三者の解説での確認はしていない）

## 未解決の点

- divisor-sum の節の「位数が d の元は φ(d) 個」は、multiplicative-order の sections の count-by-order と中身が重なる。本ページに証明（ψ(d) ≤ φ(d) と和の比較）を置いたので、multiplicative-order 側はこの節へのリンクで済ませられる。どちらを持ち主にするかはメインが決める
- 指数の mod（互いに素でないときの一般化と累乗の塔）は exponent-mod#euler-theorem を持ち主とみなし、本ページではリンクだけにした（§5 math の「持ち主は 1 つ」）
- 練習が abc222_g の 1 問だけで、§10 の目安（練習 2〜6）に届かない。上の補充の候補で 2〜3 問になる
- spf-sieve の検証役の指摘（青の節 linear-sieve が黄のページの定義を前提にしている）は、本ページが draft になったので、spf-sieve の節から euler-phi#formula へ張り替えられる
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 5 回

## 検証の指摘への対応（verify/euler-phi.md）

- 1（線形篩との速さ）：直した。「上の篩は 0.2 秒ほどで終わるので」と絶対の時間で言う
- 2（3 以上なら偶数）：直した。$k = n - k$ になるのは $n$ が偶数で $k = n/2$ のときだけで、$n \ge 4$ なら $\gcd(n/2, n) = n/2 \ge 2$、と書いた
- 3（res が p で割り切れる理由）：直した。「元の $n$」を補い、文を 2 つに分けて「res も p で割り切れる」まで書いた
- 4（abc212_g の試し割りが速い理由）：直した。drken 氏の解説にあるのは「間に合う」までとし、理由（素因数を除くたびに上限 $\sqrt{n}$ が下がる）は本ページの説明として分けた
- 5（図の 360px での読みやすさ）：直した。1〜12 を 6 個ずつ 2 段に並べ替えて幅を 720 → 420 にし、本文と重なる下の 3 行（包除原理の式・公式の式・注記）を外した。数字は 20px・凡例は 17px。render_svg.py の 360px で読めることを確かめた。代替テキストも図に合わせて直した
- 6（練習が 1 問）：本ページでは直さない。台帳の変更（abc162_e を practice に足す）が要るので、上の「台帳への提案」のとおりメインに任せる
- 7（位数が d の元は φ(d) 個の持ち主）：本ページでは直さない。持ち主の決定と multiplicative-order#count-by-order からのリンクの追加は担当外のページなので、メインに任せる（提案：本ページの divisor-sum を証明の持ち主とし、multiplicative-order の節から euler-phi#divisor-sum へリンクする）
