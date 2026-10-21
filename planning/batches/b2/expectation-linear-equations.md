# expectation-linear-equations（閉路のある期待値）の報告

- 書いたファイル：docs/comb/expectation-linear-equations.md、snippets/expectation-linear-equations/restart.{cpp,yaml}・ring.{cpp,yaml}、docs/img/expectation-linear-equations/restart-axb.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 2 件とも一致／textlint エラー 0（警告 19。要点の signs の行・数式を含む文の長さ・折りたたみの中の箇条書きで、§13-8・§14-25 の範囲）
- 図：restart-axb.svg を render_svg.py で 360px・720px にして目で確かめた
- 動く図：作っていない（visual は priority 2 で static。静的な SVG 1 枚で代えた）

## 使った出典

- https://drken1215.hatenablog.com/entry/2024/03/17/233040 ：arc174_c の問いと、包除原理＋等比級数の解き方（別解として本文に書いた）。本文の主な解き方（段ごとに等比級数で閉じ、先手から始まる確率を前向きに運ぶ）は自分で導き、スクラッチの Python で有限回の分布の反復と N ≤ 6 で一致を確かめた
- https://kmjp.hatenablog.jp/entry/2021/01/23/0900 ：abc189_f。仮定して二分探索する解き方・累積和・戻るマスが M 個続くと -1。a + bX の解き方は記事にはなく、研究レポートと本文の一般論で書いた
- https://kmjp.hatenablog.jp/entry/2021/10/26/0900 ：abc224_g。振り直す範囲 x を決めて式にし、凸性で最小を探す
- abc333_f：台帳の evidence の ikatakos.com が 503 で読めなかった（2 回）。kmjp は abc333 F の記事がない。問いは台帳の summary どおりとして、漸化式は自分で立て、Fraction の厳密計算と列の分布の直接の反復（N ≤ 5）で一致を確かめた。参考には載せていない
- 新しく noai を確かめたドメイン：なし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc189_f | approach | 「スタートの期待値を X とおいて各マスを a + bX の形で後ろから求め、X = a + bX を解く（X を仮定して二分探索してもよい）」 | kmjp の記事は二分探索の解き方なので、evidence の記事と approach をそろえる |
| abc333_f | evidence | ikatakos 以外の第三者の解説を足す（今回は見つからなかった） | 503 で読めず、裏付けが自分の検算だけになった |
| arc174_c | approach | 「段ごとに手番が交互に入れ替わってとどまる分を等比級数（または 2 未知数の方程式）で閉じ、先手から始まる確率を前向きに運ぶ（包除原理で回ごとの確率を出して等比級数で足してもよい）」 | evidence の drken の記事は包除原理＋等比級数 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 吸収マルコフ連鎖 | absorbing-markov-chain | 次の状態が今の状態だけで確率的に決まる過程（マルコフ連鎖）のうち、入ると出ない状態（吸収状態）を持ち、どの状態からも確率 1 で吸収状態に着くもの。終わるまでの期待値は (I − P)E = c の連立一次方程式の解になる |

本文では用語集へリンクしていない（語の説明を本文に書いた）。足したらメインがリンクを張ってよい。

## 手引きへの提案

- §5 comb に「閉路のある期待値は、戻る先の状態を (0, 1)、終状態を (0, 0) とする a + bX の組で書く。b = 1（終わらない）は値ではなく到達可能性で判定する」を足す案。expected-value-dp・optimal-strategy-expectation とも関わる
- 台帳の evidence が ikatakos だけの問題は、サイトが落ちていると裏付けが取れない。evidence を 2 つ持つのが望ましい

## 問題の補充の候補

catalog の problems_note のとおり、練習は abc189_f の 1 問だけで、水・青の目安（abc319 以降を 1 問以上）を満たしていない。候補を探したが、第三者の解説で裏付けられたものは見つからなかった。

| 問題 ID | 何を問うか | 裏付け |
| --- | --- | --- |
| （なし） | — | WebSearch（「ABC 期待値 未知数 一次式」「期待値 掃き出し法 連立一次方程式 ABC」など）で、閉路のある期待値の ABC の解説は見つからなかった。ap.py は題名の検索しかできず、内容からは探せない |

メインで、research の 02・07 の調査役か次のバッチの調査で、abc319 以降の「振り出しに戻る・円環・連立方程式」の期待値の問題を探してほしい。

## 未解決の点

- abc333_f の第三者の解説を読めていない（上記）。本文の解き方は自分の検算だけに基づく
- related の optimal-strategy-expectation#guess-answer は相手が stub なので、本文では anchor なしでページにリンクした（§14-23）。gaussian-elimination も stub なので同じ
- 本文の「一般の連立方程式」の節で、mod p の掃き出しで行の入れ替えが要ることに触れた。持ち主は gaussian-elimination（mod-p の節）なので、そちらとの重複はメインの判断に任せる
- 期待値 DP のページ（expected-value-dp）の確認問題に同じコインの例（表が 2 回続くまで、答え 6）がある。本文の図はこの例を a + bX の形で解き直したもので、重複は意図したもの（前提のページの続きとして読める）
- expected-value-dp・memoized-recursion・dp-order からこのページへのリンクは、相手が draft になったので節（#cycle・#unknown など）へ張り替えられる（handoff の 3 か所）

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 約 8 回（うち 503 が 2 回）、検索 6 回

## 検証の指摘への対応（b2 の直し）

- 1〜9 はすべて直した
  - 1：#infinite の「mod のとき」を「mod の値で言えるのは『1 でない』側だけ」に書き直した
  - 2：restart.cpp の判定を `p == 0`（表の遷移がない＝終状態に着けない）に替え、`b == 1` の比較を消した。関数は `(k, p, q)` を受け取る。入力の制約に `Q < 998244353` を足して assert した。case「2 5 5 → 2」を足した。ACL の囲みも「終状態に着けるかで判定する」に直した
  - 3：ring.yaml の N=2・N=5 を外し、N=4・N=6 に替えた（値は Fraction の連立方程式を掃き出す別の Python で出した）
  - 4・5・7・9：文を直した。5 は R の 1 次方程式と、S の位置による答えを足した
  - 6：#linear-system の最後の段落を 1 文に縮め、`gaussian-elimination.md#mod-p` へ張った。151 行目の「解き方は掃き出し法」は実数・mod の両方を指すので、節でなくページへのリンクのまま残した
  - 8：図の viewBox を 640 から 540 に詰め、下の説明文 2 行を 1 行にまとめた。360px で文字は約 10px（render_svg で目視）
