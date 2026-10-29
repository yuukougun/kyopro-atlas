# code-links の報告（グループ code-and-library、2026-10-29）

担当の Issue：#8（例題のコードの見せ方）・#72（本文の `snippets/…` の言及）・#62（mint から modint へ・補助関数）。
作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/code-and-library（feat/code-and-library）。git は読むだけで、commit などはしていない。
指示どおり、道具の書き込みは作業ツリーの docs/ に流していない。全ページへの書き込みはメインが最後に流す（下の「メインが流す手順」）。

## 直したファイル

| ファイル | 変更 |
| --- | --- |
| `tools/fix_code_links.py` | 新規（489 行）。コードの下の完全なプログラムへのリンクの行・mint の注記・地の文の `snippets/…` のリンクを作る道具。`--check`（差分。あれば終了コード 1）・`--stat`（件数だけ）・`--page`・`--field`・`--root`・`--snippets`。書くのは既定 |
| `tests/tools/test_fix_code_links.py` | 新規（24 の試験）。本物の Python-Markdown と pymdownx があれば、作った行が `<p class="kp-code-src">` になり、コードの塊と同じ入れ物（折りたたみ・タブ）に入ることも確かめる |
| `tools/README.md` | 一覧の表に 1 行、ふだんの検査に 1 行、工程8b の執筆者の行に `fix_code_links.py --page <id>`、節「fix_code_links.py が作る行（#8・#72・#62）」を足した |
| `docs/start/how-to-use.md` | #page-anatomy に 2 段落（226・228 行目）。updated はもとから 2026-10-29 |
| `docs/comb/binomial-identities.md` | 147・197・214 行目の段落の末尾に 1 文ずつ、`updated: 2026-10-29` |
| `docs/comb/counting-bijection.md` | 77 行目の段落の末尾に 1 文、`updated: 2026-10-29` |
| `docs/comb/partition-number.md` | 164 行目の段落の末尾に 1 文、`updated: 2026-10-29` |

`docs/comb/expected-value-dp.md`・`docs/comb/probability-dp.md` は変えていない（related にもう rational-mod がある。#62 の節）。

## 道具の行の形と、決めたこと

道具は fix_problems.py と同じ考え方で、行を決まった形で作り直す（手で書かない）。

````markdown
```cpp
--8<-- "binomial-precompute/binom.cpp:core"
```

