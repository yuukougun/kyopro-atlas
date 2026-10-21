# binomial-precompute の報告と提案（工程8b・b1）

- 書いたファイル：docs/comb/binomial-precompute.md、snippets/binomial-precompute/{binom,large-n,pascal,lucas,exact}.{cpp,yaml}、docs/img/binomial-precompute/{fact-ifact,pascal-mod2}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（5 本・期待と違う 0）、textlint（エラー 0・警告 13）。残った警告は、数式を含む文の助詞の重なりと長さ、画像の代替テキストの長さ、台帳の summary から作った問題の行（287 行目）で、規則の誤検出か台帳の文として残した
- 図：catalog の visual（static・priority 2）どおり、fact を前から・ifact を後ろから作る図と、パスカルの三角形の mod 2 の図（n = 0〜15）を SVG で置いた。動く図はない
- 使った出典：drken1215.hatenablog.com（abc156_d・abc132_d・arc117_c・agc043_b・abc281_g の解説。題名は各ページの title で確かめた）、github.com（鉄則本の解答コード A30、ACL の document_ja/modint.md）。新しいドメインはない
- 事実の確認：ACL の `static_modint::inv()` は法が素数のとき `assert(_v)` で 0 の逆元を止めること、`dynamic_modint::inv()` は gcd が 1 でないと assert で止まることを third_party/ac-library/atcoder/modint.hpp で確かめた。$\binom{66}{33} < 2^{63} < \binom{67}{33}$、掛けてから割る方法が long long のまま安全なのは $n \le 61$ まで（$k \le n/2$）であることを Python で確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| agc043_b | approach | 最初に 1 回差を取って 0・1・2 の列にすると、最後の値の偶奇は C(N−2, i) mod 2 を係数にした和で決まる（差の絶対値は偶奇だけなら和と同じ）。C(n, k) が奇数 ⇔ (n & k) == k。偶数なら 1 を含むかで場合分けし、含まなければ 2 で割って偶奇を見直す | https://drken1215.hatenablog.com/entry/2020/03/22/165200 |
| arc117_c | approach（補足） | 第三者の解説は Lucas の定理ではなく、階乗から 3 の因数を除いて指数を数える任意の法の nCr で求めている。本文は Lucas の定理（p = 3）で書いた。どちらでも解けるので approach は今のままでよいが、「Lucas の定理か、3 の因数を数える方法で」と書き足すと正確 | https://drken1215.hatenablog.com/entry/2021/06/12/001400 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 逆階乗 | inverse-factorial | 階乗 $i!$ の、法 $p$ での逆元 $(i!)^{-1}$。二項係数の前計算で階乗の表と組にして使う |

（本文からは用語集へリンクしていない。別名の行に「逆階乗」があるので、用語の索引に載せるなら上の定義を使える）

## 手引きへの提案

- sections に「ACL では …」の節（anchor: acl）があるページでは、§4 の「ACL では」の囲みをその節の中に置いた。中身の節として ACL の節を持つページと、囲みだけのページの両方があるので、どちらにするかを §4 か §13 に書いておくとよい
- 基礎のページの §4 の目安（要点 → 応用の型 → 落とし穴 → 上位の手法とのつながり → 問題）に対し、このページは sections が 8 つあり、上位の手法とのつながり（Lucas の定理・ピラミッド）が青の節として sections にあるので、「上位の手法とのつながり」の独立した節は作らなかった

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc145_d（diff 1009、台帳で確認済み。今は lattice-paths の例題） | ナイトの動きで (X, Y) へ行く方法の数。(X+Y)/3 回の移動のうち一方の動きの回数を決めると二項係数 1 つになり、表の大きさは X+Y の 1/3 程度まで要る。表の大きさの節の練習として practice に足す案 | https://drken1215.hatenablog.com/entry/2020/04/26/180000 |

基礎の練習が ABC2 問（abc156_d・abc132_d）と少ないので、abc319 以降で、表の大きさが 2N や N+K になる ABC の E を 1 問足したい。台帳の recent（abc453_e・abc458_e など）は前提として届く問題で、この手法を主に使うかは確かめていない。

## 未解決の点

- 鉄則本 A30 の制約（n の上限）は第三者の資料で確かめきれなかった。本文では制約に触れず、「1 回だけ答えるなら表は要らない」と書いた
- arc117_c・agc043_b は青の問題で、基礎のページの練習としては難しい。catalog どおり practice に置いたが、challenge に移す案もある（役割の変更は catalog の判断に任せる）
- 計算量の front matter の文字列が長い。要点の計算量と同じ内容なので、短くするなら「前計算 O(N + log p)、1 回 O(1)（N < p）」だけにしてもよい
