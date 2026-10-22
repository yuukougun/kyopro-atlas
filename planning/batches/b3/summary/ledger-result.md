# prop23/ledger.md の台帳への反映の結果

対象は data/problems.yaml だけ。ページ本文は変えていない（fix_problems.py --check の直すべき行 0、check_pages.py のエラー 0・警告 0）。
適用に使ったスクリプトは scratchpad/prop23/apply.py。反映前の台帳は scratchpad/prop23/problems.yaml.bak（HEAD と同じ）にある。
新しい evidence の URL 177 件は check_noai.py で確かめ、noai はなかった。yamanoue.tslmuse.com だけ 502 で取得できなかったので入れていない。
注意：作業中に別のエージェントが docs/（glossary.md や各ページのリンク）を書き換えていた。その変更は私のものではない。

## 反映したもの（新しい問題 12・変えた既存の項目 246）

### 新しい問題（12 件。ap.py で ID・題名・diff を確かめ、裏付けの記事で問いを確かめた）
abc116_c（difference-sequence 練習）・abc282_h（divide-and-conquer 力試し）・abc332_e（subset-enumeration-dp と expectation-of-square の練習）・abc364_d（kth-value 練習）・abc411_e（expectation-tail-sum 練習。mod 998244353 は Qiita のコードの 6 の逆元で確認。面の値の範囲は summary に書いていない）・agc045_a（xor-basis 練習）・arc145_c（reflection-principle 練習、checked あり）・dwacon2018_prelims_c（partition-number 練習）・exawizards2019_d（insertion-dp 練習）・nyc2015_5（cayley-pruefer 練習）・yahoo_procon2018_final_c（centroid-decomposition 練習）・zone2021_f（xor-basis 練習）
- どれもページ本文にはまだ行がない（台帳の pages が先にある状態。既存の台帳にも同じ状態の項目が 128 件ある）。練習問題の節がないページ（expectation-of-square・expectation-tail-sum・reflection-principle・partition-number・cayley-pruefer）は、本文に行を足すときに ## 練習問題 {#practice} を作る必要がある

### summary・approach の直し（裏付けの記事を開いて確かめたもの）
abc141_e（hash-safety の approach。perogram で経緯を確認）・abc149_e・abc180_f（本体と alternatives 2 つ）・abc191_d（本体と alternatives）・abc202_f・abc212_g（998244353 の余りを足した）・abc214_f・abc221_g・abc225_g（summary と approach）・abc251_g・abc259_h（approach）・abc261_h・abc267_g・abc268_h（approach。注記を外した）・abc277_g（approach に二乗を先に更新することを足した）・abc283_g・abc286_g（歩道→ウォーク）・abc287_h（summary と approach。ワーシャルフロイド法の語は外した。kmjp は頂点を番号順に足す形）・abc290_f（approach。cirrostratus）・abc291_h・abc295_h（summary と approach。kmjp はゼータ変換を使わない）・abc297_f（approach。kazun は「4 方向の包除」ではなく行の条件と列の条件の包除なので、その形で書いた）・abc302_h（alternatives[root-path-dfs] の summary を本体にそろえた）・abc304_f・abc309_g（alternatives[insertion-dp] の approach。kmjp は包除を使わない）・abc309_h・abc311_f（summary と approach）・abc320_g・abc325_g・abc332_g・abc350_g（alternatives[bitset-speedup] の approach）・abc375_g（approach の補足）・abc397_g（summary と approach）・abc410_g（approach）・abc421_g（summary。kmjp に「できないとき」の記述がないので「できるかどうかも判定する」は入れなかった）・abc441_f・abc447_g（checked は入れていない）・abc451_g（alternatives[xor-basis] の approach。kmjp で分割統治を使わないことを確認）・abc454_f・abc466_e（alternatives 2 つの summary を本体にそろえた）・abc470_g（approach は「二分探索と区間代入」ではなく kmjp のコードの Segment Tree Beats（区間 chmax・区間和）で書いた）・abc471_g（checked は入れていない）・abc472_g（summary と title）・abc474_f・abc477_f・abc480_g（summary だけ）・agc039_c・arc070_b（alternatives[bitset-speedup] の summary を本体にそろえた）・arc171_c・keyence2019_e（summary・approach。役割は challenge のまま）・tessoku_book_bp・tessoku_book_bq（answer_A68・A69.cpp を確認）・tessoku_book_eo（drken の Qiita で確認）・typical90_ao・typical90_by
- summ で書いた文は、その問題の alternatives の summary にも同じ文を入れた（alternatives がある問題だけ）

