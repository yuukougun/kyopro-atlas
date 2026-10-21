# rerooting（全方位木 DP）の報告と提案

- 書いたファイル：docs/dp/rerooting.md、snippets/rerooting/subtree-count.{cpp,yaml}、docs/img/rerooting/what-changes.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections に「合成と根を付ける操作の作り方の型」（anchor: patterns）を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 期待と違う 0、textlint エラー 0（警告 17 は数式を含む文の長さ・読点の数と、図の代替テキストの読点）
- 使った出典：qiita.com（keymoon・Series_205）、drken1215.hatenablog.com、kazun-kyopro.hatenablog.com、kmjp.hatenablog.jp、sigma425.hatenablog.com、ei1333.github.io、kanpurin.hatenablog.com（問題の候補探し）。どれも付録 B にあるドメインで、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc222_f | summary | 辺に重み、頂点に費用 D がある木で、各頂点 i について、i 以外の頂点 j への距離と D_j の和の最大を求める。 | https://kazun-kyopro.hatenablog.com/entry/ABC/222/F （問いは E_{i,j} = d(i, j) + D_j の最大として抽象的に定義されており、「観光」の語は記事にない。問題文の言い回しは確かめていない） |
| tdpc_tree | checked | 2026-10-21 | https://sigma425.hatenablog.com/entry/2016/08/02/214547 （方針「根をすべての頂点で試す」を確かめた。問いと制約は記事に書かれていない） |
| abc223_g | 追加（rerooting の challenge） | summary：木の各頂点 v について、v とそれに接する辺を取り除いたときの最大マッチングの大きさが元の木と同じになる v の個数を求める。approach：部分木の最大マッチングを v を使う・使わないの 2 値で持ち、全方位木 DP で各頂点を除いた値を求める | https://kmjp.hatenablog.jp/entry/2021/10/19/0930 （ap.py：G. Vertex Deletion、diff 2351） |

## 用語集への提案

- なし（結合法則 associativity・単位元 identity-element は既存の anchor を使った）

## 手引きへの提案

- 執筆の指示では担当が docs/tree/rerooting.md・レベル水となっていたが、実際のページは docs/dp/rerooting.md・level 青（catalog も dp.yaml）。ページの id・URL は変えず、docs/dp/rerooting.md に書いた。指示を作るときは front matter の field と level から作るとよい
- §5 tree の「パス状の木で再帰が深くなる」は、全方位木 DP のように 2 回走査する手法では BFS 順の配列で両方向にたどる書き方を勧めると、snippets の形がそろう

## 問題の補充の候補

- abc223_g（G. Vertex Deletion、diff 2351）：各頂点を取り除いたときに木の最大マッチングが変わらないかを問う。全方位木 DP で頂点を除いた値を求める。裏付け https://kmjp.hatenablog.jp/entry/2021/10/19/0930 。力試しの候補（黄の下限なので、ページの青より上）
- abc298_h：kanpurin 氏の典型問題メモ（https://kanpurin.hatenablog.com/entry/2020/04/07/182948）の全方位木 DP の一覧にある。問いは確かめていない（候補の手がかりだけ）
- abc319 以降で一般の全方位木 DP が要る ABC は見つからなかった（kanpurin 氏の一覧の abc337_g は research/04 がオイラーツアーの問題とし、abc348_e は根の移動の差分で済む）。drken 氏のカテゴリ「全方位木DP」の一覧は途中までしか読めていない

## 未解決の点

- 図（what-changes.svg）は手元に SVG を描画する道具がなく、座標の計算だけで確かめた。検証役が描画して文字の重なりを確かめてほしい
- TDPC N の制約（N の上限）は確かめていない。本文は「根ごとにやり直せば O(N^2)、全方位なら O(N)」とだけ書いた
- 練習の TDPC N の方針（すべての根での頂点の書き方の数の和を 2 で割る）は自分で導いたもので、第三者の解説で式までは確かめていない（sigma425 氏の記事は「すべての根で DP する」まで）
- catalog の visual は「ステップ送り」とする研究の記述もあるが、catalog では static・priority 2 なので静的な SVG にした
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 約 14 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：ABC222 F の値の上限を「最大で約 $2 \times 10^{14}$（$N \times 10^9$）になり `int` に収まらない」に直した
- 指摘 2：図のラベルから dp を外し、「頂点 2 の部分木 {2, 4, 5}」「頂点 3 の部分木 {3, 6}」「部分木 {4}・{5}（同じ）」「{3, 6}」にした
- 指摘 3：#exclude-self の文を「左右の累積そのものは結合法則と単位元だけを使い、逆元は使わない（交換法則は枠組み全体で要る）。結合法則と交換法則を満たす合成なら…」に直した
- 指摘 4：確認問題の XOR を $\oplus$ を使わず文章で書いた
- 指摘 5：「根以外の頂点の部分木はこの $2(N-1)$ 個のどれかで、根の値はそれらを合成すれば出る」に直した
- 指摘 6：$\mathrm{ans}[v]$ の式の後に、$\mathrm{up}[c]$・$\mathrm{ans}[v]$ の両方の最後の項が根ではないことを書いた
- 指摘 7：一部を採った。「根を 2 へ」「ここだけ新しく要る」を 15 に上げた。右の木の破線の枠の内側に置く「{3, 6}」は、枠の右端までの余白が約 45px しかなく 15 にすると枠からはみ出すので 13 のままにした（上下に積む組み替えは、ほかのページの図の方針が決まってからでよいと判断した）。描画の道具が手元にないので、座標の計算だけで確かめた。メインか検証役で描画を確かめてほしい
- 指摘 8：採らなかった（本文は直していない）。TDPC N の制約は執筆者の手元で確かめられる資料がなく、本文の記述は誤りではない。メインが制約を確かめ、$O(N^2)$ で足りるなら「制約が小さいので根ごとのやり直しでも間に合う」の 1 文を足すことを提案する。tdpc_tree の checked もメインの判断に任せる
