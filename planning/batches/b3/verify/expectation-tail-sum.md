# expectation-tail-sum の検証（b3）

- 対象：docs/comb/expectation-tail-sum.md、snippets/expectation-tail-sum/kth-value.{cpp,yaml}、docs/img/expectation-tail-sum/area.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page expectation-tail-sum`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page expectation-tail-sum`：直すべき行 0
- `python3 tools/check_snippets.py -v snippets/expectation-tail-sum`：8 case すべて一致
- コード片の正しさ：`-fsanitize=address,undefined` 付きでコンパイルし、Python の全列挙（分数で期待値を出して mod に直す）と、ランダムな 300 例（N ≤ 5・M ≤ 5・0 の項と決まった項が混ざる・K は 1〜N）で比べてすべて一致。サニタイザの報告なし。計算量は x ごとに O(z) のべき乗の表と和で、全体 O(NM)。本文・要点・front matter の complexity と一致
- 数値：サイコロ 2 個の大きい方の P(X ≥ k) = 36,35,32,27,20,11（/36）、和 161/36、P(X = v) = (2v−1)/36、E[X^2] = 791/36（Σv^2(2v−1)/36 と一致）、小さい方 91/36、91/36 + 161/36 = 7、幾何分布 1/p、くじの 3、一様 N 個の最大値 N/(N+1)。すべて本文どおり
- 定理・式：E[X] = Σ_{k≥1}P(X≥k) = Σ_{k≥0}P(X>k) とその指示確率変数による説明、とびとびの値の式 Σ(v_j − v_{j−1})P(X ≥ v_j)、負の値のずらし、表の最大値・最小値・K 番目の言い換え（K = 1・N で最小・最大に戻る）、二項分布の上側の和、異なる N 個を選ぶときの C(k−1,N)/C(M,N)、E[f(X)] = Σ(f(k) − f(k−1))P(X ≥ k)（f(0) = 0）、連続値の積分の形：正しい
- 靴下（ABC352 G）：P(T > k) = e_k / C(S,k)、鳩の巣原理で k ≤ N で打ち切り、分割統治の NTT で O(N log^2 N)、C(S,k) を (S−k)/(k+1) を掛けて作る：drken の記事（制約 N ≤ 3×10^5・2 ≤ A_i ≤ 3000）と一致
- 例題 ABC295 E：`tools/ap.py show` で E. Kth Number・diff 2157 を確認。PHarr の記事で方針（x ごとに「K 番目 ≥ x」の確率を 0 の項の二項分布の上側の和で数える。r ≤ 0 なら 1、r > z なら 0）を確かめ、本文の方針・解法の詳細と食い違いなし。記事の配列の大きさ 2005 から N ≤ 2000 程度で、O(NM) は間に合う
- 力試し ABC352 G：ap.py で G. Socks 3・diff 2413 を確認。要約に手法名なし
- 参考の 5 つの URL：`tools/check_noai.py` で noai の指定なし。題名・内容は書かれたとおり（drken の 2 記事は「k 回以上かかる確率」の和と等比級数、framework の記事は包除原理と等比級数、Shizen_Tota は ABC411 E の最大値の期待値と 0 の因子の扱い）
- リンク先：inclusion-exclusion#min-max・coupon-collector#geometric・symmetry-pigeonhole-casework#pigeonhole・counting-mindset#exactly-vs-at-most・linearity-of-expectation#indicator・glossary#indicator はどれも存在し、相手は draft。continuous-probability は stub でページへのリンクのみ（§14-23 どおり）
- 図：catalog の visual（static・priority 3）の text「P(X ≥ k) の棒を積むと面積が期待値」を満たす。帯の高さ（1/36 = 8px）・幅・列の値は本文と一致。白背景・viewBox・font-family="sans-serif"・相対パス。代替テキストに列の値と合計がある
- F8：本文のサイコロ・靴下・くじの例は参考の記事の文や数値の写しではない

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact F2 | 落とし穴「0 を含む積を割り算で更新する」の最後の文 | 「どの X_i も 0 でなくなる値（各 X_i の最小値のうち最大のもの）より前は積を 0 として扱う」は境界が 1 つずれて読める。P(X_i < v) は v が X_i の最小の面の値と等しいときもまだ 0 なので、その値「ちょうど」でも積は 0 である。括弧の値を「より前」とすると、その値では積が 0 でないように読める | P(X_i < v) > 0 ⇔ v > min(X_i)。よって積 > 0 ⇔ v > max_i min(X_i) | 「各 X_i の最小値のうち最大のもの以下の値では積を 0 として扱う」とする |
| 2 | 直すとよい | clarity U8 | 確認問題 2 つ目「E[X] = Σ_{k≥0} P(X ≥ k) と書くと何が起きるか」 | 答えが落とし穴「和の始まりを 1 つずらす」の文とほぼ同じで、本文の文をそのまま問う形になっている | clarity.md U8「本文の文をそのまま問う」 | 別の小問に替える。例：「値が 0・10・1000 のどれかを確率 1/2・1/4・1/4 でとる X の期待値を、とびとびの値の式で求めよ」（(10−0)·1/2 + (1000−10)·1/4 = 252.5）や、「サイコロ 1 個の目の 2 乗の期待値を E[f(X)] の式で求めよ」 |
| 3 | 直すとよい | clarity U3 | waiting-time の節「回数に上限があるとき」の「取り出し方は C(S,k) 通りが等確率」 | 同じ種類の靴下を区別するという前提が書かれておらず、「種類が同じものは同じ」と考えた読者は C(S,k) と A_{i_1}…A_{i_k} の数え方で止まる | 読者（レート 1000 前後）として読んで | 「靴下を 1 枚ずつ区別すると、最初の k 枚の集合は C(S,k) 通りが等確率で」とする |
| 4 | 直すとよい | figure G3 | area.svg（幅 360px） | 幅 580 の viewBox が 360px に縮み、font-size 11〜13 の文字が 7〜8px 程度になる。とくに「X = 1：1/36」（11px、高さ 8px の帯の横）と「幅 1」が小さい。数字は判読できるが窮屈 | render_svg の area-360.png を目視 | 左のラベルの幅を詰めて viewBox を 500 程度に狭めるか、文字を 1〜2 大きくする。「X = 1：1/36」は帯が薄いので上へ少し離して置く |
| 5 | 直すとよい | fact F7 | exactly-vs-at-least の節「二乗の期待値」へのリンク | expectation-of-square は今 stage: draft で sections がある（difference・pairs・carry-three・variance）。「和や積のような量の二乗」は #pairs が合う | docs/comb/expectation-of-square.md の front matter | メインが `../comb/expectation-of-square.md#pairs` に張り替える（§14-23） |

## 執筆者の未解決の点について

- abc295_e の制約：PHarr の記事のコード（階乗の表 2005）から N ≤ 2000 程度と読め、O(NM) と矛盾しない。本文に制約を書かない判断で問題ない
- continuous-probability は stub のままでページへのリンクでよい。expectation-of-square は draft になったので指摘 5
- coupon-collector・linearity-of-expectation・counting-mindset から本ページの節への張り替え：#identity・#waiting-time・#kth-value はどれも本文にあり、張り替えてよい（メインの作業）
- 練習の節がない：catalog の problems_note「練習の候補が見つかっていない」のとおり。執筆者の補充候補 abc411_e（ap.py で E. E [max]・diff 1400 を確認）は本文の「値の範囲が広いとき」と落とし穴の 0 の因子にそのまま合い、練習に置く価値が高い。ただし制約（面の値の範囲）は台帳に入れるときに evidence で確かめること

## 台帳への提案

- abc295_e：evidence に https://www.cnblogs.com/PHarr/p/17266778.html を足す（執筆者の提案に同意。方針を確かめた）。checked に 2026-10-21
- abc352_g：checked に 2026-10-21（drken の記事で問いと方針を確かめた）

## 総合の判定

小さな直しで可（直すべき 0・直すとよい 5）
