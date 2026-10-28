# basics-dp の報告（バッチ minor-content）

- 担当の Issue：#11・#12・#13・#14・#15・#16・#17・#18・#19・#20（どれも完了。#19 のうち ds/segment-tree-on-values は別の担当）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content）。git は読むだけで、commit などはしていない。Issue にはコメント・編集・クローズをしていない
- 直したファイル（15）：docs/basics/bit-operations.md、docs/dp/subset-enumeration-dp.md、docs/guide/method-comparison.md（217 行目だけ）、docs/basics/recursive-enumeration.md、docs/basics/prefix-sum.md、docs/basics/binary-search.md、docs/basics/brute-force.md、docs/basics/greedy-basics.md、docs/dp/monge.md、docs/dp/dp-basics.md、docs/dp/slope-trick.md、docs/dp/knapsack-01.md、docs/dp/alien-dp.md、docs/dp/cht.md、docs/dp/tree-dp.md
- front matter で変えたもの：頼まれた項目だけ。signs（bit-operations・subset-enumeration-dp・monge）、prerequisites・related（alien-dp・cht）。15 ページすべて本文を直したので `updated` を 2026-10-29 にした。stage とほかの項目は変えていない
- 生成物（逆引き辞典・docs/index/・graph.json・roadmap の生成部分など）には触れていない。メインが gen_site で作り直す（下の「検査」）

## #11 3^N で間に合う N の目安をそろえる（完了）

持ち主は basics/complexity-estimation 60 行目の「$3^N$ は $N \le 15$〜$16$ 程度まで」である。

- **docs/basics/bit-operations.md**
  - 19 行目（signs）：`N ≤ 18 程度で、…（全体で 3^N）` → `N ≤ 15〜16 程度で、集合とその部分集合の組をすべて調べる（全体で 3^N）`
  - 38 行目（要点のいつ使うか）：signs と同じ内容（`$N \le 15$〜$16$ 程度で、…`）にした
  - 146 行目（#submask）は「$N \le 16$ 程度なら軽く、$N = 18$ は中身の軽いループでなければ苦しい」で、すでに 18 に条件が付いているので変えていない
- **docs/dp/subset-enumeration-dp.md**
  - 18 行目（signs）：`N ≤ 16〜18（3^N ≈ 4×10^7〜4×10^8）` → `N ≤ 15〜16 程度（3^N ≈ 1.4×10^7〜4.3×10^7）、内側の処理が軽ければ N = 18 まで`
  - 37 行目（要点）：signs と同じ内容にした（`$N \le 15$〜$16$ 程度（$3^N \approx 1.4 \times 10^7$〜$4.3 \times 10^7$）、内側の処理が軽ければ $N = 18$ まで。`）
  - $N = 18$ を残したのは、例題 ABC187 F が $N \le 18$ で、88 行目・204 行目が「内側が軽ければ間に合う」と説明しているからである。逆引き辞典（制約から）で $N = 18$ の問題を持つ読者がこのページにたどり着けるように、条件つきで残した（Issue の「$N = 18$ に触れる箇所は条件を添える」に従った）
  - 45 行目・88 行目・204 行目はすでに条件付きなので変えていない
- **docs/guide/method-comparison.md** 217 行目：`$O(3^N)$（$N \le 15$ 程度）` → `$O(3^N)$（$N \le 15$〜$16$ 程度）`（この 1 か所と `updated` だけ）
- **docs/basics/recursive-enumeration.md** 194 行目：`$O(3^N)$ で $N \le 15$ 程度まで届く` → `$O(3^N)$ で $N \le 15$〜$16$ 程度まで届く`
- **確かめたこと**：$3^{15} = 14348907 \approx 1.4 \times 10^7$、$3^{16} = 43046721 \approx 4.3 \times 10^7$、$3^{18} = 387420489 \approx 3.9 \times 10^8$ を計算で確かめた。`gen_site.py --check --diff` で、逆引き辞典（制約から）の 2 行が「N ≤ 15〜16 程度で、…」「N ≤ 15〜16 程度（…）、内側の処理が軽ければ N = 18 まで」に替わり、docs/index/basics.md・dp.md の制約の行も替わることを見た（書き換えはしていない）。ほかのページ（cheatsheet 49・147 行目、reverse-index-constraints 89・441 行目、bell-number）はもともと 15〜16（または 16）でそろっている
- **残った点**：なし

