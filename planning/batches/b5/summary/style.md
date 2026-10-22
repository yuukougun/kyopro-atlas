# b4・b5 の手引き・prh.yml・checklists への提案

出どころは b4・b5 の各 `<id>.md` の「手引きへの提案」「手引き・front matter・catalog への提案」の手引きの部分と、検証の後の追記。「ページ数」は同じ趣旨を出したページの数。道具（gen_site・check_pages など）そのものの直しは other.md §3 にも置いた。§7 は b1・b3 の決定と手引き §13〜§15 ですでに決まっているもの。

## 1. 食い違い・決めてほしいこと（複数のページから）

| 要旨 | ページ数 | 出したページ |
| --- | --- | --- |
| **発展の概要の「学ぶための資料」を定型の節にする**：`## 学ぶための資料 {#resources}` を sections に載せない定型の見出しとして §13-1 の一覧に足す（hld が先に使った形）。§4 の overview の構成にある「学ぶための資料」に見出しと anchor が決まっていない。なお dilworth-path-cover・parallel-binary-search は独立の節にせず、参考の各行に「（学ぶための資料）」と添えた（揺れ） | 11（ほかに同じ見出しを使っただけのページ 3） | cdq-divide-and-conquer・cht・generating-function-counting・fps-basics・general-matching・lgv-lemma・segment-tree-beats・segment-tree-graph・slope-trick・stirling-first・young-tableaux（使っただけ：dynamic-tree・modular-shortest-path・alien-dp） |
| **発展の概要の「ライブラリでの使い方」の見出しと anchor**：中身の節として `{#library}`（「計算量と自作するときの要点」「自作ライブラリでの扱い」など）を足す形が揺れている。anchor を library にそろえる・sections に足してよいと明記する。ACL も Library Checker も対応がない手法では「自作するときの要点」の節で代えてよいと明記する。auxiliary-tree は `usage`（wavelet-matrix も usage）を足した | 7 | alien-dp・lgv-lemma・young-tableaux・binomial-prefix-sum・auxiliary-tree・modular-shortest-path・slope-trick |
| **ACL に対応がない発展の概要の「ライブラリでの使い方」の中身**：公開ライブラリ（ei1333）の関数名と返り値を文章で書く（k-shortest-paths）か、自作の関数の取り込み（コールバックを受け取る形。parallel-binary-search）か。扱いをそろえる | 2 | k-shortest-paths・parallel-binary-search |
| **Library Checker に対応する問題がない手法の書き方を §13-10 に足す**：「専用の問題はなく、部品（LCA など）の問題で検証する」「対応する問題はない。全列挙・愚直な方法と照らし合わせて確かめる（日付）」「近い問題が解けない理由を一言（完全永続の Persistent UnionFind など）」「FPS の問題（Inv・Exp）を漸化式に直して確かめる」 | 6 | auxiliary-tree・burnside-lemma・partially-persistent-union-find・segment-tree-graph・slope-trick・online-convolution |
| **例題・ABC の練習が 0 問の発展の概要の構成**：`## 例題` を置かない（multiplicative-function は k-shortest-paths にならった）、`## 練習問題 {#practice}` に「ABC で必須になる問題は確認できなかった」の 1 文＋ Library Checker の小見出しだけ（spanning-tree-advanced）を、§4 か §13-10・§15-5 の例として書く | 2 | multiplicative-function・spanning-tree-advanced |
| **§15-5 を Library Checker 以外のジャッジに広げるか**：CSES の小見出しを立てた（tree-isomorphism）、AOJ DPL_5 を練習の節にふつうのリンクで置きたい（twelvefold-way。onlinejudge.u-aizu.ac.jp は noai 指定なし）、yukicoder の問題を候補に挙げた（k-shortest-paths。規約は未確認） | 3 | tree-isomorphism・twelvefold-way・k-shortest-paths |
| **pattern の表の「代表の問題」の列の書き方**：(a) 行き先のページの問題の label を文字だけで書き、リンクは行き先の囲みに任せる（grid・permutation。bracket-sequence の形）、(b) label の一部を行き先のページの例題の anchor（`../ds/global-offset.md#abc212_d`）か `#practice` へのリンクにする（operation-sequence・kth-and-median）、(c) 表の後にそのページの anchor へリンクする（mex）、(d) 表に列を置かず各節の本文で「代表は［ABC147 D］(…#abc147_d)」と書く（xor）。divisors-and-multiples は他ページの例題を label で書いてよいかの決まりを求めた。検証役の指摘でも grid・operation-sequence は判断をメインに回した（atcoder.jp へのリンクは問題の囲みだけ、は全員守っている） | 7 | grid・operation-sequence・kth-and-median・mex・xor・divisors-and-multiples・permutation |
| **hub の表の例題の列**：相手のページの例題の小見出し（`../dp/cht.md#dp_z` など）か `#practice` へリンクする形を hub の書き方の例として足す（dp-speedup-overview）。台帳の pages に graph-modeling を持たない問題も相手のページの例題へのリンクとして出し、hub の問題数の目安（0〜3）は自分の囲みの問題だけを数えると解釈した（graph-modeling）。この解釈を §4 か §10 に書く | 2 | dp-speedup-overview・graph-modeling |
| **pattern の sections に overview（問われ方と手法の一覧）を骨格から入れる**：見本の bracket-sequence は持つが、骨格の permutation・subsequence-and-substring・grid などにはなく執筆者が足した。§4 の pattern の構成に明記する | 3 | grid・permutation・subsequence-and-substring |
| **guide（案内）のページの構成の目安が §4 にない**：debugging-checklist は「要点 → 別名 → 導入（略語の説明と分岐図）→ 症状ごとの節（太字の見出し語つきの箇条書き、末尾に持ち主の節へのリンク）→ 確認問題 → 参考」、method-comparison は「guide の比較のページは hub に準じ、節ごとに『状況 → 使う手法 → 計算量 → ページ』の表と、組の見分け方を 2〜4 文」、thinking-checklist は「表で決まらないときに順にたどる問いの列」を置いてよいこと（guide で hub の形を取るページの扱いも）。stress-testing は要点の 3 行目に「考察に使うなら」を置き、項目名の約束を決めてほしいとした | 4 | debugging-checklist・method-comparison・thinking-checklist・stress-testing |
| **生成ブロックを持つ guide のページの見出し**：sections の見出し `## … {#anchor}` を生成ブロックの外の直前に手で置き、ブロックの中は `###` から始める、を §2.1 か §4・§13 に書く（骨格に見出しがなかった） | 2 | roadmap・term-index |
| **guide・hub・pattern の complexity**：計算量のないページは complexity を null のままにする、と §2.1 か §4 に書く（指示は「complexity を埋め」だった。thinking-checklist も検証の指摘で null に戻した） | 2 | cpp-reverse-index・thinking-checklist |
| **データから計算した数字の再現**：横断の guide のページが計算で出した数字（早見表の数の目安・contest-strategy の確率と時刻）のスクリプトを tools/ に置くか決める（今は scratchpad の nums.py・pi.cpp など） | 2 | cheatsheet・contest-strategy |
| **§15-11（手元で数えた値）の範囲**：手元の実験の値（FFT の誤差の大きさなど。条件のコンパイラ・実装を添えた）、横断ページの地図・集計の数（分野をまたぐ前提の本数など。日付と「データから数えた値」を添える）も含めてよいか | 2 | fft-ntt・knowledge-map |
| **他者の記事の題名の textlint エラー**：全角と半角の間に空白のない題名（「行列で理解するFFT」「第N項」）が ja-space-between-half-and-full-width のエラーになる。出典の題名は原文（h1）のまま書く規則（§14-24）なので、(a) 題名をリンクの文字にする（検査から外れる。fft-ntt）、(b) textlint-disable で囲む（linear-recurrence-fast はその規則だけを外した）のどちらかに決める。固有名「AtCoder生成AI対策ルール」も同じで、prh.yml か .textlintrc の allows に足せば各ページで disable を使わずに済む（contest-strategy）。§14-25 は警告なら残してよいとしているが、これはエラー | 4 | fft-ntt・hadamard-transform・linear-recurrence-fast・contest-strategy |
| **表記の揺れを例として本文に出すページ**：索引・用語集・prh の説明の箇所を `<!-- textlint-disable prh -->`〜`<!-- textlint-enable prh -->` で囲んでよい、と §14-25 に足す（glossary も canonical-forms の節全体を外した） | 2 | term-index・glossary |

## 2. 手引きの節ごとの提案

### §2（必ず守ること）

- §2.2：guide のページの要点の項目は hub・pattern と同じく自由に決めてよいことを明記する（practice-method。§2.2 にすでに「guide・start・patterns・hub は項目を内容に合わせて変えてよい」とあるので文言の確認だけ。§7 参照）
- §2.7：bash の短いコマンド（`oj g/i --hack-actual …` の 1 行など）を本文に直接書いてよいかを明記する。research §6.7 の方針（スクリプト全体は載せず処理の流れだけ）に従い、3 つのプログラムを回す形は ```` ```text ```` の流れにした。interactive#local-testing も bash を載せている（stress-testing）

### §4（type ごとの構成）

- overview で「サイン」を節にするとき骨格の sections にない中身の節（signs）を足すことになった。overview の骨格に「式の形から選ぶ」節を標準で置くか、要点の囲みのサインで済ませてよいかを書く（fps-basics）
- 骨格の sections に `examples` の中身の節があり、定型の `## 例題 {#examples}` と anchor がぶつかった。title を「例題：…」に変えて例題の節として使い、定型の見出しは置かなかった。sections に定型の anchor（examples・practice・quiz など）を持つ骨格がほかにないか、catalog と骨格で確かめる（generating-function-counting）
- pattern で表の行が多い（16 行）ときは型ごとに表を分けてよい（interval は太字の 1 行の見出し＋表 3 つにした。小見出し ### は sections に載らないので使わなかった）
- pattern で related が多い（operation-sequence は 18）ときは、表の行を related の全部ではなく型ごとに 1 行にまとめ、残りは節の本文でリンクする形でよい（operation-sequence）
- pattern で「節の中の小さな表」（数え上げの条件の形 → 手法 → ページ）を使ってよいか（permutation）
- 問題 0 の pattern の表の「代表の問題」の列は、行き先のページの例題の小見出しか `#practice` へのリンクで書いた（§2.5 の「例題の見出しかページへリンク」に従った）。問題 0 のページの書き方として §4 の pattern に一言（kth-and-median。§1 の代表の問題の件と同じ論点）
- 横断ページ（guide）で色変記事などの個人の体験を引くときの書き方：「氏名（入水・入黄などの時期の区別）＋要旨を自分の言葉で」とし、一人の声を一般化しないよう異論も並べた（practice-method）
- guide の参考の節で自サイトのページを「数値の確かめ先」として挙げた。参考を外部の資料だけに限るなら消してよい（debugging-checklist）
- 発展の概要で AtCoder の公式解説が主な資料のとき（ABC351 G の Static Top Tree）は、「学ぶための資料」に名前だけ書き、リンクしない書き方にした。この扱いでよいか（static-top-tree）
- 発展の概要に確認問題を置くときも `## 確認問題 {#quiz}` にまとめた（generating-function-counting。§14-11 のとおりで確認だけ）
- 概要のページでも、汎用のコード片 1 つと問題ごとの載せ方の言い換えで済ませる形がよかった（頂点が「ない」時刻が 1 点なら辺を 3 区間に分ける。offline-dynamic-connectivity。記録として）

### §5（分野ごとの書き方。事実の注意と持ち主）

担当が本文で確かめたと報告したもの。§15 の「そのほか」と同じく、正しさを確かめたものだけを 1 行ずつ足す。

| 分野 | 注意の要旨 | 持ち主（提案） | 出したページ |
| --- | --- | --- | --- |
| geometry | 凸多角形の辺のベクトルを外積の符号で比べてマージするとき（ミンコフスキー和）は、どちらの列も最も下（同じ高さなら最も左）の頂点から始める（向きの差が 180 度未満に収まる）。回転キャリパーは一直線上の点を除いた凸包で行う（convex-hull#degenerate） | advanced-geometry | advanced-geometry |
| geometry・cpp | `-march=native`（AtCoder）では FMA で小数の式の結果が変わりうる。小数の外積の符号・`== 0` に頼らない | cpp-environment#march-native | cpp-environment |
| dp | Alien DP で同点の個数があるときは、罰金つきの問題で個数の少ない方を選ぶと決め、cnt(λ) ≤ K となる最小の整数 λ で g(λ) + λK を答える（返った個数ではなく K を掛ける）。値しか返せないなら h(λ) = g(λ) + λK を整数の三分探索で最小にする | alien-dp#binary-search-lambda | alien-dp |
| graph（共通） | mod の値の 0 を存在の判定に使わない（彩色数の包除で正の値の余りが 0 になると塗れないと誤判定する。法を 2 つ使うか乱択する。LGV・行列式でも同じ） | chromatic-number#chromatic-number | chromatic-number・lgv-lemma |
| graph | 頂点を共有してよい鎖での被覆は、推移閉包を取ってから頂点を共有しないパス被覆にする。覆わなくてよい頂点を通過できる場合も同じ（0→1→2 で 0 と 2 だけを覆うなら閉包なしでは 2 本と誤る） | dilworth-path-cover#antichain | dilworth-path-cover |
| graph | 下限付きの流れの最大化で t→s の大きな辺を残したまま flow(s, t) を呼ぶと、その逆辺を通ってすでに流れた量も返るので、返り値がそのまま合計の流量になる。下限付きの最小費用流では負のコストの辺も先に流したことにして非負に直せる | flow-lower-bounds#super-vertex | flow-lower-bounds |
| graph | BEST 定理の数は辺を区別し 1 本目の辺を固定した数（巡回シフトを同一視）。s ≠ t のオイラー路は辺 t→s を足して 1 本目に固定、始点だけ決まった閉路は ec × deg⁺(s)。同じ種類の辺は最後に個数の階乗で割る（c! で割れるのは始点を決めた列の数に限る）。(deg⁺(v) − 1)! の出次数には自己ループを数え、行列木定理の行列には入れない | matrix-tree-theorem#best-theorem | matrix-tree-theorem |
| graph | 最小シュタイナー木の DP の重みは 0 以上が前提（木にできることとダイクストラ法の両方に要る）。重み 0 の辺は復元で 2 回出ることがあるので印で除く | steiner-tree#library | steiner-tree |
| graph | 2-SAT の復元は「トポロジカル順で後ろの成分にある方を真」。Tarjan 法は成分を逆トポロジカル順に見つけるので、自作では番号の向きを確かめる | two-sat#acl | two-sat |
| math | 行列式の掃き出しではピボットの行を割らない（割るなら値を掛け戻す）。素数でない法は互除法の掃き出し | determinant#modulus | determinant |
| math | XOR の逆変換（アダマール変換）は 2^n で割るので偶数の法（2^64 など）では使えない。AND・OR（ゼータ変換）は足し算だけなので使える（zeta-mobius-subset#vs-xor にも同じ趣旨） | hadamard-transform#index-operations | hadamard-transform |
| math | 64 bit の法の掛け算の持ち主は mod-pow（`__int128`）、Montgomery・Barrett と Miller-Rabin の底の注意は miller-rabin#mulmod・#deterministic-bases と書き分ける（§15-12 に足す形。b3 handoff §3 の mulmod の項が閉じる） | mod-pow・miller-rabin | miller-rabin |
| comb | 連続値の期待値を double で区分ごとに積分するときは t = x + u と原点を区分の左端へ移してから [0, 1] で積分する（x^{d+1} の差は桁落ちする） | continuous-probability#library | continuous-probability |
| comb | LGV 補題で数えるのは頂点を共有しない経路の組の「置換の符号付きの和」。交わらない組が恒等置換でしか作れないように始点・終点の番号を付けてから行列式を取る（逆にすると符号が反転する） | lgv-lemma | lgv-lemma |
| comb | 非不偏ゲームの値は double で持たず、分母を固定した整数で持つ。max L ≥ min R の局面は数にならないので assert で確かめる | partizan-games | partizan-games |
| comb | 符号なし c(n,k) と符号付き s(n,k) = (−1)^(n−k) c(n,k)。Library Checker は符号付き（fps-basics・generating-function-counting でも同じ誤りが起きうる） | stirling-first | stirling-first |
| comb | p(n,k) は partition-number・twelvefold-way とも「部分が k 以下（＝k 個以下）」に統一。ちょうど k 個は p(n−k,k)（b3 handoff §2 の申し送りの決着） | partition-number・twelvefold-way | twelvefold-way |
| comb | 群・環・体の語を使わない規則（§5 math）を comb にも当てる（burnside-lemma は操作の集合の条件（合成・恒等・逆）を言葉で書いた）。comb にも明記するか | — | burnside-lemma |
| tree | 木の同型・木のハッシュで、子の名前は整列した列（多重集合）として扱い、名前の表は比べる木すべてで共有する。根のない木は中心（または重心）を根にし、2 個なら両方を試すか辺に仮の頂点を足す（tree-centroid#one-or-two とそろえた） | tree-isomorphism#unrooted | tree-isomorphism |
| tree・basics | 木の制約つきの交換論法（01 on Tree）では (0, 0) の塊は比較が推移しないので最優先でまとめる（比の最大の塊を選ぶ議論で常に最大の条件を満たすので正しさも崩れない。exchange-argument#ratios の「(0, 0) は除く」の木の版） | tree-ratio-greedy#why-ratio | tree-ratio-greedy |
| ds | 取り消しの間に値を加える問題では、根の合計を「元の値を書き戻す」方式で戻すと加えた値が消える。各頂点に下の合計を持たせ、加算は v から根までの経路すべてに足し、取り消しは引き算にする。同じ成分どうしの併合（a = b）の記録を取り消すときは sum を引かない（引くと 0 に消える） | rollback-union-find#offline-dynamic-connectivity | rollback-union-find |
| cpp | 関数の中の大きな配列は、AtCoder では呼ぶたびに 0 で埋められて遅い（-ftrivial-auto-var-init=zero）。作業用の配列はグローバルか使い回し | cpp-environment#auto-var-init | cpp-environment |
| basics・ds | mex の印の配列は大きさ N + 1（答えが N になりうる）、N より大きい値は読み飛ばす（grundy-number#pitfalls・interval-set・ordered-set でも同じ注意） | patterns/mex#pitfalls | mex |
| basics | 「計算量の目安の数値は complexity-estimation の値にそろえる」に、reverse-index-constraints#magnitudes も同じ値だと添える | complexity-estimation | reverse-index-constraints |

### §6（記法）

- 行列をセグメント木に載せるページの向き（横ベクトル・(p, q) は p → q・op(a, b) = ab）を足す。matrix-power は縦ベクトルのまま（累乗では答えに影響しない）。木の上の動的 DP は縦ベクトルの方が番号の順に積が並ぶので、static-top-tree と dynamic-dp#on-trees の書き方をそろえる（dynamic-dp。notation は「各ページの冒頭で示す」とした。handoff.md §3）
- (min,+)・(max,+) は全角の括弧に入れず半角の `(min,+)` で書く（monge）
- notation の執筆者の案：「log の底は書かないが、回数の見積もりでは底 2 で数える」「2 文字以上の名前は `\mathrm`（dp だけでなく cnt・val・dist なども）」「表の値は角括弧 $\mathrm{dist}[v]$、式で決まる値は丸括弧 $\mathrm{lca}(u, v)$」「popcount は `\operatorname{popcount}`」「具体的な文字列は本文で `abc`、数式の中で `\texttt{abc}`」「量の単位は数と単位の間に空白、メモリ制限は MiB」。§6 の「木」の行に ord[t]・ST(v)・EN(v)、「確率」の行に P(A ∣ B)・\overline{A}・V[X]、「整数」の行に Iverson の記法 [P] と [x^n] f を足す
- 「128bit」と「128 bit」の揺れ（検証役の数えで 10 対 9）を「128 bit」にそろえる（stern-brocot。prh.yml でも）
- 整数論の案内の記法「1 つの数 N、値の上限 M」（harmonic-sum の M に合わせる）を notation に（divisors-and-multiples。notation は「決まった文字を当てない」とした。handoff.md §3）
- 表の中の疑問文（？で終わる「試す問い」の列）を許すことを §6 か §7 に書く（thinking-checklist）
- 表のセルのコードに `|` を含めるときは `\|` にしない（python-markdown の tables 拡張ではバッククォートの中の `|` は区切りとみなされず、`\|` と書くと逆斜線がそのまま出る。`v | views::reverse` で確かめた）。§6 の「表の中では `\lvert … \rvert`・`\mid`」は数式の話なので、コードについて 1 行足す（cpp-reverse-index）

### §7（用語とリンク）・§15 関連

- 早見表の数値は各ページの値と食い違いやすい。早見表に値を書いたページ（complexity-estimation・divisor-count-bound・gcd-lcm・cpp-types-literals・cpp-math-functions・stl-containers・mod-arithmetic）を直すときは早見表の同じ行も直す、と §7 か §15 に一言（cheatsheet）
- 逆引き辞典の見分け方の表（手書き）はページの signs とずれうる。ページの signs を直すときにこの節の表も見直す決まりを §15 に置く（reverse-index-signs）
- 用語集の canonical-forms を prh.yml の元にするなら、prh.yml を直したときに対応表も直す手順を §7 か progress.md に書く（今は手で写した）。prh の expected（「尺取り」「貪欲」）と付録 A の形（尺取り法・貪欲法）のどちらを表の正とするかを §7 に一言（glossary）

### §8（図）

提案なし（各ページは §15-8 に従って 360px・720px で確かめた）

### §9（コード片）

- 「std の名前と同じ関数名を作らない」の例に `merge`（`std::merge`）を足す。treap・マージテク・Union-Find の自作で出やすい（balanced-bst は `join` と名付けた）。`print`（C++23 の std::print）も残っている（hadamard-transform。直しの対象は handoff.md §6）
- ライブラリの形のコード片（ヘッダに置く想定の部分）は名前空間に入れ、中では `std::` を付ける、という例外を書く（library-design の snippets は `namespace mylib` の中で `std::vector`、`main` の側は `using namespace std;`）
- `#pragma once` を main のファイルに書くと GCC が警告を出すので、ヘッダの形はコード片に入れられない（library-design は `// #pragma once` のコメントにし、本文で説明した）。同じ悩みのページがあれば手引きに足す
- 乱数の種と同じ列：`mt19937_64` の値は規格で決まるが、`uniform_int_distribution` を通した値は標準ライブラリで変わりうる（cpp-math-functions#random と同じ注意）。期待値を観測値にしたコード片には「標準ライブラリが同じときに限る」と添える（stress-testing）
- 箇条書きの句点（§15-2）を付ける機械的な置き換えは front matter の `- {title: …}` の行にも当たるので注意（xor が一度壊して直した。手順の注意として）

### §10・§11（問題・出典）

- 付録 B の github.com の扱いに、library-checker-problems の issue・PR を出典にしてよいことを明記する（segment-tree-beats は issue #1369 を参考に入れた）
- 発展の概要の「学ぶための資料」で記事の題名を出すとき、題名をリンクの文字にすれば textlint の検査から外れる（§1 の textlint の件と同じ）

### 付録・そのほか

- 「1 秒あたりの演算回数」の手元の実測（ops-per-second の表）を、ほかのページで定数倍を書くときの共通の値として付録に置く。測定：g++-15（15.2）・`-std=gnu++23 -O2`、Intel Core i7-13700・WSL2。依存のある掛け算と足し算 10^8 回 0.08 秒、32 MiB の配列を順に読む 10^8 回 0.03 秒、乱数の位置で読む 10^8 回 0.44〜0.51 秒、set の挿入と lower_bound 各 10^6 回 0.34 秒（3 回ずつ）。依存のある乱数の読み出しは 10^8 回で約 7 秒（本文には載せていない）（reverse-index-constraints）
- 数の目安を再計算するスクリプトを tools/ に置く案（research 00 §4.1 の提案。cheatsheet。§1 のデータの再現の件と同じ）

## 3. 付録 A（用語の正規形）への追加の案

| 分野 | 足す語 | 出したページ |
| --- | --- | --- |
| 全体 | Rated・パフォーマンス・レーティング（レート）・色・ARC--・ARC++（2025 年までの区分は「Div. 1」「Div. 2」と空白入り。調査 00 の「Div.2」と揺れ） | atcoder-system |
| 全体 | 複数テストケース（多重テストケースは使わない。本文は complexity-estimation の節名を含めそろっている） | glossary |
| データ構造 | DSU の扱い：別の書き方には入れず、ACL の `dsu` を指すときだけコードの名前として使う（DSU on Tree はマージテクの別名）。決まったら用語集の対応表のデータ構造の表の下に注記 | glossary |
| データ構造 | 併合可能なヒープ（「併合できるヒープ」と揺れている。prh でも） | advanced-ds-catalog |
| データ構造 | Link-Cut Tree（LCT）・Euler Tour Tree（ETT）・Top Tree・expose・evert | dynamic-tree |
| データ構造・木 | Static Top Tree の操作名「圧縮（compress）・併合（rake）」 | static-top-tree |
| DP | monotone minima・(min,+) 畳み込み | monge |
| グラフ | リテラル・節・含意グラフ（研究ノート 03-graph の用語の一覧にはある） | two-sat |
| 木 | 高さ（深さと区別する） | tree-isomorphism |
| 整数論・代数 | ラグランジュ補間・標本点・組立除法 | lagrange-interpolation |
| 整数論・代数 | 線形漸化式・特性多項式・きたまさ法・Bostan-Mori・Berlekamp-Massey | linear-recurrence-fast |
| 整数論・代数 | 乗法的関数・ディリクレ積・杜教篩・Min_25 篩・Lucy DP（aliases は中国語の「杜教筛」だが本文は mobius-function にならい「杜教篩」） | multiplicative-function |
| 整数論・代数 | Stern-Brocot 木・連分数・中間数・Farey 数列・最良有理近似（gcd-lcm:166 のエンダッシュは handoff.md §6） | stern-brocot |
| 数え上げ | 軌道・Burnside の補題 | burnside-lemma |
| 数え上げ | 標準タブロー・フック長・Young 図形・Robinson-Schensted 対応（RS 対応）。ja.wikipedia は「ヤング盤・標準盤」だが本文は aliases に合わせて「標準タブロー」 | young-tableaux |
| 文字列 | 接尾辞リンク・Lyndon 語・Lyndon 分解・回文木（suffix link・Lyndon word などの別表記を本文で使わない） | suffix-automaton |
| 全体 | ならし計算量（dynamic-tree の summary の「償却」を直す件。付録 A にあるので §7 の解決済み） | dynamic-tree |

## 4. 付録 B（確かめたドメイン）への追加の案

報告で noai・noimageai の指定なしを確かめたとあるもの（b1 の決定どおり、足す前に確かめ直す）：

| ドメイン | 確かめた日・方法 | 出したページ |
| --- | --- | --- |
| soi.ch | 2026-10-22（利用条件の記載なし） | alien-dp |
| robert1003.github.io | 2026-10-22・check_noai | cdq-divide-and-conquer |
| raw.githubusercontent.com | check_noai（chromatic-number）。library-design は check_noai を通さずに使った | chromatic-number・library-design |
| satanic0258.hatenablog.com・smijake3.hatenablog.com・hcpc-hokudai.github.io | 指定なし（hcpc の PDF は読んでいない） | cht |
| ei1333.hateblo.jp | （報告に日付なし） | lagrange-interpolation |
| mzhang2021.github.io | 2026-10-22（規約の記述なし） | merge-process-tree |
| speakerdeck.com | スライドごとに書き手が違う。確かめたのは tatyam_prime の「Monge の手引書」だけ | monge |
| rsm9.hatenablog.com・scrapbox.io の 37zigen-43465887・Atcoder-myReflection | 2026-10-22・check_noai | segment-tree-beats |
| chokudai.hatenablog.com | 2026-10-22・check_noai（検証役）。practice-method の前の報告で「付録 B のドメイン」としたのは誤りだったと訂正 | atcoder-system・practice-method |
| iroha-3856.hatenablog.com・kmyk.github.io | 指定なし | contest-strategy |
| trap.jp | 2026-10-22・check_noai（static-top-tree も evidence に使った） | cpp-environment |
| js.cytoscape.org | 2026-10-22（robots="all"） | knowledge-map |
| competitive-verifier.github.io・online-judge-tools.github.io | 指定なし | library-design |
| onlinejudge.u-aizu.ac.jp | 2026-10-22・check_noai | twelvefold-way |

報告に noai の確認の記載がないまま使われた、または提案された付録 B 外のドメイン（使う前に確かめる）：buyoh.hateblo.jp（parallel-binary-search の evidence 案）・potato167.hatenablog.com（matrix-tree-theorem の evidence 案）・hitonanode.github.io（partizan-games・tree-ratio-greedy）・ebisuke33.hatenablog.com（divisors-and-multiples）・yuulis.hatenablog.com（balanced-bst の候補）・scrapbox.io/konan-compro（grid）・scrapbox.io/pctsnote（burnside-lemma）・koosaga のブログ（韓国語。advanced-ds-catalog）・aruma256.dev（mex。提案者が「未確認、check_noai で確かめてから」と明記）・syllabus.s.isct.ac.jp（partizan-games。参考には入れていない）。cnblogs の mlystdcall 氏の記事は check_noai が時間切れで、資料から外した（cdq-divide-and-conquer）

## 5. prh.yml への提案

| 規則 | 理由 | 出したページ |
| --- | --- | --- |
| ビットリバース → ビット反転 | 本文は「ビット反転の順」で書いた | fft-ntt |
| 杜教筛 → 杜教篩 | 本文で寄せる（別名の行は textlint の外） | multiplicative-function |
| 併合できるヒープ → 併合可能なヒープ | advanced-ds-catalog の見出しに合わせる（spanning-tree-advanced・slope-trick・k-shortest-paths に揺れ） | advanced-ds-catalog・spanning-tree-advanced |
| 128bit → 128 bit | 数字と単位の間に空白（§6 と同じ） | stern-brocot |
| 「包絡線」「Li Chao Tree」（Li-Chao Tree・LiChao の揺れ） | 足すかの検討 | cht |
| 「AtCoder生成AI対策ルール」を固有名として allows に | ja-space-between-half-and-full-width のエラーを避ける（§1） | contest-strategy |
| 歩道 → ウォーク | 道路の意味の「歩道」とぶつからないか確かめてから。足したら用語集の対応表のウォークの行を戻し、表の下の注記を消す。k-shortest-paths の summary 由来で lists・llms.txt に 3 か所ある（b1 E2 で「prh に入れられるものは入れる」と決まっているので §7） | glossary |

## 6. checklists への提案

直接の提案はない。検証の観点に足せる候補（メインの判断）：

- 早見表・逆引きの値を持つページを直したら、早見表の同じ行・見分け方の表も見たか（cheatsheet・reverse-index-signs の提案から）
- 他者の記事の題名が h1 どおりか（offline-dynamic-connectivity・burnside-lemma の検証の指摘で繰り返し出た。§14-24 の確認）
- 台帳の pages に載っている役割の問題がページにあるか（abc189_c・abc197_c の食い違いから。fix_problems --check で拾えるなら道具の側。other.md §3）

## 7. 解決済み（b1・b3 の決定・手引き §13〜§15 で決まっているもの）

| 提案 | 決まっているところ | 出したページ |
| --- | --- | --- |
| 用語集にない語はリンクせず本文で定義し、提案に書く | §15-1（ほぼ全ページが従った） | 多数 |
| 確認問題を `## 確認問題 {#quiz}` にまとめるか（chromatic-number は「バッチでそろえる方針をメインが決める」として節の中に置いたまま） | §14-11 で決まっている。chromatic-number は #quiz へ移す（other.md） | chromatic-number |
| Library Checker の問題を練習問題の節の小見出しに置くか、ほかの節の中に置くか | §15-5。stirling-first は直しで移した。tree-ratio-greedy は「計算量と自作するときの要点」の節の中に置いたまま指示を求めた → 練習問題の小見出しへ移す（other.md） | stirling-first・tree-ratio-greedy |
| グリッドのマスの記法（(i, j)・di・dj） | b1 の決定（記法は notation でまとめる）どおり、notation の #indexing に入った（grid・grid-graph・rotation-transform は i・j、manhattan-chebyshev の盤面の節の r・c をそろえるかは notation に従って直す） | grid |
| 見出しが 60 字を超える sections の title | §14-12（anchor を変えずに短くしてよい）。interval は検証で短くした | interval |
| `__int128` の mulmod の置き場 | §15-12（mod-pow）。miller-rabin の書き分けの案は §2 の §5 の表に残した | miller-rabin・notation |
| two-sat の `{#acl}` の title を自作の要点と Library Checker を含む形に変えた | §15-3（acl の中身の節を認める）。title の変更は §13-2 で執筆者が行ってよい | two-sat |
| summary・signs の「歩道」 | §14-22・付録 A（ウォーク）。k-shortest-paths の summary・signs の直しは front matter の表記の直しとして反映（other.md） | k-shortest-paths・glossary |
| summary の「償却」 | 付録 A（ならし計算量）。dynamic-tree の summary を直す（other.md） | dynamic-tree |
| guide の要点の項目を内容に合わせて変えてよいか | §2.2 に「guide・start・patterns・hub は項目を内容に合わせて変えてよい」とある | practice-method・stress-testing |
| 使い分けに近い中身の節（add-only が使い分けを兼ね、comparison を置かない） | §15-4 | dynamic-tree |
| ACL の囲みを置かないページ（acl: []） | §14-4 | parallel-binary-search ほか |
| 文の箇条書きの句点 | §15-2 | xor |
| stub のページへはページへのリンク、draft になったらメインが張り替える | §14-23（handoff.md §1） | 多数 |
| Library Checker の問題数などを手元で数えた値に日付を添える | §15-11（library-design は従った。範囲を広げる件は §1） | library-design |
| std の名前と同じ関数名を作らない | §9・§15-9。`merge` を例に足す件は §2 の §9 に残した | balanced-bst・hadamard-transform |
