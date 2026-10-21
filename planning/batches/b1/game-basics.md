# game-basics の報告と提案

- 書いたファイル：docs/comb/game-basics.md、snippets/game-basics/stones.{cpp,yaml}、snippets/game-basics/set-game.{cpp,yaml}、docs/img/game-basics/stones-win-lose.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直す行 0、check_snippets 2 本とも通過、textlint エラー 0・警告 12（「二人零和有限確定完全情報」の漢字の連続は用語そのもの。台帳から作る問題の行の文の長さ・読点。残りは助詞の重複で、読みにくさは小さいと判断）
- 図：visual は priority 2 の動く図（局面の DAG を終局から塗るステップ送り）だが、指示どおり動く図は作らず、静的な SVG（1・3・4 個取れる石取りの 0〜8 個の勝ち負け）で代えた。後で動く図を作るなら、勝敗の DP の節の SVG の位置に `<div class="kp-viz" data-viz="game-dag" data-config='{"moves":[1,3,4],"n":8}'></div>` を置く案（期待値 DP・後退解析の図と部品を共有）
- 新しく noai を確かめたドメイン：なし（使ったのは付録 B のドメインだけ。zenn.dev・qiita.com・programming-hiroba.com・ikatakos.com・はてなブログの drken1215・kyopro-friends・torus711）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| arc105_d | summary | N 個の袋の硬貨を交互に皿へ移し、袋が空になったら皿から 1 枚以上の硬貨を交互に取り除くゲームで、動けなくなった方が負けのとき、勝つのはどちらかを求める。 | https://drken1215.hatenablog.com/entry/2020/10/14/120100 |
| agc014_d | summary | 木の頂点を先手が白、後手が黒で交互に塗り、塗り終えた後に黒と隣り合う白を黒に変えたとき、白が残れば先手の勝ちとなるゲームで、勝つのはどちらかを求める。 | https://drken1215.hatenablog.com/entry/2019/05/30/021200 |
| abc380_f | alternatives の summary（game-basics） | 「（ルールの詳細は執筆時に確かめる）」を外す。本文は台帳の summary（2 人の手札と場のカードを使う 2 人ゲームで…）を使った | https://torus711.hatenablog.com/entry/2024/11/17/144754 |
| abc398_e | evidence | 2 つ目の kmjp の URL（2025/03/25/0930）は ABC398 G の記事で E ではない。https://zenn.dev/nakst_hide/articles/a62a21128b03af に差し替える（対戦の流れ・First / Second の選び方・終わりの合図 -1 -1 を確かめた） | https://zenn.dev/nakst_hide/articles/a62a21128b03af |
| dp_k | evidence | qiita の drken の記事（ゲームを解く！EDPC K, L）は今回読んでいない。kyopro-friends の「EDPC解説 F～L」で問いと解法を確かめた | https://kyopro-friends.hatenablog.com/entry/2019/01/12/231000 |
| abc354_e・abc398_e・dp_k・arc064_b・arc105_d・agc014_d・abc270_d・abc195_e・abc380_f | checked | 2026-10-21（evidence の解説で問いと解き方を確かめた） | 各 evidence |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| DAG | dag | 有向閉路を持たない有向グラフ（directed acyclic graph）である。頂点を辺の向きにそろえて一列に並べられるので、DP の計算順序が決まる。 |
| 局面 | game-position | ゲームの途中の様子（盤面・手札・残りの石など）と、どちらの手番かをまとめたものである。ゲームの DP では局面を状態にする。 |

本文は `../guide/glossary.md#dag` にリンクしている（局面は本文で定義したのでリンクしていない）。

## 手引きへの提案

- §13 の 6 に関連して：台帳の evidence に別の問題の記事が混ざっていた（abc398_e の kmjp）。執筆者は evidence を読んだら、記事がその問題のものかをまず確かめる、と一文足すとよい
- 本文で触れる練習・力試しの問題は「[練習の ABC195 E](#practice)」のように見出しへのリンクにした。行そのものへの anchor がないので、問題ごとに飛べる anchor（例：囲みの各行に問題 ID の id）を生成部分で付けられると、本文からの参照が正確になる

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

水のページだが abc319 以降の ABC の例題・練習は abc354_e・abc380_f・abc398_e で、要件（1 問以上）は満たす。足すなら次の候補（研究の表にあり、台帳での状態は未確認）。

| 問題 ID | 何を問うか | 役割の案 | 裏付け |
| --- | --- | --- | --- |
| tessoku_book_af | A 個か B 個取れる石取りの勝敗を、石の数ごとの勝ち負けの DP で求める | 練習（dp_k と同じ型なので、どちらか一方でもよい） | https://github.com/E869120/kyopro-tessoku/blob/main/codes/cpp/chap05/answer_A32.cpp |
| abc244_c | 1〜2N+1 を交互に言うゲームをジャッジと行い、まだ言われていない数を答え続ける | 練習（インタラクティブの節の入門。diff 165 と易しい） | https://drken1215.hatenablog.com/entry/2025/02/08/111105 |
| arc143_c | 先手は X 個、後手は Y 個ずつ取る非対称なゲームを、X+Y で割った余りと相手の手を戻す戦略で判定する | 力試し（真似戦略・手番で手が違う節。nim-variants と分け合う） | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0626_arc143#c_-_piles_of_pebbles |
| agc033_c | 木のコイン取りの勝敗が直径の長さを 3 で割った余りで決まることを示す | 力試し（総手数・不変量の節。ただし偶奇でなく mod 3 の規則の発見で、grundy-patterns 寄り） | https://drken1215.hatenablog.com/entry/2019/05/07/005700 |

## 未解決の点

- ABC398 E の頂点数の上限は第三者の解説に明記がなく（検索の要約で 100 とあったが一次確認できず）、本文では「頂点の組を全部並べても間に合う大きさ」とだけ書いた
- ABC380 F が必ず終わる理由は、torus711 氏の記事の要約に頼らず自分で確かめた（1 手で出すカード x より小さいカードしか取れないので、2 人の手札の数の合計が毎手減る）。本文はこの理由で書いた
- 真似戦略の節は level 青だが、ページの前提に symmetry-pigeonhole-casework はない（related にだけある）。節の冒頭でページへリンクした。symmetry の節（#symmetry）は相手のページが stub なのでページへのリンクにした
- memoized-recursion・dp-order・minimax など多くのリンク先がまだ stub で、節へのリンクは bit-dp#games だけ
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 約 14 回（WebFetch 12・検索 1・curl で題名の確認）
