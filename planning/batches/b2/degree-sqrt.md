# degree-sqrt の報告（b2）

- 書いたファイル：docs/graph/degree-sqrt.md、snippets/degree-sqrt/{paint-query,triangles,four-cycle}.{cpp,yaml}、docs/img/degree-sqrt/push-pull.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の push-pull の title を「重い頂点は受け取る側、軽い頂点は配る側」から「配るか取りに行くかを次数で決める」に変えた（anchor はそのまま）。例題の公式コード（083-02a）は「軽い頂点が配り、重い頂点は自分にだけ記録して取りに来てもらう」形で、公式の解説の画像は逆向き（重い頂点が隣から受け取り、軽い頂点が取りに行く）なので、旧題はどちらとも食い違うため
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 本とも一致、textlint エラー 0・警告 7（要点の囲みの数式を含む長い文、助詞の重複の誤検出に近いもの）。SVG は render_svg で 720px・360px を目で確かめた（360px では文字が小さいが読める）
- 使った出典：GitHub の E869120/kyopro_educational_90（sol/083-02a.cpp、editorial/083-01〜03.jpg）、oraclesqlpuzzle の ABC260-F、GitHub の library-checker-problems（enumerate_triangles・counting_c4 の task.md と info.toml）。新しく確かめたドメインはなし（scrapbox.io/Example0911 は check_noai で指定なしだったが、ページは 404）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_ce | evidence | `https://scrapbox.io/Example0911/…` を外し、`https://github.com/E869120/kyopro_educational_90/blob/main/editorial/083-03.jpg` を足す | scrapbox のページが HTTP 404（2026-10-21） |
| abc260_f | evidence | `https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc260-f.html` を足す | ikatakos.com が HTTP 503 で読めなかった。oraclesqlpuzzle で T ≤ 3000 と組の記録による打ち切りを確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 向き付け | orientation | 無向グラフの各辺に向きを 1 つ決めて有向グラフにすること。頂点に全順序を決めて小さい方から大きい方へ向けると、閉路のない有向グラフになる。三角形の列挙では次数の小さい方から向ける |
| 重い頂点・軽い頂点 | heavy-vertex | 次数がしきい値 $B$ 以上の頂点を重い頂点、未満を軽い頂点と呼ぶ。重い頂点は $2M/B$ 個以下しかない（次数による平方分割） |

本文では用語集へのリンクを張っていない（check_pages が未定義の anchor をエラーにするため）。足したら三角形の節の「向き付ける」にリンクしてよい。

## 手引きへの提案

- §13-5 は「用語集へのリンクはまだなくても書いてよい」とするが、check_pages は用語集にない anchor をエラーにする。どちらに合わせるかを決めてほしい（今回はリンクを外した）

## 問題の補充の候補

- 確かめきれた候補はない。ap.py の検索（Triangle・4-cycle・Neighbor・Adjacent など）と Web 検索では、次数による平方分割を使う ABC（abc319 以降）の問題に、第三者の解説で裏付けられるものを見つけられなかった
- abc258_g（G. Triangle、diff 1944、台帳では bitset-speedup の例題）は三角形を数える問題だが、N ≤ 3000 の密なグラフで三角形が 10^9 個を超えうるため、この手法では間に合わない。使い分けの節で bitset のページへ回す形で触れた（問題 ID は出していない）
- 練習は 1 問のままで、Library Checker（enumerate_triangles・counting_c4）は verify にある

## 未解決の点

- 典型90 083 の制約は公式の解説の画像（P3 の「N, M, Q ≤ 200000」）で確かめた。問題文の画像は開いていない
- ABC260 F の S 側の頂点数と M の上限は確かめていない。本文と方針では T ≤ 3000 だけを使い、S の上限には触れていない
- 動く図は作っていない（visual は static・priority 2 で、静的な SVG 1 枚にした）

## 使用量の目安

- 道具の呼び出し約 40 回、Web 取得 6 回（検索 4 回を含まない）

## 検証の指摘への対応

- 指摘 1〜9 はすべて直した（1：和・個数は引いて取り除けるので同じ形、最大値・最小値は単調なときだけで一般は多重集合、条件を型ごとに分けた。2：見出しを「表で持つと重い」にし約 500 MB・1024 MiB でも余裕なしと書いた。3：最大 6 回。4：重くなった頂点の集計を作り直し隣の hn に加える、合計 O(M)。5：表に「自分と」。6：要点を「数え上げ」に。7：four-cycle.cpp の添字を size_t に。8：自己ループの影響を 1 文足した。9：「多重辺を含みうる（自己ループはない）」）
- 採らなかったものはない
- 共有ファイルへの提案は、検証の「台帳への提案」（typical90_ce の checked・evidence、abc260_f の evidence）に賛成する
