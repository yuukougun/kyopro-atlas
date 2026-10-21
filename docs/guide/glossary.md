---
id: glossary
title: 用語集
aliases: [用語, 略語, 用語の定義, 表記の正規形]
type: guide
field: guide
chapter: 早見表と資料
order: 140
level: null
kind: [案内]
prerequisites: []
related: [notation, term-index, cheatsheet]
summary: 本文で使う用語の短い定義と、表記の正規形（セグ木とセグメント木、Union-Find と DSU など）を引ける。本文の用語の最初の出現からリンクされ、表記の検査（prh）の元にもなる。
complexity: null
signs: []
acl: []
sections:
  - {title: ジャッジとコンテスト, anchor: judge}
  - {title: AtCoder の用語, anchor: atcoder}
  - {title: 慣用句, anchor: slang}
  - {title: 計算量の用語, anchor: complexity}
  - {title: 手法一般とデータ構造・代数, anchor: techniques}
  - {title: 数学・グラフと木・文字列と幾何・実装, anchor: domains}
  - {title: 表記の正規形と別名の対応表, anchor: canonical-forms}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：本文で使う用語の短い定義と、表記の正規形（セグ木とセグメント木、Union-Find と DSU など）を引ける。本文の用語の最初の出現からリンクされ、表記の検査（prh）の元にもなる。
    - **使い方**：（執筆時に書く）

## 手法一般とデータ構造・代数 {#techniques}

### 状態 {#state}

探索や DP で、この先の進み方を決めるのに要る情報をひとまとめにしたものである。状態を頂点とみなせば、BFS やダイクストラ法をそのまま使える。

### 番兵 {#sentinel}

配列の端や探索の範囲の外に置く、調べなくても結果が分かっている値や位置である。端の場合分けを減らすのに使う。C++ の ranges では、範囲の終わりを表すイテレータとは別の型のものも番兵（sentinel）と呼ぶ。

### 半開区間 {#half-open-interval}

左端を含み右端を含まない区間 $[l, r)$ である。長さが $r - l$ になり、隣り合う 2 つの区間 $[l, m)$ と $[m, r)$ に重なりなく分けられる。

### 結合法則 {#associativity}

演算 $\cdot$ が、どの $a, b, c$ についても $(a \cdot b) \cdot c = a \cdot (b \cdot c)$ を満たすことである。計算をまとめる順番を変えても結果が同じなので、区間を分けて計算した結果をつなげられる。

### 単位元 {#identity-element}

演算 $\cdot$ で、どの $a$ についても $e \cdot a = a \cdot e = a$ となる要素 $e$ である。和なら 0、積なら 1、最小値なら $+\infty$ が単位元になる。

### モノイド {#monoid}

結合法則を満たす演算と、その演算の単位元をもつ集合の組である。セグメント木に載せられるのは、モノイドをなす値と演算である。

### 遅延評価 {#lazy-evaluation}

値が実際に要るときまで計算を先送りすることである。C++ の views は、要素を取り出すときに初めてその要素を計算する。

## 数学・グラフと木・文字列と幾何・実装 {#domains}

### 正しい括弧列 {#balanced-parentheses}

`(` と `)` からなる文字列で、`(` を $+1$、`)` を $-1$ とした累積和が途中で負にならず、最後は 0 で終わるものである。空の文字列も正しい括弧列とする。

### 重い辺 {#heavy-edge}

根付き木の各頂点から、部分木の大きさが最大の子へ向かう辺である（HL 分解の用語）。ほかの子への辺は軽い辺と呼ぶ。

### 重いパス {#heavy-path}

重い辺だけをつないでできるパスである。木の頂点は重いパスに分かれ、どの頂点から根へ向かっても、通る重いパスは $O(\log N)$ 本である。

### 固定点 {#fixed-point}

写像 $f$ で $f(x) = x$ となる $x$ である。順列 $p$ では、$p_i = i$ となる位置 $i$ を指す。

### 指示確率変数 {#indicator}

ある事象が起きたら 1、起きなければ 0 をとる確率変数である。その期待値は事象の確率に等しいので、個数を指示確率変数の和に分けると、期待値の線形性で確率の和として求められる。

### popcount {#popcount}

整数を 2 進数で表したときの 1 の個数である。C++20 の `std::popcount`（符号なしの型が対象）や GCC の `__builtin_popcount` で求められる。
