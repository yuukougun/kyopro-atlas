# dp-speedup の報告（バッチ cross-links）

- 担当の Issue：#67（DP の高速化の発展ページからハブへ戻れるようにする）、#71（発展の概要の「学ぶための資料」の各行にリンクを付ける）のうち docs/dp/ の 5 ページ（alien-dp・cht・dynamic-dp・monge・slope-trick）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/cross-links（ブランチ fix/cross-links）。git は読むだけで、commit などはしていない
- 直したファイル：docs/dp/monge.md・docs/dp/alien-dp.md・docs/dp/slope-trick.md・docs/dp/dynamic-dp.md・docs/dp/inline-dp.md・docs/dp/cht.md。docs/dp/dp-segment-tree.md はもとからハブへの本文のリンクがある（L182）ので変えていない。ハブ docs/dp/dp-speedup-overview.md も変えていない
- front matter：`updated` だけを変えた。dynamic-dp・inline-dp を 2026-10-22 → 2026-10-29 にした。monge・alien-dp・slope-trick・cht はもとから 2026-10-29（minor-content の分）なので変えていない。stage・sections・related は変えていない
- 参考の節・生成物・共有のファイル（手引き・用語集・prh.yml・台帳など）は変えていない。`tools/gen_site.py` は `--check --diff` だけを流した

## #67 DP の高速化の章の各ページからハブへのリンク（完了）

完了の条件の確かめ：章（chapter: DP の高速化）のハブ以外の 7 ページすべてに、ハブ（dp/dp-speedup-overview）への本文のリンクがある。monge は使い分けの節で CHT に触れている。

| ページ | ハブへのリンク | 直した行 |
| --- | --- | --- |
| monge | `#shape-to-tool`・`#convexity`（新しい使い分けの節） | L205〜210（節を足した） |
| alien-dp | `#convexity`（新しい使い分けの節） | L190〜195（節を足した） |
| dynamic-dp | `#shape-to-tool`（新しい使い分けの節） | L188〜193（節を足した）、updated L29 |
| slope-trick | `#convexity`（既存の使い分けに 1 行） | L200 |
| inline-dp | `#shape-to-tool`（既存の使い分けの表の後の段落に 1 文） | L194、updated L29 |
| cht | もとから `#shape-to-tool` があり、`#convexity` を足した | L210 |
| dp-segment-tree | もとから `#shape-to-tool` がある（L182）。変えていない | — |

### 使い分けの節を置いた位置（monge・alien-dp・dynamic-dp）

- 定型の `## 使い分け {#comparison}` にし、sections には載せていない（§13-1・§14-2）
- 置いたのは参考の直前（例題・練習問題の後）である。手引き §4 の overview の並び（何ができるか → サイン → 計算量 → library → resources → 例題）を崩さず、technique の並び（… → 確認問題 → 使い分け → 参考）の終わりの部分と同じになる。同じ章の発展の概要 cht・slope-trick も、使い分けを参考の直前に置いている
- 発展の概要のうち、使い分けの位置がほかと違うページがある：k-shortest-paths・offline-dynamic-connectivity は library の前、multiplicative-function は resources の前。そろえるかは手引きの提案（下）と #69（節の並び）で決めてほしい

### monge の使い分け（L207〜210）

1. **CHT との使い分け**：コストを展開して $i$ と $j$ の両方を含む項が積の項 1 つだけなら CHT の方が軽い、と書いた。区間の和の 2 乗 $(S_i - S_j)^2$ は、要素が非負なら Monge であり、CHT の形にも当てはまる。このとき傾きとクエリはどちらも単調なので、deque の CHT で遷移 1 回がならし $O(1)$ になり、monotone minima の 1 段 $O(N \log N)$ より速い
   - 確かめたこと：$(S_r - S_l)^2$ の Monge の不等式の両辺の差は $2(S_{r_2} - S_{r_1})(S_{l_1} - S_{l_2})$ で、$S$ が広義単調増加（要素が非負）なら 0 以下になる（monge#definition の「凸関数の差」の規則と同じ条件）。CHT の傾き $-2S_j$ は広義に減り、クエリ $S_i$ は広義に増えるので、cht#lower-envelope の deque がそのまま使える（同じ傾きの扱いは cht#pitfalls）
