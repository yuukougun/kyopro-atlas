# subsequence-matching の検証（工程8b・b1）

- 対象：docs/string/subsequence-matching.md、snippets/subsequence-matching/{next-table,repeated}.{cpp,yaml}、docs/img/subsequence-matching/next-table.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page subsequence-matching`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page subsequence-matching --check`（直すべき行 0）、`python3 tools/check_snippets.py snippets/subsequence-matching`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/string/subsequence-matching.md`（0 errors・20 warnings。半開区間の no-unmatched-pair、数式を含む文の sentence-length、代替テキストの max-comma など。どれも数式・代替テキストによる誤検出で、§13.8 により残してよい）
- front matter：`git diff` で、変わったのは complexity・stage と要点以降の本文だけ。complexity・要点の計算量・本文（表の構築 $O(\sigma N)$・判定 $O(\lvert T \rvert)$・位置のリスト $O(N)$／$O(\lvert T \rvert \log N)$）が一致する。別名の行に aliases がすべてあり、最初の `##` より前にある
- コード片：2 片とも `-fsanitize=address,undefined` 付きでコンパイルし（警告なし）、乱数で素朴な方法と比べた（作業用の場所 v-subsequence-matching/b.py）
    - next-table：|S| ≤ 8・文字 ab の 500 組 × 5 問を Python の部分列判定と比べて一致、サニタイザの報告なし
    - repeated：文字 1〜4 種・N ≤ 6・|S| ≤ 6・|T| ≤ 4 の 1500 組を「S を N 回つないだ列に T の各文字を k 個並べた列が入る最大の k」を直接求めたものと比べて一致。最大の制約の近く（N = 10^12・|S| = |T| = 10^5）で 3 通り（S に z が 1 個だけで T が z の 10^5 個 → 10^7、ab の乱数列と (ab)^{5×10^4} → 499999255800、S = a^{10^5}・T = a → 10^17）を動かし、サニタイザの報告なし（あふれなし）。jump の中の値は idx ≤ 約 10^17、copy * len ≤ 10^17 で `long long` に収まる
    - 書き方（bits・using namespace std・マクロなし・`'\n'`・ラムダは判定の関数）は §9 に合う。取り込みの範囲（core）は要点だけ。cases は境界（1 文字・同じ文字の連続・S にない文字・繰り返しの周の境目）を含み、期待出力は手で数え直して正しい
- 自分で導いた主張を小さなプログラムで確かめた（v-subsequence-matching/t.py。|S| ≤ 7・文字 abc の 3000 例）
    - 「位置 p から照合したとき $S[p, e)$ が $T$ を含む ⇔ $e > r$（照合できなければ $r = N$）」と、例題の答え $\sum_l (r_l - l)$ を、すべての部分文字列の素朴な判定と比べて一致
    - 辞書順最小の部分列の条件 $q < N$ かつ $N - q \ge K - j$ で作った答えが、全部の長さ $K$ の部分列の最小と一致。lexicographic-greedy#feasibility の $p \le N - K + j$ とも同じ式
    - 最短の非部分列の DP（$\mathrm{dp}[N + 1] = 0$、$\mathrm{dp}[i] = 1 + \min_c \mathrm{dp}[\mathrm{nxt}[i][c] + 1]$）の値が、長さ順の全探索の最短と一致。「最小を与える文字のうち最も小さいもの」で位置 0 からたどる復元が、全探索の辞書順最小と一致
    - ABC324 E の判定 $l_i + r_j \ge \lvert T \rvert$ と、$r$ をソートして lower_bound で数える方法（$i = j$ を含む）が、全組の素朴な判定と 2000 例で一致
    - 表の大きさ：$26 \times (10^6 + 1) \times 4 \approx 1.04 \times 10^8$ バイト。部分文字列の数 $2 \times 10^5 \cdot (2 \times 10^5 + 1) / 2 \approx 2 \times 10^{10} > 2147483647$。本文どおり
    - 図と本文の表の値（a：0 3 3 3 5 5、b：1 1 4 4 4 5、c：2 2 2 5 5 5）、$T =$ `bab`・`bc`・`cc` の引き方、確認問題（`abcab` と `ab`）を手で計算し直して一致
