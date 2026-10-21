# invariant（不変量・単調に変わる量）の提案

- 書いたファイル：docs/thinking/invariant.md、snippets/invariant/reachable-bfs.{cpp,yaml}、docs/img/invariant/flip-signs-invariant.svg
- front matter で変えたもの：complexity・stage（draft）・updated、sections に `{title: 偶奇・構築・ゲームとのつながり, anchor: connections}` を追加
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（期待と違う 0）、textlint（エラー 0、警告 8：要点の囲みの入れ子の行・図の代替テキスト・台帳から作る問題の行の読点や助詞の重なりで、規則の誤検出か台帳の文）
- 使った出典：drken の 4 記事（abc125_d・abc323_d・arc068_b/abc053_d・abc140_d）、github.com の Reputeless/tenkei_90 と E869120/kyopro_educational_90 の sol/079.cpp。新しいドメインなし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_ca | summary | 2×2 の正方形の 4 マスに同じ値を足し引きする操作で、行列 A を B にできるか判定し、できるなら最小の操作回数を求める。 | https://github.com/E869120/kyopro_educational_90/blob/main/sol/079.cpp （Yes のとき回数も出力している） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 奇数部分 | odd-part | 正の整数を 2 で割れるだけ割って残る奇数。$X = o \times 2^k$（$o$ は奇数）の $o$。 |

（本文では用語集へのリンクを張っていない。足すなら本文の「奇数部分で分ける」の初出にリンクできる）

## 手引きへの提案

- thinking のページの構成の目安（§4）にある「その型が使える合図」は、要点の囲みの「いつ使うか」と重なるので、本文では導入文に溶かした。合図の節を独立に置くかどうかを決めておくと、thinking のページがそろう

## 問題の補充の候補

- なし（例題 3・練習 2 で目安を満たす）。abc319 以降の問題は recent 0 で見つけていない。「添字を K で割った余りごとにソートする」「1 行目を全探索すると残りが決まる」の型は本文で問題 ID を出さずに書いたので、台帳に確認済みの問題があれば練習に足せる

## 未解決の点

- 指示では「レベル 水」とあったが、骨格の front matter と catalog の level は「基礎」なので基礎のまま書いた
- 骨格の要点の「操作回数の上界」を「操作回数の下限や、操作が必ず止まることの証明」に書き直した（停止性の議論では上界、最小回数の議論では下限になるため）。summary と sections の title（「回数の上界を得る」）は変えていない。summary を「操作回数の上界・下限や停止性の証明」に直すか検討してほしい
- related の proof-patterns#necessary-sufficient は、本文では proof-patterns のページ（節なし）へリンクした（ページがまだないため）

## 検証の指摘への対応（2026-10-21）

- 1・2（直すべき）：直した。#independent-parts は合計 $o \times Y$ ではなく $Y$ の popcount と明記し、大きさ 3 の 1 体の反例を添えた。#pitfalls は足す量を $Y_o$ と明記し、合計の大きさは `long long` に入らないので求めないと書いた
- 3〜5・7：指摘の直し方どおりに直した（転倒数は値の違う 2 つ、パズルは上下左右、表の 3 行目は $k$ ずつ足す形に絞った、#monovariant 末と落とし穴の「下限」の段落を書き直した）
- 6：手引き（sections の title は執筆者が変えてよい）に従い、節の題名を「単調量（必ず減る量）で操作回数を抑える」に変え（anchor は monovariant のまま）、本文のリンク文 2 か所と要点（「上界・下限や停止性」）を揃えた。summary は変えられないので下の提案にする。docs/index/thinking.md の節名は gen_site で作り直してほしい
- 8：図の下の説明文を外し（代替テキストに「点線の枠が反転した 2 つ」を足した）、左のラベルを「1・2 を反転」に縮めて幅を 640 → 540 にし、文字を 16〜20px に大きくした。幅 358px の表示で 11〜13px 相当
- 採らなかった指摘：なし

### front matter への提案（メイン）

| 項目 | 新しい値 |
| --- | --- |
| summary | 操作で変わらない量（和の余り・個数の偶奇・XOR）を見つけて必要条件を得て、十分性は構築で示す。操作で必ず減る量（単調量）は操作回数の上界・下限や停止性の証明に使う。 |

- catalog の thinking.yaml の sections の title（凍結なので必要なら）も「単調量（必ず減る量）で操作回数を抑える」に合わせる
