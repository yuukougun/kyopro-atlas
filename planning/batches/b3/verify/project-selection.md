# project-selection の検証（b3）

- 対象：docs/graph/project-selection.md、snippets/project-selection/{builder,closure}.{cpp,yaml}、docs/img/project-selection/cut-example.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py project-selection`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目で確かめた
- atcoder.jp・codeforces.com は開いていない。試しのコードは scratchpad（v-project-selection/bf.py）に置き、リポジトリには置いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page project-selection`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page project-selection`：直すべき行 0
- `python3 tools/check_snippets.py -v snippets/project-selection`：builder（2 case、乱数で 2^n の全探索と照合を各 3000 回）・closure（7 case）すべて一致
- 早見表の 11 行：4 通りの割り当てを手で入れて、どの行も「カット＋定数＝項の値」になる。$K$ 変数の利得（補助の頂点 $y$、$s \to y$／$y \to t$ と ∞ の辺の向き）も正しい。drken の早見表の記事（S 側＝1 の約束）とも一致
- 劣モジュラの分け方 $\theta = A + (C-A)x_i + (D-C)x_j + (B+C-A-D)(1-x_i)x_j$：4 通りで $A, B, C, D$ に一致。コードの `binary` の `penalty(j, i, …)` の向き（$x_j = 1, x_i = 0$）も合う。表の 6 行の表せる／表せないの判定、確認問題「違うと罰」の辺（$i \to t$・$s \to j$・$j \to i$ の $2c$・定数 $-c$）も正しい
- 反転：$x'_j = 1 - x_j$ で $(A,B,C,D) \to (B,A,D,C)$、不等式の向きが逆になる。反転の表の 3 行も正しい。同じ色どうしの項は両方反転で $(D,C,B,A)$ になり、表せるかは変わらない（本文の注意と矛盾しない）
- 確認問題（3 頂点の閉路）：最小値 1 は正しい
- 多値変数：$y_{k+1} \to y_k$ の ∞、コスト $f(k) - f(k-1)$、値の固定、レベルの条件の辺はどれも正しい。差の 2 乗の辺（$l = k$ で 1、$l < k$ で 2、両向き）を $K = 5$ の全 25 組で数え、切れる容量の和がちょうど $(a-b)^2$ になることを Python で確かめた。kmjp の ABC347 G の記事のコードも同じ容量 1・2 で両向き
- 図 cut-example：本文の 5 つの項から 8 通りを手で計算し（000:5, 001:9, 010:9, 011:12, 100:∞, 101:∞, 110:4, 111:7）、最小 4 と本文・図・代替テキストが一致。最大流 4 の後に $s$ から届くのは $\{s, a, b\}$ で、`min_cut` の復元とも合う
- ACL：`add_edge` の容量 0 以上、`flow` の $O(n^2 m)$、`min_cut` が `flow` の後に $O(n + m)$ で `vector<bool>` を返すことを `~/lib/ac-library-master/document_ja/maxflow.md` で確かめた。残余グラフで $s$ から届く集合は s 側が最小の最小カットなので、落とし穴と確認問題（利益 0 の品物）の記述も正しい
- 例題 typical90_an：drken の記事で $2 \le N \le 100$、条件「家 i に入らずに家 c に入れない」、辺 c → i（∞）を確認。本文の向きと一致
- 例題 abc472_g：drken の Qiita の記事で、操作（左・右・下へ # を通らず届くマス）と「隣接するマスだけ考えれば十分」を確認。執筆者が自分で示した「最終的な # の集合＝閉包」の証明は正しい。H ≤ 3・W ≤ 4 のランダムな 300 盤面で、操作のくり返しで作れる最終状態の全体と閉包の全体が一致することを全探索で確かめた。答えの式「最初の値＋ - の数 − 最小カット」も最大重み閉包の式どおり
- 例題 abc445_g：二部グラフの証明（gcd で割った商の偶奇）は正しい。$0 \le A, B \le 6$（両方 0 は除く）・15×15 の盤面で、すべての移動が色を変えることを確かめた（$A = 0$ も成り立つ）。kmjp の記事も「奇閉路は存在しない」として片側を反転した Project Selection で解いている（記事は色の役割が本文と逆だが同じ構成）。本文のグラフの向き（色 0 に $s \to v$、色 1 に $v \to t$、$u \to w$ の ∞）は正しい
- 練習・力試しの方針（tessoku_book_eo・abc259_g・abc326_g・abc193_f・abc225_g・abc347_g）：本文の早見表と反転・多値変数の節で組める形で、evidence の記事と食い違いなし。abc347_g は kmjp の記事のコードから $N \le 20$ と読める
- 問題 9 件：`tools/ap.py show` で題名と diff（typical90_an なし・abc472_g 2018・abc445_g 2250・tessoku_book_eo なし・abc259_g 2428・abc326_g 2470・abc193_f 2475・abc225_g 2566・abc347_g 2876）が本文と一致。要約に手法名なし
- リンク先：glossary#cut、min-cut・bipartite-graph・konig-theorem・two-sat・min-cost-flow・tree-dp・bit-dp・bit-full-search のページはどれも存在する
- コード：手引き §9 に合う（bits/stdc++.h、マクロ・型の別名なし、`'\n'`）。INF = 2^50 で、builder の検査の範囲（容量 9 程度・辺 100 本未満）では溢れない。closure の core は本文の 3 つの規則と 1 行ずつ対応する
- F8：図の例（a・b・c の 5 項）と確認問題は参考の記事の例の写しではない。早見表の行の並びは drken の早見表と同じ型だが、標準の公式で出典にも挙げている
- 図：catalog の visual は dynamic・priority 3 で、静的な図で代えてよい。白背景・viewBox・font-family="sans-serif"・相対パス。720px で文字の重なり・はみ出しなし、矢印の向きも正しい。代替テキストに切れる辺と値がある

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact F1 | front matter の complexity、要点の計算量、#idea の「計算量」の段落 | 「項 M 個なら頂点も辺も $O(N + M)$」は 2 変数までの項のときだけ正しい。$K$ 変数の利得は 1 項で辺 $K + 1$ 本、多値変数の差の 2 乗は 1 組で $O(K^2)$ 本（本文 #multi-valued で自分で書いている）なので、項の数 $M$ では辺の数を押さえられない | 早見表の最後の 2 行、#multi-valued の最後の段落 | 「項が 2 変数までなら頂点も辺も $O(N + M)$。多くの変数をまとめる項は、その変数の数だけ辺が増える」のように条件を足す（complexity はメインに提案） |
| 2 | 直すとよい | fact F2・clarity U2 | #submodular の第 3 段落の最後の文「補助の頂点を足して最小化しても、2 変数の項としてこの性質は崩れないことが知られている」 | 正しいが根拠も出典もなく、手引きの「よく知られている」で済ませる形になっている（執筆者の未解決の点） | 補助の頂点を含むグラフで表せる関数は劣モジュラであることは、V. Kolmogorov, R. Zabih, "What Energy Functions Can Be Minimized via Graph Cuts?", IEEE TPAMI 26(2), 2004 の必要条件の定理にある | 出典を参考に足すか、「補助の頂点を足しても、補助の頂点について最小をとった関数は劣モジュラのままである（出典）」と書く |
| 3 | 直すとよい | figure G3 | cut-example.svg（幅 360px） | 幅 720 の viewBox を 360px に縮めると文字が 7px 程度になり、辺の意味のラベル（「1：b を選び c を選ばない罰」など）がスマホでかなり読みにくい。重なり・はみ出しはない | render_svg.py の cut-example-360.png を目で確認 | font-size を 15 → 18 程度に上げ、上の説明文と下の 2 行は本文にあるので図から外すか短くする |
| 4 | 直すとよい | clarity U9 | #flip-side の注意の 1 つ目「同じ 2 色の間に「違うと罰」が混ざっていると」、#cheatsheet の後の段落「「同じ」ときの罰」 | 「同じ 2 色の間に」は「同じ色どうし」と読み違えやすい（言いたいのは 2 色をまたぐ項）。「「同じ」ときの罰」は語の脱落 | 本文 216 行・104 行 | 「2 色をまたぐ項に「違うと罰」が混ざっていると」、「「同じ」であるときの罰」にする |

## 執筆者の未解決の点について

- abc472_g・abc445_g・abc225_g・abc347_g の制約：本文に数値を書いていないので問題ない。abc347_g は kmjp のコードから $N \le 20$ と読める（台帳に書くなら別の資料で確かめる）
- abc472_g の閉包の証明：正しい（全探索でも一致）
- abc445_g の二部グラフの証明：正しい。$A$ か $B$ が 0 のときも成り立つ（両方 0 は移動がなく、辺がない）
- 補助の頂点と劣モジュラ性の出典：指摘 2
- 差の 2 乗の辺を $l \le k$ に限ること：正しい（$K = 5$ の全組で確認、kmjp のコードも `j < i` で両向き）
- bipartite-graph の 171 行目「最小カットで表せるのは「2 つが違うとコスト」の形」：誤りではないが「表せるのは〜の形」と限定しているように読める。メインが「「片方だけ 1 のときのコスト」の和で、たとえば「違うとコスト」は表せる」程度に直すとよい（このページの検証の範囲外なので提案にとどめる）

## 台帳への提案

- 執筆者の提案（abc472_g・abc445_g・tessoku_book_eo・abc225_g の summary、abc472_g の title の末尾の空白、abc225_g・abc326_g の approach）に同意
- typical90_an・abc472_g・abc445_g・abc347_g：checked に 2026-10-21（evidence の記事で問いと方針を確かめた）

## 総合の判定

小さな直しで可（直すべき 0・直すとよい 4）。事実・コード・図の値に誤りはなく、直しはどれも 1〜2 文か図の文字の大きさ
