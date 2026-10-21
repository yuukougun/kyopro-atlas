# dp-segment-tree の検証（b2）

- 対象：docs/dp/dp-segment-tree.md、snippets/dp-segment-tree/{split-abs,interval-cover,window-row}.{cpp,yaml}、docs/img/dp-segment-tree/{values-steps,split-abs}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py dp-segment-tree`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page dp-segment-tree`：エラー 0・警告 0。`npx textlint`：エラー 0・警告 34（執筆者の報告どおり）
- `python3 tools/check_snippets.py -v snippets/dp-segment-tree`：interval-cover 5 case・split-abs 6 case・window-row 6 case すべて一致。各コード片は main で素朴な DP と assert で照合しており、cases は空入力・1 要素・覆えない・作れない・大きい値（C = 10^9、P = 10^15、N = 2×10^5）を含む
- window-row の deque：先頭から末尾へ値が狭義減少（`<=` で末尾を捨てる）、左端 j − r より前を捨てる、窓が空なら読まない。本文の説明と一致
- ACL（~/lib/ac-library-master/document_ja/ の segtree.md・fenwicktree.md）：コンストラクタで全要素 e()、`set`・`prod` は O(log n)、`get`・`all_prod` は O(1)、`fenwick_tree` の `add`・`sum` は O(log n)。「ACL では」の囲みと一致
- 図 values-steps の数値：高さ (1, 3, 0, 2)・美しさ (5, 3, 4, 6) で手計算すると best は [0,5,0,0] → [0,5,0,8] → [4,5,0,8] → [4,5,11,8]、答え 11（高さ 1 と 2 の花 5 + 6）。図・代替テキスト・本文と一致。花 2 の空区間 [0, 0) と e() = 0 の説明も一致
- |x − y| の分解の式、y = x を両側に入れてよいこと、確認問題 2 の符号の説明：正しい
- 区間を覆う DP：右端の順に処理すれば x < r の dp[x] が確定していること、右端が同じ区間どうしが干渉しないこと（確認問題 3）：正しい。計算量 O(N log N + L) は木の操作が log L でも、N ≥ √L なら log L ≤ 2 log N、N < √L なら N log L = O(L) なので成り立つ
- 落とし穴の「狭義なら [0, v)、広義なら [0, v + 1)」（取得の後に更新するとき）、確認問題 1 の「値の小さい順に処理し、同じ値は位置の大きい順」：正しい
- 「容量 K の袋…」の形（abc334_f）：dp[i] = min_{i−K ≤ j < i} dp[j] + dist(S, P_{j+1}) + (D_i − D_{j+1}) + dist(P_i, S) で、j だけの項と i だけの項に分かれるので、本文の主張どおりスライド最小値で取れる。Kazun 氏の記事も i だけの項を min の外に出している（記事自体は遅延セグメント木）
- **ABC410 G の方針（執筆者の未解決の点 1）**：Python で全探索（新しい弦の端点を点の間のすべての組で試し、交わる弦から互いに交わらない部分集合の最大を取る）と、本文の方針（各弦を [x, y) と [y, x + 2N) にし、右端の昇順に、左端が (x, y) にある dp の最大 + 1 を位置 x に書く）を、N ≤ 5 のランダムな 3000 例で比べて全一致。各弦を 2 つの区間だけにしてよいこと（[x + 2N, y + 2N) が要らないこと）も、点 0 の位置で切る側を選べば足りることを手で確かめた。kmjp 氏の記事の 2 周分に開く・右端の順・区間最大の木の方針とも一致
- 例題・練習・力試しの 7 問：`tools/ap.py show` で題名・diff（abc353_g 1765・abc339_e 1109・abc359_e 1275・arc026_3 1930・abc410_g 2242、dp_q・typical90_ak は diff なし）を確かめ、本文と一致。要約は台帳の summary と一致し、手法名を含まない
- dp_q：Series_205 氏の記事で、制約（N ≤ 2×10^5、h_i は 1〜N で相異なる）・状態・1 本の配列の使い回し・BIT でも書けることを確かめた
- typical90_ak：E869120 氏の sol/037.cpp で、状態・前の段を区間最大の木に載せる遷移・作れない状態を番兵にして足さない・作れなければ −1 を確かめた。配列 dp[509][10009] から N ≤ 500・W ≤ 10^4 程度と読め、O(NW log W) は間に合う（本文は数値を書いていないので問題なし。執筆者の未解決の点 3）
- abc353_g：drken 氏の記事で、N, M ≤ 2×10^5、町 0 に 0・ほかは −∞、C·j を足す木と引く木の 2 本、答えは全部の町の最大、を確かめた。本文と一致。C・P_i の上限は記事の取得した範囲になく、本文の「大きくなりうるので long long」で足りる（執筆者の未解決の点 2）
- arc026_3：drken 氏の記事で、半開区間 [l, r) で [0, L) を覆う、dp[0] = 0、右端でソート、区間最小の木、O(L + N log L) を確かめた。本文と一致
- 参考の題名（執筆者の未解決の点 4）：drken 氏の記事の h1 はそれぞれ「AtCoder ABC 353 G - Merchant Takahashi (2D, 青色, 550 点)」「AtCoder ARC 026 C - 蛍光灯 (試験管青色)」「EDPC (Educational DP Contest) Q - Flowers」で、本文の表記と一致。kmjp 氏「AtCoder ABC #410 (CodeQUEEN 2025 予選) : G - Longest Chord Chain」、Series_205 氏「Educational DP Contest (EDPC) P ~ S 問題 解説」、Kazun 氏「AtCoder Beginner Contest 334 F問題 Christmas Present 2」も一致。ドメインはすべて手引き付録 B にある
- リンク先の anchor（monotonic-stack の sliding-window-minimum・dp-transition・abc359_e、segment-tree-on-values#dp-on-values、dp-prefix-sum#prefix-min、lis#segment-tree、coordinate-compression#with-ds、glossary#identity-element）はすべて存在する。cht・dp-speedup-overview は stub だがリンクは有効
- 図：両方とも白背景・viewBox あり・font-family="sans-serif"・相対パスで参照。720px では文字の重なり・はみ出しなし。split-abs は実線・破線と色の両方で左右を区別しており、色覚の違いでも読める

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact F7・clarity U3 | interval-cover の節の最後「応用の型」の最後の文 | 「区間の重なりの深さを数える DP（力試しの ABC410 G）」の「重なりの深さ」は、ふつう「1 点を覆う区間の数の最大」を指す。ABC410 G で求めるのは入れ子の深さ（力試しの方針の折りたたみも「入れ子の深さ」）で、読者が別の量と取り違える | 力試しの方針の折りたたみ・kmjp 氏の記事（ネストの深さ） | 「区間の入れ子の深さを求める DP」とする |
| 2 | 直すとよい | fact F2 | interval-cover の節の冒頭（状態の定義の前後） | 費用が非負であることの断りがない。負の費用があると、覆うのに要らない区間も選んだ方が得になり、右端をつなぐ鎖だけを見るこの DP は最小を返さない | 反例：[0, 2) を覆う。区間 [0, 2)（費用 1）と [0, 1)（費用 −5）。最小は両方選ぶ −4 だが DP は 1 | 冒頭に「費用 $c_i \ge 0$ とする」を足す |
| 3 | 直すとよい | clarity U4 | values-on-segment-tree の処理の流れ（```text の 4〜5 行目） | 「cur ← seg.prod(l, r) が −∞ でなければ、それ + c_i」は、−∞ のときに cur がどうなるか（更新を飛ばすのか）が書かれていない。読者が擬似コードから書くと次の行で未定義の cur を使う | 擬似コードを読んで | 「v ← seg.prod(l, r)。v が −∞ なら更新しない（次の i へ）」「cur ← v + c_i」の 2 行に分ける |
| 4 | 直すとよい | clarity U3 | values-on-segment-tree の「計算量」の最後の文 | 「葉の数は $O(V)$」の $V$ が定義されていない | 本文を読んで | 「値の上限を $V$ として、葉の数は $O(V)$」とする |
| 5 | 直すとよい | fact F1 | split-abs の節の計算量と、例題 abc353_g の方針 | 節では「全体 $O(N + M \log N)$」、例題の方針では「全体 $O((N + M) \log N)$」で、同じ解き方の計算量の書き方がそろっていない（どちらも上界としては正しい） | 本文 109 行目と 230 行目 | 例題の方針も「木の構築 $O(N)$、市場 1 つにつき $O(\log N)$ で、全体 $O(N + M \log N)$」にそろえる |
| 6 | 直すとよい | figure G3 | values-steps.svg（幅 360px） | 360px の PNG では、列見出しの「高さ 0〜3」、右側の注記（「[0, 1) の max = 0」など）、凡例の文字が 6〜7px ほどに縮み、読みにくい。720px では問題ない | render_svg の values-steps-360.png を目視 | 右側の注記を各段の下へ移して横幅を詰める（viewBox を 520 幅程度に）か、文字を大きくする |
| 7 | 直すとよい | fact F9 | 参考の drken 氏「EDPC (Educational DP Contest) Q - Flowers」 | 「例題 dp_q の値を添字にした遷移」とあるが、記事本文（取得した範囲）は重み付き LIS と見るとだけ書き、状態・遷移は別の記事へのリンクに任せている。遷移は Series_205 氏の記事で確かめられる | 記事を取得して確かめた | 参考にした点を「重み付き LIS として見る見方」に直すか、この行を外す |

## 執筆者の未解決の点について

- abc410_g の方針：全探索との照合で正しいことを確かめた（上の「確かめたこと」）。直しは要らない
- abc353_g の C・P_i の上限、typical90_ak の N・W の上限：本文に数値を書いていないので問題なし
- drken 氏の記事の題名：3 件とも h1 と一致
- 動く図を作らず静的な SVG 2 枚にしたこと：catalog の visual の優先度に合うかはメインが決める。静的な図 2 枚は前後の文章だけでも要点が通じる
- which-tool と comparison：手引き §14-2 の対象に which-tool を入れるかはメインの判断。中身は使い分けの役を果たしており、ページの内容としては問題なし

## 台帳への提案

- dp_q：checked に 2026-10-21（Series_205 氏の記事で制約・状態・遷移を確かめた）
- typical90_ak：evidence に https://github.com/E869120/kyopro_educational_90/blob/main/sol/037.cpp を足し、checked に 2026-10-21
- arc026_3：checked に 2026-10-21（drken 氏の記事で半開区間・状態・遷移を確かめた）
- abc353_g・abc410_g：checked はすでに 2026-10-21。内容は上のとおり確かめた
- abc410_g の approach の提案（執筆者）は、全探索との照合で正しいので採ってよい

## 総合の判定

小さな直しで可。直すべき 0 件・直すとよい 7 件。数値・コード・計算量・問題の方針に誤りは見つからなかった。
