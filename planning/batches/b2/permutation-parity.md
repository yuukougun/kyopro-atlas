# permutation-parity（置換の偶奇）の報告と提案

- 書いたファイル：docs/comb/permutation-parity.md、snippets/permutation-parity/parity.{cpp,yaml}、docs/img/permutation-parity/two-sequences.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 期待と違う 0（自己検査で、n ≤ 6 の全順列で巡回の個数と転倒数の偶奇が一致すること、n ≤ 5 で判定が 3 要素の巡回の全探索と一致することを確かめた）、textlint エラー 0・警告 10（図の代替テキストの長さと「と」の重複、数式の中の読点による max-comma、「x と y」の列挙の「と」の重複。どれも誤検出か言い換えにくい列挙）
- 図：two-sequences.svg（静的。visual は priority 3 なので動く図は作っていない）。render_svg.py で 360・720 の幅を目で確かめた。360 では文字が小さいが読める
- 使った出典：scrapbox.io/procon-kirokuyou（abc296_f。check_noai で指定なし）、zenn.dev/koboshi（偶奇が一意に定まることの別証明）、note.com/syamashi/n/nb491ffdf0ca3（arc136_b。check_noai で指定なし、記事に利用条件の記載なし）、en.wikipedia.org「15 puzzle」（スライドパズルの可解性）。ikatakos.com は作業中ずっと 503（メンテナンス中）で読めなかった（下の未解決の点）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc470_f | summary | 許された位置の組の swap をちょうど 10^100 回行ったあとにできる文字列の種類数を求める。 | b1 の multinomial-coefficient の提案と同じ。「（詳細は執筆時に確かめる）」を外す。本文の行はこの文で書いた |
| abc470_f | approach（permutation-parity 側） | swap できる位置の組の連結成分ごとに並べ方を多項係数で数え、どの成分にも同じ文字がなければ偶奇の片方しか作れないので 2 で割る | 本文の例題の方針。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0808_abc470 |
| abc296_f | evidence に追加 | https://scrapbox.io/procon-kirokuyou/ABC296_F_-_Simultaneous_Swap_(500) | ikatakos が読めなかったため、こちらで方針（多重集合 → 重複 → 偶置換）を確かめた |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 恒等置換 | identity-permutation | 何も動かさない置換 $(1, 2, \dots, N)$。すべての $i$ で $P_i = i$ である。 |
| 互換 | transposition | 2 か所の値だけを入れ替える置換。競プロでは swap と呼ぶことが多い。どの置換も互換の積で書ける。 |

本文では「互換」の語を使わず swap と書いた。用語集に足すなら、置換のページ群（permutation-cycles・permutation-parity・inversion-number）で表記をそろえる判断が要る。

## 手引きへの提案

- 付録 A（数え上げ）に「偶置換・奇置換・恒等置換」を足す案。今は「巡回分解」だけがあり、置換のページ群で表記が揺れうる
- §14-11（確認問題を `## 確認問題 {#quiz}` にまとめる）と §3（確認問題を要所に置く）の関係が分かりにくい。本文の節の中に置いた確認問題も quiz にまとめ直した。「要所に置かず quiz の節にまとめる」と §3 側も直すとよい

## 問題の補充の候補

練習が abc296_f の 1 問だけで目安（2〜6）に足りない。

| 問題 ID | 何を問うか | 裏付けの URL |
| --- | --- | --- |
| arc136_b（B. Triple Shift、diff 1358） | 列 A の隣り合う 3 要素を巡回させる操作を繰り返して、列 B にできるかを判定する（多重集合が違えば No、同じ値があれば Yes、なければ転倒数の偶奇が一致すれば Yes）。役割は練習を想定（水の difficulty だが内容はこのページの型そのもの） | https://note.com/syamashi/n/nb491ffdf0ca3 、https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2022/0227_arc136 （後者は 503 で未読） |

ABC の候補は ap.py の題名検索（Swap）で見た範囲では見つからなかった（abc227_e・abc233_f・abc253_g・abc289_e・abc360_e は題名に Swap を含むが、偶奇が鍵になるかは確かめていない。abc227_e は隣接 swap の回数の上限つき数え上げなので関連は薄いと思われる）。本文の応用の型「隣り合う 3 か所だけを巡回させる」は arc136_b の型で、台帳に入れば例題か練習へのリンクにできる。

## 未解決の点

- **ikatakos.com が 503（メンテナンス中）で、abc470_f の解説を自分で読めなかった**。例題の内容は、台帳の approach（b1 で multinomial-coefficient の執筆者が ikatakos で確かめたもの）、研究ノート 00-curriculum の記述、検索結果の抜粋（連結成分ごとの多重集合の並べ方と偶奇の補正）と一致する範囲で書き、方針の正しさは自分で数学的に確かめた（成分の中の並べ替えは辺の swap で作れ、10^100 は偶数で十分大きい）。答えの法の値は確かめられなかったので、本文では「法が素数なら 2 の逆元を掛ける」とだけ書いた。検証役は ikatakos が戻ったら例題の節を照合してほしい
- abc470_f で辺（swap できる組）が 0 本の場合があるかは確かめていない。本文は「辺が 1 本以上あれば」と条件を付けて書いた
- スライドパズルの可解性（縦横 2 以上の盤で偶奇の条件を満たす配置はすべて作れる）は en.wikipedia の 15 puzzle の記述によった。応用の型の 1 行だけで、例題はない
- 動く図は作っていない（priority 3）。visual の text「互換の積で置換を作り、操作で偶奇が変わらないことを色で示す図」は、静的な図（2 通りの swap の列で同じ置換を作り、各段の N − c の偶奇を実線・破線と色で示す）で代えた
- 使用量の目安：道具の呼び出し 約 45 回、Web 取得 約 12 回（うち ikatakos の 503 が 3 回）

## 検証の指摘への対応（b2）

- 指摘 1（直すべき）：#three-cycle の応用の型を「組の集まりは変わらない。そろえる置換は位置の付け替えを受けるだけで、偶奇は同じ」に直した
- 指摘 2：#exactly-k の「swap できる位置の組が決まっている」に「K が十分大きいとき」の条件、小さい K の最小回数は一般に求めにくいこと、組が 1 つもなければ操作できないことを足した
- 指摘 3：箇条を「1 か所だけ共有する」とし、同じ組を 2 回 swap する場合は捨てると足した
- 指摘 4（採らない・提案のまま）：練習の追加は台帳への登録が要るので、執筆者は書けない。上の「問題の補充の候補」の arc136_b を台帳に入れるかはメインが決める。入れば「隣り合う 3 か所だけを巡回させる」の箇条から練習へリンクする
- 指摘 5：図を幅 520 の viewBox にし、4 回の列を 2 行に折り返した（2 行目の頭に「（続き）」）。文字は 17〜20。360px の PNG で読めることを目で確かめた
- 指摘 6：自己検査 2 を 600 回にし、奇数回は値がすべて異なる列（a[i] = 7i + 3）を試すようにした。cases に (5,3,1,4,2) → 昇順（No）・→ (2,1,3,4,5)（Yes）を足した
- 指摘 7：sgn(PQ) の式をやめ、「続けて行った並べ替えの符号は、それぞれの符号の積」と文で書いた
- 指摘 8：参考の注記を「多重集合・置換の偶奇・重複による判定」とした
- 台帳への提案（検証役から）：abc470_f の approach を「どの成分にも同じ文字がなければ 2 で割る」に直す。abc296_f の evidence に procon-kirokuyou を足す
