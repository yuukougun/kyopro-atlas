# lexicographic-greedy の報告（工程8b・バッチ b1）

- 書いたファイル：docs/basics/lexicographic-greedy.md、snippets/lexicographic-greedy/smallest-subsequence.{cpp,yaml}、snippets/lexicographic-greedy/kth-ab-string.{cpp,yaml}、docs/img/lexicographic-greedy/smallest-subsequence.svg
- front matter で変えたもの：complexity（`長さ L・候補 σ 種類・判定 1 回 T として O(LσT)。判定を表や個数で O(1) にすれば O(Lσ)`）・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 片・期待と違う 0）、textlint（エラー 0・警告 12。助詞の重複と数式を含む文の長さ、数式の中の `[i, …)` を括弧の対応の誤りと見るもの）
- コード片は Python の全探索とランダムなケース（部分列 300・K 番目 200）で突き合わせた（一時置き場で実施）
- 図：静的な SVG（S = bacbab・K = 3 で、各段の取れる範囲と試した候補・確定した位置）。catalog の visual は priority 2 なので動く図は作らず、div も置いていない。SVG を描画する道具が手元になく、見た目は目で確かめていない（XML として読めることだけ確かめた）。検証役に描画の確認を頼みたい
- 構成：基礎の目安に沿い、sections の 5 節＋落とし穴・使い分け・例題・練習・力試し・参考。確認問題は節の中に 3 つ置いた

## 使った出典

- drken ABC076 C・典型90 006・ABC223 D・ARC097 C（ABC097 C）・ABC009 C（いずれも drken1215.hatenablog.com）：例題・練習・力試しの問いと方針
- ikatakos ABC202 のメモ：D の解説部分だけ（先頭を a にしたときの個数と K の比較）
- 新しく noai を確かめたドメイン：なし（すべて付録 B のドメイン）

## 台帳への提案

- abc076_c｜approach｜「T を置ける位置をすべて試し、残りの ? を a にした候補の最小を取る」に直す｜**現在の「T を置ける最も後ろの位置を選び」は誤り**。反例 S = ab?、T = b：位置 2 に置くと abb、位置 1（もともとの b）を使うと aba で後者が小さい。Python の全探索とランダムなケースで反例を確かめた。evidence の https://drken1215.hatenablog.com/entry/2025/01/22/125627 も全位置を試す方針。catalog（basics.yaml の lexicographic-greedy の problems）の approach も同じ誤りがある（catalog は凍結なので台帳だけ直せばよい）
- abc076_c・abc202_d・arc097_a・typical90_f・abc009_3｜checked｜2026-10-21｜各 evidence で問いと方針を確かめた
- abc223_d｜lexicographic-greedy 用の summary｜本文の行は「「a は b より前」の条件…」のまま。主の summary（「A_i は B_i より前」…なければ −1）の方が正確なので、alternatives を主にそろえてもよい（任意）

## 用語集への提案

- なし（「実現可能性の判定」を用語集に足すことも考えたが、本文では「残りで実現できるかの判定」と言い切り、リンクしていない）

## 手引きへの提案

- 基礎の technique で sections が 5 節あり、どの節も「応用の型」に当たる。目安の「要点 → 応用の型 → 落とし穴 → 上位の手法とのつながり」の「つながり」は、独立の節にせず各節の中のリンクと「使い分け」にまとめた。この扱いでよいか、手引きに 1 行あるとよい
- 「上の図」を避ける規則（§3）について、図の直後の説明文の書き出しの例（「図は、…」）があると迷わない

## 問題の補充の候補

- 確認済みの問題で役割の数（例題 1・練習 4・力試し 1）は足りているので、補充は必須ではない。frequency_evidence が recent 0 なので、abc319 以降の「辞書順最小を出力」の型があれば足したい（今回は探していない）
- 候補（research/08 §5 にあり、台帳で未確認なら確かめが要る）：
  - abc225_f｜K 枚を選んで連結した辞書順最小。a+b < b+a で並べた後に後ろから DP（前からの貪欲だけでは誤る）。exchange-argument か本ページの青の節の力試し向き｜https://merom686.hatenablog.com/entry/2021/10/30/235859
  - arc081_c｜部分列でない最短の文字列の辞書順最小。次の出現位置の表で後ろから DP し、前から貪欲に復元する。本ページの「判定が重い型（後ろからの DP で判定の表を作る）」の例に合う｜https://drken1215.hatenablog.com/entry/2018/09/22/201000

## 未解決の点

- 「番号の小さい頂点をできるだけ前に置く」順列は、逆向きのグラフで大きい順に取り出して末尾から並べる、と本文に書いた。よく知られた事実だが、今回は出典で確かめていない（確認問題の小さい例は手で確かめた）。検証役に確かめてほしい
- 関連ページ（subsequence-matching・topological-sort・binomial-coefficient・dp-reconstruction）はまだ stub なので、節（#lexicographically-smallest など）ではなくページへリンクした。draft になったら節へのリンクに直せる
- 図の見た目（文字のはみ出し）は未確認

## 検証の指摘への対応（2026-10-21）

- 指摘 1（直すべき）：落とし穴の例を S = bacbab・K = 5 に替えた（判定なしは a(1)→a(4)→b(5) で 3 文字で行き止まり、判定ありは acbab）。「最も前の出現」の話は S = abab・K = 2（位置 2 の a で ab、正しくは aa）の別段落に分けた。64 行は「行き止まることがある」とした
- 指摘 2：「知られている」を消し、末尾から決める理由の直感と、前から小さい順で 1 が遅れる理由を足した。正しさは全探索で確かめられる、と書いた
- 指摘 3：draft になったページの節へリンクを直した（string-basics#lexicographic-order・topological-sort#lexicographic・binomial-coefficient#kth・dp-reconstruction#dp-kth-lexicographic / #lexicographic-min・greedy-basics#counterexamples）。使い分けの連結の項に string-basics#concat-order を足した。167 行の「トポロジカルソートのページ」はリンクなしのまま（98 行で節へリンク済み）
- 指摘 4：図を幅 440 に組み直した（注記を各段の箱の下へ、凡例を 3 行に、位置の番号を 13px に）。見た目の画像での確認はしていない（文字幅の見積もりでは右端に余白あり）
- 指摘 5：範囲外の箱の枠線を灰色（#999）にし、説明を「青く塗った実線の箱」とした
- 指摘 6：例を $\binom{199}{99}$ ≈ 4.5×10^58（a・b が 100 個ずつ）に替え、LIMIT のコメントに前提（K ≤ 10^18 < LIMIT、2 × LIMIT が long long に収まる）を書いた
- 採らなかった指摘：なし
- 台帳への提案（上の「台帳への提案」）は検証役も賛成。変更なし
