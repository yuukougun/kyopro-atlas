# math-string-cpp の直しの検証（バッチ minor-content）

- 検証した担当：math-string-cpp（Issue #34・#35・#36・#37・#38・#39・#40・#41）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/minor-content（ブランチ fix/minor-content、commit 前の差分）
- 見たもの：Issue の本文（`gh issue view`）、担当の報告 math-string-cpp.md、12 ページの `git diff`、行き先のページの見出しと本文、planning/checklists/（fact・clarity・figure）、planning/style-guide.md
- 結論：**8 件とも合格。直しが要る点は 0**
- ファイルは直していない。git は読むだけ。Issue にはコメント・編集・クローズをしていない

## Issue ごとの結果

### #34 メビウス関数の篩の O(M) を O(V) に：合格

- mobius-function 165 行目が「$O(V)$ だが」になっている。直前の 163 行目の「$V$ は表を作る値の上限」と同じ節（#sieve）で、要点（39 行目）と front matter の complexity の「線形篩なら O(V)」とも一致する
- ページの中に `O(M)` は残っていない。$M$ は互いに素な組の上限（$1 \le j \le M$）の意味だけで使われている

### #35 「ヴァンデルモンドの等式」を「Vandermonde の恒等式」に：合格

- binomial-coefficient 170 行目（#comparison）が「[Vandermonde の恒等式](../comb/binomial-identities.md#vandermonde)」になっている。行き先の節の見出しは「Vandermonde の恒等式（2 グループから合計 k 個）」、anchor `vandermonde` は見出しと sections の両方にあり、ビルドしたサイトでも解決する
- 159 行目（#next-steps）は別の節で、リンクを重ねてもよい（手引き §14-23）。同じ文の「[二項係数の恒等式](../comb/binomial-identities.md)」は題名「二項係数の恒等式と和の公式」を略したもので、残してよい
- サイトの中の「ヴァンデルモンド」は lagrange-interpolation 144 行目の「ヴァンデルモンドの行列式」（別の概念）だけになった

### #36 括弧列の図の説明を「上・下」に：合格

