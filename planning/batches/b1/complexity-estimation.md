# complexity-estimation の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/complexity-estimation.md、snippets/complexity-estimation/amortized-stack.{cpp,yaml}、docs/img/complexity-estimation/operation-counts.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（1 片・期待と違う 0）、textlint（エラー 0・警告 8。助詞の重複の誤検出に近いもの、画像の代替テキストの長さ、台帳の要約の「への」、参考の題名の `__int128` 付近の括弧の誤検出）
- 図：catalog の visual（priority 2）のうち、N = 2×10^5 での演算回数の棒グラフを静的な SVG にした。制約の帯図は本文の表で代え、作っていない

## 使った出典

- E869120 典型90 の解説画像 055・072（github.com、raw の画像を読んだ）：例題の回数の見積もり（N ≤ 100、C(N,5) ≈ N^5/120）、072 は 4×4 でも経路が 28512 通りという記述
- Reputeless/tenkei_90 の 055.md（台帳の evidence）：積の余りの取り方
- drken（hatenablog）HHKB2020 C、ABC278 D、hamayan ABC196 D：練習の方針
- drken（qiita）の計算量の 2 記事：目安の数値（research 01 §4.A と同じ出典）
- qiita.com/onodera の典型90 Fortran 解答集を検索で見つけ、055 の確認に読んだ（qiita.com は付録 B にある）。本文の参考には入れていない
- 新しく noai を確かめたドメイン：なし
- 数値（階乗・ベル数・C(100,5)・約数の個数の最大 10^5 で 128・10^6 で 240・N log N などの回数・メモリ）は Python で計算して確かめた。10^9・10^12 の約数の個数の最大は research 01 §4.A の値（計算済みと記載）をそのまま使った

## 台帳への提案

- typical90_bc｜evidence｜https://github.com/E869120/kyopro_educational_90/blob/main/editorial/055.jpg を足す｜回数の見積もり（1/120）の裏付けは公式の解説画像にあり、Reputeless の 055.md には見積もりの記述がない
- typical90_bt｜evidence｜https://github.com/E869120/kyopro_educational_90/blob/main/editorial/072.jpg を足す｜経路の通り数の見積もりの裏付け
- abc196_d｜approach｜「左上から 3 択（置かない・縦・横）を DFS で試す。上界 3^16 ≈ 4.3×10^7 で、枝が切られて実際はずっと少ない」に具体化してもよい｜https://blog.hamayanhamayan.com/entry/2021/03/21/124541

## 用語集への提案

- ならし計算量｜amortized-complexity｜操作 1 回ずつの最悪ではなく、操作の列全体の合計で数えた計算量。1 回が重くなることがあっても、重い操作の回数が全体で限られていれば、1 回あたりの平均は小さい。（本文では用語集へリンクしていない。ページの題名に近い語のため。必要ならメインで判断）
- 定数倍｜constant-factor｜計算量の式に表れない、1 回の操作の重さや回数の比。同じ計算量でも実行時間が数倍〜十数倍違う原因になる

## 手引きへの提案

- §13 に「計算量の目安の数値（1 秒 10^8 回・log の値・メモリの個数）はページごとにぶれないよう、このページ（complexity-estimation）の値にそろえる」を足すと、他のページの執筆者が迷わない

## 問題の補充の候補

catalog の数（例題 1・練習 4）で足りているので必須ではない。複数テストケース（ΣN）と定数倍の節に台帳の問題がないので、余力があれば次を探す価値がある（未確認。ap.py と第三者の解説での裏付けはまだしていない）。

- 複数テストケースで ΣN の制約がある ABC の問題（abc319 以降に多い形式）：ケースごとの初期化を使った分だけにする型
- research 08 §4.9 の abc258_g・abc348_f（定数倍の差の具体例として挙がっている）：定数倍の節の練習か力試しの候補。ただし bitset のページとの重なりを確かめる必要がある

## 未解決の点

- typical90_bc の実行時間制限（research では 5 秒）は、第三者の解説で確かめられなかったので本文に書いていない。signs の「実行時間制限が 5 秒など長い」の例として typical90_bc を挙げる記述（catalog の level_evidence・research §4.A）は、確かめてから使うのがよい
- typical90_bt の制約（グリッドの大きさの上限）は確かめきれず、本文は「小さいグリッドなら数万通り程度」とだけ書いた
- 定数倍の差は「数倍以上」とだけ書き、具体的な倍率は出していない（research の「数倍〜十数倍」の出典が特定できなかったため）
- 節「調和級数の計算量」の見出しは catalog のまま「詳しくは整数論の調和級数のページ」を含む。リンク先のページの題名は「調和級数と倍数の列挙」で、math は整数論の分野なので食い違いはないが、見出しを短くするならメインで判断してほしい

## 検証の指摘への対応（2026-10-21）

- 直したもの：1（表の 1・3 行目に N を掛けた）、2（$O(3^N)$ に「$N \le 15$ 程度まで」と $3^{15}$ の回数を足した）、3（図を viewBox 幅 480・本文 16px に作り直し、名前と値を棒の上に白縁付きで置いた。指数は上付き）、4（例題に「制限 5 秒」、練習の 072 に「$H \times W \le 16$」を足し、参考に problem/055.jpg・072.jpg を加えた）、5、6（本文を「初期値の $N$ 個とクエリの数」にそろえ、練習の方針に配列と触った添字の列での持ち方を足した）、8（定数倍の節の最後を例題への 1 文に、「約 1/120」に）、9（再帰の呼び出しの重さと値渡しに 1 文触れた）、10（同じ値の case を足した。`pops`・`assert` は core に残し、本文で「回数を数えて確かめている」と添えた）、11（凡例を「破線」「点線」に分け、10^9 の説明を本文の言い方にそろえた）、12(b)（3 択を「1×1 の畳にする・1×2 の畳を縦に置く・横に置く」に。練習の一覧の要約も枚数が決まっている点を足した）
- 採らなかったもの：7（`#permutations` へのリンク）。bit-full-search は今 stub で、手引き §7 によりアンカー付きのリンクはそのページが draft 以降になってから付ける。メインで、そのページが draft になったときに `../basics/bit-full-search.md#permutations` へ直してほしい

## 台帳への提案（検証の後に追加）

- typical90_bc｜checked｜2026-10-21｜evidence に https://github.com/E869120/kyopro_educational_90/blob/main/problem/055.jpg と editorial/055.jpg を足す（制限 5 秒・$5 \le N \le 100$ は問題画像にある）
- typical90_bt｜checked｜2026-10-21｜evidence に problem/072.jpg と editorial/072.jpg を足す（$H \times W \le 16$）。summary の「小さいグリッド」は「$H \times W \le 16$ のグリッド」にしてよい
- abc196_d｜summary｜「H×W ≤ 16 のマス目を、枚数の決まった 1×2 の畳と 1×1 の畳で敷き詰める方法の数を求める。」｜https://blog.hamayanhamayan.com/entry/2021/03/21/124541（ページの一覧の要約は先に本文側で直した。台帳の summary から生成し直すときは、こちらに合わせてほしい）
