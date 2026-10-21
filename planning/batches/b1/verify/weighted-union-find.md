# weighted-union-find の検証（工程8b・b1）

- 対象：docs/ds/weighted-union-find.md、snippets/weighted-union-find/{weighted-union-find,parity}.{cpp,yaml}、docs/img/weighted-union-find/{compression,merge}.svg（動く図はなし）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page weighted-union-find`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page weighted-union-find --check`（直すべき行 0）、`npx textlint docs/ds/weighted-union-find.md`（0 errors・6 warnings。執筆者の報告どおり、要点の入れ子の箇条書き・代替テキスト・確認問題の題の数式の sentence-length と、数式の間の「と」「に」の no-doubled-joshi で、残してよい）
- front matter：`git diff` で変わったのは complexity・stage と sections（§13.2 の範囲）。complexity・要点の計算量・本文の計算量の節が一致する（ならし $O(\alpha(N))$、union by size と経路圧縮の併用が条件）
- コード片：g++-15 (Ubuntu 15.2.0) で `-std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、警告なし。両片の cases を動かして期待出力と一致、サニタイザの報告なし。weighted-union-find の cases を手で計算し直した（本文の例 $x = (0, 3, 2, 7)$ で $x_2 - x_0 = 2$、$x_0 - x_3 = -7$、$x_3 - x_0 = 8$ は矛盾。4 つ目の case は $x = (0, 1, 2, -5, 5)$ で $x_2 - x_4 = -3$、しかも merge(3, 0, 5) で大きさ 2 と 3 の成分をつなぐので、向きの入れ替えが本当に起きる）。parity の cases（長さ 4 の閉路は塗れ、0-2 で奇閉路、自己ループは No）も手で正しい。書き方（bits・using namespace std・マクロなし・`'\n'`）は §9 に合う。取り込みの範囲（core）は構造体だけで、本文の find・merge・差の取得の手順と 1 行ずつ対応する（`w += diff[u] - diff[v]` は find の後の $p_u - p_v$）
- 変異の試験（作業用の場所 v-weighted-union-find/）：merge の `w = -w` を消すと乱数の試験が落ちる。find の圧縮の順序を逆にしても乱数の試験は通ってしまう（指摘 1）。$n \le 40$・80 回に広げると順序の誤りを検出し、正しいコードは通る
- 自分で導いた主張の確認：
    - 「木の高さが 2 以下の小さな例では、圧縮の順序の誤りでも正しく動く」：根 ← a ← v なら diff[a] はすでに根との差なので正しい。高さ 3（r ← a ← b ← c）で初めて c が $x_c - x_a$ になって誤る。本文どおり
    - 「同じ成分で merge すると根が自分自身を親に持つ」：コードの `par[ru] += par[rv]; par[rv] = ru;` で ru = rv なら par[r] = r になり find が止まらない。本文どおり
    - 値の範囲：根との差は受け入れた情報の全域森の経路の和なので $\sum \lvert w \rvert \le 2 \times 10^{14}$。merge の $W$ も全域森の経路の和なので同じ上限。`long long` で足りる
    - 確認問題 3 問・応用の型の確認問題（$A_2 = 3$）を手で解き直して一致
    - ARC188 C の「同じ人の証言 2 つの XOR で 2 変数が消える」：A の証言は $h_A \oplus c_A \oplus h_B = C$。2 つを XOR すると $h_B \oplus h_{B'} = C \oplus C'$。逆に、各人の目標どうしの XOR の制約さえ満たせば $c_A$ は 1 つ目の証言から決められるので、言い換えで失うものはない
- 計算量の主張（執筆者の未解決の点 2）：ACL のドキュメント（document_ja/dsu.md）で `merge`・`same`・`leader`・`size` がならし $O(\alpha(n))$。「経路圧縮だけ、または union by size だけでもならし $O(\log N)$」「$\alpha$ は実用上 4 以下」は Tarjan・van Leeuwen の解析として標準的な事実で、誤りはない（union by size だけなら最悪でも $O(\log N)$ なので「ならし」は弱めの言い方で正しい）。union-find のページが書かれたらリンクに置き換える案に賛成
- Library Checker（執筆者の未解決の点 3）：github.com の yosupo06/library-checker-problems の info.toml と task.md を読んだ。unionfind_with_potential は題名 "Unionfind with Potential"（$a_u \equiv a_v + x \pmod{\mathrm{MOD}}$ の情報と差の質問）、unionfind_with_potential_non_commutative_group は "Unionfind with Potential (Non-Commutative Group)"（$2 \times 2$ 可逆行列で $a_u \equiv a_v x$、質問は $a_v^{-1} a_u$）。本文の「可換でない演算はこの形」は正しい（指摘 6 は書き足しの提案）
- 問題：8 問（例題 2・練習 5・力試し 1）とも `python3 tools/ap.py show` で題名・diff が本文と一致。ABC451 F は ikatakos 氏の記録（解法の節）で、重み付き Union-Find の根に白と黒の数を持たせ、同じ成分の同色を結ぶと以降 −1、違う成分の同色なら一方を反転して少ない方を選ぶ、とあり本文の方針と一致。ARC090 D（$N \le 10^5$、$M \le 2 \times 10^5$、$x_R - x_L = D$）、ABC328 F（$x_a - x_b = d$ の向き、マージテクの別解）、ABC280 F（nan と inf）、典型90 068（Ambiguous）、ABC373 D、ABC327 D の方針も evidence の記事と食い違いがない
- 参考の URL：9 件とも開いて題名を確かめた（drken の Qiita 1・はてなブログ 7、enakai00 1、ikatakos 1）。どれも付録 B のドメイン。本文の例（find の図の 3・−1・2、merge の図の 3・5・4、確認問題の数値）は記事と別で、文の並びも近すぎない
- 図：Windows の Chrome（headless=new、1240×660、等倍）で 2 枚を画像にして目で見た（作業用の場所 v-weighted-union-find/compression.png・merge.png）。値は本文・代替テキストと一致（compression：前 3・−1・2、後 3・2・4。merge：3・5・情報 4・W = 2、つないだ後 2 → 0 が 2、3 → 2 が 5）。背景は白、`viewBox` あり、`font-family="sans-serif"` で文字はテキストのまま。色に加えて破線・太線で区別。merge の図で union by size の同点（大きさ 2 と 2）のとき rv が ru の下につくのはコードの比較（`<`）と一致。重なり・はみ出しは指摘 2 以外なし
- リンク：glossary の #associativity・#identity-element はある。#potential は今ない（指摘 3）。前提・関連のページは stub で、ページへのリンクだけなのは §13.4 に合う

## 指摘

### 1｜直すとよい｜code（C2）｜snippets/weighted-union-find/weighted-union-find.cpp の random_test（322・327 行）

- **問題**：本文の落とし穴の最初に挙げる「圧縮の順序」の誤り（`diff[v] += diff[par[v]]` を `find(par[v])` より前に書く）を入れても、乱数の試験が通ってしまう。$n \le 8$ で union by size だと、高さ 3 の木が圧縮されずに残る場面がほとんど出ないため
- **根拠**：作業用の場所で順序を入れ替えた m1.cpp を作り、`echo "1 0" | ./m1` が終了コード 0。$n$ を `rng() % 40 + 1`、質問を 80 回に広げた m3.cpp は assert で落ち（134）、正しいコードを同じく広げた ok3.cpp は通る
- **直し方**：`int n = rng() % 40 + 1;`・`for (int q = 0; q < 80; q++)` 程度に広げる。または本文の図と同じ一直線の木（union by size を通さず par を直に組む）で find(c) の結果を assert する

### 2｜直すとよい｜figure（G5）｜docs/img/weighted-union-find/compression.svg の上の 2 つの題

- **問題**：左の題「find(c) の前：矢印は親へ。数は diff（親との差）」の終わり（x ≈ 330）と右の題「find(c) の後：どれも根の直下」の始まり（x = 340）がほとんど接していて、画像では「…（親との差） find(c) の後：…」と 1 行の文に見える
- **根拠**：compression.png（上の帯）
- **直し方**：左の題を 2 行に分ける（「find(c) の前」と「矢印は親へ。数は diff（親との差）」）か、右の題を y = 60 程度に下げる。ついでに、中身が空の `<text x="0" y="0" …></text>` が 3 つ残っているので消す

### 3｜直すとよい｜fact（F7）｜#idea の「ポテンシャル」のリンク（61 行）

- **問題**：`../guide/glossary.md#potential` の見出しが用語集にまだない（今は壊れたアンカー）。執筆者は用語集への提案に入れている
- **根拠**：`grep -n potential docs/guide/glossary.md` で該当なし
- **直し方**：メインがバッチの終わりに用語集へ「ポテンシャル {#potential}」を足す。足さないならリンクを外す（どちらかを忘れないよう、メインの反映の一覧に載せる）

### 4｜直すとよい｜fact（F2）・clarity（U3）｜#generalization の 1 つ目の条件（168 行）

- **問題**：結合法則の効き目を「find で足し合わせる順を気にしなくてよい」と書いているが、結合法則が許すのは「まとめる区切り方」で、並ぶ順（どちらを左に置くか）ではない。直後の段落で「順序を入れ替えると結果が変わる場合は向きに気を付ける」と言うので、読者には 2 文が食い違って見える
- **根拠**：非可換群（置換・行列）でも結合法則は成り立つが、$a \cdot b \ne b \cdot a$
- **直し方**：「経路の差をまとめる演算が結合法則を満たす（親までの差と、親から根までの差をどこで区切ってまとめても同じになる）」とする

### 5｜直すとよい｜clarity（U3）｜#idea の「1 回 $O(N + M)$」（59 行）

- **問題**：$M$ と $Q$ がこの節で定義されないまま出てくる。読者は $M$ が情報の数か辺の数か、$Q$ が何かを推し量ることになる
- **根拠**：57〜59 行に $M$・$Q$ の定義がない
- **直し方**：「それまでの情報の数を $M$ とすると、毎回 DFS をやり直すと 1 回 $O(N + M)$ かかり、情報と質問が合わせて $Q = 2 \times 10^5$ 回来ると間に合わない」とする

### 6｜直すとよい｜fact（F2）｜#generalization の Library Checker への言及（172 行）

- **問題**：「置換の合成など」の例と並べて Library Checker の問題を挙げているが、実際に載る演算が何かが書かれていない。読者が問題を開いて置換を探すと戸惑う
- **根拠**：library-checker-problems の unionfind_with_potential_non_commutative_group/task.md：$2 \times 2$ 可逆行列（行列式 1、mod 素数）で $a_u \equiv a_v x$、質問は $a_v^{-1} a_u$
- **直し方**：「Library Checker の Unionfind with Potential（Non-Commutative Group）は、$2 \times 2$ 行列の積でこの形を試す問題である」とする

### 7｜直すとよい｜figure（G5）｜docs/img/weighted-union-find/merge.svg の題（「x_3 − x_1 = 4」）

- **問題**：添字が `x_3` の下線のまま表示され、本文の $x_3$ と見た目がそろわない
- **根拠**：merge.png の左上
- **直し方**：`x<tspan baseline-shift="sub" font-size="10">3</tspan>` のように下付きにするか、「x3 − x1 = 4」とする

## メインへの申し送り（指摘ではない）

- 「ACL では」の囲みを見出しなしで手順の節に置いた件、「使い分け」の anchor（choosing と comparison）の件は、執筆者の手引きへの提案のとおりメインで決める事柄で、このページの誤りではない
- 台帳の `checked` に 2026-10-21 を入れてよい（arc090_b・abc328_f・abc327_d・abc373_d・abc451_f・typical90_bp・abc280_f・arc188_c。evidence の記事で方針を確かめた）。abc451_f の approach に残る制作メモを直す執筆者の提案にも賛成（ikatakos 氏の記録の解法と一致）

## 総合の判定

**小さな直しで可**。直すべき指摘は 0 件、直すとよい指摘は 7 件。事実・計算量・コード・問題の方針に誤りは見つからなかった。試験の強さ（指摘 1）と図の題の重なり（指摘 2）は直しておくとよい。