### evidence の追加・整理
追加：abc138_f・abc141_e・abc145_e・abc149_e・abc157_f・abc191_d・abc194_f・abc202_f・abc203_e・abc203_f・abc208_e・abc209_f・abc214_f（luogu）・abc217_f・abc221_g・abc223_f（hackmd）・abc226_f（2 件）・abc231_e・abc235_f・abc242_f・abc244_g・abc251_f・abc251_g・abc259_d・abc259_h・abc260_f・abc271_e・abc273_f・abc282_g・abc283_g・abc286_g・abc287_f・abc290_f・abc291_h・abc292_g・abc295_e・abc296_f・abc296_g・abc296_h・abc309_g・abc317_f・abc331_g・abc334_g・abc339_f（2 件）・abc339_g・abc341_g・abc343_f・abc348_f・abc350_g・abc362_g（2 件）・abc371_f・abc372_f・abc375_g・abc403_f（2 件）・abc404_f（merom686。summary は直していない）・abc412_f（gotoki_no_joe。summary は直していない）・abc419_f・abc421_e（kcpc だけ）・abc422_e（2 件）・abc426_g・abc441_f（2 件）・abc447_g・abc454_f・abc458_f・abc468_g（kmjp。approach は直していない）・abc470_g・abc471_g・abc474_f・abc477_f・arc081_c・arc083_b・arc130_d・arc171_c・tdpc_iwi・tdpc_lexicographical・tessoku_book_bp・typical90_ak・typical90_as・typical90_bg・typical90_ce・typical90_k・typical90_s・typical90_w・yahoo_procon2019_qual_d
外した：abc141_f（usaco.guide の無関係な 6 件。adv/xor-basis と drken は残した）・abc187_f（usaco.guide 3 件）・abc223_f（ikatakos の一覧の入口）・abc296_h・arc130_d・yahoo_procon2019_qual_d（mathenachia.blog/dp/、404）・abc339_f（merom686 のトップ）・abc368_f（programming-hiroba のトップ）・tessoku_book_bp（フォルダの URL を answer_A68.cpp に絞った）・typical90_ce（scrapbox、404）・abc309_g（kanpurin の 2020 年の記事を tibrella に差し替え）

### pages の追加（「案」「任意」でないもの）
abc162_e（euler-phi 練習）・abc202_e（merge-sort-tree 練習）・abc254_f（sparse-table 練習）・abc303_e（tree-degree 練習）・abc334_g（lowlink 練習）・abc348_e（tree-centroid 練習）・abc375_g（lowlink 練習）・dp_u（bell-number 練習）・typical90_as（bell-number 練習）
- これらもページ本文にはまだ行がない（merge-sort-tree・sparse-table・tree-centroid は練習問題の節もない）

### title・note
title の末尾の空白を外した：abc325_f・abc376_f・abc421_g・abc472_g。note を外した：abc216_g（checked は前から 2026-10-21）

### checked（2026-10-21）
§3 の行で checked とあり、上で反映した問題に加え、§3.1 の inclusion-exclusion-dp の 5 問（dp_y・abc309_g・arc115_e・abc214_g・arc101_c）と §5 の一覧のうち保留でない 161 件に入れた。agc018_d・abc163_e・abc401_g は checked だけ入れた（abc163_e の summary はメインの判断を待つ。abc401_g の note は下の見送りを参照）。

## 見送ったもの（理由）

