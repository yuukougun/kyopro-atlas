# dp-phase の報告（b2）

- 書いたファイル：docs/dp/dp-phase.md、snippets/dp-phase/{kadane,flip,matched-prefix,all-segments}.{cpp,yaml}、docs/img/dp-phase/phases.svg
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま。sections は骨格のまま（落とし穴は §14-1 により定型の節で、sections に入れていない）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 本・期待と違う 0。各本に素朴な全探索との assert あり）、textlint（エラー 0・警告 10。数式の `[l, r)` の括弧の対応・数式を含む文の長さ・図の代替テキストの読点など誤検出）
- 図：phases.svg を render_svg.py で 360px・720px の PNG にして目で確かめた。動く図は作っていない（visual は priority 2 で、静的な図で帯と状態遷移図の両方を描いた）
- 使った出典：
  - https://en.wikipedia.org/wiki/Maximum_subarray_problem（Kadane の形と空の区間）
  - https://drken1215.hatenablog.com/entry/2022/04/01/121700（典型90 008）
  - https://drken1215.hatenablog.com/entry/2020/03/22/224200（ABC159 F）
  - https://qiita.com/comet725/items/d9928d9fdb242140f987（ABC466 E）
  - https://drken1215.hatenablog.com/entry/2018/08/05/224100_1（ABC104 D）
  - https://drken1215.hatenablog.com/entry/2019/02/10/014800（Ears）
  - 新しく check_noai で確かめたドメイン：gink03.github.io・babcs2035.hateblo.jp（どちらも指定なし。中身が Ears の 5 段階の裏付けにならなかったので本文では使っていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| yahoo_procon2019_qual_d | evidence | https://www.mathenachia.blog/dp/ を外し、https://drken1215.hatenablog.com/entry/2019/02/10/014800 に替える | mathenachia の URL は 2026-10-21 に 404（curl・WebFetch とも）。drken の記事で 5 段階とコストを確かめた |
| yahoo_procon2019_qual_d | label の表示名 | contest yahoo-procon2019-qual の表示名を「みんなのプロコン 2019」にする案（今は fix_problems が「YAHOO-PROCON2019-QUAL D. Ears」を作る） | interfaces.md §3 の「ほかは contest id を大文字」の規則どおりだが、読み手に通じにくい。決めるのはメイン |
| abc466_e | alternatives の dp-phase の summary | 「表と裏に数が書かれたカードの列で、区間の裏返しを K 回以下行った後の、上を向いた数の和の最大値を求める。」（主の summary と同じ）。（執筆時に確かめる）を消す | comet725 の解答（状態 0〜2K、段階の偶奇で表裏の値を足す） |
| abc159_f | approach | 「区間を 1 つ選ぶ段階（前・中・後）に、段階 1 で選ぶかどうかを重ねて (区間, 選び方) の組を数える」 | 本文の方針に合わせる。drken の記事の耳 DP の節 |

## 用語集への提案

- なし（状態・オーバーフローは既存の anchor を使った）

## 手引きへの提案

- 問題の label で、contest id を大文字にしただけの表示名（YAHOO-PROCON2019-QUAL など）を本文でどう呼ぶかの決まりがあるとよい。本文では label の一部「YAHOO-PROCON2019-QUAL D. Ears」をそのまま使った

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc360_g | 数列の要素を 1 つだけ好きな整数に変えてよいときの LIS の最大（台帳では lis の練習） | 本ページの練習（「変更済みか」の 2 段階。節 flip-interval で lis#variants へ触れている） | 台帳の evidence は usaco.guide のみなので、第三者の日本語解説を足してから（未確認） |
| abc211_c | 文字列から 8 文字を選んで chokudai になる選び方の数（台帳では subsequence-and-substring の例題） | 本ページの練習（matched-prefix の最も易しい形） | https://qiita.com/sano192/items/051207b6607b56cc439e（台帳の evidence） |

- 確認済みの問題は例題 2・練習 3 で数は足りている。力試しは 0 問。abc319 以降は abc466_e の 1 問だけ

## 未解決の点

- catalog の sections には pitfalls があったが、§14-1 に従い定型の `## 落とし穴 {#pitfalls}` にした（骨格の sections にもなかった）
- ABC466 E の制約（N・K の上限）は確かめていない。本文では $O(NK)$ とだけ書いた
- 例題 ABC159 F の本文の DP（区間と選び方の組を直接数える 3 段階）は、drken の記事の 2 つの方法（重みを掛ける耳 DP・左端の数を値に畳む方法）とは別の書き方で、全探索との assert（N ≤ 12）で確かめた
- 「耳 DP」の語は指す範囲が人によって違う（chokudai 氏の発言として検索結果に出たが、x.com は開いていない）。本文では別名の行にだけ置いた

## 検証の指摘への対応（b2 verify）

- 1（直すべき・Ears のコストの説明）：「段階の種類（0 回・正の偶数回・奇数回）と $A_i$ だけで決まる」に直した
- 2（導入の 1 対 1 対応）：「段階 1 の位置が 1 つ以上ある」条件を足した
- 3（遷移の一般形）：間の段階を長さ 0 で飛ばすことが $q \to p$ にあたり、段階ごとに決まること、最初・最後の段階の長さ 0 は初期値・答えで表すことを書き分け、Kadane の例を添えた
- 4（Ears の練習の方針）：5 つに分けることと回数の性質・長さ 0 を許すことまでにし、コストの式と遷移の範囲は外した
- 5（図の 360 幅）：帯の下の説明の 1 行（本文 56 行目と同じ内容）を外し、状態遷移図のラベルを 13→15、「入って a を足す」を 12→14 の 2 行にし、viewBox を 600×400 から 580×350 に詰めた。render_svg.py の 360・720 幅で確かめた
- 採らなかったもの：なし
