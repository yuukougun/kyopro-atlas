# b5 glossary の報告（2026-10-22）

- 書いたファイル：docs/guide/glossary.md（snippets・図はなし）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）・sections の先頭に `{title: 引き方, anchor: how-to-read}` を足した。complexity は guide なので null のまま
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0 行、textlint エラー 0・警告 12（反映前の glossary.md と同じ 12 件。どれも既存の語の項の no-doubled-joshi と、数式の括弧の誤検出）
- 使った出典：新しい Web の取得なし。数値は本文のページ（complexity-estimation の 1024 MiB・2 秒）、planning/research/00-curriculum.md §2.3（ABC の 7 問・100 分・Rated 〜1999、ペナルティ 1 回 5 分、difficulty の定義）、planning/decisions.md（レベルの帯）、style-guide 付録 A と prh.yml（対応表）
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 0 回

## したこと

1. 既存の 117 語の定義の文は変えていない（anchor もすべて残した）。並びだけを変えた
   - offline・forced-online を「手法一般」から「計算量の用語」へ移した（catalog の節の注記どおり）
   - 「手法一般」の中を、探索・DP・実装の語（state〜stable-sort）と演算の性質・操作の語（associativity〜rollback）にまとめ直した（dominance を representative の後へ、rollback を最後へ）
   - techniques・domains の節の頭に、中の並びを示す 1 文を足した
2. 前置き（要点・別名の行・導入）と「引き方」の節を書いた
3. 本文になかった節 judge・atcoder・slang・canonical-forms を書いた。judge・atcoder・slang には新しい語を置いた（下の「用語集への提案」。メインが定義を書き直す前提の案）
4. canonical-forms は、付録 A のかっこ書き（本文で使ってよい別の書き方）と prh.yml の規則（直す表記）を、分野ごとの 3 列の表にした。表記の揺れを書くので節全体を textlint から外してある（中の文は目で確かめた）

## 台帳への提案

- なし（問題を載せないページ）

## 用語集への提案

この報告と同時に本文に置いた新しい語（30）。定義の文はメインの判断で書き直してよい。採った基準は b3 の glossary-result.md と同じく、docs の grep で 3 ページ以上に出る語か、ページのない基本の語。

| 語 | anchor | 節 | 本文での出現（grep で数えたページ数の目安） |
| --- | --- | --- | --- |
| AC・WA・TLE・MLE・RE・CE | ac・wa・tle・mle・re・ce | judge | TLE 36・WA 21・RE 17・MLE 9・CE 16（部分一致） |
| テストケース | test-case | judge | 26 |
| 反例 | counterexample | judge | 14 |
| 制約 | constraints | judge | 多数 |
| 複数テストケース | multiple-test-cases | judge | complexity-estimation#multiple-testcases の語に合わせた（「多重テストケース」は本文に 0） |
| インタラクティブ | interactive | judge | 14 |
| ペナルティ | penalty | judge | AtCoder の意味では atcoder-system・contest-strategy の節名 |
| ABC・ARC・AGC | contest-types | atcoder | 多数 |
| Rated | rated | atcoder | 1 |
| レーティング（レート） | rating | atcoder | 5 |
| パフォーマンス | performance | atcoder | 6 |
| 色 | color | atcoder | レベルの名前として全体 |
| difficulty | difficulty | atcoder | 27 |
| AtCoder Problems | atcoder-problems | atcoder | 2 |
| ACL | acl | atcoder | 168 |
| Library Checker | library-checker | atcoder | 98 |
| verify | verify | atcoder | 152 |
| 典型90・EDPC・ADT | typical90・edpc・adt | atcoder | 69・34・3 |
| 精進・upsolve | shojin・upsolve | slang | 3・6 |
| 典型・考察 | typical・analysis | slang | 多数・53 |
| 想定解・愚直解 | intended-solution・naive-solution | slang | 10・27（「愚直」の部分一致） |
| 決め打ち | fix-the-answer | slang | 3（部分一致 20） |
| 略称 | abbreviations | slang | 座圧・ロリハ・UF などの読み替え。canonical-forms へつなぐ |
| 前計算 | precomputation | complexity | 25 |
| 枝刈り | pruning | techniques | 3（部分一致 12） |
| 判定問題 | decision-problem | techniques | 3（部分一致 9） |

- 見送った語（catalog の注記・research §6.10 にあり、本文で使われていない）：多重テストケース・コーナーケース・誤差ジャッジ・スペシャルジャッジ・嘘解法・やるだけ・エスパー・解説放送・バーチャル参加・擬多項式時間・空間計算量・部分点・早解き
- b2・b3 から持ち越しの heavy-vertex（重い頂点）と upper-hull（上側凸包）は、b3 の glossary-result.md で「1 ページだけ」「ページへのリンクで足りる」として見送られているので、足していない
- 新しい語へのリンクは本文のページにまだ張っていない。TLE・WA・difficulty・ACL・verify などはリンクの候補が多いので、張るかどうか（ページごとに最初の 1 回）はメインが決める

