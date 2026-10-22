# cpp-environment の報告（b5）

- 書いたファイル：docs/cpp/cpp-environment.md、snippets/cpp-environment/（24 個。本文に取り込むのは gnu-mode・auto-var-init-cost・fma・judge-macros・acl-version・stack-dfs・stack-limit・gcc14-15・placeholder。ほかは版と失敗例を確かめるためだけのもの：gnu-mode-strict-ng・fma-native・fma-off・assertions-o0・*-13-ng・concat-ng・add-sat-ng・starts-with-ng・mdspan-ng・placeholder-13-ng）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）・cpp_std 23・gcc_min 15・atcoder true。sections の title を 2 つ短くし、中身に合わせた（anchor は変えていない）
  - auto-var-init：「…未初期化の局所変数が 0 になり、大きな局所配列は遅くなる」
  - march-native：「-march=native：pragma の target は要らないが、FMA で小数の結果が変わりうる」
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 24 個すべて期待どおり、textlint エラー 0（警告 11 は数式・コードを含む文の長さと助詞の重なりの誤検出寄り）
- 図：catalog の visual（priority 2、static）は、オプションの比較表・版の対応表・スタックの深さの表（いずれも Markdown の表）で代えた。SVG は作っていない
- 問題：C++ のページなので置いていない（catalog の problems_note どおり）

## 新しく確かめた事実（ほかのページ・早見表にも効くもの）

- **-ftrivial-auto-var-init=zero で AtCoder だけ TLE**：`int buf[100000];` を持つ関数を 2×10^5 回呼ぶと、オプションなし 0.05 秒、付けると 1.03 秒（g++-13・g++-15、-O2）。cpp-io#tle-causes・debugging-checklist・cpp-reverse-index の「AtCoder でだけ TLE」に足す価値がある
- **-march=native で小数の結果が変わる**：GCC は既定で -ffp-contract=fast なので、FMA のある CPU では `ax*by - ay*bx` が FMA になり、平行な (0.1, 0.3) どうしの外積が 0 ではなく 1.66533e-18 になった（(0.7, 0.3) どうしでは -1.33227e-17）。-ffp-contract=off で 0 に戻る。geometry-precision に触れておくとよい（ジャッジの CPU が FMA を持つかは未確認）
- **スタックの深さ（ulimit -s 8192、g++-15）**：最小の再帰ラムダの DFS で -O2 は 2.2×10^5 まで通り 2.4×10^5 で落ちた、-O0 は 6.5×10^4 まで通り 7×10^4 で落ちた、std::function 版（-O2）は 8×10^4 まで通り 9×10^4 で落ちた。unlimited では -O2 で 10^7、-O0 で 10^6 まで通った。research 09 §4.4 の「-O2 で 10^5 は通り 2×10^5 で落ちる」と、tree-traversal の「10^5 でも落ちた」は、どちらも 1 段の大きさの違いで説明がつく（本文は「数倍変わる」と書いた）
- **PCH**：-Wall -Wextra・-ftrivial-auto-var-init=zero・-D の追加では使われ、-march=native の追加・-O2 の除去では使われない（AtCoder と同じ条件のコマンドでは PCH が効かない）。使われたとき 0.47 秒、なし 1.1 秒
- **GCC 15 の -O0**：_GLIBCXX_ASSERTIONS が自動で定義される（-O1・-O2・-Og では定義されない）。GCC 15 の更新の一覧にも「Debug assertions are now enabled by default for unoptimized builds」とある（b1 handoff §6 の件を確認した）
- **-std を付けない g++**：g++-13・g++-15 とも gnu++17（__cplusplus 201703）。g++-13 の -std=gnu++23 は __cplusplus 202100
- **C++26 の構造化束縛を条件に使う書き方**：research の対応表にあるが、`if (auto [a, b] = pair{1, 2})` は -std=gnu++26 でも通らない（pair が bool に変換できないため）。本文の表から外した
- **generator**：g++-15 の -O2 -Wall で -Wmismatched-new-delete の誤警告が出る

## 台帳への提案

なし（C++ のページは問題を置かない）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| スタック（コールスタック） | call-stack | 関数の呼び出しごとに戻り先・引数・局所変数を積む領域。再帰が深いと上限を超えて Segmentation fault になる。Linux の手元の既定の上限は 8 MiB が多い |
| FMA | fma | 掛け算と足し算を 1 回の丸めで行う CPU の命令（fused multiply-add）。GCC は既定で `a * b + c` の形を FMA にしてよいので、`-march=native` の有無で小数の最後の桁が変わる |
| プリコンパイル済みヘッダ | precompiled-header | ヘッダを前もってコンパイルした `.gch` ファイル。作ったときと同じオプションのときだけ使われ、コンパイル時間を縮める |

