# twelvefold-way の報告（b5）

- 書いたファイル：docs/comb/twelvefold-way.md、docs/img/twelvefold-way/table-n4-k3.svg（render_svg で目視済み）。snippets はなし
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections は変えていない
- 検査：check_pages エラー0・警告0、fix_problems --check 直すべき行0、textlint エラー0（警告9：数式・見出しの「も」の重なり、数式を含む文の長さ、参考の題名の「「」の連続。誤検出として残した）
- 12 マスの値（n = 4, k = 3：81・0・36／15・0・3／14・0・6／4・0・1、n = 2, k = 3 の単射の列 6・3・1・1、p(6,3) = 7 とちょうど 3 個の 3）は手元の全探索で確かめた
- 出典：drken「「写像12相」を総整理！」（qiita.com、付録 B にある）。表の式と P(n,k) の定義（k 個以下）を照合した

## 台帳への提案

- なし。hub の catalog どおり問題は持たず、各マスの例題（stars-and-bars#abc185_c、bell-number#abc390_d、partition-number#abc226_f、inclusion-exclusion の abc242_f）は行き先のページに任せた

## 用語集への提案

- 写像 12 相を用語集に置くなら：写像 12 相｜twelvefold-way｜n 個の玉を k 個の箱に入れる方法を、玉・箱の区別の有無（4 通り）と各箱の個数の制限（制限なし・1 個以下・1 個以上）で 12 通りに分けた表。（ページがあるので語の項目は不要かもしれない。メインの判断）
- 分割（整数の分割）｜integer-partition｜正の整数 n を、順序を区別せず正の整数の和で表したもの。各項を部分と呼ぶ。（partition-number・twelvefold-way が使う。set-partition と取り違えやすい）

## 手引きへの提案

- §5 comb の p(n,k) の注意に「本サイトは partition-number・twelvefold-way とも『部分が k 以下（= k 個以下）』に統一。ちょうど k 個は p(n−k,k)」と持ち主を書き添える（b3 handoff §2 の申し送りの決着）
- 記法（start/notation）：${}_k P_n$（counting-basics と同じ）を使った。Iverson の記法は使わず「n ≤ k なら 1」と言葉で書いた。notation に Iverson を足すなら、このページの単射の列も $[n \le k]$ に直せる

## 問題の補充の候補

- AOJ DPL_5_A〜L（12 マスに対応する練習。AtCoder 以外）。onlinejudge.u-aizu.ac.jp は check_noai で noai 指定なし（2026-10-22）。ただし各問題がどのマスかは drken の記事に 6 問（D・F 重複組合せ、G ベル数、I スターリング数、J・L 分割数）しか明記がなく、残りを確かめられなかった（API の取得が失敗）。§15-5 の Library Checker と同じ扱い（練習の節にふつうのリンク）を AOJ にも認めるなら、対応を確かめたうえで足せる
- AtCoder の問題は新たに探していない（hub は 0〜3 問で、catalog は「持たない」）

## 未解決の点

- 生成ブロックはこのページにない（--list-blocks で確認）
- stars-and-bars:161 は「箱の順番を区別しないなら、分割数など別の数」と書いている。玉を区別するなら S(n,k) 系なので、「玉も区別しないなら分割数、玉を区別するならスターリング数」と直すとこのページと食い違わない（stars-and-bars の次の直しで）
- 動く図（catalog の研究メモにある「マスをクリックで全列挙」）は visual が static・priority 2 なので作らず、静的な SVG にした

## 検証の指摘への対応（b5 verify）

- 1（直すべき）：#table の境界の段落に $\binom{n+k-1}{n} = \binom{-1}{0}$ も挙げ、「$n = 0$ は式に入れず別に扱う」と書いた。#surjection の二項係数の系統の恒等式・包除の式の 2 つ目に「$n \ge 1$ で成り立つ」と添えた
- 2：1 個以下の列の段落に、箱を区別しない 2 行が $n \le k$ で 1 になる理由を 1 文足した
- 3：`## 確認問題 {#quiz}` を参考の前に立て、2 問を移した（sections には載せない）
- 4：図の式を「S(n,0)+…+S(n,k)」にして本文とそろえた
- 5：図の添字を font-size 9.5 にし、${}_kP_n$ の行を 3 上げて枠への接触を防いだ（render_svg の 360px で目視）
- 採らなかった指摘：なし
