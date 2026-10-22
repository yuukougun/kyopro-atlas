# zeta-mobius-subset の問題の補充（b6・工程9）

- ページ：docs/comb/zeta-mobius-subset.md（レベル 黄）。今の練習は 0 問。例題は arc100_c、力試しは abc213_g・abc295_h
- 探したところ：(1) b1・b5 の summary/candidates.md にこのページの候補なし。b3 の summary/candidates.md と b3 の報告 planning/batches/b3/zeta-mobius-subset.md の「問題の補充の候補」に abc349_f（practice）と abc215_h（力試し）。(2) data/problems.yaml でこのページを pages に持つ問題は arc100_c・abc213_g・abc295_h の 3 問で、どれも本文にある（本文にない問題はなし）。abc349_f は台帳にまだない。(3) 第三者の解説で arc137_d・abc472_g を新たに見つけた（drken の「高速ゼータ変換」カテゴリの一覧と kmjp の記事から）
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 練習の候補 3 問（abc349_f・arc137_d・abc472_g）を足すと練習は合わせて 3 問になる。力試しの候補として abc215_h も確かめた
- 途中で WebSearch の回数の上限に達したので、abc472_g の 2 つ目の裏付けは探せていない

## 候補

### abc349_f（台帳になし。b3 から持ち越し）

- 問題ID：abc349_f
- 題名：F. Subsequence LCM
- difficulty：2169（黄）
- 役割：practice
- 要約：長さ N の正整数列と M が与えられ、空でない部分列のうち要素の lcm がちょうど M になるものの数を 998244353 で割った余りで求める。
- 方針の要点：M の約数でない要素を捨て、残りを「指数が M と等しい素因数の集合」の bit（M ≤ 10^16 なので高々 13 bit）に潰し、bit ごとの個数を部分集合ゼータ変換して 2^{g(S)} にし、メビウス変換で全 bit がちょうど立つ分を取り出す（inverse の節の型そのもの）。
- 裏付け：
    - https://merom686.hatenablog.com/entry/2024/04/14/011833 （素因数ごとの bit・ゼータ → 2 の冪 → 逆変換を確かめた。素因数分解を避ける公式の別解にも触れている）
    - https://www.cnblogs.com/MoyouSayuki/p/18134468 （M の約数でない要素を捨てること、bit への変換、高次元の累積和 → 2^{g} → 包除で全 bit の分を取る、M = 1 の特別な場合を確かめた）
- 台帳への追加の提案：新しい行。pages に {id: zeta-mobius-subset, role: practice}（b2・b3 の提案どおり divisor-inclusion-exclusion・zeta-mobius-divisor にも）

### arc137_d（新規。台帳になし）

- 問題ID：arc137_d
- 題名：D. Prefix XORs
- difficulty：2191（黄）
- 役割：practice
- 要約：長さ N の整数列について、すべての i で A_i を A_1 から A_i までの XOR に置き換える操作を k 回行った後の末尾の値を、k = 1, …, M のそれぞれについて求める。
- 方針の要点：A_{N−i} が k 回後の末尾に効くかは二項係数 C(i+k−1, k−1) の偶奇で決まり、Lucas の定理から「i と k−1 が共通の bit を持たない」とき奇数なので、S を max(N, M) 以上の 2 の冪として B[S−1−i] = A_{N−i} に置き、演算を XOR にした上位集合（または補集合の部分集合）のゼータ変換をして B[k−1] を答えにする（O(S log S)）。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2022/03/26/0930 （二項係数の偶奇・Lucas の定理・B[S−1−i] への配置・高速ゼータ変換・B[K−1] が答え、を確かめた。コードの変換は XOR の上位集合の版）
    - https://scrapbox.io/Atcoder-myReflection/ARC137_D._Prefix_XORs （コードが XOR の上位集合の変換であることだけ確かめた。解法の文章は空欄で、Lucas の定理はタグだけ）
