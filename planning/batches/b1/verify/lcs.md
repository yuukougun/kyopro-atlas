# lcs の検証（工程8b・b1）

- 対象：docs/dp/lcs.md、snippets/lcs/{lcs,edit-distance,lcs-row-dp}.{cpp,yaml}、docs/img/lcs/table.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page lcs`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/lcs`（3 片・コンパイル 3 回・期待と違う 0）、`npx textlint docs/dp/lcs.md`（エラー 0・警告 28。数式を含む文の長さ・助詞の重なり・「最長共通部分文字列」の漢字の連続で、規則の誤検出か用語そのもの）。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。3 片を `-fsanitize=address,undefined` 付きでも動かし、下の試験で異常なし
- check_pages は相対リンクの行き先のファイルがあるかを見ていない。リンク先を 1 つずつ確かめ、string-basics の 2 か所だけが壊れていた（指摘 1）。ほかのリンク先（dp-reconstruction#trace-back・#ties、prefix-sum-2d、bit-dp、dp-state-design、z-algorithm、rolling-hash、suffix-array、lis、palindrome、dp-basics、glossary#popcount）はあり、anchor もある。counting-dedup・subsequence-dp・interval-dp は stub で、節の anchor を使わずページへリンクしているので手引き §7 どおり
- 小さなプログラム（作業用の場所）で確かめた主張。どれも反例なし
    - LCS の表と全探索（部分列をすべて作って比べる）の一致、復元した列が両方の部分列で長さが dp[N][M]（文字 2〜3 種、長さ 0〜9 のランダム 400 件・200 件）
    - 共通部分列の組の数の包除の式、別法「最後に組にした位置の DP（dp[0][0] = 1、左上の長方形の和）」の総和、どちらも全列挙と一致（空の組を含む）
    - 挿入と削除だけの最小回数 $= N + M - 2\,\mathrm{LCS}$
    - 編集距離の帯：$\lvert i - j \rvert \le K$ だけを埋め、帯の外を $K + 1$ とみなした値で「距離 $\le K$ か」と、$\le K$ のときの値が正しい（$K \le 3$）
    - 最長回文部分列 $= \mathrm{LCS}(S, S^R)$（全列挙）。証明の $p$・$q$・$e$ の議論も読んで正しい（$a_t - b_t$ が狭義増加、真ん中の $a_t = b_t$ は $a_p$ と $b_p$ の間・$b_{p+e+1}$ と $a_{p+e+1}$ の間にある）
    - 最長共通部分文字列の表（一致しなければ 0、答えは全体の最大）、ABC141 E 型の $\min(\mathrm{dp}[i][j], j - i)$（$i < j$）の最大が、重ならない 2 回の出現の全探索と一致
    - 使い分けの「片方の値がすべて違えば LCS は位置に読み替えた列の狭義 LIS」（値 0〜9 のランダム 500 件。もう片方に重複があっても成り立つ）。執筆者の未解決の点 3 つ目は正しい
    - AGC021 D の区間 DP $\mathrm{dp}[l][r][k]$（両端が違えば書き換えを 1 回使って $+2$）が、$N \le 6$・文字 3 種・$K \le N$ の書き換えの全列挙と一致（150 件）。執筆者の結果と同じ
    - lcs-row-dp.cpp：$\lvert s \rvert \le 4$・$m \le 4$ の 55 通りで $26^m$ の全探索（C++）と一致。cases の大きい 2 つ（abcdefghij・aaaaaaaaaa、$m = 100$）は、bit にせず行の組をそのまま辞書に持つ Python の別実装でも同じ値になった
    - Mermaid の遷移 8 本を手で 1 行分ずつ計算し、すべて正しい（行は 4 通りとも到達する）
