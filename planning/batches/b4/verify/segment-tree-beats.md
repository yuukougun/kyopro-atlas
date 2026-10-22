# segment-tree-beats の検証（b4）

対象：docs/ds/segment-tree-beats.md、snippets/segment-tree-beats/（beats.cpp・beats.yaml）、docs/img/segment-tree-beats/three-cases.svg。観点は fact.md・code.md・clarity.md・figure.md。

## 確かめたこと

- `python3 tools/check_pages.py --page segment-tree-beats`：エラー 0・警告 0
- `python3 tools/check_snippets.py snippets/segment-tree-beats`：1 本・期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- beats.cpp を `g++-15 -std=gnu++23 -O1 -g -Wall -Wextra -fsanitize=address,undefined` でコンパイル：警告なし。cases の 1 件目でサニタイザの異常なし
- 作業用の場所で総当たりと照らした（リポジトリには置かない）：N = 1〜70・Q = 300・値の幅 ±3／±30／±10^12 の乱択 300 件（chmin・chmax・加算・和を混ぜる）で、サニタイザ付きの実行ファイルの出力が素朴な計算と一致
- 速さ：N = Q = 2×10^5、値 ±10^12 の乱択入力で 0.88 秒（-O2。起動時の self_test を含む）。Library Checker の制限 10 秒に十分収まる
- yaml の cases を手で確かめた：1 件目（chmin 3 → 1 2 3 3 3、和 12。chmax [1,4) 2 は変化なし。加算 [2,5) −4 → 1 2 −1 −1 −1、和 0。空区間 0。chmax 全体 0 → 1 2 0 0 0、[1,4) の和 2）、2 件目（7 → 5 → −5）、3 件目（±10^12 の和 0、chmin −10^12 で −2×10^12）。どれも期待どおり
- コード片の正しさの要点：`apply_chmin` の前提 `mx2 < x < mx1` は、`chmin` のタグの条件と、`push` で親の `mx1`（> 親の `mx2` ≥ 子の `mx2`）を渡す場合の両方で成り立つ。最小値の側の連動（1 種類なら `mn1`、2 種類なら `mn2`）も正しい。番兵 ±INF に加算しない。和の積 `(x - mx1) * cmx` は最大 2×10^12 × 2×10^5 = 4×10^17 で `long long` に収まる
- `npx textlint`：エラー 0・警告 8（文の長さ・半開区間の括弧・数式の中の読点・図の代替テキスト。執筆者の報告どおり。117・122 行の文の長さは指摘 10）
- front matter：変えたのは complexity・stage・updated。要点の計算量と complexity は一致。別名の行に aliases がすべてある。要点の「何ができるか」と summary は同じ文
- Library Checker の制約：github.com/yosupo06/library-checker-problems の data_structure/range_chmin_chmax_add_range_sum の task.md と info.toml で確かめた。$N, Q \le 2 \times 10^5$、`A_ABS_MAX = 1_000_000_000_000`、「クエリ処理の過程で常に $\lvert a_i \rvert \le 10^{12}$」、制限 10 秒。info.toml のテストに `issue_1369_log2.cpp`（4 件）がある（指摘 2）
- 計算量の資料：HackMD（ferin 氏のメモ。Codeforces の原典ブログの和訳）で、chmin と和は $O(n \log n)$、加算が混ざると $O(n \log^2 n)$、「ちゃんと証明してないけどもしかしたら $O(n \log n)$ のままかも」の一文、ポテンシャルが「各頂点の子孫の相異なるタグの数の和」で初期値 $O(N \log N)$ であることを確かめた。本文の complexity の節と一致する（ただし指摘 2）
- 37zigen 氏の scrapbox：題名「Segment Tree Beatsの計算量解析」、ferin 氏の HackMD と yaketake08 氏の記事を元にした解析で、本文の説明（境界のノードと余分なノード）と合う。check_noai.py で noai の指定なし
- rsm9.hatenablog.com の記事：題名「atcoder::lazy_segtree に1行書き足すだけの抽象化 Segment Tree Beats」。`all_apply` の `composition` の後に「`fail` が立っていたら `push(k)` と `update(k)`」を足す方法で、Library Checker の Range Chmin Chmax Add Range Sum の例がある。本文の説明と一致。check_noai.py で noai の指定なし。著者は rsm9 氏で、「ひとなので」はブログの名前（指摘 3）
- abc256_h：`tools/ap.py show abc256_h` で「Ex. I like Query Problem」diff 2531。台帳の summary・approach と本文の行は一致。kmjp の記事（解法とコードの部分）で、クエリが「区間を x で割る（切り捨て）・区間代入・区間和」、x が正の整数、方針が「同じ値の連続を map で持ち、BIT で和」であることを確かめた。値が 0 以上であることは記事に明記がなく、コードからの推測にとどまる（指摘 5）
- 執筆者が自分で組んだ評価（shrinking-values）：
    - 割り算 $O((N + Q \log N) \log A)$：値が 0 以上・$x \ge 2$ なら正しい。1 種類でないノードを余分に訪れると $m_1 \ge 1$ が半分以下になり、$\lfloor \log_2 m_1 \rfloor + 1$ が 1 以上減る（$m_1 = 1$ なら全部 0 になって 1 種類にまとまり 0 になる）。1 種類のノードは割っても 1 種類のままで、1 種類でなくなるのは割り算・区間代入で一部だけ覆われる境界のノードだけ。区間代入で丸ごと覆われたノードは 1 種類になりポテンシャルが 0 になる。初期値 $O(N \log A)$＋1 回 $O(\log N \log A)$ で、主張どおり
    - mod $O(N \log N \log A)$：「各要素が変わるのは $O(\log A)$ 回、降りたノードには変わる要素がある（最大値の要素は $\ge x$ なので必ず変わる）、1 つの変化は祖先 $O(\log N)$ 個に数えられる」の筋は正しい。ただし境界のノードの $O(Q \log N)$ が抜けている（指摘 6）。値が 0 以上の前提も要る（指摘 5）
    - 平方根と加算の反例「3 と 4 は 1 と 2 になり、2 を足すと元に戻る」：$\lfloor \sqrt 3 \rfloor = 1$、$\lfloor \sqrt 4 \rfloor = 2$ で正しい
