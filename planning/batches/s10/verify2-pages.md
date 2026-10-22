# 工程10 2巡目 検証：ページの直し（verify2-pages）

対象：2巡目の直し（`git diff HEAD -- docs snippets`、記録は fixed2-*.md）。decisions.md と手引き §17 を基準にした。atcoder.jp・codeforces.com は開いていない。gen_site.py は `--check` だけ実行した。commit はしていない。

**結論：重大な誤りは残っていない。** 検証で見つけた誤り 4 件はこの検証で直した（下の「検証で直したもの」）。

## 検査（検証で直した後）

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py` | エラー 0・警告 0 |
| `npm run lint:text` | エラー 0（警告 4467） |
| `uv run mkdocs build --strict -d …/s10b/site`（-q なし） | 成功。WARNING・ERROR なし（出たのは Material チームのお知らせだけ） |
| `python3 tools/check_snippets.py --changed` | コード片 11・期待と違う 0 |
| `node --test tests/viz/*.test.mjs` | pass 171・fail 0 |
| `python3 tools/check_svg.py` | 図 414・エラー 0（警告 120 は幅の目安で前と同じ） |
| `python3 tools/frequency.py --check` | 差分 0 ページ |
| `python3 tools/fix_problems.py --check` | 直すべき行 0・台帳にあって本文にない 0 |
| `python3 tools/gen_site.py --check` | 生成物が古い 45 ファイル（gen_site.py の作り直しはメインが行う） |

## decisions.md・§17 の各件

| 件 | 確かめ方 | 結果 |
| --- | --- | --- |
| §17-1 complexity | `type: guide/hub/pattern` の 33 ページの complexity を grep | すべて null |
| §17-3 anchor | git diff HEAD で、ページごとに見出しの `{#…}` と sections の anchor の増減を数えた | 変わったのは cht・dynamic-dp・monge（verify→library）、wavelet-matrix・auxiliary-tree（usage→library）、linear-recurrence-fast（implementation→library）だけ。ほかに増えたのは定型の節（slope-trick `challenge`、complement-graph-bfs・floor-sum・steiner-subtree `practice`）。消えた anchor はほかにない。two-sat の acl・roadmap の practice・string-basics の cost-pitfalls は今のまま |
| 古い anchor へのリンク | docs・data・overrides・tools を grep | 本文には 0。残るのは生成物の docs/index/{dp,ds,tree,math}.md の 6 行だけ（gen_site で消える） |
| id・URL | git status・diff の `id:`・`title:` | 消えたページ・増えたページ・id の変更なし |
| §17-8 表記 | 多重テストケース・歩道・上位／最上位／最下位ビット・平衡二分木・フェニック木・0/1 始まりを grep（生成物・aliases・別名の行・glossary・term-index を除く） | 本文・summary・signs に残りなし。コード片のコメント 5 か所と台帳の approach 4 か所が残っていたので直した（下） |
| 「ダイクストラ」→「ダイクストラ法」 | grep | 本文の残りは生成ブロック（problem-sets L100・roadmap L717）と別名の「拡張ダイクストラ」だけ |
| §17-11 重なり | rollback-union-find・root-path-dfs・offline-dynamic-connectivity の diff を読んだ | 縮め方は判断どおり。ただし縮めたことでリンク切れの言い回しが 2 か所残っていた（下） |
| §17-12 | 台帳の abc116_c・abc130_e | pages から外れている |
| front matter の提案 | 11 ページの summary・signs と 7 ページの related を読んだ | すべて入っている。summary の事実（euler-path の O(N + M)、steiner-tree の O(3^K N + 2^K (N + M) log N)、degree-sqrt の「重い頂点は 2√M 個以下」、k-shortest-paths のウォークと Eppstein）は正しい |
| agc002_d・abc180_f | 台帳と本文の行を grep | 3 ページの agc002_d はそろっている。abc180_f は 3 ページとも「自己ループのない（多重辺は許す）…閉路」。counting-mindset の方針（閉路は k = 1 で 0 通り、k = 2 で 1 通り）は問いと合う |
| abc467_f・abc475_f・abc458_g・keyence2019_e | 方針の式を自分で確かめた | abc467_f の隣接交換（B の大きい方を先に書くと、遅い方の時刻が S + A_i + A_j + B_j 以下になる）とセグメント木の合成は正しい。abc475_f の T0 − T1 + T2 − T3 + T4 + 1 は包除の形として正しい。abc458_g の遷移（−B_i(m − j) で傾きが B_i 増える、傾き −C_i との (max, +) 畳み込みで右側の急な傾きがそろう）は上に凸の性質と合う |
| floor-sum の練習 | Min of Mod of Linear の判定式 | ⌊y/M⌋ − ⌊(y − X)/M⌋ が [y mod M < X] になる（0 < X ≤ M）ので、個数 f(N,M,A,B) − f(N,M,A,B−X) は正しい |
| knapsack-undo のメモリ | 計算した | 16 × 6.4×10^7 = 1.024×10^9 バイト ≈ 977 MiB で、本文の「約 980 MiB」と合う |
| static-top-tree L71 | 読んだ | 「重軽再帰 DP」を #heavy-path-dp へのリンクにする判断は、L71 がその節の中なので張られていない（fixed2-graph の残り 2）。aliases からは外れている。自分の節へのリンクになるので今のままでよいと考える（メインの判断） |
| base-conversion | 読んだ | 「1 始まりの 26 進」→「0 を使わない 26 進」は、各桁が 1〜26 の記数法の説明として正しい。anchor `bijective-26` は同じ |

## frequency（§17-7）

tools/frequency.py を読んだ。古い ABC は「contest が abcNNN（451〜480 を除く）・status が未確認でない・pages の role が example/practice/challenge」の問題の数で、§17-7 のとおり。手で 4 ページを数え直した（台帳 data/problems.yaml から）：

- comb/bell-number：abc217_g・abc310_d・abc390_d の 3 問（dp_u・typical90_as は ABC でない）→ B、evidence「古い ABC 3 問」と一致。recent-abc.yaml に出てこない（recent 0）
- dp/knapsack-undo：abc321_f・abc441_f の 2 問（arc070_b は除く）→ C、一致
- graph/degree-sqrt：abc219_g・abc260_f・abc350_g の 3 問 → B、一致
- basics/interval-scheduling：abc103_d・abc230_d の 2 問 → C、一致（手の B を外したのは §17-7 どおり。B に戻すかはメインの判断として fixed2-frequency に書かれている）

event-sort の recent 2（abc467_e・abc478_d）も recent-abc.yaml の 2 行と合う。

## 出典の題名（§17-10）

- 2巡目で足した・直した参考の行（159 行）から 11 行を抜き、記事の `<title>` を取得して比べた（kmjp ABC394 G・ABC445 G、drken ABC141 E・ABC150 F・ARC033 C・ABC181 F・ABC193 C、kyo-pro ABC245F、maspy slope trick (1)、merom686 ABC312、oraclesqlpuzzle ABC189-E）。11 行ともリンクの題名と記事の題名が一致した（ブログ名の部分を除く）
- 参考・学ぶための資料の節の、行の 2 つ目以降のリンクも含めて URL ごとに題名を集めた。違うのは 6 URL で、どれも「X 氏の記事[「題名」]」と「[X「題名」]」のように著者をリンクの外に書く形の違いだけ（fixed2-citations の「そろえなくてよいもの」と同じ）

## 図（§17-6）

- 2巡目で変わった SVG 116 枚を含む全 414 枚で、文字の枠と viewBox の端の距離をヘッドレスの Chrome で測った（一時置き場の edge.py）。はみ出しは 0 枚。verify-pages の 9 枚はすべて 10px 以上になった
- 12 枚を `render_svg.py --width 360` で撮って目で見た（atcoder-system/levels・cht/envelope・contest-strategy/finish-times・digit-and-mod/suffix-pairs・divisors-and-multiples/multiple-hops・dp-basics/push-pull・gaussian-elimination/steps-1・grid/checkerboard・hash-safety/birthday・rolling-hash/prefix-hash・stack-techniques/bracket-stack・wavelet-matrix/levels）。切れ・重なりはない

## 検証で直したもの

1. **docs/img/meet-in-the-middle/combine.svg**：2巡目で上に 2px 足した図だが、右上の「（昇順にソート済み）」が viewBox の右端に 0px で接していた（360px で撮ると右端が欠けて見える）。x を 270→260 にして右端から 10px にした。測り直して 10px、撮って見て読める
2. **背景の白い rect が平行移動の `<g>` の中にある図 40 枚**（basics・dp などの担当が余白を足した図。上の combine.svg を含む）：`<rect width="100%" height="100%">` が `<g transform="translate(x y)">` の中にあるので、背景が x・y だけずれ、上端・左端に 1〜5px の透明な帯ができていた（暗い背景で表示すると線に見える）。rect を `<g>` の前へ移した（`<defs>` だけが先にある図に限った。描く順は変わらない）。check_svg はエラー 0 のまま
3. **docs/ds/rollback-union-find.md L61・L79・L81**：§17-11 で #offline-dynamic-connectivity を縮めたため、「引き算で戻す値は[オフライン動的連結性](#offline-dynamic-connectivity)の末尾で扱う」（L61・L81）が中身のない所を指していた。L61 は「根の合計を引き算で戻す場合は、同じグループどうしの記録を取り消すときに引かない（引くと根の合計が 0 になる）」を本文に残し（縮める前の節にあった注意で、offline-dynamic-connectivity には「取り消しの回数」の形でしか書かれていない）、リンクを graph/offline-dynamic-connectivity#dfs-rollback へ向けた。L81 のリンクも同じ先へ。L79 の「同じ説明は root-path-dfs にもある」は root-path-dfs が縮んだので「要点は…にもある」に（fixed2-graph の「ds の担当へ」の勧め）。textlint の文の長さの警告が出ないよう文を分けた
4. **§17-8 の表記の残り**：
    - コード片のコメント（本文に `--8<--` で入る）：snippets/union-find-applications/top-k.cpp・tree-traversal/dfs-order.cpp・insertion-dp/relative-rank.cpp・kth-element/reverse-insert.cpp・wavelet-matrix/wm.cpp の「0 始まり」「1 始まり」→ 0-indexed・1-indexed。check_snippets --changed で期待と違う 0
    - 台帳 data/problems.yaml の approach 4 か所：L1870「最上位ビット」→「最上位 bit」、L3237「1 始まりの 26 進」→「0 を使わない 26 進」（fixed2-math の頼み）、L8605・L8610「上位ビット」→「上位 bit」。fix_problems --check は 0

## 残っているもの（重大ではない。メインの判断か次の巡）

- 生成物（docs/index・lists・各分野の index.md・llms.txt・roadmap・problem-sets・reverse-index-signs・term-index の生成ブロック）の古い anchor・古い語・summary の写し：gen_site.py の作り直しで直る（`--check` で 45 ファイル）
- 文字の枠が端から 10px 未満の図が 154 枚ある（最小 3px、はみ出しは 0）。枠はフォントの上下の余白を含む。decisions が直すと決めたのは verify-pages の 9 枚で、それは済んでいる。§17-6 を全部の図に厳密に当てるかはメインの判断（一覧は一時置き場 s10b/v/edge_all.tsv）
- trap.jp の 4 か所（cpp-environment・cpp-macros-template-file 2・static-top-tree）：記事を取得できず noai を確かめられていない。メインの判断待ち（fixed2-shared 6）
- static-top-tree L71 のリンク（上の表）
- math/xor-basis L182・L287 のリンクの文字「拡張ダイクストラ」（別名）：相手の題名「状態を頂点にする」にそろえてもよい（左の勧めの外なので触っていない）
- 台帳の abc458_e・abc479_d・abc479_e は未確認のまま pages から外れている（fixed2-shared 9）
