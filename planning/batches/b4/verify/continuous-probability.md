# b4 検証：continuous-probability

- 対象：docs/comb/continuous-probability.md、snippets/continuous-probability/kth-max.{cpp,yaml}、docs/img/continuous-probability/holes-angles.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px（--scale 2）の PNG にして目で確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page continuous-probability`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/continuous-probability`：10 case 一致
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library`：警告なし。下の乱数試験をこのバイナリで実行して異常なし（2 通りの方法の一致の assert も通る）
- 独立の確かめ：Python で各 $t$ の $P(Y > t)$ を素朴な DP で求め、長さ 1 の区分ごとに Simpson 法（200 分割）で積分した値と、コード片の出力を比べた。$N \le 5$・$0 \le L_i < R_i \le 8$・$K$ ランダムの 150 通りで、すべて $2 \times 10^{-6}$ 以内で一致。case の `4 2 / 0 3 / 1 5 / 2 4 / 0 1` はモンテカルロ法 40 万回で 2.57609、正しい値 2.576389 と合う
- `npx textlint`：エラー 0・警告 7（執筆者の報告と同じ。数式の括弧・文の長さ・助詞の誤検出）
- 本文の数値を計算し直した：$P(X + Y \le 1) = 1/2$、$P(\lvert X - Y \rvert \le 1/2) = 1 - 2 \cdot 1/8 = 3/4$、$E\lvert X - Y \rvert = \int_0^1 (1-t)^2 dt = 1/3$、$K/(N+1)$ の $N=1$・$N=2, K=2$ の値。どれも正しい
- 円周を切る議論（$N+1$ 点の隙間がどれも期待値 $1/(N+1)$）は正しい。Wikipedia「Order statistic」に「一様分布の $k$ 番目はベータ分布 $(k, n+1-k)$、平均は $k/(n+1)$」とあり、本文と参考の記述に合う
- 区分的な多項式の DP（$f_j \leftarrow f_{j-1} p_i + f_j (1 - p_i)$、初期値 $f_0 = 1$）と、$O(S N^3)$ の数え方（1 区分で $N$ 回 × 状態 $O(N)$ × 次数 $O(N)$）は正しく、コード片の `kth_max_by_integral` と記号まで一致する。要点・complexity・本文の計算量は一致
- 区分の中の順位の方法：端点が整数なので、区分に入った変数は区分の中で独立に一様になり、$s$ 番目に大きい値の期待値 $x + 1 - s/(j+1)$ は正しい。ikatakos 氏の解法の節にある答えの集計 $\left(x+1-\frac{K-k}{j+1}\right) dp[j][k]$（$k<K\le j+k$）と一致。kmjp 氏の記事も同じ DP（区分の上と中の個数）で $O(N^3 \max R)$
- ABC226 H：`python3 tools/ap.py show abc226_h` → H. Random Kth Max・diff 2813。ikatakos 氏のメモの制約 $1 \le K \le N \le 50$、$0 \le L_i < R_i \le 100$（整数）で、本文の「端は整数で範囲も小さい」と $O(V N^3) \approx 1.25 \times 10^7$ は妥当。kmjp 氏のコードは mod 998244353 で出力しており、本文の「mod で出す」と合う
- AGC021 B：`ap.py show agc021_b` → B. Holes・diff 2130。drken 氏の記事の方針（ボロノイ図、無限の領域は凸包の頂点だけ、隣の辺を 90 度回した偏角の差 ÷ $2\pi$）と本文の方針が合う。執筆者が自分で導いた「辺の途中の点は帯で確率 0」「全点が一直線なら両端が 1/2」は、垂直二等分線が平行になること・2 つの半平面に分かれることから正しい（$N \ge 2$ なので一直線の場合も両端が存在する）
- 図：A(120,220)・B(280,220)・C(200,100)。A の内角は $\arctan(120/80) = 56.31°$ で外角 123.69°、C の内角 67.38° で外角 112.62°。確率 0.3436・0.3436・0.3128 で図の値（0.344・0.344・0.313）と一致。破線は各辺の外向きの法線の向きで、弧は凸包の外側で 2 本の破線を結ぶ。D(200,180) は三角形の内側。360px で文字は約 12px で読め、ラベルと線の重なりはない。代替テキストが値まで書いていて図なしでも通じる。catalog の visual は null なので G7 は対象外
- Library Checker：GitHub の library-checker-problems の `geo` に `static_convex_hull`・`sort_points_by_argument` があることを `gh api` で確かめた
- リンク先の anchor（probability-basics#ratio・argument-sort#atan2・expectation-tail-sum#continuous）は存在する
- 参考の URL：4 件とも開けて内容は書かれたとおり。題名は指摘 1

## 指摘

### 1. 直すべき｜事実（F9）｜#references の drken・kmjp・ikatakos の 3 行

- **問題**：参考のブログの題名が、記事の h1 と違う
    - drken：本文「AtCoder AGC 021 B - Holes (500 点)」→ 実際は「AtCoder AGC 021 B - Holes (黄色, 600 点)」（点数まで違う）
    - kmjp：本文「AtCoder ABC #226 : Ex - Random Kth Max」→ 実際は「AtCoder ABC #226 : H - Random Kth Max」
    - ikatakos：本文「AtCoder Beginner Contest 226 G,H問題メモ」→ 実際は「AtCoder Beginner Contest 226 F,G,H 問題メモ」
- **根拠**：`curl` で取った drken・kmjp の `<title>`、ikatakos の h1（`AtCoder Beginner Contest 226 F,G,H 問題メモ`）。手引き §15-24「ブログの題名は記事の h1 を使う」
- **直し方**：3 行の題名を上の実際の題名に置き換える

### 2. 直すとよい｜事実（F2）｜#what の最後の段落

- **問題**：「多項式を有理数の範囲で積分しても係数は有理数のままなので、答えは有理数になる」は、連続値の確率の問題一般には言い過ぎである。同じページの角度の比の型（AGC021 B）では答えが外角 ÷ $2\pi$ で無理数になる
- **根拠**：AGC021 B の答えは角度 ÷ $2\pi$（drken 氏の記事のとおり、実数を小数で出力する）
- **直し方**：「範囲の端が有理数で、確率が区分的な多項式の積分で書けるときは、係数は有理数のままなので答えも有理数になる」のように条件を付ける

### 3. 直すとよい｜分かりやすさ（U3）｜#ratio の 2 段落目

- **問題**：「有界な領域に落ちる確率は 0 になり、無限に伸びる領域だけが残る。…確率はくさびの角度 ÷ $2\pi$」と読むと、無限に伸びる領域はどれも正の確率を持つように読める。実際は幅が一定の帯（例題の詳細にある辺の途中の点の領域）も無限に伸びるが確率は 0 である。例題の解法の詳細まで読まないと分からない
- **根拠**：半径 $r$ の円で帯の面積は $O(r)$、円は $O(r^2)$ なので比は 0。くさびの角度が 0 の場合にあたる
- **直し方**：「無限に伸びる領域でも、幅が一定の帯のように遠くで開かないものは確率 0 で、開く角度だけが効く」のような一言を足す

### 4. 直すとよい｜事実（F10）・分かりやすさ（U1）｜front matter の summary（提案としてメインへ）

- **問題**：要点の「何ができるか」は「小さい方から $K$ 番目の期待値は $K/(N+1)$」と正確にしたが、summary は「K 番目の期待値は K/(N+1)」のままで、向きがない。ページの後半と例題は「$K$ 番目に大きい値」を扱うので、summary だけ読むと大きい方から $K$ 番目と取り違えうる（大きい方からなら $(N+1-K)/(N+1)$）
- **根拠**：要点と summary を並べて読んだ
- **直し方**：summary を「N 個の一様乱数の小さい方から K 番目の期待値は K/(N+1)」にする提案をメインに上げる（執筆者は summary を変えない規則なので）

## 台帳・提案について（指摘ではない）

- abc226_h の approach を「長さ 1 の区分ごとの個数の DP と区分の中の順位の期待値（多項式の積分でもよい）」へ変える提案は妥当。kmjp・ikatakos の両方が前者で確かめられた。evidence に ikatakos の URL を足す提案、checked に 2026-10-22 を入れる提案にも賛成
- agc021_b は drken 氏の記事で問いと方針を確かめた（checked は既に入っている）
- 用語「順序統計量」の定義案は Wikipedia の記述と合う

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 3）。計算・コード片・図はすべて正しく、直すべきは参考の題名だけである。
