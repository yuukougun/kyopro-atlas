# b5 検証：mex

- 対象：docs/patterns/mex.md、snippets/mex/window-min.{cpp,yaml}、docs/img/mex/number-line.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py mex --out <作業用の場所>` で 360px・720px の PNG にして目で確かめた（白の背景つきなのでダークでも読める）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page mex`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/mex`：コンパイル 1 回・期待と違う 0。手でも `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、警告なし・サニタイザの報告なし（`5 3 / 0 1 0 2 1` → 2）。コード片の main は素朴な方法とのランダム照合 2000 回と mex_of の境界（空・{1,2}・{0,1,3}・{0,1,2}）を assert で確かめている。cases は M = N・N より大きい値・答えが N・答え 0 を含み、手計算と一致（C1・C2）
- 取り込みの印 `mex`・`gaps` はファイルの start・end と一致。本文の記号（last・gap・番兵 −1 と N・0-indexed）とコードがそろう（C3・C4）。書き方は §9 どおり（C5）。ACL は使っていない
- リンク先の anchor：binary-search-answer#monotonicity、complexity-estimation#amortized、two-pointers#fixed-window・#two-types、grundy-number#abc368_f・#definition・#dp、interval-set#applications、lazy-segment-tree-patterns#challenge・#reformulate、ordered-set#mex・#practice、segment-tree-binary-search#predicate-patterns、glossary#amortized-complexity、construction#checker・#necessary-conditions、contribution#swap-roles、thinking/fix-variable.md、本ページの #examples・#practice・#properties：すべてある
- 作業用の場所の Python で、長さ 1〜8・値 0〜N のランダムな列 3000 個について次を素朴な方法と比べ、すべて一致した
    - 例題の別解「最初の窓の mex と、窓から出て個数が 0 になった値の最小」
    - 窓の mex の最大値の判定「0..x−1 をすべて含む窓があるか」の最大の x
    - 全区間の mex の総和 = Σ_k #{0..k をすべて含む区間}
    - 区間の mex のクエリ「last[v] < l となる最小の v」（last は r より前の最後の出現）
- 執筆者の未解決の点 1（窓の mex の最大値・区間の mex のクエリの先読み）：上の照合で正しい。判定は単調（mex ≥ x なら mex ≥ x−1）、判定 1 回 O(N)、全体 O(N log N) も正しい。台帳に問題がなくても、一般的な方法として書いてよい
- 未解決の点 2（全区間の総和の O(N log N)）：値 k を加えると左端 L の最小の右端は max(今の値, L 以降の k の最初の出現) になる。今の値が L について単調なので、各区間での chmax は「今の値が c 未満の部分（区間の左側）」への代入になり、二分探索と区間代入で書ける。区間の数は出現回数 +1 の合計で O(N)。lazy-segment-tree-patterns の力試し ABC470 G の方針（同じ言い換え、Segment Tree Beats でもよい）とも一致し、本文の「区間代入にする・全体 O(N log N)」は正しい（ただし指摘 2）
- 未解決の点 3（用語集に mex がない）：今は張らないのが正しい。用語集への提案はメインの判断
- 性質の主張（値の上限、mex ≥ k ⇔ 0..k−1 を含む、単調性、追加で変わるのは x = mex のときだけ、削除で x < mex なら x に下がる、窓の最小値の言い換えの証明、セグメント木の `max_right(0, f)` で f(e()) = true、木のパスの「1 本のパスに並ぶ」条件、接頭辞の mex が単調で i 以下）：反例なし（F2）
- 例と図：A = (2, 0, 4, 1, 5, 1) の mex 3 → (2, 0, 4, 1, 5, 3) で 6 → 0 を 7 にして 0。本文・図・代替テキストで一致（F3・G5）。確認問題（長さ 5 で mex 5 は並べ替えだけ）も正しい
- 出典（F5・F9）：ikatakos ABC194 は制約 A_i < N・値を固定して隙間を見る・答えが N になりうる点を書いており本文と一致。ikatakos ABC438 は頂点が 0-indexed、i ≤ j の全パス、0 を根にした部分木の大きさ、端 a・b の更新と端以外のパスの頂点で打ち切る O(N) で、練習の方針と一致。hamayan は答えの二分探索＋窓（O(N log N)）で別解の記述と一致。drken ABC330 E は mex ≤ N と出ていない値の set で一致。いずれも付録 B のドメイン。本文の例（A = (2,0,4,1,5,1) など）・文の並びは出典と別で、近すぎない（F8）
- 要点・front matter の complexity・本文の計算量は一致（F1・F10）。図：360px で文字は 11px 以上で読め、重なり・はみ出しなし。viewBox 380×352 と width・height が同じ比。catalog の visual は static・priority 2 で静的な図で足りる（G3・G6・G7）

