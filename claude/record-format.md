# 記録用まとめの形式（v2）

claude.ai の解説が、頼まれたときだけ出す「記録用まとめ」の形を決める。利用者はこれを手元の Claude Code の記録用スキル `/record-problem`（`.claude/skills/record-problem/SKILL.md`）に貼り付け、`notes/<問題ID>.md` に記録する。形はこのファイルだけで決め、解説の手順（`claude/explain.md`）とスキルの両方がここを参照する。形を変えたら版を上げ、スキルも合わせて直す。

v2（2026-11-13）で、任意の項目 `support`・`status`・`code` を足した。v1 のまとめも、足した 3 項目がないものとしてそのまま受け付ける。スキルは、精進用の作業フォルダなど kyopro-atlas の外で起動したセッションからも使える（そのセッションの会話から、まとめを貼らずに記録の案を出すこともある）。

使い方：claude.ai で「記録用まとめを出して」と頼む → 出たコードブロックをコピーのボタンで写す → 手元の Claude Code で `/record-problem` に続けて貼り付ける（`/record-problem` だけ打ち、聞かれてから貼ってもよい）。

## 出すとき（claude.ai の解説）

- **利用者に頼まれたときだけ出す**。解説の終わりに自分から出さない
- 下の形を **1つのコードブロック**（言語は yaml）で出す。目印の2行もブロックに入れ、ブロックの中に説明を書かない
- **問題 ID・ページの id と URL を推測で書かない**。問題 ID は利用者が示した URL か ID から取り、スクリーンショットだけで分からなければ null にする。ページは索引（`docs/llms.txt`・`docs/index/<field>.md`）で確かめたものだけを書く
- 問題の題名と difficulty は書かない（スキルが AtCoder Problems のデータで確かめて書く）
- 問題文や解説の文章を写さず、自分の言葉で短く書く。learned・improvement・memo は二重引用符で囲む

## 形

```yaml
# >>> 記録用まとめ v2
problem: abc300_e
date: 2026-10-21
cause: 気づけなかった
learned: "状態が変わらない遷移（自己ループ）は、式を移項してから計算する"
pages:
  - id: expected-value-dp#self-loop
    url: https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#self-loop
  - id: rational-mod
    url: https://yuukougun.github.io/kyopro-atlas/comb/rational-mod/
improvement: "自己ループの節に、期待値ではなく確率を求める例も置く"
memo: "1 の目で同じ値に戻る項を、右辺に残したまま止まっていた。移項すると残り 5 つの目の平均になる"
support: ヒントだけ
status: AC
code: null
# <<< 記録用まとめ ここまで
```

## 項目

| 項目 | 書くこと | ないとき |
| --- | --- | --- |
| `problem` | AtCoder の問題 ID（問題の URL の `/tasks/` の後ろ。例 `abc300_e`） | null（スキルが利用者に聞く） |
| `date` | 解説した日（YYYY-MM-DD） | null（記録した日になる） |
| `cause` | 解けなかった原因を1つ：`知識不足`・`気づけなかった`・`実装ミス`・`時間不足`。重なるときは、いちばん大きいもの。問題文の誤読は、読み直せば防げたミスとして `実装ミス` に含める | null（解けたが残したいときなど） |
| `learned` | 学んだことを一言（1文） | 書く（なければスキルが聞く） |
| `pages` | 関連ページ（3件まで）。`id` はページの id（節は `id#anchor`）、`url` は索引にある URL（節はアンカー付き） | `[]` |
| `improvement` | 教材の改善案（足りない説明・分かりにくい箇所・教材にない知識など） | null |
| `memo` | 記録の本文に入れる2〜3行（どこで詰まったか・鍵になった見方） | null |
| `support`（v2・任意） | 使った助けのうち最も強いもの。弱い順に `自力`（ヒントも解説も使っていない）・`ヒントだけ`（手法の名前や気づくべき点だけ）・`解説まで`（方針・正しさ・実装の要点まで説明を受けた）・`ギブアップ`（自分で解くのをやめ、公式の解説・他人の提出・完全な解答コードを見た）。途中で切り替えたら強い方。原因（なぜ解けなかったか）とは別に残す | null |
| `status`（v2・任意） | その記録の時点で AC したか：`AC`・`未AC`。記録ごとに持ち、今の状態は、null でない最後の記録の値で見る。解き直しの要る問題を後で探す手がかり | null |
| `code`（v2・任意） | 自分の解答ファイルのパス（記録したフォルダから見た相対パスなど）。kyopro-atlas は中身を読まず、文字列として残すだけ | null |

## 受け取るとき（記録用スキル）

- 目印の2行の間だけを読む。終わりの目印がなければ貼り付けが切れているので、貼り直してもらう
- 問題は AtCoder Problems のデータ（スキルの `record_tool.py ap`、中身は `tools/ap.py`）、ページの id と URL は docs/ の front matter で確かめ直す。null や欠けは利用者に聞く
- 版が v1・v2 でなければ、このファイルの今の定義に照らして読む。v1 には support・status・code がないので、書かない（null と同じ）
