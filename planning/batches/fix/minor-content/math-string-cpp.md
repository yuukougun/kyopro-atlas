# math-string-cpp の報告（バッチ minor-content）

- 担当の Issue：#34・#35・#36・#37・#38・#39・#40・#41（8 件とも完了）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content）。git は読むだけで、commit などはしていない。Issue にはコメント・編集・クローズをしていない
- 直したファイル（12）：docs/comb/mobius-function.md、docs/comb/binomial-coefficient.md、docs/patterns/bracket-sequence.md、docs/patterns/grid.md、docs/patterns/mex.md、docs/patterns/subsequence-and-substring.md、docs/patterns/xor.md、docs/string/string-basics.md、docs/geometry/geometry-precision.md、docs/cpp/cpp-reverse-index.md、docs/cpp/cpp-io.md、docs/cpp/cpp-undefined-behavior.md
- front matter：12 ページとも `updated` を 2026-10-29 にした。stage とほかの項目は変えていない
- 生成物・共有のファイル（用語集・prh.yml・台帳・手引きなど）・コード片・図は変えていない

## #34 メビウス関数の篩の節の O(M) を O(V) に（完了）

- **場所**：docs/comb/mobius-function.md 165 行目（#sieve の「線形篩で作る」）
- **直した内容**：`$O(M)$ だが` → `$O(V)$ だが`
- **確かめたこと**：直前の 163 行目が「$V$ は表を作る値の上限」と定めていること、要点（39 行目）と front matter の complexity が「線形篩なら O(V)」であることと合う。ページの中に `O(M)` はもう残っていない（$M$ は #gcd-one などの $1 \le j \le M$ の意味だけ）

## #35 「ヴァンデルモンドの等式」を「Vandermonde の恒等式」に（完了）

