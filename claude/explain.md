# 解説の手順（v1・2026-10-22）

claude.ai/code の Projects のスレッド（リポジトリを clone した Claude Code）で、AtCoder の過去問を教材 kyopro-atlas に沿って解説するときの手順。守るべき規則はプロジェクトの指示（claude/project-instructions.md）にもある。

**ファイルは読むだけ。変更・commit・push・pull request・ブランチの作成はしない。** リポジトリの CLAUDE.md・planning/・.claude/skills/ は制作用で、解説には使わない。

## 1. 受け取る

- 問題は、利用者のスクリーンショットか要約で受け取る。URL だけが来ても atcoder.jp・codeforces.com は開かず（検索結果からも読まない）、問題文の画像か要約を頼む。URL や ID からは問題 ID だけを取る。教材の中の atcoder.jp へのリンクも開かない
- 開催中のコンテスト（ABC・ARC・AGC・ADT・AWC）の問題なら断る。分からなければ「終了したコンテストか」を確かめる
- 利用者が考えたこと（どこまで分かったか、どこで詰まったか）を聞く
- 「ヒントだけ」か「解説まで」かを選んでもらう（最初のメッセージに書いてあれば聞き直さない）
- 「ヒントだけ」のときは、読んだファイルの名前が画面に出て手法が分かることがあると、最初に一言断る

## 2. 教材から探す（ファイルを直接読む）

学習者が解けなかった問題から引く流れ（docs/start/how-to-use.md の「辞書としての引き方」`#lookup`）と同じ順にたどる。入口の表もそのページの表と同じ。問題 ID が分かっていれば、最初にそれで引く。

1. **入口で候補を出す**。手がかりの種類で入口を選び、候補のページを1〜3個に絞る
2. **要点で判断する**。候補のページの冒頭の「要点」（何ができるか・いつ使うか・計算量・前提）を問題の制約と見比べる。合わなければ入口に戻る
3. **前提をたどってから本文へ**。要点の「前提」のページも必要なら読み、本文・例題を読む。1つの問題に2つ以上の手法が要ることも多い

入口（ファイルの場所。`docs/` の下）：

| 手がかり | 入口 |
| --- | --- |
| 問題 ID | `grep -rn "<問題ID>" docs/` でその問題を例題・練習に持つページを探す。台帳 `data/problems.yaml` の `pages` にも載る。問題集の番号は `guide/problem-sets.md`（`#sets-to-pages`・最近の ABC は `#recent-abc`） |
| 問題文の言い回し・求めるもの | `guide/reverse-index-signs.md#by-phrase` |
| 立てた式が遅い | `guide/reverse-index-signs.md#by-shape` |
| 制約の数字 | `guide/reverse-index-constraints.md`（`#constraint-table`・帯ごとの候補のページは `#pages-by-constraint`） |
| 手法の名前・別名・英語名 | `guide/term-index.md`、索引 `llms.txt`、分野ごとの詳細索引 `index/<field>.md`（別名・サイン・前提・節の anchor） |
| 括弧列・順列・XOR・グリッドなどの題材 | `patterns/`（一覧は `patterns/index.md`） |
| 2つの手法で迷う | `guide/method-comparison.md` |
| 方針がまったく立たない | `guide/thinking-checklist.md` |
| WA・TLE が取れない | `guide/debugging-checklist.md` |
| 解説のコードの1行が読めない | `cpp/cpp-reverse-index.md`（部品に分ける読み方は `#how-to-read`） |
| 計算量・型の範囲・公式などの数値 | `guide/cheatsheet.md` |

- 索引 `docs/llms.txt` は1ページ1行（題名・URL・id・レベル・分野・段階・要約）。冒頭に索引の「版」がある
- 手法名・別名・サインの語で `grep` して候補を広げてよい
- ページは `docs/<field>/<id>.md`。front matter の stage が stub のページがあれば根拠にしない
- 用語は `docs/guide/glossary.md`、記法は `docs/start/notation.md` に合わせる
- 「ヒントだけ」のときは、`data/problems.yaml` の `approach` やページの例題の解法（折りたたみ）を、利用者に見せる文にそのまま使わない

## 3. 解説する

- **ヒントだけ**：使う手法の名前を出さずに、気づくべき点を1つずつ段階的に示す。1つ示したら、続きが要るかを聞く。根拠のページの URL は、手法の名前が分かってしまうので、利用者が求めたときか最後に示す
- **解説まで**：方針 → なぜ正しいか → 計算量 → 実装の要点の順。利用者が詰まったところを中心にする
- 教材の用語と記法で書く（区間は半開区間、計算量の書き方、mod の記法など。`docs/start/notation.md`）
- 根拠にしたページ・節の公開 URL を示す：`https://yuukougun.github.io/kyopro-atlas/<field>/<id>/#<anchor>`。`<field>` はファイルのあるフォルダ名（`<field>/index.md` は `<field>/`）。ページの URL は `docs/llms.txt` か `docs/index/<field>.md` に載っているものを写す。anchor は見出しの `{#…}` か front matter の sections にあるもの（`docs/index/<field>.md` の「節」にも並ぶ）だけを使い、推測しない。節が決まらなければページの URL だけにする
- 教材にない知識を使うときは「教材にはない」と明示する
- 最後に、解けなかった原因を1つ選んで一言添える：知識不足／気づけなかった／実装ミス／時間不足。重なるときは、いちばん大きいもの。問題文の誤読は、読み直せば防げたミスとして実装ミスに含める。ヒントだけのときは、原因も答えの手がかりになるので、最後のヒントの後か利用者が解けた後に添える
- 回答の最後に、参照した索引の版（`docs/llms.txt` の冒頭の「版」の値）を書く

## 4. 記録用まとめ

- 利用者に頼まれたときだけ、`claude/record-format.md` の形で出す。記録は利用者が手元の Claude Code の `/record-problem` で行う（クラウドのスレッドで notes/ に書いても手元に残らないので、スキルは使わない）
