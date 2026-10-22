# lagrange-interpolation の検証（b4）

対象：docs/math/lagrange-interpolation.md、snippets/lagrange-interpolation/eval.{cpp,yaml}。図はなし（catalog の visual: null）。
観点：fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page lagrange-interpolation`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/lagrange-interpolation`：8 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 手で `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイル：警告なし。main の assert（k ≤ 6・n ≤ 30 で愚直な和と比較）も通過。cases の外の入力も試した：`0 10^18` → 716070898（= 10^18 mod p）、`5 -3` → 33（S_5(−1) = 0、S_5(−2) = 1、S_5(−3) = 1 − (−2)^5 = 33 と一致。負の t も ACL の modint の符号付きの構築で正しく扱える）
- cases の期待値を Python で独立に計算した：Σ_{i≤100} i^10 mod p = 543563053、(n(n+1)/2)^2 mod p = 938655393・n(n+1)(2n+1)/6 mod p = 254544589（n = 10^18）、n = p で k = 1 は 0、n = p + 1 で k = 2 は 1。すべて一致（期待値をプログラムの出力から写しただけではない）
- `npx textlint`：エラー 0・警告 6（36 行目は要点の箇条書きの見出し、ほかは数式を含む文の長さ・読点の数。執筆者の報告どおり誤検出で、残してよい）
- 本文の例 f(x) = x²、t = 3：i = 1 の項 −1·1·(3·1)/(1!·1!) = −3、i = 2 の項 4·(3·2)/(2!·0!) = 12、合計 9。正しい
- 分母 ∏_{j≠i}(i − j) = (−1)^{d−i} i! (d−i)!、等差数列 x_i = a + ih で分母が h^d 倍、Faulhaber の次数 k + 1（k + 2 点）、C(N + c, r) が r 次、和で次数が 1 上がる、t mod p が標本点と重なると全体の積を (t − i) で割る方法が 0 除算になる（t = p、p + 1）、d < p が要る、はどれも正しい
- 組立除法の添字を Python（一時置き場の syn.py。d = 4、x = 0..4、x_i = 2）で確かめた：M(x) は d + 1 次なので、商の最高次は q_d = m_{d+1} で、q_{k−1} = m_k + x_i q_k とすると ∏_{j≠i}(x − x_j) と一致し余り 0。本文の「q_{d−1} = m_d」は 1 つずれている（指摘 1）
- Library Checker（library-checker-problems の task.md・info.toml を GitHub から取得）：Shift of Sampling Points は polynomial/ にあり N, M ≤ 524288 = 2^19。Polynomial Interpolation は polynomial/ にあり N ≤ 2^17、x_i は相異なる任意の点。Sum of Exponential times Polynomial は other/ にあり Σ_{i=0}^{n−1} r^i i^d、0^0 = 1、d ≤ 10^7。本文・参考の「polynomial・other のディレクトリ」と一致
- 参考の URL（どれも開けた）：
    - ikatakos「ラグランジュ補間」：ヴァンデルモンドの行列式・O(D²) の係数の復元・等差数列のサンプル点で O(D)。本文の説明と合う
    - ei1333「ラグランジュ補間」：累積積と階乗テーブルで O(d)、等差数列の場合。ei1333.hateblo.jp は `tools/check_noai.py` で noai・noimageai の指定なしを確認（meta robots="max-image-preview:large"）。付録 B への追加の提案は妥当
    - Nyaan「$\sum_{i}a^i f(i)$」：O(N + log mod)、母関数 F(x)/(1−x)^{k+1} を使い、最後にラグランジュ補間。a = 0, 1 は場合分け。本文の説明と合う
    - kmjp（ABC137 F）：(x−0)…(x−(p−1)) を作り (x − i) で割る方針で O(P²)。コードの配列の大きさが 3030 で、p は 3000 程度まで（O(p²) が間に合う大きさ、という本文の書き方で足りる。**執筆者の未解決の点 1 は今の書き方でよい**）
    - rsk0315（ABC137 F）：フェルマーの小定理で l_j(x) = 1 − (x − j)^{p−1}、二項係数で展開。本文の解法の詳細と一致
    - ikatakos（ABC208 の記録）：解法の節だけを読んだ。Σ i^K · C(n−i+M−1, M−1) が n の多項式になる話で、本文の「累積和を何回も取った値を問う型」と合う
    - 言い回し・例の写しはない（F8 問題なし。本文の例 x² は資料にない）
- 台帳：abc137_f は ap.py で実在（diff 2402）、summary は kmjp・rsk0315 の問題の要約と合う。`checked` に 2026-10-22 を入れる提案に賛成。補充の候補 abc208_f（diff 2772）・arc033_4（diff 2470、参考値）も ap.py で実在を確認した
- リンク先の anchor（mod-inverse#inverse-table、binomial-precompute#fact-ifact、gaussian-elimination#mod-p）はすべて存在し、内容（階乗の逆元を後ろから作る話・mod p の掃き出し）も合う
- 執筆者の未解決の点 2（線形篩）：素数 ≤ k + 1 は約 k / ln k 個で、それぞれ O(log k) の累乗なので合計 O(k)。「O(k) に近づく」よりはっきり O(k) と書ける（指摘 2）
- 執筆者の未解決の点 3（verify の sum_of_exponential_times_polynomial）：r = 1 のときはこのページの補間そのもので確かめられ、r ≠ 1 も Nyaan の方法の最後の段は O(d) の補間なので、verify に載せたままでよいと考える（メインの判断）
- 図：ページに図はなく、catalog の visual も null。figure.md の観点で指摘なし

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | F2・F3 | #coefficients の「組立除法は、商の係数を次数の高い方から $q_{d-1} = m_d$、$q_{k-1} = m_k + x_i\, q_k$ と求める」 | 添字が 1 つずれている。$M(x) = \prod_{j=0}^{d}(x - x_j)$ は $d + 1$ 次（係数 $m_0, \dots, m_{d+1}$）で、商 $\prod_{j \ne i}(x - x_j)$ は $d$ 次。書かれたとおりに実装すると最高次の係数 $m_{d+1}$ を使わず、商の次数も $d - 1$ になって誤る | 一時置き場の syn.py：$q_d = m_{d+1}$ から始めると直接の積と一致し余り 0。一般に $n$ 次式を $(x - a)$ で割る商の最高次は $q_{n-1} = m_n$ で、ここでは $n = d + 1$ | 「$q_d = m_{d+1}$、$k = d, d-1, \dots, 1$ について $q_{k-1} = m_k + x_i\, q_k$」に直す。余りは $m_0 + x_i q_0 = M(x_i) = 0$ と添えると検算の文につながる |
| 2 | 直すとよい | F1 | #applications の「素数のときだけ累乗を計算して線形篩で埋めると $O(k)$ に近づく」 | 「近づく」がぼかしで、読者は $O(k)$ なのかそうでないのか判断できない。実際は $O(k)$ である | $k$ 以下の素数は約 $k / \ln k$ 個で、各 $O(\log k)$ の累乗の合計が $O(k)$。合成数は掛け算 1 回 | 「素数（約 $k / \ln k$ 個）でだけ $O(\log k)$ の累乗を計算し、合成数は線形篩で $p^k \cdot (i/p)^k$ と 1 回の掛け算で埋めると $O(k)$ になる」と書く |
| 3 | 直すとよい | U3 | #coefficients のフェルマーの段落「$(x - i)^{p-1}$ を二項定理で展開して $y_i$ 倍して足せば」 | 直前で $1 - (x - i)^{p-1}$ を作ったのに、足すものが $(x - i)^{p-1}$ の $y_i$ 倍と読める。符号と定数項の 1 が抜けたように見える | 例題の解法の詳細は「$1 - (x - i)^{p-1}$ を足す」と正しく書いている | 「$y_i \bigl(1 - (x - i)^{p-1}\bigr)$ を、$(x - i)^{p-1}$ を二項定理で展開して足せば」とする |
| 4 | 直すとよい | U3 | #uniqueness の「値がそろうことは、次の式（ラグランジュの補間公式）で具体的に作れることから分かる」 | 直前が一意性（2 つの多項式が一致する）の話なので、「値がそろうこと」が何を指すか（指定した値をとる多項式が存在すること）がつかみにくい | 本文の段落の流れ | 「$d + 1$ 点で指定した値をとる $d$ 次以下の多項式があることは、次の式で具体的に作れることから分かる」とする |
| 5 | 直すとよい | U9 | #applications の「次数の見積もりが自信なければ」 | 助詞が不自然 | ― | 「次数の見積もりに自信がなければ」とする |
| 6 | 直すべき | C3・F3 | eval.cpp の core（本文に取り込まれる）の注釈「pre[i] = (t-0)(t-1)...(t-(i-1))、suf[i] = (t-(i+1))...(t-d)」 | `suf` の注釈が誤り。コードは `suf[i] = suf[i + 1] * (tm - i)` なので suf[i] = (t−i)(t−(i+1))…(t−d) で、(t − i) を含む。使う側は `suf[i + 1]` なのでコードは正しいが、本文に見える注釈が実際と違い、本文の $R_i = \prod_{j > i}(t - j)$ との対応（$R_i$ = `suf[i + 1]`）も読み取れない | eval.cpp の 17〜20 行目。suf[d] = (t − d)、suf[d + 1] = 1 から帰納的に確かめた | 注釈を「pre[i] = (t-0)…(t-(i-1)) = L_i、suf[i] = (t-i)…(t-d)（R_i = suf[i+1]）」に直す。cases は変わらない |

（メインへの申し送り：用語集の提案「標本点」「組立除法」と、付録 A・B への追加の提案は妥当。abc137_f の `checked` に 2026-10-22 を入れることを提案する。補充の候補 abc208_f を 2 つ目の例題に足す案は、発展の例題 0〜2 の範囲に収まる。）

## 総合の判定

小さな直しで可。直すべき指摘は 2 件（組立除法の添字のずれ、コード片の `suf` の注釈の誤り）で、どちらも 1 行の直しで済む。ほかは直すとよい 4 件。
