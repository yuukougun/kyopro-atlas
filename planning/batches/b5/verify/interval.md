# b5 検証：interval

- 対象：docs/patterns/interval.md、docs/img/interval/subarrays-as-points.svg（snippets はなし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：図は `python3 tools/render_svg.py interval` で 360px・720px の PNG にし、`--bg '#1e2129'` でも撮って目で確かめた。コード片も擬似コードもないので code.md の C1〜C8 は対象なし

## 実行して確かめたこと

- `python3 tools/check_pages.py --page interval`：エラー 0・警告 0。`npx textlint`：エラー 0・警告 24（`[l, r)` の括弧の対応・文の長さ・読点の数。執筆者の報告どおり）
- リンク先の anchor：本文の `../` で始まる 51 個のリンク（prefix-sum#half-open・#circular、prefix-sum-counting#equal-k・#same-remainder、two-pointers#two-types・#negative-values、monotonic-stack#contribution・#histogram、contribution#max-min-count、fractional-binary-search#median・#median-of-medians、inversion-number#sliding-window、dp-sequence-partition#last-block・#two-pointers・#vs-interval-dp、interval-dp#split-point・#ends・#last-operation、imos#imos-1d・#large-coordinates・#online、fenwick-tree・segment-tree・lazy-segment-tree・sparse-table・mo-algorithm の #what-it-does、segment-tree-monoids#pattern-table、sparse-table#idempotent、difference-sequence#to-point-operations・#min-operations、offline-queries#distinct-count・#threshold・#online、interval-scheduling#why-right-end・#stabbing・#weighted、interval-set#representation・#applications、event-sort#make-events、sweep-line-2d#intervals-as-points、glossary の 6 語）をスクリプトで照らし、すべてある。リンク先の節の中身と本文の説明も食い違わない（interval-dp#last-operation の「左端と一緒に消える相手」、mo-algorithm の O(N√Q) など）
- 数値と性質（作業用の場所の Python）：
    - 図の例 A = (1, 3, 2, 4, 5, 0) で、A[2] = 2 が最小になる区間を全列挙すると 6 個。(2−0)×(5−2) = 6 と一致。N(N+1)/2 = 21、N = 2×10^5 で約 2×10^10 も一致
    - 区間への +1 だけで A を作る最小回数を BFS の全探索で求め、Σmax(d_i, 0) と負の差分の和の絶対値の両方と一致（長さ 1〜4・値 0〜3 のランダム 200 件）
    - 全区間の最小値の和を、左は「より小さい」・右は「以下」で止めた (i−L_i)(R_i−i) で数え、全列挙と一致（同じ値の多いランダム 500 件）
    - 全区間の mex の和 ＝ Σ_{k≥1}「0〜k−1 をすべて含む区間の数」を全列挙と照らして一致
    - 閉区間の交わる数 ＝ 全体 −「R < p」の数 −「L > q」の数を全列挙と照らして一致（2 つが同時に起きないことも L ≤ R・p ≤ q から確かめた）
- 計算量：要点・front matter の complexity・本文が一致（累積和は前計算 O(N)・1 回 O(1)、BIT・セグメント木は 1 回 O(log N)）。本文の各節の計算量（連想配列 O(N log N)・ハッシュ期待 O(N)、尺取り O(N)、単調スタック O(N)、区間 DP の O(N^3)・O(N^2)、いもす O(N+Q)、Sparse Table 前計算 O(N log N)・1 回 O(1)、Mo の伸縮 O(N√Q)、区間の set のならし O(log N)）もリンク先のページと合う
- 問題：
    - ABC189 C：ikatakos 氏の記録の解法の節で、ヒストグラムの最大長方形と見る言い換え、制約から O(N^2) の全探索が通ること、スタックで O(N) になることを確かめた。要約・練習の方針と一致
    - ABC265 D（執筆者の未解決の点 1）：dhirabayashi 氏の Zenn の記事（https://zenn.dev/dhirabayashi/articles/557bbf51c35edf ）の D の節に「A_i は 1 以上なので累積和の配列は単調増加」とあり、方針の「値が正なので累積和は狭義に増える」は正しい。oraclesqlpuzzle の記事も累積和の配列の二分探索で、A_i が正であることを前提にしている。台帳の evidence にこの Zenn の記事を 2 つ目として足す提案に使える
    - ABC457 E（未解決の点 2）：ikatakos 氏の記録の解法の節（問題文の節は使っていない）で、マスの閉区間で「左端 S の布と右端 T の布がすき間なく（y+1 ≥ x）つながる」形と「[S, T] そのものの布とその内側の布」の 2 通り、左端ごと・右端ごとのソートした一覧、T の順の走査と二分探索、通過した布の左端の最大値で判定する手順を確かめた。練習の方針と一致。2 個の和集合が [S, T] になるのは「左端の最小が S・右端の最大が T」で、それを 1 個が両方持つか 2 個が分け持つかの 2 通りに限られることも自分で確かめた。要約に手法名・解き方は入っていない
    - 台帳への提案：abc189_c・abc265_d・abc457_e の checked に 2026-10-22。abc265_d の evidence に上の Zenn の記事を足す。abc457_e の summary は台帳でまだ「（執筆時に確かめる）」なので、執筆者の提案（本文の要約と同じ文）の反映を忘れないこと
