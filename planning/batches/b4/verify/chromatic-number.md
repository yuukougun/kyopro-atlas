# chromatic-number の検証（b4）

対象：docs/graph/chromatic-number.md、snippets/chromatic-number/chromatic.{cpp,yaml}・mis.{cpp,yaml}。図はない（catalog の visual が null）。

## 実行した検査

- `python3 tools/check_pages.py --page chromatic-number -v`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/chromatic-number`：コード片 2・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `npx textlint docs/graph/chromatic-number.md`：エラー 0・警告 6（どれも文の長さ。31・34・71・81・95・96 行）
- サニタイザ（`-fsanitize=address,undefined`）付きで、乱数のグラフを chromatic.cpp に 400 個（N ≤ 10。コード内の全探索の assert で照合）、mis.cpp に 400 個（N ≤ 17。N ≤ 16 は全探索の assert）流した：異常終了・食い違い 0
- mis.cpp を N = 20〜40 の乱数のグラフ 40 個で、別に書いたメモ化つきの分枝（Python）と照合：食い違い 0
- 時間とメモリ：chromatic.cpp は N = 20（密度 0.5、答え 6）で 0.03 秒・28 MB。mis.cpp は N = 40（密度 0.3）で 0.00 秒・17 MB
- 分枝の漸化式の特性根を numpy で計算：$x^3 = x^2 + 1$ の根 1.46557、$x^4 = x^3 + 1$ の根 1.38028。$1.4656^{40} \approx 4.37 \times 10^6$、$3^{20} = 3486784401$。本文の値（1.47・1.38・$4 \times 10^6$・$3.5 \times 10^9$）と一致する
- Library Checker の制約：raw.githubusercontent.com の info.toml で chromatic_number は MIN_N = 1・MAX_N = 20、maximum_independent_set は N_MIN = 1・N_MAX = 40。本文と一致（raw.githubusercontent.com は check_noai.py で noai・noimageai の指定なし）
- 英語版 Wikipedia「Graph coloring」（action=raw）：包除原理と Yates のゼータ変換で $O(2^n n)$（Björklund・Husfeldt・Koivisto 2009）、それ以前の Lawler の $O(2.4423^n)$、k ∉ {0,1,2} で NP 完全、を確認
- 英語版 Wikipedia「Independent set (graph theory)」：補グラフのクリーク・補集合が頂点被覆・二部グラフで多項式時間（König）を確認
- drken「AtCoder 版！蟻本 (中級編)」：「n <= 40 程度なら半分全列挙」「O(1.381^n) のシンプルなアルゴリズム」の記述を確認
- 台帳の abc187_f：N ≤ 18（summary）を確認。本文の言及は例題の見出し（subset-enumeration-dp#abc187_f）へのリンクで、§2.5 に合う
- 本文のそのほかの主張（$\chi \ge \omega$、$\chi \ge N/\alpha$、$C_5$ で $\omega = 2$・$\chi = 3$、覆う数と塗れることの同値、$\mathrm{ind}$ の漸化式、確認問題 1 の $f(1) = 1$、次数 0・1 の頂点を取ってよい理由、確認問題 2 のパス $u - v - w$、三角形で $3 - 1 = 2$ は誤り、二部グラフのクリークは 2 以下、メモリ 3 本 × $2^{20}$ × 8 バイト ≈ 24 MiB）は手で確かめ、誤りはなかった

## 指摘

### 1. 直すべき｜F2・C3（事実・コード）｜#library の「最小の頂点の取り出し」

- **問題**：直前の項目で「$N \le 40$ では `unsigned long long` を使う」と言った直後に「`__builtin_ctz(s)` で得る」と書いている。`__builtin_ctz` の引数は `unsigned int` なので、64 bit の `s` を渡すと下位 32 bit に切り詰められ、下位 32 bit が 0 なら `__builtin_ctz(0)` で未定義になる。要点の通りに分枝を 64 bit で書くと誤る。同じ項目群の「`s & ~(1 << v) & ~adj[v]`」も、64 bit では `1ULL << v` が要る（次の文で断っているが、例の式自体が 32 bit の形）
- **根拠**：GCC の組み込み関数の仕様（`__builtin_ctz(unsigned int)`、`__builtin_ctzll(unsigned long long)`、引数 0 は未定義）。コード片 mis.cpp は前半・後半を `int` にしてから `__builtin_ctz` を使うので正しく、問題は本文の箇条書きだけ
- **直し方**：「`__builtin_ctz(s)`（64 bit なら `__builtin_ctzll(s)`。C++20 の `countr_zero` でもよい）で得る」とする。前の項目の式も `s & ~(1ULL << v) & ~adj[v]` にそろえるか、「32 bit なら」と添える

### 2. 直すとよい｜F7・U6（記法・断片）｜#chromatic-number・#independent-set の $N(v)$・$N(X)$

- **問題**：頂点数の $N$ と隣の集合の $N(v)$ が同じ文字で、$N(X)$（集合の隣の和集合）は定義がない。#independent-set の節だけを読むと $N(v)$ の定義もない（定義は #chromatic-number の括弧の中だけ）
- **根拠**：clarity U3・U6、fact F7。95・96 行で $Y \setminus (\lbrace v \rbrace \cup N(v))$・$B \setminus N(X)$ を説明なしに使う
- **直し方**：コードと #library の `adj[v]` に合わせて $\mathrm{adj}(v)$ と書くか、#independent-set の最初に「$N(v)$ は $v$ の隣の頂点の集合、$N(X)$ は $X$ のどれかの頂点に隣接する頂点の集合」と添える

### 3. 直すとよい｜U3（飛躍）｜#chromatic-number の「包除原理で覆う数を数える」

- **問題**：「$S$ の中だけで $k$ 個選ぶ方法は $\mathrm{ind}(S)^k$ 通り」から「覆われない頂点の集合について包除原理」への橋が 1 文ない。$\mathrm{ind}(S)^k$ が「和集合が $S$ に収まる組の数」であること、それを包除で「和集合がちょうど $V$」に絞ることが読み取りにくい
- **根拠**：clarity U3。前提の inclusion-exclusion を読んだ読者でも、符号 $(-1)^{N - \lvert S \rvert}$ が $V \setminus S$（覆われないと決めた頂点）の大きさから来ることは本文から直接は出ない
- **直し方**：「$\mathrm{ind}(S)^k$ は和集合が $S$ に収まる組の数である。覆われない頂点の集合 $T = V \setminus S$ について包除原理を使うと」のように 1 文足す

### 4. 直すとよい｜F2（言い落とし）｜#independent-set の最大クリークの補グラフ

- **問題**：「隣接の bit を反転し、自分を除いたもの」だけでは、$N$ 以上の bit も 1 になる。mis.cpp は後半・前半とも全体のマスクを取るので結果的に正しく動くが、一般の助言としては「$N$ bit に絞る」が要る
- **根拠**：`~adj[v]` は 64 bit 全部を反転する。別の書き方（`popcount` で大きさを数える、`s == full` で比べる）では誤る
- **直し方**：「隣接の bit を反転して $N$ bit に絞り、自分を除いたもの（`~adj[v] & full & ~(1ULL << v)`）」とする

### 5. 直すとよい｜手引き §14-11（構成）｜確認問題の置き場所

- **問題**：確認問題 2 問が #chromatic-number・#independent-set の中に置かれ、`## 確認問題 {#quiz}` にまとまっていない。同じ b4 の generating-function-counting は発展の概要でも #quiz にまとめている（その報告の 3）
- **根拠**：style-guide §14-11「確認問題：`## 確認問題 {#quiz}` にまとめる」。ただし既存のページ（basics の多く、static-top-tree など）には節の中に置いたものもあり、運用がそろっていない
- **直し方**：メインがバッチでそろえる方針を決め、それに合わせて #quiz に移すか、このままにする

