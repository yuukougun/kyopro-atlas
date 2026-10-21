# inline-dp の報告（b2）

- 書いたファイル：docs/dp/inline-dp.md、snippets/inline-dp/relax-edges.{cpp,yaml}・shift.{cpp,yaml}・intervals.{cpp,yaml}・stack-lazy.{cpp,yaml}（どれも範囲 core。各プログラムは素朴な 2 次元の表の解と assert で突き合わせる）、docs/img/inline-dp/row-diff.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 本とも一致、textlint エラー 0・警告 16（数式を含む文の長さ・読点、半開区間 `[l, r)` の括弧の対の誤検出、数式の中の「と」）。SVG は render_svg.py の 360px・720px で目視した。4 本のコード片は手元で乱数の小さな入力 300 組ずつでも素朴な解と一致した
- 使った出典：kanpurin「典型問題メモ」（インライン DP の定義と一覧）、drken の Qiita「DP の配列使いまわしテクニック」、Kazun の ABC271 E、drken の ABC372 F、KCPC の ABC372（ずらしの考え方と更新後の値を読む誤り）、Series_205 の EDPC W、kanpurin の ABC203 E、kmjp の ABC480 G、ACL の document_ja。atcoder.jp・codeforces.com は開いていない
- 新しく noai を確かめたドメイン：inamori.hateblo.jp（noai・noimageai の指定なし。問題の補充の候補の裏付けに読んだだけで、本文には使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc480_g | summary | 整数列を長さ 2 以上の連続する区間に分けるとき、各区間の最大値と最小値の差の和の最小を求める。 | https://kmjp.hatenablog.jp/entry/2026/10/17/0930 （本文の行はこの要約で書いた） |
| abc271_e | evidence | https://kazun-kyopro.hatenablog.com/entry/ABC/271/E を足す | 今の evidence（kanpurin の一覧）は問題名を挙げるだけで解法がない |
| abc203_e | evidence | https://kanpurin.hatenablog.com/entry/2021/05/31/041904 を足す | 同上。こちらは問題ごとの解説 |
| abc372_f | evidence | https://kcpc.hatenablog.com/entry/2024/09/22/201128 を足す | 今の drken の記事は頂点を縮める別解で、ずらしの説明はタグだけ |
| abc372_f | approach | 「全体のシフトを添字のずらしで表し、追加の辺の端だけ更新する」は保つ（本文の節 global-shift と一致） | — |

- tdpc_target は alternatives に inline-dp 用の summary があるが、fix_problems は主の summary（lis 用。「入れ子（次の円の内側にある）」を含む）で行を作った。どちらでも問題はないので、そのままでよい

## 用語集への提案

なし（状態・遷移・緩和・ならし計算量は既存の anchor にリンクした）

## 手引きへの提案

- §5 の dp に「1 本の配列で書き換えてよいか」の規則があるので、インライン DP の「その行で読む値を先にすべて集めてから書き込む」もこの規則の例として足すとよい（ABC372 F の追加の辺・ABC203 E の同じ行の黒いポーンで起きる。KCPC の記事が実例）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- abc334_f（ABC334 F. Christmas Present 2、diff 1813）：家から出て袋に K 個までのプレゼントを持ち、N 人の子どもに順に配る。途中で家に戻って補充できるとき、移動距離の合計の最小を求める（問題文は読んでいないので、要約は解説のコードと説明からの推定。台帳に入れるときに確かめる）。状態（今の位置, 持っている個数）の表で、次の子へ進む遷移は全体への一律の加算（オフセット）と個数の添字のずれ、家へ戻る遷移だけが全体の最小からの 1 点の書き込みになる。インライン DP の 3 つの道具（写し・オフセット・ずらし）がそろう練習として、practice に足すことを提案する。裏付け：https://inamori.hateblo.jp/entry/2023/12/28/193744（check_noai で noai なし）
- abc353_g（dp-segment-tree の例題）は catalog の level_evidence に名があるが、例題は 1 ページ 1 つの規則なので足さない

## 未解決の点

