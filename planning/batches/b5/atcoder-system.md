# atcoder-system の報告（b5）

- 書いたファイル：docs/start/atcoder-system.md、docs/img/atcoder-system/difficulty-by-position.svg・levels.svg（生成スクリプトは一時置き場の w-atcoder-system/gen.py。データは .cache の AtCoder Problems の JSON、abc400〜480）
- front matter で変えたもの：stage（draft）・updated（2026-10-22）。complexity は guide なので null のまま。sections は変えていない
- 検査：check_pages エラー0・警告0、fix_problems --check 直す行0、textlint エラー0・警告3（図の代替テキスト2つと参考の1行の文の長さ。§14-25 の誤検出の扱い）。コード片なし。SVG は render_svg で 360・720 の幅を目で確かめた
- 問題：catalog の problems が空なので載せていない（guide）

## 使った出典

- github.com（kenkoooo/AtCoderProblems の time-estimator/function.py）：difficulty の式・対象・400 以下の扱い
- qiita.com：anqooqie（レートの計算式、2019 更新）、drken（tips）、nabata（色別の割合、2024-08）、ToastUz（生成 AI のルールの版）、sirsoldano（調査 00 の記述を引用）
- ja.wikipedia.org（check_noai で noai なしを再確認）：ABC の形式・配点・ペナルティ、AGC・AHC
- chokudai.hatenablog.com（調査 00 の記述から。今回は開いていない）。chokudai.hatenablog.com は付録 B の「はてなブログ」の列に見当たらない（chokudai.github.io はある）。調査 00 で使われているので、確認済みか確かめて付録 B に足すことを提案する
- 数値（形式の変遷・位置ごとの四分位・ARC の区分・AGC の Rated の範囲・ABC の曜日）は .cache の AtCoder Problems のデータで手元で数え直し、調査 00 §2.3 の値と一致した

## 台帳への提案

- なし（問題を使っていない）

## 用語集への提案

- 「ARC の区分」の語の追加：ARC-- ｜ arc-divisions ｜ 2026 年の ARC の 3 つの区分（ARC--：Rated 800〜2399、ARC：1200〜2799、ARC++：1600〜2999）。2025 年までは Div. 1・Div. 2 だった。定義の持ち主は atcoder-system#contests
- 既存の glossary#color・#difficulty・#rating の項目に「詳しくは atcoder-system#colors・#difficulty・#rating」の節へのリンクを足す（今はページへのリンク）。glossary#atcoder の前置きのリンクも節へ張り替えられる
- 「パフォーマンスの上限」（performance-cap ｜ 1 回のパフォーマンスの上限。Rated の対象の上限＋401 で、今の ABC では 2400）を足すかは任意

## 手引きへの提案

- 付録 A に「Rated」「パフォーマンス」「レーティング（レート）」「色」「ARC--・ARC++」を全体の語として足すか検討（本文での表記：ARC の区分は ARC--・ARC・ARC++、2025 年までの区分は「Div. 1」「Div. 2」と空白入りで書いた。調査 00 には「Div.2」もあるので揺れを決めたい）
- 他ページから AtCoder の仕組みへのリンクが、いまはページへのリンク（stub だったため）になっている：contest-strategy（要点・#ai-rules の末尾・#difficulty-by-position の「difficulty の帯」→ #levels が適切）、problem-sets#practice-contests の末尾（→ #contests）、glossary#atcoder の前置き。メインが節へ張り替える

## 問題の補充の候補

- なし（guide のページで問題を載せない）

## 未解決の点

- レートの計算式は第三者の解説（2019 年の更新）によるもので、公式の資料（atcoder.jp のサブドメイン）は開いていない。その後の変更の有無は未確認。検索結果に、初参加者の内部レートの暫定値を 800 から 1200 に変えたという公式のお知らせ（atcoder.jp/posts/1592）が出たが、開いていないので本文に書いていない。パフォーマンスの計算に効く変更なので、ユーザーに確かめてもらうか、第三者の資料を探すとよい
- 誤答に数えない提出（コンパイルエラーなど）の細則は未確認のまま（本文で「確かめていない」と書いた）
- 生成 AI のルール 20261014 版の中身は decisions.md の記録に従った。20261014 版で AHC がどう扱われるかは確かめていない（本文で「確かめていない」と書いた）。AtCoder Problems のデータに「AHC GenAI Rules Trial Contest 2026」（2026-10-15）があり、AHC 向けのルールの試行があるらしい
- how-to-use が stub なので #ai-rule-version へはページへのリンクにした（draft になったら張り替え）
- ARC の区分ごとの難しさ（difficulty の分布）は回数が少ないので数えていない
- 色の割合の比較で、ガイドラインの上位 15%・7%・3% と nabata 氏の 7.84%・3.69%・1.46% の違いを「集計の対象と時期の違い」と推測で書いた（「考えられる」と明記）

## 使用量の目安

- 道具の呼び出し 約35回、Web 取得 7回（検索 2回を含む）

## 検証の指摘への対応（b5 verify）

- 直すべき 1〜3、直すとよい 4〜9 はすべて直した。
  - 2：E869120 氏の資料は確かめられないので、名と「2020 年」を消し「chokudai 氏の記事（2019 年）」とした。
  - 5：「〜ためと考えられる（解説の筆者の推測で、公式の説明は確かめていない）」とした。
  - 8：how-to-use.md#ai-rule-version に張り替えた。
- 採らなかったもの：なし。
- textlint の警告（文の長さ）が 3 件残る（エラーは 0）。2 件は図の代替テキストで元から、1 件は参考の function.py の行で URL の長さによる。

### 直しに伴う提案（共有ファイル）

- 上の用語集への提案「ARC の区分」の定義の「2025 年までは Div. 1・Div. 2 だった」は「2026 年 1 月までは Div. 1・Div. 2 だった（3 つの区分は 2026-02 から）」に直す。
- 付録 B に chokudai.hatenablog.com を足す（検証役が check_noai で指定なしを確かめた）。
