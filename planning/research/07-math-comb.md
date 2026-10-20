# 07 数学（数え上げ・確率・ゲーム）調査レポート

- 担当：07 math-comb（数え上げ・確率・ゲーム）
- 作成：2026-10-21（工程2「調査」）
- 成果物：本レポートと [07-math-comb.topics.yaml](07-math-comb.topics.yaml)（73 項目、例題・練習問題 221 件、重複を除いて 177 問）
- difficulty は `tools/ap.py`（AtCoder Problems の 2026-10-21 取得キャッシュ）の値。本文の「abc172_e（1880）」の括弧内は difficulty、「なし」は推定値がないもの
- 問題の内容は、すべて第三者の解説記事で確かめ、URL を §5 と topics.yaml に残した。atcoder.jp（問題・公式解説）は一度も開いていない

**調べ方についての注記**：調査の途中でセッション全体の Web 検索の枠が尽きたため、検索に頼らず、(1) ABC001〜480 の全回について、解説ブログの問題別の記事を機械的に集め（kmjp さんはブログ内の記事一覧〔検索ページ・日付アーカイブ〕から 474 問、ikatakos さんはコンテストごとの決まった URL から 817 問）、本文の語（期待値・包除・Grundy など）で分類する、(2) drken さんのブログのカテゴリページ 74 種（記事 1323 件）から「手法 → 問題」の対応を取る、(3) 決まった URL を持つ解説サイト（プロひろ・Kazun の競プロ記録）を直接読む、の方法で候補と裏付けを集めた。検索が一時的に回復したときに数回だけ使った。Codeforces は noai 指定のため使っていない。

## 1. 調べた資料

### 1.1 体系・理論（日本語）

| 資料 | URL | 何の参考にしたか |
| --- | --- | --- |
| drken「写像12相を総整理！」 | https://qiita.com/drken/items/f2ea4b58b0d21621bd51 | 写像12相の構成、スターリング数・ベル数・分割数の漸化式と計算量、重複組合せの例題（abc021_d・abc110_d）、AOJ DPL_5 の 12 問 |
| drken「998244353 で割ったあまりの求め方を総特集！」 | https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a | mod の割り算・逆元・二項係数の前計算（06 との境界の確認） |
| convexineq「ゼータ変換・メビウス変換を理解する」 | https://qiita.com/convexineq/items/afc84dfb9ee4ec4a67d5 | 部分集合と約数のゼータ・メビウス変換を「累積和」として統一する見方、約数系包除、gcd 畳み込み |
| kanpurin「【競プロ】数え上げまとめ」 | https://kanpurin.hatenablog.com/entry/2020/08/25/183953 | ABC の数え上げ問題（ABC050〜180 期の約 40 問）の一覧 |
| drken「AtCoder 版！蟻本（初級編）」「同（中級編）」 | https://qiita.com/drken/items/e77685614f3c6bf86f44 ・ https://qiita.com/drken/items/2f56925972c1d34e05d8 | 重複組合せ・ゲーム DP の例題の対応（確率・期待値の節はほぼない） |
| drken のブログのカテゴリページ | https://drken1215.hatenablog.com/ | 「包除原理」「包除原理:DP」「約数系包除」「メビウス関数」「高速ゼータ変換」「重複組合せ」「カタラン数」「スターリング数」「分割数」「プリューファー(Prüfer)コード」「数珠」「経路数に帰着」「K以上からK+1以上を引く」「最小添字規則によってダブルカウントを防ぐ」「期待値」「期待値の線形性」「回数の期待値=(k回以上の確率)の和」「有理数mod998244353」「ゲーム」「ゲームDP」「Grundy数」「Nim」「後退解析」「対称戦略」「得点差最大化ゲーム」など 74 カテゴリの記事一覧から、手法と問題の対応と、各問題の解説 |
| 『競技プログラミングの鉄則』の GitHub | https://github.com/E869120/kyopro-tessoku | 5 章の想定解（A30 二項係数、A31 包除、A32 勝ち負けの DP、A33 Nim、A34 Grundy 数、A35 ミニマックス） |
| 『アルゴリズム×数学』の GitHub | https://github.com/E869120/math-algorithm-book | 3.3 節（場合の数）・3.4 節（確率・期待値、コンプガチャ型）・5.2 節（規則性、ゲーム）・5.7 節（寄与）の解答コード |
| 競プロ典型 90 問の GitHub | https://github.com/E869120/kyopro_educational_90 | 015・031・052・066・069・088 の問題文テキストと想定解 |
| AtCoder Tags | https://atcoder-tags.herokuapp.com/tags/Mathematics/Expected-Value | 「期待値」タグの問題一覧（自分の分類との照合） |

### 1.2 体系・理論（英語・中国語）

| 資料 | URL | 何の参考にしたか |
| --- | --- | --- |
| cp-algorithms（Combinatorics・Game theory） | https://cp-algorithms.com/combinatorics/binomial-coefficients.html ほか、inclusion-exclusion、burnside、catalan-numbers、stars_and_bars、bracket_sequences、counting_labeled_graphs、graph/kirchhoff-theorem、graph/pruefer_code、game_theory/games_on_graphs、game_theory/sprague-grundy-nim | 記事一覧で項目を洗い出し、見出しで扱う範囲を確認。二項係数の mod m での計算、Burnside とネックレス、任意グラフ上のゲーム（後退解析）、SG 定理と逆形 Nim・Grundy 数のパターン、Prüfer 列、連結なラベル付きグラフの数え上げ |
| USACO Guide | https://usaco.guide/gold/combo ・ https://usaco.guide/plat/PIE ・ https://usaco.guide/plat/dp-sos ・ https://usaco.guide/adv/catalan ・ https://usaco.guide/adv/game-theory ・ https://usaco.guide/adv/prefix-sums-nt-1 | 英語圏での位置づけ（Gold：二項係数・撹乱順列・重複組合せ・期待値の線形性、Plat：包除とメビウス・SOS DP、Advanced：カタラン数と鏡像法・ゲーム理論・乗法的関数） |
| Competitive Programmer's Handbook（LaTeX ソース） | https://github.com/pllk/cphb （chapter22/24/25.tex） | 22 章 Combinatorics（二項係数・カタラン数・包除・Burnside・Cayley）、24 章 Probability（確率変数・マルコフ連鎖・乱択）、25 章 Game theory（ゲームの状態・Nim・SG 定理）の構成 |
| OI Wiki（组合数学・概率论・博弈论） | https://oi-wiki.org/math/combinatorics/combination/ ・ https://oi-wiki.org/math/probability/exp-var/ ・ https://oi-wiki.org/math/game-theory/impartial-game/ | 項目の網羅の確認（抽屉原理・容斥・错位排列・卡特兰数・斯特林数・贝尔数・分拆数・范德蒙德卷积・Pólya・图论计数・杨氏矩阵）、期待値と確率の変換・条件付き期待値・分散、公平ゲームの一覧（Bachet・Moore's Nim-k・階段 Nim・Fibonacci Nim・Wythoff・硬貨裏返し・二部グラフゲーム・逆形 Nim・有向グラフゲーム） |

### 1.3 問題の裏付け（第三者の解説）

| 資料 | URL | 使い方 |
| --- | --- | --- |
| kmjp's blog | https://kmjp.hatenablog.jp/ | ABC001〜480 で記事のある 474 問を取得し、本文の語で分類。裏付けの主力 |
| ikatakos の競プロ Wiki | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/ | ABC001〜480 で記事のある 817 問を取得し分類。2025〜2026 年の新しい問題の裏付けの主力 |
| drken のブログ | https://drken1215.hatenablog.com/ | 上記カテゴリの各記事 |
| はまやんはまやんはまやん | https://blog.hamayanhamayan.com/ | 古い問題（arc095_b） |
| kyopro_friends「EDPC解説 F～L」 | https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000 | EDPC I・J・K（確率 DP、自己ループの移項、石取りゲーム）。EDPC L・Y は drken のブログの記事 |
| プロひろ（プログラミングのひろば） | https://programming-hiroba.com/ | abc368_f・abc349_e・abc278_f・abc360_e・abc350_e・abc298_e・abc275_e・abc326_e・abc334_e |
| Kazun の競プロ記録 | https://kazun-kyopro.hatenablog.com/ | abc263_e・abc266_e・abc297_f・abc234_f・abc262_e |
| yuulis のブログ | https://yuulis.hatenablog.com/entry/ABC-390-D | abc390_d（ベル数 B(12)=4213597 での全列挙） |
| Qiita（DeltaStruct）ABC314 解説 | https://qiita.com/DeltaStruct/items/08a55509095a471c5371 | abc314_e（0 の目による自己ループの除去） |

### 1.4 ライブラリ

| 資料 | 場所 | 何の参考にしたか |
| --- | --- | --- |
| AtCoder Library ドキュメント | `~/lib/ac-library-master/document_ja/`（modint.md・convolution.md・index.md） | modint の `pow`・`inv`・`val`。ACL に二項係数・スターリング数・ゲームの機能はなく、関係するのは modint と convolution だけであること |

使わなかったもの：atcoder.jp（問題・公式解説・ブログ）、Codeforces（noai 指定）。noshi91「高速ゼータ変換の約数版 O(N log(log(N)))」（https://noshi91.hatenablog.com/entry/2018/12/27/121649）は ikatakos の abc474_f の解説が参照していることを確認しただけで、本文は読んでいない。

## 2. 分野の全体像

### 2.1 3 つの柱と前提関係

07 は「数え上げ」「確率・期待値」「ゲーム」の 3 つの柱からなる。数え上げはさらに、**数え方の考え方**（何をどう数えるか：対応づけ・言い換え・補集合・重複の除き方・順序の固定など）と**道具**（数えた結果を計算する式や変換：二項係数・包除原理・写像12相・特殊な数・ゼータ変換など）に分けて整理する。考え方が「数える対象を数えやすい形に直す」段階、道具が「直した形を速く正しく計算する」段階に当たり、ABC の E〜G で詰まる原因の多くは前者にある。

```mermaid
graph LR
  subgraph 数え方の考え方
    M[総論：和・積・ちょうど1回] --> BJ[対応づけ・言い換え]
    M --> CP[補集合]
    M --> DD[重複の除き方]
    M --> FO[順序の固定]
    M --> CT[寄与（総和）]
    M --> EX[実験・OEIS]
  end
  subgraph 道具：二項係数の系統
    CB[順列・組合せ] --> BC[二項係数] --> PC[前計算] --> MN[多項係数]
    BC --> SB[重複組合せ] --> TW[写像12相]
    BC --> LP[格子路] --> RF[鏡像法・カタラン数]
    BC --> ID[恒等式]
    BC --> LU[Lucas]
    TW --> S2[第2種スターリング] & BE[ベル数] & PN[分割数]
    PN --> CY[巡回型] --> S1[第1種スターリング]
  end
  subgraph 道具：包除の系統
    IE[包除原理] --> IED[包除 DP]
    IE --> DV[約数包除] --> MO[メビウス]
    IE --> ZS[ゼータ（部分集合）]
    DV --> ZD[ゼータ（約数）]
  end
  subgraph 確率・期待値
    PB[確率の基本] --> RM[mod 表現]
    PB --> LE[線形性] --> IV[指示確率変数] --> SY[対称性]
    LE --> TS[tail sum]
    PB --> GD[幾何分布] --> CC[コンプガチャ]
    PB --> ED[期待値 DP] --> SL[自己ループ] --> EQ[方程式]
    ED --> OS[最適戦略]
  end
  subgraph ゲーム
    GB[必勝・必敗] --> MM[ミニマックス]
    GB --> RA[後退解析]
    GB --> NI[Nim] --> GR[Grundy 数] --> PZ[非不偏]
    GB --> MI[真似戦略・偶奇]
  end
  CP --> IE
  CT -. 同じ計算 .- IV
  DD -. 対称性なら .- BU[Burnside]
  CC -. 一般化 .- IE
```

### 2.2 数え方の考え方と道具の対応

| 数え方の考え方 | 中身 | 主に組み合わせる道具 | 代表例 |
| --- | --- | --- | --- |
| 対応づけ・言い換え | 数えにくい対象を、個数の同じ数えやすい対象に 1 対 1 で移す | 二項係数・重複組合せ・格子路・Prüfer 列 | abc145_d（1009）・abc185_c（374）・arc110_d（2078） |
| 補集合 | 「少なくとも1つ」を全体から引く | 累乗・二項係数 → 条件が増えれば包除原理 | abc178_c（653）・abc163_f（2470） |
| 重複の除き方 | 一定の重複度なら割る、そうでなければ代表元を決める、対称性なら Burnside | 多項係数・部分列 DP・Burnside | arc077_b（1715）・abc171_f（1795）・abc310_d（1368） |
| 順序の固定 | 相対順序を固定して n!/k!、ソートして寄与、積の法則が使える順に決める | 階乗・二項係数 | abc151_e（1344）・abc133_e（1505）・abc160_f（2048） |
| ちょうど＝以下の差 | 「≤k」から「≤k−1」を引く | 累乗・約数包除・tail sum | abc180_f（2419） |
| 寄与（全通りの総和） | 和の順序を交換し、部分ごとに「効く通り数」を掛ける | 二項係数・2 の累乗 | abc127_e（1938）・abc173_f（1892） |
| 実験 | 小さいケースの全探索で式や規則を推測・検算する | 全探索・OEIS | abc297_g（1834）・abc398_e（1238） |

道具の側は「二項係数の系統」（意味 → 前計算 → 多項係数・重複組合せ・恒等式・格子路・写像12相・特殊な数）と「包除の系統」（包除原理 → 包除 DP・約数包除 → メビウス・ゼータ変換）の 2 本に分かれ、写像12相の「全射」のマスで 2 本が合流する（全射の数 = 包除の式 = $k!\,S(n,k)$）。

### 2.3 確率・期待値の ABC での頻出パターン

| パターン | 中身 | 代表例 |
| --- | --- | --- |
| mod 998244353 で答える確率・期待値の DP | 後ろ向きの期待値 DP、前向きの確率 DP。割り算は逆元 | abc280_e（1251）・abc275_e（1264）・abc323_e（1279）・abc298_e（1300）・abc326_e（1363） |
| 自己ループの除去 | $E=c+pE+\cdots$ を移項 | abc300_e（1354）・abc350_e（1385）・abc263_e（1659）・abc314_e（1722） |
| 期待値の線形性・指示確率変数 | 個数の期待値 = 各候補の確率の和 | abc154_d（485）・abc334_e（1195）・abc417_f（1414）・agc049_a（1922）・abc380_g（1995）・abc149_f（2208）・abc215_g（2276） |
| 対称性 | どの位置も等確率、残りから一様に選ぶ = ランダムな順列 | abc360_e（1249）・abc473_g（1974）・abc464_f（2225）・abc268_g（2311） |
| 幾何分布・コンプガチャ型 | 成功まで $1/p$、全種類 $NH_N$ | arc085_a（752）・abc194_d（1078） |
| 最適戦略の期待値 | 選択は max/min、偶然は平均 | abc266_e（1227）・abc412_f（2038）・abc470_e（2096）・abc421_e（2122）・abc342_f（2141） |
| 方程式（未知数を残す） | $a+bX$ の形、円環の依存を 1 つの未知数で閉じる | arc174_c（1706）・abc333_f（1770）・abc189_f（2154）・abc224_g（2374） |
| 期待値と確率の変換（tail sum） | $E[X]=\sum P(X\ge k)$ | abc295_e（2157）・abc352_g（2413） |
| 総和と期待値の行き来 | 期待値 = 全通りの和 / 総数 | abc276_f（1562）・abc297_f（1990）・abc334_g（2242） |
| 二乗の期待値 | 確率・期待値・二乗の期待値を一緒に運ぶ | abc450_g（2227）・abc277_g（2491） |
| min-max 包除 | 全部（一部）そろうまでの期待値 | abc331_g（2668）・abc242_h（2835） |
| 連続値の確率 | 積分・長さや角度の比 | agc021_b（2130）・abc226_h（2813） |

E 問題（diff 1200〜1700）に「mod で答える期待値・確率の DP」「自己ループ」「対称性」「線形性」が繰り返し出ている。これらは水色帯の必修とみてよい。

### 2.4 ゲームの構造

- **判定の基本**：二人零和有限確定完全情報ゲームでは、終局から後ろ向きに「負け局面へ移れるなら勝ち、どこへ移っても勝ちなら負け」で全局面が決まる。状態が小さければ DP・メモ化再帰（ゲーム DP）、得点があれば「手番の人の得点 − 相手の得点」の 1 本の式（ミニマックス）、遷移にサイクルがあれば逆向きの BFS（後退解析）
- **和の構造**：独立なゲームの和は、各ゲームの Grundy 数の XOR で判定できる（Sprague–Grundy）。Nim はその最も単純な場合。手の選択肢が両者で違う（非不偏）と Grundy 数は使えない
- **考察で決まるもの**：真似戦略（対称な盤面）、手数の偶奇・不変量、規則の発見（実験）。これらは計算より考察の比重が大きい

### 2.5 混同しやすいもの

- 包除の $N(S)$ は「$S$ を**少なくとも**破るもの」であり「ちょうど $S$ を破るもの」ではない
- 重複組合せ（区別しない玉を区別する箱へ）と多項係数（区別する玉をサイズ指定の区別する箱へ）と第2種スターリング数（区別する玉を区別しない箱へ）。写像12相の表で区別の有無を確かめる
- 「区別しない箱だから $k!$ で割る」が正しいのは各箱が空でないときだけ
- 確率 DP（前向きに確率を配る）と期待値 DP（後ろ向きに残りの期待値を求める）
- 期待値の線形性（独立性は要らない）と積の期待値 $E[XY]=E[X]E[Y]$（独立性が要る）
- $E[X^2]$ と $E[X]^2$、「期待値の最大化（最適戦略）」と「最大値の期待値（tail sum）」
- 自己ループの移項（1 状態の方程式）と連立方程式（多状態）とガウスの消去法（一般、06）
- Nim（XOR）と Grundy 数（mex → XOR）と非不偏ゲーム（Grundy 数が使えない）
- ゲーム DP（遷移が DAG）と後退解析（サイクルあり、引き分けがある）
- 約数包除とメビウス反転（同じ計算の 2 つの書き方）、部分集合のゼータ変換と約数のゼータ変換（どちらも軸ごとの累積和）
- 「重複度で割る」と Burnside の補題（重複度が一定でないときは割れない）
- 第1種スターリング数（巡回の個数）と第2種（集合の分割）

### 2.6 ABC での出題傾向（集計の目安）

kmjp・ikatakos の解説がある ABC126〜480 の D〜Ex（773 問）のうち、解説の「解法」部分に各語が現れる問題の数（解説がない問題は数えていないので下限の目安）：

| 語 | D | E | F | G | Ex |
| --- | --- | --- | --- | --- | --- |
| 二項係数（組合せ） | 7 | 22 | 36 | 53 | 31 |
| 期待値・確率 | 3 | 6 | 17 | 22 | 12 |
| 包除 | 0 | 4 | 8 | 11 | 9 |
| ゲーム（必勝・先手・Grundy・Nim） | 1 | 4 | 4 | 10 | 4 |
| 約数包除・メビウス | 0 | 1 | 4 | 2 | 1 |
| ゼータ変換 | 0 | 2 | 3 | 2 | 2 |

- 二項係数は F・G の解説で最も多く現れる語で、黄色を目指すなら前計算・恒等式・格子路は確実に要る
- 期待値・確率は F・G に多いが、kmjp が E をあまり扱わないため E は過小に数えられている。§2.3 のとおり E にも多い
- ゲームは G に偏る。D・E で出るものは状態の小さいゲーム DP（abc354_e（1223）・abc349_e（1464））が中心
- 包除・約数包除・ゼータ変換は F 以降。G・Ex では FPS（06）と組み合わさることが多い

## 3. 項目一覧

全 73 項目。レベル別に 基礎 9・水 22・青 18・黄 13・発展 11。ページ案は単独 39・節 25・概要 9。詳細（別名・問題のサイン・比較対象・図の案・問題）は topics.yaml にある。key のうち他分野のもの（modular-inverse・dp-basics・bit-dp・formal-power-series・gaussian-elimination など）は推測で書いている。

