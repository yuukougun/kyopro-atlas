# convolution-ntt の報告と提案（b2）

- 書いたファイル：docs/math/convolution-ntt.md、snippets/convolution-ntt/{sum-pairs,triplets,mod-any,hamming,wildcard}.{cpp,yaml}、docs/img/convolution-ntt/{anti-diagonal,reverse}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages はエラー 0・警告 0、fix_problems --check は 0、check_snippets は 5 本とも一致、textlint はエラー 0（警告 18。数式を含む文の長さ・図の代替テキストの長さ・「で」「は」の重なりの誤検出）。SVG 2 枚は render_svg で 360px・720px を目で確かめた
- 動く図：置き場だけ書いた。`<div class="kp-viz" data-viz="convolution-naive" data-config='{"a": [1, 2, 3], "b": [4, 5, 6]}'>`。仕様：b を反転して a の下に置き、ずらし幅 k = 0..N+M−2 を 1 段ずつ進める。各段で重なったマスを強調し、積と和 c_k を caption に出す（c = 4, 13, 28, 27, 18）。前後の文章は sum-pairs 節にある

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc471_g | summary | 母音か子音に分かれた K 種類の文字からなる長さ N の文字列について、すべての文字を同じ幅だけ巡回にずらしたときの音節の数を、すべてのずらし幅ごとに求める。 | https://kmjp.hatenablog.jp/entry/2026/08/16/0900 |
| abc471_g | approach | 音節の数を「先頭が母音か」と「子音の直後に母音が来る箇所の数」に分け、隣り合う文字の差ごとに巡回の畳み込みで全ずらし幅への寄与を求める | 同上 |
| abc471_g | evidence | 上の kmjp の記事を足す（ikatakos の記録は 2026-10-21 の取得で 2 回とも HTTP 503 だった） | 同上 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| ハミング距離 | hamming-distance | 長さの等しい 2 つの文字列（列）で、同じ位置の文字が食い違う位置の数。 |
| 指示関数 | indicator-function | 集合 S に対し、v が S に入れば 1、入らなければ 0 を返す関数。列として持つと、集合を 0/1 の列で表せる（既存の indicator は確率の「指示確率変数」なので別に立てるか、そこに一文足す）。 |

本文では、ハミング距離は用語集にリンクせず括弧で定義した（check_pages が用語集にない anchor をエラーにするため）。足したらリンクを張れる。

## 手引きへの提案

- §13-5 は「用語集へのリンクは、まだなくても書いてよい」だが、check_pages は用語集にない anchor をエラーにする。どちらに合わせるかを決めてほしい（今回はリンクを外した）
- 付録 A に「ハミング距離」「ワイルドカード」「指示関数」を足す案

## catalog・front matter・ほかのページへの提案

- crt の Garner 節（crt:136）は「任意 mod の畳み込み」として convolution-ntt にリンクしている。節 `#convolution-ll` に張り替えられる
- mod-arithmetic:139・modint:136 のリンクは `#acl` に、rolling-hash:215 は `#string-matching` に張り替えられる
- acl-reading:116 の行も `#acl` が合う見込み（行の中身は見ていない）
- multiplicative-order（stub）に「NTT に向く素数と 2^c 乗根」の節があれば、本文 #acl からその節へ張り替える。fft-ntt の節 ntt-prime もある
- 使い分けの表（早見表）に「和・差の分布を値の範囲 10^6 程度まで → 畳み込み」「添字の XOR → アダマール変換」「添字の OR・AND → 部分集合のゼータ変換」を足す案

## 問題の補充の候補

例題 2・練習 4・力試し 1 で、手引きの目安の範囲に収まっているので、今回は新しい候補を探していない。ワイルドカードの照合の例は ABC の確認済みの問題がない（Library Checker の wildcard_pattern_matching は verify にある）。

## 未解決の点

- abc471_g の問いは kmjp の記事から組み立てた。記事は「音節の数」が先頭の母音と子音→母音の箇所で決まると整理しているが、音節の定義そのもの（問題文での定め方）は確かめていない。台帳の summary を確定する前に、別の第三者の解説（ikatakos の記録が復旧したら解法の部分）でもう一度確かめたい。制約（N・K の上限）も確かめていない
- ABC143 D の畳み込みの別解（全体から「最長の辺 ≥ ほかの 2 辺の和」の組を引く）は、自分で組み立てたもので、記事の裏付けはない（drken の記事で問いと制約を確かめた。正しさは本文の方針に書いた理由で確かめた）
- 計測の数値（長さ 5×10^5 どうしで約 55 ms・約 180 ms）は手元の g++-15 -O2 の 1 回の計測で、AtCoder の環境の値ではない
- AtCoder の環境で `assert` が有効か（NDEBUG が定義されていないか）は確かめていない。本文は「assert で実行時エラーになる」と書いた

## 使った出典と domain

- github.com（ACL の document_ja と convolution.hpp は手元の v1.6 で確かめた。E869120 の 065-03.cpp）
- drken1215.hatenablog.com（practice2_f・abc143_d）、merom686.hatenablog.com（abc392_g）、kmjp.hatenablog.jp（abc291_g・abc196_f・abc471_g）：どれも付録 B にある
- ikatakos.com：abc471 の記録は 503 で読めなかった
- judge.yosupo.jp：問題文が JS で描かれ取得できなかったので、本文では詳細に触れていない
- 新しく noai を確かめたドメインはない

## 使用量の目安

道具の呼び出し 約 40 回、Web 取得 9 回（失敗 3）、Web 検索 1 回。

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜9 はすべて直した（採らなかったものはない）。指摘 3 は「値を掛けるだけで $O(N)$」も $O(N + M)$ に直した。指摘 6 は環境を書き添え、比（約 3〜4 倍）だけにした。指摘 8 は anti-diagonal の k の印を 14px・列見出しを 6 上げ・凡例の 1 項を「c₀ = 4」「c₄ = 18」に、reverse の添字の印を 14px（「0 (j=2)」と半角の括弧にして隣と重ならないようにした）・右の説明を 14px にした。render_svg の 720px で確かめた
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 5 本とも一致、textlint エラー 0（警告 19。増えた 1 は数式を含む文の長さ）
- 台帳の checked の提案（検証役から）：practice2_f・abc392_g・abc143_d・abc291_g・abc196_f・typical90_bm に 2026-10-21。abc471_g は第三者の解説がもう 1 件で確かめられるまで保留