- mountain.svg：1 つ目の組（`translate(0,0)`、y 0〜250）が「正しい：負にならず、最後が 0」で `( ( ) ( ) )`＝(()())、折れ線は 0→1→2→1→2→1→0。2 つ目の組（`translate(-350,250)`、y 250〜500）が「正しくない：途中で −1」で `( ) ) ( ( )`＝())(()、折れ線は 0→1→0→−1→0→1→0 で、3 文字目に赤い丸がある
- 64 行目の代替テキスト「上の (()()) は 0 の線を下回らず最後に 0 へ戻る。下の ())(() は、最後が 0 でも 3 文字目で −1 に下がるので正しくない」と、66 行目の「この図で、下の列は最後の値だけを見ると正しく見える」は、図の上下と一致する（下の列は最後が 0 で、途中の最小が −1）
- ビルドしたページを 390px のライトとダークで撮って目で確かめた（図は白の背景で、ダークでも読める）。ビルドした HTML の alt も上の文になっている
- ページの中に図を指す「左・右」は残っていない（ほかの「左から・右から」は読む向きの話）。SVG は変わっておらず、`check_svg.py` は警告 0

### #37 題材別の表のページ名を行き先の題名に：合格

表の「ページ」の列のリンクの文字と、行き先の front matter の title を突き合わせた（作業用フォルダのスクリプト tabletitles.py）。

| 行 | リンクの文字 | 行き先の題名 | anchor |
| --- | --- | --- | --- |
| grid 91 | マンハッタン距離と 45 度回転 | 同じ | （ページ） |
| grid 92 | 回転・平行移動・アフィン変換 | 同じ | `#grid-rotation` あり |
| mex 82 | 一部を固定して数える | 同じ | （ページ） |
| mex 84 | 遅延セグメント木の載せ方の型 | 同じ | `#reformulate` あり |
| subsequence-and-substring 82・85 | フェーズを状態に持つ DP | 同じ | `#matched-prefix`・`#counting-phases` あり |
| subsequence-and-substring 83 | 余り・個数を状態に持つ DP | 同じ | （ページ） |
| subsequence-and-substring 87 | KMP 法（足したリンク） | KMP 法と文字列の周期（略しただけ） | `#matching` あり |
| xor 101 | XOR 畳み込み | 同じ | `#transform` あり |

- Issue に挙がっていない mex 88 行目の「遅延セグメント木の使い方の型の力試し」も「載せ方の型の力試し」に直っている（`#challenge` あり）。同じずれなので妥当
- 4 ページの表のリンクで題名と違うのは、題名の一部を取った略した名前（「偶奇」「主客転倒」「Grundy 数」「集合のハッシュ」など）だけになった。例外は下の「任意」1 の 2 つ
- 390px で 4 ページの表を撮り、行の崩れがなく新しいリンクの文字が出ていることを見た

### #38 ABC110 C の要約を「入れ替え」に：合格

- string-basics 235 行目が「2 種類の文字を選んで一斉に入れ替える操作を繰り返して、S を T にできるかを判定する。」で、台帳 data/problems.yaml（HEAD の値。この作業ツリーのほかの担当も abc110_c は変えていない）の summary と一字一句同じ
- `python3 tools/ap.py show abc110_c`：C. String Transformation・diff 949。label・URL・diff は変わっていない
- #character-mapping（入れ替えか片道かで条件が変わる）と練習の方針（「操作は 2 種類の文字の入れ替えである」）と食い違わない。`fix_problems.py --check --page string-basics` は直すべき行 0

### #39 誤差のページから FMA の注意へリンク：合格

- geometry-precision 184 行目（#eps の最後）に「**手元と提出で結果が変わる**。AtCoder は `-march=native` でコンパイルするので、小数の外積の符号や `== 0` の判定が手元と変わりうる（[FMA](../cpp/cpp-environment.md#march-native)）。…」がある。Issue の 1 文を含み、リンク先の anchor `march-native` は実在する
- 2 文目の対処（整数で計算できるなら整数のまま外積を求める、実数なら `== 0` でなく EPS で比べる）は、cpp-environment#march-native の「影響」「そろえ方」と手引き §5 geometry の「小数の外積の符号や `== 0` に頼らない」に合う。`[外積・内積・距離の 2 乗で比べる](#integer-comparison)` の anchor も実在する
- 「上の EPS」は同じ節（#eps）の EPS の決め方を指すので、節だけを読んでも通じる。太字の書き出しは同じ節の「**long double**。」「**EPS の決め方**。」の形とそろう
- AtCoder のオプションに `-march=native` があることは cpp-environment#options の表と一致する

### #40 C++ の逆引きに症状と書き方の行を足す：合格

逆引き（cpp-reverse-index）に足した行と、行き先の節の本文を照らした。

| 行 | 書き方・症状 | 行き先 | 照らした結果 |
| --- | --- | --- | --- |
| 89 | `1 << 40`・`1 << k` | cpp-integer-overflow#shift-width | 「型の幅以上のシフトで未定義動作、`1LL << 40` と書く」「`1 << 32` 以上は、どの版でも未定義」と合う（手引き §5 cpp の `1 << 31` の書き方とも矛盾しない） |
| 90 | `__builtin_mul_overflow(a, b, &r)` | #overflow-check | 「あふれたなら true を返す。GCC の拡張」と合う |
| 98 | `midpoint(a, b)`・`clamp(x, lo, hi)` | cpp-math-functions#midpoint-clamp | 「midpoint は C++20、clamp は C++17」「a + b をあふれさせない」と合う |
| 101 | `numbers::pi`・`M_PI`・`acos(-1)` | #pi | 「どの書き方でも double の範囲で同じ値」「numbers::pi は C++20」と合う |
| 170 | `#ifdef ATCODER`・`#ifndef ONLINE_JUDGE` | cpp-environment#judge-macros | 「ジャッジでだけ定義されるマクロ」と合う |
| 316 | 小数の結果が手元と違う | cpp-environment#march-native | when-results-differ の「小数の最後の桁」と合う |
| 317 | 手元では速いのに AtCoder でだけ TLE | cpp-environment#auto-var-init | when-results-differ の「AtCoder でだけ TLE」と合う |

- Issue の挙げた行（pi・midpoint・`1 << 40`・`__builtin_mul_overflow`・ATCODER と ONLINE_JUDGE・症状 2 つ）がすべてあり、それぞれ節へリンクしている。7 つの anchor は見出しの `{#…}` と sections の両方にあり、ビルドしたサイトでも解決する
- 行の並び：書き方の表は行き先の節の順（gcd-lcm → midpoint-clamp → integer-division → pow-sqrt → pi）。症状の表は、疑う順の 4 行（when-results-differ の 1〜4）の後に「ほかに、次の差もある」の順で置かれていて自然
- cpp-io 272 行目（#tle-causes の表の最後）：「関数の中の大きな配列（`int buf[100000];` の先頭だけ使う）｜$2 \times 10^5$ 回呼んで 0.05 秒が、AtCoder と同じ 0 埋めのオプションで 1.03 秒に｜グローバルに置くか、外で 1 回だけ確保する（0 で埋める処理）」。数字は持ち主の cpp-environment#auto-var-init（0.05 秒・1.03 秒、g++-13・g++-15 で同じ程度）と、snippets/cpp-environment/auto-var-init-cost.cpp（`int buf[100000];`、先頭の k 個だけ使う）と一致する。表の前置き（g++-15 の -O2）と条件が違う点はセルに書いてある。直し方は持ち主の「グローバルに置くか、外で 1 回だけ確保して使い回す」と同じ
- 逆引きの「計算量は合っているのに TLE」の行の列挙（`endl`・`std::function`…）は直す前から cpp-io の表の全部ではない（同期の行もない）ので、新しい行を足さなくても食い違いにはならない。関数の中の配列は症状の 317 行目で引ける
- 390px のライト・ダークで #lookup-types・#lookup-macros・#symptoms と cpp-io #tle-causes を撮り、表の崩れがなく、数式（KaTeX）が描かれていることを見た

### #41 cph と、提出用のコピーの目印に説明を添える：合格

- cpp-undefined-behavior の本文で cph が最初に出るのは 101 行目（#out-of-range の「版」）で、そこに「[cph](../cpp/cpp-macros-template-file.md#bundling-tools)（VS Code の拡張 Competitive Programming Helper）」がある。front matter の sections の title（29 行目）は本文ではない。Issue の「cph の初出に…」を満たす
- 276 行目（#debug-build）にも同じ説明とリンクがある。別の節なので手引き §14-23 のとおり重ねてよく、節だけを読んでも cph が何か分かる。274 行目の見出しにはリンクを置いていない（§7）
- 意味は直す前と同じ（ふだんのビルドは cph で AtCoder と同じ `-O2`）。文の長さの警告は増えていない
- 参考の 333 行目「[agrawal-d「Competitive Programming Helper (cph)」](https://github.com/agrawal-d/cph)：cph が VS Code の拡張であること」：README（raw.githubusercontent.com。付録 B のドメイン）を 1 回取得し、h1 が「Competitive Programming Helper (cph)」、本文が「… judge competitive programming problems in VS Code」であることを確かめた。同じ URL をほかのページで別の題名で使ってはいない
- 逆引き 173 行目の `// @impl`：「この教材の作者が改造した cph（VS Code の拡張）で、main の後ろに回す部分を分ける印。公式の cph にはない」と、[cph の改造版](…#bundling-tools) へのリンク。cpp-macros-template-file 262 行目（公式の cph にはなく、この教材の作者が改造した版にだけある）と 266〜268 行目（目印より下を main の後ろに出す）と合う。Issue の「作者が改造した cph で使う目印であることが書いてある」を満たす

## 検査の結果

- `python3 tools/check_pages.py --page <id> -v`：12 ページともエラー 0・警告 0
- `python3 tools/fix_problems.py --check --page <id>`：12 ページとも直すべき行 0・直せない行 0・警告 0
- `npx textlint`（12 ファイル）：エラー 0・警告 105。HEAD の版を作業用フォルダに写して同じ設定で流した結果と突き合わせると、違いは文の長さの警告 3 件の行番号のずれだけで、新しい警告はない
- `python3 tools/check_svg.py docs/img/bracket-sequence/mountain.svg`：警告 0・エラー 0
- `uv run mkdocs build -q --strict -d <作業用フォルダ>/site`：成功（Material の告知だけ）
- 内部リンク：ビルドした 12 ページのリンク（サイドバーを含む 6,713 本）を作業用フォルダのスクリプト checklinks.py で解決し、行き先のファイルと anchor の id がすべて実在した（不達 0）
- 数式：12 ページを `http://127.0.0.1:<ポート>/site/…` で開き、JS を動かした後の DOM で `katex-error` は 0
- 表示：390px のライトとダークで撮って見た（上の各 Issue に書いた節）。ポートは使い終えて止めた
- 差分の範囲：12 ファイルで 41 行の追加・30 行の削除。`git diff --check` は問題なし。docs/img・snippets に差分はない。front matter は `updated`（2026-10-22 → 2026-10-29）だけで、手引き §2.1 で直してよい項目
- `python3 tools/gen_site.py --check`（書かない）：14 ファイルが古い。差分はほかの担当の変更（namori-graph の並びなど）と、版のハッシュ（updated の最大）だけで、この担当の 12 ページの本文から来る差分はない。メインが gen_site を流せば足りる

## 直しが要る点

なし。

## 任意（直さなくても合格。メインの判断に任せる）

1. **#37 の残り**：subsequence-and-substring 84 行目の「[数え上げの重複の除き方](../comb/counting-dedup.md#leftmost)」（題名は「重複の除き方」）と、xor 92 行目の「[木の距離](../tree/tree-distance.md#root-prefix)」（題名は「木の上の距離」）。Issue に挙がっておらず、題名をそのまま含むか、略しただけなので迷わない。担当の判断（残す）に賛成する。そろえるなら「重複の除き方」「木の上の距離」にする
2. **#41 の逆引きの行**：173 行目は「cph（VS Code の拡張）」で、正式名の Competitive Programming Helper は書いていない。表のセルで、リンク先（#bundling-tools）に名前があるので足りる
3. **担当の「判断してほしい点」1**（cph の説明を 101 行目と 276 行目の両方に置いた）：101 行目が本文の初出で Issue の条件を満たし、276 行目は別の節で単独で読まれるので、両方に置くのが手引き §1・§14-23 に合う。縮めなくてよい
4. **担当の提案**：1（prh の `ヴァンデルモンドの(?:等式|恒等式)` → `Vandermonde の恒等式`。「ヴァンデルモンドの行列式」には当たらない）と 2（持ち主の cpp-macros-template-file 262 行目に「VS Code の拡張」を足し、参考に cph の README を足す）は、どちらも妥当と考える

## 使った資料と Web 取得

- https://raw.githubusercontent.com/agrawal-d/cph/main/README.md（1 回。cph の README の h1 と、VS Code の拡張であること）。付録 B のドメインで、新しく noai を確かめたドメインはない。atcoder.jp・codeforces.com は開いていない
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/minor-content/verify-math-string-cpp（site/、shots/、base/（HEAD の版）、textlint-before.txt・textlint-after.txt、links.tsv、checklinks.py、tabletitles.py、gen-check.txt、dom/）