- 具体例：図の表（abcb × bdcab）の 30 マスと網かけの 6 マス、右下 3、復元の経路と「bcb」、編集距離 abcb→bdcab = 3・kitten→sitting = 3・xyz→zyx = 2、$S = \texttt{aabcaba}$ の LCS 5 と上を先に見た復元 aacba（回文でない）、確認問題 abca と acba の LCS 3。経路の向きの 1 か所を除きすべて正しい（指摘 2）
- 計算量・メモリ：$5001^2$ の `int` で約 100 MB、`short` で約 50 MB、`long long` で約 200 MB、$3001^2$ の `int` で約 36 MB、$26 \cdot 100 \cdot 2^{10} \approx 2.7 \times 10^6$。いずれも正しい
- 問題：6 問とも `python3 tools/ap.py show` で題名・diff が台帳・本文と一致。evidence を読んだ（問題文を引用した部分は使っていない）
    - dp_f（drken の Qiita）：表の定義と、終端から上・左・左上の順に遡る復元。本文と一致
    - abc185_e（drken）：$N, M \le 1000$、3 方向の遷移、記事自身が「編集距離そのもの」と書いている。本文の「編集距離そのもの」は正しい（執筆者の未解決の点 4 つ目。台帳の approach「編集距離の変形」は直してよい）
    - abc141_e（drken）：$N \le 5000$、解法 5 が一致長の表と $\min(\mathrm{dp}, j - i)$。記事は「i・j から始めた」向き、本文は「i・j で終わる」向きで、どちらも正しい
    - abc130_e（drken）：$N, M \le 2000$、dp[0][0] = 1 で空の組を含めて数える、包除の式、最後に組にした位置の DP と 2 次元累積和の別解。本文と一致（台帳の summary への提案は妥当）
    - abc391_g（kmjp・wanggk）：kmjp の記事は上限を書いていない。wanggk の記事に $N \le 10$・$M \le 100$。行の隣の差が 0 か 1 で $2^N$ 状態。本文と一致
    - agc021_d（drken）：$\lvert S \rvert \le 300$、$1 \le K \le \lvert S \rvert$、記事は区間 DP ではなく「前半を左から・後半を右から組にする」$\mathrm{dp}[i][j][k]$ で $O(N^2 K)$。本文の方針は区間 DP を主にし、記事の方法を「左右から文字を組にしていく形の DP」として添えている。区間 DP は上の全列挙で正しい。台帳の approach（区間 DP）は本文と合っているので、evidence に区間 DP の解説がない点は台帳の側の問題（下の「メインへ」）
- 参考の 7 件：題名・著者・内容が書かれたとおり（Qiita・drken 5 件・kmjp・cnblogs を開いた）。どのドメインも付録 B にある。atcoder.jp・codeforces.com の URL はない
- 図：Windows の Chrome（headless=new）で table.svg を等倍（680×468）と、幅 390px の画面に幅 358px（2 倍密度、暗い背景の上）で画像にして目で確かめた（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-lcs/full.png・narrow.png）。和文も出て、重なり・はみ出しはない。背景は白で塗られ、`viewBox` があり、文字はテキストのまま（sans-serif）、相対パスで参照されている。網かけ（斜線）と経路（赤の塗り＋矢印、斜めは実線・横は破線）は色だけでなく模様と線の種類でも区別している（執筆者の未解決の点 1 つ目は確認済み）
- Mermaid：同じ図を mermaid 10.9.1（jsDelivr）で描いて確かめた（同じ場所の mer.png）。自己ループのラベルも出て読める。図の前後の文章で遷移の要点が通じるので、欠けても困らない（手引き §8 どおり）。catalog の visual は priority 2 なので、動く図がないのは許される
- 前提とレベル：count-pairs（青）と dp-of-dp（黄）は節の最初で追加の前提をリンクしている。節の並び（落とし穴 → 例題 → 練習 → 力試し → 確認問題 → 使い分け → 参考）と定型の見出しは手引き §4・§13.1 どおり

## 指摘

### 1｜直すべき｜fact（F7）・clarity（U6）｜導入（49 行）と #substring（140 行）のリンク

- **問題**：`../basics/string-basics.md#substring-vs-subsequence` は存在しないファイルを指す。string-basics は string の分野にある。サイトでは 2 か所とも壊れたリンクになり、`mkdocs build --strict` でも警告になる
- **根拠**：`find docs -name string-basics.md` → `docs/string/string-basics.md` だけ。そのページに `{#substring-vs-subsequence}` はある
- **直し方**：2 か所とも `../string/string-basics.md#substring-vs-subsequence` にする

### 2｜直すべき｜fact（F3）・figure（G5）｜#recurrence の 81 行、table.svg の代替テキスト

- **問題**：代替テキストは経路を「斜め・左・斜め・上・斜め」と書くが、本文の手順（上を先に見る）でたどると (4,5) →斜め→ (3,4) →左→ (3,3) →斜め→ (2,2) →左→ (2,1) →斜め→ (1,0) で、4 つ目は「左」である。図の SVG（y = 248 の水平の破線の矢印）も左で、代替テキストだけが違う
- **根拠**：上の「確かめたこと」の表と復元のプログラム（出力 `['diag', 'left', 'diag', 'left', 'diag']`、終点 (1, 0)）
- **直し方**：代替テキストを「斜め・左・斜め・左・斜め」にする

### 3｜直すとよい｜figure（G3）｜table.svg の幅 390px での読みやすさ

