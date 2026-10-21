# run-length-encoding の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/run-length-encoding.md、snippets/run-length-encoding/encode.{cpp,yaml}・handstand.{cpp,yaml}、docs/img/run-length-encoding/runs.svg
- front matter で変えたもの：complexity（`圧縮・復元 O(N)、塊の数を R として塊の列の処理は O(R)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 本とも一致）、textlint（エラー 0・警告 7）
  - 残した警告：51・53 行の読点の数（(0, 2) などの組の中の読点を数えた誤検出）、55・78 行の括弧の対応（半開区間 $[i, j)$ の誤検出）、71 行の文の長さ（数式を含む段落の文の区切りの誤検出）、184 行の助詞「に」（台帳の summary の行。fix_problems が作り直すので本文では直さない）、189 行の文の長さ（折りたたみの箇条書きを 1 文として数えた誤検出）
  - handstand.cpp は長さ 7 以下・K ≤ 3 の乱択 300 件で全探索と一致を確かめた。ABC136 D の振り分けの式（$\lceil A/2 \rceil + \lfloor B/2 \rfloor$ など）も長さ 10 以下の乱択 2000 件でシミュレーションと一致を確かめた
  - SVG は手元に描画の道具がなく、目で確かめていない。座標は計算で決めた（幅 560 に収まる）。検証役に描画の確認を頼みたい
- 使った出典：
  - https://drken1215.hatenablog.com/entry/2019/04/14/222900（例題 ABC124 D：番兵の塊と塊 2K+1 個の窓）
  - https://drken1215.hatenablog.com/entry/2024/11/17/012903（ABC380 C）
  - https://github.com/Reputeless/tenkei_90/blob/main/084.md（典型90 084。台帳の evidence はリポジトリの入口なので、個別のページを参考に挙げた）
  - https://drken1215.hatenablog.com/entry/2020/12/29/190100（ABC136 D：偶奇の振り分け・ダブリングの別解）
  - https://drken1215.hatenablog.com/entry/2020/05/16/005300（ABC140 D：反転 1 回で境界は高々 2 減る）
  - https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2025/0830_abc421（ABC421 D：解説の部分だけ）
  - 候補探し：https://drken1215.hatenablog.com/archive/category/ランレングス圧縮 と下の候補の記事
  - 新しく noai を確かめたドメイン：なし（どれも付録 B にある）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| typical90_cf | evidence | https://github.com/Reputeless/tenkei_90/blob/main/084.md を足す（今はリポジトリの入口だけ） | 同 URL |
| abc136_d | summary | 「各マスに L か R が書かれたマス目で、子どもが 10^100 回移動した後に、各マスにいる人数を求める。」（textlint の助詞「に」の重なりを避けるため、読点を足すか「マス目の上で」などに直す） | 表記だけの直し |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 塊（ラン） | run | 列の中で同じ値が続く極大な区間。隣と値が違うところ（境界）で列を切ると得られ、塊の数は境界の数 + 1 である |
| 境界 | boundary | 列の隣り合う 2 要素で値が違う位置。区間の反転では、区間の両端をまたぐ 2 か所でしか増減しない |

（本文では用語集へのリンクは張っていない。足すなら「塊」の最初の出現（導入の段落）に張ると良い）

## 手引きへの提案

- §2.2 の「いつ使うか」の書き方：signs が名詞句（「同じ文字・値が続く部分」）のとき、要点では「〜を問われる」と述語を足した。signs を要点にそのまま写すか述語を足してよいかを明記するとよい
- §10 の練習の方針の折りたたみの箇条書きは、textlint が 1 文として長さを数えるので警告が出る。見本と同じく句点なしでよいなら、§13 の 8 に「折りたたみの箇条書きの文の長さの警告は残してよい」と足すとよい

## 問題の補充の候補

基礎のページなので練習は足りている。「塊ごとに数える」型と、塊が繰り返しでつながる型を補うなら次が候補（どれも ap.py で実在と diff を確かめた）。

| 問題 ID | diff | 何を問うか | 使い方 | 裏付けの URL |
| --- | --- | --- | --- | --- |
| abc329_c | 205 | 英小文字の文字列で、1 種類の文字だけからなる空でない部分文字列の種類数を求める | 文字ごとに最長の塊の長さを取って足す | https://drken1215.hatenablog.com/entry/2023/11/21/032500 |
| abc369_c | 323 | 数列の連続部分列のうち等差数列であるものの個数を求める | 隣接差の列を塊に分け、塊ごとに数える（台帳にあり、今は imos の練習。run-length-encoding の練習にも足すか、差分列の側に置くかはメインに任せる） | https://drken1215.hatenablog.com/entry/2024/09/01/153129 |
| agc039_a | 517 | 文字列 S を K 回つないだ文字列で、隣り合う文字がすべて異なるようにするための書き換えの最小回数を求める | 塊ごとに ⌊長さ/2⌋。全部が同じ文字の場合と、先頭と末尾の塊がつながる場合を分ける | https://drken1215.hatenablog.com/entry/2020/11/11/203000 |

## 未解決の点

- 骨格の related に difference-sequence があり、本文でも「境界の数＝差分列の 0 でない項の数」と書いた。difference-sequence のページがこの見方を扱うかは未確認（stub）
- [塊ごとに偶奇で振り分ける](#parity-per-run) では ABC136 D の型を本文で説明したが、問題 ID は出していない（練習の行と方針の折りたたみにだけ置いた）
- [ランレングスのまま処理する](#keep-compressed)（水）では abc452_g の型（圧縮してから部分文字列の種類を数える）を ID なしで suffix-array へのリンクだけにした。abc452_g は台帳で suffix-array・suffix-automaton のページに付いており、このページの問題には入れていない
- 動く図は作っていない（catalog の visual は priority 2・static）。静的な SVG 1 枚で代えた

## 検証の指摘への対応（2026-10-21）

- 直すべき 1・2、直すとよい 3〜9 をすべて直した。採らなかった指摘はない
- 3（参考の題名）は、記事の題名の段と色を全件で省く形にそろえた（abc380_c を「(300 点)」に）
- 9（図）は下の段のラベルを「len[i]（文字）」に縮めて 13px にし、注に「（ ）の中は塊の文字」を足した
- 台帳への提案（checked の日付、typical90_cf の evidence の追加）は検証の記録のとおりで、メインの反映を待つ
