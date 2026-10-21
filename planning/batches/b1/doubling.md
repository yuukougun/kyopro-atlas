# doubling（ダブリング）の執筆報告と提案

- 書いたファイル：docs/basics/doubling.md、snippets/doubling/{kth-next,sum-table,max-steps,func-power}.{cpp,yaml}、docs/img/doubling/table-jump.svg
- front matter で変えたもの：complexity（前計算 O(N log K)、1 回の問い合わせ O(log K)、メモリ O(N log K)）・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査：check_pages --page doubling（エラー 0・警告 0）、check_snippets snippets/doubling（4 本・計 23 case 一致）、textlint（エラー 0、警告 8）
  - 残した警告：数式の半開区間 `[0, 2^k)` の括弧の対応（誤検出 2）、数式を含む文の長さ（要点の囲み・折りたたみの確認問題・Sparse Table の項目）、「時間は〜メモリは」の助詞「は」の重なり 1
  - fix_problems --check は fractional-binary-search.md の 8 行を指摘する（他の担当のページ。doubling は 0）
- 図：catalog の visual は priority 3 なので、動く図は作らず静的な SVG（表を 3 段作り K = 5 で 2 回跳ぶ）で代えた
- 使った出典（どれも付録 B のドメイン。新しいドメインはない）
  - drken1215.hatenablog.com/entry/2020/06/20/190700（ABC167 D の表と 2 進展開・周期の検出の別解）
  - qiita.com/recuraki/items/e26c220f2bc01f58e185（ABC241 E の位置と和の表）
  - oi-wiki.org/basic/binary-lifting/（和を半開で持つ考え方だけ。文章・図は使っていない）
  - oraclesqlpuzzle の abc367-e・abc258-e・abc013-d（練習の方針）
  - drken1215.hatenablog.com/archive/category/ダブリング（補充の候補を探すため）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc241_e | summary | 飴の個数 X に A_{(X mod N)} 個を足す操作を K ≤ 10^12 回行った後の飴の個数を求める。 | 今の「皿にある飴の個数で次の位置が決まる」は「位置」が分かりにくい。https://qiita.com/recuraki/items/e26c220f2bc01f58e185 |
| abc167_d・abc241_e・abc258_e・abc367_e・abc013_4 | checked | 2026-10-21 | 各 evidence の解説で問いと方針を確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| オフライン | offline | クエリをすべて先に読み、答える順や処理の順を自由に並べ替えてから答える処理の仕方。読んだ順にその場で答えるのはオンライン。（ほかのページもすでにこの anchor にリンクしているが、用語集にまだない） |

## 手引きへの提案

- §9 のコード片：「和の表は使わない上の段まで作るとあふれる（符号付きのあふれは未定義動作）。段数は K の上限に合わせるか、和を頭打ちにする」をダブリング・Sparse Table・LCA の表の共通の注意として足すとよい
- 早見表・使い分け（basics の「巨大な K 回」の行）に「始点がすべてで K が 1 つなら、写像の繰り返し二乗法で O(N) のメモリで済む」を足すとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc136_d | R と L のマスで子どもが 10^100 回移動した後の各マスの人数（決まった遷移を十分大きい偶数回進める） | 練習（台帳には run-length-encoding の練習としてある。ダブリングの解き方もある） | https://drken1215.hatenablog.com/entry/2020/12/29/190100（drken のダブリングの分類に入っている。本文は未読） |
| arc060_c | ホテルの間を 1 日 L 以内で移動するとき、2 つのホテルの間の最小日数を答えるクエリ（ダブリング上の二分探索の代表） | 力試し（diff 2154 で黄。ap.py で確認） | 第三者の解説はまだ見つけていない（要調査） |

- 水のページだが abc319 以降（7 問体制）の問題が 0 問である。ap.py の search は題名でしか引けないので、ダブリングの最近の ABC は見つけられていない。第三者の解説（はてなブログの分類など）で探す必要がある

## 未解決の点

- abc319 以降の例題・練習がない（上記）。ダブリング上の二分探索と、オフラインで 2 段だけ持つ方法を使う台帳の問題もない
- ABC241 E・ABC258 E・ABC013 D の制約の正確な値は第三者の解説から読み取れなかったので、本文では ABC241 E の K ≤ 10^12（台帳の値）以外の制約の数値を書いていない
- SVG は描画の道具がなく目で確かめていない。文字幅は見積もりで 640 の幅に収めた。検証で描画を確かめてほしい
- 本文はメモリ制限の値（AtCoder の多くの問題の上限）を書かず「問題のメモリ制限と比べる」とした
