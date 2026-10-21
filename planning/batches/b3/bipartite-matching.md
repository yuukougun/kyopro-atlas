# bipartite-matching の報告と提案（b3）

- 書いたファイル：docs/graph/bipartite-matching.md、snippets/bipartite-matching/{mf-graph,kuhn,bottleneck}.{cpp,yaml}、docs/img/bipartite-matching/{reduction,alternating}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（3 件とも期待どおり）、textlint（エラー0・警告13。助詞の重なり、半開区間 $[l_i, r_i)$ の括弧の対、数式を含む文の長さの誤検出）
- 図：2 枚とも render_svg.py で 360px・720px にして目で確かめた（reduction の 720px の PNG は撮影の高さで下端の注記が切れるが、360px では全体が見える）。visual は priority 2 の静的な図なので、動く図の div は置いていない
- 使った出典：ACL document_ja（maxflow・appendix）、en.wikipedia.org（Hopcroft–Karp algorithm・Berge's theorem・Edge coloring）、github.com/E869120/kyopro-tessoku（A69 の解答コード）、drken1215.hatenablog.com（2023/11/14/023400・2021/07/05/183800・2023/08/27/000216）、kmjp.hatenablog.jp（2025/04/13/0900・2022/08/07/0900・2023/09/17/0930）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| tessoku_book_bq | summary | N×N の表で、i 行 j 列が # なら左の i 番目と右の j 番目を組にしてよいとき、どの要素も 1 回までしか使わずに作れる組の最大数を求める。 | https://github.com/E869120/kyopro-tessoku/tree/main/codes/cpp/chap09 （answer_A69.cpp：N×N の文字の表の # に容量 1 の辺を張り、最大流を出力） |
| tessoku_book_bq | checked | 2026-10-21 | 同上 |
| abc320_g | summary | N 個のリールにそれぞれ長さ M の数字の列があり、時刻 t に止めたリールには列の (t mod M)+1 文字目（0 から数えて t mod M 番目）の数字が出る。同じ時刻に止められるのは 1 つだけのとき、すべてのリールを同じ数字で止め終える最短の時刻を求める（できなければ -1 を出力する）。 | https://kmjp.hatenablog.jp/entry/2023/09/17/0930 （各列の回転数をどれも違う値にして先頭を同じ数字にそろえ、回転数の最大を最小化。-1 の場合あり）。リールと時刻の言い方は Slot Strategy 2 の (Easy) と同じ設定によるもので、kmjp の記事は「回す回数」で書いている。検証役は別の解説でも確かめてほしい |
| abc320_g | checked | 2026-10-21 | 同上 |
| abc401_g | checked | 2026-10-21 | https://kmjp.hatenablog.jp/entry/2025/04/13/0900 で問いと方針を確かめた |
| typical90_by | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2023/11/14/023400 |
| abc263_g | checked | 2026-10-21 | https://kmjp.hatenablog.jp/entry/2022/08/07/0900 |
| abc317_g | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2023/08/27/000216 |
| arc092_a | （bipartite-matching の alternatives の approach） | 青い点を x の小さい順に見て、組める赤い点のうち y が最大のものを選ぶ貪欲で解ける（制約が小さいので一般のマッチングでも解ける。貪欲が通る構造の見分け） | https://drken1215.hatenablog.com/entry/2021/07/05/183800 （記事は貪欲だけを書き、マッチングには触れていない。N ≤ 100 は記事にある） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| マッチング | matching | グラフの辺の集合で、どの 2 本も端点を共有しないもの。選んだ辺の本数をマッチングの大きさという。 |
| 完全マッチング | perfect-matching | すべての頂点がどれかの辺に入っているマッチング。二部グラフで左右の頂点数が違うときは、少ない側（または指定した側）をすべて覆うものを指すことが多い。 |
| 正則グラフ | regular-graph | どの頂点の次数も同じ値 k のグラフ（k 正則）。二部グラフで k 正則なら、辺全体を k 個の完全マッチングに分けられる。 |

本文ではこの 3 語を用語集へリンクしていない（anchor がないと check_pages がエラーにするため）。足したら、節 reduction の最初の「マッチング」「完全マッチング」と、節 edge-coloring の「k 正則」に最初の 1 回だけリンクを張ってほしい。

## 手引きへの提案

- graph の「フローはどんなグラフを作るかを主役に」に、「最大の最小化を二分探索するときは、答えが組のコストのどれかに等しいので、候補をソートして添字で二分探索する（実数の二分探索を避ける）」を足すとよい。abc401_g のように距離が答えの問題で、kmjp の記事は実数の二分探索で書いているが、2 乗の整数のまま比べる方が誤差の心配がない
- §13-5 と check_pages の食い違い（用語集の未登録の anchor をエラーにする）は b2 でも報告がある。手引きを「提案中の語はリンクせず提案に書く」に直すのがよい

