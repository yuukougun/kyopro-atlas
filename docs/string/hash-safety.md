---
id: hash-safety
title: ハッシュの衝突と安全な設計
aliases: [ハッシュの衝突確率, 誕生日のパラドックス, mod 2^61-1, ハッシュの mod の選び方, anti-hash, ハッシュが落とされる, unordered_map の衝突, カスタムハッシュ, hash collision]
type: technique
field: string
chapter: ハッシュ
order: 50
level: 青
kind: [ハッシュ・乱択]
prerequisites: [rolling-hash]
related: [hashing-for-sets, randomized, cpp-math-functions#random, cpp-container-idioms#unordered-map, tree-isomorphism]
summary: 比べるハッシュの組の数から衝突確率を見積もり、固定のテストでも落ちない mod と基数を選ぶ。mod 10^9 程度の 1 つでは全ペアの比較に耐えないので、mod 2^61−1 と実行時に乱択した基数（値のハッシュなら素数）を使う。
complexity: null
signs:
  - {type: phrase, text: ハッシュ値を set や map に大量に入れて重複を数える}
  - {type: phrase, text: 1000 桁程度の巨大な数の積や和が一致するかを判定する}
  - {type: constraint, text: 比べ合うハッシュが 10^5 個以上（組が 5×10^9 以上）}
acl: []
verify: []
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 2 問
sections:
  - {title: 衝突確率の見積もり：比較の回数ではなく組の数（誕生日のパラドックス）, anchor: birthday-bound}
  - {title: mod 2^64 が破られる理由（Thue-Morse 列。奇数のどの基数でも長さ 1024 で衝突する）, anchor: mod-2-64}
  - {title: 推奨する設計：mod 2^61−1・乱択した基数・除算を使わない剰余, anchor: recommended-design}
  - {title: 多項式ハッシュは基数を、値のハッシュは mod（素数）を乱択する, anchor: what-to-randomize}
  - {title: AtCoder で狙われる条件（事前に固定されたテストと、誰でも使う固定の選択）, anchor: atcoder-tests}
  - {title: 二重ハッシュとの比較, anchor: double-hashing}
  - {title: unordered_map への攻撃と、乱数を混ぜたカスタムハッシュ, anchor: unordered-map}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：比べるハッシュの組の数から衝突確率を見積もり、固定のテストでも落ちない mod と基数を選ぶ。mod 10^9 程度の 1 つでは全ペアの比較に耐えないので、mod 2^61−1 と実行時に乱択した基数（値のハッシュなら素数）を使う。
    - **いつ使うか**：
        - ハッシュ値を set や map に大量に入れて重複を数える
        - 1000 桁程度の巨大な数の積や和が一致するかを判定する
        - 比べ合うハッシュが 10^5 個以上（組が 5×10^9 以上）
    - **計算量**：（執筆時に書く）
    - **前提**：[ローリングハッシュ](../string/rolling-hash.md)