## 台帳への提案（検証で確かめた）

- abc194_e｜checked｜2026-10-22｜ikatakos・hamayan で問い・制約・解法を確かめた
- abc438_f｜checked｜2026-10-22｜ikatakos で問い（0-indexed の頂点、i ≤ j の全パス）と解法を確かめた
- 執筆者の提案どおり、両問の evidence の 1 件目（ikatakos の一覧のページ）は外してよい

## 指摘

### 1. 直すとよい｜事実（F5）・分かりやすさ（U7）｜#overview の表の 2 行目「値の範囲が大きい・区間でまとめて入る」の代表 ABC330 E、#interval-values の最後の文

- **問題**：ABC330 E は 1 点の書き換えの問題で、値が区間でまとめて入ることはなく、N より大きい値は無視できるので「値の範囲が大きい」も効かない。区間で値が出入りする問題の例を探した読者には、行と代表がかみ合わない。また #interval-values の「1 点の書き換えでも、値の範囲が大きく座標圧縮したくないときは、同じ持ち方で解ける」は、多重集合では値ごとの個数（map）も別に要ることに触れておらず、mex ≤ N で大きい値は読み飛ばせるという #properties の話とも噛み合わない
- **根拠**：台帳 abc330_e の summary「1 点を書き換えるたびに数列の mex を答える」。interval-set#applications の mex の型も「個数が 0 から 1 になったら追加、1 から 0 になったら削除」で、個数を持つ前提
- **直し方**：2 行目の代表を「—」にする（1 行目に ABC330 E があるので足りる）か、「別解として区間の集合でも解ける」と表の後の文に回す。最後の文は「1 点の書き換えでも、値ごとの個数と合わせて持てば同じ形で解ける（interval-set の練習 ABC330 E）」のようにする

### 2. 直すとよい｜分かりやすさ（U3）｜#sum-of-mex の「列の全区間」の項目

- **問題**：「最小の右端が L について単調であることを使い、更新を区間代入にする」の間が飛んでいる。読者は「なぜ代入で済むのか」「何を代入するのか」で止まる
- **根拠**：上の確かめのとおり、値 k を加えたときの更新は「最小の右端を、L 以降の k の最初の出現との max にする」で、これが単調性により区間の左側への代入になる、という 2 段がある
- **直し方**：「値 $k$ を加えると、左端 $L$ の最小の右端は『今の値』と『$L$ 以降で最初に $k$ が出る位置』の大きい方になる。今の値が $L$ について単調なので、この max は区間の一部への代入になる」の 1〜2 文を足す

### 3. 直すとよい｜事実（F1）｜#online-mex の「追加だけなら、戻らないポインタで足りる」の囲み

- **問題**：「$m$ は全体で $N$ 回しか増えない」とあるが、初めの列の長さ $N$ に $Q$ 回の追加をすると要素は $N + Q$ 個になり、$m$ は $N + Q$ まで増えうる。直後の「合計 $O(N + Q)$」とも数が合わない
- **根拠**：mex は要素の数以下（#properties の値の上限）。追加 Q 回後の要素数は N + Q
- **直し方**：「$m$ は要素の数を超えないので、全体で $N + Q$ 回しか増えない」とする

### 4. 直すとよい｜記法（F7）｜#interval-values の「区間の追加・削除はならし $O(\log N)$」

- **問題**：この節では $N$ が何か定まっていない（前の節では列の長さ）。interval-set では $N$ は区間の数
- **根拠**：interval-set の要点「（$N$ は区間の数）」
- **直し方**：「ならし $O(\log N)$（$N$ は持っている区間の数）」とするか、「1 回ならし $O(\log Q)$（$Q$ は操作の回数）」とする

## 総合の判定

小さな直しで可。直すべき 0、直すとよい 4。性質の主張・例題と練習の方針・図・コード片はすべて資料・全探索・実行で確かめ、誤りはなかった。
