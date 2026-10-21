# inline-dp の検証（b2）

- 対象：docs/dp/inline-dp.md、snippets/inline-dp/relax-edges・shift・intervals・stack-lazy（.cpp・.yaml）、docs/img/inline-dp/row-diff.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 確かめたこと

- `python3 tools/check_pages.py --page inline-dp`：エラー 0・警告 0
- `python3 tools/fix_problems.py --check --page inline-dp`：直すべき行 0
- `python3 tools/check_snippets.py snippets/inline-dp`：4 本・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `npx textlint docs/dp/inline-dp.md`：エラー 0・警告 16（数式を含む文の長さ・読点の数、半開区間 `[l, r)` の括弧の対の誤検出、220 行の「と」）。誤検出か数式のためで、残してよい
- サニタイザ：4 本を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルし、乱数の小さな入力 400 組ずつ（辺の長さ 10^9、得点 ±10^9、値 ±10^9、C = 10^9 を含む）で、各コードの assert（素朴な 2 次元の表・全探索との突き合わせ）を動かした。失敗 0、サニタイザの報告 0
- 本文 170 行の「長さの下限 $L$ なら最後に読む範囲を $[0, i - L + 1)$ に縮める」：stack-lazy.cpp を $L = 2$ に変えた版（`seg.prod(0, max(0, i - 1))`）を、長さ 2 以上に限った素朴な DP と乱数 600 組で比べた。行けない状態（$+\infty$）の扱いをそろえれば食い違い 0。$i < L$ では `prod(0, 0)` が `e()` = $+\infty$ を返し、そのまま $+\infty$ 扱いで正しく動く（指摘 4）
- 本文の数値：$N, K \le 2 \times 10^5$ で $4 \times 10^{10}$、$MK \le 50 \cdot 2 \times 10^5 = 10^7$、図の値（k = 1〜4 で dist が 3・5・5（変わらず）・6）は relax-edges の case 1 と一致。確認問題 3 の式変形も正しい
- 本文の主張を定義から確かめた：update-changes の「$a \ne b$ なら読む値は前の行のまま」、global-shift の $\mathrm{dp}[t+1][v] = a[(v - t - 1) \bmod N] = \mathrm{dp}[t][v-1]$、lazy-segment-tree の状態で足りる理由・2 を 3 より先に行う理由・落とし穴の $-2^{60}$ で足りる理由（区間加算は書き込み済みの添字 $\le i$ にしか届かない）、with-monotonic-stack のスタックの向き（コードは `a[back] <= a[x]` で降ろすので狭義に減る）と区間 $(q, p]$・ならし $O(N)$。どれも正しい
- ACL：document_ja/lazysegtree.md と照らした。テンプレート引数の順、`mapping(f, x)`・`composition(f, g)`（$f \circ g$）、`apply(l, r, f)`・`prod(l, r)`・`set(p, x)` が $O(\log n)$、半開区間。囲みの記述は正しい
- 問題（ap.py show）：abc271_e（1402）・abc372_f（1722）・dp_w（diff なし）・abc203_e（1750）・tdpc_target（diff なし）・abc480_g（2100）。label・diff は台帳と一致。例題は易しい順。例題 3・練習 2・力試し 1 は目安の範囲
- evidence と参考（どれも付録 B のドメイン。kcpc・kazun-kyopro は check_noai でも指定なし）
  - Kazun ABC271 E：有向辺、$2 \le N \le 2 \times 10^5$、$1 \le M, K \le 2 \times 10^5$、$1 \le C \le 10^9$、自己ループなし、変わるのは $B_k$ の 1 か所だけ、全体 $O(N + M + K)$。本文と一致。到達できないときの出力は書かれていない
  - drken ABC372 F：円環 $i \to i+1$ と追加の $M \le 50$ 本、$N, K \le 2 \times 10^5$、998244353、K 回の歩みの数。頂点を縮める別解。本文と一致
  - KCPC ABC372：「DP 配列全体を毎ターン時計回りにずらすと解釈すれば更新が M 回」と、更新後の値を読んでしまった誤り。本文の説明・落とし穴と一致し、言い回しは十分に違う（F8）
  - Series_205 EDPC W：$N, M \le 2 \times 10^5$、状態・3 つの遷移・遅延セグメント木。本文と一致
  - drken「EDPC W」（台帳の 2 本目の evidence、https://drken1215.hatenablog.com/entry/2021/08/11/005634 ）：$-10^9 \le a_i \le 10^9$、$a_i$ は負になりうる、すべて非負なら全部 1 が最適。執筆者の未解決 2 の答え（指摘 5）
  - kanpurin ABC203 E：盤 $(2N+1) \times (2N+1)$、$N \le 10^9$、$M \le 2 \times 10^5$、黒いポーンのある行だけ更新、ソートで $O(M \log M)$。練習の方針と一致
  - kmjp ABC480 G：「1 個以上の 2 要素以上の連続部分列に分割し、各部分列の最大と最小の差の和」を最小化。dp を遅延セグメント木（区間加算・区間最小）に載せ、単調スタックで prefix の最大・最小を管理する。本文の節と力試しの行の要約・方針と一致
  - kanpurin 典型問題メモ：「更新箇所が限定的である場合に DP 配列を使いまわすことで計算量を削減する DP」と、ABC203 E・ABC271 E・EDPC W などの一覧。drken の Qiita：配列の使い回し、セグメント木での in-place、EDPC W を Starry Sky 木で。どちらも書かれたとおり
