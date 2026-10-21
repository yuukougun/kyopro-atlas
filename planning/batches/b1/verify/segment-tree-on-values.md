# segment-tree-on-values の検証（工程8b・バッチ b1）

- 対象：docs/ds/segment-tree-on-values.md、snippets/segment-tree-on-values/{count-sum,top-k,dynamic-odd-sum}.{cpp,yaml}、docs/img/segment-tree-on-values/count-sum-tree.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page segment-tree-on-values`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/segment-tree-on-values`：3 本とも 3 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 手でのビルド：`g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` で 3 本をビルド。警告なし
- ランダムの突き合わせ（作業用の場所で実行。リポジトリには置いていない）：各 300 通り、計 900 回。コード内の assert（素朴な方法との一致）がすべて通り、サニタイザの報告なし
    - count-sum：長さ 1〜30、同じ値の多い小さな値の集合と、$10^9$ 近くを含む集合
    - top-k：追加・削除・質問を最大 40 回。$k = 0$ と $k =$ 全体の個数（`max_right` が $r = N$ を返す場合）を含む
    - dynamic-odd-sum：最大 60 個。同じ値の重なり、$1$ と $10^9$ の端を含む
- cases の期待出力を手で計算し直した：count-sum の 1 つ目（最後の行 $0, 10^9 + 3 + 3 + 7$）、top-k の 1 つ目（$\{1,5,5,9\}$ で $k = 3 \to 11$、$k = 2 \to 6$、5 を 1 個消して $k = 3 \to 15$）、dynamic-odd-sum の 1 つ目（$5, 1, 10^9 + 1, 6, 10^9 + 6$）。すべて一致
- 動的セグメント木のノード数とメモリ（指摘 1 の根拠）：コード片から assert と素朴な方法を外して $-O2$ で計測。$Q = 2 \times 10^5$ で、一様乱数の値は 2,685,039 個・最大常駐 87 MB、値を $5000$ おきに等間隔に置いた場合は 2,846,848 個・93 MB。理論上の上限は $\sum_{d=0}^{30} \min(2^d, Q) = 2{,}862{,}143$ 個
- `npx textlint docs/ds/segment-tree-on-values.md`：エラー 0・警告 23。半開区間 `[l, r)` の括弧の対応、数式を含む文の長さ・読点の数、「に」の重なり。執筆者の報告どおりで、§13.8 の誤検出の範囲
- `python3 tools/ap.py show`：abc339_e（1109）・abc281_e（1334）・abl_d（1283）・abc276_f（1562）・abc403_g（2028）・abc287_g（2180）がすべて存在し、label・diff・役割が本文・台帳・catalog（planning/catalog/ds.yaml）と一致。並びも易しい順
- front matter の差分（git diff）：変わったのは complexity・stage・updated と、sections の 3 つの title の短縮だけ（anchor と level はそのまま）。見出しの文字と sections の title は一致（§13.2）
- ACL（F4）：`~/lib/ac-library-master/document_ja/` の segtree.md（`max_right` の返り値の 2 条件と「`f` が単調なら最大の `r`」、`f(e())` が true の要件）、fenwicktree.md（`add(p, x)`・`sum(l, r)` が半開区間・$O(\log n)$）と照らした。`segtree` に加算がなく `set`・`get` だけであることも合う
- 主張の確かめ（F2）
    - #top-k-sum の「なぜ正しいか」：個数は非負なので $f$ は単調で、$r$ が最大なら $[0, r]$ の個数は $K$ を超え、$K - c$ は添字 $r$ の個数より少ない。正しい。`f(s) = [cnt < K]` で $K = 0$ のとき `f(e())` が false になる指摘も正しい
    - #odd-position-sum の結合：場合分けの式、結合法則の理由、葉の $x\lceil c/2 \rceil$・$x \lfloor c/2 \rfloor$ はすべて正しい（突き合わせでも一致）。余り $m$ への拡張（$\mathrm{cnt}_a \bmod m$ だけずらす）も正しい
    - #dp-on-values：区間の max を更新の前に取るので $A_i$ を 2 回使わない、範囲が $A_i$ 自身を含むので代入でよい、はどちらも正しい。drken の ABL D の記事の「配列を使い回すと前者の chmax が要らなくなる」と同じ筋だが、文の並び・言い回しは違う（F8）
    - 1 回の更新で通るノードは $\lceil \log_2 C \rceil + 1$ 個以下（$C = 10^9$ で 31）：中点で半分にする分け方の深さは $\lceil \log_2 C \rceil$ で、正しい。コード片の `assert(cnt.size() <= 1 + q * 31)` も通る
    - 落とし穴の「`vector` の要素への参照を持ったまま再帰」は正しい。なお `lch[v] = insert(lch[v], …)` と直接書く形は C++17 から右辺が先に評価されるので安全（本文は参照の例だけを挙げており、誤りはない）
    - #practice の ABC276 F の漸化式 $S_K = S_{K-1} + A_K + 2\sum_{i<K}\max(A_i, A_K)$：gotoki_no_joe の記事（台帳の evidence）の表の考え方と一致
