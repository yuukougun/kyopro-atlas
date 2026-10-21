# tree-degree（木の次数列と Prüfer 列）の報告と提案

- 書いたファイル：docs/tree/tree-degree.md、snippets/tree-degree/{from-degrees,pruefer,allocate}.{cpp,yaml}、docs/img/tree-degree/{pruefer,caterpillar}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の counting-links の title を短くした（「木の数え上げ（Cayley の公式）は数え上げの章、全域木の個数はグラフの章の行列木定理」→「木の数え上げ（Cayley の公式・行列木定理）へのつながり」。anchor は同じ）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 3 本とも期待どおり、textlint エラー0（警告11：図の代替テキストの長さ・数式の中の読点・数式を含む文の長さ・「に」の重なりで、意味を変えずに直しにくいもの）。SVG は render_svg.py で 360px・720px を目視した
- 使った出典：drken ABC359 F・ABC385 E（はてなブログ、付録 B 済み）、Kazun ABC239 F（付録 B 済み）、en.wikipedia.org「Prüfer sequence」（付録 B 済み）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc385_e | checked | 2026-10-21 | https://drken1215.hatenablog.com/entry/2024/12/26/010927 （中心を全探索し、隣の次数を大きい順に並べて L·d_(L) + 1 の最大を取る、を確かめた） |
| abc303_e | pages | tree-degree を practice で足す（tree-basics の例題のまま） | https://drken1215.hatenablog.com/entry/2023/05/29/134700 （次数 3 以上の頂点が元の星の中心） |
| abc378_f | pages | tree-degree を practice で足す（任意。tree-basics の練習のまま） | https://drken1215.hatenablog.com/entry/2024/11/04/002341 （次数 3 の頂点の成分ごとに数える）。本文の degree-facts で次数による形の判定を扱っているため |

- 本文は台帳の summary をそのまま使った（表記の直しは不要）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 握手補題 | handshaking-lemma | どのグラフでも次数の和は辺の本数の 2 倍になるという事実。各辺が両端の次数に 1 ずつ数えられることから出る。 |
| ラベル付き木 | labeled-tree | 頂点に 1〜N の番号が付いた木。番号の付け方が違えば、形が同じでも別の木として数える。 |
| 毛虫 | caterpillar | 1 本のパスに葉だけが付いた木。葉をすべて除くとパスになる。 |

- 本文では「握手補題」「毛虫」を用語集へリンクしていない（提案が入ったらメインが張る。どちらも本文中で 1 文の定義を書いた）

## 手引きへの提案

- なし。ただし §5 tree の「Prüfer 列の全単射は証明の筋を図で示す」について、全単射の証明（任意の列から木ができる）は図ではなく折りたたみの文章で書いた。生成の図（手順の表）で出現回数 = 次数 − 1 の筋を示している

## 問題の補充の候補

- abc303_e（A Gift From the Stars、diff 1113）：星を葉どうしでつないだ木から元の星の大きさを求める。次数 3 以上の頂点が星の中心と分かる。https://drken1215.hatenablog.com/entry/2023/05/29/134700 （台帳では確認済み。tree-basics の例題）
- abc378_f（Add One Edge 2、diff 1436）：辺を 1 本足した閉路の頂点の次数がすべて 3 になる足し方を数える。https://drken1215.hatenablog.com/entry/2024/11/04/002341 （台帳では確認済み。tree-basics の練習）
- ap.py で "Degree"・"Star"・"Leaf" を題名で探したが、abc319 以降で青の帯に合う新しい候補は見つからなかった（abc412_g は 3402 で発展、abc303_h は cayley-pruefer 側）。例題 1・練習 2 で目安の下限は満たす

## 動く図（catalog の visual は priority 2）

- 動く図は作らず、静的な図 pruefer.svg（7 頂点の木と生成の 5 手順の表）で代えた。作るなら：data-viz="pruefer"、config 例 `{"n": 7, "edges": [[1,4],[4,5],[4,6],[2,6],[3,6],[6,7]], "mode": "encode"}`。各ステップで今の葉（小さい順）・消す葉・記録する値を示し、mode "decode" では列の残りと出現回数を示す

## 未解決の点

- ABC359 F の A_i の上限を確かめていない（第三者の解説の制約欄に N の範囲しか見えなかった）。落とし穴のオーバーフローは「制約から見積もる」と一般の形で書いた
- ABC385 E の「雪の結晶」の定義で、先の葉の数が 1 以上を要するかは確かめていない。本文と方針は L·d_(L) + 1 の式だけで書き、この点に触れていない
- Prüfer 列の O(N) の生成は文章だけで、コード片は O(N log N) の版だけにした
- tree-basics と tree-construction は本ページを「次数と次数列」「次数と木」の名でリンクしている。題名「木の次数列と Prüfer 列」へそろえるかはメインの判断

## 検証の指摘への対応（b2 直し）

直すべき 0 件・直すとよい 8 件。8 件すべてを直した（採らなかったものはない）。

1. degree-facts の雪の結晶の段落：問題へのリンクと式 $1 + L \cdot d_{(L)}$ を本文から外し、「中心ごとに隣を次数順に並べ、先頭から何個使うかを試す。並べる長さの合計は $2N-2$」という一般の型の説明にした。式は練習の方針の折りたたみだけに残した
2. $m = 0$ の扱い：本文から式を外したので、練習の方針の折りたたみに「$L$ 番目の次数が 1 の選び方も式に入るが、葉の隣を中心とみた形が同じ数以上を残すので最大だけなら除かなくてよい」を 1 文足した
3. 星の中心：逆が成り立たない（次数 2 の中心は葉どうしをつないだ頂点と区別できず、別に数える）ことを添えた
4. 凸でないときの DP：全体 $O(N^3)$（$N$ が数百まで）を書き足した
5. 次数が集合に入る木の数：頂点ごとの指数型の級数 $\sum_{k\in S_v} x^{k-1}/(k-1)!$ の積（集合が同じなら累乗）の $x^{N-2}$ の係数 × $(N-2)!$ と直した
6. from-degrees.cpp：`optional` を返すラムダをやめ、条件を満たす前提で辺を作る普通の関数 `build_tree` を core にした。判定は main に移し、本文にも「判定は条件をそのまま確かめればよい。次のコードは辺を作る部分」と 1 文足した。check_snippets の 9 case は一致
7. pruefer.svg 手順 5：「4」と「, 7」を別の text に分け、点線の枠を 4 だけに合わせた
8. pruefer.svg の [5]：頂点 4 の左上（辺のない側）に移した。360px・720px の PNG で確かめた
