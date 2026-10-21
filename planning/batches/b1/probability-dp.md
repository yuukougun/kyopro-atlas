# probability-dp の報告と提案（工程8b・b1）

- 書いたファイル：docs/comb/probability-dp.md、snippets/probability-dp/coins.{cpp,yaml}、snippets/probability-dp/sugoroku.{cpp,yaml}、docs/img/probability-dp/flow.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも期待どおり、textlint エラー 0（警告 15 件。数式を含む文の助詞「に」の重複、図の代替テキストと例題の詳細の数式を含む文の長さ、ledger 由来の要約の行、参考の行の長さで、どれも誤検出か直すと読みにくくなるもの）
- 図：静的な SVG を 1 枚（コイン 2 枚で確率が分かれて流れる 3 段階の図。catalog の visual priority 2 に当たる）。動く図は作っていない。SVG は描画ツールが手元になく、目で確かめられていない（XML として正しいことだけ確かめた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc271_g | summary | 1 日の 24 個の時刻ごとに担当（高橋君か青木君）が決まり、毎日各時刻に担当が決まった確率でアクセスするとき、N 回目のアクセスが青木君である確率を求める。 | https://kmjp.hatenablog.jp/entry/2022/10/04/1000 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/1001_abc271 （解説の部分） |
| abc271_g | approach | 状態を直前のアクセスの時刻にし、次のアクセスの時刻への確率（何日もない場合は等比級数でまとめる）を 24×24 の行列にして、行列累乗で N 回分を求める | 同上 |
| abc271_g | evidence | ikatakos の URL を追加 | 同上 |
| abc382_e | pages | probability-dp に practice を追加（1 パックのレアの枚数の分布を前向きの確率 DP で求める部分） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1130_abc382#e_-_expansion_packs （台帳の既存の evidence。07-math-comb §4.5 の expected-value-dp のメモにも同じ記述）。本文にはまだ載せていない |

- 本文の abc271_g の行は、台帳の summary が「（執筆時に確かめる）」なので上の新しい値で書いた。台帳を直してから fix_problems を流しても要約は変わらない（fix_problems は要約を変えない）
- abc298_e の approach は「（または後ろから求める）」で合っている。第三者の解説（programming-hiroba）は後ろ向き（位置の大きい方から勝つ確率を埋める）で解いている

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 吸収状態 | absorbing-state | 一度入ったら確率 1 でそこにとどまる状態。ゴールを吸収状態にすると、「K 回以内に着く確率」が「K 回後にそこにいる確率」になる。 |
| 排反 | mutually-exclusive | 2 つの事象が同時には起きないこと。排反な事象の和の確率は、それぞれの確率の和になる。 |

本文では「吸収状態」「排反」を用語集へリンクしていない（定義を本文に書いた）。用語集に足したら、最初に出た箇所にリンクを足すとよい。

## 手引きへの提案

- §2.3 と §13 の 1 に「ACL では」の囲みの置き場所の決まりがない。見出しを立てずに囲みだけを落とし穴の後に置いたが、定型の見出し（例：`## ACL では {#acl}`）にするかを決めてほしい
- §7 の「ほかのページの節へは draft 以降のときだけリンク」と、front matter の related にある `lattice-paths#independent-axes`（相手は stub）の関係。本文では lattice-paths のページ全体へリンクした。related の anchor は検査で解決しているので問題はないが、本文のリンクは相手が draft になったら節へ直すとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付け |
| --- | --- | --- |
| abc382_e（確認済み、1671） | パックを開け続けてレアを X 枚集めるまでの回数の期待値。1 パックのレアの枚数の分布を確率 DP で求め、期待値 DP と組み合わせる | 上の表のとおり。practice の候補（前向きと後ろ向きの組み合わせの例として「期待値 DP との使い分け」の節に合う） |
| abc310_f（台帳になし、1938） | N 個のサイコロ（i 個目は 1〜A_i）を振ったとき、いくつかを選んで和を 10 にできる確率を mod 998244353 で求める。作れる和（10 以下）の集合を bit で持つ確率 DP | 02-dp §5.1 の候補表。第三者の解説で確かめられたのは https://scrapbox.io/konan-compro/ABC310_(2023%2F07%2F15) の感想（「k に作れる確率」の DP では和が 1 にならず、bit DP にする）だけで、裏付けとしては弱い。challenge か practice の候補。採るなら解説をもう 1 つ探す |
| tdpc_tournament（台帳になし） | 2^K 人のトーナメントで各人が優勝する確率 | 02-dp §5.1 の候補表（sigma425 の TDPC 記事）。本文で中身は確かめていない |

## 未解決の点

- TDPC D の制約（N・D の上限）は、第三者の解説に書かれておらず確かめていない。本文には制約の値を書いていない
- ABC298 E のサイコロの面の数の上限・N の上限も確かめていない（本文には書いていない）
- ABC463 G の制約は kmjp 氏の記事に明記がなく、本文の方針は「二項係数の部分和を先読みで少しずつ動かす」までにとどめた
- 「状態の設計」の節の「到達する値だけ持つ」で ABC300 E を、rational-mod のページの練習として名前だけ出した（台帳で確認済み）。例題・練習としては載せていない
- 新しく noai を確かめたドメイン：scrapbox.io（wafuwafualgorithm と konan-compro のページ。どちらも noai・noimageai の指定なし。利用規約の個別の確認はしていない）。TDPC D の参考に wafuwafualgorithm のページを使った

## 使った出典

- drken（Qiita）EDPC F〜J：例題 EDPC I の状態と遷移
- kazun ABC275 E：例題 ABC275 E の言い換え
- drken ABC323 E、programming-hiroba ABC298 E、sigma425 TDPC、wafuwafualgorithm TDPC D、drken ABC011 D：練習の方針
- kmjp ABC271 G、ikatakos ABC271（解説の部分）、kmjp ABC463 G：力試しの方針
- ACL document_ja の modint：inv の計算量

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 約 14 回（検索 2 回を含む）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：#pitfalls の「同じ配列の上で配る」を、和は 1 のまま変わらず検算では気づけないこと、小さい例を手で確かめることに替えた
- 指摘 2：確認問題の答えを「以下になり、一度着いてから離れる場合があれば小さくなる」にした
- 指摘 3：#random-walk 冒頭の前提を lattice-paths#independent-axes へのリンクにした（報告の「未解決」の lattice-paths の件はこれで解消）
- 指摘 4：確認問題「吸収状態を作らないと」を #state-design のすごろくの段落の後へ移し、問いの書き出しを「上のすごろくで」にした
- 指摘 5：「まとめる」の 1 文目を分けた
- 指摘 6：#matrix-power の 3 段落目に、u 時から v 時への遷移の確率が「途中で何も起きない確率 × v 時に起きる確率 × Σq^d」になることを 1 文で書いた
- 指摘 7：flow.svg の t = 1 → 2 のラベルを、表 0 枚の箱から出る 1 組だけにした（列の見出しの p₂ = 0.5 と凡例の実線・破線で読める）
- 採らなかった指摘：なし
- 台帳への提案（検証役から、メインで反映）：abc275_e・abc271_g・abc463_g の `checked` を 2026-10-21 に
