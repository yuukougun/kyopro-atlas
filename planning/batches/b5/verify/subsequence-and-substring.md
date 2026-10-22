# b5 検証：subsequence-and-substring

- 対象：docs/patterns/subsequence-and-substring.md、docs/img/subsequence-and-substring/two-ways.svg（snippets はなし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：図は `python3 tools/render_svg.py subsequence-and-substring --scale 2` で 360px・720px の PNG にして目で確かめた。コード片がないので code.md の C1〜C8 は対象なし（本文の擬似コード 2 つは下の Python で同じ処理を動かして確かめた）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page subsequence-and-substring`：エラー 0・警告 0
- 本文のリンク先のファイルと anchor（`../` で始まる相対リンク全部）：すべてある。中身も読んで、主張の行き先として合うかを見た（指摘 3・4 以外は合う）。dp-phase#matched-prefix には '?' を埋めた全通りの和もある。string-basics#substring-vs-subsequence の最後の段落に「K 番目の異なる部分文字列の長さは K 以下」がある。lcs#palindromic-subsequence・#substring・#edit-distance、fix-variable#fix-middle、z-algorithm#cyclic-shift、counting-dedup#leftmost、subsequence-matching の辞書順最小の節もある
- `python3 tools/ap.py show`：abc211_c「C. chokudai」diff 559、abc456_d「D. Not Adjacent 2」diff 586。本文の label・diff と一致
- 作業用の場所の Python（試しのコードはリポジトリに置かない）で、ランダムな小さい入力について次を全探索と比べた。すべて一致
    - ABC456 D の DP（cnt[c] += 他の 2 文字の cnt の和 + 1、答えは 3 つの和）と、「a・b・c の文字列の空でない部分列（位置の選び方）で同じ文字が隣り合わないものの数」の全探索（長さ 1〜10、300 個）
    - 異なる部分文字列の数 = N(N+1)/2 − Σ_{i=0}^{N−2} lcp[i]（長さ 1〜12）と、辞書順 K 番目の異なる部分文字列の長さ ≤ K
    - 最長回文部分列 = LCS(S, S の反転)（長さ 1〜10）
    - 選び方の数の DP（1 本の配列で j を大きい方から）と組合せの全探索。落とし穴の例 T = `aa`、S = `a`：小さい方から回すと 1、大きい方からは 0（本文どおり）
    - 確認問題：`abc` の空でない部分文字列 6 個・部分列 7 個。`aab` から `ab` の位置の組 2 通り。`abcab` の位置 0・2・3 が `aca`、S[1, 4) が `bca`、`aca` は部分文字列でない
- `chokudai` の 8 文字はすべて異なるので、j をどちら向きに回しても同じ（例題の詳細の主張は正しい）。C(10^5, 8) ≈ 2.5×10^34 なので、最後だけ余りを取ると long long を超えるのも正しい
- 計算量：判定 O(N+M)、表で 1 回 O(M)、選び方 O(NM)、3 つ組 O(N)、LCS O(NM)、LIS O(N log N)、Z で O(N+M)、照合オートマトン上の DP O(LMσ)、末尾 M−1 文字なら状態 σ^{M−1}：正しい。要点・front matter の complexity・本文で一致
- 回文の「N が 10^5 を超えるなら Manacher」は palindrome#expand-center の「10^4 程度なら O(N^2) で間に合う。10^5 を超えると間に合わない」と一致
- 参考の URL（F9・F8）：4 つとも開いた。sano192 氏の記事（題名一致、dp[i][j]＝S の i 文字目までで chokudai の j 文字目までを作る方法の数）、m193h 氏「AtCoder ABC211 個人的メモ」（左から見て接頭辞ごとの数を持つ）、comet725 氏「ABC456Dを解いた【DP】」（末尾の文字ごとの数、更新は前の和 + 1 で、本文の式と同じ値）、iwamutsu256 氏「AtCoder Beginner Contest 456 参加記録と解答例 (A～D問題)」（a・b・c、空でない、位置が違えば別、998244353、A = A + 1 + B + C）。台帳の提案の summary と一致。ドメインは qiita.com・zenn.dev で付録 B にある。本文は記事の文の並び・例をなぞっていない
- 執筆者の未解決の点：docs/patterns/interval.md には検証の時点で `## 問われ方と手法の一覧 {#overview}` ができている（`grep` で確かめた）。#subarrays の節の `../patterns/interval.md` は `../patterns/interval.md#overview` に張り替えてよい（指摘 10）
- 図（G3〜G7）：viewBox 400×270 と width・height が同じ比、白の背景あり（ダークでも読める）、文字はテキスト・sans-serif。代替テキストと図の中身（位置 0・2・3 で aca、S[1, 4) で bca）が本文と一致。360px でも文字は読める。気になる点は指摘 5

