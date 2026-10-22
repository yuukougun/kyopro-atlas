# debugging-checklist の提案（b5）

- 書いたファイル：docs/guide/debugging-checklist.md、snippets/debugging-checklist/multitest.{cpp,yaml}
- front matter で変えたもの：stage（draft）・updated（2026-10-22）・sections の並び（partial を wa の前へ。本文の順に合わせた。§14-11）。complexity は手法のページではないので null のまま
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 1：「$N$ と $M$、$i$ と $j$」の並列の「と」で誤検出）
- 図：catalog の visual（static, priority 2）の分岐図を Mermaid で本文に置いた。SVG は描いていない
- 使った出典：KACTL troubleshoot.txt（github.com、raw.githubusercontent.com も check_noai で指定なしを確認）、E869120「デバッグ力を高める！」（qiita.com）。数値は本文のページ（cpp-undefined-behavior・complexity-estimation・cpp-io）にそろえた

## 台帳への提案

- なし（このページは問題を載せていない。catalog の problems も空）

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| コーナーケース | corner-case | 見落としやすい端の入力である。$N = 1$、すべて同じ値、値が 0 や上限ちょうど、答えが存在しない場合などを指す。 |
| 多重テストケース | multiple-testcases | 1 つの入力で $T$ 個の独立なケースを与える形式である。前のケースの値を残さないように初期化し、計算量はケースの合計で見積もる。 |
| WA・TLE・RE・MLE | judge-verdicts | ジャッジの結果の略語である。WA は誤答、TLE は実行時間の超過、RE は実行中の異常終了、MLE はメモリの超過を表す。 |

本文では上の 3 語を本文中で短く定義し、リンクは張っていない（§15-1）。用語集に足したら、本文の初出（「コーナーケースと呼ぶ」「多重テストケースは、…形式である」）へのリンクを張れる。

## 手引きへの提案

- guide（案内）のページの構成の目安が §4 にない。このページは「要点 → 別名 → 導入（略語の説明と分岐図）→ 症状ごとの節（太字の見出し語つきの箇条書き、各項目の末尾に持ち主のページの節へのリンク）→ 確認問題 → 参考」とした。ほかの guide のページにも使えるなら §4 に足すとよい
- 参考の節で、自サイトのページを「数値の確かめ先」として挙げた。参考を外部の資料だけに限るなら、この行は消してよい

## 問題の補充の候補

- なし（チェックリストは問題を例にしない方が引きやすいと判断した。hub の目安は 0〜3 問）

## 未解決の点

- 誤答のペナルティ（正解した問題の誤答 1 回ごとに 5 分）は、research/00-curriculum §2.3.2 の記述（Wikipedia と AtCoder Problems の推定スクリプト）にもとづく。atcoder.jp を開けないので、細則（CE を数えるかなど）は書いていない。atcoder-system#ranking が書かれたら、その節へ張り替える
- cpp-environment・cpp-reverse-index・stress-testing・atcoder-system は stub なので、ページへのリンクにした（§14-23）。draft になったら cpp-environment#stack-depth、cpp-reverse-index#symptoms、atcoder-system#ranking へ張り替える
- 「深い再帰は 1 段ごとに局所変数の分のメモリを使う」は一般論として書いた。AtCoder でスタックの使用量がメモリの計測に入るかは確かめていない

## 検証の指摘への対応（b5 verify）

- 直すべき：0 件
- 直すとよい 6 件はすべて直した
    1. リンクの張り替え：張り替え先の anchor が作業ツリーにそろっていた（atcoder-system も draft になり #ranking がある）ので、担当ページの中で執筆者が張り替えた。atcoder-system#ranking、cpp-environment#stack-depth（2 か所）、#local-vs-judge の冒頭に cpp-environment#when-results-differ を追加、cpp-reverse-index#symptoms、stress-testing#procedure。メインの張り替えの作業は、このページについては不要
    2. 確認問題の 1 問目を「ストレステストで食い違いが出ない → 誤読を疑う、なぜか」に差し替えた（2 問目は残した）
    3. MLE の「テストケースごとの確保」を、グローバルの `vector` に `clear` せず `push_back` し続ける形に替え、上限の大きさの確保は TLE の節へ送った
    4. #before-submit・#wa・#tle の 1 文目を指摘のとおり直した
    5. #local-vs-judge の 1. に「0 から始まって AC することがあり」を足した。cpp-undefined-behavior#uninitialized の言い方とそろえるかはメインの判断に任せる
    6. Mermaid の図：WA の割合の分岐（D1・D2）を図から外して 1 つの箱にし、TLE・RE・MLE の箱の文字を `<br/>` で縦に折った。外した分岐の内容は図の後の説明文に 1 文で足した
- textlint の警告 1（122 行の「$N$ と $M$、$i$ と $j$」の並列の「と」）は誤検出のため残した
