# multiplicative-order の報告（b3）

- 書いたファイル：docs/math/multiplicative-order.md、snippets/multiplicative-order/order.{cpp,yaml}（範囲 core・root）、snippets/multiplicative-order/bsgs.{cpp,yaml}（範囲 core）、docs/img/multiplicative-order/powers-mod7.svg・bsgs.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 0 行。check_snippets 2 本とも期待どおり（order は m ≤ 300 の全 a で素朴な位数と比較・素数で「位数 d の元が φ(d) 個」・最小の原始根 998244353→3、469762049→3、10^9+7→5、200003→2 を assert。bsgs は m ≤ 120 の全 (a, b) で素朴な探索と比較）。textlint エラー 0、警告 18（数式を含む文の長さ・数式の中の読点・問題の行の長さ・助詞の重複の誤検出で、§13-8・§14-25 の範囲）
- 図：2 枚とも render_svg.py で 360px・720px にして目で確かめた（powers-mod7 は初版で指数のラベルが題と重なったので直した）
- 動く図：catalog の visual は static・priority 2 なので、静的な SVG 2 枚で代えた
- 使った出典：kazun（ABC270 G・ABC222 G）、drken（ABC212 G・ARC042 D・AGC047 C・ABC335 G）、cp-algorithms（Primitive Root・Discrete Logarithm。事実の確認だけ）。新しいドメインはない

## 台帳への提案

- なし（6 問とも summary・approach は evidence の解説と合っていた）
- 補足：abc335_g の evidence を WebFetch で要約させたところ「ord(b) が ord(a) の倍数」と逆向きに出たが、数学的には「a^k ≡ b となる k がある ⇔ ord(b) | ord(a)」であり、台帳の approach（d_j が d_i を割り切れば）が正しい。本文もこの向きで書いた
- abc335_g の P の上限は解説では 10^13 未満程度（drken）。台帳の summary に「（P ≤ 10^13 程度）」を足すかはメインの判断に任せる（本文の方針では「10^13 近い」とだけ書いた）

## 用語集への提案

- 平方剰余｜quadratic-residue｜素数 p と p の倍数でない a について、x^2 ≡ a (mod p) を満たす x があるときの a。オイラーの規準 a^((p−1)/2) ≡ 1 で判定する（本文では用語集へリンクしていない。ほかのページで使うなら）
- 不動点｜fixed-point｜関数 f について f(γ) = γ を満たす γ。一次漸化式 X ← AX + B では γ = B/(1 − A) を引くと等比数列になる（本文ではリンクしていない）

## 手引きへの提案

- §5 math に「離散対数（BSGS）で最小の解を返すときは、表の同じ値には大きい j を残す（x = in − j の形）。x = 0 と『正の最小』を区別する」を足すとよい
- 同じ法での余りの積が 2^63 を超える問題（法 10^12・10^13）が数論のページに複数ある（euler-phi・このページ）。`__int128` の mulmod を持ち主のページ（miller-rabin#mulmod か mod-pow）に置き、ほかはリンクする決まりにするとよい

## 問題の補充の候補

- 今回は ap.py での新しい探索をしていない。catalog の level_evidence のとおり、abc319 以降の ABC で位数・離散対数を主に使うのは abc335_g（力試し）だけと見ている。水・青より上の帯なので、例題 2・練習 2・力試し 2 で目安を満たしている
- Library Checker の Discrete Logarithm・Primitive Root・Sqrt Mod・K-th Root (Mod) は本文の発展の節で動作確認用としてリンクした

## 未解決の点

- 原始根の存在条件（1, 2, 4, p^k, 2p^k）の証明は書かず、cp-algorithms を参考に挙げただけ（文章は使っていない）
- Tonelli-Shanks の O(log^2 p)・Cipolla の期待 O(log p) は一般に知られた値で、この作業では出典を読んで確かめていない
- b2 の convolution-ntt の申し送り（「NTT に向く素数と 2^c 乗根」の節があれば #acl から張り替え）について：独立の節は作らず、primitive-root の節の末尾に「応用の型（NTT の 2 の冪乗根）」として書いた。張り替えるなら convolution-ntt から `multiplicative-order.md#primitive-root` へ
- euler-phi の divisor-sum の節（draft）と内容が一部重なる（位数 d の元が φ(d) 個）。このページでは原始根による証明と「届くかどうかは位数の割り切りで決まる」に絞り、和の式は euler-phi へリンクした

## 使用量の目安

- 道具の呼び出し 約 40 回、Web 取得 8 回（WebFetch 8）

## 検証の指摘への対応

- 直すべき 1・直すとよい 7 をすべて採った（採らなかったものはない）
    - 1：要点の計算量と complexity を、位数と原始根で分けて書き直した（原始根は候補 1 個の判定が O(log² m)、実際には小さい候補で見つかる）
    - 2：bsgs の応用の型に「x = in + j の形では小さい j を残し、i = 0 から引く」を足した
    - 3：count-by-order の割り切りの説明で未知数を z に変え、ord(y) | d への結論の 1 文を足した
    - 4：bsgs.svg を幅 560 に詰め、文字を 20〜21px にし、説明文を短いラベルにした（render_svg.py の 360px で確かめた）
    - 5：mul-to-add の擬似コードに「t + (p − 1) が範囲外なら 0」を添えた
    - 6：確認問題の答えを √m の約 6×10^4 回との比較（約 16 倍）に直した
    - 7：order.cpp の core のコメントを O(log phi × log m) にした
    - 8：affine-recurrence の「周期は P ほど」を「P 近くになりうる」にそろえた
- 共有ファイルへの新しい提案はない
