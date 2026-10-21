# digit-dp-advanced の報告（b3）

- 書いたファイル：docs/dp/digit-dp-advanced.md、snippets/digit-dp-advanced/{two-numbers,lower-upper,carry,digit-product,count-sum}.{cpp,yaml}、docs/img/digit-dp-advanced/{multiple-numbers,carry}.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま。sections は骨格のまま（5 節すべてに anchor を付けた）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check --page（直すべき行 0）、check_snippets（5 本・期待と違う 0。どれも小さい入力で全探索と assert で比べる）、textlint（エラー 0・警告 3。数式を含む文の長さと、ABC138 F の方針の数式の中の読点で、誤検出）
- 図：multiple-numbers.svg・carry.svg を render_svg.py で 360px・720px の PNG にして目で確かめた。visual は priority 3 なので動く図は作っていない（静的な図 2 枚で、catalog の「複数の数の桁とフラグ」「繰り上がりを下の桁から運ぶ」の両方を描いた）
- 使った出典：
  - https://drken1215.hatenablog.com/entry/2019/02/04/013700（フラグの土台）
  - https://kanpurin.hatenablog.com/entry/2020/04/07/182948（応用の型の分類。問題の一覧だけで、解法は書かれていない）
  - https://www.luogu.com.cn/article/ptoqryzp・https://kyo-pro.hatenablog.com/entry/ABC231E（ABC231 E）
  - https://qiita.com/Kiri8128/items/a0786a690232623bd0f6・https://zenn.dev/ichinoseac/articles/199cf94ed49926（ABC208 E・ABC235 F）
  - https://www.cnblogs.com/sonnety-v0cali0d-kksk/p/ABC317_sonnety-summary.html（ABC317 F）
  - https://geam1113.hatenablog.com/entry/2022/01/22/174557（ABC235 F）
  - https://kmjp.hatenablog.jp/entry/2021/03/06/0900（ABC194 F）・https://kmjp.hatenablog.jp/entry/2019/08/20/0930（ABC138 F）
  - 新しく check_noai で確かめたドメイン：geam1113.hatenablog.com（指定なし。付録 B への追加を提案）
- 手元で数えた数値：1〜9 の数字を 18 個まで掛けてできる積の種類は 36100（Python で集合を作って数えた）。本文の「36100 通り」はこの値

## 台帳への提案

台帳の evidence はどれも kanpurin の「典型問題メモ」だが、これは問題へのリンクの一覧で、問いや解き方は書かれていない（WebFetch で確かめた）。問題ごとの解説に替える（または足す）ことを提案する。

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc231_e | evidence | https://kyo-pro.hatenablog.com/entry/ABC231E を足す（kanpurin は分類の裏付けとして残してよい） | 混合進数への変換と繰り上がりの 2 状態の DP が書かれている |
| abc231_e | checked | 2026-10-21 | 同上 |
| abc208_e | evidence | https://qiita.com/Kiri8128/items/a0786a690232623bd0f6 を足す | 積を状態にして辞書で持つ方針 |
| abc317_f | evidence | https://www.cnblogs.com/sonnety-v0cali0d-kksk/p/ABC317_sonnety-summary.html を足す | 3 つの数のフラグ・余り・XOR が 0 の 4 通りの bit の組 |
| abc235_f | evidence | https://geam1113.hatenablog.com/entry/2022/01/22/174557 を足す | 数字の集合 2^10・個数と総和の 2 つの表 |
| abc194_f | evidence | https://kmjp.hatenablog.jp/entry/2021/03/06/0900 を足す | 未満になった後は種類数だけを持つ |
| abc138_f | evidence | https://kmjp.hatenablog.jp/entry/2019/08/20/0930 を足す | 条件の言い換えと 3 つのフラグ（下限・上限・最上位 bit） |
| abc208_e・abc317_f・abc235_f・abc194_f・abc138_f | checked | 2026-10-21 | 上の解説で問いと方針を確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 繰り上がり | carry | 足し算や支払いで、ある桁の結果が桁の大きさを超えた分を 1 つ上の桁へ送ること。下の桁から決める DP では、上の桁へ渡す唯一の情報として状態に持つ |
| 混合進数 | mixed-radix | 桁ごとに重みの比が違う数の表し方。各額面が次の額面を割り切る硬貨では、金額を「桁 i の重みが額面 a_i」の混合進数で一意に書ける |

