# s10 2巡目：共有ファイルの直し（台帳・道具・prh・付録 B）

decisions.md・left-shared.md・verify-shared.md のうち、台帳・道具・prh・手引きの付録 B に要るもの。commit はしていない。gen_site.py は `--check --diff` だけ実行した（書き込みはメイン）。atcoder.jp・codeforces.com は開いていない。

確かめたこと（2026-10-22 の作業ツリー。ほかの担当の直しも並行して入っている）：

- `python3 tools/check_pages.py`：エラー 0、警告 35（すべて新しく足した「同じ URL の出典の題名が違う」。§17-10 のそろえは後の担当）
- `python3 tools/fix_problems.py --check`：直すべき行 0・直せない行 0・逆向きの警告 0
- `npx textlint`（触ったページ 12 枚：inclusion-exclusion・counting-mindset・counting-labeled-graphs・counting-dedup・warshall-floyd・euler-path・extended-dijkstra・bit-dp・merge-process-tree・parallel-binary-search・partially-persistent-union-find・glossary）：エラー 0（警告は前からある助詞の重なりなど。足した行の文の長さの警告は文を分けて消した）
- 図・コード片は変えていない（check_svg・check_snippets は不要）

## 1. 台帳 data/problems.yaml

1. **「歩道」→「ウォーク」**：台帳の 6 か所（abc197_f・abc244_f・abc338_f の本体と alternatives、abc394_e）。本文の問題の行 5 か所（warshall-floyd L272、euler-path L180、extended-dijkstra L354・L374、bit-dp L241）も直した（fix_problems は要約を変えないので手で直した）
2. **abc180_f の「サイクル」→「閉路」**：台帳の本体と alternatives 2 つ、本文 3 ページ（counting-labeled-graphs L233・counting-mindset L255・counting-dedup L205）
3. **abc180_f の事実の食い違い**：counting-mindset の行が「単純無向グラフ」で、方針が「閉路は k ≤ 2 で 0 通り（多重辺になるので）」だった。drken 氏の記事（2020/10/21）で「自己ループは許さず多重辺は許す。大きさ 2 の閉路は 1 通り」を確かめた。台帳と counting-dedup・counting-labeled-graphs はこれに合っていたので、counting-mindset の行を台帳の形（「自己ループのない（多重辺は許す）…」）にし、方針を「閉路は k = 1 で 0 通り（自己ループ）、k = 2 で 1 通り（多重辺の 2 本）」に直した
4. **agc002_d の summary**：「x と y を含む成分の頂点数（同じ成分なら 1 回）が z 以上になる最小の t」に、台帳の本体と alternatives 2 つと本文 3 ページ（merge-process-tree L149・parallel-binary-search L145・partially-persistent-union-find L147）をそろえた
5. **abc116_c を difference-sequence の pages から外した**（§17-12）。pages は空になったので `pages: []` にし、note に外した日と理由を書いた（本文には載っていなかった）
6. **abc130_e を dp-prefix-sum の pages から外した**（§17-12）。lcs・counting-dedup の練習は残る。note を足した
7. **abc467_f**：ikatakos 氏の「AtCoder Beginner Contest 467 E,F問題メモ」（evidence にある。付録 B で確かめた ikatakos.com）で問いと解き方を確かめた。summary を「各メールに書く時間 A_j と返信までの時間 B_j があり、A・B の 1 点更新のたびに…すべての返信が届く最小の時刻を答える」、approach を「B の大きい順が最適（交換論法）、答えは先頭からの A の和 + B_i の最大、B を座標圧縮したセグメント木に（A の和, その最大）を載せる」にし、checked を 2026-10-22 にした
8. **abc475_f**：ikatakos 氏の「AtCoder Beginner Contest 475 E,F,G問題メモ」（evidence にある）で確かめた。問いは「白黒のマス目で長方形を 1 つ選んで黒く塗る操作を高々 1 回行うとき、できる盤面の数」。解き方は「4 辺のどれも全部が黒ではない長方形 + 1」を、4 辺の条件で包除して数える（T0 − T1 + T2 − T3 + T4 + 1。T4 が O(H^2 W)、H ≤ W に転置）。記事は 2 次元累積和を使っていない（列方向の累積和）ので、approach の「2 次元累積和」を直した。checked を 2026-10-22 にした
9. **abc458_e・abc479_d・abc479_e は確かめられなかった**：ikatakos 氏の記録（ABC458 は F・G、ABC479 は F・G だけ）、Konini64 氏の Qiita の記録（ABC458 は E を解いていない、ABC479 の D は方針だけで問いを書いていない、E は扱わない）、kmjp 氏のブログ（ABC479 は G だけ、ABC458 は記事が見つからない）を探したが、問いを書いた第三者の解説がない。status は未確認のまま、pages から外し（fix-variable・prefix-sum・tree-edge-contribution の練習。どれも本文には載っていなかった）、note に探した資料と「確かめたら pages にも戻す」を書いた。summary の「（執筆時に確かめる）」は未確認の印として残した
10. **abc365_g の evidence**：HTTP 403 で確かめられない suzukiapple.tumblr.com を、ページの担当が出典に替えた ikatakos 氏の「トヨタ自動車プログラミングコンテスト2024#8（AtCoder Beginner Contest 365）G問題メモ」に替えた（記事で問いと、記録の多い人を基準にした前計算・イベント順の処理の切り替えを確かめた）

