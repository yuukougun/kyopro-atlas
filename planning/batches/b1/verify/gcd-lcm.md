# gcd-lcm の検証（工程8b・b1）

- 対象：docs/math/gcd-lcm.md、snippets/gcd-lcm/（euclid・reduce-fraction の 2 組）、docs/img/gcd-lcm/euclid-squares.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/gcd-lcm.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page gcd-lcm`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/gcd-lcm`（2 片・コンパイル 2 回・期待と違う 0）、`npx textlint docs/math/gcd-lcm.md`（0 errors・11 warnings。文の長さ・読点・助詞の重なりで、数式を含む文が主。§13.8 の範囲）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- 数値を作業用の場所で計算して確かめた（Python と g++-15）：
    - 互除法の最悪回数の表：上限以下の最大のフィボナッチ数は $F_{44}$（$10^9$）・$F_{87}$（$10^{18}$）・$F_{92}$（`long long` の最大）で、$(F_{k}, F_{k-1})$ の割り算の回数は 42・85・90。Lamé の定理（$n$ 回かかる最小の組は $(F_{n+2}, F_{n+1})$）から、これが各上限での最悪でもある。表・要点（85 回以下）・本文（多くても 90 回ほど）は一致。執筆者の未解決の点 3 つ目は確認済み
    - $\operatorname{lcm}(1, \dots, 43) = 9419588158802421600 \approx 9.4 \times 10^{18} > 10^{18}$、$\operatorname{lcm}(1, \dots, 42) \approx 2.2 \times 10^{17}$。本文どおり
    - 素朴な再帰の gcd に $(4, -6)$ を渡すと $-2$（本文どおり）。`std::lcm(int, int)` の戻り値の型は `int`（`static_assert` で確認）。$\sqrt{2^{63}-1} \approx 3.04 \times 10^9$（「値が $3 \times 10^9$ 程度まで」どおり）
    - `double` で $10^9 / 999999999$ と $999999999 / 999999998$ が等しくなる（`==` が真）。#reduce-fraction の「`double` では区別できない」を裏付け、コード片の最後の case がこの組を正しく 2 と数える
    - 「2 回の置き換えで半分未満」の議論は $a \ge b$ で正しいが、$a < b$ から始めると成り立たない（指摘 1）
- 定理・性質（F2）：互除法の正しさ（公約数の集合）、多数の gcd の結合、初期値 0・1、割ってから掛ければ lcm が収まる限りあふれないこと、$x \times b > L \iff x > \lfloor L / b \rfloor$（正の整数）、1 つ書き換えと 1 つ除いた gcd の同値、累積 gcd が $O(\log V)$ 種類、既約で分母が正の表し方の一意性の証明、$\gcd(a + x, b + x) = \gcd(a + x, b - a)$、互除法の商と連分数。いずれも正しい
- 計算量（F1）：要点・front matter の complexity・本文が一致
- 問題（F5）：台帳の abc109_c・typical90_v・abc070_c・abc125_c の役割・diff・evidence と本文が一致。本文の要約 4 行は台帳の summary を「全て→すべて」「1つ→1 つ」に直したもので（執筆者の台帳への提案のとおり）、要約に手法名は入っていない。方針は台帳の approach と一致。参考の 4 つの URL は開いて題名が書かれたとおりであることを確かめた（drken の 3 記事・E869120 の 022.cpp）
- リンク：integer-division#overflow・#cpp-vs-math、cpp-integer-overflow#int128、prefix-sum#left-right、cpp-math-functions#gcd-lcm、geometry-precision#line-normalization、glossary#identity-element は見出しがある。ext-gcd・gcd-properties・prime-exponent-vector・stern-brocot・cpp-container-idioms のページもある
- 図：Windows の Chrome（headless=new）で euclid-squares.svg を等倍（600×330）と、幅 390px の画面に幅 358px で（2 倍密度、暗い背景の上に）画像にして目で確かめた。和文も出て、はみ出し・重なりはない。背景は白で塗られ、`viewBox` があり、文字はテキストのまま。1 単位 30px で 16×6・6×6・4×4・2×2 の寸法は正確で、本文の $16 \bmod 6 = 4$、$6 \bmod 4 = 2$、$4 \bmod 2 = 0$ と一致。段は色と線の種類（実線・破線・点線）と ①〜③ の説明で区別している。幅 358px では「2×2」の文字が 8px 相当でやや小さいが読める
- 執筆者の未解決の点 1 つ目（ABC109 C の「都市の座標は X と異なる」）：差が 0 の都市があっても $\gcd(g, 0) = g$ で答えは変わらず、本文の方針・詳細は制約に依らずに正しい。書かなくてよい
- 執筆者の未解決の点 2 つ目（frequency_evidence の abc460_e）：指摘 5

## 指摘

### 1｜直すとよい｜fact（F2）・clarity（U3）｜#euclid の「回数の上限」の段落

