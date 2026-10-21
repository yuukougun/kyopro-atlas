# difference-constraints の報告（b2）

- 書いたファイル：docs/graph/difference-constraints.md、snippets/difference-constraints/max-diff.{cpp,yaml}、docs/img/difference-constraints/example.svg
- front matter で変えたもの：complexity・stage（draft）・updated（今日のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（コード片 1・期待と違う 0）、textlint（エラー 0・警告 7。図の代替テキスト・出典の行・`[l, r)` を含む文の誤検出と、数式を含む文の長さ）
- 図：example.svg を render_svg.py で PNG にして目で確かめた。動く図は作っていない（visual は static・priority 2）
- 使った出典：kmjp（abc216_g・abc404_g の方針）、drken の Qiita（牛ゲーの定式化・負閉路と非有界の場合分け・双対性）、drken のはてなブログ（arc090_b の制約 N ≤ 10^5・M ≤ 2×10^5）、yamate11.github.io（abc216_g の制約 N, M ≤ 2×10^5）
- 新しく noai を確かめたドメイン：yamate11.github.io（check_noai.py で HTTP 200・X-Robots-Tag なし・meta robots="index, follow"。付録 B への追加を提案）

## 台帳への提案

- なし（3 問とも台帳の summary・approach のとおりに書いた）
- 参考：abc216_g の note にある「例題としての適否は未確認」は、kmjp 氏の記事で 0 の個数の累積和を変数にした差分制約＋ダイクストラ法で解けることを確かめた。貪欲＋BIT の別解はあるが、差分制約の representative の例題としてよいと考える。note の更新を提案する

## 用語集への提案

- なし（負閉路 negative-cycle・緩和 relaxation・ポテンシャル potential は既存の語を使った）
- 候補（任意）：差分制約｜difference-constraints は手法のページがあるので用語集には要らない

## 手引きへの提案

- 付録 B に yamate11.github.io を足す
- graph の書き方（§5）に「差分制約の最小化は、向きを逆にした最短距離の符号反転（x_t − x_s の最小 ＝ −dist(t→s)）」と書くかどうかは任せる。bellman-ford の longest-path の節と表現をそろえると読者が迷わない

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc368_e（E. Train Delay、diff 2140、ap.py で実在を確認）：research/03-graph の表で差分制約の問題に数えられている。列車の遅延 X_i を、乗り換えの条件 X_j − X_i ≥ T_i − S_j の下で総和最小にする問題と記憶しているが、第三者の解説で問いと解き方を確かめられていない（検索では裏付けが見つからなかった）。黄の帯で、解法は差分制約そのものより時刻順の処理（イベントソート）が主と思われるので、候補としては弱い。確かめたうえで力試しにするかを判断してほしい
- abc319 以降の青の ABC の例が台帳にない（abc404_g は練習）。差分制約がそのまま使える abc319 以降の問題は見つけられなかった

## 未解決の点

- 骨格の「いつ使うか」の「位置の差の情報が矛盾しないか」は、等式だけなら重み付き Union-Find の方が主役になる。本文では consistency の節で振り分けたが、signs のこの行を weighted-union-find 側の sign に寄せるかはメインの判断に任せる
- bellman-ford のページは stub なので、節（relevant-cycles・longest-path）へは anchor を付けずページへリンクした。draft になったら「届かない負閉路」の話を bellman-ford#relevant-cycles へリンクできる
- 例題の解法の詳細に「1 の個数の累積和を変数にすると負の辺になる」と書いたのは自分で導いた式で、出典の記事には書かれていない（式の検証は本文のとおりで、検証役に確かめてほしい）

## 検証の指摘への対応（b2）

- 1（直すべき・確認問題「届かない頂点」）：直した。ずらす集まりを「$s$ から届かない変数（$x_t$ も含む）」にし、届く頂点から入る辺がないことを根拠に書いた。#why-maximum の「$t$ に届かない」の行にも同じ根拠を足した
- 2（直すべき・#direction の覚え方）：直した。「右辺の $x_u + c$ の側から、左辺で上から抑えられる $x_v$ の側へ」にし、落とし穴の節と言い方をそろえた
- 3（直すとよい・落とし穴の見出し）：直した。見出しを「届いていない頂点から緩和する」にし、INF を LLONG_MAX にするとあふれることを一言添えた
- 4（直すとよい・relax_all の回数）：直した。「$N - 1$ 回の走査で値が定まり、次の走査で更新がないことを見て返す」とし、$s$ から始める場合（単純な道は辺 $N - 1$ 本まで）と全頂点 0 から始める場合の理由を分けて書いた
- 5（直すとよい・図の大きさ）：直した。凡例を図の下へ移し、viewBox を 700×300 から 480×432 にした。render_svg.py の 360px で文字が読めることを確かめた
- 6（直すとよい・signs の「位置の差の情報が矛盾しないか」）：採らなかった。signs の変更は front matter の項目で執筆者が変えられないため。メインへの提案：この sign を「位置の差の不等式（〜以上離れている・〜以内）が矛盾しないか」に変えるか、weighted-union-find 側の sign に寄せる
- 台帳への提案（検証役から）：abc216_g・abc404_g・arc090_b の `checked` に 2026-10-21、abc216_g の note「例題としての適否は未確認」を外す
- 検査（直した後）：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0・警告 7。前と同じ誤検出と文の長さ）