- 参考の URL：ikatakos.com・oraclesqlpuzzle.ninja-web.net は付録 B にある。3 件とも題名・内容が書かれたとおり。ikatakos 氏の記録は解法の節だけを読んだ。zenn.dev も付録 B にある
- 出典に近すぎないか（F8）：図の例・各節の文の並びは参考の記事と別。ABC457 E の方針は解法の手順の言い換えで、文の並びはそのままではない
- 図：点の位置・赤い長方形（l ∈ {1, 2}・r ∈ {3, 4, 5}）・緑の破線（r = 6 の行）が本文・代替テキストと一致。viewBox 400×400 と width・height が同じ比、白の背景、font-family sans-serif。360px で文字は約 12px で読め、重なり・はみ出しなし。暗い背景でも白の地の上で読める。赤（実線）と緑（破線）は線の種類でも区別できる。catalog の visual（priority 2、(l, r) の 2 次元の点として三角形の領域を見せる）を満たす
- 執筆者の未解決の点 3（60 字を超える見出し）：60 字を超えるのは online-updates（68 字）と offline（67 字）の 2 つ。指摘 5
- 執筆者の未解決の点 4（monotonic-stack の練習に abc189_c がない）：docs/ds/monotonic-stack.md に abc189 の行はない。台帳では monotonic-stack の practice なので、このページの問題ではなく monotonic-stack 側の扱いとしてメインが確かめること

## 指摘

### 1. 直すべき｜事実（F3）｜#pitfalls の「答えの大きさ」（226 行）

- **問題**：「全区間の和は N = 2×10^5・値 10^9 で約 2×10^19 に届き、long long を超えうる」とある。「全区間の和」は、寄与のページ（thinking/contribution.md 50 行）の「すべての区間の和の総和」と同じ意味に読める。その意味なら値は約 1.3×10^24 で、5 桁ずれる。しかも long long を「超えうる」のではなく必ず超える。2×10^19 は「区間の数 2×10^10 × 1 区間あたり 10^9 以下の値」の見積もりで、全区間の最小値・最大値の総和にしか当てはまらない
- **根拠**：Σ_i a_i(i+1)(N−i) で、Σ_i (i+1)(N−i) = N(N+1)(N+2)/6 ≈ 1.33×10^15。これに 10^9 を掛けると約 1.3×10^24。区間の数は N(N+1)/2 ≈ 2×10^10 なので、1 区間あたり 10^9 以下の量（最小値など）の総和は 2×10^19 以下になる
- **直し方**：「全区間の最小値（最大値）の総和は、区間が N(N+1)/2 個あるので N = 2×10^5・値 10^9 で約 2×10^19 に届き、long long（約 9.2×10^18 まで）を超えうる。全区間の和の総和なら約 10^24 で必ず超える。mod を取るか `__int128` を使う」のように、どの量かを書き分ける

### 2. 直すとよい｜事実（F2）・分かりやすさ（U3）｜#monotone-window の 2 段落目（135 行）

- **問題**：「値に負の数があると……そのときは和が K の区間の個数と同じく累積和の差で数える」とある。この節の主題の「和が K 以下」の数は、#count-by-sum の連想配列では数えられない。S_l ≥ S_r − K となる l を数えるので、座標圧縮と BIT（または順序付きの集合）が要る。リンク先の two-pointers#negative-values はそう書いているが、このページだけを読むと連想配列で足りると読める
- **根拠**：docs/basics/two-pointers.md の #negative-values（「和が K 以上」は座標圧縮して BIT で O(N log N)）
- **直し方**：「そのときは累積和の差で、端を 1 つ固定して相手を数える。ちょうど K なら連想配列、K 以下・以上なら累積和を座標圧縮して BIT で O(N log N)（負の値があるとき）」とする

