# offline-queries の検証（工程8b・b1）

- 対象：docs/ds/offline-queries.md、snippets/offline-queries/{distinct-count,threshold}.{cpp,yaml}、docs/img/offline-queries/distinct-count-sweep.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page offline-queries`（エラー 0・警告 0）、`python3 tools/check_snippets.py snippets/offline-queries`（2 片・コンパイル 2 回・期待と違う 0。g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）、`npx textlint docs/ds/offline-queries.md`（0 errors・32 warnings。執筆者の報告どおり、`[l, r)` の括弧・助詞の重なり・長文の誤検出が中心）
- front matter：git diff で、執筆者が変えたのは complexity・stage だけ。complexity と要点の計算量、本文の計算量（区間の種類数 $O(Q \log Q + (N + Q) \log N)$、しきい値 $O((M + Q) \log (M + Q))$）は一致する。別名の行に aliases がすべてある
- コード片：2 片を `-fsanitize=address,undefined -O1 -g` で作り直し、作業用の場所の fuzz.py で乱数の入力 500 件（distinct-count は $N, Q \le 8$、値は小さい値と $\pm 10^{18}$ の混在で `set` による素朴な方法と比較、threshold は自己ループ・多重辺・同じ重み・重み 0 を含み、コード内の assert（クエリごとに Union-Find を作り直す方法）で比較）を流し、すべて一致、サニタイザの報告なし。C5 の書き方（bits・using namespace std・マクロなし・`'\n'`）に合い、取り込みは core の範囲だけ。cases に 1 要素・$10^9$・全部同じ値・交互の値・辺 0 本・同じ重みの境界がある。本文の記号（`ord`・`ans[k]`・`last`・`c[i]`・$-1$ の番兵・`<=`）とコードがそろう
- 具体例：図と本文の $A = (1, 2, 1, 3, 2)$ を手で追った。$r = 4$ の 0/1 列は $(0, 1, 1, 1)$ で $[1, 4)$ の和 3（値 2・1・3）、$r = 5$ は $(0, 0, 1, 1, 1)$ で $[1, 5)$ の和 3。distinct-count の cases 1 つ目（`1 5`→3、`2 4`→3、`3 3`→1、`1 3`→2）も手計算と一致
- 主張：最後の出現位置の言い換え（1 対 1 対応）、$\mathrm{prev}_i < l$ の言い換え、「以下は辺を先・未満はクエリを先、比較の `<=`・`<` だけで決まる」、上書きと加算の差の式、マージソート木で種類数にオンラインで答えられること、確認問題 1〜3 の答え（確認問題 1 の「左端の順」は大きい順・小さい順のどちらでも一方向の掃引になり、正しい）を確かめた
- ACL：`~/lib/ac-library-master/document_ja/fenwicktree.md` と照らした。`fenwick_tree<T> fw(n)`（全要素 0）、`add(p, x)`、`sum(l, r)` が半開区間、どちらも $O(\log n)$、`T` は `int / uint / ll / ull / modint`。囲みの記述と一致
- 問題：6 問とも `python3 tools/ap.py show` で題名・diff が本文と一致（abc174_f 1495、abc253_f 1756、abc235_e 1304、abc040_d 1656（参考値）、abc128_e 1840、abc356_f 2152）。役割は台帳どおり（例題 2・練習 3・力試し 1）
- 参考の URL：開いて内容を確かめたもの
    - procon-kirokuyou（scrapbox）ABC174 F：右端の順のソート、各色の最も右の位置に 1 を立てる BIT、$O((N + Q) \log N)$。本文と一致。`tools/check_noai.py` で指定なし
    - drken ABC235 E：元の辺とクエリの辺を合わせて重みの順にクラスカル法、クエリの辺は併合せず両端が別の成分なら Yes。制約は元の辺の重みが互いに異なり、クエリの重みは元の辺の重みと異なる（指摘 4）
    - pyteyon ABC040 D：年が $w$ より大きい（等号なし）道路だけを使う、道路とクエリを年の降順に処理。本文と一致。`tools/check_noai.py` で指定なし
    - recuraki ABC253 F：先読みで各取得の直前の上書き（時刻と値）を求め、上書きの時刻で BIT の値を記録して差を取る。本文と一致。制約の記載はない（執筆者の未解決の点のとおり。本文は long long の理由を「加算が積み重なる」とだけ書いており、誤りではない）
    - drken ABC356 F：先読みと座標圧縮、存在を BIT、成分の左端・右端を遅延セグメント木（区間の書き換え）、$O(Q \log Q)$。本文の力試しの方針と一致
    - kanpurin・drken ABC128 E・ACL の Fenwick Tree は今回は内容の一部だけ確かめた（kanpurin は `check_noai.py` で指定なし）
- リンク：fenwick-tree・sorting-techniques・coordinate-compression#with-ds・sweep-line-2d・parallel-binary-search・union-find-connectivity・reverse-thinking・segment-tree-on-values・persistent-data-structures・merge-sort-tree・mo-algorithm・event-sort はすべて存在。用語集の `#offline` はまだない（執筆者が提案済み。メインがバッチの終わりに足す）
- 図：Windows の Chrome（headless=new、2 倍密度）で distinct-count-sweep.svg を等倍 620×342 と、幅 390px の画面（暗い背景）に幅 358px で置いて画像にし、目で確かめた（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-offline-queries/full.png・narrow.png）。背景は白、`viewBox` あり、文字はテキストのまま、`font-family="sans-serif"`。赤い破線の枠は色だけでなく線の種類でも区別され、枠の位置（$[1, 4)$・$[1, 5)$）も正しい。代替テキストと前後の段落だけで要点が分かる。catalog の visual（static・priority 2）を満たす

