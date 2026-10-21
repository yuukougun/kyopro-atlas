# union-find の検証（工程8b・b1）

- 対象：docs/ds/union-find.md、snippets/union-find/{own-dsu,acl-cycle}.{cpp,yaml}、docs/img/union-find/path-compression.svg、埋め込みの動く図の置き場（data-viz="union-find"。JS は未作成）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page union-find`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/union-find`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/ds/union-find.md`（0 errors・4 warnings。執筆者の報告どおり 39 行 sentence-length・98 行 max-comma・223／224 行 no-doubled-joshi で、前 2 つは誤検出、後 2 つは台帳の summary 由来）
- front matter：変わったのは complexity・stage・sections への next-steps の追加。complexity・要点の計算量（44 行）・本文（121〜125 行）が一致し、ならしと最悪（union by size だけ）の区別も書かれている
- ACL（F4）：~/lib/ac-library-master/document_ja/dsu.md と照らした。merge・same・leader・size はならし $O(\alpha(n))$、groups は $O(n)$ で順は未定義、添字の制約 $0 \le a < n$（assert）、merge の戻り値は代表元。third_party/ac-library/atcoder/dsu.hpp の 24 行 `if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);` で、同じ大きさなら a 側の根が残る（本文 106 行・own-dsu の比べ方と一致）
- コード片（C1〜C8）：2 片とも `-fsanitize=address,undefined -I third_party/ac-library` 付きで cases を動かし報告なし。own-dsu を、乱数の操作列（n ≤ 8、300 通り）で素朴な成分のラベル付けと比べて一致（作業用の場所 v-union-find/rnd.py）。cases は図の例・1 要素・自分との併合・同じグループの併合の繰り返し・質問だけを含み、期待出力を手で数え直して正しい。acl-cycle の cases（三角形と孤立点 → 1 2、辺なし → 0 3、自己ループ → 1 1、多重辺 → 2 1）も手で正しい。assert で groups の数・extra + merged = m を確かめている。書き方（bits・using namespace std・マクロなし・`'\n'`）は §9 に合う。取り込みは core の範囲だけ。本文の擬似コード（81〜94 行）とコード片の par・比べ方・足し方が 1 行ずつ対応する
- 図の例の値（F3）：merge(0,1)・(2,3)・(0,2)・(4,5)・(6,7)・(4,6)・(0,4) を手で追い、find(7) の前の par = [−8, 0, 0, 2, 0, 4, 4, 6]、後の par = [−8, 0, 0, 2, 0, 4, 0, 0]。図・代替テキスト・本文 100・106・172 行（3 の親は 2、5 の親は 4）と一致。最後の併合の直前は 0 の木・4 の木とも大きさ 4・深さ 2 で、併合後の深さ 3 も正しい
- 自分で導いた主張を小さなプログラムで確かめた（v-union-find/depth.py）
    - union by size で、どの時点でも最大の深さ ≤ $\log_2 N$（n ≤ 300 の乱数の併合 2000 通り）。n = 16 で倍々に併合すると深さ 4 = $\log_2 16$ に達し、上限は等号まで届く
    - 確認問題 (1)：大きさを見ずに `par[find(b)] = find(a)` とつなぐと、merge(i, i−1) を順に呼ぶだけで、find が根だけをたどるので圧縮が効かず、深さ $N - 1$ の鎖ができる（n = 10 で深さ 9）。執筆者の未解決の点 3 の「一時的に深い鎖ができうる」は成り立つ
    - 確認問題 (2) の $2 \times 10^5 \times 18 = 3.6 \times 10^6$（本文「約 $4 \times 10^6$」で可）、141 行の $(10^5)^2 = 10^{10}$
    - 140 行・210 行の「閉路を作る辺の数 = $M - (N - C)$」：併合の成功回数が $N - C$ なので成り立つ（acl-cycle の assert でも確かめている）
- 計算量の事実（執筆者の未解決の点 2）：cp-algorithms の DSU の記事で「経路圧縮だけで 1 回あたり平均 $O(\log n)$」「union by size／rank だけで $O(\log n)$」「両方でならし $O(\alpha(n))$」「$\alpha$ は $n < 10^{600}$ 程度まで 4 以下」を確かめた。drken の practice2_a の記事にも「$N \le 10^{80}$ で $\alpha(N) \le 4$」とある。本文の「$10^{80}$ 程度でも 4 以下」は両方と矛盾しない。union by rank でも同じ上限、経路圧縮だけでならし $O(\log N)$ は Tarjan・van Leeuwen の結果として知られており、本文の主張は正しい
- 参考の URL（F9）：8 件のうち ACL の document_ja はローカルの写しで、残り 7 件を開いた。drken（practice2_a・abc177_d・abc206_d・abc157_d）・kyo-pro（abc288_c・abc292_d）・E869120（typical90 012 の解答例）とも題名・内容が書かれたとおり。どれも付録 B のドメイン。本文の文・例は資料と並びも数値も違い、近すぎる箇所はない（F8）
- 問題（F5）：7 問とも `python3 tools/ap.py show` で題名・diff が本文と一致（abc288_c 436・abc292_d 579・abc177_d 732・abc206_d 879・abc157_d 1208・typical90_l なし・practice2_a なし）。例題・練習の方針は evidence と食い違いがない。abc292_d は kyo-pro の記事が「各辺を片方の端で数え、最後に根へ足し込む」形で、本文 164 行・231 行の両方の書き方と一致。typical90 012 は解答例でも行優先の番号 $(x-1)W + (y-1)$、判定の前に 2 マスとも赤かを見ている。台帳の `checked` に 2026-10-21 を入れてよい（abc288_c・abc177_d・abc206_d・abc157_d。abc292_d は確認済み）
- 図 path-compression.svg：headless の Chrome（chrome-headless-shell 146、puppeteer のキャッシュ）で、等倍（760×432）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（v-union-find/full.png・narrow.png）。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、色に加えて破線（たどった道）と実線（つなぎ直した辺）で区別。値は上のとおり本文と一致。はみ出しはない。気になった点は指摘 4・5
- リンク先：本文のリンク先 14 ページはすべてある（rollback-union-find は stub で §13.4 によりよい）。用語集の #representative・#amortized-complexity はまだない（申し送り）
- 執筆者の未解決の点：(1) 図は上のとおり描画して確かめた（指摘 4・5）。(2) 計算量の事実は cp-algorithms と drken で確かめた。(3) 鎖ができることは小さなプログラムで確かめた

## 指摘

直すべき指摘はない。以下はすべて「直すとよい」。

### 1｜直すとよい｜分かりやすさ（U3）｜保つ性質の節 75 行

- 問題：「大きさを根にだけ持ち、根以外の要素には持たせない点が大事である。根以外の値は、併合のあとで古くなっても直されない」。配列 par 1 本の形では、根以外の要素の値は親の番号で、大きさは持っていない。「古くなっても直されない根以外の値」が何を指すのか（親の番号か、別の配列の大きさか）が読み取れず、「親の番号が古くなる」と誤解しうる
- 根拠：71〜72 行の性質では、根以外の $\mathrm{par}[v]$ は親であり、大きさの値は根にしかない
- 直し方：例として「大きさを別の配列 $\mathrm{sz}$ に持つ書き方でも、正しいのは根の値だけである。根でなくなった要素の $\mathrm{sz}$ は併合のあとで直されないので、大きさは必ず $\mathrm{find}$ で根を求めてから読む」のように、何の値の話かを明示する

### 2｜直すとよい｜事実（F2）・分かりやすさ（U2）｜境界の節 137 行

- 問題：$x = y$ のまま併合したときの害として「根が自分を指し、大きさが消える」とあるが、より直接の害である「その後の $\mathrm{find}$ が終わらない（$\mathrm{par}[x] = x \ge 0$ なので自分を親としてたどり続け、再帰が無限に続く）」が書かれていない。読者がバグの症状（TLE・スタックあふれ）から原因に戻れない
- 根拠：own-dsu の find は `par[v] < 0` で止まる。$\mathrm{par}[x] = x$ なら `find(x)` は `find(x)` を呼び続ける
- 直し方：「…大きさが消え、以後の $\mathrm{find}(x)$ は自分をたどり続けて止まらない」と足す

### 3｜直すとよい｜分かりやすさ（U7）｜練習の方針 232 行（ABC177 D）と 222 行の要約

- 問題：方針の「同じ連結成分の人は全員が互いに友達なので」は、問題文の「友達の友達も友達」という条件に依っているが、ページの要約（catalog・台帳の alternatives の summary）からその条件が落ちている。要約だけを読んだ読者には、なぜ全員が友達になるのかが分からない
- 根拠：台帳の主の summary は「友達の友達も友達とみなすとき」を含む（data/problems.yaml 3324 行付近）。drken の記事も、友達関係を無向グラフと見て最大の連結成分の大きさを答えにしている
- 直し方：本文の方針で「問題文から、友達の友達も友達になる。だから同じ連結成分の人は全員が互いに友達で、…」と条件を明示する。あわせて台帳（alternatives の union-find 向け summary）に「友達の友達も友達とみなすとき、」を足す提案をメインに上げる

### 4｜直すとよい｜図（G3）｜path-compression.svg の下の文字

- 問題：幅 358px に縮めると全体が 0.47 倍になり、下の凡例（font-size 13）は約 6px、par の行（14）は約 6.6px で、スマホでは読みにくい。上の題（15）も約 7px
- 根拠：v-union-find/narrow.png を目で見た
- 直し方：凡例の 2 行と par の 2 行は代替テキストと本文 100 行に同じ内容があるので致命的ではない。文字を 16〜18 に上げるか、左右の 2 枚を縦に並べた形（viewBox を縦長に）にすると、縮んでも読める

### 5｜直すとよい｜図（G5）｜path-compression.svg 右側の根 0 の周り

- 問題：赤い矢印は stroke-width 3 で、marker の既定（markerUnits="strokeWidth"）により矢じりが黒の 2 倍の大きさになる。右側では 6→0・7→0 の赤い矢じりと 2→0・1→0 の黒い矢じりが根 0 の右下に集まり、重なって見える。左側の 4→0・6→4 の矢じりも大きく、頂点 4 の円に少しかかる
- 根拠：v-union-find/full.png を目で見た
- 直し方：赤の marker に `markerUnits="userSpaceOnUse"` と黒と同じ大きさ（例：markerWidth・markerHeight を 10 前後）を指定するか、赤の marker の markerWidth・markerHeight を 3.5 にする

### 6｜直すとよい｜事実（F4）｜ACL では の囲み 115 行

- 問題：「`d.merge(a, b)`（新しい代表元を返す）」。ドキュメントでは、もともと連結ならその代表元を返す。「新しい」と書くと、連結のときの値が分からない
- 根拠：document_ja/dsu.md の merge「$a, b$ が連結だった場合はその代表元、非連結だった場合は新たな代表元を返します」
- 直し方：「併合したあとの代表元を返す（もともと同じなら、その代表元）」とする

### 7｜直すとよい｜記法（F7）｜「大きさ」と「サイズ」の揺れ

- 問題：本文は「大きさ」でそろえているが、sections の見出し（「parent は根なら −(サイズ)」「根にサイズ・辺数を持たせる」「サイズの積のあふれ」）・ACL の囲み「−(サイズ)」・own-dsu.cpp のコメント「サイズを足す」と、本文の境界の節の見出し語「大きさの積のあふれ」とで用語が揺れる。また sections の invariants の title は「parent」だが、本文・コードは `par`
- 直し方：front matter の title は執筆者の担当外なので、メインに「大きさ」へそろえるか、どちらを正規形にするかを決めてもらう。コード片のコメントと ACL の囲みは本文に合わせて「大きさ」にするとよい

### 8｜直すとよい｜分かりやすさ（U4）｜境界の節 141 行

- 問題：「積と合計は `long long` で計算する」とあるが、`long long ans += d.size(a) * d.size(b);` のように右辺が `int` どうしの積だと、代入の前にあふれる。この型の読者がちょうど踏む誤り
- 直し方：「`(long long)d.size(a) * d.size(b)` のように、掛ける前に片方を `long long` にする」と一言足す

## メインへの申し送り（指摘の数には入れない）

- 用語集の #representative（67 行）・#amortized-complexity（123 行）はまだ docs/guide/glossary.md にない。mkdocs.yml は `validation.anchors: warn` で `--strict` なので、執筆者の用語集への提案を反映しないとビルドが落ちる
- 動く図 union-find（catalog の visual は dynamic・priority 1）の JS と試験はまだない。102〜106 行の文章は図がなくても通じる（静的な図と同じ最後の状態を文章でも述べている）が、JS ができるまでは div が空のまま出る。執筆者の仕様（a 側の根を残す、最後の状態が svg の右側と一致）は dsu.hpp の比べ方と一致することを確かめた
- 執筆者の手引きへの提案（next-steps を定型の見出しにするか、choosing と comparison のどちらにそろえるか）は、binary-search の検証と同じ論点

## 総合の判定

小さな直しで可。直すべき指摘は 0 件、直すとよい指摘は 8 件。事実・計算量・ACL の使い方・コード片・図の値に誤りは見つからなかった。
