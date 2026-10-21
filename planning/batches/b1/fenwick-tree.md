# fenwick-tree の報告（工程 8b・b1）

- 書いたファイル：docs/ds/fenwick-tree.md、snippets/fenwick-tree/{acl-usage,own-bit,count-by-value,range-add-sum}.{cpp,yaml}、docs/img/fenwick-tree/boxes.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の title を見出しに合わせて短くした（anchor は変えていない）
  - what-it-does：何ができるか（一点加算・接頭辞の和と逆元）
  - invariants：保つ性質（t[i] は区間 (i − lowbit(i), i] の和）（YAML のため引用符で囲んだ）
  - operations：各操作の手順（add は上へ、sum は下へ。線形時間の構築）
  - boundaries：境界（添字の変換・i = 0・符号なし整数）
  - variants：変種（差分の BIT・BIT 2 本・2 次元 BIT・接頭辞の max）
  - binary-search：BIT 上の二分探索
  - choosing：使い分け（定型の節だが、骨格の anchor を変えないため sections に残した）
- 検査の結果：check_pages エラー 0・警告 0／check_snippets 4 本すべて一致／textlint エラー 0・警告 18（数式を含む文の長さ・`[l, r)` などの括弧の対応・要点の signs の行の助詞「に」。どれも数式による誤検出）／fix_problems --check は ds/segment-tree-on-values.md の 3 行（別の担当のページ）だけが出て、このページの行はない
- 動く図：catalog の visual は priority 2。作っていない。静的な SVG（boxes.svg：N = 8 の箱の並び、sum(7) と add(3) で通る箱）で代え、本文の invariants の節に div をコメントで置いた（`data-viz="fenwick-tree"`、config 例 `{"n": 8, "ops": [{"type": "sum", "i": 7}, {"type": "add", "i": 3}]}`）。作るなら、各ステップで「今の i（2 進数）・足す/直す箱・次の i への式」を caption にする

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc340_e | evidence | 第三者の解説を BIT（差分の BIT）か区間加算・一点取得で解いたものに差し替えるか足す | 今の tayu0110 の記事は平方分割で解き、想定解を遅延セグ木と書くだけで、1 周を超える分の扱いもない。「区間加算・一点取得に帰着する」ことの裏付けにはなるが、BIT の解法そのものの裏付けではない |
| abc221_e | summary | 先頭 ≤ 末尾となる長さ 2 以上の部分列の個数を mod 998244353 で求める。 | 答えを mod で出す点が要約にない（note の記事の解法が mod の逆元を使う）。問題文の mod の値は記事に明記がないので、メインで ap.py 等で確かめてほしい |
| abc351_f | approach | 「座標圧縮して、自分以下の個数と和を BIT 2 本で数える（値の順に処理し、位置の BIT で数えてもよい）」 | torus711 の記事は値の順に処理して位置の BIT を使い、oraclesqlpuzzle は座標圧縮した値の BIT を使う。どちらの裏付けもある |
| abc231_f | approach | 「A の昇順（同じ A は B の降順）に並べ、B を座圧した BIT で数える。同じ (A, B) はまとめて入れてから数える」 | zenn（m193h）の記事のソート順と同じ組の扱い |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 逆元（演算の） | inverse-element | 演算 ∘ と単位元 e について、x ∘ y = e となる y を x の逆元という。和なら −x、XOR なら x 自身。min・max には逆元がない。mod での乗法の逆元は mod-inverse のページを参照 |
| lowbit | lowbit | 正の整数 i の 2 進数で、最下位の 1 だけを残した値。C++ では `i & -i`。BIT の箱の長さを決める |

本文では「逆の操作」と書き、用語集へのリンクはまだ張っていない（用語集に入れば、what-it-does の節の「逆の操作」に張るとよい）。

## 手引きへの提案

- §13.1 の定型の節（使い分け {#comparison}）と、骨格の sections にある `choosing` の anchor が食い違う。見本の lazy-segment-tree も `## 使い分け {#choosing}` を sections に載せている。どちらに寄せるかを決めてほしい（このページは骨格の anchor を変えない規則に従い choosing のまま）
- sections の title に `(… , …]` のようにカンマや角括弧を含むと、flow 形式の YAML が壊れる。骨格を作るとき・執筆者が title を直すときは引用符で囲む、と手引きに一言あるとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- |
| abc285_f | 一文字の書き換えを挟みながら、部分文字列が「全体をソートした文字列」の部分文字列になっているかを答える | 文字ごとの個数の BIT 26 本と、隣り合う文字の大小の逆転を 0/1 で持つ BIT（diff 1876。練習か力試し） | https://qiita.com/recuraki/items/38a850c4aad563853149（research/05-ds §5 の候補。記事はこの作業では読んでいない） |

例題・練習の数は手引きの目安（例題 1〜3、練習 2〜6、力試し 0〜3）を満たし、abc319 以降の問題（abc351_f）も 1 問ある。補充は必須ではない。

## 未解決の点

- abc340_e の evidence（上記）。本文の方針は問題の構造から自分で書いた
- abc221_e の mod の値：本文では「mod での逆元」「fenwick_tree<modint998244353> が使える」と書いた。998244353 であることは記事から直接は確かめていない（記事は modinv(2) を使うとだけ）。メインで確かめ、違えば練習の方針の 1 文を直す
- abc185_f の値の上限は記事で確かめられなかったが、本文では値の上限に触れていない
- 新しく noai を確かめたドメイン：なし（note.com の syamashi の記事 n c5b5876e0514 は meta の指定なし、記事に AI 利用を断る記述なし。付録 B の「記事ごとに確かめる」の対象として足してほしい）
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 11 回（WebFetch 9・題名の確認の curl 1 回分）
