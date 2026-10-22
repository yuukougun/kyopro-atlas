# wavelet-matrix の報告と提案（b4）

- 書いたファイル：docs/ds/wavelet-matrix.md、snippets/wavelet-matrix/wm.{cpp,yaml}、docs/img/wavelet-matrix/levels.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections はそのまま
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 36 は数式の括弧・数式を含む文の長さ・読点の数、および要点の囲みの summary と同じ文の助詞の重複）
- 図：levels.svg（静的、幅 400）。render_svg で 360・720 の PNG にして目で確かめた。catalog の visual は priority 2 の static なので、動く図は作っていない
- 使った出典：convexineq（Qiita、段の作り方と和）、miti-7.hatenablog.com（操作の一覧。check_noai で noai・noimageai の指定なしを確認、2026-10-22）、ei1333 のライブラリ（操作と計算量）、drken（abc324_g の解法）、kmjp（abc339_g がオンライン強制であること）、tayu0110（abc339_g の解法。Wavelet Matrix には触れていない）、GitHub の yosupo06/library-checker-problems（4 問の問いと制約）

## 台帳への提案

- abc339_g｜evidence（wavelet-matrix の練習としての裏付け）｜読んだ 2 つの解説（tayu0110・kmjp）はどちらもマージソート木・平方分割で、Wavelet Matrix には触れていない。Wavelet Matrix の和の累積で解けることは convexineq の記事の「和は段ごとの累積和で」で裏付けられる。Wavelet Matrix で解いた第三者の解説を 1 本足せるとよい（未確認）
- abc324_g｜evidence｜drken の記事のみ。2 本目の裏付け（動的 2 次元 BIT の解き方の第三者の解説など）は未確認

## 用語集への提案

- 簡潔ビットベクトル｜succinct-bit-vector｜bit 列を 64 bit ごとのブロックに分け、ブロックごとの 1 の個数の累積と popcount を持つことで、先頭 i 個の中の 1 の個数を O(1) で答える表現。メモリは bit 列の長さの数倍の bit で済む。（本文では短く定義し、リンクは張っていない）

## 手引きへの提案

- なし

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 探していない。台帳の 2 問（例題 abc324_g・練習 abc339_g）で発展の概要の目安（例題 0〜2）を満たすため。練習は Library Checker の 4 問（range_kth_smallest・static_range_frequency・static_range_sum_with_upper_bound・rectangle_sum）を §15-5 の形で置いた

## front matter・catalog

- verify に static_range_frequency・static_range_sum_with_upper_bound・rectangle_sum を足すことを提案（本文の Library Checker の節に載せた。どれも静的で Wavelet Matrix で解ける）

## 未解決の点

- abc324_g の問題文は読めないので、解法の詳細で値による分割の境界は「問題の x を値の境界 t（t 未満が元の列に残る）に直す」と一般的に書いた。x が「x 未満」か「x 以下」かで t = x か x + 1 かが変わる。drken の記事は境界を値の区切りに合わせて収めると書くだけで、どちらかを本文で断定していない。検証役は台帳の summary（「値が x 未満」）と合わせて確かめてほしい
- 本文の「ABC の問題はほぼ足りる（3 種類の操作）」は経験則の書き方で、出典はない。気になるなら削ってよい
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 7 回

## 検証の指摘への対応（2026-10-22）

- 指摘 1（直すべき）：本文の解法の詳細に「値を 0 始まりにした順列では、問題の『値が x 以下（1 始まり）を残す』は『0 始まりの値が x 未満』なので t = x」の 1 文を足した。例題の囲みの要約は台帳から生成されるので、台帳の直しを下の提案に書いた
- 指摘 2：取り込み `wm.cpp:core` の範囲を kth_smallest と count_sum_less の 2 関数に絞り、本文で変数（zero・nz・sum）と記号の対応を 1 文で添えた。構築は完全なプログラムの案内に任せた
- 指摘 3：「1/32」を「64 bit ごとに 32 bit の累積を持っても 1 要素あたり 1.5 bit で、1/20 ほど」に直した
- 指摘 4：「ABC の問題はほぼ足りる」を「まず持たせるとよい」に言い換えた
- 指摘 5：段の作り方の節に「この 2 分木の形のものが Wavelet Tree」「Wavelet Matrix は各ノードを段ごとの並びにまとめて配列だけで書けるようにしたもの」を足した
- 指摘 6：サインの 1 行目を「x 未満（x 以下なら x + 1 未満）の個数・和」にした
- 指摘 7：図の「0 は 4 個」を「Z₀ = 4」などに直し、alt も合わせた。例の区間の太枠は採らなかった（必須ではなく、本文の箇条で区間と値を段ごとに書いているので追える）

## 台帳への提案（検証の後）

- abc324_g｜summary｜「順列から始め、「先頭 x 個を残す」「値が x 以下のものを残す」で列を 2 つに分けるクエリごとに、新しくできた列の長さを答える。」に直す（今の「値が x 未満」は境界が逆。kmjp の文とコード、drken のコードが「x 以下を残す」で一致）。evidence に https://kmjp.hatenablog.jp/entry/2023/10/14/1000 を足し、checked に 2026-10-22。直した後に fix_problems を流せば本文の囲みも追随する
- abc339_g｜checked に 2026-10-22（検証役が kmjp の解説で確かめた）
- 用語集「簡潔ビットベクトル」：本文の「1/32」は「1/20 ほど」に直した。定義の「メモリは bit 列の長さの数倍の bit」はそのままでよい
