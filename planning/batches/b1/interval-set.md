# interval-set の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/interval-set.md、snippets/interval-set/{paint,cover}.{cpp,yaml}、docs/img/interval-set/assign.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections の choosing の title を「使い分け（次の空きへ飛ぶ Union-Find・遅延セグメント木）」に短くした（anchor は同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（このページの直すべき行 0。string/kmp.md に 6 行あるが担当外）、check_snippets（2 件すべて一致）、textlint（エラー 0・警告 38）
  - 残した警告：no-unmatched-pair は半開区間 $[l, r)$ の誤検出。sentence-length・max-comma の多くは数式を含む文と、要点の囲み・折りたたみの見出し行を 1 文と数えたもの
- コード片：手元で乱数の入力 300 件ずつを流し、素朴な配列との一致（assert）を確かめた
- 図：静的な SVG 1 枚（catalog の visual は static・priority 2）。描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた
- 使った出典：qiita.com（omakasessan、abc435_e）、merom686.hatenablog.com（abc435_e の別解）、drken1215.hatenablog.com（abc380_e・abc330_e）、kmjp.hatenablog.jp（abc430_g・abc255_h・abc256_h）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc435_e | summary | 変更なし（N ≤ 10^9 は検索結果の複数の解説で一致） | https://qiita.com/omakasessan/items/4d5dfca408ace2f70f7c |
| abc435_e | evidence | merom686 の記事を足す（座標圧縮＋遅延セグ木の別解） | https://merom686.hatenablog.com/entry/2025/12/07/023253 |
| abc380_e | approach | 「同色の区間の左端を map で持ち、隣と同色ならまとめる（Union-Find・遅延セグ木でもよい）」。evidence の drken の記事自体は遅延セグ木の解で、set は公式解説の別解として紹介されている | https://drken1215.hatenablog.com/entry/2024/11/17/035045 |

ほかの使った問題（abc330_e・abc430_g・abc255_h・abc256_h）の summary と approach は、evidence の解説と食い違いがなかった。役割は台帳のとおり（abc430_g は練習、abc255_h・abc256_h は力試し）。

## 用語集への提案

- なし（ならし計算量は complexity-estimation#amortized へ、半開区間・番兵は既存の用語集の anchor へリンクした）

## 手引きへの提案

- §13.1 の定型の「使い分け」は `{#comparison}` だが、このページは骨格の sections に `anchor: choosing` の使い分けの節を持つ。§13.2 に従い sections の節として見出しを置き、`## 使い分け {#comparison}` は別に立てなかった。lazy-segment-tree も `choosing` なので、ds の章で揃えるかメインで決めてほしい

## 問題の補充の候補

- abc478_d（D. Range Set Insertion Query、diff 729、台帳では event-sort の練習で summary が未確定）：区間に値を入れる操作の後、各位置にある値の種類数を求める。値ごとに区間をまとめて重複を除いてからいもす法で数える型で、このページの「覆われた区間だけを持つ形」の練習に使える。裏付け：https://qiita.com/tototti/items/1915baced8ce575d28b2（research/05-ds 付録 A、確度 medium。今回は読んでいない）
- abc319 以降の水の E で、区間を set で管理する問題を ap.py と解説で探すのは今回できていない。例題の abc435_e・abc380_e がどちらも abc319 以降なので、要件（水のページに 1 問以上）は満たしている

## 未解決の点

- abc435_e の Q の上限は確かめていない（本文では Q の値を書かず、$O(Q \log Q)$ とだけ書いた）
- abc255_h は N の上限を確かめておらず、本文では「答えが大きくなるので型に注意する」とだけ書いた
- 力試しの方針の abc256_h の評価（値が 0 の区間を隣とまとめる、正の区間を割る回数の合計）は kmjp の記事の要旨から自分で組み立てたもの。検証役に確かめてほしい
- 落とし穴の「右端を要素に持つ set では split(r) を先にする」は ODT の一般的な実装の注意として記憶に基づく（`map` への挿入がほかのイテレータを無効にしないことは C++ の規格どおり）

## 検証の指摘への対応（verify/interval-set.md）

- 1（直すべき）：sections から choosing の行を消し、見出しを `## 使い分け {#comparison}` にした（このページの #choosing へのリンクは 0 件）。上の「手引きへの提案」は解決したので取り下げる。lazy-segment-tree の choosing も同じ決まりにそろえるかはメインで判断してほしい
- 2（直すべき）：ABC255 Ex の方針を「998244353 で割った余り。番号の和は `__int128` か 2 の逆元で」に直した
- 3（直すべき）：#valued-intervals の最後を「差分を流す回数は区間の値が変わる回数に比例する（代入だけなら消える回数、割り算なら割る回数）」に直した
- 4〜9（直すとよい）：すべて採った。4 要点の計算量に崩れる条件を追記、5 空の区間を map の形の説明に、6 ABC380 E の番兵（右は値 0、左は最初の区間なら見ない）を追記、7 「区間の中の最大値とその個数」に直し、重なっていた「値ごとの区間の集合」の項と 1 つにまとめた、8 「`map` への 1 回の挿入・削除」に、9 cover.cpp の `erase` を波かっこで書いた
- 10（直すとよい）：assign.svg を作り直した。viewBox を 540 幅にし（1 単位 38 のまま左端 24）、題を 2 行に、「新しい左端 2 と 10」の注記を ② の見出しの行へ移した。文字はキー 16・値 18・見出し 17。描画して目で見る道具がないので、XML として読めることと座標だけを確かめた（幅 358px での見え方はメインか検証役に確かめてほしい）
- ついでに直したもの：参考の abc430_g の説明が「力試し」になっていたのを「練習」に直した
- 台帳への追加の提案：検証役の結果から、abc380_e・abc330_e・abc430_g・abc255_h・abc256_h の `checked` に 2026-10-21 を入れる（abc435_e は Q の上限が未確認のため、入れるならその注記つきで）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 40。増えた 2 件は追記した文の sentence-length と no-unmatched-pair の誤検出）
