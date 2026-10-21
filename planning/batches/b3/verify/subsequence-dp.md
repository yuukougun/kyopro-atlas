# subsequence-dp の検証（b3）

対象：docs/dp/subsequence-dp.md、snippets/subsequence-dp/（count・kth・nonadjacent・shortest）、docs/img/subsequence-dp/leftmost-dag.svg。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page subsequence-dp`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page subsequence-dp`：直すべき行 0
- `python3 tools/check_snippets.py -v snippets/subsequence-dp`：4 本・23 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 4 本を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルし、警告・実行時エラーなし（main の assert で全列挙と一致。`aba`→7、`abcab 10^18`→-1、`aba 3`→ab、`abab`→5、`abcab 3`→cc）
- `npx textlint`：エラー 0・警告 19（数式を含む文の長さ・`$a[0, i)$` の括弧・助詞の重なり。§13-8 の範囲）
- 作業用の場所の chk.py（リポジトリには置かない）で、執筆者が自分で導いた主張を全列挙と照らした。すべて正しい
    - ABC299 F の DP（2 つ目の T の先頭 j を固定、(p, q) を同時に進め、nxt[p + 1][S_j] = j で終える）：a〜c、長さ 1〜11 の 600 通りで TT が部分列になる T の数と一致
    - ABC230 F の言い換え（(S_1, …, S_{N−1}) の空を含む異なる部分列の数）：値 −2〜2、N ≤ 10 の 2000 通りで、切れ目の全列挙と一致（N = 1 で 1）
    - 最短の長さ＝「すべての文字がそろうごとに区切った区間の数 + 1」：σ = 2, 3 の 1000 通りで一致
    - kth.yaml の大きな case（`abc…z` × 3、K = 10^18）の期待出力を、頭打ちなしの多倍長の cnt で計算し直して一致
- 本文の数値：aba の nxt の表（nxt[0] = (0, 1)、nxt[1] = (2, 1)、nxt[2] = (2, 3)）、dp = 1・1・2・3、合計 7・空を除いて 6、配る先の表、図の辺 5 本と dp の値、確認問題（aba の 6 つと 2^3 − 1 = 7、aab の nxt[0][a] = 0、(1, 1, 2) の f = 1, 2, 3, 6）、`aa` の二重の数え方、N = 2×10^5・σ = 26 で約 5×10^6、N = 10^6・σ = 26 の int 表 約 104 MB、cnt の 8 MB、頭打ちの和 ≤ 2(K + 1) ≈ 2×10^18 が long long に収まること
- 定理・性質：最も左の取り出し方の存在と一意性、f[i+1] = 2f[i] − f[l]（X a_i が a[0, i) の部分列 ⇔ X が a[0, l) の部分列）、len の遷移と広義単調減少（S[i, N) の部分列は S[i+1, N) の部分列を含む）、cnt の式、K 番目の決め方（コードの順と本文の手順 1〜3 が一致）、隣を選ばない場合の貪欲の正しさ
- 計算量：要点・complexity・本文の O(σN)・O(N log N)・O(σN^3)（ABC299 F、|S| ≤ 100）が一致
- 問題：ap.py で 6 問の題名・diff（1973・2113・2349・2072、典型90 006 と TDPC G は なし）が本文と一致。www.luogu.com.cn の訳で、abc214_f（1 文字以上・隣接不可・10^9+7・|S| ≤ 2×10^5）、abc230_f（|A_i| ≤ 10^9・N ≤ 2×10^5・998244353）、abc299_f（空でない T・|S| ≤ 100・998244353）を確かめ、本文の方針・要約と合う。TDPC G の空を含めないことと N ≤ 10^6・K ≤ 10^18 は drken の Qiita で確認
- リンク先の anchor：subsequence-matching の next-occurrence・greedy-matching・position-lists・lexicographically-smallest、dp-phase#matched-prefix、counting-dedup の representative・leftmost、dp-reconstruction の lexicographic-min・dp-kth-lexicographic、lcs#count-pairs、用語集の representative・bijection・sentinel・overflow はすべて実在。dynamic-dp と patterns/subsequence-and-substring は stub で、anchor なしのリンク（§14-23 どおり）
- 参考の URL：5 件とも付録 B のドメイン。drken の Qiita（h1「部分列 DP --- 文字列の部分文字列を重複なく走査する DP の特集」、ARC081 E・TDPC G を扱う）、merom686「ABC214」（最後に選んだ位置ごとの DP、直前の同じ文字より前からはつながない、隣接で 1 ずれる調整）、drken の ARC081 E（h1 一致、後ろからの DP と復元）、drken の TDPC G（h1 一致、詳細は Qiita へ誘導）、kanpurin「競技プログラミング　典型問題メモ」（部分列 DP の項に ABC214 F・ABC230 F・ABC299 F が名前だけ並ぶ）。書かれたとおり
- 図：`python3 tools/render_svg.py` で 360px・720px と 640px×2 の PNG を目で確かめた。白背景・viewBox・sans-serif・太線と点線の併用はよい。辺の向き・ラベル・dp の値は本文と一致