- 出典（F9）：kmjp（abc403_g・abc287_g）、programming-hiroba（abc339_e）、drken（abc281_e・abl_d）、qiita gotoki_no_joe（abc276_f）を開いて、題名と内容が記述どおりであることを確かめた。kmjp の abc403_g は「想定解法は動的SegTree」「$X = (Y + \text{前の答え}) \bmod 10^9 + 1$」「バケット分割で解いた」で、本文の方針と合う。kmjp の abc287_g は「得点を座標圧縮し、得点 $n$ 以下の枚数・得点の和の BIT 2 本、全体から下位 $(S - X)$ 枚を引く」で本文と合う。Library Checker は GitHub の library-checker-problems（`data_structure/point_set_range_composite_large_array/` の task.md・info.toml）で、$N \le 10^9$・$Q \le 5 \times 10^5$ を確かめた（指摘 3）
- 未解決の点の確認
    - abc339_e の値の上限：programming-hiroba のコードの定数は $500000$。本文は「値の上限が小さい」としか書かないので、それで問題ない
    - 動的セグメント木のメモリ：見積もりの数が上限として大きすぎる（指摘 1）。abc403_g の $Q$ の上限は、kmjp の記事に記載がなく確かめられなかった。本文は $Q$ を問題に結び付けていないので、それでよい
    - Library Checker の $N$ の上限：上のとおり $10^9$ と確かめた
- 図：手元の chrome-headless-shell（puppeteer の 146.0.7680.76）で、680×490 と、幅 358px（スマホ相当）の img に縮めた 2 通りで描いて目で確かめた。この環境に日本語のフォントがなく、和文は豆腐になったので、和文の文字の幅は座標と文字数から見積もった（題名の行は約 600px、最下行は約 615px で、幅 680 に収まる）。背景は白、viewBox あり、文字はテキストのまま。丸ごと取るノードは実線の太枠、境界は破線の枠で、色だけに頼っていない（G4）。ノードの値（根 $(5, 1000000020)$、$[0,2)$ が $(3, 11)$、$[2,4)$ が $(2, 1000000009)$、葉 $(1,1)$・$(2,10)$・$(1,9)$・$(1,10^9)$）と $r = 1$・答え 6 は、本文の #top-k-sum の例と一致（G5・F3）
- リンク先：fenwick-tree・kth-element・segment-tree-binary-search・offline-queries・ordered-set・top-k-multiset は draft、dp-segment-tree・segment-tree-monoids・merge-sort-tree・wavelet-matrix・sqrt-decomposition は stub（節への anchor は付けていないので問題ない）。lis は存在する。用語集の `#identity-element`・`#associativity` は §13.5 のとおり書いてよい

## 指摘

### 1. 直すべき｜事実（F2・F3）｜#dynamic-segment-tree の「メモリの見積もり」

