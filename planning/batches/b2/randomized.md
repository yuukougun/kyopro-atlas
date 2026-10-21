# randomized の報告（b2）

- 書いたファイル：docs/misc/randomized.md、snippets/randomized/majority-vote.{cpp,yaml}（範囲 core）、snippets/randomized/random-pair.{cpp,yaml}（範囲 core）、snippets/randomized/color-coding.{cpp,yaml}（範囲 core。総当たりと assert で照合）、docs/img/randomized/failure-probability.svg、docs/img/randomized/boyer-moore.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 本とも一致、textlint エラー 0・警告 12（要点の summary 由来の「が」の重複、数式を含む文の長さ・読点、`$[l, r)$` の括弧の対の誤検出、図の代替テキストの長さ）。SVG は render_svg.py の 360px・720px で目視した
- 数値（(1−p)^k が 10^-9 以下になる k：30・73・1316、(3/4)^100 ≈ 3.2×10^-13、(63/64)^120 ≈ 0.15、6!/6^6 ≈ 1/65、4!/4^4 = 3/32）は Python で計算して確かめた
- ABC447 G の力試しの方針（ジャンルを 2 色に塗り、中央の 2 問を色 1、外側の 4 問を色 0 に限る。成功確率 2^-6）は、自分で組み立てた方法を総当たりと比べる Python の試験（ランダムな小さい入力 300 個）で確かめた。evidence の解説では確かめていない（未解決の点を参照）
- 使った出典：en.wikipedia.org（Boyer–Moore majority vote algorithm・Freivalds' algorithm）、merom686（ABC422・ABC272）、qiita.com（bfs・gotoki_no_joe の ABC422）、kmjp.hatenablog.jp（ABC447 G の問いの確認）。どれも付録 B のドメイン。atcoder.jp・codeforces.com は開いていない
- 動く図：catalog の visual は priority 2 の static なので、静的な SVG 2 枚で代えた（div は置いていない）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc447_g | summary | 番号順に 6 問を選び、前の 4 問のジャンルが互いに異なり、後ろの 4 問のジャンルも互いに異なるようにして、面白さの和を最大にする。 | https://kmjp.hatenablog.jp/entry/2026/02/28/0900 |
| abc447_g | evidence | kmjp の記事を足す（ikatakos の記録は 2026-10-21 にメンテナンス中で読めなかった） | https://kmjp.hatenablog.jp/entry/2026/02/28/0900 |
| abc422_e | evidence | qiita の 2 件を足す（乱択の手順と決定的な分割統治の解法） | https://qiita.com/bfs/items/a9f3d319fd5cb371de5d 、https://qiita.com/gotoki_no_joe/items/7f564f443dbfc0f678f4 |

- abc422_e・abc272_g・abc339_f・abc238_g の summary は変更なし（本文の行は台帳と一致）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 片側誤り | one-sided-error | 乱択アルゴリズムで、2 つの答えのうち片方だけが誤りうる性質。例えば「ある」と答えるときは確かめてあり必ず正しく、「ない」と答えるときだけ確率的に誤る。誤る側が分かっていれば、繰り返して誤りの確率を下げられる |

（本文では語だけを書き、リンクは張っていない。足したら monte-carlo-las-vegas の節の最初の出現にリンクを張れる）

- 付録 A に「モンテカルロ法」「ラスベガス法」「Color Coding」「Boyer-Moore の投票」を足すとよい（見出しで使っている）

## 手引きへの提案

- §13-5 は「用語集へのリンクはまだなくても書いてよい」とあるが、check_pages は用語集にない anchor をエラーにする。どちらかにそろえるとよい（今回はリンクを外して語だけを書いた）

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- 例題 2・練習 2・力試し 1 で目安を満たすので、必須の補充はない
- 区間の過半数（セグメント木に (候補, 個数) を載せる型）と、Freivalds の行列積の検査の ABC の例は探しきれなかった。見つかれば練習に足したい
- level_evidence にある abc455_g（3092、乱択ハッシュ）は、hashing-for-sets の参考に挙がっているが、本ページの力試しにするかは内容を確かめていない

## 未解決の点

- ABC447 G の公式の想定解が Color Coding かどうか、成功確率 1/64 の塗り方が想定と同じかは、evidence（ikatakos の記録）がメンテナンス中で確かめられなかった。研究ノートの「解説では 1/64」と自分の組み立てた方法の確率は一致する。kmjp の解法は候補を上位 30 個に絞る別の方法だった。検証役が ikatakos の記録（解説の部分だけ）で確かめるとよい
- ABC422 E・ABC272 G の制約（N の上限など）は第三者の解説に書かれておらず、本文では N の具体的な値を書かなかった。ABC272 G の「値の差が 10^9 程度なら」は仮定の形で書いた
- hash-safety・circle-geometry は stub なので anchor なしでリンクした（related の hash-safety#what-to-randomize・circle-geometry#min-enclosing-circle へは、draft になったら張り替える）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜10 はすべて直した（1：complexity と要点を「83 回。正確に解けば 73 回」に、2：本文のサインを $K \le 6$〜$7$ にして回数と手間の増え方を 1 文足した、3：回数を $(K^K/K!) \ln(1/\delta)$ に、4・5：落とし穴を書き換え、6：hash-safety#what-to-randomize・circle-geometry#min-enclosing-circle へ張り替え、7：「頂点の重みの和」に、8：failure-probability.svg の文字を 17〜18 に上げ、p = 1/64 のラベルを短くした、9：1316 回 × $O(N)$ の見積もりを仮定の形（$N = 10^5$ なら）で 1 文足した、10：係数が $10^{18}$ に収まる旨を足した）
- 採らなかったもの：なし。ただし指摘 2 のうち front matter の signs と要点の「いつ使うか」2 つ目は、執筆者が変えられない項目なので下の提案にした（要点は signs と食い違わせないため $K \le 10$ のまま）

## メインへの提案（検証のあと）

- signs の 2 つ目と要点の「いつ使うか」2 つ目を「$K \le 7$ 程度の少数の要素を選ぶ条件で、要素の種類が多い」に変える（K = 10 では 1 回の成功確率が約 1/2756 で、δ = 10^-9 に約 57000 回 × 2^10 が要る。検証役の計算）
- 台帳：abc422_e・abc272_g の checked を 2026-10-21 に（検証役が第三者の記事で方針を確かめた）。abc447_g の checked は ikatakos の記録が読めるまで null のまま
- ABC447 G の方針は検証役の総当たりの試験で正しい（成功確率 1/64）と確かめたが、公式の想定解との一致と N の上限は未確認のまま
