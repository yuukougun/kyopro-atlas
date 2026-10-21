# coordinate-compression の検証（工程8b・b1）

- 対象：docs/basics/coordinate-compression.md、snippets/coordinate-compression/{compress,covered-length}.{cpp,yaml}、docs/img/coordinate-compression/{mapping,intervals}.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page coordinate-compression`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/coordinate-compression`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/basics/coordinate-compression.md`（0 errors・12 warnings。数式の `[l, r)` の括弧の誤検出と、数式・リンクを含む文の長さ。§13.8 の範囲）
- front matter：git diff で、執筆者が変えたのは complexity・stage と sections への with-ds の追加だけ。complexity と要点の計算量は一致し、根拠（sort $O(N \log N)$、lower_bound $N$ 回で $O(N \log K)$）も本文にある
- コード片：2 片を `-fsanitize=address,undefined` 付きで作り直し、作業用の場所の t.py で乱数の入力と素朴な方法を比べた（covered-length：区間 0〜6 個・負の座標を含む 300 件を、覆われる整数の個数と比較。compress：300 件を `sorted(set(a)).index` と比較）。すべて一致、サニタイザの報告なし。C5 の書き方（bits・using namespace std・マクロなし・`'\n'`・ラムダは判定の関数）に合い、取り込みの範囲も要点だけ。cases に空・1 要素・同じ値・負の値・端が接する区間がある
- 具体例：mapping の例（$a = (100, 7, 50000, 7, 3)$ → vals $= (3, 7, 100, 50000)$、番号 $2, 1, 3, 1, 0$）、intervals の例（端点 2・5・9・14、基本区間の長さ 3・4・5、重なり 1・2・1、合計 12、番号で測ると 3）、確認問題 2 つ（upper_bound で $1$〜$K$ になり最大の値で配列の外、右端を入れ忘れると 9 も 14 も番号 $2 = K$）、基本区間が高々 $2N - 1$ 個、$[l, r)$ が番号 $\mathrm{id}(l)$〜$\mathrm{id}(r) - 1$ をちょうど覆うこと：すべて正しい
- 自分で導いた主張の確かめ：「どの区間にも覆われない最小の整数」が端点の間の vals にない値になりうるか、半開区間・下限 0 で乱数 20000 件を全探索した（指摘 2）
- 問題：4 問とも `python3 tools/ap.py show` で題名・diff が本文と一致（abc213_c 481、abc113_c 878、abc036_c 956（参考値）、typical90_ac なし）。数は基礎の目安（例題 1・練習 2〜6）に合う
- 参考の URL：5 件を開いた
    - drken ABC213 C：行と列を独立に圧縮する方針。本文と一致
    - drken ABC113 C：県ごとにソート・重複除去・lower_bound で順位、出力は `%06d`（6 桁の 0 埋め）。本文と一致
    - drken ABC036 C：sort・unique・erase・lower_bound の手順はあるが、「重複を消し忘れたときの誤り」は書かれていない（指摘 4）
    - E869120 sol/029-02.cpp：`--L[i]` で $[L-1, R)$ にして両端点を圧縮し、区間は素朴な配列（`max_element`・`fill`）で最悪 $O(N^2)$。本文と一致
    - Reputeless 029.md：同じく $[L-1, R)$ を圧縮、素朴版は小課題向け、満点は遅延セグメント木（区間最大値と区間代入）で $O(N \log W)$。本文と一致
- リンク：リンク先のページ（binary-search・imos・event-sort・fenwick-tree・inversion-number・segment-tree-on-values・sweep-line-2d・offline-queries・segment-tree・lazy-segment-tree・stl-containers）はすべて存在する。ほかのページの節へのリンクはない。用語集の `#half-open-interval` はあり、`#offline` はまだない（提案済み。§13.5 によりメインが足す）
- 図：Windows の Chrome（headless=new、2 倍密度）で mapping.svg・intervals.svg を等倍（640×330・640×300）と、幅 390px の画面に幅 358px で暗い背景の上に置いて画像にし、目で確かめた（作業用の場所 v-coordinate-compression/ の full-*.png・narrow-*.png）。和文も表示され、はみ出し・重なりはない。値は本文・代替テキストと一致し、intervals の数直線は 1 目盛 72px で縮尺がそろう。背景は白、`viewBox` あり、文字はテキストのまま、`font-family="sans-serif"`。区間の区別は色に加えて実線と破線・ラベル。catalog の visual は static・priority 2（元の値と圧縮後の番号の対応表）で、mapping.svg が満たす

## 指摘

### 1｜直すべき｜fact（F2）｜導入（49 行付近）「現れる値が $N$ 個なら番号は $N$ 個未満で済む」

