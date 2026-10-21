# gcd-properties の報告（b2 執筆）

- 書いたファイル：docs/math/gcd-properties.md、snippets/gcd-properties/{rect-gcd,subarray-gcd}.{cpp,yaml}、docs/img/gcd-properties/staircase.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 構成：technique（青）。要点 → 5 つの中身の節（各節の末尾に応用の型）→ 落とし穴 → 使い分け → 例題 → 練習問題（方針は折りたたみ）→ 確認問題 → 参考。acl: [] なので ACL の囲みはない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（両コード片とも素朴な計算と assert で比べている）、textlint エラー 0・警告 32（数式を含む文の長さ・読点の数・半開区間の角括弧・別行の数式の誤検出が中心）
- 図：staircase.svg（catalog の visual：priority 2・static の「区間 gcd が右に伸ばすたびに約数へ下がる階段グラフ」）。render_svg.py で 360px・720px の PNG にして目で確かめた。動く図の置き場は作っていない
- 使った出典：Kazun の abc254_f の記事（隣接差への帰着・Sparse Table とセグメント木の計算量）、drken の abc210_e・agc026_b の記事（練習の方針）、en.wikipedia の Coin problem（ab − a − b と表せない数の個数）。luogu の arc159_b の記事は候補の裏付けだけに使い、本文では使っていない。新しいドメインはない

## 台帳への提案

- abc254_f｜checked｜2026-10-21｜evidence の記事が abc254_f のものであること、制約（N, Q ≤ 2×10^5、A_i, B_j ≤ 10^9）、隣接差の区間 gcd に帰着する方針を確かめた｜https://kazun-kyopro.hatenablog.com/entry/ABC/254/F
- agc026_b｜checked｜2026-10-21｜evidence の記事が agc026_b のものであること、場合分け（A < B、D < B、C ≥ B − 1）と、B 未満で A と mod gcd(B, D) で合同な最大の値 B − g + (A mod g) が C を超えるかの判定を確かめた｜https://drken1215.hatenablog.com/entry/2018/07/18/083000
- abc210_e｜（変更なし）evidence の drken の記事で、費用の小さい順に使い成分の数が gcd(n, A_i) に減る方針を確かめた。本文の行は fix_problems が台帳の主の summary（「環状に並ぶ頂点に…」）で作った。alternatives の gcd-properties 用の summary は使われていない

## 用語集への提案

- なし（「互いに素」は既存の coprime へ、「単位元」は本文で用語集へリンクしていない。必要ならメインが足す）

## 手引きへの提案

- なし

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- arc159_b（GCD Subtraction、diff 1438、ap.py で実在を確認。台帳になし）：2 つの数の両方から gcd を引く操作を、片方が 0 になるまで何回行うかを数える。差が変わらないので、gcd の候補が差の約数（素因数）に絞れる。差の gcd の節の応用の型「2 つの数から同じ数を引き続ける」の練習に推す。level は水寄りなので練習｜https://www.luogu.com.cn/article/x31btgkz（中国語。差が不変で、次に gcd が 1 でなくなる素数 p が差の素因数であることを使う方針。問いの細部は記事の要約からの推定なので、日本語の解説でもう一度確かめてほしい）
- abc469_f（GCD Maximum Spanning Tree、diff 1567、台帳で確認済み・minimum-spanning-tree と harmonic-sum の練習）：本ページの型とは別（gcd の値ごとに倍数をまとめる調和級数の型）なので、足さない
- abc319 以降で、差の gcd・区間 gcd・mod の周期が鍵になる問題は今回も見つからなかった（ap.py の題名検索「GCD」で abc319 以降は abc393_e・abc469_f だけで、どちらも約数・倍数の列挙の型）
- 線分上の格子点・作れない数の上限の節には問題を付けていない。格子点はピックの定理の問題（typical90_ao、convex-hull の例題）につながるので、本文では凸包へリンクするだけにした

## 未解決の点

- 区間 gcd の右端固定の列挙の計算量を O(N log² A)（組 O(log A) 個 × gcd O(log A)）と上から押さえた。より細かい評価（gcd の手数のならし）で O(N log A) 程度に下がる可能性があるが、確かめていないので書いていない
- セグメント木の取得が O(log N + log A) になる注記（gcd の手数 O(1 + log(g/g')) の和がつぶれる）は、Kazun の記事の計算量の記述と互除法の手数の評価から書いた。検証役に確かめてほしい
- 「表せない正の整数は (a − 1)(b − 1)/2 個」の理由を、余りごとの個数 ⌊b y_ρ / a⌋ の和として 1 文で書いた。和が (a − 1)(b − 1)/2 になること自体の証明は省いている
- 3 種類以上の数で作れる値を、最小の数の余りごとにダイクストラ法で求める方法に 1 行だけ触れた（同余最短路）。リンク先は dijkstra のページ全体で、該当する節があるかは確かめていない
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 6 回（WebSearch 1 回を含む）

## 検証の指摘への対応（b2）

- 1（直すべき）：本文を「$A = 10^9$ なら 30 種類以下（$2^{29} \le 10^9 < 2^{30}$）」に直し、確認問題の答えに「$2^{30}$ は $10^9$ を超えるので 1 つ多い」と 1 文足した
- 2：尺取り法に「窓の gcd は左端から取り除けないので、Sparse Table で $O(1)$ 回の gcd として求める」と添えた
- 3：注記に `std::gcd`（libstdc++ は二進 gcd）では和の評価が当てはまらないことを足し、見積もりの文とまとめた
- 4：ダイクストラ法のリンクは残し、[同余最短路](../graph/modular-shortest-path.md) へのページのリンクを足した。**提案**：modular-shortest-path が書かれたら、メインが `#congruence` へ張り替える
- 5：図の見出しを「gcd(a₀, …, aᵣ)」、列の下のラベルを「a = 48」などにした
- 6：凡例を 14px にし、文を縮めて 1 行に収めた。ラベルも 14px にした（360px で目視）。2 行に分けると 1 列目の棒の数値と重なるので 1 行にした
- 7：採らなかった。geometry/convex-hull は stub で、stub の節へのリンクは check_pages が禁じるため、ページへのリンクのままにした。**提案**：convex-hull が書かれたら `#lattice-points` へ張り替える
- 8：「（並べ替え論法の確認問題と同じ例）」に直した
