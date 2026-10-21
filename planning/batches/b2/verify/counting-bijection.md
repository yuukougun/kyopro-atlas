# counting-bijection の検証（b2）

- 対象：docs/comb/counting-bijection.md、snippets/counting-bijection/{verify,factorization,product-sum}.{cpp,yaml}、docs/img/counting-bijection/{monotone,non-injective}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証した日：2026-10-21

## 実行したこと

- `python3 tools/check_pages.py --page counting-bijection`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/counting-bijection -v`：3 本とも cases 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 3 本を `g++-15 -std=gnu++23 -O1 -g -fsanitize=address,undefined -Wall -Wextra` でコンパイルし、最大の case（`100000 1000000000`）・`5 4`・`3 9 / 2 1 3`・`1 0` などで実行：警告なし・サニタイザの報告なし
- `npx textlint`：エラー 0・警告 18（数式を含む文の長さ・助詞の重なり。§13-8 の誤検出の範囲）
- `python3 tools/ap.py show abc110_d abc145_d arc058_b arc110_d`：4 問とも label・diff が本文と一致（1695・1009・1905・2078）
- 小さなプログラム（Python、作業用の場所）で、本文の主張を全探索と比べた：
  - lcm(a, b) = 12 の順序付きの組は 15 個（確認問題の答え）
  - AND が x・OR が y の長さ N の列の数を bit ごとの「1・1・2^N − 2・0」の積で数える式（N = 1〜3、3 bit の x・y すべて）が全探索と一致
  - Prüfer 列：n = 3〜6 で木の総数 n^{n−2}、次数 d_v を決めた木の数 (n−2)!/Π(d_v − 1)! が一致
  - ARC110 D の対応：M + N 個の位置から S + N 個を選び、選んだ位置の A_1+1・A_1+A_2+2・… 番目を仕切りとする復元が、各 B の重み Π C(B_i, A_i) をちょうど再現する（A を 6 通り・M = 0〜6）。執筆者の未解決の点「本文の位置の選び方の対応」は正しい
  - 確認問題 3 の (a) が n·2^{n−1} であること（n = 1〜7）
  - factorization の最大の case 957870001 = C(100008, 8)^2 mod 10^9+7 を Python で独立に計算して一致
- 図：`python3 tools/render_svg.py` で幅 390・幅 520（scale 2）・幅 720 の PNG にして目で見た（ヘッドレス Chrome 146、ライトの背景白）。幅 720 で下が切れるのは道具の出力の高さの問題で、幅 390・520 では全体が写る（執筆者の未解決の点と同じ。図の問題ではない）
- 出典：drken の 4 記事を開き、h1 の題名と、ABC110 D の制約（N ≤ 10^5・M ≤ 10^9・10^9+7）、ARC110 D の制約（N ≤ 2000・M ≤ 10^9・A_i ≤ 2000・10^9+7）と答え C(N+M, S+N)、ABC145 D の連立方程式、ARC058 D の行で分ける分類を確かめた。本文の言い回し・例は記事と別（F8 の問題なし）
- 前提とリンク：リンク先の anchor（stars-and-bars#monotone・#applications・#pitfalls、counting-mindset#verify-small・#formula-or-dp、reformulation#independence、prime-exponent-vector#exponent-ops、lattice-paths#basic・#forbidden-region・#independent-axes・#abc145_d、bracket-sequence#properties）はすべて実在し、相手は draft。stub の reflection-principle・cayley-pruefer へは anchor なしでリンクしている（§14-23 どおり）
- Prüfer 列の事実（執筆者の未解決の点）：上の全探索で 3 つとも正しい。cayley-pruefer が draft になったら記法（n と N）だけ照らせばよい

## 指摘

### 1. verify.cpp の assert の番号が本文の 3 つの条件と食い違う

- 重さ：直すべき
- 観点：code（C3 本文との一致）・clarity（U3）
- 場所：snippets/counting-bijection/verify.cpp の check_bijection（取り込み範囲の中）、本文 #bijection の 1〜3 と 67 行目
- 問題：本文は「1. f(x) が Y に入る、2. g(y) が X に入る、3. g(f(x)) = x と f(g(y)) = y」と番号を振り、「3 つの条件を assert で調べる」と書く。コードのコメントは `// 2. 逆に戻せる（単射）` を g(f(a)) == a（本文の 3 の前半）に、`// 3. Y のどの要素も X から来る（全射）` を in_X(g(b))（本文の 2）に付けていて、番号が入れ替わっている。f(g(b)) == b（本文の 3 の後半）には番号がない。本文の番号でコードを読む読者は、どの assert がどの条件かを取り違える
- 根拠：verify.cpp 382〜390 行と本文 55〜57 行を並べて読んだ
- 直し方：コメントを本文の番号にそろえる。例：`assert(in_Y(b, n));  // 1. 行き先が Y に入る`、`assert(g(b) == a);  // 3. 行って戻ると元に戻る（単射）`、`assert(in_X(g(b), n));  // 2. 逆向きの行き先が X に入る`、`assert(f(g(b)) == b);  // 3. 戻って行くと元に戻る（全射）`。順も本文に合わせて並べ替えるとなおよい

