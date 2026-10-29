---
title: 文字列
type: generated
---

<!-- tools/gen_site.py が生成する。手で直さない -->

# 文字列

ハッシュ、Z・KMP・Manacher、Trie、Suffix Array、Aho-Corasick。13 ページ。ページ名の横の印はレベル（[レベルの意味](../start/how-to-use.md#levels)）である。

学ぶ順：[色別ロードマップ](../guide/roadmap.md#reading-order)。使い分け：[文字列の照合](../guide/method-comparison.md#strings)。自作：[自作ライブラリの設計と動作確認](../guide/library-design.md)。

## 文字列の基本

- [文字列の基本操作と辞書順](string-basics.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：辞書順の最小・回転・文字の一斉置換を問う文字列の問題を、定義に沿った全探索と比較で解く。
- [部分列の判定と次の出現位置の表](subsequence-matching.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>：T が S の部分列かを、S を左から見て T の文字をできるだけ早く拾う貪欲で判定する。

## ハッシュ

- [ローリングハッシュ](rolling-hash.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：文字列を B 進数の値（mod p）とみなし、接頭辞のハッシュから任意の部分文字列のハッシュを O(1) で取り出して、部分文字列どうしの一致を確率的に判定する。
- [集合・多重集合のハッシュ](hashing-for-sets.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：値ごとに独立な 64 ビットの乱数を割り当て、集合は XOR、多重集合は和で表すと、2 つの集合が等しいかを順序に関係なく O(1) で比べられる。
- [ハッシュの衝突と安全な設計](hash-safety.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：比べるハッシュの組の数から衝突確率を見積もり、固定のテストでも落ちない mod と基数を選ぶ。

## 線形時間の照合と回文

- [Z-algorithm](z-algorithm.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：Z 配列 z[i]（S と S[i:] の最長共通接頭辞の長さ）を O(N) で求める。
- [KMP 法と文字列の周期](kmp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：π[i]（先頭 i+1 文字の、接頭辞でも接尾辞でもある最長の真の部分の長さ）を O(N) で求める。
- [回文の扱いと Manacher](palindrome.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：回文の問題を、対称な位置の組を見る・中心から伸ばす・両端から作るの 3 つの見方で小さな状態に落とす。

## Trie と照合オートマトン

- [Trie](trie.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>：文字列の集合を、共通の接頭辞を共有する木に入れる。
- [Aho-Corasick 法](aho-corasick.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：パターンの Trie に失敗リンク（Trie にある最長の真の接尾辞へのリンク）を BFS 順に張り、全文字の遷移を埋めたオートマトンにする。
- [照合オートマトン上の DP](string-automaton-dp.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>：KMP 法や Aho-Corasick 法の状態（いまの接尾辞のうちパターンの接頭辞になっている最長のもの）を DP の状態にして、パターンを含まない・すべて含む長さ N の文字列を数える。

## 接尾辞の構造

- [Suffix Array と LCP 配列](suffix-array.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>：全接尾辞を辞書順に並べた添字の列（SA）と隣どうしの最長共通接頭辞（LCP 配列）を作る。
- [Suffix Automaton と発展の文字列アルゴリズム](suffix-automaton.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>：Suffix Automaton は全部分文字列を状態数 2N−1 以下の DFA で表し、文字を足しながら異なる部分文字列の数を答える。

## ほかの分野にある関連ページ {#elsewhere}

種類に[文字列](../lists/kind-string.md)・[ハッシュ・乱択](../lists/kind-hashing.md)のどれかを持つ、ほかの分野のページ。

- [基本テクニック](../basics/index.md)：[ランレングス圧縮](../basics/run-length-encoding.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>・[辞書順最小を前から決める貪欲](../basics/lexicographic-greedy.md) <span class="kp-mini kp-lv-kiso" title="difficulty 〜1199">基礎</span>
- [動的計画法](../dp/index.md)：[最長共通部分列と編集距離](../dp/lcs.md) <span class="kp-mini kp-lv-mizu" title="difficulty 1200〜1599">水</span>・[部分列 DP](../dp/subsequence-dp.md) <span class="kp-mini kp-lv-ki" title="difficulty 2000〜2399">黄</span>
- [木](../tree/index.md)：[木の同型判定と木のハッシュ](../tree/tree-isomorphism.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [整数論・代数](../math/index.md)：[大きな数の素数判定と素因数分解](../math/miller-rabin.md) <span class="kp-mini kp-lv-hatten" title="difficulty 2400〜（概要だけ）">発展</span>
- [その他の技法](../misc/index.md)：[乱択アルゴリズム](../misc/randomized.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>・[構文解析](../misc/parsing.md) <span class="kp-mini kp-lv-ao" title="difficulty 1600〜1999">青</span>
