# multiplicative-function の報告（b4）

- 書いたファイル：docs/math/multiplicative-function.md、snippets/multiplicative-function/lucy.{cpp,yaml}、snippets/multiplicative-function/phi-sum.{cpp,yaml}（図はなし。catalog の visual が null）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections の prefix-sums の title の「杜教筛」を「杜教篩」に、「Min_25」を「Min_25 篩」に直した（anchor は変えていない）。sections の並びを本文の順（dirichlet → prime-counting → prefix-sums）に入れ替えた。Min_25 篩の素数の和の段で Lucy DP を使うので、先に Lucy DP を説明した
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 期待と違う 0。textlint エラー 0・警告 13（数式を含む文の長さ・読点の数、「d」の不自然なアルファベット（約数の個数の記号）、助詞の重なり 2 件。どれも数式まわりの誤検出か文意を保つため残した）
- 使った出典（どれも付録 B のドメイン）：maspypy.com（ディリクレ積の和、φ の和とメルテンス関数が O(N^{2/3})）、nyaannyaan.github.io（Lucy DP の O(N^{3/4}/log N)、Min_25 の要件と計算量の注記、O(N^{2/3}) の素数カウントの存在、解説一覧の ABC370 G の手法名）、oi-wiki.org（Min_25 の 2 段の構成と計算量。事実だけで文章は使っていない）、en.wikipedia.org（Dirichlet convolution・Prime-counting function）、github.com（library-checker-problems の task.md・info.toml で 4 問の問いと制約）。新しく noai を確かめたドメインはない
- 例題：台帳に確認済みの問題がないので 0 問。例題の見出しは置いていない

## 台帳への提案

- なし（このページの問題は 0 件のまま）。下の「問題の補充の候補」を参照

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 乗法的関数 | multiplicative-function | $f(1) = 1$ で、互いに素な $a, b$ について $f(ab) = f(a)f(b)$ が成り立つ関数。素数べきでの値だけで決まる。$\varphi$・$\mu$・約数の個数・約数の和など。互いに素でなくても成り立つものを完全乗法的という |
| ディリクレ積 | dirichlet-convolution | $(f * g)(n) = \sum_{d \mid n} f(d) g(n/d)$ で決まる関数どうしの積。$\varphi * 1 = \mathrm{id}$、$\mu * 1 = \varepsilon$ など。乗法的関数どうしの積は乗法的 |

本文ではリンクを張らず、節の中で定義している（§15-1）。用語集に足したら dirichlet の節の最初の出現にリンクを張れる。mobius-function・euler-phi・zeta-mobius-divisor からも使える語。

## 手引きへの提案

- 付録 A の整数論に「乗法的関数・ディリクレ積・杜教篩・Min_25 篩・Lucy DP」を足す案。aliases は中国語の「杜教筛」だが、本文は mobius-function にならって「杜教篩」と書いた。prh.yml で「杜教筛」を本文で「杜教篩」に寄せる（別名の行は textlint の外）とそろう
- 発展の概要で例題が 0 問のときの構成（`## 例題` を置かない）を §4 か §13-10 に一言あるとよい。今回は k-shortest-paths にならい、例題の見出しを置かず Library Checker の練習だけにした

## 問題の補充の候補

- abc370_g（G. Divisible by 3、diff 3428。ap.py で実在と題名・difficulty を確認）：乗法的関数の和に帰着する問題（約数の和が 3 の倍数になる数を、長さ M の列の積として数える）。裏付けは Nyaan「解説一覧」（https://nyaannyaan.github.io/docs/problems/editorials/ 、「乗法的関数の prefix sum」の手法名だけ）の 1 件しか取れなかった。第三者の解説（はてなブログ・GitHub）は検索で見つからなかった。研究ノートでも status は tag。役割は力試しが目安だが、裏付けが 2 件にそろうまで載せないほうがよい
- ABC で素数計数・杜教篩そのものが要る問題は、ap.py の検索（題名）と Web 検索では見つからなかった

## 未解決の点

- 「$O(N^{2/3})$ 程度のさらに速い方法（Meissel-Lehmer 法を改良した系統）」の部分は、O(N^{2/3}) の方法があること（Nyaan のライブラリ）と Meissel-Lehmer 法の経緯（Wikipedia）は確かめたが、Nyaan の O(N^{2/3}) の実装が Meissel-Lehmer の系統かは確かめていない。気になるなら「O(N^{2/3}) 程度のさらに速い方法もある」とだけにする
- Min_25 篩の $\Theta(N^{1-\varepsilon})$ は OI Wiki と Nyaan の注記に従った（原典の論文は読んでいない）
- b3 の申し送り（mobius-function の「杜教篩で O(N^{2/3})」とメルテンス関数）は maspy の記事で確かめた。mobius-function#quotient の記述は「N^{2/3} までを前計算すれば」という条件を添えるとより正確（前計算なしは O(N^{3/4})）。直すかどうかはメインに任せる
- Library Checker の Counting Squarefrees（$N \le 10^{18}$）の解法として本文に書いた式 $\sum_{d \le \sqrt{N}} \mu(d) \lfloor N/d^2 \rfloor$ は標準的な事実で、Nyaan のライブラリ（μ の累積和を商の列挙で求める構成）と一致するが、計算量までは書いていない
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得・検索 約 20 回

## 検証の指摘への対応

- 指摘 1〜6 をすべて直した（1：素数の和で超えるのは初めの値と途中の値と直した、2：「$p$ 以下」に直した、3：Meissel-Lehmer の括弧を消し、Wikipedia の注記から「Meissel-Lehmer 法の経緯」を消した、4：要点・complexity・表に $\Theta(N^{1-\varepsilon})$ の断りを足した、5：「合成数」に直した、6：`mf_prefix_sum` の渡し方を足した）。採らなかったものはない
- aliases の「Meissel-Lehmer」は素数計数の方法の名前として引く読者がいるので残した（本文では触れない）。外すかどうかはメインに任せる
- 検査：check_pages エラー 0・警告 0、fix_problems 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0（警告 14）
