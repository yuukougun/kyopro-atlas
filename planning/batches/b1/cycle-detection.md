# cycle-detection の報告（工程8b・b1）

- 書いたファイル：docs/graph/cycle-detection.md、snippets/cycle-detection/directed.{cpp,yaml}、snippets/cycle-detection/undirected.{cpp,yaml}、docs/img/cycle-detection/three-color.svg
- front matter で変えたもの：complexity（`O(N + M)（Union-Find で判定するならならし O(M α(N))）`）・stage（draft）・updated（2026-10-21）。sections は変えていない（見出しは title と同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（2 件・期待と違う 0）、fix_problems --check --page cycle-detection（0 行）、textlint（エラー 0、警告 1：参考の行の ikatakos 氏の記事の題名が長いための文の長さ。題名なので残した）
  - 全体の `fix_problems.py --check` は graph/bipartite-graph.md の 5 行で 1 を返す（ほかの執筆者の担当。こちらのページは 0 行）
- 図：静的な SVG を 1 枚（visual は priority 2・static。有向の 3 色 DFS で、完了した頂点への辺と探索中の頂点への辺を左右に並べた）。手元に SVG を描画する道具がなく、目視の確認はしていない。XML として読めることだけ確かめた
- 使った出典：
  - https://kyo-pro.hatenablog.com/entry/ABC285D（例題の方針）
  - https://zenn.dev/dokaraya/articles/atcoder-abc285d（例題を 3 状態の DFS で解く方針）
  - https://programming-hiroba.com/abc285-d/（例題を 2 つの印の DFS で解く方針）
  - https://kyo-pro.hatenablog.com/entry/2023/02/04/224004（abc288_c）
  - https://drken1215.hatenablog.com/entry/2023/07/24/030543（abc311_c）
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0502_abc456（abc456_e。解法の節だけ）
  - ACL document_ja（scc.md・dsu.md）、Library Checker の問題一覧
  - 新しく noai を確かめたドメイン：programming-hiroba.com（付録 B に既にある。check_noai で再確認、指定なし）。zenn.dev は付録 B にある

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc288_c | summary | 末尾の「。」を外すか、ほかの行とそろえる（abc456_e も「。」付き、abc285_d・abc311_c は無し）。表記の統一だけ | — |
| abc285_d | evidence | https://zenn.dev/dokaraya/articles/atcoder-abc285d を追加（3 状態の DFS で解く解説） | 左の URL |
| abc285_d | approach | 「名前を頂点、変更を辺にした有向グラフに閉路があれば不可能（3 色の DFS か Kahn 法で判定）」 | kyo-pro・dokaraya の解説 |

catalog の abc456_e の summary は「（執筆時に確かめる）」のままだが、台帳には ikatakos 氏の記録で確かめた summary があり、本文はそれを使った（catalog は凍結なので変更不要）。

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 探索中（DFS の頂点の状態） | `in-progress` | DFS で、訪れたがそこから出る辺をまだ調べ終えていない頂点の状態。今の再帰の経路の上にある頂点がちょうどこれにあたる。有向グラフでは、探索中の頂点への辺が閉路の印になる |
| 多重辺 | `multi-edge` | 同じ 2 頂点を結ぶ 2 本以上の辺。無向グラフでは 2 本で長さ 2 の閉路になる |
| 自己ループ | `self-loop` | 頂点から自分自身への辺。それだけで長さ 1 の閉路である |

（本文では用語集へのリンクは張っていない。足すなら、多重辺・自己ループの初出にリンクを張るとよい）

## 手引きへの提案

- 基礎の technique の構成（要点 → 応用の型 → 落とし穴 → つながり → 問題）で、ACL の囲みをどこに置くかが §4 にない。このページでは落とし穴の後に見出しなしで置いた。見出し（`## ACL では {#acl}`）を定型の節に足すかを決めておくとよい
- 「上位の手法とのつながり」を定型の見出しにするか。このページでは `## 使い分け {#comparison}` にまとめた

## 問題の補充の候補

確認済みの問題で数は足りている（例題 1・練習 2・力試し 1）。補うなら次の型が欲しい。

- 有向グラフの閉路を 3 色の DFS で「復元」まで行う問題（出次数 1 でない一般の有向グラフ）。今の練習の abc311_c は出次数 1 なので、復元の一般形を練習できる問題がない。候補は未調査（ap.py と第三者の解説で探す必要がある）
- 無向グラフの閉路の復元（多重辺を含む）。Library Checker の cycle_detection_undirected（AtCoder の問題ではないので台帳の対象外）

## 未解決の点

- abc285_d で無向の Union-Find が正しい理由：変更前の名前どうし・変更後の名前どうしが相異なる（各頂点の出次数・入次数が高々 1）という制約によると考えられるが、読んだ第三者の解説（kyo-pro・dokaraya・sano192・viral_8・programming-hiroba）のどれにも制約の記載がなく、確かめられなかった。本文では「各名前から出る辺・入る辺が高々 1 本のときに正しい。そう言えるかは問題の制約で確かめる」と条件付きで書いた。制約を確かめられるなら、本文の解法の詳細を言い切りに直せる
- abc285_d の解法の詳細の「閉路がなければ、変更先の名前を今使っている人がいない人から順に変えればよい」は解説の要旨に従ったが、厳密な議論（同じ変更先が重ならないこと）は上の制約に依存する
- dfs.md が手元で 0 バイトだった（ほかの執筆者が作業中と思われる）。前提へのリンクはページ単位なので影響はない
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 11 回（検索 1 回を含む）

## 検証の指摘への対応（verify/cycle-detection.md）

- 指摘 1〜5 はすべて採った
    - 1：abc285_d の方針の段落と「解法の詳細」の最後の項目を、制約（変更前・変更後の名前がそれぞれ相異なる）による言い切りに直した。参考に kazun 氏の記事（制約）を足した
    - 2：#directed の「完了した頂点への辺は閉路を作らない」を、不変条件（完了した頂点から行ける頂点はすべて完了）1 つで言い直した
    - 3：#kahn-leftover の理由を「閉路の頂点のうち最初に取り出されるもの」を仮定する形に直した
    - 4：参考の kyo-pro「ABC288C」の参考にした点から式を除いた
    - 5：three-color.svg の文字を上げた（見出し 16、ラベル・説明 15）。右下の説明は幅に収めるため「探索中の頂点への辺：閉路になる」に縮めた（閉路の並びは見出しと代替テキストにある）
- 共有ファイルへの提案（検証役の提案に同意）：台帳 abc285_d の evidence に https://kazun-kyopro.hatenablog.com/entry/ABC/285/D（制約の確認）と https://zenn.dev/dokaraya/articles/atcoder-abc285d を足す。abc285_d・abc288_c・abc311_c の `checked` に 2026-10-21。abc288_c・abc456_e の summary の末尾の「。」をそろえる
- 未解決の点の (1)(2) は、検証役が制約を確かめたので解消した
