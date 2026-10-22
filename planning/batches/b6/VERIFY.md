# b6（問題の補充）の検証

- 検証した日：2026-10-22。対象は git diff（data/problems.yaml と 51 ページ）と APPLIED.md
- 結論：**重大な誤りは見つからなかった**。軽い直しを 2 か所した（下の「直したもの」）。commit はしていない

## 1. 実在・題名・difficulty（ap.py で全件）

- 台帳に新しく足された 51 件（APPLIED.md の数と一致）を `python3 tools/ap.py show --json` で引き、contest・index・title・difficulty・experimental を台帳と機械的に突き合わせた。**不一致 0 件**。difficulty のない 9 件（bitflyer2018_final_d・code_thanks_festival_2017_f・ddcc_2016_qual_d・dwacon2018_prelims_e・icpc2013summer_day4_f・joi2020_yo2_e・math_and_algorithm_bt・nikkei2019_final_g・yahoo_procon2018_final_a）も ap.py に存在し、台帳も difficulty null
- 既存の問題の更新 64 件：消えた問題 0 件。ページの 1 行の label・URL・diff が台帳と合うことは `fix_problems.py --check` で確かめた

## 2. 要約と方針を裏付けの URL で確かめた（新しい 51 件のうち 40 件を開いた）

atcoder.jp・codeforces.com は開いていない。次の 40 件は、開いた記事の内容と台帳の summary・approach（ページの方針の折りたたみも一部）が合っていた。

nikkei2019_final_g（navel_tos）・ddcc_2016_qual_d（kmjp）・arc122_a（hal_mat）・bitflyer2018_final_d・code_thanks_festival_2017_f・icpc2013summer_day4_f・dwacon2018_prelims_e（いずれも drken）・yahoo_procon2018_final_a（noshi91）・joi2020_yo2_e（hamayan）・arc185_e・arc121_e・arc111_e・abc248_g・abc315_g・abc389_g・arc044_b・arc074_d・agc035_b・arc111_d・arc137_d・arc122_d（いずれも kmjp）・arc039_d（ei1333 の検証の節）・arc038_d・arc143_d・agc032_c・hhkb2020_f・arc107_d（いずれも drken）・arc142_c・abc319_e・abc349_f・arc150_c（いずれも merom686）・abc379_f（RomanLin）・arc013_3・arc046_b（kmyk）・abc340_f（programming-hiroba）・abc350_f（torus711）・abc405_e（testcampus・rsk0315）・abc217_g（bondo）・abc020_d（tsutaj）・abc409_e（untan）

自分で式を確かめたもの（記事と合わせて）：abc028_d の 1 + 3(N−1) + 6(K−1)(N−K)、abc008_3 の確率（0〜p の偶数の個数）/(p+1)、abc414_e の N + 1 − b − ⌊N/b⌋、arc046_b の場合分け、arc116_b の寄与。

気づいた点（誤りではない）：

- **abc379_f・merge-sort-tree の 4 問**：裏付けの記事はどれもオフライン（単調スタック・BIT）で解いていて、マージソート木で解く最後の一歩は執筆者の導出である。abc379_f の「区間 (r, N] で p(j) ≤ l の個数」は自分でも正しいと確かめた。本文の方針と参考の節は「言い換えの裏付け」として正直に書いてあるので、そのままにした
- **arc150_c**：裏付けの 1 件目 miscalc の記事は ARC150 C を類題として挙げるだけで解き方を書いていない（ネタバレ回避で畳んである）。2 件目 merom686 が「一致数の最小をダイクストラ法（01-BFS も可）」を裏付ける。ページの参考の節は miscalc を「ダイクストラ法が使える 2 つの条件」の出典にしていて、内容と合っている
- **abc405_e**：approach の「和の範囲が切れるので閉じた式にしない」は執筆者の判断。rsk0315 は項ごとの閉じた形を出したうえで O(B) の和を取っていて、矛盾はない

## 3. 手法の練習として妥当か

- arc122_a（parsing の練習）：構文解析そのものではなく、+ と − の式すべての値を和のまま更新する DP である。ただ、ページの例題 arc061_a と節 #substring-sum が同じ「全部の式の和を和のまま更新する」型なので、置き場所として妥当と判断した。結びつきが読めるよう、方針に一文を足した（下の「直したもの」）
- agc032_c（euler-path）・arc143_d／arc111_d（graph-construction の向き付け）・abc174_f ほか（merge-sort-tree）・code_thanks_festival_2017_f／bitflyer2018_final_d／icpc2013summer_day4_f（gaussian-elimination）・arc137_d／abc349_f（zeta-mobius-subset）・yahoo_procon2018_final_a（zeta-mobius-divisor）など、ほかはページの手法の中心を使う
- 例題の持ち主がほかにある問題を練習・力試しに置いたもの（APPLIED.md の一覧）は、どれも alternatives にページ向けの方針があり、本文も別解として書いている

## 4. レベルの帯と役割

ページの level と問題の帯の差（+ は難しい側）を全行で出した。目立つものだけ挙げる。

- **steiner-subtree（基礎）の力試し abc149_f（2208、+3）**：帯から大きく上に離れる。力試しなので誤りではないが、メインの判断に任せる（外すなら typical90_ai だけが残る）
- probability-basics（基礎）の力試し abc008_3（1836、+2、experimental）・ext-gcd（水）の力試し abc315_g（+2）・floor-quotient-enum（水）の力試し abc132_f（+2）：力試しとして許容範囲
- 練習で帯より 2 つ下：parsing の arc122_a（783）・sparse-table の abc125_c（1197）・euler-phi の abc186_e（1461）・game-retrograde-analysis の abc245_f（1451）・tree-centroid の abc348_e（1347）。どれも易しい側の入口として置かれていて、役割（練習）とは合う
- nim の arc013_3（1831、+1）を練習に置いた判断（APPLIED.md）は、既存の練習 arc143_c と同じ高さなので妥当
- exponent-mod（水）の練習 abc212_g（2150、+2）は今回の追加ではなく、もとから台帳にあった配置（catalog 由来）
- 数の目安（練習 2〜6・力試し 0〜3）を超えたページはない。divide-and-conquer の練習 1 問はもとから

## 5. 検査

- `python3 tools/fix_problems.py --check`：直すべき行 0・直せない行 0（見たページ 354）
- `python3 tools/check_pages.py`：エラー 0・警告 0
- `uv run mkdocs build --strict`（-q なし）：終了コード 0。WARNING・ERROR なし（Material for MkDocs チームの告知の枠が出るだけ）
- 直した 2 ページの `npx textlint`：エラー 0（警告は文の長さ・助詞などの既存の種類）
- 上の 4 つは直した後にもう一度通した

## 直したもの

- docs/math/gaussian-elimination.md：CODE-THANKS-FESTIVAL-2017 F の方針の「（想定解は値の和の制約を使う DP）」を「（値の和が $10^5$ 以下という制約を使う別の解き方もある）」に。裏付けの drken の記事は値の和の制約を見落としたと書くだけで、想定解が DP だとは書いていないため
- docs/misc/parsing.md：ARC122 A の方針の末尾に「例題 ARC061 C と同じく、すべての式の値を和のまま更新する形で、[式の部分文字列の総和](#substring-sum)の易しい版に当たる」を足した（構文解析のページに置く理由が読めるように）

## メインへの申し送り

- steiner-subtree の力試し abc149_f（+3）を残すかの判断
- 見送った abc411_e の正規表現の件（APPLIED.md の提案）は道具の変更なので、検証では扱っていない
