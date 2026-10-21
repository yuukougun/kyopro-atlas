# aho-corasick の報告と提案（b2）

- 書いたファイル：docs/string/aho-corasick.md、snippets/aho-corasick/count.{cpp,yaml}・avoid-dp.{cpp,yaml}・taboo-greedy.{cpp,yaml}、docs/img/aho-corasick/failure-links.svg・fail-tree.svg
- front matter で変えたもの：complexity（`構築 O(σM)（M はパターンの長さの総和、σ は文字の種類数）、テキストの走査 O(N)、出現回数の集計 O(N + M)`）・stage（draft）・updated。sections は変えていない（catalog の comparison は §14-2 で骨格から外れており、定型の `## 使い分け {#comparison}` に置いた）
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check 直すべき行 0。check_snippets 3 本・19 case 一致（count は main で素朴な数え上げと assert、taboo-greedy は出現を区間にした串刺しの貪欲と assert、期待値は Python の全探索で作った）。textlint エラー 0、警告 26（要点の囲み・図の代替テキスト・数式を含む文の長さと読点、`s`・`b` を単独の文字として書いた箇所の ja-unnatural-alphabet、助詞の重複。§13-8・§14-25 で残してよいもの）
- 図：render_svg.py で 360px・720px を目で確かめた（Trie と失敗リンク、失敗リンクの木での集計）
- 使った出典：noshi91 のアルゴリズム事典（計算量の言い方）、プロひろ・kmjp（abc362_g の問い）、KCPC ブログ（abc419_f の状態）、anoconne の note（abc268_h の貪欲と印の受け継ぎ）。新しく noai を確かめたドメイン：noshi91.github.io（指定なし）。note.com の記事 anoconne/n/n26b5912e1e9c（meta に noai の指定なし）
- 動く図：catalog の visual は priority 1。指示どおり JS は作らず、`<div class="kp-viz" data-viz="aho-corasick" data-config='{"patterns": ["he", "she", "his", "hers"], "text": "ushers"}'>` を failure-links の節に置いた。静的な SVG を 2 枚添えた

## 動く図の仕様（JS を作るときに）

- 前半：Trie を描き、BFS 順に節点を 1 つずつ取り出す。取り出した節点の行を失敗リンク先から写す様子と、子の失敗リンク（破線）を張る様子を 1 ステップずつ見せる。caption 例「sh を取り出す。子 she の失敗リンクは nxt[link(sh) = h][e] = he」
- 後半：テキストを 1 文字ずつ読み、状態の移動（根 → s → sh → she → her → hers）を強調する。状態に着いたら失敗リンクの連鎖を薄く示し、終端の印が立つ節点（she・he、hers）を出現として表示する
- 本文の文章はこの 2 段の流れで書いてある（failure-links の節の div の前後）

## 台帳への提案

- abc362_g｜evidence｜https://programming-hiroba.com/abc362-g/ と https://kmjp.hatenablog.jp/entry/2024/07/14/0900 を足す｜ikatakos.com が 2026-10-21 にメンテナンス中（HTTP 503）で読めなかった。問いは 2 つの記事で確かめた（どちらも SA の解き方。Aho-Corasick の解き方は本文のコード片で確かめた）
- abc419_f｜evidence｜https://kcpc.hatenablog.com/entry/ABC419 を足す｜状態が「単語の接頭辞と、含んだ単語の集合の bit」であることを確かめた
- abc268_h｜approach｜「走査して一致したら終端を * にして状態を根に戻す貪欲（受け継いだ終端の印で判定。区間の串刺し）」に直し、「裏付けは検索結果の要約だけ…」の注記を外す｜note の記事本文と解答コードで、一致したら数えて根に戻すこと・印を失敗リンク先から受け継ぐことを確かめた。checked を 2026-10-21 に

## 用語集への提案

- 照合オートマトン｜matching-automaton｜パターンとの照合の状態（末尾のうちパターンの接頭辞になっている最長の部分）を頂点、文字を辺にした有限オートマトン。次の状態が次の 1 文字だけで決まるので、DP の状態や行列累乗に使える。1 パターンなら KMP 法、複数なら Aho-Corasick 法で作る（kmp・string-automaton-dp・matrix-power と共有の語。本文ではリンクしていない）
- 失敗リンクの木｜failure-tree｜Aho-Corasick 法の各節点から失敗リンクの先への辺を、子から親への辺とみた根付き木。ある節点の祖先は、その文字列の接尾辞で Trie にあるものすべてに当たる（足すならメインがリンクを張る）