完全なプログラム：[`binom.cpp`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/binomial-precompute/binom.cpp)（GitHub）。`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）。
{ .kp-code-src }
````

- **置く場所**：閉じのフェンスの後に空行を 1 つ挟んで置く。空行を挟まないと、Python-Markdown はコードの塊（div）ごと `<p class="kp-code-src">` の中に入れてしまう（サイトと同じ拡張で確かめ、試験 `RenderTest` にした）。字下げはフェンスの開きに合わせるので、`??? note`・`!!!`・`=== "…"`（タブ）・箇条書きの中でも同じ入れ物に入る
- **2 行目**：attr_list の class（`{ .kp-code-src }`）。段落（p 要素）に class が付く。md_in_html より 1 行で済み、Markdown のまま読める
- **同じファイルを続けて取り込むとき**：空行だけを挟んで続き、字下げが同じで、取り込むファイルの組が同じフェンスは 1 つの続きとみなし、最後のフェンスの下にだけ置く（22 か所。例：basics/binary-search の `count.cpp:core` と `:query`、cpp の 11 か所）。地の文を挟めば、それぞれのフェンスの下に置く。メインの決定の「各コードの近くに」と、どの節も単独で読まれる（手引き §1）ことに合わせた。1 つのフェンスで同じファイルを 2 回取り込んでも（cpp/acl-reading の 2 か所）リンクは 1 つ
- **ファイルが違えば**：続いていても別の行（cpp/cpp-integer-overflow の `int128-format.cpp` と `int128-println.cpp`）。1 つのフェンスで別のファイルを取り込めば「`a.cpp`・`b.cpp`」と並べる（今はない）
- **mint の注記**：取り込む範囲に `mint` という語が出れば付ける。範囲は pymdownx.snippets 10.x と同じ切り出し方で読む（`[start:名前]`〜`[end:名前]`、ほかの範囲の目印は出ない、行の範囲 `:3:5`、ファイル全体）。型はファイルの `using mint = …;`（typedef も）から読み、`atcoder::` を外す。ACL の型（`modint998244353`・`modint1000000007`・`modint`・`static_modint<…>`・`dynamic_modint<…>`）は「ACL の」を付け、そうでなければ付けない。modint のページ自身（math/modint）には付けない。型が読めない・2 通りあるときは「直せない」に出し、注記は付けない（今は 0 件）
- **リンクの形**：modint へは、docs/<field>/ のページからは手引き §7 の `../math/modint.md`（同じ math でも）。リンクの文字は modint のページの title
- **作り直し**：「完全なプログラム：」で始まり次の行が `{ .kp-code-src }` の段落は道具のものとみなし、毎回外してから置き直す。ファイル名の変更・mint の有無の変化・続きになって要らなくなった行・取り込みのなくなったフェンスの下の行も追う（削除として数える）。フェンスの中の同じ形の行は見ない
- **見ないもの**：cpp 系（cpp・c++・cxx・cc・hpp・h）以外のフェンス、HTML のコメントの中のフェンス、`;` でエスケープした取り込み
- **地の文の言及（#72）**：フェンス・HTML のコメント・`$$` の外の、行の中のコード `` `snippets/<id>/<名前>` `` を `` [`snippets/<id>/<名前>`](https://github.com/yuukougun/kyopro-atlas/blob/main/snippets/<id>/<名前>) `` にする（フォルダと `snippets/` だけは `…/tree/main/…`）。もう `` [`snippets/…`](このリポジトリの URL) `` の形なら、先のファイルがあるかを確かめ、URL がずれていれば作り直す（ファイルの名前を変えたときに `--check` で気づける）。見出しの中・HTML のコメントのある行・ないファイルは直さず「直せない」に出す（今は 0 件）

## #8 例題のコードの見せ方 — 一部（道具と使い方の説明は済み。全ページへの書き込みと手引きはメイン）

- 決定（メイン）：本文のコードは要所のまま、各コードの近くに GitHub の完全なプログラムへのリンクを出す。入出力は自前の形で、提出用ではないと使い方に書く
- 道具：`tools/fix_code_links.py`（上の節）。全ページへの試しは下の「作業用フォルダでの試し」
- `docs/start/how-to-use.md` の #page-anatomy（226 行目）：「本文のコードは要所だけで、`#include`・`main`・入出力はほとんど省いてある」「各コードの下の『完全なプログラム：ファイル名（GitHub）』の行のリンクから、GitHub の [`snippets/`](https://github.com/yuukougun/kyopro-atlas/tree/main/snippets) のファイルで見られる」「同じファイルのコードが続くときは最後のコードの下にだけある」「入出力は手元で確かめるための自前の形で、問題の入力の形ではない。提出用ではないので、問題に使うときは入出力を合わせて書く」「書き方の約束は[コード片の約束](notation.md#code)」を書いた
  - 「ほとんど省いてある」は数えて決めた：取り込み 1151 か所のうち、範囲に `#include` があるのは 6、`int main` は 16、`cin >>` は 47
  - この説明は、メインが道具を流した後の姿を書いている。流す前にマージすると、行がまだないページで説明だけが先に出る
- 完了の条件の残り：手引きへの記載（提案 2）と、全ページへの書き込み（メインが流す手順）

## #72 本文の `snippets/…` の言及 — 一部（道具は済み。書き込みと手引きはメイン）

- 道具が、地の文の 40 ページ 48 か所をリンクにする（Issue の数と一致）。全ページの試しで、リンクのない `` `snippets/…` `` は 0 になった（作業用フォルダの `verify_cov.py` で数えた）
- 48 か所のうち 37 か所は、同じファイルを取り込むコードの前後 3 行以内にある（例：tree/hld の「構築の中心は次のとおりである（完全なプログラムは `snippets/hld/usage.cpp`）。」）。道具の行と重なるが、メインの決定どおりリンクにした。言い換えるかは提案 9
- 残りの 11 か所はコードから離れているか、本文に取り込まないファイル（`cht/monotone.cpp`・`burnside-lemma/cube.cpp`・`hash-safety/thue-morse.cpp`・`flow-lower-bounds/usage.cpp` など）を指すもので、リンクにする意味が大きい
- コードの書式でない言及が 1 か所ある：ds/weighted-union-find.md 119 行目「完全なプログラムは乱数の試験つきで snippets に置く」。担当外のページなので直していない（提案 9）
- 完了の条件（docs の本文にリンクのない `snippets/…` が残らない）は、メインが道具を流せば満たす。手引きへの書き方の追加は提案 2

