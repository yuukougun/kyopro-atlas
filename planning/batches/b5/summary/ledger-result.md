# b4・b5 の台帳の提案の反映結果（2026-10-22）

対象：prop45/ledger.md。data/problems.yaml を項目ごとに書き換えた（build_ledger.py は使っていない）。summary・approach を直したものと evidence を足したものは、裏付けの URL を開いて確かめた。atcoder.jp・codeforces.com は開いていない。
検査：`python3 tools/fix_problems.py --check` は直すべき行 0、`python3 tools/check_pages.py` はエラー 0・警告 0。
ページで直したのは docs/ds/wavelet-matrix.md の abc324_g の問題の行（131 行目）だけ。要約の「値が x 未満」を、台帳と同じ「値が x 以下のものを残す」にした。例題の本文はもともと「x 以下を残す」と書いていたので、そこは直していない。

注：作業中の `git diff --stat` に、自分では触っていない docs/ のページ（glossary.md ほか 22 ファイル）の変更が出ている。並行して動いている別の作業の変更とみて、そのままにした。

## 反映したもの（72 項目）

### summary・approach の直し（確かめた URL）

| 問題 ID | 直したもの | 確かめた資料 |
| --- | --- | --- |
| abc215_h | summary（仮の文を置き換え） | kmjp 2021/08/22・ikatakos 0821_abc215（最小の個数と、その個数での取り除き方の数の両方を出力すると確認） |
| abc216_h | summary・approach | kmjp 2021/09/02 |
| abc226_h | approach（区分ごとの DP。提案の「区分の中の順位の期待値」は、ikatakos に合わせて「区分の中での K 番目の値の期待値」に言い換えた。提案にあった括弧の別解「P(K 番目 > t) を多項式として積分」は第三者の解説で確かめられないので入れていない） | ikatakos 1107_abc226 |
| abc229_h | summary | kmjp 2021/12/01 |
| abc235_g | summary（「執筆時に確かめる」を外した） | kmjp 2022/01/17・ikatakos 0115_abc235 |
| abc237_h | summary（「に」の重なりをなくす言い換え。意味は同じ） | — |
| abc244_h | approach に別解を追記（「点の番号のセグメント木の各節に凸包を持たせ、オフラインで答える」。kmjp の記事は「時刻」ではなく「点の番号」のセグメント木なので、その言い方にした） | kmjp 2022/03/22 |
| abc247_h | summary | kmjp 2022/04/10・ikatakos 0410_abc247 |
| abc281_h | summary・approach | drken 2023/01/07（合成の規則は記事の問題概要で確認。summary は提案どおり粗いまま） |
| abc300_h | summary（K ≤ 5×10^4、N ≤ 10^18 も drken の記事で確認） | drken 2023/05/02・kmjp 2023/05/04 |
| abc311_h | summary | cnblogs Scarab（「取り除いた頂点の子は親につなぎ直す」と制約をここで確認）・luogu |
| abc318_h | summary。approach は書き換えた。drken の記事にある形（包除原理と、最後の頂点を含む閉路の大きさで分ける DP を分割統治の畳み込みで速くする）にした。**提案の exp(Σ x^t/t^2) の式は記事になく、執筆者が自分で導いたものなので入れていない** | drken 2023/09/03 |
| abc324_g | summary（「値が x 以下のものを残す」）。kmjp は文とコードの両方が x 以下。drken は問題概要の文が「x 未満」だが、コードは x 以下を残す | kmjp 2023/10/14・drken 2023/10/15 |
| abc336_g | summary | kmjp 2024/01/16・potato167 |
| abc340_g | summary | kmjp 2024/02/10 |
| abc348_g | approach | kmjp 2024/04/08（g の側は凹でないので monotone minima を使う、と記事に明記） |
| abc350_g | approach の末尾に「LCT による解法は第三者の解説で確かめていない」と注記した（提案の 2 案のうち注記のほう） | — |
| abc351_g | summary | ikatakos 0427_abc351・trap.jp |
| abc354_g | summary | kmjp 2024/05/19・ikatakos 0518_abc354 |
| abc355_g | summary | kmjp 2024/06/05 |
| abc374_g | summary | ikatakos 1005_abc374（kmjp の要約は条件の書き方があいまいなので、ikatakos の条件に合わせた提案の文のままにした） |
| abc376_g | summary | kmjp 2024/10/23 |
| abc378_g | summary・approach | ikatakos 1102_abc378（「ある値 n + 0.5 を付け加える」と明記） |
| abc383_g | approach | kmjp 2024/12/13 |
| abc395_g | approach（提案の「根の頂点として読む」は、ikatakos に合わせて「DP の表の頂点（木に含める頂点）の添字として読む」にした。DP は S ごとに回す） | ikatakos 0301_abc395 |
| abc412_g | summary | kmjp 2025/06/29 |
| abc414_g | summary | kmjp 2025/07/14 |
| abc428_g | summary・approach | kmjp 2025/10/18・ikatakos 1018_abc428 |
| abc449_g | summary・approach（kmjp の (1+…+x^9)^(M−1) に (1+⌊(N−i)/9⌋) の重みを付ける形は、提案の (1−x^10)^(M−1)/(1−x)^M の x^N・x^(N−9)・… の係数の和と同じ式になる） | kmjp 2026/03/14・ikatakos（既存） |
| abc456_d | summary・approach | zenn iwamutsu |
| abc457_e | summary・approach | ikatakos 0509_abc457 |
| abc458_g | summary・approach（summary は提案の仮の文のまま。ikatakos の記録で「メダルを日ごとに A_i 得て、生き残りに B_i、脱出に C_i かかる中で、脱出できる人数の最大」と確かめた。細部はもっと書ける） | ikatakos 0516_abc458（Slope Trick を明記している） |
| abc464_e | summary・approach（2 次元の累積 max） | qiita comet725・scrapbox konan-compro |
| abc464_g | approach（最小化の向きに直した） | ikatakos 0627_abc464（「最小コスト」「x が単独なら Alien DP も使えるが、今回は向かない」） |
| abc466_d | summary | qiita Wakako19972899 |
| abc470_d | summary・approach | qiita comet725 |
| abc472_d | summary | qiita comet725・scrapbox konan-compro |
| abc478_g | approach（「research/00 §5.2 の分類による」を、具体的な手順に置き換えた） | kmjp 2026/10/08 |
| typical90_bw | summary | ebisuke33 |
| typical90_cl | summary・approach | 公式の解説画像 090-01〜05（取得して読んだ。値が 0〜K、mod 998244353、N ≤ 10^9・K ≤ 10^5、(高さ, 長さ) の DP、高速きたまさ法・Bostan-Mori） |