- 図：`python3 tools/render_svg.py inline-dp`（360px・720px）と `--width 1000 --scale 2` で PNG にして見た。白い背景・viewBox あり・文字はテキスト（sans-serif）。色に加えて枠の太さと破線（調べたが変わらない）で区別している。文字の重なり・はみ出しなし。値と代替テキストは本文と一致。catalog の visual（priority 2：変化したセルだけ色付けし、1 本の配列の上書きに置き換える）を満たす。1000px の撮影は高さが足りず下が切れたが、道具の側の問題（kth-value の検証と同じ）
- リンク：global-offset#offset・monotonic-stack#dp-transition・lis#binary-search・lis#nesting・knapsack-01#dp-rolling-array・glossary の state・transition・relaxation はどれも anchor がある

## 執筆者の未解決の点への答え

1. abc271_e の到達できないときの出力：Kazun の記事にも書かれておらず、確かめられなかった。本文の「出力は問題の指定に従う」のままでよい（コード片の -1 はコード片の入出力の約束として書かれているので問題ない）
2. dp_w の $a$ の範囲：台帳の evidence の drken の記事に $-10^9 \le a_i \le 10^9$ とある。「負のこともある」は正しい（指摘 5）
3. abc480_g と節の例の重なり：節の例（$C$ を足した一般形）は、力試しの方針の一行で問題の解き方そのものになる。メインの判断に回す（指摘 3）
4. 図は priority 2 の静的な図 1 枚で足りる
5. dp-segment-tree・lazy-segment-tree-patterns・dp-dimension-reduction は今は draft になっている。anchor を付けられる（指摘 7）

## 指摘

### 1. 直すべき｜事実（F2）｜with-monotonic-stack の最後の段落（170 行）

- 問題：「コストが『最大』だけ、あるいは『最大 × 長さ』のような形でも、最大の変わる始点が単調スタックの範囲でまとまる点は同じである」と書き、同じ方法がそのまま使えるように読める。「最大 × 長さ」では使えない
- 根拠：$g_i[j] = \mathrm{dp}[j] + \max A[j, i) \cdot (i - j)$ とすると、$i$ を 1 進めるだけで、最大が変わらない始点 $j$ でも長さが 1 伸びて $g$ が $\max A[j, i)$ だけ増える。スタックの範囲ごとに足す量が違うので、1 歩ごとにスタックの範囲すべてへ区間加算が要る。値が減っていく列ではスタックが $\Theta(N)$ 段のまま残り、全体 $\Theta(N^2 \log N)$ になる。この節の「区間加算は全体で $O(N)$ 回（ならし）」が成り立たない
- 直し方：「最大 × 長さ」を消し、「コストが最大だけ（あるいは最小だけ）なら、スタックを 1 本にすればよい」とする。残すなら「長さに比例する項があると、$i$ を進めるたびに全始点の値が範囲ごとに違う量だけ変わるので、この方法だけでは足りない」と制限を書く

