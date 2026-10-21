# hash-safety の報告と提案（b2）

- 書いたファイル：docs/string/hash-safety.md、snippets/hash-safety/{thue-morse,random-prime,unordered-attack}.{cpp,yaml}、docs/img/hash-safety/birthday.svg
- front matter で変えたもの：complexity・stage（draft）。updated は今日のまま。sections は変えていない
- 検査：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 3 本・期待と違う0、textlint エラー0（警告 14。数式の中の半開区間 `[2^{60}, 2^{61})` の括弧の対、数式を含む文の長さ、図の代替テキストの長さ、助詞の重なりの軽いもの）
- 図：birthday.svg を render_svg.py で 360px・720px にして目で確かめた
- 動く図：作っていない（catalog の visual は priority 2 の静的な図で、SVG で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc339_f | evidence に追加 | https://noshi91.hatenablog.com/entry/2024/02/06/222907 、https://programming-hiroba.com/abc339-f/ | 乱択した素数の mod の確率の評価（noshi91）、制約 N ≤ 1000・A_i ≤ 10^1000 と解き方（プロひろ） |
| abc339_f | evidence | 1 件目の https://merom686.hatenablog.com/ （トップページ）を外す | 個別の記事（2024/02/04/021920）だけで足りる |
| abc141_e | evidence に追加 | https://perogram.hateblo.jp/entry/2019/09/16/103911 | hash-safety の approach「固定の mod・基数がテストに衝突し、基数を変えて回避した記録」の裏付け。記事は「1 本で WA、法だけを変えた 2 本でも WA、基数も変えると WA は消えたが TLE、一致した候補を直接比べて AC」。法と基数の具体的な値は書かれていない |
| abc141_e | hash-safety の approach | 長さの二分探索とハッシュ。1 回の判定で約 1.25×10^7 組を比べるので、法が 10^9 程度の 1 つでは衝突しうる。1 本のハッシュで WA になり、法だけ変えても消えなかった記録がある | 上の perogram の記事。「基数を変えて回避」は、基数も変えた 2 本で WA は消えたが TLE になった、が正確 |
| typical90_au | checked | 2026-10-21 | 問題文（GitHub の problem-txt/047.txt）と解説 047-01・047-02.jpg を読んで確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 誕生日のパラドックス | birthday-paradox | $p$ 通りの値から $K$ 個を一様に選ぶと、どれか 2 つが一致する確率は $K$ が $\sqrt{p}$ 程度で 1/2 に届くこと。ハッシュの衝突は比較の回数ではなく組の数 $K^2/2$ で見積もる |
| 衝突（ハッシュの） | hash-collision | 異なるものが同じハッシュ値になること。ハッシュで一致を判定すると、衝突したときに誤って「等しい」と答える |

本文では用語集へのリンクを張っていない（どちらも本文の節で説明している）。足すなら本文の初出にリンクしてよい。

## 手引きへの提案

- §5 string：「ハッシュは衝突の確率と mod・基数の選び方（乱択）に必ず触れる」に、「値そのものの mod（巨大な整数）は基数がないので法の素数を乱択する。持ち主は hash-safety#what-to-randomize」を足すとよい（randomized・big-integer 系のページで同じ説明を繰り返さないため）
- §9：Miller-Rabin のように素数判定の中だけで使う短い型の別名（`u64`）も「型の別名は使わない」に当たるとして `unsigned long long` に書き直した。長い宣言が続く数論のコード片では読みにくくなるので、例外にするかを決めてほしい

## 問題の補充の候補

ハッシュの設計が結果を分けたと第三者の記事で確かめられた新しい問題は、今回は見つからなかった（検索 2 回）。

- abc284_f：検索結果の抜粋に「法を 2^64 にして WA と TLE が多発し、2^61−1 で通った」という記録があるが、出典の記事を特定できていない。読んだ Qiita（hyouchun「ABC284-F ABCBAC (Python)」https://qiita.com/hyouchun/items/9ec478e01d145c32aed9 ）にはその記述がなく、法と基数をどちらも乱択していた。出典が見つかれば hash-safety の練習に足せる（台帳では z-algorithm の例題・rolling-hash の練習）
- 本文の確認問題に、巨大な整数の和（$A_i + A_j = A_k$）を入れた。同じ形の ABC の問題があれば練習に足せる

