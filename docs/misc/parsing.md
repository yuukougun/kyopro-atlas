---
id: parsing
title: 構文解析
aliases: [再帰下降構文解析, パーサ, BNF, 式の評価, 逆ポーランド記法, recursive descent parsing]
type: technique
field: misc
order: 40
level: 青
kind: [文字列]
prerequisites: [recursion-structure]
related: [bracket-sequence, stack-techniques, dp-basics, bit-full-search, cpp-environment#stack-depth]
summary: +・*・括弧を含む式の文字列を、演算子の優先順位どおりに評価・解析する。文法の規則（式・項・因子）ごとに関数を作り、読み取り位置を共有して再帰的に読む（再帰下降構文解析）。
complexity: null
signs:
  - {type: phrase, text: 数式の文字列が与えられ、値を求める}
  - {type: phrase, text: + と * と括弧の優先順位がある}
  - {type: phrase, text: 式として正しい部分文字列}
  - {type: phrase, text: 入れ子の構造を持つ文字列}
  - {type: constraint, text: 式の長さが 2×10^5 程度で、括弧の入れ子が深くなりうる}
acl: []
frequency: B
frequency_evidence: recent 0・前提として届くページなし・古い ABC 3 問
sections:
  - {title: BNF と規則ごとの関数（読み取り位置を参照で共有する）, anchor: bnf}
  - {title: 優先順位と括弧が正しく読める理由（構文木と呼び出しの木）, anchor: why-it-works}
  - {title: 単項マイナス・空白などの例外, anchor: edge-cases}
  - {title: 文法に沿った DP, anchor: grammar-dp}
  - {title: 式の部分文字列の総和, anchor: substring-sum, level: 発展}
  - {title: 深い入れ子と再帰の深さ, anchor: deep-nesting}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：+・\*・括弧を含む式の文字列を、演算子の優先順位どおりに評価・解析する。文法の規則（式・項・因子）ごとに関数を作り、読み取り位置を共有して再帰的に読む（再帰下降構文解析）。
    - **いつ使うか**：
        - 数式の文字列が与えられ、値を求める
        - \+ と \* と括弧の優先順位がある
        - 式として正しい部分文字列
        - 入れ子の構造を持つ文字列
        - 式の長さが 2×10^5 程度で、括弧の入れ子が深くなりうる
    - **計算量**：（執筆時に書く）
    - **前提**：[再帰的な構造](../basics/recursion-structure.md)
