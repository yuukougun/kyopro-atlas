---
id: subsequence-and-substring
title: 部分列と部分文字列
aliases: [部分列, 部分文字列, subsequence, substring]
type: pattern
field: patterns
order: 20
level: null
kind: [案内, 文字列, DP]
prerequisites: []
related: [subsequence-matching, dp-state-design, dp-mod-state, subsequence-dp, counting-dedup, dp-phase, lcs, lis, rolling-hash, z-algorithm, suffix-array, palindrome, interval-dp, string-automaton-dp, string-basics, interval]
summary: 部分列（飛び飛びに選ぶ）と部分文字列（連続する部分）が出てくる問題で、問われ方から使う手法を引ける。判定・選び方の数・異なるものの数・最長の共通部分・種類数の問われ方に分ける。
complexity: null
signs:
  - {type: phrase, text: T が S の部分列か判定する}
  - {type: phrase, text: S から何文字か選んで順に並べると T になる選び方の数}
  - {type: phrase, text: S の部分列として現れる異なる文字列の個数}
  - {type: phrase, text: S の部分文字列の種類数}
acl: []
sections:
  - {title: 題材の性質, anchor: properties}
  - {title: T が S の部分列か → 前から貪欲に照合・次の出現位置の表（subsequence-matching）, anchor: is-subsequence}
  - {title: T が部分列として現れる選び方の数 → 照合した文字数を状態にした DP（dp-state-design）, anchor: count-occurrences}
  - {title: '条件を満たす部分列の数 → 末尾の文字や余りを状態にした DP（dp-state-design, dp-mod-state）', anchor: count-with-condition}
  - {title: '異なる部分列の数 → 部分列 DP と代表元の決め方（subsequence-dp, counting-dedup）', anchor: distinct-subsequences}
  - {title: i < j < k の位置の組の数 → 段階を状態にした DP（dp-phase）, anchor: index-tuples}
  - {title: '最長共通部分列・最長増加部分列 → LCS・LIS（lcs, lis）', anchor: longest}
  - {title: '部分文字列の一致・比較 → ローリングハッシュ・Z（rolling-hash, z-algorithm）', anchor: substring-match}
  - {title: 部分文字列の種類数・K 番目 → Suffix Array（suffix-array）, anchor: distinct-substrings}
  - {title: '回文の部分文字列・部分列 → 回文のページと区間 DP（palindrome, interval-dp）', anchor: palindromes}
  - {title: T を部分文字列に含まない文字列の数 → 照合の状態を持つ DP（string-automaton-dp）, anchor: avoid-substring}
  - {title: 数列の連続部分列 → 題材別の区間（interval）, anchor: subarrays}
  - {title: 落とし穴, anchor: pitfalls}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：部分列（飛び飛びに選ぶ）と部分文字列（連続する部分）が出てくる問題で、問われ方から使う手法を引ける。判定・選び方の数・異なるものの数・最長の共通部分・種類数の問われ方に分ける。
    - **いつ使うか**：
        - T が S の部分列か判定する
        - S から何文字か選んで順に並べると T になる選び方の数
        - S の部分列として現れる異なる文字列の個数
        - S の部分文字列の種類数
    - **使い方**：（執筆時に書く）
