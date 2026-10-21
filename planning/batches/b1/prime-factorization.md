# prime-factorization の報告と提案（工程8b・b1）

- 書いたファイル：docs/math/prime-factorization.md、snippets/prime-factorization/{factorize,legendre}.{cpp,yaml}、docs/img/prime-factorization/trial-division.svg
- front matter で変えたもの：complexity（1 個の素因数分解 O(√N)、ルジャンドルの公式 O(log N)）・stage（draft）。updated は 2026-10-21 のまま。sections は変えていない
- 検査の結果：check_pages エラー 0・警告 0。check_snippets 2 片とも一致。textlint エラー 0・警告 6（要点の囲みの summary・signs 由来の文の長さと助詞、ルジャンドルの式の別行数式、台帳の summary の行、参考の記事題名の読点。どれも誤検出か台帳・骨格由来）。fix_problems --check は本ページに指摘なし（math/divisor-enum.md:181 の diverta2019_d の label で終了コード 1。担当外なので触れていない）
- 使った出典：drken のはてなブログ 7 記事（例題・練習・力試しの全問の evidence）。新しいドメインはない
- 図：catalog の visual は static・priority 2 なので、静的な SVG（360 を割れるだけ割り、i = 4 で 16 > 5 となって止め、残り 5 を素数として加える流れ）にした。描画ツールが手元にないため、見た目は SVG のソースでしか確かめていない（検証で表示を確かめてほしい）

## 台帳への提案

- abc169_d｜summary｜「同じ z は1回だけ」→「同じ z は 1 回だけ」（半角と全角の間の空白。本文の行は直した）｜表記の規則
- abc142_d｜summary｜「どの2つも」→「どの 2 つも」（同上。本文の行は直した）｜表記の規則
- abc110_d｜summary｜「積が M になる長さ N の正の整数列の個数を 10^9+7 で割った余りで求める。」（catalog の summary と同じにし、法を明記）｜https://drken1215.hatenablog.com/entry/2018/09/23/224100 。本文は今の台帳の summary のままにした
- arc067_a｜approach｜catalog は「1..N を素因数分解して指数を足す」、evidence の drken の記事はルジャンドルの公式で解いている。本文の方針は両方を書いた。approach を「N 以下の素数ごとに v_p(N!) を求め Π(e + 1)（1..N を分解して指数を足してもよい）」にするとよい
- 7 問とも summary・approach は evidence の解説と食い違わないことを確かめた（checked を付けるならメインの判断で）

## 用語集への提案

- なし（v_p(N) の記法はページ内で定義した。用語集に入れるなら：p 進付値｜p-adic-valuation｜整数 N を割り切る素数 p の最大の指数 v_p(N)。v_p(ab) = v_p(a) + v_p(b) が成り立つ）

## 手引きへの提案

- §13.7 の補足：fix_problems は要約（「：」の後ろ）を作り直さないので、台帳の summary が表記の規則（半角と全角の間の空白）に合わず textlint のエラーになる行は、本文側で空白を足してエラーを 0 にし、台帳の直しを提案する、と明記するとよい（今回そうした）

## 問題の補充の候補

- typical90_bw（典型90 075. Magic For Balls（★3））：N を素因数分解し、素因数の個数（重複込み）k から操作回数 ⌈log2 k⌉ を求める。練習の候補（abc319 以降ではないが、素因数の個数そのものを使う型の代表）。裏付け：https://github.com/E869120/kyopro_educational_90/blob/main/sol/075.cpp （調査 06-math-nt §5.3 で確認済みとされる。今回は再確認していない）
- abc319 以降の問題は見つけていない（ap.py での探索はしていない）。素因数分解そのものが本体になる新しい ABC は少なく、spf-sieve・prime-exponent-vector 側に回る傾向がある

## 未解決の点

- ルジャンドルの公式の計算量を front matter では O(log N)、本文では O(log_p N) と書いた（front matter は KaTeX 不可のため底を省いた）
- 「値が 10^6 以下の数を 2×10^5 個試し割りすると最悪 2×10^8 回」「最小素因数の篩なら 1 個あたり高々 20 回ほど」は log2(10^6) ≈ 20 からの見積もり
- snippets の期待値（10^18 の v_2・v_5、999999999999 の分解など）は Python で計算して確かめた

## 検証の指摘への対応（2026-10-21）

- 1（直すべき）：factorize.cpp のコメントを「残りが 1 より大きければ素数 1 個（指数 1）」に直した
- 2（直すべき）：§pitfalls の sqrt の誤った説明を消し、整数のまま `i * i <= n` で書くことと約数列挙の落とし穴へのリンクの 1〜2 文にした。整数のオーバーフローのリンクは int のあふれの文へ移した
- 3：種類数の上界に「1 以外は」「1 を含めれば + 1」を加えた
- 4：abc169_d の解法の詳細の「吸収」の行を、指数が余っても操作の条件に反しない旨に書き換えた
- 5：表の該当セルを「値の上限 $A$ までの前計算のあと 1 個 $O(\log A)$」にした
- 6：図の「÷5」の点線の矢印と「1」の箱を消し、5 の箱の下に「残り（素数）」と添えた
- 7：`i = …` のラベルを 14px にし、右端の箱を消した分 viewBox を幅 660 に詰めた（2 段に折るのは見送り。縮小率が 0.47 → 約 0.54 に改善する程度で、横長の図の扱いはメインの判断に任せる）
