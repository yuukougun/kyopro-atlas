---
id: cpp-io
title: 入出力と定数倍
aliases: [入出力, fast I/O, cin.tie(nullptr), sync_with_stdio, endl, println, 'std::print', 'std::format', printf, setprecision, fixed, 小数の出力, fflush(stdout), TLE になる書き方, 入出力が遅い]
type: cpp
field: cpp
chapter: 入出力・環境・落とし穴
order: 180
level: 基礎
kind: [実装・C++, 計算量]
prerequisites: []
related: [cpp-types-literals, cpp-integer-overflow, acl-reading, interactive, complexity-estimation, debugging-checklist]
summary: 入出力を速くし（sync_with_stdio・cin.tie）、println・小数の桁の指定・インタラクティブ問題のフラッシュを正しく書く。C++ の書き方が原因で TLE になる例も、計測つきで示す。
complexity: null
signs:
  - {type: constraint, text: 入力や出力が 10^6 個程度ある（入出力の書き方で実行時間に差が出る）}
  - {type: phrase, text: 答えの絶対誤差または相対誤差が 10^-6 以下なら正解とする（小数の桁を指定して出力しないと WA になる）}
acl: []
sections:
  - {title: '入出力の高速化：ios::sync_with_stdio(false); cin.tie(nullptr);（10^6 個の入力で約 0.15 秒の差）', anchor: fast-io}
  - {title: endl は改行のたびに書き出す（10^6 行で約 0.2 秒余計にかかる）、普段は改行文字 '\n' を出す, anchor: endl}
  - {title: '区切りと改行の書き方：cout << a[i] << " \n"[i == n - 1]、cond ? "Yes" : "No"', anchor: separators}
  - {title: 入力の終わりまで読む：while (cin >> x), anchor: read-until-eof}
  - {title: printf・scanf と書式, anchor: printf}
  - {title: 'std::format（C++20・GCC 13〜）と std::print・println（C++23・GCC 14〜。引数なしの println() も通る）', anchor: format-println}
  - {title: '書式の指定：幅・左寄せ・0 埋め・2 進・16 進・小数の桁（{:5}・{:<5}・{:05}・{:b}・{:x}・{:.3f}）（C++20・GCC 13〜）', anchor: format-spec}
  - {title: '小数の出力：cout は有効数字 6 桁（123456789.0 が 1.23457e+08 になる）、fixed << setprecision(15)・{:.15f}・printf("%.15f")', anchor: float-output}
  - {title: '同期を切った後に println・printf と cout を混ぜると順番が入れ替わる（println(cout, ...) なら混ざらない）', anchor: mixing-streams}
  - {title: インタラクティブ問題のフラッシュ：出力がパイプのときは cout << endl か fflush(stdout) が要る, anchor: flush}
  - {title: 'そのままでは出力できない型：__int128・modint（.val() を出す）、vector は println("{}", v) で [1, 2, 3] と出て AtCoder の形式にならない（C++23・GCC 15〜）', anchor: unprintable-types}
  - {title: 'C++ 側で TLE になる書き方の一覧と計測（endl・同期・std::function の再帰・set への std::lower_bound・s = s + c・vector の値渡し。views::iota は普通の for と同じ速さ）', anchor: tle-causes}
stage: stub
updated: 2026-10-21
cpp_std: null
gcc_min: null
atcoder: true
---

!!! abstract "要点"
    - **何ができるか**：入出力を速くし（sync_with_stdio・cin.tie）、println・小数の桁の指定・インタラクティブ問題のフラッシュを正しく書く。C++ の書き方が原因で TLE になる例も、計測つきで示す。
    - **いつ使うか**：
        - 入力や出力が 10^6 個程度ある（入出力の書き方で実行時間に差が出る）
        - 答えの絶対誤差または相対誤差が 10^-6 以下なら正解とする（小数の桁を指定して出力しないと WA になる）
    - **計算量**：（執筆時に書く）
    - **前提**：なし
