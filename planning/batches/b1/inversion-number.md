# inversion-number の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/inversion-number.md、snippets/inversion-number/{count,shift,window}.{cpp,yaml}、docs/img/inversion-number/inversions.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（このページは直すべき行 0。実行時点で ds/kth-element.md に別の執筆者の 1 行が残っていた）、check_snippets（3 件すべて一致。どれも素朴な方法の結果と assert で照合）、textlint（エラー 0・警告 15。数式の半開区間 $[l, r)$ を括弧の対と誤検出する no-unmatched-pair と、それに引きずられた sentence-length・max-comma、数式を含む文の max-comma）
- 動く図：作っていない。catalog の visual は static・priority 2 なので、SVG 1 枚（棒グラフと転倒している組を点線で結ぶ）と、BIT に左から入れていく様子の表（本文の Markdown の表）で代えた
- 使った出典：ACL document_ja（fenwicktree）、vain0x（note。check_noai で noai の指定なし。記事に利用条件の記載はなかった）、kmjp（abc190_f）、cnblogs cutelxy（abc452_f）、kcpc.hatenablog.com（abc396_f。新しく check_noai で確かめた：noai の指定なし）、kyo-pro（abc261_f）、ikatakos（abc479_f。解法の節だけを要約させて読んだ）、drken（abc380_g）。abc264_d・abc378_e・arc075_c の方針は台帳の approach と研究の記録に従い、evidence の drken の記事は今回は開いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc479_f | summary（pages と alternatives の両方） | 数直線上に並ぶ人々を、隣と位置を入れ替える操作のくり返しで目標の配置にするための最小の操作回数を求める。（本文はこの文で書いた） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/1011_abc479 （解法の節） |
| abc479_f | approach（inversion-number） | 人のいない座標に仮の人を置くと操作は隣接 swap になり、目標の並びの番号に置き換えた列の転倒数が答え。仮の人どうし・人と仮の人・人どうしの組に分けて数え、人どうしは BIT | 同上 |
| kcpc.hatenablog.com | 付録 B | 確かめたドメインに足す（noai の指定なし、2026-10-21） | check_noai.py の結果 |

ほかの使った問題（abc190_f・abc452_f・chokudai_S001_j・abc396_f・abc261_f・abc380_g）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- 転倒｜inversion｜列の 2 要素の組で、前にある方が真に大きいもの。転倒している組の個数が転倒数。（本文ではリンクしていない。ページがあるので不要なら足さなくてよい）
- 隣接 swap｜adjacent-swap｜列の隣り合う 2 要素を入れ替える操作。1 回で転倒数がちょうど 1 増減する（等しい値どうしなら変わらない）。

## 手引きへの提案

- §13.1 は落とし穴・使い分けを定型の節（`{#pitfalls}`・`{#comparison}`）として sections に載せないとしているが、このページの catalog の sections には `pitfalls` と `choosing` が中身の節として入っている。既存の anchor を変えない規則に従い、見出しは sections の title のまま（`## 落とし穴（…） {#pitfalls}`・`## 使い分け（…） {#choosing}`）にした。ほかのページと揃えるなら、メインで sections から外すか、手引きに「catalog に載っている場合は anchor をそのまま使う」と足してほしい
- 基礎でない水のページで、`prerequisites` の BIT（fenwick-tree）がまだ stub。本文の「ACL では」の囲みに fenwick_tree の宣言を短く書いたので、BIT のページと重なる

## 問題の補充の候補

- typical90_ck（089. Partitions and Inversions（★7）、diff なし。台帳にない）：各部分の転倒数が K 以下になる列の分割の数を求める。尺取り＋BIT で各右端の左端の限界を求め、累積和で DP する（sliding-window 節の発展の練習）。裏付け：https://emtubasa.hateblo.jp/entry/2021/07/11/192251 （research/05-ds の記録。今回は開いておらず、ドメインの noai も未確認）
- arc101_b（D. Median of Medians、diff 2073。台帳にない）：すべての連続区間の中央値を集めた列の中央値を求める。答えを二分探索し、±1 の累積和の大小の組を BIT で数える（reformulation 節の力試し）。裏付け：https://drken1215.hatenablog.com/entry/2018/09/08/011500 （research の記録。今回は開いていない）
- typical90_q（017. Crossing Segments（★7）、diff なし。台帳にない）：円周上の点を結ぶ線分のうち交差する組の数を数える。端点でソートし BIT で数える（転倒数型の数え上げ）。裏付け：https://kaage.hatenablog.com/entry/2021/04/21/235030 （research の記録。今回は開いておらず、ドメインの noai も未確認）
- abc319 以降の水の練習が abc378_e・abc396_f の 2 問で、どちらも差分・言い換えの型。BIT で数えるだけの易しい abc319 以降の問題があれば足したいが、今回は ap.py の題名検索だけでは見つけられなかった

## 未解決の点

- abc479_f の問い（summary）は ikatakos 氏の記録の解法の節から組み立てた。「隣と位置を入れ替える」が人どうしの入れ替えも許すのか（人は空きにだけ動くのか）は確かめきれていない。仮の人を置くと隣接 swap になるという解法の筋とは矛盾しないが、検証役に確かめてほしい
- chokudai_S001_j の制約（N の上限・値の範囲）は vain0x 氏の記事に書かれておらず確かめられなかった。本文では「値が大きいときは座標圧縮する」と一般論で書いた
- 図 inversions.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算（弧の最下点 294、説明文の基線 320）だけを確かめた。文字のはみ出しの確認を検証役に頼みたい
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 7 回
