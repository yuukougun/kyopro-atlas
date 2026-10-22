# b5 検証：debugging-checklist

- 対象：docs/guide/debugging-checklist.md、snippets/debugging-checklist/multitest.{cpp,yaml}、本文の Mermaid の分岐図（SVG はない）
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。Mermaid の図は、ローカルにあった mermaid.min.js と chrome-headless-shell（~/.cache/puppeteer）で PNG にして形を確かめた（日本語のフォントがない環境なので文字は豆腐になったが、構文の解釈・分岐・矢印の向きは確かめられた。幅は約 880px）

## 実行して確かめたこと

- `python3 tools/check_pages.py --page debugging-checklist`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/debugging-checklist`：multitest 2 case 一致
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` で multitest を動かした：警告なし・異常終了なし。case 1 は手計算と一致（[3,1,3,3,2]→3 3、[0]→1 1、[3,3,3,3]→1 4）。3 つ目のケースが 1 つ目と同じ値 3 を使うので、「使った添字だけを戻す」が効いているかを case で確かめられている。case 2 は値 0 と上限 200000 の端を含む。最後の `assert` で全体が 0 に戻ることも確かめている
- `npx textlint`：エラー 0・警告 1（「と」の連続。執筆者の報告と同じで誤検出）
- 本文のリンク 51 本：すべての相手のファイルと anchor がある。stage は atcoder-system だけ stub。cpp-environment・cpp-reverse-index・stress-testing は作業ツリーでは draft になっていて、cpp-environment#stack-depth・#when-results-differ、cpp-reverse-index#symptoms、atcoder-system#ranking の anchor がある
- front matter：git diff で、変えたのは sections の並び（partial を wa の前へ。手引き §14-11 で許される）・stage・updated だけ。summary と要点の「何のページか」は同じ文。aliases はすべて別名の行にある。catalog の sections の注記（提出前・WA・TLE・RE・MLE・手元との違い・最後の手段）の項目はすべて本文にある
- 数値を兄弟のページと照らした（どれも一致）
    - 同期したままの `cin` は $10^6$ 個で 0.21〜0.23 秒、切ると 0.03〜0.04 秒（cpp-io#fast-io）→ 本文「0.2 秒ほど余計」
    - ABC の多くはメモリ制限 1024 MiB、`int` なら約 $2.7 \times 10^8$ 個（complexity-estimation#how-to-estimate）。$1024 \cdot 2^{20} / 4 \approx 2.68 \times 10^8$。`int` の $10^8$ 個は $4 \times 10^8$ バイト ≒ 400 MB
    - AtCoder の GCC の `-ftrivial-auto-var-init=zero`（cpp-environment#auto-var-init、cpp-undefined-behavior#uninitialized）
    - `-fsanitize=address` と `_GLIBCXX_DEBUG` が見つけるもの（cpp-undefined-behavior#detection-tools の表）
    - `pq.top()` を参照で受けて pop すると値が変わる（cpp-undefined-behavior#dangling-pq-top）
    - ACL v1.5 以前は `modint::val()` が `unsigned int`（acl-reading#version）
    - 手元の Linux のスタック 8 MiB、AtCoder は上限が大きい（cpp-environment#stack-depth、tree-traversal#recursion-depth）
    - `set` への `std::lower_bound` は $O(N)$（cpp-container-idioms#member-lower-bound）、固定の法と基数のハッシュが狙われる（hash-safety#atcoder-tests）
- C++ の仕様：`cout` の既定の精度は 6（有効数字 6 桁）、`-7 / 2` は C++11 から 0 の方向への切り捨てで $-3$、`multiset::erase(x)` は値 x をすべて消す、`priority_queue` の既定は最大が先頭、`accumulate` の結果の型は初期値の型。どれも本文のとおり
- 執筆者の未解決 3（深い再帰のメモリ）：深さ $10^6$・1 段 256 バイトの局所配列の再帰を `ulimit -s unlimited` で動かすと、`/usr/bin/time` の最大常駐メモリが 4 MB（深さ 1000）から 264 MB に増えた。スタックの使用量は常駐メモリに入るので、「1 段ごとに局所変数の分のメモリを使う」は正しい。AtCoder の計測が常駐メモリによるかは確かめられないが、本文はそこまで主張していないので今のままでよい
- 執筆者の未解決 1（誤答のペナルティ）：ABC で「最終的に正解した問題の誤答 1 回ごとに 5 分」は広く知られた規則で、本文の書き方（細則は書かない）でよい。atcoder.jp は開いていない。出典のリンク先 atcoder-system は stub だが #ranking の節が予定されているので、書かれたら張り替える（指摘 1）
- 参考の URL
    - KACTL troubleshoot.txt：github.com は付録 B にある。raw を取得し、Pre-submit・Wrong answer・Runtime error・Time limit exceeded・Memory limit exceeded の構成を確かめた。本文の「構成の参考」の記述と合う
    - E869120 の Qiita 記事：`tools/check_noai.py` で noai の指定なし（HTTP 200）。題名が一致。4-1 節「WA の割合からバグを予測」のパターン D（1〜5 割しか正解がない → 根本的な誤り）・E（8〜9 割正解 → 場合分け・コーナーケース、ただし一概には言えない）、パターン B の「配列外参照は WA と表示される場合がある」、6-1 節「誤読していると愚直解も同じ誤りを持ち、ランダムチェッカーで見つからない」を確かめた。本文の表（1〜2 割だけ落ちる／半分以上落ちる）と「割合は目安にすぎない」の注意は、記事の内容と合う