2. **Monge の方法が要る場合**：積の項 1 つにまとまらないコスト（区間の中の同じ値の組の個数など。monge#monotone-minima の自作の要点に出てくる例）は CHT では扱えない。逆に積の項がなく $i$ だけの項と $j$ だけの項の和なら、範囲の最小で済む（dp-segment-tree#which-tool へリンク）
   - 確かめたこと：「区間の中の同じ値の組の個数」が Monge であることは、組 $(p, q)$ ごとの寄与 $[l \le p][q < r]$ の差が $([l_1 \le p] - [l_2 \le p])([q < r_2] - [q < r_1]) \ge 0$ になることで確かめた
3. **Alien DP**：区間の個数 $K$ が大きく $K$ 段を回せないなら alien-dp#with-monge（本文の monotone-minima の節の終わりと同じ内容の要約）
4. **ハブ**：`#shape-to-tool`（早見表）と `#convexity`（確かめ方の表）

### alien-dp の使い分け（L192〜195）

1. $K$ が小さく個数を状態に持つ DP で間に合うなら Alien DP は要らない
2. すべての $k$ が要るなら、取り消し付きの貪欲（同じページの #undoable-greedy。本文の「すべての k が要る問題ではこちらを使う」と同じ）か、凸な列どうしの (max,+) 畳み込み（monge#convex-max-plus-convolution）を考える
3. 凸なのが個数についての答えではなく、DP の値を状態の値 $x$ の関数とみた折れ線なら Slope Trick。罰金つきの問題の遷移はコストの形で CHT か Monge（monge#smawk-larsch。同じページの #with-monge の内容の要約）
4. ハブの `#convexity`

### dynamic-dp の使い分け（L190〜193）

1. 書き換えがなく同じ遷移を巨大な回数くり返すだけなら行列累乗（math/matrix-power#dp-transition）
2. 入力の書き換えではなく、DP の段ごとに前の段の数か所だけが変わるならインライン DP（inline-dp#diff-per-row）
3. 書き換えの回数 $Q$ が少なく、やり直しの $O(S^2 N Q)$ が間に合うなら行列にしなくてよい（本文 #what-it-does の見積もりと同じ式）
4. ハブの `#shape-to-tool`

### そのほかのページ

