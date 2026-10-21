# ordered-set の検証（工程8b・b1）

- 対象：docs/ds/ordered-set.md、snippets/ordered-set/{neighbors,pareto,adjacent-pairs}.{cpp,yaml}、docs/img/ordered-set/neighbors.svg（動く図はない。catalog の visual は static・priority 2）
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md、手引き planning/style-guide.md

## 確かめたこと

- 検査：`python3 tools/check_pages.py --page ordered-set`（エラー 0・警告 0）、`python3 tools/fix_problems.py --check --page ordered-set`（直すべき行 0）、`npx textlint docs/ds/ordered-set.md`（出力なし・終了コード 0）。コード片は yaml の cases を g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0、`-std=gnu++23 -O2 -Wall -Wextra` で動かし、14 件すべて期待どおり・警告なし
- front matter：`git diff` で変わったのは complexity・stage と要点以降の本文だけ。complexity・要点の計算量・本文が一致する
- コード片：3 片とも `-fsanitize=address,undefined` 付きでコンパイルし、乱数の入力 400 組ずつを Python の素朴な方法（全点を見る・ソートして隣の差を取る・全要素から前後を探す）と比べ、すべて一致、サニタイザの報告なし（作業用の場所 v-ordered-set/gen.py）。pareto は最後の assert（b が狭義の降順）も毎回通る。書き方（bits・using namespace std・マクロなし・`'\n'`・ラムダ）は §9 に合う。取り込みの範囲は core・query だけで要点の数行。`INF = 2e18` は double で正確に表せ、$\pm 10^{18}$ との差 $3 \times 10^{18}$ は `long long` に収まる（本文 75 行どおり）
- 自分で導いた主張を確かめた
    - ABC140 E の式 $(l_1 - l_2)(r_1 - i) + (i - l_1)(r_2 - r_1)$ と、番兵 $0$・$N + 1$ を 2 個ずつ入れる扱い：長さ 2〜8 の順列 500 個で全区間の素朴な和と一致（v-ordered-set/e140.py）
    - ABC245 E の向き（箱を縦の昇順、縦が収まるチョコの横を multiset、`prev(upper_bound(D))`）：小さな入力 3000 組で全割り当ての素朴な判定と一致（v-ordered-set/e245.py）。drken の記事も同じ向き（「箱を縦が小さい順」「S.upper_bound(D[j]) をデクリメント」）で、執筆者の台帳への提案（abc245_e の approach）に賛成する
    - mex が $N$ 以下（鳩の巣）、set が空にならないこと、パレート境界で $b$ が狭義の降順になること・質問の答えが `lower_bound(x)` の点であること：論証を読み、pareto の乱数試験でも一致
    - K 番目付近の番兵を $K$ 個ずつ入れる扱い：`upper_bound(x)` から $K$ 歩戻る・`lower_bound(x)` から $K - 1$ 歩進むとき、番兵は $K$ 個あれば越えない
- 事実の出典：cpprefjp の set::lower_bound（メンバの lower_bound は対数時間）。イテレータの無効化（消した要素だけ）・multiset の erase(x) が全部消すことは cpp-container-idioms の該当節と一致
- 参考の URL：8 件とも開き、題名・著者が書かれたとおり（drken 4 件・kanpurin・kyo-pro・betrue12・cpprefjp）。どれも付録 B のドメイン。記事の要点と本文の方針に食い違いはない（ABC370 D の行ごと・列ごとの set と番兵 $-1$・$W$／$-1$・$H$、ABC385 D の map<int, set<int>> と線分上の走査、ABC330 E の出現回数 0 の値の set、ABC241 D の upper_bound から戻る・lower_bound から進む）。本文の文・例は出典と並びも数値も違い、近すぎる箇所はない
- 問題：7 問とも check_pages で台帳・label・URL・diff が一致し、台帳で確認済み。evidence を読んだ範囲で方針・要約は正しく、要約に手法名・解き方は入っていない。台帳の `checked` に 2026-10-21 を入れてよい（abc217_d・abc330_e・abc370_d・abc385_d・abc241_d・abc245_e・abc140_e）
- 図 neighbors.svg：Windows の Chrome（headless=new）で、等倍（640×260、2 倍密度）と、幅 390px の暗い背景の画面に幅 358px で画像にして目で見た（v-ordered-set/full.png・narrow.png）。値（3・8・15、x = 10 → 15 と 8、x = 1 → 3 と −INF、x = 20 → INF と 15）は本文・代替テキスト・確認問題と一致。背景は白、`viewBox` あり、文字はテキストのまま `font-family="sans-serif"`、色（赤の x）に加えて破線とラベルで区別。はみ出しはない。幅 358px では下の 2 行の文字がやや小さいが読める。catalog の visual の text（数直線上の要素と lower_bound・その 1 つ前を矢印で）を満たす
- 執筆者の未解決の点
    1. abc217_d で長さのクエリの $x$ が切れ目に一致しうるか：第三者の解説（kanpurin・code.kira924age.com）からは確かめられなかった。本文は保証に触れず「`lower_bound(x)` とその 1 つ前の差」とだけ書き、$0 < x < L$ から番兵の間にあることだけを使っているので、どちらでも本文は誤りにならない。指摘にしない
    2. sections の「落とし穴（…）」：指摘 1
    3. frequency_evidence の abc466_f・abc475_e：front matter は執筆者の担当外で本文にも載せていないので、このページの指摘にしない（メインが判断）

## 指摘

### 1｜直すべき｜手引き（§13.1）｜front matter の sections（31 行）と #pitfalls の見出し（166 行）

