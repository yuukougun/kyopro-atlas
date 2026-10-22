# 検証：wavelet-matrix（b4）

- 対象：docs/ds/wavelet-matrix.md、snippets/wavelet-matrix/wm.{cpp,yaml}、docs/img/wavelet-matrix/levels.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py（chrome-headless-shell 146）で 360px・720px の PNG にして目視（ライトのみ。SVG は白の背景つき）

## 実行した検査と結果

- `python3 tools/check_pages.py --page wavelet-matrix`：エラー 0・警告 0
- `python3 tools/check_snippets.py wavelet-matrix`：コード片 1・期待と違う 0
- `g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined snippets/wavelet-matrix/wm.cpp`：警告なし。cases 1・3 の入力で実行し、期待どおりの出力でサニタイザの報告なし。main の中の乱択の比べ合わせ（n ≤ 8、lg ≤ 4、全区間・全 k・x = −1〜2^lg+1）も assert を通る
- `npx textlint docs/ds/wavelet-matrix.md`：エラー 0・警告 36（執筆者の報告と同じ。数式・参考の行の長さの誤検出）
- 手計算：図の 3 段（(2,1,3,0|5,7,6,4)・(1,0,5,4|2,3,7,6)・(0,4,2,6|1,5,3,7)、どの段も 0 は 4 個）と、本文の K 番目の例（[1,6) の K=2 → [0,3) → [4,6) → 011₂ = 3）を確かめた。どちらも正しい。メモリの見積もり 4NL = 4·2·10^5·18 ≈ 14.4 MB も正しい
- Library Checker の 4 問：GitHub の yosupo06/library-checker-problems の task.md で問いを確かめた（range_kth_smallest は k_i+1 番目、static_range_sum_with_upper_bound は x 以下の個数と総和、rectangle_sum は l ≤ x < r, d ≤ y < u の重みの和）。本文の書き方と一致する
- 参考の URL：convexineq（Qiita）・miti-7・ei1333・kmjp（abc339）を開き、題名が書かれたとおりであることを確かめた。miti-7.hatenablog.com は check_noai で「noai・noimageai の指定はない」。ei1333 のドキュメントの操作（kth_smallest・range_freq・prev_value・next_value、CompressedWaveletMatrix）と計算量 O(MAXLOG) は本文の記述と合う
- 台帳：abc324_g（diff 2501）・abc339_g（diff 1792）は `tools/ap.py show` の値と一致

## 指摘

### 1｜直すべき｜事実（F5）｜例題 abc324_g の囲みの要約（台帳の summary）

- **問題**：要約の「値が x 未満」で分割する、は境界が逆らしい。値による分割で元の列に残るのは「値が x 以下」で、新しい列に移るのは「値が x より大きい要素」である
- **根拠**：kmjp の解説（https://kmjp.hatenablog.jp/entry/2023/10/14/1000 。付録 B の kmjp.hatenablog.jp）は問題の整理に「X より大きな要素を取り除いて A[i] に入れる」と書き、コードも新しい列の値の範囲を [x+1, VR]、元の列を [VL, x] にしている。evidence の drken の記事（https://drken1215.hatenablog.com/entry/2023/10/15/020209）は本文で「x 未満のものだけを残す」と書くが、コードはクエリ 2 で `++v` してから境界にしていて、kmjp と同じ「x 以下を残す」になる。3 つ（kmjp の文・kmjp のコード・drken のコード）が「x 以下を残す」で一致し、drken の文だけが食い違う。執筆者が未解決の点に挙げたとおり、台帳の summary は drken の文から取ったと見られる
- **直し方**：台帳の abc324_g の summary を「順列から始め、「先頭 x 個を残す」「値が x 以下のものを残す」で列を 2 つに分けるクエリごとに、新しくできた列の長さを答える。」のように直し（メインが台帳を直して fix_problems を流す。catalog の problems の summary は凍結なので触れない）、evidence に kmjp の URL を足す。本文の解法の詳細は境界を一般に書いているので誤りではないが、値を 0 始まりにした順列なら「値が x 以下（1 始まり）を残す」は「0 始まりの値が x 未満」なので t = x、と 1 文で書けば読者が迷わない（直すとよい）。台帳の checked に 2026-10-22 を入れる提案も添える

### 2｜直すとよい｜コード（C4）・分かりやすさ（U10）｜段の作り方の節の取り込み `wm.cpp:core`

