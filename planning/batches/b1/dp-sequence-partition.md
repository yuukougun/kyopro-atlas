# dp-sequence-partition（区間分割 DP）の報告と提案

- 書いたファイル：docs/dp/dp-sequence-partition.md、snippets/dp-sequence-partition/sum-at-most-k.{cpp,yaml}、docs/img/dp-sequence-partition/last-block.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。節は足していない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0・警告 35。数式を含む文の長さ・`[` の対応・読点の数・助詞の重複で、ほとんどが数式や表の中の誤検出）
- 図：catalog の visual は priority 2（静的）なので SVG を 1 枚（仕切りの図と、dp[6] に足し込まれる dp[j] の範囲の帯）。動く図は作っていない。SVG はレンダラがなく目視の確認をしていない（座標で重なりがないように配置した）
- 使った出典：drken（AGC031 B・ABC207 E・ARC104 C・ARC065 C）、E869120 の GitHub（典型90 089 の解説画像 editorial/089-01〜04.jpg とsol/089-05.cpp を gh api で取得）、emtubasa.hateblo.jp、scrapbox.io/kani（ABC370 E）、www.cnblogs.com/superl61（ABC370 E。本文の参考には入れていない）
- 新しく noai を確かめたドメイン：emtubasa.hateblo.jp・scrapbox.io（どちらも noai・noimageai の指定なし。check_noai.py で確認）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc207_e | summary（dp-sequence-partition の alternatives。dp-prefix-sum 側も同じ） | 数列をいくつかの区間に区切り、各区間の和が、左から数えたその区間の番号で割り切れるようにする方法の数を求める。 | 元の「k 番目」が prh で `K 番目` に直されエラーになる（意味が変わるので大文字にできない）。本文はこの文で書いた。fix_problems は本文の要約を保つので、台帳を直さないと次に作り直したとき食い違う |
| agc031_b | approach | 最後の塊の左端を直前の同じ色の位置に限り、遷移元を 2 つにする（隣が同じ色なら塗らない場合と同じなので除く） | https://drken1215.hatenablog.com/entry/2019/03/17/130800 （小さい列の全探索で漸化式を確かめた） |
| typical90_ck | evidence | https://github.com/E869120/kyopro_educational_90/blob/main/sol/089-05.cpp を足す（emtubasa の記事は方針の一言だけ） | 作者のサンプルコード |
| arc104_c | evidence の補足 | 判定の落とし穴（片方だけ分かっている人の位置）が書かれている | 同 URL |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 半開区間 | half-open-interval | （既存の提案と同じなら不要）左端を含み右端を含まない区間 $[l, r)$。長さが $r - l$ で、空区間を $[l, l)$ と書ける |

本文では glossary#half-open-interval・glossary#state にリンクした（どちらもほかのページで使われている anchor）。

## 手引きへの提案

- §13.7 の補足：台帳の summary が prh に引っかかり、直すと意味が変わる場合（`k 番目` のように番号が変数）は、変数を使わない言い回しに書き換えて本文に置き、台帳の直しを提案する、と明記するとよい
- §8：SVG を確かめるレンダラ（rsvg-convert など）が環境にないので、目視の確認ができない。tools に SVG を PNG にする手段があると検証役も助かる

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc370_e（E. Avoid K Partition、diff 1453、2024-09-07。ap.py で確認） | 数列を連続する区間に区切る方法のうち、和がちょうど K になる区間を含まないものの数を求める（mod 998244353。A_i と K は負もありうる） | 例題（水・abc319 以降・E の位置。representative の agc031_b より素直な代表）。最後の区間で分け、全体の和から「累積和の値が S_i − K の j の dp の和」を連想配列で引く。本文の two-pointers 節の「除く j が値で決まる」の型を ID なしで書いてある | https://scrapbox.io/kani/ABC370_-_E_-_Avoid_K_Partition ・ https://www.cnblogs.com/superl61/p/18523419 |

research の 02-dp §5 末尾で abc370_e は「解説で手法を確認できなかったので外した」とあるが、上の 2 つの第三者の解説で区間分割 DP（全体から引く遷移）だと確かめた。台帳に足すなら、本文の two-pointers 節の箇条書き「除く j が値で決まる」をこの問題の例題の見出しへのリンクにし、例題を 2 問（abc370_e → agc031_b）にするとよい。

## 未解決の点

- 例題 agc031_b（representative）は、遷移元を 1〜2 個に絞る重複回避が主役で、「最後の区間で分ける」の素直な代表ではない。abc370_e を例題に足し、agc031_b は 2 問目にする案を推す
- level_evidence に「abc319 以降の根拠は見つかっていない」とあるが、abc370_e（1453）が水の根拠になる
- 参考に ABC370 E の第三者の解説（scrapbox）を入れたが、台帳にない問題名が参考の題名に出る。§13.6 は本文で ID を出さないことを求めているので、参考の題名も避けるべきなら、台帳に足すまで参考から外す
- 典型90 089 の制約（N の上限）は解説画像とサンプルコードの配列の大きさから見積もった（本文には N の上限を書いていない）
- 使用量の目安：道具の呼び出し約 35 回、Web 取得 9 回（WebFetch 7・WebSearch 3・gh api と curl の取得を含む）

## 検証の指摘への対応（2026-10-21）

- 1（直すべき）：典型90 089 の方針を「区間を縮めても転倒数は増えないので」に直した
- 2：front matter の complexity と要点の計算量に「余りごとの和の表で遷移をまとめると」を添えた
- 3：#block-index の区間の個数を $L$ にそろえ（$\mathrm{dp}[N][L]$・$O(LN^2)$・「$L$ 倍」）、156 行の添字を $\mathrm{dp}[i][k]$・$\mathrm{dp}[j][k-1]$ の順に直した
- 4：#two-pointers の箇条と確認問題「和が K 以上」に「$K \ge 1$」を添えた
- 5：ARC065 C の方針を、遷移元の位置 3 か所（長さ 5 の単語が 2 つ）と単語の照合に分けて書いた
- 6：#agc031_b の方針の冒頭に、塊が重ならない理由（色の違う交差は両方行えない・同じ色の交差は 1 つにまとまる）を自分の言葉で足した
- 8：last-block.svg の下段に「点線はまだ求めていない」を小さく添え、代替テキストにも一言足した
- 7（採らなかった・メインの判断待ち）：abc370_e を台帳に足すかはメインが決めることなので、参考の行はそのまま残した。足すなら 126 行の箇条を例題へのリンクにする。足さないなら参考の最後の行（かに「ABC370 - E - Avoid K Partition」）を外す。どちらも本文の直しは 1 行で済む

## 台帳への提案（検証の指摘から追加）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc207_e | approach | 区間の番号ごとに余りの累積を持つ（節 block-index）。今は存在しない anchor `by-remainder` を指している | ページの sections の anchor は block-index |
| agc031_b・abc207_e・arc104_c | checked | 2026-10-21 | 検証役が drken の解説と全探索で確かめた |
