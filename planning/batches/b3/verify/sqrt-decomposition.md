# sqrt-decomposition の検証（b3）

対象：docs/ds/sqrt-decomposition.md、snippets/sqrt-decomposition/（bucket-add-count・step-dp）、docs/img/sqrt-decomposition/buckets.svg。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page sqrt-decomposition`：エラー 0・警告 0（本文の問題 5 行）
- `python3 tools/check_snippets.py sqrt-decomposition`：2 本とも期待どおり（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 2 本を `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルして警告なし。cases の入力と `N = 0`（`0 0`）で実行して異常なし。どちらも main の先頭の乱択の self_test（素朴な方法との突き合わせ）が通る
- `npx textlint`：エラー 0・警告 24（数式を含む文の長さなど。§13-8・§14-25 の範囲）
- front matter：git diff で、変えたのは complexity・stage・updated と sections の title 3 つ（anchor は不変）。title の短縮は §13-2・§14-12 で認められている。要点の計算量と complexity は一致
- 計算量の数え直し：
    - バケット分割：加算は端の作り直し O(B log B)＋タグ O(N/B)、質問は O(B + (N/B) log B)。B = √N でどちらも O(√N log N)。マージで作り直せば加算 O(B + N/B)、B = √(N log N) で両方 O(√(N log N))。本文どおり
    - 歩幅：表の大きさ 1 + … + (B−1) = B(B−1)/2 < B²/2。1 マス O(B + N/B)。本文どおり
    - クエリの平方分割：作り直し O(QN/K)、質問 O(K log N)、K = √(N / log N) で O(Q√(N log N))。本文どおり
    - abc219_g：1 回 O(B + M/B)（hn[v] は 2M/B 個以下）、最後の resolve が O(N·M/B)。全体 O(N + M + (Q + N)√M)。本文どおり
    - 数値：2×10^5 × √(2×10^5) ≈ 8.94×10^7（約 9×10^7）、× 8 バイト ≈ 715 MB（約 700 MB）。正しい
- 自分で導いた主張の確かめ（作業用の場所の Python・C++、リポジトリには置かない）：
    - abc219_g の解法の詳細（重い頂点に own_t・own_v を記録し、resolve で隣の重い頂点の最新の記録を取る）を Python で書き、N ≤ 8 のランダムなグラフ・クエリ列・しきい値 B = 1〜4 の 3000 通りで素朴な伝播と一致した（初期値は val[v] = v + 1・t[v] = 0・own_t = −1 とした）
    - 歩幅の DP の予約が i より後で i と同じ余りの位置すべてに届くこと：j > i かつ j ≡ i (mod A_i) と j = i + xA_i（x ≥ 1）は同値。step-dp の self_test（歩幅 1〜3 の回を含む）でも確かめている
    - 出現回数で分ける式 Σ_{軽い色} c_v² < B Σ c_v ≤ BN、重い色 N/B 個以下：正しい
    - abc259_h：c ≤ N のラベルで Σ c² ≤ N·N² = N³、c > N のラベルは N²/N = N 個未満で DP O(N²) ずつ。全体 O(N³)。正しい
    - 確認問題 4 問：答えと理由が正しい（代入のタグを押し下げない例：タグ「5 にする」の後に a_i を 7 にすると、本当の値を求めるときに 5 になる）
    - 図：N = 16・B = 4・[2, 13) で、斜線が添字 2・3・12、塗りがブロック 1・2（添字 4〜11）。本文・代替テキストと一致
