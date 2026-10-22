# b6（工程9・問題の補充）の反映の記録

- 反映した日：2026-10-22。入力は planning/batches/b6/ の 52 件の報告
- 反映先：台帳 `data/problems.yaml` と、ページの本文の練習（practice）・力試し（challenge）の囲み・方針の折りたたみ・参考の節
- commit はしていない。gen_site.py は実行していない

## 数

- ページに足した問題の行：116 行（練習 83・力試し 33）。問題としては 114 問（arc185_e と abc133_f が 2 ページずつ）
- 反映したページ：51 ページ（complement-graph-bfs は候補がなく、変更なし）
- 台帳：新しい問題 51 件、既存の問題の更新 64 件（pages への追加・evidence の追加・別のページ向けの alternatives・checked を 2026-10-22 に）
    - 新しい問題は `python3 tools/ap.py show` で実在・題名・difficulty を確かめ直した（51 件すべて OK）。contest・index・title・difficulty・experimental は ap.py の値、difficulty_fetched は既存の項目と同じキャッシュの日付（2026-10-21）、status は確認済み、checked は 2026-10-22
    - 既存の問題で、そのページの方針が台帳の approach と違うものは alternatives に `{pages: [ページ], summary, approach}` を足した
    - abc451_g：divide-and-conquer の報告の提案どおり pages から divide-and-conquer を外した（本文にはなかった）。approach は xor-basis 向けの値を本体に上げ、その alternatives を消した。binary-trie の力試しを足した
- 方針：各問題の方針を、ページの「練習の方針」「力試しの方針」（既存の名前が「方針」「ヒント」ならその中）の折りたたみに 1 問 1 項目で足した。報告の方針の要点をもとに、だ・である調で書き直した
- 出典：方針に使った第三者の解説を、ページの参考の節に「著者「題名」」の形で足した（題名は記事の title 要素から取った。すでに参考にある URL は足していない）

## ページごとの反映（* は台帳に新しく足した問題）

