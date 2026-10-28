# verify-basics-dp の報告（バッチ minor-content）

- 検証した担当：basics-dp（報告は planning/batches/fix/minor-content/basics-dp.md）
- Issue：#11〜#20（`gh issue view` で読んだだけ。コメント・編集・クローズはしていない）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content）。ファイルは直していない（書いたのはこの報告だけ）。git は読むだけ
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/verify-basics-dp（ビルド site/、撮影 shots/、生成物の比較 gen/、textlint の比較、直し方の案を試した写し trial/）

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #11 3^N の目安 | 合格 | 0（逆引き辞典の作り直しはメインの gen_site 待ち） |
| #12 prefix-sum の重複 | 合格 | 0 |
| #13 fix-variable へのリンク | 合格 | 0 |
| #14 マトロイドとクラスカル法 | 合格 | 0 |
| #15 Monge の添字の大小 | 合格 | 0（逆引き辞典の作り直しはメインの gen_site 待ち） |
| #16 DP の型の地図 | 合格 | 0 |
| #17 Slope Trick の出題数 | 合格 | 0 |
| #18 ナップサックの目安 | 合格 | 0 |
| #19 前提の過不足 | 直しが要る | 2（どちらも alien-dp。cht は合格） |
| #20 木 DP のスタック | 合格 | 0 |

## 直しが要る点

### 1. #19 alien-dp：前提から DP のページが消えた（必須）

- **場所**：docs/dp/alien-dp.md 11 行目（prerequisites）・39 行目（要点の前提）
- **理由**：monge を外した結果、前提の閉包は {binary-search, sorting-techniques} だけになった。直す前は monge → dp-sequence-partition → dp-prefix-sum → … → dp-basics の鎖で DP のページが 4 つ届いていた（front matter から計算した）。一方、本文の核は DP の状態と遷移を使う。
    - 導入：「DP の状態から『ここまでに選んだ個数』の次元を外す方法である」
    - #penalty：「DP なら、遷移で 1 個選ぶたびに値から $\lambda$ を引くだけ」
    - #binary-search-lambda のコード片（罰金つきの DP）
    - 例題 ABC218 H の方針：「直前のランプの色を状態に持つ DP」

  #with-monge の外には DP のページへのリンクもない（本文のリンクは binary-search・glossary・ternary-search・priority-queue・linked-list・greedy-priority-queue・slope-trick だけ）。チェックリスト F6（前提にない手法を説明なしに使う）と設計書 D12（直接の前提を書き、推移的に届くものだけを省く）に当たる。ビルドしたページの下部の「前提」も「二分探索 基礎」だけになり、知識マップでは Alien DP が二分探索だけにつながる。同じ章の cht・dp-speedup-overview は dp-basics を前提に持つ。担当の報告の「判断してほしい点 1」と同じ件である。直したことで生じた不足なので、直しが要ると判断した
- **直し方の案**：prerequisites を `[dp-basics, binary-search]` にし、要点の前提を「[DP の基本](../dp/dp-basics.md)、[二分探索](../basics/binary-search.md)」にする。作業用フォルダの写し（trial/）で試したところ、check_pages はエラー 0・警告 0 だった。ロードマップ（発展）での Alien DP の位置は、今の直しと同じ 5 番（Monge の次）のままである

### 2. #19 alien-dp：#with-monge の冒頭の文で、全角と半角の間に空白がない（必須・軽い）

- **場所**：docs/dp/alien-dp.md 128 行目
- **理由**：「この節は[Monge 性による DP の高速化](../dp/monge.md)を前提にする。」は、表示が「この節はMonge 性による…」になる（撮影で確かめた）。手引き §7「半角英数字と全角文字の間に空白を入れる」に反する。担当が手本に挙げたページも空白を入れている（static-top-tree 45 行目「この節は [HL 分解]」、lcs 183 行目「この節は [bitDP]」）。サイト全体でも、仮名・漢字の直後に半角で始まるリンクを置く 656 か所のうち 583 か所が空白ありである。textlint はリンクの境目を見ないので、この形を検出しない
- **直し方の案**：「この節は [Monge 性による DP の高速化](../dp/monge.md)を前提にする。」

## Issue ごとに確かめたこと

### #11 3^N で間に合う N の目安（合格）

