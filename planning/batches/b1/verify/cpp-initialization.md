# cpp-initialization の検証（工程8b・b1）

- 対象：docs/cpp/cpp-initialization.md、snippets/cpp-initialization/（19 片）、docs/img/cpp-initialization/{nested,ctad-flow}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0、ACL は third_party/ac-library（~/lib/ac-library-master/atcoder と差分なし）。図は chrome-headless-shell 146 で描画（幅 760／840 の原寸と、幅 390 の画面に 358px で収めた場合）。この環境には日本語のフォントがなく、日本語は豆腐で出たので、日本語の文字の見た目は確かめていない（配置・はみ出し・線の種類は確かめた）

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page cpp-initialization`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/cpp-initialization`：19 片・38 回のコンパイルがすべて期待どおり
- 本文が引くエラー・警告の文面を g++-13・g++-15 で出し直し、一致を確かめた：`conversion from 'int' to non-scalar type 'atcoder::dsu' requested`、`designator order for field 'Edge::to' does not match declaration order in 'Edge'`、`designated initializers cannot be used with a non-aggregate type`、`no matching function for call to 'Edge::Edge(long long int)'`（-std=gnu++17）、`'s' may be used uninitialized`（-O2 -Wall -Wextra。`cnt` には警告なし）
- `-std=gnu++17 -Wall -Wextra` で指示付き初期化が黙って通ること、`-std=c++17 -Wpedantic` で警告が出ること
- `Edge{1.9, 2}` が `narrowing conversion of '1.8999999999999999e+0' from 'double' to 'int'` のエラーになり、`emplace_back(1.9, 2)` は `-Wall -Wextra` で警告 0 であること。`vector w{v.begin(), v.end()}` も警告 0
- uninit-ng を `-O2 -ftrivial-auto-var-init=zero` で動かすと 6001。付けないと毎回違う大きな値（例：102697273239592396、108593175476289564）
- ACL の `dsu`・`fenwick_tree`・`segtree`・`lazy_segtree`・`scc_graph`・`mf_graph`・`mcf_graph`・`two_sat` の大きさを取るコンストラクタに `explicit` があり、`static_modint(T v)` にはないこと（third_party/ac-library/atcoder/*.hpp）。`dsu` に既定のコンストラクタ（大きさ 0）があること
- 数値：0x3f3f3f3f = 1061109567（2 倍で 2122219134 < 2^31-1）、0x01010101 = 16843009、`sizeof(vector<int>)` = 24（手元）
- `vector c{v};` が `vector<int>` になる（コピーの推論が優先）ことを static_assert と cppreference の CTAD のページで確かめた
- 参考の 9 件の URL が開け、題名が書かれたとおりであること。cpprefjp の丸括弧の集成体初期化のページに縮小変換の記述があること。本文の例は資料の例と数値・形が違い、近すぎない（F8）
- catalog の visual（static・priority 2、入れ子の箱と CTAD の流れ）と 2 枚の図の内容が合う。図はどちらも背景を白で塗り、viewBox があり、文字はテキストのまま。線の種類（実線・破線・点線）とラベルで次元を区別していて、色だけに頼っていない
- 確認問題 4 問の答えは本文と合い、理由まで書かれている

## 指摘

### 1. 直すとよい｜fact（F2・F3）・clarity｜#global-vs-local の 111 行と 119 行

- 問題：「`-Wall -Wextra` は `s` について `'s' may be used uninitialized` と警告した」とあるが、この警告は最適化を付けたときにしか出ない。`-O2` を付けずに `-Wall -Wextra` だけでコンパイルすると、g++-13・g++-15 とも `s` についても何も出ない。読者が手元で最適化なしで試すと、本文と違う結果になる
- 根拠：`g++-15 -std=gnu++23 -Wall -Wextra uninit-ng.cpp` は警告 0。`-O2` を足すと `-Wmaybe-uninitialized` が出る（g++-13 も同じ）
- 直し方：「`-O2 -Wall -Wextra` では `s` について…と警告したが（`-O2` を付けないと `s` にも警告は出ない）、配列 `cnt` については何も言わなかった」とする。119 行の「版」も「`-O2` 付きで `s` だけを警告した」にそろえる

### 2. 直すとよい｜fact（F2）｜冒頭の 48 行

- 問題：「版は AtCoder の GCC 15.2（`-std=gnu++23`）と、手元の g++-13・g++-15 で確かめた」とあるが、AtCoder の上での確認はしていない（報告にもない）。確かめたのは手元の g++-15.2 である
- 根拠：執筆者の報告（planning/batches/b1/cpp-initialization.md）は g++-13・g++-15 での確認だけを挙げている。cpp-undefined-behavior は「手元の g++-13 と g++-15 で確かめた」と書き分けている
- 直し方：「手元の g++-13・g++-15（`-std=gnu++23`）で確かめた。AtCoder の GCC 15.2（`-std=gnu++23`）では、このページの書き方はすべて使える」とする

### 3. 直すとよい｜fact（F2）・code（C8）｜#refill の 205 行とコード片 refill.cpp の `fill(&grid[0][0], &grid[0][0] + 3 * 5, 7)`

- 問題：2 次元の C 配列を `&grid[0][0]` から 15 個進めるポインタの演算は、規格の上では `grid[0]`（5 要素）の範囲を超えるので未定義動作とされる（[expr.add] は同じ配列の中か末尾の次までしか認めない）。GCC では期待どおりに動き、よく使われる書き方ではあるが、このページは 113 行で「規格の上では未定義動作のままなので、初期化を書いて防ぐ」と言っており、立場がそろわない
- 根拠：C++ 規格 [expr.add]/4。g++-13・g++-15 では期待どおり 7 が入る（check_snippets が通る）ので、実害は確かめられていない
- 直し方：行ごとに埋める `for (auto& row : grid) ranges::fill(row, 7);` を主にし、`&grid[0][0]` の形は「よく見かけるが、規格の上では行をまたぐポインタの演算になる」と一言添える。または本文の説明（行の順に続いて並ぶ）を残すなら、厳密には保証されない旨を落とし穴に加える

### 4. 直すとよい｜clarity（U3）｜#aggregate-emplace の 164 行

- 問題：C++17 でのエラーとして `no matching function for call to 'Edge::Edge(long long int)'` を挙げているが、取り込んだコードは `emplace_back(1, 10LL)` と引数が 2 個なので、読者は「なぜ引数が `long long` 1 個なのか」で止まる。実際は直前に `new initializer expression list treated as compound expression` が出ていて、丸括弧の中の `1, 10LL` がカンマ演算子として 1 個の値 `10LL` にまとめられたためである
- 根拠：g++-13・g++-15 の `-std=gnu++17` の出力の 1 行目が `new initializer expression list treated as compound expression [-fpermissive]`、2 行目が上の文面
- 直し方：「`new initializer expression list treated as compound expression`（丸括弧の中がカンマ演算子として 1 つの値に読まれる）に続いて `no matching function for call to 'Edge::Edge(long long int)'` などのエラーになる」とする

### 5. 直すとよい｜figure（G3）｜nested.svg・ctad-flow.svg

- 問題：幅 760・840 の図を幅 390 の画面（本文の幅 約 358px）に収めると、約 0.43〜0.47 倍に縮み、13px の文字が 6px 前後になって読めない。とくに nested.svg の 1 行目のコードと、ctad-flow.svg の右側の注記（12px）
- 根拠：chrome-headless-shell で 358px 幅に縮めた画像を目で確かめた
- 直し方：nested.svg は cnt[0] と cnt[1] を縦に並べて幅を 400 前後にする（1 行目のコードは 2 行に折る）。ctad-flow.svg は右の注記を箱の下に移すか消して幅を 600 前後にする。どちらも文字を 14〜16px にする。ほかにも、ctad-flow.svg の最下行の赤い文（y=238）が最下段の箱（下端 228）と下の縁（250）に詰まっているので、高さを 270 程度に広げるとよい。矢印の頭（marker が線の太さで拡大され約 20px）も小さくするとよい

### 6. 直すとよい｜fact（F7）・process｜#designated-init の 148 行、#aggregate-emplace の 165 行の用語集のリンク

- 問題：`../guide/glossary.md#aggregate` と `../guide/glossary.md#narrowing-conversion` は、今の用語集にない（執筆者の「用語集への提案」が反映されて初めてつながる）
- 根拠：`grep -n 'aggregate\|narrowing' docs/guide/glossary.md` が 0 件
- 直し方：メインがバッチの終わりに用語集へ 2 語を足す。足さない場合はリンクを外す

### 7. 直すとよい｜fact（F2）｜用語集への提案「縮小変換」の文（ページの外。メインへの申し送り）

- 問題：提案の定義の「波括弧の初期化ではコンパイルエラーになる」は、GCC では定数のときだけ成り立つ。変数の `double` を波括弧で `int` のメンバへ入れると、GCC は警告（`-Wnarrowing`）だけでコンパイルを通す。規格の上では不適格（ill-formed）である
- 根拠：`double x; cin >> x; Edge e{x, 2};` は g++-13・g++-15 とも `warning: narrowing conversion of 'x' from 'double' to 'int' [-Wnarrowing]` でコンパイルが通る。`Edge{1.9, 2}` はエラー
- 直し方：「波括弧の初期化では規格の上で許されず、GCC は定数ならエラー、変数なら警告を出す」とする。本文 165 行（定数 `1.9` の例でエラー）はこのままで正しい

### 8. 直すとよい｜fact（F2）｜#global-vs-local の 103 行

- 問題：「関数の中で宣言した `int`・`long long`・C 配列・`array` は、初期化を書かないと値が決まらない」は、`static` を付けた局所変数を除く必要がある（静的記憶域なので 0 で初期化される）
- 根拠：cppreference「Zero-initialization」。`static int z[3];` を関数の中に置くと 0 が出た（g++-13・g++-15）
- 直し方：「関数の中で（`static` を付けずに）宣言した…」と括弧で足す。解説コードで関数の中の `static` 配列を見ることがあるので、一言あると誤解を防げる

### 9. 直すとよい｜clarity（U9）｜#designated-init の 147 行

- 問題：警告の文面を `C++ designated initializers only available with '-std=c++20'` で切っているが、実際は `… with '-std=c++20' or '-std=gnu++20'` まで続く。検索して照らす読者のために全文がよい
- 根拠：g++-13・g++-15 の `-std=c++17 -Wpedantic` の出力
- 直し方：`… only available with '-std=c++20' or '-std=gnu++20'` と全文にする

## 執筆者の未解決の点について

- 未初期化の値の例（105842398323404453）：「のような値」と書いてあり、実行ごとに変わる値の例として問題ない（手元では別の値が出た）
- `vector c{v};` がコピーになる理由：cppreference の CTAD のページ（copy deduction candidate の優先）と static_assert で確かめた。本文の説明で正しい
- 大きな局所配列とスタック：このページでは触れなくてよい。使い分けの表の「グローバルの C 配列」は正しい
- 見出しの `<` を `&lt;` と書く件（手引きへの提案）：検証の範囲外。メインの判断に任せる

## 総合の判定

小さな直しで可（直すべき 0 件、直すとよい 9 件）。事実・コード・エラー文面はすべて手元で再現でき、誤りは見つからなかった。指摘 1・2・4 は本文の数語の修正、3 はコード片 1 行と本文 1 文、5 は図の組み直し、6・7 はメインが用語集に反映するときの申し送りである。
