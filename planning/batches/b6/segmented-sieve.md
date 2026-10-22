# segmented-sieve の問題の補充（b6・工程9）

- ページ：docs/math/segmented-sieve.md（レベル 水）。今の練習は abc227_g（diff 2207）の 1 問、例題は abc412_e（diff 1496）
- 探したところ：
    - (1) b1 の summary/candidates.md と報告 planning/batches/b1/segmented-sieve.md の「問題の補充の候補」には具体的な問題がない（「易しい練習（区間の素数を数えるだけのもの）を、典型90・アルゴ数学・鉄則本などから探すとよい」とだけある）。b3・b5 の candidates.md に segmented-sieve の項はない
    - (2) data/problems.yaml で pages に segmented-sieve を持つのは abc412_e（example）と abc227_g（practice）だけで、どちらも本文にある
    - (3) `python3 tools/ap.py search` で Prime・Primes・Sieve・Divisor・Factor を題名検索し、math_and_algorithm_bt（097. Primes in an Interval）を見つけた。第三者の資料は GitHub のコード検索（「区間篩 atcoder.jp/contests」「segmented sieve atcoder.jp/contests」など）で探した。この作業では WebSearch の上限に達していて使えなかった
- 問題の実在・題名・difficulty は `python3 tools/ap.py search` で確かめた（2026-10-22）
- 候補 1 問を足すと練習は合わせて 2 問になる（目標の下限）

## 候補

### math_and_algorithm_bt（新規。台帳になし）

- 問題ID：math_and_algorithm_bt
- 題名：097. Primes in an Interval
- difficulty：なし（AtCoder Problems に値なし。アルゴ数学の演習問題集）
- 役割：practice（区間篩をそのまま書くだけの易しい問題で、abc227_g より前に置く易しい練習になる。difficulty がないので、易しい順の位置は内容から先頭とする）
- 要約：L 以上 R 以下の整数のうち素数がいくつあるかを数える（R ≤ 10^12 と大きく、区間の長さ R − L は 50 万程度まで）。
- 方針の要点：√R 以下の各数 p について区間で最初の p の倍数 ⌈L/p⌉·p から p 自身を除いて印を付け、L = 1 なら 1 も除いて、残った数を数える。
- 裏付け：
    - https://github.com/E869120/math-algorithm-book/blob/main/editorial/chap6-21_25/prob6-23.cpp （著者 E869120 氏の公式の解答コード。最終確認問題 23 の解答で、配列 500009 要素・⌈L/i⌉·i から i 自身を飛ばして印を付ける・L = 1 の場合分け、を確かめた。この問題番号が 097 と同じものだとは題名と内容の一致から判断した。解説の PDF は読めなかった）
    - https://github.com/bouzuya/blog.bouzuya.net/blob/master/data/2022/03/2022-03-18.md （「097 - Primes in an Interval を解いた」とあり、R ≤ 10^12 で 10^12 の配列は持てないので区間篩にする、1 の扱いに注意、を確かめた）
    - 補足：https://github.com/hoshinon57/Algorithm/blob/master/AtCoder/Others/algo-math-097.cpp （冒頭のコメントに 097 の URL と「エラトステネスの区間篩を用いて解いた」）
- 台帳への追加の提案：pages に {id: segmented-sieve, role: practice}。label は「アルゴ数学 097. Primes in an Interval」の形（台帳の既存のアルゴ数学の問題の書き方に合わせる）
- 本文への影響：確認問題・落とし穴の「L = 1」「p 自身を消さない」がそのまま試される問題なので、練習の方針の折りたたみで #first-multiple を指せばよい

## 見つからなかったもの

- ABC・ARC で区間篩を使う問題は、abc412_e・abc227_g のほかに見つからなかった。AtCoder の問題を手法で分類した第三者のリポジトリ（https://github.com/mostafa-cse/AtCoder-Categorizer の QUALITY_PROBLEMS_BY_TOPIC.md）でも、Segmented Sieve の分類は abc227_g だけだった。区間篩を扱う個人のライブラリ（goropikari・Haar-you・tomoakiii・hoshinon57 のリポジトリ）が挙げる AtCoder の問題も math_and_algorithm_bt と abc412_e だけだった
- arc116_c（Multiple Sequences）は、ある第三者のメモ（matcher9131/AtCoder-Repo の notes/integer.md）が「区間篩」と書いているが、中身は N 以下を前処理で素因数分解する普通の篩なので候補にしない
- 青〜黄の帯の力試しの候補は見つからなかった。無理には足さない。WebSearch が使えれば、はてなブログ・Qiita の「区間篩」の記事から ABC 以外（PAST・企業コンテスト）を探す余地がある

## 新しく確かめたドメイン

- なし（github.com は付録 B にある）
