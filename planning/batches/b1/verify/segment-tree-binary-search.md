# segment-tree-binary-search の検証（工程8b・b1）

- 対象：docs/ds/segment-tree-binary-search.md、snippets/segment-tree-binary-search/{first-at-least,kth-one,own-max-right,lazy-monotone}.{cpp,yaml}、docs/img/segment-tree-binary-search/climb-descend.svg（動く図はない。catalog の visual は priority 2 なので静的な図で代えてよい）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page segment-tree-binary-search -v`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page segment-tree-binary-search --check`（直すべき行 0）、`python3 tools/check_snippets.py snippets/segment-tree-binary-search`（4 片・コンパイル 4 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/ds/segment-tree-binary-search.md`（0 errors・33 warnings。半開区間 $[l, r)$ の括弧の対応・数式を含む文の長さ・助詞の重複で、§13.8 により残してよい）
- コード片：4 片とも `-fsanitize=address,undefined -Wall -Wextra` で cases を動かし、出力一致・報告なし。cases の期待出力を手で数え直した（first-at-least の 4・5・8・7・2、kth-one の 0・3・−1・6、lazy-monotone の 1 4 4 6 7）。どれも素朴な方法と `assert` で比べ、cases に 1 要素・$l = N$・見つからない場合を含む。書き方（bits・using namespace std・マクロなし・`long long`・`'\n'`・ラムダは判定の関数）は §9 に合う。取り込みの範囲（core・left）は要点だけ
- ACL v1.6：~/lib/ac-library-master/document_ja/segtree.md・lazysegtree.md と atcoder/segtree.hpp・lazysegtree.hpp を読んだ。返り値の定義（「$r = l$ もしくは真」「$r = n$ もしくは偽」、単調なら最大の $r$）、要件（副作用なし・`f(e()) = true`・$0 \le l \le n$）、計算量 $O(\log n)$、`l == _n` で `_n` を返すこと、lazy_segtree も同じ約束で降りながら push すること：本文 57〜79・86・162・181 行と一致
- 自分で導いた主張を小さなプログラムで確かめた（作業用の場所 v-segment-tree-binary-search/t.cpp、サニタイザ付き）
    - 図と本文 103〜109 行の手順（列 3 1 4 1 5 9 2 6、$l = 1$、$x \le 12$）を segtree.hpp の手順で手で追い、訪れる順・累積 1 → 6 → 28（偽）→ 20（偽）→ 11 → $r = 5$ が一致。図のノードの値（31・9・22・4・5・14・8）も一致
    - 自作の再帰版（own-max-right の core）と ACL の `max_right` を、$N \le 40$ の乱数 2 万回で素朴な方法と比べて一致。$f$ の呼び出しは最大 11 回（段の数 7）で、$O(\log N)$ の主張（111・127 行）と合う
    - mex の型（値 $0..N$ の個数の min の木で `max_right(0, c > 0)`）：乱数 2 万回で素朴な mex と一致
    - 登る段階で足すノードの段が毎回上がる理由（`while (l % 2 == 0)` の後は l が奇数なので、`l++` で偶数になり必ず 1 段以上登る）、降りた先の葉が境目になること、余りの葉で止まらないことを確かめた（111・117 行は正しい）
    - lazy の節：$[L, R]$ に $+1$ しても広義単調増加が保たれる（189 行）。値 $< L$ は $\le L - 1$、$[L, R]$ は $[L + 1, R + 1]$、$> R$ は $\ge R + 1$ なので成り立つ
    - 確認問題の 2 つの直し方（（和, 接頭辞の和の最大値）の組、累積和の min の木で `min_left`）、gcd の $f(g) = (g \ne 1)$ の単調性、BIT への言い換え（298 行）、$\log^2 N \approx 324$・$6.5 \times 10^7$ は正しい
    - `INT_MIN + 1` は −2147483647 で、あふれない（指摘 2）
- 問題：7 問とも `python3 tools/ap.py show` で題名・diff が台帳・本文と一致（practice2_j は diff なし）。役割と数は catalog・台帳と一致。evidence を読んだもの：
    - practice2_j（drken）：$1 \le N, Q \le 2 \times 10^5$、なければ $N + 1$、単位元 −1。本文と一致（ただし指摘 7）
    - abc307_f（drken）：（日, 距離）の辞書順のダイクストラ法と、X の max のセグメント木の `max_right` で「翌日以降で初めて $X \ge w$ になる日」を探す。本文の方針と一致（執筆者の未解決の点 1 は解決）
    - abc478_f（ikatakos 氏の解法の部分のコード・merom686 氏）：親の候補の範囲が本文と違う（指摘 3）。「自分より大きい値」は順列（訪問順）の値の大小で、本文の書き方で足りる（未解決の点 2 は、範囲を直せば解決）
    - abc382_c・abc392_f・abc330_e・abc389_f の evidence は今回は開いていない。方針は問題の構造から手で確かめ、矛盾はない（abc392_f の言い換えの理由、$1 \le P_i \le i$ のとき $r < N$ になること、abc330_e の mex $\le N$）
    - 台帳の `checked` に 2026-10-21 を入れてよい：practice2_j・abc307_f。abc478_f は指摘 3 を直した後に入れてよい
- 図 climb-descend.svg：Windows の Chrome（headless=new）で、等倍（680×470、2 倍密度）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（作業用の場所 v-segment-tree-binary-search/full.png・narrow.png）。値・訪れた順の番号・実線と破線の区別・$l = 1$ と $r = 5$ の印は本文と一致し、文字の重なり・はみ出しはない。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、色に加えて実線と破線で区別している（執筆者の未解決の点 3 は解決）
- リンク先：segment-tree・binary-search・kth-element・monotonic-stack・segment-tree-on-values・lazy-segment-tree・fenwick-tree・acl-reading は draft。acl-reading#capturing-lambda・glossary#identity-element はある。#choosing へのほかのページからのリンクはない（grep で確かめた）
- 参考の URL：drken 3 件・ikatakos・merom686 を開き、題名・著者・内容が書かれたとおり。ほかは開いていない（ドメインは付録 B か、執筆者が check_noai で確かめたもの）。本文の例（列 3 1 4 1 5 9 2 6）と文の並びは、読んだ資料と近すぎない

## 指摘

### 1｜直すべき｜手引き（§13.1）｜front matter の sections と「落とし穴」「使い分け」の見出し（30〜31 行・171 行・285 行）

- **問題**：「落とし穴」「使い分け」は定型の節なので sections に載せず、見出しを `## 落とし穴 {#pitfalls}`・`## 使い分け {#comparison}` にする決まり（§13.1。上の各節より優先）だが、sections に `anchor: choosing`・`anchor: pitfalls` の行があり、見出しが長く、使い分けの anchor が `choosing` になっている。執筆者も「手引きへの提案」で迷った点として挙げている
- **根拠**：style-guide §13.1・§13.2。binary-search の検証の指摘 1 と同じ型
- **直し方**：sections から 2 行を消し、見出しを `## 落とし穴 {#pitfalls}`・`## 使い分け {#comparison}` にする。#choosing はほかのページから参照されていないので、anchor を変えても壊れるリンクはない（§2.1 の「既存の anchor は変えない」との関係はメインが判断する）

