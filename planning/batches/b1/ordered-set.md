# ordered-set の報告（工程8b・b1）

- 書いたファイル：docs/ds/ordered-set.md、snippets/ordered-set/{neighbors,pareto,adjacent-pairs}.{cpp,yaml}、docs/img/ordered-set/neighbors.svg
- front matter で変えたもの：complexity・stage（draft）・updated（節の追加・変更なし）
- 検査の結果：check_pages --page ordered-set（エラー 0・警告 0）、fix_problems --check --page ordered-set（0 行）、check_snippets（3 本とも一致）、textlint（エラー 0・警告 0）
  - 全体の `fix_problems.py --check` は dp/tree-dp.md の 10 行（別の執筆者の作業中の行）で終了コード 1。このページの行は 0
- 使った出典：drken（abc330_e・abc370_d・abc385_d・abc245_e）、kanpurin（abc217_d）、kyo-pro（abc241_d）、betrue12（abc140_e）、cpprefjp（set::lower_bound）。新しく noai を確かめたドメイン：inamori.hateblo.jp（指定なし。候補の確認に読んだだけで本文には使っていない）
- 図：visual は priority 2・static なので、静的な SVG（数直線と lower_bound・prev）を 1 枚作った。動く図は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc241_d | summary（全 alternatives も） | 数の追加と「x 以下で大きい方から K 番目」「x 以上で小さい方から K 番目」の質問を処理する（K ≤ 5）。 | prh が「k 番目」を「K 番目」に直す（textlint のエラー）。本文の行は手で K に直したので、台帳を直さないと fix_problems で戻ると textlint が落ちる |
| abc245_e | alternatives（ordered-set）の approach | 箱を縦の小さい順に見て、縦が収まるチョコの横幅を multiset に入れ、箱の横以下で最大のものを使う | drken の解説は「箱を縦の小さい順・チョコの横幅を multiset・D 以下で最大」の向き。catalog の「縦の大きい順・箱の横幅を multiset・最小のもの」も対称で正しいが、出典と合わせるなら前者（https://drken1215.hatenablog.com/entry/2022/03/30/003800） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 支配（点の支配） | dominance | 2 つの組 (a, b) と (a', b') で a' ≥ a かつ b' ≥ b のとき、(a, b) は (a', b') に支配されるという。支配される組は最大化の答えにならないので捨ててよい |
| パレート境界 | pareto-front | どの組にも支配されない組の集まり。一方の成分の昇順に並べると、もう一方は降順になる |

（本文ではリンクしていない。用語集に入れるなら、本文の最初の「支配される」「パレート境界」にリンクを足す）

## 手引きへの提案

- 台帳の summary が prh に引っかかる（k 番目など）場合、§13.7 は「台帳を直す提案」だが、textlint のエラー 0 と両立しない。本文の行を手で直してよい（fix_problems --check は summary を見ていない）と明記するとよい
- 全体の `fix_problems.py --check` は並列の執筆中にほかのページの行で落ちる。執筆者の検査は `--check --page <id>` にすると誤報がない

## 問題の補充の候補

| 問題 ID | 何を問うか | 使う型 | 裏付け |
| --- | --- | --- | --- |
| abc302_e（E. Isolation、diff 988） | 辺の追加と、ある頂点の全辺の削除のたびに孤立点の数を答える | 隣接頂点を set で持ち、変わった分だけ数え直す（前後の要素ではなく set の削除の練習） | https://drken1215.hatenablog.com/entry/2023/06/01/020700（research の値。今回は読んでいない） |
| abc444_e（E. Sparse Range、diff 1107） | どの 2 要素も差が D 以上である連続部分列の個数 | 尺取り法で窓の値を順序付き集合に持ち、新しい値の前後が D 未満かを調べる | https://inamori.hateblo.jp/entry/2026/02/09/194520（著者はセグ木で代用。set の解は別の第三者の解説で確かめる必要あり。確度 medium） |
| abc260_d（D. Draw Your Cards、diff 1074） | カードを場の山に重ね、K 枚で消える操作で各カードが消える時刻 | 山の一番上の値を set で持ち upper_bound で置き先を探す | research 付録 B（低確度）。第三者の解説で未確認 |

- パレート境界の節（水）に対応する確認済みの問題がない。ABC で「支配される点を消す map」を使う問題を探す必要がある

## 未解決の点

- abc217_d で、長さのクエリの x がちょうど切れ目に一致することがあるかを第三者の解説で確かめられなかった（kanpurin の記事の制約の記載にはない）。本文は lower_bound とその 1 つ前の差とだけ書き、保証には触れていない
- sections の「落とし穴（…）」は §13.1 では定型の節（sections に載せない）だが、骨格で sections にあるので残し、見出しを title と同じにした（binary-search と同じ扱い）
- frequency_evidence の abc466_f・abc475_e はこのページの問題にしていない（abc466_f は台帳で reverse-thinking の力試し、abc475_e は台帳を見ていない）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：sections から pitfalls の行を消し、見出しを `## 落とし穴 {#pitfalls}` にした（style-guide §13.1 どおり。anchor は同じ）。binary-search ほか骨格で pitfalls を sections に持つページが多い（bit-operations・bit-full-search・kth-value・prefix-sum・digit-dp など）ので、メインが一括で揃えるかを判断するとよい
- 指摘 2（直すべき）：#rows-and-columns の「探す」に「$(r, c)$ に壁がないとき」の前提を足し、自身が壁なら `*it == c` を先に調べる・自身を含めないなら `upper_bound(c)` と添えた
- 指摘 3：線分の段落で記号を $(x, y)$・$x_1$・$x_2$ に改め、`row[y]`・`col[x]` の意味を 1 文で足した。擬似コードも `x1`・`x2` に直した
- 指摘 4：支配の定義を「別の点 $q$」とし、同じ点が 2 つあれば 1 つだけ残すと添えた。用語集への提案の定義も、同じ点の扱い（別の組で、同じ組は 1 つだけ残す）を足して採ってほしい
- 指摘 5：#near-kth の計算量を $O(\log N + K)$（続けて $K$ 歩動かす手間は合計 $O(K + \log N)$）に直した
- 指摘 6：`contains`（C++20）とし、cpp-container-idioms#contains へリンクした
- 指摘 7（このページの外）：提案として残す。docs/cpp/cpp-container-idioms.md 166 行の「set で x 未満の個数が要るとき」のリンク先を ordered-set から kth-element（BIT）か pb-ds の節に変える
- 採らなかったもの：なし
