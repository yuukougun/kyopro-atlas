# permutation-cycles の報告（工程8b・b1）

- 書いたファイル：docs/comb/permutation-cycles.md、snippets/permutation-cycles/decompose.{cpp,yaml}、snippets/permutation-cycles/power.{cpp,yaml}、docs/img/permutation-cycles/swap-split.svg
- front matter で変えたもの：complexity（`巡回分解 O(N)、K 回の合成 O(N)（K を各巡回の長さで割った余りだけ進める）`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件とも期待どおり）、textlint（エラー 0・警告 3。図の代替テキストの文の長さと読点、確認問題の数式 $P = (2, 3, 1, 5, 4, 6)$ の中の読点で、どちらも数式・列の表記による誤検出）
- 図：静的な SVG 1 枚（catalog の visual は static・priority 2）。手元に SVG を画像にする道具がなく、XML として正しいことだけを確かめた。表示の崩れ（文字の重なり）は検証役に目で確かめてほしい
- 使った出典：
  - ikatakos ABC436 のメモ（解説の部分）：例題の方針、Union-Find での実装、「任意の swap によるソートは近年の ABC で頻出」
  - drken ABC175 D：練習の方針
  - Lanly（cnblogs）ABC377：練習の方針（歩数が 2 倍ずつ）
  - ikatakos ABC371 のメモ（解説の部分）：力試しの方針、lcm が約 700 桁になりうること
  - oraclesqlpuzzle ABC367 E：台帳の確認（下記）
  - 新しく noai を確かめたドメインはない（すべて付録 B にある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc367_e | summary | 「置換 X」は一般の写像の可能性が高い。「数列に、添字の写像 X による並べ替え B_i = A_{X_i} を K ≤ 10^18 回行った結果を求める。」など、置換と言わない形を提案（問題文で値の重複が許されるかはメインが確かめる） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc367-e.html （X を値の重複を許す Functional graph として扱っている） |
| abc377_e | summary（本体） | 本体の summary の末尾に句点がない（「…行った後の列を求める」）。alternatives の permutation-cycles 用は句点ありで問題なし | 表記の統一 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 置換 | permutation | $\{0, \dots, N-1\}$ から自分自身への全単射で、順列 $p$ を写像 $i \mapsto p_i$ と見たもの。続けて使うことを合成と呼ぶ |
| 巡回 | cycle-of-permutation | 置換の矢印 $i \to p_i$ をたどって出発点に戻るまでに通る頂点の列。置換は互いに交わらない巡回に分かれる |
| 恒等置換 | identity-permutation | すべての $i$ で $p_i = i$ となる置換。ソート済みの列に当たり、巡回はすべて長さ 1 である |
| 置換の位数 | order-of-permutation | $p^K$ が恒等置換になる最小の $K \ge 1$。巡回の長さすべての lcm に等しい |

本文では用語集へのリンクは既存の「固定点」だけに張った。上の語を足すなら、本文の最初の出現にリンクを足してよい。

## 手引きへの提案

- §11 の出典の題名：ikatakos 氏のメモの題名はページの h1（例「AtCoder Beginner Contest 436 E,F,G問題メモ」）で、title 要素からは取れなかった。h1 を題名にする、と書いておくと迷わない
- 図の確認：SVG を画像にする道具（rsvg-convert など）が環境にないので、執筆者は見た目を確かめられない。検証役の手順に「SVG を表示して文字の重なりを見る」を入れるか、道具を用意してほしい

## 問題の補充の候補

練習 2・力試し 1 で目安（練習 2〜6）は満たしている。補充するなら次を探す価値がある（どれも問いと解き方の裏付けはまだ取っていない）。

- ap.py で題名に Swap・Permut を含む ABC を見たが、巡回分解が主役と確かめられたものはなかった。abc233_f（Swap and Sort、2038）は swap できる組が限られる問題で、巡回分解より連結成分・木の話が主役と思われるので、このページの候補にはしない
- 「任意の swap でソートする最小回数」そのもの（N − c）を問う易しい問題があれば練習の先頭に置きたい（ikatakos 氏によれば近年の ABC で頻出の題材なので、ABC の C〜E にある可能性が高い）

## 未解決の点

- abc436_e で「最初からソート済み」の入力がありうるかは確かめていない（式 $\sum \binom{\ell}{2}$ はその場合 0 になるので、本文はその前提に触れていない）
- 力試しの方針の「多倍長整数で持つなどの工夫が要る」は ikatakos 氏の記述（多倍長で扱う）に沿った。素数べきごとに余りを持つ別法には本文で触れていない
- related の permutation（patterns）には本文からリンクしていない（stub のため。必要ならメインの判断で）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 6 回
