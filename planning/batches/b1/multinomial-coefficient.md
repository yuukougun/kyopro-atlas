# multinomial-coefficient の報告と提案

- 書いたファイル：docs/comb/multinomial-coefficient.md、snippets/multinomial-coefficient/reorder.{cpp,yaml}、docs/img/multinomial-coefficient/divide.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（期待と違う 0）、textlint（エラー 0・警告 7。数式を含む文の長さ・読点の数、「で」「に」「が」「も」の重なりの誤検出寄りのもの）、fix_problems --check はこのページについて 0。全体の --check は、執筆中の他ページ（comb/counting-fix-order.md の ID だけの行）で 1 を返す
- 注意（作業の誤り）：最初に `fix_problems.py --page multinomial-coefficient --field comb` を実行したところ、--field comb が分野全体に効き、執筆中の comb/counting-mindset.md の 7 行（abc167_e・abc156_e・abc127_e・abc460_e・abc150_e・abc173_f・abc180_f）まで書き換えた。直後に「- ID：要約」の形へ戻した（要約の文字は変えていない）。担当の執筆者に影響がないか、メインで確かめてほしい
- 使った出典：kazun-kyopro.hatenablog.com（abc234_f）、ikatakos.com（abc470_f。解説の部分だけ）、drken1215.hatenablog.com（abc266_g・arc067_c）。どれも付録 B にあるドメインで、新しく noai を確かめたドメインはない
- 事実の確かめ：abc266_g の式 C(G+B, G)·C(G, K)·C(R+B, K+B) と、合流 DP（abc234_f の型）は Python の全探索で小さいケースと一致を確かめた。MISSISSIPPI＝34650、6 人を 2 人ずつ 3 組＝15 も計算で確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc470_f | summary（ページ multinomial-coefficient の alternatives と本体の両方） | 許された位置の組の swap をちょうど 10^100 回行ったあとにできる文字列の種類数を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0808_abc470 |
| abc234_f | approach（任意） | 各文字の個数だけで文字列が決まるので、文字ごとに使う個数を DP で決め、合流のたびに C(全体の長さ, 追加する個数) を掛ける | https://kazun-kyopro.hatenablog.com/entry/ABC/234/F |
| abc266_g | approach（任意） | G と B を先に並べ、RG にする K 個の G の直前に R を置き、残りの R を新しい RG を作らない K+B+1 か所に重複組合せで配る | https://drken1215.hatenablog.com/entry/2023/05/04/185000 |

- abc470_f の summary は「（詳細は執筆時に確かめる）」を外した。本文の行は上の文で書いた（fix_problems は要約を変えないので、台帳を直せば一致する）

## 用語集への提案

- なし（本文は用語集へリンクしていない）

## 手引きへの提案

- `tools/fix_problems.py --page X --field Y` は、--page と --field を両方渡すと --field の分野全体を直す（AND ではなく OR に見える）。手引き §10 の「--page <id> で埋めてもよい」に「--field は付けない」と書き足すか、ツールで AND にする。並列で書くと他の執筆者のページを書き換えてしまう

## 問題の補充の候補

- 練習は 2 問（abc470_f・abc266_g）、力試し 1 問で目安の範囲内。補充は必須ではないので探していない。水の帯の練習（abc319 以降、diff 1200〜1700 で多項係数をそのまま使う E）があれば足したいが、裏付けまでは取っていない

## 未解決の点

- abc470_f で、全成分の文字がすべて異なるとき答えが半分になるのは「大きさ 2 以上の成分が少なくとも 1 つある」ことが前提（辺が 1 本以上あれば成り立つ）。制約で辺が 1 本以上と保証されるかは atcoder.jp を開けないので確かめていない。本文の方針ではこの端の場合に触れていない
- visual は priority 3 なので、静的な SVG（divide.svg）で代えた。動く図は作っていない
- 「多項定理」は別名にあるので、式の意味の節に展開の係数としての見方を 1 段落だけ足した
