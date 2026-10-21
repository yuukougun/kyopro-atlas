# segment-tree-binary-search の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/segment-tree-binary-search.md、snippets/segment-tree-binary-search/{first-at-least,kth-one,own-max-right,lazy-monotone}.{cpp,yaml}、docs/img/segment-tree-binary-search/climb-descend.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は見出しを短くしたので title を合わせ（anchor・level は不変）、節「条件の書き方の型（初めて x 以上・和が w 以下・mex）」（anchor: predicate-patterns、level 水）を足した
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（4 件すべて一致）、textlint（エラー 0、警告 33。大半は数式の半開区間 [l, r) の括弧の対応・数式を含む文の長さ・助詞の重複の誤検出）
- 図：動く図は作らず、静的な SVG（登る段階と降りる段階、和の木で max_right(1, x ≤ 12) → r = 5）で代えた。catalog の visual は priority 2 なので、後で動く図を作るなら同じ例（列 3 1 4 1 5 9 2 6、l = 1、f(x) = x ≤ 12）を使うとよい
- 新しく noai を確かめたドメイン：blog.nishigake.net（指定なし）、yuulis.hatenablog.com（指定なし）、inthebloom.github.io（指定なし。ただし本文は読んでいないので参考には入れていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc478_f | summary | 頂点 1 を根とする木のうち、決められた規則の探索で頂点を訪れる順が与えられた順列になるものの個数を、998244353 で割った余りで求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/1003_abc478 （解法の部分）、https://merom686.hatenablog.com/entry/2026/10/04/013441 |
| abc478_f | alternatives（segment-tree-binary-search）の approach | 各頂点の親になれる範囲の左端（自分より前で最も近い、自分より大きい値の直後）を max のセグ木の min_left で求め、範囲の長さの積を取る（単調スタックでもよい） | ikatakos 氏の記録のコードが min_left を使う |
| abc330_e | 確認 | 本文の方針は「値 0〜N の個数の min のセグ木で max_right(0, c > 0)」。drken 氏の記事の 3 通りの解法の 1 つと一致 | https://drken1215.hatenablog.com/entry/2023/11/26/233800 |
| abc382_c | 確認 | approach の「min のセグ木で、条件を満たす最左の客を max_right で探す」は述語が「prod > B_j」であることを確かめた | https://qiita.com/hibit/items/e0ed4e6d2604ff6cec49 |

## 用語集への提案

- 総積｜total-product｜セグメント木で、区間の要素を結合法則を満たす演算で左から順に結んだ値。和の木なら和、max の木なら最大値。空の区間では単位元（本文ではリンクしていない。用語集にあれば最初の出現にリンクを足したい）

## 手引きへの提案

- §13-1 の定型の節（落とし穴 {#pitfalls}・使い分け）が、骨格の sections に「落とし穴（…） anchor: pitfalls」「使い分け（…） anchor: choosing」として載っているページがある（このページ）。今回は sections に従い、見出しを sections の title と同じにした。定型の節を sections に残すか外すかを決めておくとよい
- ds の「保つ性質・各操作の手順・境界」の 3 小見出しは、データ構造そのもののページ向けで、このような技法のページでは「なぜ正しいか（保つ性質）」「再帰で書くとき」「境界」の節に分けて書いた。技法のページでの扱いを明記するとよい

## 問題の補充の候補

- abc371_f（F. Takahashi in Narrow Road、diff 2109）：一列に並ぶ人を順に目的地へ動かすときの総移動回数を求める。X_i − i に直した単調な列に区間代入し、影響範囲を遅延セグ木上の二分探索で求める。青の節（on-lazy-segment-tree）の練習か力試しの候補。裏付け：research/05-ds §（ikatakos 氏 https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0914_abc371 。ただし今回は開いていない。採るなら解法の部分で確かめる）
- 例題の位置の目安（水＝E）に合う abc319 以降の E が例題にない（例題は C・practice・F）。abc330_e（diff 1004）は練習に置いたが、ordered-set・interval-set でも練習なので、例題に上げるかは台帳の持ち主の決定に従う

## 未解決の点

- abc307_f の方針は drken 氏の記事の要約に頼った（翌日以降で初めて X_d が辺の長さ以上になる日を max の木で探す）。日ごとの上限が「その日に進める距離の合計の上限」であることは記事の要約から読んだもので、本文には細部を書いていない
- abc478_f の「自分より大きい値」は頂点番号の大小で、訪問順の規則（Min-First Search）の中身は問題文を見ていないので本文に書いていない
- 静的な SVG はレンダラがなく目視で確かめていない（座標は計算で配置した）。検証役に表示の確認を頼みたい
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 8 回

## 検証の指摘への対応（verify/segment-tree-binary-search.md）

- 直すべき 1〜4、直すとよい 5〜12 をすべて直した。採らなかったものはない
    - 1：sections から「使い分け」「落とし穴」の 2 行を消し、見出しを `## 落とし穴 {#pitfalls}`・`## 使い分け {#comparison}` にした（§13.1）。anchor が choosing から comparison に変わる。本文からの参照はないが、生成物 docs/index/ds.md 404 行に `segment-tree-binary-search#choosing` があるので、gen_site.py の再実行で更新されたい（§2.1 の「既存の anchor は変えない」との関係はメインの判断に任せる。fenwick-tree・monotonic-stack は `anchor: choosing` を sections に残しており、ページ間で揃っていない）
    - 2：例を「min の単位元を `INT_MAX` にした `int` の木で $f(v) = (v + 1 \le x)$」にした
    - 3：ABC478 F の親の範囲を「最も近い大きい値の位置から自分の直前まで（なければ前のすべて）、その位置は `min_left` の返り値の 1 つ左」にした
    - 4：副作用の理由を segtree.hpp の手順（`assert(f(e()))` の 1 回とノードの累積ごと）に合わせた
    - 7：単位元の条件を「すべての $A_i$ と $V$ より小さい値、値が 0 以上なので −1」にした。値が 0 以上であることは drken 氏の記事のコードの −1 に拠る。問題文の制約での確かめはメインに頼みたい
    - 8：本文と kth-one.cpp のコメントに「閉区間」と明記した
    - 12：区間のラベルの font-size を 11 から 12.5 にした（葉の幅に収まる）。代替テキストを「葉 [1, 2) とノード [2, 4)」にした
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（4 片・期待と違う 0）、textlint（エラー 0・警告 34）

## 台帳への提案（訂正）

- 上の表の abc478_f の approach は誤りなので、次に差し替える：「各頂点の親になれる範囲（自分より前で最も近い、自分より大きい値の位置から自分の直前まで。なければ前のすべて）の左端を max のセグ木の min_left の返り値の 1 つ左として求め、範囲の長さの積を取る（単調スタックでもよい）」
- `checked`：practice2_j・abc307_f・abc478_f に 2026-10-21（abc478_f は指摘 3 を直したので検証役の条件を満たす）
