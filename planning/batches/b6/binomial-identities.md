# binomial-identities の問題の補充（b6・工程9）

- ページ：docs/comb/binomial-identities.md（レベル 青）。今の練習は arc106_d（diff 1988）の 1 問。例題は abc262_e・abc154_f、力試しは arc110_d・abc290_f
- 探したところ：(1) b2 の報告 planning/batches/b2/binomial-identities.md の「問題の補充の候補」に abc405_e・abc463_g（b3 summary/candidates.md にも同じ 2 問。b1 の candidates.md は abc290_f の行だけで、これは力試しに既にある。b5 の candidates.md には binomial-identities の候補なし）。(2) data/problems.yaml で pages に binomial-identities を持つ問題は 5 問で、すべて本文にある（本文にないものはなし）。(3) 第三者の解説として drken の「二項係数」カテゴリの記事一覧（1〜2 ページ目）をたどり、abc150_e を新しく見つけた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補 2 問を足すと練習は合わせて 3 問になる

## 候補

### abc150_e（台帳にあり。pages は counting-mindset の practice だけ）

- 問題ID：abc150_e
- 題名：E. Change a Little Bit
- difficulty：1851（青）
- 役割：practice
- 要約：長さ N の 0/1 列の相異なる 2 つの組すべてについて、k 回目に位置 i を反転するとコストが k × C_i かかるとして一方を他方に変える最小コストを求め、その総和を 10^9+7 で割った余りで求める。
- 方針の要点：C を降順に並べて n 番目（0 始まり）の要素の寄与を数えると、前の n 個のうち k 個が異なる場合の係数 Σ_k (k+1) C(n,k) が要り、これを二項定理の 2^n と吸収公式の Σ_k k C(n,k) = n 2^{n−1} で 2^n + n 2^{n−1} という閉じた式にする（節 #absorption の「選んだ個数の総和」そのもの）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2020/01/12/142100 （S を 000…0 に固定して 2^N 倍、降順に並べた寄与、Σ_k k C(n,k) = n 2^{n−1} を C(n,k) = (n/k) C(n−1,k−1) から導くこと、最後の式 2^N Σ c_n (2^{N−1} + n 2^{N−2})。N = 1 を別に扱う）
    - https://kmjp.hatenablog.jp/entry/2020/01/11/0900 （同じ寄与の数え方。P(i) = Σ_k C(i,k)(k+1) をパスカルの漸化式から P(i+1) = 2P(i) + 2^i で求める別の導き方）
- 台帳への追加の提案：abc150_e の pages に {id: binomial-identities, role: practice}。approach の alternatives に「寄与の係数 Σ (k+1) C(n,k) を二項定理と吸収公式で 2^n + n 2^{n−1} にする」

### abc405_e（新規。台帳になし）

- 問題ID：abc405_e
- 題名：E. Fruit Lineup
- difficulty：1259（水）
- 役割：practice（帯の下の水だが、本文の落とし穴「閉じた式を探しすぎる」の実例として練習の入口に置ける。帯を厳しく見るなら足さない）
- 要約：リンゴ A 個・オレンジ B 個・バナナ C 個・ブドウ D 個を、種類どうしの前後の条件を満たして一列に並べる方法の数を 998244353 で割った余りで求める。
- 方針の要点：ある境目の左にあるバナナの個数 k で場合を分けると各項が二項係数 2 つの積になり、上の数が動く Vandermonde の形に似ているが和の範囲が途中で切れて 1 つの二項係数にはまとまらないので、k についての O(C) のループで足す。
- 裏付け：
    - https://qiita.com/testcampus/items/1389257a0c177ceb736a （ブドウの左のバナナの個数 k で分け、Σ_{k=0}^{C} C(A+k+B, B)·C(D+C−k−1, C−k)、998244353）
    - https://rsk0315.hatenablog.com/entry/2025/05/11/201737 （別の分け方の Σ C(A−1+i, A−1) C(B+C+D−i, C) を導き、内側の和を hockey stick と上の数が動く Vandermonde 型の恒等式で閉じた式にするが、外側の和は一般には速く求まる閉じた式にならないと検討している）
- 未確認の点：問題文の前後の条件の正確な形（「どの果物がどの果物より左」）は第三者の記事が問題文を書いていないので確かめていない。要約は条件をぼかして書いた。本文に載せる前に別の記事で条件を確かめること
- 台帳への追加の提案：abc405_e を pages {id: binomial-identities, role: practice} で追加。evidence は上の 2 つ（zenn.dev/sukenori/articles/sukenori-abc405 は b2 が挙げたもので今回は読んでいない）

## 除いたもの・採らなかったもの

- arc106_d（練習）・abc262_e・abc154_f（例題）・arc110_d・abc290_f（力試し）：本文に既にある
- abc463_g（G. Random Walk Distance、diff 2452）：kmjp の記事（https://kmjp.hatenablog.jp/entry/2026/06/20/0900 ）を読んだ。E|P − X| を −X + ((N+X)F − 2G)/2^{N−1}（F = Σ_{k<M} C(N,k)、G = Σ_{k<M} k C(N,k)）に直し、(N, M) を Mo のように動かしてパスカルの漸化式で F・G を更新する。G は吸収公式で N Σ C(N−1, k−1) にもできるが、記事は吸収公式を使わずに漸化式で扱っている。中心は二項係数の prefix sum の更新で binomial-prefix-sum の力試し向き。このページに置くなら帯（黄の上を超えて 2452）からも離れるので採らない
- abc156_e（E. Roaming、diff 1514）：各項は C(N,m)·C(N−1,m) で、K ≥ N−1 なら全体の和が Vandermonde（下の数がそろった積）で C(2N−1, N) に一致するが、kmjp の記事（https://kmjp.hatenablog.jp/entry/2020/02/23/0900 ）は恒等式を使わず K ≥ N を別に扱って H(N,N) と書くだけで、解き方の中心は重複組合せの和のループ。台帳では stars-and-bars の practice・counting-mindset の example にある
- abc171_f（F. Strivore、diff 1795）：kmjp の記事（https://kmjp.hatenablog.jp/entry/2020/06/21/1030 ）では重複組合せと 25・26 の累乗の積の和で、二項定理の余事象の形は使っていない。台帳では counting-dedup の例題
- abc276_g（G. Count Sequences、diff 2278）：kmjp の記事（https://kmjp.hatenablog.jp/entry/2022/11/06/0900 ）では差の偶奇の割り当て C(N−1, x) と「B 回以下の上乗せ」を余りの変数で重複組合せ H(N+1, B) にする。和の上限を余りの変数で消す点は縦の和の公式と同じだが、記事は恒等式として扱っていないので採らない
- abc240_g（diff 2462）：45 度回転で独立な 2 本の移動にする格子路の問題（台帳では lattice-paths の力試し）。恒等式の問題ではない
- arc115_d（D. Odd Degree、diff 2325）・abc215_g（diff 2276）：drken の「二項係数」カテゴリにあるが、解説を開いて確かめておらず、題名と台帳の情報からはこのページの恒等式が中心とは言えないので候補にしない
- abc319 以降で恒等式で和を閉じた式にする青の ABC の問題は、今回も見つからなかった

## 本文に足すときのメモ

- 練習の並びは易しい順に abc405_e（1259）→ abc150_e（1851）→ arc106_d（1988）が自然。abc405_e は落とし穴「閉じた式を探しすぎる」、abc150_e は吸収公式の節、arc106_d は累乗の和の展開の節に対応する
- 使った第三者のドメインはどれも付録 B にある（drken1215・kmjp・rsk0315 の各ブログ、qiita.com）。新しく noai を確かめたドメインはない
