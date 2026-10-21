# palindrome の検証（工程8b・b1）

- 対象：docs/string/palindrome.md、snippets/palindrome/{expand-center,manacher}.{cpp,yaml}、docs/img/palindrome/{symmetric-pairs,manacher-mirror}.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page palindrome`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/palindrome`（2 片・コンパイル 2 回・期待と違う 0）。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。2 片を `-fsanitize=address,undefined` 付きでも動かし、下のランダム試験で異常なし
- リンク先の anchor（dp-state-design#last-characters・extended-dijkstra#two-ends・rolling-hash#hash-segment-tree・#concat-and-reverse・z-algorithm#reverse・#linear-time）と、interval-dp・divisor-enum・memoized-recursion・contribution・suffix-automaton のページがあることを確かめた
- 小さなプログラム（作業用の場所）で確かめた主張。どれも反例なし
    - expand-center.cpp：$N \le 12$・$k \le 3$・文字 2〜3 種のランダム 300 件で、不一致 $k$ 組以下の部分文字列の数が全区間の素朴な数え上げと一致
    - manacher.cpp：$N \le 150$ のランダム 300 件で、snippet 内の assert（$S[l, r)$ が回文 ⇔ $\mathrm{len}[l + r] \ge r - l$）が通り、回文の部分文字列の個数 $= \sum_c \lfloor (\mathrm{len}[c] + 1)/2 \rfloor$、最長の回文の接尾辞 $=$ $\mathrm{len}[l + N] \ge N - l$ を満たす最小の $l$ も素朴な方法と一致
    - 組 $(i, j)$ が対になる閉区間の数 $= \min(i + 1, N - j)$（$N \le 8$ の全組）
    - 「長さ $K$ 以上の回文を含まない ⇔ 長さ $K$ と $K + 1$ の回文を含まない」（$K \le 5$、$N \le 10$ の a・b の全列挙）
    - グラフ上の回文：外へ伸ばす BFS（距離 0 を先、距離 1 を後に入れ、遷移 $+2$）が全頂点対の最短の回文の歩道と一致（有向・自己ループ・多重辺ありのランダム 300 件、素朴な探索は長さ 9 まで）。内側へ向かう BFS で「同じ頂点で $2d$・辺の両端で $2d + 1$」の最小を取る方法も、有向・無向の両方で $1 \to N$ の答えと一致
- 具体例：symmetric-pairs の数列 1 2 3 1 3 2 の組（1–2・2–3・3–1）と答え 2、確認問題 $N = 5$ の位置 1・3（$[0,4]$・$[1,3]$）、Manacher の図の $T$（abacabad、中心 7・右端 15、位置 9 は鏡 5 の len 1 を写す、位置 11 は鏡 3 の len 3 が左端に届き $T[7] = $ c と $T[15] = $ d が食い違って len 3）、確認問題の abaaababa の len 列（snippet の cases と一致）・$S[0, 7) = $ abaaaba・$S[4, 9) = $ ababa、`abc` の b の中心が位置 3。すべて正しい
- 問題：8 問とも `python3 tools/ap.py show` で題名・diff が台帳・本文と一致。evidence を読んだ（問題文を引用した部分は読んでいない）
    - abc468_d（ikatakos）：長さ $1 \sim 10^4$、高々 1 文字の書き換えで回文になる部分文字列（位置が違えば別）を数える。中心から伸ばし 2 回目の不一致で打ち切る $O(N^2)$。本文と一致
    - abc398_f（ikatakos）：$\lvert S \rvert \le 5 \times 10^5$、$S$ を接頭辞に持つ最短の回文。最長の回文の接尾辞を Manacher かハッシュで。本文と一致
    - abc394_e（ikatakos）：有向・$N \le 100$・到達できない組は $-1$。初期値は長さ 0 と 1。解説の方法は BFS ではなく、更新がなくなるまで緩和を繰り返す方法（公式解説は BFS とある）。本文の BFS は上の試験で正しい
    - abc290_e（ikatakos）：$\min$（左から何番目, 右から何番目）の寄与、全組から値の等しい組を引く、値ごとに両端から寄せて $O(N)$。本文と一致
    - abc197_f（kmjp）：無向、$\mathrm{dp}(x, x) = 0$・辺ごとに $1$ から外へ $+2$。本文の「外へ伸ばす」形と一致。本文の主な説明（$(1, N)$ から内側へ BFS し、出会い方の偶奇で答える）は解説と別の形だが、上の試験で正しい（執筆者の未解決の点 3 は問題なし）
    - abc363_f（merom686）：中に回文の数、外側に反転の組、どれも $N$ の約数で 0 を含まない、積の途中は `__int128`。N の上限は記事に書かれていない（未解決の点 2 は本文に書かないままでよい）。記事自身の方法は約数の小さい方からの DP で、外側を剥がす再帰は公式解説の方法として触れているだけ（指摘 6）