- **問題**：取り込みの範囲が構造体の全体（構築・K 番目・x 未満の個数と和、約 55 行）で、手引き §3「コードの全体は載せない」・§9「要点の数行と処理の流れ」・§4 の発展の概要「実装の流れは資料に任せる」より重い。本文の文章だけで手順が十分に書けているので、全体を見せる必要は薄い
- **根拠**：snippets/wavelet-matrix/wm.cpp の `[start:core]`〜`[end:core]` が struct の最初から最後まで
- **直し方**：取り込みを `kth_smallest` と `count_sum_less` の 2 関数（または K 番目だけ）に絞り、構築は「完全なプログラムは wm.cpp」の案内に任せる。`[start:query]` のような名前の範囲を足せば済む

### 3｜直すとよい｜事実（F2）｜段の作り方の節「自作するときの要点」のメモリ

- **問題**：「bit 列を 64 bit ごとにまとめ、ブロックごとの累積と popcount で…メモリは 1/32 ほどになる」は、ブロックごとの累積の分を数えていない。64 bit ごとに 32 bit の累積を持つ素朴な形では 1 要素あたり 1.5 bit で、`int` の 32 bit に比べて 1/21 ほどである
- **根拠**：(64 + 32) / 64 = 1.5 bit/要素、32 / 1.5 ≈ 21
- **直し方**：「メモリは 1/20 ほどになる」か「数十分の 1 になる」とする

### 4｜直すとよい｜事実（F2）・分かりやすさ（U2）｜ライブラリでの使い方の節「3 種類あれば ABC の問題はほぼ足りる」

- **問題**：出典のない経験則で、執筆者も未解決の点に挙げている。言い切ると根拠のない主張になる
- **根拠**：参考の資料（ei1333・miti-7）は操作の一覧を示すが、ABC で足りるかは述べていない
- **直し方**：「まず持たせるとよいのは…の 3 種類である」のように、推奨の形に言い換える（または文を削る）

### 5｜直すとよい｜分かりやすさ（U3）｜冒頭の別名と導入

- **問題**：別名に Wavelet Tree があるが、本文は Wavelet Tree と Wavelet Matrix の違いに触れない。「Wavelet Tree」で引いた読者は同じものか別のものか分からない（段の作り方の節の「2 分木を値の上位 bit で降りるのと同じだが…1 本の並びにまとめている」が答えに近いが、名前を出していない）
- **直し方**：段の作り方の節のその文に「この 2 分木の形のものが Wavelet Tree で、Wavelet Matrix は各段をまとめて配列だけで書けるようにしたもの」と 1 句足す

### 6｜直すとよい｜記法（F7）｜何ができるかの節のサイン

- **問題**：サインの 1 行目だけ「x 以下の個数・和」で、節の題・要点・コードは「x 未満」。練習の abc339_g が「X 以下」なので意図は分かるが、同じ節で表記が揺れる
- **直し方**：「$x$ 以下（$x + 1$ 未満）の個数・和」のように 1 回だけ対応を添えるか、「$x$ 未満」にそろえる

### 7｜直すとよい｜図（G5）｜levels.svg

- **問題**：図は正しく読みやすい（360px で文字は 10px ほど、はみ出し・重なりなし）が、本文の K 番目の例（[1,6) → [0,3) → [4,6)）が図の上に示されていないので、例を追うときに区間の位置を自分で数えることになる。右端の「0 は 4 個」が本文の記号 $Z_d$ と結び付いていない
- **直し方**：「0 は 4 個」を「$Z_d$ = 4」相当の書き方（「Z = 4」など）にする。余力があれば例の区間を各段で太枠にする。必須ではない

## 執筆者の未解決の点への答え

- abc324_g の境界：指摘 1 のとおり、元の列に残るのは「値が x 以下」と判断した（kmjp の文とコード、drken のコードが一致）。本文の一般的な書き方は誤りではない
- 「ABC の問題はほぼ足りる」：指摘 4。言い換えか削除を勧める

## 提案（メイン向け）

- 台帳 abc324_g：summary の直し（指摘 1）、evidence に https://kmjp.hatenablog.jp/entry/2023/10/14/1000 を足す、checked に 2026-10-22
- 台帳 abc339_g：checked に 2026-10-22（kmjp の解説でオンライン強制と X 以下の和であることを確かめた）
- front matter の verify に static_range_frequency・static_range_sum_with_upper_bound・rectangle_sum を足す執筆者の提案に賛成（task.md で問いを確かめた）
- 用語集「簡潔ビットベクトル」の提案は、定義の「メモリは bit 列の長さの数倍の bit」と合わせて、本文の「1/32」を指摘 3 のとおり直してからがよい

## 総合の判定

小さな直しで可。直すべき 1 件（台帳の summary の境界。直すのはメインの台帳の作業で、本文は fix_problems で追随する）、直すとよい 6 件。本文の手順・例・計算量・コードは正しく、コードは乱択の比べ合わせとサニタイザを通った。
