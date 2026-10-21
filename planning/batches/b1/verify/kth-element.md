# kth-element の検証（工程8b・バッチ b1）

- 対象：docs/ds/kth-element.md、snippets/kth-element/bit-kth.{cpp,yaml}・reverse-insert.{cpp,yaml}、docs/img/kth-element/bit-binary-search.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page kth-element`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/kth-element`：2 片・コンパイル 2 回・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）。cases の期待出力は手で追って一致を確かめた（bit-kth の 1 件目は {6, 2, 6} から 2 番目 = 6、3 番目なし、1 番目 = 2）。どちらの main も multiset・vector の素朴な方法と assert で比べている
- `npx textlint docs/ds/kth-element.md`：エラー 0・警告 31（数式の中の括弧・数式を含む文の長さ・囲みの中の行。手引き §13.8 の許容の範囲）
- `python3 tools/ap.py show`：arc033_3（C. データ構造、1641 参考値）・abc241_d（D. Sequence Query、1177）・abc281_e（E. Least Elements、1334）・abc392_f（F. Insert、1395）の実在と diff を確認。囲みの label・diff と一致し、練習は易しい順
- ACL：`~/lib/ac-library-master/document_ja/segtree.md` の max_right（返り値の 2 条件・要件 `f(e()) = true`・$O(\log n)$）と「ACL では」の囲みが一致。`third_party/ac-library/atcoder/fenwicktree.hpp` で `data` が private であることを確認
- 試しのプログラム（一時置き場の neg.py。リポジトリには置いていない）
    - 図の例（個数 $(1,0,2,1,0,0,3,1)$・$K = 5$）：$t[1..8] = (1,1,2,4,0,0,3,8)$、試す順 $t[8], t[4], t[6], t[7]$、答え 7。本文・図・代替テキストと一致
    - 確認問題 3（{1, 3, 4} で 2 を誤って削除）：$t[2]=0$・$t[3]=1$・$t[4]=2$、`kth(1)` は 3 を返す。答えのとおり
    - 逆順の挿入の例（$N = 4$、$P = (1,1,2,1)$）：前からも逆順からも $(4,2,3,1)$
    - 個数が負の配列での BIT 上の二分探索：返す位置 $r$ は必ず「$r-1$ までの和 $< k \le$ $r$ までの和」を満たす。正しい多重集合から存在しない値を 1 回以上削除した状態（個数が正しい値以下）では、20 万回の乱択で、返す位置が本当の答えより手前になったことは 0 回、先へ進んだことは約 45%（指摘 2）
    - 歩幅の初期値を $N$（2 べきでない）にすると壊れること：$N = 6$、個数がすべて 1 で $k = 2..6$ が誤り。ただし原因は $\mathrm{step}$ が 2 べきでないことで、$\mathrm{pos}$ が $2 \cdot \mathrm{step}$ の倍数でなくなるからではない（指摘 1）。$N$ 以上の 2 べきから始めても（$\mathrm{pos} + \mathrm{step} \le N$ の条件があれば）結果は同じ（5 万回で不一致 0）
- 外側の二分探索の目安：$\log_2(2 \times 10^5) \approx 17.6$、$2 \times 10^5 \times 17.6^2 \approx 6.2 \times 10^7$。本文の「およそ $6 \times 10^7$」は正しい
- evidence・参考を読んで確かめたこと（atcoder.jp・codeforces.com は開いていない。qiita.com・*.hatenablog.com の drken1215・kyo-pro は付録 B にある。yuulis.hatenablog.com は執筆者が check_noai で確かめたもの）
    - drken の Qiita：arc033_3 は $1 \le Q \le 200000$、$1 \le X \le 200000$。種類 2 は「X 番目に小さい数を答えて削除」。方法は「値の範囲が小さいときの BIT（と平方分割）→ 座標圧縮して BIT → K が固定なら 2 つのヒープ → 平衡二分探索木」の順。本文の比較の表は 8 方法で行の分け方・言い回しが違い、例の数値も記事にない（記事に BIT 上の二分探索の数値例はない）。F8 の問題なし
    - drken の Qiita は「x 番目が存在する」保証を書いておらず、コードも確かめずに引いている（執筆者の未解決の点。指摘 9）
    - Yuulis「ABC 392 F」：$1 \le N \le 5 \times 10^5$、$1 \le P_i \le i$。逆順に処理し、空きを 1 にした和のセグメント木の `max_right` で探す。本文の節・練習の方針と一致
- 図：chrome-headless-shell 146（puppeteer のもの）で bit-binary-search.svg を 640×445（等倍）と、幅 358px の枠（暗い背景の上）で画像にした。和文も表示された。背景は白で塗られ、`viewBox` あり、文字はテキストのまま（`font-family="sans-serif"`）。進んだ・進まなかったは色に加えて実線・破線と ○・× でも区別している

