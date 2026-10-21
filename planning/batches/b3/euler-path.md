# euler-path の報告（b3）

- 書いたファイル：docs/graph/euler-path.md、snippets/euler-path/hierholzer.{cpp,yaml}（範囲 core＝無向・directed＝有向）、docs/img/euler-path/conditions.svg・hierholzer.svg
- front matter で変えたもの：complexity（判定・構成とも O(N + M)）・stage（draft）・updated。sections に `{title: 応用の型（縮約・辺を足す・向き付け・文字列を辺にする）, anchor: applications}` を足した（hierholzer と vs-hamiltonian の間。既存の anchor は変えていない）。catalog にあった `pitfalls` の節は §14-1 のとおり定型の `## 落とし穴 {#pitfalls}` にした（骨格の sections にはもとからなかった）
- 構成：level 黄・type technique なので §4 の technique（水・青・黄）。必要になる場面は conditions の冒頭で兼ねた（§14-5）。Hierholzer の節に小見出し「処理の流れ」`#hierholzer-steps`・「なぜ正しいか」`#hierholzer-proof`・「計算量」`#hierholzer-complexity` を置いた。acl は空なので ACL の囲みはない（例題の Union-Find は本文でリンクだけ）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 期待と違う 0（6 ケース：辺なし・自己ループ・多重辺・非連結・奇数次数 4 個・有向で差が 2）。プログラムの中で、M ≤ 6 の乱数のグラフ 3000 個について辺の順の全探索と存在の有無を比べ、返した路が正しいことも assert で確かめている。textlint エラー 0・警告 5（要点の「いつ使うか」の箇条書きが 1 文に数えられる長さ、有向の条件の数式を含む行の長さ、図の代替テキストの長さ、数式の中の読点、折りたたみの中の長さ。どれも誤検出として残した）
- 図：conditions.svg（(a) 奇数次数 2 個の 5 頂点のグラフ、(b) K4。奇数次数の頂点をオレンジの二重丸と次数の数字で示す）と hierholzer.svg（6 頂点 9 辺。1 周目を青の太い実線、2 周目をオレンジの破線、通った順を丸数字、差し込む頂点 2 を丸で囲む）。visual は priority 2 の static なので静的な SVG にした。render_svg.py で 360px・720px を目で確かめた（720px の PNG は下が切れて撮れるが、360px で全体を確かめた。道具の撮り方によるものと思う）。図の例の路 0 1 2 4 3 1 4 5 2 0 はコード片の出力（ケース 2）と一致する

## 使った出典

- https://kmjp.hatenablog.jp/entry/2023/01/21/1100：例題 abc286_g の縮約とオイラー路への帰着（台帳の evidence）。この記事には「元のグラフが連結」の記述がない
- https://it.commutty.com/MichaelChick/articles/21b95c9dc0f943829e9ef939cda4fbfb：abc286_g で「制約から元のグラフは連結なので、縮約後も連結」と書かれており、偶奇だけで判定できる根拠にした
- https://qiita.com/drken/items/a803d4fc4a727e02f7ba：オイラー閉路の必要十分条件（連結・多重辺可）と、DFS の構成で十分性を示すという筋
- https://kokiymgch.hatenablog.com/entry/2017/12/07/193238：Hierholzer 法（行き止まりは終点だけ、閉路を差し込む）、応用の型（しりとり・部分文字列からの復元・向き付け）
- https://github.com/yosupo06/library-checker-problems （graph/eulerian_trail_undirected・eulerian_trail_directed の task.md）：入出力の形・多重辺を含むこと
- drken1215.hatenablog.com の agc032_c・abc054_c の記事は、下の候補の裏付けだけに使った（本文には使っていない）
- 新しく noai を確かめたドメイン（tools/check_noai.py、どれも指定なし）：it.commutty.com（MichaelChick の記事）、kokiymgch.hatenablog.com。付録 B に足すことを提案する
- ikatakos.com の ABC286 は 503 で読めなかった

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc286_g | evidence | https://it.commutty.com/MichaelChick/articles/21b95c9dc0f943829e9ef939cda4fbfb を足す | 今の evidence（kmjp）には連結の保証の記述がなく、「偶奇だけで判定できる」を裏付けられない |
| abc286_g | summary | 「…ほかの辺は何回でも通ってよいウォークがあるかを判定する。」（「歩道」を「ウォーク」に） | 手引き §14-22 で「歩道」は使わない。本文の行は fix_problems が台帳から作るので、台帳の直しを待つ |
| abc286_g | checked | 2026-10-21 | 上の 2 つの解説で問いと方針を確かめた |

