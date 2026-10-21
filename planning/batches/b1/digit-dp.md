# digit-dp の報告（工程8b・バッチ b1）

- 書いたファイル：docs/dp/digit-dp.md、snippets/digit-dp/（3 組：digit-sum・leading-zero・digit-sum-divisible の .cpp と .yaml）。静的な図の SVG は作らず、表と動く図の置き場で代えた
- front matter で変えたもの：complexity・stage（draft）。updated は 2026-10-21 のまま（今日の日付と同じ）。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。fix_problems --check --page digit-dp 直すべき行 0（全体の --check では dp/tree-dp.md の 10 行が出るが、並行して執筆中のほかのページのもの）。check_snippets 3 組・期待と違う 0。textlint エラー 0、警告 1（2 進の節の「(0, 0)・(0, 1)・(1, 0)」の数式の中のカンマを max-comma が数える誤検出）
- 使った出典：参考の節の 8 件（drken 5 件・Series_205・comet725・torus711）。どれも付録 B のドメイン。新しく noai を確かめたドメインはない
- 使用量の目安：道具の呼び出し 約 40 回、Web 取得 10 回・Web 検索 2 回

## 台帳への提案

- abc465_e｜summary｜1 以上 N 以下（N は巨大な数字の列）の整数のうち、「数字がちょうど 3 種類」「数字 3 を含む」「3 の倍数」のちょうど 1 つだけを満たすものの個数を求める。｜https://qiita.com/comet725/items/0e337dca7c6eba510868 （最後の集計のコードで 3 条件のうち満たす数がちょうど 1 のものを足し、空の集合を除いている）・https://qiita.com/alpha0314alpha/items/bfb3aa4c581cf84aa2a8 （3 条件の中身）
- abc465_e｜evidence｜上の alpha0314alpha の記事を足す
- abc336_e｜evidence｜https://torus711.hatenablog.com/entry/2024/01/15/200630 を足す（今の evidence の kanpurin の記事は問題の一覧で、解き方の裏付けにならない）
- abc117_d・abc129_e・abc135_d｜pages の digit-dp 用の alternatives の summary を本文で使った（台帳の主の summary とは言い回しが違う）。どちらかにそろえるならメインの判断で

## 用語集への提案

- leading zero｜leading-zero｜整数を決まった桁数にそろえるとき、左に埋める 0。桁 DP では、数字の集合や 0 の個数を数える条件のときに、本物の 0 と区別する必要がある
- （任意）smaller フラグ｜smaller-flag｜桁 DP で、上から決めた桁がここまで上限 N と一致しているか、N より小さいことが確定したかを表す 2 値の状態。未満フラグ・tight フラグとも言う

## 手引きへの提案

- §13.1 では落とし穴は定型の節（sections に載せない）だが、このページは catalog の sections に「落とし穴：N 自身を含むか・0 を数えるか」（anchor pitfalls）を持つ。§13.2 に従い見出しを title と同じにした。ほかのページにも同じ形があるなら、どちらに寄せるかを決めてほしい
- 要点の「いつ使うか」の小項目と「解法の詳細」の箇条に句点を付けないと、textlint が前後の項目を 1 文と見て sentence-length を出す。見本（binary-search-answer）と同じく句点を付けるよう §2.2 か §2.4 に一言あるとよい

## 動く図の仕様（priority 1。JS は作っていない）

- 置き場：`<div class="kp-viz" data-viz="digit-dp-tight" data-config='{"digits": "253", "base": 10}'></div>`（tight-flag の節）
- 内容：N の桁を横に並べ、上から 1 桁ずつステップ送りする。各段で「一致の道」を 1 本の太線で伸ばし、そこから「N の桁より小さい数字を選んで未満になる枝」を、選べる数字の範囲と残りの自由な桁の個数（例：百の位で 0・1 → 2 × 100 通り）のラベル付きで分ける。最後のステップで N 自身（一致の道の終点）を示し、合計 2×100 + 5×10 + 3 + 1 = 254 が 0〜N の個数と一致することを caption に出す
- 図の前後の文章は本文に書いた（図の流れを箇条で追う形）。base: 2 を渡せば 2 進の節にも使える形にしておくとよい

## 問題の補充の候補（問題ID・何を問うか・裏付けの URL）

- tdpc_number（TDPC E. 数、diff なし）｜N 以下（N は最大 10^4 桁）の正の整数のうち、各桁の和が D の倍数になるものの個数。EDPC S と同じ型なので練習に足すなら 1 問として｜https://sigma425.hatenablog.com/entry/2016/08/02/214547 （research/02-dp §5.1 に候補として載っている。台帳には未登録。中身は今回は読んでいない）

## 未解決の点

- abc465_e の問いは、問題文を読めないので 2 つの第三者の記事（コードと解説）から組み立てた。「1 以上 N 以下」の下限は、comet725 氏のコードが空の集合（整数の 0）を集計から外していることからの判断で、N の桁数の上限（記事の感想では 500 桁程度）は確かめきれず要約に入れなかった
- digit-sum-divisible の計算時間（N = 10^14 で約 0.1 秒）は手元の g++ -O2 での実測で、計算量の式は粗い見積もり（O(L·(9L)^3) 程度）として書いた
- 本文の abc154_e の「答えは C(100, 3) × 9^3 程度まで」は K ≤ 3・桁数 ≤ 100 からの上からの見積もりで、drken 氏の記事にある制約（N の桁数 ≤ 100、1 ≤ K ≤ 3）に基づく
