# s10 共有ファイル：直したもの

audit-*.md の「## shared」のうち、共有ファイル（tools/・data/problems.yaml・prh.yml・用語集の表記の表・README.md・tools/README.md・progress.md・手引きの付録 B）で直したもの。直した数：**31 件**（下の番号）。残したものは left-shared.md（14 件）。commit はしていない。gen_site.py は `--check` だけ実行した（生成物は古いままなので、メインが `python3 tools/gen_site.py` で作り直す）。

確かめたこと：`python3 tools/check_pages.py` エラー 0・警告 0、`python3 tools/fix_problems.py --check` 直すべき行 0・直せない行 0（終了コード 0。新しい逆向きの警告が 18）、`python3 tools/gen_site.py --check` は生成物が古い（下の生成の文言の変更と、並行しているページの直しによる。予期したもの）。

## 道具

1. **check_pages.py の PROBLEM_LINE_RE**：label を `(?:[^\[\]]|\[[^\[\]]*\])+` にし、題名の 1 段の角かっこを読めるようにした。試験：`- [ABC411 E. E [max]](…abc411_e)（diff 1400）：…` から label・id・summary を読め、ふつうの行も変わらず読める
2. **fix_problems.py の LINK_TAIL_RE**：同じく label に 1 段の角かっこを許した。試験：`- abc411_e：…` と `- [x [y]](…abc411_e)：…` の両方から正しい行を作れた
3. **abc411_e を comb/expectation-tail-sum の練習に足した**（b6 の見送り）：`## 練習問題 {#practice}` の囲みを例題と力試しの間に作り、`fix_problems.py --page expectation-tail-sum` で行を作った。方針の文は Shizen_Tota 氏の記事（参考の節にすでにある。check_noai で指定なし）で確かめた：値を座標圧縮して小さい順に掃き、P(最大値 ≤ v) を各サイコロの割合の積として掛け直し、差で足す。0 の因子は個数を別に数える。記事は双対セグメント木で掛け直す
4. **fix_problems.py --check に逆向きの検査**：台帳の pages にあるのに本文の問題の囲みにない（問題, ページ）を「警告」に出す（status が確認済みの問題だけ。終了コードには入れない）。冒頭の説明と tools/README にも書いた
5. **gen_site.py：詳細索引の冒頭の文**：stub のページがその分野にないときは「stub（準備中）のページは要約と前提しかなく…」を出さない
6. **gen_site.py：llms.txt のページ数**：準備中が 0 なら「（準備中 0）」を出さない
7. **gen_site.py：段階の言い方**：STAGE_JA と llms.txt の説明の draft を「執筆中」から「本文あり・未検証」にした（reviewed＝検証済み と対になる形。制作状況の表の見出しも変わる）
8. **gen_site.py：分野の一覧の表（fields）**：準備中のページが 1 つもなければ「準備中」の列を出さない（how-to-use の 66 行目の表）。生成部分の説明の文も直した
9. **gen_site.py：ロードマップの位置ごとの表**：1 問の pages に同じページの anchor が 2 つあると 2 回と数えていたのを、問題ごとにページの id で重複を除いてから数えるようにした（`--check --diff` で「最小全域木（2）」が「最小全域木」になることを確かめた。ほかの行は変わらない）
10. **新しい道具 tools/check_svg.py**：図の width・height の欠けと比、幅 450 超え（§15-8）、幅 328px で 9px 未満の文字を警告する（audit-figure の svg_audit.py の計算を取り込んだ）。試験：font-size 8 の文字を持つ幅 400 の図で 6.6px を警告し、下付きの tspan は数えないことを確かめた。tools/README の表と「ふだんの検査」に書いた

## 台帳 data/problems.yaml

