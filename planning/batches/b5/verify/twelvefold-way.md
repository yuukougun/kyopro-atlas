# b5 検証：twelvefold-way

- 対象：docs/comb/twelvefold-way.md、docs/img/twelvefold-way/table-n4-k3.svg（snippets はなし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：図は `python3 tools/render_svg.py twelvefold-way --scale 2` で 360px・720px の PNG にして目で確かめた（白の背景つきなのでダークでも読める）。コード片がないので code.md の C1〜C8 は対象なし

## 実行して確かめたこと

- `python3 tools/check_pages.py --page twelvefold-way`：エラー 0・警告 0
- リンク先の anchor：counting-basics#twelvefold-cells・#permutations、stars-and-bars#stars-bars・#at-most・#pitfalls、binomial-coefficient#meanings、bell-number#size・#recurrence、partition-number#recurrence、inclusion-exclusion#surjection・#symmetric、multinomial-coefficient#meaning・#same-size-groups、generating-function-counting#formulas、burnside-lemma#why-not-divide、counting-dedup#representative・#min-index、basics/recursive-enumeration#partition、glossary#injection・#surjection、start/notation.md はすべてある
- 全探索（作業用の場所の Python。写像を全部作り、玉・箱の区別を消して数える）と、表の 12 個の式を n = 0..5、k = 0..4 で比べた。一致しないのは n = k = 0 の「玉を区別せず箱を区別する」の制限なし C(n+k−1, n) と 1 個以上 C(n−1, k−1) の 2 つだけ（全探索は 1、範囲の外を 0 とする二項係数の式は 0）。指摘 1
- 本文の数値：n = 4, k = 3 の 81・0・36／15・0・3／14・0・6／4・0・1、n = 2, k = 3 の単射の列 6・3・1・1、3·1 + 7·6 + 6·6 = 81（空の箱が e 個なら k!/e! 回）、C(3,2)/3! = 1/2、3·1 + 3·14 + 1·36 = 81、3·1 + 3·3 + 1·3 = 15、15 − 3·5 + 3·1 − 0 = 3、確認問題の S(6,1..3) = 1・31・90、122、540、729 − 192 + 3 = 540、p(6,3) = 7、ちょうど 3 個の分割 3 通り = p(3,3)：すべて一致
- #surjection の 2 つの恒等式（k^n = Σ C(k,j) j! S(n,j)、C(n+k−1,n) = Σ C(k,j) C(n−1,j−1)）と包除の 2 つの式を n = 0..6、k = 0..5 で確かめた。1 つ目と全射の包除は常に成り立つ。二項係数の系統の 2 つは n = 0（k ≥ 1）で、範囲の外を 0 とする約束だと C(−1, −1)・C(−1, 0) が 0 になって崩れる（指摘 1 と同じ根）
- p(n, k) を「部分が k 以下」と定め「k 個以下」と等しいとする点は共役で正しく、partition-number#recurrence の定義（部分が k 以下）と一致。drken 氏の記事も P(n,k) を「k 個以下の 1 以上の整数の和」と言い換えている
- k! の逆元が法が素数で k より大きいときにある、包除 1 つの値が O(k log n)（k+1 項、累乗が O(log n)、二項係数は前計算）、S・p の表が O(nk)：正しい。要点・front matter の complexity・本文の表で一致
- 参考の URL：qiita.com は付録 B にある。`tools/check_noai.py` でも noai の指定なし。題名「「写像12相」を総整理！ 〜 数え上げ問題の学びの宝庫 〜」が一致。記事の例と本文の例（n = 4, k = 3）・文の並びは別で、近すぎない（F8）
- 執筆者の未解決の点：stars-and-bars:161 は「玉を区別しない（重複組合せ）で箱の順番を区別しないなら分割数など」という文脈なので、今のままでも誤りではない（このページの直しは要らない）。生成ブロックはなく、catalog の visual は priority 2・static で静的な図で足りる
- 図：値・式が本文の表と一致。360px で値・ラベルは読め、重なり・はみ出しなし。viewBox 400×316 と width・height が同じ比。代替テキストに 12 個の値がすべてある

## 指摘

### 1. 直すべき｜事実（F2・F3）｜#table の「境界の値は式だけに任せず確かめる」の段落

