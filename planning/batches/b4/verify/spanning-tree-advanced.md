# b4 検証：spanning-tree-advanced

- 対象：docs/graph/spanning-tree-advanced.md、snippets/spanning-tree-advanced/boruvka.{cpp,yaml}・manhattan-mst.{cpp,yaml}、docs/img/spanning-tree-advanced/octants.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px の PNG にして確かめた（ライトの白背景。SVG は背景を白で塗っているのでダークでも同じ見え方）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page spanning-tree-advanced`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/spanning-tree-advanced`：2 本とも 4 case 一致
- 両方のコード片を `-fsanitize=address,undefined -Wall -Wextra` でコンパイルし、乱数の種を変え、比べる回数を 20000 回（Manhattan は座標の範囲を 0〜49 に広げて）にしても、素朴な方法（配列のプリム法・全点対のクラスカル法）と一致した。警告・サニタイザの報告なし。Manhattan の候補の辺が $4N$ 本以下という assert も通った
- `npx textlint`：エラー 0・警告 2（38 行目は要点の計算量の行の長さ、78 行目は数式の中の読点。執筆者の報告と同じで、§13-8 で残してよいもの）
- front matter：変えたのは complexity・stage・updated だけ（git diff で確認）。要点の「何ができるか」と summary が一致、要点の計算量と complexity が一致。別名の行に aliases がすべてある
- リンクの anchor：minimum-spanning-tree の #kruskal-prim・#why-correct・#reduce-candidates、bottleneck-path#why-mst、lca#path-aggregate、manhattan-chebyshev#remove-abs、glossary#cut・#contraction はどれもある。#reduce-candidates の確認問題に「ソートした隣どうしでは足りない」反例（(3,0)・(0,3)・(2,2)・(4,4)）があり、本文の「反例は最小全域木の確認問題」と合う
- Library Checker：library-checker-problems（GitHub）の task.md・info.toml で確認した
    - directedmst：$N, M \le 2 \times 10^5$、重み $0 \le c_i \le 10^9$、根 $S$ から全頂点へ到達可能、出力は重みと親の列。本文の括弧書きと一致
    - manhattanmst：$N \le 200000$、出力は重みと辺。一致
    - minimum_spanning_tree：無向・連結・単純とは限らない、出力は重みと辺の番号。Borůvka 法の確かめに使える
    - judge.yosupo.jp の 3 つの URL は 200 を返す（執筆者の未解決の点 1 への答え：URL の形は正しい）
- 計算量
    - Borůvka 法：1 段で各成分が別の成分と併合されるので成分数は半分以下、段は $\lceil \log_2 N \rceil$ 以下。1 段 $O(M)$ で $O(M \log N)$。ei1333 氏のライブラリの build も $O(E \log V)$ と書いている
    - Edmonds：英語版 Wikipedia に素朴な $O(EV)$、Tarjan の $O(E \log V)$（疎）、Gabow ほかの $O(E + V \log V)$ がある。ei1333 氏の Directed MST は skew heap を使い $O(E \log V)$。本文と一致
    - 第 2 最小全域木：最小全域木 $O(M \log M)$＋ダブリングの前計算 $O(N \log N)$＋各辺 $O(\log N)$ で $O(M \log N)$。一致
- 主張の確かめ
    - Manhattan の 8 領域の補題・4 回の走査で足りること：cp-algorithms の記事と一致。コード片の `break`（$dy > dx$ の点より $y$ の小さい点も外）は乱数の比較で確かめた。同じ $y$ の点を `sweep[-y[i]] = i` で上書きする箇所は、直前のループで同じ $y$ の点が必ず先に取り出されて消える（$dy = 0 \le dx$）ので取りこぼしはない
    - Edmonds の「入る辺から一律に $c_v$ を引いても最適な木は変わらない」「0 の辺に閉路がなければ最適」：正しい。「閉路の辺を 1 本だけ外した最適な木がある」は Wikipedia の手順（閉路から $(\pi(v), v)$ を 1 本外す）と合う（未解決の点 3：資料に任せてよい）
    - 「根が決まっていないとき」の $L$ の技：$L$ の辺を 1 本だけ使う木の重みは $L + (\text{元の辺の和}) < 2L$、2 本以上なら $2L$ 以上なので、重みが非負なら正しい（指摘 3）
    - 第 2 最小全域木の 1 本の入れ替えの補題：cp-algorithms の記事の本文にある。真に大きいものの「2 番目の最大」は、同記事のコードの combine（最大と、それと異なる 2 番目を持ち、等しいときは 2 番目を使う）にあり、本文の「資料：…真に大きいものを求めるときの 2 番目の最大」と合う（文章では説明していない点は参考の書き方で正確）
    - Borůvka 法の同じ重みの扱い：Python で確かめた（指摘 1）
- 例の重み $D \lvert i - j \rvert + A_i + A_j$：drken 氏の記事（台帳の keyence2019_e の evidence）の重みと同じで、記事に「解法 3: Borůvka 法」の見出しと「Borůvka 法でやると自然に解けるみたい」という一言がある。執筆者の報告の「言及のみで手順はない」と合う。本文は問題 ID を出さず型だけを書いており §13-6 に合う。例を自分で $j < i$ と $j > i$ に分けた式 $(A_j - Dj) + (A_i + Di)$ は正しい
- 参考の URL：Wikipedia 2 本・cp-algorithms 2 本・ei1333 氏の 3 ページ・drken 氏の記事・GitHub がどれも 200 で、題名と内容が書かれたとおり。atcoder.jp・codeforces.com の URL はない
- 図 octants.svg：viewBox 360×352 と width・height が同じ比、背景は白、文字は sans-serif のテキスト。塗った領域（右の水平線と右上の斜線の間）は数学の座標で $0 \le y_q - y_p \le x_q - x_p$ に当たり、q（差 50, 25）と r（差 110, 80）はその中にある。$x+y$ 一定の破線は q を通る（差の和 75）。360px でも文字が読め、重なりもない

