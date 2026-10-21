# divisor-inclusion-exclusion の報告（b2）

- 書いたファイル：docs/comb/divisor-inclusion-exclusion.md、snippets/divisor-inclusion-exclusion/{subset-gcd,perfect-powers}.{cpp,yaml}、docs/img/divisor-inclusion-exclusion/subtract-multiples.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の order の title を「大きい g から引く理由と計算量 O(M log M)」に変えた（anchor は同じ。値の上限を M と書くため）
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行 0）、check_snippets（2 件とも一致）、textlint（エラー0、警告14：数式を含む文の長さ・読点の数）。SVG は render_svg.py の 360・720 の幅で目視した
- 使った出典：kmjp（abc162_e）、drken（abc206_e・abc361_f・abc304_f）。どれも付録 B のドメイン。新しいドメインなし（候補の裏付けに www.cnblogs.com・merom686.hatenablog.com の検索結果を使った。どちらも付録 B にある）
- 動く図：catalog の visual は priority 2（static）なので静的な SVG で代えた。動く図の div は置いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc304_f | summary | 「.」と「#」の予定表 S に対し、N 未満の N の約数 M を周期に持ち、条件を満たすシフト表の数を mod 998244353 で求める。（現状の「N の約数 M を周期に持つ…」は M が N 未満であることが抜けている。問題文の細部は解説で確かめきれていないので、文言はメインが整える） | https://drken1215.hatenablog.com/entry/2023/06/07/153403 |
| abc361_f | alternatives の approach（divisor-inclusion-exclusion） | 指数 b ごとに ⌊N^(1/b)⌋ − 1 を求め、最大の指数がちょうど b のものを大きい b から倍数の指数の分を引いて求める | 同上 drken（解説は素数の指数の包除。本文はそれを指数の倍数関係で書き直した） |

## 用語集への提案

- 原始的な文字列｜primitive-string｜自分より短いどの文字列の繰り返しでも書けない文字列。長さ N の原始的な文字列の数は、約数の周期で数えた分を引いて求まる。（本文では使っていない。kmp と共有するなら）
- 本文で使った用語集の anchor はすべて既存（disjoint・coprime・period・perfect-power）

## front matter・catalog への提案

- summary の「全体で O(N log N)」は、N が列の長さと紛れる（ABC162 E では N が列の長さで、ループは K まで）。「値の上限 M に対して全体で O(M log M)」にしたい。要点の本文はこちらで書いた
- related に string/kmp#count-periodic と math/integer-root#perfect-powers を足す（周期と累乗数の節から相互に参照している）

## 手引きへの提案

- comb：約数包除の「向き」（倍数から引くなら大きい順、約数から引くなら小さい順）と、空集合・1 のようにすべての F に入る対象を除くことを、comb の分野の注意に足すとよい（mobius-function・zeta-mobius-divisor の執筆でも同じ落とし穴が出る）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc349_f（Subsequence LCM、diff 2169） | 数列の空でない部分列のうち、lcm がちょうど M のものの数。M の約数の上で「すべて d の約数」から引く（本文の確認問題の lcm の形）。主な解説は素因数の bit の高速ゼータ変換・メビウス変換 | 力試し（あるいは zeta-mobius-subset の例題） | https://www.cnblogs.com/MoyouSayuki/p/18134468 、https://merom686.hatenablog.com/entry/2024/04/14/011833（検索結果の要約で確かめた。本文は未読） |
| arc185_e（Adjacent GCD、diff 2185） | 接頭辞ごとに、すべての部分列の隣り合う項の gcd の和の総和。gcd = Σ_{d∣gcd} φ(d) で約数ごとの和に直す | 力試し（gcd の総和は φ でも書ける の形） | https://www.cnblogs.com/georgeyucjr/p/18464435（検索結果の要約で確かめた。本文は未読） |

- abc319 以降で、約数包除を中心にする ABC は見つからなかった（ap.py で gcd・coprime・lcm・period などを検索）。abc469_f は harmonic-sum の練習にある（大きい公約数から結ぶ形で、引き算はしない）

## 未解決の点

- abc304_f の問題文の細部（どちらの文字が固定されるか）は第三者の解説の要約でしか確かめていないので、練習の方針は「決まった日が含まれるかで 1 通りか 2 通りか」とぼかして書いた
- 周期の節の巡回シフトによる証明（周期 d∣N ⇔ d 文字の巡回シフトで不変、ベズーで gcd も周期）は自分で組んだ。kmp の節は弱周期定理で書いているので、検証役に両者の整合を見てほしい
- 確認問題の lcm の形は、F(d) が lcm で排反に分かれる根拠を一文で書いただけである

## 検証の指摘への対応（2026-10-21）

- 指摘 1（summary の O(N log N)）：担当ページの front matter なので直した。「値の上限を M として O(M log M) になる」とし、check_pages の summary の長さ（120 字）に収めるため前半を少し詰めた
- 指摘 2（abc304_f の要約）：台帳の問題なので本文は触っていない。上の「台帳への提案」の summary の直しをメインが反映し、fix_problems を流してほしい（kmp の行も同時に直る）。検証役の文例「'.' と '#' からなる予定 S について、条件を満たし、N 未満の N の約数 M を周期に持つ長さ N の勤務表の数を mod 998244353 で求める。」でよい
- 指摘 3：コードのコメントを「n <= 10^18 なら 2^60 > n で指数は 59 までで足りるが、n < 2^63 まで正しいよう 62 まで回す」に、入力の範囲を「1 <= n < 2^63」に直した（kth_root の上限 3037000500 と pow_le のあふれ判定で n < 2^63 まで正しい）。2^60 の case は残した
- 指摘 4・5・6・7・10：示された直し方のとおりに直した（6 は見出し・sections の title・練習の方針のリンクの題名をそろえ、anchor は変えていない。本文で 1 回「累乗数（完全累乗）」と添えた）
- 指摘 8（図の小さい字）：灰色の F(g) の式を 12 → 13 に上げただけにした。幅を詰める・2 行を 1 行にまとめるのは採らなかった。右の列の最長の式（f(1) = 36 − 7 − … = 23）がすでに幅 720 の右端近くまであり、字を大きくすると収まらない。検証役も誤りではないとしている
- 指摘 9：本文の箇条書きの各行に句点を足した。要点の囲みと参考の行は手引きの見本どおりなので足していない

### 台帳への追加の提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc162_e・abc206_e・abc304_f・abc361_f | checked | 2026-10-21 | 検証役が参考の解説記事で問い・方針を確かめた（planning/batches/b2/verify/divisor-inclusion-exclusion.md） |
