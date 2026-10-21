# divide-and-conquer（分割統治）の執筆の報告

- 書いたファイル：docs/basics/divide-and-conquer.md、snippets/divide-and-conquer/{merge-inversion,split-at-max,range-knapsack}.{cpp,yaml}、docs/img/divide-and-conquer/{recursion-tree,range-knapsack}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 構成：level 黄・type technique なので §4 の黄の technique の目安（§14-6）に従った。中身の節は sections の 5 つで、各節の末尾に応用の型を置いた
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 3 件とも期待どおり、textlint エラー 0（警告 33：数式の中の括弧の対応・数式を含む文の長さ・助詞の重なりの誤検出。§13-8）
- 図：SVG 2 枚を render_svg.py で 360px・720px の PNG にして目で確かめた。visual は priority 2（static）なので、動く図は作っていない
- コード片：split-at-max.cpp は小さい乱数の列 3000 個で素朴なシミュレーションと比べて assert し、range-knapsack.cpp は全クエリを区間ごとの素朴な DP と比べて assert する

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc451_g | pages から divide-and-conquer（challenge）を外す | xor-basis の practice だけにする | kmjp 氏の解説（https://kmjp.hatenablog.jp/entry/2026/03/28/0930）は全域木・XOR 基底・Trie で解いており、分割統治を使っていない。台帳のもう 1 つの evidence（ikatakos 氏の記録）は 503 で読めず、分割統治の使い方を確かめられなかった。役割を確かめられないので、本文には載せなかった |
| abc426_g | evidence に足す | https://kmjp.hatenablog.jp/entry/2025/10/06/1000 | ikatakos 氏の記録が 503 で読めず、kmjp 氏の解説で問いと方針（中央をまたぐクエリを左の接尾辞と右の接頭辞の表で答える）を確かめた |
| abc426_g・arc189_d・chokudai_S001_j | checked | 2026-10-21 | 上の解説と、drken 氏・vain0x 氏の記事で問いを確かめた |
| arc189_d | approach | 区間の最大値の位置（同じ値なら最も左）で左右に分ける分割統治。区間の和と親の値を比べ、親から子へ最終的な大きさを渡す | 本文の解法の詳細と同じ。同じ値の最大値が並ぶ場合の扱いを含めた |

## 問題の補充の候補（問題 ID・何を問うか・裏付けの URL）

練習が chokudai_S001_j の 1 問しかない（catalog の problems_note のとおり）。ap.py で実在と difficulty を確かめ、第三者の解説で分割統治で解けることを確かめた候補。

| 問題 ID | diff | 役割の案 | 何を問うか | 使う節 | 裏付け |
| --- | --- | --- | --- | --- | --- |
| keyence2019_e | 2623 | 力試し | 一列に並ぶ都市の完全グラフで、辺 $(i, j)$ の重みが $D \lvert i - j \rvert + A_i + A_j$ のときの最小全域木の重みを求める | crossing（番号で半分に分け、またぐ辺の候補を各側の代表 1 点との辺だけに減らして $O(N \log N)$ 本にする） | https://drken1215.hatenablog.com/entry/2019/01/15/081500 （解法 1 が分割統治。台帳では centroid-decomposition の challenge で、summary は（執筆時に確かめる）。summary の案：「一列に並ぶ都市を結ぶ完全グラフで、辺の重みが番号の差と両端の値で決まるときの最小全域木の重みを求める。」） |
| abc282_h | 2621 | 力試し | 2 つの列 $A$・$B$ で、区間の $A$ の最小値と $B$ の和の合計が $S$ 以下になる区間の個数を求める | split-at-max（最小値の位置で分け、短い側の端点を全部試して長い側を累積和の二分探索で数える。$O(N \log^2 N)$） | https://kmjp.hatenablog.jp/entry/2022/12/18/0930 （台帳にない） |

どちらも 2600 台で、黄のページの力試しとしては難しい。練習に置ける黄までの ABC の問題は見つけられなかった（drken 氏の「分割統治法」の分類の ABC の問題は 2400 以上で、多くは分割統治 FFT）。

## 用語集への提案

なし（再帰木 `recursion-tree`・オフライン `offline` は既存の anchor を使った）。

