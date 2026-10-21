# mobius-function の報告（b3）

- 書いたファイル：docs/comb/mobius-function.md、snippets/mobius-function/coprime-pairs.{cpp,yaml}（範囲 sieve・coprime・quotient）、snippets/mobius-function/lcm-sum.{cpp,yaml}（範囲 core）、docs/img/mobius-function/divisors-of-12.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない（骨格の title のまま）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 0 行。check_snippets 2 本とも期待どおり。textlint エラー 0、警告 16（数式を含む文の長さ・数式の中の読点・数式のブロック・fix_problems が作る問題の行の長さ。どれも §13-8・§14-25 で許された種類）
- 図：divisors-of-12.svg を render_svg.py で 360px・720px にして目で確かめた。360px では右の説明の文字が小さいが、同じことを本文に文章で書いている
- 動く図：catalog の visual は null なので作っていない
- 使った出典：drken の Qiita（篩の活用法。μ の定義・篩・倍数の形の反転）、drken の AGC038 C・AGC039 C、kmjp の ABC230 G、Kodaman の scrapbox（ABC230 G）
- 新しく noai を確かめたドメイン：scrapbox.io/Kodaman（指定なし）、tsutaj.hatenablog.com（指定なし。補充の候補の裏付けに読んだ）、geam1113.hatenablog.com（指定なし。G の記述がなく使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| agc039_c | summary | N 桁の 2 進数で与えられる X 以下の各整数 k について、「奇数なら 1 引いて 2 で割り、偶数なら 2 で割って 2^(N−1) を足す」操作を何回で k に戻るかを求め、その総和を求める。 | https://drken1215.hatenablog.com/entry/2020/11/11/035400 |
| agc039_c | approach | k と bit を反転した列をつないだ 2N bit の巡回シフトとみて、N/d が奇数の約数 d ごとに周期が 2d の約数になる k を数え、約数の周期の分を引いて（メビウス反転）2d を掛けて足す | 同上 |
| abc230_g | summary | 「組 (i, j)」を「1 ≤ i ≤ j ≤ N の組 (i, j)」にする（未解決の点を参照。確かめられたら） | https://kmjp.hatenablog.jp/entry/2021/12/08/1000 |
| abc230_g | evidence | Kodaman の scrapbox を 2 件目に足す | https://scrapbox.io/Kodaman/ABC230_-_G._GCD_Permutation_(600) |
| agc038_c | approach（mobius-function の側） | 1/gcd を約数の和 Σ_{t \| gcd} w(t)（w は 1/n のメビウス反転）に直し、t ごとに「t の倍数の和」の 2 乗を足す。今の「メビウス変換で gcd がちょうど g の分を取り出す」も誤りではないが、本文は w の形で書いた | https://drken1215.hatenablog.com/entry/2020/11/06/031600 |

## 用語集への提案

- メルテンス関数｜mertens-function｜メビウス関数の累積和 M(N) = μ(1) + … + μ(N)。N が大きいときは篩を使わず、商の値だけの再帰（杜教篩）で O(N^{2/3}) で求める（本文では用語集へリンクしていない。multiplicative-function のページで使うなら）
- [P]（アイバーソンの記法）は start/notation.md に載っていない。binomial-identities・convolution-ntt・sigma-manipulation・このページが「記法と用語の約束」へリンクして使っているので、notation に 1 行足すとよい

## 手引きへの提案

- §5 comb に「メビウス関数の篩は、符号の反転を p の倍数すべて（p 自身を含む）に行い、0 にするのだけを p^2 の倍数にする」を足すとよい（sieve-eratosthenes の変形の節と同じ落とし穴）
- 表の列は 4〜5 までの決まりで、μ(1..12) のような値の一覧は表にできない。数式の 1 行（μ(1), …, μ(12) = …）で書いた。一覧は数式で書いてよいと明記するとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- |
| abc020_d（LCM Rush、diff 2695 参考値） | 1 ≤ i ≤ N についての lcm(i, K) の総和を求める（N, K ≤ 10^9、mod 10^9+7） | gcd(i, K) = x ごとに分け、i' ≤ ⌊N/x⌋ で K/x と互いに素な i' の和を、K/x の素因数の部分集合（μ(d) ≠ 0 の約数）について足し引きする。本文の gcd-one の節の「ある数と互いに素な数の和」の型そのもので、ID を出さずに書いた。力試し（発展）の候補 | https://tsutaj.hatenablog.com/entry/2017/07/01/073648 |
| arc185_e（Adjacent GCD、diff 2185） | 列の各接頭辞について、空でない部分列すべての「隣り合う要素の gcd の和」の総和を求める | gcd = Σ_{d \| gcd} φ(d) と置き換え、d の倍数ごとに 2^i の和を持って更新する。b2 の zeta-mobius-divisor の報告と同じ候補。このページの練習（黄）に向く | https://kmjp.hatenablog.jp/entry/2024/10/19/0900 |
| abc248_g（GCD cost on the tree、diff 2514） | 木の全パスについて、パス上の頂点の値の gcd × 頂点数の総和を求める（未確認。解説を読んでいない） | d の倍数の頂点だけの森でパスの頂点数の和を数え、φ か約数包除で gcd ごとに直す型と思われる。執筆者は未確認なので、台帳に入れる前に第三者の解説で確かめる | （未確認） |

