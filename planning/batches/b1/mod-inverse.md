# mod-inverse（逆元と mod での割り算）の報告

- 書いたファイル：docs/math/mod-inverse.md、snippets/mod-inverse/{inverse,inv-table,half-sum,acl}.{cpp,yaml}、docs/img/mod-inverse/mult-table.svg
- front matter で変えたもの：complexity（逆元 1 つ O(log m)、1〜N の逆元の表 O(N)）・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 4 片とも期待どおり／textlint エラー 0、警告 20（助詞の重複・読点の数・文の長さ。どれも数式を含む文や定理の説明で、§13-8 の誤検出の範囲）／fix_problems --check は本ページで 0（残る 6 行は digit-and-mod.md のもので、本ページとは無関係）
- 動く図は作っていない。visual は priority 2・static なので静的な SVG（mod 7 と mod 6 の掛け算の表）にした

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc186_e | summary（と alternatives の summary） | 「1回に」→「1 回に」（半角数字と全角文字の間の空白。textlint のエラーになる） | 表記の規則（手引き §7） |

本文の行はすでに「1 回に」に直してある。台帳を直したら fix_problems で本文と食い違わないことを確かめてほしい。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 互いに素 | coprime | 2 つの整数の最大公約数が 1 であること。$a$ と $m$ が互いに素なら、$a$ は法 $m$ で逆元をもつ |
| 逆元（mod の） | modular-inverse | $a x \equiv 1 \pmod{m}$ となる $x$。$\gcd(a, m) = 1$ のときだけ存在し、法 $m$ でただ 1 つに決まる。mod での割り算は逆元を掛けて行う（ページは math/mod-inverse。本文では用語集にリンクしていない） |

本文から用語集へのリンクは coprime の 1 つだけ（既存のページも同じ anchor を使っている）。

## 手引きへの提案

- §13-7 は「台帳の summary が規則に合わないとき本文だけ直さない」としているが、台帳の summary が textlint のエラー（空白の規則）になる場合は本文のエラー 0 と両立しない。今回は本文の要約だけを直して提案に回した。「textlint のエラーになる表記の違いだけは本文を先に直してよい（fix_problems は要約を変えない）」と明記するとよい

## 問題の補充の候補

- 足りているので新しい候補は探していない（例題 1：typical90_cd、練習 3：math_and_algorithm_as・abc357_d・abc186_e）
- 参考：frequency_evidence に挙がっている abc468_e（E. Sum of Average、diff 1038、ap.py で実在を確認）は台帳では contribution の練習で、summary が「（執筆時に確かめる）」のまま。本ページには載せていない。平均（割り算）を mod で求める問題なら本ページの練習にも向くが、問いを第三者の解説で確かめていない

## 未解決の点

- SVG を描画して目で確かめる道具（rsvg-convert・cairosvg）が手元になく、配置は座標の計算だけで決めた（幅 600・高さ 350。文字のはみ出しがないかを一度目で確かめてほしい）
- abc357_d の公比 $10^d$（$1 \le d \le 19$）が法 998244353 で 1 にならないことは python で確かめ、確認問題の答えにした。drken の解説にはこの点の記述はない
- 例題 typical90_cd の内容は作問者の解答コード（E869120/kyopro_educational_90 sol/082a.cpp）で確かめた。ABC357 D・ABC186 E は drken の解説、アルゴ数学 053 は math-algorithm-book の解答コードで方針を確かめた
- 新しく noai を確かめたドメインはない（qiita.com・drken1215.hatenablog.com・github.com はどれも付録 B にある）

## 使用量の目安

- 道具の呼び出し 約 35 回、Web 取得 7 回（WebFetch 6、curl でタイトルの確認 4 件）
