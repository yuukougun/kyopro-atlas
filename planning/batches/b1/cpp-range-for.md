# cpp-range-for の報告と提案（工程8b・b1）

- 書いたファイル：docs/cpp/cpp-range-for.md、snippets/cpp-range-for/{references,references-const-ng,pass-by-reference,move-swap,forwarding-reference,range-for-forms,vector-bool,vector-bool-ng,range-for-init,range-for-init-17,modify-in-loop,temporary-range,temporary-range-ub}.{cpp,yaml}、docs/img/cpp-range-for/copy-ref-move.svg
- front matter で変えたもの：complexity・stage（draft）・cpp_std（17）・gcc_min（13）。updated は 2026-10-21 のまま。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（13 件・25 回のコンパイルがすべて期待どおり）、textlint（エラー 0・警告 0）
- 取り込まないコード片：references-const-ng（const 参照からの書き換えがエラー）、range-for-init-17（gnu++17 で警告）、temporary-range-ub（g++-15 の C++23 でだけ動くことを確かめる）、vector-bool-ng（本文はエラーの文面だけ）
- 手元で確かめた事実（scratchpad で実行。snippets にないもの）
  - 値渡しの再帰（長さ・深さ 10^4、g++-15 -O2）：172 ms・最大 395 MB。const& は 0 ms・3.7 MB
  - swap と代入（長さ 10^7 の vector<long long> を 100 回）：swap は 0 µs、代入は g++-13 で 592 ms・g++-15 で 572 ms
  - move で構築した後の元の vector の size は g++-13・g++-15 とも 0
  - 範囲 for の中の push_back（{2, 3, 4, 8}）：ASan で heap-use-after-free（両方）。ASan なしの -O2 では g++-13 が 6、g++-15 が 7
  - for (int v : d.groups()[0])（ACL dsu）：g++-13 gnu++23・g++-15 gnu++20・g++-15 gnu++23 -fno-range-for-ext-temps は ASan で heap-use-after-free、ASan なしの -O2 では segfault。g++-15 gnu++23 は正しく動いた。どれも -Wall -Wextra で警告なし
- 使った出典：cppreference（range-for・reference・vector_bool）、cpprefjp（範囲for文・C++20 の初期化式・C++23 の P2718・右辺値参照・vector::swap）、GCC 15 の changes。どれも付録 B のドメインで、URL は curl で 200 を確かめた（cpprefjp の P2718 のページは題名も確かめた）。新しく noai を確かめたドメインはない
- 図：catalog の visual（static・priority 2）のうち、コピー・参照・ムーブの図を SVG にした。4 通りの受け方は 2 軸の表（Markdown の表）にした。SVG は描画の道具がなく、XML として読めることと座標だけを確かめた

## 台帳への提案

なし（catalog の problems_note のとおり、C++ のページは ABC の問題を置かない）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 一時オブジェクト | temporary-object | 関数の戻り値や式の途中の結果のように、名前を持たず、普通はその文の終わりで消える値。参照で受けると寿命が延びることがある |
| プロキシ | proxy | 本物の要素の参照の代わりに返される、要素を指す小さな物。`vector<bool>` の `vb[i]` が返す `vector<bool>::reference` が代表 |

本文では両方とも最初の出現からリンクした。research/09 §6.5 の「無効化」「寿命の延長」も、cpp-undefined-behavior などで使うなら足すとよい。

## 手引きへの提案

- §4 の cpp の目安（一言 → 素朴に書くと → 版 → 落とし穴 → 確認問題 → 関連）を、views-basics と同じく節ごとの箇条書き（素朴に書くと・版・落とし穴・関連）で書いた。cpp の節の型としてこの箇条書きの見出し語をそろえると、検証しやすい
- `cpp_std` の値は 17・20・23 しかない。このページの中心（参照・範囲 for・ムーブ）は C++11 なので、いちばん小さい 17 を入れた（C++20 の初期化式と C++23 の寿命の延長は節の「版」に書いた）。「ページの中心の機能が使える最も古い値」を入れる、と手引きか interfaces に書いてほしい

## 問題の補充の候補

なし（C++ のページは問題を置かない方針のため探していない）。

## 未解決の点

- `swap` が定数時間であることは C++98 から、`vector<bool>` の特殊化も C++98 からというのは記憶と cppreference の記述に基づく（版の注記として書いた）
- move の後の vector が空になることは、本文では「手元では空になった」とし、規格の保証には触れていない（移動構築なら空が保証されるが、移動代入は保証されない）
- related に cpp-dangling は無い（catalog で merged か別名か未確認）。一時オブジェクトの寿命の話は cpp-undefined-behavior へリンクした
- 「範囲 for の 4 通り」の表は手引き §8 の「列は 4〜5 まで」に収まる 4 列にした
