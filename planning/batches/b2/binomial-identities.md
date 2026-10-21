# binomial-identities の報告と提案（工程8b・b2）

- 書いたファイル：docs/comb/binomial-identities.md、snippets/binomial-identities/{verify,rect-sum,pair-powers}.{cpp,yaml}、docs/img/binomial-identities/hockey-stick.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（7 節すべてを見出しに置いた）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件・全ケース一致。期待値は Python の math.comb と素朴な和で別に計算し、大きいケースは階乗の表で計算した値と C(2×10^6, 10^6) の一致で確かめた。rect-sum と pair-powers は小さい入力で素朴な和との assert も持つ）、textlint（エラー 0・警告 11）
  - 残した警告：sentence-length 8 件（どれも数式を含む文か、`$$` の前後の文）、max-comma 1 件（数式 $x = 1, \dots, K$ の中の読点）、no-doubled-joshi 2 件（「重複も漏れもない」の慣用句と、図の代替テキスト）
- 図：静的な SVG 1 枚（パスカルの三角形の上の hockey stick）。catalog の visual は static・priority 2 なので動く図は作らず、置き場の div も置いていない。render_svg.py で 360px・720px の PNG にして目で確かめた
- 使った出典：Kazun（abc262_e）、drken 2 本（abc154_f・arc110_d）、kmjp（arc106_d）、cirrostratus（abc290_f）。題名は各記事の entry-title で確かめた
  - 新しく noai を確かめたドメイン：cirrostratus.hatenablog.com（check_noai で noai・noimageai の指定なし。meta robots は max-image-preview:large のみ）。付録 B への追加をお願いしたい
  - ikatakos.com（abc290_f の台帳の evidence）は取得のたびに HTTP 503 で読めなかったので、cirrostratus の記事で問いと方針を確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| arc106_d | checked | 2026-10-21（evidence の kmjp の記事で、問いと「二項定理で展開し、累乗の和の積から求める。i = j の項を引いて 2 で割る」を確かめた） | https://kmjp.hatenablog.jp/entry/2020/10/26/1030 |
| arc110_d | checked | 2026-10-21（evidence の drken の記事で、問いと答え C(M+N, ΣA_i+N) を確かめた） | https://drken1215.hatenablog.com/entry/2020/12/06/070100 |
| abc290_f | evidence | cirrostratus の記事を足す（ikatakos.com が 503 で読めなかった。記事は Σ (k+1) C(N,k) C(N−3,k−1) を Vandermonde と吸収公式で N·C(2N−4, N−3) + C(2N−3, N−1) にまとめている） | https://cirrostratus.hatenablog.com/entry/2023/03/05/163234 |

ほかの使った問題（abc262_e・abc154_f）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 閉じた式 | closed-form | $\sum$ や項数が入力で変わる繰り返しを含まず、決まった回数の演算で値が求まる式である。二項係数を含む和を二項係数 1 つや $2^n$ にまとめると、階乗の表から $O(1)$ で求まる |
| ダブルカウント（2 通りに数える） | double-counting | 同じ集合の大きさを 2 つの方法で数え、結果が等しいことから等式を導く方法である。二項係数の恒等式の多くはこの方法で説明できる |

- check_pages が用語集にない anchor へのリンクをエラーにするため（§13-5 の「まだなくても書いてよい」と食い違う）、本文の「閉じた式」はリンクせず、導入の文の中で定義した。用語集に入ったら、導入の「閉じた式」に `../guide/glossary.md#closed-form` のリンクを付けてほしい

## 手引きへの提案

- §13-5 は「用語集の anchor はまだなくても書いてよい」とするが、check_pages は「用語集に anchor がない」をエラーにする。どちらかにそろえてほしい（たとえば手引きを「提案中の語はリンクせず、提案に書く」に直す）
- comb の §5 の「範囲外を 0 とする約束だけでは空の組を落とす」例に、ABC290 F の N = 2（C(N−3, k−1) が C(−1, −1) になる）も同じ型として足せる

## 問題の補充の候補

- **abc405_e**（E. Fruit Lineup、diff 1259。ap.py で確認）：4 種類の果物を、種類ごとの順序の条件を満たして並べる方法の数を求める。左端の葡萄の左にあるバナナの個数 k で分け、二項係数の積 C(A+B+k, B)·C(D−1+C−k, C−k) を k について足す。上の数が動く Vandermonde の形に近いが和の範囲が途中で切れるので閉じた式にはならず、O(C) のループで足す。本文の「閉じた式を探しすぎる」の例として練習に置ける（abc319 以降。ただし diff は水）。裏付け：https://qiita.com/testcampus/items/1389257a0c177ceb736a 、https://zenn.dev/sukenori/articles/sukenori-abc405 、閉じた式にならないことの検討は https://rsk0315.hatenablog.com/entry/2025/05/11/201737 （rsk0315.hatenablog.com は付録 B にある。qiita・zenn も付録 B）
- **abc463_g**（台帳に確認済みで probability-dp の力試し、diff 2452）：台帳の approach が「距離の期待値を二項係数の和として求める」。このページの力試しにも使えるかもしれないが、解説を読んでいないので、和をどの恒等式でまとめるかは確かめていない
- abc319 以降で、恒等式で和を閉じた式にする青の ABC の問題は見つからなかった（検索で拾えたのは恒等式の一般の解説だけ）

## 未解決の点

- ABC262 E の法（998244353 か）を evidence の記事で確かめられなかった。本文では法に触れていない
- ARC106 D の制約（K ≤ 300 など）は kmjp の記事のコードの配列の大きさからの推測しかなく、本文と方針には書いていない
- 例題 ABC154 F の方針の 4 隅の式 g(x, y) = C(x+y+2, x+1) − 1 は自分で導き、Python で小さい値を確かめたもので、出典の記事は行ごとの差の形だけを書いている
- 力試し ARC110 D の方針の「上の数が動く Vandermonde を N+1 個の因子に広げる」説明は自分で組み立てたもの（drken の記事は格子路の言い換えと母関数で示している）。r = 3, 4 の小さい場合を Python の全列挙で確かめた
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 9 回（うち 503 が 2 回）、検索 4 回

## 検証の指摘への対応（直し）

- 指摘 1〜7 はすべて採った。採らなかったものはない
  - 1：落とし穴の「約束の外」をやめ、「約束では 0 になるが、空の組を数える式では 1 としなければならないことがある」とし、$n = k = 0$ の重複組合せと ABC290 F の $N = 2$ を例に挙げた
  - 2：parity-sum の「偶奇の条件の言い換え」を 1 文にし、理由は例題 ABC262 E の方針に任せた
  - 3：$r$ 因子の数え方で「$j$ 番目の区間」を定義し、区切りを $b_j$ に数えないこと・$b_1 + \dots + b_r = m$・$r = 2$ で元の形に戻ることを補った
  - 4：hockey-stick.svg の凡例を三角形の下に移し、4 行の説明を外して viewBox を 440×510 に詰めた（360px で三角形の数がおよそ 15px）。題も「C(2,2)+…= C(6,3)」だけにした
  - 5：「次の節の」を [Vandermonde の恒等式](#vandermonde) へのリンクにした
  - 6：verify.cpp のコメントと check の名前を「上の数が動く形」にそろえた
  - 7：長方形の計算量を点の数・行の数と前計算 $O(r_2 + c_2)$ で書き直した
- 共有ファイルへの提案は、検証の提案（arc106_d・arc110_d の checked、abc290_f の evidence、付録 B に cirrostratus）に賛成する。新しい提案はない
