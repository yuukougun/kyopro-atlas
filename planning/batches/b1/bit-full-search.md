# bit-full-search の報告と提案（工程8b・b1）

- 書いたファイル：docs/basics/bit-full-search.md、snippets/bit-full-search/{subsets,base3,permutations,precedence-ng}.{cpp,yaml}、docs/img/bit-full-search/{mask-table,next-permutation}.svg
- front matter で変えたもの：complexity・stage（draft）・updated（2026-10-21 のまま）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0／fix_problems --check 直すべき行 0／check_snippets 4 本とも期待どおり（precedence-ng は expect: warning で取り込まない）／textlint エラー 0・警告 10（助詞の重複のうち数式・コードを含む文の誤検出と、折りたたみの箇条書きが 1 文として数えられる文長・読点。§13.8 の範囲）
- 図：静的な SVG 2 枚（catalog の visual は static・priority 2 なので動く図は作っていない）。SVG を画像に描いて目で確かめる道具が手元になく、XML の妥当性と座標の計算だけを確かめた
- 使った出典：参考の節の 8 件（drken 5・hamayan 1・oraclesqlpuzzle 1・cpprefjp 1）。どれも付録 B のドメインで、新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc232_c | summary | 頂点数 N ≤ 8 の 2 つの単純無向グラフが、頂点の番号を付け替えて一致するか（同型か）を判定する。 | 末尾の「。」が抜けている。本文の行は台帳のままにした（§13.7） |
| abc197_c | pages | bit-full-search を practice で追加（xor の practice はそのまま） | 区切る／区切らない 2^(N−1) 通りの型の唯一の代表。https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc197-c.html（研究メモ 01-basics §5 の候補にもある）。台帳では確認済み・diff 809 |

## 用語集への提案

なし（popcount・番兵は既存。本文では用語集へのリンクを使っていない）。

## 手引きへの提案

- 落とし穴の「`1 << 31`」の書き方：C++20 から符号付きの左シフトで符号ビットに入るのは定義された動作になった（`1 << 31` は −2^31）。research の「int あふれ」は C++17 以前の言い方なので、ほかのページ（bit-operations・cpp-integer-overflow）でも「C++20 より前は未定義動作、今は負の値になる。シフト幅が 32 以上はどの版でも未定義動作」とそろえるとよい
- research の「`mask >> i & 1 == 1` の優先順位」は、実は `(mask >> i) & (1 == 1)` ＝ `(mask >> i) & 1` となって偶然正しく動く。本文では壊れる例として `== 0` と `mask & 1 << i == 1`（i ≥ 1 で常に偽）を使った。catalog の節の題名「== と & の優先順位」はそのままでよいが、他ページで同じ例を引くときに注意が要る

## 問題の補充の候補

| 問題 ID | 何を問うか | 裏付けの URL | 備考 |
| --- | --- | --- | --- |
| abc197_c | 数列を区間に区切り、各区間の OR の XOR を最小化する（区切り方 2^(N−1) 通り） | https://oraclesqlpuzzle.ninja-web.net/kyoupro/05-atcoder-02-abc/kyoupro-abc197-c.html | 台帳では確認済み（xor の practice）。practice への追加を推す |
| abc104_c | 各難易度の問題を「全部解く／解かない」で 2^D 通り決め、残りは 1 つの難易度だけを部分的に解く貪欲で、目標点に届く最小の問題数を求める | 第三者の解説は未取得（研究メモ 01-basics §4.B・§7.5 に型として記載） | ap.py で実在を確認（C. All Green、diff 1393）。台帳にない。片側を bit で決めて残りは貪欲の型で、abc159_e と並ぶ水の代表。裏付けの解説を取ってから台帳に足す |
| abc150_c | 2 つの順列が辞書順で何番目かを、全順列を列挙して求める | https://drken1215.hatenablog.com/entry/2020/01/12/122100 | 台帳では確認済み（permutation の practice）。順列全探索の練習として追加してよい |

## 未解決の点

- 練習の行 abc232_c の要約だけ末尾に「。」がない（台帳の修正後に fix_problems で直る）
- 本文の abc100_d の節で使った「最大化の順序の入れ替え」は直感的な説明だけで、証明は書いていない（基礎のページなので短くした）
- next_permutation の「全部回したときの平均はならし O(1)」は出典で確かめられなかったので、本文は「1 回の呼び出しは O(N)」だけにした
- 使用量の目安：道具の呼び出し約 30 回、Web 取得 6 回（WebFetch）＋題名の確認 8 件（curl）

## 検証の指摘への対応（2026-10-21）

- 指摘 1〜6：本文と図（next-permutation.svg の ④ を実線にし「2 3 5 は昇順（実線）」を添えた。代替テキストも合わせた）を直した
- 指摘 7（sections の pitfalls）：front matter の sections の方針はメインが決める事項なので、執筆者は変えなかった。提案：手引き §13.1 に合わせて sections から外し見出しを `## 落とし穴 {#pitfalls}` にするか、副題付きを例外として §13 に書く（bit-operations も同じ形）
- 指摘 8（abc232_c の「。」）：上の台帳への提案のとおり。本文は直していない（§13.7）
- 手引きへの提案のうち「`1 << 31` は C++20 より前は未定義動作」とそろえる案は誤りだったので取り下げる。そろえるなら「C++20 から規格で値が決まった。それより前も GCC では同じ値（C++14 以降は `1 << 31` も未定義動作ではない）。シフト幅が型の bit 数以上はどの版でも未定義動作」とする
- 台帳への追加の提案：abc182_c・abc128_c・abc159_e の `checked` に 2026-10-21（検証役が drken の解説で確認）
