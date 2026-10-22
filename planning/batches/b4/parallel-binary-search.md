# parallel-binary-search の報告（b4）

- 書いたファイル：docs/ds/parallel-binary-search.md、snippets/parallel-binary-search/usage.{cpp,yaml}、docs/img/parallel-binary-search/rounds.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 8：要点の計算量の行・図の代替テキスト・数式を含む文の長さ、`[l, r)` の括弧の対、数式を挟んだ助詞の重複で、どれも誤検出か数式による長さ）
- 図：rounds.svg（幅 400）を render_svg.py で 360・720 にして目で確かめた。可は実線の枠と太字、不可は破線の枠で、色に頼らない。catalog の visual は static・priority 2 なので動く図は作っていない
- 使った出典：
  - https://drken1215.hatenablog.com/entry/2018/09/15/193722（例題の問いと 2 つの解法）
  - https://buyoh.hateblo.jp/entry/2017/12/08/181813（例題の並列二分探索。再帰の形）。**新しいドメイン**：buyoh.hateblo.jp を check_noai.py で確かめた（X-Robots-Tag なし、meta robots は max-image-preview:large だけ。noai・noimageai の指定なし）
  - https://drken1215.hatenablog.com/entry/2018/09/15/193740（練習の問いの確認）
  - https://cp-algorithms.com/num_methods/binary_search.html（Parallel Binary Search の節。学ぶための資料。文章と図は使っていない）
  - https://oi-wiki.org/misc/parallel-binsearch/（整体二分。学ぶための資料。文章と図は使っていない）
  - https://judge.yosupo.jp/problem/range_kth_smallest（題と問いは GitHub の library-checker-problems の task.md・info.toml で確かめた）

## 台帳への提案

- agc002_d｜evidence｜https://buyoh.hateblo.jp/entry/2017/12/08/181813 を足す（並列二分探索で解く記事。§15-6 の 2 つ以上）
- code_thanks_festival_2017_h｜evidence｜並列二分探索で解いた第三者の解説は見つけられなかった（drken の記事は部分永続 Union-Find の解法だけが読めた部分にある）。alternatives の parallel-binary-search の approach は手法の一般論から明らかなので練習のままでよいと考えるが、裏付けを足すならメインで探してほしい

## 用語集への提案

- なし（オフライン・番兵・単調性は既存の anchor にリンクした）

## 手引き・front matter・catalog への提案

- 他ページのリンクの張り替え（このページが draft になったので §14-23 どおり節へ）：
  - basics/binary-search-answer.md:167 → `../ds/parallel-binary-search.md#what-it-does`
  - ds/offline-queries.md:118 → `#what-it-does`
  - graph/union-find-connectivity.md:165・268 → `#with-union-find`
  - graph/bottleneck-path.md:129 → `#alternatives`
- related に wavelet-matrix を足す案（Library Checker の Range Kth Smallest を並列二分探索でも解けると本文に書き、リンクした）。persistent-data-structures も本文でリンクしている
- 手引きへ：並列二分探索のように ACL に対応がなく acl: [] の発展の概要では、「ライブラリでの使い方」を自作の関数の取り込み（コールバックを受け取る形）で書いた。ほかの発展の概要でも同じ扱いでよいか決めてほしい

## 問題の補充の候補

- 足りているので新しい候補は探していない（例題 1・練習 1・Library Checker 1。発展の概要の目安の範囲）。ABC で並列二分探索が想定の問題は、調査（01・05）でも見つかっていない

## 未解決の点

- 例題 agc002_d の制約（N・M・Q の上限）と「グラフが連結か」は第三者の解説で数値まで確かめられなかったので、本文には書かず、番兵 ok = M + 1 で一般に扱った
- Range Kth Smallest を並列二分探索（BIT）で解いたときに時間制限（5 秒）に収まるかは実測していない。計算量 O((N + Q) log^2 N) だけを書いた
- code_thanks_festival_2017_h の「最後まで同じ集合にならないとき」の出力（-1 と思われる）は本文では「問題に合わせる」とした

## 検証の指摘への対応（verify/parallel-binary-search.md）

- 指摘 1（直すべき）：#procedure の「再帰の形（整体二分）」を、[l, mid) の操作だけ足して判定し取り消してから左右へ再帰し、右へは左半分の寄与を差し引いて渡す形に書き直した。「同じ深さの区間を左から順に」の文は削った
- 指摘 2〜6（直すとよい）：すべて採った。段の数を「高々」にして図の 3 段の理由を添えた。Union Sets は -1 を出力と明記。agc002_d は連結なので全辺で必ず満たすと書いた。「想定の解き方の 1 つ」を「代表的な解き方」にした。リンクを節へ張り替えた（persistent-data-structures#prefix-versions、binary-search#meguru、partially-persistent-union-find・cdq-divide-and-conquer・wavelet-matrix の #what-it-does）
- 採らなかった指摘：なし
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 8 は以前と同じ種類）

### 台帳への提案（検証を受けて追加）

- code_thanks_festival_2017_h｜checked｜2026-10-22（問いと -1 の出力を drken の記事で検証役が確かめた）
- agc002_d｜checked｜2026-10-22。evidence に buyoh の記事を足す案は上のとおり
- agc002_d｜summary｜「x と y の成分の頂点数の合計」を「x と y の成分を合わせた頂点数」に（同じ成分のときの二重計上と読まれないように）。本文の例題の要約も同じ文なので、メインで台帳を変えるときに本文もそろえてほしい