- 注意：二項係数の偶奇（Lucas の定理）の持ち主のページがあればそちらへリンクしたい。和の代わりに XOR を使う変換なので、superset の節か「和の代わりに別の演算」の補足に結び付けるとよい
- 台帳への追加の提案：新しい行。pages に {id: zeta-mobius-subset, role: practice}

### abc472_g（台帳にあり。別のページの例題）

- 問題ID：abc472_g
- 題名：G. Cascading Grid
- difficulty：2018（黄）
- 役割：practice（ただし主な解き方はゼータ変換ではない。下の注意）
- 要約：+・-・# の盤面で、# でないマスと、そこから # を通らずに左右と下へ進んで届くマスを # に変える操作を何度でも行い、残った + の数から - の数を引いた値を最大化する。
- 方針の要点：各行を左右につながった成分に分け、行ごとに「どの成分を埋めたか」の bit を持つ DP にし、下の行で「少なくとも mask を埋めた」ときの最良値を、和の代わりに max を取る上位集合のゼータ変換で一括して求める。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2026/08/22/0930 （行内の成分・bit DP・dp[mask] = max(dp[mask], dp[mask | 1<<i]) の上位集合の変換を確かめた。制約は記事に明記なし）
- 注意：台帳ではすでに project-selection の example（approach は「DAG 上の選択の条件を最小カットに直す」。evidence は ikatakos と drken の燃やす埋める）。ゼータ変換は kmjp の別解なので、台帳の alternatives に {pages: [zeta-mobius-subset], approach: 上の方針} を足して練習に置く形になる。別解だけで練習に置くのが重いなら外してよい。2 つ目の裏付けは検索の上限で探せていない
- 台帳への追加の提案：pages に {id: zeta-mobius-subset, role: practice}、alternatives に上の approach

### abc215_h（台帳にあり。力試しの候補）

- 問題ID：abc215_h
- 題名：H. Cabbage Master
- difficulty：3101（発展。帯から大きく離れる）
- 役割：challenge
- 要約：キャベツの種類ごとの個数と、各会社の必要数と受け入れる種類の集合が与えられ、全社の要求を満たす配り方がなくなるように取り除く個数の最小値と、その個数での取り除き方の数を求める。
- 方針の要点：種類の集合 mask ごとに「mask の中だけで受け入れる会社の需要の和」と「mask の供給の和」を部分集合ゼータ変換で求めて Hall の条件を全 mask で調べ、取り除き方の数は二項係数をメビウス変換で「ちょうど mask」に直し、不足の起きる mask の印を部分集合の方向へ広げて足す。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2021/08/22/0930 （需要・供給の部分集合和、Hall の定理、メビウス変換と印の伝播を確かめた）
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0821_abc215 （台帳の evidence。今回は読んでいない）
- 注意：力試しはすでに 2 問（abc213_g・abc295_h）。b3 で abc295_h はゼータ変換を使わないので外す提案が出ている。外すなら abc215_h を入れ替えに使える
- 台帳への追加の提案：pages に {id: zeta-mobius-subset, role: challenge}

## 見送ったもの

- arc171_d（D. Rolling Hash、diff 2377）：drken の「高速ゼータ変換」カテゴリにあるが、中身は彩色数（独立集合の数と包除）への帰着で、記事のコードも変換を直接は使っていない。chromatic-number の候補にはなりうる
- arc106_e（E. Medals、diff 2825）：drken のカテゴリにある Hall の条件＋ゼータ変換の問題だが、発展の帯で力試しはすでに足りるので今回は内容を確かめていない
- abc304_f・agc038_c・agc039_c：約数・倍数の変換なので zeta-mobius-divisor の担当

## 使った出典と noai

- 使ったドメインはすべて付録 B にある（merom686.hatenablog.com・www.cnblogs.com・kmjp.hatenablog.jp・scrapbox.io の Atcoder-myReflection・drken1215.hatenablog.com）。新しく check_noai を流したドメインはない
