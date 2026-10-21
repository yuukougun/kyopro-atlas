# persistent-data-structures の報告（b2・執筆）

- 書いたファイル：docs/ds/persistent-data-structures.md、snippets/persistent-data-structures/{version-tree,persistent-segtree,offline-version-tree,prefix-kth}.{cpp,yaml}、docs/img/persistent-data-structures/{version-tree,path-copying}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（今日のまま）。sections は変えていない
- 検査の結果：check_pages エラー0・警告0。fix_problems --check 直すべき行0。check_snippets 4 片・期待と違う0。textlint エラー0・警告8（図の代替テキストと数式の中の半開区間 `[l, r)` の括弧・読点の誤検出だけ）
- 追加の確かめ：persistent-segtree.cpp と offline-version-tree.cpp を乱択の入力 300 件で突き合わせて一致。prefix-kth.cpp は中で素朴な方法と assert で比べ、乱択 300 件で通過
- 図：render_svg で 360px・720px を目視。720px の PNG は下端の約 20px が切れて写った（360px では全体が写る）。SVG の viewBox は正しいので、道具の撮影範囲の問題とみられる（version-tree.svg・path-copying.svg の両方で同じ）
- 使った出典：kazun-kyopro（abc273_e）、www.cnblogs.com/CR-J（abc453_g。h1 は「ABC 453 个人题解」、表示名 Billlly）、qiita.com/hotman78（永続配列・永続 UF・接頭辞の版）。新しく check_noai で確かめたのは qiita の記事（指定なし。ドメインは付録 B にある）
- ikatakos の abc453 の記録は 2 回とも HTTP 503 で読めなかった。オフラインの解き方（版の木の DFS と取り消し）は自分で組み、永続セグ木の解と乱択で一致することで確かめた

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc453_g | summary | 「1 点更新」を「1 点の値の変更」にするか検討（cnblogs の解説では値の代入。加算ではない） | https://www.cnblogs.com/CR-J/p/19853087 |
| abc453_g | evidence | ikatakos の URL は 2026-10-21 に 503 で読めず、オフラインの解き方の裏付けが取れていない。読めたら確かめてほしい | — |

## 用語集への提案

なし（ならし計算量・オンライン強制・ダングリング・イテレータの無効化は既存の anchor にリンクした）。

候補として：

| 語 | anchor | 定義 |
| --- | --- | --- |
| 経路コピー | path-copying | 木のデータ構造を更新するとき、変わるノードから根までの経路だけを新しく作り、ほかのノードは前の版と共有する方法。古い根からたどれば前の版がそのまま見える |

（ページがあるので、用語集ではなく term-index の別名で足りるならそれでよい）

## 手引きへの提案

- render_svg.py の 720px の出力で SVG の下端が切れる（高さ 300〜312 の viewBox、幅 640）。撮影の高さの計算を確かめてほしい

## 問題の補充の候補

| 問題 ID | 役割の案 | 何を問うか | 裏付けの URL |
| --- | --- | --- | --- |
| abc339_g | 練習（prefix-versions の節） | 区間内で X 以下の要素の和を、前の答えで次の質問が決まる形で多数答える（オンライン強制） | https://tayu0110.hatenablog.com/entry/2024/02/05/205618 （主解はマージソート木。接頭辞ごとの版の永続セグ木で解けることは、HackMD の題単 https://hackmd.io/@rfr9XKMgQ7iE-PzOXscYEw/ry8CYJA7yl に「永続でも可」とあるだけで、詳しい解説は未確認。手法としては prefix-kth.cpp に和を持たせれば O(log N) で答えられる） |
| abc133_f | 力試し（path-copying の節） | 木の辺の色と長さが与えられ、各質問で「色 x の辺の長さを y にしたとき」の 2 頂点間の距離を答える | https://qiita.com/hotman78/items/9c643feae1de087e6fc5 （根から頂点への版を永続配列で持つ使い方として挙がる。主解はオフラインの DFS。問いの要約は解説の記述から書いたもので、台帳の summary と合わせて確かめてほしい） |

ABC で版の木そのものの練習（abc273_e 以外）は見つからなかった。

## 未解決の点

- 動く図は作っていない（catalog の visual は priority 2・static なので、静的な SVG 2 枚で代えた）
- abc453_g の問題文の細部（区間が 1-indexed の閉区間、更新が代入）は cnblogs のコードからの推測を含む。解法の詳細の折りたたみではそれに沿って書いた
- 永続遅延セグ木（Library Checker persistent_range_affine_range_sum）は 1 段落で触れただけで、コード片はない。verify に挙がっているので、自作ライブラリ用に足すなら別の作業にしたい

## 検証の指摘への対応（b2・直し）

- 直すべき 1（マージソート木の計算量）・2（K は 0 始まり）：直した。171 行は文が長くなったので 3 文に分けた
- 直すとよい 3（ならし計算量の言い切り）：本文と落とし穴を「完全永続では上限が保てない／部分永続でも読むときに書き換える操作は使えない」に分けた
- 直すとよい 4：要点と complexity で「長さ $N$ の列の永続セグ木」と $N$ を定義し、`map` の $O(\log Q)$ を書き、「ならしではなく」を「ノードの配列を先に確保すれば、どれも 1 回ごとの上限」にした
- 直すとよい 5・6・9：指摘どおり直した
- 直すとよい 7：(a) 祖先の表で追加が $O(\log Q)$ になること、(b) 永続キュー（persistent_queue）になることを 1 文ずつ足した。あわせて祖先を求める計算量の $O(\log N)$ を $O(\log Q)$ にした（この節に $N$ はない）
- 直すとよい 8（図の文字）：2 枚とも 12・13 の文字を 14 にし、path-copying.svg の viewBox の幅を 640 → 600 にした。360px で全体が写り、重なりなし
- 採らなかったもの：なし