## 用語集への提案

- なし（次数・入次数・多重辺・自己ループ・孤立点・パスとウォーク・NP 困難・超頂点は既存の anchor にリンクした）
- 検討：「弱連結」（weakly-connected）：有向グラフで、辺の向きを無視したときに連結であること。本文では定義をその場で書いたので、今はリンクしていない

## 手引きへの提案

- 練習の問題が台帳に 1 問もないページで、`## 練習問題 {#practice}` に Library Checker への文章のリンクだけを置いた。問題の囲みがない練習の節を置いてよいか（置かないなら Library Checker をどこに書くか）を決めてほしい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| agc032_c（C. Three Circuits、diff 2284） | 単純な連結グラフの辺全体を、3 つの閉路（オイラー閉路の意味の、辺を 1 回ずつ使う閉じたウォーク）に分けられるか。全頂点の次数が偶数であることが前提で、次数 4 の頂点の数と次数 6 以上の頂点の有無で場合分けする | 力試し（黄）。オイラー閉路の条件と「閉路をつなぎ合わせる・切り分ける」の応用 | https://drken1215.hatenablog.com/entry/2019/03/28/161000 |
| abc054_c（C. One-stroke Path、diff 1244） | 頂点 1 から始めて全頂点をちょうど 1 回ずつ通るパスの数（N ≤ 8）。題名に「One-stroke」とあるが、問うのはハミルトン路 | このページの本文で「一筆書きと書いてあっても頂点の話のことがある」例として触れたい（台帳にないので本文では型だけを書いた）。持ち主は順列全探索か bit-dp | https://drken1215.hatenablog.com/entry/2019/09/16/224600 |

- ap.py で「Circuit・Euler・Stroke・Trail・Walk・Domino・Tour・Bridge」を探したが、ABC でオイラー路をそのまま使う問題はほかに見つからなかった。hamayanhamayan 氏のまとめ（https://blog.hamayanhamayan.com/entry/2016/10/05/101107 ）に載る問題はどれも AtCoder 以外だった

## 未解決の点

- 有向グラフで「辺を辞書順に並べてから Hierholzer 法を回すと、頂点の列が辞書順最小のオイラー路になる」という話はよく見るが、出典で確かめていないので書かなかった
- 応用の型「辺を k 本の路に分ける（奇数次数 2k 個）」「向き付けで差を 1 以下にする」「de Bruijn 列の長さ 2^k + k − 1」は、超頂点を足す議論と次数の数え上げで自分で確かめた。台帳の問題による裏付けはない
- 720px の図の PNG が下で切れて撮れた（render_svg.py の撮影範囲）。ほかのページの縦長の図でも起きるかもしれない
- 使用量の目安：道具の呼び出し 40 回ほど、Web 取得 8 回（検索 5 回）

## 検証（b3）の指摘への対応

- 直した：1（落とし穴の始点の誤り）・2（擬似コードの先頭に次数の条件を足し、長さの確認に「次数の条件を満たしたうえで」を付けた。理由も本文に 1 文足した）・3（BEST 定理に「有向グラフの」を付けた。2 か所）・4（証明と確認問題 4 を「次数のうち使った辺の分」と自己ループの数え方に直した）・5（69 行に「s と t が違う場合は辺 t → s を足して考える」を足した）・8（処理の流れの説明に「ans はコードの t.vs、辺の番号は t.es」を添えた）
- 3 のリンクは `#best-theorem` にしたかったが、行列木定理のページが stub なので check_pages が節へのリンクを許さない。今はページへのリンクにしてある。相手が draft になったら `../graph/matrix-tree-theorem.md#best-theorem` にするよう、メインに提案する
- 6・7 は共有ファイルの直しなので提案に回す（下）

### 提案（検証の指摘 6・7 から）

- 指摘 6：front matter の summary の「O(M)」を「O(N + M)」に直す（complexity・要点・本文と合わせる）
- 指摘 7：上の「台帳への提案」の abc286_g（summary の「歩道」→「ウォーク」、evidence に MichaelChick の記事、checked 2026-10-21）を反映し、fix_problems で本文の行を作り直す