- 3 つの場合（node-data）とポテンシャルの議論（complexity）：$x \ge m_1$・$m_2 < x < m_1$ の扱いは正しい。$x \le m_2$ の理由の書き方に誤りがある（指摘 1）
- 確認問題 2 の「どの $x < m_1$ でも子へ降りるので … ならしの評価が成り立たない」：全要素が同じ列に $x < m_1$ の chmin をくり返すと毎回葉まで降りて 1 回 $O(N)$ になるので正しい
- 図：`python3 tools/render_svg.py segment-tree-beats` で 360px・720px の PNG を目で確かめた。棒の値 4・9・2・9・6 と線（最大値 9 の実線、真に 2 番目の 6 の破線）は本文と一致。文字の重なり・はみ出しはなく、360px でも読める。白背景・viewBox と同じ比の width・height（400×290）・sans-serif のテキスト・実線と破線の併用（色だけに頼らない）はよい。下の帯の「9 と 6 の両方が変わる」は指摘 1
- catalog の visual は null で、動く図は要らない
- 参考の URL：上のほか、OI Wiki・Library Checker・kmjp・Nyaan は付録 B のドメイン。atcoder.jp・codeforces.com の URL は入っていない。本文の言い回し・例（4・9・2・9・6）は資料と別で、F8 の問題はない

### 執筆者の未解決の点について

- 割り算・mod の評価：上のとおり、筋は正しい。直すのは前提（値が 0 以上）と mod の境界の項だけ（指摘 5・6）
- chmin と chmax を両方持ち加算がない場合：資料（HackMD）にも記述がなく、本文の 2 つの場合だけを書く今の形でよい。加算ありの $O((N + Q) \log^2 N)$ はこの場合も含むので、読者が困ることはない
- 平方根の打ち切りと $O(\log \log A)$：$\lfloor \sqrt{a} \rfloor$ を $k$ 回施すと $a^{1/2^k}$ 程度になるので、$O(\log \log A)$ 回で 1 以下になるのは正しい。一般的な事実として出典なしでよい
- abc256_h の制約：kmjp の記事で x が正の整数であることは確かめられた。「x = 1 なら飛ばす」の書き方でよい。値が 0 以上は推測なので、本文では評価の前提として明記する（指摘 5）
- 台帳の提案（nyaannyaan の裏付けが弱い）：同意する。beats 型の方針は本文の評価で支えられており、台帳の approach の前半「区間がすべて同じ値なら一括で処理し、違えば子へ潜る」も本文と一致するので、evidence の変更は不要

