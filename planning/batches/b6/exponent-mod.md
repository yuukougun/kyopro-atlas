# exponent-mod の問題の補充（b6・工程9）

- ページ：docs/math/exponent-mod.md（レベル 水）。今の練習は abc222_g（diff 2242）の 1 問。例題は abc228_e
- 探したところ：
    - (1) b1 の報告 planning/batches/b1/exponent-mod.md と b1 summary/candidates.md に abc212_g・tenka1_2017_f が出ている。b3・b5 の candidates.md には exponent-mod の候補はない
    - (2) data/problems.yaml で pages に exponent-mod を持つが本文にない問題は abc212_g の 1 問（role: practice、確認済み）
    - (3) `python3 tools/ap.py search` で題名の語（Tower・Power・Exponent・Fermat・Euler・Pow・Huge・Tetration・Iterated・Repunit、diff 1000〜2800）を引いた。手法が合いそうなものは abc357_d だけだった（下の「採らなかったもの」）。Web 検索はこのセッションの検索の上限に達していて使えなかったので、新しい問題を Web で探すことはできていない
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補 1 問を足すと練習は合わせて 2 問になる（目標の下限）

## 候補

### abc212_g（台帳にあり、本文になし）

- 問題ID：abc212_g
- 題名：G. Power Pair
- difficulty：2150（黄）
- 役割：practice（帯の上端 1599 より上だが、今の練習 abc222_g（2242）と同じ程度で、フェルマーの小定理の「周期は p − 1 の約数」をそのまま使う。帯を厳しく見るなら challenge）
- 要約：素数 P（P ≤ 10^12）について、0 ≤ x, y ≤ P − 1 の組 (x, y) のうち、ある正の整数 n で x^n ≡ y (mod P) となるものの個数を 998244353 で割った余りで求める問題である。
- 方針の要点：x = 0 は 1 組、x ≠ 0 なら到達できる y の個数は x の位数 d で、フェルマーの小定理から d は P − 1 の約数、位数 d の元は φ(d) 個あるので、答えは 1 + Σ_{d | P−1} d·φ(d) である（P − 1 を素因数分解して約数ごとに φ を求める）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2021/08/01/163600 （問いと制約、答えの式 1 + Σ d·φ(d)、位数が P − 1 の約数であることにフェルマーの小定理を使う点を確かめた。P = 7 で 22 になる検算も載っている）
- 補足：本文の練習の方針では [位数](../math/multiplicative-order.md) と [φ](../math/euler-phi.md) へのリンクを張るのがよい。このページの節 #fermat の「最短の周期（位数）は p − 1 の約数」の応用として置ける。2 つ目の裏付けとして kmjp・kazun-kyopro・programming-hiroba の記事の URL を試したが、どれも 404 で見つからなかった

## 採らなかったもの

- tenka1_2017_f（F. ModularPowerEquation!!、diff 3653）：ap.py で実在を確かめたが、黄の帯（〜2399）から大きく離れていて力試しにも重い。第三者の解説も今回は開いていない
- abc357_d（D. 88888888、diff 970）：N を N 個つなげた数の mod を等比数列の和で求める問題である。指数 kN（k は N の桁数）を p − 1 で割る解き方もできるが、programming-hiroba の記事（https://programming-hiroba.com/abc357-d/ ）の本文は (10^k)^N を繰り返し二乗法で求めて逆元で割る方法で、このページの手法が主役ではない。帯も下に外れる
- abc335_g（diff 2614）・arc191_c（diff 2198）・abc449_g（diff 2631）：題名からは位数や累乗の話に見えるが、位数（multiplicative-order）が主役か、帯を外れるので、このページの候補にはしなかった（解説は開いていない）

## 結論

確かめた候補は abc212_g の 1 問で、足すと練習は 2 問になる。Web 検索が使えなかったので、指数を p − 1 や φ(m) で割ることが主役の水〜青の問題（とくに abc319 以降）はほかに見つけていない。必要なら検索の上限が戻ってから探し直す。
