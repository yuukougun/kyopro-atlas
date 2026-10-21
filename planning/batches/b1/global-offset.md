# global-offset の報告と提案（工程8b・b1）

- 書いたファイル：docs/ds/global-offset.md、snippets/global-offset/{offset-heap,flip-deque}.{cpp,yaml}、docs/img/global-offset/offset.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件すべて一致）、textlint（エラー 0・警告 3）
  - 残した警告：138 行の sentence-length（数式 $(\sigma i + s) \bmod N$ を含む文）、162 行の no-unmatched-pair（半開区間 $[l, r)$ の誤検出）、198 行の no-doubled-joshi（abc278_d の行。台帳の summary から fix_problems が作る行なので本文では直していない。下の台帳への提案を参照）
- 動く図：作っていない（visual は static・priority 2）。静的な SVG を 1 枚（格納値と実際の値を 2 段で並べる）置いた
- 使った出典：drken のはてなブログ 5 本（abc212_d・abc379_d・abc278_d・abc158_d・arc077_a）、hamayan のブログ（abc199_c）、E869120 の典型90 044 の解答例（GitHub）。題名は各ページの title 要素で確かめた。新しく noai を確かめたドメインはない（どれも付録 B のドメイン）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc199_c | evidence | https://blog.hamayanhamayan.com/entry/2021/04/25/002202 を足す。いまの evidence（Qiita の典型90 の類題リスト）は問題へのリンクだけで、問いも解き方も書いていない | 左の URL（問い：長さ 2N の文字列への 2 文字の入れ替えと前半・後半の入れ替え。解き方：前半・後半の入れ替えを実際には行わない） |
| abc278_d | summary | 「全体への代入・1 点への加算・1 点の取得のクエリを処理する。」（「への」の重複を避け、手引きの「1 点」の表記に合わせる。textlint の no-doubled-joshi の警告が消える） | 台帳の evidence（drken 2023/05/05） |

ほかの使った問題（abc212_d・arc077_a・abc158_d・abc379_d・typical90_ar）の summary と approach は、evidence の解説と食い違いがなかった。

## 用語集への提案

- なし（ならし計算量は complexity-estimation#amortized、逆元は math/mod-inverse へリンクした）

## 手引きへの提案

- §13.1 では「落とし穴」は sections に載せない定型の節だが、このページの骨格は sections に `anchor: pitfalls` を持つ（binary-search の報告と同じ件）。§13.2 に従い見出しを sections の title と同じ長い形にした。sections から外して `## 落とし穴 {#pitfalls}` にそろえるかはメインで決めてほしい
- 基礎のページの「上位の手法とのつながり」は、このページでは sections の to-lazy-segment-tree（level 水）が受け持つ。使い分けの節は別に立てていない

## 問題の補充の候補

- abc389_c（C. Snake Queue、diff 255、ap.py で実在を確認、台帳になし）：蛇の列の末尾への追加・先頭の蛇が抜ける・K 番目の蛇の頭の座標を答えるクエリを処理する。追加時の座標を保存し、抜けた蛇の長さの合計をオフセットとして引く。abc319 以降の問題で、オフセットの節の練習の最初の 1 問に合う。裏付け：https://merom686.hatenablog.com/entry/2025/01/19/020250 、https://zenn.dev/shinonome81/articles/b1de75b0849b32 （research/05-ds の付録の候補にもある）

## 未解決の点

- 図 offset.svg は描画して目で確かめる道具がなく、座標の計算だけを確かめた。文字の重なりがないかの表示の確認を検証役に頼みたい
- 回転と反転を組み合わせる式（実際の $i$ 番目 ＝ もとの $(\sigma i + s) \bmod N$ 番目、反転で $s \leftarrow s + \sigma(N - 1)$・$\sigma \leftarrow -\sigma$、右回転で $s \leftarrow s - \sigma$）は自分で導いた。対応する台帳の問題はない
- 全体代入の節の、配列と時刻で持つ別法は記憶に基づく（abc278_d の台帳の approach「一括代入の時刻を覚え、触った要素だけ遅れて更新する」とは一致する）
- 遅延セグメント木の節は、lazy-segment-tree の #idea 節へリンクした。相手のページの書き方との食い違いがないかを検証役に見てほしい

## 検証の指摘への対応（verify/global-offset.md）

- 直したもの：指摘 1〜11 すべて
  - 指摘 2 は (a) を採った。練習の方針はフラグのままにし、hamayan の参考は「ABC199 C の別法（前半と後半を別の文字列で持ち、入れ替えを swap で済ませる）」に直した
  - 指摘 3 は「区間が全体だけなら、全体代入の値とオフセットを組にして持つことにあたる」に言い換えた
  - 指摘 5 は「ソート済みの queue」を外し、ABC379 D の練習の方針に任せた
  - 指摘 8 は flip-deque のメンバ名を `dq` に変えた（コード片の検査は一致）
  - 指摘 10 は図の下の行を「箱は格納値の小さい順。この順は実際の値でも同じなので、…」に変え、代替テキストにも並べ方を足した（下の行の右端の見積もりは約 556、viewBox の幅 600 以内）
- 採らなかったもの：なし
- textlint の警告は前と同じ 3 件（138 行の数式を含む文の長さ・162 行の $[l, r)$ の誤検出・198 行の台帳由来の「への」）

## 台帳への提案（指摘 2 を受けて差し替え）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc199_c | evidence | 上の表の提案のうち根拠の書き方を直す：hamayan の記事は「前半と後半を別の文字列 pre・post で持ち、前半・後半の入れ替えを swap(pre, post) で済ませる」解き方（フラグの方法ではない）。evidence に足すなら approach を記事の方法に合わせるか、フラグの方法を書いた別の解説を探して足す | https://blog.hamayanhamayan.com/entry/2021/04/25/002202 |
| abc278_d | summary | 検証役の申し送りに従い、台帳の alternatives にある「全体代入・1 点加算・1 点取得のクエリを処理する。」を勧める（「への」の重複が確実に消える） | 台帳の evidence（drken 2023/05/05） |
