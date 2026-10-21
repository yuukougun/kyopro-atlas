# cpp-range-for の検証（工程8b・b1）

- 対象：docs/cpp/cpp-range-for.md、snippets/cpp-range-for/ の 13 片（.cpp・.yaml）、docs/img/cpp-range-for/copy-ref-move.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page cpp-range-for -v`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page cpp-range-for --check`（直すべき行 0）、`python3 tools/check_snippets.py snippets/cpp-range-for`（13 片・コンパイル 25 回・期待と違う 0）、`npx textlint docs/cpp/cpp-range-for.md`（出力なし＝0 件）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0 と g++-13 (Ubuntu 13.4.0-6ubuntu1~22~ppa2) 13.4.0
- front matter：complexity・要点の計算量・本文の主張（コピーは $O(N)$、参照・ムーブ・swap は $O(1)$）が一致する。cpp_std 17・gcc_min 13・atcoder true は、C++20・23 の話題を節の「版」で断っているので合う（C6）。問題は置かない方針で、本文に問題のリンクはない
- コード片：書き方（bits・using namespace std・マクロなし・`'\n'`）は §9 に合う。取り込みはどれも要点の数行。cases の期待出力を手で確かめた（range-for-forms の `1 2 3` → `2 3 4`、modify-in-loop の `2 3 4 8` → `2 3 4 8 1 2 4`、move-swap のナップサック 3 品・容量 8 → 90（重さ 3+5 で 30+60）、vector-bool の n=3 → `0` と `011`、temporary-range の `0 2 3`）。compile-error の 2 片は、それぞれ const 参照からの push_back と `auto&` のプロキシ束縛が原因で、ほかの打ち間違いではない
- 自分で確かめた主張（作業用の場所 v-cpp-range-for/）
    - vector-bool-ng の g++-15 のエラー：`cannot bind non-const lvalue reference of type ‘std::_Bit_reference&’ to an rvalue of type ‘std::_Bit_iterator::reference’`。本文の文面と一致
    - `for (int v : d.groups()[0])`（ACL dsu、0-2-3 をつなぐ）：g++-13 gnu++23・g++-15 gnu++20・g++-15 gnu++23 `-fno-range-for-ext-temps` は ASan で heap-use-after-free、ASan なし `-O2` では 3 回とも segfault。g++-15 gnu++23 は ASan あり・なしとも `0 2 3`。本文の表と一致
    - 範囲 for の中の push_back（bad.cpp）：ASan では両方 heap-use-after-free。ASan なし `-O2` の長さは実行のたびに変わった（指摘 3）
    - 値渡しの再帰（長さ・深さ $10^4$、g++-15 -O2）：294 ms・最大 395 MB、const& は 0.002 ms・3.9 MB。時間は機械で変わるが、桁と結論は本文と合う
    - swap と代入（長さ $10^7$ の `vector<long long>` を 100 回）：swap 0.2 µs、代入 1121 ms。桁と結論は本文と合う
- 事実の出典：GCC 15 の changes に「Several C++23 features have been implemented: … P2718R0, Wording for P2644R1 Fix for Range-based for Loop」がある。GCC 15.2 のマニュアルの `-frange-for-ext-temps` に「With -std=c++23 and above this is part of the language standard … by default」とあり、`-fno-range-for-ext-temps` で戻る本文の記述と合う。cpprefjp の vector::swap は「定数時間」。cppreference の vector の移動構築は「要素への参照・イテレータは移った先で有効」とだけ書き、元が空になる保証を直接は書いていない。本文の「手元では空になった」「中身を当てにしない」という控えめな書き方でよい（執筆者の未解決の点 2 は解決）
- 参考の URL：9 件とも 200。題名は 1 件が実際と違う（指摘 4）。ほかは cppreference・cpprefjp・gcc.gnu.org で付録 B のドメイン。本文の例（dsu の groups、{2, 3, 4, 8}、ナップサック）は出典と別で、近すぎる箇所はない
- リンク：knapsack-01・cpp-lambda・cpp-structured-bindings・cpp-undefined-behavior・cpp-views-cpp23・cpp-views-basics#filter-transform は存在する。用語集の `#temporary-object`・`#proxy` はまだない（執筆者の提案あり。§13.5 によりメインが用語集に足せば解消。足さないならリンクを外す）
- 図 copy-ref-move.svg：Windows の Chrome（headless=new）で、等倍（720×300、2 倍密度）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（v-cpp-range-for/full.png・narrow.png）。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、色に加えて破線（コピー）と点線（空）で区別。矢印の向き（r → a、a → b）は正しい。内容は本文（参照は箱が増えない、ムーブは置き場所を渡す、swap は $O(1)$）と一致する。幅 358px では文字が小さい（指摘 9）
- 執筆者の未解決の点：(1) swap の定数時間と vector<bool> の特殊化が C++98 からであることは正しい（C++98 のコンテナの要件で swap は定数時間、`vector<bool>` の特殊化も C++98 の標準ライブラリにある）。(2) 上のとおり今の書き方でよい。(3) cpp-dangling のページは docs にない。cpp-undefined-behavior へのリンクでよい。(4) 表の列は 4 で §8 に収まる

