# bottleneck-path の報告（b2）

- 書いたファイル：docs/graph/bottleneck-path.md、snippets/bottleneck-path/{pair,many-queries,matching}.{cpp,yaml}、docs/img/bottleneck-path/graph.svg、docs/img/bottleneck-path/reconstruction-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（4 節とも見出しと title が同じ）
- 構成：level が青なので §4 の technique（水・青・黄）。必要になる場面・処理の流れ・計算量は why-mst・kruskal-order の中で兼ねた（§14-5）。応用の型は kruskal-order の末尾（§14-7）。黄の節 many-queries は冒頭でマージテク（small-to-large#relabel-smaller）、発展の節 reconstruction-tree は LCA と merge-process-tree を前提として示した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0（3 本）、textlint エラー 0・警告 3（要点の囲み・図の代替テキスト・折りたたみの中の文の長さ。§14-25 の誤検出として残した）
- コード片の確かめ：many-queries.cpp と matching.cpp は main で素朴な方法（しきい値ごとの連結判定・B の並べ方の全探索）と assert で比べる。手元で乱択の 300 ケースずつを流し、どちらも一致した
- 図：graph.svg（5 頂点のグラフ、最小全域木の辺を実線、使われない辺を破線）と reconstruction-tree.svg（同じグラフの併合過程の木、LCA(1, 4) を太線で強調）。visual は priority 2 の static なので静的な図にした。初めは 1 枚に並べたが 360px で文字が小さすぎたので 2 枚に分けた。render_svg.py で 360px・720px を目で確かめた。動く図の置き場は置いていない

## 使った出典

- https://www.cnblogs.com/Lanly/p/18606772：例題 abc383_e（f の定義、併合のたびに成分の A と B の残りの数から組を作る方針）
- https://drken1215.hatenablog.com/entry/2020/11/02/013900：練習 abc181_f（N ≤ 100、壁を頂点にする、二分探索をせず距離の順に併合して上下がつながった距離の半分が答え）
- https://kmjp.hatenablog.jp/entry/2025/02/24/1000：練習 abc394_g（答えの式 h < min(Y, Z) なら Y + Z − 2h、そうでなければ |Y − Z|。高い順に併合し、成分のクエリの集合を小さい方から移す）
- https://github.com/atcoder/ac-library/blob/master/document_ja/dsu.md：ACL の囲み
- 新しく noai を確かめたドメイン：なし（すべて付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc383_e | checked | 2026-10-21 | evidence の Lanly の記事で、問い（f の定義と B の並べ替え）と方針を確かめた |
| abc214_d | pages に追加（任意） | {id: bottleneck-path, role: practice}。summary は既存のまま | 本文の応用の型「全点対の和」で union-find-applications の例題の小見出しへリンクした。木の上のパスの最大は最小ボトルネックそのもので、練習に置ける（diff 1341 なので青のページには易しめ）。根拠は既存の evidence（hamayan） |

## 用語集への提案

- ボトルネック｜bottleneck｜経路が通る辺の重みの最大値である。これを最小にする経路を最小ボトルネック路と呼ぶ。最小値を最大にする向きで使うこともある。（本文では why-mst の最初で太字で定義し、リンクは張っていない）

## 手引きへの提案

- 横に 2 つの図を並べた SVG（幅 760 程度）は、360px で文字が 6px ほどになり読めない。§8 に「並べたい図は 2 枚の SVG に分ける（1 枚の幅は 400 程度まで）」を足すとよい

## 問題の補充の候補

- abc214_d（ABC214 D. Sum of Maximum Weights、diff 1341）：重み付きの木の全頂点対のパス上の最大の辺の和。併合のたびに重み × 両側の頂点数を足す。台帳で確認済み（https://blog.hamayanhamayan.com/entry/2021/08/15/034729）。上の台帳への提案のとおり
- abc235_h（ABC235 Ex. Painting Weighted Graph、diff 2967）：同じ重みの辺で成分がまとまる過程（併合過程の木を同じ重みでまとめたもの）で塗り方を数える。research/03 の候補で、裏付けは https://kmjp.hatenablog.jp/entry/2022/01/17/0930 とされるが、私は記事を読んでいない。難しすぎるので、載せるなら merge-process-tree の力試し向き
- 青の帯の水準（E の難しい問題・F）で、ボトルネックをそのまま問う abc319 以降の問題は見つけられなかった（ap.py の題名の検索では手がかりがない）。frequency_evidence の「recent 0」と合う

## 未解決の点

1. abc383_e で A_i ≠ B_j が保証されるか、N・M・K の制約は確かめられなかった（Lanly の記事に制約の記述がない）。本文と matching.cpp は、同じ頂点の A と B を重み 0 で組にして、保証がなくても正しい形にした。全員を組にできる（連結である）前提で書いた
2. handoff §1 の 3 か所（minimum-spanning-tree:214・minimum-spanning-tree:288・union-find-connectivity:159）は、それぞれ #why-mst（:214・:288）と #kruskal-order（:159）へ張り替えられる
3. merge-process-tree・parallel-binary-search・partially-persistent-union-find は stub なので anchor を付けずにページへリンクした（§14-23）。merge-process-tree が draft になったら、reconstruction-tree の節から #bottleneck・#group-as-interval へ張り替えられる
4. reconstruction-tree の節は発展の概要として、作り方・LCA の重み・行ける範囲が DFS 順の区間になることだけを書き、証明とコードは merge-process-tree に任せた。merge-process-tree の bottleneck の節と内容が重なるので、持ち主をどちらにするかはメインが決める
5. 例題の位置の目安（青＝F と難しい E）に対し、例題 abc383_e は diff 1616 の E で合う。練習の 2 問はどちらも diff 2000 を超え（黄の帯）、青のページの練習としては難しい

## 使用量の目安

- 道具の呼び出し 約 40 回、Web 取得 5 回（うち 1 回は別の記事で空振り）、検索 1 回

## 検証の指摘への対応

- 1（直すべき）：front matter の complexity を `Q 組はオフラインで O(M log M + Q log N α(N))` にし、要点・本文とそろえた。
- 2：解法の詳細の最初に、同じ頂点の A と B を重み 0 で先に組にする 1 文を足した。
- 3：残りの数の記号を $p, q$ に変え、1 段落目を「残りの数を求める」「min 組を作って足す」の 2 文に分けた。
- 4：ACL の囲みに `d.leader(a)` を足した（size は残した）。参考の ACL の行にも leader を足した。
- 5：「カットを渡る辺」を用語集に合わせて「カットを横切る辺」にした。
- 6：見出しと sections の title を「クラスカル法の順に成分を併合しながら答える」にした（anchor は kruskal-order のまま）。front matter の summary の「Kruskal 法」も「クラスカル法」にした。
- 7：参考の「~Lanly~」を「Lanly」にした。
- 8：本文の箇条書きと番号付きの手順の各行を句点で終えた。要点の囲みと参考の行は手引きの見本どおり句点なしのまま。
- 採らなかったもの：なし。
