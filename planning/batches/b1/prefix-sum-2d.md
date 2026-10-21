# prefix-sum-2d の報告と提案（工程8b・b1）

- 書いたファイル：docs/basics/prefix-sum-2d.md、snippets/prefix-sum-2d/rect-sum.{cpp,yaml}、snippets/prefix-sum-2d/periodic.{cpp,yaml}、docs/img/prefix-sum-2d/build-step.svg・four-terms.svg
- front matter で変えたもの：complexity・stage（draft）・updated。節 `fix-rows`（長方形を全部試す・行の組を固定して 1 次元に落とす、level はページと同じ水）を formula の後に足した
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 2 本とも期待どおり／textlint エラー 0（警告 32 は助詞の重複・数式を含む文の長さ・数式内の `[` の対応の誤検出）／fix_problems --check は本ページの行に指摘なし（event-sort.md の 7 行が未展開と出るが担当外）
- 図：visual は static・priority 2。SVG 2 枚（4 項の包除、前計算の 1 ステップ）。描画系の道具が手元になく、PNG に描いて目で確かめてはいない（座標は手計算で確認）
- 使った出典：参考の節の 7 件（oraclesqlpuzzle・qiita comet725・drken ×4・qiita gotoki_no_joe）。どれも付録 B のドメインで、新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc461_d | summary | グリッドの部分長方形のうち、書かれた値の和がちょうど K になるものの個数を求める。 | https://qiita.com/comet725/items/26d94dac9716a755877f |
| abc461_d | approach | 行の組を固定して列ごとの和を作り、和が K 以下と K−1 以下の区間を尺取りで数えて差を取る | 同上 |

- abc461_d は本文の行を上の summary で書いた（台帳の「（詳細は執筆時に確かめる）」を外した形）。台帳を直して fix_problems を流してほしい
- abc465_f・abc311_e・abc331_d・arc025_2・abc075_d は台帳の summary のまま使った

## 用語集への提案

- なし（半開区間は既存の `half-open-interval` にリンクした）

## 手引きへの提案

- 基礎の分野にある水のページ（今回の prefix-sum-2d）は、§4 の「technique（基礎）」と「technique（水・青・黄）」のどちらの構成に従うかが手引きからは読み取りにくい。今回は指示に従って短めにし、式の導出は 1 節に絞って応用の型を主にした。分野が basics でも level で決める、などの一文があると迷わない
- SVG を目で確かめる道具（rsvg-convert など）が環境にない。図の確認を検証役に任せるなら、その旨を手引きか checklists に書くとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc106_d | M 本の区間のうち、クエリの区間 [p, q] に完全に含まれるものの数（端点 ≤ 500） | 練習（節 intervals-as-points の代表。台帳では event-sort・sweep-line-2d の練習） | https://drken1215.hatenablog.com/entry/2018/09/06/020200 （r ≤ 500 なので 2 次元累積和が想定と記述） |
| abc203_d | N×N の池の K×K の区画の中央値の最小値（判定を 2 次元累積和で行う） | 練習（台帳では fractional-binary-search の例題。ここでは練習として参照） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc203-d.html |

- 節 intervals-as-points は台帳に本ページの問題がないので、問題 ID を出さず型だけを書いた（手引き §13-6）。abc106_d を本ページの練習に足せば節と問題がそろう
- abc475_f（包除原理と 2 次元累積和、1916）は frequency_evidence に挙がっているが、台帳では inclusion-exclusion の練習で summary も未確認のため使わなかった

## 未解決の点

- abc461_d の値の範囲：comet725 氏の記事のコードからはグリッドが 0 と 1 に見えるが、上限（H, W, K）は記事に書かれておらず確かめていない。本文は「値が非負」としか書いていない
- abc331_d のクエリの座標の並び（A, B, C, D のどれが行か）は第三者の解説で確定できなかったので、本文では文字を使わず「両端を含む長方形を半開区間に直す」とだけ書いた
- 確認問題の答えで「2 次元の Sparse Table」に触れた。対応するページは catalog にない可能性がある（リンクはしていない）
- 使用量の目安：道具の呼び出し 約 25 回、Web 取得 10 回

## 検証の指摘への対応（2026-10-21）

- 直すべき：0 件。直すとよい 10 件のうち、1〜8・10 を直した
    - 1：#higher-dimensions の前計算の段落の後に、「自分以下の和」（番兵なし）と半開区間の 8 項の式（番兵つき）の対応を書き足した
    - 2：0-indexed の閉区間の文字を $[l, r]$ にした
    - 3：辺の候補を点の座標に絞るのは「面積の最小のように中の点の集合だけで良し悪しが決まり、縮めても悪くならない」ときに限ると書いた
    - 4：1 次元に並べたとき $c_t = 0$ の要素では足さないこと、軸ごとに長さが違うときの読み替えを添えた
    - 5：dp-grid#largest-square・sweep-line-2d#intervals-as-points・fenwick-tree#variants（2 か所）へのリンクにした
    - 6・7：2 つの SVG を幅 420 の縦長にし、凡例と式を図の下に回した。縦軸のラベルは回さずに「行 i ↓」を左上に横書きで置いた
    - 8：使い分けの節を力試しの後・参考の前に移した
    - 10：periodic.cpp の core で、下端の帯と右端の帯の行を本文の順に入れ替えた
- 9（abc106_d を台帳に足す）は共有ファイルの直しなので、ここでは直さず提案に回す。参考の ABC106 D の行は節の型の裏付けとして残した

### メインへの提案（指摘 9）

- abc106_d を本ページ（prefix-sum-2d）の練習として台帳に足し、節 intervals-as-points から引けるようにしてほしい。summary は台帳の alternatives にある sweep-line-2d のものが使える。足したら本文の #intervals-as-points の節に問題名を出し、練習問題の一覧へ加える（執筆者で対応できる）
