# roadmap（色別ロードマップ）の検証

- 対象：docs/guide/roadmap.md（stage: draft、updated 2026-10-22）
- 観点：fact・code・clarity・figure（code と figure は、コードも図もないので該当なし）
- 生成ブロック（recent-positions・roadmap-order）の中身は執筆者の担当外なので、手書きの部分と、生成の手順の説明が gen_site.py と合うかを確かめた

## 確かめたこと（問題なし）

- `python3 tools/check_pages.py --page roadmap -v`：エラー 0・警告 0。本文の相対リンクはすべてファイルと anchor が実在する（glossary の difficulty・performance・rating・typical90・edpc・adt、contest-strategy#difficulty-by-position・#time-targets、practice-method#upsolve・#speed・#choosing-problems、knowledge-map#progress、reformulation#then-data-structure）
- 位置ごとの割合（abc400〜480 の 81 回）：.cache/atcoder-problems/problem-models.json から独自に再集計した（scratchpad/v-roadmap/recalc.py）。D 基礎 93%、E 水 59%・基礎 31%・青以上 9.9%、F 青 49%・水 26%・黄 19%・発展 6%・2000 未満 75%、G 黄 38%・発展 49% で本文と一致
- 到達の目安の表：AtCoder Problems のモデル（解く確率は 1/(1+exp(−discrimination·(P−difficulty)))、時間は exp(slope·P+intercept)）で再計算した。A〜D／A〜E は 1200：42／72 分、1600：30／56 分、2000：22／43 分、A〜F は 2000 で 70 分。E・F の解く確率の中央値は 40/8、80/34、96/76%、G はレート 2000 で 15%（「7 回に 1 回ほど」で可）。どれも本文と一致（A〜E は 78 回、A〜F は時間のモデルがそろう 71 回での中央値だが、値は変わらない）
- 6 問体制の E・F の中央値 1528・2132、abc400〜480 の 1286・1744：再集計で一致。abc126 は 2019-05-19、abc319 は 2023-09-09 開催で A〜G の 7 問（ap.py contest abc319）
- 典型90 の★と difficulty の帯（★5 1200〜1599、★6 1600〜1999、★7 2000〜）：E869120 の Qiita 記事の表と一致
- 色変記事の要約：nouka28 氏（2024-05-05）は「実践的な面で考えると…結構少ない」「全部で5つだけ」「ほとんどコンテスト中に必要な知識は水色のときで持っていた」、効いたものに典型力・考察力・速読・デバッグを挙げる。ks2m 氏はローリングハッシュ・形式的べき級数・HL 分解を未習得のまま黄色、「最後は、青diffの正答率が上がったおかげ」。blueberry 氏の記事（2024-12-25）は「6完を安定させたうえで、550点以下ぐらいのG問題は解ける必要があります」。どれも趣旨は正しく、転載にもなっていない。ks2m.hatenablog.com に AI の利用を断る指定は見当たらない
- WebKit のブログ：対象は iOS・iPadOS 13.4 と macOS の Safari 13.1、「seven days of Safari use without user interaction on the site」で LocalStorage を含む script-writable storage を消す、ホーム画面のウェブアプリは独自の日数の数え方で実際の利用に合わせる。本文と一致
- 色ごとのページの列の手順の説明：gen_site.py の roadmap_items（同じ色の前提だけで数えた深さ → 分野の並び → frequency → order、上の帯の節を下のレベルのページから入れる）と合う。頻度の定義は design.md §5.5・catalog/README.md §5 と一致
- 進捗の節：progress.js と overrides/main.html で確かめた。「理解した」のチェック欄はページの上と下（main.html の `{{ checks }}` が 2 か所）にあり、ページのレベルと上の帯の節のレベルごとに 1 つ。「解いた」は .kp-problems の各行の先頭に付く。書き出し・読み込みは kp-progress-io
- E・G の傾向の文：data/recent-abc.yaml と合う（E の考察 11・累積和 10・二項係数の前計算 4、G の DP の発展は Monge・Alien DP・Slope Trick・挿入 DP）
- 文体はだ・である調で統一されている

## 指摘

### 1. 直すべき｜fact｜#recent-positions の F の箇条（105 行）と #practice の「青」の箇条（746 行）

- **問題**：「条件を言い換えてからセグメント木に載せる形が多い」「F の多くは『言い換えてからデータ構造に載せる』形なので」は、本文が典拠にしている最近 30 回の分類と合わない
- **根拠**：data/recent-abc.yaml の F 30 問のうち、reformulation を使ったのは abc454_f・abc459_f・abc479_f・abc480_f の 4 問。このうちデータ構造のページも使うのは abc479_f（転倒数）だけで、セグメント木の系統のページと組むものは 0 問。データ構造のページを使った 11 問の側にも reformulation は 1 問しか入っていない。「多い」「多く」と言える根拠がない
- **直し方**：F の箇条は「データ構造が最も多く（11 問）、言い換えの典型（4 問）が単独のページでは最も多い」のように数で言える事実にとどめる。reformulation#then-data-structure への誘導は「データ構造に載せる前の言い換えは…の節にある」程度にする。「青」の箇条も「F で最も多いのはデータ構造なので、水の列のセグメント木を、条件を言い換えて載せる練習まで含めて身につける」のように、割合の主張を外す

