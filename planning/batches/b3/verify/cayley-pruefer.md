# cayley-pruefer の検証（b3）

対象：docs/comb/cayley-pruefer.md、snippets/cayley-pruefer/（count・max-diameter）、docs/img/cayley-pruefer/degree-sequence.svg。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page cayley-pruefer`：エラー 0・警告 0
- `python3 tools/check_snippets.py cayley-pruefer`：2 本とも期待どおり（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 2 本を `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルし、警告なし。count は入力 `5 / 3 2 1 1 1` で `125 3`、max-diameter は N = 10^6（表の上限 2N−3 ≤ 2×10^6 に収まる）と N = 7 で実行時エラーなし。どちらも main の先頭の全探索の assert（N ≤ 7）が通った
- `npx textlint`：エラー 0・警告 17（数式を含む文の長さ・読点・助詞の重複。手引き §14-25 の範囲）
- front matter：git diff で、執筆者が変えたのは complexity・stage・updated だけ。要点の計算量と complexity は一致
- 本文の具体例を手で確かめた：小さい N の表（1・1・3・16、パス 12 個 = 4!/2）、図の 3 つの木の Prüfer 列（葉を小さい順に消して (1,1,2)・(1,2,1)・(2,1,1) になる）、落とし穴の (2,2,1,1) の 2 個（パス 3−1−2−4 と 3−2−1−4）と 2!/(2!2!) = 1/2、確認問題 3 問（1 個・64/125・20 通りと内訳 8+8+4）
- 自分で導いた主張の確かめ（作業用の場所の Python、リポジトリには置かない）：
    - 頂点 v の次数が k の木 C(N−2, k−1)(N−1)^(N−1−k)、成分をつなぐ (Π s_i) N^(k−2)：count.cpp の全探索の assert（N ≤ 7、成分は連続する番号の分け方すべて）が通る
    - 根付き N^(N−1)、v が葉 (N−1)^(N−2)（N = 2 でも 1）、確率 (1−1/N)^(N−2)：Prüfer 列からの数え方で正しい
    - 次数列の個数 C(2N−3, N−1)：N 個の正の整数で和 2N−2 の重複組合せで正しい
    - abc290_f の閉じた式 (N+1)C(2N−3,N−1) − N C(2N−4,N−2) と Σ_k (k+1)C(N,k)C(N−3,k−1) が N = 3〜59 で一致。cirrostratus の記事の最終式 N C(2N−4,N−3) + C(2N−3,N−1) とも、C(2N−3,N−1) = C(2N−3,N−2) とパスカルの関係で一致する
    - arc106_f の (Π d_v)(S−N)(S−N−1)…(S−2N+3)：d = (1,1)・(2,1,1)・(3,2,2)・(1,1,1)・(2,3,1,2)・(4,1,1,1,2) で、次数列ごとの (N−2)!/Π(e_v−1)! × Π(d_v の下降階乗) の総和と一致。drken の記事の解答コード（n = N … 2N−3 で S − n を掛ける）とも同じ
    - Π a_v^{d_v} が F_v(x) = a_v e^{a_v x} に当たること、多項定理で総和が N^(N−2) に戻ること：正しい
- 本文のリンク先の anchor：tree-degree#pruefer・tree-degree#realizable・multinomial-coefficient#meaning・stars-and-bars#stars-bars・binomial-identities#vandermonde・counting-bijection#classic-bijections・glossary#spanning-tree はすべて実在。fps-basics・generating-function-counting・matrix-tree-theorem は stub で、anchor なしのリンクなので §14-23 どおり
- 問題：台帳で abc290_f（example）・abc303_h（challenge）・arc106_f（challenge）の役割と要約・diff が本文と一致。要約は手法名を含まない
- 図：`python3 tools/render_svg.py` で 360px・720px の PNG を目で確かめた。白背景・viewBox・sans-serif のテキスト、色と数字ラベルの併用はよい。720px の PNG で下端の注記が切れるのは撮影の高さのためで、viewBox（620×400）には収まっている
- 参考の URL：4 件とも check_noai.py で noai の指定なし。curl で取得した `<title>` が本文の題名（記事の h1）と一致。cirrostratus.hatenablog.com は付録 B にない（執筆者の提案どおり追加するとよい）。本文の言い回し・例は記事と別で、F8 の問題はない

### 執筆者の未解決の点について

- abc290_f を例題に残すか：本文は「和が次数列にわたるとき」の型として正しく位置づけ、木の数の式を使わないことを明示しており、内容に誤りはない。ただし catalog では representative（手法をそのまま使う代表）で、実際は Cayley・多項係数を使わない。例題を tree-degree か binomial-identities に移すか、このページの例題として残すかはメインの判断でよい（指摘 5）。台帳の approach「次数列を決めたときの木の数と直径を式にし…」は誤り（木の数は使わない）なので、執筆者の提案どおり直すべき
- 出典に直接ない標準的な事実（成分をつなぐ式など）：上のとおり全探索と導出で確かめ、どれも正しい
- 発展の節の計算量：全頂点で同じ条件の場合（O(N log N)・O(N log^2 N)）は drken の abc303_h の記事と一致。頂点ごとに条件が違う場合には条件の書き落としがある（指摘 1）
- tree-degree#counting-links の呼び名の食い違い：執筆者の指摘どおり、メインで題名に合わせるとよい
- 台帳の abc303_h は checked が null のまま。drken の記事で問い（次数が集合 S に入るラベル付き木の数）を確かめたので、checked に 2026-10-21 を入れる提案に同意する