- slope-trick L200：「CHT・Monge・Alien DP・Slope Trick の確かめ方と選び方は、凸性を使う高速化の使いどころ（#convexity）にまとめる」。既存の行にそろえて句点なし
- inline-dp L194：使い分けの表の後の段落に「表にない形の遷移は、貰う形の式の右辺から DP の高速化の選び方（#shape-to-tool）の早見表で道具を選ぶ。」を足した
- cht L210：既存の「全体の選び方は [DP の高速化の選び方](#shape-to-tool)にまとめる。」に、`#convexity` への「CHT・Monge・Alien DP・Slope Trick の確かめ方は…」を足した（Issue の条件はもとから満たしていたが、凸性の 4 ページがどれも `#convexity` を指すようにそろえた）

## #71 学ぶための資料の各行のリンク（担当の 5 ページは完了）

### 書き方

- 各行を、参考の節の同じ資料の行と同じリンク `[著者「題名」](URL)` で始め、「：」の後に何が学べるかを書いた。リンクの文字も URL も参考の行のまま（§17-10）。行がリンクで始まるので、check_pages の §17-10 の検査（参考・学ぶための資料の節で「- [題名](URL)」と始まる行の最初のリンクを比べる）に入る。同じ作業ツリーで残りの 46 ページを直した担当（resources.md）と同じ形である
- 言語の注記は、リンクの直後に（英語）（中国語）と置いた（resources.md と同じ）
- 1 行に資料が 2 つある行は、元の行の説明を変えずに 2 つのリンクを「と」でつないだ（`](URL)と [`。「」」と「と」の間に空白を入れず、「と」と半角で始まるリンクの文字の間に空白を入れる。§7）。cht L157・slope-trick L150・dynamic-dp L155 の 3 行
- 説明の文は元の行の内容を変えていない。主語がリンクに移った文を「：」の後の形に直し、資料の種類（スライド・記事・解説）を説明に残した

### 直した行

| ページ | 資料の節の行 | 内容 |
| --- | --- | --- |
| monge | L170〜171 | tatyam「Monge の手引書」（「日本語の資料」→「日本語のスライド」）、noshi91「簡易版 LARSCH Algorithm」 |
| alien-dp | L155〜157 | noshi91「Monge グラフ上の d-辺最短路長を計算するアルゴリズム」、Daniel Rutschmann「Alien Optimization」（英語）、かんプリン「競技プログラミング　典型問題メモ」 |
| slope-trick | L148〜150 | maspy の 2 本、ei1333「Luzhiled's Library: Slope Trick」と hitonanode「Slope trick（…）」（1 行に 2 つ） |
| dynamic-dp | L154〜156 | 元の 1 行目を 2 行に分けた：サイトの中のページを指す L154（行列累乗・セグメント木に何を載せるか。もとからリンクあり）と、例題の解説 kmjp と ikatakos の L155（1 行に 2 つ。3×3 と 4×4 を比べる勧めなので分けていない）。L156 は OI Wiki「动态 DP」（中国語）。L157 の Static Top Tree の行は、もとから static-top-tree#resources へのリンクがあるので変えていない |
| cht | L156〜160 | satanic0258 と ageprocpp（1 行に 2 つ）、smijake3「Li Chao Treeのメモ」、cp-algorithms「Convex hull trick and Li Chao tree」（英語） |

- cht の ageprocpp の題名「Convex Hull Trickを知っていますか？僕は知っています。」は、リンクの文字でも textlint の `ja-technical-writing/no-mix-dearu-desumasu` のエラーになる（試験で確かめた。`ja-space-between-half-and-full-width` と prh はリンクの文字を見ない）。そこで資料の節のリストの前後を `<!-- textlint-disable ja-technical-writing/no-mix-dearu-desumasu -->`〜`<!-- textlint-enable … -->` で囲んだ（L156・L160）。該当の行だけを囲むとリストが 2 つの `<ul>` に割れる（参考の節の L213〜215 はそうなっている）ので、リスト全体を囲み、止める規則を 1 つに絞った

### 確かめたこと

- 5 ページの資料の節の外部リンク 16 個（monge 2・alien-dp 3・slope-trick 4・dynamic-dp 3・cht 4）のすべてが、同じページの参考の節に同じ「[題名](URL)」としてある（題名も URL も一致。スクリプトで確かめた）。どの行にもリンクがある（サイトの中のページを指す dynamic-dp の 2 行は相対リンク）
- 参考の節は 7 ページとも元のまま（差分なし）。front matter の差分は `updated` だけ
- この 16 の URL を curl で取得し、どれも HTTP 200 で、ページの題名が参考の題名と合うことを確かめた。robots の meta に noai・noimageai はない（どのドメインも付録 B にある。speakerdeck は付録 B に挙がる tatyam_prime の「Monge の手引書」そのもの）。soi.ch の「Alien Optimization」の著者が Daniel Rutschmann であること（ページの「Written by Daniel Rutschmann.」）も確かめた。atcoder.jp・codeforces.com は開いていない

## 検査（どれも書き換えない検査）

- **check_pages**：`--page` で 7 ページともエラー 0・警告 0。全ページでもエラー 0・警告 0（§17-10 の「同じ URL の出典の題名が違う」も 0）。作業用フォルダの写しで資料の行の題名を 1 字変えると「同じ URL の出典の題名が違う」の警告が出ることも確かめた（この形の行が検査に入っている）
- **textlint**（7 ページ）：エラー 0。警告は monge 20 → 19、alien-dp 15 → 14、slope-trick 17 → 18、dynamic-dp 7 → 7、inline-dp 17 → 17、cht 23 → 24、dp-segment-tree 35 → 35（変えていない）
  - 新しく出た警告は 2 件で、どちらも 1 行に 2 つのリンクを並べた行の文の長さ（sentence-length）である：slope-trick L150（149 字）・cht L157（124 字）。リンクの題名の長さによるもので、§14-25 により残した
  - 消えた警告：monge の資料の 1 行（125 字）、alien-dp の資料の 1 行（143 字）。monge の資料の L171（124 字）は元の 126 字からの残り（数式を含む文）
  - 使い分けの節の文で出た no-doubled-joshi（「だけの」「も」）は、言い回しを直して消した
- **作業用フォルダへのビルド**（`uv run mkdocs build -q -d <作業用フォルダ>/site`）：成功。6 ページの資料の節と使い分けの節の HTML で、リンク・数式が正しく出ることを確かめ、幅 390px のスクリーンショット（monge・alien-dp・dynamic-dp の使い分け、cht・slope-trick・dynamic-dp・monge・alien-dp の資料、inline-dp・slope-trick の使い分け）で見た。cht の資料の節が 1 つの `<ul>` になることも確かめた
- **gen_site.py --check --diff**：変わるのは docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md の版のハッシュだけ（並行して直しているほかの担当の `updated` の分も含む）。節の索引などは変わらない（足した使い分けは定型の節で sections にないため）。メインが作り直す
- fix_problems・check_snippets・check_svg：問題の行・コード片・図を触っていないので流していない

## 提案（メインに頼む共有ファイルの変更）

1. **手引き §4 の overview に足す文の案**：
    > 似た手法との使い分けを書くときは、定型の `## 使い分け {#comparison}` を 2〜4 行で、例題・練習問題（力試し・確認問題があればその後）の後、参考の直前に置く（technique の並びの終わりと同じ）。似た手法のページと、章にハブがあればハブの節（DP の高速化なら dp-speedup-overview#shape-to-tool・#convexity）へリンクする
   - 既存で位置の違う k-shortest-paths・offline-dynamic-connectivity（library の前）・multiplicative-function（resources の前）をそろえるかは #69 で決める
2. **手引き §16-1**：資料の行の書き方は、resources.md の提案 1 の文案に賛成する（この 5 ページも同じ形で直した）。足すとよい点：題名に「です・ます」があると、リンクの文字でも no-mix-dearu-desumasu のエラーになる。その規則だけを名指しした `textlint-disable` で資料のリスト全体を囲む（行だけを囲むとリストが割れる）
3. **（任意。#56 で関連を出すなら）related**：ハブを front matter の related に持たないのは alien-dp・slope-trick・dynamic-dp・inline-dp の 4 ページ（monge・cht・dp-segment-tree は持つ）。#56 で related をページの下に出すなら、4 ページの related に `dp-speedup-overview` を足すとハブへの戻り道が下部にもできる。ハブの related には dynamic-dp がない（早見表と #algebraic-tools では動的 DP へリンクしている）ので、足すとよい
4. **（表記。急がない）ハブを指すリンクの文字**：dp-basics L156・L189、dp-prefix-sum L303、dp-segment-tree L182 は、ハブを「DP の高速化の全体像」と書いている（ハブの題名は「DP の高速化の選び方」。matrix-power L391 は「DP の高速化の一覧」）。題名にそろえるなら #77（表記）でまとめて直すとよい。dp-segment-tree は担当のファイルだが、ほかのページと一緒に直す方がよいので変えていない
5. **（道具。急がない）check_pages**：§17-10 の検査は行の最初のリンクだけを見るので、1 行に 2 つ並べた行の 2 つ目（cht L157 の ageprocpp・slope-trick L150 の hitonanode・dynamic-dp L155 の ikatakos）は検査に入らない。resources.md の提案 2（行の中のすべてのリンクを見る、リンクのない資料の行を警告にする）に賛成する

## 判断してほしい点

1. **使い分けの節の位置**：発展の概要の monge・alien-dp・dynamic-dp では、参考の直前に置いた（理由は上）。§4 の overview の並びに使い分けを入れるかと、その位置を決めてほしい（提案 1）
2. **cht の `#convexity` の追加**：Issue の条件は cht ではもとから満たしていたが、凸性の 4 ページをそろえるために使い分けの既存の 1 行に `#convexity` を足した。要らなければ L210 を戻す
3. **dynamic-dp の資料の行**：元の 1 行（サイトの中のページの組み合わせ ＋ 例題の解説 2 本）を 2 行に分けた。例題の解説の 2 本は「3×3 と 4×4 を比べる」勧めなので 1 行に並べたままにした

## 守れなかった点

- textlint がリンクの文字をどう見るかを試すために、作業ツリーの docs/dp/ に一時ファイル（zz-tl-test-dp-speedup.md）を作り、同じコマンドの中で消した（数秒。git status で消えたことを確かめた）。その後の試験は作業用フォルダで行った。その数秒の間にほかの担当が check_pages などを流していれば、front matter のないページの指摘が出た可能性がある

## 使用量の目安

- 道具の呼び出し 約 85 回。Web の取得：curl で 16 URL の状態と題名、soi.ch の著者、cht の資料 2 本の扱う話題（キーワードの数）の確かめ（どれも付録 B のドメイン）。所要時間 約 70 分
