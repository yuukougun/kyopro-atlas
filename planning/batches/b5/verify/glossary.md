# b5 glossary の検証（2026-10-22）

- 対象：docs/guide/glossary.md（作業ツリーの版。HEAD との差分）
- 観点：fact.md・code.md・clarity.md・figure.md
- 確かめたこと
  - 既存の 117 語：HEAD の版と項ごとに本文を突き合わせ、定義の文が 1 字も変わっていないこと・anchor がすべて残ることを確かめた（スクリプトで比較。変わった項 0、消えた項 0、新しい項 44（語 36・対応表の小見出し 8））
  - `python3 tools/check_pages.py --page glossary`：エラー 0・警告 0
  - `npx textlint docs/guide/glossary.md`：エラー 0・警告 12（既存の項の no-doubled-joshi など。報告どおり）
  - リンク先の anchor：complexity-estimation#constraint-table・#multiple-testcases・#amortized・#constant-factor、cpp-undefined-behavior#assert、interactive#format、acl-reading#conventions、binary-search-answer#monotonicity はすべて存在し、相手は draft
  - ABC の形式：`.cache/atcoder-problems/contests.json` と contest-problem.json で abc476〜abc480 が 7 問・100 分・rate_change「~ 1999」であることを確かめた（「7 問・100 分」「1999 以下が対象」は正しい）
  - 典型90：`python3 tools/ap.py contest typical90` で 90 問、★2（10）・★3（20）・★4（14）・★5（17）・★6（14）・★7（15）、diff はすべて「なし」。表示名「001. Yokan Party（★4）」は台帳・binary-search-answer の書き方と一致。EDPC は dp_a〜dp_z の 26 問・diff なし
  - レベルの帯（基礎 〜1199・発展 2400〜）は planning/decisions.md と一致。difficulty の定義（解ける確率 50% のレート）は research 00-curriculum の AtCoder Problems のスクリプトの記述と一致。MLE の 1024 MiB・TLE の 2 秒は complexity-estimation と一致。ACL v1.6 は acl-reading と一致
  - 対応表と prh.yml：「直す表記」の列の各語を prh.yml の pattern と 1 つずつ照らした（下の 5 以外はすべて prh が拾う）。「別の書き方」の列は付録 A のかっこ書き（diff・答えの二分探索・走査線・動的計画法・LIS・LCS・CHT・DFS・BFS・SCC・LCA・ヒープ・Fenwick Tree・セグ木・遅延セグ木・Mo・CRT・FPS）と過不足なく一致
  - code.md・figure.md：このページにはコード片（snippets/glossary/）・コードブロック・図（docs/img/glossary/）がないので、当てはまる項目なし。atcoder.jp・codeforces.com の URL もない

## 指摘

### 1. 直すべき｜事実（F3・ほかのページとの一致）｜#adt

- 問題：ADT を「毎日開かれる練習用のコンテスト」と書いている
- 根拠：同じバッチで draft になった docs/guide/problem-sets.md の 486 行は「平日に 60 分で出すコンテスト」「2026 年は主に平日に 1 日 2 回開かれている」としている。名前の Daily に引きずられた書き方で、ページどうしが食い違う
- 直し方：「過去の ABC の問題を組み直して、主に平日に開かれる 60 分の練習用のコンテストである」のように problem-sets にそろえる

### 2. 直すべき｜事実（F2 の言い過ぎ）｜#penalty

- 問題：1 文目「誤答を提出するたびに、順位を決める時間に足される時間である」は、解けなかった問題の誤答もペナルティになると読める。2 文目の「AC するまでの誤答」も、AC しなかった問題を除くかどうかがはっきりしない
- 根拠：docs/guide/contest-strategy.md#before-submit（178 行）は「最終的に正解した問題への誤答だけが数えられる」「同点なら最後に正解した時刻＋ペナルティの早い方が上」と書いている。用語集の定義がこれと食い違い、「解けない問題に投げると損」という誤った判断を招く
- 直し方：「最終的に AC した問題について、それまでの誤答 1 回ごとに、順位を決める時間（最後に AC した時刻）に足される時間である。ABC では 1 回 5 分である」のようにする。CE を数えるかの細則は contest-strategy と同じく書かないままでよい（執筆者の未解決の点はこれで足りる）