## 未解決の点

- check_pages は `../string/hashing-for-sets.md#random-values` を「anchor がない」とした。hashing-for-sets の見出し `## 値ごとに乱数を割り当てる理由（値そのものを足すと {1, 4} と {2, 3} が衝突する） {#random-values}` は、見出しの中の `{1, 4}` の波かっこで attr_list の解釈が崩れている可能性がある（check_pages が拾えないなら、サイトでも anchor が付かないかもしれない）。本文はページへのリンクにした。hashing-for-sets の見出しの言い換えか、check_pages の確かめを頼みたい
- ikatakos 氏の ABC141 の記録（研究の evidence）は 503 で読めなかった。abc141_e の記述は perogram の記事だけで裏付けた
- unordered_map への攻撃の数値（10^5 個で 3.2 秒、2×10^5 個で 17.5 秒）は手元の g++-15・-O2 の 1 回の計測である。バケットの数の列（172933・351061）は libstdc++ の実装による。g++-13 でも unordered-attack.cpp の期待（いちばん混んだバケットに n 個）は通った
- AtCoder の固定のテストに unordered_map を狙う入力が実際に入った問題は確かめていない。本文では「入っていれば既定のハッシュでは避けようがない」とだけ書いた
- 典型90 047 のテストに mod 2^64 を落とす入力が実際にあるかは確かめていない。本文は「作問者の解説が注意している」にとどめた
- 「1 組あたり 1/p とみなす根拠と限界」（rolling-hash からのリンク先）は、birthday-bound の中の小見出し「1 組あたり 1/p とみなす根拠と限界」に書いた。小見出しには anchor を付けていない。rolling-hash の 103 行目は #birthday-bound へ張り替えるとよい。rolling-hash の 102・109・114 行目は、それぞれ #birthday-bound・#recommended-design（または #mod-2-64）・#mod-2-64 が合う

## 使った出典と noai の確認

- 新しく check_noai.py で確かめたドメイン：perogram.hateblo.jp（noai・noimageai の指定なし）。付録 B に足してほしい
- 付録 B のドメインで読んだもの：qiita.com（keymoon・hyouchun）、maspypy.com、noshi91.hatenablog.com、merom686.hatenablog.com、programming-hiroba.com、github.com（E869120 の problem-txt と editorial の画像）、drken1215.hatenablog.com（題名だけ）
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 9 回（失敗 2 回を含む）、検索 3 回

## 検証の指摘への対応（b2 verify）

- 直したもの：1（87・201 行目を「奇数の基数なら長さ 1024、どの基数でも Thue-Morse の組に同じ 64 文字を付けた長さ 1088」に）・2（箇条書きと要点の計算量・前提の各行に句点）・3（集合なら $2^{-64}$、多重集合でもごく小さい、と hashing-for-sets へのリンク）・4（Miller-Rabin を docs/math/miller-rabin.md へリンク。stub なので anchor なし）・5（「全部の組を 1 組ずつ比べるわけではないが」）・6（図の帯のラベルを帯の左上に 2 行で置き、曲線と重ならないようにした。360px・720px で目視）・7（代替テキストを「10^8 を過ぎてから立ち上がり、10^10 でほぼ 1」に）・9（keymoon 氏の計測の ABC141 E を `#practice` へリンク）
- 採らなかったもの：8（練習問題の追加）。候補の abc284_f は「mod 2^64 で WA」の記録の出典を今回も特定できておらず、確かめられない問題は足さない。frequency C のページなので練習 1 問のままとし、メインの判断に任せる
- 検査：check_pages エラー0・警告0、fix_problems --check 直すべき行0、check_snippets 期待と違う0、textlint エラー0（警告 14、内容は執筆時と同じ種類）
