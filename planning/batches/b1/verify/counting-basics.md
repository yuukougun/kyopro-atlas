# counting-basics の検証（工程8b・バッチ b1）

- 対象：docs/comb/counting-basics.md、snippets/counting-basics/distance2.{cpp,yaml}・cycle-coloring.{cpp,yaml}、docs/img/counting-basics/line-vs-cycle.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page counting-basics`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/counting-basics`：2 片・期待と違う 0
- 手で `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined -I third_party/ac-library`（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）。警告なし。$K \le 5$・$N \le 6$ の全列挙と 2 片の出力を突き合わせて違い 0。distance2 は $(N, K) = (10^{18}, 10^9)$・$(10^{18}, 10^{18})$・$(3, 10^9+8)$・$(2, 10^9+8)$ も Python の式と一致し、サニタイザの報告なし。yaml の `1000000 1000000 → 201471773` も Python で一致
- 式と数値（一時置き場の b.py）：一列で隣が異なる $K(K-1)^{N-1}$、距離 2 以内が異なる $K(K-1)(K-2)^{N-2}$（$N \ge 2$）、円環 $(K-1)^N + (-1)^N(K-1)$（$N \ge 2$）を $K \le 5$・$N \le 7$ の全列挙で確かめた。$C_3 = 6$・$C_4 = 18$（$K = 3$）、暗証番号 7290、3 桁の偶数 328、4 桁の 5 の倍数 952、$20! = 2432902008176640000 < 2^{63} - 1 < 21!$、円順列 $(n-1)!$ と数珠順列（$n = 3..6$ で $(n-1)!/2$、$n \le 2$ で 1）、赤 2・青 2 の円形の並べ方 2 通り、$n = 3$・$k = 2$ の全射 6 通り。すべて本文と一致
- `python3 tools/ap.py show`：typical90_bq「069. Colorful Blocks 2（★3）」diff なし、abc307_e「E. Distinct Adjacent」diff 1240、abc178_c「C. Ubiquity」diff 653。本文の label・diff・要約は台帳と一致
- typical90_bq の問いと制約：E869120 のリポジトリの問題の画像（https://raw.githubusercontent.com/E869120/kyopro_educational_90/main/problem/069.jpg）で $1 \le N \le 10^{18}$、$1 \le K \le 10^9$、$10^9 + 7$ で割った余り、$\lvert i - j \rvert \le 2$ なら異なる色、を確かめた。sol/069.cpp も読み、本文の場合分け（$N = 1$・$N = 2$・$K = 1$）と一致
- abc307_e：drken の記事（題名「AtCoder ABC 307 E - Distinct Adjacent (1Q, 水色, 475 点)」）で、問い（サイクルを隣が異なるよう塗る・998244353）、解法 (1) の 1 人目と同じかの DP、解法 (2) の「頂点 1 と頂点 N をひとかたまりにして N−1 頂点のサイクルに帰着」を確かめた。本文の導き方は同じ考えだが文章は独自で、近すぎない（F8）
- 図：chrome-headless-shell 146（puppeteer のもの）で SVG を 640×320（等倍）と幅 358px（2 倍密度・暗い背景の上）で画像にした（/tmp/claude-1000/-home-yuuki-projects-kyopro2-kyopro-atlas/ff4dc6ee-16d4-486c-b97a-49fefbe7b218/scratchpad/v-counting-basics/full.png・narrow.png）。この環境には日本語のフォントがなく和文は豆腐になったので、和文の見え方は確かめていない（字数から幅を見積もると、右端の「→ 積にならない」が約 635px で 640 の内側に収まる）。背景は白で塗られ、円環の 5 番目は色に加えて破線の枠と太字で区別しており、色だけに頼っていない。図の値（K, K−1×4、5 番目が K−1 か K−2）は本文と一致

## 執筆者の未解決の点

- typical90_bq の $K$ の上限：問題の画像で $K \le 10^9$ と確かめた。法 $10^9 + 7$ より小さいので、「$K$ が法より大きいことがある」という書き方は当たらない。指摘 1 を参照
- 赤 2・青 2 の円形の並べ方：プログラムで回転の同値類を数えて 2 通り。正しい
- 関連ページの状態：dp-state-design と mod-pow は draft になった。dp-state-design には `{title: 環状の列（1 か所で切り、最初の状態を固定して DP を回す）, anchor: dp-cyclic}` がある。指摘 4 を参照。twelvefold-way・burnside-lemma・inclusion-exclusion はまだ stub
- リンクの文字は各ページの title と一致していた（繰り返し二乗法・DP の状態の設計・余事象 など）

## 指摘

### 1｜直すべき｜事実（F5）・コード（C3）｜distance2.cpp の core のコメント、例題の「解法の詳細」の 2 つ目

- **問題**：コード片のコメント「k は 10^9+7 より大きいことがあるので、mint にしてから掛ける」は、例題の制約（$K \le 10^9 < 10^9 + 7$）では起きないことを事実のように書いている。本文の「$K$ が法より大きくてもよいように、$K$ を余りにしてから掛ける」も、mint にする本当の理由（$K(K-1)$ は $10^{18}$ 近くになり、さらに累乗を掛けるとあふれる）を言っていない
- **根拠**：E869120 の問題の画像 problem/069.jpg の制約 $1 \le K \le 10^9$。sol/069.cpp も `int K` で読み、`(long long)(K) * (K - 1) % mod` で掛けた直後に余りを取っている
- **直し方**：コメントを「k(k-1) は 10^18 近くになり、続けて掛けるとあふれるので、mint にしてから掛ける（mint(k-2) は k=1 で -1 だが、k-1=0 が掛かる）」にする。本文は「$K \le 10^9$ なので $K(K-1)$ は `long long` に収まるが、累乗を続けて掛けるとあふれる。mint にしてから掛ければ、$K$ が法以上の場合も含めて安全である」とする。台帳の summary（mod-pow の alternatives）に $K \le 10^9$ を足すかはメインの判断

