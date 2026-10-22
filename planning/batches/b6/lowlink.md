# lowlink の問題の補充（工程9・b6）

- ページ：docs/graph/lowlink.md（レベル 黄）
- 今の問題：例題 abc075_c（1 問）、練習 0 問、力試し 0 問（練習の節は Library Checker の 2 問と、ABC375 G・ABC334 G への文章での言及だけ）
- 結論：練習の候補 2 問（合わせて 2 問になる）と力試しの候補 1 問を確かめた。difficulty・題名はすべて `python3 tools/ap.py show` で確かめた（2026-10-22）。練習の 2 問はどちらも台帳に `{id: lowlink, role: practice}` が既にあり、本文の囲みに入っていないだけである

## 練習の候補（practice）

### abc375_g　G. Road Blocked 2（diff 2014・黄）

- 台帳：登録済み（shortest-path-dag:challenge・lowlink:practice）。本文の練習問題の囲みに移すだけでよい
- 要約：各道路について、その道路だけを通行止めにしたとき都市 1 から都市 N への最短距離が変わるかを判定する。
- 方針の要点：1 と N からの最短距離で dist1[x] + c + distN[y] = dist1[N] となる辺だけを取り出した部分グラフを作り、その橋になっている辺だけで答えが変わる。
- このページとの対応：#conditions（橋の判定）。部分グラフは多重辺を含みうるので #multi-edges の注意も効く
- 裏付け：
  - https://www.cnblogs.com/codwarm/p/18463129 （最短路に乗る辺の部分グラフで Tarjan により橋を求める。今回開いて確かめた）
  - https://kmjp.hatenablog.jp/entry/2024/10/14/0930 （台帳の evidence。最短路の本数で判定する別解。今回は開き直していない）

### abc334_g　G. Christmas Color Grid 2（diff 2242・黄）

- 台帳：登録済み（offline-dynamic-connectivity:example・lowlink:practice）。本文の練習問題の囲みに移すだけでよい
- 要約：緑のマスを 1 つ一様に選んで赤に塗り替えたときの、緑のマスの連結成分の数の期待値を求める。
- 方針の要点：各マスを除いたときの成分の増分を、根でない頂点は low(c) ≥ ord(u) を満たす子の数、根は子の数 − 1 として数え、元の成分数に足した総和をマスの数で割る。
- このページとの対応：#conditions と応用の型「辺・頂点を 1 つ除いたときの連結成分の数」（pieces[v]）。孤立したマスを除くと成分が 1 減る点は落とし穴の節と同じ
- 裏付け：
  - https://amentorimaru.hatenablog.com/entry/2025/04/11/210228 （ord・low と子の条件で増減を数える。今回開いて確かめた）
  - https://kmjp.hatenablog.jp/entry/2023/12/23/1030 （台帳の evidence。今回は開き直していない）

## 力試しの候補（challenge）

### arc039_d　D. 旅行会社高橋君（diff 2550・参考値・発展）

- 台帳：未登録（新規の追加の提案。b3 の報告でも提案済み）
- 要約：無向グラフで、頂点 A から B を経て C へ、同じ橋を 2 度渡らずに行けるかをクエリごとに答える。
- 方針の要点：二重辺連結成分で縮約した木（橋の木）の上で、B の成分が A の成分と C の成分を結ぶ道に乗るかを、LCA で求めた距離が dist(A,B) + dist(B,C) = dist(A,C) を満たすかで判定する。
- このページとの対応：#two-edge-connected（縮約すると木になる）。帯（黄）より上なので力試し
- 裏付け：
  - https://ei1333.github.io/luzhiled/snippets/graph/two-edge-connected-components.html （この問題が検証に挙がり、成分の縮約と木の上の LCA の距離で答えるコードがある。今回開いて確かめた）
  - https://blog.hamayanhamayan.com/entry/2016/10/18/123552 （一覧の「二重辺連結成分分解と橋」の節にある。解法の説明はない）

## 見送ったもの・確かめきれなかったもの

- abc318_g（G. Typical Path Problem、diff 2260・黄）：A から B を通って C へ行く単純パスがあるかを問う。ブロックカット木で B のブロックが A と C を結ぶ道に乗るかを調べれば解ける見込みだが、確かめた解説（台帳の evidence の https://kmjp.hatenablog.jp/entry/2023/09/02/0900 ）は頂点を分けた最大流で解いており、ブロックカット木の解法は書かれていない。第三者の解説で裏付けられなかったので候補にしない（今回の作業では Web 検索の回数の上限に達し、ほかの解説を探せなかった）。見つかれば #block-cut-tree（発展）の力試しに向く
- tenka1_2015_qualA_d（D. ハシポン）・arc045_d・arc062_d：b3 で挙がったが難しすぎるうえ、解説を読んでいない。今回も確かめていない
- hamayan の一覧（上の URL）には橋・関節点・二重連結成分に分類された ABC の問題がない。ABC で lowlink をそのまま使う問題は少ない、という本文の記述と合う

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc375_g | evidence に追加 | https://www.cnblogs.com/codwarm/p/18463129 | lowlink の方針の裏付け（b3 でも提案済み。未反映なら） |
| abc334_g | （変更なし） | evidence に amentorimaru の記事は既にある | — |
| arc039_d | 新規 | contest arc039・index D・title 旅行会社高橋君・difficulty 2550（参考値）・pages [{id: lowlink, role: challenge}]・evidence 上の 2 件 | 上の節 |

## 本文への反映（メインの判断）

- 練習問題の節の文章「ABC の G で、橋や関節点を使って解ける問題として……」を、abc375_g・abc334_g の練習問題の囲みに置き換える（b3 の未解決の点 2）

## 使用量の目安

- 道具の呼び出し 約 12 回、Web 取得 7 回（うち 2 回は 401・404）、検索 1 回（上限で実行されず）
