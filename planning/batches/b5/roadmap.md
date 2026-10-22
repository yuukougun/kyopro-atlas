# roadmap（色別ロードマップ）の報告と提案

- 書いたファイル：docs/guide/roadmap.md（snippets・図はなし。catalog の visual は null、problems は空）
- front matter で変えたもの：stage（stub → draft）・updated（2026-10-22）。complexity は guide なので null のまま。sections は変えていない
- 生成ブロック（recent-positions・roadmap-order）は中身を変えず、前後に `## 位置ごとの頻出手法（最近30回） {#recent-positions}`・`## 色ごとのページの列 {#reading-order}` の見出しと読み方を置いた（HEAD とブロックの中身が一致することを確かめた）
- 進捗の節に `<div class="kp-roadmap-stats"></div>` と `<div class="kp-progress-io"></div>` を置いた（progress.js が描く。research/10 §3.10 の「書き出し・読み込みをロードマップに置く」に従った）
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0・警告1（参考の記事の題名の「！！」。誤検出として残した）
- 数値の確かめ：位置ごとの difficulty の分布（D 93% 基礎、E 水 59%、F 青 49%・2000 未満 75%、G 黄 38%・発展 49%）、レート 1200／1600／2000 の解く確率・解き終える時刻、6 問体制の E・F の中央値（1528・2132）は、tools/ap.py の Data で再集計して research/00 §2.3.3・§2.3.6 と一致することを確かめた（一時スクリプトは scratchpad に置いた）
- 使った出典：qiita.com（E869120 典型90 告知、nouka28、blueberry1001）、ks2m.hatenablog.com、webkit.org、github.com（AtCoder Problems の time-estimator）
- 新しく noai を確かめたドメイン：ks2m.hatenablog.com（指定なし）・webkit.org（指定なし）。付録 B への追加を提案する

## 台帳への提案

- なし（このページは問題を載せない）

## 用語集への提案

- 語「色変記事」｜anchor `color-change-article`｜「レーティングの色が上がった人が、学んだことや練習の方法を振り返って書いた記事。」（本文では短く言い換えずに使っている。リンクは張っていない）
- 語「バーチャル参加」｜anchor `virtual-contest`｜「終わったコンテストに、本番と同じ時間配分で後から参加する練習。AtCoder の機能と、AtCoder Problems のバーチャルコンテストがある。」（本文では practice-method#speed へリンクした）

## 手引きへの提案

- guide の生成ブロックを持つページ（roadmap・problem-sets など）では、sections の節の見出し `## … {#anchor}` を生成ブロックの直前に手で置き、ブロックの中は `###` から始まる、という形を手引き §4 か §13 に書いておくとよい（今回は骨格で見出しがなかったので自分で置いた）
- 到達の目安の数値（解く確率・解き終える時刻）は contest-strategy#time-targets と roadmap#targets に重なって載る。持ち主を contest-strategy にし、roadmap は 3 行の要約とリンクにした。この分担を決めておくとよい

## 問題の補充の候補

- なし（catalog の problems は空で、hub・guide は問題 0〜3 でよい）

## 未解決の点

- front matter の related にある `atcoder-system#difficulty-by-position` は、atcoder-system が stub で節がまだない。本文では同じ内容の contest-strategy#difficulty-by-position へリンクした。related を `contest-strategy#difficulty-by-position` に変えるか、atcoder-system にその節を置くかをメインで決めてほしい
- 本文で problem-sets・reverse-index-signs・reverse-index-constraints・thinking-checklist（どれも stub）へはページへのリンクにした。problem-sets の「最近の ABC → ページ」の表の節が書けたら、節へのリンクに張り替える
- contest-strategy・practice-method・knowledge-map は同じバッチで書かれている途中のページで、その節の anchor（difficulty-by-position・time-targets・upsolve・speed・choosing-problems・progress）を使った。anchor が変わったら直す必要がある
- 「2023 年 9 月の abc319 以降、E〜G の難しさに一方向の変化は見えない」は research/00 §2.3.4（ap.py による集計）に拠った。半年ごとの中央値は再集計していない
- 黄の練習の問題集の例が典型90 の★7 だけと薄い。EDPC・鉄則本などの帯の対応は problem-sets の執筆で確かめてから足すとよい

## 検証の指摘への対応（verify/roadmap.md）

- 1（直すべき）：F の箇条を数で言える事実（データ構造 11 問、単独のページでは言い換え 4 問）にとどめ、reformulation#then-data-structure は「言い換えはこの節にある」程度の誘導にした。#practice の「青」の箇条から割合の主張を外した
- 2（直すべき）：本文と参考の著者名を bluebery1001 氏に直した
- 3：かぎかっこを外して言い換え、problem-sets#typical90-stars へのリンクを添えた
- 4：8 問体制（abc212〜abc318）の 1 文を足した。ただし直し方の案の「G・Ex は今の G より難しい」は、8 問体制の G の中央値 2326 が今の G 2391 より低いので、「E・F・G は今とほぼ同じ、Ex は今の G より難しい（2912）」とした（research/00 §2.3.4 の表で確かめた）
- 5：指摘 1 の直しとまとめ、累積和を外した
- 6：problem-sets へのリンクを #recent-abc にし、#goal の段落に atcoder-system#difficulty-by-position（図）へのリンクを足した。未解決の点の 1 つ目と 2 つ目の problem-sets の分は解消
- 7：#yellow の繰り返しを「到達の目安のとおり G はまれにしか解けない」の参照にした
- 採らなかったもの：なし。参考（生成ブロックの見出し「G 問題（黄の帯）」）はメインの判断に任せる
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0（警告1 は参考の記事の題名の「！！」で前回と同じ）