## 執筆者の未解決の点について

- **abc392_f の N の上限**：Yuulis の記事で $N \le 5 \times 10^5$ を確かめた。本文の「$N$ が数十万だと間に合わない」は正しい。具体的に「$N = 5 \times 10^5$ では」と書いてもよい（任意）
- **arc033_3 で x 番目が必ず存在するか**：一次資料（問題文）は開けず、drken の記事にも明記がない。記事のコードは存在を前提にしている。解法の詳細は「存在する前提」と一言断るとよい（指摘 9）
- **外側の二分探索の目安**：上のとおり計算で確かめた。正しい

## 指摘

### 1｜直すべき｜事実（F2）｜#bit-binary-search「境界」の「歩幅の初期値」

- **問題**：「$N$ が 2 べきでないのに $\mathrm{step} = N$ から始めると、$\mathrm{pos}$ が $2 \cdot \mathrm{step}$ の倍数でなくなり、$t[\mathrm{pos} + \mathrm{step}]$ が区間の和でなくなる」の理由が誤りである。$N = 6$ なら最初は $\mathrm{pos} = 0$ で $12$ の倍数だが、$\mathrm{lowbit}(6) = 2$ なので $t[6]$ は $(4, 6]$ の和で $(0, 6]$ の和ではない。壊れる原因は $\mathrm{step}$ が 2 べきでないこと（$\mathrm{lowbit}(\mathrm{pos} + \mathrm{step}) = \mathrm{step}$ は $\mathrm{step}$ が 2 べきのときだけ成り立つ）。また半分にしていくと $6 \to 3 \to 1$ と 2 べきでない歩幅が続く
- **根拠**：neg.py で $N = 6$・個数すべて 1 のとき、$\mathrm{step} = N$ から始めると $k = 2..6$ で誤った位置を返す。$\mathrm{lowbit}(6) = 2$
- **直し方**：「$\mathrm{step}$ は 2 べきでなければならない。$N$ が 2 べきでないのに $\mathrm{step} = N$ から始めると、$\mathrm{lowbit}(\mathrm{pos} + \mathrm{step}) \ne \mathrm{step}$ となり（$N = 6$ なら $t[6]$ は $(4, 6]$ の和）、$t[\mathrm{pos} + \mathrm{step}]$ が区間 $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ の和でなくなる」とする。必要なら「$N$ 以上の 2 べきから始めても、条件 $\mathrm{pos} + \mathrm{step} \le N$ があれば正しい」を添える

### 2｜直すとよい｜事実（F2）｜#pitfalls「個数が負になる」

- **問題**：「答えより手前で止まったり先へ進んだりする」とあるが、存在しない値を削除しただけの状態（各個数が本当の個数以下）では、返す位置は本当の答えより手前にならない。返す位置 $r$ では誤った接頭辞の和が $k$ 以上で、本当の和はそれ以上なので、$r$ は本当の答え以上である。起きるのは「先へ進む（飛び越える）」ほうで、確認問題 3 もその例である。手前で止まるのは、狂った答えでさらに削除を重ねた後など、二次的な場合だけ
- **根拠**：neg.py。20 万回の乱択（1 回でも複数回でも存在しない値を削除）で、手前は 0 回、先は約 45%
- **直し方**：「本当の答えを飛び越えて先の位置を返す（確認問題 3）。その答えで削除を続けると、以後の結果も狂う」とする

### 3｜直すとよい｜事実（F2）・分かりやすさ（U4）｜#bit-binary-search「境界」の「K 個に満たないとき」

- **問題**：「全体の和が $k$ 未満なら、毎回進んで $\mathrm{pos} = N$ で終わり」の「毎回進んで」は不正確である。$N$ が 2 べきでないと、$\mathrm{pos} + \mathrm{step} > N$ の回は進まない（$N = 6$ なら歩幅 4・2 で進み、歩幅 1 は $7 > 6$ で進まない）。終わりの $\mathrm{pos} = N$ は正しい
- **根拠**：擬似コードを $N = 6$ で手で追った
- **直し方**：「範囲に収まる歩幅ではどれも進むので、$\mathrm{pos} = N$ で終わり」とする

### 4｜直すとよい｜分かりやすさ（U3）｜#bit-binary-search「保つ性質」の最後の段落

