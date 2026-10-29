# code-links の検証（グループ code-and-library、2026-10-29）

検証した担当：code-links（Issue #8・#72・#62）。報告は [code-links.md](code-links.md)。
見たファイル：`tools/fix_code_links.py`・`tests/tools/test_fix_code_links.py`・`tools/README.md`・`docs/start/how-to-use.md`・`docs/comb/binomial-identities.md`・`docs/comb/counting-bijection.md`・`docs/comb/partition-number.md`・`planning/batches/fix/code-and-library/code-links.md`。
作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-and-library/verify-code-links（作業ツリーの docs/ などの写し、検証用のスクリプト `scripts/`、ビルドしたサイト `site/`、画像 `png/`）。作業ツリーのファイルは、この報告のほかは変えていない。

## 結果

| Issue | 判定 | 要点 |
| --- | --- | --- |
| #8 | 合格（担当の範囲） | 道具が全コードの下に行を正しく置き、使い方の説明（how-to-use#page-anatomy）も道具の動きと合う。手引きへの記載と全ページへの書き込みはメインの仕事（提案 2・手順）で、完了の条件はそれで満たす |
| #72 | 合格（担当の範囲） | 道具を流した写しで、リンクのない `` `snippets/…` `` は 0。48 か所のリンクの先はすべて実在し、git で追跡されている。手引きは提案 2 |
| #62 | 直しが要る（軽微 1 件） | mint の注記は mint を見せるコードにだけ付き、mint を見せる 75 ページすべてから modint へ 1 回で行ける。3 ページの補助関数の説明は中身が正しいが、partition-number の 1 文で記号が節と食い違う |

直しが要る点：1 件。推奨（直さなくてもよい）：5 件。

## 直しが要る点

1. **docs/comb/partition-number.md 164 行目**（#62・記法、手引き §6・チェックリスト code C3）
    - 理由：足した文「コードの `fact[i]` は $i!$ の表、`inv[i]` は $i$ の逆元の表で、どちらも $n$ まで前計算しておく」の $n$ は、この節（cycle-type）で順列の長さを表す $N$ と同じ量である。同じ段落の直前の文は「法は $N$ 以下の数と互いに素（$N$ より大きい素数など）」と $N$ で書いている。また、このページでは $n$ は別の節で分割する整数（$p(n)$）にも使う。地の文は $N$、コードは `n` という手引きの対応（§6・§9）から外れ、別の量と読まれうる
    - 直し方の案：「どちらも $N$ まで前計算しておく」にする（コードの `n` が $N$ にあたることは、コードの `fact[n]`・`dfs(dfs, n, n, 0, 1, 1)` から読める）

## 推奨（直さなくてもよい）

1. **docs/start/how-to-use.md 226 行目**：「完全なプログラムの入出力は、…自前の形で、問題の入力の形ではない」は言い切りすぎである。例題の「解法の詳細」にあるコード片は 23 個あり、問題の入力の形と偶然一致するものがないとは、AtCoder の問題ページを開かない方針のもとでは確かめられない。「問題の入力の形に合わせたものではない」とすれば正確になる
2. **docs/start/how-to-use.md 228 行目**：「型を決める `using mint = atcoder::modint998244353;` の行は要所の外にあるので、コードには出ない」には例外がある。cpp/cpp-environment の `acl-version.cpp:core` は using の行を範囲の中で見せている（注記の付く 114 行のうち 1 行。どちらも同じ型なので食い違いはない）。「ふつうは要所の外にあるので」とすれば言い切りを避けられる
3. **docs/math/sigma-manipulation.md 153 行目**（担当外のページ）：本文がすでに「次のコードの `mint` は ACL の `modint998244353`（[modint](modint.md)）で…」と書いており、道具を流すと直後の行に同じ注記が付いて重なる。担当の提案 9（重なる言及の言い換え）と同じく、後のバッチで本文の方を削るとよい
4. **tools/README.md の節「fix_code_links.py が作る行」**：最後から 2 つ目の項目は「リンクの文字の中にあるものはそのまま」とだけ書くが、道具は `` [`snippets/…`](このリポジトリの URL) `` の形のリンクを確かめ直す。先がなければ「直せない」に出し、URL がずれていれば作り直す（docstring と試験 `test_existing_links_are_checked` のとおり）。README にも 1 文足すと、執筆者が `--check` の出力を読み違えない
5. **ほかのページの定義の見えない補助関数**（Issue に名前のあった 3 ページの外）：範囲の外で定義した `binom`・`comb`・`fact` などを範囲の中で使うコードを数え直した（`scripts/helpers.py`）。binomial-coefficient（kth）・binomial-prefix-sum（mover）・cayley-pruefer（max-diameter）・lattice-paths（knight）・multinomial-coefficient（core・merge）・reflection-principle（below-line・two-sided）・inclusion-exclusion-dp（first-obstacle）は、本文が階乗の表やパスカルの表に触れているか、前提に binomial-precompute を持つ。説明の 1 文がないのは counting-mindset の `verify-small.cpp:core`（検算用の `long long` の `binom`）と、担当の提案 8 の generating-function-counting の `bounded.cpp:closed`（範囲の中の `binom` が範囲の外の `fact`・`ifact` を引く）の 2 つである。足すかはメインが決める