| 項目（key） | レベル | 根拠の問題と difficulty | 前提 | ACL | ページ案 |
| --- | --- | --- | --- | --- | --- |
| 数え上げの考え方（総論）（`counting-mindset`） | 水 | 数え方の設計そのものが問われる問題が水色帯にまとまる：abc167_e (diff 1442)・abc133_e (diff 1505)・abc156_e (diff 1514)。和と積だけで済む abc185_c (diff 374) は茶色以下 | modular-arithmetic | — | 単独 |
| 対応づけ・数える対象の言い換え（`counting-bijection`） | 水 | abc145_d (diff 1009)（移動の回数の組に言い換え）・abc110_d (diff 1695)（素因数ごとの重複組合せへ）で必要。応用は arc058_b (diff 1905)・arc110_d (diff 2078) と青〜黄 | counting-mindset, binomial-coefficient | — | 単独 |
| 補集合で数える（`counting-complement`） | 基礎 | abc178_c (diff 653)・abc162_d (diff 757)・abc156_d (diff 1014) と茶〜緑で頻出。木のパスの色で使う abc163_f (diff 2470) は発展 | counting-mindset | — | 節：counting-mindset |
| 重複の除き方（割る・代表元を決める）（`counting-dedup`） | 青 | abc310_d (diff 1368) は易しめの入口、arc077_b (diff 1715)・abc171_f (diff 1795) と青帯で必須になる | counting-mindset, binomial-coefficient | — | 単独 |
| 順序を固定して数える（`counting-fix-order`） | 水 | abc151_e (diff 1344)・abc133_e (diff 1505) で必要。木の上の順番を数える abc160_f (diff 2048) は黄 | counting-mindset, binomial-coefficient | — | 単独 |
| 「ちょうど」を「以下」の差で数える（`counting-at-most-difference`） | 水 | 考え方は水色帯の数え上げで常用される（abc178_c (diff 653) も同じ構造）。前面に出る例は abc180_f (diff 2419)・arc100_c (diff 2111) と黄以上 | counting-complement | — | 節：counting-mindset |
| 全通りの総和を寄与で数える（`counting-contribution`） | 水 | abc186_d (diff 436) が入口、abc151_e (diff 1344)・abc150_e (diff 1851)・abc173_f (diff 1892)・abc127_e (diff 1938) と水〜青で頻出 | counting-mindset, binomial-coefficient | — | 節：counting-mindset |
| 小さいケースの全探索と OEIS（`counting-experiment`） | 水 | 実験で規則を見つけるのが近道とされる問題が abc398_e (diff 1238)・abc297_g (diff 1834)・abc450_g (diff 2227) と幅広い帯にある | counting-mindset | — | 節：counting-mindset |
| 和・積の法則と順列・組合せ（基礎）（`counting-basics`） | 基礎 | typical90_bq (diff なし)（★3）・abc307_e (diff 1240) と緑以下 | — | — | 単独 |
| 二項係数の意味と性質（`binomial-coefficient`） | 基礎 | arc095_b (diff 867)・abc202_d (diff 966)・abc145_d (diff 1009) など緑以下で必須 | counting-basics | — | 単独 |
| 階乗・逆階乗の前計算による nCr mod p（`binomial-precompute`） | 基礎 | abc145_d (diff 1009)・abc132_d (diff 1167) で必要になり、abc167_e (diff 1442)・abc156_e (diff 1514) と水色帯で頻出 | binomial-coefficient, modular-inverse | なし（atcoder::modint998244353 の inv()・pow() を使って自作する） | 単独 |
| 二項係数の計算の変種（n が巨大・mod が素数でない・正確な値）（`binomial-variants`） | 水 | n が巨大な abc156_d (diff 1014) は緑上位、mod が素数とは限らない abc281_g (diff 2304) は黄 | binomial-precompute | — | 節：binomial-precompute |
| 多項係数（同じものを含む順列）（`multinomial-coefficient`） | 水 | abc234_f (diff 1596) で必須、応用は abc266_g (diff 2045)・arc067_c (diff 2190) と黄 | binomial-precompute | — | 単独 |
| 重複組合せ（玉と仕切り）（`stars-and-bars`） | 基礎 | abc185_c (diff 374)・abc178_d (diff 875)・abc132_d (diff 1167) と緑以下で頻出。応用は abc156_e (diff 1514)・abc110_d (diff 1695) と水〜青 | binomial-coefficient | — | 単独 |
| 写像12相（玉と箱の数え上げの地図）（`twelvefold-way`） | 青 | 重複組合せのマス abc021_d (diff 1704)、集合の分割のマス abc310_d (diff 1368)・abc390_d (diff 1607)、分割数のマス abc226_f (diff 2086) と水〜黄に散らばる | stars-and-bars, binomial-coefficient | — | 単独 |
| 二項係数の恒等式と和の公式（`binomial-identities`） | 青 | abc262_e (diff 1719)・abc154_f (diff 1775)・arc106_d (diff 1988)・arc110_d (diff 2078)・abc290_f (diff 2300) と青〜黄にまとまる | binomial-coefficient, lattice-paths | — | 単独 |
| 格子路の数え上げ（`lattice-paths`） | 水 | 基本は abc145_d (diff 1009)（緑）。禁止領域・障害物つきは arc058_b (diff 1905)（青）、3 次元・座標変換は abc240_g (diff 2462)（発展） | binomial-precompute | — | 単独 |
| 辞書順 k 番目と順位（`kth-combination`） | 基礎 | abc202_d (diff 966)（緑）。順列の順位は BIT と組み合わせる（05） | binomial-coefficient | — | 節：binomial-coefficient |
| Lucas の定理と二項係数の偶奇（`lucas-theorem`） | 青 | arc117_c (diff 1768)・agc043_b (diff 1945) と ARC・AGC の青帯。ABC での直接の出題は見つからなかった | binomial-coefficient, binomial-precompute | — | 単独 |
| 包除原理（`inclusion-exclusion`） | 青 | 2 条件なら abc131_c (diff 518) と茶色。一般形は abc246_f (diff 1677)・abc172_e (diff 1880)・abc152_f (diff 1965)・abc297_f (diff 1990) と青、abc242_f (diff 2268) は黄 | counting-complement, bit-full-search, binomial-coefficient | — | 単独 |
| 包除原理を DP に載せる（`inclusion-exclusion-dp`） | 黄 | abc309_g (diff 2372)・arc115_e (diff 2363) と黄。abc214_g (diff 2893)・arc101_c (diff 2913) は発展 | inclusion-exclusion, dp-basics | — | 単独 |
| 撹乱順列（完全順列）（`derangement`） | 青 | 撹乱順列の包除を一般化した abc172_e (diff 1880)（青）。abc462_g (diff 2232) は黄 | inclusion-exclusion | — | 節：inclusion-exclusion |
| 約数包除（gcd ごとに数える）（`divisor-inclusion-exclusion`） | 青 | abc361_f (diff 1606)・abc304_f (diff 1619)・abc162_e (diff 1662)・abc206_e (diff 1745) と青帯にまとまる | counting-at-most-difference, harmonic-series-complexity | — | 単独 |
| メビウス関数とメビウス反転（`mobius-function`） | 黄 | agc038_c (diff 2327)・agc039_c (diff 2379) と黄、ABC では abc230_g (diff 2516)（発展）。青帯の問題は約数包除で足りる | divisor-inclusion-exclusion, eratosthenes-sieve | — | 単独 |
| 高速ゼータ変換・メビウス変換（部分集合）（`zeta-mobius-subset`） | 黄 | arc100_c (diff 2111)（黄）。ABC では abc213_g (diff 2663)・abc295_h (diff 2728) と発展 | bit-full-search, cumulative-sum | — | 単独 |
| 約数・倍数のゼータ変換・メビウス変換（`zeta-mobius-divisor`） | 青 | 倍数の個数を集める abc393_e (diff 1253)（水）、約数メビウス変換を使う abc474_f (diff 1911)（青）、lcm の総和 agc038_c (diff 2327)（黄） | divisor-inclusion-exclusion, eratosthenes-sieve | — | 単独 |
| 鏡像法とカタラン数（`reflection-principle`） | 黄 | abc205_e (diff 2025)（黄）。abc309_h (diff 3029) は発展 | lattice-paths | — | 単独 |
| カタラン数（`catalan-number`） | 黄 | ABC では鏡像法の一般化として abc205_e (diff 2025) に現れる。括弧列を数える問題は DP で解くことが多い | reflection-principle | — | 節：reflection-principle |
| 第2種スターリング数と全射（`stirling-second`） | 黄 | 全射型の包除 abc242_f (diff 2268)（黄）。区別しないグループ分けの全列挙 abc310_d (diff 1368) は水 | inclusion-exclusion, twelvefold-way | — | 節：twelvefold-way |
| ベル数と集合の分割の列挙（`bell-number`） | 青 | 分割を全列挙する abc310_d (diff 1368)（水）・abc390_d (diff 1607)（青）。B(12)=4213597 なので N ≤ 12 なら全列挙できる | twelvefold-way | — | 節：twelvefold-way |
| 分割数と整数の分割の列挙（`partition-number`） | 黄 | 分割を全列挙する abc226_f (diff 2086)・abc404_f (diff 2162) と黄。分割数型の DP abc221_h (diff 2793) は発展 | twelvefold-way, dp-basics | — | 節：twelvefold-way |
| 第1種スターリング数（`stirling-first`） | 発展 | abc385_g (diff 2492)・abc247_h (diff 2664) とも発展（FPS と組み合わせる） | permutation-cycles, formal-power-series | — | 概要 |
| 置換の巡回分解に基づく数え上げ（`permutation-cycles`） | 黄 | abc226_f (diff 2086)（黄）。abc247_h (diff 2664) は発展 | partition-number, counting-dedup | — | 単独 |
| Burnside の補題（回転などで同一視して数える）（`burnside-lemma`） | 発展 | ABC では abc198_f (diff 2769)（発展）。回転の同一視を最短周期の分類で数える abc428_g (diff 2472)（発展）もある | counting-dedup, gcd-lcm | — | 概要 |
| ラベル付き木の数と Prüfer 列（`cayley-pruefer`） | 黄 | abc290_f (diff 2300)（黄）。abc303_h (diff 2501)・arc106_f (diff 2755) は発展 | multinomial-coefficient, counting-bijection | — | 単独 |
| 行列木定理（`matrix-tree-theorem`） | 発展 | abc253_h (diff 2758)・abc336_g (diff 3138) とも発展 | gaussian-elimination, cayley-pruefer | — | 概要 |
| LGV 補題（交わらない経路の組）（`lgv-lemma`） | 発展 | ABC では abc216_h (diff 3295)（発展）のみ | lattice-paths, gaussian-elimination | — | 概要 |
| 連結なグラフ・構造の数え上げ（`counting-labeled-graphs`） | 黄 | abc281_g (diff 2304)（黄）、abc180_f (diff 2419)・abc213_g (diff 2663) は発展 | counting-complement, bit-dp, binomial-precompute | — | 単独 |
| 二項係数の部分和（`binomial-prefix-sum`） | 発展 | abc235_g (diff 2462)（発展） | binomial-precompute, inclusion-exclusion | — | 概要 |
| 母関数の考え方（数え上げの視点）（`generating-function-counting`） | 発展 | abc303_h (diff 2501)・abc385_g (diff 2492) などで FPS と組み合わせて使う（発展） | stars-and-bars, binomial-identities, formal-power-series | atcoder::convolution（多項式の積） | 概要 |
| Young 図形とフック長公式（`young-tableaux`） | 発展 | ABC では abc378_g (diff 3051)（発展）のみ | partition-number | — | 概要 |
| 確率の基本（`probability-basics`） | 基礎 | abc126_c (diff 638)・abc193_d (diff 866) と茶〜緑 | counting-basics | — | 単独 |
| 確率・期待値を mod 998244353 で答える（有理数の mod 表現）（`rational-mod`） | 水 | abc280_e (diff 1251)・abc323_e (diff 1279)・abc300_e (diff 1354)・abc326_e (diff 1363) と水色帯で頻出 | modular-inverse, probability-basics | atcoder::modint998244353（割り算は inv() を掛ける） | 単独 |
| 期待値の線形性（`linearity-of-expectation`） | 水 | abc154_d (diff 485) は易しい入口。abc334_e (diff 1195)・abc417_f (diff 1414) と緑上位〜水で前面に出て、abc199_f (diff 2065) は黄 | probability-basics | — | 単独 |
| 指示確率変数（個数の期待値を確率の和にする）（`indicator-variables`） | 青 | typical90_bn (diff なし)（★5）・agc049_a (diff 1922)・abc380_g (diff 1995)・abc149_f (diff 2208)・abc215_g (diff 2276) と青〜黄にまとまる | linearity-of-expectation | — | 節：linearity-of-expectation |
| 期待値と確率の変換（E[X] = Σ P(X ≥ k)）（`expectation-tail-sum`） | 黄 | abc295_e (diff 2157)（黄）、abc352_g (diff 2413) は発展 | linearity-of-expectation, counting-at-most-difference | — | 単独 |
| 二乗の期待値・分散（`expectation-of-square`） | 黄 | abc450_g (diff 2227)（黄）、abc277_g (diff 2491)（発展） | linearity-of-expectation, indicator-variables | — | 単独 |
| 条件付き期待値と全期待値の公式（`conditional-expectation`） | 水 | 期待値 DP の漸化式の根拠として dp_j (diff なし)・abc184_d (diff 1276) で使う | probability-basics, linearity-of-expectation | — | 節：expected-value-dp |
| 期待値 DP の数学的側面（後ろ向きに考える理由）（`expected-value-dp`） | 水 | abc280_e (diff 1251)・abc184_d (diff 1276)・abc326_e (diff 1363) と水、abc382_e (diff 1671) は青、abc144_f (diff 2189) は黄 | conditional-expectation, dp-basics | — | 単独 |
| 自己ループの除去（方程式を移項して解く）（`self-loop-expectation`） | 水 | abc300_e (diff 1354)・abc350_e (diff 1385) と水、abc263_e (diff 1659)・abc314_e (diff 1722) は青 | expected-value-dp | — | 節：expected-value-dp |
| 未知数を残す・連立方程式で解く期待値（`expectation-linear-equations`） | 青 | arc174_c (diff 1706)・abc333_f (diff 1770) と青、振り出しに戻る abc189_f (diff 2154) は黄、abc224_g (diff 2374) は黄上位 | self-loop-expectation, gaussian-elimination | — | 単独 |
| 幾何分布（成功するまで繰り返す回数）（`geometric-distribution`） | 基礎 | arc085_a (diff 752)・abc194_d (diff 1078) と緑以下 | probability-basics | — | 節：coupon-collector |
| コンプリートガチャ型（全種類そろうまで）（`coupon-collector`） | 基礎 | 等確率なら abc194_d (diff 1078)（緑）。確率が異なる・一部だけそろえるものは min-max 包除が要り abc331_g (diff 2668)・abc242_h (diff 2835) と発展 | geometric-distribution, linearity-of-expectation | — | 単独 |
| 対称性で確率を求める（`probability-symmetry`） | 水 | abc360_e (diff 1249)（水）、abc473_g (diff 1974)・abc380_g (diff 1995) は青、abc464_f (diff 2225)・abc268_g (diff 2311) は黄 | probability-basics | — | 単独 |
| 最適戦略の期待値（続けるか止めるか）（`optimal-strategy-expectation`） | 水 | abc266_e (diff 1227)（水）。abc412_f (diff 2038)・abc470_e (diff 2096)・abc421_e (diff 2122)・abc342_f (diff 2141) と黄にもまとまる | expected-value-dp | — | 単独 |
| 確率 DP（前向きに確率を配る）（`probability-dp`） | 水 | abc275_e (diff 1264)・abc298_e (diff 1300) と水 | probability-basics, dp-basics | — | 節：expected-value-dp |
| 総和と期待値の行き来（`counting-vs-expectation`） | 青 | abc276_f (diff 1562)（水）・abc297_f (diff 1990)（青）・abc334_g (diff 2242)（黄） | linearity-of-expectation, counting-contribution | — | 節：linearity-of-expectation |
| 連続値の確率（`continuous-probability`） | 発展 | agc021_b (diff 2130)（黄）・abc226_h (diff 2813)（発展） | probability-basics, expectation-tail-sum | — | 概要 |
| ランダムウォーク（`random-walk`） | 青 | abc011_4 (diff 1843)（青）、abc271_g (diff 2323)（黄）・abc463_g (diff 2452)（発展） | binomial-precompute, probability-basics | — | 節：probability-dp |
| ゲームの基本（必勝・必敗の判定）（`game-basics`） | 水 | 基本の判定は tessoku_book_af (diff なし)・dp_k (diff なし)（diff なし）。ABC では abc354_e (diff 1223)・abc270_d (diff 1300) と水 | dp-basics | — | 単独 |
| 必勝・必敗の判定（ゲーム DP）（`game-winning-losing-dp`） | 水 | abc354_e (diff 1223)・abc270_d (diff 1300)・abc278_f (diff 1452) と水、abc195_e (diff 1609)・abc380_f (diff 1769) は青 | game-basics, bit-dp | — | 節：game-basics |
| ミニマックス（得点差を最大化するゲーム）（`minimax`） | 水 | abc201_d (diff 1317)・abc349_e (diff 1464) と水。木の上の abc218_g (diff 2217)・abc246_g (diff 2313) は黄、abc303_g (diff 2736) は発展 | game-basics, dp-basics | — | 単独 |
| サイクルのあるゲーム（後退解析）（`game-retrograde-analysis`） | 黄 | abc209_e (diff 2153)（黄）、abc261_h (diff 2531)（発展） | game-basics, bfs | — | 単独 |
| Nim と XOR（Bouton の定理）（`nim`） | 水 | arc168_b (diff 1289)（水）。Nim の結論を使って考察する abc172_f (diff 2216) は黄 | game-basics, bit-operations | — | 単独 |
| Grundy 数と Sprague–Grundy の定理（`grundy-number`） | 青 | abc368_f (diff 1180)（緑）は易しい入口。Grundy 数が必須の問題は typical90_ae (diff なし)（★6）・abc297_g (diff 1834)・abc206_f (diff 2221)・abc278_g (diff 2533) と青〜黄にまとまる | nim, game-winning-losing-dp | — | 単独 |
| Grundy 数の規則を見つける（`grundy-patterns`） | 青 | abc297_g (diff 1834)（青）、例外つきの abc255_g (diff 2734) は発展 | grundy-number, counting-experiment | — | 節：grundy-number |
| Nim の変種（上限つき・範囲つき・非対称）（`nim-variants`） | 青 | 上限つきの arc168_b (diff 1289)（水）、非対称な arc143_c (diff 1805)（青）、範囲つきの abc297_g (diff 1834)（青） | nim, grundy-number | — | 節：nim |
| 真似戦略・対称戦略（`game-mirror-strategy`） | 青 | arc143_c (diff 1805)・arc105_d (diff 1871) と青、agc014_d (diff 2266) は黄 | game-basics | — | 単独 |
| 偶奇・不変量で決まるゲーム（`game-parity-invariant`） | 青 | abc398_e (diff 1238)（水）・agc033_c (diff 1758)・arc064_b (diff 1814)（青） | game-basics, parity-invariant | — | 節：game-basics |
| 逆形 Nim（最後に取った方が負け）（`misere-nim`） | 発展 | ABC・ARC での出題は確認できなかった（cp-algorithms・OI Wiki で扱われる知識） | nim | — | 節：nim |
| 非不偏ゲーム（組合せゲーム理論）（`partizan-games`） | 発展 | abc229_h (diff 3308)・abc265_h (diff 3319) とも発展 | grundy-number | — | 概要 |
| インタラクティブ形式のゲーム（必勝戦略を実行する）（`interactive-games`） | 水 | 易しい abc244_c (diff 165)（灰）から、abc398_e (diff 1238)（水）・abc278_g (diff 2533)（発展）まで | game-basics, interactive | — | 節：game-basics |
| ゲームの局面を数える（`nim-counting`） | 発展 | abc212_h (diff 2741)（発展） | nim, xor-convolution | — | 節：nim |

## 4. 項目ごとのメモ

各項目の「何ができるか・なぜ正しいか・つまずき・図・確認問題・問題のサイン・使い分け」。レベルとその根拠は §3 の表と topics.yaml にある。

### 4.1 数え方の考え方

#### counting-mindset 数え上げの考え方（総論）

- **何ができるか**：数え上げを「数える対象を確定する → 数えやすい形に言い換える → 排反な場合に分けて和、独立な段階に分けて積 → 重複と漏れを確かめる → 小さいケースで検算する」という手順で解く。個々の道具（二項係数・包除など）はこの手順の部品として使う
- **なぜ正しいか**：数え上げの正しさは「どの対象もちょうど1回数えられる」ことに尽きる。和の法則は分類が排反かつ網羅的であること、積の法則は「前の段階で何を選んでも、次の段階の選択肢の数が同じ」であることが条件。積の法則の条件が崩れている（前の選び方で選択肢の数が変わる）のに掛けてしまうのが典型的な誤り
- **つまずき**：玉・箱・グループを区別するかどうかの取り違え、空を許すかどうか、「選ぶ」と「並べる」の混同、「少なくとも」と「ちょうど」の混同、数える順番を工夫すれば積の法則が使えるのに気づかない（abc133_e は BFS 順に塗ると各頂点の選択肢の数が一定になる）
- **図**：同じ対象を2通りの見方で数える図（格子路と R/U の列）。樹形図で「次の段階の枝の数が一定か」を色分けする図
- **確認問題**：「3人を区別しない2つの組に分ける方法は何通りか。組を区別するとどうなるか」「赤玉3個・白玉2個の並べ方と、5人から2人を選ぶ方法が同じ数になるのはなぜか」
- **問題のサイン**：「〜の個数を 998244353 で割った余り」「何通りあるか」「すべての〜についての総和」
- **使い分け**：N が小さければ全探索、状態で数えられるなら DP（02）、閉じた式があるなら組合せの式。式と DP の折衷（DP の遷移に二項係数を掛ける）も多い
- **ページ案**：総論1ページに「和と積」「対応づけ」「補集合」「重複の除き方」「順序の固定」「ちょうど＝以下の差」「寄与」「検算」の節を置き、重い3つ（対応づけ・重複の除き方・順序の固定）は個別ページにする

#### counting-bijection 対応づけ・数える対象の言い換え

- **何ができるか**：数えにくい対象を、個数が同じで数えやすい対象に1対1で対応させる
- **典型の対応**：
  - 広義単調増加列 $1 \le a_1 \le \dots \le a_k \le n$ ↔ $b_i = a_i + i - 1$ とした狭義単調列 ↔ $\{1,\dots,n+k-1\}$ の $k$ 元部分集合（$\binom{n+k-1}{k}$）
  - 長さ $L$ の棒を $k$ 本の正の長さに切る方法 ↔ $L-1$ か所の切れ目から $k-1$ 個を選ぶ（abc185_c）
  - 格子路 ↔ R と U の列 ↔ R を置く位置の選び方
  - ナイトの移動（$(+1,+2)$ と $(+2,+1)$）↔ 各移動の回数を連立方程式で決めてから、その並べ方を数える（abc145_d）
  - 括弧列 ↔ ±1 の列で途中で負にならないもの ↔ 対角線を越えない格子路（カタラン数・鏡像法へ）
  - ラベル付き木 ↔ 長さ $n-2$ の Prüfer 列（cayley-pruefer）
- **なぜ正しいか**：逆向きの写像が作れる（全単射）なら個数は等しい。「逆に戻せるか」を確かめるのが対応づけの検算になる
- **つまずき**：対応が単射でない（同じ対象に複数の表現がある）と重複して数える。とくに「操作の結果」を「操作の列」で数えると、同じ結果を作る別の操作列を重ねて数えてしまう（→ counting-dedup）
- **図**：左に元の対象、右に言い換えた対象を並べ、対応を線で結ぶ。片方をクリックで変えるともう片方も変わる動く図
- **確認問題**：「$1 \le a_1 < a_2 < \dots < a_k \le n$ の個数は。不等号を $\le$ に変えるとどうなるか」「長さ $L$ の棒を 12 本に切る方法を、切れ目の選び方に言い換えよ」
- **問題のサイン**：「単調な数列の個数」「切り分け方」「経路の数」「ある条件を満たす列で途中の和が負にならない」
- **使い分け**：対応づけで二項係数に落ちれば O(1)、落ちなければ DP。言い換えの候補として「格子路に帰着できないか」をまず疑う（drken の「経路数に帰着」系の問題群）

#### counting-complement 補集合で数える

- **何ができるか**：「少なくとも1つ〜を満たす」「いずれかが〜」を、全体から「1つも満たさない」を引いて数える
- **典型**：0 と 9 を両方含む長さ $N$ の数字列 $= 10^N - 2\cdot 9^N + 8^N$（abc178_c。2条件の包除そのもの）、条件付きの3つ組を全体から悪い組を引いて数える（abc162_d）、選び方の総数 $2^n-1$ から禁止された本数の場合を引く（abc156_d）、「色 $k$ の頂点を含むパスの数 = 全パス − 色 $k$ を避けるパス」（abc163_f）
- **なぜ正しいか**：全体 = 条件を満たす + 満たさない、が排反な分割だから
- **つまずき**：mod での引き算で負になる（`(a - b + mod) % mod`。modint なら気にしなくてよい）。「1つもない」も直接数えにくい場合は包除原理へ進む
- **確認問題**：「長さ $N$ の 0〜9 の列で 0 を含むものは。0 と 9 の両方を含むものは」
- **問題のサイン**：「少なくとも1つ」「〜を含む」「いずれかが」
- **境界**：余事象の一般論は 01（考察系）。07 では数え上げでの使い方と包除原理への入口として総論の節で扱う

#### counting-dedup 重複の除き方

- **何ができるか**：同じ対象を複数回数えてしまうときに、ちょうど1回にする
  1. **重複度が一定なら割る**：同じものを含む順列 $n!/(a!\,b!\,\cdots)$、円順列 $(n-1)!$、区別のないグループに分けるときの $k!$ 
  2. **重複度が一定でないなら代表元（正規形）を決めて、代表元だけを数える**：部分列として含む文字列を「最も左で一致させる埋め込み」で数える（abc171_f Strivore）、1か所だけ値が重複する列の部分列の種類数（arc077_b 11）、グループ分けで「まだ組に入っていない最小番号の人」から順に組を決める（abc310_d Peaceful Teams、drken の「最小添字規則によってダブルカウントを防ぐ」）
  3. **回転・反転などの対称性で同一視するなら Burnside の補題**（発展、burnside-lemma）
- **なぜ正しいか**：1 は各対象がちょうど $c$ 回ずつ数えられるので $c$ で割れる。2 は各対象に代表元がちょうど1つ対応するので、代表元の数が対象の数になる
- **つまずき**：重複度が一定でないのに割る（回転で同一視する数珠で $k^n/n$ とすると、対称な塗り方の重複度が小さいので誤り。そもそも割り切れないこともある）。最左マッチでは「一致させた文字の間にある文字は、次に一致させたい文字以外」という条件を落としやすい
- **図**：同じ文字列に部分列 S が何通りにも埋め込める様子と、最も左の埋め込みだけを残す様子のステップ送り
- **確認問題**：「"aab" の並べ替えを $3!/2!$ で数えてよいのはなぜか」「6 個の玉の数珠を 4 色で塗り回転で同一視するとき、$4^6/6$ が答えにならないのはなぜか」
- **問題のサイン**：「異なる〜の個数」「操作で作れる文字列の種類数」「区別しない」「〜として含む」
- **使い分け**：割れるか（重複度が一定か）→ 代表元を決められるか → 対称性なら Burnside、の順に検討する。代表元の数え上げは DP（部分列 DP）になることが多い（02 との境界）

#### counting-fix-order 順序を固定して数える

- **何ができるか**：並べ方の自由度の一部を固定して数え、あとで掛けるか割る。あるいは数える順番を工夫して積の法則が使える形にする
- **典型**：
  - 相対順序が決まった $k$ 個を含む $n$ 個の並べ方 $= n!/k! = \binom{n}{k}(n-k)!$
  - ソートしてから「$a_i$ が最大になる組合せの数 $\binom{i-1}{K-1}$」で寄与を数える（abc151_e）
  - 木の頂点に「親が子より先」となる順番を付ける方法 $= n!/\prod(\text{部分木のサイズ})$（abc160_f。各部分木の根が部分木の中で最初に来る確率 $1/\text{size}$ の積と読める）
  - BFS 順に色を決めると、各頂点で使える色の数が前の選び方によらず一定になる（abc133_e）
- **なぜ正しいか**：すべての順序が等しく現れる対称性があるとき、条件を満たす順序はその比率だけ残る。積の法則が使えるのは「次の段階の選択肢の数が一定」になる順番で決めたときだけ
- **つまずき**：固定した部分が全体の何分の一かを取り違える。順番を変えたら選択肢の数が一定でなくなる（DFS 順では成り立たないことがある）
- **図**：$k$ 個の相対順序 $k!$ 通りのうち1通りだけ残す図
- **確認問題**：「1, 2, 3 がこの順に現れる 5 個の並べ方は何通りか」「木の根から順に色を塗るとき、なぜ子の選択肢の数が兄弟の塗り方に依存しないのか」
- **問題のサイン**：「〜より先に」「順番の制約」「木の頂点に番号を振る」「最大値（最小値）に注目」
- **使い分け**：順序を状態に持つ DP（挿入 DP・bitDP、02）は、閉じた式が見つからないときの代替

#### counting-at-most-difference 「ちょうど」を「以下」の差で数える

- **何ができるか**：「最大値がちょうど $k$」＝「すべて $k$ 以下」−「すべて $k-1$ 以下」のように、累積の形で数えてから差を取る。$k^n-(k-1)^n$ が典型
- **典型**：最大の連結成分のサイズがちょうど $L$ のグラフの数（abc180_f）、最大値・最小値の期待値（expectation-tail-sum へ）、「ちょうど $K$ 個」を「$K$ 個以上」の差で求める（drken「K以上からK+1以上を引く」）
- **なぜ正しいか**：「$\le k$」の集合は「$= k$」と「$\le k-1$」に排反に分かれる
- **つまずき**：$k=0$ や下限の扱い。「以下」の側が数えやすい形になっているかを先に確かめる
- **関係**：約数包除（gcd ちょうど $g$ を「$g$ の倍数」から引く）と包除原理（ちょうど0個を「少なくともこれら」から求める）は同じ発想の一般化
- **ページ案**：総論の節で足りる

#### counting-contribution 全通りの総和を寄与で数える

