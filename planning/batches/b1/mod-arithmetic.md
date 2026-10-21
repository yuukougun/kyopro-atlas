# mod-arithmetic の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/mod-arithmetic.md、snippets/mod-arithmetic/mod-ops.{cpp,yaml}、docs/img/mod-arithmetic/clock.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「繰り返し二乗法・逆元・modint へのつながり（next-steps）」を足した（level はページと同じ）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 0 行、check_snippets 期待と違う 0、textlint エラー0・警告6（要点の囲みの 1 行目は summary と同文なので残した。そのほかは助詞の重なりと数式を含む文の長さ）
- 図：catalog の visual（static・priority 2）に合わせ、静的な SVG（時計の輪 2 つ：合同な数が同じ位置に来ること、5 + 4 が 2 に着くこと）を手書きした。手元に SVG を描画する道具がなく、見た目は座標の計算でしか確かめていない。検証のときに目で確かめてほしい
- 使った出典：drken の 3 記事（abc275_b・abc055_b・arc111_a の台帳の evidence）。題名は記事の title 要素で確かめた。新しく noai を確かめたドメインはない
- 数の確認：998244353 と 10^9+7 が素数であること、998244353 − 1 = 2^23 × 7 × 17、10^9+7 − 1 = 2 × 500000003、998244353 の原始根 3、2(p−1) < 2^31、(p−1)^2 < 2^63 を Python で計算して確かめた

## 台帳への提案

- abc275_b・abc055_b・arc111_a：変更なし（summary と evidence の記事の内容が一致することを確かめた）
- arc111_a の mod-arithmetic 側の approach（alternatives）：「10^N mod M² を求め、M で割った商が答えになる」で問題ない

## 用語集への提案

- 合同｜congruence｜整数 a, b を m で割った余りが等しいこと（a − b が m の倍数であること）。a ≡ b (mod m) と書き、m を法と呼ぶ。
  - 本文は `../guide/glossary.md#congruence` へリンクしている

## 手引きへの提案

- なし。強いて言えば、§13.1 で next-steps（上位の手法とのつながり）を sections に載せるかどうかを明記するとよい（見本の binary-search-answer は載せているので、それに合わせた）

## 問題の補充の候補

- abc266_b（B. Modulo Number、diff 95、ap.py で確認済み）：|N| ≤ 10^18 の負もありうる N について、N − x が 998244353 の倍数になる 0 以上 998244353 未満の x を求める。C++ の % は負の余りを返すので、MOD を足して直す（[引き算の後の負の数を 0 以上に直す](#negative) の練習）
  - 裏付け：https://kazun-kyopro.hatenablog.com/entry/ABC/266/B ・ https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc266-b.html （どちらも付録 B のドメイン。記事の本文はまだ読んでおらず、検索結果の要約で問いを確かめただけ）
  - 役割の案：practice（例題 abc275_b より易しいが、負の数の直しだけを問う最小の問題なので、練習の先頭に置く）

## 未解決の点

- 「近年は畳み込みを使わない問題でも 998244353 が使われる」は傾向の記述で、数えて確かめてはいない（近年の ABC の経験則）。気になるなら検証役に削るか確かめるかを任せたい
- 動く図は作っていない（visual は static・priority 2 なので不要と判断した）
