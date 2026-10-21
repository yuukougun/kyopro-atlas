# subsequence-dp（部分列 DP）の報告と提案

- 書いたファイル：docs/dp/subsequence-dp.md、snippets/subsequence-dp/{count,nonadjacent,shortest,kth}.{cpp,yaml}、docs/img/subsequence-dp/leftmost-dag.svg
- front matter で変えたもの：complexity・stage（draft）・updated。sections の positions-or-strings の title を「位置の組を数えるか、異なる文字列を数えるか」に短くした（anchor は同じ）
- 検査の結果：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 4 本とも期待どおり、textlint エラー 0（警告 19。数式を含む文の長さ・図の代替テキスト・`$a[0, i)$` の括弧の対応・数式の中の「に」の重なりなどの誤検出）
- 図：leftmost-dag.svg を render_svg.py で PNG にして目で確かめた（catalog の visual は priority 2 の static。S = aba の状態と nxt の辺を描き、ab の最も左の道を太線にした）
- コード片はどれも、小さな乱択の入力で全列挙と比べる assert を main に持つ。TT の DP（abc299_f）と累積和への言い換え（abc230_f）は、一時置き場で全列挙と照合して確かめた（ページには取り込んでいない）
- 使った出典：drken の Qiita「部分列 DP」（考え方・ARC081 E・TDPC G）、merom686「ABC214」（abc214_f）、drken の ARC081 E と TDPC G の記事、かんプリン「典型問題メモ」（型への分類）。問いの細部（abc214_f の 1 文字以上・法 10^9+7、abc230_f の A_i の範囲と法、abc299_f の |S| ≤ 100）は www.luogu.com.cn の問題の訳で確かめた（付録 B にある。ページの参考には入れていない）。新しく noai を確かめたドメインはない

## 台帳への提案

| 問題 ID | 項目 | 新しい値 | 根拠 |
| --- | --- | --- | --- |
| abc214_f | summary | 文字列から、隣り合う位置を選ばずに 1 文字以上取り出してできる文字列の種類数を求める。 | 空文字列を数えないことが答えに効く（本文はこの形で書いた。fix_problems が台帳の値に戻すなら、台帳を先に直す）。https://www.luogu.com.cn/problem/AT_abc214_f |
| tdpc_lexicographical | evidence に追加 | https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd | 今の evidence（drken1215 の記事）は Qiita へのリンクだけで、DP の中身は Qiita にある |
| arc081_c | evidence に追加 | https://qiita.com/drken/items/a207e5ae3ea2cf17f4bd | 同じ記事に DP と復元がある |
| abc230_f | evidence | 第三者の詳しい解説を見つけられなかった（kanpurin の記事は分類だけ）。下の「未解決の点」を参照 | — |
| abc299_f | evidence | 同上 | — |

## 用語集への提案

なし（state・representative・bijection・sentinel・overflow の既存の anchor だけを使った）

## 手引きへの提案

- §5 dp に「異なる部分列（種類）を数える DP では、空文字列を含めるかを入力 1 文字の場合で確かめる」を足すとよい。配る DP の dp[0] = 1 が空文字列で、問題によって引く・引かないが分かれる（abc214_f は引く、abc230_f の言い換えでは引かない）

## ほかのページへの申し送り（メインが張り替える）

- subsequence-matching:165（使い分け）「部分列として何通り取り出せるか・異なる部分列の数 → 部分列 DP」：「何通り取り出せるか」（位置の組）は dp-phase#matched-prefix の範囲。異なる部分列の数は subsequence-dp#next-table-dp へ
- lcs:321「異なる部分列の種類数や、ある文字列を部分列に含むかの判定は部分列 DP」：判定は subsequence-matching の範囲。種類数だけを subsequence-dp#next-table-dp へ
- string-automaton-dp:305 の表「決まった文字列を部分列として含む・その個数 → 部分列 DP」：個数（位置の組）は dp-phase#matched-prefix、含む文字列の数は counting-dedup#leftmost。部分列 DP は異なる部分列の種類のとき
- dp-reconstruction:191 → #kth-subsequence、dp-reconstruction:270（ARC081 E の方針）→ #shortest-non-subsequence、lcs:166（異なる共通部分列の種類）→ #positions-or-strings か #leftmost、dp-phase:235 → #positions-or-strings、counting-dedup:104・130 → #leftmost
- dynamic-dp（stub）：本文の使い分けで「末尾の文字が c である異なる部分列の数を文字ごとに持つと、文字を 1 つ読む遷移が (σ + 1) 次の行列（文字 c で g_c ← Σg + 1）になるので、セグメント木に載せる。貰う形の f[l] は遠い位置を参照するのでそのままでは行列にならない」と書き、ページへリンクした（検証の指摘 2 で直した）。abc246_h（研究資料で dynamic-dp の例題）を書くときに #next-table-dp を参照できる

## 問題の補充の候補

- 確かめた範囲では新しい候補を見つけられなかった。frequency_evidence が recent 0 なので、abc319 以降で「異なる部分列の個数」を問う問題を探す価値がある（ap.py で題名から候補を探したが、題名だけでは判断できず、第三者の解説で裏付けたものはない）

## 未解決の点

- abc230_f・abc299_f は、台帳の evidence（かんプリンの分類記事）に解法の説明がない。第三者の詳しい解説を探したが、検索で見つかるのは atcoder.jp の解説と codeforces だけで、kmjp の記事は見つけられなかった（kmjp の検索が 429 を返した）。本文の方針（abc230_f の累積和の部分列への言い換え、abc299_f の 2 つ目の T の先頭を固定して組を進める DP）は自分で導き、全列挙と照合して確かめた
- 例題 abc230_f の解法の詳細には、コード片 count.cpp:prev を本文の next-table-dp 節で取り込んだもので代えている（問題専用のコードは置いていない）
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 約 12 回（検索 7 回を含む）

## 検証の指摘への対応（b3 verify）

- 直したもの：1（隣を選ばない場合の p_1 = nxt[0][X_1] を明記）、2（使い分けの行列の説明を末尾の文字ごとの個数の (σ + 1) 次の行列に直し、上の申し送りも直した）、3（2f[i] − f[l] への橋の 1 文を足した）、5（図の viewBox を 640×400 → 540×372 に詰め、下の説明を 2 行に短くし、「位置 0」などを 14px に。360px の PNG で確かめた）、6（「K 番目のための cnt の DP」に）、7（箇条書きの末尾に句点。要点の計算量・前提の 2 行も合わせた）
- 4 は一部だけ採った：count.yaml の cases を `abb`・`bbbb`・`abcd`・`abab` に替えた（`aba`・`aaaaa`・`abcde` をやめた）。本文と図・表・確認問題の `aba` は残した。理由：`aba` は同じ文字が離れて現れる最小の例で、図・配る表・確認問題 1 がそろって依存しており、替えると 4 か所を作り直す割に、例の文字列そのものは定義と同じく標準的で文章の転載には当たらないため。メインが替えると判断するなら `abb` などで図・表・確認問題をそろえて直す

