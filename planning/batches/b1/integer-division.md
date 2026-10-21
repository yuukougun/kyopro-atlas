# integer-division の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/integer-division.md、snippets/integer-division/{division,multiples,overflow,double-ng}.{cpp,yaml}、docs/img/integer-division/floor-ceil.svg
- front matter で変えたもの：complexity（どれも O(1)（lcm は gcd の O(log min(a, b)) を含む））・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 周期・mod・floor sum・商の列挙へのつながり, anchor: next-steps}` を足した（基礎の目安の「上位の手法とのつながり」）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 件すべて一致）、textlint（エラー 0・警告 22）
  - 残した警告：no-doubled-joshi（数式・コードを挟んだ「に」「で」「と」の重なり）、sentence-length（問題の行・方針の折りたたみの中の数式を含む文）、no-unmatched-pair 2 件（半開区間 $[0, X)$ と見出しの [L, R] を括弧の対と誤検出）
- 動く図：作っていない（catalog の visual は static・priority 2）。静的な SVG を 1 枚描いた
- 使った出典：台帳の evidence（qiita nagi0724・zenn fjnkt98・drken のはてなブログ 6 本・E869120 の GitHub）、zenn asamichiruko（abc432_c の問いの向き）、en.cppreference.com（整数の / が 0 の向きに切り捨てること）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメイン：ryo-manba.hatenablog.com・fkgtinfo.com（どちらも指定なし。本文では使っていない。候補の裏付けにだけ使う）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc432_c | summary | 2 種類の飴（値 X と Y、X < Y）を各人に決まった個数ずつ配り、全員の合計をそろえるとき、Y の飴の個数の合計の最大値を求める（できなければ -1 を出力する）。 | https://zenn.dev/asamichiruko/articles/feecf5ef8874fb |
| abc432_c | approach | 各人の Y の個数は合計 P から (P − X A_i)/(Y − X) で決まる。X A_i mod (Y − X) が全員で等しいことが要り、P は最大の Y min A を取る（それが X max A 以上か確かめる） | 同上・https://drken1215.hatenablog.com/entry/2025/11/16/160322 |
| abc432_c | evidence | zenn asamichiruko の URL を足す | 下の「未解決の点」 |

- abc432_c の本文の行は、上の summary の案で書いた。台帳を直したら fix_problems で行がそろう
- ほかの問題（abc239_b・abc131_c・abc165_d・abc048_b・abc084_c・typical90_al）の summary と approach は evidence の解説と食い違いがなかった
- abc432_c の catalog の approach「切り上げの割り算で境界を求める」は、解説ではどれも余りの一致と合計の範囲で解いており、切り上げは使っていない。catalog は凍結なので、台帳の approach の直しだけを提案する

## 用語集への提案

なし（本文では用語集へリンクしていない。床関数・天井関数は記法として冒頭で定義した）

## 手引きへの提案

- 基礎の technique の目安の「上位の手法とのつながり」に定型の見出しがない。binary-search の報告と同じ点。今回は sections に `next-steps` として足した（binary-search-answer の見本も next-steps を使っている）。定型にするなら `## …へのつながり {#next-steps}` にそろえるとよい

## 問題の補充の候補

- abc345_b（B. Integer Division Returns、diff 91、ap.py で実在を確認）：$-10^{18} \le X \le 10^{18}$ の整数 X について ⌈X/10⌉ を求める。例題の abc239_b と対になる切り上げの版で、`(X + 9) / 10` が負の X で誤ることを確かめる練習になる。裏付け：https://fkgtinfo.com/2024/03/17/abc345/ （問いと制約）、https://zenn.dev/yamasakit/articles/b40cc269f80b1b （切り上げの式。ただし Python の // なので負の数は自動で正しい）
- typical90_t（020. Log Inequality（★3）、ap.py で実在を確認）：$\log_2 a < b \log_2 c$ を判定する。整数の $a < c^b$ に直して誤差を避ける（[double で割らない](#no-double)の節の練習）。裏付け：https://github.com/E869120/kyopro_educational_90/blob/main/sol/020.cpp （research/06 で確認済み）、https://ryo-manba.hatenablog.com/entry/2021/08/25/225307
- abc319 以降の問題は、基礎のページの要件でないため探していない（練習のうち abc432_c が 2025 年）

## 未解決の点

- abc432_c：台帳の evidence の drken の記事は、問題概要で「大きい飴の購入個数の総和の最小値」と書き、解法では総和が最大になる P を選んでいる。zenn asamichiruko と note の解説（検索結果）は「最大値」なので、本文は最大値で書いた。問題文の向きは検証役かメインで確かめてほしい（atcoder.jp は開けないため）
- 飴の X・Y を「値段」とする解説（drken）と「重さ」とする解説（zenn）があり、本文の要約では「値」とぼかした
- 図 floor-ceil.svg は描画して目で確かめる道具がなく、座標の計算だけで文字の重なりを避けた。表示の確認を検証役に頼みたい
- `double` の仮数部 53 bit・`__int128` の上限約 $1.7 \times 10^{38}$ は一般の事実として書いた。double-ng.cpp で $10^{18} - 1$ の割り算が 1 ずれることは実行して確かめた
- 例題の方針・解法の詳細はコードを載せず floor_div を呼ぶ形にした（例題用の snippets は作っていない）
- 使用量の目安：道具の呼び出し約 40 回、Web 取得 13 回・検索 3 回