- 図：Windows の Chrome（headless=new）で 2 枚を等倍と、幅 390px の画面に幅 358px（2 倍密度、暗い背景の上）で画像にして目で確かめた。和文も表示され、背景は白で塗られ、`viewBox` があり、文字はテキストのまま。弧と辺は色だけでなく実線・破線・点線で区別している。値は本文・代替テキストと一致
- 動く図：作っていない。手引き §8 どおり静的な SVG で足りる（執筆者の報告では visual は priority 3）

## 指摘

### 1｜直すべき｜手引き（§13.1・§4）｜front matter の sections（32 行）と #comparison の見出し（176 行）・置き場所

- **問題**：「使い分け」は定型の節なので sections に載せず、見出しは `## 使い分け {#comparison}` にする決まりだが、sections に `{title: 回文判定の道具の使い分け（…）, anchor: comparison}` があり、見出しもその title になっている。置き場所も、technique の目安（落とし穴 → 例題 → 練習・力試し → 確認問題 → 使い分け → 参考）と違い、落とし穴の前にある
- **根拠**：style-guide §13.1（「定型の節は sections に載せず、次の見出しと anchor を使う：… `## 使い分け {#comparison}`」）、§4 の technique の目安。z-algorithm の検証の指摘 3 と同じ扱い。執筆者も報告でこの扱いを尋ねている
- **直し方**：sections から comparison の行を消し、見出しを `## 使い分け {#comparison}` にして、確認問題の後・参考の前へ移す。§13 に「sections に comparison が残っていたら消す」の一言を足すかはメインが判断する

### 2｜直すべき｜figure（G5）・clarity（U3）｜manacher-mirror.svg と 162 行の代替テキスト

- **問題**：本文（156 行〜）は、いま求める位置を $j$、鏡の位置を $j'$、右端が最も右の回文の中心を $c$ と書いている。図と代替テキストは「中心 c = 7」と書いた直後に、いま求める位置を「c = 9」「c = 11」と同じ $c$ で書き、行の見出しも「c」になっている。本文と照らす読者には「c = 9 は中心が 9 に移ったのか」と読め、鏡のコピーの説明の要の場所で記号が食い違う
- **根拠**：SVG の「実線：c = 9 は鏡の位置 5 の len = 1 を写す」「破線：c = 11 は …」と、本文の「$c < j < r$ なら …鏡の位置 $j' = 2c - j$」
- **直し方**：図の説明と代替テキストの「c = 9」「c = 11」を「j = 9」「j = 11」にする（「鏡の位置 j′ = 5」としてもよい）。行の見出しの「c」は「位置」にする。題の行「中心 c = 7」はそのままでよい

### 3｜直すとよい｜fact（F7）・clarity（U3）｜#manacher の 146 行

- **問題**：「$2N + 1$ 個のすべての中心」とあるが、ページのほかの場所（84 行・191 行・例題）では中心は $2N - 1$ 個。差の 2 個は両端の空の中心（$c = 0, 2N$）だと書いていないので、読者は数え違いかと迷う
- **直し方**：「$T$ の $2N + 1$ 個の位置（両端の空の回文の中心 2 個を含む）」などと添える

### 4｜直すとよい｜fact（F2）｜#comparison の 187 行

