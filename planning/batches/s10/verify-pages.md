# 工程10 検証：ページの直し（s10）

対象：audit-*.md（facts・figure・relations・shared・structure）の一覧に従った直し（`git diff docs/ snippets/`、記録は fixed-*.md・left-*.md）。commit はしていない。

**結論：重大な誤りは残っていない。** 見つけた誤り 2 件は直した（下の「直したもの」）。メインの判断が要るものを「メインへ」に書いた。

## 検査の結果（直した後）

- `python3 tools/check_pages.py`：エラー 0・警告 0
- `npm run lint:text`：エラー 0（警告 4449。直した 2 ページも textlint のエラー 0）
- `uv run mkdocs build --strict`：通った（WARNING 0）
- `python3 tools/check_snippets.py --changed`：コード片 1（zero-one-bfs/turns.cpp の `dx`・`dy` → `di`・`dj`）、期待と違う 0
- `node --test "tests/viz/*.test.mjs"`：171 件すべて通った
- `python3 tools/fix_problems.py --check`：直すべき行 0。台帳にあって本文にない警告 6（inclusion-exclusion の abc475_f、spanning-tree-advanced の keyence2019_e など。left-*.md に記録済みの判断待ち）

## 直したもの（2 件）

1. **docs/graph/spanning-tree-advanced.md L163**：節の並べ替え（library・resources・practice の移動）で `## 参考 {#references}` の見出しの文字が消え、行が ` {#references}` だけになっていた（参考の一覧が練習問題の節の下に入り、見出しがなくなる）。`## 参考 {#references}` に戻した
2. **docs/graph/time-dependent-dijkstra.md L212**：audit-facts の `\mathrm{lcm}` → `\operatorname{lcm}`。math の担当は担当外として left-math.md に残し、graph の担当も直していなかった。直した

## id・URL・anchor

- front matter の id はどのページも変わっていない。ファイルの削除・改名は図の 8 枚だけ（下の「図」）
- 見出しの `{#…}` と sections の anchor を HEAD と比べた（スクリプト。増えたもの・減ったもの）。増えたのは定型の節（next-steps 31 ページ・library・resources・practice・challenge・motivation）だけ
- 減ったもの（どれも意図どおりで、外からのリンクはない。check_pages の anchor の検査も 0）：
    - geometry/manhattan-chebyshev の `#acl`：見出しを消し、囲みを最遠点対の節へ移した（audit-structure の指示）。ページ内のリンク 2 か所は `#farthest-pair` に張り替え済み
    - math/miller-rabin の `#examples`：0 問の例題の節を消し、§16-5 の 1 文を練習問題へ（指示どおり）
    - comb/generating-function-counting：sections から定型の `examples` を外した（見出し `## 例題 {#examples}` は残る）
    - graph/matrix-tree-theorem：sections から定型の `resources` を外した（見出しは残る）
    - graph/spanning-tree-advanced の `#references`：上の 1 で戻した
- anchor を変える指示（cht・dynamic-dp・monge の `verify`→`library`、wavelet-matrix・auxiliary-tree の `usage`、linear-recurrence-fast の `implementation`、two-sat の `acl`、roadmap の `practice`）はどれも変えずに left に残してある

## 一覧の項目が直っているか

