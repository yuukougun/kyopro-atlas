# fps-basics（形式的冪級数と多項式の演算）の検証

- 検証した版：作業ツリーの docs/math/fps-basics.md（stage: draft、updated 2026-10-22）、snippets/fps-basics/newton.{cpp,yaml}
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0

## 実行した確かめ

- `python3 tools/check_pages.py --page fps-basics`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/fps-basics`：4 case 一致
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library newton.cpp`：警告なし。case 1・3 を流してサニタイザの報告なし（main の先頭の n = 1..70 の乱数比較の assert もすべて通る）
- cases の期待値：case 3（1 − x）は手計算、case 4（1 + x + … + x^5）の log と exp(f − 1) は Fraction で素朴な式から計算し直して一致（一時置き場の chk.py）
- 時間：snippet の fps_exp を N = 5×10^5 の乱数の列で動かして 0.43 秒、fps_inv は 0.12 秒（-O2、手元の WSL2）。下の 3
- ABC318 Ex：drken の記事（evidence）を読み、問題の貪欲法は「i = 1, …, N の順に、辺 (i, P_i) が閉路に含まれるなら消す」（Bob は逆順）であることを確かめた。この定義で (P, Q) を全探索するプログラムを書き、N = 1..5 で 0・0・4・172・6828、本文の式 $(N!)^2 - 2(N!)^2[x^N]\exp(\sum x^t/t^2) + N!$ と一致した。drken の DP $g(x) = \sum_{y<x} g(y)/(\max(y,1)(x-y))$ も記事と一致し、$[x^N]\exp(\sum x^t/t^2) = g(N)/N$ が N = 1..8 で成り立つので「DP の母関数を閉じた形で解いたもの」も正しい（一時置き場の b318.py）。式は正しいが、言葉の説明に誤りがある（下の 1）
- 式の手での確かめ：逆元のニュートン法 $1 - fh = (1 - fg)^2$、exp の反復 $g(1 - \log g + f)$（コード片の注記）、割り算の $\operatorname{rev}(q) \equiv \operatorname{rev}(f)/\operatorname{rev}(g) \pmod{x^{N-M+1}}$、Taylor shift の係数の式（drken の記事の式と添字をずらすと同じ）、$\log(1+x^a)$ の項数の調和級数、ABC303 Ex の $(N-2)!\,[x^{N-2}]F^N$、素朴な exp・累乗の漸化式：どれも正しい
- Library Checker：`gh api` で polynomial のフォルダを一覧し、9 問の名前と `*_sparse`（inv・exp・log・pow・sqrt）の実在を確かめた。pow の task.md（$0 \le M$、$M = 0$ も来る）、sqrt の task.md（ないときは −1）、division の task.md（$N < M$ も許され、そのとき $q = 0$）、multipoint の task.md を読んだ
- ACL：document_ja/convolution.md と照らした（`convolution(a, b)`、$O(n \log n + \log \mathrm{mod})$、$n = \lvert a \rvert + \lvert b \rvert$）。本文の書き方で問題ない
- 出典：hotman78 の記事（題名・各演算の計算量と定数項の条件・部分集合の和を log と exp で求める例があること）、drken の Taylor shift の記事（題名・式・和の順序の入れ替え）、Nyaan の Multipoint Evaluation のページ（ProductTree と余りで下ろすコード。説明の文章はない）を読んだ。題名・内容は書かれたとおり。本文の文章は出典の言い回しに近くない
- リンク先の anchor：convolution-ntt#reverse・#acl、stirling-first#fps、cayley-pruefer#with-polynomials、knapsack-undo#undo-by-subtraction、glossary#overflow はどれも存在する
- 台帳：abc303_h は generating-function-counting の例題、abc321_f は knapsack-undo の例題で、練習の方針の括弧書きと一致する
- 図：catalog（planning/catalog/math.yaml）の visual は null、ページに図はない。figure.md の観点は対象なし

## 指摘

### 1（直すべき）事実 F5：ABC318 Ex の「小さい順の貪欲法が消す辺」が逆