本文ではどちらもリンクしていない（用語集に足したら、carry 節の最初の「繰り上がり」と「混合進数」へリンクできる）。

## 手引きへの提案

- §5 dp に「下の桁から決める桁 DP で上限のフラグを持つときは、『ここまでの下の桁だけを比べて上限より大きいか』を持ち、上の桁で上限と異なる数字を置いたら上書きする」を足す案。上から決めるときのフラグと向きが違い、取り違えやすい（本文の carry 節の末尾に書いた）

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL | 備考 |
| --- | --- | --- | --- |
| abc182_f（Valid payments、diff 2121） | 各額面が次を割り切る硬貨で X 円を払うとき、払う硬貨とお釣りの硬貨に同じ額面が現れないような「お釣りの額」の数を数える（繰り上がりの有無を状態にした数え上げ） | https://kyo-pro.hatenablog.com/entry/ABC231E（ABC231 E の難しい版として言及） | ap.py で実在と diff を確認。問いの詳細は第三者の解説で未確認。carry 節の練習（黄）に向く。執筆者が確かめる |
| abc155_e（Payment、diff 1569） | 10 の累乗の額面の紙幣で N 円を払うときの、払う枚数とお釣りの枚数の和の最小（N は巨大な数字の列） | https://kmjp.hatenablog.jp/entry/2020/02/17/0900（検索結果の題名と概要だけ確認、本文は未読） | ap.py で実在と diff を確認。水なので digit-dp の練習か、このページの carry 節の易しい練習に向く |

## 未解決の点

- ABC231 E の制約（最小の額面が 1 か・額面の数の上限）は第三者の解説で明記を確かめられなかった。本文では「額面 $a_0 = 1$」として書き、例題の詳細では「値は $10^{18}$ 程度まで」とだけ書いた。Luogu の解説の再帰の終わり（残りの金額を最小の額面の枚数とする）は最小の額面が 1 であることと合う
- ABC208 E の K の上限は確かめられなかった（解説はどれも「K が大きいので工夫が要る」とだけ書く）。本文では上限の数値を書かず「$K$ が大きいので値ごとの配列は持てない」とした
- ABC317 F の答えを mod で求めるかは確かめていない。方針には書いていない
- b1 の申し送り（handoff 1.3）で、このページへの節のないリンクが 4 か所ある。今は draft なので節へ張り替えられる：digit-dp:132（総和）→ `#count-and-sum`、digit-dp:178（2 つの数の上限・繰り上がり）→ `#multiple-numbers`（繰り上がりは `#carry`）、digit-dp:218（使い分け）→ ページのままでよい、memoized-recursion:159（状態がまばら）→ `#sparse-states`
- frequency_evidence の abc466_g（diff 3347）は発展の帯なので本文では扱っていない

## 検証の指摘への対応

- 1（直すべき）：ABC138 F の方針を「最上位 bit が違えば $y \oplus x > x > y \bmod x$ で不成立」「同じなら $y < 2x$ で $y \bmod x = y - x$」の 2 段に直した
- 2（直すべき）：multiple-numbers.svg を $B = 0111$、$y = 0101$ に替え（$x \text{ AND } y = 0$、フラグの切り替わりは x が bit 2・y が bit 1 のまま）、図の題に「x AND y = 0」を入れた
- 3：遷移を $t_x' = t_x \land (b_x = a_k)$ と書き、コードの `ntx = tx && bx == la` との対応を添えた
- 4：「1 回の DP で済む」に、計算量は同程度で利点は呼び直しが要らないことだと補った
- 5：carry の遷移を 3 文に分けた。「2 つの数の和の条件」の下の桁からのフラグを独立の段落にし、上限 25 の例（17・27）を添えた
- 6：両図の小さい文字を 15〜16px に上げ、carry.svg の「（上は 10 枚ぶん）」を省き、下の注記を 2 行にした。render_svg.py の PNG で確かめた
- 7：「上から決める」方法は 1 文で触れるだけにし、下の桁から決める方法を勧める形にした（落とし穴の文も合わせた）
- 採らなかった指摘：なし。textlint の警告 2 件（276 行の数式の中の読点、286 行の文の長さ）は検証で §13-8・§14-25 の範囲とされたものでそのまま
