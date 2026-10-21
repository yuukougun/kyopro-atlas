# tree-centroid の報告（b3 執筆）

- 書いたファイル：docs/tree/tree-centroid.md、snippets/tree-centroid/centroid.{cpp,yaml}・pair-across.{cpp,yaml}、docs/img/tree-centroid/walk.svg・center-vs-centroid.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は骨格のまま（4 節、anchor 不変）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致、textlint エラー 0（警告 7：別行数式の中の文の長さ 1、同じ助詞の重複 6。読みにくくない箇所と問題の行（台帳の summary）なので残した）
- 図：render_svg で 360px・720px の PNG にして目で確かめた。catalog の visual（static・priority 2）は walk.svg で代えた
- 追加の確かめ：pair-across.cpp の組み方を、N ≤ 10 の乱択の木 400 個で全探索の最大マッチングと比べ、すべて一致した（一時置き場の bf.py）。centroid.cpp は「重心は 1 個か隣り合う 2 個」「mx の最小と一致」を assert で確かめている
- 使った出典：
  - https://speakerdeck.com/tatyam_prime/gao-nan-yi-du-mu-wen-ti-wojie-kutekunitukuji （新しいドメイン speakerdeck.com。check_noai で noai・noimageai の指定なし。HTTP 200、X-Robots-Tag なし、meta robots="max-image-preview:large"）：重心の定義・2 個のとき辺とみなす見方・移動距離の上限の議論・AGC018 D の方針（文字起こしの部分を読んだ）
  - https://qiita.com/gotoki_no_joe/items/63344a24b906bc9a74c9 ：ABC362 F の方針（列を半分に切って前から組む。逆順に組むと失敗する）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc348_e | pages | tree-centroid に role: practice を足す（tree-dp の practice は残す） | 全頂点への重み付き距離の和を最小にする頂点は重み付き重心。https://qiita.com/gotoki_no_joe/items/6a3a10194d5a276281ca （台帳の evidence 済み） |
| agc018_d | evidence | speakerdeck の URL に加え、可能なら文章の解説を足す | スライドの文字起こしで方針は確かめられたが、式が画像のため細部（引く辺の選び方）は文字だけでは読み切れない |

## 用語集への提案

- 重心｜centroid｜木から取り除いたとき、残るどの成分の頂点数も全体の半分以下になる頂点。1 個か隣り合う 2 個ある（本文ではページへリンクできるので任意）
- 重み付き重心｜weighted-centroid｜頂点に非負の重みがある木で、取り除いた後のどの成分も重みの和が全体の半分以下になる頂点。重みつきの距離の和を最小にする

## 手引きへの提案

- なし（§5 tree の「重心の性質は証明の筋を図で示す」は walk.svg で満たした）

## 問題の補充の候補

練習が 0 問のまま。

- abc348_e（diff 1347）：頂点に重みのある木で Σ C_i d(v, i) の最小値。重み付き重心（または根を動かした差分）。https://qiita.com/gotoki_no_joe/items/6a3a10194d5a276281ca 。水の問題なので練習の先頭に向く
- abc453_f（diff 2811、F. Avoid Division）：ap.py で実在を確認。research 00-curriculum には「木の『葉の重心』を使う構築」とあり、problem-sets.md でもこのページの pair-across に結び付いているが、第三者の文章の解説が見つからず（ikatakos は問題文の引用節があるので読んでいない）、問いを確かめられなかった。裏付けが取れたら力試しの候補
- arc087_d（diff 3252、F. Squirrel Migration）：ap.py で実在を確認。順列で Σ d(i, p_i) を最大にするものの数を数える問題と記憶しているが、第三者の解説で確かめていない。重心で分けた後の包除が本体なので、確かめられれば発展の力試し（このページの pair-across の「順列」の段落と対応）

## 未解決の点

- AGC018 D の方針の「重心が 1 個なら重心とそれに接する最も軽い辺の先を両端にする」は tatyam のスライドの文字起こしに基づく。式の部分が画像で読めないので、検証役は別の解説でも確かめてほしい
- 「全頂点への距離の和は重心で最小」を tree-dp#reroot-difference の確認問題も述べている。内容の重なりは小さく、こちらは証明、あちらは差分の計算に絞っているので両方残してよいと考える
- tree-isomorphism は stub なのでページへのリンクだけ。重心が 2 個のときの扱い（両方試す・辺に仮の頂点を足す）を、同型判定のページを書くときにそろえてほしい
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 3 回（qiita 1・speakerdeck 1・検索 1）

## 検証の指摘への対応（b3 直し）

- 1（直すべき）：落とし穴を「根から遠い頂点ほど小さく見積もり、葉まで重心と誤る。根だけは正しく求まる」に直した
- 2（直すべき）：(a) を採り、2 つの図・代替テキスト・#vs-center の本文の頂点番号を 0〜9 に振り直した（walk の重心は 2、中心と重心の図は直径 0–6・中心 3・辺 4–5・重心 4 と 5）。snippet の cases は 1-indexed の入力なのでそのまま
- 3（直すとよい）：採った。注記の font-size を 13 → 15 にし、walk.svg の下の説明は 2 行に分けた（viewBox の高さ 380 → 390）。720px で重なり・はみ出しがないことを render_svg で確かめた
- 4（直すとよい）：採った。列の変数 `list` を `seq` にし、本文の手順の前に「コードでは重心を `c`、列を `seq` と書く」を添えた
- 5（直すとよい）：採った。「両端を結ぶパス上の辺は通る回数が 1 減るので損は両端の距離以上」「どちらも損は重心に接する辺 1 本で済む」を足した。下限が辺 1 本で済む理由（重心以外を端にすると他の辺でも上限を割る）は力試しの方針の範囲を超えるので書いていない
- 6（直すとよい）：採った。「そこからぶら下がる枝も両方に入るので、両方に入る頂点は少なくともパスの内側の頂点数だけある」と書いた
- 不採用：なし
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 2 本とも一致、textlint エラー 0（警告 7 は直し前と同じ箇所）
- 台帳への提案（検証役から）：abc362_f・agc018_d の checked に 2026-10-21