## 確かめたこと

### 道具を docs/ の写しに流した結果

- 写し：作業ツリーの `docs/`・`mkdocs.yml`・`nav.yml`・`overrides/`・`snippets/` を作業用フォルダの `root/` へ写した（08:54 の時点。ほかの担当の直しを含む）。流す前の docs は `docs-orig/` に残した
- `python3 tools/fix_code_links.py --root <写し> --check --stat`：終了コード 1。直すべきファイル 328・追加 1127・地の文のリンク 48・直せない 0・見たページ 354・取り込みのある ```cpp 1149・mint の注記 114（担当の報告と一致）
- 書いた後の `--check`：終了コード 0（差分 0）。もう一度書いても、写しの docs は 1 バイトも変わらない（`diff -r` で一致）
- 作業ツリーそのものへの `--check --stat`（書かない）も同じ件数で、作業ツリーの docs はまだ書かれていない
- 写しを壊して試した：取り込みを別のファイルに変えると行が「更新 1」で作り直され（mint の注記も付く）、取り込みを消して ```text にすると行が「削除 1」で消える

### 独立に書いた検査（道具の関数を使わない）

- **Markdown**（`scripts/vmd.py`）：取り込みのあるフェンス 1149 のうち、1127 は閉じのフェンスの後に空行がちょうど 1 つ、次に字下げのそろった「完全なプログラム：」の行と `{ .kp-code-src }` の行がある。残りの 22 は、空行だけを挟んで同じファイル・同じ字下げのフェンスが続く（その最後のフェンスに行がある）。リンクの先はフェンスの取り込むファイルと一致し、どれも snippets/ にあり、git で追跡されているか、作業ツリーの新しいファイルである。リンクの文字はファイル名。フェンスのない所に行やクラスの行は残らない。誤り 0
- **HTML**（`.venv/bin/mkdocs build --strict` で写しをビルド。WARNING 0。`scripts/vhtml.py`）：
    - `p.kp-code-src` は 1127 個で、どれもすぐ前の兄弟要素がコードの塊（`div.language-cpp.highlight`）である。つまり折りたたみ・囲みの中でも同じ入れ物に入っている。p の中に div・pre はなく、`{ .kp-code-src }` の文字は残らず、`<pre>`・`<code>` の中に「完全なプログラム：」はない
    - ```cpp のコードの塊 1149 個は、どれも次が `p.kp-code-src` か、続きの cpp の塊（22）である
    - mint の注記：表示されたコードの文字に語 `mint` がある塊（続きの組はまとめる）と、注記のある行が 114 対 114 で一致し、ずれ 0。math/modint の 3 行には注記がない。注記のリンクはどれも modint のページへ行く
    - mint を ```cpp に見せるページは 75 で、75 ページすべてに modint へのリンクがある（完了の条件の 1 つ目）
- **字下げ**：字下げした行 38 は、どれも `??? note`（37）か `!!! tip`（1）の中である。docs にはタブ（`=== "…"`）の中の取り込みはない（タブは試験 RenderTest が確かめている）
- **地の文の言及**：リンクにした 48 か所と、how-to-use の `` [`snippets/`](…/tree/main/snippets) `` の 49 本は、blob はファイル・tree はフォルダを指し、どれも実在する。フェンスの外で、リンクのない `` `snippets…` `` は 0。残るのはコードの書式でない ds/weighted-union-find 119 行目の「snippets に置く」だけで、Issue の対象の外である（担当の提案 9）
- **見た目**：写しのサイトを `python3 -m http.server`（127.0.0.1:41873。使い終えて止めた）で開き、幅 390px のライトとダークで撮った。`png/uf-note-light.png`・`png/uf-note-dark.png`（折りたたみ「自作するとき」の中の行）、`png/bi-p0-light.png`（binomial-identities の rect-sum と mint の注記）、`png/pn-p2-dark.png`（partition-number の cycle-type）、`png/dbg-tip-dark.png`（`!!! tip` の中）。行はコードのすぐ下の段落として出て、ダークでも読める。kp.css の提案 1 はまだ入っていないので、ふつうの段落の大きさで出る（担当の画像 `css-dark-360.png` で、提案の見た目も見た）

### #62 の 3 ページの説明（コード片と照らした）

