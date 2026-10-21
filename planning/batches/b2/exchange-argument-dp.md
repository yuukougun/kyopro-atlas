# exchange-argument-dp の報告と提案（b2）

- 書いたファイル：docs/dp/exchange-argument-dp.md、snippets/exchange-argument-dp/tower.{cpp,yaml}・composition.{cpp,yaml}、docs/img/exchange-argument-dp/swap-tower.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 16。数式を含む文の長さ・「に」の重なり・図の代替テキストの長さ・数式の中の括弧の誤検出）
- コード片の確かめ：どちらも n ≤ 7 で「集合と順序をすべて試す」素朴な方法と assert で突き合わせ、乱数の入力 400 組でも一致した
- 図：swap-tower.svg（隣り合う 2 つのブロックを入れ替えたときの耐えられる重さの上限）。render_svg.py の 720px・360px で目で確かめた。visual は static・priority 3 なので動く図は作っていない
- 使った出典：
  - kyopro-friends（EDPC X の方針）、qiita Series_205（EDPC X）、github E869120 の sol/011-03.cpp（典型90 011。台帳の evidence の jpg の代わりに解答コードで確かめた。手引き §14-17）
  - drken1215（ABC163 E の方針と N ≤ 2000）
  - sen-comp.hatenablog.com（ABC145 E の方針）：新しいドメイン。check_noai で noai・noimageai の指定なしを確かめた
  - shinchankosen.hatenadiary.jp：check_noai で指定なしを確かめたが、本文には使っていない
- ikatakos.com は作業中ずっと HTTP 503 で読めなかった（abc366_f・abc145_e・abc216_f の evidence）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc145_e | evidence | https://sen-comp.hatenablog.com/entry/2019/11/17/003150 を足す | ikatakos が 503 で読めず、この記事で「時間の昇順に並べて最後の 1 つを決め打ち」を確かめた |
| typical90_k | evidence | https://github.com/E869120/kyopro_educational_90/blob/main/sol/011-03.cpp を足す | 締切の昇順にソートしてから日数を状態にする DP を解答コードで確かめた |
| abc163_e | summary | 「活発度 A_i の幼児を並べ替えて、各幼児の活発度 × 移動距離の和の最大を求める。」 | 今の「〜を最大化する。」は他の要約の「〜の最大を求める。」の形とそろっていない（本文は台帳のまま） |

## 用語集への提案

なし（状態 #state・狭義の弱順序 #strict-weak-ordering は既存の anchor を使った）

## 手引きへの提案

- 比を掛け算で比べる注意（分母の符号・分母 0・積の大きさ）は exchange-argument#ratios と重なる。持ち主を exchange-argument にするなら、こちらは DP 側の例（一次関数の合成）だけ残して要点をリンクに置き換えられる。exchange-argument が draft になったときに、どちらを持ち主にするかをメインが決めるとよい

## 問題の補充の候補

- 確認済みの問題は例題 3・練習 2・力試し 1 で、目安を満たしている。abc319 以降の問題は abc366_f の 1 問だけ
- 候補（未確認。ap.py と第三者の解説での確かめはしていない）：なし。ikatakos が読めず、abc319 以降で「並べてから DP」の型を第三者の解説で裏付けられる問題を見つけられなかった

## 未解決の点

- abc366_f の evidence（ikatakos）が 503 で読めなかった。比較の式 B_j(A_i − 1) と B_i(A_j − 1) は自分で計算し、コード片の全探索との突き合わせで確かめた。制約（N ≤ 2×10^5・K ≤ 10・A, B ≤ 50）は Web 検索の結果の要約（qiita aoriso 氏の記事についてのもの）からで、記事の本文は読んでいない。検証役は ikatakos が復旧していれば読み直してほしい
- ABC163 E の活発度の上限は確かめられなかったので、本文では具体的な値を書かず「活発度が大きいと int を超える」とした
- EDPC X の制約（N ≤ 10^3、w, s ≤ 10^4）は kyopro-friends の記事の要約から。本文には具体的な制約を書かず、表の幅 max s + max w だけを書いた
- 典型90 011 の表の幅は解答コードの 5000 から。本文は O(N max D) とだけ書いた
- place-at-ends（黄）の「大きい順に端へ置いてよい」の証明は本文に書かず、drken 氏の記事に任せた
- 骨格の related にある exchange-argument・interval-dp は stub なので、anchor なしでリンクした

## 検証の指摘への対応（b2 verify）

- 直すべき 1〜3、直すとよい 4〜11 をすべて直した。採らなかった指摘はない
  - 1：`double` の害を「違う比が同じ値に丸められて順を取り違える（誤答）」に改め、落とし穴は `<=`（未定義動作）と `double`（誤答）を分けた
  - 2：値の上限を約 $2 \times 10^{17}$（$50^{10} \cdot 99/49$ ほど）に直した
  - 3：「$s$ だけ・$w$ だけ」を落とし穴の別の段落「入れ替えの式から基準を作っていない」に分け、$w$ だけで失敗する例（A：w=5,s=0、B：w=1,s=100）を足した
  - 4：「最後の 1 つ」の段落に、−1 が ABC145 E の T − 0.5 と整数の時間から来ることと、入れ替えで減るのは 2 つの所要時間の差であることを書いた
  - 5：典型90 011 の状態を「t 日目までに終えたとき（空きの日を許す）」にし、本文の状態の定義もそろえた
  - 6：drken 氏の記事は考え方の出典とし、端へ寄せても和が減らない理由（遠い側の端へ寄せ、ずらした人は距離が高々 1 減るだけ）を本文に 1 文で足した
  - 7：$A_i < 0$ で入れ替えの議論と最大だけ持つ DP の両方が壊れると書き、最大と最小を持つ話は消した
  - 8・9：swap-tower.svg を縦の 2 段（400×640、文字 16・添字 13）にし、ブロック i を常に青・j を常に黄（j は破線の枠も）にした。代替テキストの「左・右」は「(a)・(b)」にした。360px・720px の PNG で目視した
  - 10：EDPC X と典型90 011 の解法の詳細の長い文を分けた
  - 11：DP の手間を $O(N \max s)$、表の幅（メモリ）を $\max s + \max w$ と分けて書いた

## 提案（検証の指摘から。共有ファイル・ほかのページ）

- docs/basics/exchange-argument.md の落とし穴「`double` の比は誤差で同点になって同等の推移を壊す」は、要素ごとに決まる `double` のキーの比較は推移的で、害は順の取り違え（誤答）である。このページの指摘 1 の直しとそろえて、持ち主のページを直すとよい
- abc163_e の summary：ページは主の summary を使っている。alternatives の summary に合わせるか主を書き換えるかはメインが決める（検証の台帳への提案のとおり）
