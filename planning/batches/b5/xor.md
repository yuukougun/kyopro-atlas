# b5 提案：xor（docs/patterns/xor.md）

- 書いたファイル：docs/patterns/xor.md、docs/img/xor/column-parity.svg（snippets は作っていない。例題は擬似コードで足りるため）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を properties の次に足した（見本の bracket-sequence と同じ形）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、textlint エラー 0・警告 4（数式の `[l, r)` の括弧の対応 2、数式を含む文の長さ 1、リンクの題名の中の「に」の重複 1。どれも誤検出）。図は render_svg で 360・720 の幅を目で確かめた
- 使った出典：drken1215.hatenablog.com（ABC171 E）、oraclesqlpuzzle.ninja-web.net（ABC197 C）。どちらも付録 B にあるドメイン。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc171_e | checked | 2026-10-22 | https://drken1215.hatenablog.com/entry/2020/06/22/122500 （N は偶数、2 ≤ N ≤ 2×10^5、全体の XOR と各 A_i の XOR で答える方針を確かめた） |
| abc197_c | checked | 2026-10-22 | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc197-c.html （区切り方 2^(N−1) 通りの全探索を確かめた） |
| abc171_e・abc197_c | evidence | 2 つ目の裏付けを足す | §15-6 の目標 2 つに届いていない。ikatakos 氏の ABC197 の記録には C の節がなかった（D〜F だけ） |

## 用語集への提案

なし（使った語の単位元・逆元は用語集にある）。

## 手引きへの提案

- pattern のページで、代表の問題がほかのページの例題・練習にあるときの書き方を決めてほしい。今回は表に問題の列を置かず、各節の本文で「代表は [ABC147 D](../basics/bitwise-independence.md#abc147_d)」（例題の見出しへのリンク）や「そのページの[練習問題](…#practice)の ABC365 E」と書いた。表の列に label を文字で並べる bracket-sequence の形は、このページの問題が 2 問しかないので使わなかった
- 箇条書きの句点（§15-2）を付ける機械的な置き換えは、front matter の `- {title: …}` の行にも当たるので注意（自分で一度壊して直した）

## 問題の補充の候補

台帳では確認済みで、ほかのページに載っている問題。xor のページの練習（patterns は 0〜3）に足すなら次が候補になる。

| 問題 ID | 何を問うか | 裏付け |
| --- | --- | --- |
| abc365_e | 長さ 2 以上の全区間の XOR の総和（累積 XOR と桁ごとの数え上げを組み合わせる） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc365-e.html （台帳の evidence） |
| abc201_e | 重み付きの木の全頂点の組のパスの XOR の和（根からの XOR と桁ごとの数え上げ） | https://blog.hamayanhamayan.com/entry/2021/05/15/235842 、https://kanpurin.hatenablog.com/entry/2021/05/15/224226 （台帳の evidence） |
| abc121_d | A 以上 B 以下の整数の XOR（0〜n の XOR の周期と累積の形） | https://drken1215.hatenablog.com/entry/2019/03/09/224100 （台帳の evidence） |

性質を 2 つ組み合わせる abc365_e・abc201_e が、横断のページの練習に向いている。新しい問題は探していない。

## 未解決の点

- ABC197 C の N の上限を一次資料で確かめられなかった（解説記事に制約が書かれていない）。本文は「N が小さいので」とだけ書き、数値は書いていない
- b1 handoff 348 行の bit-operations:179・bitwise-independence:211 の xor へのリンクは、ページへのリンク（anchor なし）のまま。このページが draft になったので、`#overview` に張り替えられる
- 表の最後の行（列全体を同じ値で XOR したものを探す → KMP 法の例題 ABC150 F）は sections に節を持たない。節にするほどの中身がないので、表の行とリンクだけにした

## 検証の指摘への対応（2026-10-22）

- 直したもの：1（#basis の「繰り上がりのない足し算（mod 2 のベクトルの和）」）、2（括弧の性質は「2 つの性質と 2 つの見方のどれか」）、3（Binary Trie のノードに持たせるのは部分木の中の 2 要素の XOR の最小値）、4（全域木に入らない辺ごとの $d(a) \oplus d(b) \oplus w$ を基底に入れる、と書き直した）、5（$0 \oplus \dots \oplus n$ は $n \bmod 4$ で場合分けした式 $n$・$1$・$n+1$・$0$ で決まる）、6（図の破線の括弧をやめ、2 つの 3 に同じ赤の破線の丸と「1 つ目の 3」「2 つ目の 3」を付け、下に「印を付けた 2 つの 3 は打ち消し合う」を足した。render_svg の 360・720 で確かめた）、7（#xor-equals-sum は実装の決め手を消し、#meet-in-the-middle の対角線の注意は代表の段落から切り離して手法一般の注意にした）、8（同じバッチの divisors-and-multiples・mex・kth-and-median・permutation にそろえ、表を「よく出る問われ方｜使う手法（性質）｜ページ｜代表の問題」の 4 列にした。性質は手法の列の括弧へ移した）、9（例題の方針を、何回現れるかを数え N の偶奇がどこで効くかを考える、までにとどめた）
- 採らなかったもの：なし
- メインへの提案（指摘 5 の続き）：前提のページ bit-operations:90 の「$n \bmod 4$ だけで次のように決まる」も、値そのものが 4 通りと読めるので「$n \bmod 4$ で場合分けした次の式で決まる」に直すとよい（担当外なので書いていない）
- 台帳（検証役の連絡の再掲）：abc197_c の pages に `{id: bit-full-search, role: practice}` があるが、docs/basics/bit-full-search.md に ABC197 C の行がない。台帳かページのどちらかを直す必要がある
