# binary-trie の報告（b2・執筆）

- 書いたファイル：docs/ds/binary-trie.md、snippets/binary-trie/{trie,min-pair,implicit}.{cpp,yaml}、docs/img/binary-trie/xor-min.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の kth-and-global-xor の title を「K 番目と全体への XOR（bit ごとの反転フラグ）」に変えた（prh.yml が「ビットごと」を「bit ごと」に直すため。anchor は同じ）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 3 本とも一致、textlint エラー 0（警告 13：数式を含む文の長さ・数式内の括弧・助詞「に」の重なり）。図は render_svg で 360px・720px を目で確かめた
- 使った出典：drken1215.hatenablog.com（abc281_f）、merom686.hatenablog.com（abc308_g）、judge.yosupo.jp（set_xor_min）。kmjp.hatenablog.jp（arc122_d、候補の裏付け）。新しく check_noai を通したドメイン：www.acwing.com（noai の指定なし。ただし取得すると 403 のページへ転送され、中身は読めなかった）
- 動く図：作らない（visual は priority 2。静的な SVG で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc308_g | checked | 2026-10-21 | https://merom686.hatenablog.com/entry/2023/07/02/004802 （部分木ごとに 2 要素の XOR の最小を持ち上げる Binary Trie の解） |
| abc308_g | evidence | acwing の URL を外すか残すかを決める | acwing は転送先が 403 で読めなかった |
| abc425_g | checked | 確かめられなかった（null のまま） | evidence の ikatakos.com が 503 で読めなかった。本文の練習のヒントは、snippets/binary-trie/implicit.cpp の再帰（全探索と比べて確かめた）から書いた |

## 用語集への提案

- なし（ぶら下がり参照 `#dangling`・オーバーフロー `#overflow` は既存の anchor を使った）

## 手引き・catalog・ほかのページへの提案

- catalog の binary-trie の sections に残る choosing・pitfalls は、§14-1・2 に従い本文では定型の節（#comparison・#pitfalls）にした。catalog を凍結のまま扱うなら変更不要
- docs/index/ds.md など生成部分の節名「ビットごとの反転フラグ」は、gen_site で「bit ごとの反転フラグ」に変わる
- ordered-set#adjacent-pairs の本文「最小の組がソート順で隣り合う点は同じ」の証明を、binary-trie#comparison に書いた。ordered-set からは binary-trie#comparison へリンクを張り替えてよい
- bitwise-independence の #split-by-top-bit と #comparison の「Binary Trie」へのリンクは、#implicit・#xor-min-max へ張り替えてよい（handoff 361 行の件）
- kth-element:74・trie:299・ordered-set:155 の binary-trie へのリンク（handoff 229 行）は、それぞれ #kth-and-global-xor・#build・#comparison へ張り替えられる

## 問題の補充の候補

| 問題 ID | 役割の案 | 何を問うか | 裏付けの URL |
| --- | --- | --- | --- |
| arc122_d（D. XOR Game、diff 2331） | 力試し | 2N 個の整数を 2 人が交互に取り、組の XOR の最大値を先手は大きく後手は小さくしたいときの値。上位 bit で分けて、両側が偶数個なら再帰、奇数なら 2 つの集合をまたぐ組の XOR の最小を Binary Trie で求める | https://kmjp.hatenablog.jp/entry/2021/06/13/0930 |

- 練習が 1 問（abc425_g）だけで、目安の 2〜6 に足りない。abc319 以降で Binary Trie を主に使う ABC の E・F は、ap.py の題名検索（xor）では見つからなかった。「XOR」を題名に含まない問題は題名からは探せないので、工程の問題の補充で第三者の解説のタグ（Binary Trie）から探すのがよい

## 未解決の点

- abc425_g の evidence（ikatakos）を読めなかった。台帳の summary の問いは確かめていない（本文の行は台帳の summary のまま）
- abc308_g の問いの細部（削除は入っている値だけか、質問の時点で 2 個以上あるか）は merom686 の記事に書かれておらず、確かめていない。本文では台帳の summary だけを使い、方針の折りたたみもこの点に依らない書き方にした
- Library Checker の問題名「Set Xor-Min」はページが JS で描かれるため題名を取得できず、記憶で書いた（URL は library-design.md と同じ）

## 使用量の目安

- 道具の呼び出し 約 35 回、Web 取得 6 回（うち失敗 3）、Web 検索 2 回

## 検証の指摘への対応（b2 verify）

- 直したもの：1（#comparison の括弧書きを消し、全体に XOR をかけても 2 要素の XOR は変わらないと一言添えた）、2（全体への XOR の累計を $M$ から $T$ に改め、#implicit の $M$ は「上限 $M$（ABC425 G の記号）」と断った）、3（確認問題 2 に「$B = 2$ の木に」を足した）、4（リンクの語を「ダングリング（ぶら下がり参照）」にした）、5（見出し 2 つと sections の title を「上位 bit から」「たどる」「上位 bit で」に。anchor は不変）、7（min-pair.cpp のコンストラクタで最大ノード数を受け取り 4 本の vector を reserve、path を `array<int, 64>` に）、8（xor-min.svg の凡例 3 行を短くして font-size 18、葉の下のラベルも 18。360px で確認。答えの「4 xor 5 = 1」は本文にあるので凡例から外した）
- 採らなかったもの
    - 6（abc425_g の checked）：本文の直しは不要で、台帳の確認はメインの作業。null のままにする提案は上の「台帳への提案」のとおり
    - 9（練習が 1 問）：問題の追加は台帳の変更なのでメインの判断。候補 arc122_d は上の「問題の補充の候補」のとおり

## 用語集への提案（追記）

- glossary の「ダングリング {#dangling}」に別名「ぶら下がり参照」を足すとよい（本文は「ダングリング（ぶら下がり参照）」と書いた）
