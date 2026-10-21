# tree-path の報告と提案（b2）

- 書いたファイル：docs/tree/tree-path.md、snippets/tree-path/path-tools.{cpp,yaml}・edge-set.{cpp,yaml}、docs/img/tree-path/decompose.svg・meeting.svg・intersection.svg
- front matter で変えたもの：complexity（`LCA の前処理 O(N log N)、各判定は LCA を定数回求めるので 1 回 O(log N)`）・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 2 本・7 case 一致（path-tools は main で、与えた木と 9 頂点以下のランダムな木 300 個について、on_path・meet・intersect・kth_on_path を全探索と assert で比べる。edge-set は 16 頂点以下で塗り方の全探索と assert）。textlint エラー 0、警告 14（要点の囲み・図の代替テキスト・数式を含む文の長さと読点。§13-8・§14-25 で残してよいもの）
- 図：render_svg.py で 360px・720px を目で確かめた（パスの 2 本への分解、3 点の合流点、2 本のパスの交差）。catalog の visual は static・priority 2 なので動く図は置いていない
- 使った出典：hamayan「LCA問題まとめ」（型の立て方）、drken（abc152_f）、hamayan（abc133_f）、kmjp（abc298_h）。どれも付録 B のドメインで、新しいドメインはない
- 重なり：lca のページ（距離の式・K 個上の祖先・頂点の値の足し戻し）、tree-distance#from-two（パス上の判定の式・どちらに近いか）、tree-imos#path-add（加算の印）と重なる部分は、式だけを置いてリンクした。lca:99・hld:133・tree-distance:134・complete-binary-tree:164 からこのページへのリンクは、節へ張り替えられる（lca:99 →`#on-path`・`#meeting-point`、hld:133 →`#on-path`、tree-distance:134 →`#intersection`）

## 台帳への提案

- 変更なし。3 問とも evidence の記事で問いを確かめ、台帳の summary のまま使った
- abc152_f の制約（頂点 50 個以下、M ≤ 20）は drken の記事（「辺の本数はたかだか 50 本」）と台帳の summary から書いた

## 用語集への提案

- 合流点｜median-vertex｜木の 3 頂点 a, b, c について、3 本のパス a–b・b–c・c–a のすべてに含まれるただ 1 つの頂点。3 つの LCA のうち最も深いものに等しく、根を c に付け替えたときの a, b の LCA でもある（本文ではリンクしていない。足すならメインが張る）

## 手引きへの提案

- §5 tree に「パス上の判定に距離の式 d(u,x) + d(x,v) = d(u,v) を使うときは、重みのない距離（深さ）で行う（重み 0 の辺があると誤判定する）」を足すとよい。持ち主はこのページの pitfalls

## 問題の補充の候補

- 練習が 1 問（目安は 2〜6）で、abc319 以降の問題がない（catalog の problems_note のとおり）。ap.py で "Path"・"Tree" を題名に含む abc の 1300〜2500 を検索したが、パスの判定・交差・合流点が本体と第三者の解説で確かめられる問題は見つからなかった
- 本文から触れられる既存の台帳の問題（役割の追加の候補）：abc014_4（lca の例題。閉路の長さ＝距離＋1）、abc267_f（lca の例題。K 個上の祖先）、typical90_ai（lca の練習。DFS 順で隣り合う 2 点の距離の和の半分）。どれも持ち主が lca なので、ここでは練習に足していない。typical90_ai は「合流点の距離の和＝距離の和の半分」の一般化なので、練習に足すなら https://github.com/E869120/kyopro_educational_90/blob/main/sol/035-04.cpp を裏付けにする

## 未解決の点

- abc133_f の制約（N, Q ≤ 10^5）は本文に書いていない（hamayan の解答コードの配列の大きさからの推測にとどまるため）。abc298_h も上限の数値は書かず、計算量だけにした
- 交差の共通部分の両端（4 つの LCA のうち深い 2 つ）は、出典で確かめたのではなく、コード片の全探索（9 頂点以下のすべての木の形ではなく、ランダムな 300 個と与えた木）で確かめた
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 4 回

## 検証の指摘への対応（b2 verify）

- 指摘 1〜6 はすべて直した。1：edge-set の条件を「頂点が 64 個以下（辺が 63 本以下）」「頂点が 64 個を超えるとき」に、「パスが数本」を「20 本程度まで」に。2：popcount を用語集へリンクし、コード片の後に C++20 の `<bit>` の関数へのリンクと `unsigned` に変換する理由を足した。3：交差の両端の直感（a・b それぞれの c–d への合流点）を 1 段落足した。4：合流点の証明を「r と同じか r より下」にした。5：確認問題の 1 問目（部分木の辺の数）と 4 問目（重み 0 の辺）を、図の木での K 番目の頂点と、7・8 のどちらに近いかの境目を求める問いに替えた（重み 0 は落とし穴に残る）。6：kth の箇条を「このとき」に、合流点の括弧を言い換えた
- 採らなかったもの：なし。snippet は変えていない（注釈の n ≤ 64 は元から正しい）
- 検査：check_pages エラー 0・警告 0、fix_problems 直すべき行 0、check_snippets 期待と違う 0、textlint エラー 0・警告 14（新しい段落の 1 文は数式内の読点による max-comma で §13-8 の範囲）

## 台帳への提案（検証役の提案の転記）

- abc152_f・abc133_f・abc298_h の `checked` に 2026-10-21 を入れる（検証役が evidence で確かめた）
- 練習の補充として typical90_ai を持ち主（lca）と重ならない役割で足すかはメインで判断する
