# complete-binary-tree の検証（工程8b・b1）

- 対象：docs/tree/complete-binary-tree.md、snippets/complete-binary-tree/（lru-moves・lca-by-index・count-at-distance の 3 組）、docs/img/complete-binary-tree/binary-path.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md、執筆者の報告 planning/batches/b1/complete-binary-tree.md の未解決の点

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page complete-binary-tree`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/complete-binary-tree`（3 片・コンパイル 3 回・期待と違う 0）、`npx textlint docs/tree/complete-binary-tree.md`（0 errors・9 warnings。報告のとおり助詞「は」の重複と文の長さ。目で読んで支障はない）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- front matter：前の commit との差は complexity・stage・sections への next-steps の追加だけ。next-steps は tree-basics・steiner-subtree・memoized-recursion など他の基礎のページと同じ書き方で、手引き §4 の基礎の構成（… → 上位の手法とのつながり → 問題）に合う。要点の計算量と complexity は一致。別名の行に aliases 5 つがすべてある
- 問題：`python3 tools/ap.py show` で abc243_d（Moves on Binary Tree・758）・abc465_d（X to Y・839）・abc321_e（Complete Binary Tree・1627）を確かめ、本文の題名・diff と一致。補充の候補の abc264_h（Ex. Perfect Binary Tree・2660）も実在
- 例題 ABC243 D：drken の記事（evidence）で、根で U をしない保証・答えが 10^18 以下・「L/R の直後の U は相殺 → スタック → U が続いた後に L・R が続く列が残る」を確かめた。本文の方針・解法の詳細と一致する。言い回しは記事と別（記事は「相殺」、本文は「打ち消す」で、確認問題の例 2・URL も独自）で F8 の問題はない
- 力試し ABC321 E：drken の記事で、自分の部分木の深さ K と、祖先ごとに X を含まない側の子の部分木を足し、根の手前で距離 K の祖先を数える方針、計算量 $O((\log N)^2)$ を確かめた。本文の 3 つの場合分けと一致
- 練習 ABC465 D（執筆者の未解決の点）：2yuu 氏の記事で操作（$\lfloor x/K \rfloor$ への置き換えと、$\lfloor y/K \rfloor = x$ となる $y$ への置き換え）を確かめた。comet725 氏・2yuu 氏・Konini64 氏の記事はどれも「大きい方を K で割る」解法で、comet725 氏・2yuu 氏のコードは $K = 1$ の場合を特別に扱っていない（$K = 1$ で $X \ne Y$ なら止まらない）。$K \ge 2$ が制約にあると考えてよい。どの記事にも制約の数値はなく、K の下限と X・Y が 0 を含むかを一次資料で確かめることはできなかった。ただし本文の方針は頂点 0 を含んでも正しい（大きい方は 1 以上なので 0 を割ることはなく、0 は 1..K−1 の親として木につながる）。本文の要約の行は 2yuu 氏の記事と一致し、手法名を含まない
- 主張の確かめ（手計算と反例探し）：
    - 2 進表記と道順・祖先 ⇔ 接頭辞・13 と 11 の LCA が 1（`1101` と `1011`）・$i \le 10^{18}$ の祖先が 60 個以下（$\lfloor \log_2 10^{18} \rfloor = 59$）：正しい
    - 大きい方を割る LCA の正しさの説明：$x > y$ なら $x$ は $y$ の祖先でない → $x$ は LCA でない → LCA は $x$ の親の祖先、の筋で穴はない。K 分木（$\lfloor i/K \rfloor$）でも親は子より小さいので同じ
    - L/R/U の打ち消し：U で空のスタックなら前の L・R はすべて打ち消し済み、残りの L・R を適用する間は単調増加、で途中の値は max(初めの X, 答え) を超えない。確認問題（2 から URL → 6、並べ替えると 5 になる）も正しい
    - 3 分木の確認問題（14 と 5 の距離 3・LCA 1・3 進で `112` と `12`）、N = 10・頂点 2 から 2 段下が 3 個、$[v 2^d, v 2^d + 2^d - 1]$：正しい
    - 0 始まりの式（子 $Ki+1..Ki+K$・親 $\lfloor (i-1)/K \rfloor$）、`__builtin_clz` に long long を渡すと unsigned int に変換される・0 は未定義動作：正しい
- コード片：
    - lca-by-index は k = 2..5・x, y ≤ 200 で祖先の集合を作る方法と、k = 2 で dep の式と照合している。cases の 13 11 2 → 6 を手で数え直して一致
    - lru-moves は根で U をしない乱数の列 2000 本を素朴なシミュレーションと照合。cases の 100 回 R → 100 回 U → L（途中が $2^{100}$ 倍）で 10^18 が出る
    - count-at-distance は n ≤ 70 の全頂点・全 k を BFS と照合。cases の N = 10^18・X = 1・K = 59 → 423539247696576513 は $10^{18} - 2^{59} + 1$ と一致。`count_below` の `2 * l`・`2 * r + 1` は l, r ≤ n ≤ 10^18 で 2×10^18+1 < 2^63 なのであふれない。K = 999999999999999999 でも 60 回ほどで抜ける
    - 取り込みは core の数行だけで、書き方は §9（bits・using namespace・マクロなし・`'\n'`）に合う
