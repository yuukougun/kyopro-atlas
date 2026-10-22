# stirling-first の検証（b4）

対象：docs/comb/stirling-first.md、snippets/stirling-first/{rising,buildings}.{cpp,yaml}。図はなし（catalog の visual: null）。
観点：fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page stirling-first`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/stirling-first`：2 本とも 4 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 手で `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library`：警告なし。中の全列挙の assert（n ≤ 7、表と分割統治の n ≤ 100）も通過。N = 200000 で rising・buildings とも 0.6 秒
- `npx textlint`：エラー 0・警告 11（執筆者の報告どおり。max-comma・sentence-length・no-doubled-joshi で、数式を含む文。残してよい）
- 独自の Python（一時置き場の chk.py）で確かめた：
    - c(4,·) = (0,6,11,6,1)、c(5,·) = (0,24,50,35,10,1)
    - n = 3 の巡回の表と、左から見える位置の分け方（312・321／132・213・231／123）を手で確認
    - 例題の閉じた形 Σ_j c(N−1, j)·C(j, (j+|K|)/2)（j ≡ K mod 2）が、N ≤ 8 の全 K で全列挙（左から見える数 − 右から見える数）と一致。**執筆者の未解決の点 1 は正しい**
    - c(n,k) = S(n,k) となる (n,k) は、k ≥ n−1・k = 0（と n = k = 0）だけ（n ≤ 8）
