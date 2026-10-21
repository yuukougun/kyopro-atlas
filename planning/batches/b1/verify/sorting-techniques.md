# sorting-techniques（ソートで考える）の検証

- 対象：docs/basics/sorting-techniques.md、snippets/sorting-techniques/（matching・ratio-sort・ratio-double-ng）、docs/img/sorting-techniques/matching.svg
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page sorting-techniques`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/sorting-techniques`：3 片・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `npx textlint`：エラー 0・警告 3（72 行と 146 行の max-comma は数式の中の読点、192 行の sentence-length は練習の方針の折りたたみ全体を 1 文と数えたもの。どれも誤検出で、手引き §13.8 のとおり残してよい）
- **front matter**：git diff で、変わったのは complexity・stage・sections への next-steps の追加と、要点の計算量・句点・`<=` のコード書式だけ。手引き §2.1 の範囲に収まる。sections の 5 節は見出しの文字と anchor が一致する
- **台帳**：4 問（abc121_c 360・typical90_n —・abc308_c 605・abc187_d 650）の label・diff・summary が data/problems.yaml と一致する。例題 1・練習 3 は catalog（basics.yaml）と手引き §10 の目安（基礎は例題 1）に合う。例題の見出しは §13.3 の形
- **evidence と参考の URL**：6 件とも取得した。題名は本文の参考の行と一致する
    - drken ABC121 C：安い店から pair のソートで買う。本文の方針と解法の詳細と一致する
    - drken ABC308 C：double では誤差で WA、分母を払った整数の比較、stable_sort。本文の比率の節・練習の方針と一致する（記事は long double でも通ると書く。本文は long double に触れないが、誤りではない）
    - drken ABC187 D：(A+B, A) の辞書順は嘘、差は 2A+B 縮む、差が負になったら止める。本文と一致する。記事の反例（総和 100・99・98）と本文の反例 (0,10),(6,3),(6,3) は別の数で、F8 の問題はない
    - Reputeless/tenkei_90 014.md：ページがある
    - cppreference stable_sort：「O(N·log²(N)) comparisons（enough extra memory なら O(N·log(N))）」。執筆者の未解決の点の計算量の記述は正しい。front matter の complexity がメモリの取れる場合だけを書くのは要点と矛盾しない
- **執筆者の未解決の点**
    - 図：ヘッドレスのブラウザ・rsvg・cairosvg が手元になく、画像にはできなかった。座標を読んで確かめた（下の「図」）
    - stable_sort の計算量：上のとおり cppreference と一致する
    - 確認問題の $T_i W_j < T_j W_i$：小さなプログラムで、$N \le 6$・$T, W \in [1, 6]$ の 2000 ケースで全順列の最小と一致することを確かめた（Smith の規則）。$W_i$ が等しければ $T_i$ の小さい順でよいことも同じ式から出る
- **本文の主張を確かめた**（作業用の場所で実行。どれも正しい）
    - `<=` の比較関数：要素がすべて同じ値の配列で `std::sort`（g++-15 -O2 -fsanitize=address）。n = 16 では落ちず、n ≥ 17 で `heap-buffer-overflow`（READ of size 4）。`-D_GLIBCXX_DEBUG` では「Error: comparison doesn't meet irreflexive requirements, assert(!(a < a)).」で止まる。同じ値を含まない配列でも `_GLIBCXX_DEBUG` は同じ文で止まる（確認問題の答えを支える）
    - `999999998.0/1999999997.0 == 999999999.0/1999999999.0` は double で true（どちらも 0.49999999974999997931）。正しい順は 2 番目が大きく、ratio-sort の期待「2 1」と一致する（展開すると $2 \times 10^{18} - 5 \times 10^9 + 2 < 2 \times 10^{18} - 5 \times 10^9 + 3$）
    - 1 対 1 の対応：$N \le 6$・値 $[-5, 5]$ の 3000 ケースで、両方ソートして組んだ和が全順列の最小と一致した。並べ替え不等式（同じ向きで最大、逆向きで最小）も同じケースで一致した。証明（各点をまたぐ組の数の下限 $\lvert p - q \rvert$ と、ソート順での等号）は論理を追って正しい
    - 落とし穴の反例：(A+B, A) の辞書順の大きい順だと 2 町、2A+B の大きい順だと 1 町
    - 非反射と推移から非対称が出ること、$\varepsilon$ の例、NaN の例、分母が正のときの分母を払った比較が狭義の弱順序になること、積が $2 \times 10^{18}$ 以下であること
