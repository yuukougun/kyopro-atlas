# sqrt-decomposition の報告（b3）

- 書いたファイル：docs/ds/sqrt-decomposition.md、snippets/sqrt-decomposition/{bucket-add-count,step-dp}.{cpp,yaml}、docs/img/sqrt-decomposition/buckets.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は §14-2 に従い choosing を外し（定型の `## 使い分け {#comparison}` に）、§14-12 に従って長い title を短くした（anchor は変えていない）
  - buckets：「完全に含まれるブロックは…」→「丸ごと入るブロックはタグ、端は要素ごと」
  - heavy-light：「（合計が抑えられた量の大小で分ける）」だけにした（歩幅の話と次数のページへの入口は本文に書いた）
  - implementation：「（ブロック番号・同じブロックの場合・タグの押し下げ・B の選び方）」
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致（どちらも乱択で素朴な方法と突き合わせる self_test を持つ）、textlint エラー 0・警告 24（数式の中の角括弧の対応・数式を含む文の長さ・助詞の重複の誤検出に近いもの）。SVG は render_svg で 720px・360px を目で確かめた（360px では文字が小さいが読める）
- 動く図：visual は static・priority 2 なので、静的な SVG 1 枚（buckets.svg）にし、kp-viz の div は置いていない
- 使った出典：torus711（abc335_f）、kmjp（abc219_g・abc403_g）、suzukiapple.tumblr.com（abc365_g）、merom686（abc259_h）、Library Checker（static_range_mode_query）。新しく確かめたドメインはなし（suzukiapple.tumblr.com は台帳の evidence にあったもの。付録 B にないので、メインで check_noai を確かめてほしい）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc259_h | evidence | `https://merom686.hatenablog.com/entry/2022/07/10/002150` を足す | ikatakos.com が HTTP 503 で読めなかった（2026-10-21）。merom686 の記事で「出現数 N 以上のラベルは N 個以下で色ごとに DP、N 以下はペアの全探索と二項係数、全体 O(N^3)」を確かめた |
| abc259_h | approach | 「出現数が N 以下のラベルは同じラベルの組を全部見て二項係数で数え、N を超えるラベル（N 個以下）はラベルごとにグリッドの DP」 | 同上 |
| abc365_g | approach | 「記録が多い人（M/C 人以下）はその人ごとに全記録を 1 回走査してほかの全員との値を前計算し、少ない人どうしは区間の列をマージする」 | suzukiapple の記事 |

## 用語集への提案

- なし（degree-sqrt の報告で提案済みの「重い頂点・軽い頂点」heavy-vertex が入れば、根号で場合分けの節の「重い頂点」にリンクしてよい）

## 手引きへの提案

- §14-25「箇条書きの各行は句点で終える」に従って本文の箇条書きに句点を付けたが、見本の lazy-segment-tree は句点のない箇条書きが多い。見本と規則のどちらに合わせるかを決めてほしい（要点の囲みの「前提」の行は見本どおり句点なし）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付け |
| --- | --- | --- | --- |
| abc405_g | 区間内の X 未満の要素を並べ替えてできる列の種類数を答える | 練習（mo-algorithm の力試しと共有。Mo の伸縮 O(1)・取得 O(√N) の値の平方分割の例） | https://kmjp.hatenablog.jp/entry/2025/05/10/0900（台帳で確認済み。本ページ向けの approach は未確認なので、検証役に読んでほしい） |
| typical90_ac | 区間にレンガを順に積み、各レンガの上端の高さを答える | 練習（配列のバケット分割で区間 max・区間代入。タグの押し下げが要る代入の練習） | 台帳の evidence（research の表に「座圧・平方分割でも解ける」とある。平方分割の解き方を書いた第三者の解説は確かめていない） |

- abc319 以降で、配列のバケット分割そのもの（区間加算＋区間の x 以上の個数など）を使う ABC の問題は見つけられなかった。クエリの平方分割の例題もない（本文では台帳にない木の例を問題 ID なしで書いた）

## 未解決の点

- abc219_g・abc259_h の制約の上限は第三者の解説で確かめられなかったので、本文では書いていない（abc219_g の計算量は N・M・Q の式だけ、abc259_h は N×N のグリッドとして O(N^3)）
- クエリの平方分割の節で「Mo's algorithm もクエリを平方分割する方法と呼ばれることがある」と書いた。b2 の mo-algorithm の検証（ei1333 の記事に英語の別名 Query Square Root Decomposition がある）を根拠にしたが、自分では記事を開いていない
- 確認問題の「タグを押し下げないと代入が消える」は、snippets で確かめていない（加算のコード片だけ）
- abc219_g の解法の詳細は kmjp の記事（重い頂点は時刻と値を記録し、処理する頂点の隣の重い頂点を確かめる）をもとに組み立てた。コード片で突き合わせてはいない（同じ形の degree-sqrt/paint-query.cpp は検査済み）

## 使用量の目安

- 道具の呼び出し約 35 回、Web 取得 6 回（検索 3 回を含まない）

## 検証の指摘への対応（直し）

- 指摘 1〜7 はすべて直した（参考の題名を記事の h1 に・歩幅の型は合計の抑えでなく種類の少なさを使うと表の前と段落の頭に明記し、表の 3 行目を「小さい歩幅は B 種類未満」に・Mo の説明を「先読みして並べ替える（基本形は更新のない列）」に・K ≈ √Q と呼ぶ理由を 1 文足した・count_ge のしきい値を y に・cases の 3 つ目を丸ごと入るブロックにタグが付く加算 [1, 5) に替えた・図は下の説明 3 行を省いて文字を 18〜20px に上げた）
- 指摘 8 は共有の front matter の summary に当たるので、下の提案とした

## summary への提案（検証の指摘 8）

- summary の末尾を「…ブロックごとに集約とタグを持つ方法と、大きいものと小さいもので処理を変える方法と、クエリをまとめて作り直す方法がある。」とし、要点の「何ができるか」の 3 つの方法とそろえる
