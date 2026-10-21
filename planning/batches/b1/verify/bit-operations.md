# bit-operations（bit 演算の基本と XOR の性質）の検証

- 対象：docs/basics/bit-operations.md、snippets/bit-operations/{submask,xor-range,count-bit,pitfalls-ng,precedence-ng}.{cpp,yaml}、docs/img/bit-operations/{ops-table,submask-steps}.svg
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21。コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0（比較に g++-13 も使った）

## 確かめたこと

- `python3 tools/check_pages.py --page bit-operations`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/bit-operations`：5 片・期待と違う 0
- **サニタイザ**：submask・count-bit・xor-range を `-fsanitize=address,undefined` で動かした。境界の入力でも指摘は出なかった。入力は $m = 2^{59} + 2^{58} + 7$（部分集合 32 個）、`count_bit(2^60, 60)`（ABC356 D の上限 $N, M \le 2^{60}$）、`xor_range(999999999999, 10^12)` = 8191
- **台帳**：4 問の題名と diff を `tools/ap.py show` で確かめた。abc269_c 384・abc213_a 33・abc356_d 886・abc121_d 1164 で、label・diff・summary は台帳と一致する。例題 1・練習 3 は基礎の目安に合う
- **evidence と参考の URL**：drken の 4 記事を取得した。`<title>` は参考の行の題名と完全に一致する。中身は次のとおり
    - ABC269 C：制約は $0 \le N < 2^{60}$ と「1 の個数は 15 以下」。`for (S = N; S; S = (S - 1) & N)` は空集合を探索しない、という注意がある
    - ABC356 D：法は 998244353、制約は $0 \le N, M \le 2^{60}$（上限を含む）。方針は桁ごとに数える
    - ABC121 D：$f(B) \oplus f(A - 1)$ への分解と、偶数と次の奇数の対の XOR が 1 になること
    - ABC213 A：両辺に XOR する移項
    - 本文の方針はどれもこれと一致する。文の並びと例は記事と違い、近すぎない（F8）。記事の例は $a = 19, b = 14$ で、本文は $12, 10$
- **本文の主張を小さなプログラムで確かめた**（作業用の場所の Python と t.cpp）
    - $a + b = (a \oplus b) + 2(a \text{ AND } b) = (a \text{ OR } b) + (a \text{ AND } b)$：$0 \le a, b < 300$ で成り立つ
    - $f(n)$ の表：$n < 5000$ で一致する。$n \bmod 4 = 1, 3$ の対の数の議論も正しい
    - 「自分以外の XOR」の復元：$N$ が偶数なら各 $A_i$ が奇数回現れ $T$ になる。正しい
    - submask の列挙：$m < 2^{10}$ のすべてで、`(s - 1) & m` の列が $\{u : u \subseteq m\}$ の降順と一致する。証明の筋（最初に違う桁 $q \ge p$ で場合分け）も正しい
    - $3^{15} = 14348907$・$3^{16} = 43046721$・$3^{18} = 387420489$・$3^{20} = 3486784401$。$2^{60} \approx 1.15 \times 10^{18}$
    - count_bit の cases の `1000000000000000000 59 → 423539247696576513` を Python で計算し直し、一致した
    - 演算子の優先順位の 3 例（`x & 1 == 0`・`1 << n - 1`・`a ^ b < c`）は C++ の優先順位のとおり。`x & 1 == 0` に `-Wparentheses` が出ることは precedence-ng の warning で確かめられている
    - 落とし穴（g++-15 `-std=gnu++23 -O2 -Wall -Wextra`、g++-13 `-std=gnu++20` も同じ）
        - `long long b = 1 << 31;` は警告なしに $-2147483648$ になる
        - 定数の `1 << 40` には `-Wshift-count-overflow` が出て、`x & (1 << 40)` は 0 になる
        - `__builtin_popcount` に `long long` を渡すと、警告なしに切り詰められる
        - `-7 >> 1 = -4`、`-7 / 2 = -3`
        - 変数の `1 << n`（n = 40）は 256 だった（下の 4）
    - `std::popcount`・`std::bit_width` に `long long` を渡すとコンパイルエラーになる（下の 5）
    - `__builtin_ctz`・`__builtin_clz` に 0 を渡すと結果が未定義になる（GCC のドキュメントのとおり）
- **リンク先**：すべて存在する。cpp-math-functions・cpp-integer-overflow・bitwise-independence・bit-full-search・bit-dp・fenwick-tree は draft で、bit-dp#subsets-as-integers もある。subset-enumeration-dp・zeta-mobius-subset・xor-basis・patterns/xor は stub。用語集に identity-element がある
- **関連ページとの食い違い**：見当たらない。cpp-integer-overflow#shift-width（1 << 40 は警告が出て 0）、cpp-math-functions#bit-unsigned-only、bitwise-independence#range-xor（累積 XOR）と照らした
- **図**：ヘッドレスのブラウザ（playwright）も cairosvg も rsvg も手元になく、画像にはできなかった。代わりに SVG を読んで確かめた
    - どちらも viewBox があり、背景は白の rect、文字はテキスト（sans-serif）である
    - 文字の右端を DejaVu Sans の字幅（全角は 1em）で見積もった。いちばん右は submask-steps の題の約 459px で、幅 480 に収まる
    - ops-table：$12 = 1100$、$10 = 1010$、AND 1000 = 8、OR 1110 = 14、XOR 0110 = 6、$22 = 6 + 2 \times 8$。どれも正しい。1 の桁は薄い青の塗りに太字も付けていて、色だけで区別していない
    - submask-steps：8 行（1011→1010→1001→1000→0011→0010→0001→0000）の s・s − 1・(s − 1) & m がすべて正しい。bit 2 は灰色の列で、1000 の行は点線の枠と赤字の 1 で示している。色だけには頼っていない
    - 代替テキストは図の値と一致する
    - catalog の visual（static・priority 2）の 2 つの図をどちらも満たしている

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2・F3／clarity U8 | #xor-properties の確認問題「和と XOR」の問いと答え | $a + b = 10$、$a \oplus b = 6$ を満たす非負整数は存在しない。答えの「$a \text{ AND } b = 2$（例：$a = 2$、$b = 8$）」は誤りで、$2 \oplus 8 = 10$ であって 6 ではない。AND の値 $2 = 010$ と XOR の値 $6 = 110$ が bit 1 で重なっている。しかし同じ桁が「両方 1」（AND）と「片方だけ 1」（XOR）を兼ねることはない。答えは偶奇（最下位の桁）だけを条件のように述べているが、偶奇は必要条件にすぎない | $a = 0..10$ の全列挙で、$a \oplus (10 - a)$ がとる値は $\{10, 8, 4, 2, 0\}$ だけだった。$S, X < 200$ の全探索で、解がある条件は「$S \ge X$、$S - X$ が偶数、$((S - X)/2) \text{ AND } X = 0$」とちょうど一致した | 1 問目を解のある組に替える。たとえば $a \oplus b = 4$ なら AND は 3 で、例は $a = 3, b = 7$ になる。そのうえで「$a \oplus b = 6$ はどうか」を 2 問目に回すとよい。偶奇は合うが AND＝2 と XOR＝6 が bit 1 で重なるので解がない、という形で、条件 $((S - X)/2) \text{ AND } X = 0$ を答えに書く。本文の「等号は $a \text{ AND } b = 0$ のとき」の段落にも、AND と XOR は同じ桁に 1 を持たない、の 1 文を足すと問いとつながる |
| 2 | 直すとよい | clarity U3・U4 | #submask の 1 段落目の最後の文 | 「$s$ から始めて $s \gets (s - 1) \text{ AND } m$ を繰り返す」とあり、$s$ の初期値（$s = m$）が書かれていない。図とコードを見れば分かるが、本文だけでは始め方が決まらない | 125 行目 | 「$s = m$ から始めて」にする |
| 3 | 直すとよい | clarity U2／fact F5 | #practice の「練習の方針」ABC356 D | 「998244353 で割った余りを出力する」だけで、足す途中で余りを取らないと `long long` があふれることに触れていない。$N = M = 2^{60} - 1$ なら総和は $60 \times 2^{59} \approx 3.5 \times 10^{19}$ で、$2^{63} - 1 \approx 9.2 \times 10^{18}$ を超える。落とし穴の節の主題（型の幅）とも結び付く | Python で総和を計算した。制約は drken の記事で $N, M \le 2^{60}$ | 「各桁の個数は $2^{59}$ 程度まであり、60 桁分を足すと long long を超えるので、足すたびに余りを取る」を足す |
| 4 | 直すとよい | fact F2 | #pitfalls の 1 段落目「$k \ge 32$ では未定義動作で、`-O2` では 0 などのでたらめな値になる」 | 手元で変数の `1 << n`（n = 40、入力から読む）を `-O2` で動かすと 256 だった。x86 のシフトが幅を 5 bit に切るためである。0 になるのは定数を畳み込んだ場合で、「-O2 では 0」と読める書き方は言い過ぎになる | g++-15・g++-13 の `-O2` で `long long v = 1 << n;`、n = 40 を試すと 256 になった。定数の `1 << 40` は 0 になった | 「未定義動作で、手元では定数なら 0、変数なら 256（40 mod 32 = 8 だけずらした値）になった。どちらも当てにならない」のように、確かめた値で書く |
| 5 | 直すとよい | fact F2 | #popcount の 3 段落目「C++20 の `std::bit_width(x) - 1`」 | `std::bit_width` も `std::popcount` と同じく符号なし整数しか受け取らない。`long long` を渡すとコンパイルエラーになる。1 段落目では popcount に符号なしの注意があるが、bit_width にはない | g++-15 `-std=gnu++23` で `std::bit_width(long long)` を試すと `no matching function for call to 'bit_width(long long int&)'` になった | 「C++20 の `std::bit_width(x) - 1`（x は符号なし。[符号なしだけ](../cpp/cpp-math-functions.md#bit-unsigned-only)）」とする |
| 6 | 直すとよい | fact F7（リンク） | #popcount の 1 段落目、#pitfalls の 1 段落目、#next-steps の 1・2 行目 | 執筆者の未解決の点のとおり、節へのアンカーなしでページにリンクしている。リンク先はどれも同じバッチで draft になり、節がそろった。cpp-math-functions に #bit-unsigned-only・#builtins、cpp-integer-overflow に #shift-width がある。bitwise-independence・bit-full-search も draft | 各ページの見出しを grep した | `../cpp/cpp-math-functions.md#bit-unsigned-only`（std::popcount の文）、`../cpp/cpp-integer-overflow.md#shift-width`（1 << k の文）に直す。subset-enumeration-dp・xor-basis は stub のままなので今のままでよい |
| 7 | 直すとよい | fact F10 | front matter の complexity「全集合とその部分集合の組は合計 O(3^N)」 | 「全集合」は全体集合（$\{0, \dots, N - 1\}$）と読める。要点と本文の「$N$ 要素のすべての集合とその部分集合の組」と意味がずれる | 要点と front matter を並べて読んだ | 「すべての集合とその部分集合の組は合計 O(3^N)」にする |
| 8 | 直すとよい | figure G5 | submask-steps.svg の最後の行の注記「点線の行：s − 1 で bit 2 に立った 1 を消し、下の桁だけが残る。」 | 主語がなく、「s − 1 で」が「消す」に係るように読める。すると「s − 1 が 1 を消す」と誤読しうる。消すのは & m である | SVG の文字を読んだ | 「点線の行：s − 1 で bit 2 に立った 1 を & m が消し、下の桁 011 だけが残る。」とする（幅は約 20px 増え、まだ 480 に収まる見込み） |
| 9 | 直すとよい | 規則（手引き §13.1・§13.2） | #pitfalls の見出しと front matter の sections | 執筆者の未解決の点のとおりである。§13.1 では落とし穴は定型の節で、sections に載せず `## 落とし穴 {#pitfalls}` にする。このページは sections に残し、括弧付きの見出しにしている。ほかの draft のページでも、括弧付き（bit-full-search・binary-search）と定型（greedy-basics ほか多数）が混在している | `grep '^## 落とし穴' docs/*/*.md` | メインがバッチの終わりにどちらかへそろえる。§13.1 に従うなら、sections から pitfalls の行を外し、見出しを `## 落とし穴 {#pitfalls}` にする（anchor は同じ） |

直すべき指摘は 1 件（番号 1）。

## 台帳への提案（確認済みの記録）

- abc269_c・abc213_a・abc356_d・abc121_d の checked に 2026-10-21 を入れてよい。問い・制約・方針を、台帳の evidence の drken の記事で確かめた
- 執筆者の提案（abc356_d の summary に法を足す、abc269_c に「1 が 15 個以下」を足す）は、記事の問題概要・制約と合っている

## 総合の判定

**小さな直しで可**（直すべき 1 件、直すとよい 8 件）。直すべきは確認問題「和と XOR」の誤りだけである。1 問目の組（和 10・XOR 6）には解がなく、例の値も合っていない。本文の性質・表・証明・落とし穴・コード片・図には、事実の誤りは見つからなかった。執筆者が自分で導いた主張は、全列挙と小さなプログラムで確かめた。対象は $f(n)$ の周期、submask の列挙順と証明、count_bit、$3^N$ の値、コンパイラの挙動である。図は画像にできなかったため、座標と字幅の見積もりで確かめた。
