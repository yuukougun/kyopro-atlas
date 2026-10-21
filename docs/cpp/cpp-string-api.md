---
id: cpp-string-api
title: 文字列の操作
aliases: [string, substr, 'string::find', npos, to_string, stoi, stoll, starts_with, ends_with, string_view, s += c, getline, c - 'a', 文字と数の変換]
type: cpp
field: cpp
chapter: コンテナ・アルゴリズム・ACL
order: 140
level: 基礎
kind: [実装・C++]
prerequisites: []
related: [string-basics, cpp-views-basics, cpp-io, cpp-undefined-behavior, run-length-encoding]
summary: std::string の操作（substr・find・+=・数との変換）と string_view を、計算量と寿命に気をつけて書く。s = s + c が全体をコピーして遅いことや、cin >> の後の getline の罠を防ぐ。
complexity: null
signs: []
acl: []
sections:
  - {title: 'substr(i, len) は O(len) のコピー、find は見つからないと string::npos', anchor: substr-find}
  - {title: s += c と s = s + c（後者は毎回全体をコピーして O(|s|)。先頭に足すなら後ろに足して最後に reverse）, anchor: append}
  - {title: 文字と数の変換：c - 'a'・char('a' + i)・c - '0', anchor: char-arithmetic}
  - {title: to_string（double は小数点以下 6 桁）・stoi・stoll, anchor: to-string}
  - {title: starts_with・ends_with（C++20）、contains（C++23）, anchor: starts-with}
  - {title: 'string(n, c)・reverse・辞書順の比較', anchor: construct-compare}
  - {title: string_view：コピーしない部分文字列。一時的な string を入れると壊れる（C++17）, anchor: string-view}
  - {title: '区切る：views::split('' '') と string_view(w)（C++20）', anchor: split}
  - {title: cin >> s は空白で区切る、cin >> の後に getline を使うと残った改行を読む, anchor: getline}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：std::string の操作（substr・find・+=・数との変換）と string_view を、計算量と寿命に気をつけて書く。s = s + c が全体をコピーして遅いことや、cin >> の後の getline の罠を防ぐ。
    - **いつ使うか**：（執筆時に書く）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