## 手引きへの提案

- 付録 A に「DSU」の扱いを決めて足す。glossary の summary は「Union-Find と DSU」を例に挙げているが、付録 A にも prh.yml にも DSU がなく、対応表に載せられなかった（案：別の書き方には入れず、ACL の `dsu` のときだけコードの名前として使う）
- 付録 A に「複数テストケース」（多重テストケースは使わない）を足す。本文は complexity-estimation の節名を含め「複数テストケース」にそろっている
- 付録 A の「尺取り法」に対し prh.yml の expected は「尺取り」、「貪欲法」に対し「貪欲」なので、対応表では付録 A の形（尺取り法・貪欲法）を正規形にした。食い違いではないが、prh の expected と付録 A のどちらを表の正とするかを §7 に一言書くとよい
- 用語集の canonical-forms を prh.yml の元にするなら、prh.yml を直したときに対応表も直す手順を §7 か progress.md に書く（今は手で写した）

## 問題の補充の候補

- なし（用語集は問題を載せない）

## 未解決の点

- ペナルティの項は「ABC では AC するまでの誤答 1 回につき 5 分」とした。根拠は research §2.3 の AtCoder Problems のスクリプトの記述だけで、CE を数えないこと・解けなかった問題の誤答を数えないことは確かめられなかったので書いていない（atcoder-system を書くときに確かめる）
- 色の項の境目は灰（〜399）・水（1200〜）・青（1600〜）・黄（2000〜）・赤（2800〜）だけを書いた。茶・緑・橙の境目も 400 刻みだが、本文には範囲を書いていない
- 典型90 の ★ の範囲（★1 からか ★2 からか）を確かめられなかったので、「★ の数で示す」とだけ書いた
- 相手のページ（atcoder-system・debugging-checklist・practice-method・problem-sets・library-design・stress-testing・term-index・cheatsheet・notation）は stub なのでページへのリンクにした。draft になったら次の節へ張り替えられる：penalty → atcoder-system#ranking、color → atcoder-system#colors、difficulty → atcoder-system#difficulty、rating・performance → atcoder-system#rating、contest-types → atcoder-system#contests、shojin → practice-method、upsolve → practice-method#upsolve、atcoder-problems → practice-method#atcoder-problems、verify → library-design#verify、adt → problem-sets#practice-contests、typical90 → problem-sets#typical90-stars、naive-solution・counterexample → stress-testing#procedure、judge の節の頭 → debugging-checklist

## 検証の指摘への対応（2026-10-22）

- 直したもの：1（ADT を「主に平日に開かれる 60 分」に）・2（ペナルティを「最終的に AC した問題の誤答だけ」に）・3（summary と要点の例を「セグ木とセグメント木、DFS と深さ優先探索など」に替えた。「最短路と最短経路」は prh が要点の中で拾うので避けた）・4（BIT を Binary Indexed Tree の略と書き分け、本文で使う略称の文を直した）・5（ウォークの行の「直す表記」を — にし、表の下に「ウォークを『歩道』とは書かない」を置いた）・6（「人名をつないだ名前と、Union-Find のような 2 語の名前」に）・7（慣用句の導入を書き分けた）・8（引き方は「1〜4 文」、要点は「数文」に）・9（「多くは質問の回数に上限があり」に）・10（「★2〜★7」を足した）
- 採らなかったもの：なし。ただし 3 は DSU の注記を足す形ではなく、例を替える形にした（DSU の扱いはメインが決めるため）。5 は prh.yml に足す形ではなく、注記に移す形にした
- 検査：check_pages エラー 0・警告 0、fix_problems --check 0 行、textlint エラー 0・警告 12（前と同じ）。snippets はなし

### 共有ファイルへの提案（指摘への対応から）

- 付録 A／対応表：DSU の扱いを決める（案：別の書き方には入れず、ACL の `dsu` を指すときだけコードの名前として使う。DSU on Tree はマージテクの別名）。決まったら対応表のデータ構造の表の下に 1 行の注記を足せる
- prh.yml：「歩道 → ウォーク」を足すかを決める（道路の意味の「歩道」とぶつからないか確かめてから）。足すなら対応表のウォークの行の「直す表記」を「歩道」に戻し、表の下の注記を消す。docs/graph/k-shortest-paths の summary 由来で lists・llms.txt に「歩道」が 3 か所ある（検証の参考）
- typical90 の ★ と difficulty の対応の目安は、problem-sets#typical90-stars へのリンクで足せる（メインがバッチの終わりに節へ張り替えるときに合わせて）
