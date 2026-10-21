# sparse-table の検証（b2）

- 対象：docs/ds/sparse-table.md、snippets/sparse-table/sparse-table.{cpp,yaml}・disjoint.{cpp,yaml}、docs/img/sparse-table/cover.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page sparse-table`：エラー 0・警告 0
- `python3 tools/fix_problems.py --check --page sparse-table`：直すべき行 0
- `python3 tools/check_snippets.py snippets/sparse-table`：2 本・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `npx textlint docs/ds/sparse-table.md`：エラー 0・警告 31（文の長さ・読点の数・数式の角括弧・助詞「は」の重なり。誤検出か数式を含む文で、残してよい）
- サニタイザ：両方を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、N ≤ 70・値 1〜60 の乱数 400 組（各 60 クエリ）をコード片の main の素朴な計算（assert）と比べた。食い違い 0、サニタイザの報告 0。disjoint は N = 129（2 のべきでない・最後の塊が半端）で、空を含むすべての l ≤ r（8515 個）を通した
- yaml の期待出力を手で確かめた：[1,7) の min 3・gcd(3,7,9,6,4,8) = 1、和 37・全体 43・[3,5) 15 など。すべて正しい
- 本文の数値
  - 図の表：k = 1 の段 (3,3,7,6,4,4,1)、k = 2 の段 (3,3,4,4,1)、k = 3 の段 (1)。st[2][1] = 3、st[2][3] = 4、答え 3。正しい
  - メモリ：N = 5×10^5 で段は ⌊log₂ N⌋ + 1 = 19、個数は Σ(N − 2^k + 1) = 19·500001 − (2^19 − 1) = 8,975,732 ≈ 9×10^6、×8 バイト ≈ 71.8 MB。正しい
  - N = 10^6 で 20 段、確認問題の a = (1,2,3) の和 8・min 1。正しい
  - DST の例（l = 1, r = 6 → h = 3、t[3][1] = a1a2a3・t[3][6] = a4a5a6。l = 4, r = 5 → h = 1、塊 [4,6)）と確認問題の [2,5]（h = 3、a2a3 と a4a5）。正しい
  - abc282_f：Σ_{k=0}^{11}(4000 − 2^k + 1) = 48012 − 4095 = 43917 ≤ 50000、2^11 = 2048 ≤ 4000 < 2^12。正しい
- 証明：「2 区間で過不足なく覆える」（l + 2^k > r − 2^k ⇔ 2^{k+1} > L）と「重なっても変わらない」を確かめた。重なり B は長さ 2^{k+1} − L ≥ 1 で空にならず、(A·B)·(B·C) = A·(B·B)·C は結合法則だけで組み替えられ、左右の順を保つので交換法則は要らない。**執筆者の未解決 3 の主張は正しい**（L = 2^k のとき A・C が空になる点だけ指摘 6）
- DST の「l ⊕ r の最上位 bit が h − 1（0 始まり）なら、l と r は長さ 2^h の同じ塊の左右の半分に入る」：bit h 以上が等しいので同じ塊、bit h − 1 が l で 0・r で 1 なので左右に分かれる。正しい。コードも l, r < N ≤ 2^H から h ≤ H を満たす
- リンクの anchor：doubling#aggregates・lca#comparison・suffix-array#lcp-rmq・interactive#format・glossary#half-open-interval・glossary#associativity はある
- 問題：`python3 tools/ap.py show abc282_f abc254_f` で abc282_f（Union of Two Sets、diff 1734）・abc254_f（Rectangle GCD、diff 1764）を確かめた。囲みの label・diff・要約は台帳と一致し、要約に手法名はない
- 参考の URL（すべて付録 B のドメイン）
  - drken abc282_f：h1「AtCoder ABC 282 F - Union of Two Sets (2D, 青色, 600 点)」と一致。制約 1 ≤ N ≤ 4000、出力する区間 50000 個以下、**Q ≤ 10^5**。記事の本解は長さ 2^k − 1 の区間を用意する形で、長さ 2^k の Sparse Table 型でもよいと述べる（指摘 5）
  - Kazun abc254_f：h1 一致。隣接差の gcd に直し、セグメント木で区間 gcd、更新がないので Disjoint Sparse Table も使えると述べる。本文の注記と一致
  - cp-algorithms「Sparse Table」：冪等な演算に限り O(1)（"only supports queries of idempotent functions"）、`st[K + 1][MAXN]` で MAXN を 2 番目にして連続アクセス、Disjoint Sparse Table の存在。注記の 3 点とも一致。本文の文章・図は cp-algorithms の言い回し・例と別のもの（例の列 5 3 7 9 6 4 8 1 は独自）
  - cppreference bit_width：`<bit>`・C++20。手引き §14-24 の `/cpp/` の形に合う
  - Library Checker staticrmq：WebFetch では本文が取れなかった（JS で描く頁）。題名 Static RMQ は front matter の verify と合う
- 図：`python3 tools/render_svg.py sparse-table --out <作業場所>/png` で 360px・720px の PNG にして目で見た。白い背景・viewBox・テキストのまま。2 つの区間は実線と破線・色の両方で区別し、重なりはハッチ。文字の重なり・はみ出しなし。360px で表の数字は読めるが、「重なり [3, 5)」の注記と最下行の灰色の説明はやや小さい（許容）。値・添字は本文と代替テキストに一致
  - 備考（ページの問題ではない）：720px の PNG は高さが足りず、表の k = 2 の段の途中で切れる（kth-value の検証と同じ道具の側の問題）
- 執筆者の未解決の点
  1. 練習の節がない → 台帳に練習が付けば作る、でよい。abc254_f を practice に足す提案は妥当（gcd-properties では example、ここでは practice なので重複の規則に触れない）
  2. abc282_f のクエリ数 → drken の記事で Q ≤ 10^5 と確かめた。本文に足すなら指摘 5 のとおり
  3. 交換法則が要らないこと → 正しい（上記）

## 指摘

### 1. 直すべき｜事実（F2）｜what-it-does の「区間の gcd」の箇条書き（48 行）

- 問題：「2 次元の格子や等差数列の gcd は、隣り合う項の差の gcd に直すと 1 次元の区間 gcd になる」は型を言い誤っている。等差数列 a, a+d, …, a+(n−1)d の gcd は gcd(a, d) で、区間 gcd のデータ構造は要らない。「2 次元の格子」も何の gcd か分からない。差の gcd に直して効くのは、「列の各項に同じ値を足したもの」（A_i + B_j の行列の長方形はその 2 方向版）の gcd である
- 根拠：gcd(a, a+d, a+2d, …) = gcd(a, d)。Kazun の abc254_f の記事：gcd(x₁,…,x_k) = gcd(x₁, x₂−x₁, …, x_k−x_{k−1}) を使い、長方形 [h₁,h₂]×[w₁,w₂] の gcd を X_{h₁,w₁} と C_i = A_{i+1}−A_i（h₁ ≤ i < h₂）・D_j = B_{j+1}−B_j の区間 gcd との gcd にする
- 直し方：例「**区間の gcd**：gcd(x₁, …, x_k) = gcd(x₁, x₂ − x₁, …, x_k − x_{k−1}) を使うと、各項に同じ値を足した列の gcd や、(i, j) 成分が A_i + B_j の行列の長方形の gcd は、隣り合う項の差の区間 gcd に直る（[gcd の性質](../math/gcd-properties.md)）。列が変わらなければ Sparse Table で引ける」

### 2. 直すとよい｜コード（C3）｜snippets/sparse-table/disjoint.cpp 9 行のコメント

- 問題：`t[h][i]：段 h の塊の中点から i までの累積` は右半分の説明だけで、左半分（i から中点の手前まで）が抜けている。本文の「Disjoint Sparse Table の表」の 2 つの場合と合わない
- 直し方：`// t[h][i]：段 h の塊で、左半分の i は [i, 中点) の積、右半分の i は [中点, i] の積`