## #62 mint から modint へ・補助関数 — 一部（注記は道具、補助関数は済み、related は変更不要）

### mint の注記

- 取り込む範囲に `mint` が出るコードは 75 ページ・117 か所（Issue の 75 ページと一致）。modint のページ自身の 1 か所（`modint/dynamic.cpp:core`）を除き、続きの 2 組をまとめて、74 ページ 114 行に注記が付く。型は `modint998244353` が 106 行、`modint1000000007` が 8 行
- 全ページの試しで、modint 以外の 74 ページすべてに modint へのリンクがあることを確かめた（`verify_cov.py`）。完了の条件「mint を見せる全ページから 1 回のクリックで modint へ」は、メインが道具を流せば満たす
- how-to-use の #page-anatomy（228 行目）に、注記の意味（`mint` は四則演算のたびに自動で余りを取る型、`using mint = atcoder::modint998244353;` は要所の外にあって見えない、法が $10^9 + 7$ なら `modint1000000007`）と modint へのリンクを書いた

### 定義の見えない補助関数（1 文ずつ、binomial-precompute の該当の節へリンク）

| ページ・行 | コード | 書いた文（要旨） | リンク |
| --- | --- | --- | --- |
| binomial-identities 147 | `rect-sum.cpp:core` の `binom(…)` | 前計算した階乗と逆階乗の表から $O(1)$ で返し、範囲外では 0 | `binomial-precompute.md#fact-ifact` |
| binomial-identities 214 | `verify.cpp:core` の `binom(…)` | mod を取らないパスカルの三角形の表（$n \le 63$）から引き、範囲外では 0 | `binomial-precompute.md#composite-mod` |
| binomial-identities 197 | `pair-powers.cpp:core` の `c[x][t]` | $x \le K$ の $\binom{x}{t}$ をパスカルの三角形の漸化式から $O(K^2)$ 時間で前計算した表 | `binomial-precompute.md#composite-mod` |
| counting-bijection 77 | `factorization.cpp:core` の `comb(…)` | 階乗と逆階乗の表（$2 \times 10^5$ まで）を前計算し、$O(1)$ で返し、範囲外では 0 | `binomial-precompute.md#fact-ifact` |
| partition-number 164 | `cycle-type.cpp:core` の `fact[…]`・`inv[…]` | `fact[i]` は $i!$、`inv[i]` は $i$ の逆元の表で、どちらも $n$ まで前計算 | `binomial-precompute.md#fact-ifact` |

- 指示にあったのは binomial-identities の `binom`・counting-bijection の `comb`・partition-number の `fact` である。binomial-identities には `binom` が 2 つ（mod の表と、mod を取らないパスカルの三角形）あるので両方に書いた。同じページの `c[x][t]`（範囲の外で作る表）と、partition-number の同じコードの `inv[…]` も、同じ問題なので 1 文に含めた
- 中身はコード片で確かめた（`init_binom`・`TABLE = 64` と `assert(n < TABLE)`・`MAX = 200000`・`inv[i] = mint(i).inv()`）。どの文も段落の末尾に置いたので、道具の行はコードの直下に来る
- textlint：binomial-identities の `c[x][t]` の文が最初は「で」の重複の警告を出したので言い直し、4 ページとも HEAD と同じ警告の数（エラー 0）にした

### related（rational-mod）

- expected-value-dp と probability-dp の related には、もう rational-mod がある（b1 のころから。`git log -S`）。page-template（#56）でページ下部の「関連」に出るので、どちらからも rational-mod へ行ける。変えていない
- ほかの確率・期待値のページ（kind に「確率・期待値」）で、mint を見せるのに prerequisites にも related にも rational-mod がないもの：coupon-collector・expectation-linear-equations・expectation-of-square・expectation-tail-sum・linearity-of-expectation・probability-symmetry。probability-symmetry は本文にも rational-mod へのリンクがない（提案 7）

## 作業用フォルダでの試し（件数と差分）

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-and-library/code-links

