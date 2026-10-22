# leaf-first の問題の補充（b6・工程9）

- ページ：docs/tree/leaf-first.md（レベル 水）。今の練習は 0 問。例題は abc459_e・abc397_e、力試しは abc345_f
- 探したところ：
    - (1) b1 の報告 planning/batches/b1/leaf-first.md の「問題の補充の候補」と b1 summary/candidates.md に abc333_d（練習の案）・agc014_d（力試しの案）。b3・b5 の candidates.md には leaf-first の候補はなかった
    - (2) data/problems.yaml で pages に leaf-first を持つのは abc345_f・abc397_e・abc459_e だけで、どれも本文にある。本文にない問題はなかった
    - (3) 第三者の解説：drken のカテゴリ「葉から考える」（17 件）、ap.py の題名の検索（Leaf・Leaves・Matching・Cover・Tree・Pair など）、qiita の検索で、abc409_e と abc266_f を新たに見つけた
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 練習の候補 3 問を足すと、練習は合わせて 3 問になる。水の帯（1200〜1599）に入るのは abc266_f だけで、ほかの 2 問は基礎の帯である。水の帯で「葉から貪欲に決める」問題そのものは、今回も見つからなかった
- Web 検索はセッションの上限に達したため途中で打ち切った。足りない分は、残った手がかり（qiita の検索・既知のブログ）で確かめた

## 候補

### abc266_f（台帳にあり。namori-graph の例題）

- 問題ID：abc266_f
- 題名：F. Well-defined Path Queries on a Namori
- difficulty：1525（水）
- 役割：practice
- 要約：N 頂点 N 辺の連結な無向グラフで、2 頂点の間の単純パスがただ 1 つに決まるかを、多数の質問に答える。
- 方針の要点：次数 1 の頂点をキューで削り続けて残る閉路を求め、2 頂点が閉路の同じ頂点からぶら下がる木に入っているときだけ一意と答える（節 peel-leaves の「一般のグラフでも木の部分が消える」をそのまま使う）。
- 裏付け：
    - https://zenn.dev/fjnkt98/articles/98c9dfbd0702a4 （次数 1 の頂点をキューで削除して閉路を残し、閉路の各頂点からぶら下がる木を Union-Find でまとめる）
- 台帳への追加の提案：pages に {id: leaf-first, role: practice}。namori-graph の例題と重なるので、本文の練習の行では「キューで削る」部分を主に書く

### abc409_e（新規。台帳になし）

- 問題ID：abc409_e
- 題名：E. Pair Annihilation
- difficulty：973（基礎の帯。水の帯より下）
- 役割：practice（帯より易しいが、節 send-up の「親との辺を通して外へ出ていく量だけを送る」の最も素直な例なので練習の 1 問目に置く）
- 要約：辺に重みのある木の各頂点に電子か陽電子が置かれ（合計は打ち消し合う数）、粒子を辺に沿って動かすと重みの分だけ費用がかかるとき、すべてを打ち消すのに要る費用の最小を求める。
- 方針の要点：帰りがけ順に、各頂点で自分の値と子から届いた余りを足して親へ送り、親との辺の重みと送った量の絶対値の積を足していく（辺を切った片側の和の絶対値だけは必ずその辺を通るので、これが下界でありちょうど達成できる）。O(N)。
- 裏付け：
    - https://qiita.com/untan/items/92f4a5e02356bdb9fae7 （辺ごとの下界 w × |片側の和| と、葉に近い辺から順に送れば達成できること、DFS で親へ和を返す実装）
    - https://qiita.com/gotoki_no_joe/items/6431ec91a0bef27665aa （帰りがけ順に子から戻った電荷を足し、余りを親へ送って |量| × 重みを加える）
- 台帳への追加の提案：新規の行。summary は上の要約、approach は上の方針の要点、pages に {id: leaf-first, role: practice}

### abc333_d（台帳にあり。tree-traversal の練習）

- 問題ID：abc333_d
- 題名：D. Erase Leaves
- difficulty：704（基礎の帯。水の帯よりかなり下）
- 役割：practice（サイン「葉を消していく操作」の代表として置く案。易しすぎると判断するなら入れなくてよい。手法の中心は部分木の大きさなので、3 問の中では優先が最も低い）
- 要約：木から葉を 1 つずつ消す操作をくり返し、頂点 1 を消すまでに要る操作の最小の回数を求める。
- 方針の要点：葉を消す操作では枝が外側からしか削れないので、頂点 1 を葉にするには 1 本を残してほかの枝をすべて消すしかなく、残すのは最大の枝にして答えは N から最大の子の部分木の大きさを引いた値になる。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2024/11/02/192645 （drken のカテゴリ「葉から考える」に入っている。残す枝を最大のものにして N − M）
- 台帳への追加の提案：pages に {id: leaf-first, role: practice} を足す

### agc014_d（台帳にあり。game-basics の力試し）

- 問題ID：agc014_d
- 題名：D. Black and White Tree
- difficulty：2266（黄）
- 役割：challenge
- 要約：2 人が交互に木の頂点を白と黒に塗り、塗り終えた後に黒と隣り合う白を黒に変えたとき白が残るかで勝敗が決まるゲームで、勝つのはどちらかを求める。
- 方針の要点：木に完全マッチングがあれば後手が相手の塗った頂点の相方を塗って勝ち、なければ先手が勝つので、葉から「葉と隣を組む」貪欲で最大マッチングを作ってキューで判定する（節 tree-matching の応用）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/05/30/021200 （完全マッチングへの帰着、先手は葉の隣を塗り続ける戦略、葉からの貪欲なマッチングをキューで実装）
    - https://blog.hamayanhamayan.com/entry/2017/05/06/232930 （b1 の報告で確かめたもの。今回は開き直していない）
- 台帳への追加の提案：pages に {id: leaf-first, role: challenge} を足す

## 採らなかったもの

- abc296_e（E. Transition Game、diff 1285、台帳では scc・functional-graph の練習）：入次数 0 の頂点を削り続けて閉路の頂点を残す解き方がある（https://kyo-pro.hatenablog.com/entry/ABC296E ）。有向グラフの削り方で、このページでは Kahn 法への言及だけなので、練習には入れない。入れるなら topological-sort 側
- abc368_d（D. Minimum Steiner Tree、diff 816）：指定外の葉を削り続ける解き方があるが、steiner-subtree の例題なのでここには足さない
- abc359_f・abc282_e：drken のカテゴリにあるが、主役は別の手法（b1 の報告と同じ判断）
