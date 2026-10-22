# persistent-data-structures の問題の補充（工程9・b6）

- ページ：docs/ds/persistent-data-structures.md（レベル 青）
- 今の問題：例題 abc273_e・abc453_g、練習 0 問、力試し 0 問
- 結論：練習の候補 2 問（合わせて 2 問になる）と力試しの候補 1 問を確かめた。difficulty・題名はすべて `python3 tools/ap.py show` で確かめた（2026-10-22）
- 探した順：b3 の candidates.md と b2 の報告の「問題の補充の候補」（abc339_g・abc133_f）→ 台帳（このページを pages に持つのは例題の 2 問だけ）→ 第三者の解説。Web 検索はセッション全体の上限に達したため途中で打ち切った（下の「見送ったもの・調べ残し」）

## 練習の候補（practice）

### abc339_g　G. Smaller Sum（diff 1792・青）

- 台帳：登録済み（merge-sort-tree:example・wavelet-matrix:practice）。pages に persistent-data-structures:practice を足す提案
- 要約：列の区間に含まれる X 以下の要素の和を、前の答えで次の質問が決まる形で多数答える。
- 方針の要点：値を座標圧縮し、接頭辞 $A_0, \dots, A_{i-1}$ を入れた「値ごとの個数と和」のセグメント木を経路コピーで版 $i$ として残し、版 $r$ と版 $l$ の差で区間の X 以下の和を $O(\log N)$ で答える。
- このページとの対応：#prefix-versions（level 発展）。本文の末尾に「ノードに値の和も持てば、区間の x 以下の要素の和も同じ形で求まる」とあり、そのまま当てはまる。オンライン強制なので #offline-version-tree の先読みは使えない
- 注意：主解はマージソート木（または平方分割・BIT on Wavelet Matrix）で、永続セグメント木で解いた詳しい第三者の解説は見つけられなかった。永続で解けることの裏付けは HackMD の題単の一言（「持久化應該也能做」）と本文の手法の対応だけである。練習の方針の折りたたみには「マージソート木でも解ける」と添えるとよい
- 裏付け：
  - https://tayu0110.hatenablog.com/entry/2024/02/05/205618 （問いの形とオンライン強制。各ノードにソート列の累積和を持つ主解）
  - https://hackmd.io/@rfr9XKMgQ7iE-PzOXscYEw/ry8CYJA7yl （マージソート木の項に挙がり、永続でも解けるという一言がある）

### abc165_f　F. LIS on Tree（diff 1843・青）

- 台帳：登録済み（root-path-dfs:example・lis:practice）。pages に persistent-data-structures:practice を足す提案（例題の持ち主は root-path-dfs のままで、ここでは練習）
- 要約：木の各頂点に数が書かれ、頂点 1 から各頂点へのパス上の数を並べた列の最長増加部分列の長さを、すべての頂点について求める。
- 方針の要点：LIS の末尾の配列を 1 つだけ持って DFS し、頂点に入るときに二分探索で 1 か所を書き換え（または末尾に追加し）て変更前の値を覚え、出るときに元へ戻す。
- このページとの対応：#offline-version-tree（版の木を DFS し、入るときに施して出るときに取り消す）と、#version-tree の「木の上の DFS で使う」の段落。版の木が入力の木として与えられている形である。本文の取り消しの手順がそのまま使える
- 裏付け：
  - https://kmjp.hatenablog.jp/entry/2020/05/02/0930 （DFS で LIS の配列を 1 か所更新し、戻るときに元に戻す。台帳の evidence）
  - 2 つ目の裏付けは探せていない（検索の上限のため）

## 力試しの候補（challenge）

### abc133_f　F. Colorful Tree（diff 2330・黄）

- 台帳：登録済み（tree-path:practice）。pages に persistent-data-structures:challenge を足す提案
- 要約：辺に色と長さがある木で、色 x の辺の長さをすべて y に変えたときの 2 頂点間の距離を、多数の質問に答える。
- 方針の要点：根から各頂点までの「色ごとの本数と長さの和」を、親の版から 1 か所だけ変えた永続配列として DFS で作り、LCA で 2 頂点の距離を組み立てて色 x の分だけ差し替える。
- このページとの対応：#path-copying の「永続配列」の段落（各頂点の版が親の版と 1 か所だけ違う）。想定解はオフラインの DFS で数える方法で（#offline-version-tree の考え方に近い）、永続配列は別解である。difficulty が青の帯から離れる（黄）ので力試し
- 裏付け：
  - https://qiita.com/hotman78/items/9c643feae1de087e6fc5 （永続配列の例題として挙がり、DFS で親と 1 か所だけ違う情報を各頂点に持つと説明。想定解ではないと明記）
  - https://blog.hamayanhamayan.com/entry/2019/07/08/213009 （台帳の evidence。距離を根からの距離と LCA で表し、パス上の色 x の本数と長さの和を差し替える想定解。今回は開き直していない）

## 見送ったもの・調べ残し

- code_thanks_festival_2017_h（Union Sets）：hotman78 の記事で永続 Union-Find の例題として挙がるが、台帳では partially-persistent-union-find の持ち主なので、このページには足さない
- abc324_g（Generate Arrays、diff 2501）：区間の矩形内の個数を問う型で、永続セグメント木でも解けそうだが、永続で解いた第三者の解説を確かめていない。帯（青）からも離れるので見送った
- 版の木そのものの練習（abc273_e 以外）は、b2 の報告と同じく見つからなかった
- Web 検索がセッション全体の上限（200 回）に達したため、luogu・cnblogs の「主席树 AT_abc」の題解の検索は途中で止めた。luogu の題解ページ（/problem/solution/AT_abc339_g）はログインが要り（HTTP 401）読めなかった
- 新しく使ったドメイン：なし（すべて付録 B にある）
