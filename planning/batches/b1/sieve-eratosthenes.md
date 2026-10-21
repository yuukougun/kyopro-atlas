# sieve-eratosthenes（エラトステネスの篩）の報告と提案

- 書いたファイル：docs/math/sieve-eratosthenes.md、snippets/sieve-eratosthenes/sieve.{cpp,yaml}（core と prefix の 2 区間）、snippets/sieve-eratosthenes/omega.{cpp,yaml}、docs/img/sieve-eratosthenes/grid100.svg
- front matter で変えたもの：complexity（`O(N log log N)。区間の素数の個数は累積和を前計算 O(N)、1 回 O(1)`）・stage（draft）・updated。sections の title を 2 つ短くした：complexity を「計算量 O(N log log N) の根拠と、調和級数の O(N log N) との違い」に、memory を「メモリの見積もり（10^8 までは bit で持つ）」に（`vector<bool>` を見出しに入れると `<bool>` が HTML として読まれるおそれがあるため）。anchor は変えていない
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 0、check_snippets 期待と違う 0、textlint エラー 0・警告 2（189 行は台帳の summary の「x も (x + 1)/2 も」の助詞の重複、196 行は数式を含む練習の方針の文の長さの誤検出）
- 図：静的な SVG（1〜100 の表で、各合成数を最初に消した素数を右下に書き、素数を太枠にする。色に加えて数字のラベルで区別）。catalog の visual は priority 2 なので動く図は作らず、置き場の div も置いていない。作るなら仕様：同じ 10×10 の表で、p = 2, 3, 5, 7 の番ごとに p² から p 刻みで印を付けるステップ送り。各ステップの caption で「p² 未満の倍数はすでに消えている」と「11² = 121 > 100 なので止める」を示す
- 事実の確認：篩の内側の回数・Σ N/i・素数の個数・N = 10^8 の実行時間は手元で計測（g++-15 -O2。N = 10^6 で 2,122,048 回／13,970,034 回、10^7 で 22,850,051 回／162,725,364 回、10^8 で 242,570,204 回／1,857,511,568 回。π(10^6) = 78498、π(10^7) = 664579。2p から始めた場合は 10^7 で 23,492,028 回）。vector<bool> と vector<char> の 10^8 の篩は、同じ計測プログラムで前者が速かった（約 0.5 秒と約 1 秒。ただし両方に Σ N/i のループを含む計測）

## 注意（他のページへの意図しない変更）

- `python3 tools/fix_problems.py --page sieve-eratosthenes --field math` を実行したところ、`--field math` のため math 分野全体が対象になり、docs/math/prime-exponent-vector.md の問題の行 7 つ（`- abc342_d：…` などの ID だけの行）も label・URL・diff の形に直された。要約は変わっていない。戻そうとしたが権限で止められたので、そのままにしてある。メインで確認し、必要なら戻すか、そのまま受け入れてほしい（担当の執筆者がいずれ同じ処理をする内容である）

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc475_d | summary | 文字列 S の各文字を、同じ文字は同じ数字、異なる文字は異なる数字に置き換えて、先頭が 0 でない素数を作る。作れればその 1 つを、作れなければ -1 を出力する。 | https://qiita.com/hyouri/items/8aba1a9b9c6378fcf6f1 ・ https://qiita.com/Konini64/items/72cfce90cf1682c02498 ・ https://qiita.com/comet725/items/777d32f7cf7630a48663 |
| abc475_d | approach | S の長さ n について 10^n 未満を篩い、n 桁の素数ごとに文字と数字の対応が両方向に矛盾しないかを調べる（文字への数字の割り当てを全探索して篩で判定してもよい） | 同上 |
| abc475_d | evidence | 上の Konini64・hyouri の記事を追加 | 同上 |
| abc084_d | summary | （変更は任意）「x も (x + 1)/2 も素数」を「x と (x + 1)/2 がどちらも素数」にすると textlint の助詞の重複の警告が消える | — |

本文の abc475_d の行は上の summary で書いた。

## 用語集への提案

なし（用語集へのリンクは張っていない）。

## 手引きへの提案

- §10 の `fix_problems.py --page <id>` の例に、`--field` を付けると分野全体が対象になることを注意書きで足す（`--page` だけで足りるなら `--field` を外した例にする）。並列で書くとき、他の執筆者のページを書き換えてしまう
- 見出しに `<…>` を含む型名（`vector<bool>` など）を入れない、と §2.3 に書くとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

台帳の確認済みの問題で数は足りている（例題 1・練習 4）。力試しはない（基礎のページなので 0 でよいと判断した）。補充は提案しない。

## 未解決の点

- abc475_d：S の長さの上限 7 は Konini64 の記事の記述と、chokudai の観戦記の「異なる文字は高々 7 種類」から読んだが、問題文では確かめていない。答えが複数あるとき「どれでもよい」か「最小」かも確かめられなかったので、本文は「その 1 つ」と書いた
- abc084_d：l, r の上限は確かめた記事に書いておらず、本文は「x の上限までを篩う」とだけ書いた
- メルテンスの定理（素数の逆数の和 = log log N + O(1)）は ja.wikipedia の記事で確かめ、証明は書いていない
- 新しく noai を確かめたドメイン：chokudai.github.io（noai・noimageai の指定なし。観戦記を読んだが本文の出典には入れていない）。付録 B への追加を提案
- 使用量の目安：道具の呼び出し 約 35 回、Web 取得 10 回・検索 1 回
