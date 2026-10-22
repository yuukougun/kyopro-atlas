# 工程10 洗い出し：道具・台帳・生成物・共有ファイル

- 観点：(1) 生成物の古い文言（準備中・stub・骨格）、(2) 題名に角かっこを含む問題を読めない正規表現、(3) 台帳の判断待ちの 6 件と、台帳の pages と本文の食い違い、(4) 用語集の正規形の表と prh.yml、(5) README・tools/README・progress.md の古い記述、(6) 参考の節の URL のうち付録 B にないドメイン
- 調べ方：スクリプトは一時置き場 `/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/s10/` に置いた（`ledger_vs_body.py` 台帳の pages と本文の問題の囲み、`summary_cmp.py` 本文の要約と台帳の summary、`prh_cmp.py` 用語集の表と prh.yml、`domains.py` 本文の URL のドメインと付録 B、`noai.json` check_noai の結果、`textlint.txt` textlint の全件）。判断の要るもの（判断待ちの 6 件、関係するページの本文）は読んで確かめた。atcoder.jp・codeforces.com は開いていない
- 現状の道具の結果：`check_pages.py -v` エラー 0・警告 0、`fix_problems.py --check` 直すべき行 0、`gen_site.py --check` 最新、textlint の prh の指摘 0（警告はほかの規則だけ 4415 件）。`build_ledger.py --check` は終了コード 1（目次の凍結で台帳にだけある問題 77・役割の違い 69。CI は警告だけにしてある）
- 各行の形：ページ ｜ 行の目安 ｜ 問題 ｜ 根拠 ｜ 直し方
- 問題がなかったこと：本文の問題の囲みの行はすべて台帳の pages にあり、役割も一致（逆向きの「本文にあって台帳にない」は 0）。囲みの外の atcoder.jp のリンクと、atcoder.jp の解説（editorial）へのリンクは 0。glossary の表の「直す表記」はすべて prh.yml のどれかの規則が拾い、「別の書き方」と正規形を誤って直す規則はない。付録 B にない 45 のホスト（scrapbox.io・note.com を含む）と trap.jp の 69 URL の check_noai はどれも noai・noimageai の指定なし（取得できなかった 4 件は下に挙げた）

## shared

### (1) 生成物と共通の部品の古い文言

