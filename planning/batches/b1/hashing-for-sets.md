# hashing-for-sets（集合・多重集合のハッシュ）の報告と提案

- 書いたファイル：docs/string/hashing-for-sets.md、snippets/hashing-for-sets/{range-multiset,prefix-set,update-fenwick,mod-k}.{cpp,yaml}、docs/img/hashing-for-sets/prefix-sum-hash.svg
- front matter で変えたもの：complexity（`前計算 O(N)、比較 1 回 O(1)、BIT と組むと更新・比較 O(log N)。誤判定の確率は比較 1 回あたり 2^-47 以下`）・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0（abc424_f の label は台帳の題名の先頭の空白を除いた形に fix_problems で直した）、check_snippets 期待と違う 0（4 本・ACL の fenwick_tree を 1 本で使用）、textlint エラー 0・警告 15（数式の中の `[`・`(A, B]`・`[l, r)` による括弧の対の誤検出、数式を含む文の長さと読点、図の代替テキストの長さ、参考の題名の長さと全角の「Ｓｋｙ」。どれも規則の誤検出か、元の題名のまま）
- 図：静的な SVG 1 枚（値ごとの乱数の表、a と b の累積、区間のハッシュを両端の差で得る図）。catalog の visual は priority 2・static なので動く図の div は置いていない
- 事実の確認：コード片の期待出力は Python の素朴な全探索で作った。和のハッシュの衝突確率（個数の差の 2 進の付値 k で 2^(k−64) 以下）は自分で導いた（下の未解決の点）
- 使った出典：trap.jp（新しいドメイン。check_noai で noai の指定なし）・yamate11.github.io（新しいドメイン。check_noai で noai の指定なし）・merom686.hatenablog.com・ikatakos.com（ABC424・ABC455 の解説の部分だけ）・ACL document_ja/fenwicktree.md

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc455_g | summary | 現れる値がどれも同じ回数ずつ現れる連続部分列を、与えられた条件の値ごとに数える。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0425_abc455 （解説の部分。問題文の節は読んでいない） |
| abc455_g | approach | 「各値がちょうど B 個」は B 回で XOR が 0 になる符号化の累積の一致と尺取り、「ちょうど B 種類が同じ個数」は乱数の和を使って B·S_i − H·i の一致に直し尺取りで数える | 同上 |
| abc424_f | title | `Adding Chords`（先頭の空白を除く。ap.py の値も先頭に空白がある） | ap.py show abc424_f |
| abc367_f | evidence | yamate11 の記事は ABC367 F を多重集合のハッシュの例として挙げるだけで、merom686 の記事も手法の詳細がない。解き方まで書いた第三者の解説を足すとよい（未発見） | — |

abc455_g の summary は、解説の記述から「どれも同じ回数ずつ」と「B 個ずつ／B 種類」の 2 つの数え方があることまでは分かったが、問題文の正確な条件（B_k が何を表すか）は確かめきれなかった。本文の行はこの提案の文にしてある。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| Zobrist hashing | zobrist-hashing | 値（要素）ごとに独立な乱数を割り当て、集合を要素の乱数の XOR で表すハッシュ。要素の追加・削除が XOR 1 回で済む。多重集合は XOR の代わりに和を使う。 |
| ハッシュの衝突 | hash-collision | 異なるものが同じハッシュの値になること。乱択のハッシュでは、衝突の確率を比較の回数（等しい組を数えるなら組の数）と掛けて全体の誤判定の確率を見積もる。 |

本文では用語集へのリンクは半開区間（half-open-interval）だけ。「誕生日のパラドックス」は hash-safety で扱う想定で、本文では語だけ出した。

## 手引きへの提案

- §5 string の「ハッシュは衝突の確率と mod・基数の選び方（乱択）に必ず触れる」に、集合のハッシュでは「等しい組を数えるときは組の数（N^2/2）で見積もる」も足すとよい（多くのページで 32 ビットの誤りが起きやすい点）

## front matter・catalog への提案

- related に spf-sieve・two-pointers を足す案（積が立方数の判定と、「ちょうど k 個」の条件を尺取りで課す場面で本文からリンクしている）
- prerequisites は prefix-sum・bit-operations のままでよい。黄の節 multiplicity-mod-k は本文の先頭で parity・prime-exponent-vector を追加の前提として示した

## 問題の補充の候補

例題 2・練習 2・力試し 1 で手引きの数の目安を満たすので、新しい候補は探していない。練習を増やすなら「区間の各値が偶数個」（XOR の累積）を問う ABC の E・F を探すとよい。

## 未解決の点

- 和（mod 2^64）の衝突確率 2^(k−64) の見積もりは自分で導いた（c·r ≡ t (mod 2^64) の解は 0 個か 2^k 個）。yamate11 の記事は素数を法とする場合だけを証明し、2^64 は実用上よいと書く。検証役に確かめてほしい
- ABC367 F の入力の形（区間が 1-indexed の閉区間か、値の範囲）は確かめていないので、本文は「問題文の区間を半開区間に直す」とだけ書いた
- hash-safety・randomized・mo-algorithm・segment-tree は stub なので、節へのリンクは張らずページへのリンクだけにした

## 検証の指摘への対応（工程8b）

指摘 1〜9 はすべて直した。採らなかった指摘はない。

- 1（直すべき）：ABC455 G の要約を検証の案の文にし、力試しの方針の先頭を「求める 2 つの個数を別々に数える」にした
- 2：使い分けの Mo の行を「1 つの区間の中の各値の個数」に絞り、2 つの区間の比較では見積もりがそのまま成り立たないことを添えた
- 3：乱数を $z(v)$（コード片は `z`）にし、区間は $[l, r)$ のまま。コード片の `rr` を `r` に戻した。図の「乱数 r(v)」も「乱数 z(v)」に
- 4：front matter の complexity を要点に合わせた（XOR で 2^-64、和で 2^-47 以下・個数 2×10^5 以下）
- 5：32 ビットの確認問題を「Q 回の比較」と「等しい組を数える」の比較に変えた
- 6：区間を $(A, B)$ にし、「交差する弦があるかを判定できる」に改め、円を切ったときの交差の条件を 1 文足した
- 7：図の a を (3, 1, 3, 2, 4) にして S = 0, 14, 51, 65, 155, 216（S[4] − S[1] = 141、S[3] = 65）とし、累積の箱の下に添字 0〜5 を付けた。代替テキストの数値も直した
- 8：prefix-set.cpp の `rand_of`・`prefix_hash` をやめて main の中のループにし、update-fenwick.cpp の `update` をクエリ処理の中に書いた（`same` は判定の関数なので残した）
- 9：区間の集合の段落に「クエリを右端の順に並べて最後の出現位置を BIT に持つ方法（オフライン）」と Mo's algorithm を名前とリンクで添えた

### 台帳への提案の訂正

- abc455_g の summary は上の表の文ではなく、「各値が同じ回数ずつ現れる連続部分列のうち、各値が B 回ずつのものと、B 種類の値からなるものの個数を、与えられた複数の B ごとに求める。」にする（根拠：検証役が web.archive.org の写しで ikatakos の問題文の節を確認）
- abc455_g の approach の先頭も「求める 2 つの個数を別々に数える」に合わせる
- checked に 2026-10-21 を入れてよい（検証役の確認）：abc250_e・abc238_g・abc424_f・abc455_g