- F8（出典との近さ）：提出前の確認の 5 項目は KACTL の Pre-submit の 5 行と同じ順だが、各項目は日本語で独自に書き足されていて（$N = 1$・$H = 1$ のグリッド・`__int128`・ペナルティの話など）、文の写しではない。KACTL はおもに CC0 を方針とし、参考に構成の出典として挙げている。E869120 の記事とも文の並び・例は違う。問題なし
- 図（Mermaid）：分岐（サンプル → 結果の種類 → WA は割合で 2 つ → すべて「最後の手段」へ）は本文の節の順と一致する。catalog の visual（static・priority 2・Mermaid の分岐図）を満たし、図の後に流れを文章で説明しているので、図が出なくても意味は通る（G7）。priority 2 なので Mermaid でよい（手引き §8 の「欠けると困る図は SVG」には当たらない）

## 指摘

### 1. 直すとよい｜事実（F10・リンク）｜#before-submit、#re、#local-vs-judge、#last-resort、導入

- **問題**：cpp-environment・cpp-reverse-index・stress-testing・atcoder-system へのリンクがページへのリンクになっている。執筆時は stub だったが、今のバッチで前の 3 つは draft になり、張り替え先の anchor がそろった
- **根拠**：執筆者の未解決 2、手引き §14-23。作業ツリーの各ページの sections に stack-depth・when-results-differ・symptoms がある。atcoder-system は stub のまま（#ranking は sections にある）
- **直し方**：メインがバッチの終わりに張り替える。#re と #local-vs-judge の 3. の「AtCoder と手元の C++ 環境」→ `cpp-environment.md#stack-depth`。#local-vs-judge の冒頭に `cpp-environment.md#when-results-differ`（同じ 4 つの順を、手元で試すコマンドつきで説明している）を足すとよい。「C++ の逆引き」→ `cpp-reverse-index.md#symptoms`。stress-testing は節を選ぶなら #procedure。atcoder-system は draft になってから #ranking へ

### 2. 直すとよい｜分かりやすさ（U8）｜#quiz

- **問題**：確認問題 2 つが、どちらも本文の 1 か所を写せば答えられる。1 問目は #partial の表の「1〜2 割だけ落ちる」の行、2 問目は #local-vs-judge の 3. と #re の「深すぎる再帰」の言い換えである。本文の主張を別の場合に当てる問いになっていない。1 問目の題「手元では合うのに AtCoder で WA」も、答えが手元と AtCoder の差に触れないので、題と中身がずれる
- **根拠**：clarity.md U8「答えが本文の 1 文を写せば済むものになっていないか（本文の主張を別の場合に当てる・条件を外すと何が起きるかを問うか）」
- **直し方**：どちらか 1 問を「なぜ」を問う形に替える。例：「愚直解とのストレステストを 1 万回回しても食い違いが出ないのに WA。何を疑うか、なぜか」（答え：誤読。愚直解も同じ誤読で書かれるので一致する）。または「$T \le 2 \times 10^5$、値 $\le 2 \times 10^5$ の多重テストケースで、ケースごとに `fill(cnt, cnt + MAX_V + 1, 0)` すると何が起きるか、なぜか」（答え：$4 \times 10^{10}$ 回で TLE。使った添字だけ戻す）。1 問目を残すなら、題を「30 個のうち 2 個だけ WA」にする

### 3. 直すとよい｜分かりやすさ（U3・U5）｜#mle の「テストケースごとの確保」

