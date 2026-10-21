# spf-sieve（最小素因数の篩と線形篩）の報告

- 書いたファイル：docs/math/spf-sieve.md、snippets/spf-sieve/spf.{cpp,yaml}、snippets/spf-sieve/linear-sieve.{cpp,yaml}、docs/img/spf-sieve/chain.svg
- front matter で変えたもの：complexity・stage（draft）・updated。節 `after-factor`「分解した後の使い方（異なる素因数・指数・約数）」を sections に足した（level はページと同じ）
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 期待と違う 0／textlint エラー 0・警告 7（文の長さ・助詞の重複。数式や問題の行を含む文で、残した）／fix_problems --check は自分のページで 0 件（全体では math/divisor-enum.md:181 の diverta2019_d の label が 1 件。担当外）
- 使った出典：drken の Qiita「エラトステネスの篩の活用法を総特集！」（表の作り方・計算量・線形篩）、drken の ABC177 E の記事（例題）、プロひろ・hyouri の ABC368 F の記事（練習）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc177_e | summary | 「どの2つも」→「どの 2 つも」（textlint の半角・全角の空白） | 表記の規則 |
| abc368_f | alternatives（spf-sieve）の summary | 「要素を1つ」「操作を2人」→「要素を 1 つ」「操作を 2 人」 | 表記の規則 |

本文の行はこの直した形で書いてある（fix_problems は本文の summary を保つ）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 素因数の個数 Ω(n)・ω(n) | prime-omega | Ω(n) は重複も数えた n の素因数の個数（360 = 2³·3²·5 なら 6）、ω(n) は異なる素因数の個数（同じく 3）。本文では未リンク（記法の行で定義した） |
| 最小素因数 spf(n) | smallest-prime-factor | n ≥ 2 を割り切る最小の素数。n が素数なら n 自身 |

## 手引きへの提案

- front matter の signs の「全ての組が互いに素か」は prh で「すべて」に直される語を含む。要点の囲みでは「すべて」に直したので、signs も「すべての組が互いに素か」に直すことを提案する（catalog 由来の signs・summary に「全て」が残っているページは他にもありそう）
- 基礎の technique の構成（要点 → 応用の型 → 落とし穴 → つながり → 問題）に対し、catalog の sections が「作り方・比較・線形篩・メモリ」だったので、応用の型を `after-factor` として節に足した。基礎のページで応用の型を節にして sections に載せるのを標準にするか決めてほしい

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc215_d（D. Coprime 2、diff 736） | 数列のどの要素とも互いに素な M 以下の整数 k を列挙する。各 A_i の素因数を集め、その倍数を篩のように消す（A_i の分解に最小素因数の表が使える。試し割りでも可） | https://qiita.com/sano192/items/00f6b70dab3bd3323ae6 ・ https://qiita.com/okm-uv/items/240b3fd3d2ff5f9561ab |

- ap.py で実在と diff を確認済み（2021-08-21、diff 736）。練習（易しい側）として spf-sieve に載せることを提案する。台帳には書いていない
- 解説の多くは試し割りで分解しているので、「最小素因数の篩でも試し割りでも解ける」型の練習になる

## 未解決の点

- ABC368 F の制約（A_i の範囲・A_i ≥ 2 か）は第三者の解説に明記がなく、hyouri のコードが 10^5 まで前計算していることから A_i ≤ 10^5 と推測した。本文には制約を書かず、「値が小さいので試し割りでも間に合う」とだけ書いた
- 「AtCoder のメモリ制限は 1024MB の問題が多い」は一般的な知識で書いた（最近の ABC の標準）。出典で確かめたい場合は検証役に頼む
- 線形篩とエラトステネスの篩の実測の速さは測っていない（本文は「log log V は 3 程度で、ほぼ変わらない」と理論の目安だけ）
- 動く図はない（visual は static・priority 2 なので SVG 1 枚で済ませた）
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 6 回・検索 1 回