- 恒等式：f_{2m}(x) = f_m(x)·f_m(x+m)、上の bit から読んで奇数なら (x+2m) を掛ける手順、EGF Σ c(n,K) xⁿ/n! = (−log(1−x))^K / K!、x^n = Σ S(n,k) x(x−1)…(x−k+1)、符号付きは下降階乗の係数。どれも正しい。Nyaan's Library の `Stirling1st`（TaylorShift による倍化、奇数で (x + n−1) を掛ける）と `Stirling1stRow`（Σ x^i/i の K 乗 × finv(K) × fac(n)）で実装が本文どおりであることを確認。**未解決の点 2 は正しい**
- Library Checker（GitHub の task.md と info.toml）：3 問とも符号付きの定義（下降階乗の係数）。行は N ≤ 500000、Fixed K は K ≤ n ≤ N（N ≤ 500000）、Small p は p ≤ 5000・n ≤ 10^18。本文の記述と一致
- ACL v1.6 document_ja/convolution.md：static_modint の版の宣言、n = |a|+|b| で O(n log n + log mod)、法の要件。「ACL では」の囲みと一致
- 参考：kmjp の abc385_g（大きい順の挿入、先頭・末尾・その他の 3 通り、多項式の積）、kmjp の abc247_h（m ≤ K かつ偶奇一致の和、異なる色の swap は無視、色ごとの第 1 種スターリング数の行を NTT で畳み込む）、ikatakos の abc385 G の解法の節（差だけを状態にまとめ (x^{-1}+i+x) の積をマージテクで O(N log² N)）、ikatakos の abc247 Ex の解法の節（偶奇、同色だけの swap、表による 2 色の畳み込み）。参考の一覧の説明と本文の方針はどれも資料と合う。言い回し・例の写しはない（F8 問題なし）
- 練習の方針（ABC247 Ex）：最小回数 m ≤ K かつ偶奇一致でちょうど K 回が作れる、色ごとの Σ c(m_i,k) x^{m_i−k} の積、は kmjp・ikatakos と一致
- 台帳：abc385_g は stirling-first が example、generating-function-counting が practice で、例題の重なりはない。abc247_h の summary は台帳でまだ「（執筆時に確かめる）」なので、報告の提案どおりの反映が要る（メインの作業）
- リンク先の anchor（permutation-cycles#decompose・#min-swaps、glossary#fixed-point、insertion-dp#insert-by-value、convolution-ntt#acl、bell-number#recurrence）はすべて存在する
- 図：ページに図はなく、catalog の visual も null。figure.md の観点で指摘なし

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | F1・F10 | 要点の「計算量」 | front matter の complexity にある「列 c(n,K)（n ≤ N）は FPS の累乗で O(N log N)」が要点の計算量にない。summary は「FPS で一度に求める」と言うので、要点だけを読むと FPS の使いどころが見えない | front matter の complexity と要点の比較 | 要点の計算量に「列 c(n, K)（K を固定、n ≤ N）は FPS の累乗で O(N log N)」を 1 文足す |
| 2 | 直すとよい | F2・U3 | #vs-second-kind の第 1 段落「組の大きさがどれも 2 以下なら一致する」 | 数 c(n,k) と S(n,k) の一致の条件として読むと、何の組か（どの分け方も、なのか）が曖昧。実際に一致するのは k ≥ n−1（と k = 0）のときだけ | chk.py で n ≤ 8 の全 (n,k) を比べた結果：一致は k ∈ {0, n−1, n} のみ | 「大きさ 2 以下の組は輪の並べ方が 1 通りなので、どの分け方でも組がそうなる k ≥ n − 1 のとき c(n, k) = S(n, k) になる」のように条件を (n, k) で書く |
| 3 | 直すとよい | U3 | #records の「応用の型」の $\prod_i (x + y + i - 1)$ | i の範囲が書かれておらず、最大の値の分（左右どちらからも見えるので xy）が積に入るのかが分からない。直前の 1 変数の議論は「1 回目は x、以降は (x+i)」で、添字の付け方が違って見える | 例題の方針は $\prod_{i=1}^{N-1}$ と書いていて、こちらは範囲がある | 「最大の値の $xy$ と、$i = 1, \dots, n-1$ の $(x + y + i - 1)$ の積（$i$ はすでに並べた個数。隙間 $i+1$ か所のうち先頭が $x$、末尾が $y$、残り $i-1$ か所）」と書く |
| 4 | 直すとよい | U9 | 練習の方針（ABC247 Ex） | 同じ折りたたみの中で、$m$ を「最小の swap 回数」に、$m_1, m_2, \dots$ を「色ごとの人数」に使っていて、記号がぶつかる | 本文の該当文 | 色ごとの人数を $a_1, a_2, \dots$ など別の文字にする |
| 5 | 直すとよい | U3 | #what の「$k$ 個の輪に人を座らせる方法（輪の回転は同一視し、輪は区別しない）」 | 裏返し（鏡像）を同一視するかが書かれていない。読者が数珠順列（裏返しも同一視）と取り違えると、長さ 3 以上の巡回で数が半分になる | 巡回 (1 2 3) と (1 3 2) は別の置換 | 「回転は同一視し、裏返しは区別する」と足す |
| 6 | 直すとよい | 構成（手引き §15-5） | #fps の末尾の Library Checker 3 問 | 手引き §15-5 は Library Checker の練習を `## 練習問題 {#practice}` の中の小見出し「Library Checker」に置く形を示している。今は fps 節の中の箇条書き。§15-5 は「置いてよい」なので違反ではないが、ほかのページとそろわない。執筆者も判断をメインに任せている | style-guide §15-5 | メインの判断で、練習問題の節に小見出し「Library Checker」を立てて移し、fps 節には「確かめ方は練習問題の節」と 1 行残す。いまの位置のままでもよい |

（メインへの申し送り：`## 学ぶための資料 {#resources}` は sections にない定型でない節で、check_pages は通る。手引き §4 の overview の構成に沿った置き場所（例題の前）なので、§13-1 に定型として足すかどうかは執筆者の提案どおりメインが決める。abc247_h の台帳の summary の反映と、両問題の `checked` に 2026-10-22 を入れることを提案する。）

## 総合の判定

**小さな直しで可**。直すべき指摘は 0 件、直すとよい指摘は 6 件。事実（数値・漸化式・上昇階乗・EGF・Taylor shift の倍化・例題の閉じた形・Library Checker の定義と制約・ACL の要件）とコード片（コンパイル・cases・サニタイザ・全列挙の照合）はすべて確かめられた。
