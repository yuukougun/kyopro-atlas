# 直したもの（comb・patterns・guide・start の直し担当）

audit-*.md の「## comb」「## patterns」「## guide」「## start」の項目を直した。直した項目 94・残した項目 27（うち 17 ページ分は complexity の 1 つの判断）・直さなくてよいと判断した項目 2。残したものと理由は [left-comb.md](left-comb.md)。

検査：check_pages エラー 0・警告 0。変えたページの textlint はエラー 0（全体の npm run lint:text のエラーは ds/partially-persistent-union-find.md の 1 件だけで、分野の外）。check_snippets --changed は期待と違う 0（コード片は変えていない）。ページの id・URL・anchor は変えていない（見出しの文字を変えた how-to-use#stub は anchor を残した）。

## audit-facts（10）

- comb：グラフの成分の「サイクル」を「閉路」に（counting-labeled-graphs L111・L239・L290、counting-mindset L260、counting-dedup L212、inclusion-exclusion-dp L147・L264・L300）。問題の囲みの行（台帳の summary）は残した。
- comb/reflection-principle L196：$|d|$ → `\lvert d \rvert`。
- patterns/permutation の summary：「矢印のサイクル」→「矢印の巡回」。
- guide/cheatsheet L58、guide/debugging-checklist（6 か所）、start/notation L103：「多重テストケース」→「複数テストケース」。
- guide/cheatsheet L330・L331：リンクの文字「popcount・最下位ビット」→ 節の題「popcount・最下位 bit」。L393 は出典の題名なので残した。
- guide/cheatsheet L306：「閉区間 $[L, R]$」と書いた。
- guide/glossary L485：`\lvert A \rvert < \lvert B \rvert`。L713：$(T - 1) \text{ AND } S$。

## audit-figure（41）

360px 表示（倍率 328/幅）で文字が 9px 以上になるように直し、`tools/render_svg.py` で 360px の画像を撮って目で確かめた。直した後に全 69 枚を測り直し、9px 未満の文字と width・height のない SVG は 0。

- 描き直し（幅 400 以下）：counting-basics/line-vs-cycle、expected-value-dp/hp-chain、counting-fix-order/relative-order（3 組を縦に）、probability-basics/two-dice（説明を表の下へ）、probability-dp/flow、probability-symmetry/two-states、rational-mod/two-routes、minimax/deque-tree、divisor-inclusion-exclusion/subtract-multiples（説明を表の下へ）。
- 横に並んだ図を縦に積んだ：permutation-cycles/swap-split、zeta-mobius-subset/cube-axes（4 枚を 1 列に）、zeta-mobius-divisor/exponent-grid（3 枚を 1 列に）、patterns の bracket-sequence/mountain。
- 小さい文字を大きくした（必要なら width・height も付けた）：bell-number/stirling-table（重なった「×1」「×3」と数を動かした）、binomial-coefficient/pascal-and-paths、binomial-precompute/fact-ifact・pascal-mod2、cayley-pruefer/degree-sequence、counting-bijection/monotone・non-injective、counting-dedup/leftmost-embedding、counting-labeled-graphs/component-of-1・bfs-layers、expectation-linear-equations/restart-axb、expectation-tail-sum/area、expectation-of-square/pairs、game-retrograde-analysis/propagation、grundy-number/range-table、inclusion-exclusion/venn-net-count、inclusion-exclusion-dp/first-obstacle、multinomial-coefficient/divide、stars-and-bars/stars-bars、twelvefold-way/table-n4-k3、guide の contest-strategy/finish-times・library-design/workflow・reverse-index-constraints/max-n-per-class、start の atcoder-system/difficulty-by-position・levels。
- width・height だけ付けた：counting-fix-order/bfs-coloring、expectation-of-square/pairs、game-basics/stones-win-lose、lattice-paths/basic・forbidden、nim/winning-move、permutation-parity/two-sequences。
- 図の後の説明を足した：binomial-precompute（各行の 1 の個数が 2 の累乗になることを n = 5・7・8 で確かめる 1 文）、guide/library-design（3 つの使われ方の要点 2 文）。
- guide/reverse-index-constraints の代替テキストを 227 字から 125 字に縮めた（細部は図の後の本文にある）。

## audit-relations（11）