- **何ができるか**：「すべての選び方についての $f$ の総和」を、$f$ を部分の和に分け、各部分について「その部分が効く選び方の数」を掛けて足す（和の順序の交換）
- **典型**：ソート後の $\max-\min$ の総和（abc151_e）、選んだ $K$ マスのすべての組の距離の総和を「2マスの組 × 残りの選び方 $\binom{NM-2}{K-2}$」で数える（abc127_e）、区間ごとの連結成分数の総和を「頂点数 − 辺数」の寄与で数える（abc173_f）、ソートして各要素の係数を求める（abc150_e）
- **なぜ正しいか**：二重和の順序の交換。$\sum_{\text{選び方}} \sum_{\text{部分}} [\text{部分が効く}]\cdot w = \sum_{\text{部分}} w \cdot \#\{\text{部分が効く選び方}\}$
- **つまずき**：「効く選び方の数」に二項係数の端（$K<2$ など）が入るときの 0 の扱い。寄与が独立でない（同じ選び方で2回効く）ときの数え過ぎ
- **境界**：寄与・主客転倒の一般論は 01。07 では「二項係数と組み合わせる総和の数え上げ」と「期待値の線形性との同型性（総和 = 期待値 × 総数）」に絞る
- **問題のサイン**：「すべての〜についての総和」「$\binom{N}{K}$ 通りの選び方それぞれについて〜を求め、その和」

#### counting-experiment 小さいケースの全探索と OEIS

- **何ができるか**：小さい $n$ を全探索して数列を得て、規則（漸化式・閉じた式）を推測し、OEIS で既知の数列か確かめる。式を作った後の検算にも使う
- **手順**：全探索のコード → $n=1..8$ 程度の値 → 差分・比・素因数分解を見る → OEIS で検索 → 推測した式と全探索を大きめの $n$ で照合
- **つまずき**：mod を取った値では規則が見えない（小さいケースは mod なしで出す）。確率・期待値は分数に戻して見る（rational-mod の「有理数復元」）
- **境界**：ストレステスト一般は 00（コンテストの戦い方）。Grundy 数の規則の発見（grundy-patterns）も同じ手法
- **ページ案**：総論の節か、00 の「実験」ページへのリンクで足りる

### 4.2 道具：二項係数まわり

#### counting-basics 和・積の法則と順列・組合せ（基礎）

- **何ができるか**：$n$ 個から $k$ 個を並べる $nPk = n!/(n-k)!$、選ぶ $\binom{n}{k}$、重複を許して並べる $n^k$、円順列 $(n-1)!$
- **つまずき**：積の法則の条件（前の選択によらず選択肢の数が一定）。隣り合う色が異なる塗り分けで「最初は $K$ 通り、以降は $K-1$ 通り」としてよい一列の場合と、円環で最後が最初とも隣り合う場合（abc307_e）の違い
- **確認問題**：「一列 $N$ 個を $K$ 色で隣が異なるように塗る方法は。円環ならどうか」
- **問題のサイン**：「何通り」「並べ方」「塗り分け」
- **関係**：典型90 069（距離2以内が異なる塗り分け → $K(K-1)(K-2)^{N-2}$）は積の法則と繰り返し二乗法の組合せ

#### binomial-coefficient 二項係数の意味と性質

- **何ができるか**：$\binom{n}{k}$ を「$n$ 個から $k$ 個を選ぶ」「0/1 列で 1 が $k$ 個」「格子路」の3つの意味で使い分ける
- **性質**：パスカルの漸化式 $\binom{n}{k}=\binom{n-1}{k-1}+\binom{n-1}{k}$（最後の1個を選ぶか選ばないか）、対称性 $\binom{n}{k}=\binom{n}{n-k}$、$k<0$ や $k>n$ では 0 と約束する（和の式で端を気にせず書けるようにするため）、$\binom{n}{k}$ は $k=\lfloor n/2\rfloor$ で最大（arc095_b）
- **つまずき**：mod なしで計算するときのオーバーフロー（$\binom{60}{30}\approx 1.2\times10^{17}$ は 64 bit に収まるが、$\binom{67}{33}$ は $2^{63}$ を超える）。$\binom{n}{k}$ を $n!/(k!(n-k)!)$ で直接計算すると途中の階乗があふれる
- **図**：パスカルの三角形を、各値が「上の2つの和」になる様子と、格子路の数としての読み替えを並べて示す
- **確認問題**：「$\binom{n}{k}=\binom{n-1}{k-1}+\binom{n-1}{k}$ を『最後の1人を選ぶか』で説明せよ」
- **使い分け**：mod 素数で $n$ が $10^7$ 程度まで → 前計算（binomial-precompute）。$n$ が小さく mod が任意 → パスカルの三角形。$n$ が巨大で $k$ が小さい → binomial-variants

#### binomial-precompute 階乗・逆階乗の前計算による nCr mod p

- **何ができるか**：素数 $p$ について、$0..N$ の階乗 `fact` と逆階乗 `ifact` を $O(N+\log p)$ で前計算し、$\binom{n}{k}=\text{fact}[n]\cdot\text{ifact}[k]\cdot\text{ifact}[n-k]$ を $O(1)$ で答える
- **処理の流れ**：`fact[0]=1, fact[i]=fact[i-1]*i` → `ifact[N]=fact[N]^{p-2}`（逆元は 06）→ `ifact[i-1]=ifact[i]*i` を $i=N..1$ で後ろから。後ろから作るのは $1/(i-1)! = i \cdot 1/i!$ だから。逆元を1回だけ求めればよい
- **つまずき**：テーブルの大きさが足りない（必要な最大の $n$ は $H+W$、$N+K$、$2N$ などになる）。$n \ge p$ では $n! \equiv 0$ になり使えない（Lucas へ）。$k<0$・$k>n$ の 0 の処理を忘れる。$N=10^7$ では 64 bit 配列2本で 160 MB になるので 32 bit で持つ
- **ACL**：ACL に二項係数の関数はない。`atcoder::modint998244353` の `inv()`・`pow()` を使って自作する（ACL のドキュメント modint.md）
- **確認問題**：「逆階乗を前から $1/i! = 1/(i-1)! \cdot 1/i$ で作ると何が困るか（各 $i$ の逆元が必要になる）」「$H, W \le 10^5$ の格子路で、テーブルはどこまで要るか」
- **問題のサイン**：「998244353 で割った余り」「$N \le 2\times10^5$ で選び方の数」
- **関係**：mod の逆元・Fermat の小定理そのものは 06

#### binomial-variants 二項係数の計算の変種

- **何ができるか**：前計算が使えない状況での二項係数
  - $n$ が巨大（$10^9$ など）で $k$ が小さい：$\binom{n}{k} = \frac{n(n-1)\cdots(n-k+1)}{k!}$ を $O(k)$ で（abc156_d：$n \le 10^9$、$a,b \le 2\times10^5$）
  - mod が素数でない・小さい：パスカルの三角形を $O(n^2)$ で（$n \le 5000$ 程度。abc281_g は mod が入力で与えられ素数とは限らないので、この方法で二項係数を作る）。小さい素数なら Lucas（lucas-theorem）、素数冪や合成数は CRT と組み合わせる方法がある（発展）
  - mod なしの正確な値：`__int128` や逐次 $\binom{n}{k}=\binom{n}{k-1}\cdot(n-k+1)/k$（この順に掛けてから割ると毎回割り切れる）。確率の計算では `long double` や対数（`lgamma`）で
- **つまずき**：逐次計算で「割ってから掛ける」と割り切れない。double で大きな二項係数を扱って桁落ち
- **確認問題**：「$\binom{10^9}{3}$ を mod $p$ で求める手順は」「mod が $10^9$（合成数）のとき前計算の方法が使えないのはなぜか」
- **問題のサイン**：「$n \le 10^9$」「mod $M$ は入力で与えられる（素数とは限らない）」

#### multinomial-coefficient 多項係数（同じものを含む順列）

- **何ができるか**：種類ごとの個数が $a_1,\dots,a_m$ の並べ方 $\frac{(a_1+\cdots+a_m)!}{a_1!\cdots a_m!}$。ラベル付きの $n$ 個をサイズ指定の区別あるグループに分ける方法も同じ式
- **典型**：使う文字の個数を DP で決め、合流のたびに $\binom{\text{全体}}{\text{追加分}}$ を掛ける（abc234_f Reordering）。ブロックを先に並べてから残りを挿入する（abc266_g）。同じサイズのグループが $c$ 個あれば $c!$ で割る（arc067_c）
- **なぜ正しいか**：全部区別した $n!$ 通りを、同じ種類の入れ替え $a_i!$ 通りずつで割る（各並べ方がちょうど $\prod a_i!$ 回数えられる）
- **つまずき**：グループを区別しないとき、同じサイズのグループの入れ替えでさらに割るのを忘れる
- **確認問題**：「"MISSISSIPPI" の並べ替えは何通りか」「6 人を 2 人ずつ区別のない 3 組に分ける方法は」
- **問題のサイン**：「文字の並べ替えでできる文字列の個数」「各文字を使う個数が決まっている」

#### stars-and-bars 重複組合せ（玉と仕切り）

- **何ができるか**：$x_1+\cdots+x_k=n$ の非負整数解の数 $\binom{n+k-1}{k-1}$、正の整数解の数 $\binom{n-1}{k-1}$。「$\le n$」は余りの変数を1つ足して等式にする。広義単調列の個数も同じ
- **典型**：棒を 12 本に切る（abc185_c）、各素因数の指数を $N$ 個に配る（abc110_d）、$K$ 個の青玉を $i$ 個のかたまりに分けて赤玉の間に入れる $\binom{K-1}{i-1}\binom{N-K+1}{i}$（abc132_d）、空き部屋の数で場合分けして配り方を数える（abc156_e）、多重ループの回数（abc021_d）
- **隣り合わない選び方**：$n$ 個から隣り合わない $k$ 個を選ぶ方法 $\binom{n-k+1}{k}$、間隔を $d$ 以上空けるなら $\binom{n-(k-1)(d-1)}{k}$（典型90 015。各 $d$ で $k \le n/d$ なので全体で調和級数の $O(n\log n)$）
- **なぜ正しいか**：$n$ 個の玉と $k-1$ 本の仕切りの並べ方と1対1に対応する
- **つまずき**：0 を許すか（非負か正か）の取り違え。上限 $x_i \le c$ がつくと単純な式にならない（包除で「上限を破る変数の集合」を数える）
- **図**：玉と仕切りの列を、変数の値の組に対応させる図（仕切りを動かすと値が変わる）
- **確認問題**：「$x+y+z=10$ の正の整数解は。$x \le 3$ という制限がつくと」
- **問題のサイン**：「和が $N$ になる非負整数の組」「単調な列の個数」「分け方（区別のない玉を区別のある箱へ）」

#### twelvefold-way 写像12相（玉と箱の数え上げの地図）

- **何ができるか**：$n$ 個の玉を $k$ 個の箱に入れる方法を「玉を区別するか × 箱を区別するか × 制限なし／各箱 1 個以下／各箱 1 個以上」の 12 通りに整理する地図
- **表**（玉→箱）：
  - 玉○・箱○：制限なし $k^n$、1 個以下 $k^{\underline{n}}$、1 個以上 $k!\,S(n,k)$（全射。包除で $\sum_i (-1)^i\binom{k}{i}(k-i)^n$）
  - 玉×・箱○：$\binom{n+k-1}{n}$、$\binom{k}{n}$、$\binom{n-1}{k-1}$（重複組合せ）
  - 玉○・箱×：$\sum_{j\le k} S(n,j)$（ベル数の部分和）、$[n\le k]$、$S(n,k)$（第2種スターリング数）
  - 玉×・箱×：分割数 $p(n,k)$（$k$ 個以下の部分への分割）、$[n\le k]$、$p(n-k,k)$（ちょうど $k$ 個の部分）
- **なぜ正しいか**：箱を区別しない場合は「箱を区別した数え方」をそのまま $k!$ で割れない（空の箱があると重複度が変わる）ので、別の数（スターリング数・分割数）が要る
- **つまずき**：「箱を区別しないから $k!$ で割る」が成り立つのは各箱が1個以上（全射）のときだけ
- **図**：12 マスの表をクリックすると、そのマスの小さい例（$n=4,k=3$）の全列挙が出る図
- **ABC の例**：重複組合せのマス（abc021_d）、第2種スターリング数のマスに条件がついたもの（abc310_d）、ベル数のマスの全列挙（abc390_d）、分割数のマスの全列挙（abc226_f）
- **練習**：AOJ DPL_5_A〜L（12 マスに対応する 12 問。AtCoder 以外。drken の写像12相の記事の問題集）
- **問題のサイン**：「区別しない」「グループに分ける」「各グループ 1 人以上」
- **ページ案**：地図としての独立ページ（短め）。各マスの詳しい扱いは stars-and-bars・stirling-second・bell-number・partition-number へ

#### binomial-identities 二項係数の恒等式と和の公式

- **何ができるか**：二項係数を含む和を閉じた式にする
  - 二項定理 $(a+b)^n=\sum\binom{n}{k}a^kb^{n-k}$、$\sum_k\binom{n}{k}=2^n$、$\sum_k(-1)^k\binom{n}{k}=[n=0]$（包除原理の根拠）
  - 偶数番目の和 $=2^{n-1}$（$n\ge1$）。偶奇の条件つきの和は「奇数のものを偶数個選ぶ」$\sum_{i\,\text{偶数}}\binom{a}{i}\binom{b}{K-i}$ の形で数える（abc262_e：端点の色が異なる辺の数の偶奇を、赤い頂点の次数の和の偶奇に言い換える）
  - Vandermonde $\sum_i\binom{a}{i}\binom{b}{k-i}=\binom{a+b}{k}$（2グループから合計 $k$ 個を選ぶ）、その拡張で経路数に帰着する（arc110_d）
  - 縦の和（hockey stick）$\sum_{i=r}^{n}\binom{i}{r}=\binom{n+1}{r+1}$：長方形領域の経路数の総和（abc154_f）
  - 吸収 $k\binom{n}{k}=n\binom{n-1}{k-1}$：$\sum k\binom{n}{k}=n2^{n-1}$
  - 二項定理で $(A_i+A_j)^x$ の全ペアの和をまとめる（arc106_d）
- **なぜ正しいか**：どれも「同じものを2通りに数える（ダブルカウント）」で説明できる。Vandermonde は2グループからの選び方、hockey stick は「最後に選ぶ要素の位置」で分類
- **つまずき**：和の範囲の端（$\binom{n}{-1}=0$ の約束を使うと楽）。式変形が正しいかは小さいケースで検算する
- **図**：パスカルの三角形の上で、hockey stick の斜めの和が1つ下のマスになる様子
- **確認問題**：「$\sum_{i=0}^{n}\binom{i}{2}$ を閉じた式にせよ。なぜそうなるかを『3つ選んだうち最大のもの』で説明せよ」
- **問題のサイン**：「$\sum$ の中に二項係数」「$N$ が大きく和を直接計算できない」「長方形領域の各点への経路数の総和」

#### lattice-paths 格子路の数え上げ

- **何ができるか**：$(0,0)$ から $(a,b)$ への右・上の最短経路 $\binom{a+b}{a}$。禁止領域や障害物、移動の種類が違うものへの拡張
- **典型**：ナイト移動を回数の組に直して二項係数（abc145_d）、左下の長方形を避ける経路を「境界を越える点」で分類して足す（arc058_b）、長方形領域の経路数の総和を hockey stick で（abc154_f）、障害物が多いときは障害物をソートして「最初に踏む障害物」で分類する DP（dp_y、包除の側は inclusion-exclusion-dp）、3 次元や斜めの移動は座標変換して独立な成分に分ける（abc240_g）、二項係数の和を経路数として DP で一括計算する（agc001_e）
- **つまずき**：障害物の「最初に踏む」の定義（ソート順）を間違えると重複する。座標変換の後の偶奇条件（到達できない点）を落とす
- **図**：格子を描き、各点の経路数を左下から順に埋めるステップ送り。障害物ありでは「最初に踏む障害物」で色分けした経路の図
- **確認問題**：「$(0,0)\to(3,2)$ の経路は何通りか。$(1,1)$ を通らないものは」
- **問題のサイン**：「グリッドの左上から右下へ」「通れないマス」「$H, W \le 10^5$」（DP では間に合わない → 二項係数）
- **ページ案**：基本（基礎）と障害物・総和（青〜黄）を1ページの節に分ける

#### kth-combination 辞書順 k 番目と順位

- **何ができるか**：辞書順で $k$ 番目の文字列・組合せ・順列を、先頭から1文字ずつ「この文字にしたときの残りの並べ方の数」と $k$ を比べて決める（abc202_d：a と b の並べ方の $K$ 番目）。逆に、与えられた順列が何番目かは「各位置でそれより小さい未使用の数の個数 × 残りの階乗」の和（数える部分は BIT、05）
- **なぜ正しいか**：辞書順では先頭が小さいものがすべて先に来るので、先頭を決めるごとに「飛ばせる個数」が二項係数や階乗で分かる
- **つまずき**：$k$ を 0 始まりにするか 1 始まりにするか。残りの数が $10^{18}$ を超えるときのオーバーフロー（上限で打ち切る）
- **確認問題**：「a 2 個・b 2 個の並べ方を辞書順に並べたとき 4 番目は」
- **問題のサイン**：「辞書順で $K$ 番目」「何番目か」

#### lucas-theorem Lucas の定理と二項係数の偶奇

- **何ができるか**：素数 $p$ が小さい（$n \ge p$ になりうる）とき、$\binom{n}{k} \equiv \prod_i \binom{n_i}{k_i} \pmod p$（$n_i, k_i$ は $p$ 進法の各桁）。特に $p=2$ では「$\binom{n}{k}$ が奇数 ⇔ $k$ の 1 のビットが $n$ でもすべて 1（`(n & k) == k`）」
- **典型**：隣り合う2つから1つを作る操作を繰り返すピラミッドで、最後の値が $\sum\binom{N-1}{i}a_i$ になる（係数が二項係数）ことを見抜き、mod 3（arc117_c）や mod 2（agc043_b）で Lucas を使う
- **なぜ正しいか**：$(1+x)^p \equiv 1+x^p \pmod p$ から $(1+x)^n=\prod_i(1+x^{p^i})^{n_i}$ と分解でき、$x^k$ の係数を $p$ 進の桁ごとに取り出せる
- **つまずき**：前計算の nCr を $n \ge p$ で使って 0 を返してしまう。mod 2 で「差の絶対値」を「和」と同一視してよい理由（偶奇は変わらない）を押さえる
- **図**：パスカルの三角形を mod 2 で塗るとシェルピンスキーの三角形になる図
- **確認問題**：「$\binom{10}{3}$ は奇数か偶数か（10 = 1010₂、3 = 0011₂）」
- **問題のサイン**：「隣り合う2つから新しい値を作る操作を繰り返す（三角形・ピラミッド）」「mod 2・mod 3 など小さい素数」
- **レベル**：ARC・AGC 中心（青）。ABC での直接の出題は見つからなかった

### 4.3 道具：包除原理の系統

#### inclusion-exclusion 包除原理

- **何ができるか**：「条件 $1..m$ のどれも破らないもの」の個数を、「指定した条件の集合 $S$ をすべて破るもの（他は自由）」の個数 $N(S)$ から $\sum_S (-1)^{|S|} N(S)$ で求める。$N(S)$ が $|S|=k$ だけで決まるなら $\sum_k (-1)^k\binom{m}{k} f(k)$ にまとまる
- **典型**：
  - 2〜3 条件：$C$ の倍数でも $D$ の倍数でもない数（abc131_c、$\mathrm{lcm}$ を使う）、0 と 9 を両方含む列（abc178_c）、3 か 5 の倍数（tessoku A31）
  - 条件を bit 全探索：木のパスの制約 $M \le 20$ 個のうち、指定した集合のパス上の辺をすべて白にする塗り方（abc152_f）、使える文字集合の共通部分ごとに数える（abc246_f）
  - 対称性で $k$ ごとにまとめる：$A_i \ne B_i$ を「一致する位置を $k$ 個指定」で包除（abc172_e。撹乱順列の一般化）、行・列をすべて使う配置（abc242_f）、4 辺がすべて点を含む長方形（abc297_f）
- **なぜ正しいか**：ちょうど $t$ 個の条件を破る対象は、$\sum_S$ の中で $S$ がその $t$ 個の部分集合のときだけ数えられ、合計 $\sum_{j}(-1)^j\binom{t}{j}=[t=0]$ 回になる。だから「1つも破らないもの」だけが1回ずつ残る
- **つまずき**：$N(S)$ を「ちょうど $S$ を破る」と取り違える（正しくは「少なくとも $S$ を破る」）。符号の付け方、空集合を含め忘れる、$\mathrm{lcm}$ のオーバーフロー（$10^{18}$ を超えたら打ち切る）、$2^m$ の全探索が $m \le 20$ 程度までしか使えないこと
- **図**：ベン図で3集合の和集合を数える様子（足しすぎ・引きすぎの領域が順に打ち消し合う）のステップ送り
- **確認問題**：「1〜100 で 2, 3, 5 のいずれでも割り切れない数は何個か」「$N(S)$ を『ちょうど $S$ の条件を破るもの』にすると何がおかしくなるか」
- **問題のサイン**：「すべて異なる」「どの〜も〜ない」「各〜を少なくとも1回使う」「制約 $M \le 20$ の禁止条件」「$A_i \ne B_i$」
- **使い分け**：条件が少数 → bit 全探索、条件が対称 → $k$ ごとにまとめる、条件が列に沿って並ぶ → 包除 DP（inclusion-exclusion-dp）、条件が約数の構造 → 約数包除・メビウス
- **ページ案**：2 集合の補集合の延長（基礎）から一般形（青）までを1ページに。包除 DP は別ページ（黄）

#### inclusion-exclusion-dp 包除原理を DP に載せる

- **何ができるか**：包除の和 $\sum_S(-1)^{|S|}N(S)$ の項が多すぎて列挙できないとき、$S$ の選び方を DP で数え、符号 $(-1)^{|S|}$ を DP の値に掛けて運ぶ
- **典型**：
  - 「最初に踏む障害物」で分類：障害物をソートし、$dp[i]$ = 他の障害物を通らずに障害物 $i$ に着く経路数 = 全経路 − $\sum_{j} dp[j]\cdot(j \to i)$（dp_y Grid 2）。これは「最初の悪いイベント」で分類する包除の変形
  - 符号付き DP：木の辺を「切る（条件を破らせる）」と決めた集合ごとに $(-1)^{\text{切った本数}}$ を掛けて木 DP（arc101_c Ribbons on Tree）
  - 違反の個数を状態に持ち、最後に $(-1)^k \cdot (\text{残りの自由度})$ を掛ける（abc214_g Three Permutations など）
- **なぜ正しいか**：包除の和は「$S$ ごとの重み $(-1)^{|S|}N(S)$ の総和」なので、$S$ を作る過程を DP にし、重みを積として運べば同じ値になる
- **つまずき**：障害物のソート順（$x$ と $y$ の両方で前にあるものだけが遷移元）、終点を障害物の1つとして扱うと楽なこと、符号の付け忘れ
- **図**：障害物を並べて「最初の障害物」で経路を色分けする図
- **確認問題**：「障害物が1つのときの式を、この DP の式に当てはめて確かめよ」
- **問題のサイン**：「障害物 $N \le 3000$、グリッド $10^5$」「禁止条件が列や木に沿って並ぶ」
- **境界**：DP の状態設計は 02。07 では「包除の和を DP で数える」という見方と符号の意味を扱う

#### derangement 撹乱順列（完全順列）

- **何ができるか**：$p_i \ne i$ がすべての $i$ で成り立つ順列の数 $D_n$。包除で $D_n = \sum_k (-1)^k\binom{n}{k}(n-k)! = n!\sum_k (-1)^k/k!$、漸化式 $D_n=(n-1)(D_{n-1}+D_{n-2})$
- **典型**：abc172_e（$A$ と $B$ がともに単射で $A_i \ne B_i$。撹乱順列の包除をそのまま一般化した形）
- **なぜ正しいか**：漸化式は「1 の行き先 $j$（$n-1$ 通り）を決め、$j$ が 1 に行くか行かないかで分ける」
- **つまずき**：$D_n/n! \to 1/e$ なので、ランダムな順列に固定点がない確率は約 0.368
- **ページ案**：包除原理のページの例として節で扱う

#### divisor-inclusion-exclusion 約数包除（gcd ごとに数える）

- **何ができるか**：「gcd がちょうど $g$」の個数 $f(g)$ を、「すべて $g$ の倍数」の個数 $F(g)$（数えやすい）から、大きい $g$ の順に $f(g)=F(g)-\sum_{m=2g,3g,\dots}f(m)$ で求める。全体で調和級数の $O(N\log N)$
- **典型**：$\gcd$ の総和 $\sum_g g\cdot f(g)$（abc162_e）、$\gcd(x,y)$ が条件を満たす組の数（abc206_e）、周期 $d$ の文字列の数を「$d$ の約数の周期」で引いて重複を除く（abc304_f）、完全累乗の個数を指数ごとに重複を除いて数える（abc361_f）
- **なぜ正しいか**：「すべて $g$ の倍数」の集合は、gcd が $g, 2g, 3g, \dots$ のものに排反に分かれる
- **つまずき**：大きい順に処理するのを忘れる。上限 $N$ までの倍数を回すループが $O(N\log N)$ になる理由（$\sum N/g$）
- **図**：数直線上に $g$ の倍数を並べ、$F(g)$ から倍数側の $f$ を引いていく様子
- **確認問題**：「$1 \le x,y \le 6$ で $\gcd(x,y)=1$ の組の数を、この方法で求めよ」
- **問題のサイン**：「gcd の総和」「gcd が $1$ になる組」「互いに素」「周期」「$\sum_{i,j}\gcd(\cdot)$」
- **関係**：メビウス関数を使えば $f(g)=\sum_k\mu(k)F(gk)$ と1本の式で書ける（mobius-function）。結果は同じで、競プロでは約数包除の書き方で十分なことが多い

