# reverse-thinking（執筆の報告）

- 書いたファイル：docs/thinking/reverse-thinking.md、snippets/reverse-thinking/multiples-parity.{cpp,yaml}、docs/img/reverse-thinking/reverse-deletion.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（期待と違う0）、textlint（エラー0、警告8。どれも同じ助詞の重複 no-doubled-joshi で、文意を保つため残した）
- 使った出典：drken（agc032_a・abc134_d・arc065_a・abc120_d）、comet725（abc477_d）、ikatakos（abc477_d・abc466_f。解説の部分だけを読むよう指示して取得）。新しいドメインはなし
- 図：visual は priority 2・static なので、削除と逆順の追加を並べた静的な SVG を 1 枚作った（動く図は作っていない）。環境に SVG の描画ツールがなく、見た目は目で確かめていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc477_d | summary | マスにマスキングテープを貼る（貼ってあればはがす）操作と、テープのないすべてのマスを指定の文字で塗る操作を順に行った後の、各マスの文字を求める。 | https://qiita.com/comet725/items/a3fca15e86349dadf4b2 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0926_abc477 |
| abc477_d | approach | 最後の塗りだけが効くので、クエリを逆順に処理して各マスを最初に当たった塗りで確定させる | 同上 |
| abc466_f | summary | 数列 A の先頭から順に余りを取っていくと 0 になる、1 以上 X 以下の整数の個数を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0711_abc466 |
| abc466_f | approach | 0 になる値の集合を最後の剰余から逆に組み立て、長さ X+1 の棒を A_i で順に切る問題に見直して、同じ長さの棒をまとめる | 同上 |
| abc120_d | summary | 本文の行は台帳どおり（「不便さ」を含む形）になっている。catalog の短い形と食い違うが、どちらでもよい | — |

## 用語集への提案

- なし（固定点 `fixed-point` は既存。オフラインはページ ds/offline-queries#reverse-time へリンクした）

## 手引きへの提案

- thinking のページでは、ほかのページが持ち主の例題（abc137_d など）に触れたくなることが多い。§2.5 の「本文で触れるときは例題の見出しかページへリンクする」に、「ほかのページの例題の小見出し `../<field>/<id>.md#<問題ID>` へリンクしてよい」と明記するとよい（本ページでは greedy-priority-queue#abc137_d にリンクした）

## 問題の補充の候補

- なし。台帳の確認済み 6 問（例題 3・練習 2・力試し 1）で、目安（thinking の例題 2〜4・練習 2〜6）を満たす。締め切りの節の代表 abc137_d は greedy-priority-queue の例題なので、本文からその小見出しへリンクした。練習に加えるなら abc137_d を practice としてこのページにも載せる案がある（台帳の pages に {reverse-thinking, practice} を足す。根拠 https://drken1215.hatenablog.com/entry/2020/12/29/195900）

## 未解決の点

- abc477_d の問題の細部（初期の文字が a であること、操作の種類の番号）は第三者の解説から読み取ったもので、本文の要約ではその細部を書いていない
- abc466_f の方針は ikatakos 氏の解説だけで裏付けた。2 つ目の解説があれば確かめたい
- SVG の見た目（矢印とラベルの重なり）は描画して確かめていない。検証役に確かめてほしい

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜4：すべて直した（塗る操作の計算量を「全体を塗る」と「区間を塗る」に分けた／トポロジカル順の括弧を「この矢印の向きでの順そのもの」に／確認問題の見出しを「固定点が 2 つあるとき」に／条件 $i$ に $x_i$ 自身も出ることを明記）
    - 指摘 3 で示された別案 (1, 3, 2) は、取り除いた後の (3, 2) で位置 2 が固定点になるので、検証の説明とは途中が異なる（最後は (3) で固定点がなくなり作れない）。見出しを変える案を採った
- 指摘 5 (b)：逆向きの集合から棒の見方へ移る理由を 2 文足した
- 指摘 5 (a)：ikatakos.com は再取得でも HTTP 503 で、abc466_f の問題の要約は一次資料で確かめられていない。本文はそのまま
    - **提案（メイン向け）**：abc466_f の台帳の summary・approach は、2 つ目の解説（付録 B のドメイン）か ikatakos の再取得で確かめてから反映する。abc477_d は comet725 の記事を evidence に足して反映してよい（検証役の確認による）。agc032_a・abc134_d・arc065_a・abc120_d に `checked: 2026-10-21` を入れてよい
