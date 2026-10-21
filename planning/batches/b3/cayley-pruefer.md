# cayley-pruefer の報告と提案（b3）

- 書いたファイル：docs/comb/cayley-pruefer.md、snippets/cayley-pruefer/count.{cpp,yaml}、snippets/cayley-pruefer/max-diameter.{cpp,yaml}、docs/img/cayley-pruefer/degree-sequence.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（2 件とも期待どおり。どちらも N ≤ 7 の全探索と assert で照合）、textlint（エラー0・警告17。数式を含む文の長さ・読点、図の代替テキスト、折りたたみ内の箇条書きによる誤検出）
- 図：degree-sequence.svg を render_svg.py で 360px・720px にして目で確かめた（720px の PNG は撮影の高さで下端の注記が切れるが、360px では全体が見え、SVG 自体は正しい）
- 使った出典：drken1215.hatenablog.com の 3 記事（2020/10/25/132900・2023/05/28/010200・2020/10/25/140600）、cirrostratus.hatenablog.com/entry/2023/03/05/163234
- 新しく noai を確かめたドメイン：cirrostratus.hatenablog.com（check_noai で指定なし。付録 B への追加を提案）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc290_f | approach | 次数列を決めたときの直径の最大値（次数 2 以上の頂点の数 + 1）を求め、葉の数の寄与に分けて二項係数の閉じた式にする（木の個数の式は使わない） | https://cirrostratus.hatenablog.com/entry/2023/03/05/163234 （直径の観察と閉じた式。和は次数列にわたり、木の数を掛けない） |
| abc290_f | evidence | 上の cirrostratus の記事を追加（ikatakos.com は 2026-10-21 にメンテナンス中で 503 だった） | 同上 |
| abc290_f | checked | 2026-10-21 | 同上で問いを確かめた |
| abc303_h | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2023/05/28/010200 で問い（次数が集合 S に入るラベル付き木の数、N ≤ 2×10^5）を確かめた |
| arc106_f | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2020/10/25/140600 で問いと答えの式を確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| ラベル付き木 | labeled-tree | 頂点に 1〜N の番号を付けて区別した木。辺の集合が違えば別の木として数え、形が同じでも番号の付き方が違えば別物になる。 |
| 多項定理 | multinomial-theorem | (x_1 + … + x_m)^n を展開したときの x_1^{a_1} … x_m^{a_m} の係数が多項係数 n!/(a_1! … a_m!) になるという定理。 |

（本文ではどちらも用語集へリンクしていない。多項定理は multinomial-coefficient#meaning へリンクした）

## 手引きへの提案

- なし。comb の「mod の値は大小比較できない」は落とし穴の「木があるかを数え上げの値で判定しない」で扱った

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL | 備考 |
| --- | --- | --- | --- |
| nyc2015_5 | 完全グラフの全域木のうち、各頂点の次数が指定どおりのものの数を 10^9+7 で割った余りで求める | https://drken1215.hatenablog.com/entry/2020/10/25/132900 | ap.py で実在を確認（E. ひも、difficulty なし、2015-01-04）。次数を指定した木の数の式をそのまま使う代表なので、練習（degree-sequence）に向く。ABC ではない |

- 練習の候補は ABC から見つからなかった。ap.py で題名に Tree・Degree・Spanning・Labeled・Forest を含む 1500 以上の問題を見たが、Cayley の公式・次数を指定した木の数を主に使うと第三者の解説で確かめられたものはなかった（abc253_h は行列木定理、abc359_f は tree-degree の例題）
- 現状は例題 1・力試し 2・練習 0 で、練習の目安（2〜6）を満たしていない

## 未解決の点

- 例題 abc290_f は catalog の representative だが、実際の解法は「次数列の数え上げ（重複組合せ）と木が作れる条件」で、木の個数の式（Cayley・多項係数）は使わない。本文ではこのページの節「次数列ごとに数えて総和を取る」で「和が次数列にわたる場合」として位置づけた。このページの例題として残すか、tree-degree や binomial-identities の例題に移すかはメインの判断に任せる
- 連結成分をつなぐ式 N^(k−2) Π s_i、頂点 v の次数が k の木の数、根付き木 N^(N−1)、葉になる木 (N−1)^(N−2) は、出典の記事に直接は書かれていない標準的な事実で、snippets の全探索（N ≤ 7）で確かめた（根付き・葉の式は全探索していないが、Prüfer 列からの直接の数え方を本文に書いた）
- 発展の節の計算量（FPS の累乗 O(N log N)、繰り返し二乗法と畳み込み O(N log^2 N)、分割統治 O(N log^2 N)）は fps-basics・generating-function-counting が draft になったら照らしてほしい
- counting-bijection の申し送り（Prüfer 列の事実の照合）：counting-bijection#classic-bijections の記述（n^{n−2}、次数 − 1 回、(n−2)!/Π(d_v−1)!、条件外は 0）は本ページと食い違いがない
- tree-degree#counting-links はこのページを「ラベル付き木の数と Prüfer 列」と呼んでいるが、題名は「ラベル付き木の数え上げ」。メインで題名に合わせるとよい

## 使用量の目安

- 道具の呼び出し 約 40 回、Web 取得 6 回（うち 1 回はメンテナンス中で失敗）、Web 検索 3 回

## 検証の指摘への対応（b3）

- 指摘 1（直すべき）：#with-polynomials の「頂点ごとに条件が違う」に、各 F_v の次数の合計が O(N)（例：次数の上限 D_v の合計が O(N)）という条件と、満たさないと Θ(N^2) になることを足した。要点と complexity は「多項式の累乗で数える」（全頂点で同じ条件）の値なので変えていない
- 指摘 2：count.cpp の印 core を trees（count_trees）と degrees（count_with_degrees）に分け、degrees は #degree-sequence の計算の段落の後で取り込んだ。Cayley の節の assert の文も合わせた
- 指摘 3：成分をつなぐ式の段落に、k 頂点の木への当てはめ（指数 k − 2）と Σ s_i = N を明記した
- 指摘 4：図の副題と最下段の注記を省き（本文と代替テキストにある）、文字を 17〜18px、頂点の円を r = 20 に上げた。360px の PNG で読めることを確かめた
- 指摘 5：(a) abc290_f は現在の位置づけ（「和が次数列にわたる」型）のまま残した。例題を移すかはメインの判断。(b) 練習 0 問は、台帳への追加が要るので直していない。提案は下記

### 提案（共有ファイル）

- data/problems.yaml：nyc2015_5（E. ひも）を足し、このページの練習（anchor: degree-sequence）に置く。裏付けは drken のプリューファーコードの記事（上の「問題の補充の候補」）。追加されたら本文の練習の節を書く
- data/problems.yaml：abc290_f の approach の「次数列を決めたときの木の数と直径を式にし…」を、木の数は使わず「木が作れる次数列（正の整数で和 2N−2）の数と直径の最大値 = 次数 2 以上の頂点数 + 1 を寄与に分けて二項係数で閉じる」旨に直す
- data/problems.yaml：abc303_h の checked に 2026-10-21 を入れる（drken の記事で問いを確認済み、検証役も同意）
- tree-degree#counting-links のこのページの呼び名を題名「ラベル付き木の数え上げ」に合わせる
