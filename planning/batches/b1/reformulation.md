# reformulation（言い換えの典型）の報告と提案

- 注意：指示は担当を `docs/thinking/reformulate.md` としていたが、catalog と骨格の id は `reformulation`（`docs/thinking/reformulation.md`）なので、そのページに書いた。コード片・図も id に合わせて `snippets/reformulation/`・`docs/img/reformulation/` に置いた。この提案のファイルだけは指示どおり `reformulate.md` の名前にした（ほかの提案のファイルにそろえるなら `reformulation.md` に名前を変えてほしい）
- 書いたファイル：docs/thinking/reformulation.md、snippets/reformulation/separate-indices.{cpp,yaml}、docs/img/reformulation/prefix-suffix.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21）。sections は変えていない
- 検査の結果：
  - check_pages --page reformulation：エラー 0・警告 0
  - check_snippets snippets/reformulation：期待と違う 0
  - textlint：エラー 0。警告 10 は、数式を含む文の長さ・読点の数、半開区間 `[l, r)` の括弧の対の誤検出、表の行の長さ
  - fix_problems --check：このページの直すべき行は 0。全体では math/digit-and-mod.md の 6 行が ID だけの形で残っていて終了コード 1（ほかの執筆者の担当。fix_problems を流せば直る）
- 使った出典：drken（abc324_e・abc105_d・agc003_a・abc146_e）、comet725 の Qiita（abc460_e）、ikatakos（abc460_e・abc479_f、解説の部分だけ）。新しいドメインはない
- 動く図：catalog の visual は static・priority 2（元の条件と言い換えた条件の対応表）なので、本文の表で代えた。ほかに例題 ABC324 E の静的な SVG（前からの一致長と後ろからの一致長）を 1 枚作った

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc460_e | summary | N 以下の正の整数の組 (x, y) のうち、x と y を 10 進でこの順につないだ数が x + y と M を法として合同になるものの数を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0530_abc460 （E の解説部分）、https://qiita.com/comet725/items/7ac6436793b6e5d1ee4f |
| abc460_e | approach（reformulation） | y の桁数 d ごとに (10^d − 1)x ≡ 0 (mod M) に変形して y を消し、x を gcd で数える | 同上 |
| abc479_f | summary | 数直線上の N 人を、1 人を 1 歩動かし、その先に人がいれば入れ替わる操作で、それぞれの目的地へ動かすのに要る操作の最小回数を求める。 | https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/1011_abc479 （F の解説部分） |
| abc479_f | approach | 空き位置に仮の人を置いて隣接 swap に言い換え、組を種類で分けて転倒数を数える（実際の人どうしは BIT） | 同上 |
| abc146_e | approach（reformulation の alternatives） | 累積和 S で S_j − j ≡ S_i − i (mod K) と j − i < K に分け、長さ K 未満の窓で数える（a_i − 1 の累積和と同じ） | https://drken1215.hatenablog.com/entry/2024/11/23/183549 （drken は a_i − 1 ではなく S_i − i の形で書いている） |
| abc460_e | 本文の行の summary（digit-and-mod） | digit-and-mod.md の行は「10 進で連結した数」と書いている。上の summary とそろえるなら同じ文にする | — |

## 用語集への提案

- 言い換え｜reformulation｜条件・目的関数・操作を、意味を変えずに（両向きに成り立つ形で）書き直し、既知の手法が使える形にすること。本文ではページへのリンクで済むので、用語集に載せるならページへ飛ばす項目でよい
- 差分列は difference-sequence のページがあるので不要。鍵（連想配列で数えるときの値）は一般語として使い、用語集には足さない

## 手引きへの提案

- 指示の担当名（reformulate）とページの id（reformulation）が違っていた。工程の指示を作るスクリプトの id を catalog から取るようにすると、提案のファイル名もそろう
- thinking の §4 の構成「合図 → 最小の例 → 例題」と、catalog の sections（表・型ごとの節）が並ぶページでは、合図は冒頭の要点と表の前置きで済ませ、最小の例は各節の中に置いた。thinking で sections が多いページはこの形でよいかを §4 に一言あるとよい

## 問題の補充の候補（問題 ID・何を問うか・裏付けの URL）

