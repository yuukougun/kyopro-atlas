# b5 検証：stress-testing（ストレステストと実験）

- 検証したもの：docs/guide/stress-testing.md、snippets/stress-testing/{compare-random,exhaustive,generators,experiment}.{cpp,yaml}、執筆者の報告 planning/batches/b5/stress-testing.md
- 観点：fact.md・code.md・clarity.md・figure.md
- 実行したもの（2026-10-22）
  - `python3 tools/check_pages.py --page stress-testing`：エラー 0・警告 0
  - `python3 tools/check_snippets.py -v snippets/stress-testing`：4 片・各 3 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
  - 4 片を `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でも手でコンパイル・実行：警告なし、サニタイザの報告なし。`1000 7 -5 5` → trial 5（6 回目）で `(-5)`・solve 0・naive -5、`100000 1 1 20` → 食い違いなし、`4 2` → `(-2)` で停止、experiment `20` → `2 3 5 … 17711` と `LWLWWWWLWLWWWWLWLWWWW`（assert すべて通過）、generators `1000 3` → ok
  - online-judge-tools の generate_input.py と getting-started.ja.md を raw.githubusercontent.com から取得して照合
  - betrue12 氏の記事・kmyk 氏の記事を取得して照合（どちらも付録 B のドメイン／執筆者が noai なしを確認済み）
  - OEIS（fmt=text）：A047352 = "Numbers that are congruent to {0, 2} mod 7."（0,2,7,9,14,16,…）、`2,3,5,8,13,21,34,55,89,144` の検索の先頭は A000045
  - GCC Bugzilla PR 85494（MinGW の random_device）を照合
  - 本文のリンク先の節（construction#checker・cpp-types-literals#float-compare・cpp-undefined-behavior#debug-build・#assert・grundy-number#patterns・counting-mindset#verify-small・proof-patterns#necessary-sufficient・interactive#local-testing・debugging-checklist#before-submit・#last-resort・cpp-math-functions#random、用語集の 7 語）がすべて存在することを grep で確認
- 図：Mermaid 1 つだけで、SVG はない（render_svg.py の対象なし）。catalog の visual は static・priority 2・「生成器 → 愚直解・本解 → 比較 のループの図（Mermaid）」で、そのとおり。図の後に同じ内容の文章があり、Mermaid が出なくても通じる（G6・G7 問題なし）。Mermaid の構文（`C -- "一致" --> G`）は正しい
- 確かめて正しかった主な点
  - 区間の和の例：`best = 0` の誤りは値がすべて負のときだけ表に出る。値 1〜20 では 10^5 回で見つからない（実行で確認）
  - 全数テスト：長さ順・辞書順の列挙は正しく、`5^8 = 390625 ≈ 3.9 × 10^5`
  - random_tree：どの頂点も前の頂点を親に持つので木になる。どのラベル付き木も（BFS 順の並べ方で）作れるが一様ではない、の主張は正しい
  - 1・3・4 を取るゲームの負けは $i \bmod 7 \in \{0, 2\}$（表と assert で確認）。円の領域の数 1, 2, 4, 8, 16, 31 も正しい（Moser の円の問題、A000127）
  - oj：`--hack` と `--hack-actual` は同じ引数、`--hack-expected` は `--command` の別名、`-j`、`-e 1e-6`、`--judge-command`、`oj t/r` はすべてドキュメント・ソースのとおり。ヘルプの例 `oj g/i --hack-actual ./a.out --hack-expected ./naive 'python3 generate.py'` も本文と一致
  - betrue12 氏の記事：数列 4〜10 要素・値 20 以下の目安、互いに異なる値を set で、木を Union-Find で（直線やウニは出にくい）、自己ループ・多重辺の確かめを忘れがち、Yes になる入力を先に作る例と片側の誤りしか探せないこと、MinGW の注意、裏で回す使い方、事前の練習。どれも記事にある
  - `uniform_int_distribution` の値が標準ライブラリで変わりうる注意は正しく、cpp-math-functions#random の記述ともそろう

## 指摘

### 1（直すとよい）事実｜F2・F9｜#caveats の最後の段落（MinGW の random_device）

- **問題**：「Windows の MinGW では `random_device` が実行ごとに同じ値を返すことがある」と現在形で書くが、これは古い libstdc++ の不具合で、mingw-w64 では GCC 9.2 で直っている（執筆者の未解決の点）。いまの g++-13 以降の MinGW を使う読者には当てはまらない
- **根拠**：GCC Bugzilla PR 85494（https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85494 ）。"In mingw environment, std::random_device uses mt19937 with fixed seed." → rand_s を使うよう修正、"This is now fixed for mingw-w64."、"it should be fixed for mingw-w64 in the gcc-9-branch, so for the GCC 9.2 release."（Target Milestone 10.0、9.2 に戻し入れ）。mingw.org 版は RDSEED・RDRAND のない古い CPU でだけ残る
- **直し方**：「GCC 9.2 より前の MinGW では、`random_device` が実行ごとに同じ値を返す（betrue12 氏の記事、2019 年）。生成器を回しても同じ入力しか出ないときは、時刻を種にする」のように版を限る。参考に gcc.gnu.org（付録 B にある）の PR 85494 を足すとよい

### 2（直すとよい）事実｜F2｜#setups「online-judge-tools に任せる」

- **問題**：「`--hack-expected` を省くと、本解が RE か TLE になる入力を探す」。TLE と判定するのは制限時間 `-t`（`--tle`）を渡したときだけで、既定は無限（`default: inf`）。`-t` なしで本解が無限ループすると止まらないまま待つ
- **根拠**：generate_input.py の `subparser.add_argument('-t', '--tle', type=float, help='set the time limit (in second) (default: inf)')`、`check_status` の TLE 判定は `timeout=tle` による
- **直し方**：「`--hack-expected` を省くと、本解が RE になる入力（`-t 2` のように制限時間を渡せば TLE になる入力も）を探す」とする

### 3（直すとよい）事実・出典｜F9・F8｜#caveats 155 行「kmyk 氏の例」

- **問題**：「値の上限ちょうど、0、2 の冪、すべて同じ値のような特定の入力でだけ誤るなら…（kmyk 氏の例）」とあるが、kmyk 氏の記事の例は $0 \le n \le 10^{18}$ で $n = 0$ や $n = 2^k$ がコーナーケースの場合だけで、「上限ちょうど」「すべて同じ値」は記事にない。列挙全体が同氏の例に見える
- **根拠**：kmyk 氏の記事の「ランダムテスト」の節（"たとえば、入力の制約が $0 \le n \le 10^{18}$ でかつ $n = 0$ や $n = 2^k$ がコーナーケースだった場合"）
- **直し方**：「0 や 2 の冪（kmyk 氏の例）、値の上限ちょうど、すべて同じ値のような…」と、出典の付く範囲を 0・2 の冪だけにする

### 4（直すとよい）出典｜F9｜参考の betrue12 氏の行

- **問題**：「手順の 4 段階」とあるが、記事の手順は「手順1：愚直解法コード作成」「手順2：乱数データ生成コード作成」「手順3：ひたすら回すスクリプト作成」の 3 段階で、反例を手で追うことは手順 3 の後の 1 文（「手計算したりコードの途中経過を細かく追ってみましょう」）である
- **直し方**：「手順（愚直解・生成器・繰り返して比べる・反例を手で追う）」のように中身で書くか、「手順の 3 段階と、見つかった反例の追い方」とする

### 5（直すとよい）出典の近さ｜F8｜#procedure の最後の段落・#setups「3 つのプログラム」・#generators の最後の段落

- **問題**：出典を明示しているので転載ではないが、言い回しが記事に近い箇所が重なる
  - 「準備に時間がかかりすぎると本末転倒」「裏で回しておき、見つかれば儲けもの」← 記事「この準備作業に手間取ってしまうと本末転倒」「コードや考察を見直している裏で回しておいて、もし見つかったら儲けもの」
  - 「入力を毎回ファイルに書いておけば、止まったときに反例が確実に残る」「`g++ -o` で別の名前の実行ファイルに」← 記事「スクリプトが止まった時に確実に入力データが保存されている」「g++であれば -o オプションで実行ファイル名を変えられます」
  - 「列 $A$ を列 $B$ にできるか」の例は記事と同じ例（氏の例と明記済み）
- **直し方**：同じ例を使うのは明記があるのでよいが、「本末転倒」「儲けもの」の語は自分の言い方に替える（例：「準備が長引けばその分だけ考察の時間が減る。見直しの間に裏で回し、当たれば助かる程度に考える」）。ファイルの段落も「止まった時点の input.txt がそのまま反例になる」など言い換える

### 6（直すとよい）分かりやすさ｜U8・F2｜#quiz の 2 問目の答え

- **問題**：問いは $N = 1, \dots, 6$ で $1, 2, 4, 8, 16, 32$ が出た場面だが、答えの例（円の領域の数）は 6 項目が 31 で、表の 6 項目 32 とすでに食い違う。「6 項だけでは決められない」の例として、6 項とも一致する別の数列を示せていない。読者は「6 項目で 32 が出ているのだから円の数列ではないと分かっている」と考えて、例が論拠にならない
- **直し方**：問いを $N = 1, \dots, 5$ で $1, 2, 4, 8, 16$ にする（円の例が 5 項すべて一致し、6 項目で 31 に分かれるので、例がそのまま効く）。6 項のまま残すなら、例を「5 項一致して 6 項目で分かれる数列がある。同じことが 7 項目で起きてもおかしくない」と、例と主張の関係を書き足す

### 7（直すとよい）分かりやすさ｜U6｜#generators の 2 つ目の項目

- **問題**：「上の区間の和の例では、値を 1 以上 20 以下で作ると…」は #setups の例を指す。節だけを取り出して読むと「上の区間の和の例」が何か分からない
- **直し方**：「[1 つのプログラムにまとめる](#setups)例（空でない区間の和の最大で、最大値を 0 で始める誤り）では」と、指す先と誤りの中身を 1 句で添える

### 8（直すとよい）リンク｜F7｜#experiment の最後の文

- **問題**：「[詰まったときの発想リスト](../guide/thinking-checklist.md)」はページへのリンクだが、thinking-checklist は作業ツリーで stage: draft になり、`## 小さいケースを試す {#q-small-cases}` がある（related も `thinking-checklist#q-small-cases`）。執筆者の未解決の点のとおり、節へ張り替えられる
- **直し方**：`../guide/thinking-checklist.md#q-small-cases` にする（メインのバッチの終わりのリンクの張り替えでまとめてもよい）