- 問題：「$Q = 2 \times 10^5$、$C = 10^9$ でノードは約 $6.2 \times 10^6$ 個になる」「約 200 MB 使う」は、$Q \times 31$ をそのまま掛けた上界で、実際にはその数にならない。根に近い段のノードは多くの値で共有されるので、深さ $d$ の段のノードは $\min(2^d, Q)$ 個までしかない
- 根拠：$\sum_{d=0}^{30} \min(2^d, 2 \times 10^5) = 2^{18} - 1 + 13 \times 2 \times 10^5 \approx 2.86 \times 10^6$ 個（32 バイトで約 92 MB）。コード片で計測すると、一様乱数で 2,685,039 個・最大常駐 87 MB、等間隔に散らした最悪に近い入力で 2,846,848 個・93 MB
- 直し方：「1 回の追加で作るノードは 31 個以下なので、全体で $Q \times 31 \approx 6.2 \times 10^6$ 個を超えない。実際は根に近い段のノードが共有されるので、最悪でも約 $2.9 \times 10^6$ 個（このコードで約 90 MB）である」のように、上界と実際の数を分けて書く。`reserve` を勧める文はそのままでよい（`reserve` するなら上界の $Q \times 31 + 1$ で確保すると書くと迷わない）

### 2. 直すとよい｜事実（F1）｜要点の「計算量」と front matter の complexity

- 問題：(a) 動的セグメント木の「1 回 $O(\log C)$」に、ならしかどうかが書かれていない。コード片はノードを `vector` の `push_back` で作るので、伸長を含めるとならしである（`reserve` すれば最悪でも $O(\log C)$）。手引き §5 の ds は「ならし計算量かどうかを明記する」。(b)「座標圧縮に $O(N \log N)$」の直後に「$N$ は値の種類数」と定義していて、ソートするのは種類数ではなく集めた値の全部（要素数 + クエリ数）である
- 直し方：(a)「（`vector` に足していくのでならし。先に `reserve` すれば最悪でも同じ）」と添える。(b)「座標圧縮は集めた値の個数を $M$ として $O(M \log M)$」とするか、「$N$ は値の個数（種類数はそれ以下）」のように、圧縮のソートの対象と添字の数を分ける。complexity の文字列も合わせる

### 3. 直すとよい｜事実（F3・F9）｜#dynamic-segment-tree の最後の段落（Library Checker）

- 問題：「長さの大きい列」が具体的でなく、なぜ動的セグメント木の確認になるのかが伝わりにくい（執筆者の未解決の点）
- 根拠：library-checker-problems の info.toml の params が `N_MAX = 1_000_000_000`・`Q_MAX = 500_000`。task.md は「$1 \le N \le$ N_MAX」
- 直し方：「長さ $N \le 10^9$ の一次関数の列への一点更新と区間の合成（$Q \le 5 \times 10^5$）」と書く。合成は順序に依存する（可換でない）ので、区間を左から右へ結ぶことにも一言触れるとよい。参考の行の「問題文は GitHub の library-checker-problems で読んだ」に制約もそこで確かめた旨を足す

### 4. 直すとよい｜分かりやすさ（U4）・事実（F2）｜#top-k-sum の手順 3 と #index-by-value の「保つ性質」

- 問題：(a) 手順に「$0 \le K \le$ 全体の個数」の前提がない（コード片のコメントにだけある）。(b) `max_right` が $r = N$ を返すと $\mathrm{vals}[r]$ は配列の外になる。これが起きるのは $c = K$ のときだけで、そのとき「$K = c$ なら $s$」で済むが、本文からはその理由が読み取れず、読者は $\mathrm{vals}[r]$ を先に読む実装を書きうる（コード片は `rest == 0` で先に返しているので正しい）。(c) #index-by-value の「$[l, r)$ は $\mathrm{vals}[l]$ 以上 $\mathrm{vals}[r]$ 未満」も $r = N$ で $\mathrm{vals}[N]$ が存在しない
- 根拠：突き合わせで $k =$ 全体の個数の質問（$r = N$）を作って確かめた
- 直し方：手順の前に「$K$ は集合の個数以下とする」と置き、手順 3 に「$r = N$ になるのは $c = K$ のときだけなので、$K = c$ を先に判定してから $\mathrm{vals}[r]$ を読む」と足す。(c) は「（$r = N$ なら上限なし）」と添える

