# circle-geometry の報告と提案（b2）

- 書いたファイル：docs/geometry/circle-geometry.md、snippets/circle-geometry/{relation,connect,lattice,enclose}.{cpp,yaml}、docs/img/circle-geometry/{two-circles,enclose-candidates}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 4 件すべて一致。textlint エラー 0・警告 14（数式を含む文の長さと、助詞の重複の誤検出。§13-8・§14-25 の範囲）
- 図：two-circles.svg（visual の priority 2 の静的な図。2 列 3 段で、スマホ幅でも文字が読める）と enclose-candidates.svg（鈍角・鋭角三角形の最小包含円）。render_svg で 360px・720px を目で確かめた。動く図は作っていない
- 使った出典：参考の節のとおり。新しく check_noai で確かめたドメイン：sen-comp.hatenablog.com（指定なし）、qiita.com/vain0x の記事（指定なし。本文では使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc191_d | summary（circle-geometry の alternatives と本体） | 小数第 4 位までで与えられた円の内部（周上を含む）にある格子点の数を求める。 | 周上の点も数える。https://sen-comp.hatenablog.com/entry/2021/02/18/164536 。本文の行は先に直した（§14-15） |
| abc191_d | evidence | https://sen-comp.hatenablog.com/entry/2021/02/18/164536 を足す | ikatakos.com は執筆時に 503 で読めなかった。sen-comp で問いと方針（10^4 倍・行ごとの範囲・double で WA）を確かめた |
| abc157_f | evidence | https://drken1215.hatenablog.com/entry/2020/03/03/015300 を足す。checked を 2026-10-21 に | ikatakos は 503。drken で問い（N 個の肉・硬さ c_i・K 個焼ける最小時刻）と方針（時刻の二分探索・中心と 2 円の交点が候補）を確かめた |
| abc259_d | evidence | https://blog.hamayanhamayan.com/entry/2022/07/09/224142 を足す（任意） | int のあふれと 2 乗の整数判定に触れている |
| abc292_f | approach（circle-geometry の alternatives） | 1 頂点を角に置き、傾きの角度を決めると横と縦の制約の小さい方が上限になる。両者が等しくなる角度を二分探索する | merom686 の記事は角度を二分探索している。「場合分け」より実態に近い |
| abc181_f | checked | 2026-10-21 | drken の記事で問い（上下の壁 y = ±100・N ≤ 100 の釘）と方針を確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 最小包含円 | minimum-enclosing-circle | 平面上の点をすべて含む（周上も含む）円のうち、半径が最小のもの。2 点を直径とする円か、3 点の外接円になる。 |
| 外心 | circumcenter | 三角形の 3 頂点から等距離にある点で、外接円の中心。3 辺の垂直二等分線の交点。3 点が一直線上なら存在しない。 |

本文ではどちらにもリンクしていない（ページの中で説明しているため）。用語集に置く場合は、circle-geometry#min-enclosing-circle・#circumcenter を指す形でよい。

## 手引きへの提案

- §9 のコード片：`using namespace std;` の下で `relation`・`sort` のような std の名前と同じ関数名を作ると、C++20 以降は `std::relation`（概念）などとぶつかってコンパイルエラーになる（g++-15 で確かめた。本文に囲みで書いた）。関数名は `circle_relation` のように具体的にする、と一行足すとよい
- §5 geometry：「2 乗の比較は 0 以上の量どうしのときだけ大小を保つ」を一般の規則として足してもよい（円の判定・距離の比較で共通）

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc389_d（Squares in Circle、diff 749） | 1 つのマス目の中心を中心とする半径 R の円に、全体が入るマス目の数を数える。マスの右上の格子点が円の内部（周上を含む）にあるかに言い換え、列ごとに高さの最大を二分探索（または尺取り）で求める。座標を 2 倍して整数で判定する | 練習（節 lattice-points-in-circle。基礎帯なので易しい側。abc319 以降の唯一の候補） | https://kcpc.hatenablog.com/entry/2025/01/20/032000 （kcpc は付録 B にある）。ほかに https://yuulis.hatenablog.com/entry/ABC-389-D （未確認のドメイン） |

- ap.py の search（Circle・Disk・Enclose・Radius・Distance・Point・Triangle など）で abc319 以降を探したが、円・幾何の最適化が本体で水〜黄の問題は見つからなかった。abc467_d（Concentric Circles、928）は geometry-precision の練習にすでにある（中身は垂直二等分線の交差で、円の判定そのものではない）
- abc314_h（Ex. Disk and Segments、2938）は catalog の level_evidence にあるが台帳にない。入れ子の三分探索の発展の例として、ternary-search-caveats（黄）の力試しに足す案がある（研究ノートの裏付け：https://drken1215.hatenablog.com/entry/2023/08/12/231800 。執筆者は未読）

## 未解決の点

- abc259_d の制約（N ≤ 3000、座標と半径の絶対値 ≤ 10^9）は検索結果の要約から得た。本文では「N が 3000 程度」「10^9 規模」とぼかして書いた。検証役が第三者の記事で確かめるとよい
- abc292_f の「1 頂点を角に置き、傾きは 0° 以上 30° 以下でよい」は、merom686 の記事では証明されていない（記事は 15° までを調べたと書いている）。練習の方針の折りたたみに書いた。検証役が別の解説で確かめるとよい
- abc191_d・abc157_f の台帳の evidence（ikatakos.com）は 503 で読めなかった。代わりの記事で確かめた
- Library Checker の minimum_enclosing_circle は、GitHub の問題リポジトリ（geo/minimum_enclosing_circle）で「各点が円周上にあるかを答える」問題だと確かめた。本文の囲みでそのことに触れた
- Welzl のコード片は、乱数で作った 200 組の点で候補の全列挙と答えが一致することを main の assert で確かめている。座標が 10^9 規模での EPS の妥当性は確かめていない（本文では N が大きいときの方法として紹介するだけにした）
- 使用量の目安：道具の呼び出し約 50 回、Web 取得約 15 回

## 検証の指摘への対応（b2）

- 指摘 1〜6（すべて直すとよい）：すべて直した。採らなかったものはない
  - 1：整数の平方根の補正の条件を $w^2 \le m < (w + 1)^2$ にした
  - 2：「時刻を決めると…」の箇条書きに、$c_i$ の意味（位置から点 $i$ までの距離に掛ける係数）を添えた
  - 3：候補の箇条書きの後に「点が 1 つか、すべて同じ位置なら半径 0」を足し、証明の冒頭で $r > 0$ とした。外心の囲みの半径 0 の行を「最初の答えを点 1 つを中心とする円にしておく」に直した
  - 4：ABC292 F の方針に、外接長方形の角に頂点がある理由の 1 文を足した
  - 5：relation.cpp で一致の判定（`d2 == 0 && r1 == r2`）を先に置き、半径 0 の同じ 2 点も一致を返すようにした。cases に半径 0 の 2 点の例を足した
  - 6：enclose.cpp の welzl の取り込みの幅にコメントを足した
