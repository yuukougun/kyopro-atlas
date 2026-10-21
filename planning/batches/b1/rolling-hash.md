# rolling-hash の報告と提案（工程8b・バッチ b1）

- 書いたファイル：docs/string/rolling-hash.md、snippets/rolling-hash/{substring-hash,longest-repeat,hash-segtree}.{cpp,yaml}、docs/img/rolling-hash/{prefix-hash,segtree-merge}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（3 片とも一致）、textlint（エラー0、警告23。数式の中の `[` の対応・数式を含む文の長さと読点の数による誤検出）
- 使った出典：keymoon（Qiita）、drken（abc141_e・abc150_f）、ikatakos（abc141・abc398・abc430・abc284・abc135。解説の部分だけ）、merom686（abc331）、syamashi（note.com、abc331_f）、E869120 の典型90 047 の解説画像（github.com の raw から取得して読んだ）、ACL の document_ja/segtree.md
- 新しく noai を確かめたドメイン：なし。note.com の記事 https://note.com/syamashi/n/n8e580d4ce59d は check_noai.py で指定なし（meta robots は max-image-preview:large のみ）、本文に AI 利用や転載を禁じる記載なし（note の利用規約そのものは読んでいない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| typical90_au | summary | R・G・B からなる 2 つの列で各マスの色が決まるマス目について、すべてのマスが同じ色である斜めの線の数を求める。 | https://github.com/E869120/kyopro_educational_90/blob/main/editorial/047-01.jpg （と 047-02.jpg） |
| typical90_au | evidence | 047-01.jpg を足す（色の条件の言い換えはこちらの画像にある） | https://github.com/E869120/kyopro_educational_90/blob/main/editorial/047-01.jpg |
| abc430_e | alternatives（hash-safety 用の記録） | 「基数を 2 に固定すると有名な mod で衝突するテストがあり、mod を複数試して回避した」という記録がある。hash-safety の練習の候補にもなる | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1101_abc430 |
| abc331_f | evidence の補足 | syamashi の記事は BIT（1 点加算）で解き、base を固定して WA になったと書いている。hash-safety の記録としても使える | https://note.com/syamashi/n/n8e580d4ce59d |

本文の typical90_au の行は、上の summary を自分で書いて入れた（台帳は「（執筆時に確かめる）」のまま）。fix_problems が台帳から作り直すと戻るので、台帳の summary を直してほしい。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 衝突（ハッシュの） | hash-collision | 異なる 2 つの対象のハッシュが等しくなること。ハッシュが等しいことを「対象が等しい」とみなす判定は、衝突すると誤る |
| 最長共通接頭辞（LCP） | lcp | 2 つの文字列の先頭から何文字が一致するかの長さ。文字列の接尾辞どうしについて使うことが多い |

（本文ではどちらにもリンクしていない。足されたら、最初に出る箇所にリンクを付けられる）

## 手引きへの提案

- §2.5 と §13.7 の関係：台帳の summary が「（執筆時に確かめる）」のとき、§2.5 は「自分の言葉で書いて台帳の修正を提案」、§13.7 は「本文だけ直さず提案」とある。今回は §2.5 に従って本文に書き、提案もした。どちらに従うかを §13 に一行足すとよい
- SVG を手元で画像にする道具（rsvg-convert・cairosvg など）がないので、見た目を確かめられなかった。文字の幅を概算して viewBox からはみ出ないことだけ確かめた。検証役が見るか、道具を入れるとよい

## 問題の補充の候補

足さなくても数の目安（例題 2・練習 3・力試し 3、abc319 以降 3 問）を満たしているので、補充の候補は出さない。

## 未解決の点

- abc331_f の解法の詳細で「入力は 1-indexed の閉区間なので $[L-1, R)$ に直す」と書いた。第三者の解説の記法（S[L..R]）からそう判断したが、問題文は開いていないので検証で確かめてほしい。制約（N・Q の上限）は書いていない
- related の palindrome#manacher に合わせたいが、palindrome は stub なので節へはリンクせず、ページへのリンクにした。hash-safety も stub なので節へのリンクはしていない（birthday-bound・mod-2-64 などが draft になったら張り替えられる）
- 本文で fenwick-tree（../ds/fenwick-tree.md、骨格あり）へリンクした
- 力試しの並び：typical90_au は difficulty がないので、★7 を水〜青の上位とみて先頭に置いた
- 図の priority は 2（静的）なので、動く図は作っていない
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 11 回（うち curl で題名の確認 1 回、画像の取得 1 回）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜8 はすべて直した（採らなかったものはない）
    - 1：abc331_f の解法の詳細で、更新の $x$ も $x - 1$ に直すと明記した
    - 2：#collision-bound に「$(L-1)/p$ は保証の上界、多くの組の見積もりでは約 $1/p$ とみなす」を足し、#recommended-design の $10^6$ 個の文を期待値約 $2 \times 10^{-7}$ の形に直した
    - 3：「前の節のコード」を「多項式ハッシュの節のコード」に直した
    - 4：3 片の `B` をその場で呼ぶラムダから `random_base()` 関数に変えた
    - 5：longest-repeat の二分探索を `if (check(mid)) ok = mid; else ng = mid;` にした
    - 6：2 枚の図から、本文と代替テキストが言っている説明の行を外し、viewBox の高さを詰めた（prefix-hash 336→248、segtree-merge 310→262）
    - 7：ABC430 E の記録を「基数 2 と有名な法の組で衝突した」に狭めた
    - 8：mod $2^{64}$ の衝突の作り方は hash-safety に任せるリンクを足した

### 提案（共有ファイル）

- hash-safety を書くときに、mod $2^{64}$ が長さ 1024 程度で衝突する構成（Thue-Morse 列）と、その出典を載せる。rolling-hash の #recommended-design はそこへリンクしている
- hash-safety に「多くの組を比べるとき 1 組あたり約 $1/p$ とみなす根拠と限界」を載せる（rolling-hash の #collision-bound がリンクしている）
