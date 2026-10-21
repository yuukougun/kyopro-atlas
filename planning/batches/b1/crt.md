# crt（中国剰余定理）の執筆の報告

- 担当の指示は `docs/math/chinese-remainder.md`（水）だったが、骨格のページは `docs/math/crt.md`（id: crt、level: 青）だった。id と URL は変えない規則なので、`docs/math/crt.md`・`snippets/crt/`・`docs/img/crt/` に書いた。level は front matter の 青 のままにした
- 書いたファイル：docs/math/crt.md、snippets/crt/crt-merge.{cpp,yaml}、snippets/crt/sum-multiple.{cpp,yaml}、snippets/crt/garner.{cpp,yaml}、docs/img/crt/grid-3-5.svg、docs/img/crt/grid-4-6.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections に「応用の型（範囲を余りに直す・分けて戻す）」（anchor: applications、level はページと同じ）を足した
- 検査の結果：check_pages --page crt はエラー・警告とも 0。fix_problems --check は 0。check_snippets snippets/crt は 3 本とも一致。textlint はエラー 0、警告 23（数式を含む文の長さ、`$[0, m)$` の半開区間を括弧の対応の誤りとみなすもの、数式の中の助詞の重なりで、誤検出として残した）
- 図：visual は priority 2（static）なので、catalog の指定どおり mod 3 × mod 5 の格子の SVG を作り、対比として mod 4 × mod 6（解のないマスを点線と「なし」で示す）も足した。動く図は作っていない
- 使った出典：drken の Qiita（CRT のまとめ）、flkanjin.hatenablog.com、ACL の document_ja（手元の v1.6 と GitHub）、drken1215（acl1_b）、kazun-kyopro（abc286_f）、nullkara.jp（abc193_e）、ikatakos（abc371_g の解法の部分だけ）
- 新しく noai を確かめたドメイン：flkanjin.hatenablog.com・nullkara.jp（どちらも noai・noimageai の指定なし。2026-10-21、tools/check_noai.py）。kazun-kyopro.hatenablog.com・qiita.com も確かめ直して指定なし

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc193_e | summary | 電車が X 秒走って Y 秒停車するのを往復で繰り返し、乗客が P 秒眠り Q 秒起きるを繰り返すとき、起きている間に電車が目的の駅に停車している最初の時刻を求める。 | 今の summary の「X 秒停車・Y 秒移動」は逆（X が走行、Y が停車、周期は 2(X+Y)）。https://nullkara.jp/2021/02/28/atcoder_abc193/ 。本文の行は新しい値で書いた（fix_problems は要約を変えないので、台帳を直せば一致する） |
| abc286_f | summary | インタラクティブ。隠された整数 N（≤ 10^9）を、写像 f を 1 つ指定して f を N 回適用した結果を教えてもらう 1 回の質問から当てる。 | 「1つ」「1回」が半角数字と全角文字の間の空白の規則（textlint のエラー）に合わない。本文の行は空白を入れて書いた |
| abc371_g | pages | `{id: crt, role: challenge}` を足す | 置換の巡回ごとに操作回数を合同式で絞り、法が互いに素でない CRT で統合していく（abc319 以降で crt を使う問題）。https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0914_abc371 （解法の部分）。C++ では lcm が数百桁になるので、素因数の冪ごとに条件を持つ形になる（本文の many-equations の「素因数ごとに持つ」に対応） |

## 用語集への提案

| 語 | anchor | 定義 |
| --- | --- | --- |
| 互いに素 | coprime | 2 つの整数 $a, b$ の最大公約数が 1 であること。$a$ と $b$ が互いに素なら、$a$ は $\bmod b$ で逆元を持つ |

- 混合基数表示（Garner の節で 1 回だけ使う）は、本文の式で意味が分かるので用語集には入れなくてよいと考える

## 手引きへの提案

- 任務の指示（ページのパスと level）が骨格と食い違っていた（chinese-remainder／水 ↔ crt／青）。指示を作るときに catalog の id と level から作ると食い違いが起きない
- 1 つの snippet から 2 か所を取り込む（`:core` と `:fold`）書き方を使った。手引き §9 には `core` の例しかないので、名前を変えて複数の範囲を取り込めることを書いておくとよい

## 問題の補充の候補

- **abc371_g**（G. Lexicographically Smallest Permutation、diff 2348、台帳で確認済み）：置換を何回か適用した列の辞書順最小。巡回ごとに「操作回数 ≡ r (mod 巡回の長さ)」の条件を前から足し、法が互いに素でない CRT で統合する。裏付け：https://ikatakos.com/pot/programming_algorithm/contest_history/atcoder/2024/0914_abc371 。crt の力試しにすることを提案する（上の台帳への提案）
- abc319 以降で crt を例題・練習にできる水〜青の ABC は、drken の「中国剰余定理」カテゴリ（11 件。ABC は 103 C・186 E・193 は無し）と Web 検索では見つからなかった。abc186_e（Throne）は ext-gcd の例題なので crt には足さない

## 未解決の点

- 図の SVG は手元に描画の道具がなく、ブラウザで見た目を確かめていない（viewBox は 640 幅。グリッドは左寄せ）
- 「Garner のアルゴリズム」の節（黄）は、任意 mod の畳み込みの節（convolution-ntt）がまだ stub なので、ページへのリンクにとどめた。convolution-ntt が draft になったら `convolution-ntt#<anchor>` に直すとよい
- ext-gcd のページが同じバッチで執筆中で、2 式の統合の説明（一次合同式を gcd で割る）が重なりうる。crt では「2 式の統合」の形に絞り、一次合同式の一般論は ext-gcd へのリンクにした。検証のときに重なりの程度を見てほしい
- frequency は C（recent 0）のまま。abc371_g を足しても黄の力試しなので、frequency の根拠は変わらない

## 検証の指摘への対応（2026-10-21）

- 直したもの：1（落とし穴の「法で割った余りにする」を、大きい法を m0 に入れ替えて u1 で割る ACL の方法に直し、余りにするだけでは足りない理由を足した）、2（上限を超える統合の 1 回を `__int128` で行う旨を足した）、3（素数冪の式に分ける段と、残った式の使い道を書いた）、4（多数の式・応用の節の添字を 0 始まりにそろえた）、5（必要性と十分性の文に直した）、6（「互いに素とは限らない」に直した）、7（使い分けの 1 項目めを $x = r_0 + m_0 t$ の形の言い方に直した）、8（2 つの SVG の副題を 2〜3 行に分け、文字を 13px にし、viewBox の幅を 420・470 に詰めた）、9（grid-4-6.svg の行 1・列 2 を太枠にし、副題と代替テキストに足した）、10（「あふれない」にそろえた）、12（「取りうる値の個数以上（ABC286 F なら $10^9$ 以上）」に直した）
- 採らなかったもの：11（導入と図の例 3・5 の余り 2・3）。孫子算経以来の定番の数値で、検証役も転載ではないとしており、図の形・説明の筋は出典と違う。変えると図・代替テキスト・計算・snippet をそろえて動かすことになり、得るものが小さいので、そのままにした
- 検査：check_pages --page crt エラー・警告 0、fix_problems --check 0、check_snippets snippets/crt 期待と違う 0、textlint エラー 0（警告 25。前回と同じ種類の誤検出）
- SVG は今回も画像にして目では確かめていない（座標と文字数から幅を見積もった）