- complexity-estimation 60 行目「$3^N$ は $N \le 15$〜$16$ 程度まで」に、次の箇所がそろった：bit-operations 19・38 行目、subset-enumeration-dp 18・37 行目、method-comparison 217 行目、recursive-enumeration 194 行目。早見表 49・147 行目、reverse-index-constraints 89・441 行目、bell-number 137・143 行目とも食い違わない
- $N = 18$ に触れる箇所にはどれも条件がある：subset-enumeration-dp 37 行目（内側の処理が軽ければ）・45・88・204 行目、bit-operations 146 行目。条件なしで $3^N$ に $N \le 18$ を当てる箇所は、手書きのページには残っていない（生成物の reverse-index-constraints 146・147 行目と docs/index/ は gen_site の作り直しで替わる）
- 数値：$3^{15} = 14348907$、$3^{16} = 43046721$、$3^{18} = 387420489$ を計算で確かめた。要点の「$1.4 \times 10^7$〜$4.3 \times 10^7$」と合う
- 生成物：gen_site の出力をメモリで作り、作業用フォルダに写して比べた（作業ツリーには書いていない）。逆引き辞典（制約から）では 2 行とも「上限が 20 以下」の帯に入り、条件つきの「N = 18 まで」も行に残る
- 任意：reverse-index-constraints 112 行目（手書き）の「$N \le 16$〜$18$ のように幅のあるサインは…」は、この直しで当てはまるサインがなくなる。規則の例としては読めるので直しは要らない。作り直しのついでに「$N \le 16$〜$20$」（bitDP）などに替えてもよい

### #12 prefix-sum の重複（合格）

- #next-tools は導入・表・2 段落だけになった。消した 4 項目の行き先（prefix-sum-counting・prefix-sum-2d・imos・dp-prefix-sum）は、#next-steps の 4 項目が節へのリンクで指している。#next-steps の最後の項目は #next-tools へ戻る。anchor は変わっていない

### #13 fix-variable へのリンク（合格）

- binary-search 136 行目の末尾のリンクは fix-variable#fix-middle（見出し「真ん中を固定して左右を独立に数える」）を指す。添え書き「位置の条件 $i < j < k$ も付くときは」は、fix-middle 67 行目の書き分け（位置の条件があれば BIT、なければ二分探索）と合う
- brute-force 128 行目の 1 文は fix-variable#speed-up を指す。どちらの anchor もあり、strict のビルドが通る

### #14 マトロイドとクラスカル法（合格）

- $C \ge \max w$ なら $C - w \ge 0$ である。全域木 $T$ について $\sum_{e \in T} (C - w_e) = C(N - 1) - \sum_{e \in T} w_e$ なので、置き換えた重みで最大の木と元の重みで最小の木は一致する。$C - w$ は $w$ について減少なので、重い順は軽い順と同じになる（同点の並びも保たれる）
- 置き換えた重みに負がないので、65 行目の「負になったところで止める」は働かない。貪欲は閉路を作らない辺を最後まで足すので、結果は（連結なら）全域木になる。Issue が指摘した「符号を反転すると全部負になり、1 本も足さない」という飛躍はなくなった
- 任意：$C(N - 1)$ は関数の呼び出しにも見えるので、$(N - 1)C$ と書けば誤読がない（好みの範囲）

### #15 Monge の添字の大小（合格）

- 要点・signs の「$a \le b \le c \le d$」は、62 行目の言い直し（$l_1 \le l_2 \le r_1 \le r_2$）と一致する。行列の定義（行 $i_1 < i_2$・列 $j_1 < j_2$）を区間に移したもの（$a = l_1$、$b = l_2$、$c = r_1$、$d = r_2$）とも合う。$a = b$・$c = d$ のときは両辺が等しく、$b = c$ のときは空区間のコスト $c(b, b)$ を含む四辺形不等式（Knuth-Yao で使う形）になる
- alien-dp 132 行目の「$a < b < c < d$」は残っている。区間分割 DP の行列では $j \ge i$ の成分が $+\infty$ なので、要るのは狭義の場合だけである。どちらの書き方も正しく、直しは要らない
- signs は front matter で KaTeX を使わず、引用符で囲んである。逆引き辞典（言い回しから）と docs/index/dp.md の行は作り直しで替わる

### #16 DP の型の地図（合格）

- 表に 2 行が足され、区間 DP の行に「（区切るだけなら区間分割 DP）」が添えてある。リンク先の dp-grid・dp-sequence-partition はどちらも reviewed で、行の言い回しは両ページの summary と合う。幅 390px・ダークモードでも 3 列の表は崩れず、横にはみ出さない
- 任意：見出し「DP の型の地図（列・区間・集合・桁・木・順列・確率・ゲーム・高速化）」にグリッドがない。手引き §13-2 では sections の title の変更は執筆者が行ってよい。直すなら見出しと title を同時に「（列・グリッド・区間・…）」にする（anchor の map は変えない）。Issue の完了の条件には入っていない

### #17 Slope Trick の出題数（合格）

