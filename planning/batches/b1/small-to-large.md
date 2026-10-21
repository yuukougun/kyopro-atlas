# small-to-large（マージテク）執筆の報告

- 書いたファイル：docs/tree/small-to-large.md、snippets/small-to-large/{swap-sets,map-on-root,dsu-on-tree}.{cpp,yaml}、docs/img/small-to-large/doubling.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「小さい方の要素だけを書き換える（ずれ・クエリの集合）」（relabel-smaller、level はページと同じ水）を足した（abc314_f・abc394_g・abc350_g の共通の型を 1 か所で説明するため）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 3 件とも一致、textlint エラー 0（警告 6：数式を含む文の長さと、「が」の重複の誤検出。要点の囲みの長さは骨格の signs をそのまま使った部分）
- 図：静的な SVG 1 枚（catalog の visual は priority 2・static なので動く図は作らない）。描画の確認環境（rsvg-convert 等）がなく、座標の計算だけで確かめた。メインの目視を頼む
- 使った出典：drken（abc329_f・abc183_f・abc350_g・abc359_g）、kazun（abc314_f）、kmjp（abc394_g・abc454_g）、ikatakos（abc454_g の解法部分のみ）、ACL document_ja と dsu.hpp。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc394_g | summary（本体と small-to-large の alternatives の両方） | 建物が格子状に並び、隣り合う建物の間は両方の高さ以下の階で行き来できるとき、2 つの建物の指定された階どうしを移動する際の、上り下りする階数の最小値を各質問に答える | https://kmjp.hatenablog.jp/entry/2025/02/24/1000 |
| abc454_g | summary | 根付き木の各頂点の部分木について、色ごとの頂点数の最大値と、その最大値をとる色の数を求める | https://kmjp.hatenablog.jp/entry/2026/04/19/0900 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0418_abc454 （出力は全頂点分を XOR と積でまとめた値の mod。summary には書かなかった） |
| abc314_f | summary の確認 | 現行のままでよい。方針の「答えは mod」は解説の分数の扱いから判断した（下の未解決を参照） | https://kazun-kyopro.hatenablog.com/entry/ABC/314/F |

catalog の level_evidence にある abc454_g の役割は台帳どおり challenge で載せた（研究メモの §5.1 では dsu-on-tree の例題だったが、ページに併合された後は challenge）。

## 用語集への提案

- 本文は既存の `amortized-complexity`（ならし計算量）にだけリンクした。新しい語の提案はない
- 「重い子」「軽い辺」は hld#heavy-light で定義済みなので、用語集でなくそこへリンクした

## 手引きへの提案

- §8：SVG を手元で描画して確かめる道具（rsvg-convert か cairosvg）が環境にない。check に入れるか、執筆者に使える描画手段を示すと図の確認がしやすい
- §13 の確認問題の書き方は、答えを `??? success "答え"` で入れ子にするページ（union-find-applications）と直接書くページ（lazy-segment-tree）がある。どちらかにそろえる決まりがあるとよい（本ページは入れ子にした）

## 問題の補充の候補

確認済みの問題で数は足りている（例題 2・練習 4・力試し 1）。水のページの例題に abc319 以降が abc329_f の 1 問あるので条件も満たす。補充はなし。

## 未解決の点

- abc314_f の「答えは mod で求める」：問題文は開けないので、Kazun の解説が分数を mod で扱っていることからの判断。違えば方針の 1 文を消す
- abc394_g の答えの式（低い方の階が h 以下なら |Y−Z|、そうでなければ Y+Z−2h）は kmjp の解説の記述に合わせた。同じ建物の質問（最初からつながっている）の扱いは方針に書いていない
- abc454_g の方針の「親の番号が子より小さい」は ikatakos の制約の記述（1 ≤ p_i < i）による
- ページの relabel-smaller 節を足したので、メインの側で index/tree.md などの生成物を作り直す必要がある（gen_site.py は実行していない）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直した）：#why-log で 2 倍の議論は「重なりのない集合」の話だと明記し、折りたたみ「別の言い方」の min(a, b) の形を本文に出した。色の集合のように重なりがまとまる場合は「小さい方の箱のボールの個数以下」で同じ上限になる段落を足し、折りたたみは消した。abc329_f の方針の上限の根拠もその段落へ向けた
- 指摘 2（直した）：doubling.svg の各行のラベルを「x の側 n　相手 m（…）」の 1 行にまとめ、重なりをなくした（バーの左端 x=110 から始まり、右の「→ 移った後」x=450 には届かない）
- 指摘 3（メイン側）：本文のリンク `../guide/glossary.md#amortized-complexity` はそのまま残した。用語集への「ならし計算量 {#amortized-complexity}」の追加を提案する。足さないならメインがリンクを外す
- 指摘 4（直した）：abc394_g の方針に「同じ建物の質問は、併合を待たずに |Y − Z| と答える」を足した
- 指摘 5（直した）：最頻値の段落に、足すときと引くときの cnt・freq の動かし方を書いた
- 指摘 6（ぼかした）：ikatakos の記録をもう一度読もうとしたが 503 で読めなかった。「N が数百万まであり」とぼかした。値を確かめられたら戻してよい
- 指摘 7（消した）：abc314_f の「答えは mod で求める」を消した。方針はそのまま成り立つ
- 指摘 8（直した）：#subtree-merge の第 2 段落に「項目数の小さい方は、どちらの map の項目数以下でもあるので、頂点数の小さい方の部分木の頂点数以下でもある」の 1 段を足した
- 台帳への提案（検証役から）：abc329_f・abc183_f・abc350_g・abc394_g・abc359_g に `checked: 2026-10-21`。abc314_f は「mod」の文を消したので checked を入れてよい。abc454_g は N の上限を本文でぼかしたので checked を入れてよいが、制約の値は未確認のまま
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 3 件とも一致、textlint エラー 0（警告 6）
