---
id: string-automaton-dp
title: 照合オートマトン上の DP
aliases: [オートマトン DP, KMP DP, Aho-Corasick 上の DP, 照合状態の DP, 禁止文字列, 禁止部分文字列, automaton DP]
type: technique
field: string
chapter: Trie と照合オートマトン
order: 110
level: 青
kind: [DP, 文字列]
prerequisites: [kmp, matrix-power]
related: [aho-corasick, dp-state-design, bit-dp, digit-dp, lcs, inclusion-exclusion, subsequence-dp]
summary: KMP や Aho-Corasick の状態（いまの接尾辞のうちパターンの接頭辞になっている最長のもの）を DP の状態にして、パターンを含まない・すべて含む長さ N の文字列を数える。N が巨大なら遷移を行列にして累乗する。
complexity: null
signs:
  - {type: phrase, text: 長さ N の文字列のうち、どのパターンも部分文字列に含まないものの数}
  - {type: phrase, text: 与えられた文字列をすべて含む長さ L の文字列の数}
  - {type: constraint, text: N ≤ 10^9〜10^18 で、パターンの長さの総和が小さい}
  - {type: constraint, text: パターンの個数 ≤ 8 程度で、すべてを含むかを問う}
  - {type: shape, text: 長さ i までの文字列の数を、末尾とパターンの先頭が何文字一致しているかで分けて持つ}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc458_f）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: 照合の状態とマルコフ性（次の状態は次の文字だけで決まる。直近の数文字で足りる簡易版は dp-state-design）, anchor: matching-state}
  - {title: KMP オートマトンの遷移表を前計算して DP する, anchor: kmp-automaton}
  - {title: 複数パターンは Aho-Corasick（終端の印を受け継ぐ）, anchor: multiple-patterns}
  - {title: すべて含む：含んだパターンの集合を bit で持つ, anchor: contain-all}
  - {title: N が巨大なとき：遷移行列の累乗・ダブリング, anchor: matrix-power}
  - {title: 包除で解こうとすると破綻する理由（パターンの重なり）, anchor: why-not-inclusion-exclusion}
  - {title: 部分列 DP・桁 DP との違い, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：KMP や Aho-Corasick の状態（いまの接尾辞のうちパターンの接頭辞になっている最長のもの）を DP の状態にして、パターンを含まない・すべて含む長さ N の文字列を数える。N が巨大なら遷移を行列にして累乗する。
    - **いつ使うか**：
        - 長さ N の文字列のうち、どのパターンも部分文字列に含まないものの数
        - 与えられた文字列をすべて含む長さ L の文字列の数
        - N ≤ 10&#94;9〜10&#94;18 で、パターンの長さの総和が小さい
        - パターンの個数 ≤ 8 程度で、すべてを含むかを問う
        - 長さ i までの文字列の数を、末尾とパターンの先頭が何文字一致しているかで分けて持つ
    - **計算量**：（執筆時に書く）
    - **前提**：[KMP 法と文字列の周期](../string/kmp.md)、[行列累乗](../math/matrix-power.md)
