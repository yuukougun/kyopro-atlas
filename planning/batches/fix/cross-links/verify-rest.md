# verify-rest の報告（バッチ cross-links）

- 検証したもの：前の検証（verify-thinking・verify-resources）の後に入った 2 つの直し
  - #70：docs/comb/permutation-cycles.md 97 行目（#vs-adjacent）の隣接 swap の証明を、持ち主 ds/inversion-number#adjacent-swaps への要点とリンクに縮めた
  - #71：docs/tree/static-top-tree.md 142 行目（{#resources}）の「ABC351 G の公式解説」の行を、ページの中の例題 #abc351_g へのリンクにした
- Issue：#70・#71（`gh issue view` で読んだだけ。コメント・編集・クローズはしていない）
- 作業ツリー：/home/yuuki/projects/kyopro2/kyopro-atlas-wt/cross-links（ブランチ fix/cross-links、HEAD c5c263c、commit 前の差分）。書いたのはこの報告だけで、ほかのファイルは直していない。git は読むだけ
- 作業用フォルダ：/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/7a638398-7759-4637-95c7-6739e8d52414/scratchpad/fix/verify-cross-links-rest
- Web の取得：0 回（atcoder.jp・codeforces.com を含む）

## 結果

| Issue | 判定 | 直しが要る点 |
| --- | --- | --- |
| #70 重なる説明の持ち主 | 合格 | 0 |
| #71 学ぶための資料の各行のリンク | 合格 | 0 |

- **#70**：完了の条件を満たす。3 つの考え方のどれでも、証明を書くページは持ち主の 1 つである。ほかのページは持ち主の節へリンクしている
- **#71**：完了の条件を満たす。51 ページの {#resources} の箇条書き 152 行に、リンクのない行は 0 行である（自分のスクリプトで数えた）
- `python3 tools/check_pages.py`（全体、353 ページ）：エラー 0・警告 0
- 2 つの Issue とも、「やること」の手引きへの 1 行（#70 は §5、#71 は §16-1）は、作業ツリーにも origin/main にもまだない。どちらも完了の条件の外にあり、担当の報告では提案になっている。メインがバッチの終わりに反映する（下の「メインへの申し送り」）

## #70：permutation-cycles の直しと、3 つの考え方の持ち主

### 直しの中身

- 差分は 97 行目と front matter の `updated`（2026-10-22 → 2026-10-29）だけである。sections・related・stage は変わっていない
- 差分の行は、thinking の担当が用意した patch（scratchpad/fix/cross-links/fixup-thinking/permutation-cycles.patch）と同じである（`diff` で比べた）
- 直した後の 97 行目は次の 3 文からなる
  1. 結論：転倒数へのリンク（`../ds/inversion-number.md#adjacent-swaps`）と定義
  2. 理由 1 文：「隣接 swap 1 回で転倒数はちょうど 1 だけ変わり、ソートされていなければ隣り合う転倒した組を swap して 1 減らせるからである。」
  3. 任意の swap との関係：このページの持ち分
- 消えたのは、下限と作り方を 2 文で書いた証明と `$P_i > P_{i+1}$` である。表（99〜103 行目）・読み分けの段落（105 行目）・偶奇の段落（107 行目）・anchor #vs-adjacent は残っている

### 事実と書き方

- **理由の文は正しい**
  - 順列では値が相異なるので、隣接 swap 1 回で転倒数はちょうど ±1 変わる。よって転倒数より少ない回数ではソートできない
  - ソートされていなければ $P_i > P_{i+1}$ となる隣の組がある。それを swap すると転倒数はちょうど 1 減るので、転倒数の回数で足りる
  - 2 つで最小回数＝転倒数になる。持ち主の 93〜96 行目の 2 つの事実と同じ内容で、食い違いはない
- **表の値は計算し直して合っていた**（表は変わっていない）
  - $(3,2,1)$：巡回 2・任意 1・転倒数 3
  - $(2,3,4,1)$：巡回 1・任意 3・転倒数 3
  - $(4,3,2,1)$：巡回 2・任意 2・転倒数 6
  - どの行も任意の swap の回数 ≤ 転倒数で、偶奇もそろう
- **ほかの持ち主でないページと同じ形になった**：「理由 1 文と #adjacent-swaps へのリンク」の形である。同じ形のページは patterns/permutation 103・thinking/reformulation 142・thinking/invariant 101・comb/permutation-parity 74 である
- **§7**：本文で「転倒数」が最初に出るのは 97 行目である（95 行目は見出し、26 行目は front matter）。リンクはここに置かれている。本文から inversion-number へのリンクはこの 1 つだけである
- **#vs-adjacent を指す側も食い違わない**：patterns/permutation 110 は「違いの表」を、guide/method-comparison 384 は「隣接 swap との違い」を指している。どちらも残した表と段落を指しているので、文と食い違わない。method-comparison 384 は持ち主 #adjacent-swaps にも別にリンクしている

