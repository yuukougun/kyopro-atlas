# offline-queries の報告（工程8b）

- 書いたファイル：docs/ds/offline-queries.md、snippets/offline-queries/distinct-count.{cpp,yaml}、snippets/offline-queries/threshold.{cpp,yaml}、docs/img/offline-queries/distinct-count-sweep.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 期待と違う 0。textlint エラー 0・警告 32（ほとんどが `$[l, r)$` の括弧の対応・数式を含む文の長さと読点の数の誤検出。「が」「に」の重なりの一部は残した）。fix_problems --check は ds/kth-element.md:202（abc281_e の label の末尾の空白）だけで終了コード 1。担当外なので直していない
- 動く図：作っていない（visual は static・priority 2）。区間の種類数の BIT の変化は静的な SVG にした（白背景・テキスト・viewBox あり。画像への描画は手元に道具がなく目視で確かめていない）

## 台帳への提案

- 問題 ID｜項目｜新しい値｜根拠
- abc174_f｜evidence｜kanpurin の記事は Mo's algorithm での解法なので、右端の順の BIT の根拠としては scrapbox の記事を先頭に置くとよい（台帳の URL は末尾の `(600)` が欠けている：https://scrapbox.io/procon-kirokuyou/ABC174_F_-_Range_Set_Query_(600)）｜scrapbox の記事で方針、kanpurin の記事で N, Q ≤ 5×10^5 を確かめた
- abc356_f｜approach｜「クエリを先読みして座標圧縮し、存在を BIT、成分の左端・右端を遅延セグ木で持つ」（今の値でも誤りではない。より具体にするなら）｜https://drken1215.hatenablog.com/entry/2024/06/08/024017

## 用語集への提案

- オフライン｜offline｜すべての入力を先に読んでから、好きな順に処理して答えてよい処理の仕方。クエリの先読みや座標圧縮はこれを前提にする。
- オンライン強制｜forced-online｜前のクエリの答えで次の入力が決まる（暗号化される）ため、クエリを入力の順に 1 つずつ答えなければならない形式。先読みが使えない。

本文は `../guide/glossary.md#offline` へリンクした（オンライン強制はページ内の節へのリンクで済ませた）。

## 手引きへの提案

- §9 の ACL の include 名：ACL のヘッダは `<atcoder/fenwicktree>`・`<atcoder/lazysegtree>` のように下線なしで、クラス名（`fenwick_tree`）と違う。手引きに一言あると、執筆者がコンパイルエラーで迷わない
- §4 の technique（水）の目安に「処理の流れ」の節があるが、型を束ねるページ（このページのように型ごとに節があるもの）では、各型の節に手順を持たせる形でよいことを明記するとよい

## 問題の補充の候補

- abc319 以降で、基本形の先読み（右端の順・しきい値の順）だけで解ける水の ABC を見つけられていない（level_evidence にもある既知の不足）。今回は探索に時間を使っていない
- abc106_d（ABC106 D. AtCoder Express 2、diff 1319）：区間とクエリを右端の順に並べ、BIT で左端を数える（2 時点の差・右端の順の入門）。台帳は確認済み（event-sort・sweep-line-2d の練習）。このページの練習に足す案｜https://drken1215.hatenablog.com/entry/2018/09/06/020200
- typical90_bp（典型90 068. Paired Information（★5））：クエリを先読みして Union-Find で関係の確定を判定する。台帳は確認済み（weighted-union-find の練習）。このページの練習に足す案｜https://enakai00.hatenablog.com/entry/2021/09/06/103720（このセッションでは記事を開いていない。research/05-ds §5 の記載による）
- abc287_g（ABC287 G. Balance Update Query、diff 2180）：得点を先読みして座標圧縮し、値を添字にした BIT で上位 X 枚の和を答える（compress の節の力試し）。台帳は確認済み（segment-tree-on-values の力試し）｜https://kmjp.hatenablog.jp/entry/2023/01/28/0900（このセッションでは開いていない）

## 未解決の点

- 新しく noai を確かめたドメイン：scrapbox.io（procon-kirokuyou の記事。指定なし）、pyteyon.hatenablog.com（指定なし）。付録 B への追加を提案する
- abc253_f の制約（x の上限）は記事で確かめられなかったので、本文では「加算が積み重なるので long long」とだけ書いた
- abc128_e は event-sort では力試し、このページでは練習（台帳どおり）。方針はイベントソートの力試しの方針へリンクした
- related の dynamic-segment-tree は segment-tree-on-values の節（黄）なので、本文ではページへのリンクだけにした（stub のため節へはリンクしていない）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 6 回