- **問題**：「落とし穴」は定型の節で、sections に載せず見出しを `## 落とし穴 {#pitfalls}` にする決まりだが、sections に `anchor: pitfalls` の行があり、見出しがかっこ付きで長い。執筆者は binary-search と同じ扱いにしたと書いているが、binary-search の検証（指摘 1）でも同じ点を直すべきとしている。two-pointers は決まりどおり
- **根拠**：style-guide §13.1（215 行）。planning/batches/b1/verify/binary-search.md の指摘 1
- **直し方**：sections から pitfalls の行を消し、見出しを `## 落とし穴 {#pitfalls}` にする（anchor は同じなのでリンクは壊れない）。かっこの中の項目は節の中の太字の小見出しにすでにある。メインが binary-search と合わせて「骨格にある pitfalls は残す」と決めるなら、そちらに従う

### 2｜直すべき｜fact（F2）・clarity（U4）｜#rows-and-columns の「探す」（108・110 行）

- **問題**：「同じ行で $c$ 列より右にある最初の壁」を「行 $r$ の set で `lower_bound(c)`」と書いているが、$(r, c)$ 自身が壁のとき `lower_bound(c)` は $c$ を返し、「$c$ より右」にならない。その 1 つ前も「左の最初の壁」ではなく、$c$ のすぐ左の壁になる。このまま実装すると、ABC370 D で爆弾のマスの壁を「右の壁」として消し、さらに左の壁まで消してしまう。練習の方針（220 行）では「爆弾のマスに壁があればそれだけを消す」と分けているが、本文の節には前提がない
- **根拠**：`lower_bound` の定義（$c$ 以上の最小）。drken の ABC370 D の記事のコードも `*right == c` を先に調べている
- **直し方**：「$(r, c)$ に壁がないとき、行 $r$ の set で `lower_bound(c)` を取れば右の最初の壁…」と前提を足す。または「$c$ 以上の最初の壁」と言い換え、「$(r, c)$ 自身を含めないなら `upper_bound(c)` を使う」と一言添える

### 3｜直すとよい｜clarity（U3）｜#rows-and-columns の線分の段落と擬似コード（115〜126 行）

- **問題**：節の前半は $r$ を行番号に使い（$(r, c)$・行 $r'$）、後半は線分の右端を $r$、行を $y$、列を $x$ とし、`row[y]`・`col[x]` に切り替わる。同じ節で $r$ が行と右端の 2 つの意味になり、`row[y]` が「行 $y$ にある点の $x$ 座標の set」であることも書かれていない
- **直し方**：線分の端を $l$・$u$ などに変えるか、前半と同じ $(r, c)$ の記号で書く。擬似コードの前に「`row[y]` は $y$ 座標が $y$ の点の $x$ 座標の set、`col[x]` はその逆」と 1 文足す

### 4｜直すとよい｜fact（F2）｜#pareto の支配の定義（130 行）

- **問題**：「$a_q \ge a_p$ かつ $b_q \ge b_p$」の定義では、同じ点どうしが互いに支配し合い、「支配されない点だけを残す」と読むと両方消える。141 行の「同じ $a$ の点が来たときは $b$ の大きい方だけを残す」で実装上は手当てされているが、定義と食い違う
- **直し方**：「$q \ne p$ で」を足し、「同じ点が 2 つあれば 1 つだけ残す」と添える。あるいは「どれか 1 つの点に支配される点は捨てる。同じ点は 1 つだけ残す」とする。用語集への提案の定義も同じように直す

### 5｜直すとよい｜fact（F1）｜#near-kth の計算量（91 行）と要点の「続けて動かすとならし $O(1)$」（43 行）

- **問題**：1 回の質問を $O(\log N + K \log N)$ と書き、続けて「続けて動かすとならし $O(1)$」とあるが、ならしの話を使うなら 1 回の質問は $O(\log N + K)$ になる（$K$ 歩を続けて動かす手間は合計 $O(K + \log N)$）。上界としては誤りではないが、2 つの文がかみ合っていない
- **直し方**：「1 回の質問は $O(\log N + K)$ である（1 歩は最悪 $O(\log N)$ だが、続けて $K$ 歩動かす手間は合計 $O(K + \log N)$）」とする。$K \le 5$ の問題では差はないので、簡単に「$O(K \log N)$ で十分」と書いてもよい

### 6｜直すとよい｜code（C6）｜#pitfalls の「map の `[]` で要素ができる」（178 行）

- **問題**：`contains` は C++20 のメンバ関数だが、版の注記も C++ の章へのリンクもない
- **直し方**：「`find`・`contains`（C++20）を使う」とし、cpp-container-idioms に contains の節があればリンクする

### 7｜直すとよい（メインへの連絡・このページの外）｜clarity（U3）｜docs/cpp/cpp-container-idioms.md 166 行

- **問題**：cpp-container-idioms は「set で $x$ 未満の個数が要るとき」の行き先に「[set・multiset・map の応用](../ds/ordered-set.md)の方法を使う」と書くが、このページは「$x$ 未満の個数」は set では速くならず BIT か pb_ds を使う（184 行）と書いている。リンクの先で答えが見つからない
- **直し方**：cpp-container-idioms 側のリンク先を kth-element（BIT）か pb-ds にする。このページの指摘ではないので、メインがバッチの終わりにまとめて扱う

## 提案への意見

- 台帳への提案：abc241_d の summary（K 番目）、abc245_e の approach（箱を縦の昇順・チョコの横を multiset・D 以下で最大）はどちらも賛成。後者は乱数試験と drken の記事で確かめた
- 用語集への提案（支配・パレート境界）：入れるなら指摘 4 のとおり同じ点の扱いを足す

## 総合の判定

小さな直しで可（直すべき 2 件：指摘 1・2。直すとよい 5 件）
