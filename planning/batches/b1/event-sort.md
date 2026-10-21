# event-sort の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/event-sort.md、snippets/event-sort/interval-query.{cpp,yaml}、snippets/event-sort/red-blue-pairs.{cpp,yaml}、docs/img/event-sort/timeline.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 33。「x も y も」の助詞の重複、数式 `[l, r)` の括弧の対応、数式を含む文の長さの誤検出）
- 図：catalog の visual（static、priority 2）を静的な SVG にした（区間 3 本・クエリ 3 つの時間軸と、座標ごとの処理と集合の中身の表）。動く図は作っていない
- 構成：基礎の帯ではなく水のページなので、sections の 4 節を中心に、落とし穴・使い分け・例題・練習・力試し・参考を置いた。確認問題は make-events の節の中に 1 つ（同じ座標の開始と終了の順）

## 使った出典

- drken（hatenablog）abc309_c・arc092_a・abc106_d・abc245_e・abc128_e、oraclesqlpuzzle abc188_d、comet725（qiita）abc478_d：台帳の evidence。例題・練習の問いと方針を確かめた
- Konini64（qiita）https://qiita.com/Konini64/items/6fefc9fe50142dc107a8 ：abc478_d の問い（N 個の空の集合、区間に値を入れる、各集合の要素数）の確認。qiita.com は付録 B にある
- 新しく noai を確かめたドメイン：なし

## 台帳への提案

- abc478_d｜summary｜N 個の空の集合に、区間 [L, R] の番号の集合すべてへ値 X を入れる操作を Q 回行った後、各集合の要素数を求める。｜https://qiita.com/comet725/items/53e6c3b9804e2f235a01 ・https://qiita.com/Konini64/items/6fefc9fe50142dc107a8 （どちらも問題文の転記はなく、コードと説明から問いを確かめた。2 本で一致）
- abc478_d｜approach｜「操作を L での追加と R + 1 での削除のイベントにし、値ごとの個数が 0 と 1 の間で変わるときに種類数を増減する」に具体化
- abc478_d｜evidence｜https://qiita.com/Konini64/items/6fefc9fe50142dc107a8 を足す。b8d667d4…・15e9951d…・4e3a310e… は research 00 の表で別の問題（abc455_d・abc463_e・abc458_d）の記事なので、abc478_d の evidence から外す
- abc245_e｜approach（任意）｜台帳は「大きい順に並べ、箱を multiset で管理して最小のものを使う」。evidence の drken の記事は「箱を縦の小さい順に、チョコの横を multiset に入れて upper_bound の 1 つ前（横が箱以下で最大）を使う」。本文の練習の方針は記事の向きで書いた。どちらでも解けるが、evidence に合わせるなら approach を直す
- arc092_a｜status・checked｜本文に使ったので checked に日付を入れてよい（status は確認済み）

## 用語集への提案

- オフライン｜offline｜クエリを先に全部読み、答えやすい順に並べ替えて処理してよいこと。前の答えで次のクエリが決まる（オンラインでの回答が要る）問題では使えない。本文から `../guide/glossary.md#offline` でリンクした

## 手引きへの提案

- §2.5・§10：台帳の summary が「（執筆時に確かめる）」の問題は、行を `- <ID>：自分の要約` で書けば fix_problems が要約を残したまま label などを埋める、と一言あると迷わない（今回そうした）

## 問題の補充の候補

catalog の数（例題 2・練習 4・力試し 1）で足りており、abc319 以降の問題も 1 問（abc478_d）ある。追加は必須ではない。

- abc467_e（recent-abc.yaml にあり、frequency_evidence に挙がっている）：台帳にない。ikatakos 氏の記録によれば主役は変数の固定と偶奇で、折り返し点をソートして増分を追う部分がイベントソートに当たる。このページの練習にするより fix-variable の側で扱うのがよい。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0718_abc467 （本文には使っていない。中身は読んでいない）

## 未解決の点

- abc309_c の制約（a_i・b_i の上限）は evidence に見当たらず確かめていない。本文では「int に収まるか制約で確かめ、迷ったら long long」とだけ書いた
- abc128_e で同じ地点 X の通行止めが時間の重なる形で複数あるかは確かめていない。本文は multiset で書いた（evidence の記事も multiset）
- frequency_evidence の abc467_e は台帳になく、このページとの関係も薄い（上記）。frequency の値は変えていない
- level_evidence では abc128_e（1840）が青だが、catalog どおり力試しに置いた
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 11 回（WebFetch 9・検索 1・curl で題名の取得 1 回分）
