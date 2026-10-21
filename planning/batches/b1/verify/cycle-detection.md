# cycle-detection の検証（工程8b・b1）

- 対象：docs/graph/cycle-detection.md、snippets/cycle-detection/{directed,undirected}.{cpp,yaml}、docs/img/cycle-detection/three-color.svg（動く図はない）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page cycle-detection -v`（エラー 0・警告 0）、`python3 tools/fix_problems.py --page cycle-detection --check`（直すべき行 0）、`python3 tools/check_snippets.py snippets/cycle-detection`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/graph/cycle-detection.md`（0 errors・1 warning。217 行の参考の ikatakos 氏の記事の題名による sentence-length。題名なので残してよい）
- front matter：執筆者が変えたのは complexity・stage・updated だけ（報告どおり）。complexity・要点の計算量・本文（DFS・Kahn 法は $O(N + M)$、Union-Find はならし $O(M \alpha(N))$）が一致する。sections の 6 節は見出しの文字と title・anchor が一致し、定型の節（落とし穴・使い分け・例題・練習問題・力試し・参考）は sections に載っていない（§13.1）。別名の行に aliases がすべてある
- コード片（C1〜C8）
    - 2 片とも `-fsanitize=address,undefined` 付きでコンパイルし、乱数のグラフ（$N \le 7$・$M \le 9$、自己ループ・多重辺を含む）3000 個ずつで動かした。サニタイザの報告・assert の失敗なし。閉路の有無は、有向は Kahn 法、無向は Union-Find の素朴な判定と 3000 個すべて一致。無向の出力は、頂点が重複せず、閉路の各辺が入力の辺の本数の範囲で使われている（長さ 2 の閉路は平行な 2 本があるときだけ出る）ことを別のプログラムで確かめた（作業用の場所 v-cycle-detection/gen.py・brute.py・chk2.py）
    - cases：空（辺なし）・自己ループ・完了した頂点への辺（図の左と同じ形）・しっぽ付きの閉路・長さ 2・頂点 0 から届かない閉路（有向）、木・多重辺・三角形・2 つ目の成分の閉路（無向）。期待出力を手で確かめ、正しい。出力した閉路が本当に閉路かを main の assert で確かめている
    - 本文との一致：color/state の 0・1・2、`par`、来た辺の番号 `pe` での除外、見つけたら `true` を返して打ち切ること、復元の擬似コード（$v$ から $\mathrm{par}$ を $u$ までたどって逆順）が本文と一致。取り込みは core の範囲だけ
    - 書き方：DFS は `-> bool` で `p` の引数がなく、§9 の `-> void` の形と違うが、見つけた時点で打ち切るためで、本文（#restore）がその理由を書いているので指摘にしない
- 自分で導いた主張の確認
    - Union-Find で閉路を作る辺が $M - (N - C)$ 本：併合に成功した辺が森をなすことから正しい（自己ループ・多重辺も「同じ成分」で数えられる）
    - 確認問題 1 の答え（入る辺・出る辺が高々 1 本なら、無向の閉路は向きのそろった有向の閉路）：無向の閉路上の頂点は次数 2 で、入・出が高々 1 本ずつなので入 1・出 1 になり正しい
    - Kahn 法の残りの例（$0 \to 1 \to 2 \to 0$、$2 \to 3$ で 3 が残る）、残った頂点で逆向きにたどれば閉路が取れること、確認問題 2 の反例（$0 \leftrightarrow 1 \to 2 \to 3 \leftrightarrow 4$ で 2 が残る）：どれも正しい
    - 出次数 1 のグラフ：$N$ 歩で同じ頂点に 2 回来ること、$N$ 歩進んだ頂点は閉路上にあること、入次数 0 から剥がすと残るのはちょうど閉路上の頂点であることを、乱数の Functional graph（$N \le 9$）2 万個で確かめた（すべて一致）
    - 「状態の配列を探索ごとに初期化すると $O(N(N + M))$」「自己ループは scc の成分の大きさに表れない」も正しい
