# b4 提案：cht（Convex Hull Trick と Li Chao Tree）

- 書いたファイル：docs/dp/cht.md、snippets/cht/monotone.{cpp,yaml}、snippets/cht/li-chao.{cpp,yaml}、docs/img/cht/envelope.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査の結果：check_pages エラー 0（警告 1：related の monge が未作成扱い）、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 24（数式を含む文の長さ・助詞の重なり・数式内の括弧の誤検出）。ageprocpp 氏の記事題名（です・ます を含む）は参考の 1 行だけ textlint-disable で囲んだ
- 図：envelope.svg（400×280）を render_svg.py で 360px・720px にして目で確かめた。動く図（visual priority 2）は作っていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| dp_z | evidence | 追加：https://zenn.dev/kiwamachan/articles/34949d6ab8d049 | deque による CHT とならし O(N) を確認 |
| dp_z | checked | 2026-10-22 | 上の 2 件で問いと解き方を確認 |
| abc289_g | checked | 2026-10-22 | kmjp の記事で、傾き＝買う人数・x＝商品の価値・二分探索のクエリを確認 |
| abc228_h | checked | 2026-10-22 | kmjp の記事で、ソート後の DP の傾き −SC[i]・クエリ A[j]（どちらも単調）を確認 |

- abc289_g・abc228_h の evidence は kmjp 氏の 1 件だけのまま（§15-6 の目標 2 件に届かない）。ikatakos.com の該当ページは「まだ存在しません」で、検索でもほかの第三者の解説は見つからなかった
- kmjp 氏の abc289_g の記事は、本文の人数の式（N−1−i）とコード（N−i）がずれていると読める。本文の方針は人数を「k」とだけ書いたので影響はない

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 下側の包絡線 | lower-envelope | 直線（関数）の集まりについて、各 x での最小値をつないだ折れ線である。直線の場合は上に凸な折れ線になり、どの x でも最小にならない直線は含まれない。最大値をつないだものは上側の包絡線という。点 (a, b) の下側凸包と対応する（convex-hull#cht-duality）。 |

- handoff-b2b3 の申し送り（上側凸包・下側凸包を用語集に）について：本文では凸包の語を「下側凸包の頂点に当たる」の 1 か所でしか使わず、convex-hull#cht-duality へリンクした。凸包の側の語を用語集に足すかはメインの判断に任せる
- prh.yml：「包絡線」「Li Chao Tree」（Li-Chao Tree・LiChao の揺れ）を足すかの検討

## 手引きへの提案

- §4 の overview に「学ぶための資料」を `## 学ぶための資料 {#resources}` の定型の節として §13-1 の一覧に加えるとよい（hld と cht で同じ見出しを使った）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- colopl2018_final_c：各位置 i で (i − j)^2 + a_j の最小値を求める（直線の最小として CHT、傾きもクエリも単調）。調査レポート 02-dp §5.1 の候補。裏付け：https://drken1215.hatenablog.com/entry/2018/09/18/014400 （今回は未読。ageprocpp 氏の Qiita 記事 https://qiita.com/ageprocpp/items/3533b8f5678f9d4a5515 でも例題として挙げられていることを確認）。確認問題の 1 問目はこの形を問題 ID なしで使った
- Library Checker の line_add_get_min・segment_add_get_min は §15-5 に従い練習問題の小見出しに置いた（台帳は不要）

## 未解決の点

- EDPC Z の h・C の上限は第三者の解説で確かめられなかったので、本文に数値を書いていない
- 「遷移元が範囲 [l_i, i) に限られるときは分割統治などの別の工夫が要る」は一般論として書いた。具体的な方法（Li Chao Tree をセグメント木に重ねるなど）は書いていない
- visual（dynamic、priority 2）：作るなら data-viz="cht-envelope"、config 例 `{"lines": [[2,1],[0.5,6],[-1,9],[-0.5,10]], "queries": [1,3,5]}`。ステップは「直線を傾きの減る順に追加 → 末尾が不要なら消す（交点の位置を表示）→ クエリで先頭を捨てる」。置き場は #lower-envelope の静的な図の直後
- 使った出典：参考の節のとおり。新しく noai を確かめたドメイン：satanic0258.hatenablog.com・smijake3.hatenablog.com・hcpc-hokudai.github.io（どれも指定なし。hcpc の PDF は読んでいない）
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 約 12 回

## 検証の指摘への対応（verify/cht.md）

- 1〜6 をすべて直した（採らなかった指摘はない）。図は「8/3」「10/3」の x を点線の位置（186.7・223.3）にそろえ、PNG で重なりがないことを確かめた
- 台帳：検証役も abc289_g・abc228_h に `checked: 2026-10-22` を入れてよいとした（上の提案のとおり）。dp_z の checked はこの提案に含めていない