### evidence の追加・整理

- 追加：abc189_c（ikatakos）、abc198_f（pctsnote）、abc212_h（kmjp）、abc213_h（kmjp）、abc215_h（ikatakos）、abc217_h（ikatakos）、abc218_h（kmjp）、abc226_h（ikatakos）、abc229_h（hitonanode dyadic_rational。「問題例」に載っている）、abc235_g（ikatakos）、abc247_h（ikatakos）、abc265_d（zenn dhirabayashi）、abc285_g（qiita recuraki）、abc300_h（kmjp）、abc302_h（ikatakos）、abc311_h（luogu・cnblogs）、abc324_g（kmjp）、abc333_g（kanpurin。Stern-Brocot の節に載っている）、abc336_g（potato167）、abc340_g（kmjp）、abc351_g（ikatakos・trap.jp）、abc352_g（kmjp）、abc354_g（ikatakos）、abc359_g（kmjp）、abc374_g（ikatakos）、abc376_g（nyaannyaan の一覧に「01 on Tree」・hitonanode tree_pop_order_optimization の問題例）、abc378_g（ikatakos）、abc385_g（ikatakos）、abc395_g（ikatakos）、abc428_g（ikatakos）、abc436_g（ikatakos。和が M 以下の個数と Bostan-Mori を確認）、abc449_g（kmjp）、abc456_d（zenn iwamutsu）、abc464_e（scrapbox）、abc466_d（qiita Wakako）、abc472_d（scrapbox）、agc002_d（buyoh。並列二分探索の記事）、arc123_d（kmjp。貪欲に作ってから調整する解き方で、Slope Trick の裏付けではない）、dp_z（zenn kiwamachan。deque の CHT。ならし O(N) とは書いていない）、typical90_bw（ebisuke33・zenn samekard。samekard は素因数の補題だけを扱う）、typical90_cl（090-03〜05.jpg）
- 外した：abc194_e・abc438_f の ikatakos の一覧のページ（`…/contest_history/atcoder/`）、agc002_d の cp-algorithms の二分探索の記事（問題に固有の解説ではないので、buyoh と差し替えた）

### checked に '2026-10-22' を入れた（§2）

abc137_f・abc171_e・abc180_c・abc189_c・abc194_e・abc197_c・abc198_f・abc213_h・abc215_h・abc216_h・abc218_h・abc226_h・abc228_h・abc229_h・abc235_g・abc246_h・abc265_d・abc285_g・abc289_g・abc300_h・abc311_h・abc318_h・abc324_g・abc333_g・abc336_g・abc340_g・abc351_g・abc354_g・abc355_g・abc364_g・abc374_g・abc376_g・abc385_g・abc412_g・abc414_g・abc428_g・abc436_g・abc438_f・abc449_g・abc457_e・abc464_e・abc466_d・abc470_d・abc472_d・agc002_d・arc033_3・arc084_b・code_thanks_festival_2017_h・dp_z・tdpc_fibonacci・typical90_ai・typical90_bw・typical90_cl

- すでに '2026-10-21' が入っていたもの（abc478_g・abc244_h・abc464_g・abc183_f・abc452_g・abc339_g）は上書きしていない（日付を新しくするかはメインの判断）
- dp_z は執筆者だけの提案だが、zenn の記事で CHT の方針を確かめたので入れた

## 反映しなかったもの（理由）

