# parity（偶奇に着目する）の検証

- 対象：docs/thinking/parity.md、docs/img/parity/checkerboard-walk.svg（コード片はない）
- 観点：fact.md（F1〜F10）・code.md（C1〜C8）・clarity.md（U1〜U10）・figure.md（G1〜G7）
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page parity`：エラー 0・警告 0
- **台帳**：5 問（arc089_a 397・abc126_e 1340・typical90_x —・abc454_e 1627・abc474_g 2280）の label・diff・summary が data/problems.yaml と一致する。例題 2・練習 2・力試し 1 は catalog と手引き §10 の数の目安（thinking は例題 2〜4）に合う
- **evidence と参考の URL**：6 件とも取得して中身を確かめた。
    - hamayan の arc089_a：題名あり
    - drken の abc126_e：Union-Find・連結成分ごとに分解
    - E869120 の sol/024.cpp：差の合計が K 以下か、差と K の偶奇が同じか、の 2 つで判定している。本文の方針と一致する
    - Reputeless/tenkei_90：リポジトリがある
    - ikatakos の abc454・abc474：解法の節で照らした。abc454_e は「N が偶数で A+B が奇数」のときだけ可能で、本文の練習の方針と一致する。abc474_g は「N が奇数・K が偶数・N−1 ≤ K ≤ (N−1)(N+1)/2」で、構築は上 2 行の往復か左 2 列で、本文の力試しの方針と一致する
    - 問題の要約は、台帳の summary が問いだけで手法名を含まないことを確かめた。ikatakos 氏の記録で照らしたのは解法の節だけで、本文に使った文はない
- **執筆者の未解決の点（abc474_g の K の偶奇）**：小さなプログラムで確かめた。N×N で (0,0) から (N−1,N−1) へ全マスを 1 回ずつ通る道筋を全列挙し、右への移動の回数を数えた（作業用の場所の ham.cpp）。結果は次のとおりで、「K の偶奇にも条件がある」という本文の主張は正しい。N=5 の範囲は ikatakos 氏の記録の 4 ≤ K ≤ 12 と一致する。本文が具体的な条件を書かず「実験で推測する」とした書き方は、力試しの方針として妥当である
    - N=2・4・6：道筋は 0 本
    - N=3：K ∈ {2, 4}
    - N=5：道筋は 104 本で、K ∈ {4, 6, 8, 10, 12}（すべて偶数）
- **本文の主張を手で確かめた**。どれも正しい
    - ナイトの確認問題：1 回の移動で x+y は ±1 か ±3 変わる。(2,1)→(4,2)→(3,4) は正しいナイトの移動で、1 往復を足して 5 回になる
    - exactly-k：必要条件 2 つと、往復で十分になること
    - components：成分の全員の偶奇を反転しても条件が保たれること、答えが成分の数になること
    - 市松模様：L の偶奇と色の数の関係、N×N の角から角へ行く道筋、8×8 から対角の 2 隅を除く例、4×4 の確認問題
    - bipartite-game：二部グラフで歩道の長さの偶奇が決まること。dist[v][K mod 2] ≤ K で可能なこと（例外は出発点に辺がないとき。無向に限ると明記されている）
    - 落とし穴：`-3 % 2 == -1`、`x & 1` は C++20 で 2 の補数が保証される
- **リンク先**：すべて存在する。ただし comb/game-basics は現在 draft で `#move-parity` の節がある（下の 3）
- **図**：ヘッドレスのブラウザ（playwright・chromium）も rsvg・cairosvg も手元になく、画像にはできなかった。代わりに SVG の座標を読んで確かめた。
    - viewBox あり、背景は白の rect、文字はテキスト（sans-serif）
    - 右側の説明の文字は x=278 から約 182px で、幅 534 に収まる
    - 道筋 (0,0)→(0,1)→(0,2)→(1,2)→(1,1)→(2,1)→(3,1) の各マスで i+j の偶奇が歩数 t の偶奇と一致し、色の塗り分けとも合う
    - 代替テキストと図の後の文で要点が分かる
    - catalog の visual（static, priority 2「市松模様の塗り分けで、1 歩ごとに色が入れ替わる図」）を満たす
