# verify-dp-speedup の報告（バッチ cross-links）

- 検証した担当：dp-speedup（報告 [dp-speedup.md](dp-speedup.md)）。書いた担当とは別に、一次資料・計算・ビルドで確かめた
- 担当の Issue：#67（DP の高速化の発展ページからハブへ戻れるようにする）、#71（学ぶための資料の各行のリンク）のうち docs/dp/ の 5 ページ
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/cross-links（ブランチ fix/cross-links）。ファイルは直していない（この報告だけを書いた）。git は status・diff・show・ls-files だけ
- 見た差分：docs/dp/monge.md・alien-dp.md・slope-trick.md・dynamic-dp.md・inline-dp.md・cht.md（`git diff`）と、担当の報告

## 結論

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #67 | 合格 | 0 |
| #71（担当の 5 ページ） | 合格 | 0 |

## #67：合格

### 完了の条件

- **ハブ以外のページすべてに、ハブへの本文のリンクがある**：front matter が `chapter: DP の高速化` のページは 8 枚（ハブを含む）。ハブ以外の 7 枚のどれにも、本文に dp-speedup-overview へのリンクがある（grep で確かめた。related の行は数えていない）
  - monge L210（#shape-to-tool・#convexity）、alien-dp L195（#convexity）、dynamic-dp L193（#shape-to-tool）、slope-trick L200（#convexity）、inline-dp L194（#shape-to-tool）、cht L210（#shape-to-tool・#convexity）、dp-segment-tree L182（もとからある #shape-to-tool）
- **monge が CHT との使い分けに触れている**：monge L207〜208

### 使い分けの中身（事実）

**monge L207（CHT との関係）**

- $(S_r - S_l)^2$ が要素が非負のとき Monge であることを式で確かめた。行 $i_1 < i_2$・列 $j_1 < j_2$ で $A[i][j] = (S_i - S_j)^2$ とすると、不等式の左辺 − 右辺は $-2(S_{i_2} - S_{i_1})(S_{j_2} - S_{j_1})$ で、$S$ が広義単調増加なら 0 以下になる。乱数の小さい入力（長さ 1〜7、300 回）でも違反は 0。要素に負の数を混ぜると 300 回中 196 回で Monge でなくなるので、「要素が非負なら」の条件は要る
- 展開した $-2 S_i S_j$ が積の項 1 つで、直線は傾き $-2S_j$（広義に減る）、クエリは $S_i$（広義に増える）。cht#lower-envelope の deque の条件（傾きが減る順に追加・クエリが増える）に合う。$K$ 段の区間分割 DP を素朴な DP と deque の CHT（同じ傾きは cht#pitfalls のとおり切片の小さい方を残す）で 2000 回比べ、食い違いは 0
- 「monotone minima の 1 段 $O(N \log N)$ より速く」は本文 L93 の「1 段ぶんを monotone minima で $O(N \log N)$」と同じで、deque の CHT は 1 段ならし $O(N)$。正しい
- 「積の項 1 つなら CHT の方が軽い」は、このページの読者の場面（コストが Monge）でも裏付けがある：コストが $g(i) + h(j) + p(j) q(i)$ で Monge なら、不等式は $(p(j_1) - p(j_2))(q(i_1) - q(i_2)) \le 0$ になり、$q$ が増える範囲では $p$ が減る（逆向きに単調）。よって傾きとクエリは単調に並び、deque の CHT が使える。単調でなくても Li Chao Tree で 1 回 $O(\log N)$ なので、monotone minima・LARSCH・分割統治より重くならない

**monge L208**

- 「区間の中の同じ値の組の個数」は Monge である。組 $(p, q)$ ごとの寄与 $[l \le p][q < r]$ について、差が $([l_1 \le p] - [l_2 \le p])([q < r_1] - [q < r_2]) \le 0$ になる。乱数の入力（300 回）でも違反は 0。値の種類ごとの累積の個数の内積の形になり、積の項 1 つにはまとまらないので、CHT では扱えない。本文 L99 の例と同じ
- 「$i$ だけの項と $j$ だけの項の和なら範囲の最小で済む」は正しい（$\mathrm{dp}[i] = g(i) + \min_j (\mathrm{dp}[j] + h(j))$）。リンク先 dp-segment-tree#which-tool の表と合う

**monge L209**：本文 L101・alien-dp#with-monge と同じ内容。

**alien-dp L192〜195**