### 3. 直すべき｜分かりやすさ（U1）・冒頭（F10）｜要点・summary と #canonical-ds

- 問題：要点（と summary）が「表記の正規形（セグ木とセグメント木、Union-Find と DSU など）を引ける」と約束しているのに、対応表にも本文のどこにも DSU がない。冒頭で引けると書いた例そのものが引けない
- 根拠：対応表のデータ構造の行は「Union-Find｜—｜UF・Union Find・ユニオンファインド」だけ。付録 A・prh.yml にも DSU はない（執筆者の手引きへの提案のとおり）。docs では DSU は「DSU on Tree」（small-to-large の別名）と ACL の `dsu` として出る
- 直し方：メインが DSU の扱い（執筆者の案：別の書き方に入れず、ACL の `dsu` を指すときだけコードの名前として使う）を決め、データ構造の表の下に 1 行の注記（例：「DSU は ACL のクラス名 `dsu` を指すときだけ使い、手法の名前としては Union-Find と書く。DSU on Tree はマージテクの別名である」）を足す。決めるまで待つなら、summary の例を「セグ木とセグメント木、最短路と最短経路など」に替える提案にする（要点も同時に）

### 4. 直すとよい｜事実・分かりやすさ（F7・U3）｜#abbreviations

- 問題：(a)「BIT（Fenwick Tree）」は「略称（正式名）」の並びの中にあり、BIT が Fenwick Tree の略に見える。BIT は Binary Indexed Tree の略で、本教材ではそれ自体が正規形である。(b)「本文で使ってよいのはセグ木・遅延セグ木・BIT までで、ほかは正規形で書く」は、対応表で本文に使ってよいとしている DFS・BFS・LCA・SCC・LIS・CRT などの略称を禁じているように読める。(c)「ほかは正規形で書く（対応表）」とあるが、にぶたん・全方位は対応表にない
- 根拠：付録 A「BIT（Fenwick Tree）」は「正規形（別の書き方）」の意味。対応表 #canonical-ds・#canonical-graph
- 直し方：「BIT（Binary Indexed Tree の略。Fenwick Tree ともいう）」と書き分け、最後の文を「このうち本文で使うのはセグ木・遅延セグ木だけで、ほかは正規形（座標圧縮・ローリングハッシュ・二分探索・全方位木 DP など）で書く。DFS・LCA など英字の略称で本文に使ってよいものは[対応表](#canonical-forms)の『別の書き方』にある」のようにする

### 5. 直すとよい｜事実（F7）｜#canonical-graph の「ウォーク」の行と #how-to-read・#canonical-forms の説明

- 問題：「直す表記」の列は「textlint の prh 規則が見つけて正規形に直すもの」と説明しているが、「ウォーク｜—｜歩道」の歩道は prh.yml に規則がない。ほかの行はすべて prh が拾うので、この行だけ説明と合わない
- 根拠：prh.yml のグラフの節に 歩道 の pattern はない。なお docs/graph/k-shortest-paths の summary から生成された lists・llms.txt に「歩道」が 3 か所残っている（このページの範囲外。メインへの参考）
- 直し方：メインが prh.yml に「歩道 → ウォーク」を足すか（問題の要約などで道路の意味の「歩道」とぶつからないか確かめてから）、足さないならこの行を「別の書き方」の注記（「歩道は使わない」）に移し、説明を「直す表記の列は、prh 規則が見つけるもの（歩道を除く）」のようにそろえる

### 6. 直すとよい｜事実（F7）｜#canonical-rules の 1 つ目

- 問題：「人名をつないだ名前は ASCII のハイフンでつなぐ（Aho-Corasick・Sprague-Grundy・Union-Find）」の例に Union-Find が入っているが、Union-Find は人名ではない
- 根拠：Union と Find は操作の名前。手引き §7 の例は Aho-Corasick・Sprague-Grundy だけ
- 直し方：「人名をつないだ名前と、Union-Find のような 2 語の名前は ASCII のハイフンでつなぐ」とするか、例から Union-Find を外す

### 7. 直すとよい｜分かりやすさ（U3）｜#slang の導入

- 問題：「本文では略さない書き方を使い、ここでは読み物で出会ったときの意味を引けるようにする」とあるが、この節の語の多く（典型・考察・愚直解・決め打ち・想定解）は略語ではなく、本文でも使われている（執筆者の数えで考察 53 ページ、愚直 27 ページ）。読者は「本文では使わない語」と受け取る
- 根拠：執筆者の報告の用語集の提案の表
- 直し方：「本文でもそのまま使う語と、本文では正規形に言い換える略称（[略称](#abbreviations)）がある」のように書き分ける

### 8. 直すとよい｜分かりやすさ（U9）｜要点の「使い方」と #how-to-read の 1 つ目

- 問題：「各項は…1〜3 文の定義からなる」「その語の項の 1〜3 文だけを読んで」とあるが、4 文の項が 12 ある（新しい re のほか、既存の amortized-complexity・invariant・representative・potential・inverse-element・multiset・fixed-point・cut・back-edge・labeled-tree・cross-product。句点の数で数えた）
- 根拠：スクリプトで各項の句点を数えた（2 文 82・3 文 58・4 文 12・1 文 1）
- 直し方：「1〜4 文」か「数文」に改める。既存の定義の文は変えない方針なので、説明の方を合わせる

### 9. 直すとよい｜事実（F2）｜#interactive

- 問題：「質問の回数に上限があり」と言い切っているが、回数の上限がない（または計算量だけで縛る）インタラクティブ問題もある
- 根拠：形式の定義としては上限は必須ではない
- 直し方：「多くは質問の回数に上限があり」とする

### 10. 直すとよい｜分かりやすさ（U5）｜#typical90

- 問題：★ の範囲を書いていないので、「★4」がどの程度か見当が付かない（執筆者の未解決の点）
- 根拠：`python3 tools/ap.py contest typical90` で全 90 問の表示名の ★ は 2〜7（★1 はない）。research 00-curriculum 225 行に、作者の記事による ★ と difficulty の対応（★5＝1200〜1599 など）がある
- 直し方：「難しさは ★2〜★7 の ★ の数で示され、」とする。対応の目安を足すなら problem-sets#typical90-stars へのリンクで済ませる（problem-sets は draft になったので、メインが節へ張り替えるときに合わせてよい）

## 執筆者の未解決の点について

- ペナルティ：指摘 2 で、contest-strategy にそろえる形を示した。CE の扱いは書かないままでよい
- 色の境目：灰・水・青・黄・赤だけを書く今の形で誤りはない（400 刻みと書いてあるので茶 400〜・緑 800〜・橙 2400〜は読み取れる）。直さなくてよい
- 典型90 の ★：★2〜★7 と確かめた（指摘 10）
- リンクの張り替え：この検証の時点で debugging-checklist・practice-method・problem-sets・library-design・stress-testing・term-index・cheatsheet は draft になっている（atcoder-system・notation は stub のまま）。執筆者の挙げた張り替え先の anchor は、相手のページの sections を見てメインがバッチの終わりに張り替える（ページへのリンクのままでも規則違反ではない）

## 総合の判定

小さな直しで可（直すべき 3・直すとよい 7）。既存の 117 語は変わっておらず、新しい語の事実（ABC の形式・Rated の範囲・difficulty の定義・典型90・EDPC・ACL の版）は確かめた範囲で正しい。直すべきものは、ほかのページと食い違う ADT とペナルティの記述、要点で約束した DSU が対応表にないことの 3 つで、どれも数行で直せる。
