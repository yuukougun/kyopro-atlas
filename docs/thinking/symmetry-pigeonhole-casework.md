---
id: symmetry-pigeonhole-casework
title: 対称性・鳩の巣原理・場合分け
aliases: [対称性, 鳩の巣原理, 部屋割り論法, 場合分け, pigeonhole principle, 端の場合を分ける]
type: thinking
field: thinking
order: 90
level: 基礎
kind: [考察]
prerequisites: []
related: [thinking-checklist#q-invariants, periodicity, probability-symmetry#symmetry, game-basics#mirror-strategy, proof-patterns#pigeonhole-remainder, stress-testing#experiment]
summary: 対称性で計算や場合を半分に減らし、鳩の巣原理で「必ず一致が起きる」ことから探索の回数の上限を得る。端の場合（N = 1 など）や大小関係で場合を分けて、それぞれを単純な問題にする。
complexity: null
signs:
  - {type: phrase, text: i < j の組の和など、i と j を入れ替えても同じ形の式}
  - {type: phrase, text: 自分以外の全員の XOR（和）が与えられる}
  - {type: constraint, text: 余りや状態が M 種類しかなく、M + 1 個以上の候補がある}
  - {type: phrase, text: N = 1 や N が小さいときだけ答えの形が違う}
acl: []
frequency: A
frequency_evidence: recent 4（abc457_f・abc459_d・abc462_e・abc463_f）・前提として届くページなし・古い ABC 6 問
sections:
  - {title: 対称性で計算を半分にする（i < j の和・全体の XOR から 1 つ除く）, anchor: symmetry}
  - {title: 対称性で場合を減らす（N ≤ M に入れ替える）, anchor: symmetry-cases}
  - {title: 鳩の巣原理（必ず一致が起きる・探索の打ち切り回数）, anchor: pigeonhole, level: 水}
  - {title: 場合分け（端の場合・大小関係・操作の順序によらないこと）, anchor: casework}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：対称性で計算や場合を半分に減らし、鳩の巣原理で「必ず一致が起きる」ことから探索の回数の上限を得る。端の場合（N = 1 など）や大小関係で場合を分けて、それぞれを単純な問題にする。
    - **いつ使うか**：
        - i < j の組の和など、i と j を入れ替えても同じ形の式
        - 自分以外の全員の XOR（和）が与えられる
        - 余りや状態が M 種類しかなく、M + 1 個以上の候補がある
        - N = 1 や N が小さいときだけ答えの形が違う
    - **計算量**：（執筆時に書く）
    - **前提**：なし