- L192：本文 L45（個数を状態に持つと状態数が $K$ 倍）と合う
- L193：本文 L106（Alien DP は 1 つの $K$ ごとに $O(T \log M)$。すべての $k$ が要るなら取り消し付きの貪欲）と、練習 ABC464 G の方針（L187）と合う。凸な列どうしの合成へのリンクは、ハブ L148 と同じ行き先
- L194：Slope Trick の条件はハブ #convexity の 4 行目、CHT・Monge の選び方は本文 L138 と合う。Monge のリンク先 #smawk-larsch は、ハブ #shape-to-tool の「段のない形」の行と同じ行き先（罰金つきの DP は段のない形なので正しい）

**dynamic-dp L190〜193**

- L190：ハブ #shape-to-tool の行列累乗の行（L102）と #algebraic-tools（L125）と合う
- L191：ハブのインライン DP の行（L99）と合う
- L192：本文 L58 の「やり直すと 1 回 $O(S^2 N)$、$Q$ 回で $O(S^2 N Q)$」と同じ式
- L193：ハブの動的 DP の行（L109）・L133 と合う

**slope-trick L200・inline-dp L194・cht L210**：ハブへの 1 文。中身はハブの節の題名どおり。

### ハブの表との食い違い

なし。CHT の行（ハブ L103・L141）の「$i$ だけの項・$j$ だけの項と、積の項 1 つに分かれる」と monge L207 の言い方は同じ条件である。monotone minima の行（L104）・LARSCH の行（L105）・Alien DP の行（L107）・Slope Trick の行（L108）・動的 DP の行（L109）と、各ページの使い分けのリンク先の anchor も一致する。guide/method-comparison・reverse-index-signs の CHT・Monge の行とも食い違わない。

### 手引きとの照合

- 定型の `## 使い分け {#comparison}` で sections に載せていない（§13-1・§14-2）。3 ページとも `{#comparison}` は 1 つだけで、使い分けに近い中身の節（§15-4）もない
- 文の箇条書きは句点で終わる（§15-2）。slope-trick L200 は、句点のない既存の 3 行にそろえている
- リンクは `../<field>/<id>.md#anchor`（§7）。半角で始まるリンクの文字の前の空白も合う。同じ節で同じ手法へ 2 回リンクしていない（§14-23。alien-dp L193・L194 の monge へのリンクは、別の節（畳み込み・LARSCH）を指す別の話題）
- 置いた位置（例題・練習問題の後、参考の直前）は、同じ章の発展の概要 cht・slope-trick と同じである。§4 の overview の並びに使い分けがない点は、担当の提案 1 と #69 でメインが決めればよい（直しは要らない）
- front matter の変更は `updated` だけ（dynamic-dp・inline-dp を 2026-10-29 に。ほかの 4 ページはもとから 2026-10-29）。stage は変わっていない（brief-fix のとおり）

## #71（docs/dp の 5 ページ）：合格

### 完了の条件

