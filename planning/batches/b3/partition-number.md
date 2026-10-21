# partition-number（整数の分割と分割数）執筆の報告

- 書いたファイル：docs/comb/partition-number.md、snippets/partition-number/{partition,cycle-type,count-multiset}.{cpp,yaml}、docs/img/partition-number/young-5.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 件・期待と違う 0）、textlint（エラー 0、警告 12。数式を含む文の長さ・読点、要点の囲みの全体、「重複も漏れもない」「の有無と…も」などの助詞の重なりの誤検出）
- 図：young-5.svg（n = 5 の 7 通りを Young 図形で、最大の部分と個数を添える）。render_svg で 360px・720px を目で確かめた。catalog の visual は static・priority 2 なので動く図は作っていない
- 使った出典：
  - ikatakos の ABC226・ABC404 の記事は本体が「メンテナンス中」だったので、web.archive.org の写し（2025 年）で解法の部分だけを読んだ（問題文の節は読んでいない）。参考の URL は ikatakos.com の元の URL を書いた
  - kmjp（abc221_h）、drken「分割数と、問題まとめ」、drken「第4回 ドワンゴからの挑戦状 予選 2018 C」、merom686「ABC404」
  - 新しく noai を確かめたドメイン（どれも指定なし）：yamate11.github.io、competitive12.blogspot.com、hidehic0.github.io（F の記述がなく使っていない）、web.archive.org（check_noai は通していない。写しの元は付録 B の ikatakos.com）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc404_f | summary | N 個のボタンのうち 1 つだけが当たりで、ボタンの並びは毎回見分けられないように入れ替わる。1 回に合計 M 回ボタンを押すことを T 回くり返すとき、当たりを合計 K 回以上押せる確率の最大値を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0503_abc404#f_-_lost_and_pound （解法の節：残りターン t・残り必要押し回数 k の勝率、押し方は和が M の分割）、https://merom686.hatenablog.com/entry/2025/05/04/203436 |
| abc404_f | evidence | 上に merom686 の記事を足す（ikatakos が保守中で読めないときの代わり） | 同上 |
| abc226_f | evidence | https://competitive12.blogspot.com/2021/11/abc-226-f-score-of-permutations.html と https://yamate11.github.io/blog/posts/2021/11-08-abc226/ を足す | 同ページ（巡回の長さの lcm、分割の全列挙で解けること） |

本文の abc404_f の行は、`- abc404_f：自分の要約` の形で fix_problems が label を埋めた（§14-16）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 多重集合 | multiset | 同じ要素を何個でも含んでよい集合。要素の順序は区別せず、各要素の個数だけで決まる。{1, 1, 2} と {1, 2} は違う多重集合である |

本文では用語集へのリンクは張っていない（提案が入ったら「多重集合」の初出に張るとよい）。

## 手引き・早見表への提案

- 計算量の見積もり（basics/complexity-estimation#count-candidates）の表に「分割数 p(N)：p(30) = 5604、p(50) = 204226、p(100) ≈ 1.9×10^8」の行を足す（07 調査 §7.5 の指摘と同じ）。いまは階乗・ベル数・二項係数・約数の個数だけ
- 手引き §5 comb に「分割数の p(n,k) は資料によって『部分が k 以下（＝個数 k 以下）』『ちょうど k 個』『0 を含めて k 個』と定義が違う。ページの中で 1 つに決め、小さい値で確かめる」を足すとよい（twelvefold-way・stars-and-bars を書くときにそろえるため）。このページは「部分が k 以下（＝個数 k 以下）」を p(n,k) とし、ちょうど k 個を p(n−k,k) と書いた

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| dwacon2018_prelims_c（C. Kill/Death、diff なし、ap.py で実在を確認） | 2 チームの各メンバーのキル数（広義単調減少）が与えられ、キル数の合計と相手チームのデス数の合計が等しく、同じキル数のメンバーの中ではデス数が広義単調になるようなデス数の割り当ての数を求める。同じキル数の区間ごとに「和を何個に分けるか」が分割数（ちょうど c 個以下の部分）になり、それを重さにした DP で数える | https://drken1215.hatenablog.com/entry/2023/05/07/160611 、https://drken1215.hatenablog.com/entry/2018/01/16/222843 |

- 役割の案：練習（catalog の problems_note「練習の候補が見つかっていない」への答え）。ABC ではないので、ABC の候補が見つかればそちらを優先する
- ABC で分割の全列挙・分割数の DP を練習にできる問題は、今回の検索（kmjp・drken の「分割数」カテゴリ・Web 検索）では見つからなかった

## 未解決の点

- abc226_f の制約 N ≤ 50 は、第三者の解説（ikatakos が N = 50 で状態数を試したこと、sansaqua が g(50) で見積もったこと）からの判断で、問題文では確かめていない。K の上限は書いていない
- abc404_f の M ≤ 30 も、ikatakos の「M = 30 でも 5604 個」と merom686 の「30 というのが絶妙」からの判断である。N・T・K の上限は書いていない
- abc221_h の N の上限は本文に書かず「O(N^2)」とだけ書いた。力試しの方針のメモリの注意（N^2 個の表）は、N が数千であることを前提にしている（kmjp のコードの配列 5050×5050 から）
- 発展の節で「Library Checker の Partition Function」に触れたが、制約の値は確かめていない（存在は drken の記事の題名で確認）
- ikatakos.com が保守中で読めなかったため、web.archive.org の写しを使った。付録 B に web.archive.org を足すかはメインの判断に任せる

## 使用量の目安

- 道具の呼び出し約 45 回、Web 取得・検索 約 20 回

## 検証の指摘への対応（b3）

- 指摘 1〜4（いずれも「直すとよい」）はすべて採った。採らなかったものはない
  - 1：境界の節と落とし穴に「表全体が 0 になる」（p(1,1) = p(1,0) + p(0,1) = 0 から）と、全部 0 が出たら疑う旨を書いた
  - 2：count-multiset.cpp の `f` を `dp` にし、コメントを「同じ値は M 個以下（入力の m）」にした。本文にも「コードでは上限 M を入力の `m` で受け取る」と添えた
  - 3：young-5.svg の上の段のラベルを y = 95・117 に上げ、下の段を 36 上げて viewBox の高さを 340→304 にした（render_svg で 720px を目視）
  - 4：abc404_f の解法の詳細に「k > tM なら f(t,k) = 0 で調べなくてよい。k は min(K, tM) までに絞れる」を足した
- 提案（メイン向け）：abc404_f の N・M・T・K の上限は未確認のまま。ikatakos の記事が読めるようになったら確かめ、台帳の checked はそれまで入れない（検証の提案に同意）
