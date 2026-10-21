# tree-dp-square の報告と提案（b3）

- 書いたファイル：docs/dp/tree-dp-square.md、snippets/tree-dp-square/tree-knapsack.{cpp,yaml}、snippets/tree-dp-square/components.{cpp,yaml}、docs/img/tree-dp-square/pairs-at-lca.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（2 件とも期待どおり。どちらも小さい木で全探索の assert を持ち、手元で N ≤ 12 の乱択 300 件でも assert が通った。N = 5000 の一直線・星形で components は 0.07 秒）、textlint（エラー0・警告11。数式を含む文の長さ、図の代替テキスト、「か」「は」の重なりの誤検出）
- 図：pairs-at-lca.svg（catalog の visual、static・priority 2）を render_svg.py で PNG にして目で確かめた。動く図は作っていない
- 使った出典：qiita.com/jikei/items/780bc6f793e1b12e3a37、merom686.hatenablog.com/entry/2023/01/28/234655、kanpurin.hatenablog.com/entry/2020/04/07/182948、kmjp.hatenablog.jp/entry/2021/06/27/0900、drken1215.hatenablog.com/entry/2024/02/05/021046、www.luogu.com.cn/article/kjm1y7yt、sigma425.hatenablog.com/entry/2016/08/02/214547、kmjp.hatenablog.jp/entry/2021/12/21/0930
- 新しく noai を確かめたドメイン：なし（使ったのは付録 B のドメインだけ。note.com/anoconne と devgenjin77.hatenablog.com は check_noai で指定なしだったが、abc287_f の記述がなく使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc287_f | evidence | https://qiita.com/jikei/items/780bc6f793e1b12e3a37 を足す（今の kanpurin の記事は問題の一覧だけで、解法がない） | 記事の F の節で、頂点を使う・使わないの 2 つの配列、両方使うと成分が 1 減る遷移、N = 5000 を確かめた |
| abc287_f | checked | 2026-10-21 | 同上 |
| arc171_c | summary | 木の頂点 i に駒 i を置き、まだ選んでいない辺を 1 本選んで両端の駒を入れ替える操作を好きな回数行う（各辺は 1 回まで）。最後の駒の並びとしてありうるものの数を求める。 | https://www.luogu.com.cn/article/kjm1y7yt （問題文の要約・N ≤ 3000・mod 998244353） |
| arc171_c | evidence | 上の Luogu の記事を足す（drken の記事は問題文が画像で、問いを文字で確かめられない） | 同上 |
| arc171_c | checked | 2026-10-21 | 同上 |
| arc130_d | evidence | https://www.mathenachia.blog/dp/ が 404（2026-10-21）。https://kmjp.hatenablog.jp/entry/2021/12/21/0930 に差し替える | kmjp の記事で、問い（どの長さ 3 のパスでも真ん中が最大か最小）と f(v, n)・対称性を確かめた。台帳の summary と同じ意味 |
| arc130_d | checked | 2026-10-21 | 同上 |

- tdpc_eel は evidence の sigma425 の記事に状態（本数と下へ伸びる本数 0〜2）しか書かれておらず、問いの文（K 本のパスの条件・制約）は確かめられなかった。checked は空のまま
- arc171_c の approach（「子の数と選んだ辺の数を状態にする」）は、Luogu の記事では「v と子を結ぶ辺のうち選んだ本数を添字にし、親との辺を選ぶかで i! か (i+1)! を掛ける」で、本文の方針はこちらで書いた。approach を「各頂点の選んだ次数の階乗の積を、子への辺の本数を添字にした DP で足す」に直す案

## 用語集への提案

- なし（本文で用語集へリンクしていない）

## 手引きへの提案

- §14-25「箇条書きの各行は句点で終える」に従い、本文の箇条書きは句点で終えた。見本と同じ分野の draft（docs/dp/tree-dp.md など）は句点がないので、どちらにそろえるかを決めてほしい
- dp の §5 に「二乗の木 DP の計算量は、添字の範囲が部分木のサイズに比例するときだけ成り立つ（配列を長さ N で取らない・サイズの更新はマージの後）」を足す案。tree-dp・insertion-dp など、部分木や長さで添字を抑える DP を書く人が同じ落とし穴を書けるように

## 問題の補充の候補

- 目安（例題 1・練習 3・力試し 1）は満たしているので、新しい問題は探していない
- catalog の level_evidence にある arc121_e・arc101_c（発展）は本文で使っていない。力試しを増やすなら候補だが、第三者の解説で問いを確かめていない

## 未解決の点

- TDPC P の制約（N・K の大きさ）と「パス」の条件（長さ 1 以上か）を確かめられなかったので、方針は状態と K での打ち切りだけにして、計算量の数値は書いていない
- cap-k の節の「N ≤ 10^5 の木から K ≤ 100 個選ぶ」は型の例で、特定の問題を指していない。台帳にこの型の確認済みの問題があれば、練習に足して節からリンクできる
- arc171_c の「使う辺の集合が違えば結果も違う」「各頂点の辺の順だけが結果を決める」は Luogu の記事（中国語）と drken の記事のコードで確かめた。日本語の第三者の解説で問題文を文字で確かめられる記事は見つからなかった

## 検証の指摘への対応（b3）

- 1（直すべき）：直した。落とし穴の文を「`dp[c] = vector<long long>();`（または `vector<long long>().swap(dp[c]);`）で捨てる。`dp[c] = {};` や `clear()` は容量を解放しない」に替え、components.cpp も `dp[c] = array<vector<mint>, 2>();` と型を書く形にした
- 2：直した（「$i = j = 0$ のときに添字 $-1$ へ書き込み、範囲外になる」）
- 3：直した（ABC207 F の方針を「見張られていない頂点は、隣（親か子）に見張りを置くと分かったマージで +1 する」に）
- 4（図の 360px での文字の小ささ）：採らなかった。検証役も「代替テキストと本文で意味は通るので急がない」としており、配置を縦長に組み替えると表と木の対応の見やすさが変わるため、図の見直しをまとめて行う機会に回したい
- 5（TDPC P の要約）：採らなかった。問題文を atcoder.jp 以外で確かめられる資料がまだなく、「頂点を共有しない」と書くと確かめていない事実になる。資料が見つかったら台帳の summary を「互いに頂点を共有しない K 本のパス」の形にし checked を埋める（提案として残す）
