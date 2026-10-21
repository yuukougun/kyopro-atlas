# bell-number の検証（b2）

- 対象：docs/comb/bell-number.md、snippets/bell-number/{stirling,partition-xor}.{cpp,yaml}、docs/img/bell-number/stirling-table.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page bell-number`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/bell-number`：stirling 6 case・partition-xor 7 case すべて一致
- サニタイザ（`-fsanitize=address,undefined`）：stirling は n = 0・1・25 で異常なし（n = 26 で符号付きのあふれが出る。本文の「B_26 はあふれる」と一致）。partition-xor は n = 7 の 2 例で異常なし
- partition-xor の正しさ：Python の素朴な全探索（制限成長列で分け方を列挙）と比べ、cases の小さい 4 例と、新しく作った n = 7 の 2 例（全部 1 → 4、3 141 592 … → 380）で C++ と一致
- 数値（Python で S(n,k) の表を作って計算）：S(4,2)=7・S(5,3)=25・S(4,3)=6、図の n = 0〜6 の表と B_0〜B_6 = 1,1,2,5,15,52,203、表の B_8〜B_16 と 3^n、B_9 = 21147 > 3^9 = 19683（N ≥ 9 で 3^N < B_N）、倍率 5.1〜6.9（n = 8〜14）、max_T S(12,T) = S(12,5) = 1379400、Σ_{i<12} B_i = 820988（B_12 の 19.5%）、12! = 479001600、B_25 = 4.64×10^18 < 2^63−1 < B_26 = 4.96×10^19、p(12) = 77、S(n,2) = 2^{n-1}−1、3^5 − 3·2^5 + 3 = 150 = 3!·S(5,3)。すべて本文どおり
- 漸化式・境界・ベル数の二項係数の漸化式とその説明、列挙木の内部の節点の数 B_0 + … + B_{N-1}、空の箱を許すと k! で割れない例（9/6）、第 1 種の係数 n−1：正しい
- 例題 ABC390 D：台帳（確認済み）と label・diff・要約が一致。evidence の yuulis の記事で制約 N ≤ 12・A_i ≤ 10^17、分け方の DFS、set では TLE を確かめた。oraclesqlpuzzle でハッシュ集合が TLE・ソートして数える方法を確かめた。本文の方針・解法の詳細と食い違いなし
- 練習 ABC310 D：台帳と一致。drken の記事で 1 ≤ T ≤ N ≤ 10、最小添字から組を決める全探索、T^N の割り当ては重複して TLE を確かめた
- 参考の 4 つの URL：check_noai で noai の指定なし。題名・内容は書かれたとおり
- 図：値・添字は本文と一致。白背景・viewBox あり・font-family="sans-serif"・相対パス。360px でも数字は読める

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | figure G5 | stirling-table.svg の 2 本の矢印 | 凡例は「実線＝×1、破線＝×3」と区別するが、破線の矢印は長さ 16px（dasharray 6 4）で、720px・360px のどちらの PNG でも実線と見分けられない。矢じりが「25」の文字にほぼ接している | render_svg の PNG を目視。SVG の 91 行目 `y1=252 y2=268` | 破線の矢印を長くする（S(4,3) のセルの上寄りから 25 のセルの上端まで）か、矢印の横に「×1」「×3」のラベルを直接置き、凡例の線種への依存をなくす。矢じりの終点を 25 のセルの上端（y=260 付近）で止める |
| 2 | 直すとよい | fact F2 | recurrence の節「n が大きく k が小さいとき」の最後の文 | 「法は k より大きい素数でなければならない」は条件として強すぎる。必要なのは k! が逆元を持つこと（法と k! が互いに素）で、k より大きい素数は十分条件 | 定義から。たとえば法 = 合成数で素因数がすべて k より大きいときも割れる | 「$k!$ の逆元が要るので、法は $k!$ と互いに素でなければならない（$k$ より大きい素数なら満たす）」とする |
| 3 | 直すとよい | fact F2 | 落とし穴「組に番号を付けて全列挙する」 | 「T^N 通りの全探索は、同じ分け方を T! 回ずつ数える」は、空の組がある割り当て（組の数が T 未満の分け方）には当てはまらない（その分け方は T!/(T−j)! 回）。同じページの落とし穴 1 つ目が述べる「空を許すと k! 回ずつにならない」と食い違って読める | 落とし穴 1 つ目の 9/6 の例と同じ理屈 | 「どの組も空でない割り当てでは、同じ分け方を T! 回ずつ数える」と条件を足す |
| 4 | 直すとよい | clarity U4 | size の節の目安の箇条書き | N ≤ 10、N = 11〜12、N ≥ 14 で、N = 13（B_13 ≈ 2.8×10^7）が抜けている。制約 N ≤ 13 の問題で読者が判断できない | 表の B_13 = 27644437 | 「N = 11〜12」を「N = 11〜13」にして、N = 13 は葉 1 つ O(1) が必須で定数倍に注意、と添える。または N = 13 の行を足す |
| 5 | 直すとよい | fact F5 | 練習問題の節 | 練習が 1 問で、手引き §10 の目安（練習 2〜6）を下回る（執筆者の未解決の点 1） | 手引き §10「練習 2〜6」 | 執筆者の提案（dp_u・typical90_as を practice に足す）をメインが採るか決める。どちらも台帳で確認済みで、vs-subset-dp の節の対比（B_N では無理で 3^N にする）に合う |
| 6 | 直すとよい | fact F7 | recurrence の節「n が大きく k が小さいとき」の包除原理へのリンク | inclusion-exclusion は今 stage: draft で、#surjection の節がある。執筆者の未解決の点 2 のとおり `../comb/inclusion-exclusion.md#surjection` に張り替えられる | docs/comb/inclusion-exclusion.md の front matter（stage: draft、sections に surjection） | メインが張り替える（手引き §14-23） |
| 7 | 直すとよい | code C3 | partition-xor.cpp の core の `found.reserve(4213597);` | 定数が B_12 の直書きで、本文に説明がない。N が小さいときは不要な確保で、読者が「なぜこの数か」で止まる | コードを読んで | コメント「// N ≤ 12 なら葉は B_12 = 4213597 個以下」を同じ行に足す |

## 執筆者の未解決の点について

- 練習が 1 問：指摘 5
- `inclusion-exclusion#surjection`：相手は draft になっている。指摘 6
- recursive-enumeration#pruning・complexity-estimation から #size への張り替え：#size は本文にあり、張り替えてよい（メインの作業）
- 図が静的 1 枚：catalog の visual priority 3 に合い、問題なし

## 台帳への提案

- abc390_d・abc310_d：evidence で問題の内容を確かめた（2026-10-21）。checked はすでに 2026-10-21

## 総合の判定

小さな直しで可。直すべき 0 件・直すとよい 7 件。事実・数値・コードに誤りは見つからなかった。
