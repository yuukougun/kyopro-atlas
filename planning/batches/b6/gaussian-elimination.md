# gaussian-elimination の問題の補充（b6・工程9）

- ページ：docs/math/gaussian-elimination.md（レベル 青）。今の練習は abc128_c（diff 805）の 1 問。例題は abc313_d・typical90_be、力試しは abc366_g・yahoo_procon2019_qual_e
- 探したところ：
    - (1) b1・b5 の summary/candidates.md にこのページの補充の候補はない。b3 の summary/candidates.md と b2 の報告 planning/batches/b2/gaussian-elimination.md は「確認済みの候補なし。atcoder-tags の行列タグから拾う」とだけ書いている
    - (2) data/problems.yaml で pages に gaussian-elimination を持つ問題は abc128_c・abc313_d・abc366_g・typical90_be・yahoo_procon2019_qual_e の 5 問で、どれも本文にある。本文にない問題はない
    - (3) atcoder-tags の Mathematics/Matrix・XOR・Expected-Value の一覧、ap.py の題名検索（Light・Lamp・Switch・Flip・Equation・Matrix など）、kmjp・drken のブログ内の検索（「掃き出し」）を見た。drken の記事「Gauss-Jordan の掃き出し法と、連立一次方程式の解き方」（https://drken1215.hatenablog.com/entry/2019/03/20/202800）の練習問題の一覧から、AtCoder で出された 3 問を見つけた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）。3 問ともコンテストが rated の対象外で difficulty がない
- 候補 3 問を足すと練習は合わせて 4 問になる
- 注意：Web 検索はこのセッションの上限に達して 1 回しか使えなかった。第三者の解説は drken の記事 1 本ずつしか確かめられていない（2 本目は見つけられなかった）

## 候補

### icpc2013summer_day4_f（新規。台帳になし）

- 問題ID：icpc2013summer_day4_f
- 題名：F. Graph Automata Player
- difficulty：なし（AtCoder Problems に値なし。JAG 夏合宿 2013 Day4。drken の記事は難しさを「2D」・550 点相当とする）
- 役割：practice
- 要約：N 頂点（N ≤ 300）の有向グラフで、各頂点の 0/1 の値が「辺の先で 1 の頂点の数が奇数なら 1」という規則で一斉に変わるとき、T 回後の値から元の値を復元し、解がなければ none、複数あれば ambiguous と答える。
- 方針の要点：1 回の変化は隣接行列 A を掛ける mod 2 の演算なので、A^T を繰り返し二乗法で求め、A^T x = (T 回後の値) を mod 2 で掃き出して、0 = 1 が出れば none、ランクが N 未満なら ambiguous、N なら解を出す（bitset で行列の積と掃き出しを速くする）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/03/20/192300 （問いの 3 通りの出力、N ≤ 300、行列累乗と mod 2 の掃き出し、bitset の実装を確かめた。記事は AOJ 2624 として書いているが同じ問題）
- 本文に足すときのメモ：row-reduction の節の「解なし・一意・無数」の判定がそのまま出力の 3 通りになる。行列累乗のページ（matrix-power）への関連も付けられる

### code_thanks_festival_2017_f（新規。台帳になし）

- 問題ID：code_thanks_festival_2017_f
- 題名：F. Limited Xor Subset
- difficulty：なし（AtCoder Problems に値なし。CODE FESTIVAL 2017 Thanks、500 点。drken の記事は「2D」とする）
- 役割：practice
- 要約：N 個（N ≤ 10^5）の正の整数から 0 個以上を選んで XOR が K になる選び方の数を、10^9+7 で割った余りで求める（値は 10^5 以下）。
- 方針の要点：選ぶかどうかを x_i とすると bit ごとに mod 2 の式が 17〜20 本並ぶので、掃き出してランク r を求め、矛盾があれば 0、なければ 2^(N−r) と数える（rank の節の「選び方の数え上げ」の型。想定解は値の和の制約を使う DP）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/03/20/173300 （問い・制約・bit ごとの連立方程式とランクから 2^(N−r) を出す解法、総和の制約がなくても正しいことを確かめた）
- 本文に足すときのメモ：XOR 基底（xor-basis）のページでも同じ数え方ができる（基底の大きさがランク）。台帳では pages に xor-basis を alternatives で持たせてもよい

### bitflyer2018_final_d（新規。台帳になし）

- 問題ID：bitflyer2018_final_d
- 題名：D. 数列 XOR
- difficulty：なし（AtCoder Problems に値なし。codeFlyer 本選 2018、600 点。drken の記事は「3D」とする）
- 役割：practice（1 問目・2 問目より一段難しい。帯を厳しく見るなら challenge）
- 要約：長さ N（N ≤ 10^5）の 60 bit の整数の列 A に、隣り合う 2 項の一方をその 2 項の XOR に置き換える操作を何度でも行って、列 B にできるかを判定する。
- 方針の要点：操作を組み合わせると行の入れ替えと「ある行に別の行を XOR する」ができ、各数を 60 bit の行とみると操作は mod 2 の行基本変形そのもので、逆の操作も行基本変形なので、A と B をそれぞれ簡約階段形にして一致するかで判定する（O(60N)）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2018/07/04/070000 （操作、制約、3 回の操作で隣を入れ替えられること、操作が行基本変形になること、簡約階段形が一意なので比べればよいことを確かめた）
- 本文に足すときのメモ：row-reduction の節の「行基本変形は元に戻せる」と、簡約階段形が操作の順によらず決まることを使う問題。本文に「簡約階段形は一意」の一言がないなら、練習の方針の欄で補う

## 除いたもの

- abc128_c（練習）・abc313_d・typical90_be（例題）・abc366_g・yahoo_procon2019_qual_e（力試し）：本文に既にある
- abc141_f（Xor Sum 3、2342）：drken は想定解を掃き出し法とするが、台帳で xor-basis の practice。XOR の最大化は基底の話なので重ねない
- arc054_c（C. 鯛焼き、2292 参考値）：atcoder-tags の Matrix タグにあり、mod 2 の行列式（完全マッチングの数の偶奇）を求める問題として知られるが、第三者の解説を開いて確かめていない。determinant のページの候補になりうる
- abc276_h（Construct a Matrix）・abc299_h（Dice Sum Infinity）・arc138_d（Differ by K bits）：kmjp の「掃き出し」の検索で出たが、発展の難しさと見込まれ、解説も開いていないので候補にしない（difficulty も確かめていない）
- caddi2018_d（F. Square、2723）：drken の「掃き出し」の検索で出たが、帯から離れすぎる
- AOJ 1308・AOJ 2530・AOJ 2171・AOJ 1328、yukicoder No.184・No.803：drken の記事の練習問題だが AtCoder の問題ではない
- ap.py の題名検索で出た Lamp・Flip・Lights 系（abc129_d・arc148_c・abc396_g・arc199_a など）：題名だけで、掃き出しを使う裏付けがない

## 本文に足すときのメモ

- 練習の並びは易しい順に abc128_c（805）→ code_thanks_festival_2017_f（500 点）→ icpc2013summer_day4_f（550 点）→ bitflyer2018_final_d（600 点）が自然。3 問とも difficulty がないので、配点と drken の目安（2D・2D・3D）で並べた
- 台帳への追加の提案：上の 3 問を pages に {id: gaussian-elimination, role: practice}、evidence に各 drken の記事の URL で足す
