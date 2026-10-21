# geometry-precision の報告と提案（工程8b・b1）

- 書いたファイル：docs/geometry/geometry-precision.md、snippets/geometry-precision/{truncation,scale,compare,normalize,cancellation}.{cpp,yaml}、docs/img/geometry-precision/double-spacing.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査：check_pages（エラー 0・警告 0）、check_snippets（5 件すべて一致）、textlint（エラー 0、警告 6：数式・代替テキストを含む文の長さの誤検出）、fix_problems --check（このページの行は直す必要なし。argument-sort.md の 6 行が未展開と出るが担当外）
- 図：catalog の visual（priority 2、static）を SVG で作った。描画の道具が手元にないため目視の確認はしていない（座標は計算で確かめた）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc385_f | summary | 数直線上に並ぶビルについて、座標 0 から見てすべてのビルを見渡せない高さの最大値を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/1221_abc385 ・ https://merom686.hatenablog.com/entry/2024/12/22/165012 |
| abc385_f | evidence | ikatakos の上記 URL を追加（merom686 のトップページの URL は外してよい） | 同上 |
| abc385_f | approach | 答えは隣り合うビルの頂点を結ぶ直線の y 切片の最大。切片の分子を整数で持ち __int128 で比べる。double では桁落ちで誤る（節 double-precision） | 同上 |
| abc467_d | summary | 2 点 P・Q から等距離で、2 点 R・S からも等距離な点があるかを判定する（テストケースが複数ある）。 | https://qiita.com/comet725/items/6d1da8aae01548d3ebba ・ https://qiita.com/hyouri/items/c2d2344566d215b6cae0 |
| abc467_d | evidence | comet725 の上記 URL を追加 | 同上 |
| abc467_d | approach | PQ と RS の垂直二等分線を整数の係数で書き、平行でないか同じ直線なら Yes（節 double-coordinates・line-normalization） | 同上 |
| abc418_e・abc385_f・abc467_d | checked | 2026-10-21（第三者の解説で問いと方針を確かめた） | 各 evidence |

- 本文の abc385_f・abc467_d の行の要約は上の新しい summary で書いた。台帳を直した後に fix_problems を流しても同じ文になる

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 桁落ち | catastrophic-cancellation | 誤差を含む近い大きさの 2 つの値を引き算したとき、結果が小さくなって相対誤差が大きくなること。10^9 規模の double どうしの差が 1 程度になると、相対誤差は 10^-7 程度になる。 |
| EPS | epsilon | 浮動小数点数を誤差を許して比べるときに使う小さな正の数。計算の誤差より大きく、真の値の差より小さく取る。 |
| 正規化 | canonical-form | 同じものを表す複数の書き方を、決まった 1 つの代表に直すこと。方向 (dx, dy) は gcd で割って dx > 0（dx = 0 なら dy > 0）にそろえる。 |

- 本文から用語集へのリンクは張っていない（必要ならメインの判断で足す）

## 手引きへの提案

- 付録 A の幾何に「正規化」「桁落ち」「EPS」を足すとよい（本文で使った）
- check_noai で確かめたドメインはなし（qiita.com は付録 B にある。comet725 の記事は個別に check_noai で確かめ、指定なし）

## 問題の補充の候補

- 台帳で足りているので追加の候補はなし。参考までに、research/08 の表で geometry-vectors の例題になっている abc181_c・abc224_c は、このページの練習には入れていない（易しすぎ、外積の基本のため）

## 未解決の点

- abc467_d：P = Q（または R = S）の入力がありうるかを確かめられなかった（解説に制約がない）。練習の方針では触れていない
- abc385_f：答えがちょうど 0 になる場合（切片の最大が 0）の扱いは merom686 氏の記事の「答えが 0 のケース」の記述から、最大値が負のときだけ −1 と書いた。問題文で確かめていない
- abc169_c：「A ≤ 10^15」「B は x.yz の形」は drken 氏の記事による
- 「AtCoder の C++ も x86-64 の GCC で long double は仮数 64 ビット」は手元の g++-15（x86-64）で LDBL_MANT_DIG = 64 を確かめたもので、ジャッジの環境そのものは確かめていない
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 11 回（検索 1 回を含む）
- abc220_g・abc296_g：merom686 氏の記事には問題文と制約がなく、方針だけを確かめた（checked は null のまま）
