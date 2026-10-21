---
id: cpp-reverse-index
title: C++ の逆引き
aliases: [解説コードの読み方, 解説コードが読めない, モダン C++ の読み方, 書き方から引く, 症状から引く, Segmentation fault, コンパイルエラーの読み方, エラーメッセージ, required from here]
type: guide
field: cpp
order: 10
level: null
kind: [実装・C++, 案内]
prerequisites: []
related: [cpp-environment, cpp-undefined-behavior, debugging-checklist, reverse-index-signs, glossary]
summary: 解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。1 行を「何を回すか・何を受け取るか・どう受け取るか」に分けて読む手順も示す。
complexity: null
signs: []
acl: []
sections:
  - {title: 1 行の読み方：何を回すか・何を受け取るか・どう受け取るかに分ける, anchor: how-to-read}
  - {title: 書き方から引く：型・リテラル・初期化・数の関数, anchor: lookup-types}
  - {title: 書き方から引く：参照・構造化束縛・組, anchor: lookup-references}
  - {title: 書き方から引く：ラムダ・再帰・テンプレート, anchor: lookup-lambda}
  - {title: 書き方から引く：雛形とマクロ, anchor: lookup-macros}
  - {title: 書き方から引く：コンテナ・比較関数・アルゴリズム・文字列, anchor: lookup-containers}
  - {title: 書き方から引く：views, anchor: lookup-views}
  - {title: 書き方から引く：入出力, anchor: lookup-io}
  - {title: 書き方から引く：ACL, anchor: lookup-acl}
  - {title: '混同しやすい書き方の対（std::iota と views::iota、unique と erase など）', anchor: confusing-pairs}
  - {title: 症状から引く：WA・RE・TLE と、手元と AtCoder で結果が違うとき, anchor: symptoms}
  - {title: 'コンパイルエラーのメッセージから引く（最初の error: の行と、required from here で自分の行を探す読み方を含む）', anchor: compile-errors}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何のページか**：解説コードの書き方・実行時の症状・コンパイルエラーのメッセージから、意味と C++ 章の該当する節を引く。1 行を「何を回すか・何を受け取るか・どう受け取るか」に分けて読む手順も示す。
    - **使い方**：（執筆時に書く）
