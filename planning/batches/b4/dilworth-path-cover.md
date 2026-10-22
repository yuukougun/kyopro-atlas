# dilworth-path-cover の報告と提案（b4）

- 書いたファイル：docs/graph/dilworth-path-cover.md、snippets/dilworth-path-cover/path-cover.{cpp,yaml}、docs/img/dilworth-path-cover/split.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0。ほかに乱数の DAG 300 個で反鎖の全探索と照合）、textlint（エラー 0・警告 5。要点の計算量・数式の多い段落・確認問題の題の文の長さ、台帳の summary の助詞「に」の重複。どれも数式を含む文の長さか台帳由来）
- 図：split.svg を render_svg.py で PNG にして目で確かめた（幅 360）
- 新しく noai を確かめたドメイン：なし（kmjp・ikatakos・en.wikipedia・oi-wiki・judge.yosupo.jp・github.com は付録 B にある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc374_g | summary | 2 文字の文字列の集合が与えられる。隣り合うどの 2 文字も集合に含まれる文字列を何本か作り、集合の文字列がどれも少なくとも 1 本に部分文字列として現れるようにするとき、本数の最小を求める。 | https://kmjp.hatenablog.jp/entry/2024/10/06/0930 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1005_abc374 |
| abc374_g | evidence | ikatakos の URL を足す | 同上 |
| abc354_g | summary | 重みの付いた文字列が N 個与えられ、どの 2 つも一方が他方の部分文字列にならないように選ぶとき、選んだ重みの和の最大を求める。 | https://kmjp.hatenablog.jp/entry/2024/05/19/0930 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0518_abc354 |
| abc354_g | evidence | ikatakos の URL を足す | 同上 |
| abc215_h | summary | キャベツの種類ごとの個数と、各会社の必要数と受け入れる種類が与えられる。全社の要求を満たす配り方がなくなるように取り除く個数の最小値と、その個数での取り除き方の数を求める。 | https://kmjp.hatenablog.jp/entry/2021/08/22/0930 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0821_abc215 |
| abc215_h | evidence | ikatakos の URL を足す | 同上 |
| abc237_h | summary（任意） | 「…選ぶとき、選べる最大数を求める。」の「に」の重複で textlint の警告が出る。直すなら「文字列の部分文字列である回文を、どの 2 つも一方が他方の部分文字列にならないように選ぶとき、選べる個数の最大を求める。」 | https://kmjp.hatenablog.jp/entry/2022/01/31/0930 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 推移閉包 | transitive-closure | 有向グラフで、u から v へ 1 本以上の辺で届くとき、またそのときだけ辺 u→v を張ったグラフである。各頂点から探索すれば O(N(N + M)) で求まる。 |
| 鎖・反鎖 | chain-antichain | 半順序の要素の集まりで、どの 2 つも比べられるものを鎖、どの 2 つも比べられないものを反鎖という。DAG では、鎖は 1 本の道に乗る頂点の集まりにあたる。 |
| 最小パス被覆 | path-cover | DAG の頂点を、頂点を共有しないパスに分けるときの本数の最小である。頂点を 2 つに分けた二部グラフの最大マッチングを頂点数から引いた値に等しい。（ページがあるので用語集に置くかはメインの判断） |

## 手引きへの提案

- §5 graph に「頂点を共有してよい鎖での被覆は、推移閉包を取ってから頂点を共有しないパス被覆にする。覆わなくてよい頂点を通過できる場合も同じ（辺 0→1→2 で 0 と 2 だけを覆うなら、閉包を取らないと 2 本と誤る）」を足す案。持ち主は dilworth-path-cover#antichain

## 問題の補充の候補

- なし（台帳の 4 問で例題 1・練習 3 がそろった）

## 未解決の点

- abc237_h の裏付けは kmjp の 1 件だけ。ikatakos の abc237 のページには Ex の節がなく、ほかの第三者の解説も検索では見つからなかった（§15-6 の 2 件以上の目標に届かない）
- abc374_g の summary は kmjp と ikatakos の解法の節（NG リストの文字列をウォークとみる）から書いた。問題文は読んでいないので、「作る文字列の隣り合う 2 文字がすべて集合に含まれる」という条件の言い方を検証役に確かめてほしい
- 本文の重み付きの反鎖（ABC354 G）の「重みの総和 − 最大流」は、2 つの解説の構成をそのまま書いたもので、本文では証明していない（概要のページなので資料に任せた）
- 「学ぶための資料」は独立の節にせず、参考の各行に「（学ぶための資料）」と添えた（parallel-binary-search と同じ形）
- 使用量の目安：道具の呼び出し 40 回ほど、Web 取得 12 回（検索 5 回を含む）

## 検証の指摘への対応（直し）

- 1（直すべき・閉路があるとき）：直した。縮約した DAG の推移閉包を取ってから最小パス被覆を求めることと、図の DAG でウォーク 2 本・閉包なし 3 本の例を足した
- 2（計算量）：直した。「ACL では」の囲みに Dinic 法も二部マッチングの形では $O(M\sqrt{N})$ で動くこと（bipartite-matching#alternating-path）を足し、#antichain の「辺の数」にも「`mf_graph` の Dinic 法でも同じ」と添えた
- 3（図のラベル）：直した。入る側を 0'〜4' にし、代替テキストも 0-2' などに合わせた。幅 360 で重なりなしを確かめた
- 4（Hall の右の部分集合）：直した。$N(S) \subseteq T$ の形で書き直し、確認問題 2 の答えも合わせた
- 5（導入の 1 文目）：直した。「最小パス被覆の公式と Hall の定理は」にした
- 6（確認問題 1 の題）：直した。題を縮め、答えの 1 文目を分けて警告を消した
- 採らなかった指摘：なし
- 申し送り（メインへの提案、再掲）：bipartite-matching.md 157 行目の Hall の定理へのリンクを `../graph/dilworth-path-cover.md#hall`・文言「Hall の結婚定理」に張り替える。台帳の abc374_g・abc354_g・abc215_h の `checked` に 2026-10-22 を入れる（検証役が問いの内容を確かめた）。abc237_h の evidence が 1 件で目標 2 件に届かないことを台帳か進捗に記録する
