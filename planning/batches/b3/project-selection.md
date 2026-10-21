# project-selection（燃やす埋める）の報告と提案

- 書いたファイル：docs/graph/project-selection.md、snippets/project-selection/{builder,closure}.{cpp,yaml}、docs/img/project-selection/cut-example.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の先頭に `{title: 0/1 の選択を s 側と t 側に対応させる, anchor: idea}` を足した（約束・図・処理の流れ・計算量・ACL の囲みを置く節）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（2 片とも一致。builder は乱数で 2^n の全探索と照合）、textlint（エラー 0・警告 21。助詞の重なり・読点の数・数式や問題の行を含む文の長さ）
- 図：cut-example.svg を render_svg.py で 360px・720px にして目で確かめた。動く図（visual priority 3）は作らず、静的な図で代えた
- 新しく noai を確かめたドメイン：なし（qiita.com・drken1215・kmjp・ikatakos・github.com は付録 B にある）。ikatakos の abc472 の記事は 503 で読めず、abc472_g は drken の Qiita の記事で確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc472_g | summary | +・-・# の盤面で、# でないマスと、そこから # を通らずに左右と下へ進んで届くマスを # に変える操作を何度でも行い、+ の数から - の数を引いた値を最大化する。 | https://qiita.com/drken/items/52aafd8c073b37749539 |
| abc472_g | title | 末尾の空白を取る（'Cascading Grid ' → 'Cascading Grid'）。fix_problems の label は空白なしになっている | ap.py show abc472_g |
| abc445_g | summary | 一部のマスが使えない N × N の盤面に、縦横に (A, B) か (B, A) 離れた 2 マスの両方には置けない駒を最も多く置き、置き方を 1 つ出力する。 | https://kmjp.hatenablog.jp/entry/2026/02/14/1030 |
| abc445_g | alternatives（konig-theorem）の summary | 上と同じ | 同上 |
| tessoku_book_eo | summary | 各駅を急行の停車駅にするかを選ぶ。停車駅にすると利益（負もある）が得られ、「駅 A を停車駅にするなら駅 B も停車駅にする」という条件がいくつかあるとき、利益の合計の最大値を求める。 | https://qiita.com/drken/items/52aafd8c073b37749539 |
| abc225_g | summary | マス目からいくつかのマスを選んで × 印を描き、選んだマスの値の和から、斜めに続く線を 1 本と数えた線の本数の C 倍を引いた値を最大化する。 | https://kmjp.hatenablog.jp/entry/2021/11/01/0900 |
| abc225_g | approach | 選んだマスの左上（右上）が選ばれていなければ線が始まるので、「選び、左上を選ばないと罰 C」を辺にする | 同上 |
| abc326_g | approach | （補足）レベルごとの頂点を並べた最大重み閉包にする | https://kmjp.hatenablog.jp/entry/2023/10/28/1100 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 劣モジュラ | submodular | 2 つの 0/1 変数の関数 $\theta$ が $\theta(0,1) + \theta(1,0) \ge \theta(0,0) + \theta(1,1)$ を満たすことである。最小カットで表せる 2 変数の項は、ちょうどこの形である（燃やす埋めるへのリンク）。 |
| 閉包（依存関係） | closure | 「a を選ぶなら b も選ぶ」という条件をすべて満たす集合である。利益の和が最大の閉包は最小カットで求まる（project-selection#closure）。 |

本文では「劣モジュラ」を用語集にリンクせず、節の中で定義した。用語集に足したら、最初の出現からリンクしてよい。

## 手引きへの提案

- §5 graph に「燃やす埋めるの約束は s 側＝選ぶ（x = 1）にそろえる」を足す。解説によって約束が逆で、min-cut・konig-theorem・two-sat・bipartite-graph などのページで向きが混ざると読者が混乱する。bipartite-graph の 171 行目の「最小カットで表せるのは『2 つが違うとコスト』の形」は、正しくは「片方だけ 1 のときのコスト（向きのある罰）」とその和なので、検証の際に確かめてほしい（違うと罰は表せるので誤りではない）

## 問題の補充の候補

数は目安（例題 3・練習 4・力試し 2）を満たしているので、補充の候補は出さない。

## 未解決の点

- abc472_g・abc445_g・abc225_g・abc347_g の制約（H・W・N の上限）は、読んだ解説に数値がなく確かめていない。本文には数値を書かず、頂点と辺の数の目安だけを書いた
- abc472_g の「最終的に # になる集合＝閉包」の証明は、drken の記事では「隣接するマスだけ考えれば十分」とだけ書かれているので、自分で示した（解法の詳細の折りたたみ）。検証役に確かめてほしい
- abc445_g の二部グラフの証明は kmjp の記事の場合分けを、座標を gcd で割った商の偶奇で書き直した。A と B の一方が 0 の場合も同じ議論で成り立つと考えたが、問題の制約は確かめていない
- 「補助の頂点を足しても 2 変数の項として劣モジュラ性は崩れない」は既知の事実（部分的な最小化は劣モジュラ性を保つ）として出典なしで書いた。出典が要るなら探す
- 差の凸関数（多値変数の 2 乗の差）の一般論は書かず、kmjp の記事の容量 1・2 の辺を、$l \le k$ の向きに限ることを自分で確かめて書いた（記事の要約では向きの制限が読み取れなかった）
- min-cut・max-flow・konig-theorem・two-sat は stub なので、節の anchor を付けずにページへリンクした。draft になったら、`../graph/min-cut.md#restore` などへ張り替えられる

## 検証の指摘への対応（b3）

- 指摘 1（計算量）：要点と #idea の計算量に「2 変数までの項なら」の条件と、多くの変数をまとめる項・多値変数の差の 2 乗では辺が増えることを足した。front matter の complexity は検証の提案どおりメインに任せる（提案：「最大流 1 回。変数 N 個・2 変数までの項 M 個で頂点・辺は O(N + M)（多くの変数をまとめる項は変数の数だけ辺が増える）。ACL の mf_graph の上限は頂点 V・辺 E で O(V^2 E)（実際はずっと速い）」）
- 指摘 2（補助の頂点と劣モジュラ性）：「補助の頂点について最小をとった関数は劣モジュラのままである」と書き直し、参考に Kolmogorov・Zabih（IEEE TPAMI 26(2), 2004）を足した
- 指摘 3（図の文字）：上の説明文と下の 2 行（本文と代替テキストにある）を図から外して viewBox を詰め、文字を 15 → 19、辺のラベルを 14 → 17 にした。render_svg.py の 720px で重なりがないことを確かめた
- 指摘 4（語）：「2 色をまたぐ項に」「「同じ」であるときの罰」に直した
- 採らなかったもの：なし
