# optimal-strategy-expectation（b3）の報告と提案

- 書いたファイル：docs/comb/optimal-strategy-expectation.md、snippets/optimal-strategy-expectation/real-and-mod.{cpp,yaml}・restart.{cpp,yaml}、docs/img/optimal-strategy-expectation/expectimax-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0、textlint エラー 0（警告 26：文の長さ・読点の数・助詞の重なりで、多くは数式を含む文と折りたたみの箇条書き。参考の KCPC ブログの題名の「！！！」は記事の h1 のまま）
- 図：expectimax-tree.svg を render_svg.py で 360・720 幅にして目で確かめた
- 動く図：catalog の visual は null なので作っていない
- 使った出典：gotoki_no_joe の Qiita（abc412_f）、yamanoue.tslmuse.com・kcpc.hatenablog.com（abc421_e）、kmjp（abc224_g）。新しく noai を確かめたドメイン：yamanoue.tslmuse.com（指定なし）、kcpc.hatenablog.com（指定なし。付録 B にはすでにある）
- 自分で確かめたこと：abc412_f の「枚数の多い色を残す」が最適であることを、小さい入力 200 件で値反復（各状態で両方の行動を比べる）と分数の漸化式が一致することで確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc412_f | summary | 色ごとの枚数が決まった靴下のうち 1 枚を手に持ち、引き出しから 1 枚ずつ取り出して、手の靴下と同じ色ならやめ、違えばどちらか 1 枚を引き出しへ戻すことを繰り返すとき、戻す靴下を最適に選んだときの取り出す回数の期待値を mod で求める。 | https://qiita.com/gotoki_no_joe/items/dbd1cf6437edd867afa3 |
| abc412_f | evidence に追加 | https://qiita.com/gotoki_no_joe/items/dbd1cf6437edd867afa3 | ikatakos.com が執筆時に 503 で読めなかったため |
| abc421_e | evidence に追加 | https://yamanoue.tslmuse.com/abc_421/ 、https://kcpc.hatenablog.com/entry/ABC421 | 同上 |
| abc470_e | summary | N 組のカードの神経衰弱で、決まった回数失敗するかすべてのカードを取ると終わるとき、最適にめくったときの、取ったペアの得点の和の期待値を求める。 | 下の未解決の点を参照（要確認） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 多重集合 | multiset | 同じ値を何個でも含められる集合。順序は区別せず、値ごとの個数で決まる。C++ の `multiset` はこれを順序付きで持つコンテナである |
| 戦略 | strategy | 確率過程やゲームで、各時点に見えている情報から次の行動を決める規則。まだ起きていない偶然の結果を使って行動を決めることはできない |

本文では多重集合を用語集へリンクせず、かっこで定義を書いた。用語集に足したら、state-design の節の最初の出現をリンクに直してほしい。

## 手引きへの提案

- §5 comb に「答えを仮定して二分探索するときは、戦略を固定すると f(y) が y の 1 次式で傾きが 1 未満になることを根拠に書く（f(y) − y が狭義に減少）」を足す案。expectation-linear-equations の #unknown の最後の段落とも合う
- §5 comb に「最適な行動が値の比較なしに入力の性質だけで決まると示せるなら、mod のまま計算できる（例：abc412_f）」を、mod で比較できない話の避け方の 2 つ目として足す案

## 問題の補充の候補

- 比較が要り答えを mod で出す ABC の問題（rational-mod の担当からの申し送り b1/rational-mod.md:32）は、abc412_f がそれに当たる（ただし比較は性質で消える型）。rational-mod の練習に abc412_f を足すのを提案する（役割 practice）
- 「やり直しを答えの二分探索で解く」型の、実数で答える ABC の問題は見つけられなかった（abc224_g は戦略の形から 1 次方程式で解くのが本筋）。候補が見つかれば guess-answer の練習に足したい

## 未解決の点

- ikatakos.com（台帳の evidence）が執筆中ずっと 503 で読めなかった。abc412_f・abc421_e は別の第三者の解説で確かめたが、abc470_e（Concentration）と abc342_f の問いは、台帳の approach・summary と検索結果の抜粋（ikatakos のページの要約）にしか拠っていない。abc470_e の要約（失敗の回数の上限・ペアの得点の和）と練習の方針は、検証役が evidence で確かめてほしい
- abc412_f の答えの法（998244353 か）を第三者の解説で確かめられなかったので、要約は「mod で求める」とした
- abc421_e の「サイコロ 5 個・3 回まで」は yamanoue の記事に拠る（KCPC の記事は個数と回数を書いていない）
- stopping の節の手順はブラックジャック型の自作の遊び（引き分けは負け）で書いた。abc342_f の細かい規則（引き分けの扱いなど）は確かめていないので、練習の方針では規則に触れていない
- 使用量の目安：道具の呼び出し 40 回ほど、Web の取得・検索 15 回ほど

## 検証の指摘への対応（直し）

- 1（直すべき）：「狭義に減少」を「増えることがなく（広義に減少）、y < X で正、y > X で負」に直した
- 2（直すべき）：(a) を採った。stopping の遊びを「相手はちょうど K 回振る（分布は K 段の確率 DP といもす法で O(K²D)）・両方 N 以下なら大きい方が勝ち・引き分けは 1/2」に変え、g(x) = P(Y > N) + P(Y < x) + P(Y = x)/2、全体 O(N + D + K²D) とした。確認問題と応用の型の「L 以上になるまで振る」も合わせて直した。練習の方針の ABC342 F は解き方を書かず、「相手の分布を先に求めて葉にする。遊びとの違い（相手がいつまで振るか・引き分けの扱い）に合わせて作り直す」とした。上の未解決の点の「abc342_f の細かい規則は確かめていない」は、検証役が公式解説の要旨の抜粋で確かめたので解消
- 3：解法の詳細の 4 つ目を 1 − p_x = (Σ_{B_j > B_x} B_j + B_x − 1)/S の形にし、同じ B の色をまとめて処理すると書いた
- 4：本文は変えていない。abc470_e の要約（失敗の上限・得点の和）と練習の方針は、ikatakos.com が読めるようになってからメインが確かめてほしい（台帳の checked は空のまま）
- 5：「順序を区別すると、5 個すべてを残す列だけでも 6^5 = 7776 通りある」に直した
- 6：「残した目の多重集合は 462 個しかない」に直した
- 7：図を縦の配置（根を左、選択の節点 6 つを縦に並べ、葉に「やめる d」「振り直す 3.5」と書く）に作り直し、viewBox を 420×470 にした。下の注の行は葉の文字で足りるので削った。360px・720px の PNG で重なり・はみ出しがないことを確かめた。代替テキストも合わせた
- 8：「g(s) が『相手の得点との比較』になる形もある」に直した

## 台帳への提案（直しの後）

- abc412_f・abc421_e・abc342_f の checked に 2026-10-21（検証役の提案のとおり）。abc470_e は空のまま
- abc342_f の役割は practice のまま（本文の遊びを別の規則に変えたので、例題へ移す必要はない）