### 執筆者の未解決の点について

- **abc230_f・abc299_f の方針を自分で導いた点**：上のとおり、どちらも全列挙と照合して正しい。問題の細部も luogu の訳と合う。第三者の解説が台帳にないことは残るので、メインが evidence を足すなら探す（本文の直しは要らない）
- **abc230_f の詳細を count.cpp:prev で代えている点**：解法の詳細に「答えは f[N−1]、N = 1 なら 1、空を引かない」と境界が書かれており、取り込みのコードで足りる。問題専用のコードは要らない

## 指摘

1. **直すべき**｜F2・F3 式の誤り｜with-conditions の「隣り合う位置を選ばない」（165 行）｜「最も左の取り出し方は p_k = nxt[p_{k−1} + 2][X_k] になる」とあるが、leftmost の節で p_0 = −1 と置いているので、k = 1 では nxt[1][X_1] になり誤り。S = `ab`、X = `a` で、正しい p_1 = 0 に対し式は nxt[1][a] = N（取れない）になる。コード（nonadjacent.cpp の 1 文字目を nxt[0] から配る）と例題の解法の詳細の初期値は正しく、本文の式だけがずれている｜S = `ab` で手計算｜「k ≥ 2 で p_k = nxt[p_{k−1} + 2][X_k]（1 文字目は p_1 = nxt[0][X_1]）」とするか、「この場合は p_0 = −2 とおく」と断る

2. **直すべき**｜F2 主張の誤り｜使い分けの最後から 2 行目（288 行）｜「貰う形の遷移は線形なので、行列にしてセグメント木に載せる」とあるが、f[i+1] = 2f[i] − f[l] は直前の出現位置 l の値 f[l]（任意に遠い）を参照するので、位置ごとの固定の大きさの行列にはならない。セグメント木に載せられるのは、状態を「末尾の文字が c である異なる部分列の数 g_c（c ごと）と定数 1」のベクトルにし、文字 c を読むと g_c ← Σ g + 1 とする形で、これは (σ + 1) × (σ + 1) の行列になる。申し送りの dynamic-dp（abc246_h）もこの形で書くことになる｜式の依存を確かめた（f[i+1] は f[i] と f[l] の 2 項で、l は入力で変わる）｜「末尾の文字ごとの個数を状態にすると遷移が (σ + 1) 次の行列になるので、セグメント木に載せる（[動的 DP](../dp/dynamic-dp.md)）」に直す。報告の申し送り（「貰う形の遷移 … は線形なので行列にしてセグ木に載せる」）も同じく直す

