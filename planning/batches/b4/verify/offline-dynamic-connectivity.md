# offline-dynamic-connectivity の検証（fact・code・clarity・figure）

対象：docs/graph/offline-dynamic-connectivity.md、snippets/offline-dynamic-connectivity/usage.{cpp,yaml}、docs/img/offline-dynamic-connectivity/time-segment-tree.svg

## 確かめたこと

- `python3 tools/check_pages.py --page offline-dynamic-connectivity`：エラー 0・警告 0
- `python3 tools/fix_problems.py --check --page offline-dynamic-connectivity`：直すべき行 0
- textlint：エラー 0・警告 21（文の長さ・区間の括弧など。誤検出の範囲）
- `python3 tools/check_snippets.py snippets/offline-dynamic-connectivity`：期待と違う 0（g++-15 (Ubuntu 15.2.0-15ubuntu1~22~ppa2) 15.2.0）
- `g++-15 -std=gnu++23 -O2 -Wall -Wextra -fsanitize=address,undefined` でコンパイルし、乱数の入力 1500 件（頂点数 1〜6、クエリ 0〜20、同じ辺の再追加・端点を入れ替えた削除を含む）を素朴な再計算（Python）と比べた：すべて一致、サニタイザの報告なし、末尾の assert も通る
- 頂点の値の加算の扱い（本文 dfs-rollback の段落）：加算を時刻 $[t, Q)$ のノードに載せ、入るときに根の合計へ足し・出るときに（そのノードの併合を取り消す前に）引く実装を一時置き場で書き、Library Checker の問題と同じ形の乱数入力 800 件を素朴な方法と比べた：すべて一致。本文の方法は正しい
- 例題 abc334_g：`python3 tools/ap.py show abc334_g` で題名・diff 2242 を確認。本文の「辺を 3 区間に分けて載せ、葉で成分数 − 1」を Python で実装し、5×5 以下の乱数グリッド 500 件で全マスの除去を素朴に数えた結果と一致した。kmjp 氏の記事（noai の指定なし）は、マスを $[0, h)$・$[h + 1, G)$ に載せる形で、本文の「kmjp 氏の解説はこの形」と合う。法は 998244353（記事のコード）で、本文の「問題が指定する法」と矛盾しない
- 参考の URL：kmjp（h1 と一致）、cp-algorithms（題名一致。時間軸のセグメント木・ロールバックと動的連結性の実装がある）、Library Checker の task.md（追加の直前に辺がない・削除の直前に辺があるの保証。本文の前提と合う）、amentorimaru（check_noai で指定なし。題名は指摘 1）
- 計算量（F1）：要点・front matter・本文の根拠の 3 か所が $O(N + Q \log Q \log N)$・メモリ $O(N + Q \log Q)$ で一致。最悪 $O(\log N)$ でならしでないことも明記されている
- 図：`python3 tools/render_svg.py offline-dynamic-connectivity --scale 2` で 360px・720px を目視。文字の重なり・はみ出しなし、背景は白、幅 400・viewBox と同じ比。$[1, 6)$ が葉 1・$[2, 4)$・$[4, 6)$ に分かれるのは正しく、本文の「葉 3 は $[2, 4)$ を通る」「葉 6 は通らない」とも合う
- 執筆者の未解決の点 1（rollback-union-find の「根だけに足すと…残る」との食い違いの見え方）は指摘 2、点 2（例題の制約）は指摘 4 で扱った。点 3（lowlink との別解の記述）はそろっている

## 指摘

| 番号 | 重さ | 観点 | 場所 | 問題 | 根拠 | 直し方 |
|---|---|---|---|---|---|---|
| 1 | 直すべき | fact F9 | 参考の 2 行目（amentorimaru） | 記事の題名に、h1 ではなく記事の書き出し（og:description）の「LowLinkなにもわかってないのがバレる」を使っている。著者もブログの表示名と違う | 記事の h1（entry-title）は「【AtCoder】G - Christmas Color Grid 2 / AtCoder Beginner Contest 334」、ブログ名は「あめんばーどのバーチャル日記」。手引き §14-24（ブログの題名は記事の h1）。lowlink.md の参考は「あめんばーど「G - Christmas Color Grid 2 / AtCoder Beginner Contest 334」」と書いている | 「[あめんばーど「【AtCoder】G - Christmas Color Grid 2 / AtCoder Beginner Contest 334」](…)」にする（lowlink.md の表記との統一はメインが決める） |
| 2 | 直すとよい | clarity U3・fact F2 | dfs-rollback の「頂点の値の加算」の段落 | rollback-union-find#offline-dynamic-connectivity は「加算は取り消してはいけないので」と書き、本ページは「出るときに引けば…取り消せる」と書くので、両方を読む読者には食い違って見える。また、根に成分の合計を持たせ、併合で足し・取り消しで引くこと、同じノードに辺と加算があるときは加算を引いてから併合を取り消すこと（逆にすると $\mathrm{find}(v)$ が入るときと違う根になる）が書かれていない | 一時置き場の実装で、この順なら 800 件すべて一致。rollback-union-find の段落は「葉で加算をそのまま行い、取り消さない」書き方の話 | 段落に 1〜2 文足す。例：「根に成分の値の合計を持たせ、併合で足し、取り消しで引く。同じノードでは加算を先に引いてから併合を取り消す。ロールバックできる Union-Find の節は、加算を葉でそのまま行い取り消さない書き方で、そちらでは根だけに足すと崩れる」 |
| 3 | 直すとよい | figure G5 | time-segment-tree.svg の葉 1 | 葉 1 の枠に時刻の数字がなく「e」だけが書かれ、ほかの葉（0, 2, …, 7）と並べると何番の葉か読み取りにくい。上の段は「[2, 4) に e」と区間も書いている | 360px・720px の PNG を目視。代替テキストは「葉 [1, 2)」と書いている | 葉 1 の文字を「1 に e」にする（枠の幅 41 に収まるよう font-size を 11〜12 にするか、e を枠の上に小さく添える） |
| 4 | 直すとよい | fact F5・clarity U7 | 例題 abc334_g の解法の詳細 | 本文の主な方法（隣り合う 2 マスの辺を 3 区間に分けて載せる）は、マスそのものを載せる方法よりノードに載る要素がかなり多い。制約が大きいとメモリが重いことに触れていない | 手元の列挙で数えた値：1000×1000 がすべて緑のとき、辺を載せる方法は 49,818,233 個（pair<int,int> で約 400MB に、4G 個の vector の分が加わる）、マスを載せる方法は 19,951,424 個。制約は問題ページを開けないので確かめていない（kmjp 氏のコードの配列の大きさは 1000 程度を示唆する） | 4 つ目の箇条（マスを載せる書き方）に「載せる要素が辺の方法の半分以下で済み、盤面が大きいときはこちらが軽い」と添える |

## 総合の判定

小さな直しで可（直すべき 1 件・直すとよい 3 件）。本文の事実・計算量・コード片・図の内容はいずれも確かめた範囲で正しい。
