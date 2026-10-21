# zeta-mobius-subset の検証（b3）

対象：docs/comb/zeta-mobius-subset.md、snippets/zeta-mobius-subset/{transforms,or-plus-max}.{cpp,yaml}、docs/img/zeta-mobius-subset/cube-axes.svg
観点：fact.md・code.md・clarity.md・figure.md

## 確かめたこと

- `python3 tools/check_pages.py --page zeta-mobius-subset`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/zeta-mobius-subset`：コード片 2・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 手で `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、cases の一部を動かした：警告なし、サニタイザの報告なし、期待どおりの出力。どちらのコード片も main で愚直な O(4^n) と assert で比べている（C2 を満たす）
- textlint：エラー 0・警告 11（文の長さ・読点の数・助詞の重なり。執筆者の報告と同じ）
- 図：`python3 tools/render_svg.py` で 360px・720px の PNG にして目で見た。4 枚の値（1 → bit0 の後 → bit1 の後 → bit2 の後）を手で計算し直し、すべて一致（最後は 2^|S|）。ラベル・矢印の重なりなし。背景は白で塗られ、viewBox あり、font-family="sans-serif"。代替テキストの値も図と一致
- 例・数値を手で確かめた：loop-order の n = 2 の例（f(0) が 2 回入る）、確認問題 1（(3,4,4,5) → (3,4,7,9)）、確認問題 4（S 外側で (10,10)、正しくは (10,0)）、確認問題 3（順序対から A_i = 0 の個数を引いて 2 で割る）、OR がちょうど K の組＝(cnt と cnt の OR 畳み込み − cnt)/2、1 段の変換の表（OR・AND・XOR とその逆）、3^20 ≈ 3.5×10^9、20·2^20 ≈ 2×10^7、18·2^18 ≈ 4.7×10^6、pitfalls の 2 ⊆ 3・2 ⊄ 4
- 出典：drken（arc100_c）は「OR ≤ K を部分集合に言い換え・上位 2 つのゼータ・累積 max・L = 0 を除く・O(N 2^N)・N ≤ 18」で本文と一致。drken（abc213_g）は「e(S) をゼータ変換で（O(M 2^N) の直接計算も可）・f(S) を O(3^N) の DP・答えは f(S)·2^{e(V∖S)}」で力試しの方針と一致。kmjp（abc295_h）は 1 マスずつの O(HW 2^W) の DP で、ゼータ変換・上位集合の和は使っていない（執筆者の報告どおり）。merom686（abc349_f）はゼータ → 2 の冪 → 逆変換で、本文の inverse の応用の型と一致。convexineq は題名・著者とも一致し、部分集合のメビウスをゼータと同じループ順で書いている（本文の「同じ順でよい」と合う）
- ap.py：arc100_c（2111）・abc213_g（2663）・abc295_h（2728）の題名と diff は囲みと一致
- リンク先の anchor（bit-dp#subsets-as-integers・subset-enumeration-dp#submask-loop・#vs-zeta・prefix-sum-2d#higher-dimensions・zeta-mobius-divisor#inverse・#vs-subset・inclusion-exclusion#general・#bit-enumeration）はすべてあり、リンク先の内容も本文の言い分と合う（zeta-mobius-divisor#inverse は段の中の向きが効くことを表にしている）

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | clarity U9 / fact F10 | 要点の囲み 37 行目 | `- **いつ使うか**：。` と「：」の後に「。」が残っている。ほかのページ（zeta-mobius-divisor・inclusion-exclusion など）は `**いつ使うか**：` で終わる | `grep -l "いつ使うか\*\*：。" -r docs` でこのページだけが当たる | 「。」を消して `- **いつ使うか**：` にする |
| 2 | 直すとよい | fact F5 / clarity U7 | 力試しの abc295_h（251・257 行目） | 方針が「変換を使わずに済む」で、このページの手法を使わない問題を力試しに置いている。台帳の approach「上位集合のゼータ変換で速くする」も evidence（kmjp）で確かめられない | kmjp の解説は 1 マスずつの O(HW 2^W) の DP で、ゼータ変換も上位集合の和も使っていない（記事を読んで確かめた） | メインの判断。執筆者の提案どおり broken-profile-dp（または bit-dp）の力試しへ移し、このページから外すのがよい。残すなら台帳の approach を kmjp の方針に直す |
| 3 | 直すとよい | clarity U3 | inverse の 125 行目 | 「『$S$ の部分集合だけを使う数』$\hat f(T)$」で、言葉は $S$、記号は $T$ になっていて対応がずれる | 式 $f(S) = \sum_{T \subseteq S} (-1)^{\lvert S \rvert - \lvert T \rvert} \hat f(T)$ の $\hat f(T)$ は「$T$ の部分集合だけを使う数」 | 「各 $T$ について『$T$ の要素だけを使う数』$\hat f(T)$ が求めやすいとき、『$S$ の要素をすべて使う数』$f(S)$ を…」にする |
| 4 | 直すとよい | fact F2 | inverse の応用の型（129 行目） | lcm がちょうど $M$ の帰着で、「$M$ の約数でない要素を先に除く」ことが書かれていない。除かないと、指数が $M$ を超える素数を持つ要素が混ざって誤る | merom686 の解説も、執筆者の報告の要約も「M の約数でない要素を除く」を前提にしている | 「$M$ の約数でない要素を除いてから、各要素を…に潰す」とする |
| 5 | 直すとよい | fact F2 / clarity U3 | vs-xor の最後の段落（206 行目） | 部分集合の畳み込みの手順が「$\lvert A \rvert + \lvert B \rvert = \lvert U \rvert$ の組だけを掛け合わせる」で止まり、変換後の各点で要素数ごとに積を足し、逆変換して要素数 $k$ の位置だけを取る、という形が分からない。また、右辺に dp 自身が出る形は要素数の小さい層から順に求める必要があるのに、ただの畳み込みと同じ道具のように書いている | subset-enumeration-dp#vs-zeta は「右辺の dp を要素数の小さい順に層ごとに求める部分集合の畳み込み」と書いている | 「要素数 $a$ の列ごとに変換し、各点で $\sum_{a+b=k} \hat f_a \hat g_b$ を作って逆変換し、要素数 $k$ の $U$ だけを取る」と一言足す。dp の形は「要素数の小さい層から順に求めれば」を添える（詳細は subset-enumeration-dp#vs-zeta に任せてよい） |
| 6 | 直すとよい | code C4 / clarity U5 | top-two（187 行目）と例題の解法の詳細（243 行目） | 同じ `or-plus-max.cpp:core` を 2 か所で取り込んでいる。top-two の節の取り込みには、まだ説明していない「K について累積の max」まで入っている | 本文 187 行目と 243 行目、コード片の core の範囲 | コード片に `top2`（merge_top2 と変換のループ）と `answer`（累積の max）の印を分け、top-two の節は `top2` だけ、例題では全体（または `answer`）を取り込む |
| 7 | 直すとよい | figure G3 | cube-axes.svg | 360px 幅では頂点の 2 進ラベル（font-size 13）が 6〜7px ほどに縮み、読みにくい。値（21）とパネルの題（17）は読める | render_svg.py の 360px の PNG を目で見た | 2 進ラベルを 15〜16 に上げるか、2×2 のままパネルの余白を詰めて縮み方を減らす。必須ではない |
| 8 | 直すとよい | fact F7 | 本文の各所の `\hat{\mathrm{cnt}}` | `\hat` は 1 文字幅なので、`\mathrm{cnt}` の上で小さく中央に載る | KaTeX の \hat の仕様 | `\widehat{\mathrm{cnt}}` にするか、変換後を $\mathrm{cnt}'$ のような別の記号で書く |
| 9 | 直すとよい | fact F7 | pitfalls の最後（222 行目） | 「値の上限が $2^{20}$ なら」は、値が $2^{20}$ ちょうどを取ると bit が 21 本要る | 2^20 は 21 bit 目 | 「値が $2^{20}$ 未満なら」とする |

## 執筆者の未解決の点について

- abc295_h：指摘 2 のとおり、このページの力試しには合わない。kmjp の解説で確かめた範囲ではゼータ変換を使わない。移す先と台帳の approach の直しはメインが決める
- 練習の囲みがないこと：手引き上、練習は必須の節ではない。abc349_f を台帳に足すなら、merom686 の解説で「M の約数に絞る → bit に潰す → ゼータ → 2 の冪 → 逆変換」を確かめられたので、practice に置ける（台帳の `checked` に今日の日付を入れる提案を添える：arc100_c・abc213_g は drken、abc295_h は kmjp で内容を確かめた）
- counting-labeled-graphs は stub ではなく draft だった（執筆者は stub として扱った）。今はページへのリンクで問題ないが、メインが節へ張り替えるときの候補になる
- 部分集合の畳み込みの持ち主：指摘 5 の直しで足りる。持ち主のページを作るかはメインの判断

## 総合の判定

小さな直しで可（直すべき 1 件・直すとよい 8 件）。事実・計算量・コード片・図の値に誤りは見つからなかった。
