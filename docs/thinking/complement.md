---
id: complement
title: 余事象
aliases: [補集合, 全体から引く, 少なくとも 1 つ, 2 条件の包除, complementary counting]
type: thinking
field: thinking
order: 40
level: 基礎
kind: [考察, 数え上げ]
prerequisites: []
related: [counting-mindset, inclusion-exclusion]
summary: 「少なくとも 1 つ」「〜でない」ものは、全体から数えやすい補集合を引いて数える。条件が 2〜3 個なら包除原理で重なりを足し引きし、mod での引き算は負にならないように直す。
complexity: null
signs:
  - {type: phrase, text: 〜でないもの・少なくとも 1 つ含むもの}
  - {type: phrase, text: すべて異なる・条件を 1 つでも満たす}
  - {type: phrase, text: A でも B でもないものの個数}
  - {type: shape, text: 直接数えると場合分けが多いが、条件を満たさない側は数えやすい}
acl: []
frequency: B
frequency_evidence: recent 1（abc455_e）・前提として 3 ページに届く（直接 1）・古い ABC 5 問
sections:
  - {title: 全体 − 補集合, anchor: whole-minus-complement}
  - {title: 2〜3 条件の包除（重なりを足し戻す）, anchor: two-conditions}
  - {title: mod の引き算と空集合の扱い, anchor: mod-and-empty}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：「少なくとも 1 つ」「〜でない」ものは、全体から数えやすい補集合を引いて数える。条件が 2〜3 個なら包除原理で重なりを足し引きし、mod での引き算は負にならないように直す。
    - **いつ使うか**：
        - 〜でないもの・少なくとも 1 つ含むもの
        - すべて異なる・条件を 1 つでも満たす
        - A でも B でもないものの個数
        - 直接数えると場合分けが多いが、条件を満たさない側は数えやすい
    - **計算量**：（執筆時に書く）
    - **前提**：なし