## #12 prefix-sum の「次のページ」の重複をなくす（完了）

- **docs/basics/prefix-sum.md**
  - 172 行目（#next-tools の導入）：「前提が崩れたときに使う手法と、累積和の考え方が広がる先をまとめる。」→「この前提が崩れたときに使う手法をまとめる。」
  - 旧 185〜190 行目（「累積和の考え方は、次のページで広がる。」と 4 項目）を消した。#next-tools は導入・表・2 段落だけになった
- **確かめたこと**：消した 4 項目の行き先（prefix-sum-counting・imos・prefix-sum-2d・dp-prefix-sum）は、どれも直後の #next-steps の 4 項目が節へのリンクで指している。#next-steps の最後の項目は #next-tools へ戻るリンクのまま。#next-tools の anchor は変えていない
- **残った点**：なし

## #13 二分探索と全探索から「一部を固定して数える」へリンクする（完了）

- **docs/basics/binary-search.md** 136 行目（#fix-one-side の「3 つ組は真ん中を固定する」）の末尾に「（位置の条件 $i < j < k$ も付くときは[真ん中を固定して左右を独立に数える](../thinking/fix-variable.md#fix-middle)）」を足した。項目の並びのほかの行と同じ、括弧で添える形にした
- **docs/basics/brute-force.md** #half-enumeration の末尾（128 行目）に 1 段落を足した：「片側を全探索で固定したあと、残りの条件の形から道具を選ぶ方法は[固定したあとを速くする](../thinking/fix-variable.md#speed-up)にある。」
- **確かめたこと**：fix-variable の sections に fix-middle・speed-up があり、fix-middle の 67 行目が「位置の条件 $i < j < k$ もあるなら BIT、3 つの別の列なら二分探索」と書き分けていることを読んで、binary-search 側の添え書きの内容を合わせた。ビルドした HTML で 2 つのリンクが thinking/fix-variable/#fix-middle・#speed-up を指すことを見た
- **残った点**：なし

## #14 マトロイドとクラスカル法の飛躍を埋める（完了）

- **docs/basics/greedy-basics.md** 71 行目の括弧（「全域木はどれも辺の数が同じなので、重みの符号を反転して重い順に足すのと同じになる」）を消し、次の文に置き換えた（段落の最後の「コンテストでマトロイドを…」は 73 行目の別の段落にした）
  > 重みの和の最小化を重い順に足す貪欲の形に直すには、各辺の重み $w$ を $C - w$（$C$ は重みの最大値以上の定数）に置き換える。置き換えた重みはどれも非負である。全域木はどれも辺の数が同じ（頂点数を $N$ として $N - 1$ 本）なので、置き換えた重みの和は、$C(N - 1)$ から元の重みの和を引いた値になる。よって、置き換えた重みで和が最大の木は、元の重みで和が最小の木である。置き換えた重みの重い順は元の重みの軽い順と同じなので、重い順に足す貪欲は、軽い順に足すクラスカル法と同じ手順になる。
- Issue の例文の 3 文に、「辺の数が同じ」が効く理由（どの木でも定数の分 $C(N - 1)$ が等しい）を式で添えた。「十分大きな定数」は「重みの最大値以上の定数」と具体的にした（これで 65 行目の「重みがどれも非負」を満たす）。括弧の中に 3 文以上入れると読みにくいので、括弧を外して文にした
- **確かめたこと**：全域木 $T$ について $\sum_{e \in T} (C - w_e) = C(N - 1) - \sum_{e \in T} w_e$ なので、置き換えた重みの最大と元の重みの最小が一致する。65 行目の規則（負になったら止める）とも食い違わない
- **残った点**：なし

## #15 Monge の要点と signs の不等式に添字の大小を書く（完了）

- **docs/dp/monge.md**
  - 16 行目（signs）：`'区間分割 DP のコストが a ≤ b ≤ c ≤ d について c(a, c) + c(b, d) ≤ c(a, d) + c(b, c) を満たす（区間を広げるほど増え方が大きい）'`
  - 39 行目（要点）：同じ内容で `$a \le b \le c \le d$ について` を足した
