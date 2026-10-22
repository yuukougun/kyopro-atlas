# binomial-prefix-sum の検証（b4）

- 対象：docs/comb/binomial-prefix-sum.md、snippets/binomial-prefix-sum/mover.{cpp,yaml}（図はなし。catalog の visual は null）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、ACL は third_party/ac-library

## 実行した検査

- `python3 tools/check_pages.py --page binomial-prefix-sum`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/binomial-prefix-sum`：期待と違う 0
- `python3 tools/fix_problems.py --check --page binomial-prefix-sum`：直すべき行 0
- `npx textlint docs/comb/binomial-prefix-sum.md`：エラー 0・警告 12（数式を含む文の読点・長さ。誤検出として妥当）
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、cases 3 つを実行：期待どおり（`1`／`0 16 32 4`／`863941396 1 2`）。警告・サニタイザの報告なし
- 一時置き場の brute.py：n_max ≤ 40、Q ≤ 30、K は −1 から n_max の乱数 400 回で、Python の愚直な和（math.comb）と一致
- cases 3 つ目の値 863941396 は (2^200000 + C(200000, 100000)) / 2 mod 998244353 を Python で計算して一致
- 縮めてから伸ばす順（dec_k → dec_n → inc_k → inc_n）に書き換えた版も、同じ乱数 400 回で愚直な和と一致（指摘 2 の根拠）

## 確かめた事実（問題なし）

- 更新式 4 本（K±1・n±1）と、K < 0・K ≥ n でもそのまま成り立つこと：手計算と上の乱数試験で確認
- 例 S(4,2) = 11、S(5,2) = 16、2·11 − 6 = 16：正しい
- パスカルの三角形の説明（右端の C(n,K) だけ右下への寄与が範囲外）：正しく、ikatakos 氏の記録の G の解法の節と同じ筋（文は別の言い回しで、近すぎない）
- Mo の順の計算量 O(N√Q + Q log Q)：ブロック N/√Q で n の移動 Q·N/√Q、K の移動はブロックごとに O(N) で √Q ブロック。根拠どおり。要点・front matter の complexity・本文が一致
- 例題 ABC235 G：`tools/ap.py show abc235_g` で題名 G. Gardens・diff 2462。問題の条件（同じ種類は 1 つの庭に 1 本まで、余ってよい、どの庭にも 1 本以上）と、空の庭の包除の式・S(m+1, P) = 2S(m, P) − C(m, P) で O(N) にする方針を kmjp 氏の記事と ikatakos 氏の記録（解法の節だけ）で確認。本文の方針・解法の詳細と食い違いなし
- 参考の URL 3 件：kmjp の記事の題名「AtCoder ABC #235 : G - Gardens」、ikatakos の h1「HHKB Programming Contest 2022（AtCoder Beginner Contest 235）F,G問題メモ」、library-checker-problems の enumerative_combinatorics に部分和の問題がなく binomial_coefficient_prime_mod（title 'Binomial Coefficient (Prime Mod)'）があることを確認（リポジトリ全体の木でも binom を含む問題は binomial_coefficient・binomial_coefficient_prime_mod・q_binomial_coefficient_prime_mod だけ）。ドメインはどれも付録 B にある
- リンク先の節（mo-algorithm#two-prefixes・binomial-precompute#table-size・glossary#offline）はあり、相手は draft。mo-algorithm#two-prefixes の記述（S(n+1,k) = 2S(n,k) − C(n,k)）とも一致
- front matter：執筆者が変えたのは complexity・stage・updated と sections の library の追加だけ。summary・signs と要点が一致。別名の行に aliases がすべてある
- 未解決の点 1（N の上限）：kmjp・ikatakos のどちらにも数値の上限は見当たらない（kmjp のコードの配列は 5×10^6 程度）。本文は「N が大きいので」とぼかしており、このままでよい

## 指摘

### 1. 直すべき｜コード（C2・手引き §9）・事実（F3）｜#library の最後の段落と snippets/binomial-prefix-sum/mover.cpp の main

- 問題：本文は「完全なプログラム（mover.cpp）は、クエリを Mo の順に並べて処理し、小さい n で愚直な和と比べて確かめたものである」と書くが、mover.cpp には愚直な和との比較も `assert` もない。読者がファイルを開くと書かれた確かめが見当たらない。手引き §9 の「プログラムは main と assert を持つ完全なものにし」にも合わない（執筆者の 300 回の比較は手元だけで、リポジトリに残っていない）
- 根拠：mover.cpp を読んだ（`assert` なし。main はクエリを読んで答えを出すだけ）
- 直し方：main の最後に、n_max が小さい（例：n_max ≤ 60）ときだけ各クエリの答えを `binom` の和で計算し直して `assert(ans[i] == brute)` で比べる処理を足す（cases の 1・2 つ目で動く）。またはこの文を「cases の小さい値は手で計算した値と比べてある」のように実際に合わせて書き直す。前者がよい

### 2. 直すべき｜事実（F2）・分かりやすさ（U4）｜#library の箇条書き 3 つ目（「Mo の順のときは、区間の Mo と同じく『伸ばしてから縮める』順にすると K が −1 より小さくならない」）

- 問題：この状態 (n, K) には、区間の Mo の l > r にあたる「通ってはいけない状態」がない。4 つの while はそれぞれ目標の値で止まるので、どの順で動かしても n・K は今の値と目標の値の間にとどまり、K が目標（≥ −1）より小さくなることはない。本文は「伸ばしてから縮める順でないと K が −1 を割る」と読める書き方で、順番に意味があると誤解させる。自作する読者が理由のない制約を覚えてしまう
- 根拠：mover.cpp を「縮めてから伸ばす」順（dec_k → dec_n → inc_k → inc_n）に書き換えた版を作り、乱数 400 回（n_max ≤ 40、K は −1 から）で愚直な和と一致した。サニタイザの報告もなし。dec_n で K > n の状態を通っても S(n−1, K) = (2^n + 0)/2 = 2^{n−1} で式は成り立つ
- 直し方：この箇条を「区間の Mo と違って、(n, K) には通ってはいけない状態がない（K > n や K = −1 でも式が成り立つ）ので、4 方向をどの順に動かしてもよい。K は目標の値より小さくならないので、クエリに K = −1 がなければ S(n, −1) も通らない」のように直す。mover.cpp の main のコメント「伸ばしてから縮める」も、順は自由である旨に合わせる（区間の Mo の習慣にそろえただけ、など）。#order の最後の段落の「K = −1 まで行くことがある」は「クエリに K = −1 があれば」と条件を添えるとよい

### 3. 直すとよい｜分かりやすさ（U5・U7）｜#with-inclusion-exclusion と例題 ABC235 G の方針・解法の詳細

- 問題：#with-inclusion-exclusion の「箱と 3 種類の玉」は例題そのもので、包除の式・S(m, A) の表を n の順に作ること・全体 O(N) まで書いている。そのため例題の方針と「解法の詳細」の 1・2・3 点目がほぼ同じことの繰り返しになり、折りたたみに新しい情報が少ない（4 点目の計算量の比較だけ）
- 根拠：2 か所を並べて読んだ
- 直し方：どちらかを薄くする。たとえば #with-inclusion-exclusion は一般形（「各グループへ入れる数に上限 K、どのグループも空にしない」→ Σ(−1)^k C(N,k) S(N−k, K)^…）と、そこに K 固定の S(m, K) の列が出ることに絞り、3 種類・庭の具体は例題に任せる。解法の詳細には、本文にない点（同じ種類を区別しない理由、m ≤ A の間は 2^m で進む点、計算量の比較）だけを残す

### 4. 直すとよい｜分かりやすさ（U3）｜#with-inclusion-exclusion の 2 段落目「ある種類の玉を各箱 1 個まで、合計 A 個以下入れる方法は、玉の入る箱の選び方なので S(N, A) 通り」

- 問題：「玉の入る箱の選び方で決まる」のは同じ種類の玉を区別しないときだけで、その前提が書かれていない（例題の解法の詳細には「同じ種類の苗は区別しない」とある）。区別すると読んだ読者は S(N, A) にならない
- 直し方：「同じ種類の玉は区別しないので、」を足す

### 5. 直すとよい｜事実（F5・手引き §2.5）｜導入 2 段落目「例題の ABC235 G（diff 2462）が代表である」

- 問題：本文で問題に触れるときは例題の見出しへリンクする決まり（§2.5）だが、ここはリンクがない（#with-inclusion-exclusion では `[例題 ABC235 G](#abc235_g)` とリンクしている）
- 直し方：`[ABC235 G](#abc235_g)` にする

### 6. 直すとよい｜コード（C3）｜#library のコード片 `BinomPrefix` と本文の記号

- 問題：本文は状態を (n, K)（大文字。和の添字が小文字の k）と書くが、コードのメンバは `k` で、コメントの「S(n, k) = C(n, 0) + … + C(n, k)」も小文字。本文の箇条「K を増やすときは先に K を進めてから C(n, K) を足し」とコードの `inc_k` を対応させるとき、和の添字 k と取り違えやすい
- 直し方：本文の最初の段落に「コードの `k` が本文の K にあたる」と一言添える（コードを `K` にすると §9 の小文字の変数名から外れるので、本文側の注記がよい）

### 7. 直すとよい｜分かりやすさ（U9）｜#update の最後の段落「K ≥ n では C(n, K) = 0（K = n なら 1）」

- 問題：「K ≥ n では 0」と言ってから括弧で K = n を例外にしており、一度読んで矛盾に見える
- 直し方：「K > n では C(n, K) = 0 なので S(n+1, K) = 2^{n+1}、K = n では C(n, K) = 1 なので 2^{n+1} − 1 になる」と 2 つに分けて書く

## 図

図はなし。catalog の visual は null なので G7 の不足もない。figure.md の G1〜G6 は対象なし。

## 台帳への提案（執筆者の提案の確認）

- abc235_g の summary の直し（植え方の条件を入れ、「（執筆時に確かめる）」を外す）：kmjp・ikatakos の解法の節で条件を確かめた。賛成
- evidence に ikatakos の記録を足す：G の解法の節がこの問題のものであることを確認した。賛成
- abc235_g の `checked` に 2026-10-22 を入れる

## 総合の判定

小さな直しで可（直すべき 2 件：コード片に愚直な和との比較を足す（または本文の記述を実際に合わせる）、伸縮の順についての誤った理由を直す。どちらも局所的な直し）