### 2｜直すべき｜事実（F9）｜#references の 3 件目（Zenn）

- **問題**：「shinonome81「ABC307 E」（Zenn の解いた記録）」は題名と著者の書き方が実際と違う。記事は ABC301〜350 の D・E をまとめた個人のメモで、ABC307 E はその 1 項目である
- **根拠**：https://zenn.dev/shinonome81/articles/3e1c0c8a9c00fc の og:title は「AtCoder Beginer Contest 301~350 D or E までの要点・解答（Go）」（Beginer は原文のまま）、表示名は「tmsn」。ABC307 E の項に「円環になっていなければ M*(M-1)^{N-1}」と「最初の人と同じ数字かどうか」の DP があり、参考にした点の説明は合っている
- **直し方**：`- [tmsn「AtCoder Beginer Contest 301~350 D or E までの要点・解答（Go）」](https://zenn.dev/shinonome81/articles/3e1c0c8a9c00fc)：ABC307 E の項。一列の数 $M(M-1)^{N-1}$ と円環の違い、1 人目と同じかを状態にした DP`

### 3｜直すとよい｜事実（F7）・メインへの申し送り｜#sum-and-product の「排反」のリンク

- **問題**：`../guide/glossary.md#disjoint` の anchor が用語集にまだない。mkdocs.yml は `validation: anchors: warn` で `--strict` なので、用語集に足さないままビルドすると落ちる
- **根拠**：`grep -n "disjoint\|排反" docs/guide/glossary.md` が 0 件
- **直し方**：執筆者の提案（排反｜disjoint）をメインがバッチの終わりに用語集へ反映する。反映しないならリンクを外す

### 4｜直すとよい｜事実（F7）・メインへの申し送り｜#coloring の最後の段落の「DP の状態の設計」へのリンク

- **問題**：執筆時は stub だったので anchor なしでリンクしたが、dp-state-design は draft になり、円環の DP の節 `#dp-cyclic` がある
- **直し方**：「円環を 1 か所で切り、最初の要素の色を固定して DP を回す考え方は」の後のリンクを `../dp/dp-state-design.md#dp-cyclic` にする。#order-of-choice の手順の 3 つ目のリンクは一般の話なので anchor なしのままでよい

### 5｜直すとよい｜分かりやすさ（U3）｜#coloring の「これを解くと $C_N = (K-1)^N + (-1)^N (K-1)$ になる」

- **問題**：漸化式から閉じた式への橋がなく、折りたたみの証明も「式が漸化式を満たす」確認だけなので、読者はどうやって式を見つけるのかが分からない
- **根拠**：$D_N = C_N - (K-1)^N$ とおくと、漸化式から $D_N = K(K-1)^{N-1} - (K-1)^N - C_{N-1} = (K-1)^{N-1} - C_{N-1} = -D_{N-1}$、$D_2 = K(K-1) - (K-1)^2 = K - 1$。よって $D_N = (-1)^N (K-1)$
- **直し方**：「$C_N$ と $(K-1)^N$ の差を $D_N$ とおくと、漸化式から $D_N = -D_{N-1}$、$D_2 = K - 1$ なので」と 1 文足してから閉じた式を書く

### 6｜直すとよい｜事実（F1）・分かりやすさ（U9）｜#permutations の最後の段落

- **問題**：「${}_n P_k$ と $n^k$ は、$k$ 回掛ける素朴なループで求まる」は、$k$ が大きい $n^k$（$k \le 10^{18}$ など）にもそう読める。ページの要点・落とし穴では累乗に繰り返し二乗法を使うと言っており、ここだけ食い違って見える
- **直し方**：「$k$ が小さければ $k$ 回掛ける素朴なループで求まる。$n^k$ で $k$ が大きいなら[繰り返し二乗法](../math/mod-pow.md)で $O(\log k)$」とする（mod-pow へのリンクはページの 2 回目以降になるので、リンクを付けない書き方でもよい）

### 7｜直すとよい｜問題（F5）｜#practice

- **問題**：練習が abc307_e の 1 問だけで、手引き §10 の目安（練習 2〜6）に届かない
- **根拠**：`tools/ap.py show abc178_c` で実在と diff 653 を確かめた。落とし穴「和の法則で重なりを足す」と同じ型である
- **直し方**：執筆者の提案どおり abc178_c を practice として台帳に足すか、メインが補充の調査に回す（ページの直しはメインの反映後）

### 8｜直すとよい｜図（G3）｜line-vs-cycle.svg

- **問題**：viewBox の幅 640 に 14px の文字なので、スマホの幅（358px）では文字が約 8px になる。要の「K−1 か K−2」と下の説明文（13px→約 7px）が小さい
- **根拠**：narrow.png（幅 358px・2 倍密度）。右側（x = 530 より右）は短い注記だけで余白が多い
- **直し方**：位置の下の選択肢の数と「K−1 か K−2」を 16〜18px にし、円の間隔を少し詰める。必須ではない（同じ幅の図はほかのページにもある）

## 台帳への提案

- typical90_bq｜checked: 2026-10-21｜E869120 の problem/069.jpg（制約 $N \le 10^{18}$・$K \le 10^9$）と sol/069.cpp で確かめた
- abc307_e｜checked: 2026-10-21｜drken の記事で問い・998244353・両方の解き方を確かめた

## 総合の判定

小さな直しで可。直すべき 2 件（指摘 1・2）、直すとよい 6 件（うち 3・4 はメインへの申し送り）。式・数値・コード片はすべて全列挙と一致し、本文の主張に誤りは見つからなかった。
