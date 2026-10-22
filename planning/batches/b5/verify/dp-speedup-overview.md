# 検証：dp-speedup-overview（DP の高速化の選び方、hub）

- 対象：docs/dp/dp-speedup-overview.md、docs/img/dp-speedup-overview/read-ranges.svg（コード片なし）
- 観点：fact.md・code.md・clarity.md・figure.md
- 確かめたこと
  - `python3 tools/check_pages.py --page dp-speedup-overview`：エラー 0・警告 0
  - 本文の `../<field>/<id>.md#<anchor>` のリンクをすべて相手のページで grep：見つからないものなし
  - 典型90 090：E869120 の解説画像 090-01〜05.jpg（raw.githubusercontent.com、github.com の内容）を読んだ。問い（どの区間でも min × 長さ ≤ K、0 以上の整数、mod 998244353、N ≤ 10^9・K ≤ 10^5）と、方針の流れ（P3 の高さの大きい順の区間 DP → P4 の dp[h][m] への削減と h・(r−l) ≤ K の組だけ、m+2 項間の漸化式 → P5 の h = 0 で高速きたまさ法・Bostan-Mori）が本文の力試しの要約・方針と一致する。執筆者の台帳への提案（summary・approach・evidence に 03〜05 を足す）は根拠どおりで、反映してよい。`checked` に 2026-10-22 を入れる提案を添える
  - 手計算：$n = 100$, $T = 10^{18}$ で $10^6 \times 60 = 6 \times 10^7$、$n = 500$ で $1.25 \times 10^8 \times 60 = 7.5 \times 10^9$、確認問題の $50^3 \times 60 = 7.5 \times 10^6$（$\log_2 10^{18} \approx 59.8$）。すべて正しい
  - $P = \mathrm{dp}[0] / (1 - G)$：$\mathrm{dp}[i] = \sum_{j<i} \mathrm{dp}[j] g[i-j]$（$i \ge 1$）は $g[0] = 0$ とみると $P = \mathrm{dp}[0] + PG$ なので正しい
  - Monge の言い換え「交差する 2 区間の和 ≤ 外側と内側の和」：$a \le b \le c \le d$ で $c(a,c) + c(b,d) \le c(a,d) + c(b,c)$ と一致する
  - 落とし穴の $A = (1, 5, 3)$、$[1, 3)$ の min が 3、累積 min が $1, 1, 1$：正しい
  - (min,+) の行列の結合法則：成り立つ（半環）
  - 要点の計算量・front matter の complexity・本文の計算量の主張：一致している
  - 図：`python3 tools/render_svg.py dp-speedup-overview`（360px・720px）と `--bg '#1e2129' --width 360` で撮って目視。背景は白で塗られ、文字の重なり・はみ出しなし。viewBox 400×330 と width・height の比が一致。③ の A[j] < A[i] = 4 を満たす位置（値 2・1・3）の印は正しい。代替テキストだけで 3 つの型が分かる

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | 事実 F2 | #shape-to-tool の表の「$\min_j (\mathrm{dp}[j] + c(j, i))$ で $c$ が Monge」の行 | この形（段のない DP。$\mathrm{dp}[i]$ が同じ列の $\mathrm{dp}[j]$ から決まる）に道具として「monotone minima・Knuth-Yao」を挙げているが、どちらもこの形にはそのまま使えない。monotone minima は段ごとの形（$\mathrm{dp}_k[i] = \min_j \mathrm{dp}_{k-1}[j] + c(j,i)$）か行列が最初から分かる場合、Knuth-Yao は区間 DP $\mathrm{dp}[l][r]$ の道具である。読者が式どおりに monotone minima を当てると、行の値がまだ決まっていない列を読むことになる | リンク先の monge.md #smawk-larsch（113 行）：「行列が最初から分からない（オンラインに決まる）ので、monotone minima も SMAWK もそのままでは使えない。この形を $O(N)$ で解くのが LARSCH」「左半分を先に確定させる分割統治で $O(N \log^2 N)$」。#knuth-yao は区間 DP の節 | 行を形に合わせて書き分ける。例：右辺の形を「$\min_j (\mathrm{dp}_{k-1}[j] + c(j, i))$ で $c$ が Monge（段ごと・区間分割）」、道具を「monotone minima（段のない形は LARSCH・分割統治、区間 DP は Knuth-Yao）」とし、リンクを [Monge](../dp/monge.md#monotone-minima) にする。段のない形も残すなら別の行にして #smawk-larsch へ。#convexity の表の 2 行目の道具の列も「monotone minima・LARSCH・Knuth-Yao」にそろえるとよい |
| 2 | 直すとよい | 事実 F7・分かりやすさ U3 | #convexity の最後の段落「凸な列の (max,+) 畳み込みが使える」 | 同じ節で用語集の[凸関数](下に凸)にリンクした直後に、(max,+) 畳み込みで「凸な列」と書いている。(max,+) で速くなるのは上に凸な列どうしで、下に凸のまま読むと誤る | glossary.md #convex-function は「下に凸」と定義。monge.md #convex-max-plus-convolution と ABC348 G の方針は「上に凸」 | 「上に凸な列どうしの (max,+) 畳み込み（下に凸なら (min,+)）」と書く |
| 3 | 直すとよい | 図 G5 | read-ranges.svg の ①・② の行 | 行のラベルが「dp[j]」なのに、マスの中は添字 $j$（0〜7・i・9）である。③ は「A[j]」の行のマスに値が入っているので、①・② のマスの数字も dp の値と読める | SVG の 67 行目付近・175 行目付近の `<text>dp[j]</text>` と各マスの数字 | ①・② の行のラベルを「j」にする（または「dp[j] の添字 j」）。③ はそのままでよい |
| 4 | 直すとよい | 分かりやすさ U9 | #shape-to-tool の「表の読み方」の 1 つ目の項目 | 1 文に「窓が単調ならスライド最小値」「セグメント木はどの行の代わりにもなる」「log が付いても間に合うならセグメント木」「使い分けのリンク」が入り、120 字を超える | 手引き §U9 の目安（1 文 120 字まで） | 「セグメント木は和・min・max のどの行の代わりにもなる。」で文を切り、「$\log$ が付いても間に合うなら…」を次の文にする |
| 5 | 直すとよい | 分かりやすさ U1 | #shape-to-tool の導入「上の行ほど易しく」 | 「1 点を書き換えるたびに DP の答えを聞く（動的 DP、ABC246 Ex）」が CHT（EDPC Z）より上にあり、「上ほど易しい」と合わない。動的 DP は発展の内容 | 表の並び。dynamic-dp は「下の 4 行は発展」の外にある | 動的 DP の行を CHT の直前ではなく発展の 4 行と並べて「下の 5 行は発展」とするか、導入を「おおむね上の行ほど易しく」にする |

## 執筆者の未解決の点への見解

- スライド最小値の行の例題が「—」：hub の例題は相手のページに載った問題だけという作り方なので、「—」のままでよい（相手のページに例題がつけば埋める）
- 典型90 090 の第三者の解説が 1 本だけ：公式の解説画像 P1〜P5 で、問い・制約・本文の方針の各段がすべて確かめられた。本文は解き方の詳細を書かず流れだけなので、内容の確かさに問題はない。§15-6 の「2 つ以上」を満たすかはメインの判断
- 手計算の見積もり 3 つ：上のとおり確かめ、正しい

## コード片

なし（code.md の対象外）。

## 総合の判定

小さな直しで可（直すべき 1 件：早見表の Monge の行の道具の取り違え。ほかは直すとよい 4 件）。
