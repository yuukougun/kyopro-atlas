---
id: prefix-sum-counting
title: 累積和と連想配列で区間を数える
aliases: [Zero-Sum Ranges, 区間和が K, 余りが等しい組を数える, 累積和の mod, subarray sum equals K]
type: technique
field: basics
chapter: 累積和といもす法
order: 130
level: 基礎
kind: [累積和・差分]
prerequisites: [prefix-sum]
related: [two-pointers, reformulation, stl-containers]
summary: 和がちょうど K の区間や和が M の倍数の区間の個数を、条件を S_r と S_l の関係に言い換えて数える。左から S_l の個数を連想配列に記録しながら組を足していく。
complexity: null
signs:
  - {type: phrase, text: 和がちょうど K の区間の個数}
  - {type: phrase, text: 和が M の倍数になる区間の個数}
  - {type: constraint, text: −10^9 ≤ A_i ≤ 10^9 のように負の値を含む}
  - {type: shape, text: 区間の条件が S_r と S_l の関係（差が K・余りが等しい）に書き直せる}
acl: []
frequency: A
frequency_evidence: recent 2（abc455_e・abc473_e）・前提として届くページなし・古い ABC 5 問
sections:
  - {title: S_r − S_l = K となる l を数える（S_0 を入れ忘れない）, anchor: equal-k}
  - {title: 余りが等しい組（M の倍数の区間・負の余りの正規化）, anchor: same-remainder}
  - {title: 後ろからの累積（数字列の倍数）, anchor: suffix}
  - {title: 円環を伸ばして数える, anchor: circular}
  - {title: 長さの制限付き（窓の中だけで数える）, anchor: length-limited, level: 青}
  - {title: 尺取りとの使い分け（負の値）, anchor: vs-two-pointers}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：和がちょうど K の区間や和が M の倍数の区間の個数を、条件を S_r と S_l の関係に言い換えて数える。左から S_l の個数を連想配列に記録しながら組を足していく。
    - **いつ使うか**：
        - 和がちょうど K の区間の個数
        - 和が M の倍数になる区間の個数
        - −10^9 ≤ A_i ≤ 10^9 のように負の値を含む
        - 区間の条件が S_r と S_l の関係（差が K・余りが等しい）に書き直せる
    - **計算量**：（執筆時に書く）
    - **前提**：[累積和](../basics/prefix-sum.md)
