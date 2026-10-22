# stress-testing の報告と提案（b5）

- 書いたファイル：docs/guide/stress-testing.md、snippets/stress-testing/{compare-random,exhaustive,generators,experiment}.{cpp,yaml}
- front matter で変えたもの：stage（draft）・updated（2026-10-22）。complexity は guide なので null のまま（debugging-checklist などほかの guide にそろえた）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 片・期待と違う 0、textlint エラー 0・警告 6（Mermaid の中の「本解を実行」の冗長表現、$[l, r)$ の括弧の対応、数式の中の読点の数。どれも誤検出）
- 図：catalog の visual（priority 2、static）どおり、生成器 → 本解・愚直解 → 比較のループを Mermaid で書いた（procedure の節）。SVG は描いていない
- 問題：catalog の problems が空なので、本文に問題は載せていない（下の「問題の補充の候補」を参照）
- 新しく noai を確かめたドメイン（どれも指定なし。2026-10-22）：kmyk.github.io・oeis.org・raw.githubusercontent.com（参考には github.com の URL を書いた）

## 台帳への提案

- なし（本文に問題を載せていない）。補充するなら下の候補を参照

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 全数テスト | exhaustive-testing | 小さい範囲の入力をすべて試して、本解と愚直解の答えを比べるテストである。短い順・辞書順に試せば、最初に見つかる反例が最小の反例になる。 |
| チェッカー | checker | 出力が問題の条件を満たすかを確かめるプログラムである。答えが複数ある問題や誤差が許される問題で、出力を文字列として比べられないときに使う。 |
| コーナーケース | corner-case | 見落としやすい端の入力（$N = 1$、すべて同じ値、値の上限ちょうど、答えがない場合など）である。debugging-checklist#wa が本文で定義している語で、本ページでも使っている。 |

- 用語集の「愚直解」「反例」の定義は stress-testing.md へのリンクを持つ。相手が draft になったので、節へのリンク（愚直解 → `stress-testing.md#procedure`、反例 → `stress-testing.md#procedure`）に張り替えてよい

## 手引きへの提案

- guide の要点の囲み：debugging-checklist と同じく「何のページか・使い方」に加え、3 行目に「考察に使うなら」を置いた。guide の要点の項目は内容に合わせて変えてよい（§2.2）の範囲と考えたが、ほかの guide とそろえるなら項目名の約束を決めてほしい
- シェルのループ：research §6.7 の方針（スクリプト全体は載せず処理の流れだけ）に従い、3 つのプログラムを回す形は ```` ```text ```` の流れだけにした。`oj g/i --hack-actual …` の 1 行だけは ```` ```bash ```` で載せた（interactive#local-testing も bash を直接載せている）。bash の短いコマンドを本文に直接書いてよいかを手引き §2.7 に明記するとよい
- 乱数の種と同じ列：`mt19937_64` の値は規格で決まるが、`uniform_int_distribution` を通した値は標準ライブラリで変わりうる（cpp-math-functions#random と同じ注意）。snippets の期待（種 7 で 6 回目に止まる）は libstdc++（g++-15）での観測値で、本文にも「標準ライブラリが同じときに限る」と添えた

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

catalog の problems は空で、hub と同じく 0〜3 問が目安と考える。載せるなら実験の節（#experiment）の練習に次を提案する。どれも小さい値の表を作ると規則が見える問題で、第三者の解説が実際に表を作って規則を見つけている。

| 問題ID | 台帳 | 何を問うか | 役割の案 | 裏付け |
| --- | --- | --- | --- | --- |
| abc165_d（Floor Function、diff 600） | 確認済み（integer-division の練習） | $0 \le x \le N$ で $\lfloor Ax/B \rfloor - A \lfloor x/B \rfloor$ の最大。$x$ を動かした表から周期 $B$ と周期内の単調増加が見える | 練習（#experiment） | https://drken1215.hatenablog.com/entry/2020/05/02/225600 |
| abc121_d（XOR World、diff 1164） | 確認済み（bit-operations の練習） | $A$ 以上 $B$ 以下の整数の XOR。$0$ から $n$ までの XOR の表が 4 周期になる | 練習（#experiment） | https://drken1215.hatenablog.com/entry/2019/03/09/224100 |
| abc380_d（Strange Mirroring、diff 849） | 台帳にない（ap.py で実在と diff 849 を確認） | 大文字と小文字を入れ替えて連結する操作を繰り返した文字列の $K$ 文字目。何番目のブロックが反転しているかの表が、番号の 2 進表記の 1 の個数の偶奇で決まる | 練習（#experiment） | https://drken1215.hatenablog.com/entry/2024/11/17/030500 |

- abc380_d は台帳への追加が要る（evidence は上の 1 件。2 件目は未確認）

## 未解決の点

- thinking-checklist は stub なので、ページへのリンクだけにした（related の `thinking-checklist#q-small-cases` へは、相手が draft になったら節へ張り替える）
- cpp-environment が stub なので、MinGW の `random_device` の注意（betrue12 氏の 2019 年の記事）は本ページに短く書いた。現在の MinGW で再現するかは確かめていない
- ほかのページの「[ストレステスト](../guide/stress-testing.md)」へのリンク（greedy-basics:133・interval-scheduling:122・cpp-math-functions:248・cpp-undefined-behavior:272・proof-patterns:179・construction:154・fix-variable:139・counting-mindset:154・symmetry-pigeonhole-casework:87・127・interactive:190・grundy-number:163・binomial-identities:222・exchange-argument:103・debugging-checklist:190）は、節へ張り替えられる。目安：反例探し・ランダムテスト → `#procedure`、全探索との比較の組み方 → `#setups`、チェッカー（construction:154）→ `#caveats`、実験・OEIS（counting-mindset:154・symmetry-pigeonhole-casework・grundy-number:163・proof-patterns:179）→ `#experiment`、interactive:190 → `#interactive`

## 検証の指摘への対応（b5 verify）

- 1〜8 は直した（MinGW の版を GCC 9.2 より前に限り PR 85494 を参考に追加、`-t` なしでは TLE を探さないこと、kmyk 氏の例を 0・2 の冪に限定、betrue12 氏の行を「手順の 3 段階と見つかった反例の追い方」に、「本末転倒」「儲けもの」とファイルの段落を言い換え、確認問題 2 を $N = 1, \dots, 5$ に、#generators の指す先を明示、thinking-checklist を `#q-small-cases` へ）
- 9：本文は「端のケース」のままにした（「コーナーケース」へのそろえはメインの判断に任せる）。上の用語集への提案「コーナーケース」の理由は、debugging-checklist#wa が定義している語だから、だけに改める（「本ページでも使っている」は誤り）