5 ページの {#resources} の箇条書き 15 行のどれにもリンクがある。外部リンクは 16 個（monge 2・alien-dp 3・slope-trick 4・dynamic-dp 3・cht 4）。dynamic-dp L154・L157 はサイトの中のページへのリンクで、もとからある。

### 参考の節と §17-10

- 16 個のリンクを、行の 2 つ目のリンク（cht L157 の ageprocpp・slope-trick L150 の hitonanode・dynamic-dp L155 の ikatakos。check_pages の §17-10 の検査は行の最初のリンクしか見ない）も含めてスクリプトで調べた。どれも同じページの参考の節に同じ「[題名](URL)」があり、サイト全体の参考・資料の節でも、同じ URL の題名は 1 通りだけである
- 16 の URL を curl で取得した（どれも付録 B のドメイン。atcoder.jp・codeforces.com は開いていない）。すべて HTTP 200、robots の meta に noai・noimageai はない。ページの題名・h1 は参考の題名と対応する（かんプリンの題名の全角空白 U+3000 も原文どおり）。soi.ch の著者が Daniel Rutschmann であることも本文の「Written by Daniel Rutschmann.」で確かめた
- 資料の説明を元の行と並べて読んだ。意味は変わっておらず、足した説明（cht L159「CHT と Li Chao Tree の両方を扱っている」など）は取得したページの見出し（cp-algorithms の h2 が「Convex hull trick」「Li Chao tree」）と合う。kanpurin の記事に「AlienDP」の見出しがあり、smijake3 の記事が線分と $\log^2$ を扱うことも確かめた
- 書き方（`[著者「題名」](URL)（英語）：説明`、2 つの資料を「と」でつなぐ）は、同じ作業ツリーの resources の担当の 46 ページと同じ

### cht の textlint-disable（L156・L160）

- ageprocpp の題名の「です・ます」は、リンクの文字でも no-mix-dearu-desumasu のエラーになる。規則を 1 つに絞った disable でリスト全体を囲んでいる。ビルドした HTML で、資料の節が 1 つの `<ul>` のまま（コメントがリストを割らない）ことを確かめた
- 手引きにない書き方だが、参考の節の同じ行は既存の素の `<!-- textlint-disable -->` で囲まれていて、これより狭い。手引きに足すかは担当の提案 2 のとおりメインが決めればよい（直しは要らない）

## 別の箇所が壊れていないか

- 新しいリンクの行き先 13 の anchor（cht#lines、monge#smawk-larsch・#convex-max-plus-convolution、slope-trick#breakpoints、alien-dp#with-monge・#undoable-greedy、dp-segment-tree#which-tool、dp-speedup-overview#shape-to-tool・#convexity、matrix-power#dp-transition、inline-dp#diff-per-row、static-top-tree#resources、segment-tree-monoids#matrix）が、ビルドした HTML にある。mkdocs.yml は `validation: anchors: warn` で、ビルドの警告は 0
- 参考の節は 6 ページとも変わっていない。既存の anchor は消えていない
- `gen_site.py --check --diff`：変わるのは docs/llms.txt・graph.json・start/how-to-use.md の版のハッシュだけ（同じ作業ツリーのほかの担当の `updated` の分も含む）。メインが作り直す
- 担当が一時的に作った docs/dp/zz-tl-test-dp-speedup.md は残っていない（`git status` と `ls` で確かめた）

## 検査（どれも書き換えない検査）

- `check_pages.py --page`（monge・alien-dp・slope-trick・dynamic-dp・inline-dp・cht・dp-segment-tree・dp-speedup-overview）：エラー 0・警告 0。全ページでもエラー 0・警告 0
- `fix_problems.py --check --page`（6 ページ）：直すべき行 0
- `npx textlint`（6 ページ）：エラー 0。警告は HEAD と比べて monge 20→19、alien-dp 15→14、slope-trick 17→18、dynamic-dp 7→7、inline-dp 17→17、cht 23→24（担当の報告と一致）。直した行に出る警告は次の 4 件で、どれも残してよい（§13-8・§14-25）
  - cht L157（文の長さ 124）・slope-trick L150（149）：1 行に題名の長いリンクを 2 つ並べたため
  - monge L171（124）：元の 126 字からの残り（数式を含む文）
  - cht L158（no-doubled-joshi「に」）：元の行からある「場合に … になる」がそのまま残ったもの（規則ごとの件数は増えていない）
- check_snippets・check_svg・`node --test "tests/viz/*.test.mjs"`：コード片・図・動く図を変えていないので対象外
- 作業用フォルダへのビルド（`uv run mkdocs build -q -d <作業用フォルダ>/site`）：成功。`python3 -m http.server 47213` を立てて開き、幅 390px で撮った（使い終えて止めた）
  - ライト：monge・alien-dp・dynamic-dp の使い分けと資料、cht・slope-trick の資料と使い分け、inline-dp の使い分け
  - ダーク：monge・alien-dp の使い分け、cht・dynamic-dp の資料
  - KaTeX の数式（$(S_i - S_j)^2$ の展開、$O(S^2 N Q)$ など）は崩れずに出る。リンク・箇条書き・表も崩れていない
  - 画像：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/verify-dp-speedup/shots/ の combo1.png〜combo4.png（4 枚目がダーク）
  - fragment（`#comparison`）付きの URL を直接撮ると真っ白になったので、作業用フォルダに置いた iframe の包みのページ（wrap.html）で節まで送って撮った。サイトの不具合ではない

## 直しが要る点

なし。

## 担当外の気づき（メインへ。直しの要否は書いた担当・メインが決める）

1. #71 の完了の条件「どの行にもリンクがある」について、tree/static-top-tree L142（ABC351 G の公式解説。atcoder.jp なのでリンクしない）だけは、リンクが 1 つもない。resources の担当の報告の「判断してほしい点 2」に挙がっている。comb/stirling-first L170 はページの中の `#practice` へのリンクだけを持つ
2. 参考の節に前からある題名の形のうち、ページの題名と細部が違うものがある：ei1333「Luzhiled's Library: Slope Trick」（ページの title は「Slope Trick | Luzhiled’s Library」）、hitonanode の題名は「（」の前の半角の空白を除いている、noshi91 の d-辺 は原文では $d$-辺。どれも同じ URL ではサイト全体で 1 通りの題名にそろっていて、§17-10 には反しない。今回の直しの範囲の外である

## 使用量の目安

- 道具の呼び出し 約 60 回。Web の取得：curl で 16 URL（付録 B のドメインだけ）。所要時間 約 50 分
