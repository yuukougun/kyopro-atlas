---
title: その他の技法
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# その他の技法

インタラクティブ、乱択、bitset による高速化、構文解析。4 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[小さい N の全探索](../guide/method-comparison.md#small-n)。

- [インタラクティブ問題](interactive.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：質問を出力してジャッジの答えを受け取る形式の問題で、質問回数の上限から方針を逆算する（2 択の質問なら ⌈log2 候補数⌉ 回）。
- [乱択アルゴリズム](randomized.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：乱数を使って、一定の確率で誤るが速い方法（モンテカルロ法）や、常に正しいが時間が確率的な方法（ラスベガス法）を作る。
- [bitset による高速化](bitset-speedup.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：bool を 64 個ずつ 1 語に詰め、AND・OR・XOR・シフトを語単位で行って計算量をおよそ 1/64 にする。
- [構文解析](parsing.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：+・\*・括弧を含む式の文字列を、演算子の優先順位どおりに評価・解析する。
