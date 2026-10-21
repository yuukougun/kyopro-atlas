# reflection-principle の報告（b3）

- 書いたファイル：docs/comb/reflection-principle.md、snippets/reflection-principle/below-line.{cpp,yaml}、snippets/reflection-principle/two-sided.{cpp,yaml}、docs/img/reflection-principle/reflection.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 期待と違う0、textlint エラー0・警告10（助詞の重なり・数式を含む文の長さ・読点の数、台帳の要約の行と参考の題名の長さ。誤検出か軽微なので残した）
- 図：reflection.svg を render_svg.py で 360px・720px の PNG にして目で確かめた。visual は priority 2（dynamic）だが、指示に従い動く図は作らず静的な SVG で代えた
- 使った出典：drken（abc205_e、例題）、kmjp（abc309_h、力試し）、kmjp（arc145_c、補充の候補）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc309_h | summary | N 行 M 列のグリッドで、1 行目にある K 個の駒それぞれを、1 行下の左下・真下・右下のマスへ外に出ずに動かして N 行目へ進めるとき、駒と N 行目の L 個の指定マスのすべての組についての経路の数の総和を求める。 | https://kmjp.hatenablog.jp/entry/2023/07/08/1030 （本文の行は fix_problems が要約を残して埋めた） |

## 用語集への提案

なし（全単射 #bijection・正しい括弧列 #balanced-parentheses は既存の語にリンクした）。

## 手引きへの提案

- §5 comb に「鏡像法は、折り返す線を『触れたら違反の線』にし、終点・始点が条件を破る場合を先に 0 で返す」を足すと、二項係数の差の式を使うほかのページ（ballot 型の数え上げ）でも同じ誤りを防げる

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| arc145_c（Split and Maximize、diff 1697） | 1〜2N の順列を順序を保って 2 つの長さ N の列に分けたときの内積の最大値を得点とし、得点が最大になる順列の個数を求める。最大値を作る組の並び方が括弧列に対応し、カタラン数 × N! × 2^N になる | 練習（catalan の節の「応用の型」：ペアの並べ方がカタラン数） | https://kmjp.hatenablog.jp/entry/2023/09/21/1000 |

- kmjp の「鏡像」の検索で見つかった arc202_d（diff 3116）・arc147_f（diff 4016）は難しすぎるので候補にしない。drken の「カタラン数」カテゴリの kupc2020_m は difficulty がなく、内容を確かめていない
- ABC で鏡像法を直接使う新しい問題（abc319 以降）は見つからなかった。練習が 0 問のままなので、arc145_c の追加を勧める

## 未解決の点

- abc309_h の制約の具体的な値（N の上限）は第三者の解説から読み取れなかったので、本文では「繰り返し二乗法で O(M log M log N)」とだけ書き、数値は書いていない
- abc205_e の法：drken の記事では 10^9+7。本文は「法は問題の指定に合わせる」とし、数値は書いていない
- 練習問題の節は、確認済みの問題がないので置いていない
- ほかのページから stub のこのページへのリンク（handoff §1 の 5 か所：binomial-precompute:94・lattice-paths:91・lattice-paths:175・bracket-sequence:79・bracket-sequence:120、counting-bijection:111・124）は、節へ張り替えられる。案：括弧列・表の大きさ → #catalan、境界線を越えない経路・途中で負にならない → #reflection か #complement-count

## 検証の指摘への対応（b3）

- 指摘 1〜6 はすべて直した（vs-dp の「1 歩で 2 以上動く」の理由、確認問題 1 を (4, 3)・答え 14 に、「線 ℓ 上の点」、abc205_e の法 10^9+7 と modint の書き換え、代替テキストの「破線」、応用の型に席とペアの具体例）
- 指摘 6 の「練習に arc145_c を足す」は、台帳への追加が要るので本文には置いていない。上の「問題の補充の候補」の提案のとおり、メインが台帳に足したら catalan の節の練習に置くとよい
- 台帳への追加の提案：abc205_e・abc309_h・arc145_c の checked に 2026-10-21（検証で実在・内容を確認済み）
- 検査：check_pages エラー0・警告0、fix_problems 直すべき行0、check_snippets 期待と違う0、textlint エラー0・警告10（前と同じ種類）
