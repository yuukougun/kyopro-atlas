# tree-edge-contribution（辺で切って数える）の報告と提案

- 書いたファイル：docs/tree/tree-edge-contribution.md、snippets/tree-edge-contribution/distance-sum.{cpp,yaml}、docs/img/tree-edge-contribution/edge-pairs.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 期待と違う 0（加えて手元で N = 2×10^5 のパスを流し、(N−1)N(N+1)/6 と一致を確認）／textlint エラー 0（警告 11：数式を含む文の長さ、数式の中の読点、助詞の重なり（「は」「に」）、折りたたみの行の長さの誤検出）
- 黄の節（期待値・色を通らないパス）の式と DFS の手順は、小さいランダムな木（N ≤ 9）の全探索と照合して確かめた（照合の脚本は一時置き場で、リポジトリには置いていない）
- 使った出典：E869120 の GitHub（典型90 039 の解答例）、hamayan（abc214_d・abc173_f・abc201_e）、kmjp（abc149_f・abc163_f）。どれも付録 B のドメインで、新しく確かめたドメインはない
- 動く図：作っていない（catalog の visual は static・priority 2 なので静的な SVG で代えた）
- ACL：対応なし（Union-Find の型は union-find-applications へリンク）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc479_e | pages の tree-edge-contribution | 外す（または status を未確認に戻す）。台帳の evidence（zenn の takechi_s 氏の記事）は問題文を載せておらず、解法のコードから「各頂点について値を出力する木の問題で、辺の番号と切った両側の大きさを使う」ことしか読み取れなかった。問いを自分の言葉で書けないので本文には載せていない | https://zenn.dev/takechi_s/articles/atcoder-abc479 |
| abc479_e | summary | （執筆時に確かめる）のまま。別の第三者の解説が見つかれば書く。GitHub の Aryudesu/myLibrary の PR #11 は「E の木上いもすから抽出」とだけ書いており、tree-imos の問題の可能性もある | https://github.com/Aryudesu/myLibrary/pull/11 |
| typical90_am | summary | 文末に「。」を足す（「木のすべての頂点の組について、距離を足し合わせた値を求める。」） | — |
| abc173_f | summary | 文末に「。」を足す | — |

- catalog の frequency_evidence は「recent 1（abc479_e）」を根拠にしている。abc479_e が外れると recent 0 になる（頻度 B のままでよいかはメインの判断）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 森 | forest | 閉路のない無向グラフ。各連結成分が木になる。連結成分の数は「頂点数 − 辺数」に等しい。 |

本文では `../guide/glossary.md#forest` でリンクした。

## 手引きへの提案

- 台帳の evidence が問題文を載せていない記事だけのとき（コードと短い説明だけ）、問いを確かめられないことがある。build_ledger の段階で、evidence が問いを述べているかを確かめる項目を足すとよい

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc201_e | 重み付きの木の全頂点対について、パスの XOR の総和を求める。根からの累積 XOR の bit ごとの 0 と 1 の個数の積で数える。台帳は確認済み（tree-distance の練習） | 練習（本文の edge-pairs の「XOR の和」の型に対応。abc479_e を外すと、水の ABC の練習が 1 問減るので補う） | https://blog.hamayanhamayan.com/entry/2021/05/15/235842 |
| abc220_f | 木の各頂点について、ほかの全頂点への距離の和を求める。台帳は確認済み（tree-dp の例題） | 練習（任意。使い分けの「頂点ごとの値は根の移動の差分」に対応） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0926_abc220 |
| abc163_f | 頂点に色がある木で、色ごとに「その色の頂点を 1 つ以上通るパスの数」を求める。台帳にない（ap.py で実在と diff 2470 を確認） | 力試し（黄の節 expectation の「特定の色を通らないパス」に対応。本文では問題 ID を出さず型だけを書いた） | https://kmjp.hatenablog.jp/entry/2020/04/20/0930 |

## 未解決の点

