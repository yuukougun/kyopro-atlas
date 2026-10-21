# multinomial-coefficient の検証

- 対象：docs/comb/multinomial-coefficient.md、snippets/multinomial-coefficient/reorder.{cpp,yaml}、docs/img/multinomial-coefficient/divide.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した確認

- `python3 tools/check_pages.py --page multinomial-coefficient`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/multinomial-coefficient`：コンパイル 1 回・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` で cases と追加の入力（`zzzzzzzzzzzzzzzzzzzzyx` → `462 4024`）を実行：警告・サニタイザの報告なし
- Python の全探索（一時置き場の bf.py）で次を確かめ、すべて一致した
  - cases の期待出力：aab→8、abc→15、aabbc→89（部分列の並べ替えを全列挙）、mississippi→34650 と 107898（個数の組ごとの多項係数の和）。期待出力はプログラムの出力の写しではなく正しい
  - 合流の節の表（A だけ 1,1,1,0／B を足した後 1,2,3,3）は手計算で一致
  - MISSISSIPPI＝34650、6 人を 2 人ずつ 3 組＝15（集合分割の全列挙でも 15）
  - ABC266 G の式 C(G+B,G)·C(G,K)·C(R+B,K+B) を R≤3, G≤3, B≤2 の全探索と照合
  - 同じ大きさのグループを割る DP（ARC067 E の型）を n≤7、A・B・C・D の全組で集合分割の全列挙と照合
  - ABC470 F の方針（成分ごとの多項係数の積、どの成分にも同じ文字がなければ半分）を、ランダムな長さ 2〜6 の文字列と辺 1〜4 本で、偶数回の swap で届く文字列の BFS と照合（400 ケース）
- 20! = 2432902008176640000 < 2^63−1 < 21! を確認
- 参考の 4 件を読んだ（どれも付録 B のドメイン）
  - kazun（abc234_f）：各文字の個数だけで決まる言い換えと、Σ x^m/m! の積に n! を掛ける見方。本文の参考の説明どおり
  - ikatakos（abc470_f）：連結成分・成分ごとの多項係数の積・同じ文字がなければ F/2。制約は 1 ≤ M（辺が 1 本以上）
  - drken（abc266_g）：G と B を先に並べ、K 個の G の左に R、残りを K+B+1 か所に重複組合せ。本文と一致
  - drken（arc067_c）：人数ごとの DP、C(N−i, sk)·(sk)!/(k!(s!)^k)、調和級数で O(N^2 log N)。本文と一致
- 図：ヘッドレスのブラウザがこの環境になかった（chromium・playwright なし）ので、SVG のソースを座標で読んで確かめた。viewBox あり・背景は白で塗り・文字はテキスト（sans-serif）・枠は x=24〜536（幅 560 の中）・最下の文字 y=290（高さ 300 の中）

## 執筆者の未解決の点への回答

- abc470_f で辺が 1 本以上あるか：ikatakos 氏の記録に制約 1 ≤ M とある。大きさ 2 以上の成分が必ずあるので、本文の「なければ半分」は成り立つ。本文の直しは不要（指摘 3 は任意）
- visual が priority 3 なので静的な SVG で代えた点：figure.md G7 の上で問題なし
- 多項定理の段落：短く、別名の「多項定理」に応えていて妥当

## 指摘

### 1. 直すとよい｜clarity U4｜#same-size-groups の DP

- 問題：DP の状態と遷移はあるが、初期値と答えがない。合流の節（#dp-merge）は「初期値と答え」を書いているので、そろっていない。読者は $s$ の始まり（1 から）と答えの位置で迷う
- 根拠：本文の箇条は「状態・遷移・計算量」の 3 つだけ
- 直し方：「**初期値と答え**：$\mathrm{dp}[1][0] = 1$。答えは $\mathrm{dp}[n + 1][n]$（大きさに制限があればその範囲だけを回す）」を足す

### 2. 直すとよい｜fact F1｜要点・front matter の complexity・#dp-merge の計算量

