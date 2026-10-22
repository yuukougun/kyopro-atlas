# segment-tree-beats の報告と提案（b4）

- 書いたファイル：docs/ds/segment-tree-beats.md、snippets/segment-tree-beats/beats.{cpp,yaml}、docs/img/segment-tree-beats/three-cases.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 定型でない見出し：`## 学ぶための資料 {#resources}`（hld・cdq-divide-and-conquer・dynamic-dp と同じ。sections には載せていない）。node-data の中に小見出し `### 自作するときの要点` を置いた（anchor なし）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 8：要点の囲み・数式を含む文の長さ、半開区間の `[` の対、数式の中の読点 `$4, 9, 2, 9, 6$`、図の代替テキストの長さ。誤検出として残した）
- コード片：区間 chmin・chmax・加算・和の完全な実装。起動時に乱数の小さな列で愚直な計算と 300×200 回突き合わせる assert を入れた。手元で N = Q = 2×10^5 の乱数入力が 0.8 秒ほど（Library Checker の制限は 10 秒）
- 図：three-cases.svg（幅 400）を render_svg.py で 360px・720px にして目で確かめた。catalog の visual は null なので動く図は作っていない

## 使った出典

- hackmd.io「Segment Tree Beats」（Codeforces の原典ブログの和訳メモ。計算量・ノードの値・3 つの場合・ポテンシャル）
- scrapbox.io/37zigen-43465887「Segment Tree Beats の計算量解析」（境界のノードと余分なノード、chmin と和の評価）。check_noai で noai なしを確認（新しいプロジェクト）
- rsm9.hatenablog.com（ひとなので氏、ACL の all_apply に 1 行足す方法）。check_noai で noai なしを確認（新しいブログ）
- scrapbox.io/Atcoder-myReflection「SegmentTreebeats!」は check_noai で noai なしを確認したが、本文には使っていない（参考にも入れていない）
- oi-wiki.org「吉司机线段树」（2016 年の論文が原典であること、2 つの計算量。文章と図は使っていない）
- github.com/yosupo06/library-checker-problems の task.md・info.toml（Range Chmin Chmax Add Range Sum の操作と制約。N, Q ≤ 2×10^5、|a_i| ≤ 10^12）
- kmjp.hatenablog.jp（例題の問いと map の別解）、nyaannyaan.github.io（例題が Segment Tree Beats で解けること。キーワードだけ）

## 台帳への提案

- abc256_h｜evidence｜変更なし。ただし nyaannyaan.github.io の解説一覧は「Segment Tree Beats!」の一言だけで、beats 型の方針（最大値と最小値が等しければ代入に直す）の裏付けとしては弱い。beats 型の解法を書いた第三者の解説は見つからなかった。本文の方針は、ページの shrinking-values の節で自分で示した評価に基づく

## 用語集への提案

- なし（ならし計算量 amortized-complexity・ポテンシャル potential は既存の語にリンクした）

## 手引きへの提案

- 付録 B に rsm9.hatenablog.com、scrapbox.io のプロジェクト 37zigen-43465887・Atcoder-myReflection を足す（2026-10-22 に check_noai で確認）
- `## 学ぶための資料 {#resources}` を §13-1 の定型の見出しに加える（cdq-divide-and-conquer の提案と同じ）

## 問題の補充の候補

- 見つからなかった。Web 検索で、ABC・ARC の問題で Segment Tree Beats（区間 chmin・chmax と和）が想定解か主な別解になる第三者の解説は見当たらなかった
- abc430_g（台帳にあり、interval-set の練習）は、検索結果の要約に「Segment Tree Beats で解ける」とする記述があったが、それは atcoder.jp の解説の要約で、第三者の解説（kmjp）の方針は値ごとの set と遅延セグメント木である。裏付けが取れないので、本ページへの追加は提案しない
- 練習の代わりに、Library Checker の Range Chmin Chmax Add Range Sum（verify）を `## 練習問題` の小見出し「Library Checker」に置いた（§15-5）

## 未解決の点

- shrinking-values の割り算の評価 $O((N + Q \log N) \log A)$ と、mod の評価 $O(N \log N \log A)$（区間代入なし）は、資料からの引用ではなく自分で組んだポテンシャルの議論である。検証役に筋を確かめてほしい
- 区間 chmin と chmax を両方持ち加算がない場合の計算量（ならし $O((N + Q) \log N)$ になるはず）は資料で確かめきれなかったので、本文では「chmin と和だけ」と「加算が混ざる」の 2 つだけを書いた
- 平方根の打ち切り（差が変わらなければ区間加算に直す）と $O(\log \log A)$ は一般的な事実として書いたが、ページの出典には個別の資料を挙げていない
- 例題 abc256_h の制約（x の範囲・値が非負か）は atcoder.jp を開けないので確かめていない。本文は「x = 1 なら飛ばす」「x ≥ 2 なら」と条件付きで書いた
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 約 12 回（WebFetch 8・検索 4）

## 検証の指摘への対応

- 指摘 1〜10 はすべて直した（採らなかったものはない）。指摘 1 は本文の 3. と図の下の帯の小さい文字（「9 が 6 以下に（x < 6 なら 6 も）」）・代替テキストを直した。指摘 2 は一文を直し、参考に library-checker-problems の issue #1369 を足した。指摘 10 は平方根と mod で段落を分け、長い文を割った
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 7）

## 手引きへの提案（追加）

- 付録 B の github.com の扱いに、library-checker-problems の issue・PR を出典にしてよいことを明記するとよい（今回 issue #1369 を参考に入れた）
