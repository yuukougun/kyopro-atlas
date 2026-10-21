# dp-basics の報告（工程8b・バッチ b1）

- 書いたファイル：docs/dp/dp-basics.md、snippets/dp-basics/frog.{cpp,yaml}（貰う形 `pull` と配る形 `push` の 2 つの取り込み範囲。main で 2 つの答えの一致を assert）、snippets/dp-basics/range-pull.{cpp,yaml}（累積和で区間の遷移をまとめる。素朴な O(N(R−L)) の DP と assert で突き合わせ）、docs/img/dp-basics/push-pull.svg
- front matter で変えたもの：complexity（`状態数 × 1 状態あたりの遷移数（状態 N 個・遷移 K 通りなら O(NK)）。遷移元が区間なら累積和で 1 状態 O(1)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 23。数式を含む文の長さ・数式の中の読点・要点の「いつ使うか」の入れ子の箇条、助詞「に」「が」の重複で、読みやすさを確かめて残した）
- 数値の確かめ：例の高さ (2, 9, 4, 5, 1, 6) の表 (0, 7, 2, 3, 5, 4)、素朴な再帰の呼び出し 20 回、跳び方の数 F(100) ≈ 3.5×10^20、「次の 1 歩が安い方へ跳ぶ」貪欲の反例 (1, 0, 3)（長さ 3〜5・高さ 0〜5 の全探索、同点を除く）、Strange Bank 型の反例 12 円（貪欲 4 回・最適 2 回）、range-pull の最後のケース（2^98 mod 998244353 = 719747106）は Python で計算した
- 図：静的な SVG 1 枚（同じ表の上に、貰う形の実線の矢印と配る形の破線の矢印を 2 段で描いた）。描画の道具が手元になく、見た目は目で確かめていない。検証役に描画の確認を頼みたい

## 動く図（priority 1）の仕様

本文の four-parts の節に置き場の div を書いた：`<div class="kp-viz" data-viz="dp-tree-table" data-config='{"h": [2, 9, 4, 5, 1, 6]}'></div>`

- 左に「足場 5 から逆向きに『どこから来たか』を分岐する素朴な再帰の木」（呼び出し 20 個）、右に DP の表（6 マス）を並べる
- ステップ 1〜：木の節を帰りがけ順に計算していき、同じ足場の節が 2 回目以降に現れたら、表の既に埋まったマスへ線を引いて「計算済み」に灰色にする。表のマスが埋まるたびに caption で `dp[i] = min(dp[i-1] + |h_i − h_{i-1}|, dp[i-2] + |h_i − h_{i-2}|)` の値を示す
- 後半（モード切り替えでもよい）：同じ表の上で、貰う形（dp[i] へ矢印を集める、青の実線）と配る形（dp[i] から矢印を出す、赤の破線）を 1 マスずつ進める。どちらも各辺を 1 回ずつ使うことを caption で数える（辺は 2N − 3 本）
- 図の前後の文章は本文に書いた（図がなくても通じる）

## 使った出典

- drken「動的計画法超入門！ Educational DP Contest の A ～ E 問題の解説と類題集」https://qiita.com/drken/items/dc53c683d6de8aeacf5a：例題の状態・遷移、配る・貰うが各辺を 1 回ずつ使うこと、初期値（INF・0・false）、Frog 2 と類題（abc129_c・abc099_c は類題として名前が挙がるだけで、中身の解説はない）
- Kazun「AtCoder Beginner Contest 240 C問題 Jumping Takahashi」https://kazun-kyopro.hatenablog.com/entry/ABC/240/C：練習の方針（可否の表、X を超えた座標を捨てる）
- drken「AtCoder ABC 129 C - Typical Stairs (3Q, 茶色, 300 点)」https://drken1215.hatenablog.com/entry/2019/06/10/140000：練習の方針（dp[0] = 1、壊れた段、mod 10^9+7）
- 補充候補の確認に読んだもの：drken の ABC245 C の記事、Kazun の ABC242 C の記事（下記）
- 新しく noai を確かめたドメイン：なし（すべて付録 B）

## 台帳への提案

- dp_a・dp_b・abc240_c・abc129_c｜checked｜2026-10-21｜各 evidence で問いと方針を確かめた
- abc099_c｜evidence｜drken の EDPC 記事は類題として名前を挙げるだけなので、DP の方針（dp[n] と、大きい額からの貪欲が失敗すること）を書いた第三者の解説を足すとよい。私は方針を自分で確かめた（12 円で貪欲 4 回・最適 2 回）が、第三者の URL は見つけていない
- abc179_d は dp-prefix-sum の例題なので、このページでは本文で問題 ID を出さず、pull-to-prefix-sum の節で dp-prefix-sum へのリンクだけにした（変更の提案ではない）

## 用語集への提案

- 遷移｜transition｜DP で、ある状態の値を別の状態の値から決める関係。状態を頂点、遷移を辺とみると、DP は辺を 1 本ずつ使って値を伝える計算になる
- 本文では既存の `#state`（状態）と `#identity-element`（単位元）にリンクした

## 手引きへの提案

- §13.1 では落とし穴は定型の節（sections に載せない `## 落とし穴 {#pitfalls}`）だが、骨格の sections に「落とし穴：…」（anchor pitfalls）が載っているページがある。今回は sections の title と見出しをそのまま一致させた。定型にそろえるなら、メインが sections から外して見出しを `## 落とし穴 {#pitfalls}` に縮めるとよい
- 基礎の technique の「上位の手法とのつながり」は、このページでは map の節（DP の型の地図）が兼ねるので、next-steps の節は足していない

## 問題の補充の候補

catalog の数（例題 1・練習 4）は目安の範囲だが、数え上げの練習が abc129_c の 1 問だけなので、状態に少し情報を足す易しい問題を足す候補を挙げる。

- abc245_c（Choose Elements、diff 403）：各位置で A_i か B_i を選び、隣り合う値の差をすべて K 以下にできるかを判定する。dp[i][直前に A を選んだか B を選んだか] の可否 DP｜https://drken1215.hatenablog.com/entry/2022/03/29/112500（記事の本文の条件の不等号は誤植で、コードと図は「K 以下」）
- abc242_c（1111gal password、diff 512）：各桁が 1〜9 で隣り合う桁の差が 1 以下の N 桁の整数の個数を求める。dp[i][末尾の数字] の数え上げ｜https://kazun-kyopro.hatenablog.com/entry/ABC/242/C
- abc248_c（Dice Sum、diff 787）：各項が 1〜M で総和が K 以下の長さ N の列の個数。和を状態にする数え上げ｜https://kazun-kyopro.hatenablog.com/entry/ABC/248/C（調査レポート 02-dp §5.3 の裏付け。私は開いていない）
- abc040_c（柱柱柱柱柱、diff 896 参考値）：Frog 1 と同じ構造｜https://qiita.com/drken/items/dc53c683d6de8aeacf5a（例題と重なるので優先度は低い）

## 未解決の点

- abc242_c の法：Kazun の記事の要約では mod の記載が拾えなかった。台帳に足すときは問いの mod（998244353 と記憶しているが未確認）を ap.py か別の解説で確かめてほしい
- SVG の見た目（矢印の重なり・文字のはみ出し）は未確認
- 動く図 dp-tree-table の JS はまだないので、div は空の置き場になっている
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 6 回（curl でのタイトル確認を含めず）
