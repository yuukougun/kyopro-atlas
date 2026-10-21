# sweep-line-2d の報告（b2）

- 書いたファイル：docs/ds/sweep-line-2d.md、snippets/sweep-line-2d/rectangle-sum.{cpp,yaml}・window-max.{cpp,yaml}・union-area.{cpp,yaml}、docs/img/sweep-line-2d/rectangle-prefix.svg・window-to-rectangle.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は rectangle-count の title を「支配点の数え上げと長方形内の点の数」に短くした（anchor は同じ。見出しも同じ文字）。catalog にあった choosing は手引き §14-2 に従い定型の `## 使い分け {#comparison}` にした（骨格の時点で sections から外れていた）
- 構成：青の technique（§4）。必要になる場面・処理の流れ・計算量は idea の節で兼ねた（§14-5）。応用の型は各節の末尾、ACL の囲みは rectangle-count（fenwick_tree）と window-max（lazy_segtree）に置いた
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0（3 本。どれも main で素朴な数え上げと assert で照らし合わせる。手元で乱数 300 件ずつも照らし合わせた）、textlint エラー 0・警告 42（数式の中の角括弧・読点、数式を含む文の長さ、要点の囲みの長い行、図の代替テキスト。誤検出として残した。「に」の重なりのうち数式でないものは直した）
- 図：rectangle-prefix.svg（長方形 [3, 7) × [2, 6) を x < 7 の帯と x < 3 の帯の差で数える。斜線・色・破線で区別）、window-to-rectangle.svg（点 (5, 4) を覆う枠の角 (s, L) が D × W の長方形になる）。render_svg.py で 360px・720px を目で確かめた。visual は priority 2 の static なので動く図・div は置いていない

## 使った出典

- https://drken1215.hatenablog.com/entry/2023/11/11/010900：例題 abc327_f（制約はどれも 2×10^5 まで、時刻の窓の走査、区間加算・最大の遅延セグ木、半開区間、O(N log M)）
- https://inamori.hateblo.jp/entry/2026/10/01/182341：例題 abc477_f（入力は N M Q、N 個の区間、Q 個の長方形。高さの向きに走査し、各列の累計を a + b·y の 1 次式で持つセグ木、答えは 2 時点の差）。**新しいドメイン inamori.hateblo.jp を check_noai.py で確かめた（noai・noimageai の指定なし。meta robots は max-image-preview:large のみ）**
- https://drken1215.hatenablog.com/entry/2018/09/06/020200：練習 abc106_d
- https://drken1215.hatenablog.com/entry/2020/12/20/111600：練習 abc186_f（H, W, M ≤ 2×10^5、2 通りの動きの重なりを BIT で数える）
- https://kmjp.hatenablog.jp/entry/2024/03/23/1000：練習 abc346_g（左端の走査、各値が唯一になる右端の区間、和集合の長さ）
- https://betrue12.hateblo.jp/entry/2019/08/05/212635：力試し abc136_f（座標は互いに異なる、4 象限、包除、BIT 2 本）
- https://drken1215.hatenablog.com/entry/2024/07/06/172000：力試し abc360_f（交差の定義、0 ≤ l < r ≤ 10^9、候補の座標、最大値とその位置を持つ遅延セグ木）
- ACL document_ja（fenwicktree・lazysegtree）、Library Checker の rectangle_sum・area_of_union_of_rectangles（入出力の形）
- 台帳の evidence の ikatakos（2026/0926_abc477）は、作業中ずっと HTTP 503 で読めなかった

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc477_f | summary | 各列で黒いマスが縦にひと続きの区間になっているマス目について、長方形の中の黒いマスの数を多数のクエリで答える。 | inamori の解説のコード（N 個の区間を列ごとに読み、Q 個の長方形の黒マスを数える）。本文の行はこの要約で書いた（§14-16） |
| abc477_f | approach | 行の向きに走査し、各列の「その行より前の黒マスの数」を行の 1 次式として、係数を BIT 2 本（またはセグ木）に持つ。答えは上端と下端の 2 時点の差 | 同上。現行の「遅延セグ木で窓の中のマスを数える」は、確かめた解説（inamori）では一点の置き換えと区間和のセグ木で、遅延伝搬は使っていない。ikatakos の記事は 503 で読めず、遅延セグ木の解き方は確かめられなかった |
| abc477_f | evidence | https://inamori.hateblo.jp/entry/2026/10/01/182341 を足す | 上 |

