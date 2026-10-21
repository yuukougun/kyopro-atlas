# matrix-power の報告（工程8b・バッチ b1）

- 書いたファイル：docs/math/matrix-power.md、snippets/matrix-power/matpow.{cpp,yaml}、snippets/matrix-power/min-plus.{cpp,yaml}、docs/img/matrix-power/fast-power.svg、docs/img/matrix-power/adjacency-power.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（title・anchor・level とも骨格のまま）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 24。数式を含む文の長さ・読点の数、要点の囲み全体を 1 文と数える誤検出、台帳の要約の助詞の重複、数式の括弧の対応の誤検出）
- 図：catalog の visual（static・priority 2）を静的な SVG 2 枚にした（繰り返し二乗法の K = 13 の図、隣接行列 A と A² の図）。フィボナッチの「ベクトルに行列を掛ける」式は KaTeX で本文に書いた。動く図は作っていない
- 使った出典：参考の節のとおり。hossie 氏の Qiita 記事は本文が画像なので、qiita-image-store（S3）の G のスライド画像 2 枚を読んだ（ABC305 G の状態の作り方の確認）。新しく noai を確かめたドメインはない（qiita.com・hatenablog・ikatakos.com・zenn.dev・oraclesqlpuzzle・github.com は付録 B にある）
- 確かめた事実：ABC305 G の禁止文字列の長さ 6 以下（merom686 の「長さ 6 にそろえる」と hossie のスライドの「6 文字の場合も 64×64」から）、EDPC R の制約（Series_205）、ABC199 F の係数（hamayan）、ABC204 F の 64 次の行列と mod（kmjp）、ABC009 D の制約と単位元（drken）、ABC256 G の制約と O(D log N)（drken）、典型90 005 の B ≤ 1000 と O(B² log N)（drken）、ABC458 F の制約と状態数（ikatakos の解法の部分）、ABC456 F の問い（ikatakos の解法の部分と loop0919）。計算量の表の数値は Python で計算した。std::identity との名前の衝突は check_snippets（g++-15・-std=gnu++23）の実際のエラーで確かめた

## 台帳への提案

- abc456_f｜alternatives（matrix-power）の summary と本体の summary｜「各日を費用 A_i で休日にでき、両隣が休日の日は費用なしで休日にできるとき、K 日以上続く休日を作る費用の最小を求める。」｜今の「区間 [l, r] の日をすべて休日にする費用の最小を、多数のクエリについて答える」は誤り。入力にクエリはなく、長さ K 以上の連続した休日を 1 つ作る最小費用を問う（区間の積をセグメント木で取るのは解法の道具）。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0502_abc456 （解法の節）・https://zenn.dev/loop0919/articles/f779f54ccdfedf 。本文の行は先に正しい要約にした
- abc458_f｜alternatives（matrix-power）の summary｜「英小文字からなる長さ N（≤ 10^9）の文字列のうち、与えられた K 個の文字列をどれも部分文字列に含まないものの個数を 998244353 で割った余りで求める。」｜「（詳細は執筆時に確かめる）」を外す。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0516_abc458 （解法の節：K ≤ 10、各長さ ≤ 10、英小文字、998244353）。本文の行は先にこの要約にした
- abc199_f｜summary（本体と matrix-power 用）｜「辺を1本」→「辺を 1 本」｜textlint のエラー（半角と全角の間の空白）。本文の行は先に直した
- abc305_g｜evidence｜https://qiita.com/hossie/items/bb08bf6abe92b2f85269 を足す｜状態（末尾の数文字）と行列の作り方が G のスライドにある。今の evidence の merom686 の記事は方針の概略だけ
- abc199_f・abc204_f・abc009_4・abc256_g・typical90_e・abc458_f・math_and_algorithm_aw・dp_r｜checked｜2026-10-21｜evidence の解説で問いと方針を確かめた（checked が null のもの）

## 用語集への提案

- 歩道｜walk｜グラフで、辺を順にたどる経路のうち、同じ頂点や同じ辺を何度通ってもよいもの。長さはたどった辺の本数。競技プログラミングの問題文では「パス」と呼ぶこともある（本文ではリンクしていない。リンクするならメインで判断）
- 半環｜semiring｜「足し算」と「掛け算」の 2 つの演算の組で、足し算は結合法則と交換法則を満たして単位元（零元）を持ち、掛け算は結合法則を満たして単位元を持ち、掛け算が足し算に分配し、零元との掛け算が零元になるもの。(min,+) や (max,+) が例で、この演算で作った行列の積は結合法則を満たす（手引きの「群・環・体の語は使わない」に近いが、catalog の別名と節の題名に「半環」があるので本文では定義して使った。用語集に載せるかはメインで判断）

