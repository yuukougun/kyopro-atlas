# code-docs の報告（グループ code-and-library、2026-10-29）

- 担当：メインが採ると決めた提案（[code-links.md](code-links.md)・[own-library.md](own-library.md) の提案）を、手引き・設計書・部品の約束・使い方・記法・kp.css・CI に反映する（Issue #8・#72・#62・#53・#64）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/code-and-library（feat/code-and-library）。git は読むだけ（status・diff・log・show）。Issue には触れていない。atcoder.jp・codeforces.com は開いていない
- 道具 `fix_code_links.py` の作業ツリーへの書き込みと `gen_site.py` は流していない（`--check` だけ）
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/code-docs

## まとめ

| 頼まれたこと | ファイル | 状態 |
| --- | --- | --- |
| 1 手引き（§2.1・§4・§9・§15-5） | planning/style-guide.md | 済み |
| 2 部品の約束（§2・§7） | planning/interfaces.md | 済み |
| 3 設計書（technique の構成・verify） | planning/design.md | 済み |
| 4 使い方の #page-anatomy | docs/start/how-to-use.md | 済み（updated はもとから 2026-10-29） |
| 5 記法の #code | docs/start/notation.md | 済み（updated はもとから 2026-10-29） |
| 6 コードの下の行の見た目 | overrides/assets/css/kp.css | 済み |
| 7 CI | .github/workflows/check.yml・links.yml | 済み（道具の書き込みと同じ pull request に入れること。下の「メインに判断してほしい点」の 1） |

## 直したファイルと内容

### 1. planning/style-guide.md

- 22 行（§2.1 の updated）：「道具 `fix_code_links.py` が作る所（コードの下の行と地の文の `snippets/…` のリンク。§9）の変更でも直さない。」を足した。「だけ」が 3 つ重なったので、front matter・生成部分の文とは分けた
- 102〜119 行（§4、「ACL では」の例の後）：「自作するとき」の決まり。own-library.md の提案 1（検証の指摘 6 で改めた版）を短くした。冒頭の 1 文（ページの題の部品の自作に当て、節の中の変種と使い方の例には当てない）と 5 項目
  - **置き場所**：処理の流れの節の中で、手順の擬似コード（なければ手順の説明）の後。境界の小見出しの前後どちらでもよい。上の帯の自作の節があればその節の終わり、発展の概要は `#library`
  - **折りたたむか**：ACL に同じ部品があり「ACL では」を置くなら `` ??? note "自作するとき：`型名`（ACL の `名前` に当たる）" ``。ACL にない部品と ACL の部品で書けない操作は開いて置く
  - **ACL との対応**：折りたたむときは最初の段落、開いて置くときは同じ節のコードより前の段落に書く。違いは library-design#acl-names の表にもまとめる（行を足すのは提案）
  - **名前**：メンバ関数の名前・引数の順・0-indexed・半開区間は ACL にそろえる。コンストラクタは ACL のドキュメントの「コンストラクタ」の項の形（`dsu(n)`・`fenwick_tree(n)`・`segtree(v)` など）。そろえないのは本文の手順や図と名前を合わせたいときだけ
  - **試験とリンク**：折りたたむときは試験の 1〜2 文と library-design の #interface・#verify へのリンクの文で結ぶ。開いて置くときはリンクの文だけでよい。verify の問題はページ下部に出るので並べ直さない（触れるなら judge.yosupo.jp へのリンク。§15-5）
  - 例は折りたたむ形の 1 つだけにした（union-find#operations の今の形に合わせた）。開いて置く形の例（sparse-table）は、項目の文で足りるので省いた
- 256〜258 行（§9、取り込みの例の直後）：3 項目
  - コードの下の行は `tools/fix_code_links.py` が作るので手で書かない。取り込みを足したら `python3 tools/fix_code_links.py --page <id>` を流す。CI が `--check` で確かめる（#8・#62）
  - 本文から `` `snippets/<id>/<名前>` `` と書けば道具が GitHub へのリンクにする（#72）
  - 範囲の外で定義した補助関数や表（`binom`・`comb`・`fact` など）を使うときは、どの前計算かを本文に 1 文で書き、binomial-precompute の該当の節（`#fact-ifact`・`#composite-mod` など）へリンクする（#62）。手引きは planning/ にあるので、ページ名と anchor は文字で書いた（ほかの項目と同じ）
