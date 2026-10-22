# b4 検証：balanced-bst

- 対象：docs/ds/balanced-bst.md、snippets/balanced-bst/implicit-treap.{cpp,yaml}、docs/img/balanced-bst/treap.svg・split.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は tools/render_svg.py で 360px・720px の PNG にして確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page balanced-bst`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/balanced-bst`：期待と違う 0
- `g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined`：警告なし。main の自己検査（乱数の 20000 操作を vector と比較、10^5 個の末尾挿入で深さ < 60）と、cases 2 つ、手で作った入力（[1,2,3,4,5] を [1,4) 反転 → 和 [0,2) = 5、位置 0 を削除 → 和 [0,4) = 14）を実行して異常なし・出力一致
- split・join・ops のコードを本文の手順と 1 行ずつ照らした：split の $k \le s$／$k > s$ の場合分けと $k - s - 1$、join の優先度の比較、push の後に子を読む順、pull の位置はすべて本文どおり。`t[a].r = join(t[a].r, b)` は C++17 以降、右辺が先に評価され、join と split は push_back しないので参照の無効化もない
- 深さの評価：$\sum_{j \ne i} 1/(\lvert i-j \rvert+1) \le 2(H_N - 1)$ で、$N \ge 2$ では左右の和が同時に $1/N$ まで届かないので厳密な不等号も正しい。$H_N - 1 < \ln N$ も正しい。$2 \ln 10^5 \approx 23.03$。祖先になる条件の証明（R に初めて入るノードが R の中で優先度最大）も正しい
- 図：treap.svg はヒープの条件（9 > 7 > 3, 2、9 > 6 > 4）と sz（6, 3, 2, 1…）が正しく、通りがけ順が A〜F。split.svg は k = 2 の split をコードどおりに追った結果（左：B(A)、sz2。右：D の左に C、右に F(E)、D の sz4）と一致。本文の「D では左の要素数 3 → 左、B では 1 → 右、C の手前で切れる」も一致
- Library Checker：task.md で確かめた。range_reverse_range_sum は「0 l r 反転・1 l r 和」、dynamic_sequence_range_affine_range_sum は「挿入・削除・反転・アフィン・和（mod）」、ordered_set は「挿入・削除・x 番目・x 以下の個数・x 以下の最大・x 以上の最小」。本文の説明と一致
- 問題：`python3 tools/ap.py show abc241_d arc033_3` → D. Sequence Query diff 1177、C. データ構造 diff 1641（参考値）。本文の diff と一致。台帳の summary と本文の要約が一致
- ARC033 C：drken 氏の記事（台帳の evidence）で $Q, X \le 2 \times 10^5$ と BIT 上の二分探索・平衡二分探索木の方法を確かめた。方針は正しい
- ABC241 D：recuraki 氏の記事で、pb_ds に（値, 通し番号）相当の鍵を入れ、`order_of_key` で x 以下の個数 c を数えて `find_by_order(c - k)` を読む解き方を確かめた。本文の方針と一致。K ≤ 5 は読んだ 2 記事にも書かれておらず（執筆者の報告どおり）、台帳の主の summary にだけある。問題文は開けないのでここでは確かめられない（私の記憶でも K ≤ 5 だが、根拠にはしない）
- pb_ds：C++ の章の #pb-ds の内容（型引数・重複の扱い・less_equal の落とし穴）と食い違わない。`order_of_key` は x 未満の個数、`find_by_order` は 0 から数える、どちらも $O(\log N)$ で正しい
- F8：hamamu 氏の記事と並べた。記事は回転による挿入・クイックソートとの類比で説明し、例も違う（A〜F・優先度 9/7/6 の例は記事にない）。近すぎる箇所はない
- 参考の URL のドメインはすべて付録 B にある（qiita.com・*.hatenablog.com・ei1333.github.io・gcc.gnu.org・github.com・en.wikipedia.org）。atcoder.jp の URL は練習の囲みの中だけ
- 前の節へのリンク先 anchor（ordered-set#near-kth、kth-element#bit-binary-search・#reverse-insertion・#arc033_3、sqrt-decomposition#buckets、cpp-container-idioms#invalidation・#pb-ds）はすべて存在する
- front matter：変えたのは complexity・stage・updated、sections の library の追加と pbds の title の短縮（報告どおり）。visual は null なので G7 は対象外

## 指摘

直すべき指摘はない。以下はすべて「直すとよい」。

### 1. 直すとよい｜事実（F2）・分かりやすさ（U3）｜#treap の第 1 段落と #library の性質の 2 つ目、コード片の Node の注釈

- **問題**：#treap では「親の優先度は子より大きい」「木はちょうど 1 通りに決まる」と書き、#library では「親の優先度は子の優先度以上」と書いていて、言い方がそろっていない。1 通りに決まるのは優先度がすべて異なるときだけで、コードの優先度は 32 ビットの乱数なので等しい組が実際に出る
- **根拠**：$2 \times 10^5$ 個のノードで、等しい優先度の組の個数の期待値は $\binom{2 \times 10^5}{2} / 2^{32} \approx 4.7$。join は `t[a].pri > t[b].pri` で、等しいときは b を根にするので「以上」の条件は保つが、形は一意でなくなる。深さの評価への影響は無視できる
- **直し方**：#treap に「優先度がすべて異なるとき」と一言添え（等しい組はまれで、深さの評価にはほぼ影響しない、と脚注程度）、#library の「以上」と書き方をそろえる

