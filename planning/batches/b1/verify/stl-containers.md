# stl-containers の検証

- 対象：docs/ds/stl-containers.md、snippets/stl-containers/count-pairs.{cpp,yaml}・multiset-erase.{cpp,yaml}（図の画像はなし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査

- `python3 tools/check_pages.py --page stl-containers`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/stl-containers`：コード片 2・期待と違う 0
- `npx textlint docs/ds/stl-containers.md`：エラー 0・警告 5（要点の計算量の行の長さ・助詞「に」の重複。数式を含む列挙で、§13.8 の範囲）
- コンパイラ：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- サニタイザ：両方のコード片を `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined` で作り、cases と n = 0（空）の入力で動かした。警告・実行時エラーなし。count-pairs は n = 0 で `0`、`5 / 3 1 5 3 7` で `4`（手計算：キー 3,0,3,0,3 → 3 + 1 = 4）。multiset-erase は `2`
- 小さなプログラム（一時置き場の bench.cpp、g++-15 -O2）で次を確かめた
    - vector の容量：1・2・4・8・…・256 と 2 倍で伸びる（libstdc++。執筆者の未解決の点 2 は正しい）
    - 空の `vector<int>` の `size() - 1` は 18446744073709551615（約 1.8×10^19。本文どおり）
    - 20 万要素の set に `std::lower_bound` を 200 回：12.5 秒、メンバの `lower_bound`：0.0003 秒（本文の O(N) の主張どおり）
    - 50 万要素の追加と、最大の取り出しを全部：priority_queue 0.03 秒、multiset 0.39 秒（約 13 倍。指摘 2）
- 一次資料：cpprefjp の multiset::erase・multiset::count（計算量 log(size()) + count(x)）、cppreference の std::lower_bound（"map, multimap, set, multiset ... member lower_bound functions should be preferred" の注記を確認）。参考の URL 6 件はすべて 200 で、題名・内容は書かれたとおり
- 台帳の evidence：kyo-pro の ABC253C（multiset で find して erase、map と set、ヒープの遅延削除の別解）、drken の ABC166E（制約 1 ≤ A_i ≤ 10^9、A_i + i = j − A_j に分けて map、先に全部の i を記録しても i ≥ j は一致しない）、kyopro-tessoku 第 8 章の answer_A54.cpp（`map<string, int>`）・answer_A55.cpp（`set` の insert・erase・`lower_bound`、`end()` なら -1）。どれも本文の方針と合う
- atcoder.jp・codeforces.com は開いていない

## 指摘

### 1. 直すとよい｜clarity（手引き §13.1）・F10｜#pitfalls の見出しと sections

- **問題**：§13.1 は「落とし穴」を定型の節とし、sections に載せずに `## 落とし穴 {#pitfalls}` とする決まりである。このページは sections に pitfalls を残し、見出しを「落とし穴（multiset の erase(x)・set に std::lower_bound・map の []・空の size() − 1・無効化・ハッシュ）」と長くしている。書き終えたほかのページ（complexity-estimation・prefix-sum-counting など 117 ページ）は `## 落とし穴 {#pitfalls}` にそろっている
- **根拠**：style-guide §13.1。`grep "{#pitfalls}"` の結果。執筆者も報告の「手引きへの提案」で同じ点を挙げている
- **直し方**：メインが決める。§13.1 に従うなら、sections から pitfalls を外し、見出しを `## 落とし穴 {#pitfalls}` にする（anchor は同じなのでリンクは壊れない）。front matter の行を消すのは §2.1 で執筆者に許された変更の外なので、メインが行う

### 2. 直すとよい｜F2・F3｜#choosing の「定数倍が数倍重い」

- **問題**：「`multiset` は木の節点を 1 つずつ確保するので定数倍が数倍重い」とあるが、追加と最大の取り出しを繰り返す典型の使い方で測ると約 13 倍だった。「数倍」は軽く見積もりすぎで、読者が乗り換えの判断を誤りうる
- **根拠**：上の測定（50 万要素、priority_queue 0.03 秒・multiset 0.39 秒）
- **直し方**：「数倍から 10 倍ほど重い」のように幅を持たせる

### 3. 直すとよい｜F2｜#choosing の確認問題の答え「begin() の前を参照すると未定義動作」

- **問題**：`it == s.begin()` のときは `prev(it)` を計算すること自体が未定義動作で、参照（`*`）しなくても起きる。「参照すると」だと「prev を取るだけなら安全」と読める
- **根拠**：双方向イテレータの `--` の事前条件（デクリメントできる値であること）。begin() はデクリメントできない
- **直し方**：「（`begin()` に `prev` を使うこと自体が未定義動作）」にする

### 4. 直すとよい｜F1・F3｜#complexity-table の set・multiset の削除

