# counting-labeled-graphs の報告（b3・執筆）

- 書いたファイル：docs/comb/counting-labeled-graphs.md、snippets/counting-labeled-graphs/{connected-count,subset-connected,farthest-layers}.{cpp,yaml}、docs/img/counting-labeled-graphs/{component-of-1,bfs-layers}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の並びを本文の順に入れ替えた（by-size を subset-dp の前へ。anchor・title は変えていない）
- 検査の結果：check_pages エラー0・警告0。fix_problems --check 直す行0。check_snippets 3 本とも期待どおり。textlint エラー0・警告5（数式を含む文の長さと読点の数、台帳の要約の行の「で」の重なり。誤検出として残した）
- 図：SVG 2 枚を render_svg.py で 360px・720px の PNG にして目で確かめた（component-of-1 は成分の間の「×」の文字が枠と重なったので、枠を狭めて直した）
- 使った出典：drken の ABC281 G・ABC180 F・ABC213 G の記事（どれも evidence の URL。付録 B の drken1215.hatenablog.com）。新しく noai を確かめたドメインはない（kmjp.hatenablog.jp の記事は付録 B にあり、check_noai でも指定なし）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc180_f | summary（本体と alternatives の 2 つ） | 自己ループのない（多重辺は許す）N 頂点 M 辺の無向グラフで、各連結成分がパスかサイクルで、最大の連結成分の頂点数がちょうど L のものの数を求める。 | https://drken1215.hatenablog.com/entry/2020/10/21/145700（「多重辺はアリ」で、大きさ 2 のサイクルを二重辺として数える）。b2 の counting-dedup の検証の提案と同じ。本文の行は §14-15 により先に直した |
| abc180_f・abc213_g | checked | 2026-10-21 | 上の記事と https://drken1215.hatenablog.com/entry/2021/08/12/132500 で問いを確かめた |
| abc281_g | alternatives（counting-labeled-graphs）の approach | 頂点 1 からの距離の層ごとに頂点を配り、層の大きさを状態にした DP。頂点 N だけの層を最後に置き、二項係数はパスカルの三角形で作る | 本文の方針に合わせる（任意） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| ラベル付きグラフ | labeled-graph | 頂点に番号（ラベル）が付いていて、番号の付け方が違えば形が同じでも別のものとして数えるグラフ。競プロの「N 頂点のグラフの数」はふつうこれを数える |

本文では用語集へのリンクを張っていない（語は導入の 1 文で説明した）。足すなら導入の「頂点に番号の付いたグラフ」をリンクにできる。

## 手引きへの提案

- §5 comb に「連結なものを全体から引くときは、頂点 1（最小の頂点）を含む成分の外を『全体』の数で掛ける（連結なものの数で掛けると成分がちょうど 2 つのものしか引かれない）」を足すとよい。counting-dedup・subset-enumeration-dp・inclusion-exclusion-dp でも同じ形が出る

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc389_g（G. Odd Even Graph、diff 2762） | 素数 P と N について、辺の数 M ごとに、頂点 1 からの距離が偶数の頂点と奇数の頂点の数が等しい N 頂点の連結な単純無向グラフの数を P で割った余りで求める。距離の層ごとに頂点を配り、層の大きさ・偶奇の差・辺の数を状態にする DP | https://kmjp.hatenablog.jp/entry/2025/01/19/1000 |

- 役割は力試し（#bfs-layers の応用）を提案する。発展の帯なので、黄のページの力試しとして置くかはメインの判断に任せる
- ほかに ABC253 Ex（We Love Forest、diff 2758。頂点集合ごとの全域木の数から森を組み立てる）、ABC327 G（Many Good Tuple Problems、diff 2968。連結な二部グラフを全体から引く）が型に合うが、第三者の解説の本文を確かめられなかったので候補に入れていない

## 未解決の点

- abc180_f の頂点は区別するもの（番号付き）として数える前提で書いた。drken の記事は明示していないが、二項係数で頂点を選ぶ式からそう読める
- drken の ABC281 G の記事は頂点 N から逆向きに層を作る形だが、本文は頂点 1 から前向きに層を作り、最後に頂点 N を置く形にした（全探索で N ≤ 6 を確かめた）
- 練習は abc180_f の 1 問だけで、目安（2〜6）に届かない。黄の帯で確認済みの問題が台帳に見つからなかった
- 使い分けの表で stub の matrix-tree-theorem・cayley-pruefer・zeta-mobius-subset にページへリンクした（anchor なし）
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 9 回（WebFetch 6・WebSearch 3）

## 検証の指摘への対応（直し）

- 1（直すべき）：#by-size の応用の型を 2 つに分けた。森は逆向きの $a(n)$ に $h(k) = k^{k-2}$（cayley-pruefer#cayley へリンク）、連結な二部グラフは 2 色に塗ったグラフ $b(n)$ を全体にして引き、最後に 2 で割る手順を書いた
- 2：#bfs-layers に「$R = N - 1$ なら $\sum_j \mathrm{dp}[R][j] = c(N)$（$N = 4$ で 38）」を足した
- 3：「端子」を「各頂点の端点を 2 つずつ組にして辺にする」と書き、$f(S) = (2m-1)!!$ を示した
- 4：bfs-layers.svg の頂点 7 の赤い太枠をほかの頂点と同じ色・太さにした
- 5：リンクの文字を「頂点 1 の成分で分類する節」にした
- 6：#component-of-1 の段落は理由だけ、落とし穴は確認問題へのリンクにし、値 5・41 は確認問題の答えにだけ置いた
- 7（採らない）：練習を増やすかはメインの判断（指摘のとおり）。候補 abc389_g は上の「問題の補充の候補」のとおり力試し向き
- 8：cayley-pruefer へのリンクのうち #by-size の応用の型は #cayley に張った。使い分けの表の cayley-pruefer・zeta-mobius-subset・matrix-tree-theorem の張り替えはメインに任せる（手引き §14-23）。#subset-dp の最小の頂点を代表にする文に subset-enumeration-dp#fix-minimum へのリンクを足した

## 台帳への提案（検証を受けて）

- abc180_f の summary（本体と alternatives）：検証の「台帳への提案」の文に賛成
- abc180_f・abc213_g の checked：2026-10-21（検証が drken の記事で問いと制約を確かめた）