### 2. 直すべき｜fact｜#yellow の 3 つ目の箇条（90 行）と参考（786 行）

- **問題**：著者名を「blueberry1001 氏」と書いているが、記事の Qiita の ID は @bluebery1001（r が 1 つ）で、記事中の名乗りは「Blueberry」。出典の著者名が誤っている（参考の URL は bluebery1001 で正しい）
- **根拠**：https://qiita.com/bluebery1001/items/3253399ebf287e197346 の著者表示
- **直し方**：本文と参考の両方を「bluebery1001 氏」（ID）に直す

### 3. 直すとよい｜fact・clarity｜#practice の表の下の段落（742 行）

- **問題**：「作者が『その帯の参加者の半分ほどが解ける』difficulty の帯として示した」は、かぎかっこが付いているが原文の引用ではない。原文は「Diff. は仮に AtCoder のコンテストに出題された場合、どのレーティング帯の半分の参加者が解きそうかを示しています」。また「その帯の参加者の半分ほどが解ける difficulty の帯」は主語と修飾がもつれて読みにくい
- **根拠**：E869120 の告知記事の表の直前の文
- **直し方**：かぎかっこを外し、「★ごとに difficulty の範囲が決まっていて、仮に AtCoder に出たら、どのレート帯の参加者の半分が解きそうかを表す」のように言い換える。同じ内容が[問題集の案内](problem-sets.md#typical90-stars)に表であるので、そこへのリンクを添えると重複を減らせる

### 4. 直すとよい｜fact・clarity｜#practice の最後の段落（749 行）

- **問題**：6 問体制（abc126〜211）と 7 問体制（abc319〜）だけを書き、その間の 8 問体制（abc212〜318、約 2 年）が抜けている。過去問を選ぶ読者は abc212〜318 をどう扱えばよいか分からない
- **根拠**：research/00 §2.3.4 の中央値：8 問体制の E 1308・F 1866・G 2326（今の E 1286・F 1744・G 2391 に近い）、Ex 2912
- **直し方**：「8 問体制（abc212〜318）の E・F は今とほぼ同じ難しさで、G・Ex は今の G より難しい帯まで広がる」のような 1 文を足す。ここでも位置より difficulty で選ぶ、という結論は同じでよい

### 5. 直すとよい｜clarity｜#practice の「青」の箇条（746 行）

- **問題**：「水の列のセグメント木・累積和」とあるが、累積和（basics/prefix-sum）は基礎のページで、水の列には入らない
- **根拠**：docs/basics/prefix-sum.md の level は基礎、docs/ds/segment-tree.md は水
- **直し方**：「基礎の累積和と水のセグメント木」とするか、累積和を外す（指摘 1 の直しとまとめてよい）

### 6. 直すとよい｜clarity｜#goal の最後から 2 段落目（52 行）・#recent-positions の最後の段落（108 行）

- **問題**：執筆時は節がなかったのでページへのリンクにしたが、同じバッチで節ができている。atcoder-system に `## 位置ごとの difficulty {#difficulty-by-position}`（箱ひげ図つき）、problem-sets に `## 最近の ABC → ページ {#recent-abc}` がある。front matter の related の `atcoder-system#difficulty-by-position`・`problem-sets#recent-abc` もこれで実在する（未解決の点の 1 つ目と 2 つ目は解消）
- **根拠**：docs/start/atcoder-system.md 151 行、docs/guide/problem-sets.md 86 行
- **直し方**：108 行の problem-sets へのリンクを `problem-sets.md#recent-abc` にする。52 行は contest-strategy のままでも正しいが、related と合わせて atcoder-system#difficulty-by-position（図のある方）へのリンクを足すとよい

### 7. 直すとよい｜clarity｜#targets の最後の箇条（78 行）と #yellow の第 1 段落（84 行）

- **問題**：「レート 2000 の人でも G を解くのは 7 回に 1 回ほど」が近い 2 か所で繰り返される
- **直し方**：#yellow では「[到達の目安](#targets)のとおり G はまれにしか解けない」と参照にして、F の 75% が 2000 未満という新しい数だけを置く

### 参考（メインへの申し送り。執筆者の指摘ではない）

- 生成ブロックの見出し「G 問題（黄の帯）」は、G の 49% が発展である本文の説明（47〜52 行）とずれる。gen_site.py の RECENT_POSITIONS の見出しを「黄・発展の帯」にするかはメインで判断してほしい

## 総合の判定

小さな直しで可。直すべき 2 件（F の傾向の主張が分類のデータと合わない、出典の著者名の誤り）、直すとよい 5 件。数値（位置の割合・解く確率・時刻・中央値）と出典の要約、進捗の仕組みの説明は再計算と一次資料で一致した。