## 手引きへの提案

- §4 の基礎の構成と、basics の field で level が黄のページの扱い：指示文には「基礎のページは短く、応用の型・落とし穴・上位の手法とのつながりに絞る」とあったが、§14-6 により level 黄・technique の構成に従った。上位の手法へのつながりは、sections の other-fields の節で兼ねたので、定型の `## 上位の手法へのつながり {#next-steps}` は置かなかった

## メインへの申し送り（リンクの張り替え）

このページが draft になったので、次のリンクを節へ張り替えられる。

- docs/dp/knapsack-01.md:217 と docs/dp/knapsack-undo.md:148・218 → `../basics/divide-and-conquer.md#range-knapsack`（b2 の knapsack-undo の検証の指摘 6）
- docs/ds/monotonic-stack.md:298 → `#split-at-max`
- docs/ds/sparse-table.md:61 → `#split-at-max`、:145 → `#range-knapsack`（中点をまたぐ区間を中点からの累積で扱う考え方）
- docs/ds/inversion-number.md:133 → `#crossing`
- docs/basics/recursion-structure.md:156 → `#crossing`

## 使った出典

- drken1215.hatenablog.com（arc189_d・keyence2019_e）、kmjp.hatenablog.jp（abc426_g・abc478_g・abc451_g・abc282_h）、note.com の vain0x 氏の記事（chokudai_S001_j。inversion-number で確かめ済みのものを参考に挙げた）、www.luogu.com.cn の記事 xj49grtm（abc426_g の制約の見当だけ。本文の参考には入れていない）。どれも付録 B にあるドメイン
- ikatakos.com の abc426・abc451 の記録は HTTP 503 で読めなかった

## 未解決の点

- abc426_g の制約：解説の本文に制約の記載がなく、kmjp 氏と luogu の記事のコードの配列の大きさから $C \le 500$・$N$ は $2 \times 10^4$ 程度・$Q$ は $2 \times 10^5$ 程度と見当を付けた。本文には「容量の上限 $C$ が数百と小さい」とだけ書いた。台帳か検証役が確かめられれば数を書ける
- abc451_g の分割統治の役割（上の台帳への提案）。ikatakos 氏の記録が読めるようになれば確かめ直す
- frequency_evidence の「recent 2（abc451_g・abc478_g）」は abc451_g を外すと 1 になる
- 使い分けの表の「戻す DP と区間の出し入れ」は、取り除ける DP なら Mo's algorithm などで区間を出し入れできるという趣旨。Mo のページへのリンクは付けていない

## 検証の指摘への対応（b3 の直し）

指摘 1〜8 はすべて採った。

- 1（ARC189 D の段落）：「区間の外のすぐ隣はどちらも $A_m$ 以上」という $m$ についての主張に書き直した
- 2（短い側だけを試すときの計算量）：長い側を $O(1)$ で数えれば $O(N \log N)$、二分探索なら $O(N \log^2 N)$ と分けた。応用の型の 1 つ目にも $O(N \log^2 N)$ を書いた
- 3：「長さ 1 の区間（葉）を除くと」を足した
- 4：kmjp 氏の abc478_g の記事と vain0x 氏の記事の題名を記事のとおりにした（著者の表記は inversion-number に合わせて vain0x のまま）
- 5：図を 2 枚とも作り直した。recursion-tree は幅 480 にし、段の説明の列を図の下の短い注記にまとめた（文字 16〜18px）。range-knapsack は幅 480 にし、品物を番号だけにして、下の 2 行の注記（本文・代替テキストにある）を省いた（文字 16〜18px）
- 6：split-at-max は Sparse Table を core の外の `ArgMax` に移し、core は本体だけにした。`bit_width` は core の外になったので C++ の章へのリンクは付けていない。本文に「構築の部分は省いた」と書いた。range-knapsack の `int n;` は core の外へ出した
- 7：手順 2 に空の表を 0 で始めること（「以下」の意味になる理由）を足し、コード片の前に `tab` の行と $L$・$R$ の対応を 1 文足した
- 8：応用の型の 3 つ目から ABC478 G の名前を外した

共有ファイルへの新しい提案はない（台帳の提案は上のとおり）。