| ページ・行 | 書いた文 | コード片で確かめたこと | 結果 |
| --- | --- | --- | --- |
| binomial-identities 147 | `binom(n, k)` は階乗と逆階乗の表から $O(1)$、範囲外は 0 | `rect-sum.cpp`：`init_binom(r2 + c2 + 1)` で fact・ifact を作り、`binom` は `n < 0 \|\| k < 0 \|\| k > n` で 0、ほかは `fact[n] * ifact[k] * ifact[n - k]` | 正しい |
| binomial-identities 197 | `c[x][t]` は $x \le K$ の $\binom{x}{t}$ をパスカルの漸化式で $O(K^2)$ 時間で前計算した表 | `pair-powers.cpp`：`c` は $(K+1) \times (K+1)$ で、`c[x][i] = c[x-1][i-1] + c[x-1][i]` の二重ループ | 正しい |
| binomial-identities 214 | `binom(n, k)` は mod を取らないパスカルの表（$n \le 63$）から引き、範囲外は 0 | `verify.cpp`：`TABLE = 64` の `long long c_table`、`assert(n < TABLE)`、範囲外は 0 | 正しい |
| counting-bijection 77 | `comb(n, r)` は階乗と逆階乗の表（$2 \times 10^5$ まで）から $O(1)$、範囲外は 0 | `factorization.cpp`：`MAX = 200000` の fact・ifact、`comb` は範囲外で 0 | 正しい |
| partition-number 164 | `fact[i]` は $i!$、`inv[i]` は $i$ の逆元の表で、$n$ まで前計算 | `cycle-type.cpp`：`fact(n + 1)`・`inv(n + 1)`、`inv[i] = mint(i).inv()` | 中身は正しい。記号は「直しが要る点」1 |

- リンク先の節（binomial-precompute の `#fact-ifact`「fact を前から、ifact を後ろから作る理由」、`#composite-mod`「…パスカルの三角形で作る」）は実在し、それぞれ階乗の表とパスカルの漸化式を説明している。verify.cpp・pair-powers.cpp は法が素数（か mod なし）でパスカルの表を使うが、節の漸化式はそのまま当てはまるので、リンクとして適切である
- どの文も段落の末尾にあり、道具を流した後はコード → 「完全なプログラム」の行の順になる（写しで確かめた）
- 3 ページの `updated` は 2026-10-29 になっている。expected-value-dp・probability-dp の related にはもとから rational-mod がある（担当の報告のとおり）。prerequisites に modint・rational-mod を持つページは 0 のままで、この判断は提案 7 としてメインに渡っている

### #8 の使い方の説明

- 226・228 行目の 2 段落は、道具の行の形（「完全なプログラム：ファイル名（GitHub）」、続きのときは最後のコードの下だけ、mint の注記の形）と合う
- 「`#include`・`main`・入出力はほとんど省いてある」の根拠の数を数え直した：取り込み 1151 のうち、表示される範囲に `#include` があるのは 6、`int main` は 16、`cin >>` は 47（担当の数と一致）
- リンク（`[modint](../math/modint.md)`・`[コード片の約束](notation.md#code)`・GitHub の `snippets/`）は通る。説明は道具を流した後の姿なので、how-to-use の変更と道具の書き込みを同じ pull request でマージする必要がある（担当の判断 3 に同意）

### 検査

| 検査 | 結果 |
| --- | --- |
| `.venv/bin/python -m unittest tests/tools/test_fix_code_links.py -v`（3.12.15） | 24 個とも通る（RenderTest も本物の Python-Markdown で走る） |
| `.venv/bin/python -m unittest discover -s tests/tools` | 68 個、OK |
| `python3 -m unittest discover -s tests/tools`（システムの 3.10.12） | 68 個、OK（Python-Markdown の要る 3 個は飛ばす） |
| `python3 tools/check_pages.py --page <id> -v`（how-to-use・binomial-identities・counting-bijection・partition-number） | エラー 0・警告 0 |
| `python3 tools/check_pages.py`（作業ツリー全体） | エラー 0・警告 0 |
| `python3 tools/check_pages.py --root <写し> -v`（道具を流した後の 353 ページ） | エラー 0・警告 0 |
| `mkdocs build --strict`（写し。作業用フォルダの `site/` へ） | 通る。WARNING 0 |
| `npx textlint`（直した 4 ページを HEAD と比べる） | エラー 0。警告は HEAD と同じ数・同じ中身（how-to-use 4・binomial-identities 16・counting-bijection 21・partition-number 16。how-to-use は行番号がずれただけ） |
| `npx textlint`（道具が変える 328 ページの、流す前と後） | どちらも警告 4290・エラー 0 で、増えた・消えた指摘は 0 |
| `python3 tools/gen_site.py --check` | 古いのは llms.txt・graph.json・how-to-use の版の行だけ。版のハッシュが front matter（updated）の変更で変わるためで、メインが流せば直る |

## メインへの申し送り

- 担当の「メインが流す手順」の順でよい。ほかの担当の docs・snippets の直しが終わってから道具を流し、`--check` が終了コード 0 になることを確かめる
- 提案 1（kp.css）・2（手引き §9）・4（notation#code）・5（CI）・6（lychee の除外）は、道具の動きと合っていて、内容に誤りはない
- 道具を流すと、サイト内検索で「modint」を引いたとき、注記のある 74 ページも当たるようになる（Issue #62 の求めたことの結果で、誤りではない）
