# grundy-number（b2）の報告と提案

- 書いたファイル：docs/comb/grundy-number.md、snippets/grundy-number/{subtraction,range-formula,kayles}.{cpp,yaml}、docs/img/grundy-number/range-table.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 本とも期待どおり、textlint エラー 0（警告 16：読点の数・助詞の重なり・数式や画像の代替テキストの括弧の誤検出。§13-8・§14-25 の範囲）。SVG は render_svg.py で 360px・720px を目視した（720px の PNG は下が切れて出るが、360px では全体が見え、図自体の問題ではない）
- 使った出典：参考の節のとおり（en.wikipedia.org・github.com・programming-hiroba.com・qiita.com・kmjp.hatenablog.jp・drken1215.hatenablog.com。どれも付録 B にある）。新しいドメインはない

## 台帳への提案

- abc368_f｜evidence の 3 つ目 `https://programming-hiroba.com/`（サイトのトップ）は問題の裏付けにならないので外す
- abc368_f｜qiita（hyouri）の記事は「素因数の個数」ではなく「約数への mex を篩の要領で表にする」方針。approach の「素因数の個数（重複を含む）」は programming-hiroba の記事で裏付けられる（記事は Grundy 数の語を使わず「素因数の個数の Nim」として説明）。直しは不要だが、evidence の役割の注記として
- abc206_f｜grundy-number では alternatives の summary（区間を 1 つ選ぶと重なる区間が使えなくなるゲーム…）が使われた。問題ない
- 外す・加える・役割の変更はない

## 用語集への提案

- 不偏ゲーム｜impartial-game｜どちらの手番でも、同じ局面で打てる手が同じゲーム。Nim や石取りが例で、Grundy 数が定義できる。先手と後手で手が違うものは非不偏ゲーム（partizan-games）
  - 本文では用語集にリンクしていない（anchor がまだないと check_pages がエラーにするため）。足したら導入の「不偏ゲーム」の最初の出現にリンクを足す
- ゲームの和｜（ページの別名にあるので用語集には不要。ニム和は nim の提案 nim-sum のとおり）

## 手引きへの提案

- §13-5 は「用語集へのリンクはまだなくても書いてよい」とするが、check_pages は用語集にない anchor をエラーにする。どちらかにそろえるとよい（今回はリンクを外して提案に回した）
- render_svg.py の 720px の PNG で、縦に長い図（viewBox 450×398）の下側が切れた。撮影の高さを図に合わせると目視しやすい

## 問題の補充の候補

- arc091_d（ARC091 F. Strange Nim、diff 2395）：各山 i で、石が X 個のとき 1 個以上 ⌊X / K_i⌋ 個以下を取れる Nim の勝者を求める。小さい表から「X が K の倍数なら X / K、そうでなければ X − ⌈X / K⌉ 個の山と同じ値」を見つけ、商が同じ間はまとめて引いて速くする。規則を見つける節（patterns）の力試し向き（黄の難しさ）。裏付け：https://kmjp.hatenablog.jp/entry/2018/03/11/1130
- arc087_c（ARC087 E. Prefix-free Game、diff 2431）：trie の b1 の報告の候補。Trie の空いた部分木ごとの Grundy 数を XOR する型。第三者の解法の解説は今回も見つけられなかった（kmjp の ARC087 E の記事は検索で出なかった）ので、入れるなら evidence を探す必要がある
- abc319 以降の Grundy 数の問題は abc368_f のほかに見つけていない（ap.py で題名から探す方法がないため。メインで AtCoder Tags などから探すとよい）

## handoff の申し送り（nim との配分）への答え

- 逆形 Nim は nim#misere に置いたままにし、grundy-number は「使えない場合」の節からリンクするだけにした（一般の逆形は Grundy 数で扱えない、とだけ書いた）
- arc105_d は game-basics の練習（真似戦略）のままでよい。grundy-number には載せていない
- arc091_d は上のとおり grundy-number の力試しとして提案する
- nim#bounded の「Grundy 数のページ」へのリンクは、grundy-number が draft になったので `../comb/grundy-number.md#patterns` に張り替えられる（nim の執筆者の申し送りどおり）

## 未解決の点

- 例題・練習の問題の制約（A_i の上限など）は第三者の解説から確かめきれなかったので、本文には具体的な上限を書かず「山が大きいので」「値の範囲が小さければ」のように書いた
- ABC278 G は、L と R の関係によっては真似戦略（中央を取って左右対称にする）でも解けるはずだが、裏付けの解説（kmjp）は Grundy 数だけを使うので、本文の方針も Grundy 数だけにした
- abc297_g の式 ⌊(x mod (L+R)) / L⌋ は証明を載せず、コード片で L ≤ 10・R ≤ 20・x ≤ 500 のすべてで表と一致することを確かめた形にした（kmjp も実験で見つけたと書いている）
- Kayles の周期 12 が x = 71 から始まることはコード片で x ≤ 1000（手元では 3000）まで確かめた。以降ずっと続くことは Wikipedia の記述に頼った
- 動く図は作っていない（visual は static・priority 2 で、静的な SVG にした）

## 検証の指摘への対応（b2）

- 直すべき：0 件
- 直すとよい 4 件はすべて直した
  1. #sum：「すべてのゲームで動けなくなった人が負けである」に直した
  2. #patterns と落とし穴の Kayles に、[DP の節](#dp) へのリンクを付けた（#patterns ではゲームの説明も一言入れた）
  3. 確認問題 1：「先手は勝てるか。勝てるなら勝つ手を 1 つ答えよ」に直した
  4. range-formula：本文に「`table(L, R, n)` は上の DP の `grundy_table` で取れる個数を L 以上 R 以下にしたものと同じ」と書き、core の先頭にも同じ旨のコメントを入れた
- 採らなかったもの：なし
- 台帳への提案（検証役から、メインで反映を）：typical90_ae・abc278_g・abc255_g の `checked` に 2026-10-21 を入れる。abc368_f の evidence からサイトのトップ `https://programming-hiroba.com/` を外す（執筆時の提案と同じ）
