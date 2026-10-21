# binary-trie の検証（b2）

対象：docs/ds/binary-trie.md、snippets/binary-trie/{trie,min-pair,implicit}.{cpp,yaml}、docs/img/binary-trie/xor-min.svg
観点：fact.md・code.md・clarity.md・figure.md

## 確かめたこと

- `python3 tools/check_pages.py --page binary-trie`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/binary-trie`：3 本とも 4 case 一致（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）。各コード片の main の乱択の assert（素朴な方法との比較）も通っている
- `npx textlint docs/ds/binary-trie.md`：エラー 0・警告 13（文の長さ・助詞「に」の重なり・数式内の括弧。§14-25 で許される種類）
- `python3 tools/ap.py contest`：abc281_f（diff 1714）・abc308_g（2008）・abc425_g（2205）・arc122_d（2331）の題名と diff が本文・報告と一致
- 本文の数値：$3 \oplus 4 = 7$・$5 \oplus 4 = 1$、図の例 $\{1,3,4,6\}$ と $x = 5$（$4, 6, 1, 3$ の XOR）・ノードの個数・枝のラベル・降りる道、確認問題 1（bit 2・bit 0 ↔ 深さ 0・2）、確認問題 2（$B = 2$ なら 0 が返る）、ノード数 $1 + NB$・$6 \times 10^6 \times 12$ バイト ≈ 72 MB をすべて手で確かめた
- 自分で導いた主張を小さなプログラムで確かめた（作業用の場所の g.cpp。リポジトリには置いていない）
    - 「昇順で隣り合う組に XOR 最小の組がある」：要素 2〜8 個・値 64 未満の乱択 3000 回で全組の最小と一致
    - 練習 ABC425 G のヒント（$[0, M)$ を上位 bit から分け、$M$ の bit が 1 の段で「$x$ の bit を 0 にした半分」の到達ノードに full_sum を使い、残りは $M$ の bit に沿って降りる）：台帳の summary の問いとして、$B \le 6$・乱択 3000 回で全探索と一致（$M < 2^B$ の範囲。$M = 2^B$ は full_sum そのもの）
    - implicit の「片側だけなら 子の和 × 2 + $2^b \cdot 2^b$」：コード片の assert（300 回）と同じ式で確認
- 参考の URL：drken の記事は h1「AtCoder ABC 281 F - Xor Minimization (2D, 青色, 500 点)」で題名どおり、上位 bit で分ける再帰（本文と同じ方針）。merom686 の記事は ABC308 の Binary Trie で部分木ごとの最小を持ち上げ、「部分木の XOR を持てば簡単だった」と書いており本文の記述と合う。Library Checker の題名「Set Xor-Min」は library-checker-problems の info.toml（title = "Set Xor-Min"、MAX_Q = 500000）で確かめた。クエリは 0 x 追加（あれば何もしない）・1 x 削除（なければ何もしない）・2 x で $\min (i \oplus x)$、2 のとき集合は空でない。本文の「追加・削除・x との XOR の最小の検証」と合う
- 未解決の点（執筆者の報告）
    - abc425_g の evidence（ikatakos）は今も 503 で読めなかった。Web 検索でも第三者の解説は見つからなかった → 指摘 6
    - abc308_g の細部（多重集合か等）は merom686 の記事に問題文の記述がなく、確かめられなかった。本文はこの点に依らない書き方で、min-pair.cpp は多重集合でも正しい（乱択で確認済み）ので、本文の直しは要らない
    - Set Xor-Min の題名は上のとおり確かめた。解決済み
- 図：`python3 tools/render_svg.py binary-trie` で 360px・720px の PNG を目視。文字の重なり・はみ出しなし、背景は白で塗られている（ダークでも読める）。太線（実線・破線）と色の両方で道を示しており、色だけに頼っていない。代替テキストと直後の箇条書きで図なしでも道が分かる

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すとよい | fact（F2）・clarity（U3） | #comparison の 1 行目「2 要素の XOR の最小（全体への XOR がない）」 | 「全体への XOR がない」の条件は要らず、読者に「全体に XOR をかけると隣り合う組の方法は使えない」と誤解させる。2 要素の XOR は全体への XOR で変わらない（$(a \oplus M) \oplus (b \oplus M) = a \oplus b$）ので、木と同じく元の値のまま隣り合う組を持てば済む | 式の計算 | 括弧書きを消すか、「全体に XOR をかけても 2 要素の XOR は変わらないので、元の値のまま持てばよい」と一言添える |
| 2 | 直すとよい | clarity（U3）・fact（F7） | #implicit の後半「$x$ の範囲が $[0, M)$ のように…$M$ を上位 bit から見て」 | 直前の #kth-and-global-xor で $M$ を「かけた値の累計」に使っており、同じページで同じ記号が別の意味になる。断片で読む claude.ai でも、ページ全体を読む人でも引っかかる | 本文の 2 か所の定義 | #implicit 側は「上限 $M$（ABC425 G の記号）」と断るか、累計の方を $T$ などに変える |
| 3 | 直すとよい | clarity（U8） | 確認問題 2「子の有無で降りる側を決めるとどうなるか」 | $B$ が書かれていない。答えの「根から bit 1 で子 1」は $B = 2$ を前提にしている（$B = 3$ なら根は bit 2 で、道の説明がずれる） | 手計算 | 問いに「$B = 2$ の木に」と足す |
| 4 | 直すとよい | fact（F7） | #pitfalls「ぶら下がり参照」 | リンク先の用語集の見出しは「ダングリング」で、語が違う。読者がリンクを開いて別の語に着き、同じものか迷う | docs/guide/glossary.md:339 `### ダングリング {#dangling}` | 「ダングリング（ぶら下がり参照）」とする。用語集に別名を足すなら提案に書く |
| 5 | 直すとよい | fact（F7）・F10 | front matter の sections と見出し「作り方（上位ビットから辿る二分木・ノードに個数）」「明示的に作らない Binary Trie（上位ビットで分ける再帰）」 | 付録 A・§14-22 の正規形は「上位 bit」で、本文も「上位 bit」を使うのに、見出しだけ「上位ビット」。「辿る」も本文の「たどる」とそろっていない。執筆者は kth の title だけ prh に合わせて直している | style-guide 付録 A「上位 bit」・§14-22 | 2 つの見出しと sections の title を「上位 bit から」「上位 bit で」「たどる」に直す（anchor は変えない。§14-12 で title の直しは許される） |
| 6 | 直すとよい | fact（F5） | #practice の ABC425 G の行とヒント、台帳 abc425_g | 台帳の summary（問い）が第三者の資料で確かめられていない（evidence の ikatakos は 503、検索でも解説が見つからない）。ヒントの正しさは summary の問いに対しては乱択で確かめたが、問いそのものが違えばヒントも外れる | 執筆者の報告・今回の取得の結果 | checked を null のままにし、メインがあとで ikatakos か別の解説で問いと制約を確かめる。読めるまで本文はこのままでよい |
| 7 | 直すとよい | code（C3） | snippets/binary-trie/min-pair.cpp の MinPairTrie | #pitfalls で「最大のノード数が分かっているので reserve しておく」と書いているのに、例題のコード片は reserve をせず 4 本の vector を push_back で伸ばす。1 ノード 28 バイトで、$Q = 3 \times 10^5$・$B = 30$ なら 9×10^6 ノード・約 250 MB になり、伸ばす瞬間に一時的にその数倍を使う。各操作で `vector<int> path` を作る点も定数倍が重い | コードの読み・見積もり（ABC308 G の Q の上限は確かめていない） | trie.cpp と同じく、コンストラクタで最大ノード数を受け取り reserve する。path は `array<int, 31>` か固定長の配列にする |
| 8 | 直すとよい | figure（G3） | xor-min.svg の 360px 表示 | 幅 600 の viewBox が 360px で 0.6 倍になり、下の凡例 3 行と葉の下のラベルが約 10px になる。読めなくはないが小さい | render_svg の 360px の PNG を目視 | 凡例を 1 行目の題と同じく短くするか、font-size を 18 程度に上げる。直さなくても可 |
| 9 | 直すとよい | clarity（U5）・F5 | #practice | 練習が 1 問で、目安の 2〜6 に足りない（執筆者も報告済み） | style-guide の目安 | 執筆者の候補 arc122_d（力試し）をメインが台帳に加えるかを判断する |

直すべき指摘：0 件。直すとよい指摘：9 件。

## 台帳への提案

- abc281_f・abc308_g：題名と diff は ap.py で確認。abc308_g の checked は、merom686 の記事で「部分木ごとに 2 要素の XOR の最小を持ち上げる」方針を確かめたので 2026-10-21 を入れてよい（問題の細部は未確認）
- abc425_g：checked は null のまま（指摘 6）

## 総合の判定

小さな直しで可（直すべき 0 件、直すとよい 9 件）。計算量・定理の主張・例の数値・コード片・図はすべて確かめて誤りはなかった。