## 2. 本文の囲み（4 か所）

- **inclusion-exclusion の練習に abc475_f を足した**：囲みの行（fix_problems --page で作った）、練習の方針（辺がすべて黒の長方形が小さい長方形と同じ盤面になること、4 辺のどれにも白がある長方形は白いマスを囲む最小の長方形で決まるので重ならないこと、4 辺の包除、黒の連続の長さと累積和、O(H^2 W)）、参考に ikatakos 氏の記事の行
- **exchange-argument の力試し（abc467_f）・slope-trick の力試し（abc458_g）・spanning-tree-advanced の練習（keyence2019_e）**：並行しているページの担当がすでに囲みの行と方針と参考を足していたので、重ねて書いていない。中身は台帳と出典に合うことを読んで確かめた（abc467_f の隣接交換の式、abc458_g の 3 つの遷移とスタックの持ち方、keyence2019_e の候補の辺を O(N log N) 本に絞る方針）

## 3. prh.yml（§17-8）と用語集の表

- 足した規則：`多重テストケース→複数テストケース`・`歩道→ウォーク`・`上位ビット/最上位ビット/最下位ビット→… bit`・`平衡二分木→平衡二分探索木`・`フェニック木→BIT`・`0 始まり/1 始まり→0-indexed/1-indexed`
- 「0 始まり」と「… ビット」は、後ろに語が続くときに半角と全角の間の空白を足す規則と、句読点・括弧が続くときの規則の 2 つに分けた（1 つの規則では prh の specs が「0-indexedの添字」のように空白を落とす）。「10 始まり」は直さない（先読みで除いた）。specs を 13 件書き、一時ファイルで textlint と `--fix` の結果を確かめた
- prh.yml の冒頭の約束（規則を足したら用語集の表にも行を足す）に従い、docs/guide/glossary.md の正規形の表に「0 始まり・1 始まり」「複数テストケース｜多重テストケース」「上位 bit・最上位 bit・最下位 bit｜上位ビット・…」「ウォーク｜歩道」「BIT｜フェニック木」「平衡二分探索木｜平衡二分木」を足した
- 本文に残る該当の語（2026-10-22 の時点で 11 ファイル・22 か所。term-index・wavelet-matrix・fenwick-tree・balanced-bst・bitwise-independence・bit-operations と生成物）はページの担当が直す。生成物（docs/*/index.md・lists・reverse-index-signs の表）は front matter の summary・signs から作られるので、ページを直して gen_site を流せば消える

## 4. tools/check_pages.py の警告

足した警告（`check_conventions`。冒頭の説明にも書いた）：

1. **定型の節の見出しと anchor**：`## 例題`・`練習問題`・`力試し`・`確認問題`・`使い分け`・`落とし穴`・`参考`・`学ぶための資料` の見出しの anchor が定型と違う（ない）とき、定型の anchor が別の見出しに付いているとき。例外は roadmap の `practice`（§17-3）
2. **sections に定型の節**：sections に上の 8 つの anchor があるとき
3. **guide・hub・pattern の complexity**：null でないとき（§17-1）
4. **発展の概要の定型の節の欠け**：stage が draft 以降の overview に `## … {#library}`・`{#resources}` がないとき。two-sat は `acl` を library の代わりに認める（§17-3）
5. **同じ URL の出典の題名が違う**：参考と学ぶための資料の節の「- [題名](URL)」を全ページで集め、URL が同じで題名が 2 つ以上あるとき（§17-10）。今は 35 件（洗い出しのときの 124 件から、並行の直しで減っている）

試験：一時置き場（scratchpad/s10b/t）に cht.md と glossary.md を写して、例題の anchor を `ex` に、学ぶための資料の anchor を消し、使い分けの見出しを「選び方」に、sections に practice を足し、glossary の complexity を O(1) にし、同じ URL に違う題名の出典を 2 ページに置いた。7 件の警告がそれぞれの種類で出ることを確かめた。今の docs では 1〜4 は 0 件

## 5. tools/gen_site.py

- ロードマップの位置ごとの表の見出し「G 問題（黄の帯）」を「G 問題（黄・発展の帯）」にした（`POSITION_LEVEL`）。recent-abc.yaml の G 30 問は黄 12・発展 14・青 4 問。anchor `recent-positions-g` は変えない。`--check --diff` でこの 1 行だけが変わることを確かめた（作り直しはメイン）

## 6. 付録 B と出典の差し替え先

- **miti-7.hatenablog.com**・**fairy-lettuce.hatenadiary.com**：check_noai --robots で、どちらも HTTP 200、robots の meta は `max-image-preview:large` だけ、X-Robots-Tag なし、robots.txt に AI 向けの指定なし。fairy-lettuce を付録 B のはてなの行に足した（miti-7 は前から載っている）
- **trap.jp**：証明書の検証を外して check_noai と同じ方法で取得しようとしたが、この環境の権限の判定で断られたので行っていない。検証つきの check_noai をやり直すと、トップページ（https://trap.jp/）は 1 回 HTTP 200 で取得でき、robots の meta と X-Robots-Tag に noai・noimageai はなかった。記事 4 本（post/2589・2861・1224・1594）は HTTP 503 か「自己署名の証明書」で検証に失敗し、取得できなかった（503 の応答にも指定はないが、エラーの応答なので判定に使っていない）。付録 B にこの結果を書いた。**メインに判断してもらうこと**：noai の指定はふつうサイト全体の設定なので、トップページで指定がないことを根拠に残すか、記事を取得できるまで待つか。証明書の検証を外して確かめるなら、ユーザーの許可が要る
- **doi.org**（union-find-applications L293）：差し替え先は書誌情報だけの出典。ページの担当がすでに「Tarjan, van Leeuwen「Worst-case Analysis of Set Union Algorithms」（Journal of the ACM 31(2), 1984, pp. 245–281, doi:10.1145/62.2160）」とリンクなしの形にしている。この形でよい（巻・号・ページ・DOI は記憶ではなく既にあった DOI と一致する書誌情報）
- **suzukiapple.tumblr.com**（sqrt-decomposition L259）：差し替え先は ikatakos 氏の「トヨタ自動車プログラミングコンテスト2024#8（AtCoder Beginner Contest 365）G問題メモ」（https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0803_abc365。h1 を確かめた）。ページの担当がすでにこの行に替えている。台帳の evidence も替えた（1 の 10）
- **hashing-for-sets の trap.jp post/1594**：ページの担当が出典から外していた。付録 B の使っているページを 3 つに直した

## 残したもの

- 出典の題名のそろえ（35 件）：check_pages の警告で一覧できる。そろえるのは後の担当
- 本文に残る prh の新しい規則の該当（3 の最後）：ページの担当
- abc458_e・abc479_d・abc479_e：問いを書いた第三者の解説が出てきたら、status と pages を戻す
- trap.jp の判断（6）
- tools/README.md の check_pages の行には新しい警告を書いていない（docstring に書いた）。メインが README をまとめて直すときに足すとよい
