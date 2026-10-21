# z-algorithm の報告と提案（工程8b・b1）

- 書いたファイル：docs/string/z-algorithm.md、snippets/z-algorithm/{own-z,find-all,rotation,period,prefix-concat}.{cpp,yaml}、docs/img/z-algorithm/z-box.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。節 `reverse`（反転と連結する：後ろからの一致と回文の接尾辞、水）を sections に足した
- 骨格の本文にあった catalog の項目の書き出し（要点の囲みの後の YAML）は消した
- 検査：check_pages（エラー 0・警告 0）、check_snippets（5 片すべて一致）、textlint（エラー 0、警告 37 は数式の半開区間の括弧・数式を含む文の長さ・数式の中の読点）、fix_problems --check（このページの行は 0。dp/subset-sum.md に 6 行が残っているが担当外）
- 使った出典：ACL document_ja/string.md（手元と GitHub）、ikatakos（abc430・abc284・abc398・abc257。解説の部分だけ）、drken（abc141_e・arc055_c）、kmjp（abc343_g）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc284_f | approach（z-algorithm） | 前半 X と後半の反転 Y を作ると Y は X の回転になる。Y＋区切り＋X＋X の Z 配列で回転の位置 i を探す | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2023/0107_abc284 （catalog の「区切り位置ごとの両側の一致」より、解説の方法に合わせた） |
| abc257_g | approach | S＋区切り＋T の Z 配列で各位置から伸ばせる長さを得る。dp が単調なので、届く範囲を段ごとに広げる貪欲で O(N) | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0625_abc257 |
| abc398_f | alternatives の z-algorithm の approach | 根拠の URL（ikatakos）は Manacher とハッシュだけで、Z の解き方は書かれていない。Z の方法（rev(S)＋区切り＋S で z = N − j）は本文で証明したが、第三者の裏付けが要るなら URL を足す | — |
| abc343_g | checked など | 変更なし。kmjp の解説が Z で重なりを求めることを確かめた | https://kmjp.hatenablog.jp/entry/2024/03/02/0930 |
| abc141_e・arc055_c | checked | 2026-10-21（解説で問いと Z の方法を確かめた） | 各 evidence の URL |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 最長共通接頭辞（LCP） | lcp | 2 つの文字列の先頭から一致が続く最長の長さ。Z 配列・LCP 配列はこれを位置ごとに並べたもの |
| 周期 | period | 1 ≤ p ≤ N で、すべての 0 ≤ i < N − p について S[i] = S[i + p] となる p。長さ N − p の border があることと同じ |
| border | border | 文字列の接頭辞であり接尾辞でもある部分文字列（文字列全体を除く）。KMP 法の失敗関数は各接頭辞の最長の border の長さ |

本文はこの 3 つの anchor でリンクしている。

## 手引きへの提案

- 付録 A の文字列の語に「Z 配列」「Z-box」「border」「周期」を足すとよい（Z-box はこのページで定義した）
- §13 に「骨格の本文に catalog の書き出し（YAML）が残っているときは消してよい」と明記するとよい（kmp など同じ形の骨格がある）

## 問題の補充の候補

水・青のページには abc319 以降を 1 問以上という目安は abc430_e（例題）で満たしている。追加の候補は探していない（台帳の 7 問で数の目安を満たす）。

## 動く図の仕様（priority 1。JS は未作成）

- 置き場：`<div class="kp-viz" data-viz="z-algorithm" data-config='{"s": "aabaabaac"}'></div>`（節 linear-time）
- 状態：i を 1 から N − 1 へ 1 つずつ進める。各ステップで Z-box [l, r) を枠で示し、場合（1：箱の外・2：写す・3：写してから比べる）を caption に出す。写した値のマスと、比較したマス（成功は色、失敗は斜線）を分ける。下に z 配列の行を埋めていく。最後に「成功した比較の合計 ≤ N」を caption に出す
- 静的な図 z-box.svg（i = 4 の写す場合と i = 6 の比べる場合）は動く図ができた後も残してよい
- palindrome の Manacher の図と部品（箱と対応位置の矢印）を共有する予定（catalog の visual のとおり）

## 未解決の点

- 節の並びで「反転と連結する」を足した。catalog の sections にはないので、凍結した catalog との差になる（front matter が正）
- related の palindrome#manacher・method-comparison#strings は相手が stub なので、本文ではページへのリンクにとどめた
- 周期の補題（Fine-Wilf）を証明の折りたたみで名前だけ使った。定理のページはないので、出典が要るなら足す
- SVG は描画して目で確かめていない（変換の道具が手元にない）。座標で重なりがないことだけ確かめた

## 検証の指摘への対応（2026-10-21）

- 1〜10 はすべて直した
    - 1：Z-box を $1 \le i' < i$ に限り、初期値 $l = r = 0$ と $i' = 0$ を除く理由を添えた。「$r$ がちょうど 1 進む」を「少なくとも 1 進む」にし、成功した比較が読む位置がそれまでの $r$ 以上であることを書いた
    - 2：abc284_f の参考の行を「前半と後半の反転を作り、Z 配列で区切り位置ごとの一致を判定する方法」に直し、回転への帰着は本文で導いたと明記した
    - 3：sections から comparison を消し、見出しを `## 使い分け {#comparison}` にして確認問題の後・参考の前へ移した
    - 4：「図で比べたマスを数えると」を削り、「色と模様で分けてある」にした（動く図の JS を作るときは、失敗のマスを斜線にする仕様に合わせる）
    - 5：z-box.svg の上の題と下の 4 行の説明を短い 2 行にし、viewBox を 500×274、文字を 15〜19 にした。幅 358px（2 倍密度）で描画して確かめた
    - 6：「$y$ をまたぐピース $[a, b)$（$a < y \le b$）を $[a, y)$ に切り詰め、後ろのピースを捨てる」にした
    - 7：Fine-Wilf は弱い形（$p + q \le N$）だけを使い、「周期 $a < b$、$a + b \le N$ なら $b - a$ も周期」の短い証明を添えて互除法で $\gcd$ に至る形にした（出典は不要にした）。記号は $p_0$ にそろえた
    - 8：「偶然通る」をやめ、$\ge$ なら正しく、$=$ で判定すると取りこぼすことを書いた
    - 9：「$1 \le i \le N$ について」と $i = 0$ の扱いを添えた
    - 10：prefix-concat.cpp の条件を `if (j == reach)` にした（check_snippets は通る）

### 台帳への提案（指摘 2 を受けて差し替え）

- abc284_f の approach の提案の根拠：「回転への帰着は本文で導いた（全列挙で検証済み）。解説（ikatakos）は同じ X・Y から `lr + rl`・`rl + lr` の 2 つの Z 配列を作り、区切り位置ごとに両側の一致を判定する」
- checked：abc430_e・abc257_g・arc055_c・abc284_f に 2026-10-21（検証役の提案どおり）
- abc398_f：alternatives の Z の行は残す（全列挙で正しさを確認済み）。第三者の裏付けの URL は別に探す
