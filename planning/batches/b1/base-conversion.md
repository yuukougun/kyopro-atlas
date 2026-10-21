# base-conversion の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/base-conversion.md、snippets/base-conversion/{convert,bijective26,negabinary,base-n}.{cpp,yaml}、docs/img/base-conversion/ladder.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 4 片とも一致。textlint エラー 0・警告 12（a, b, …, z の列挙の読点、台帳の summary の行、数式を含む文の長さ・助詞の重なりで、誤検出か台帳由来）。fix_problems --check は本ページに指摘なし（comb/probability-dp.md の 8 行が未整形で終了コード 1。担当外なので触れていない）
- 使った出典：drken（abc171_c・abc186_c・abc105_c）、E869120 の典型90 067 の解答コード（GitHub）、ikatakos の ABC192 メモ（D の解説部分だけ）、zenn.dev（問題の補充の候補の裏付け）。新しいドメインはない
- 動く図：catalog の visual は static・priority 2 なので、静的な SVG（23 を 3 進にする割り算のはしごと Horner 法の復元）で代えた

## 台帳への提案

- 変更なし。5 問とも summary・approach・evidence は本文の内容と食い違わないことを確かめた
- abc192_d の evidence の ikatakos のメモはオーバーフローに触れていない（Python の多倍長で済ませている）。approach の「オーバーフローに注意」は C++ での実装上の注意として本文に書いた。必要なら evidence に C++ の解説を足す

## 用語集への提案

- なし（Horner 法はページ内で定義した。用語集に入れるなら：Horner 法｜horner-method｜多項式や b 進表記の値を、上の係数から v ← v·x + c を繰り返して累乗を作らずに計算する方法）

## 手引きへの提案

- なし

## 問題の補充の候補

- abc414_c（ABC414 C. Palindromic in Both Bases、diff 709）：N 以下で 10 進でも A 進でも回文になる整数の総和を求める（N ≤ 10^12）。10 進の回文を前半から生成し、各候補を A 進に変換して回文か判定する。abc319 以降の練習として。裏付け：https://zenn.dev/testcampus/articles/72d76d6366df7d
- abc220_b（ABC220 B. Base K、diff 58）：K 進で書かれた 2 数を 10 進に直して積を求める型と思われる（題名だけ ap.py で確認。第三者の解説は未確認）
- arc164_a（ARC164 A. Ternary Decomposition、diff 532）：3 進表記の桁和と分解の個数の関係を使う型と思われる（ap.py で実在のみ確認。解説は未確認）

## 未解決の点

- 確認問題「28 番目の名前」の答え ab は手計算と snippets の関数の考え方で確かめた（snippets のケースには入れていない）
- 確認問題の桁数（3^37 = 450283905890997363 ≤ 10^18 < 3^38、2^59 ≤ 10^18 < 2^60）は Python で確かめた

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：オーバーフローの式の小文字 $m$ を $M$ に直し、各桁の数字を $c$（$0 \le c \le M$）にして最大の数字 $d$ と分けた
- 指摘 2：番兵の段落に、$n = d$ は判定されないので $f(d) \le M$ でなくてよいこと、満たす $n$ がなければ答えが 0 になることを足した
- 指摘 3：「`/` は 0 方向へ切り捨て、`%` はそれに合わせて割られる数と同じ符号」に直した
- 指摘 4：ladder.svg の位の注記を上付きの tspan（3⁰ の形）にし、注記と最下段の説明の font-size を 13 から 15 に上げた（横幅 520 はそのまま。最下段は x=20 に寄せた）
- 指摘 5：単調性の段落の最後に「$n$ の個数がそのまま値の種類数になる」を足した
- 採らなかったものはない。台帳への提案（abc171_c・abc186_c・typical90_bo・abc105_c の `checked: '2026-10-21'`）は検証の報告のとおりメインに委ねる
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 4 片一致、textlint エラー 0・警告 11