### 6. 直すとよい｜U9（読みやすさ）｜81 行（205 字）と 71 行

- **問題**：81 行の 1 文が 205 字で、$O(3^N)$ の方法・ABC187 F・補グラフの彩色数の 3 つの話が 1 段落に入っている。71 行も 137 字
- **根拠**：textlint の sentence-length の警告。clarity U9（1 文 120 字・1 段落 1 主張）
- **直し方**：81 行を「$O(3^N)$ の別法」と「クリークに分ける問題は補グラフの彩色数」の 2 段落に分け、括弧の中の ABC187 F の注記を独立の文にする

### 7. 直すとよい｜F9（出典の記録）｜付録 B のドメイン

- **問題**：執筆者は制約を raw.githubusercontent.com から読んでいる。付録 B にはない（参考の URL は github.com なので、ページ自体は規則に合う）
- **根拠**：`python3 tools/check_noai.py https://raw.githubusercontent.com/...`：noai・noimageai の指定なし
- **直し方**：メインが付録 B に raw.githubusercontent.com（github.com の生ファイルの配信先）を足す。ページは直さなくてよい

## 執筆者の未解決の点への回答

- **分枝の 1.47^N・1.38^N**：特性根を計算して 1.46557・1.38028 を確認した。drken 氏の記事の $O(1.381^n)$ とも一致する。分枝の規則（次数 0・1 は取る、次数 3 以上で分ける）も正しい。コード片がないことは発展の概要として問題ない
- **2 つの法で両方 0 になる誤判定**：本文の「どちらかが 0 でなければ $f(k) > 0$ は確実」は正しい。誤るのは $f(\chi)$ が 2 つの素数の積の倍数になるときだけで、固定の法を狙ったテストでない限り起きにくい。今の「気になるなら法を乱択する」で足り、確率の評価を足す必要はない
- **要点と summary**：並べて読んで食い違いはない（要点に最大クリークと計算量が加わっただけ）

## 台帳への提案の確認

- abc187_f を chromatic-number の practice に足す提案：補グラフの彩色数として解けるのは正しい（$N \le 18$ なので $O(2^N N)$ でも $O(3^N)$ でも間に合う）。ただし例題の持ち主（subset-enumeration-dp）の解き方と違う手法の練習として載せるなら、練習の方針の折りたたみで「補グラフ」と書くと解き方が見える点に注意。足すかどうかはメインの判断でよい

## 総合の判定

小さな直しで可。直すべき 1 件（#library の `__builtin_ctz` と 64 bit の食い違い）、直すとよい 6 件。事実・計算量・コード片の正しさには誤りが見つからなかった。
