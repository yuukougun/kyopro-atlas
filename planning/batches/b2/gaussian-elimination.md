# gaussian-elimination の報告（b2）

- 書いたファイル：docs/math/gaussian-elimination.md、snippets/gaussian-elimination/{mod-p,mod2-bitset,real,real-ng}.{cpp,yaml}、docs/img/gaussian-elimination/{steps,outcomes}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の rank の title を「ランクと解の個数 p^(変数の数 − ランク)」に変えた（anchor は同じ。本文の記法で n を式の数、m を変数の数にしたので、元の「p^(n − rank)」だと n の意味が食い違うため）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 本すべて一致、textlint エラー 0（警告 16：文の長さと助詞の重なり。数式を含む文・図の代替テキスト・問題の行で、§14-25 の範囲）。図は render_svg で 360px・720px を目で確かめた
- 使った出典：drken（Gauss-Jordan の記事・abc313_d・abc128_c・yahoo E）、E869120 の sol/057.cpp、kmjp の abc366_g。どれも付録 B のドメインで、新しく noai を確かめたドメインはない
- real-ng.cpp は本文に取り込まない確認用（部分ピボット選択をしないと 1e-20 x + y = 1, x + y = 2 で x = 0 になることを確かめた。§13-9）

## 台帳への提案

- abc313_d｜checked｜2026-10-21｜https://drken1215.hatenablog.com/entry/2023/08/06/010000 （1 ≤ K < N ≤ 1000・K は奇数・質問 N 回までを確かめた）
- typical90_be｜checked｜2026-10-21｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/057.cpp （入力の形と解法を確かめた。制約の数値は解答コードからは分からない）
- abc366_g｜checked｜2026-10-21｜https://kmjp.hatenablog.jp/entry/2024/08/16/1000 （N ≤ 60 を確かめた）
- yahoo_procon2019_qual_e｜checked｜2026-10-21｜https://drken1215.hatenablog.com/entry/2019/02/10/024200 （N, M ≤ 300、答え (2^N − 2^(N−r))·2^(M−1) と同値な式を確かめた）
- abc128_c の alternatives の approach に「N, M ≤ 300 でも同じ方法で解ける（drken の記事の発展）」を足してもよい

## 用語集への提案

本文では用語集にリンクしていない（anchor がまだないと check_pages がエラーにするため）。足したら、本文のそれぞれの語の最初の出現にリンクを足す。

- 拡大係数行列｜augmented-matrix｜連立一次方程式の係数の行列の右に、右辺の列を 1 列足した表。行基本変形を右辺にも同時に施すために使う。（最初の出現：導入の記法の段落）
- ピボット｜pivot｜掃き出し法で、その列のほかの行を消すのに使う 0 でない成分。mod p では逆元を持つ値、実数では絶対値が最大の値を選ぶ。（最初の出現：row-reduction の「手順」）
- 自由変数｜free-variable｜掃き出した後にピボットのない列の変数。好きな値にでき、決めるとほかの変数が決まる。個数は変数の数 − ランク。（最初の出現：row-reduction の判定の箇条書き）
- ランク｜rank｜行列を掃き出したときのピボットの個数。一次独立な行（列）の最大の個数に等しい。階数ともいう。（最初の出現：rank の節の 1 文目。用語集から gaussian-elimination#rank へ案内してもよい）
- 一次独立｜linear-independence｜いくつかのベクトルのどれも、ほかのものの定数倍の和（mod 2 なら XOR）で作れないこと。（最初の出現：rank の節の 1 文目）

## 手引きへの提案

- 骨格の sections の title が、本文で決めた記法（式の数 n・変数の数 m）と文字の意味が食い違うことがある。数学のページでは、title に文字を使うなら本文の記法にそろえて title を直してよい、と §13-2 に添えるとよい

## 申し送り（メインへ）

- handoff §1.2 の bit-full-search:188（スイッチと電球）は gaussian-elimination#mod-2、prime-exponent-vector:158（積が平方数）は gaussian-elimination#rank へ張り替えられる
- expectation-linear-equations:155 の「手順は掃き出し法のページに任せる」は gaussian-elimination#mod-p へ、:151 は #real か #row-reduction へ張り替えられる
- bitset-speedup の related の gaussian-elimination#mod-2 は本文にある
- 動く図（catalog の visual は priority 2）は作っていない。静的な図 steps.svg で代えた。作るなら仕様は「拡大係数行列を 1 列ずつ掃き出すステップ送り。各ステップで、ピボットの行を色付けし、引いた行と倍率を caption に出す。config は {"matrix": [[1,1,1,6],[2,1,-1,1],[1,-1,2,5]], "mod": null}（mod 2 の例も選べる）」

## 問題の補充の候補

- 確認済みの青の帯の練習は見つけられなかった（ap.py の題名検索と Web 検索で、第三者の解説で mod 2 の掃き出しを主にした ABC の問題を裏付けられたものがなかった）。練習は abc128_c の 1 問のまま。候補を探すなら、atcoder-tags の「行列」「XOR」タグの一覧（https://atcoder-tags.herokuapp.com/tags/Mathematics/Matrix）から、kmjp・drken の解説で掃き出しを使うものを拾うのがよい

## 未解決の点

- typical90_be の制約（N, M の上限）は確かめられなかった（問題文は画像で、解答コードに書かれていない）。本文では制約の数値を書いていない
- 「mod p のランクは実数のランク以下で、たまたま小さくなることがある」は整数の行列についての一般的な事実（小行列式が p の倍数になりうる）として書いた。出典は付けていない
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 6 回・検索 2 回

## 検証の指摘への対応（直し）

- 直すとよい 6 件をすべて直した：1 rank の一次独立の言い方（定数倍の和・mod 2 なら XOR）、2 typical90_be の方針に「パネルを M 枚」、3 abc313_d に行列を使わない XOR の直接の説明を先に置き、行列の説明に行列累乗へのリンクと q = BA → Bq = A を足した、4 outcomes.svg の解なしの見出しを「解なし（rank = 2）」にし、括弧を本文の判定の言葉「係数が 0 で右辺が 0 でない」に変えた（代替テキストも合わせた。render_svg 360px で確かめた）、5 確認問題 3 の問いに「long long のまま余りを取らずに」を足し、答えに ACL の modint では起きないことを添えた、6 bitset の計算量に「W を変数の数 + 1 程度にとれば」を、落とし穴に「大きすぎても 1 回の XOR が W/64 語かかる」を足した
- 採らなかったもの：なし
- 直した後の検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 本一致、textlint エラー 0（警告 17、§14-25 の範囲）
