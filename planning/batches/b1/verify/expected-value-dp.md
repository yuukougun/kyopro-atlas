# expected-value-dp（期待値 DP）検証の記録

- 対象：docs/comb/expected-value-dp.md、snippets/expected-value-dp/{hp-mod,self-loop}.{cpp,yaml}、docs/img/expected-value-dp/hp-chain.svg
- 観点：planning/checklists/ の fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page expected-value-dp`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/expected-value-dp`：コード片 2・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- 手で `g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library` でコンパイルし、hp-mod は N = 200000、self-loop は N = 1000 の乱数入力で動かした。警告なし、サニタイザの報告なし
- hp-mod：(N, P) = (1,30)・(5,50)・(7,13)・(10,99) で、Fraction で求めた厳密な値を mod に直したものと一致した
- self-loop：小さな乱数の入力で、Fraction の素朴な O(N^2) の DP とモンテカルロ（10^5 回）の両方と一致した（例：A = [2,2,1] で 3.75、シミュレーション 3.745）
- 本文の数値：HP の例 E = 0・1・1.5・2.25・2.875（図とも一致）、サイコロの E_2 = 4.25、表が 2 回続くまで 6 回（シミュレーション 5.987）、6 が出るまで 6 回・失敗 5 回、寿司の移項した式（[1,3,2,3] で式 16.811、シミュレーション 16.802）、すごろくの移項した式 E[i] = (A_i+1)/A_i + (1/A_i)ΣE[i+k]（kazun の記事の式と一致）
- 移項の正しさの説明（p < 1 なら滞在回数が幾何分布で有限、1 次方程式のただ 1 つの解）、計算順序の表、選択の後に偶然がある形・mod の値で比べない注意：誤りなし
- ACL：modint の割り算の要件 `gcd(b.val(), mod) == 1` と計算量 O(log mod) を ~/lib/ac-library-master/document_ja/modint.md で確かめた（表記の問題は指摘 3）
- 問題と方針：ABC280 E・ABC184 D（drken）、EDPC J（drken の Qiita）、ABC300 E（drken。1 の目の移項で残り 5 つの平均、約数だけのメモ化）、ABC350 E（programming-hiroba）、ABC382 E（ikatakos。R_0 の自己ループを 1 − R_0 で割る）、ABC314 E（DeltaStruct。0 点の目を移項し最小を取る）、ABC144 F（kmjp。出次数 2 以上の頂点で期待値最大の行き先を消し、頂点ごとに再計算して O(NM)、N ≤ 600）、TDPC J（kmjp。座標 0〜15、x に投げると x−1・x・x+1 に等確率、bitDP と移項と最小）を、参考の記事で確かめた。方針・要約は記事と食い違わない
- 例題・練習の並びは difficulty の易しい順。front matter で変わったのは complexity・stage だけ
- 参考の URL は全部付録 B のドメイン。atcoder.jp・codeforces.com の URL はない

## 指摘

### 1（直すべき）F5 事実｜練習「練習の方針」の ABC263 E と問題の要約

- **問題**：ABC263 E の答えは mod 998244353 で出力する問題なのに、方針は「mod で答えるなら」と条件付きで書き、練習の要約（台帳の summary）も「期待値を求める」だけで出力の形が抜けている。読者が double で出力するコードを書くおそれがある（執筆者の未解決の点の 1 つ目）
- **根拠**：gotoki_no_joe「ABC263 A～E をHaskellで」（https://qiita.com/gotoki_no_joe/items/98225d578c885656a959 ）の E は、問題の求める整数 R = PQ^{-1} を modBase = 998244353 で求めている。kazun の記事は出力形式に触れていない
- **直し方**：方針を「答えは mod 998244353 なので、$A_i$ での割り算は逆元の掛け算にする」と言い切る。台帳の abc263_e の summary に「（mod 998244353）」を足す提案をメインに上げる（要約の行は台帳に合わせて直す）。あわせて evidence に上の Qiita の記事を足す提案もする

### 2（直すべき）F9 参考の URL｜参考の drken の 2 件

- **問題**：記事の題名の写しが違う。「AtCoder ABC 280 E - Critical Hit (緑色, 500 点)」は実際は「AtCoder ABC 280 E - Critical Hit (1D, 水色, 500 点)」、「AtCoder ABC 184 D - increment of coins (緑色, 400 点)」は実際は「AtCoder ABC 184 D - increment of coins (1Q, 水色, 400 点)」
- **根拠**：https://drken1215.hatenablog.com/entry/2022/12/07/113800 、https://drken1215.hatenablog.com/entry/2020/11/23/010500 を開いて題名を確かめた（ABC300 E の記事も同じ形式「(1D, 水色, 500 点)」）
- **直し方**：記事の題名どおりに直すか、括弧の部分を省いて「AtCoder ABC 280 E - Critical Hit」のように書く

### 3（直すべき）F7・F4 記法｜要点の「計算量」、front matter の complexity、「ACL では」の囲み