#### mobius-function メビウス関数とメビウス反転

- **何ができるか**：$\mu(n)$（平方因子を持てば 0、異なる素因数が $r$ 個なら $(-1)^r$）を使い、$F(n)=\sum_{d\mid n}f(d)$ から $f(n)=\sum_{d\mid n}\mu(n/d)F(d)$ を戻す。「互いに素」を $[\gcd=1]=\sum_{d\mid\gcd}\mu(d)$ に置き換えて和の順序を交換する
- **典型**：互いに素な組の数 $\sum_d \mu(d)\lfloor N/d\rfloor^2$、$\mathrm{lcm}$ の総和（agc038_c）、gcd が条件に入る順列・組の数（abc230_g）、周期的な文字列（abc304_f は約数包除でもメビウスでも解ける）
- **なぜ正しいか**：$\sum_{d\mid n}\mu(d)=[n=1]$。これは $n$ の異なる素因数についての包除原理そのもの
- **つまずき**：$\mu$ の篩（線形篩・エラトステネス）で作る手間。$\lfloor N/d\rfloor$ が同じ値の区間をまとめる高速化（商の列挙、06）
- **確認問題**：「$\mu(12)$ と $\mu(30)$ は」「$\sum_{d\mid n}\mu(d)=[n=1]$ を $n=12$ で確かめよ」
- **問題のサイン**：「互いに素」「$\gcd(i,j)=1$ となる組」「$\sum\gcd$、$\sum\mathrm{lcm}$」
- **境界**：素因数分解・篩・乗法的関数・商の列挙は 06。07 は「包除としての意味」と反転の使い方を扱う

#### zeta-mobius-subset 高速ゼータ変換・メビウス変換（部分集合）

- **何ができるか**：$\hat f(S)=\sum_{T\subseteq S}f(T)$（下位集合の和）を全 $S$ について $O(n2^n)$ で求める（素朴には $O(3^n)$）。逆変換（メビウス変換）で戻せる。上位集合の和も同様。OR 畳み込み $h(S)=\sum_{A\cup B=S}f(A)g(B)$ は「両方をゼータ変換 → 各点の積 → メビウス変換」、AND 畳み込みは上位集合の版で
- **典型**：$i \mid j \subseteq K$ となる組の最大値（和の代わりに上位2つを持つ、arc100_c Or Plus Max）、部分集合ごとの量を全部分集合について集計する（abc213_g の補助、abc295_h など）
- **なぜ正しいか**：$n$ 次元の $\{0,1\}^n$ 上の累積和を、1 軸ずつ取る（2 次元累積和を $n$ 次元にしたもの）
- **つまずき**：ループの順（bit を外側、集合を内側）を逆にすると誤り。メビウス変換は引き算で同じ順に回す。$n=20$ で $2^{20}\cdot20\approx 2\times10^7$
- **図**：$n=3$ の立方体の頂点に値を置き、軸ごとに累積していくステップ送り
- **確認問題**：「$n=2$ で $\hat f$ を手で計算し、1 軸ずつの累積和と一致することを確かめよ」
- **問題のサイン**：「$N \le 20$ で部分集合（bit）ごとの和・最大」「$A_i \mathbin{|} A_j$」「$x \subseteq S$ となる $x$ についての和」
- **境界**：XOR 畳み込み（アダマール変換、abc212_h・abc367_g）は 06 の畳み込みと同じ枠組みなので 06 に置き、ここから参照するのがよい。部分集合畳み込み・集合冪級数は発展

#### zeta-mobius-divisor 約数・倍数のゼータ変換・メビウス変換

- **何ができるか**：$F(n)=\sum_{n \mid m}f(m)$（倍数の和）や $\sum_{d \mid n}f(d)$（約数の和）を、素数 $p$ ごとに「$p$ の方向の累積和」を取ることで $O(N\log\log N)$ で求める。逆変換も同様。GCD 畳み込み $h(g)=\sum_{\gcd(i,j)=g}f(i)g(j)$ は倍数のゼータ → 積 → メビウス、LCM 畳み込みは約数の版で
- **典型**：各 $d$ について「$d$ の倍数である $A_i$ の個数」を倍数を回して集める（abc393_e。素朴な倍数ループで $O(N\log N)$）、約数ゼータ変換とその逆（約数メビウス変換）を使う（abc474_f）、$\mathrm{lcm}$ の総和（agc038_c）
- **参考**：noshi91「高速ゼータ変換の約数版 O(N log(log(N)))」
- **なぜ正しいか**：$n$ を素因数の指数ベクトルと見ると「約数」は各成分が小さいことなので、部分集合のゼータ変換と同じく素数（軸）ごとの累積和になる
- **つまずき**：素数ごとに「倍数の和」は $i$ を大きい順、「約数の和」は小さい順に回すなど、向きの取り違え
- **問題のサイン**：「gcd ごと・lcm ごとの集計」「$\sum_{i,j} f(\gcd(A_i,A_j))$」
- **境界**：GCD/LCM 畳み込みは 06 の畳み込みとの境界。07 では約数包除の高速版として扱い、畳み込みとしての一般論は 06 から参照するのがよい

### 4.4 道具：特殊な数・構造の数え上げ

#### reflection-principle 鏡像法

- **何ができるか**：「途中で境界を越える経路」を、最初に越えた点以降を折り返すことで「別の終点への経路（すべて）」と1対1に対応させて数える。越えない経路 = 全経路 − 越える経路
- **典型**：黒 $N$ 個・白 $M$ 個の並べ方で「どの接頭辞でも白の数 ≤ 黒の数 + $K$」を満たすもの $=\binom{N+M}{N}-\binom{N+M}{M+K+1}$（abc205_e）。上下の両端を越えない移動を鏡像法で多項式の係数に落とす発展例（abc309_h）
- **なぜ正しいか**：境界 $y=x+K+1$ に初めて触れた後の部分を折り返すと終点が対称な点に移り、逆の操作で戻せる（全単射）
- **つまずき**：折り返す線は「越えたら違反になる線」（$+1$ ずれ）。条件がそもそも満たせない場合（$N > M+K$ など）の 0
- **図**：格子路と境界線を描き、最初に触れた点以降を折り返す動く図
- **確認問題**：「$(0,0)\to(3,3)$ で $y \le x$ を保つ経路の数を、鏡像法で求めよ」
- **問題のサイン**：「どの接頭辞でも A の個数 ≥ B の個数」「途中で負にならない」「括弧列」

#### catalan-number カタラン数

- **何ができるか**：$C_n=\frac{1}{n+1}\binom{2n}{n}=\binom{2n}{n}-\binom{2n}{n+1}$。正しい括弧列、対角線を越えない単調路、$n+1$ 葉の二分木、凸多角形の三角形分割などの個数。漸化式 $C_{n+1}=\sum_i C_iC_{n-i}$（最初の括弧が閉じる位置で分類）
- **典型**：ABC では鏡像法の一般化として出る（abc205_e）。括弧列の個数を数える問題は DP（開き括弧の数を状態に持つ）で解く方が多い（02 との境界）
- **つまずき**：$\binom{2n}{n}/(n+1)$ を mod で計算するときは $(n+1)$ の逆元を掛ける
- **確認問題**：「長さ 6 の正しい括弧列を全部書き、5 個あることを確かめよ」
- **ページ案**：鏡像法とまとめて1ページ（「鏡像法とカタラン数」）にするのがよい

#### stirling-second 第2種スターリング数と全射

- **何ができるか**：$S(n,k)$ = $n$ 個の区別できる玉を区別しない $k$ 個の空でないグループに分ける方法。全射の数 $k!\,S(n,k)=\sum_{i=0}^{k}(-1)^i\binom{k}{i}(k-i)^n$（包除）。漸化式 $S(n,k)=S(n-1,k-1)+kS(n-1,k)$（最後の玉が1人で新しい組を作るか、既存の $k$ 組のどれかに入るか）
- **典型**：各色を少なくとも1回使う塗り方（全射の包除）。ABC では包除の形で現れることが多い（すべての行・列を使う配置を数える abc242_f は同じ形）。グループ分けの条件付き版は全探索や DP（abc310_d）
- **つまずき**：箱を区別しないときに $k!$ で割ってよいのは「どの箱も空でない」ときだけ
- **確認問題**：「$S(4,2)$ を、漸化式と包除の両方で求めよ」
- **問題のサイン**：「$N$ 人を $K$ 個のグループに分ける（区別なし、空なし）」「すべての色を使う」

#### bell-number ベル数と集合の分割の列挙

- **何ができるか**：$B_n=\sum_k S(n,k)$ = $n$ 個の集合の分割の総数。$B_{n+1}=\sum_k\binom{n}{k}B_k$。$B_{10}=115975$、$B_{12}=4213597$ なので、$n \le 12$ 程度なら分割を全列挙できる
- **典型**：$N \le 12$ 個をグループに分けて各グループの和の XOR を全列挙（abc390_d。$B_{12}=4213597$ 通りなので間に合う）、グループ分けを重複なく全列挙する（abc310_d。「まだ使っていない最小番号の要素」を新しいグループに入れるか既存のグループに入れるかで分岐）
- **つまずき**：重複して列挙しない書き方（各要素を「既存のグループ」か「新しいグループ」に入れる。グループの番号を区別すると $k!$ 倍に重複する）。計算量を $B_n$ で見積もること
- **図**：要素を1つずつ「既存の組に入れる／新しい組を作る」で分岐する木（制限付き成長列）
- **確認問題**：「$\{1,2,3\}$ の分割をすべて書け（5 個）」「$N=12$ の分割の全列挙は間に合うか」
- **問題のサイン**：「$N \le 10$〜$12$ でグループに分ける全通り」

#### partition-number 分割数と整数の分割の列挙

- **何ができるか**：$p(n)$ = $n$ を正整数の和で表す方法（順序を区別しない）。$p(n,k)$（$k$ 個以下の部分）は $p(n,k)=p(n,k-1)+p(n-k,k)$ で $O(nk)$。$p(n)$ は五角数定理で $O(n\sqrt n)$（発展）。$p(50)=204226$、$p(100)\approx1.9\times10^8$ なので、$n \le 50$〜$60$ 程度なら分割を全列挙できる
- **典型**：置換の巡回型（巡回の長さの多重集合 = $N$ の分割）を全列挙し、各巡回型の置換の数を数える（abc226_f）。重複を許す数の多重集合で和が決まったものを数える DP（abc221_h）
- **つまずき**：列挙の重複（部分を降順に並べた形だけを作る）。分割の個数の見積もり
- **確認問題**：「$p(5)$ をすべて書き出せ（7 個）」
- **問題のサイン**：「和が $N$ になる多重集合」「区別のない玉を区別のない箱へ」「$N \le 50$ で巡回の長さの組合せ」

#### stirling-first 第1種スターリング数

- **何ができるか**：$c(n,k)$（符号なし）= ちょうど $k$ 個の巡回からなる $n$ 次の置換の数。漸化式 $c(n,k)=c(n-1,k-1)+(n-1)c(n-1,k)$（$n$ を新しい巡回にするか、既存のどこかの後ろに入れるか）。上昇階乗 $x(x+1)\cdots(x+n-1)=\sum_k c(n,k)x^k$
- **典型**：左から見て最大値を更新する位置（見える建物）の個数ごとの順列の数（abc385_g。FPS で上昇階乗を展開）、置換を巡回で数える問題（abc247_h など）
- **つまずき**：第2種と漸化式の係数（$k$ と $n-1$）を取り違える
- **レベル**：ABC では G・Ex（発展）。概要ページで足りる

#### permutation-cycles 置換の巡回分解に基づく数え上げ

- **何ができるか**：置換を巡回に分け、巡回型（長さ $\ell$ の巡回が $m_\ell$ 個）ごとの置換の数 $\frac{N!}{\prod_\ell \ell^{m_\ell}m_\ell!}$ で数える。置換を $K$ 回繰り返して元に戻る最小回数は巡回の長さの $\mathrm{lcm}$
- **典型**：巡回型を分割として全列挙し、$\mathrm{lcm}^K$ の総和を求める（abc226_f）
- **なぜ正しいか**：$N!$ 通りの並べ方を巡回の書き方の重複（各巡回の始点 $\ell$ 通り、同じ長さの巡回の順番 $m_\ell!$ 通り）で割る
- **つまずき**：巡回の始点の重複で割るのを忘れる
- **境界**：Functional graph（03）・置換の操作（01）と接する。07 では「巡回型ごとの数え上げ」に絞る

#### burnside-lemma Burnside の補題（発展）

- **何ができるか**：回転・反転などで同一視したときの「本質的に異なるもの」の数 $=\frac{1}{|G|}\sum_{g\in G}|\mathrm{Fix}(g)|$（各操作で動かないものの数の平均）。$n$ 個の玉の数珠を $k$ 色で塗る方法（回転のみ）$=\frac{1}{n}\sum_{d\mid n}\varphi(d)k^{n/d}$
- **典型**：立方体の面への書き込み方（abc198_f。回転 24 通りそれぞれで固定される書き込み方を数えて平均する）。回転で同一視するネックレスを「最短周期ごとに数えて周期で割る」方法で数える例（abc428_g。約数包除と同じ形で、Burnside を使わずに済む）
- **なぜ正しいか**：(対象, それを動かさない操作) の組を2通りに数える。各対象の軌道の大きさと安定化群の大きさの積が $|G|$
- **つまずき**：割る前の重複度が対象ごとに違うので、単純に $|G|$ で割ってはいけない（counting-dedup）
- **確認問題**：「4 個の玉の数珠を 2 色で塗る方法（回転で同一視）を、全列挙と Burnside で求めよ」
- **ページ案**：発展の概要ページ

#### cayley-pruefer ラベル付き木の数と Prüfer 列

- **何ができるか**：頂点にラベルのある $n$ 頂点の木は $n^{n-2}$ 個（Cayley）。木と長さ $n-2$ の Prüfer 列が1対1に対応し、頂点 $i$ は列にちょうど $\deg(i)-1$ 回現れる。よって次数列 $d$ を指定した木の数は $\frac{(n-2)!}{\prod(d_i-1)!}$
- **典型**：次数列ごとの木の数を使って直径の総和を数える（abc290_f）、次数が集合 $S$ に入る木の数（abc303_h。FPS の累乗、06 との境界）
- **つまずき**：「次数 − 1」回であること。$n=1, 2$ の端
- **図**：葉を最小番号から1つずつ取り除きながら Prüfer 列を作るステップ送り
- **確認問題**：「4 頂点のラベル付き木は何個か。頂点 1 の次数が 3 のものは」
- **ページ案**：黄〜発展。「Cayley と Prüfer」で1ページ（概要寄り）

#### matrix-tree-theorem 行列木定理（発展）

- **何ができるか**：無向グラフの全域木の数 = ラプラシアン行列（次数行列 − 隣接行列）から1行1列を除いた行列の行列式。重み付き・有向版もある
- **典型**：頂点集合ごとの全域木の数を行列木定理で求めて、集合の DP（森の数え上げ）と組み合わせる（abc253_h）。有向のオイラー閉路を数える BEST 定理と組み合わせる（abc336_g）
- **境界**：行列式の計算（$O(n^3)$ の掃き出し、mod 素数）は 06。07 では「何を数えられるか」と行列の作り方だけを書く

#### lgv-lemma LGV 補題（発展）

- **何ができるか**：DAG 上で始点 $a_1..a_k$ から終点 $b_1..b_k$ への「互いに交わらない経路の組」の数（符号付き）を、$M_{ij}$ = $a_i$ から $b_j$ への経路数とした行列 $M$ の行列式で求める
- **典型**：$K$ 人のロボットが交わらずに動く確率（abc216_h。bitDP で行列式を展開）
- **ページ案**：発展の概要ページ（行列木定理と並べて「行列式で数える」）

#### young-tableaux Young 図形とフック長公式（発展）

- **何ができるか**：整数の分割を左詰めの箱の図（Young 図形）で表し、1..N を行・列とも増加するように書き込んだもの（標準タブロー）の数をフック長公式 $N!/\prod(\text{各箱のフック長})$ で数える。順列と「同じ形の標準タブローの組」を1対1に対応させる Robinson–Schensted 対応により、最長増加部分列・最長減少部分列の長さの条件を Young 図形の形の条件に言い換えられる
- **典型**：LIS・LDS の長さの条件を満たす順列の数（abc378_g）
- **ページ案**：発展の概要ページ。分割数（partition-number）から参照する

#### counting-labeled-graphs 連結なグラフ・構造の数え上げ

- **何ができるか**：「連結なもの」を「全体 − 非連結なもの」で数える。非連結なものは「頂点 1 を含む連結成分」で分類して、成分のサイズや頂点集合ごとに DP する（部分集合 DP、$O(3^n)$）
- **典型**：辺の部分集合で頂点 1 と頂点 $k$ が連結になる数（abc213_g）、最大の成分サイズが $L$ のグラフ（abc180_f。「$L$ 以下」の差を取る）、BFS の層ごとに頂点を配って距離条件を満たすグラフを数える（abc281_g）
- **つまずき**：「頂点 1 を含む成分」で分類しないと成分の順序で重複する（counting-dedup の代表元の考え）
- **境界**：DP の状態設計は 02、グラフの性質は 03

#### binomial-prefix-sum 二項係数の部分和（発展）

- **何ができるか**：$S(n,K)=\sum_{k\le K}\binom{n}{k}$ を、$S(n+1,K)=2S(n,K)-\binom{n}{K}$、$S(n,K+1)=S(n,K)+\binom{n}{K+1}$ で $(n,K)$ を1ずつ動かしながら更新する（Mo のような移動）
- **典型**：上限つきの配り方を包除で数えるときに部分和が大量に必要になる（abc235_g）

#### generating-function-counting 母関数の考え方（数え上げの視点）

- **何ができるか**：「選び方の数」を多項式の係数として表し、積で「独立な選択の組合せ」、累乗で「同じ選択の繰り返し」を表す。例：各値を 0〜$c$ 個使う → $(1+x+\cdots+x^c)$、重複組合せ → $(1-x)^{-k}$ の係数
- **典型**：Prüfer 列と組み合わせて次数の制約を FPS の累乗にする（abc303_h）、上昇階乗の展開（abc385_g）、各桁の上限つきの和を $(1-x^{10})^{M-1}/(1-x)^M$ の係数として二項係数と負の二項係数で求める（abc449_g）
- **境界**：FPS の演算（NTT・逆元・log・exp）は 06。07 では「数え上げを多項式の係数に言い換える」考え方だけを、二項定理・重複組合せとのつながりで扱う。黄より上の G・Ex でしか本格的には要らない

### 4.5 確率・期待値

#### probability-basics 確率の基本

- **何ができるか**：有限個の同様に確からしい根元事象なら「確率 = 条件を満たす場合の数 / 全体の場合の数」。独立な事象の積、排反な事象の和、余事象 $1-P$、条件付き確率 $P(A\mid B)=P(A\cap B)/P(B)$、全確率の公式 $P(A)=\sum_i P(B_i)P(A\mid B_i)$（期待値 DP の漸化式の根拠）
- **典型**：最初の出目で場合分けし、各場合でコインが続けて表になる確率を足す（abc126_c）、残りのカードを数えて勝つ確率を求める（abc193_d）
- **つまずき**：「同様に確からしい」でないものを場合の数の比で計算する（例：2個のサイコロの目の和）。独立でない事象の確率を掛ける。浮動小数点の誤差と出力桁数（$10^{-6}$ などの許容誤差の読み方）
- **確認問題**：「サイコロを2回振り、和が 7 になる確率は。1回目が 3 だと分かっているときは」
- **問題のサイン**：「確率を求めよ（絶対誤差または相対誤差が $10^{-6}$ 以下なら正解）」
- **ページ案**：基礎の短いページ。期待値の定義もここで扱う

#### rational-mod 確率・期待値を mod 998244353 で答える（有理数の mod 表現）

- **何ができるか**：答えが既約分数 $P/Q$ のとき、$R \equiv P\cdot Q^{-1} \pmod{998244353}$ を出力させる形式の意味を理解し、途中の計算をすべて mod の世界で行う
- **なぜ正しいか**：$Q$ が 998244353 の倍数でなければ $Q$ の逆元がただ1つ存在し、$a/b$ を $a\cdot b^{-1}$ に置き換えても足し算・引き算・掛け算・割り算の関係はすべて保たれる（写像が環の準同型になる）。だから実数での計算の手順をそのまま mod で行ってよい。問題文の「$Q$ は 998244353 で割り切れないことが証明できる」はこのための保証
- **つまずき**：
  - mod の値では大小比較ができない。「確率が最大になる選択」「期待値の小さい方を選ぶ」のような判断は mod の値ではできないので、比較が必要なら実数で行うか、比較が要らない式にする（optimal-strategy-expectation では double を使う問題が多い）
  - 確率 $p\%$ は $p\cdot 100^{-1}$ として mod に入れる（abc280_e）
  - 分母が途中で 0（mod の倍数）になる式変形（$1-p$ で割るとき $p \equiv 1$ になりうるか）に注意
  - 検算：mod の出力を分数に戻すには、小さい分母 $q$ を全探索して $R\cdot q \bmod p$ が小さい値になるものを探す（有理数復元）
- **確認問題**：「$1/2$ を mod 998244353 で表すといくつか（499122177）。$1/2 + 1/2$ が 1 に戻ることを確かめよ」「mod で答える期待値 DP で max を取ってよいか」
- **問題のサイン**：「期待値（確率）を mod 998244353 で出力せよ」「求める値は有理数で表せ、…」
- **境界**：逆元の求め方（Fermat・拡張ユークリッド）は 06。07 では「なぜ有理数を mod で表してよいか」と「何ができて何ができないか」を扱う

#### linearity-of-expectation 期待値の線形性

- **何ができるか**：$E[X+Y]=E[X]+E[Y]$、$E[cX]=cE[X]$。$X$ と $Y$ が独立でなくても成り立つ。複雑な量を単純な量の和に分け、それぞれの期待値を足す
- **典型**：各サイコロの期待値 $(1+p)/2$ の和を区間ごとに求める（abc154_d）、青と赤のサイコロの和の期待値（アルゴ×数学 3.4）、区間の値をその区間の平均で上書きする操作を期待値の線形性で置き換える（abc417_f。期待値どうしが線形に変わるので、期待値の配列に遅延セグ木で同じ操作をすればよい）、操作のたびに値が線形に混ざる過程を期待値の行列累乗で追う（abc199_f）
- **なぜ正しいか**：$E[X+Y]=\sum_\omega P(\omega)(X(\omega)+Y(\omega))$ を2つの和に分けるだけ。独立性は使っていない（独立性が要るのは積 $E[XY]=E[X]E[Y]$ のとき）
- **つまずき**：積・二乗・max・min には線形性が使えない（$E[X^2]\ne E[X]^2$、$E[\max]\ne\max E$）。「期待値どうしの積」を答えにしてしまう
- **図**：確率変数を表（行 = 起こりうる場合、列 = 部分の量）で書き、行ごとの和の平均 = 列ごとの平均の和、を示す図
- **確認問題**：「サイコロを 100 回振ったとき、1 の目が出る回数の期待値は。前の回と同じ目が出る回数の期待値は（隣どうしは独立でないのに足してよいか）」
- **問題のサイン**：「〜の個数の期待値」「〜の総和の期待値」
- **ページ案**：指示確率変数（indicator-variables）と同じページにまとめてよい（線形性の最大の使い道が指示確率変数のため）

#### indicator-variables 指示確率変数（個数の期待値を確率の和にする）

- **何ができるか**：「条件を満たすものの個数」の期待値を、各候補 $i$ について $X_i=[\text{$i$ が条件を満たす}]$ とおき、$E[\sum X_i]=\sum P(\text{$i$ が条件を満たす})$ で求める
- **典型**：転倒数の期待値を各ペアが転倒する確率の和にする（典型90 066、abc380_g）、最小部分木に含まれる白い頂点の個数の期待値を頂点ごとの確率の和にする（abc149_f）、操作の回数の期待値を「頂点 $i$ が操作で選ばれる確率 $=1/(\text{$i$ に到達できる頂点数})$」の和にする（agc049_a）、ランダムに $K$ 個選んだときの色の種類数の期待値を色ごとに「その色が1つ以上含まれる確率」の和にする（abc215_g）
- **なぜ正しいか**：個数 = 指示変数の和、という恒等式に線形性を使うだけ。$E[X_i]=P(\text{条件})$
- **つまずき**：「ちょうど1回数える」設計（同じものを2つの $i$ で数えない）。ペアの確率を求めるときに対称性（probability-symmetry）を使うと簡単になることが多い
- **図**：各候補の上に「条件を満たす確率」を書き、それを足すと期待値になる図
- **確認問題**：「ランダムな順列の固定点（$p_i=i$）の個数の期待値は（$n$ によらず 1）」「ランダムな順列の転倒数の期待値は（$n(n-1)/4$）」
- **問題のサイン**：「〜の個数の期待値」「〜の種類数の期待値」「連結成分の個数の期待値」
- **関係**：数え上げの寄与（counting-contribution）と同じ構造（総和 = 期待値 × 総数）

