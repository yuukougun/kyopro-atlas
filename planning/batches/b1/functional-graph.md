# functional-graph の報告と提案（工程8b・b1）

- 書いたファイル：docs/graph/functional-graph.md、snippets/functional-graph/{peel,walk,scc}.{cpp,yaml}、docs/img/functional-graph/rho.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 本とも一致）、textlint（エラー 0、警告 9。数式を含む文の長さ・助詞の重なりの誤検出と、台帳の summary の行）
- 図：catalog の visual（static・priority 2）を静的な SVG（rho.svg）で作った。動く図は作っていない
- 使った出典：drken（abc256_e・abc357_e）、kyo-pro（abc296_e）、Lanly（cnblogs、abc377_e）、hamayan（abc167_d）、ACL document_ja の scc。どれも付録 B のドメインで、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc256_e | summary | 末尾に「。」を足す（ほかの行と表記をそろえる） | — |
| abc357_e | summary | 末尾に「。」を足す | — |
| abc377_e | summary | 末尾に「。」を足す | — |
| abc256_e | approach | 「i → X_i の Functional graph で、閉路ごとにその上の最小の C を足す」のままでよい。alternatives に Union-Find（C の大きい順に辺をつなぎ、閉路を作る辺の C を足す）を足してもよい | https://drken1215.hatenablog.com/entry/2023/08/03/140800 |

- abc377_e について：Lanly 氏の記事は「p_i から数えて 2^K − 1 歩」と書いている。i から数えると 2^K 歩で、台帳の approach（2^K 歩進む）と同じ意味である。本文は「i から 2^K 歩先」と書いた

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 入次数・出次数 | in-degree | 有向グラフで、頂点に入ってくる辺の数を入次数、出ていく辺の数を出次数という。自己ループは両方に 1 ずつ数える |
| しっぽ（ρ 形） | rho-tail | 写像を繰り返し適用したときや Functional graph で、閉路に入るまでに一度しか通らない部分。長さを μ と書くことが多い |

（本文では用語集へのリンクは張っていない。足したら「入次数」の初出にリンクするとよい）

## 手引きへの提案

- 定型の節の一覧（§13-1）に「ACL では」の囲みの置き場所を足すとよい。見出し `## ACL では` を立てるか、関係する節の中に置くかが手引きから読み取れなかった。このページでは SCC の段落の直後（on-cycle の節の中）に置いた
- 例題のコードを例題の節に取り込むか、本文の節に置いて例題から参照するかの目安があると迷わない（このページは両方の形を使った）

## 問題の補充の候補

- 確認済みの問題で足りている（例題 2・練習 3）。足すなら次の候補（台帳への追加を提案。本文では触れていない）
  - abc179_e（E. Sequence Sum、diff 1175、台帳で確認済み・periodicity の例題）：A_{i+1} = A_i^2 mod M の列の和。写像の周期を見つける。裏付け：https://drken1215.hatenablog.com/entry/2020/09/20/091500 。ただし主題は周期性のページ（periodicity の例題）なので、ここでは練習としての参照が妥当
  - abc311_c（C. Find it!、diff 448、台帳で確認済み）：各頂点から辺が 1 本出るグラフの閉路を 1 つ出力する。cycle-detection の練習として台帳にある。functional-graph にも練習として載せる候補（易しい側の 1 問）

## 未解決の点

- abc256_e の C_i の上限（和に long long が要るか）は第三者の解説で確かめていない。本文は「コストの和も long long で持つ」と一般的に書いた
- related に memoized-recursion・dp/tree-dp がないが、本文からリンクしている。related に足すかはメインの判断に任せる（front matter の related は変えていない）
- tree-basics・namori-graph・scc・mod-pow は stub なので、ページへのリンクだけにした（節へのリンクは draft 以降に足せる。tree-basics#remove-add-edge、scc#on-cycle、mod-pow#binary-expansion、namori-graph#directed-version が候補）
- SVG は描画して目で確かめていない（手元に描画の道具がない）。座標は計算して置いた

## 検証の指摘への対応（verify/functional-graph.md）

- 1（直すべき）：確認問題の答えを「頂点 0 や 8 へは行けない」に直した
- 2（直すべき）：Union-Find の別解を「コスト $C_i$ の大きい順に辺 $i$–$X_i$ をつなぐ」に直した
- 3：「一番上（今の頂点）から $K$ 個下の要素 `stk[stk.size() - 1 - K]`」に直した
- 4：#one-cycle の ρ 形の導入に「しっぽは周期性のページでいう尾で、長さを $\mu$ と書く」を足した。語の統一（用語集・prh）は提案として残す：「しっぽ」と「尾」、「ρ 形」と「ρ 型」をどちらかにそろえるかはメインが決める
- 5：囲みの文を「`add_edge` はならし $O(1)$、`scc()` は $O(N + M)$」に直した。置き場所は手引きへの提案（上の「手引きへの提案」）のとおりメインの判断に任せる
- 6（採らなかった）：rho.svg の下の 3 行は残した。同じ内容が本文（#k-steps の例・#per-cycle）と代替テキストにあり、スマホで読みにくくても情報は失われない。図を描き直すと座標の見直しと再度の描画確認が要るため、今回は見送る
