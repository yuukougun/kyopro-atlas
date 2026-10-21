# grundy-number の検証（b2）

対象：docs/comb/grundy-number.md、snippets/grundy-number/{subtraction,range-formula,kayles}.{cpp,yaml}、docs/img/grundy-number/range-table.svg
観点：fact.md・code.md・clarity.md・figure.md

## 確かめたこと

- `python3 tools/check_pages.py --page grundy-number`：エラー 0・警告 0（台帳・diff・リンク先の anchor を含む）
- `python3 tools/check_snippets.py -v snippets/grundy-number`：3 本とも期待どおり（kayles 2 case、range-formula 4 case、subtraction 6 case）。コンパイラは g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0
- 3 本を `-std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で手でもコンパイルして動かした。警告・サニタイザの報告なし。`kayles` に n = 3000 を与えても `period 12 from 71`
- front matter の差分は complexity・stage・updated だけ。complexity と要点の計算量は一致
- 1・3・4 個を取る石取りの表（x = 0〜9）、g(5) = mex{2, 0, 1} = 3、g(6) = 2 から 1 個取ると g(5) = 3：手計算で一致。game-basics の図（0〜8 個で 0・2・7 が負け）とも一致
- 「1 個の山 2 つは先手の負け、1 個と 4 個は先手の勝ち」：全局面を調べる小さなプログラムで確かめた（False・True）
- Sprague-Grundy の証明（2 つの和、c < a⊕b の行き先の作り方）と勝つ手の選び方（g(v_i) が s の最上位の 1 を持つ）：議論を追って正しい
- 2〜3 個を取る山の表と式 ⌊(x mod (L+R)) / L⌋：コード片の assert（L ≤ 10・R ≤ 20・x ≤ 500）が通ることを確かめた
- Kayles：値 0 1 2 3 1 4 3 2 1 4 2 6 4 1 と、x ≥ 71 で周期 12（x = 70 では崩れる）。Wikipedia の Kayles の表（72 以降の行がくり返し、60 台の行が 1 か所違う）と矛盾しない。周期を探すコード片は lim = 50・60・80・100 では何も出さず、120 以上で (12, 71) を出す（誤った周期を出さない）ことを試した
- 例題・練習・力試しの方針を evidence で確かめた
  - typical90_ae：E869120 の 031.cpp は状態 (白, 青)、白を 1 減らすと青が白の数だけ増える手と、青を 1〜⌊青/2⌋ 個減らす手。白を外側に小さい順、青の表を広げて持つ。本文の「2 種類の石」の段落と練習の方針に合う
  - abc278_g：kmjp は長さごとの Grundy 数と XOR を 0 に保つ方針で、素直な O(N^3) でも間に合うと書く。本文の方針（Grundy 数だけ）と食い違わない。真似戦略は記事では感想の扱い
  - abc255_g：kmjp は例外の点以外で「それまでの最大値 + 1」、点からの距離で値を求める、2 回以上現れる値だけを数で持つ。本文の方針に合う
- 図：`python3 tools/render_svg.py grundy-number --width 360 --width 720 --scale 2` で PNG にして目で見た。360px では全体が見え、文字の重なり・はみ出しなし。背景は白で塗られている。値・矢印（9 → 7 が 2 個、9 → 6 が 3 個）・注記が本文と一致。720px の PNG で下が切れるのは道具の撮影の高さの問題（執筆者の報告どおり）で、図の問題ではない

## 指摘

1. 直すとよい｜分かりやすさ（U3）｜#sum の最初の段落「どのゲームでも動けなくなった人が負けである」｜「どれか 1 つのゲームで動けなくなったら負け」とも読める。和では「どのゲームでも動けない（すべてのゲームが終局）」ときに負け｜和の定義なので誤読の余地をなくしたい｜「すべてのゲームで動けなくなった人が負けである」に直す
2. 直すとよい｜分かりやすさ（U6）｜#patterns「尾が長いことがある」の段落「上の Kayles の表を計算すると」｜Kayles は #dp の節で定義されており、この節だけを取り出すと何のゲームか分からない（落とし穴の節の「Kayles の周期 12」も同じ）｜断片で読んでも通じるように（U6）｜「Kayles（1 本か隣り合う 2 本のピンを倒すゲーム。[DP の節](#dp)）」のように一言添える
3. 直すとよい｜確認問題（U8）｜#quiz の 1 問目「山が 5, 6, 7 のとき、先手の勝つ手を 1 つ答えよ」｜答えは「勝つ手はない（後手必勝）」なので、問いが勝つ手の存在を前提にしていて不親切｜引っかけとして意図していても、問いの形が答えと食い違う｜「先手が勝てるか。勝てるなら勝つ手を 1 つ答えよ」に直す
4. 直すとよい｜コード（C3・C4）｜snippets/grundy-number/range-formula.cpp の core｜取り込みの範囲は `table(L, R, n)` を呼ぶが、`table` の中身は取り込みの外にあり、本文にも「上の DP で作って」としか書かれていない。読者は `table` が #dp の `grundy_table` と同じもの（moves が L〜R）だと推測するしかない｜本文との対応が切れる｜core の先頭のコメントに「table(L, R, n) は moves = {L, …, R} の grundy_table と同じ」と書くか、本文の図の前の文に一言添える

直すべき指摘はない。

## 台帳への提案（検証役から）

- 確かめた問題の `checked` に日付（2026-10-21）を入れてよい：typical90_ae（031.cpp で状態と遷移を確認）、abc278_g・abc255_g（kmjp で方針を確認）、tessoku_book_ah・abc368_f・abc297_g・abc206_f は方針が本文のコード片と計算で裏付けられる（evidence の記事本文までは今回開いていない）
- 執筆者の提案（abc368_f の evidence からサイトのトップ `https://programming-hiroba.com/` を外す）に賛成

## 執筆者の未解決の点への見解

- 制約を書かなかった件：本文は「山が大きいので」「値の範囲が小さければ」の書き方で、事実の誤りにはならない。そのままでよい
- ABC278 G の真似戦略：evidence（kmjp）も Grundy 数が主で O(N^3) でも間に合うとしているので、本文の方針で問題ない
- abc297_g の式を証明なしにした件：コード片の確認で裏付けられており、本文も「予想して確かめる」節の流れに合う。そのままでよい
- Kayles の周期の始まり：上のとおり手元でも 3000 まで確かめた

## 総合の判定

小さな直しで可（直すべき 0 件・直すとよい 4 件）
