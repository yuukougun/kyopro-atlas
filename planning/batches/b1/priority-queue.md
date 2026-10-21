# priority-queue の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/ds/priority-queue.md、snippets/priority-queue/{usage,binary-heap,kth-prefix,offset-heap,erasable-heap}.{cpp,yaml}、docs/img/priority-queue/{heap-push-pop,lazy-deletion}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21。sections は変えていない）
- 検査の結果：check_pages エラー0・警告0、check_snippets 5 件すべて期待どおり、fix_problems --check でこのページの直すべき行 0、textlint エラー0・警告 11（数式の中の読点・「K 番目に」の「に」の重複・骨格の signs の行・図の代替テキストの長さなどの誤検出）
- 図：visual は static・priority 2 なので静的な SVG 2 枚にした（動く図の div は置いていない）。SVG を描画して目で確かめる道具が手元になく、座標の計算で確かめただけなので、検証役に表示の確認を頼みたい
- 使った出典：kyo-pro（abc234_d）、drken（abc123_d・abc170_e・abc116_d）、scrapbox.io/nishio（abc170_e の遅延削除）、qiita comet725（abc471_d）、qiita snsn46（abc217_e）、merom686（abc391_f）、scrapbox.io/procon-kirokuyou（abc214_e）、cpprefjp（priority_queue・コンストラクタ・make_heap）
- 新しく noai を確かめたドメイン：scrapbox.io（https://scrapbox.io/nishio/ABC170_E で確認。X-Robots-Tag・meta ともに指定なし）。付録 B への追加を提案する

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc471_d | summary | 時刻とともに増え上限で止まる値を追加するクエリと、最大のものを取り出してその値を答えるクエリを処理する。 | https://qiita.com/comet725/items/cc08f26bb6f986813248 |
| abc471_d | approach | 時刻 t に入る値 w を w − t で最大ヒープに入れ、取り出したら今の時刻を足して上限 V との min を答える | 同上 |
| abc214_e | evidence | https://scrapbox.io/procon-kirokuyou/ABC214_E_-_Packing_Under_Range_Regulations_(500)（今の URL は末尾の「(500)」が欠けて 404） | 同左 |
| abc391_f | title | 末尾の空白を除いた「K-th Largest Triplet」（台帳の title に末尾の空白がある。fix_problems の出力では除かれていた） | — |
| abc170_e | evidence | https://scrapbox.io/nishio/ABC170_E を追加（遅延削除のヒープの方針。drken 氏の記事は set とセグメント木だけ） | 同左 |
| abc234_d | evidence | https://kyo-pro.hatenablog.com/entry/ABC234D を追加（今の drken 氏の記事は Wavelet Matrix の解法で、ヒープの方針が本文にない） | 同左 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 完全二分木 | complete-binary-tree | 最下段以外の段がすべて埋まり、最下段は左から詰めて並ぶ二分木。0-indexed の配列で、頂点 v の子を 2v + 1 と 2v + 2 に置いて表せる |
| ならし計算量 | amortized-complexity | 操作を何回も行ったときの合計を回数で割った、1 回あたりの計算量。1 回だけなら重いことがあっても、合計で抑えられる（手引きの付録 A に語はあるが用語集に anchor がない。本文ではリンクしていない） |

## 手引きへの提案

- §5 の ds に「優先度付きキューのように標準ライブラリで足りるデータ構造でも、自作の要点（保つ性質・各操作の手順・境界）は二分ヒープの節に 3 つの小見出しでそろえた」ことを、標準コンテナの応用の章の扱いとして明記してはどうか（基礎寄りのページでどこまで自作を書くかの基準）
- SVG を確かめる道具（rsvg-convert など）が環境にない。図を描く執筆者のために、描画して PNG を見る手段を用意してほしい

## 問題の補充の候補

catalog の例題 3・練習 5 で足りているので必須ではない。research/05-ds にある次の問題は台帳になく、ページの型の練習に合う（ap.py と第三者の解説での確認はしていない。足すなら確かめる）。

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc253_c | 多重集合への追加・個数を指定した削除と、最大値 − 最小値の出力（遅延削除か multiset） | https://kyo-pro.hatenablog.com/entry/ABC253C |
| abc331_e | 禁止の組を除いた主菜と副菜の組の最大価格（価格の大きい組から列挙） | https://zenn.dev/shinonome81/articles/3e1c0c8a9c00fc |
| abc384_e | グリッドで隣のスライムを条件つきで吸収し続けた後の最大の強さ（弱い順にヒープから） | https://zenn.dev/shinonome81/articles/b1de75b0849b32 |

## 未解決の点

- abc471_d の問題の細部（値が増える速さが 1 か、時刻が単調か）は、第三者の解説のコード（w − t を入れ、取り出し時に t を足して V との min）から読み取ったもので、解説の本文には書かれていない。本文の要約と方針は「同じ速さで増える」「上限で止まる」までにとどめた
- abc391_f の評価値の式は、参照した解説に書かれていないので本文に書いていない（「降順にソートすると添字を進めても増えない」とだけ書いた）
- abc170_e の解法の詳細（園ごとのヒープと全体のヒープの両方で検証して捨てる）は nishio 氏の説明に基づく。drken 氏の記事は set とセグメント木なので、別解として multiset に触れた
- 節「使い分け」は sections の vs-multiset が同じ内容なので、定型の `## 使い分け {#comparison}` は置かなかった。必要ならメインの判断で足す
- 「ACL では」の囲みは、ACL に対応がない（acl: []）ので置いていない
