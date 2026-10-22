# zeta-mobius-divisor の問題の補充（b6・工程9）

- ページ：docs/comb/zeta-mobius-divisor.md（レベル 青）。今の練習は abc393_e（diff 1253）の 1 問、例題は abc474_f、力試しは agc038_c
- 探したところ：(1) b2 の報告 planning/batches/b2/zeta-mobius-divisor.md の「問題の補充の候補」に arc185_e・abc349_f（b3 summary/candidates.md にも同じ記載。b1 の candidates.md は abc393_e の台帳の行だけ、b5 の candidates.md には記載なし）。(2) data/problems.yaml で pages に zeta-mobius-divisor を持つ問題は abc393_e・abc474_f・agc038_c の 3 問で、どれも本文にある（本文にない問題はない）。(3) 第三者の解説（aprilganmo のゼータ変換の記事・drken の「添字GCD畳み込み」カテゴリー）から yahoo_procon2018_final_a を新たに見つけた。ap.py の題名検索（GCD・LCM・Divisor・Multiple・Coprime・Prime、diff 1300〜2500）も見直した
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補は 2 問。yahoo_procon2018_final_a を練習に足すと練習は合わせて 2 問になる。arc185_e は力試しの候補（練習に置けば 3 問）

## 候補

### yahoo_procon2018_final_a（新規。台帳になし）

- 問題ID：yahoo_procon2018_final_a（コンテストは yahoo-procon2018-final。オープン版 yahoo-procon2018-final-open も同じ問題 ID）
- 題名：A. Uncommon
- difficulty：なし（AtCoder Problems に値なし。600 点）
- 役割：practice
- 要約：相異なる N 個の整数 a_1, …, a_N（値は 10^5 以下）と M が与えられ、i = 1, …, M のそれぞれについて i と互いに素な a_j の個数を求める。
- 方針の要点：値ごとの個数を倍数ゼータ変換して d の倍数の個数 C(d) を作り、δ_1 の約数メビウス変換（メビウス関数 μ）と点ごとに掛けた μ(d)·C(d) を約数ゼータ変換すると、i の位置に Σ_{d|i} μ(d) C(d) ＝ 答えが並び、全体 O(A log log A) で済む（gcd 畳み込みの第 1 成分を全 i について一度に出す形）。素因数ごとの包除（各 i で 2^6 通り）でも解ける。
- 裏付け：
    - https://noshi91.hatenablog.com/entry/2020/01/15/185642 （cnt の倍数ゼータ・δ_1 の約数メビウス・点ごとの積・約数ゼータの順で答えのベクトルを作り、Θ(A log log A) になることを確かめた。noshi91 は付録 B にある）
    - https://drken1215.hatenablog.com/entry/2018/07/12/213300 （問い・制約 N, M, a_i ≤ 10^5 と、素因数の包除で解く別解。添字 GCD 畳み込みで O(N log log N) の方法として上の記事を挙げている）
    - 補足：https://aprilganmo.hatenablog.com/entry/2020/07/24/190816 も gcd 畳み込みの応用としてこの問題を挙げる。aprilganmo.hatenablog.com は付録 B にないので check_noai で確かめた（X-Robots-Tag なし、meta robots="max-image-preview:large"、noai・noimageai の指定なし）。付録 B への追加を提案する
- 台帳への追加の提案：pages に {id: zeta-mobius-divisor, role: practice}。素因数ごとの包除でも解けるので divisor-inclusion-exclusion か mobius-function の practice にも向くが、そちらは確かめていない

### arc185_e（b2 の候補。台帳になし）

- 問題ID：arc185_e
- 題名：E. Adjacent GCD
- difficulty：2185（黄）
- 役割：challenge（青の帯の上端 1999 を 190 ほど超える。練習が足りないときは practice に置いてもよい）
- 要約：長さ N の列 A の各接頭辞 A_1, …, A_M（M = 1, …, N）について、空でない部分列 2^M − 1 通りすべての「隣り合う要素の gcd の和」の総和を 998244353 で割った余りで求める。
- 方針の要点：答えは f(n+1) = 2f(n) + Σ_{x<n} 2^x·gcd(A_x, A_n) と更新でき、gcd(a, b) = Σ_{d | gcd(a, b)} φ(d)（φ は恒等関数 n の約数メビウス変換）と分けて、d ごとに「d の倍数である過去の要素の 2^x の和」を持てば、A_n の約数を回すだけで更新できる。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2024/10/19/0900 （上の漸化式、φ による分解、d ごとの 2^i の和を持つ更新を確かめた。作者は本番では約数の包除で係数を作り、φ の方が見通しがよいと書いている）
    - 2 件目は見つからなかった（Web 検索 2 回で第三者の解説が出なかった）

## 除いたもの

- abc393_e（練習）・abc474_f（例題）・agc038_c（力試し）：本文に既にある
- abc349_f（Subsequence LCM、diff 2169）：b2 の候補。部分集合のゼータ変換が主役で、b3 の集約で zeta-mobius-subset の練習に割り当て済み。本文の vs-subset の節で型だけ触れているので、このページの練習には足さない
- abc162_e（1662）・abc206_e（1745）：divisor-inclusion-exclusion の例題で、本文ではリンクで触れている
- abc170_d（1033）・abc172_d（963）・abc106_b（122）：aprilganmo の記事がゼータ変換で解く例に挙げるが、帯（青）から離れて易しく、倍数を回す素朴な方法で足りる（abc170_d は台帳で別ページの扱い）
- abc020_d（LCM Rush、diff 2695 参考値）：約数に限ったメビウス変換で解けるが、帯から離れすぎる
- yurufuwa_onsite_07_g（FORCIA #7 G. Dot Product Query）：drken の記事が gcd 畳み込みを 6〜8 回繰り返す解法を書くが、ap.py に見つからない（AtCoder Problems に載っていない）ので候補にしない
- abc445_e（Many LCMs、1337）：題名は lcm だが、ikatakos の記録では素因数ごとに指数の上位 2 つを持つ解法で、このページの手法ではない
- arc126_c（Maximize GCD、1824）・abc191_f（GCD or MIN、2333）・abc469_f（1567）：ap.py の検索に出たが、倍数ごとの累積和・約数の列挙・倍数を回す方法で解く問題として知られ、変換そのものは使わない（解説を開いて確かめてはいない）

## 本文に足すときのメモ

- 練習の並びは abc393_e（1253）→ yahoo_procon2018_final_a（diff なし）が自然。abc393_e は「倍数ゼータ → max の約数ゼータ」、Uncommon は「倍数ゼータ → μ を掛ける → 約数ゼータ」で、gcd-lcm-convolution の節の GCD 畳み込みを 1 成分だけ取り出す形の練習になる
- 力試しを 2 問にするなら agc038_c（2327）の前に arc185_e（2185）を置く。φ が「恒等関数の約数メビウス変換」であることは euler-phi のページへのリンクで補う
