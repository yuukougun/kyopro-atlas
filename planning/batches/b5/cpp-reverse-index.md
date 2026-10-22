# cpp-reverse-index の報告（b5）

- 書いたファイル：docs/cpp/cpp-reverse-index.md、snippets/cpp-reverse-index/{read-line,read-line-ng,required-from-here-ng}.{cpp,yaml}、docs/img/cpp-reverse-index/read-line.svg
- front matter で変えたもの：stage（draft）・updated（2026-10-22）。complexity は type guide なので null のまま（check_pages も technique・overview 以外は求めない）
- 検査：check_pages エラー 0・警告 0、fix_problems --check 直すべき行 0、check_snippets 3 個・期待と違う 0（g++-13・g++-15）、textlint エラー 0・警告 2（要点の 1 行目は summary の写しの「か」の重複、図の代替テキストの長さ。§14-25 の誤検出の扱い）
- 図：read-line.svg（幅 400）を render_svg で 360px・720px にして目で確かめた。catalog の visual（static・priority 1）の分解図そのもので、動く図ではない
- 使った出典：cppreference（range-for・structured_binding・enumerate_view）、ACL document_ja/scc.md。表の中身は C++ 章の各ページ（draft）の節の題名と本文で確かめた。コンパイルエラーの文面は各ページに書かれた g++-13・g++-15 の文面を写し、required from here の例と行数（g++-15 で 132 行、g++-13 で 79 行。どちらも -O2 -Wall -Wextra）は手元で出した。新しく noai を確かめたドメインはない

## 台帳への提案

- なし（problems は catalog どおり空。hub・guide の目安 0〜3 の範囲）

## 用語集への提案

- なし（リンクした temporary-object は用語集にある）

## 手引きへの提案

1. **表の中の `|`**：表のセルのコードに `|` を含めるときは、`\|` にしない。手元の python-markdown（.venv、tables 拡張）では、バッククォートの中の `|` は区切りとみなされず、`\|` と書くと逆斜線がそのまま表示された（`v | views::reverse` で確かめた）。§6 の「表の中では `|` の代わりに `\lvert … \rvert`・`\mid`」は数式の話なので、コードについて 1 行足すとよい
2. **guide の complexity**：type guide・hub・pattern のうち計算量のないページは complexity を null のままにする、と §2.1 か §4 に書くと迷わない（今回の指示は「complexity を埋め」だった）

## 早見表・逆引きへの申し送りの反映（b1 handoff §4）

- lookup-types に `bit_ceil`・`__builtin_popcountll`・`mt19937_64 rng(random_device{}())`・`uniform_int_distribution`、`1e18`・`auto INF = 1e18`・`0x3f3f3f3f`・`memset(d, 0x3f, sizeof d)`・`0uz`・`ll(x)` を入れた
- compile-errors に `deduced conflicting types for parameter`・`'constexpr' loop iteration count exceeds limit of 262144`・`constraints not satisfied` を入れた
- symptoms のインタラクティブの行と後の段落は、「同期を切る 2 行があるときに届かない（2 行なしでは届いた）」の条件をそろえて書いた（cpp-io#flush の表に合わせた）
- b1 handoff §5 のとおり、std::function の遅さの倍率は書いていない（cpp-lambda#speed・cpp-io#tle-causes へのリンクだけ）

## メインに頼みたいリンクの張り替え

- cpp-environment が draft になったら、次の 3 か所を節へ張り替える：導入の対応表（→ #version-matrix）、symptoms の「手元でだけ Segmentation fault」（→ #stack-depth）、symptoms の後の段落「疑う順」と「同じ条件にするオプション」（→ #when-results-differ・#options）
- debugging-checklist が draft になったら、symptoms の前置きのリンクを該当の節へ

## 問題の補充の候補

- なし（案内のページなので問題を載せない）

## 未解決の点

1. cpp-comparators#less-equal-pitfall の見出しは「同じ値が多いと Segmentation fault」だが、本文の表では落ちるのは要素 3.5×10^4 以上だけである。このページの symptoms では「大きな入力の sort で RE」と書いた。見出しを本文に合わせるかはメインの判断
2. research/09 §6.1・§6.2 の行き先は統合前のページ名（cpp-ctad・cpp-idioms・cpp-references・acl-modint・cpp-performance など）なので、すべて今の id と節に読み替えた。research の §6.2 にあった `'typeof' was not declared` は、今の本文のどのページにも文面がないので載せていない（cpp-environment#gnu-mode を書くときに確かめて足すとよい）
3. GCC 15 の `-O0` で `_GLIBCXX_ASSERTIONS` が自動で付く話（手元で範囲外が -O0 のときだけ止まる）は、cpp-undefined-behavior#out-of-range にあるので symptoms からはそこへのリンクで済ませた。「-O0 では止まるが -O2 では止まらない」を独立の症状の行にするかは、cpp-environment の執筆後に決めるとよい

## 検証の指摘への対応（b5 verify）

- 直したもの：1（フラッシュの段落を「`cout` なら `endl`、`println`・`printf` なら `fflush(stdout)`」の組に）、2（`-7 % 2` の行を「商は 0 に向かって切り捨て、余りは負になりうる」に。symptoms の同じ行もそろえた）、3（一時オブジェクトの用語集リンクを最初に出る行へ移した）、4（`min(int&, long long int&)` と `operand type is 'std::ranges::dangling'` を併記）、5（引用符の注意を「ロケール（`LANG`）が UTF-8 なら」にして、required from here の抜き出しの前へ移した）、6（compile-errors に `'typeof' was not declared` の行、symptoms に「`-O0` でだけ Assertion で止まる」の行を足した。後者は cpp-environment#when-results-differ にもリンク）、8（図の ② を「（添字, 成分への参照）の組の列にする」に。render_svg の 360px で収まりを確かめた）
- 7（リンクの張り替え）：担当ページの中なので、cpp-environment の 3 か所（#version-matrix・#stack-depth・#when-results-differ と #options）はこちらで張り替えた。debugging-checklist への前置きのリンクは「点検の順」全体を指すので、節ではなくページへのリンクのままにした（特定の節に寄せると WA・TLE・RE のどれかに偏る）
- 「メインに頼みたいリンクの張り替え」の cpp-environment の分は済んだので不要
