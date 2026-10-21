---
id: stack-techniques
title: スタック・キュー・deque の使いどころ
aliases: [stack, queue, 括弧の対応, 打ち消し, 操作の取り消し]
type: technique
field: ds
chapter: スタックとキュー
order: 80
level: 基礎
kind: [データ構造]
prerequisites: [stl-containers]
related: [monotonic-stack, bracket-sequence, persistent-data-structures, run-length-encoding, zero-one-bfs]
summary: スタックで括弧の対応・直前との打ち消し・操作の取り消しを、deque で両端への追加を処理する。ランレングスを積む、円を切り開いて弦の交差判定に帰着する、などの型がある。
complexity: null
signs:
  - {type: phrase, text: 括弧の対応を取る・対応する括弧ごと消す}
  - {type: phrase, text: 特定の並びが現れたら取り除く操作を繰り返した結果}
  - {type: phrase, text: 直前の操作を取り消す（Undo）}
  - {type: phrase, text: 円周上の弦どうしが交差するか}
acl: []
verify: []
frequency: A
frequency_evidence: recent 1（abc454_d）・前提として 60 ページに届く（直接 3）・古い ABC 5 問
sections:
  - {title: 括弧の対応（開き括弧の位置を積む）と括弧列の残高（→ 題材別の括弧列）, anchor: brackets}
  - {title: 直前と打ち消し合うものを消す（末尾を見て pop）, anchor: cancel}
  - {title: 'ランレングスを積む（(値, 個数) の組）', anchor: run-length}
  - {title: 直前の操作を取り消す（変更前の値を積んで戻す。任意の版へ戻るなら永続データ構造）, anchor: undo}
  - {title: deque（両端への追加・真ん中への挿入は deque 2 本）, anchor: deque}
  - {title: 円を切り開いて弦の交差判定に帰着する, anchor: chords, level: 水}
stage: stub
updated: 2026-10-21
---

!!! abstract "要点"
    - **何ができるか**：スタックで括弧の対応・直前との打ち消し・操作の取り消しを、deque で両端への追加を処理する。ランレングスを積む、円を切り開いて弦の交差判定に帰着する、などの型がある。
    - **いつ使うか**：
        - 括弧の対応を取る・対応する括弧ごと消す
        - 特定の並びが現れたら取り除く操作を繰り返した結果
        - 直前の操作を取り消す（Undo）
        - 円周上の弦どうしが交差するか
    - **計算量**：（執筆時に書く）
    - **前提**：[STL コンテナの使い分け](../ds/stl-containers.md)
