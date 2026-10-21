# recursive-enumeration の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/recursive-enumeration.md、snippets/recursive-enumeration/partition.{cpp,yaml}・tiling.{cpp,yaml}、docs/img/recursive-enumeration/partition-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に 2 節を足した（`skeleton`「再帰の骨組み（決める・進む・戻す）」、`next-steps`「上位の手法へのつながり」。level はページと同じ）。既存の anchor は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 16。助詞の重複と文の長さ。要点の計算量の行・図の代替テキストなど、数式や列挙を含む文の長さが主）
- 図：catalog の visual（static・priority 2）の「組分けの再帰木」を SVG にした（3 人、葉 5 個。実線＝今ある組に入れる、破線＝新しい組を作る）。描画は手元で確かめられなかった（SVG 変換の道具がない）ので、検証役に表示の確認を頼みたい

## 使った出典

- drken（hatenablog）ABC161 D・ABC310 D・ABC114 C：例題 2 問の問いと方針、生成型の再帰
- oraclesqlpuzzle ABC236 D・ABC345 D・ABC390 D：練習・力試しの方針
- ikatakos ABC473 メモ（解説の部分だけ）・comet725（Qiita）ABC473 D：練習の問いと方針
- 新しく noai を確かめたドメイン：なし（どれも付録 B にある）
- 数値（ベル数 B_3〜B_13、(2N−1)!!、S(10,k)、ルンルン数の桁数ごとの個数 9 桁以下 68468・10 桁以下 199368、3+…+3^9 = 29523、ドミノの敷き詰めの数）は Python とコード片で計算して確かめた

## 台帳への提案

- abc473_d｜summary｜「重み付きの和 1×A_1 + 2×A_2 + … + N×A_N が K になる長さ N の非負整数列 A を、辞書順にすべて出力する。」｜https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0829_abc473（本文の一覧はこの文で書いた）
- abc473_d｜approach｜「A_1 から順に残りの和を超えない値を小さい順に決め、最後の A_N は残りが N で割り切れるかで決める DFS」｜同上・https://qiita.com/comet725/items/fccbb66706bb14a53b46
- abc390_d｜pages の recursive-enumeration の alternatives の summary は「グループの和の XOR」と書いているが、本文の一覧は台帳の主の summary（袋の石を移す操作の言い方）を使った。alternatives の summary を主と同じにそろえるか、どちらかに決めてほしい
- abc161_d・abc310_d・abc114_c・abc236_d・abc345_d・abc390_d｜checked｜2026-10-21（evidence の解説で問いと方針を確かめた）

## 用語集への提案

- 再帰木｜recursion-tree｜再帰関数の呼び出しの関係を木にしたもの。根が最初の呼び出し、子がそこから呼んだ呼び出しで、全列挙では葉が 1 つの候補（または枝刈りで止まった所）に当たる。（本文で `../guide/glossary.md#recursion-tree` へリンク済み）
- バックトラック｜backtracking｜状態を書き換えて再帰で先へ進み、戻るときに書き換えを元に戻しながら、選択肢を順に試す探索。（題名に近い語なので、リンクはしていない。用語集に載せるかはメインで判断）

## 手引きへの提案

- §4 の「technique（基礎）」の構成と「technique（水・青・黄）」の構成のどちらに従うかが、field が basics で level が水のページでは分かりにくい。今回は課題の指示（基礎のページは短く、応用の型・落とし穴・つながり）に従い、「必要になる場面」「処理の流れ」を独立の節にせず、骨組みの節と各型の節に含めた。basics の水のページはどちらの型か、§4 に 1 行あるとよい

## 問題の補充の候補

catalog の数（例題 2・練習 4・力試し 1）で足りているので必須ではない。abc319 以降の問題は abc345_d・abc390_d・abc473_d がある。

- abc475_d（D. Alphametic Prime、diff 741、台帳では sieve-eratosthenes の練習で確認済み）：文字に数字を割り当てる候補を DFS で全部作り、素数かを篩で判定する。生成型の練習に足せる｜https://qiita.com/comet725/items/777d32f7cf7630a48663（frequency_evidence に挙がっているのに本文にないため。summary は「（執筆時に確かめる）」のままなので、足すなら summary の確認が要る）
- typical90_bt（072. Loop Railway Plan（★4）、台帳で確認済み・complexity-estimation と dfs の練習）：経路のバックトラック。枝刈りと見積もりの節の練習に足せる｜https://github.com/E869120/kyopro_educational_90/blob/main/sol/072.cpp

## 未解決の点

- abc473_d の「辞書順にすべて出力する」は、ikatakos 氏の解説の「小さい順に試すと辞書順に出る」という記述からの推定で、出力順の指定そのものは確かめきれていない（atcoder.jp を開けないため）。検証役が別の第三者の解説で確かめてほしい
- abc345_d の制約（N・H・W の上限）は第三者の解説に書かれておらず、本文には数値を書いていない。「回転してよい」「使わないタイルがあってよい」は oraclesqlpuzzle 氏のコードの振る舞いから確かめた
- 「値で渡すとコピーの分だけ遅くなる」は倍率を書かずに定性的にとどめた
- related の `bell-number#size`・`cpp-lambda#recursive-lambda` はどちらも stub のページなので、本文では anchor なしでページへリンクした（§7）。draft になったら `#size`・`#recursive-lambda` を付けるとよい

## 使用量の目安

- 道具の呼び出し 約 25 回、Web 取得 9 回（WebFetch 8・curl で題名の確認 1 回 8 件）

## 検証の指摘への対応（2026-10-21）

- 1・2・3（直すべき）：直した。表の列を「答えになる葉の数」にし、「ちょうど T 組」の行に「枝刈りで止まった葉は別。上界は B_N」を足し、表の前に一文を足した。10N + 9 は「以下」にした。図は 1 列に葉 5 個を並べるとスマホで 10px に届かない（葉の文字幅の比から計算）ので、再帰木を左から右へ描く形に描き直した（viewBox 580×450、節点 20・凡例と説明 18 → 幅 358px で約 12px・11px）。葉の枠は 164 に広げ、凡例と説明は 2 行ずつに分けた
- 6・8・9・10・11・13・14：指摘のとおり直した（ラムダ式へのリンクは `#recursive-lambda`）
- 12：図に空の根「{ }」を足し、人 1 が新しい組を作る破線を描いた。代替テキストも合わせた
- 4・5：本文は変えない（指摘のとおり）。台帳への提案は下の追記のとおり
- 7：本文のリンクは残した。用語集に「再帰木」を足す提案は上の「用語集への提案」のとおり。足さないならリンクを外す必要がある

## 台帳への提案（検証を受けての追記）

- abc473_d｜evidence に https://www.luogu.com.cn/article/yizbvigw を足し、checked に 2026-10-21（出力が辞書順であることを検証役が確かめた）
- abc390_d｜alternatives の summary を主の summary（操作の言い方）にそろえる（検証役も同意）
