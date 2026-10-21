# counting-basics の報告（工程8b・バッチ b1）

- 書いたファイル：docs/comb/counting-basics.md、snippets/counting-basics/distance2.{cpp,yaml}、snippets/counting-basics/cycle-coloring.{cpp,yaml}、docs/img/counting-basics/line-vs-cycle.svg
- front matter で変えたもの：complexity（`式が段階の数 N の累乗を含むなら、繰り返し二乗法で O(log N)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（「上位の手法とのつながり」は節を立てず、各節の末尾と「使い分け」に分けて書いた）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（このページの直すべき行 0。basics/lexicographic-greedy.md に 6 行あるが担当外）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 4。「赤赤青青」の連続語、図の代替テキストの「K, K−1, …」の読点、「玉も箱も」の「も」、台帳の summary の行の「に」で、いずれも意図した表記か生成部分）
- 式の確かめ：一列で距離 2 以内が異なる $K(K-1)(K-2)^{N-2}$、円環の $(K-1)^N + (-1)^N(K-1)$ を、$N \le 6$・$K \le 4$ の全列挙で照合した。本文の数値（3 桁の偶数 328、4 桁の 5 の倍数 952、$20! < 2^{63} < 21!$）も計算で確かめた（一時置き場の brute.py）
- 図：静的な SVG（一列と円環の 5 個を並べ、各位置の選択肢の数を書き、円環の 5 番目だけ「K−1 か K−2」を破線の枠で示す）。catalog の visual は static・priority 2 なので動く図は作っていない。SVG を描画する道具が手元になく、見た目は目で確かめていない。検証役に描画の確認を頼みたい

## 使った出典

- E869120 kyopro_educational_90 sol/069.cpp（github raw）：例題の式と $N = 1$・$N = 2$・$K = 1$ の場合分け
- drken ABC307 E（hatenablog）：問いと制約（$2 \le N, M \le 10^6$）、両端を同じ色にまとめて $N - 1$ 個の円環に帰着する漸化式 $\mathrm{dp}[n] = M(M-1)^{n-1} - \mathrm{dp}[n-1]$、1 人目と同じかを状態にした DP
- shinonome81（zenn.dev）ABC307 E：一列の数 $M(M-1)^{N-1}$ との違い、DP の状態
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

- typical90_bq｜checked｜2026-10-21｜sol/069.cpp で問いと方針を確かめた｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/069.cpp
- abc307_e｜checked｜2026-10-21｜https://drken1215.hatenablog.com/entry/2024/06/10/024932
- abc307_e｜approach（counting-basics の alternatives）｜「両端が同じ色の一列は N−1 個の円環に対応するので C_N = M(M−1)^(N−1) − C_(N−1)。閉じた式 (M−1)^N + (−1)^N (M−1)。または最初の人と同じ値かを状態にした DP」に具体化してもよい｜同上
- abc178_c｜pages に counting-basics（role: practice）を足す案｜和の法則で重なりを足す落とし穴（「0 を含む」と「9 を含む」）と、$10^N$・$9^N$・$8^N$ の重複順列を使う。本文の落とし穴の節で型だけ触れた（問題 ID は出していない）｜https://drken1215.hatenablog.com/entry/2020/10/09/162600

## 用語集への提案

- 排反｜disjoint｜2 つの集まり（場合）が共通の要素をもたないこと。排反な場合に分けたときだけ、各場合の数を足して総数にできる（和の法則）。本文で `../guide/glossary.md#disjoint` にリンクした

## 手引きへの提案

- §4 の「technique（基礎）」の構成の「上位の手法とのつながり」は、sections に専用の節がないページでは各節の末尾と「使い分け」に分けて書くことになる。定型の節（§13.1）に `## つながり {#next-steps}` のような見出しを足すか、「使い分け」で兼ねてよいと明記するとよい
- 問題の囲みの中の折りたたみ（解法の詳細）にコード片を取り込むとき、4 字下げの `--8<--` で取り込めることを §9 に一言あるとよい（lazy-segment-tree・bit-operations でも同じ書き方）

## 問題の補充の候補

catalog の練習は abc307_e の 1 問だけで、手引きの目安（練習 2〜6）に届かない。

- abc178_c（Ubiquity、diff 653、ap.py で実在を確認）：長さ N の数字の列で 0 と 9 をどちらも含むものを数える。重複順列と、和の法則で重なりを扱う型。台帳では complement の例題なので、ここでは練習として足す案｜https://drken1215.hatenablog.com/entry/2020/10/09/162600
- 積の法則・円順列だけで解く易しい ABC（C・D）は、今回は探しきれていない。必要なら調査で「並べ方の数」「何通り」の ABC C を拾う

## 未解決の点

- typical90_bq の $K$ の上限は確かめていない（解答のコードは `int K` で読み、`K % mod` を取っている）。本文では「$K$ が法より大きくてもよいように余りにしてから掛ける」とだけ書き、制約の値は書いていない。コード片は $K$ を `long long` で読む
- 円順列で同じものを含む場合の例（赤 2・青 2 で 2 通り）は手で数えた。Burnside の補題のページは stub なので、ページへのリンクだけにした
- 関連ページ（mod-pow・dp-state-design・twelvefold-way など）はどれも stub なので、節へのリンクは付けず、ページへのリンクにした。dp-state-design が draft になったら `#dp-cyclic` を付けてほしい（円環の DP の節）
- リンクの文字は各ページの front matter の title に合わせた（重複組合せ・順序を固定して数える など）
