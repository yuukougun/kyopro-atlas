# string-automaton-dp の検証（b2）

- 対象：docs/string/string-automaton-dp.md、snippets/string-automaton-dp/{aho-dp,matrix}.{cpp,yaml}、docs/img/string-automaton-dp/kmp-abab.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目視
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page string-automaton-dp`：エラー 0・警告 0。`python3 tools/fix_problems.py --check --page string-automaton-dp`：直すべき行 0。`npx textlint`：エラー 0・警告 9（数式を含む文・確認問題の答えの文の長さ、助詞の重なり。執筆者の報告どおり）
- `python3 tools/check_snippets.py -v snippets/string-automaton-dp`：aho-dp 5 case・matrix 6 case すべて一致。中の自己検査（aho-dp は素朴な全列挙と 300 回、matrix は 1 文字ずつの DP と 200 回）も通る
- サニタイザ（`-fsanitize=address,undefined`）：aho-dp を σ = 26・K = 8・各 10 文字・L = 50（S = 81、mask 256 通り）、matrix を σ = 26・K = 10・各 10 文字・N = 10^18（S = 101）で動かし、異常なし（matrix は 0.6 秒）
- 数値（Python の全列挙）：P = abab の dp（長さ 3 で 2・3・2・1、和 8。長さ 4 で 4・6・3・2、和 15。長さ 5 の和 28）、nxt[3][a] = 1・nxt[2][b] = 0、aa・N = 3 の素朴な式 4 と正しい数 3、aba・N = 5 の位置 {0, 2} が 1 個・{0, 1} が 0 個、2^8·81·26 = 539136 ≈ 5.4×10^5、101^3·30 ≈ 3.1×10^7、2^8·81 = 20736。図の例 dp[4][1] = 2 + 3 + 1 も正しい
- 照合の状態のマルコフ性の証明、out の受け継ぎ（BFS 順で fail[v] が先に確定）、あるパターンが別のパターンを含む場合、同じパターンが 2 回の場合（add が OR）、パターンの集合についての包除の式、位置の包除の値（差 d < M が周期でなければ 0、そうでなければ σ^{N − 覆われた文字数}。重なる 2 つの組が矛盾しなければ全体も矛盾しない）：正しい
- 確認問題 5 問の答え：正しい（KMP の表の作り方は kmp#automaton の規則 nxt[j][c] = nxt[π[j − 1]][c] と一致。bc・abcd の Trie で fail[abc] = bc。ab・b で誤った書き方だと答え 0、正しくは 1）
- 計算量：要点・front matter の complexity・本文（O(NσM)・O(NσS)・O(NσS·2^K)・O(S^3 log N)、前計算 O(σS)）が一致し、根拠（状態数 × 遷移数、積 1 回 O(S^3) × log N 回）も本文にある
- 問題：4 問とも `tools/ap.py show` で題名・diff が台帳と一致。abc458_f は gdst.dev（check_noai で指定なし）で N ≤ 10^9・K ≤ 10・各 10 文字以下・総和 100 以下・英小文字・998244353・Aho-Corasick の禁止状態を除いた行列の累乗を確かめ、本文の方針・解法の詳細と食い違いなし。abc419_f は kcpc の記事（check_noai で指定なし）で「含んだ集合の bit とパターンの接頭辞を状態にし、その数は 80 程度」を確かめた。abc122_d（drken）・abc305_g（merom686）は台帳の evidence と方針が合う
- 参考の 4 件：題名・内容は書かれたとおり。出典の文章・例との近さ（F8）は見当たらない（本文の例 abab・bc/abcd・aa・aba はどれも記事にない）
- 図：白背景・viewBox あり・font-family="sans-serif"・相対パス。辺の向きと遷移（0 →a 1、0 →b 0、1 →a 1、1 →b 2、2 →a 3、2 →b 0、3 →a 1、3 →b 4）は正しく、捨てる辺を破線と色の両方で区別している。代替テキストと前後の文章だけで要点が分かる。catalog の visual は static・priority 2 で、動く図は不要

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | clarity（手引き §14-2）・fact F10 | front matter の sections の matching-state（26 行）と見出し（55 行） | sections の title は「照合の状態とマルコフ性（次の状態は次の文字だけで決まる。直近の数文字で足りる簡易版は dp-state-design）」で、見出しは「照合の状態とマルコフ性」。ほかの 5 節は一致しているが、この節だけ食い違う（check_pages はこの一致を見ていない） | 手引き §14-2「sections に載せた節は、見出しの文字と front matter の title を同じにする（見出しを短くしたら title も直す）」 | front matter の title を「照合の状態とマルコフ性」に直す（執筆者が直してよい範囲） |
| 2 | 直すとよい | clarity U5・fact F2 | #pitfalls の最後から 2 つ目（211 行）「パターンが空や文字の範囲外」 | 見出しに「空」とあるが、本文は文字の範囲外のことだけで、空のパターンが何を起こすかを書いていない。空のパターンを add すると根の out が立ち、count_avoid は L = 0 でも 1 を返す（空の文字列も空のパターンを含むので正しくは 0） | aho-dp.cpp の add と count_avoid（dp[0] = 1 から始め、根の out を見ない） | 「空のパターンは、どの文字列にも含まれるので『含まない』数は 0 になる。根に印が立つので、入力で空が来るなら先に場合分けする」と 1 文足すか、見出しから「空や」を外す |
| 3 | 直すとよい | clarity U3・fact F1 | #matrix-power の最後の段落（176 行）「次の節の包除でパターンの部分集合ごとに S × S の行列を累乗する方法がある」 | 「すべて含む」で N が巨大なときの代わりの方法として示すが、その計算量 O(2^K S^3 log N) が書かれていない。K = 8・S = 81・N = 10^9 で約 256 × 5.3×10^5 × 30 ≈ 4×10^9（部分集合ごとの Trie は小さくなるが、それでも 10^8〜10^9 の桁）で、「方法がある」だけだと間に合うと読める。また「次の節」が位置に頼っている（U6） | 256·81^3·30 ≈ 4.1×10^9 | 「計算量は O(2^K S^3 log N) で、S と K が小さいときに限る」と添え、「次の節」を [パターンの集合についての包除](#why-not-inclusion-exclusion) へのリンクにする |
| 4 | 直すとよい | clarity（手引き §2.3・§14-2） | #why-not-inclusion-exclusion の見出し（183 行） | 執筆者の未解決の点のとおり、題は「破綻する理由」だが、節の後半は「パターンの集合についての包除は正しく使える」で、#matrix-power からもこの後半を指している。題だけ見るとページ内で包除は使えないと読める | 199 行・176 行 | 執筆者の案のとおり title と見出しを「包除はどこで破綻するか（位置の重なりとパターンの集合）」のように変える（anchor は変えない） |
| 5 | 直すとよい | fact F7・clarity U3 | #multiple-patterns（113〜123 行）とコード片の build | aho-corasick が draft になり、同じ構築を aho-corasick#build・#inherit-terminal が説明している。記号がページ間で違う（本ページは fail[v]・out[v]・「頂点」、aho-corasick は link(v)・term[v]/mask[v]・「節点」）。前提ではないページなので本ページで構築を示すのはよいが、両方を読む読者には同じものか分かりにくい | aho-corasick.md 79〜143 行 | 執筆者の申し送りのとおり、115 行の Aho-Corasick 法へのリンクを aho-corasick.md#build に、117〜123 行の受け継ぎに aho-corasick.md#inherit-terminal へのリンクを足す。記号は「失敗リンク fail[v]（Aho-Corasick 法のページの link(v)）」と一言断るか、どちらかにそろえる（メインが決める） |
| 6 | 直すとよい | figure G3・G5 | kmp-abab.svg | 状態の円の中の小さなラベル（""・a・ab・aba・abab）と最下行の例の文が、720px でも小さく、360px ではほぼ読めない（6px 程度）。下の dp の表に列の見出し（j = 0〜3）がなく、列が上の状態の円の真下にあることで対応を読ませている。「和 8」が状態 4 の真下にあり、状態 4 の値と読み違えうる | render_svg.py の 360px・720px の PNG を目視 | 円の中のラベルを 13〜14px 程度にし、表の上に「j = 0 1 2 3」の見出し行を足す。和の列は区切り線か少し離して置く |
| 7 | 直すとよい | clarity U3 | #matrix-power の式（165 行） | A[u][v] = #{ c \| … } の「#」（集合の要素の数）が説明なしに出る。直後の文で意味は分かるが、レート 1000 前後の読者には記号が初見でありうる | — | 「状態 v から 1 文字で u に移る文字の数」と文で先に言い、式はその言い換えにする（コード片のコメントと同じ言い方） |

## 執筆者の未解決の点について

- abc419_f の制約：ikatakos.com は今も HTTP 503 で、L と各パターンの長さの上限を確かめられなかった。kcpc の記事は「26^10 と比べる」形で各 10 文字以下を示唆し、状態数 80 程度と書いている。本文の「100 に届かない程度」・#contain-all の S = 81 の見積もりはこれと矛盾しないので、今の書き方（上限の値を断言しない）でよい。#contain-all の「N が数百までなら間に合う」も L の上限を断言していないので問題なし
- 「abc458_f の解説が包除の破綻を説明している」：gdst.dev の記事には包除の話はない。本文はこの主張に頼らず自分の例で示しているので問題なし。題については指摘 4
- 使い分けを定型の節にした判断：手引き §14-2 のとおりで同意する

## 台帳への提案

- abc458_f：evidence に https://gdst.dev/posts/abc458_f/ を足す案に同意する（制約と方針を確かめた。checked は既に 2026-10-21）
- abc419_f：evidence に https://kcpc.hatenablog.com/entry/ABC419 を足す案に同意する。問い（すべて含む）と状態の方針は確かめたので checked に 2026-10-21 を入れてよい。L の上限は ikatakos が戻ったら確かめ直す

## 総合の判定

小さな直しで可。直すべき 1 件（matching-state の sections の title と見出しの食い違い）・直すとよい 6 件。コード片・式・数値・確認問題・問題の方針に誤りは見つからなかった。
