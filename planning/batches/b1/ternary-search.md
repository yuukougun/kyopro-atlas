# ternary-search の報告と提案（工程8b）

- 書いたファイル：docs/basics/ternary-search.md、snippets/ternary-search/{ternary-real,ternary-int,diff-sign,marginal-greedy}.{cpp,yaml}、docs/img/ternary-search/{shrink,difference-sign,flat-pitfall}.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（4 片・期待と違う 0）、textlint（エラー 0、警告 20。数式内の括弧・数式を含む文の長さ・画像の代替テキストの読点など誤検出が主）
- 動く図：作っていない（visual は priority 2 の static。静的な SVG 3 枚で代えた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc130_f | approach | 端の動きが区分線形なので、式が変わる候補の時刻を列挙する（面積は凸でないので全体の三分探索は正しさが保証されない） | https://drken1215.hatenablog.com/entry/2019/06/22/022600 （「全体で三分探索をするのは嘘」）。circle-geometry 側の alternatives の記述とも合う |
| abc359_f | summary（本体） | 末尾に「。」がない。「各頂点 i の次数を d_i とした木のコスト Σ d_i^2 A_i の最小値を求める。」 | 表記の統一 |
| abc279_d | approach | 「x について下に凸なので整数の三分探索をする（範囲は 0〜⌊A/B⌋）」と補ってもよい | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc279-d.html |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 凸関数（下に凸） | convex-function | グラフ上の 2 点を結ぶ線分が、その間でグラフより下にならない関数。実数なら傾きが右へ行くほど大きく、整数なら差分 f(x+1) − f(x) が広義単調増加である。本文でリンク済み（`../guide/glossary.md#convex-function`） |
| 単峰 | unimodal | 最小（または最大）に向かって単調に減り、そこから単調に増える関数。凸関数は単峰だが、単峰でも凸とは限らない（本文では使っていないので任意） |

## 手引きへの提案

- 整数の凸関数の最小化で「差分の符号で二分探索」を勧める方針は binary-search-answer の使い分けとも合う。手引き §5 basics に「三分探索は凸性の確かめ方と、整数では差分の二分探索を主役にする」を足してもよい
- 例題の数の目安で、基礎のページは 1、technique の水は 1〜3 とあり、このページ（水）は catalog どおり 2 問にした

## 問題の補充の候補

- drken の「三分探索」「凸関数」の分類から探したが、ABC で水〜青の新しい候補は見つからなかった（ABC314 Ex は赤で難しすぎる。https://drken1215.hatenablog.com/archive/category/三分探索 ・ https://drken1215.hatenablog.com/archive/category/凸関数 ）。abc319 以降の問題は abc359_f（練習）で 1 問あり、手引き §10 の条件は満たしている
- 練習が 2 問で最小限なので、次のバッチで「整数の凸関数の最小化（丸めを含まない式）」の ABC D〜E を探すとよい（未確認のため ID は挙げない）

## 未解決の点

- 用語集に convex-function がまだない（リンクは提案の anchor で書いた）
- greedy-priority-queue・slope-trick・circle-geometry・tree-degree・median-absolute は stub なので、節の anchor ではなくページへリンクした。circle-geometry の ternary-search-caveats（黄）と内容が重なるので、そちらを書くときはこのページの flat-pitfall と convexity へリンクすると重複を避けられる
- ARC054 B の制約（P の範囲・許容誤差）は第三者の解説に明記がなく、本文では範囲を [0, P] と式から決め、制約の数値は書いていない
- 黄金分割探索の評価回数（約 86 回）と三分探索（約 204 回）は自分で計算した値（幅を 10^−18 倍にする場合）
- 使った出典：oraclesqlpuzzle（abc279_d・arc054_b）、drken（abc151_f・abc359_f・abc130_f・分類のページ）。どれも付録 B で確認済みのドメイン

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：直した。要点・complexity に「反復は log_{3/2}(W/ε) 回、W/ε が 10^17 程度までなら 100 回、W が 10^18 近いなら 200 回」と書き、#real-and-integer に W = 10^18 では 100 回で幅が約 2.5 残る旨を足した。ARC054 B は「P が 10^18 に達しうるので 200 回」とした
- 指摘 2：本文のリンクは残す。用語集への convex-function の追加（上の「用語集への提案」）をメインに改めて頼む。反映しない場合はリンクを外す必要がある（--strict でビルドが落ちる）
- 指摘 3：直した。「区分線形の関数の積」を #flat-pitfall の列挙から外し、#convexity の「凸にならない作り方」に谷が複数になる例として移した
- 指摘 4・5・6：直した（境界の配り方と個数の数え方を足す、黄金分割探索の段落に主語を書く、O 記法から定数を外し N の目安を 10^3 程度に）
- 指摘 7：直した。2 枚の SVG の題を短くし、下の注記の行は本文（図の後の段落・#difference-sign の箇条）に任せて削った（viewBox の高さも詰めた）
- 指摘 8：台帳への提案（abc130_f の approach ほか）は上の表のとおり。あわせて abc279_d・arc054_b・abc151_f・abc359_f・abc130_f の `checked` に 2026-10-21 を入れることを提案する（検証役が題名・diff・evidence を確かめた）
- 採らなかった指摘：なし
