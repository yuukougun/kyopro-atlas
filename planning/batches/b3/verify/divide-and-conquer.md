# divide-and-conquer の検証（b3）

対象：docs/basics/divide-and-conquer.md、snippets/divide-and-conquer/（merge-inversion・split-at-max・range-knapsack）、docs/img/divide-and-conquer/（recursion-tree.svg・range-knapsack.svg）。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page divide-and-conquer`：エラー 0・警告 0
- `python3 tools/check_snippets.py divide-and-conquer`：3 本とも期待どおり（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 3 本を `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、警告なし。作業用の場所の乱数の生成器で次を流し、assert（素朴な方法との一致）とサニタイザに引っかからなかった
    - range-knapsack：N ≤ 40・Q ≤ 60・重さ 1〜500・価値 ≤ 10^9・c は 0〜500 の 300 通り
    - split-at-max：N ≤ 300・値の幅 3・30・10^9 の 200 通り。drken 氏の記事の同じ値が並ぶ例 (3, 15, 15, 15, 15, 15, 7, 8) も 3 93 15 15 15 93 7 15 になる
    - merge-inversion：同じ 200 通りの列
- yaml の cases を手で確かめた：転倒数の (3,1,5,4,2) = 5、(2,2,1) = 2、ナップサックの 1 つ目の 5 クエリ（7・0・8・0・5）
- front matter：git diff で、執筆者が変えたのは complexity・stage だけ（updated は元から同じ日付）。要点の計算量と complexity は一致。別名の行に aliases がすべてある
- 図の例：(5, 2, 7, 1, 8, 3, 6, 4) の転倒数は 13、段 0 のまたぐ組 5、段 1 の 2 と 2、段 2 の 1 が 4 個で、図・代替テキストと一致
- 計算量の主張：表（O(L)→O(N log N)、O(L log L)→O(N log^2 N)、O(LC)→O(NC log N)、O(L^2)→O(N^2)）、確認問題 1 の段ごとの和 N^2/2^d、短い側だけを試す O(N log N) の理由（短い側の区間の長さは (L−1)/2 以下）、区間ナップサックの O(NC log N + QC)、落とし穴の「区間は約 2N 個」「N(N−1)/2 ≈ 2×10^10」「[l, l+1) が [l, l) と [l, l+1) に分かれ続ける」はどれも正しい
- 確認問題 2（(2, 2) で 1 と出る）・3（(1, 2, …, N) で O(N^2)・深さ N）：正しい
- ARC189 D の解法の詳細：最大値を最も左に取ると、左の子の要素は A_m より真に小さく、区間の外の隣は祖先で A_m 以上。「m の隣に真に小さい要素があれば区間を吸収しきる」「S > A_p なら g = g_親、S ≤ A_p なら g = S」は正しく、コードとも一致する（上の乱数の比較）。制約 2 ≤ N ≤ 5×10^5 は drken 氏の記事の制約の節で確かめた
- 問題：ap.py で arc189_d（2006）・abc426_g（2119）・abc478_g（2582）・chokudai_S001_j（diff なし）を確かめ、本文の題名・diff と一致。台帳の役割（example 2・practice 1・challenge 1）と要約も一致し、要約に手法名はない
- ABC478 G：kmjp 氏の記事の問い（i < j の P_i と P_j を p:q に内分した点の凸包の面積）と方針（前半・後半の内分点の凸包と、前半の凸包と後半の凸包を q:p に重みづけたミンコフスキー和の凸包）が、本文の方針と一致。内分点は (q P_i + p P_j)/(p+q) なので「左の点を q 倍・右の点を p 倍」も正しい
- ABC426 G：kmjp 氏の記事の問いと方針（中央 M' を末尾とする接尾辞・先頭とする接頭辞の表、容量の配り方を総当たり）が本文と一致
- 本文のリンク先の anchor（monotonic-stack#cartesian-tree・sparse-table#disjoint-sparse-table・knapsack-undo#prefix-and-suffix・knapsack-undo#offline-divide-and-conquer・inversion-number#count-with-bit・recursion-structure#stack・glossary#recursion-tree・glossary#offline）はすべて実在。monge・online-convolution・cdq-divide-and-conquer・advanced-geometry は stub で anchor なしのリンク
- 参考の URL：4 件とも check_noai.py で noai の指定なし。curl で `<title>` を取り、内容が本文の説明どおりであることを確かめた（題名の食い違いは指摘 4）。本文の言い回し・例は記事と別で、F8 の問題はない
- 図：`python3 tools/render_svg.py divide-and-conquer` で 360px・720px の PNG を目で確かめた（Chrome headless shell 146）。白背景・viewBox・sans-serif のテキスト。720px で文字の重なり・はみ出しはない（720px の PNG で最下行が切れるのは撮影の高さのためで、viewBox には収まっている）。visual は static で動く図はない

