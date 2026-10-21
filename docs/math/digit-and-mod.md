---
id: digit-and-mod
title: 桁と mod
aliases: [九去法, 倍数判定, divisibility rule, 数の連結, 10 倍して a を足す, 部分文字列の余り, 桁和]
type: technique
field: math
chapter: mod の計算
order: 90
level: 水
kind: [整数論, 累積和・差分]
prerequisites: [mod-arithmetic]
related: [geometric-series-mod, prefix-sum-counting, modular-shortest-path, digit-dp, dp-mod-state]
summary: 10 進数の桁を mod で考えて、倍数判定・数の連結 x·10^d + y・部分文字列が P の倍数になる個数を求める。部分文字列は接尾辞の余りが等しい組を数え、P が 2・5 のときは場合を分ける。
complexity: null
signs:
  - {type: phrase, text: 数字列の部分文字列を整数とみて、P の倍数になるものを数える}
  - {type: phrase, text: 桁を消したり並べ替えたりして K の倍数にする}
  - {type: phrase, text: 2 つの数を文字列として連結した数についての条件}
  - {type: constraint, text: '|S| ≤ 2×10^5 の数字列で、部分文字列を全部試すと間に合わない'}
acl: []
verify: []
frequency: B
frequency_evidence: recent 1（abc460_e）・前提として届くページなし・古い ABC 4 問
sections:
  - {title: 倍数判定（3・9 は桁和、4 は下2桁、8 は下3桁、11 は交互和）, anchor: divisibility}
  - {title: 数の連結：x の後ろに d 桁の y を付けると x·10^d + y, anchor: concatenation}
  - {title: 接尾辞の余りで部分文字列を数える（10 と P が互いに素なとき）, anchor: suffix-remainder}
  - {title: P が 2・5 のときの場合分け, anchor: p-2-5}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：10 進数の桁を mod で考えて、倍数判定・数の連結 x·10^d + y・部分文字列が P の倍数になる個数を求める。部分文字列は接尾辞の余りが等しい組を数え、P が 2・5 のときは場合を分ける。
    - **いつ使うか**：
        - 数字列の部分文字列を整数とみて、P の倍数になるものを数える
        - 桁を消したり並べ替えたりして K の倍数にする
        - 2 つの数を文字列として連結した数についての条件
        - |S| ≤ 2×10^5 の数字列で、部分文字列を全部試すと間に合わない
    - **計算量**：（執筆時に書く）
    - **前提**：[mod の計算の基本](../math/mod-arithmetic.md)