#### expectation-tail-sum 期待値と確率の変換（$E[X]=\sum P(X\ge k)$）

- **何ができるか**：非負整数値の確率変数 $X$ について $E[X]=\sum_{k\ge1}P(X\ge k)$。最大値・最小値・$k$ 番目の値の期待値を「$\max \ge k$ の確率（= 1 − すべて $< k$ の確率）」の和で求める
- **典型**：ソートして $K$ 番目の値の期待値を $\sum_x P(\text{$K$ 番目} \ge x)$ と二項係数で（abc295_e）、ペアができるまで取り出す回数の期待値（abc352_g）、成功までの回数（arc085_a の別解）
- **なぜ正しいか**：$X=\sum_{k\ge1}[X\ge k]$（$X$ 以下の正整数の個数）に線形性を使う
- **つまずき**：$k$ の範囲（0 からでなく 1 から）。連続値なら積分 $E[X]=\int_0^\infty P(X>t)\,dt$（continuous-probability）
- **図**：$P(X\ge k)$ の棒グラフを横に積むと面積が期待値になる図
- **確認問題**：「サイコロを 2 回振った最大値の期待値を、$P(\max\ge k)$ の和で求めよ」
- **問題のサイン**：「最大値（最小値・$K$ 番目）の期待値」「〜になるまでの回数の期待値」

#### expectation-of-square 二乗の期待値・分散

- **何ができるか**：$E[X^2]$ は線形性で直接は求まらないので、(1) $X=\sum X_i$ と分けて $X^2=\sum_i\sum_j X_iX_j$ とし、ペアごとの $E[X_iX_j]$ を足す、または (2) DP で「確率」「期待値×確率」「二乗の期待値×確率」を同時に運ぶ（$(x+1)^2=x^2+2x+1$ を使って更新）。分散は $V[X]=E[X^2]-E[X]^2$
- **典型**：レベルの二乗の期待値を、確率・期待値・二乗和の3つの量を一緒に遷移させて求める（abc277_g）、二乗の期待値を「全操作についての $x^2$ の総和 / 操作の数」として数える（abc450_g）。平均が決まっているとき分散の最小化は二乗和の最小化と同じ（$V=E[X^2]-E[X]^2$）
- **なぜ正しいか**：(1) は二乗の展開と線形性。(2) は $E[(X+c)^2]=E[X^2]+2cE[X]+c^2$ なので、$E[X^2]$ の更新に $E[X]$ が必要になり、両方を運べば閉じる
- **つまずき**：$E[X]^2$ と $E[X^2]$ の混同。$i=j$ の項（$X_i^2=X_i$）を忘れる
- **確認問題**：「コインを $n$ 回投げた表の回数 $X$ の $E[X^2]$ を、ペアに分ける方法で求めよ」
- **問題のサイン**：「〜の二乗の期待値」「分散」「スコアの二乗」

#### conditional-expectation 条件付き期待値と全期待値の公式

- **何ができるか**：$E[X]=\sum_i P(B_i)E[X\mid B_i]$（最初の一手で場合分けする）。期待値 DP の漸化式「$E[\text{状態}]=\text{コスト}+\sum P(\text{遷移})E[\text{遷移先}]$」はこの公式そのもの
- **ページ案**：独立ページにせず、期待値 DP のページの「なぜこの漸化式でよいか」の節で扱う

#### expected-value-dp 期待値 DP の数学的側面（後ろ向きに考える理由）

- **何ができるか**：「終了までの回数（コスト）の期待値」を、状態 $s$ からの残りの期待値 $E[s]$ として定義し、終状態 $E=0$ から後ろ向きに埋める。$E[s]=c(s)+\sum_t P(s\to t)E[t]$
- **典型**：硬貨を取り出していずれかが 100 枚になるまでの回数（abc184_d）、HP が 0 以下になるまでの攻撃回数（abc280_e）、寿司がなくなるまでの回数（dp_j。「寿司が 1 個・2 個・3 個の皿の数」を状態にする）、サイコロで給料が決まる過程を後ろから（abc326_e）、パックを開ける回数（abc382_e。1 パックのレアの枚数の分布は前向きの確率 DP で求める）、DAG 上でゴールまでの回数（abc144_f）
- **なぜ後ろ向きか**：「ここから先にかかる量」は未来の状態だけで決まり、どうやってここに来たかによらない（マルコフ性）。前向きに「ここまでにかかった量の期待値」を持つと、到達確率で重み付けした和を別に持つ必要があり、終了時刻がばらばらなので扱いにくい。後ろ向きなら終状態が 0 という境界条件から1本の漸化式で済む
- **確率 DP との違い**：前向きの確率 DP（probability-dp）は「状態に到達する確率」を配る。期待値は「到達確率 × その遷移のコスト」の総和としても求められ、どちらでも書ける問題が多い。終了条件が「ある状態に達したら終わり」なら後ろ向き、時刻が固定（$K$ 回後）なら前向きが自然
- **つまずき**：状態に自分自身への遷移がある（自己ループ、self-loop-expectation）と、そのままでは埋められない。遷移確率の和が 1 になっているかの検算
- **図**：状態の DAG に、終状態から $E$ を埋めていくステップ送り
- **確認問題**：「コインを表が2回連続で出るまで投げる回数の期待値を、状態『直前が表か』で式に立てよ（6）」
- **問題のサイン**：「〜になるまでの回数の期待値」「操作を終えるまでに〜する回数の期待値」
- **境界**：状態設計・高速化は 02。07 は「式の立て方（全期待値の公式）・後ろ向きの理由・自己ループの処理」に絞る。ページは 07 に置き、02 の DP の章から参照するのがよい（「期待値 DP が解けない」原因の多くが数学側にあるため）

#### self-loop-expectation 自己ループの除去（方程式を移項して解く）

- **何ができるか**：$E[s]=c+pE[s]+\sum_{t\ne s}P(s\to t)E[t]$ のように自分自身が右辺に出るとき、移項して $E[s]=\frac{c+\sum_{t\ne s}P(s\to t)E[t]}{1-p}$ とする
- **典型**：1 の目は状態を変えない（自己ループ）のでサイコロの目を掛けていく確率を移項して求める（abc300_e）、サイコロに 0 の目がありその場にとどまるすごろく（abc263_e）、0 の目があるルーレットの費用（abc314_e。0 以外の目が出る確率で割る）、1 の目で $N$ が変わらないうえに 2 つの操作の小さい方を選ぶ（abc350_e）
- **なぜ正しいか**：$E[s]$ は有限の値（$p<1$ なら有限回で抜ける）なので、方程式の解として一意に決まる。幾何分布の和を展開した結果と一致する
- **つまずき**：$p=1$（抜けられない）のときに 0 で割る。最適戦略で「自己ループする選択肢」を含む min/max を取るときは、移項してから比較する
- **確認問題**：「確率 $p$ で成功する試行を成功まで繰り返す回数の期待値を、$E=1+(1-p)E$ から求めよ」
- **問題のサイン**：「出た目が〜なら振り直し」「確率 $p$ で何も起きない」

#### expectation-linear-equations 未知数を残す・連立方程式で解く

- **何ができるか**：遷移にサイクル（スタートへ戻る・円環状に回る）があり、後ろ向きに埋められないとき、(1) 戻る先の期待値を未知数 $X$ とおき、各状態の期待値を $a+bX$ の形で持って最後に $X=a+bX$ を解く（abc189_f：振り出しに戻るマスがあるすごろく、abc224_g）、(2) 円環状の依存は1か所を未知数にして一周させる（abc333_f）、(3) 一般の状態数 $n$ が小さいなら連立一次方程式をガウスの消去法で解く（吸収マルコフ連鎖、発展）
- **典型**：2人が交互に引くロシアンルーレット型で、無限に続く場合の和を等比級数か方程式で閉じる（arc174_c）
- **なぜ正しいか**：期待値の漸化式は線形なので、未知数を1つ残しても各状態の値は未知数の1次式のまま伝わる
- **つまずき**：(1) で $b=1$（どこからでも必ず戻る）なら解がない（期待値が無限大）。最適戦略が絡むと $\min$ のせいで1次式にならないので、$X$ の値を二分探索して「仮定した $X$ と計算結果の大小」を比べる（optimal-strategy-expectation）
- **境界**：ガウスの消去法（mod・実数）は 06。吸収マルコフ連鎖の基本行列 $(I-Q)^{-1}$ は発展の概要で
- **問題のサイン**：「振り出しに戻る」「円形に並んだ人が順に」「無限に続く可能性がある」

#### geometric-distribution 幾何分布（成功まで繰り返す回数）

- **何ができるか**：成功確率 $p$ の独立な試行を成功するまで繰り返す回数の期待値は $1/p$
- **典型**：確率 $1/2^M$ で全部正解するまで提出し直す総時間（arc085_a）、未訪問の頂点へ移る確率が $(N-k)/N$ の段階が続く（abc194_d）
- **なぜ正しいか**：$E=1+(1-p)E$（1回目で成功しなければ最初からと同じ状況）を解く。あるいは $\sum_{k\ge1}P(X\ge k)=\sum(1-p)^{k-1}=1/p$
- **つまずき**：「失敗の回数」と「試行の回数」の違い（$1/p-1$ と $1/p$）
- **確認問題**：「サイコロで 6 が出るまで振る回数の期待値は。6 が出るまでに 6 以外が出る回数の期待値は」
- **問題のサイン**：「成功するまで繰り返す」「〜が出るまで」

#### coupon-collector コンプリートガチャ型

- **何ができるか**：$N$ 種類が等確率で出るとき、全種類そろうまでの回数の期待値 $N\left(\frac11+\frac12+\cdots+\frac1N\right)=N H_N$。「すでに $k$ 種類持っている」段階ごとに幾何分布（成功確率 $(N-k)/N$）の期待値 $N/(N-k)$ を足す
- **典型**：全種類のコインを集める（アルゴ×数学 3.4 の Coin Gacha）、グラフの全頂点を訪れるまで（abc194_d）。確率が等しくない場合や「一部だけそろえる」場合は min-max 包除（$E[\max]=\sum_{S\neq\emptyset}(-1)^{|S|+1}E[\min S]$）が要る（abc242_h・abc331_g、発展）
- **つまずき**：段階ごとに分けずに一度に計算しようとする。確率が等しくないときに $NH_N$ を使う
- **確認問題**：「サイコロの目を 6 種類すべて出すまでの回数の期待値は（14.7）」
- **問題のサイン**：「すべての種類を集めるまで」「全頂点を訪れるまで」

#### probability-symmetry 対称性で確率を求める

- **何ができるか**：区別のない対象の入れ替えで問題が変わらないとき、各対象の確率は等しい。「残りから一様に選んでいく」過程は「最初に一様ランダムな順列を決めて先頭から取る」と同じ
- **典型**：ボールの位置を入れ替える操作の後、黒玉が位置 1 にいる確率と、それ以外の位置にいる確率（どれも等しい）の2つだけを追う（abc360_e）、ランダムに選んだ区間をシャッフルした後の転倒数の期待値（区間内のペアは確率 1/2 で転倒、abc380_g）、prefix の関係がない2つの文字列の大小は確率 1/2（abc268_g）、ランダムな順で開ける過程を順列に置き換える（abc464_f、abc473_g）
- **なぜ正しいか**：確率空間の全単射（ラベルの入れ替え）が確率を保つので、入れ替えで移り合う事象は同じ確率を持つ
- **つまずき**：対称でない要素（初期位置・特別な要素）を見落とす。対称性で「2状態」に縮めた後の遷移確率の計算
- **図**：$N$ 個の位置のうち特別な1つと「その他すべて（同じ確率）」の2つに縮める図
- **確認問題**：「52 枚のトランプをよく切ったとき、上から 10 枚目がスペードである確率は」「ランダムな順列で $p_1>p_2$ となる確率は」
- **問題のサイン**：「一様ランダムにシャッフル」「ランダムに入れ替える」「ランダムな順列」

#### optimal-strategy-expectation 最適戦略の期待値（続けるか止めるか）

- **何ができるか**：プレイヤーが選択できる確率過程で、期待値を最大（最小）にする戦略のもとでの期待値を求める。状態ごとに「選択は max（min）、偶然は平均」を交互に取る（expectimax）
- **典型**：サイコロを振り直すかやめるかを後ろから決める（abc266_e：$E_k=\frac16\sum\max(\text{目},E_{k-1})$）、取り出した靴下のどちらを残すかを決めながら期待値を求める（abc412_f）、出た目のどれを残すかを max、振るのを平均でメモ化再帰（abc421_e）、どの道を消すかを全部試して期待値を比べる（abc144_f）、ブラックジャック型で止める点を選ぶ（abc342_f）、神経衰弱の最適行動（abc470_e）
- **自己参照があるとき**：最初からやり直す選択肢があると、答え $X$ 自身が式に入る。$X$ を仮定して計算した値が $X$ より大きいか小さいかで二分探索する（abc224_g のように未知数を置いて解ける場合もある）
- **つまずき**：mod で答える問題では比較できない（rational-mod）。比較は double で行い、同じ戦略で mod の値を計算し直す問題もある。「期待値が最大になる戦略」と「最大値の期待値」の取り違え
- **確認問題**：「サイコロを最大2回振れ、止めた時の目が得点のとき、1 回目にいくつ以上なら止めるべきか（4 以上、期待値 4.25）」
- **問題のサイン**：「最適に行動したときの期待値」「好きなタイミングでやめられる」「やり直せる」

#### probability-dp 確率 DP（前向きに確率を配る）

- **何ができるか**：$dp[t][s]$ = 時刻 $t$ に状態 $s$ にいる確率、を前向きに配る。$K$ 回後の分布、ある時刻に特定の状態にいる確率など
- **典型**：すごろくで $K$ 回以内にゴールに着く確率（abc275_e、mod）、2 人のサイコロのどちらが先にゴールするか（abc298_e）、時刻 $X+0.5$ に曲 1 が流れている確率（abc323_e）、$N$ 枚のコインで表が過半数の確率（dp_i）
- **使い分け**：時刻が決まっている・分布が要る → 前向きの確率 DP、終わるまでの量の期待値 → 後ろ向きの期待値 DP。期待値は「到達確率 × 各遷移のコスト」の和でも書けるので、前向きでも求められる
- **境界**：DP の側面は 02。07 は確率の積と和の使い分け（独立な遷移の積、排反な経路の和）だけを扱い、02 から参照される形がよい

#### counting-vs-expectation 総和と期待値の行き来

- **何ができるか**：全体が $M$ 通りの一様な選び方なら「期待値 = 総和 / $M$」「総和 = 期待値 × $M$」。数え上げの寄与（counting-contribution）と期待値の線形性（indicator-variables）は同じ計算の別の表現
- **典型**：期待値を「全パターンの得点の和 / $K^2$」として数え上げる（abc276_f）、長方形の大きさの期待値を「全配置についての和 / 総数」（abc297_f）、黒マスを1つ消したときの連結成分数の期待値を「各マスを消したときの和 / マス数」（abc334_g）、全操作の $x^2$ の総和 / 操作の総数（abc450_g）
- **つまずき**：一様でない確率（重み付き）では単純な割り算にならない
- **ページ案**：期待値の線形性のページの節で足りる

#### continuous-probability 連続値の確率（発展）

- **何ができるか**：$[0,1]$ の一様乱数などの連続確率変数。確率は長さ・面積の比、期待値は積分。$E[X]=\int_0^\infty P(X>t)dt$。$N$ 個の一様乱数の $K$ 番目の期待値 $K/(N+1)$
- **典型**：一様乱数の $K$ 番目の最大値の期待値を積分と多項式で（abc226_h）、ランダムな点から最も近い点を選ぶ確率を角度の比で（agc021_b）
- **ページ案**：発展の概要ページ。ABC では G・Ex のみ

#### random-walk ランダムウォーク

- **何ができるか**：1 次元のランダムウォークで $N$ 歩後の位置の分布は二項係数（$k$ 回右に動く確率 $\binom{N}{k}/2^N$）。2 次元は「軸ごとに何回動くか」を二項係数で分けて独立にする
- **典型**：上下左右の移動を「横に動く回数」で分け、各軸の到達確率の積を足す（abc011_4）、$N$ 歩後の位置と目標の距離の期待値を二項係数の和で（abc463_g）、確率と期待値の遷移が一定のランダムウォークを行列累乗で（abc271_g・abc277_g）
- **境界**：行列累乗は 06
- **ページ案**：格子路（lattice-paths）や期待値 DP の節で足りる

### 4.6 ゲーム

#### game-basics ゲームの基本（必勝・必敗）

- **何ができるか**：二人零和有限確定完全情報ゲーム（偶然がなく、情報がすべて見え、有限手で終わり、引き分けがない）では、各局面は「手番の人が必ず勝てる（必勝）」か「必ず負ける（必敗）」のどちらかに決まる。終局（動けない局面）から後ろ向きに「負け局面へ1手で移れるなら勝ち、どこへ移っても勝ち局面なら負け」で決める
- **なぜ正しいか**：有限で終わるので、局面の遷移は DAG になり、終局から順に（トポロジカル順の逆に）値が確定する（Zermelo の定理の競プロ版）
- **つまずき**：「相手も最適に動く」の意味（相手は自分にとって最悪の手を選ぶ）。終局の勝ち負けの定義（動けなくなった方が負けか勝ちか）を問題文から正確に読む
- **図**：局面の DAG で、終局から W/L を塗っていくステップ送り
- **確認問題**：「石が $N$ 個、1〜3 個取れる、最後の石を取った方が勝ち。先手が負けるのは $N$ がどんなときか（4 の倍数）」
- **問題のサイン**：「先手と後手が交互に」「両者が最適に行動したとき、勝つのはどちらか」「First / Second を出力」
- **ページ案**：game-winning-losing-dp と1ページにまとめる

#### game-winning-losing-dp 必勝・必敗の判定（ゲーム DP）

- **何ができるか**：局面を状態とする DP（メモ化再帰）で必勝・必敗を求める。状態数が小さければ全局面を探索する
- **典型**：取れる石の数が決まっている石取り（dp_k、tessoku A32）、カードを2枚ずつ取り除く局面を残りカードの集合で持つ bitDP（abc354_e）、しりとりで使った単語の集合と最後の単語を状態にする bitDP（abc278_f）、後ろから mod 7 の余りごとに勝敗を決める（abc195_e）、カードの所在（3 か所）を $3^N$ 通りの状態にする（abc380_f）
- **つまずき**：状態にサイクルがあるとメモ化再帰が止まらない（→ game-retrograde-analysis）。手番を状態に入れ忘れる（両者の手が非対称なとき）
- **確認問題**：「メモ化再帰で、自分の手で移れる局面のどれか1つが『相手の負け』なら自分の勝ち、と書く理由を説明せよ」
- **問題のサイン**：「$N \le 16$〜$18$ で状態が集合」「状態数が小さい」
- **境界**：DP の実装の側面（bitDP、メモ化）は 02。07 では必勝・必敗の定義と「なぜ後ろから決まるか」を扱う。ページは 07 に置き、02 から参照するのがよい

#### minimax ミニマックス（得点差を最大化するゲーム）

- **何ができるか**：両者が「自分の得点 − 相手の得点」を最大化するとき、$f(\text{局面})$ = 手番の人が以後に得られる「自分 − 相手」の最大値とすると、$f=\max_{\text{手}}(\text{その手の得点}-f(\text{次の局面}))$ と1本の式で書ける（手番を入れ替えるたびに符号を反転、negamax）
- **典型**：両端から取るゲームの得点差（dp_l、区間 DP）、ピラミッドを上から交互に進む（tessoku A35）、グリッドを右か下に進みながら得点を取り合う（abc201_d）、三目並べで重みつきの得点（abc349_e）、袋を取り合う区間 DP（abc303_g）、木を降りていき中央値を最大化・最小化する（abc218_g）、3×3 のマスを埋める得点（abc025_c）
- **なぜ正しいか**：零和なので「自分の得 = 相手の損」。相手も同じ式で最適に動くと仮定すれば、後ろから値が確定する
- **つまずき**：手番によって max と min を使い分ける書き方（符号反転で1つにまとめると楽）。「自分の得点の最大化」と「得点差の最大化」の取り違え（得点の総和が一定なら同じ）
- **確認問題**：「両端から取るゲームで、貪欲（大きい方を取る）が最適でない例を作れ」
- **問題のサイン**：「両者が最適に行動したときの得点（の差）」「太郎は X − Y を最大化、次郎は最小化」

#### game-retrograde-analysis サイクルのあるゲーム（後退解析）

- **何ができるか**：局面の遷移にサイクルがあり、引き分け（永遠に続く）がありうるとき、終局から逆向きに勝敗を確定させる。各局面の「まだ負けと確定していない行き先の数」を数え、0 になったら負け確定、負け局面へ移れるなら勝ち確定。最後まで確定しない局面が引き分け
- **典型**：しりとりの単語をグラフの辺にして勝敗と引き分けを求める（abc209_e）、得点のあるゲームを確定済みの局面からダイクストラのように確定させる（abc261_h）
- **なぜ正しいか**：負けが確定するのは「すべての行き先が勝ち確定」のときだけ、勝ちが確定するのは「負け確定の行き先がある」とき。BFS で逆辺をたどり、確定した局面だけを使って次を確定させるので、サイクルがあっても矛盾しない
- **つまずき**：メモ化再帰で書くとサイクルで無限ループになる。逆辺のグラフを作ること、出次数を数えておくこと
- **図**：サイクルのあるグラフで、終局から勝ち・負けが伝わり、サイクルの部分だけ引き分けとして残るステップ送り
- **確認問題**：「A→B、B→A、B→C（C は終局）のとき、各局面の勝敗は」
- **問題のサイン**：「無限に続く場合は Draw」「同じ局面が繰り返されうる」「グラフ上でコマを動かす」
- **境界**：グラフの BFS は 03。cp-algorithms の "Games on arbitrary graphs" と同じ内容

#### nim Nim と XOR

- **何ができるか**：いくつかの山から、1 つの山を選んで 1 個以上取る。最後の石を取った方が勝ち。全山の個数の XOR が 0 なら後手必勝、0 でなければ先手必勝
- **なぜ正しいか**（Bouton の定理）：XOR が 0 の局面からはどう取っても XOR が 0 でなくなる（1 つの山だけが変わるため）。XOR が 0 でない局面からは、XOR の最上位ビットが立っている山を選んで XOR を 0 にできる。終局（全部 0）は XOR 0 なので、「XOR 0 = 必敗」が帰納的に成り立つ
- **典型**：そのまま Nim（tessoku A33）、最初の 2 山の間で石を移して後手必勝にできるか（abc172_f。XOR と AND を桁ごとに決める）、1 回に取れる上限 $k$ を選んで後手必勝にする（arc168_b。上限 $k$ の Nim の Grundy 数は $A \bmod (k+1)$）
- **つまずき**：逆形（最後に取った方が負け）では結論が変わる（misere-nim）
- **確認問題**：「山が 3, 4, 5 のとき、先手は何をどれだけ取ればよいか」
- **問題のサイン**：「山から石を取る」「最後に取った人が勝ち」「XOR」

#### grundy-number Grundy 数と Sprague–Grundy の定理

- **何ができるか**：不偏ゲーム（両者の手の選択肢が同じ）の各局面に Grundy 数 $g=\mathrm{mex}\{g(\text{次の局面})\}$ を割り当てる。$g=0$ ⇔ 必敗。独立なゲームの和（どれか1つを選んで1手進める）の Grundy 数は各ゲームの Grundy 数の XOR
- **なぜ正しいか**：Grundy 数 $g$ の局面は「大きさ $g$ の Nim の山」と同じに振る舞う（$g$ 未満のすべての値へ移れ、$g$ へは移れない。$g$ より大きい値へ移っても相手がすぐ戻せる）。よって和は Nim と同じく XOR で判定できる
- **典型**：割る操作の Grundy 数を「素因数の個数（重複込み）」で決める（abc368_f）、2 種類の石の山の Grundy 数を DP で表にして XOR（典型90 031）、取れる個数に下限と上限がある Nim（abc297_g）、区間を選ぶと重なる区間が消えるゲームで区間ごとの Grundy 数を区間 DP で（abc206_f）、Grundy 数そのもの（tessoku A34）
- **つまずき**：mex の計算（集合に含まれない最小の非負整数）。Grundy 数の上限を見積もって配列の大きさを決める。和にならない（1 手で複数の山を動かす）ゲームには使えない
- **図**：小さい局面から Grundy 数を mex で埋める表のステップ送り
- **確認問題**：「1〜3 個取れる石取りの Grundy 数の列を求めよ（$n \bmod 4$）」「Grundy 数が 0 でない局面から 0 の局面へ必ず移れるのはなぜか」
- **問題のサイン**：「複数の山（盤面）があり、どれか1つを選んで操作」「先手と後手の取れる手が同じ」
- **レベル判定**：abc368_f（diff 1180）は Grundy 数を知っていれば素直だが、Grundy 数が必須の問題がまとまるのは abc297_g（1834）・典型90 031（★6、1600〜1999 相当）・abc206_f（2221）・abc278_g（2533）・abc255_g（2734）と青以上。よって青とし、abc368_f を易しい入口の例題にする

#### grundy-patterns Grundy 数の規則を見つける

