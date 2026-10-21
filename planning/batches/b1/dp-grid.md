# dp-grid の報告と提案（工程8b・b1）

- 書いたファイル：docs/dp/dp-grid.md、snippets/dp-grid/{grid-paths,queen-paths,largest-square}.{cpp,yaml}、docs/img/dp-grid/{order,square}.svg
- front matter で変えたもの：complexity（基本は O(HW)。状態を足すと O(HW × 状態数)）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件すべて一致）、textlint（エラー 0・警告 17）
  - 残した警告：no-doubled-joshi（「右か下か」の「か」、「〜に〜に」など、言い換えると意味がぼやける箇所）、max-comma・sentence-length（数式 $(i-1, j)$・$\min(\dots)$ の中の読点、数式を含む長い文）
- 動く図：作っていない（visual は static・priority 2）。静的な SVG を 2 枚置いた（order.svg：経路の数を書いた表と、上下左右に動くときの閉路の対比。square.svg：min + 1 の正方形）
- 使った出典：drken の Qiita（EDPC H）、drken のはてなブログ 4 本（abc311_e・abc183_e・abc175_e・abc210_d）、torus711（abc369_f）、ikatakos 3 本（abc147_e・abc344_f・abc227_f。解説の部分だけ）。題名は各ページの title 要素・h1 で確かめた。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 9 回

## 台帳への提案

使った 9 問（dp_h・abc311_e・abc183_e・abc210_d・abc175_e・abc369_f・abc147_e・abc344_f・abc227_f）の summary と approach は、evidence の解説と食い違いがなかった。直しの提案はない。

- abc227_f の approach に別解を足してよい：「値を max(a − X, 0) に置き換えて最小の経路の和 + KX を全 X で最小化すると、個数の状態なしで O(H²W²)」。根拠：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/1113_abc227 。本文の折りたたみに証明を書いた

## 用語集への提案

なし（状態 `state`・番兵 `sentinel` は既存の anchor にリンクした）。

## 手引きへの提案

- §5 の dp に「グリッドのように 2 次元の表を広げて番兵を置くときは、問題の (i, j) と表の (i+1, j+1) の対応をコメントに書く」を足すとよい（largest-square と落とし穴で書いたが、ほかのページでも同じ誤りが起きる）

## catalog・front matter への提案

- related に lis・dp-reconstruction・dp-state-design を足すとよい（本文の落とし穴と練習で、大きな盤面を点の列の LIS に直す話と、状態の足し方の話でリンクしている）
- related の `inclusion-exclusion-dp#first-obstacle` と `grid#right-down` は、相手のページが stub なので本文では節ではなくページへリンクした。相手が draft になったら節へのリンクに直せる

## 問題の補充の候補

- 足さなくても例題 2・練習 6・力試し 1 で目安を満たし、abc319 以降も 2 問（abc369_f・abc344_f）ある
- abc415_e（E. Hungry Takahashi、diff 1212、台帳で確認済み・binary-search-answer の練習）：グリッドを右か下に進み、所持枚数が負にならない最初の枚数の最小を求める。右下から「要る枚数の最小」を DP する向きの反転の練習として dp-grid にも practice で載せられる。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0719_abc415
- abc201_d（D. Game in Momotetsu World、diff 1317、確認済み・minimax の例題）：右下から埋めるグリッドのゲーム。本文では minimax の節へのリンクで触れただけ。dp-grid の練習に足すかはメインの判断

## 未解決の点

- SVG を描画する道具がなく、XML として読めることと座標・文字幅の見積もりだけを確かめた。表示（特に order.svg の右側の曲線の矢印と文字のはみ出し）の確認を検証役に頼みたい
- abc227_f の K の制約は解説の抜粋で確かめられなかった。本文は「K が経路の長さ（H + W − 1）以下なら約 5×10^7」と条件付きで書いた
- 「左にも動けるが上には戻れない」型（確認問題の 1 つ目）は台帳に問題がなく、型だけを書いた
- frequency_evidence の recent（abc476_f）は manhattan-chebyshev の練習で、このページには載せていない