## 指摘

### 1. 直すとよい｜事実（F2）・分かりやすさ（U3）｜#boruvka の「なぜ正しいか」の最後の 2 文

- **問題**：「比べ方を決めないと、2 つの成分が同じ重みの別の辺を選び、合わせて閉路を作りうる」とあり、読者は「全順序で比べないと答えを間違える」と読む。しかし同じ節の「同じ辺を 2 回足さない」のとおり、採るときに Union-Find で両端がすでに同じ成分かを確かめるなら、全順序で比べなくても重みの和は正しい。全順序が要るのは、選んだ辺をまとめて全部採る（確かめない）書き方のとき
- **根拠**：選んだ辺が成分の間で閉路を作るとき、閉路の各成分が選んだ辺は前の成分の辺以下なので、閉路の辺の重みはすべて等しく、1 本外しても損をしない。Python で、同じ重みの辺の中からランダムに選び、Union-Find で確かめて採る Borůvka 法を、重み 0〜2 の小さなグラフ 20000 個でクラスカル法と比べ、すべて一致した（スクリプトは作業用の場所の tie.py）
- **直し方**：「選んだ辺をまとめて採ると、比べ方を決めなければ閉路を作りうる。採るたびに Union-Find で確かめるなら重みの和は正しいが、比べ方を決めておくと選んだ辺が必ず森になり扱いやすい」のように、条件を書き分ける

### 2. 直すとよい｜分かりやすさ（U3）・用語（F7）｜#directed の「計算量」の「併合できるヒープ」のリンク

- **問題**：リンク先が advanced-ds-catalog のページの先頭で、節を指していない。また、そのページの見出し・別名は「併合可能なヒープ」で、本文の「併合できるヒープ」と揺れている（front matter の complexity と要点も同じ語）
- **根拠**：docs/ds/advanced-ds-catalog.md の sections に `{title: 併合可能なヒープ（…）, anchor: meldable-heap}` がある
- **直し方**：リンクを `../ds/advanced-ds-catalog.md#meldable-heap` にする。語を「併合可能なヒープ」にそろえるかはメインが決める（complexity を変えるなら front matter の変更として提案に回す）

### 3. 直すとよい｜事実（F2）・実装の粒度（U4）｜#directed の「根が決まっていないとき」

- **問題**：(a) $L$ を「元の辺の重みの和より大きい値」としているが、負の重みがあると成り立たない（Library Checker は非負だが、本文は重みの符号を述べていない）。(b) 答えの重みが $2L$ 未満のとき、元のグラフでの答えが「結果 $- L$」であること、根が「$L$ の辺の先の頂点」であることが書かれておらず、読者が取り出し方で迷う
- **根拠**：使う $L$ の辺が 1 本なら重みは $L + (\text{元の辺の和}) < 2L$。負の辺があると元の辺の和が小さくなり、$L$ の辺 2 本の木と区別できなくなる場合がある
- **直し方**：「$L$ は元の辺の重みの絶対値の和より大きくする」とし、「$2L$ 未満なら、結果から $L$ を引いたものが答えで、$L$ の辺の先が根になる」を足す

### 4. 直すとよい｜事実（F2）｜#directed の「閉路の検出」

- **問題**：「選んだ辺を逆にたどると、各頂点から出る辺が 1 本のグラフになる」とあるが、根は入る辺を選ばないので出る辺がなく、functional graph の形（全頂点の出次数が 1）にならない
- **根拠**：手順 1 は根以外の頂点についてだけ辺を選ぶ
- **直し方**：「根には自分への辺を足す（または根で止まる）と、Functional graph の閉路の見つけ方がそのまま使える」と 1 句足す。あわせて、縮約のときに閉路の内側どうしの辺（縮約後の自己ループ）を捨てることを「自作するときの要点」に一言入れると、「入る辺がなければ答えなし」の判定が自己ループで狂う失敗を防げる（手順 3 の「外からの辺」で示されてはいるが、実装の落とし穴として明示するとよい）

### 5. 直すとよい｜図（G5）｜octants.svg

- **問題**：(a) 座標軸の向きが図にない。SVG の上が $y$ の大きい向きであることが分からないと、「塗った領域：0 ≤ (y の差) ≤ (x の差)」を右下の領域と読み違えうる。(b) 「x+y 一定」の青い破線は 360px で細く短く、実線の辺の陰になって見つけにくい
- **根拠**：render_svg.py の 360px の PNG を目で見た
- **直し方**：(a) 左下などに小さく「x →」「y ↑」の矢印を足す。(b) 破線を少し太くし（2〜2.5）、塗った領域の端まで伸ばす

## 執筆者の未解決の点への答え

1. Library Checker の 3 つの URL：GitHub の定義と judge.yosupo.jp の応答で確かめた。正しい
2. 第 2 最小全域木の Library Checker の問題がないこと：確かめていない（ディレクトリの全数は見ていない）。本文はこれに依存した主張をしていないので問題ない
3. 「閉路の辺を 1 本だけ外した最適な木がある」を資料に任せること：発展の概要の分量（§13-10）として妥当。Wikipedia の手順と合う
4. related に bottleneck-path・functional-graph・lca を足す案：本文でリンクしており妥当。メインの判断

## 総合の判定

小さな直しで可。直すべき指摘は 0 件、直すとよい指摘は 5 件。事実・計算量・コード片（サニタイザ付きの長い乱数比較を含む）・参考の URL に誤りは見つからなかった。
