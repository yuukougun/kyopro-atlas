# mod-pow（繰り返し二乗法）の報告

- 書いたファイル：docs/math/mod-pow.md、snippets/mod-pow/{pow-mod,monoid-power,acl}.{cpp,yaml}、docs/img/mod-pow/binary-expansion.svg
- front matter で変えたもの：complexity・stage（draft）・updated、sections に `{title: 繰り返し二乗法を部品にする手法, anchor: building-block}` を追加、binary-expansion の title を「指数を 2 進展開して…」（半角と全角の間に空白）に直した
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 3 片とも期待どおり。textlint エラー 0、警告 5（要点の囲みと折りたたみの中の数式を含む文の長さ、台帳の summary の行（abc228_e）の長さと「で」の重なり）。fix_problems --check は mod-pow には指摘なし（graph/minimum-spanning-tree.md の 10 行が未展開と出るが担当外）
- 使った出典：drken ARC111 A の記事（例題の導出）、E869120 典型90 sol/069.cpp（式と境界）、Kazun ABC228 E の記事（指数を p−1 で、底が p の倍数）、ACL document_ja の math.md・modint.md と手元のソース（pow_mod の m は int、m = 1 で 0、0^0 は 1）。新しいドメインはなし
- 図：静的 SVG 1 枚（3^13 の 2 進展開）。visual は priority 2 の動く図なので作っていない。作るなら binary-expansion の SVG の後に置き、状態は「k ごとに a^(2^k) を作る → bit が 1 なら res に掛ける」で、caption に res・a・n の値を出す

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_bq | pages の mod-pow の approach（catalog 側） | 「K(K−1)(K−2)^(N−2) を繰り返し二乗法で計算する。N = 2・K = 2 では 0^0 = 1 として扱う」 | https://github.com/E869120/kyopro_educational_90/blob/main/sol/069.cpp （N ≤ 2 と K = 1 を場合分けしている） |
| abc228_e | approach | 「M が 998244353 の倍数なら答えは 0」に加えて「指数を 998244353 で割るのは誤り」を足すかは任意 | https://kazun-kyopro.hatenablog.com/entry/ABC/228/E |
| abc228_e | summary | 現在の summary は 140 字で textlint の文の長さの警告が出る。例：「長さ N・各項 1 以上 K 以下の数列すべてに 1 以上 M 以下の点数を付ける方法の数（M^(K^N)）を 998244353 で割った余りで求める（N, K, M ≤ 10^18）。」 | 同上 |
| arc111_a | checked のほかに変更なし | — | https://drken1215.hatenablog.com/entry/2022/12/26/195928 で問いと方針を確認した |

## 用語集への提案

- 交換法則｜commutativity｜2 つの要素の順番を入れ替えても演算の結果が変わらないこと（x ∘ y = y ∘ x）。行列の積や写像の合成は満たさないが、同じ要素の累乗どうしなら順番を気にしなくてよい。（本文では語だけ使い、リンクはしていない）

## 手引きへの提案

- 基礎の technique の構成（§4）に「上位の手法とのつながり」があるが、sections に載せるかどうかが決まっていない。本ページでは中身の節として sections に足した（building-block）
- math の基礎のページで「指数の mod」「逆元」など同じ落とし穴が複数ページにまたがる。どのページが持ち主かを catalog で決めておくと、リンクだけで済ませやすい

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL | 状態 |
| --- | --- | --- | --- |
| math_and_algorithm_aq（アルゴ数学 050. Power） | a^b を 10^9+7 で割った余り（繰り返し二乗法をそのまま使う入門） | https://github.com/E869120/math-algorithm-book （4.6 節の解答のフォルダ。問題との対応は未確認） | 未確認。ap.py で実在のみ確認。問いの裏付けは取れていないので、確かめてから練習の先頭に置く候補 |

## 未解決の点

- 動く図（visual priority 2）は作っていない
- SVG の描画を手元で確かめる道具（rsvg-convert など）がなく、文字のはみ出しは目視していない（viewBox 720×300、最長の行は約 690px と見積もった）
- 確認問題の「2 乗は 3 回」は概念上の回数で、snippet の反復版はループの最後にも 1 回 2 乗する（4 回）。本文では触れていない
- related のページ（mod-inverse・exponent-mod・geometric-series-mod・matrix-power）は stub なので、節へのリンクはせずページへのリンクだけにした
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 5 回