- **audit-facts**：「歩道」「上位ビット」「最下位ビット」「多重テストケース」「フェニック木」「平衡二分木」「1024 MB」「slope trick」「ワーシャルフロイド（法なし）」「4-サイクル」「\mathrm{lcm}」「トポロジカル順序」を全ページで grep した。本文に残るのは、front matter（summary・aliases。提案として left にある）、生成物（index・lists・problem-sets・roadmap の生成ブロック）、台帳から作る問題の行（warshall-floyd L272・extended-dijkstra L354・L374 の「歩道」。left-graph・left-dp に台帳の直しとして記録済み）だけ。数値の直しを計算し直した：complexity-estimation の $3^{16} \approx 4.3 \times 10^7$、trie の約 50 MiB（$1.3 \times 10^7 \times 4$ バイト）・約 118 MiB、`1 << 31` の C++14・C++17 の扱い（[expr.shift] の符号なしへの写しと処理系定義の変換。style-guide §5 どおり）。どれも正しい
- **audit-figure**：一覧の 253 枚を audit と同じ計算（svg_audit.py）で測り直した。245 枚は 9px 未満の文字 0・width と height あり。残りの 8 枚は 2 枚ずつに分けられていて（exponent-mod・gaussian-elimination・integer-division・mod-arithmetic・mod-inverse・multiplicative-order・priority-queue・sigma-manipulation）、分けた 16 枚も 9px 未満 0。古いファイルを参照するページはない
- **audit-relations**：exchange-argument の落とし穴、imos#adjacent-difference の 1 文、parity のリンク先、dp-dag・subset-enumeration-dp の節のレベル、spf-sieve の linear-sieve の前提、リンクの文字の張り替えを読んだ。どれも指示どおりで、意味の変わったものはない。φ・μ の素数冪の値も正しい
- **audit-structure**：next-steps の 31 ページ、library・resources の節の新設（dilworth-path-cover・flow-lower-bounds・k-shortest-paths・offline-dynamic-connectivity・spanning-tree-advanced・tree-isomorphism・suffix-automaton・parallel-binary-search・partially-persistent-union-find・rollback-union-find・segment-tree-beats・fft-ntt・fps-basics・multiplicative-function・online-convolution・generating-function-counting・partizan-games・stirling-first・advanced-geometry）を見出しの増減で確かめ、spanning-tree-advanced・manhattan-chebyshev・miller-rabin は本文を読んだ（上の 1 を見つけた）
- **audit-shared（問題の補充）**：本文に足された問題 35 問（abc131_f〜zone2021_f、typical90 3 問）を `tools/ap.py show` で照らし、題名と diff がすべて台帳・AtCoder Problems と一致した。方針の文（+ の行 60 余り）を読み、知っている解き方と照らした。誤りは見つからなかった（例：ABC147 E の差の上限 $159 \times 80 = 12720$、ABC237 D の後ろからの deque、ABC413 G の 2 組の外周、ABC304 F の $-\sum_{d \mid N, d < N} \mu(N/d) F(d)$、ABC266 B の負の余り、ARC046 B の場合分け）

## 図を目で確かめたもの

`python3 tools/render_svg.py --width 360` で 74 枚を撮って見た：[A] の 50 枚すべて、分けた 16 枚、それ以外から無作為の 8 枚。文字の重なり・切れはなく、値と図の内容も計算し直して合っていた（例：push-pull の dp、区間 DP の表の 22、二分探索の count、残余グラフのカット 5 と流量保存、deque のゲーム木 f = 7、prod の 4 ノード、区間篩の素数、reroot の f(3) = 10、Bellman-Ford の各回の dist など）。

加えて、直した図と新しい図 304 枚をヘッドレスの Chrome で開き、文字の枠どうしの重なりと viewBox からのはみ出しを HEAD の図と比べた。新しく出たのは 9 枚で、撮って見るとどれも読める。はみ出しは 1〜9px で、どれも行の末尾の全角のかっこか下の余白にかかるだけ：digit-and-mod/suffix-pairs の「（空）」（右へ 9px）、rolling-hash/prefix-hash の注記（5px）、gaussian-elimination/steps-1・steps-2 の凡例（3px）、ほかは 3px 以下。フォントが違う環境では端の字が少し欠けるおそれがあるので、次に図を触るときに 10px ほど余白を足すとよい（直してはいない）。

## メインへ（判断・追従が要るもの）

1. **complexity を null にするかがページによって違う**：audit-structure の指示どおり dp-speedup-overview・advanced-ds-catalog・graph-modeling の 3 ページは null にされた。comb・patterns・guide の担当は、audit-facts の「メインが決める（全 17 ページをそろえる）」に従って 14 ページを残した（left-comb.md）。どちらに決めても 17 ページをそろえる
2. **front matter の summary を担当が直した 3 ページ**：comb/probability-symmetry（要点の 1 文目に合わせた）、guide/library-design（要点との食い違い）、patterns/permutation（「サイクル」→「巡回」）。audit で直し方が示されていた項目で、どれも内容は正しい。ただし summary は「提案」にする決まりなので、メインが確かめる。related も 23 ページで足されている（audit-relations の【関連】。check_pages は 0）
3. **一覧になかったが残る表記**：patterns/xor の節の題と sections の title「…→ 上位ビットから決める・Binary Trie」（L27・L130）と、L135 のリンクの文字「上位ビットで 2 つに分けて再帰する」（リンク先の節の題は「上位 bit…」に直った）。付録 A にそろえるなら「上位 bit」に。degree-sqrt の summary と graph/index の生成の行は「4-サイクル」のまま（left-graph に提案あり）
4. gen_site.py での作り直しが要る（problem-sets・roadmap の生成ブロックに古い節の題が残る。left-comb・fixed-shared に記録）
