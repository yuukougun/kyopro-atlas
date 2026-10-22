# chromatic-number の報告（b4）

- 書いたファイル：docs/graph/chromatic-number.md、snippets/chromatic-number/chromatic.{cpp,yaml}、snippets/chromatic-number/mis.{cpp,yaml}（図はなし。visual が null のため）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `relations`（3 つの量の関係と難しさ）と `library`（計算量と自作するときの要点）を足した（既存の 3 つの anchor は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（2 本）、textlint エラー 0・警告 6（どれも数式を含む文の長さ）
- 使った出典：en.wikipedia.org「Graph coloring」「Independent set (graph theory)」、qiita.com の drken「AtCoder 版！蟻本 (中級編)」（例題 3-2-7 の節で「n <= 40 程度なら半分全列挙」と「O(1.381^n)」を確かめた）、github.com の library-checker-problems（task.md と info.toml で N ≤ 20・N ≤ 40 を確かめた。raw.githubusercontent.com から取得）。新しいドメインはない（raw.githubusercontent.com は github.com の生ファイルの配信先。必要なら付録 B に足す）

## 台帳への提案

- abc187_f｜pages｜chromatic-number に role: practice を追加｜補グラフの彩色数（クリークへの分割の最小）として包除原理の O(2^N N) でも解ける。根拠：台帳の evidence https://drken1215.hatenablog.com/entry/2021/01/02/224300 （問いの確認）。本文では subset-enumeration-dp#abc187_f への節リンクで触れるだけにした。足すなら本文に `## 練習問題 {#practice}` を立てる
- catalog の problems_note（「ABC で必須の問題が見つからない」）はそのまま当てはまる。例題は 0 問で書いた

## 用語集への提案

- 補グラフ｜complement-graph｜単純なグラフの、辺のある頂点の組と辺のない組を入れ替えたグラフである。独立集合は補グラフのクリークになる。（本文では短く定義し、リンクは張っていない。complement-graph-bfs のページにも使える）
- 彩色数｜chromatic-number｜隣り合う頂点が同じ色にならないように頂点を塗るときの、色の数の最小である。辺がなければ 1、二部グラフ（辺あり）なら 2 で、3 色で塗れるかの判定は NP 完全である。（用語集から本ページへリンクする形でもよい）

## 手引きへの提案

- §5 graph に「彩色数の包除原理を mod で計算するとき、正の値の余りが 0 になると塗れないと誤判定する。法を 2 つ使うか乱択する（持ち主は chromatic-number#chromatic-number）」を足すか検討（mod の値の 0 を存在の判定に使う落とし穴として、ほかのページ（行列式・LGV など）とも共通）

## 問題の補充の候補

- abc187_f（Close Group）：上記のとおり、練習としての追加を提案。裏付け https://drken1215.hatenablog.com/entry/2021/01/02/224300
- 一般グラフの最大独立集合（N ≤ 40）を ABC で問う問題は、Web 検索（「AtCoder 最大独立集合 N≤40 半分全列挙」）では見つからなかった。候補なし

## 未解決の点

- 分枝の計算量 1.47^N（T(N) ≤ T(N−1)+T(N−3)）と 1.38^N（T(N) ≤ T(N−1)+T(N−4)）は特性方程式の根を手元で計算した値（1.4656・1.3803）。後者は drken 氏の記事の O(1.381^n) と一致する。分枝の実装はコード片にしていない（半分全列挙だけ）
- 彩色数のコード片の「2 つの法のどちらかが 0 でなければ正」は確実だが、両方 0 になる誤判定の確率は評価していない（本文では「気になるなら法を乱択する」と書いた）
- 要点の「何ができるか」は summary より詳しく書いた（括弧で彩色数の定義を添え、計算量を足した）。summary と食い違いはない

## 検証の指摘への対応

- 1（直すべき）：#library の例の式を `1ULL << v` にそろえ、64 bit では `__builtin_ctzll`（または C++20 の `std::countr_zero`）を使うと書いた
- 2：隣の集合を $\mathrm{adj}[v]$ に改め（コードと #library に合わせた）、#independent-set の冒頭で $\mathrm{adj}[v]$・$\mathrm{adj}[X]$ を定義した
- 3：$\mathrm{ind}(S)^k$ が和集合が $S$ に収まる組の数であることと、$T = V \setminus S$ で包除して符号 $(-1)^{\lvert T \rvert}$ になることを 1 文足した
- 4：補グラフの隣接を「反転して $N$ bit に絞り、自分を除く」（`~adj[v] & full & ~(1ULL << v)`）とした
- 6：81 行を「$O(3^N)$ の別法」と「クリークへの分割は補グラフの彩色数（ABC187 F）」の 2 段落に分けた。textlint の警告（文の長さ）は数式を含む文で 6 件残る（エラー 0）
- 5（採らなかった）：確認問題を #quiz に移すかはバッチでそろえる方針をメインが決めるとの指摘なので、今は節の中に置いたままにした。方針が決まれば移す
- 7（採らなかった）：付録 B は共有ファイルなので書かない。提案：付録 B に raw.githubusercontent.com（github.com の生ファイルの配信先。check_noai.py で noai・noimageai の指定なし）を足す
