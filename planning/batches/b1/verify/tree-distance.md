# tree-distance の検証（工程8b・b1）

- 対象：docs/tree/tree-distance.md、snippets/tree-distance/（from-one・xor-count の 2 組）、docs/img/tree-distance/two-sources.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/tree-distance.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page tree-distance`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/tree-distance`（2 片・コンパイル 2 回・期待と違う 0）、`npx textlint docs/tree/tree-distance.md`（指摘なし）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- front matter：前の commit（75cd131）との差は complexity・stage と、sections に足した next-steps だけ（§2.1 の範囲）。要点の計算量と complexity は一致。別名の行に aliases の 6 つがすべてある。要点は summary・signs・prerequisites と食い違わない
- 問題：`python3 tools/ap.py show` で 4 問の題名・diff を確かめた（abc070_d 1182・abc148_f 1457・abc201_e 1694・arc045_c 2022（参考値））。台帳・本文と一致し、どれも「確認済み」。例題 1・練習 2・力試し 1 で、並びは易しい順。要約は問いだけで手法名を含まない
- 例題 ABC070 D：drken の記事（evidence）で、K を経由する質問の答えが dist(K, x) + dist(K, y) で、K からの距離を 1 回の DFS で前計算する方針を確かめた。N, Q ≤ 10^5。重みの上限は記事に書かれていない（執筆者の未解決の点）。本文は具体的な上限を書かずに `long long` の理由を一般の形で書いているので、このままでよい
- 練習 ABC148 F：zk_phi の記事で、逃げる側が先に動くこと、$d_u(x) < d_v(x)$ を満たす $x$ のうち $d_v(x)$ が最大の頂点へ逃げ、答えが $d_v(x) - 1$ であることを確かめた。本文の方針と一致する。hamayan の記事は葉と LCA で判定する別の筋だが、「鬼の動きは決まっていて逃げる側の行き先だけを探す」という参考の書き方とは合う
- 練習 ABC201 E：hamayan・kanpurin の記事で、根からの XOR と bit ごとの 0 と 1 の個数の積で数えることを確かめた（N ≤ 2×10^5、重み < 2^60）。法の値はどちらの記事にも数字では書かれていない（hamayan は mint を使う）。本文は「問題の指定どおりに余りを取る」で値を書かないので、このままでよい（執筆者の未解決の点）
- 力試し ARC045 C：drken の記事で、根からの XOR、`map` で $S[v] \oplus X$ の個数を数えること、順序なしの組で数えて X = 0 のとき自分自身を引き 2 で割ることを確かめた。本文の「前に見た頂点とだけ組にする」数え方と同じ数になる
- 参考：6 件の URL を開き、題名・著者・内容が書かれたとおりであることを確かめた。どれも付録 B のドメイン
- 自分で導かれた主張の確かめ（作業用の場所のプログラム）：
    - 重み 1〜4 の乱数の木 20000 個で、$\{x : d_a(x) < d_b(x)\}$ が $a$ を含んで連結であることを確かめた（不一致 0）
    - 確認問題「等しい頂点がない木」の理屈（差が $2 d_a(p) - d(a, b)$）、パスの上の判定と重み 0 の辺の落とし穴、和の偶奇が LCA なしで決まること、最大値が累積で表せないこと：どれも正しい
    - 重み −5〜5 の乱数の木 20000 個で、「直径の両端からの距離 2 回分で全頂点の最遠距離が求まる」が 10029 個で成り立たなかった（指摘 1）
- コード片：from-one.cpp の core は本文（親を持つスタック、親へ戻らない、$\mathrm{dist}[c] = \mathrm{dist}[v] + w$、−1 の印を使わない）と 1 行ずつ対応する。cases は 1 頂点・負の重み・10^9 の重みで int を超える距離・枝分かれを含む。xor-count.cpp の core は BFS 順で $S$ を配り、前に見た頂点とだけ組にする。cases は 1 頂点・X = 0・重み 0 で全組・該当なしを含み、`assert` で組の数の上限を見る。§9 の書き方（bits・using namespace・マクロなし・`'\n'`・構造化束縛）に合う
- リンク：dijkstra#negative-edges・lca#distance・lca#path-aggregate・bitwise-independence#per-bit-contribution・tree-traversal#recursion-depth はどれも draft で見出しがある。節へのリンクのない tree-path は stub だが、ページへのリンクなので §13-4 のとおりでよい
- 図：Windows の Chrome（headless=new）で two-sources.svg を等倍（640×400）と、幅 390px の画面に幅 358px で（2 倍密度、暗い背景の上に）画像にして目で確かめた。背景は白で塗られ、`viewBox` があり、文字はテキストのまま。近い側は塗り（青・灰・橙）と枠線の種類（実線・細かい点線・点線）の両方で分けている。各頂点の $(d_a, d_b)$ の 9 組を手で数え直して一致し、代替テキスト・本文（$p(6) = 1$、中点 2 と 7 で等しい、$d(a, b) = 4$）とも一致する。catalog の visual（static・priority 2）を満たす

## 指摘

### 1｜直すべき｜fact（F2）｜#next-steps の「各頂点から最も遠い点」

- **問題**：「木の直径の両端からの距離 2 回分で全頂点の最遠距離が求まる」は、重みが非負のときだけ成り立つ。このページは #from-one で「負の重みがあっても正しく求まる」と強調しているので、読者は負の重みでも使えると受け取りやすい
- **根拠**：重み −5〜5 の乱数の木（頂点 2〜8）20000 個で、頂点 0 から最遠の $u$、$u$ から最遠の $v$ を取り、全頂点で $\max_y d(x, y) = \max(d(u, x), d(v, x))$ かを比べると、10029 個で成り立たなかった。重み 1 以上では成り立つ（直径の 2 回探索の証明が非負を使う）
- **直し方**：「重みが非負なら、すべての点から探索しなくても…」と条件を足す

### 2｜直すとよい｜figure（G5）｜two-sources.svg の頂点 2 の上のラベル

- **問題**：「パスの中点」の縦の破線（x = 310）が、頂点 2 のラベル「(2, 2)」の真ん中を通り、「(2,¦2)」のように読みにくい
- **根拠**：等倍とスマホ幅の画像で、破線がラベルのカンマと 2 の間に重なって見える
- **直し方**：破線の始点を y = 92 程度に下げる（ラベルの下から引く）か、頂点 2・7 のラベルを右へずらす。ほかの位置・値は直さなくてよい

### 3｜直すとよい｜clarity（U6）｜#pitfalls の「パス状の木で再帰が深くなる」

- **問題**：「上のコードのように明示的なスタックか BFS 順で書けば起きない」の「上のコード」は #from-one のコードで、落とし穴の節だけを読むと何を指すか分からない（§3「上の図」「前述の」に頼らない）
- **直し方**：「[1 点からの距離](#from-one)のコードのように明示的なスタックで書くか、BFS 順で書けば起きない」とする

## 提案（メインへ）

- 台帳の `checked`：abc070_d・abc201_e・arc045_c に 2026-10-21 を入れる（上の記事で問いと方針を確かめた）
- 執筆者の台帳への提案（abc148_f の evidence に zk_phi を足す・approach の書き直し、abc201_e の evidence に kanpurin を足す）は妥当。abc148_f の hamayan の記事は葉と LCA で判定する解き方で、ページの方針の裏付けは zk_phi の記事が適する
- 手引きへの提案（基礎の「上位の手法とのつながり」の定型の見出しと anchor）は、ほかの基礎のページとそろえるために決めておくとよい

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 2）。
