# complete-binary-tree の報告（工程8b・バッチ b1）

- 書いたファイル：docs/tree/complete-binary-tree.md、snippets/complete-binary-tree/{lru-moves,lca-by-index,count-at-distance}.{cpp,yaml}、docs/img/complete-binary-tree/binary-path.svg
- front matter で変えたもの：complexity（`移動 1 回 O(1)、LCA・距離 O(log N)、距離 K の頂点の数 O((log N)^2)`）・stage（draft）・updated（2026-10-21 のまま）。sections に「上位の手法とのつながり（next-steps）」を足した（手引き §4 の基礎の構成。level はページと同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 9。画像の代替テキストと要点の囲みの文の長さ、数式を含む文の助詞の重複・読点の数、折りたたみの箇条書きの文の長さ）。fix_problems --check はこのページで 0（string/hashing-for-sets.md:223 の abc424_f に 1 行あるが、別の執筆者の担当）
- 図：catalog の visual（static・priority 2）どおり、深さ 3 までの木に番号と 2 進表記を並べ、13 への道（R・L・R）を太線にした SVG を作った。動く図は作っていない。SVG を描画する道具が手元になく、見た目は座標の計算でだけ確かめた（検証役に表示を見てほしい）
- コード片はすべて、素朴な方法（シミュレーション・祖先の集合・BFS）との照合を main の assert に入れてある

## 使った出典

- drken「ABC243 D」（台帳の evidence）：制約 N ≤ 10^6・答えは 10^18 以下、スタックで打ち消す方針（本文の例題の節）
- drken「ABC321 E」（台帳の evidence）：制約 T ≤ 10^5・N ≤ 10^18・0 ≤ K ≤ N−1、祖先へ上がりながら反対側の子の部分木を数える方針、計算量 O((log N)^2)
- comet725「ABC465Dを解いた【LCA】」（台帳の evidence）：大きい方を K で割って共通の祖先まで上がる方針
- 2yuu「Atcoder解いてみた AtCoder Beginner Contest D - X to Y」https://qiita.com/2yuu/items/b4d70003b7f311f8b8d1 ：abc465_d の操作の内容（x を ⌊x/K⌋ に置き換える、または ⌊y/K⌋ = x となる y に置き換える）を確かめた。Konini64 氏の記事 https://qiita.com/Konini64/items/40587ce97ddf24e3e26e でも「大きい方を K で割る」解法を確かめた（参考には入れていない）
- 新しく noai を確かめたドメイン：なし（qiita.com・drken1215.hatenablog.com は付録 B にある）

## 台帳への提案

- abc465_d｜summary｜「整数 x を ⌊x/K⌋ に置き換えるか、⌊y/K⌋ = x となる整数 y に置き換える操作を繰り返して、X を Y にするための最小の操作回数を求める（テストケースが複数ある）。」｜https://qiita.com/2yuu/items/b4d70003b7f311f8b8d1 （本文の行はこの要約で書いた）
- abc465_d｜evidence｜上の 2yuu 氏の URL を足す（comet725 氏の記事は問題の操作を書いていない）
- abc243_d・abc321_e の summary は文末の「。」がない。ほかのページの行にそろえるなら句点を足す（本文の行は台帳のまま）

## 用語集への提案

- なし（本文で用語集へのリンクは使っていない）

## 手引きへの提案

- なし

## 問題の補充の候補（問題 ID・何を問うか・裏付けの URL）

- abc264_h（Ex. Perfect Binary Tree、diff 2660）｜頂点を順に加えながら、完全二分木の高さが log N 程度しかないことを使って祖先の DP だけを更新する｜https://kmjp.hatenablog.jp/entry/2022/08/13/0930 （research 04-tree §5.1 の候補。ap.py で実在と diff 2660（橙）を確かめた。台帳にはない。基礎のページには難しすぎるので、載せるなら tree-dp か別の上位のページの力試し）
- 練習が 1 問しかない（catalog の problems_note のとおり）。基礎の形の ABC の問題は見つけられなかった。セグメント木を番号で自作する問題や、ヒープの問題を練習に回すかはメインで判断してほしい

## 未解決の点

- abc465_d の制約（K の下限、X・Y が 0 を含むか）は確かめきれなかった。本文の方針は K ≥ 2 を前提にしている（大きい方を割る方法は、頂点 0 を含んでも正しい）
- 手引き §4 の基礎の構成（要点 → 応用の型 → 落とし穴 → つながり → 問題）に、catalog の sections の順をそのまま入れた。確認問題は節の中に置き、`## 確認問題 {#quiz}` は立てていない
- tree-basics はまだ stub なので、前提へのリンクはページへのものだけにした
- SVG の表示を目で確かめていない（上記）

## 使用量の目安

- 道具の呼び出し 約 35 回、Web 取得 6 回（curl で解説 5 件、Web 検索 2 回）

## 検証の指摘への対応（修正）

- 指摘 1（直すべき・図の 2 進表記と辺の重なり）：binary-path.svg を作り直した。辺の始点を 2 進表記の下（円の中心 +48）に下げ、深さの間隔を 120 にした。座標で、どの深さでも辺が表記の文字の範囲（中心 +24〜+40）を通らないことを確かめた（描画の道具は手元になく、目では見ていない）
- 指摘 2（直すとよい・スマホでの文字）：採った。上下の説明文を図から外し（同じ内容が本文と代替テキストにある）、viewBox を 700×500 → 600×452 に詰め、2 進表記を 13px → 16px（太線の道の上は太字）、番号を 18px にした
- 指摘 3（直すとよい・移動の数を N と呼ぶ）：採った。#lru-moves の 2 か所と例題の解法の詳細を、移動の列 $S$ として $O(\lvert S \rvert)$ にそろえた
- 指摘 4（直すとよい・K の 2 つの意味）：採った。#count-at-distance の冒頭に「この節の $K$ は距離であり、K 分木の $K$ とは別である」と添えた（問題の表記に合わせ、文字は変えていない）
- 指摘 5（直すとよい・最後の段）：採った。「$2^d$ 以上 $2^{d+1}$ 未満（かつ $N$ 以下）の番号に左から順に並ぶ」とした
- 台帳への提案は上の「台帳への提案」のとおり（検証役も abc465_d の summary・evidence の追加と、abc243_d・abc321_e・abc465_d の checked に 2026-10-21 を入れることに賛成）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（3 片・期待と違う 0）、textlint（エラー 0・警告 9）
