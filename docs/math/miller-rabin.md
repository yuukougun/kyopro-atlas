---
id: miller-rabin
title: 大きな数の素数判定と素因数分解
aliases: [ミラー・ラビン, Miller-Rabin, ポラード・ロー, Pollard's rho, Montgomery 乗算, 64bit の素数判定]
type: overview
field: math
chapter: 素数と約数
order: 190
level: 発展
kind: [整数論, ハッシュ・乱択]
prerequisites: [exponent-mod, prime-factorization]
related: [divisor-enum, gcd-lcm, rolling-hash]
summary: 10^18 程度の数の素数判定を Miller-Rabin で、素因数分解を Pollard's rho で期待 O(N^{1/4}) で行う。64bit の法の掛け算には __int128 か Montgomery 乗算を使う。
complexity: null
signs:
  - {type: constraint, text: N ≤ 10^18 の素数判定・素因数分解（√N の試し割りでは間に合わない）}
  - {type: phrase, text: 非常に大きい数が素数かを多数判定する}
acl: []
verify: [primality_test, factorize]
frequency: C
frequency_evidence: recent 0・前提として届くページなし・古い ABC 0 問
sections:
  - {title: Miller-Rabin の判定の仕組み（フェルマーの小定理と −1 の現れ方）, anchor: miller-rabin}
  - {title: '決定的な底（32bit は {2, 7, 61}、64bit は 7 個の底）', anchor: deterministic-bases}
  - {title: Pollard's rho（x ← x² + c の周期と gcd）, anchor: pollard-rho}
  - {title: 64bit の法での掛け算（__int128・Montgomery・Barrett）, anchor: mulmod}
  - {title: 'ACL の内部実装（internal::is_prime_constexpr）', anchor: acl-internal}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：10^18 程度の数の素数判定を Miller-Rabin で、素因数分解を Pollard's rho で期待 O(N^{1/4}) で行う。64bit の法の掛け算には \_\_int128 か Montgomery 乗算を使う。
    - **いつ使うか**：
        - N ≤ 10^18 の素数判定・素因数分解（√N の試し割りでは間に合わない）
        - 非常に大きい数が素数かを多数判定する
    - **計算量**：（執筆時に書く）
    - **前提**：[フェルマーの小定理と指数の mod](../math/exponent-mod.md)、[素因数分解とルジャンドルの公式](../math/prime-factorization.md)