### 執筆者の未解決の点について

- abc426_g の制約：kmjp 氏の記事のコードは容量の表を 0〜500（`dp[..][512]`、ループの上限 500）、クエリの配列を 202020、品物の再帰を `dfs(0, 1<<15)` で取っており、$C \le 500$・$Q \le 2 \times 10^5$・$N \le 2^{15}$ 程度と読める。ただし問題文の制約そのものは確かめられないので、本文の「容量の上限 $C$ が数百と小さい」のままでよい
- abc451_g：kmjp 氏の記事（https://kmjp.hatenablog.jp/entry/2026/03/28/0930）を読み、全域木の根からの XOR・残りの辺の閉路で値を小さくする・Trie で数える、の流れで、分割統治は出てこないことを確かめた。ikatakos 氏の記録は今も 503。台帳から divide-and-conquer の challenge を外す提案に同意する。frequency_evidence の recent も 1 になる（メインの反映）
- 使い分けの「戻す DP と区間の出し入れ」：趣旨は正しい。Mo のページがあれば、メインのリンクの張り替えのときに足すとよい
- 台帳の checked：arc189_d（drken 氏の記事で問いと制約）・abc426_g（kmjp 氏の記事で問い）を確かめたので、checked に 2026-10-21 を入れる提案に同意する。abc426_g の evidence に kmjp 氏の記事を足す提案にも同意する

## 指摘

1. **直すべき**｜F2 主張の誤り｜#arc189_d の本文（解法の詳細の前の段落）「区間 $[l, r)$ の最大値の位置を $m$ とすると、$[l, r)$ の中の誰も $m$ を吸収しないまま区間の外へ出ることはできない」｜この文は成り立たない。反例：列 (5, 3, 2, 1, 4) で、区間 [1, 5)（根 5 の右の子）の最大値は位置 4 の 4。位置 1 の 3 は 2・1 を吸収して 6 になり、4 を吸収しないまま区間の外の 5 を吸収できる（素朴なシミュレーションで確かめた）。解法の詳細と コードは「m 自身の答え」だけを各区間で決めており、こちらは正しい｜手計算と split-at-max.cpp の naive 関数｜例えば「区間 $[l, r)$ の最大値の位置を $m$ とすると、区間の外のすぐ隣はどちらも $A_m$ 以上である。だから $m$ については、区間の中を吸収しきれるかと、吸収しきった後に外の境界を越えられるかを分けて考えられ、後者は区間の和と親の値で決まる」のように、m についての主張に直す

2. **直すべき**｜F1 計算量｜#split-at-max の 2 つ目の箇条書き「長い方は二分探索や累積和で数える。$O(\min(\text{左の長さ}, \text{右の長さ}))$ の処理の合計は $O(N \log N)$ になる」と、応用の型の 1 つ目「長い側を累積和の二分探索で数える」｜短い側の端点 1 つごとに二分探索をすると、1 回の処理は $O(\min \cdot \log N)$ で、合計は $O(N \log^2 N)$ になる。今の書き方では二分探索を使っても $O(N \log N)$ と読める（執筆者の提案の abc282_h も $O(N \log^2 N)$ と書いている）｜短い側の端点の数 × 二分探索 1 回の手間｜「長い側を $O(1)$ で数えられれば合計は $O(N \log N)$、二分探索を使うと $O(N \log^2 N)$ になる」と分けて書く

3. **直すとよい**｜F3・U3 図と本文の食い違い｜#recurrence の「段の数は $\lceil \log_2 N \rceil$ である」と図 recursion-tree.svg｜図は段 0〜3 の 4 段を描き、注記で「段の数は log₂ 8 = 3（葉を除く）」としている。本文には「葉を除く」がないので、図を見た読者は 4 段か 3 段かで止まる｜図と本文の照合｜本文を「長さ 1 の区間（葉）を除くと、段の数は $\lceil \log_2 N \rceil$ である」とする

