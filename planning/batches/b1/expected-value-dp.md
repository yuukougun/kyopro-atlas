# expected-value-dp（期待値 DP）執筆の報告

- 書いたファイル：docs/comb/expected-value-dp.md、snippets/expected-value-dp/hp-mod.{cpp,yaml}・self-loop.{cpp,yaml}、docs/img/expected-value-dp/hp-chain.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 期待と違う 0／textlint エラー 0・警告 23（数式を含む文の長さ・読点の数、数式の中の文字を拾った助詞の重なり、問題の要約の x。規則の誤検出として残した）
- 使った出典：drken（abc280_e・abc184_d の記事、Qiita の EDPC F〜J）、kazun（abc263_e）、programming-hiroba（abc350_e）、ikatakos（abc382_e。解法の部分だけ）、DeltaStruct（Qiita、abc314_e）、kmjp（abc144_f、TDPC J）、ACL の document_ja（GitHub）。すべて付録 B のドメインで、新しいドメインはない
- 動く図は作っていない（visual は priority 1）。置き場の div と前後の文章だけを書いた（下の「動く図の仕様」）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| tdpc_ball | summary | 位置 0〜15 にある的を、位置 x を狙うと x−1・x・x+1 のどれかに等確率でボールが当たる投げ方で倒していくとき、最適に狙ったときの全部倒すまでの投げる回数の期待値を求める。 | https://kmjp.hatenablog.jp/entry/2013/09/09/1030 |
| tdpc_ball | evidence | kmjp の記事を足す（今の sigma425 の記事は「bitDP・移項」の一言だけで、問いを確かめられない） | https://kmjp.hatenablog.jp/entry/2013/09/09/1030 |
| tdpc_ball | approach | 残っている的の集合を状態にし、狙う位置ごとに外れたときの自己ループを移項して、期待値の最小を取る（「最適に狙う」が抜けていた） | 同上 |
| abc266_e | summary（主の値） | 主の summary と expected-value-dp 用の alternatives が別の文になっている。本文には alternatives の文を使った。1 つにそろえるなら alternatives の文がよい | https://kazun-kyopro.hatenablog.com/entry/ABC/266/E |
| abc266_e | evidence | `https://kazun-kyopro.hatenablog.com/entry/ABC/NNN/X` はひな形の URL なので消す（abc263_e も同じ） | — |
| abc144_f | approach | 「各部屋で、行き先の期待値が最大の通路だけを塞ぐ候補にし、塞ぐ部屋ごとに DP をやり直して O(NM)」と具体にするとよい | https://kmjp.hatenablog.jp/entry/2019/10/28/0930 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 自己ループ | self-loop | 状態の遷移で、ある状態から同じ状態へ戻る遷移。期待値の式では左辺と同じ値が右辺に現れるので、移項して解く |
| 終状態 | terminal-state | それ以上遷移しない状態。期待値 DP では「残りの量」が 0 と分かっているので、計算の出発点になる |

（本文では用語集へリンクしていない。足すなら本文の最初の出現にリンクを付けられる）

## 手引きへの提案

- §5 comb の「期待値 DP は『なぜ後ろから』・自己ループの移項・計算順序を書く」に、「選択がある状態の比較は移項した後で行う」と「mod の値で比べない」を足してよい。どちらも複数の問題（abc350_e・abc314_e）で実際につまずく点
- 動く図の置き場を先に書くとき、data-config の形を執筆者が決めてよいか（今回は仮の形にした）。決めた形を JS の担当に渡す手順があるとよい

## 動く図の仕様（priority 1、後でまとめて作る用）

- 置いた div：`<div class="kp-viz" data-viz="expected-value-dp" data-config='{"mode": "hp", "n": 4, "p": "1/2", "selfLoop": {"stay": "1/3"}}'></div>`（config の形は仮。JS の担当が決めてよい）
- 前半：HP 4〜0 の 5 状態を横に並べ、HP − 1（確率 1 − p、実線）と HP − 2（確率 p、破線。HP 1 からは HP 0 へ）の矢印を描く。HP 0 に 0 を書き、1 ステップごとに 1 状態ずつ $E[h] = 1 + pE[\max(h-2,0)] + (1-p)E[h-1]$ を当てはめて値を埋める（p = 1/2 で 0・1・1.5・2.25・2.875）。caption に式と数値を出す
- 後半：自己ループのある小さな例（たとえば、とどまる確率 1/3・1 つ先へ 1/3・2 つ先へ 1/3 のすごろく。snippets/expected-value-dp/self-loop.cpp の入力「4 / 3 2 1」と同じ形にすると数値を試験に使える：E = 2.8333…・2.5・2・0）。自分へ戻る矢印を描き、移項前の式と移項後の式を並べてから値を埋める
- catalog の visual が言うとおり、ゲームの勝敗 DP の図と部品（状態の DAG を終状態から埋める）を共有できる

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| abc326_e | サイコロを振って給料が決まる過程の、給料の期待値を mod 998244353 で求める（後ろからの期待値と累積和）。台帳で確認済みで、rational-mod の練習。prefix-sum の節の練習に足せる | https://programming-hiroba.com/abc326-e/ （台帳の evidence。本文の確認はしていない） |
| abc189_f | 振り出しに戻るマスがあるすごろくの期待値（未知数を置く）。expectation-linear-equations 側の例題候補で、このページの使い分けの裏付けになる | https://kmjp.hatenablog.jp/entry/2021/01/23/0900 （調査レポート 02 §5.1 に記載。台帳の状態は見ていない） |

abc319 以降（7 問体制）は abc350_e・abc382_e の 2 問が練習にある。例題に 7 問体制の問題はない（水の E で期待値 DP の基本形の新しい問題は見つけていない）。

## 未解決の点

- abc263_e の出力が mod 998244353 かどうかを evidence（kazun の記事）で確かめられなかった。本文の方針では「mod で答えるなら」と条件付きで書いた
- abc300_e は台帳で確認済みで、方針は台帳の approach と drken の記事の題名から書いた（記事本文は今回読んでいない）。abc266_e も台帳の approach と調査レポートの値（E_2 = 4.25）で書いた
- EDPC J の difficulty がないので、例題の中で最後（3 問目）に置いた
- 「ACL では」の囲みは独立の節にせず、落とし穴の後に置いた
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 10 回・検索 1 回