- **問題**：viewBox の幅 680 のうち表は x = 140〜512 で、左に約 140、右に約 170 の余白がある。幅 358px に縮めると 0.53 倍になり、説明の文字（13px）が約 7px、添字のラベル（12px）が約 6px になって、スマホでは読みにくい
- **根拠**：narrow.png（上の「確かめたこと」）
- **直し方**：表を左へ寄せて viewBox の幅を 560 程度に詰める（上の 3 行と下の 2 行は改行して短くする）か、説明の文字を 15px 以上にする

### 4｜直すとよい｜fact（F1・F10）｜要点の「計算量」（44 行付近）

- **問題**：front matter の complexity には「DP の DP は O(σ·M·2^N)」があるが、要点の計算量には LCS の $O(NM)$ と 2 行の $O(M)$ だけで、DP の DP がない。要点の「いつ使うか」の 4 つ目（ちょうど $k$ になる文字列の数）に対応する計算量が冒頭だけでは分からない
- **直し方**：要点の計算量に「DP の DP は $O(\sigma M 2^N)$（$N$ は短い方の長さ、$\sigma$ は文字の種類数）」を足して complexity とそろえる

### 5｜直すとよい｜clarity（U4）｜#count-pairs の 164 行（別の数え方）

- **問題**：「最後に組にした位置が $(i, j)$ である組の数」の DP は、空の組を表す $\mathrm{dp}[0][0] = 1$（ほかの 0 行目・0 列目は 0）と、答えが表全体の和であることが書かれていない。この 2 つがないと、長方形 $[0, i) \times [0, j)$ の和が何を数えるかが決まらず、実装できない。累積和を表を埋めながら作る順序（行ごとに、使うのは左上の確定した部分だけ）にも触れるとよい
- **根拠**：drken の ABC130 E の記事の解法 2 も dp[0][0] = 1 を置いている。上の全列挙で、この初期値と「全体の和」で組の数と一致することを確かめた
- **直し方**：「空の組を $(0, 0)$ に置いて $\mathrm{dp}[0][0] = 1$ とし、答えは表全体の和」の 1 文を足す

### 6｜直すとよい｜clarity（U3）｜#dp-of-dp の 185 行

- **問題**：#recurrence の表は $S$ が行（$i$）、$T$ が列（$j$）だったが、この節は「$T$ の先頭 $i$ 文字に対する表の行」で、$i$ が $T$、$j$ が $S$ の側になり、前の節の表では列にあたる。図（table.svg）を見た読者は「行」が $S$ の 1 文字ごとの横の並びだと思い、取り違えやすい
- **直し方**：「ここでは $T$ を 1 文字ずつ読むので、前の節とは行と列を入れ替えて、$T$ の先頭 $i$ 文字を行にした表を考える」と一言添える

### 7｜直すとよい｜code（C5・C6）｜snippets/lcs/lcs-row-dp.cpp の `popcount((unsigned)mask)`

- **問題**：`std::popcount` は C++20 の `<bit>` の関数で、引数は符号なしの型だけ（そのためのキャスト）。本文は用語集の popcount にリンクしているが、C++ の版やキャストの理由が本文から辿れない
- **直し方**：本文の popcount の初出か、コードの直後に [<bit> の関数](../cpp/cpp-math-functions.md#bit-functions)（C++20、符号なしだけ）へのリンクを添える。`__builtin_popcount(mask)` に替えてもよい

## メインへ（台帳・提案の判断材料）

- abc185_e の approach：「編集距離そのもの（削除・挿入・置換がどれもコスト 1）」に直してよい（drken の記事の記述と一致）
- agc021_d：区間 DP は全列挙で正しいが、evidence の記事は左右から組にする $\mathrm{dp}[i][j][k]$。approach を「S と反転の LCS（最長回文部分列）に書き換えの回数を足した DP。区間 DP でも、前半と後半を左右から組にする形でもよい」とするのが evidence と合う
- abc130_e の summary に「空の列どうしの組も数える」を足す提案は、drken の記事（dp[0][0] = 1 を答えに含める）で裏付けられる
- abc391_g の evidence に wanggk の記事を足す提案は妥当（$N \le 10$・$M \le 100$ を確かめた。kmjp の記事には上限がない）
- 6 問とも上の evidence で問いを確かめたので、`checked` に 2026-10-21 を入れてよい
- check_pages が壊れた相対リンク（存在しないファイル）を検出しない。指摘 1 はこれで漏れた。検査に足すかどうかの判断を

## 総合の判定

小さな直しで可。直すべき 2 件（リンク先の分野の誤り、代替テキストの経路の 1 語）はどちらも 1 行の直しで、内容の主張・コード・数値・問題の方針はすべて確かめて正しかった。直すとよい 5 件。
