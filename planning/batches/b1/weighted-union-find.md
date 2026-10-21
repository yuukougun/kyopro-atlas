# weighted-union-find の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/weighted-union-find.md、snippets/weighted-union-find/{weighted-union-find,parity}.{cpp,yaml}、docs/img/weighted-union-find/{compression,merge}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は §13.2 に従い見出しと同じ短い title に直し、節を 4 つ足した（idea・boundaries・complexity・applications）。既存の anchor（invariants・operations・consistency・generalization・choosing・pitfalls）は変えていない。invariants の title は `[v]` を含むので引用符で囲んだ
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件すべて一致）、textlint（エラー 0・警告 6）
  - 残した警告：41 行の sentence-length（要点の囲みの「いつ使うか」の入れ子の箇条書きを 1 文と数える誤検出）、94 行の sentence-length（図の代替テキスト）、205 行の sentence-length（確認問題の題の数式）、135・190・191 行の no-doubled-joshi（数式 $u$・$v + N$ などの間の「と」「に」で、言い換えると読みにくくなる）
- 動く図：作っていない（visual は static・priority 2）。静的な SVG 2 枚（経路圧縮の前後・merge の前後）で代えた
- 使った出典：drken の Qiita（重み付き Union-Find のまとめ）、drken のはてなブログ 7 本（arc090_b・abc328_f・abc373_d・abc327_d・abc280_f・arc188_c）、enakai00 のはてなブログ（typical90_bp）、ikatakos 氏の記録（abc451_f。解法の節だけ）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc451_f | pages の weighted-union-find の alternatives.approach | 「（research/00 §2.3.8 の分類）」を消し、「偶奇の Union-Find の根に、根と同じ色・違う色の数を持たせ、成分ごとに少ない方を黒にする」にする（制作メモが approach に残っている） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0328_abc451 |
| arc090_b | evidence の解説の題名 | 記録の補足として、drken 氏の記事の題名は「ABC 087 D (ARC 090 D)」で、ABC087 D と同じ問題であることを note に残すとよい（abc087_d を台帳に別に持つなら重複の扱いを決めてほしい） | https://drken1215.hatenablog.com/entry/2022/12/08/152700 |

ほかの使った問題（abc328_f・abc327_d・abc373_d・abc280_f・typical90_bp・arc188_c）の summary と approach は、evidence の解説と食い違いがなかった。abc328_f の条件は $x_a - x_b = d$ の向き（本文の merge の約束と逆）であることを解説で確かめ、本文の解法の詳細と落とし穴に書いた。

## 用語集への提案

- ポテンシャル｜potential｜各要素に割り当てた値で、2 要素の差だけが意味を持つもの。重み付き Union-Find では「成分の根との差」、最短路では各頂点に割り当てて辺の重みを付け替える値を指す（本文の最初の出現から `../guide/glossary.md#potential` でリンクした）

## 手引きへの提案

- §4 の technique の目安に「ACL では」があるが、ACL に対応がない手法（`acl: []`）での扱いが決まっていない。今回は「`dsu` は差を持てないので自作する。偶奇だけなら頂点を 2 倍にして `dsu` が使える」という囲みを、手順の節のコードの直後に置いた（見出しは立てていない）。定型の見出しにするか、対応のない手法では省くかを決めてほしい
- §13.1 の定型の節のうち「使い分け」の anchor は comparison だが、骨格の sections には `anchor: choosing` が入っている（このページと lazy-segment-tree）。既存の anchor は変えない規則に従い choosing のままにした。どちらにそろえるかメインで決めてほしい

## 問題の補充の候補

- 確認済みの問題は例題 2・練習 5・力試し 1 で、目安を満たすので新しい候補は探していない
- abc319 以降の問題は abc328_f（例題）と abc451_f（練習）の 2 問で、水のページの要件（1 問以上）を満たす

## 未解決の点

- SVG 2 枚は描画して目で確かめる道具（rsvg-convert・cairosvg・ブラウザ）が手元になく、XML として読めることと座標の計算だけを確かめた。ラベルと矢印の重なりの確認を検証役に頼みたい
- 「経路圧縮だけ、または union by size だけでも、ならし $O(\log N)$」「$\alpha$ は実用上 4 以下」は記憶に基づく（Union-Find のページと同じ内容になるはず）。union-find のページが draft になったら、計算量の節（`../ds/union-find.md#complexity`）へのリンクに置き換えるとよい
- 一般化の節で Library Checker の Unionfind with Potential（Non-Commutative Group）に触れたが、judge.yosupo.jp の問題ページは開いていない。題名と内容（可換でない演算のポテンシャル）は front matter の verify の id から書いた。確認を検証役に頼みたい
- 前提の union-find・関連の bipartite-graph・difference-constraints・dfs・union-find-applications・small-to-large はどれも stub なので、節へのリンクは張らずページへのリンクだけにした

## 検証の指摘への対応

- 直した：指摘 1（乱数の試験を $n \le 40$・質問 80 回に広げた）、指摘 2（compression.svg の左右の題をそれぞれ 2 行に分け、右の題を x = 370 に移した。中身が空の text 3 つを消した）、指摘 4（結合法則の説明を「どこで区切ってまとめても同じ」に直した）、指摘 5（$M$ を定義し、$Q$ を「情報と質問を合わせた数」とした）、指摘 6（Library Checker の問題が $2 \times 2$ 行列の積であることを書いた）、指摘 7（merge.svg の題の添字を tspan の下付きにした）
- 採らなかった：指摘 3（`#potential` のリンク）は用語集が共有ファイルで執筆者は書けないため、リンクは残した。上の「用語集への提案」のポテンシャルをメインがバッチの終わりに用語集へ足してほしい（足さない場合はリンクを外す必要がある）
- 再検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件一致）、textlint（エラー 0・警告 6。前と同じ箇所）