- **何ができるか**：状態が大きくて Grundy 数を全部計算できないとき、小さい状態の表を作って周期性や式を見つける（実験）
- **典型**：$L$ 以上 $R$ 以下を取る Nim の Grundy 数 $\lfloor (x \bmod (L+R))/L\rfloor$（abc297_g）、特定の局面で特定の個数を取れない Nim で、例外の局面だけ別に扱って Grundy 数を圧縮して求める（abc255_g）、$2^k-1$ だけが負け局面になる石取り（『アルゴリズム×数学』5.2 節の節末問題）
- **つまずき**：周期が始まる前の部分（前周期）を見落とす。実験の範囲が狭すぎる
- **ページ案**：Grundy 数のページの節（実験の方法は counting-experiment と共通）

#### game-mirror-strategy 真似戦略・対称戦略

- **何ができるか**：盤面を対称な2つに分けられるとき、後手（または先手が最初の一手で対称にしてから）は相手の手を対称な位置で真似し続けることで負けない。ペアリング戦略（盤面を2つずつの組に分け、相手が組の片方を取ったらもう片方を取る）も同じ発想
- **典型**：同じ枚数の袋が偶数個ずつあれば後手が相手の手を真似できる（arc105_d）、先手と後手で取れる個数が違うゲームで、相手が崩した状態を必ず元に戻せる側が勝つ（arc143_c）、木に完全マッチングがあれば後手が相手の塗った頂点の相方を塗る（agc014_d）、連続するカードの列を真ん中で分けて対称にしてから真似する（abc278_g の kmjp の解説が触れている）
- **つまずき**：真似した手が常に合法かを確かめる（中央の要素の扱い）
- **確認問題**：「円形に並んだ $N$ 枚のコインから隣り合う 1〜2 枚を取るゲームで、$N \ge 3$ なら後手必勝なのはなぜか」
- **問題のサイン**：「盤面が対称」「後手が勝つことを示せ」

#### game-parity-invariant 偶奇・不変量で決まるゲーム

- **何ができるか**：ゲームの総手数の偶奇が戦略によらず決まるなら、勝敗はその偶奇だけで決まる。手数を変えられる要素（変えられる回数の上限）を見つける
- **典型**：最終的に完全二部グラフになり、追加できる辺の総数の偶奇で先手・後手が決まる（abc398_e、インタラクティブ）、端以外の文字を消していくゲームで最後の形が両端の文字で決まり、手数の偶奇で勝敗が決まる（arc064_b）、木のコイン取りが直径の長さ mod 3 で決まる（agc033_c）
- **境界**：偶奇・不変量の一般論は 01（考察）。07 ではゲームでの使い方の節にする

#### misere-nim 逆形 Nim（最後に取った方が負け）

- **何ができるか**：すべての山が 1 以下なら、1 の山の個数が偶数のとき先手必勝（通常と逆）。2 以上の山が1つでもあれば通常の Nim と同じ判定（XOR が 0 でなければ先手必勝）
- **なぜ正しいか**：2 以上の山が1つになった時点で、勝つ側はその山を 0 か 1 にして「1 の山の個数の偶奇」を自分に有利に調整できる
- **レベル**：ABC での出題は見つからなかった（OI Wiki・cp-algorithms で扱われる）。Nim のページの節で触れる程度でよい

#### partizan-games 非不偏ゲーム（発展）

- **何ができるか**：両者の取れる手が違うゲームでは Grundy 数は使えない。局面に「数（超現実数）」を割り当て、和が正なら左の勝ち、などで判定する（組合せゲーム理論）
- **典型**：左右で動き方の違う駒のゲーム（abc229_h、abc265_h）
- **ページ案**：発展の概要ページ。ABC の Ex/G でまれ

#### nim-variants Nim の変種

- **何ができるか**：取れる個数に上限・範囲がある Nim（Bachet。Grundy 数は周期的）、階段 Nim（奇数段だけの Nim に帰着）、Moore's Nim-$k$（$k$ 個まで同時に取れる）、Wythoff（2 山から同数取れる。負け局面が黄金比で決まる）、ある山を別の山へ移す変形
- **典型**：上限つき Nim（arc168_b）、範囲つき Nim（abc297_g）、取れない手が指定された Nim（abc255_g）、先手と後手で取れる個数が違う変形（arc143_c。Grundy 数は使えず、$X+Y$ で割った余りと戻す戦略で考える）
- **ページ案**：Nim と Grundy 数のページの節。ABC で出たのは範囲つき・集合つきの Nim

#### interactive-games インタラクティブ形式のゲーム

- **何ができるか**：ジャッジと実際に対戦し、毎手を出力する。必勝側を選んで宣言し、必勝戦略を実際に実行する必要がある
- **典型**：$1..2N+1$ の整数を交互に言うゲームで、まだ言われていない数を答える（abc244_c）、木に辺を追加していくゲームで、偶奇で手番を選び、二部グラフの条件を保つ辺を追加する（abc398_e）、Grundy 数の XOR を 0 にする手を毎回探す（abc278_g）
- **つまずき**：出力のフラッシュ、必勝の判定だけでなく「必勝手を見つける処理」が要ること（Grundy 数の XOR を 0 にする手を全探索するなど）
- **境界**：インタラクティブ形式そのもの（入出力・フラッシュ）は 08。07 では「必勝戦略を構成する」側に絞る

#### nim-counting ゲームの局面を数える（発展）

- **何ができるか**：「先手必勝になる初期配置の数」を、Nim の XOR が 0 でない配置の数として数える。XOR 畳み込み（アダマール変換）で山の個数ごとに数える（abc212_h）
- **境界**：XOR 畳み込みは 06

## 5. 例題・練習問題の候補

重複を除いて 177 問（difficulty の昇順）。「使う手法」は topics.yaml の key（複数の項目で使う問題は複数並べた）。「何を問う問題か」は最初に載せた項目での要約。裏付けはすべて第三者の解説記事（作者の GitHub を含む）で、atcoder.jp の URL は含まない。各項目での役割（例題・練習）は topics.yaml を見る。

