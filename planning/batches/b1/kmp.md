# kmp の報告と提案（工程8b・b1）

- 書いたファイル：docs/string/kmp.md、snippets/kmp/{prefix-function,match,borders,automaton}.{cpp,yaml}、docs/img/kmp/{shift,border-chain}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない（見出しは sections の title と同じ）
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（4 件すべて一致）、textlint（エラー 0・警告 20）
  - 残した警告：要点・導入の「接頭辞でも接尾辞でもある」の「でも」の重なり（summary の文言どおり）、表を含む段落と図の代替テキストの文の長さ、半開区間 $[l, r)$ の括弧の対の誤検出、数式で切れた文の助詞の重なり
- 動く図：作っていない（visual は priority 2 なので静的な SVG 2 枚で代えた）。動く図にするなら、照合でずらす様子のステップ送りと border の入れ子を、aho-corasick の失敗リンクの図と部品を共有して作る
- 使った出典：snuke のはてなブログ（MP の配列と線形の理由）、Wikipedia 英語版（KMP の 1 文字あたりの比較回数の上界）、cp-algorithms（構成の参考だけ）、ACL document_ja、drken（abc304_f・abc150_f・arc060_d）、ikatakos（abc430_e・abc135_f。解法の部分だけ）、kmjp と merom686（abc312_h）
  - 新しく noai を確かめたドメイン：snuke.hatenablog.com・en.wikipedia.org（どちらも noai・noimageai の指定なし。2026-10-21）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc312_h | summary | N 人が順に希望の文字列を名乗り、それまでの名前と重なるときは希望の文字列を最小の回数だけ繰り返したものを名乗るとき、各人の繰り返しの回数を求める。 | https://kmjp.hatenablog.jp/entry/2023/07/30/0930 （本文の行はこの文で書いた） |
| abc312_h | evidence | kmjp の記事を足す（merom686 の記事は問いの説明がなく、方針だけ） | https://kmjp.hatenablog.jp/entry/2023/07/30/0930 |
| abc304_f | alternatives[0].summary | 「（執筆時に確かめる）」を本体の summary と同じにする | https://drken1215.hatenablog.com/entry/2023/06/07/153403 |

ほかの使った問題（abc150_f・abc430_e・abc135_f・arc060_d）の summary と approach は、evidence の解説と食い違いがなかった。abc135_f の evidence（ikatakos）は解き方をハッシュで書いており、KMP での解き方は本文で自分の言葉で書いた。

## 用語集への提案

- 原始的な文字列｜primitive-string｜より短い文字列の 2 回以上の繰り返しで書けない文字列。最小の周期が長さを割り切らないか、長さそのものであるときに限る（本文ではまだリンクしていない。足すなら kmp#string-period の最初の出現からリンクする）
- border・周期は z-algorithm がすでに `#border`・`#period` でリンクしている。kmp も同じ anchor でリンクした（定義：border は「自分より短く、接頭辞かつ接尾辞である文字列」、周期は「すべての $i$ で $S[i] = S[i + p]$ となる $p$」）

## 手引きへの提案

- sections に `anchor: comparison` の「Z との使い分け（…）」があり、§13.1 の定型の `## 使い分け {#comparison}` と anchor が重なる。今回は sections の title をそのまま見出しにした。定型にそろえるなら sections から外して見出しを「使い分け」にするか、メインで決めてほしい（anchor は同じなのでリンクは壊れない）
- 指示では担当のレベルが「水」だったが、骨格と catalog の level は「青」なので、青として書いた（front matter は変えていない）

## 問題の補充の候補

- 照合オートマトンをそのまま使う青の練習（KMP の表の DP）を探したが、ABC で 1 パターンの KMP オートマトンだけで解ける問題を第三者の解説で裏付けられなかった。候補の abc305_g・abc419_f・abc458_f は複数パターン（Aho-Corasick）なので string-automaton-dp・aho-corasick に任せる
- abc319 以降（7 問体制）の問題がこのページにない（例題・練習はすべて古い ABC か ARC）。水・青のページには 1 問以上という目安を満たしていない。border の連鎖・周期を問う新しい ABC の候補を見つけられなかった（drken の KMP 法のカテゴリは abc150_f・arc060_d と Codeforces の 1 問だけ）

## 未解決の点

- KMP 法の 1 文字あたりの比較回数が黄金比を底とする対数で抑えられることは、Wikipedia 英語版の記述に基づく（原論文は読んでいない）
- abc312_h の方針で、調べた位置が戻らないことからの全体の計算量の上界は、kmjp・merom686 のどちらにも明記がなく、本文でも具体的な式は書いていない
- abc304_f の制約（N ≤ 10^5）は drken の記事に基づく。約数の個数の最大（10^5 以下で 128、10^6 以下で 240）は手元で数えて確かめた
- 図 shift.svg・border-chain.svg は描画して目で確かめる道具がなく、XML として読めることと座標の計算だけを確かめた。表示の確認を検証役に頼みたい
- 使用量の目安：道具の呼び出し約 45 回、Web 取得 10 回（検索 1 回を含む）

## 検証の指摘への対応（planning/batches/b1/verify/kmp.md）

- 直したもの：指摘 1（周期の倍数の条件を「$N - d$ 以下の周期だけ。$N$ 未満の約数はこれに含まれ、$N$ 自身は倍数とは限らない」に）、指摘 3（sections から comparison を外し、見出しを `## 使い分け {#comparison}` にして確認問題の後・参考の前へ移した。「ACL では」の囲みは手引き §4 の順に合わせて落とし穴の後・例題の前に置いた）、指摘 4（導入の π の説明）、指摘 5（無限ループ → 誤った値）、指摘 6（`while` は $N - 2$ 回・比較は $N - 1$ 回）、指摘 7（border-chain.svg のラベルを各段の枠の上へ移し、「aabaa の最長の border」などと入れ子を書き添えた。代替テキストも合わせた）、指摘 8（ABC135 F の文を分けた。練習・力試しの方針の各項目の末尾に「。」を付け、前の項目と 1 文につながって数えられるのも防いだ）、指摘 9（ACL の参考の行）、未解決の点の黄金比（「$\log_\varphi M$ 程度」に）
- 本文では直していないもの：指摘 2 の arc060_d の行（§13.7 により台帳から作られるので、下の提案で直す）
- 検査：check_pages（エラー 0・警告 0）、fix_problems --check（0）、check_snippets（4 片・期待と違う 0）、textlint（エラー 0・警告 23。残りは要点・図の代替テキスト・数式を含む文の長さと助詞の重なり）

### 台帳への提案（検証の指摘 2）

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| arc060_d | summary | 文字列を、より短い文字列の繰り返しで書けない文字列に分割するときの最小の個数と、その分け方の数を求める。 | https://drken1215.hatenablog.com/entry/2018/09/07/190100 （良い文字列は $y^k$（$k \ge 2$）で書けない文字列。「周期を持たない」はこのページの周期の定義では成り立たない） |
| arc060_d | approach | 各接頭辞・接尾辞が、より短い文字列の繰り返しで書けるかを判定する | 同上 |

台帳を直したら fix_problems で kmp の力試しの行を作り直してほしい（catalog の summary も同じ文言なら、凍結中なので執筆の指示として読むときの注意に留める）。
