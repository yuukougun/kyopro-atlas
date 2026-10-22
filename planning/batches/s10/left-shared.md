# s10 共有ファイル：直さずに残したもの

共有ファイルの直し担当（fixed-shared.md）が直さなかったものと、その理由。どれもメインの判断か、担当の外のファイルの作業が要る。

## メインが基準を決めるもの

1. **frequency・frequency_evidence の付け直し**（audit-facts ## shared の 1〜3 項目）：recent の数え漏れ 4 ページ、「前提として N ページに届く」のずれ 3 ページ、「古い ABC n 問」のずれ 108 ページ（基準を当てると C→B が 18 ページ、B→C が knapsack-undo の 1 ページ）。理由：「古い ABC で繰り返し使われた」の基準（3 問以上か）と、工程9 で補充した問題を数えるかが catalog/README §5 に書かれていない。値が変わるので担当では決めない。直すのはページの front matter（担当の外）。基準が決まれば、一時置き場の freq3.py・freq_ev.py を元に tools/ に付け直しのスクリプトを置ける
2. **prh に足す規則**（audit-facts）：`多重テストケース→複数テストケース`・`歩道→ウォーク`・`上位ビット→上位 bit`・`最上位ビット`・`最下位ビット`・`平衡二分木→平衡二分探索木`・`フェニック木→BIT`。理由：足すと本文の約 80 か所が textlint のエラーになり、本文はこの担当の外。付録 A に「最上位 bit」「最下位 bit」を足すかも未定。本文を直す作業と同時に足す
3. **「0 始まり」「1 始まり」**（約 35 か所）を認めるか：付録 A は担当の外（担当は付録 B だけ）。決めたら付録 A と prh に反映する
4. **本文の要約と台帳の summary が一字一句は一致しない 199 行**（audit-shared (3)）：手引き 58 行目の「台帳の summary を使う」を厳密に守るかの規則が要る。担当は「（執筆時に確かめる）」の仮の文 15 問だけを本文から写した
5. **check_pages に足す構造の検査**（audit-structure ## shared）：定型の見出しと anchor の組、sections の定型 anchor、complexity の null（§16-12 の読み方が未定）、#quiz の置き場所（§3 と §14-11 の食い違い）、箇条書きの句点、#library・#resources。理由：どれも規則の読み方をメインが決めてからでないと、警告の条件を書けない。調べたスクリプトは一時置き場の audit1.py
6. **出典の題名のそろえ**（audit-relations ## shared 2 項目め、124 件）：URL ごとに h1 を 1 つに決めるのはページの作業。check_pages に「同じ URL で題名が違う」の警告を足すと今は 124 件が出るので、ページをそろえた後に足すのがよい
7. **用語の索引の漢字の読み**：五十音順にするか（読みの表か pykakasi）。progress.md の工程10 の残りと tools/README.md に 1 か所ずつ書いた

## 担当の外のファイル（ページ・図・手引きの本文）

8. **planning/style-guide.md §5 L183**：`-ftrivial-auto-var-init=zero` の計測を「0.05 秒が 1.03 秒」に直す（持ち主の cpp/cpp-environment L113 が正）。担当が書いてよいのは付録 B だけなので残した
9. **台帳の pages にあるのに本文の囲みにない問題**：`python3 tools/fix_problems.py --check` の警告に出るようにした（2026-10-22 の時点で 18 組。並行してページの直しが進んでいるので数は動く）。各組は「本文に足す」か「台帳の pages から外す」かをページの担当と決める。この担当の判断で台帳に足したもので、本文の作業が要るもの：
   - abc458_g → dp/slope-trick の力試し（囲みと方針を足す。台帳に slope-trick 向けの alternatives を書いた）
   - keyence2019_e → graph/spanning-tree-advanced の練習（参考の drken 氏の記事がその行の出典になる。台帳に alternatives を書いた）
   - abc189_c → ds/monotonic-stack の練習（#histogram の節の型。N が小さく O(N^2) でも通ること、単調スタックで O(N) にできることを方針に書く）
10. **tree/static-top-tree の aliases の「重軽再帰 DP」**を外し、本文 71 行目の語に用語集か #heavy-path-dp を当てる（front matter と本文は担当の外。台帳の判断は fixed-shared.md）
11. **図**（audit-figure）：幅・文字の大きさ・width と height の欠けの直しは docs/img（担当の外）。検査は tools/check_svg.py として足した（2026-10-22 の時点で 406 枚中 301 枚に警告 646 件。並行して直しが進んでいる）。width・height を viewBox から写す一括の直しも図の担当で行う
12. **生成物の外の手書きの文**：docs/index.md の info「制作中」（ユーザーに info を消すか確かめる）、docs/start/how-to-use.md の「『準備中』のページ」の節と FM の sections（anchor stub は main.html の howto_url が指すので残す）、guide/knowledge-map.md 59 行目・guide/reverse-index-signs.md 75 行目。gen_site.py の生成する文言はこの担当で直した
13. **出典の差し替え**：doi.org（union-find-applications 289）は転送先の dl.acm.org を確かめるか書誌情報だけの出典に、suzukiapple.tumblr.com（sqrt-decomposition 259）は abc365_g の別の解説に替える（どちらも HTTP 403）。trap.jp は 4 ページ 5 か所で使うが、今回も証明書の検証の失敗で取得できなかった（付録 B は「確かめられなかった」のまま、使っているページを 4 つに直した）。時間を置いて check_noai をやり直す

## 台帳の仮の summary（5 問）

14. abc458_e・abc467_f・abc475_f・abc479_d・abc479_e の summary は「（執筆時に確かめる）」のまま。本文に要約がなく、問題文を読めない（atcoder.jp を開かない）ので、第三者の解説で問いを確かめてから書く。abc467_f（exchange-argument の力試し）と abc475_f（inclusion-exclusion の練習）は status が確認済みで台帳の pages にあるのに本文にない（上の 9 の警告に出る）