### 2｜直すべき｜fact（F2）｜#boundaries の「単位元に算術をしない」の例（168 行）

- **問題**：「max の単位元を `INT_MIN` にした `int` の木で $f(v) = (v + 1 \le x)$ … あふれる」は誤り。`INT_MIN + 1` は −2147483647 で、あふれない。あふれるのは `INT_MIN - 1` や `x - INT_MIN`（$x \ge 0$）の向き
- **根拠**：t.cpp で `INT_MIN + 1` を出力して −2147483647
- **直し方**：例を「min の単位元を `INT_MAX` にした `int` の木で $f(v) = (v + 1 \le x)$」にするか、「max の単位元を `INT_MIN` にして $f(v) = (x - v > 0)$」にする

### 3｜直すべき｜fact（F5）｜練習の方針 ABC478 F（252 行）と台帳への提案

- **問題**：「親になれるのは、自分より前で最も近い『自分より大きい値』の後ろから自分の直前まで」は、範囲の左端を 1 つ取り違えている。evidence では、最も近い大きい値の位置そのものも親の候補に入る。ikatakos 氏のコードは `j = min_left(i, a < q)` で、候補の数を `i - j + 1`（位置 $j - 1$ から $i - 1$ まで）としている（`j == 0` なら `i`）。merom686 氏も「初めて大きい値が出てくる所まで（その位置を含む）」と書いている。台帳への提案の approach（「自分より大きい値の直後」）も同じ誤り
- **根拠**：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/1003_abc478 （解法のコードだけを読んだ）、https://merom686.hatenablog.com/entry/2026/10/04/013441
- **直し方**：「自分より前で最も近い『自分より大きい値』の位置から自分の直前までの連続した範囲になる（大きい値がなければ前のすべて）。その位置は max のセグメント木の `min_left` の返り値の 1 つ左として求まる」とする。台帳への提案の approach も「最も近い大きい値の位置から」に直す

### 4｜直すべき｜fact（F2・F4）｜#pitfalls の「$f$ に副作用を持たせる」（177 行）

- **問題**：「ACL は同じノードの値で $f$ を何度も呼ぶので」は segtree.hpp の手順と合わない。登る段階でも降りる段階でも、各ノードについて $f$ を呼ぶのは 1 回だけ。ほかに呼ぶのは `assert(f(e()))` の 1 回だけである。避けるべき理由（呼ぶ回数・順序・引数が手順で決まり、要素ごとには呼ばれない）は正しい
- **根拠**：~/lib/ac-library-master/atcoder/segtree.hpp 72〜94 行。t.cpp で数えた呼び出し回数
- **直し方**：「ACL は $f$ を `assert(f(e()))` で 1 回と、木のノードの累積ごとに呼ぶ。呼ぶ回数・順序・引数は木の形で決まり、要素の数とも真になった区間とも対応しない」とする