- abc271_e で到達できないときの出力（-1 と思われる）は解説で確かめきれなかったので、本文は「問題の指定に従う」と書いた
- dp_w の得点 a の範囲は解説に明記がなかった。「a は負のこともある」は、すべて正なら全部を 1 にすればよいという理由から書いた（制約の数値は書いていない）
- 力試し abc480_g の方針は、本文の with-monotonic-stack の節の DP（C = 0、長さの下限 2）にほぼそのまま当たる。節の例を、問題そのものではなくコストに定数 C を足した一般形にして重ならないようにしたが、方針が見えやすすぎるならメインの判断で節の例を変える
- visual は priority 2 の静的な図で、図は「表の各行で変わるマスを色付けし、1 本の配列の書き換えに置き換える」1 枚にした（動く図の置き場の div は置いていない）
- 前提の dp-segment-tree・関連の dp-dimension-reduction・lazy-segment-tree-patterns は stub なので、anchor を付けずにページへリンクした

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：「最大 × 長さ」でも同じという文を消し、「最大だけ（最小だけ）ならスタック 1 本」とし、長さに比例する項があるとならし $O(N)$ が崩れてこの方法だけでは足りない、という制限を書いた
- 指摘 2：各 $i$ でまず始点 $i-1$ に $\mathrm{dp}[i-1]$ を 1 点で書く手順と、スタックの底なら $q = -1$ とすることを本文に足した
- 指摘 3：本文の節の例（$C$ + 最大 − 最小、長さの下限）はそのまま残し、力試しの方針を「問題のコストと長さの条件が節の例とどこで違うかを確かめ、節の DP のどこを変えるかを決める」に変えて、答えを直接書かないようにした。節の例そのものを変える（案 b の前半）はコード片と本文の作り直しになるので採らなかった。ABC480 G を節の例題に格上げするか（案 a）はメインの判断に回す（下の提案）
- 指摘 4：$i < L$ では `prod` が `e()` ＝ $+\infty$ を返し、そのまま書いてよい（加算は値の幅までなのであふれない）を足した
- 指摘 5：EDPC W の解法の詳細に $N, M \le 2 \times 10^5$、$\lvert a \rvert \le 10^9$、和の絶対値 $2 \times 10^{14}$ までを書き、参考に drken「EDPC (Educational DP Contest) W - Intervals」を足した
- 指摘 6：確認問題 1 を「段ごとに辺の集合から高々 1 本を使えるとき、段の中を順に緩和すると何が誤るか・どう直すか」に変えた（落とし穴の「同じ行で書き換えた値を読む」につながる）
- 指摘 7：90 行のリンクを dp-segment-tree#values-on-segment-tree に、ACL の囲みの「標準の型」に lazy-segment-tree#acl-standard へのリンクを足した
- 指摘 8：row-diff.svg の viewBox を 700×330 から 440×486 に縮めた（題を 2 行に、凡例を縦に、配列 dist を表の下へ移し、右下の説明文 4 行は本文 57 行と重なるので外した）。render_svg.py の 360px・720px で文字の重なり・はみ出しがないことを見た
- 指摘 9：本文 151 行のリンクを monotonic-stack#procedure（左で初めて大きい位置・狭義減少のスタック）にした。front matter の related の `monotonic-stack#dp-transition` は catalog どおりなので変えていない（下の提案）
- textlint は警告が 17 件（1 件増は確認問題 1 の題と答えの長さ。数式を含むため）でエラー 0

## 検証の後の提案

- abc480_g（指摘 3）：力試しの方針はぼかしたが、節の例と問題の解き方はほぼ同じである。台帳と catalog で abc480_g を節 with-monotonic-stack の例題（黄）に移し、力試しを空にするか別の問題に替えるかを、メインで判断してほしい
- front matter の related の `monotonic-stack#dp-transition` を `monotonic-stack#procedure` に変えることを提案する（dp-transition はスライド最小値の deque の節で、この節が使うスタックの区間の見方は procedure にある）
- dp_w の evidence の drken の記事（2021/08/11/005634）は、本文の参考にも足した。checked に 2026-10-21 を入れてよい（検証役が確かめた）