| 問題 ID | 提案 | 理由 |
| --- | --- | --- |
| abc187_f | chromatic-number に practice を足す | chromatic-number に「練習問題」の節を新しく作る必要がある。ページの構成を変えることになり、この作業で直してよい「問題の行」を超える。メインがバッチで判断する |
| abc189_c | monotonic-stack の pages との食い違い | 台帳から外すか、ページに行を足すかの判断が要る（evidence の追加と checked は反映した） |
| abc197_c | evidence に oraclesqlpuzzle を足す・bit-full-search との食い違い | oraclesqlpuzzle はすでに evidence に入っていた。bit-full-search の pages とページの食い違いは、台帳とページのどちらを直すかの判断が要る |
| abc171_e・abc210_f・abc277_h・abc377_e・agc021_b・abc438_f（2 件目） | 2 つ目の evidence | 足す URL が提案にない |
| abc241_d | alternatives（balanced-bst）の summary に K ≤ 5 を足す・checked | K ≤ 5 を確かめた資料がない（検証役も未確認とした）。checked も入れていない |
| abc311_h | static-top-tree から tree-dp-square などへ移す | メインの判断（summary・evidence・checked は反映した） |
| abc321_f・abc449_g | title の末尾の空白を削る | AtCoder Problems のデータの題名そのものが末尾に空白を持つ（ap.py で確認）。label は check_pages が作るときに空白を落としているので、本文には影響しない |
| abc355_g | monge に practice を足す | candidates.md の候補で、ページに行がない。メインの判断 |
| abc433_g | suffix-automaton に足す | SAM による解き方を第三者の解説で確かめられない（提案者も見送りを勧めた） |
| abc458_g | slope-trick に practice で足すか、slope-trick の frequency_evidence から外すか | 食い違いの判断はメイン。frequency_evidence はページの front matter なので、この作業の範囲の外。なお ikatakos の記録は Slope Trick を明記していた（判断の材料として） |
| abc464_e | problem-sets で imos#imos-2d に振っているのを直す | ページの本文の振り分けで、この作業の範囲の外（other.md の扱い） |
| abc470_e・abc470_f | contest-strategy で ID を出すか | 台帳の変更は要らない。本文の判断はメイン |
| agc002_d | summary の直し（2 案） | 2 案のどちらにするかはメインの判断。evidence の追加・差し替えと checked は反映した |
| arc033_3 | evidence に drken の Qiita（k 番目の値のまとめ）を足す | 記事は ARC033 C を BIT と二分探索の例として挙げるだけで、提案が書いた「平衡二分探索木・pb_ds でも解ける」という記述はこの問題について書かれていない。checked は検証役の提案どおり入れた |
| arc123_d | approach を Slope Trick の具体的な手順にする | Slope Trick の手順は手元の全探索で確かめただけで、第三者の解説の裏付けがない（kmjp は貪欲に作ってからずらす解き方）。evidence の追加だけ反映した |
| keyence2019_e | spanning-tree-advanced に example か practice で足す・approach に Borůvka 法を追記 | 役割の選び方はメインの判断。Borůvka 法での解き方も、drken の記事では「Borůvka でも解ける」と触れているだけで、手順の裏付けにならない |
| practice2_h | evidence に ac-library の document_ja/twosat.md を足す | 文書の使用例の欄は `@{example.twosat_practice}` というテンプレートの置き場所だけで、練習会の H を指すとは文書から読み取れない（既存の evidence の twosat_practice.cpp で足りている） |
| abc228_h・abc289_g・abc237_h・abc256_h・abc334_g・abc339_g・abc452_g・abc127_f・abc131_f・abc286_g・abc137_f・abc246_h・arc084_b・tdpc_fibonacci・typical90_ai | 変更なし・記録だけ | 台帳を書き換える提案ではない（checked の提案があったものは §2 で入れた） |
| §4 の新しい問題（abc380_d・abc253_h・agc023_f）と、既存の問題に pages を足す一覧（typical90_e・abc392_f・abc462_g・abc165_d・abc121_d・abc365_e・abc201_e・abc265_h） | 台帳への追加・pages の追加 | 台帳に入れると、ページの練習の節を新しく作ったり、ID なしで型だけ書いた本文を例題・練習へのリンクに張り替えたりすることになる。これは執筆の作業で、この作業で直してよい「問題の行」を超える。agc023_f は問いの確認も未了、abc253_h は 2 件目の裏付けが未確保で、提案にも「確かめてから」とある。pages を足す一覧は中身を読んでいないもの・裏付けがタグだけのものを含む |
| §5 の evidence が 1 件のままの一覧 | 台帳か進捗に記録する | 台帳に記録する欄（note）の使い方はメインの判断。進捗への記録はこの作業の範囲の外 |

## 数

- 反映：72 項目（summary・approach を直した 40 項目、evidence の追加・整理だけの 19 項目、checked の記入だけの 13 項目。checked の記入は全部で 53 項目）
- 見送り：20 件（上の表の行。「変更なし・記録だけ」の行を除くと 19 件）