### 5｜直すとよい｜fact（F2）・clarity（U3）｜導入（51 行）の「根から葉への 1 本の道」

- **問題**：本文が説明する ACL の手順（92〜95 行）は、葉 $l$ から登って降りる。導入の「根から葉への 1 本の道で見つける」と食い違い、図を見た読者が戸惑う。再帰版でも、訪れるのは葉 $l$ への道と右側の丸ごと足すノードと降りる道である（127 行）
- **直し方**：「ノードの集約値を使い、木を登って降りる $O(\log N)$ 個のノードだけを見て見つける」のようにする

### 6｜直すとよい｜fact（F2）｜#complexity の「右隣が列の右端を超えたら」（94 行）

- **問題**：ACL が $N$ を返す条件 `(l & -l) == l` は、木の葉の右端（$\mathrm{size}$。余りの葉を含む）を超えたことで、列の右端 $N$ ではない。117 行で余りの葉が $e$ であることは述べているが、94 行だけ読むと $N$ で止まるように読める
- **直し方**：「右隣が木の右端（余りの葉を含む）を超えたら、すべて足しても真だったので $r = N$ を返す」とする

### 7｜直すとよい｜fact（F5）｜例題 PRACTICE2 J の解法の詳細（221 行）

- **問題**：「max の単位元は $V$ より小さい値（値が 1 以上なら −1 など）」の条件の書き方がずれている。−1 が使えるのは値（$A_i$・$V$）が 0 以上だからで、「1 以上」は要らない条件に読める。drken 氏の記事のコードも −1 を使う
- **直し方**：「max の単位元は、すべての $A_i$ と $V$ より小さい値にする。値が 0 以上なので −1 でよい」とする（問題の制約の値の範囲は問題文で確かめていないので、メインが ap.py かほかの解説で確かめる）

### 8｜直すとよい｜F7（§6）｜#kth-one の閉区間（148 行）と kth-one.cpp のコメント

- **問題**：「$[l, r]$ にすると $K$ 個に達する」「[l, r] にちょうど k 個」は閉区間だが断りがない（§6「閉区間は明記する」）
- **直し方**：「閉区間 $[l, r]$」と書くか、半開区間で「$[l, r + 1)$」とする

### 9｜直すとよい｜clarity（U3）｜#what-it-does の `min_left` の定義（63 行）

- **問題**：`max_right` は返り値の正確な定義（59 行）と「単調なら最大の $r$」を分けているのに、`min_left` は「最小の $l$ を返す」とだけ書き、単調でないときの意味がない。#pitfalls の単調でない条件の話が `min_left` にも当てはまるかが読み取れない
- **直し方**：「$l = 0$ か $f(\mathrm{prod}(l - 1, r))$ が偽、かつ $f(\mathrm{prod}(l, r))$ が真の $l$ を返す。$f$ が単調なら最小の $l$」と対にする

### 10｜直すとよい｜clarity（U3）・F7｜例題 ABC392 F の方針（231 行）の `max_right(0, s < P_i)`

- **問題**：関数の代わりに式を引数に書いた形で、ACL の呼び方として読むと誤る
- **直し方**：「$f(s) = (s < P_i)$ で `max_right(0, f)`」と、解法の詳細（236 行）と同じ書き方にする

### 11｜直すとよい｜clarity（U6）｜BIT 上の二分探索へのリンク（238 行・291 行）

- **問題**：「BIT 上の二分探索」をどちらも fenwick-tree.md のページの先頭へリンクしているが、fenwick-tree には節 `#binary-search`（draft で見出しあり）がある
- **直し方**：`../ds/fenwick-tree.md#binary-search` にする

### 12｜直すとよい｜figure（G3・G5）｜climb-descend.svg と代替テキスト

- **問題**：(a) 幅 358px に縮めると、区間のラベル（font-size 11）が 6px ほどになり読みにくい（値と番号は読める）。(b) 代替テキストの「葉 [1, 2) と [2, 4) を足して」は、[2, 4) も葉と読める
- **直し方**：(a) 区間のラベルを 12〜13 にする（葉の幅 60 に収まる）。(b)「葉 [1, 2) とノード [2, 4) を足して」とする

## 提案（メイン向け）

- 台帳の `checked`：practice2_j・abc307_f に 2026-10-21。abc478_f は指摘 3 の直しの後
- 執筆者の台帳への提案のうち、abc478_f の approach は指摘 3 のとおり「最も近い大きい値の位置から」に直してから反映する。summary（「頂点 1 を根とする木のうち…」）は問題文を見ずには確かめきれなかった（ikatakos 氏の解法の部分では、訪問順の先頭が根であることと矛盾しない）

## 総合の判定

**小さな直しで可**（直すべき 4 件：sections と定型の見出し・単位元のあふれの例・ABC478 F の親の範囲・副作用の理由。どれも 1〜数文の直しで、手順・計算量・コード片・図の本体は正しい）