- **問題**：値がすべて異なれば番号はちょうど $N$ 個（$0$〜$N-1$）で、「未満」は誤り。本文の後の箇所（#with-ds の前の「$K \le N$」、#pitfalls の「$K \le N$」）とも食い違う
- **根拠**：compress の cases `3\n-1000000000 0 1000000000` で $K = 3 = N$
- **直し方**：「番号は $N$ 個以下で済む」にする

### 2｜直すべき｜fact（F2）｜#keep-original の最後の段落「どの区間にも覆われない最小の整数を求めるなら、答えは端点と端点の間の、どの vals にもない値になりうる」

- **問題**：半開区間 $[l, r)$ の両端点を入れていれば、覆われない最小の整数（下限を $0$ とする）は $0$ か、どれかの右端 $r$ である。$x$ が覆われず $x - 1$ が覆われるなら、$x - 1$ を覆う区間の右端が $x$ だからで、「端点と端点の間の、vals にない値」にはならない。例として主張を支えていない
- **根拠**：作業用の場所の t.py で、区間 1〜4 個・座標 0〜12 の乱数 20000 件を全探索し、答えが $\{0\} \cup \{\text{端点}\}$ にない例は 0 件。閉区間を $l$・$r$ のまま圧縮した場合（本文の禁じる形）なら答えは $r + 1$ で vals にない
- **直し方**：例を差し替える。たとえば「閉区間のまま $l$・$r$ を入れると、覆われない最小の整数 $r + 1$ が vals にない」や「各基本区間の中で条件を満たす最初の整数（基本区間の左端とは限らない値）を答える問題」。または「下限の値（$0$ や $1$）も vals に入れておく」という形に言い直す

### 3｜直すべき｜fact（F2）｜#pitfalls の「値の型」

- **問題**：「値が $10^9$ を超える、または負になりうるときは、vals を `long long` にする」とあるが、負の値は `int` にそのまま入る（$-10^9$ も可）。負かどうかは型を選ぶ理由にならない。また `int` の上限は約 $2.1 \times 10^9$ なので、「$10^9$ を超える」も境目として不正確（$r + 1$ や $2 \times 10^9$ 程度の座標を作るときに効く）
- **根拠**：`int` の範囲は $[-2^{31}, 2^{31} - 1]$。compress の cases でも $\pm 10^9$ を扱っている（vals は `long long` だが `int` でも収まる）
- **直し方**：「値が `int` の範囲（約 $\pm 2.1 \times 10^9$）を超えうるとき（$10^9$ に足し引きした座標、$10^{18}$ までの値など）は vals を `long long` にする」とし、負の値の話は「負の値もそのまま並べられるので、ずらす必要はない」だけにする

### 4｜直すべき｜fact（F9）｜#references の drken ABC036 C の行

- **問題**：参考にした点に「重複を消し忘れたときの誤り」とあるが、記事にその話はない（C++ の sort・unique・erase・lower_bound と、Python の `sorted(set(A))` の解法、計算量だけ）
- **根拠**：https://drken1215.hatenablog.com/entry/2021/08/10/003714 を読んだ
- **直し方**：「sort・unique・erase・lower_bound の 3 段の書き方」だけにする

### 5｜直すとよい｜手引き（§13.1）｜#vs-map の節

- **問題**：「map で足りる場合との使い分け」は中身が使い分けで、§13.1 の決まりでは定型の `## 使い分け {#comparison}` にして sections から外す形に当たる（kmp・z-algorithm の検証の指摘 3 と同じ種類）。ただし vs-map は骨格（stub）の sections にすでにあった anchor で、執筆者が変えたものではない。§2.1 の「既存の anchor は変えない」とぶつかる
- **直し方**：メインがどちらに寄せるか決める。寄せるなら `## 使い分け {#comparison}` にして sections から消す（ほかのページから #vs-map へのリンクがないか確かめる）。今のままにするなら、骨格由来の節として残す旨を決定事項に書く

### 6｜直すとよい｜clarity（U3・U6）・code（C3）｜#intervals・#keep-original の記号 xs

- **問題**：#three-steps では並べた列を vals と呼ぶが、#intervals では定義なしに $\mathrm{xs}_j$ が現れる（コード片の変数名 `xs` から来ている）。#keep-original は「$\mathrm{vals}$ で元の値に戻す」の直後に「$\mathrm{xs}_{j+1} - \mathrm{xs}_j$」と書き、同じものか別のものか迷う。節だけを取り出すと xs が何か分からない
- **直し方**：#intervals の最初で「両端点を集めて圧縮した列を $\mathrm{xs}$ とする（#three-steps の vals に当たる）」と定義する。または、コード片の変数名を `vals` にそろえて本文も vals にする

### 7｜直すとよい｜fact（F2）・clarity｜#pitfalls の「閉区間の右端に 1 を足し忘れる」