## 指摘

1. **直すべき**｜F2・F1 定理の条件と計算量｜#with-polynomials の箇条書き 2 つ目「頂点ごとに条件が違う：N 個の多項式の積を…分割統治で O(N log^2 N) にする」（と、それを含む要点・complexity の「O(N log N)〜O(N log^2 N)」）｜各 F_v は N−2 次まで項を持ちうるので、条件がなければ多項式の次数の合計は Θ(N^2) になり、分割統治でも一番下の段だけで N/2 回の (N−2) 次どうしの掛け算が要り、O(N log^2 N) にならない（例：頂点ごとに別の集合 S_v で、各 S_v が 1〜N−1 の大半を含む場合）。O(N log^2 N) になるのは、各 F_v の次数の合計が O(N)（各頂点の次数の上限 D_v の合計が O(N) など）のときである｜分割統治の各段の計算量の見積もり。段 l で 2^l 個ずつまとめた積の次数は min(Σ deg F_v, N−2) なので、Σ deg F_v = Θ(N^2) なら各段 Θ(N^2/2^l · …) を下回らない｜「頂点ごとに条件が違う：各 $F_v$ の次数の合計が $O(N)$（例：頂点 $v$ の次数の上限 $D_v$ の合計が $O(N)$）なら、$N$ 個の多項式の積を…分割統治で $O(N \log^2 N)$ にする」と条件を足す。要点と complexity は「全頂点で同じ条件なら」の場合の値なので、そのままでよいが、必要なら「全頂点で同じ条件を多項式の累乗で数えるなら」と言い添える

2. **直すとよい**｜U3・C3 飛躍｜#cayley の節のコード片（`count.cpp:core`）｜Cayley の節で取り込む core に `count_with_degrees` まで入っており、次数を指定した木の式がまだ出ていない段階で読者がそのコードを読むことになる。#degree-sequence の節では「コードは上の節の count_with_degrees」と前に戻らせている｜count.cpp の印 `[start:core]` が count_trees と count_with_degrees の両方を囲む｜印を `trees` と `degrees` の 2 つに分け、count_with_degrees を #degree-sequence の「計算は fact[N−2]・Π ifact[d_v−1] で…」の段落の後で取り込む。Cayley の節の「どちらの関数とも一致することを assert で確かめている」の文もそれに合わせる

3. **直すとよい**｜U3 飛躍｜#sum-over-degrees の「連結成分をつなぐ方法の数」の段落｜「上の式に a_i = s_i を入れて」とあるが、上の式は N 頂点の木についての (Π a_v)(Σ a_v)^{N−2} で、ここで当てはめるのは縮めた k 頂点の木である。読者は指数が N−2 のままか k−2 かで一度止まる｜上の式の導出と当てはめ先の頂点数の比較｜「上の式を $k$ 頂点の木に当てはめ（指数は $k - 2$）、$a_i = s_i$ を入れると、$\sum_i s_i = N$ なので次の式になる」と、頂点数の読み替えと Σ s_i = N を明示する

4. **直すとよい**｜G3 スマホで読めるか｜degree-sequence.svg｜幅 360px では viewBox 620 が約 0.58 倍に縮み、副題と下の注記（13px）が約 7.5px、各木の下の「2 に付く葉は 5」（13px）も約 7.5px になり読みにくい。頂点の番号（15px → 約 9px）もやや小さい｜render_svg.py の 360px の PNG を目で確かめた｜文字を 16〜17px に上げる。副題と最下段の注記は図の外（本文と代替テキスト）にすでにあるので、図からは省いてもよい。または viewBox の幅を詰める（木の横の間隔 200 を 170 程度に）

5. **直すとよい**｜F5・U7 例題と問題の数｜#examples と練習問題の欠落｜(a) 例題 abc290_f はこのページの主な式（Cayley・多項係数）を使わない。本文の扱いは正しいが、「このページの手法をそのまま使う代表」としては弱い。(b) 練習が 0 問で、手引き §14 の目安（練習 2〜6）を満たさない｜手引き 210〜211 行（数の目安・representative の扱い）、台帳の abc290_f の pages（binomial-identities は challenge）｜メインの判断として、執筆者が挙げた nyc2015_5（次数を指定した木の数をそのまま使う）を台帳に足して練習に置く案に賛成する。abc290_f は、このページに残すなら現在の位置づけ（「和が次数列にわたる」型）のままでよい。残す場合でも台帳の approach は直す（上の「未解決の点」）

## 総合の判定

小さな直しで可。直すべきは 1 件（発展の節の「頂点ごとに条件が違う」場合の計算量の条件）。ほかの事実（Cayley の公式・次数を指定した式・1 頂点の次数・成分をつなぐ式・abc290_f と arc106_f の閉じた式）は全探索・別形との照合で正しいことを確かめた。コード片は警告・サニタイザの異常なし。