### 2. 直すとよい｜事実（F2）｜#treap「split と merge は、どちらも根から 1 本の経路を降りるだけなので」

- **問題**：merge は 1 本の経路ではなく、$a$ の右端の経路と $b$ の左端の経路を交互に降りる。時間は 2 つの木の深さの和に比例する
- **根拠**：join の再帰は、$a$ 側に進むと `t[a].r` へ、$b$ 側に進むと `t[b].l` へ移る。最悪で深さ$(a)$ + 深さ$(b)$ 回
- **直し方**：「split は根から 1 本の経路を、merge は $a$ の右端と $b$ の左端の経路を降りるだけなので、かかる時間は木の深さ（merge は 2 つの深さの和）に比例する」とする。split で分けた後の木もそれぞれの列の treap なので深さの評価がそのまま使える、と添えるとなおよい

### 3. 直すとよい｜コード（C4）・分かりやすさ（U10）｜#library の 3 つの取り込み（node・core・ops）

- **問題**：node・core・ops の 3 つで main 以外のほぼ全部（約 90 行）を見せていて、手引き §9（載せるのは要点の数行と処理の流れ）と §4 の overview（実装の流れは資料に任せる）より多い。導入の「詳しい実装は学ぶための資料に任せる」とも合わない。ops の 4 関数は #what-it-does の表と同じことのくり返しである
- **根拠**：手引き §4 overview・§9 の「載せるのは要点の数行」、code.md C4 の「完全な実装を載せる」。§15-10 は「自作するときの要点」を入れるよう求めるが、それは間違えやすい点の箇条書きと core で足りる
- **直し方**：ops の取り込みを外し（表と「完全なプログラムは snippets に」の一文で足りる）、node は push と pull だけを見せる範囲に絞る。core（split・join）は残す

### 4. 直すとよい｜分かりやすさ（U3）｜#library の性質の 3 つ目と、間違えやすい点の「push の位置」

- **問題**：性質では「保留は自分の値には反映済みで、子にはまだ配っていない作用」と書くが、コードの反転の保留は自分の左右の子の入れ替えも push まで遅らせる（rev が立った v はまだ自分の子を入れ替えていない）。値（val・sum）には反転が効かないので矛盾ではないが、1 次関数の合成と反転を混ぜる読者（Dynamic Sequence Range Affine Range Sum）は「逆向きの合成値の入れ替えを付けたときにするか、push でするか」で迷う
- **根拠**：`reverse_range` は `t[b].rev ^= true` だけで、入れ替えは `push` の `swap(t[v].l, t[v].r)`。同じ節の「非可換な演算では…反転のときに入れ替える」はどちらの時点かを言っていない
- **直し方**：「コード片の反転の保留は、自分の左右の子の入れ替えも push まで遅らせる形にしている。逆向きの集約値を持つときは、保留を付けた時点で自分の 2 つの集約値を入れ替え、push では子の入れ替えと子への保留の受け渡しだけをする」のように、どちらの約束かを 1 文で書く

### 5. 直すとよい｜事実（F1）・冒頭（F10）｜front matter の complexity と要点の計算量、導入の第 1 段落

- **問題**：complexity は「split・join … 区間の和」、要点は「split・merge … 区間の総積」と、同じ内容で語が違う。導入の「位置で指定して $O(\log N)$ で行える」には「期待」がない
- **根拠**：F1 は 3 か所の一致を求める。本文の概念名は merge、join はコード片の名前
- **直し方**：complexity を「split・merge と、それで書く位置での挿入・削除・区間の反転・区間の総積は期待 O(log N)…」に直し、導入を「期待 $O(\log N)$」にする

### 6. 直すとよい｜図（G5）｜treap.svg・split.svg の D の「sz6」「sz4」、treap.svg の B の「p7」

- **問題**：D から F への辺が D の右下のラベル（treap.svg の sz6、split.svg の sz4）の上を通り、文字に線が重なる。treap.svg では D から B への辺が「p7」にも触れている
- **根拠**：render_svg.py の 720px の PNG で目視。辺 (220,70)→(340,132) は x = 239〜255 で y ≈ 80〜88 を通り、text (239, 83) の sz と重なる
- **直し方**：D のラベルを辺の上側（例：x = 240, y = 52・64）か左側に移すか、ラベルの下に白い矩形を敷く。B の p7 も少し右上へずらす

## 執筆者の未解決の点について

- 例題 0 問：catalog の problems_note どおりで問題ない
- iwiwi 氏のスライドを載せなかった：確かめていない資料を載せない判断は正しい
- ABC241 D の K ≤ 5：本文は練習の方針（折りたたみ）で台帳の主の summary に従っている。台帳の alternatives（balanced-bst）の summary を主にそろえる執筆者の提案に賛成。K の上限の裏付けになる第三者の資料を evidence に足せるとよい
- 台帳の checked：abc241_d・arc033_3 の内容（問い）を evidence の記事で確かめたので、checked に 2026-10-22 を入れることを提案する（ただし K ≤ 5 は上記のとおり未確認）

## 総合の判定

小さな直しで可（直すべき 0 件、直すとよい 6 件）。