11. **冒頭のコメント**：「下書き」のままだったのを、骨格（8a）以降は台帳が正で、手で直し build_ledger.py では作り直さない、と書き直した
12. **agc002_d**（判断待ち）：merge-process-tree 向けの alternatives の summary を本体と同じ文（「最初の t 本の辺だけを使ったとき…最小の t」）にし、approach だけを残した。理由：3 ページの本文の要約がすでに本体の文にそろっている。これで「2 案のどちらか」は閉じる
13. **abc311_h**（判断待ち）：static-top-tree の練習のまま残す。裏付け：luogu の解説（1s1aiccu）は重い子を 1 回・軽い子を 2 回再帰する木 DP（O(N^{log2 3} X)）で、Static Top Tree には触れない。Nyaan 氏の解説一覧もこの問題を「重軽再帰 DP」として挙げ、Static Top Tree は ABC351 G に付けている。つまりこの問題は Static Top Tree そのものの問題ではないが、ページの本文（71 行目・方針 174 行目）は「更新のない木 DP に重い子を使う重軽再帰 DP の問題」と区別して説明済みで、移すと tree-dp-square に節と方針を書き足すことになる（diff 3605 は黄の帯から遠い）。台帳の approach は「重軽再帰 DP」のままで正しい。ページの aliases から「重軽再帰 DP」を外すのはページの作業（left-shared 10）
14. **abc458_g**（判断待ち）：裏付け（ikatakos 氏の ABC458 の記録。check_noai で指定なし）で問いと解き方を確かめた。人数を二分探索し、「j 人が脱出済みのときの残りのメダルの最大」を上に凸な折れ線として傾きの列で持つ（Slope Trick）。収入は平行移動、生存の費用は傾きの一律の変更、脱出は傾きの下限を −C_i にそろえる操作で、判定は O(N)。決めたこと：仮の文だった summary を問いの形に書き直し、pages に slope-trick（力試し。diff 2831 は発展の帯）を足し、slope-trick 向けの alternatives（approach は上の手順）を書いた。checked を 2026-10-22 にした。slope-trick の frequency_evidence の「recent 1（abc458_g）」は recent-abc.yaml が正なので残す。ページの囲みと方針はページの作業（left-shared 9）
15. **keyence2019_e**（判断待ち）：裏付け（drken 氏の記事。check_noai で指定なし）で、辺の重みが D|i−j| + A_i + A_j であり、分割統治で候補の辺を O(N log N) 本にしてクラスカル法（O(N log² N)）、ほかに A の大きい順の枝刈りで O(N) 本にする方法、Borůvka 法などが紹介されていることを確かめた。spanning-tree-advanced の 72 行目の説明（O(N log N) 本に減らしてクラスカル法）と合うので、pages に spanning-tree-advanced（練習）を足し、alternatives の approach を「候補の辺を絞るクラスカル法」にした（Borůvka 法は記事が名前を挙げるだけなので書かない）。ページの行はページの作業（left-shared 9）
16. **abc189_c**（判断待ち）：台帳の pages の monotonic-stack は残す（#histogram の節がこの型そのもので、ikatakos 氏の記録も裏付けにある）。本文に足すのはページの作業（left-shared 9）
17. **abc197_c**（判断待ち）：台帳の pages の bit-full-search は残す（approach が区切り方 2^(N−1) 通りの bit 全探索で、ページの中心）。並行しているページの直しで本文にも載り、逆向きの警告から消えた
18. **仮の summary 15 問**：summary が「（執筆時に確かめる）」かそれを含む 20 問のうち、本文に自分の要約がある 15 問（16 か所）を本文の要約で置き換えた：abc404_f・abc412_f・abc432_c・abc445_g・abc450_g・abc459_f・abc466_f・abc468_e・abc469_e・abc470_e・abc470_f（本体と alternatives）・abc473_e・abc476_f・abc476_g・abc479_f。2 ページで要約が違う abc445_g（project-selection と konig-theorem）と abc479_f（reformulation と inversion-number）は、本体を 1 つ目のページの文、そのページ向けの alternatives をもう一方の文にした（それぞれの本文と台帳が一致する）。残り 5 問は left-shared 14
19. **abc455_f・abc470_g の対応**（audit-facts）：直さない、と決めた。recent-abc.yaml の pages は「使う手法のページ」、台帳の pages は「問題を載せるページ」で、台帳は帯で置き場を選んでいる。abc455_f（diff 1549）は水の lazy-segment-tree の練習、abc470_g（diff 2097）は青の lazy-segment-tree-patterns の力試しで、どちらもページの帯に合う。recent の側の対応（abc455_f は S・F の設計が要るので patterns、abc470_g は遅延セグ木）は recent-abc.yaml の note が ikatakos 氏の記録で確かめた手法の記述で、食い違いではない

