# parallel-binary-search の検証（b4）

対象：docs/ds/parallel-binary-search.md、snippets/parallel-binary-search/usage.{cpp,yaml}、docs/img/parallel-binary-search/rounds.svg
観点：fact.md・code.md・clarity.md・figure.md（検証役は執筆者と別のエージェント）

## 確かめたこと（記録）

- `python3 tools/check_pages.py --page parallel-binary-search`：エラー 0・警告 0
- `python3 tools/check_snippets.py parallel-binary-search`：コンパイル 1 回・期待と違う 0
- コンパイラ：`g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0`。`g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` で警告なし。乱択の入力 500 個（N ≤ 7、M ≤ 10、Q ≤ 8、自己ループ・多重辺・M = 0 を含む）で、コード片の中の assert（素朴な方法との照合）がすべて通り、サニタイザの報告もない
- `npx textlint`：エラー 0、警告 8（執筆者の報告と同じ。数式による文の長さ・助詞の重複など）
- `python3 tools/ap.py show agc002_d code_thanks_festival_2017_h`：Stamp Rally は diff 2514、Union Sets は diff なし。本文の（diff 2514）（diff —）と一致する
- 図：`python3 tools/render_svg.py` で 360・720 の PNG にして目で見た。文字の重なり・はみ出しはない。可は実線と太字、不可は破線で、色に頼っていない。背景は白で塗ってある。viewBox 400×290 と width・height の比が同じ
- 図の値を手で追った（ng = -1、ok = 8 から）：1 段目 mid は 3・3・3（A 可、B・C 不可）、2 段目 A は (3 - 1)/2 = 1 で不可、B・C は (8 + 3)/2 = 5 で B 可・C 不可、3 段目 A は 2 で可、B は 4 で不可、C は 6 で可。ok = 2・5・6 で、図・代替テキストと一致する
- 段の数 ⌈log₂(M + 2)⌉：幅 w が 1 段で ⌈w/2⌉ 以下になるので上限として正しい。M = 7 で答えが 7 のクエリは 4 段かかる（3 → 5 → 6 → 7）
- 例題の事実：drken の記事（https://drken1215.hatenablog.com/entry/2018/09/15/193722）に「グラフは連結です」とあり、解法 1 が部分永続 Union-Find、解法 2 が並列二分探索。本文と一致する。執筆者の未解決の点 1 のうち「連結か」はこれで確かめられた
- 練習の事実：drken の記事（https://drken1215.hatenablog.com/entry/2018/09/15/193740）に「最後まで別離しているときは -1」とある。執筆者の未解決の点 3 は -1 で確定。記事の題は「CODE THANKS FESTIVAL 2017 H - Union Sets (3D, 600 点)」で参考の書き方と一致し、読める範囲の解法は部分永続 Union-Find だけ
- Library Checker：library-checker-problems の data_structure/range_kth_smallest の task.md で「k_i + 1 番目に小さい値」、info.toml で N ≤ 200000・時間制限 5 秒を確かめた。sol/correct.cpp はビットベクトルを使う（Wavelet Matrix の系統）
- 未解決の点 2（Range Kth Smallest を並列二分探索で解いて時間内か）：BIT と並列二分探索で書いたプログラムを、N = Q = 200000 の乱択の入力で動かして 0.24 秒（手元、-O2）。小さい入力 50 クエリで素朴な方法と出力が一致した。本文の O((N + Q) log² N) と「並列二分探索で解ける」は問題ない
- 参考の URL：buyoh.hateblo.jp は付録 B にないので `tools/check_noai.py` で確かめた（X-Robots-Tag なし、meta robots は max-image-preview:large だけ、noai の指定なし）。題は「AtCoder Grand Contest 002 - D Stamp Rally」で、並列二分探索と再帰の話がある。cp-algorithms の Binary search のページに Parallel Binary Search の節と Fenwick tree の例がある。OI Wiki「整体二分」は再帰の形と区間の K 番目を扱う
- リンク先の anchor：glossary の #offline・#sentinel、union-find-applications の #data-on-root、union-find-connectivity の #binary-search はどれもある。merge-process-tree は stub なのでページへのリンクで正しい

## 指摘

### 1｜直すべき｜事実（F2）・分かりやすさ（U4）｜#procedure の「再帰の形（整体二分）」の箇条

- **問題**：「同じ深さの区間を左から順に処理すれば、操作は深さごとに 1 回流すだけで済む。…値の順に要素を足す型（区間の K 番目など）では、この形で書かれることが多い」と書いてある。しかし、よく書かれる再帰の形（OI Wiki の整体二分、buyoh の記事の再帰）は、深さごとに左から流す（実質は反復の形と同じ幅優先）ものではない。深さ優先で再帰し、各節では区間 [l, mid) の操作だけを足して判定し、判定の後で取り消す。右へ送るクエリは、左半分の寄与（区間の K 番目なら数えた個数 t）を K から引いて渡す。だから操作は各深さで合わせて M 回で済む。本文の説明のまま再帰を書くと、右の子が「最初の mid 回の操作の後の状態」を必要とする点の扱いが分からず、素朴に作り直すと計算量が崩れる
- **根拠**：OI Wiki「整体二分」の区間第 k 小の参考コード（各 solve で値が [l, m] の要素だけ add し、判定後に add(-1) で取り消し、右へ送るクエリは `q[i].k -= t`）。この書き方は寄与が足し引きできること（OI Wiki の条件「贡献…具有可加性」）に頼っており、Union-Find のように取り消せない操作では、そのままでは使えない（取り消せる Union-Find などが要る）
- **直し方**：箇条を次の趣旨に直す。「区間 [l, r) と、答えがそこにあるクエリの組を受け取り、[l, mid) の操作だけを足して判定し、取り消してから左右に分けて再帰する書き方もある。右へ送るクエリには左半分の寄与を差し引いて渡す（区間の K 番目なら K から個数を引く）。各深さで操作は合わせて M 回なので計算量は同じ。寄与を足し引きできる BIT の型でよく使い、取り消せない Union-Find では反復の形が手軽」。「同じ深さの区間を左から順に」の文は削る