- **問題**：n = k = 0 で崩れる式として $\binom{n-1}{k-1}$ だけを挙げているが、同じ行の制限なしの $\binom{n+k-1}{n}$ も $\binom{-1}{0}$ になり、このページが宣言した「範囲の外を 0 とする二項係数」では 0 を返す（正しくは 1）。しかもリンク先の stars-and-bars#pitfalls が述べているのは制限なしの式（$\binom{n+k-1}{k-1}$ の $k = 0$）の方で、本文の例とリンク先の話題が食い違う。読者は制限なしのマスは安全だと読む
- **根拠**：全探索と式の比較で n = k = 0 の 2 マスだけが不一致（全探索 1、式 0）。binomial-coefficient#out-of-range の約束（k > n なら 0）で $\binom{-1}{0} = 0$。さらに #surjection の二項係数の系統の恒等式 2 つも n = 0（k ≥ 1）で同じ理由で崩れる
- **直し方**：例えば「$n = k = 0$ はどのマスも 1 だが、二項係数の行は $\binom{n+k-1}{n} = \binom{-1}{0}$、$\binom{n-1}{k-1} = \binom{-1}{-1}$ になり、範囲の外を 0 とする関数ではどちらも 0 を返す。$n = 0$ は式に入れず別に扱う」とする。#surjection の恒等式には「（$n \ge 1$）」を添えるとよい

### 2. 直すとよい｜分かりやすさ（U2）｜#table の「箱を区別しない」2 行の 1 個以下のマス

- **問題**：「$n \le k$ なら 1、そうでなければ 0」に理由がなく、行き先も「—」なので読者はどこにも答えを探せない。なぜ 1 通りなのかで一瞬止まる
- **根拠**：ほかの 10 マスは行き先のページか式で根拠が追えるが、この 2 マスだけ説明がない
- **直し方**：表の下か 1 個以下の列の説明（「1 個以下の列は n > k だと…」の段落）に「箱を区別しないなら、どの玉も別々の箱に 1 個ずつ入る入れ方はどれも同じに見えるので 1 通り」と 1 文足す

### 3. 直すとよい｜手引き（§14-11）｜#reading の末尾の確認問題 2 つ

- **問題**：確認問題が #reading の節の中に置かれている。手引き §14-11 は `## 確認問題 {#quiz}` にまとめるとする（既存のページにも節の中に置いたものが多いので、直すべきとまではしない）。2 問目（p(n,k) の定義の違い）は #reading の話題ではなく #table の記法の話で、節の中に置くと断片で読むとき（U6）に浮く
- **根拠**：planning/style-guide.md §14-11
- **直し方**：参考の前に `## 確認問題 {#quiz}` を立て、2 問を移す（sections には載せない）

### 4. 直すとよい｜図（G5）・事実（F3）｜table-n4-k3.svg の「玉を区別し、箱を区別しない・制限なし」のマス

- **問題**：図の式は「S(n,1)+…+S(n,k)」、本文の表は $\sum_{j=0}^{k} S(n, j)$ で、n = 0 のときだけ値が違う（図の式は 0、正しくは 1）。値の例（n = 4）には影響しない
- **根拠**：S(0,0) = 1、S(0,j) = 0（j ≥ 1）
- **直し方**：図を「S(n,0)+…+S(n,k)」か「Σ S(n,j)」にして本文とそろえる。あるいは指摘 1 の直しで「n = 0 は別に扱う」と書けば、このままでもよい

### 5. 直すとよい｜図（G3）｜table-n4-k3.svg の 1 個以下・両方区別するマスの式「kPn」

- **問題**：添字の k・n が font-size 8 で、360px の幅では約 7px になり読みにくい
- **根拠**：render_svg の 360px の PNG で確かめた（読めるが小さい）
- **直し方**：添字を 9〜9.5 にする。ほかの文字は 360px で 9.5px 以上あり問題ない

## 総合の判定

小さな直しで可。直すべき 1（n = k = 0 の境界で崩れる式の挙げ漏れ）、直すとよい 4。12 マスの式・値・図・本文の数値はすべて全探索と一致し、リンクと出典も正しい。
