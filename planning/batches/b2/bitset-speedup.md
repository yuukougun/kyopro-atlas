# bitset-speedup の報告（b2・青）

- 書いたファイル：docs/misc/bitset-speedup.md、snippets/bitset-speedup/{triangle,subset-restore,reach-dag,reach-batch}.{cpp,yaml}、docs/img/bitset-speedup/{word-and,shift-or}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 片すべて期待どおり、textlint エラー 0（警告 24。数式を含む文の長さ・助詞の重なり・折りたたみの中の箇条書きの誤検出）。図は render_svg で 360px・720px を目視した
- 動く図：作っていない。catalog の visual は priority 2（static）なので静的な SVG 2 枚で代えた。kp-viz の div は置いていない
- 使った出典：参考の節の 9 件。新しく check_noai で確かめたドメイン：scrapbox.io/konan-compro（noai 指定なし。ABC348 F・ABC350 G の記述がなく使わなかった）、petalite-healer-98a.notion.site（指定なし。本文が取れず使わなかった）。zenn.dev・www.cnblogs.com・kmjp.hatenablog.jp・github.com は付録 B にある

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc287_h | summary | 有向グラフで、s から t へ行く道のうち、通る頂点の番号の最大値が最小になるものを選んだときの、その最大値を各クエリで求める（行けなければ -1）。 | https://kmjp.hatenablog.jp/entry/2023/01/28/0930 |
| abc287_h | approach | 頂点を番号の小さい順に加え、到達集合をワーシャルフロイド法と同じ順に bitset の OR で更新し、届くようになった時点の番号を答える | 同上 |
| abc221_g | summary | 長さ D_i の移動を順に上下左右のどれかへ行い、原点から (A, B) に着けるかを判定し、着けるなら向きの列を 1 つ出力する。 | https://kmjp.hatenablog.jp/entry/2021/10/03/1000 |
| abc221_g | evidence | 上の kmjp の URL を足す（ikatakos.com は 2026-10-21 に 503 で読めなかった） | 同上 |
| abc348_f | evidence | https://zenn.dev/mmrz/articles/abc348-f-learning-bitset を足す（ikatakos.com は 503 で読めなかった） | 同 URL |
| abc350_g | alternatives（bitset-speedup）の approach | 次数がしきい値（√N 程度）以上になった頂点だけ隣接集合を bitset で持ち、両端が大きければ AND、片方が小さければ隣接リストを調べる（全頂点の bitset は N²/8 バイトで置けない） | https://www.cnblogs.com/No-play-Yes-splay/p/18148245/atcoder-beginner-contest-350-sol |
| abc350_g | evidence | 上の cnblogs の URL を足す | 同上 |
| arc070_b | alternatives（bitset-speedup）の summary | 主の summary と同じ文にそろえる（「定義は執筆時に確かめる」を消す）。必要なカードより値の大きいカードも必要、という単調性で二分探索する | https://drken1215.hatenablog.com/entry/2020/10/06/113600 |
| typical90_bg | evidence | https://github.com/E869120/kyopro_educational_90/blob/main/problem-txt/059.txt を足す（制約 N, M, Q ≤ 10^5、X < Y を確かめた） | 同 URL |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| ワード並列 | word-parallel | 64 bit の整数（語）を 64 個の 0/1 の入れ物とみて、1 回の AND・OR・XOR で 64 か所を同時に計算すること。計算量の次数は変えず、定数倍をおよそ 1/64 にする。 |

（本文では用語集へのリンクを張っていない。足すなら本文の最初の「ワード並列とは」からリンクしてよい）

## 手引きへの提案

- §5 misc の「bitset は 1/64 になる根拠を書く」に、「計算量の次数が 1 つ違う問題は救えないこと（目安の表）と、メモリ N²/8 バイトの見積もり」を足すとよい

## 問題の補充の候補

- なし。abc319 以降の ABC は abc348_f（例題）と abc350_g（練習）があり、目安を満たす

## 未解決の点

- ABC348 F の制約（N・M の上限）は第三者の解説で数値を確かめられなかった（zenn の記事はコードの bitset<2000> からの推定だけ）。本文では制約の数値を書かず、目安の表の「N = M = 2000」は一般の例として書いた
- ABC258 G の N ≤ 3000 は台帳の summary に従った。merom686 の記事には制約の記載がない
- 確認問題の「制限が 1024 MB なら置ける」は条件付きの言い方にした。各問題のメモリ制限は確かめていない
- degree-sqrt・gaussian-elimination・xor-basis は stub なので、anchor を付けずにページへリンクした。degree-sqrt が draft になったら #triangles へ、gaussian-elimination は #mod-2 へ張り替えるとよい
- 使い分けに「疎なグラフの三角形は O(M√M)」と書いた。degree-sqrt の本文と食い違いがないか、検証役に見てほしい

## 使用量の目安

- 道具の呼び出し約 45 回、Web 取得 約 20 回（うち 503 が 3 回）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜10 はすべて直した（採らなかった指摘はない）
  - 1：届く例（$N = 10^5$ の $O(N^2)$）と届かない例（$N = 10^4$ の $O(N^3)$）を対にした
  - 2：memory-batching と典型90 059 の詳細を「約 3.1×10^8 回の語の演算（うち OR は約 1.6×10^8 回）」にした
  - 3：`dp._Find_next(x - 1)`（$x = 0$ なら `_Find_first()`）にし、なければ `MAXS + 1` が返ることを足した
  - 4：ABC221 G は表を 1 つ作って 2 軸の復元に使い回すこと、1 GB 近くになりうることを書いた
  - 5：kmjp ABC287 Ex の出典の説明に、記事は 2 つの集合を更新する別の形だと足した
  - 6：degree-sqrt#triangles・gaussian-elimination#mod-2 に張り替えた（xor-basis は stub のまま）
  - 7：落とし穴を「K 以上を問うなら K + 最大値まで、K 未満だけを見る問題（ARC070 D）なら K で足りる」にした
  - 8：「要素がすべて正の整数で総和が S の列なら（和の上限も S にとれる）」と条件を足した
  - 9：reach-dag.cpp に頂点ごとの探索との assert を足し、2 段のひし形の case（7 5 5 4 2 2 1）を足した
  - 10：両方の図の viewBox の左右の余白を詰め、凡例を 14px に上げた。添字を tspan にし、「品物」を「要素」にした
- 検査：check_pages エラー 0・警告 0、fix_problems 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 27、文の長さなど）
