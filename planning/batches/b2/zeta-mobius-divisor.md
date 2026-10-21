# zeta-mobius-divisor の報告（b2）

- 書いたファイル：docs/comb/zeta-mobius-divisor.md、snippets/zeta-mobius-divisor/transforms.{cpp,yaml}、snippets/zeta-mobius-divisor/increment-divisors.{cpp,yaml}、docs/img/zeta-mobius-divisor/exponent-grid.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 0 行。check_snippets 2 本とも期待どおり。textlint エラー 0、警告 5（数式のブロック・数式の中のカンマ・図の代替テキスト・数式を含む箇条書き・fix_problems が作る問題の行の長さ。どれも規則の誤検出か許された種類）
- 図：exponent-grid.svg を render_svg.py で 360px・720px にして目で確かめた。360px では格子の隅の「n=…」が小さいが、本文で同じことを文章にしている
- 使った出典：noshi91（素数ごとの累積と計算量）、drken の AGC038 C（GCD 畳み込みの手順・力試しの方針と制約）、WineChord/algo（GitHub。ABC474 F の解法の部分だけ）。新しく noai を確かめたドメインはない（github.com・はてなブログの noshi91・drken1215 は付録 B にある）。www.cnblogs.com の AndrewMVP の記事と blog.csdn.net の記事は check_noai で指定なしだったが、F の解説がない・取得できない（HTTP 521）ので使っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc474_f | summary | 長さ N の列 A に、i を選んで i の約数 j すべての A_j に 1 を足す操作を何回でも行えるとき、A をすべて等しくできるか判定し、できるなら最小の操作回数を求める。 | https://github.com/WineChord/algo/blob/main/docs/daily/2026-09-14/atcoder-abc474-f.md |
| abc474_f | approach | 操作 i の回数 x_i について、目標の値 T との差 T − A_j が x の倍数ゼータになるので、x を倍数メビウス変換で T の 1 次式として求め、x_i ≥ 0 から T の範囲を出す（操作の総数は T − A_1） | 同上 |
| abc474_f | evidence | 上の WineChord の URL を足す。ikatakos.com は 2026-10-21 にメンテナンス中（HTTP 503）で読めなかった | — |
| abc474_f | catalog の approach | 「約数のゼータ変換とその逆変換（約数メビウス変換）」は向きが逆。位置 j に効くのは j の倍数の操作なので、倍数のゼータ変換とその逆変換（倍数メビウス変換）である。catalog は凍結なので台帳の approach だけ直せばよい | 同上 |

- 本文の問題の行：abc474_f は自分の要約で書いた（§14-16）。abc393_e と agc038_c は台帳の alternatives の要約のまま

## 用語集への提案

なし（「順序対」を使ったが、一般語として本文で説明なしに通ると判断した。必要なら「順序対｜ordered-pair｜(i, j) と (j, i) を別のものとして数える 2 つ組。i = j も含めることが多い」）

## 手引きへの提案

- 例題の evidence が ikatakos.com だけのとき、サイトが落ちていると問いを確かめられない。台帳の evidence には、できれば 2 つ目の出典（kmjp・GitHub の解説など）を置くとよい
- GitHub の個人の解説リポジトリには、問題文を英訳して載せたものがある（WineChord/algo など）。ikatakos と同じく「問題文の節を読まない・使わない、解法の部分だけを参照」の扱いを付録 B に書いておくとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- |
| arc185_e（Adjacent GCD、diff 2185） | 列の各接頭辞について、空でない部分列すべての「隣り合う要素の gcd の和」の総和を求める | gcd(a, b) = Σ_{d \| gcd} w(d) と約数メビウス変換の重み w（φ）に分け、d の倍数ごとに 2^i の和を持って更新する。このページの力試し（黄）か、mobius-function・euler-phi の練習 | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 |
| abc349_f（Subsequence LCM、diff 2169） | 列から部分列を選び、その lcm がちょうど M になる選び方の数を求める | M を素因数分解し、各要素を「指数が M と等しい素数の集合」の bit に潰して、部分集合のゼータ変換 → 2 の冪 → メビウス変換で数える。zeta-mobius-subset の練習（このページの vs-subset の節の型の代表）。本文では型だけを書いた | https://merom686.hatenablog.com/entry/2024/04/14/011833 |

- 練習が abc393_e の 1 問だけ（catalog の problems_note どおり）。青の帯の ABC で、素数ごとの変換か GCD 畳み込みを直接使う問題は見つからなかった（ap.py の題名検索で GCD・LCM・Divisor・Multiple の 1400〜2600 を見た）

## 未解決の点

- abc474_f の問い・制約（N ≤ 2×10^5、A_i ≤ 10^9）は WineChord の記事の 1 件だけで確かめた。ikatakos の記録が戻ったら 2 件目として確かめたい。解法は自分で総当たり（n ≤ 5・A_i ≤ 5 の乱択 400 通り）と照合した
- frequency_evidence の「古い ABC 1 問」がどれかは分からない（本文には影響しない）
- 本文で abc162_e・abc206_e（約数包除の例題）は ID を出さず、約数包除のページへのリンクで触れた（problems_note の「本文で参照する」に対応）
- 使用量の目安：道具の呼び出し 約 60 回、Web 取得 約 15 回（検索 4 回を含む）

## 検証の指摘への対応（2026-10-21）

- 直すべき：0 件。直すとよい 5 件はすべて採った
    1. 記号 $N$ の使い分け：lcm の総和の箇条を $M$ に、落とし穴の「個数の積なら要素の個数の 2 乗」「要素が 10 個でも」に直した
    2. 落とし穴の 1 つ目が確認問題 1 の答えを書いていた：具体例を消し、確認問題へのリンクにした
    3. 「格子どうしが縦に積まれる」：5 の指数という 3 つ目の軸（奥行き）の方向だと書き直した
    4. transforms.cpp のコメント：倍数ゼータを `G[d]`、GCD 畳み込みの添字を `k` にした
    5. 「コード片の main がその形である」：ページに main は見えないので消した
- 採らなかったもの：なし
- 台帳への提案（検証役の提案に同意）：abc474_f・agc038_c に `checked: 2026-10-21`。abc474_f の approach は倍数ゼータ・倍数メビウスの向きで書く
