# merge-process-tree の報告（b4）

- 書いたファイル：docs/tree/merge-process-tree.md、snippets/merge-process-tree/usage.{cpp,yaml}、docs/img/merge-process-tree/merge-tree.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-22）。sections に `{title: 自作するときの要点と Library Checker, anchor: library}` を足した。`## 学ぶための資料 {#resources}` は hld と同じく sections に載せていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 7：数式・リンクを含む文の長さ、要点の囲みの文の長さ、台帳の要約の行の長さと `[` の対の誤検出、「に」の重複 1 件）。図は render_svg で 360・720 の幅を目で確かめた
- 使った出典：drken の abc183_f・agc002_d の記事、mzhang2021.github.io（check_noai で noai なしを確認。付録 B への追加を提案）、oi-wiki.org（付録 B にある）、ACL の document_ja、library-checker-problems の GitHub（問題の一覧）
- 動く図は作っていない（visual は static・priority 2 なので静的な SVG 1 枚で済ませた）

## 台帳への提案

- agc002_d：evidence に、併合過程の木の解き方を説明した第三者の記事がない。drken の記事は併合過程の木をカテゴリーの札でしか示していない（本文は部分永続 Union-Find と並列二分探索）。alternatives の merge-process-tree の approach は論理として正しく（グループの大きさは時刻について単調で、判定はコード片の group で行える）、本文の方針もこの形で書いたが、裏付けの記事が見つかれば evidence に足したい
- agc002_d：evidence の 1 件目 cp-algorithms の二分探索の記事は問題に固有の解説ではない（参考程度）。差し替えてよい

## 用語集への提案

- なし（代表元・オフライン・ボトルネックは既存の語にリンクした）

## 手引きへの提案

- 付録 B に mzhang2021.github.io を足す（2026-10-22、noai・noimageai の指定なし、規約の記述なし）

## ほかのページへの申し送り（メインの判断）

- bottleneck-path#reconstruction-tree との分担（handoff-b2b3 §2）：本ページは木の作り方・グループの区間・自作の要点を持ち、MST との関係と使い分けは bottleneck-path#reconstruction-tree に任せて節へリンクした。bottleneck-path 側の「木の作り方の詳細は併合過程の木のページにある」のページへのリンクは、#new-vertex への節のリンクに張り替えられる。「重み x 以下の辺で v から行ける頂点」の段落は #group-as-interval へ張れる
- ページへのリンクで本ページを指している partially-persistent-union-find#alternatives・parallel-binary-search#alternatives・small-to-large（例題 abc183_f の別解と使い分けの表）は、#group-as-interval・#bottleneck・#alternatives へ張り替えられる

## 問題の補充の候補

- abc235_h（handoff-b2b3 の申し送り、03-graph の研究にあり）：同じ重みの辺で成分がまとまる過程で塗り方を数える（diff 2967 の見込み）。力試しの候補。台帳になく、ap.py での確認と第三者の解説での裏付けは今回していない
- abc394_g（台帳で確認済み、bottleneck-path・small-to-large の練習）：2 つの建物がつながる最大のしきい値を多数答える。最大全域木の向きの併合過程の木で LCA の重みを取れば答えられるが、evidence の kmjp の記事は併合過程の木の解き方ではないので、本ページへは載せていない

## 未解決の点

- agc002_d の併合過程の木による解き方を明示した第三者の解説は見つからなかった（上記）
- Library Checker に併合過程の木を直接確かめる問題はない（tree・graph・datastructure の一覧で確認）。部品として lca・jump_on_tree を挙げた

## 使用量の目安

- 道具の呼び出し 約 30 回、Web 取得 4 回・検索 5 回

## 検証の指摘への対応（b4 直し）

- 指摘 1〜10 はすべて採った。1：部分永続 Union-Find で持てるもの（和・最大値）と持てないもの（種類ごとの個数・k 番目）を分けた。2：#group-as-interval の Confluence の名指しと解き方を除き、一般の形にした。3：導入の強みと #alternatives の箇条 3 を、比べる相手ごとの差に書き直した。4：「多い」を「出題は少なく、…現れる」にした。5：「$p$ の重みの時刻に」と、親を作る併合・根の場合を書いた。あわせて図の例（x = 4、t = 3）を本文に足した。6：番兵の役割を単調性に書き直し、`group` が葉の重みを読まないことを書いた。7：usage.cpp のコメントと #bottleneck に $u = v$ の約束を足した。8：表の列名を「質問の答え方」にし、並列二分探索の行に 1 段の量を書いた。9：図の右上に「橙：x = 4、t = 3 の例」を足し、代替テキストにも書いた（render_svg の 360px で確認）。10：Stamp Rally の方針に単調性の理由を足した
- 採らなかったもの：なし
- 台帳への提案（検証から引き継ぐ）：agc002_d の summary を問いだけの文（alternatives にある文）に替え、3 ページの行を fix_problems で作り直す。agc002_d・abc183_f の checked を 2026-10-22 に
