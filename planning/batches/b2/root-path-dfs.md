# root-path-dfs の報告と提案（b2）

- 書いたファイル：docs/tree/root-path-dfs.md、snippets/root-path-dfs/{unique-color,lis-on-tree,median-on-path}.{cpp,yaml}、docs/img/root-path-dfs/stack-is-path.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 3 件とも一致（lis-on-tree・median-on-path は素朴な解との assert つき。手元で 300 件の乱択も通した）／textlint エラー 0・警告 13（助詞の重複「に」など、図の代替テキストと確認問題の題の文の長さ。言い換えると不自然になるものを残した）
- 図：stack-is-path.svg を render_svg.py で 360・720 の幅にして目で確かめた。visual は priority 3 なので、動く図の置き場は作らず静的な図で代えた
- 使った出典：hamayanhamayan（abc198_e）・kmjp（abc165_f、abc218_g）・kazun（abc273_e）・drken（abc302_h）。どれも付録 B のドメインで、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc302_h | alternatives[pages=root-path-dfs].summary | 「（執筆時に確かめる）」を本体の summary と同じ「木の根から各頂点へのパス上で各頂点のボールの片方を選ぶとき、書かれた値の種類数の最大値を各頂点について求める。」にそろえる（本文の行は本体の summary で書いた） | https://drken1215.hatenablog.com/entry/2023/06/10/032900 |
| abc302_h | evidence の確かめ | 記事は abc302_h のもので、制約 2 ≤ N ≤ 2×10^5、値の範囲 1〜N、成分ごとの答え min(頂点数, 辺数) を確かめた | 同上 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 巻き戻し | rollback | データ構造への変更を「位置と元の値」として記録しておき、新しい順に元の値を書き戻して、以前の状態に戻すこと。記録 1 件を戻すのは O(1) で、戻す回数は変更の回数を超えない |

本文では用語集の anchor がまだないため、リンクを付けずに「巻き戻し」と書いた（check_pages が未定義の anchor をエラーにするため）。足したらリンクを張ってほしい。

## 手引きへの提案

- §13-5 は「用語集へのリンクは、まだなくても書いてよい」とするが、check_pages は用語集にない anchor をエラーにする。手引きか検査のどちらかにそろえる

## ほかのページへの申し送り

- handoff の「tree-imos（根から y 世代までの数える形）」：本文の path-statistics の「祖先から何世代下まで届くか」で扱った。最後に届く深さごとの個数 end を持ち、reach[v] = reach[par] − end[dep[v] − 1] + 自分の効果の数 として O(N + Q)。tree-imos#depth-limited からのリンクは、節 `#path-statistics` へ張り替えてよい
- lis#variants の末尾のリンク文言「根からのパスを持つ DFS」は題名「根からのパスを DFS で持ち回る」と違う。handoff の表では lis:180 が `#undo-log` へ張る予定になっている
- minimax#tree は root-path-dfs を前提にしている。abc218_g は両方のページで力試し
- rollback-union-find（stub）の #no-path-compression・#with-dfs と、このページの no-path-compression の節が重なる。こちらは「併合の記録は 2 件・経路圧縮すると併合だけ戻しても成分が分かれない・union by size で O(log N)」までにした。rollback-union-find を書くときに食い違わないよう確かめる

## 問題の補充の候補

catalog の problems_note のとおり、abc319 以降の問題がない。ap.py の search（Tree・abc・diff 1300〜2400）と第三者の解説の検索で探したが、根からのパスを巻き戻しで持つ問題を abc319 以降で裏付けられなかった。候補なし。

## 未解決の点

- abc218_g の中央値の定義（個数が偶数なら真ん中の 2 つの平均）は、kmjp の解答コードが真ん中の 2 つを使っていることから書いた。問題文は開いていないので、検証役に解説で確かめてほしい
- 骨格の「いつ使うか」の 3 つ目を「操作の取り消しや、保存した状態の読み込みがある。」と言い換えた（signs の文言とは少し違う。textlint の助詞の重複を避けたため）
- 計算量の front matter は一般形と代表例を並べたので長め

## 検証の指摘への対応（2026-10-21）

直すべき 0 件、直すとよい 7 件はすべて採った（採らなかったものはない）。

1. path-statistics：「（効果は合わせて $Q$ 個）」を足して $Q$ を定義した
2. no-path-compression：par[s] の括弧を「$s$ 自身を指していたのが $r$ を指すようになる」にした
3. stack-is-path.svg：右下の説明 3 行（本文と同じ内容）を外し、cnt の表を横向きにしてスタックの下へ移し、viewBox を幅 640 → 510 にした。render_svg.py の 360px で文字が読めることを確かめた。代替テキストはそのままで合う
4. to-version-tree の本文と練習の方針に「根では動かない」「根にいるなら動かない」を足した
5. 要点と front matter の complexity を「色の数なら O(N + C)（C は色の範囲）」にそろえた
6. 落とし穴の 1 つ目を「非再帰版で $\sim v$ を積む前に `continue` したり」にした
7. 図の前の文に「（頂点の番号は問題文と同じく 1 から）」を足した

台帳への提案は検証役の「台帳への提案」（checked の日付・abc302_h の alternatives の summary）のとおり。
