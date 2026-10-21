# bit-operations の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/bit-operations.md、snippets/bit-operations/{submask,xor-range,count-bit,pitfalls-ng,precedence-ng}.{cpp,yaml}、docs/img/bit-operations/{ops-table,submask-steps}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections に「上位の手法とのつながり（next-steps）」を足した（手引き §4 の基礎の構成の節。level はページと同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（5 片・期待と違う 0）、textlint（エラー 0・警告 18。数式を含む文の長さ、画像の代替テキストの長さ、折りたたみの証明の助詞の重複、参考の `[0, B]` の括弧の誤検出）、fix_problems --check（このページは 0。basics/event-sort.md に 7 行あるが、別の執筆者の担当）
- 図：catalog の visual（static・priority 2）どおり、AND・OR・XOR の桁をそろえた表（a + b との関係を添えた）と、submask の列挙の手順の表を静的な SVG にした。動く図は作っていない。手元に SVG を描画する道具がなく、見た目は座標の計算でだけ確かめた（検証役に表示を見てほしい）
- pitfalls-ng（run）・precedence-ng（warning）は落とし穴の記述の裏付けで、本文には取り込んでいない（手引き §13.9）

## 使った出典

- drken（hatenablog、付録 B にある）：ABC269 C・ABC213 A・ABC356 D・ABC121 D の解説（台帳の evidence）。例題の制約（N < 2^60、1 の個数 15 以下）、列挙が大きい順で 0 を別に扱うこと、ABC356 D の法 998244353、ABC121 D の対の議論を確かめた
- 新しく noai を確かめたドメイン：なし
- 事実の確かめ：g++-15（-std=gnu++23 -O2）で `1 << 31` が警告なしに -2147483648、`1 << n`（n = 40、変数）が -O2 で 0、定数の `1 << 40` に -Wshift-count-overflow、`__builtin_popcount` に long long を渡して警告なしに切り詰め、`-7 >> 1 = -4`・`-7 / 2 = -3`、`x & 1 == 0` に括弧の警告。0〜n の XOR の表と count_bit は素朴な計算と assert で照合。3^15・3^16・3^18・3^20 は Python で計算

## 台帳への提案

- abc356_d｜summary｜「0 から N までの各 k について popcount(k AND M) を足した値を、998244353 で割った余りで求める。」｜https://drken1215.hatenablog.com/entry/2024/06/08/041849（法が要約にない。本文は方針の折りたたみで補った）
- abc269_c｜summary｜「1 が 15 個以下の N について、2 進表記で 1 が立っている bit だけを使って表せる整数を、すべて昇順に出力する。」としてもよい（制約がサインそのもの）｜https://drken1215.hatenablog.com/entry/2024/07/07/222412
- abc476_g（frequency_evidence に挙がっている）｜summary が「（執筆時に確かめる）」のまま。lis のページの力試しなので、このページでは扱っていない

## 用語集への提案

- 最下位ビット｜lowest-set-bit｜2 進表記で 1 が立っている桁のうち、最も下の桁。`x & -x` でその桁だけを残した値が、`x & (x - 1)` でその桁を消した値が得られる
- 部分集合の列挙（submask）｜submask｜整数 m の 1 の桁だけからなる整数（m の部分集合）を列挙すること。`s = (s - 1) & m` を繰り返すと大きい順に 1 回ずつ現れる
- popcount｜popcount｜2 進表記の 1 の個数。集合を整数で表したときの要素数
- （本文の単位元のリンクは既存の identity-element を使った）

## 手引きへの提案

- §6 の記法に「AND・OR を数式で書くとき `\text{ AND }` を使う」とあるが、本文の C++ の式（`(s - 1) & m`）と数式（$(s - 1) \text{ AND } m$）が混ざる。数式では `\text{ AND }`、コードの話ではバッククォートの `&`、と使い分けを明記するとよい
- 表のセルにバッククォートで `|`（OR 演算子）を書くと表が崩れる恐れがある。bit 演算のページでは表の代わりに箇条書きを使う、を §8 か §6 に足すとよい（このページは箇条書きにした）

## 問題の補充の候補

- abc171_e（E. Red Scarf、diff 778、台帳で確認済み・xor のページの例題）｜「自分以外の XOR」から各値を復元する。本文の XOR の性質の節の型そのもの｜https://drken1215.hatenablog.com/entry/2020/06/22/122500（台帳の evidence）。このページの練習に足すことを提案する（例題は xor のページのまま）
- arc098_b（D. Xor Sum 2、diff 1404、台帳で確認済み・two-pointers の力試し）｜和と XOR が等しい ⇔ 桁が重ならない、を使う｜https://drken1215.hatenablog.com/entry/2018/06/26/125054。このページの力試しの候補（尺取り法が要るので、力試しなら可）
- 部分集合の部分集合の列挙で 3^N の DP（集合を 2 つ以上のグループに分ける ABC の問題）は subset-enumeration-dp の担当なので、ここには足さない

## 未解決の点

- catalog の sections の「落とし穴（…）」は sections に残っているので、手引き §13.1 の定型の `## 落とし穴 {#pitfalls}` ではなく、sections の title をそのまま見出しにした（anchor は pitfalls で同じ）。title から括弧を外して定型にそろえるかはメインで判断してほしい
- bitwise-independence・bit-full-search・subset-enumeration-dp・xor-basis・cpp-math-functions・cpp-integer-overflow はまだ stub なので、節へのアンカーは付けずページへのリンクにした。draft になったら cpp-math-functions#bit-functions・#builtins、cpp-integer-overflow#shift-width、subset-enumeration-dp#why-3n へ直すとよい
- SVG の表示を目で確かめていない（上記）

## 使用量の目安

- 道具の呼び出し 約 25 回、Web 取得 4 回（drken の解説）＋題名の確認に curl 4 回
