# cpp-structured-bindings の検証（工程8b・b1）

- 対象：docs/cpp/cpp-structured-bindings.md、snippets/cpp-structured-bindings/ の 20 片（.cpp と .yaml）、docs/img/cpp-structured-bindings/hidden-variable.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_snippets.py snippets/cpp-structured-bindings`（20 片・コンパイル 38 回・期待と違う 0）、`python3 tools/check_pages.py --page cpp-structured-bindings`（エラー 0・警告 0）、`npx textlint`（0 errors・9 warnings。長い見出しを含む文の長さ・コードを含む文の助詞の重複で、§13.8 の範囲）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0 と g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- front matter：complexity と要点の計算量が一致する。別名の行に aliases がすべてある。cpp_std 17・gcc_min null・atcoder true は、C++20 以降の書き方（キャプチャ・enumerate・zip・`_` 2 回）に本文で版が書かれていて食い違いはない
- 本文の版・エラー文面の主張を、作業用の場所 v-cpp-structured-bindings/ で手で確かめた（すべて本文どおり）
    - count-ng：g++-15 で `only 2 names provided for structured binding` と `note: while 'std::tuple<int, int, int>' decomposes into 3 elements`
    - cond-binding-ng：g++-15 `-std=gnu++23` は `structured bindings in conditions only available with '-std=c++2c'` の警告のあと `could not convert '<structured bindings>' from 'std::pair<…, bool>' to 'bool'` のエラー。`-std=gnu++26` でも同じエラー（組全体を bool にする、の説明どおり）。g++-13 は `expected unqualified-id before '['` の文法エラー
    - placeholder-twice：g++-15 `-std=gnu++23` は `name-independent declarations only available with '-std=c++2c'` の警告で通る。g++-13 は `redeclaration of 'auto _'`
    - キャプチャ：g++-13・g++-15 とも `-std=gnu++17 -pedantic -Wall -Wextra` と `-std=c++17 -pedantic` で警告なし
    - `tie(f0, f1) = tie(f1, f0 + f1)`：`cannot bind non-const lvalue reference of type 'long long int&' to an rvalue`
    - 空の optional の `*o`：g++-15 `-O2` で 0 が出た。`-D_GLIBCXX_ASSERTIONS` で `Assertion 'this->_M_is_engaged()' failed`
    - 範囲 for の初期化式 `for (auto v = f(); int x : v)`：g++-13 `-std=gnu++20 -Wall -Wextra` で警告なしに動く
    - pq-top：g++-13・g++-15 で `-Wall -Wextra`・`-D_GLIBCXX_DEBUG`・`-fsanitize=address,undefined` のどれでも `7 2`、報告なし
- 自分で導いた主張の確認
    - pop の後に先頭の場所へ (7, 2) が入る：libstdc++ の pop_heap は末尾の値を退避し、先頭に穴を作って小さい子を詰め上げるので、要素 3 個 [(5,1),(7,2),(9,3)] は [(7,2),(9,3)] になる。2 個以上なら参照先の要素は代入されるだけで寿命は切れないので未定義動作ではなく、1 個なら pop_back で寿命が切れて未定義動作、という本文の区別は正しい（指摘 2 は見出しとの食い違い）
    - map の要素を `auto [k, v]` で受けても k は const：map-loop.cpp の static_assert が通る
    - enumerate・zip の要素の組が参照を持つ：enumerate-ref の cases で確かめられている
    - `tie(a, b) = tie(b, a)` が `2 2`：libstdc++ の tuple の `_M_assign` は先頭の要素から順に代入する（/usr/include/c++/15/tuple 466 行）。規格は代入の順を決めていない（指摘 6）
    - exchange の cases：n = 0・1・10 で 0・1・55（$F_0 = 0$ から手で確かめた）。apply の cases：12、sort 後 (1,1,2)・(2,0,1)。if-init の cases：3 → 0、2 → 3、空 → -1。capture：inside(2,3) = 1・inside(3,0) = 0
- AtCoder での扱い：decisions.md の AtCoder の GCC のオプション（`-std=gnu++23 -O2 -Wall -Wextra …`、`-Werror` なし）から、`_` を 2 回使う書き方が警告つきで通るという推定は筋が通る（執筆者の未解決の点 1。指摘 9 は書き方の提案だけ）
- 参考の URL：10 件とも curl で 200（cpprefjp 9・cppreference 1、付録 B のドメイン）。本文の文と例は出典と並びも数値も別で、近すぎる箇所は見当たらない
- 図 hidden-variable.svg：ヘッドレスのブラウザが手元になかったため、作業用の場所に cairosvg を入れて 2 倍の PNG（v-cpp-structured-bindings/hv.png）にして目で見た。日本語の字形は手元に日本語フォントがなく豆腐になったが、文字の幅（全角 1 字 ≒ 1em）と配置は確かめられる。背景は白、viewBox あり、文字はテキストのまま `font-family="sans-serif"`、コピーは破線の枠・参照は太線で、色だけに頼っていない。内容（auto は e がコピー、auto& は e が p そのもの）は本文・代替テキストと一致する
- 執筆者の未解決の点：(1) AtCoder での `_` 2 回は上のとおり推定で可。(2) optional の `*o` が 0 を返すのは手元の一例と読める書き方で問題ない。手引きへの提案（pq-top-reference の題名）は、指摘 2 で題名の直しを勧める。なお cpp-undefined-behavior は draft になり `#dangling-pq-top` の節がある（その見出しは「値が変わる」とだけ書き、ダングリングの区別と食い違わない）。本文 164 行の未定義動作のリンクを `../cpp/cpp-undefined-behavior.md#dangling-pq-top` に、55 行の CTAD を cpp-initialization の節に直すのは、メインがバッチの終わりに判断する

