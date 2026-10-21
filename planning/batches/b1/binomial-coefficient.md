# binomial-coefficient の報告（工程8b）

- 書いたファイル：docs/comb/binomial-coefficient.md、snippets/binomial-coefficient/{pascal,kth}.{cpp,yaml}、docs/img/binomial-coefficient/pascal-and-paths.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：
  - check_pages --page binomial-coefficient：エラー 0・警告 0
  - check_snippets snippets/binomial-coefficient：コード片 2・期待と違う 0
  - textlint：エラー 0。警告 5（要点の囲みの「いつ使うか」の入れ子の箇条を 1 文と数える誤検出、図の代替テキストの長さ・読点、折りたたみの中の数式を含む文の長さ、「それに合わせる（…）」の助詞「に」）
  - fix_problems --check：このページの行は直す必要なし。ただし basics/median-absolute.md の 3 行（arc100_a・typical90_br・abc330_f）が「直すべき行」と出て終了コード 1。担当外のページなので触っていない
- 使った出典（どれも付録 B のドメイン。新しいドメインなし）：
  - https://blog.hamayanhamayan.com/entry/2018/04/15/164633 ：例題 arc095_b の方針
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0522_abc202 ：abc202_d の方針と A, B ≤ 30（解説の部分だけ）
  - https://drken1215.hatenablog.com/entry/2019/02/16/000900 ：abc057_d の方針と N ≤ 50
  - オーバーフローの境目（C(66,33) は long long に収まり、C(67,33) はあふれて unsigned long long には収まる、C(68,34) はどちらもあふれる）は Python の math.comb で確かめた

## 台帳への提案

- abc202_d：本文の行は alternatives の binomial-coefficient 用の summary（「a を A 個、b を B 個並べてできる文字列のうち、辞書順で K 番目のものを求める。」）を使った。問題なし
- arc095_b：evidence の 1 件目 `https://blog.hamayanhamayan.com/`（トップページ）は裏付けにならないので外してよい
- abc476_g：frequency_evidence に recent として挙がっているが、台帳の pages は lis（challenge）だけで、二項係数との関係は確かめられなかった。frequency_evidence の見直しを提案する（未解決の点も参照）

## 用語集への提案

- なし（本文は用語集へリンクしていない）

## 手引きへの提案

- §6 の記法に、パスカルの三角形の表を `$\mathrm{C}[n][k]$`（二項係数の値 $\binom{n}{k}$ と区別する）と書く約束を足すとよい。本文ではそう書いた
- §13-8 の「誤検出なら残してよい」の例に、要点の囲みの入れ子の箇条（「いつ使うか」）が 1 文と数えられる件を足すとよい

## 問題の補充の候補

基礎のページとしては例題 1・練習 2 で目安の下限にあたる。足すなら次の型が合う（どれも台帳で確認済みだが、別のページの持ち物）。

- abc145_d（lattice-paths の例題）：2 種類の移動の回数を決めて並べ方を二項係数で数える。本ページの「0/1 列の形」の練習として practice に足せる。裏付け https://drken1215.hatenablog.com/entry/2020/04/26/180000
- abc156_d（binomial-precompute の練習）：n が巨大で k が小さい二項係数。使い分けの表の参照先としてだけ使い、本ページには載せない方がよい

## 未解決の点

- 動く図は作っていない。catalog の visual は static・priority 2 なので、静的な SVG（パスカルの三角形と格子路を並べた図）で代えた
- frequency_evidence の abc476_g（Increasing Popcount）が二項係数を使う根拠は、台帳の approach（Dilworth の定理と popcount）からは読み取れなかった。メインで確かめてほしい
- 使い分けの表の「n が巨大で k が小さい」行は、catalog の統合（binomial-variants → binomial-precompute）に合わせて本ページには載せず、二項係数の前計算のページに任せた
- 使用量の目安：道具の呼び出し 約 25 回、Web 取得 3 回（WebFetch）＋題名の確認に curl 4 回
