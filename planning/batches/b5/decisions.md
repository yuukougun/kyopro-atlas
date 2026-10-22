# b4・b5 の振り返りで決めたこと（2026-10-22、メイン）

b4（発展の概要 50）・b5（横断 33）の提案のまとめ（`summary/style.md`）への判断。手引きには §16 として足す（§13〜§15 と食い違えば §16 を優先）。既存のページをこの決定にそろえるのは、工程10の全体の検証で行う。

## 発展の概要（overview）

| 件 | 決定 |
| --- | --- |
| 学ぶための資料 | 定型の `## 学ぶための資料 {#resources}` にする（sections に載せない。§13-1 の一覧に足す） |
| ライブラリでの使い方 | 中身の節として anchor を `library` にそろえる（見出しの文字はページに合わせてよい。sections に載せてよい） |
| ACL に対応がないとき | 公開ライブラリの名前と使い方（関数名・引数・返り値）を文章で書き、自作するときの要点を処理の流れで添える。コードは載せない |
| Library Checker に対応がないとき | 「専用の問題はなく、部品（LCA など）の問題で確かめる」「対応する問題はない。愚直な方法と照らし合わせて確かめる」のどちらかを書く |
| 例題・練習が 0 問のとき | `## 例題` は省いてよい。`## 練習問題 {#practice}` には「ABC で必須になる問題は確認できなかった」の1文と、Library Checker などの小見出しだけを置いてよい |
| ほかのジャッジ | §15-5 を AOJ・CSES に広げる（noai の指定がないことを確かめてから）。yukicoder は利用規約を確かめるまで使わない |

## 横断のページ（guide・hub・pattern）

| 件 | 決定 |
| --- | --- |
| pattern の「代表の問題」の列 | 行き先のページの問題の label を文字だけで書き、リンクは行き先のページに任せる（見本 bracket-sequence の形） |
| hub の表の例題の列 | 相手のページの例題の小見出し（`../dp/cht.md#dp_z`）か `#practice` へリンクしてよい |
| pattern の overview | 「問われ方と手法の一覧」の節（anchor `overview`）を中身の節として sections に置く（§4 の pattern の構成に明記） |
| guide の構成 | 自由。目安の例として debugging-checklist（要点 → 導入 → 症状ごとの節 → 確認問題 → 参考）を §4 に書く |
| 生成ブロックの見出し | sections の見出し `## … {#anchor}` は生成ブロックの外の直前に手で置き、ブロックの中は `###` から始める |
| complexity | 計算量のない guide・hub・pattern のページは null のままにする |

## 全体

| 件 | 決定 |
| --- | --- |
| 計算で出した数字 | 本文の数字を出したスクリプトは `tools/numbers/<page-id>-<名前>.<拡張子>` に置き、本文の数字の近くか参考の節に「データから計算した値（日付）」と書く。スクリプトが残っていないものは工程10で作り直す |
| 手元で数えた値（§15-11） | 手元の実験の値（条件のコンパイラ・実装を添える）と、教材のデータから数えた値（日付を添える）にも広げる |
| 出典の題名の textlint | 題名は原文のまま書く。参考の節の該当の行だけを `<!-- textlint-disable ja-space-between-half-and-full-width -->` 〜 `<!-- textlint-enable ja-space-between-half-and-full-width -->` で囲んでよい |
| 表記の揺れを例に出すページ | 索引・用語集・表記の説明の箇所を `<!-- textlint-disable prh -->` 〜 `<!-- textlint-enable prh -->` で囲んでよい |
| 判断待ちの台帳の件 | agc002_d・abc311_h・abc458_g・keyence2019_e・abc189_c・abc197_c（summary/ledger-result.md）は工程10で決める |
- §16-7 の言い回し：見本 bracket-sequence はページ自身の例題・練習の囲みも持つ。「代表の問題の列は label の文字だけ。pattern のページが自分の囲みを持つのは構わない」と工程10で明記する
- 張り替え（2回目）の残り：リンクの文字を相手の題名にそろえる6か所（euler-phi:153・bipartite-matching:157・difference-constraints:219・euler-path:221・priority-queue:196・cdq-divide-and-conquer:119。relink-plan.md）は工程10で直す
- 題名に角かっこを含む問題（abc411_e「E [max]」）を check_pages.py・fix_problems.py の正規表現が読めない。道具を直してから expectation-tail-sum の練習に足す（提案は batches/b6/APPLIED.md）