### 2. 直すとよい｜分かりやすさ（U4）｜with-monotonic-stack の 159〜161 行

- 問題：本文だけで実装しようとすると、(a) 各 $i$ で新しい始点 $i - 1$ に $\mathrm{dp}[i-1]$ を書き込む（区間 $[i-1, i)$ は最大 − 最小 = 0）手順と、(b) スタックが空になったときの $q = -1$ の扱いが分からない。どちらもコード（折りたたみの中）にしかない
- 根拠：stack-lazy.cpp 43 行 `seg.set(x, dp[x]);` と 47 行 `int q = smax.empty() ? -1 : smax.back();`。本文の 159 行は $g_i[j]$ を「持つ」とだけ書き、161 行は「1 つ下が $q$」とだけ書く
- 直し方：161 行の前に「まず始点 $i - 1$ の値 $\mathrm{dp}[i-1]$ を 1 点に書く」を、161 行に「スタックが空になるなら $q = -1$ とする」を足す

### 3. 直すとよい｜事実・分かりやすさ（F5・U7）｜力試しと with-monotonic-stack の節（149〜172 行、254〜259 行）

- 問題：執筆者の未解決 3 のとおり、節の例（区間のコスト $C$ + 最大 − 最小）と 170 行の長さの下限で、力試し ABC480 G の解き方がほぼすべて本文に出ている。力試しの方針は「$C = 0$、下限 2」の一言で答えになる
- 根拠：kmjp の解説の解き方（dp を区間加算・区間最小の遅延セグメント木に載せ、単調スタックで最大・最小の変わる範囲を求める）と本文の節が同じ
- 直し方（メインの判断）：(a) 台帳と catalog に提案して ABC480 G をこの節の例題にする（黄の節の例題として本文で扱い、力試しは空にするか別の問題にする）、(b) 力試しのまま残すなら、節の例のコストを「最大だけ」か「最大 − 最小の 2 倍に定数」などに変え、長さの下限の文は残して、方針は「節の DP のどこを変えるか」を読者に考えさせる形にする

### 4. 直すとよい｜分かりやすさ（U4）｜with-monotonic-stack の 170 行

- 問題：長さの下限 $L$ があると $i < L$ の $\mathrm{dp}[i]$ は行けない状態になるが、その扱い（$+\infty$ のまま木に書いてよいか）に触れていない
- 根拠：$L = 2$ に変えた版を素朴な DP と比べると、$+\infty$（ACL の `prod(0, 0)` は `e()` を返す）をそのまま書き込んで正しく動く。$+\infty$ への加算は全体で最大 − 最小の幅（$2 \times 10^9$ 程度）までなので、$2^{60}$ ではあふれない
- 直し方：「$i < L$ では読む範囲が空になり、`prod` は `e()` = $+\infty$ を返す。それをそのまま書き込んでよい（加算は値の幅までなのであふれない）」の 1 文を足す

### 5. 直すとよい｜事実（F5）｜例題 EDPC W の方針（232 行）と参考

- 問題：「得点 $a$ は負のこともある」の根拠が本文にも参考にもない。制約の数値がないので、`long long` で足りるかを読者が見積もれない
- 根拠：台帳の evidence の drken の記事（https://drken1215.hatenablog.com/entry/2021/08/11/005634 ）に $1 \le N, M \le 2 \times 10^5$、$-10^9 \le a_i \le 10^9$ とある。和の絶対値は $2 \times 10^{14}$ まで
- 直し方：解法の詳細の最後の文を「$N, M \le 2 \times 10^5$、$\lvert a \rvert \le 10^9$ なので、得点の和は $2 \times 10^{14}$ までになり `long long` で持つ」とし、参考に drken の記事（「EDPC W の制約と、すべて非負なら全部 1 が最適である点」）を足す

