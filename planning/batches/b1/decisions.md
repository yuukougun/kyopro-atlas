# b1 の振り返りで決めたこと（2026-10-21、メイン）

b1（基礎・水 173ページ）の執筆者・検証役の提案（`planning/batches/b1/*.md` を集めたもの）への判断。手引き（style-guide.md）・道具・ページへの反映はこの表に従う。記号は提案のまとめの項目。

## 手引き（style-guide.md に §14 として足す。§13 と食い違えば §14 を優先）

| 項目 | 決定 |
| --- | --- |
| A1 落とし穴 | 定型の `## 落とし穴 {#pitfalls}` にそろえ、sections から外す（骨格のページも） |
| A2 使い分け | 定型の `## 使い分け {#comparison}` にそろえる。sections の `choosing`・`comparison` は外す（見本の lazy-segment-tree も）。ほかのページから `#choosing` へのリンクは `#comparison` に張り替える |
| A3 上位の手法へのつながり | 定型に足す：`## 上位の手法へのつながり {#next-steps}`（主に基礎のページ。sections に載せない。見本の binary-search-answer も外す） |
| A4 ACL | 見出しは立てず、関係する節の中に `!!! info "ACL では"` の囲みで置く。`acl: []` のページでは省く |
| A5 水の目安の節 | 「必要になる場面・処理の流れ・計算量」は sections の中身の節で兼ねてよい。独立の見出しは要らない |
| A6 構成の決め方 | 分野ではなく front matter の level と type で決める |
| A7 応用の型 | 各節の末尾に置く。独立の節にするのは sections にあるときだけ |
| A8 ds の3小見出し | データ構造そのもののページだけ。使い方・応用のページでは要らない |
| A9 thinking | 合図 → 最小の例 → 例題 → 関連する手法 を目安にし、関連は節の末尾のリンクで済ませてよい。例題の折りたたみの題は「方針」も可。ほかのページの例題の小見出し（`../<field>/<id>.md#<問題ID>`）へリンクしてよい |
| A10 cpp | 一言 → 素朴に書くと → 版 → 落とし穴 を目安とし、型の説明のページなど合わない節は省いてよい |
| A11 確認問題 | `## 確認問題 {#quiz}` にまとめる。答えは `??? success` の入れ子で可。sections の並びは本文の順に入れ替えてよい。骨格に残った catalog の書き出しは消す |
| B1 見出しの記号 | 見出しと sections の title に `<` `>` `[` `]` とバッククォートを書かない（言葉で言い換える）。見出しは60字以内を目安とし、長い title は anchor を変えずに短くしてよい（見出しと title を同時に） |
| B2 YAML | title にカンマ・角括弧・コロンを含むときは引用符で囲む |
| B3 cpp_std・gcc_min | ページの中心の機能が使える最も古い版 |
| C1 台帳の表記 | textlint のエラーになる表記の違いだけは本文の行を先に直してよい（台帳の直しも提案する）。事実の誤りも本文を直し、提案に書く |
| C2 要約が（執筆時に確かめる） | `- <ID>：自分の要約` と書けば fix_problems が label を埋める |
| C3 evidence | 読んだ記事がその問題のものかを最初に確かめる。画像だけの解説（典型90 の jpg）は、同じリポジトリの解答コードで確かめてよい |
| D1・D2 fix_problems | 執筆者は `--page <id>` だけを使い、`--field` を付けない。検査は `--check --page <id>`（道具を直す） |
| D3 実行時の異常終了 | check_snippets に `expect: crash`（0 以外の終了かシグナル）を足す。未定義動作の観測値を期待にした片は、版で変わったら「観測値の変化」として直す |
| D4 図の目視 | `tools/render_svg.py`（ヘッドレスの Chrome で PNG にする）を用意し、執筆者も検証役も使う |
| D5 動く図の置き場 | div の config は執筆者が仮に決めてよい。仕様は報告に書き、JS を作るときに config と前後の文章を直してよい |
| E2 表記 | 付録 A に：最短路（最短経路は使わない）・狭義の弱順序・安定ソート・ウォーク（歩道は使わない）・クラスカル法・プリム法・上位 bit・巡回シフト・border・周期・Z 配列。prh に入れられるものは入れる（lint のエラー0を保つ） |
| E3 リンク | stub のページへは anchor を付けずにページへ（相手が draft になったらメインが節へ張り替える。控えは handoff.md）。用語・手法へのリンクは同じ節では最初の1回。本文から練習の問題を指すときは label の一部と `#practice` へのリンク |
| E4 出典 | cppreference は転送のない形の URL にそろえる。ブログの題名は記事の h1 |
| F コード片 | 提案のうち事実の注意（ranges の射影の誤警告、`sync_with_stdio(false)` と printf を混ぜない、再帰ラムダの `-> void`、非再帰 DFS の形、`using mint = atcoder::modint;` も可、ACL のヘッダ名、複数の範囲の取り込み、折りたたみの中の取り込み）を §9 に足す |
| G 分野 | 提案の各項目を §5 の該当の分野に1行ずつ足す |
| H textlint | 折りたたみの中の箇条書き・図の代替テキスト・リンクの題名の誤検出は警告なら残してよい。箇条書きは句点を付ける |
| 付録 B | 報告で確かめたとあるドメインを足す（dev.to・kcpc／miscalc／pyteyon の hatenablog・scrapbox.io・chokudai.github.io・developer.apple.com・en.wikipedia.org・luogu）。足す前に noai の指定がないことを確かめ直す |

## 工程の手順（メイン）

- 執筆の指示は、ページの front matter（field・id・level・type）から機械的に作る。手で打たない
- 見本は2枚を別のファイルで渡す
- 記法（E1）は start/notation（横断のページ）を書くときにまとめる。提案は handoff.md に残す

## ページの front matter（other.md §1.5）

- 表記の直し（signs・summary・aliases・sections の title）と、内容の直し（tree-basics・tree-dp・invariant・segmented-sieve・harmonic-sum・knapsack-01・string-basics・geometric-series-mod・contribution・small-graph-brute-force の summary・signs）は反映する。内容の直しは根拠を確かめてから
- related・prerequisites の追加は反映する（双方向にする必要はない）
- frequency_evidence は、根拠の問題がそのページと関係しないものを外す（frequency の値は変えない。工程10で見直す）
- level・節の帯（spf-sieve の線形篩）は据え置き
- 内容の重なり（other.md §1.6）は、後から書く側が先に書かれたページへリンクして短くする

## 動く図

- 置き場の div があって JS のないもの（18個）は、動く図のバッチで作る（JS と tests/viz の単体試験。作る担当と検証役を分ける）。それまでは div を残す（viz.js が読み込みの失敗を表示するかを確かめ、出ないなら div を一時的に外す）