## 手引きへの提案

- §5 の cpp か geometry に「`-march=native`（AtCoder）では FMA で小数の式の結果が変わりうる。小数の外積の符号・`== 0` に頼らない」を足す（持ち主は cpp-environment#march-native）
- §5 の cpp に「関数の中の大きな配列は、AtCoder では呼ぶたびに 0 で埋められて遅い（cpp-environment#auto-var-init）。作業用の配列はグローバルか使い回し」を足す
- 早見表・cpp-reverse-index の症状の欄に「AtCoder でだけ TLE → 大きな局所配列（-ftrivial-auto-var-init=zero）」「手元でだけ CE → -std の付け忘れ（既定は gnu++17）・g++-13」を足す
- 付録 B に trap.jp を足す（check_noai で noai・noimageai の指定なしを確かめた。2026-10-22）。qiita.com（punirunrun・reika727 の記事）は既存

## 問題の補充の候補

なし。

## 未解決の点

- **AtCoder の新ジャッジのスタックの上限**：確かめられなかった。2023-06 の reika727 の記事の 1 GiB だけを書き、新ジャッジは「この教材では確かめていない」とした。コードテストで stack-limit.cpp を動かせば分かる（ユーザーに確かめてもらうとよい）
- **AtCoder のオプションの一覧**：decisions.md の値を使った。traP の記事（GCC 15.1 時点）には `-fopenmp` も載っているが、decisions.md にはない。-ftrivial-auto-var-init=zero は traP の記事の「主要なコンパイルフラグ」には載っていない（decisions.md を正とした）。公式の一覧は atcoder.jp なので読んでいない
- **ジャッジの CPU が FMA を持つか**：未確認。本文は「持てば、AtCoder でも同じことが起こりうる」とした
- **エディタ（cph）が ulimit を引き継ぐか**：未確認。本文は「引き継ぐことが多い」とし、stack-limit.cpp で確かめる方法を書いた
- **Clang 版の libc++ にない機能**：traP の記事（2025-06、当時の Clang）による。Clang 21.1 で変わっている可能性がある（手元に clang++ がなく確かめていない）
- **Ubuntu の g++ の -fstack-protector-strong**：手元の g++-15 では既定で有効（-Q --help=common と __stack_chk の出力で確認）。AtCoder で同じかは未確認なので本文には書いていない
- 版の対応表の C++17・C++20 の行と GCC 11〜13 の行は research 09 §4.3 と各ページの「版」の確認に拠り、このページでは GCC 14 以降・C++26・GCC 16 の行だけを新たにコンパイルして確かめた

## 使った出典

- https://trap.jp/post/2589/（新たに noai を確認）、https://qiita.com/punirunrun/items/9bbdb33ef03e9a3a5138、https://qiita.com/reika727/items/8fa6f5944b183c0a28f9（research 経由）、gcc.gnu.org（gcc-15/changes.html・Optimize-Options.html）、cppreference の C++23 の対応表と libstdc++ の対応表（research 経由）、ACL の Releases
- 使用量の目安：道具の呼び出し 約 45 回、Web 検索 1 回・Web 取得 3 回（curl 2 回を含めず）

## 検証の指摘への対応（verify/cpp-environment.md）

- 直すべき 1〜3：すべて直した（範囲 for の例を `d.groups()[0]` の形に、`-ffp-contract=fast` は C++ では `-std=c++23` でも既定、`-std=gnu++23` は GCC 11 から）
- 直すとよい 4・5・7・8：直した（確認問題と #stack-depth の断定をぼかす、AVX2 も「ジャッジの CPU が持てば」に、IOI-Style に触れる、`gcd` と `abs` のエラーの理由を分ける）
- 直すとよい 6：参考に「オプションの一覧は AtCoder の公式の言語の一覧による。traP の記事の主要なフラグには `-ftrivial-auto-var-init=zero` がない」の 1 行を足した。公式の一覧で確かめたかどうかは執筆者には確かめられないので、下の提案に回す
- 直すとよい 9：fma-native.yaml に「FMA のある CPU が前提」のコメントを足した（検査からは外していない）
- 直すとよい 10：judge-macros-local.cpp・.yaml（フラグなしで `local`）を足した
- 採らなかったもの：なし

## メインへの提案（検証の指摘 6）

- decisions.md の AtCoder のオプションの一覧（特に `-ftrivial-auto-var-init=zero`・`-fmodules`、traP にある `-fopenmp` の有無）が公式の言語の一覧で確かめたものかを確かめ、必要ならユーザーにコードテストで確かめてもらう。本文の参考の 1 行（「公式の言語の一覧による」）はその前提で書いたので、違えば直す
