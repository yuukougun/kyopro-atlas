---
id: subsequence-dp
title: 部分列 DP
aliases: [異なる部分列の数, 部分列の個数, Distinct Subsequences]
type: technique
field: dp
chapter: 列の DP
order: 190
level: 黄
kind: [DP, 文字列, 数え上げ]
prerequisites: [subsequence-matching, counting-dedup]
related: [dp-phase, dp-reconstruction, lcs, string-automaton-dp, dynamic-dp, subsequence-and-substring#distinct-subsequences]
summary: 異なる部分列の個数を、各文字を「まだ使っていない位置のうち最も左」から取る取り出し方だけを数えて求める。次の出現位置の表を使い、各位置から文字ごとに配る DP になる。
complexity: null
signs:
  - {type: phrase, text: 異なる部分列の個数}
  - {type: phrase, text: 部分列として現れない最短の文字列（辞書順最小）}
  - {type: phrase, text: 辞書順で K 番目の部分列}
  - {type: constraint, text: 文字の種類 26 程度、|S| ≤ 2×10^5}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 位置の組を数える（重複を気にしない）か、異なる文字列を数えるか, anchor: positions-or-strings}
  - {title: 最も左を取る取り出し方が一意な理由, anchor: leftmost}
  - {title: 次の出現位置の表で配る DP, anchor: next-table-dp}
  - {title: 部分列として現れない最短の文字列（後ろから DP して辞書順最小に復元）, anchor: shortest-non-subsequence}
  - {title: 辞書順 K 番目の部分列（後ろからの個数で先頭から決める）, anchor: kth-subsequence}
  - {title: 条件付き・言い換えてから数える（隣り合う位置を選ばない・累積和の列・TT の形）, anchor: with-conditions}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：異なる部分列の個数を、各文字を「まだ使っていない位置のうち最も左」から取る取り出し方だけを数えて求める。次の出現位置の表を使い、各位置から文字ごとに配る DP になる。
    - **いつ使うか**：
        - 異なる部分列の個数
        - 部分列として現れない最短の文字列（辞書順最小）
        - 辞書順で K 番目の部分列
        - 文字の種類 26 程度、|S| ≤ 2×10^5
    - **計算量**：（執筆時に書く）
    - **前提**：[部分列の判定と次の出現位置の表](../string/subsequence-matching.md)、[重複の除き方](../comb/counting-dedup.md)