- 問題：合流の DP の計算量 $O(N^2)$ は、種類数 $m$ が $N$ 程度以下のときの値。各段で $(\text{それまでの長さの最大} + 1) \times (c_j + 1)$ なので、合計は $O(N^2 + mN)$ になる（個数 0 の種類も 1 段かかる）。ABC234 F は $m = 26$ で問題ないが、式としては条件が落ちている
- 根拠：$\sum_j (S_{j-1} + 1)(c_j + 1) \le (N + 1)(N + m)$
- 直し方：「$O(N^2)$（$m \le N$ のとき。一般には $O(N^2 + mN)$）」とするか、個数 0 の種類を飛ばすと書く。3 か所（要点・complexity・本文）をそろえる

### 3. 直すとよい｜fact F2｜#practice の「練習の方針」ABC470 F

- 問題：「なければ半分になる」は、大きさ 2 以上の成分があることが前提。制約（1 ≤ M）で満たされるが、方針の文からは読み取れない
- 根拠：辺がないと届く文字列は 1 つだけで、半分にはならない（ikatakos 氏の記録の制約は 1 ≤ M）
- 直し方：「辺は 1 本以上あるので」などの一言を足す（任意）

### 4. 直すとよい｜clarity U6｜#dp-merge のコードの場所

- 問題：合流の節のコードは #meaning の取り込みの中にあり（`count_strings`）、合流の節だけを読むと「コードは式の意味の節」へ戻る必要がある。DP の説明の前にコードが出るので、#meaning で読む人には `count_strings` が何か分からない
- 根拠：#meaning の「上のコードの `count_strings` は合流の節で使う」と、#dp-merge の「コードは式の意味の節の `count_strings`」
- 直し方：取り込みを 2 つの印に分け（`core` に multinomial、`merge` に count_strings）、合流の節で `merge` を取り込む

### 5. 直すとよい｜fact F5・F8｜例題 abc234_f の方針の出典

- 問題：例題の方針（二項係数を掛ける合流 DP）は、evidence の kazun 氏の記事の解き方（指数型の多項式の積）とは形が違う。両者は同値で、本文も #dp-merge の最後で同値を述べているので誤りではない。参考の説明も「指数型の多項式の積として数える見方」と正しく書いている
- 根拠：kazun 氏の記事は E = Σ n! [X^n] ∏ P_α(X) の形で、二項係数の DP は出てこない
- 直し方：直さなくてよい。気になるなら、解法の詳細に「各文字の Σ x^k/k! の積の係数に ℓ! を掛けても同じ」と 1 行足して出典とつなぐ

## 台帳への提案（検証役から）

- abc234_f・abc266_g・abc470_f・arc067_c の `checked` に 2026-10-21 を入れる（上の evidence を読み、要約・方針と食い違いがないことを確かめた）
- abc470_f の summary から「（詳細は執筆時に確かめる）」を外す執筆者の提案に賛成する（本体と alternatives の両方）

## 問題のなかった項目

- fact：F1（指摘 2 以外）・F2（多項定理・割れる条件・空のグループで割れない理由・Lucas への誘導）・F3・F5（check_pages 0 件、要約に手法名なし）・F6（黄の節は節の頭で前提を示す）・F7・F8（例・数値は出典と別）・F9・F10
- code：C1〜C8（core は要点の 2 関数、`'\n'`、マクロなし、modint の `val()` は出力だけ、`int` のあふれなし）
- clarity：U1・U2（割れる理由・合流の重複なし・挿入の可逆性に理由あり）・U3・U5・U7・U8・U9・U10
- figure：G3〜G7（静的な図。破線で A₁ と A₂ を色以外でも区別、代替テキストが要点を述べる）。G1・G2 は動く図がないので対象外

## 総合の判定

**小さな直しで可**（直すべき 0 件、直すとよい 5 件）。事実・コード・図に誤りは見つからなかった。指摘 1・2 を直すとよい。