- リンク先：glossary#half-open-interval・degree-sqrt#push-pull・complexity-estimation#constraint-table は実在。tree/lca・merge-sort-tree・offline-queries・segment-tree-on-values は draft、segment-tree-beats は stub で anchor なし（§14-23 どおり）
- 問題：台帳と label・diff・要約が一致（check_pages）。abc335_f の言い換え（塗られた集合と進み方の 1 対 1、Σ dp）は torus711 の記事と一致。abc403_g の「想定解は動的セグ木、バケットで整列を保つ」は kmjp の記事と一致（kmjp はバケットの個数を均等に保つ形で、本文の「大きくなりすぎたら割る」は別の保ち方だが正しい）
- 参考の URL：6 件とも check_noai で noai・noimageai の指定なし。suzukiapple.tumblr.com は手元の curl で本文が取れなかった（接続はできるが 0 バイト）。abc365_g の方針は上の式で自分で確かめ、計算量の筋は正しい
- 図：`python3 tools/render_svg.py sqrt-decomposition` で 720px・360px の PNG を目で確かめた（出力：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-sqrt-decomposition/sqrt-decomposition/）。白背景・viewBox・sans-serif・斜線と塗りの区別・ラベルの併用はよい。720px では重なり・はみ出しなし

### 執筆者の未解決の点について

- 制約の上限を書いていない点：計算量を N・M・Q の式で書いており、誤りはない。このままでよい
- Mo を「クエリを平方分割する方法と呼ばれることがある」：b2 の mo-algorithm の検証記録（ei1333 の記事に "Query Square Root Decomposition"）と、mo-algorithm のページの aliases に「クエリ平方分割」があることで裏付けられる。ただし同じ文の「更新のない列で」は言い過ぎ（指摘 3）
- タグを押し下げないと代入が消える：上のとおり手で確かめ、正しい
- abc219_g の解法の詳細：上のとおり乱択の突き合わせで正しい

## 指摘

1. **直すべき**｜F9 参考の URL の題名｜#references の 1 行目と 2 行目｜torus711 の記事の h1 は「AtCoder Beginner Contest 335, F : Hop Sugoroku」で、本文の「AtCoder Beginner Contest 335 : F - Hop Sugoroku」と違う。kmjp の abc219_g の記事の h1 は「AtCoder ABC #219 (サイシードプログラミングコンテスト2021) : G - Propagation」で、本文はかっこの部分を落としている｜curl で取った各記事の `entry-title-link` の文字。手引き §14-24「ブログの題名は記事の h1 を使う」｜題名を h1 のとおりに直す：`[torus711「AtCoder Beginner Contest 335, F : Hop Sugoroku」]`、`[kmjp「AtCoder ABC #219 (サイシードプログラミングコンテスト2021) : G - Propagation」]`

2. **直すとよい**｜U3 飛躍｜#heavy-light の表の 3 行目「歩幅（$N/A_i$ 歩で端に着く）」と「歩幅で分ける」の段落｜節の冒頭は「大きさの合計だけが $S$ で抑えられているとき」という枠で始まるが、歩幅は合計が抑えられた量ではない。読者は「歩幅の何の合計が抑えられているのか」で止まる。歩幅の場合に効いているのは「小さい側は歩幅の種類が $B$ 未満しかない（だから表が $B^2/2$ で済む）」「大きい側は 1 回 $N/B$ 歩以下」という別の数え方である｜節の冒頭の定義と表の列名「合計が抑えられた量」の照合｜表の前か「歩幅で分ける」の頭に「歩幅は合計の抑えではなく、小さい歩幅の種類が $B$ 未満しかないことを使う」と 1 文足す。表の列名を「分ける量」にして、3 行目を「歩幅（小さい歩幅は $B$ 種類未満）」とする案もある

3. **直すとよい**｜F2 言い過ぎ｜#query-buckets の最後の段落「こちらは更新のない列でクエリの処理順を変える方法で」｜mo-algorithm のページは時間付き Mo（点の更新がある列）を扱い、その使い分けの表に「列に点の更新がある → 時間付き Mo・平方分割」と書いている。「更新のない列で」と言い切ると食い違う｜docs/ds/mo-algorithm.md の aliases（時間付き Mo）と 269 行の表｜「こちらはクエリを先読みして処理順を並べ替える方法で（基本形は更新のない列が対象）」のように、違いを「並べ替えるか、かたまりごとに作り直すか」に置く