- **問題**：「2 回の置き換えで、$a$ は半分未満になる」は $a \ge b$ のときだけ正しい。$a < b$ から始めると 1 回目は入れ替わるだけで、2 回後の $a$ は元の $a$ のまま（例：$(3, 100) \to (100, 3) \to (3, 1)$）。続く「1 回目の後は…」で結論は救われているが、最初の文が条件なしの主張になっている
- **根拠**：上の例の計算。$b \le a / 2$・$b > a / 2$ の場合分けも $b \le a$ を暗に仮定している
- **直し方**：「$a \ge b$ なら、2 回の置き換えで $a$ は半分未満になる」とし、「$a < b$ でも 1 回目で入れ替わって $a \ge b$ になる」を足す（その後の $O(\log \min(a, b))$ の文はそのままでよい）

### 2｜直すとよい｜code（C3・C4）・clarity（U6）｜#euclid の取り込み（euclid.cpp:core）と #lcm-overflow の「上の `lcm_capped`」

- **問題**：#euclid の取り込みに `lcm_capped` まで入っているが、#euclid の本文は lcm に触れていない。説明は 2 節後の #lcm-overflow にあり、そこでは「上の `lcm_capped`」と別の節のコードを指す。節を 1 つだけ取り出して読むと、#lcm-overflow ではコードが見えず、#euclid では説明のない関数が出る
- **根拠**：手引き §9・code.md C3（説明にない処理が取り込みの範囲に入っている）、clarity.md U6（「上の」が指すものが節の中にない）
- **直し方**：euclid.cpp の印を `gcd`（`my_gcd` だけ）と `lcm`（`lcm_capped` だけ）に分け、#euclid には `gcd`、#lcm-overflow の段落の位置に `lcm` を取り込む。#lcm-overflow の「上の `lcm_capped`」は「次の `lcm_capped`」にする

### 3｜直すとよい｜clarity（U9）｜#pitfalls の 3 つ目の見出し「gcd が 0 で割る」

- **問題**：「gcd が 0 で割る」は主語と述語が合わず、何が起きるかが読み取りにくい（割るのは gcd ではなく、gcd で割る側）
- **直し方**：「**gcd で割ると 0 除算になる**」などにする

### 4｜直すとよい｜fact（F7）｜front matter の sections と本文の見出し #prefix-suffix-gcd、signs（提案。front matter はメインが直す）

- **問題**：見出しと sections の title が「（1つ除いた gcd）」、signs が「1つだけ書き換え」「全ての点を訪れられる」で、本文のほかの箇所（「1 つ」「すべて」）と表記が揃っていない。執筆者は本文の問題の行は直したが、front matter は直せない
- **根拠**：手引き §7・prh（執筆者の台帳への提案と同じ規則）。textlint は見出しを指摘していないが、要点の「いつ使うか」は「すべて」「1 つ」で書いてあり、signs と食い違う
- **直し方**：メインが sections の title を「左右からの累積 gcd（1 つ除いた gcd）」、signs を「1 つだけ書き換え（取り除い）たときの gcd の最大」「等間隔に移動してすべての点を訪れられる最大の幅（gcd）」にし、本文の見出しをそろえる。summary の「1つ除いた gcd」も同じ

### 5｜直すとよい｜fact（F10）｜front matter の frequency_evidence の「recent 1（abc460_e）」（提案。メインが判断する）

- **問題**：執筆者の未解決の点 2 つ目。台帳の abc460_e は pages が reformulation・digit-and-mod・counting-mindset で、gcd-lcm はない。ikatakos 氏の記録の解法の節（台帳の evidence。問題文の節は使わない）を確かめると、桁数 $d$ を固定して $(10^d - 1)x \equiv 0 \pmod M$ に直し、$g = \gcd(10^d - 1, M)$ として $x$ が $M / g$ の倍数であることを使う。gcd は使うが、中身は「mod $N$ で $A$ の倍数になる条件は $\gcd(A, N)$ で決まる」で、gcd-properties（#next-steps の「mod の周期」）の話題に近い。gcd-lcm の本文（互除法・lcm・累積 gcd・既約分数）の型の例ではない
- **根拠**：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460 の E の解法の節、data/problems.yaml の abc460_e
- **直し方**：根拠として残すなら「gcd を道具として使う」程度の重さとみなし、frequency A の判断は「前提として 14 ページに届く」を主にする。gcd-properties の frequency_evidence に移す（または両方に書く）ことも検討する。台帳の abc460_e に `checked` の日付と、summary（いまは「（執筆時に確かめる）」）を担当のページの執筆時に入れる必要がある点も申し送る

### 6｜直すとよい｜clarity（U3）｜#reduce-fraction の「既約」

- **問題**：「既約」「互いに素」を定義なしで使い（一意性の証明の「$p$ と $q$ に共通の素因数はない」で意味が分かる程度）、用語集へのリンクもない。読者の想定（レート 1000 前後）では知っていることが多いが、断片で読むと定義がない
- **直し方**：執筆者の用語集への提案（互いに素・既約分数）をメインが反映したら、#reduce-fraction の最初の「既約」に用語集へのリンクを付ける。用語集に入れないなら、手順 1 の後に「（分子と分母の gcd が 1 の状態を既約という）」を足す

## 総合の判定

**小さな直しで可**。直すべき指摘は 0、直すとよい指摘は 6（うち 4・5 は front matter と台帳にかかわるメインへの提案）。事実・数値・コード片・図はすべて確かめた範囲で正しい。
