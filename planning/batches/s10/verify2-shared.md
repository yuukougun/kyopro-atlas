# s10 2巡目の検証：共有ファイル（道具・台帳・prh・付録 B）

対象：`git diff HEAD tools/ data/ prh.yml planning/style-guide.md` と新しいファイル tools/frequency.py・tests/tools/test_frequency.py。記録は fixed2-shared.md・fixed2-problems.md・fixed2-frequency.md。検証役が確かめた（2026-10-22）。commit はしていない。gen_site.py は `--check --diff` だけ実行した。atcoder.jp・codeforces.com は開いていない。一時ファイルは scratchpad/s10b/ に置いた。

## 結論

誤りは 1 件だけ見つけて直した（台帳の evidence に残っていた trap.jp/post/1594。下の「直したもの」）。ほかは判断（decisions.md・§17）と裏付けに合う。メインに判断を頼みたいことが 2 件ある（最後の節）。

## 1. check_pages.py の新しい警告

一時置き場（scratchpad/s10b/v）に docs・snippets を写し、次のように壊して `--root` で動かした。台帳は本物を使った。

| 壊し方 | 期待 | 結果 |
| --- | --- | --- |
| prefix-sum の `## 例題 {#examples}` の anchor を消す | 見出しと anchor の警告 | 出た |
| cht の `## 練習問題 {#practice}` を `## 練習 {#practice}` に | 定型の anchor が別の見出しにある警告 | 出た |
| bfs の `## 参考` の anchor を `{#refs}` に | 見出しと anchor の警告 | 出た |
| two-sat の `## 学ぶための資料` の anchor を消す | 見出しと anchor の警告と、発展の概要の resources の欠け | 両方出た |
| two-sat の `{#acl}` を `{#acl2}` に | 例外の acl がないので欠けの警告 | 「{#acl}・{#resources} がない」と出た |
| monge の `{#library}` を `{#lib}` に | 発展の概要の library の欠け | 出た |
| segment-tree の sections に pitfalls | sections に定型の節の警告 | 出た |
| roadmap の sections の practice（例外） | 警告なし | 出なかった（例外が効く） |
| patterns/xor の complexity を O(1) に | pattern の complexity の警告 | 出た |
| 同じ URL・違う題名を 2 ページの参考の節に | 題名の警告 | 出た |
| 同じ URL・違う題名を、片方はコードの囲みの中・片方は参考でない節（落とし穴）に置き、題名に `[a]` を含む行も足す | 警告なし | 出なかった |
| cht の related に `segment-tree#zzz-none`（既存の検査） | エラー | エラーが出た |

- 既存の検査を壊していないか：HEAD の check_pages.py（`git show HEAD:tools/check_pages.py` を scratchpad/s10b/mirror/tools に置いた）と今の版を、壊した写しと今の docs の両方で `-v` で比べた。違いは新しい警告の行だけで、エラーと既存の警告は同じ。今の docs では HEAD 版・新版ともエラー 0・警告 0（記録の 35 件の題名の警告は、並行の出典のそろえで 0 になった）
- `--page`・`--field` の絞り込み：題名の警告（複数のページに関わる）も、関わるページで絞ると出る

## 2. tools/frequency.py

- `python3 -m unittest discover -s tests/tools`：9 件とも通る
- `python3 tools/frequency.py --check`：差分 0（台帳の直しのあとでも）
- 独立の計算：frequency.py を使わずに、全ページの front matter・台帳・recent-abc.yaml から recent の数・届くページの数・直接の数・古い ABC の数と A/B/C を計算し直す小さなスクリプト（scratchpad/s10b/indep_freq.py）を書いて、全 301 ページの frequency と frequency_evidence の数と比べた。食い違いは 0（modint の手の A を除く）。内訳は A 76・B 167・C 58
- --write は 2 行だけを書き換える（試験の test_only_two_lines_change と、差分の出たページの git diff で確かめた）
- tests/tools/__pycache__ は .gitignore の対象

## 3. 台帳の変更と裏付け

`python3 tools/ap.py show` で、abc467_f（Email Scheduling Optimization・2052）・abc475_f（Rectangle Filling・1916）・abc365_g（AtCoder Office・2254）・agc002_d（Stamp Rally・2514）・abc180_f（Unbranched・2419）・abc458_e・abc479_d・abc479_e・abc116_c・abc130_e の実在・題名・difficulty が台帳と合うことを確かめた。第三者の資料は check_noai で指定がないことを確かめてから読んだ。

- **abc467_f**：ikatakos 氏の ABC467 E,F 問題メモで、A_j（書く時間）・B_j（返信までの時間）・A・B の 1 点更新・すべての返信が届く最小の時刻、B の降順が最適（隣接交換）、答え = max(先頭からの A の和 + B_i)、B を座標圧縮したセグメント木に（A の和, その最大）を載せること、を確かめた。summary・approach と合う
- **abc475_f**：ikatakos 氏の ABC475 E,F,G 問題メモで、長方形を 1 つ黒く塗る操作を高々 1 回・できる盤面の数、4 辺のどれも全部が黒ではない長方形 + 1、T0 − T1 + T2 − T3 + T4 + 1 の包除、T4 が O(H²W)・H ≤ W に転置、累積和は列方向の 1 次元（2 次元ではない）を確かめた。summary・approach と合う
- **abc365_g の evidence**：ikatakos 氏の記事の h1 が「トヨタ自動車プログラミングコンテスト2024#8（AtCoder Beginner Contest 365）G問題メモ」で、2 人が同時に在室した時間・記録の多い人を基準にした前計算とイベント順の切り替えを確かめた。summary・approach と合う
- **abc180_f**：drken 氏の記事（2020/10/21）で「自己ループは持たない・多重辺は許す・大きさ 2 の閉路は 1 通り」を確かめた。台帳の「自己ループのない（多重辺は許す）」と「閉路」への言い換えは正しい
- **agc002_d**：「x と y を含む成分の頂点数（同じ成分なら 1 回）」は問い（2 人が訪れる頂点の種類の数）に合う。台帳と 3 ページの行がそろっている
- **歩道 → ウォーク**：台帳に「歩道」は残っていない
- **abc116_c・abc130_e**：decisions（§17-12）どおり pages から外れ、note がある。本文にも残っていない（fix_problems --check で台帳にあって本文にない問題 0）
- **abc458_e・abc479_d・abc479_e**：status は 未確認、pages は空、note に探した資料がある。decisions の「確かめられなければ status を未確認にし、pages から外して note を残す」に合う。summary の「（執筆時に確かめる）」は未確認の印として残っている（未確認なので本文の行は作られない）
- `python3 tools/fix_problems.py --check`：直すべき行 0・直せない行 0・台帳にあって本文にない 0

## 4. prh.yml

一時ファイルで textlint を動かし、「多重テストケース・歩道・上位ビット・0 始まり・1 始まり・フェニック木・平衡二分木・最下位ビット」がそれぞれ指摘され、「10 始まり」は指摘されないことを確かめた。prh の specs で設定の読み込みが失敗することもない。aliases と別名の行（balanced-bst・fenwick-tree・bit-operations・bitwise-independence・term-index）は textlint でエラーにならない（aliases は残す判断どおり）。本文の該当は生成物（docs/*/index.md・lists・index・reverse-index-signs）にだけ残っており、gen_site の作り直しで消える。

## 5. gen_site.py --check --diff

40 ファイルが変わる（scratchpad/s10b/gendiff.txt）。中身は次のどれかで、意図どおり。

- POSITION_LEVEL の見出し「G 問題（黄・発展の帯） {#recent-positions-g}」（anchor は同じ）
- ページの summary・signs・sections の直し（ダイクストラ法・ウォーク・上位 bit・0-indexed・すべて・閉区間、steiner-tree・euler-path・degree-sqrt の summary、static-top-tree の別名、cht・dynamic-dp・monge・wavelet-matrix・auxiliary-tree・linear-recurrence-fast の anchor の library への改名。check_pages のリンクの検査はエラー 0）
- frequency の付け直し（graph.json の frequency、roadmap の「必修・準必修・余裕があれば」の列。interval-scheduling・median-absolute が「準必修」→「余裕があれば」、knapsack-undo など）

台帳の evidence は生成物に出ないので、下の直しで差分は変わらない（直す前後の --diff を比べて同じ）。

## 直したもの

- **data/problems.yaml の abc238_g・abc250_e の evidence から https://trap.jp/post/1594/ を外した**。decisions は「取れない記事（hashing-for-sets の post/1594）は出典から外す」で、ページの出典からは外れていたが、台帳の evidence に 2 か所残っていた（付録 B でも記事は取得できていない）。どちらもほかの evidence（ikatakos 氏・drken 氏・merom686 氏）が残る。直したあと check_pages（エラー 0・警告 0）・fix_problems --check（0）・frequency --check（差分 0）・gen_site --check --diff（直す前と同じ差分）を確かめた
- trap.jp/post/2861（abc351_g の evidence）は static-top-tree の出典に残っている記事で、付録 B の trap.jp の判断待ち（fixed2-shared の 6）に含まれるので触っていない

## メインに判断してほしいこと

1. **interval-scheduling・median-absolute の B → C**：手で付けていた B を外したので、roadmap の列が「余裕があれば」に下がる（gen_site の差分に出る）。§17-7 の基準どおりではあるが、区間スケジューリングは定番なので、B に戻すなら台帳に古い ABC の問題を足すか、frequency.py の MANUAL に入れる（fixed2-frequency の記録と同じ論点）
2. **recent-abc.yaml の abc475_f が prefix-sum-2d を指す**（technique「包除原理＋2次元累積和」、note「表の記述どおり」）。evidence の ikatakos 氏の記事は列方向の 1 次元の累積和で、台帳の approach もそれに直った。2 次元累積和でも解けるので誤りとまでは言えず、直していない。外すと prefix-sum-2d の recent が 3 → 2（A のまま）、problem-sets・roadmap の表が変わる