- **リンク先**：exchange-argument・greedy-basics・two-pointers・binary-search・coordinate-compression・interval-scheduling・event-sort・median-absolute・cpp-comparators・cpp-integer-overflow はすべてある。cpp-comparators は本ページの `#strict-weak-ordering` へ逆にリンクしていて、用語も「狭義の弱順序」でそろっている（aliases に「厳密弱順序」が残るのは別名として妥当）
- **コード片**（C1〜C8）：3 片とも `bits/stdc++.h`・`using namespace std;`・マクロなし・`'\n'`。core は要点の数行。matching は n ≤ 8 で全順列と assert で照らし、cases に空・1 要素・同じ値・10^9 を含む。ratio-sort は制約と分母 ≥ 1 を assert し、cases に同率・率 0・誤差の例を含む。変数名と本文の記号（a・b・idx・s）がそろう。積は long long に収まる。ratio-double-ng は §13.9 の取り込まない失敗例で、期待「1 2」（誤った順）が本文の説明と一致する
- **図**（座標を読んで確かめた。ブラウザでは見ていない）
    - viewBox 0 0 720 400、背景は白の rect、文字はテキスト（sans-serif）
    - x 座標は 60 + 60 × 値で、1・2・3・4・6・8 の位置と x = 5 の縦線（x = 360）が正しい
    - 上段：1–8・4–3・6–2 の 3 本の破線、差 7 + 1 + 4 = 12、x = 5 をまたぐのは 1–8 と 6–2 の 2 組。下段：1–2・4–3・6–8 の実線、1 + 1 + 2 = 4、またぐ組 0。本文・代替テキストの値と一致する
    - 上段を破線・下段を実線にしていて、色だけに頼らない。文字どうし・文字と図形の重なりは座標の上では見当たらない
    - catalog の visual（static・priority 2「2 つの列の対応を線で結び、両方ソートすると交差が消える図」）を満たす

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | clarity U3・fact F2 | #greedy-order の確認問題の答え | 答えは「効果を 1 つの数で表せない」としてから $T_i W_j < T_j W_i$ を導くが、$W_i > 0$ ならこれは $T_i / W_i$ の小さい順に並べることと同じで、結局 1 つの数のキーで決まる。#next-steps の交換論法の行も「キーが 1 つの数で決まらず」と書いており、読者は「1 つの数で決まるのか決まらないのか」で迷う | 式 $T_i W_j < T_j W_i \iff T_i/W_i < T_j/W_j$（$W > 0$）。全順列との照合でこの順が最適 | 「罰金への寄与は順番で変わるので、各仕事の効果としては 1 つの数にならない。ただし入れ替えの式を整理すると $T_i / W_i$ の小さい順という 1 つのキーになる（比べるときは[比率の節](#ratio-and-ties)のとおり掛け算で）」のように、何が 1 つの数にならないのかを分けて書く。#next-steps の行も「キーがすぐには 1 つの数で書けないとき」程度にする |
| 2 | 直すとよい | fact F2 | #strict-weak-ordering の確認問題の答え | 理由「要件は配列の中身ではなく比較関数そのものに課される」は根拠としてずれている。規格の文言は「comp shall induce a strict weak ordering on the values」で、値についての要件と読める。同じ値を含まない配列でも破れる本当の理由は、どの要素 $a$ についても `comp(a, a)`（$a \le a$）が true になり、非反射が配列の値の上で破れていることである | `-D_GLIBCXX_DEBUG` は同じ値を含まない配列（n = 1009 の相異なる値）でも irreflexive の検査で止まった | 「どの要素も自分自身とは同じ値なので、`comp(a, a)` は配列の各要素について true になり、非反射を破る。同じ値を含まなくても未定義動作で、`-D_GLIBCXX_DEBUG` でも止まる」と書き直す |
| 3 | 直すとよい | fact F2 | #ratio-and-ties の `stable_sort` の行 | 「番号順に並べた配列を `sort` すると同点の順はばらばらになる」は言い過ぎで、`sort` は同点の順を保証しないだけ（小さい配列では保たれることも多い）。落とし穴の段落の「小さい入力では偶然合っても」とも食い違う | 規格・cppreference の std::sort（安定性は保証しない） | 「同点の順は保たれるとは限らない」にする |
| 4 | 直すとよい | figure G3 | matching.svg | viewBox の幅が 720 で、スマホの本文幅（約 358px）では約 0.5 倍に縮み、14px の文字が約 7px、x = 5 の注記（12px）が約 6px になって読みにくい。右端の「和 12」「和 4」（x = 620）より右と、数直線の左右（値 0 未満・8 超）は使っていない | viewBox 0 0 720 400 と font-size を読んだ（画像にする道具がなく、目では見ていない） | 値の間隔を 60 から 45 程度に詰めて幅を 520〜560 程度にし、文字を 16px、注記を 14px にする。あわせて検証でブラウザに表示して確かめる |
| 5 | 直すとよい | clarity U5 | #pitfalls の 4 つ目の見出し | 見出しは「比較関数のキャプチャと添字」だが、本文はキャプチャ（`[&]` で配列を引く）に触れず、添字の取り違えだけを書いている | 本文を読んだ | 見出しを「番号の配列を並べるときの添字」にするか、「キーの配列は `[&]` で参照して受け取り、引数は番号」と 1 文足す |
| 6 | 直すとよい | fact F2 | #next-steps の中央値の行 | 「最小にする $x$ は、ソートしたときの中央の値である」は $N$ が奇数のときの言い方で、偶数なら中央の 2 つの間のどれでもよい | $\sum \lvert x - A_i \rvert$ は中央の 2 値の間で一定 | 「中央の値（$N$ が偶数なら中央の 2 つの間のどれか）」とする |
| 7 | 直すとよい | clarity U3 | #matching-two-lists の本文 76 行 | 本文は「点 $x$ の左に $A$ が $p$ 個」と書き、証明の折りたたみは「$x$ 以下の」と書く。$x$ ちょうどの点の扱いで言い方がずれる（面積 0 なので結論には影響しない） | 本文と証明を並べて読んだ | 本文も「$x$ 以下に」にそろえる |

直すべき指摘はない。

## 提案（メインへ）

- 台帳：abc121_c・typical90_n・abc308_c・abc187_d の `checked` に 2026-10-21 を入れてよい（4 問とも evidence の解説で問いと方針を確かめた）
- 執筆者の用語集の提案（狭義の弱順序・安定ソート）は妥当。cpp-comparators の本文はすでに「狭義の弱順序」で書かれ、「厳密弱順序」は aliases と summary に残る。summary をそろえるかはメインの判断

## 総合の判定

小さな直しで可（直すべき 0・直すとよい 7）。事実・コード片・台帳はすべて確かめられ、誤りはない。直すとよいのは答えの理由の書き方（1・2）、言い過ぎ（3・6）、図のスマホでの文字の大きさ（4）と細かな表記（5・7）である。