| 問題ID | タイトル | difficulty | 使う手法 | 何を問う問題か | 裏付け |
| --- | --- | --- | --- | --- | --- |
| agc001_e | E. BBQ Hard | なし | lattice-paths | 多数の二項係数の和を、グリッド上の経路数として DP で一括計算する | https://drken1215.hatenablog.com/entry/2019/05/18/152000 |
| dp_i | I. Coins | なし | probability-dp | N 枚のコインを投げて表が過半数になる確率を、表の枚数ごとの確率を配って求める | https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000 |
| dp_j | J. Sushi | なし | conditional-expectation, expected-value-dp | 寿司が残っている皿の数ごとの状態で、次の 1 回で場合分けして期待値の式を立てる | https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000 |
| dp_k | K. Stones | なし | game-basics | 取れる個数の集合が決まった石取りの勝敗を、石の数ごとの DP で求める | https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000 |
| dp_l | L. Deque | なし | minimax | 両端から取るゲームの得点差を、区間ごとの「手番の人の得点 − 相手の得点」の区間 DP で求める | https://drken1215.hatenablog.com/entry/2023/07/22/031100 |
| dp_y | Y. Grid 2 | なし | lattice-paths, inclusion-exclusion-dp | 障害物をソートし「最初に踏む障害物」で分類する DP で、どの障害物も踏まない経路を数える | https://drken1215.hatenablog.com/entry/2019/01/16/000100 |
| math_and_algorithm_w | 023. Dice Expectation | なし | linearity-of-expectation | 2 つのサイコロの出目の和の期待値を、それぞれの期待値の和で求める | https://github.com/E869120/math-algorithm-book/blob/main/codes/cpp/Code_3_04_1.cpp |
| math_and_algorithm_z | 026. Coin Gacha | なし | coupon-collector | N 種類のコインがそろうまでの回数の期待値 N(1+1/2+…+1/N) を求める | https://github.com/E869120/math-algorithm-book/blob/main/editorial/chap3-4/prob3-4-4.cpp |
| tessoku_book_ad | A30. Combination | なし | binomial-precompute | nCr を 10^9+7 で割った余りを、階乗とフェルマーの小定理による逆元で求める（鉄則 A30） | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A30.cpp |
| tessoku_book_af | A32. Game 1 | なし | game-basics | A 個か B 個取れる石取りの勝敗を、石の数ごとの勝ち負けの DP で求める（鉄則 A32） | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A32.cpp |
| tessoku_book_ag | A33. Game 2 | なし | nim | 山の個数の XOR が 0 かどうかで勝敗を判定する（鉄則 A33） | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A33.cpp |
| tessoku_book_ah | A34. Game 3 | なし | grundy-number | X 個か Y 個取れる石取りの Grundy 数を mex で求め、全山の XOR で判定する（鉄則 A34） | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A34.cpp |
| tessoku_book_ai | A35. Game 4 | なし | minimax | ピラミッドを交互に下る駒の最終値を、段ごとに max と min を交互に取る DP で求める（鉄則 A35） | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A35.cpp |
| typical90_ae | 031. VS AtCoder（★6） | なし | grundy-number | 白石と青石の 2 種類がある山の Grundy 数を DP で表にして XOR を取る | https://github.com/E869120/kyopro_educational_90/blob/main/sol/031.cpp |
| typical90_bn | 066. Various Arrays（★5） | なし | indicator-variables | 値を一様に選んだ数列の転倒数の期待値を、各ペアが転倒する確率の和で求める | https://github.com/E869120/kyopro_educational_90/blob/main/editorial/066.jpg |
| typical90_bq | 069. Colorful Blocks 2（★3） | なし | counting-basics | 距離 2 以内が異なる色になる一列の塗り方を積の法則で求める（K(K−1)(K−2)^(N−2)） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/069.cpp |
| typical90_o | 015. Don't be too close（★6） | なし | stars-and-bars | 差が k 以上の数だけを選ぶ方法を、選ぶ個数ごとの二項係数で数える（全 k で調和級数の計算量） | https://github.com/E869120/kyopro_educational_90/blob/main/sol/015.cpp |
| abc244_c | C. Yamanote Line Game | 165 | interactive-games | 1〜2N+1 を交互に言うゲームで、まだ言われていない数を答え続ける | https://drken1215.hatenablog.com/entry/2025/02/08/111105 |
| abc185_c | C. Duodecim Ferra | 374 | counting-mindset, stars-and-bars | 長さ L の棒を正の長さの 12 本に切る方法を、11 か所の切れ目の選び方に言い換えて数える | https://drken1215.hatenablog.com/entry/2020/12/14/015500 |
| abc186_d | D. Sum of difference | 436 | counting-contribution | すべての 2 数の差の絶対値の総和を、ソート後の各要素に付く係数で求める | https://drken1215.hatenablog.com/entry/2020/12/19/231000 |
| abc154_d | D. Dice in Line | 485 | linearity-of-expectation | 各サイコロの期待値 (1+p)/2 を足して、連続 K 個の和の期待値の最大値を求める | https://drken1215.hatenablog.com/entry/2020/02/10/235800 |
| abc131_c | C. Anti-Division | 518 | inclusion-exclusion | C の倍数でも D の倍数でもない数の個数を、lcm を使った 2 条件の包除で数える | https://drken1215.hatenablog.com/entry/2019/06/22/224100 |
| abc126_c | C. Dice and Coin | 638 | probability-basics | 最初の出目で場合分けし、各場合でコインが続けて表になる確率を足す | https://drken1215.hatenablog.com/entry/2019/05/19/224500_2 |
| abc178_c | C. Ubiquity | 653 | counting-complement | 0 と 9 を両方含む長さ N の数字列を、全体から 0 を含まない・9 を含まない場合を引いて（重なりを足し戻して）数える | https://drken1215.hatenablog.com/entry/2020/10/09/162600 |
| arc085_a | C. HSI | 752 | geometric-distribution | 確率 1/2^M で全部通るまで提出し直す総時間の期待値を、1/p で求める | https://drken1215.hatenablog.com/entry/2019/03/23/175300 |
| abc162_d | D. RGB Triplets | 757 | counting-complement | 色がすべて異なる 3 つ組の数から、添字が等間隔になっているものを引く | https://drken1215.hatenablog.com/entry/2020/04/12/225900 |
| abc193_d | D. Poker | 866 | probability-basics | 残りのカードの枚数から、2 枚の組合せごとに勝つ確率を数える | https://drken1215.hatenablog.com/entry/2021/03/02/190700 |
| arc095_b | D. Binomial Coefficients | 867 | binomial-coefficient | nCr が最大になる n と r の組を選ぶ（n は最大、r は n/2 に最も近いもの） | https://blog.hamayanhamayan.com/entry/2018/04/15/164633 |
| abc178_d | D. Redistribution | 875 | stars-and-bars | 3 以上の整数の和で S を表す数列の数を、各項から 2 を引いて正の整数解の数にする（または DP） | https://drken1215.hatenablog.com/entry/2020/10/11/211000 |
| abc202_d | D. aab aba baa | 966 | kth-combination | a を A 個・b を B 個並べた文字列の辞書順 K 番目を、先頭から残りの並べ方の数と K を比べて決める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0522_abc202#d_-_aab_aba_baa |
| abc145_d | D. Knight | 1009 | counting-bijection, lattice-paths | 2 種類のナイト移動で目的のマスに着く方法を、各移動の回数を連立方程式で決めてから並べ方の二項係数で数える | https://drken1215.hatenablog.com/entry/2020/04/26/180000 |
| abc156_d | D. Bouquet | 1014 | counting-complement, binomial-variants | n 本の花から作る花束のうち禁止された 2 つの本数を全体 2^n−1 から引く（n は巨大） | https://drken1215.hatenablog.com/entry/2020/04/22/013400 |
| abc194_d | D. Journey | 1078 | geometric-distribution, coupon-collector | 未訪問の頂点へ移る確率が (N−k)/N の段階ごとに 1/p を足す | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0306_abc194#d_-_journey |
| abc132_d | D. Blue and Red Balls | 1167 | binomial-precompute | K 個の青玉を i 個のかたまりに分けて赤玉の間に置く方法を、i ごとに二項係数の積で数える | https://drken1215.hatenablog.com/entry/2019/06/30/183400 |
| abc368_f | F. Dividing Game | 1180 | grundy-number | 真の約数に置き換える操作の Grundy 数が素因数の個数（重複込み）になることを使って XOR で判定する | https://programming-hiroba.com/abc368-f/ |
| abc334_e | E. Christmas Color Grid 1 | 1195 | linearity-of-expectation | ランダムな赤マスを緑にしたときの連結成分数の期待値を、各マスについての値の平均で求める | https://programming-hiroba.com/abc334-e/ |
| abc354_e | E. Remove Pairs | 1223 | game-winning-losing-dp | 残りのカードの集合を状態にした bitDP で、取り除けるペアがあるかを見て勝敗を決める | https://drken1215.hatenablog.com/entry/2024/05/19/011051 |
| abc266_e | E. Throwing the Die | 1227 | optimal-strategy-expectation | 残り k 回振れるときの期待値を、出目と「続けた場合の期待値」の大きい方の平均で後ろから求める | https://kazun-kyopro.hatenablog.com/entry/ABC/266/E |
| abc398_e | E. Tree Game | 1238 | counting-experiment, game-parity-invariant, interactive-games | 木に辺を加えていくゲームの勝敗を、小さいケースの実験で辺の総数の偶奇に帰着させる（インタラクティブ） | https://kmjp.hatenablog.jp/entry/2025/03/25/0930 |
| abc307_e | E. Distinct Adjacent | 1240 | counting-basics | 円環に並んだ N 人に、隣どうしが異なる 0〜M−1 の整数を割り当てる方法を数える | https://drken1215.hatenablog.com/entry/2024/06/10/024932 |
| abc360_e | E. Random Swaps of Balls | 1249 | probability-symmetry | 黒玉が左端にある確率と、それ以外のどの位置にも等しい確率の 2 つだけを追う | https://programming-hiroba.com/abc360-e/ |
| abc280_e | E. Critical Hit | 1251 | rational-mod, expected-value-dp | 確率 P% の会心の一撃があるときの攻撃回数の期待値を、P/100 を mod に入れて DP で求める | https://drken1215.hatenablog.com/entry/2022/12/07/113800 |
| abc393_e | E. GCD of Subset | 1253 | zeta-mobius-divisor | 各 d について A の中の d の倍数の個数を倍数を回して集め、各 A_i の約数で条件を満たす最大のものを求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0215_abc393#e_-_gcd_of_subset |
| abc275_e | E. Sugoroku 4 | 1264 | probability-dp | 跳ね返りのあるすごろくで K 回以内にゴールする確率を、マスごとの確率を配って求める | https://programming-hiroba.com/abc275-e/ |
| abc184_d | D. increment of coins | 1276 | expected-value-dp | いずれかの硬貨が 100 枚になるまでの操作回数の期待値を、残りの期待値で後ろから求める | https://drken1215.hatenablog.com/entry/2020/11/23/010500 |
| abc323_e | E. Playlist | 1279 | rational-mod | ランダムに曲を流し続けたとき、時刻 X+0.5 に曲 1 が流れている確率を mod で求める | https://drken1215.hatenablog.com/entry/2023/10/14/113816 |
| arc168_b | B. Arbitrary Nim | 1289 | nim, nim-variants | 1 回に取れる上限 k を決める Nim で、Grundy 数 A mod (k+1) を使って後手必勝になる最大の k を求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/1119_arc168#b_-_arbitrary_nim |
| abc270_d | D. Stones | 1300 | game-winning-losing-dp | 石の数ごとに手番の人が取れる最大の石の数を DP で求める | https://drken1215.hatenablog.com/entry/2023/07/22/020725 |
| abc298_e | E. Unfair Sugoroku | 1300 | probability-dp | 2 人のサイコロでどちらが先にゴールするかの確率を、両者の位置を状態に求める | https://programming-hiroba.com/abc298-e/ |
| abc201_d | D. Game in Momotetsu World | 1317 | minimax | グリッドを右か下に進みながら得点を取り合う差を、後ろからの DP で求める | https://drken1215.hatenablog.com/entry/2023/07/21/235300 |
| abc151_e | E. Max-Min Sums | 1344 | counting-fix-order | ソートして各要素が最大・最小になる選び方の数を二項係数で数え、全 K 個組の max−min の総和を求める | https://drken1215.hatenablog.com/entry/2020/01/12/224100 |
| abc300_e | E. Dice Product 3 | 1354 | rational-mod, self-loop-expectation | サイコロの目を掛けていき N ちょうどになる確率を、mod の分数のまま DP する | https://drken1215.hatenablog.com/entry/2023/05/03/212600 |
| abc326_e | E. Revenge of "The Salary of AtCoder Inc." | 1363 | rational-mod | サイコロで給料が決まる過程の期待値を、後ろから mod で計算する | https://programming-hiroba.com/abc326-e/ |
| abc310_d | D. Peaceful Teams | 1368 | counting-dedup, twelvefold-way, stirling-second, bell-number | 仲の悪い組を避けて N 人を T 組に分ける方法を、まだ組に入っていない最小番号の人から組を決めて重複なく数える | https://drken1215.hatenablog.com/entry/2023/07/17/213800 |
| abc350_e | E. Toward 0 | 1385 | self-loop-expectation | 1 の目で N が変わらない自己ループを移項し、2 つの操作の期待値の小さい方を取るメモ化再帰 | https://programming-hiroba.com/abc350-e/ |
| abc417_f | F. Random Gathering | 1414 | linearity-of-expectation | 区間を平均で上書きする操作を期待値の線形性で置き換え、遅延セグ木で期待値を更新する | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0802_abc417#f_-_random_gathering |
| abc167_e | E. Colorful Blocks | 1442 | counting-mindset, binomial-precompute | 隣り合う同色の組が K 個以下になる塗り方を、組の数 k ごとに二項係数と累乗の積で数えて足す | https://kmjp.hatenablog.jp/entry/2020/05/10/0900 |
| abc278_f | F. Shiritori | 1452 | game-winning-losing-dp | 使った単語の集合と最後の単語を状態にした bitDP でしりとりの勝敗を決める | https://programming-hiroba.com/abc278-f/ |
| abc349_e | E. Weighted Tic-Tac-Toe | 1464 | minimax | 重み付き三目並べの勝敗を、盤面の全状態のメモ化探索で求める | https://programming-hiroba.com/abc349-e/ |
| abc133_e | E. Virus Tree 2 | 1505 | counting-mindset, counting-fix-order | 木の頂点を距離 2 以内が異なる色になるように塗る方法を、BFS 順に決めて積の法則で数える | https://drken1215.hatenablog.com/entry/2019/07/08/002700 |
| abc156_e | E. Roaming | 1514 | counting-mindset, binomial-precompute | k 回の移動後にありうる各部屋の人数の組を、空き部屋の数で場合分けして重複組合せで数える | https://kmjp.hatenablog.jp/entry/2020/02/23/0900 |
| abc276_f | F. Double Chance | 1562 | counting-vs-expectation | 2 回引いた値の最大値の期待値を、全 K^2 通りの最大値の和を数えて割る | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/1105_abc276#f_-_double_chance |
| abc234_f | F. Reordering | 1596 | multinomial-coefficient | 部分列を並べ替えてできる文字列の数を、文字ごとの個数を DP で決めながら二項係数を掛けて数える | https://kazun-kyopro.hatenablog.com/entry/ABC/234/F |
| abc361_f | F. x = a^b | 1606 | divisor-inclusion-exclusion | N 以下の完全累乗の個数を、指数ごとの重複を除いて数える | https://drken1215.hatenablog.com/entry/2024/07/07/020716 |
| abc390_d | D. Stone XOR | 1607 | twelvefold-way, bell-number | 玉を区別し箱を区別しない・個数自由のマス（ベル数）を全列挙する | https://yuulis.hatenablog.com/entry/ABC-390-D |
| abc195_e | E. Lucky 7 Battle | 1609 | game-winning-losing-dp | 後ろから「余りが j のとき勝てるか」を、手番の人に応じて or と and で埋める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0313_abc195#e_-_lucky_7_battle |
| abc304_f | F. Shift Table | 1619 | divisor-inclusion-exclusion | 周期 d の文字列の数を、d の約数の周期で重複して数えた分を引いて求める | https://drken1215.hatenablog.com/entry/2023/06/07/153403 |
| abc025_c | C. 双子と○×ゲーム | 1640 | minimax | 3×3 のマスを交互に埋めたときの得点を、残りのマスの状態ごとのミニマックス探索で求める | https://drken1215.hatenablog.com/entry/2023/07/22/192817 |
| abc057_d | D. Maximum Average Sets | 1658 | binomial-coefficient | 平均の最大値と、それを実現する選び方の数を二項係数で数える | https://drken1215.hatenablog.com/entry/2019/02/16/000900 |
| abc263_e | E. Sugoroku 3 | 1659 | self-loop-expectation | 0 の目でその場にとどまるすごろくの期待値を、移項と累積和で後ろから求める | https://kazun-kyopro.hatenablog.com/entry/ABC/263/E |
| abc162_e | E. Sum of gcd of Tuples (Hard) | 1662 | divisor-inclusion-exclusion | 長さ N の列の gcd の総和を、gcd がちょうど g の個数を大きい g から求めて計算する | https://kmjp.hatenablog.jp/entry/2020/04/12/1000 |
| abc382_e | E. Expansion Packs | 1671 | expected-value-dp | 1 パックのレアの枚数の分布を確率 DP で求め、必要枚数に達するまでのパック数の期待値を後ろから求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1130_abc382#e_-_expansion_packs |
| abc246_f | F. typewriter | 1677 | inclusion-exclusion | 選んだ文字列の文字だけで作れる文字列の数を、選ぶ集合ごとの共通の文字で包除する | https://drken1215.hatenablog.com/entry/2022/04/03/212800 |
| abc110_d | D. Factorization | 1695 | counting-bijection, stars-and-bars | 積が M になる長さ N の数列を、素因数ごとに指数を N 個へ配る重複組合せの積に言い換える | https://drken1215.hatenablog.com/entry/2018/09/23/224100 |
| abc021_d | D. 多重ループ | 1704 | stars-and-bars, twelvefold-way | 1 ≤ a1 ≤ … ≤ ak ≤ n の個数 C(n+k−1, k) を求める（多重ループの回数） | https://qiita.com/drken/items/f2ea4b58b0d21621bd51 |
| arc174_c | C. Catastrophic Roulette | 1706 | expectation-linear-equations | 2 人が交互に回すルーレットで各人の支払いの期待値を、無限に続く分を等比級数・方程式で閉じて求める | https://drken1215.hatenablog.com/entry/2024/03/17/233040 |
| arc077_b | D. 11 | 1715 | counting-dedup | 1 つの値だけが 2 回現れる数列の、長さ k の異なる部分列の数を、重複して数えた分を引いて求める | https://kmjp.hatenablog.jp/entry/2017/07/02/0900 |
| abc262_e | E. Red and Blue Graph | 1719 | binomial-identities | 端点の色が異なる辺の数の偶奇を「赤い頂点の次数の和」の偶奇に言い換え、奇数次数の頂点を偶数個選ぶ方法の和で数える | https://kazun-kyopro.hatenablog.com/entry/ABC/262/E |
| abc314_e | E. Roulettes | 1722 | self-loop-expectation | 0 の目があるルーレットの費用を、0 以外が出る確率で割って自己ループを消しつつ最小の期待値を選ぶ | https://qiita.com/DeltaStruct/items/08a55509095a471c5371 |
| abc206_e | E. Divide Both | 1745 | divisor-inclusion-exclusion | gcd(x,y) が条件を満たす組の数を、gcd ごとの個数を倍数から引いて求める | https://drken1215.hatenablog.com/entry/2021/06/25/121800 |
| agc033_c | C. Removing Coins | 1758 | game-parity-invariant | 木のコイン取りの勝敗が直径の長さを 3 で割った余りで決まることを示す | https://drken1215.hatenablog.com/entry/2019/05/07/005700 |
| arc117_c | C. Tricolor Pyramid | 1768 | lucas-theorem | 3 色の三角形の最後の色を、係数が二項係数になることと mod 3 の Lucas の定理で求める | https://drken1215.hatenablog.com/entry/2021/06/12/001400 |
| abc380_f | F. Exchange Game | 1769 | game-winning-losing-dp | 各カードの所在（3 か所）を状態にした 3^N 状態のメモ化再帰で勝敗を決める | https://drken1215.hatenablog.com/entry/2024/11/17/132223 |
| abc333_f | F. Bomb Game 2 | 1770 | expectation-linear-equations | 先頭が確率 1/2 で消えるか末尾へ回る過程の確率を、円環状の依存を 1 つの未知数で閉じて解く | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/1216_abc333#f_-_bomb_game_2 |
| abc154_f | F. Many Many Paths | 1775 | binomial-identities | 長方形領域の各点への格子路の数の総和を、縦の和の公式で閉じた式にする | https://drken1215.hatenablog.com/entry/2020/02/09/225000 |
| abc171_f | F. Strivore | 1795 | counting-dedup | 文字列 S を部分列として含む長さ N+K の文字列を、最も左で一致させる埋め込みで一意にして数える | https://drken1215.hatenablog.com/entry/2020/06/27/125500 |
| arc143_c | C. Piles of Pebbles | 1805 | nim-variants, game-mirror-strategy | 先手は X 個、後手は Y 個ずつ取る非対称なゲームを、X+Y で割った余りと「相手の手を戻す」戦略で判定する | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0626_arc143#c_-_piles_of_pebbles |
| arc064_b | D. An Ordinary Game | 1814 | game-parity-invariant | 端以外を消すゲームの最終形が両端の文字で決まることから、手数の偶奇で勝敗を決める | https://drken1215.hatenablog.com/entry/2019/02/02/181600 |
| abc297_g | G. Constrained Nim 2 | 1834 | counting-experiment, grundy-number, grundy-patterns, nim-variants | 取れる個数に下限と上限がある Nim の Grundy 数の式を、表を作って見つける | https://kmjp.hatenablog.jp/entry/2023/04/19/1000 |
| abc011_4 | D. 大ジャンプ | 1843 | random-walk | 上下左右のランダムな移動を横に動く回数で分け、各軸の到達確率を二項係数で求めて掛ける | https://drken1215.hatenablog.com/entry/2020/11/14/084800 |
| abc150_e | E. Change a Little Bit | 1851 | counting-contribution | 異なる 2 つの 0/1 列のすべての組の最小コストの総和を、コストをソートして各要素の係数を数えて求める | https://drken1215.hatenablog.com/entry/2020/01/12/142100 |
| arc105_d | D. Let's Play Nim | 1871 | game-mirror-strategy | 同じ枚数の袋が偶数個ずつあるとき後手が相手の手を真似できることを使って勝敗を決める | https://drken1215.hatenablog.com/entry/2020/10/14/120100 |
| abc172_e | E. NEQ | 1880 | inclusion-exclusion, derangement | A_i ≠ B_i の条件を「一致する位置を k 個指定」で包除し、k ごとにまとめて数える | https://kmjp.hatenablog.jp/entry/2020/06/27/1000 |
| abc173_f | F. Intervals on Tree | 1892 | counting-contribution | すべての区間 [L,R] の連結成分数の総和を、頂点の寄与から辺の寄与を引いて求める | https://kmjp.hatenablog.jp/entry/2020/07/06/0930 |
| arc058_b | D. Iroha and a Grid | 1905 | counting-bijection, lattice-paths | 左下の禁止された長方形を避ける格子路を、境界を越える位置で分類して数える | https://drken1215.hatenablog.com/entry/2020/04/06/235844 |
| abc474_f | F. Increment All Divisors | 1911 | zeta-mobius-divisor | 約数ゼータ変換とその逆（約数メビウス変換）を使って、値をそろえる操作の回数を求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0906_abc474#f_-_increment_all_divisors |
| agc049_a | A. Erasing Vertices | 1922 | indicator-variables | 操作回数の期待値を、各頂点が自分で選ばれる確率 1/(自分に到達できる頂点数) の和にする | https://drken1215.hatenablog.com/entry/2020/11/15/104400 |
| abc127_e | E. Cell Distance | 1938 | counting-contribution | K 個のマスの選び方すべてについての距離の総和を、2 マスの組ごとの寄与 × 残りの選び方の数で求める | https://drken1215.hatenablog.com/entry/2019/06/15/111500 |
| agc043_b | B. 123 Triangle | 1945 | lucas-theorem | 差の絶対値を繰り返した最後の値の偶奇を、nCr mod 2 の判定（ビットの包含）で求める | https://drken1215.hatenablog.com/entry/2020/03/22/165200 |
| abc152_f | F. Tree and Constraints | 1965 | inclusion-exclusion | M ≤ 20 個の「パスに黒い辺を含む」条件を、bit 全探索の包除で数える | https://drken1215.hatenablog.com/entry/2020/01/26/164200 |
| abc473_g | G. Wipeout | 1974 | probability-symmetry | ランダムに並べたカードを先頭から順にめくると考えてよいことを使い、確率を求める | https://kmjp.hatenablog.jp/entry/2026/08/29/0900 |
| arc106_d | D. Powers | 1988 | binomial-identities | 全ペアの (A_L+A_R)^x の和を、二項定理で展開してべき乗和から求める | https://kmjp.hatenablog.jp/entry/2020/10/26/1030 |
| abc297_f | F. Minimum Bounding Box 2 | 1990 | inclusion-exclusion, counting-vs-expectation | 外接長方形の面積の期待値を、長方形ごとに「4 辺すべてに点がある」配置を包除で数えて求める | https://kazun-kyopro.hatenablog.com/entry/ABC/297/F |
| abc380_g | G. Another Shuffle Window | 1995 | indicator-variables, probability-symmetry | ランダムに選んだ区間をシャッフルした後の転倒数の期待値を、ペアごとに分けて求める | https://drken1215.hatenablog.com/entry/2024/11/17/113336 |
| abc205_e | E. White and Black Balls | 2025 | reflection-principle, catalan-number | どの接頭辞でも白の数が黒の数 + K 以下になる並べ方を、全体から鏡像法で越えるものを引いて数える | https://drken1215.hatenablog.com/entry/2024/05/20/005905 |
| abc412_f | F. Socks 4 | 2038 | optimal-strategy-expectation | 取り出した靴下のどちらを残すかを期待値の上で決め、残りの回数の期待値を求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0628_abc412#f_-_socks_4 |
| abc266_g | G. Yet Another RGB Sequence | 2045 | multinomial-coefficient | RG が指定回数現れる文字列を、先に一部の文字を並べて残りを挿入する位置で数える | https://drken1215.hatenablog.com/entry/2023/05/04/185000 |
| abc160_f | F. Distributing Integers | 2048 | counting-fix-order | 隣接する頂点から順に番号を書く方法の数（N!/Π 部分木サイズ）を、全頂点を始点として求める | https://kmjp.hatenablog.jp/entry/2020/03/28/1030 |
| abc199_f | F. Graph Smoothing | 2065 | linearity-of-expectation | 辺を選んで値を平均する操作が期待値に線形に作用することを使い、行列累乗で K 回後を求める | https://kmjp.hatenablog.jp/entry/2021/04/24/0900 |
| arc110_d | D. Binomial Coefficient is Fun | 2078 | counting-bijection, binomial-identities | 二項係数の積の総和を、1 本の格子路の数に言い換えて閉じた式にする | https://drken1215.hatenablog.com/entry/2020/12/06/070100 |
| abc226_f | F. Score of Permutations | 2086 | twelvefold-way, partition-number, permutation-cycles | 玉も箱も区別しないマス（整数の分割）を、置換の巡回型として全列挙する | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/1107_abc226#f_-_score_of_permutations |
| abc470_e | E. Concentration | 2096 | optimal-strategy-expectation | 神経衰弱で、取ったペア・場所を知ったカード・未知のカードの数を状態に最適行動の期待値を求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0808_abc470#e_-_concentration |
| arc100_c | E. Or Plus Max | 2111 | counting-at-most-difference, zeta-mobius-subset | 「i or j がちょうど K」の代わりに「K の部分集合」で最大値を求め、累積の max を取る | https://drken1215.hatenablog.com/entry/2018/07/25/200000 |
| abc421_e | E. Yacht | 2122 | optimal-strategy-expectation | サイコロゲームで、振る部分は平均・残す目の選択は max を取るメモ化再帰 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0830_abc421#e_-_yacht |
| agc021_b | B. Holes | 2130 | continuous-probability | 円内のランダムな点に最も近い点が選ばれる確率を、凸包の外角の比で求める | https://drken1215.hatenablog.com/entry/2019/04/02/225600 |
| abc342_f | F. Black Jack | 2141 | optimal-strategy-expectation | 止めるタイミングを選ぶプレイヤーの勝率を、相手の得点の分布と累積和で最大化する | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0224_abc342#f_-_black_jack |
| abc209_e | E. Shiritori | 2153 | game-retrograde-analysis | しりとりの単語を辺とするグラフで、逆辺をたどって勝ち・負け・引き分けを確定させる | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0710_abc209#e_-_shiritori |
| abc189_f | F. Sugoroku2 | 2154 | expectation-linear-equations | 振り出しに戻るマスがあるすごろくで、スタートの期待値を X とおいて各マスを a+bX の形で求める | https://kmjp.hatenablog.jp/entry/2021/01/23/0900 |
| abc295_e | E. Kth Number | 2157 | expectation-tail-sum | ソート後の K 番目の値の期待値を、各 x について P(K 番目 ≥ x) の和として二項係数で求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/0325_abc295#e_-_kth_number |
| abc404_f | F. Lost and Pound | 2162 | partition-number | ボタンの押し方を M の分割として全列挙し、最適な押し方の確率を求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0503_abc404#f_-_lost_and_pound |
| abc144_f | F. Fork in the Road | 2189 | expected-value-dp | DAG 上でゴールまでの通路数の期待値を後ろから求め、各部屋で消す通路を全部試す | https://kmjp.hatenablog.jp/entry/2019/10/28/0930 |
| arc067_c | E. Grouping | 2190 | multinomial-coefficient | 人数の条件を満たすグループ分けを、サイズごとに多項係数を掛け、同じサイズの組の入れ替えで割って数える | https://drken1215.hatenablog.com/entry/2018/06/14/151800 |
| abc149_f | F. Surrounded Nodes | 2208 | indicator-variables | 最小部分木に含まれる白い頂点の個数の期待値を、頂点ごとの確率の和で求める | https://kmjp.hatenablog.jp/entry/2019/12/30/0930 |
| abc172_f | F. Unfair Nim | 2216 | nim | 最初の 2 山の間で石を移して XOR を 0 にできるかを、XOR と AND の桁ごとの関係で決める | https://kmjp.hatenablog.jp/entry/2020/06/27/1030 |
| abc218_g | G. Game on Tree 2 | 2217 | minimax | 木を根から降りて葉で止まるゲームの中央値を、手番ごとに max と min を取る DFS で求める | https://kmjp.hatenablog.jp/entry/2021/09/12/0900 |
| abc206_f | F. Interval Game 2 | 2221 | grundy-number | 区間を選ぶと重なる区間が使えなくなるゲームを、区間ごとの Grundy 数の区間 DP で解く | https://drken1215.hatenablog.com/entry/2021/06/19/224100 |
| abc464_f | F. Random Vault Heist | 2225 | probability-symmetry | 残りから一様に選んでいく過程を、一様ランダムな順列を先頭から見る過程に置き換える | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0627_abc464#f_-_random_vault_heist |
| abc450_g | G. Random Subtraction | 2227 | counting-experiment, expectation-of-square | ランダムな操作でできる値の二乗の期待値を、小さいケースの全探索から規則を見つけて求める | https://kmjp.hatenablog.jp/entry/2026/03/23/0900 |
| abc462_g | G. Completely Wrong | 2232 | derangement | 重複を含む列の並べ替えで、どの位置も指定の値と一致しない確率を撹乱順列の包除を一般化して求める | https://kmjp.hatenablog.jp/entry/2026/06/13/0900 |
| abc334_g | G. Christmas Color Grid 2 | 2242 | counting-vs-expectation | 黒マスを 1 つ消したときの連結成分数の期待値を、各マスを消したときの成分数の和 / マス数で求める | https://kmjp.hatenablog.jp/entry/2023/12/23/1030 |
| agc014_d | D. Black and White Tree | 2266 | game-mirror-strategy | 木に完全マッチングがあれば、後手が相手の塗った頂点の相方を塗り続けて勝てる | https://drken1215.hatenablog.com/entry/2019/05/30/021200 |
| abc242_f | F. Black and White Rooks | 2268 | inclusion-exclusion, stirling-second | 白と黒の駒の置き方を、使われない行・列の集合で包除して数える | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0305_abc242#f_-_black_and_white_rooks |
| abc215_g | G. Colorful Candies 2 | 2276 | indicator-variables | K 個選んだときの色の種類数の期待値を、色ごとに「1 つ以上含まれる確率」の和で求める | https://drken1215.hatenablog.com/entry/2023/09/04/015942 |
| abc290_f | F. Maximum Diameter | 2300 | binomial-identities, cayley-pruefer | 次数列ごとの木の直径の総和を、二項係数の和の公式で閉じた式にする | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/0219_abc290#f_-_maximum_diameter |
| abc281_g | G. Farthest City | 2304 | binomial-variants, counting-labeled-graphs | mod が素数とは限らないので二項係数をパスカルの三角形で作り、距離の層ごとにグラフを数える | https://drken1215.hatenablog.com/entry/2022/12/13/173300 |
| abc268_g | G. Random Student ID | 2311 | probability-symmetry | 接頭辞の関係にない 2 つの文字列の大小は確率 1/2 であることから、順位の期待値を求める | https://kmjp.hatenablog.jp/entry/2022/09/10/0900 |
| abc271_g | G. Access Counter | 2323 | random-walk | 時間帯ごとに確率の決まった遷移を、行列累乗で多数回まとめて計算する | https://kmjp.hatenablog.jp/entry/2022/10/04/1000 |
| agc038_c | C. LCMs | 2327 | mobius-function, zeta-mobius-divisor | 全ペアの lcm の総和を、gcd ごとの和に直してメビウス変換で求める | https://drken1215.hatenablog.com/entry/2020/11/06/031600 |
| arc115_e | E. LEQ and NEQ | 2363 | inclusion-exclusion-dp | 隣り合う値が異なる数列を、等しいと指定した隣接の個数に符号を付けた DP で数える | https://drken1215.hatenablog.com/entry/2021/03/21/235000_1 |
| abc309_g | G. Ban Permutation | 2372 | inclusion-exclusion-dp | P_i と i の差が X 以上になる順列を、違反する位置の個数を状態に持つ包除 DP で数える | https://kmjp.hatenablog.jp/entry/2023/07/08/1000 |
| abc224_g | G. Roll or Increment | 2374 | expectation-linear-equations | 最適戦略に未知数を含む期待値を、変数を置いた 2 通りの式を等しくして解く | https://kmjp.hatenablog.jp/entry/2021/10/26/0900 |
| agc039_c | C. Division by Two with Something | 2379 | mobius-function | 周期ごとの個数を、約数の周期との重複をメビウス反転で除いて数える | https://drken1215.hatenablog.com/entry/2020/11/11/035400 |
| abc352_g | G. Socks 3 | 2413 | expectation-tail-sum | 同じ色の 2 枚がそろうまで取り出す回数の期待値を、「k 回目までそろわない確率」の和で求める | https://drken1215.hatenablog.com/entry/2024/05/05/023117 |
| abc180_f | F. Unbranched | 2419 | counting-at-most-difference, counting-labeled-graphs | 最大の連結成分のサイズがちょうど L のグラフを、「L 以下」から「L−1 以下」を引いて数える | https://drken1215.hatenablog.com/entry/2020/10/21/145700 |
| abc463_g | G. Random Walk Distance | 2452 | random-walk | N 回の ±1 移動後の位置と目標との距離の期待値を、二項係数の和で求める | https://kmjp.hatenablog.jp/entry/2026/06/20/0900 |
| abc235_g | G. Gardens | 2462 | binomial-prefix-sum | 空の庭がない植え方を包除で数え、必要な二項係数の部分和を n を 1 ずつ動かしながら更新する | https://kmjp.hatenablog.jp/entry/2022/01/17/0900 |
| abc240_g | G. Teleporting Takahashi | 2462 | lattice-paths | 3 次元の ±1 移動を軸ごとの回数に分け、平面部分は 45 度回転で独立な 2 本の 1 次元移動にする | https://kmjp.hatenablog.jp/entry/2022/02/23/0900 |
| abc163_f | F. path pass i | 2470 | counting-complement | 各色について、その色の頂点を通る単純パスの数を、全パス数からその色を避けるパス数を引いて求める | https://kmjp.hatenablog.jp/entry/2020/04/20/0930 |
| abc428_g | G. Necklace | 2472 | burnside-lemma | 回転で同一視するネックレスを、最短周期ごとに数えて周期の長さで割る（Burnside を使わない方法） | https://kmjp.hatenablog.jp/entry/2025/10/18/0900 |
| abc277_g | G. Random Walk to Millionaire | 2491 | expectation-of-square | レベルの二乗の期待値を、確率・期待値・二乗の期待値の 3 つを一緒に遷移させて求める | https://kmjp.hatenablog.jp/entry/2022/11/13/0900 |
| abc385_g | G. Counting Buildings | 2492 | stirling-first, generating-function-counting | 左右から見える建物の数の差ごとの順列の数を、挿入 DP と上昇階乗の展開で求める | https://kmjp.hatenablog.jp/entry/2024/12/21/0930 |
| abc303_h | Ex. Constrained Tree Degree | 2501 | cayley-pruefer, generating-function-counting | 次数が集合 S に入る木の数を、Prüfer 列と多項式の累乗で求める | https://drken1215.hatenablog.com/entry/2023/05/28/010200 |
| abc230_g | G. GCD Permutation | 2516 | mobius-function | gcd(i,j) と gcd(P_i,P_j) がともに 1 でない組の数を、メビウス関数を変形した符号で数える | https://kmjp.hatenablog.jp/entry/2021/12/08/1000 |
| abc261_h | Ex. Game on Graph | 2531 | game-retrograde-analysis | 得点のあるグラフ上のゲームを、確定した局面からダイクストラのように後退解析する | https://kmjp.hatenablog.jp/entry/2022/07/24/0930 |
| abc278_g | G. Generalized Subtraction Game | 2533 | grundy-number, interactive-games | 連続するカードの列ごとの Grundy 数を求め、XOR を 0 にする手を毎回出力する（インタラクティブ） | https://kmjp.hatenablog.jp/entry/2022/11/24/0900 |
| abc449_g | G. Many Repunit Sum 2  | 2631 | generating-function-counting | 各桁の上限つきの和を (1−x^10)^(M−1)/(1−x)^M の係数として、二項係数と負の二項係数の畳み込みで求める | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0314_abc449#g_-_many_repunit_sum_2 |
| abc213_g | G. Connectivity 2 | 2663 | zeta-mobius-subset, counting-labeled-graphs | 頂点集合ごとの連結な部分グラフの数を部分集合 DP で求め、頂点 1 と k を含む集合について足す | https://drken1215.hatenablog.com/entry/2021/08/12/132500 |
| abc247_h | Ex. Rearranging Problem | 2664 | stirling-first, permutation-cycles | 最小 swap 回数ごとの並びの数（巡回の個数で決まる）を、色ごとの多項式の積で求める | https://kmjp.hatenablog.jp/entry/2022/04/10/1100 |
| abc331_g | G. Collect Them All | 2668 | coupon-collector | 確率の異なる N 種類がそろうまでの回数の期待値を、min-max 包除と多項式で求める | https://kmjp.hatenablog.jp/entry/2023/12/08/0930 |
| abc295_h | Ex. E or m | 2728 | zeta-mobius-subset | 行ごとの状態を部分集合で持つ DP の遷移を、上位集合のゼータ変換で高速化する | https://kmjp.hatenablog.jp/entry/2023/03/26/0930 |
| abc255_g | G. Constrained Nim | 2734 | grundy-patterns | 取れない手がある Nim の Grundy 数を、例外の局面だけ別に扱って圧縮して求める | https://kmjp.hatenablog.jp/entry/2022/06/12/0900 |
| abc303_g | G. Bags Game | 2736 | minimax | 袋を取り合うゲームの得点差を、区間 DP と区間 max の高速化で求める | https://kmjp.hatenablog.jp/entry/2023/05/27/0900 |
| abc212_h | H. Nim Counting | 2741 | nim-counting | 山の数と各山の石の数の候補から、XOR が 0 でない Nim の盤面の数をアダマール変換で数える | https://drken1215.hatenablog.com/entry/2021/08/01/025200 |
| arc106_f | F. Figures | 2755 | cayley-pruefer | 各部品の穴の数を次数とみなし、Prüfer 列の考え方で全域木の数を閉じた式にする | https://drken1215.hatenablog.com/entry/2020/10/25/140600 |
| abc253_h | Ex. We Love Forest | 2758 | matrix-tree-theorem | 頂点集合ごとの全域木の数を行列木定理で求め、集合の DP で森の数を数える | https://kmjp.hatenablog.jp/entry/2022/05/28/1030 |
| abc198_f | F. Cube | 2769 | burnside-lemma | 立方体の 24 通りの回転それぞれで動かない書き込み方を数え、平均を取る | https://kmjp.hatenablog.jp/entry/2021/04/11/0900 |
| abc221_h | H. Count Multiset | 2793 | partition-number | 同じ値を M 個まで含む多重集合の数を、分割数の漸化式（全体から 1 を引く／1 を取り除く）で求める | https://kmjp.hatenablog.jp/entry/2021/10/03/1030 |
| abc226_h | H. Random Kth Max | 2813 | continuous-probability | 区間ごとに一様な実数の K 番目の値の期待値を、区分的な多項式の積分で求める | https://kmjp.hatenablog.jp/entry/2021/11/08/0930 |
| abc242_h | Ex. Random Painting | 2835 | coupon-collector | 区間をランダムに塗って全マスが塗られるまでの回数の期待値を、min-max 包除と DP で求める | https://kmjp.hatenablog.jp/entry/2022/03/07/0930 |
| abc214_g | G. Three Permutations | 2893 | inclusion-exclusion-dp | 2 つの順列の両方と異なる順列を、違反の個数ごとに数えてから包除する | https://kmjp.hatenablog.jp/entry/2021/08/16/0900 |
| arc101_c | E. Ribbons on Tree | 2913 | inclusion-exclusion-dp | 木の頂点のペアリングを、切る辺の集合に符号を付けた木 DP で包除する | https://drken1215.hatenablog.com/entry/2019/06/21/024200 |
| abc309_h | Ex. Simple Path Counting Problem | 3029 | reflection-principle | 上下の端を越えない移動の数を、鏡像法で多項式の係数に落とし込む | https://kmjp.hatenablog.jp/entry/2023/07/08/1030 |
| abc378_g | G. Everlasting LIDS | 3051 | young-tableaux | 最長増加・減少部分列の長さの条件を満たす順列の数を、Robinson–Schensted 対応とフック長公式で数える | https://kmjp.hatenablog.jp/entry/2024/11/07/1000 |
| abc336_g | G. 16 Integers | 3138 | matrix-tree-theorem | 有向グラフのオイラー路の数を BEST 定理（行列木定理を含む）で数える | https://kmjp.hatenablog.jp/entry/2024/01/16/0930 |
| abc216_h | H. Random Robots | 3295 | lgv-lemma | K 個のロボットが衝突しない確率を、LGV 補題の行列式を bitDP で展開して求める | https://kmjp.hatenablog.jp/entry/2021/09/02/0900 |
| abc229_h | H. Advance or Eat | 3308 | partizan-games | 先手と後手で動きの違う駒のゲームを、局面に数（超現実数）を割り当てて和で判定する | https://kmjp.hatenablog.jp/entry/2021/12/01/0930 |
| abc265_h | Ex. No-capture Lance Game | 3319 | partizan-games | 向かい合う香車は Grundy 数、それ以外は手数の貯金として扱い、先手必勝の配置を数える | https://kmjp.hatenablog.jp/entry/2022/08/23/0930 |

## 6. 横断ページへの材料

### 6.1 逆引き辞典（制約・言い回し → 疑う手法）

