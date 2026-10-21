# fenwick-tree の検証（工程8b・バッチ b1）

- 対象：docs/ds/fenwick-tree.md、snippets/fenwick-tree/{acl-usage,own-bit,count-by-value,range-add-sum}.{cpp,yaml}、docs/img/fenwick-tree/boxes.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page fenwick-tree`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/fenwick-tree -v`：4 片・各 3 case、期待と違う 0
- 手で `g++-15 -std=gnu++23 -O1 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルした（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）。警告は出ず、全 case の出力が一致し、サニタイザも何も報告しなかった。各コード片は素朴な計算と照らす `assert` を持つ
- 総当たり（scratchpad/v-fenwick-tree/brute.py）。食い違いはどれも 0
  - $N = 1 \sim 129$ のすべての $i$ について、add の通る添字の列は「$i$ を含む箱 $(j - \mathrm{lowbit}(j), j]$ を短い順に並べたもの」と一致した。各長さで $i$ を含む箱は高々 1 つで、回数は $N$ のビット数以下だった（折りたたみの証明・invariants の 2 つ目の主張・operations の回数の上限を確かめた）
  - 線形時間の構築では、構築した後のすべての $t[i]$ が区間 $(i - \mathrm{lowbit}(i), i]$ の和と等しかった（ランダムな列 3000 個）
  - BIT 上の二分探索（非負の値、$w \ge 1$）は、左から順に足していく素朴な方法と一致した
  - 接頭辞の max（chmax の更新だけ）は、素朴な接頭辞の max と一致した
- 例題・練習の方針を総当たりで確かめた（p231.py・p340.py）。食い違いはどれも 0
  - abc351_f の $A_j \cdot c - s$ の和は、$\sum_{i<j} \max(A_j - A_i, 0)$ と一致した
  - abc231_f は「$A$ 昇順・同じ $A$ は $B$ 降順、同じ組はまとめて入れてから数える」で数えた結果が、全組 $(i, j)$（$i = j$ も含む）の数え上げと一致した
  - abc340_e は「取り出し量を一点で引き、商は全体加算、余りは次の箱からの区間加算（端を跨ぐなら 2 つ）」の差分の列が、愚直なシミュレーションと一致した。本文の方針は正しい
- 数値の見積もりを計算で確かめた
  - #what-it-does の $4 \times 10^{10}$、#boundaries の $2 \times 10^{14}$、#pitfalls の約 $2 \times 10^{10}$ は正しい
  - practice2_b の和の最大は、初期値 $5 \times 10^5 \cdot 10^9$ と加算 $5 \times 10^5 \cdot 10^9$ を合わせて $10^{15}$ で、本文の「約 $10^{15}$」と合う
  - abc351_f の $\frac{N(N-1)}{2} \cdot 10^8 \approx 8.0 \times 10^{18} < 9.22 \times 10^{18}$ は正しい
- ACL：`~/lib/ac-library-master/document_ja/fenwicktree.md` と `atcoder/fenwicktree.hpp` を照らした。囲みと #boundaries の記述はどれも合う
  - 型は `int/uint/ll/ull/modint`
  - 計算量は構築 $O(n)$、add・sum が $O(\log n)$
  - `sum(l, r)` は半開区間で、`0 ≤ l ≤ r ≤ n` を assert する
  - 内部は `to_unsigned_t` で持ち、あふれたら $\bmod 2^{\mathrm{bit}}$ の値を返す
  - 初期値の配列を受け取るコンストラクタはない
- 問題：`python3 tools/ap.py show` で 8 問の題名と diff を確かめ、本文と一致した（practice2_b は diff なし）
- 出典（atcoder.jp・codeforces.com は開いていない）
  - drken の ABC185 F：$N, Q \le 3 \times 10^5$。添字は 1-indexed の閉区間 $[x, y]$ で、本文と合う
  - drken の ARC068 E：「長さ $d$ 以上は必ず踏む」・長さの順に入れる・$O(N \log N + M \log^2 M)$ で、本文と合う
  - syamashi（note）の LEQ の記事：mod の値は書かれていない（執筆者の未解決の点のとおり）
  - ikatakos の ABC221 の記録（https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2021/1002_abc221 の E の節）：法は **998244353** で、BIT の位置 $A_j$ に $2^{-j}$ を足し、$2^{i-1}$ を掛ける解き方である。本文の練習の方針（`fenwick_tree<modint998244353>`）は正しい
  - abc340_e の第三者の BIT の解説は見つけられなかった（ikatakos の ABC340 の記録には E の節がない）。方針は上の総当たりで確かめた
- 図：chrome-headless-shell 146（~/.cache/puppeteer）で、boxes.svg を画像にした
  - 幅は 626px と 358px（スマホ 390px の画面での表示幅）で、どちらも 2 倍の密度（scratchpad/v-fenwick-tree/w626.png・w358.png）
  - 和文のフォントは v-doubling の一時の fontconfig を使った
  - 背景は白で塗られ、ダークの背景の上でも読める
  - sum(7) は塗り、add(3) は太い破線で区別しており、色だけに頼っていない。両方に当たる t[4] は塗りと破線を併せ持つ
  - 箱の位置・長さ・ラベルは本文（$t[6] = a_5..a_6$ など）と一致する
- 動く図：catalog の visual は priority 2 である。本文にはコメントで div を置き、静的な SVG で代えている。手引きの範囲内である

## 指摘

### 1｜直すべき｜図（G3）｜boxes.svg のスマホでの文字の大きさ

- **問題**：viewBox の幅は 626、font-size は 12〜14 である。表示幅 358px では文字が約 6.9〜8px になり、`t[1]` などの箱のラベル・2 進数の行・凡例が読みづらい
- **根拠**：w358.png での実測による。358 / 626 × 13 ≈ 7.4、358 / 626 × 12 ≈ 6.9。lis・dp-dag・doubling の検証と同じ基準（スマホで 10px 以上）に届かない
- **直し方**：左の「長さ 8」などの見出しの列（幅 約 100）をなくす。代わりに長さを各段の右端か箱の中に書くか、2 進数の行の下に一言で添える。列の間隔 62 → 50 程度に詰め、viewBox の幅を 450 前後にする（358 / 450 × 13 ≈ 10.3）。または font-size を 18 前後に上げ、幅を保ったまま箱の高さを広げる。凡例は今の 2 行のままでよい

### 2｜直すとよい｜分かりやすさ（U2）｜#operations の「add が正しい理由」

- **問題**：見出しは「正しい理由」だが、本文で述べているのは「最下位の 1 の位置が真に上がるので $\lfloor \log_2 N \rfloor + 1$ 回で終わる」という速さ（停止）である。正しさ（$a_i$ を含む箱をすべて通る）は折りたたみの中にしかない。sum の段落が「速い理由」なので、対で読む読者は add の正しさの直感を本文で得られない
- **直し方**：見出しを「add が正しく速い理由」とし、本文に直感の 1 文を足す。たとえば「$i$ を含む長さ $2^k$ の箱は、$i$ の下の $k$ 桁を切り上げた位置にある。$i + \mathrm{lowbit}(i)$ はちょうどこの切り上げを短い順に行う」

### 3｜直すとよい｜事実（F5）｜練習 abc221_e の要約と台帳

- **問題**：答えを 998244353 で割った余りで出すことが、要約にない。方針の `modint998244353` も、今の evidence（syamashi の記事は法の値を書いていない）だけでは裏付けられない
- **根拠**：ikatakos の ABC221 の記録の E の節に、法 998244353 が書かれている
- **直し方**：執筆者の提案どおり、本文と台帳の summary を「先頭 ≤ 末尾となる長さ 2 以上の部分列の個数を 998244353 で割った余りを求める。」にする。台帳の evidence に ikatakos の URL（上記）を足し、`checked: 2026-10-21` を入れる

### 4｜直すとよい｜構成（U5）｜#pitfalls と #boundaries・#what-it-does の重なり

- **問題**：落とし穴の 5 項目のうち 3 項目が、ほかの節の言い直しである
  - 「区間 min に使おうとする」は #what-it-does の繰り返し
  - 「値で配列を取る」は #boundaries の「配列の長さは値の上限ではなく個数」の繰り返し
  - 「答えの型」は #boundaries の「値の型」とほぼ同じ
- **直し方**：#pitfalls は、ほかの節にない実際のバグに寄せる。候補は 3 つある
  - 「読む前に足す」
  - 「ACL で XOR」
  - 「1-indexed の問題で `sum(L, R)` と書いて 1 つずれる」
  - 重なる項目は 1 行にしてリンクで済ませる。#boundaries 側を短くしてもよい

### 5｜直すとよい｜事実（F5）｜練習 abc340_e の evidence

- **問題**：今の evidence（tayu0110）は平方分割による解き方で、「区間加算・一点取得に帰着する」ことの裏付けにとどまる（執筆者の報告のとおり）。本文の方針は、上の総当たりで正しいと確かめた
- **直し方**：差分の BIT か双対セグ木で解いた第三者の解説が見つかれば、evidence に足す（メインのバッチの終わりでよい）。本文はこのままでよい

### 6｜直すとよい｜構成（手引き §5・§13.1）｜節の並びと定型の anchor

- **問題**
  - 手引きの technique の並び（… → 落とし穴 → ACL では → 例題 …）に対し、このページは「ACL では」を #boundaries の中に置き、落とし穴を BIT 上の二分探索の後に置いている
  - 使い分けの anchor が `choosing` で、手引き §13.1 の定型 `comparison` と違う（執筆者は骨格の anchor を守った。見本の lazy-segment-tree も同じ）
- **直し方**
  - 並びは、ACL の囲みが #boundaries の符号なしの話とつながっているので今のままでも読める。直すなら #pitfalls の直後に移す
  - anchor はメインで方針を決める（執筆者の手引きへの提案のとおり）。このページだけでは直さない

## 総合の判定

**小さな直しで可**（直すべき 1：図の文字の大きさ。直すとよい 5）。

計算量・ACL の API・保つ性質・証明・線形時間の構築・BIT 上の二分探索・変種・例題と練習の方針は、どれも一次資料か総当たりで確かめて誤りがなかった。執筆者の未解決の点のうち abc221_e の法は 998244353 で、本文は正しい。abc185_f の値の上限は本文で触れていないので問題ない。