### 完了の条件（3 つの考え方のそれぞれで証明は 1 ページ、ほかは持ち主の節へリンク）

担当の表を前提にせず、docs/ を grep して読み直した。生成物の docs/index/・docs/lists/・llms.txt は除いた。

| 考え方 | 証明のある場所（持ち主） | 持ち主でないページの書き方 |
| --- | --- | --- |
| 1 つを固定して相手を速く数える | 役割ごとに 1 か所ずつ。何を固定するかと、重複・漏れがない理由は thinking/fix-variable#fix-middle（51〜59 行目）。相手が連続した範囲になる理由は basics/binary-search#fix-one-side（130〜132 行目）。分け目の手順と空の側の初期値は basics/brute-force#half-enumeration（116〜124 行目） | 1 文とリンクの形：binary-search 136 → fix-variable#fix-middle、patterns/subsequence-and-substring 142 → #fix-middle、fix-variable 124 → binary-search#fix-one-side、fix-variable 129 → brute-force#half-enumeration、brute-force 128 → fix-variable#speed-up。同じ理由を 2 か所で書いているところはない |
| 区間加算の最小回数＝正の差分の和 | basics/difference-sequence#min-operations（83 行目に下限と作り方、85・87〜90 行目にほかの型） | reformulation 138：結論と #min-operations へのリンク。patterns/interval 188：下限の理由 1 文と #min-operations へのリンク。imos 123・219：リンクだけ。invariant 142 は「2 か所だけを変える」の話で、#to-point-operations を指す（最小回数の話ではない）。作り方の証明の語（「本始め」「本を終え」「終える本数」）は 83 行目にしかない |
| 隣接 swap の最小回数＝転倒数 | ds/inversion-number#adjacent-swaps（91〜96 行目） | 理由 1 文と #adjacent-swaps へのリンク：reformulation 142・invariant 101・patterns/permutation 103・permutation-parity 74・permutation-cycles 97（今回）。下限と作り方の 2 方向を書くページは、持ち主の外にない |

隣接 swap の考え方の grep の方法と、そのほかの行：

- 方法：「転倒数」「転倒し」「転倒した」「inversion」を含む行のうち、「隣」「swap」「交換」「バブル」「入れ替え」も含む行を全部読んだ
- 理由を書かない言及（結論だけ）：
  - divide-and-conquer 231（練習の方針）
  - permutation-parity 135・153
  - method-comparison 458（確認問題の答え）
  - reverse-index-signs 352（signs からの表）
- invariant 111（確認問題「止まることの証明」の答え）は、単調量で停止を示す最小の例である。最小回数の証明ではない。前の検証と同じく、thinking の持ち分として残してよい

前の検証の指摘 1 件（permutation-cycles 97）は解消した。この 1 か所が、完了の条件を満たしていなかった最後の場所である。

## #71：static-top-tree の 1 行と、51 ページの数え上げ

### 直しの中身

- 142 行目：`- [ABC351 G](#abc351_g) の公式解説は、…下の記事の多くが出発点にしている。AtCoder の解説ページなので、このサイトからは解説へリンクしない。`
  - 前の検証の案と同じである。最後の文を「解説へリンクしない」に改めたので、リンクのある行と文が食い違わない
  - 143〜146 行目と `updated` は、resources の担当の直し（検証済み）のままである
- 行き先：150 行目に `### ABC351 G. Hash on Tree {#abc351_g}` がある。ビルドした HTML にも `id="abc351_g"` が 1 つある
- 手引き §2.5 の「本文で触れるときは例題の見出しかページへリンクする」に合う。リンクはページの中の anchor で、atcoder.jp の URL ではない。そのため「囲みの外の問題リンク」の検査には当たらない
- §7：リンクの文字は半角の「G」で終わる。その後の「の」との間に空白がある（`](#abc351_g) の`）
- ほかのページの書き方とも同じである（例：graph/graph-modeling 77 の `[ABC256 E](../graph/functional-graph.md#abc256_e)`）

### 51 ページの数え上げ（完了の条件）

スクリプト：scripts/count_resources.py（作業用フォルダ。前の担当の verify.py・vcheck.py は使っていない）。