### 6. 直すとよい｜分かりやすさ（U8）｜確認問題 1（263〜264 行）

- 問題：答えが本文 88 行（「この行で読むのは dist[a] で、書くのは dist[b] である。a ≠ b なら…」）の言い直しで、本文の文をそのまま問っている
- 根拠：clarity.md U8 のよくある失敗「本文の文をそのまま問う」
- 直し方：本文から一歩出る問いに変える。例：「同じ緩和を、辺の列 $E$ を後ろから処理したら何が求まるか（頂点 1 からではなく、頂点 $N$ への長さになるよう初期値も変える必要があるか）」や、「辺 $a \to b$ と $b \to c$ が同じ段にまとめて来る問題では、1 本の配列で何に気を付けるか（読む値を先に集める）」

### 7. 直すとよい｜記法（F7）｜90 行・122 行・145 行のリンク

- 問題：執筆者は前提のページが stub だとして anchor なしでリンクしたが、dp-segment-tree・lazy-segment-tree は今は draft で、当てはまる節がある
- 根拠：dp-segment-tree の sections に `values-on-segment-tree`（dp の値を位置や値を添字にしたセグメント木に載せる）、lazy-segment-tree に `acl-standard`（ACL の lazy_segtree で標準の型を呼ぶ）がある
- 直し方：90 行の重み付き LIS のリンクを `../dp/dp-segment-tree.md#values-on-segment-tree` に、145 行の「標準の型」に `../ds/lazy-segment-tree.md#acl-standard` へのリンクを足す（任意）

### 8. 直すとよい｜図（G3）｜row-diff.svg、幅 360px

- 問題：viewBox の幅 700 に 14px の文字で、本文の幅（スマホで約 328px）では文字が約 6.5px になる。360px の PNG では表の数字は読めるが、行のラベル（「辺 1→2（3）」）と凡例・右下の説明文は小さい
- 根拠：render_svg.py の 360px の出力（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-inline-dp/png/inline-dp/row-diff-360.png）
- 直し方：右の「配列 1 本 dist[v]」を表の下へ移して viewBox の幅を 450 前後に縮めるか、右下の説明文 4 行（本文 57 行と同じ内容）を図から外して幅を詰める

### 9. 直すとよい｜分かりやすさ（U6）｜with-monotonic-stack の前提のリンク（151 行）

- 問題：「単調スタック」のリンク先 `monotonic-stack#dp-transition` はスライド最小値の deque による遷移の節で、この節が使う「スタックで $p$ の 1 つ下が $q$ なら、$(q, p]$ の最大は $A[p]$」という見方（左で初めて大きい位置）は、そのページの基本の節にある
- 根拠：docs/ds/monotonic-stack.md の dp-transition の節（170〜185 行）は deque の擬似コードで、スタックの区間の見方は扱わない
- 直し方：151 行のリンクを monotonic-stack のページ（anchor なし、または「左で初めて大きい位置」を扱う節）にする。front matter の related の `monotonic-stack#dp-transition` は catalog どおりなので、変えるなら提案にする

## 台帳への提案（検証役から）

- checked に 2026-10-21 を入れてよい：abc271_e（Kazun）、abc372_f（drken）、dp_w（drken 2021-08-11・Series_205）、abc203_e（kanpurin 個別記事）、abc480_g（kmjp）
- abc480_g の summary は執筆者の提案（長さ 2 以上の区間に分け、最大と最小の差の和の最小）で正しい（kmjp の記事と一致）
- 執筆者の evidence の追加の提案（Kazun・kanpurin 個別記事・KCPC）は、どれも内容を確かめた。足してよい
- tdpc_target は今回確かめていない（持ち主は lis）

## 総合の判定

小さな直しで可。直すべき 1 件（指摘 1：「最大 × 長さ」でも同じ方法が使えるという言い過ぎ）。直すとよい 8 件。コード片 4 本・ACL の囲み・例題の事実・図の値はすべて正しい。指摘 3（力試しと節の重なり）はメインの判断に回す。