### 3. 直すとよい｜事実・分かりやすさ（F2・U3）｜disjoint-sparse-table の「結合法則を満たす演算なら何でも載せられ」とコード片の `e`

- 問題：本文は単位元なしで載ると書くが、コード片はテンプレート引数に `e` を取るので、読者は単位元が要ると思う。コードで `e()` を使うのは空の区間の返り値と表の初期値だけである
- 直し方：コード片の前の文に「`e` は空の区間 $l = r$ に返す値にだけ使う。空の区間を聞かないなら単位元は要らない」と 1 文足す

### 4. 直すとよい｜分かりやすさ（U3）｜disjoint-sparse-table の「その bit を下から数えて h − 1 番目」

- 問題：「下から数えて h − 1 番目」が 0 始まりか 1 始まりか分からない。1 始まりと読むと例（l ⊕ r = 111₂、h = 3）とずれる
- 直し方：「最下位を 0 番目として h − 1 番目（すなわち h = `bit_width(l ^ r)`）」とする

### 5. 直すとよい｜事実（F5・F9）｜例題 abc282_f の解法の詳細と、参考の drken の注記

- 問題：(a) 解法の詳細にクエリ数の上限がなく、「1 問 O(1)」がなぜ必要十分かが見えない（執筆者の未解決 2）。(b) 参考の注記「長さ 2 のべきの区間を全始点に用意する方針」は、記事の本解（長さ 2^k − 1 の区間）と違う
- 根拠：drken の記事に Q ≤ 10^5。本解は長さ 1, 3, 7, 15, … の区間を用意し、2 のべきの形でもよいと付記している
- 直し方：(a) 解法の詳細の最初の文を「$N \le 4000$、出力できる区間は $50000$ 個まで、問いは $10^5$ 個までである」とする。(b) 注記を「例題 abc282_f の制約と、長さが倍々に伸びる区間を全始点に用意する方針（記事は長さ 2^k − 1、2 のべきでもよいと述べる）」とする