- comb/counting-labeled-graphs L54：「余事象」のリンク先を `../thinking/complement.md` に。
- 写像 12 相の qiita の記事の題名：h1（「「写像12相」を総整理！ 〜 数え上げ問題の学びの宝庫 〜」、2026-10-22 に確かめた）に bell-number・partition-number をそろえた。
- リンクの文字を相手の題名に：binomial-precompute・zeta-mobius-subset（連結なグラフの数え上げ）、continuous-probability（確率・期待値を mod 998244353 で答える）、expectation-of-square（節の題「mod の値では大小比較できない」）、reflection-principle（LGV 補題）、zeta-mobius-divisor（素因数の指数で考える）。dp の 2 か所は left-comb。
- related に足した：game-retrograde-analysis ↔ minimax、zeta-mobius-subset に convolution-ntt、counting-basics に inclusion-exclusion、cayley-pruefer に fps-basics、patterns/mex に lazy-segment-tree-patterns#reformulate、start/how-to-use に contest-strategy#ai-rules、guide/contest-strategy に how-to-use#ai-rule-version。
- guide/contest-strategy#difficulty-by-position：四分位の表を外し、持ち主の atcoder-system#difficulty-by-position へのリンクにした（教材のレベルへの読み替えの箇条と逆転の段落は残した）。
- 生成 AI のルールの重なり：ルールの要約と版の履歴は atcoder-system#ai-rules、教材の約束（ADT・AWC を含む）は how-to-use#ai-rule-version を持ち主にした。contest-strategy は 1 文の要約と 2 つのリンク、コンテスト中・終了後の 2 行だけにし、atcoder-system の「この教材との関係」と how-to-use のルールの要約を短いリンクの文にした。
- guide/debugging-checklist L210：参考の行のリンクの文字を題名に。
- start/notation L172：リンクの文字を節の題「有理数 P/Q を P × Q^(−1) で表す計算」に。

## audit-shared（5）

- comb/stars-and-bars：練習に abc132_d を足し、方針の行と出典（drken の記事。題名は 2026-10-22 に確かめた）を足した。
- comb/probability-dp：練習に abc382_e を足し、方針の行（後半は期待値 DP へのリンク）と出典（ikatakos の記事）を足した。どちらも `fix_problems.py --page` で行を作った。
- start/how-to-use の「『準備中』のページ」の節：今は準備中のページがないことと、帯が出たときの扱いだけの短い節「ページの段階と『準備中』の帯」に替えた（anchor stub は残した）。
- guide/knowledge-map L59・guide/reverse-index-signs L75：「本文がまだないページ（いまはない）」の条件の書き方にした。

## audit-structure（27）

- comb/generating-function-counting：例題の見出しを `## 例題 {#examples}` にして sections から外し、`## ライブラリでの使い方 {#library}` を立てて ACL の囲み・自作の要点・Library Checker を移した。L194 の句点。
- comb/partizan-games：`## 計算量と自作するときの要点 {#library}` を立てて自作の要点・コード片・ACL と Library Checker の文を移した（§16-4 の書き方に合わせ「総当たりの勝敗と照らし合わせて確かめる」を足した）。
- comb/stirling-first：`## ライブラリでの使い方 {#library}` を立てて ACL の囲みと自作の要点を移した。
- comb/burnside-lemma：節の順を library → 落とし穴 → 学ぶための資料 → 例題 → 確認問題 に。
- comb の基礎の technique 5 ページ（binomial-coefficient・binomial-precompute・counting-basics・permutation-cycles・stars-and-bars）に `## 上位の手法へのつながり {#next-steps}` を足した（落とし穴の後）。
- comb/probability-symmetry：要点の「何ができるか」と summary を、何ができるか（1 つを求めて個数を掛ける）が分かる文にした。
- 箇条書きの句点（comb の 9 ページと patterns/divisors-and-multiples）：混在した箇条書きの句点のない行に句点を足した。minimax L224 はコードの前の行を文にした。
- patterns/kth-and-median・operation-sequence：「代表の問題」の列を文字だけにした（operation-sequence の ABC466 D はこのページにしかないので「このページの練習」へのリンクを残した）。
- patterns/kth-and-median の ABC123 D：ページの列に ds/priority-queue#patterns を足した。
- patterns/permutation の ABC350 C：ページの列に「構築問題の考え方」を足した。
- guide/library-design の summary：要点に合わせて「提出用の展開の仕方と、各ページの確認用の問題の表もある」にした。
