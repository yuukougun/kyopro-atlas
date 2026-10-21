# subset-enumeration-dp の検証（b2）

- 対象：docs/dp/subset-enumeration-dp.md、snippets/subset-enumeration-dp/{grouping,partition-count,k-groups}.{cpp,yaml}、docs/img/subset-enumeration-dp/three-states.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page subset-enumeration-dp`：エラー 0・警告 0（リンク先の anchor bit-operations#submask・bit-dp#subsets-as-integers・counting-dedup#min-index・recursive-enumeration#partition・bell-number#vs-subset-dp も実在を grep で確認）
- `python3 tools/check_snippets.py -v snippets/subset-enumeration-dp`：grouping 5 case・k-groups 6 case・partition-count 5 case すべて一致
- サニタイザ（`-O1 -fsanitize=address,undefined`）付きで、partition-count を n = 0〜10 のすべて、grouping を乱数の n = 5・7・8（n ≤ 8 は素朴な全列挙との assert が走る）、k-groups を n = 6・7・8 × k = 1・2・3・5・8（n ≤ 8 は全列挙との assert）で実行し、異常なし・assert 通過。k > n では -1 を出す
- 数値（手計算と Python）：表の 2^N N・3^N・4^N（N = 14・16・18・20）すべて正しい。B_16 = 10480142147 ≈ 10^10。B_3 = 5、順序付きの分け方 13。Σ_{S≠∅} 2^{|S|−1} = (3^N − 1)/2。確認問題の 3^15 − 2^15 = 14316139 ≈ 1.4×10^7、(3^15 − 1)/2 = 7174453 ≈ 7.2×10^6。3^16/2 ≈ 2.2×10^7。19 × 2^18 × 8 byte ≈ 39.8 MB（「約 40 MB」）。O(3^N N^2) は N = 16 で 1.1×10^10
- 主張：(T − 1) & S の列挙順と止め方、S ∖ T < S（昇順でよい）、配る DP も 3^N、最小（最大）の要素を固定すると分け方が 1 通りの順になること、順序の重複が組の数で違うので割って直せないこと（k 個の組は k! 回）、j の次元を外せないこと、ゼータ変換で足りる確認問題。どれも正しい
- 例題・練習・力試し：`python3 tools/ap.py show` で 6 問（dp_u・abc187_f 1895・abc310_d 1368・typical90_as・abc321_g 2439・abc332_e 1883）の実在・題名・diff を確認。本文の label と diff は台帳と一致
- evidence の確認：Series_205（EDPC U、dp_S の最大・(T−1)&S・Σ 2^k C(N,k) = 3^N）、drken ABC187 F（N ≤ 18、クリークの前計算、配る形の 3^N、補グラフの彩色数）、drken ABC321 G（N ≤ 17、最小の頂点を含む成分で f(S) = g(S) − Σ f(T) g(S∖T)、O(3^N)）、E869120 sol/045.cpp（dp[i][S]＝ちょうど i 個の非空グループ、遷移 min max(dp[i−1][S∖T], cost[T])、距離は 2 乗のまま）、rareshana ABC332 E（空の袋を重さ 0 の袋とし、巨大値で初期化しない）。本文の方針・解法の詳細と食い違いなし
- 参考の 6 つの URL：check_noai で noai の指定なし。題名・著者は書かれたとおり（drken ABC310 D の「参考にした点」は指摘 5）
- 図：S = 1101・g = 0101 で要素 0・2 が g、3 が残り、1 が外。代替テキストと一致。白背景・viewBox あり・font-family="sans-serif"・相対パス。360px でも文字は読め、重なり・はみ出しなし。色だけでなく「残り・g・外」の文字と破線で区別している。（720px の PNG は下端が切れて出たが、viewBox 480×330 を 1.5 倍した高さに撮影の枠が足りないためで、360px の PNG では全体が出ている。図の問題ではない）
- catalog の visual（static・priority 2）は「(T−1)&S の列挙の様子」と「3 状態」の 2 つを挙げるが、前者は bit-operations#submask の図に任せてリンクしている。重ねて描かない判断で問題なし
- F8：出典の文と並べたが、文の並び・例の数値は本文独自（EDPC U の例の数値は使っていない）

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2 | #vs-zeta の 3 段落目「グループの数の最小（グラフの彩色数など）は、包除原理と高速ゼータ変換で O(2^N N) にできる」 | 条件の書き落とし。包除原理の方法は「k 個の許される集合で全体を覆えるか」を数えるので、覆う最小と分ける最小が一致するのは、許される集合の部分集合もまた許される（独立集合・クリークのように下に閉じている）ときだけ。一般の「グループの数の最小」では成り立たない | 反例：N = 3、許される集合が {0,1} と {1,2} だけ。2 個で覆えるが、分け切る方法はない（DP の答えは「分けられない」） | 「グループの条件が部分集合でも保たれる（独立集合・クリークのように）とき、グループの数の最小は包除原理と高速ゼータ変換で O(2^N N) にできる（彩色数）」と条件を足す |
| 2 | 直すとよい | fact F2 | #vs-zeta の箇条書き 2 つ目「T ごとに組を作って試すしかなく、O(3^N) になる」 | 2 段落後で「部分集合の畳み込みで O(2^N N^2) にできる」と書いており、「試すしかない」は言い過ぎで前後が食い違って読める | 同じ節の 3 段落目 | 「素直には T ごとに組を作って試すことになり、O(3^N) になる（速くする道具は下に述べる）」とする |
| 3 | 直すとよい | fact F1 | #pitfalls「グループの値を遷移の中で数え直す」 | 「O(N) や O(N^2) かけて求めると、全体が O(3^N N^2) になる」は、O(N) のときは O(3^N N) で、数式が合わない | 回数 × 1 回の手間 | 「全体が O(3^N N)〜O(3^N N^2) になる」とする |
| 4 | 直すとよい | figure G5・clarity U3 | three-states.svg と #why-3n の本文 | 図と代替テキストはグループを g と書くが、#why-3n の本文と式はずっと T（組 (S, T)）を使う。同じ節で記号が変わり、読者が別物かと止まる（g はコード片の変数名） | 本文 71・75 行と図のラベル | 図のラベル・代替テキストを T にそろえる（コードの g は本文 100 行の説明のとおり t ∪ {v} として残してよい） |
| 5 | 直すとよい | fact F9 | #references の drken「ABC 310 D」の「参考にした点」 | 「最小番号の人から組を決める全列挙」とあるが、記事の全列挙は「番号順に 1 人ずつ、既存の組に入れるか新しい組を末尾に作るか」を選ぶ形。本文の「最小番号の人から入るチームを決める」（recursive-enumeration#partition の形）と同値だが、記事の説明とは違う | 記事を確認（WebFetch） | 「1 人ずつ既存の組か新しい組に入れる全列挙（組の並びの重複を防ぐ）」とする |
| 6 | 直すとよい | code C2 | #fix-minimum「`fixed` が … に一致することを N ≤ 10 で確かめている」と partition-count.yaml | cases は n = 0・1・3・4・10 だけで、n = 2・5〜9 は試していない（assert は与えた n でだけ走る）。私の手元では n = 0〜10 すべて一致したので内容は正しいが、記述と cases がずれる | 手で n = 0〜10 を実行して一致を確認 | cases に n = 2・5・6・7・8・9 を足す（どれも一瞬）か、本文を「N = 0, 1, 3, 4, 10 で」とする。前者を勧める |
| 7 | 直すとよい | fact F2 | #vs-zeta 3 段落目「dp[S] = Σ_T f(T) dp[S∖T] の形の数え上げは … 部分集合の畳み込みで O(2^N N^2)」（執筆者の未解決の点 2） | 結論は正しいが、右辺に dp 自身が出てくるので 1 回の畳み込みでは済まず、要素数の小さい順に層ごとに求める必要がある。そのまま読むと「f と dp を畳み込む」と誤解しうる。出典もない | 要素数 k の層の dp は k 未満の層のゼータ変換だけから決まり、層ごとのメビウス変換 O(2^N N) × N 層で O(2^N N^2) | 「右辺の dp を要素数の小さい順に層ごとに求める部分集合の畳み込みで」と一言足す。出典は持ち主の節ができたらリンクに替える（執筆者の案どおり） |

## 執筆者の未解決の点について

- 典型90 045 の N の上限：解答コードからは読めない（WebFetch の要約も同じ）。本文は上限を書かず、方針の O(K 3^N) だけを述べているので現状で問題なし。「2 乗のまま比べてよい」は sol/045.cpp が 2 乗のまま比べていることで確認できた
- 部分集合の畳み込みの記述：指摘 7。正しさは確認した
- counting-labeled-graphs・chromatic-number（stub）へのリンク：今の形でリンク切れなし。相手が draft になったらメインが張り替える
- bit-operations:146・178 のリンクの張り替え：#why-3n・#submask-loop は本文にあり、張り替えてよい（メインの作業）

## 台帳への提案

- dp_u・abc187_f・typical90_as・abc321_g｜checked｜2026-10-21｜検証役も evidence で問いと方針を確認した（執筆者の提案に同意）
- typical90_as｜evidence に https://github.com/E869120/kyopro_educational_90/blob/main/sol/045.cpp を足す（執筆者の提案に同意。状態と遷移を確認できた）
- abc310_d の subset-enumeration-dp の approach：執筆者の提案の文で問題なし（3^N の方針は本ページの自前の説明で、全列挙の記事と矛盾しない）

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 6）。指摘 1 は条件を 1 句足せば済む。
