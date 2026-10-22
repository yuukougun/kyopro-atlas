# 残したもの（comb・patterns・guide・start の直し担当）

audit-*.md の「## comb」「## patterns」「## guide」「## start」の項目のうち、直さなかったもの・ほかの分野や共有ファイルに要る直し。

## メインの判断が要るもの

- **complexity（guide・hub・pattern の 17 ページ）**：audit-facts（guide）と audit-structure（comb・patterns・guide）。§16-12 どおり null にするか、§16-12 を改めるかをメインが決める（audit-facts の指示）。対象は guide/reverse-index-constraints・library-design・method-comparison、comb/twelvefold-way、dp/dp-speedup-overview・ds/advanced-ds-catalog・graph/graph-modeling（hub）、patterns の 10 ページ。どちらに決めても全ページをそろえる。
- **pattern・hub の prerequisites と要点の「前提」**（audit-relations ## patterns の後半）：xor・bracket-sequence だけが持ち、ほかの 8 ページと advanced-ds-catalog は持たない。どちらにそろえるかを §16 に足す。
- **patterns の見出しの 60 字超え 7 か所**（audit-structure ## patterns）：末尾の「（id）」を外すなら見本 bracket-sequence を含む全 pattern でそろえる。
- **guide/roadmap の anchor `practice`**（audit-structure ## guide）：直すには anchor を `practice-by-color` に変える必要があり、「anchor を変えない」の決まりに当たるので残した（外からのリンクはないと audit にある）。変えるなら sections も直す。
- **guide/glossary・guide/term-index に参考の節がない**（audit-structure ## guide、判断）：参考にした資料がなければ現状でよいかをメインが決める。

## 生成・道具・台帳（メインが流すもの）

- **guide/roadmap の生成ブロックの見出し「G 問題（黄の帯）」**（audit-relations ## guide）：tools/gen_site.py の見出しを「黄・発展の帯」か「黄以上」にする。
- **comb/expectation-tail-sum の練習の囲み**（audit-shared ## comb・audit-structure ## comb）：abc411_e が道具の正規表現のせいで載らない。正規表現を直した後に練習の囲みを作る（方針の文は b6/APPLIED.md のとおり）。
- **comb/inclusion-exclusion の abc475_f**（audit-shared ## comb）：台帳の summary が仮の文で、問いを確かめないと本文に足せない（atcoder.jp は開けない）。evidence で問いを確かめて summary を書くか、未確認にして note を残す。
- **台帳の summary の「サイクル」**：abc180_f の summary（counting-labeled-graphs・counting-mindset・counting-dedup の囲みに出る）は「各連結成分がパスかサイクル」。§7 に合わせるなら「パスか閉路」に台帳を直して fix_problems を流す（本文の行は台帳から作り直されるので触っていない）。

## ほかの分野のページへの直し

- **docs/dp/subset-enumeration-dp.md L229**：リンクの文字「ラベル付きグラフの数え上げ」→「連結なグラフの数え上げ」（counting-labeled-graphs の題名。comb の 2 か所は直した）。
- **docs/dp/insertion-dp.md L154**：リンクの文字「包除原理の DP」→「包除 DP」（inclusion-exclusion-dp の題名）。
- **docs/math/convolution-ntt.md L12**：related に `zeta-mobius-subset` を足す（XOR・OR 畳み込みと NTT の比較で 2 か所ずつリンクし合う。zeta-mobius-subset 側には convolution-ntt を足した）。
- **docs/basics/bitwise-independence.md L28・L140・L209**（別の担当が直したところ）：「上位 bitで」の bit と「で」の間に空白がない（§7 の半角と全角の間の空白）。
- **docs/ds/partially-persistent-union-find.md L122**：npm run lint:text の唯一のエラー（`UnionFind => Union-Find`、prh）。この担当の分野の外。

## 直さなくてよいと判断したもの

- **guide/problem-sets L202・guide/roadmap L422 の「上位ビット」**：どちらも生成ブロックの中で、元の basics/bit-operations・bitwise-independence の節の題はすでに「上位 bit」「最下位 bit」に直っている。gen_site.py を流せば追従する。
- **guide/thinking-checklist L45 の「前提」**：要点は「前提：なし」と書き、計算量の見積もりは参照先として添えているだけなので、prerequisites が空なのと食い違わない。
