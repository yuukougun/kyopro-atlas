# suffix-array（Suffix Array と LCP 配列）

- 書いたファイル：docs/string/suffix-array.md、snippets/suffix-array/{usage,lcp-rmq,pattern-count,lcp-sum,multi-string,rotations,doubling}.{cpp,yaml}、docs/img/suffix-array/banana.svg
- front matter で変えたもの：complexity・stage（draft）・updated、sections の concat-separator の title を「複数の文字列を連結するときの区切り（int の列と大きな値）」に変更（anchor は同じ。理由：見出しの `vector<int>` の `<int>` が生の HTML タグとして出力され、ブラウザで消えるため。手引き §13.2 により見出しと title をそろえた）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（7 本・期待と違う 0。別に乱択の小さい入力 300 組で素朴解との一致を確かめた）、textlint（エラー 0、警告 27。数式を含む文の長さ・読点、半開区間 `[l, r)` による括弧の対応、確認問題の `abab（0）` の英字の誤検出）。mkdocs build --strict はこのページ由来の警告なし（ほかのページの用語集の anchor の警告で止まる）
- 使った出典：ACL document_ja（string.md・appendix.md、手元の v1.6）、drken1215.hatenablog.com（practice2_i・abc213_f）、ikatakos.com（abc362_g・abc433_g・abc452_g、解法の部分だけ）、merom686.hatenablog.com（abc272_f）。新しく noai を確かめたドメインなし（すべて付録 B にある）
- 動く図：catalog の visual は priority 2（static）なので、静的な SVG（banana の表と LCP の棒）で作った。動く図の div は置いていない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc452_g | summary | 「数列の連続部分列のうち、各値 c が長さちょうど c の連続として並ぶ形のものの種類数を求める。」のように問いを具体的にする（今の「条件を満たす連続部分列の種類数を求める。」では何を数えるかが分からない）。条件の言い方は問題文で確かめられないため、メインで ikatakos 氏の記録の解法の節（l < c・l = c・l > c の塊の分類）と照らして決めてほしい | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0404_abc452 |
| abc213_f | summary | 「各 i について、すべての j にわたる LCP(S[i:], S[j:]) の和を求める。」（j が全体を動くこと、自分自身も含むことを明示） | https://drken1215.hatenablog.com/entry/2021/08/12/012000 （答えに自分自身との LCP N − sa[k] を足している） |
| abc213_f・abc362_g・abc272_f・practice2_i | checked | 2026-10-21（evidence の解説で問いと方針を確かめた） | 各 evidence |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 最長共通接頭辞（LCP） | longest-common-prefix | 2 つの文字列の先頭から一致する部分のうち最も長いもの、またはその長さ。Z-algorithm・Trie・Suffix Array で使う |
| 接尾辞 | suffix | 文字列の末尾を含む部分文字列。長さ N の文字列 S には、位置 p から始まる S[p, N) が N 個ある |

## 手引きへの提案

- §2.3 か §6 に「見出しと sections の title に `<` `>` を書かない（`vector<int>` は生の HTML タグとして消える）。本文ではコード `` `vector<int>` `` にする」を足す
- 骨格の level と指示の level が食い違うことがある（下の未解決の点）。指示を作るときは front matter の level を写すとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc280_h（Ex. Substring Sort、diff 3307、ap.py で確認） | 複数の文字列の全部分文字列を重複込みで辞書順に並べたときの K 番目を、複数の K について答える。SA と LCP 配列で数える（発展の節 kth-substring の代表） | 力試し（kth-substring の節） | https://drken1215.hatenablog.com/entry/2023/01/02/070100 （planning/research/08-string-geo.md の表にあるが、本文の執筆では開いていない。採るなら解説で問いを確かめてから台帳へ） |

- 水・青の例題（ACL を呼ぶだけで解ける ABC の E・F）は台帳にない。abc362_g（1625）が最も易しいが、例題は aho-corasick が持つ

## 未解決の点

- 指示はレベルを「水」としていたが、骨格と catalog の level は「黄」（level_evidence に「水・青にまとまっていないので黄のまま」とある）。執筆者は level を変えられないので黄のまま書き、導入に「ACL を呼ぶだけで水色のうちから使える」と注記した（catalog の level_evidence の指示どおり）。節 kth-substring は発展のまま
- 節 kth-substring の重複込みの場合（abc280_h の型）は「LCP の小さい位置で SA を区切る再帰」と短く触れただけで、手順は書いていない。問題を台帳に足すなら手順を厚くしたい
- abc433_g の方針は ikatakos 氏の記録の解法の要約に基づく（伸ばせない接尾辞だけを残す・LCP の大きい順にまとめる）。細部（どの接尾辞を落とすか）は方針の折りたたみに書いていない
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 6 回

## 検証の指摘への対応（2026-10-21）

直すべき 0 件。直すとよい 9 件はすべて採った。

1. 図：棒の列を表のすぐ右（x = 330）へ寄せ、viewBox を 700×414 から 580×364 にした（スマホで約 0.62 倍）。見出しの文字を 12 から 13 にした。下の説明は「斜線と白の意味」と「破線の min = 1」の短い 2 行にし、式の行は本文に任せた。和文の見え方は描画環境がなく確かめていない
2. ABC452 G の方針に「使える塊は長さちょうど（値と同じ長さ）で並ぶので、各塊を値の 1 文字に置き換えてよい」を足した。台帳の abc452_g の summary の具体化は、前の提案のとおり（メインで反映を）
3. #rotations に、回転でない接尾辞（位置 N〜2N−1・3N 以降）は数えない旨を足した
4. Kasai 法に h ≥ 1 の場合分けと、間の接尾辞も同じ h−1 文字を持つ（#lcp-rmq）という橋を足した
5. 区切りの言い過ぎを「区切りが少なければ使わない文字で足りるが、文字列の数が多い（数百を超えうる）と足りないので vector<int>」に直した
6. 基数ソートの値の範囲を「−1 以上 max(N, 256) 未満（−1 は 1 つずらす）」に直した
7. #distinct-substrings と #kth-substring に「i = 0 では lcp[−1] = 0 とする」を足した
8. 見出しと sections の title を「lcp の長さは N−1」にそろえた（anchor は変えていない）
9. pattern-count.cpp の条件演算子への代入を if/else にした（basics/binary-search の meguru.cpp と同じ書き方）

検査：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 7 片・期待と違う 0、textlint エラー 0（警告 28。足した文の長さによるもので手引き §13.8 の許容の範囲）。