## 指摘

### 1｜直すとよい｜clarity（U3）・fact（F1）｜#idea、2 段落目の最後「状態を進める更新は全体で $N$ 回（辺なら $M$ 回）しか起きないので、合計がクエリ数に比例しなくなる」

- **問題**：全体の手間は更新 $N$ 回とクエリ $Q$ 回の和で、クエリ数には比例する。言いたいのは「更新の回数がクエリごとに $N$ 回ずつ積み上がらない（$NQ$ にならない）」ことで、文のままでは計算量の主張として誤って読める
- **根拠**：本文の計算量 $O(Q \log Q + (N + Q) \log N)$ 自体が $Q$ を含む
- **直し方**：「状態を進める更新は、クエリがいくつあっても全体で $N$ 回（辺なら $M$ 回）なので、手間は $NQ$ ではなく $N + Q$ に比例する（データ構造の log を除く）」

### 2｜直すとよい｜fact（F2）｜#compress、2 段落目「集めなかった値を `lower_bound` で引くと、その値以上の最小の値の番号が返る。『$x$ 以下の個数』を求めたつもりが、$x$ より大きい値まで数えることになる」

- **問題**：誤りになるのは、返った番号 $i$ を $x$ の番号とみなして接頭辞 $[0, i]$（`sum(0, i + 1)`）を取ったときだけである。`upper_bound` で番号を取り `sum(0, i)` とすれば、集めていない値でも「$x$ 以下の個数」は正しい。文のままでは `lower_bound` を使えば必ず数えすぎると読める
- **根拠**：圧縮後の値 $(10, 30)$ に $x = 20$（集めていない）で、`lower_bound` は 1（30 の番号）。`sum(0, 2)` は 30 まで数えて誤り、`upper_bound` の 1 で `sum(0, 1)` は正しい
- **直し方**：「返った番号を $x$ の番号とみなして、その位置までの和を取ると、$x$ より大きい値まで数えることになる」と、誤る使い方を明示する。結論（クエリの値もすべて集める）はそのままでよい

### 3｜直すとよい｜code（C3）・clarity（U8）｜#quiz の確認問題 3「辺を足す条件を `edges[e].w <= w` から `edges[e].w < w` に変えるだけである」

- **問題**：取り込んだコードの条件は `edges[e].w <= qs[k].w` で、`w` という変数はない。本文のコードと照らした読者が一瞬迷う
- **根拠**：snippets/offline-queries/threshold.cpp の core（`while (e < (int)edges.size() && edges[e].w <= qs[k].w)`）
- **直し方**：「`edges[e].w <= qs[k].w` を `edges[e].w < qs[k].w` に変えるだけである」

### 4｜直すとよい｜fact（F5）｜#practice の練習の方針、ABC235 E「辺の重みはすべて異なるので、同じ重みの順序に迷わない」

- **問題**：保証されているのは「元の辺の重みが互いに異なる」ことと「クエリの辺の重みが元の辺の重みと異なる」ことで、クエリどうしの重みが異なるとは書かれていない（クエリの辺は併合しないので、答えには効かない）。「すべて」はやや言い過ぎ
- **根拠**：台帳の evidence の drken「AtCoder ABC 235 E - MST + 1」の制約
- **直し方**：「元の辺の重みは互いに異なり、クエリの辺の重みも元の辺と重ならないので、同じ重みの順序に迷わない」

### 5｜直すとよい｜clarity（U4）｜#abc253_f の解法の詳細、1 つ目の項目「上書きがまだなければ $x = 0$、$t$ は『最初』とする」

- **問題**：$t$ が「最初」のとき、記録する加算の合計が何か（0）と、ぶら下げる先がないことが書かれていない。2 つ目・4 つ目の項目の手順をそのまま当てはめようとすると止まる
- **直し方**：「上書きがまだなければ $x = 0$ とし、記録する合計も 0 として扱う（小さなクエリはぶら下げない）」

### 6｜直すとよい｜figure（G3）｜distinct-count-sweep.svg、右側の注記「値 1 の 1 を位置 0 から 2 へ移す」と幅 390px の表示

- **問題**：(a) 注記は x=404 から始まり、Chrome の既定の sans-serif で右端が約 613px と、viewBox の幅 620 にほぼ接する。字幅の広いフォントの環境では切れるおそれがある。(b) 幅 358px に縮むと本文の 15px の文字が約 8.7px、下の説明（13px）が約 7.5px になり、読めるが小さい
- **根拠**：full.png・narrow.png（上記の作業用の場所）
- **直し方**：注記を「値 1 の 1 を 0 → 2 へ」と短くするか viewBox の幅を 660 程度に広げる。表の左のラベル列（x=0〜150）の余白を詰めて全体を横に縮めると、狭い画面での文字も大きくなる

## 台帳・メインへの補足（ページの指摘ではない）

- 用語集の `#offline` はまだない。執筆者の提案（オフライン・オンライン強制）をメインが反映する
- abc174_f の evidence の scrapbox の URL は末尾の `(600)` が欠けている（本文の参考の URL が正しい）。執筆者の提案どおり直すとよい
- `checked` の日付の提案（2026-10-21）：abc174_f（scrapbox の記事で方針）、abc235_e（drken の記事で方針と制約）、abc253_f（recuraki の記事で方針）、abc356_f（drken の記事で方針）
- 付録 B への追加の候補：scrapbox.io（procon-kirokuyou）・pyteyon.hatenablog.com（どちらも `tools/check_noai.py` で指定なし）

## 総合の判定

小さな直しで可（直すべき 0 件、直すとよい 6 件）。事実・計算量・コード・図に誤りは見つからなかった。指摘はどれも言い回しの精度と読みやすさの改善である。