## 指摘

### 1. 直すべき｜分かりやすさ（U7）・手引き（§15-23）｜#count-with-condition の 1 つ目の項目（「隣り合う文字についての条件」）

- **問題**：本文が「同じ文字が続かない」を例に、cnt[c] に「つないでよい末尾の文字 d の cnt[d] の和と 1」を足す更新式まで書き、その場で「練習の ABC456 D」を指している。練習の要約は「同じ文字が隣り合わないものの個数」なので、本文を読んだ時点で練習の解き方がそのまま見える。練習の方針を折りたたみに入れた意味がなくなる
- **根拠**：clarity.md U7 のよくある失敗「本文が練習の問題を指して、その解き方を折りたたみの外で書いてしまう」。style-guide §244 行「練習の方針は一覧の後の折りたたみに書く（一覧で解き方が見えないように）」
- **直し方**：どちらか。(a) 本文の例の条件を練習と違うもの（例：「`b` の直後に `a` を置かない」など）にし、「（練習の ABC456 D）」を消す。更新式は一般の形（つないでよい d の和 + 1）のまま残してよい。(b) 例はそのままにして、ABC456 D を練習から外す（patterns の練習は 0〜3 なので 0 でもよい）。台帳の提案もそれに合わせる

### 2. 直すとよい｜事実（F2）・分かりやすさ（U3）｜#properties の「できるだけ左で拾う」の段落、#distinct-subsequences の 2 段落目

- **問題**：「各文字をそれまでで最も左の位置から取る」（#properties）、「各文字を、まだ使っていない位置のうち最も左から取る」（#distinct-subsequences）は、字義どおりに読むと前に取った位置より左の未使用の位置も候補に入る。例：S = `aba`、X = `ba` で、b を位置 1 で取ったあと、まだ使っていない最も左は位置 0 だが、正しくは位置 2
- **根拠**：subsequence-dp#leftmost の定義は「前に使った位置より右で、最も左の位置」。上の反例
- **直し方**：両方を「直前に取った位置より右で、最も左の位置から取る」とする。同じ言い回しは subsequence-dp の要点・counting-dedup#leftmost にもあるので、揃えるかはメインが判断する（このページだけ直しても矛盾はしない）

### 3. 直すとよい｜事実（F3：リンク先）｜#distinct-subsequences の箇条書き 1 つ目

