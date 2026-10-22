# 工程10 直し：basics・thinking で残したもの

basics・thinking の直し担当が、担当の外のファイル（台帳・front matter の summary・ほかの分野のページ）に要る直しや、判断の要るものをここに残す。

## 台帳（data/problems.yaml）に要る直し

- **abc116_c（difference-sequence の練習）**：台帳の pages に difference-sequence の練習があるが、本文にない。audit-shared の勧めどおり「黄のページの練習としては易しすぎる（diff 542）」ので、台帳の pages から外すのが自然。外すのは共有ファイルの直しなのでメインに任せる（本文に足す方を選ぶなら、方針は「答えは隣り合う目標の高さの差の正の部分の和」で #min-operations へリンクする）
- **abc467_f（exchange-argument の力試し）**：台帳の summary が仮の文（「（執筆時に確かめる）」）のまま。問いを atcoder.jp で確かめることはできない（noai）。出典の ikatakos 氏の記録で問いを確かめて summary を書き、力試しの囲みに足すか、確かめられなければ status を未確認にして note を残す（abc458_e と同じ扱い）。台帳の直しと問いの確認が要るので残した
- **abc197_c（bit-full-search の練習）**：audit-shared ## shared (3) の「判断待ち」の 1 件。勧めどおり bit-full-search の練習に足した（区切りの位置を bit に対応させる方針）。台帳はすでに pages に bit-full-search の練習を持つので、台帳の直しは要らない。判断を閉じたことを decisions に記録してほしい

## front matter の提案（本文は直した）

- **docs/basics/bitwise-independence.md の summary**：「最大化・最小化は上の bit から決め」を付録 A の正規形「上位 bit」にそろえる案（例：「最大化・最小化は上位 bit から決め」）。本文と sections の title・complexity は「上位 bit」に直した。aliases の「上位ビットから決める」は検索語として残した
- **docs/basics/bit-operations.md の aliases**：「最下位ビット」「ビット演算」は検索語として残した（本文の見出しと sections の title は「最下位 bit」に直した）
- **docs/basics/divide-and-conquer.md の signs**：phrase「区間 [L, R] の品物だけを使う…」も「閉区間 [L, R]」にするか。要点の箇条（本文）は「閉区間 $[L, R]$」に直した
- **docs/thinking/parity.md の related**：weighted-union-find を足した（本文のリンクの行き先を union-find-applications から weighted-union-find#generalization に替えたため）。front matter の変更なので、メインが確かめてほしい

## ほかの分野に残る同じ型（audit-facts の指摘の続き）

- 「0 始まり」「1 始まり」の揺れ：kth-value の 2 か所は直した（順位の数え方は「0 番目から数える」、添字は「1-indexed」）。同じ型のほかの分野（comb・ds・tree・graph・patterns・math・cpp・guide）はどこまでを揺れとみなすかをメインが決める
- graph/degree-sqrt の「4-サイクル」：thinking/symmetry-pigeonhole-casework L109 は先に「長さ 4 の閉路の検出」に直した（リンクの anchor `four-cycles` はそのまま）。graph 側の節題が直ったら文言がそろう

## 検査で見つけた担当外のエラー

- `python3 tools/check_pages.py` のエラー 1 件：`math/integer-division.md:65` の `../img/integer-division/floor-ceil.svg` がない。math の直しが作業中のものと思われる（basics・thinking のページにはエラーはない）