- 269 行（§9 の「プログラムは main と assert を持つ…」）：「完全なプログラムは提出用ではないので、入出力は手元で確かめるための自前の形でよい（問題の入力の形に合わせなくてよい。読者向けの説明は how-to-use#page-anatomy）」を足した
- 381 行（§15-5 の下の項目）：verify の問題はテンプレートがページ下部の「自作の確認」に出すので、発展の概要以外のページでは「Library Checker」の小見出しは verify にない問題か問題ごとの注意を書くときだけでよい。発展の概要の `#library` に書く問題名は judge.yosupo.jp へのリンクにする（名前だけだと 2 か所に並ぶ）（#53）

### 2. planning/interfaces.md

- 5 行（版）：§2 の verify の表示と、§7 の自作の確認・コードの下の行を足したことと Issue（#8・#53・#62）を書き足した
- 51 行（§2 の front matter の例）：`verify` に注「Library Checker の問題名。ページ下部の「自作の確認」に出る（§7）」
- 69 行（§2 の注の箇条書き。related の次）：verify は「自作の確認」の行に judge.yosupo.jp へのリンクとして出る。発展の概要では本文にリンクのある問題を出さない
- 152・153 行（§7 の表。「前提・次に読む・関連」の次）
  - 「自作の確認」：overrides/main.html と照らして書いた（関連の欄の後・知識マップのリンクの前に `p.kp-links__verify`、問題名は judge.yosupo.jp/problem/<名前>、「確かめ方」は library-design#verify、overview だけ本文の HTML に `judge.yosupo.jp/problem/<名前>"` がある問題を出さない、出す問題がなければ行もない）
  - 「コードの下の行」：テンプレートでも JS でもなく道具が本文に書くこと、2 行の段落の形（`p.kp-code-src`、見た目は kp.css）、mint の注記、続くフェンスは最後の下だけ、地の文のリンク、check.yml の `--check`

### 3. planning/design.md

- 153 行（§3 の front matter の例）：verify の注に「ページ下部の「自作の確認」の行と library-design の対応表に出る」
- 319 行（§5.1 の verify（D14））：「ページ下部の「自作の確認」の行（発展の概要では、本文にリンクのない問題だけ）と、library-design の対応表（生成）に出る（工程11、#53）」。対応表は gen_site.py の `verify-table`（library-design #verify-table）であることを確かめた
- 402 行（§6.3 の technique（水・青・黄））：「8. ACL では」の後に「9. 自作するとき（処理の流れの節の中に置く。ACL にある部品は折りたたみ、ACL と違う名前・返り値を書く。style-guide §4。工程11、#64）」を足し、後ろの 5 項目を 10〜14 に番号を振り直した。planning・CLAUDE.md・tools に §6.3 の番号を指す所はない（grep で確かめた）。置き場所は一覧の順ではなく処理の流れの節の中なので、括弧に書いた

### 4. docs/start/how-to-use.md（#page-anatomy）

own-library.md の提案 3 のとおり。code-links の担当が書いたコードの下の行の説明（228・230 行）は変えていない。