## 問題の補充の候補

- 現状は例題 2・練習 3・力試し 2 で目安を満たしているので、補充は探していない
- 「構造で貪欲が通る」節の、しきい値の形・区間の形の練習（ABC の E〜F で貪欲とマッチングの見分けを問うもの）があるとよい。台帳の候補が見つかれば greedy-cases の練習に足したい

## 未解決の点

- 計算量の書き方：ACL のドキュメントは容量がすべて 1 のとき $O((n + m)\sqrt{m})$ と書く。Dinic を単位容量のネットワークで使うと $O(M\sqrt{N})$ になるのは広く知られているが、確かめた資料（Wikipedia の Hopcroft–Karp の記事）は「Dinic の特殊な場合とみなせる」までしか書いていない。本文は「ACL の値」と「Hopcroft-Karp の $O(M\sqrt{N})$」を分けて書き、「Dinic もこのグラフでは同じ動きをする」とした
- 前提の max-flow と、リンク先の konig-theorem・min-cost-flow・general-matching・dilworth-path-cover は stub なので、ページへのリンクだけにした。Hall の結婚定理は dilworth-path-cover の節 hall にあるので、相手が draft になったら `../graph/dilworth-path-cover.md#hall` へ張り替えてほしい（節 edge-coloring の冒頭）
- abc401_g の制約（N の上限、座標が整数か）は kmjp の解答コード（座標を long long で読む・配列 303）からの推測である。本文は「入力の座標が整数なので」と書いた。検証役は別の解説で確かめてほしい
- abc317_g は「必ずできる」と力試しの方針に書いた（M 正則の二部グラフなので）。drken の記事も Hall の定理で完全マッチングがあるとしている

## 使用量の目安

- 道具の呼び出し 約 30 回、Web 取得 9 回

## 検証の指摘への対応（b3 の直し）

- 指摘 1（直すべき）：直した。#abc401_g の解法の詳細に「座標は $10^{18}$ まで、2 乗の和は `__int128`（../cpp/cpp-integer-overflow.md#int128）、節のコードの `long long` のままではあふれる」を足し、出力を `sqrtl((long double)x)` と相対誤差 $10^{-6}$ の説明にした。#pitfalls の「判定に実数を使う」に $10^{18}$ の場合と例題へのリンクを足した。bottleneck.cpp の先頭の注釈に「座標が 10^9 程度までの場合」と `__int128` にする旨を足した（コードと cases は変えていない）
- 指摘 2（直すべき）：直した。#challenge の abc320_g の要約を「(t mod M)+1 文字目（0 から数えて t mod M 番目）」にし、上の台帳への提案の summary も同じに直した
- 指摘 3：直した。#reduction に「左右の数が違うときは、左を覆うマッチングを問うことが多い」を足し、#pitfalls の見出しを「左をすべて組に入れる判定で、左右の数を取り違える」にした
- 指摘 4：直した。reduction.svg は文字を 20px にし、下の 2 行の注記を 1 行の凡例（赤の太線・灰の破線）に縮めた（説明は代替テキストと本文にある）。alternating.svg は「反転の前」「反転の後」を縦に並べ（viewBox 380×706）、文字を 18px にした。代替テキストの内容（辺・組・増加路）は変えていない。render_svg.py の 360px で目で確かめた
- 指摘 5：本文の typical90_by の要約を「時間 T の後に、8 方向のどれかへ（斜めなら x と y の両方を）T だけ動かし」に直した。台帳の summary も下の提案のとおり直してほしい
- 指摘 6：直した。#reduction の整数性の括弧書きを max-flow の #residual へのリンクにし、確認問題 1 を「失敗した始点を見直さなくてよい理由」（交互路でたどれる集合 $A$ が後の増加路に触れない）に替えた
- 指摘 7：直した。ARC092 C の方針を「二部マッチング（`mf_graph`）でも解ける」にした。上の arc092_a の approach の提案の「一般のマッチング」も「二部マッチング（mf_graph）」と読み替えてほしい

### 台帳への提案（直しで足したもの）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_by | summary | N 機の飛行機を時間 T の後に、8 方向のどれかへ（斜めなら x と y の両方を）T だけ動かし、指定の N か所に 1 機ずつ着くようにできるかを判定し、できれば方向を出力する。 | 検証の指摘 5（drken の記事の $A_i + T d$） |
| abc401_g | note | 座標は 10^18 まで（Luogu の AT_abc401_g で確認）。距離の 2 乗は __int128 | 検証の指摘 1 |
| arc092_a | approach | 「一般のマッチングでも解ける」を「二部マッチング（mf_graph）でも解ける」に | 検証の指摘 7 |