- **問題**：「部分列として現れない最短の文字列・辞書順 K 番目の部分列」を、shortest-non-subsequence の節 1 つへだけリンクしている。K 番目は別の節 subsequence-dp#kth-subsequence にあり、リンク先には書かれていない
- **根拠**：docs/dp/subsequence-dp.md の見出し `{#shortest-non-subsequence}` と `{#kth-subsequence}`
- **直し方**：「（[最短の文字列](../dp/subsequence-dp.md#shortest-non-subsequence)、[辞書順 K 番目](../dp/subsequence-dp.md#kth-subsequence)）」と 2 つに分ける

### 4. 直すとよい｜事実（F3：リンク先）｜#palindromes の「最長回文部分列」の項目

- **問題**：「区間ごとの最長回文部分列を状態にした[区間 DP](../dp/interval-dp.md#state)」のリンク先 interval-dp#state は合体のコスト（EDPC N の形）で状態を説明する節で、最長回文部分列の漸化式はない。読者は行き先で目的の DP を見つけられない
- **根拠**：最長回文部分列の区間 DP（両端が等しければ dp[l+1][r−1] + 2、違えば max）は lcs#palindromic-subsequence の最後の段落にある。interval-dp で回文が出てくるのは #ends の「回文にする最小の挿入」だけ
- **直し方**：区間 DP のリンクを [最長回文部分列](../dp/lcs.md#palindromic-subsequence) の段落に任せ（同じ文の前半ですでにリンクしている）、「区間 DP でも O(N^2) で書け、条件を足しやすい（同じ節）」とする。区間 DP そのものへはページへのリンク（anchor なし）でよい

### 5. 直すとよい｜図（G5）｜two-ways.svg の下段

- **問題**：部分文字列の枠（rect y=186〜242）の上辺が、位置の番号 1・2・3（文字のベースライン y=186）を横切り、番号に取り消し線が引かれたように見える（360px・720px の両方）
- **根拠**：render_svg の PNG を目で確かめた
- **直し方**：枠を `y="190" height="50"` 程度に下げて番号の下から始めるか、下段の番号を y=180 に上げる（上段と同じく枠の外に出す）

### 6. 直すとよい｜分かりやすさ（U2・U4）｜#index-tuples の 2 段落目

- **問題**：A_i < A_j < A_k で「左で A_j より小さいものの個数と、右で大きいものの個数を、それぞれ数えて掛ければよい」とあるが、その個数を速く数える道具がない。この読者は j ごとに走査して O(N^2) にしかねない（文字の 3 つ組の O(N) と違う点が抜けている）
- **根拠**：リンク先 fix-variable#fix-middle の本文と表は「BIT（座標圧縮と組み合わせる）で O(log N)」と書いている
- **直し方**：「j を左から動かしながら [BIT](../ds/fenwick-tree.md) で数えれば全体で O(N log N)」を 1 文足す

### 7. 直すとよい｜事実（F2：言い回し）｜#longest の 1 段落目

- **問題**：「同じ表で、挿入・削除・置換の最小回数（編集距離）も求まる」は、LCS の表の値から編集距離が読めるように読める。実際は状態の形（先頭 i 文字と j 文字）が同じで、初期値と遷移が違う別の表である（置換を含む編集距離は LCS の値からは出ない）
- **根拠**：lcs#edit-distance「LCS と同じく先頭 i 文字と j 文字の組を状態にし、最大の代わりに最小を取る」「初期値… LCS と違って 0 ではない」
- **直し方**：「同じ形の表（状態は同じで、遷移と初期値を変える）で」とする

### 8. 直すとよい｜手引き（§15-11）｜#properties の末尾の確認問題

- **問題**：確認問題が #properties の節の中にある。手引き §15-11 は `## 確認問題 {#quiz}` にまとめるとする（既存のページにも節の中に置いたものがあるので、直すべきとはしない）
- **根拠**：planning/style-guide.md 300 行
- **直し方**：参考の前に `## 確認問題 {#quiz}` を立てて移す（sections には載せない）。節の中に残すならそのままでもよい

### 9. 直すとよい（メインへの提案）｜front matter（F10）｜sections の count-occurrences の title

- **問題**：title の「（dp-state-design）」に対し、本文の行き先の中身は dp-phase#matched-prefix で、一覧の表のページの列も dp-phase。執筆者の提案と同じ
- **根拠**：本文 #count-occurrences の最後の文と一覧の 2 行目
- **直し方**：メインが title を「（dp-phase）」に直すか判断する（anchor は変えない）。執筆者は front matter を変えない

### 10. 直すとよい｜リンク（§15-23）｜#subarrays の 1 段落目の「[区間](../patterns/interval.md)」

- **問題**：執筆時は interval に見出しがなかったのでページへのリンクにしたが、いまは interval.md に `{#overview}` がある
- **根拠**：`grep -n "{#overview}" docs/patterns/interval.md` → 82 行目
- **直し方**：`../patterns/interval.md#overview` にする（メインのリンク張り替えでまとめてもよい）

## 総合の判定

小さな直しで可。直すべき 1 件（練習の解き方が本文で見える）、直すとよい 9 件。事実・計算量・問題の内容・出典に誤りはなかった。
