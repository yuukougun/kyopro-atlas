# expectation-of-square の問題の補充（b6・工程9）

- ページ：docs/comb/expectation-of-square.md（レベル 黄）。本文の練習は 0 問（例題 abc450_g・力試し abc277_g）
- 結果：確かめた候補 2 問。帯に近い練習の候補は 1 問（abc332_e）だけで、目標の 2〜4 問には届かない。2 問目の abc194_c は基礎の帯で大きく外れるので、採るかはメインの判断に任せる

## 候補

| 問題ID | 題名 | difficulty | 役割 | 要約 | 方針の要点 | 裏付け |
| --- | --- | --- | --- | --- | --- | --- |
| abc332_e | E. Lucky bag | 1883（青） | practice | N ≤ 15 個の品物を D 個の袋に分け（空の袋も許す）、袋ごとの重さの分散の最小値を求める。 | どの分け方でも平均は一定なので、分散の最小化を袋の重さの二乗和（平均との差の二乗和）の最小化に言い換え、部分集合の部分集合を列挙する DP で袋を 1 つずつ決める。空の袋の値 0 も二乗和に入れる | https://qiita.com/rareshana/items/76af4e8d8dcbedfc8714 |
| abc194_c | C. Squared Error | 386（基礎） | practice（帯外。入れるなら練習の先頭のウォームアップ） | 長さ N ≤ 3×10^5 の数列の全ペアについて、差の二乗の総和を求める。 | (A_i − A_j)^2 を展開して全順序対で足し 2 で割ると N Σ A_i^2 − (Σ A_i)^2 になり、O(N) で求まる（分散と二乗和の関係の節の式そのもの） | https://vermee81-coding-memo.hatenablog.jp/entry/2021/03/07/090000 （別解として値ごとの個数で全ペアを数える方法：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0306_abc194 ） |

### 確かめたこと

- 実在・題名・difficulty は `python3 tools/ap.py show abc332_e abc194_c` で確認した（2026-10-22）
- abc332_e：(2) の経路で見つけた。台帳 data/problems.yaml では pages に `{id: expectation-of-square, role: practice}` を持つが、本文の練習の節がない（b3 の報告の「問題の補充の候補」でも提案済み）。rareshana の記事で、制約 2 ≤ D ≤ N ≤ 15・空の袋を許すこと・平均が一定なので二乗和に言い換えること・空の袋の初期値の扱いを確かめた。本文の variance の節の「平均が決まっているなら、分散の最小化は二乗和の最小化」がそのまま使える。台帳の summary・approach は今のままでよい
- abc194_c：(3) の経路で見つけた。vermee81 の記事で、全ペアの差の二乗の和を展開して N Σ A^2 − (Σ A)^2 にする解法を確かめた（記事の途中式に符号の誤記 +2A_iA_j があるが最終式は正しい）。「N 個の値の分散 = 一様に 1 つ選んだ値の分散」と同じ式で、ペアに分ける節の Σ_{i<j} の和を和の二乗から求める式の練習にもなる。台帳にないので、採るなら追加が要る

### 台帳への提案（採る場合）

- abc194_c｜新規｜summary「長さ N の数列の全ペアについて、差の二乗の総和を求める。」・approach「二乗を展開し、N Σ A_i^2 − (Σ A_i)^2 で O(N) で求める」・pages `{id: expectation-of-square, role: practice}`｜evidence https://vermee81-coding-memo.hatenablog.jp/entry/2021/03/07/090000

## 見つからなかったこと

- 「〜の二乗の期待値」を正面から問う、水〜黄の帯の AtCoder の問題は、例題・力試しにある 2 問のほかに見つけられなかった。b1・b3・b5 の candidates.md と b3 の報告にも、abc332_e のほかの候補はない
- 調べて外したもの：abc463_g（Random Walk Distance、diff 2452）は kmjp の記事で確かめると距離の絶対値の期待値で、二乗は使わない。abc480_g（Zonal Score Minimization）は最大 − 最小の和の最小化で二乗は出ない。abc330_g（Inversion Squared、diff 3455）は帯から遠すぎるので開いていない。AtCoder Tags の Expected-Value の一覧（35 問）と drken1215 の「期待値」カテゴリの一覧にも、二乗の期待値を問う問題は見当たらなかった
- ABC332 E の 2 つ目の裏付けを kmjp で探そうとしたが、はてなブログの検索が HTTP 429 で止まった

## 資料のドメイン

- 新しく noai を確かめたもの：vermee81-coding-memo.hatenablog.jp（check_noai：X-Robots-Tag なし、meta robots は max-image-preview:large だけ、noai の指定なし）、scrapbox.io/kimiyuki（指定なし。ただし競技の問題は載っておらず資料にはしていない）
- ほかは付録 B のドメイン（qiita.com・ikatakos.com・kmjp.hatenablog.jp・drken1215.hatenablog.com・atcoder-tags.herokuapp.com）

## 使用量の目安

- 道具の呼び出し 約 40 回、Web 検索 12 回、Web 取得 約 12 回
