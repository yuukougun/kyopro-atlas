# 工程10 1巡目の残り（left-*.md・verify-*.md）への判断（2026-10-22、メイン）

決まりとして残すものは手引き §17 に書いた。ここには個々の件の扱いを書く。2巡目の直しはこの表と left-*.md に従う。

## 決まりに関わるもの（§17）

| 件 | 決定 |
| --- | --- |
| guide・hub・pattern の complexity | 17 ページすべて null（§17-1） |
| pattern・hub の prerequisites | 任意。持つなら要点の「前提」と一致（§17-2）。今のままでよい |
| ライブラリの節の anchor | cht・dynamic-dp・monge（verify）・wavelet-matrix・auxiliary-tree（usage）・linear-recurrence-fast（implementation）を `library` に改め、本文のリンク（geometry/advanced-geometry の cht#verify、ds/persistent-data-structures の wavelet-matrix#usage など）を張り替える。two-sat の acl、roadmap の practice、string-basics の cost-pitfalls は残す（§17-3） |
| next-steps | modint・mod-pow・global-offset は今のまま。lazy-segment-tree も今のまま（§17-4） |
| 確認問題の置き場所 | 本文の途中でよい。#quiz は任意（§17-5） |
| 図を縦に積んだもの | 認める（§17-6）。dp-order/six-orders.svg（幅 260・高さ 1864）も今のまま。verify-pages の「はみ出し 1〜9px」の 9 枚は余白を 10px 足す |
| frequency | 3 問以上で B。tools/frequency.py を作って全ページの frequency・frequency_evidence を付け直す（§17-7） |
| prh・付録 A | §17-8 の規則を足し、本文の残りを直す。summary・signs も直す（aliases は残す） |
| 0 始まり・1 始まり | 0-indexed・1-indexed にそろえる（§17-8） |
| 問題の行の要約と台帳 | 一字一句の一致は求めない（§17-9） |
| 出典の題名 | URL ごとに 1 つにそろえ、check_pages に警告を足す（§17-10） |
| 重なりの持ち主 | §17-11。rollback-union-find#offline-dynamic-connectivity を要点とリンクに縮める。root-path-dfs L151〜161 を 2〜3 文と rollback-union-find#no-path-compression へのリンクに縮める |
| 練習の数 | extended-dijkstra の 9 問はそのまま。abc116_c（difference-sequence）・abc130_e（dp-prefix-sum）は台帳の pages から外す（§17-12） |

## 個々の件

- front matter の提案（left-*.md の summary・signs・related・acl の追加）はすべて採る：bitwise-independence・divide-and-conquer の signs・euler-path・steiner-tree・degree-sqrt・k-shortest-paths・binary-trie・wavelet-matrix・palindrome の signs・string-automaton-dp・tree-centroid の summary、parity の related（済み）、convolution-ntt・minimax・divisor-inclusion-exclusion・interval-dp-advanced・divide-and-conquer・bitset-speedup・subset-enumeration-dp の related。担当が直した summary（probability-symmetry・library-design・permutation）と related の追加 23 ページは追認する
- ほかの分野のページへの直し（left-*.md の「ほかの分野」の節）はすべて行う。「ダイクストラ」→「ダイクストラ法」、リンクの文字、`\operatorname{lcm}`、閉区間の断り、bitwise-independence の「上位 bitで」の空白、patterns/xor の「上位ビット」、partially-persistent-union-find L122 の UnionFind
- advanced-ds-catalog L155「HLD・重軽分解」は「HL 分解（HLD）」に
- mo-algorithm の別名「クエリ平方分割」は残す（term-index が使い分けを説明している）
- cpp-undefined-behavior が level null の cpp-environment を前提にするのは認める
- weighted-union-find の acl は空のまま（囲みは本文の 1 文で足りる）
- manhattan-chebyshev の #motivation は sections に足さない
- tree-ratio-greedy の「トポロジカル順」は付録 A の別の書き方として認める（そのまま）
- 60 字を超える見出し：直さない（目安）
- glossary・term-index の参考の節：なくてよい
- static-top-tree の aliases の「重軽再帰 DP」は外し、本文 71 行目の語を #heavy-path-dp へのリンクにする
- agc002_d の summary：「x と y を含む成分の頂点数（同じ成分なら 1 回）」の形に台帳と 3 ページの行をそろえる
- 台帳の「歩道」→「ウォーク」（abc338_f ほか）、abc180_f の「サイクル」→「閉路」を直して fix_problems を流す
- 台帳の仮の summary 5 問（abc458_e・abc467_f・abc475_f・abc479_d・abc479_e）：第三者の解説（ikatakos 氏の記録など、noai を確かめたもの）で問いを確かめて書く。abc467_f は exchange-argument の力試し、abc475_f は inclusion-exclusion の練習に足す。確かめられなければ status を未確認にし、台帳の pages から外して note を残す
- abc458_g → dp/slope-trick の力試し、keyence2019_e → graph/spanning-tree-advanced の練習を本文に足す
- 練習の節がない complement-graph-bfs・floor-sum・steiner-subtree：問題を探し（tools/ap.py と第三者の解説で確かめる）、見つかれば台帳と本文に足す。見つからなければ §16-5 の 1 文を置く
- gen_site.py の roadmap の見出し「G 問題（黄の帯）」：実際に集める帯に合う名前にする
- 生成物の外の手書きの文：docs/index.md の「制作中」の info は残す（ユーザーの確認が済むまで done はない）。guide/knowledge-map L59・guide/reverse-index-signs L75 の古い文言は直す
- 出典：doi.org（union-find-applications）は書誌情報だけの出典に、suzukiapple.tumblr.com（sqrt-decomposition）は別の解説に替える。trap.jp は証明書の検証を外して取得し、noai の指定がなければ残す（付録 B に記録）。取れない記事（hashing-for-sets の post/1594）は出典から外す。miti-7.hatenablog.com・fairy-lettuce.hatenadiary.com は check_noai で確かめて付録 B に足す
- 用語の索引の五十音順：工程10では行わない（progress の残りに記録済み）