- 場所：`#abc318_h` の「方針」の 2 文目と 3 文目、「解法の詳細」の 2 つ目の項目
- 問題：本文は「小さい順の貪欲法は各閉路で番号最大の辺を消すので、正しいのは『どの閉路でも番号最大の辺の重みが最小』のときである」「長さ $t$ の閉路で番号最大の辺が重み最小である確率は $1/t$」と書く。問題の貪欲法は番号の小さい順に「閉路に含まれるなら消す」ので、各閉路で最初に消されるのは番号最小の辺で、その時点で閉路が切れて残りは消されない。小さい順の貪欲法が消すのは番号最小の辺である
- 根拠：drken の記事（evidence）の問題の説明「Alice は i = 1, …, N の順に、辺 (i, P_i) が閉路に含まれるなら削除する」と、DP の定義「各サイクルで頂点番号が最小の頂点から出る辺の重みが最小」。全探索（b318.py）も「小さい順＝番号最小を消す」の定義で書き、式と一致した。対称なので数え上げの式と答えは変わらないが、説明は誤り
- 直し方：方針の「番号最大」2 か所と、解法の詳細の 2 つ目の項目の「番号最大」を「番号最小」に直す（「大きい順は番号最大を消す」は書くなら逆の側として添える）。解法の詳細 1 つ目の「番号最大と最小の辺が同時に重み最小になれない」はそのままでよい

### 2（直すべき）分かりやすさ U7：本文が練習問題の解き方を折りたたみの外で書いている