### §1 の食い違い（メインが決める）
- abc445_g：summary が 2 案で食い違う。summary も checked も入れていない
- abc075_c：checked が食い違う
- abc163_e：summary の形（主を書き換えるかページを alternatives に合わせるか）。checked だけ入れた
- abc334_f・arc185_e・abc349_f：新しい問題だが、どのページのどの役割にするかが決まっていない（abc334_f は要約も推定）
- keyence2019_e：divide-and-conquer に足すか（summary・approach・checked は入れた）
- abc290_f：例題の置き場（approach・evidence は入れた）
- abc480_g・abc292_g・abc315_f：role の変更
- abc295_h：zeta-mobius-subset から broken-profile-dp への移動（summary・approach は直した。いまの approach はゼータ変換を使わないので、ページの力試しの囲みと食い違う。移すときは本文の行も消す）
- abc451_g：divide-and-conquer の challenge から外すこと（本文の行も消す必要がある。xor-basis 側の approach は直した）
- abc309_f・abc283_f：segment-tree-monoids から segment-tree-on-values への移動
- abc450_g：操作の向きが確かめられていない

### 新しい問題で見送ったもの
- arc039_d：問題文の内容（A→B→C の条件）を確かめられなかった。ei1333 はコードだけで、hamayan の記事は問題へのリンクだけ

### 裏付けが取れなかったもの・食い違ったもの
- abc230_g：summary の「i ≤ j」について、kmjp の記事を読んだ要約は「i < j」と出た。Kodaman の scrapbox にも条件が書いていない。summary・evidence・checked のどれも入れていない（問題文の条件を別の資料で確かめる必要がある）
- abc404_f：merom686 だけでは問題文の条件（1 回に合計 M 回押す・K 回以上）を確かめられない。evidence だけ足した
- abc412_f：gotoki_no_joe の記事は問題文の全文がなく、mod も書いていない。evidence だけ足した。rational-mod の練習に足す案も見送った
- abc459_f：yaohaoyou の記事には B_i = A_i − i の言い換えしかなく、問題文もブロックの併合も書いていない（もう 1 件は解答コードだけ）。何も反映していない
- abc468_g：approach の遷移（外に伸ばすときの長さ）が kmjp の記事では「前後 2 通り」と読め、提案の書き方と一致するか確かめられない。evidence だけ足した
- abc401_g：note の「座標は 10^18 まで」は kmjp の記事に書いていない（Luogu は開いていない）。checked だけ入れた
- abc470_f：summary と approach の裏付けが ikatakos だけで、その記事が 503
- abc421_e：yamanoue.tslmuse.com が 502

### 提案が「案」「任意」・保留のもの（メインが判断する）
- 役割の追加の案：abc133_f・abc214_d・abc215_h・abc237_e・abc245_f・abc266_g・abc267_f・abc339_g（persistent-data-structures）・abc378_f・abc405_g・abc412_f（rational-mod）・abc455_f・arc085_a・typical90_ac・typical90_ai・keyence2019_e（divide-and-conquer）
- approach の任意の言い換えで、今回は裏付けを開かなかったもの：abc110_d・abc128_c・abc159_f・abc189_f・abc281_g・abc292_f・abc310_d・abc326_g・abc359_g（URL なし）・abc361_f・abc365_g（tumblr の記事が取れない）・agc038_c・arc092_a・arc174_c・arc189_d（URL なし）
- summary の補足を「検討」としたもの：abc335_g・abc453_g・abc467_g・abc470_e
- 判断の待ち：abc010_4（問題文の意味）・abc308_g（acwing の URL を残すか）・abc467_f（ページから外すか）・abc475_f・yahoo_procon2019_qual_d の label の表示名・abc456_f の evidence の順・abc461_g・abc471_f の note（そのまま）
- 何もしなくてよいとされたもの：abc206_f・abc210_e・abc252_g・abc366_f・tdpc_target・dp_n・tdpc_grid・abc230_f・abc299_f・abc333_f・abc379_g・abc456_g・tdpc_eel
- §5 で保留のもの：abc425_g・abc471_g・abc447_g・abc470_e・abc470_f・abc466_e・abc366_f・abc216_g（保留の一覧にあるので checked は変えていない。前から 2026-10-21）・abc332_f・abc404_f・abc379_g・abc365_g・abc450_g・tdpc_eel・abc075_c・abc445_g

## 補足
- summary が 120 字を超える項目がある（abc261_h 125・abc295_h 141・abc320_g 152。提案の文のまま）。台帳の検査には掛からないが、本文の行に使うときは短くしたほうがよい