thinking の例題は 2〜4 問が目安で、台帳の例題は 2 問（abc324_e・abc105_d）だった。足すなら次の候補がある（どれも台帳では確認済みで、ほかのページに置かれている）。

- abc129_e（diff 1547）：a + b ≤ L かつ a + b = a xor b の組の数。表の「a + b = a ⊕ b ⇔ a AND b = 0」の代表。https://drken1215.hatenablog.com/entry/2019/06/10/150000 。今は bitwise-independence・digit-dp の練習。reformulation の練習に足す案
- abc466_e（diff 1027）：区間の反転を切り替え点 2 つに言い換えて DP。操作の言い換えの節の易しい代表。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2026/0711_abc466 ／ https://qiita.com/comet725/items/d9928d9fdb242140f987 。台帳の summary が「（執筆時に確かめる）」なので、difference-sequence の執筆者の確認を待ってから練習に足す案
- abc330_f（diff 1718）：点を合計 K 回以下動かして 1 辺 d の正方形に収める最小の d。独立に分解する節の確認問題の題材（軸をまたぐ合計の制約）。https://ikatakos.com/ の該当回の記録などで裏付けを取ってから練習に足す案（今回は解説を読んでいないので、本文では問題 ID を出さず型だけ書いた）
- abc460_e を例題に格上げする案：式変形で変数を消す型の代表で、abc319 以降の E。今は reformulation・digit-and-mod・counting-mindset の 3 ページで練習なので、例題の持ち主をどこにするかはメインの判断

## 未解決の点

- 例題が 2 問で、どちらも 2023 年以前（abc319 以降は abc324_e だけ）。水のページに最近の E を例題として置く目安を満たすのは abc324_e のみ
- frequency_evidence の abc454_f・abc459_f・abc466_e・abc470_g・abc475_e は本文では扱っていない（差分列・寄与などの別ページの持ち主）。言い換えのページの問題としては使っていない
- 「言い換えてからデータ構造に載せる」（青）の節は、台帳で確認済みの最近の F が abc479_f しかないので、一般の型の説明にとどめた。abc480_f（言い換え＋DP、research/00 §2.3.8）などを裏付けて足すとよい
- 図 prefix-suffix.svg は手元に描画の道具がなく、XML として正しいことだけを確かめた。表示の崩れ（文字のはみ出し）は検証役に見てほしい

## 検証の指摘への対応（planning/batches/b1/verify/reformulate.md）

- 直した：1（隣接 swap と転倒数の両向きの理由）、2（偶数個の中央値の定め方）、3（鍵の登録の順の理由）、4（転倒数の不等号の向き）、5（ABC105 D の添字を §6 の形に）、7（差分列の最小回数の下限と構成を分けた）、8（本文の ⇐ を図の分け方にそろえ、図の説明を本文に移した）、9（図から上下の説明文を外し、ラベルを 16px・文字を 20px にして viewBox を 500×200 に縮めた。画像にしての確認はまだなので、メインの側で表示を見てほしい）、10（XOR の総和の対象を書いた）、12（練習・力試しへの言及を一覧の見出しへのリンクにした）
- 本文では採らなかったもの：
  - 6：台帳の summary の直しなので共有ファイルにあたる。下の提案のとおり
  - 11：difference-sequence が stub のうちは節へリンクできない（手引き §7）。draft になったら `../basics/difference-sequence.md#strict-to-weak` に直すことをメインの控えに残してほしい
- textlint の警告は 10 のまま（`[l, r)` の括弧の誤検出で文の区切りがずれ、136 行の文の長さが大きく出る。エラーは 0）

### 台帳への提案（指摘 6 による修正）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc460_e | summary | N 以下の正の整数の組 (x, y) のうち、x と y を 10 進でこの順につないだ数が x + y と M を法として合同になるものの数を 998244353 で割った余りを求める。 | 上の表と同じ（ikatakos・comet725 の解説はどちらも 998244353 で割った余りを出力する） |
| abc324_e・abc105_d・agc003_a・abc146_e・abc460_e・abc479_f | checked | 2026-10-21 | 検証役が解説で問いと方針を確かめた |