### 2. 単射でない対応の節で X と Y の役割がページの約束と逆になる

- 重さ：直すとよい
- 観点：clarity（U3・U6）・fact（F7 記法）
- 場所：#non-injective の 1 段落目（本文 130 行）
- 問題：導入（49 行）で「数えたい対象の集合を X、言い換えた先を Y、f : X → Y」と約束したのに、この節では「数えたい対象を Y、手順の結果を X」と入れ替えている。断り書きはあるが、節だけを読む人も通して読む人も、直前の節までの X・Y と混ざる
- 根拠：49 行と 130 行
- 直し方：この節では別の文字（手順の結果の集合を $P$、対象の集合を $X$、写像を $h : P \to X$ など）を使う。図の見出し「（指定の赤, 残りの 1 個）」「選んだ集合」はそのままでよい

### 3. 本文が力試し ARC110 D の問いと答えをそのまま解いている

- 重さ：直すとよい
- 観点：clarity（U7）
- 場所：#to-lattice-paths の「和と積の両方を位置の選び方にまとめる」（103〜109 行）と力試しの方針
- 問題：本文の設定（N 個の A_i と上限 M、B_1+…+B_N ≤ M の B にわたる Π C(B_i, A_i) の総和）が ARC110 D の問いと同じで、答え C(M+N, S+N) まで本文に書いてある。力試しの一覧の要約と本文が同じ文なので、一覧を見た時点で答えが分かってしまい、力試しの意味が薄れる
- 根拠：191 行の要約と 103 行の設定の比較
- 直し方：どちらかにする。(a) 本文の例を一段小さく（N = 2 で B_1 + B_2 = M ちょうど、など）して対応の考え方だけを示し、和を ≤ M にする「余りの玉」の工夫と閉じた式は力試しの方針の折りたたみに回す。(b) 本文はこのままにし、力試しから外して本文の参照にする（役割の変更は台帳・catalog への提案）

### 4. 非単射の図の破線の矢じりが大きく、色が線と違う

- 重さ：直すとよい
- 観点：figure（G5）
- 場所：docs/img/counting-bijection/non-injective.svg
- 問題：marker が stroke-width に比例して大きくなり、太さ 2.5 の赤い破線 2 本の先に灰色の大きな矢じりが重なって {r₁, r₂} の箱の枠にかかる。線は赤なのに矢じりは灰色（#444）で、「この 2 本が同じ所に届く」強調が弱まる。また下の注記（font-size 12）は幅 390 で約 9px になり読みにくい
- 根拠：render_svg の幅 520（scale 2）と幅 390 の PNG を目視
- 直し方：赤い破線用に fill="#b03030" の marker を別に作り、`markerUnits="userSpaceOnUse"`（markerWidth・markerHeight を 8 程度）にする。2 本の終点を {r₁, r₂} の箱の上寄り・下寄りに少しずらす。注記は 13〜14 にするか 2 行に分ける

### 5. 確認問題 1 が本文の文をほぼそのまま問う

- 重さ：直すとよい
- 観点：clarity（U8）
- 場所：#quiz「狭義単調な列と不等号の向き」
- 問題：前半（狭義単調は部分集合と同じで C(n, k)）は #bijection の「狭義単調な列は値の集合で決まる」、後半は #bijection の例そのもので、理解を試す問いになっていない
- 根拠：61・65 行と 204 行
- 直し方：「この場合は？」に変える。例：「$0 \le a_1 \le a_2 \le \dots \le a_k \le n$（下限 0）なら？」「$a_{i+1} \ge a_i + 2$ なら $b_i$ をどう置くか、行き先の上限は？」など、置き方と上限を自分で直す問いにする

