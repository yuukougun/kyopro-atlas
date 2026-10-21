# sorting-techniques の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/sorting-techniques.md、snippets/sorting-techniques/matching.{cpp,yaml}・ratio-sort.{cpp,yaml}・ratio-double-ng.{cpp,yaml}（失敗例。本文には取り込まない）、docs/img/sorting-techniques/matching.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: 二分探索・尺取り法・交換論法へのつながり, anchor: next-steps}` を足した（手引き §4 の基礎の構成「上位の手法とのつながり」の節）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 3。数式 `$A = (1, 4, 6)$` などの中の読点を数える max-comma が 2 件、練習の方針の折りたたみ全体を 1 文と数える sentence-length が 1 件。どれも誤検出）
- 図：catalog の visual（static・priority 2）どおり、2 列の対応を線で結び、ソートすると交差が消える SVG を作った。証明の筋（点 x = 5 をまたぐ組の数）も同じ図に入れた。画像に変換して目視はしていない（手元に SVG を描く道具がない）ので、検証で表示を確かめてほしい
- 確かめた事実：`<=` の比較関数で同じ値ばかりの配列を `std::sort` すると、g++-15 -O2 -fsanitize=address で heap-buffer-overflow になること、`-D_GLIBCXX_DEBUG` で「comparison doesn't meet irreflexive requirements」で止まること、999999998/1999999997 と 999999999/1999999999 が double で同じ値になること（ratio-double-ng で確かめた）は、すべて手元で実行して確かめた

## 使った出典

- drken（hatenablog）ABC121 C・ABC308 C・ABC187 D：例題と練習の方針。ABC187 D の「(A+B, A) の辞書順は誤り」は記事にあり、本文の反例 (0,10),(6,3),(6,3) は自分で作った
- Reputeless/tenkei_90 の 014.md：典型90 014 の方針
- en.cppreference.com（Compare の要件、stable_sort の計算量）：付録 B にあり、check_noai でも指定なしを確かめた
- ikatakos.com（ABC474 の記録）：問題の補充の候補を探すために解説の部分だけを読んだ。本文には使っていない
- 新しく noai を確かめたドメイン：なし

## 台帳への提案

- なし（4 問とも evidence の解説で問いと方針を確かめ、summary と approach はそのままでよい）

## 用語集への提案

- 狭義の弱順序｜strict-weak-ordering｜比較関数 comp が満たすべき性質。comp(a, a) が false（非反射）、comp が推移的、comp(a, b) と comp(b, a) がどちらも false という「同等」も推移的、の 3 つ。std::sort・set・priority_queue の比較関数に要る（本文で `../guide/glossary.md#strict-weak-ordering` にリンク済み）
- 安定ソート｜stable-sort｜同等な要素の元の並びを保つソート。C++ では `stable_sort`。`sort` は保たない
- 用語の揺れ：cpp-comparators の sections は「厳密弱順序」と書いている。このページと catalog の summary は「狭義の弱順序」。どちらかにそろえ、prh.yml で揺れを検出するとよい（cpp-comparators を書く前に決めてほしい）

## 手引きへの提案

- 付録 A に「狭義の弱順序」「安定ソート」を加えるか検討してほしい（basics と cpp の両方で使う）
- 折りたたみ（`??? note`）の中の箇条書きは textlint が 1 文として長さを数えることがある。sentence-length の警告は折りたたみの中なら無視してよい、と §13.8 に書き添えると迷わない

## 問題の補充の候補

- abc474_e（E. One Time Coupon、diff 1153、ap.py で確認）｜商品をすべて買う最小の金額を、クーポンの得方と使い方を考えて求める。$A_i - B_i$ の昇順（同値なら $A_i$ の昇順）に並べると定価で買う商品が先頭の連続部分になり、分割位置を全探索できる｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0906_abc474 ｜力試しの候補。frequency_evidence の recent に挙がっている。ただし要約を取った範囲では「先頭に連続すると考えられる」理由までは確かめていないので、台帳に入れる前に解説の本文で根拠を確かめること
- abc457_e は台帳で interval の練習になっており、このページには足していない

## 未解決の点

- 図の SVG は描画して確かめていない（座標は計算で配置した）
- 「`stable_sort` は追加のメモリが取れないと O(N log² N)」は cppreference の記述による。front matter の complexity にはメモリが取れる場合だけを書いた
- 確認問題の「重み付き完了時刻の和」（$T_i W_j < T_j W_i$ なら i を先）は自分で計算した交換の式で、出典はない（交換論法のページで扱う内容への導入として置いた）
