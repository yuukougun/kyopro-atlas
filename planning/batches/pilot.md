# バッチ：試作（工程7）

執筆者の報告からの、共有ファイルへの提案と手引きの改善点。バッチの終わりにメインが反映する。

## bracket-sequence（約8,000字、図1）

- 台帳：abc454_d の summary の書き直し、abc407_e の summary の「( を」→「`(` を」
- 用語集：「正しい括弧列｜balanced-parentheses｜…」
- 手引き：pattern の表の置き場（sections の扱い）、例題・練習・参考を sections に入れるか、textlint が $…$ 内の括弧を検査する（半開区間で警告）
- 未解決：abc454_d の操作の向き

## hld（約7,400字、図1、snippets 1）

- 台帳：abc460_g の summary「加算を行いながら」→「加算をしながら」。abc294_g の hld 向けの evidence（kmjp）は HL 分解を使っていない → 差し替えか note
- 用語集：重い辺（heavy-edge）、重いパス（heavy-path）
- 手引き：overview の分量の目安（例題とコードの取り込み）、examples・practice・resources を sections に入れるか、前提ページがないときの用語リンク
- 未解決：Library Checker は GitHub の task.md で確かめた

## linearity-of-expectation（約1.5万字、図1、snippets 1。例題3・練習4・力試し3）

- 台帳：abc149_f の summary の末尾に「。」、abc199_f の「辺を1本」→「辺を 1 本」
- 用語集：固定点（fixed-point）、指示確率変数（indicator）
- 未解決：abc380_g の方針（窓を固定して K(K−1)/4）は執筆者が自分で導いた → 事実の検証で確かめる
- 手引き：定型の節（例題・参考）を sections に載せるか、練習と力試しの見出し、台帳の summary が textlint に違反するとき本文だけ直してよいか、**まだないページへの本文のリンクが mkdocs --strict で落ちるか**

## bit-dp（約14,900字、図1、snippets 2）

- 台帳：abc338_f の evidence に programming-hiroba を足す（今の cnblogs は別解）、abc274_e の evidence を Kazun に替える（kanpurin は一覧だけ）
- 用語集：popcount
- 動く図の案（priority 2）：subset-dp（ハッセ図に dp の値を出し S の昇順に確定）
- 手引き：目安の節を sections に足すか、参考の題名を取る道具、sentence-length の扱い

## cpp-views-basics（約9,100字、snippets 19・コンパイル37回）

- 発見：iota(5,1) は空にならない、filter の view は const 参照で受けるとエラー、split は末尾の空白で空の部分、ranges::to・views::indices は g++-13 にない（indices は g++-15 にもない）
- noai 確認済みのドメインの追加：en.cppreference.com・cpprefjp.github.io・gcc.gnu.org（style-guide 付録 B）
- 用語集：遅延評価、番兵
- 手引き：見本がない、見出しを sections の title どおりにするか、取り込まない失敗例の snippet を置いてよいか

## binary-search-answer（約10,600字、図2、snippets 2。例題1・練習6・力試し2・確認問題2）

- 台帳：abc463_d・abc415_e の summary、abc026_d の approach（f は単調とは限らない）、abc246_g の summary をそろえる
- 用語集：番兵（sentinel。本文から anchor でリンク済み）
- 骨格の不具合：signs に `10^−6` と `10&#94;9` が混在。要点の入れ子の箇条書きに句点がなく textlint の長さの警告
- 手引き：例題・練習の見出しの名前と anchor
- 未解決：abc463_d の「間隔」の定義

## floor-sum（約13,700字、図2、snippets 2。練習0）

- 台帳：abc443_g・abc313_g の summary を確定（「執筆時に確かめる」を外す）
- noai 確認済みのドメインの追加：hackmd.io・rsk0315.hatenablog.com
- 問題の補充：練習0問
- 未解決：ABC443 G の k の範囲（0 ≤ k < N とした）、一般化した floor sum は出典なし、SVG は目視していない
- 手引き：notation・glossary が未作成のときのリンク、sections にない節の扱い、数式内の textlint 警告

## lazy-segment-tree（約16,800字、snippets 5、動く図1（19ステップ、試験12件））

- 台帳：abc473_f・abc455_f の summary を確定
- 用語集：half-open-interval・associativity・identity-element・monoid（本文から anchor でリンク済み）
- 未解決：abc455_f の「コスト」の定義、diff のない問題の並べ方、動く図は目視していない
- 手引き：sections の title を見出しにするか、ds の3つの小見出しと catalog の節割りの重なり、見本がない

## extended-dijkstra（約1.7万字、図2＋Mermaid1、snippets 1。例題3・練習6・力試し3）

- 台帳：arc061_c の evidence を betrue12 の 2019/05/25 の記事に替える、abc164_e の evidence に drken を足す、abc339_d の title の末尾の空白、abc348_d・zone2021_e・typical90_bb を台帳に足す
- 用語集：状態（state）
- 未解決：資源を上限で打ち切ってよい理由の証明（執筆者が組み立てた）、abc184_e・abc132_e の制約の数値
- 手引き：sections の外の節、台帳にない問題に本文で触れるときの扱い、用語リンクの範囲

## 使用量（執筆）

| ページ | 種類 | トークン | 道具の呼び出し | 時間 |
| --- | --- | --- | --- | --- |
| bracket-sequence | 題材別 | 98,325 | 33 | 5.6 分 |
| hld | 発展の概要 | 104,469 | 41 | 5.9 分 |
| linearity-of-expectation | 水・数学 | 130,664 | 41 | 6.9 分 |
| bit-dp | 水・DP | 126,927 | 41 | 6.9 分 |
| cpp-views-basics | C++ | 104,410 | 32 | 7.0 分 |
| binary-search-answer | 基礎 | 124,439 | 42 | 7.9 分 |
| floor-sum | 黄・数学 | 131,684 | 41 | 9.4 分 |
| lazy-segment-tree | 水・データ構造・動く図 | 158,274 | 37 | 9.7 分 |
| extended-dijkstra | 水（青の節）・グラフ | 151,765 | 54 | 10.8 分 |

## 直しの後の提案（第2回の報告から）

### 台帳（data/problems.yaml）
- abc454_d：summary「`(`・`x`・`)` からなる 2 つの文字列について、`(xx)` を `xx` に置き換える操作を繰り返して、同じ文字列にできるか判定する。」、approach「両方を `(xx)` を `xx` に縮めきった形にして比べる。末尾 4 文字をスタックで照合する」、evidence に https://zenn.dev/chiaoi/articles/abc454_solution
- abc407_e：summary の「( を」→「`(` を」
- abc257_d：summary「どこか1つのジャンプ台から出発してすべてのジャンプ台へ行けるようにするための、最小の訓練回数を求める。」
- abc026_d：approach「f(0)<100≤f(十分大きい t) を保つ実数の二分探索。f は単調とは限らないが、中間値の定理で解が見つかる（反復回数を固定）」
- abc463_d・abc415_e・abc246_g・abc313_g・abc443_g・abc473_f・abc455_f・arc061_c：summary を本文（docs/）の問題の行の文にそろえる（本文が正）。abc443_g の note「k の範囲は第三者の解説のコードから判断」。arc061_c の evidence を betrue12 の 2019/05/25 の記事と kmjp の 2016/10/03 の記事に
- abc460_g：「加算を行いながら」→「加算をしながら」。abc294_g の hld 向け：HL 分解で解いた解説の URL を足すか、note「HL 分解の方針はページ本文の議論による」
- abc149_f：summary の末尾に「。」。abc199_f：「辺を1本」→「辺を 1 本」。abc380_g の note「本文の方針は小さい N の全数で確かめた」
- abc338_f：evidence に https://programming-hiroba.com/abc338-f/。abc274_e：evidence を https://kazun-kyopro.hatenablog.com/entry/ABC/274/E（kanpurin を外す）。abc278_f：kanpurin を外す
- abc339_d・abc301_e：title の末尾の空白を消す（AtCoder Problems の値をそのまま写しているなら label を作るときに strip する）。abc453_d・abc463_e：summary の句点
- abc164_e：evidence に drken の記事（drken1215.hatenablog.com/entry/2020/04/27/190000）
- 台帳に足す：abc348_d・zone2021_e・typical90_bb（第三者の解説で確かめてから）
- checked を 2026-10-21 にする：試作の9ページの本文にある問題で、執筆者・検証役が確かめたもの（各ページの例題・練習・力試しのすべて）

### 用語集（docs/guide/glossary.md）の語
sentinel（番兵）、half-open-interval（半開区間）、associativity（結合法則）、identity-element（単位元）、monoid（モノイド）、balanced-parentheses（正しい括弧列）、heavy-edge（重い辺）、heavy-path（重いパス）、fixed-point（固定点）、indicator（指示確率変数）、lazy-evaluation（遅延評価）、popcount、state（状態）

### 手引き（style-guide.md）
- 付録 B に足すドメイン：en.cppreference.com・cpprefjp.github.io・gcc.gnu.org・hackmd.io・rsk0315.hatenablog.com・tayu0110.hatenablog.com
- §9 の使ってよいラムダに「判定の関数」を足す。型の別名の例外として `using mint = atcoder::modint998244353;` を認める
- 遅延セグ木の `choosing`（使い分け）は anchor を変えずそのまま

## 使用量（直し）

直しは各担当 6〜20 万トークン（文脈を引き継いだ再開を含む）、道具の呼び出し 5〜9 回、1〜2 分。検証は9本で約104万トークン（1本あたり約11.6万）、合わせて約7分。

## 全体の見込み（T21）

- 1ページあたり：執筆 10〜16万トークン・6〜11分、検証 約12万トークン・約7分、直し 6〜20万トークン・1〜2分。合わせて約35〜45万トークン
- 残り約340ページ：約1.2〜1.5億トークン。9本並列・1バッチ約30分で約38バッチ、作業時間は合計約20時間（基礎・発展は短いので少し下がる見込み）
- 規模を下げる手段（必要なら）：基礎・発展は検証を1本にまとめて複数ページを担当させる、直しを検証役に任せる、priority 2 以下の図を作らない
