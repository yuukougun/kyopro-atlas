# tree-dp の報告と提案（工程8b・b1）

- 書いたファイル：docs/dp/tree-dp.md、snippets/tree-dp/{postorder,independent-set,reroot-difference,greedy-children}.{cpp,yaml}、docs/img/tree-dp/{independent-set,reroot-difference}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: パスを最も浅い頂点で数える（子の上位 2 つ）, anchor: path-at-top}` を vertex-states の後に足した（level はページと同じ水。representative の例題 abc447_f の型の置き場がなかったため）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 件すべて一致。各プログラムは小さい入力で全探索・素朴な BFS と assert で照合。greedy-children と independent-set はランダムな木 300 個でも照合した）、textlint（エラー 0・警告 28。数式を含む文の長さ、`$…$` の中の助詞の重複の誤検出が大半）
- 動く図：作っていない。catalog の visual は priority 2 なので、静的な SVG 2 枚（葉から根へ (白, 黒) が集まる図、根を子へ移すときの距離の和の差分の図）で代えた。動く図を後で作るなら、independent-set.svg と同じ 6 頂点の木（辺 1-2・1-3・2-4・2-5・3-6）で葉から順に値が決まるステップ送りにすると本文の数値（23 通り、f(1) = 8・f(3) = 10）と合う
- 使った出典：Series_205（Qiita, dp_p）、ikatakos（abc220_f の問いだけ）、merom686・torus711（abc447_f）、E869120 の典型90 解説画像（typical90_bu）、kazun（abc239_e）、gotoki_no_joe（Qiita, abc348_e）、drken 4 本（abc133_e・abc259_f・abc359_g・abc246_g）。abc447_f の確認のために kcpc.hatenablog.com も読んだ（meta に noai・noimageai なし。参考には載せていない。付録 B にない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc447_f | summary | 木の部分グラフとして含まれるムカデグラフ（k 頂点のパスの各頂点に、葉を 2 つずつ付けたもの）の k の最大を求める（複数のテストケース）。 | https://merom686.hatenablog.com/entry/2026/03/01/013149 ・ https://torus711.hatenablog.com/entry/2026/03/01/213520 |
| abc447_f | evidence | torus711 の記事を足す | https://torus711.hatenablog.com/entry/2026/03/01/213520 |
| abc447_f | alternatives（tree-diameter）の summary | 上と同じ | 同上 |
| typical90_bu | summary | 各頂点に a か b が書かれた木で、辺をいくつか切り、どの連結成分にも a と b の両方が含まれるようにする方法の数を求める。（今の「a か b が書かれた木の辺」は辺に書かれているとも読める。解説画像では頂点に書かれている） | https://github.com/E869120/kyopro_educational_90/blob/main/editorial/073.jpg |
| abc348_e | evidence | 今の 2 件で問いを確かめられた（gotoki_no_joe の記事。根を動かした差分 f(V) = f(R) + W − 2D の式もある）。変更なし | — |

ほかの問題（dp_p・abc220_f・abc239_e・abc133_e・abc259_f・abc359_g・abc246_g）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- 空の積｜empty-product｜掛ける対象が 1 つもないときの積で、値は 1 とする（空の和は 0）。DP の葉や初期値の決め方の根拠になる（本文ではリンクしていない。足すなら tree-dp の postorder 節の「空の積（1）」からリンクする）

## 手引きへの提案

- front matter の related に `small-to-large#subtree-merge`・`cpp-environment#stack-depth` があるが、どちらのページもまだ stub なので、§7 に従い本文ではページへのリンク（anchor なし）にした。ページが draft になったら、tree-dp-merge 節と pitfalls 節のリンクに anchor を足すとよい
- binary-search の報告と同じく、sections の `pitfalls` が長い題名（「落とし穴：再帰の深さ・親への逆流・根の選び方」）を持つので、§13.2 に従って見出しも同じにした。定型の `## 落とし穴 {#pitfalls}` にそろえるかはメインで決めてほしい

