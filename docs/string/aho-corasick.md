---
id: aho-corasick
title: Aho-Corasick 法
aliases: [AC オートマトン, 失敗リンク, 複数パターン照合, 禁止語, Aho-Corasick algorithm]
type: technique
field: string
chapter: Trie と照合オートマトン
order: 100
level: 青
kind: [文字列]
prerequisites: [trie, kmp, bfs]
related: [string-automaton-dp, suffix-array, rolling-hash, matrix-power]
summary: パターンの Trie に失敗リンク（Trie にある最長の真の接尾辞へのリンク）を BFS 順に張り、全文字の遷移を埋めたオートマトンにする。テキストを 1 回流すだけで、多数のパターンの出現をまとめて数えられる。
complexity: null
signs:
  - {type: phrase, text: 多数のパターンそれぞれの、テキスト中の出現回数}
  - {type: phrase, text: どのパターンも含まない（すべて含む）文字列の数}
  - {type: phrase, text: 禁止語を含まないように最少の文字を書き換える}
  - {type: constraint, text: パターンの長さの総和が 10^5〜10^6 で、パターンの個数も多い}
acl: []
verify: [aho_corasick]
frequency: B
frequency_evidence: recent 1（abc458_f）・前提として届くページなし・古い ABC 3 問
sections:
  - {title: Trie と失敗リンク（KMP の π を Trie に一般化したもの）, anchor: failure-links}
  - {title: BFS 順に失敗リンクを張る理由と、全文字の遷移表の埋め方, anchor: build}
  - {title: 出現回数の集計：訪問回数を失敗リンクの木で葉から根へ足す（出現のたびにたどると遅い）, anchor: count-occurrences}
  - {title: 終端の印を失敗リンク先から受け継ぐ, anchor: inherit-terminal}
  - {title: 照合オートマトンとして使う（DP・行列累乗）, anchor: as-automaton}
  - {title: 禁止語の貪欲：一致したら書き換えて状態を根に戻す, anchor: forbidden-greedy, level: 黄}
  - {title: SA の二分探索・ハッシュとの使い分け, anchor: comparison}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：パターンの Trie に失敗リンク（Trie にある最長の真の接尾辞へのリンク）を BFS 順に張り、全文字の遷移を埋めたオートマトンにする。テキストを 1 回流すだけで、多数のパターンの出現をまとめて数えられる。
    - **いつ使うか**：
        - 多数のパターンそれぞれの、テキスト中の出現回数
        - どのパターンも含まない（すべて含む）文字列の数
        - 禁止語を含まないように最少の文字を書き換える
        - パターンの長さの総和が 10&#94;5〜10&#94;6 で、パターンの個数も多い
    - **計算量**：（執筆時に書く）
    - **前提**：[Trie](../string/trie.md)、[KMP 法と文字列の周期](../string/kmp.md)、[幅優先探索（BFS）と無重み最短路](../graph/bfs.md)
