# partition-number の検証（b3）

- 対象：docs/comb/partition-number.md、snippets/partition-number/{partition,cycle-type,count-multiset}.{cpp,yaml}、docs/img/partition-number/young-5.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py partition-number`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目で確かめた
- atcoder.jp・codeforces.com は開いていない。web.archive.org は WebFetch で取れず、ikatakos.com は 503（保守中）で読めなかった

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page partition-number`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page partition-number`：直すべき行 0
- `python3 tools/check_snippets.py -v snippets/partition-number`：3 片・17 case すべて一致。コード片はどれも自分の中で全列挙（partition は再帰の葉の数、cycle-type は n ≤ 8 の全順列、count-multiset は n ≤ 30 の全分割）と assert で照合しており、期待出力は写しではない
- 表の数値：Python で p(n) と Σ_{s≤n} p(s) を計算し、n = 10, 20, 30, 40, 50, 60, 80, 100 の 16 個の値すべてが本文の表と一致。節点 / 葉 の比は n = 30〜80 で 5.1〜7.8（本文「5〜8 倍ほど」どおり）。p(50)/p(40) = 5.47、p(60)/p(50) = 4.73（「10 増えるごとに 5 倍ほど」どおり）。Hardy–Ramanujan の式も本文どおり（n = 50 で 2.18×10^5）
- そのほかの値：2^29 ≈ 5.4×10^8、2^49 ≈ 5.6×10^14、B_12 = 4213597、p(12) = 77、p(4) = 5、p(6) = 11、Landau の g(50) = 180180、和が 50 の分割の lcm の種類数 1056（全列挙で計算）。すべて本文どおり
- 漸化式と全単射：p(n,k) = p(n,k−1) + p(n−k,k)、共役（折り返し）による「部分 ≤ k」＝「個数 ≤ k」、ちょうど k 個 = p(n−k,k)、玉と箱（空を許す p(n,k)・許さない p(n−k,k)）、最小の部分が 1 かどうかの dp[k][s] = dp[k−1][s−1] + dp[k][s−k]、個数の上限 M の引く項 dp[k−M−1][s−k] の導出（M 個の 1 を持つものに 1 を足す分が、残り k−M−1 個から 1 ずつ引いて和 s−k に対応）：正しい。kmjp の記事の漸化式 f(n,s) += f(n,s−n)、f(n−1,s−1) − f(n−(M+1), s−n) と一致
- 巡回型の数 N!/Π(ℓ^{m_ℓ} m_ℓ!)、N = 4 の表（6・8・3・6・1、計 24）、確認問題の 40・45：正しい
- 確認問題 p(5,3) = 5（p(5,2) = 3、p(2,3) = 2）、6 の分割 11 通りとちょうど 3 個の 3 通り、7 個の玉 3 箱の 8 通り・4 通りと各列挙：正しい
- 計算量：要点・front matter の complexity・本文（O(nk)、節点 Σp(s)、例題 O(p(N) log K) + 節点、O(TK·M p(M))、ABC221 H の O(N^2)）が互いに一致
- 例題・力試し：`tools/ap.py show` で abc226_f（F. Score of Permutations・2086）、abc404_f（F. Lost and Pound・2162）、abc221_h（H. Count Multiset・2793）を確認。要約に手法名なし
- abc226_f の方針（巡回型の全列挙、lcm を整数で持つ、g(50) = 180180）は sansaqua の記事、別解の DP（巡回の長さを決めて lcm で遷移）は yamate11 の記事と食い違いなし（yamate11 は最小番号ではなく最大の要素 n を含む巡回で数えているが、同じ考え方で、本文の「最小の番号を入れる」も正しい）
- abc221_h の方針は kmjp の記事と一致。記事の配列 5050×5050 から N は 5000 程度で、O(N^2) と「int の 2 次元配列」のメモリの注意は妥当
- abc404_f：merom686 の記事に「毎回ボタンの区別がなくなる」「当たりを押した回数で T と K が減る小さい問題になる」「30 が絶妙で分割の数が多くない」とあり、本文の方針（押し方を M の分割として全列挙）と食い違いなし
- 参考の URL：drken「分割数と、問題まとめ」（題名・漸化式・k 個の分割は P(n−k,k)・上限付きの漸化式を確認）、sansaqua、yamate11、kmjp、merom686 は内容が書かれたとおり。check_noai で yamate11.github.io・competitive12.blogspot.com・kmjp・merom686・ikatakos.com はどれも指定なし
- リンク先：counting-dedup#representative・#min-index、bell-number#size、permutation-cycles#power、knapsack-01#knapsack-unbounded、complexity-estimation#count-candidates はどれも存在（相手は draft）。twelvefold-way・stirling-first・generating-function-counting・young-tableaux は stub でページへのリンクのみ
- コード：手引き §9 の DFS の形（`auto dfs = [&](auto&& self, ...) -> void`）、'\n'、マクロ・型の別名なし。mint は ACL v1.6 の modint998244353 で、`val()` を出力にだけ使う。cycle-type の lcm は long long で 180180 以下、mint(l).pow(k) は k が long long で可。1/x・1/c の逆元は法 998244353 > N なので存在する
- 図：catalog の visual（static・priority 2「n = 5 の 7 通りを Young 図形で並べる」）を満たす。7 つの形・ラベル（最大・個数）は本文の列挙と一致。白背景・viewBox・font-family="sans-serif"・相対パス。代替テキストに 7 通りと読み方がある
- F6：前提（recursive-enumeration・dp-basics・permutation-cycles）で足りる。発展の節（partition-dp）は冒頭でナップサック DP を前提と断っている
- F8：本文の例（n = 5・6・7、N = 4 の巡回型、N = 40 の見積もり）は参考の記事の写しではない

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact F3 | 落とし穴「p(0) = 1 を忘れる」 | 「すべての値が小さくなる」は弱すぎる。p(0,k) を 0 のままにすると、p(1,1) = p(1,0) + p(0,1) = 0 から始まって表の全部が 0 になる。読者が自分の誤りに気づく手がかり（全部 0 が出る）として、そう書く方が役に立つ | 表を p[0][k] = 0 のまま埋めると p(10,10) = 0（Python で確認） | 「すべての値が 0 になる」とする（recurrence の節の「数えそこなう」の文にも「その結果、表全体が 0 になる」と足すとよい） |
| 2 | 直すとよい | code C3 | partition-dp の節と count-multiset.cpp:core | 本文は $\mathrm{dp}[k][s]$ と上限 $M$、コード片は `f[k][s]` と `m`。記号がそろっていない | 本文 178〜193 行とコード片の変数名 | コード片の `f` を `dp` に、コメントの `m` を本文の $M$ に合わせて「同じ値は M 個以下（入力の m）」と書く。入力変数を `m` のままにするなら本文に「コードでは m」と添える |
| 3 | 直すとよい | figure G5 | young-5.svg（上の段） | 上の段の形は高さが最大 3 行なのに、ラベルの位置が 5 行分の高さに合わせてあり、形とラベルの間が大きく空く（360px でとくに目立つ）。どのラベルがどの形のものかは読めるが、上の段のラベルが下の段の形に近く見える | render_svg の young-5-360.png・young-5-720.png を目視 | 上の段のラベルを y ≈ 95・117 程度へ上げ、段の間隔を詰める（viewBox の高さも縮む） |
| 4 | 直すとよい | fact F5 | 例題 abc404_f の解法の詳細（状態の数 O(TK)） | K の上限を確かめられなかった（ikatakos.com は 503、web.archive.org は取得できず、ほかの公開記事に F の記述なし）。K が M·T 程度まで大きい場合でも、残りで押せる回数 t·M より k が大きい状態は 0 なので、状態を k ≤ t·M に絞れることを一言足すと見積もりが安全になる | merom686 の記事・検索で見つかった記事（zenn・fkgtinfo・note）に制約の記述なし | 「$k > tM$ なら $f(t,k) = 0$ で、調べなくてよい」を 1 文足す。台帳に入れる前に、メインが ikatakos の記事が戻ったときに N・M・T・K の上限を確かめる |

## 執筆者の未解決の点について

- abc226_f の N ≤ 50：sansaqua の記事の g(50) と、yamate11・ikatakos の見積もりから N = 50 程度と読める。本文の主張（p(50) 通り以下で全列挙が間に合う）と矛盾しない。K の上限は本文に要らない（O(log K) とだけ書いている）
- abc404_f の M ≤ 30：merom686 の「30 というのが絶妙」「分割数がそんなに多くない」と合う。N・T・K の上限は確かめられなかった（指摘 4）
- abc221_h の N：kmjp のコードの 5050×5050 から N ≤ 5000 程度。O(N^2) とメモリの注意は妥当（int なら約 100MB）
- Library Checker の Partition Function：本文は制約の値を書いておらず、「n = 10^5 程度まで」は一般の目安として問題ない。問題の囲みの外の言及だが、atcoder の問題ではなくリンクもないので check_pages も通る
- web.archive.org の扱い：今回の検証では WebFetch で取得できなかった。付録 B に足すかはメインの判断（検証の環境では使えないので、台帳の evidence は merom686 などの直接読める URL を併記するのがよい。執筆者の提案に同意）

## 台帳への提案

- abc404_f：summary を執筆者の案（本文の要約と同じ文）にする。evidence に merom686 の記事を足す（執筆者の提案に同意）。checked はまだ入れない（制約を確かめられていない）
- abc226_f：evidence に competitive12.blogspot.com と yamate11.github.io を足す（執筆者の提案に同意。方針を確かめた）。checked に 2026-10-21
- abc221_h：checked に 2026-10-21（kmjp の記事で問いと漸化式を確かめた）

## 総合の判定

小さな直しで可（直すべき 0・直すとよい 4）