- docs/index.md ｜ 5〜6 ｜ ホームの info「制作中」が「多くのページは『準備中』で、冒頭の要点だけを載せている。…本文はまだない」のまま。今は 353 ページすべて draft（準備中 0） ｜ check_pages の段階別「draft 353」、llms.txt「準備中 0」 ｜ 生成ブロックの外の手書きなので、メインが文を直す。例：「全ページに本文がある。検証と仕上げを進めている」（README 6 行目と同じ内容）。info を消すかはユーザーに確かめる
- tools/gen_site.py（docs/index/*.md の 15 ファイル） ｜ gen_site.py 529、各 docs/index/<field>.md の 12 行目 ｜ 詳細索引の冒頭が「stub（準備中）のページは要約と前提しかなく、節の見出しもまだない」と、ないものを説明している ｜ 準備中 0 ｜ stub のページが 1 つもないときはこの文を出さない（`if any(p.stub for p in ps)`）
- tools/gen_site.py（docs/llms.txt） ｜ gen_site.py 507・512、llms.txt 6・9 行目 ｜ 「ページ数：353（準備中 0）」と、段階の説明の「draft は執筆中」。全ページが書けた今、claude.ai の解説役が「draft＝書きかけ」と読むおそれがある ｜ 段階別 draft 353。claude/explain.md 41 行目は stub だけを根拠にしないと決めている ｜ 準備中が 0 なら括弧を出さない。STAGE_JA（86 行目）と llms.txt の説明の draft を「本文あり（未検証）」のような言い方にする（reviewed＝検証済み と対になる形）
- tools/gen_site.py（`fields` ブロック → docs/start/how-to-use.md 66 行目の表） ｜ gen_site.py 604〜605 ｜ 分野の一覧の表に「準備中」の列があり、15 行すべて 0 ｜ 同上 ｜ 準備中の合計が 0 のときは列を出さない（あるいは列を「段階」の集計に替える）。how-to-use の本文（下の ## start）と一緒に直す
- tools/gen_site.py（分野の入口 docs/<field>/index.md） ｜ gen_site.py 371・436 ｜ 「（準備中）」の印と「（準備中 n）」は n が 0 なら出ない作りで、今の生成物には出ていない ｜ 生成物を grep して 0 件 ｜ 直さなくてよい（記録だけ）
- overrides/main.html・overrides/assets/js/map.js・kp.css ｜ main.html 102〜105、map.js 743 ｜ 「準備中」の帯・印は stage が stub のときだけ出る作りで、今は出ない ｜ 同上 ｜ 直さなくてよい。帯の文（「骨組みだけで、本文はまだない」）は将来 stub を足すときのために残してよい
- docs/start/how-to-use.md の front matter ｜ FM 24 ｜ sections に「『準備中』のページ」（anchor stub）が残る。生成の llms.txt・docs/index/start.md にもこの節が載る ｜ 下の ## start ｜ ## start の直し方に合わせて節を消すか短くし、sections も直す。anchor stub へのリンクは main.html 105 行目（howto_url）とページ内 188 行目にある

### (2) 題名に角かっこを含む問題を読めない正規表現

- tools/check_pages.py ｜ 101〜103（PROBLEM_LINE_RE） ｜ label を `[^\]]+` で読むので、`- [ABC411 E. E [max]](https://atcoder.jp/contests/abc411/tasks/abc411_e)（diff 1400）：…` が「行の書式が違う」になる（手元で再現：match が None） ｜ batches/b6/APPLIED.md 83 行目、b5/decisions.md の最後の行 ｜ label を `(?P<label>(?:[^\[\]]|\[[^\[\]]*\])+)` にする（手元で `ABC411 E. E [max]` を読めることを確かめた）。gen_site.py は check_pages の read_page を使うので、これ 1 か所で生成物も直る
- tools/fix_problems.py ｜ 32（LINK_TAIL_RE） ｜ 同じく label を `[^\]]*` で読むので、直す対象の行として要約を取り出せない（`--check` が「問題 ID か要約が読めない」になる） ｜ 同上 ｜ `^- \[(?:[^\[\]]|\[[^\[\]]*\])*\]\(…` に替える。BARE_RE（33 行目）は角かっこを使わないので直さなくてよい
- tools/check_pages.py ｜ 759（LINK_RE） ｜ 本文のリンクの検査は 1 段の入れ子を許す形で、`[ABC411 E. E [max]](…)` を 1 つのリンクとして読める ｜ 正規表現を読んで確かめた ｜ 直さなくてよい（記録だけ）
- data/problems.yaml の題名 ｜ — ｜ 角かっこを含む題名は abc411_e の 1 問だけ。ほかに Markdown で意味を持つ字を含む題名（`#(subset sum = K)…` abc321_f、`M<=ab` abc296_d、`rng_10s` agc026_b、括弧の題名など 17 問）は、今の正規表現で読めている（check_pages エラー 0） ｜ 台帳の全 1255 題名を走査 ｜ 正規表現を直したら、試験として abc411_e の行を一時ファイルに置いて check_pages・fix_problems を通す。ページへの追加は下の ## comb

### (3) 台帳：判断待ちの 6 件（b5/summary/ledger-result.md・b5/decisions.md 35 行目）

- data/problems.yaml agc002_d ｜ 台帳の項目 ｜ 本体の summary（「最初の t 本の辺だけを使ったとき…最小の t」）が 3 ページ（parallel-binary-search の例題、merge-process-tree・partially-persistent-union-find の練習）の本文の要約と一致しているのに、alternatives に merge-process-tree 向けの別の summary（「番号 i 以下の辺だけを使って…最小の i」）が残る。partially-persistent-union-find 向けの alternatives は summary が本体と同じで、approach だけが違う ｜ 本文 3 か所を読んで確かめた（merge-process-tree.md 149・partially-persistent-union-find.md 139・parallel-binary-search.md 135） ｜ summary は本体の 1 案に決める（本文がすでにそろっている）。merge-process-tree の alternatives の summary を本体と同じにして approach だけを残す。これで「2 案のどちらか」の判断は閉じる
- data/problems.yaml abc311_h ｜ 台帳の項目、docs/tree/static-top-tree.md FM 4・71・169・174 ｜ static-top-tree の練習のまま。aliases の「重軽再帰 DP」は Static Top Tree の別名ではない（b5 other.md 36・76 行目） ｜ 本文の 71 行目と方針（174 行目）が「更新のない木 DP に重い子を使う重軽再帰 DP の問題」と説明済みで、ページの中で区別は付いている ｜ 練習は static-top-tree に残す（移すと tree-dp-square に節と方針を書き足すことになり、diff 3605 は黄の帯から遠い）。aliases の「重軽再帰 DP」は外し、用語の索引から引けるよう、本文 71 行目の語に用語集か #heavy-path-dp を当てる。決めたことを decisions に残す
- data/problems.yaml abc458_g ｜ 台帳の項目、docs/dp/slope-trick.md FM 21、docs/dp/monge.md 197 ｜ 台帳では monge の練習だけだが、slope-trick の frequency_evidence が「recent 1（abc458_g）」を数えている ｜ data/recent-abc.yaml 302〜310 行目が pages に slope-trick#breakpoints を持ち、ikatakos 氏の記録で Slope Trick の形の実装と確かめてある。台帳の approach も「傾きの列（Slope Trick に近い持ち方）」と書く ｜ frequency_evidence は recent-abc.yaml が正なので残す。台帳の pages に slope-trick（力試し。diff 2831 は発展の帯）を足し、slope-trick のページに力試しの囲みと方針を足す（執筆の作業）。summary は ledger-result の注のとおり仮の文なので、ikatakos 氏の記録で問いを確かめて書き直す
- data/problems.yaml keyence2019_e ｜ 台帳の項目、docs/graph/spanning-tree-advanced.md 72・159 ｜ spanning-tree-advanced は参考の節に drken 氏の keyence2019_e の記事を挙げ、72 行目で「辺の候補を O(N log N) 本に減らしてクラスカル法」に触れるのに、問題の行がない。台帳では centroid-decomposition・divide-and-conquer の力試し ｜ 本文と台帳を突き合わせた。Borůvka 法での手順は drken 氏の記事が触れるだけで裏付けにならない（ledger-result） ｜ spanning-tree-advanced に練習（発展の帯、diff 2623）で足し、台帳の pages と alternatives（approach は候補の辺を絞るクラスカル法。Borůvka 法は書かない）を足す。参考の記事はその行の出典になる
- data/problems.yaml abc189_c ｜ 台帳の項目、docs/ds/monotonic-stack.md 236（練習の囲み） ｜ 台帳の pages に monotonic-stack の練習があるのに、本文にない（interval の練習にはある） ｜ ledger_vs_body.py。monotonic-stack の #histogram の節（110 行目〜）がちょうどこの型 ｜ monotonic-stack の練習に足す（N が小さく O(N^2) でも通ること、単調スタックで O(N) にできることを方針に書く）。足さないなら台帳の pages から monotonic-stack を外す
- data/problems.yaml abc197_c ｜ 台帳の項目、docs/basics/bit-full-search.md 210（練習の囲み） ｜ 台帳の pages に bit-full-search の練習があるのに、本文にない（xor の練習にはある） ｜ 同上。approach は「区切り方 2^(N−1) 通りを bit 全探索」でページの中心そのもの ｜ bit-full-search の練習に足す（区切りの位置を bit に対応させる方針）

### (3) 台帳：pages にあるのに本文の囲みにない問題（上の 2 件を除く 37 件）

各ページの見出しの下に分けて挙げた（ページごとの直し方はそちら）。まとめ：

- data/problems.yaml ｜ — ｜ 台帳の pages の（問題, ページ）のうち 39 組が本文の問題の囲みにない（abc189_c・abc197_c を含む）。`fix_problems.py --check` は本文 → 台帳の向きしか見ないので検出しない ｜ ledger_vs_body.py ｜ 各組について「本文に足す」か「台帳の pages から外す」かを決める。うち 3 問（abc458_e・abc479_d・abc479_e）は status が未確認で、本文に載せないことが note に書いてあるので、そのままでよい
- tools/fix_problems.py ｜ --check ｜ 逆向き（台帳で役割を持つのに本文にない）を検出できない ｜ b5/summary/other.md 118 行目の提案 ｜ `--check` に「台帳の pages にあって本文にない」を警告として足す。status が未確認の問題は数えない

### (3) 台帳の summary の仮の文と、本文の要約との食い違い

- data/problems.yaml ｜ 20 項目 ｜ summary が「（執筆時に確かめる）」かそれを含む問題が 20 ある。うち 15 問（16 か所）は本文がすでに自分の要約を持っている：abc459_f（difference-sequence）・abc469_e（fractional-binary-search）・abc473_e（prefix-sum-counting）・abc450_g（expectation-of-square）・abc470_f（multinomial-coefficient・permutation-parity）・abc412_f と abc470_e（optimal-strategy-expectation）・abc404_f（partition-number）・abc476_g（lis）・abc479_f（inversion-number・reformulation）・abc476_f（manhattan-chebyshev）・abc445_g（konig-theorem・project-selection）・abc432_c（integer-division）・abc468_e（contribution）・abc466_f（reverse-thinking） ｜ summary_cmp.py。手引き 58 行目（要約を書いたら台帳の修正を提案する）の反映もれ ｜ 本文の要約を台帳の summary に写す（2 ページにある問題は文をそろえる）。残りの 5 問（abc458_e・abc467_f・abc475_f・abc479_d・abc479_e）は本文にないので、確かめるまで仮のままでよい
- data/problems.yaml ｜ — ｜ 本文の要約が台帳の summary（その ページ向けの alternatives を含む）と一字一句は一致しない行が 1549 行中 199 行（上の 16 か所を含む）。多くは「1 点」と「一点」、$ の有無、条件の補い ｜ summary_cmp.py の出力 ｜ 規則としては本文の要約が台帳の summary と違ってよいか（手引き 58 行目は「台帳の summary を使う」）を決める。違ってよいなら記録だけ。そろえるなら、意味が変わるもの（abc304_f・abc326_e・abc287_g・abc437_f・abc354_d など、問いの一部を落とした要約）を先に見る
- data/problems.yaml ｜ 1〜3 ｜ 冒頭のコメントが「tools/build_ledger.py が catalog と調査レポートから作った下書き」のまま。今は手で直す台帳で、作り直さない約束（progress.md 61 行目） ｜ progress.md、tools/README の build_ledger の行 ｜ 「骨格（8a）以降は台帳が正。手で直し、build_ledger.py では作り直さない」と書き直す

### (4) 用語集の正規形の表と prh.yml

- docs/guide/glossary.md ↔ prh.yml ｜ glossary 849（データ構造の表のセグメント木の行）、prh.yml 156〜157 ｜ 表は「セグツリー」を正規形「セグメント木」に直すとするが、prh は「セグ木」に直す ｜ prh_cmp.py ｜ どちらかにそろえる。表の考え方（直す先は正規形）に合わせ、prh の `expected: セグ木 / pattern: セグツリー` を `expected: セグメント木` の patterns に移す
- docs/guide/glossary.md ↔ prh.yml ｜ prh.yml 205〜208、glossary の整数論の表（858 行目〜） ｜ prh に「ビットリバース → ビット反転」「杜教筛 → 杜教篩」があるのに、用語集の表に行がない（付録 A には杜教篩がある） ｜ prh_cmp.py ｜ 整数論の表に「ビット反転 ｜ — ｜ ビットリバース」「杜教篩 ｜ — ｜ 杜教筛」を足す
- prh.yml ｜ 3 ｜ 冒頭のコメントが「正規形は planning/style-guide.md の §7 と付録 A」とし、用語集のページ（「表記の検査の元」と書く。glossary 13・47 行目）を挙げていない。正のものが 2 つに見える ｜ 両方の文 ｜ 「正規形の表は docs/guide/glossary.md#canonical-forms（付録 A はその元の一覧）」のように、どれが正かを 1 つに決めて書く
- prh.yml ↔ 本文 ｜ — ｜ textlint の全件実行で prh の指摘は 0 ｜ textlint.txt ｜ 直さなくてよい（記録だけ）

### (5) README・tools/README・progress.md

- planning/progress.md ｜ 16 ｜ 工程 8 が「進行中（…全353ページが draft）」。本文の執筆（8b）は b1〜b6 で終わっている ｜ 99〜104 行目の「次にやること」は全部済み ｜ 「完了（2026-10-22。全 353 ページが draft）」にする
- planning/progress.md ｜ 18 ｜ 工程 10 が「未着手」 ｜ 今この洗い出しをしている ｜ 「進行中（洗い出し：batches/s10/）」と成果物の欄を入れる
- planning/progress.md ｜ 63 ｜ 「残り：用語の索引の漢字の読み、docs/index/*.md に search: exclude を足す」。search: exclude はもう入っている（docs/index/math.md など 4〜5 行目） ｜ 生成物を読んで確かめた ｜ search: exclude を「済み」にし、漢字の読みだけを残りに残す（tools/README 82 行目も「未定」のまま）
- planning/progress.md ｜ 99・101 ｜ 「本文のあるページは 270/353」「相手がまだ stub のものは、そのページを書いた後に同じ手順で」が、その後の 2 回目の張り替えで済んだ後も途中の状態の書き方のまま ｜ 103 行目に完了の記録がある ｜ 99 行目の見出しの文を「全 353 ページが draft」に、101 行目の後半を消すか「2 回目で済み」にする
- planning/progress.md ｜ 104 ｜ 工程 10 の残りが「§14〜§16 へのそろえ直しと、batches/b5/decisions.md の残り」だけで、b6 の残り（abc411_e、道具の正規表現）と b5/decisions.md の最後の 2 行（張り替えの残り 6 か所・§16-7 の言い回し）への道筋がない ｜ b5/decisions.md 36〜38 行目、b6/APPLIED.md 83 行目 ｜ 工程 10 の節を作り、残りの一覧（この洗い出しの結果を含む）をそこへ移す
- planning/progress.md ｜ 106〜108 ｜ 「ユーザーにお願いしていること：sudo apt install libnspr4 libnss3 libasound2」が残る。手元の ldconfig で 3 つとも見つかる（入っている） ｜ `ldconfig -p` ｜ 済みとして消す（render_svg.py が動くかは一度確かめる）
- planning/progress.md ｜ 88〜95 ｜ 「本制作の進め方（8b）」は執筆中の手順で、工程 10 の今は読み手を迷わせる ｜ — ｜ 見出しに「（記録）」を付けるか、工程 10 の節の後ろへ回す
- tools/README.md ｜ 30〜37 ｜ 「工程6 土台作り・工程7 試作」の例の注が「試作のページ。catalog にだけある前提・related は『未作成』の警告」のまま。今は全ページがあり、この警告は出ない ｜ check_pages の結果 | 注を「全ページの検査」に直すか、節ごと「工程10 全体の検証・定期の検査」に寄せる
- tools/README.md ｜ 一覧の表（12〜24） ｜ `textlint_targets.py`（package.json の lint:text が使う）が表にない ｜ tools/ の一覧 ｜ 「textlint の対象の Markdown の一覧を出す（stub と生成物を除く）｜なし」の行を足す
- tools/README.md ｜ 16 ｜ build_ledger は「今は `--check`（catalog との食い違い）だけ使う」とあるが、目次の凍結の後は `--check` が必ず食い違い（終了コード 1）を出す。CI（check.yml 70〜73）は警告だけにしてある ｜ 手元で実行：台帳にだけある 77 問・役割の違い 69 問 ｜ 「8a 以降は catalog が凍結なので、`--check` の食い違いは予期したもの。台帳の確認は check_pages と fix_problems で行う」と書く
- tools/README.md ｜ 82 ｜ 「用語の索引の漢字で始まる語は…未定」 ｜ progress.md 63 行目と同じ残り ｜ 工程 10 で決めるか、残りとして progress に寄せる（どちらかに 1 か所で書く）
- README.md ｜ — ｜ 古い記述はない（6 行目「全 353 ページに本文があり、検証と仕上げを進めています」は今の状態に合う）。claude.ai/code の Projects の書き方も claude/ の 2 ファイルと一致 ｜ 読んで確かめた ｜ 直さなくてよい。細かい点として 46 行目「uv と Node.js が要ります」は、Node.js が textlint のためだけなので「サイトを見るだけなら uv だけ」と分けてもよい

### (6) 外部リンク：付録 B にないドメイン

check_noai で 69 URL を確かめ、取得できたものはどれも noai・noimageai の指定がなかった。付録 B に足す候補は次のとおり（メインがまとめて付録 B に足す）。

- planning/style-guide.md 付録 B ｜ 401〜 ｜ 本文の参考の節が使っているのに付録 B にないドメイン（どれも check_noai で指定なし、2026-10-22）：algo-logic.info・arxiv.org・atcoder-novisteps.vercel.app・blog.nishigake.net・blog.tibrella.space・blog.tiramister.net・book.mynavi.jp・code.claude.com・competitive12.blogspot.com・cplusplus.github.io・gdst.dev・it.commutty.com・kato-hiro.github.io・koosaga.com・kopricky.github.io・kumonosu.cloudsquare.jp・nullkara.jp・oeis.org・picomikan.net・webkit.org・yamanoue.tslmuse.com ｜ domains.py・noai.json ｜ 「そのほか」に足す
- planning/style-guide.md 付録 B（はてなブログ） ｜ 405 ｜ 付録 B にないはてなブログの書き手（どれも指定なし）：amentorimaru・at274・ferin-tech・flkanjin・fukuro-hoho・geam1113・kazuma8128・kokiymgch・ks2m・miti-7・mmxsrup・motsu-xe・ngtkana・sapphire15・sen-comp・snuke・tsutaj（.hatenablog.com）、bondo・emtubasa・perogram（.hateblo.jp） ｜ 同上 ｜ はてなブログの行に足す
- planning/style-guide.md 付録 B（scrapbox・note） ｜ 406 ｜ 付録 B にない scrapbox のプロジェクト（Kodaman・esaka-sandbox・procon-kirokuyou・kyopuro-ryusuke920）と note.com の記事（vain0x n0037d6468812、syamashi nb491ffdf0ca3・nc5b5876e0514・n8e580d4ce59d、hip_crow3665 ne7a656317cea）。meta の指定はない ｜ 同上。note.com は「利用条件を記事ごとに確かめる」約束で、確かめた記事は 2 本だけ ｜ scrapbox は確かめたプロジェクトに足す。note.com の 5 記事は利用条件を読んでから足す（読めなければ出典を別の資料に替える）
- docs/cpp/cpp-environment.md・docs/cpp/cpp-macros-template-file.md・docs/string/hashing-for-sets.md・docs/tree/static-top-tree.md ｜ 304／315〜316／266／185 ｜ trap.jp は付録 B で「確かめられなかった」のまま、4 ページ 5 か所で使っている（付録 B は 2 ページと書くが、cpp-macros-template-file・hashing-for-sets もある）。今回も取得できなかった（タイムアウト・接続拒否） ｜ check_noai ｜ 付録 B の「使っているページ」を 4 ページに直す。時間を置いて check_noai をやり直し、指定がなければ確認済みに移す
- docs/ds/union-find-applications.md・docs/ds/sqrt-decomposition.md ｜ 289／259 ｜ doi.org（ACM の論文への DOI）と suzukiapple.tumblr.com が HTTP 403 で確かめられない ｜ check_noai ｜ doi.org は転送先の dl.acm.org を確かめるか、書誌情報だけの出典（URL なし）にする。tumblr はブラウザなしで確かめられなければ、同じ問題（abc365_g）の別の解説に替える

## basics

- docs/basics/difference-sequence.md ｜ 209（練習の囲み） ｜ 台帳の abc116_c（diff 542、練習）が本文にない ｜ ledger_vs_body.py ｜ 練習に足すか、台帳の pages から外す（黄のページの練習としては易しすぎるので、外すのが自然）
- docs/basics/bit-full-search.md ｜ 210 ｜ abc197_c（台帳では練習）が本文にない ｜ 上の ## shared (3) の判断待ち ｜ 練習に足す
- docs/basics/binary-search.md ｜ 200 ｜ abc299_d（diff 684、練習。interactive の例題）が本文にない ｜ ledger_vs_body.py ｜ 練習に足す（インタラクティブの二分探索として #practice に。interactive の例題へのリンクを方針に）か、pages から外す
- docs/basics/kth-value.md ｜ 165 ｜ abc364_d（diff 1136、練習）が本文にない ｜ 同上 ｜ 練習に足す（答えで二分探索して K 番目の距離）か外す
- docs/basics/prefix-sum.md ｜ 212 ｜ typical90_bx（練習）が本文にない。abc479_d は未確認で、載せない note どおり ｜ 同上 ｜ typical90_bx は練習に足すか外す。abc479_d はそのまま
- docs/basics/exchange-argument.md ｜ 230（力試しの囲み）・FM 21 ｜ abc467_f（diff 2052、力試し）が本文になく、台帳の summary も仮の文。frequency_evidence は recent に数える ｜ 同上 ｜ 問いを確かめて summary を書き、力試しに足す。確かめられなければ status を未確認にして note を残す（abc458_e と同じ扱い）

## thinking

- docs/thinking/fix-variable.md ｜ 182 ｜ abc458_e は status 未確認で、載せない note どおり ｜ 台帳の note ｜ 直さなくてよい（問いを確かめたら足す）

## dp

- docs/dp/dp-prefix-sum.md ｜ 254 ｜ abc130_e（diff 1676、練習）・abc183_e（diff 1288、練習）が本文にない ｜ ledger_vs_body.py ｜ どちらも累積和で遷移を速くする典型なので練習に足す（abc183_e は方向ごとの累積和）。足さないなら pages から外す
- docs/dp/dp-state-design.md ｜ 271 ｜ abc147_e（diff 1713、練習）が本文にない ｜ 同上 ｜ 練習に足すか外す（dp-grid・bitset-speedup にはある）
- docs/dp/rerooting.md ｜ 229・練習の後に力試しの囲みがない ｜ abc223_g（diff 2351、力試し）が本文にない ｜ 同上 ｜ 力試しの節を作って足すか外す
- docs/dp/dp-basics.md ｜ 235 ｜ abc242_c（diff 512、練習）が本文にない ｜ 同上 ｜ 練習に足すか外す
- docs/dp/subset-enumeration-dp.md ｜ 209・参考 256〜 ｜ abc332_e（diff 1883、練習）が本文にない。参考の節には「ABC332 E - Lucky bag 解説」の記事がある ｜ 同上 ｜ 練習に足す（参考の記事が出典になる）。足さないなら pages と参考の記事を外す
- docs/dp/insertion-dp.md ｜ 233 ｜ exawizards2019_d（diff 2075、練習）が本文にない ｜ 同上 ｜ 練習に足すか外す
- docs/dp/slope-trick.md ｜ FM 21・力試しの囲みなし ｜ abc458_g の扱い ｜ ## shared (3) の判断待ち ｜ 力試しに足す（台帳の pages も）

## graph

- docs/graph/connected-components.md ｜ 169 ｜ abc284_c（diff 193、練習）が本文にない ｜ ledger_vs_body.py ｜ 練習に足すか外す（graph-basics にはある）
- docs/graph/extended-dijkstra.md ｜ 344 ｜ abc348_d（練習）・typical90_bb（練習）・zone2021_e（練習）が本文にない。台帳の note は「本文の参照として台帳に足した（catalog の problems_note）」だが、本文に題名も ID もない ｜ 同上 ｜ 本文の参照として書く予定だったものなので、練習に足す（3 問とも問いと方針は note のとおり確かめ済み）。足さないなら外す
- docs/graph/union-find-connectivity.md ｜ 226 ｜ abc413_g（diff 1723、練習）が本文にない ｜ 同上 ｜ 練習に足すか外す（grid-graph の力試しにはある）
- docs/graph/spanning-tree-advanced.md ｜ 練習の囲み・72・159 ｜ keyence2019_e の扱い ｜ ## shared (3) の判断待ち ｜ 練習に足す

## tree

- docs/tree/tree-diameter.md ｜ 277 ｜ abc267_f（diff 1939、練習）が本文の問題の囲みにない（162 行目で「ABC267 F（Exactly K Steps…」と名前だけ触れる） ｜ ledger_vs_body.py ｜ 練習に足す（lca の例題へのリンクを方針に）
- docs/tree/tree-degree.md ｜ 57・206 ｜ abc303_e（台帳では練習）は 57 行目で tree-basics の例題へのリンクとして触れるだけで、囲みにない ｜ 同上 ｜ 他ページの例題として触れる形で十分なら、台帳の pages から tree-degree を外す。練習として持つなら囲みに足す
- docs/tree/lca.md ｜ 205 ｜ typical90_ai（練習）が本文にない ｜ 同上 ｜ 練習に足すか外す（auxiliary-tree の例題）
- docs/tree/tree-edge-contribution.md ｜ 201 ｜ abc479_e は未確認で、載せない note どおり ｜ 台帳の note ｜ 直さなくてよい

## ds

- docs/ds/monotonic-stack.md ｜ 236 ｜ abc189_c（台帳では練習）が本文にない ｜ ## shared (3) の判断待ち ｜ 練習に足す
- docs/ds/union-find-applications.md ｜ 256・273 ｜ abc206_d（diff 879、練習）・abc131_f（diff 1937、力試し）が本文にない ｜ ledger_vs_body.py ｜ 足すか外す（abc131_f は #modeling の「何を頂点にするか」の典型、abc206_d は union-find の練習にもある）
- docs/ds/stack-techniques.md ｜ 193 ｜ abc237_d（diff 544）・abc283_d（diff 453）・abc428_c（diff 483）の 3 問（すべて練習）が本文にない ｜ 同上 ｜ 練習に足すか外す
- docs/ds/union-find.md・docs/ds/global-offset.md など ｜ — ｜ 本文の要約と台帳の summary の言い回しの違い（abc206_d・abc157_d・abc278_d） ｜ summary_cmp.py ｜ ## shared (3) の要約の規則を決めてから

## math

- docs/math/mod-arithmetic.md ｜ 183 ｜ abc266_b（diff 95、練習）が本文にない ｜ ledger_vs_body.py ｜ 練習に足すか外す
- docs/math/crt.md ｜ 225・力試しの囲みなし ｜ abc371_g（diff 2348、力試し）が本文にない ｜ 同上 ｜ 力試しの節を作って足すか外す（permutation-cycles の力試しにはある）
- docs/math/xor-basis.md ｜ 232・245 ｜ agc045_a（diff 2070）・zone2021_f（diff 2197）の 2 問（練習）が本文にない ｜ 同上 ｜ 練習に足すか外す
- docs/math/integer-root.md ｜ 185・214 ｜ panasonic2020_c（diff 701、練習）が本文にない。参考の節 214 行目には at274 氏の「パナソニックコン2020 C - Sqrt Inequality」が残る（使い道のない出典） ｜ 同上 ｜ 練習に足す（参考の記事が出典になる）か、pages と参考の行の両方を外す

## comb

- docs/comb/expectation-tail-sum.md ｜ 練習の囲みなし・206（力試し）・248 ｜ abc411_e（diff 1400、練習）が道具の正規表現のせいで載っていない。参考の節 248 行目に Shizen_Tota 氏の ABC411 の記事が出典として残る ｜ b6/APPLIED.md 83 行目、## shared (2) ｜ 正規表現を直した後に練習の囲みを作って足す。方針の文は APPLIED.md のとおり（値を圧縮し、P(最大値 ≤ v) を各サイコロの割合の積として小さい順に更新し、差で足す。0 の因子に注意）
- docs/comb/stars-and-bars.md ｜ 188 ｜ abc132_d（diff 1167、練習）が本文にない ｜ ledger_vs_body.py ｜ 練習に足すか外す（binomial-precompute にはある）
- docs/comb/probability-dp.md ｜ 243 ｜ abc382_e（diff 1671、練習）が本文にない ｜ 同上 ｜ 練習に足すか外す（expected-value-dp にはある）
- docs/comb/inclusion-exclusion.md ｜ 271・FM 22 ｜ abc475_f（diff 1916、練習）が本文になく、台帳の summary も仮の文。frequency_evidence は recent に数える ｜ 同上 ｜ 問いを確かめて summary を書いて足すか、未確認にして note を残す

## start

- docs/start/how-to-use.md ｜ 24（FM）・188・243〜251・308 ｜ 「『準備中』のページ」の節（243〜251）が「帯が出ているページは骨組みだけで本文がまだない」「要点は目次から機械的に作ったもの」と、今はないページを詳しく説明する。188 行目・308 行目も準備中のページに触れる ｜ 準備中 0 ｜ 節を「段階（stage）の意味」の短い説明に替える（stub＝準備中は今はないこと、draft＝本文あり・未検証、reviewed＝検証済み）。anchor stub は main.html の howto_url が指すので、残すか main.html も一緒に直す。66 行目の生成の表の「準備中」の列は ## shared (1)

## guide

- docs/guide/knowledge-map.md ｜ 59 ｜ 「準備中のページには『（準備中）』と添える」 ｜ 準備中 0。map.js 743 行目は stub のときだけ出す ｜ 文を消すか「本文がまだないページ（今はない）」と条件の書き方にする
- docs/guide/reverse-index-signs.md ｜ 75 ｜ 「ページ名の後の『（準備中）』は、そのページの本文がまだないことを表す」 ｜ 同上（生成の表に「（準備中）」は 0 件） ｜ 同上

## string

- docs/string/hashing-for-sets.md ｜ 266 ｜ trap.jp（確かめられていないドメイン） ｜ ## shared (6) ｜ check_noai をやり直す

## cpp

- docs/cpp/cpp-environment.md・docs/cpp/cpp-macros-template-file.md ｜ 304・315〜316 ｜ trap.jp（確かめられていないドメイン） ｜ ## shared (6) ｜ check_noai をやり直す

## misc

（この観点の指摘なし）

## geometry

（この観点の指摘なし。本文の要約と台帳の summary の違い（abc251_g・abc202_f・abc191_d）は ## shared (3) の要約の規則を決めてから）

## patterns

（この観点の指摘なし）
