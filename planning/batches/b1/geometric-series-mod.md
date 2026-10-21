# geometric-series-mod の報告と提案

- 書いたファイル：docs/math/geometric-series-mod.md、snippets/geometric-series-mod/{formula,halving,repeat}.{cpp,yaml}、docs/img/geometric-series-mod/halving.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。節 `{title: 行列累乗・ダブリング・位数へのつながり, anchor: next-steps}` を sections に足した
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check で本ページの直すべき行 0（digit-and-mod.md の 6 行は別の執筆者の作業中のページ）／check_snippets 3 本とも一致／textlint エラー 0、警告 13（数式を含む文の長さと、数式の前後の助詞「で」「に」「が」の重なり。誤検出か、言い換えると不自然になるもの）
- 使った出典：drken（abc357_d・abc129_f）、kazun-kyopro（abc293_e）、GitHub E869120/math-algorithm-book（math_and_algorithm_as）、ACL document_ja/modint.md（ローカルの v1.6 で確認）。新しいドメインはない
- 確かめた事実：998244353 で 10 の位数は p − 1（Python で計算。d ≤ 19 で 10^d ≢ 1）。10^9+7 でも d ≤ 18 で 10^d ≢ 1。ACL v1.6 の static_modint::inv は prime のとき assert(_v)

## 台帳への提案

- abc357_d の evidence の記事（drken）のコードは r ≡ 1 の分岐を持たないが、998244353 では起きないので問題なし。台帳の変更は不要
- 変更の提案はなし

## 用語集への提案

- 位数｜multiplicative-order｜a^k ≡ 1 (mod m) となる最小の正の整数 k。gcd(a, m) = 1 のときだけ存在する。（本文では括弧で定義したのでリンクは張っていない。multiplicative-order のページがあるならそちらへのリンクでよい）

## 手引きへの提案

- §13 に「基礎のページで、上位の帯の節（水・青）が sections にあるとき、§4 の基礎の構成（応用の型 → 落とし穴 → つながり → 問題）のどこに置くか」の目安があるとよい。本ページは公式 → 水の節 → 青の節 → 応用の型（同じ数字列）→ 落とし穴 → つながり → 確認問題 → 使い分け → 問題 の順にした
- 「つながり」の節を sections に載せるかどうか（中身の節として載せた）を決めておくとよい

## 問題の補充の候補

- 現状で例題 1・練習 2・力試し 1 で、手引きの数の目安の範囲内なので探していない
- abc319 以降の問題が無い（基礎のページなので必須ではない）。必要なら次のバッチで「法が入力の等比数列の和」「同じ数字列を並べた数」の形を ap.py と第三者の解説で探す

## 未解決の点

- 練習の abc293_e の方針で「M = 1 のとき答えが 0」と書いた。制約 1 ≤ M は kazun 氏の記事の制約の記載による（問題ページは開いていない）
- 図 halving.svg はブラウザで描画を確かめていない（変換の道具がなかった）。文字のはみ出しがないかメインかレビューで確認してほしい
- ACL の modint の割り算で逆元がないとき「assert で止まる」と書いた。AtCoder の提出で NDEBUG が定義されていれば止まらない可能性があるので、表現を「制約の違反」に寄せた