- ACL（F4）：document_ja の dsu.md（`merge`・`same` はならし $O(\alpha(n))$）、scc.md（`scc_graph g(n)`・`add_edge(from, to)`・`scc()` は `vector<vector<int>>` で $O(n + m)$）と一致
- 問題（F5）：4 問とも `python3 tools/ap.py show` で題名・diff（663・436・448・1214）が本文・台帳と一致。役割（例題 1・練習 2・力試し 1）は台帳のとおり。要約は台帳の summary そのままで手法名を含まない
    - abc285_d：kyo-pro・dokaraya の記事で方針（名前を頂点、変更を辺 $S \to T$ にした有向グラフで閉路があれば No）を確かめた。執筆者の未解決の点の制約は、kazun 氏の記事（https://kazun-kyopro.hatenablog.com/entry/ABC/285/D 、付録 B のブログ）の「制約」の節で、$S_i \ne T_i$、$S_1, \dots, S_N$ が相異なる、$T_1, \dots, T_N$ が相異なる、の 3 つが挙がっていることを確かめた。よって各名前の出次数・入次数は高々 1 で、Union-Find の判定は正しく、「閉路がなければ順に変えられる」も成り立つ（指摘 1）
    - abc288_c：kyo-pro の記事は「両端がすでに同じ成分なら数える」。式 $M - (N - C)$ は記事にない（指摘 4）
    - abc311_c：drken の記事は「$N$ 回たどれば閉路の内部にいる、そこから一周」で本文と一致
    - abc456_e：ikatakos 氏の記録の解法の部分だけを読んだ。出発の都市は自由で、（都市, 曜日）を頂点、とどまる辺を含めて休日どうしを翌日へ結び、出次数 0 の頂点を剥がして残れば Yes。本文の方針と一致
- 参考の URL（F9）：8 件の Web の URL を開き（ACL・Library Checker は GitHub）、題名・著者は書かれたとおり。プロひろの記事は seen・finished の 2 つの印、dokaraya の記事は 3 状態の DFS で、本文の「参考にした点」と一致。本文の文・例は記事と並びも例も違い、近すぎる箇所はない（F8）
- リンク先：dfs・union-find・topological-sort・scc・functional-graph・namori-graph・periodicity は draft、cpp-environment・lowlink は stub（ページ単位のリンクなので §13.4 によりよい）。periodicity#rho の節はある
- 図 three-color.svg：Windows の Chrome（headless=new）で、等倍（640×300、2 倍密度）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（作業用の場所 v-cycle-detection/full.png・narrow.png）。左は A→B、A→C、C→B（点線）で B が完了・A と C が探索中、右は A→B→C→A で C→A が太い赤。矢印の向き・状態のラベル・代替テキスト・本文の説明・有向の cases（3 3 / 0 1 / 0 2 / 2 1 → -1）が一致する。背景は白、`viewBox` あり、文字はテキストで `font-family="sans-serif"`、色に加えて点線・太線・「完了」「探索中」の文字で区別。はみ出し・重なりはない。幅 358px では小さい文字が読みにくい（指摘 5）
- 執筆者の未解決の点：(1)(2) abc285_d の制約は上のとおり確かめられた（指摘 1）。(3) dfs.md は今は draft で中身がある

## 指摘

直すべき指摘はない。

### 1｜直すとよい｜fact（F5）・clarity（U7）｜#abc285_d の「解法の詳細」の最後の項目と方針の段落