## 問題の補充の候補

- 水のページに abc319 以降の問題を 1 問以上という目安は、abc348_e（練習）と abc447_f（例題）で満たしている。新しい候補は探していない
- catalog の level_evidence にある abc369_g（2055、子ごとの得の応用）は台帳を見ていない。greedy-children 節の力試しに足すなら、第三者の解説での確認が要る

## 未解決の点

- abc447_f のムカデグラフの定義（パスの各頂点に葉が 2 つ、部分グラフとして含むか）は、問題文を開けないので 2 つの第三者の記録の次数の条件（端は 3 以上、途中は 4 以上、長さ 1 は 2 以上）から組み立てた。「部分グラフ」か「頂点を取り除いて得られる」かなどの言い回しは検証役に確かめてほしい（解き方は変わらない）
- abc246_g の式 dp[v] = max(0, Σ dp[c] − 1) + [v が黒] は、drken の記事の数式部分が取得した文から欠けていたため、記事の言葉（黒頂点自体の余裕値は 1、黒い子が 2 個なら 1、3 個なら 2）と合うように組み立てた。式と「駒が v に入る前に消しておく必要がある数」という意味づけを検証役に確かめてほしい
- 再帰の深さについて、AtCoder のスタックの上限の具体的な値は書いていない（確かめていない）。cpp-environment の stack-depth 節と食い違わないかを見てほしい
- SVG 2 枚は描画して確かめる道具がなく、座標と文字幅の見積もりだけで確かめた。表示の確認を検証役に頼みたい
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 13 回（curl 12・検索 1）

## 検証の指摘への対応（2026-10-21）

- 直すべき：0 件。直すとよい 10 件はすべて採った（7・10 は一部）
- 1：「初期値 0 で見落とす」の文を消し、「場合分けの落とし」の箇条を別に立てた（ABC447 F の長さ 1 の例へリンク）
- 2：まとめてソートなら $O(NK \log(NK))$、1 人ずつ切り詰めれば $O(NK \log K)$ と書き分けた
- 3：$-\infty$ の表し方によってはオーバーフローする、とだけ書き、本数の数え方がずれるという言い過ぎを消した
- 4：要点を「子どうしの部分木」、導入を「同じ頂点の子の部分木どうし」に直した
- 5：手元（8 MiB が多い）で落ちることを先に書いた
- 6：直径の段落に、頂点数で数えること・葉は up = 1・辺の数なら 1 を引くことを足した
- 7（一部）：小さい文字（13・12）を本体と同じ 14 にそろえた。15 以上にして図を組み直すことはしていない。図の計算の行は本文に同じ内容が文章で書かれており、ほかのページの図の文字の大きさの方針（本体 14）に合わせたため
- 8：和で効く理由（どの子へ進むか分からない、1 手は v にいる間に打てる）と小さな例（黒い葉の子 2 つで 1、3 つで 2）を足し、「参考の解説に詳しい」を消した
- 9：Series_205 氏の題名を「EDPC P ~ S 問題 解説」に、ikatakos 氏の行を「解法の節」に直した
- 10（一部）：(a) 本文に「コードでは `white[v]`・`black[v]` と書く」を足した（コードは白黒の名前の方が遷移のコメントと読みやすいので残した）。(b) greedy-children の `best` のラムダはメインの判断に任せる（手引き §9 の「など」の範囲と考えて残した）

## 追加の提案（検証の指摘 4 から）

- front matter の summary の「各頂点の部分木は互いに交わらない小問題になる」は、祖先と子孫の部分木が入れ子になるので言い過ぎである。「同じ頂点の子の部分木どうしは交わらない小問題に分かれるので」のように直すことを提案する（front matter はページ内だが、summary は catalog・一覧に出るのでメインの判断に任せ、今回は変えていない）