| 制約・言い回し | 疑う手法（key） |
| --- | --- |
| 「〜の個数を 998244353 で割った余り」「何通り」 | 数え上げの考え方（counting-mindset）、二項係数の前計算（binomial-precompute） |
| 「少なくとも 1 つ」「〜を含む」 | 補集合（counting-complement） → 条件が複数なら包除原理（inclusion-exclusion） |
| 「すべて異なる」「$A_i \ne B_i$」「どの〜も元の位置にない」 | 包除原理、撹乱順列（derangement） |
| 条件（禁止）が $M \le 20$ 個 | 包除原理を bit 全探索で（inclusion-exclusion） |
| 障害物 $N \le 3000$ 個、グリッドは $10^5$ | 包除 DP（inclusion-exclusion-dp）、格子路（lattice-paths） |
| 「グリッドの左上から右下へ」「$H,W \le 10^5$」 | 格子路（lattice-paths） |
| 「和が $N$ になる非負整数の組」「単調な数列の個数」「切り分け方」 | 重複組合せ（stars-and-bars）、対応づけ（counting-bijection） |
| 「各文字を使う個数が決まっている」「並べ替えてできる文字列の数」 | 多項係数（multinomial-coefficient） |
| 「区別しない」「グループに分ける」「各グループ 1 人以上」 | 写像12相（twelvefold-way）、第2種スターリング数、分割数 |
| $N \le 10$〜$12$ で「グループ分けを全部試す」 | ベル数で全列挙の数を見積もる（bell-number） |
| $N \le 50$ 程度で「長さの組合せ（多重集合）を全部試す」 | 分割数で全列挙の数を見積もる（partition-number） |
| 「異なる〜の個数」「操作で作れるものの種類数」 | 重複の除き方（counting-dedup） |
| 「回転して一致するものは同じ」「数珠」 | Burnside の補題（burnside-lemma）、最短周期で分類（counting-dedup） |
| 「〜より先に」「木の頂点に順に番号を振る」 | 順序の固定（counting-fix-order） |
| 「すべての〜についての総和」 | 寄与（counting-contribution） |
| 「最大値がちょうど $K$」「ちょうど $K$ 個」 | 「以下」の差（counting-at-most-difference） |
| 「gcd の総和」「互いに素な組」「周期」 | 約数包除（divisor-inclusion-exclusion）、メビウス関数 |
| 「各値の倍数（約数）であるものの個数」「lcm の総和」 | 約数・倍数のゼータ変換（zeta-mobius-divisor） |
| $N \le 20$ で「部分集合ごとの和・最大」「$A_i$ OR $A_j$」 | 高速ゼータ変換（zeta-mobius-subset） |
| 「どの接頭辞でも A の数 ≥ B の数」「括弧列」「途中で負にならない」 | 鏡像法・カタラン数（reflection-principle） |
| 「隣り合う 2 つから新しい値を作る操作を繰り返す（三角形）」「mod 2・mod 3」 | 係数が二項係数になる、Lucas の定理（lucas-theorem） |
| 「辞書順で $K$ 番目」 | 辞書順 k 番目（kth-combination） |
| 「$n \le 10^9$ で $r$ が小さい」「mod $M$ が入力（素数とは限らない）」 | 二項係数の変種（binomial-variants） |
| 「頂点にラベルのある木の数」「次数の条件つきの木」 | Cayley・Prüfer（cayley-pruefer） |
| 「全域木の個数」 | 行列木定理（matrix-tree-theorem） |
| 「条件を満たすグラフの個数」「連結な部分グラフの数」 | 連結なグラフの数え上げ（counting-labeled-graphs） |
| 「期待値（確率）を mod 998244353 で出力」 | 有理数の mod 表現（rational-mod） |
| 「〜の個数の期待値」「〜の種類数の期待値」 | 期待値の線形性・指示確率変数（linearity-of-expectation、indicator-variables） |
| 「最大値（最小値・$K$ 番目）の期待値」 | tail sum（expectation-tail-sum） |
| 「〜になるまでの回数の期待値」 | 期待値 DP（expected-value-dp）、幾何分布（geometric-distribution） |
| 「出た目が〜なら振り直し」「0 の目」「その場にとどまる」 | 自己ループの除去（self-loop-expectation） |
| 「振り出しに戻る」「円形に並んだ人が順に」「無限に続くことがある」 | 未知数を残す・方程式（expectation-linear-equations） |
| 「すべての種類を集めるまで」「全頂点を訪れるまで」 | コンプガチャ型（coupon-collector）、min-max 包除 |
| 「一様ランダムにシャッフル」「残りから一様に選ぶ」 | 対称性（probability-symmetry） |
| 「好きなタイミングでやめられる」「最適に行動したときの期待値」 | 最適戦略の期待値（optimal-strategy-expectation） |
| 「$K$ 回後に〜にいる確率」「どちらが先にゴールするか」 | 確率 DP（probability-dp） |
| 「〜の二乗の期待値」「分散」 | 二乗の期待値（expectation-of-square） |
| 「実数を一様ランダムに選ぶ」 | 連続値の確率（continuous-probability） |
| 「先手と後手が交互に」「両者が最適に行動したとき」「First / Second」 | ゲームの基本（game-basics）、ゲーム DP |
| $N \le 16$〜$18$ で「残りのカードの集合」 | ゲーム DP の bitDP（game-winning-losing-dp） |
| 「山から石を取る」「最後に取った人が勝ち」 | Nim（nim）、Grundy 数（grundy-number） |
| 「複数の盤面（山）のどれか 1 つを選んで操作」 | Grundy 数（grundy-number） |
| 「1 回に取れる個数に上限・範囲がある」 | Nim の変種（nim-variants）、Grundy 数の規則（grundy-patterns） |
| 「無限に続く場合は Draw」「同じ局面が繰り返されうる」 | 後退解析（game-retrograde-analysis） |
| 「太郎は X−Y を最大化、次郎は最小化」 | ミニマックス（minimax） |
| 「盤面が対称」「同じものが偶数個ずつ」 | 真似戦略（game-mirror-strategy） |
| 「先手と後手で動かせるものが違う」 | 非不偏ゲーム（partizan-games）、または真似戦略 |
| 「ジャッジと対戦する（インタラクティブ）」 | インタラクティブなゲーム（interactive-games） |

### 6.2 似た手法の使い分け

**二項係数の計算方法**

| 状況 | 方法 |
| --- | --- |
| mod が素数 $p$ で、$n < p$、$n \le 10^7$ 程度、質問が多い | 階乗・逆階乗の前計算（$O(n)$ 前計算、$O(1)$ 質問） |
| $n$ が $10^9$ 以上、$r$ が小さい | 分子 $r$ 項の積と $r!$ の逆元（$O(r)$） |
| mod が素数でない、$n \le 5000$ 程度 | パスカルの三角形（$O(n^2)$） |
| mod が小さい素数（$n \ge p$ がありうる） | Lucas の定理 |
| mod なしの正確な値 | 逐次計算（掛けてから割る）と `__int128`。確率なら `long double` や対数 |

**「条件を満たさないものを除く」系**

| 状況 | 方法 |
| --- | --- |
| 条件が 1 つ | 補集合 |
| 条件が数個〜20 個 | 包除原理（bit 全探索） |
| 条件が対称（何個破ったかだけで数が決まる） | 包除原理を $k$ ごとにまとめる |
| 条件が列・木に沿って並ぶ、障害物が多い | 包除 DP（符号付き DP、最初の障害物で分類） |
| 条件が約数の構造（gcd・周期） | 約数包除、メビウス関数 |
| 部分集合ごとの量を全部の集合について集計 | 高速ゼータ・メビウス変換 |

**期待値の求め方**

| 状況 | 方法 |
| --- | --- |
| 量が和に分けられる | 線形性・指示確率変数（独立性は不要） |
| 最大値・$K$ 番目 | tail sum $\sum P(X \ge k)$ |
| 終わるまでの量 | 後ろ向きの期待値 DP |
| 自分自身に戻る遷移が 1 つ | 移項 |
| 戻る先が 1 か所（スタートなど） | 未知数 $X$ を残して $a+bX$ |
| 一般の状態の連立 | ガウスの消去法（06） |
| 時刻が決まっている・分布が要る | 前向きの確率 DP |
| 選択がある | 選択は max/min、偶然は平均（自己参照があれば二分探索） |

**ゲームの解き方**

| 状況 | 方法 |
| --- | --- |
| 状態が小さく遷移が DAG、勝ち負けだけ | ゲーム DP・メモ化再帰 |
| 得点の差が問われる | ミニマックス（negamax で 1 本の式） |
| 遷移にサイクル、引き分けあり | 後退解析 |
| 独立なゲームの和、両者の手が同じ | Grundy 数の XOR |
| 状態が巨大 | 実験で規則（周期・式）を見つける |
| 盤面が対称 | 真似戦略 |
| 両者の手が違う | 非不偏ゲーム（超現実数）、または戻す戦略の考察 |

### 6.3 早見表

- 二項係数：$\binom{n}{k}=\frac{n!}{k!(n-k)!}$、$\binom{n}{k}=\binom{n-1}{k-1}+\binom{n-1}{k}$、$k<0$ や $k>n$ は 0
- 重複組合せ：非負整数解 $\binom{n+k-1}{k-1}$、正整数解 $\binom{n-1}{k-1}$、隣り合わない $k$ 個 $\binom{n-k+1}{k}$
- 多項係数：$\frac{(a_1+\cdots+a_m)!}{a_1!\cdots a_m!}$
- 恒等式：$\sum_k\binom{n}{k}=2^n$、$\sum_k(-1)^k\binom{n}{k}=[n=0]$、$\sum_i\binom{a}{i}\binom{b}{k-i}=\binom{a+b}{k}$、$\sum_{i=r}^{n}\binom{i}{r}=\binom{n+1}{r+1}$、$k\binom{n}{k}=n\binom{n-1}{k-1}$
- 包除：$|\overline{A_1}\cap\cdots\cap\overline{A_m}|=\sum_{S}(-1)^{|S|}N(S)$
- 撹乱順列：$D_n=(n-1)(D_{n-1}+D_{n-2})$、$D_1..D_6=0,1,2,9,44,265$
- カタラン数：$C_n=\frac{1}{n+1}\binom{2n}{n}$、$C_0..C_6=1,1,2,5,14,42,132$
- 鏡像法：直線 $y=x+c$ を越える経路の数 = 終点を折り返した点への経路の数
- 第2種スターリング数：$S(n,k)=S(n-1,k-1)+kS(n-1,k)$、全射 $k!S(n,k)=\sum_i(-1)^i\binom{k}{i}(k-i)^n$
- ベル数：$B_0..B_{12}=1,1,2,5,15,52,203,877,4140,21147,115975,678570,4213597$
- 分割数：$p(n,k)=p(n,k-1)+p(n-k,k)$、$p(10)=42$、$p(30)=5604$、$p(50)=204226$
- 第1種スターリング数（符号なし）：$c(n,k)=c(n-1,k-1)+(n-1)c(n-1,k)$
- 巡回型ごとの置換の数：$N!/\prod_\ell(\ell^{m_\ell}m_\ell!)$
- Cayley：ラベル付き木 $n^{n-2}$、次数指定 $\frac{(n-2)!}{\prod(d_i-1)!}$
- Burnside：$\frac{1}{|G|}\sum_g|\mathrm{Fix}(g)|$、数珠（回転のみ）$\frac1n\sum_{d\mid n}\varphi(d)k^{n/d}$
- 期待値：$E[X]=\sum_{k\ge1}P(X\ge k)$、幾何分布 $1/p$、コンプガチャ $NH_N$、ランダム順列の固定点の個数の期待値 1、転倒数の期待値 $n(n-1)/4$
- mod：$1/2 \equiv 499122177 \pmod{998244353}$
- ゲーム：Nim は XOR ≠ 0 なら先手必勝、Grundy 数 = mex、和は XOR、上限 $k$ の Nim の Grundy 数は $x \bmod (k+1)$、逆形 Nim はすべての山が 1 以下なら 1 の山が偶数個で先手必勝

### 6.4 用語集に入れるべき語

| 用語 | 短い定義 |
| --- | --- |
| 二項係数 | $n$ 個から $k$ 個を選ぶ方法の数 $\binom{n}{k}$ |
| 逆階乗 | $1/k! \bmod p$。前計算で二項係数を $O(1)$ にするために持つ |
| 重複組合せ | 重複を許して $k$ 個選ぶ方法の数（玉と仕切り） |
| 多項係数 | 種類ごとの個数が決まった並べ方の数 |
| 写像12相 | 玉と箱の区別の有無と制限の 12 通りの数え上げの整理 |
| 包除原理 | 和集合（条件を 1 つも破らないもの）を、共通部分の個数の符号付きの和で求める原理 |
| 撹乱順列（完全順列） | どの $i$ でも $p_i \ne i$ となる順列 |
| 約数包除 | gcd がちょうど $g$ の個数を、$g$ の倍数の個数から大きい順に引いて求める方法 |
| メビウス関数 | $\sum_{d\mid n}\mu(d)=[n=1]$ を満たす数論的関数。包除の符号 |
| 高速ゼータ変換 | 部分集合（または約数）についての和を、軸ごとの累積和で求める変換。逆がメビウス変換 |
| 鏡像法 | 境界を越える経路を、越えた後を折り返して別の終点への経路に対応させる方法 |
| カタラン数 | 正しい括弧列の個数 $\frac{1}{n+1}\binom{2n}{n}$ |
| スターリング数 | 第2種：集合を $k$ 個の空でない組に分ける数。第1種：$k$ 個の巡回からなる置換の数 |
| ベル数 | 集合の分割の総数 |
| 分割数 | 整数を順序を区別せずに正整数の和で表す方法の数 |
| Burnside の補題 | 同一視したものの数 = 各操作で動かないものの数の平均 |
| Prüfer 列 | ラベル付き木と長さ $n-2$ の列の 1 対 1 対応 |
| 期待値の線形性 | $E[X+Y]=E[X]+E[Y]$（独立でなくても成り立つ） |
| 指示確率変数 | 事象が起きれば 1、起きなければ 0 の確率変数。期待値は確率に等しい |
| 有理数の mod 表現 | 既約分数 $P/Q$ を $P\cdot Q^{-1} \bmod p$ で表すこと |
| 自己ループ | 期待値の漸化式で自分自身が右辺に現れること。移項して解く |
| 幾何分布 | 成功確率 $p$ の試行を成功まで繰り返す回数の分布（期待値 $1/p$） |
| 必勝・必敗 | 手番の人が最適に動けば必ず勝てる（負ける）局面 |
| Nim | 山から石を取り、最後に取った人が勝つゲーム。XOR で判定 |
| Grundy 数 | 不偏ゲームの局面に割り当てる値 $\mathrm{mex}\{\text{次の局面の値}\}$ |
| mex | 集合に含まれない最小の非負整数 |
| 後退解析 | 終局から逆向きに勝敗を確定させる方法。サイクルがあっても使える |
| ミニマックス | 手番ごとに自分に最善の手を選ぶとして値を後ろから決める方法 |
| 真似戦略 | 相手の手を対称な位置で真似して負けない戦略 |

## 7. 設計への提言

### 7.1 ページの分け方の案

topics.yaml の `page` は次の案に基づく（own = 単独ページ、section-of = 他ページの節、overview = 発展の概要ページ）。

- **数え上げ（考え方）**：総論 1 ページ（節：補集合、ちょうど＝以下の差、寄与、実験）＋ 対応づけ・重複の除き方・順序の固定の 3 ページ。考え方を道具より先に置き、道具のページから「どの考え方で使うか」を参照させる
- **数え上げ（二項係数の系統）**：順列・組合せ（基礎）、二項係数（節：辞書順 k 番目）、前計算（節：変種）、多項係数、重複組合せ、写像12相（節：第2種スターリング数・ベル数・分割数）、恒等式、格子路、Lucas、鏡像法とカタラン数
- **数え上げ（包除の系統）**：包除原理（節：撹乱順列）、包除 DP、約数包除、メビウス関数、ゼータ変換（部分集合）、ゼータ変換（約数・倍数）
- **数え上げ（構造）**：置換の巡回分解、Cayley と Prüfer、連結なグラフの数え上げ
- **発展の概要**：第1種スターリング数、Burnside の補題、行列木定理、LGV 補題、二項係数の部分和、母関数の考え方、Young 図形
- **確率・期待値**：確率の基本、mod 表現、線形性（節：指示確率変数・総和と期待値）、tail sum、二乗の期待値、期待値 DP（節：条件付き期待値・自己ループ・確率 DP・ランダムウォーク）、方程式で解く期待値、コンプガチャ型（節：幾何分布）、対称性、最適戦略、連続値の確率（概要）
- **ゲーム**：ゲームの基本（節：ゲーム DP・偶奇・インタラクティブ）、ミニマックス、後退解析、Nim（節：変種・逆形・局面の数え上げ）、Grundy 数（節：規則の発見）、真似戦略、非不偏ゲーム（概要）

単独ページはおよそ 40、概要ページは 9、残りは節になる。写像12相は「地図」のページとして短く作り、各マスの詳しい扱いを個別ページに振り分けるとよい（12 マスを 1 ページに詰めると長くなりすぎ、逆に 12 ページに分けると各ページが薄くなる）。

### 7.2 ゲームのレベル判定（根拠）

| 知識 | レベル | 根拠 |
| --- | --- | --- |
| 必勝・必敗の判定（ゲーム DP） | 水 | 状態の小さいゲーム DP が abc354_e（1223）・abc270_d（1300）・abc278_f（1452） と水色帯にまとまる。abc195_e（1609）・abc380_f（1769） は青。基本形の tessoku_book_af（なし）・dp_k（なし） は diff なしだが教科書的 |
| ミニマックス（得点差） | 水 | abc201_d（1317）・abc349_e（1464） と水。abc025_c（1640） は青。木の上の abc218_g（2217）・abc246_g（2313） は黄、区間 DP の abc303_g（2736） は発展 |
| Nim（XOR の判定） | 水 | Nim そのものが答えになる ABC の問題は少なく、変種の arc168_b（1289） が水。Nim の結論を前提に考察する abc172_f（2216） は黄 |
| Grundy 数・SG 定理 | 青 | Grundy 数が必須の問題は typical90_ae（なし）（★6 ＝ 1600〜1999 相当）・abc297_g（1834）・abc206_f（2221）・abc278_g（2533） と青〜黄にまとまる。abc368_f（1180） は 1180 と低いが、Grundy 数を知っていれば素直に解ける易しい例で、知らなければ解けない。入口の例題として水色向けに置くのがよい |
| 後退解析（サイクルのあるゲーム） | 黄 | abc209_e（2153）（黄）、abc261_h（2531）（発展） |
| 真似戦略・偶奇 | 青 | arc143_c（1805）・arc105_d（1871）・agc033_c（1758）・arc064_b（1814） と青。ABC では abc398_e（1238）（水、インタラクティブ） |
| 非不偏ゲーム | 発展 | abc229_h（3308）・abc265_h（3319） |
| 逆形 Nim | 発展 | ABC・ARC での出題を確認できなかった |

結論：ゲームは「判定の基本（ゲーム DP）とミニマックス」が水、「Grundy 数」が青、「後退解析」が黄、「非不偏」が発展。Grundy 数は最近の ABC で易しい問題（abc368_f（1180））にも出ているので、水色向けのロードマップから見えるようにしておく。

### 7.3 確率・期待値のレベル判定

- 水：mod 表現、期待値の線形性、期待値 DP（後ろ向き）、自己ループの除去、確率 DP、対称性（2 状態に縮める）、最適戦略の基本形。根拠は §2.3 の E 問題群（1200〜1450）
- 青：指示確率変数を使うペアごとの確率（typical90_bn（なし）・agc049_a（1922）・abc380_g（1995））、方程式で閉じる期待値（arc174_c（1706）・abc333_f（1770））、総和と期待値の行き来（abc297_f（1990））
- 黄：tail sum（abc295_e（2157））、二乗の期待値（abc450_g（2227））、振り出しに戻るすごろく（abc189_f（2154））、最適戦略の応用（abc342_f（2141）・abc421_e（2122））
- 発展：min-max 包除（abc331_g（2668）・abc242_h（2835））、連続値の確率（abc226_h（2813））、FPS と組み合わせる期待値（abc352_g（2413））
- 基礎：確率の基本、幾何分布、コンプガチャ型（等確率）

### 7.4 レベル割り当てで迷う点

1. **包除原理**：2 条件なら茶色（abc131_c（518））、一般形は青（abc172_e（1880）・abc152_f（1965））。1 ページで「2 条件 → 一般形 → $k$ ごとにまとめる」と段階を追い、ページのレベルは青とするのがよい
2. **重複組合せ**：式は基礎（abc185_c（374））だが、応用（abc156_e（1514）・abc110_d（1695））は水〜青。基礎ページとし、応用の型を厚めに書く
3. **期待値の線形性**：易しい例（abc154_d（485））は茶色だが、線形性に気づくこと自体が難しい問題（agc049_a（1922）・abc199_f（2065））は青〜黄。ページは水とし、指示確率変数の節（青）を同じページに置く
4. **写像12相**：地図としては青だが、マスによって基礎（重複組合せ）から黄（分割数）まで幅がある。地図ページのレベルは青、各マスのページは個別に判定した
5. **メビウス関数とゼータ変換（部分集合）**：ABC では発展の帯でしか必須にならない（ARC・AGC の例で黄）。ABC の青帯の問題は約数包除で足りるので、約数包除（青）を本命にし、メビウスは黄の短いページにする
6. **Lucas の定理**：ABC での出題が見つからない（ARC・AGC で青）。ページは作るが、ロードマップ上の優先度は下げる

### 7.5 見落としやすい項目

- **全列挙の個数の見積もり**：ベル数（$B_{12}\approx4.2\times10^6$）・分割数（$p(50)\approx2\times10^5$）を知らないと、abc390_d（1607）・abc226_f（2086）・abc404_f（2162） の「全部試せる」という判断ができない。計算量の見積もり（01）の早見表にも載せるとよい
- **mod の値は大小比較できない**：最適戦略の期待値を mod で答える問題での落とし穴
- **min-max 包除**：コンプガチャ型の一般化として G・Ex に出る
- **二乗の期待値**：線形性が使えない量の扱い
- **Young 図形・フック長公式**：abc378_g（3051） のみだが、ABC の範囲に出ている
- **最短周期で分類して割る**（abc428_g（2472））：Burnside の代わりに約数包除の形で回転の同一視を処理する方法
- **二項係数の mod が素数でない場合**：abc281_g（2304） のようにパスカルの三角形で作る
- **インタラクティブなゲーム**：必勝の判定に加えて「必勝手を毎回見つける処理」が要る

### 7.6 ほかの分野との境界の意見

- **01（探索・考察）**：補集合・寄与・主客転倒・対称性・偶奇・鳩の巣原理の一般論は 01 に置く。07 は「数え上げ・期待値・ゲームでの使い方」に絞り、01 のページへリンクする。とくに寄与（counting-contribution）と指示確率変数（indicator-variables）は同じ計算なので、01 の寄与のページと 07 の期待値のページを相互に参照させる。鳩の巣原理（典型90 088、abc179_e（1175） など）は 01 がよい
- **02（DP）**：期待値 DP とゲーム DP のページは 07 に置き、02 の章からは「DP の型」として参照するのがよいと考える。理由：学習者が詰まるのは状態設計より「なぜ後ろ向きか」「自己ループをどう消すか」「必勝・必敗の定義」という数学の部分だから。一方、確率・期待値の DP の高速化（累積和・bitDP・行列累乗）、括弧列や部分列を数える DP、挿入 DP（abc385_g（2492））、包除 DP の状態設計は 02 の担当として、07 からリンクする。「数え上げ DP の重複を防ぐ設計」は 07 の重複の除き方から 02 へつなぐ
- **03（グラフ）**：後退解析はゲームの文脈で 07 に置き、逆辺の BFS の実装は 03 を前提にする。置換の巡回分解の数え上げは 07、Functional graph の構造は 03。関節点・橋（abc334_g（2242））は 03
- **04（木）**：ラベル付き木の数え上げ（Prüfer）は 07、木 DP・全方位木 DP（abc160_f（2048） の全頂点ぶんの計算）は 02・04。木の上のゲーム（abc218_g（2217）・abc246_g（2313）・agc033_c（1758））は 07 のミニマックス・偶奇の節から 04 を参照
- **05（データ構造）**：転倒数を数える BIT は 05、転倒数の期待値は 07。遅延セグ木で期待値を更新する abc417_f（1414） は両方の例題にできる
- **06（整数論・代数）**：逆元・Fermat の小定理・繰り返し二乗法・篩・素因数分解・FPS・NTT・XOR 畳み込み（アダマール変換、abc212_h（2741）・abc367_g（3110））・行列累乗・ガウスの消去法・行列式・ラグランジュ補間・商の列挙は 06。07 はこれらを前提として参照する。約数・倍数のゼータ変換と GCD/LCM 畳み込みはどちらに置いてもよいが、約数包除の延長として理解しやすいので 07 に置き、06 の畳み込みのページから参照するのを提案する。有理数の mod 表現は「なぜ分数を mod で表してよいか」という確率側の意味を 07、逆元の計算を 06 とする
- **08（その他）**：インタラクティブ形式そのもの（入出力・フラッシュ）は 08、必勝戦略の実行は 07。乱択アルゴリズムの期待計算量は 08。文字列ゲーム（abc433_g（2060）：接尾辞配列を使う）は 08 の例題として参照
- **00（全体・横断）**：実験とストレステスト（counting-experiment）は 00 の「戦い方」と共有する。全列挙の個数の見積もり（ベル数・分割数・二項係数の大きさ）は早見表へ

### 7.7 調査の限界と未確認の点

- Web 検索の枠が尽きたため、第三者の解説は kmjp・ikatakos・drken・プロひろ・Kazun の記事に偏っている。これらが扱っていない ABC の D・E 問題には、手法に該当するのに拾えていないものがありうる
- ABC358 E（Alphabet Tiles、多項係数の DP と思われる）は第三者の解説で内容を確認できなかったので載せていない
- 典型90 066（typical90_bn（なし））は作者の GitHub の問題文テキストで内容を確認し、裏付けとして解説画像のファイルを示した（画像そのものは読んでいない）
- difficulty は 2026-10-21 のキャッシュの値で、今後の再計算で多少動く