- **問題**：MLE の節の項目なのに、本文は「メモリより先に時間の不足で落ちることが多い」と書き、MLE の原因としてどう効くかが書かれていない。ケースの中で作った `vector` はケースの終わりに解放されるので、読者は「なぜ MLE の節にあるのか」で止まる
- **根拠**：clarity.md U3（前の文から出るか）。TLE としての話は #tle の 1 項目目と提出前の囲みで既に書かれている
- **直し方**：MLE になる形に絞って書く（例：グローバルの `vector` にケースをまたいで `push_back` し続け、`clear` し忘れると要素がたまる）か、「この形はふつう MLE ではなく TLE になる（[TLE のとき](#tle)）」と一言で送って項目を短くする

### 4. 直すとよい｜分かりやすさ（U9）｜#before-submit の 1 文目、#wa の 1 文目、#tle の 1 段落目

- **問題**：
    - #before-submit「提出の前に次を確かめると、防げる誤答の多くを提出の前に見つけられる」は「提出の前に」が 2 回出る
    - #wa「WA の原因は、上から順に確かめやすい」は、何が確かめやすいのかが読み取りにくい（「項目は確かめやすい順に並べた」の意味と思われる）
    - #tle「次数が違う原因は、最適化の指定では直らない」の「次数」「最適化の指定」が、この読者（レート 1000 前後）には説明なしで分かりにくい
- **根拠**：clarity.md U9・U3
- **直し方**：「次を確かめると、防げる誤答の多くを出す前に見つけられる」。「WA の原因は、確かめやすいものから順に並べた」。「計算量の次数が違う（$O(N^2)$ を $O(N \log N)$ にすべき）ときは、`#pragma` や `-O3` などの最適化の指定では間に合わない」

### 5. 直すとよい｜事実（F2）｜#local-vs-judge の 1.

- **問題**：「初期化を忘れたコードが AtCoder では AC し、手元では答えが合わない」は、0 で始まれば正しく動くコードに限った話で、言い切りが強い。cpp-environment#when-results-differ は「AtCoder では AC、手元では WA（またはその逆）」と書いている
- **根拠**：fact.md F2（「必ず」「常に」の言い過ぎ）。0 以外の初期値（最小値を探す変数など）が必要なコードなら、AtCoder でも 0 で始まって WA になる
- **直し方**：「AtCoder では 0 から始まって AC することがあり、手元では答えが合わない」のように「ことがある」を足す（cpp-undefined-behavior#uninitialized も同じ言い方なので、メインが両方そろえるかを決める）

### 6. 直すとよい｜図（G3）｜本文の Mermaid の分岐図

- **問題**：最下段に 5 つの箱（端のケース・解法そのもの・TLE・RE・MLE）が横に並び、描いた幅は約 880px になる。Material の Mermaid は幅を画面に合わせて縮めるので、幅 360px では約 0.4 倍になり、文字が 5〜6px ほどになる
- **根拠**：figure.md G3（縮めたときの文字の大きさを幅の比で見積もる）。手元で描いた PNG の幅から見積もった
- **直し方**：横に並ぶ数を減らす。例：WA の割合の分岐（D・D1・D2）を図から外して「WA → 落ちたケースの割合の節」の 1 つの箱にし、TLE・RE・MLE の箱の文字を短くする（「計算量・無限ループ・定数倍」→ 1 行に収まる長さ）。または `flowchart LR` にして、結果の種類ごとの枝を縦に並べる。priority 2 の図なので、直さなくても本文の文章で意味は通る

## 総合の判定

小さな直しで可。直すべき指摘は 0 件、直すとよい指摘は 6 件。事実（数値・C++ の仕様・出典）はすべて一次資料・兄弟のページ・小さなプログラムで確かめられ、誤りは見つからなかった。コード片は警告・サニタイザとも問題なく、case が初期化の戻し忘れを捉える作りになっている。リンクの張り替え（指摘 1）はメインの作業、ほかは文の手直しと確認問題の差し替えで済む。

## 提案（メインへ）

- 用語集への 3 語（コーナーケース・多重テストケース・WA・TLE・RE・MLE）の提案は妥当。「多重テストケース」の定義は本文の囲みの 1 文目と同じなので、足したら本文の初出にリンクを張れる
- 参考の 3 行目（自サイトのページを数値の確かめ先として挙げる行）は、参考を外部資料に限る方針なら消してよい（執筆者の提案と同じ）。本文の各所で同じページへ既にリンクしているので、消しても失うものはない