### 5. 直すとよい｜分かりやすさ（U3）｜#dynamic-segment-tree の「先にオフラインを考える」

- 問題：「動的セグメント木が要るのは、先読みが禁じられた（オンライン強制の）問題か、添字が $10^{18}$ のように大きく、しかもクエリが後から来る場合である」の後半が、前半とどう違うのか分からない。「クエリが後から来る」が先読みできないという意味なら前半に含まれ、先読みできるなら $10^{18}$ でも座標圧縮で済む。また「オンライン強制」の語はここで初めて出るのに、見分け方のある [offline-queries の #online](../ds/offline-queries.md#online) へのリンクがない（#index-by-value の「前の答えで次の入力が決まる問題では先読みができない」の文も同じ）
- 直し方：後半を削るか、「対話の問題のように、入力を先に全部は読めない場合」など前半と区別できる具体例に言い換える。「オンライン強制」の初出を offline-queries#online へリンクする（用語集への提案「オンライン強制」を採るなら用語集でもよい）

### 6. 直すとよい｜コード（C3）・分かりやすさ（U4）｜#dynamic-segment-tree の本文とコード片 dynamic-odd-sum

- 問題：(a) 本文は「値域 $[0, C)$ 全体を根にして」と書くが、コード片は `[LO, HI) = [1, 10^9 + 1)`。$C$ との対応（$C = \mathrm{HI} - \mathrm{LO}$）が本文から読めない。(b) 本文は「1 回の更新と取得は $O(\log C)$」「取得では単位元を返す」と書くが、区間の取得の手順はどこにもない（コード片は根の値を読むだけ）。個数や和を区間で取りたい読者が、ここから実装に移れない
- 直し方：(a) 「値域を半開区間 $[\mathrm{LO}, \mathrm{HI})$ とし、$C = \mathrm{HI} - \mathrm{LO}$」と本文で一言書く。(b) 取得の手順を 1〜2 行足す（「ノード $v$ の区間 $[l, r)$ が質問の区間の外なら単位元、内に含まれれば $v$ の値、そうでなければ左右の子の結果を左・右の順に結ぶ。$v = 0$ なら単位元を返す」）

### 7. 直すとよい｜分かりやすさ（U3）｜#top-k-sum の見出しと最後の 2 段落

- 問題：(a) 見出しは「上位 K 個の和」だが、手順はすべて「小さい方から $K$ 個」で、「大きい方」への読み替えは 4 段落後に出る。冒頭だけ読む読者は「上位」がどちらを指すのかで止まる。(b)「BIT 上の二分探索で境界を探しても同じ計算量」の「BIT 上の二分探索」は、前提のページ（segment-tree・coordinate-compression）にない。fenwick-tree に #binary-search、kth-element に BIT 上の二分探索の手順の節がある
- 直し方：(a) 節の最初の段落に「ここでは小さい方から $K$ 個を求める。大きい方（上位）から $K$ 個は全体から引けば求まる（後述）」と 1 文置く。(b)「BIT 上の二分探索」を [fenwick-tree の #binary-search](../ds/fenwick-tree.md#binary-search) へリンクする

### 8. 直すとよい｜分かりやすさ（U5・U10）｜#index-by-value の「必要になる場面」

- 問題：「$j < i$ かつ $A_j \le A_i$ の個数を、左から順に入れながら BIT の接頭辞の和で読む」という導入は、同じ水の [fenwick-tree の #count-by-value](../ds/fenwick-tree.md#count-by-value) とほぼ同じ例・同じ説明である（あちらは「個数と和を両方持つ」も型として挙げている）。このページから入る読者には要るが、BIT のページとのつながりが示されていない
- 直し方：例は残してよいが、「BIT のページの[値を添字にして数える](../ds/fenwick-tree.md#count-by-value)と同じ形で」とリンクし、説明をこのページの新しい点（個数と和の 2 本・`upper_bound` と `lower_bound` の使い分け・クエリの値の圧縮）に寄せて短くする。座標圧縮の段落も [coordinate-compression の #with-ds](../basics/coordinate-compression.md#with-ds) へ節でリンクするとよい

### 9. 直すとよい｜事実（F5）｜#challenge の ABC287 G の要約（台帳の summary）

- 問題：「得点ごとの枚数を更新しながら」は、得点ごとに枚数があるように読める。kmjp の記事（台帳の evidence）では、カードは $N$ 種類で、クエリは「1 つの種類の得点を変更」「1 つの種類の使用可能枚数を変更」「計 $X$ 枚選ぶときの得点の総和の最大」。得点そのものも変わる。本文の方針（「得点や枚数の変更は古い分を引いて新しい分を足す」）は正しい
- 直し方：台帳の abc287_g の summary を「カードの種類ごとの得点と枚数を更新しながら、$X$ 枚選んだときの得点の和の最大を答える。」のように直す提案にする（§13.7。本文の行は fix_problems で作り直す）

### 10. 直すとよい｜図（G3・G5）｜count-sum-tree.svg

- 問題：(a) 幅 680 の図を 358px に縮めると、ノードの値（14px）が約 7.4px、ラベル（12px）が約 6.3px になり、スマホでは読みにくい。(b) 図の中の $10^9$ が「10^9」と ASCII のキャレットのまま。(c) 図の題名の行と代替テキストは多重集合を {5, 1, 5, 9, 10^9}、本文の #top-k-sum は $\{1, 5, 5, 9, 10^9\}$ と、並びが違う（同じ集合なので誤りではない）
- 直し方：(a) ノードの値とヒストグラムのラベルを 16〜18px に上げる（ノードの箱は横に余裕がある）か、根と葉の大きな値を「10⁹ + 20」のように短くして文字を大きくする。(b) `10<tspan baseline-shift="super" font-size="9">9</tspan>` か「10⁹」にする。(c) 本文の並びに合わせるとよい

### 11. 直すとよい｜図（G7）｜catalog の visual と図の範囲

- 問題：catalog の visual（static・priority 2）の text は「横軸を値にしたヒストグラムとセグ木を重ねる。動的セグ木は必要になったノードだけが作られた木」で、後半の動的セグメント木の図がない。priority 2 なので必須ではない
- 直し方：余力があれば、値域 $[0, 8)$ に 2〜3 個の値を入れたとき作られたノードだけを実線、作っていないノードを薄い破線で描く図を #dynamic-segment-tree に足す。足さないなら、そのままでよい

## メインへの申し送り（指摘ではない）

- 執筆者の台帳の提案（abc339_e の evidence から abl_d の drken の記事を外す、abc281_e の題名の末尾の空白）は妥当。`ap.py show abc281_e` の題名にも末尾の空白がある
- abc403_g の approach の evidence について：kmjp の記事は想定解が動的セグメント木であることだけを述べ、ノードの中身は書いていない（執筆者の報告どおり）。本文の（個数, 奇数番目の和, 偶数番目の和）の結合は、この検証で式と突き合わせにより確かめた
- 台帳の `checked` に 2026-10-21 を入れる提案：abc403_g・abc287_g（kmjp）、abc339_e（programming-hiroba）、abc281_e・abl_d（drken）、abc276_f（gotoki_no_joe）。いずれも evidence の解説で問いと方針を確かめた
- 執筆者の手引きへの提案（「ACL では」の囲みの置き場所、使い方のページでの 3 つの小見出しの置き方）はメインの判断事項

## 総合の判定

小さな直しで可。直すべき 1 件（動的セグメント木のノード数・メモリの見積もり）、直すとよい 10 件。コード片 3 本はサニタイザ付きの突き合わせで正しく、定理・結合の式・ACL の使い方に誤りはない。
