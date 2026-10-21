# cpp-integer-overflow（整数のオーバーフローと __int128）の検証

- 対象：docs/cpp/cpp-integer-overflow.md、snippets/cpp-integer-overflow/（22 組）、docs/img/cpp-integer-overflow/wrap-around.svg
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21。コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0

## 確かめたこと

- `python3 tools/check_pages.py --page cpp-integer-overflow`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-integer-overflow`：22 片・43 回のコンパイルで期待と違う 0
- `npx textlint docs/cpp/cpp-integer-overflow.md`：指摘なし
- **リンク先**：cpp-views-basics#iota-int・#iota-size-mismatch、cpp-types-literals、cpp-io、cpp-environment、cpp-undefined-behavior、math/integer-division、math/integer-root はある。用語集の #overflow・#unsigned-integer はまだない（手引き §13 の 5 のとおり、提案した anchor で書いてよい。メインが用語集に足す）
- **参考の URL**：5 件とも取得できた（200）。cppreference「Arithmetic operators」、cpprefjp「std::ssize」、GCC の __int128 のページ（見出しは「6.1.1 128-bit Integers」、`<title>` は「__int128」）、GCC の Integer Overflow Builtins（見出しは「7.2.5 Built-in Functions to Perform Arithmetic with Overflow Checking」）、libstdc++ の状況表
    - GCC の __int128 のページに「There is no support in GCC for expressing an integer constant of type __int128 for targets with long long integer less than 128 bits wide」がある（#int128 の「リテラルがない」と一致）
    - Integer Overflow Builtins の「無限の精度で計算して第 3 引数の型に直し、等しくなければ true」は本文の説明と一致する
    - libstdc++ の状況表：P0645R10（format）は 13.1、P2093R14（print）は 14.1。本文の「format は GCC 13〜、println は GCC 14〜」と一致する（執筆者の未解決の点 2 は解消）
- **AtCoder の環境**：planning/decisions.md の記録（GCC 15.2.0、`-std=gnu++23`）と本文が一致する。厳密モードの __int128 の扱い（decisions.md の 54 行目）とも一致する
- **本文の主張を手で確かめた**（作業用の場所。g++-13・g++-15、`-std=gnu++23 -O2 -Wall -Wextra`）
    - $10^{10} - 2 \times 2^{32} = 1410065408$：正しい。図の値・代替テキストとも一致する
    - エラーの文面：`ambiguous overload for 'operator<<'`（cout）、`no match for 'operator>>'`（cin）、`no matching function for call to 'min(int, long long int&)'`、`-std=c++23` での `static assertion failed: std::gcd arguments must be integers` と `call of overloaded 'abs(__int128&)' is ambiguous`。どれも両方の版で本文のとおり
    - 警告の文面：`left shift count >= width of type [-Wshift-count-overflow]`、`comparison of integer expressions of different signedness`（-Wsign-compare）、`comparison of unsigned expression in '>= 0' is always true`（-Wtype-limits、`for (size_t i = n - 1; i >= 0; i--)` で確かめた）、`integer constant is too large for its type`、`-Wformat=`（printf の %lld）
    - `__int128 x = 1000000000000000000000000000000;` は両方の版で `5076944270305263616` になった。`(__int128)1'000'000'000'000'000 * 1'000'000'000'000'000` は $10^{30}$
    - `INT_MIN / -1` と `INT_MIN % -1` を入力から読んで実行すると、g++-15 `-O2` でどちらも `Floating point exception`（終了コード 136）。執筆者の未解決の点 3 は本文のとおり
    - ub-check：`-O2` で `same`、`-O0` で `differ`。AtCoder に近い `-march=native` を足しても `same`
    - 執筆者の未解決の点 1：`long long p1 = a * b; p2 = 1LL * a * b; p3 = (long long)a * b;` を `-O2` で動かすと、両方の版で `1410065408 10000000000 10000000000` になり、research の記述（p2・p3 まで壊れる）は再現しなかった。正しい行を先に置くと p1 が `10000000000` になることも再現した。本文が再現した例（比較）に替えたのは妥当。cpp-undefined-behavior#breaks-other-lines は今はループの条件が消える例で書かれ、このページの #signed-overflow-ub へのリンクもあり、食い違いはない
    - `long double`：$10^{18} \cdot 10^{18}$ と $10^{36} - 1$ の差 1 は、$10^{36}$ 付近の刻み（$2^{56}$ 程度）より小さいので区別できない。本文のとおり
    - `__int128` の速さ（complexity の主張）：$10^7$ 回の `(x * 7 + i + c) % m` で、割る数が 64 bit 以下なら long long の 1.0〜1.7 倍、割る数が $2^{100}$ 程度だと約 3.0 倍だった（下の 3）
- **サニタイザ**：int128.cpp を `-fsanitize=undefined` で cases の 2 つ目を入れて動かすと、`parse` で 2 つの報告が出た（下の 1）。ほかの run のコード片の未定義動作は、本文が意図して見せているもの（int-product-ng・edge-values・ub-check・shift）だけ
- **図**：Windows の Chrome（headless）で幅 640px と 358px（スマホの幅から余白を除いた想定）の PNG にして目で確かめた。白の背景・viewBox あり・文字はテキスト（sans-serif）。正の側は実線（青）、負の側は破線（紫）で、色だけに頼っていない。0 が上、INT_MAX と INT_MIN が下で隣り合い、時計回りに増える向きも正しい。catalog の visual は dynamic・priority 3 なので、静的な図で代えてよい（G7 は priority 1 だけを求める）

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | code C8・C2／fact F2 | snippets/cpp-integer-overflow/int128.cpp の `parse`（取り込み `read`、本文 #int128-io）と int128.yaml の cases の 2 つ目 | `parse` は符号を外した絶対値を正の側に積み上げてから符号を付けるので、$-2^{127}$（`-170141183460469231731687303715884105728`）を読むと $2^{127}$ を作る途中であふれる（未定義動作）。しかも cases の 2 つ目がちょうどこの値で、期待どおりの出力になるのはたまたまである。直前の段落は「$-2^{127}$ を先に正へ直すとあふれるため」に `to_str` で符号を反転して桁にする、と説明しており、同じ節の `parse` がその注意に反している | `g++-15 -std=gnu++23 -O1 -fsanitize=undefined` で cases の 2 つ目を入れると、`int128.cpp:26:33: runtime error: signed integer overflow: 0x7ff…ff8 + 8 cannot be represented in type '__int128'` と `int128.cpp:27:31: runtime error: negation of 0x8000…0 cannot be represented in type '__int128'` が出た | 負の側に積み上げる形にする。例：`x = x * 10 - (s[i] - '0');` で積み上げ、`return s[0] == '-' ? x : -x;`（$2^{127} - 1$ の否定は収まる）。本文の「入力は string で読み、先頭から x = x * 10 + 桁 で組み立てる」の文も合わせて「負の側に積み上げ、最後に符号を決める（to_str と同じ理由）」に直す。直さないなら、cases から $-2^{127}$ を外し、本文に「$-2^{127}$ は読めない」と書く |
| 2 | 直すとよい | clarity U3／fact F2 | #unsigned-size の箇条書き 2 つ目の末尾「`v.size() - 1` には警告が出ない」 | 直前の箇条書きの `for (int i = 0; i < v.size() - 1; i++)` には、`int` と `size_t` の比較なので `-Wsign-compare` の警告が出る。「`v.size() - 1` には警告が出ない」は式そのものの話だが、直前のループにも警告が出ないと読める | g++-15 `-Wall -Wextra` で、そのループに `comparison of integer expressions of different signedness: 'int' and 'std::vector<int>::size_type'` が出た | 「`v.size() - 1` の引き算そのものには警告が出ない（`i < v.size() - 1` の比較には `-Wsign-compare` が出るが、`size_t i` で書くと何も出ない）」のように、何に出ないのかを明示する |
| 3 | 直すとよい | fact F1 | front matter の `complexity` と要点の「計算量」 | 「手元で $10^7$ 回の積・割り算は long long の 2.5 倍以内だった」は、割る数が 64 bit 以下の場合の値である。割る数が 64 bit を超えると約 3 倍になり、「以内」が外れる（執筆者の未解決の点 4 のとおり）。辞書として引く計算量の欄に、条件の付かない 1 回の計測値を置くと言い過ぎになる | `(x * 7 + i + c) % m` を $10^7$ 回：$m \approx 2^{40}$ で long long の 1.68 倍、$m \approx 2^{100}$・$2^{120}$ で 2.98 倍・2.93 倍（g++-15 `-O2`） | 「どれも 1 回 O(1)。__int128 の割り算は関数の呼び出し（__divti3 など）になり、手元の計測では long long の 1〜3 倍程度（割る数が 64 bit を超えると遅い）」のように、条件と幅で書く |
| 4 | 直すとよい | code C3 | min-max-ok.cpp の取り込み（#min-max-types） | 取り込みの 3 行目 `max({0LL, x, 2 * x})`（初期化子リスト）は本文で説明していない。初期化子リストでは「要素の型をすべてそろえる」必要がある点は落とし穴として価値があるが、今はコメントだけで分かりにくい | 本文 134〜141 行目に初期化子リストの記述がない | 箇条書きに「`max({…})` の初期化子リストでも、要素の型がそろわないとコンパイルエラーになる（`max({0, x})` は誤り）」を 1 行足すか、取り込みから外す |
| 5 | 直すとよい | code C3 | snippets/cpp-integer-overflow/int128-strict-gnu.cpp の取り込み範囲のコメント | `-std=gnu++23` で通ることを確かめるコード片なのに、行末のコメントが厳密モードのエラーの文面（`static assertion failed…`・`call of overloaded…`）のままである。本文には取り込まないが、後でこのファイルを読む人が誤解する | ファイルの 8〜9 行目。このファイルは `expect: run` で `2 6` を出す | コメントを「// 2」「// 6」などの実際の値にする |
| 6 | 直すとよい | figure G5・G3 | wrap-around.svg | (a) 代替テキストと右下の注記は「10^10 は輪を 2 周して 1410065408 の位置に来る」と言うが、輪の上にその位置の印がなく、図が主張を示していない（注記の文だけ）。(b) スマホの幅（約 358px）では文字が 640px の 0.56 倍、約 7px になり、注記と INT_MAX・INT_MIN の数字が読みにくい | 幅 640px と 358px の PNG で確かめた。$1410065408 / 2^{32} \approx 0.328$ 周なので、印は 0 から時計回りに約 118° の位置（右下）になる | (a) 輪の上の約 118° の位置に点と「1410065408（10^10 の行き先）」のラベルを置く。(b) 右の凡例と注記を輪の下に回して viewBox を縦長（例：480×480）にし、縮めたときの文字を大きくする |
| 7 | 直すとよい | clarity U9／規則（手引き §13.2） | #min-max-types と #int128-strict-mode の見出し | 見出しの一部（`min<long long>(1, x)`・`is_integral_v<__int128>`）だけがバッククォートで囲まれ、ほかの式（`min(1, x)`・`1 << 40` など）は囲まれていない。執筆者の報告のとおり HTML のタグと解釈されないための処置で、check_pages も通るが、§13.2 の「見出しと title を同じにする」から外れている | 本文 126・219 行目と front matter の title | 執筆者の「手引きへの提案」のとおり、メインが「`<…>` を含む部分は見出しでバッククォートで囲み、title とはバッククォートを除いて一致でよい」と決めるか、ほかの書き方にそろえる |
| 8 | 直すとよい | fact F2 | 導入の最後「このページの例はすべて、手元の g++-13 と g++-15（`-std=gnu++23 -O2 -Wall -Wextra`）で確かめた」 | #int128-strict-mode の例は `-std=c++23`、#signed-overflow-ub の比較は `-O0` でも確かめていて、「すべて -std=gnu++23 -O2」と読める書き方と合わない。println は g++-15 だけである | int128-limits.yaml・int128-strict-ng.yaml の flags、ub-check-o0.yaml、int128-println.yaml の compilers | 「断りのない例は…で確かめた」にする |
| 9 | 直すとよい | clarity U8 | 確認問題 1 の答え「$2^{31} - 1$ を超えるとあふれる」 | 積が $-2^{31}$ を下回る場合（$a$ と $b$ の符号が違う）もあふれるので、正の側だけを述べている | `int` の範囲は $[-2^{31}, 2^{31} - 1]$ | 「`int` の範囲（約 $\pm 2.1 \times 10^9$）を外れるとあふれる」にする |

直すべき指摘は 1 件（番号 1）。

## 総合の判定

小さな直しで可。事実の主張・エラーと警告の文面・版の記述は一次資料と手元の実行ですべて確かめられた。直すべきは `parse` の $-2^{127}$ でのあふれ（コード片と本文の 1 文）だけである。