### 2｜直すとよい｜事実（F2）・分かりやすさ（U3）｜#procedure の計算量の根拠の 1 つ目

- **問題**：「段の数は ⌈log₂(M + 2)⌉ = O(log M) である」は上限であって、ちょうどその数ではない。直前の図は M = 7 で 3 段で終わっているが、式は 4 になるので、読者が食い違いと取りうる
- **根拠**：幅 w は 1 段で ⌈w/2⌉ 以下になる。M = 7 で答えが 7 のクエリは mid = 3, 5, 6, 7 の 4 段かかり、図の 3 クエリは 3 段で済む
- **直し方**：「段の数は高々 ⌈log₂(M + 2)⌉ である（図の例は答えの位置がよいので 3 段で済んだ）」とする

### 3｜直すとよい｜事実（F5）・分かりやすさ（U7）｜#practice の「方針」（Union Sets）

- **問題**：「その場合の出力を問題に合わせる」とぼかしているが、出力は確かめられた
- **根拠**：drken の記事の問題概要に「最後まで別離しているときは -1」
- **直し方**：「ok が番兵の M + 1 のまま残るクエリは -1 を出力する」と書く（コード片の main の出力と同じ扱いになる）

### 4｜直すとよい｜事実（F5）｜#agc002_d の「解法の詳細」の 3 つ目

- **問題**：「全辺を使っても満たさない場合に備えて、番兵は ok = M + 1 のままでよい」とあるが、この問題はグラフが連結で z ≤ N なので、全辺を使えば必ず満たす。誤りではないが、「満たさない場合がある」と読める
- **根拠**：drken の記事の問題概要「グラフは連結です」
- **直し方**：「グラフは連結なので、全辺を使えば必ず満たし、答えは M 以下に決まる。番兵は ok = M + 1 のままでよい」とする

### 5｜直すとよい｜分かりやすさ（U6）・規則（§14-23）｜#alternatives の永続データ構造へのリンク、#procedure の二分探索へのリンク

- **問題**：draft のページへのリンクがページ単位のまま。永続データ構造は「過去の版を持つ構造」の例として引いており、その話の節 #prefix-versions（接頭辞ごとの版で区間の K 番目）がある。二分探索は ng と ok の不変条件の話で、節 #meguru がある
- **根拠**：docs/ds/persistent-data-structures.md・docs/basics/binary-search.md の sections（どちらも HEAD で draft）
- **直し方**：`../ds/persistent-data-structures.md#prefix-versions`、`../basics/binary-search.md#meguru` へ張り替える。部分永続 Union-Find・CDQ 分割統治・Wavelet Matrix は今回のバッチで draft になったので、メインの張り替えに含める（例：`partially-persistent-union-find.md#what-it-does`、`cdq-divide-and-conquer.md#what-it-does`、`wavelet-matrix.md#what-it-does`）

### 6｜直すとよい｜事実（F5）｜#practice の Library Checker の行

- **問題**：「想定の解き方の 1 つは Wavelet Matrix」の「想定」は、Library Checker が想定解を公表しているように読める
- **根拠**：問題の文と info.toml に想定の記述はない。sol/correct.cpp はビットベクトル（Wavelet 系）だが、これは参照解である
- **直し方**：「代表的な解き方は Wavelet Matrix である」とする

## 執筆者の未解決の点への答え

1. agc002_d の「グラフが連結か」：連結（drken の記事）。指摘 4 で本文に反映を勧める。制約の数値は今回は確かめていない（本文に書いていないので直す必要はない）
2. Range Kth Smallest を並列二分探索で解いて時間内か：N = Q = 200000 で 0.24 秒（手元）。時間制限 5 秒に十分収まる
3. Union Sets の「最後まで同じ集合にならないとき」：-1（drken の記事）。指摘 3

## メインへの提案（ページの外）

- 台帳：code_thanks_festival_2017_h の `checked` に 2026-10-22 を入れる（問いと -1 の出力を drken の記事で確かめた）。agc002_d も同じ日付で、evidence に https://buyoh.hateblo.jp/entry/2017/12/08/181813 を足す執筆者の提案に賛成（並列二分探索の記事。noai の指定なしを確かめた）
- 台帳の agc002_d の summary「x と y の成分の頂点数の合計」は、同じ成分のときに二重に数えるとも読める。「x と y の成分を合わせた頂点数」のほうが誤解がない（本文の要約も同じ文なので、変えるなら両方）

## 総合の判定

小さな直しで可（直すべき 1、直すとよい 5）。コード片・図・計算量・問題の事実は正しく、直すべきは整体二分の再帰の形の説明 1 か所だけである。
