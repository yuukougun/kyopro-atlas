# string-automaton-dp の報告（b2）

- 書いたファイル：docs/string/string-automaton-dp.md、snippets/string-automaton-dp/aho-dp.{cpp,yaml}・matrix.{cpp,yaml}、docs/img/string-automaton-dp/kmp-abab.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages（エラー 0・警告 0）、fix_problems --check（直すべき行 0）、check_snippets（2 件とも一致）、textlint（エラー 0・警告 10。数式を含む文の長さ・要点の囲みと折りたたみの中の文の長さ・数式の中の角括弧の対の誤検出）。SVG は render_svg.py で 360px・720px を目で確かめた
- 動く図：作っていない（visual は static・priority 2 なので SVG にした）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠の URL |
| --- | --- | --- | --- |
| abc458_f | evidence | https://gdst.dev/posts/abc458_f/ を足す（ikatakos.com がメンテナンス中で読めなかったため、こちらで制約と方針を確かめた） | https://gdst.dev/posts/abc458_f/ |
| abc419_f | evidence | https://kcpc.hatenablog.com/entry/ABC419 を足す（状態と bit の方針のみ。制約の L の上限は確かめられていない） | https://kcpc.hatenablog.com/entry/ABC419 |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 照合オートマトン | matching-automaton | パターンとの照合の途中経過（いまの接尾辞のうちパターンの接頭辞になっている最長のもの）を状態とし、状態と次の 1 文字から次の状態を引く表。1 パターンなら KMP 法、複数なら Aho-Corasick 法で作る。 |
| 吸収状態 | absorbing-state | 一度入るとどの遷移でも出ない状態。「少なくとも 1 回含んだ」を表すのに使う。 |

本文では「照合オートマトン」を kmp#automaton へのリンクで済ませたので、用語集に足さなくても本文は成り立つ。

## 手引きへの提案

- §5 string に「照合の状態の DP では、終端の印を失敗リンク先から受け継ぐ（out[v] |= out[fail[v]]）ことを必ず書く。持ち主は string-automaton-dp（multiple-patterns）と aho-corasick（inherit-terminal）で、片方はリンクで済ませる」を足す案。matrix-power の dp-transition の節にも同じ注意があるので、持ち主をメインが決めてほしい

## 問題の補充の候補

確認済みの例題 2・練習 2 で目安は満たしている。力試しは 0。ap.py で新しい候補は探していない（ikatakos.com がメンテナンス中で、第三者の解説で裏付けを取れる候補を見つけられなかった）。

## ほかのページへの申し送り

- aho-corasick（stub）：本文の multiple-patterns 節で Aho-Corasick の build（Trie・BFS 順の失敗リンク・遷移の写し・out の受け継ぎ）を snippets/string-automaton-dp/aho-dp.cpp:build に置いた。aho-corasick を書く人は、この snippet を流用するか、自分のページの snippet に移して本文からリンクし直してよい。aho-corasick が draft になったら、本文の aho-corasick へのリンク（multiple-patterns 節）を #build・#inherit-terminal に張り替える
- subsequence-dp（stub）：使い分けの表からページへリンクしている
- handoff の §1 で本ページを指している 6 行（digit-dp:219・dp-state-design:136・dp-state-design:317・matrix-power:159・matrix-power:316・kmp:210）の張り替え先：digit-dp:219 → #matching-state（応用の型に桁 DP との組が書いてある）、dp-state-design:136・317 → #kmp-automaton、matrix-power:159 → #multiple-patterns、matrix-power:316 → #multiple-patterns、kmp:210 → #kmp-automaton（L が巨大なら #matrix-power）

## 未解決の点

- abc419_f の制約（作る長さ L の上限・各パターンの長さの上限）を第三者の解説で確かめられなかった（evidence の ikatakos.com がメンテナンス中で HTTP 503）。本文ではパターン 8 個以下だけを書き、Trie の頂点数は「100 に届かない程度」と書いた（KCPC の記事の「80 程度」による）。ikatakos.com が戻ったら検証役に確かめてほしい
- research の「abc458_f の解説が包除が破綻する理由を説明している」は確かめられなかった（同じ理由）。why-not-inclusion-exclusion の節は、位置の包除が周期の構造に依存することを自分の例で示し、パターンの集合についての包除は正しく使えることを書いた。この節の題は「破綻する理由」のままだが、内容は「位置の包除は破綻し、パターンの包除は使える」になっている。題を「包除はどこで破綻するか（位置の重なりとパターンの集合）」のように変える案もある
- catalog の sections にあった comparison（部分列 DP・桁 DP との違い）は、手引き §14-2 に従って定型の「使い分け」で書いた（骨格の sections にもすでにない）

## 使った出典

- https://gdst.dev/posts/abc458_f/（abc458_f の制約と方針。新しいドメイン gdst.dev を check_noai で確かめた：noai・noimageai の指定なし。規約や AI 利用を断る表示もなし）
- https://kcpc.hatenablog.com/entry/ABC419（abc419_f の状態。付録 B にある）
- https://drken1215.hatenablog.com/entry/2019/04/23/120400（abc122_d）
- https://merom686.hatenablog.com/entry/2023/06/11/005610（abc305_g）
- 読んだが使わなかったもの：qiita.com/chiaoi（F の詳細なし）、www.variabits.com（F の記述なし。check_noai で指定なし）、kotatsugame.hatenablog.com（別の問題の記録。check_noai で指定なし）

## 使用量の目安

- 道具の呼び出し 約 45 回、Web 取得 8 回（うち 503 が 3 回）、検索 6 回

## 検証の指摘への対応（b2 verify）

- 1（直すべき）：sections の matching-state の title を見出しと同じ「照合の状態とマルコフ性」に直した
- 2：落とし穴「パターンが空や文字の範囲外」に、空のパターンでは答えが 0 になり、根の印を DP が見ないので先に場合分けする旨を足した
- 3：#matrix-power の最後の段落で、「次の節」を #why-not-inclusion-exclusion へのリンクにし、計算量 O(2^K S^3 log N)（K = 8・S = 81・N = 10^9 で約 4×10^9）と「S と K が小さいときに限る」を足した
- 4：title と見出しを「包除はどこで破綻するか（位置の重なりとパターンの集合）」に変えた（anchor は同じ）
- 5：Aho-Corasick 法へのリンクを aho-corasick.md#build に、out の受け継ぎに aho-corasick.md#inherit-terminal へのリンクを足した。記号は本ページの fail[v]・頂点のままにし、「Aho-Corasick 法のページの link(v) と同じもので、そのページでは頂点を節点と呼ぶ」と断った。どちらかにそろえるかはメインが決めてほしい（提案）
- 6：図の円の中のラベルを 12px → 14px に、表の上に「j = 0 1 2 3 和」の見出し行と区切り線を足し、和の列を縦線で分けた。例の文は 2 行に分けて 16px にした。render_svg.py の 360px・720px で目視した（360px では円の中のラベルはなお小さめだが読める）
- 7：A[u][v] の式の前に「状態 v から 1 文字で u に移る文字の数（u か v が禁止された状態なら 0）」と文で言い、# が集合の要素の数であることを添えた
- 採らなかったもの：なし

## 提案（検証の後）

- 台帳：abc458_f の evidence に https://gdst.dev/posts/abc458_f/、abc419_f の evidence に https://kcpc.hatenablog.com/entry/ABC419 を足し、abc419_f の checked を 2026-10-21 にする（検証役も同意）
- 記号：失敗リンクを本ページは fail[v]・頂点、aho-corasick は link(v)・節点と書いている。サイト全体でそろえるなら用語集か手引きで決めてほしい
