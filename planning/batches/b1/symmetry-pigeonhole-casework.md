# pigeonhole（対称性・鳩の巣原理・場合分け）の執筆の報告

- 担当の指示は `docs/thinking/pigeonhole.md`（基礎・thinking）だったが、そのページはない。鳩の巣原理は catalog で `symmetry-pigeonhole-casework` の節（#pigeonhole）に統合されている（merged_keys に pigeonhole）。id と URL は変えない規則なので、`docs/thinking/symmetry-pigeonhole-casework.md`・`snippets/symmetry-pigeonhole-casework/`・`docs/img/symmetry-pigeonhole-casework/` に書いた（crt の担当と同じ扱い）。`snippets/pigeonhole/`・`docs/img/pigeonhole/` は作っていない
- 書いたファイル：docs/thinking/symmetry-pigeonhole-casework.md、snippets/symmetry-pigeonhole-casework/pair-sum.{cpp,yaml}、snippets/symmetry-pigeonhole-casework/pigeonhole-subsets.{cpp,yaml}、docs/img/symmetry-pigeonhole-casework/pair-table.svg、docs/img/symmetry-pigeonhole-casework/pigeonhole-boxes.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages --page symmetry-pigeonhole-casework はエラー・警告とも 0。fix_problems --check は 0。check_snippets は 2 本とも一致。textlint はエラー 0、警告 15（数式を含む文の長さ、数式の中の助詞の重なり、`$[l, r)$` の半開区間を括弧の対応の誤りとみなすもの。誤検出として残した）
- 図：visual は priority 2（static）。catalog の指定どおり、i < j の積の表（対角より上を塗り、対角に斜線）と、3 つの箱に 4 個の玉（7, 77, 777, 7777 の mod 3）の SVG を作った。SVG を画像に変換する道具が手元になく、見た目は確かめていない（XML として読めることだけ確かめた）。メインか検証役で表示を確かめてほしい
- 使った出典：E869120（Qiita、対称性と abc177_c）、hamayan（arc091_a）、oraclesqlpuzzle（abc200_d・abc174_c）、m193h（zenn、abc200_d の 201 個）、hyouri・bit_otter（Qiita、abc471_e）、comet725（Qiita、abc462_e）、ikatakos（abc462_e、解法の部分だけ）、drken（abc171_e、本文の XOR の型の出典。問題 ID は本文に出していない）
- 新しく noai を確かめたドメイン：なし（zenn.dev は付録 B にあり、記事を tools/check_noai.py で確かめて指定なし）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc471_e | summary | N 個の整数から K 個を選ぶすべての選び方について、選んだ数の和の 2 乗を足し合わせた値を 998244353 で割った余りを求める。 | https://qiita.com/bit_otter/items/b032b01dcf3ab95a042e 、https://qiita.com/hyouri/items/941cbb14aaf4c810fa90 。本文の行はこの値で書いた。alternatives（sigma-manipulation）の summary も同じ値でよい |
| abc471_e | approach | 和の 2 乗を展開し、A_i^2 は C(N−1, K−1) 回、i < j の組は C(N−2, K−2) 回現れることから、C(N−1, K−1) S2 + C(N−2, K−2)(S1² − S2) で求める（対称性） | 同上 |
| abc462_e | summary | 原点から上下左右に 1 マスずつ動き、奇数回目の移動は横が A・縦が B、偶数回目は横が B・縦が A のコストがかかるとき、(X, Y) へ行く最小のコストを求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0613_abc462 （解法の部分）、https://qiita.com/comet725/items/2edf7be7b7b4cd846d29 （入力は複数のテストケース）。本文の行はこの値で書いた |
| abc462_e | approach | X, Y を絶対値に直し、A > B なら A と B、X と Y を一緒に入れ替えて場合を減らしてから、斜めの部分と残りに分けて最小を求める（対称性） | 同上 |

## 用語集への提案

- なし（逆元は math/mod-inverse へ、半開区間は本文で式とともに使っただけ）

## 手引きへの提案

- 任務の指示のページのパスが catalog の id と食い違っていた（pigeonhole ↔ symmetry-pigeonhole-casework）。指示は catalog の id（merged_keys ではなく）から作るとよい
- thinking の構成の目安にある「関連する手法」は、独立の節にすると薄くなるので、各節の末尾のリンクで済ませた。基礎の thinking ではそれでよいと書いておくとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc133_c | L 以上 R 以下から選ぶ 2 数の積の mod 2019 の最小値。幅が 2019 以上なら答えは 0（鳩の巣原理の「範囲が広ければ答えが決まる」型） | practice（台帳では proof-patterns の例題。#pigeonhole の 3 つ目の型の練習として） | https://drken1215.hatenablog.com/entry/2019/07/07/233700 |
| abc179_e | 値が M 種類の漸化式の列の和。M + 1 項以内に同じ値が現れる（鳩の巣原理の「同じ状態に戻る」型） | practice（台帳では periodicity の例題） | https://drken1215.hatenablog.com/entry/2020/09/20/091500 |

- 今の問題（例題 3・練習 3）で thinking の目安（例題 2〜4、全体 5〜6）を満たすので、補充は任意

## 未解決の点

- abc200_d の B と C が「異なる」だけでよく、共通の要素を持ってよいかは、第三者の解説の記述では明言されていない（m193h のコードは重なりを除かずに出力して通っている）。本文は台帳の summary どおり「異なる 2 つの部分列」とし、重なりには触れていない
- abc177_c の剰余の法は解説（E869120）に書かれていないので、本文では法の値を書かず「剰余を取って計算する」とだけ書いた
- abc462_e の残りの部分の式（候補の 2 つ）は解説の要約から細部を確かめきれず、練習の方針では対称性でそろえる部分を中心に書き、残りは「偶奇に注意して候補を比べる」にとどめた
- 確認問題の 3 つ組の式 (S1³ − 3 S1 S2 + 2 S3) / 6 は自分で展開して確かめた（ニュートンの恒等式と一致）

## 使用量の目安

- 道具の呼び出し 約 40 回、Web 取得 約 12 回（WebFetch 10・検索 1・curl で題名の取得）

## 検証の指摘への対応（2026-10-21）

- 直した（docs/thinking/symmetry-pigeonhole-casework.md）：1（オーバーフローで答え自体が収まらないこと・累積和の書き方が効く範囲を書き分け）、3（順序によらない操作は「合計」で決まると修正）、4（R − L + 1 ≥ M と余りの一巡を明記）、5（#pigeonhole-remainder・#four-cycles へのリンクと黄の帯の注記）、6（N が奇数の場合を 1 文追加）、7（ABC471 E の方針を式の手前までにとどめ文を分割）
- 直した（snippets/symmetry-pigeonhole-casework/pigeonhole-subsets.cpp）：8（コメントに a_i ≥ 0 の前提を追記）
- 未対応：2（直すべき：pair-table.svg の添字を A_1〜A_4 に）と 9（図の文字の大きさ・題の長さ）。docs/img/symmetry-pigeonhole-casework/ への書き込みが権限の判定で拒まれた（指示の書いてよい場所が docs/img/pigeonhole/ だったため）。メインで図の直しを許すか、直す必要がある。直し方：セルを A₁A₁…A₄A₄、軸を i, j = 1〜4、題を「積 A_i A_j の表（N = 4）」に短縮し、全体の和 (A_1 + … + A_4)² は下の注へ移す。注と凡例の font-size を 14 に。箱の図も題を短くし注を 14 に
- 検査：本文の直しの後、check_pages・fix_problems・check_snippets・textlint の実行も権限の判定で拒まれ、まだ通していない
