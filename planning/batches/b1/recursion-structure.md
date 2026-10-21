# recursion-structure（再帰的な構造）の報告と提案

- 書いたファイル：docs/basics/recursion-structure.md、snippets/recursion-structure/{burger,kth-char,carpet}.{cpp,yaml}、docs/img/recursion-structure/burger-kth.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（3 片とも期待どおり）、textlint（エラー 0、警告 6）
  - 残した警告：折りたたみの見出しの行（86・123・171・186。中身が 1 文として数えられる誤検出）、図の代替テキスト（76）、数式を含む箇条書き（119）
- 図：静的な SVG 1 枚（visual は priority 2。レベル 2 のバーガーの下から 10 枚を数え、レベル 1 へ降りる道筋）。catalog の「呼び出し関係を木で示す」は、降りる先が 1 つだけの道筋の図で代えた。SVG は描画して目で確かめられていない（手元に描画の道具がない）ので、検証で見た目を確かめてほしい
- 使った出典：drken1215.hatenablog.com の 4 記事（台帳の evidence。例題・練習の問いと方針を確かめた）。新しいドメインはない

## 台帳への提案

- なし（使った 4 問の summary・役割は台帳のとおり）
- 参考：typical90_b の approach「再帰（または bit 全探索）」に対し、evidence の drken の記事の解法は bit 全探索だけである。本文の方針は両方を書いた

## 用語集への提案

- なし。「スタック（関数呼び出しの）」を用語集に入れるなら：語「コールスタック」｜anchor `call-stack`｜定義「関数を呼ぶたびに戻り先と局所変数を積む領域。再帰が深いと使用量が上限を超えて落ちる（スタックオーバーフロー）。」（本文ではリンクしていない）

## 手引きへの提案

- 基礎の technique の構成（§4）に「上位の手法とのつながり」があるが、見出しの文字と anchor が決まっていない。recursive-enumeration と同じ `## 上位の手法へのつながり {#next-steps}` にそろえる案（このページは「上位の手法とのつながり {#next-steps}」で書いた。どちらかに統一してほしい）

## 問題の補充の候補

| 問題ID | 何を問うか | 役割の案 | 裏付けの URL |
| --- | --- | --- | --- |
| abc380_d（D. Strange Mirroring、diff 849） | 文字列の後ろに大文字・小文字を入れ替えたものを連結する操作を繰り返した文字列の、K 文字目（K は 10^18 程度まで）を答えるクエリ。長さが倍々に増えるので、K を含むブロックを探して前半へ戻ることを約 60 段繰り返す | 練習（depth の節「必要な深さは log K」の代表。研究ノートでも depth の例に挙がっている） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc380-d.html |

- ap.py で実在・題名・difficulty を確かめた（`OK abc380_d D. Strange Mirroring diff=849`）。ikatakos のページには ABC380 の記録がなかった
- 本文では台帳にないため問題に触れず、depth の節は自作の構造（$S_n = S_{n-1} + c_n + S_{n-1}$）で説明した。追加されたら練習に入れ、方針に「長さが倍々なので K を含むブロックを探して反転の回数を数える」を書くとよい

## 未解決の点

- 再帰の深さとスタックの節は、手元の上限（8 MiB が多い）と AtCoder の上限の数値を書かず、cpp-environment（stub）へリンクした。cpp-environment の stack-depth の節が書かれたら、節へのリンクに替えたい
- cpp-lambda の recursive-lambda・self-argument の節へは、ページが stub なのでページへのリンクにとどめた
- catalog の frequency_evidence の recent に abc476_g があるが、台帳ではこの問題は lis のページの力試しで、このページの問題ではない。再帰的な構造との関係（popcount の構造）は確かめていない
- 使用量の目安：道具の呼び出し約 25 回、Web 取得 7 回（うち検索 2 回）

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：#depth の「レベルを先に下げる」から「（または終わる）」を消し、「$S_{n-1}$ で終わる構造なら、末尾から数えた $K$ 番目に限って使える」と書き分けた
- 指摘 2（直すべき）：burger-kth.svg のレベル 1 の段の箱を幅 90 に広げ、ラベルを 2 段（「レベル 0」「+1」・「P」「+1」）にした。空の 4 つ目の括弧は、使わない部分なので括弧ごと消した（レベル 2 の段の扱いにそろえた）
- 指摘 3：注記の文字を 13〜14px から 15px に上げた。図の幅（760）は変えていない（レベル 2 の 13 枚を 1 行で見せるため）。下の 2 本の説明文は残した
- 指摘 4：練習の方針の典型90 002 に、再帰は `(` を先に試すこと、bit 全探索は上位の bit を先頭の文字・0 を `(` にすると辞書順になることを書いた
- 指摘 5：擬似コードの直後に、部品ごとの $\mathrm{len}(p)$・$\mathrm{all}(p)$ の読み替えを 1 段落足した
- 指摘 7：本文側の「集計の問題で $K$ 番目だけを求めても答えは出ない」を消し、落とし穴に寄せた
- 指摘 8：kth-char.cpp の `rec` のコメントを「1-indexed、1 <= k <= len[n]。n = 1 で必ず止まる」にした
- 指摘 9：この例では $2\,\mathrm{INF} + 1$ が収まるので計算してから min を取ればよいこと、部品が多い・INF が大きいときに足す前の確かめが要ることを書き分けた
- 指摘 6：執筆者が直す欄ではないので、下の提案に回した

## メインへの提案（検証の指摘 6）

- front matter の frequency_evidence の「recent 1（abc476_g）」は、abc476_g（Increasing Popcount、diff 2477）が台帳では lis のページの力試しで、このページの手法との関係が確かめられていない。recent から外すか、上の「問題の補充の候補」の abc380_d（D. Strange Mirroring、diff 849）を台帳に入れて recent の根拠に替える案
- 台帳の abc115_d・typical90_b の checked に 2026-10-21 を入れてよい（検証役が evidence で問いと方針を確かめた）