## 指摘

1. **直すべき**｜F2・G5｜#node-data の 3 つの場合の 3.（「$m_1$ と $m_2$ の両方の要素が変わり」）と、図 three-cases.svg の下の帯（「x ≤ 6：子へ降りる／9 と 6 の両方が変わる」）｜$x = m_2$ のとき、値が $m_2$ の要素は変わらない（例：$x = 6$ なら 9 の 2 個が 6 になるだけで、6 はそのまま）。子へ降りる本当の理由は、$m_1$ の要素が $m_2$ の要素とまとまって新しい最大値の個数（$c$ に $m_2$ の個数を足したもの）と新しい真に 2 番目の最大値が、ノードの情報だけでは分からないことである。今の文は境界の場合に誤った理由を述べ、図もそれをくり返している｜4・9・2・9・6 に $x = 6$ を施すと 4・6・2・6・6 で、6 の要素は不変。和は $30 - 6 = 24$ と計算できるが、新しい最大値の個数 3 と真に 2 番目の 4 は $m_1, m_2, c, s$ からは出ない｜本文の 3. を「**$x \le m_2$：子へ降りる**。$m_1$ の要素が $m_2$ 以下に下がり、$x < m_2$ なら $m_2$ の要素も変わる。どちらの場合も、新しい最大値の個数と真に 2 番目の最大値がノードの情報だけでは分からない。」のように直す。図の下の帯の小さい文字を「9 が 6 以下に下がる（x < 6 なら 6 も）」などにし、代替テキストの「（9 と 6 の両方が変わる）」も合わせて直す
2. **直すべき**｜F2・F9｜#complexity の 2 つ目の箇条の最後「元の解説は、実際には $O((N + Q) \log N)$ で済む可能性にも触れている（証明はない）」｜この可能性は否定されている。Library Checker に 2025 年 12 月の issue #1369「Range Chmin Chmax Add Range Sum に Θ(n log² n) のケースを追加」が立ち、PR #1370（2026-02-02 にマージ、コミットは「add (log^2 n)-time query pattern」）で `issue_1369_log2.cpp` のテスト 4 件が加わった。issue は、この計算量の問題が解決したらしいことを動機にしている。今の文のままだと、読者は「実は log 1 つかもしれない」と受け取る｜https://github.com/yosupo06/library-checker-problems/issues/1369 、https://github.com/yosupo06/library-checker-problems/pull/1370 、info.toml の tests の `issue_1369_log2.cpp`（github.com は付録 B）。issue が根拠に挙げる記事は codeforces.com なので開いていない｜その一文を消すか、「元の解説は $O((N + Q) \log N)$ で済む可能性に触れていたが、のちに $\log^2$ の回数かかる入力が作られ、Library Checker のテストにも加わった（2026 年）」に直し、参考に「[yosupo06/library-checker-problems issue #1369](https://github.com/yosupo06/library-checker-problems/issues/1369)：加算が混ざる場合に log^2 かかる入力のテストの追加」を足す。「下界が証明された」とまでは書かない（確かめた資料はテストの追加だけ）
3. **直すべき**｜F9｜#node-data の最後の段落「ひとなので氏の記事」、#resources の「ひとなので氏の…」、#references の「ひとなので「…」」｜「ひとなので」はブログの名前で、著者は rsm9 氏である。手引き §11 の「著者「題名」」に合わない｜記事の HTML の `data-author="rsm9"`、ブログの「このブログについて」の題が「ひとなので」・id:rsm9｜本文は「rsm9 氏の記事」、参考は「[rsm9「atcoder::lazy_segtree に1行書き足すだけの抽象化 Segment Tree Beats」](…)」にする（ブログ名を添えるなら「rsm9（ひとなので）」）
4. **直すとよい**｜F9｜#references の 1 行目「HackMD「Segment Tree Beats」」と #resources の「HackMD のメモ」｜著者がない。37zigen 氏のページはこのメモを「ferin さんの Segment Tree Beats の解説」と呼んでいる｜37zigen 氏の scrapbox の冒頭｜「[ferin「Segment Tree Beats」](…)」にする。#resources も「ferin 氏の HackMD のメモ」にする
5. **直すとよい**｜F2｜#shrinking-values の割り算のポテンシャル（「$\lfloor \log_2 m_1 \rfloor + 1$ をポテンシャルとすると」）と mod の段落（「$a \bmod x < a / 2$」）、#abc256_h の解法の詳細｜どちらの評価も値が 0 以上であることを前提にしている（負の値の切り捨ての割り算は $-1$ で止まり、$m_1$ が負だと $\log_2 m_1$ が定まらない）が、本文に書かれていない｜$-3, -1$ を 2 で割ると（C++ の切り捨てなら $-1, 0$、床なら $-2, -1$）で、「最大値が半分以下」の議論はそのままでは当てはまらない｜割り算の段落の最初に「値は 0 以上とする」を足す。mod の文も「値が 0 以上で、値が変わる要素は…」とする。例題の制約は確かめていない旨を報告に残す必要はない（評価の前提として書けば足りる）
6. **直すとよい**｜F1｜#shrinking-values の mod の最後の文「全体で $O(N \log N \log A)$ 回のノードの訪問に収まる」｜変化の数え上げで抑えられるのは余分なノードだけで、各クエリの境界のノード $O(\log N)$ 個が抜けている。$Q \gg N \log A$ のとき（全部の値が $x$ 未満で、何も変わらないクエリが続く）、訪問は $\Theta(Q \log N)$ になり、書かれた式を超える｜値がすべて 0 の列に mod のクエリを $Q$ 回：各回、境界の $O(\log N)$ 個を訪れて止まる｜「全体で $O((N \log A + Q) \log N)$ 回のノードの訪問に収まる」にする（割り算の式と同じく $Q$ の項を入れる）
7. **直すとよい**｜F3｜#node-data の「和のオーバーフロー」の「Library Checker の制約（$N \le 2 \times 10^5$、$\lvert a_i \rvert \le 10^{12}$）では和の絶対値は $2 \times 10^{17}$ 以下に収まる」｜加算のクエリがあるので、初期値の制約だけでは和の上限は出ない。この結論は「クエリの途中も常に $\lvert a_i \rvert \le 10^{12}$」という制約に頼っている｜task.md の「クエリ処理の過程で常に $\lvert a_i \rvert \le 10^{12}$ が成り立つ」｜「（$N \le 2 \times 10^5$、クエリの途中も常に $\lvert a_i \rvert \le 10^{12}$）」と書く
8. **直すとよい**｜U2・C3｜#node-data の「子へ降りる前の保留の受け渡しは、加算を先に、切り詰めを後にする。」｜なぜこの順なのかがない。読者は順を逆にしてよいかを判断できない｜コード片の `push` は、加算を施した後の子の `mx1` と、加算の後の値である親の `mx1` を比べている。順を逆にすると加算の前の値と比べることになり、切り詰めを取り逃すか誤る｜「親の最大値・最小値は加算をすでに含んだ値なので、子にも先に加算を施してから比べる」を 1 文足す
9. **直すとよい**｜U3｜要点の「タグ」、#node-data の 2.「**$m_2 < x < m_1$：タグ**」｜「タグ」が定義なしに使われている。前提の遅延セグメント木のページは「保留」と言っているので、読者には「タグ」と「保留」が同じものか分からない｜本文の 2. で「子に保留を残して止める」と説明しているが、語の定義はない｜2. の最初に「タグ（ノードの値だけ直し、子には保留を残して止める）」と一言足す。要点の囲みは今のままでよい
10. **直すとよい**｜U9｜#shrinking-values の 3 つ目の段落（122 行。「平方根も同じで、…」）｜平方根の回数、加算が混ざるときの反例と打ち切り、mod の止め方と評価の 3 つの主張が 1 段落に入り、textlint の文の長さの警告（128 字）も出ている｜textlint の警告 122:5824｜「平方根（と加算）」と「mod」で段落を 2 つに分け、長い文を割る

## 総合の判定

小さな直しで可。直すべき 3 件（指摘 1〜3）、直すとよい 7 件。コード片は総当たり・サニタイザ・最大の制約の速さのどれも問題がなく、そのままでよい。直すべき 3 件は文と図の文字の直しで済む。