### 6. 直すとよい｜分かりやすさ（U2）｜idempotent の「重なっても答えが変わらない理由」

- 問題：$L = 2^k$ のときは 2 つの区間が同じになり、$A$・$C$ が空になる。式 $(A \cdot B) \cdot (B \cdot C)$ がこの場合も通ることに触れていない（単位元を使わない表なので、空の部分の扱いが気になる読者がいる）
- 直し方：「$A$ や $C$ が空（$L = 2^k$ で 2 区間が一致する）なら、その部分を式から除けばよく、$B \cdot B = B$ だけで済む」と 1 文足す

### 7. 直すとよい｜事実（F1）｜what-it-does の「二分探索は、セグメント木なら O(log² N)」

- 問題：セグメント木でも木の上を降りる二分探索（ACL の `max_right`・`min_left`）なら $O(\log N)$ になる。「区間の取得を外から二分探索で呼ぶなら」の条件がないと、セグメント木が必ず遅いと読める
- 根拠：ACL v1.6 document_ja/segtree.md の max_right・min_left の計算量は $O(\log n)$
- 直し方：「区間の最小値を外側から二分探索で呼ぶと、セグメント木なら $O(\log^2 N)$（木を降りる `max_right` を使えば $O(\log N)$）、Sparse Table なら $O(\log N)$ になる」

### 8. 直すとよい｜事実（F2）｜使い分けの「窓の幅が一定で、左右の端が単調に動く」

- 問題：スライド最小値（両端キュー）に要るのは左右の端が単調に動くことだけで、幅が一定である必要はない。条件を狭く書いている
- 直し方：「左右の端がどちらも単調に動く（尺取り・幅が一定の窓）」とする

## 台帳への提案（検証役から）

- abc282_f の `checked` に 2026-10-21 を入れる（drken の記事で制約 N ≤ 4000・区間 50000 個まで・Q ≤ 10^5 と方針を確かめた）。執筆者の提案と同じ
- abc254_f の `checked` に 2026-10-21 を入れる（Kazun の記事で隣接差の gcd・セグメント木か Disjoint Sparse Table の方針を確かめた）。pages に `{id: sparse-table, role: practice}` を足す執筆者の提案は妥当
- 用語集「冪等」の提案は妥当。足したら what-it-does の「冪等」をリンクにする

## 総合の判定

小さな直しで可。直すべき 1 件（区間の gcd の型の言い誤り）、直すとよい 7 件。コード片は乱数・全区間・サニタイザで誤りなし、図・本文の数値・証明・参考の注記はおおむね正しい。
