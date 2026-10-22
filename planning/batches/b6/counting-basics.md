# counting-basics の問題の補充（工程9）

- ページ：docs/comb/counting-basics.md（レベル 基礎）
- 今の問題：例題 typical90_bq、練習 abc307_e（1 問）。力試しなし
- 確かめた日：2026-10-22。実在・題名・difficulty は `python3 tools/ap.py show` で確かめた。裏付けはどれも付録 B のドメイン（drken1215・torus711・kmjp.hatenablog.jp・ikatakos.com）
- 補充すると練習は 3 問（abc307_e・abc178_c・agc031_a）になり、目標の 2〜4 問に入る

## 候補

### abc178_c　C. Ubiquity（diff 653）

- 役割：practice
- 台帳：既にこのページを pages に持つ（role: practice）が、本文に載っていない。本文に足すだけでよい
- 要約：各要素が 0〜9 の長さ N の列のうち、0 と 9 をどちらも含むものの数を求める問題である。
- 方針の要点：全体 10^N から 0 を含まない 9^N と 9 を含まない 9^N を引き、二重に引いたどちらも含まない 8^N を足し戻す（重複順列と、和の法則で重なりを扱う型。引き算の後の負の余りに注意）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2020/10/09/162600
    - https://torus711.hatenablog.com/entry/2020/09/14/000222（検索結果の要約で同じ式を確認。本文は開いていない）

### agc031_a　A. Colorful Subsequence（diff 953）

- 役割：practice
- 台帳：未登録。追加の提案（pages: counting-basics の practice）
- 要約：文字列 S の部分列（取り出す位置が違えば別のものとする）のうち、含まれる文字がすべて異なるものの数を求める問題である。
- 方針の要点：文字ごとに「使わない」か「S の中の出現位置の 1 つを選ぶ」かで（出現回数 + 1）通り、文字どうしは独立なので積の法則で掛け、最後に空の部分列の 1 通りを引く。並べ方は S の中の順で決まるので数えなくてよい。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/03/18/125300
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2019/0316_agc031

### abc133_e　E. Virus Tree 2（diff 1505）

- 役割：challenge（帯「基礎 〜1199」から離れるので力試し）
- 台帳：既に tree-dp（practice）・tree-traversal（challenge）・counting-fix-order（example）にある。counting-basics の challenge を足す案。counting-fix-order の例題と重なるので、載せるかはメインの判断に任せる
- 要約：N 頂点の木を K 色で塗り、距離 2 以下のどの 2 頂点も違う色になる塗り方の数を求める問題である。
- 方針の要点：根から順に色を決めると、根は K 通り、根の子は K−1 色から、ほかの頂点の子は自分と親の色を除く K−2 色から互いに違う色を選ぶ順列になり、選択肢の数が前の選び方によらず一定なので全頂点の積で数えられる（本文の例題の「距離 2 以内が異なる」を木に広げた形で、「決める順番を変える」節にも合う）。
- 裏付け：
    - https://drken1215.hatenablog.com/entry/2019/07/08/002700
    - https://kmjp.hatenablog.jp/entry/2019/07/07/1000（検索結果の要約で DFS 順に掛ける方針を確認。本文は開いていない）

## 見送ったもの

- abc209_c（C. Not Equal、diff 285）：積の法則そのものだが、台帳で counting-fix-order の practice で、決める順番を変える型の代表としてそちらが持ち主。重複を避けて見送った（足すなら practice の先頭に置ける）
- abc167_e（E. Colorful Blocks、diff 1442）：二項係数で隣が同じになる位置を選ぶ必要があり、counting-mindset の例題。このページの主役ではないので見送った
- 円順列・数珠順列だけで解く ABC の問題は、今回も見つけられなかった
