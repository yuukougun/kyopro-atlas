# b5 検証：problem-sets（docs/guide/problem-sets.md）

- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-22
- 確かめたもの
    - `python3 tools/check_pages.py --page problem-sets`：エラー 0・警告 0
    - front matter の差分：stage（stub → draft）と updated だけ。sections・related などは変わっていない
    - 数の再集計（`.cache/atcoder-problems/`、2026-10-21T01:14 取得）：問題集の問題数（typical90 90・dp 26・tdpc 20・ndpc 20・tessoku-book 151・math-and-algorithm 104・practice2 12・aalc001 24・fps-24 24・game-24 24・atc001 3・atc002 3・abs 11・abl 6）、開催月（dp 2019-01・tdpc 2013-08・ndpc 2026-05・aalc001 2026-10・fps-24 2025-11・game-24 2026-10・abl 2020-09）、典型90問の★ごとの問題数（10・20・14・17・14・15、水以上 46）、ADT（2023-10-17 開始、EASY 5 問・ALL 9 問・60 分、MEDIUM・HARD は 2026-02-05 まで、2026 年は月〜金に 1 日 2 回、CODE QUEEN の問題 122 問が混じる、ALL の A〜E は全 1414 回で EASY と同じ、位置ごとの中央値 12・13・57・60・354・357・844・1295・1819）、AWC（2026-02-09 開始、平日の欠けなし、awc0001〜0005 は 90 分、awc0100・awc0150 は 15 問 150 分、182 回とも rate_change「-」、difficulty なし）、PAST 24 回・各 15 問、ARC--（800〜2399）・ARC・ARC++ の区分、最近の ABC の表 120 行と位置ごとの difficulty の中央値（D 787・E 1267・F 1888・G 2389）。すべて本文と一致した
    - 典型90問の告知記事（Qiita）：★と difficulty の範囲の表は本文と一致（★1 は〜149）
    - AtCoder Problems の FAQ・recommend.md・virtual_contest.md（GitHub）：50% の定義、Easy 80%・Moderate 50%・Difficult 20%、Bacha Gacha と参加者の解いた問題を除く設定は本文と一致
    - NoviSteps の About：17 段階（11Q〜1Q・1D〜6D）、投票、AC・解説 AC・挑戦中・未挑戦の記録、トピックごとの問題集は本文と一致
    - AtCoder Clans：目的と形式ごとの分類は本文と一致
    - library-checker-problems の categories.toml：14 分類・235 問は本文と一致（Sample 3 問を含む）
    - kyopro_educational_90 のリポジトリ：editorial/ に 001.jpg などの画像がある（「解説は GitHub に画像で置かれている」は正しい）
    - 本文の各問題集の表に出るページの level を数えた（典型90 基礎34・水18・青12・黄5・発展1、EDPC 基礎5・水13・青9・黄2・発展1、TDPC 基礎1・水5・青3・黄4・発展1、ACL Practice 基礎1・水4・青2・黄4・発展1、鉄則本 基礎3・水4・青1・黄3、アルゴ数学 基礎3・青1）
- コード片・図：このページにはない（`snippets/problem-sets/`・`docs/img/problem-sets/` がなく、本文に取り込みも SVG もない）。code.md・figure.md の観点は該当なし。catalog の visual の指定も見当たらない

## 指摘

### 1. 直すべき｜事実（F3）｜#collections の表の典型90問の行・#typical90-stars の 3 つめの箇条

- **問題**：(a) 「2021 年に毎日 1 問ずつ出た」とあるが、告知記事では日曜を除いて毎日 1 問（2021-03-30〜07-11）である。(b) 「作者の勧める進め方は 3 つある」とあるが、記事の「典型 90 問を解くにあたって重要な 4 つのポイント」は 4 つで、本文は 4 つめの「コンテストに参加しよう」を落としている。数を言い切っているので誤りになる
- **根拠**：E869120 の告知記事（https://qiita.com/e869120/items/1b2a5f0f07fd927e44e9）の出題期間の節と第 5 章
- **直し方**：(a) 「2021 年に日曜を除く毎日 1 問ずつ出た」にする（または「2021 年に 1 日 1 問ずつ出た」とぼかす）。(b) 「作者の勧める取り組み方は 4 つある」とし、「本番のコンテストにも出て、学んだ典型を使う」を足す（言い回しは記事に寄せすぎない）

### 2. 直すべき｜出典（F9）｜#references の drken の記事

- **問題**：題名を「」で囲んで「Educational DP Contest / DP まとめコンテストの A〜E 問題の解説と類題集」と書いているが、記事の題名は「動的計画法超入門！ Educational DP Contest の A ～ E 問題の解説と類題集」である。題名として示す形なので一致させる
- **根拠**：https://qiita.com/drken/items/dc53c683d6de8aeacf5a の題名
- **直し方**：`drken「動的計画法超入門！ Educational DP Contest の A〜E 問題の解説と類題集」（Qiita）` にする。位置づけ（「初めて DP を学ぶ人向けに作られた問題」）は記事どおりなので、説明はそのままでよい

### 3. 直すとよい｜事実（F2）｜#collections の表の鉄則本の行

- **問題**：中身の列で章を「累積和・二分探索・DP・数学・考察・データ構造・グラフ」と挙げているが、本には 7 章「ヒューリスティック」と 10 章「総合問題・力試し問題」もあり、問題集にも A46 Heuristic 1・A49 Heuristic 2 がある。列挙が全章のように読める
- **根拠**：kyopro-tessoku の README の章の表（1〜10 章）。AtCoder Problems のデータの tessoku-book の問題名
- **直し方**：「…・データ構造・グラフ、ヒューリスティック・総合問題）に沿う」とするか、「（累積和・二分探索・DP など）」と例示の形にする