- `root/` に作業ツリーの docs/ の写し（ほかの担当の直しを含む、最後に写した時点のもの）と mkdocs.yml・nav.yml を置き、snippets/・overrides/ は作業ツリーへのリンクにした。`python3 tools/fix_code_links.py --root <作業用フォルダ>/root` で書いた
- 結果：見たページ 354（353 ページと docs/index.md）、取り込みのある ```cpp 1149（取り込み 1151 行）、直したファイル 328、置いた行 1127（1149 − 続きの 22）、うち mint の注記 114、地の文のリンク 48、直せない 0、削除・更新 0
- 2 回目の `--check` は差分 0（同じ結果を作り直せる）
- 差分：`check-diff.txt`（unified diff、12391 行。作業ツリーに `--check` を流したもの）、ファイルごとの件数：`check-stat.txt`。字下げした行（折りたたみ・囲みの中）は 38
- 作業ツリーへの `--check --stat` も同じ件数（直すべきファイル 328・追加 1127・リンク 48・直せない 0）

## 検査

| 検査 | 結果 |
| --- | --- |
| `python3 -m unittest discover -s tests/tools`（.venv の Python 3.12） | 全部通る（新しい 24 を含む。RenderTest は本物の Python-Markdown で走る） |
| 同じ（システムの Python 3.10） | 全部通る（Python-Markdown の要る 3 つは飛ばす） |
| `check_pages.py --page` how-to-use・binomial-identities・counting-bijection・partition-number・expected-value-dp・probability-dp | エラー 0・警告 0 |
| `check_pages.py`（作業ツリー全体） | エラー 0・警告 0 |
| `check_pages.py --root <写し>`（道具を流した後の全ページ） | エラー 0・警告 0（modint への相対リンクも通る） |
| `mkdocs build --strict -f <写し>/mkdocs.yml -d <作業用フォルダ>/site`（venv の mkdocs。作業ツリーの site/ は触らない） | 通る。1127 行がすべて `<p class="kp-code-src">` になり、直前の兄弟要素がコードの塊（`div.language-cpp`）であること、`{ .kp-code-src }` の文字が残らないこと、p の中に div が入らないことを、全ページの HTML で確かめた |
| textlint（道具を流した 328 ページの写しと、元のページ） | 道具の行で増える警告・エラーは 0。違いが出た 1 ページ（graph/general-matching）は、ほかの担当が同時に本文を直したためで、道具の行を外すと元と同じだった |
| textlint（直した 4 ページ） | エラー 0。警告は HEAD と同じ数（how-to-use 4・binomial-identities 16・counting-bijection 21・partition-number 16） |
| 見た目 | kp.css の提案（提案 1）を写しのサイトに当てて、幅 360px のライトとダークで撮った（`png/css-360.png`・`png/css-dark-360.png`。当てないものは `png/plain-360.png`） |

`check_snippets.py` は、snippets を変えていないので流していない。

## メインが流す手順

1. このグループのほかの担当の直し（docs・snippets）が終わってから流す（この報告を書いた時点で、作業ツリーではほかの担当が 38 ページと snippets を直していた。道具は流した時点の取り込みと範囲から行を作るので、後から範囲や `mint` が変わっても、流し直せば追う）
2. `python3 tools/fix_code_links.py --check --stat`（件数を見る）→ `python3 tools/fix_code_links.py`（書く）→ もう一度 `--check`（終了コード 0）
3. `python3 tools/check_pages.py`・`python3 -m unittest discover -s tests/tools`・`python3 tools/gen_site.py --check`（本文だけの変更なので生成物は変わらないはず。updated を上げるなら変わる。判断 1）・`mkdocs build --strict`
4. commit は道具・試験・README と、道具の書き込み（328 ページ）を分けると、差分を読みやすい

## 提案（メインに頼む共有ファイルの変更）

1. **kp.css**（別の担当が直しているので書いていない）：末尾に次を足す。行がコードの下に寄り、小さく薄い字になる。色は Material の変数なのでダークでも読める（上の画像）

    ```css
    /* コードの下の「完全なプログラム：…（GitHub）」の行（tools/fix_code_links.py。#8・#62） */
    .md-typeset .kp-code-src {
      margin-top: -0.6em;                          /* 直前のコードの塊（pre の下の 1em）に寄せる */
      font-size: 0.85em;
      color: var(--md-default-fg-color--light);
    }
    ```

2. **手引き（planning/style-guide.md）§9**：次を足す（#8・#72 の完了の条件「手引きに書かれている」）
    - 「本文のコードの下には、`tools/fix_code_links.py` が『完全なプログラム：[`<名前>`](GitHub の URL)（GitHub）』の行と `{ .kp-code-src }` を置く（取り込む範囲に `mint` が出れば、同じ行に『`mint` は ACL の `modint998244353`（[modint](../math/modint.md)）』）。手で書かず、取り込みを足したら `python3 tools/fix_code_links.py --page <id>` を流す」
    - 「完全なプログラムの入出力は自前の形でよく、提出用にしない（問題の入力の形に合わせない。理由は AtCoder の問題ページを開かないので入力の形を確かめられないこと）。読者向けの説明は how-to-use#page-anatomy」
    - 「本文から snippets のファイルを指すときは `` `snippets/<id>/<名前>` `` と書けば、道具が GitHub へのリンクにする。コードの直前・直後で『完全なプログラムは `snippets/…`』とだけ言う文は、コードの下の行と重なるので書かない」
    - §12（報告の形）の検査に `fix_code_links.py --page <id>` を足す
3. **手引き §9 か §2.7**（#62）：「取り込む範囲の外で定義した補助関数・表（`binom`・`comb`・`fact` など）を範囲の中で使うときは、どの前計算か（表か $O(k)$ の積か、範囲外の値）を本文に 1 文で書き、binomial-precompute の該当の節へリンクする」
4. **start/notation.md の #code**：最後の文「完全なプログラムは手元でコンパイルと実行を確かめてある。」の後に「各コードの下のリンクから GitHub で見られる（[ページの構成と読み方](how-to-use.md#page-anatomy)）。」を足す
5. **CI（.github/workflows/check.yml の pages）**：道具を流した後に `python tools/fix_code_links.py --check --stat` を足す。範囲の中身（mint の有無）やファイル名が変わったとき、新しいページで流し忘れたときに落ちる
6. **links.yml（lychee）**：`--exclude '^https://github\.com/yuukougun/kyopro-atlas/(blob|tree)/main/snippets'` を足す。道具を流すと、自分のリポジトリへのリンクが 1176 本（URL は 975 種。今の docs の github.com の URL は 169 種）増え、週 1 回の外部リンクの検査が GitHub に多く問い合わせる（429 は通す設定なので落ちはしないが遅い）。先のファイルがあることは `fix_code_links.py --check` が確かめる（コードの下の行は取り込みから作り、地の文のリンクは先を確かめる）
7. **related に rational-mod**（#62 の残り）：coupon-collector・expectation-linear-equations・expectation-of-square・expectation-tail-sum・linearity-of-expectation・probability-symmetry（どれも mint を見せる確率・期待値のページで、prerequisites にも related にもない）。少なくとも本文にもリンクのない probability-symmetry
8. **同じ種類の補助関数の候補**（#62 と同じ問題。目視で確かめたのは 1 つ）：comb/generating-function-counting の `bounded.cpp:closed` は、範囲の中の `binom` が範囲の外の表 `fact`・`ifact` を引く。本文に前計算の説明があるかは確かめていない。ほかのページは、範囲の中で定義しているか、本文が binomial-precompute へリンクしていた（作業用フォルダの `survey7.py` の粗い数え方）
9. **重なる言及の言い換え**（後のバッチでよい）：地の文の 48 か所のうち 37 か所は、同じファイルを取り込むコードの前後 3 行以内の「（完全なプログラムは `snippets/…`）」で、道具の行と同じ先を指す。何で確かめたか（「乱数の入力で愚直な方法と比べている」など）だけを残して言い換えると、行が重ならない。ds/weighted-union-find.md 119 行目の「完全なプログラムは乱数の試験つきで snippets に置く」（コードの書式でない）も同じ

## メインに判断してほしい点

1. **updated**：道具の書き込みは 328 ページの読者に見える変更（手引き §2.1 では updated を直す）である。道具は front matter を変えない。全ページを流した日に上げるか、行の追加はページの中身の変更ではないとして上げないか。上げないなら手引き §2.1 に例外として書く
2. **同じファイルの行をどこまでまとめるか**：今は「空行だけを挟んで続くフェンス」だけをまとめ、地の文を挟めば各コードの下に置く（tree/hld では、同じ `usage.cpp` の行が 4 つ出る）。節ごとに 1 つにまとめる案もあるが、節の途中から読まれると近くにリンクがなくなるので、各コードの下を選んだ
3. **how-to-use の説明の時期**：説明は道具を流した後の姿なので、how-to-use の変更と道具の書き込みを同じ pull request でマージしてほしい

## 残った点

- 全ページへの書き込み・手引き・kp.css・CI はメイン（上の手順と提案）
- 道具は ```cpp の取り込みだけを見る。今の docs に、ほかの言語のフェンスでの取り込みはない