- **問題**：「閉区間 $[l, r]$ を $l$ と $r$ だけで圧縮していもす法をすると、点 $r$ の後ろまで覆ったことになる」は、差分を $\mathrm{id}(r) + 1$ で引いた場合の話。本文とコード片の形（差分を $\mathrm{id}(r)$ で引く）にそのまま当てはめると、覆うのは $[l, r)$ で、点 $r$ が抜ける。どちらの誤りになるかは書き方しだいで、読者が自分のコードに当てはめると逆に読める
- **直し方**：「差分を $\mathrm{id}(r)$ で引けば点 $r$ が抜け、$\mathrm{id}(r) + 1$ で引けば $r$ の次の座標の手前まで覆ってしまう」と両方を書く

### 8｜直すとよい｜fact（F2）・code｜#pitfalls の「vals にない値で lower_bound を引く」

- **問題**：「値を使う所をすべて先に集めるか、`*it == x` を確かめてから使う」とあるが、(1) `it == vals.end()` のとき `*it` は配列の外を読むので、確かめる式は `it != vals.end() && *it == x` でなければならない。(2) 半開区間 $[l, r)$ の範囲の個数・和を BIT で求めるとき（#vs-map の表の 3 行目）は、$l$・$r$ が vals になくても `lower_bound(l)`〜`lower_bound(r)` がちょうど $[l, r)$ に入る値の番号の範囲になり、正しく使える。「ない値はいつも誤り」と読める
- **直し方**：式を `it != vals.end() && *it == x` にする。「値そのものの番号が要るときの話で、範囲の境界として引くだけなら vals になくてもよい（$[l, r)$ の値は番号 $\mathrm{lower\_bound}(l)$ から $\mathrm{lower\_bound}(r) - 1$）」と 1 文足す

### 9｜直すとよい｜clarity（U3）｜#practice の「練習の方針」の典型90 029

- **問題**：#intervals と #pitfalls では「閉区間 $[l, r]$ は $[l, r + 1)$ に直す」と教えているのに、ここでは「$[L - 1, R)$ に直す」とあり、読者には別の規則に見える（どちらも正しく、マス $i$ を $[i - 1, i)$ と見るか $[i, i + 1)$ と見るかの違い）
- **根拠**：E869120 sol/029-02.cpp・Reputeless 029.md はどちらも $[L - 1, R)$。$[L, R + 1)$ でも基本区間の並びは同じ
- **直し方**：「マス $i$ を $[i - 1, i)$ と見て $[L - 1, R)$ に直す（本文の $[L, R + 1)$ と同じことで、どちらでもよい）」とするか、本文にそろえて $[L, R + 1)$ と書く

### 10｜直すとよい｜clarity（U4）｜#practice の「練習の方針」の ABC113 C

- **問題**：「出力は 0 で埋めた桁数に合わせる」は何桁に合わせるのかが分からず、方針として使えない
- **根拠**：drken の記事のコードは県の番号と順位をそれぞれ `%06d` で出す
- **直し方**：「県の番号と順位をそれぞれ 6 桁に 0 で埋めてつなげる」とする

### 11｜直すとよい｜clarity（U3）｜導入「値そのものを捨てて」

- **問題**：#keep-original は「元の値を残す」を節の題にしているので、導入の「捨てて」と食い違って読める
- **直し方**：「値そのものの代わりに『全体で何番目に小さい値か』という番号を使う方法である」のようにする

### 12｜直すとよい｜code（C2）｜snippets の main の assert

- **問題**：compress は `vals[id[i]] == a[i]` だけ、covered-length は `l < r` だけを assert しており、番号の大小の保存や覆われる長さを素朴な方法と比べていない（今回の乱数の比較では誤りはなかった）
- **直し方**：compress に「$a_i < a_j \iff \mathrm{id}_i < \mathrm{id}_j$」の全対の assert、covered-length に座標の小さい cases 用の素朴な数え上げとの比較を足す

## 執筆者の未解決の点について

- abc467_f（frequency_evidence）：ページで使っておらず、このページの問題ではない。台帳の summary は exchange-argument の側で直す話
- 「値の隙間に意味がある問題」に台帳の問題がない点：例の主張自体が誤り（指摘 2）なので、例の差し替えと合わせて考える。問題を付けるなら台帳への追加の提案にする（§13.6）
- prerequisites に sorting-techniques がない点：本文は sort・unique を前提の説明なしに使うが、基礎のページとして困るほどではない。足すかはメインの判断

## 総合の判定

小さな直しで可（直すべき 4 件：導入の「N 個未満」、覆われない最小の整数の例、値の型の理由、ABC036 C の参考の記述。どれも 1〜2 文の差し替えで済む）。

- 台帳の提案：abc213_c・abc113_c・abc036_c・typical90_ac の `checked` は 2026-10-21 のままでよい（今回も evidence で方針を確かめた）