## 用語集への提案

- 支配点の数え上げ｜dominance-counting｜各点 i について、x 座標も y 座標も i 以下（または未満）の点の数を数えること。一方の座標で並べて、もう一方を BIT で数える。（本文では節の中で定義したので、リンクは張っていない）

## 手引きへの提案

- 付録 A の「平面走査」の別の書き方として「走査線」を本文で使ってよいとするとよい（本文で走査線を何度も使った。今は別名だけにある）

## 問題の補充の候補

- 要らないと判断した。例題 2・練習 3・力試し 2 で目安を満たし、abc319 以降が 4 問（abc327_f・abc346_g・abc360_f・abc477_f）ある
- union-area の節（黄）の例題は台帳にない。Library Checker の area_of_union_of_rectangles を verify に持つので、ABC から 1 問あれば練習に足すとよい（探していない）

## 未解決の点

1. abc477_f の問題の細部（行と列のどちらに区間があるか、制約の数値、閉区間か）は、第三者の解説のコードから読み取ったもので、問題文と照らしていない。本文は軸の向きに依らない書き方にし、制約の数値は書いていない。ikatakos の記事が読めるようになったら、メインか検証役が確かめる
2. 台帳の abc477_f の approach は遅延セグ木だが、本文は 1 次式の係数を BIT 2 本に持つ解き方で書いた（遅延セグ木の解き方は確かめられなかった）。catalog の research（00 §2.3.8）の記述「行を 1 つずつ進めながら列ごとの累計を遅延セグ木で持つ」とは食い違う
3. abc327_f の解説では、記事の文章で時間と位置の幅の文字（D・W）が入れ替わった箇所があるとのこと。本文は台帳の summary（時間幅 D・位置幅 W）に合わせた
4. sections の rectangle-count の title を短くしたので、gen_site の生成部分（problem-sets.md の「支配点の数え上げ・長方形内の点の数（4 つの接頭辞の包除、…）」など）は作り直しで変わる

## 使用量の目安

- 道具の呼び出し 約 40 回、Web 取得 14 回（うち 503 が 3 回）、検索 3 回

## 検証の指摘への対応（b2 verify）

- 1（直すべき）：直した。rectangle-count の 1 段落目に、y の座標圧縮と、同じ x の点をまとめて扱う手順（$x_j \le x_i$ なら全部入れてから読み自分の 1 を引く、$x_j < x_i$ なら全部読んでから入れる。boundaries へのリンク）を足した
- 2：直した。区間の関係の表の下に、「交差する」は $R = p$ を含めていること、ABC360 F は狭義 $L < p < R < q$ で $\le$ を $<$ に直すことを注として足した
- 3：直した。boundaries の「データ構造の向きの境界」の最後の文を、BIT の添字は左端 $L$ で、$[p, \infty)$ は `lower_bound(p)` から末尾までを読む、と具体にした
- 4：直した。rectangle-prefix.svg は凡例と注記を図の下へ移し（幅 640→420）、目盛り・注記を 15px にした。window-to-rectangle.svg は 2 枚を縦に積み（幅 680→340）、下の説明文 2 行は図から外して本文と代替テキストに任せた（D = 3・W = 2 は上の図の見出しに入れた）。代替テキストの「左は・右は」を「上は・下は」にした。render_svg の 360px で目で確かめた
- 5：本文の直しはない。台帳（abc477_f の summary・approach・evidence、abc327_f・abc360_f・abc477_f の checked に 2026-10-21）は共有ファイルなので、上の「台帳への提案」と検証役の提案をメインが反映する
- 6：直した。「区間加算が $O(\log N)$、全体の取得が $O(1)$」にした
- 検査（直した後）：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 42 は前と同じ誤検出）
