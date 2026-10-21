# dp-order（DP の計算順序）の報告

- 書いたファイル：docs/dp/dp-order.md、snippets/dp-order/{backward,traveler}.{cpp,yaml}、docs/img/dp-order/six-orders.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー0・警告0）、fix_problems --check（直すべき行0）、check_snippets（2 件とも一致）、textlint（エラー0、警告10。すべて数式の中の括弧・読点・数式を含む文の長さ、図の代替テキストの長さによる誤検出）
- 図：six-orders.svg は Python で生成した（生成スクリプトはリポジトリに置いていない）。手元に SVG の描画器がなく、見た目は目視で確かめていない。XML としての妥当性だけ確かめた。検証で表示を確かめてほしい
- 動く図：作っていない（catalog の visual は priority 2・static）
- 使った出典：参考の節の 5 件（ikatakos.com 3 件・kazun-kyopro.hatenablog.com・torus711.hatenablog.com）。どれも付録 B にあるドメインで、新しく noai を確かめたドメインはない。ikatakos 氏の記事は解説の部分だけを読んだ

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc266_e | evidence | 1 件目の `https://kazun-kyopro.hatenablog.com/entry/ABC/NNN/X`（URL の型の置き場所が残ったもの）と 3 件目のブログのトップを外し、`https://kazun-kyopro.hatenablog.com/entry/ABC/266/E` だけにする | 置き場所の URL は実在の記事ではない |
| abc188_e | approach | 「後ろから『そこから行ける町の最高の売値』を埋める（前から『そこへ来られる町の最安の買値』でもよい）」 | ikatakos 氏の記事に「先頭から考えてもいい」とある |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 依存グラフ | dependency-graph | DP の状態を頂点とし、「状態 y の値を使って状態 x を計算する」ときに辺 y → x を張った有向グラフ。計算順序は、このグラフのトポロジカル順である。閉路があれば普通の DP では計算できない |

（本文は `../guide/glossary.md#dependency-graph` にリンクしている。`#state` は既存）

## 手引きへの提案

- §8 の SVG について、描画の確認の手段（例：リポジトリで使える rsvg-convert や playwright の有無）を手引きに書いておくと、執筆者が図の見た目を確かめられる

## 問題の補充の候補

| 問題 ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc232_d | 壁のあるグリッドを左上から右か下へだけ進むときに通れるマスの数の最大（行ごとに左から回す順が依存の向きに合う） | 練習（diff 539 と易しい。添字の順の入口として） | https://kazun-kyopro.hatenablog.com/entry/ABC/232/D（02-dp §5.3 にある。本文では未読） |

- abc319 以降の問題は abc341_f（練習）だけである。水のページに 1 問以上という目安は満たすが、例題は abc188_e・abc197_e と古い。abc319 以降で「後ろから」「値の順」が主役の E を、ap.py と第三者の解説で探す余地がある（今回は探しきれていない）

## 未解決の点

- 例題 ABC188 E の「利益が負になりうる（必ず 1 回売買する）」は、ikatakos 氏のコードで答えの初期値が -10^18 であることからの判断で、記事の文章では明言されていない。検証で確かめてほしい
- 例題 ABC197 E の「ほかの色のボールは通り過ぎても回収しなくてよい（端から端へ動く間に同じ色のボールを拾える）」は、ikatakos 氏の記事の「途中の同じ値のボールは自然に回収できる」という説明に基づく
- 落とし穴の節の pitfalls は、手引き §13.1 では定型の節（sections に載せない）にあたるが、骨格の sections に入っていたので、見出しの文字を sections の title とそろえて残した
- 使用量の目安：道具の呼び出し 約 30 回、Web 取得 8 回