## 検証の指摘への対応（2026-10-29）

検証の報告：[verify-code-links.md](verify-code-links.md)。直しが要る点 1 件を直した。推奨（直さなくてもよい）の 5 件は、直す点として頼まれていないので変えていない（下の表。メインが決める）。

### 直しが要る点 1：docs/comb/partition-number.md 164 行目（#62）— 直した

- 直した内容：足した文の「どちらも $n$ まで前計算しておく」を「どちらも $N$ まで前計算しておく」にした。ほかの字は変えていない
- 指摘は正しいと判断した。手引き §6 の文字は「列の長さ・頂点数 $N$」で、§9 はコードの変数名を §6 にそろえる（コードは `n`）。この節（cycle-type）は「長さ $N$ の順列」と書き、同じ段落の直前の文も「法は $N$ 以下の数と互いに素」と $N$ で書く。このページの $n$ は、分割数 $p(n)$ の節で分割する整数に使っている
- コードの `n` が $N$ にあたることは、表示される範囲の `fact[n]`・`dfs(dfs, n, n, 0, 1, 1)` から読める。表の大きさは範囲の外の `fact(n + 1)`・`inv(n + 1)`（添字 0 から `n`）で、「$N$ まで」と合う
- 直した後、この節（137〜172 行目）の地の文に小文字の $n$ は残らない
- front matter は変えていない（`updated: 2026-10-29` は最初の直しのまま）

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --page partition-number -v` | エラー 0・警告 0 |
| `npx textlint docs/comb/partition-number.md` | エラー 0・警告 16。HEAD の写しと同じ数で、位置を除いた中身も一致する。164 行目の警告（164:108、助詞「に」の重複）は HEAD からある元の段落の部分 |
| `python3 tools/fix_code_links.py --check --page partition-number`（書かない） | 置く行 4（うち mint の注記 2）・直せない 0。cycle-type の行は、直した段落の後のコードの直下に来る。終了コード 1 は、指示どおり道具を作業ツリーの docs に流していないため |

作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-and-library/fixup-code-links（textlint の出力 `textlint-now.txt`・`textlint-head.txt` と、HEAD の写し `head/`）。

### 推奨（直さなくてもよい）5 件 — 変えていない

| 推奨 | 場所 | 判断 |
| --- | --- | --- |
| 1 | docs/start/how-to-use.md 226 行目「…自前の形で、問題の入力の形ではない」 | 同意する。AtCoder の問題ページを開かないので、偶然一致するものがないとは確かめられない。「問題の入力の形に合わせたものではない」にすれば言い切らずに済む。担当のファイル |
| 2 | docs/start/how-to-use.md 228 行目「…の行は要所の外にあるので、コードには出ない」 | 同意する。例外を確かめた：cpp/cpp-environment の `acl-version.cpp:core` は、範囲の中（ファイルの 6 行目）に `using mint = atcoder::modint998244353;` がある。「ふつうは要所の外にあるので」にする。担当のファイル |
| 3 | docs/math/sigma-manipulation.md 153 行目（本文の注記と道具の注記が重なる） | 担当外のページ。提案 9（重なる言及の言い換え）に加える |
| 4 | tools/README.md 105 行目「リンクの文字の中にあるものはそのまま」 | 同意する。道具は、このリポジトリの URL へのリンク `` [`snippets/…`](…) `` を確かめ直し、URL がずれていれば作り直し、先がなければ「直せない」に出す（docstring の 37〜38 行目と試験 `test_existing_links_are_checked`）。そのままにするのは、ほかのサイトへのリンクだけである。README にこの 1 文を足す。担当のファイル |
| 5 | counting-mindset の `verify-small.cpp:core`・generating-function-counting の `bounded.cpp:closed`（定義の見えない補助関数） | 担当外のページ。提案 8 に counting-mindset を加える |

1・2・4 は担当のファイルの中の言い回しで、直すなら数分で済む。直すかはメインが決める（直すなら、その文だけ検証すればよい）。

### Issue の状態（この直しの後）

- #8・#72：一部のまま。道具・試験・README・使い方の説明は済み。全ページへの書き込み（「メインが流す手順」）と手引き（提案 2）はメイン
- #62：一部のまま。補助関数の説明（3 ページ）は検証の指摘を直して済み。related は変更不要（もとから rational-mod がある）。mint の注記は道具を流せば付く（メイン）