- **問題**：「各名前から出る辺・入る辺が高々 1 本のときに正しい。そう言えるかは問題の制約で確かめる」と条件付きで書いてあり、読者に確かめを任せている。制約（$S_i$ が相異なる・$T_i$ が相異なる）は第三者の記事で確かめられたので、言い切れる。方針の段落の「閉路がなければ…順に変えていけばよい」も、この制約に支えられていることが書いてあると分かりやすい
- **根拠**：kazun 氏「AtCoder Beginner Contest 285 D問題 Change Usernames」（https://kazun-kyopro.hatenablog.com/entry/ABC/285/D）の制約の節。$S$ が相異なれば出次数、$T$ が相異なれば入次数が高々 1
- **直し方**：最後の項目を「変更前の名前どうし・変更後の名前どうしはそれぞれ相異なるので、各名前から出る辺・入る辺は高々 1 本である。このとき[確認問題](#directed)のとおり、向きを無視した Union-Find で『両端がすでに同じ成分なら No』と判定しても正しい」とする。参考に kazun 氏の記事を足し（参考にした点：制約）、台帳の evidence の追加を提案する（下）

### 2｜直すとよい｜clarity（U2・U3）｜#directed の「$u$ が完了なら、$u$ から $v$ へ戻る道はない」の段落（69 行）

- **問題**：場合分けの議論が飛んでいる。「$v$ が $u$ より後で訪れた頂点なら、道があれば $v$ は $u$ の探索の中で訪れられ」は、その道が $u$ を探索した時点で探索中・完了の頂点を通る場合を扱っていない。結論は正しいが、レート 1000 前後の読者にはなぜかが読み取りにくい
- **根拠**：clarity U2。白い道の定理の前提（道の頂点がすべて未訪問）が書かれていない
- **直し方**：不変条件 1 つで言う。「頂点が完了するのは、出る辺の先がすべて完了したときだけである（未訪問なら先に探索して完了させ、探索中なら閉路として止まる）。だから完了した頂点から行ける頂点はすべて完了している。$v$ は探索中なので、完了した $u$ から $v$ へ戻る道はなく、辺 $v \to u$ は閉路を作らない」

### 3｜直すとよい｜clarity（U2）｜#kahn-leftover の「閉路上の頂点はどれも、閉路の 1 つ前の頂点から入る辺が消えないので」（89 行）

- **問題**：「1 つ前の頂点の辺が消えない」は、その 1 つ前の頂点も取り出されないことを前提にしていて、理由が循環して読める
- **根拠**：clarity U2
- **直し方**：「閉路の頂点のうち最初に取り出されるものがあったとすると、その時点で閉路の 1 つ前の頂点はまだ残っているので、入次数は 0 でなく取り出せない。だから閉路の頂点は 1 つも取り出されない」とする

### 4｜直すとよい｜fact（F9）｜#references の kyo-pro「ABC288C - Don’t be cycle」の行（215 行）

- **問題**：参考にした点に「$M - (N - C)$ の式」とあるが、記事には式はなく、Union-Find で閉路を作る辺を数える方法だけが書かれている。式は執筆者が導いたもの（正しい）
- **根拠**：https://kyo-pro.hatenablog.com/entry/2023/02/04/224004 を読んだ結果
- **直し方**：参考にした点を「練習の方針（Union-Find で閉路を作る辺を数える）」にする。式の理由は本文 #undirected にすでにある

### 5｜直すとよい｜figure（G3）｜three-color.svg の小さい文字

- **問題**：幅 640 の図に 12〜13 の文字（「探索中」「完了」「C → B（点線）」、下の 2 行）が多く、スマホの幅 358px に縮めると約 7px になり読みにくい。図の形と色は読める
- **根拠**：v-cycle-detection/narrow.png（幅 390px の画面、Chrome headless=new）
- **直し方**：状態のラベル・辺のラベル・下の説明を 15〜16 に上げる（下の 2 行の説明は本文と代替テキストにあるので、1 行にまとめるか消してもよい）。上の見出しも 16 程度にする

## 提案（メイン向け）

- 台帳 abc285_d：evidence に https://kazun-kyopro.hatenablog.com/entry/ABC/285/D（制約の確認）と https://zenn.dev/dokaraya/articles/atcoder-abc285d（3 状態の DFS）を足す。approach の執筆者の提案（「…閉路があれば不可能（3 色の DFS か Kahn 法で判定）」）に賛成
- 台帳の `checked` に 2026-10-21 を入れてよい：abc285_d・abc288_c・abc311_c（abc456_e は入っている）
- 台帳 abc288_c・abc456_e の summary の末尾の「。」：執筆者の提案のとおり、ほかの行とそろえるとよい（表記だけ）

## 総合の判定

**小さな直しで可**（直すべき 0・直すとよい 5）。事実・コード片・図に誤りはなく、直すとよいのは説明の飛躍 2 件・例題の言い切り・参考の行・図の文字の大きさ。