- 数え方：`## 学ぶための資料 {#resources}` から次の `##` までを読んだ
  - 箇条書きの行は、続きの行と合わせて 1 行と数えた
  - インラインのリンクは、入れ子の角かっこと URL の中の丸かっこを数えて取り出した
  - 箇条書きでない行と HTML のコメントは別に出した
- 対象：見出しのあるページは 51 で、front matter が type: overview のページ（51）とちょうど一致する。見出しの形はすべて定型どおりである
- 結果（今の作業ツリー）：51 ページ・箇条書き 152 行・外部リンク 159 個で、**リンクのない行は 0** だった
  - 152 行の内訳は、resources の担当の 46 ページが 137 行、dp の 5 ページが 15 行である
  - 159 個の内訳は、46 ページが 143 個、dp の 5 ページが 16 個である
  - どちらも、2 つの担当の報告と前の検証の数に合う
- 内部リンクだけの行は 6 行ある。どれもリンクはある
  - static-top-tree 142（#abc351_g。今回の行）
  - binomial-prefix-sum 123（mo-algorithm#two-prefixes）
  - stirling-first 170（#practice）
  - offline-dynamic-connectivity 123（rollback-union-find）
  - dynamic-dp 154（matrix-power・segment-tree-monoids#matrix）
  - dynamic-dp 157（static-top-tree#resources）
- 箇条書きでない行：auxiliary-tree 125 の導入「次の 3 つがよい。」と、cht 156・160 の textlint のコメントだけである。どちらも資料の行ではない
- **数え方が正しいことの確かめ**：同じスクリプトを直す前の HEAD に流した（`--rev HEAD`）
  - リンクのない行のあるページは 48 で、リンクのない行は 135 だった
  - リンクのあった 3 ページは fft-ntt・multiplicative-function・stern-brocot だった
  - これは Issue の背景（「51 ページのうち 48 ページ」「リンクがあるのは math/fft-ntt・multiplicative-function・stern-brocot だけ」）と一致する
- **main とマージした後も変わらない**：main（da9b5c2）にこの枝の 64 ファイルを 3 方向でマージした写しでも、51 ページ・152 行・リンクのない行 0 だった（下の検査）

## 検査（書き換えない検査）

- **check_pages**
  - `python3 tools/check_pages.py`（全体、353 ページ）：エラー 0・警告 0
  - `--page permutation-cycles,static-top-tree -v`：エラー 0・警告 0
  - 検査がこの 2 つのリンクを見ていることも確かめた。作業用フォルダの写しで anchor を `#abc351_x`・`#adjacent-swapz` に壊すと、「リンク先に anchor がない」のエラーが 2 件出た（同じページの中の anchor と、別のページの anchor の両方）
- **main の新しい check_pages**
  - この枝より新しい main の版（952a4e5 で #50 などの検査が増えた）を、`--root` で作業ツリーに向けて流した。2 ページはエラー 0・警告 0 だった
  - 試しのマージ：作業ツリーで変わった docs/ の 64 ファイルを、基点 c5c263c・この枝・main（da9b5c2）の 3 方向で `git merge-file` した（作業用フォルダの merged-tree/）
    - 衝突は 0 だった
    - マージした写しの全体で、エラー 0・警告 0 だった
    - main は c5c263c の後に permutation-cycles・static-top-tree を変えていない。マージ後の 2 ファイルは、この枝のものと同じである
    - 差分をそのまま `git apply` すると、main 側でも変わった 4 ファイル（difference-sequence・offline-dynamic-connectivity・hld・merge-process-tree）で当たらない。マージでは衝突しない
- **fix_problems**：`python3 tools/fix_problems.py --check --page permutation-cycles,static-top-tree` で、直すべき行は 0 だった
- **textlint**（`npx textlint`、HEAD の写しと比べた）
  - 2 ファイルとも、エラー 0 である
  - 警告は直す前と同じ行・同じ件数である。permutation-cycles は 78 行目の 2 件と 130 行目の 1 件、static-top-tree は 31・47・169・183 行目の 4 件である
  - 直した行（97、142〜146）に警告はない
- **ビルド**：`uv run mkdocs build --strict -q -d <作業用フォルダ>/site` は終了コード 0 だった。ログにある「Warning」は Material の告知（MkDocs 2.0）で、ビルドの警告ではない
  - ビルドの前後で、作業ツリーの git status は変わっていない
  - 生成された HTML の href は、`../../ds/inversion-number/#adjacent-swaps` と `#abc351_g` になる。行き先の id はどちらも 1 つずつある
