# modint の提案（工程8b・バッチ b1）

- 書いたファイル：docs/math/modint.md、snippets/modint/{conversion,dynamic,self-made}.{cpp,yaml}（図はなし。visual は null）
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「上位の手法での使われ方（階乗の表・畳み込み・行列・期待値）」（anchor: connections）を足した（基礎の構成の「上位の手法とのつながり」に当たる）
- 検査の結果：check_pages エラー0・警告0、fix_problems --check 0 行、check_snippets 3 本とも一致、textlint エラー0（警告7：要点の計算量の行と、台帳の要約の行、折りたたみの長い行の助詞の重複・文の長さ。意味を崩さずに直しにくいので残した）
- 使った出典：ACL v1.6 の document_ja/modint.md と modint.hpp・internal_math.hpp（手元）、noshi91「modint 構造体を使ってみませんか？ (C++)」（付録 B のドメイン）、drken の ABC357 D・ABC281 G の記事。新しいドメインはなし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc281_g | alternatives（pages: modint）の summary | 主の summary と同じ「頂点 1 から頂点 N への距離が他のどの頂点への距離よりも真に大きい、N 頂点の連結な単純無向グラフの数を、入力の M（素数とは限らない）で割った余りで求める。」に。いまの「入力の P」は問題の変数名（M）と食い違う。本文は主の summary で書いた | https://drken1215.hatenablog.com/entry/2022/12/13/173300 |
| abc281_g | alternatives（pages: modint）の approach | 「頂点 1 からの距離の層ごとに頂点数を決める DP。M が入力なので dynamic_modint を使い、割り算を避けて二項係数はパスカルの三角形で作る」 | 同上（drken は long long と % で書いているが、法が実行時に決まる点は同じ） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| Barrett 還元 | barrett-reduction | 法 m で割った余りを、前計算した ⌈2^64 / m⌉ との掛け算とシフトで求める方法。商の見積もりが 1 ずれるだけなので、1 回の補正で余りが求まり、実行時に決まる法でも割り算を使わずに済む |
| 不変条件 | invariant | 処理の間ずっと成り立たせておく性質。modint なら「値は常に 0 以上 m 未満」。（ほかのページでも使うので、まだなければ） |

本文では用語集へのリンクは張っていない（Barrett 還元はページ内の節へのリンク）。

## 手引きへの提案

- §9 の「`using mint = atcoder::modint998244353;` を使ってよい」に、法が入力のときの `using mint = atcoder::modint;` も含めてよいと明記するとよい（dynamic.cpp で使った）
- §13 の定型の見出し `## 落とし穴 {#pitfalls}` と、catalog の sections の anchor `pitfalls`（modint では「val() で取り出す…」）がぶつかる。今回は sections の題名を見出しにして `{#pitfalls}` を付け、別に「落とし穴」の見出しは立てなかった。sections の anchor に `pitfalls` を使っているページがほかにもあれば、扱いを決めておくとよい

## 問題の補充の候補

例題は catalog の problems_note のとおり置かず、練習 2 問（abc357_d・abc281_g）だけにした。基礎のページとしては練習が少ないが、mod の数え上げの練習は comb のページに任せる方針なので、無理に足さない。足すなら次の型が合う（ap.py と第三者の解説の確認はまだ）。

- 法が入力で与えられる易しい数え上げ（dynamic_modint の set_mod の練習）。水以下の ABC で探す価値がある
- 「方法がなければ -1」と mod の数え上げが同時に出る問題（到達可能性を別に持つ落とし穴の練習）

## 未解決の点

- 「static_modint は法が定数なので % が掛け算とシフトに置き換わって速い」は一般的なコンパイラの最適化と noshi91 の記事に基づく。速さの実測はしていない
- 練習の方針の「$d \le 19$ で $10^d - 1$ は 998244353 の倍数にならない」は Python で d = 1〜19 を計算して確かめた（drken の記事はこの点に触れていない）
- acl-reading#modint・#modint-val と内容が一部重なる（`.val()`・`<` がない）。このページでは重複を避けてリンクにし、「余りから元の値は分からない」側に絞った

## 検証の指摘への対応（verify/modint.md）

- 指摘 1〜5 はすべて直した。指摘 5 の例は、数式の $\bmod$ だと数学の余り（2）と読めるので、コードの `-7 % 3` は `-1` と書いた
- 台帳への提案（abc281_g の alternatives）は上の表のとおり。検証役の答えにより、台帳の abc357_d・abc281_g の `checked` に 2026-10-21 を入れることも提案する