- 問題：5 問（例題 1・練習 3・力試し 1）とも `python3 tools/ap.py show` で題名・diff が台帳・本文と一致し、台帳で確認済み。例題 abc452_d はこのページだけにある。arc081_c は dp-reconstruction でも challenge だが、例題でないので重ねてよい
- evidence と参考の URL：6 件とも開き、題名と著者が書かれたとおり（はてなブログ 5 件・Qiita 1 件。どれも付録 B のドメイン）。内容も本文の説明と一致する
    - merom686「ABC452」：始点ごとに次の出現位置の表で照合し、T の同じ文字の連続で同じ位置を使わない注意。制約の数値は書かれていない（未解決の点 1 は、本文が上限を書いていないので問題なし）
    - comet725：照合位置を状態にした DP の別解。参考の説明どおり。台帳の evidence の順を入れ替える執筆者の提案は妥当
    - drken（ABC324 E）：$l_i + r_j \ge \lvert T \rvert$、r をソートして lower_bound、$i = j$ も数える。本文・練習の方針と一致
    - drken（典型90 006）：nex を後ろから作り番兵 N、最も前の出現を取る理由、$1 \le K \le N \le 10^5$。本文と一致
    - merom686「ABC346」：累積個数と割り算、余りが 0 のとき 1 周余分に進める誤り、N を超えたら早めに打ち切ってあふれを防ぐ。本文の注意と一致。S にない文字で答え 0 も一致
    - drken（ARC081 E）：$\mathrm{dp}[i]$ ＝ $A[i, N)$ の部分列にならない最短の長さ、遷移 $\mathrm{dp}[\mathrm{next}[i][c] + 1] + 1$、$\mathrm{dp}[N] = 1$、記録をたどる復元。本文の $\mathrm{dp}[N + 1] = 0$ と同じ値になる
    - 本文の例（`abcab`・`bab`）と文の並びは出典のどれとも違い、近すぎる箇所はない（F8）
    - 台帳の `checked` に 2026-10-21 を入れてよい（abc452_d・abc324_e・typical90_f・abc346_f・arc081_c）
