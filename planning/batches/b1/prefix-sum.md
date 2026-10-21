# prefix-sum の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/prefix-sum.md、snippets/prefix-sum/range-sum.{cpp,yaml}、snippets/prefix-sum/exclude-one.{cpp,yaml}、docs/img/prefix-sum/half-open.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 30。数式・リンクの `[` を括弧の対応と誤検出するもの、数式や画像の代替テキストを含む文の長さ、数式の中の読点、助詞の重複の誤検出に近いもの）
- 図：catalog の visual（static・priority 2）を静的な SVG にした（棒グラフ a と S の折れ線、[2, 5) の網掛けと差 10）。手元に SVG を画像にする道具がなく、見た目は座標の計算でだけ確かめた。検証で表示を見てほしい
- 動く図：作っていない（priority 2 で static 指定のため、div も置いていない）

## 使った出典

- drken（hatenablog）ABC122 C・ARC098 C・ABC125 C、hamayan ABC172 C：例題と練習の方針（台帳の evidence）。題名は各ページの title で確かめた
- github.com の Reputeless/tenkei_90 076.md：円環を 2 周分に伸ばした累積和と二分探索の型（台帳にない問題なので、本文では問題 ID を出さず型だけを書いた）
- qiita.com の comet725・Konini64 の ABC479 記事と WebSearch：abc479_d の問いを確かめようとしたが、どちらも問題文を載せておらず、問いを確かめきれなかった（下の「未解決の点」）
- 新しく noai を確かめたドメイン：なし

## 台帳への提案

- abc479_d｜pages｜prefix-sum の practice を外す（いったん保留）｜第三者の解説（https://qiita.com/comet725/items/0c8bc1e676d535283e84、https://qiita.com/Konini64/items/0d0408d36adc0434c6ad）はコードと方針だけで、問い（L・R の意味、クエリが何の最小を問うか）が書かれていない。summary が「（執筆時に確かめる）」のままで本文に書けないため、本文には載せていない。問いを書いた解説（例：kmjp の ABC479 の記事など。付録 B のドメイン）で確かめられれば、練習に戻してよい
- abc125_c｜evidence の内容｜変更なし。drken の記事に「N ≥ 2、書き換え後の値は 1〜10^9」とあり、summary はそのままでよい

## 用語集への提案

- なし（半開区間 half-open-interval と単位元 identity-element は既にある）

## 手引きへの提案

- §13.1 の定型の見出し `## 落とし穴 {#pitfalls}` と、catalog の sections の `{title: あふれと添字のずれ, anchor: pitfalls}` がぶつかる。今回は sections に従い `## あふれと添字のずれ {#pitfalls}` にした（中身は落とし穴の節）。ほかのページの catalog にも anchor が pitfalls の節があるなら、「sections に pitfalls があれば、その title を見出しにして定型の『落とし穴』の代わりにする」と §13 に書くとよい

## 問題の補充の候補

- typical90_bx（076. Cake Cut（★3）、ap.py で実在を確認、diff なし）：円環に並んだケーキのピースから連続する部分を取り、和をちょうど全体の 1/10 にできるか判定する。列を 2 周分に伸ばした累積和の上で、各始点から目標の値を二分探索する（尺取りでもよい）｜https://github.com/Reputeless/tenkei_90/blob/main/076.md（解答コードで方針を確認。問いはコードからの推定なので、公式の解説画像 https://github.com/E869120/kyopro_educational_90/blob/main/editorial/076.jpg でも確かめるとよい）｜節 circular の練習の候補。research 01 §4.E でも円環の例に挙がっている
- abc265_d（D. Iroha and Haiku (New ABC Edition)、diff 727、台帳では interval の practice）：区間和が P・Q・R と続く位置があるか判定する。累積和の値を集合に入れて調べる｜https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc265-d.html｜節 with-binary-search の練習の候補（research 01 §5 で prefix-sum の候補に挙がっている）。interval のページと重なるので、どちらに置くかはメインで判断

## 未解決の点

- abc479_d の問いを確かめられなかった（上記）。catalog の練習 4 問のうち 3 問だけを載せた
- 節 left-right の「1 つ除いた最大値は、最大と 2 番目の最大でも求まる」は自分で確かめた事実で、出典はない
- 図の見た目（文字の重なり）を画像で確かめていない