- **問題**：割り算の計算量を $O(\log p)$ と書いているが、このページの $p$ は自己ループの確率・攻撃の確率の記号として使っている（自己ループの節・HP の例・ACL の囲みの直前の文脈でも確率 $P\%$）。確率の log と読めてしまう
- **根拠**：ACL のドキュメント（document_ja/modint.md）は割り算・inv の計算量を $O(\log \mathrm{mod})$ と書く
- **直し方**：3 か所とも「$O(\log \mathrm{mod})$」（front matter はプレーンな文字で `O(log mod)`）にする

### 4（直すとよい）G7・U6 図の前後の文章｜#total-expectation の動く図の div と前の段落

- **問題**：「次の動く図では、…ステップ送りで確かめられる。後半では、自己ループのある状態で…」と書いているが、overrides/assets/js/viz/ に expected-value-dp.js はまだない（あるのは binary-search.js・lazy-segment-tree.js だけ）。JS ができるまでは何も出ない div を指す文になる。また後半（自己ループ）の内容は div の後の段落に文章がなく、図が出ないと何を見せる予定か分からない
- **根拠**：手引き §8 は JS を頼まれていなければ div と仕様の報告でよいとするので、置き場自体は規則どおり。文が指す実体がない点だけの指摘
- **直し方**：JS を作るまで残すなら、div の後の段落に後半の要点（「自己ループのある状態では、移項前の式と移項後の式を並べてから値を埋める（[自己ループの移項](#self-loop)）」）を 1 文足す。メインが JS の作成を後回しにするなら、そのことを progress に残す

### 5（直すとよい）U3 飛躍｜#total-expectation の 2 つ目の式

- **問題**：1 つ目の式は $E[X_s]$（期待値の記号 E と確率変数）、2 つ目からは $E[s]$（DP の表）と書く。同じ文字 $E$ を期待値の演算と表の名前の両方に使っているのに、「$E[s] = E[X_s]$ と書く」という橋がない
- **直し方**：1 つ目の式の後に「以下、$E[X_s]$ を $E[s]$ と書く」と 1 文足す

### 6（直すとよい）U4 実装の粒度｜#prefix-sum

- **問題**：式と累積和の添字が成り立つ前提「$i + A_i \le N - 1$（ゴールを越える目はない）」が本文になく、コード片のコメントにだけある。また「マスは 0-indexed で、ゴールをマス $N - 1$ とする」が式と累積和の説明の後に来るので、$\mathrm{suf}[i + A_i + 1]$ が範囲内かを読む途中で判断できない
- **直し方**：すごろくの設定の文に「マスは 0-indexed でゴールはマス $N - 1$、$i + A_i \le N - 1$ とする」を移す

### 7（直すとよい）U3 分かりにくさ｜#choice の 3 つ目の箇条

- **問題**：「各回の結果の最大値の期待値とは別のものである」が何を指すか読み取りにくい（全部の目を見てから一番よいものを選べる場合の $E[\max]$ のことか）
- **直し方**：「全部の結果を見てから最大のものを選べる場合の期待値（$E[\max]$）とは違い、各状態ではそれまでに見た情報だけで行動を選ぶ」のように具体にする

### 8（直すとよい）G5 図の配置｜hp-chain.svg

- **問題**：ヘッドレスのブラウザ（playwright・chromium）も rsvg・cairosvg もこの環境になく、画像にして目で確かめられなかった。座標から読むと、(a) HP 1 → HP 0 の破線の弧（M455,166 Q510,215 548,168）が x ≈ 536〜540・y ≈ 180 を通り、「終状態」のラベル（中心 x = 560・y = 194、幅およそ 42px）の左上に近い、(b) 下の説明文の基線が y = 246 で viewBox の高さ 250 に近く、下に出る字形が欠けるおそれがある。値・ラベル・白背景・viewBox・font-family・代替テキストは本文と一致し、問題はない
- **直し方**：ブラウザで表示して確かめ、近ければ「終状態」を y = 200 程度に下げるか、viewBox の高さを 260 にして下の文を y = 252 にする

## 台帳への確認の提案

- 次の問題の内容を参考の記事で確かめた。`checked: 2026-10-21` を入れてよい：abc280_e・abc184_d・dp_j・abc300_e・abc350_e・abc382_e・abc314_e・abc144_f・tdpc_ball・abc263_e（指摘 1 の summary の直しとあわせて）
- 執筆者の提案のうち、tdpc_ball の summary（kmjp の記事の問題設定と一致）・abc144_f の approach（kmjp の記事と一致）は裏付けを確かめた
- 執筆者の未解決の点：abc263_e は指摘 1 で解決。abc300_e は drken の記事本文で方針を確かめた（問題なし）。abc266_e の E_2 = 4.25 は計算で確かめた。EDPC J を例題の最後に置いたこと・ACL の囲みの位置は規則に反しない

## 総合の判定

小さな直しで可（直すべき 3 件：指摘 1・2・3。どれも数語〜1 文の直し）