### 4. 直すとよい｜事実（F2）・分かりやすさ（U3）｜#collections の表の ACL Practice の行、#verify-sets の ACL Practice の箇条

- **問題**：「ACL の機能 1 つにつき 1 問、計 12 問」とあるが、遅延セグメント木は K（Range Affine Range Sum）と L（Lazy Segment Tree）の 2 問で、#verify-sets で挙げる機能は 11 個である。読者が数を合わせようとすると食い違う。また ACL の数学（pow_mod・inv_mod・crt）・modint・z_algorithm などには問題がないので、「機能 1 つにつき」は全機能を覆うように読める
- **根拠**：AtCoder Problems のデータの practice2 の問題名（A〜L）。本文の ACL Practice の表
- **直し方**：「ACL の主な機能を 1 問ずつ（遅延セグメント木は 2 問）、計 12 問」とする。表の行も「ACL の主な機能を 1 問ずつ」にそろえる

### 5. 直すとよい｜事実（F2）｜#collections の表の AtCoder Typical Contest 001・002 の行、#verify-sets の同じ箇条

- **問題**：レベルの目安を「基本の確かめ」とし、#verify-sets でも「基本のアルゴリズムを入出力の素直な形で問う」とするが、atc002 C（最適二分探索木）は N が 10^5 までで、満点には Hu-Tucker（または Garsia–Wachs）の O(N log N) が要る。基本の確かめに使うと詰まる
- **根拠**：ei1333 のライブラリの Hu-Tucker のページ（https://ei1333.github.io/luzhiled/snippets/dp/hu-tucker.html、atc002_c で検証、O(N log N)）。洛谷の写し（https://www.luogu.com.cn/problem/AT_atc002_c、n ≤ 100000、部分点 n ≤ 100・n ≤ 3000）。atcoder.jp は開いていない
- **直し方**：表を「基本の確かめ（atc002 C の満点は発展）」とし、#verify-sets も「…など、基本のアルゴリズムを問う（atc002 C の最適二分探索木は満点が難しい）」と断る

### 6. 直すとよい｜分かりやすさ（U3）｜#practice-contests の ADT の中央値の表

- **問題**：A・B の中央値 12・13 は、AtCoder Problems の difficulty の生の値（400 未満では負にもなる）ではなく、表示用に 400 未満を補正した値である（補正した値で中央値を取ると本文の値に一致した）。断りがないと、自分で JSON を見た読者や、ほかのページの diff と見比べる読者が戸惑う
- **根拠**：problem-models.json の difficulty に 400 未満の補正（400 / exp(1 − d/400)）をかけて再計算した結果が本文と一致
- **直し方**：表の前の文に「（400 未満は AtCoder Problems の表示と同じく補正した値）」を足す。教材全体の diff の扱いと同じなら、その決まりへのリンクでもよい

### 7. 直すとよい｜事実（F2）｜#practice-contests の AWC の箇条

- **問題**：「問題は新しく作られたもので」は、AtCoder Problems のデータで問題 ID が awcNNNN_x で過去の問題を指さないことからの推測で、一次資料で確かめられていない（執筆者の報告にも出典がない）。ADT の問題 ID は abc・codequeen を指すので推測としては妥当だが、言い切りになっている
- **根拠**：contest-problem.json で awc の 930 問はどれも awc の ID（ADT は abc 30174・codequeen 122）
- **直し方**：「問題は AWC のために用意されたもので（AtCoder Problems のデータでは過去の問題を使い回していない）」のように、確かめた範囲を添える

### 8. 直すとよい｜分かりやすさ（U3）｜#collections の表の「レベルの目安」（鉄則本・ACL Practice）

- **問題**：鉄則本は「基礎〜水が中心」とするが、表に出るページの帯は基礎 3・水 4・青 1・黄 3 で、黄のページ（最大流・二部マッチング・燃やす埋める）が 3 割近い。ACL Practice は「（基礎〜黄）」とするが、発展のページも 1 つある。帯の数え方（問題の難しさでなく載せたページの帯）は前の段落で断っているので誤りではないが、数と合わない
- **根拠**：本文の各問題集の表のリンク先の front matter の level を数えた結果（冒頭の「確かめたもの」）
- **直し方**：鉄則本は「基礎〜水が多い。最大流・二部マッチング・燃やす埋めるなど黄のページの練習も入る」とする。ACL Practice は「基礎〜発展」か「水〜黄が多い」とする

## 執筆者の未解決の点について

- NDPC・AAL・組合せゲーム 24 題の難しさの目安を書かないこと：本文では「本文ではまだ使っていない」とだけあり、根拠のない推測を書いていないので、このままでよい
- ADT・AWC が Unrated であること：データの rate_change が全回「-」であることを確かめた。本文は「AtCoder Problems のデータでは」と確かめた範囲を断っているので、このままでよい。MEDIUM・HARD の終わり 2026-02-05 もデータの最後の回と一致した（「まであった」はデータに基づく書き方で問題ない）
- 鉄則本の B・C の意味：README には「節末問題・力試し問題の解答」とあるが、B・C との対応は書かれていない。本文に書かない判断でよい
- NoviSteps のグレードと ABC の位置の対応を書かないこと：About にも対応表はなく、書かない判断でよい
- EDPC・TDPC・鉄則本のレベルの目安：検証役が数え直した level の分布は執筆者の値と一致した（鉄則本の書き方は指摘 8）

## 総合の判定

小さな直しで可。直すべき指摘は 2 件（指摘 1・2。どちらも数語の直し）、直すとよい指摘は 6 件。問題数・日付・difficulty の中央値など、データから出した数はすべて再集計と一致した。