4. **直すとよい**｜F9 参考の題名｜#references の 3 つ目と 4 つ目｜kmjp 氏の abc478_g の記事の題名は「AtCoder Beginner Contest 478 : G - Division Point Hull」（本文は「AtCoder ABC #478 : G - Division Point Hull」）。vain0x 氏の記事の題名は「競プロ参戦記 第10回「転倒数」 Chokudai Speed Run 001 [J]」で、note の著者名は「令掛ベイン」｜curl で取得した `<title>`｜題名を記事のとおりに直す（著者の表記はほかのページの vain0x の書き方に合わせてよい）

5. **直すとよい**｜G3 スマホで読めるか｜recursion-tree.svg（viewBox 660 幅、文字 12〜14px）・range-knapsack.svg（viewBox 640 幅、14px）｜幅 360px では約 0.55 倍に縮み、recursion-tree の「またぐ 2」「長さの合計 8・またぐ組 4」（12px）が約 6.5px、range-knapsack の「品物 0」などが約 7.5px になり読みにくい｜render_svg.py の 360px の PNG を目で確かめた｜文字を 16〜18px に上げる。recursion-tree は右側の段の説明の列（x = 496 以降）を図の下にまとめるか省くと幅を詰められる。range-knapsack は下の 2 行の注記が本文・代替テキストにあるので図から省いてもよい

6. **直すとよい**｜C4・C5 取り込みの範囲と書き方｜split-at-max.cpp の core（9〜46 行）・range-knapsack.cpp の core（10〜57 行）｜split-at-max の core は Sparse Table の構築（13〜26 行）まで含み、本文で説明する「最大値で割る」の要点が埋もれる。また C++20 の `bit_width` を使うが、本文に版の注記も C++ の章へのリンクもない。range-knapsack の core には solve で使わない `int n;` が入っている｜手引き §9（要点の数行・新しい書き方には C++ の章へのリンク）｜split-at-max は印を Sparse Table の部分と本体（スタックの部分）に分けて本体だけを取り込むか、`bit_width` の行に [bit ヘッダの関数](../cpp/cpp-math-functions.md#bit-functions) へのリンクを本文で添える（または `__lg` にする）。range-knapsack は `int n;` を core の外へ出す

7. **直すとよい**｜U4 実装の粒度｜#range-knapsack の手順 4「表の値を『容量 $x$ 以下での最大』と決めておけば」と、手順 2・3 と コードの対応｜(a) どうすれば「以下」の意味になるか（空の表を全部の容量で 0 から始める）が本文にない。0 以外（−∞）で始めると「ちょうど」の意味になり、配り方を全部試すだけでは足りなくなる。(b) 本文は L と R の 2 つの表で説明するが、コードは 1 本の `tab` で、`tab[i]`（i < m）が L、`tab[j]`（j > m）が R、`tab[m]` が空の表を兼ねる。読者がコードと手順を対応させるときに止まる｜本文とコードの照合｜(a) 手順 2 に「空の表 $L[m]$ はすべての容量で 0 にする（こうすると表の値が『容量 $x$ 以下での最大』になる）」と足す。(b) コード片の前か後に「コードでは 1 本の配列 tab の $i < m$ の行を $L$、$j > m$ の行を $R$ に使い、$m$ の行が空の表になる」と 1 文足す

8. **直すとよい**｜U7 問題の書き方｜#crossing の応用の型の 3 つ目「…集合どうしの演算（凸包のミンコフスキー和など）でまとめて作る（[力試し](#challenge)の ABC478 G）」｜力試しの方針は折りたたみに入っているが、本文の応用の型で問題名と解き方（ミンコフスキー和）を結び付けて書いており、折りたたむ意味が薄れる｜手引きの例題・力試しの書き方（方針は折りたたみ）｜応用の型からは問題名を外し、型の説明だけにする（力試しの側から #crossing へリンクしているので、つながりは保てる）

## 総合の判定

小さな直しで可。直すべきは 2 件（ARC189 D の段落の成り立たない主張、最大値で分けるときの二分探索の計算量）。どちらも 1〜2 文の書き換えで済む。ほかの事実（転倒数のマージ・計算量の表・区間ナップサックの正しさと計算量・ARC189 D の解法の詳細・ABC478 G の内分点の式）は計算・記事・乱数での照合で正しいことを確かめた。コード片は警告・サニタイザの異常なし。
