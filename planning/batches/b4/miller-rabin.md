# miller-rabin の報告と提案（b4）

- 書いたファイル：docs/math/miller-rabin.md、snippets/miller-rabin/factorize.{cpp,yaml}、docs/img/miller-rabin/rho.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `library`（自作するときの要点と確かめ方）を足した。波かっこと `__` を見出しから外すため、deterministic-bases の title を「決定的な底（32bit は 2・7・61、64bit は 7 個の底）」に、mulmod の title を「64bit の法での掛け算（128 bit 整数・Montgomery・Barrett）」に直した（anchor は変えていない）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 1 本 OK、textlint エラー 0（警告 15：数式を含む文の長さ・読点の数・「にも」「も」の重なり。数式の中の読点や自然な「1 にも −1 にもならない」の誤検出として残した）
- 図：rho.svg（n = 533 = 13 × 41、c = 3、x₀ = 2 の列の mod 13 が ρ の形になり、x₅ と x₁₀ が出会う）。render_svg で目視した
- 使った出典：drken1215.hatenablog.com の 2 記事、cp-algorithms（Primality tests・Integer factorization。事実だけ使い文章は使っていない）、en.wikipedia.org（Miller–Rabin・Pollard's rho・Montgomery）、ACL のソース、library-checker-problems の info.toml・task.md・sol/fixed_RNG.cpp。新しいドメインはない

## 台帳への提案

- なし（catalog のとおり problems は空。例題 0）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| カーマイケル数 | carmichael-number | 合成数なのに、互いに素なすべての a で a^(n−1) ≡ 1 (mod n) となる数。最小は 561 = 3 × 11 × 17。フェルマーの小定理だけの素数判定では見抜けない |
| 証拠（witness） | witness | Miller-Rabin で、n が合成数であることを示す底 a。素数なら起きるはずの「a^d ≡ 1 か途中に −1」がどちらも起きない |
| Montgomery 乗算 | montgomery-multiplication | 奇数の法 n で、値を xR mod n（R = 2^64 など）の形で持ち、n での割り算を掛け算とシフトに置き換えて積の余りを求める方法 |

## 手引きへの提案

- §5 math か §15-12 に「64bit の法の掛け算の持ち主は mod-pow（`__int128` の書き方）、Montgomery・Barrett と Miller-Rabin の底の注意は miller-rabin#mulmod・#deterministic-bases」と書き分けると、b3 handoff §3 の「`__int128` の mulmod の置き場」の項が閉じる。このページは mod-pow#pitfalls と cpp-integer-overflow#int128 へリンクした
- hash-safety の「Miller-Rabin」へのリンク（b3 handoff §1.2）は `miller-rabin#deterministic-bases` へ張り替えられる

## 問題の補充の候補

- 必須の ABC 問題は見つからなかった（ap.py で Prime・Factor・素数・素因数を検索、Web 検索でも第三者の解説で「Pollard's rho が必須」とする ABC は見つからない）
- abc284_d（D. Happy New Year 2023、diff 658）：N = p²q（N ≤ 9 × 10^18）の p・q を求める。小さい方が立方根以下なので試し割りで足り、「構造で避ける」型の練習になる。ただし第三者の解説の URL を確かめられていない（ikatakos 氏の記録は E〜G だけ、kmjp 氏の記事は URL を見つけられず、codeforces は開かない）。本文では問題 ID を出さずに型だけ書いた。裏付けが取れれば、prime-factorization か divisor-enum の練習の候補（このページの例題には合わない。難しさが基礎）

## 未解決の点

- 「1 つあたり 1 秒よりずっと短い時間」は手元のコード片（10^9 程度の 2 素数の積を含む 3 ケースが合わせて 1.3 秒の検査に収まる。コンパイルを含む）からの控えめな見積もりで、厳密な計測ではない
- rho の期待 O(√p) は列を乱数とみなす発見的な見積もりで、本文にもそう書いた
- Barrett 還元の 64bit の法での扱いは本文に書いていない（ACL の 32bit 版だけに触れた）

## 検証の指摘への対応

- 指摘 1〜4 はすべて直した。確認問題の 1 問目は $n = 85 = 5 \times 17$、すり抜ける底 $13$（$13^{21} \equiv 13$、$13^{42} \equiv -1$）、証拠の底 $2$（$32$、$4$）に替えた（Python で計算し直した）。2 問目の答えは素数べきで言い直し、`dynamic_modint` の法は「$2 \times 10^9$ 程度まで」とした。コード片の `find_factor`・`factor_rec` の約数の変数を `g` にそろえた
- 採らなかった指摘はない。共有ファイルへの新しい提案はない