- **問題**：2 つめの性質は「試した後、答えは $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$（step は試した歩幅）」だが、続く文は「最初は … $\mathrm{step}$ を $N$ 以下の最大の 2 べきにすれば $2 \cdot \mathrm{step} > N$ なので、2 つめの性質が成り立つ」と、試す前の形 $(\mathrm{pos}, \mathrm{pos} + 2 \cdot \mathrm{step}]$ を前提にしている。最初の状態では $(0, \mathrm{step}]$ に答えがあるとは限らないので、文字どおり読むと食い違う
- **直し方**：「最初は $\mathrm{pos} = 0$ で、答えは $(0, N] \subseteq (0, 2 \cdot \mathrm{step}]$ にある。歩幅 $\mathrm{step}$ を試すと、この範囲の前半 $(\mathrm{pos}, \mathrm{pos} + \mathrm{step}]$ か後半かが決まり…」のように、試す前は幅 $2 \cdot \mathrm{step}$、試した後は幅 $\mathrm{step}$ と書き分ける

### 5｜直すとよい｜図（G5・G3）｜bit-binary-search.svg の下の注記と「試す」の文字

- **問題**：(a) 「pos=6」（x = 470 中央）と「答え 7」（x = 500 中央）の文字がくっつき、等倍の画像で「pos=6答え 7」と読める。(b) 「試す1×」「試す2○」は日本語として不自然で、何の番号か分かりにくい。(c) 幅 358px に縮めると 12px の文字が約 7px になり、t[1]〜t[7] の枠の文字と下の注記が読みにくい
- **根拠**：chrome-headless-shell 146 で 640px と 358px 幅に描いた画像（一時置き場の full.png・narrow.png）
- **直し方**：(a) 「答え 7」を下の段（y を 14px ほど下げる）へ移すか、「pos=6」を枠線の左に寄せる。(b) 「1 回目 ×」「2 回目 ○」か「① ×」のようにし、下の 4 行も「1 回目：…」にそろえる。(c) 下の 4 行と注記は本文の箇条書きと同じ内容なので、図から外して縦を縮め、枠の文字を 13〜14px にする

### 6｜直すとよい｜手引き（§4・§13.1）｜#comparison の見出しと節の順序

- **問題**：手引き §13.1 では anchor `comparison` は定型の `## 使い分け {#comparison}` に使い、technique では使い分けは確認問題の後に置く。このページは catalog の sections の anchor が `comparison` のため、「方法の比較」を本文の前半に置いている。また「ACL では」は落とし穴の後に独立させる型だが、#bit-binary-search の中にある。どちらも執筆者が報告で判断を求めている
- **直し方**：メインの判断に任せる。比較の節が最初に引かれる内容なので、今の位置のままでよいと考える（sections に載る中身の節として扱い、手引きに「sections の anchor が定型の anchor と重なるときは sections を優先する」と足す）

### 7｜直すとよい｜コード（C6）｜#bit-binary-search「境界」・bit-kth.cpp

- **問題**：`bit_floor` は C++20 の機能で、本文に「C++20 の `bit_floor`」とはあるが C++ の章へのリンクがない
- **直し方**：「C++20 の [`bit_floor`](../cpp/cpp-math-functions.md#bit-functions)」とリンクする

### 8｜直すとよい｜分かりやすさ（U7）｜#practice の方針「ABC241 D」

- **問題**：BIT で解く場合の説明が「$x$ 以下で大きい方から $k$ 番目」だけで、もう一方の質問（$x$ 以上で小さい方から $k$ 番目）と、答えがない場合（$s < k$）の扱いがない
- **直し方**：「$x$ 以下の個数 $s$ から $s - k + 1$ 番目（$s < k$ ならなし）、$x$ 未満の個数 $s'$ から $s' + k$ 番目（全体が足りなければなし）を BIT 上の二分探索で求める」とする

### 9｜直すとよい｜事実（F5）・記法（F7）｜#arc033_3 の解法の詳細

- **問題**：(a) 「$O(\log 2 \times 10^5)$」は $O(\log(2 \times 10^5) )$ とも読めず書き方が不自然である。(b) x 番目が存在する保証を確かめられていない（未解決の点）
- **直し方**：(a) 「どちらの操作も $O(\log X)$ なので、全体で $O(Q \log X)$」とする（$X$ は数の上限）。(b) 「x 番目の数は存在する前提で書く」と一言断るか、`kth` が配列の外を返したときは来ないことを確かめる旨を添える

## 台帳への提案

- arc033_3：`checked: 2026-10-21`（drken の Qiita で $Q, X \le 2 \times 10^5$ と問いを確認。存在の保証は未確認）
- abc392_f：`checked: 2026-10-21`（Yuulis の記事で $N \le 5 \times 10^5$・$1 \le P_i \le i$ と問いを確認）
- abc241_d の kth-element の summary を k → K に直す提案（執筆者の報告）に賛成する。手引き §13.7 のとおり、メインが台帳を直して fix_problems を流す

## 総合の判定

**小さな直しで可**。直すべき 1 件（指摘 1：歩幅の初期値の説明の理由の誤り）。直すとよい 8 件。手順・保つ性質・確認問題・図の値・逆順の挿入の正しさ・ACL の囲み・コード片はどれも確かめて正しい。