- リンク先：string-basics#substring-vs-subsequence・greedy-basics#proof・lexicographic-greedy#feasibility・glossary#sentinel の anchor はある。subsequence-dp・patterns/subsequence-and-substring は stub（§13.4 によりよい）、ほかは draft。前提にない binary-search-answer・lexicographic-greedy は、上位の帯の節の冒頭で「前提にする」と書いてある
- 図 next-table.svg：Windows の Chrome（headless=new、2 倍密度）で、等倍（560×300）と、暗い背景の画面に幅 358px で画像にして目で見た（作業用の場所 v-subsequence-matching/full.png・narrow.png）。文字のはみ出しや重なりはなく、358px でも数字と説明の行は読める。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`。引いた欄は色に加えて太枠と ①②③ で区別している。catalog の visual（static・priority 2）を満たす。執筆者の未解決の点 2 は解決
- 執筆者の未解決の点 3（表の大きさ・`vector<vector<int>>`）：大きさは上の計算どおり。行ごとに別の確保になり、確保の回数と行ごとの管理の領域が増えることも正しい

## 指摘

直すべき指摘はない。以下はすべて直すとよい。

### 1｜直すとよい｜clarity（U3）・fact（F7）｜#repeated-string と練習の方針（ABC346 F）の N

- **問題**：ページ全体では $N = \lvert S \rvert$（要点・番兵 $N$・表の大きさ）だが、#repeated-string では「$S$ を $N$ 回つないだ」「周の番号が $N$ 以上」と、$N$ を繰り返しの回数に使っている。節の中では $\lvert S \rvert$ と書き分けているものの、要点から読んだ人は「$N$ 回 = $\lvert S \rvert$ 回」と読みかねない。練習の方針の「上限は $N \lvert S \rvert / \lvert T \rvert$」も同じ
- **根拠**：要点の「$N = \lvert S \rvert$」と、#repeated-string の 1 段落目・最後の段落
- **直し方**：節の冒頭で「この節では $N$ は繰り返しの回数を表し、$S$ の長さは $\lvert S \rvert$ と書く」と断る。または繰り返しの回数を別の文字（$R$ など）にする（問題の記号と合わせたいなら前者）

### 2｜直すとよい｜fact（F2）・clarity（U2）｜#greedy-matching の交換の説明

- **問題**：「$q$ より左の位置 $q'$ にも同じ文字があるとする」だけでは、$q'$ が $T[j - 1]$ を拾った位置より右であることが言われていない。$q'$ がそれより左だと拾い直しは順序を壊すので、説明の条件が足りない。また「$(q', N)$」は開区間で、手引き §6（区間は半開区間を基本にする）とずれる
- **根拠**：style-guide §6（117 行）。$S =$ `aba`・$T =$ `ba` で $T[1] =$ `a` を位置 2 で拾う照合に、位置 0 の `a` は使えない
- **直し方**：「$T[j - 1]$ を拾った位置より右で、$q$ より左の位置 $q'$ にも同じ文字があるとする」とし、範囲を「$[q' + 1, N)$ に広がる」と半開区間で書く

### 3｜直すとよい｜code（C3）｜snippets/subsequence-matching/next-table.cpp の match_end と、本文の「位置 $p$ から始めた照合」

- **問題**：本文（コード片の直後の段落）と例題の解法の詳細は「位置 $p$（始点 $l$）から始めた照合」の $r$ を使うが、`match_end` は常に位置 0 から照合し、始める位置を受け取らない。例題を解く読者は、取り込んだ関数をそのまま使えない
- **根拠**：next-table.cpp 21 行 `int p = 0, last = -1;`。本文の「位置 $p$ から始めた照合が…」、例題の「各始点 $l$ で、$p = l$ から」
- **直し方**：`int match_end(const vector<array<int, 26>>& nxt, const string& t, int p = 0)` のように始める位置を引数にし、本文で「位置 $p$ から照合したとき」と対応させる（main と cases はそのままでよい。始点を変えた cases を 1 つ足すとなおよい）

### 4｜直すとよい｜clarity（U3）｜#next-occurrence の図の後の「表の列 $i = 5$ は番兵の行」

- **問題**：同じ文の中で「列」と「行」が混ざる。図では $i$ が横（列）で、コードの $\mathrm{nxt}[N]$ は「行」と呼んでいるので、初めて読む人はどちらを指すか迷う
- **根拠**：図は $i$ を横軸に取り、本文の別の箇所は「表は $N + 1$ 行」「番兵の行」と呼ぶ
- **直し方**：「図の右端の列（$i = 5$）が番兵の行 $\mathrm{nxt}[5]$ で、すべて 5 である。図では $i$ を横に並べている」のように、図の向きとコードの行の対応を一言書く

### 5｜直すとよい｜fact（F1）｜確認問題「表を前から作れない理由」の答えの $O(\sigma N^2)$

- **問題**：前から作る素朴な方法は、行ごとに位置 $i$ から右へ 1 回走査すれば $\sigma$ 個の欄が全部埋まるので $O(N^2)$（＋$O(\sigma N)$）で済む。$O(\sigma N^2)$ は文字ごとに別々に走査した場合で、「かかりうる」としても根拠の手順が書かれていない
- **根拠**：行 $i$ の走査は $N - i$ 文字を見て、各文字の最初の出現を記録すれば終わる。合計 $\sum_i (N - i) = O(N^2)$
- **直し方**：「行ごとに右へ走査し直すことになり $O(N^2)$ かかる」とする

## 総合の判定

小さな直しで可（直すべき 0 件・直すとよい 5 件）。事実・計算量・図・コード片はすべて確かめた範囲で正しく、乱数の比較でも一致した。