## 指摘

### 1｜直すべき｜手引き（§13.1）・fact（F7）｜見出しの anchor の重なり（48 行と 230 行）

- **問題**：最初の節「参照 T& と const 参照 const T&」の anchor が `references` で、末尾の定型の節 `## 参考 {#references}` と同じ。1 ページに同じ id が 2 つでき、`#references` へのリンク（docs/index/cpp.md の節の一覧など）がどちらに飛ぶか定まらない。check_pages と mkdocs はこの重なりを検出していない
- **根拠**：style-guide §13.1（参考は `## 参考 {#references}` に固定）。`grep -n "{#references}" docs/cpp/cpp-range-for.md` で 48 行と 230 行
- **直し方**：最初の節の anchor を `reference-basics` など別の名前にし、front matter の sections の anchor も同じに直す（§13.2 で執筆者が直してよい）。ほかのページからこの節へのリンクはない（grep で確かめた。docs/index/cpp.md は gen_site で作り直される）

### 2｜直すべき｜fact（F2）｜冒頭の「範囲 for・参照・ムーブは C++11 からあり」（46 行）

- **問題**：参照は C++98 からある。同じページの #references の「版」は「C++98 から」と書いており、食い違う
- **根拠**：C++98 の時点で参照（`T&`）は言語にある。本文 59 行の「版」の記述
- **直し方**：「参照は C++98 から、範囲 for とムーブは C++11 からあり、…」とする

### 3｜直すべき｜fact（F3）｜#modify-in-loop の `-O2` の結果（182 行）

- **問題**：「g++-13 は長さ 6、g++-15 は長さ 7 を出した（本来は 7）」は、版ごとに決まった結果のように読め、g++-15 は正しく動くと受け取られかねない。同じ機械で同じ実行ファイルを 6 回動かすと、g++-13 は 7 7 7 6 7 7、g++-15 は 8 7 7 7 6 6 と毎回変わった（別に 5 も出た）。解放後のメモリの中身しだいで変わるので、版と結果は結び付かない
- **根拠**：v-cpp-range-for/bad.cpp を `g++-13/15 -std=gnu++23 -O2` でコンパイルし、6 回ずつ実行した結果
- **直し方**：「付けずに `-O2` で動かすと、長さは実行のたびに 5〜8 と変わった（本来は偶数 3 個を足して 7）。たまたま正しい 7 が出ることもあり、黙って誤った答えを出す」のように、版を名指ししない書き方にする

### 4｜直すべき｜fact（F9）｜参考の cpprefjp の題名（236 行）

- **問題**：「範囲for文に初期化式を記述できるようにする」と書いているが、ページの題名は「初期化式をともなう範囲for文」
- **根拠**：`curl` で取った `<title>`：「初期化式をともなう範囲for文 [P0614R1] - cpprefjp C++日本語リファレンス」
- **直し方**：`[cpprefjp「初期化式をともなう範囲for文」](…)` にする

### 5｜直すべき｜clarity（U9）｜#forwarding-reference の 2 つの箇条書きがつながる（114〜121 行）

- **問題**：「主に次の 3 か所である」の 3 項目の箇条書きと、「版」「落とし穴」の箇条書きの間が空行だけなので、MkDocs（Python-Markdown）では 1 つの 5 項目の箇条書きになる。「3 か所」の後に 5 項目が並び、「版」「落とし穴」が 3 か所の 4・5 番目のように見える
- **根拠**：プロジェクトの .venv の `markdown.markdown()` で同じ形を変換すると、`<ul>` が 1 つで `<li>` が 5 つになった
- **直し方**：2 つの箇条書きの間に 1 文（例：「どれも、受けたものを書き換えられる参照として使う」）を挟むか、3 か所の後に `<!-- -->` を置いて箇条書きを切る

