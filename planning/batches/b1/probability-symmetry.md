# probability-symmetry（対称性で確率を求める）の報告と提案

- 書いたファイル：docs/comb/probability-symmetry.md、snippets/probability-symmetry/two-states.{cpp,yaml}、docs/img/probability-symmetry/two-states.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（0 行）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 12）
  - 残した警告：数式を含む文の長さ（要点の囲みの summary、図の代替テキスト、問題の行、方針の行）、signs の文字列「ランダムに 2 つを選んで入れ替える操作を K 回行う」の助詞「に」の重複（front matter の signs のまま）、ABC464 F の方針の `$[X - A_i, X)$` の括弧の対応（半開区間の誤検出）
- 図：静的な SVG を 1 枚（visual は priority 3 なので動く図は作っていない）。描画の道具が手元になく、目視の確認はしていない（XML としては正しい）。メインのビルドで一度見てほしい
- 使った出典：programming-hiroba.com/abc360-e/（ABC360 E）、kmjp.hatenablog.jp の ABC473・ABC268、ikatakos.com の ABC473・ABC464（解法の節だけ）、drken1215.hatenablog.com の ABC380 G、merom686.hatenablog.com の ABC268。どれも付録 B にあるドメインで、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc473_g | summary | 1〜N が書かれた N 枚のカードが一様ランダムに伏せて並び、カードを 1 枚めくっては次に取り除く値なら取り除き、違えば戻す（見た値は覚えている）操作で 1 から順に取り除くとき、最適にめくってちょうど K 回ですべて取り除ける確率を求める。 | https://kmjp.hatenablog.jp/entry/2026/08/29/0900 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0829_abc473 |
| abc473_g | approach（probability-symmetry 向け） | どこをめくっても出る値はまだ見ていない値から一様なので、山を上から順にめくると考え、外れの回数の分布を ∏(1/n + (n−1)/n x) の係数として分割統治の NTT で求める | 同上（kmjp は多項式の積、ikatakos は挿入 DP から (x + i − 1) の積） |
| abc473_g | checked | 2026-10-21 | 同上 |
| abc360_e | checked | 2026-10-21 | https://programming-hiroba.com/abc360-e/ |
| abc268_g | checked | 2026-10-21（「N 個の文字列は相異なる」を summary に足してもよい） | https://kmjp.hatenablog.jp/entry/2022/09/10/0900 |

- abc473_g の本文の行は、上の summary を自分で書いて置いた（fix_problems は本文の summary を残すので、台帳を直せば一致する）
- abc473_g の summary は 2 つの解説から再構成したもので、「最適に」の意味（場所が分かっている値はすぐ取る）は解説の記述からの推定である。検証役に確かめてほしい

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 一様ランダムな順列 | uniform-random-permutation | $N$ 個の並べ方 $N!$ 通りのそれぞれが確率 $1/N!$ で選ばれる順列。残りから一様に 1 つずつ選んでいく過程で選ばれる順もこの分布になる |

（本文からはリンクしていない。必要なら最初の出現にリンクを足す）

## 手引きへの提案

- 確率・期待値のページの例題で、問題の「a = b を許すか」「復元抽出か」のような、遷移確率を左右する設定を要約にどこまで書くかの目安があるとよい（台帳の summary は短く、本文の解法で補った）
- SVG を確かめる描画の道具（rsvg-convert など）が執筆の環境にない。目視の確認を誰が行うかを決めておくとよい

## 問題の補充の候補

- 例題 1・練習 2・力試し 2 で数の目安を満たし、abc319 以降も ABC360 E・ABC473 G・ABC464 F があるので、今回は探していない
- 型として欲しいもの（未調査）：「残りから一様に選ぶ」を順列に置き換えるだけで解ける水〜青の E（AGC049 A は linearity-of-expectation の練習にある。このページの練習に足してもよい）

## 未解決の点

- ABC360 E の制約（N・K の上限）は解説から確かめられなかった。本文では O(K) と閉じた式 O(log K) の両方を書き、制約に依存する記述は避けた
- ABC268 G の制約も解説から確かめていない（本文は O(文字列の長さの和) の Trie に触れるだけ）
- linearity-of-expectation#pairs と内容が重なる（ランダムな順列の転倒数・区間のシャッフル）。こちらはペアの 1/2 の理由と、位置以外の対称性（文字の順序）に絞り、転倒数は向こうへリンクした
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 7 回
