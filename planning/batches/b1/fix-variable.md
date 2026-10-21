# fix-variable（一部を固定して数える）の報告と提案

- 書いたファイル：docs/thinking/fix-variable.md、snippets/fix-variable/middle-abc.{cpp,yaml}、snippets/fix-variable/remainder-pairs.{cpp,yaml}、docs/img/fix-variable/fix-middle.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 期待と違う 0（2 本）。textlint エラー 0・警告 8（要点の計算量の行と画像の代替テキストの文の長さ、数式の中の「と」と読点、台帳から作る問題の行の長さと助詞。どれも誤検出か台帳の文）
- 使った出典：drken（abc330_d・abc318_e・arc102_a・abc254_d）、qiita の comet725（abc453_e・abc458_e）、cnblogs の Billlly（abc453_e の問いの確認）。www.cnblogs.com は付録 B にあり、check_noai でも指定なし
- SVG は描画の道具が手元になく、目で確かめていない。検証で表示（特に下の括弧のラベルの重なり）を確かめてほしい
- 動く図は作っていない（visual は priority 2・static なので SVG 1 枚で済ませた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc453_e | summary | N 人を 2 つのチーム A・B（どちらも 1 人以上）に分ける。各人 i は、所属するチームの人数が L_i 以上 R_i 以下でなければならない。分け方の数を 998244353 で割った余りで求める。 | https://www.cnblogs.com/CR-J/p/19853087 ・ https://qiita.com/comet725/items/0747fd1209e978e74e66 |
| abc453_e | approach | A の人数を固定し、各人を「A だけ・B だけ・両方・どちらも不可」に分類して二項係数を足す。分類の人数は境界での差分更新で O(N) | 同上 |
| abc453_e | evidence | https://www.cnblogs.com/CR-J/p/19853087 を足す | — |
| abc458_e | pages | fix-variable の practice を外すか、問いを確かめてから戻す（下の「未解決の点」） | https://qiita.com/comet725/items/3fdcd73125c20e2cc7a2 |
| abc330_d・abc318_e・arc102_a・abc254_d・abc453_e | checked | 2026-10-21（検証で確かめた後に） | 上の各 URL |

- 本文の abc453_e の行は、台帳の summary が「（執筆時に確かめる）」のため上の値で書いた。台帳を直してから fix_problems を流せば一致する
- abc458_e（Count 123）は、問題の条件（どんな並べ方を数えるか）を第三者の解説から確かめられなかったので、本文に載せていない。comet725 の記事は方針とコードだけで、問いの文章がない

## 用語集への提案

- なし

## 手引きへの提案

- §4 の thinking の構成（合図 → 最小の例 → 例題 → 関連する手法）と §13-1 の定型の節（落とし穴・使い分け）の並べ方が、基礎の technique の目安と少し違う。thinking でも「中身の節 → 落とし穴 → 使い分け → 例題 → 練習 → 力試し → 参考」でよいと明記すると迷わない（このページはその順にした）

## 問題の補充の候補

- abc376_e（Max × Sum、diff 1063、確認済み）：A の最大値を固定し、それ以下の中から B の小さい K 個の和をヒープで保つ。「最大値を固定して残りを最適化する」節の代表。台帳では greedy-priority-queue の practice だけなので、fix-variable の practice に足す案。https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc376-e.html （research/01 §5 でも「fix-variable と共通」とある）
- arc084_a（Snuke Festival、diff 1096、確認済み）：中段を固定し、上段・下段の個数を二分探索で数える。真ん中を固定する代表。台帳では binary-search の practice。fix-variable の practice に足す案。https://drken1215.hatenablog.com/entry/2021/02/25/223800
- abc458_e を外すと練習が 2 問になるので、上の 2 問のどちらかを足すと thinking の目安（練習 2〜6）に余裕が出る

## 未解決の点

- abc458_e の問いが確かめきれない（上記）。ikatakos 氏の記録は問題文を引用した節を読まない規則なので、ほかの解説が見つかるまで保留にした
- abc318_e の方針は、drken の「隙間ごとに寄与を数える」ではなく、出現位置 p_t から q_t = p_t − t を作って Σ(q_b − q_a) を累積で足す形で書いた。同じ値を数える別の書き方で、式は自分で確かめた（間の位置の数 − 間の値 v の数）。検証で確かめてほしい
- ARC102 C の練習の方針で O(N + K) としたのは、K ≤ 2×10^5 を drken の記事の別解の説明から読んだため
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 9 回・Web 検索 3 回

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：#fix-middle の最後の段落を、位置の条件があるときは BIT、3 つの別の列から選ぶときはソートして二分探索、の 2 つに分けた
- 指摘 2（直すべき）：fix-middle.svg を viewBox 500×300 に詰めた。上下の文を短く折り、本文 16・添字とラベル 14 にした（スマホ幅 358px で約 11.5px・10px）。マス目の左の余白も詰めた
- 指摘 3：採った。「2 重ループが要る」を「単純な積にならず、もう 1 段の前計算が要る」にした
- 指摘 4：採った。「ソートの後の数える部分を $O(N)$ にできる」にした
- 指摘 5：採った。文を分け、$\mathrm{cnt}[r] \cdot \mathrm{cnt}[s]^2$ と書いた
- 指摘 6：台帳の直しはメインの作業なので、上の「台帳への提案」のとおり（abc453_e の summary・approach・evidence、abc458_e を fix-variable の pages から外す、checked の日付）。本文は変えていない。練習を足す場合の候補は「問題の補充の候補」の arc084_a・abc376_e