- **コード片**：snippets/parity/ はなく、code.md の C1〜C8 は対象外。本文の行内のコード（`x % 2 != 0`・`x & 1`・`long long`）は正しい

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | clarity U3 | #exactly-k の「偶奇」の行 | 「$K$ 回の後の偶奇は $K$ で決まる」から「$K \equiv D$ が必要」へ飛んでいる。$\sum A_i - \sum B_i$ と $D$ の偶奇が同じ理由（$\lvert a \rvert \equiv a \pmod 2$）が書かれておらず、読者は D がどこから来たか迷う | 本文の 1 文の前後を読んだ | 「$\lvert A_i - B_i \rvert$ と $A_i - B_i$ は偶奇が同じなので、$\sum A_i - \sum B_i \equiv D$。終わりに $B$ と一致するには $K \equiv D \pmod 2$ が必要である」のように 1 段足す |
| 2 | 直すとよい | figure G5 | checkerboard-walk.svg の矢印 | polyline の終点が最後の丸（6）の中心 (114,246) で、そのあとに丸を描いている。矢じり（markerWidth 6 × 線の太さ 3 ＝ 約 18px）の大半が半径 12 の丸に隠れ、先が欠けた形で丸の後ろから少しだけ出る | SVG の座標と描く順を読んだ（画像にする道具がなく、目では見ていない） | 最後の区間の終点を丸の縁（例：(114, 232)）までにするか、marker-end をやめる。ほかの区間には矢じりがないので、矢じりを外しても歩数の数字で向きは分かる |
| 3 | 直すとよい | fact F7（リンク） | #bipartite-game の「ゲーム」の行 | 執筆者の未解決の点のとおり、[ゲームの基本](../comb/game-basics.md) にページとしてリンクしている。game-basics は同じバッチで draft になり、`{#move-parity}`「総手数の偶奇・不変量で決まるゲーム」の節がある。front matter の related も game-basics#move-parity を指している | docs/comb/game-basics.md の 159 行目 | リンクを `../comb/game-basics.md#move-parity` にする |
| 4 | 直すとよい | fact F9 | 参考の 1 行目と 2 行目 | 記事の題名が実際と少し違う。hamayan の題名は「Traveling [AtCoder Regular Contest 089 / AtCoder Beginner Contest 086 C]」。drken の題名は「AtCoder ABC 126 E - 1 or 2 (1Q, 水色, 500 点)」 | 各ページの `<title>` | 題名を記事のとおりにする（略すなら略した形がほかのページとそろうように） |
| 5 | 直すとよい | clarity U3 | #alternating の本文と図 | 本文は格子点 $(x, y)$ と $x + y$ で説明している。直後の図と #checkerboard はマス $(i, j)$ と $i + j$ で、記号が節の中で切り替わる | 本文と SVG の文字を読んだ | 図の題を「$(x, y)$ ＝ マス $(i, j)$」と書くか、図の前に「格子点をマスと見ると」の 1 文を足して橋を架ける |
| 6 | 直すとよい | fact F1・F10 | front matter の complexity | 要点は「Union-Find でならし $O(\alpha(N))$ ずつ」と 1 回あたりであることを書いている。front matter は「ならし O(α(N))」だけで、全体の計算量と読める | 要点と front matter を並べて読んだ | complexity を「…Union-Find で 1 回あたりならし O(α(N))」にする |

直すべき指摘はない。

## 台帳への提案（確認済みの記録）

- arc089_a・abc126_e・typical90_x・abc454_e・abc474_g の checked に 2026-10-21 を入れてよい。問いと方針を evidence の解説（ikatakos 氏の記録は解法の節）で確かめた
- typical90_x の evidence に E869120/kyopro_educational_90 の sol/024.cpp を足すという執筆者の提案に賛成する（判定の中身を確かめられる）

## 総合の判定

**小さな直しで可**（直すべき 0 件、直すとよい 6 件）。事実の誤りは見つからなかった。執筆者が自分で導いた主張は、反例探しと全列挙で確かめた。ナイト・exactly-k の十分性・成分の数・市松模様の数え方・dist[v][p] の条件・abc474_g の K の偶奇がその対象である。