- **場所**：docs/comb/binomial-coefficient.md 170 行目（#comparison の表の後）
- **直した内容**：「（ヴァンデルモンドの等式・hockey stick など）」→「（[Vandermonde の恒等式](../comb/binomial-identities.md#vandermonde)・hockey stick など）」。後ろのページへのリンク「[二項係数の恒等式](../comb/binomial-identities.md)」は残した
- **書き方の判断**：文は複数の公式（hockey stick も）を挙げてページを案内しているので、ページへのリンクを #vandermonde に変えるのではなく、「Vandermonde の恒等式」の語に節へのリンクを付けた。159 行目（#next-steps）は別の節なので、§14-23 のとおりリンクを重ねてよい
- **確かめたこと**：binomial-identities の節の題が「Vandermonde の恒等式（2 グループから合計 k 個）」・anchor が `vandermonde` であること。サイトの中の「ヴァンデルモンド」はこの行と lagrange-interpolation 144 行目の「ヴァンデルモンドの行列式」（別の概念）だけだった
- **提案**：下の「提案」1（prh）

## #36 括弧列の図の説明を「上・下」に（完了）

- **場所**：docs/patterns/bracket-sequence.md 64 行目（図の代替テキスト）・66 行目（本文）
- **直した内容**：「左の (()()) は…右の ())(() は…」→「上の (()()) は…下の ())(() は…」、「この図で、右の列は」→「この図で、下の列は」
- **確かめたこと**：mountain.svg は 2 つ目の組が `translate(-350,250)` で下に積まれている。`tools/render_svg.py bracket-sequence` で PNG にし、上が (()())（正しい）、下が ())(()（3 文字目で −1）であることを目で見た。SVG は変えていない。ページの中にほかの「左の・右の」の言い方は残っていない

## #37 題材別の表のページ名を行き先の題名に（完了）

- **場所と直した内容**（どれも表の「ページ」の列）
  - docs/patterns/grid.md 91 行目：「マンハッタン距離とチェビシェフ距離」→「マンハッタン距離と 45 度回転」。92 行目：「回転と座標変換」→「回転・平行移動・アフィン変換」
  - docs/patterns/mex.md 82 行目：「変数を固定する」→「一部を固定して数える」。84 行目：「遅延セグメント木の使い方の型」→「遅延セグメント木の載せ方の型」。表の後の 88 行目の「[遅延セグメント木の使い方の型の力試し]」も同じ古い名前だったので「[遅延セグメント木の載せ方の型の力試し]」にした（Issue には挙がっていないが同じずれ）
  - docs/patterns/subsequence-and-substring.md 82・85 行目：「段階を状態にした DP」→「フェーズを状態に持つ DP」。83 行目：「余りを状態にした DP」→「余り・個数を状態に持つ DP」。87 行目：「ページ」の列に「、[KMP 法](../string/kmp.md#matching)」を足した
  - docs/patterns/xor.md 101 行目：「アダマール変換」→「XOR 畳み込み」（「使う手法」の列の「アダマール変換（線形）」は手法名なので残した）
- **確かめたこと**：4 ページの表のリンクの文字と行き先の front matter の title を、作業用フォルダのスクリプト（linktitles.py）で全部突き合わせた。行き先の題名・anchor（`#matched-prefix`・`#counting-phases`・`#grid-rotation`・`#reformulate`・`#transform`・`kmp#matching`）が実在する。作業用フォルダへのビルドで、直した行のリンク先が正しいことも見た
- **残したもの**（略した名前か、題名をそのまま含む名前と判断）：grid の「マンハッタン距離」「偶奇」「全探索」、mex の「主客転倒」「Grundy 数」「構築」、subsequence-and-substring の「最長共通部分列」「Suffix Array」「回文の扱い」、xor の「BIT」「木の距離」（題名は「木の上の距離」）「Nim」「Grundy 数」「集合のハッシュ」「KMP 法」。subsequence-and-substring 84 行目の「数え上げの重複の除き方」（題名は「重複の除き方」）は、題名より長いが題名をそのまま含み迷わないので残した（下の「判断してほしい点」2）
- **参考**：ほかの pattern のページ（divisors-and-multiples・interval・permutation など）の表も同じスクリプトで見たが、略した名前か節の題を使ったリンクだけで、この Issue と同じ種類のずれはなかった（担当外なので直していない）

## #38 ABC110 C の要約を「入れ替え」に（完了）

- **場所**：docs/string/string-basics.md 235 行目（#practice）
- **直した内容**：要約を台帳の summary と同じ「2 種類の文字を選んで一斉に入れ替える操作を繰り返して、S を T にできるかを判定する。」にした（手で直した。fix_problems.py は使っていない）
- **確かめたこと**：`python3 tools/ap.py show abc110_c` で「C. String Transformation・diff 949」を確かめた。data/problems.yaml の summary と一字一句同じ。同じページの #character-mapping（93〜112 行目）と練習の方針（243 行目）の「入れ替え」と合う。`fix_problems.py --check --page string-basics` は直すべき行 0

## #39 誤差のページから FMA の注意へリンク（完了）

- **場所**：docs/geometry/geometry-precision.md 184 行目（#eps の最後に段落を 1 つ足した）
- **直した内容**：「**手元と提出で結果が変わる**。AtCoder は `-march=native` でコンパイルするので、小数の外積の符号や `== 0` の判定が手元と変わりうる（[FMA](../cpp/cpp-environment.md#march-native)）。整数で計算できるなら外積を整数のまま求め（[外積・内積・距離の 2 乗で比べる](#integer-comparison)）、実数が避けられないなら `== 0` ではなく上の EPS で比べる。」
- **書き方の判断**：1 文目は Issue の文のとおり。2 文目の対処は cpp-environment#march-native の「影響」（整数の座標なら整数のまま外積を求める）と「そろえ方」（AtCoder のオプションは変えられないので誤差に強い書き方で対処する）に合わせた。困った読者が見つけやすいよう、太字の書き出しの段落にした
- **確かめたこと**：AtCoder のオプションに `-march=native` があることは cpp-environment#options の表と一致する

## #40 C++ の逆引きに症状と書き方の行を足す（完了）

- **docs/cpp/cpp-reverse-index.md**
  - #lookup-types（89・90 行目、`1LL * a * b` の行の後）：`` `1 << 40`・`1 << k` ``（int の 1 を 32 以上ずらすと未定義動作。`1LL << k` と書く → [シフトの幅](../cpp/cpp-integer-overflow.md#shift-width)）、`` `__builtin_mul_overflow(a, b, &r)` ``（積があふれるかを判定する。GCC の拡張 → [積のあふれの判定](../cpp/cpp-integer-overflow.md#overflow-check)）
  - #lookup-types（98 行目、gcd の行の後）：`` `midpoint(a, b)`・`clamp(x, lo, hi)` ``（あふれない中点（C++20）・範囲に収めた値（C++17）→ [midpoint・clamp](../cpp/cpp-math-functions.md#midpoint-clamp)）。節が clamp も扱うので書き方に clamp も入れた
  - #lookup-types（101 行目、pow・sqrt の行の後）：`` `numbers::pi`・`M_PI`・`acos(-1)` ``（円周率。double ではどれも同じ値、`numbers::pi` は C++20 → [円周率](../cpp/cpp-math-functions.md#pi)）
  - #lookup-macros（170 行目、`#ifdef LOCAL` の行の後）：`` `#ifdef ATCODER`・`#ifndef ONLINE_JUDGE` ``（ジャッジでだけ定義されるマクロで、提出と手元を分ける → [ジャッジのマクロ](../cpp/cpp-environment.md#judge-macros)）
  - #symptoms（316・317 行目、ACL の版の行の後）：「小数の結果が手元と違う（外積の符号・`== 0` の判定）」→ `-march=native` で FMA が使われ、丸めが変わる → [FMA](../cpp/cpp-environment.md#march-native)。「手元では速いのに AtCoder でだけ TLE」→ 関数の中の大きな配列（AtCoder では呼ぶたびに 0 で埋まる）→ [大きな局所配列は遅くなる](../cpp/cpp-environment.md#auto-var-init)。並びは cpp-environment#when-results-differ の「ほかに、次の差もある」と同じにした
  - 行の並びは行き先のページの節の順（cpp-integer-overflow は int-product → shift-width → … → overflow-check、cpp-math-functions は gcd-lcm → midpoint-clamp → integer-division → pow-sqrt → pi）に合わせた
- **docs/cpp/cpp-io.md** 272 行目（#tle-causes の表の最後）：「関数の中の大きな配列（`int buf[100000];` の先頭だけ使う）｜$2 \times 10^5$ 回呼んで 0.05 秒が、AtCoder と同じ 0 埋めのオプションで 1.03 秒に｜グローバルに置くか、外で 1 回だけ確保する（[0 で埋める処理](../cpp/cpp-environment.md#auto-var-init)）」。表の前置きは「手元の g++-15（-O2）で測った例」なので、この行だけはオプションを付けたときの値だと計測の列に書いた
- **確かめたこと**
  - 行き先の anchor 7 つ（`pi`・`midpoint-clamp`・`shift-width`・`overflow-check`・`judge-macros`・`auto-var-init`・`march-native`）が、見出しの `{#…}` と front matter の sections の両方にあることを grep で確かめた。check_pages（本文のリンクと anchor を見る）と `mkdocs build --strict`（anchors: warn）も通った
  - 各行の「意味」は行き先の節の本文と照らした（例：`1 << 40` は「型の幅以上のシフトで未定義動作、`1LL << 40` と書く」、円周率は「どの書き方でも double の範囲で同じ値」、`__builtin_mul_overflow` は「GCC の拡張」）
  - cpp-io の数字は持ち主の cpp-environment#auto-var-init の値（0.05 秒・1.03 秒、snippets/cpp-environment/auto-var-init-cost.cpp）をそのまま使った。手元で計り直すと（q = 2×10^5、k = 1、3 回ずつ）オプションなしの `-O2` が 0.048〜0.056 秒、`-ftrivial-auto-var-init=zero` 付きが g++-15 で 1.06〜1.09 秒・g++-13 で 1.05〜1.06 秒で、同じ程度だった

## #41 cph と、提出用のコピーの目印に説明を添える（完了）

- **docs/cpp/cpp-undefined-behavior.md**
  - 101 行目（#out-of-range の「版」）：「`-O2`（AtCoder・cph）では止まらない」→「AtCoder や手元の [cph](../cpp/cpp-macros-template-file.md#bundling-tools)（VS Code の拡張 Competitive Programming Helper）でふだん使う `-O2` では止まらない」
  - 276 行目（#debug-build）：「ふだんのビルド（cph で AtCoder と同じ `-O2`）とは別に、…」→「ふだんは [cph](../cpp/cpp-macros-template-file.md#bundling-tools)（VS Code の拡張 Competitive Programming Helper）を使い、AtCoder と同じ `-O2` でビルドして試す。それとは別に、…」
  - 参考（333 行目）：「[agrawal-d「Competitive Programming Helper (cph)」](https://github.com/agrawal-d/cph)：cph が VS Code の拡張であること」を足した
  - 274 行目の見出し「不具合を探すビルドを cph とは別に用意する」は変えていない（見出しにはリンクを置かない。§7）
- **初出の判断**：Issue は 274・276 行目を挙げているが、本文で cph が最初に出るのは 101 行目だった。101 行目に説明とリンクを置いて「初出」を満たし、276 行目は別の節（#debug-build）で、節だけを読んでも通じるように（§1・§14-23）同じ説明とリンクを置いた（下の「判断してほしい点」1）
- **docs/cpp/cpp-reverse-index.md** 173 行目（#lookup-macros の `// @impl` の行）：意味を「この教材の作者が改造した cph（VS Code の拡張）で、main の後ろに回す部分を分ける印。公式の cph にはない」にし、ページの列に [cph の改造版](../cpp/cpp-macros-template-file.md#bundling-tools) を足した（逆引きでは cph がここで初めて出るため。「作者」だけだと解説コードの作者と読めるので「この教材の作者」にした）
- **確かめたこと**：cph が VS Code の拡張「Competitive Programming Helper (cph)」であることを、リポジトリの README（https://raw.githubusercontent.com/agrawal-d/cph/main/README.md。付録 B にあるドメイン）で確かめた（「Quickly compile, run and judge competitive programming problems in VS Code」、VS Code の Marketplace から入れる）。「公式の cph にはない」「提出用にコピー」「main の後ろに回す」は cpp-macros-template-file 252〜268 行目（#bundling-tools・#impl-marker）と合う
- **提案**：下の「提案」2（持ち主の #bundling-tools にも「VS Code の拡張」を）

## 検査の結果

- `python3 tools/check_pages.py --page <id> -v`：12 ページともエラー 0・警告 0（直す前も 0・0）
- `python3 tools/fix_problems.py --check --page string-basics`：直すべき行 0・直せない行 0・警告 0
- `npx textlint`（12 ファイル）：エラー 0・警告 105（直す前も 105）。直す前後の警告を突き合わせると、違いは geometry-precision の 2 件と cpp-io の 1 件の sentence-length の行番号がずれただけで、新しい警告はない。残っている 105 件は直す前からのもの（数式を含む文の長さ・読点の数・同じ助詞など）
- 作業用フォルダへのビルド `.venv/bin/mkdocs build --strict -q -d <作業用フォルダ>/site`：成功（Material の告知だけ）。直した行の HTML を取り出し、表が崩れずリンク先が正しいことを見た
- `python3 tools/gen_site.py --check`：生成物が古い（14 ファイル）。ほかの担当の変更を含む。生成物に写る文は変えていない（直した文を docs/index・docs/lists・llms.txt・graph.json・nav.yml で探して 0 件）が、版のハッシュは front matter（updated を含む）から作られるので、メインが gen_site.py を流せば足りる
- コード片・図は変えていないので check_snippets・check_svg は流していない（図は render_svg で見ただけ）

## 提案（メインに頼む共有のファイルの変更）

1. **prh.yml**：「ヴァンデルモンドの等式」「ヴァンデルモンドの恒等式」を「Vandermonde の恒等式」に寄せる規則（例：`expected: Vandermonde の恒等式`、`pattern: /ヴァンデルモンドの(?:等式|恒等式)/`）。lagrange-interpolation 144 行目の「ヴァンデルモンドの行列式」は別の概念なので当たらないようにする
2. **docs/cpp/cpp-macros-template-file.md**（担当外。cph の説明の持ち主）：262 行目の「公式の cph（Competitive Programming Helper）」を「公式の cph（VS Code の拡張 Competitive Programming Helper）」にし、参考に「[agrawal-d「Competitive Programming Helper (cph)」](https://github.com/agrawal-d/cph)：cph が VS Code の拡張であること」を足す。いまは cpp-undefined-behavior と逆引きが「VS Code の拡張」と書き、リンク先の #bundling-tools には書いていない

## 判断してほしい点

1. **#41 の説明の置き場所**：cph の本文の初出は 101 行目（#out-of-range）で、Issue の挙げた 276 行目（#debug-build）ではなかった。両方に「（VS Code の拡張 Competitive Programming Helper）」とリンクを置いた。重く感じるなら、276 行目を「ふだんは VS Code の拡張 [cph](…) を使い、…」に縮める
2. **#37 の残したリンク**：subsequence-and-substring 84 行目の「[数え上げの重複の除き方]」（題名は「重複の除き方」）と xor 92 行目の「[木の距離]」（題名は「木の上の距離」）は、Issue に挙がっておらず、題名を含む・略しただけと判断して残した。そろえるなら「重複の除き方」「木の上の距離」にする

## 使った出典と Web 取得

- https://raw.githubusercontent.com/agrawal-d/cph/main/README.md（1 回。cph が VS Code の拡張であること）。付録 B にあるドメインで、新しく noai を確かめたドメインはない。atcoder.jp・codeforces.com は開いていない

## 使用量の目安

- 道具の呼び出し：約 80 回。Web 取得：1 回。作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/math-string-cpp（linktitles.py・tlcmp.py・textlint の前後の出力・render/・bench/・site/）