- 195 行（5. ページの下）：「前提・次に読む・関連の 3 つの欄、「自作の確認」の行、知識マップで…リンクがある。」
- 203 行（3 つの欄の箇条書きの後、種類の表の前）：段落を足した。「[Library Checker](../guide/glossary.md#library-checker) の問題で自作のコードを確かめられるページには、欄の下に「自作の確認」の行があり、その問題が並ぶ。問題名を押すと問題文へ、「確かめ方」を押すと[自作ライブラリの設計と動作確認](../guide/library-design.md#verify)の手順へ移る。発展の概要のページでは、本文にリンクのある問題（…）を重ねて出さない。」。このページで Library Checker が出るのはここが最初なので、手引き §7 のとおり用語集へリンクした（提案の文案の「（judge.yosupo.jp）」は用語集にあるので省いた）
- 226 行（「ACL では」の段落）：「データ構造そのもののページには…境界の小見出しがある。」の後に「ACL に同じ部品があれば、自作のコードは「自作するとき」の折りたたみに入れ、最初に ACL と違う名前・返り値を書いてある（違いの一覧は[自作ライブラリの設計と動作確認](../guide/library-design.md#acl-names)）。」を入れた（新しい段落にせず、自作の話の続きに置いた）

### 5. docs/start/notation.md（#code）

- 262 行：「完全なプログラムは手元でコンパイルと実行を確かめてある。」の後に「各コードの下のリンクから GitHub で見られる（[ページの構成と読み方](how-to-use.md#page-anatomy)）。」（code-links.md の提案 4 の文）

### 6. overrides/assets/css/kp.css

- 649〜655 行（末尾。own-library の担当の「自作の確認」の節の後）：節の見出しのコメントと `.md-typeset .kp-code-src { margin-top: -0.6em; font-size: 0.85em; color: var(--md-default-fg-color--light); }`（code-links.md の提案 1 の値のまま）

### 7. CI

- .github/workflows/check.yml
  - 2・3 行（冒頭の説明）：検査の一覧に「コードの下の行（fix_code_links.py --check）」を足した
  - 35〜38 行（pages の手順。check_pages.py の次）：`python tools/fix_code_links.py --check --stat`。`--stat` にしたのは tools/README.md の「ふつうの検査」の書き方に合わせたためで、差分の全文（流す前は 12,000 行ほど）でなくファイルごとの件数と「直せない」の行が出る。直し方のコメントを添えた
- .github/workflows/links.yml
  - 6・7 行（冒頭の説明）：除外の理由（先のファイルは fix_code_links.py --check が確かめる）
  - 37 行：`--exclude '^https://github\.com/yuukougun/kyopro-atlas/(blob|tree)/main/snippets([/?#]|$)'`。ほかの除外と同じく末尾を `([/?#]|$)` で区切った

## 確かめたこと

| 検査 | 結果 |
| --- | --- |
| `python3 tools/check_pages.py --page how-to-use -v`・`--page notation -v` | どちらもエラー 0・警告 0 |
| `python3 tools/check_pages.py`（作業ツリー全体） | エラー 0・警告 0 |
| `npx textlint docs/start/how-to-use.md docs/start/notation.md` | エラー 0。警告は how-to-use 4・notation 22 で、HEAD の版と規則・中身が同じ（how-to-use は行番号がずれただけ）。直した行に警告はない |
| `npx textlint`（planning の 3 ファイル。CI の対象外） | 足した行に残るのは「工程11」の全角と半角の間の空白の指摘だけで、planning の既存の書き方（HEAD でも style-guide 26・design 326 のエラーの大半が同じもの）に合わせた。文の長さと助詞の重なりの指摘は書き直して消した。interfaces は HEAD と同じ数 |
| check.yml・links.yml を PyYAML で読む | どちらも読める。pages の手順の並びも確かめた |
| lychee の除外の正規表現（Python の re で） | `blob/main/snippets/<id>/<名前>`・`tree/main/snippets`・`tree/main/snippets/<id>` は除外され、Issue の URL・`blob/main/tools/…`・ほかのリポジトリ・`snippets-weekly` は除外されない |
| `python3 tools/fix_code_links.py --check --stat`（作業ツリー。書かない） | 終了コード 1（直すべきファイル 328・追加 1127・地の文のリンク 48・直せない 0）。道具をまだ流していないためで、code-links の報告の数と同じ。how-to-use は直すところなし、notation は 87 行目の取り込みの下に 1 行入る |
| 作業用フォルダの写し（docs を写し、`fix_code_links.py --root <写し>` で書いた）の `check_pages.py --root`・`.venv/bin/mkdocs build --strict` | エラー 0・警告 0。ビルドは通る。how-to-use の新しい文とリンク（用語集の #library-checker、library-design の #verify・#acl-names）、notation の how-to-use#page-anatomy へのリンク、kp.css の規則がビルドした HTML にあり、リンク先の id があることを確かめた |
| 見た目（ヘッドレスの Chrome、幅 390px） | 写しのサイトの union-find の「自作するとき」の折りたたみを開いて、ライトとダークで撮った（作業用フォルダの `png/uf-open.png`・`png/uf-open-dark.png`）。折りたたみの中でも行がコードの塊のすぐ下に小さく薄い字で出て、続く段落との間は空き、ダークでも読める。囲みの外の見た目は code-links の担当の画像（css-360.png ほか）で確かめてある |
| `python3 tools/gen_site.py --check --diff` | 変わるのは llms.txt・graph.json・how-to-use の版の文字列だけで、前と同じ 3 ファイル（ほかの担当の updated による）。今回の変更で増えた生成物の差はない |
| main（af7ee6c）との重なり | main は style-guide（§2.1 の order・§4 の小項目・§10・§16）・interfaces（§3・§8）・how-to-use・kp.css を変えている。HEAD を元に、作業ツリーのファイルと main のファイルを `git merge-file`（作業用フォルダの写し）で重ねると、直した 8 ファイルとも衝突 0 |

## メインに判断してほしい点

1. **CI の手順を入れる時期**：check.yml の新しい手順は、道具を全ページに流す前は必ず落ちる（328 ファイル）。道具の書き込みと同じ pull request（できれば同じか後の commit）に入れる。how-to-use の説明も流した後の姿を書いている（code-links の判断 3 と同じ）
2. **§2.1 の例外の範囲**：指示は「コードの下の行」だったが、道具の書き込みには地の文の `snippets/…` のリンク（40 ページ・48 か所）も入るので、両方を例外にした（code-links の判断 1 の「道具の書き込み」に合わせた）。コードの下の行だけにするなら、22 行の「と地の文の `snippets/…` のリンク」を消す
3. **反映しなかった提案の一部**（指示の一覧になかったもの）
    - code-links.md の提案 2 のうち、「コードの直前・直後で『完全なプログラムは `snippets/…`』とだけ言う文は書かない」と、§12（報告の形）の検査に `fix_code_links.py` を足すこと。前者は今のページに 37 か所あり（提案 9 で後のバッチ）、今入れると既存のページが手引きに合わなくなる
    - graph-code.md の提案 2・3（§9 に、グラフの章の距離の INF を `1LL << 60` にそろえる決まりと、取り込む範囲で入力を読むなら直後に 1 を引く決まり）。指示の一覧に graph-code の項目がなかったので、手引きは変えていない
    - verify-code-links.md の推奨 1・2（how-to-use 228 行の「問題の入力の形ではない」→「問題の入力の形に合わせたものではない」、230 行の「要所の外にあるので」→「ふつうは要所の外にあるので」）。code-links の担当の文なので残した

## 提案（頼まれていないファイル）

1. **tools/README.md 85 行**（CI の説明）：「check.yml が `check_pages.py`・`fix_code_links.py --check --stat`・…」と、links.yml が snippets への GitHub のリンクを除外することを足す（今回の CI の変更で古くなる）
2. **interfaces.md §10（検査の表）**：「コードの下の行と地の文の snippets/… のリンクが最新か｜`tools/fix_code_links.py --check`」の行を足すと、CI と表がそろう（指示の範囲外なので触れていない）

## 使ったもの

- 作業用フォルダ（上）：`root/`（docs の写しに道具を流したもの。overrides・snippets は作業ツリーへのリンク）、`site/`（写しのビルド）、`png/`（見た目）、`head/`（HEAD の版。textlint の比較用）、`merge/`（main と重ねた写し）、`fcl-check-stat.txt`・`fcl-write-copy.txt`・`gen-diff.txt`
- 読んだ報告：code-links.md・own-library.md・graph-code.md・verify-code-links.md・verify-own-library.md、overrides/main.html の差分、tools/fix_code_links.py の使い方
- 新しいドメインは使っていない
