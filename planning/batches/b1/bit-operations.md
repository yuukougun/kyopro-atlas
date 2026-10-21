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

## 検証の指摘への対応（2026-10-21）

- 1（直すべき）：確認問題「和と XOR」の 1 問目を $a + b = 10$、$a \oplus b = 4$（AND は 3、例 $a = 3, b = 7$）に替えた。2 問目を $a \oplus b = 6$ にし、偶奇は合うが AND＝2 と XOR＝6 が bit 1 で重なるので解がない、と答えに書いた。解がある条件 $S \ge X$・$S - X$ が偶数・$((S - X)/2) \text{ AND } X = 0$ と、偶奇は必要条件にすぎないことも書いた。本文の等号の段落に「AND と XOR は同じ桁に 1 を持たない」の 1 文を足した
- 2：#submask の文を「$s = m$ から始めて」にした
- 3：ABC356 D の方針に、60 桁分を足すと long long を超えるので足すたびに余りを取る、を足した
- 4：#pitfalls の 1 段落目を、手元の値（定数の `1 << 40` は 0、変数の `1 << n`（n = 40）は 256）で書き直した。確認問題「どこが誤りか」の答えも「手元では 0 になった」にそろえた
- 5：`std::bit_width` も符号なしだけ、の注記とリンク（cpp-math-functions#bit-unsigned-only）を足した
- 6：std::popcount の文を cpp-math-functions#bit-unsigned-only へ、1 << k の文を cpp-integer-overflow#shift-width へのリンクに直した。#next-steps の bitwise-independence・bit-full-search は節を指す文ではないのでページへのリンクのままにした。subset-enumeration-dp・xor-basis は stub なので今のまま
- 7：front matter の complexity を「すべての集合とその部分集合の組は合計 O(3^N)」にした
- 8：submask-steps.svg の注記を「点線の行：s − 1 で立った bit 2 の 1 を & m が消し、011 が残る。」にした。提案の文は字幅の見積もりで 480 を超えるおそれがあったので、主語（& m）を明示したまま短くした。字幅の見積もりは元の文と同程度
- 9：採らなかった。落とし穴の見出しを定型にそろえるかは、ほかのページとの統一を含めてメインが判断する事項なので（手引き §13.1）。そろえる場合は sections から pitfalls の行を外し、見出しを `## 落とし穴 {#pitfalls}` にすればよい（anchor は同じ）

### 台帳への提案（追加）

- 検証役の確認に基づき、abc269_c・abc213_a・abc356_d・abc121_d の checked に 2026-10-21 を入れる

### 検査（対応後）

- check_pages エラー 0・警告 0、fix_problems --check 0 行、check_snippets 5 片・期待と違う 0、textlint エラー 0（警告 18）
