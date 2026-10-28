# verify-resources：resources の直しの検証（工程11 グループ cross-links・Issue #71）

作業ツリー：`kyopro-atlas-wt/cross-links`（ブランチ fix/cross-links、HEAD c5c263c、commit 前の差分）。日付：2026-10-29。対象は resources の担当が直した 46 ページ（type: overview のうち docs/dp/ の 5 ページを除くもの）と報告 resources.md。ファイルは直していない（この報告だけを書いた）。

## まとめ

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #71（担当の 46 ページ） | 直しが要る | 1（static-top-tree の ABC351 G の公式解説の行にリンクがない） |

リンクの URL と文字は、143 個すべてが同じページの参考の行と一字一句同じだった。サイト全体でも、同じ URL の題名は 1 つだけである。リンクのない行は 1 行だけで、資料の節の外は変わっていない。検査（check_pages・textlint・ビルド）もすべて通った。

## 直しが要る点

### 1. #71 static-top-tree の資料の節に、リンクのない行が 1 行残っている

- ファイル：`docs/tree/static-top-tree.md` 142 行目（`- ABC351 G の公式解説は、…AtCoder の解説ページなので、このサイトからはリンクしない。`）
- 理由：Issue の完了の条件は「51 ページの {#resources} のどの行にもリンクがある」である。担当の 46 ページの箇条書き 137 行のうち、この行だけにリンクがない。公式解説は atcoder.jp なので、参考に URL がない（§11）。解説へ直接リンクできないのは正しい。ただし同じページの 150 行目に例題の小見出し `### ABC351 G. Hash on Tree {#abc351_g}` がある。手引き §2.5 も、本文で問題に触れるときは例題の見出しへリンクするとしている。担当は報告の「判断してほしい点 2」で、この行をメインの判断に回している
- 直し方の案：「ABC351 G」を例題の小見出しへのリンクにし、最後の文を解説へのリンクだけを断る形に直す。例：`- [ABC351 G](#abc351_g) の公式解説は、ABC の想定解として Static Top Tree を初めて正面から扱ったもので、下の記事の多くが出発点にしている。AtCoder の解説ページなので、このサイトからは解説へリンクしない。`（「G」と「の」の間の空白は §7 のとおり）
  - メインがこの行を完了の条件の例外にすると決めるなら、この直しは要らない。その場合は pull request に例外を書く。手引き §16-1 に足す文（resources.md の提案 1）の「URL のない資料（書籍・atcoder.jp の解説）はリンクを付けずに書き」も、その決定にそろえる。上の案で直すなら、この文を「atcoder.jp の解説は、ページの例題の小見出しへリンクする」に改める

## 確かめたこと

### 完了の条件（担当の 46 ページ）

独自の突き合わせのスクリプト（作業用フォルダの `vcheck.py`。担当の verify.py は使っていない）で、46 ページの HEAD と今のファイルを読み比べた。

- 資料の節の箇条書きは 137 行、外部リンクは 143 個で、担当の報告の数と一致した。報告の表の 46 行（updated の行・資料の節の範囲・行数・リンク数）も、すべて実際のファイルと一致した
- 外部リンク 143 個のすべてが、同じページの参考の節に同じ「[題名](URL)」としてある。新しい URL はなく、atcoder.jp・codeforces.com の URL もない。入れ子の角かっこは数えて取り出し、題名の中の数式と、URL の中の丸かっこも扱った。行の 2 つ目・3 つ目のリンク（9 行）と、行の途中のリンク（partizan-games 142 行目）も確かめた。この 10 行は check_pages の §17-10 の検査に入らない
- 参考の行で「学ぶための資料」と添えた URL は、どれも資料の節からリンクされている
- リンク（外部・内部）のない箇条書きの行は、static-top-tree 142 行目だけである（上の直しが要る点 1）
- 内部リンクだけの行が 3 行ある。どれもリンクはあり、外部の資料ではないので妥当である
  - binomial-prefix-sum 123 行目：Mo's algorithm の節へのリンク
  - stirling-first 170 行目：練習問題の節へのリンク。参考の yosupo の GitHub の行は問題の定義なので、この行の資料（問題そのもの）とは別のものとみなした。この判断にも同意する
  - offline-dynamic-connectivity 123 行目：rollback-union-find へのリンク
- 箇条書きでない行は auxiliary-tree 125 行目の「次の 3 つがよい。」だけで、資料の行ではなく導入の文である。消した「（URL は参考の節にある）」に当たる文は、ほかのページの本文にも残っていない
- リンクのない資料は 2 つで、どちらも参考に URL がない
  - partizan-games 142 行目の書籍『Lessons in Play』。同じ行の Wikipedia「超現実数」はリンクになっている
  - static-top-tree の公式解説

### リンクの文字（§17-10 の題名の形）

- 143 個のリンクの文字は、同じページの参考の行の題名と一字一句同じである
- サイト全体の docs/ のすべての Markdown で、この 143 個の URL に付いた文字を集めた。節は問わず、どの URL も文字は 1 つだけだった（食い違いは 0）。他の担当が直している dp の 5 ページも含めて集めた
- 形は、132 個が「著者「題名」」（うち 8 個はリンクの文字の末尾に（Qiita）などを含む）である。残りの 11 個は参考の題名をそのまま写したもので、内訳は次のとおり
  - Wikipedia の 9 個（lgv-lemma 1・chromatic-number 2・matrix-tree-theorem 2・spanning-tree-advanced 2・two-sat 1・determinant 1）：「「Graph coloring」（英語版 Wikipedia）」のように題名の後ろに出どころを書く形
  - two-sat の ACL の 2 個：「ACL「2-SAT」のドキュメント（GitHub）」と「ACL の使用例 twosat_practice.cpp（GitHub）」
  - サイト全体で同じ URL に 1 つの題名なので、§17-10 を満たす。形をそろえるには参考の行も変える必要があり、この Issue の範囲の外なので、指摘にしない
- fft-ntt・multiplicative-function・stern-brocot の形を変えたこと（担当の「判断してほしい点 1」）は、戻さなくてよい。前の文字は参考の題名と違っていた（例：fft-ntt の「「行列で理解するFFT（競プロ向け）」」と参考の「51_24_11_「…」」、stern-brocot の「「Stern-Brocot Tree」」と参考の「Nyaan「Stern-Brocot Tree」（Nyaan's Library）」）。同じ URL に 2 つの題名があり、§17-10 に合わない状態だった。リンクが行頭になかったので、check_pages の検査に入らなかっただけである。Issue の「題名は §17-10 にそろえる」には、今の形が合う

### 差分の範囲とほかの箇所への影響

- HEAD との差分は、46 ページとも資料の節の中と front matter の `updated`（2026-10-22 → 2026-10-29）だけだった。参考の節・stage・ほかの本文は HEAD と同じで、共有のファイルと生成物も変わっていない
- check_pages（作業ツリーの版）：`--page` で 46 ページのエラーは 0・警告は 0。全ページでもエラーは 0・警告は 0
- origin/main の check_pages（この枝より 13 commit 新しい。#50 などの検査が増えた版）を作業ツリーに当てた。46 ページでエラーは 3・警告は 0 だった。3 件はどれも図の代替テキストの `[`（offline-dynamic-connectivity 51・hld 76・merge-process-tree 59 行目）である。origin/main で直し済み（c0b77a3）で、今回の直しとは関係がない
- origin/main の 46 ページを、この枝の差分と `git merge-file -p` で試しにマージした（作業用フォルダの写しで行った）。衝突は 0 だった。重なる 3 ページの `updated` は、両方が同じ 2026-10-29 に変えている
- textlint（46 ページ。HEAD の版も作業用フォルダに写して比べた）
  - エラーは 0 で、HEAD も 0
  - 資料の節の外の警告は 459 → 459、資料の節の中の警告は 15 → 24 だった
  - 増えたのは文の長さの 8 件（binomial-prefix-sum 121・continuous-probability 137・k-shortest-paths 118・spanning-tree-advanced 151・steiner-tree 133・linear-recurrence-fast 167・miller-rabin 160・tree-ratio-greedy 133）と、k-shortest-paths 118 の ja-no-successive-word の 2 件（hotman78 の題名の「！！！」）である。two-sat 145 の警告は消えた
  - どれもリンクの文字の題名の長さか題名の文字による警告で、§14-25 により残してよい。担当の報告と一致した
- hadamard-transform・linear-recurrence-fast で外した textlint-disable：外した後も 2 ページのエラーは 0 である。残る無効化は別名の行だけである
- §7 の空白：147 個のリンクの前後を調べ、直しが要る箇所は 0 だった。リンクの文字が半角で始まるときは「と [」・「は [」のように空白があり、「・[」には空白がない。リンクの文字はどれも全角（」か））で終わり、後ろに空白はない
- 箇条書きの句点：どのページも、直す前と同じ終え方のままである（句点のある行とない行が混ざったページはない）
- ビルド（`uv run mkdocs build -d <作業用フォルダ>/site`。-q なし）：警告は 0
- ビルドした HTML：46 ページの資料の節の li は 137 個、a は 147 個（外部 143・内部 4）だった。href と文字は Markdown と一致し、`](` の名残もない。次のものも正しいリンクになる
  - 入れ子の角かっこ：maspy「[Library Checker] …」・Heartlessly「题解 P2371 【[国家集训队]墨墨的等式】」・issue #1263「[問題案] 01 on Tree」
  - リンクの文字の中の数式：Nyaan「$\sum_{i}a^i f(i)$」。a の中に arithmatex が入る
  - 丸かっこを含む URL：Independent_set_(graph_theory)
- スクリーンショット（幅 390px、ライトとダーク）：wavelet-matrix（いちばん長い題名）・static-top-tree・lagrange-interpolation（リンクの中の数式）・spanning-tree-advanced（1 行に 3 つのリンク）を撮った。どれも長いリンクが折り返されて横にはみ出さず、ダークモードでも読めて、KaTeX も描かれる。作業用フォルダで http.server（ポート 47391）を立てて撮り、撮り終えてから止めた
- `gen_site.py --check --diff`：変わるのは llms.txt・graph.json・how-to-use.md の版のハッシュだけで、メインが作り直す
- 本文から資料の節への `[学ぶための資料](#resources)` は、anchor が変わらないので切れない。本文で「学ぶための資料の Nyaan 氏の解説」（lagrange-interpolation 139 行目）、「学ぶための資料の rsm9 氏の記事」（segment-tree-beats 103 行目）と指している先も、リンクの行として残っている。資料の節を読む道具は check_pages のほかにない

### 説明の文

- 137 行の前後を読み比べた。各リンクは、元の文が名前で挙げていた資料（著者とコンテスト・問題）と同じものを指している
  - 例：ikatakos の ABC235 → `0115_abc235`、kmjp の ABC235 G → 「G - Gardens」、けんちょんの ARC084 D → drken「ABC 077 D - Small Multiple (ARC 084 D) …」、kmjp の ABC213 H・ABC352 G → それぞれの記事
- 説明は主語をリンクに移して「：」の後の述語にしただけで、新しい事実は足されていない
- advanced-geometry の 1 行 → 5 行の分割も、元の文（各記事が手順と計算量をまとめている、半平面交差の記事の詳しい点）を分けたものである
- 言語・種類の注記は残っている。リンクの文字に「英語版 Wikipedia」などがある行に、（英語）は重ねていない

### 担当の「判断してほしい点」への意見

1. 行の形：今の「- [著者「題名」](URL)：」でよい（上の「リンクの文字」の節）。dp の 5 ページとの書き方のそろえ方は、別の担当の検証とあわせてメインが決める
2. ABC351 G の公式解説の行：直しが要る点 1 のとおり、例題の小見出しへのリンクを足すのを勧める
3. trap.jp：origin/main の手引き付録 B に 2026-10-29 の追記がある。check_noai で記事 post/2861 も HTTP 200 で取得でき、noai・noimageai がないことを確かめてある。origin/main を取り込めば、static-top-tree の noya2 の記事へのリンクに残る問題はない

## 範囲の外（直しが要る点に入れない）

- Issue の「やること」の 2 つ目（手引き §16-1 に足す）は、共有のファイルなのでメインが反映する。担当の提案 1 の文案は今回の直し方と合っている（URL のない資料の書き方は、上の直しが要る点 1 の決定にそろえる）
- 参考の題名の著者名に「けんちょん「…」」（サイト全体で 16 か所。担当の範囲では online-convolution 122 行目）と「drken「…」」（692 か所）の揺れがある。直す前からの参考の書き方で、URL ごとの題名は 1 つなので §17-10 には当たらない
- docs/dp/ の 5 ページは別の担当の範囲で、ここでは見ていない（題名の一致を調べるときの対象には含めた）

## 使った道具（作業用フォルダ /tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/cross-links/verify-resources）

- `vcheck.py`：資料と参考の突き合わせ、サイト全体の題名、差分の範囲、リンクのない行
- `forms.py`：リンクの文字の形と、サイト全体の別の文字
- `htmlcheck.py`：ビルドした HTML の li と a
- `tlcmp.py`：textlint の HEAD と今の版の、節の中と外の比較
- `maintools/check_pages.py`：origin/main の check_pages を、ROOT だけ作業ツリーに替えて写したもの
- スクリーンショット：`*-light.png`・`*-dark.png`
- Web の取得：0 回（atcoder.jp・codeforces.com を含む）
