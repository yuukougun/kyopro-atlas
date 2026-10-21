# sweep-line-2d の検証（b2）

- 対象：docs/ds/sweep-line-2d.md、snippets/sweep-line-2d/{rectangle-sum,window-max,union-area}.{cpp,yaml}、docs/img/sweep-line-2d/{rectangle-prefix,window-to-rectangle}.svg
- 観点：fact.md・code.md・clarity.md・figure.md
- 環境：g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0。図は `python3 tools/render_svg.py sweep-line-2d`（chrome-headless-shell 146、幅 360px・720px、白背景）で PNG にして目で見た
- atcoder.jp・codeforces.com は開いていない

## 確かめたこと（指摘なし）

- `python3 tools/check_pages.py --page sweep-line-2d`：エラー 0・警告 0
- `python3 tools/check_snippets.py -v snippets/sweep-line-2d`：rectangle-sum 3 case・union-area 4 case・window-max 3 case すべて一致
- サニタイザ（`-O1 -fsanitize=address,undefined`）で 3 本を乱数の入力 400 件ずつ動かした（main の assert による素朴な数え上げとの照合を含む）。rectangle-sum は負の重み・同じ座標・空の長方形を含む。異常・不一致 0
- window-max の main の素朴な方法は「枠の角を点の座標にそろえてよい」という本文の主張に頼るので、主張に頼らない全探索（s・L を -10〜14 のすべての整数で試す Python）と別に 300 件照らした。不一致 0。本文 162 行の「上端を点の時刻にそろえてよい」・171 行の「左端を点の位置に絞れる」の議論も正しい
- 本文の例（103 行）：x < 3 で y ∈ [2, 6) は (1,2)・(2,5) の 2 個、x < 7 では 2,5,4,4,3 の 5 個、差 3 で中は (3,4)・(4,4)・(6,3)。図とも一致
- 窓の条件の同値（153 行）、図の例 D = 3・W = 2・P = (5, 4) で s ∈ [3, 5]・L ∈ [3, 4]（6 点＝D × W）：正しい
- 区間の関係の表（134〜139 行）と「交わる」の余事象が同時に起きない理由：正しい（ただし指摘 2）
- 和集合の面積の (最小値, 最小値をとる長さ) の作用、葉の len を帯の幅にすること、10^18 で long long：正しい。tip の「遅延伝搬なしの書き方」も正しい
- 「値が走査の位置について連続なら順は問わない」（188 行）：g_i は y = L_i で 0 = 0、y = R_i で R_i − L_i = R_i − L_i となり、切り替わりで前後の式が一致する。正しい
- ACL（~/lib/ac-library-master/document_ja/）：fenwick_tree の add・sum は O(log n)、lazy_segtree の apply(l, r, f) は O(log n)、all_prod は O(1)。mapping(f, x)・composition(f, g) の引数の順もコードと合う
- 計算量：要点・front matter の complexity・idea の節が一致
- リンクの anchor：offline-queries#distinct-count・#online、prefix-sum-2d#intervals-as-points、lazy-segment-tree#acl-standard・#size-in-node、fenwick-tree#variants、glossary#offline、inversion-number・contribution・coordinate-compression・cdq-divide-and-conquer・merge-sort-tree・persistent-data-structures はどれも存在する
- 例題 ABC327 F：drken の記事で 1 ≤ N, D, W, T_i, X_i ≤ 2×10^5、枠 S ≤ T < S + D・L ≤ X < L + W、時刻の尺取りと [X − W + 1, X] への区間加算・全体最大、0 未満の切り詰め、O(N log M) を確かめた。記事の本文で D・W の文字が入れ替わる箇所があり、コードは T 向きが D（執筆者の未解決 3 のとおり）。本文は台帳の summary に合っていて問題なし
- 例題 ABC477 F：inamori の記事（check_noai で指定なし）で、各列の黒マスが 1 つの区間であること、高さの向きに走査し各列の累計を a + b·y の 1 次式で持つこと、置き換えは点更新・区間和のセグメント木（遅延なし）、答えは 2 時点の差、O((N + Q) log(N + Q)) を確かめた。本文（BIT 2 本）は同じ解き方の言い換えで食い違いなし。記事は閉区間 1-indexed（下端 C − 1 と上端 D の差）で、本文は半開区間に直していると明記しているので問題なし。ikatakos の記事は今も HTTP 503 で読めなかった
- 力試し ABC360 F：drken の記事で 0 ≤ l < r ≤ 10^9、l で走査し r の軸に区間加算・最大値（同点は最小の r）の遅延セグ木、座標圧縮を確かめた
- 練習・力試しの残り（ABC106 D・186 F・346 G・136 F）：台帳の approach・evidence と方針が合う。要約に手法名はない
- 参考の URL：ikatakos・inamori は check_noai で指定なし。drken・kmjp・betrue12 は付録 B のドメイン
- 図：白背景・viewBox あり・font-family="sans-serif"・相対パス。rectangle-prefix の薄い青は x ∈ [0, 7) 全体に塗られ、斜線は x < 3 に重なる（凡例のとおり）

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 直すべき | fact F2 | rectangle-count の節の 1 段落目（85 行）「点を x の小さい順に処理し、自分を入れる前に BIT の [0, y_i] の和を読めばよい」 | 定義は $x_j \le x_i$ なのに、この手順は x が同じ点どうしで誤る。同じ x の点のうち先に処理した点は数え、後の点は数えない（狭義 $x_j < x_i$ でも先に処理した同じ x の点を余分に数える）。括弧の「不等号が狭義かどうかは問題による」は、その差を手順でどう扱うかを言っていない | 反例：点 (1, 1)・(1, 2)。$x_j \le x_i$ かつ $y_j \le y_i$ なら (1, 2) は (1, 1) を支配し、(1, 1) は何も支配しない。並べ方が (1, 2)→(1, 1) なら (1, 2) の数は 0 になる | 「同じ x の点はまとめて扱う。$x_j \le x_i$ なら同じ x の点を先にすべて入れてから読み（自分の分 1 を引く）、$x_j < x_i$ なら同じ x の点をすべて読んでから入れる（[境界](#boundaries)）」と手順に足す。y の座標圧縮にも一言触れるとよい |
| 2 | 直すとよい | fact F2 / clarity U3 | intervals-as-points の表の「交差する（一部だけ重なる）」の行（139 行）と、応用の型の ABC360 F（146 行） | 表は $L < p \le R < q$ で、端点が 1 点だけ重なる $R = p$ も交差に入れる。ABC360 F の「交差」は端点の一致を含まない狭義（$l_1 < l_2 < r_1 < r_2$）で、表の不等号をそのまま使うと境界を誤る | drken の ABC360 F の記事（コードの条件が狭義） | 表の行に「端点の一致を交差に入れるかは問題による（ABC360 F は $L < p < R < q$ の狭義）」と注を足すか、表を狭義にして「端点の一致を許すなら等号を足す」と書く |
| 3 | 直すとよい | clarity U3 | boundaries の節「データ構造の向きの境界」の最後の文（186 行）「区間を点と見る型のように、区間を BIT に入れるなら、閉区間を [L, R + 1) に直して端点を圧縮する書き方にそろえる」 | intervals-as-points の型で BIT の添字にするのは左端 L だけで、R + 1 は BIT に出てこない。何を何に直すのかが読み取れない | 128 行の手順（BIT の位置 L に 1 を加え、[p, ∞) を読む） | 「区間を点と見る型では BIT の添字は左端 L なので、区間の L とクエリの p をまとめて圧縮し、[p, ∞) は `lower_bound(p)` から末尾までを読む」のように具体にする |
| 4 | 直すとよい | figure G3 | rectangle-prefix.svg（幅 640）・window-to-rectangle.svg（幅 680）の 360px 表示 | 360px では約 0.55 倍に縮み、13px の目盛り・注記（「x = 3 の点 (3, 4) は数え、…」、下の説明文）が 7px ほどになり読みにくい。window-to-rectangle は 2 枚が横並びでとくに小さい | render_svg の 360px の PNG を目視 | 注記・目盛りを 15〜16px に上げる。window-to-rectangle は左右の 2 枚を縦に積むか、下の説明文を本文（代替テキストと前後の文）に任せて図から外す |
| 5 | 直すとよい | fact F5 | 台帳の abc477_f | 台帳の summary が「（執筆時に確かめる）」のまま、approach が「遅延セグ木」。確かめた解説（inamori）は遅延なしの点更新・区間和で、本文とも合わない（執筆者の未解決 1・2） | inamori の記事。ikatakos は 503 で読めず、遅延セグ木の解き方は確かめられない | 執筆者の台帳への提案（summary・approach・evidence に inamori を足す）をそのまま採る。ikatakos が読めるようになったら列と行の向き・制約をメインが確かめる |
| 6 | 直すとよい | clarity U4 | union-area の節（209 行）「各イベントの区間加算と全体の取得が O(log N)」 | all_prod は O(1)（ACL の document_ja）で、計算量の結論は同じだが記述が不正確 | lazysegtree.md の all_prod の計算量 | 「区間加算が O(log N)、全体の取得が O(1)」とする |

## 執筆者の未解決の点について

1. abc477_f の細部：inamori の解説で「各列の黒マスが縦の 1 区間」「クエリは長方形」は確かめた（本文の要約・解き方と一致）。制約の数値と閉区間かどうかは解説に数値がなく、ikatakos は今も 503。本文は数値を書いていないので本文の直しは要らない。指摘 5
2. 台帳の approach（遅延セグ木）と本文の食い違い：本文の解き方が確かめられる方である。台帳を直す（指摘 5）
3. abc327_f の D・W：drken の記事のコードは時刻向きが D で、台帳・本文と一致。問題なし
4. sections の title の短縮：anchor は同じで check_pages も通る。gen_site の作り直しで生成部分が変わることはメインが把握すればよい

## 台帳への提案

- abc327_f・abc360_f・abc477_f：checked に 2026-10-21 を入れる（上の記事で方針を確かめた）。abc477_f は執筆者の提案の summary・approach・evidence を採ったうえで

## 総合の判定

小さな直しで可（直すべき 1・直すとよい 5）。コード片 3 本は乱数とサニタイザでも正しく、主要な主張（窓をそろえる議論・和集合の面積の作用・2 時点の差）はどれも成り立つ。直すべきは支配点の数え上げの手順に、同じ x の点の扱いを足すことだけ。
