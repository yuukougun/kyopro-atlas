# euler-path の問題の補充（b6・工程9）

- ページ：docs/graph/euler-path.md（レベル 黄）。今の練習・力試しは 0 問で、例題は abc286_g だけ
- 探したところ：
    - (1) b3 の報告 planning/batches/b3/euler-path.md の「問題の補充の候補」に agc032_c と abc054_c（b3 summary/candidates.md にも記載）。b1・b5 の candidates.md には euler-path の候補はない。abc054_c は全頂点を 1 回ずつ通るパス（ハミルトン路）を数える問題で、このページの手法では解けないので練習から外した
    - (2) data/problems.yaml で pages に euler-path を持つのは abc286_g（例題）だけで、本文にない問題はない。agc032_c は台帳にない
    - (3) ap.py の題名検索（Euler・Stroke・Circuit・Trail・Domino・Walk・Orientation・Bridge・Tour・Cycle・Loop・Necklace・Shiritori・Route・Travel・Railway・一筆・しりとり など）と、第三者のブログの検索（drken1215 の「オイラー路」「オイラー閉路」「一筆書き」、blog.hamayanhamayan.com の「オイラー路」、qiita の「オイラー路 AtCoder」、drken の「AtCoder 版！蟻本」の発展編のオイラー閉路の節、potato167 の BEST 定理の問題一覧）。新しく見つかったのは BEST 定理で数える問題（abc336_g diff 3138・agc051_d diff 2807・arc146_e diff 3131・arc117_e diff 3166）だけで、どれも発展の帯で、主役は matrix-tree-theorem の側なので候補にしなかった。kmjp.hatenablog.jp の検索は HTTP 429 で読めなかった
    - Web 検索（WebSearch）はセッションの上限に達していて使えなかった。上の (3) はブログ内の検索ページと既知の一覧だけで探した
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 結論：確かめた候補は 1 問。足すと練習は 1 問で、目標の 2〜4 問に届かない。AtCoder でオイラー路をそのまま使う問題は少なく（b3 の報告と同じ所見）、無理に足さない

## 候補

### agc032_c（新規。台帳になし）

- 問題ID：agc032_c
- 題名：C. Three Circuits
- difficulty：2284（黄）
- 役割：practice（黄の帯 2000〜2399 に入る）
- 要約：単純で連結な無向グラフ（N, M ≤ 10^5）の辺をすべて 1 回ずつ使い、ちょうど 3 つの閉路（頂点の重複は許す閉じたウォーク）に分けられるかを判定する。
- 方針の要点：閉路をつなぐと一筆書きの閉路になるので全頂点の次数が偶数であることが必要で、そのうえで次数 6 以上の頂点があれば Yes（オイラー閉路をその頂点で 3 つに区切る）、次数 4 の頂点が 3 個以上なら Yes、1 個以下なら No、ちょうど 2 個（s, t）なら s から t を通らずに s へ戻れるかを DFS で調べる。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/03/28/161000 （問いの設定、全頂点の次数が偶数という必要条件、次数 6 以上ならオイラー路をその頂点で区切る、次数 4 の個数での場合分けと 2 個のときの DFS）
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2019/0323_agc032 （同じ場合分け。筆者は全ケースを覆う証明は詰めていないと書いている）
- 台帳への追加の提案：pages に {id: euler-path, role: practice}。summary・approach は上の要約・方針の要点を使える
- 本文での使い方の案：応用の型の節（applications）の「閉路をつなぐ・切り分ける」の練習として置ける。次数の偶奇でまず落とし、あとは場合分けという流れが、このページの存在条件の節とつながる

## 候補にしなかったもの

- abc054_c（C. One-stroke Path、diff 1244）：題名は「一筆書き」だが問うのはハミルトン路の数（N ≤ 8）。持ち主は順列全探索か bit-dp（b3 の報告どおり。本文の vs-hamiltonian の節で型として触れる用途だけ）
- abc209_e（E. Shiritori、diff 2153）：題名はしりとりだが、単語を辺にしたグラフ上のゲームの後退解析で、オイラー路ではない（game-retrograde-analysis の側。記憶による判断で、第三者の解説は開いていない）
- abc336_g・agc051_d・arc146_e・arc117_e：オイラー閉路の数を BEST 定理で数える問題で、いずれも発展の帯。potato167 の一覧（https://potato167.hatenablog.com/entry/2024/02/21/100000 ）に載る。abc336_g は matrix-tree-theorem の例題に既にある。euler-path の力試しにするには帯から離れすぎる
