---
title: 考察
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 考察

言い換え・主客転倒・寄与・余事象・偶奇・不変量・構築などの考察の型。9 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

問題の形から試す型を選ぶときは[詰まったときの発想リスト](../guide/thinking-checklist.md)、言い回しからは[逆引き辞典（言い回しから）](../guide/reverse-index-signs.md#by-phrase)を使う。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。

- [言い換えの典型](reformulation.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：条件や目的関数を、数えやすい・判定しやすい形に書き直す。
- [一部を固定して数える](fix-variable.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：変数の一部（3 つ組の真ん中・最大値・余りなど）を固定すると、残りの条件が単純になって独立に数えられる。
- [主客転倒・寄与](contribution.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：全ペア・全区間・全部分集合についての総和を、「各要素が何回数えられるか × 値」の和に入れ替えて求める。
- [余事象](complement.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：「少なくとも 1 つ」「〜でない」ものは、全体から数えやすい補集合を引いて数える。
- [偶奇に着目する](parity.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：1 歩ごとに (x + y) の偶奇が入れ替わる、±1 をちょうど K 回なら差と K の偶奇がそろう、など偶奇の必要条件から可否を判定する。
- [不変量・単調に変わる量](invariant.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：操作で変わらない量（和の余り・個数の偶奇・XOR）を見つけて必要条件を得て、十分性は構築で示す。
- [後ろから・逆順に考える](reverse-thinking.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：後ろから決めると選択肢が一意になる、最後の操作が特定できれば逆再生で取り除ける、削除を逆にすると追加になる、など時間の向きを逆にして考える。
- [構築問題の考え方](construction.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：条件を満たすものを 1 つ作る問題は、小さい N で手で作って規則を見つけ、不可能な場合の必要条件を先に挙げてから一般化する。
- [対称性・鳩の巣原理・場合分け](symmetry-pigeonhole-casework.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：対称性で計算や場合を半分に減らし、鳩の巣原理で「必ず一致が起きる」ことから探索の回数の上限を得る。

## ほかの分野にある関連ページ {#elsewhere}

種類に[考察](../lists/kind-observation.md)を持つ、ほかの分野のページ。

- [基本テクニック](../basics/index.md)：[bit ごとに独立に考える](../basics/bitwise-independence.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[差分列への言い換え](../basics/difference-sequence.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>・[ランレングス圧縮](../basics/run-length-encoding.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[絶対値の和の最小化と中央値](../basics/median-absolute.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [グラフ](../graph/index.md)：[DFS 木・BFS 木とグラフの構築](../graph/graph-construction.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [木](../tree/index.md)：[辺で切って数える](../tree/tree-edge-contribution.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[木の構築・復元](../tree/tree-construction.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [データ構造](../ds/index.md)：[遅延セグメント木の載せ方の型](../ds/lazy-segment-tree-patterns.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
- [整数論・代数](../math/index.md)：[Σ の変形](../math/sigma-manipulation.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[整数の証明の型](../math/proof-patterns.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [数え上げ・確率・ゲーム](../comb/index.md)：[数え上げの考え方](../comb/counting-mindset.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[対応づけ・数える対象の言い換え](../comb/counting-bijection.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[順序を固定して数える](../comb/counting-fix-order.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[重複の除き方](../comb/counting-dedup.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[置換の巡回分解](../comb/permutation-cycles.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[置換の偶奇](../comb/permutation-parity.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[対称性で確率を求める](../comb/probability-symmetry.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
- [幾何](../geometry/index.md)：[マンハッタン距離と 45 度回転](../geometry/manhattan-chebyshev.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>
