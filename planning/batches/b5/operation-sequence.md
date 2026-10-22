# operation-sequence の報告と提案（b5）

- 書いたファイル：docs/patterns/operation-sequence.md、docs/img/operation-sequence/timeline.svg（snippets はなし）
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 問われ方と手法の一覧, anchor: overview}` を properties の次に足した（見本の bracket-sequence と同じ形）
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0・警告7（131 行は半開区間 $[0, 3)$ の括弧の誤検出。ほかは読点・助詞の重なりの警告で、数式を含む文）
- 図：timeline.svg（幅 400）を render_svg で 360px・720px にして目で確かめた。catalog の visual（static・priority 2）にあたる。reverse-thinking の reverse-deletion.svg（グラフの図）と重ならないよう、状態 S0〜S3 の時間軸と、記録する時点だけを示した
- 使った出典：qiita.com の 2 件（Wakako19972899・comet725。どちらも ABC466 D）。新しいドメインはなし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
|---|---|---|---|
| abc466_d | summary | N×N のマス目で、指定したマスと同じ行・同じ列にあるコマを取り除いてからそのマスにコマを置く操作を繰り返した後、残っているコマの数を求める。 | https://qiita.com/Wakako19972899/items/58622774de0fe5e24616、https://qiita.com/comet725/items/754d920467029090b165 |
| abc466_d | evidence | 既存の comet725 に https://qiita.com/Wakako19972899/items/58622774de0fe5e24616 を足す（後ろから見て行・列の印で数える方針。§15-6 の 2 件目） | 同左 |
| abc466_d | checked | 2026-10-22 | — |

本文の行は `- abc466_d：要約` で書き、fix_problems --page で label を埋めた。

## 用語集への提案

なし（オフライン・オンライン強制・ならし計算量は用語集の既存の項目へリンクした。版の木・経路コピーは persistent-data-structures の節へリンクした）。

## 手引きへの提案

- §4 の pattern：表の「代表の問題」の欄で、代表の問題が行き先のページの例題にあるときは、label の一部（ABC212 D など）を行き先のページの例題の anchor（`../ds/global-offset.md#abc212_d`）へのリンクにしてよい、と明記する。このページはそうした（atcoder.jp へのリンクは問題の囲みだけ）。練習に置いた問題は `#practice` へのリンクにした
- §4 の pattern：related が多い（このページは 18）案内のページでは、表の行を related の全部ではなく型ごとに 1 行にまとめ、残りは節の本文でリンクする形でよい、と書き添えると迷わない

## 問題の補充の候補

なし。patterns の練習の目安（0〜3）に対して確認済みの abc466_d が 1 問ある。表の各行の代表は行き先のページの例題・練習（abc212_d・abc344_e・abc328_d・abc435_e・abc229_e・abc174_f・abc341_e・abc273_e・abc167_d、本文で abc461_e・abc253_f・abc179_e）を参照した。

## 未解決の点

- 骨格の sections の title は catalog の title から括弧の id を落としたもの（paint・offline・online・versions）と、残したもの（global-ops など）が混ざる。見出しは骨格の title のままにした。そろえるならメインが決める
- 節 paint の「区間への加算のように、たどるだけの操作が混ざるとならしが崩れる → 遅延セグメント木」は interval-set の要点と #comparison 付近の記述に合わせた

## 検証の指摘への対応

- 直した：1（平方分割の例を $O(\sqrt{N}\log N)$ 程度、工夫で $O(\sqrt{N\log N})$ に）・2（「区間加算と 1 点の質問」に限定）・3（確認問題を、入力は全部あるが辺の番号が前の答えとの XOR で決まる削除クエリに逆順の追加が使えるか、に差し替え）・4（map で持てば保存と読み込みは $O(\log Q)$ を添えた）・5（complexity の末尾に「が多い」）・6（案 (b)：名指しは catalog の problems_note どおり残し、方針の文から行・列の具体を外して一般論にした）・7（「次の節」を [後ろから見る](#overwrite) へのリンクに）・8（行き先として kth-element#reverse-insertion と balanced-bst#alternatives へリンク）
- 採らなかった：9（表の「代表の問題」をリンクにする形）は手引き §4 への提案として上に挙げてあり、採るかはメインの判断に任せる。採らない場合は label を文字にし、表の後に 1 文を置く直しが要る。10（見出しの括弧の id のそろえ方）は sections の title を変えるので骨格の判断にあたり、メインに任せる
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0・警告7