- **問題**：表は set・multiset の削除を一律に $O(\log N)$ としているが、`multiset` の `erase(x)` は消す個数に比例して $O(\log N + x \text{ の個数})$ かかる（同じ表で `count(x)` には書いている）。落とし穴の節で「全部消す」とは言うが、時間の面には触れていない
- **根拠**：cpprefjp multiset::erase（キーを渡す版の計算量は log(size()) + count(x)）
- **直し方**：表の「遅い・できない操作」の `count(x)` と並べて「`erase(x)`・`count(x)` は $O(\log N + x \text{ の個数})$」とする

### 5. 直すとよい｜clarity U3・C6｜#pitfalls 1 段落目の `contains(x)`

- **問題**：`contains` が最初に出る multiset の段落（110 行）に版の注記がなく、2 つ後の map の段落で初めて「（C++20）」と書かれる。断片で読むと版が分からない
- **根拠**：手引き §9（新しい書き方には版かリンク）、clarity U6
- **直し方**：110 行の `contains(x)` に「（C++20）」を付ける（または [contains](../cpp/cpp-container-idioms.md#contains) へリンクする）

### 6. 直すとよい｜clarity U3｜#choosing の表の書き方 2 か所

- **問題**：(a) 「最小は `greater<>` を渡す」は、第 2 引数の `vector<int>` も要ることが分からない。落とし穴の節は `greater<int>` と書いていて表記もそろっていない。(b) 「`map`（値が小さければ配列）」の「値」は、キー（数える対象の値）の範囲のことか、記録する個数のことか迷う
- **根拠**：読者（C++ の基本文法は分かるが現代的な書き方に不慣れ）の立場で読んだ
- **直し方**：(a)「最小は `priority_queue<int, vector<int>, greater<int>>`（[落とし穴](#pitfalls)）」。(b)「`map`（キーの範囲が狭ければ配列）」

### 7. 直すとよい｜C2｜snippets/stl-containers/count-pairs.yaml

- **問題**：cases に空の入力がない（手引き §9 は「空・1 要素・境界」を求める）
- **根拠**：手で n = 0 を与えると `0` が出て、正しく動くことは確かめた
- **直し方**：`- {input: "0\n", output: "0\n"}` を足す

### 8. 直すとよい（提案のみ）｜F2｜#pitfalls の unordered_map「AtCoder ではまれだが」

- **問題**：執筆者の未解決の点 1。AtCoder で狙われた実例の有無は確かめられない（atcoder.jp を開けない）。ただし「まれ」は弱い言い方で、参加者が入力を作れるコンテストで狙われるという主張の中心は正しい。誤りとは言えないので、直さなくてもよい
- **直し方**：気になるなら「AtCoder では問題の作成者が狙うことは少ないが」のように、根拠のある範囲の言い方にする。hash-safety の執筆時にそろえる

## 問題がなかった点（要点）

- 計算量：要点・front matter の complexity・本文が一致し、ならし（vector）・平均と最悪（unordered_map）の条件が書かれている。ABC253 C の $O(Q \log Q)$ のならしの議論（消す回数の合計は追加の回数以下）も正しい
- 主張：multiset の `erase(x)` の挙動と戻り値、`std::lower_bound` が set で $O(N)$ になる理由、map の `[]`、範囲 for 中の `push_back` が未定義動作（end が無効になる）、set・map の erase の無効化、libstdc++ の赤黒木と 2 倍の伸長は正しい
- ABC166 E の練習の方針（$A_i \ge 1$ なので $i \ge j$ は一致しない）は drken の記事の制約と合う。本文の例（$A_j - A_i = j - i$）は練習とは別の式で、解説の例をなぞっていない（F8）
- コード片：`find` → `end()` を確かめて `erase` の順、調べてから記録する順、`long long` の答えと符号付きのキーが本文の説明と 1 行ずつ対応する。取り込みは core の数行だけ。書き方は §9 どおり（`'\n'`、マクロと別名なし）
- 図：catalog の visual は static・priority 2 で、Markdown の表で代えたのは §8（2 は余力があれば）の範囲。表は 3 列でスマホでも読める。SVG はないので G1〜G6 は対象外
- リンク：節へのリンク（cpp-container-idioms の multiset-erase-one・member-lower-bound・map-subscript・invalidation、prefix-sum-counting の equal-k）はどれも draft のページに anchor がある。stub の balanced-bst・hash-safety へはページへのリンクだけで、§13.4 の範囲

## 台帳への提案

- abc253_c・abc166_e・tessoku_book_bb・tessoku_book_bc：`checked: 2026-10-21`（evidence で問いと方針を確かめた）
- tessoku_book_bb・tessoku_book_bc の evidence をファイルの URL（.../codes/cpp/chap08/answer_A54.cpp・answer_A55.cpp）にする執筆者の提案に賛成（どちらも 200 で中身を確かめた）

## 総合の判定

小さな直しで可。直すべき指摘 0、直すとよい指摘 8（うち 1 はメインの判断、8 は提案のみ）。