## 指摘

### 1｜直すべき｜図（G3・G5）｜hidden-variable.svg の上段の説明文（`<text x="440" y="148">`）

- 問題：上段の説明文「a・b は e のメンバの名前。a = 100 でも p は変わらない」が viewBox（幅 640）の右端からはみ出し、「p は変わらない」の部分が切れて表示されない。この図のいちばん言いたいこと（コピーなので p は変わらない）が欠ける
- 根拠：x = 440 から 12px の文字で全角 18 字・半角約 20 字、幅はおよそ 340px で右端は 780 前後。cairosvg で画像にすると「a・b は e のメンバの名前。a = 100 でも p」で切れる（v-cpp-structured-bindings/hv.png）
- 直し方：説明文を x = 20〜200 あたりから始める（下段の説明文と同じく箱の下の左寄せ）か、2 行に分ける

### 2｜直すべき｜事実（F2）・手引き §13.2｜#pq-top-reference の見出し（24 行の sections の title と 156 行）

- 問題：見出しの「理由は cpp-undefined-behavior のダングリング」は、本文（164 行）の正しい区別と食い違う。ダイクストラ法で起きる普通の場合（要素が 2 個以上）は、参照先の要素は生きていて別の値が代入されるだけで、ダングリングでも未定義動作でもない。辞書として見出しだけを読む人や、節だけを読む claude.ai は「理由はダングリング」と受け取る
- 根拠：libstdc++ の pop_heap の動き（上の「確かめたこと」）。本文 164 行と執筆者の報告の「手引きへの提案」も同じ区別をしている。cpp-undefined-behavior#dangling-pq-top の見出しは「値が変わる」と書き、ダングリングの理由を言い切っていない
- 直し方：見出しと sections の title を同じ文に直す（§13.2 で執筆者が直してよい）。例：「const auto& [d, v] = pq.top(); pq.pop(); で値が変わる（ダイクストラで起きる。値で受ける。要素が 1 個ならダングリング）」。anchor は変えない

### 3｜直すとよい｜図（G5）｜hidden-variable.svg の矢印の先

- 問題：上段の a からの矢印の先（315, 64）が、ラベル「見えない変数 e（p のコピー）」の文字の上に重なる。下段の a の矢印は `stroke-width="2.5"` のため矢じり（marker は線の太さに比例して大きくなる）が大きく、ラベル「p（見えない変数 e は p そのものを指す）」の先頭の文字にかぶる
- 根拠：hv.png で目視。上段の経路は y = 60（ラベルの下端は約 56）、下段は y = 230（ラベルの下端は約 226）で、矢じりが縦に 7〜17px ほど伸びる
- 直し方：矢印を箱の下側から入れる（b と同じ向き）か、ラベルを 10px ほど上に上げる。下段は marker に `markerUnits="userSpaceOnUse"` を付けるか、太線用に小さい marker を別に用意する

### 4｜直すとよい｜図（G3）｜hidden-variable.svg の文字の大きさ

- 問題：viewBox の幅 640 に対し説明文が 12px なので、幅 390px の画面（本文の幅 358px 前後）では約 0.56 倍の 6.7px 程度になり、スマホで読みにくい
- 根拠：358 / 640 × 12 ≒ 6.7
- 直し方：指摘 1 で説明文を左寄せにするのに合わせて 14px にするか、右側の a・b の列を左へ詰めて viewBox の幅を 560 程度に縮める

### 5｜直すとよい｜コードと本文（C3）・事実（F2）｜#structured-binding の 85 行

