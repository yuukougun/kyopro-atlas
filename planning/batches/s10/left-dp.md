# 工程10 直し：dp・misc で残したもの

dp・misc の直し担当が、担当の外のファイル（台帳・ほかの分野のページ・生成物）に要る直しや、判断の要るものをここに残す。

## anchor の付け替え（判断が要る）

- **cht・dynamic-dp・monge の `#verify` → `#library`（audit-structure、§16-2）**：「ページの id・URL・anchor は変えない」の決まりに従い、anchor は変えずに残した。見出しと sections の title は 3 ページとも「ライブラリでの検証」に縮めた（§14-12。問題名はもともと本文にある）。§16-2 にそろえるなら、メインが次をまとめて行う
    - 3 ページの見出しの `{#verify}` と sections の `anchor: verify` を `library` にする
    - `docs/geometry/advanced-geometry.md` L181 の `../dp/cht.md#verify` を `#library` に張り替える（geometry は担当の外）
    - `docs/index/dp.md` は gen_site.py が作り直す（`dynamic-dp#verify`・`cht#verify`・`monge#verify` の 3 行）
    - 外から `#verify` で来るリンク（サイトの外・localStorage）を気にするなら、転送の扱いを決める

## 台帳（data/problems.yaml）に要る直し

- **abc130_e（dp-prefix-sum の練習）**：本文に足していない。dp-prefix-sum の練習はすでに 6 問あり、今回 abc183_e（方向ごとの累積和）を足して 7 問になった（§10 の目安は 2〜6）。abc130_e は lcs と counting-dedup の練習にもあるので、台帳の pages から dp-prefix-sum を外すのを勧める。本文に足す方を選ぶなら、方針は「$S_i = T_j$ のとき $\mathrm{dp}[i][j] = 1 + \sum_{i' < i, j' < j} \mathrm{dp}[i'][j']$ を 2 次元の累積和で $O(1)$ にし、全体 $O(NM)$」
- **abc458_g（slope-trick の力試し）**：§16-17 の判断待ちの件（audit-shared ## shared (3)）。決まるまで本文には足していない。台帳では今は monge の練習だけを持つ
- **summary の「歩道」**：付録 A の正規形は「ウォーク」。台帳の summary に「歩道」が 6 か所残る（abc338_f の本体と alternatives、ほか 4 件。`grep -n 歩道 data/problems.yaml`）。bit-dp L241 の練習の行（abc338_f）は台帳から作られるので、本文だけ直すと fix_problems で戻る。台帳の summary を「ウォーク」に直してから fix_problems をかけてほしい

## 判断の要る図

- **dp-order/six-orders.svg**：2 列 × 3 段の 6 枚のパネルを 1 列に並べ直した（幅 260・高さ 1864）。文字は 360px で 12px 以上になったが、縦に長い。分けるなら 3 枚ずつの 2 枚の画像にする手もある（本文の差し替えが要る）。いまのままでよいかを決めてほしい

## 検査で見つけた担当外のエラー

- `npm run lint:text` のエラー 1 件：`docs/ds/partially-persistent-union-find.md:122` の「UnionFind」（prh で Union-Find）。ds の直しが作業中のものと思われる（dp・misc のページにはエラーはない）
