# interactive（インタラクティブ問題）の執筆の報告

- 書いたファイル：docs/misc/interactive.md、snippets/interactive/boundary.{cpp,yaml}、snippets/interactive/bits.{cpp,yaml}、docs/img/interactive/halving.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、check_snippets（2 片・期待と違う 0）、fix_problems --check（このページの行はなし。ほかの担当のページ tree/complete-binary-tree・tree/small-to-large に直すべき行が残っている）、textlint（エラー0・警告6。数式内の読点、「適応的」を「適用」と誤検出、台帳の summary の「が」、折りたたみの箇条書きが句点なしで 1 文につながる長さの誤検出）
- 図：Mermaid の sequenceDiagram（形式の節）と静的な SVG（halving.svg、二分探索で候補が 7→4→2→1 と減る）。手元に SVG を画像にする道具がなく、見た目は目視で確かめていない（文字幅から配置を計算しただけ）。検証で表示を確かめてほしい
- 使った出典：kazun-kyopro（abc299_d の制約 N ≤ 2×10^5・20 回）、oraclesqlpuzzle（abc299_d・abc269_e の N ≤ 1000 と 10 回ずつ）、drken（abc244_c・abc305_f・abc313_d・abc282_f の N ≤ 4000・M ≤ 50000）、merom686（abc269_e・abc337_e・abc286_f）、kyopro-friends（practice_2）、ikatakos（abc355_e、解説の部分だけ）、picomikan（mkfifo と tee）、scrapbox kyopuro-ryusuke920（並べ方）
- 新しく noai を確かめたドメイン：picomikan.net（指定なし）、scrapbox.io（kyopuro-ryusuke920 のページ、指定なし）→ 付録 B への追加を提案

## 台帳への提案

- abc299_d｜evidence｜https://kazun-kyopro.hatenablog.com/entry/ABC/299/D を追加｜制約（2 ≤ N ≤ 2×10^5、20 回）を明記している。oraclesqlpuzzle のページは文字化けで制約が読めない
- abc337_e｜evidence｜（任意）N の範囲を明記した解説の追加。merom686 の記事には N の範囲がない。本文では N の範囲を書いていない
- practice_2｜label｜fix_problems の出力が「PRACTICE B. Interactive Sorting」になる。表示名の規則（contest id を大文字）どおりだが、「practice contest B」など読みやすい表示名を規則に足すか検討してほしい

## 用語集への提案

- 適応的ジャッジ｜adaptive-judge｜インタラクティブ問題で、隠れた答えを最初に固定せず、それまでの答えと矛盾しない範囲で解答者に不利な答えを返すジャッジ。最悪の場合の質問回数で方針を考える必要がある（本文では節 #adaptive-judge にリンクしたので、用語集は任意）
- flush（フラッシュ）｜flush｜出力のバッファにたまった内容を書き出して相手に届けること。C++ では `cout << endl`・`cout << flush`・`fflush(stdout)`。本文では「flush」と書いた（summary が flush なので）。cpp-io は「フラッシュ」と書いているので、prh で一方にそろえるか決めてほしい

## 手引きへの提案

- インタラクティブのコード片は、ジャッジの答えを cases の input に先に並べれば、決定的な質問列を output と照合して確かめられる（boundary.yaml・bits.yaml）。§9 に例として足すとほかのページ（game-basics など）でも使える
- textlint の sentence-length は、折りたたみの中の句点のない箇条書きを 1 文につなげて数えるようなので、§13-8 の「誤検出なら残してよい」の例に足すとよい

## 問題の補充の候補

- abc019_4（台帳にあり・確認済み、ページの割り当ては interactive にない）｜距離の質問で木の直径を求める（2 回の探索、2(N−1) 回の質問）｜https://drken1215.hatenablog.com/entry/2021/06/14/001500（研究 08 の表）。本文の「未知のグラフを探索する」で問題 ID を出さずに型だけ書いた。interactive の練習（または tree-diameter の練習）として pages に足すことを提案する。difficulty 1378（参考値）
- 水・青の帯に abc319 以降の問題が 2 問（abc337_e・abc355_e）しかない。直近のインタラクティブ問題は ap.py で題名から探しきれなかったので、メインのバッチで候補を探してほしい

## 未解決の点

- abc305_f の到着の合図（ジャッジが返す文字列）と、abc299_d に不正の合図（−1）があるかは確かめていない。本文では一般的な書き方（「合図」「−1 などを返す問題では」）にとどめた
- abc337_e の N の範囲は確かめていない（本文に書いていない）
- abc286_f の M ≤ 110 は merom686 の記事の推論から読み取った値で、明記した資料は見ていない。本文には「合計 108 頂点」「頂点数の上限の中で」とだけ書き、110 の数は書いていない
- 「適応的ジャッジかどうかが問題文に書かれていることがある」は一般的な記述で、具体的な問題を挙げていない
- related の stress-testing#interactive は、stress-testing がまだ骨格なのでページへのリンクだけにした（節へのリンクは張っていない）
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 14 回（検索 1 回を含む）

## 検証の指摘への対応（verify/interactive.md）

- 直したもの：1（端末での見え方を printf・println と同期を切った cout で分け、落とし穴にも条件を付けた）、2（ABC355 E を累積和の添字の頂点と L から R+1 への最短路に）、3（cin.tie(nullptr) の条件を先に書く順に）、4（ABC355 E の結びを「上限から逆算できないので別に考える」に）、5（Practice B を最悪 99 回と具体的に）、6（DFS 木の辺・「どの質問もほぼ半分に分けているか」に）、7（図の注記に隠れた列と S_2・S_3 の値を書き、2 行に分けて viewBox の高さを 396 に）、8（#format に「ng・ok の意味と不変条件は二分探索の節で説明する」と一言足す方を採った。core を 2 つに分けるより変更が小さく、例題の「形式の節に載せたコード」との対応も保てるため）、10（Mermaid の N を 5 にし、S = 0 0 1 1 1 の例と書いた。boundary.yaml の 2 つめの case と一致）
- 9 の一部を採らなかった：用語集に glossary#flush の項目がまだない（docs/guide/glossary.md に flush・フラッシュの語がない）ので、リンクは張らなかった。用語集への追加と prh での表記の統一は、上の「用語集への提案」のとおりメインに任せる
- 9 の「01 列」：本文の該当行は台帳の summary 由来なので、本文は直さず台帳の直しを提案する（下）

## 台帳への提案（追加）

- abc299_d｜summary｜先頭が 0・末尾が 1 の隠れた 0/1 の列について、隣と値が異なる位置を 20 回以内の質問で見つける。｜本文の「0/1 の列」と表記をそろえる（検証の指摘 9）
- abc313_d｜summary｜ちょうど K 個（奇数）の要素の和の偶奇を聞く N 回の質問で、0/1 の列のすべての要素を特定する。｜同上