- abc479_e の問いを確かめられず、本文から外した（上の台帳への提案）。練習は abc214_d・abc173_f の 2 問で目安の下限。abc319 以降の問題が本文に 1 問もない（手引き §10 の「水・青のページには 1 問以上」を満たしていない）。abc479_e の問いが確かめられれば戻すのが最もよい
- abc214_d は union-find-applications の例題で、このページでは練習にした（台帳どおり）。本文の max-on-path の節は短くし、正しさとコードは union-find-applications#count-on-merge へリンクした
- 黄の節の「色ごとに成分の大きさを求める DFS」は、kmjp 氏の解説（BIT とオイラーツアーで通るパスを直接数える方法）とは別の、よく知られた O(N) の方法を自分で組み立てて書いた。全探索との照合で正しさは確かめたが、参考の行にはその旨を書いた
- tree-basics が骨格のままなので、「辺を 1 本取り除くと 2 つに分かれる」はページへのリンクだけにした（節 remove-add-edge へのリンクは、tree-basics が draft になってから足せる）
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 約 20 回

## 検証の指摘への対応（verify/tree-edge-contribution.md）

- 1（直すべき・max-on-path の同じ重み）：直した。まず重みがすべて異なるとして「$e$ を除いた、重み $w$ 未満の辺の森」で $a \times b$ を定義し、同じ重みは「小さい順（同じ重みは決めた順）に並べ、$e$ より前の辺だけの森」で数えると書き直した。最大の重みの辺が複数あるパスは、その中で最後に並ぶ辺に割り当てられる（Union-Find で初めてつながる瞬間と一致）。旧文の「先に併合した辺に割り当てられる」は誤りなので消した
- 2（直すべき・abc319 以降の問題と frequency_evidence）：台帳と front matter の頻度はメインの領分なので、本文は変えていない。下の「メインへの提案（検証後）」に書いた
- 3（直すべき・#abc149_f）：`[力試しの ABC149 F](#challenge)` にした
- 4（直すとよい）：採った。56 行のリンクを `../tree/tree-basics.md#remove-add-edge` に、forest-count の 1 段落目は森の式の理由を tree-basics#forest へのリンクに縮めた。用語集の `#forest` へのリンクは本文から外した（用語集への提案は残す）
- 5（直すとよい）：採った。XOR の和を箇条書きから出し、「辺ごとに足せない量では、別の分け方をする」の段落にした
- 6（直すとよい）：採った。「黒い頂点をすべて含む最小の連結な部分（以下「黒を結ぶ木」）」と呼び名を決め、節と力試しの方針でそろえた。力試しの問題の 1 行の説明（「最小の部分木」）は台帳の summary に合わせる行なので変えていない
- 7（直すとよい）：採った。図の 1 行目の長い説明を外し、viewBox を 720 × 380 から 580 × 360 に詰め、文字を 15 にした（幅 358px で約 9px）。根の側のラベルを「根の側 {1, 3, 6}：N − s = 3」に短くした。図には辺の名前の表記が残らないので、本文の「辺 1−2」との食い違いはなくなった
- 8（直すとよい）：採った。「「辺で切って数える」は、…」にした

## メインへの提案（検証後）

- abc319 以降の問題がない（手引き §10）。abc479_e の問いが第三者の解説で確かめられれば練習に戻す。戻せなければ、力試しに abc362_f（距離の和を最大にする組の分け方。各辺の寄与の上限 $\min(s, N - s)$ を使う。台帳では tree-centroid の例題）を足すのがこのページの主題に最も近い。abc359_g（同じ色の組の距離の和。使い分けの 3 つ目に対応）も候補
- あわせて front matter の `frequency_evidence: recent 1（abc479_e）` を、ページに載せた問題に合わせて書き直す
- 用語集の forest：本文からは外したが、tree-basics・connected-components が `glossary.md#forest` にリンクしているので、バッチの終わりに足す必要は残る