### 3. 直すとよい｜分かりやすさ（U7）｜#containment の最後の段落（214 行）

- **問題**：「2 つの区間の組で決まる条件も、片方の端点で並べて走査し、もう一方を二分探索で探す形に直せることが多い（ABC457 E）」は、練習の問題の解き方を折りたたみの外で明かしている。checklists/clarity.md の U7 にある「本文が練習の問題を指して、その解き方を折りたたみの外で書く」に当たる
- **根拠**：clarity.md U7、手引き §10（練習の方針は一覧の後の折りたたみに書く）
- **直し方**：問題名を外して一般論だけを残す（「2 つの区間の組で決まる条件も……形に直せることが多い」）。ABC457 E への手がかりは練習の方針の折りたたみに任せる。一覧の表の「代表の問題」の ABC457 E は、pattern の表の決まりどおりなので残してよい

### 4. 直すとよい｜分かりやすさ（U3・U6）｜#properties の図の直後の段落（75 行）と #containment の 2 段落目（212 行）

- **問題**：(a) 75 行の「2 より小さい値の位置で最も近いものは、左の 0 と右の 5 である」は、A の中に値 0（位置 5）もあるので、0 と 5 が位置か値か迷う。(b) 212 行の「ある区間に含まれる区間の数は……「p ≤ L かつ R ≤ q の点の数」」で、p・q がまだ出ていない。この節だけを読むと何が p・q か分からない
- **根拠**：clarity.md U3（記号を定義の前に使う）・U6（節を 1 つだけ取り出して読む）
- **直し方**：(a)「左では位置 0（値 1）、右では位置 5（値 0）である」。(b)「質問の区間 [p, q] に含まれる区間の数は」と書いて p・q を名付ける

### 5. 直すとよい｜手引き（§14-12）｜60 字を超える見出し 2 つ

- **問題**：「更新と質問が交互 → BIT・セグメント木（fenwick-tree, segment-tree, lazy-segment-tree）」（68 字）と「区間の異なる値の個数・x 以下の個数 → クエリの先読みと BIT、Mo（offline-queries, mo-algorithm）」（67 字）が目安の 60 字を超える。執筆者も未解決の点に挙げている
- **根拠**：手引き §14-12（見出しは 60 字以内を目安。anchor を変えずに見出しと title を同時に短くしてよい）
- **直し方**：かっこの中のページ id を省くか（たとえば「更新と質問が交互 → BIT・セグメント木・遅延セグメント木」「区間の種類数・x 以下の個数 → クエリの先読みと BIT・Mo」）、骨格の形をそろえるならメインの判断で残す。どちらでも anchor は変えない

### 6. 直すとよい｜分かりやすさ（U5）｜#shrink-and-merge の 2 段落目（163 行）

- **問題**：遷移の 3 つの型のうち、1 つ目と 2 つ目には計算量があるのに 3 つ目にはない。3 つ目の型にはリンク先（interval-dp#last-operation）で「左端と一緒に消える相手を決める」のほかに「最後に残すものを決める」決め方もある。本文の 1 文だけでは、どんな操作のときにこの型を使うかが分からない
- **根拠**：docs/dp/interval-dp.md の #last-operation（決め方は 2 通り。相手 m を試すので O(N^3)）
- **直し方**：「3 つ目は、ある要素がいつ・何と一緒に消えるかを決める型で、左端と組んで消える相手 m を試すので O(N^3) かかる（最後に残す・最後に消すものを決める型）」のようにする

## 総合の判定

小さな直しで可。直すべきは 1 件（落とし穴の「全区間の和」の大きさの見積もりが量と合わない）、直すとよいは 5 件。図・リンク・計算量・定理の主張（差分列の最小回数、同じ値の扱い、mex の主客転倒、交わる区間の余事象）・問題の要約と方針はすべて確かめて一致した。執筆者の未解決の点のうち ABC265 D の「値が正」は 2 つ目の資料で確かめられた。台帳では abc457_e の summary の反映と、abc265_d の evidence の追加が要る。
