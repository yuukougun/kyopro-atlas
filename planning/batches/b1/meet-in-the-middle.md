# meet-in-the-middle の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/meet-in-the-middle.md、snippets/meet-in-the-middle/max-sum.{cpp,yaml}・by-count.{cpp,yaml}、docs/img/meet-in-the-middle/combine.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 3。51 行は数式 $A_0, \dots$ の読点の誤検出、189 行は数式を挟んだ「は」の重複の誤検出、226 行は参考の題名の長さ）
- コード片は、手元で 2^n の全探索と 300 組の乱択入力で答えを突き合わせた（一時置き場のスクリプト、どちらも一致）
- 図：catalog の visual（static、priority 2）のとおり、前半・後半の部分和の列と、二分探索で見つかる相手を矢印で示す SVG を作った。描画の道具が手元になく、見た目は目で確かめていない（座標と文字幅の見積もりだけ）。検証で確かめてほしい
- 動く図は作っていない（priority 2 のため不要）

## 使った出典

- drken ABC184 F・AGC026 C・ABC300 G（hatenablog）、oraclesqlpuzzle ABC271 F、ikatakos ABC464（解説の部分だけ）：台帳の evidence
- E869120 kyopro_educational_90 の sol/051.cpp（github.com）：典型90 051 の方針（個数ごとに分けて lower_bound）。台帳の evidence の qiita（dvoraker3）はリンク集で、方針の記述がなかったため
- miraclepbc（www.cnblogs.com）：ABC271 F の制約 N ≤ 20 と対角線での突き合わせ
- 新しく noai を確かめたドメイン：なし（www.cnblogs.com・atcoder-tags.herokuapp.com は付録 B にある。念のため check_noai で個別の URL も確かめ、指定なし）

## 台帳への提案

- typical90_ay｜evidence｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/051.cpp を足す｜今の evidence（qiita のリンク集）には方針の記述がない。公式の解説画像 editorial/051.jpg も候補（読んでいない）
- abc271_f｜evidence｜https://www.cnblogs.com/miraclepbc/p/16768972.html を足す｜oraclesqlpuzzle のページには制約が書かれておらず、N ≤ 20 はこちらで確かめた
- abc271_f｜summary｜「N ≤ 20 の N×N のグリッドの左上から右下へ…」と制約を入れてもよい（任意）
- catalog の abc464_f の summary が「（執筆時に確かめる）」のままだが、台帳には summary が入っていて、ikatakos の解説の方針と合っていた。台帳はこのままでよい

## 用語集への提案

- 両側探索｜bidirectional-search｜初期状態と目標の状態の両方から探索を進め、途中で出会った状態で 2 つの探索をつなぐ方法。片側から深さ d まで探すより、両側から d/2 ずつ探す方が状態の数がずっと少ない。（本文では用語集へリンクしていない。リンクするならメインで判断）

## 手引きへの提案

- なし。§13 の「まだないページへのリンク」と「節へのリンクは draft 以降」の両方に該当する場面（bit-full-search#half-greedy・knapsack-01#choose-by-size）があった。今はページへのリンクにしてある。これらのページが draft になったら、メインで節へのリンクに直すとよい：
  - （bit-full-search は執筆中に draft になったので、vs-greedy の節から `#half-greedy` へリンクした）
  - vs-knapsack の節の [ナップサック DP] → `../dp/knapsack-01.md#choose-by-size`

## 問題の補充の候補

水・青のページには abc319 以降の問題を 1 問以上（手引き §10）とあるが、今は力試しの abc464_f（2225）だけ。次を候補にする。

- abc326_f（F. Robot Rotation、diff 1870、ap.py で確認）｜練習｜「回るたびに 90 度向きを変えながら進むロボットで、各移動の左右の回り方を選んで点 (X, Y) に着けるか判定し、着けるなら回り方を 1 つ出力する。」移動は x 軸と y 軸に交互に効くので、x と y の問題に分け、それぞれ ± の符号の選び方を半分全列挙で突き合わせ、選び方を復元する｜裏付け：https://www.cnblogs.com/RainPPR/p/solution-at-abc326-f.html（check_noai で指定なし）。atcoder-tags の「半分全列挙」にも載る（https://atcoder-tags.herokuapp.com/tags/Technique/Split-And-List）。制約（N ≤ 80 など）は解説から確かめきれていない
- abc336_f（Rotation Puzzle、diff 2018、atcoder-tags で半分全列挙）｜力試し（両側探索）の候補。第三者の解説はまだ見つけていない（未確認）
- 古い問題（atcoder-tags の同じタグ）：abc018_4 バレンタインデー（1711）・arc017_3 無駄なものが嫌いな人（1625）。どちらも未確認。典型 90 051 の類題としてリンク集（dvoraker3）にも載る

## 未解決の点

- 典型90 051 の制約（K・P・A_i の範囲）は確かめておらず、本文には N ≤ 40 だけを書いた。答えの上限は C(40, 20) ≈ 1.4×10^11 と計算で書いた
- ABC464 F の方針は ikatakos の解説を要約させて読んだ範囲で書いた（最後の金庫 i を固定し、前に開ける集合の大きさで確率が決まる・個数ごとの列と累積和・尺取り）。細部（L と R を入れ替えて 2 回行うこと）は本文に書いていない
- vs-knapsack の表の目安（DP は T が 10^5〜10^6 程度まで、bitset は NT が 10^9〜10^10 程度）は計算量からの見積もりで、出典はない。complexity-estimation のページの目安とそろえる必要があればメインで直してほしい
- 参考に載せた E869120「上級編」は、半分全列挙が黄色を目指す追加の項目であることを research 01（§2 の資料表）経由で使った。本文の主張には使っていない
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 約 10 回（検索 7 回）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜7 はすべて直した。指摘 1 は knapsack-01 が draft になっていたので、担当ページの中で `../dp/knapsack-01.md#choose-by-size` へのリンクに直した（メインの反映は不要）。指摘 5 は (a) を書き直し、(b) として $N = 41$ の分け方と列の長さを問う小問を足した。指摘 7 は font-size を 14→16・12→14 に上げた（配置は変えていない）
- 指摘 3 に合わせて、力試しの方針の ABC300 G の $p$ を問題の変数の $P$ にそろえた

## 台帳への提案（検証を受けて追加）

- abc300_g｜summary｜「p 以下の素数だけを…」を「P 以下の素数だけを…」にそろえる（問題の変数が大文字の P。prime-exponent-vector の alternatives の summary も P）
- abc184_f・abc271_f・agc026_c・abc300_g｜checked 2026-10-21｜検証の報告（verify/meet-in-the-middle.md）の「台帳への提案」のとおり