- 練習が agc039_c の 1 問だけで、ABC の黄の帯で μ を直接使う問題は見つからなかった（ap.py の題名検索で GCD・Coprime・LCM・Prime の 1800〜2800 を見た）。abc195_f（Coprime Present）・abc263_g は題名に合うが、bitDP・二部マッチングの問題で μ ではない（記憶による見当で、確かめていない）

## 未解決の点

- abc230_g が i ≤ j（i = j を含む）か i < j かを確かめきれなかった。kmjp の式は c(c+1)/2（i ≤ j）で、Kodaman は順序対の c^2 で書いている。検索結果の要約では ikatakos の記録が「1 ≤ i ≤ j ≤ N」としているが、ikatakos は問題文を引用した節を読まない約束なので読んでいない。本文の力試しの方針では「問題文で確かめる」と書いた。台帳の summary を確定させたら、方針の最後の文を直すとよい
- abc230_g の N の上限も確かめていない（方針では「値が 2×10^5 程度なら」と条件付きで書いた）
- agc039_c の方針は drken の記事（WebFetch の要約）だけで確かめた。周期の集合の包含（d | d' で d'/d が奇数）は自分で導いた部分がある
- 発展の節の「杜教篩で O(N^{2/3})」は記憶による一般的な事実で、この作業では出典を読んでいない。multiplicative-function の執筆で確かめるとよい

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 7 回（WebFetch 6・WebSearch 2）

## 検証の指摘への対応（2026-10-21）

- 直すべき 3 件（1〜3）・直すとよい 6 件（4〜9）をすべて直した。採らなかったものはない
    - 1：値の上限を V に分け、complexity と要点を同じ文にそろえた（篩・gcd の関数の和・約数包除の表・AGC038 C・使い分けも V）。コード片の篩の引数を v、lcm-sum.cpp の M を V にした
    - 2：ABC230 G は 1 ≤ i ≤ j ≤ N と言い切り、c(c + 1)/2・N ≤ 2×10^5・約 63 N log N を書いた
    - 3：ν の定義を gcd-one の節の「応用の型」に「gcd が 1 でない組」として出し、確認問題は #quiz に移して N = 4 で手を動かす形にした。落とし穴と力試しのリンクは #gcd-one（その箇条）へ
    - 6：図は右側の説明を消して viewBox を 480 × 340 にし、縦の軸に 3⁰・3¹、下に凡例と和の式を置いた。360px の PNG で読めることを確かめた
- 上の「未解決の点」のうち abc230_g の i ≤ j と N の上限は、検証で確かめられたので解決した

## 台帳への提案（検証を受けて確定）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc230_g | summary | 1〜N の順列 P について、1 ≤ i ≤ j ≤ N・gcd(i, j) ≠ 1・gcd(P_i, P_j) ≠ 1 をすべて満たす組 (i, j) の数を求める。 | https://kmjp.hatenablog.jp/entry/2021/12/08/1000 |
| abc230_g | checked | 2026-10-21 | 同上 |
| agc038_c | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2020/11/06/031600 |
| agc039_c | summary | 「X 以下の各整数 k」を「X 以下の各非負整数 k」にする（0 を含むことをはっきりさせる） | https://drken1215.hatenablog.com/entry/2020/11/11/035400 |
| agc039_c | checked | 2026-10-21 | 同上 |

- 本文の abc230_g の一覧の行（台帳の summary から出る）は、台帳を直した後に gen_site で 1 ≤ i ≤ j ≤ N の形になる