## 手引きへの提案

- §9 に「`using namespace std;` の下では、`identity`（C++20 の std::identity）など std の名前と同じ関数名を使わない。g++-15 の -std=gnu++23 で ambiguous のエラーになる」を足すとよい。単位行列の関数でよく踏む
- 行列を使うページ（matrix-power・segment-tree-monoids・dynamic-dp・linearity-of-expectation）の流儀をそろえるため、§6 に「状態のベクトルは列ベクトルで、遷移は v' = Av（a_ij は j から i への係数）」を足すとよい。隣接行列（行が出発）とは転置の関係になることも本文で触れた

## 問題の補充の候補

catalog の数（例題 3・練習 6・力試し 2）で足りている。frequency_evidence にある最近の問題で、ページに載っていないものを挙げる（どれも台帳にない・未確認）。

- abc469_g（G. K-nacci Operations、diff 2804・発展。ap.py で実在を確かめた）：frequency_evidence に挙がっているが、問いと解法は第三者の解説で確かめていない。発展の帯なので、このページより linear-recurrence-fast の候補かもしれない
- abc293_e（E. Geometric Progression、diff 1453・水。ap.py で確かめた）：台帳では geometric-series-mod の練習。2×2 の行列の累乗でも解ける別解として、このページの練習か本文の参照にできる（研究 06 §7.2 の記述。第三者の解説での裏付けは geometric-series-mod の台帳の evidence を使える見込み）
- abc129_f（F. Takahashi's Basics in Education and Learning、diff 2621・発展。ap.py で確かめた）：桁数ごとに 3×3 の行列を累乗する型（研究 06 §4.6）。台帳では geometric-series-mod の力試し。本文の合成の節の「周期のある遷移」に近い
- abc236_g（G. Good Vertices、diff 2438）：(max,min) の行列のダブリングの代表。研究 06 §7.5 で未確認とされていて、本文では問題 ID を出さず「ボトルネック」の型だけを書いた。第三者の解説で確かめられれば、半環の節の力試しの候補

## 未解決の点

- 依頼の文面ではレベルが「水」だったが、front matter と catalog は「青」なので、front matter（正）に従って青のまま書いた（黄の節 2 つはそのまま黄）
- ABC305 G の M の上限と禁止文字列の長さの上限は、第三者の解説から間接的に確かめた（長さ 6 以下）。M の上限は本文に書いていない
- アルゴ数学 057 の K の上限（解答例のコードは K = 2, 3, 4 に対応）は本文に書かず「K は小さい」とした
- SVG は手元に描画の手段がない（ブラウザのライブラリ未導入）ので、目で確かめていない。XML として正しいことと、文字の幅の見積もりで枠に収まることだけ確かめた。検証で画像にして確かめてほしい
- 半環の表の (max,min) と (OR,AND) の行は一般的な事実として書き、問題での裏付けはない（abc236_g が未確認のため）
- プロファイル DP の節の「上下の反転で状態をまとめる」は一般論として書いた。具体的な問題での裏付けはない

## 使用量の目安

- 道具の呼び出し：約 45 回（Web 取得 13 回・検索 2 回を含む）

## 検証の指摘への対応（2026-10-21）

- 1〜8 は直した（1：snippets の `using Mat` を外して型を書き下した。2：確認問題の $-\infty$ の記述を、値の下限の見積もりと INF との和を飛ばす注意に替えた。3：本文に「最後の 2 乗は使われない」の 1 文を足し、図と代替テキストを「使う 2 乗 3 回」にした。4：照合の状態と ABC458 F の方針を、接尾辞に禁止文字列を持つ状態（fail の先も含む）を捨てる形にした。5・6・7・8 は指摘の直し方のとおり。あわせて半環の表の (max,min) の行に「ちょうど $K$ 辺の歩道のうち」を添えた）
- 9 はページを直していない：台帳の summary の直しが要るので、上の「台帳への提案」（abc456_f・abc458_f・abc199_f）をメインが反映してから fix_problems を流してほしい
- 手引きへの提案（追加）：指摘 1 のとおり型の別名をやめると、行列の型 `vector<vector<long long>>` が関数の宣言ごとに並んで長くなる（min-plus.cpp の `mul` は 1 行に収まらず折り返した）。行列を扱うページ（segment-tree-monoids・dynamic-dp など）でも同じになるので、§9 の例外に「行列の型の別名」を足すかはメインで判断してほしい
