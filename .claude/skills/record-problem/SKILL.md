---
name: record-problem
description: 解けなかった AtCoder の問題を notes/<問題ID>.md に1問1ファイルで記録する（日付・問題のリンク・原因の分類・学んだこと・関連ページ・教材の改善案）。引数は問題 ID か問題の URL（省略可）、または claude.ai の解説が出した「記録用まとめ」の貼り付け。
disable-model-invocation: true
argument-hint: "[問題ID | 問題のURL | 記録用まとめ]"
allowed-tools:
  - Bash(printenv CLAUDE_CODE_REMOTE)
  - Bash(python3 tools/ap.py show *)
  - Bash(python3 tools/ap.py contest *)
  - Bash(python3 .claude/skills/record-problem/record_tool.py *)
---

# 問題を記録する

利用者が残したいと思った問題を `notes/<問題ID>.md` に記録する。利用者が `/record-problem` と打ったときだけ使う。

## 守ること

- **atcoder.jp・codeforces.com を開かない**（noai 指定）。問題の実在・題名・difficulty は `python3 tools/ap.py` だけで確かめ、記憶で補わない
- **1問1ファイル**。同じ問題のファイルがあれば、新しく作らずに追記する
- **集計しない**（件数・傾向・一覧を出さない）。`notes/` は git の追跡外（.gitignore 済み）なので、git add・commit もしない
- **クラウドのセッションでは使わない**。書いた記録が手元に残らないため。最初に `printenv CLAUDE_CODE_REMOTE` を実行し、`true` と出たら何も書かずに「手元の Claude Code で使う」と伝えて終える
- コマンドはリポジトリの根で実行する。以下の `record_tool.py` は `python3 .claude/skills/record-problem/record_tool.py` のこと

## 手順

1. **入力を読む**。引数は末尾の「入力」にある。空なら、問題 ID か記録用まとめを聞く
   - `# >>> 記録用まとめ` の行があれば、`claude/record-format.md` を読み、その形で読む。終わりの目印の行がなければ切れているので、貼り直してもらう。まとめが複数あれば1つずつ記録する
   - 問題の URL なら `/tasks/` の後ろを ID にする（URL は開かない）。「ABC300 E」のような名前なら `python3 tools/ap.py contest abc300` で ID を引く
2. **問題を確かめる**：`python3 tools/ap.py show <ID> --json`
   - NG（見つからない）かキャッシュがないときは、`python3 tools/ap.py fetch --force` を **1回だけ** 実行して show をやり直す。AtCoder Problems の API は間隔を空けて使う方針なので、1回の `/record-problem` で2度は取得しない
   - それでも見つからなければ ID の誤りを疑い、利用者に確かめる。正しいと言われたら、title を「未確認」、difficulty を「未定」、contest を ID の最後の `_` より前、url を `https://atcoder.jp/contests/<contest>/tasks/<ID>` にして記録する
   - difficulty が null なら「未定」と書く
3. **中身をそろえる**
   - 貼り付けがなければ、1回のメッセージで短く聞く：原因（知識不足／気づけなかった／実装ミス／時間不足）、学んだことを一言、関連ページ（手法の名前でよい）、教材の改善案（なければ「なし」）
   - 関連ページの候補は `record_tool.py pages --problem <ID> <語>…` で出す。docs/ の front matter の id・題名・別名・節から探し（ページがまだなければ planning/catalog/ から）、台帳にある問題は結び付いたページが先に出る。利用者が選んだものだけを書く
   - 貼り付けの関連ページは `record_tool.py url <id>…` で確かめ、id と URL を出力に合わせる。NG のものは候補を示して利用者に確かめる
   - 原因が4つのどれでもない、学んだことがない、といった欠けは利用者に聞く（解けたが残したいときは、原因を null にする）
4. **書く**：下の形で `notes/<ID>.md` に書く
   - ファイルがなければ作る。あれば読み、records の末尾に1件、本文の末尾に節を1つ足す。ほかの部分（利用者が手で書いたところを含む）は変えない。title が「未確認」・difficulty が「未定」で、今は分かるなら、そこと見出しだけ書き換える
   - 同じ日付で同じ学んだことの記録がもうあれば、重ねずに利用者に確かめる
   - 書いたら `record_tool.py check notes/<ID>.md` を実行し、NG があれば直す
5. **伝える**：書いたファイルのパスと、記録した中身を2〜3行で

## notes/<ID>.md の形

```markdown
---
problem: abc300_e
contest: abc300
title: "E. Dice Product 3"
url: https://atcoder.jp/contests/abc300/tasks/abc300_e
difficulty: 1354
records:
  - date: 2026-10-21
    cause: 気づけなかった
    learned: "状態が変わらない遷移（自己ループ）は、式を移項してから計算する"
    pages:
      - id: expected-value-dp#self-loop
        url: https://yuukougun.github.io/kyopro-atlas/comb/expected-value-dp/#self-loop
    improvement: null
---

# [abc300_e E. Dice Product 3](https://atcoder.jp/contests/abc300/tasks/abc300_e)

## 2026-10-21（気づけなかった）

1 の目で同じ値に戻る項を、右辺に残したまま止まっていた。移項すると残り 5 つの目の平均になる。
```

- problem・contest・title・url・difficulty は、`ap.py show --json` の id・contest_id・title・url・difficulty を写す
- records は記録1回につき1件、古い順。項目の意味は `claude/record-format.md` と同じ。date は記録用まとめにあればその日、なければ今日。pages がなければ `[]`、improvement がなければ null
- title・learned・improvement は二重引用符で囲む
- 本文は、最初に問題へのリンクの見出しを1つ置き、記録ごとに「## 日付（原因）」の節を立てる（原因が null なら日付だけ）。節の中身は記録用まとめの memo か利用者の言葉で2〜3行（どこで詰まったか・鍵になった見方）。なければ learned を1行。問題文は写さない

## 入力

$ARGUMENTS