### 6｜直すとよい｜fact（F2）・clarity（U3）｜#modify-in-loop の「再確保が起きると」（176 行）と bad のコメント

- **問題**：本文は「再確保が起きると」未定義動作と書くので、`v.reserve(…)` で再確保を防げば範囲 for の中で push_back してよい、と読める。実際は再確保がなくても push_back で末尾のイテレータ（範囲 for が覚えた `v.end()`）が無効になり、未定義動作のままである。また bad のコメント「再確保で x の元の場所が消える」は、`x` は int のコピーなので、壊れるのは範囲 for が覚えた位置（イテレータ）だという点がぼやける
- **根拠**：cppreference の vector::push_back「If after the operation the new size() is greater than old capacity() a reallocation takes place, in which case all iterators (including the end() iterator) and all references to the elements are invalidated. Otherwise only the end() iterator is invalidated.」（curl で確かめた）
- **直し方**：本文に「再確保が起きなくても、覚えた `v.end()` は無効になるので、`reserve` しても未定義動作である」と 1 文足す。コメントは「再確保で、範囲 for が覚えた位置が古い場所を指す」とする

### 7｜直すとよい｜fact（F2）｜#range-for-forms の表の `auto&&` の行（132 行）

- **問題**：「元を書き換え できる」とあるが、`const vector` を回すとき（`const T&` になる）や、`views::transform` のように要素をその場で作る view では、`x` を書き換えても元は変わらない。「views も」と並べているので誤解しやすい
- **根拠**：auto&& は受けたものの型に合わせるだけで、元が const や値（右辺値）なら元には届かない
- **直し方**：「できる（元が書き換えられる範囲なら）」とする。または表の下に一言足す

### 8｜直すとよい｜clarity（U3）｜#pass-by-reference の「長さ 2×10^5 なら」（72 行）と #temporary-range の冒頭（195 行）・落とし穴（214 行）

- **問題**：(a)「長さ $2 \times 10^5$ なら値渡しは確実に TLE か MLE」は、深さも同じだけあることが前提だが書いていない（深さが小さければ問題にならない）。(b)「関数の戻り値そのもの…どの版でも安全」は、値で返す関数のときに限る（参照を返す関数なら延長されない）。(c) 落とし穴の「（逆に、新しいコンパイラで通ったコードが古い環境で落ちる）」は、前の「AtCoder で通ったコードが手元で落ちる」と同じ向きで「逆」になっていない
- **直し方**：(a)「長さ・深さとも $2 \times 10^5$ なら」。(b)「値で返す関数の戻り値そのもの」。(c) かっこの中を消すか、「AtCoder（GCC 15・C++23）で通ったコードが、手元の g++-13 や C++20 の環境で落ちる」と 1 つにまとめる

### 9｜直すとよい｜figure（G3）｜copy-ref-move.svg の文字の大きさ

- **問題**：viewBox の幅 720 に 14 の文字なので、スマホの幅 358px に縮むと文字が約 7px になり、説明の 2 行（「箱が増える（N 個を写す）」など）と下の swap の行が読みにくい（narrow.png で確かめた）
- **直し方**：説明の文字を図から外して本文の代替テキストと前後の文章に任せ、図はラベル（a・b・r・1 2 3・空）だけにして文字を 18 程度に上げる。または 3 つを縦に並べる配置にして横幅を 400 程度にする

### 10｜直すとよい｜clarity（U3）｜#move-swap の見出しの O(N) とコードの O(W)（84 行・コード片のコメント）

- **問題**：見出しと本文は「`dp = ndp` は $O(N)$」、取り込むコードのコメントは「$O(W)$」。このコードの $N$ は品物の数なので、見出しの $N$ を品物の数と読むと誤る
- **直し方**：見出しを「…dp = ndp は長さに比例するコピー」にするか、本文で「長さ $N$ の配列」と断る。コード片の側を「長さ w + 1 のコピー」としてもよい

## 総合の判定

小さな直しで可（直すべき 5 件：anchor の重なり、参照の版、UB の実行結果の書き方、参考の題名、箇条書きのつながり。どれも数行の修正で済む。直すとよい 5 件）。
