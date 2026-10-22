# min-cut の問題の補充（b6・工程9）

- ページ：docs/graph/min-cut.md（レベル 黄）。今の練習は 0 問。例題は abc010_4・abc239_g、力試しは abc332_g・abc397_g
- 探したところ：
    - (1) b1・b5 の summary/candidates.md には min-cut の補充の候補なし。b3 の summary/candidates.md と報告 planning/batches/b3/min-cut.md に arc074_d が 1 問。b3 の報告は abc318_g（頂点を分ける最大流）を max-flow の練習として、ここでは扱わないと書いている
    - (2) data/problems.yaml で pages に min-cut を持つ問題は abc010_4・abc239_g・abc332_g・abc397_g の 4 問で、どれも本文にある。本文にない問題はない
    - (3) 第三者の解説で探した。drken の「燃やす埋める問題（最小カット問題）の考え方を総整理！前編」（https://qiita.com/drken/items/52aafd8c073b37749539）が挙げる AtCoder の問題 15 問は、どれも二択の割り当て（燃やす埋める）か多値の割り当てで、辺や頂点を消して s と t を切り離す型の問題はなかった（project-selection 向き）。ikatakos の最大流のページ（https://ikatakos.com/pot/programming_algorithm/graph_theory/maximum_flow）は最小カットの節で AtCoder の問題を挙げていない。台帳で approach に「最小カット」を含む問題（abc193_f・abc347_g・abc445_g・abc472_g・typical90_an）はどれも燃やす埋める向きで、すでに project-selection に入っている。題名で ap.py search（Cut・Block・Separ・Isolat・Wall など）をかけたが、最小カットの問題は見つからなかった
    - Web 検索は途中でこのセッションの上限に達し、それ以上は探せていない。追加で探すなら、kmjp・hamayan のブログのフローの記事から辺・頂点を消す型の問題を拾うのがよい
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 確かめた候補は 1 問。足すと練習は 1 問になり、目標（2〜4 問）に届かない。無理には足さない

## 候補

### arc074_d（b3 の候補。台帳になし）

- 問題ID：arc074_d
- 題名：F. Lotus Leaves
- difficulty：2208（黄）
- 役割：practice（ページのレベル 黄の帯に入る。手法は節「頂点を入口と出口に分けて頂点カットを表す」そのもの）
- 要約：グリッド上の葉から同じ行か同じ列にある葉へ跳べる蛙が、始点 S から終点 T の葉に着けないように、S と T 以外の葉を取り除くときの最小の枚数を求める（切り離せなければ −1 を出力する）。
- 方針の要点：葉ごとに入口 → 出口の容量 1 の辺を張り、同じ行・列の葉へ跳ぶ移動を容量 ∞ の辺にして、S の出口から T の入口への最大流を求める。S と T が同じ行か列にあれば −1 で、行・列ごとに中継の頂点を置くと辺の数が O(HW) 程度に減る。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2017/05/20/0930 （葉を U・V の 2 頂点に分けて U→V に容量 1、同じ行・列の葉へ V→U の容量 ∞ の辺を張り、S の V から T の U へ流す。流量が大きすぎれば −1。行・列に代表の頂点を置けば辺が減るとも書いている）
    - https://scrapbox.io/nishio-en/✅ARC074D （頂点を容量 1 の辺に分けた最小カットで、S と T が同じ行か列なら −1。行・列ごとの中継の頂点で辺を約 200 万本から約 3 万本に減らした話。scrapbox.io は nishio のプロジェクトを付録 B で確かめてあるが、nishio-en は別のプロジェクトなので check_noai は未実行。メインで確かめるか、出典は kmjp だけにする）
    - 補足：https://blog.hamayanhamayan.com/entry/2017/05/20/230731 も開いた。頂点を入口と出口に分けるのが定石だという方針だけが書かれ、問題の設定や −1 の条件は書かれていないので、裏付けとしては弱い
- 台帳への追加の提案：pages に {id: min-cut, role: practice}。本文では節 vertex-cut への練習として置き、「行・列を頂点にして辺を減らす」点を一言添えるとよい

## 見送った問題

- abc318_g（Typical Path Problem、diff 2260）：頂点を入口と出口に分けるが、問われるのは流量 2 を流せるかで、カットの値や復元は使わない。b3 の判断どおり max-flow の練習のままにする
- abc472_g・abc193_f・typical90_an・abc445_g：最小カットで解くが、二択の割り当ての型なので project-selection の問題とする（台帳もそうなっている）
