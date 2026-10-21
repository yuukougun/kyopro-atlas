# exponent-mod の報告（工程8b・バッチ b1）

- 書いたファイル：docs/math/exponent-mod.md、snippets/exponent-mod/tower-prime.{cpp,yaml}、snippets/exponent-mod/tower-general.{cpp,yaml}、docs/img/exponent-mod/powers-mod-7.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（このページの直すべき行 0。harmonic-sum.md に 7 行あるが担当外）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 11。数式を含む文の長さ・読点、台帳の要約の行の長さ、助詞の重複の誤検出）
- 図：catalog の visual（static・priority 2）を静的な SVG 1 枚にした（法 7 で底 3 は 6 回、底 2 は 3 回で 1 に戻る 2 つの円）。描画の道具がなく目視での確認はしていないので、検証のときに表示を見てほしい
- 確かめた事実：コード片の値と、一般化（余り + φ(m)）の塔の計算は Python の総当たり（底 0〜4・高さ 4 以下・法 1〜79 の 56880 通り）で直接計算と一致した。素数の法の場合分け（底が p の倍数・0^0）も p = 2〜13 で総当たりした。998244352 = 2^23 × 7 × 17、pow_mod の制約は ACL v1.6 の document_ja と third_party のソースで確かめた。Library Checker の Tetration Mod の約束（0^0 = 1、A, B ≤ 10^9、M ≤ 10^9）は GitHub の library-checker-problems の task.md で確かめた
- 使った出典：参考の節のとおり。新しく noai を確かめたドメインはない（judge.yosupo.jp・github.com・qiita.com・hatenablog・cp-algorithms.com は付録 B にある。cp-algorithms は式の確認だけで文章は使っていない）

## 台帳への提案

- abc228_e｜checked｜2026-10-21｜evidence の kazun・kyo-pro の解説で、問い（M^(K^N) mod 998244353、N, K, M ≤ 10^18）と場合分け（M が p の倍数なら 0）を確かめた
- abc222_g｜checked｜2026-10-21｜evidence の kazun の解説で、問い（T ≤ 200 ケース、K ≤ 10^8）と方針（10^n ≡ 1 (mod L)、L = 9K または 9K/2、φ(L) の約数）を確かめた
- abc212_g｜pages に {id: exponent-mod, role: practice} を足す｜素数 P で x^n の取りうる値を数える問題で、累乗の周期が P − 1 の約数になること（このページの fermat の節）が出発点。evidence は台帳の drken の記事（https://drken1215.hatenablog.com/entry/2021/08/01/163600）。ただし本体は euler-phi の例題なので、重複が気になるなら見送ってよい

## 用語集への提案

- 互いに素｜coprime｜2 つの整数の最大公約数が 1 であること。crt のページも同じ anchor でリンクしているので、まだなければ足してほしい

## 手引きへの提案

- 「ACL では」の囲みを置く位置に見出しを付けるか（定型の見出しに `## ACL では {#acl}` を足すか）が §13 で決まっていない。今回は見出しを付けず、落とし穴の後に囲みだけを置いた

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

練習が abc222_g の 1 問だけで、abc319 以降の問題もない。ap.py の検索（Tower・Power・Exponent・Fermat・Euler・累乗・べき・塔）と Web の検索では、指数を p − 1 や φ(m) で割ることが主役の ABC の問題は新たに見つからなかった。

- abc212_g（G. Power Pair、diff 2150。台帳で確認済み）：素数 P について x^n ≡ y となる組の数。上の台帳への提案のとおり練習に足せる。裏付け：https://drken1215.hatenablog.com/entry/2021/08/01/163600
- tenka1_2017_f（F. ModularPowerEquation!!、diff 3653。ap.py で実在を確かめた）：A^K ≡ K (mod M) となる K を求める問題で、法を φ に置き換えて再帰する一般化（黄の節）の典型と記憶しているが、第三者の解説で問いを確かめていない。発展の帯なので、確かめられても力試しか参照にとどめる
- Library Checker の Tetration Mod（verify に既にある）：一般の法の節の確認用。AtCoder の問題ではないので台帳の対象外

## 未解決の点

- tower-general.cpp は塔を配列で受け取る形にした。Library Checker の Tetration Mod（高さ B ≤ 10^9）にそのまま出すには、上の O(log m) 段だけを扱う形に直す必要がある（本文ではそう書いた）。自作ライブラリにするときの形はメインで決めてほしい
- 一般化の条件を本文では「n ≥ φ(m)」（コードで使う境目）と「n ≥ log2 m」（よく見る形）の 2 通りで書いた。証明は折りたたみに置いた
- 例題の問題 ID が mod-pow の練習にも載っている（台帳どおり）。mod-pow 側で M が p の倍数の場合分けに触れるなら、このページの base-multiple の節へリンクするとよい