- `tools/ap.py show`：abc217_h は H. Snuketoon（diff 3112、2021-09-04）、abc458_g は G. Children Yearn for the Evil Kindergarten（diff 2831、2026-05-16）。ABC458 G は力試し（#challenge、188 行目）にあり、frequency_evidence の「recent 1（abc458_g）」と数が合う
- 任意：「ABC217 H（2021 年）と、その変形で解く ABC458 G」の「その」は、直前の ABC217 H を指すとも読める。「Slope Trick の変形で解く」と書けば曖昧さがない。どちらに読んでも事実は変わらないので、直しは要らない

### #18 ナップサックの目安（合格）

- $100 \times 10^6 = 10^8$ で、直前の目安と合う。要点・signs の「$NW \le 10^7$〜$10^8$」とも、例題の「$N \le 100$、$W \le 10^5$ なので $10^7$」（実際の制約）とも食い違わない

### #19 前提の過不足（直しが要る：alien-dp。cht は合格）

- alien-dp：Monge に頼るのは #with-monge（冒頭で前提と書いた）と、そこへの内部リンク（74・90 行目）、練習の ABC355 G の方針（188 行目。#with-monge へリンク）だけである。#penalty・#binary-search-lambda・#undoable-greedy・#library・例題は Monge なしで読める。同じ節の 2 回目の monge へのリンクを文字にしたのは手引き §14-23 に合う。ただし、上の直しが要る点 1・2 がある
- cht：凸包に頼るのは双対の段落（97 行目。convex-hull#cht-duality へのリンクは残っている）だけである。下側の包絡線は本文で定義し、不要な直線の判定は掛け算の不等式で書いてある（$(b_h - b_f)(a_f - a_g) \le (b_g - b_f)(a_f - a_h)$ を交点の比較から導き直して確かめた）。related の `convex-hull#cht-duality` は check_pages の anchor の検査を通り、graph.json では convex-hull になる。convex-hull の「次に読む」から cht は外れるが、convex-hull の本文（153・355 行目）と related から cht へ行ける
- 生成物：ロードマップ（発展）で Alien DP は 77 番から 5 番（Monge の次）へ、CHT は 7 番から 8 番へ移る。並びは自然である

### #20 木 DP のスタック（合格）

- 223 行目は cpp-environment#stack-depth と同じ見方になり、その節へリンクしている（手元は 8 MiB が多い、上限を広げるか非再帰にする、AtCoder では深い再帰も通ることが多い、深さ $10^6$ 超や上限が分からないときは非再帰）。3 文目は tree-traversal 142 行目と同じ文で、graph/dfs 109 行目とも合う。リンクの文字はページの題名「AtCoder と手元の C++ 環境」である

## 検査

- `python3 tools/check_pages.py --page <15 ページ>`：エラー 0・警告 0。全ページ（353）でもエラー 0・警告 0
- `npx textlint <15 ファイル>`：エラー 0。警告は、直す前（`git show HEAD:` の写し）と直した後で同じ 256 件だった（ファイルと規則ごとの件数も同じ）。直した行に出る警告は 2 件で、どちらも直す前からある。recursive-enumeration 194 行目の文の長さ（数式の文字を数えた分を含む）と、tree-dp 223 行目の「が」の重複（変えていない冒頭の「再帰が深すぎる：木が」）である
- `python3 tools/fix_problems.py --check --page <id>`（method-comparison を除く 14 ページ）：直すべき行 0
- `uv run mkdocs build -q --strict -d <作業用フォルダ>/site`：終了コード 0。作業ツリーの状態は変わっていない
- 表示：作業用フォルダで http.server（127.0.0.1:37241。使い終えて止めた）を立て、ヘッドレスの Chrome を CDP で動かした。15 ページの直した箇所を幅 390px のライト・ダークで撮った（shots/ の 36 枚）。どのページも数式のエラー（.katex-error）は 0、描かれていない数式も 0 で、横のはみ出しはなく、ダークモードでは slate になった
- 生成物：gen_site の出力をメモリで作り、作業用フォルダの gen/ に写して比べた（作業ツリーには書いていない）。変わる 14 ファイルのうち、この担当の分は docs/index/basics.md・docs/index/dp.md・reverse-index-constraints・reverse-index-signs・roadmap・graph.json と、llms.txt・how-to-use の版である。ほかの担当の分（なもりグラフなど）も含む
- check_snippets・check_svg・tests/viz：コード片・図・動く図は変わっていないので流していない

## メインに伝えること

- #11・#15・#19 の完了の条件の「`tools/gen_site.py` で作り直してある」は、メインの作業として残っている
- 直しが要る点 1 は front matter の prerequisites の変更である。担当に直させるかメインが直すかを決めてほしい
- 任意の点（#11 の reverse-index-constraints 112 行目、#14 の $(N - 1)C$、#16 の見出し、#17 の「その」）は直さなくても合格である

## 使用量の目安

- 道具の呼び出し：約 60 回。Web の取得：0 回（atcoder.jp・codeforces.com は開いていない。問題は `tools/ap.py` で確かめた）