- **数式**：作業用フォルダで http.server を立てて調べた（127.0.0.1:41837。使い終えて止めた）
  - ヘッドレスの Chrome で描画後の DOM を出し、katex-error は 0 だった
  - arithmatex の数と katex の数は、どのページでも一致した（permutation-cycles 182／182、static-top-tree 120／120、inversion-number 233／233）
  - 直した段落の中の数式も描かれている（97 行目は 2 つ、資料の節は 1 つ）
- **撮影**（幅 390px、ライトとダーク。shots/ に置いた）
  - 撮ったもの：pc-vs-adjacent-light.png・pc-vs-adjacent-dark.png・stt-resources-light.png・stt-resources-dark.png
  - リンク・数式・折り返しは崩れていない。ダークは slate で描かれ、ページの横幅は 390 のまま（scrollWidth 390）である
  - #vs-adjacent の表の右端の列は、表の中の横スクロールに入る。表は直す前と同じである
  - ほかの検証役への注意：CLI の `--screenshot` に `#fragment` を付けた URL を渡すと白紙になった。そのため、CDP で要素の位置を取って切り出す scripts/shot.mjs で撮った。使い終えた Chrome は残っていない
- **gen_site**：`python3 tools/gen_site.py --check --diff` で変わると出るのは、docs/llms.txt・overrides/assets/data/graph.json・docs/start/how-to-use.md の版のハッシュの行だけである。メインが作り直す
- **流していない検査**：コード片・図・動く図の差分はない（git status は docs/*.md と報告だけ）。そのため、check_snippets・check_svg・`node --test` は流していない

## 任意（直さなくてよい）

1. **転倒数の結論だけを書く行のリンク先**：次の 2 行は、隣接 swap の結論を述べつつページの先頭を指している。証明は書いていないので、完了の条件の「証明を書くページが 1 つ」には反しない。`#adjacent-swaps` を指すと、「ほかのページはその節へリンク」に文字どおり合う
   - basics/divide-and-conquer 231「交換回数は転倒数に等しい（[転倒数](../ds/inversion-number.md)）」
   - comb/permutation-parity 153「隣接 swap は[転倒数](../ds/inversion-number.md)で求める」
   - basics/brute-force 113（→ binary-search の先頭）も同じで、前の検証の任意の項目のまま残っている
2. **dynamic-dp 157 行目の空白（§7）**：「Static Top Tree は[Static Top Tree のページ](…)」は、全角の「は」と、半角で始まるリンクの文字の間に空白がない。直す前の HEAD からある行で、今回の直しではない。textlint は文字列がリンクの境目で分かれるので見つけない。直すなら「は [Static Top Tree のページ](…)」にする

## メインへの申し送り

- **#70**：完了の条件を満たしたので、pull request は `Closes #70` にできる
  - 「やること」の 3 つ目（手引き §5 に basics と thinking の書き分けを 1 行足す）はまだ入っていない
  - thinking.md の提案 1 を、バッチの終わりに反映する
- **#71**：完了の条件を満たしたので、`Closes #71` にできる
  - 「やること」の 2 つ目（手引き §16-1）は resources.md の提案 1 として残っている
  - 提案 1 の文は、今回の決め方にそろえて反映する。今の文案は「URL のない資料（書籍・atcoder.jp の解説）はリンクを付けずに書き」である。改め方の案は次のとおり
    - 「atcoder.jp の解説は、ページの中のその問題の例題（練習）の小見出しへリンクし、解説へはリンクしないと書く」
    - 「書籍のように URL のない資料は、同じ行の別の資料かサイトの中の節へのリンクを添える」
  - 書籍の例は partizan-games 142 で、書籍と Wikipedia が同じ行にあり、行にはリンクがある
- 生成物（llms.txt・graph.json・how-to-use.md）は、版のハッシュだけが変わる。gen_site で作り直す

## 使った道具（作業用フォルダ）

- scripts/count_resources.py：資料の節の行ごとのリンクの数え上げ。`--rev` で git の版も読む
  - 結果：resources-now.txt（今の作業ツリー）・resources-head.txt（HEAD）・resources-merged.txt（main とのマージ後）
- scripts/shot.mjs：CDP で要素の位置から撮る（幅 390px、ライトとダーク）
- tree/：anchor を壊して check_pages を試した写し
- merge3/・merged-tree/：main との 3 方向のマージの写し
- dom/：描画後の DOM
- shots/：スクリーンショット
- tl-*.txt：textlint の HEAD と今の結果
- gen-diff.txt：gen_site の差分
- 道具の呼び出し：およそ 50 回。Web の取得は 0 回
