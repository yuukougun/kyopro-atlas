# complete-binary-tree の問題の補充（b6・工程9）

- ページ：docs/tree/complete-binary-tree.md（レベル 基礎）。今は例題 abc243_d（diff 758）、練習 abc465_d（diff 839）の 1 問、力試し abc321_e（diff 1627）
- 探したところ：
    - (1) b1 の報告 planning/batches/b1/complete-binary-tree.md と b1 summary/candidates.md の候補は abc264_h（Ex. Perfect Binary Tree、diff 2660 橙）だけだった。基礎のページには難しすぎるので今回も候補にしない。b3・b5 の candidates.md と、b2〜b5 の報告に complete-binary-tree の補充の候補はない
    - (2) data/problems.yaml で pages に complete-binary-tree を持つ問題は abc243_d・abc465_d・abc321_e の 3 問で、どれも本文にある。本文にない問題はない
    - (3) `python3 tools/ap.py search` で題名に Binary・Perfect・Complete・Heap・Tournament・Divide などを含む問題を探し、abc220_e を見つけて第三者の解説で確かめた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 結果：確かめられた候補は 1 問（challenge）。練習（practice）に足せる問題は見つけられず、練習は 1 問のままである

## 候補

### abc220_e（新規。台帳になし）

- 問題ID：abc220_e
- 題名：E. Distance on Large Perfect Binary Tree
- difficulty：1593（水）
- 役割：challenge（基礎の帯 〜1199 から離れるため。今の力試し abc321_e と同じく、count-at-distance の節（青）の考え方を使う）
- 要約：頂点 i の子が 2i と 2i+1 の、2^N − 1 頂点の完全二分木（N ≤ 10^6）で、距離がちょうど D の頂点の順序対 (i, j) の個数を 998244353 で割った余りで求める。
- 方針の要点：2 頂点を結ぶパスの最も浅い頂点（LCA）を深さ d ごとにまとめ、まっすぐ D 段降りる組（1 頂点あたり 2^D 個）と、左右の子孫から深さ l と D − l の頂点を 1 個ずつ選ぶ組（l によらず 2^{D−2} 個で、l の取れる範囲を N で切る）を数え、深さ d の頂点が 2^d 個あることを掛けて O(N) で足し合わせる。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/0926_abc220 （E の節。問題の設定（2^N − 1 頂点、子は 2i・2i+1、N ≤ 10^6、順序対を数える）と、上の深さごとの数え方を確かめた）
- 2 つ目の裏付けは取れていない（Web 検索の回数の上限に達したため。kmjp の 2021-09-26 の記録には ABC220 E の記事がなかった）。台帳に入れる前に、もう 1 件あると安心である
- 台帳への追加の提案：pages に {id: complete-binary-tree, role: challenge}。力試しが abc321_e と合わせて 2 問になる

## 確かめきれなかったもの（候補にしない）

- abc349_d（D. Divide Interval、diff 832 緑、ap.py で実在を確認）：区間 [L, R) を「2^i·j から 2^i·(j+1) まで」の形の区間に最少個数で分ける問題と理解している。分ける区間は完全二分木（セグメント木）の頂点にあたるので、基礎の練習に向く可能性がある。ただし第三者の解説を開いて確かめられていない（ikatakos の abc349 の記録には F の節しかなく、kmjp の記録は G だけ。Web 検索は上限に達した）。手法もこのページよりセグメント木（segment-tree）の区間の分け方に近いので、どちらのページに置くかはメインで判断してほしい
- abc188_c（C. ABC Tournament、diff 120）：2^N 人のトーナメントで、左半分と右半分の最強の選手のうち弱い方が準優勝。完全二分木の形ではあるが、ヒープ番号も祖先をたどる処理も使わないので候補にしない
- abc340_c（C. Divide and Divide、diff 528）：台帳では memoized-recursion の例題。⌊x/2⌋・⌈x/2⌉ に分けていく木だが、頂点の番号の計算は使わないので候補にしない

## 未解決の点

- 練習は 1 問のまま。基礎の帯で「番号 i と ⌊i/2⌋ の木」「L/R/U の移動」「K 分木の LCA」を直接問う ABC の問題は、ap.py の題名の検索では abc243_d・abc465_d のほかに見つからなかった。題名に手がかりのない問題は Web 検索が戻ってから探す余地がある
- 新しく noai を確かめたドメイン：なし（ikatakos.com は付録 B にある）