- **確かめたこと**：62 行目の言い直し（$l_1 \le l_2 \le r_1 \le r_2$、$a, b, c, d$ をこう書き替えた）と大小の向きが一致する。等号の場合（$a = b$ や $c = d$）は両辺が等しくなるので、$\le$ で書いてよい。`gen_site.py --check --diff` で逆引き辞典（言い回しから）と docs/index/dp.md の行が替わることを見た
- **残った点**：alien-dp 132 行目は Monge を「$a < b < c < d$ で …」と狭義で書いている（担当の Issue の範囲外なので変えていない。どちらでも正しい）

## #16 DP の基本の型の地図にグリッドと区間分割を足す（完了）

- **docs/dp/dp-basics.md** #map の表（178〜181 行目）
  - 179 行目に足した：`| グリッドのマス $(i, j)$ | 右か下にだけ進む経路の数・経路上の値の最大 | [グリッド上の DP](../dp/dp-grid.md) |`
  - 180 行目に足した：`| 先頭 $i$ 個の区切り方（最後の区間の左端で分ける） | 列を連続した区間に区切る方法の数・最小コスト | [区間分割 DP](../dp/dp-sequence-partition.md) |`
  - 181 行目（区間 DP の行）のページの列に「（区切るだけなら区間分割 DP）」を添えた。リンクは直前の行にあるので、ここは文字だけにした（同じ節でのリンクは 1 回）
- Issue の例からの小さな違い：状態の形を「列の区切り方（最後の区間の左端）」ではなく「先頭 $i$ 個の区切り方（最後の区間の左端で分ける）」にした（dp-sequence-partition の導入「『先頭 $i$ 個をどう区切るか』の表で解く」と summary「最後の区間の左端 j で分けて求める」に合わせた）。サインの例は「経路の数・最大」を「経路の数・経路上の値の最大」にした（dp-grid の summary に合わせた）
- 並びは、列 → グリッド → 区切り → 区間 の順にした（列の DP の章どうしを先に、区切りを区間の直前に置いて、添え書きが直前の行を指すようにした）
- **確かめたこと**：ビルドした HTML で表が 10 行になり、2 つのリンクが ../dp-grid/・../dp-sequence-partition/ を指すことを見た
- **残った点**：見出し「DP の型の地図（列・区間・集合・桁・木・順列・確率・ゲーム・高速化）」にグリッドがない（下の提案 1）

## #17 Slope Trick の導入の出題数を力試しと合わせる（完了）

