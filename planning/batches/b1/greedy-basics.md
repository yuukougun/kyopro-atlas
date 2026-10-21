# greedy-basics の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/greedy-basics.md、snippets/greedy-basics/strongest-first.{cpp,yaml}、snippets/greedy-basics/batch-same-values.{cpp,yaml}、snippets/greedy-basics/coin-counterexample.{cpp,yaml}、docs/img/greedy-basics/exchange.svg
- front matter で変えたもの：complexity（`基準でのソート O(N log N) と 1 回の走査 O(N) が多い。同じ値をまとめれば、回数 K によらず O(N log N)`）・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 交換論法・優先度付きキュー・区間スケジューリングへのつながり, anchor: next-steps}` を足した（手引き §4 の「上位の手法とのつながり」の節）
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 6。数式の中の読点を数える max-comma 2 件、助詞の重複 4 件で、読みやすさを確かめたうえで残した）
- fix_problems --check：このページの行は直すべき行 0。ただし basics/lexicographic-greedy.md の 6 行（素の ID のままの行）が「直すべき行」として出て、終了コードは 0 でない。担当外なので触っていない
- コード片の確かめ：strongest-first は「投げた刀は使えない」制約を守る全探索（メモ化）と、batch-same-values は 1 回ずつのシミュレーションと、それぞれ乱数の小さい 400 ケースで突き合わせた（一時置き場で実施）
- 図：静的な SVG 1 枚（貪欲解・ほかの解・入れ替えた解を 3 段に並べ、最初に違う列を強調）。SVG を描画する道具が手元になく、見た目は目で確かめていない。検証役に描画の確認を頼みたい。visual は priority 2 なので動く図の div は置いていない

## 使った出典

- drken「AtCoder ABC 085 D - Katana Thrower (3Q, 緑色, 400 点)」https://drken1215.hatenablog.com/entry/2024/05/15/012834：例題（制約をゆるめてから貪欲、強い順に使う理由）。制約 1 ≤ a_i ≤ b_i もここで確かめた
- hamayan「Amusement Park [AtCoder Beginner Contest 216 E]」https://blog.hamayanhamayan.com/entry/2021/08/29/231101：同じ値をまとめる方法と途中で尽きる場合
- comet725「ABC459Dを解いた【Counter】」https://qiita.com/comet725/items/097da34b603464d309cd、cry999「AtCoder ABC459 D - Adjacent Distinct String：貪欲法が動く条件を証明する」https://zenn.dev/cry999/articles/20260704-atcoder-abc459-d-adjacent-distinct-string：練習の問いと方針、帰納法の不変条件
- ikatakos ABC473 の記録（解説の部分だけ）：下の補充候補 abc473_e の問いと方針の確認
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

- abc459_d｜summary｜文字列の文字を並べ替えて、隣り合う 2 文字がどれも異なるようにできるかを判定し、できるなら 1 つ作る。｜https://zenn.dev/cry999/articles/20260704-atcoder-abc459-d-adjacent-distinct-string（本文の行にはこの要約を書いた）
- abc459_d｜approach｜「最多の文字が ⌈N/2⌉ 以下なら可。直前と違う文字のうち残りの最も多いものを置く貪欲（行き詰まらないことは帰納法で示せる）」に具体化してもよい｜同上
- abc085_d・abc216_e・abc459_d｜checked｜2026-10-21｜各 evidence で問いと方針を確かめた
- abc216_e｜approach｜変更なし。evidence（hamayan）は貪欲の段ごとの処理だけで、答えの二分探索の別解は書かれていない（別解の裏付けが要るなら別の URL を足す）

## 用語集への提案

- なし（本文で用語集へのリンクは使っていない）。必要なら「マトロイド｜matroid｜部分集合で閉じ、交換の性質（小さい独立集合に大きい独立集合から要素を足せる）を持つ集合族。重みの大きい順に足せるなら足す貪欲で、重みの和が最大になる」を足す候補（aliases にマトロイドがあるので、本文の proof の節で定義した）

## 手引きへの提案

- §4 の technique（基礎）の構成「要点 → 応用の型 → 落とし穴 → 上位の手法とのつながり → 問題」の「上位の手法とのつながり」を sections に載せるかが §13.1 から読み取りにくい。brute-force・sorting-techniques にならい `next-steps` として sections に載せた。決まりとして書くとよい
- fix_problems --check がほかのページの行で失敗するので、`--page` で絞れる検査（`--check --page <id>`）があると、並列の執筆で検査の結果を判断しやすい

## 問題の補充の候補

catalog の数（例題 1・練習 2）は手引きの目安の下限。次の候補で練習を足せる。

- abc473_e（K-Divisible Subarrays、966、台帳では prefix-sum-counting の練習・確認済み）：数列から重ならない連続部分列を選び、和が K の倍数のものを最大いくつ選べるか。累積和 mod K を見て、条件を満たす区間ができたら最も早く閉じる貪欲（最初の区間を早く終わる区間に入れ替えても悪くならない、の交換論法）。このページの proof の節の練習として合う｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0829_abc473（解説の部分）
- abc141_d（Powerful Discount Tickets、823、台帳では greedy-priority-queue の練習・確認済み）：毎回最も高い商品に券を使う。「1 回ごとに最大を選ぶ」サインの易しい代表で、ここから greedy-priority-queue へつなげられる｜https://drken1215.hatenablog.com/entry/2019/09/16/032000（台帳の evidence。私は開いていない）

## 未解決の点

- abc216_e の制約（N・K・A_i の上限）は evidence で確かめきれなかった。本文では「K が 10^9 を超えると」「値と回数がどちらも 2×10^9 なら」と一般論として書き、問題の制約としては書いていない。batch-same-values の等差数列の積の途中値は、値・回数が 2×10^9 程度まで long long に収まる（最大の場合をケースに入れた）
- 「日本の硬貨は大きい順の貪欲で正しい」は既知の事実として書いた（出典は付けていない）。必要なら検証役に確かめてほしい
- interval-scheduling・exchange-argument・greedy-priority-queue・lexicographic-greedy・minimum-spanning-tree・stress-testing・knapsack-01・dp-basics は stub なので、ページへのリンクだけにした（節へのリンクは draft の sorting-techniques#greedy-order と binary-search-answer#greedy-check だけ）