- リンク先の anchor：ds/segment-tree.md#invariants・ds/priority-queue.md#binary-heap・tree/lca.md#jump・tree/lca.md#distance・ds/stack-techniques.md#cancel・basics/bit-operations.md#pitfalls がすべてある（どれも draft）
- 確認問題を節の中に置いた点（執筆者の未解決の点）：手引き 78 行「確認問題を要所に置き」に合う。`## 確認問題 {#quiz}` がなくてよい
- 図：Windows の Chrome（headless=new）で binary-path.svg を等倍（700×500 を 2 倍密度）と、幅 390px の画面に幅 358px で（2 倍密度・暗い背景の上に）画像にして目で確かめた。背景は白で塗られ、`viewBox` があり、文字はテキストのまま。番号・2 進表記・13 への道（R・L・R の太線）は本文・代替テキストと一致し、色に加えて線の太さとラベルで区別している。ただし指摘 1・2

## 指摘

### 1｜直すべき｜figure（G5）｜binary-path.svg の深さ 2 の 2 進表記（`100`・`101`・`110`・`111`）

- **問題**：深さ 2 の頂点から深さ 3 へ下りる辺が、頂点の下の 2 進表記の文字の上を通り、`100`・`101`・`110`・`111` が線と重なって読みにくい。とくに `110`（頂点 6）は本文と代替テキストが「13 から 6 = 110 になる」と名指しする値で、太線も重なる
- **根拠**：上の画像で確認。座標でも、辺は (455, 308) から (492.5, 372) などへ引かれ、2 進表記は y = 328（字の高さ 318〜328）・幅約 23px で、y = 318〜328 での辺の x は中心から ±6〜12px にあり、文字の範囲（±11.5px）と重なる。深さ 0・1 は辺の開きが大きいので重ならない
- **直し方**：2 進表記を円の横（右下）に置くか、深さ 2 だけ円の下の余白を広げる（深さの間隔を 100 → 120 にする、または辺の始点を表記の下 y ≈ 335 からにする）。深さ 3 は下に辺がないのでそのままでよい

### 2｜直すとよい｜figure（G3）｜binary-path.svg の文字の大きさ（スマホ）

- **問題**：viewBox の幅 700 を幅 358px で表示すると約 0.51 倍になり、2 進表記（13px）は約 6.6px、上と下の説明文（14px）は約 7px になる。画像で確かめると、2 進表記は拡大しないと読みにくい
- **直し方**：上下の説明文は本文と代替テキストに同じ内容があるので図から外し、その分の高さを詰める。2 進表記を 15〜16px にする。または viewBox の左の「深さ」の列を細くして横幅を 600 程度に詰める

### 3｜直すとよい｜fact（F7）・clarity（U3）｜#lru-moves の「計算量は移動の数を $N$ として $O(N)$」と #abc243_d の「全体で $O(N)$」

- **問題**：このページでは $N$ は一貫して頂点数（「頂点 $1, \dots, N$」「$N \le 10^{18}$」「$O(\log N)$」）だが、この 2 か所だけ移動の数を $N$ と呼ぶ。同じ節の近くに $O(\log N)$ があるので、$N = 10^{18}$ の $O(N)$ と読み違えうる
- **直し方**：「移動の列の長さを $\lvert S \rvert$ として $O(\lvert S \rvert)$」か「移動の数を $M$ として $O(M)$」にし、例題の解法の詳細もそろえる

### 4｜直すとよい｜fact（F7）・clarity（U6）｜#k-ary と #count-at-distance の $K$

- **問題**：$K$ が #k-ary・練習では「子の数（分木の K）」、#count-at-distance・力試し・front matter の complexity では「距離」を表す。コード片でも lca-by-index の `k` は子の数、count-at-distance の `k` は距離である。節を 1 つだけ読めば通じるが、要点の「頂点 $X$ から距離 $K$ の頂点の数」と別名の「K 分木」が並ぶ冒頭では同じ文字が 2 つの意味になる
- **直し方**：#count-at-distance の冒頭に「この節の $K$ は距離である（K 分木の $K$ とは別）」と一言添える。または分木の側を $k$（小文字）に統一する（問題の表記に合わせたいなら前者でよい）

### 5｜直すとよい｜fact（F2）｜#binary-path の 3 つ目の箇条（「深さ $d$ の頂点は $2^d$ 以上 $2^{d+1}$ 未満の番号にちょうど並ぶ」）

- **問題**：導入で「頂点 $1, \dots, N$ だけを使うと最後の段が欠ける」と述べた直後なので、「ちょうど並ぶ」は最後の段でも $2^{d+1} - 1$ まで埋まると読める。最後の段が欠けることは落とし穴の 2 つ目の主題でもある
- **直し方**：「深さ $d$ の頂点は、$2^d$ 以上 $2^{d+1}$ 未満（かつ $N$ 以下）の番号に左から順に並ぶ」とする

## 台帳への提案（メインへ。ページの指摘ではない）

- abc465_d の summary はいま台帳で「（執筆時に確かめる）」のまま。執筆者の提案の要約（本文の行と同じ）を入れ、evidence に 2yuu 氏の URL を足すことに賛成（記事で操作の内容を確かめた）。checked に 2026-10-21 を入れてよい
- abc243_d・abc321_e：記事で問題の内容を確かめた。checked に 2026-10-21 を入れてよい

## 総合の判定

小さな直しで可。直すべき 1 件（図の文字と辺の重なり）、直すとよい 4 件。本文の事実・コード片・問題の方針に誤りは見つからなかった。