| ページ | 練習 | 力試し |
| --- | --- | --- |
| bell-number | abc217_g*・dp_u・typical90_as | |
| bellman-ford | abc237_e・abc280_f | |
| binary-trie | arc033_3・abc403_g | abc451_g・arc122_d*（力試しの節を新設） |
| binomial-identities | abc150_e・abc405_e* | |
| cayley-pruefer | nyc2015_5（練習の節を新設） | |
| centroid-decomposition | yahoo_procon2018_final_c・abc267_f | ddcc_2016_qual_d*・nikkei2019_final_g* |
| complete-binary-tree | | abc220_e* |
| counting-basics | abc178_c・agc031_a* | abc133_e（力試しの節を新設） |
| counting-fix-order | abc209_c・arc116_b*・abc216_f | |
| counting-labeled-graphs | abc321_g | abc389_g* |
| degree-sqrt | abc350_g | abc219_g（節を新設） |
| divide-and-conquer | arc075_c | abc282_h・keyence2019_e |
| euler-path | agc032_c*（囲みを新設。Library Checker の文はそのまま残した） | |
| euler-phi | abc186_e・abc162_e・arc185_e* | |
| expectation-linear-equations | | abc271_g |
| expectation-of-square | abc332_e（節を新設） | |
| expectation-tail-sum | （下の「見送ったもの」の abc411_e） | hhkb2020_f* |
| exponent-mod | abc212_g | |
| ext-gcd | abc340_f* | acl1_b・abc315_g*（節を新設） |
| floor-quotient-enum | abc172_d・abc414_e* | abc132_f* |
| floor-sum | | arc111_e* |
| game-retrograde-analysis | abc245_f（節を新設） | arc038_d* |
| gaussian-elimination | code_thanks_festival_2017_f*・icpc2013summer_day4_f*・bitflyer2018_final_d* | |
| graph-basics | abc343_b・abc276_b | |
| graph-construction | arc044_b*・agc035_b*・arc111_d* | arc143_d* |
| hash-safety | abc331_f・abc377_g | |
| inclusion-exclusion-dp | abc462_g | arc121_e* |
| leaf-first | abc333_d・abc409_e*・abc266_f（節を新設） | agc014_d |
| lowlink | abc375_g・abc334_g（囲みを新設し、本文の「ABC375 G と ABC334 G がある」の段落を消した） | arc039_d*（節を新設） |
| merge-sort-tree | abc174_f・abc405_f*・abc202_e・abc379_f*（節を新設） | |
| min-cut | arc074_d*（節を新設） | |
| mobius-function | abc304_f | abc248_g*・abc020_d* |
| namori-graph | abc378_f | |
| nim | arc046_b*・abc368_f・arc013_3* | arc105_d |
| parsing | arc122_a*・joi2020_yo2_e*・abc350_f* | |
| partition-number | dwacon2018_prelims_c・arc107_d*（節を新設） | |
| permutation-parity | arc136_b* | |
| persistent-data-structures | abc339_g・abc165_f（節を新設） | abc133_f（節を新設） |
| probability-basics | abc028_d* | abc008_3*（節を新設） |
| reflection-principle | arc145_c（節を新設） | |
| root-path-dfs | abc453_g | abc133_f |
| segmented-sieve | math_and_algorithm_bt* | |
| sparse-table | abc125_c・abc254_f（節を新設） | |
| spf-sieve | abc215_d*・abc342_d | abc152_e（節を新設） |
| steiner-subtree | | abc149_f・typical90_ai（節を新設） |
| time-dependent-dijkstra | abc084_c・abc319_e* | arc150_c*（節を新設） |
| tree-centroid | abc348_e・dwacon2018_prelims_e*（節を新設） | |
| tree-imos | abc138_d・abc309_e | |
| tree-path | arc142_c* | |
| zeta-mobius-divisor | yahoo_procon2018_final_a* | arc185_e |
| zeta-mobius-subset | abc472_g・abc349_f*・arc137_d*（節を新設） | abc215_h |

## 複数のページの候補になった問題の置き場所

- arc185_e（euler-phi・mobius-function・zeta-mobius-divisor の候補）：解き方の中心は $\gcd = \sum_{d \mid \gcd} \varphi(d)$ の分解なので、euler-phi の練習を持ち主にした（台帳の本体の summary・approach）。zeta-mobius-divisor は「φ は恒等関数の約数メビウス変換」として力試しに置いた（帯 青から離れるため。alternatives あり）。mobius-function には置かなかった（解説は μ を直接使わない）
- abc133_f（persistent-data-structures・root-path-dfs の力試しの候補）：両方に置いた。前者は永続配列の別解、後者は想定の DFS の足し引きで、方針が違うので重ならない（alternatives を 2 つ）
- 例題の持ち主がほかにある問題は、そのページの例題に触れつつ練習・力試しとして置いた（abc266_f は namori-graph の例題で leaf-first の練習、abc339_g は merge-sort-tree の例題で persistent-data-structures の練習、abc453_g は persistent-data-structures の例題で root-path-dfs の練習、abc472_g は project-selection の例題で zeta-mobius-subset の練習、abc219_g は sqrt-decomposition の例題で degree-sqrt の力試し、abc342_d は prime-exponent-vector の例題で spf-sieve の練習、abc172_d は sigma-manipulation の例題で floor-quotient-enum の練習、abc174_f は offline-queries の例題で merge-sort-tree の練習）
- arc013_3（diff 1831）は nim（水）の帯より上だが、力試しがすでに 3 問（abc172_f・abc212_h・arc105_d）になるので練習に置いた。今の練習 arc143_c（1805）と同じ高さである

## 見送ったもの

