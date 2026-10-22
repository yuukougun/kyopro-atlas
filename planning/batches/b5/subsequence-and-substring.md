# subsequence-and-substring の提案（b5）

- 書いたファイル：docs/patterns/subsequence-and-substring.md、docs/img/subsequence-and-substring/two-ways.svg（コード片なし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を properties の後に足した（見本 bracket-sequence と同じ形）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0・警告 11（数式の半開区間 `[l, r)` による括弧の対応の誤検出、数式やリンクを含む文の長さ、問題の囲みの要約の助詞「で」の重複、方針の折りたたみの「b」の誤検出）
- 図：two-ways.svg（幅 400）を render_svg で 360・720 にして目で確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
|---|---|---|---|
| abc456_d | summary | a・b・c からなる文字列 S の空でない部分列（位置の選び方）のうち、同じ文字が隣り合わないものの個数を 998244353 で割った余りで求める。 | https://zenn.dev/iwamutsu/articles/trvmolry2fo0il 、https://qiita.com/comet725/items/96ce9b1e24f522c6e86f |
| abc456_d | evidence | 既存に https://zenn.dev/iwamutsu/articles/trvmolry2fo0il を足す（2 つ目の裏付け） | 同上 |
| abc456_d | approach | 末尾の文字が a・b・c の部分列の数を持ち、S[i] の文字の値に、ほかの 2 文字で終わる数の和と 1 を足す DP | 同上 |

本文の行は自分の要約で書いた（§14-16）。

## 用語集への提案

なし（部分列は `subsequence` がある。部分文字列の項目はないが、本文で定義した。足すなら：部分文字列｜substring｜文字列の連続する範囲 $S[l, r)$ の文字を並べた文字列。部分列と違い、位置を飛ばせない）

## 手引きへの提案

- pattern のページの sections に、見本 bracket-sequence と同じく `overview`（問われ方と手法の一覧）を骨格の段階から入れておくとよい（今回は執筆者が足した）

## front matter・catalog への提案

- 節 count-occurrences の title の「（dp-state-design）」は、中身の持ち主が dp-phase#matched-prefix なので「（dp-phase）」が正確。anchor は変えず、title だけ直すかをメインが判断する（本文は両方へリンクした）
- related に fix-variable（3 つ組で真ん中を固定）と kmp（パターン照合）を足してもよい（本文でリンクした：thinking/fix-variable#fix-middle、string/kmp#matching）

## 問題の補充の候補

- 確認済みの問題は例題 1・練習 1 で、patterns の目安（例題 0〜1、練習 0〜3）の範囲内。表のほかの行の代表は行き先のページの例題に任せた（problems_note のとおり）ので、補充は必須ではない
- 補うなら、異なる部分列の数（subsequence-dp の例題 ABC214 F）・異なる部分文字列の数（suffix-array の PRACTICE2 I）は各ページの例題なので、このページには練習としても重ねないのがよいと判断した

## 未解決の点

- docs/patterns/interval.md は front matter が draft だが、執筆時点で見出しがなかった（並行で執筆中とみられる）。subarrays の節からはページへのリンク（anchor なし）にした。interval の見出しができたら `#overview` へ張り替えてよい
- 使った出典のドメインはすべて付録 B 内（qiita.com・zenn.dev）。新しく noai を確かめたドメインはない

## 検証の指摘への対応

- 直した：1（(a) を採り、本文の例を「`b` の直後に `a` を置かない」に変え、練習への言及を消した。練習は残すので台帳の提案は変えない）、2、3、4、5（枠を y=190・高さ 50 に下げ、番号の下から始めた）、6、7、8（`## 確認問題 {#quiz}` を参考の前に立てて移した。sections には載せない）、10（`interval.md#overview` に張り替え）
- 採らなかった：9（front matter の title はメインの判断。上の「front matter・catalog への提案」の 1 つ目のとおり、title を「（dp-phase）」にするのを提案する）
- 指摘 2 の言い回し「直前に取った位置より右で最も左」は、subsequence-dp の要点・counting-dedup#leftmost の言い回しと揃えるかをメインが判断する（提案）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0（警告 11 は執筆時と同じ種類）。図は render_svg で 720px を目で確かめた
