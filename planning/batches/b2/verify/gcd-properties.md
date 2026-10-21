# gcd-properties の検証（b2）

- 対象：docs/math/gcd-properties.md、snippets/gcd-properties/{rect-gcd,subarray-gcd}.{cpp,yaml}、docs/img/gcd-properties/staircase.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15。図は `python3 tools/render_svg.py`（chrome-headless-shell 146、幅 360px・720px）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page gcd-properties`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/gcd-properties`：rect-gcd 4 case・subarray-gcd 5 case すべて一致
- サニタイザ（`-fsanitize=address,undefined`）：両コード片を cases と、乱数の大きめの入力（rect-gcd は N = 200・Q = 300、値は 10^9 程度。subarray-gcd は N = 500）で動かし、異常なし・コード内の素朴な方法との assert も通った。N = 0（subarray）・1 行 1 列（rect）の境界も通る
- 差の gcd の式、矩形の式（ΔA の添字 $h_1 \le i < h_2 - 1$）、行が 1 つのとき空区間で 0 が返ること：コードの `query(l >= r) → 0` と一致
- 組の列が gcd の大きい順に並び、同じ値が隣り合うこと：新しい組の値 $x$ と、それ以外の $\gcd(g, x)$ が約数の鎖になるので正しい
- mod N の歩み：Python で $N < 25$、歩幅 2 つまでの全組を union-find で数え、連結成分の数が $\gcd(N, A, B)$、前にだけ進んで通る点の数が $N / \gcd(A, N)$ であることを確かめた
- 格子点 $\gcd(|dx|, |dy|) + 1$：乱数 2000 組で全探索と一致。$(0,0)$–$(6,4)$ の 3 点、確認問題の $(1,2)$–$(10,-4)$ の 4 点も正しい
- フロベニウス：$a, b < 15$ の互いに素な全組で、最大 $ab - a - b$、個数 $(a-1)(b-1)/2$、判定「$n \ge b y_\rho$」が全探索と一致。$a = 3, b = 5$ の $1, 2, 4, 7$、確認問題の 6 と 9（3 の倍数の最大 3）も正しい
- 余りごとの個数 $\lfloor b y_\rho / a \rfloor$（執筆者の未解決の点 3）：$n = b y_\rho - ka$（$k \ge 1$、$n > 0$）の個数で、$b y_\rho$ は $y_\rho \ge 1$ なら $a$ で割り切れないので $\lceil b y_\rho / a \rceil - 1 = \lfloor b y_\rho / a \rfloor$。正しい。和の証明の省略は辞書としてはこのままでよい
- セグメント木の取得 $O(\log N + \log A)$（未解決の点 2）：互除法の手数は $(g, x)$ と $(g/g', x/g')$ で同じなので $O(1 + \log(g / g'))$ で、左から合わせると $\log$ の和がつぶれる。ACL の prod のように左右から別々に合わせても、左右それぞれでつぶれ、最後の 1 回を足すだけなので同じ。Kazun の記事もセグメント木のクエリを $O(\log N + \log \max A)$ としている。主張は互除法については正しい（std::gcd については指摘 3）
- 右端固定の列挙 $O(N \log^2 A)$（未解決の点 1）：上からの押さえとして正しい。細かい評価は書かなくてよい
- 確認問題：$x = 0$ で 2・$x = 2$ で 6、$\gcd(30,12,20) = 2$ で 15 点・12 だけなら 6 で 5 点、$2^{30}$ から 31 種類：すべて正しい
- 図の値：48, 72, 36, 60, 18, 27, 45, 10 の累積 gcd は 48・24・12・12・6・3・3・1 で、種類は 6。代替テキスト・図の下の文・コード片の case（`6 510` の入力）と一致
- 例題 ABC254 F：台帳（確認済み・diff 1764）と label・URL が一致。Kazun の記事で制約 $N, Q \le 2 \times 10^5$・$A_i, B_j \le 10^9$、隣接差への帰着、セグメント木・Sparse Table での計算量を確かめた。成分が $2 \times 10^9$ で `long long` が要ることも正しい
- 練習 ABC210 E：drken の記事で $N \le 10^9$・$M \le 10^5$、費用の小さい順・成分の数 $n \to \gcd(n, A_i)$・辺 $n - g$ 本を確かめた。Python で小さい $N$ のクラスカル法の全探索と 500 例一致
- 練習 AGC026 B：drken の記事で場合分け（$A < B$、$D < B$、$C \ge B - 1$）と $B - g + (A \bmod g) > C$ の判定を確かめた。Python で $A < 25$・$B, C, D < 15$ の全組をシミュレーションと比べ一致
- 参考の 4 つの URL：check_noai で noai の指定なし。題名・内容は書かれたとおり
- 本文のリンクの先（gcd-lcm#euclid・#prefix-suffix-gcd・#reduce-fraction・#pitfalls、proof-patterns#gcd-invariant・#rearrangement、sparse-table#idempotent・#pitfalls、ext-gcd#applications、glossary#coprime）はどれも節があり、内容が合う
- 図：白背景・viewBox あり・font-family="sans-serif"・相対パス。720px で文字の重なり・はみ出しなし

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F3 | range-gcd の節「左端を固定すると値は O(log A) 種類」の最後の文 | 「値の種類は $\lfloor \log_2 A \rfloor + 1$ 以下である。$A = 10^9$ なら 31 種類以下」は、直前の式に $A = 10^9$ を入れた値（$\lfloor \log_2 10^9 \rfloor + 1 = 29 + 1 = 30$）と合わない。31 は上からの押さえとしては誤りではないが、読者が式で計算すると食い違う | $2^{29} = 536870912 \le 10^9 < 2^{30}$。Python で確かめた。確認問題の $2^{30}$（$> 10^9$）からの 31 種類とも混ざりやすい | 「$A = 10^9$ なら 30 種類以下（$2^{29} \le 10^9 < 2^{30}$）になる」とする。確認問題はこのままでよい（$2^{30}$ は $10^9$ を超えることを答えに 1 文足すとなおよい） |
| 2 | 直すとよい | clarity U4 / fact F2 | range-gcd の節「gcd が 1 になる最短の区間」 | 「尺取り法か、Sparse Table の上の二分探索で求まる」とあるが、gcd は左端から取り除けない（逆の操作がない）ので、尺取り法のページの「取り除く処理」をそのまま書けない。読者は窓の gcd をどう保つかで止まる。尺取り法のページにも gcd の窓の扱いはない | docs/basics/two-pointers.md の #implementation・#fixed-window は取り除ける量か最大・最小だけ | 「尺取り法（窓の gcd は取り除けないので、Sparse Table で $O(1)$ 回の gcd として求める）」と添える |
| 3 | 直すとよい | fact F1 | range-gcd の注記「セグメント木の取得は実際には O(log N + log A)」 | 根拠の「互除法の手数が $O(1 + \log(g/g'))$」は互除法には正しいが、コード片が使う `std::gcd` は libstdc++（g++-13・15）では二進 gcd（`__countr_zero` と引き算）で、手数は $\log(g/g')$ ではなく値のビット数で決まるため、和がつぶれない。読者が `std::gcd` で同じ評価を当てはめると誤る | /usr/include/c++/15/numeric の `__detail::__gcd`（二進 gcd） | 注記の末尾に「`std::gcd`（libstdc++ は二進 gcd）ではこの和の評価は当てはまらないが、1 回が十分速いので見積もりは $O(\log N \log A)$ で足りる」と 1 文足す |
| 4 | 直すとよい | fact F6 | frobenius の節の応用の型「3 種類以上の数」 | リンク先の dijkstra のページに、余りごとの最小値を求める（同余最短路の）節がない（執筆者の未解決の点 4）。読者はページ全体を探して見つけられない。同余最短路のページ graph/modular-shortest-path（stub、aliases に「同余最短路」、節 #congruence）がある | docs/graph/dijkstra.md の節の一覧、docs/graph/modular-shortest-path.md の front matter | リンクを `[同余最短路](../graph/modular-shortest-path.md)` に替え、ダイクストラ法へのリンクは残してもよい（stub の節へのリンクは check_pages が禁じるので、ページへのリンクにする。#congruence はページが書かれた後にメインが張り替える） |
| 5 | 直すとよい | figure G5 | staircase.svg の見出しと各列の下のラベル | 本文はこの節で列を小文字 $a_0, \dots$、値の上限を $A$ と書くが、図は「gcd(A_0, …, A_r)」「A = 48」と書く。「A = 72」は本文の $A$（値の最大）と同じ文字で、要素の値と読み違えやすい。`A_0` の下付きもテキストの `_` のまま | 本文 51 行目「列を $a_0, \dots, a_{N-1}$」、42 行目「$A$ は値の最大」 | 見出しを「gcd(a₀, …, aᵣ)」、ラベルを「a₀ = 48」「a₁ = 72」…（または「a = 48」）にする |
| 6 | 直すとよい | figure G3 | staircase.svg の 360px 表示 | viewBox 600 幅のため、360px では凡例（12px）とラベル（13px）が 7〜8px 相当になり、凡例の「太枠：値が変わった…」がほぼ読めない | render_svg の 360px の PNG を目視 | 凡例を 2 行に分けて font-size を 14 に上げるか、凡例を図の下の文に移す。棒の数値（太字）は 360px でも読めるので、要点は崩れていない |
| 7 | 直すとよい | fact F7 | lattice-on-segment の節の応用の型「多角形の格子点」の凸包へのリンク | ページへのリンクだけで、convex-hull に格子点とピックの定理の節 #lattice-points がある（front matter の related も `convex-hull#lattice-points`） | docs/geometry/convex-hull.md の sections | `../geometry/convex-hull.md#lattice-points` にする（相手が stub なら今のままでよい。check_pages に任せる） |
| 8 | 直すとよい | clarity U3 | step-mod の節「N = 12、A = 8 なら…（並べ替え論法の例）」 | 並べ替え論法は $\gcd(a, m) = 1$ の場合の主張で、$\gcd(12, 8) = 4$ のこの例は「互いに素でないときに $N / g$ 点に限られる」側の例。括弧の位置だと、並べ替え論法がこの例に当てはまるように読める | proof-patterns#rearrangement の本文（互いに素の場合）と、そこの確認問題（同じ 12・8 の例） | 「（[並べ替え論法](…)の確認問題と同じ例）」とするか、括弧を周期の段落の「互いに素なので」の後へ移す |

## 執筆者の未解決の点について

- 1（$O(N \log^2 A)$ のまま）：上からの押さえとして正しい。このままでよい
- 2（セグメント木の $O(\log N + \log A)$）：互除法については正しい。Kazun の記事とも合う。std::gcd との差は指摘 3
- 3（$(a-1)(b-1)/2$ の和の証明の省略）：余りごとの個数の式は正しく、和も全探索で一致。このままでよい
- 4（dijkstra のリンク）：指摘 4

## 台帳への提案

- abc254_f・abc210_e・agc026_b：evidence の記事で制約と方針を確かめた（2026-10-21）。執筆者の提案のとおりでよい

## 総合の判定

小さな直しで可。直すべき 1 件（数値の食い違い）・直すとよい 7 件。定理・数値・コードに誤りは見つからなかった。
