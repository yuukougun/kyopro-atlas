# hash-safety の問題の補充（b6・工程9）

- ページ：docs/string/hash-safety.md（レベル 青）。今の練習は abc141_e（diff 1459）の 1 問、例題は abc339_f・typical90_au
- 探したところ：
    - (1) b1・b3・b5 の summary/candidates.md：hash-safety の行は b3 の abc284_f だけ（「法 2^64 で WA、2^61−1 で通った」記録の出典が特定できず採らなかったもの）。b2 の報告 planning/batches/b2/hash-safety.md の「問題の補充の候補」も abc284_f だけ。ほかに b1 の rolling-hash の報告（planning/batches/b1/rolling-hash.md）に「abc430_e は hash-safety の練習の候補にもなる」「abc331_f の syamashi の記事は hash-safety の記録としても使える」とあったので、この 2 問を確かめた
    - (2) data/problems.yaml で pages に hash-safety を持つ問題は abc141_e・abc339_f・typical90_au の 3 問で、どれも本文にある。本文にない問題はなかった
    - (3) 第三者の解説：abc377_g を kmjp のブログでハッシュの解き方として見つけた。abc353_e・abc287_e（prefix のハッシュを数えれば誕生日の見積もりがそのまま効く形）は、merom686・programming-hiroba・ikatakos の記事がどれもソートか Trie で解いていて、ハッシュで解いた第三者の解説を見つけられなかったので候補にしない
- 問題の実在・題名・difficulty は `python3 tools/ap.py show` で確かめた（2026-10-22）
- 候補 2 問（abc377_g・abc331_f）を足すと練習は合わせて 3 問になる。abc430_e は帯より易しいので別に挙げる
- 途中で Web 検索の上限に達したので、kmjp のブログ内検索と既知の URL だけで探した。探し足りない可能性がある

## 候補

### abc377_g（新規。台帳では trie の practice）

- 問題ID：abc377_g
- 題名：G. Edit to Match
- difficulty：1782（青）
- 役割：practice
- 要約：各文字列 S_k について、末尾の 1 文字の削除と末尾への 1 文字の追加をくり返して、空文字列かそれより前の文字列のどれかに一致させる最小の操作回数を求める。
- 方針の要点：前の文字列の長さ l の prefix のハッシュごとに「その prefix を持つ文字列の最短の長さ f」を長さごとの map に記録し、S_k の各 prefix で |S_k| + f − 2l の最小を取る。prefix のハッシュは合計約 2×10^5 個（総文字数）が map の中で比べ合うので、[組の数の見積もり](#birthday-bound)で法が約 10^9 の 1 つでは足りず、mod 2^61−1 か二重ハッシュと乱択した基数が要る。
- 裏付け：
    - https://kmjp.hatenablog.jp/entry/2024/10/29/0900 （上の方針のハッシュの解き方。法 1000000021・1000000009 の 2 つと、実行時の時刻などから乱択した基数を使い、2 つのハッシュを 64 ビットの 1 つの鍵にまとめて map に入れている。Trie を試してからハッシュに切り替えたと書いている）
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1026_abc377 （問題の設定の確認。解き方は Trie の各節に最小のコストを持たせる方法で、ハッシュではない）
- 台帳への追加の提案：pages に {id: hash-safety, role: practice}、evidence に kmjp の URL。alternatives に hash-safety 用の approach（上の方針の要点）

### abc331_f（台帳では rolling-hash の example・segment-tree-monoids の practice）

- 問題ID：abc331_f
- 題名：F. Palindrome Query
- difficulty：1666（青）
- 役割：practice
- 要約：文字列の 1 文字を書き換える更新と、区間が回文かを問う質問を、合わせて Q 回処理する。
- 方針の要点：順方向と逆方向の多項式ハッシュを BIT かセグメント木に載せて区間のハッシュを比べるが、基数を 2 に固定すると WA になった記録があり、[狙われる条件](#atcoder-tests)のとおり基数を実行時に乱択する（比べる組は Q 組なので、組の数の見積もりより基数の固定が問題になる例）。
- 裏付け：
    - https://note.com/syamashi/n/n8e580d4ce59d （BIT に base^i を掛けた値を載せる解き方。base = 2 に固定した提出が 1 WA になり、法だけでなく基数も変える必要があるとして、法が約 10^9 の素数 2 つと rand() で決めた基数にした。note.com は記事ごとに確かめる扱いなので check_noai で確かめた：X-Robots-Tag なし、meta robots="max-image-preview:large"、noai・noimageai の指定なし。付録 B の note.com の確かめた記事に syamashi の n8e580d4ce59d の追加を提案する）
    - https://merom686.hatenablog.com/entry/2023/12/03/001625 （順方向・逆方向の 2 本の更新できるハッシュで区間を比べる方針の確認。法・基数には触れていない）
- 台帳への追加の提案：pages に {id: hash-safety, role: practice}。alternatives に hash-safety 用の approach（「基数を固定すると落ちた記録がある。基数を乱択する」）
- メモ：rolling-hash の例題と同じ問題なので、本文では解き方を rolling-hash の例題へリンクし、ここでは基数の乱択の話だけにするとよい

### abc430_e（帯より易しい。台帳では z-algorithm の example・rolling-hash と kmp の practice）

- 問題ID：abc430_e
- 題名：E. Shift String
- difficulty：1109（緑。帯の 基礎 に当たり、青から離れる）
- 役割：challenge（指示の「帯から離れるなら力試しの候補」による。ただし帯より易しい側に外れているので、実際には練習の先頭に置くか、足さないのが自然。メインの判断に任せる）
- 要約：同じ長さの 2 つの 0/1 の文字列 A・B で、A の先頭の文字を末尾へ移す操作を何回すれば B に一致するかの最小を求める（できなければ −1）。
- 方針の要点：A+A の中で B が最初に現れる位置をハッシュで探すが、0/1 の文字列に合わせて基数を 2、法を 998244353 や 10^9+7 のような有名な素数にすると衝突するテストがあったという記録があり、[誰でも使う固定の選択が狙われる](#atcoder-tests)例になる。
- 裏付け：
    - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1101_abc430 （E の節。基数 2 と有名な法の組で衝突し、法を 4 つに増やして通した記録。推測されやすい選び方を避け、基数を乱択するか mod 2^61−1 を使う助言を引いている）
- 台帳への追加の提案：採るなら pages に {id: hash-safety, role: practice}（帯の扱いはメインが決める）

## 除いたもの

- abc141_e（練習）・abc339_f・typical90_au（例題）：本文に既にある
- abc284_f（diff 1575）：b2・b3 と同じく、法の選び方で結果が分かれた記録の出典を確かめられなかった。比べる組も約 N 組と少なく、このページの見積もりが効く場面ではない
- abc353_e（diff 1217）・abc287_e（diff 1093）：prefix のハッシュを数え上げる形なら誕生日の見積もりがそのまま効くが、読めた第三者の解説（merom686・programming-hiroba・ikatakos）はソート・Trie で解いており、ハッシュでの解き方を確かめられなかった。どちらも帯より易しい

## 本文に足すときのメモ

- 練習の並びは易しい順に abc141_e（1459）→ abc331_f（1666）→ abc377_g（1782）。abc141_e と abc377_g は「組の数で見積もる」、abc331_f は「基数を固定すると狙われる」の練習で、役割が重ならない
- abc430_e を入れるなら、abc331_f と同じ「固定の選択」の例として先頭に置く
