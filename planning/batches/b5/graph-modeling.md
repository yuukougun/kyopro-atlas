# graph-modeling の報告（b5）

- 書いたファイル：docs/graph/graph-modeling.md、docs/img/graph-modeling/points.svg、docs/img/graph-modeling/bipartite.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections の what-to-vertex の title を「何を頂点にするか（物・値・座標・状態・時刻・剰余・区間の端点）」に短くした（「→ 行き先のページの表」を除いた。anchor は不変。見出しと同じ文字）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、textlint エラー 0・警告 4（要点の計算量の列挙の「は」2 件、並べた 2 枚の図の代替テキストの文の長さと読点。誤検出として残した）
- 図：render_svg.py で 360px・720px を目視した（B と「足す」のラベルを線の上の白地に置き直した）。visual は priority 2 の static で、言い換えの前後の 2 枚に分けた（§15-8）
- 使った出典：drken1215（ABC131 F）、kmjp（ABC286 G）、cnblogs Lanly（ABC377 E）。どれも付録 B のドメイン。新しいドメインなし

## 台帳への提案

- abc286_g・abc131_f・abc377_e：変更なし（role practice のまま。問いと方針を evidence で確かめた）
- abc377_e：evidence が 1 件だけ（§15-6 は 2 件以上を目標）。2 件目を探す余地あり（今回は探していない）

## 用語集への提案

- なし（「縮約」は既存の contraction にリンクした）

## 手引きへの提案

- hub の表に「代表の問題」の列を置き、ほかのページの例題の小見出し（`../<field>/<id>.md#<問題ID>`）へリンクした（dp-speedup-overview と同じ形）。台帳の pages に graph-modeling を持たない問題も、相手のページの例題へのリンクとして表に出している。hub の問題数の目安（合わせて 0〜3）は、自分の囲みの問題だけを数えると解釈した。この解釈でよいかを §4 か §10 に書いておくと迷わない
- 次数 1・2 の頂点を消す縮約（V ≤ 2(E − V)）は持ち主のページがないので、このページの contraction の節で短く説明した。持ち主をここにするか、別のページ（degree-sqrt など）に移すかをメインが決める

## 問題の補充の候補

- abc419_g（G. Count Simple Paths 2、diff 2677）：次数 1 の頂点を消し、次数 2 の頂点を辺にまとめてから単純パスを全列挙する。contraction の節の「次数 2 の頂点を消す」の代表になる。裏付け：https://kmjp.hatenablog.jp/entry/2025/08/16/0930（research/03 §5.2 H に記載。今回は記事を読み直していないので、追加するときに確かめる）。台帳にないので本文では型だけを書いた

## 未解決の点

- b1・b2b3 の申し送りでこのページへページへのリンクを置いている箇所（bipartite-graph:141 → #what-to-edge か #what-to-vertex、connected-components:129 → #what-to-vertex、extended-dijkstra:397 → #what-to-vertex、ほかに difference-constraints:219 → #constraints-to-edges、euler-path:221 → #contraction）は、節へ張り替えられる
- euler-path:221 はリンクの文字が「グラフの作り方」、difference-constraints:219 は「グラフへの言い換え」で、題名「グラフへの帰着」と違う。張り替えるときにそろえるとよい
- 「頂点・辺が 10^6〜10^7 程度なら線形に近い探索が 1 秒前後」は complexity-estimation の 1 秒に 10^8 回の目安からの概算で、計測はしていない

## 検証の指摘への対応（b5 直し）

- 直すべき 2 件・直すとよい 8 件をすべて直した。採らなかった指摘はない
    - 指摘 1：縮約の上界に「連結で $k \ge 1$（木でも閉路 1 つでもない）」の条件、非連結なら成分ごと、残した頂点 $t$ 個で $V \le 2k + 2t$（$2E \ge 3(V - t) + t$ から。残した頂点の次数が 1 以上のとき）を足した。$k$ は元の $M - N$ に等しいと書き分けた。確認問題 3 の前提を直し、答えに次数 0・2 の頂点が残らない理由を足した
    - 指摘 2：(a) を取った。表の 2 か所（座標の値・物そのもの）の「ABC131 F（練習）」を「—」に、127 行の ABC286 G の名指しを削った。図 bipartite.svg の積の 2 行と代替テキストの「2×2 + 1×1 = 5」を「足す点は同じ成分の中の辺」に差し替え、64 行の「成分ごとに数えればよい」を削った（render_svg で 360px・720px を目視）
    - 指摘 9：確認問題 2 を「同じ $x + y$ か同じ $x - y$ でつながる点の頂点の選び方」に差し替えた
    - 指摘 10：「BFS・Union-Find のような線形に近い探索は」とし、ダイクストラ法は $10^6$ 程度までと足し、complexity-estimation#how-to-estimate へリンクした
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、textlint エラー 0・警告 4（前回と同じ要点の「は」2 件と図の代替テキスト 2 件）

## 直しに伴う提案

- 用語集の縮約（glossary.md の contraction）：「まとめた頂点どうしの辺は消し」を「多くの場合は消し（通る回数が決まった辺は自己ループとして残すこともある）」にゆるめるかをメインが決める。本文は「用語集の定義と違って消さない」と理由を書いて対応した
- 台帳 abc414_g：summary が「（執筆時に確かめる）」、checked が空のまま。表の行は「頂点・区間から区間への移動」に直したので代表として残したが、diff 3020 で重いので「—」にするかはメインの判断に任せる
- 台帳 abc131_f・abc286_g：role practice のまま（指摘 2 は (a) を取ったので役割の変更は不要）