- **問題**：「決定的に（衝突なしで）済ませたいなら Manacher か Z を選ぶ」は、Z で決定的に分かるのは回文の接頭辞・接尾辞だけで、任意の区間の判定はできない。表の行ごとの範囲を外れて一般化して読める
- **直し方**：「任意の区間の判定を決定的に済ませたいなら Manacher、接頭辞・接尾辞だけなら Z でもよい」とする

### 5｜直すとよい｜fact（F7）｜#pitfalls の 193 行

- **問題**：$\mathrm{pal}[l][r] = (S[l] = S[r]) \land \mathrm{pal}[l + 1][r - 1]$ は閉区間の式だが、節の中で断りがない（Manacher の節は半開区間）。断片で読むと区間の流儀が分からない
- **直し方**：「（閉区間 $[l, r]$）」を添える

### 6｜直すとよい｜fact（F9）｜#references の merom686「ABC363」の行（302 行）

- **問題**：「外側の組を剥がす再帰と約数」の出典としているが、記事自身の方法は約数を小さい方から並べ、作れる約数に反転の組を掛けて広げる DP で、外側を剥がす再帰は公式解説の方法として一言触れているだけ
- **根拠**：evidence の URL（上の「確かめたこと」）
- **直し方**：「力試し ABC363 F の方針（中の回文の数と外側の反転の組、どれも N の約数で 0 を含まない。積の途中のあふれ）」などに直す。本文の再帰は約数ごとのメモで正しいので、そのままでよい

### 7｜直すとよい｜fact（F5）｜#abc394_e の解法の詳細（248 行）

- **問題**：「到達できない場合の出力の指定に従う」は、執筆者の未解決の点 1。evidence に「到達できない組は $-1$」とある
- **直し方**：「最後まで未到達の組は $-1$ を出す」と書いてよい。台帳への提案（abc394_e の unverified_in の削除）は evidence と合うので、あわせて反映してよい

### 8｜直すとよい｜figure（G3）｜manacher-mirror.svg・symmetric-pairs.svg

- **問題**：(a) 幅 390px の画面（表示幅 358px）では manacher-mirror が約 0.6 倍に縮み、位置の数字（12）が 7px 前後になって読みにくい。symmetric-pairs も位置の数字が 8px 前後。(b) manacher-mirror の右端の「r」の文字が位置 15 の数字に接している。(c) 弧の下（y 約 200〜260）に何もない帯があり、図が縦に間延びしている
- **根拠**：Chrome で幅 358px に描画した画像（作業用の場所の n-manacher-mirror.png・n-symmetric-pairs.png）
- **直し方**：位置の数字を 14〜15 に上げる。「r」を破線の上端の上（位置の数字の行より上）へ動かす。下の説明 4 行を代替テキストと本文に任せるか、空いた帯を詰めて viewBox の高さを縮める

## 執筆者の未解決の点・提案への回答

- 未解決の点 1（ABC394 E の出力）：指摘 7
- 未解決の点 2（ABC363 F の N の上限）：evidence にも書かれていない。本文に書かないままでよい
- 未解決の点 3（ABC197 F の 2 通りの方針）：どちらも正しい（全探索との照合）。力試しの方針の「無向グラフで…両端から BFS」は内側へ向かう形で、本文 #palindrome-path の説明と合う
- 未解決の点 4（回文木へのリンク）：stub の間はページへのリンクでよい
- 手引きへの提案 1（レベル）：front matter は level: 水で、構成は水の technique の目安に合っている（青の 2 節は sections の level: 青と前提の一言がある）
- 手引きへの提案 2（comparison の見出し）：指摘 1
- 台帳への提案：abc468_d・abc398_f・abc206_d（未読だが drken の記事は参考に挙げた内容どおりの題）・abc359_d・abc290_e・abc363_f の checked、abc394_e の unverified_in の削除は、上の evidence の確認と合う。このほか abc197_f も kmjp の記事で内容を確かめたので checked: 2026-10-21 を提案する

## 総合の判定

小さな直しで可。直すべき 2 件（sections と使い分けの見出し・置き場所、Manacher の図の記号）、直すとよい 6 件。事実の誤り・コードの誤りは見つからなかった。