- **docs/dp/slope-trick.md** 45 行目：「ABC で必須になったのは H に 1 問（ABC217 H、2021 年）見つかる程度の発展の手法である。」→「ABC で必須になったのは ABC217 H（2021 年）と、その変形で解く ABC458 G（2026 年。[力試し](#challenge)に載せた）の 2 問が見つかる程度の発展の手法である。」
- ABC458 G の扱い：台帳の approach は「傾きの列（Slope Trick に近い持ち方）でならし O(N) に判定する」、slope-trick 向けの alternatives も「上に凸な折れ線として傾きの列で持つ」、ページの力試しの方針は「2 つのヒープの代わりに片側のスタックで足りる Slope Trick の変形」である。どれも標準の形ではなく変形なので「その変形で解く」とし、詳しくは力試しの節へリンクした。読点が 3 つを超えないように、Issue の例の「H に 1 問（…、…）」の形を「ABC217 H（2021 年）」の形にした
- **確かめたこと**：`python3 tools/ap.py show abc458_g` → G. Children Yearn for the Evil Kindergarten、diff 2831、2026-05-16。`show abc217_h` → H. Snuketoon、diff 3112、2021-09-04。front matter の frequency_evidence「recent 1（abc458_g）」と数が合う。入口の形（2 つのヒープ）の ABC127 F は「黄の帯の問題にも出る」の文のほうに入るので、数えていない
- **残った点**：なし

## #18 ナップサック DP の O(NW) の目安の括弧の値（完了）

- **docs/dp/knapsack-01.md** 158 行目：「（$N \le 100$ なら $W \le 10^5$ 程度）」→「（$N = 100$ なら $W \le 10^6$ 程度）」
- **確かめたこと**：$100 \times 10^6 = 10^8$ で、直前の「$NW$ が $10^8$ 程度まで」と合う。メモリは 89 行目のとおり 1 次元の配列なら $O(W)$（`long long` で約 8 MB）で足りる
- **残った点**：なし

## #19 前提の過不足（alien-dp・cht。segment-tree-on-values は別の担当）（完了）

- **docs/dp/alien-dp.md**
  - 11 行目：`prerequisites: [monge, binary-search]` → `[binary-search]`
  - 12 行目：related に `monge` を足した（dp-sequence-partition の後ろ）
  - 39 行目（要点の前提）：「[二分探索](../basics/binary-search.md)」だけにした
  - 128 行目（#with-monge の冒頭）：「この節は[Monge 性による DP の高速化](../dp/monge.md)を前提にする。」の段落を足した（merge-process-tree・static-top-tree・lcs と同じ書き方）
  - 138 行目：同じ節の 2 回目の monge へのリンク（「[Monge 性による DP の高速化](../dp/monge.md)で速く解ける」）を「Monge 性を使って速く解ける」の文字だけにした（同じ節でのリンクは 1 回。LARSCH の節へのリンクは残した）
- **docs/dp/cht.md**
  - 11 行目：`prerequisites: [dp-basics, convex-hull]` → `[dp-basics]`
  - 12 行目：related の末尾に `convex-hull#cht-duality` を足した（双対の節を指す。graph.json では anchor が外れて convex-hull になる）
  - 38 行目（要点の前提）：「[DP の基本](../dp/dp-basics.md)」だけにした
  - 97 行目の双対の段落の[凸包と CHT の双対](../geometry/convex-hull.md#cht-duality)へのリンクは残した
- **確かめたこと**：alien-dp で Monge に触れるのは #with-monge と、そこへの内部リンク（74・90 行目、練習の ABC355 G の方針 188 行目）だけで、#penalty・#binary-search-lambda・#undoable-greedy・例題 ABC218 H は Monge なしで読める。cht の #lower-envelope の不要な直線の判定は掛け算の不等式で書かれていて、凸包のページを読まなくても分かる。`check_pages.py` がエラー・警告 0（前提と related の重複・循環・anchor の検査を含む）。`gen_site.py --check --diff` で、docs/index/dp.md の前提の行、graph.json の prerequisites・related、ロードマップの発展の表の並び（Slope Trick・CHT などの位置）が替わることを見た
- **残った点**：alien-dp の前提が binary-search だけになり、DP のページが前提の鎖から消えた（下の判断してほしい点 1）

## #20 木 DP のスタックの深さの助言（完了）

- **docs/dp/tree-dp.md** 223 行目（落とし穴の「再帰が深すぎる」）の 3 文目以降を次にした
  > AtCoder ではスタックの上限が大きく、再帰の DFS のままで通ることが多い。ランダムな木の入力例では深くならないので、一直線の木は自分で作って試す。手元で試すときは、スタックの上限を広げるか、[帰りがけ順に子から集める](#postorder)の BFS 順の逆で書いて再帰をなくす（[AtCoder と手元の C++ 環境](../cpp/cpp-environment.md#stack-depth)）。深さが $10^6$ を超えるときや、提出先の上限が分からないときも、再帰をなくす方が確実である
- 「ジャッジの上限は環境によるので、手元で落ちるなら提出でも危ないと考える」を消した。リンクの文字は「環境の設定」から、tree-traversal 142 行目・graph/dfs 109 行目と同じページ名「AtCoder と手元の C++ 環境」にした
- **確かめたこと**：cpp-environment#stack-depth（156〜185 行目）の「手元は 8 MiB が多い」「`ulimit -s unlimited` で上限を外す」「AtCoder では深い再帰も通ることが多いが、深さ $10^6$ を超えるときや上限が分からないときは非再帰に書き直す」と同じ見方になった。tree-traversal 142 行目・dfs 109 行目の「AtCoder では再帰の DFS のままで通ることが多い」とも合う
- **残った点**：なし

## 検査

- `python3 tools/check_pages.py --page <15 ページ>`：エラー 0・警告 0。全ページ（353）でもエラー 0・警告 0（同じ作業ツリーのほかの担当の変更を含む時点）
- `npx textlint <15 ファイル>`：エラー 0。警告は直す前と後で同じ 256 件（ファイルと規則ごとの件数も同じ。元の版は作業用フォルダに `git show HEAD:` で取り出して比べた）。直した行に出る警告は 2 件で、どちらも前からある
  - recursive-enumeration 194 行目：文の長さ（直す前 126 字 → 131 字。目安の「〜$16$」の分だけ伸びた。上位の手法へのつながりの 1 項目なので、Issue の範囲を超えて言い換えていない）
  - tree-dp 223 行目 16 字目：助詞「が」の重複。変えていない 2 文目（「スタックの上限が 8 MiB のことが多い」）の分
- `python3 tools/fix_problems.py --check --page <id>`（method-comparison を除く 14 ページ）：直すべき行 0。問題の行には触れていない
- `python3 tools/gen_site.py --check --diff`：終了コード 1（期待どおり）。作り直しが要る生成物は docs/llms.txt・docs/index/basics.md・docs/index/dp.md・overrides/assets/data/graph.json・docs/guide/reverse-index-constraints.md・docs/guide/reverse-index-signs.md・docs/guide/roadmap.md・docs/start/how-to-use.md の 8 ファイル（ほかの担当の変更の分も含みうる）。書き換えはしていない
- `uv run mkdocs build -q --strict -d <作業用フォルダ>/site`：終了コード 0（壊れたリンクなし）。dp-basics の表、alien-dp の #with-monge、binary-search・brute-force・tree-dp・slope-trick の新しいリンクを HTML で確かめた
- コード片・図には触れていないので check_snippets・check_svg は流していない

## 提案（メインに頼む共有のものの変更）

1. **dp-basics の #map の見出し**（任意）：表にグリッドの行を足したので、見出しと sections の title を「DP の型の地図（列・グリッド・区間・集合・桁・木・順列・確率・ゲーム・高速化）」にしてもよい（anchor の map は変えない。front matter の sections の title の変更なので、頼まれた範囲の外として直していない）
2. **生成物**：上の 8 ファイルを gen_site で作り直す。ロードマップの発展の表（reading-order-advanced）は、alien-dp と cht の前提が減って並びが変わるので、作り直した後に並びを目で確かめてほしい（`--check --diff` の出力は途中で切れていて、新しい並びは見られなかった）

## 判断してほしい点

1. **alien-dp の DP の前提**：monge を外すと、前提は binary-search だけになり、DP のページ（monge → dp-sequence-partition → dp-prefix-sum → … → dp-basics）が前提の鎖から消える。#penalty と例題 ABC218 H は DP の状態と遷移を使うので、prerequisites と要点の前提に dp-basics（または dp-state-design）を足すかを決めてほしい。Issue と指示の範囲を超えるので足していない
2. **cht の related の書き方**：`convex-hull#cht-duality` と節まで書いた。Issue の字面どおり `convex-hull` だけにしたいなら書き換える（graph.json ではどちらも convex-hull になる）
3. **#16 の行の言い回し**：Issue の例と少し違う（状態の形「先頭 $i$ 個の区切り方（最後の区間の左端で分ける）」、サイン「経路の数・経路上の値の最大」）。Issue の字面に合わせるなら直す

## 使用量の目安

- 道具の呼び出し：約 65 回。Web の取得：0 回（atcoder.jp・codeforces.com は開いていない。問題は `tools/ap.py` と台帳で確かめた）
- 一時ファイル：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/basics-dp（textlint の比較、gen_site の --check の出力 gen-check.txt、ビルド site/）

## 検証の指摘への対応（2026-10-29）

検証（verify-basics-dp.md）の「直しが要る点」2 件（どちらも #19 の alien-dp）を直した。指摘はどちらも正しいと判断した。任意の点（#11 の reverse-index-constraints 112 行目、#14 の $(N - 1)C$、#16 の見出し、#17 の「その」）は頼まれていないので直していない。直したファイルは docs/dp/alien-dp.md だけである（`updated` はすでに 2026-10-29）。

### 1. alien-dp の前提に DP の基本を足した（上の「判断してほしい点 1」は、これで解消）

- **docs/dp/alien-dp.md**
  - 11 行目：`prerequisites: [binary-search]` → `[dp-basics, binary-search]`
  - 39 行目（要点の前提）：「[二分探索](../basics/binary-search.md)」→「[DP の基本](../dp/dp-basics.md)、[二分探索](../basics/binary-search.md)」（cht・dp-speedup-overview と同じ形。並びは prerequisites と同じ）
- **確かめたこと**
  - front matter から前提の閉包を計算した：直す前は {binary-search, sorting-techniques} だけ、直した後は {dp-basics, brute-force, complexity-estimation, binary-search, sorting-techniques}。dp-basics と binary-search はどちらも他方から届かないので、推移的に冗長な前提にならない。dp-basics（dp・order 10）はナビゲーションで alien-dp（order 370）より前にある
  - 本文の核（導入、#penalty の「DP なら遷移で λ を引く」、#binary-search-lambda の罰金つきの DP、例題 ABC218 H の「直前のランプの色を状態に持つ DP」）は DP の状態と遷移を使い、#with-monge の外に DP のページへのリンクがないことを読んで確かめた（指摘のとおり）
  - gen_site の Site をメモリで作り（何も書いていない）、ロードマップの発展の列を出した：Alien DP は 5 番（Monge の次）、CHT は 8 番で、検証の報告と同じである。`gen_site.py --check --diff` で、docs/index/dp.md の前提の行が「`dp-basics`、`binary-search`」に、graph.json の alien-dp の prerequisites が ["dp-basics","binary-search"] になり、related に monge が入ることを見た
  - ビルドした HTML で、要点の前提が「DP の基本、二分探索」（../dp-basics/・../../basics/binary-search/ へのリンク）、ページ下部の「前提」が「DP の基本 基礎」「二分探索 基礎」になることを見た

### 2. #with-monge の冒頭の文に空白を入れた

- **docs/dp/alien-dp.md** 128 行目：「この節は[Monge 性による DP の高速化](../dp/monge.md)を前提にする。」→「この節は [Monge 性による DP の高速化](../dp/monge.md)を前提にする。」
- **確かめたこと**：手引き §7 の「半角英数字と全角文字の間に空白を入れる」に当たる。リンクの文字が半角で始まるときに前へ空白を入れるのは、static-top-tree 45 行目・lcs 183 行目・dynamic-dp 111 行目と同じ書き方である。ビルドした HTML で「この節は Monge 性による DP の高速化を前提にする。」と表示されることを見た。リンクの後ろは「高速化」と「を」でどちらも全角なので、空白は要らない

### 検査（この対応の後）

- `python3 tools/check_pages.py --page alien-dp`：エラー 0・警告 0。全ページ（353）でもエラー 0・警告 0
- `npx textlint docs/dp/alien-dp.md`：エラー 0。警告は直す前と同じ 15 件（規則ごとの件数も同じ）で、直した行（11・39・128 行目）には出ない
- `python3 tools/fix_problems.py --check --page alien-dp`：直すべき行 0（問題の行には触れていない）
- `python3 tools/gen_site.py --check --diff`：終了コード 1（期待どおり。作り直しはメインの作業）。書き換えはしていない
- `uv run mkdocs build -q --strict -d <作業用フォルダ>/site`：終了コード 0
- コード片・図には触れていないので check_snippets・check_svg は流していない

### 残った点

- なし。#19 の完了の条件のうち「`tools/gen_site.py` で作り直してある」はメインの作業として残る（ds/segment-tree-on-values は別の担当）

### 使用量の目安（この対応）

- 道具の呼び出し：約 25 回。Web の取得：0 回（atcoder.jp・codeforces.com は開いていない）
- 一時ファイル：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/fixup-basics-dp（前提の閉包の計算 closure.py、ロードマップの計算 roadmap.py、textlint の比較、gen_site の --check の出力 gen-check.txt、ビルド site/）