### 9（直すとよい）報告の提案｜—｜用語集への提案「コーナーケース」

- **問題**：報告は「本ページでも使っている」とするが、本文に「コーナーケース」の語はない（本文は「端のケース」と書く。grep で 0 件）
- **直し方**：提案の理由を debugging-checklist#wa だけにするか、本文の「端のケース」を「コーナーケース（見落としやすい端の入力）」にそろえる。どちらにするかはメインが決める

## 問題なしとした点（観点ごと）

- **fact**：計算量の主張は全数テストの $(2v+1)^n$ 通りだけで正しい。OEIS の番号と名前、ゲームの周期、フィボナッチの漸化式、乱数の再現性の注意、oj の各オプション（指摘 2 を除く）を確認。参考の URL 5 件は存在し内容も合う（指摘 3・4 を除く）。front matter で変えたのは stage・updated だけ（catalog と比べて確認）。要点の「何のページか」は summary と同じ
- **code**：4 片ともコンパイル警告・サニタイザの報告なし。cases は境界（試行 0 回・長さ 0 の全数・$v = 0$・$n = 1, 2$）を含み、期待値は手計算・別の実行と一致。取り込みは funcs・core・distinct・tree・count・game で、`#include`・`main` を見せていない。`endl`・マクロ・型の別名なし。is_tree の再帰ラムダは取り込みの外。本文の半開区間 $[l, r)$ とコードの `r = l + 1 … n` がそろう
- **clarity**：手順 → 書き方の形 → 生成器 → 注意 → 実験 → インタラクティブの順で、各節の冒頭に節の主題がある。確認問題 1 は本文の「符号と 0 を制約どおりに」を別の場面に当てる問いで、理由まで答えている
- **figure**：上の「図」の項のとおり

## 総合の判定

**小さな直しで可**（直すべき 0 件・直すとよい 9 件）。コード片と事実の大筋は正しい。直すとよいの中では、1（MinGW の版の限定）・2（`-t` なしでは TLE を探さない）・6（確認問題の例が論拠になっていない）を優先して直すとよい。