4. **直すとよい**｜U3・F1 見出しと本文の食い違い｜#query-buckets の見出し「√Q 個ごとに作り直し」と本文の $K = \sqrt{N / \log N}$｜見出しは √Q 個ごとと言うが、本文の例では $K$ を作り直しと質問の重さの釣り合いで決め、√Q は出てこない。読者は「√Q なのか √(N/log N) なのか」で迷う。要点の「クエリを $\sqrt{Q}$ 個ずつまとめる方法」も同じ｜本文 120・138 行と見出しの照合｜本文の最初の段落に「$K$ は作り直しの重さと補正の重さが釣り合うように決める。作り直しが $O(N)$・補正が 1 件 $O(1)$ で $N \approx Q$ なら $K \approx \sqrt{Q}$ になるので、この名前で呼ぶ」のように 1 文足す（見出しの anchor・title は catalog 由来なので変えずに済む）

5. **直すとよい**｜C3 本文との一致｜snippets/sqrt-decomposition/bucket-add-count.cpp 34・37・45 行の `count_ge(int l, int r, long long x)`｜本文は加える値を $x$、しきい値を $y$（「$y$ 以上の個数」「$a_i \ge y - \mathrm{tag}[b]$」）と書き分けているが、コードはしきい値も `x` にしており、本文の `x - tag[b]` に当たる箇所が「加える値からタグを引く」ようにも読める｜本文 53・69 行とコードの照合｜`count_ge` の引数としきい値の変数を `y` にする（コメントの「a_i + tag >= x」も `y` に）。main の読み込みはそのままでよい

6. **直すとよい**｜C2 cases｜snippets/sqrt-decomposition/bucket-add-count.yaml の 3 つ目の case｜コメントは「丸ごと入るブロック」を含むと言うが、加算 `1 1 4 10`（B = 2）は bl = 0・br = 1 で丸ごと入るブロックがなく、タグが 0 のままである。タグが 0 でない状態で `sorted` を二分探索する経路（`x - tag[b]`）を cases が一度も通らない（self_test の乱択では通る）｜手で bl・br を計算した｜加算を `1 0 5 10` のように丸ごと入るブロックを含むものに替えるか、case を 1 つ足し、期待出力を手計算で入れる

7. **直すとよい**｜G3 スマホで読めるか｜buckets.svg｜幅 360px では viewBox 720 が 0.5 倍に縮み、添字（12px）が 6px、下の説明 3 行とブロック名（13px）が 6.5px、「tag[1] += x」も 6.5px になり読みにくい（360px の PNG で確かめた）。執筆者は「小さいが読める」としているが、添字はほぼ読めない｜render_svg.py の buckets-360.png｜下の説明 3 行は代替テキストと本文にあるので図から省き、残りの文字を 18〜20px に上げる。または列を 16 から 12（N = 12、B = 4、区間 [2, 11)）に減らして viewBox を狭める（本文と代替テキストの例も合わせて直す）

8. **直すとよい**｜F10 summary との食い違い（提案）｜front matter の summary と要点の「何ができるか」｜要点は 3 つ目の方法（クエリを $\sqrt{Q}$ 個ずつまとめる）を足したが、summary は 2 つの方法のままで、索引の文と本文の冒頭が少しずれる。食い違い（矛盾）ではないので執筆者が書き換えるものではない｜手引き §2.2｜メインで summary の末尾を「…処理を変える方法、クエリをまとめて作り直す方法がある。」とする提案として扱う

## 台帳への提案（検証役から）

- abc335_f・abc219_g・abc403_g：evidence の記事で問いと方針を確かめた。checked に 2026-10-21 を入れてよい
- abc259_h：執筆者の提案（evidence に merom686 の記事を足す、approach の具体化）に同意する。記事の題名が「ABC259」で Ex の記述があることは確かめた
- abc365_g：evidence の tumblr の記事が手元で取れなかったので checked は保留。approach の提案の内容（記録の多い人は全記録を 1 回走査して前計算、少ない人どうしはマージ）は計算量の筋として正しい

## 総合の判定

小さな直しで可。直すべきは 1 件（参考の 2 件の題名を記事の h1 に合わせる）。計算量の主張・各手法の正しさ・abc219_g の解法（乱択で素朴な方法と一致）・図の内容はどれも正しい。コード片は警告・サニタイザの異常なし。
