# tree-distance（木の上の距離）の報告と提案

- 書いたファイル：docs/tree/tree-distance.md、snippets/tree-distance/from-one.{cpp,yaml}、snippets/tree-distance/xor-count.{cpp,yaml}、docs/img/tree-distance/two-sources.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に `{title: LCA・直径・全方位木 DP へのつながり, anchor: next-steps}` を足した（基礎の構成の「上位の手法とのつながり」）
- 検査の結果：check_pages エラー 0・警告 0、check_snippets 期待と違う 0、textlint エラー 0・警告 0。fix_problems --check は tree/small-to-large.md の 7 行を挙げたが、別の担当のページで、このページの行は 0
- 図：catalog の visual（static・priority 2）は静的な SVG（two-sources.svg）で作った。9 頂点の木で、各頂点に (d_a, d_b) を書き、a に近い・等しい・b に近いを塗りと枠線の種類（実線・細かい点線・点線）で分けた。手元に SVG を画像にする道具がなく、見た目は目で確かめていない（XML として読めることだけ確かめた）。検証で表示の確認を頼みたい
- 使った出典（どれも付録 B のドメイン）：drken（abc070_d・arc045_c）、hamayan（abc148_f・abc201_e）、qiita zk_phi（abc148_f の手番と「真に先に着ける頂点・距離 − 1」）、kanpurin（abc201_e の制約と bit ごとの数え方）。新しいドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc148_f | evidence | 次の URL を追加（台帳の evidence の hamayan は HL 分解と LCA で解いていて、2 点からの距離を比べる解き方は書いていない） | https://qiita.com/zk_phi/items/66de865261c9c9b38145 |
| abc148_f | approach | 2 人それぞれからの距離を求め、逃げる側が真に先に着ける頂点のうち鬼から最も遠い頂点を選び、その距離から 1 を引く | 同上 |
| abc201_e | evidence | 次の URL を追加 | https://kanpurin.hatenablog.com/entry/2021/05/15/224226 |
| abc070_d・abc148_f・abc201_e・arc045_c | summary | 末尾に「。」がない（本文の行は「。」を付けて書いた。fix_problems が台帳から作り直すなら台帳にも付けたい） | — |

## 用語集への提案

なし（「パス」「最小共通祖先」はページへリンクした）。

## 手引きへの提案

- §4 の「technique（基礎）」の「上位の手法とのつながり」は、§13-1 の定型の節の一覧にない。sections に載せる中身の節として扱い、anchor を `next-steps` にした（binary-search-answer と同じ）。定型の見出しと anchor を決めておくとそろう

## 問題の補充の候補

確認済みの問題は例題 1・練習 2・力試し 1 で、手引きの目安（練習 2〜6）の下限にある。次は研究の資料にある候補で、台帳には入っていない。

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc414_f | 木の上でちょうど K 辺ずつ進む移動の最短回数を、距離の余りと来た方向を状態に持つ BFS で求める（研究の資料 04-tree §5.1 で練習の候補。グラフの状態拡張との境界なので、力試しが合う） | https://merom686.hatenablog.com/entry/2025/07/13/021033 （この URL は今回は読んでいない。研究の資料の記載のまま） |

abc319 以降の ABC から新しい候補を探す作業はしていない（第三者の解説での裏付けが要るため、次の担当に回したい）。

## 未解決の点

- abc201_e の答えの法（10^9+7 と記憶しているが、読んだ第三者の解説では数字を確かめられなかった）。本文では法の値を書かず「問題の指定どおりに余りを取る」とした
- abc070_d の重みの上限は確かめていない。本文では具体的な値を書かず、long long にする理由を一般の形（N = 2×10^5、重み 10^9）で書いた
- frequency_evidence の recent 1 に abc451_e（tree-construction の例題）が挙がっているが、このページには載せていない

## 検証の指摘への対応（工程8b）

- 1（直すべき・#next-steps の直径の両端）：「重みが非負なら」の条件を足した
- 2（直すとよい・two-sources.svg）：中点の破線を頂点 2 のラベル「(2, 2)」の上下で切り、ラベルに重ならないようにした
- 3（直すとよい・#pitfalls の「上のコード」）：[1 点からの距離](#from-one) への参照に書き換えた
- 採らなかったもの：なし
- 台帳・手引きへの提案は検証の「提案（メインへ）」のとおり（checked の日付、evidence の追加、基礎の「上位の手法とのつながり」の見出しの定型）