## prh.yml への提案

- 「エイホ・コラシック」「エイホ–コラシック」「Aho–Corasick」（en dash）→「Aho-Corasick 法」（付録 A の正規形）

## 手引きへの提案

- §5 string に「Aho-Corasick 法・KMP 法のオートマトンを DP に使うときは、ならしの $O(1)$ が効かないので遷移表を埋める」と「終端の印は失敗リンク先から受け継ぐ」を足すとよい（string-automaton-dp・matrix-power でも同じ落とし穴を書いている）。持ち主はこのページの inherit-terminal を推す

## ほかのページのリンクの張り替え（handoff §1.3 の 7 か所）

aho-corasick が draft になったので、節へ張り替えられる。
- matrix-power:159（終端だけでなく fail の先も捨てる）→ `aho-corasick.md#inherit-terminal`
- kmp:217（Trie にまとめて π の代わりに失敗リンク）→ `aho-corasick.md#build`（または `#failure-links`）
- kmp:329（使い分けの表）→ ページへのままでよい
- rolling-hash:214（多数のパターンの出現）→ `aho-corasick.md#count-occurrences`
- suffix-array:261（ABC362 G は Aho-Corasick 法でも解ける）→ `aho-corasick.md#abc362_g`
- suffix-array:291（使い分けの表）→ ページへのままでよい
- trie:300（多数のパターンの出現を数える）→ `aho-corasick.md#count-occurrences`

## 問題の補充の候補

- 例題 1・練習 2・力試し 1 で目安（例題 1〜3・練習 2〜6）に収まるので、新しい候補は探していない
- 練習の 2 問はどちらも string-automaton-dp の例題なので、本文の練習の方針では DP の作り方を 1 行にとどめ、そちらへリンクした

## 未解決の点

- 例題 abc362_g の制約（$\lvert S \rvert$・$Q$・$\sum \lvert T_i \rvert$ の上限）は、読めた解説に書かれておらず確かめきれなかった。本文には上限の数値を書かず、計算量の式だけにした
- abc458_f の「状態は 100 程度」は matrix-power のページ（ikatakos の記録を出典にしたもの）の値に合わせた。今回は ikatakos.com がメンテナンス中で、自分では確かめていない
- 落とし穴の節の「$N = M = 5 \times 10^5$ なら約 $5 \times 10^8$ 回」は自作の見積もり（パターン a, aa, …, a^k）で、特定の問題の制約ではない
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 6 回（検索 3 回を含む）

## 検証の指摘への対応（b2 の直し）

- 指摘 1〜8 をすべて直した（採らなかったものはない）
    - 1：参考の題名を記事の h1「AtCoder Beginner Contest反省会 ~入緑編~」にし、「Ex - Taboo の節」を添えた
    - 2：fail-tree.svg の題と凡例の「本文」を「テキスト」にした
    - 3：両方の図で辺の文字・題を 18px、注記・凡例を 16px、節点の文字を 15px に上げた。fail-tree の凡例は 2 段にして viewBox の高さを 400 にした。render_svg.py の 360px・720px で、はみ出しや重なりがないことを確かめた
    - 4：集計の手順 2 を「根以外の節点を BFS の逆順に見て」にした
    - 5：「表は long long でなく int で持つ」とし、push_back の再確保で一時的に約 2 倍のメモリを使うので reserve する、を足した
    - 6：ABC458 F の方針を「禁止文字列は 10 個以下・各 10 文字以下なので状態は 101 個以下」にした
    - 7：count.cpp の core をメンバの宣言と build だけにした（構造体の中で build を先に置き、add_node・insert を範囲の外に出した）
    - 8：確認問題 2 を、パターン a・ab・b とテキスト abab で止まった回数と部分木の和を求める小問に替えた（答え：どれも 2）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 本一致、textlint エラー 0（警告 25）

## 台帳への提案（直しで追加）

- abc458_f｜evidence｜https://gdst.dev/posts/abc458_f/ を足す（検証役が制約 1 ≤ N ≤ 10^9、1 ≤ K ≤ 10、1 ≤ |S_i| ≤ 10 を確かめた。本文の「状態は 101 個以下」の根拠）
