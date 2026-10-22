# tree-ratio-greedy の報告（b4）

- 書いたファイル：docs/tree/tree-ratio-greedy.md、snippets/tree-ratio-greedy/merge.{cpp,yaml}、docs/img/tree-ratio-greedy/move-block.svg
- front matter で変えたもの：complexity（O(N log N)）・stage（draft）・updated（2026-10-22）。sections に `formulation`（何を最小にするか（3 つの言い換え））と `library`（計算量と自作するときの要点）を足した。既存の why-ratio・merge-with-heap はそのまま
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 期待と違う 0（7 ケース。別に、N ≤ 7 の乱数の木 1500 個で全順列の最小値と一致することを手元で確かめた）。textlint エラー 0、警告 3（図の代替テキストの読点・数式を含む確認問題の読点・参考のリンクの題名の長さ。§13-8・§14-25 の範囲）
- 図：move-block.svg を render_svg.py で 360・720 の PNG にして目で確かめた
- 使った出典：kmjp.hatenablog.jp（例題の方針）、nyaannyaan.github.io（ABC376 G＝01 on Tree）、github.com（hitonanode/cplib-cpp の tree_pop_order_optimization、library-checker-problems の task.md・info.toml・issue #1263）、maspypy.com（帰着の資料）。どれも付録 B の確認済みのドメイン。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc376_g | summary | 根付き木のどこか 1 頂点に宝があり、各頂点にある確率が与えられる。根から始めて、親を調べ終えた頂点を 1 つずつ調べるとき、宝のある頂点を調べるまでの回数の期待値の最小値を求める。 | https://kmjp.hatenablog.jp/entry/2024/10/23/0930 |
| abc376_g | evidence（追加） | https://nyaannyaan.github.io/docs/problems/editorials/ （手法名 01 on Tree の対応）、https://github.com/hitonanode/cplib-cpp/blob/master/other_algorithms/tree_pop_order_optimization.md （問題例に挙がる） | 左の URL |

本文の行は上の要約で書いた（fix_problems が label・diff を埋めた）。

## 用語集への提案

- なし（「縮約」は既存の contraction にリンクした）

## 手引きへの提案

- tree か basics の注意に「木の制約つきの交換論法（01 on Tree）では、(0, 0) の塊は比較が推移しないので最優先でまとめる。比の最大の塊を選ぶ議論で (0, 0) は常に最大の条件を満たすので、正しさも崩れない」を足すとよい（exchange-argument#ratios の「(0, 0) は除く」の木の版。持ち主は tree-ratio-greedy#why-ratio）

## 問題の補充の候補

| 問題 ID | 題名・diff（ap.py） | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- | --- |
| agc023_f | F. 01 on Tree・diff 3148 | 根付き木の各頂点に 0 か 1 が書かれ、親が子より先に来るように並べた 01 列の転倒数の最小値を求める（型の名前の由来。c・d がそれぞれ 0/1 の場合） | 練習（発展のページなので力試しでも可） | https://github.com/hitonanode/cplib-cpp/blob/master/other_algorithms/tree_pop_order_optimization.md 、https://maspypy.com/01-on-tree-%e4%ba%ac%e9%83%bd%e8%a6%b3%e5%85%89-train-seats 、https://github.com/yosupo06/library-checker-problems/issues/1263 （「AGC023-F をそのままやる」） |

- agc023_f の問いは上の 3 つの資料（問題名と、Library Checker の問題がその一般化であるという記述）から組み立てたもので、問題文の細部（N の上限など）は確かめていない。台帳に足すなら、問いの言い回しを第三者の解説でもう 1 つ確かめたい（日本語の解説記事は検索で見つからなかった）
- 台帳に足したら、本文の「名前の 01 on Tree は、この型を問うた過去の AGC の問題名から来ている」を練習の問題へのリンクに張り替えられる

## 未解決の点

- abc376_g の制約（確率の分子の上限）を確かめていないので、比較の積が long long に収まるかは本文で断定せず、「余裕がなければ __int128」と書いた。コード片は常に __int128 で比べている
- 「一般化」の一文（結合が結合法則を満たし、比較がまとめた後も保たれる形なら同じ手順）は、hitonanode 氏のライブラリが比較と += を差し替えられる形になっていることに基づく要約で、条件を厳密には述べていない
- Library Checker の問題は練習の見出しにせず、「計算量と自作するときの要点」の節の中でリンクした（例題・練習の囲みは atcoder.jp 専用のため）。§15-5 の形（練習問題の中の Library Checker の小見出し）にそろえるべきなら指示がほしい

## 検証の指摘への対応（b4 verify）

- 1（直すべき・記号 X の衝突）：比が最大の頂点を $V$ に改め、#why-ratio の本文・引用・図 move-block.svg のラベルと代替テキスト、#merge-with-heap の箇条（par[v]）、擬似コードの塊（x → v）、例題の解法の詳細（$d_P c_V$）をそろえた。費用は $X$ のまま
- 2（一般化）：条件を述べず、「比較と += を差し替えると違う問題にも使え、資料のライブラリがその形。どんな演算なら正しいかは資料に任せる」にした
- 3（図）：下付きを tspan にし、見出しを「P は V の親」にした
- 4（確認問題の答え）：定義の形 $d_0 c_1 + (d_0 + d_1) c_2$ で書いた
- 5（擬似コード）：「新しい代表に先頭の頂点 p を対応させる」にした
- 任意の点（#library の最後の段落）：コード片の節へのリンクにして短くした
- 採らなかったもの：なし
- 台帳への提案（abc376_g の summary・evidence）は検証で確かめられたので、checked に 2026-10-22 を入れる提案を添える
