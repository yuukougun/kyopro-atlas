# burnside-lemma の報告（b4）

- 書いたファイル：docs/comb/burnside-lemma.md、snippets/burnside-lemma/necklace.{cpp,yaml}、snippets/burnside-lemma/cube.{cpp,yaml}（cube は本文に取り込まず、立方体の回転の型と個数・k 色の塗り方を確かめるだけ。§13-9）。図はなし（catalog の visual が null。立方体の回転は表で示した）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と検証, anchor: library}` を足した
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（2 本）、textlint エラー 0・警告 11（数式や漸化式を含む文の長さ・助詞の重複の誤検出。§13-8）
- 使った出典：kmjp（ABC428 G・ABC198 F）、ikatakos（ABC428 G の解法の節だけ。ABC198 F の記事も読んだが、公式解説の第 2 の方法の実装で Burnside の型分けの説明がないので出典にしていない）、scrapbox.io/pctsnote「バーンサイドの補題」（ABC198 F の型分け）、ja.wikipedia、cp-algorithms（文章・図は使っていない）、GitHub の library-checker-problems の一覧
- 新しく noai を確かめたドメイン：scrapbox.io/pctsnote（`tools/check_noai.py` で noai・noimageai の指定なし。付録 B の scrapbox.io の確かめたプロジェクトに pctsnote を足す提案）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc428_g | summary | 美しさの決まった何種類かの宝石を何個でも使って輪のネックレスを作るとき、美しさの積が x になるもの（回転で一致するものは同じ、裏返しは区別）の数を、2 以上 U 以下の各 x について求める。 | https://kmjp.hatenablog.jp/entry/2025/10/18/0900 ・ https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/1018_abc428 |
| abc428_g | evidence | 上の 2 件（ikatakos を追加） | 同上 |
| abc428_g | approach | 長さと積ごとの列の数を DP で求め、最短周期で分類して周期の長さで割る（Burnside の式でも同じ形になる） | 同上。Burnside の形は本文の解法の詳細で導いた |
| abc428_g・abc198_f | checked | 2026-10-22 | — |
| abc198_f | evidence | https://scrapbox.io/pctsnote/%E3%83%90%E3%83%BC%E3%83%B3%E3%82%B5%E3%82%A4%E3%83%89%E3%81%AE%E8%A3%9C%E9%A1%8C を追加（型を 5 つに分け 2x+2y+2z=S などを母関数で数える） | 同 URL |

本文の例題の行は fix_problems で label・URL・diff を埋め、abc428_g は自分の要約を残している。台帳の summary を直したら fix_problems を流してよい（同じ文）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 軌道 | orbit | 同一視に使う操作の集合 G があるとき、x に G の操作を施して得られるものをすべて集めた集合。同一視した後の 1 種類が 1 つの軌道にあたる。Burnside の補題は軌道の数を数える。 |

本文では「軌道」を太字で定義し、リンクは張っていない（§15-1）。用語集に足したら、#what の最初の「軌道」にリンクを張れる。付録 A（数え上げ）に「軌道」「Burnside の補題」を足すかも検討してほしい。

## 手引きへの提案

- 発展の概要のページで Library Checker に対応する問題がない場合の書き方（「対応する問題はない。全列挙と比べて確かめる」と書いた）を §13-10 に一言足すとよい
- 群・環・体の語を使わない規則（§5 math）は comb にも当てはめた。「群」と言わずに操作の集合の条件（合成・恒等・逆）を言葉で書いた。comb にも明記するか判断してほしい

## 問題の補充の候補

例題は台帳の 2 問で足りている（発展は 0〜2）。練習の候補は探したが、第三者の解説で裏付けられた ABC の問題を見つけられなかった（ap.py の題名検索 Necklace・Bracelet・Cube・Rotation・Circular などで、abc428_g・abc198_f のほかに当たったのは abc252_h（Ex. K-th beautiful Necklace、diff 3015）だけ。題名だけでは回転の同一視を問うかが分からず、第三者の解説で裏付けを取っていないので候補にしない）。補充は不要と考える。

## 未解決の点

- ABC198 F の S の上限（10^18 程度）は ikatakos の記事の計算量の記述と kmjp のコードからの推定で、本文には「S が大きい」とだけ書いた
- ABC428 G の「美しさが 2 以上」は kmjp・ikatakos の記述（長さが log2 U 程度になる理由）による。問題文は見ていない
- euler-phi のページは本ページを「バーンサイドの補題」と書いている（docs/math/euler-phi.md の応用の型）。題名の「Burnside の補題」にそろえる直しを提案する
- counting-basics:91・191、counting-dedup:63・226・245、divisor-inclusion-exclusion:150 は本ページへのリンク（ページ単位）。本ページが draft になったので、counting-basics:91 は #necklace（色の個数が決まった例）、divisor-inclusion-exclusion:150 は #by-period、euler-phi の式は #necklace へ張り替えられる

## 検証の指摘への対応（2026-10-22）

- 指摘 1（直すべき）：リンクを counting-basics#permutations（円順列の落とし穴）に張り替え、リンクの文字も合わせた
- 指摘 2：#why-not-divide の中で Stab(x) を一言定義し、#what の証明を指した
- 指摘 3：多項係数を $c!/\prod_i (a_i/L)!$ の式で書き、回転では巡回の長さがすべて同じことを明記。赤 2 青 2 での確かめ（2）を添えた
- 指摘 4：$\binom{S-1}{5}$ は 5 個の積に $5!$ の逆元を掛ければ求まると直した
- 指摘 5：kmjp（ABC428 G）・ikatakos の題名を h1 にそろえた
- 指摘 6：確認問題を `## 確認問題 {#quiz}`（落とし穴の前）に移し、条件を変えた問いを 2 つ足した（6 個 2 色で 14、裏返しも含めた 5 個 3 色で 39。どちらも手計算で確かめた）
- 採らなかったもの：なし
- 共有ファイルへの提案（追加）：counting-basics:91 から本ページへのリンクは #necklace（「色の個数が決まっている」の段落）に張り替えると、両方向の参照がそろう（検証の「未解決の点 4」と同じ）
