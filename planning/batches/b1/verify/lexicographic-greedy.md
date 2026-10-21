# lexicographic-greedy の検証（工程8b・バッチ b1）

- 対象：docs/basics/lexicographic-greedy.md、snippets/lexicographic-greedy/smallest-subsequence.{cpp,yaml}・kth-ab-string.{cpp,yaml}、docs/img/lexicographic-greedy/smallest-subsequence.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 検証日：2026-10-21

## 実行した検査と環境

- `python3 tools/check_pages.py --page lexicographic-greedy`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/lexicographic-greedy`：2 片（8 case・5 case）すべて一致
- 手で `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined`（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）。警告なし。サニタイザの報告なし
- Python の全探索と突き合わせた（一時置き場の bf.py・t.py）：
    - smallest-subsequence：ランダム 300 ケース（n ≤ 9、文字 a・b・c・z）で違い 0
    - kth-ab-string：ランダム 200 ケース（A, B ≤ 5）で違い 0。A = B = 30、K = C(60, 30)（最後）で bbb…aaa を出す
    - 「番号の小さい頂点をできるだけ前に置く」＝逆向きのグラフで入次数 0 を大きい順に取り出し末尾から並べる：ランダム 3000 グラフ（N ≤ 6、閉路あり・なしを含む）で全探索と一致。辞書順最小と答えが違うグラフは 357 個あり、本文の「別の問題である」も正しい
    - 確認問題（3 は 1 より前）：辞書順最小 (2, 3, 1)、1 をできるだけ前 (3, 1, 2)。本文どおり
    - 落とし穴の S = ab?、T = b：置ける位置は 1 と 2、候補は aba・abb、最小は aba で、最も後ろに置いた abb ではない。本文どおり（台帳の approach の誤りの指摘も正しい）
    - ABC009 C の判定式（残りの長さ − Σ min(s_c, t_c) が K − 接頭辞の不一致 以下）：ランダム 1500 ケース（n ≤ 6、文字 a〜c、K = 0〜n）で全探索と一致
    - 接頭辞で閉じた集合（部分文字列すべて）で K 番目の長さ ≤ K：ランダム 500 文字列のすべての K で成り立つ
    - $\binom{120}{60} = 9.66 \times 10^{34}$（「約 $10^{35}$」は正しい）
- 図・本文の例（S = bacbab、K = 3）を計算し直した：1 文字目の範囲 0〜3 で a（位置 1）、2 文字目の範囲 2〜4 で a（位置 4）、3 文字目は位置 5 だけで a は nxt[5][a] = 6 で不可、b に確定、答え aab。図・代替テキスト・本文・yaml の 1 つ目の case と一致
- 図：Windows 側の Chrome（headless=new）で、等倍（760px）と表示幅 358px の 2 通りで画像にした（scratchpad/v-lexicographic-greedy/shot.png）。和文のフォントは出ており、文字のはみ出しはない（最長の「答え：…」の行は右端に余白がある）。背景は白で塗られている。選んだ位置は赤の太枠、範囲外は灰色の破線で、色だけに頼っていない
- `python3 tools/ap.py show`：abc076_c 846・abc202_d 966・abc223_d 1069・arc097_a 1108・typical90_f なし・abc009_3 1915（参考値）。本文の題名・diff と一致。台帳の summary と本文の要約も一致
- 出典：drken の ABC076 C（T の位置を全部試し、残りの ? を a。最小を取り、なければ UNRESTORABLE）・典型90 006（残りの文字数で範囲を決め、同じ文字は前を取る。nex の表）・ABC223 D（最小ヒープの Kahn 法、取り出せた数が N 未満なら −1、O(M + N log N)）・ARC097 C（K 番目の長さは K を超えない）・ABC009 C（Σ min(s_c, t_c) による不一致の最小）、ikatakos の ABC202 D（先頭を a にした個数と K の比較）を読んだ。いずれも参考の行の説明どおり。本文の例（bacbab、ab?）は記事の例（bbbbazzzz など）と重ならない
- related の関連ページ：string-basics・topological-sort・binomial-coefficient・dp-reconstruction・greedy-basics は draft（見出しあり）、subsequence-matching・exchange-argument は stub

## 執筆者の未解決の点

- 「番号の小さい頂点をできるだけ前に置く」の方法：上の全探索で正しいことを確かめた。書き方については指摘 2
- 関連ページへのリンク：stub と思われていた 4 ページのうち subsequence-matching 以外は draft になっており、節がある。指摘 3
- 図の見た目：文字のはみ出しはない。スマホ幅での読みやすさは指摘 4・5

## 指摘

### 1｜直すべき｜事実（F3）・分かりやすさ（U3）｜#pitfalls の 1 つ目（153 行）と、それを指す 64 行

- **問題**：見出しは「判定せずに最小の文字を取って行き止まる」だが、例の S = bacbab・K = 3 では、判定せずに「残りの中の最小の文字を、最も前の出現で取る」としても a（1）→ a（4）→ b（5）で正しく aab になり、行き止まらない。本文は「全体で最小の a のうち後ろの位置 4 を取ると」と、わざわざ後ろの出現を選んだ場合で失敗させており、これは同じ段落の最後の文が言う「最も前の出現を取る規則」の話である。見出しの主張（判定がないと行き止まる）を例が示していない。64 行の「判定を省いて最小の文字を置くと、後で条件を満たせなくなって行き止まる（落とし穴）」もこの例を指している
- **根拠**：手で追った（判定なし・最も前の出現：s[0..] の最小 a は位置 1、s[2..] = cbab の最小 a は位置 4、s[5..] = b）。上の全探索の smallest-subsequence と同じ結果
- **直し方**：最も小さい文字が範囲より後ろにしかない例に替える。たとえば同じ S = bacbab で K = 5 にすると、判定なしでは a（1）→ a（4）→ b（5）で 3 文字しか取れず行き止まり、判定ありでは 2 文字目の範囲が位置 2 だけなので c になり答えは acbab。あるいは S = bca・K = 2（判定なしだと a（2）で終わる。答えは ba）。「後ろの出現を取ると失敗する」話は、最後の文に別の例（S = abab・K = 2 で位置 2 の a を取ると ab、正しくは aa）を添えて分けるとよい

### 2｜直すとよい｜分かりやすさ（U2）・事実（F2）｜#topological の 3 段落目（102 行）

- **問題**：「辺を逆向きにしたグラフで、入次数 0 の頂点を大きい順に取り出して末尾から並べる方法が知られている」は、内容は正しい（全探索で確認）が、理由も出典もなく「知られている」で済ませている（clarity.md U2 の失敗例）。topological-sort の 105 行はこの節へリンクしており、読者は理由を求めてここに来る
- **根拠**：上の全探索（3000 グラフで一致）。clarity.md U2
- **直し方**：理由の直感を 1〜2 文足す。たとえば「末尾から決めると、最後に置けるのは後ろに何も要求されない頂点（逆向きで入次数 0）で、そこへ一番大きい番号を回せば小さい番号ほど前に残る。前から小さい順に取ると、1 を前に出すために必要な頂点より先に 2 などを置いてしまい、1 が遅れる（確認問題の例）」。「知られている」は消すか、「小さい場合の全探索と比べて確かめられる」に替える

### 3｜直すとよい｜事実（F7）｜本文のほかのページへのリンク（49・98・119・125・137・147・155・165・166 行）

- **問題**：関連ページが stub だと考えてページへのリンクにしているが、今は draft で該当の節がある。手引き §6（136 行）は draft 以降のページの節へリンクしてよいとしている
- **根拠**：`docs/string/string-basics.md` に `{#lexicographic-order}`・`{#concat-order}`、`docs/graph/topological-sort.md` に `{#lexicographic}`、`docs/comb/binomial-coefficient.md` に `{#kth}`、`docs/dp/dp-reconstruction.md` に `{#lexicographic-min}`・`{#dp-kth-lexicographic}`、`docs/basics/greedy-basics.md` に `{#counterexamples}` がある。subsequence-matching・exchange-argument はまだ stub
- **直し方**：49 行の辞書順 → `string-basics.md#lexicographic-order`、98 行 → `topological-sort.md#lexicographic`、119 行 → `binomial-coefficient.md#kth`、125 行 → `dp-reconstruction.md#dp-kth-lexicographic`、137・147・166 行 → `dp-reconstruction.md#lexicographic-min`（後ろからの DP と前からの貪欲の節）、155 行の反例の探し方 → `greedy-basics.md#counterexamples`。165 行の連結の辞書順最小は、exchange-argument が stub なので `string-basics.md#concat-order` へのリンクを足すとよい

### 4｜直すとよい｜図（G3）｜smallest-subsequence.svg 全体

- **問題**：viewBox が 760×424 の横長で、表示幅 358px（幅 390px の端末）では 0.47 倍になり、12px の位置の番号・「選択済」は約 5〜6px、本文の 14px は約 6.6px で読みにくい。各段の間に約 70px の空白があり、高さも余っている
- **根拠**：headless の Chrome で表示幅 358px にした画像（scratchpad/v-lexicographic-greedy/shot.png の下半分）
- **直し方**：右側の「a を試す：…」の注記を各段の文字の箱の下へ移して幅を 400〜450 程度に詰めるか、段の間隔を詰めて全体の文字を大きくする。最下行の凡例は 2 行に分ける

### 5｜直すとよい｜図（G5）｜smallest-subsequence.svg の 2 行目の説明「残りの文字数が足りる範囲（青い枠）」

- **問題**：範囲外の箱も枠線は同じ青（`stroke="#1f4e9a"`、破線）で、範囲内との違いは塗り（青と灰色）と実線・破線である。「青い枠」だと全部の箱が当てはまる
- **根拠**：SVG のソース（範囲外も `stroke="#1f4e9a"`）と描画した画像
- **直し方**：「青く塗った実線の箱」とするか、範囲外の枠線を灰色にする

### 6｜直すとよい｜事実（F3）・コード（C3）｜#kth の 125 行と kth-ab-string.cpp の LIMIT のコメント

- **問題**：(a) 例の $\binom{120}{60}$ はページのどこにも出てこない数で、コード片の範囲（A, B ≤ 100、最大 $\binom{200}{100} \approx 9.05 \times 10^{58}$）とも合わない。(b) 頭打ちが正しいのは LIMIT が K の最大値以上のときだけだが、コメントの「K を超える値は意味がない」はその前提（K ≤ 10^18 < LIMIT、かつ 2 × LIMIT が long long に収まる）を書いていない
- **根拠**：$\binom{200}{100} = 9.05 \times 10^{58}$（計算）。LIMIT = 2×10^18、和の最大 4×10^18 < 9.22×10^18
- **直し方**：(a) コードの範囲に合わせて「a・b が 100 個ずつなら $\binom{199}{99}$ は約 $4.5 \times 10^{58}$」などにする。(b) コメントを「K ≤ 10^18 なので、それより大きい LIMIT で頭打ちにしても比較は変わらない。2 × LIMIT は long long に収まる」とする

## 台帳・catalog への提案（執筆者の提案の確認）

- abc076_c の approach を「T を置ける位置をすべて試し、残りの ? を a にした候補の最小を取る」に直す提案に賛成する。反例 ab? / b を手で確かめ、evidence（drken）も全位置を試す方針である
- checked：abc076_c・abc202_d・abc223_d・arc097_a・typical90_f・abc009_3 に 2026-10-21 を入れてよい（各 evidence で問いと方針を確かめた。typical90_f と arc097_a は drken、abc202_d は ikatakos）
- abc223_d の lexicographic-greedy 用の summary を主の summary（「A_i は B_i より前」…なければ −1）にそろえる提案は任意でよい

## 総合の判定

小さな直しで可。直すべき 1 件（落とし穴の例が見出しの主張を示していない）、直すとよい 5 件。事実の主張（不変条件による正当性、トポロジカルソートの 2 つの「小さい順」、K 番目の手順と長さ ≤ K、ABC009 C の判定式、ABC076 C の反例）とコード片 2 つは全探索で確かめて誤りがなかった。