### 6. 落とし穴の「N = 1 の木」が文字と内容の両方で浮いている

- 重さ：直すとよい
- 観点：fact（F7）・clarity（U3）
- 場所：#pitfalls「空の対象と境界」（148 行）
- 問題：木の頂点数はページで $n$ と書いているのに、ここだけ $N$。また「N = 1 の木」を確かめる例に挙げながら、どうなるか（Prüfer 列は定義されないが、n^{n−2} は n = 1 で 1 になり偶然合う）を書いていない
- 根拠：126 行（n）と 148 行（N）
- 直し方：「$n = 1$ の木（Prüfer 列は定義されないが、木は 1 つ）」のように文字を $n$ にそろえ、結果を一言添える

### 7. 導入の「$Y$ の行き先」

- 重さ：直すとよい
- 観点：clarity（U9）
- 場所：導入 47 行
- 問題：Y は行き先そのものなので「Y の行き先」は意味が通りにくい
- 直し方：「$Y$ は、ほとんどが二項係数・重複組合せ・格子路・積の形で数えられる集合になる」などにする

### 8. 次数を決めた木の数の条件

- 重さ：直すとよい
- 観点：fact（F2）
- 場所：#classic-bijections の Prüfer 列の段落（126 行）
- 問題：$\frac{(n-2)!}{\prod_v (d_v - 1)!}$ は $d_v \ge 1$ かつ $\sum_v d_v = 2n - 2$ のときの値で、満たさなければ 0。条件が書かれていない（式は条件の下で全探索と一致した）
- 直し方：「（$d_v \ge 1$、$\sum d_v = 2n - 2$ のとき。そうでなければ 0）」を添える

### 9. verify.cpp の取り込み範囲が長い

- 重さ：直すとよい
- 観点：code（C4）
- 場所：snippets/counting-bijection/verify.cpp の core（約 40 行）
- 問題：in_X・in_Y の定義まで取り込んでいて、要点（f・g と check_bijection の 4 つの assert）が埋もれる
- 直し方：範囲を f・g と check_bijection に絞るか、in_X・in_Y を別の範囲に分ける（in_X・in_Y の中身は本文の条件の写しなので、コメント 1 行で足りる）

## 問題なしと確かめた点（抜粋）

- 計算量：要点・complexity・ABC110 D の詳細（O(√M) と O(N)）がそろう
- ARC110 D の方針：S + N ≤ 2000·2000 + 2000 ≈ 4×10^6、M + N ≤ 10^9 + 2000 < 10^9+7 なので分子に法の倍数が出ず、直接掛けて割る方法でよい。S > M なら 0
- ABC110 D の詳細：異なる素因数は 9 個以下（2·3·…·23 = 223092870、×29 で 10^9 超）、指数は 29 以下、M = 1 の扱い、残った素数の扱いがコードと一致
- lcm の (e+1)^2 − e^2 = 2e + 1、45 度回転、Vandermonde の読み、括弧列の対応、非単射の例（4 と 3）、確認問題 2・3 の答え
- 問題の囲み・役割・要約は台帳どおり、atcoder.jp の URL は囲みの中だけ、参考に atcoder.jp・codeforces.com なし
- 図 monotone.svg：値・添字が本文と一致（b₁ = a₁、b₂ = a₂ + 1、6 対 6、C(4, 2) = 6）、背景白・viewBox・テキストのまま、代替テキストで要点が分かる。catalog の visual（static・priority 2）を満たす
- front matter：変えたのは complexity・stage・updated だけ

## 提案への意見（メイン向け）

- 台帳 arc110_d の checked を 2026-10-21 にする提案に同意（記事で問い・制約・答えを確かめた）
- 用語集の単射（injection）・全射（surjection）の提案に同意。足したら #non-injective の最初の「単射」と #bijection の最初の「全射」相当の箇所にリンクを
- render_svg の幅 720 で下が切れる件は、道具の出力の高さが固定か幅に比例していないためと見られる（ページの問題ではない）

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 8）。