- 問題：「素朴に書くと `for (const auto& e : es) { int to = e.to; … }` と同じ意味」とあるが、取り込んだコード片（bindings.cpp 17 行）は `for (auto [to, cost] : es)` で、見えない変数は要素のコピーである。`const auto&` で受ける素朴な形とは、コピーするかどうかが違う。直後の括弧書き「構造化束縛の名前は… `e` のメンバそのものの別名」の `e` が、素朴な形の `e`（es の要素への参照）と見えない変数（コピー）のどちらか読み手に分からない
- 根拠：構造化束縛の `auto` は見えない変数 `auto e = 要素;` にかかる（本文 94 行と cppreference）
- 直し方：素朴な形を `for (auto e : es) { int to = e.to; long long cost = e.cost; … }` にして、括弧書きを「名前 to・cost は、新しい変数ではなく見えない変数 e のメンバの別名である」とする。あるいはコード片を `const auto& [to, cost]` に変える

### 6｜直すとよい｜事実（F2）｜#tie-swap-pitfall の 224 行と確認問題の答え（240 行）

- 問題：「`a = b;` を行ってから `b = a;` を行うことになる。結果は両方とも元の `b` になる」と、代入の順が決まっているように書いている。規格の tuple の代入は「各要素を対応する要素に代入する」とだけ定め、順を決めていない。先頭から順に代入するのは libstdc++ の実装である（逆の順なら両方とも元の `a` になる）。どちらの順でも入れ替えにならない、という要点は正しい
- 根拠：cppreference の tuple::operator=（"Assigns each element of other to the corresponding element of *this"）、/usr/include/c++/15/tuple の `_M_assign`（先頭から順）。実行結果 `2 2` は g++-13・g++-15 で一致
- 直し方：224 行を「右辺も参照の組なので、片方を代入した時点で右辺の残りも書き換わっている。GCC（libstdc++）は先頭から順に代入するので、`a = b;` の後に `b = a;` となり、両方とも元の `b` になる」とし、入れ替えにならないのは順によらない、と一言足す。確認問題の答えにも「GCC では」を足す

### 7｜直すとよい｜事実（F2）｜#pair-tuple の 55 行

- 問題：「`tuple<T, U, V, …>` は 3 つ以上の組」とあるが、tuple は要素の数を問わない（2 個でも 1 個でもよい。`tie(a, b)` は 2 要素の tuple で、本文 211 行でも `tuple<int&, int&>` と書いている）。同じページの中で食い違って見える
- 根拠：cpprefjp・cppreference の tuple（可変長の型引数）
- 直し方：「`tuple<T, U, V, …>` は好きな個数の組で、3 つ以上をまとめるのに使う」とする

### 8｜直すとよい｜本文とコード（C3）｜#capture-and-placeholder の 193 行

- 問題：「グリッドの高さと幅を pair で受けて」とあるが、コード片（capture.cpp）は `auto [w, h] = p;` で (幅, 高さ) の順、判定も `x < w`・`y < h` である。本文の順と名前の順が逆で、構造化束縛の「名前は宣言順に付き、意味は検査されない」落とし穴（88 行）を扱うページだけに、読み手が引っかかる
- 根拠：capture.cpp 6〜10 行
- 直し方：本文を「グリッドの幅と高さを pair で受けて」にする

### 9｜直すとよい｜分かりやすさ（U9）｜#enumerate-reference の 189 行と #capture-and-placeholder の 206 行

- 問題：(1) 189 行「添字付きで回しながら値を変えて試す（元は変えたくない）つもりで」は、何をしたい場面か読み取りにくい。(2) 206 行「AtCoder の GCC 15.2 も同じ扱いになる」は AtCoder の上では試していない推定だが、確かめた事実と同じ書き方になっている
- 根拠：(1) 読者の立場で 2 度読んで場面が浮かばなかった。(2) 執筆者の未解決の点 1。decisions.md の AtCoder のオプション（`-std=gnu++23`、`-Werror` なし）から推定は妥当
- 直し方：(1)「ループの中で `x` を一時的に書き換えて計算に使う（元の配列は変えたくない）つもりで」。(2)「AtCoder の GCC 15.2 も同じ版・同じ `-std=gnu++23` で、警告をエラーにしないので通る」と根拠を添える

## 総合の判定

小さな直しで可。直すべき 2 件（図の説明文のはみ出し、pq-top-reference の見出しの「理由はダングリング」）、直すとよい 7 件。コード片 20 片はすべて期待どおりで、版・エラー文面・挙動の主張は手で確かめた範囲ですべて本文どおりだった。