## 用語集の表記の表と prh.yml

20. **セグツリー**：prh の `expected: セグ木 / pattern: セグツリー` を消し、`expected: セグメント木` の patterns に移した（用語集の表「セグメント木 ｜ セグ木 ｜ セグメントツリー・セグツリー」と合わせた。直す先は正規形）。textlint で「セグツリー => セグメント木」になることを確かめた
21. **用語集の整数論の表**に「ビット反転 ｜ — ｜ ビットリバース」「杜教篩 ｜ — ｜ 杜教筛」を足した（prh にある規則の行）
22. **prh.yml の冒頭のコメント**：正規形の表は docs/guide/glossary.md#canonical-forms が正で、手引きの §7・付録 A はその元の一覧、と 1 つに決めて書いた。規則を足したら表にも行を足すことも書いた

## README・tools/README・progress.md

23. **progress.md**：工程 8 を「完了（2026-10-22。全 353 ページが draft）」、工程 10 を「進行中（batches/s10/）」と成果物の欄を入れた
24. **progress.md**：工程 6 の残りの search: exclude を「済み」にし（docs/index/*.md の front matter にあることを確かめた）、漢字の読みだけを残した
25. **progress.md**：8b の行を「全 353 ページが draft」に、張り替えの「相手がまだ stub のもの」を「2 回目で済み」にし、「本制作の進め方（8b）」の見出しに「（記録）」を付けた
26. **progress.md**：「工程10：全体の検証」の節を作り、洗い出しの置き場と、b5/decisions.md の残り・§14〜§16 へのそろえ直し・漢字の読み・abc411_e の道筋を移した
27. **progress.md**：ユーザーにお願いしていた `sudo apt install libnspr4 libnss3 libasound2` を済みにした（ldconfig で 3 つとも見つかり、render_svg.py が PNG を作れることを確かめた）
28. **tools/README.md**：「工程6・工程7」の例の注（「catalog にだけある前提・related は『未作成』の警告」）を「全ページの検査」に直し、節の名前を「ふだんの検査」にした。表に textlint_targets.py と check_svg.py の行を足した
29. **tools/README.md**：build_ledger の行に、8a 以降は catalog が凍結なので `--check` の食い違いは予期したもので、台帳の確認は check_pages と fix_problems で行うと書いた。漢字の読みの行を「工程10 の残り（progress.md に記録）」にした
30. **README.md**：「uv と Node.js が要ります」を「サイトを見るだけなら uv だけ（Node.js は textlint にだけ使う）」と分けた

## 手引きの付録 B

31. **付録 B**：check_noai で指定がなかったドメイン 21 個を「そのほか」に、はてなブログの書き手 20（.hatenablog.com 17・.hateblo.jp 3）を、scrapbox のプロジェクト 4 つを足した。note.com の 5 記事（vain0x・syamashi 3 本・hip_crow3665）は check_noai で指定がなく、本文に転載・引用・AI の利用を断る記述がない無料の記事であることを 2026-10-22 に確かめて「確かめた記事」に足した。trap.jp は使っているページを 4 つ（cpp-environment・cpp-macros-template-file・hashing-for-sets・static-top-tree）に直し、doi.org と suzukiapple.tumblr.com が HTTP 403 で確かめられないことを書いた