- 場所：`#signs` の「同じ因子の累乗」の項目「次数の条件つきのラベル付き木の数は $F(x)^N$ の係数になる（練習の ABC303 Ex、…）」。軽いものとして `#polynomial-ops` の「練習の ABC245 D はこの筆算で足りる」
- 問題：ABC303 Ex の解き方の核（Prüfer 列で $F(x)^N$ の係数にする）を、問題名を挙げて折りたたみの外で書いている。clarity.md U7 の「本文が練習の問題を指して、その解き方を折りたたみの外で書いてしまう」に当たる。同じ内容は「練習の方針」の折りたたみにもあるので、消しても情報は失われない（generating-function-counting の検証の指摘 1 と同じ型）
- 根拠：clarity.md U7
- 直し方：「（練習の ABC303 Ex、」を消し、括弧を「（[Prüfer 列と多項式](../comb/cayley-pruefer.md#with-polynomials)）」だけにする。ABC245 D の文は「割り算の筆算を上の次数からたどると $O(NM)$ である」で止め、問題名を消す（問題名を残すなら練習の方針の折りたたみに任せる）

### 3（直すとよい）事実 F1・コード C3：「N = 5×10^5 で時間が厳しいとき」は見当のまま

- 場所：`#operations` のコード片の直後の段落「$N = 5 \times 10^5$ 程度で時間が厳しいときは、資料にある逆元を同時に更新する書き方に替える」。執筆者の未解決の点 3
- 問題：試していない見当で書かれている。実測では snippet の fps_exp は N = 5×10^5 で 0.43 秒、fps_inv は 0.12 秒で、Library Checker の制約でも十分に間に合う
- 根拠：上の「時間」の測定（snippet の関数をそのまま使い、main だけを替えたプログラム）
- 直し方：「手元では $N = 5 \times 10^5$ で 0.5 秒ほどで、ふつうはこれで足りる。さらに速くしたいときは、資料にある逆元を同時に更新する書き方に替える」のように、測った事実に直す

### 4（直すとよい）事実 F2：累乗で $M \bmod p$ に縮めてよいのは exp に渡す側だけ

- 場所：`#operations` の「自作するときの要点」の「累乗で $a_0 = 0$」の項目の最後の文「$\exp$ に渡す $M$ は $M \bmod p$ でよい」
- 問題：正しいが、同じ式の $a_d^M$ と $dM \ge N$ の比較には元の $M$（$a_d^M$ なら $M \bmod (p-1)$ でもよい）を使う必要がある。先に $M$ を $M \bmod p$ に置き換えると $a_d^M$ と比較の両方が誤る。自作でよく落ちる点なので、区別を一言書くとよい
- 根拠：$\exp(M \log h)$ の係数は $\mathbb{F}_p$ の元なので $M \bmod p$ でよいが、$a_d^M$ はフェルマーの小定理で指数を $p - 1$ で縮める
- 直し方：「$\exp$ に渡す $M$ は $M \bmod p$ でよいが、$a_d^M$ は元の $M$ で繰り返し二乗法をする（指数を縮めるなら $M \bmod (p - 1)$）」とする

### 5（直すとよい）事実 F2：多項式の割り算で $N < M$ の場合が抜けている

- 場所：`#polynomial-ops` の「多項式の割り算」の段落
- 問題：「商 $q$（$N - M$ 次）」は $N \ge M$ を前提にしている。$N < M$ なら $q = 0$・$r = f$ で、Library Checker の Division of Polynomials でもこの入力が許される（出力は $u = 0$）。式の $\bmod x^{N-M+1}$ がそのまま使えないので、場合分けを落とした実装が誤る
- 根拠：library-checker-problems の division_of_polynomials/task.md（$1 \le N, M$ が独立で、$q = 0$ のときの出力の決まりがある）
- 直し方：「（$N \ge M$ のとき。$N < M$ なら $q = 0$・$r = f$）」を添える

### 6（直すとよい）分かりやすさ U3：mod p の平方根の求め方にリンクがない

- 場所：`#operations` の「平方根」の項目「平方根は Tonelli-Shanks 法などで求め」
- 問題：前提（convolution-ntt・mod-inverse）にない手法の名前が説明なしに出る。サイト内に解説の節がある
- 根拠：docs/math/multiplicative-order.md の `#mod-root`（平方剰余と mod の K 乗根、Tonelli-Shanks・Cipolla）
- 直し方：「[Tonelli-Shanks 法](../math/multiplicative-order.md#mod-root)など」とリンクする

### 7（直すとよい）事実 F10：front matter の complexity と表の累乗の計算量が少し違う

- 場所：front matter の `complexity` と要点の「計算量」、`#operations` の表
- 問題：表は累乗を $O(N \log N + \log M)$ とし、complexity と要点は累乗をまとめて $O(N \log N)$ とする。矛盾ではないが、3 か所の一致（F1）として $\log M$ の扱いをそろえるとよい
- 根拠：fact.md F1
- 直し方：表の値を $O(N \log N)$ にして下の注意で $a_d^M$ の $O(\log M)$ に触れるか、complexity と要点に「累乗は $+\,O(\log M)$」を添える

### 8（直すとよい）出典 F9：Nyaan の Multipoint Evaluation のページの説明

- 場所：`#references` の「Nyaan「Multipoint Evaluation」：多点評価の積の木と余りの木の流れ」
- 問題：このページは説明の文章がなく、ProductTree と余りで下ろす C++ のコードだけである。「流れ」を読み取れるのはコードからで、読者が解説の記事を期待すると外れる
- 根拠：ページを読んだ結果（@brief だけで、計算量の記述もない）
- 直し方：「多点評価の実装（積の木を作り、余りを葉へ下ろすコード）」のように、コードであることが分かる書き方にする

## 執筆者の未解決の点への答え

- 「difficulty 2200 以上の G・Ex で現れる」：台帳で FPS を approach に持つ問題（abc303_h 2501・abc318_h 2785・abc462_g 2232 など）と合う。見当としての書き方で問題ない
- ABC318 Ex の exp の導出：閉路ごとに確率 $1/t$ で独立になる点は正しい（$Q$ を一様に選ぶと、互いに素な辺の集合の上の相対順位は独立）。式も全探索と一致した。ただし「小さい順が消す辺」の説明が逆（指摘 1）
- exp の定数倍：N = 5×10^5 で 0.43 秒（指摘 3）
- 台帳の提案の abc318_h の summary・approach は、drken の記事の問題の説明と合う。approach の「正しい組の数を閉路ごとの確率 1/t の…」は、指摘 1 を直しても文言はそのまま使える。checked に 2026-10-22 を入れてよい

## 総合の判定

小さな直しで可（直すべき 2 件・直すとよい 6 件）。直すべきは ABC318 Ex の「番号最大」を「番号最小」に直すこと（3 か所）と、`#signs` の本文から練習 ABC303 Ex の解き方を外すことで、どちらも数語の修正で済む。数式・計算量・コード片・Library Checker の対応はすべて確かめて正しかった。
