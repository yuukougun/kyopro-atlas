# expectation-linear-equations の検証（b2）

- 対象：docs/comb/expectation-linear-equations.md、snippets/expectation-linear-equations/{restart,ring}.{cpp,yaml}、docs/img/expectation-linear-equations/restart-axb.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page expectation-linear-equations`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/expectation-linear-equations`：restart 7 case・ring 4 case すべて一致。`-fsanitize=address,undefined` でも cases と ring の N = 3000 で異常なし
- restart の cases：K=4・q=2/3 の期待値は Σ_{j=1..4}(3/2)^j = 195/16 で、mod 998244353 で 811073549（Python で計算）。K=2・q=1/3 → 3 + 9 = 12。ほかの case も 1/q + … + 1/q^K で一致
- ring の値：a + bX を使わず、n ごとに Fraction の連立方程式を掃き出し法で解く別の Python で N = 2・3・5 を計算し、cases と一致
- 等比級数の節：p/(1−p²)、p²/(1−p²)、進む確率 1/(1+p)・p/(1+p)、方程式 u = p(1+v)・v = pu の解はすべて正しい
- ARC174 C の解法の詳細：r_1 = 0 と r_{i+1} の漸化式による先手・後手の罰金を、(状態, 手番) の 2×2 の方程式を後ろから厳密に解く別の Python と N = 1〜7 で比べ、すべて一致。合計 Σ i/(N−i) とも一致
- 確認問題：表 3 回で E[0] = 7/4 + 7/8 X、X = 14、b = 7/8 = 1 − 1/8。円環で d_i = 1 のときの閉じる式。どちらも正しい
- 「b は始めの状態へ戻る確率」（例で 1/2 + 1/4 = 3/4）、円環の閉じる係数 d_0 d_1 ⋯ d_{n−1}、ABC333 F の漸化式と 1 − (1/2)^n ≠ 0、二分探索の f(y) − y = a − (1−b)y による向き、(I − P) が逆行列を持つ条件（着けない状態があると、その到達集合の行がブロック三角で特異）、O(km + k^3)：正しい
- 問題 4 つ：`tools/ap.py show` で題名・diff（1706・1770・2154・2374）を確かめ、本文と一致
- 参考の 3 つの URL（付録 B の kmjp・drken1215）：題名と内容は書かれたとおり。drken の記事は小さい N から包除原理の形を予想し、偶数回目・奇数回目ごとに公比 ((N−j)/N)^2 の等比級数で足す（本文の別解の記述と合う）。kmjp の ABC189 F は X を仮定して二分探索・累積和・M 個続くと −1。kmjp の ABC224 G は閾値 x を決めて f(x) = A(x−1)/2 + BN/x とし凸性で最小を探す。文の並びや例をそのまま使った箇所はない
- 図：値・添字は本文と一致（(0,0)・(1,½)・(3/2,3/4)、X = 6）。白背景・viewBox あり・font-family="sans-serif"・相対パス。破線と実線で戻る辺を区別しており、色だけに頼っていない
- リンク先の anchor（expected-value-dp#self-loop・#prefix-sum、coupon-collector#geometric、rational-mod#no-compare、geometric-series-mod#formula）はすべてある

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2 | #infinite の「mod のとき」の 2 文目 | 「mod の値が 1 でないことは、本当の b が 1 でないことの保証にならない」は誤り。b は遷移確率（分母が法と互いに素な有理数）の足し算と掛け算だけで作られるので、本当の b = 1 なら mod の値も必ず 1 になる。したがって「mod の値が 1 でない ⇒ 本当の b は 1 でない」は成り立つ。危ないのは 1 文目の向き（偽陽性）だけ | 対偶。有理数から mod への写像は環準同型（分母が逆元を持つ範囲で） | 2 文目を消し、「mod の値が 1 になっても本当の b が 1 とは限らない（偽陽性）。値で判定できるのは『1 でない』側だけである」のように書き直す |
| 2 | 直すべき | code C3・C8 | restart.cpp の 245 行目 `if (e[0].b == 1) return nullopt;` と 254 行目の入力の制約 | ページの主張（b = 1 を mod の値で判定してはいけない。到達可能性で判定する）に、コード片自身が反する。宣言した入力の範囲（0 ≤ P ≤ Q、Q ≥ 1）で実際に誤る。`1 998244353 998244354`（q ≈ 1、本当の期待値は約 1）で -1 を出力する。`1 998244353 1996488706`（q = 1/2）では `mint(p)/q` の逆元で ACL の assert に落ちる。ACL の囲み（92 行目）の「本当に 1 かどうかは実数の側で判断する」とも食い違う | 手元で g++-15 でコンパイルして実行（上の入力で `-1`、`Assertion '_v' failed`） | 終わらないかを入力の整数で判定する（`P == 0` なら -1。表が出る遷移がないときだけ終状態に着けない＝到達可能性）。b の比較は消す。入力の制約に「Q < 998244353」を足すか assert する。コメントを「終状態に着けるのは P > 0 のときだけ（グラフで判定）」にする |
| 3 | 直すべき | code C2 | ring.yaml の case N=2・N=5 | 入出力の形がそのまま ABC333 F と同じで、N=2 と N=5 の 2 つは問題の入出力例と一致している疑いがある（手引き §9「問題の入出力例は使わない」）。検証役の記憶による。atcoder.jp は開いていないので確定はしていない | 手引き 184 行目 | 疑いを消すため、N=2・N=5 を N=4・N=6 に替える（値は Fraction の別解で出せる）。N=1・N=3 は残してよい |
| 4 | 直すとよい | clarity U3 | #infinite の「実数のとき」1 文目 | 「b は 1 に近い値でも、誤差で 1 − b が小さな正の数になり」は意味が取りにくい。言いたいのは「本当は b = 1 なのに、誤差で b が 1 よりわずかに小さくなり」だと思われる | 読者の立場で読んで、主語と条件がつながらなかった | 「本当は b = 1 でも、誤差で 1 − b が小さな正の数になり、巨大な値を答えにしてしまう」とする |
| 5 | 直すとよい | clarity U4・fact F5 | 力試しの方針（ABC224 G） | (1) 「x を決めれば R は未知数を含まない式で求まる」は、R が右辺にも出る（振り直す目で B + R）ので不正確。x を決めると R の 1 次方程式になり、解くと閉じた式になる。(2) 最後の答え（S が範囲内なら A(T − S)、そうでなければ B + R の最小）に触れていない | kmjp の記事（f(x) = A(x−1)/2 + BN/x、S が窓の中なら A(T − S)）と、R = A(x−1)/2 + (N−x)B/x の手計算 | 「x を決めると R は 1 次方程式 R = (A·x(x−1)/2 + (N−x)(B+R))/N になり、解けば x の式になる」とし、「答えは S の位置で A(T−S) か B + R」を一言足す |
| 6 | 直すとよい | fact F7 | #linear-system の最後の段落 | mod p の掃き出しで行の入れ替えが要る話は、gaussian-elimination（今は stage: draft）の #mod-p の節に同じ注意（113 行目）がある。ページへのリンクだけで節に飛べない（執筆者の未解決の点 3） | docs/math/gaussian-elimination.md の 103 行目 {#mod-p}・113 行目 | リンクを `../math/gaussian-elimination.md#mod-p` に張り替え、本文は 1 文に縮めてよい。gaussian-elimination が draft になったので、151 行目のリンクも節（#real か #mod-p）へ張れる |
| 7 | 直すとよい | fact F1 | #cycle の 111 行目「全体で O(N^2)」 | ABC333 F の解法の詳細は「O(N^2 + N log mod)」と書き、コード片も人数ごとに逆元を 1 回取る。同じ計算の計算量の書き方が 2 か所で違う | ring.cpp 299 行目の `/` | 111 行目を「全体で O(N^2)（逆元は人数ごとに 1 回で O(N log mod)）」にそろえる |
| 8 | 直すとよい | figure G3 | restart-axb.svg（幅 360px） | 640 幅の viewBox が 360px に縮み、14px の文字が約 8px になる。上下の説明文と式は読めるが小さい | render_svg の 360px の PNG を目視 | 左右の余白を詰めて viewBox を 560 前後にするか、下の 2 行の説明文（本文にも同じ内容がある）を図から外して縦を詰める |
| 9 | 直すとよい | clarity U6 | #unknown の 85 行目「例のコインの問題」 | 節だけを取り出すと「例」が何か分からない | 断片で読んだとき | 「表が 2 回続くまでコインを投げる例（[#generalize](#generalize)）を」と書く |

## メインへの申し送り（指摘でなく判断事項）

- 練習が ABC189 F の 1 問だけ（執筆者の報告「問題の補充の候補」）。検証でも新しい候補は探していない
- 執筆者の未解決の点 1（abc333_f の第三者の解説がない）：漸化式は上の別解（Fraction の連立方程式）で独立に確かめたので、本文の内容に疑いはない。台帳の evidence を足す件はメインの判断
- 台帳：arc174_c・abc189_f・abc224_g は evidence の記事で問いを確かめた。台帳の approach の修正提案（執筆者の報告）は記事の内容と合う

## 総合の判定

小さな直しで可（直すべき 3 件：#infinite の mod の判定の誤った 1 文、restart.cpp の b = 1 の値による判定、ring.yaml の case の差し替え。いずれも局所的）
