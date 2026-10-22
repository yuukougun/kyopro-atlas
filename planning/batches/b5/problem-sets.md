# b5 problem-sets の報告と提案

- 書いたファイル：docs/guide/problem-sets.md（snippets・図はなし）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）。complexity は guide なので null のまま。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、textlint（エラー 0・警告 0）
- 生成ブロック recent-abc・problem-sets は中身を変えず、それぞれ `## 最近の ABC → ページ {#recent-abc}`・`## 問題集の問題 → ページ {#sets-to-pages}` の見出しと前置きの下に移した
- 使った出典：E869120 の告知記事（Qiita。★と difficulty の対応・期間・進め方）、kyopro_educational_90・kyopro-tessoku（GitHub）、drken の EDPC の記事（Qiita）、AtCoder Problems の FAQ とガイド（recommend.md・virtual_contest.md、GitHub）、NoviSteps の About、AtCoder Clans、library-checker-problems の categories.toml。数（問題数・開催日・ADT の位置ごとの difficulty の中央値・AWC の時間・PAST の回数・ARC の区分）は `.cache/atcoder-problems/` の JSON から集計した
- 新しく noai を確かめたドメイン（check_noai で指定なし）：atcoder-novisteps.vercel.app、kenkoooo.com、kato-hiro.github.io、judge.yosupo.jp（付録 B にすでにある）

## 台帳への提案

- 問題は載せていない（catalog の problems が空、guide のため）。台帳への変更の提案はない
- 表示名：問題集の問題の表の label が `PRACTICE2 A. Disjoint Set Union` のように contest id の大文字になる。interfaces §3 の表示名に practice2 → `ACL Practice`（ほかに aalc001 → `AAL001`、ndpc → `NDPC`、fps-24 → `FPS24`、game-24 → `ゲーム24` など）を足すかを決めてほしい（§15-10 で表示名は変えない決まりなので、変えるなら全ページ一括）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| difficulty | difficulty | AtCoder Problems が問題ごとに推定する難しさ。その問題を 50% の確率で解けるレートを表し、参加者のレートとコンテストの結果から推定する。この教材の帯（基礎・水・青・黄・発展）は difficulty の範囲で決める。 |
| バーチャル参加 | virtual-contest | 終わったコンテストの問題を、時間を計って本番と同じ形で解くこと。AtCoder Problems のバーチャルコンテストでは、問題と制限時間を自分で選べる。 |

## 手引きへの提案

- 横断ページの表で、生成ブロックの見出し（`### … {#problem-sets-<cid>}`）へ同じページの中からリンクした。本文で使っていない問題集には見出しができないので、リンクは使っている問題集（typical90・dp・tdpc・practice2・tessoku-book・math-and-algorithm）だけにした。ほかのページから `problem-sets#problem-sets-<cid>` へリンクするなら、生成のたびに anchor が消えうることに注意（gen_site.py で、使っていない問題集にも見出しと「まだない」の 1 行を出すと安定する）
- gen_site.py の problem-sets ブロックは、ABC・ARC・AGC 以外の本番のコンテスト（KEYENCE2019・CODE-FESTIVAL-2017-QUALB など）も「問題集」として並べる。本文ではその旨を断ったが、見出し「そのほかの本番のコンテスト」でまとめる（`####` に下げる）と読みやすい

## 問題の補充の候補

guide のページなので問題は載せない。問題集の中で本文にまだ使っていないもの（NDPC・AAL Contest 001・組合せゲーム 24 題・FPS 24 題）は、各分野のページの練習の候補になる。どれも atcoder.jp を開かずに問いを確かめる第三者の解説を探しきれていない。

| 問題 ID の例 | 何を問うか（題名から） | 裏付けの URL |
| --- | --- | --- |
| aalc001_a〜aalc001_d | Segment Tree・Lazy Segment Tree・Binary Search on a Segment Tree・Inversion Count | 未確認（第三者の解説が見つからない） |
| game_a・game_d・game_e | Nim・Parallel Nim・Restricted Nim 1 | 未確認 |
| ndpc2026_n・ndpc2026_p・ndpc2026_t | Knapsack・LIS・Independent Set | 未確認 |

## 未解決の点

- NDPC・AAL Contest 001・組合せゲーム 24 題の難しさの目安は、第三者の資料で確かめられなかった（本文では「本文ではまだ使っていない」とだけ書いた）
- ADT・AWC が Unrated であることは、AtCoder Problems のデータの rate_change が「-」であることだけで確かめた（公式のお知らせは atcoder.jp なので開いていない）。ADT の MEDIUM・HARD の終わり（2026-02-05）も、データの最後の回の日付による
- 鉄則本の問題番号の B・C の意味（節末問題・力試し問題）は、README の語から推測できるが確かめきれなかったので、本文には書いていない（A が各章の例題であることは、章ごとの解答コードのファイル名で確かめた）
- NoviSteps のグレードと ABC の位置の対応（research 00 §6.9 の D≈2Q〜1Q など）は、出典が drken 氏の記事題名の目安で NoviSteps のグレードと同じものか確かめられなかったので、本文には書いていない
- EDPC・TDPC・鉄則本の「レベルの目安」は、本文でその問題を載せたページの level の分布（手元で数えた値：EDPC は水 13・青 9・基礎 5 ほか、TDPC は水 5・黄 4・青 3 ほか、リンクの出現回数）から書いた。作者の示す目安ではない
- 使用量の目安：道具の呼び出し約 50 回、Web 取得 13 回（検索 6 回を含む）

## 検証の指摘への対応（b5 直し）

- 指摘 1〜8 はすべて直した。指摘 6 は、表の前に「400 未満は AtCoder Problems の表示と同じく縮めた値」を足し、atcoder-system#difficulty へリンクした。指摘 8 の ACL Practice は「水〜黄が多い」にした
- 指摘 5 の出典（ei1333 の Hu-Tucker のページ）は参考の節には足していない（本文では「満点に O(N log N) が要る」と断っただけで、解法は説明していないため）。参考に足すかはメインの判断に任せる
- 採らなかった指摘：なし