- **abc411_e**（expectation-tail-sum の練習。台帳にはすでに practice で入っている）：題名「E [max]」に角かっこがあり、`tools/fix_problems.py` が作る行 `- [ABC411 E. E [max]](…)` を、`check_pages.py` の `PROBLEM_LINE_RE` と `fix_problems.py` の `LINK_TAIL_RE`（label を `[^\]]+` で読む）が読めない（`fix_problems.py --check` が「問題 ID か要約が読めない」になる）。道具を直すのはこの作業の範囲の外なので、ページに入れなかった。**提案**：2 つの正規表現の label の部分を、1 段の角かっこを許す形（例 `(?:[^\[\]]|\[[^\[\]]*\])+`）にすれば載せられる。方針の文は data に書いてあるので、直したら足せる（方針：値を圧縮し、P(最大値 ≤ v) を各サイコロの割合の積として小さい順に更新し、差で足す。0 の因子に注意）
- complement-graph-bfs：報告どおり候補なし
- expectation-of-square の abc194_c（diff 386）：ページの帯（黄）から大きく下に離れる。報告もメインの判断に任せていた
- expectation-tail-sum の arc085_a（diff 752）：報告で「置かなくてもよい」とされ、台帳では coupon-collector の練習。帯からも大きく下に離れる
- counting-labeled-graphs の abc253_h（N の上限を確かめていない）・abc236_h（2898）：どちらも発展の帯で、報告の勧めどおり型が本文の節と最も合う abc389_g だけを力試しに置いた
- divide-and-conquer の abc223_h：要約が記事の記述からの言い換えで、問題文を確かめていない（裏付け 1 件）。力試しも 3 問になった
- inclusion-exclusion-dp の abl_f・abc236_h・agc005_d：力試しが arc121_e を入れて 3 問になるので、報告の勧めどおり arc121_e だけにした
- hash-safety の abc430_e（diff 1109）：帯（青）より易しい側に外れ、報告も「足さないのが自然」としていた
- mobius-function の abc206_e：報告で優先度が低いとされ（μ の式は執筆者の導出で、解説は約数包除）、divisor-inclusion-exclusion の例題でもある
- namori-graph の jsc2019_qual_e（2691）：ページの帯（水）から大きく離れる
- nim の abc297_g：報告のとおり範囲つきの Nim は grundy-number の持ち物で、本文の #bounded もそちらへ任せている
- probability-basics の abc463_f：報告の「どちらか 1 つ」に従い、裏付けが 2 件あり基礎のページに近い abc008_3 を力試しにした
- min-cut の arc074_d の裏付けのうち scrapbox.io/nishio-en は check_noai をしていないので使わず、kmjp の記事だけにした
- 報告で「確かめていない」「候補にしない」とされたもの（complete-binary-tree の abc349_d、sparse-table の arc189_d など）は扱っていない
- zeta-mobius-subset の報告にある「abc295_h を力試しから外す」案（b3 の提案）は、問題の補充の範囲の外なので反映していない

## 新しく noai を確かめたドメイン（付録 B への追加の提案）

`tools/check_noai.py` で確かめ、どれも noai・noimageai の指定はなかった（2026-10-22）。参考の節で使っている。

- bondo.hateblo.jp（bell-number）
- tsutaj.hatenablog.com（mobius-function）
- scrapbox.io/esaka-sandbox（nim）
- fukuro-hoho.hatenablog.com・mmxsrup.hatenablog.com・blog.tiramister.net（probability-basics）
- amentorimaru.hatenablog.com（lowlink。参考にはもとからあった）
- note.com の syamashi の記事 n8e580d4ce59d（hash-safety）・nb491ffdf0ca3（permutation-parity の参考にもとからある）
- aprilganmo.hatenablog.com（報告で確かめたもの。ページでは使っていない）

## 検査

- `python3 tools/fix_problems.py --check`：直すべき行 0・直せない行 0
- `python3 tools/check_pages.py`：エラー 0・警告 0
- `npm run lint:text`：エラー 0（反映の途中で出た prh の「bit DP → bitDP」1 件を直した。警告は文の長さ・読点の数のもの）
