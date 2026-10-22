# b5 contest-strategy の報告

- 書いたファイル：docs/guide/contest-strategy.md、docs/img/contest-strategy/finish-times.svg（静的な図、visual priority 2 の帯グラフ）
- front matter で変えたもの：stage（draft）・updated（2026-10-22）。complexity は guide なので null のまま。sections は変えていない
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直す行 0（問題は載せていない）、textlint エラー 0・警告 9。警告はすべて助詞の重なり（no-doubled-joshi）と図の代替テキストの長さ。コード片はない
- 図：render_svg.py で 360px と 720px の幅で確かめた

## 数字の確かめ方

- 位置ごとの difficulty、解く確率と時間、解き終える時刻、半々以上で解ける問題の数、位置の逆転の回数は、tools/ap.py の Data（AtCoder Problems のキャッシュ）から手元で計算し直した（スクリプトは一時置き場の stats.py。リポジトリには入れていない）。research/00 §2.3.3・§2.3.5・§2.3.6 の値と一致した
- 例外が 1 つある：research/00 §2.3.6 の「解ける確率が 50% 以上の問題の数」の分布は、計算し直すと P = 1200 が 3 問 4%・4 問 69%・5 問 27%、P = 1600 が 4 問 11%・5 問 62%・6 問 27%、P = 2000 が 5 問 21%・6 問 73%・7 問 6% になった（調査の表は 68%・60%・20% で、3 問の行がない）。本文は計算し直した値を、3〜4 問・5 問・6〜7 問にまとめて載せた
- E869120 氏の目安・ABC148 の例、drken 氏の完答数の目安・同点の扱い、Wikipedia のペナルティ（5 分、正解した問題への誤答だけ）は、各記事で確かめた。drken 氏の記事にペナルティの分数は書かれていない（調査の §2.2.1 の出典表示に注意）
- 「10 分の遅れがパフォーマンス 160〜250」「誤答 1 回が 80〜130」は ABC148 の 1 回の例から割った粗い見積もりで、本文にもそう書いた

## 台帳への提案

- なし（catalog の problems が空で、hub と同じく問題は載せなかった）
- 本文では abc470 の E（2096）・F（1604）の逆転を、§13-6 に従い問題 ID を出さずに「2026 年のある回」と書いた。台帳に abc470_e・abc470_f はあるので、ID を出してよければメインの判断で直す

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| パフォーマンス | performance | 1 回のコンテストでの成績をレートと同じ物差しで表した値。順位から決まり、レートはパフォーマンスの重み付きの平均に近い値になる |
| ペナルティ | penalty | 正解した問題への誤答 1 回ごとに、最終の正解時刻に足される時間。主なコンテストでは 5 分で、得点が同じときの順位に効く |
| upsolve | upsolve | コンテストで解けなかった問題を、終了後に解説などを使って解き直すこと |
| 完答数 | solves | 1 回のコンテストで正解した問題の数。「4 完」は 4 問を正解したことを表す |

（パフォーマンス・difficulty は atcoder-system が持ち主になるはずなので、用語集の定義はそちらと合わせる）

## 手引きへの提案

- 横断の guide のページが「データから計算した数字」を載せるとき、計算のスクリプトを tools/ に置くか（再現できるように）を決めてほしい。今回は一時置き場に置いただけ
- AtCoder生成AI対策ルールの正式名は、全角文字と半角文字の間の空白の規則（ja-space-between-half-and-full-width）に引っかかる。固有名として prh.yml か .textlintrc の allows に足すと、各ページで textlint-disable を使わずに済む

## 問題の補充の候補

- なし（戦い方のページに問題は要らないと判断した）

## 未解決の点

- 生成 AI のルールの現行の版（20261014 版）の条文は atcoder.jp を開けないので確かめていない。本文は decisions.md の記録どおりの内容だけを書き、「教材のページを引くことがルールに触れるか」には触れなかった。how-to-use#ai-rule-version と atcoder-system#ai-rules と表現をそろえてほしい
- どの提出がペナルティに数えられるか（コンパイルエラーなど）は確かめられなかった。本文では「各コンテストのルールのページで確かめる」と書いた
- atcoder-system にも同じ anchor の節 difficulty-by-position・ai-rules があり、内容が重なる。こちらは「戦い方に使う数字」、atcoder-system は「定義と仕組み」と分けたつもりだが、atcoder-system の執筆者と表の値（中央値・割合）をそろえる必要がある。roadmap#recent-positions も同じ
- 相手のページ（atcoder-system・roadmap・thinking-checklist・debugging-checklist・stress-testing・practice-method・how-to-use・reverse-index-signs）が stub なので、§14-23 に従いページへのリンクにした。draft になったら次の節へ張り替えるとよい：debugging-checklist#before-submit、thinking-checklist#q-misreading ほか、stress-testing#procedure・#experiment、practice-method#upsolve・#when-to-read・#records、how-to-use#claude・#ai-rule-version、atcoder-system#levels・#ranking・#ai-rules、roadmap#recent-positions
- 「終了前の 10〜15 分」と「切り替えの時刻」の手順は、出典のない提案（調査 §6.5.2）で、本文にもそう書いた
- 新しく noai を確かめたドメイン：iroha-3856.hatenablog.com・kmyk.github.io（どちらも指定なし）。付録 B への追加を提案する

## 検証の指摘への対応（2026-10-22）

- 直したもの：1（頻度は 81 回の確率の平均で言い直し、表の確率は中央値の問題についての値だと一文を足した。黄の行は「F は 3 回に 2 回ほど、3 回に 1 回は落とす」に）、2（時刻は時間のモデルがある回だけの中央値で A〜E 78 回・A〜F 71 回と明記し、注意を 3 つ目として追加。表の分数の回数も明記。数え直すと G の時間のモデルは 49 回分で、指摘の約 46 回とは違ったので 49 回と書いた。図の注記も直した）、3、4（(1)(2) とも）、5、6、7（162 回の値で約 470・約 490 に）、9（図の「perf」を「P」に）
- 採らなかったもの
  - 8（difficulty-by-position の表と帯の割合を atcoder-system へのリンクに絞る）：atcoder-system は draft で、どちらを値の持ち主にするかはメインが決めることなので、今回は残した。メインへの提案：値の持ち主を atcoder-system#difficulty-by-position に決めるなら、この節は結論の 3〜4 文とリンクに縮める
  - 10（相手のページの節への張り替え）：相手のページがまだ draft なので §14-23 に従いページへのリンクのまま。張り替え先は上の「未解決の点」のとおり（メインの張り替えで反映してほしい）