3. **直すとよい**｜U3 飛躍｜next-table-dp の最後の段落（114 行）｜「位置 i で終わる部分列は直前に使った位置が l 以上のものに限られる」から、なぜ 2f[i] − f[l] になるのかの橋がない。読者は「同じもの」を確かめられない｜—｜「その数は a[l, i) のどこかで終わるもの（l がなければ空も）で f[i] − f[l] 個。使わないもの f[i] 個と足して 2f[i] − f[l] になる」と 1 文足す

4. **直すとよい**｜F8 出典に近い例｜本文の主な例 S = `aba`（68〜96 行・確認問題）と count.yaml の cases `abcde`・`aaaaa`・`aba`｜drken の Qiita の問題 1 の数値例が `abcde`・`aaaaa`・`aba` で、例の文字列がそろって同じ。dp の定義（最後に使った位置が p − 1、dp[0] = 1 は空）も同じ形である。定義は標準的なのでよいが、例まで同じだと「記事の例をそのまま使う」に当たる｜Qiita の記事を開いて確かめた｜少なくとも count.yaml の cases を別の文字列（`abb`・`bbbb`・`abcd` など）に替える。本文と図の `aba` も、余力があれば `abb` など別の例にする（図・表・確認問題をそろえて直す必要があるので、メインの判断でよい）

5. **直すとよい**｜G3 スマホで読めるか｜leftmost-dag.svg｜幅 360px では 0.56 倍になり、下の説明 3 行（14px）が約 8px、「位置 0」（12px）が約 7px で読みにくい。また太線の説明の行は viewBox 640 の右端まで約 6px しか余白がなく、フォントによってははみ出す。下の説明 3 行は本文 70 行と同じ内容である｜render_svg.py の 360・720・640×2 の PNG｜下の説明を削るか 2 行に短くし（例：「太線：ab の最も左の道 0 → 1 → 2」「0 からの道 7 本 ＝ 異なる部分列 7 個」）、viewBox の幅を 560 程度に詰める

6. **直すとよい**｜U3 語のあいまいさ｜落とし穴「表のメモリ」（187 行）｜「数え上げの DP は後ろから進むので」とあるが、ページの主役の数え上げ（next-table-dp）は前から配る。ここで言うのは kth の cnt の DP である｜—｜「K 番目のための cnt の DP は後ろから進むので」とする

7. **直すとよい**｜§14-25 箇条書きの句点｜positions-or-strings（54・55 行）、leftmost（63・64 行）、next-table-dp の 4 項目（78〜81 行）、shortest-non-subsequence の 4 項目（120〜123 行）、TT の箇条（171〜173 行）、練習・力試しの方針（240〜242・253 行）、使い分け（283〜289 行）｜行末に句点がない｜本文を読んだ｜各行の末尾に「。」を付ける

## 台帳への提案（検証で確かめたもの）

- abc214_f：summary を「…1 文字以上取り出して…」にする執筆者の提案に賛成（luogu の訳で 1 文字以上を確認）。checked を 2026-10-21 に
- abc230_f・abc299_f：問いと制約を luogu の訳で確認し、本文の方針を全列挙で確かめた。checked を 2026-10-21 に。evidence は分類記事だけなので、第三者の解説が見つかれば足す
- tdpc_lexicographical・arc081_c：evidence に Qiita の記事を足す執筆者の提案に賛成（TDPC G の空を含めない・N ≤ 10^6・K ≤ 10^18 と、ARC081 E の DP と復元がそこにある）。checked を 2026-10-21 に

## 総合の判定

**小さな直しで可**。中心の主張（最も左の取り出し方の一意性と道との全単射、配る DP、貰う形の式、最短の非部分列、K 番目の決め方と頭打ち）と、執筆者が自分で導いた ABC230 F・ABC299 F の方針は、すべて全列挙と照らして正しい。コード 4 本もサニタイザ付きで問題なく、図の値も本文と一致する。直すべきは 2 件（隣を選ばない場合の p_1 の式、使い分けの「貰う形の遷移を行列に」の誤り）で、どちらも 1 文の書き直しで済む。ほかに直すとよい 5 件。
