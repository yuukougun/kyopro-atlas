# counting-dedup（重複の除き方）の報告と提案

- 書いたファイル：docs/comb/counting-dedup.md、snippets/counting-dedup/leftmost.{cpp,yaml}、snippets/counting-dedup/partition-dp.{cpp,yaml}、docs/img/counting-dedup/leftmost-embedding.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections から `pitfall-order` を外した（手引き §14-1）。anchor は `## 落とし穴 {#pitfalls}` の下の `### グループの順序を区別して K! 倍に数える {#pitfall-order}` として残したので、URL の `#pitfall-order` はそのまま使える
- 検査：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 期待と違う 0／textlint エラー 0・警告 9（数式を含む文の長さ、図の代替テキストの長さ、数式まわりの助詞の重複の誤検出）
- 図：leftmost-embedding.svg を render_svg.py で 360・720 幅にして目で確かめた。visual は priority 2（static）なので動く図は作っていない
- 使った出典：kmjp（arc077_b）、drken（abc171_f・abc180_f・abc311_f・abc310_d・abc130_e）。題名は記事の title から取った。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc311_f | summary | 一部のマスが黒い N×M のグリッドで、白いマスを黒く塗り、どの黒いマスについても真下と右下のマスが黒かグリッドの外になるようにする方法の数を求める。 | https://drken1215.hatenablog.com/entry/2023/07/24/182416 （本文の行はこの要約で先に書いた） |
| abc311_f | approach | 各列の黒いマスは下側にまとまるので、列ごとの上から続く白の数の列と盤面が 1 対 1 に対応する。右の列の白の数 ≤ 左 + 1 の条件で、累積和の DP O(NM) | 同上 |
| abc311_f | checked | 2026-10-21 | 同上 |
| arc077_b・abc171_f・abc180_f | checked | 2026-10-21（evidence の記事で問いを確かめた） | 各 evidence |
| abc180_f | 備考 | 記事の題名は「(橙色, 600 点)」。本ページは diff 2419 で力試しのまま | https://drken1215.hatenablog.com/entry/2020/10/21/145700 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 重複度 | multiplicity | 数え上げで、1 つの対象を作る作り方（数えたもの）が何通りあるかを表す数である。どの対象でも同じ値 c なら、作り方の数を c で割れば対象の数になる。 |
| 代表元（追記） | representative | 既存の定義（Union-Find の根）に「数え上げでは、同じ対象を作る作り方のうち規則で 1 つだけ選んだもの。代表元だけを数えれば各対象を 1 回ずつ数えられる（正規形とも言う）」を足す |
| 部分列 | subsequence | 列からいくつかの要素を、順序を保ったまま取り出してできる列である（連続でなくてよい）。連続して取り出したものは部分文字列（部分列のうち連続なもの）と言う。今回は本文で string/subsequence-matching へリンクした |

## 手引きへの提案

- §14-1 で落とし穴の節を sections から外すとき、骨格の sections に `pitfall-*` の anchor があり index などから既に指されている場合は、`## 落とし穴` の下に同じ anchor の `###` を立てて残す、という扱いをそろえるとよい（今回そうした）

## 問題の補充の候補（abc319 以降）

| 問題 ID | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- |
| abc390_d（diff 1607、台帳で確認済み） | N ≤ 12 個の袋の石を袋ごと別の袋へ移す操作の後、石の数の XOR としてありうる値の種類数 | #min-index の練習。最後の状態は袋の集合の分割に対応し、最小番号から組を決めてベル数通りを全列挙する（「異なる値の数」は set で数える） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc390-d.html 、https://yuulis.hatenablog.com/entry/ABC-390-D （台帳の evidence。今回は読み直していない） |

- abc319 以降で「最も左の埋め込み」「操作で作れる列の種類数」の型の ABC は見つけられなかった（ap.py の search は題名の検索なので、型での検索は第三者のまとめで探す必要がある）

## 未解決の点

- `#in-dp` の「直前と違う」の型は、台帳の agc031_b（dp-sequence-partition の例題）の approach の要約をもとに書き、drken の解説（https://drken1215.hatenablog.com/entry/2019/03/17/130800）は読み直していない。検証で確かめてほしい
- ARC077 D の制約（n の上限）は kmjp の記事のコードの配列の大きさから「10^5 程度」と読めるだけなので、本文には書いていない
- 骨格の related に inclusion-exclusion-dp・dp-sequence-partition・binomial-precompute・subsequence-matching がないが本文からリンクした。related に足すかはメインの判断

## 検証（verify/counting-dedup.md）への対応

- 1（ABC180 F の要約）：本文の行を「自己ループのない（多重辺は許す）N 頂点 M 辺の無向グラフで…」に直した。台帳 abc180_f の summary（本体と alternatives 2 つ）と、同じ要約を持つ counting-mindset・counting-labeled-graphs の行の直しは、検証の「台帳への提案」の表のとおりメインに頼む
- 2（#in-dp の 2 つ目の型）：操作を「同じ色の 2 か所を選び、その間をその色で塗る」と一言書き、型の名前を「何も変えない操作を除く」に変えた。節の見出しと front matter の sections の title も合わせて直した（anchor `in-dp` は変えていない）。docs/index/comb.md の同じ見出しの行は gen_site.py で作り直してほしい
- 3（ABC311 F の方針）：条件の式・累積和・計算量を外し、「隣り合う列の白の数にどんな条件が要るかを考える」で止めた
- 4（#first-obstacle へのリンク）：**採らなかった**。inclusion-exclusion-dp は stage が stub で、check_pages が「節へのリンクは draft 以降のページにだけ付ける」とエラーにするため、ページへのリンクのままにした。inclusion-exclusion-dp が draft になったら `#first-obstacle` を付けるとよい（提案）
- 5（leftmost.cpp の計算量）：逆階乗と sigma − 1・sigma の累乗を前計算する形にし、core を O(n + k) にした。check_snippets で期待と違う 0
- 6（図の 360 幅）：マスと注記を左へ 30 寄せ、注記の font-size を 12→14（「代表でない」などは 14→15）に上げた。viewBox は 560 のまま、720 幅で重なり・はみ出しがないことを render_svg.py で確かめた
