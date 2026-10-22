# multiplicative-function の検証（b4）

対象：docs/math/multiplicative-function.md、snippets/multiplicative-function/lucy.{cpp,yaml}、phi-sum.{cpp,yaml}。観点：fact.md・code.md・clarity.md・figure.md（図はなし。catalog の visual が null なので figure.md は該当なし）。

## 実行したこと

- `python3 tools/check_pages.py --page multiplicative-function`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/multiplicative-function`：2 片とも期待どおり（lucy 3 case・phi-sum 4 case）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- 手で `-std=gnu++23 -O2 -Wall -Wextra` と `-O1 -fsanitize=address,undefined` でコンパイルした。サニタイザ付きで lucy（N = 10^6・99999999）と phi-sum（N = 10^6）を動かし、出力は正しく（78498・5761455・497269080）、エラーはなかった
- 実行時間：lucy は N = 10^10 と 10^11 を合わせて 0.235 秒、phi-sum は N = 10^10 で 0.22 秒。本文の「0.3 秒以内」と合う
- 素数の和を `__int128` の Lucy DP で計算した（一時置き場の psum.cpp）。N = 10^10 以下の素数の和は 2220822432581729238 で、LLONG_MAX = 9223372036854775807 より小さい（指摘 1）
- N = 10^10 の Lucy の手計算の例（S(10) = 5 → 4、S(5) = 3）と、確認問題 1 の N = 27 の例を Python で確かめた。大きい x から更新すると π(27) = 9、p = 3 の段だけ小さい x から更新すると 10 になり、S(9) は 5 から 4 になる。本文と合う
- Library Checker の 4 問の問いと制約を GitHub の task.md・info.toml で確かめた。counting_primes は N_MAX = 10^11、sum_of_totient_function は N_MAX = 10^10 で mod 998244353、sum_of_multiplicative_function は f(p^e) = ae + bp・MOD = 469762049・T = 1 なら N ≤ 10^11、counting_squarefrees は N_MAX = 10^18。どれも本文と一致する
- Nyaan のライブラリ 4 ページを読んだ。prime_counting・sum_of_totient・mf_prefix_sum の名前、Min_25 の要件（素数での値が多項式）と O(N^{1−ε}) の追記は本文と一致する。O(N^{2/3}) の素数カウントは「Min_25 氏の記事およびツイートを参考にした実装」とあり、Meissel-Lehmer の系統とは書かれていない（指摘 3）
- OI Wiki の Min_25 篩：再帰の方法（第一種）は O(n^{1−ε})、もう一つの方法は O(n^{3/4}/log n) と書かれている。本文の書き方と合う
- ディリクレ積の関係（1 * 1 = d、id * 1 = σ、φ * 1 = id、μ * 1 = ε、μ * id = φ）、gcd(i, j) = 1 の組の個数 2Σφ − 1、N^{2/3} ≈ 4.6 × 10^6、杜教篩の計算量（前計算ありで O(N^{2/3})、なしで O(N^{3/4})）、メモの添字 k = ⌊N/m⌋ が一意になること、counting squarefrees の式 Σ μ(d)⌊N/d²⌋：どれも正しい
- コード片の更新順：lucy の hi は k の小さい順なので、読む hi[d]（d = kp > k）はまだ更新前。lo は x の大きい順なので lo[x/p] も更新前。正しい。phi-sum の res への引き算は 1 回あたり MOD 未満で、項の数は 2√N 程度なので long long であふれない
- abc370_g（執筆者の補充の候補）は ap.py で実在・題名・diff 3428 を確かめた

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2 | #prime-counting「自作するときの要点」の「素数の和」（108 行） | 「$N = 10^{10}$ の素数の和は `long long` を超える」は誤り。答えは約 $2.2 \times 10^{18}$ で `long long` に収まる。超えるのは初めの値 $x(x+1)/2 - 1$（$x = 10^{10}$ で約 $5 \times 10^{19}$）と途中の値である | `__int128` の Lucy DP で計算すると、10^10 以下の素数の和は 2220822432581729238。LLONG_MAX は 9223372036854775807 | 「初めの値 $x(x+1)/2$ が $N = 10^{10}$ で約 $5 \times 10^{19}$ になり `long long` を超えるので、mod を取るか `__int128` にする（答えそのものは約 $2.2 \times 10^{18}$ で収まる）」のように直す |
| 2 | 直すべき | fact F2・clarity U3 | #prime-counting の 2 段落目（84 行） | $S(x, p)$ は「素数であるか、最小素因数が $p$ より大きい」数の個数と定義しているのに、言い換えが「篩で $p$ **未満**の素数の倍数を消し終えた後に残っている数の個数」になっている。$p$ 自身の倍数も消えた後の個数なので、「$p$ 以下」が正しい。すぐ後の「$p^2 \le x$ なら新しく消えるのは最小素因数がちょうど $p$ の合成数」とも食い違い、読者がどの段の値か迷う | 定義から、$S(x, p)$ では最小素因数が $p$ 以下の合成数がすべて除かれている。$S(10, 2) = 5$（2・3・5・7・9）は 2 の倍数を消した後の個数である | 「篩で $p$ 以下の素数の倍数（素数自身は残す）を消し終えた後に残っている数の個数」に直す |
| 3 | 直すとよい | fact F2 | #prime-counting の最後の段落（110 行） | 「$O(N^{2/3})$ 程度のさらに速い方法（Meissel-Lehmer 法を改良した系統）」の括弧の中は、参考の資料で裏付けられていない（執筆者の未解決の点 1） | Nyaan「素数カウント(O(N^{2/3}))」は「Min_25 氏の記事およびツイートを参考にした実装」とだけ書き、Meissel-Lehmer には触れていない。Wikipedia の記述は Meissel-Lehmer 法の経緯だけで、この実装との関係までは言っていない | 括弧を消し、「$O(N^{2/3})$ 程度のさらに速い方法もある」にする。参考の Nyaan「O(N^{2/3})」の注記はそのまま、Wikipedia の注記の「Meissel-Lehmer 法の経緯」は本文で使わないなら消す |
| 4 | 直すとよい | fact F1 | 要点の「計算量」・front matter の complexity・#comparison の表の Min_25 篩の行 | 本文（#prefix-sums）は「実装しやすい再帰の形では $\Theta(N^{1-\varepsilon})$」と断っているのに、要点と表は「$O(N^{3/4}/\log N)$ 程度」だけである。辞書として要点だけを引く読者には、ふつうの実装の計算量が伝わらない | OI Wiki の Min_25 篩（第一種の方法は O(n^{1−ε})）、Nyaan「乗法的関数の prefix sum」の追記（葉でないノードの個数は O(N^{1−ε})） | 要点・complexity・表を「$O(N^{3/4}/\log N)$ 程度（再帰の実装は $\Theta(N^{1-\varepsilon})$ だが $N \le 10^{11}$ では十分速い）」などにそろえる。表の幅が気になるなら、表は「#prefix-sums を参照」の注を付けるだけでもよい |
| 5 | 直すとよい | fact F2 | #prefix-sums の Min_25 篩、「合成数を足す」（146 行） | 「素数でない数は $\sqrt{N}$ 以下の素因数を必ず持つ」は 1 に当てはまらない（1 は素数でないが素因数を持たない）。言いたいのは合成数のこと | 1 は素数でも合成数でもない | 「$N$ 以下の合成数は $\sqrt{N}$ 以下の素因数を必ず持つ」に直す |
| 6 | 直すとよい | fact F4 相当（外部ライブラリの使い方）・clarity U4 | #prefix-sums の最後の段落（150 行） | 「`mf_prefix_sum`（$f(p^e)$ を返す関数を渡す）」だけでは使い方が足りない。実際は `f(p, c)` をテンプレート引数の関数ポインタで渡し、素数での値の和の表（`pi_table()`・`prime_sum_table()` を組み合わせて作る）を `run()` に渡す必要がある | Nyaan「乗法的関数のprefix sum」のコード：`template <typename T, T (*f)(long long, long long)> struct mf_prefix_sum`、`T run(const vector<T>& Fprime)` | 「`mf_prefix_sum`（$f(p^e)$ を返す関数をテンプレート引数に渡し、`pi_table()`・`prime_sum_table()` から作った素数での和の表を `run` に渡す）」のように一言足す |

## 問題ないと確かめた点（参考）

- code C1〜C8：警告なし、サニタイザで問題なし、cases は境界（N = 1・2・3、小さい値、最大の制約 10^10・10^11）を含み、main の中で素朴な方法と assert で照らしている。期待値の π(10^10)・π(10^11) は Wikipedia の表の値、Σφ の期待値は Python の多倍長で別に計算したものと yaml にある。取り込みの範囲は core だけで、本文の `lo`・`hi`・$S$ の記号とそろう。書き方の決まり（`bits/stdc++.h`・マクロなし・`'\n'`）も守っている
- fact F5：例題・練習の AtCoder の問題はなく、問題の囲みもない。Library Checker の 4 問の要約は問いと制約だけで、解き方は「〜の確かめに使う」の範囲（Counting Squarefrees だけ式を書いているが、手法の確かめの練習の説明として許容範囲）
- fact F6：μ・線形篩・メモ化再帰・調和級数はリンクで手当てされている。prerequisites（euler-phi・floor-quotient-enum）と related の範囲で足りる
- fact F8：Lucy DP のコード片は Nyaan の `pi_table` と処理の形が同じ（大きい商は配列の添字 k、小さい値は x で持ち、`k * p` で参照する）だが、Lucy DP の標準の形であり、変数名・コメント・関数の分け方は独自である。本文の文章も参考の資料と言い回しが重ならない
- fact F10：front matter の変更は complexity・stage・updated と、sections の title・並び（§15-2・§15-11 で執筆者に許されている）だけ。要点と summary は食い違わない。別名の行に aliases がすべてある
- clarity：要点の「いつ使うか」が制約の形（N ≤ 10^10〜10^11）で書かれ、冒頭だけで引ける。各節は単独で読んで何の話か分かる。確認問題 2 問はどちらも本文の主張を別の場合に当てる問いで、答えに理由がある。発展の概要として、Lucy DP は手で回せる粒度、杜教篩・Min_25 篩は概要とライブラリ案内に絞っていて、レベルに合っている

## 執筆者の未解決の点への回答

1. Meissel-Lehmer の系統か：資料では確かめられない。指摘 3 のとおり括弧を消すのがよい
2. Min_25 篩の $\Theta(N^{1-\varepsilon})$：OI Wiki（第一種の方法は O(n^{1−ε}) と証明されている）と Nyaan の追記の両方で確かめた。本文の書き方でよい（要点との食い違いは指摘 4）
3. mobius-function#quotient の「杜教篩で O(N^{2/3})」：本ページの記述（前計算ありで O(N^{2/3})、なしで O(N^{3/4})）は正しい。mobius-function の 181 行は「篩なしで求める」と書いた直後に「O(N^{2/3})」とあり、N^{2/3} までの篩の前計算が要ることと読み違えやすい。メインの判断で「N^{2/3} までを篩で前計算すれば」と添えるとよい（このページの指摘ではない）
4. Counting Squarefrees の式：$\sum_{d \le \sqrt{N}} \mu(d) \lfloor N/d^2 \rfloor$ は正しい（包除原理で、$d^2$ で割り切れる数を μ の符号で足し引きする）。計算量を書かないのは練習の要約として妥当

## 総合の判定

小さな直しで可。直すべき 2 件（指摘 1・2）、直すとよい 4 件（指摘 3〜6）。どれも 1 文の直しで済み、コード片は直さなくてよい。
